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

/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_CSIRX CSIRX CSL-FL
 *
 *  @{
 *
 * The CSI2 RX CSL FL provides the APIs to configure CSI2RX module.
 */

#ifndef CSIRX_IF_H
#define CSIRX_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */


/** @defgroup CsirxConfigInfo  CSIRX Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
#define CSIRX_MAX_NUM_OF_STREAMS (0x4U)

/** Magic number value */
#define CSIRX_MAGIC_NUMBER 0x50220200U

/**
 *  @}
 */

/** @defgroup CSIRX DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
* Forward declarations
**********************************************************************/
typedef struct CSIRX_Config_s CSIRX_Config;
typedef struct CSIRX_SysReq_s CSIRX_SysReq;
typedef struct CSIRX_SoftReset_s CSIRX_SoftReset;
typedef struct CSIRX_MonitorIrqs_s CSIRX_MonitorIrqs;
typedef struct CSIRX_MonitorIrqsMaskCfg_s CSIRX_MonitorIrqsMaskCfg;
typedef struct CSIRX_InfoIrqs_s CSIRX_InfoIrqs;
typedef struct CSIRX_InfoIrqsMaskCfg_s CSIRX_InfoIrqsMaskCfg;
typedef struct CSIRX_ErrorIrqs_s CSIRX_ErrorIrqs;
typedef struct CSIRX_ErrorIrqsMaskCfg_s CSIRX_ErrorIrqsMaskCfg;
typedef struct CSIRX_DphyLaneControl_s CSIRX_DphyLaneControl;
typedef struct CSIRX_DphyStatus_s CSIRX_DphyStatus;
typedef struct CSIRX_DphyErrStatusIrq_s CSIRX_DphyErrStatusIrq;
typedef struct CSIRX_DphyErrIrqMaskCfg_s CSIRX_DphyErrIrqMaskCfg;
typedef struct CSIRX_IntegrationDebug_s CSIRX_IntegrationDebug;
typedef struct CSIRX_StreamStatus_s CSIRX_StreamStatus;
typedef struct CSIRX_StreamCtrl_s CSIRX_StreamCtrl;
typedef struct CSIRX_StaticCfg_s CSIRX_StaticCfg;
typedef struct CSIRX_ErrorBypassCfg_s CSIRX_ErrorBypassCfg;
typedef struct CSIRX_ErrorDebug_s CSIRX_ErrorDebug;
typedef struct CSIRX_TestGeneric_s CSIRX_TestGeneric;
typedef struct CSIRX_DeviceConfig_s CSIRX_DeviceConfig;
typedef struct CSIRX_StreamCfg_s CSIRX_StreamCfg;
typedef struct CSIRX_StreamDataCfg_s CSIRX_StreamDataCfg;
typedef struct CSIRX_StreamMonitorCtrl_s CSIRX_StreamMonitorCtrl;
typedef struct CSIRX_StreamMonitorFrame_s CSIRX_StreamMonitorFrame;
typedef struct CSIRX_StreamMonitorLb_s CSIRX_StreamMonitorLb;
typedef struct CSIRX_StreamTimer_s CSIRX_StreamTimer;
typedef struct CSIRX_StreamFccCfg_s CSIRX_StreamFccCfg;
typedef struct CSIRX_StreamFccCtrl_s CSIRX_StreamFccCtrl;
typedef struct CSIRX_StreamFifoFillLvl_s CSIRX_StreamFifoFillLvl;
typedef struct CSIRX_PrivateData_s CSIRX_PrivateData;
typedef struct CSIRX_InterruptsHandlers_s CSIRX_InterruptsHandlers;
typedef struct CSIRX_AsfInfo_s CSIRX_AsfInfo;

/**********************************************************************
* Callbacks
**********************************************************************/
typedef void (*CSIRX_InfoHandler)(CSIRX_PrivateData* pD, CSIRX_InfoIrqs* val);

typedef void (*CSIRX_MonitorHandler)(CSIRX_PrivateData* pD, CSIRX_MonitorIrqs* val);

typedef void (*CSIRX_ErrorHandler)(CSIRX_PrivateData* pD, CSIRX_ErrorIrqs* val);

typedef void (*CSIRX_DphyHandler)(CSIRX_PrivateData* pD, CSIRX_DphyErrStatusIrq* val);

/**
 *  @}
 */

/** @defgroup CsirxDriverFunctionAPI CSIRX Driver Function API
 *  Prototypes for the driver API functions. The user application can link statically to the
 *  necessary API functions and call them directly.
 *  @{
 */

/**********************************************************************
* API methods
**********************************************************************/

/**
 * Get the driver's memory requirements to support the given
 * configuration.
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSIRX_Probe(const CSIRX_Config* config, CSIRX_SysReq* memReq);

/**
 * Initialize the driver. Must be called before all other access APIs.
 * The init function will retain the default value in the hardware.
 * @param[in] pD Memory pointer to the uninitialized private data of the size specified by probe.
 * @param[in] config specifies driver/hardware configuration
 * @param[in] irqs info interrupt handler
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_Init(CSIRX_PrivateData* pD, const CSIRX_Config* config, const CSIRX_InterruptsHandlers* irqs);

/**
 * Driver ISR. Platform-specific code is responsible for ensuring this
 * gets called when the corresponding hardware's interrupt is
 * asserted. The driver's ISR will not attempt to lock any locks, but
 * will perform client callbacks. If the client wishes to defer
 * processing to non-interrupt time, it is responsible for doing so.
 * Should not be called before init.
 * @param[in] pD Pointer to the private data initialized by init
 */
void CSIRX_Isr(CSIRX_PrivateData* pD);

/**
 * getter for DeviceConfig
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDeviceConfig(const CSIRX_PrivateData* pD, CSIRX_DeviceConfig* value);

/**
 * Destructor for the driver.
 */
void CSIRX_Destroy(void);

/**
 * getter for SoftReset
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetSoftReset(const CSIRX_PrivateData* pD, CSIRX_SoftReset* value);

/**
 * setter for SoftReset
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetSoftReset(CSIRX_PrivateData* pD, const CSIRX_SoftReset* value);

/**
 * getter for StaticCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStaticCfg(const CSIRX_PrivateData* pD, CSIRX_StaticCfg* value);

/**
 * setter for StaticCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStaticCfg(CSIRX_PrivateData* pD, const CSIRX_StaticCfg* value);

/**
 * getter for ErrorBypassCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorBypassCfg(const CSIRX_PrivateData* pD, CSIRX_ErrorBypassCfg* value);

/**
 * setter for ErrorBypassCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorBypassCfg(CSIRX_PrivateData* pD, const CSIRX_ErrorBypassCfg* value);

/**
 * getter for InfoIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetInfoIrqsMaskCfg(const CSIRX_PrivateData* pD, CSIRX_InfoIrqsMaskCfg* value);

/**
 * setter for InfoIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetInfoIrqsMaskCfg(CSIRX_PrivateData* pD, const CSIRX_InfoIrqsMaskCfg* value);

/**
 * getter for MonitorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetMonitorIrqsMaskCfg(const CSIRX_PrivateData* pD, CSIRX_MonitorIrqsMaskCfg* value);

/**
 * setter for MonitorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetMonitorIrqsMaskCfg(CSIRX_PrivateData* pD, const CSIRX_MonitorIrqsMaskCfg* value);

/**
 * getter for ErrorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorIrqsMaskCfg(const CSIRX_PrivateData* pD, CSIRX_ErrorIrqsMaskCfg* value);

/**
 * setter for ErrorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorIrqsMaskCfg(CSIRX_PrivateData* pD, const CSIRX_ErrorIrqsMaskCfg* value);

/**
 * getter for DphyErrIrqMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyErrIrqMaskCfg(const CSIRX_PrivateData* pD, CSIRX_DphyErrIrqMaskCfg* value);

/**
 * setter for DphyErrIrqMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyErrIrqMaskCfg(CSIRX_PrivateData* pD, const CSIRX_DphyErrIrqMaskCfg* value);

/**
 * getter for InfoIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetInfoIrqs(const CSIRX_PrivateData* pD, CSIRX_InfoIrqs* value);

/**
 * setter for InfoIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetInfoIrqs(CSIRX_PrivateData* pD, const CSIRX_InfoIrqs* value);

/**
 * getter for MonitorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetMonitorIrqs(const CSIRX_PrivateData* pD, CSIRX_MonitorIrqs* value);

/**
 * setter for MonitorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetMonitorIrqs(CSIRX_PrivateData* pD, const CSIRX_MonitorIrqs* value);

/**
 * getter for ErrorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorIrqs(const CSIRX_PrivateData* pD, CSIRX_ErrorIrqs* value);

/**
 * setter for ErrorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorIrqs(CSIRX_PrivateData* pD, const CSIRX_ErrorIrqs* value);

/**
 * getter for DphyErrStatusIrq
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyErrStatusIrq(const CSIRX_PrivateData* pD, CSIRX_DphyErrStatusIrq* value);

/**
 * setter for DphyErrStatusIrq
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyErrStatusIrq(CSIRX_PrivateData* pD, const CSIRX_DphyErrStatusIrq* value);

/**
 * getter for DphyLaneControl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyLaneControl(const CSIRX_PrivateData* pD, CSIRX_DphyLaneControl* value);

/**
 * setter for DphyLaneControl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyLaneControl(CSIRX_PrivateData* pD, const CSIRX_DphyLaneControl* value);

/**
 * getter for DphyStatus
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyStatus(const CSIRX_PrivateData* pD, CSIRX_DphyStatus* value);

/**
 * getter for IntegrationDebug
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetIntegrationDebug(const CSIRX_PrivateData* pD, CSIRX_IntegrationDebug* value);

/**
 * getter for ErrorDebug
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorDebug(const CSIRX_PrivateData* pD, CSIRX_ErrorDebug* value);

/**
 * getter for testGeneric
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetTestGeneric(const CSIRX_PrivateData* pD, CSIRX_TestGeneric* value);

/**
 * getter for StreamCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamCtrl(const CSIRX_PrivateData* pD, CSIRX_StreamCtrl* value, uint32_t streamNo);

/**
 * setter for StreamCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamCtrl(const CSIRX_PrivateData* pD, const CSIRX_StreamCtrl* value, uint32_t streamNo);

/**
 * getter for StreamStatus
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamStatus(const CSIRX_PrivateData* pD, CSIRX_StreamStatus* value, uint32_t streamNo);

/**
 * getter for StreamCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamCfg(const CSIRX_PrivateData* pD, CSIRX_StreamCfg* value, uint32_t streamNo);

/**
 * setter for StreamCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamCfg(const CSIRX_PrivateData* pD, const CSIRX_StreamCfg* value, uint32_t streamNo);

/**
 * getter for StreamDataCfgl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamDataCfg(const CSIRX_PrivateData* pD, CSIRX_StreamDataCfg* value, uint32_t streamNo);

/**
 * setter for StreamDataCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamDataCfg(const CSIRX_PrivateData* pD, const CSIRX_StreamDataCfg* value, uint32_t streamNo);

/**
 * getter for StreamMonitorCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorCtrl(const CSIRX_PrivateData* pD, CSIRX_StreamMonitorCtrl* value, uint32_t streamNo);

/**
 * setter for StreamMonitorCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamMonitorCtrl(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorCtrl* value, uint32_t streamNo);

/**
 * getter for StreamMonitorFrame
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorFrame(const CSIRX_PrivateData* pD, CSIRX_StreamMonitorFrame* value, uint32_t streamNo);

/**
 * getter for StreamMonitorLb
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorLb(const CSIRX_PrivateData* pD, CSIRX_StreamMonitorLb* value, uint32_t streamNo);

/**
 * setter for StreamMonitorLb
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamMonitorLb(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorLb* value, uint32_t streamNo);

/**
 * getter for StreamTimer
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamTimer(const CSIRX_PrivateData* pD, CSIRX_StreamTimer* value, uint32_t streamNo);

/**
 * setter for StreamTimer
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamTimer(const CSIRX_PrivateData* pD, const CSIRX_StreamTimer* value, uint32_t streamNo);

/**
 * getter for StreamFccCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFccCfg(const CSIRX_PrivateData* pD, CSIRX_StreamFccCfg* value, uint32_t streamNo);

/**
 * setter for StreamFccCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFccCfg(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCfg* value, uint32_t streamNo);

/**
 * getter for StreamFccCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFccCtrl(const CSIRX_PrivateData* pD, CSIRX_StreamFccCtrl* value, uint32_t streamNo);

/**
 * setter for StreamFccCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFccCtrl(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCtrl* value, uint32_t streamNo);

/**
 * getter for StreamFifoFillLvl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFifoFillLvl(const CSIRX_PrivateData* pD, CSIRX_StreamFifoFillLvl* value, uint32_t streamNo);

/**
 * setter for StreamFifoFillLvl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFifoFillLvl(const CSIRX_PrivateData* pD, const CSIRX_StreamFifoFillLvl* value, uint32_t streamNo);

/**
 * Retrieves ASF information from CSIRX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return CDN_EINVAL If pD or asfInfo is NULL.
 * @return CDN_ENOTSUP If ASF is not available.
 * @return CDN_EOK On success.
 */
uint32_t CSIRX_GetAsfInfo(const CSIRX_PrivateData* pD, CSIRX_AsfInfo* asfInfo);

/**
 *  @}
 */

/** @} */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif  /* CSIRX_IF_H */
