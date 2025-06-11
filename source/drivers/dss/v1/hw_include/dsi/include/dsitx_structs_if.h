/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure" */
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
#ifndef DSITX_STRUCTS_IF_H
#define DSITX_STRUCTS_IF_H

#include "dsitx_if.h"

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** DPHY Power and Reset Control configuration. */
struct DSITX_DphyPwrRstConfig_s
{
    /** Drives dphy_c_rstb output. */
    bool dphyCRstb;
    /** Drives dphy_d_rstb output. */
    uint8_t dphyDRstb;
    /** Drives dphy_pll_pdn output. */
    bool dphyPllPdn;
    /** Drives dphy_cmn_pdn output. */
    bool dphyCmnPdn;
    /** Drives dphy_c_pdn output. */
    bool dphyCPdn;
    /** Drives dphy_d_pdn output. */
    uint8_t dphyDPdn;
    /** Drives dphy_pll_pso output. */
    bool dphyPllPso;
    /** Drives dphy_cmn_pso output. */
    bool dphyCmnPso;
};

/** DSC Event Status structure. */
struct DSITX_DscEventStatus_s
{
    /** DSC PPS Command Sent */
    bool dscPpsDone;
    /** DSC Execute Command Sent */
    bool dscExecDone;
};

/** DPHY timings configuration structure. */
struct DSITX_DphyConfig_s
{
    /**
     * DPHY's Clock division ratio. The clock division means that
     * the check counter is incremented every 2^clkDivisionRatio clock cycles and
     * not that a clock divider is built internally! The value of the division
     * is limited to 2^11. clkDivisionRatio must not exceed 11.
    */
    uint8_t clkDivisionRatio;
    /** DPHY's High Speed TX timeout detection value. */
    uint32_t hstxTimeout;
    /** DPHY's Low Power RX timeout detection value. */
    uint32_t lprxTimeout;
    /**
     * For clock lane - specify what the duration to
     * leave ULP mode is in system clock cycles. This value is multiplied by
     * 1000 in DSITX Host.
    */
    uint16_t clkLaneUlpTimeout;
    /**
     * For data lane(s) - specify what the duration to
     * leave ULP mode is in system clock cycles. This value is multiplied by
     * 1000 in DSITX Host.
    */
    uint16_t dataLaneUlpTimeout;
};

/** Structure containing main data path configuration. */
struct DSITX_DataPathConfig_s
{
    /** Enables or disables link. */
    bool linkEnabled;
    /** Operation mode of selected interface. */
    DSITX_InterfaceMode interfaceMode;
    /** Determines which video interface is active. */
    DSITX_VideoInterfaceSelection videoIfSelect;
    /** Enables Video Stream Generator or indicates if it's enabled or disabled. */
    bool videoStreamGenEnabled;
    /**
     * Test Video Generator is (or should be) enabled. This is not start signal.
     * Should not be set if Interface 1 is enabled and operating in Video Mode.
    */
    bool tvgEnabled;
    /**
     * Enables tearing effect on Interface 1.
     * Note: Enabling TE on all SDI interfaces simultaneously is not supported.
    */
    bool if1TeEnabled;
    /** Enables tearing effect from register. */
    bool regTeEnabled;
    /** Enables read operations. */
    bool readOpEnabled;
    /** Enables BTA packets. */
    bool btaEnabled;
    /** Display generates ECC on its response packets. */
    bool dispGenEcc;
    /** Display generates checksum on its response packets. */
    bool dispGenChecksum;
    /** Generates EOT packet after a transfer in HS Mode. */
    bool hostEotGen;
    /** Display adds an EOT packet to its LPDT transfers. */
    bool dispEotGen;
    /**
     * Enables TE Polling feature following MIPI recommendations
     * (Polling by software).
    */
    bool teHwPolling;
    /**
     * Enables TE Polling feature following internal solution.
     * (Currently not supported by DSITX3 Host)
    */
    bool teMipiPolling;
};

/** Main control settings for physical lanes. */
struct DSITX_PhyConfig_s
{
    /** Enable second lane. */
    bool lane2Enabled;
    /** Enable third lane. */
    bool lane3Enabled;
    /** Enable fourth lane. */
    bool lane4Enabled;
    /**
     * Clock lane should remain in High Speed mode.
     * No return in STOP state.
    */
    bool laneClkContinous;
    /**
     * Specifies that clock lane can be switched in
     * Ultra Low Power mode (on demand).
    */
    bool laneClkUlpMode;
    /** Data lane 1 can be switched to Ultra Low Power mode. */
    bool laneUlpMode[DSITX_MAX_LANE_NUMBER];
    /**
     * Delay to respect between two High Speed bursts (in clock cycles).
     * Value of 0 is forbidden.
    */
    uint8_t waitBurstTime;
};

