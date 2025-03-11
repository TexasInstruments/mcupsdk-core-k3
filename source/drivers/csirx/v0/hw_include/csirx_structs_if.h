/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure" */
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
*          api-generator: 13.00.31660be
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for MIPI CSIRX Controller
**********************************************************************/
#ifndef CSIRX_STRUCTS_IF_H
#define CSIRX_STRUCTS_IF_H


/** @defgroup CSIRX DataStructure Dynamic Data Structures
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
struct CSIRX_Config_s
{
    /** base address of the CSIRX controller registers */
    CSIRX_Regs* regBase;
};

/** System requirements returned by probe */
struct CSIRX_SysReq_s
{
    /** size of memory required for drivers private data */
    uint32_t privDataSize;
};

/**
 * CSI2 Slave Controller Individual Soft Reset for Front and Protocol blocks.
 * Writing to these registers will cause a single cycle pulse to be applied to the
 * soft reset signals.
 * Soft reset must only be applied when the associated clocks are running.
 * These are used to recover from error conditions and should not be required during
 * normal operation.
 */
struct CSIRX_SoftReset_s
{
    /** writing 1'b1 will apply a synchronous soft reset to the protocol module */
    uint8_t protocol;
    /** writing 1'b1 will apply a synchronous soft reset to the Front module */
    uint8_t front;
};

/** Information type Interrupt status (non-error conditions) */
struct CSIRX_MonitorIrqs_s
{
    /** Stream Line count error interrupt */
    uint8_t lineCntErrorIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream Frame mismatch error interrupt */
    uint8_t frameMismatchIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream Frame count error interrupt */
    uint8_t frameCntErrorIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream FCC stop interrupt */
    uint8_t fccStopIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream FCC start interrupt */
    uint8_t fccStartIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream Frame interrupt */
    uint8_t frameIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream Line/byte interrupt */
    uint8_t lbIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream imer interrupt */
    uint8_t timerIrq[CSIRX_MAX_NUM_OF_STREAMS];
};

/**
 * Monitor interrupt mask. Bit addressable mask register in order to independently enable
 * each event to trigger the MonitorIrq line. Only events whose corresponding bit
 * is set to 1 can trigger the interruption line.
 * Hard reset is 0x00000000, i.e. interrupt line disabled
 */
struct CSIRX_MonitorIrqsMaskCfg_s
{
    /** Interrupt mask for stream Line count error. */
    uint8_t lineCntErrorIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream Frame mismatch error. */
    uint8_t frameMismatchIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream Frame count error. */
    uint8_t frameCntErrorIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream FCC stop. */
    uint8_t fccStopIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream FCC start. */
    uint8_t fccStartIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream Frame. */
    uint8_t frameIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for stream Line/byte. */
    uint8_t lbIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask stream imer */
    uint8_t timerIrqm[CSIRX_MAX_NUM_OF_STREAMS];
};

/** Information type Interrupt status (non-error conditions) */
struct CSIRX_InfoIrqs_s
{
    /** Stream Abort process complete. Apply a Soft reset before re-enabling the stream. */
    uint8_t abortIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream Stop process complete. Apply a Soft reset before re-enabling the stream. */
    uint8_t stopIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** A generic short packet has been received. */
    uint8_t spGenericRcvdIrq;
    /** Either clock or any datalane has entered deskew */
    uint8_t deskewEntryIrq;
    /**
     * Bits 7:6 of the ECC byte are non-zero.
     * Indicates non compliance with the MIPI specification although the core will continue to operate as normal.
     */
    uint8_t eccSparesNonzeroIrq;
    /** Wake-up interrupt. */
    uint8_t wakeupIrq;
    /** Sleep interrupt. */
    uint8_t sleepIrq;
    /** Long Packet received by the protocol module */
    uint8_t lpRcvdIrq;
    /** Short Packet received by the protocol module */
    uint8_t spRcvdIrq;
};

