/*
 * Copyright (c) 2013-2021, Texas Instruments Incorporated
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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include <c6x_migration.h>
#include <c7x.h>

#include <drivers/hw_include/csl_types.h>
#include "HwiP_c75.h"

/* Object__sizingError */
typedef char Hwi_Object__sizingError[(sizeof(Hwi_Object) > sizeof(HwiC7x_Struct)) ? -1 : 1];

#pragma FUNC_EXT_CALLED(Hwi_dispatchC);

extern void Hwi_dispatchAlways(void);
extern void Hwi_switchAndRunFunc(void (*func)());


extern char Hwi_vectorsBase[];
extern  char _stack[0x10001];

/*
 * ECSP stores an 8 KB context for each interrupt, up to a maximum of 8
 * nesting levels (1 per priority level).
 */
#define HWI_ECSP_SIZE (0x10000)

#if Hwi_bootToNonSecure__D
extern void Hwi_switchToNS();
#endif

extern const Hwi_Params Hwi_Object__PARAMS__C;
extern uint32_t ulPortInterruptNesting;

void Hwi_secureStart()
{
#if Hwi_bootToNonSecure__D
    /* Initialize the vector table pointer, ESTP */
    __ESTP_S = (unsigned long)Hwi_vectorTableBase;
   // __ESTP_SS = (unsigned long)Hwi_vectorTableBase_SS;

    __ECSP_S = (uint64_t)_stack;
    //__ECSP_SS = (uint64_t)_stack;
    __TCSP = (uint64_t)(_stack + HWI_ECSP_SIZE);

    /* start with a clean slate */
    __set_indexed(__EFCLR, 0, 0xFFFFFFFFFFFFFFFFUL);

    Hwi_switchToNS();
#endif
}

/*
 *  ======== Hwi_Module_startup ========
 */
void Hwi_Module_startup(void)
{
    int i;
    Hwi_Object *hwi;

    /* Task and Swi APIs used not called until BIOS_start() */
    /* okay to proceed with initialization */

    /* Initialize the vector table pointer, ESTP */
    __ESTP_S = (unsigned long)Hwi_vectorTableBase;

    if (Hwi_getCXM() == Hwi_TSR_CXM_SecureSupervisor) {
      //  __ESTP_SS = (unsigned long)Hwi_vectorTableBase_SS;
    }

    /*
     * Initialize the pointer to the isrStack. These symbols are part of the
     * Hwi_module (instead of floating) in order to support ROM.
     * Leave room for two 32-bit values pushed by xdc_runtime_Startup_reset()
     * (for cases where intentionally reset as resume from power down),
     * and maintain double word alignment.
     */
    Hwi_Module_state.isrStack = Hwi_getIsrStackAddress() - 16;
    __ECSP_S = (uint64_t)_stack;
    __TCSP = (uint64_t)(_stack + HWI_ECSP_SIZE);

    if (Hwi_getCXM() == Hwi_TSR_CXM_SecureSupervisor) {
       // __ECSP_SS = (uint64_t)_stack;
    }

    /* signal that we're executing on the ISR stack */
    Hwi_Module_state.taskSP = (char *)-1;

    /* initialize event mapping */
    for (i = 0; i < Hwi_NUM_INTERRUPTS; i++) {
        if (Hwi_Module_state.intEvents[i] != -1) {
            Hwi_eventMap(i, Hwi_Module_state.intEvents[i]);
        }
        else {
            /* keep intEvents[] current for ROV */
            Hwi_Module_state.intEvents[i] = Hwi_getEventId(i);
        }
    }

    /* start with a clean slate */
    __set_indexed(__EFCLR, 0, 0xFFFFFFFFFFFFFFFFUL);

    Hwi_enableIER(Hwi_Module_state.ierMask); /* IER per static Hwi settings */

    for (i = 0; i < Hwi_NUM_INTERRUPTS; i++) {
        hwi = Hwi_Module_state.dispatchTable[i];
        if (hwi !=  NULL) {
            Hwi_postInit(hwi);
        }
    }

    Hwi_setCOP(0xff);

    return;
}

/*
 *  ======== Hwi_Instance_init ========
 */
