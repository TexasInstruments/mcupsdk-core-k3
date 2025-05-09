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
 *  \file hyperbus_v0.c
 *
 *  \brief File containing HYPERBUS Driver APIs implementation for version V0.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/csl_types.h>
#include <drivers/hyperbus.h>
#include <drivers/soc.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include "soc/hyperbus_soc.h"
/* This is needed for memset/memcpy */
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * @brief Offset of SYSCONFIG register in Hyperbus FSS module
 */
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG                             (0x00000004U)

/**
 * @brief Value to enable ECC in SYSCONFIG register
 */
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE                  (0x00000001U)

/**
 * @brief Value to disable ECC in SYSCONFIG register
 */
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE                 (0x00000000U)

/**
 * @brief Value to enable Hyperbus mode in SYSCONFIG register
 */
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_HB_OSPI_HYPERBUS_ENABLE     (0x00000002U)
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_HB_OSPI_SHIFT               (0x1U)

/**
 * @brief Value to disable Hyperbus mode in SYSCONFIG register
 */
#define HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_HB_OSPI_HYPERBUS_DISABLE    (0x00000000U)

/**
 * @brief Offset of CCFG register in Hyperbus OTFA module
 */
#define HYPERBUS_FSS_FSAS_OTFA_REGS_CCFG                                (0x00000018U)

/**
 * @brief Value to enable master read mode in CCFG register
 */
#define HYPERBUS_FSS_FSAS_OTFA_REGS_CCFG_MASTER_EN_RD_ENABLE            (0x00000001U)

/**
 * @brief Value to disable master read mode in CCFG register
 */
#define HYPERBUS_FSS_FSAS_OTFA_REGS_CCFG_MASTER_EN_RD_DISABLE           (0x00000000U)

/**< Number of iterations for MDLL stabilization check */
#define HYPERBUS_NUM_DLL_ITERATIONS      16U

/**< Consecutive stable reads required for DLL stabilisation */
#define HYPERBUS_DLL_STABILIZATION_COUNT 4U 

/**< Size of data to be read for DLL stabilisation check */
#define HYPERBUS_DATA_SIZE           64U 

#define HYPERBUS_DEFAULT_REGISTER_READ_TIMEOUT_US             (500000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void *openLock;
    /**<  Lock to protect HYPERBUS open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} HYPERBUS_DrvObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Internal functions */

/* Set device configuartion for HyperFlash or HyperRAM */
static int32_t HYPERBUS_setDeviceCfg(HYPERBUS_Handle handle);
static void HYPERBUS_fssInstanceSelect(HYPERBUS_Handle handle, HYPERBUS_fssHandle * fssHandle);
static void HYPERBUS_configureFss(HYPERBUS_Handle handle, HYPERBUS_fssHandle * fssHandle);
static void HYPERBUS_enableHyperBus(HYPERBUS_fssHandle * fssHandle, uint16_t val);
static int32_t HYPERBUS_waitForMdllStabilization(HYPERBUS_Handle handle);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Driver object */
static HYPERBUS_DrvObj gHyperBusDrvObj =
{
    .openLock      = NULL,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void HYPERBUS_init(void)
{
    int32_t status;
    uint32_t count;
    HYPERBUS_Object *obj;

    /* Init each driver instance object */
    for(count = 0U; count < gHyperBusConfigNum; count++)
    {
        /* Init object variables */
        obj = gHyperBusConfig[count].object;
        DebugP_assert(NULL_PTR != obj);
        memset(obj, 0U, sizeof(HYPERBUS_Object));
    }

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gHyperBusDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gHyperBusDrvObj.openLock = &gHyperBusDrvObj.lockObj;
    }

    return;
}

void HYPERBUS_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gHyperBusDrvObj.openLock)
    {
        SemaphoreP_destruct(&gHyperBusDrvObj.lockObj);
        gHyperBusDrvObj.openLock = NULL;
    }

    return;
}

