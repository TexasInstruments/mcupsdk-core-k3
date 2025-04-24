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

#include <kernel/dpl/HwiP.h>

#define TEXT_HWI    __attribute__((section(".text.hwi")))
#define WEAK        __attribute__((weak))
#ifdef __cplusplus
extern "C" {
#endif
/** Following handlers starts in assembly and switch to C implementation. 
 * Hence DON'T use interrupt attribute. Else it will result in re-entry */ 
void TEXT_HWI HwiP_undefined_handler_c(volatile uint32_t LR);
void TEXT_HWI HwiP_prefetch_abort_handler_c(volatile uint32_t LR);
void TEXT_HWI HwiP_data_abort_handler_c(volatile uint32_t LR);
/* Use weak attribute with user handler so that applications can override with its own implementation */
void TEXT_HWI WEAK HwiP_user_data_abort_handler_c(DFSR dfsr, ADFSR adfsr, volatile uint32_t DFAR, 
                                                  volatile uint32_t LR,volatile uint32_t SPSR);
void TEXT_HWI WEAK HwiP_user_prefetch_abort_handler_c(IFSR ifsr, AIFSR aifsr, volatile uint32_t IFAR, 
                                                      volatile uint32_t LR,volatile uint32_t SPSR);
void TEXT_HWI WEAK HwiP_user_undefined_handler_c(volatile uint32_t LR,volatile uint32_t SPSR);

volatile uint32_t GET_DFSR(void);
volatile uint32_t GET_ADFSR(void);
volatile uint32_t GET_DFAR(void);
volatile uint32_t GET_IFSR(void);
volatile uint32_t GET_AIFSR(void);
volatile uint32_t GET_IFAR(void);
volatile uint32_t GET_SPSR(void);
volatile uint32_t GET_LR(void);
#ifdef __cplusplus
}
#endif

/* Undefined handler starts execution in HwiP_undefined_handler, defined in
 * HwiP_armv7r_exception_handlers_nortos_asm.S
 * After some initial assembly logic it then branches to this function.
 * After exiting this function it does some more assembly before exiting
 */
void TEXT_HWI HwiP_undefined_handler_c(volatile uint32_t LR)
{
    typedef struct {
        volatile uint32_t SPSR;
        /* DFSR register */
        volatile uint32_t LR;
        /* Instruction causing the exception*/
    }UNDEF_REG;

    UNDEF_REG abort_regs;
    abort_regs.SPSR = GET_SPSR();
    abort_regs.LR   = LR;

    HwiP_user_undefined_handler_c(abort_regs.LR, abort_regs.SPSR);
}

/* Prefetch abort handler starts execution in HwiP_prefetch_abort_handler, defined in
 * HwiP_armv7r_exception_handlers_nortos_asm.S
 * After some initial assembly logic it then branches to this function.
 * After exiting this function it does some more assembly before exiting
 */
void TEXT_HWI HwiP_prefetch_abort_handler_c(volatile uint32_t LR)
{
    typedef struct {
        volatile uint32_t IFSR;
        /* IFSR register */
        volatile uint32_t AIFSR;
        /* AIFSR register */
        volatile uint32_t IFAR;
        /* IFAR register */
        volatile uint32_t LR;
        /* Instruction causing the exception*/
        volatile uint32_t SPSR;
        /* SPSR register*/
    }PREFETCH_ABORT_REG;

    PREFETCH_ABORT_REG abort_regs;

    /*Extract register values through functions coded in ASM*/
    abort_regs.AIFSR = GET_AIFSR();
    abort_regs.IFAR  = GET_IFAR();
    abort_regs.IFSR  = GET_IFSR();
    abort_regs.LR    = LR;
    abort_regs.SPSR  = GET_SPSR();

    /*Extract contents of IFSR register
    1. status: indicates the type of fault generated
    2. sd: distinguishes between an AXI Decode or Slave error on an external abort.
    This bit is only valid for external aborts. For all other aborts types of abort,
    this bit is set to zero*/
    IFSR     ifsr;
    uint32_t ifsr_value = abort_regs.IFSR;

    ifsr.status = ((ifsr_value & 0xFU) | (((ifsr_value >> 10U) & 0x1U) << 4U));
    ifsr.sd     = ((ifsr_value >> 12U) & 0x1U);

    /*Extract contents of AIFSR register
    1. index: returns the index value for the access giving the error
    2. side_ext: value returned in this field indicates the source of the error
    3. recoverable_error:  value returned in this field indicates if the error is recoverable
        (0=Unrecoverable error, 1=Recoverable Error)
    4. cacheway: value returned in this field indicates the cache way or ways in which the error occurred*/
    AIFSR    aifsr;
    uint32_t aifsr_value = abort_regs.AIFSR;

    aifsr.index             = ((aifsr_value >> 5U) & 0x1FFU);
    aifsr.side_ext          = (((aifsr_value >> 22U) & 0x3U) | (((aifsr_value >> 20U) & 0x1U) << 2U));
    aifsr.recoverable_error = ((aifsr_value >> 21U) & 0x1U);
    aifsr.cacheway          = ((aifsr_value >> 24U) & 0xFU);

    HwiP_user_prefetch_abort_handler_c(ifsr, aifsr, abort_regs.IFAR, abort_regs.LR, abort_regs.SPSR);
}

