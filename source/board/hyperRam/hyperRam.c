/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file hyperRam.c
 *
 *  \brief File containing HyperRam Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/hyperRam.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hyperbus.h>
#include <drivers/utils/utils.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
/* This is needed for memset/memcpy */
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Offset of CR0 register from HyperRam base address.
 *
 *  This is the offset from the HyperRam base address to the CR0 register.
 */
#define HYPERRAM_CR0_OFFSET     (0x800U * 2U)

/**
 *  \brief Offset of CR1 register from HyperRam base address.
 *
 *  This is the offset from the HyperRam base address to the CR1 register.
 */
#define HYPERRAM_CR1_OFFSET     (0x801U * 2U)

/**
 *  \brief Offset of ID0 register from HyperRam base address.
 *
 *  This is the offset from the HyperRam base address to the ID0 register.
 */
#define HYPERRAM_ID0_OFFSET     (0x0U * 2U)

/**
 *  \brief Offset of ID1 register from HyperRam base address.
 *
 *  This is the offset from the HyperRam base address to the ID1 register.
 */
#define HYPERRAM_ID1_OFFSET     (0x1U * 2U)

/**
 *  \brief Default value for CR0 register.
 *
 *  This is the default value for the CR0 register, which includes setting the
 *  initial latency cycle to 6 clocks for a 166MHz bus speed.
 */
#define HYPERRAM_CR0_DEFAULT_VALUE        (0x8F1FU)

/**
 *  \brief Offset of FSS_FSAS fragment configuration register from  FSS_FSAS_GENREGS
 *         base address.
 *
 *  This is the offset from the  FSS_FSAS_GENREGS base address to the FSS_FSAS
 *  fragment configuration register.
 */
#define HYPERRAM_FSSFSAS_FRAG_OFFSET     (0xCU)

/**
 *  \brief Fragment disable value for FSS_FSAS fragment configuration register.
 *
 *  This is the value to write to the FSS_FSAS fragment configuration register to
 *  disable fragments.
 */
#define HYPERRAM_FSSFSAS_FRAG_DISABLE    (0x0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void *openLock;
    /**<  Lock to protect HyperRam open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} HyperRam_DrvObj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Driver object */
static HyperRam_DrvObj gHyperRamDrvObj =
{
    .openLock      = NULL,
};

extern HyperRam_Config gHyperRamConfig[];
extern uint32_t gHyperRamConfigNum;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
            
static void HyperRam_getDeviceID(HYPERRAM_Handle handle, uint32_t baseAddress);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void HyperRam_init(void)
{
    int32_t status;
    uint32_t count;
    HyperRam_Object *obj;

    /* Init each driver instance object */
    for(count = 0U; count < gHyperRamConfigNum; count++)
    {
        /* Init object variables */
        obj = gHyperRamConfig[count].object;
        DebugP_assert(NULL_PTR != obj);
        memset(obj, 0U, sizeof(HYPERBUS_Object));
    }

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gHyperRamDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gHyperRamDrvObj.openLock = &gHyperRamDrvObj.lockObj;
    }

    return;
}

void HyperRam_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gHyperRamDrvObj.openLock)
    {
        SemaphoreP_destruct(&gHyperRamDrvObj.lockObj);
        gHyperRamDrvObj.openLock = NULL;
    }

    return;
}

void HyperRam_close(HYPERRAM_Handle handle)
{

    if(handle != NULL)
    {
        HyperRam_Config *config = ((HyperRam_Config *)handle);
        DebugP_assert(NULL_PTR != config->object);
        HyperRam_Object *obj = config->object;
        
        obj->isOpen = 0U;
        SemaphoreP_post(&gHyperRamDrvObj.lockObj);
    }

    return;
}

