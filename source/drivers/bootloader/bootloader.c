/*
 *  Copyright (C) 2021-2023 Texas Instruments Incorporated
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
 *  \file bootloader.c
 *
 *  \brief Bootloader Driver API source file.
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

static Bootloader_Config* Bootloader_getMemBootloaderConfig(Bootloader_Handle handle);

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

Bootloader_Handle Bootloader_open(uint32_t instanceNum, Bootloader_Params *openParams)
{
    Bootloader_Config *config = 0;

    if(instanceNum < gBootloaderConfigNum)
    {
        config = &gBootloaderConfig[instanceNum];
        if(config->fxns && config->fxns->imgOpenFxn && config->args)
        {
            int32_t status;

            status = config->fxns->imgOpenFxn(config->args, openParams);
            if(status != SystemP_SUCCESS)
            {
                config = NULL;
            }
        }
    }

    return (Bootloader_Handle)config;
}

void Bootloader_close(Bootloader_Handle handle)
{
    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config && config->fxns && config->fxns->imgCloseFxn)
    {
        config->fxns->imgCloseFxn(handle, config->args);
    }
}

int32_t Bootloader_loadCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t numOfCores;
    uint8_t core;
    if(cpuInfo->smpEnable == true)
    {
        numOfCores = FREERTOS_SMP_NO_OF_CORES;
    }
    else
    {
        numOfCores = 1;
    }
    for( core = 0; core < numOfCores; core ++)
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
            if( cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
            {
                status = Bootloader_rprcImageLoad(handle, cpuInfo);
            }
        }
        cpuInfo ++;
    }

    return status;
}

int32_t Bootloader_runCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uintptr_t entryPoint = cpuInfo->entryPoint;

    if( cpuInfo->rprcOffset == BOOTLOADER_INVALID_ID)
    {
        /* boot a dummy while(1) loop */
        entryPoint = 0;
    }
    status = Bootloader_socCpuResetRelease(cpuInfo->cpuId, entryPoint);

    if(SystemP_SUCCESS == status)
    {
        status = Bootloader_socCpuRelease(cpuInfo->cpuId);
    }

    if(status == SystemP_SUCCESS)
    {
        uint64_t cpuHz;

        cpuHz = Bootloader_socCpuGetClock(cpuInfo->cpuId);
        if(cpuHz > (uint64_t)0)
        {
            DebugP_logInfo("CPU %s is initialized to %d Hz !!!\r\n",
                Bootloader_socGetCoreName(cpuInfo->cpuId), (uint32_t)cpuHz);
        }
    }

    return status;
}

int32_t Bootloader_loadSelfCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t cpuId = cpuInfo->cpuId;
#if !defined(SOC_AM62X) && !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62PX)
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

int32_t Bootloader_runSelfCpu(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_logInfo("All done, reseting self ...\r\n\n");
    status = Bootloader_socCpuResetReleaseSelf();
    /* control will not reach here */

    return status;
}

void Bootloader_JumpSelfCpu(void)
{
    DebugP_logInfo("All done, jumping self ...\r\n\n");
    Bootloader_socSelfCPUjump();
    /* control will not reach here */
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

int32_t Bootloader_rprcImageParseEntryPoint(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_RprcFileHeader header;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config && config->bootMedia != BOOTLOADER_MEDIA_MEM && Bootloader_socIsAuthRequired() == (uint32_t)1)
    {
        config = Bootloader_getMemBootloaderConfig(handle);
    }

    if(config)
    {
      config->fxns->imgSeekFxn(cpuInfo->rprcOffset, config->args);
      status = config->fxns->imgReadFxn(&header, sizeof(Bootloader_RprcFileHeader), config->args);

      cpuInfo->entryPoint = (uintptr_t)header.entry;
    }
    else{/* do nothing */}

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

    if(config && config->bootMedia != BOOTLOADER_MEDIA_MEM && Bootloader_socIsAuthRequired() == (uint32_t)1)
    {
        config = Bootloader_getMemBootloaderConfig(handle);
        gMemBootloaderConfig.fxns->imgSeekFxn(0, gMemBootloaderConfig.args);
    }

    if(config)
    {
      config->fxns->imgSeekFxn(cpuInfo->rprcOffset, config->args);
      status = config->fxns->imgReadFxn(&header, sizeof(Bootloader_RprcFileHeader), config->args);

      if(header.magic != (uint32_t)BOOTLOADER_RPRC_MAGIC_NUMBER)
      {
          status = SystemP_FAILURE;
      }
      else
      {
          cpuInfo->entryPoint = (uintptr_t)header.entry;

          uint32_t i;

          for(i=0; i<header.sectionCount; i++)
          {
              status = config->fxns->imgReadFxn(&section, sizeof(Bootloader_RprcSectionHeader), config->args);

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
                  status = config->fxns->imgReadFxn((void *)(uintptr_t)(section.addr), section.size, config->args);
                  ((Bootloader_Config *)handle)->bootImageSize += section.size;
              }
          }
        }
      }
      else{/* do nothing */}

    return status;
}

