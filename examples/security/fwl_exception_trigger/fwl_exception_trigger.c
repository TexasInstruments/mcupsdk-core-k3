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

#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <stdlib.h>

/*
 * This should be an addresses that would not be accessible
 * by the core running this example. Only when the stated
 * condition is ensured, will exceptions be triggered
 * and this example will be useful.
 */
/*
 * Accessing this address will trigger a CMBN firewall
 * exeption.
 */
#define CMBN_FWL_EXCEPTION_ADDR            (0x300000U)
/*
 * Accessing this address will trigger a SYSFW firewall
 * exception.
 */
#define SYSFW_FWL_EXCEPTION_ADDR            (0x44040000U)

void fwl_exception_trigger_main(void *args)
{
    uint32_t val, addr = 0U;
    char ch;

    /* Send entry string */
    DebugP_log("Enter \'D\' to trigger SYSFW firewall exception..\r\n");
    DebugP_log("Enter \'C\' to trigger CMBN firewall exception..\r\n");

    /* Wait for user to send a character over UART */
    DebugP_scanf("%c", &ch);

    if (ch == 'D')
    {
        /* Access the memory location to trigger SYSFW firewall exception */
        addr = (uint32_t)SYSFW_FWL_EXCEPTION_ADDR;
    }
    else if (ch == 'C')
    {
        /* Access the memory location to trigger CMBN firewall exception */
        addr = (uint32_t)CMBN_FWL_EXCEPTION_ADDR;
    }
    /* Access only when a valid character was sent! */
    val = (addr) ? (CSL_REG32_RD(AddrTranslateP_getLocalAddr(addr))) : 0U;
    (void) val;

    /*
     * If the address being accessed in the above statement is not firewalled against
     * access from the core executing this example, there would be no data abort and
     * the below code would get executed. If the following code gets executed,
     * it means an incorrect address was used and no exception got triggered.
    */
    DebugP_log("Something went wrong!\r\n");

    return;
}
