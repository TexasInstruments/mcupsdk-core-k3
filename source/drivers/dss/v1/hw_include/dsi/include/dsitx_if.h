/**********************************************************************
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
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.00.31660be
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for MIPI DSITX Host Controller
 **********************************************************************/

#ifndef DSITX_IF_H
#define DSITX_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */


/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
#define	DSITX_MAX_LANE_NUMBER 4U

#define	DSITX_MAGIC_NUMBER 0xCADD5U

/**
 *  @}
 */


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
typedef struct DSITX_DphyPwrRstConfig_s DSITX_DphyPwrRstConfig;
typedef struct DSITX_DscEventStatus_s DSITX_DscEventStatus;
typedef struct DSITX_DphyConfig_s DSITX_DphyConfig;
typedef struct DSITX_DataPathConfig_s DSITX_DataPathConfig;
typedef struct DSITX_PhyConfig_s DSITX_PhyConfig;
typedef struct DSITX_Video3dConfig_s DSITX_Video3dConfig;
typedef struct DSITX_CommandModeSettings_s DSITX_CommandModeSettings;
typedef struct DSITX_VideoSize_s DSITX_VideoSize;
typedef struct DSITX_Color_s DSITX_Color;
typedef struct DSITX_ErrorColor_s DSITX_ErrorColor;
typedef struct DSITX_VcaConfig_s DSITX_VcaConfig;
typedef struct DSITX_VideoModeSettings_s DSITX_VideoModeSettings;
typedef struct DSITX_TestVideoModeConfig_s DSITX_TestVideoModeConfig;
typedef struct DSITX_IpConf_s DSITX_IpConf;
typedef struct DSITX_HwIdAndVersion_s DSITX_HwIdAndVersion;
typedef struct DSITX_DsiLinkConfig_s DSITX_DsiLinkConfig;
typedef struct DSITX_DirectCommandRequest_s DSITX_DirectCommandRequest;
typedef struct DSITX_TestGeneric_s DSITX_TestGeneric;
typedef struct DSITX_Config_s DSITX_Config;
typedef struct DSITX_SysReq_s DSITX_SysReq;
typedef struct DSITX_AsfInfo_s DSITX_AsfInfo;

typedef struct DSITX_PrivateData_s DSITX_PrivateData;

/**********************************************************************
 * Enumerations
 **********************************************************************/
/** Status of the DSITX Link. */
typedef enum
{
    /** Initial value. */
    DSITX_LINK_STATUS_BITS_INIT = 0U,
    /** Interface 1 signals an unterminated packet. */
    DSITX_MAIN_STS_IF1_UNTERM_PCK = DSITX__MCTL_MAIN_STS__IF1_UNTERM_PCK_MASK,
    /** Signals an LP_RX time-out error. */
    DSITX_MAIN_STS_LPRX_TO_ERR = DSITX__MCTL_MAIN_STS__LPRX_TO_ERR_MASK,
    /** Signals an HS_TX time-out error. */
    DSITX_MAIN_STS_HSTX_TO_ERR = DSITX__MCTL_MAIN_STS__HSTX_TO_ERR_MASK,
    /** Signals data lane 4 is ready. */
    DSITX_MAIN_STS_DAT4_READY = DSITX__MCTL_MAIN_STS__DAT4_READY_MASK,
    /** Signals data lane 3 is ready. */
    DSITX_MAIN_STS_DAT3_READY = DSITX__MCTL_MAIN_STS__DAT3_READY_MASK,
    /** Signals data lane 2 is ready. */
    DSITX_MAIN_STS_DAT2_READY = DSITX__MCTL_MAIN_STS__DAT2_READY_MASK,
    /** Signals data lane 1 is ready. */
    DSITX_MAIN_STS_DAT1_READY = DSITX__MCTL_MAIN_STS__DAT1_READY_MASK,
    /** Signals clock lane is ready (normal DSITX operation can start). */
    DSITX_MAIN_STS_CLKLANE_READY = DSITX__MCTL_MAIN_STS__CLKLANE_READY_MASK,
    /** Signals PLL is locked - data coming from DCB (if DSITX link is PLL master) or copy of pll_en (if DSITX link is slave). */
    DSITX_MAIN_STS_PLL_LCK = DSITX__MCTL_MAIN_STS__PLL_LCK_MASK
} DSITX_LinkStatusBits;

/** Status and error bits of the Command Mode operations. */
typedef enum
{
    /** Initial value. */
    DSITX_CMD_MODE_STATUS_BITS_INIT = 0U,
    /** Signals if CSM is running - command(s) are being proceeded. */
    DSITX_CMD_MODE_STS_CSM_RUNNING = DSITX__CMD_MODE_STS__CSM_RUNNING_MASK,
    /** A read request was received while read capability was not enabled. */
    DSITX_CMD_MODE_STS_ERR_UNWANTED_RD = DSITX__CMD_MODE_STS__ERR_UNWANTED_RD_MASK,
    /** Signals when a data shortage occurs on IF1. */
    DSITX_CMD_MODE_STS_ERR_IF1_UNDERRUN = DSITX__CMD_MODE_STS__ERR_IF1_UNDERRUN_MASK,
    /** TE window time-out. */
    DSITX_CMD_MODE_STS_ERR_TE_MISS = DSITX__CMD_MODE_STS__ERR_TE_MISS_MASK,
    /** No TE generated by display. */
    DSITX_CMD_MODE_STS_ERR_NO_TE = DSITX__CMD_MODE_STS__ERR_NO_TE_MASK
} DSITX_CmdModeStatusBits;

