/*
 *  Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \file gpmc_v0.c
 *
 *  \brief File containing GPMC Driver APIs implementation for version V1.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/gpmc.h>
#include <drivers/elm.h>

//#include "gpmc.h" //todo:
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void *openLock;
    /**<  Lock to protect GPMC open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} GPMC_DrvObj;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Internal functions */
static uint32_t GPMC_ECCBCHResultGet(GPMC_Handle handle, uint32_t resIndex);
static void GPMC_ECCResultSizeSelect(GPMC_Handle handle, uint32_t eccResReg,
                             uint32_t eccSize);

static void GPMC_nandADDRwrite(GPMC_Handle handle, uint32_t address);
static void GPMC_nandCMDwrite(GPMC_Handle handle, uint32_t cmd);
static void GPMC_transferCallback(GPMC_Handle handle, GPMC_Transaction *msg);
static int32_t GPMC_programInstance(GPMC_Config *config);
static void GPMC_disableInterupt(uint32_t baseAddr, uint32_t interupt);
static void GPMC_enableInterupt(uint32_t baseAddr, uint32_t interupt);
static void GPMC_interuptStatusClear(uint32_t baseAddr, uint32_t interupt);
static uint32_t  GPMC_interuptStatusGet(uint32_t baseAddr, uint32_t interupt);
static void GPMC_waitPinPolaritySelect(GPMC_Handle handle, uint32_t pin,
                                uint32_t polarity);
static int32_t GPMC_waitpinInteruptStatusReadywaitTimeout(GPMC_Handle handle,
                                uint32_t timeOut);
static int32_t GPMC_waitpinStatusReadywaitTimeout(GPMC_Handle handle,
                                uint32_t timeOut);
static uint32_t GPMC_waitPinStatusGet(uint32_t baseAddr, uint32_t pin);
static int32_t GPMC_moduleResetStatuswaitTimeout(GPMC_Config *config,
                                uint32_t timeOut);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Driver object */
static GPMC_DrvObj gGpmcDrvObj =
{
    .openLock      = NULL,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void GPMC_init(void)
{
    int32_t status = SystemP_SUCCESS;
    GPMC_Object *obj;

    for(uint8_t count =0; count < gGpmcConfigNum; count++)
    {
        /* Init object variables */
        obj = gGpmcConfig[count].object;
        DebugP_assert(NULL != obj);
        memset(obj, 0, sizeof(GPMC_Object));
    }

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gGpmcDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gGpmcDrvObj.openLock = &gGpmcDrvObj.lockObj;
    }

    return;
}

void GPMC_deinit(void)
{
    if(gGpmcDrvObj.openLock != NULL)
    {
        SemaphoreP_destruct(&gGpmcDrvObj.lockObj);
        gGpmcDrvObj.openLock = NULL;
    }

    return;
}

static void GPMC_hwiFxn_v1(void *arg)
{
    //todo:
}

static int32_t GPMC_moduleResetStatuswaitTimeout(GPMC_Config *config, uint32_t timeOut)
{
    int32_t status  =   SystemP_SUCCESS;
    const GPMC_HwAttrs *hwAttrs = config->attrs;
    uint64_t curTime = 0;

    if(timeOut != 0)
    {
        curTime = ClockP_getTimeUsec();

        while((CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_SYSSTATUS, GPMC_SYSSTATUS_RESETDONE) != CSL_GPMC_SYSSTATUS_RESETDONE_RSTDONE) &&
            ((ClockP_getTimeUsec() - curTime) < timeOut))
        {
            uint32_t delay = 100;
            while(delay--);
        }

        if(CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_SYSSTATUS, GPMC_SYSSTATUS_RESETDONE) != CSL_GPMC_SYSSTATUS_RESETDONE_RSTDONE)
        {
            return SystemP_FAILURE;
        }

    }
    else
    {
        if(CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_SYSSTATUS, GPMC_SYSSTATUS_RESETDONE) != CSL_GPMC_SYSSTATUS_RESETDONE_RSTDONE)
        {
            return SystemP_FAILURE;
        }
    }

    return status;

 }

static uint32_t GPMC_waitPinStatusGet(uint32_t baseAddr, uint32_t pin)
{
    uint32_t pinStatus;

    pinStatus = 0;

    if (pin == CSL_GPMC_CONFIG1_WAITPINSELECT_W0)
    {
        pinStatus = CSL_REG32_FEXT(baseAddr + CSL_GPMC_STATUS,
                                  GPMC_STATUS_WAIT0STATUS);
    }
    else if (pin == CSL_GPMC_CONFIG1_WAITPINSELECT_W1)
    {
        pinStatus = CSL_REG32_FEXT(baseAddr + CSL_GPMC_STATUS,
                                  GPMC_STATUS_WAIT1STATUS);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }

    return (pinStatus);
}

