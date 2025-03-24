/*
 *  Copyright (c) Texas Instruments Incorporated 2024-25
 *  All rights reserved.
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
 *  \file can_response_config.c
 *
 *  \brief File containing the CAN response implementation for boot app
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/pinmux.h>
#include <drivers/gpio.h>
#include <drivers/mcan.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "can_response_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t gMcanModAddr;

/* Initialize MCU MCAN 0 STB Pinmux */
static Pinmux_PerCfg_t gPinMuxMcanStb[] = {
    /* MCU MCAN 0 STB pin config */
    {
        PIN_WKUP_UART0_RTSN,
        (PIN_MODE(7))
    },
    {PINMUX_END, PINMUX_END}
};

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 * \brief  This function will configure MCAN module
 *
 * \param  mcanInstAddr MCAN Instance address
 *
 * \return CSL_PASS for success, CSL_EFAIL for failure
 */
static int32_t CanResponseApp_canConfig(uint32_t mcanInstAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CanResponseApp_enableTransceivers(void)
{
    /*  Configure padconfig registers of MCU MCAN 0 STB pin */
    Pinmux_config(gPinMuxMcanStb, PINMUX_DOMAIN_ID_MCU);
    /* Set MCU_MCAN0_STB pin to LEVEL_Low to exit CAN0 from Standby mode */
    GPIO_setDirMode(CSL_MCU_GPIO0_BASE, MCAN_RESPONSE_APP_MCU_MCAN0_STB_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_pinWriteLow(CSL_MCU_GPIO0_BASE, MCAN_RESPONSE_APP_MCU_MCAN0_STB_PIN);
    return;
}

void CanResponseApp_transmit(void)
{
    int32_t             status = CSL_PASS;
    uint32_t            loopCnt = 0U;
    MCAN_TxBufElement   txMsg;
    MCAN_ProtocolStatus protStatus;

    /* MCAN Module for usage */
    gMcanModAddr = CSL_MCU_MCAN0_MSGMEM_RAM_BASE;

    /* Configure MCAN Module */
    status = CanResponseApp_canConfig(gMcanModAddr);
    if(CSL_PASS != status)
    {
        DebugP_log("Error in MCAN config\r\n");
    }
    else
    {
        /* Initialize message to transmit */
        txMsg.id  = (uint32_t)((uint32_t)(0x4U) << 18U);    /* Message ID */
        txMsg.rtr = 0U;                                     /* Remote Transmission Request disabled */
        txMsg.xtd = 0U;                                     /* Extended Identifier disabled */
        txMsg.esi = 0U;                                     /* Error State Indicator bit depends on Error Passive Flag */
        txMsg.dlc = 0xFU;                                   /* Data Length Code = 64B */
        txMsg.brs = 1U;                                     /* Bit Rate Switching enabled */
        txMsg.fdf = 1U;                                     /* FD Format enabled */
        txMsg.efc = 0U;                                     /* Event FIFO Control disabled */
        txMsg.mm  = 0xAAU;                                  /* Dummy value for Message Marker */

        for (loopCnt = 0; loopCnt < MCAN_MAX_PAYLOAD_BYTES; loopCnt++)
        {
            txMsg.data[loopCnt] = loopCnt;                  /* Populate Data bytes */
        }

        /* Write message to Msg RAM */
        MCAN_writeMsgRam(gMcanModAddr, MCAN_MEM_TYPE_BUF, 1U, &txMsg);

        /* Add request for transmission */
        status = MCAN_txBufAddReq(gMcanModAddr, 1U);

        if (CSL_PASS != status)
        {
            DebugP_log("Error in Adding Transmission Request...\r\n");
        }
        else
        {
            MCAN_getProtocolStatus(gMcanModAddr, &protStatus);

            /* Checking for Errors: Last Error Code, Data Phase Last Error Code and Protocol Exception Event */
            if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                (0U == protStatus.pxe))
            {
                DebugP_log("Message successfully transferred with payload Bytes: %dB\r\n",MCAN_MAX_PAYLOAD_BYTES);
            }
            else
            {
                DebugP_log("Error in transmission with payload Bytes\r\n");
                status = CSL_EFAIL;
            }
        }
        if (CSL_EFAIL == status)
        {
            DebugP_log("CAN message transmission FAILED...\r\n");
        }
        else
        {
            DebugP_log("CAN message successfully transmitted...\r\n");
        }
    }
    return;
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static int32_t CanResponseApp_canConfig(uint32_t mcanInstAddr)
{
    int32_t                    configStatus = CSL_PASS;
    uint32_t                   timeout      = 100U;
    MCAN_InitParams            initParams;
    MCAN_ConfigParams          configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_BitTimingParams       bitTimes;

    /* Initialize MCAN Init params */
    initParams.fdMode          = 0x1U;      /* FD operation enabled */
    initParams.brsEnable       = 0x1U;      /* Bit rate switching for transmissions enabled */
    initParams.txpEnable       = 0x0U;      /* Transmit pause disabled */
    initParams.efbi            = 0x0U;      /* Edge filtering disabled */
    initParams.pxhddisable     = 0x0U;      /* Protocol exception handling enabled */

    /* To enable automatic retransmission of the packet, program initParams.darEnable to "0" */
    initParams.darEnable       = 0x1U;      /* Disabled Automatic Retransmission */
    initParams.wkupReqEnable   = 0x1U;      /* Wakeup request is enabled */
    initParams.autoWkupEnable  = 0x1U;      /* Auto-Wakeup is enabled */
    initParams.emulationEnable = 0x1U;      /* Emulation/Debug Suspend is enabled */
    initParams.emulationFAck   = 0x0U;      /* Emulation/Debug Suspend does not wait for idle/immediate effect */
    initParams.clkStopFAck     = 0x0U;      /* Clock Stop does not wait for idle/immediate effect */
    initParams.wdcPreload      = 0xFFU;     /* Start value of the Message RAM Watchdog Counter */
    initParams.tdcEnable       = 0x1U;      /* Transmitter Delay Compensation is enabled */
    initParams.tdcConfig.tdcf  = 0xAU;      /* Transmitter Delay Compensation Filter Window Length Range:[0x0-0x7F] */
    initParams.tdcConfig.tdco  = 0x6U;      /* Transmitter Delay Compensation Offset Range:[0x0-0x7F]*/

    /* Initialize MCAN Config params */
    configParams.monEnable         = 0x0U;      /* Bus Monitoring Mode is disabled */
    configParams.asmEnable         = 0x0U;      /* Restricted Operation Mode disabled */
    configParams.tsPrescalar       = 0xFU;      /* Timestamp Counter Prescaler */
    configParams.tsSelect          = 0x0U;      /* Timestamp counter value set to 0x0000 always */
    configParams.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;  /* Time-out counter source select - Continuous operation Mode */
    configParams.timeoutPreload    = 0xFFFFU;   /* Start value of the Timeout Counter */
    configParams.timeoutCntEnable  = 0x0U;      /* Time-out Counter is disabled */
    configParams.filterConfig.rrfs = 0x1U;      /* Reject all remote frames with 11-bit standard IDs */
    configParams.filterConfig.rrfe = 0x1U;      /* Reject all remote frames with 29-bit extended IDs */
    configParams.filterConfig.anfe = 0x2U;      /* Accept Non-matching Frames Extended disabled */
    configParams.filterConfig.anfs = 0x2U;      /* Accept Non-matching Frames Standard disabled */

    /* Initialize Message RAM Sections Configuration Parameters */
    msgRAMConfigParams.lss                  = MCAN_RESPONSE_APP_MCAN_STD_ID_FILT_NUM;            /* Standard Message Filter section not configured */
    msgRAMConfigParams.lse                  = MCAN_RESPONSE_APP_MCAN_EXT_ID_FILT_NUM;            /* Extended Message Filter section not configured */
    msgRAMConfigParams.txStartAddr          = MCAN_RESPONSE_APP_MCAN_TX_BUFF_START_ADDR;         /* Tx Buffers Start Address */
    msgRAMConfigParams.txBufCnt             = MCAN_RESPONSE_APP_MCAN_TX_BUFF_SIZE;               /* No. of dedicated transmit buffers */
    msgRAMConfigParams.txFIFOCnt            = MCAN_RESPONSE_APP_MCAN_TX_FIFO_SIZE;               /* Tx FIFO/Queue section not configured*/
    msgRAMConfigParams.txBufMode            = 0U;                                       /* Tx Queue operation disabled */
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_64BYTES;                   /* Tx Buffer Element Size */
    msgRAMConfigParams.txEventFIFOCnt       = MCAN_RESPONSE_APP_MCAN_TX_EVENT_SIZE;              /* Tx Event FIFO section not configured */
    msgRAMConfigParams.rxFIFO0Cnt           = MCAN_RESPONSE_APP_MCAN_RX_FIFO_0_NUM;              /* Rx FIFO0 section not configured */
    msgRAMConfigParams.rxFIFO1Cnt           = MCAN_RESPONSE_APP_MCAN_RX_FIFO_1_NUM;              /* Rx FIFO1 section not configured */
    msgRAMConfigParams.rxBufStartAddr       = MCAN_RESPONSE_APP_MCAN_RX_BUFF_START_ADDR;         /* Rx Buffer Start Address */
    msgRAMConfigParams.rxBufElemSize        = MCAN_ELEM_SIZE_64BYTES;                   /* Rx Buffer Element Size */

    /* Initialize bit timings, configuring 1Mbps and 5Mbps as nominal and data bit-rate respectively */
    bitTimes.nomRatePrescalar   = 0x7U;     /* Nominal Baud Rate Pre-scaler */
    bitTimes.nomTimeSeg1        = 0x5U;     /* Nominal Time segment before sample point */
    bitTimes.nomTimeSeg2        = 0x2U;     /* Nominal Time segment after sample point */
    bitTimes.nomSynchJumpWidth  = 0x0U;     /* Nominal (Re)Synchronization Jump Width */
    bitTimes.dataRatePrescalar  = 0x1U;     /* Data Baud Rate Pre-scaler */
    bitTimes.dataTimeSeg1       = 0x3U;     /* Data Time segment before sample point */
    bitTimes.dataTimeSeg2       = 0x2U;     /* Data Time segment after sample point */
    bitTimes.dataSynchJumpWidth = 0x0U;     /* Data (Re)Synchronization Jump Width */

    /* Wait for memory initialization to happen */
    do
    {
        if(TRUE == MCAN_isMemInitDone(mcanInstAddr))
        {
            break;
        }
        timeout--;
    } while(timeout>0);

    if(0U == timeout)
    {
        configStatus = CSL_EFAIL;
    }
    else
    {
        /* Resetting timeout value */
        timeout = 100U;
    }

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(mcanInstAddr, MCAN_OPERATION_MODE_SW_INIT);
    do
    {
        if(MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(mcanInstAddr))
        {
            break;
        }
        timeout--;
    } while (timeout>0);

    if(0U == timeout)
    {
        configStatus = CSL_EFAIL;
    }
    else
    {
        /* Resetting timeout value */
        timeout = 100U;
    }

    /* Initialize MCAN module */
    MCAN_init(mcanInstAddr, &initParams);

    /* Configure MCAN module */
    MCAN_config(mcanInstAddr, &configParams);
    MCAN_setBitTime(mcanInstAddr, &bitTimes);

    /* Configure Message RAM Sections */
    MCAN_msgRAMConfig(mcanInstAddr, &msgRAMConfigParams);

    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(mcanInstAddr, MCAN_OPERATION_MODE_NORMAL);
    do
    {
        if(MCAN_OPERATION_MODE_NORMAL == MCAN_getOpMode(mcanInstAddr))
        {
            break;
        }
        timeout--;
    } while (timeout>0);

    if(0U == timeout)
    {
        configStatus = CSL_EFAIL;
    }

    return configStatus;
}