/** Status and error bits of the Video Mode operations. */
typedef enum
{
    /** Initial value. */
    DSITX_VID_MODE_STATUS_BITS_INIT = 0U,
    /** Specifies whether the VSG is in recovery mode or not. */
    DSITX_VID_STS_VSG_RECOVERY = DSITX__VID_MODE_STS__VSG_RECOVERY_MASK,
    /** Signals that packets in SDI interface differ from the expected size (as specified by rgb_size). */
    DSITX_VID_STS_ERR_VRS_WRONG_LENGTH = DSITX__VID_MODE_STS__ERR_VRS_WRONG_LENGTH_MASK,
    /** Signals the read was too long. */
    DSITX_VID_STS_ERR_LONGREAD = DSITX__VID_MODE_STS__ERR_LONGREAD_MASK,
    /** Signals the long packet is too long to pass during a long slot. */
    DSITX_VID_STS_ERR_LINEWRITE = DSITX__VID_MODE_STS__ERR_LINEWRITE_MASK,
    /** Signals a 'long' packet has been sent during active area. */
    DSITX_VID_STS_ERR_BURSTWRITE = DSITX__VID_MODE_STS__ERR_BURSTWRITE_MASK,
    /** Less lines than expected between 2 VSYNC. */
    DSITX_VID_STS_REG_ERR_SMALL_HEIGHT = DSITX__VID_MODE_STS__REG_ERR_SMALL_HEIGHT_MASK,
    /** Less bytes received than expected between 2 HSYNC. */
    DSITX_VID_STS_REG_ERR_SMALL_LENGTH = DSITX__VID_MODE_STS__REG_ERR_SMALL_LENGTH_MASK,
    /** Missing VSYNC. */
    DSITX_VID_STS_ERR_MISSING_VSYNC = DSITX__VID_MODE_STS__ERR_MISSING_VSYNC_MASK,
    /** Missing HSYNC. */
    DSITX_VID_STS_ERR_MISSING_HSYNC = DSITX__VID_MODE_STS__ERR_MISSING_HSYNC_MASK,
    /** Data starvation at input of the VSG. */
    DSITX_VID_STS_ERR_MISSING_DATA = DSITX__VID_MODE_STS__ERR_MISSING_DATA_MASK,
    /** VSG is running (1) or stopped (0). */
    DSITX_VID_STS_VSG_RUNNING = DSITX__VID_MODE_STS__VSG_RUNNING_MASK
} DSITX_VidModeStatusBits;

/** Status of the Test Video Generator module. */
typedef enum
{
    /** Initial value. */
    DSITX_TVG_STATUS_BITS_INIT = 0U,
    /** Test Video generator is running. */
    DSITX_TVG_STS_TVG_IS_RUNNING = DSITX__TVG_STS__TVG_RUNNING_MASK
} DSITX_TvgStatusBits;

/** Status of the DPHY - errors detected by DPHY. */
typedef enum
{
    /** Initial value. */
    DSITX_DPHY_ERROR_BITS_INIT = 0U,
    DSITX_DPHY_STS_ERR_CONT_LP1_4 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP1_4_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP1_3 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP1_3_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP1_2 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP1_2_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP1_1 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP1_1_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP0_4 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP0_4_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP0_3 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP0_3_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP0_2 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP0_2_MASK,
    DSITX_DPHY_STS_ERR_CONT_LP0_1 = DSITX__MCTL_DPHY_ERR__ERR_CONT_LP0_1_MASK,
    DSITX_DPHY_STS_ERR_CONTROL_4 = DSITX__MCTL_DPHY_ERR__ERR_CONTROL_4_MASK,
    DSITX_DPHY_STS_ERR_CONTROL_3 = DSITX__MCTL_DPHY_ERR__ERR_CONTROL_3_MASK,
    DSITX_DPHY_STS_ERR_CONTROL_2 = DSITX__MCTL_DPHY_ERR__ERR_CONTROL_2_MASK,
    DSITX_DPHY_STS_ERR_CONTROL_1 = DSITX__MCTL_DPHY_ERR__ERR_CONTROL_1_MASK,
    DSITX_DPHY_STS_ERR_SYNCESC_4 = DSITX__MCTL_DPHY_ERR__ERR_SYNCESC_4_MASK,
    DSITX_DPHY_STS_ERR_SYNCESC_3 = DSITX__MCTL_DPHY_ERR__ERR_SYNCESC_3_MASK,
    DSITX_DPHY_STS_ERR_SYNCESC_2 = DSITX__MCTL_DPHY_ERR__ERR_SYNCESC_2_MASK,
    DSITX_DPHY_STS_ERR_SYNCESC_1 = DSITX__MCTL_DPHY_ERR__ERR_SYNCESC_1_MASK,
    DSITX_DPHY_STS_ERR_ESC_4 = DSITX__MCTL_DPHY_ERR__ERR_ESC_4_MASK,
    DSITX_DPHY_STS_ERR_ESC_3 = DSITX__MCTL_DPHY_ERR__ERR_ESC_3_MASK,
    DSITX_DPHY_STS_ERR_ESC_2 = DSITX__MCTL_DPHY_ERR__ERR_ESC_2_MASK,
    DSITX_DPHY_STS_ERR_ESC_1 = DSITX__MCTL_DPHY_ERR__ERR_ESC_1_MASK
} DSITX_DphyErrorBits;