/**
 * Information interrupt mask. Bit addressable mask register in order to independently enable
 * each event to trigger the InfoIrq line. Only events whose corresponding bit
 * is set to 1 can trigger the interruption line.
 * Hard reset is 0x00000000, i.e. interrupt line disabled
 */
struct CSIRX_InfoIrqsMaskCfg_s
{
    /** Interrupt mask for stream Abort process. */
    uint8_t abortIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for Stream Stop process complete. */
    uint8_t stopIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt mask for Generic Short Packet received */
    uint8_t spGenericRcvdIrqm;
    /** Interrupt mask for Deskew entry check */
    uint8_t deskewEntryIrqm;
    /** Interrupt mask for ECC spares check */
    uint8_t eccSparesNonzeroIrqm;
    /** Interrupt mask for Wake-up interrupt. */
    uint8_t wakeupIrqm;
    /** Interrupt mask for Sleep interrupt. */
    uint8_t sleepIrqm;
    /** Interrupt mask for Long Packet received flag */
    uint8_t lpRcvdIrqm;
    /** Interrupt mask for Short Packet received */
    uint8_t spRcvdIrqm;
};

/**
 * Datapath error interrupt status.
 * Provides information about data path errors.
 * The host processor can read the interrupt status register to identify the root cause of the event,
 * typically after that the CSIRX_ErrIrq interrupt line is raised
 */
struct CSIRX_ErrorIrqs_s
{
    /** Overflow of the Stream FIFO detected */
    uint8_t fifoOverflowIrq[CSIRX_MAX_NUM_OF_STREAMS];
    /** A reserved or invalid short packet has been received */
    uint8_t spInvalidRcvdIrq;
    /** Invalid access to the configuration register space. */
    uint8_t invalidAccessIrq;
    /** Data ID error has been detected in the header packet */
    uint8_t dataIdIrq;
    /** ECC error has been detected and corrected. */
    uint8_t headerCorrectedEccIrq;
    /** Unrecoverable ECC error has been detected. */
    uint8_t headerEccIrq;
    /** CRC error has been detected. */
    uint8_t payloadCrcIrq;
    /**
     * Overflow detected in resynchronization FIFO between DPHY Lane Management and Protocol blocks.
     * This will occur if SysClk is not fast enough and should be increased since the byte clock
     * frequency is fixed
     */
    uint8_t frontFifoOverflowIrq;
};

/**
 * Datapath error interrupt enable Bits. This register is used to independently enable each event
 * to trigger the ErrIrq interrupt line. Only events whose corresponding enable bit is set to 1
 * can trigger the interrupt line.
 * Hard reset is 0x0000000, i.e. all interrupt lines are disabled
 */
struct CSIRX_ErrorIrqsMaskCfg_s
{
    /**
     * Interrupt enable bit for:
     * StreamFifoOverflow[16] -> Stream 0 overflow
     * StreamFifoOverflow[17] -> Stream 1 overflow
     * StreamFifoOverflow[18] -> Stream 2 overflow
     * StreamFifoOverflow[19] -> Stream 3 overflow
     */
    uint8_t fifoOverflowIrqm[CSIRX_MAX_NUM_OF_STREAMS];
    /** Interrupt enable bit for invalid short packet */
    uint8_t spInvalidRcvdIrqm;
    /** Interrupt enable bit for ErrorIrqsInvalidAccess. */
    uint8_t invalidAccessIrqm;
    /** Interrupt enable bit for ErrorIrqsDataId */
    uint8_t dataIdIrqm;
    /** Interrupt enable bit for ErrorIrqsHeaderCorrectedEcc */
    uint8_t headerCorrectedEccIrqm;
    /** Interrupt enable bit for ErrorIrqsHeaderEcc */
    uint8_t headerEccIrqm;
    /** Interrupt enable bit for ErrorIrqsPayloadCrc */
    uint8_t payloadCrcIrqm;
    /** Interrupt enable bit for ErrorIrqsFrontFifoOverflow */
    uint8_t frontFifoOverflowIrqm;
};

