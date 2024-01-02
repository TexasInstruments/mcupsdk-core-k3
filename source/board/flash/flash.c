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
 *  \file flash.c
 *
 *  \brief File containing Flash Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/flash.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void *openLock;
    /**<  Lock to protect OSPI open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} Flash_DrvObj;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Flash_Config gFlashConfig[];
extern uint32_t gFlashConfigNum;

/** \brief Driver object */
static Flash_DrvObj gFlashDrvObj =
{
    .openLock      = NULL,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Flash_init(void)
{
    int32_t status;

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gFlashDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gFlashDrvObj.openLock = &gFlashDrvObj.lockObj;
    }

    return;
}

void Flash_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gFlashDrvObj.openLock)
    {
        SemaphoreP_destruct(&gFlashDrvObj.lockObj);
        gFlashDrvObj.openLock = NULL;
    }

    return;
}

Flash_Attrs *Flash_getAttrs(uint32_t instanceId)
{
    Flash_Attrs *attrs = NULL;
    Flash_Config *config = NULL;

    if(instanceId < gFlashConfigNum)
    {
        config = &gFlashConfig[instanceId];
        attrs = config->attrs;
    }
    return attrs;
}

Flash_Handle Flash_open(uint32_t instanceId, Flash_Params *params)
{
    Flash_Config *config = NULL;

    if(instanceId < gFlashConfigNum)
    {
        config = &gFlashConfig[instanceId];

        if(config->fxns && config->fxns->openFxn)
        {
            int32_t status;

            /* Protect this region from a concurrent Flash_open */
            DebugP_assert(NULL != gFlashDrvObj.openLock);
            SemaphoreP_pend(&gFlashDrvObj.lockObj, SystemP_WAIT_FOREVER);

            status = config->fxns->openFxn(config, params);

            status += SemaphoreP_constructBinary(&config->lockSem,  1U);

            if(status != SystemP_SUCCESS)
            {
                config = NULL;
            }

            SemaphoreP_post(&gFlashDrvObj.lockObj);
        }
    }
    return config;
}

void Flash_close(Flash_Handle handle)
{
    Flash_Config *config = (Flash_Config*)handle;

    if(config && config->fxns && config->fxns->closeFxn)
    {
        DebugP_assert(NULL != gFlashDrvObj.openLock);
        SemaphoreP_pend(&gFlashDrvObj.lockObj, SystemP_WAIT_FOREVER);

        config->fxns->closeFxn(config);
        SemaphoreP_destruct(&config->lockSem);

        SemaphoreP_post(&gFlashDrvObj.lockObj);
    }
}

Flash_Handle Flash_getHandle(uint32_t instanceId)
{
    Flash_Config *config = NULL;

    if(instanceId < gFlashConfigNum)
    {
        config = &gFlashConfig[instanceId];
    }

    return config;
}

int32_t Flash_read(Flash_Handle handle, uint32_t offset, uint8_t *buf, uint32_t len)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->readFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->readFxn(config, offset, buf, len);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_write(Flash_Handle handle, uint32_t offset, uint8_t *buf, uint32_t len)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->writeFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->writeFxn(config, offset, buf, len);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_eraseBlk(Flash_Handle handle, uint32_t blockNum)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->eraseFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->eraseFxn(config, blockNum);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_eraseSector(Flash_Handle handle, uint32_t sectorNum)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->eraseFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->eraseSectorFxn(config, sectorNum);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_reset(Flash_Handle handle)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->resetFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->resetFxn(config);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_enablePhyPipeline(Flash_Handle handle)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->enablePhyPipelineFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status = config->fxns->enablePhyPipelineFxn(config);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_disablePhyPipeline(Flash_Handle handle)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->disablePhyPipelineFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status = config->fxns->disablePhyPipelineFxn(config);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    return status;
}

int32_t Flash_blkPageToOffset(Flash_Handle handle, uint32_t *offset, uint32_t block, uint32_t page)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && offset)
    {
        uint32_t blockCount = config->attrs->blockCount;
        uint32_t pageSize   = config->attrs->pageSize;
        uint32_t pageCount  = config->attrs->pageCount;

        status = SystemP_SUCCESS;
        *offset = 0;

        if( block > blockCount || page > pageCount)
        {
            status = SystemP_FAILURE;
        }
        if(status == SystemP_SUCCESS)
        {
            *offset =   (block * (pageCount * pageSize)) + (page * pageSize);
        }
    }
    return status;
}

int32_t Flash_offsetToBlkPage(Flash_Handle handle, uint32_t  offset, uint32_t *block, uint32_t *page)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && block && page)
    {
        uint32_t blockCount = config->attrs->blockCount;
        uint32_t pageSize   = config->attrs->pageSize;
        uint32_t pageCount  = config->attrs->pageCount;
        uint32_t blockSize  = config->attrs->blockSize;
        uint32_t leftover;

        status = SystemP_SUCCESS;

        *block 	  = offset / blockSize;
        leftover  = offset % blockSize;
        *page 	  = leftover / pageSize;
        if (leftover % pageSize)
        {
            /* All writes must be page aligned for now */
            status = SystemP_FAILURE;
        }
        if (*block > blockCount || *page > pageCount)
        {
            /* beyond limits for this flash */
            status = SystemP_FAILURE;
        }
    }
    return status;
}

int32_t Flash_sectorPageToOffset(Flash_Handle handle, uint32_t *offset, uint32_t sector, uint32_t page)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && offset)
    {
        uint32_t sectorCount = config->attrs->sectorCount;
        uint32_t pageSize    = config->attrs->pageSize;
        uint32_t pageCount   = config->attrs->pageCount;

        status = SystemP_SUCCESS;
        *offset = 0;

        if( sector > sectorCount || page > pageCount)
        {
            status = SystemP_FAILURE;
        }
        if(status == SystemP_SUCCESS)
        {
            *offset =   (sector * (pageCount * pageSize)) + (page * pageSize);
        }
    }
    return status;
}

int32_t Flash_offsetToSectorPage(Flash_Handle handle, uint32_t  offset, uint32_t *sector, uint32_t *page)
{
    Flash_Config *config = (Flash_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && sector && page)
    {
        uint32_t sectorCount = config->attrs->sectorCount;
        uint32_t pageSize    = config->attrs->pageSize;
        uint32_t sectorSize  = config->attrs->sectorSize;
        uint32_t pageCount   = sectorSize / pageSize;
        uint32_t leftover;

        status = SystemP_SUCCESS;

        *sector   = offset / sectorSize;
        leftover  = offset % sectorSize;
        *page 	  = leftover / pageSize;
        if (leftover % pageSize)
        {
            /* All writes must be page aligned for now */
            status = SystemP_FAILURE;
        }
        if (*sector > sectorCount || *page > pageCount)
        {
            /* beyond limits for this flash */
            status = SystemP_FAILURE;
        }
    }
    return status;
}

uint32_t Flash_getPhyTuningOffset(Flash_Handle handle)
{
    Flash_Config *config = (Flash_Config*)handle;
    uint32_t offset = 0xFFFFFFFFU;

    if(config)
    {
        offset = config->attrs->flashSize - config->attrs->blockSize;
    }

    return offset;
}

uint32_t Flash_getFlashInterfaceIndex(uint32_t flashType)
{
    uint32_t flashIndex = 0;
    Flash_Config *config = NULL;

    for (uint8_t count = 0; count < gFlashConfigNum; count++)
    {
        config = &gFlashConfig[count];
        if(config->attrs->flashType == flashType)
        {
            flashIndex = count;
            break;
        }
    }

    return flashIndex;
}