static int32_t GPMC_waitpinStatusReadywaitTimeout(GPMC_Handle handle, uint32_t timeOut)
{

    int32_t status  =   SystemP_SUCCESS;
    const GPMC_HwAttrs *hwAttrs = NULL;
    hwAttrs = ((GPMC_Config*)handle)->attrs;
    uint64_t curTime= 0;

    if(handle != NULL)
    {
        if(timeOut != 0)
        {
            curTime = ClockP_getTimeUsec();

            while((GPMC_waitPinStatusGet(hwAttrs->gpmcBaseAddr,hwAttrs->waitPinNum) == \
            CSL_GPMC_STATUS_WAIT0STATUS_W0ACTIVEL) && ((ClockP_getTimeUsec() - curTime) < timeOut))
            {
                uint32_t delay = 100;
                while(delay--);
            }

            if((GPMC_waitPinStatusGet(hwAttrs->gpmcBaseAddr,hwAttrs->waitPinNum) == \
            CSL_GPMC_STATUS_WAIT0STATUS_W0ACTIVEH))
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
        else
        {
            if((GPMC_waitPinStatusGet(hwAttrs->gpmcBaseAddr,hwAttrs->waitPinNum) == \
            CSL_GPMC_STATUS_WAIT0STATUS_W0ACTIVEH))
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;

 }

static int32_t GPMC_waitpinInteruptStatusReadywaitTimeout(GPMC_Handle handle, uint32_t timeOut)
{
    int32_t status  =   SystemP_SUCCESS;
    uint32_t            waitPinInterupt;
    uint64_t curTime = 0;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        if(hwAttrs->waitPinNum == CSL_GPMC_CONFIG1_WAITPINSELECT_W0)
        {
            waitPinInterupt = GPMC_WAIT0EDGEDETECTION_STATUS;
        }
        else if(hwAttrs->waitPinNum == CSL_GPMC_CONFIG1_WAITPINSELECT_W1)
        {
            waitPinInterupt = GPMC_WAIT1EDGEDETECTION_STATUS;
        }

        if(timeOut != 0)
        {

            curTime = ClockP_getTimeUsec();

            while((GPMC_interuptStatusGet(hwAttrs->gpmcBaseAddr,waitPinInterupt) == 0) \
            && ((ClockP_getTimeUsec() - curTime) < timeOut))
            {
                uint32_t delay = 100;
                while(delay--);
            }


            if(GPMC_interuptStatusGet(hwAttrs->gpmcBaseAddr,waitPinInterupt) == 1)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }

        }
        else
        {
            if(GPMC_interuptStatusGet(hwAttrs->gpmcBaseAddr,hwAttrs->waitPinNum) == 1)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;

 }

int32_t GPMC_configureTimingParameters(GPMC_Handle handle)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t timeConfig = 0;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object  = ((GPMC_Config*)handle)->object;


        /* CONFIG2 reister timing config, no extra delay */
        timeConfig = GPMC_CS_TIMING_CONFIG(hwAttrs->timingParams.csWrOffTime,
                                            hwAttrs->timingParams.csRdOffTime,
                                            hwAttrs->csExDelay,
                                            hwAttrs->timingParams.csOnTime);

        CSL_REG32_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG2(object->params.chipSel), timeConfig);


        /* CONFIG3 reister timing config, no extra delay */
        timeConfig = GPMC_ADV_TIMING_CONFIG(hwAttrs->timingParams.advAadMuxWrOffTime,
                                            hwAttrs->timingParams.advAadMuxRdOffTime,
                                            hwAttrs->timingParams.advWrOffTime,
                                            hwAttrs->timingParams.advRdOffTime,
                                            CSL_GPMC_CONFIG3_ADVEXTRADELAY_NOTDELAYED, //todo : make it part of structure
                                            hwAttrs->timingParams.advAadMuxOnTime,
                                            hwAttrs->timingParams.advOnTime);
        CSL_REG32_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG3(object->params.chipSel), timeConfig);

       /* CONFIG4 reister timing config, no xtra delay */
        timeConfig = GPMC_WE_OE_TIMING_CONFIG(hwAttrs->timingParams.weOffTime,
                                                CSL_GPMC_CONFIG4_WEEXTRADELAY_NOTDELAYED,
                                                hwAttrs->timingParams.weOnTtime,
                                                hwAttrs->timingParams.oeAadMuxOffTime,
                                                hwAttrs->timingParams.oeOffTime,
                                                CSL_GPMC_CONFIG4_OEEXTRADELAY_DELAYED,
                                                hwAttrs->timingParams.oeAadMuxOnTime,
                                                hwAttrs->timingParams.oeOnTime);

        CSL_REG32_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG4(object->params.chipSel), timeConfig);

        /* CONFIG5 reister timing config */
        timeConfig = GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG(hwAttrs->timingParams.rdCycleTime,
                                                            hwAttrs->timingParams.wrCycleTime,
                                                            hwAttrs->timingParams.rdAccessTime,
                                                            hwAttrs->timingParams.pageBurstAccess);
        CSL_REG32_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG5(object->params.chipSel), timeConfig);


        /* CONFIG6 reister timing config */
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG6(object->params.chipSel),
                    GPMC_CONFIG6_WRACCESSTIME, hwAttrs->timingParams.wrAcessTime);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG6(object->params.chipSel),
                    GPMC_CONFIG6_WRDATAONADMUXBUS, hwAttrs->timingParams.wrDataOnMuxBusTime);


        timeConfig = GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG(hwAttrs->timingParams.cycle2CycleDelay,
                                                                    hwAttrs->timingParams.cycleDelaySameChipSel,
                                                                    hwAttrs->timingParams.cycleDelayDiffChipSel,
                                                                    hwAttrs->timingParams.busTurnAroundTime);

        CSL_REG32_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG6(object->params.chipSel), \
        (CSL_REG32_RD(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG6(object->params.chipSel)) | timeConfig));

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}


