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

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10, DRV-4789" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#ifndef CSITX_SANITY_H
#define CSITX_SANITY_H


uint32_t CSITX_CallbacksSF(const CSITX_Callbacks *obj);
uint32_t CSITX_ConfigSF(const CSITX_Config *obj);
uint32_t CSITX_DataTypeConfigSF(const CSITX_DataTypeConfig *obj);
uint32_t CSITX_DphyConfig1SF(const CSITX_DphyConfig1 *obj);
uint32_t CSITX_DphyConfigSF(const CSITX_DphyConfig *obj);
uint32_t CSITX_EpdConfigSF(const CSITX_EpdConfig *obj);
uint32_t CSITX_PrivateDataSF(const CSITX_PrivateData *obj);
uint32_t CSITX_RxCompatibilityConfigSF(const CSITX_RxCompatibilityConfig *obj);
uint32_t CSITX_StreamConfigSF(const CSITX_StreamConfig *obj);
uint32_t CSITX_VirtualChannelConfigSF(const CSITX_VirtualChannelConfig *obj);
uint32_t CSITX_WaitBurstTimeConfigSF(const CSITX_WaitBurstTimeConfig *obj);

uint32_t CSITX_SanityFunction1(const CSITX_Config* config, const CSITX_SysReq* memReq);
uint32_t CSITX_SanityFunction2(const CSITX_PrivateData* pD, const CSITX_Config* config, const CSITX_Callbacks* callbacks);
uint32_t CSITX_SanityFunction3(const CSITX_PrivateData* pD);
uint32_t CSITX_SanityFunction8(const CSITX_PrivateData* pD, const uint32_t* enable);
uint32_t CSITX_SanityFunction9(const CSITX_PrivateData* pD, const CSITX_DphyConfig* config);
uint32_t CSITX_SanityFunction10(const CSITX_PrivateData* pD, const CSITX_DphyConfig* config);
uint32_t CSITX_SanityFunction11(const CSITX_PrivateData* pD, const CSITX_DphyConfig1* config);
uint32_t CSITX_SanityFunction12(const CSITX_PrivateData* pD, const CSITX_DphyConfig1* config);
uint32_t CSITX_SanityFunction13(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, const CSITX_VcNumber number);
uint32_t CSITX_SanityFunction14(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, const CSITX_VcNumber number);
uint32_t CSITX_SanityFunction15(const CSITX_PrivateData* pD, const CSITX_DataTypeConfig* config, const CSITX_DtNumber number);
uint32_t CSITX_SanityFunction16(const CSITX_PrivateData* pD, const CSITX_DataTypeConfig* config, const CSITX_DtNumber number);
uint32_t CSITX_SanityFunction17(const CSITX_PrivateData* pD, const CSITX_StreamConfig* config, const CSITX_IfNumber number);
uint32_t CSITX_SanityFunction18(const CSITX_PrivateData* pD, const CSITX_StreamConfig* config, const CSITX_IfNumber number);
uint32_t CSITX_SanityFunction20(const CSITX_PrivateData* pD, const bool* enable);
uint32_t CSITX_SanityFunction27(const CSITX_PrivateData* pD, const CSITX_WaitBurstTimeConfig* config);
uint32_t CSITX_SanityFunction28(const CSITX_PrivateData* pD, const CSITX_WaitBurstTimeConfig* config);
uint32_t CSITX_SanityFunction30(const CSITX_PrivateData* pD, const uint16_t* value);
uint32_t CSITX_SanityFunction35(const CSITX_PrivateData* pD, const uint32_t* value, const CSITX_IfNumber number);
uint32_t CSITX_SanityFunction40(const CSITX_PrivateData* pD, const uint16_t* value);
uint32_t CSITX_SanityFunction42(const CSITX_PrivateData* pD, const CSITX_AsfInfo* asfInfo);
uint32_t CSITX_SanityFunction43(const CSITX_PrivateData* pD, const CSITX_DeviceConfig* value);
uint32_t CSITX_SanityFunction44(const CSITX_PrivateData* pD, const CSITX_EpdConfig* config);
uint32_t CSITX_SanityFunction45(const CSITX_PrivateData* pD, const CSITX_EpdConfig* config);
uint32_t CSITX_SanityFunction48(const CSITX_PrivateData* pD, const CSITX_RxCompatibilityConfig* config);
uint32_t CSITX_SanityFunction49(const CSITX_PrivateData* pD, const CSITX_RxCompatibilityConfig* config);