int Hwi_Instance_init(Hwi_Object *hwi, int intNum,
                      Hwi_FuncPtr fxn, const Hwi_Params *params)
{
    int status;

    /* there are 64 "interrupt" events in C7x */
    if (intNum < 0 || intNum > 63) {
        return (1);
    }

    if (Hwi_Module_state.dispatchTable[intNum] != NULL) {
        return (1);
    }

    Hwi_Module_state.dispatchTable[intNum] = hwi;

// There is no vector table on C7x.  Instead, all interrupts vector to
// ESTP + 0x800, where a dispatcher needs to look at AHPEE for interrupt
// number in service and call the configured ISR.
//    Hwi_plug(intNum, Hwi_dispatchAlways);

    Hwi_reconfig(hwi, fxn, params);
    hwi->intNum = intNum;

    hwi->irp = 0;

    status = Hwi_postInit(hwi);

    if (status != 0) {
        return (3 + status);
    }

    return (0);
}

/*
 *  ======== Hwi_postInit ========
 *  Function to be called during module startup to complete the
 *  initialization of any statically created or constructed Hwi.
 *  returns (0) and clean 'eb' on success
 *  returns 'eb' *and* 'n' for number of successful createFxn() calls iff
 *      one of the createFxn() calls fails
 */
int Hwi_postInit (Hwi_Object *hwi)
{

    if (hwi->priority < 1 || hwi->priority > 7) {

        hwi->priority = Hwi_DEFAULT_INT_PRIORITY;
    }

    Hwi_setPriority(hwi->intNum, hwi->priority);

    return (0);
}

/*
 *  ======== Hwi_Instance_finalize ========
 *  Here on Hwi_delete() or failed Hwi_create().
 */
void Hwi_Instance_finalize(uint32_t intNum, int status)
{

    if (status == 1) {  /* failed early in Hwi_Instance_init() */
        return;
    }

    HwiP_disableInt(intNum);
    Hwi_Module_state.dispatchTable[intNum] = NULL;

    if (status == 2) {  /* failed mid-way into Hwi_Instance_init() */
        return;
    }

}

/*
 *  ======== Hwi_unPluggedInterrupt ========
 *  Here on interrupt unPlugged by Hwi_delete().
 */
void Hwi_unPluggedInterrupt() {
    while(true);
}

/*
 *  ======== Hwi_eventMap ========
 *  Function maps an event to a Hwi vector so that the event will be the
 *  source of the interrupt of the vector.
 */
void Hwi_eventMap(int vectId, int eventId)
{
    unsigned int mask;          /* Interrupt mask value */

    if (vectId < 0 || vectId > 63) {
        return;
    }

    mask = Hwi_disable();

    /* Program CLEC to map external eventId to internal interrupt (event) */

    /* clear any residual interrupt */
    __set_indexed(__EFCLR, 0, 1L << vectId);

    Hwi_restore(mask);
}

/*
 *  ======== Hwi_getEventId ========
 */
int Hwi_getEventId(unsigned int vectId)
{
    if (vectId > 63) {
        return -1;
    }

    /* TODO */

    return 0;
}

/*
 * Below APIs provided for backward compatability.
 */

/*
 *  ======== Hwi_disableIER ========
 */
unsigned long Hwi_disableIER(unsigned long mask)
{
    unsigned int key;
    unsigned long oldEER;

    key = Hwi_disable();
    oldEER = __get_indexed(__EER, 0);
    __set_indexed(__EECLR, 0, mask);
    Hwi_restore(key);

    return oldEER;
}

/*
 *  ======== Hwi_enableIER ========
 */
unsigned long Hwi_enableIER(unsigned long mask)
{
    unsigned int key;
    unsigned long oldEER;

    key = Hwi_disable();
    oldEER = __get_indexed(__EER, 0);
    __set_indexed(__EESET, 0, mask);
    Hwi_restore(key);

    return oldEER;
}

/*
 *  ======== Hwi_restoreIER ========
 */
unsigned long Hwi_restoreIER(unsigned long mask)
{
    unsigned int key;
    unsigned long oldEER;

    key = Hwi_disable();
    oldEER = __get_indexed(__EER, 0);
    __set_indexed(__EESET, 0, mask);
    Hwi_restore(key);

    return oldEER;
}

/*
 *  ======== Hwi_setPriority ========
 */
void Hwi_setPriority(unsigned int intNum, unsigned int priority)
{
    DebugP_assert(priority >= 1U && priority <= 7U);

    if (Hwi_getCXM() != Hwi_TSR_CXM_SecureSupervisor) {
        return;
    }

    __set_indexed(__EPRI, intNum, priority << 5);
}


#include <FreeRTOS.h>
#include <task.h>

