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
 *  \file fwl_isolation_main.c
 *
 *  \brief This example waits for ipc notify message from the MCU core.
 *         Upon receiving the message it triggers a firewall exception
 *         by accessing the region firewalled by the MCU core.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <stdlib.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Accessing this address will trigger a firewall exeption */
#define FWL_EXCEPTION_ADDR            (CSL_I2C0_CFG_BASE)

/* IPC notify client ID that is used to send and receive messages */
#define IPC_NOTIFY_CLIENT_ID     (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void FwlApp_ipcNotifyISR (uint16_t remoteCoreId, uint16_t localClientId,
                                uint32_t msgValue, void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void fwl_isolation_main(void *args)
{
    int32_t status = SystemP_FAILURE;

    /* Regsiter IPC notify handler to trigger firewall exception */
    status = IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID, FwlApp_ipcNotifyISR, NULL);
    DebugP_assert (status == SystemP_SUCCESS);

    DebugP_log("Waiting for ipc notify message to trigger firewall exception....\r\n");

    /* Wait for all cores to be ready */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    return;
}

static void FwlApp_ipcNotifyISR (uint16_t remoteCoreId, uint16_t localClientId,
                                uint32_t msgValue, void *args)
{
    uint32_t val, addr = 0U;

    if (remoteCoreId == CSL_CORE_ID_MCU_R5FSS0_0)
    {
        if (localClientId == IPC_NOTIFY_CLIENT_ID)
        {
            /* Access the I2C0 config memory location to trigger firewall exception */
            addr = (uint32_t)FWL_EXCEPTION_ADDR;
            val = (addr) ? (CSL_REG32_RD(AddrTranslateP_getLocalAddr(addr))) : 0U;
            (void) val;

            /*
            * If the address being accessed in the above statement is not firewalled against
            * access from the core executing this example, there would be no data abort and
            * the below code would get executed. If the following code gets executed,
            * it means an incorrect address was used and no exception got triggered.
            */
            DebugP_log("Something went wrong!\r\n");

        }
    }

    return;
}
