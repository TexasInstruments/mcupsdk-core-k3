/*
 *  Copyright (C) 2024-2025 Texas Instruments Incorporated
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

/**
 *  \file bootloader_mcelf.c
 *
 *  \brief Bootloader MCELF Driver API source file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/bootloader.h>
#include <board/flash.h>
#if defined (DRV_VERSION_MMCSD_V0) || defined (DRV_VERSION_MMCSD_V1)
#include <drivers/bootloader/bootloader_mmcsd_raw.h>
#endif
#include <drivers/bootloader/soc/bootloader_soc.h>
#include <drivers/bootloader/bootloader_priv.h>
#include <string.h>
#include <drivers/device_manager/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Flash data region base address */
#define FLASH_BASE_ADDRESS                    (CSL_FSS0_DAT_REG1_BASE)

/* MCELF note segment types */
#define SEGMENT_MAP_NOTE_TYPE                 (0xBBBB7777U)
#define ENTRY_POINTS_NOTE_TYPE                (0xCCCC9999U)
#define VENDOR_ID_NOTE_TYPE                   (0xAAAA5555U)

#define X509CERT_HEADER_SIZE                  (4U)
#define SCRATCH_BUFFER_SIZE                   ((uint32_t)(0x1000))

#define BOOTLOADER_MCELF_META_DATA_SIZE_MAX   (ELF_HEADER_MAX_SIZE + \
                                               (ELF_MAX_SEGMENTS * ELF_P_HEADER_MAX_SIZE) \
                                               + ELF_NOTE_SEGMENT_MAX_SIZE)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t noteSegmentSz;
    /**< Size of the note segment */
    uint32_t noteSegmentOffset;
    /**< Offset of the note segment */
    Bootloader_ELFNote *noteSegmentPtr;
    /**< Pointer to store address of note segment */
    uint8_t *noteSegmentMapPtr;
    /**< Pointer to the map type note segment */
} Bootloader_NoteSegInfo;

typedef struct
{
    uint32_t certLength;
    uint32_t numSegments;
    uint8_t elfClass;
    Bootloader_ELFH32 *elfPtr32;
    Bootloader_ELFPH32 *elfPhdrPtr32;
    Bootloader_ELFH64 *elfPtr64;
    Bootloader_ELFPH64 *elfPhdrPtr64;
    Bootloader_NoteSegInfo *noteSegInfo;
} Bootloader_McelfMeta;

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

/* Buffer to store the elf header, program header table(PHT) and note segment */
uint8_t gElfBuffer[BOOTLOADER_MCELF_META_DATA_SIZE_MAX];

/* Map to store cores booted */
static uint32_t gCoresBootedMap = 0;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Function to initialize CPU core */
static int32_t Bootloader_initCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo);

/* Function to authenticate the certificate */
int32_t Bootloader_authCertificate(Bootloader_Config *config, Bootloader_McelfMeta *mcelfMetaInfo);

/* Function to parse the mcelf image meta data */
int32_t Bootloader_parseELFMeta(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo, Bootloader_McelfMeta *mcelfMetaInfo);

/* Function to parse the note segment info*/
static int32_t Bootloader_parseNoteSegment(Bootloader_Handle handle,
                                    Bootloader_BootImageInfo *bootImageInfo,
                                    Bootloader_NoteSegInfo *noteSegInfo,
                                    uint8_t elfClass);

/* Functions to call TISCI APIs for authentication */
static int32_t Bootloader_authInit(uint32_t certLoadAddr);
static int32_t Bootloader_authUpdate(uint32_t segAddr, uint32_t segSize, bool final_pkt, uint64_t dst);
static int32_t Bootloader_authFinish(void);

/* Function to copy DMA restricted regions */
static void Bootloader_restrictedRegionCopy(Bootloader_Handle handle, uint32_t segmentSize, uint32_t loadAddr);

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

