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

#ifndef CSITX_IF_H
#define CSITX_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */


/** @defgroup CsitxConfigInfo  CSITX Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/**
 * Bytes per pixel values for the supported pixel formats
 * @details YUV420 8-bit (legacy)
 */
#define CSITX_BPP_YUV_420_8_LEGACY (1.5)

/** @details YUV420 8-bit */
#define CSITX_BPP_YUV_420_8 (1U)

/** @details YUV420 10-bit */
#define CSITX_BPP_YUV_420_10 (1.25)

/** @details YUV422 8-bit */
#define CSITX_BPP_YUV422_8 (2U)

/** @details YUV422 10-bit */
#define CSITX_BPP_YUV422_10 (2.5)

/** @details RGB888 */
#define CSITX_BPP_RGB888 (3U)

/** @details RGB666 */
#define CSITX_BPP_RGB666 (2.25)

/** @details RGB565 */
#define CSITX_BPP_RGB565 (2U)

/** @details RGB555 */
#define CSITX_BPP_RGB555 (2U)

/** @details RGB444 */
#define CSITX_BPP_RGB444 (2U)

/** Magic number value */
#define CSITX_MAGIC_NUMBER 0x50250300U

/**
 *  @}
 */

/** @defgroup CsitxDataStructure CSITX Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
* Forward declarations
**********************************************************************/
typedef struct CSITX_Config_s CSITX_Config;
typedef struct CSITX_DeviceConfig_s CSITX_DeviceConfig;
typedef struct CSITX_SysReq_s CSITX_SysReq;
typedef struct CSITX_DphyConfig1_s CSITX_DphyConfig1;
typedef struct CSITX_DphyConfig_s CSITX_DphyConfig;
typedef struct CSITX_DataTypeConfig_s CSITX_DataTypeConfig;
typedef struct CSITX_VirtualChannelConfig_s CSITX_VirtualChannelConfig;
typedef struct CSITX_WaitBurstTimeConfig_s CSITX_WaitBurstTimeConfig;
typedef struct CSITX_StreamConfig_s CSITX_StreamConfig;
typedef struct CSITX_RxCompatibilityConfig_s CSITX_RxCompatibilityConfig;
typedef struct CSITX_EpdConfig_s CSITX_EpdConfig;
typedef struct CSITX_Callbacks_s CSITX_Callbacks;
typedef struct CSITX_AsfInfo_s CSITX_AsfInfo;

typedef struct CSITX_PrivateData_s CSITX_PrivateData;

/**********************************************************************
* Enumerations
**********************************************************************/
/** DPHY Data Lanes */
typedef enum
{
    /** Lane Number 0 */
    CSITX_DPHY_LANE_0 = 0x1U,
    /** Lane Number 1 */
    CSITX_DPHY_LANE_1 = 0x2U,
    /** Lane Number 2 */
    CSITX_DPHY_LANE_2 = 0x4U,
    /** Lane Number 3 */
    CSITX_DPHY_LANE_3 = 0x8U
} CSITX_DataLane;

/** DPHY modes */
typedef enum
{
    /** Ultra Low Power Mode */
    CSITX_DPHY_ULP_MODE = 0x0U,
    /** High Speed Transmission Mode */
    CSITX_DPHY_HS_MODE = 0x1U,
    /** Stop Mode */
    CSITX_DPHY_STOP_MODE = 0x2U
} CSITX_DphyMode;

/** DPHY Clock modes */
typedef enum
{
    /** Continuous */
    CSITX_DPHY_CLOCK_CONT = 0x0U,
    /** Non Continuous */
    CSITX_DPHY_CLOCK_NON_CONT = 0x1U
} CSITX_DphyClockMode;

/** Pixel interface number */
typedef enum
{
    CSITX_PIXEL_IF0 = 0U,
    CSITX_PIXEL_IF1 = 1U,
    CSITX_PIXEL_IF2 = 2U,
    CSITX_PIXEL_IF3 = 3U
} CSITX_IfNumber;