/** DPHY lane control for data and clock lanes enables and resets */
struct CSIRX_DphyLaneControl_s
{
    /** DPHY data lane Enable */
    uint8_t dlEnable[CSIRX_MAX_NUM_OF_STREAMS];
    /** DPHY Clock lane Enable */
    uint8_t clEnable;
    /** DPHY data lane Reset */
    uint8_t dlReset[CSIRX_MAX_NUM_OF_STREAMS];
    /** DPHY Clock lane Reset */
    uint8_t clReset;
};

/** DPHY Clock and Data Lane mode status */
struct CSIRX_DphyStatus_s
{
    /** DPHY Clock lane Stop State */
    uint8_t cl_StopState;
    /** DPHY Clock lane ULPSActiveNot */
    uint8_t cl_ULPSActiveNot;
    /** DPHY Clock lane RxULPSClkNot */
    uint8_t cl_RxULPSClkNot;
    /** DPHY Data lane Stop State */
    uint8_t dlStopState[CSIRX_MAX_NUM_OF_STREAMS];
    /** DPHY Data lane ULPSActiveNot */
    uint8_t dlULPSActiveNot[CSIRX_MAX_NUM_OF_STREAMS];
    /** DPHY Data lane ULPS Esc */
    uint8_t dlRxULPSEsc[CSIRX_MAX_NUM_OF_STREAMS];
};

/** DPHY error interrupt status */
struct CSIRX_DphyErrStatusIrq_s
{
    /** DPHY Data lane ErrSotHS */
    uint8_t dlErrSotHSIrq[CSIRX_MAX_NUM_OF_STREAMS];
};

/** DPHY error interrupt status */
struct CSIRX_DphyErrIrqMaskCfg_s
{
    /** DPHY Data lanes ErrSotHS mask */
    uint8_t dlErrSotHSIrqm[CSIRX_MAX_NUM_OF_STREAMS];
};

/**
 * Used to observe the current data field, extracted by the protocol block from the last
 * short packet data field and FSM state.
 * It also indicates what data type and virtual channels were used for that short packet.
 * This is primarily used during error condition debug.
 * Since the data can come from asynchronous domains the data coherency cannot be relied upon.
 */
struct CSIRX_IntegrationDebug_s
{
    /**
     * CSIRXFsmState
     * 0x0: WAIT_FOR_PACKE
     * 0x1: PAYLOAD_DAA
     * 0x2: PACKET_FOOER_CHECK
     * 0x3: Reserved
     */
    uint8_t protFsmState;
    /** Protocol Virtual Channel */
    uint8_t protVc;
    /** Protocol Datatype */
    uint8_t protDt;
    /** Protocol Word Count (Data Field) */
    uint16_t protWordCount;
};

/**
 * CSI2 Slave Controller Status. Contains useful debug information such as
 * FSM states.
 */
struct CSIRX_StreamStatus_s
{
    /** he Stream is enabled */
    uint8_t running;
    /** Indicates the state of the pushback signal PixelReadyIf for this stream */
    uint8_t readyState;
    /**
     * "Output to Stream FSM states:
     * 0x0: STREAM_IDLE
     * 0x1: STREAM_WAIT_CTRL_DATA Expecting control data next
     * 0x2: STREAM_CTRL Check contents of Ctrl packet and extract header information
     * 0x3: STREAM_DATA Pixel stream pixel data unpacking
     * 0x4: STREAM_DATA_START Assert Hsync
     * 0x5: STREAM_DATA_END De-assert Hysnc
     * 0x6: STREAM_FILL_WAIT  Elastic Buffer cfg - wait until fill level is reached
     * 0x7: STREAM_STOP Stop at the end of Frame - used to set irq
     * 0x8: STREAM_WAIT_CRC Wait until CRC check has completed - Full Line cfg
     * 0x9: STREAM_DATA_PACKED Packed stream data handling
     * 0xA-F : Reserved
     */
    uint8_t streamFsm;
    /**
     * Input to Stream FSM states:
     * 0x0: PRO_IDLE
     * 0x1: PROT_CRL
     * 0x2: PROT_DAA
     * 0x3: Reserved
     */
    uint8_t protocolFsm;
};