int32_t Bootloader_parseAndLoadMultiCoreELF(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_ELFH32 *elfPtr32 = NULL;
    Bootloader_ELFPH32 *elfPhdrPtr32 = NULL;

    Bootloader_ELFH64 *elfPtr64 = NULL;
    Bootloader_ELFPH64 *elfPhdrPtr64 = NULL;

    Bootloader_NoteSegInfo noteSegInfo =
    {
        .noteSegmentSz = 0U,
        .noteSegmentOffset = 0U,
        .noteSegmentPtr = NULL,
        .noteSegmentMapPtr = NULL,
    };

    Bootloader_McelfMeta mcelfMetaInfo=
    {
        .certLength = 0U,
        .elfClass = ELFCLASS_32,
        .numSegments = 0U,
        .elfPtr32 = NULL,
        .elfPtr64 = NULL,
        .elfPhdrPtr32 = NULL,
        .elfPhdrPtr64 = NULL,
        .noteSegInfo = &noteSegInfo,
    };

    /* Array to check if core is initialized */
    uint8_t initCpuDone[CSL_CORE_ID_MAX] = {0U};

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if ((config->fxns != NULL) && ((config->fxns->imgReadFxn == NULL) || (config->fxns->imgSeekFxn == NULL)))
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {


#if !defined (SKIP_AUTH_FLOW)

        uint32_t certLen = 0U;

        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            status = Bootloader_authCertificate(config, &mcelfMetaInfo);
            certLen = mcelfMetaInfo.certLength;

            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_parseELFMeta(handle, bootImageInfo, &mcelfMetaInfo);
            }

            if(status == SystemP_SUCCESS)
            {
                uint32_t i = 1U, cslCoreId = 0U, mcelfCoreId = 0U, imgAddr;
                bool isFinalPkt = FALSE;

                if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
                {
                    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);
                    imgAddr = (uint32_t) FLASH_BASE_ADDRESS + flashArgs->appImageOffset + certLen;
                }

                if(mcelfMetaInfo.elfClass == ELFCLASS_32)
                {
                    elfPtr32 = mcelfMetaInfo.elfPtr32;
                    elfPhdrPtr32 = mcelfMetaInfo.elfPhdrPtr32;

                    if(status == SystemP_SUCCESS)
                    {
                        /* Loop over the segments and do auth update */
                        for(i = 1U; i < elfPtr32->ePhnum; i++)
                        {
                            mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                            cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                            if(!initCpuDone[cslCoreId])
                            {
                                status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                                initCpuDone[cslCoreId] = 1U;
                            }

                            if (status == SystemP_SUCCESS)
                            {
                                if((elfPhdrPtr32[i].filesz != 0U) && (elfPhdrPtr32[i].type == PT_LOAD))
                                {
                                    uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr32[i].vaddr);
                                    uint32_t loadAddr = addr;

                                    /* Add check for SBL reserved memory */
                                    Bootloader_resMemSections *resMem;
                                    uint32_t resSectionCnt, start, end;
                                    resMem = Bootloader_socGetSBLMem();
                                    for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                                    {
                                        start = resMem->memSection[resSectionCnt].memStart;
                                        end = resMem->memSection[resSectionCnt].memEnd;
                                        if((addr > start) && (addr < end))
                                        {
                                            status = SystemP_FAILURE;
                                            DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                            break;
                                        }
                                    }

                                    if (status == SystemP_SUCCESS)
                                    {
                                        if (i == elfPtr32->ePhnum - 1U)
                                        {
                                            isFinalPkt = TRUE;
                                        }

                                        if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
                                        {
                                            status = Bootloader_authUpdate( imgAddr + elfPhdrPtr32[i].offset, \
                                                                    (uint32_t) elfPhdrPtr32[i].filesz, \
                                                                    isFinalPkt, \
                                                                    (uint64_t) addr);

                                            ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr32[i].filesz;
                                        }
                                        else if ((config->bootMedia == BOOTLOADER_MEDIA_SD) || (config->bootMedia == BOOTLOADER_MEDIA_EMMC))
                                        {
                                            /* Move current read position to start of Program segment */
                                            config->fxns->imgSeekFxn(((uint32_t) elfPhdrPtr32[i].offset + certLen), config->args);

                                            if(Bootloader_socIsDmaRestrictedRegion(addr) != 0)
                                            {
                                                if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                                {
                                                    loadAddr = elfPhdrPtr32[i].paddr;
                                                }
                                                Bootloader_restrictedRegionCopy(handle, (uint32_t) elfPhdrPtr32[i].filesz, loadAddr);
                                            }
                                            else
                                            {
                                                config->fxns->imgReadFxn((void *)(loadAddr), (uint32_t)elfPhdrPtr32[i].filesz, config->args);
                                            }

                                            /* Do auth init from the load address */
                                            status = Bootloader_authUpdate( addr, \
                                                                    (uint32_t) elfPhdrPtr32[i].filesz, \
                                                                    isFinalPkt, \
                                                                    (uint64_t) addr);

                                            ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr32[i].filesz;
                                        }
                                        else
                                        {
                                            /* do nothing */
                                        }
                                    }
                                    else
                                    {
                                        /* do nothing */
                                    }
                                }
                                else
                                {
                                    /* NO LOAD segment, do nothing */
                                }
                            }

                            if (status != SystemP_SUCCESS)
                            {
                                break;
                            }
                        }
                    }
                }
                else if(mcelfMetaInfo.elfClass == ELFCLASS_64)
                {
                    if(status == SystemP_SUCCESS)
                    {
                        elfPtr64 = mcelfMetaInfo.elfPtr64;
                        elfPhdrPtr64 = mcelfMetaInfo.elfPhdrPtr64;

                        /* Loop over the segments and do auth update */
                        for(i = 1; i < elfPtr64->ePhnum; i++)
                        {
                            mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                            cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                            if(!initCpuDone[cslCoreId])
                            {
                                status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                                initCpuDone[cslCoreId] = 1;
                            }

                            if ((elfPhdrPtr64[i].filesz != 0U) && (elfPhdrPtr64[i].type == PT_LOAD))
                            {
                                uint32_t addr = (uint32_t) Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr64[i].vaddr);
                                uint32_t loadAddr = addr;

                                /* Add check for SBL reserved memory */
                                Bootloader_resMemSections *resMem;
                                uint32_t resSectionCnt, start, end;
                                resMem = Bootloader_socGetSBLMem();
                                for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                                {
                                    start = resMem->memSection[resSectionCnt].memStart;
                                    end = resMem->memSection[resSectionCnt].memEnd;
                                    if((addr > start) && (addr < end))
                                    {
                                        status = SystemP_FAILURE;
                                        DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                        break;
                                    }
                                }

                                if (status == SystemP_SUCCESS)
                                {
                                    if (i == (elfPtr64->ePhnum - 1U))
                                    {
                                        isFinalPkt = TRUE;
                                    }

                                    if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
                                    {
                                        status = Bootloader_authUpdate( imgAddr + elfPhdrPtr64[i].offset, \
                                                                (uint32_t) elfPhdrPtr64[i].filesz, \
                                                                isFinalPkt, \
                                                                (uint64_t) addr);
                                        ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr64[i].filesz;
                                    }
                                    else if((config->bootMedia == BOOTLOADER_MEDIA_SD) || (config->bootMedia == BOOTLOADER_MEDIA_EMMC))
                                    {
                                        /* Move current read position to start of Program segment */
                                        config->fxns->imgSeekFxn(((uint32_t) elfPhdrPtr64[i].offset + certLen), config->args);

                                        if(Bootloader_socIsDmaRestrictedRegion((uint32_t)addr) != 0)
                                        {
                                            if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                            {
                                                loadAddr = (uint32_t) elfPhdrPtr64[i].paddr;
                                            }
                                            Bootloader_restrictedRegionCopy(handle, (uint32_t) elfPhdrPtr64[i].filesz, loadAddr);
                                        }
                                        else
                                        {
                                            config->fxns->imgReadFxn((void *)(addr), (uint32_t) elfPhdrPtr64[i].filesz, config->args);
                                        }

                                        /* Do auth init from the load address */
                                        status = Bootloader_authUpdate( addr, \
                                                                (uint32_t) elfPhdrPtr64[i].filesz, \
                                                                isFinalPkt, \
                                                                (uint64_t) addr);

                                        ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr64[i].filesz;
                                    }
                                    else
                                    {
                                        /* do nothing */
                                    }
                                }
                            }
                            else
                            {
                                /* NO LOAD segment, do nothing */
                            }

                            if (status != SystemP_SUCCESS)
                            {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    /* do nothing */
                }
            }

            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_authFinish();
            }

        }
