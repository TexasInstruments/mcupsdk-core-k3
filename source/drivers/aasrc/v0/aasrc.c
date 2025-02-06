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
 *  \file aasrc.c
 *
 *  \brief File containing AASRC Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* This is needed for memset/memcpy */
#include "aasrc.h"
#include <kernel/dpl/CacheP.h>
#include <drivers/soc.h>
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>
#include <drivers/hw_include/hw_types.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    void *openLock;
    /**< Lock to protect AASRC open*/
    SemaphoreP_Object openLockObj;
    /**< Lock object */
} AASRC_DrvObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Driver internal functions */
static int32_t AASRC_validateOpenParams(uint8_t instNum, const AASRC_OpenParams *openPrms);
static int32_t AASRC_programInstance(AASRC_Config *drvCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Driver object */
static AASRC_DrvObj gAasrcDrvObj =
{
    .openLock      = NULL,
};

AASRC_gAasrcDrvState gAasrcDrvState[AASRC_INSTANCE_COUNT];

/* ========================================================================== */
/*                      API Function Definitions                              */
/* ========================================================================== */

void AASRC_init(void)
{
    int32_t status;
    uint32_t count;
    AASRC_Object *obj;

    /* Init each driver instance object */
    for(count = 0U; count < gAasrcInstNum; count++)
    {
        /* Init object variables */
        obj = gAasrcConfig[count].object;
        DebugP_assert(NULL != obj);
        memset(obj, 0U, sizeof(AASRC_Object));
    }

    /* Create the driver and channel lock */
    status = SemaphoreP_constructMutex(&gAasrcDrvObj.openLockObj);
    if(SystemP_SUCCESS == status)
    {
       gAasrcDrvObj.openLock = &gAasrcDrvObj.openLockObj;
    }
    status = SemaphoreP_constructMutex(&gAasrcChLockObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
       gAasrcChLockObj.lock = &gAasrcChLockObj.lockObj;
    }

    return;
}

void AASRC_deinit(void)
{
    /* Delete driver and channel lock */
    if (NULL != gAasrcDrvObj.openLock)
    {
       SemaphoreP_destruct(&gAasrcDrvObj.openLockObj);
       gAasrcDrvObj.openLock = NULL;
    }
    if (NULL != gAasrcChLockObj.lock)
    {
       SemaphoreP_destruct(&gAasrcChLockObj.lockObj);
       gAasrcChLockObj.lock = NULL;
    }

    return;
}

AASRC_Handle AASRC_open(uint32_t instNum, const AASRC_OpenParams *openParams)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *obj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t i;

    /* Check for valid instance number */
    if (instNum >= gAasrcInstNum)
    {
        status = AASRC_EINVALID_PARAMS;
    }
    else
    {
        drvCfg = &gAasrcConfig[instNum];
    }

    /* Protect this region from a concurrent AASRC_open */
    DebugP_assert(NULL != gAasrcDrvObj.openLock);
    SemaphoreP_pend(&gAasrcDrvObj.openLockObj, SystemP_WAIT_FOREVER);

    if (AASRC_SOK == status)
    {
        DebugP_assert(NULL != drvCfg);
        obj = drvCfg->object;
        attrs = drvCfg->attrs;
        DebugP_assert(NULL != obj);
        DebugP_assert(NULL != attrs);

        if(1U == obj->isOpen)
        {
            /* Handle already opened */
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        /* Init object handle */
        obj->drvHandle = (AASRC_Handle)drvCfg;
        if (NULL != openParams)
        {
            memcpy(&obj->openParams, openParams, sizeof(AASRC_OpenParams));
        }
        else
        {
            /* Init with default if NULL is passed */
            AASRC_OpenParamsInit(&obj->openParams);
        }
        /* Validate input param */
        status = AASRC_validateOpenParams(instNum, &obj->openParams);
    }

    if (AASRC_SOK == status)
    {
        /* Register interrupts */
        if (obj->openParams.transferMode == AASRC_TRANSFER_MODE_INTERRUPT)
        {
            status = AASRC_RegisterHwEventInterrupts(obj->drvHandle);
            status += AASRC_RegisterHwErrorInterrupts(obj->drvHandle);

        }
    }

    if (AASRC_SOK == status)
    {
        /* Initializing the global state holding variables. */
        for (i = 0U; i < AASRC_MAX_NUM_MONO_CHANNELS; i++)
        {
            gAasrcDrvState[instNum].monoChUsageArray[i] = (int8_t)(-1);
        }
        for (i = 0U; i < AASRC_MAX_NUM_GROUP_CHANNELS; i++)
        {
            gAasrcDrvState[instNum].grpUsageArray[i] = (int8_t)(-1);
        }
        memset(&gAasrcDrvState[instNum].chState[0U], 0U,
                sizeof(AASRC_ChState)*AASRC_MAX_NUM_ASRC_CHANNELS);

        /* Program AASRC instance according the user config */
        status = AASRC_programInstance(drvCfg);
    }

    if(AASRC_SOK == status)
    {
        obj->isOpen = 1U;
    }

    SemaphoreP_post(&gAasrcDrvObj.openLockObj);

    /* Free up resources in case of error */
    if(AASRC_SOK != status)
    {
        if(NULL != drvCfg)
        {
            AASRC_close(obj->drvHandle);
        }
    }
    return obj->drvHandle;
}

void AASRC_close(AASRC_Handle handle)
{
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *obj = NULL;
    uint8_t i;

    if (handle != NULL)
    {
        drvCfg = (AASRC_Config *)handle;
        DebugP_assert(NULL != drvCfg);
        obj = drvCfg->object;
        DebugP_assert(NULL != obj);

        /* Protect this region from a concurrent AASRC_close */
        DebugP_assert(NULL != gAasrcDrvObj.openLock);
        SemaphoreP_pend(&gAasrcDrvObj.openLockObj, SystemP_WAIT_FOREVER);

        /* Destruct all Hwi objects */
        if (AASRC_TRANSFER_MODE_INTERRUPT == obj->openParams.transferMode)
        {
            for (i = 0U; i < AASRC_PROCESSOR_INTERRUPT_COUNT; i++)
            {
                HwiP_destruct(&obj->hwiObj[i]);
            }
        }

        /* Closing all the channels before closing the driver */
        for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
        {
            if (obj->chObj[i].isOpen)
            {
                AASRC_chClose((AASRC_ChHandle)(&obj->chObj[i]));
            }
        }

        obj->isOpen = 0U;
        SemaphoreP_post(&gAasrcDrvObj.openLockObj);
    }

    return;
}

AASRC_Handle AASRC_getHandle(uint32_t index)
{
    AASRC_Handle handle = NULL;
    /* Check index */
    if(index < gAasrcInstNum)
    {
        AASRC_Object *obj;
        obj = gAasrcConfig[index].object;

        if(obj && (TRUE == obj->isOpen))
        {
            /* valid handle */
            handle = obj->drvHandle;
        }
    }
    return handle;
}

void AASRC_softReset(AASRC_Handle drvHandle)
{
    AASRC_Config *drvCfg = (AASRC_Config *)drvHandle;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    const CSL_aasrc_cfgRegs *pReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    volatile uint32_t timeout = AASRC_SOFTRESET_CYCLES;

    /* writing the soft reset bit of the aasrc instance to 1 (resetting) */
    CSL_REG32_FINS(&pReg->AASRC_SYSCONFIG, AASRC_CFG_AASRC_SYSCONFIG_SOFTRESET, 1U);

    /* waiting for the timeout to occure */
    while (timeout > 0U)
    {
        timeout--;
    };

    /* writing the soft reset bit of the aasrc instance to 0 (getting out of reset) */
    CSL_REG32_FINS(&pReg->AASRC_SYSCONFIG, AASRC_CFG_AASRC_SYSCONFIG_SOFTRESET, 0U);
}

/* ========================================================================== */
/*                          Local Function Definitions                        */
/* ========================================================================== */

/* Internal functions */
static int32_t AASRC_programInstance(AASRC_Config *drvCfg)
{
    int32_t status = AASRC_SOK;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    const CSL_aasrc_cfgRegs *pReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    uint8_t rxSyncPin, txSyncPin;
    uint32_t rxExtClkSrc, txExtClkSrc;
    uint8_t i;
    uint8_t clkConfigRxMap[AASRC_RXSYNC_PIN_COUNT] = {0U};
    uint8_t clkConfigTxMap[AASRC_TXSYNC_PIN_COUNT] = {0U};

    /* Configure MMR to route clock to rxSync / txSync Pin as per clock zone config
     * Avoid reconfiguring same pin to different clock source,
     * Skip the configuration for a pin if it is already taken by another config */

    if(AASRC_SOK == status)
    {
        for(i =0U; i < gAasrcRxClkZoneNum[attrs->instNum]; i++)
        {
            /* Configure rxSync pins of all Clock Zone configs added */
            rxSyncPin =  obj->openParams.rxClkZoneCfg[i].syncPin;
            rxExtClkSrc =  obj->openParams.rxClkZoneCfg[i].extClkSrc;

            if( clkConfigRxMap[rxSyncPin] == 0U )
            {
                /* This pin is not configured before by any channel config */
                /* Configure Rx Sync Pin */
                status = AASRC_extClkSrcRxConfig(attrs->instNum, rxSyncPin, rxExtClkSrc);
                clkConfigRxMap[rxSyncPin] = rxExtClkSrc;
            }
            else
            {
                /* This pin is already being configured by another channel config */
                /* Check the required config is already set before*/
                if( clkConfigRxMap[rxSyncPin] == rxExtClkSrc)
                {
                    /* Skip reconfiguring same */
                }
                else
                {
                    /* Current Channel requires different config for the same pin */
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
        for(i =0U; i < gAasrcTxClkZoneNum[attrs->instNum]; i++)
        {
            /* Configure txSync pins of all Clock Zone configs added */
            txSyncPin =  obj->openParams.txClkZoneCfg[i].syncPin;
            txExtClkSrc =  obj->openParams.txClkZoneCfg[i].extClkSrc;

            if( clkConfigTxMap[txSyncPin] == 0U )
            {
                /* This pin is not configured before by any channel config */
                /* Configure Tx Sync Pin */
                status = AASRC_extClkSrcTxConfig(attrs->instNum, txSyncPin, txExtClkSrc);
                clkConfigTxMap[txSyncPin] = txExtClkSrc;
            }
            else
            {
                /* This pin is already being configured by another channel config */
                /* Check the required config is already set before*/
                if( clkConfigTxMap[txSyncPin] == txExtClkSrc)
                {
                    /* Skip reconfiguring same */
                }
                else
                {
                    /* Current Channel requires different config for the same pin */
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
    }

    if(AASRC_SOK == status)
    {
        /* Applying soft reset */
        AASRC_softReset((AASRC_Handle)drvCfg);

        /* Set sample data alignment enable/disable */
        CSL_REG32_FINS(&pReg->AASRC_SYSCONFIG, AASRC_CFG_AASRC_SYSCONFIG_DATA_FORMAT_DISABLE,
                       (obj->openParams.isDataAlignmentDisabled));
    }

    return status;
}


static int32_t AASRC_validateOpenParams(uint8_t instNum, const AASRC_OpenParams *openPrms)
{
    int32_t status = AASRC_SOK;

    if( AASRC_TRANSFER_MODE_INTERRUPT != openPrms->transferMode )
    {
        status = AASRC_EINVALID_PARAMS;
    }

    if( status == AASRC_SOK)
    {
        /* Validate data alignment */
        if (openPrms->isDataAlignmentDisabled > 1U)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }

    return status;
}