HYPERBUS_Handle HYPERBUS_getHandle(uint32_t driverInstanceIndex)
{
    HYPERBUS_Handle         handle = NULL;
    /* Check index */
    if(driverInstanceIndex < gHyperBusConfigNum)
    {
        HYPERBUS_Object *obj;
        obj = gHyperBusConfig[driverInstanceIndex].object;

        if(obj && (CSL_TRUE == obj->isOpen))
        {
            /* valid handle */
            handle = obj->handle;
        }
    }
    return handle;
}

static void HYPERBUS_fssInstanceSelect(HYPERBUS_Handle handle, HYPERBUS_fssHandle * fssHandle)
{
    HYPERBUS_Config *config = ((HYPERBUS_Config *)handle);
    DebugP_assert(NULL_PTR != config->attrs);
    const HYPERBUS_Attrs *attrs = config->attrs;

    fssHandle->cfg_base     = attrs->fssCfgBase;
    fssHandle->fsas_base    = attrs->fssFsasBase;
    fssHandle->otfa_base    = attrs->fssOtfaBase;
    fssHandle->s0_reg0_base = (HYPERBUS_fssDataIf) {(uint64_t)attrs->fssS0Reg0Base, (uintptr_t)attrs->fssS0Reg0Base};
    fssHandle->s0_reg1_base = (HYPERBUS_fssDataIf) {(uint64_t)attrs->fssS0Reg1Base, (uintptr_t)attrs->fssS0Reg1Base};
    fssHandle->s0_reg3_base = (HYPERBUS_fssDataIf) {(uint64_t)attrs->fssS0Reg3Base, (uintptr_t)attrs->fssS0Reg3Base};
}

static void HYPERBUS_configureFss(HYPERBUS_Handle handle, HYPERBUS_fssHandle * fssHandle)
{
    HYPERBUS_Config *config = ((HYPERBUS_Config *)handle);
    DebugP_assert(NULL_PTR != config->attrs);
    const HYPERBUS_Attrs *attrs = config->attrs;

    /* select HYPERBUS path */
    HYPERBUS_enableHyperBus(fssHandle, 1U);

    if(CSL_TRUE == attrs->ECCEnable)
    {
        /* ECC not supported */
    }
    else
    {
        /* disable ECC */
        CSL_REG16_WR_RAW((uint16_t *)((uintptr_t)(fssHandle->fsas_base) + HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG),\
         HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);        
    }

    if(CSL_TRUE == attrs->OTFAEnable)
    {
        /* OTFA not supported */
    }
    else
    {
        /* disable OTFA */
        CSL_REG16_WR_RAW((uint16_t *)((uintptr_t)(fssHandle->otfa_base) + HYPERBUS_FSS_FSAS_OTFA_REGS_CCFG),\
         HYPERBUS_FSS_FSAS_OTFA_REGS_CCFG_MASTER_EN_RD_DISABLE);
    }
}

static void HYPERBUS_enableHyperBus(HYPERBUS_fssHandle * fssHandle, uint16_t val)
{
    CSL_REG16_WR_RAW((uint16_t *)((uintptr_t)(fssHandle->cfg_base) + HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG),\
     val << HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_HB_OSPI_SHIFT);
}