#else
        if(status == SystemP_SUCCESS)
        {
            /* Read the ELF metadata from the bootmedia */
            status = config->fxns->imgReadFxn(gElfBuffer, BOOTLOADER_MCELF_META_DATA_SIZE_MAX, config->args);

            char ELFSTR[] = { 0x7F, 'E', 'L', 'F' };
            if(memcmp(ELFSTR, gElfBuffer, 4U) != 0)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                elfClass = gElfBuffer[ELFCLASS_IDX];
                if(elfClass == ELFCLASS_64)
                {
                    elfPtr64 = (Bootloader_ELFH64 *)gElfBuffer;
                    numSegments = elfPtr64->ePhnum;

                    /* Check if number of PHT entries are <= MAX */
                    if (numSegments > ELF_MAX_SEGMENTS)
                    {
                        status = SystemP_FAILURE;
                    }

                    if(elfPtr64->eVersion != (uint32_t)SW_VERSION)
                    {
                        DebugP_logWarn("Software version mismatch, Installer version 0x%x, \
                        AppImage version 0x%x\n\r", SW_VERSION, elfPtr64->eVersion);
                        status = SystemP_FAILURE;
                    }

                    if(status == SystemP_SUCCESS)
                    {
                        elfPhdrPtr64 = (Bootloader_ELFPH64*) &gElfBuffer[elfPtr64->ePhoff];

                        /* Note segment is always first */
                        noteSegInfo.noteSegmentSz = elfPhdrPtr64[0].filesz;
                        noteSegInfo.noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[elfPhdrPtr64[0].offset];
                        noteSegInfo.noteSegmentOffset = elfPhdrPtr64[0].offset;
                    }
                }
                else if(elfClass == ELFCLASS_32)
                {
                    elfPtr32 = (Bootloader_ELFH32 *)gElfBuffer;
                    numSegments = elfPtr32->ePhnum;

                    /* Check if number of PHT entries are <= MAX */
                    if (numSegments > ELF_MAX_SEGMENTS)
                    {
                        status = SystemP_FAILURE;
                    }

                    if(elfPtr32->eVersion != (uint32_t)SW_VERSION)
                    {
                        DebugP_logWarn("Software version mismatch, Installer version 0x%x, \
                        AppImage version 0x%x\n\r", SW_VERSION, elfPtr32->eVersion);
                        status = SystemP_FAILURE;
                    }

                    if(status == SystemP_SUCCESS)
                    {
                        elfPhdrPtr32 = (Bootloader_ELFPH32 *) &gElfBuffer[elfPtr32->ePhoff];

                        /* Note segment is always first */
                        noteSegInfo.noteSegmentSz = elfPhdrPtr32[0].filesz;
                        noteSegInfo.noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[elfPhdrPtr32[0].offset];
                        noteSegInfo.noteSegmentOffset = elfPhdrPtr32[0].offset;
                    }
                }
                else
                {
                    status = SystemP_FAILURE;
                }

                if(status == SystemP_SUCCESS)
                {
                    /* Parse the note segment */
                    status = Bootloader_parseNoteSegment(handle, bootImageInfo, &noteSegInfo, elfClass);
                }
            }
        }

        if(status == SystemP_SUCCESS)
        {
            uint32_t i = 1U, cslCoreId = 0U, mcelfCoreId = 0;

            if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
            {
                Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                /* Enable OSPI Phy if configured to do so */
                flashArgs->enablePhyPipeline = TRUE;
                status = config->fxns->imgCustomFxn(config->args);
            }

            if(elfClass == ELFCLASS_32)
            {
                if(status == SystemP_SUCCESS)
                {
                    for(i = 1U; i < elfPtr32->ePhnum; i++)
                    {
                        mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr+ (i-1));
                        cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                        if(!initCpuDone[cslCoreId])
                        {
                            status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                            initCpuDone[cslCoreId] = 1;
                        }

                        if (status == SystemP_SUCCESS)
                        {
                            if(elfPhdrPtr32[i].filesz != 0 && elfPhdrPtr32[i].type == PT_LOAD)
                            {
                                uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr32[i].vaddr);
                                uint32_t loadAddr = addr;

                                /* Add check for SBL reserved memory */
                                Bootloader_resMemSections *resMem;
                                uint32_t resSectionCnt, start, end;
                                resMem = Bootloader_socGetSBLMem();
                                for (resSectionCnt = 0; resSectionCnt < resMem->numSections; resSectionCnt++)
                                {
                                    start = resMem->memSection[resSectionCnt].memStart;
                                    end = resMem->memSection[resSectionCnt].memEnd;
                                    if((addr > start) && (addr < end))
                                    {
                                        status = SystemP_FAILURE;
                                        DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                        break;
                                    }
                                }

                                if (status == SystemP_SUCCESS)
                                {
                                    /* Move current read position to start of Program segment */
                                    config->fxns->imgSeekFxn(elfPhdrPtr32[i].offset, config->args);

                                    if(Bootloader_socIsDmaRestrictedRegion(addr))
                                    {
                                        if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                        {
                                            loadAddr = elfPhdrPtr32[i].paddr;
                                        }
                                        Bootloader_restrictedRegionCopy(handle, (uint32_t) elfPhdrPtr32[i].filesz, loadAddr);
                                    }
                                    else
                                    {
                                        config->fxns->imgReadFxn((void *)(loadAddr), (uint32_t)elfPhdrPtr32[i].filesz, config->args);
                                    }

                                    ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr32[i].filesz;
                                }
                            }
                            else
                            {
                                /* NO LOAD segment, do nothing */
                            }
                        }

                        if (status != SystemP_SUCCESS)
                        {
                            break;
                        }
                    }
                }
            }
            else if(elfClass == ELFCLASS_64)
            {
                if(status == SystemP_SUCCESS)
                {
                    for(i = 1; i < elfPtr64->ePhnum; i++)
                    {
                        mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1));
                        cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                        if(!initCpuDone[cslCoreId])
                        {
                            status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                            initCpuDone[cslCoreId] = 1;
                        }

                        if(elfPhdrPtr64[i].filesz != 0 && elfPhdrPtr64[i].type == PT_LOAD)
                        {
                            uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr64[i].vaddr);
                            uint32_t loadAddr = addr;

                            /* Add check for SBL reserved memory */
                            Bootloader_resMemSections *resMem;
                            uint32_t resSectionCnt, start, end;
                            resMem = Bootloader_socGetSBLMem();
                            for (resSectionCnt = 0; resSectionCnt < resMem->numSections; resSectionCnt++)
                            {
                                start = resMem->memSection[resSectionCnt].memStart;
                                end = resMem->memSection[resSectionCnt].memEnd;
                                if((addr > start) && (addr < end))
                                {
                                    status = SystemP_FAILURE;
                                    DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                    break;
                                }
                            }

                            if (status == SystemP_SUCCESS)
                            {
                                /* Move current read position to start of Program segment */
                                config->fxns->imgSeekFxn(((uint32_t) elfPhdrPtr64[i].offset), config->args);

                                if(Bootloader_socIsDmaRestrictedRegion(addr))
                                {
                                    if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                    {
                                        loadAddr = elfPhdrPtr64[i].paddr;
                                    }
                                    Bootloader_restrictedRegionCopy(handle, (uint32_t) elfPhdrPtr64[i].filesz, loadAddr);
                                }
                                else
                                {
                                    config->fxns->imgReadFxn((void *)(addr), (uint32_t) elfPhdrPtr64[i].filesz, config->args);
                                }

                                ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr64[i].filesz;
                            }
                        }
                        else
                        {
                            /* NO LOAD segment, do nothing */
                        }

                        if (status != SystemP_SUCCESS)
                        {
                            break;
                        }
                    }
                }
            }
        }