static void GPMC_waitPinPolaritySelect(GPMC_Handle handle, uint32_t pin,
                                uint32_t polarity)
{
    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        if (pin == CSL_GPMC_CONFIG1_WAITPINSELECT_W0)
        {
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG, GPMC_CONFIG_WAIT0PINPOLARITY,
                        polarity);
        }
        else if (pin == CSL_GPMC_CONFIG1_WAITPINSELECT_W1)
        {
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG, GPMC_CONFIG_WAIT1PINPOLARITY,
                        polarity);
        }
        else
        {
            /*
            * Do nothing. Error will be generated by the hardware
            */
        }
    }
}


static uint32_t  GPMC_interuptStatusGet(uint32_t baseAddr, uint32_t interupt)
{
    uint32_t retVal;

    retVal = 0;

    switch (interupt)
    {
        case GPMC_FIFOEVENT_STATUS:
            retVal = CSL_REG32_FEXT(baseAddr + CSL_GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_FIFOEVENTSTATUS);
            break;
        case GPMC_TERMINALCOUNT_STATUS:
            retVal = CSL_REG32_FEXT(baseAddr + CSL_GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_TERMINALCOUNTSTATUS);
            break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
            retVal = CSL_REG32_FEXT(baseAddr + CSL_GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS);
            break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
            retVal = CSL_REG32_FEXT(baseAddr + CSL_GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS);
            break;

        default:
            break;
    }

    return (retVal);
}

static void GPMC_interuptStatusClear(uint32_t baseAddr, uint32_t interupt)
{
    switch (interupt)
    {
        case GPMC_FIFOEVENT_STATUS:
            CSL_REG32_FINS(baseAddr + CSL_GPMC_IRQSTATUS,
                          GPMC_IRQSTATUS_FIFOEVENTSTATUS,
                          CSL_GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT1_W);
            break;
        case GPMC_TERMINALCOUNT_STATUS:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQSTATUS, GPMC_IRQSTATUS_TERMINALCOUNTSTATUS,
                CSL_GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT1_W);
            break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQSTATUS,
                GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS,
                CSL_GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET1_W);
            break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQSTATUS,
                GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS,
                CSL_GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET1_W);
            break;

        default:
            break;
    }
}

static void GPMC_enableInterupt(uint32_t baseAddr, uint32_t interupt)
{
    switch (interupt)
    {
        case GPMC_FIFOEVENT_INT:
            CSL_REG32_FINS(baseAddr + CSL_GPMC_IRQENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE,
                          CSL_GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOENABLED);
            break;
        case GPMC_TERMINALCOUNT_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE,
                CSL_GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCENABLED);
            break;
        case GPMC_WAIT0EDGEDETECTION_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE,
                CSL_GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0ENABLED);
            break;
        case GPMC_WAIT1EDGEDETECTION_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE,
                CSL_GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1ENABLED);
            break;

        default:
            break;
    }
}

static void GPMC_disableInterupt(uint32_t baseAddr, uint32_t interupt)
{
    switch (interupt)
    {
        case GPMC_FIFOEVENT_INT:
            CSL_REG32_FINS(baseAddr + CSL_GPMC_IRQENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE,
                          CSL_GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOMASKED);
            break;
        case GPMC_TERMINALCOUNT_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE,
                CSL_GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCMASKED);
            break;
        case GPMC_WAIT0EDGEDETECTION_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE,
                CSL_GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0MASKED);
            break;
        case GPMC_WAIT1EDGEDETECTION_INT:
            CSL_REG32_FINS(
                baseAddr + CSL_GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE,
                CSL_GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1MASKED);
            break;

        default:
            break;
    }
}



