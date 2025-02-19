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

/* *
 *  \file   psci.c
 *
 *  \brief  File containing PSCI Driver APIs implementation for V0.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SystemP.h>
#include <drivers/psci.h>
#include <drivers/scp/smccc/smccc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    void                   *lock;
    /* *< Driver lock - to protect across open/close */
    SemaphoreP_Object       lockObj;
    /* *< Driver lock object */
} PSCI_DrvObj;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static inline uint32_t PSCI_function(uint32_t functionId, uint32_t arg0, uint32_t arg1, uint32_t arg2);
static inline int32_t PSCI_handleErr(int32_t errNo);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Externs */
extern PSCI_Config gPSCIConfig[];
extern uint32_t gPSCIConfigNum;

/* * \brief Driver object */
static PSCI_DrvObj gPSCIDrvObj =
{
    .lock = NULL,
};

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

void PSCI_init(void)
{
    PSCI_Handle handle;
    uint32_t i;

    /* Call init function for each config */
    for(i = 0; i < gPSCIConfigNum; i++)
    {
        handle = &gPSCIConfig[i];
        /* Input parameter validation */
        if (handle->object != NULL)
        {
            /* Mark the object as available */
            handle->object->isOpen = (bool)false;
        }
    }
    /* Create driver lock */
    (void)SemaphoreP_constructMutex(&gPSCIDrvObj.lockObj);
    gPSCIDrvObj.lock = &gPSCIDrvObj.lockObj;
}

void PSCI_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gPSCIDrvObj.lock)
    {
        SemaphoreP_destruct(&gPSCIDrvObj.lockObj);
        gPSCIDrvObj.lock = NULL;
    }
}