/**
 * CSIRX Stream Data output datapath control.
 * Start and Stop commands are independent for each output with the exception of pixel outputs that can never be
 * enabled together. If a pixel output is started while the other is already running,
 * the start command will be ignored. If both pixel outputs are enabled in a single register access,
 * then both start commands are ignored and no pixel output is started.
 */
struct CSIRX_StreamCtrl_s
{
    /** Writing 1'b1 will apply a synchronous soft reset of this stream registers/FIFO */
    uint8_t softRst;
    /**
     * Writing 1 this register will cause the csirx to stop streaming on the corresponding output immediately.
     * This may corrupt the output protocol.
     * StreamAbortIrq is generated on completion of the abort operation.
     */
    uint8_t abrt;
    /**
     * Writing 1 in this register will cause csirx to stop streaming on the corresponding output at
     * the end of the current frame. If the command is issued during frame blanking, then the datapath will
     * immediately stop streaming data on that output.
     * StreamStopIrq is generated on completion of the stop operation.
     */
    uint8_t stop;
    /**
     * Writing 1 in this register enables the corresponding datapath output.
     * It will start streaming data at the start of the next frame that complies with the output configuration.
     * StreamStatus[31] running indicates when data stream is enabled.
     */
    uint8_t start;
};

/**
 * Configuration register to set the physical/logical DPHY lane mapping,
 * the number of lanes being used and external DPHY selection.
 * This register should be set prior to enabling the streams and must not be updated
 * when the stream is running.
 */
struct CSIRX_StaticCfg_s
{
    /** physical mapping of logical data lanes */
    uint8_t dlMap[CSIRX_MAX_NUM_OF_STREAMS];
    /** number of lanes being used */
    uint8_t laneNb;
    /** selection of DPHY used as input of CSIRX module */
    uint8_t sel;
    /** enable CSI ver2.0 support for CSIRX module */
    uint8_t enable2p0Support;
};

/**
 * Error detection event flag configuration.
 * This allows various error conditions to be masked that would normally
 * prevent data being applied to the pixel interface.
 * This applies to ALL streams that are enabled.
 * This register should only be modified while the datapath is disabled.
 * In case this register is modified while the datapath is enabled,
 * the behavior on the current frame is unpredictable.
 * Hard reset value is 0x00000000, meaning all error masking is disabled.
 */
struct CSIRX_ErrorBypassCfg_s
{
    /**
     * Enables Data ID error bypass for stream outputs. When enabled, Data ID errors
     * in packets are signalled as interrupt events, however the data is still passed to the pixel/packed
     * data outputs.  The system must decide to mask of use the pixel data.
     */
    uint8_t dataId;
    /**
     * Enables ECC error bypass for stream outputs. When enabled, CRC errors
     * in packets are signalled as interrupt events, however the data is still passed to the pixel/packed
     * data outputs.  The system must decide to mask of use the pixel data.
     */
    uint8_t ecc;
    /**
     * Enables CRC error bypass for stream outputs. When enabled, CRC errors
     * in packets are signalled as interrupt events, however the data is still passed to the pixel/packed
     * data outputs.  The system must decide to mask of use the pixel data.
     */
    uint8_t crc;
};

/**
 * Error condition debug. After an error is detected by the CSIRX, this register indicates which virtual channel,
 * datatype and data field is impacted.
 */
struct CSIRX_ErrorDebug_s
{
    /** Indicates the Data Field for an invalid CRC/ECC/Data ID */
    uint16_t dataField;
    /** Indicates the Virtual Channel for a invalid CRC/ECC/Data ID */
    uint8_t vc;
    /** Indicates the Data Type for a invalid CRC/ECC/Data ID */
    uint8_t dt;
};

