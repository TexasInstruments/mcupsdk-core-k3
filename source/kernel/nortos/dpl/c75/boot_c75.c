/*****************************************************************************/
/* Copyright (c) 2021-26 Texas Instruments Incorporated                      */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#include <stdint.h>
#include <string.h>
#include "MmuP_c75.h"
#include <c7x.h>
#include "kernel/dpl/StartuphooksP.h"

int _system_pre_init(void);
void _system_post_cinit(void);
void _c_int00_secure(void);

extern char __TI_STACK_END[];
register volatile uint64_t __SP;

/* Below symbols are set in linker command file */
extern uint32_t __BSS_START;
extern uint32_t __BSS_END;

/*****************************************************************************/
/* C_INT00() - C ENVIRONMENT ENTRY POINT                                     */
/*****************************************************************************/
#pragma CODE_SECTION(_c_int00_secure, ".text:_c_int00_secure")
void _c_int00_secure(void)
{
   /*------------------------------------------------------------------------*/
   /* SETUP __SP IN A POSITION-INDEPENDENT MANNER (I.E. NO _symval())        */
   /*------------------------------------------------------------------------*/
    __SP = (((uint64_t)&__TI_STACK_END) - 16U) & ~((uint64_t)(0b111));

   MmuP_init();
}

/*****************************************************************************/
/* _SYSTEM_PRE_INIT() - _system_pre_init() is called in the C/C++ startup    */
/* routine (_c_int00()) and provides a mechanism for the user to             */
/* insert application specific low level initialization instructions prior   */
/* to calling main().  The return value of _system_pre_init() is used to     */
/* determine whether or not C/C++ global data initialization will be         */
/* performed (return value of 0 to bypass C/C++ auto-initialization).        */
/*                                                                           */
/* PLEASE NOTE THAT BYPASSING THE C/C++ AUTO-INITIALIZATION ROUTINE MAY      */
/* RESULT IN PROGRAM FAILURE.                                                */
/*                                                                           */
/* The version of _system_pre_init() below is skeletal and is provided to    */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/

int _system_pre_init(void)
{
    /* initialize .bss to zero */
    uint32_t bss_size = ((uintptr_t)&__BSS_END - (uintptr_t)&__BSS_START);
    memset((void*)&__BSS_START, 0x00, bss_size);
    StartuphooksP_systemPreInit();
    return 1;
}

/*****************************************************************************/
/* _SYSTEM_POST_CINIT() - _system_post_cinit() is a hook function called in  */
/* the C/C++ auto-initialization function after cinit() and before pinit().  */
/*                                                                           */
/* The version of _system_post_cinit() below is skeletal and is provided to  */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/


void _system_post_cinit(void)
{
    extern void c7x_startup_init(void);
    c7x_startup_init();  /* Switch to Unprotected mode first */

    /* Check if MMA hardware is present on THIS core before accessing it */
    uint64_t tsr = __TSR;  /* Read Task State Register via __cregister (MVC instruction) */
    if (tsr & ((uint64_t)1U << 52U))  /* TSR.HWA_PRESENT (bit 52) */
    {
        /* MMA power-on workaround (ErrataID:i2087) */
        __HWA_CONFIG_REG_v1 mmaConfig = __gen_HWA_CONFIG_REG_v1();
        __HWA_OFFSET_REG    mmaOffset = {0};
        __HWAOPEN(mmaConfig, mmaOffset, __MMA_OPEN_FSM_RESET);
        __HWACLOSE(0);
    }
    StartuphooksP_systemPostCInit();
}
