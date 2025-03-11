/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */
/**********************************************************************
* Copyright (C) 2012-2019 Cadence Design Systems, Inc.
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
*          api-generator: 13.04.5beed88
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for MIPI CSI Host Controller
**********************************************************************/
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_CSITX CSITX CSL-FL
 *
 *  @{
 *
 * The CSI2 TX CSL FL provides the APIs to configure CSI2TX module.
 */

#ifndef CSITX_STRUCTS_IF_H
#define CSITX_STRUCTS_IF_H


/** @defgroup CsitxDataStructure CSITX Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
* Structures and unions
**********************************************************************/
/** Configuration parameters passed to probe & init */
struct CSITX_Config_s
{
    /** base address of the CSITX controller registers */
    CSITX_Regs* regBase;
    bool enableInterrupts;
};

/** CSI-2 Transmitter Device Configuration Register */
struct CSITX_DeviceConfig_s
{
    /** v1.3 features available. */
    uint8_t v1p3FeaturesEnable;
    /** RX Compatibility Mode. */
    uint8_t rxCompatibilityMode;
    /** Scrambler present. */
    uint8_t scramblerPresent;
    /** ASF present. */
    uint8_t asfPresent;
    /** Number of Datatypes supported. */
    uint8_t numDts;
    /** Number of Virtual channels supported. */
    uint8_t numVcs;
    /** Internal datapath width. */
    uint8_t datapathSize;
    /** Number of stream interfaces. */
    uint8_t numStreams;
    /** Cadence D-PHY present. */
    uint8_t cdnsPhyPresent;
    /** Max Number of Lanes. */
    uint8_t numLanes;
};

/** System requirements returned by probe */
struct CSITX_SysReq_s
{
    /** "Size of memory required for driver's private data." */
    uint32_t privDataSize;
};

/** Configuration of DPHY (CFG1) */
struct CSITX_DphyConfig1_s
{
    /** D-PHY Transmitter FORCE_STOP_MODE TX Data Lane 0. */
    bool forceStopModeLn0;
    /** D-PHY Transmitter FORCE_STOP_MODE TX Data Lane 1. */
    bool forceStopModeLn1;
    /** D-PHY Transmitter FORCE_STOP_MODE TX Data Lane 2. */
    bool forceStopModeLn2;
    /** D-PHY Transmitter FORCE_STOP_MODE TX Data Lane 3. */
    bool forceStopModeLn3;
    /** D-PHY Transmitter invert differential pair on TX Data Lane 0. */
    bool diffInvertLn0;
    /** D-PHY Transmitter invert differential pair on TX Data Lane 1. */
    bool diffInvertLn1;
    /** D-PHY Transmitter invert differential pair on TX Data Lane 2. */
    bool diffInvertLn2;
    /** D-PHY Transmitter invert differential pair on TX Data Lane 3. */
    bool diffInvertLn3;
    /** D-PHY Transmitter invert differential pair on TX Clock Lane. */
    bool diffInvertClock;
};

/** Configuration of DPHY */
struct CSITX_DphyConfig_s
{
    /** Active low reset for D-PHY */
    bool dphyReset;
    /** D-PHY Calibration Enable. */
    bool dphyCalEnable;
    /** D-PHY Clock Mode. */
    uint8_t dphyClockMode;
    /** D-PHY Mode */
    uint8_t dphyMode;
    /** Active high enable for DPHY clock lane */
    bool dphyClkEnable;
    /** Active high enable for DPHY data lane 3 */
    bool dphyLn3Enable;
    /** Active high enable for DPHY data lane 2 */
    bool dphyLn2Enable;
    /** Active high enable for DPHY data lane 1 */
    bool dphyLn1Enable;
    /** Active high enable for DPHY data lane 0 */
    bool dphyLn0Enable;
};

struct CSITX_DataTypeConfig_s
{
    /** "Line counter enabling." */
    uint32_t lineCountEnable;
    /** "Line start/end generating enabling." */
    uint32_t lineStartEndEnable;
    /** "Data type." */
    uint8_t dataType;
    /** "Extended Data Type." */
    uint32_t extendedDataType;
    /** "Packed enable." */
    uint32_t packedEnable;
    /** "Max line number." */
    uint16_t maxLineNumber;
    /** "Bytes per line number." */
    uint16_t bytesPerLine;
};

struct CSITX_VirtualChannelConfig_s
{
    /** "Frame count enable." */
    uint32_t frameCountEnable;
    /** "Max number of frames on a given VC." */
    uint16_t maxFrameNumber;
};

struct CSITX_WaitBurstTimeConfig_s
{
    /** "Tx clock exit time".  */
    uint8_t txClockExitTime;
    /** "Wait Burst Time." */
    uint8_t waitBurstTimeCnt;
};

struct CSITX_StreamConfig_s
{
    /** Stream Slave Mode. */
    uint32_t slaveMode;
    /** "Minimum number of packed 32 words loaded into the stream fifo before TX start for a given stream." */
    uint16_t fillLevel;
};

/** CSIRX compatibilty settings. */
struct CSITX_RxCompatibilityConfig_s
{
    /** "RX Compatibility Mode Enable." */
    bool rxCompEnable;
    /** "CSI-2 v1.3 features Enable." */
    bool rxMapping;
};

struct CSITX_EpdConfig_s
{
    /** EPD enable. */
    uint32_t enable;
    /** EPD option. */
    uint32_t option;
    /** "EPD Short Packet Spacers." */
    uint16_t spSpacers;
    /** "EPD Long Packet Spacers." */
    uint16_t lpSpacers;
};

/**
 * "Struct containing function pointers for event notification callbacks issued
 * by isr(). Each call passes the driver's privateData pointer for instance
 * identification if necessary, and may also pass data related to the event."
 */
struct CSITX_Callbacks_s
{
    CSITX_Event event;
};

/** Information about ASF in CSITX controller. */
struct CSITX_AsfInfo_s
{
    /** ASF registers start addresses. */
    volatile uint32_t* regBase;
};

/** "Driver PrivateData" */
struct CSITX_PrivateData_s
{
    /** "The configuration hardcoded inside the device configuration register." */
    CSITX_DeviceConfig deviceConfig;
    /** "Copy of CSITX_Config info supplied to Init API function." */
    CSITX_Config cfg;
    /** "Copy of pointers to callback functions." */
    CSITX_Callbacks cb;
};

/**
 *  @}
 */

#endif  /* CSITX_STRUCTS_IF_H */
 /** @} */