#endif
    }
    return status;
}

int32_t Bootloader_bootCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_initCpu(handle, cpuInfo);

    if(status == SystemP_SUCCESS)
    {
        status = Bootloader_runCpu(handle, cpuInfo);
    }

    return status;
}

/* This API should only be called after the bootimage is parsed */
uint32_t Bootloader_isCorePresent(Bootloader_Handle handle, uint32_t cslCoreId)
{
    uint32_t retVal = 0U;

    if(handle != NULL)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        if((config->coresPresentMap & ((uint32_t)1 << cslCoreId)) != (uint32_t)0)
        {
            retVal = 1U;
        }
    }

    return retVal;
}

void Bootloader_CpuInfo_init(Bootloader_CpuInfo *cpuInfo)
{
    cpuInfo->cpuId = CSL_CORE_ID_MAX;
    cpuInfo->clkHz = 0U;
    cpuInfo->entryPoint = (uintptr_t)BOOTLOADER_INVALID_ID;
    cpuInfo->smpEnable  = false;
}

void Bootloader_BootImageInfo_init(Bootloader_BootImageInfo *bootImageInfo)
{
    uint16_t i;

    for(i=0U; i<(uint16_t)CSL_CORE_ID_MAX; i++)
    {
        Bootloader_CpuInfo_init(&bootImageInfo->cpuInfo[i]);
        bootImageInfo->cpuInfo[i].cpuId = (uint32_t)i;
        bootImageInfo->cpuInfo[i].clkHz = Bootloader_socCpuGetClkDefault((uint32_t)i);
    }
}

static int32_t Bootloader_initCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t numOfCores;
    uint8_t core;

    uint32_t *selfCpuList  = Bootloader_socGetSelfCpuList();

    if(cpuInfo->smpEnable == true)
    {
        numOfCores = FREERTOS_SMP_NO_OF_CORES;
    }
    else
    {
        numOfCores = 1U;
    }

    for( core = 0U; core < numOfCores; core ++)
    {
        if(cpuInfo->cpuId == selfCpuList[0U])
        {
            status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

            if(SystemP_SUCCESS == status)
            {
                uintptr_t entryPoint = cpuInfo->entryPoint;

                if( cpuInfo->entryPoint == BOOTLOADER_INVALID_ID)
                {
                    entryPoint = 0U;
                }
                status = Bootloader_socCpuSetEntryPoint(cpuInfo->cpuId, entryPoint);
            }

            if(SystemP_SUCCESS == status)
            {
                status = Bootloader_socMemInitCpu(cpuInfo->cpuId);
            }
        }
        else
        {
            Bootloader_Config *config = (Bootloader_Config *)handle;

            status = Bootloader_socEnableDomain(cpuInfo->cpuId, &gCoresBootedMap);

            if(SystemP_SUCCESS == status)
            {
                status = Bootloader_socCpuRequest(cpuInfo->cpuId);
            }

            if(SystemP_SUCCESS == status)
            {
                status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                if(SystemP_SUCCESS == status)
                {
                    status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId,config->socCoreOpMode);

                    gCoresBootedMap = gCoresBootedMap | (1U << cpuInfo->cpuId);
                }
            }
        }

        if(SystemP_SUCCESS != status)
        {
            break;
        }

        cpuInfo ++;
    }

    return status;
}