/** Virtual Channel number */
typedef enum
{
    CSITX_VC0 = 0U,
    CSITX_VC1 = 1U,
    CSITX_VC2 = 2U,
    CSITX_VC3 = 3U,
    CSITX_VC4 = 4U,
    CSITX_VC5 = 5U,
    CSITX_VC6 = 6U,
    CSITX_VC7 = 7U,
    CSITX_VC8 = 8U,
    CSITX_VC9 = 9U,
    CSITX_VC10 = 10U,
    CSITX_VC11 = 11U,
    CSITX_VC12 = 12U,
    CSITX_VC13 = 13U,
    CSITX_VC14 = 14U,
    CSITX_VC15 = 15U
} CSITX_VcNumber;

/** Data Type number */
typedef enum
{
    CSITX_DT0 = 0U,
    CSITX_DT1 = 1U,
    CSITX_DT2 = 2U,
    CSITX_DT3 = 3U,
    CSITX_DT4 = 4U,
    CSITX_DT5 = 5U,
    CSITX_DT6 = 6U,
    CSITX_DT7 = 7U,
    CSITX_DT8 = 8U,
    CSITX_DT9 = 9U,
    CSITX_DT10 = 10U,
    CSITX_DT11 = 11U,
    CSITX_DT12 = 12U,
    CSITX_DT13 = 13U,
    CSITX_DT14 = 14U,
    CSITX_DT15 = 15U
} CSITX_DtNumber;

/**
 * Data format codes. Note that these enums also include
 * extended data type bit information. Some structures
 * may keep this information using separates fields.
 * See 'CSITX_DataTypeConfig'.
 */
typedef enum
{
    /** Format YUV_420_8_LEGACY */
    CSITX_DFC_YUV_420_8_LEGACY = 0x1AU,
    /** Format YUV_420_8 */
    CSITX_DFC_YUV_420_8 = 0x18U,
    /** Format YUV_420_10 */
    CSITX_DFC_YUV_420_10 = 0x19U,
    /** Format YUV_420_8_CSPS */
    CSITX_DFC_YUV_420_8_CSPS = 0x1CU,
    /** Format YUV_420_10_CSPS */
    CSITX_DFC_YUV_420_10_CSPS = 0x1DU,
    /** Format YUV422_8 */
    CSITX_DFC_YUV422_8 = 0x1EU,
    /** Format PACKED_YUV422_8 */
    CSITX_DFC_PACKED_YUV422_8 = 0x5EU,
    /** Format YUV422_10 */
    CSITX_DFC_YUV422_10 = 0x1FU,
    /** Format RGB888 */
    CSITX_DFC_RGB888 = 0x24U,
    /** Format RGB666 */
    CSITX_DFC_RGB666 = 0x23U,
    /** Format RGB565 */
    CSITX_DFC_RGB565 = 0x22U,
    /** Format RGB555 */
    CSITX_DFC_RGB555 = 0x21U,
    /** Format RGB444 */
    CSITX_DFC_RGB444 = 0x20U,
    /** Format RAW6 */
    CSITX_DFC_RAW6 = 0x28U,
    /** Format RAW7 */
    CSITX_DFC_RAW7 = 0x29U,
    /** Format DFC_RAW8 */
    CSITX_DFC_RAW8 = 0x2AU,
    /** Format RAW8_DUAL_PIXEL */
    CSITX_DFC_RAW8_DUAL_PIXEL = 0x6AU,
    /** Format RAW10 */
    CSITX_DFC_RAW10 = 0x2BU,
    /** Format RAW12 */
    CSITX_DFC_RAW12 = 0x2CU,
    /** Format RAW14 */
    CSITX_DFC_RAW14 = 0x2DU,
    /** Format GENERIC_8BIT_NULL */
    CSITX_DFC_GENERIC_8BIT_NULL = 0x10U,
    /** Format GENERIC_8BIT_BLANKING */
    CSITX_DFC_GENERIC_8BIT_BLANKING = 0x11U,
    /** Format GENERIC_8BIT_EMBED */
    CSITX_DFC_GENERIC_8BIT_EMBED = 0x12U,
    /** Format USER_DEFINED */
    CSITX_DFC_USER_DEFINED = 0x30U
} CSITX_DataFormatCode;

/**********************************************************************
* Callbacks
**********************************************************************/
/** Reports CSITX interrupts. The irq_event - indicates interrupt events from CSI2TX. The dphy_event - indicates dphy interrupt events from CSI2TX. */
typedef void (*CSITX_Event)(CSITX_PrivateData* pD, uint32_t irq_event, uint32_t dphy_event);

