/*
 *  Copyright (C) 2024-25 Texas Instruments Incorporated
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
 *  \file bootloader_rprc.c
 *
 *  \brief Bootloader RPRC Driver API source file.
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*RPRC image ID for linux load only images */
#define RPRC_LINUX_LOAD_ONLY_IMAGE_ID ((uint32_t)21)
#define FLASH_BASE_ADDRESS            (CSL_FSS0_DAT_REG1_BASE)

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

extern Bootloader_Config gBootloaderConfig[];
extern Bootloader_Config gMemBootloaderConfig;
extern uint32_t gBootloaderConfigNum;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Bootloader_getMemBootloaderConfig(Bootloader_Config *config, Bootloader_MemArgs *memArgs);

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

int32_t Bootloader_loadSelfCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t cpuId = cpuInfo->cpuId;
#if !defined(SOC_AM62X) && !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62PX) && !defined(SOC_J722S)
    status = Bootloader_socCpuRequest(cpuId);
#endif
    if(SystemP_SUCCESS == status)
    {
        status = Bootloader_socCpuSetClock(cpuId, cpuInfo->clkHz);
    }
    if(SystemP_SUCCESS == status)
    {
        if( cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
        {
            status = Bootloader_rprcImageParseEntryPoint(handle, cpuInfo);
        }
    }
    if(SystemP_SUCCESS == status)
    {
        uintptr_t entryPoint = cpuInfo->entryPoint;

        if( cpuInfo->rprcOffset == BOOTLOADER_INVALID_ID)
        {
            entryPoint = 0;
        }
        status = Bootloader_socCpuSetEntryPoint(cpuId, entryPoint);
    }
    if(SystemP_SUCCESS == status)
    {
        status = Bootloader_socMemInitCpu(cpuId);
    }
    if(SystemP_SUCCESS == status)
    {
        if( cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
        {
            status = Bootloader_rprcImageLoad(handle, cpuInfo);
        }
    }
    if(status == SystemP_SUCCESS)
    {
        uint64_t cpuHz;

        cpuHz = Bootloader_socCpuGetClock(cpuId);
        if(cpuHz > (uint64_t)0)
        {
            DebugP_logInfo("CPU %s is initialized to %d Hz !!!\r\n", Bootloader_socGetCoreName(cpuId), (uint32_t)cpuHz);
        }
    }
    return status;
}

int32_t Bootloader_loadCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t numOfCores;
    uint8_t core;
    uintptr_t smpEntryPoint = 0U;

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
        status = Bootloader_socCpuRequest(cpuInfo->cpuId);

        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

        if(SystemP_SUCCESS == status)
        {
            Bootloader_Config *config = (Bootloader_Config *)handle;
            status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId,config->socCoreOpMode);
        }

        if(SystemP_SUCCESS == status)
        {
            if(cpuInfo->smpEnable == true)
            {
                if(cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                {
                    if(FREERTOS_SMP_BOOT_CORE == cpuInfo->cpuId)
                    {
                        status = Bootloader_rprcImageLoad(handle, cpuInfo);
                        smpEntryPoint = cpuInfo->entryPoint;
                    }
                    else
                    {
                        cpuInfo->entryPoint = smpEntryPoint;
                    }
                }
            }
            else
            {
                if( cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                {
                    status = Bootloader_rprcImageLoad(handle, cpuInfo);
                }
            }
        }
        cpuInfo ++;
    }

    return status;
}

int32_t Bootloader_bootCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_loadCpu(handle, cpuInfo);

    if(status == SystemP_SUCCESS)
    {
        status = Bootloader_runCpu(handle, cpuInfo);
    }

    return status;
}

int32_t Bootloader_bootSelfCpu(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i = 0;
    uint32_t *selfCpuList  = Bootloader_socGetSelfCpuList();

    while( selfCpuList[i] != BOOTLOADER_INVALID_ID)
    {
        status = Bootloader_loadSelfCpu(handle, &bootImageInfo->cpuInfo[ selfCpuList[i] ] );
        if(status!=SystemP_SUCCESS)
        {
            break;
        }
        i++;
    }

    if(status == SystemP_SUCCESS)
    {
        status = Bootloader_runSelfCpu(handle, bootImageInfo);
    }

    return status;
}

