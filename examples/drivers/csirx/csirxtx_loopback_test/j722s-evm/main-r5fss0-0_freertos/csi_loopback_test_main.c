/*
 *  Copyright (c) Texas Instruments Incorporated 2022-25
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
 *  \file csi_loopback_test_main.c
 *
 *  \brief CSI loopback Example.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include "csi_loopback_test_main.h"
#include "serdes_sensor_config.h"
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   App function to create CSITX Driver Instance with the supplied
 *          parameters
 *
 * \param   appInstObj      CSI TX Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_txCreate(CsiLoopback_TxInstObj* appInstObj);

/**
 * \brief   App function to create CSIRX Driver Instance with supplied
 *          parameters, configures DPHY-RX and sensors.
 *
 * \param   appInstObj      CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_rxCreate(CsiLoopback_RxInstObj *appInstObj);

/**
 * \brief   App function to delete the CSITX driver Instance.
 *
 * \param   appInstObj      CSI TX Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_txDelete(CsiLoopback_TxInstObj* appInstObj);

/**
 * \brief   App function to delete the CSIRX driver Instance and
 *          disable the error events
 *
 * \param   appInstObj      CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_rxDelete(CsiLoopback_RxInstObj *appInstObj);

/**
 * \brief   Main App function to test Initialize an application timer,
 *          and CSIRX& CSITX drivers, and perform the loopback test.
 *
 * \param   none.
 *
 * \retval  status.        FVID2_SOK on success.
 *                         else otherwise
 */
int32_t CsiLoopback_testMain(void);

/**
 * \brief   App function to initialize channel,instance and module configuration
 *          parameters for CSITX
 *
 * \param   appInstObj     CSI TX Test Object
 *
 * \retval  none.
 */
static void CsiLoopback_initTxParams(CsiLoopback_TxInstObj* appInstObj);

/**
 * \brief   App function to initialize channel,instance and module configuration
 *          parameters for CSIRX
 *
 * \param   appInstObj    CSI RX Capture Test Object      .
 *
 * \retval  none.
 */
static void CsiLoopback_initCaptParams(CsiLoopback_RxInstObj *appInstObj);

/**
 * \brief   App event callback function for CSITX events
 *
 * \param   status             status of the event
 *
 *          appData            pointer to the CSITX test Object
 * \retval  none.
 */
void CsiLoopback_eventCallback(Csitx_EventStatus status,void *appData);

/**
 * \brief   App callback function for timer interrupt. stops the CSIRX and
 *          CSITX streams
 *
 * \param   arg             CSI RX Capture Test Object
 *
 *
 * \retval  none.
 */
void CsirxApp_timerIsr(void *arg);

/**
 * \brief   App function to Initialize CSITX & CSIRX drivers.
 *          and Initializes I2C instance to communicate with SERDES.
 *
 * \param   appCommonObj    CSI Common Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_init(CsiLoopback_CommonObj *appCommonObj);

/**
 * \brief   App function to start the CSIRX & CSITX streams, and a
 *          timer to count how much time the application has to run.
 *
 * \param   appCommonObj    CSI Common Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_csiTest(CsiLoopback_CommonObj *appCommonObj);

/**
 * \brief   App function to deinitialize the CSIRX & CSITX drivers and to clean
 *          the used resources.
 *
 * \param   appCommonObj    CSI Common Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsiLoopback_deinit(CsiLoopback_CommonObj *appCommonObj);
void App_wait(uint32_t wait_in_ms);
void App_fvidPrint(const char *str, ...);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* App common object */
CsiLoopback_CommonObj gAppCommonObj;

/* CSIRX instances to use in application */
uint32_t  gAppCapInst[APP_TEST_INST_NUM] = {CSIRX_INSTANCE_ID_0};
/* CSITX instances to use in application */
uint32_t  gAppTxInst[APP_TEST_INST_NUM] = {CSITX_INSTANCE_ID_0};
/* Source selection for loopback stream  */
uint32_t  gLpbksrc[APP_TOTAL_INST] = {CSIRX_INSTANCE_ID_0};
/* Timer Baseaddresses */
extern uint32_t gTimerBaseAddr[TIMER_NUM_INSTANCES];