static int32_t Bootloader_parseNoteSegment(Bootloader_Handle handle,
                                    Bootloader_BootImageInfo *bootImageInfo,
                                    Bootloader_NoteSegInfo *noteSegInfo,
                                    uint8_t elfClass)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t idx = 0U, sgMpIdx = 0U, alignSize = 4U, mcelfCoreId = 0U, cslCoreId = 0U;
    uint32_t noteSegmentStart = 0U;
    uint32_t numEntries = 0U, i =0U;
    Bootloader_CpuInfo *cpuInfo = NULL;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    noteSegmentStart = (uint32_t) &noteSegInfo->noteSegmentPtr->namesz;

    while(idx < noteSegInfo->noteSegmentSz)
    {
        /* Read the type */
        idx += (ELF_NOTE_NAMESZ_SIZE + ELF_NOTE_DESCSZ_SIZE + ELF_NOTE_TYPE_SIZE);
        if(noteSegInfo->noteSegmentPtr->type == ENTRY_POINTS_NOTE_TYPE)
        {
            idx += noteSegInfo->noteSegmentPtr->namesz;
            if((noteSegInfo->noteSegmentPtr->namesz % alignSize) != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }

            if(elfClass == ELFCLASS_32)
            {
                numEntries = noteSegInfo->noteSegmentPtr->descsz / 8U;
                for (i = 0U; i < numEntries; i++)
                {
                    mcelfCoreId = gElfBuffer[noteSegInfo->noteSegmentOffset + idx];
                    cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);
                    cpuInfo = &bootImageInfo->cpuInfo[cslCoreId];

                    cpuInfo->entryPoint = (uint32_t)(((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 4U]) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 5U] << 8U) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 6U] << 16U) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 7U] << 24U));

                    if (Bootloader_socIsSmpEnable(mcelfCoreId) == true)
                    {
                        cpuInfo->smpEnable = true;
                    }

                    config->coresPresentMap |= ((uint32_t)1U << cslCoreId);

                    idx += 8U;
                }
            }
            else if(elfClass == ELFCLASS_64)
            {
                numEntries = noteSegInfo->noteSegmentPtr->descsz / 12U;
                for (i = 0U; i < numEntries; i++)
                {
                    mcelfCoreId = gElfBuffer[noteSegInfo->noteSegmentOffset + idx];
                    cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);
                    cpuInfo = &bootImageInfo->cpuInfo[cslCoreId];

                    cpuInfo->entryPoint = (uint32_t)(((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 4U]) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 5U] << 8U) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 6U] << 16U) | \
                                                    ((uint32_t)gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 7U] << 24U));

                    if (Bootloader_socIsSmpEnable(mcelfCoreId) == true)
                    {
                        cpuInfo->smpEnable = true;
                    }

                    config->coresPresentMap |= ((uint32_t)1U << cslCoreId);

                    idx += 12U;
                }
            }
            else
            {
                /* do nothing */
            }

            break;
        }
        else if(noteSegInfo->noteSegmentPtr->type == SEGMENT_MAP_NOTE_TYPE)
        {
            /* Start of values in segment map */
            sgMpIdx = idx + noteSegInfo->noteSegmentPtr->namesz;
            noteSegInfo->noteSegmentMapPtr = &gElfBuffer[noteSegInfo->noteSegmentOffset + sgMpIdx];

            idx += noteSegInfo->noteSegmentPtr->namesz + noteSegInfo->noteSegmentPtr->descsz;
            if((noteSegInfo->noteSegmentPtr->namesz % alignSize) != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }

            if((noteSegInfo->noteSegmentPtr->descsz % alignSize) != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->descsz % alignSize));
            }

            noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *)(noteSegmentStart + idx);
        }
        else if(noteSegInfo->noteSegmentPtr->type == VENDOR_ID_NOTE_TYPE)
        {
            idx += noteSegInfo->noteSegmentPtr->namesz + noteSegInfo->noteSegmentPtr->descsz;
            if((noteSegInfo->noteSegmentPtr->namesz % alignSize) != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }
            if((noteSegInfo->noteSegmentPtr->descsz % alignSize) != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->descsz % alignSize));
            }

            noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *)(noteSegmentStart + idx);
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    if(sgMpIdx == 0U)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    return status;
}

static int32_t Bootloader_authInit(uint32_t certLoadAddr)
{
    int32_t status, authStatus = SystemP_FAILURE;
    struct tisci_security_mesg_mcelf_init_req request;
    struct tisci_security_mesg_mcelf_init_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MCELF_PROC_AUTH_BOOT_INIT;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;
    request.certificate_address_hi = 0U ;
    request.certificate_address_lo = certLoadAddr;

    reqParam.messageType    = (uint16_t) TISCI_MSG_MCELF_PROC_AUTH_BOOT_INIT;
    reqParam.flags          = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0U; /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t)  sizeof (response);

    status = Sciclient_service(&reqParam, &respParam);
    if ((status == SystemP_SUCCESS)  && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        authStatus = SystemP_SUCCESS;
    }
    else
    {
        authStatus = SystemP_FAILURE;
    }

    return authStatus;
}

