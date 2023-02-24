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

#ifndef MMUP_C75_H
#define MMUP_C75_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/MmuP_armv8.h>
#include "HwiP_c75.h"
#include "CacheP_c75.h"


typedef struct Mmu_Module_State Mmu_Module_State;

/* PA_MAX_WIDTH */
#define MMUP_PA_MAX_WIDTH            48

/* PA_SIZE_ENCODING */
#define MMUP_PA_SIZE_ENCODING   0x5

/* DescriptorType */
typedef enum MmuP_DescriptorType_ {
    MmuP_DescriptorType_INVALID0 = 0,   /*! Virtual address is unmapped     */
    MmuP_DescriptorType_BLOCK = 1,      /*! Block descriptor                */
    MmuP_DescriptorType_INVALID1 = 2,   /*! Virtual address is unmapped     */
    MmuP_DescriptorType_TABLE = 3       /*! Next-level table address        */
} MmuP_DescriptorType;

/* GranuleSize */
typedef enum MmuP_GranuleSize_ {
    MMUP_GRANULE_SIZE_4KB = 0x1000,
    MMUP_GRANULE_SIZE_16KB = 0x4000,
    MMUP_GRANULE_SIZE_64KB = 0x10000
} MmuP_GranuleSize;

/* InitFuncPtr */
typedef void (*Mmu_InitFuncPtr)(void );

/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* ConfigInfo */
typedef struct MmuP_Info_ {
    uint64_t indexMask;
    uint32_t tableLength;
    uint8_t  tableOffset[4];
    uint8_t  granuleSizeBits;
    uint8_t  indexBits;
    uint8_t  noLevel0Table;
} MmuP_Info;



/* defaultMapAttrs */
extern const MmuP_MapAttrs Mmu_defaultMapAttrs;

/* enableMMU */
extern const bool Mmu_enableMMU;

/* granuleSize */
extern const MmuP_GranuleSize Mmu_granuleSize;

/* MAIR0 */
extern const uint8_t Mmu_MAIR0;

/* MAIR1 */
extern const uint8_t Mmu_MAIR1;

/* MAIR2 */
extern const uint8_t Mmu_MAIR2;

/* MAIR3 */
extern const uint8_t Mmu_MAIR3;

/* MAIR4 */
extern const uint8_t Mmu_MAIR4;

/* MAIR5 */
extern const uint8_t Mmu_MAIR5;

/* MAIR6 */
extern const uint8_t Mmu_MAIR6;

/* MAIR7 */
extern const uint8_t Mmu_MAIR7;


/* initFunc */
extern const Mmu_InitFuncPtr Mmu_initFunc;

/* tableArrayLen */
extern const unsigned int Mmu_tableArrayLen;


/* configInfo */
extern const MmuP_Info Mmu_configInfo;



/*
 * ======== FUNCTION DECLARATIONS ========
 */




/* tlbInvAll */
void MmuP_tlbInvAll( uint64_t type);

/* disableI */
void MmuP_disableI( void);

/* enableI */
void MmuP_enableI( void);

/* enableI_secure */
void MmuP_enableI_secure( void);

/* init */
void Mmu_init( void * tableAddr, bool secure);

/* setMAIRAsm */
void MmuP_setMAIRAsm( uint8_t attrIndx, uint8_t attr);

/* setTCR */
void MmuP_setTCR( uint64_t regVal, bool secure);



#ifdef __cplusplus
    } /* extern C */
#endif

#endif