#define CSITX_ProbeSF CSITX_SanityFunction1
#define CSITX_InitSF CSITX_SanityFunction2
#define CSITX_IsrSF CSITX_SanityFunction3
#define CSITX_StartSF CSITX_SanityFunction3
#define CSITX_StopSF CSITX_SanityFunction3
#define CSITX_SetConfigurationModeSF CSITX_SanityFunction3
#define CSITX_GetConfigurationModeSF CSITX_SanityFunction8
#define CSITX_SetDphyConfigSF CSITX_SanityFunction9
#define CSITX_GetDphyConfigSF CSITX_SanityFunction10
#define CSITX_SetDphyConfig1SF CSITX_SanityFunction11
#define CSITX_GetDphyConfig1SF CSITX_SanityFunction12
#define CSITX_SetVirtualChannelConfiSF CSITX_SanityFunction13
#define CSITX_GetVirtualChannelConfiSF CSITX_SanityFunction14
#define CSITX_SetDataTypeConfigSF CSITX_SanityFunction15
#define CSITX_GetDataTypeConfigSF CSITX_SanityFunction16
#define CSITX_SetStreamConfigSF CSITX_SanityFunction17
#define CSITX_GetStreamConfigSF CSITX_SanityFunction18
#define CSITX_SetBypassModeEnableSF CSITX_SanityFunction3
#define CSITX_GetBypassModeEnableSF CSITX_SanityFunction20
#define CSITX_SetSoftResetRequestSF CSITX_SanityFunction3
#define CSITX_GetSoftResetRequestSF CSITX_SanityFunction20
#define CSITX_SetInterruptsEnableSF CSITX_SanityFunction3
#define CSITX_GetInterruptsEnableSF CSITX_SanityFunction20
#define CSITX_GetStatusRegisterSF CSITX_SanityFunction8
#define CSITX_GetDphyStatusRegisterSF CSITX_SanityFunction8
#define CSITX_SetRegWaitBurstTimeSF CSITX_SanityFunction27
#define CSITX_GetRegWaitBurstTimeSF CSITX_SanityFunction28
#define CSITX_SetDphyClkWakeupSF CSITX_SanityFunction3
#define CSITX_GetDphyClkWakeupSF CSITX_SanityFunction30
#define CSITX_SetDphyUlpsWakeupSF CSITX_SanityFunction3
#define CSITX_GetDphyUlpsWakeupSF CSITX_SanityFunction30
#define CSITX_SetDebugEnableSF CSITX_SanityFunction3
#define CSITX_GetDebugEnableSF CSITX_SanityFunction20
#define CSITX_GetDebugProtFsmSF CSITX_SanityFunction35
#define CSITX_GetDebugLnFsmSF CSITX_SanityFunction8
#define CSITX_GetDebugClkLnFsmSF CSITX_SanityFunction8
#define CSITX_GetDebugDataLnFsmSF CSITX_SanityFunction8
#define CSITX_SetTestGenericCtrlSF CSITX_SanityFunction3
#define CSITX_GetTestGenericCtrlSF CSITX_SanityFunction40
#define CSITX_GetTestGenericStatusSF CSITX_SanityFunction40
#define CSITX_GetAsfInfoSF CSITX_SanityFunction42
#define CSITX_GetDeviceConfigSF CSITX_SanityFunction43
#define CSITX_SetEpdConfigSF CSITX_SanityFunction44
#define CSITX_GetEpdConfigSF CSITX_SanityFunction45
#define CSITX_SetScramblerModeSF CSITX_SanityFunction3
#define CSITX_GetScramblerModeSF CSITX_SanityFunction20
#define CSITX_SetRxCompatibilitySF CSITX_SanityFunction48
#define CSITX_GetRxCompatibilitySF CSITX_SanityFunction49

#endif  /* CSITX_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