static int32_t Bootloader_authUpdate(uint32_t segAddr, uint32_t segSize, bool final_pkt, uint64_t dst)
{
    int32_t status;
    struct tisci_security_mesg_mcelf_update_req request;
    struct tisci_security_mesg_mcelf_update_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MCELF_PROC_AUTH_BOOT_UPDATE;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;
    request.address_hi = 0U;
    request.address_lo = segAddr;
    request.segment_size = segSize;
    request.final_pkt = final_pkt;
    request.dest_address = dst;

    reqParam.messageType = (uint16_t)TISCI_MSG_MCELF_PROC_AUTH_BOOT_UPDATE;
    reqParam.flags = (uint32_t)TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload = (const uint8_t *)&request;
    reqParam.reqPayloadSize = (uint32_t)sizeof(request);
    reqParam.timeout = (uint32_t)SystemP_WAIT_FOREVER;


    respParam.flags = (uint32_t)0U; /* Populated by the API */
    respParam.pRespPayload = (uint8_t *)&response;
    respParam.respPayloadSize = (uint32_t)sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

    if ((status == SystemP_SUCCESS) && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Bootloader_authFinish(void)
{
    int32_t status;
    struct tisci_security_mesg_mcelf_finish_req request;
    struct tisci_security_mesg_mcelf_finish_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MCELF_PROC_AUTH_BOOT_FINISH;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;

    reqParam.messageType    = (uint16_t) TISCI_MSG_MCELF_PROC_AUTH_BOOT_FINISH;
    reqParam.flags          = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) SystemP_WAIT_FOREVER;;

    respParam.flags           = (uint32_t) 0U;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t)  sizeof (response);

    status = Sciclient_service(&reqParam, &respParam);
    if ((status == SystemP_SUCCESS)  && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static void Bootloader_restrictedRegionCopy(Bootloader_Handle handle, uint32_t segmentSize, uint32_t loadAddr)
{
    Bootloader_Config *config = (Bootloader_Config *)handle;
    uint32_t bytesRead = 0U;
    uint32_t bytesToRead = 0U;

    while(bytesRead < segmentSize)
    {
        if((segmentSize - bytesRead) > SCRATCH_BUFFER_SIZE)
        {
            bytesToRead = SCRATCH_BUFFER_SIZE;
        }
        else
        {
            bytesToRead = segmentSize - bytesRead;
        }

        config->fxns->imgReadFxn((void *)(config->scratchMemPtr), bytesToRead, config->args);
        memcpy((void *)loadAddr,(void *)(config->scratchMemPtr), bytesToRead);
        CacheP_wb((void *)loadAddr, bytesToRead, CacheP_TYPE_ALL);
        bytesRead += bytesToRead;
        loadAddr += bytesToRead;
    }
}

int32_t Bootloader_UartParseAndLoadMultiCoreELF(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t certLen = 0U;

    Bootloader_ELFH32 *elfPtr32 = NULL;
    Bootloader_ELFPH32 *elfPhdrPtr32 = NULL;

    Bootloader_ELFH64 *elfPtr64 = NULL;
    Bootloader_ELFPH64 *elfPhdrPtr64 = NULL;

    Bootloader_NoteSegInfo noteSegInfo =
    {
        .noteSegmentSz = 0U,
        .noteSegmentOffset = 0U,
        .noteSegmentPtr = NULL,
        .noteSegmentMapPtr = NULL,
    };

    Bootloader_McelfMeta mcelfMetaInfo=
    {
        .certLength = 0U,
        .elfClass = ELFCLASS_32,
        .numSegments = 0U,
        .elfPtr32 = NULL,
        .elfPtr64 = NULL,
        .elfPhdrPtr32 = NULL,
        .elfPhdrPtr64 = NULL,
        .noteSegInfo = &noteSegInfo,
    };

    /* Array to check if core is initialized */
    uint8_t initCpuDone[CSL_CORE_ID_MAX] = {0U};

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if((config->fxns == NULL) || (config->fxns->imgReadFxn == NULL) || (config->fxns->imgSeekFxn == NULL))
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            status = Bootloader_authCertificate(config, &mcelfMetaInfo);
            certLen = mcelfMetaInfo.certLength;

            if(status == SystemP_SUCCESS)
            {
                Bootloader_parseELFMeta(handle, bootImageInfo, &mcelfMetaInfo);
            }

            if(status == SystemP_SUCCESS)
            {
                uint32_t i = 1U, cslCoreId = 0U, mcelfCoreId = 0U;
                bool isFinalPkt = FALSE;

                if(mcelfMetaInfo.elfClass == ELFCLASS_32)
                {
                    elfPtr32 = mcelfMetaInfo.elfPtr32;
                    elfPhdrPtr32 = mcelfMetaInfo.elfPhdrPtr32;

                    /* Loop over the segments and do auth update */
                    for(i = 1U; i < elfPtr32->ePhnum; i++)
                    {
                        mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                        cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                        if(!initCpuDone[cslCoreId])
                        {
                            status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                            initCpuDone[cslCoreId] = 1U;
                        }

                        if (status == SystemP_SUCCESS)
                        {
                            if ((elfPhdrPtr32[i].filesz != 0U) && (elfPhdrPtr32[i].type == PT_LOAD))
                            {
                                uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr32[i].vaddr);
                                uint32_t loadAddr = addr;

                                /* Add check for SBL reserved memory */
                                Bootloader_resMemSections *resMem;
                                uint32_t resSectionCnt, start, end;
                                resMem = Bootloader_socGetSBLMem();
                                for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                                {
                                    start = resMem->memSection[resSectionCnt].memStart;
                                    end = resMem->memSection[resSectionCnt].memEnd;
                                    if((addr > start) && (addr < end))
                                    {
                                        status = SystemP_FAILURE;
                                        DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                        break;
                                    }
                                }

                                if (status == SystemP_SUCCESS)
                                {
                                    if (i == (mcelfMetaInfo.elfPtr32->ePhnum - 1U))
                                    {
                                        isFinalPkt = TRUE;
                                    }

                                    Bootloader_UartArgs *uartArgs = (Bootloader_UartArgs *)(config->args);
                                    if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                    {
                                        loadAddr = elfPhdrPtr32[i].paddr;
                                    }
                                    uartArgs->finalPacket = false;
                                    uartArgs->virtMemOffset = elfPhdrPtr32[i].offset + certLen;
                                    uartArgs->segmentSize = elfPhdrPtr32[i].filesz;
                                    uartArgs->loadAddress = loadAddr;

                                    /* Request the program segment required and store to load address*/
                                    status = config->fxns->imgCustomFxn(config->args);

                                    if(status == SystemP_SUCCESS)
                                    {
                                            /* Do auth init from the load address */
                                        status = Bootloader_authUpdate( addr, \
                                                                (uint32_t) elfPhdrPtr32[i].filesz, \
                                                                isFinalPkt, \
                                                                (uint64_t) addr);
                                    }

                                    ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr32[i].filesz;
                                }
                            }
                            else
                            {
                                /* NO LOAD segment, do nothing */
                            }
                        }

                        if (status != SystemP_SUCCESS)
                        {
                            break;
                        }
                    }
                }
                else if(mcelfMetaInfo.elfClass == ELFCLASS_64)
                {
                    elfPtr64 = mcelfMetaInfo.elfPtr64;
                    elfPhdrPtr64 = mcelfMetaInfo.elfPhdrPtr64;

                    /* Loop over the segments and do auth update */
                    for(i = 1U; i < elfPtr64->ePhnum; i++)
                    {
                        mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                        cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                        if(!initCpuDone[cslCoreId])
                        {
                            status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                            initCpuDone[cslCoreId] = 1;
                        }

                        if((elfPhdrPtr64[i].filesz != 0U) && (elfPhdrPtr64[i].type == PT_LOAD))
                        {
                            uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr64[i].vaddr);
                            uint32_t loadAddr = addr;

                            /* Add check for SBL reserved memory */
                            Bootloader_resMemSections *resMem;
                            uint32_t resSectionCnt, start, end;
                            resMem = Bootloader_socGetSBLMem();
                            for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                            {
                                start = resMem->memSection[resSectionCnt].memStart;
                                end = resMem->memSection[resSectionCnt].memEnd;
                                if((addr > start) && (addr < end))
                                {
                                    status = SystemP_FAILURE;
                                    DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                    break;
                                }
                            }

                            if (status == SystemP_SUCCESS)
                            {
                                if (i == (mcelfMetaInfo.elfPtr64->ePhnum - 1U))
                                {
                                    isFinalPkt = TRUE;
                                }
                                if(cslCoreId == CSL_CORE_ID_WKUP_R5FSS0_0)
                                {
                                    loadAddr = (uint32_t) elfPhdrPtr64[i].paddr;
                                }

                                /* Request the program segment required and store to load address*/
                                Bootloader_UartArgs *uartArgs = (Bootloader_UartArgs *)(config->args);
                                uartArgs->loadAddress = loadAddr;

                                uartArgs->finalPacket = false;
                                uartArgs->virtMemOffset = elfPhdrPtr64[i].offset + certLen;
                                uartArgs->segmentSize = elfPhdrPtr64[i].filesz;
                                uartArgs->loadAddress = loadAddr;

                                status = config->fxns->imgCustomFxn(config->args);

                                if(status == SystemP_SUCCESS)
                                {
                                        /* Do auth init from the load address */
                                    status = Bootloader_authUpdate( addr, \
                                                            (uint32_t) elfPhdrPtr64[i].filesz, \
                                                            isFinalPkt, \
                                                            (uint64_t) addr);
                                }

                                ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr64[i].filesz;
                            }
                        }
                        else
                        {
                            /* NO LOAD segment, do nothing */
                        }

                        if (status != SystemP_SUCCESS)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    /* do nothing */
                }

            }
            if(status == SystemP_SUCCESS)
            {
                /* Send the transfer complete ack to host */
                Bootloader_UartArgs *uartArgs = (Bootloader_UartArgs *)(config->args);
                uartArgs->finalPacket = true;
                status = config->fxns->imgCustomFxn(config->args);

            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_authFinish();
            }

        }
    }
    return status;
}

