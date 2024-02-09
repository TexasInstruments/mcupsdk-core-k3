/*
 * Copyright (c) 2016-2024, Texas Instruments Incorporated
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
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>

#include <kernel/nortos/dpl/c75/csl_clec.h>
#include <drivers/hw_include/am62ax/cslr_soc_baseaddress.h>

#include "MmuP_c75.h"

#define Mmu_PADDR_MASK          0x0000FFFFFFFFFFFF

#define Mmu_GRANULE_SIZE_4KB    0x000
#define Mmu_GRANULE_SIZE_16KB   0x100
#define Mmu_GRANULE_SIZE_64KB   0x080

#define Mmu_OUTER_SHAREABLE     0x0400
#define Mmu_OUTER_CACHEABLE     0x2000
#define Mmu_INNER_CACHEABLE     0x0800

#define Mmu_MEMTYPE_CACHEABLE   0x08000

#define Mmu_WALK_EN             0x1

extern uint64_t *Mmu_level1Table;
#pragma DATA_SECTION(Mmu_tableArray, ".data.Mmu_tableArray");
#pragma DATA_ALIGN(Mmu_tableArray, 4096);
uint64_t Mmu_tableArray[16*512];
extern uint64_t  Mmu_tableArraySlot;

#pragma DATA_SECTION(gMmu_tableArray_NS, ".data.gMmu_tableArray_NS");
#pragma DATA_ALIGN(gMmu_tableArray_NS, 4096);
uint64_t gMmu_tableArray_NS[16*512];
extern uint64_t *Mmu_level1Table_NS;
extern uint64_t  Mmu_tableArraySlot_NS;

extern MmuP_Config gMmuConfig;
extern MmuP_RegionConfig gMmuRegionConfig[];
/*
 * TODO Pending work
 * =================
 *  - Add custom memset() for BIOS (name it differently). Copy implementation
 *    from RTS version.
 */


static void MmuP_addBlockEntry(uint8_t level, uint64_t *tablePtr, uint16_t tableIdx,
    uint64_t paddr, MmuP_MapAttrs *mapAttrs)
{
    uint64_t desc;

    if (level == 3)
    {
        desc = 0x3;
    }
    else
    {
        desc = MmuP_DescriptorType_BLOCK;
    }

    desc |= ((uint64_t)(mapAttrs->attrIndx & 0x7) << 2) |
            ((uint64_t)(0x1 << 5)) |
            ((uint64_t)(mapAttrs->accessPerm & 0x3) << 6) |
            ((uint64_t)(mapAttrs->shareable & 0x3) << 8) |
            ((uint64_t)(0x1) << 10) |  /* access flag */
            ((uint64_t)(!(mapAttrs->global) & 0x1) << 11) |
            ((uint64_t)(paddr & ~((1 << Mmu_configInfo.tableOffset[level]) - 1))) |
            ((uint64_t)(!(mapAttrs->privExecute) & 0x1) << 53) |
            ((uint64_t)(!(mapAttrs->userExecute) & 0x1) << 54);

    tablePtr[tableIdx] = desc;
}


static uint64_t* MmuP_allocTable()
{
    uint64_t *table;
    unsigned int i, tableLen = (Mmu_granuleSize >> 3);
    uint64_t *slot;

    table = &gMmu_tableArray_NS[tableLen * Mmu_tableArraySlot_NS];
    slot = &Mmu_tableArraySlot_NS;

    if (*slot == (~0)) {
        return (NULL);
    }

    *slot = *table;

    /* Zero-out level 1 table */
    for (i = 0; i < tableLen; i++) {
        /*
         * Use (i << 2) instead of 0 to init table, in order to force
         * compiler to not use memset() as an optimization
         */
        table[i] = (i << 2);
    }

    return (table);
}


static uint64_t* MmuP_addTableEntry(uint64_t *tablePtr, uint16_t tableIdx,
    MmuP_MapAttrs *mapAttrs)
{
    uint64_t desc, *newTable;

    newTable = MmuP_allocTable();
    if (newTable == NULL)
    {
        return (NULL);
    }

    desc = ((uint64_t)MmuP_DescriptorType_TABLE & 0x3) |
           ((uint64_t)newTable & ~(Mmu_granuleSize - 1));
    tablePtr[tableIdx] = desc;

    return (newTable);
}


