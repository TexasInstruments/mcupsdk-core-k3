/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file fwl_isolation_mcu.c
 *
 *  \brief The example demonstrates the MCU firewall isolation in the use case
 *         when the MCU domain is running a safety application. The application
 *         configures a firewall to the MAIN domain I2C by allowing access only
 *         to the MCU core. After configuring the firewall, it reads data from
 *         the main domain I2C to check the access from MCU core. Then it will
 *         a send a ipc notify message to the other core running this example to
 *         trigger a firewall exception. The MCU core receives a interrupt for
 *         firewall exception. If the interrupt is not received the test fails.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/i2c.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Firewall exception interrupt number */
#define FWL_EXCEPTION_NOTIFY_INT_NUM    (CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_SMS0_COMMON_0_COMBINED_SEC_IN_0)

#define I2C_READ_LEN                    (1U)

/* CSL ID of the core that triggers firewall exception */
#if defined (SOC_AM62AX)
#define FWL_EXCEPTION_TRIGGER_CORE_ID    (CSL_CORE_ID_R5FSS0_0)
#elif defined (SOC_AM62PX)
#define FWL_EXCEPTION_TRIGGER_CORE_ID    (CSL_CORE_ID_WKUP_R5FSS0_0)
#endif

/* IPC notify client ID that is used to send and receive messages */
#define IPC_NOTIFY_CLIENT_ID     (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern uint32_t Board_i2cGetEepromDeviceAddr();