uint32_t Bootloader_getX509CertLen(uint8_t *x509_cert_ptr)
{
    uint32_t certLen = 0;
    uint8_t *pCertLen = (uint8_t *)&certLen;

    if ( *x509_cert_ptr != (uint8_t)0x30)
    {
        return (uint32_t)0;
    }

    *pCertLen = *(x509_cert_ptr + 1);

    /* If you need more than 2 bytes to store the cert length  */
    /* it means that the cert length is greater than 64 Kbytes */
    /* and we do not support it                                */
    if ((certLen > (uint32_t)0x80) &&
        (certLen != (uint32_t)0x82))
    {
        return (uint32_t)0;
    }

    if ( certLen == (uint32_t)0x82)
    {
        *pCertLen = *(x509_cert_ptr + 3);
        *(pCertLen + 1) = *(x509_cert_ptr + 2);

        /* add current offset from start of x509 cert */
        certLen += 3;
    }
    else
    {
        /* add current offset from start of x509 cert  */
        /* if cert len was obtained from 2nd byte i.e. */
        /* cert size is 127 bytes or less              */
        certLen += 1;
    }

    /* certLen now contains the offset of the last byte */
    /* of the cert from the ccert_start. To get the size */
    /* of certificate, add 1                             */

    return certLen + (uint32_t)1;
}

uint8_t *Bootloader_findSeq(uint8_t *x509_cert_ptr, uint32_t x509_cert_size, uint8_t *seq_oid, uint8_t seq_len)
{
    uint8_t *x509_cert_end = x509_cert_ptr + x509_cert_size - seq_len;

    /* searching for the following byte seq in the cert */
    /* seq_id(0x30) seq_len(< 0x80) 0x06 0x09 0x2B...   */
    while (x509_cert_ptr < x509_cert_end)
    {
        if ((*x509_cert_ptr == seq_oid[0]) &&
            (*(x509_cert_ptr + 2) == seq_oid[2]) &&
            (*(x509_cert_ptr - 2) == (uint8_t)0x30))
        {
            if ((memcmp((const void *)x509_cert_ptr, (const void *)seq_oid, (size_t)seq_len)) == 0)
            {
                /* return start boot_seq */
                return (x509_cert_ptr - 2);
            }
        }
        x509_cert_ptr++;
    }

    return 0;
}

uint32_t Bootloader_getMsgLen(uint8_t *x509_cert_ptr, uint32_t x509_cert_size)
{
    uint8_t *boot_seq_ptr;
    uint32_t msg_len = 0, boot_seq_len;
    uint8_t *msg_len_ptr = (uint8_t *)&msg_len;
    /* oid encoding of image_integrity extension - 1.3.6.1.4.1.294.1.22 */
    uint8_t boot_seq_oid[] = {0x06, 0x09, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x26, 0x01, 0x22};

    boot_seq_ptr = Bootloader_findSeq(x509_cert_ptr, x509_cert_size, boot_seq_oid, sizeof(boot_seq_oid));

    /* length of seq is stored in the byte after the 0x30 seq_id */
    /* length of seq is stored as offset of the last byte of seq */
    /* from current offset. Jump to the end of the boot seq as   */
    /* the length of the message  is the last field of this seq  */
    boot_seq_len = (uint32_t)*(++boot_seq_ptr);
    boot_seq_ptr = boot_seq_ptr + boot_seq_len;

    /* The last integer in this sequence is the msg length    */
    /* integers are tagged 0x20, so search backwards for 0x20 */
    /* The msg size can be encoded in 1, 2, 3 or 4 bytes      */
    /* 0x02 0x01 0x##                                         */
    /* 0x02 0x02 0x## 0x##                                    */
    /* 0x02 0x03 0x## 0x## 0x##                               */
    /* 0x02 0x04 0x## 0x## 0x## 0x##                          */
    if ( (*(boot_seq_ptr - 5) == (uint8_t)0x02) &&
         (*(boot_seq_ptr - 4) == (uint8_t)0x04) )
    {
        /* msg length encoded in 4 bytes */
        *msg_len_ptr = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
        *(msg_len_ptr + 2) = *(boot_seq_ptr - 2);
        *(msg_len_ptr + 3) = *(boot_seq_ptr - 3);
    }
    else if ( (*(boot_seq_ptr - 4) == (uint8_t)0x02) &&
         (*(boot_seq_ptr - 3) == (uint8_t)0x03) )
    {
        /* msg length encoded in 3 bytes */
        *msg_len_ptr = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
        *(msg_len_ptr + 2) = *(boot_seq_ptr - 2);
    }
    else if ( (*(boot_seq_ptr - 3) == (uint8_t)0x02) &&
         (*(boot_seq_ptr - 2) == (uint8_t)0x02) )
    {
        /* msg length encoded in 2 bytes */
        *msg_len_ptr = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
    }
    else if ( (*(boot_seq_ptr - 2) == (uint8_t)0x02) &&
         (*(boot_seq_ptr - 1) == (uint8_t)0x01) )
    {
        /* msg length encoded in 1 byte */
        *msg_len_ptr = *boot_seq_ptr;
    }

    return msg_len;
}