/**
 *  @}
 */

/** @defgroup CsitxDriverFunctionAPI CSITX Driver Function API
 *  Prototypes for the driver API functions. The user application can link statically to the
 *  necessary API functions and call them directly.
 *  @{
 */

/**********************************************************************
* API methods
**********************************************************************/

/**
 * "Get the driver's memory requirements to support the given
 * configuration."
 * @param[in] config "Driver/hardware configuration required."
 * @param[out] memReq "Size of the memory allocation required."
 * @return CDN_EOK on success (requirements struct filled).
 * @return CDN_ENOTSUP if magic number does not match.
 * @return CDN_EINVAL if config or memReq is NULL.
 */
uint32_t CSITX_Probe(const CSITX_Config* config, CSITX_SysReq* memReq);

/**
 * "Initialise the driver instance and state, configure the CSITX as
 * specified in the 'config' settings. The function enables the
 * datapath."
 * @param[in] pD "Driver state info specific to this instance."
 * @param[in] config "Specifies driver/hardware configuration."
 * @param[in] callbacks "Client-supplied callback functions."
 * @return CDN_EOK on success.
 * @return CDN_EINVAL if illegal/inconsistent values in 'config' does not support feature(s) required by 'config' parameters.
 */
uint32_t CSITX_Init(CSITX_PrivateData* pD, const CSITX_Config* config, const CSITX_Callbacks* callbacks);

/**
 * "Driver ISR. Platform-specific code is responsible for ensuring
 * this gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so."
 * @param[in] pD "Driver instance data filled by Init."
 */
void CSITX_Isr(CSITX_PrivateData* pD);

/**
 * "Start the CSITX driver, enabling interrupts. This is called after
 * the client has successfully initialized the driver and hooked the
 * driver's ISR (the isr member of this struct) to the IRQ."
 * @param[in] pD "Driver state info specific to this instance."
 */
void CSITX_Start(CSITX_PrivateData* pD);

/**
 * "Stop the CSITX driver, disabling interrupts."
 * @param[in] pD "Driver state info specific to this instance."
 */
void CSITX_Stop(CSITX_PrivateData* pD);

/**
 * "Destructor for the driver."
 */
void CSITX_Destroy(void);

