/*
 *  Copyright (C) 2024-25 Texas Instruments Incorporated
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
 *  \file csitx_transmit_test_main.c
 *
 *  \brief CSITx transmit example code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "csitx_transmit_test_cfg.h"

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

/**
 * \brief   This function is wrapper function used to print message on
 *          respective consoles
 *
 * \param   pcString        Print contents.
 *
 * \retval  none.
 */
void App_consolePrintf(const char *pcString, ...);

/**
 * \brief   This function is used to initialize test parameters
 *
 * \param   appObj          Type of print message.
 *                          Refer to struct #appTxObj
 *
 * \retval  none.
 */
static void App_initTxParams(appTxObj* appObj);

/**
 * \brief   App Init function.
 *
 * \param   appObj          CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_init(appTxObj* appObj);

/**
 * \brief   App create function.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_create(appTxObj* appObj);

/**
 * \brief   App CSI test function: transmits frames.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_csitxTest(appTxObj* appObj);

/**
 * \brief   App delete function.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_delete(appTxObj* appObj);

/**
 * \brief   App Init function.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_deinit(appTxObj* appObj);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   handle        Fvid2 DRV handle
 *
 * \param   appData       App based back by to CB function
 *
 * \param   reserved      reserved, not used
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_allocAndQFrames(appTxObj *appObj);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   appObj        CSI RX Tx Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t App_txFreeFrames(appTxObj *appObj);

/**
 * \brief   App print function for FVID2 driver.
 *
 * \param   str             Print string
 *
 * \retval  None.
 */
void App_fvidPrint(const char *str, ...);

/**
 * \brief   App print function for UDMA driver.
 *
 * \param   str             Print string
 *
 * \retval  None.
 */
void App_dmaPrint(const char *str);

/**
 * \brief   App function to get current time in msec.
 *
 * \param   None.
 *
 * \retval  Current time stamp in milliseconds.
 */
uint32_t App_getCurTimeInMsec(void);

/**
 * \brief   App function to calculate the elapsed time from 'startTime' in msec.
 *
 * \param   None.
 *
 * \retval  Elapsed time startTime in milliseconds.
 */
uint32_t App_getElapsedTimeInMsec(uint32_t startTime);

extern void App_wait(uint32_t wait_in_ms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

appTxObj gAppObj;
/* Memory buffer to hold data */
uint8_t gTxFrms[(APP_TX_FRAMES_PER_CH * APP_TX_CH_NUM)][APP_TX_FRAME_SIZE] __attribute__(( aligned(128), section(".data_buffer")));

/*
 * UDMA driver objects
 */
Udma_DrvObject gUdmaDrvObj;

static SemaphoreP_Object gLockSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int Csitx_transmitTest(void)
{
    int retVal = FVID2_SOK;
    appTxObj *appObj;

    appObj = &gAppObj;
    memset(appObj, 0x0, sizeof (appTxObj));

    /* Initialize application object for current transmit context */\
    App_initTxParams(appObj);
    /* App Init */
    retVal += App_init(appObj);

    GT_0trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_1trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Tx DF:0x%x\r\n", APP_TX_IMAGE_DT);
    GT_2trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Tx Resolution:%d x %d\r\n",
              APP_TX_FRAME_WIDTH,
              APP_TX_FRAME_HEIGHT);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]App_init() FAILED!!!\r\n");
    }

    /* App Init */
    if (FVID2_SOK == retVal)
    {
        retVal += App_create(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]App_create() FAILED!!!\r\n");
        }
    }

    /* App CSI test function */
    if (FVID2_SOK == retVal)
    {
        retVal += App_csitxTest(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]App_csitxTest() FAILED!!!\r\n");
        }
    }

    /* App CSI delete function */
    if (FVID2_SOK == retVal)
    {
        retVal += App_delete(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]App_delete() FAILED!!!\r\n");
        }
    }

    /* App CSI De-initialization function */
    if (FVID2_SOK == retVal)
    {
        retVal += App_deinit(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]App_deinit() FAILED!!!\r\n");
        }
    }

    /* using 'App_consolePrintf' instead of GT trace as Fvid2_deInit has happend */
    App_consolePrintf("Sample Application - DONE !!!\r\n");

    return (retVal);
}