/* This API should only be called after all the rprc loading is complete */
uint32_t Bootloader_getMulticoreImageSize(Bootloader_Handle handle)
{
    uint32_t size = 0;

    if(handle != NULL)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        size = config->bootImageSize;
    }
    return size;
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

uint32_t Bootloader_getBootMedia(Bootloader_Handle handle)
{
    uint32_t media = BOOTLOADER_INVALID_ID;

    if(NULL != handle)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        media = config->bootMedia;
    }

    return media;
}

int32_t Bootloader_verifyMulticoreImage(Bootloader_Handle handle)
{
    int32_t status = SystemP_SUCCESS, authStatus = SystemP_FAILURE;
    uint32_t certLen = 0U, imageLen = 0U, ddrCopy = 1U;
    uint32_t certLoadAddr = 0xFFFFFFFFU;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config->fxns->imgReadFxn == NULL || config->fxns->imgSeekFxn == NULL)
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
            uint32_t cacheAlignedLen = (certLen + imageLen + (uint32_t)128) & ~(127);

            /* Write back and invalidate the cache before passing to HSM */
            CacheP_wbInv((void *)certLoadAddr, cacheAlignedLen, CacheP_TYPE_ALL);
        }
        else if(config->bootMedia == BOOTLOADER_MEDIA_FLASH || config->bootMedia == BOOTLOADER_MEDIA_EMMC)
        {
            config->fxns->imgReadFxn(x509Header, 4, config->args);
            config->fxns->imgSeekFxn(0, config->args);

            certLen = Bootloader_getX509CertLen(x509Header);

            if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
            {
                Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);

                if(flashArgs->flashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
                {
                    ddrCopy = 0;

                    certLoadAddr = FLASH_BASE_ADDRESS + flashArgs->appImageOffset;
                    imageLen = Bootloader_getMsgLen((uint8_t *)(certLoadAddr), certLen);

                    /* Invalidate 128B cache-line aligned destination region before TIFS writes to it */
                    CacheP_inv((void *)config->scratchMemPtr, (imageLen + (uint32_t)128) & ~(127), CacheP_TYPE_ALL);

                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);
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

            if(config->scratchMemPtr != NULL && ddrCopy == 1U)
            {
                config->fxns->imgReadFxn((void *)config->scratchMemPtr, 0x800, config->args);

                imageLen = Bootloader_getMsgLen((uint8_t *)config->scratchMemPtr, certLen);

                uint32_t totalLen = (certLen + imageLen + (uint32_t)128) & ~(127);

                config->fxns->imgSeekFxn(0, config->args);
                config->fxns->imgReadFxn((void *)config->scratchMemPtr, totalLen, config->args);

                certLoadAddr = (uint32_t)(&(config->scratchMemPtr[0]));

                config->fxns->imgSeekFxn(0, config->args);

                /* Get the 128B cache-line aligned image length */
                uint32_t cacheAlignedLen = (certLen + imageLen + (uint32_t)128) & ~(127);

                /* Write back and invalidate the cache before passing to HSM */
                CacheP_wbInv((void *)certLoadAddr, cacheAlignedLen, CacheP_TYPE_ALL);
            }
        }

        /* Check if the certificate length is within valid range */
        if((certLen > (uint32_t)0x100) && (certLen < (uint32_t)0x800) && status == SystemP_SUCCESS)
        {
            authStatus = Bootloader_socAuthImage(certLoadAddr);

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
      if(config->fxns->imgReadFxn == NULL || config->fxns->imgSeekFxn == NULL)
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
              if(config && config->bootMedia != BOOTLOADER_MEDIA_MEM && Bootloader_socIsAuthRequired() == (uint32_t)1)
              {
                  config = Bootloader_getMemBootloaderConfig(handle);
                  gMemBootloaderConfig.fxns->imgSeekFxn(0, gMemBootloaderConfig.args);
              }

              memset(&mHdrCore[0], 0xFF, BOOTLOADER_MAX_INPUT_FILES*sizeof(Bootloader_MetaHeaderCore));

              if(config)
              {
                status = config->fxns->imgReadFxn(&mHdrStr, sizeof(Bootloader_MetaHeaderStart), config->args);

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
                        status = config->fxns->imgReadFxn(&mHdrCore[i], sizeof(Bootloader_MetaHeaderCore), config->args);
                        /* TODO: Figure out how to add boot media specific offset */
                    }

                    /* Parse individual rprc files */
                    for(i=0U; i<mHdrStr.numFiles; i++)
                    {
                        rprcCoreId = mHdrCore[i].coreId;
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

void Bootloader_Params_init(Bootloader_Params *params)
{
    params->memArgsAppImageBaseAddr = BOOTLOADER_INVALID_ID;
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

#if defined (SOC_AM64X) || defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
/* Linux image load is applicable only for am64x,am62x and am62ax */
int32_t Bootloader_parseAndLoadLinuxAppImage(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config)
    {
      if(config->fxns->imgReadFxn == NULL || config->fxns->imgSeekFxn == NULL)
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
              if(config && config->bootMedia != BOOTLOADER_MEDIA_MEM && Bootloader_socIsAuthRequired() == (uint32_t)1)
              {
                  config = Bootloader_getMemBootloaderConfig(handle);
                  gMemBootloaderConfig.fxns->imgSeekFxn(0, gMemBootloaderConfig.args);
              }

              memset(&mHdrCore[0], 0xFF, BOOTLOADER_MAX_INPUT_FILES*sizeof(Bootloader_MetaHeaderCore));

              if(config)
              {
                status = config->fxns->imgReadFxn(&mHdrStr, sizeof(Bootloader_MetaHeaderStart), config->args);

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
                        status = config->fxns->imgReadFxn(&mHdrCore[i], sizeof(Bootloader_MetaHeaderCore), config->args);
                        /* TODO: Figure out how to add boot media specific offset */
                    }

                    /* Parse individual rprc files */
                    for(i=0U; i<mHdrStr.numFiles; i++)
                    {
                        /* Load the load only linux images */
                        if(mHdrCore[i].coreId == RPRC_LINUX_LOAD_ONLY_IMAGE_ID)
                        {
                            Bootloader_CpuInfo load_only_image;
                            load_only_image.rprcOffset = mHdrCore[i].imageOffset;
                            load_only_image.entryPoint = 0;

                            /* Set CPU ID as A53 as linux runs on A53 */
                            load_only_image.cpuId = CSL_CORE_ID_A53SS0_0;

                            /**************/
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
                            config->coresPresentMap |= ((uint32_t)1 << cslCoreId);
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


int32_t Bootloader_runSelfCpuWithLinux(void)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_logInfo("All done, reseting self ...\r\n\n");
    status = Bootloader_socCpuResetReleaseSelf();
    /* control will not reach here */

    return status;
}

#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62PX)
void Bootloader_ReservedMemInit(uint32_t startAddress, uint32_t regionlength)
{
    return Bootloader_socSetSBLMem(startAddress, regionlength);
}
#endif

#endif

static Bootloader_Config* Bootloader_getMemBootloaderConfig(Bootloader_Handle handle)
{
    if(handle && ((Bootloader_Config *)handle)->scratchMemPtr)
    {
        ((Bootloader_MemArgs*)gMemBootloaderConfig.args)->appImageBaseAddr = (uint32_t)((Bootloader_Config *)handle)->scratchMemPtr;
    }

    return &gMemBootloaderConfig;
}