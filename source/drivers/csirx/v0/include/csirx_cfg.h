/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
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
 *  \ingroup DRV_CSIRX_MODULE
 *  \defgroup DRV_CSIRX_CFG_MODULE CSIRX Driver Configurations
 *            This is documentation for CSIRX driver configuration.
 *
 *  @{
 */

/**
 *  \file csirx_cfg.h
 *
 *  \brief CSIRX Driver configuration file.
 */

#ifndef CSIRX_CFG_H_
#define CSIRX_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \anchor CSIRX_CreateDefaultCfg
 *  \name   CSIRX Create Default configurations.
 *  \brief  Default values for create time parameters.
 *          See \ref Csirx_CreateParams for details
 *
 *  @{
 */
/** \brief Number of Channels: Maximum number of channels for configuration */
#define CSIRX_NUM_CH                             (CSIRX_NUM_CH_MAX)
/** \brief Channel ID: Default channel ID used for initialization */
#define CSIRX_CH_ID_DEFAULT                      ((uint32_t) 0x00U)
/** \brief Virtual Channel ID: Default virtual channel ID used
 *         for initialization */
#define CSIRX_VC_NUM_DEFAULT                     ((uint32_t) 0x00U)
/** \brief Frame Width: Default frame width used for initialization */
#define CSIRX_IN_DT_DEFAULT                      (FVID2_CSI2_DF_RGB888)
/** \brief Default max number of frames that can be queued per capture driver
 *         instance */
#define CSIRX_CAPT_QUEUE_DEPTH_PER_CH            ((uint32_t)10U)
/** \brief Time out value: Time-out value in ms */
#define CSIRX_TIMEOUT_VAL_MS                     ((uint32_t)10U)
/* @} */

/** \brief Log enable for CSIRX module */
#define CsirxTrace                             ((uint32_t) GT_INFO   |\
                                                (uint32_t) GT_TraceState_Enable)

/** \brief Enable logging for debug purpose.
  *        Set to '1' to enable debug logging. */
#define CSIRX_DRV_ENABLE_DEBUG                    (0U)
/** \brief Number of entries to log for debug */
#define CSIRX_DRV_LOG_CNT                         (2000U)
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

#endif /* #ifndef CSIRX_CFG_H_ */

/* @} */
