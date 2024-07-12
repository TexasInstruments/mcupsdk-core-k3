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

/**
 *  \file panel.c
 *
 *  \brief File containing Panel Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/panel.h>
#include <drivers/hw_include/csl_types.h>
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
    /**<  Lock to protect Panel open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} Panel_DrvObj;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Panel_Config gPanelConfig[];
extern uint32_t gPanelConfigNum;

/** \brief Driver object */
static Panel_DrvObj gPanelDrvObj =
{
    .openLock      = NULL,
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t Panel_initPanelPinControl(Panel_Config *config);
static void Panel_deinitPanelPinControl(Panel_Config *config);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Panel_init(void)
{
    int32_t status;

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gPanelDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gPanelDrvObj.openLock = &gPanelDrvObj.lockObj;
    }

    return;
}

void Panel_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gPanelDrvObj.openLock)
    {
        SemaphoreP_destruct(&gPanelDrvObj.lockObj);
        gPanelDrvObj.openLock = NULL;
    }

    return;
}

Panel_Handle Panel_open(uint32_t instanceId, Panel_Params *params)
{
    Panel_Config *config = NULL;

    if(instanceId < gPanelConfigNum)
    {
        config = &gPanelConfig[instanceId];

        if(config->fxns && config->fxns->openFxn)
        {
            int32_t status;

            config->inputParams = params;
            /* Protect this region from a concurrent Panel_open */
            DebugP_assert(NULL != gPanelDrvObj.openLock);
            SemaphoreP_pend(&gPanelDrvObj.lockObj, SystemP_WAIT_FOREVER);

            status = Panel_initPanelPinControl(config);

            status += config->fxns->openFxn(config, params);

            status += SemaphoreP_constructBinary(&config->lockSem,  1U);

            if(status != SystemP_SUCCESS)
            {
                config = NULL;
            }

            SemaphoreP_post(&gPanelDrvObj.lockObj);
        }
    }

    return config;
}

void Panel_close(Panel_Handle handle)
{
    Panel_Config *config = (Panel_Config*)handle;

    if(config && config->fxns && config->fxns->closeFxn)
    {
        DebugP_assert(NULL != gPanelDrvObj.openLock);
        SemaphoreP_pend(&gPanelDrvObj.lockObj, SystemP_WAIT_FOREVER);

        config->fxns->closeFxn(config, (Panel_Params *)config->inputParams);

        Panel_deinitPanelPinControl(config);

        SemaphoreP_destruct(&config->lockSem);

        SemaphoreP_post(&gPanelDrvObj.lockObj);
    }
}

Panel_Handle Panel_getHandle(uint32_t instanceId)
{
    Panel_Config *config = NULL;

    if(instanceId < gPanelConfigNum)
    {
        config = &gPanelConfig[instanceId];
    }

    return config;
}

int32_t Panel_control(Panel_Handle handle, uint32_t cmd, void *cmdArgs)
{
    Panel_Config *config = (Panel_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->controlFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->controlFxn(config, \
                                           (Panel_Params *)config->inputParams,\
                                           cmd, \
                                           cmdArgs);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }

    return status;
}

int32_t Panel_reset(Panel_Handle handle)
{
    Panel_Config *config = (Panel_Config*)handle;
    int32_t status = SystemP_FAILURE;

    if(config && config->fxns && config->fxns->resetFxn)
    {
        /* Take the instance semaphore */
        status = SemaphoreP_pend(&config->lockSem, SystemP_WAIT_FOREVER);

        status += config->fxns->resetFxn(config, \
                                         (Panel_Params *)config->inputParams);

        /* Post the instance Semaphore. */
        SemaphoreP_post(&config->lockSem);
    }
    
    return status;
}

uint32_t Panel_getPanelInterfaceIndex(uint32_t panelType)
{
    uint32_t panelIndex = 0;
    Panel_Config *config = NULL;

    for (uint8_t count = 0; count < gPanelConfigNum; count++)
    {
        config = &gPanelConfig[count];
        if(config->panelType == panelType)
        {
            panelIndex = count;
            break;
        }
    }

    return panelIndex;
}

/* ========================================================================== */
/*                          Internal Functions                                */
/* ========================================================================== */

static int32_t Panel_initPanelPinControl(Panel_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    TCA6424_Params  tca6424Params;
    Panel_PinCtrl *pinCtrl = NULL;

    if(config != NULL)
    {
        pinCtrl = config->pinConfig;
        TCA6424_Params_init(&tca6424Params);
        tca6424Params.i2cInstance = pinCtrl->pinCtrlI2cInstance;
        tca6424Params.i2cAddress = pinCtrl->pinCtrlI2cAddr;

        status = TCA6424_open(&pinCtrl->ioExpConfig, &tca6424Params);

        if(status == SystemP_SUCCESS)
        {
            for(uint32_t count = 0U; count < pinCtrl->numPins && \
                status == SystemP_SUCCESS; count++)
            {
                status += TCA6424_config(&pinCtrl->ioExpConfig, \
                                         pinCtrl->pinConf[count].pinIoNum, \
                                         pinCtrl->pinConf[count].pinType);

                status += TCA6424_setOutput(&pinCtrl->ioExpConfig, \
                                            pinCtrl->pinConf[count].pinIoNum,\
                                            pinCtrl->pinConf[count].pinVal);
            }
        }
    }
    else
    {
        status= SystemP_FAILURE;
    }

    return status;
}

static void Panel_deinitPanelPinControl(Panel_Config *config)
{
    Panel_PinCtrl *pinCtrl = NULL;

    if(config != NULL)
    {
        pinCtrl = config->pinConfig;
        TCA6424_close(&pinCtrl->ioExpConfig);
    }
}