/**
 * "Enables or disables Configuration Request."
 * @param[in] pD "Driver instance data."
 * @param[in] enable "True to enable Configuration Request, false to disable".
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetConfigurationMode(CSITX_PrivateData* pD, uint32_t enable);

/**
 * "Gets value of the Configuration request."
 * @param[in] pD "Driver instance data."
 * @param[out] enable "'configuration_request' bit from the CONFIG register is tested. If enable Configuration Request is enabled, false otherwise."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetConfigurationMode(CSITX_PrivateData* pD, uint32_t* enable);

/**
 * "Performs D-PHY configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config "Configuration to apply to D-PHY."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetDphyConfig(CSITX_PrivateData* pD, const CSITX_DphyConfig* config);

/**
 * "Reads the D-PHY configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY config."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyConfig(CSITX_PrivateData* pD, CSITX_DphyConfig* config);

/**
 * "Performs D-PHY configuration (DPHY CFG1)."
 * @param[in] pD "Driver instance data."
 * @param[in] config "Configuration to apply to DPHY CFG1."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetDphyConfig1(CSITX_PrivateData* pD, const CSITX_DphyConfig1* config);

/**
 * "Reads DPHY configuration (DPHY CFG1)."
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY CFG1 config."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetDphyConfig1(CSITX_PrivateData* pD, CSITX_DphyConfig1* config);

/**
 * "Writes a virtual channel configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config "Virtual channel configuration."
 * @param[in] number Number of the Virtual channel to configure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetVirtualChannelConfig(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, CSITX_VcNumber number);

/**
 * "Reads a virtual channel configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config "Virtual channel configuration."
 * @param[in] number Number of the virtual channel
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetVirtualChannelConfig(const CSITX_PrivateData* pD, CSITX_VirtualChannelConfig* config, CSITX_VcNumber number);

/**
 * "Writes a data type configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config "Data type configuration."
 * @param[in] number Number of the Data type to configure.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetDataTypeConfig(const CSITX_PrivateData* pD, const CSITX_DataTypeConfig* config, CSITX_DtNumber number);

/**
 * "Reads a data type configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config "Data type configuration."
 * @param[in] number Number of the data type
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetDataTypeConfig(const CSITX_PrivateData* pD, CSITX_DataTypeConfig* config, CSITX_DtNumber number);

/**
 * "Writes a stream configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config "Stream configuration."
 * @param[in] number Pixel interface number.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetStreamConfig(const CSITX_PrivateData* pD, const CSITX_StreamConfig* config, CSITX_IfNumber number);

/**
 * "Reads a stream configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config "Stream configuration."
 * @param[in] number Pixel interface number.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetStreamConfig(const CSITX_PrivateData* pD, CSITX_StreamConfig* config, CSITX_IfNumber number);

/**
 * "Enables or disables Bypass Mode request."
 * @param[in] pD "Driver instance data."
 * @param[in] enable True to enable Bypass mode, false to disable.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetBypassModeEnable(CSITX_PrivateData* pD, bool enable);

/**
 * "Gets value of the Bypass Mode Enable request."
 * @param[in] pD "Driver instance data."
 * @param[out] enable "'bypass_mode_enable' bit from the CONFIG register is tested. If enable Bypass Mode Enable is enabled, false otherwise."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetBypassModeEnable(CSITX_PrivateData* pD, bool* enable);

/**
 * "Enables or disables soft reset request."
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable soft reset request false to disable.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetSoftResetRequest(CSITX_PrivateData* pD, bool enable);

/**
 * "Gets value of the soft reset request."
 * @param[in] pD Driver instance data
 * @param[out] enable "'soft_reset_request' bit from the CONFIG register is tested. If enable soft reset request is enabled, false otherwise."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetSoftResetRequest(CSITX_PrivateData* pD, bool* enable);

/**
 * "Enables or disables interrupts. Note that in order to generate
 * interrupts the IRQ_MASK register must be configured first. If in
 * the driver initialization stage the 'CSITX_Config.enableInterrupts
 * = true', then the IRQ_MASK is configured that all interrupts are
 * generated."
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable interrupts, false to disable.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetInterruptsEnable(CSITX_PrivateData* pD, bool enable);

/**
 * "Gets value of the interrupts."
 * @param[in] pD "Driver instance data."
 * @param[out] enable "'irq_enable' bit from the CONFIG register If true interrupts are enabled, false otherwise."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetInterruptsEnable(CSITX_PrivateData* pD, bool* enable);

/**
 * "Reads Status register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the STATUS register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetStatusRegister(CSITX_PrivateData* pD, uint32_t* value);

/**
 * "Reads D-PHY Status register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DPHY_STATUS register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyStatusRegister(CSITX_PrivateData* pD, uint32_t* value);

/**
 * "Writes DPHY Wait Time Configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config DPHY Wait Time Configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetRegWaitBurstTime(CSITX_PrivateData* pD, CSITX_WaitBurstTimeConfig* config);

/**
 * "Reads DPHY Wait Time Configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config "DPHY Wait Time Configuration."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetRegWaitBurstTime(CSITX_PrivateData* pD, CSITX_WaitBurstTimeConfig* config);

/**
 * "Writes DPHY_CLK_WAKEUP register with value."
 * @param[in] pD "Driver instance data."
 * @param[in] value Value to write to the DPHY_CLK_WAKEUP register.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyClkWakeup(CSITX_PrivateData* pD, uint16_t value);

/**
 * "Reads DPHY_CLK_WAKEUP register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DPHY_CLK_WAKEUP register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyClkWakeup(CSITX_PrivateData* pD, uint16_t* value);

/**
 * "Writes DPHY_ULPS_WAKEUP register with value."
 * @param[in] pD "Driver instance data."
 * @param[in] value Value to write to the DPHY_ULPS_WAKEUP register.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyUlpsWakeup(CSITX_PrivateData* pD, uint16_t value);

/**
 * "Reads DPHY_ULPS_WAKEUP register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DPHY_ULPS_WAKEUP register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyUlpsWakeup(CSITX_PrivateData* pD, uint16_t* value);

/**
 * "Enables or disables CSITX debugging functionality."
 * @param[in] pD "Driver instance data."
 * @param[in] enable "True to enable debugging functionality, false to disable."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDebugEnable(CSITX_PrivateData* pD, bool enable);

/**
 * "Reads status of the core debug functionality."
 * @param[in] pD "Driver instance data."
 * @param[out] enable "True if the the core debug functionality is enabled false otherwise."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugEnable(CSITX_PrivateData* pD, bool* enable);

/**
 * "Reads debug register for a given Pixel pixel interface."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DEBUG_PROT_FSM register."
 * @param[in] number Number of the Pixel interface.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugProtFsm(CSITX_PrivateData* pD, uint32_t* value, CSITX_IfNumber number);

/**
 * "Reads DEBUG_LN_FSM register register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DEBUG_LN_FSM register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugLnFsm(CSITX_PrivateData* pD, uint32_t* value);

/**
 * "Reads DEBUG_CLK_LN_FSM register register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DEBUG_CLK_LN_FSM register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugClkLnFsm(CSITX_PrivateData* pD, uint32_t* value);

/**
 * "Reads DEBUG_DATA_LN_FSM register register value."
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the DEBUG_DATA_LN_FSM register."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugDataLnFsm(CSITX_PrivateData* pD, uint32_t* value);

/**
 * "Sets test_generic_ctrl field of the GENERIC Register."
 * @param[in] pD "Driver instance data."
 * @param[in] value "Test generic_ctrl value."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetTestGenericCtrl(CSITX_PrivateData* pD, uint16_t value);

/**
 * "Gets test_generic_ctrl field of the GENERIC Register."
 * @param[in] pD "Driver instance data."
 * @param[out] value "D-PHY config."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetTestGenericCtrl(CSITX_PrivateData* pD, uint16_t* value);

/**
 * "Reads test_generic_status field of the GENERIC register"
 * @param[in] pD "Driver instance data."
 * @param[out] value "Contents of the test_generic_status field".
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetTestGenericStatus(CSITX_PrivateData* pD, uint16_t* value);

/**
 * Retrieves ASF information from CSITX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return CDN_EINVAL If pD or asfInfo is NULL.
 * @return CDN_EOK On success.
 */