static void App_initTxParams(appTxObj* appObj)
{
    uint32_t loopCnt = 0U;

    /* set instance to be used for transmit */
    if (0U == CSITX_INSTANCE)
    {
        appObj->instId = CSITX_INSTANCE_ID_0;
    }
    /* set instance initialization parameters */
    /* This will be updated once UDMA init is done */
    Csitx_initParamsInit(&appObj->initPrms);
    /* set instance configuration parameters */
    Csitx_createParamsInit(&appObj->createPrms);

    if (0U == CSITX_INSTANCE)
    {
        appObj->createPrms.instCfg.dphyCfg.inst = CSITX_INSTANCE_ID_0;
    }

    appObj->createPrms.numCh = APP_TX_CH_NUM;

    /* set channel configuration parameters */
    for (loopCnt = 0U ; loopCnt < appObj->createPrms.numCh ; loopCnt++)
    {
        appObj->chFrmCnt[loopCnt]                          = 0U;
        appObj->createPrms.chCfg[loopCnt].chId             = loopCnt;
        appObj->createPrms.chCfg[loopCnt].chType           = CSITX_CH_TYPE_TX;
        appObj->createPrms.chCfg[loopCnt].vcNum            = loopCnt;
        appObj->createPrms.chCfg[loopCnt].outCsiDataType   = APP_TX_IMAGE_DT;
        appObj->createPrms.chCfg[loopCnt].inFmt.width      = APP_TX_FRAME_WIDTH;
        appObj->createPrms.chCfg[loopCnt].inFmt.height     = APP_TX_FRAME_HEIGHT;
        appObj->createPrms.chCfg[loopCnt].inFmt.pitch[0U]  =
                                                APP_TX_FRAME_PITCH;
        appObj->createPrms.chCfg[loopCnt].inFmt.dataFormat =
                                                FVID2_DF_BGRX32_8888;
        appObj->createPrms.chCfg[loopCnt].inFmt.ccsFormat  =
                                                APP_TX_IMAGE_STORAGE_FORMAT;
        appObj->createPrms.chCfg[loopCnt].vBlank           =
                                            22U;
        appObj->createPrms.chCfg[loopCnt].hBlank           =
                                            40U;
        appObj->createPrms.chCfg[loopCnt].startDelayPeriod =
                                            40U;
    }

    /* set module configuration parameters */
    appObj->createPrms.instCfg.rxCompEnable    = (uint32_t)1U;
    appObj->createPrms.instCfg.rxv1p3MapEnable = (uint32_t)1U;
    appObj->createPrms.instCfg.numDataLanes    = 4U;

    for (loopCnt = 0U ;
         loopCnt < appObj->createPrms.instCfg.numDataLanes ;
         loopCnt++)
    {
        appObj->createPrms.instCfg.lanePolarityCtrl[loopCnt] = 0U;
    }

    /* This will be updated once Fvid2_create() is done */
    appObj->createStatus.retVal = FVID2_SOK;
    appObj->drvHandle           = NULL;
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn        = (Fvid2_CbFxn) &App_frameCompletionCb;
    appObj->cbPrms.appData      = appObj;

    appObj->numFramesToTx = APP_TX_FRAMES_TX;
    appObj->numFramesTx = 0U;
    appObj->frameErrorCnt = 0U;
    appObj->maxWidth      = APP_TX_FRAME_WIDTH;
    appObj->maxHeight     = APP_TX_FRAME_HEIGHT;

    /* Initialize transmit instance status */
    Csitx_instStatusInit(&appObj->txStatus);
}

static int32_t App_init(appTxObj* appObj)
{
    int32_t retVal = FVID2_SOK, dmaStatus = UDMA_SOK;
    uint32_t instId = 0U;
    Fvid2_InitPrms initPrms;
    Udma_InitPrms   udmaInitPrms;
    Udma_DrvHandle drvHandle = &gUdmaDrvObj;

    appObj->initPrms.drvHandle = drvHandle;
    appObj->captObj.initPrms.drvHandle = drvHandle;
    /* Fvid2 init */
    Fvid2InitPrms_init(&initPrms);
    initPrms.printFxn = &App_fvidPrint;
    retVal = Fvid2_init(&initPrms);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": Fvid2 Init Failed!!!\r\n");
    }

    /* Do UDMA init before CSITX Init */
    /* UDMA driver init */
    instId = UDMA_INST_ID_BCDMA_1;
    UdmaInitPrms_init(instId, &udmaInitPrms);
    dmaStatus = Udma_init(drvHandle, &udmaInitPrms);
    if(UDMA_SOK != dmaStatus)
    {
        retVal = FVID2_EFAIL;
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": UDMA Init Failed!!!\r\n");
    }

    /* System init */
    retVal = Csitx_init(&appObj->initPrms);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }

    return (retVal);
}