/** Generic test control and status register that controls and reads primary I/O. */
struct CSIRX_TestGeneric_s
{
    /** Test control - Directly controls primary outputs 'testGenericCtrl' */
    uint16_t ctrl;
    /**
     * Test status - Directly reflects, after resynchronisation into the pclk domain, the
     * state of 'testGenericStatus' primary inputs.
     */
    uint16_t status;
};

/**
 * This register provides information related to the current configuration.
 * This should be read by FW to determine the number of streams available and other associated
 * paramters that will influence how the device should be controlled.
 */
struct CSIRX_DeviceConfig_s
{
    /** Pixel Monitor present */
    uint8_t monitorPresent[CSIRX_MAX_NUM_OF_STREAMS];
    /**
     * The width of the pixel interface and the bits per pixel for the selected
     * datatype will determine how many pixels can be output in a single cycle.
     */
    uint8_t numPixels[CSIRX_MAX_NUM_OF_STREAMS];
    /** Stream FIFO Mode. */
    uint8_t fifoMode[CSIRX_MAX_NUM_OF_STREAMS];
    /** Internal Datapath width. */
    uint8_t datapathSize;
    /** Number of Stream interfaces. */
    uint8_t numStreams;
    /** Cadence DPDHY present. */
    uint8_t cdnsPhyPresent;
    /** Max Number of Lanes. */
    uint8_t maxLaneNb;
    /** Extended Virtual Channel Configuration. */
    uint8_t vcxConfig;
    /** Additional Safety Features (ASF). */
    uint8_t asfConfig;
};

/**
 * Primary CSI2 Slave Controller Data pixel outputs configuration.
 * This register is used to configure the output mode.
 * It is also used to set up some Stream FIFO related settings.
 */
struct CSIRX_StreamCfg_s
{
    /**
     * Set the FIFO_FILL_LEVEL which is used to hold data in the FIFO
     * until this level is reached before allow data to be pulled.
     * This setting is only used when FifoMode is set for Large Buffer operation
     */
    uint16_t fifoFill;
    /**
     * Force unpacking of any Data type as selected RAW type.
     * 0 - No bypass
     * 1 - unpack as RAW6
     * 2 - unpack as RAW7
     * 3 - unpack as RAW8
     * 4 - unpack as RAW10
     * 5 - unpack as RAW12
     * 6 - unpack as RAW14
     * 7 - unpack as RAW16
     */
    uint8_t bppBypass;
    /**
     * Stream FIFO configuration, which must be set in accordance to FIFO sizing, flow control and the relationship between the link and pixel interface data rates.
     * Refer to Use Case descriptions for further guidance on FIFO sizing and valid stream configuration options.
     * 00: Full Line Buffer. Hold data in FIFO until CRC check completes.
     * 01: Large Buffer (Fill Level Controlled). Hold data in FIFO until FIFO_FILL_LEVEL is reached.
     * 1x: Short Buffer. When pixel output data rate can match link data rate, a small buffer can be used to accommodate CDC, pixel data packing, and data rate matching
     */
    uint8_t fifoMode;
    /**
     * Number of pixels to output from the stream.
     * Valid values are 1, 2, 4 and 8.
     * The width of the pixel interface and the bits per pixel for the selected
     * datatype will determine how many pixels can be output in a single cycle.
     * Default will be 1 pixel per clock.
     * 00 -> 1 pixel per clock
     * 01 -> 2 pixels per clock
     * 10 -> 4 pixels per clock
     * 11 -> 8 pixels per clock (Reserved)
     */
    uint8_t numPixels;
    /**
     * Enable LS/LE control of HYSNC_VALID output.
     * By default, LS and LE short packets are not required and HYSC_VALID
     * will be generated from the start and end of payload data.
     */
    uint8_t lsLeMode;
    /**
     * Select the output configuration.
     * Pixel = 0 (default)
     * Packed = 1
     */
    uint8_t interfaceMode;
};