uint32_t CSITX_GetAsfInfo(const CSITX_PrivateData* pD, CSITX_AsfInfo* asfInfo);

/**
 * "Getter for DeviceConfig."
 * @param[in] pD "Pointer to the private data initialized by init".
 * @param[out] value "Output value."
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSITX_GetDeviceConfig(const CSITX_PrivateData* pD, CSITX_DeviceConfig* value);

/**
 * "Writes EPD configuration."
 * @param[in] pD "Driver instance data."
 * @param[in] config EPD configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointers
 */
uint32_t CSITX_SetEpdConfig(CSITX_PrivateData* pD, const CSITX_EpdConfig* config);

/**
 * "Reads EPD configuration."
 * @param[in] pD "Driver instance data."
 * @param[out] config EPD configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointers
 */
uint32_t CSITX_GetEpdConfig(CSITX_PrivateData* pD, CSITX_EpdConfig* config);

/**
 * "Enables or disables Scrambler mode."
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable scrambler mode, false to disable.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetScramblerMode(CSITX_PrivateData* pD, bool enable);

/**
 * "Gets value of the scrambler mode."
 * @param[in] pD Driver instance data
 * @param[out] enable "Scrambler mode status."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetScramblerMode(CSITX_PrivateData* pD, bool* enable);

/**
 * "Set CSIRX compatibility features."
 * @param[in] pD Driver instance data
 * @param[in] config CSIRX compatibility configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetRxCompatibility(CSITX_PrivateData* pD, CSITX_RxCompatibilityConfig* config);

/**
 * "Get CSIRX compatibility features."
 * @param[in] pD Driver instance data
 * @param[out] config CSIRX compatibility configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetRxCompatibility(CSITX_PrivateData* pD, CSITX_RxCompatibilityConfig* config);

/**
 *  @}
 */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif  /* CSITX_IF_H */
 /** @} */