uintptr_t HwiP_disable(void)
{
    uintptr_t key = (uintptr_t)NULL_PTR;

    if(( xPortInIsrContext() ) ||
       ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ))
    {
        key = Hwi_disable();
    }
    else
    {
        portENTER_CRITICAL();
    }

    return (key);
}

void HwiP_restore(uintptr_t key)
{
    if(( xPortInIsrContext() ) ||
       ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ))
    {
        (void)Hwi_restore((uint32_t)key);
    }
    else
    {
        portEXIT_CRITICAL();
    }

    return;
}

void HwiP_post(uint32_t intrNum)
{

    __set_indexed(__EFSET, 0, 1L << intrNum);

    return;

    /* Please note that in future,for targets which do not support Hwi_Post,
       add #ifdefs appropriately to return osal_UNSUPPORTED */
}

uint32_t HwiP_disableInt(uint32_t intNum)
{
    unsigned long mask = 1L << intNum;

    /* Hwi_disableIER() returns old EER */
    return ((Hwi_disableIER(mask) & mask) != 0L);
}

void HwiP_enableInt(uint32_t intNum)
{
    unsigned long mask = 1L << intNum;

    Hwi_enableIER(mask);

    return;
}


void HwiP_restoreInt(uint32_t intNum, uint32_t key)
{
    if (key) {
        HwiP_enableInt(intNum);
    }
    else {
        HwiP_disableInt(intNum);
    }
}

void HwiP_clearInt(uint32_t intNum)
{
    __set_indexed(__EFCLR, 0, 1L << intNum);
}

/*
 *  ======== Hwi_reconfig ========
 *  Reconfigure a dispatched interrupt.
 */
void Hwi_reconfig(Hwi_Object *hwi, Hwi_FuncPtr fxn, const Hwi_Params *params)
{
    unsigned int intNum;

    for (intNum = 0; intNum < Hwi_NUM_INTERRUPTS; intNum++) {
        if (Hwi_Module_state.dispatchTable[intNum] == hwi) {
            break;
        }
    }

    if (intNum == Hwi_NUM_INTERRUPTS) {
        return;
    }


    HwiP_disableInt(intNum);

    hwi->fxn = fxn;
    hwi->arg = params->arg;

    if (params->priority == -1) {
        hwi->priority = Hwi_DEFAULT_INT_PRIORITY;
    }
    else {
        hwi->priority = params->priority;
    }

    switch (params->maskSetting) {
        case Hwi_MaskingOption_NONE:
            hwi->disableMask = 0;
            hwi->restoreMask = 0;
            break;
        case Hwi_MaskingOption_ALL:
            hwi->disableMask = 0xFFFFFFFFFFFFFFFFUL;
            hwi->restoreMask = 0xFFFFFFFFFFFFFFFFUL;
            break;
        default:
        case Hwi_MaskingOption_SELF:
            hwi->disableMask = 1L << intNum;
            hwi->restoreMask = 1L << intNum;
            break;
        case Hwi_MaskingOption_BITMASK:
            hwi->disableMask = params->disableMask;
            hwi->restoreMask = params->restoreMask;
            break;
    }

    if (params->eventId != -1) {
        Hwi_eventMap(intNum, params->eventId);
    }

    /* keep intEvents[] current for ROV */
    Hwi_Module_state.intEvents[intNum] = Hwi_getEventId(intNum);

    if (params->enableInt) {
        HwiP_enableInt(intNum);
    }
}

/*
 *  ======== switchFromBootStack ========
 *  Indicate that we are leaving the boot stack and
 *  are about to switch to a task stack.
 */
void Hwi_switchFromBootStack()
{
    Hwi_Module_state.taskSP = 0;
}

/*
 *  ======== Hwi_getIsrStackAddress ========
 */
char *Hwi_getIsrStackAddress()
{
    extern uint8_t __TI_STACK_SIZE;
    uint64_t isrStack;

    isrStack = (uint64_t)_stack;
    isrStack += (uint64_t)_symval(&__TI_STACK_SIZE);
    isrStack -= 0x1;

    isrStack &= ~0x7;   /* align to long word */

    return ((char *)isrStack);
}

/*
 *  ======== Hwi_getStackInfo ========
 *  Used to get Hwi stack usage info.
 */
