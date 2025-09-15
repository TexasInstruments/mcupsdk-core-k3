/*
 * Copyright (c) 2015-2025, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This is a copy of TaskSupport.c adapted for ThreadX. Note
 * that to keep maximum compatibility with the nortos port and the C7x SDK
 * as a whole some objects use the same names as the FreeRTOS port.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include <tx_api.h>

#include "TaskSupport_threadx_c75.h"

#include <kernel/dpl/DebugP.h>


#include <stdint.h>

#define portBYTE_ALIGNMENT 8U

#define TCSP_SIZE  0x2000
#define TCSP_ALIGN 0x2000


void * TaskSupport_setupTaskStack(VOID * pxStackArrayEndAddress, VOID * pxStackArrayStartAddress, VOID (*fxn)(VOID), VOID (*exit)(VOID), VOID (*enter)(VOID), bool privileged)
{
    void * sp;
    void * tcspBase;
    uint32_t tskStackSize = (uintptr_t)pxStackArrayEndAddress - (uintptr_t)pxStackArrayStartAddress;
    uint32_t align;
    VOID * pxStackArrayStartAddressAligned;

    align = TaskSupport_getStackAlignment();

    if (align != 0U) {
        uintptr_t stackTemp;

        DebugP_assert(align >= portBYTE_ALIGNMENT);
        /* align low address to stackAlignment */
        /* MISRA.CAST.VOID_PTR_TO_INT.2012 */
        stackTemp = (uintptr_t)pxStackArrayStartAddress;
        stackTemp = stackTemp + (align - 1U);
        stackTemp = stackTemp & ~(align - 1U);
        pxStackArrayStartAddressAligned = (VOID *)(stackTemp);

        /* subtract what we removed from the low address from stackSize */
        /* MISRA.CAST.VOID_PTR_TO_INT.2012 */
        tskStackSize = tskStackSize - ((uintptr_t)pxStackArrayStartAddressAligned - (uintptr_t)pxStackArrayStartAddress);

        /* lower the high address as necessary */
        tskStackSize = tskStackSize & (size_t)~(align - 1U);
    }
    else
    {
        pxStackArrayStartAddressAligned = pxStackArrayStartAddress;
    }

    DebugP_assert(tskStackSize >= TaskSupport_defaultStackSize);

    if (tskStackSize < TaskSupport_defaultStackSize) {
        return (NULL);
    }

    tcspBase = (void *)(((uintptr_t)pxStackArrayStartAddressAligned + tskStackSize) - TCSP_SIZE);
    if (align)
    {
        DebugP_assert(((uintptr_t)tcspBase & (align - 1U)) == 0U);
    }
    /* subtract 16 from size to account for 16-byte free area @SP */
    sp = TaskSupport_buildTaskStack((void *)((size_t)tcspBase - 16),
                                    fxn,
                                    exit,
                                    enter,
                                    NULL,
                                    NULL,
                                    tcspBase,
                                    privileged);

    return (sp);
}

/*
 *  ======== TaskSupport_getStackAlignment ========
 */
unsigned int TaskSupport_getStackAlignment()
{
    return (TaskSupport_stackAlignment);
}

#pragma DATA_SECTION(TaskSupport_defaultStackSize, ".const:TaskSupport_defaultStackSize");
const size_t TaskSupport_defaultStackSize = (size_t)(16 * 1024);


/* stackAlignment__C */
#pragma DATA_SECTION(TaskSupport_stackAlignment, ".const:TaskSupport_stackAlignment");
const unsigned int TaskSupport_stackAlignment = (unsigned int)0x2000U;

#pragma DATA_SECTION(OS_mpeEnabled, ".const:OS_mpeEnabled");
const uint32_t OS_mpeEnabled = 0;


void Task_exit()
{
    /* This should never be reached on ThreadX. */
    for(;;) {}
}