static int32_t App_create(appTxObj* appObj)
{
    int32_t retVal = FVID2_SOK;

    if (retVal == FVID2_SOK)
    {
        /* Fvid2_create() */
        appObj->drvHandle = Fvid2_create(
            CSITX_TX_DRV_ID,
            appObj->instId,
            &appObj->createPrms,
            &appObj->createStatus,
            &appObj->cbPrms);

        if ((NULL == appObj->drvHandle) ||
            (appObj->createStatus.retVal != FVID2_SOK))
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
                      APP_NAME ": Tx Create Failed!!!\r\n");
            retVal = appObj->createStatus.retVal;
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Allocate instance semaphore */
        SemaphoreP_constructBinary(&gLockSem, 0U);
    }

    if (retVal == FVID2_SOK)
    {
        GT_0trace(CsitxAppTrace,
                  GT_INFO,
                  APP_NAME ": CSITX DRV created\r\n");
    }

    return (retVal);
}

int32_t App_csitxTest(appTxObj* appObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t loopCnt;
    uint32_t startTime, elapsedTime, fps;
    uint64_t tempVar;

    /* Allocate and queue all available frames */
    retVal += App_allocAndQFrames(appObj);

    /* start CSITX later as it is source/producer here */
    if (retVal == FVID2_SOK)
    {
        retVal += Fvid2_start(appObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
                      APP_NAME ": Tx Start Failed!!!\r\n");
        }
    }

    startTime = App_getCurTimeInMsec();
    /* Wait for reception completion */
    if (appObj->numFramesToTx == 0U)
    {
        /* indefinite transmit */
        /* TODO: Press any key to stop transmit */
    }
    else
    {
        while (appObj->numFramesTx < appObj->numFramesToTx)
        {
            /* Pend on semaphore until last frame is transmitted */
            SemaphoreP_pend(&gLockSem, SystemP_WAIT_FOREVER);
            /* Check for Image data here */
        }
    }
    elapsedTime = App_getElapsedTimeInMsec(startTime);
    /* fps calculation and some x100 for precision */
    tempVar = ((uint64_t)(appObj->numFramesTx * 100000U)) / (elapsedTime);
    fps = (uint32_t)tempVar;

    /* start CSITX first as it is source/producer here */
    retVal += Fvid2_stop(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": Tx Stop Failed!!!\r\n");
        return retVal;
    }

    retVal += App_txFreeFrames(appObj);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": Tx/Capture free frames FAILED!!!\r\n");
    }

    /* Print CSITX status */
    Csitx_instStatusInit(&appObj->txStatus);
#if (APP_PRINT_DRV_LOGS == 1U)
    /* print debug logs if enabled */
    retVal += Fvid2_control(appObj->drvHandle,
                            IOCTL_CSITX_PRINT_DEBUG_LOGS,
                            NULL,
                            NULL);
#endif

    retVal += Fvid2_control(appObj->drvHandle,
                            IOCTL_CSITX_GET_INST_STATUS,
                            &appObj->txStatus,
                            NULL);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(CsitxAppTrace,
                  GT_INFO,
                  APP_NAME
                  ":Get Tx Status Failed!!!\r\n");
    }
    GT_0trace(CsitxAppTrace, GT_INFO,
        "\n\r==========================================================\r\n");
    GT_0trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Tx Status:\r\n");
    GT_0trace(CsitxAppTrace, GT_INFO,
              "==========================================================\r\n");
    GT_1trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Frames Transmitted: %d\r\n",
              appObj->numFramesTx);
    GT_1trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": Frames Transmitted with errors: %d\r\n",
              appObj->frameErrorCnt);
    GT_1trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": FIFO Overflow Count: %d\r\n",
              appObj->txStatus.overflowCount);
    for(loopCnt = 0U ; loopCnt < APP_TX_CH_NUM ; loopCnt++)
    {
        GT_4trace(CsitxAppTrace, GT_INFO,
              APP_NAME ":[Channel No: %d] | Frame Queue Count: %d |"
              " Frame De-queue Count: %d | Frame Repeat: %d |\r\n",
              loopCnt,
              appObj->txStatus.queueCount[loopCnt],
              appObj->txStatus.dequeueCount[loopCnt],
              appObj->txStatus.frmRepeatCount[loopCnt]);
    }

    GT_4trace(CsitxAppTrace, GT_INFO,
              APP_NAME ": %d frames transmitted in %d msec"
              " at the rate of %d.%2d frames/sec.\r\n",
              appObj->numFramesTx,
              elapsedTime,
              (fps / 100U),
              (fps % 100U));

    return (retVal);
}

