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

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#ifndef CSIRX_SANITY_H
#define CSIRX_SANITY_H


uint32_t CSIRX_ConfigSF(const CSIRX_Config *obj);
uint32_t CSIRX_DphyErrIrqMaskCfgSF(const CSIRX_DphyErrIrqMaskCfg *obj);
uint32_t CSIRX_DphyErrStatusIrqSF(const CSIRX_DphyErrStatusIrq *obj);
uint32_t CSIRX_DphyLaneControlSF(const CSIRX_DphyLaneControl *obj);
uint32_t CSIRX_ErrorBypassCfgSF(const CSIRX_ErrorBypassCfg *obj);
uint32_t CSIRX_ErrorIrqsMaskCfgSF(const CSIRX_ErrorIrqsMaskCfg *obj);
uint32_t CSIRX_ErrorIrqsSF(const CSIRX_ErrorIrqs *obj);
uint32_t CSIRX_InfoIrqsMaskCfgSF(const CSIRX_InfoIrqsMaskCfg *obj);
uint32_t CSIRX_InfoIrqsSF(const CSIRX_InfoIrqs *obj);
uint32_t CSIRX_InterruptsHandlersSF(const CSIRX_InterruptsHandlers *obj);
uint32_t CSIRX_MonitorIrqsMaskCfgSF(const CSIRX_MonitorIrqsMaskCfg *obj);
uint32_t CSIRX_MonitorIrqsSF(const CSIRX_MonitorIrqs *obj);
uint32_t CSIRX_PrivateDataSF(const CSIRX_PrivateData *obj);
uint32_t CSIRX_SoftResetSF(const CSIRX_SoftReset *obj);
uint32_t CSIRX_StaticCfgSF(const CSIRX_StaticCfg *obj);
uint32_t CSIRX_StreamCfgSF(const CSIRX_StreamCfg *obj);
uint32_t CSIRX_StreamCtrlSF(const CSIRX_StreamCtrl *obj);
uint32_t CSIRX_StreamDataCfgSF(const CSIRX_StreamDataCfg *obj);
uint32_t CSIRX_StreamFccCfgSF(const CSIRX_StreamFccCfg *obj);
uint32_t CSIRX_StreamFccCtrlSF(const CSIRX_StreamFccCtrl *obj);
uint32_t CSIRX_StreamFifoFillLvlSF(const CSIRX_StreamFifoFillLvl *obj);
uint32_t CSIRX_StreamMonitorCtrlSF(const CSIRX_StreamMonitorCtrl *obj);
uint32_t CSIRX_StreamMonitorLbSF(const CSIRX_StreamMonitorLb *obj);
uint32_t CSIRX_StreamTimerSF(const CSIRX_StreamTimer *obj);