static int32_t FwlApp_i2cFwlConfigure();
static int32_t FwlApp_i2cRead();
static void FwlApp_excptIntrISR(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Object for registering exception handler */
static HwiP_Params gFwlHwiParams;
static HwiP_Object gFwlHwiObj;

/* Global variable to notify fwl exception */
volatile uint32_t gExcptTestPass;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void fwl_isolation_main(void *args)
{
    int32_t status = SystemP_FAILURE;
    uint32_t waitCount = 0;

    /* Wait for all cores to be ready */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    /* Configure I2C0 region firewall to allow access only to MCU core */
    status = FwlApp_i2cFwlConfigure();

    if(SystemP_SUCCESS == status)
    {
        /* Read data from EEPROM through I2C0 to check the firewall is allowing to read */
        status = FwlApp_i2cRead();
    }

    if(SystemP_SUCCESS == status)
    {
        if(SystemP_SUCCESS == status)
        {
            /* Register handler for firewall exception */
            HwiP_Params_init(&gFwlHwiParams);
            gFwlHwiParams.intNum = FWL_EXCEPTION_NOTIFY_INT_NUM;
            gFwlHwiParams.callback = (HwiP_FxnCallback)FwlApp_excptIntrISR;
            gFwlHwiParams.args = (void *)NULL;
            status = HwiP_construct(&gFwlHwiObj, &gFwlHwiParams);
        }

        if(SystemP_SUCCESS == status)
        {
            /* Send ipc notify to the other core to trigger firewall exception */
            status = IpcNotify_sendMsg(FWL_EXCEPTION_TRIGGER_CORE_ID, IPC_NOTIFY_CLIENT_ID, 0x0, 0);
            if(SystemP_SUCCESS == status)
            {
                /* Wait for firewall exception trigger from the other core */
                DebugP_log("Waiting for firewall exception trigger from the other core... \r\n");
                while ((gExcptTestPass == FALSE) && (waitCount++ < 100u))
                {
                    ClockP_usleep(10);
                }

                if (gExcptTestPass == TRUE)
                {
                    DebugP_log("Firewall exception occurred... \r\n");
                    status = SystemP_SUCCESS;
                }
                else
                {
                    DebugP_logError ("Firewall exception test failed timedout ...\r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed\r\n");
    }

    return;
}

static int32_t FwlApp_i2cFwlConfigure()
{
    int32_t status = SystemP_FAILURE;

    /* Lock the firewall ownership to MCU core, so that other cores cannot modify this firewall configuration */
    const struct tisci_msg_fwl_change_owner_info_req fwl_owner_req =
    {
        .fwl_id = CSL_STD_FW_I2C0_CFG_ID,
        .region = 0,
        .owner_index = TISCI_HOST_ID_MCU_0_R5_0,
    };
    struct tisci_msg_fwl_change_owner_info_resp fwl_owner_resp = { 0 };
    status = Sciclient_firewallChangeOwnerInfo(&fwl_owner_req, &fwl_owner_resp, SystemP_TIMEOUT);

    if(SystemP_SUCCESS == status)
    {
        /* Configure the whole region covered by the firewall to allow access to all cores as a background region */
        const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
        {
            .fwl_id = CSL_STD_FW_I2C0_CFG_ID,
            .region = 0,
            .n_permission_regs = 3,
            /*
             * The firewall control register layout is
             *  ---------------------------------------------------------------------------
             * |  31:10   |      9     |     8      |     7:5    |      4      |   3:0     |
             *  ---------------------------------------------------------------------------
             * | Reserved | Cache Mode | Background |  Reserved  | Lock Config |  Enable   |
             *  ---------------------------------------------------------------------------
             *
             * Enable = 0xA implies firewall is enabled. Any other value means not enabled
             *
             */
            .control = 0x30A, /* 0x3 - Firewall background region, Unlocked. 0xA - Enable Firewall */
            /*
             * The firewall permission register layout is
             *  ---------------------------------------------------------------------------
             * |  31:24   |    23:16   |  15:12     |   11:8     |   7:4      |   3:0      |
             *  ---------------------------------------------------------------------------
             * | Reserved |   Priv ID  | NSUSR-DCRW | NSPRI-DCRW | SUSER-DCRW | SPRIV-DCRW |
             *  ---------------------------------------------------------------------------
             *
             * PRIV_ID = 0xC3 implies all.
             * In each of the 4 nibbles from 15:0 the 4 bits means Debug, Cache, Read, Write Access for
             * Non-secure user, Non-secure Priv, Secure user, Secure Priv respectively. To enable all access
             * bits for all users, we set each of these nibbles to 0b1111 = 0xF. So 15:0 becomes 0xFFFF
             *
             */
            .permissions[0] = 0xC3FFFF,
            .permissions[1] = 0xC3FFFF,
            .permissions[2] = 0xC3FFFF,
            .start_address  = 0X0,
            .end_address    = 0xFFFFFFFFU,
        };
        struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = { 0 };

        status = Sciclient_firewallSetRegion(&fwl_set_req, &fwl_set_resp, SystemP_TIMEOUT);
    }

    if(SystemP_SUCCESS == status)
    {
        /*
         * Lock I2C0 Config region by region based firewall only to MCU core. Configure this as a foreground region.
         * This will override the above config only for I2C region. So all other regions covered by the firewall
         * can be accessed by other cores.
         */
        const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
        {
            .fwl_id = CSL_STD_FW_I2C0_CFG_ID,
            .region = 1,
            .n_permission_regs = 3,
            .control = 0xA, /* 0xA - Enable Firewall */
            .permissions[0] = 0x60FFFF, /* PRIV_ID = 0x60 implies MCU R5 core */
            .permissions[1] = 0x60FFFF,
            .permissions[2] = 0x60FFFF,
            .start_address  = CSL_STD_FW_I2C0_CFG_CFG_START,
            .end_address    = CSL_STD_FW_I2C0_CFG_CFG_END,
        };
        struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = { 0 };

        status = Sciclient_firewallSetRegion(&fwl_set_req, &fwl_set_resp, SystemP_TIMEOUT);
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Configure I2C0 firewall to allow access only to MCU core... DONE !!!\r\n");
    }
    else
    {
        DebugP_logError("Configure I2C0 firewall ... Failed !!!\r\n");
    }

    return status;
}

static int32_t FwlApp_i2cRead()
{
    uint16_t        sample;
    int32_t         status;
    uint32_t        i2cReadSlaveAddr;
    uint8_t         rxBuffer[I2C_READ_LEN];
    I2C_Handle      i2cHandle;
    I2C_Transaction i2cTransaction;

    i2cReadSlaveAddr     = Board_i2cGetEepromDeviceAddr();
    i2cHandle = gI2cHandle[CONFIG_I2C0];

    DebugP_log("I2C read data through MCU core... !!!\r\n");

    /* Set default transaction parameters */
    I2C_Transaction_init(&i2cTransaction);

    /* Override with required transaction parameters */
    i2cTransaction.readBuf      = rxBuffer;
    i2cTransaction.readCount    = I2C_READ_LEN;
    i2cTransaction.slaveAddress = i2cReadSlaveAddr;

    /* Read 5 samples and log them */
    for(sample = 0; sample < 5; sample++)
    {
        status = I2C_transfer(i2cHandle, &i2cTransaction);
        if(status == I2C_STS_SUCCESS)
        {
            DebugP_log("Sample %u: %u\r\n", sample, rxBuffer[0]);
        }
        else
        {
            DebugP_logError("Sample %u: I2C Read failed\r\n", sample);
        }
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("I2C read data through MCU core... DONE !!!\r\n");
    }
    else
    {
        DebugP_logError("I2C read data through MCU core... Failed !!!\r\n");
    }

    return status;
}

/* FWL Exception interrput ISR */
static void FwlApp_excptIntrISR(void)
{
    gExcptTestPass = TRUE;

    return;
}