static int32_t App_delete(appTxObj* appObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    /* Dequeue all the request from the driver */
    retVal = Fvid2_dequeue(
                    appObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);

    if ((FVID2_SOK != retVal) && (FVID2_ENO_MORE_BUFFERS != retVal))
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": Tx De-queue Failed!!!\r\n");
    }
    else
    {

        retVal = Fvid2_delete(appObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
                      APP_NAME ": FVID2 Delete Failed!!!\r\n");
        }
        else
        {
            appObj->drvHandle = NULL;
        }

        if (FVID2_SOK == retVal)
        {
            /* Delete semaphore */
            SemaphoreP_destruct(&gLockSem);
            GT_0trace(CsitxAppTrace, GT_INFO, APP_NAME ": Tx Driver deleted\r\n");
        }
    }

    return (retVal);
}

static int32_t App_deinit(appTxObj* appObj)
{
    int32_t retVal = FVID2_SOK;
    Udma_DrvHandle drvHandle = &gUdmaDrvObj;

    /* System de-init */
    retVal = Csitx_deInit();
    if(UDMA_SOK != Udma_deinit(drvHandle))
    {
        retVal = FVID2_EFAIL;
        GT_0trace(CsitxAppTrace,
                  GT_ERR,
                  APP_NAME ": UDMA deinit failed!!!\r\n");
    }
    Fvid2_deInit(NULL);

    return (retVal);
}

void App_consolePrintf(const char *pcString, ...)
{
    char printBuffer[APP_PRINT_BUFFER_SIZE];
    va_list arguments;

    /* Start the var args processing. */
    va_start(arguments, pcString);
    vsnprintf (printBuffer, sizeof(printBuffer), pcString, arguments);
    printf("%s", printBuffer);
    /* End the var args processing. */
    va_end(arguments);
}

void App_fvidPrint(const char *str, ...)
{
    App_consolePrintf(str);

    return;
}

void App_dmaPrint(const char *str)
{
    App_consolePrintf(str);

    return;
}

static int32_t App_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmIdx = 0U, idx = 0U;
    static Fvid2_FrameList frmList;
    Fvid2_Frame *pFrm;
    appTxObj *appObj = (appTxObj *) appData;

    GT_assert(CsitxAppTrace, (appData != NULL));

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(
        appObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        appObj->numFramesTx += frmList.numFrames;
        for (frmIdx = 0; frmIdx < frmList.numFrames; frmIdx++)
        {
            pFrm = frmList.frames[frmIdx];
            appObj->chFrmCnt[pFrm->chNum]++;
            /* Update the frame first word with frame number to be transmitted.
               This is used for testing. */
            if (FVID2_FRAME_STATUS_COMPLETED != pFrm->status)
            {
                idx = (appObj->frameErrorCnt % APP_ERR_FRAME_LOG_MAX);
                appObj->errFrmCh[idx] = pFrm->chNum;
                appObj->errFrmNo[idx] = appObj->chFrmCnt[pFrm->chNum];
                appObj->errFrmTs[idx] = (uint32_t)(pFrm->timeStamp64 / 1000U);
                appObj->frameErrorCnt++;
            }
        }

        /* Queue back de-queued frames,
           last param i.e. streamId is unused in DRV */
        retVal = Fvid2_queue(appObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsitxAppTrace, GT_ERR,
                      APP_NAME ": Tx Queue Failed!!!\r\n");
        }
    }

    /* always return 'FVID2_SOK' */
    /* Post semaphore here for sending next Image */
    SemaphoreP_post(&gLockSem);

    return FVID2_SOK;
}