static void MmuP_readBlockEntry(uint8_t level, uint64_t *tablePtr, uint16_t tableIdx,
    uint64_t *paddr, MmuP_MapAttrs *mapAttrs)
{
    uint64_t desc;

    desc = tablePtr[tableIdx];

    mapAttrs->attrIndx = (MmuP_AttrIndx)((desc >> 2) & 0x7);
    mapAttrs->accessPerm = (MmuP_AccessPerm)((desc >> 6) & 0x3);
    mapAttrs->shareable = (MmuP_Shareable)((desc >> 8) & 0x3);
    mapAttrs->global = !((desc >> 11) & 0x1);
    mapAttrs->privExecute = !((desc >> 53) & 0x1);
    mapAttrs->userExecute = !((desc >> 54) & 0x1);

    *paddr = desc & (uint64_t)Mmu_PADDR_MASK &
        ~((1 << Mmu_configInfo.tableOffset[level]) - 1);
}


static void MmuP_freeTable(uint64_t *table)
{
    *table = Mmu_tableArraySlot_NS;
    Mmu_tableArraySlot_NS = (table - gMmu_tableArray_NS) / (Mmu_granuleSize >> 3);
}


static uint8_t MmuP_tableWalk(uint8_t level, uint64_t *tablePtr, uint64_t *vaddr, uint64_t *paddr,
    uint32_t *size, MmuP_MapAttrs *mapAttrs)
{
    uint64_t desc;
    uint16_t tableIdx;
    uint32_t  blockSize;
    uint8_t   retStatus;
    uint8_t   blockTranslation;
    uint64_t *nextLevelTablePtr;

    blockTranslation = 1;
    blockSize = 1 << Mmu_configInfo.tableOffset[level];
    if ((level == 0) ||
       ((level == 1) && (Mmu_granuleSize != MMUP_GRANULE_SIZE_4KB))) {
        blockTranslation = 0;
    }

    tableIdx = (*vaddr >> Mmu_configInfo.tableOffset[level]) &
        Mmu_configInfo.indexMask;

    while ((*size != 0) && (tableIdx < Mmu_configInfo.tableLength)) {
        desc = tablePtr[tableIdx];

        if (((desc & 0x3) == MmuP_DescriptorType_TABLE) && (level != 3)) {
            if ((blockTranslation == 1) && (*size >= blockSize) &&
                (*vaddr & (blockSize - 1) == 0))
            {
                MmuP_addBlockEntry(level, tablePtr, tableIdx, *paddr, mapAttrs);
                *size = *size - blockSize;
                *vaddr = *vaddr + blockSize;
                *paddr = *paddr + blockSize;
                MmuP_freeTable((uint64_t *)(Mmu_PADDR_MASK & desc &
                    ~(uint64_t)(Mmu_granuleSize - 1)));
            }
            else {
                nextLevelTablePtr = (uint64_t *)(Mmu_PADDR_MASK & desc &
                    ~(uint64_t)(Mmu_granuleSize - 1));
                retStatus = MmuP_tableWalk(level + 1, nextLevelTablePtr,
                    vaddr, paddr, size, mapAttrs);
                if (!retStatus) {
                    return 0;
                }
            }
        }
        else if (((desc & 0x3) != MmuP_DescriptorType_TABLE) || (level == 3))
        {
            if ((level == 0) || ((level < 3) && (*size < blockSize)) ||
               ((*size >= blockSize) && ((*vaddr & (blockSize - 1)) != 0)))
            {
                uint64_t vaddrCopy = (*vaddr & (~(blockSize - 1)));
                uint64_t paddrCopy;
                MmuP_MapAttrs mapAttrsCopy;
                uint32_t sizeCopy = blockSize;

                if ((desc & 0x3) == MmuP_DescriptorType_BLOCK)
                {
                    MmuP_readBlockEntry(level, tablePtr, tableIdx, &paddrCopy,
                        &mapAttrsCopy);
                }

                nextLevelTablePtr =
                    MmuP_addTableEntry(tablePtr, tableIdx, mapAttrs);
                if (nextLevelTablePtr == NULL) {
                    return 0;
                }

                if ((desc & 0x3) == MmuP_DescriptorType_BLOCK) {
                    /*
                     * If old entry is a block entry, a new table entry is
                     * added and merged with the old block entry.
                     */
                    MmuP_tableWalk(level + 1, nextLevelTablePtr, &vaddrCopy,
                        &paddrCopy, &sizeCopy, &mapAttrsCopy);
                }

                retStatus = MmuP_tableWalk(level + 1, nextLevelTablePtr,
                    vaddr, paddr, size, mapAttrs);
                if (!retStatus) {
                    return 0;
                }
            }
            else if ((blockTranslation == true) && (*size >= blockSize)) {
                MmuP_addBlockEntry(level, tablePtr, tableIdx, *paddr, mapAttrs);
                *size = *size - blockSize;
                *vaddr = *vaddr + blockSize;
                *paddr = *paddr + blockSize;
            }
        }

        tableIdx++;
    }

    return 1;
}