int32_t Bootloader_authCertificate(Bootloader_Config *config, Bootloader_McelfMeta *mcelfMetaInfo)
{
        int32_t status = SystemP_SUCCESS;
        uint32_t certLen = 0U;
        uint8_t x509Header[4U];
        uint32_t certLoadAddr = 0xFFFFFFFFU;

        /* Read the x509 certificate header */
        config->fxns->imgSeekFxn(0U, config->args);
        config->fxns->imgReadFxn(x509Header, 4U, config->args);
        certLen = Bootloader_getX509CertLen(x509Header);
        mcelfMetaInfo->certLength = certLen;

        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
            {
                Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                if(flashArgs->flashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
                {
                    certLoadAddr = FLASH_BASE_ADDRESS + flashArgs->appImageOffset;

                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);
                }
            }
            else if(config->bootMedia == BOOTLOADER_MEDIA_SD  || config->bootMedia == BOOTLOADER_MEDIA_EMMC)
            {
                memcpy(config->scratchMemPtr, x509Header, X509CERT_HEADER_SIZE);
                config->fxns->imgReadFxn((config->scratchMemPtr+X509CERT_HEADER_SIZE), (certLen-X509CERT_HEADER_SIZE), config->args);
                certLoadAddr = (uint32_t)(config->scratchMemPtr);
            }
            else if(config->bootMedia == BOOTLOADER_MEDIA_UART)
            {
                Bootloader_UartArgs *uartArgs = (Bootloader_UartArgs *)(config->args);
                certLoadAddr = (uint32_t)(uartArgs->appImageBaseAddr);
            }
            else
            {
                /* do nothing */
            }

            /* Check if the certificate length is within valid range */
            if((certLen > (uint32_t)0x100U) && (certLen < (uint32_t)0x800U) && status == SystemP_SUCCESS)
            {
                status = Bootloader_authInit(certLoadAddr);
            }
        }

        return status;
}