bool Hwi_getStackInfo(Hwi_StackInfo *stkInfo, bool computeStackDepth)
{
    extern  uint8_t __TI_STACK_SIZE;

    char *isrSP;
    bool stackOverflow;

    /*
     * Copy the stack base address and size.
     *
     * Adjust for HW ECSP/TCSP portions.  TCSP only temporarily occupies
     * 0x2000 bytes of stack starting at _stack + HWI_ECSP_SIZE, until
     * the first Task switch.
     */
    stkInfo->hwiStackSize = (size_t)_symval(&__TI_STACK_SIZE) -
                            (HWI_ECSP_SIZE + 0x2000);
    stkInfo->hwiStackBase = _stack + HWI_ECSP_SIZE + 0x2000;

    isrSP = stkInfo->hwiStackBase;

    /* Check for stack overflow */
    stackOverflow = (*isrSP != (char)0xbe ? true : false);

    if (computeStackDepth && !stackOverflow) {
        /* Compute stack depth */
        do {
        } while(*isrSP++ == (char)0xbe);
        stkInfo->hwiStackPeak = stkInfo->hwiStackSize - (size_t)(--isrSP - (char *)stkInfo->hwiStackBase);
    }
    else {
        stkInfo->hwiStackPeak = 0;
    }

    return stackOverflow;
}

/*
 *  ======== Hwi_getCoreStackInfo ========
 *  Used to get Hwi stack usage info.
 */
bool Hwi_getCoreStackInfo(Hwi_StackInfo *stkInfo, bool computeStackDepth,
    unsigned int coreId)
{
    return (Hwi_getStackInfo(stkInfo, computeStackDepth));
}

/*
 *  ======== Hwi_dispatchCore ========
 *  Configurable dispatcher.
 */
void Hwi_dispatchCore(int intNum)
{
    /*
     * Enough room is reserved above the isr stack to handle
     * as many as 16 32-bit stack resident local variables.
     * If the dispatcher requires more than this, you must
     * handle this in Hwi_Module_startup().
     */

    Hwi_Object *hwi;
    Hwi_FuncPtr fxn;
    unsigned int arg;

    /* save away intNum in module state because it might be saved on stack */
    Hwi_Module_state.intNum = intNum;

    /*
     * pre-read local copies of the variables used
     * within to eliminate memory fetch nops
     */
    hwi = Hwi_Module_state.dispatchTable[intNum];
    fxn = hwi->fxn;
    arg = hwi->arg;

    if (Hwi_dispatcherIrpTrackingSupport) {
        uint64_t *contextStack;
        unsigned int ncnt;

        /*
         * There is no IRP register on C7x.  The interrupt return pointer
         * is stored on the "Context Stack" at offset 0.  The context stack
         * is pointed to by:
         *     - TCSP if interrupt occurred while CPU in "Thread Mode"
         *     - ECSP[n] if interrupt occurred while in "Event Handler Mode"
         *       where n is the interrupt nesting count minus one (i.e., first
         *       nested interrupt uses ECSP[0] since the original non-nested
         *       interrupt was saved on TCSP)
         * If ncnt (ECSP nesting count, bits 15-13) is 0 then TCSP must be the
         * one because ncnt would be > 0 if an interrupt's context had already
         * been stored on it.
         */
        ncnt = (__ECSP_S & 0xe000) >> 13;
        if (ncnt) {
            contextStack = (uint64_t *)(((uint64_t)__ECSP_S) +
                                      ((ncnt - 1) * 0x2000));
        }
        else  {
            contextStack = (uint64_t *)__TCSP;
        }

        hwi->irp = contextStack[0];
    }

    if ( fxn != NULL)
        (fxn)(arg);
    
    Hwi_setCOP(0xff);

}

/* construct */
int Hwi_construct(HwiC7x_Struct *objp, int intNum, Hwi_FuncPtr hwiFxn, const Hwi_Params *paramsPtr)
{
    int iStat;

    /* common instance initialization */
    memset(objp, 0, sizeof(*objp));

    /* module-specific initialization */
    iStat = Hwi_Instance_init((void *)objp, intNum, hwiFxn, paramsPtr);
    
    return iStat;
}

/* destruct */
void Hwi_destruct(uint32_t intNum)
{
    Hwi_Instance_finalize(intNum, 0);
}

/* Params__init__S */
void Hwi_Params__init__S( Hwi_Params *prms)
{
    memcpy(prms, &Hwi_Object__PARAMS__C, sizeof(*prms));
}


void Hwi_Params_init( Hwi_Params *prms )
{
    if (prms != NULL) {
        Hwi_Params__init__S(prms);
    }
}

