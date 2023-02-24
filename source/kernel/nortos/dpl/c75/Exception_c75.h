/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef Exception__include
#define Exception__include




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

typedef struct Exception_Context Exception_Context;
typedef struct Exception_Status Exception_Status;
typedef struct Exception_Module_State Exception_Module_State;




/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef void (*Exception_FuncPtr)(void );

/* Context */
typedef void * C7XVectorReg[8];

struct Exception_Context {
    void * IERR;
    void * IEAR;
    void * IESR;
    void * RP;
    void * FPCR;
    void * FSR;
    void * GFPGFR;
    void * GPLY;
    void * P7;
    void * P6;
    void * P5;
    void * P4;
    void * P3;
    void * P2;
    void * P1;
    void * P0;
    C7XVectorReg SE0_0;
    C7XVectorReg SE0_1;
    C7XVectorReg SE0_2;
    C7XVectorReg SE0_3;
    C7XVectorReg SE1_0;
    C7XVectorReg SE1_1;
    C7XVectorReg SE1_2;
    C7XVectorReg SE1_3;
    C7XVectorReg SA3CR;
    C7XVectorReg SA2CR;
    C7XVectorReg SA1CR;
    C7XVectorReg SA0CR;
    C7XVectorReg SA3CNTR0;
    C7XVectorReg SA2CNTR0;
    C7XVectorReg SA1CNTR0;
    C7XVectorReg SA0CNTR0;
    C7XVectorReg CUCR3;
    C7XVectorReg CUCR2;
    C7XVectorReg CUCR1;
    C7XVectorReg CUCR0;
    C7XVectorReg VBL7;
    C7XVectorReg VBL6;
    C7XVectorReg VBL5;
    C7XVectorReg VBL4;
    C7XVectorReg VBL3;
    C7XVectorReg VBL2;
    C7XVectorReg VBL1;
    C7XVectorReg VBL0;
    C7XVectorReg VBM7;
    C7XVectorReg VBM6;
    C7XVectorReg VBM5;
    C7XVectorReg VBM4;
    C7XVectorReg VBM3;
    C7XVectorReg VBM2;
    C7XVectorReg VBM1;
    C7XVectorReg VBM0;
    C7XVectorReg VB15;
    C7XVectorReg VB14;
    C7XVectorReg VB13;
    C7XVectorReg VB12;
    C7XVectorReg VB11;
    C7XVectorReg VB10;
    C7XVectorReg VB9;
    C7XVectorReg VB8;
    C7XVectorReg VB7;
    C7XVectorReg VB6;
    C7XVectorReg VB5;
    C7XVectorReg VB4;
    C7XVectorReg VB3;
    C7XVectorReg VB2;
    C7XVectorReg VB1;
    C7XVectorReg VB0;
    void * AL7;
    void * AL6;
    void * AL5;
    void * AL4;
    void * AL3;
    void * AL2;
    void * AL1;
    void * AL0;
    void * AM7;
    void * AM6;
    void * AM5;
    void * AM4;
    void * AM3;
    void * AM2;
    void * AM1;
    void * AM0;
    void * D15;
    void * D14;
    void * D13;
    void * D12;
    void * D11;
    void * D10;
    void * D9;
    void * D8;
    void * D7;
    void * D6;
    void * D5;
    void * D4;
    void * D3;
    void * D2;
    void * D1;
    void * D0;
    void * A15;
    void * A14;
    void * A13;
    void * A12;
    void * A11;
    void * A10;
    void * A9;
    void * A8;
    void * A7;
    void * A6;
    void * A5;
    void * A4;
    void * A3;
    void * A2;
    void * A1;
    void * A0;
};

/* Status */
struct Exception_Status {
    uint64_t nrp;
    uint64_t ntsr;
    uint64_t ierr;
    uint64_t iear;
    uint64_t iesr;
    Exception_Context *excContext;
};

/* IERRPFX */
#define Exception_IERRPFX (0x00000001)

/* IERRIFX */
#define Exception_IERRIFX (0x00000002)

/* IERRFPX */
#define Exception_IERRFPX (0x00000004)

/* IERREPX */
#define Exception_IERREPX (0x00000008)

/* IERROPX */
#define Exception_IERROPX (0x00000010)

/* IERRRCX */
#define Exception_IERRRCX (0x00000020)

/* IERRRAX */
#define Exception_IERRRAX (0x00000040)

/* IERRPRX */
#define Exception_IERRPRX (0x00000080)

/* IERRLBX */
#define Exception_IERRLBX (0x00000100)

/* IERRMSX */
#define Exception_IERRMSX (0x00000200)

/* IERRDFX */
#define Exception_IERRDFX (0x00000400)

/* IERRSEX */
#define Exception_IERRSEX (0x00000800)

/* IERREXX */
#define Exception_IERREXX (0x00001000)

/* IERRADX */
#define Exception_IERRADX (0x00002000)

/* IERRMMX */
#define Exception_IERRMMX (0x00004000)

/* sizeContextBuf */
#define Exception_sizeContextBuf (0x1000)




/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* useInternalBuffer */
extern const bool Exception_useInternalBuffer;

/* enablePrint */
extern const bool Exception_enablePrint;

/* exceptionHook */
extern const Exception_FuncPtr Exception_exceptionHook;

/* internalHook */
extern const Exception_FuncPtr Exception_internalHook;

/* returnHook */
extern const Exception_FuncPtr Exception_returnHook;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
void Exception_Module_startup( void );


/* getLastStatus */
void Exception_getLastStatus( Exception_Status *status);

/* clearLastStatus */
void Exception_clearLastStatus( void);

/* setReturnPtr */
Exception_FuncPtr Exception_setReturnPtr( Exception_FuncPtr ptr);

/* dispatch */
void Exception_dispatch( void);

/* handler */
void Exception_handler( bool abortFlag, int vectorType);

/* internalHandler */
void Exception_internalHandler( void);


/*
 * ======== STATE STRUCTURES ========
 */

/* Module_State */
struct Exception_Module_State {
    uint64_t nrp;
    uint64_t ntsr;
    uint64_t ierr;
    uint64_t iear;
    uint64_t iesr;
    Exception_FuncPtr returnHook;
    Exception_Context *excContext;
    char *excPtr;
    uint64_t contextBuf[(Exception_sizeContextBuf/sizeof(uint64_t))];
};

/* Module__state__V */
extern struct Exception_Module_State Exception_Module_state;



/*
 * ======== PREFIX ALIASES ========
 */



#ifdef __cplusplus
    } /* extern C */
#endif

#endif
