/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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

/*
 * ======== GENERATED SECTIONS ========
 *
 *     PROLOGUE
 *     INCLUDES
 *
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef TaskSupport__include
#define TaskSupport__include



/*
 * ======== INCLUDES ========
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef void (*TaskSupport_FuncPtr)(void);

typedef void (*Task_FuncPtr)(uint32_t arg1, uint32_t arg2);



/*
 * ======== MODULE-WIDE CONFIGS ========
 */


/* defaultStackSize */
extern const size_t TaskSupport_defaultStackSize;


/* stackAlignment */
extern const unsigned int TaskSupport_stackAlignment;




/*
 * ======== FUNCTION DECLARATIONS ========
 */


/* swap */
void TaskSupport_swap( void **oldtskContext, void **newtskContext);

/* getStackAlignment */
unsigned int TaskSupport_getStackAlignment( void);


extern void * TaskSupport_buildTaskStack(void * stack, VOID (*fxn)(VOID), VOID (*exit)(VOID), VOID (*enter)(VOID), void* arg0, void* arg1, void * TCSP, bool privileged);

void * TaskSupport_setupTaskStack(VOID * pxStackArrayEndAddress, VOID * pxStackArrayStartAddress, VOID (*fxn)(VOID), VOID (*exit)(VOID), VOID (*enter)(VOID), bool privileged);


#ifdef __cplusplus
    } /* extern C */
#endif

#endif