/** DPI Status Bits */
typedef enum
{
    /** Initial value. */
    DSITX_DPI_STATUS_BITS_INIT = 0U,
    /** DPI FIFO Overflow. */
    DSITX_DPI_STS_PIXEL_BUF_OVERFLOW = DSITX__DPI_IRQ_STS__PIXEL_BUF_OVERFLOW_STS_MASK
} DSITX_DpiStatusBits;

/** Status of the Direct Command Request. */
typedef enum
{
    /** Initial value. */
    DSITX_DIRECT_COMMAND_STATUS_BITS_INIT = 0U,
    /** A command is being sent. */
    DSITX_DCR_STS_TRANSMISSION = DSITX__DIRECT_CMD_STS__CMD_TRANSMISSION_MASK,
    /** Write command request completed. */
    DSITX_DCR_STS_WRITE_COMPLETED = DSITX__DIRECT_CMD_STS__WRITE_COMPLETED_MASK,
    /** Trigger command request completed. */
    DSITX_DCR_STS_TRIGGER_COMPLETED = DSITX__DIRECT_CMD_STS__TRIGGER_COMPLETED_MASK,
    /** Read command request completed. */
    DSITX_DCR_STS_READ_COMPLETED = DSITX__DIRECT_CMD_STS__READ_COMPLETED_MASK,
    /** Acknowledge with no error has been received in case of command with BTA. */
    DSITX_DCR_STS_ACK_RECEIVED = DSITX__DIRECT_CMD_STS__ACK_RECEIVED_MASK,
    /** Acknowledge with error has been received in case of command with BTA. */
    DSITX_DCR_STS_ACK_WITH_ERR_RECEIVED = DSITX__DIRECT_CMD_STS__ACK_WITH_ERR_RECEIVED_MASK,
    /** Trigger has been received in case of command with BTA. */
    DSITX_DCR_STS_TRIGGER_RECEIVED = DSITX__DIRECT_CMD_STS__TRIGGER_RECEIVED_MASK,
    /** TE has been received in case of command with BTA. */
    DSITX_DCR_STS_TE_RECEIVED = DSITX__DIRECT_CMD_STS__TE_RECEIVED_MASK,
    /** BTA request completed. */
    DSITX_DCR_STS_BTA_COMPLETED = DSITX__DIRECT_CMD_STS__BTA_COMPLETED_MASK,
    /** DSITX Link recovered link mastership after a BTA request. */
    DSITX_DCR_STS_BTA_FINISHED = DSITX__DIRECT_CMD_STS__BTA_FINISHED_MASK,
    /** Read command terminated with error. */
    DSITX_DCR_STS_READ_COMPLETED_WITH_ERR = DSITX__DIRECT_CMD_STS__READ_COMPLETED_WITH_ERR_MASK
} DSITX_DirectCommandStatusBits;

/** Status of the Direct Command read Request. */
typedef enum
{
    /** Initial value. */
    DSITX_DIRECT_COMMAND_READ_STATUS_BITS_INIT = 0U,
    /** One error detected and fixed by ECC. */
    DSITX_DCR_RD_STS_ERR_FIXED = DSITX__DIRECT_CMD_RD_STS__ERR_FIXED_MASK,
    /** More than 1 error detected by ECC. */
    DSITX_DCR_RD_STS_ERR_UNCORRECTABLE = DSITX__DIRECT_CMD_RD_STS__ERR_UNCORRECTABLE_MASK,
    /** Error(s) detected by checksum. */
    DSITX_DCR_RD_STS_ERR_CHECKSUM = DSITX__DIRECT_CMD_RD_STS__ERR_CHECKSUM_MASK,
    /** Command opcode not understood. */
    DSITX_DCR_RD_STS_ERR_UNDECODABLE = DSITX__DIRECT_CMD_RD_STS__ERR_UNDECODABLE_MASK,
    /** Receive packet not complete. */
    DSITX_DCR_RD_STS_ERR_RECEIVE = DSITX__DIRECT_CMD_RD_STS__ERR_RECEIVE_MASK,
    /** Packet size exceeds maximum. */
    DSITX_DCR_RD_STS_ERR_OVERSIZE = DSITX__DIRECT_CMD_RD_STS__ERR_OVERSIZE_MASK,
    /** Length error has been detected. */
    DSITX_DCR_RD_STS_ERR_WRONG_LENGTH = DSITX__DIRECT_CMD_RD_STS__ERR_WRONG_LENGTH_MASK,
    /** EOT requested but not received. */
    DSITX_DCR_RD_STS_ERR_MISSING_EOT = DSITX__DIRECT_CMD_RD_STS__ERR_MISSING_EOT_MASK,
    /** EOT received with error. */
    DSITX_DCR_RD_STS_ERR_EOT_WITH_ERR = DSITX__DIRECT_CMD_RD_STS__ERR_EOT_WITH_ERR_MASK
} DSITX_DirectCommandReadStatusBits;