HYPERRAM_Handle HyperRam_open(uint32_t instanceId)
{
    HyperRam_Config *config = NULL;
    HYPERRAM_Handle handle = NULL;
    HyperRam_Object *obj = NULL;
    HyperRam_Attrs *attrs = NULL;
    uint32_t baseAddress = 0U;
    int32_t status = SystemP_SUCCESS;
    HYPERBUS_Config *hyperBusConfig = NULL;
    const HYPERBUS_Attrs *hyperBusAttrs = NULL;
    uint32_t fssFsasBaseAddr = 0U;

    /* Check for valid index */
    if(instanceId >= gHyperRamConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        config = &gHyperRamConfig[instanceId];
    }
    
    if(SystemP_SUCCESS == status)
    {
        /* Protect this region from a concurrent HYPERRAM_Open */
        DebugP_assert(NULL_PTR != gHyperRamDrvObj.openLock);
        SemaphoreP_pend(&gHyperRamDrvObj.lockObj, SystemP_WAIT_FOREVER);
        
        obj = (HyperRam_Object *)(config->object);
        DebugP_assert(NULL_PTR != obj);
        DebugP_assert(NULL_PTR != config->attrs);
        attrs = config->attrs;
        if(CSL_TRUE == obj->isOpen)
        {
            /* Handle already opened */
            status = SystemP_FAILURE;
        }

        obj->hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    }
    
    if((obj != NULL) && (SystemP_SUCCESS == status))
    {
        if(NULL != obj->hyperbusHandle)
        {
            baseAddress = HYPERBUS_getHyperBusDataBaseAddr(obj->hyperbusHandle);

            hyperBusConfig = ((HYPERBUS_Config *)obj->hyperbusHandle);
            DebugP_assert(NULL_PTR != hyperBusConfig);
            
            hyperBusAttrs = hyperBusConfig->attrs;
            DebugP_assert(NULL_PTR != hyperBusAttrs);
            
            fssFsasBaseAddr = hyperBusAttrs->fssFsasBase;
            obj->handle = (HYPERRAM_Handle)config;
        }

        /* hyperram initialization requires Wait of 150 µs for RAM to power up after reset*/
        ClockP_usleep(150U);
        
        /* disablling 16 bit fragmentation at fss boundary */
        CSL_REG32_WR(fssFsasBaseAddr + HYPERRAM_FSSFSAS_FRAG_OFFSET, HYPERRAM_FSSFSAS_FRAG_DISABLE);
        
        HyperRam_getDeviceID(obj->handle, baseAddress);

        /* disablling 16 bit fragmentation at fss boundary */
        CSL_REG32_WR(fssFsasBaseAddr + HYPERRAM_FSSFSAS_FRAG_OFFSET, HYPERRAM_FSSFSAS_FRAG_DISABLE);

        obj->isOpen = 1U;
        handle = (HYPERRAM_Handle) config;

        SemaphoreP_post(&gHyperRamDrvObj.lockObj);
    }

    /* Free up resources in case of error */
    if(SystemP_SUCCESS != status)
    {
        if(NULL != config)
        {
            HyperRam_close((HYPERRAM_Handle) config);
        }
    }

    return handle;
}

static void HyperRam_getDeviceID(HYPERRAM_Handle handle, uint32_t baseAddress)
{
    HyperRam_Config *config = ((HyperRam_Config *)handle);
    DebugP_assert(NULL_PTR != config->object);
    const HyperRam_Object *obj = config->object;
    DebugP_assert(NULL_PTR != config->attrs);
    const HyperRam_Attrs *attrs = config->attrs;
    HYPERBUS_Handle hyperBusHandle = obj->hyperbusHandle;
    HYPERBUS_Config *hyperBusConfig = ((HYPERBUS_Config *)hyperBusHandle);
    DebugP_assert(NULL_PTR != hyperBusConfig->attrs);
    const HYPERBUS_Attrs *hyperBusAttrs = hyperBusConfig->attrs;
    CSL_hyperbus_coreRegs   *hyperBusCoreRegs = (CSL_hyperbus_coreRegs *)hyperBusAttrs->baseAddr;

    uint32_t chipSelect = hyperBusAttrs->chipSelect;
    uint16_t CR0 = 0U;
    uint16_t CR1 = 0U;
    uint16_t ID0 = 0U;
    uint16_t ID1 = 0U;

    /* Set target to Register Space */
    CSL_REG32_FINS(&hyperBusCoreRegs->MCR[chipSelect], HYPERBUS_CORE_MCR_CRT, HYPERBUS_MCR_CR_SPACE);

    CSL_REG16_WR_RAW((uint16_t *)(baseAddress + HYPERRAM_CR0_OFFSET), HYPERRAM_CR0_DEFAULT_VALUE);

    CR0 = CSL_REG16_RD_RAW((uint16_t *)(baseAddress + HYPERRAM_CR0_OFFSET));
    DebugP_assert(CR0 == HYPERRAM_CR0_DEFAULT_VALUE);

    Utils_dataAndInstructionBarrier();
    
    CR1 = CSL_REG16_RD_RAW((uint16_t *)(baseAddress + HYPERRAM_CR1_OFFSET));
    DebugP_assert(CR1 == attrs->CR1);

    ID0 = CSL_REG16_RD_RAW((uint16_t *)(baseAddress + HYPERRAM_ID0_OFFSET));
    DebugP_assert(ID0 == attrs->ID0);

    ID1 = CSL_REG16_RD_RAW((uint16_t *)(baseAddress + HYPERRAM_ID1_OFFSET));
    DebugP_assert(ID1 == attrs->ID1);

    /* Set target to Memory Space */
    CSL_REG32_FINS(&hyperBusCoreRegs->MCR[chipSelect], HYPERBUS_CORE_MCR_CRT, HYPERBUS_MCR_MEM_SPACE);
}