uint32_t HwiP_inISR(void)
{
    uint32_t stat = 0U;

    if (ulPortInterruptNesting != 0)
    {
        stat =  1U;
    }
    return stat;
}

void HwiP_init(void)
{
    return;
}

void HwiP_enable()
{

}

#include <FreeRTOS.h>
#include "portmacro.h"
/*
 *  ======== Hwi_dispatchC ========
 *  Configurable dispatcher.
 */
void Hwi_dispatchC(int intNum)
{
    extern uint32_t ulPortInterruptNesting;
    extern uint32_t ulPortYieldRequired;

    ulPortInterruptNesting++;

    Hwi_switchAndDispatch(intNum);

    ulPortInterruptNesting--;
    if (ulPortInterruptNesting == 0)
    {
        if (ulPortYieldRequired != pdFALSE)
        {
            ulPortYieldRequired = pdFALSE;
            vPortYieldAsyncFromISR();
        }

    }

}

/* bootToNonSecure */
#pragma DATA_SECTION(Hwi_bootToNonSecure, ".const:Hwi_bootToNonSecure");
const bool Hwi_bootToNonSecure = 1;

/* enableException */
#pragma DATA_SECTION(Hwi_enableException, ".const:Hwi_enableException");
const bool Hwi_enableException = 1;

/* dispatcherIrpTrackingSupport */
#pragma DATA_SECTION(Hwi_dispatcherIrpTrackingSupport, ".const:Hwi_dispatcherIrpTrackingSupport");
const bool Hwi_dispatcherIrpTrackingSupport = 1;

/* --> soft_reset */
extern void* soft_reset;

/* --> secure_soft_reset */
extern void* secure_soft_reset;

/* Object__PARAMS__C */
#pragma DATA_SECTION(Hwi_Object__PARAMS__C, ".const:Hwi_Object__PARAMS__C");
const Hwi_Params Hwi_Object__PARAMS__C = {
    Hwi_MaskingOption_SELF,  /* maskSetting */
    ((unsigned int)(0x0)),  /* arg */
    1,  /* enableInt */
    (int)(-0x0 - 1),  /* eventId */
    (int)(-0x0 - 1),  /* priority */
    (unsigned long)0x0UL,  /* disableMask */
    (unsigned long)0x0UL,  /* restoreMask */
};