/** Main control settings for 3d video. */
struct DSITX_Video3dConfig_s
{
    /** Video 3D mode for VSYNC Control Parameter */
    DSITX_Video3dMode vidSync3dMode;
    /** Video 3D format for VSYNC Control Parameter1 */
    DSITX_Video3dFormat vidSync3dFormat;
    /** A second VSYNC enabled between L and R images  */
    bool vidVsync3dSecondEnable;
    /** Starting Frame. */
    DSITX_Video3dFirstSide vidVsync3dLr;
    /** Enable 3D. */
    bool vidVsync3dEnable;
};

/** Structure containing Command Mode configuration. */
struct DSITX_CommandModeSettings_s
{
    /** Send Command from interface 1 in Low Power Mode if possible. */
    bool sendFromInt1InLp;
    /** Send Command from interface 3 in Low Power Mode if possible. */
    bool sendFromInt3InLp;
    /** Virtual Channel ID of request from interface 1. */
    uint8_t vcIdIf1;
    /** Virtual Channel ID of request from interface 3. */
    uint8_t vcIdIf3;
    /**
     * Length of TE window.
     * Bits 9:0 determines timeout value while bits 11:10 determines multiplier:
     * 00b - 256x, 01b - 512x, 10b - 1024x, 11b - 2048x.
    */
    uint16_t teTimeout;
    /**
     * Value to use to fill packet during data underrun or to complete
     * unterminated packet. Referred also as padding value.
    */
    uint8_t fillValue;
    /** Specifies interface with higher priority in fixed mode. */
    DSITX_CmdArbitrationPriority arbPriority;
    /** Arbitration mode. */
    DSITX_CmdArbitrationMode arbMode;
};

/** Image and Blanking Packet size configuration structure. */
struct DSITX_VideoSize_s
{
    /**
     * Duration of the VSYNC pulse (in lines).
     * This value should be at least one and greater or equal to two when in pulse mode.
    */
    uint8_t vsa;
    /** Length of the Vertical Back Porch (in lines). */
    uint8_t vbp;
    /**
     * Length of the Vertical Front Porch (in lines).
     * Needs to be greater than 0.
    */
    uint8_t vfp;
    /** Vertical length of active area (in line). Must be greater than 0. */
    uint16_t vact;
    /**
     * Duration of HSYNC pulse (in bytes).
     * Need to be at least set to one if pulse mode is enabled.
    */
    uint16_t hsa;
    /**
     * Length of the Horizontal Back Porch (in bytes).
     * If 0, HBP packet is sent with 0 payload.
    */
    uint16_t hbp;
    /**
     * Length of the Horizontal Front Porch.
     * If 0, no HFP packet is sent.
    */
    uint16_t hfp;
    /** Size of the RGB packet (in bytes). */
    uint16_t rgb;
    /** Packet length on end of line if burst mode (in bytes). */
    uint16_t blkEolPacket;
    /**
     * Packet length in blanking line if line has to be filled with a packet
     * and sync is an event (in bytes).
    */
    uint16_t blkLineEventPacket;
    /**
     * Packet length in blanking line if line has to be filled with a packet
     * and sync is a pulse (in bytes).
    */
    uint16_t blkLinePulsePacket;
};

