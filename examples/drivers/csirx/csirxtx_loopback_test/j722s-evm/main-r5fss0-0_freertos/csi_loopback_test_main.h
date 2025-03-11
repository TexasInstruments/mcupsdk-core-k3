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
 *  \file csi_loopback_test_main.h
 *
 *  \brief Header for CSI loopback Example.
 *
 */
#ifndef CSI_LOOPBACK_TEST_MAIN_H_
#define CSI_LOOPBACK_TEST_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/tistdtypes.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/soc.h>
#include <drivers/uart.h>
#include <drivers/csirx.h>
#include <drivers/csitx.h>
#include <drivers/i2c.h>
#include <board/board_control.h>
#include "imx390.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Application name */
#define APP_NAME                                  "CSI_LOOPBACK_TESTAPP"

/**< Number of CSIRX instances exist in SOC */
#define APP_TOTAL_INST                            (CSIRX_INSTANCE_ID_MAX)

/**< Number of CSI instances to test parallelly */
#define APP_TEST_INST_NUM                         ((uint32_t)1U)

/**< Number of channels */
#define APP_CH_NUM                                ((uint32_t)1U)

/**< Input Image Data format */
#define APP_IMAGE_DT                              (FVID2_CSI2_DF_RAW12)

/**< Frame storage format. Only valid for RAW12 DT. */
#define APP_IMAGE_STORAGE_FORMAT                  (FVID2_CCSF_BITS12_UNPACKED16)

/**< Number of frames per stream */
#define APP_FRAMES_PER_CH                         ((uint32_t)4U)

/**< Frame Attribute: Width in pixels */
#define APP_FRAME_WIDTH                           ((uint32_t)1936U)

/**< Frame Attribute: Height in pixels */
#define APP_FRAME_HEIGHT                          ((uint32_t)1100U)

/**< Frame Attribute: Bytes per pixel */
#define APP_FRAME_BPP                             ((uint32_t)2U)

/**< Time period to receive frames in app */
#define APP_TEST_PERIOD_IN_SEC                    ((uint32_t)1)

/**< Frame Attribute: Pitch in bytes */
#define APP_FRAME_PITCH                           ((uint32_t)\
                                                  (APP_FRAME_WIDTH * APP_FRAME_BPP))
/**< Frame Attribute: size in bytes */
#define APP_FRAME_SIZE                            ((uint32_t)\
                                                  (APP_FRAME_HEIGHT * APP_FRAME_WIDTH * APP_FRAME_BPP))

/** \brief Log enable for CSIRX Sample application */
#define AppTrace                                  ((uint32_t) GT_INFO   |\
                                                  (uint32_t) GT_TraceState_Enable)

/**< Maximum number of error frame logs to store.
     It stores most recent errors.*/
#define APP_ERR_FRAME_LOG_MAX                     ((uint32_t)500U)

/**< Print Driver Logs. Set to '1' to enable printing. */
#define APP_PRINT_DRV_LOGS                        (0U)

/**< Number of channels */
#define APP_CH_MAX                                ((uint32_t)4U)

#define APP_PRINT_BUFFER_SIZE                   ((uint32_t)4000)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Capture application object.
 */
typedef struct
{
    uint32_t instId;
   /**< Csirx Drv Instance ID. */
    uint32_t boardCsiInstID;
   /**< Csirx Drv Instance ID. */
    uint32_t cameraSensor;
   /**< Camera sensor type */
    Csirx_CreateParams createPrms;
   /**< Csirx create time parameters */
    Csirx_CreateStatus createStatus;
   /**< Csirx create time status */
    Fvid2_Handle drvHandle;
   /**< FVID2 capture driver handle. */
    Fvid2_CbParams cbPrms;
   /**< Callback params. */
    uint32_t frameErrorCnt;
   /**< Number of erroneous frames received */
    uint32_t maxWidth;
   /**< Max width in pixels - used for buffer allocation for all instance. */
    uint32_t maxHeight;
   /**< Max height in lines - used for buffer allocation for all instance. */
    Csirx_InstStatus captStatus;
   /**< CSIRX Capture status. */
    uint32_t chFrmCnt[APP_CH_NUM];
   /**< Number of frames captured per channel. */
    uint32_t errFrmCh[APP_ERR_FRAME_LOG_MAX];
   /**< Channel to which error frame belongs. */
    uint32_t errFrmNo[APP_ERR_FRAME_LOG_MAX];
   /**< Error frame number for the channel. */
    uint32_t errFrmTs[APP_ERR_FRAME_LOG_MAX];
   /**< TS in ms. */
}CsiLoopback_RxInstObj;

/**
 *  \brief Tx application object.
 */
typedef struct
{
    uint32_t instId;
   /**< Csitx Drv Instance ID. */
    Csitx_InitParams initPrms;
   /**< Csitx init time parameters */
    Csitx_CreateParams createPrms;
   /**< Csitx create time parameters */
    Csitx_CreateStatus createStatus;
   /**< Csitx create time status */
    Fvid2_Handle drvHandle;
   /**< FVID2 transmit driver handle. */
    Fvid2_CbParams cbPrms;
   /**< Callback params. */
    uint32_t frameErrorCnt;
   /**< Number of erroneous frames transmitted */
    uint32_t maxWidth;
   /**< Max width in pixels - used for buffer allocation for all instance. */
    uint32_t maxHeight;
   /**< Max height in lines - used for buffer allocation for all instance. */
    Csitx_InstStatus txStatus;
   /**< CSITX Tx status. */
    uint32_t chFrmCnt[APP_CH_NUM];
   /**< Number of frames transmitted per channel. */
}CsiLoopback_TxInstObj;

/**
 *  \brief Common application object.
 */
typedef struct
{
    Csirx_InitParams rxInitPrms;
   /**< Csirx init time parameters */
    Csitx_InitParams txInitPrms;
   /**< Csitx init time parameters */
    CsiLoopback_RxInstObj appInstObjRx[APP_TEST_INST_NUM];
   /**< Capture application objects */
    CsiLoopback_TxInstObj appInstObjTx[APP_TEST_INST_NUM];
   /**< transmit application objects */
}CsiLoopback_CommonObj;

#endif