/**
 * Secondary CSI2 Slave Controller Data outputs configuration.
 * This register is used to configure the data types and virtual channels
 * are processed and output by this stream.
 */
struct CSIRX_StreamDataCfg_s
{
    /**
     * Enable processing of stream using virtual channel selection;
     * Default '0' -> All Virtual Channels are processed
     */
    uint8_t enableVcSelect;
    /**
     * Selection of Virtual Channels to be processed:
     * Active when stream enable VC bit is active
     * VcSelect0[16]  -> Virtual Channel Select 0 is processed
     * VcSelect1[17]  -> Virtual Channel Select 1 is processed
     * VcSelect2[18]  -> Virtual Channel Select 2 is processed
     * VcSelect3[19]  -> Virtual Channel Select 3 is processed
     * ...
     */
    uint16_t vcSelect;
    /** Enable processing of dt1 */
    uint8_t enableDt1;
    /** Second data type format that this stream will process */
    uint8_t datatypeSelect1;
    /** Enable processing of dt0 */
    uint8_t enableDt0;
    /** First data type format that this stream will process */
    uint8_t datatypeSelect0;
};

/**
 * Stream Monitor configuration.
 * This register is used to configure the CSIRX Monitors:
 * Programmable Frame monitor to trigger an event if a truncated frame is detected,
 * Programmable Timer to trigger an event based on a clock cycle counter after a frame start
 * or frame end,
 * Programmable line/byte counters to trigger an event at a specific byte in a line.
 * This register is used to enable/disable CSIRX programmable interrupt, select the virtual
 * channel for each programmable IT and select the point which will trigger the event.
 * This register should not be modified while the data path is enabled, nor should any of
 * settings be changed when the respective monitor/counter/timer is enabled.
 * In these cases, the behaviour is unpredictable.
 * Hard reset value is 0x00000000, all interrupt generators disabled on Virtual Channel 0.
 */
struct CSIRX_StreamMonitorCtrl_s
{
    /**
     * Indicates the frame length in lines to detect truncated frames.
     * This value must not change while monitor is enabled, i.e. it must only be changed when
     * the FrameMonEn bit is low.
     * 0x0000 means truncated frame detection feature disabled
     */
    uint16_t frameLength;
    /**
     * Enables monitor.
     * This bit must only be set high after the FrameMonVc and FrameLength have been set.
     */
    uint8_t frameMonEn;
    /**
     * Indicates virtual channel for monitor.
     * This value must not change while monitor is enabled, i.e. it must only be changed when
     * the FrameMonEn bit is low.
     */
    uint8_t frameMonVc;
    /**
     * Select the starting point of the timer:
     * 0x0: Start of Frame event on selected virtual channel
     * 0x1: End of Frame event on selected virtual channel.
     * This value must not change while timerEn is enabled
     */
    uint8_t timerEof;
    /**
     * Enables timer based interrupt.
     * This bit must only be set high after the timerEof and timerVc have been set.
     */
    uint8_t timerEn;
    /**
     * Indicates which VC should be used to generate timer based interrupt.
     * This value must not change while timerEn is enabled.
     */
    uint8_t timerVc;
    /**
     * Enables line/byte counter.
     * This bit must only be set high after the LbVc, LineCount and ByteCount have been set.
     */
    uint8_t lbEn;
    /**
     * Indicates which VC should be used to generate line/byte counter interrupt.
     * This value must not change while lbEn is enabled
     */
    uint8_t lbVc;
};

/**
 * Stream Monitor Frame.
 * Used to observe the current frame number and packet size on monitored virtual channels.
 * These values are extracted by the CSIRX from the last frame start short packet data field.
 */
struct CSIRX_StreamMonitorFrame_s
{
    /** Size of the current payload */
    uint16_t packetSize;
    /** Number of the last frame processed. */
    uint16_t nb;
};