__attribute__((weak)) void MmuP_setConfig()
{
	uint32_t i;
	int32_t status;

	for(i = 0; i < gMmuConfig.numRegions; i++)
	{
		status = MmuP_map(gMmuRegionConfig[i].vaddr, gMmuRegionConfig[i].paddr,
						gMmuRegionConfig[i].size, &gMmuRegionConfig[i].attr);

        DebugP_assertNoLog(status == SystemP_SUCCESS);
	}

    HwiP_configClecAccessCtrl();
	return;
}

void MmuP_disable(void)
{
    uint16_t type;
    unsigned int   key;

    /* if MMU is alreay disabled, just return */
    if (!(MmuP_isEnabled())) {
        return;
    }

    key = Hwi_disable();

    type = CacheP_TYPE_L1D;

    if (type & CacheP_TYPE_L1D) {
        /* disable the L1 data cache */
        CacheP_disable(CacheP_TYPE_L1D);
    }

    /* disables the MMU */
    MmuP_disableI();

    /* Invalidate entire TLB */
    MmuP_tlbInvAll(0);

    /* set cache back to initial settings */
    CacheP_enable(type);

    Hwi_restore(key);
}

/*
 *  ======== Mmu_disableI ========
 */
void MmuP_disableI()
{
    asm("\t mvk64.l1    0xfffffffffffffffeLL, a2 \n"
        "\t mvc.s1      SCR, a3                  \n"
        "\t nop                                  \n"
        "\t andd.l1     a2, a3, a3               \n"
        "\t mvc.s1      a3, SCR");
}

/*
 *  ======== Mmu_enable ========
 */
void MmuP_enable()
{
    unsigned int   key;
    unsigned int   mode;

    /* if MMU is already enabled then just return */
    if (MmuP_isEnabled()) {
        return;
    }

    key = Hwi_disable();

    CacheP_disable(CacheP_TYPE_L1D);

    /* Invalidate entire TLB */
    MmuP_tlbInvAll(0);

    /* enables the MMU */
    mode = Hwi_getCXM();
    if (mode == Hwi_TSR_CXM_SecureSupervisor) {
        MmuP_enableI_secure();
    }
    MmuP_enableI();

    CacheP_enable(CacheP_TYPE_L1D);

    Hwi_restore(key);
}

/*
 *  ======== Mmu_enableI_secure ========
 */
void MmuP_enableI_secure()
{
    asm("\t mvk64.l1    0x80000000000000C1LL, a2 \n"
        "\t mvc.s1      SCR, a3                  \n"
        "\t nop                                  \n"
        "\t ord.l1      a2, a3, a3               \n"
        "\t mvc.s1      a3, SCR                  \n"
        "\t mvc.s1      a3, SCR_S");
}

/*
 *  ======== Mmu_enableI ========
 */
void MmuP_enableI()
{
    asm("\t mvk64.l1    0x80000000000000C1LL, a2 \n"
        "\t mvc.s1      SCR, a3                \n"
        "\t nop                                  \n"
        "\t ord.l1      a2, a3, a3               \n"
        "\t mvc.s1      a3, SCR");
}


/*
 *  ======== MmuP_MapAttrs_init ========
 */
void MmuP_MapAttrs_init(MmuP_MapAttrs *attrs)
{
    DebugP_assertNoLog( attrs != NULL );

    attrs->accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_NONE;
    attrs->privExecute = 1;
    attrs->userExecute = 0;
    attrs->shareable = MMUP_SHARABLE_OUTER;
    attrs->attrIndx = MMUP_ATTRINDX_MAIR0;
    attrs->global = 1;
}