extern void Drivers_open();

/* Semaphore to indicate app completion */
SemaphoreP_Object gAppCompletionSem;

/* I2c Handle to access deserializer */
extern I2C_Handle gI2cHandle;
volatile uint32_t gNumFrameStartIntrs[APP_TOTAL_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/*
 * Application main
 */
int32_t CsiLoopback_testMain(void)
{
    int32_t retVal = FVID2_SOK;
    CsiLoopback_RxInstObj *appInstObjRx[APP_TEST_INST_NUM];
    CsiLoopback_CommonObj *appCommonObj;
    appCommonObj = &gAppCommonObj;
    CsiLoopback_TxInstObj *appInstObjTx[APP_TEST_INST_NUM];


    Drivers_open();
    for(uint32_t i = 0U; i < APP_TEST_INST_NUM; i++)
    {
        appInstObjTx[i] = &appCommonObj->appInstObjTx[i];;
        memset(appInstObjTx[i], 0x0, sizeof (CsiLoopback_TxInstObj));
        appInstObjTx[i]->instId = gAppTxInst[i];
        /* Initialize application object for current transmit context */
        CsiLoopback_initTxParams(appInstObjTx[i]);
        appInstObjRx[i] = &appCommonObj->appInstObjRx[i];
        memset(appInstObjRx[i], 0x0, sizeof (CsiLoopback_RxInstObj));
        appInstObjRx[i]->instId = gAppCapInst[i];
        CsiLoopback_initCaptParams(appInstObjRx[i]);
    }

    /* Creating semaphore to indicate application completion of each Instance */
    SemaphoreP_constructBinary(&gAppCompletionSem,0U);

    /* App Init */
    retVal += CsiLoopback_init(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsiLoopback_init() FAILED!!!\r\n");
    }

    GT_0trace(AppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_0trace(AppTrace, GT_INFO,
              APP_NAME ":===================Setup Details===================\r\n");

    GT_1trace(AppTrace, GT_INFO,
              APP_NAME ": Capture DF:0x%x\r\n", APP_IMAGE_DT);
    GT_2trace(AppTrace, GT_INFO,
              APP_NAME ": Capture Resolution:%d x %d\r\n",
              APP_FRAME_WIDTH,
              APP_FRAME_HEIGHT);
    GT_0trace(AppTrace, GT_INFO,
              APP_NAME ":===================================================\r\n");

    /* App Create */
    if (FVID2_SOK == retVal)
    {
        for(uint32_t i = 0U; i< APP_TEST_INST_NUM; i++)
        {
            retVal += CsiLoopback_rxCreate(appInstObjRx[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": [ERROR]CsiLoopback_rxCreate() FAILED!!!\r\n");
            }
            retVal += CsiLoopback_txCreate(appInstObjTx[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": [ERROR]CsiLoopback_txCreate() FAILED!!!\r\n");
            }
        }
    }

    /*  APP start */
    retVal = CsiLoopback_csiTest(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsirxCsiLoopback_csiTest() FAILED!!!\r\n");
    }

    /* App CSI delete function */
    if (FVID2_SOK == retVal)
    {
        for(uint32_t i = 0U; i< APP_TEST_INST_NUM; i++)
        {
            retVal += CsiLoopback_rxDelete(appInstObjRx[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(AppTrace, GT_ERR,
                          APP_NAME ": [ERROR]CsiLoopback_rxDelete() FAILED!!!\r\n");
            }
            retVal += CsiLoopback_txDelete(appInstObjTx[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(AppTrace, GT_ERR,
                          APP_NAME ": [ERROR]CsiLoopback_txDelete() FAILED!!!\r\n");
            }
        }
    }
    /* App CSI De-initialization function */
    if (FVID2_SOK == retVal)
    {
        retVal += CsiLoopback_deinit(appCommonObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(AppTrace, GT_ERR,
                      APP_NAME ": [ERROR]CsirxCsiLoopback_deinit() FAILED!!!\r\n");
        }
    }

    /* using 'App_consolePrintf' instead of GT trace as Fvid2_deInit has happend */

    return (retVal);
}

static int32_t CsiLoopback_txCreate(CsiLoopback_TxInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;

    if (FVID2_SOK == retVal)
    {
        /* Fvid2_create() */
        appInstObj->drvHandle = Fvid2_create(
            CSITX_TX_DRV_ID,
            appInstObj->instId,
            &appInstObj->createPrms,
            &appInstObj->createStatus,
            &appInstObj->cbPrms);

        if ((NULL == appInstObj->drvHandle) ||
            (FVID2_SOK != appInstObj->createStatus.retVal))
        {
            GT_0trace(AppTrace, GT_ERR,
                      APP_NAME ": Tx Create Failed!!!\r\n");
            retVal = appInstObj->createStatus.retVal;
        }
    }
    return retVal;
}

static int32_t CsiLoopback_rxCreate(CsiLoopback_RxInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    Csirx_DPhyCfg dphyCfg;
    Csirx_EventPrms eventPrms;

    /* Fvid2_create() */
    appInstObj->drvHandle = Fvid2_create(
        CSIRX_CAPT_DRV_ID,
        appInstObj->instId,
        &appInstObj->createPrms,
        &appInstObj->createStatus,
        &appInstObj->cbPrms);

    if ((NULL == appInstObj->drvHandle) ||
        (FVID2_SOK != appInstObj->createStatus.retVal))
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": Capture Create Failed!!!\r\n");
        retVal = appInstObj->createStatus.retVal;
    }
    if (FVID2_SOK == retVal)
    {
        /* Set CSIRX D-PHY configuration parameters */
        Csirx_initDPhyCfg(&dphyCfg);
        dphyCfg.inst = appInstObj->instId;
        dphyCfg.leftLaneBandSpeed  = CSIRX_LANE_BAND_SPEED_1350_TO_1500_MBPS;
        dphyCfg.rightLaneBandSpeed = CSIRX_LANE_BAND_SPEED_1350_TO_1500_MBPS;
        retVal = Fvid2_control(appInstObj->drvHandle,
                                IOCTL_CSIRX_SET_DPHY_CONFIG,
                                &dphyCfg,
                                NULL);
        if(FVID2_SOK != retVal)
        {
            GT_1trace(AppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Set D-PHY Configuration FAILED for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
        else
        {
            GT_1trace(AppTrace,
                      GT_INFO,
                      APP_NAME
                      ":Set D-PHY Configuration Successful for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Register Error Events */
        Csirx_eventPrmsInit(&eventPrms);
        retVal = Fvid2_control(appInstObj->drvHandle,
                               IOCTL_CSIRX_REGISTER_EVENT,
                               &eventPrms,
                               NULL);
        if(FVID2_SOK != retVal)
        {
            GT_1trace(AppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Error Events Registration FAILED for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
        else
        {
            GT_1trace(AppTrace,
                      GT_INFO,
                      APP_NAME
                      ":Error Events Registration Successful for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_1trace(AppTrace,
                  GT_INFO,
                  APP_NAME ": CSIRX Capture created for CSIRX instance %d\r\n",appInstObj->instId);
    }

    /* Configure sensor here */
    retVal += CsirxApp_sensorConfig(appInstObj);
    return (retVal);
}

static int32_t CsiLoopback_txDelete(CsiLoopback_TxInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_delete(appInstObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": FVID2 Delete Failed!!!\r\n");
    }
    else
    {
        appInstObj->drvHandle = NULL;
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(AppTrace, GT_INFO, APP_NAME ": Tx Driver deleted\r\n");
    }
    return (retVal);
}

static int32_t CsiLoopback_rxDelete(CsiLoopback_RxInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    if ((FVID2_SOK == retVal) || (FVID2_ENO_MORE_BUFFERS == retVal))
    {
        retVal = FVID2_SOK;
        /* Disable Error Events */
        retVal = Fvid2_control(appInstObj->drvHandle,
                               IOCTL_CSIRX_UNREGISTER_EVENT,
                               (void *)CSIRX_EVENT_GROUP_ERROR,
                               NULL);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(AppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Error Events un-registration FAILED!!!\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_delete(appInstObj->drvHandle, NULL);
    }
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": FVID2 Delete Failed!!!\r\n");
    }
    else
    {
        appInstObj->drvHandle = NULL;
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(AppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\r\n");
    }

    return (retVal);
}

static void CsiLoopback_initTxParams(CsiLoopback_TxInstObj* appInstObj)
{
    uint32_t loopCnt = 0U;

    /* set instance configuration parameters */
    Csitx_createParamsInit(&appInstObj->createPrms);
    appInstObj->createPrms.instCfg.dphyCfg.inst = appInstObj->instId;
    appInstObj->createPrms.instCfg.dphyCfg.laneBandSpeed = CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS;
    appInstObj->createPrms.numCh = APP_CH_NUM;
    /* set channel configuration parameters */
    for (loopCnt = 0U ; loopCnt < appInstObj->createPrms.numCh ; loopCnt++)
    {
        appInstObj->chFrmCnt[loopCnt]                          = 0U;
        appInstObj->createPrms.chCfg[loopCnt].chId             = loopCnt;
        appInstObj->createPrms.chCfg[loopCnt].chType           = CSITX_CH_TYPE_LPBK;
        appInstObj->createPrms.chCfg[loopCnt].vcNum            = loopCnt;
        appInstObj->createPrms.chCfg[loopCnt].outCsiDataType   = APP_IMAGE_DT;
        appInstObj->createPrms.chCfg[loopCnt].inFmt.width      = APP_FRAME_WIDTH;
        appInstObj->createPrms.chCfg[loopCnt].inFmt.height     = APP_FRAME_HEIGHT;
        appInstObj->createPrms.chCfg[loopCnt].inFmt.pitch[0U]  =
                                                APP_FRAME_PITCH;
        appInstObj->createPrms.chCfg[loopCnt].inFmt.dataFormat =
                                                FVID2_DF_BGRX32_8888;
        appInstObj->createPrms.chCfg[loopCnt].inFmt.ccsFormat  =
                                                APP_IMAGE_STORAGE_FORMAT;
        appInstObj->createPrms.chCfg[loopCnt].vBlank           =
                                            22U;
        appInstObj->createPrms.chCfg[loopCnt].hBlank           =
                                            40U;
        appInstObj->createPrms.chCfg[loopCnt].startDelayPeriod =
                                            40U;
    }
    /* set module configuration parameters */
    appInstObj->createPrms.instCfg.rxCompEnable    = (uint32_t)1U;
    appInstObj->createPrms.instCfg.rxv1p3MapEnable = (uint32_t)1U;
    appInstObj->createPrms.instCfg.numDataLanes    = 4U;
    appInstObj->createPrms.instCfg.eventParams[CSITX_EVENT_GROUP_TX_IRQ].eventCb    = CsiLoopback_eventCallback ;
    appInstObj->createPrms.instCfg.eventParams[CSITX_EVENT_GROUP_TX_IRQ].appData    = appInstObj ;
    appInstObj->createPrms.instCfg.lpbkCsiRxInst    = gLpbksrc[appInstObj->instId] ;
    for (loopCnt = 0U ;
         loopCnt < appInstObj->createPrms.instCfg.numDataLanes ;
         loopCnt++)
    {
        appInstObj->createPrms.instCfg.lanePolarityCtrl[loopCnt] = 0U;
    }
    /* This will be updated once Fvid2_create() is done */
    appInstObj->createStatus.retVal = FVID2_SOK;
    appInstObj->drvHandle           = NULL;
    Fvid2CbParams_init(&appInstObj->cbPrms);
    appInstObj->cbPrms.appData      = appInstObj;

    appInstObj->frameErrorCnt = 0U;
    appInstObj->maxWidth      = APP_FRAME_WIDTH;
    appInstObj->maxHeight     = APP_FRAME_HEIGHT;

    /* Initialize transmit instance status */
    Csitx_instStatusInit(&appInstObj->txStatus);
}

static void CsiLoopback_initCaptParams(CsiLoopback_RxInstObj* appInstObj)
{
    uint32_t loopCnt = 0U;

    if (CSIRX_INSTANCE_ID_0 == appInstObj->instId)
    {
        appInstObj->boardCsiInstID = 0;
        appInstObj->cameraSensor = APP_CSIRX_INST0_CAMERA_SENSOR;
    }
    else if (CSIRX_INSTANCE_ID_1 == appInstObj->instId)
    {
        appInstObj->boardCsiInstID = 1;
        appInstObj->cameraSensor = APP_CSIRX_INST1_CAMERA_SENSOR;
    }
    else
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": Invalid Capture Instance\r\n");
    }

    /* set instance configuration parameters */
    Csirx_createParamsInit(&appInstObj->createPrms);
    appInstObj->createPrms.numCh = APP_CH_NUM;
    /* set channel configuration parameters */
    for (loopCnt = 0U ; loopCnt < appInstObj->createPrms.numCh ; loopCnt++)
    {
        appInstObj->chFrmCnt[loopCnt] = 0U;
        appInstObj->createPrms.chCfg[loopCnt].chId = loopCnt ;
        appInstObj->createPrms.chCfg[loopCnt].chType = CSIRX_CH_TYPE_LPBK;
        appInstObj->createPrms.chCfg[loopCnt].vcNum = loopCnt;
        appInstObj->createPrms.chCfg[loopCnt].inCsiDataType = APP_IMAGE_DT;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.width = APP_FRAME_WIDTH;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.height = APP_FRAME_HEIGHT;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.pitch[0U] =
                                                APP_FRAME_PITCH;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.dataFormat =
                                                FVID2_DF_BGRX32_8888;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.ccsFormat =
                                                APP_IMAGE_STORAGE_FORMAT;
    }
    /* set module configuration parameters */
    appInstObj->createPrms.instCfg.enableCsiv2p0Support = UTRUE;
    appInstObj->createPrms.instCfg.numDataLanes = 4U;
    appInstObj->createPrms.instCfg.enableErrbypass = UFALSE;
    appInstObj->createPrms.instCfg.enableStrm[CSIRX_LPBK_STREAM_ID] = 1U;
    for (loopCnt = 0U ;
         loopCnt < appInstObj->createPrms.instCfg.numDataLanes ;
         loopCnt++)
    {
        appInstObj->createPrms.instCfg.dataLanesMap[loopCnt] = (loopCnt + 1U);
    }
    /* This will be updated once Fvid2_create() is done */
    appInstObj->createStatus.retVal = FVID2_SOK;
    appInstObj->drvHandle = NULL;
    Fvid2CbParams_init(&appInstObj->cbPrms);

    appInstObj->frameErrorCnt = 0U;
    appInstObj->maxWidth = APP_FRAME_WIDTH;
    appInstObj->maxHeight = APP_FRAME_HEIGHT;

    /* Initialize capture instance status */
    Csirx_instStatusInit(&appInstObj->captStatus);
}

void CsiLoopback_eventCallback(Csitx_EventStatus status,void *appData)
{
	CsiLoopback_TxInstObj *appTxData = (CsiLoopback_TxInstObj*)appData;
	if((status.eventMasks & CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START) ==
                      CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START)
	{
                gNumFrameStartIntrs[appTxData->instId]++;
	}
}

void CsirxApp_timerIsr(void *arg)
{
    static volatile uint32_t timerIsrCount=0;
    timerIsrCount++;
    if (timerIsrCount == APP_TEST_PERIOD_IN_SEC)
    {
        TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);
        /* Post semaphore to print the results */
        SemaphoreP_post(&gAppCompletionSem);
    }
}

static int32_t CsiLoopback_init(CsiLoopback_CommonObj* appCommonObj)
{
    int32_t retVal = FVID2_SOK;
    Fvid2_InitPrms initPrms;

    /* set instance initialization parameters for CSIRX*/
    Csirx_initParamsInit(&appCommonObj->rxInitPrms);
    /* set instance initialization parameters for CSITX*/
    Csitx_initParamsInit(&appCommonObj->txInitPrms);
    /* Fvid2 init */
    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": Fvid2 Init Failed!!!\r\n");
    }
    /* System init */
    retVal = Csitx_init(&appCommonObj->txInitPrms);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }

    retVal = Csirx_init(&appCommonObj->rxInitPrms);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(AppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }

    return (retVal);
}

static int32_t CsiLoopback_csiTest(CsiLoopback_CommonObj* appCommonObj)
{
    int32_t retVal = FVID2_SOK;

    /* start CSITX First as it is consumer here */
    for(uint32_t i = 0U; i < APP_TEST_INST_NUM; i++)
    {
        if (FVID2_SOK == retVal)
        {
            retVal += Fvid2_start(appCommonObj->appInstObjTx[i].drvHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(AppTrace, GT_ERR,
                          APP_NAME ": Tx Start Failed!!!\r\n");
            }
        }
    }

    for(uint32_t i = 0U; i < APP_TEST_INST_NUM; i++)
    {
        if (FVID2_SOK == retVal)
        {
            retVal += Fvid2_start(appCommonObj->appInstObjRx[i].drvHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(AppTrace, GT_ERR,
                         APP_NAME ": Capture Start Failed for instance %d!!!\r\n",appCommonObj->appInstObjRx[i].instId);
            }
        }
    }
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
    SemaphoreP_pend(&gAppCompletionSem, SystemP_WAIT_FOREVER);
     /* Stop the streams immediately after the timeout is reached */
    for(uint32_t i = 0U; i < APP_TEST_INST_NUM; i++)
    {
        retVal += Fvid2_stop(appCommonObj->appInstObjRx[i].drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(AppTrace, GT_ERR,
                      APP_NAME ": Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObjRx[i].instId);
        }
        retVal += Fvid2_stop(appCommonObj->appInstObjTx[i].drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(AppTrace, GT_ERR,
                      APP_NAME ": Transmit stop Failed for instance %d!!!\r\n", appCommonObj->appInstObjTx[i].instId);
        }
    }
    for(uint32_t i = 0U; i < APP_TEST_INST_NUM; i++)
    {
      GT_3trace(AppTrace, GT_INFO,
                           APP_NAME ": CSITX start of frame interrupts for CSITX instance:%d in %d sec is %d!!!\r\n",appCommonObj->appInstObjTx[i].instId,APP_TEST_PERIOD_IN_SEC ,gNumFrameStartIntrs[appCommonObj->appInstObjTx[i].instId] );
    }
    return retVal;
}

static int32_t CsiLoopback_deinit(CsiLoopback_CommonObj *appCommonObj)
{
    int32_t retVal = FVID2_SOK;

    retVal = Csirx_deInit();
    /* System de-init */
    Fvid2_deInit(NULL);
    /* Close I2C channel */
    I2C_close(gI2cHandle);
    /* Delete semaphore */
    SemaphoreP_destruct(&gAppCompletionSem);
    /* Delete Timer */
    return (retVal);

}