static int32_t GPMC_programInstance(GPMC_Config *config)
{
    int32_t status = SystemP_SUCCESS;

    if(config != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = config->attrs;
        GPMC_Object *object  = config->object;

        /* Reset GPMC */
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_SYSCONFIG, GPMC_SYSCONFIG_SOFTRESET,CSL_GPMC_SYSCONFIG_SOFTRESET_RESET);

        status += GPMC_moduleResetStatuswaitTimeout(config,GPMC_MODULE_RESET_WAIT_TIME_MAX);

        if(status == SystemP_SUCCESS)
        {
            // /* Set SYSCONFIG register to no idle mode */
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_SYSCONFIG, GPMC_SYSCONFIG_IDLEMODE, CSL_GPMC_SYSCONFIG_IDLEMODE_NOIDLE);

            // /* Disable all interrupts */
            GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_FIFOEVENT_INT);
            GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_TERMINALCOUNT_INT);
            GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_WAIT0EDGEDETECTION_INT);
            GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_WAIT1EDGEDETECTION_INT);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG7(object->params.chipSel), GPMC_CONFIG7_CSVALID, CSL_GPMC_CONFIG7_CSVALID_CSDISABLED);

            /* Timeout control disable */
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_TIMEOUT_CONTROL,
                        GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE,
                        CSL_GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TODISABLED);
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_TIMEOUT_CONTROL,
                        GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE, 0);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_GPMCFCLKDIVIDER, hwAttrs->clkDivider );
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_MUXADDDATA,  hwAttrs->addrDataMux);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_WAITMONITORINGTIME, CSL_GPMC_CONFIG1_WAITMONITORINGTIME_ATVALID);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_WAITREADMONITORING, CSL_GPMC_CONFIG1_WAITREADMONITORING_WNOTMONIT);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_READTYPE, hwAttrs->readType);

            /* Set the wait pin polarity */
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_WAITPINSELECT,  hwAttrs->waitPinNum);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_TIMEPARAGRANULARITY, hwAttrs->timeLatency);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                        GPMC_CONFIG1_READMULTIPLE,  hwAttrs->accessType);


            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG7(object->params.chipSel),
                        GPMC_CONFIG7_BASEADDRESS, hwAttrs->chipSelBaseAddr >> GPMC_CS_BASE_ADDR_SHIFT); //todo : check

            /* Set chip select address */
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG7(object->params.chipSel),
                        GPMC_CONFIG7_MASKADDRESS,  hwAttrs->chipSelAddrSize);

            GPMC_waitPinPolaritySelect((GPMC_Handle*)config, hwAttrs->waitPinNum, hwAttrs->waitPinPol);

            GPMC_interuptStatusClear(hwAttrs->gpmcBaseAddr,GPMC_WAIT0EDGEDETECTION_STATUS);
            GPMC_enableInterupt(hwAttrs->gpmcBaseAddr,GPMC_WAIT0EDGEDETECTION_INT);

            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG7(object->params.chipSel), \
                            GPMC_CONFIG7_CSVALID, CSL_GPMC_CONFIG7_CSVALID_CSENABLED);

            status += GPMC_waitpinStatusReadywaitTimeout((GPMC_Handle)config, GPMC_WAIT_PIN_STATUS_WAIT_TIME_MAX);
        }

    }

    return status;
}

