/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/DebugP.h>

/* Trace API prototypes */
extern void trace_reconfigure(uint16_t src_enables, uint16_t dst_enables);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief Test: DM Trace Configuration Test
 *
 * Tests sciserver, sciclient and IPC logs on DM R5.
 * These logs are based on board configuration.
 *
 * Test Steps:
 * 1. Configure trace with boardcfg: trace_dst_enables=0x01, trace_src_enables=0x10
 * 2. Print "Test: Success"
 * 3. Toggle boardcfg using trace_reconfigure to dst=0, src=0
 * 4. Print "Test: FAILED!!!"
 */
void test_main(void *args)
{
    /* Step 1: Configure trace with dst=0x01 (UART0), src=0x10 (USER) */
    trace_reconfigure(0x10, 0x01);

    /* Step 2: Print "Test: Success" */
    DebugP_log("Test: Success\r\n");

    /* Step 3: Toggle boardcfg using trace_reconfigure to dst=0, src=0 */
    trace_reconfigure(0, 0);

    /* Step 4: Print "Test: FAILED!!!" */
    DebugP_log("Test: FAILED!!!\r\n");

    return;
}
