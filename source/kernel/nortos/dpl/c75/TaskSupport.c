/*
 * Copyright (c) 2015-2021, Texas Instruments Incorporated
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
 *  ======== TaskSupport.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include "TaskSupport_c75.h"

#include <kernel/dpl/DebugP.h>




/*
 *
 * Here is a pseudo image of the initial C6x task stack:
 *
 *  saved-by-callee registers
 *  Task enter()
 *  Task glue()
 *  arg0
 *  arg1
 *  User's task func()
 *  Task_exit()
 *
 * The initial stack consists of the registers that are preserved by a
 * called C function as defined by the C compiler. These are the registers
 * pushed and popped by TaskSupport_swap.
 *
 * Below (or above, depending on your view of the stack) those registers
 * are the Task enter() function which sets up the first invocation of the
 * task in the same manner as if it had been "returned" to from Task_restore()
 * which is the normal path back to an unblocked task.
 *
 * Below the Task enter() function address on the initial task stack is the
 * address of the Glue function. This address is popped by the return from
 * Task enter(). Glue pops the 2 UArgs below it on the stack into the
 * appropriate registers for a fxn(arg0, arg1) call, and then "returns"
 * into the user's task function, which is the next to last address on
 * the stack.
 *
 * Below the Task's function address on the stack is the Task_exit()
 * function address which is returned into if the task function falls
 * out the bottom.
 *
 * The TaskSupport_swap() function pushes all the saved-by-callee
 * registers onto the task stack, then saves the updated SP into
 * the "old" task object's context (SP) address passed to it. Then it
 * loads the "new" task object's context (SP) (the second arg passed
 * to swap) into the SP, unrolls the saved registers and returns into
 * the new task.
 *
 * The pointer returned by the buildTaskStack function is the task's initial
 * stack pointer. This address is stored into the task object's context
 * field and is passed to the TaskSupport_swap() function later.
 *
 */

#define TCSP_SIZE  0x2000
#define TCSP_ALIGN 0x2000


void * TaskSupport_setupTaskStack(StackType_t * pxStackArrayEndAddress, StackType_t * pxStackArrayStartAddress, Task_FuncPtr fxn, TaskSupport_FuncPtr exit, TaskSupport_FuncPtr enter, TaskFunction_t pxCode, void * pvParameters , bool privileged)
{
    void * sp;
    void * tcspBase;
    uint32_t tskStackSize = (uintptr_t)pxStackArrayEndAddress - (uintptr_t)pxStackArrayStartAddress;
    uint32_t align;
    StackType_t * pxStackArrayStartAddressAligned;

    align = TaskSupport_getStackAlignment();

    if (align != 0U) {
        uintptr_t stackTemp;

        DebugP_assert(align >= portBYTE_ALIGNMENT);
        /* align low address to stackAlignment */
        /* MISRA.CAST.VOID_PTR_TO_INT.2012 */
        stackTemp = (uintptr_t)pxStackArrayStartAddress;
        stackTemp = stackTemp + (align - 1U);
        stackTemp = stackTemp & ~(align - 1U);
        pxStackArrayStartAddressAligned = (StackType_t *)(stackTemp);

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
    sp = TaskSupport_buildTaskStack((void *)((size_t)tcspBase - 16), fxn,
                                    exit, enter, pvParameters, pxCode,
                                    tcspBase, privileged);

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