int32_t GPMC_SetDeviceType(GPMC_Handle handle, uint32_t deviceType)
{
    int32_t status = SystemP_SUCCESS;
    if(handle != NULL)
    {
        GPMC_Config *config = (GPMC_Config*)handle;
        const GPMC_HwAttrs *attrs = config->attrs;
        GPMC_Object *object = config->object;

        object->params.devType = deviceType;
        CSL_REG32_FINS(attrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                  GPMC_CONFIG1_DEVICETYPE, deviceType);

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t GPMC_SetDeviceSize(GPMC_Handle handle, uint32_t deviceSize)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        GPMC_Config *config = (GPMC_Config*)handle;
        const GPMC_HwAttrs *attrs = config->attrs;
        GPMC_Object *object = config->object;

        object->params.devSize = deviceSize;

        CSL_REG32_FINS(attrs->gpmcBaseAddr + CSL_GPMC_CONFIG1(object->params.chipSel),
                  GPMC_CONFIG1_DEVICESIZE, deviceSize);

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

GPMC_Handle GPMC_open(uint32_t index, const GPMC_Params *prms)
{
    int32_t status = SystemP_SUCCESS;
    GPMC_Handle         handle = NULL;
    GPMC_Config         *config = NULL;
    GPMC_Object         *object = NULL;
    const GPMC_HwAttrs  *hwAttrs = NULL;
    HwiP_Params         hwiParams;


    /* Check for valid index */
    if(index >= gGpmcConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        config = &gGpmcConfig[index];
    }

    /* Protect this region from a concurrent GPMC_Open */
    DebugP_assert(NULL != gGpmcDrvObj.openLock);
    SemaphoreP_pend(&gGpmcDrvObj.lockObj, SystemP_WAIT_FOREVER);

    if(status == SystemP_SUCCESS)
    {
        object = config->object;
        DebugP_assert(object != NULL);
        DebugP_assert(config->attrs != NULL);
        hwAttrs = config->attrs;
        if(object->isOpen == TRUE)
        {
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        object->handle = (GPMC_Handle)config;

        if(prms != NULL)
        {
            memcpy((void*)&object->params, (void*)prms, sizeof(GPMC_Params));
        }
        else
        {
            /* Init with default if NULL is passed */
            GPMC_Params_init(&object->params);
        }

        if(object->params.dmaEnable == TRUE)
        {
            //todo: dma configuration
        }
        else
        {
            object->dmaInfo = NULL;
        }

        if(object->params.transferMode == GPMC_TRANSFER_MODE_BLOCKING)
        {
            if(object->params.intrEnable == TRUE || object->params.dmaEnable == TRUE)
            {
                object->operMode = GPMC_OPERATING_MODE_BLOCKING;
            }
            else
            {
                object->operMode = GPMC_OPERATING_MODE_POLLING;
            }
        }
        else
        {
            object->operMode = GPMC_OPERATING_MODE_CALLBACK;
        }

        if(object->params.intrEnable == TRUE)
        {
            HwiP_Params_init(&hwiParams);
            hwiParams.intNum = hwAttrs->intrNum;
            hwiParams.callback = GPMC_hwiFxn_v1;
            hwiParams.args     = (void*)config;
            hwiParams.priority = hwAttrs->intrPriority;
            status += HwiP_construct(&object->hwi, &hwiParams);

        }

    }

    if(status == SystemP_SUCCESS)
    {
        status += GPMC_programInstance(config);

        status += SemaphoreP_constructMutex(&object->mutex);

        if (object->operMode == GPMC_OPERATING_MODE_BLOCKING)
        {
            /*
            * Semaphore to cause the waiting task to block for the GPMC
            * to finish
            */
            status += SemaphoreP_constructBinary(&object->transferComplete, 0);

            /* Store internal callback function */
            object->params.transferCallBckFunc = &GPMC_transferCallback;
        }

        if(object->operMode == GPMC_OPERATING_MODE_CALLBACK)
        {
            /* Currently not supported*/
        }

    }

    if(status == SystemP_SUCCESS)
    {
        object->isOpen = 1;
        handle = (GPMC_Handle)config;
    }

    SemaphoreP_post(&gGpmcDrvObj.lockObj);

    /* Free up resources in case of error */
    if(SystemP_SUCCESS != status)
    {
        if(NULL != config)
        {
            GPMC_close((GPMC_Handle) config);
        }
    }

    return(handle);
}


static void GPMC_transferCallback(GPMC_Handle handle, GPMC_Transaction *msg)
{
    GPMC_Object   *object; /* GPMC object */

    /* Input parameter validation */
    if (handle != NULL)
    {
        /* Get the pointer to the object */
        object = ((GPMC_Config*)handle)->object;

        /* Indicate transfer complete */
        SemaphoreP_post(&object->transferComplete);
    }
}

void GPMC_close(GPMC_Handle handle)
{
    /* Input parameter validation */

    if (handle != NULL)
    {
        GPMC_Object        *object = NULL;
        const GPMC_HwAttrs *hwAttrs = NULL;
        /* Get the pointer to the object and hwAttrs */
        object = ((GPMC_Config*)handle)->object;
        hwAttrs = ((GPMC_Config*)handle)->attrs;

        /* Mask I2C interrupts */
        GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_FIFOEVENT_INT);
        GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_TERMINALCOUNT_INT);
        GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_WAIT0EDGEDETECTION_INT);
        GPMC_disableInterupt(hwAttrs->gpmcBaseAddr,GPMC_WAIT1EDGEDETECTION_INT);

        /* Destruct the Hwi */
        if(object->operMode != GPMC_OPERATING_MODE_POLLING)
        {
            HwiP_destruct(&object->hwi);
        }

        /* Destruct the instance lock */
        SemaphoreP_destruct(&object->mutex);

        /* Destruct the transfer completion lock */
        if(object->operMode == GPMC_OPERATING_MODE_BLOCKING)
        {
            SemaphoreP_destruct(&object->transferComplete);
        }


        if (object->params.dmaEnable == TRUE)
        {
            /* dma not supported*/
        }

        /* Open flag is set false */
        object->isOpen = 0;
    }

    return;
}

// static void GPMC_ctrlNandWriteData(GPMC_HwAttrs const *hwAttrs,
//                                    uint8_t *pTxData,
//                                    uint32_t size)
// {
//     uint16_t *pData16 = (uint16_t *)pTxData;
//     uint8_t  *pData8 = pTxData;

//     while(size > 0U)
//     {
//         /* Check if writer buffer is empty */
//         while(!GPMCEmptyWriteBuffStatusGet(hwAttrs->gpmcBaseAddr));

//         if(hwAttrs->devSize == GPMC_DEVICESIZE_16BITS)
//         {
// 			HW_WR_REG16(hwAttrs->gpmcBaseAddr + GPMC_NAND_DATA_N(hwAttrs->chipSel), *pData16);
// 			pData16++;
// 			if (size == 1U)
//             {
//                 size = 0U;
//             }
// 			else
//             {
//                 size -= 2U;
//             }
//         }
//         else
//         {
//             HW_WR_REG8(hwAttrs->gpmcBaseAddr + GPMC_NAND_DATA_N(hwAttrs->chipSel), *pData8);
//             pData8++;
//             size--;
//         }
//     }
// }