/** SDI Interface mode. */
typedef enum
{
    /** Command Mode. */
    DSITX_IF_MODE_COMMAND = 0U,
    /** Video Mode. */
    DSITX_IF_MODE_VIDEO = 1U
} DSITX_InterfaceMode;

/** Video Interface selections. */
typedef enum
{
    /** Interface SDI. */
    DSITX_VID_IF_SELECT_IF1 = 0U,
    /** Interface DPI. */
    DSITX_VID_IF_SELECT_IF2 = 1U,
    /** Interface DSC. */
    DSITX_VID_IF_SELECT_IF3 = 2U
} DSITX_VideoInterfaceSelection;

/** Direct Command Request event handler response. */
typedef enum
{
    /**
    * Finish processing request. After returning this value Core Driver
    * will complete processing request and another request may be sent.
    * This value shall be returned if status bits indicate that request
    * was completed and user wants to send another.
    */
    DSITX_DCR_RESULT_FINISHED = 0U,
    /**
    * Continue processing request. After returning this value Core Driver
    * will continue to process request and another event may occur.
    * In most cases this value shall be returned in response to
    * DCR_STS_TRANSMISSION event and if any status bits indicating
    * that request is completed were not set.
    */
    DSITX_DCR_RESULT_CONTINUE = 1U,
    /**
    * Finish processing request and report error. After returning this
    * value Core Driver will complete processing request and another
    * request may be sent.
    * This value shall be returned if status bits indicate that request
    * was completed and user wants to send another.
    */
    DSITX_DCR_RESULT_FINISHED_ERR = 2U
} DSITX_DirectCommandEventHandlerResponse;

/** PLL's High Speed input type. */
typedef enum
{
    /** Command Mode. */
    DSITX_PLL_OUT_SEL_SYSTEM = 0U,
    /** Video Mode. */
    DSITX_PLL_OUT_SEL_DSI = 1U
} DSITX_LinkPllOutSel;

/** Type of the Direct Command. */
typedef enum
{
    /** Write command. */
    DSITX_DCR_TYPE_WRITE = 0U,
    /** Read command. */
    DSITX_DCR_TYPE_READ = 1U,
    /** Tearing Effect command. */
    DSITX_DCR_TYPE_TE = 4U,
    /** Trigger Command. */
    DSITX_DCR_TYPE_TRIGGER = 5U,
    /** Bus Turn Around command. */
    DSITX_DCR_TYPE_BTA = 6U
} DSITX_DirectCommandType;

/** Type of the Trigger value. */
typedef enum
{
    /** Reset (in TX direction). */
    DSITX_DCR_TRIGGER_VALUE_RESET = 0x01U
} DSITX_DirectCommandTriggerType;

/** Lane state */
typedef enum
{
    /** Lane is in a Start state. */
    DSITX_LANE_STATE_START = 0U,
    /** Lane is in a Idle state. */
    DSITX_LANE_STATE_IDLE = 1U,
    /** Lane is in a Write state. */
    DSITX_LANE_STATE_WRITE = 2U,
    /** Lane is in a ULPM state. */
    DSITX_LANE_STATE_ULMP = 3U,
    /** Lane is in a Read state. This is state is valid only for Data Lane 1. */
    DSITX_LANE_STATE_READ = 4U
} DSITX_LaneState;

/** Test Video Generator Display Mode. */
typedef enum
{
    /** Single color. */
    DSITX_TVG_MODE_SINGLE_COLOR = 0U,
    /** Vertical stripes. */
    DSITX_TVG_MODE_VERTICAL_STRIPES = 2U,
    /** Horizontal stripes. */
    DSITX_TVG_MODE_HORIZONTAL_STRIPES = 3U
} DSITX_TvgDisplayMode;

/** Test Video Generator Stop Mode. */
typedef enum
{
    /** Stop at the end of frame. */
    DSITX_TVG_STOP_MODE_AT_END_OF_FRAME = 0U,
    /** Stop at the end of line. */
    DSITX_TVG_STOP_MODE_AT_END_OF_LINE = 1U,
    /** Stop immediate. */
    DSITX_TVG_STOP_MODE_IMMEDIATE = 2U
} DSITX_TvgStopMode;

/** Test Video Generator stripe size. */
typedef enum
{
    /** 1 pixel. */
    DSITX_TVG_STRIPE_SIZE_1 = 0U,
    /** 2 pixels. */
    DSITX_TVG_STRIPE_SIZE_2 = 1U,
    /** 4 pixels. */
    DSITX_TVG_STRIPE_SIZE_4 = 2U,
    /** 8 pixels. */
    DSITX_TVG_STRIPE_SIZE_8 = 3U,
    /** 16 pixels. */
    DSITX_TVG_STRIPE_SIZE_16 = 4U,
    /** 32 pixels. */
    DSITX_TVG_STRIPE_SIZE_32 = 5U,
    /** 64 pixels. */
    DSITX_TVG_STRIPE_SIZE_64 = 6U,
    /** 128 pixels. */
    DSITX_TVG_STRIPE_SIZE_128 = 7U
} DSITX_TvgStripeSize;