int32_t Bootloader_rprcImageLoad(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    Bootloader_RprcFileHeader     header;
    Bootloader_RprcSectionHeader section;

    int32_t status = SystemP_SUCCESS;

    Bootloader_Config *config = (Bootloader_Config *)handle;
    Bootloader_Config memConfig = {0U};
    Bootloader_MemArgs memArgs = {0U};

    if((config) && (config->args))
    {
        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            Bootloader_getMemBootloaderConfig(&memConfig, &memArgs);

            /* Initialize the appimage base address according to the boot media */
            if(config->bootMedia != BOOTLOADER_MEDIA_MEM)
            {
                ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = (uint32_t)config->scratchMemPtr;
            }
            else
            {
                ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = ((Bootloader_MemArgs*)(config->args))->appImageBaseAddr;
            }

            memConfig.fxns->imgSeekFxn(0U, memConfig.args);
        }
        else
        {
            memConfig = *config;
        }

        memConfig.fxns->imgSeekFxn(cpuInfo->rprcOffset, memConfig.args);
        status = memConfig.fxns->imgReadFxn(&header, sizeof(Bootloader_RprcFileHeader), memConfig.args);

        if((header.magic != (uint32_t)BOOTLOADER_RPRC_MAGIC_NUMBER) || (header.version != (uint32_t)SW_VERSION))
        {
            if(header.version != (uint32_t)SW_VERSION)
            {
                DebugP_logWarn("Software version mismatch, Installer version 0x%x, AppImage version 0x%x\n\r", SW_VERSION, header.version);
            }
            status = SystemP_FAILURE;
        }
        else
        {
            cpuInfo->entryPoint = (uintptr_t)header.entry;

            uint32_t i;

            for(i=0; i<header.sectionCount; i++)
            {
                status = memConfig.fxns->imgReadFxn(&section, sizeof(Bootloader_RprcSectionHeader), memConfig.args);

                section.addr = Bootloader_socTranslateSectionAddr(cpuInfo->cpuId, section.addr);

                /* Add check for SBL reserved memory */
                Bootloader_resMemSections *resMem;
                uint32_t resSectionCnt, start, end;
                resMem = Bootloader_socGetSBLMem();
                for (resSectionCnt = 0; resSectionCnt < resMem->numSections; resSectionCnt++)
                {
                    start = resMem->memSection[resSectionCnt].memStart;
                    end = resMem->memSection[resSectionCnt].memEnd;
                    if((section.addr > start) && (section.addr < end))
                    {
                        status = SystemP_FAILURE;
                        DebugP_logError("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", section.addr);
                        break;
                    }
                }
                if (status == SystemP_SUCCESS)
                {
                    status = memConfig.fxns->imgReadFxn((void *)(uintptr_t)(section.addr), section.size, memConfig.args);
                    config->bootImageSize += section.size;
                }
            }
        }
      }
      else{/* do nothing */}

    return status;
}