// static int32_t GPMC_nand_write_v1(GPMC_Handle handle,
//                                   const GPMC_Transaction *transaction)
// {
//     GPMC_Object *object = NULL;
//     GPMC_HwAttrs const *hwAttrs = NULL;
//     int32_t         retVal = GPMC_STATUS_ERROR;

//     /* Input parameter validation */
//     if ((handle != NULL) && (transaction != NULL))
//     {
//         object = (GPMC_Object *)handle->object;
//         hwAttrs = (GPMC_HwAttrs const *)handle->hwAttrs;

//         if(GPMC_OPER_MODE_POLLING == object->intrPollMode)
//         {
//             GPMC_ctrlNandWriteData(hwAttrs, object->writeBufIdx,
//                                    object->writeCountIdx);
//         }
//         else
//         {
//         }
//         retVal = GPMC_STATUS_SUCCESS;
//     }
//     return(retVal);
// }

void GPMC_transactionInit(GPMC_Transaction *trans)
{
    trans->Buf = NULL;
    trans->count = 0;
    trans->status = GPMC_TRANSFER_STARTED;
    trans->transType = GPMC_TRANSACTION_TYPE_READ;
    trans->arg = NULL;
    trans->transferTimeout = SystemP_WAIT_FOREVER;
}


int32_t GPMC_nandReadData(GPMC_Handle handle, GPMC_Transaction *trans)
{
    int32_t status = SystemP_SUCCESS;


    if(handle != NULL && trans != NULL)
    {
        GPMC_Object *object = ((GPMC_Config*)handle)->object;
        const GPMC_HwAttrs *attrs = ((GPMC_Config*)handle)->attrs;
        volatile uint8_t nandData;
        uint8_t *bufPtr = (uint8_t*)trans->Buf;
        uint32_t byteCount = trans->count;

        if(trans->transType == GPMC_TRANSACTION_TYPE_READ)
        {
            if(object->operMode == GPMC_OPERATING_MODE_POLLING)
            {
                while((byteCount--) > 0)
                {
                    nandData = CSL_REG8_RD(attrs->gpmcBaseAddr + CSL_GPMC_NAND_DATA(object->params.chipSel));
                    *bufPtr = nandData;
                    bufPtr++;
                }
            }
            else
            {
                //todo : DMA mode not supported
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static void GPMC_nandCMDwrite(GPMC_Handle handle, uint32_t cmd)
{
    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object = ((GPMC_Config*)handle)->object;

        CSL_REG8_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_NAND_COMMAND(object->params.chipSel),
                    cmd);
    }
}

static void GPMC_nandADDRwrite(GPMC_Handle handle, uint32_t address)
{
    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object = ((GPMC_Config*)handle)->object;

        CSL_REG8_WR(hwAttrs->gpmcBaseAddr + CSL_GPMC_NAND_ADDRESS(object->params.chipSel),
                    address);
    }
}

void GPMC_writeNandCommandParamsInit(GPMC_nandCmdParams *cmdParams)
{
    cmdParams->cmdCycle1 = GPMC_CMD_INVALID;
    cmdParams->cmdCycle2 = GPMC_CMD_INVALID;
    cmdParams->colAddress = GPMC_CMD_INVALID;
    cmdParams->rowAddress = GPMC_CMD_INVALID;
    cmdParams->numColAddrCycles = GPMC_CMD_INVALID;
    cmdParams->numRowAddrCycles = GPMC_CMD_INVALID;
    cmdParams->waitTimeout = 0;
    cmdParams->checkReadypin = TRUE;
}

int32_t GPMC_writeNandCommand(GPMC_Handle handle, GPMC_nandCmdParams *cmdParams)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL &&  cmdParams != NULL)
    {
        uint32_t waitPinInterupt = 0;
        uint32_t colAddress = 0;
        uint32_t rowAddress = 0;

        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        if(hwAttrs->waitPinNum == CSL_GPMC_CONFIG1_WAITPINSELECT_W0)
        {
            waitPinInterupt = GPMC_WAIT0EDGEDETECTION_STATUS;
        }
        else if(hwAttrs->waitPinNum == CSL_GPMC_CONFIG1_WAITPINSELECT_W1)
        {
            waitPinInterupt = GPMC_WAIT1EDGEDETECTION_STATUS;
        }

        GPMC_interuptStatusClear(hwAttrs->gpmcBaseAddr, waitPinInterupt);

        if(cmdParams->cmdCycle1 != GPMC_CMD_INVALID)
        {
            GPMC_nandCMDwrite(handle,cmdParams->cmdCycle1);
        }

        if(cmdParams->colAddress != GPMC_CMD_INVALID)
        {
            colAddress = cmdParams->colAddress;
            for (uint8_t count = 0; count < cmdParams->numColAddrCycles; count++)//todo: get the address cycles from page params read command
            {
                GPMC_nandADDRwrite(handle, (colAddress & 0xFF));
                colAddress = colAddress >> 0x8;
            }
        }

        if(cmdParams->rowAddress != GPMC_CMD_INVALID)
        {
            rowAddress = cmdParams->rowAddress;
            for (uint8_t count = 0; count < cmdParams->numRowAddrCycles; count++)//todo: get the address cycles from page params read command
            {
                GPMC_nandADDRwrite(handle, (rowAddress & 0xFF));
                rowAddress = rowAddress >> 0x8;
            }
        }

        if(cmdParams->cmdCycle2 != GPMC_CMD_INVALID)
        {
            GPMC_nandCMDwrite(handle,cmdParams->cmdCycle2);
        }

        if(!cmdParams->checkReadypin)
        {
            status += GPMC_waitpinStatusReadywaitTimeout(handle, cmdParams->waitTimeout);
        }
        else
        {
            status += GPMC_waitpinInteruptStatusReadywaitTimeout(handle,cmdParams->waitTimeout);
            status += GPMC_waitpinStatusReadywaitTimeout(handle, GPMC_WAIT_PIN_STATUS_WAIT_TIME_MIN);
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;

}



int32_t GPMC_ECCSizeValSet(GPMC_Handle handle, uint32_t eccSize,
                       uint32_t eccSizeVal)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        if (eccSize == GPMC_ECC_SIZE_0)
        {
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECCSIZE0,
                          eccSizeVal);
        }
        else if (eccSize == GPMC_ECC_SIZE_1)
        {
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECCSIZE1,
                          eccSizeVal);
        }
        else
        {
            /*
            * Do nothing. Error will be generated by the hardware
            */
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;

}

