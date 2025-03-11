/*
 *  Copyright (c) Texas Instruments Incorporated 2020-25
 *  All rights reserved.
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
 *  \ingroup DRV_CSITX_MODULE
 *  \defgroup DRV_CSITX_CFG_MODULE CSITX Driver Configurations
 *            This is documentation for CSITX driver configuration.
 *
 *  @{
 */

/**
 *  \file csitx_cfg.h
 *
 *  \brief CSITX Driver configuration file.
 */

#ifndef CSITX_CFG_H_
#define CSITX_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \anchor CSITX_CreateDefaultCfg
 *  \name   CSITX Create Default configurations.
 *  \brief  Default values for create time parameters.
 *          See \ref Csitx_CreateParams for details
 *
 *  @{
 */
/** \brief Number of Channels: Maximum number of channels for configuration
 *         Application can save some memory by reducing this to actual number
 *         of channels used rather than all available channels. */
#define CSITX_NUM_CH                             (4U)
/** \brief Number of Pixel Interfaces: Maximum number of Pixel Interfaces for configuration */
#define CSITX_NUM_PIXEL_IF                       (4U)
/** \brief Channel ID: Default channel ID used for initialization */
#define CSITX_CH_ID_DEFAULT                      ((uint32_t) 0x00U)
/** \brief Virtual Channel ID: Default virtual channel ID used
 *         for initialization */
#define CSITX_VC_NUM_DEFAULT                     ((uint32_t) 0x00U)
/** \brief Frame DT: Default frame DT used for initialization */
#define CSITX_OUT_DT_DEFAULT                     (FVID2_CSI2_DF_RAW12)
/** \brief Frame Width: Default frame width used for initialization */
#define CSITX_IN_FRAME_WIDTH_DEFAULT             (1920U)
/** \brief Frame Height: Default frame height used for initialization */
#define CSITX_IN_FRAME_HEIGHT_DEFAULT            (1080U)
/** \brief Horizontal Blanking: Default HB (in terms of number of pixels)
  *        used for initialization */
#define CSITX_IN_FRAME_HB_DEFAULT                (0U)
/** \brief Vertical Blanking: Default VB (in terms of number of pixels)
  *        used for initialization */
#define CSITX_IN_FRAME_VB_DEFAULT                (0U)
/** \brief Default max number of frames that can be queued per capture driver
 *         instance */
#define CSITX_TX_QUEUE_DEPTH_PER_CH              ((uint32_t)10U)
/** \brief Time out value: Time-out value in ms.
 *         This is used as time-out for some of the blocking calls like
 *         completion of reset to prevent the driver from hang. */
#define CSITX_TIMEOUT_VAL_MS                     ((uint32_t)10U)
/** \brief Extended Data-type support for v2.0 partial support.
  *        Set to '1' to enable. */
#define CSITX_DRV_ENABLE_EXTENDED_DT             (1U)
/** \brief Line Start and Line End packets transmit support.
  *        Set to '1' to enable. */
#define CSITX_DRV_ENABLE_LS_LE                   (1U)
/* @} */


/** \brief Log enable for CSITX module */
#define CsitxTrace                             ((uint32_t) GT_INFO   |\
                                                (uint32_t) GT_TraceState_Enable)

/** \brief Enable logging for debug purpose.
  *        Set to '1' to enable debug logging. */
#define CSITX_DRV_ENABLE_DEBUG                    (1U)
/** \brief Number of entries to log for debug */
#define CSITX_DRV_LOG_CNT                         (100U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_CFG_H_ */

/* @} */