/* Data abort handler starts execution in HwiP_data_abort_handler, defined in
 * HwiP_armv7r_exception_handlers_nortos_asm.S
 * After some initial assembly logic it then branches to this function.
 * After exiting this function it does some more assembly before exiting
 */
void TEXT_HWI HwiP_data_abort_handler_c(volatile uint32_t LR)
{
     typedef struct {
        volatile uint32_t DFSR;
        /* DFSR register */
        volatile uint32_t ADFSR;
        /* ADFSR register */
        volatile uint32_t DFAR;
        /* DFAR register */
        volatile uint32_t LR;
        /* Instruction causing the exception*/
        volatile uint32_t SPSR;
        /* SPSR register*/
    }DATA_ABORT_REG;

    /*Extract register values through functions coded in ASM*/
    DATA_ABORT_REG abort_regs;
    abort_regs.ADFSR = GET_ADFSR();
    abort_regs.DFAR  = GET_DFAR();
    abort_regs.DFSR  = GET_DFSR();
    abort_regs.LR    = LR;
    abort_regs.SPSR  = GET_SPSR();

    /*Extract contents of DFSR register
    1. status: indicates the type of fault generated
    2. sd: distinguishes between an AXI Decode or Slave error on an external abort.
    This bit is only valid for external aborts. For all other aborts types of abort,
    this bit is set to zero
    3. rw:  Indicates whether a read or write access caused an abort
        (0=read abort; 1=write abort)*/
    DFSR dfsr;
    uint32_t dfsr_value = abort_regs.DFSR;

    dfsr.status = ((dfsr_value & 0xFU) | (((dfsr_value >> 10U) & 0x1U) << 4U));
    dfsr.rw     = ((dfsr_value >> 11U) & 0x1U);
    dfsr.sd     = ((dfsr_value >> 12U) & 0x1U);

    /*Extract contents of ADFSR register
    1. index: returns the index value for the access giving the error
    2. side_ext: value returned in this field indicates the source of the error
    3. recoverable_error:  value returned in this field indicates if the error is recoverable
        (0=Unrecoverable error, 1=Recoverable Error)
    4. cacheway: value returned in this field indicates the cache way or ways in which the error occurred*/
    ADFSR adfsr;
    uint32_t adfsr_value = abort_regs.ADFSR; 

    adfsr.index             = ((adfsr_value >> 5U) & 0x1FFU);
    adfsr.side_ext          = (((adfsr_value >> 22U) & 0x3U) | (((adfsr_value >> 20U) & 0x1U) << 2U));
    adfsr.recoverable_error = ((adfsr_value >> 21U) & 0x1U);
    adfsr.cacheway          = ((adfsr_value >> 24U) & 0xFU);

    HwiP_user_data_abort_handler_c(dfsr, adfsr, abort_regs.DFAR, abort_regs.LR, abort_regs.SPSR);
}

void TEXT_HWI WEAK HwiP_user_undefined_handler_c(volatile uint32_t LR,volatile uint32_t SPSR)
{
    volatile uint32_t loop = 1U;
    while(loop != 0U){ ; }
}

void TEXT_HWI WEAK HwiP_user_prefetch_abort_handler_c(IFSR ifsr, AIFSR aifsr, volatile uint32_t IFAR, 
                                                      volatile uint32_t LR,volatile uint32_t SPSR)
{
    volatile uint32_t loop = 1U;
    while(loop != 0U){ ; }
}

void TEXT_HWI WEAK HwiP_user_data_abort_handler_c(DFSR dfsr, ADFSR adfsr, volatile uint32_t DFAR, 
                                                  volatile uint32_t LR,volatile uint32_t SPSR)
{
    volatile uint32_t loop = 1U;
    while(loop != 0U){ ; }
}