uint32_t CSIRX_SanityFunction1(const CSIRX_Config* config, const CSIRX_SysReq* memReq);
uint32_t CSIRX_SanityFunction2(const CSIRX_PrivateData* pD, const CSIRX_Config* config, const CSIRX_InterruptsHandlers* irqs);
uint32_t CSIRX_SanityFunction3(const CSIRX_PrivateData* pD);
uint32_t CSIRX_SanityFunction4(const CSIRX_PrivateData* pD, const CSIRX_DeviceConfig* value);
uint32_t CSIRX_SanityFunction6(const CSIRX_PrivateData* pD, const CSIRX_SoftReset* value);
uint32_t CSIRX_SanityFunction7(const CSIRX_PrivateData* pD, const CSIRX_SoftReset* value);
uint32_t CSIRX_SanityFunction8(const CSIRX_PrivateData* pD, const CSIRX_StaticCfg* value);
uint32_t CSIRX_SanityFunction9(const CSIRX_PrivateData* pD, const CSIRX_StaticCfg* value);
uint32_t CSIRX_SanityFunction10(const CSIRX_PrivateData* pD, const CSIRX_ErrorBypassCfg* value);
uint32_t CSIRX_SanityFunction11(const CSIRX_PrivateData* pD, const CSIRX_ErrorBypassCfg* value);
uint32_t CSIRX_SanityFunction12(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction13(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction14(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction15(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction16(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction17(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqsMaskCfg* value);
uint32_t CSIRX_SanityFunction18(const CSIRX_PrivateData* pD, const CSIRX_DphyErrIrqMaskCfg* value);
uint32_t CSIRX_SanityFunction19(const CSIRX_PrivateData* pD, const CSIRX_DphyErrIrqMaskCfg* value);
uint32_t CSIRX_SanityFunction20(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqs* value);
uint32_t CSIRX_SanityFunction21(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqs* value);
uint32_t CSIRX_SanityFunction22(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqs* value);
uint32_t CSIRX_SanityFunction23(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqs* value);
uint32_t CSIRX_SanityFunction24(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqs* value);
uint32_t CSIRX_SanityFunction25(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqs* value);
uint32_t CSIRX_SanityFunction26(const CSIRX_PrivateData* pD, const CSIRX_DphyErrStatusIrq* value);
uint32_t CSIRX_SanityFunction27(const CSIRX_PrivateData* pD, const CSIRX_DphyErrStatusIrq* value);
uint32_t CSIRX_SanityFunction28(const CSIRX_PrivateData* pD, const CSIRX_DphyLaneControl* value);
uint32_t CSIRX_SanityFunction29(const CSIRX_PrivateData* pD, const CSIRX_DphyLaneControl* value);
uint32_t CSIRX_SanityFunction30(const CSIRX_PrivateData* pD, const CSIRX_DphyStatus* value);
uint32_t CSIRX_SanityFunction31(const CSIRX_PrivateData* pD, const CSIRX_IntegrationDebug* value);
uint32_t CSIRX_SanityFunction32(const CSIRX_PrivateData* pD, const CSIRX_ErrorDebug* value);
uint32_t CSIRX_SanityFunction33(const CSIRX_PrivateData* pD, const CSIRX_TestGeneric* value);
uint32_t CSIRX_SanityFunction34(const CSIRX_PrivateData* pD, const CSIRX_StreamCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction35(const CSIRX_PrivateData* pD, const CSIRX_StreamCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction36(const CSIRX_PrivateData* pD, const CSIRX_StreamStatus* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction37(const CSIRX_PrivateData* pD, const CSIRX_StreamCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction38(const CSIRX_PrivateData* pD, const CSIRX_StreamCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction39(const CSIRX_PrivateData* pD, const CSIRX_StreamDataCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction40(const CSIRX_PrivateData* pD, const CSIRX_StreamDataCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction41(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction42(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction43(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorFrame* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction44(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorLb* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction45(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorLb* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction46(const CSIRX_PrivateData* pD, const CSIRX_StreamTimer* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction47(const CSIRX_PrivateData* pD, const CSIRX_StreamTimer* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction48(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction49(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCfg* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction50(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction51(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCtrl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction52(const CSIRX_PrivateData* pD, const CSIRX_StreamFifoFillLvl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction53(const CSIRX_PrivateData* pD, const CSIRX_StreamFifoFillLvl* value, const uint32_t streamNo);
uint32_t CSIRX_SanityFunction54(const CSIRX_PrivateData* pD, const CSIRX_AsfInfo* asfInfo);

#define CSIRX_ProbeSF CSIRX_SanityFunction1
#define CSIRX_InitSF CSIRX_SanityFunction2
#define CSIRX_IsrSF CSIRX_SanityFunction3
#define CSIRX_GetDeviceConfigSF CSIRX_SanityFunction4
#define CSIRX_GetSoftResetSF CSIRX_SanityFunction6
#define CSIRX_SetSoftResetSF CSIRX_SanityFunction7
#define CSIRX_GetStaticCfgSF CSIRX_SanityFunction8
#define CSIRX_SetStaticCfgSF CSIRX_SanityFunction9
#define CSIRX_GetErrorBypassCfgSF CSIRX_SanityFunction10
#define CSIRX_SetErrorBypassCfgSF CSIRX_SanityFunction11
#define CSIRX_GetInfoIrqsMaskCfgSF CSIRX_SanityFunction12
#define CSIRX_SetInfoIrqsMaskCfgSF CSIRX_SanityFunction13
#define CSIRX_GetMonitorIrqsMaskCfgSF CSIRX_SanityFunction14
#define CSIRX_SetMonitorIrqsMaskCfgSF CSIRX_SanityFunction15
#define CSIRX_GetErrorIrqsMaskCfgSF CSIRX_SanityFunction16
#define CSIRX_SetErrorIrqsMaskCfgSF CSIRX_SanityFunction17
#define CSIRX_GetDphyErrIrqMaskCfgSF CSIRX_SanityFunction18
#define CSIRX_SetDphyErrIrqMaskCfgSF CSIRX_SanityFunction19
#define CSIRX_GetInfoIrqsSF CSIRX_SanityFunction20
#define CSIRX_SetInfoIrqsSF CSIRX_SanityFunction21
#define CSIRX_GetMonitorIrqsSF CSIRX_SanityFunction22
#define CSIRX_SetMonitorIrqsSF CSIRX_SanityFunction23
#define CSIRX_GetErrorIrqsSF CSIRX_SanityFunction24
#define CSIRX_SetErrorIrqsSF CSIRX_SanityFunction25
#define CSIRX_GetDphyErrStatusIrqSF CSIRX_SanityFunction26
#define CSIRX_SetDphyErrStatusIrqSF CSIRX_SanityFunction27
#define CSIRX_GetDphyLaneControlSF CSIRX_SanityFunction28
#define CSIRX_SetDphyLaneControlSF CSIRX_SanityFunction29
#define CSIRX_GetDphyStatusSF CSIRX_SanityFunction30
#define CSIRX_GetIntegrationDebugSF CSIRX_SanityFunction31
#define CSIRX_GetErrorDebugSF CSIRX_SanityFunction32
#define CSIRX_GetTestGenericSF CSIRX_SanityFunction33
#define CSIRX_GetStreamCtrlSF CSIRX_SanityFunction34
#define CSIRX_SetStreamCtrlSF CSIRX_SanityFunction35
#define CSIRX_GetStreamStatusSF CSIRX_SanityFunction36
#define CSIRX_GetStreamCfgSF CSIRX_SanityFunction37
#define CSIRX_SetStreamCfgSF CSIRX_SanityFunction38
#define CSIRX_GetStreamDataCfgSF CSIRX_SanityFunction39
#define CSIRX_SetStreamDataCfgSF CSIRX_SanityFunction40
#define CSIRX_GetStreamMonitorCtrlSF CSIRX_SanityFunction41
#define CSIRX_SetStreamMonitorCtrlSF CSIRX_SanityFunction42
#define CSIRX_GetStreamMonitorFrameSF CSIRX_SanityFunction43
#define CSIRX_GetStreamMonitorLbSF CSIRX_SanityFunction44
#define CSIRX_SetStreamMonitorLbSF CSIRX_SanityFunction45
#define CSIRX_GetStreamTimerSF CSIRX_SanityFunction46
#define CSIRX_SetStreamTimerSF CSIRX_SanityFunction47
#define CSIRX_GetStreamFccCfgSF CSIRX_SanityFunction48
#define CSIRX_SetStreamFccCfgSF CSIRX_SanityFunction49
#define CSIRX_GetStreamFccCtrlSF CSIRX_SanityFunction50
#define CSIRX_SetStreamFccCtrlSF CSIRX_SanityFunction51
#define CSIRX_GetStreamFifoFillLvlSF CSIRX_SanityFunction52
#define CSIRX_SetStreamFifoFillLvlSF CSIRX_SanityFunction53
#define CSIRX_GetAsfInfoSF CSIRX_SanityFunction54

#endif  /* CSIRX_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