int32_t MmuP_map(uintptr_t vaddr, uintptr_t paddr, uint32_t size, MmuP_MapAttrs *mapAttrs)
{
    uint32_t key;
    uint8_t retStatus, enabled;
    int32_t status = SystemP_SUCCESS;

    /* Assert that mapAttrs != NULL */
    DebugP_assertNoLog(mapAttrs != NULL);

    /* Range check on vaddr and paddr */
    DebugP_assertNoLog(vaddr <= Mmu_PADDR_MASK);
    DebugP_assertNoLog(paddr <= Mmu_PADDR_MASK);

    /* Alignment check on vaddr, paddr & size */
    DebugP_assertNoLog((vaddr & (Mmu_granuleSize - 1)) == 0);
    DebugP_assertNoLog((paddr & (Mmu_granuleSize - 1)) == 0);
    DebugP_assertNoLog((size & (Mmu_granuleSize - 1)) == 0);

    key = Hwi_disable();

    /* determine the current state of the MMU */
    enabled = MmuP_isEnabled();

    /* disable the MMU (if already disabled, does nothing) */
    MmuP_disable();

    if (Mmu_configInfo.noLevel0Table) {
        retStatus = MmuP_tableWalk(1, Mmu_level1Table_NS, &vaddr, &paddr,
            &size, mapAttrs);
    }
    else {
        retStatus = MmuP_tableWalk(0, Mmu_level1Table_NS, &vaddr, &paddr,
            &size, mapAttrs);
    }

    /* Ensure all translation table updates have been observed */
#if 0
    __asm__ __volatile__ (
        "dsb sy"
        ::: "memory"
    );
#endif

    if (enabled) {
        /* if Mmu was enabled, then re-enable it */
        MmuP_enable();
    }

    Hwi_restore(key);

    if(retStatus==1)
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return (status);
}

void MmuP_init()
{
    uint64_t tcr = 0;
    uint32_t i, tableLen = Mmu_configInfo.tableLength;
    uint32_t mode;

    /* Initialize MAIR */
    MmuP_setMAIRAsm(0, Mmu_MAIR0);
    MmuP_setMAIRAsm(1, Mmu_MAIR1);
    MmuP_setMAIRAsm(2, Mmu_MAIR2);
    MmuP_setMAIRAsm(3, Mmu_MAIR3);
    MmuP_setMAIRAsm(4, Mmu_MAIR4);
    MmuP_setMAIRAsm(5, Mmu_MAIR5);
    MmuP_setMAIRAsm(6, Mmu_MAIR6);
    MmuP_setMAIRAsm(7, Mmu_MAIR7);

    if (Mmu_granuleSize == MMUP_GRANULE_SIZE_4KB) {
        tcr = Mmu_GRANULE_SIZE_4KB;
    }
    else if (Mmu_granuleSize == MMUP_GRANULE_SIZE_16KB) {
        tcr = Mmu_GRANULE_SIZE_16KB;
    }
    else if (Mmu_granuleSize == MMUP_GRANULE_SIZE_64KB) {
        tcr = Mmu_GRANULE_SIZE_64KB;
    }

    /*
     * TCR config:
     *  - MMU tables reside in outer and inner write-back write-allocate
     *    cacheable memory
     *  - Physical address size is 48-bits wide
     *  - TTBR0 is used for translating VA 0 to (2^48 - 1)
     */
    tcr = tcr | (uint64_t)Mmu_MEMTYPE_CACHEABLE | Mmu_OUTER_SHAREABLE |
          Mmu_OUTER_CACHEABLE | Mmu_INNER_CACHEABLE |
          ((64 - MMUP_PA_MAX_WIDTH) << 1) | Mmu_WALK_EN;

    mode = Hwi_getCXM();
    if (mode == Hwi_TSR_CXM_SecureSupervisor)
    {
        MmuP_setTCR(tcr, 1);
    }
    MmuP_setTCR(tcr, 0);

    for (i = 0; i < Mmu_tableArrayLen; i++)
    {
        gMmu_tableArray_NS[tableLen * i] = i + 1;
    }

    gMmu_tableArray_NS[tableLen * (i - 1)] = (~0);
    Mmu_tableArraySlot_NS = 0;

    /* Allocate level1 Table */
    Mmu_level1Table_NS = MmuP_allocTable();


    /* Install MMU translation tables */
    if (mode == Hwi_TSR_CXM_SecureSupervisor)
    {
        Mmu_init(Mmu_level1Table, 1);
    }

    Mmu_init(Mmu_level1Table_NS, 0);

    Mmu_initFunc();


    /* Invalidate entire TLB */
//    Mmu_tlbInvAll(0);

    if (Mmu_enableMMU) //Add enable mmu attr from syscfg once supported
    {
        mode = Hwi_getCXM();
        if (mode == Hwi_TSR_CXM_SecureSupervisor) {
            MmuP_enableI_secure();
        }
        else {
            MmuP_enableI();
        }
    }

    if (Hwi_bootToNonSecure) {
        Hwi_secureStart();
    }
}

