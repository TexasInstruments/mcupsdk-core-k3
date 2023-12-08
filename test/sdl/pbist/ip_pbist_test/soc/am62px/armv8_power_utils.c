/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     armv8_power_utils.c
 *
 *  \brief    This file defines functions to specifically handle
 *            proper power sequencing for the armv8 cores/cluster.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl/include/sdl_types.h>

#include <kernel/dpl/DebugP.h>
#include <drivers/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* This flag adds more verbose prints */
//#define DEBUG

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                            External Variables                              */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* The following steps in the armv8_powerDownSequence() function are needed
 * to ensure proper shutdown of the L2 system with ARMv8:
 * 1. Assert AINACTS first (to idle the ACP)
 * 2. Ensure system interrupts are disabled (N/A because this is boot sequence only)
 * 3. Assert L2FLUSHREQ, and then check L2FLUSH_DONE status flag has been asserted
 * 4. Deassert L2FLUSHREQ, and then check L2FLUSH_DONE status flag has been deasserted
 * 5. Assert ACINACTM (to idle the AXI master interface)
 * 6. Wait for STANDBY_WFI_L2 (STANDBYWFIL2) bit to be asserted
 */
int32_t armv8_powerDownSequence(uint8_t processorId)
{
    int32_t status = SDL_EFAIL;

#ifdef DEBUG
    DebugP_log("  Running custom powerdown sequence for ARMv8 core\n");
#endif

    /* Assert AINACTS first (to idle the ACP) - Set Bit 1 to 1 for asserting AINACTS */
    status = Sciclient_procBootSetSequenceCtrl(processorId, 0x00000002, 0x0, 0,
                                               SystemP_WAIT_FOREVER);
    if (status != SDL_PASS)
    {
        DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for AINACTS assert\n");
    }

    /* Assert L2FLUSHREQ - Set Bit 8 to 1 for asserting L2FLUSHREQ */
    if (status == SDL_PASS) {
        status = Sciclient_procBootSetSequenceCtrl(processorId, 0x00000100, 0x0, 0,
                                                   SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for " \
                        "L2FLUSHREQ assert/set\n");
        }
    }
    /* Check L2FLUSH_DONE has been asserted - Ensure that Bit 4 has been set to 1 */
    if (status == SDL_PASS) {

        status = Sciclient_procBootWaitProcessorState(processorId, 1, 1,
                                                      0x00000010, 0x0,
                                                      0x0, 0x0, 0,
                                                      SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootWaitProcessorState...FAILED for " \
                        "L2FLUSH_DONE set\n");
        }
    }
    /* Deassert L2FLUSHREQ - Clear Bit 8 to 0 for deasserting L2FLUSHREQ */
    if (status == SDL_PASS) {
        status = Sciclient_procBootSetSequenceCtrl(processorId, 0x0, 0x00000100, 0,
                                                   SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for " \
                        "L2FLUSHREQ deassert/clear\n");
        }
    }

    /* Check L2FLUSH_DONE has been deasserted - Ensure that Bit 4 has been cleared to 0 */
    if (status == SDL_PASS) {

        status = Sciclient_procBootWaitProcessorState(processorId, 1, 1,
                                                      0x0, 0x0,
                                                      0x00000010, 0x0, 0,
                                                      SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootWaitProcessorState...FAILED for " \
                        "L2FLUSH_DONE clear \n");
        }
    }
    /* Assert ACINACTM (to idle the AXI master interface) - Set Bit 0 to 1 for asserting ACINACTM */
    if (status == SDL_PASS) {
        status = Sciclient_procBootSetSequenceCtrl(processorId, 0x00000001, 0x0, 0,
                                                   SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for " \
                        "ACINACTM assert/set \n");
        }
    }

    return (status);
}

/* The following steps in the armv8_powerPrepareForPowerUpSequence() function are needed
 * to ensure the L2 system within ARMv8 is in a state where proper startup
 * can occur from SBL calls:
 * 1. Deassert L2FLUSHREQ.
 * 2. Deassert AINACTS (to enable the ACP)
 * 3. Deassert ACINACTM (to enable the AXI master interface)
 * This sequence should be run when the cluster is powered down
 * before any power up sequence.
 */
int32_t armv8_powerPrepareForPowerUpSequence(uint8_t processorId)
{
    int32_t status = SDL_EFAIL;

#ifdef DEBUG
    DebugP_log("  Running custom power restore sequence for ARMv8 core\n");
#endif

    /* Deassert L2FLUSHREQ - Clear Bit 8 to 0 for deasserting L2FLUSHREQ */
    if (status == SDL_PASS) {
        status = Sciclient_procBootSetSequenceCtrl(processorId, 0x0, 0x00000100, 0,
                                                   SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for " \
                        "L2FLUSHREQ deassert/clear\n");
        }
    }
    /* Deassert AINACTS  - Clear Bit 1 to 0 for deasserting AINACTS */
    status = Sciclient_procBootSetSequenceCtrl(processorId, 0x0, 0x00000002, 0,
                                               SystemP_WAIT_FOREVER);
    if (status != SDL_PASS)
    {
        DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for AINACTS " \
                    "deassert\n");
    }

    /* Deassert ACINACTM - Clear Bit 0 to 0 for deasserting ACINACTM */
    if (status == SDL_PASS) {
        status = Sciclient_procBootSetSequenceCtrl(processorId, 0x0, 0x00000001, 0,
                                                   SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("Sciclient_procBootSetSequenceCtrl...FAILED for " \
                        "ACINACTM deassert/clear \n");
        }
    }


    return (status);
}
