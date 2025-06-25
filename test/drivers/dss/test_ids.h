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

/**
 *  \file test_ids.h
 *
 *  \brief Header file for test ids
 */

#ifndef TEST_IDS_H_
#define TEST_IDS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* DCTRL_IOCTL_TEST IDs */

#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO                    (1U)
#define TEST_DSS_IOCTL_DCTRL_SET_ZERO_PATH_EDGES                      (2U)
#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID                        (3U)
#define TEST_DSS_IOCTL_DCTRL_CONFIG_IN_USE_VP                         (4U)
#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID                       (5U)
#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS                 (6U)
#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM                (7U)
#define TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID                    (8U)
#define TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS                  (9U)
#define TEST_DSS_IOCTL_DCTRL_LINENUM_CB                              (10U)
#define TEST_DSS_IOCTL_DCTRL_SYNCLOST_CB                             (11U)
#define TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL                           (12U)
#define TEST_DSS_IOCTL_DCTRL_DEINIT_ERR                              (13U)
#define TEST_DSS_DCTRL_DRV_DELETE_ERR                                (14U)
#define TEST_DSS_IOCTL_DCTRL_INVALID_VP_ERR_STATS                    (15U)
#define TEST_DSS_IOCTL_DCTRL_STOP_VP                                 (16U)
#define TEST_DSS_DISP_VSYNC_ENABLE                                   (17U)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

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

#endif /* TEST_IDS_H_ */