#if defined(__GNUC__) && !defined(__ti__)
#error "Unsupported compiler"
#else



#pragma DATA_SECTION(Mmu_tableArraySlot, ".data.Mmu_tableArraySlot");
#pragma DATA_ALIGN(Mmu_tableArraySlot, 4096);
uint64_t Mmu_tableArraySlot;
#pragma DATA_SECTION(Mmu_tableArraySlot_NS, ".data.Mmu_tableArraySlot_NS");
#pragma DATA_ALIGN(Mmu_tableArraySlot_NS, 4096);
uint64_t Mmu_tableArraySlot_NS;

#pragma DATA_SECTION(Mmu_level1Table, ".data.Mmu_level1Table");
#pragma DATA_ALIGN(Mmu_level1Table, 4096);
uint64_t* Mmu_level1Table;
#pragma DATA_SECTION(Mmu_level1Table_NS, ".data.Mmu_level1Table_NS");
#pragma DATA_ALIGN(Mmu_level1Table_NS, 4096);
uint64_t* Mmu_level1Table_NS;

#endif

/* enableMMU */
#pragma DATA_SECTION(Mmu_enableMMU, ".const:Mmu_enableMMU");
const bool Mmu_enableMMU = 1; //to be removed once syscfg support is added

/* granuleSize */
#pragma DATA_SECTION(Mmu_granuleSize, ".const:Mmu_granuleSize");
const MmuP_GranuleSize Mmu_granuleSize = MMUP_GRANULE_SIZE_4KB;

/* MAIR0 */
#pragma DATA_SECTION(Mmu_MAIR0, ".const:Mmu_MAIR0");
const uint8_t Mmu_MAIR0 = (uint8_t)0x0U;

/* MAIR1 */
#pragma DATA_SECTION(Mmu_MAIR1, ".const:Mmu_MAIR1");
const uint8_t Mmu_MAIR1 = (uint8_t)0x4U;

/* MAIR2 */
#pragma DATA_SECTION(Mmu_MAIR2, ".const:Mmu_MAIR2");
const uint8_t Mmu_MAIR2 = (uint8_t)0x8U;

/* MAIR3 */
#pragma DATA_SECTION(Mmu_MAIR3, ".const:Mmu_MAIR3");
const uint8_t Mmu_MAIR3 = (uint8_t)0xcU;

/* MAIR4 */
#pragma DATA_SECTION(Mmu_MAIR4, ".const:Mmu_MAIR4");
const uint8_t Mmu_MAIR4 = (uint8_t)0x44U;

/* MAIR5 */
#pragma DATA_SECTION(Mmu_MAIR5, ".const:Mmu_MAIR5");
const uint8_t Mmu_MAIR5 = (uint8_t)0x4fU;

/* MAIR6 */
#pragma DATA_SECTION(Mmu_MAIR6, ".const:Mmu_MAIR6");
const uint8_t Mmu_MAIR6 = (uint8_t)0xbbU;

/* MAIR7 */
#pragma DATA_SECTION(Mmu_MAIR7, ".const:Mmu_MAIR7");
const uint8_t Mmu_MAIR7 = (uint8_t)0x7dU;

/* tableArrayLen */
#pragma DATA_SECTION(Mmu_tableArrayLen, ".const:Mmu_tableArrayLen");
const unsigned int Mmu_tableArrayLen = (unsigned int)0x10U;

/* configInfo */
#pragma DATA_SECTION(Mmu_configInfo, ".const:Mmu_configInfo");
const MmuP_Info Mmu_configInfo = {
    (uint64_t)0x1ffU,  /* indexMask */
    (uint32_t)0x200U,  /* tableLength */
    {
        (uint8_t)0x27U,  /* [0] */
        (uint8_t)0x1eU,  /* [1] */
        (uint8_t)0x15U,  /* [2] */
        (uint8_t)0xcU,  /* [3] */
    },  /* tableOffset */
    (uint8_t)0xcU,  /* granuleSizeBits */
    (uint8_t)0x9U,  /* indexBits */
    0,  /* noLevel0Table */
};