static void GPMC_ECCResultSizeSelect(GPMC_Handle handle, uint32_t eccResReg,
                             uint32_t eccSize)
{
    const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

    switch (eccResReg)
    {
        case GPMC_ECC_RESULT_1:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_2:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_3:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_4:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_5:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_6:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_7:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_8:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_9:
            CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE,
                          eccSize);
            break;

        default:
            break;
    }
}

int32_t GPMC_BCHECCconfigureELM(GPMC_Handle handle)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        elmModuleReset(hwAttrs->elmBaseAddr);
        elmECCSizeSet(hwAttrs->elmBaseAddr, CSL_ELM_LOCATION_CONFIG_ECC_SIZE_MAX);
        elmErrCorrectionLevelSet(hwAttrs->elmBaseAddr, ELM_ECC_BCH_LEVEL_8BITS);
        elmIntConfig(hwAttrs->elmBaseAddr, ELM_LOC_VALID_0_STATUS, ELM_INT_ENALBLE);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}


int32_t GPMC_nandBCHEccConfig (GPMC_Handle handle)
{
    int32_t status = SystemP_SUCCESS;


    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object = ((GPMC_Config*)handle)->object;

       // GPMCECCResultRegSelect(hwAttrs->gpmcBaseAddr, GPMC_ECC_RESULT_1);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONTROL, GPMC_ECC_CONTROL_ECCPOINTER, GPMC_ECCPOINTER_RESULT_1);

        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCCS, object->params.chipSel);
        //GPMCECCCSSelect(hwAttrs->gpmcBaseAddr,hwAttrs->chipSel);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCTOPSECTOR, GPMC_ECC_BCH_NUMOFSECTS_1);
        //GPMCECCBCHNumOfSectorsSelect(hwAttrs->gpmcBaseAddr, GPMC_ECC_BCH_NUMOFSECTS_1);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECC16B, CSL_GPMC_ECC_CONFIG_ECC16B_EIGHTCOL);

        //GPMCECCColumnSelect(hwAttrs->gpmcBaseAddr, CSL_GPMC_ECC_CONFIG_ECC16B_EIGHTCOL);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCWRAPMODE, GPMC_ECC_WRAP_MODE1);
        //GPMCECCBCHWrapModeValSet(hwAttrs->gpmcBaseAddr, 1);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCBCHTSEL, GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS);

        //GPMCECCBCHErrCorrectionCapSelect(hwAttrs->gpmcBaseAddr, GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS);
        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCALGORITHM, GPMC_ECC_ALGORITHM_BCH);
        //GPMCECCAlgoSelect(hwAttrs->gpmcBaseAddr, GPMC_ECC_ALGORITHM_BCH);

        GPMC_ECCResultSizeSelect(handle, GPMC_ECC_RESULT_1, CSL_GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_SIZE0SEL);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t GPMC_ECCengineEnable(GPMC_Handle handle)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *hwAttrs = ((GPMC_Config*)handle)->attrs;

        CSL_REG32_FINS(hwAttrs->gpmcBaseAddr + CSL_GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCENABLE,
                  CSL_GPMC_ECC_CONFIG_ECCENABLE_ECCENABLED);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