static int32_t HYPERBUS_waitForMdllStabilization(HYPERBUS_Handle handle)
{
    uint8_t current_data[HYPERBUS_DATA_SIZE];
    uint8_t previous_data[HYPERBUS_DATA_SIZE];
    uint32_t stable_count = 0U;
    uint32_t iteration;
    int32_t status = SystemP_SUCCESS;
    uint32_t databaseAddr = 0U;

    databaseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);

    for (iteration = 0U; iteration < HYPERBUS_NUM_DLL_ITERATIONS; iteration++) 
    {
        /* Invalidate cache */
        CacheP_inv((void*)databaseAddr, HYPERBUS_DATA_SIZE, CacheP_TYPE_ALLD);

        memcpy(current_data, (void*)databaseAddr, HYPERBUS_DATA_SIZE);

        /*
         * Compare current data with previous data
         * If it is the same we increment the stable count
         * If not, we reset the stable count
         */
        if (((iteration > 0U) && (memcmp(current_data, previous_data, HYPERBUS_DATA_SIZE) == 0)) == (bool)(TRUE))
        {
            stable_count++;
        }
        else
        {
            stable_count = 0U; 
        }

        /*
         * Copy current data to previous data for the next iteration
         * This is done so we can compare the current data with the previous data
         * in the next iteration
         */
        memcpy(previous_data, current_data, HYPERBUS_DATA_SIZE);

        /*
         * Check if we have reached the stabilization count
         * If we have, we can proceed with normal RAM access
         * If not, we continue to loop until we reach the stabilization count
         */
        if (stable_count >= (HYPERBUS_DLL_STABILIZATION_COUNT - 1U))
        {
            break;
        }
    }

    if (stable_count < (HYPERBUS_DLL_STABILIZATION_COUNT - 1U))
    {
        DebugP_log("DLL did not stabilize after %d iterations.\r\n", HYPERBUS_NUM_DLL_ITERATIONS);
        status = SystemP_FAILURE;
    }

    return status;
}