int32_t Bootloader_parseELFMeta(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo, Bootloader_McelfMeta *mcelfMetaInfo)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    config->fxns->imgSeekFxn(mcelfMetaInfo->certLength, config->args);
    /* Read the ELF metadata from the bootmedia */
    status = config->fxns->imgReadFxn(gElfBuffer, BOOTLOADER_MCELF_META_DATA_SIZE_MAX, config->args);

    char elfStr[] = { 0x7F, 'E', 'L', 'F' };
    if (memcmp(elfStr, gElfBuffer, sizeof(elfStr)) != 0U)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        mcelfMetaInfo->elfClass = gElfBuffer[ELFCLASS_IDX];
        if(mcelfMetaInfo->elfClass == ELFCLASS_64)
        {
            mcelfMetaInfo->elfPtr64 = (Bootloader_ELFH64 *)gElfBuffer;
            mcelfMetaInfo->numSegments = mcelfMetaInfo->elfPtr64->ePhnum;

            /* Check if number of PHT entries are <= MAX */
            if (mcelfMetaInfo->numSegments > ELF_MAX_SEGMENTS)
            {
                status = SystemP_FAILURE;
            }

            if(mcelfMetaInfo->elfPtr64->eVersion != (uint32_t)SW_VERSION)
            {
                DebugP_logWarn("Software version mismatch, Installer version 0x%x, \
                 AppImage version 0x%x\n\r", SW_VERSION, mcelfMetaInfo->elfPtr64->eVersion);
                status = SystemP_FAILURE;
            }

            if(status == SystemP_SUCCESS)
            {
                mcelfMetaInfo->elfPhdrPtr64 = (Bootloader_ELFPH64*) &gElfBuffer[mcelfMetaInfo->elfPtr64->ePhoff];
                /* Note segment is always first */
                mcelfMetaInfo->noteSegInfo->noteSegmentSz = mcelfMetaInfo->elfPhdrPtr64[0U].filesz;
                mcelfMetaInfo->noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[mcelfMetaInfo->elfPhdrPtr64[0U].offset];
                mcelfMetaInfo->noteSegInfo->noteSegmentOffset = mcelfMetaInfo->elfPhdrPtr64[0U].offset;

                /* Do auth update for the elf header, PHT and note segment */
                status = Bootloader_authUpdate((uint32_t) &gElfBuffer[0U], \
                                            (uint32_t) mcelfMetaInfo->elfPtr64->eEhsize + \
                                            (mcelfMetaInfo->elfPtr64->ePhnum * mcelfMetaInfo->elfPtr64->ePhentsize) + \
                                            mcelfMetaInfo->elfPhdrPtr64[0U].filesz, \
                                            FALSE, \
                                            (uint64_t) &gElfBuffer[0U]);
            }
        }
        else if(mcelfMetaInfo->elfClass == ELFCLASS_32)
        {
            mcelfMetaInfo->elfPtr32 = (Bootloader_ELFH32 *)gElfBuffer;
            mcelfMetaInfo->numSegments = mcelfMetaInfo->elfPtr32->ePhnum;

            /* Check if number of PHT entries are <= MAX */
            if (mcelfMetaInfo->numSegments > ELF_MAX_SEGMENTS)
            {
                status = SystemP_FAILURE;
            }

            if(mcelfMetaInfo->elfPtr32->eVersion != (uint32_t)SW_VERSION)
            {
                DebugP_logWarn("Software version mismatch, Installer version 0x%x, \
                 AppImage version 0x%x\n\r", SW_VERSION, mcelfMetaInfo->elfPtr32->eVersion);
                status = SystemP_FAILURE;
            }

            if(status == SystemP_SUCCESS)
            {
                mcelfMetaInfo->elfPhdrPtr32 = (Bootloader_ELFPH32*) &gElfBuffer[mcelfMetaInfo->elfPtr32->ePhoff];
                /* Note segment is always first */
                mcelfMetaInfo->noteSegInfo->noteSegmentSz = mcelfMetaInfo->elfPhdrPtr32[0U].filesz;
                mcelfMetaInfo->noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[mcelfMetaInfo->elfPhdrPtr32[0U].offset];
                mcelfMetaInfo->noteSegInfo->noteSegmentOffset = mcelfMetaInfo->elfPhdrPtr32[0U].offset;

                /* Do auth update for the elf header, PHT and note segment */
                status = Bootloader_authUpdate((uint32_t) &gElfBuffer[0U], \
                                            (uint32_t) mcelfMetaInfo->elfPtr32->eEhsize + \
                                            (mcelfMetaInfo->elfPtr32->ePhnum * mcelfMetaInfo->elfPtr32->ePhentsize) + \
                                            (mcelfMetaInfo->elfPhdrPtr32)[0U].filesz, \
                                            FALSE, \
                                            (uint64_t) &gElfBuffer[0U]);
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            /* Parse the note segment */
            status = Bootloader_parseNoteSegment(handle, bootImageInfo, mcelfMetaInfo->noteSegInfo, mcelfMetaInfo->elfClass);
        }
    }

    return status;
}