PSCI_Handle PSCI_open(uint32_t idx)
{
    PSCI_Handle          handle = NULL;
    PSCI_Object          *object = NULL;
    int32_t              status = SystemP_SUCCESS;
    uint32_t psciVer;

    /* Check index */
    if(idx >= gPSCIConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        handle = ( PSCI_Handle)&(gPSCIConfig[idx]);
    }

    DebugP_assert(NULL != gPSCIDrvObj.lock);
    (void)SemaphoreP_pend(&gPSCIDrvObj.lockObj, SystemP_WAIT_FOREVER);

    if(status == SystemP_SUCCESS)
    {
        object = ( PSCI_Object*)handle->object;
        DebugP_assert(NULL != object);
        if(object->isOpen)
        {
            /* Handle already opened */
            status = SystemP_FAILURE;
            handle = NULL;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* Mark the handle as being used */
        object->isOpen = (bool)true;

        /* Create object lock */
        status = SemaphoreP_constructMutex(&object->mutex);

        if (status == SystemP_SUCCESS)
        {
            /* Get PSCI version for sanity */
            status = PSCI_getPSCIVersion(handle, &psciVer);

            /* Print PSCI version. */
            DebugP_log("PSCI Major version %d\r\n", PSCI_MAJOR_VERSION(psciVer));
            DebugP_log("PSCI Minor version %d\r\n", PSCI_MINOR_VERSION(psciVer));
        }
    }

    /* Close the driver object if initialization does not go through */
    if(status != SystemP_SUCCESS)
    {
        PSCI_close(handle);
    }

    SemaphoreP_post(&gPSCIDrvObj.lockObj);
    return (handle);
}

void PSCI_close(PSCI_Handle handle)
{
    PSCI_Object          *object = NULL;

    if(handle != NULL)
    {
        object = ( PSCI_Object *)handle->object;
        DebugP_assert(NULL != object);

        DebugP_assert(NULL != gPSCIDrvObj.lock);
        (void)SemaphoreP_pend(&gPSCIDrvObj.lockObj, SystemP_WAIT_FOREVER);

        /* Destruct the instance lock */
        (void)SemaphoreP_destruct(&object->mutex);

        SemaphoreP_post(&gPSCIDrvObj.lockObj);
    }
}

PSCI_Handle PSCI_getHandle(uint32_t driverInstanceIndex)
{
    PSCI_Handle         handle = NULL;
    /* Check instanceIndex */
    if(driverInstanceIndex < gPSCIConfigNum)
    {
        PSCI_Object *obj;
        obj = gPSCIConfig[driverInstanceIndex].object;

        if(obj && obj->isOpen)
        {
            /* valid handle */
            handle = (PSCI_Handle)&gPSCIConfig[driverInstanceIndex];
        }
    }

    return handle;
}

uint32_t PSCI_getInitDriverIndex(void)
{
    uint32_t instanceIndex = 0xFF;

    for(uint8_t count = 0U; count < gPSCIConfigNum; count++)
    {
        PSCI_Object *obj;
        obj = gPSCIConfig[count].object;
        if(obj && obj->isOpen)
        {
            instanceIndex = count;
            break;
        }
    }
    return instanceIndex;
}

int32_t PSCI_getPSCIVersion(PSCI_Handle handle, uint32_t *psciVer)
{
    PSCI_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (psciVer != NULL))
    {
        object = (PSCI_Object*)handle->object;

        /* Acquire the lock for this particular PSCI handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        *psciVer = PSCI_function(PSCI_FUNC_PSCI_VERSION, 0, 0, 0);

        /* Release the lock for this particular PSCI handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t PSCI_cpuOff(PSCI_Handle handle)
{
    PSCI_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;
    int32_t err;

    if(handle != NULL)
    {
        object = (PSCI_Object*)handle->object;

        /* Acquire the lock for this particular PSCI handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        err = PSCI_function(PSCI_FUNC_CPU_OFF, 0, 0, 0);

        /* We should never reach here as the CPU should be turned off before this point.*/
        status = PSCI_handleErr(err);

        /* Release the lock for this particular PSCI handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t PSCI_cpuOn(PSCI_Handle handle, uint32_t cpuId, uint32_t entryPoint)
{
    PSCI_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;
    int32_t err;

    if(handle != NULL)
    {
        object = (PSCI_Object*)handle->object;

        /* Acquire the lock for this particular PSCI handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        err = PSCI_function(PSCI_FUNC_CPU_ON_64BIT, cpuId, entryPoint, 0);

        status = PSCI_handleErr(err);

        /* Release the lock for this particular PSCI handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t PSCI_systemReset(PSCI_Handle handle)
{
    PSCI_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;
    int32_t err;

    if(handle != NULL)
    {
        object = (PSCI_Object*)handle->object;

        /* Acquire the lock for this particular PSCI handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        err = PSCI_function(PSCI_FUNC_SYSTEM_RESET, 0, 0, 0);

        /* We should never reach here as the system reset should have happened before this point.*/
        status = PSCI_handleErr(err);

        /* Release the lock for this particular PSCI handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t PSCI_getFeatures(PSCI_Handle handle, uint32_t functionId, uint32_t *feature)
{
    PSCI_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (feature != NULL))
    {
        object = (PSCI_Object*)handle->object;

        /* Acquire the lock for this particular PSCI handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        *feature = PSCI_function(PSCI_FUNC_PSCI_FEATURES, functionId, 0, 0);

        /* Release the lock for this particular PSCI handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/* ========================================================================== */
/*                     API ISR Function Definitions                           */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

static inline uint32_t PSCI_function(uint32_t functionId, uint32_t arg0, uint32_t arg1, uint32_t arg2)
{
	SMCCC_Res res;

	smccc_smc(functionId, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	return (uint32_t) res.a0;
}

static inline int32_t PSCI_handleErr(int32_t errNo)
{
    int32_t err;

    switch (errNo) {
	case PSCI_SUCCESS:
		err = SystemP_SUCCESS;
        break;
	case PSCI_NOT_SUPPORTED:
	case PSCI_INVALID_PARAMS:
    case PSCI_DENIED:
    case PSCI_ALREADY_ON:
    case PSCI_ON_PENDING:
    case PSCI_INTERNAL_FAILURE:
    case PSCI_NOT_PRESENT:
    case PSCI_DISABLED:
	case PSCI_INVALID_ADDRESS:
        err = SystemP_FAILURE;
        break;
    default:
		err = SystemP_FAILURE;
        break;
    }

    return err;
}