/** Video3dMode */
typedef enum
{
    /** 3D off 2D mode only. */
    DSITX_VIDEO_MODE_2D = 0U,
    /** 3D on Portrait Orientation. */
    DSITX_VIDEO_MODE_PORTRAIT = 1U,
    /** 3D on Landscape orientation. */
    DSITX_VIDEO_MODE_LANDSCAPE = 2U
} DSITX_Video3dMode;

/** Video3dFormat */
typedef enum
{
    /** Line Format alternating line of left and right data. */
    DSITX_VIDEO_FORMAT_LINE = 0U,
    /** Frame Format alternating frames of left and right data. */
    DSITX_VIDEO_FORMAT_FRAME = 1U,
    /** Pixel Format alternating frames of left and right data. */
    DSITX_VIDEO_FORMAT_PIXEL = 2U
} DSITX_Video3dFormat;

/** Video3dFirstSide */
typedef enum
{
    /** Data is sent left first then right. */
    DSITX_VIDEO_START_LEFT = 0U,
    /** Data is sent right first then left. */
    DSITX_VIDEO_START_RIGHT = 1U
} DSITX_Video3dFirstSide;

/** Arbitration priority */
typedef enum
{
    /** Initial value. */
    DSITX_CMD_ARB_PRIORITY_INIT = 0U,
    /** SDI interface has higher priority. */
    DSITX_CMD_ARB_PRIORITY_SDI = 1U,
    /** DSC interface has higher priority. */
    DSITX_CMD_ARB_PRIORITY_DSC = 2U
} DSITX_CmdArbitrationPriority;

/** Arbitration mode type */
typedef enum
{
    /** Fixed Mode. */
    DSITX_CMD_ARBITRATION_MODE_FIXED = 0U,
    /** Round Robin Mode. */
    DSITX_CMD_ARBITRATION_MODE_ROUND_ROBIN = 1U
} DSITX_CmdArbitrationMode;

/** Video Pixel Modes */
typedef enum
{
    /** 16-bit RGB */
    DSITX_VID_PIXEL_MODE_RGB_16 = 0U,
    /** 18-bit RGB */
    DSITX_VID_PIXEL_MODE_RGB_18 = 1U,
    /** 18-bit RGB loosely packed */
    DSITX_VID_PIXEL_MODE_RGB_18_LOOSELY = 2U,
    /** 24-bit RGB */
    DSITX_VID_PIXEL_MODE_RGB_24 = 3U,
    /** 30-bit RGB */
    DSITX_VID_PIXEL_MODE_RGB_30 = 4U,
    /** 36-bit RGB */
    DSITX_VID_PIXEL_MODE_RGB_36 = 5U,
    /** 12-bit YCbCr */
    DSITX_VID_PIXEL_MODE_YCBCR_12 = 8U,
    /** 16-bit YCbCr */
    DSITX_VID_PIXEL_MODE_YCBCR_16 = 9U,
    /** 20-bit YCbCr */
    DSITX_VID_PIXEL_MODE_YCBCR_20 = 10U,
    /** 24-bit YCbCr */
    DSITX_VID_PIXEL_MODE_YCBCR_24 = 11U
} DSITX_VideoPixelMode;

/** Video Data Types */
typedef enum
{
    /** Default value */
    DSITX_VID_DATA_TYPE_DEFAULT = 0x0U,
    /** Loosely Packed Pixel Stream 20-bit YCbCr 4_2_2 */
    DSITX_VID_DATA_TYPE_YCBCR_20 = 0x0CU,
    /** Packed Pixel Stream 24-bit YCbCr 4_2_2 */
    DSITX_VID_DATA_TYPE_YCBCR_24 = 0x1CU,
    /** Packed Pixel Stream 16-bit YCbCr 4_2_2 */
    DSITX_VID_DATA_TYPE_YCBCR_16 = 0x2CU,
    /** Packed Pixel Stream 30-bit RGB 10-10-10 */
    DSITX_VID_DATA_TYPE_RGB_30 = 0x0DU,
    /** Packed Pixel Stream 36-bit RGB 12-12-12 */
    DSITX_VID_DATA_TYPE_RGB_36 = 0x1DU,
    /** Packed Pixel Stream 12-bit YCbCr 4_2_0 */
    DSITX_VID_DATA_TYPE_YCBCR_12 = 0x3DU,
    /** Packed Pixel Stream 16-bit RGB 5-6-5 */
    DSITX_VID_DATA_TYPE_RGB_16 = 0x0EU,
    /** Packed Pixel Stream 18-bit RGB 6-6-6 */
    DSITX_VID_DATA_TYPE_RGB_18 = 0x1EU,
    /** Loosely Packed Pixel Stream 18-bit RGB 6-6-6 */
    DSITX_VID_DATA_TYPE_RGB_18_LOOSELY = 0x2EU,
    /** Packed Pixel Stream 24-bit RGB 8-8-8 */
    DSITX_VID_DATA_TYPE_RGB_24 = 0x3EU
} DSITX_VideoDataType;

