/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/pmic.h>
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/i2c.h>

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
    /**<  Lock to protect PMIC open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} PMIC_DrvObj;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Function to init PMIC handle with default values*/
static inline void PMIC_handleInit(Pmic_CoreHandle_t *pmicHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern PMIC_Config gPmicConfig[];
extern uint32_t gPmicConfigNum;

/** \brief Driver object to protect open and close */
static PMIC_DrvObj gPmicDrvObj =
{
    .openLock      = NULL,
};

/* Driver lock object to protect critical sections */
static SemaphoreP_Object gPmicLldLockObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void PMIC_init(void)
{
    int32_t status;

    /* Create the driver open lock */
    status = SemaphoreP_constructMutex(&gPmicDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gPmicDrvObj.openLock = &gPmicDrvObj.lockObj;
    }

    /* Create the LLD driver critical section lock */
    status = SemaphoreP_constructMutex(&gPmicLldLockObj);

    return;
}

void PMIC_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gPmicDrvObj.openLock)
    {
        SemaphoreP_destruct(&gPmicDrvObj.lockObj);
        gPmicDrvObj.openLock = NULL;
    }

    /* Delete the LLD driver critical section lock */
    SemaphoreP_destruct(&gPmicLldLockObj);

    return;
}

PMIC_Handle PMIC_open(uint32_t instanceId, const PMIC_Params *params)
{
    int32_t         status = PMIC_ST_SUCCESS;
    PMIC_Config *config = NULL;

    if(instanceId < gPmicConfigNum)
    {
        config = &gPmicConfig[instanceId];
        if((NULL != config->pmicCoreHandle) && (NULL != config->pmicConfigData))
        {
            if((config->pmicConfigData->commMode == PMIC_INTF_SINGLE_I2C) ||
            (config->pmicConfigData->commMode == PMIC_INTF_DUAL_I2C))
            {
                config->pmicConfigData->pCommHandle  = I2C_getHandle(params->mainDrvinstance);
                config->pmicConfigData->validParams |= PMIC_CFG_COMM_HANDLE_VALID_SHIFT;
                if(config->pmicConfigData->commMode == PMIC_INTF_DUAL_I2C)
                {
                    config->pmicConfigData->pQACommHandle = I2C_getHandle(params->qaWdogDrvinstance);
                    config->pmicConfigData->validParams  |= PMIC_CFG_QACOMM_HANDLE_VALID_SHIFT;
                }
            }

            /* Protect this region from a concurrent PMIC_open */
            DebugP_assert(NULL != gPmicDrvObj.openLock);
            (void)SemaphoreP_pend(&gPmicDrvObj.lockObj, SystemP_WAIT_FOREVER);

            PMIC_handleInit(config->pmicCoreHandle);
            status = Pmic_init(config->pmicConfigData, config->pmicCoreHandle);
            if(PMIC_ST_SUCCESS != status)
            {
                PMIC_close(config);
                config = NULL;
            }

            SemaphoreP_post(&gPmicDrvObj.lockObj);
        }
        else
        {
            config = NULL;
        }
    }

    return (PMIC_Handle)config;
}

PMIC_Handle PMIC_getHandle(uint32_t instanceId)
{
    PMIC_Handle handle = NULL;

    if(instanceId < gPmicConfigNum)
    {
        handle = (PMIC_Handle)&gPmicConfig[instanceId];
    }

    return handle;
}

void PMIC_close(PMIC_Handle handle)
{
    int32_t         status = PMIC_ST_SUCCESS;
    PMIC_Config *config = (PMIC_Config *)handle;

    if(config && config->pmicCoreHandle)
    {
        DebugP_assert(NULL != gPmicDrvObj.openLock);
        (void)SemaphoreP_pend(&gPmicDrvObj.lockObj, SystemP_WAIT_FOREVER);

        status = Pmic_deinit(config->pmicCoreHandle);
        DebugP_assert(status == PMIC_ST_SUCCESS);

        SemaphoreP_post(&gPmicDrvObj.lockObj);
    }

    return;
}

void PMIC_critSecStartFn(void)
{
    (void)SemaphoreP_pend(&gPmicLldLockObj, SystemP_WAIT_FOREVER);
}

void PMIC_critSecStopFn(void)
{
    SemaphoreP_post(&gPmicLldLockObj);
}

static inline void PMIC_handleInit(Pmic_CoreHandle_t *pmicHandle)
{
    pmicHandle->pPmic_SubSysInfo = NULL;
    pmicHandle->drvInitStatus = 0x00;
    pmicHandle->pmicDeviceType = 0xFF;
    pmicHandle->pmicDevRev = 0xFF;
    pmicHandle->pmicDevSiliconRev = 0xFF;
    pmicHandle->commMode = 0xFF;
    pmicHandle->slaveAddr = 0xFF;
    pmicHandle->qaSlaveAddr = 0xFF;
    pmicHandle->nvmSlaveAddr = 0xFF;
    pmicHandle->i2c1Speed = 0xFF;
    pmicHandle->i2c2Speed = 0xFF;
    pmicHandle->crcEnable = false;
    pmicHandle->pCommHandle = NULL;
    pmicHandle->pQACommHandle = NULL;
    pmicHandle->pFnPmicCommIoRead = NULL;
    pmicHandle->pFnPmicCommIoWrite = NULL;
    pmicHandle->pFnPmicCritSecStart = NULL;
    pmicHandle->pFnPmicCritSecStop = NULL;
}