int32_t Bootloader_verifyMulticoreImage(Bootloader_Handle handle)
{
    int32_t status = SystemP_SUCCESS, authStatus = SystemP_FAILURE;
    static int32_t flashAuthStatus = SystemP_SUCCESS;
    uint32_t certLen = 0U, imageLen = 0U, ddrCopy = 1U;
    uint32_t certLoadAddr = 0xFFFFFFFFU;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if((config->fxns->imgReadFxn == NULL) || (config->fxns->imgSeekFxn == NULL))
    {
        status = SystemP_FAILURE;
    }
    else
    {
        uint8_t x509Header[4];
        if(config->bootMedia == BOOTLOADER_MEDIA_MEM)
        {
            Bootloader_MemArgs *memArgs = (Bootloader_MemArgs *)(config->args);
            certLoadAddr = memArgs->appImageBaseAddr;
            config->fxns->imgReadFxn(x509Header, 4, config->args);
            config->fxns->imgSeekFxn(0, config->args);

            certLen = Bootloader_getX509CertLen(x509Header);
            imageLen = Bootloader_getMsgLen((uint8_t *)certLoadAddr, certLen);

            /* Get the 128B cache-line aligned image length */
            uint32_t cacheAlignedLen = (certLen + imageLen + (uint32_t)128) & ~((uint32_t)127);

            /* Write back and invalidate the cache before passing to HSM */
            CacheP_wbInv((void *)certLoadAddr, cacheAlignedLen, CacheP_TYPE_ALL);
        }
        else if((config->bootMedia == BOOTLOADER_MEDIA_FLASH) || (config->bootMedia == BOOTLOADER_MEDIA_EMMC))
        {
            config->fxns->imgReadFxn(x509Header, 4, config->args);
            config->fxns->imgSeekFxn(0, config->args);

            certLen = Bootloader_getX509CertLen(x509Header);

            if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
            {
                Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);

                if((flashArgs->flashType == CONFIG_FLASH_TYPE_SERIAL_NOR) && (flashAuthStatus == SystemP_SUCCESS))
                {
                    ddrCopy = 0;

                    certLoadAddr = FLASH_BASE_ADDRESS + flashArgs->appImageOffset;
                    imageLen = Bootloader_getMsgLen((uint8_t *)(certLoadAddr), certLen);

                    /* Invalidate 128B cache-line aligned destination region before TIFS writes to it */
                    CacheP_inv((void *)config->scratchMemPtr, (imageLen + (uint32_t)128) & ~((uint32_t)127), CacheP_TYPE_ALL);

                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);

                    flashAuthStatus = Bootloader_socAuthImage(certLoadAddr);

                    if(flashAuthStatus == SystemP_FAILURE)
                    {
                        DebugP_logWarn("Failed to authenticate and copy on the go, reading the image to DDR.\n\r");
                        ddrCopy = 1;
                    }
                    else
                    {
                        authStatus = SystemP_SUCCESS;
                    }
                }
                else
                {
                    certLoadAddr = flashArgs->appImageOffset;
                }
            }
#if defined (DRV_VERSION_MMCSD_V0) || defined (DRV_VERSION_MMCSD_V1)
            if(config->bootMedia == BOOTLOADER_MEDIA_EMMC)
            {
                Bootloader_MmcsdArgs *mmcsdArgs = (Bootloader_MmcsdArgs *)(config->args);
                certLoadAddr = mmcsdArgs->appImageOffset;
            }
#endif

            if((config->scratchMemPtr != NULL) && (ddrCopy == 1U))
            {
                config->fxns->imgReadFxn((void *)config->scratchMemPtr, 0x800, config->args);

                imageLen = Bootloader_getMsgLen((uint8_t *)config->scratchMemPtr, certLen);

                uint32_t totalLen = (certLen + imageLen + (uint32_t)128) & ~((uint32_t)127);

                config->fxns->imgSeekFxn(0, config->args);
                config->fxns->imgReadFxn((void *)config->scratchMemPtr, totalLen, config->args);

                certLoadAddr = (uint32_t)(&(config->scratchMemPtr[0]));

                config->fxns->imgSeekFxn(0, config->args);

                /* Get the 128B cache-line aligned image length */
                uint32_t cacheAlignedLen = (certLen + imageLen + (uint32_t)128) & ~((uint32_t)127);

                /* Write back and invalidate the cache before passing to HSM */
                CacheP_wbInv((void *)certLoadAddr, cacheAlignedLen, CacheP_TYPE_ALL);
            }
        }

        /* Check if the certificate length is within valid range */
        if((certLen > (uint32_t)0x100) && (certLen < (uint32_t)0x800) && (status == SystemP_SUCCESS))
        {
            if(authStatus != SystemP_SUCCESS)
            {
                authStatus = Bootloader_socAuthImage(certLoadAddr);
            }

            if(config->bootMedia == BOOTLOADER_MEDIA_BUFIO)
            {
                /* Authentication will fail in Buf Io because we don't have full data yet, so make it pass here for testing. Default behaviour is to assert. */
                /* authStatus = SystemP_SUCCESS; */
                DebugP_assertNoLog(authStatus == SystemP_SUCCESS);
            }

            if(authStatus == SystemP_FAILURE)
            {
                DebugP_logError("Failed to authenticate Image\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Authentication passed, all good. Now re-init bootloader params to point to image start instead of start of x509 certificate */
                if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
                {
                    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                    flashArgs->curOffset = flashArgs->appImageOffset;

                    if(flashArgs->flashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
                    {
                        /* Disable only the PHY pipeline*/
                        flashArgs->enablePhyPipeline = FALSE;
                        status = config->fxns->imgCustomFxn(config->args);
                    }
                }
                else if(config->bootMedia == BOOTLOADER_MEDIA_BUFIO)
                {
                    Bootloader_BufIoArgs *bufIoArgs = (Bootloader_BufIoArgs *)(config->args);
                    bufIoArgs->curOffset = bufIoArgs->appImageOffset;
                }
#if defined (DRV_VERSION_MMCSD_V0) || defined (DRV_VERSION_MMCSD_V1)
                else if(config->bootMedia == BOOTLOADER_MEDIA_EMMC)
                {
                    Bootloader_MmcsdArgs *mmcsdArgs = (Bootloader_MmcsdArgs *)(config->args);
                    mmcsdArgs->curOffset = mmcsdArgs->appImageOffset;
                }
#endif
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }

    }

    return status;
}

int32_t Bootloader_parseMultiCoreAppImage(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t rprcCoreId;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config)
    {
        if((config->fxns->imgReadFxn == NULL) || (config->fxns->imgSeekFxn == NULL))
        {
            status = SystemP_FAILURE;
        }
        else
        {
            Bootloader_MetaHeaderStart mHdrStr;
            Bootloader_MetaHeaderCore  mHdrCore[BOOTLOADER_MAX_INPUT_FILES];

            /* Verify the multicore image if authentication is required */
            if(Bootloader_socIsAuthRequired() == (uint32_t)1)
            {
                /* Device is HS, verify image. */
                status = Bootloader_verifyMulticoreImage(handle);
            }
            else
            {
                /* Device is GP, no authentication required */
                status = SystemP_SUCCESS;
            }

            if(SystemP_SUCCESS == status)
            {
                Bootloader_Config memConfig = {0U};
                Bootloader_MemArgs memArgs = {0U};

                if((config) && (config->args))
                {
                    if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
                    {
                        Bootloader_getMemBootloaderConfig(&memConfig, &memArgs);

                        /* Initialize the appimage base address according to the boot media */
                        if(config->bootMedia != BOOTLOADER_MEDIA_MEM)
                        {
                            ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = (uint32_t)config->scratchMemPtr;
                        }
                        else
                        {
                            ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = ((Bootloader_MemArgs*)(config->args))->appImageBaseAddr;
                        }

                        config->coresPresentMap = 0;
                        memConfig.fxns->imgSeekFxn(0U, memConfig.args);
                    }
                    else
                    {
                        memConfig = *config;
                    }

                    memset(&mHdrCore[0], 0xFF, BOOTLOADER_MAX_INPUT_FILES*sizeof(Bootloader_MetaHeaderCore));

                    status = memConfig.fxns->imgReadFxn(&mHdrStr, sizeof(Bootloader_MetaHeaderStart), memConfig.args);

                    if(mHdrStr.magicStr != (uint32_t)BOOTLOADER_META_HDR_MAGIC_STR)
                    {
                        status = SystemP_FAILURE;
                    }
                    else
                    {
                        /* TODO */
                        /* Check for device Id later if needed, just a warning */

                        /* Read all the core offset addresses */
                        uint32_t i;

                        for(i=0U; i<mHdrStr.numFiles; i++)
                        {
                            status = memConfig.fxns->imgReadFxn(&mHdrCore[i], sizeof(Bootloader_MetaHeaderCore), memConfig.args);
                            /* TODO: Figure out how to add boot media specific offset */
                        }

                        /* Parse individual rprc files */
                        for(i=0U; i<mHdrStr.numFiles; i++)
                        {
                            /* Load the load only linux images */
                            rprcCoreId = mHdrCore[i].coreId;
                            if(mHdrCore[i].coreId == RPRC_LINUX_LOAD_ONLY_IMAGE_ID)
                            {
                                Bootloader_CpuInfo load_only_image;
                                load_only_image.rprcOffset = mHdrCore[i].imageOffset;
                                load_only_image.entryPoint = 0;
                                /* Set CPU ID as A53 as linux runs on A53 */
                                load_only_image.cpuId = CSL_CORE_ID_A53SS0_0;

                                if (status == SystemP_SUCCESS)
                                {
                                    status = Bootloader_rprcImageLoad(handle, &load_only_image);
                                }

                                continue;
                            }

                            if(mHdrCore[i].coreId != (0xFFFFFFFFU))
                            {
                                uint32_t cslCoreId = Bootloader_socRprcToCslCoreId(mHdrCore[i].coreId);
                                Bootloader_CpuInfo *cpuInfo = &bootImageInfo->cpuInfo[cslCoreId];
                                cpuInfo->rprcOffset = mHdrCore[i].imageOffset;
                                cpuInfo->entryPoint = 0;
                                cpuInfo->cpuId      = cslCoreId;
                                if(Bootloader_socIsSmpEnable(mHdrCore[i].coreId) == true)
                                {
                                    cpuInfo->smpEnable = true;
                                }
                                config->coresPresentMap |= ((uint32_t)1 << cslCoreId);
                            }
                        }
                        if(Bootloader_socIsSmpEnable(rprcCoreId) == true)
                        {
                            for( i = CSL_CORE_ID_A53SS0_1; i < FREERTOS_SMP_CSL_CORE_ID_MAX; i ++)
                            {
                                Bootloader_CpuInfo *cpuInfo = &bootImageInfo->cpuInfo[i];
                                cpuInfo->rprcOffset = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].rprcOffset;
                                cpuInfo->entryPoint = 0;
                                cpuInfo->cpuId      = i;
                            }
                        }
                    }
                }
                else{/* do nothing */}
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }
    else{/* do nothing */}

    return status;
}

int32_t Bootloader_rprcImageParseEntryPoint(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_RprcFileHeader header;

    Bootloader_Config *config = (Bootloader_Config *)handle;
    Bootloader_Config memConfig = {0U};
    Bootloader_MemArgs memArgs = {0U};

    if((config) && (config->args))
    {
        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            Bootloader_getMemBootloaderConfig(&memConfig, &memArgs);

            /* Initialize the appimage base address according to the boot media */
            if(config->bootMedia != BOOTLOADER_MEDIA_MEM)
            {
                ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = (uint32_t)config->scratchMemPtr;
            }
            else
            {
                ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = ((Bootloader_MemArgs*)(config->args))->appImageBaseAddr;
            }
        }
        else
        {
            memConfig = *config;
        }

        memConfig.fxns->imgSeekFxn(cpuInfo->rprcOffset, memConfig.args);
        status = memConfig.fxns->imgReadFxn(&header, sizeof(Bootloader_RprcFileHeader), memConfig.args);

        cpuInfo->entryPoint = (uintptr_t)header.entry;
    }
    else{/* do nothing */}

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
    cpuInfo->rprcOffset = BOOTLOADER_INVALID_ID;
    cpuInfo->entryPoint = (uintptr_t)BOOTLOADER_INVALID_ID;
    cpuInfo->smpEnable  = false;
}