/** Type of video recovery modes. */
typedef enum
{
    /** Continue with dummy packets till next HSYNC. */
    DSITX_CONTINUE_TILL_NEXT_HSYNC = 0U,
    /** Continue until next stop point (according to stop mode) */
    DSITX_CONTINUE_UNTIL_NEXT_STOP_POINT = 2U,
    /** Continue with dummy packets until next VSYNC. */
    DSITX_CONTINUE_TILL_NEXT_VSYNC = 3U
} DSITX_VideoRecoveryMode;

/** Video start mode. */
typedef enum
{
    /** The stream starts on the VSYNC packet. */
    DSITX_VID_START_MODE_START_ON_VSYNC = 0U
} DSITX_VideoStartMode;

/** Video stop mode. */
typedef enum
{
    /** Initial value. */
    DSITX_VID_STOP_MODE_STOP_INIT = 0U,
    /** Stop just before VSYNC. */
    DSITX_VID_STOP_MODE_STOP_JUST_BEFORE_VSYNC = 1U
} DSITX_VideoStopMode;

/** Video blanking mode during blanking time or end of line in burst mode. */
typedef enum
{
    /** NULL packet. */
    DSITX_VID_BLK_MODE_NULL_PACKET = 0U,
    /** Blanking packet. */
    DSITX_VID_BLK_MODE_BLANKING_PACKET = 1U,
    /** LP. */
    DSITX_VID_BLK_MODE_LP = 2U
} DSITX_VideoBlankingMode;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/**
 * DSITX Link event handler type.
 * This event is raised when status of the DSITX Link changes and if
 * corresponding interrupts are enabled.
*/
typedef void (*DSITX_DsiLinkEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * Command Mode event handler type.
 * This event is raised when status of the Command Mode changes and if
 * corresponding interrupts are enabled.
*/
typedef void (*DSITX_CmdModeEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * Video Mode event handler type.
 * This event is raised when status of the Video Mode changes and if
 * corresponding interrupts are enabled.
*/
typedef void (*DSITX_VidModeEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * Test Video Generator event handler type.
 * This event is raised when status of the Test Video Generator changes
 * and if corresponding interrupts are enabled.
*/
typedef void (*DSITX_TvgEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * DPHY error event handler type.
 * This event is raised when errors in DPHY are detected
 * and if corresponding interrupts are enabled.
*/
typedef void (*DSITX_DphyErrorEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * DPI event handler type.
 * This event is raised when enabled DPI interrupt occurs.
*/
typedef void (*DSITX_DpiEventHandler)(DSITX_PrivateData* pD, uint32_t status);

/**
 * Direct Command event handler type.
 * This event is raised if status of the Direct Command Request changes
 * and if corresponding interrupts are enabled.
*/
typedef DSITX_DirectCommandEventHandlerResponse (*DSITX_DirectCmdEventHandler)(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr);

/** Display configuration handler type. */
typedef uint32_t (*DSITX_InitializeDisplayHandler)(DSITX_PrivateData* pD);

/**
 *  @}
 */

/** @defgroup DriverFunctionAPI Driver Function API
 *  Prototypes for the driver API functions. The user application can link statically to the
 *  necessary API functions and call them directly.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/

/**
 * Obtains the driver's memory requirements to support the given
 * configuration.
 * @param[in] config Proposed driver/hardware configuration.
 * @param[out] sysReq Returns the memory requirements for given configuration in field privDataSize.
 * @return EOK On success (requirements struct filled).
 * @return EINVAL If config contains invalid values or not supported configuration.
 */
uint32_t DSITX_Probe(const DSITX_Config* config, DSITX_SysReq* sysReq);

/**
 * Initializes the Driver and the DSITX Host as specified in the
 * config structure.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Specifies driver/hardware configuration.
 * @return EOK On success
 * @return EINVAL If illegal/inconsistent values in 'config' doesn't support feature(s) required by 'config' parameters.
 */
uint32_t DSITX_Init(DSITX_PrivateData* pD, const DSITX_Config* config);

/**
 * Driver ISR. Platform-specific code is responsible for ensuring this
 * gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so. This function must not be called after calling destroy
 * and releasing private data memory.
 * @param[in] pD Driver instance data filled by init.
 */
void DSITX_Isr(DSITX_PrivateData* pD);

/**
 * Start the DSITX driver, enabling interrupts. This is called after
 * the client has successfully initialized the driver and hooked the
 * driver's ISR (the isr member of this struct) to the IRQ.
 * @param[in] pD Driver state info specific to this instance.
 */
void DSITX_Start(DSITX_PrivateData* pD);

/**
 * Stops the DSITX driver by disabling interrupts.
 * @param[in] pD Driver state info specific to this instance.
 */
void DSITX_Stop(DSITX_PrivateData* pD);

/**
 * Destroy the driver (automatically performs a stop).
 * @param[in] pD Driver instance data
 */
void DSITX_Destroy(DSITX_PrivateData* pD);

/**
 * Sets DPHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure which specifies DPHY configuration.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDphyConfig(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config);

/**
 * Obtains DPHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DPHY configuration will be written.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDphyConfig(DSITX_PrivateData* pD, DSITX_DphyConfig* config);

/**
 * Sets Data Path configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Data Path configuration.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDataPathConfig(DSITX_PrivateData* pD, const DSITX_DataPathConfig* config);

/**
 * Obtains Data Path configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which Data Path configuration will be written.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDataPathConfig(DSITX_PrivateData* pD, DSITX_DataPathConfig* config);

/**
 * Sets PHY main configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing PHY configuration.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetPhyConfig(DSITX_PrivateData* pD, const DSITX_PhyConfig* config);

/**
 * Obtains PHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which PHY configuration will be written.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetPhyConfig(DSITX_PrivateData* pD, DSITX_PhyConfig* config);

/**
 * Sets the DPHY Power and Reset Control configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Pointer to structure containing configuration.
 * @return EINVAL If pD or cfg is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_SetDphyPwrAndRstCtrl(DSITX_PrivateData* pD, const DSITX_DphyPwrRstConfig* cfg);

/**
 * Obtains the DPHY Power and Reset Control configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Pointer to structure to which DPHY Power and Reset Control
 *    configuration will be written.
 * @return EINVAL If pD or cfg is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_GetDphyPwrAndRstCtrl(DSITX_PrivateData* pD, DSITX_DphyPwrRstConfig* cfg);

/**
 * Sets DSITX Link configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing DSITX Link configuration.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDsiLinkConfig(DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config);

/**
 * Obtains DSITX Link configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX Link setup will be stored.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDsiLinkConfig(DSITX_PrivateData* pD, DSITX_DsiLinkConfig* config);

/**
 * Obtains IP configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX IP configuration will be stored.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetIpConf(DSITX_PrivateData* pD, DSITX_IpConf* config);

/**
 * Reads information about DSITX version.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] id Pointer to structure where DSITX version information will be stored.
 * @return EINVAL If pD or id is NULL.
 * @return EOK If information is successfully obtained.
 */
uint32_t DSITX_GetHwIdAndVersion(DSITX_PrivateData* pD, DSITX_HwIdAndVersion* id);

/**
 * Sets Command Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cmdMode Pointer to structure containing detailed information about
 *    Command Mode configuration.
 * @return EINVAL If cmdMode contains invalid values.
 * @return EOK On success.
 */
uint32_t DSITX_SetCommandMode(DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode);

/**
 * Reads Command Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cmdMode Pointer to structure to which detailed information about
 *    Command Mode configuration will be written.
 * @return EINVAL If pD or cmdMode is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_GetCommandMode(DSITX_PrivateData* pD, DSITX_CommandModeSettings* cmdMode);

/**
 * Sets Video Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidMode Pointer to structure containing Video Mode configuration.
 * @return EINVAL If provided configuration contains invalid values.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVideoMode(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode);

/**
 * Reads Video Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidMode Pointer to structure to which Video Mode configuration will be written.
 * @return EINVAL If pD or vidMode is NULL.
 * @return EOK If configuration was successfully read.
 */
uint32_t DSITX_GetVideoMode(const DSITX_PrivateData* pD, DSITX_VideoModeSettings* vidMode);

/**
 * Sets Video Command Arbiter configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vca Pointer to structure containing Video Command Arbiter configuration.
 * @return EINVAL If provided configuration contains invalid values.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVcaConfig(DSITX_PrivateData* pD, const DSITX_VcaConfig* vca);

/**
 * Reads Video Command Arbiter configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vca Pointer to structure to which Video Command Arbiter configuration will be written.
 * @return EINVAL If pD or vca is NULL.
 * @return EOK If size is successfully set.
 */
uint32_t DSITX_GetVcaConfig(DSITX_PrivateData* pD, DSITX_VcaConfig* vca);

/**
 * Sets Video size configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidSize Pointer to structure containing Video Size configuration.
 * @return EINVAL If provided configuration contains invalid values.
 * @return EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVideoSize(DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize);

/**
 * Reads Video size configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidSize Pointer to structure to which Video Size configuration will be written.
 * @return EINVAL If pD or vidSize is NULL.
 * @return EOK If size is successfully set.
 */
uint32_t DSITX_GetVideoSize(DSITX_PrivateData* pD, DSITX_VideoSize* vidSize);

/**
 * Configures Test Video Generator using provided configuration. This
 * function ignores value of 'enabled' field in config structure. New
 * configuration can be applied only if Test Video Generator is not
 * running.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Test Video Generator configuration.
 *    Value of the enabled field is ignored. Use startTvg function to enable TVG.
 * @return EINVAL If provided configuration contains invalid values.
 * @return EPERM If Test Video Generator is enabled.
 * @return EOK If Test Video Generator was successfully started.
 */
uint32_t DSITX_SetTvgConfig(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config);

/**
 * Reads Test Video Generator configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which received Test Video Generator
 *    configuration will be written.
 * @return EINVAL If pD or config is NULL.
 * @return EOK If Test Video Generator configuration was successfully read.
 */
uint32_t DSITX_GetTvgConfig(DSITX_PrivateData* pD, DSITX_TestVideoModeConfig* config);

/**
 * Enables Test Video Generator.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] wait Determines if function will wait until Test Video Generator is started
 *    (true) or will exit immediately (false) and raise TVG Event (if enabled)
 *    when TVG starts.
 * @return EINVAL If pD is NULL.
 * @return EIO On timeout.
 * @return EOK If operation was successful.
 */
uint32_t DSITX_StartTvg(DSITX_PrivateData* pD, bool wait);

/**
 * Stops Test Video Generator. If stop mode is 'stop immediate' then
 * the VSG needs to be stopped and video system restarted.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] wait Determines if function will wait until Test Video Generator is in
 *    stopped state (true) or will exit immediately (false).
 * @return EINVAL If pD is NULL.
 * @return EPERM If TVG stop mode is set to 'stop immediate'.
 * @return EIO On timeout.
 * @return EOK If operation was successful.
 */
uint32_t DSITX_StopTvg(DSITX_PrivateData* pD, bool wait);

/**
 * Sends Direct Command Request. Only one request can be sent at a
 * time. After sending command request user shall not make changes to
 * request structure unless request structure is provided to user in
 * the callback function.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] dcr Pointer to structure containing detailed information about command.
 *    This structure will be updated by Core Driver during command
 *    execution. After passing it to Core Driver user shall not make
 *    any changes to its content until dcr status is set to completed
 *    or it is presented in callback function.
 * @return EINVAL If pD NULL.
 * @return EPERM If dcr cannot be sent due to state of the DSITX link (e.g. TVG enabled).
 * @return EINPROGRESS If processing of other request has not yet been completed.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SendDirectCmd(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr);

/**
 * Sets DSITX Link Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DSITX Link events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    DSITX Link will be disabled and value of the events argument is ignored.
 */
uint32_t DSITX_SetDsiLinkEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_DsiLinkEventHandler callback);

/**
 * Sets Command Mode Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Command Mode events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Command Mode event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Command Mode will be disabled and value of the events argument is ignored.
 * @return EINVAL If pD is NULL.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetCmdModeEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_CmdModeEventHandler callback);

/**
 * Sets Video Mode Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Video Mode events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Video Mode event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Video Mode will be disabled and value of the events argument is ignored.
 * @return EINVAL If pD is NULL.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetVidModeEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_VidModeEventHandler callback);

/**
 * Sets Test Video Generator Event Handler function and informs Core
 * Driver which events should be reported to the user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Test Video Generator events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Test Video Generator event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Test Video Generator will be disabled and value of events argument is ignored.
 * @return EINVAL If pD is NULL.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetTvgEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_TvgEventHandler callback);

/**
 * Sets DPHY Error Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DPHY errors should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when DPHY error occurs.
 *    When value of this pointer is set to NULL then all error events for
 *    DPHY will be disabled and value of the events argument is ignored.
 * @return EINVAL If pD is NULL.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetDphyErrorEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_DphyErrorEventHandler callback);

/**
 * Sets DPI Event Handler function and informs Core Driver which
 * events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DPI events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when DPI interrupt occurs.
 *    When value of this pointer is set to NULL then all events for DPI
 *    will be disabled and value of the events argument is ignored.
 * @return EINVAL If pD is NULL.
 * @return EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetDpiEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_DpiEventHandler callback);

/**
 * Sets DSITX Test register.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] test Pointer to structure containing control configuration.
 * @return EINVAL If pD is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_SetTestGeneric(DSITX_PrivateData* pD, const DSITX_TestGeneric* test);

/**
 * Obtains DSITX Test register value.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] test Pointer to structure to which control configuration will be
 *    written.
 * @return EINVAL If pD or test are NULL.
 * @return EOK On success.
 */
uint32_t DSITX_GetTestGeneric(DSITX_PrivateData* pD, DSITX_TestGeneric* test);

/**
 * Sets Video 3D configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Video 3D configuration.
 * @return EINVAL If pD or value is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_SetVideo3dConfig(DSITX_PrivateData* pD, const DSITX_Video3dConfig* cfg);

/**
 * Gets Video 3D configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Video 3D configuration.
 * @return EINVAL If pD or value is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_GetVideo3dConfig(DSITX_PrivateData* pD, DSITX_Video3dConfig* cfg);

/**
 * Retrieves ASF information from DSITX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return EINVAL If pD or asfInfo is NULL.
 * @return EOK On success.
 */
uint32_t DSITX_GetAsfInfo(const DSITX_PrivateData* pD, DSITX_AsfInfo* asfInfo);

/**
 * Checks if lanes are ready.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] repeatCount status checking repeat count
 * @return EINVAL If pD is NULL.
 * @return EIO If lanes are not ready.
 * @return EOK On success.
 */
uint32_t DSITX_CheckLanesState(const DSITX_PrivateData* pD, uint32_t repeatCount);

/**
 * Waits for PLL lock event.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] repeatCount status checking repeat count
 * @return EINVAL If pD is NULL.
 * @return EIO If timeout occurs.
 * @return EOK On success.
 */
uint32_t DSITX_WaitForPllLock(const DSITX_PrivateData* pD, uint32_t repeatCount);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* DSITX_IF_H */