/** Color struct. */
struct DSITX_Color_s
{
    /**
     * Red component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t r;
    /**
     * Green component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t g;
    /**
     * Blue component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t b;
};

/** Error color struct. */
struct DSITX_ErrorColor_s
{
    /**
     * Red component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t r;
    /**
     * Green component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t g;
    /**
     * Blue component of the fill color.
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t b;
    /**
     * Byte used do pad data (when system does not know exactly where it is).
     * Maximum value for this field depends on chosen video pixel mode.
    */
    uint16_t padValue;
};

/** Video Command Arbiter settings. */
struct DSITX_VcaConfig_s
{
    /** Size of biggest burst packet (packet that fits after RGB in burst mode). */
    uint16_t maxBurstLimit;
    /**
     * Determines if after an active line, the system can switch in
     * Low Power mode (true) or should complete the line with NULL packet (false).
    */
    bool burstLp;
    /** Exact maximum size of the burst packet (packet that fits after RGB in burst mode). */
    uint16_t exactBurstLimit;
    /** Maximum size of the line packet (packet that fits in blanking line). */
    uint16_t maxLineLimit;
};

/** Video Mode Settings. */
struct DSITX_VideoModeSettings_s
{
    /**
     * Video entry point.
     * (Only DSITX_VID_START_MODE_START_ON_VSYNC is supported)
    */
    DSITX_VideoStartMode startMode;
    /**
     * Video stop point.
     * (Only stop DSITX_VID_STOP_MODE_STOP_JUST_BEFORE_VSYNC is supported)
    */
    DSITX_VideoStopMode stopMode;
    /**
     * Specifies the Virtual Channel Identifier of the video packets.
     * First field in interlaced mode.
    */
    uint8_t vidId;
    /**
     * Specifies the Virtual Channel Identifier of the
     * second field of interlaced video packet.
    */
    uint8_t vidIdSdfd;
    /** Specifies the datatype of RGB packets. */
    DSITX_VideoDataType header;
    /**
     * Video Pixel Mode.
     * (YCbCr modes are not supported by DSITX3 Host)
    */
    DSITX_VideoPixelMode vidPixelMode;
    /** Signals if system works in burst mode or not. */
    bool burstMode;
    /** Synchro are pulse (1) or event (0) during active area. */
    bool syncPulseActive;
    /**
     * Synchro are pulse (1) or event (0) all the time.
     * To be set only when syncPulseActive is set.
    */
    bool syncPulseHorizontal;
    /**
     * Behavior during blanking time.
     * 1xb - LP, 01b - Blanking packet, 00b - NULL packet
    */
    DSITX_VideoBlankingMode blkLineMode;
    /**
     * Behavior during end of line in burst mode.
     * 1xb - LP, 01b - Blanking packet, 00b - NULL packet
    */
    DSITX_VideoBlankingMode blkEolMode;
    /** Specifies recovery mode. */
    DSITX_VideoRecoveryMode recoveryMode;
    /** Enables interlaced video mode. */
    bool interlancedVideoModeEnabled;
    /**
     * When interlaced mode is enabled this allows to choose which field
     * to start the video stream.
    */
    uint8_t fieldSwitch;
    /** Specifies the duration of the BLLP period (in clock cycles). */
    uint16_t blkEolDuration;
    /** Error color. */
    DSITX_ErrorColor errColor;
    /**
     * Estimated time to perform transition from Low Power Mode to
     * High Speed Mode on DPHY (in clock cycles).
     * This time must be shorter than line duration.
    */
    uint16_t regWakeupTime;
    /** Duration of the blanking area for VSA/VBP/VFP (in clock cycles). */
    uint32_t regLineDuration;
    /** Ignore miss vsync. */
    bool ignoreMissVsync;
};

/** Test Video Generator configuration. */
struct DSITX_TestVideoModeConfig_s
{
    /** Determines if TVG was enabled or disabled. */
    bool enabled;
    /** Size of the stripe (in pixels) - defined by 2^stripeSize. */
    DSITX_TvgStripeSize stripeSize;
    /** TVG display mode. */
    DSITX_TvgDisplayMode displayMode;
    /** TVG stop mode. */
    DSITX_TvgStopMode stopMode;
    /**
     * Number of lines per frame.
     * Must be equal to VACT size set for VSG (see VideoModeSettings).
    */
    uint16_t linesPerFrame;
    /**
     * Number of bytes per line.
     * Must be equal to RGB size set for VSG (see VideoModeSettings).
    */
    uint16_t bytesPerLine;
    /** Color 1 of Dummy frame. */
    DSITX_Color color1;
    /** Color 2 of Dummy frame. */
    DSITX_Color color2;
};

/**
 * IP configuration values. This structure is read only and it is filled by
 * DSITX Core Driver while calling DSITX_GetIpConf function.
*/
struct DSITX_IpConf_s
{
    /** Depth of the RX FIFO. */
    uint8_t rxFifoDepth;
    /**
     * Number of Data Lanes. Not fully implemented for two lanes.
     * 0 means one data line; 1 means two data lanes;
     * 2 means three data lanes; 3 means four data lanes.
    */
    uint8_t maxLaneNumber;
    /** Number of the SDI Interfaces. */
    uint8_t sdiIfNumber;
    /** Datapath bus size in bits. */
    uint8_t datapathSize;
    /** SDI data bus size in bits. */
    uint8_t sdiIfDataBusSize;
    /** Direct Command FIFO depth. Each item has width equal to datapathSize. */
    uint16_t directCmdFifoDepth;
    /** FIFO depth in VRS block. Each item has 50-bit width. */
    uint8_t vrsBlockFifoDepth;
    /**
     * Low Power FIFO depth in sending path.
     * FIFO depth will be set to 2^lpFifoDepth. Each item has 8-bit width.
    */
    uint8_t lpFifoDepth;
    /**
     * High Speed FIFO depth in sending path.
     * The depth of the FIFO is set to 2^hsFifoDepth. Each item has 8-bit width.
    */
    uint8_t hsFifoDepth;
};

/**
 * Structure describing DSITX Host version and ID. Its content is filled by Core
 * Driver when calling getHwIdAndVersion function.
*/
struct DSITX_HwIdAndVersion_s
{
    /** Vendor ID. */
    uint16_t vendorId;
    /** Product ID. */
    uint8_t productId;
    /** Hardware revision number. */
    uint8_t revisionNumber;
    /** Major revision value. */
    uint8_t majorRevision;
    /** Minor revision value. */
    uint8_t minorRevision;
};

/** This structure contains information that is used to control DSITX Link. */
struct DSITX_DsiLinkConfig_s
{
    /** Specifies if PLL is enabled (non 0) or disabled (0). */
    bool pllEnabled;
    /** Starts or stops clock lane. */
    bool clkLaneEnabled;
    /** Starts data lanes . */
    bool datLaneEnabled[DSITX_MAX_LANE_NUMBER];
    /** Switches clock lane in ULP Mode. */
    bool clkLaneInUlpMode;
    /** Switches data lanes in ULP Mode. */
    bool datLaneInUlpMode[DSITX_MAX_LANE_NUMBER];
    /** Enable SDI1 Interface. */
    bool if1Enabled;
    /** Enable DPI Interface. */
    bool if2Enabled;
    /** Enable DSC Interface. */
    bool if3Enabled;
    /** When enabled, data lanes are forced back in stop mode. */
    bool forceStopMode;
    /** Force clock lanes back in STOP mode. */
    bool clkForceStop;
};

/** Structure describing the Direct Command Request. */
struct DSITX_DirectCommandRequest_s
{
    /** Virtual Channel ID in case of read or write command type. */
    uint8_t vcId;
    /**
     * Read or write command data size.
     * In case of write request maximum size value is 16.
     * In case of read request maximum size value is 2.
    */
    uint8_t cmdSize;
    /** In case of read or write command this field state data type. */
    uint8_t head;
    /** If set command will be sent as long packet. */
    bool longPacket;
    /** Nature of command. */
    DSITX_DirectCommandType type;
    /** Enables Low Power mode for sending command request. */
    bool lpMode;
    /**
     * Determines if function processing the request will wait for request
     * to finish by polling status register or enable interrupts and exit
     * immediately.
    */
    bool wait;
    /** Direct Command execution status. Set after command completes. */
    uint32_t status;
    /**
     * Specifies what events should be enabled and reported to the user
     * when they occur. Set before sending request.
    */
    uint32_t enEvents;
    /** Value of ACK if acknowledge with error has been received. */
    uint16_t ackVal;
    /** Value of the trigger in case of trigger command. */
    DSITX_DirectCommandTriggerType triggerValue;
    /** Direct Command read status. Set after read command completes. */
    uint32_t rdStatus;
    /**
     * Specifies what read command events should be enabled and reported
     * to the user when they occur. Set before sending request. This field
     * will be ignored in case of command type different than
     * DSITX_DCR_TYPE_READ.
    */
    uint32_t enRdEvents;
    /** Pointer to buffer from which command data will be sent. */
    uint8_t* cmdData;
    /**
     * Nature of Read Command. If true then this is a DCS packet.
     * If false then its a generic read.
     * This field is set by DSITX Host Driver when calling
     * getDirectCmdRdDataProperties function.
    */
    bool dcsPk;
    /**
     * Number of bytes received from Display.
     * Value of this field is set by the Core Driver
     * when calling getDirectCmdRdDataProperties function.
    */
    uint16_t recDataSize;
    /** Pointer to buffer where data received from Display will be stored. */
    uint8_t* recData;
};

/**
 * Generic Control and Status. Used by System for any extra DFT control
 * through the DSITX controller
*/
struct DSITX_TestGeneric_s
{
    /** Test control - Drives test_generic_ctrl output. */
    uint16_t ctrl;
    /** Test status - Value of test_generic_status input. */
    uint16_t status;
};

/** Configuration parameters passed to probe & init functions. */
struct DSITX_Config_s
{
    /**
     * Base address of the register space.
     *
    */
    struct DSITX_Regs_s* regBase;
    /**
     * Number of physical lanes used in Video Mode.
     * Valid values are 1-4.
    */
    uint8_t numOfLanes;
    /** This handler is called when Direct Command request status changes. */
    DSITX_DirectCmdEventHandler dirCmdEventHandler;
    /**
     * This handler is called during DSITX Host initialization to allow client
     * configure (initialize) Display before DSITX Host Core Driver
     * starts to operate.
    */
    DSITX_InitializeDisplayHandler initDisplay;
};

/** System requirements returned by probe. */
struct DSITX_SysReq_s
{
    /** Size of memory required for driver's private data. */
    uint32_t privDataSize;
};

/** Information about ASF in DSITX controller. */
struct DSITX_AsfInfo_s
{
    /** ASF registers start addresses. */
    volatile uint32_t* regBase;
};

/**
 *  @}
 */

#endif	/* DSITX_STRUCTS_IF_H */
