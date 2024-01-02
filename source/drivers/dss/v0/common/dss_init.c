/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file dss_init.c
 *
 *  \brief File containing the DSS initialization APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <drivers/fvid2.h>
#include <drivers/dss.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>
#include <drivers/dss/v0/dctrl/dss_dctrlDrv.h>
#include <drivers/dss/v0/disp/dss_dispDrv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Dss_initParamsInit(Dss_InitParams *dssParams)
{
    if(NULL != dssParams)
    {
        Dss_socParamsInit(&(dssParams->socParams));
    }
}

int32_t Dss_init(const Dss_InitParams *initParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, numInst = 0U;
    uint32_t isPipeAvailable[CSL_DSS_VID_PIPE_ID_MAX];
    uint32_t isPortAvailable[CSL_DSS_VP_ID_MAX];
    Dss_DctrlDrvInitParams dctrlInitParams;
    Dss_EvtMgrInitParams evtMgrInitParams;
    Dss_DispDrvInitParams dispInitParams[CSL_DSS_VID_PIPE_ID_MAX];
    Dss_RmInfo *rmInfo;
    Dss_IrqParams *irqParams;

    /* Check for NULL pointers and invalid arguments */
    if(NULL == initParams)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        rmInfo = (Dss_RmInfo *)(&(initParams->socParams.rmInfo));
        Dss_fillSocInfo(rmInfo);

        /* Perform DSS soft reset */
        Dss_setDssSoftReset();

        /* Initialize event manager */
        irqParams = (Dss_IrqParams *)(&(initParams->socParams.irqParams));
        Dss_evtMgrInitParamsInit(&evtMgrInitParams);
        retVal = Dss_fillEvtMgrInitInfo(&evtMgrInitParams, irqParams);
        retVal += Dss_evtMgrInit(
                            (const Dss_EvtMgrInitParams *) &evtMgrInitParams);
    }

    if(FVID2_SOK == retVal)
    {
        /* Initialize display controller driver */
        dctrlInitParams.drvInstId = DSS_DCTRL_INST_0;
        dctrlInitParams.numAvailablePorts = 0U;
        for(i=CSL_DSS_VP_ID_1; i<CSL_DSS_VP_ID_MAX; i++)
        {
            isPortAvailable[i] =
                            initParams->socParams.rmInfo.isPortAvailable[i];

            if(TRUE == isPortAvailable[i])
            {
                dctrlInitParams.availablePortId[
                                        dctrlInitParams.numAvailablePorts] = i;
                dctrlInitParams.numAvailablePorts++;
            }
        }

        dctrlInitParams.dsiInitParams.isAvailable = FALSE;

        retVal = Dss_dctrlDrvInit(&dctrlInitParams);
    }

    if(FVID2_SOK == retVal)
    {
        /* Initialize display driver */
        for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
            isPipeAvailable[i] =
                                initParams->socParams.rmInfo.isPipeAvailable[i];

            if(TRUE == isPipeAvailable[i])
            {
                dispInitParams[numInst].drvInstId = i;
                numInst++;
            }
        }
        retVal += Dss_dispDrvInit(numInst, dispInitParams);
    }

    return retVal;
}

int32_t Dss_deInit(void)
{
    int32_t retVal = FVID2_SOK;

    retVal += Dss_dispDrvDeInit();
    retVal += Dss_dctrlDrvDeInit();
    retVal += Dss_evtMgrDeInit();

    return retVal;
}