HYPERBUS_Handle HYPERBUS_open(uint32_t index)
{
    int32_t status = SystemP_SUCCESS;
    HYPERBUS_Handle handle = NULL;
    HYPERBUS_Config *config = NULL;
    HYPERBUS_Object *obj = NULL;
    const HYPERBUS_Attrs *attrs = NULL;
    HYPERBUS_fssHandle fssHandle = {0U};
    const CSL_hyperbus_syscfgRegs *hpbSyscfgRegs = NULL;
    uint32_t regval = 0U;
    uint64_t curTime = 0U;

    /* Check for valid index */
    if(index >= gHyperBusConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        config = &gHyperBusConfig[index];
    }
    
    if(SystemP_SUCCESS == status)
    {
        /* Protect this region from a concurrent HYPERBUS_Open */
        DebugP_assert(NULL_PTR != gHyperBusDrvObj.openLock);
        SemaphoreP_pend(&gHyperBusDrvObj.lockObj, SystemP_WAIT_FOREVER);

        obj = config->object;
        DebugP_assert(NULL_PTR != obj);
        DebugP_assert(NULL_PTR != config->attrs);
        attrs = config->attrs;
        hpbSyscfgRegs = (const CSL_hyperbus_syscfgRegs *)attrs->ssBaseAddr;
        if(CSL_TRUE == obj->isOpen)
        {
            /* Handle already opened */
            status = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == status)
    {
        obj->handle = (HYPERBUS_Handle)config;
        
        status = HYPERBUS_powerClockInit(obj->handle);

        if(SystemP_SUCCESS == status)
        {
            /* Ensure that the FIFO RAM auto-initialization is complete by reading the
             * HPB0_SS_RAM_STAT_REG[0] INIT_DONE bit . 
             */
            regval = CSL_REG32_FEXT_RAW(&hpbSyscfgRegs->RAM_STAT_REG, CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_MASK,\
                CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_SHIFT);
            
            curTime = ClockP_getTimeUsec();
            while(0U == regval)
            {
                ClockP_usleep(1U);
                regval = CSL_REG32_FEXT_RAW(&hpbSyscfgRegs->RAM_STAT_REG, CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_MASK,\
                    CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_SHIFT);
                    
                if((HYPERBUS_DEFAULT_REGISTER_READ_TIMEOUT_US < (ClockP_getTimeUsec() - curTime)))
                {
                    status = SystemP_TIMEOUT;
                    break;
                }
            }
        }
                
        if(SystemP_SUCCESS == status)
        {
            status = HYPERBUS_waitForMdllStabilization(obj->handle);
            
            if(SystemP_SUCCESS == status)
            {
                HYPERBUS_fssInstanceSelect(obj->handle, &fssHandle); 

                /* Enabling hyperbus in FSS */
                HYPERBUS_configureFss(obj->handle, &fssHandle);

                status = HYPERBUS_setDeviceCfg(obj->handle);

                if(SystemP_SUCCESS == status)
                {
                    /* Check the HPB0_SS_DLL_STAT_REG[0] MDLL_LOCK bit to ensure the Master DLL is locked. */
                    regval = CSL_REG32_FEXT_RAW(&hpbSyscfgRegs->DLL_STAT_REG, CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_MASK,\
                        CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_SHIFT);
                    
                    curTime = ClockP_getTimeUsec();
                    while(0U == regval)
                    {
                        ClockP_usleep(1U);
                        regval = CSL_REG32_FEXT_RAW(&hpbSyscfgRegs->DLL_STAT_REG, CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_MASK,\
                        CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_SHIFT);

                        if((HYPERBUS_DEFAULT_REGISTER_READ_TIMEOUT_US < (ClockP_getTimeUsec() - curTime)))
                        {
                            status = SystemP_TIMEOUT;
                            break;
                        }
                    }
                }
            }
        }
    }

    if(SystemP_SUCCESS == status)
    {
        obj->isOpen = 1U;
        handle = (HYPERBUS_Handle) config;
        SemaphoreP_post(&gHyperBusDrvObj.lockObj);
    }

    /* Free up resources in case of error */
    if(SystemP_SUCCESS != status)
    {
        if(NULL != config)
        {
            HYPERBUS_close((HYPERBUS_Handle) config);
        }
    }
    
    return handle;
}

void HYPERBUS_close(HYPERBUS_Handle handle)
{
    if(handle != NULL)
    {
        HYPERBUS_Object *obj = ((HYPERBUS_Config *)handle)->object;
        
        HYPERBUS_fssHandle fssHandle = {0U};
        HYPERBUS_fssInstanceSelect(handle, &fssHandle);

        /* Disabling hyperbus in FSS */
        HYPERBUS_enableHyperBus(&fssHandle, 0U);

        /* Destruct all locks*/
        obj->isOpen = 0U;
        SemaphoreP_post(&gHyperBusDrvObj.lockObj);
    }

    return;
}

static uint32_t HYPERBUS_makeMemCfg(HYPERBUS_Handle handle, HYPERBUS_MemCfg *pHyperBusMemCfg)
{
    uint32_t value = 0x0U;
    value |= (pHyperBusMemCfg->max_en          << CSL_HYPERBUS_CORE_MCR_MAXEN_SHIFT);
    value |= (pHyperBusMemCfg->max_len         << CSL_HYPERBUS_CORE_MCR_MAXLEN_SHIFT);
    value |= (pHyperBusMemCfg->true_cont_merge << CSL_HYPERBUS_CORE_MCR_TCMO_SHIFT);
    value |= (pHyperBusMemCfg->asymm_cache     << CSL_HYPERBUS_CORE_MCR_ACS_SHIFT);
    value |= (pHyperBusMemCfg->cfg_reg_target  << CSL_HYPERBUS_CORE_MCR_CRT_SHIFT);
    value |= (pHyperBusMemCfg->dev_type        << CSL_HYPERBUS_CORE_MCR_DEVTYPE_SHIFT);
    value |= (pHyperBusMemCfg->wrap_size       << CSL_HYPERBUS_CORE_MCR_WRAPSIZE_SHIFT);

    return value;
}

static uint32_t HYPERBUS_makeMemTiming(HYPERBUS_Handle handle, HYPERBUS_MemTiming *pHyperBusMemTiming)
{
    uint32_t value = 0x0U;
    value |= (pHyperBusMemTiming->readCSHigh   << CSL_HYPERBUS_CORE_MTR_RCSHI_SHIFT);
    value |= (pHyperBusMemTiming->writeCSHigh  << CSL_HYPERBUS_CORE_MTR_WCSHI_SHIFT);
    value |= (pHyperBusMemTiming->readCSSetup  << CSL_HYPERBUS_CORE_MTR_RCSS_SHIFT);
    value |= (pHyperBusMemTiming->writeCSSetup << CSL_HYPERBUS_CORE_MTR_WCSS_SHIFT);
    value |= (pHyperBusMemTiming->readCSHold   << CSL_HYPERBUS_CORE_MTR_RCSH_SHIFT);
    value |= (pHyperBusMemTiming->writeCSHold  << CSL_HYPERBUS_CORE_MTR_WCSH_SHIFT);
    value |= (pHyperBusMemTiming->latency      << CSL_HYPERBUS_CORE_MTR_LTCY_SHIFT);

    return value;
}

static int32_t HYPERBUS_setDeviceCfg(HYPERBUS_Handle handle)
{
    HYPERBUS_Config *config = ((HYPERBUS_Config *)handle);
    DebugP_assert(NULL_PTR != config->attrs);
    const HYPERBUS_Attrs *attrs = config->attrs;
    CSL_hyperbus_coreRegs   *hpbCoreRegs = (CSL_hyperbus_coreRegs *)attrs->baseAddr;
    int32_t status = SystemP_SUCCESS;

    uint32_t deviceType = attrs->deviceType;
    uint32_t chipSelect = attrs->chipSelect;
    uint32_t retval = 0U;

    if (deviceType == (uint32_t)HYPERBUS_DEVICETYPE_HYPERRAM)
    {
        /* Initialize MCR_x Register */
        HYPERBUS_MemCfg memCfg;
        memCfg.max_en          = HYPERBUS_MCR_CONFIGURABLE_CS_LOW_TIME;
        memCfg.max_len         = HYPERBUS_MCR_MAXLEN_1024_BYTE;
        memCfg.true_cont_merge = HYPERBUS_MCR_NO_MERGE_WRAP_INCR;
        memCfg.asymm_cache     = HYPERBUS_MCR_NO_ASYMM_CACHE_SUPPORT;
        memCfg.cfg_reg_target  = HYPERBUS_MCR_CR_SPACE;
        memCfg.dev_type        = HYPERBUS_MCR_HYPERRAM;
        memCfg.wrap_size       = HYPERBUS_MCR_WRAPSIZE_NONE;

        retval = HYPERBUS_makeMemCfg(handle, &memCfg);
        
        CSL_REG32_WR_RAW(&hpbCoreRegs->MCR[chipSelect], retval);

        /* Initialize MTR_x Register */
        HYPERBUS_MemTiming memTiming;
        memTiming.readCSHigh   = attrs->readCSHigh;
        memTiming.writeCSHigh  = attrs->writeCSHigh;
        memTiming.readCSSetup  = attrs->readCSSetup;
        memTiming.writeCSSetup = attrs->writeCSSetup;
        memTiming.readCSHold   = attrs->readCSHold;
        memTiming.writeCSHold  = attrs->writeCSHold;
        memTiming.latency      = attrs->latency;

        retval = HYPERBUS_makeMemTiming(handle, &memTiming);
        
        CSL_REG32_WR_RAW(&hpbCoreRegs->MTR[chipSelect], retval);

        /* Initialize MBAR_x Register */
        CSL_REG32_WR_RAW(&hpbCoreRegs->MBAR[chipSelect], HYPERBUS_MEM_OFFSET);

        /* Set target to Memory Space */
        memCfg.cfg_reg_target  = HYPERBUS_MCR_MEM_SPACE;
        retval = HYPERBUS_makeMemCfg(handle, &memCfg);
        CSL_REG32_WR_RAW(&hpbCoreRegs->MCR[chipSelect], retval);
    }
    else if (deviceType == (uint32_t)HYPERBUS_DEVICETYPE_NONE)
    {
            status = SystemP_FAILURE;
    }
    else
    {
        /* other device configuration*/
    }
    return status;
}

uint32_t HYPERBUS_getHyperBusDataBaseAddr(HYPERBUS_Handle handle)
{
    uint32_t dataBaseAddr = 0U;

    if(NULL != handle)
    {
        const HYPERBUS_Attrs *attrs = ((HYPERBUS_Config *)handle)->attrs;
        dataBaseAddr = attrs->dataBaseAddr;
    }

    return dataBaseAddr;
}
