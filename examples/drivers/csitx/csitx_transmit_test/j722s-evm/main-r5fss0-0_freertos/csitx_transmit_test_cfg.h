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

#ifndef CSITX_TRANSMIT_TEST_CFG_H_
#define CSITX_TRANSMIT_TEST_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "kernel/dpl/TimerP.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>

#include <drivers/hw_include/tistdtypes.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/soc.h>
#include <drivers/uart.h>
#include <drivers/csirx.h>
#include <drivers/csitx.h>
#include <kernel/nortos/dpl/common/ClockP_nortos_priv.h>
#include <board/board_control.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/device_manager/sciserver/sciserver_init.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Application name */
#define APP_NAME                        "CSITX_TX_APP"

/**< CSITX instance to be used. Valid values are:
      0: For CSITX instance 0
      1: For CSITX instance 1 (Only for J721S2, as J721E has only instance 0) */
#define CSITX_INSTANCE                          (0U)
/**< Number of channels */
#define APP_TX_CH_NUM                           ((uint32_t)4U)
/**< Input Image Data format */
#define APP_TX_IMAGE_DT                         (FVID2_CSI2_DF_RAW16)
/**< Frame storage format. Only valid for RAW12 DT. */
#define APP_TX_IMAGE_STORAGE_FORMAT             (FVID2_CCSF_BITS16_PACKED)
/**< Number of frames to transmit. Set it to '0' for indefinite transmit */
#define APP_TX_FRAMES_TX                        ((uint32_t)1000U)
/**< Number of frames per Tx channel */
#define APP_TX_FRAMES_PER_CH                    ((uint32_t)1U)
/**< Number of frames per Rx channel */
#define APP_RX_FRAMES_PER_CH                    ((uint32_t)4U)
/**< Frame Attribute: Width in pixels */
#define APP_TX_FRAME_WIDTH                      ((uint32_t)1920U)
/**< Frame Attribute: Height in pixels */
#define APP_TX_FRAME_HEIGHT                     ((uint32_t)1080U)
/**< Frame Attribute: Bytes per pixel */
#define APP_TX_FRAME_BPP                        ((uint32_t)2U)
/**< Frame storage format. Only valid for RAW12 DT. */
#define APP_CAPT_IMAGE_STORAGE_FORMAT           (FVID2_CCSF_BITS12_UNPACKED16)

/**< Frame Attribute: Pitch in bytes */
#define APP_TX_FRAME_PITCH                      ((uint32_t)(APP_TX_FRAME_WIDTH * APP_TX_FRAME_BPP))
/**< Frame Attribute: size in bytes */
#define APP_TX_FRAME_SIZE                       ((uint32_t)(APP_TX_FRAME_HEIGHT * APP_TX_FRAME_WIDTH * APP_TX_FRAME_BPP))

/* Print buffer character limit for prints- UART or CCS Console */
#define APP_PRINT_BUFFER_SIZE                   ((uint32_t)4000)

/** \brief Log enable for CSITX Sample application */
#define CsitxAppTrace                           ((uint32_t) GT_INFO   | (uint32_t) GT_TraceState_Enable)

/**< Maximum number of error frame logs to store.
     It stores most recent errors.*/
#define APP_ERR_FRAME_LOG_MAX                   ((uint32_t)500U)

/**< Print Driver Logs. Set to '1' to enable printing. */
#define APP_PRINT_DRV_LOGS                      (0U)

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
    Csirx_InitParams initPrms;
   /**< Csirx init time parameters */
    Csirx_CreateParams createPrms;
   /**< Csirx create time parameters */
    Csirx_CreateStatus createStatus;
   /**< Csirx create time status */
    Fvid2_Handle drvHandle;
   /**< FVID2 capture driver handle. */
    Fvid2_CbParams cbPrms;
   /**< Callback params. */
    uint32_t numFramesToCapture;
   /**< Number of frames to receive for a given configuration */
    volatile uint32_t numFramesRcvd;
   /**< Number of frames received */
    uint32_t frameErrorCnt;
   /**< Number of erroneous frames received */
    Fvid2_Frame frames[APP_TX_FRAMES_PER_CH * APP_TX_CH_NUM];
   /**< FVID2 Frames that will be used for capture. */
    Csirx_InstStatus captStatus;
   /**< CSIRX Capture status. */
    uint32_t chFrmCnt[APP_TX_CH_NUM];
   /**< Number of frames captured per channel. */
    uint32_t errFrmCh[APP_ERR_FRAME_LOG_MAX];
   /**< Channel to which error frame belongs. */
    uint32_t errFrmNo[APP_ERR_FRAME_LOG_MAX];
   /**< Error frame number for the channel. */
    uint32_t errFrmTs[APP_ERR_FRAME_LOG_MAX];
   /**< TS in ms. */
} appCaptObj;

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
    uint32_t numFramesToTx;
   /**< Number of frames to transmit for a given configuration */
    volatile uint32_t numFramesTx;
   /**< Number of frames transmitted */
    uint32_t frameErrorCnt;
   /**< Number of erroneous frames transmitted */
    uint32_t maxWidth;
   /**< Max width in pixels - used for buffer allocation for all instance. */
    uint32_t maxHeight;
   /**< Max height in lines - used for buffer allocation for all instance. */
    Fvid2_Frame frames[APP_TX_FRAMES_PER_CH * APP_TX_CH_NUM];
   /**< FVID2 Frames that will be used for transmit. */
    Csitx_InstStatus txStatus;
   /**< CSITX Tx status. */
    uint32_t chFrmCnt[APP_TX_CH_NUM];
   /**< Number of frames transmitted per channel. */
    uint32_t errFrmCh[APP_ERR_FRAME_LOG_MAX];
   /**< Channel to which error frame belongs. */
    uint32_t errFrmNo[APP_ERR_FRAME_LOG_MAX];
   /**< Error frame number for the channel. */
    uint32_t errFrmTs[APP_ERR_FRAME_LOG_MAX];
   /**< TS in ms. */
   appCaptObj captObj;
   /**< CSIRX Capture Object. */
}appTxObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern uint8_t gTxFrms[(APP_TX_FRAMES_PER_CH * APP_TX_CH_NUM)][APP_TX_FRAME_SIZE];
extern uint8_t gCompareFrame;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */

#endif /* CSITX_TX_TEST_CFG_H_ */
