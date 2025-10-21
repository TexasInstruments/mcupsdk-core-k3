/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sigchain_gateway.h"

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

SemaphoreP_Object gSemExit;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SigchainGatewayMain_configureEVMCodec()
{
    int32_t status = SystemP_SUCCESS;
    I2C_Handle i2cHandle;
    uint8_t devAddr = 0x68;

    i2cHandle = gI2cHandle[CONFIG_I2C0];

    /* Configure clock generator for getting the external HCLK */
    status = Board_clockgenConfig(i2cHandle, devAddr);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Configure codec */
    status = configure_codec(); // Board_codecConfig();
    DebugP_assert(status == SystemP_SUCCESS);
}

void SigchainGateway_main(void *args)
{
    SigchainGatewayMain_configureEVMCodec();
    DebugP_log(" SigchainGateway_main: codec is configured \r\n");

    /* blocking: sync with remote core */
    SigchainGatewayIPC_syncRemote();

    DebugP_log(" SigchainGateway_main: remote core synchronized \r\n");

    SigchainGatewayIPC_init();

    /* initialization of UART interface for tuner communication */
    SigchainGatewayUART_init();

    SemaphoreP_constructBinary(&gSemExit, 0);

    /* wait for exit command from uart */
    SemaphoreP_pend(&gSemExit, SystemP_WAIT_FOREVER);

    DebugP_log(" SigchainGateway_main: exiting app now !! \r\n");
}