void GPMC_ECCResultRegisterClear(GPMC_Handle handle)
{
    if(handle != NULL)
    {
        const GPMC_HwAttrs *attrs = ((GPMC_Config*)handle)->attrs;

        CSL_REG32_FINS(attrs->gpmcBaseAddr + CSL_GPMC_ECC_CONTROL, GPMC_ECC_CONTROL_ECCCLEAR,
                    CSL_GPMC_ECC_CONTROL_ECCCLEAR_MAX);
    }
}




GPMC_Handle GPMC_getHandle(uint32_t driverInstanceIndex)
{
    GPMC_Handle         handle = NULL;
    /* Check index */
    if(driverInstanceIndex < gGpmcConfigNum)
    {
        GPMC_Object *obj;
        obj = gGpmcConfig[driverInstanceIndex].object;

        if(obj && (TRUE == obj->isOpen))
        {
            /* valid handle */
            handle = obj->handle;
        }
    }
    return handle;
}

static uint32_t GPMC_ECCBCHResultGet(GPMC_Handle handle, uint32_t resIndex)
{
    uint32_t result = 0;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *attrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object = ((GPMC_Config*)handle)->object;

        switch (resIndex)
        {
            case GPMC_BCH_RESULT0:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_0(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT1:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_1(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT2:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_2(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT3:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_3(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT4:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_4(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT5:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_5(object->params.chipSel));
                break;
            case GPMC_BCH_RESULT6:
                result = CSL_REG32_RD(attrs->gpmcBaseAddr + CSL_GPMC_BCH_RESULT_6(object->params.chipSel));
                break;

            default:
                break;
        }
    }

    return (result);
}

int32_t GPMC_BCHECCcheckError(GPMC_Handle handle, uint32_t *bchData, uint32_t *errCount, uint32_t *errLoc)
{
    int32_t status = SystemP_SUCCESS;
    uint64_t curTime;

    if(handle != NULL)
    {
        const GPMC_HwAttrs *attrs = ((GPMC_Config*)handle)->attrs;
        GPMC_Object *object = ((GPMC_Config*)handle)->object;

        bchData[0] = GPMC_ECCBCHResultGet(handle, GPMC_BCH_RESULT0);
        bchData[1] = GPMC_ECCBCHResultGet(handle, GPMC_BCH_RESULT1);
        bchData[2] = GPMC_ECCBCHResultGet(handle, GPMC_BCH_RESULT2);
        bchData[3] = GPMC_ECCBCHResultGet(handle, GPMC_BCH_RESULT3);

        elmSyndromeFrgmtSet(attrs->elmBaseAddr, ELM_SYNDROME_FRGMT_0, bchData[0], object->params.chipSel);
        elmSyndromeFrgmtSet(attrs->elmBaseAddr, ELM_SYNDROME_FRGMT_1, bchData[1], object->params.chipSel);
        elmSyndromeFrgmtSet(attrs->elmBaseAddr, ELM_SYNDROME_FRGMT_2, bchData[2], object->params.chipSel);
        elmSyndromeFrgmtSet(attrs->elmBaseAddr, ELM_SYNDROME_FRGMT_3, bchData[3], object->params.chipSel);


        elmErrLocProcessingStart(attrs->elmBaseAddr, object->params.chipSel);

        curTime = ClockP_getTimeUsec();

        while((elmIntStatusGet(attrs->elmBaseAddr, ELM_LOC_VALID_0_STATUS) == ELM_BIT_SET_LOW) &&
        ((ClockP_getTimeUsec() - curTime) < GPMC_ELM_ERR_STATUS_TIMEOUT_MAX))
        {
            uint32_t delay = 100;
            while(delay--);
        }

        if(elmIntStatusGet(attrs->elmBaseAddr, ELM_LOC_VALID_0_STATUS) == ELM_BIT_SET_LOW)
        {
            status = SystemP_FAILURE;
        }
        else
        {
            elmIntStatusClear(attrs->elmBaseAddr, ELM_LOC_VALID_0_STATUS);
        }

        if(status == SystemP_SUCCESS)
        {
            if (elmErrLocProcessingStatusGet(attrs->elmBaseAddr, object->params.chipSel) > 0U)
            {
                uint32_t count;

                *errCount = elmNumOfErrsGet(attrs->elmBaseAddr, object->params.chipSel);
                for (count = 0; count < *errCount; count++)
                {
                    errLoc[count] = elmErrLocBitAddrGet(attrs->elmBaseAddr, count, object->params.chipSel);
                }
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

uint32_t GPMC_getInputClk(GPMC_Handle handle)
{
    uint32_t retVal = 0U;
    if(handle != NULL)
    {
        const GPMC_HwAttrs* attrs = ((GPMC_Config *)handle)->attrs;
        retVal = attrs->inputClkFreq;
    }
    return retVal;
}