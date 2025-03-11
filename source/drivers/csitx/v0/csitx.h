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
 *  \defgroup DRV_CSITX_MODULE CSITX Driver
 *
 *  @{
 *
 * The CSI2 TX module provides the logic to for handling
 * CSI2 protocol based camera sensor or sensor data stream for transmit.
 * This is CSITX FVID2 driver documentation.
 */
/* @} */

/**
 *  \ingroup DRV_CSITX_MODULE
 *  \defgroup CSITX_TOP_LEVEL CSITX Driver Header
 *            This is CSI2 Tx's top level include for applications.
 *
 *  @{
 */

/**
 *  \file csitx.h
 *
 *  \brief CSITX Driver API/interface file.
 *
 *  Requirement: NA
 */

/**
 *  \brief Application API calling sequence:
 *         1. Csitx_init()
 *            - to initialize CSITX Driver
 *         2. Csitx_initParamsInit()
 *            - to initialize initialization parameters
 *         3. Csitx_createParamsInit()
 *            - to initialize create time parameters
 *         4. Csitx_instStatusInit()
 *            - not mandatory
 *            - to initialize driver instance status parameters
 *         5. Fvid2_create()
 *            - to create CSITX driver instance
 *         6. Fvid2_control(FVID2_REGISTER_TIMESTAMP_FXN)
 *            - to register time-stamping function
 *         7. Fvid2_control(IOCTL_CSITX_REGISTER_EVENT)
 *            - mandatory for error handling
 *            - to enable event handling in CSITX driver
 *         8. Fvid2_start()
 *            - to start CSITX driver instance
 *         9. Fvid2_queue() and Fvid2_dequeue()
 *            - to transmit the frames
 *         10. Fvid2_stop()
 *            - to stop CSITX driver instance
 *         11. Fvid2_delete()
 *            - to delete CSITX driver instance
 *         12. Csitx_deInit()
 *            - to un-initialize CSITX Driver
 */

#ifndef CSITX_H_
#define CSITX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/csl_csitx.h>
#include <drivers/fvid2.h>
#include <drivers/csitx/v0/include/csitx_cfg.h>
#include <drivers/csitx/v0/soc/csitx_soc.h>
#include <drivers/csitx/v0/include/csitx_event.h>
#include <drivers/udma.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief CSITX transmit driver ID used at the time of FVID2 create. */
#define CSITX_TX_DRV_ID               (FVID2_CSITX_DRV_BASE + 0x00000000U)

/* transmit IOCTL's */
/**
 *  \brief Get transmit status IOCTL.
 *
 *  This IOCTL can be used to get the transmit status like number of frames
 *  queued/dequeued.
 *  Note: These counters will be reset either at the time of driver create or
 *  while starting the transmit operation. See respective counter comments for
 *  details.
 *
 *  \param cmdArgs       [OUT] Csitx_InstStatus *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_CSITX_GET_INST_STATUS     (FVID2_CSITX_DRV_IOCTL_BASE + 0x0000U)

/**
 *  \brief Print transmit debug logs.
 *
 *  This IOCTL can be used to print the transmit debug logs if enabled through
 *  CSITX_DRV_ENABLE_DEBUG.
 *  Note: These logs will be reset at the time of driver create.
 *
 *  \param cmdArgs       [OUT] NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_CSITX_PRINT_DEBUG_LOGS    (FVID2_CSITX_DRV_IOCTL_BASE + 0x0100U)
/* @} */

/**
 *  \anchor CSITX_ChType
 *  \name   CSITX Channel Type
 *  \brief  Id for CSITX Channel/Stream type.
 *
 *  @{
 */
/** \brief Stream type: transmit mode, frames will transmitted from
  *        internal memory or DDR */
#define CSITX_CH_TYPE_TX                          ((uint32_t) 0x0U)
/** \brief Stream type: Color Bar mode,
  *        Pre-defined color bar pattern is sent out through CSI interface */
#define CSITX_CH_TYPE_COLORBAR                    ((uint32_t) 0x1U)
/** \brief Stream type: Loopback mode,
  *        frames are accepted through CSI Tx trans PADs and will sent out */
#define CSITX_CH_TYPE_LPBK                        ((uint32_t) 0x2U)
/* @} */

/** \brief Buffer memory alignment with cache line size. */
#define CSITX_BUF_ALIGNMENT                       (UDMA_CACHELINE_ALIGNMENT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing Channels configurations.
 */
typedef struct
{
    uint32_t chId;
    /**< Channel ID.
     *   It should be unique and start with '0' and continue without any gaps.
     *   It should be less than 'CSITX_NUM_CH'. */
    uint32_t chType;
    /**< Channel type
     *   See \ref CSITX_ChType for details. */
    uint32_t vcNum;
    /**< Specify the virtual channel number to be used.
     *   Valid rage 0 - 3 when v2p0 support is disabled and
     *   0 - 15 when v2p0 support is enabled */
    uint32_t outCsiDataType;
    /**< Data Type as per \ref FVID2_CSI2DF */
    Fvid2_Format inFmt;
    /**< Specify the characteristics of streams that has to be sent out.
     *   Output format described using FVID2 frame format #Fvid2_Format
     *      Valid member of this structure are
     *      <b>width</b>:<br>
     *      Input width, in pixels.
     *      WARNING - Sufficient buffer should be allocated to
     *      accommodate max line length.
     *      For CSITX_CH_TYPE_COLORBAR channel,
     *      it should be in units of pixel pairs<br>
     *
     *      <b>height</b>:<br>
     *      Expected number of lines, 0x0 for unknown
     *      WARNING - Sufficient buffer should be allocated to
     *      accommodate max lines.<br>
     *
     *      <b>pitch</b>:<br>
     *      Pitch in bytes between two lines.<br>
     *
     *      <b>dataFormat</b>:<br>
     *      Output Data format, valid options are:<br>
     *      FVID2_DF_YUV422I_UYVY<br>
     *      FVID2_DF_YUV422I_YUYV<br>
     *      FVID2_DF_YUV422I_YVYU<br>
     *      FVID2_DF_YUV422I_VYUY<br>
     *
     *      <b>ccsFormat</b>:<br>
     *      Valid values are :''
     *      FVID2_CCSF_BITS12_PACKED<br>
     *      FVID2_CCSF_BITS12_UNPACKED16<br>
     *      This valid only when outCsiDataType is 'CSI2_DATA_FORMAT_RAW12' and
     *      when chType is CSITX_CH_TYPE_TX.
     *
     *      <b>Unused Parameters</b>:<br>
     *      .bpp    - unused parameter for CSI2TX<br>
     *      For OTF mode, following parameters are not used:
     *      .bpp, .pitch<br>
     *      For loop-back mode, only .dataFormat is used. Rest of the
     *      parameters are unused.<br> */
    uint32_t vBlank;
    /**< Vertical blanking in terms of number of line. */
    uint32_t hBlank;
    /**< Horizontal blanking in terms of number of pixels */
    uint32_t startDelayPeriod;
    /**< Delay in terms of micro-seconds before sending
     *   first line after enabling.
     *   Note: This is only applicable if chType is CSITX_CH_TYPE_COLORBAR. */
    Udma_ChTxPrms txChParams;
    /**< UDMA Tx channel configuration parameters */
    uint8_t ringOrderId;
    /**<  Ring bus order ID value to be programmed into the orderid field of
     *    the ring's RING_ORDERID register. */
} Csitx_ChCfg;

/**
 *  \brief Structure containing csitx module initialization arguments
 */
typedef struct
{
    uint32_t rxCompEnable;
    /**< Enable RX compatibility mode
     *   0: Disable RX compatibility mode.
     *   1: Enable RX compatibility mode.
     *   For J721S2, it is programmed as '1' irrespective of any value passed
     *   for this parameter.
     */
    uint32_t rxv1p3MapEnable;
    /**< Enable TX controller to use pixel mappings for 8-bit data types
     *   which match that of the CSI-2 RX v1.3 Controller
     *   0: Disable RX v1p3 mapping.
     *   1: Enable RX v1p3 mapping.
     */
    uint32_t numDataLanes;
    /**< Number of data to be used for receiving data */
    uint32_t lanePolarityCtrl[(CSITX_TX_DATA_LANES_MAX + CSITX_TX_CLK_LANES_MAX)];
    /**< Invert control for differential pair of DPHY
     *   0: Default mapping.
     *   1: Invert P and N pair of the differential signals.
     *   dlMap[0U]: Invert control for clock lane
     *   dlMap[1U]: Invert control for data lane 1
     *   dlMap[2U]: Invert control for data lane 2
     *   dlMap[3U]: Invert control for data lane 3
     *   dlMap[4U]: Invert control for data lane 4
     *   Note: This feature is currently not supported.
     */
    uint32_t enableFrameRepeat;
    /**< Enable frame repeat control.
     *   0: Disable Frame Repeat
     *   1: Enable Frame Repeat
     *   Last frame is repeated (and will not be returned to the application)
     *   until new frame is queued for transmission.
     *   Enable this feature for remote device which expects frames at
     *   regular intervals like display. */
    Csitx_DPhyCfg dphyCfg;
    /**< CSITX D-PHY configurations. */
    uint32_t eventGrpNum;
    /**< CSITX number of event groups to register  */
    Csitx_EventPrms eventParams[CSITX_EVENT_GROUP_MAX];
    /**< CSITX event configurations parameter. */
    uint32_t lpbkCsiRxInst;
    /*< Input CSIRX instance for the loopback stream */
    CSL_CsitxRetransCfg retransCfg;
    /*< Retransmission stream configurations */
} Csitx_InstCfg;

/**
 *  \brief Capture driver create arguments, used when calling Fvid2_create().
 *         Structure containing Streams configurations.
 */
typedef struct
{
    uint32_t        numCh;
    /**< Number of channels to be configured/processed
     *   It should be less that 'CSITX_NUM_CH'. */
    Csitx_ChCfg     chCfg[CSITX_NUM_CH];
    /**< Configuration for channels to be processed */
    Csitx_InstCfg   instCfg;
    /**< CSI Tx module configuration.
      *  See \ref Csitx_InstCfg for details */
} Csitx_CreateParams;

/**
 *  \brief Capture driver create arguments, used when calling Fvid2_create().
 *         Structure containing Streams configurations.
 */
typedef struct
{
    Udma_DrvHandle  drvHandle;
    /**< UDMA Driver handle */
} Csitx_InitParams;

/**
 *  \brief Capture driver create status. Returned after calling Fvid2_create().
 */
typedef struct
{
    int32_t retVal;
    /**< Create status, FVID2_SOK on success, else failure. */
} Csitx_CreateStatus;

/**
 *  \brief Capture status structure used to get the current status.
 */
typedef struct
{
    uint32_t queueCount[CSITX_NUM_CH];
    /**< Counter to keep track of how many requests are queued to the
     *   driver.
     *   Note: This counter will be reset at the time of driver init. */
    uint32_t dequeueCount[CSITX_NUM_CH];
    /**< Counter to keep track of how many requests are dequeued from the
     *   driver.
     *   Note: This counter will be reset at the time of driver init. */
     uint32_t frmRepeatCount[CSITX_NUM_CH];
    /**< Counter to keep track of how many frames are repeated from the
     *   driver when no buffers are queued by the application.
     *   Note: This counter will be reset at the time of driver init. */
    uint32_t overflowCount;
    /**< Counter to keep track of the occurrence of overflow error.
     *   Note: This counter will be reset at the time of driver create and
     *   during driver start. */
    uint32_t frameStartCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many frame start events occured*/
    uint32_t frameEndCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many frame end events occured*/
    uint32_t fifoUnderflowCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many fifo underflow events occured*/
    uint32_t dataFlowErrCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many data flow error events occured*/
    uint32_t byteCountMismatchCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many byte count mismatch events occured*/
    uint32_t lineNumerrorCount[CSITX_NUM_PIXEL_IF];
    /* *<Counter to keep track of how many line number error events occured*/
} Csitx_InstStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief CSITX Driver Init function.
 *
 *  \param initParams       [IN] Pointer to #Csitx_InitParams structure.
 *
 *  \return status CSITX Initialization status. 'FVID2_SOK' is successful.
 */
int32_t Csitx_init(const Csitx_InitParams *initParams);

/**
 *  \brief CSITX Driver de-Init function.
 *
 *  \return status CSITX Initialization status. 'FVID2_SOK' is successful.
 */
int32_t Csitx_deInit(void);

/**
 *  \brief Csitx_InitParams structure init function.
 *
 *  \param initPrms         [IN] Pointer to #Csitx_InitParams structure.
 *
 */
void Csitx_initParamsInit(Csitx_InitParams *initPrms);

/**
 *  \brief Csitx_CreateParams structure init function.
 *
 *  \param createPrms   [IN] Pointer to #Csitx_CreateParams structure.
 *
 *  Note: If given 'createPrms.instCfg.dphyCfg.laneBandSpeed' does no match with pre-defined
 *        configurations, this API will default the DPHY parameters for 800 Mbps.
*         Application should change the lane speed (if needed) prior to calling
 *        'Fvid2_create()'.
 *        Pre-defined configurations are supported for following lane-speeds:
 *        1. CSITX_LANE_BAND_SPEED_770_TO_870_MBPS
 *        2. CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS
 *        3. CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS
 *        4. CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS
 */
void Csitx_createParamsInit(Csitx_CreateParams *createPrms);

/**
 *  \brief Csitx_ChCfg structure init function.
 *
 *  \param chCfg            [IN] Pointer to #Csitx_ChCfg structure.
 *
 */
void Csitx_chCfgInit(Csitx_ChCfg *chCfg);

/**
 *  \brief Csitx_InstCfg structure init function.
 *
 *  \param instCfg          [IN] Pointer to #Csitx_InstCfg structure.
 *
 */
void Csitx_instCfgInit(Csitx_InstCfg *instCfg);

/**
 *  \brief Csitx_InstStatus structure init function.
 *
 *  \param status           [IN] Pointer to #Csitx_InstStatus structure.
 *
 */
void Csitx_instStatusInit(Csitx_InstStatus *status);

/* ========================================================================== */
/*                         Function Definitions                               */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_H_ */
/* @} */