void Bootloader_BootImageInfo_init(Bootloader_BootImageInfo *bootImageInfo)
{
    uint16_t i;

    for(i=0; i<(uint16_t)CSL_CORE_ID_MAX; i++)
    {
        Bootloader_CpuInfo_init(&bootImageInfo->cpuInfo[i]);
        bootImageInfo->cpuInfo[i].cpuId = (uint32_t)i;
        bootImageInfo->cpuInfo[i].clkHz = Bootloader_socCpuGetClkDefault((uint32_t)i);
    }
}

static void Bootloader_getMemBootloaderConfig(Bootloader_Config *config, Bootloader_MemArgs *memArgs)
{
    if(config && memArgs)
    {
        memcpy(config, &gMemBootloaderConfig, sizeof(Bootloader_Config));
        memcpy(memArgs, gMemBootloaderConfig.args, sizeof(Bootloader_MemArgs));
        config->args = memArgs;
    }

    return;
}

int32_t Bootloader_parseAppImage(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_FAILURE;

    Bootloader_Config *config = (Bootloader_Config *)handle;
    Bootloader_Config memConfig = {0U};
    Bootloader_MemArgs memArgs = {0U};
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore[BOOTLOADER_MAX_INPUT_FILES];

    if(config)
    {
        /* Now the Image is in DDR, use mem functions */
        Bootloader_getMemBootloaderConfig(&memConfig, &memArgs);
        ((Bootloader_MemArgs*)memConfig.args)->appImageBaseAddr = (uint32_t)config->scratchMemPtr;

        config->coresPresentMap = 0U;
        memConfig.fxns->imgSeekFxn(0U, memConfig.args);

        memset(&mHdrCore[0U], 0xFF, BOOTLOADER_MAX_INPUT_FILES*sizeof(Bootloader_MetaHeaderCore));

        status = memConfig.fxns->imgReadFxn(&mHdrStr, sizeof(Bootloader_MetaHeaderStart), memConfig.args);

        if(status == SystemP_SUCCESS)
        {
            if(mHdrStr.magicStr != (uint32_t)BOOTLOADER_META_HDR_MAGIC_STR)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                /* Read all the core offset addresses */
                uint32_t i;

                for(i=0U; i<mHdrStr.numFiles; i++)
                {
                    status = memConfig.fxns->imgReadFxn(&mHdrCore[i], sizeof(Bootloader_MetaHeaderCore), memConfig.args);
                }

                /* Parse individual rprc files */
                for(i=0U; i<mHdrStr.numFiles; i++)
                {

                    if(mHdrCore[i].coreId != (0xFFFFFFFFU))
                    {
                        uint32_t cslCoreId = Bootloader_socRprcToCslCoreId(mHdrCore[i].coreId);
                        Bootloader_CpuInfo *cpuInfo = (&bootImageInfo -> cpuInfo[cslCoreId]);
                        cpuInfo->rprcOffset = mHdrCore[i].imageOffset;
                        cpuInfo->entryPoint = 0;
                        cpuInfo->cpuId      = cslCoreId;
                        config->coresPresentMap |= ((uint32_t)1 << cslCoreId);
                    }

                }

            }
        }
        else
        {
            DebugP_logError("Failed to read image header!!! \r\n");
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}