/* Module__state__V */
#ifdef __ti__
struct Hwi_Module_State Hwi_Module_state __attribute__ ((section(".data:Hwi_Module_state")));
#elif !(defined(__MACH__) && defined(__APPLE__))
struct Hwi_Module_State Hwi_Module_state __attribute__ ((section(".data:Hwi_Module_state")));
#endif
struct Hwi_Module_State Hwi_Module_state = {
    {
        (char)(-0x0 - 1),  /* [0] */
        (char)(-0x0 - 1),  /* [1] */
        (char)(-0x0 - 1),  /* [2] */
        (char)(-0x0 - 1),  /* [3] */
        (char)(-0x0 - 1),  /* [4] */
        (char)(-0x0 - 1),  /* [5] */
        (char)(-0x0 - 1),  /* [6] */
        (char)(-0x0 - 1),  /* [7] */
        (char)(-0x0 - 1),  /* [8] */
        (char)(-0x0 - 1),  /* [9] */
        (char)(-0x0 - 1),  /* [10] */
        (char)(-0x0 - 1),  /* [11] */
        (char)(-0x0 - 1),  /* [12] */
        (char)(-0x0 - 1),  /* [13] */
        (char)0x4e0,  /* [14] */
        (char)(-0x0 - 1),  /* [15] */
        (char)(-0x0 - 1),  /* [16] */
        (char)(-0x0 - 1),  /* [17] */
        (char)(-0x0 - 1),  /* [18] */
        (char)(-0x0 - 1),  /* [19] */
        (char)(-0x0 - 1),  /* [20] */
        (char)(-0x0 - 1),  /* [21] */
        (char)(-0x0 - 1),  /* [22] */
        (char)(-0x0 - 1),  /* [23] */
        (char)(-0x0 - 1),  /* [24] */
        (char)(-0x0 - 1),  /* [25] */
        (char)(-0x0 - 1),  /* [26] */
        (char)(-0x0 - 1),  /* [27] */
        (char)(-0x0 - 1),  /* [28] */
        (char)(-0x0 - 1),  /* [29] */
        (char)(-0x0 - 1),  /* [30] */
        (char)(-0x0 - 1),  /* [31] */
        (char)(-0x0 - 1),  /* [32] */
        (char)(-0x0 - 1),  /* [33] */
        (char)(-0x0 - 1),  /* [34] */
        (char)(-0x0 - 1),  /* [35] */
        (char)(-0x0 - 1),  /* [36] */
        (char)(-0x0 - 1),  /* [37] */
        (char)(-0x0 - 1),  /* [38] */
        (char)(-0x0 - 1),  /* [39] */
        (char)(-0x0 - 1),  /* [40] */
        (char)(-0x0 - 1),  /* [41] */
        (char)(-0x0 - 1),  /* [42] */
        (char)(-0x0 - 1),  /* [43] */
        (char)(-0x0 - 1),  /* [44] */
        (char)(-0x0 - 1),  /* [45] */
        (char)(-0x0 - 1),  /* [46] */
        (char)(-0x0 - 1),  /* [47] */
        (char)(-0x0 - 1),  /* [48] */
        (char)(-0x0 - 1),  /* [49] */
        (char)(-0x0 - 1),  /* [50] */
        (char)(-0x0 - 1),  /* [51] */
        (char)(-0x0 - 1),  /* [52] */
        (char)(-0x0 - 1),  /* [53] */
        (char)(-0x0 - 1),  /* [54] */
        (char)(-0x0 - 1),  /* [55] */
        (char)(-0x0 - 1),  /* [56] */
        (char)(-0x0 - 1),  /* [57] */
        (char)(-0x0 - 1),  /* [58] */
        (char)(-0x0 - 1),  /* [59] */
        (char)(-0x0 - 1),  /* [60] */
        (char)(-0x0 - 1),  /* [61] */
        (char)(-0x0 - 1),  /* [62] */
        (char)(-0x0 - 1),  /* [63] */
    },  /* intEvents */
    (unsigned long)0x4003UL,  /* ierMask */
    (int)0x0,  /* intNum */
    ((char*)NULL),  /* taskSP */
    ((char*)NULL),  /* isrStack */
    (int)0x0,  /* scw */
    {
        0,  /* [0] */
        0,  /* [1] */
        0,  /* [2] */
        0,  /* [3] */
        0,  /* [4] */
        0,  /* [5] */
        0,  /* [6] */
        0,  /* [7] */
        0,  /* [8] */
        0,  /* [9] */
        0,  /* [10] */
        0,  /* [11] */
        0,  /* [12] */
        0,  /* [13] */
        0,  /* [14] */
        0,  /* [15] */
        0,  /* [16] */
        0,  /* [17] */
        0,  /* [18] */
        0,  /* [19] */
        0,  /* [20] */
        0,  /* [21] */
        0,  /* [22] */
        0,  /* [23] */
        0,  /* [24] */
        0,  /* [25] */
        0,  /* [26] */
        0,  /* [27] */
        0,  /* [28] */
        0,  /* [29] */
        0,  /* [30] */
        0,  /* [31] */
        0,  /* [32] */
        0,  /* [33] */
        0,  /* [34] */
        0,  /* [35] */
        0,  /* [36] */
        0,  /* [37] */
        0,  /* [38] */
        0,  /* [39] */
        0,  /* [40] */
        0,  /* [41] */
        0,  /* [42] */
        0,  /* [43] */
        0,  /* [44] */
        0,  /* [45] */
        0,  /* [46] */
        0,  /* [47] */
        0,  /* [48] */
        0,  /* [49] */
        0,  /* [50] */
        0,  /* [51] */
        0,  /* [52] */
        0,  /* [53] */
        0,  /* [54] */
        0,  /* [55] */
        0,  /* [56] */
        0,  /* [57] */
        0,  /* [58] */
        0,  /* [59] */
        0,  /* [60] */
        0,  /* [61] */
        0,  /* [62] */
        0,  /* [63] */
    },  /* dispatchTable */
};

/* vectorTableBase__C */
#pragma DATA_SECTION(Hwi_vectorTableBase, ".const:Hwi_vectorTableBase");
const void * Hwi_vectorTableBase = ((const void *)((void*)&soft_reset));

/* vectorTableBase_SS__C */
#pragma DATA_SECTION(Hwi_vectorTableBase_SS, ".const:Hwi_vectorTableBase_SS");
const void * Hwi_vectorTableBase_SS = ((const void *)((void*)&secure_soft_reset));