static int32_t App_allocAndQFrames(appTxObj *appObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx = 0U, frmIdx = 0U , loopCnt;
    static Fvid2_FrameList frmList;
    uint32_t pixCnt;
    Fvid2_Frame  *pFrm;


    /* for every channel in a transmit handle,
       allocate memory for and queue frames */
    Fvid2FrameList_init(&frmList);
    frmList.numFrames = 0U;
    for (chIdx = 0U; chIdx < appObj->createPrms.numCh ; chIdx++)
    {
        for (frmIdx = 0U; frmIdx < APP_TX_FRAMES_PER_CH ; frmIdx++)
        {
            pixCnt = 0U;
            /* assign frames memory */
            /* Initialize frames to be transmitted */
            for (loopCnt = 0U ;
                 loopCnt < (APP_TX_FRAME_HEIGHT * APP_TX_FRAME_PITCH) ;
                 )
            {
                CSL_REG32_WR(&gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][loopCnt],
                                (uint32_t)(((pixCnt + 1U) << 16U) | pixCnt));
                pixCnt = (pixCnt + 2U) % APP_TX_FRAME_WIDTH;
                loopCnt += 4U;
            }
            uint32_t val = ((chIdx * APP_TX_FRAMES_PER_CH) + frmIdx);
            gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][3U] = val & 0xFF;
            gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][2U] = (val >> 8) & 0xFF;
            gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][1U] = (val >> 16) & 0xFF;
            gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][0U] = (val >> 24) & 0xFF;

            CacheP_wb(&gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][0],
		      APP_TX_FRAME_SIZE, CacheP_TYPE_ALL);
            /* Only following fields are used in CSITX DRV */
            /*scanf("%d",loopCnt);*/
            pFrm = (Fvid2_Frame *)
                    &appObj->frames[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx];
            pFrm->addr[0U] =
               (uint64_t)&gTxFrms[(chIdx * APP_TX_FRAMES_PER_CH) + frmIdx][0U];
            pFrm->chNum = appObj->createPrms.chCfg[chIdx].chId;
            pFrm->appData = appObj;
            frmList.frames[frmList.numFrames] = pFrm;
            frmList.numFrames++;
        }
    }
    /* queue the frames in frmList
     * All allocated frames are queued here as an example.
     * In general at least 2 frames per stream/channel need to queued
     * before transmit can be started.
     * Failing which, frame could be dropped.
     */
    /* last parameter, i.e. streamId is unused in CSITX DRV */
    retVal = Fvid2_queue(appObj->drvHandle, &frmList, 0U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsitxAppTrace, GT_ERR,
                  APP_NAME ": Tx Queue Failed!!!\r\n");
    }

    return retVal;
}

static int32_t App_txFreeFrames(appTxObj *appObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    /* for every stream and channel in a transmit handle */
    Fvid2FrameList_init(&frmList);

    /* Deq-queue any frames queued more than needed */
    retVal = Fvid2_dequeue(
                    appObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);
    if (retVal == FVID2_ENO_MORE_BUFFERS)
    {
        /* All buffer might be de-queued during stop,
           in this case no error shall be returned */
        retVal = FVID2_SOK;
    }
    /* TODO: Free up frame allocated memories here */
    /* it is global variable here so not needed */

    return (retVal);
}

uint32_t App_getCurTimeInMsec(void)
{
    uint64_t curTimeMsec, curTimeUsec;

    curTimeUsec = ClockP_getTimeUsec();
    curTimeMsec = (curTimeUsec / 1000U);

    return ((uint32_t) curTimeMsec);
}

uint32_t App_getElapsedTimeInMsec(uint32_t startTime)
{
    uint32_t     elapsedTimeMsec = 0U, currTime;

    currTime = App_getCurTimeInMsec();
    if (currTime < startTime)
    {
        /* Counter overflow occured */
        elapsedTimeMsec = (0xFFFFFFFFU - startTime) + currTime + 1U;
    }
    else
    {
        elapsedTimeMsec = currTime - startTime;
    }

    return (elapsedTimeMsec);
}