/**
 * Stream Monitor Line.
 * Used to specify the byte and line numbers that will generate an interrupt.
 * This register must only be modified when the corresponding line/byte enable is disabled.
 */
struct CSIRX_StreamMonitorLb_s
{
    /**
     * Indicates the line number to generate an interrupt.
     * (First line of a Frame is line number 0)
     */
    uint16_t lineCount;
    /**
     * Indicates the byte number of the line to generate an interrupt.
     * (First byte of a line is byte number 0)
     */
    uint16_t byteCount;
};

/**
 * Stream timer.
 * Used to specify the number of clock cycles until the interrupt is triggered after frame
 * start or frame end.
 * This register must only be modified when the corresponding timer enable is disabled.
 */
struct CSIRX_StreamTimer_s
{
    /** Number of clock cycles */
    uint32_t count;
};

/**
 * Stream Frame Capture Control configuration.
 * Used to specify the frame count value when when the CSIRX must generate interrupts
 * FCC_START and FCC_STOP.
 * This register must only be modified when the corresponding frame count enable is disabled.
 */
struct CSIRX_StreamFccCfg_s
{
    /**
     * Indicates the frame number on which the interrupt should be
     * generated and the stream will stop outputting data on the pixel
     * interface.
     * (0x0000 will be continuous frames.)
     */
    uint16_t frameCountStop;
    /**
     * Indicates the frame number on which the interrupt should be
     * generated and the stream will start outputting data on the pixel
     * interface.
     * (0x0000 will be the current frame.)
     */
    uint16_t frameCountStart;
};

/**
 * Stream Frame Capture Counter control.
 * Used to enable / disable the FCC and specify which virtual channel it
 * should operate on.
 */
struct CSIRX_StreamFccCtrl_s
{
    /** Current Frame number being processed */
    uint16_t frameCounter;
    /**
     * Indicates which VC should be used to generate FCC interrupts.
     * This value must not change while FccEn is enabled
     */
    uint8_t fccVc;
    /** Frame Capture Counter enable. */
    uint8_t fccEn;
};

/**
 * Stream FIFO fill level monitor.  This can operate in 2 modes:
 * 1 - Monitor peak fill level until the stream is stopped.
 * 2 - Monitor peak fill level when the first FIFO read is made during a frame.
 */
struct CSIRX_StreamFifoFillLvl_s
{
    /**
     * 00 -> Fill level detection disabled
     * 01 -> Mode 1
     * 10 -> Mode 2
     * 11 -> Reserved
     */
    uint8_t mode;
    /** Peak fill level of FIFO. */
    uint16_t count;
};

struct CSIRX_PrivateData_s
{
    CSIRX_Regs* regs;
    CSIRX_InfoHandler infoHandler;
    CSIRX_MonitorHandler monitorHandler;
    CSIRX_ErrorHandler errorHandler;
    CSIRX_DphyHandler dphyErrorHandler;
    /** copy of CSIRX_Config info supplied to init */
    CSIRX_Config cfg;
    /** The configuration hardcoded inside the device configuration register. */
    CSIRX_DeviceConfig deviceConfig;
};

/** The structure that contains interrupts handlers */
struct CSIRX_InterruptsHandlers_s
{
    /** info interrupt handler */
    CSIRX_InfoHandler infoHandler;
    /** monitor interrupt handler */
    CSIRX_MonitorHandler monitorHandler;
    /** error interrupt handler */
    CSIRX_ErrorHandler errorHandler;
    /** dphy error interrupt handler */
    CSIRX_DphyHandler dphyHandler;
};

/** Information about ASF in CSIRX controller. */
struct CSIRX_AsfInfo_s
{
    /** ASF registers start addresses. */
    volatile uint32_t* regBase;
};

/**
 *  @}
 */

#endif  /* CSIRX_STRUCTS_IF_H */
