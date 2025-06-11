/******************************************************************************
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * MIPI DSITX Host and its Core Driver default configuration file.
 *
 *****************************************************************************/

#ifndef DSITX_CFG_H_
# define DSITX_CFG_H_

# include <drivers/dss/v1/hw_include/dsi/include/dsitx_if.h>

/******************************************************************************
 * Defines and macros.
 *****************************************************************************/

#define DSITX_VID_BYTES_PER_PIXEL 3

/** Maximum interface number starting from 0. This value depends on number of
 * interfaces supported by DSITX Host. */
# define DSITX_MAX_INTERFACE_NUMBER 1

# define DSITX_MAIN_PHY_CLK_CONTINUOUS 0

# define DSITX_VID_PIXEL_MODE DSITX_VID_PIXEL_MODE_RGB_24
# define DSITX_VID_VC_ID 0
# define DSITX_VID_SYNC_PULSE_ACTIVE 0
# define DSITX_VID_SYNC_PULSE_HORIZONTAL 0
# define DSITX_VID_BLK_MODE_LINE DSITX_VID_BLK_MODE_LP
# define DSITX_VID_BLK_MODE_EOL DSITX_VID_BLK_MODE_LP
# define DSITX_VID_RECOVERY_MODE DSITX_VID_RECOVERY_MODE_CONTINUE_TILL_NEXT_HSYNC

# define DSITX_VID_SIZE_VSA 1
# define DSITX_VID_SIZE_VBP 0
# define DSITX_VID_SIZE_VFP 1
# define DSITX_VID_SIZE_VACT 320
# define DSITX_VID_SIZE_HSA 0
# define DSITX_VID_SIZE_HBP 0
# define DSITX_VID_SIZE_HFP 0
# define DSITX_VID_SIZE_RGB (480 * DSITX_VID_BYTES_PER_PIXEL)

# define DSITX_VID_BURST_LP 0

// Below values are taken from example in specification
# define DSITX_VID_WAKEUP_TIME_CL ((DSITX_MAIN_PHY_CLK_CONTINUOUS) ? 0x1 : 0x27)
# define DSITX_VID_WAKEUP_TIME_DL 0xA
# define DSITX_VID_WAKEUP_TIME_DSI 0x13
# define DSITX_VID_WAKEUP_TIME (DSITX_VID_WAKEUP_TIME_CL + DSITX_VID_WAKEUP_TIME_DL + DSITX_VID_WAKEUP_TIME_DSI)

# define DSITX_TVG_STRIPE_SIZE 5 // 2^5==32
# define DSITX_TVG_DISPLAY_MODE DSITX_TVG_MODE_HORIZONTAL_STRIPES
# define DSITX_TVG_STOP_MODE DSITX_TVG_STOP_MODE_AT_END_OF_LINE
# define DSITX_TVG_LINES_PER_FRAME 240
# define DSITX_TVG_PIXELS_PER_LINE 320

# define DSITX_TBG_MODE DSITX_TBG_MODE_START_BURST_STOP
# define DSITX_TBG_USE_PROGRAMMED_DATA 1
# define DSITX_TBG_HS_TRANSFER 1
# define DSITX_TBG_DATA 0xCADE4ECE

# define DSITX_DSC_PPS_BUFFER_SIZE 32

/* DPHY Timeouts */
# define DSITX_DPHY_TIME_CLK_DIV_RATIO 1
# define DSITX_DPHY_TIME_HS_TX_TIMEOUT 30000
# define DSITX_DPHY_TIME_LP_RX_TIMEOUT 30000

/* PHY config */
# define DSITX_PHY_WAIT_BURST_TIME 10

# define DSITX_ULP_MODE_ENABLED 0

#endif

