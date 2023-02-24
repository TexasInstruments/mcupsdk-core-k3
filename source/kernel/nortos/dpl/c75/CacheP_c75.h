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

#ifndef CACHEP_C75_H
#define CACHEP_C75_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>
#include <c6x_migration.h>
#include <kernel/dpl/CacheP.h>
#include "HwiP_c75.h"
#include "MmuP_c75.h"

/* L1Size */
typedef enum CacheP_L1Size_ {
    CacheP_L1Size_0K = 0,
    CacheP_L1Size_4K = 1,
    CacheP_L1Size_8K = 2,
    CacheP_L1Size_16K = 3,
    CacheP_L1Size_32K = 4,
    CacheP_L1Size_64K = 5
} CacheP_L1Size;

/* PC */
#define CacheP_PC  (1)

/* WTE */
#define CacheP_WTE (2)

/* PCX */
#define CacheP_PCX (4)

/* PFX */
#define CacheP_PFX (8)

/* Size */
typedef struct CacheP_Size_ {
    CacheP_L1Size l1dSize;
} CacheP_Size;


/* enableCache */
extern const bool CacheP_enableCache;

/* atomicBlockSize */
extern const uint32_t CacheP_atomicBlockSize;

/* enable writeback */
void CacheP_enableWB(uint32_t type);

/* enable writethrough */
void CacheP_enableWT(uint32_t type);

void Cache_wbInvL1dAll(void);

void CacheP_invL1dAll(void);

/* wait */
void CacheP_wait(void);

/* getSize */
void CacheP_getSize( CacheP_Size *size);

/* setL1DCFG */
void CacheP_setL1DCFG( unsigned int size);

/* getL1DCFG */
unsigned long CacheP_getL1DCFG( void);

/* setL1DWB */
void CacheP_setL1DWB( unsigned int flag);

/* setL1DWBINV */
void CacheP_setL1DWBINV( unsigned int flag);

void CacheP_setL1DINV( unsigned int flag);


void CacheP_Module_startup( void );



/*
 * ======== STATE STRUCTURES ========
 */



/* Module_State */
typedef struct CacheP_Module_State_ {
    uint64_t L1DCFG;
} CacheP_Module_State;

/* Module__state__V */
extern CacheP_Module_State CacheP_Module_state;






#ifdef __cplusplus
    } /* extern C */
#endif

#endif
