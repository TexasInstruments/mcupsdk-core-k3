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

#ifndef DSITX_SANITY_H
#define DSITX_SANITY_H


uint32_t DSITX_ColorSF(const DSITX_Color *obj);
uint32_t DSITX_CommandModeSettingsSF(const DSITX_CommandModeSettings *obj);
uint32_t DSITX_ConfigSF(const DSITX_Config *obj);
uint32_t DSITX_DataPathConfigSF(const DSITX_DataPathConfig *obj);
uint32_t DSITX_DirectCommandRequestSF(const DSITX_DirectCommandRequest *obj);
uint32_t DSITX_DphyConfigSF(const DSITX_DphyConfig *obj);
uint32_t DSITX_DphyPwrRstConfigSF(const DSITX_DphyPwrRstConfig *obj);
uint32_t DSITX_DsiLinkConfigSF(const DSITX_DsiLinkConfig *obj);
uint32_t DSITX_ErrorColorSF(const DSITX_ErrorColor *obj);
uint32_t DSITX_PhyConfigSF(const DSITX_PhyConfig *obj);
uint32_t DSITX_PrivateDataSF(const DSITX_PrivateData *obj);
uint32_t DSITX_TestGenericSF(const DSITX_TestGeneric *obj);
uint32_t DSITX_TestVideoModeConfigSF(const DSITX_TestVideoModeConfig *obj);
uint32_t DSITX_VcaConfigSF(const DSITX_VcaConfig *obj);
uint32_t DSITX_Video3dConfigSF(const DSITX_Video3dConfig *obj);
uint32_t DSITX_VideoModeSettingsSF(const DSITX_VideoModeSettings *obj);
uint32_t DSITX_VideoSizeSF(const DSITX_VideoSize *obj);

uint32_t DSITX_SanityFunction1(const DSITX_Config* config, const DSITX_SysReq* sysReq);
uint32_t DSITX_SanityFunction2(const DSITX_PrivateData* pD, const DSITX_Config* config);
uint32_t DSITX_SanityFunction3(const DSITX_PrivateData* pD);
uint32_t DSITX_SanityFunction7(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config);
uint32_t DSITX_SanityFunction8(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config);
uint32_t DSITX_SanityFunction9(const DSITX_PrivateData* pD, const DSITX_DataPathConfig* config);
uint32_t DSITX_SanityFunction10(const DSITX_PrivateData* pD, const DSITX_DataPathConfig* config);
uint32_t DSITX_SanityFunction11(const DSITX_PrivateData* pD, const DSITX_PhyConfig* config);
uint32_t DSITX_SanityFunction12(const DSITX_PrivateData* pD, const DSITX_PhyConfig* config);
uint32_t DSITX_SanityFunction13(const DSITX_PrivateData* pD, const DSITX_DphyPwrRstConfig* cfg);
uint32_t DSITX_SanityFunction14(const DSITX_PrivateData* pD, const DSITX_DphyPwrRstConfig* cfg);
uint32_t DSITX_SanityFunction15(const DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config);
uint32_t DSITX_SanityFunction16(const DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config);
uint32_t DSITX_SanityFunction17(const DSITX_PrivateData* pD, const DSITX_IpConf* config);
uint32_t DSITX_SanityFunction18(const DSITX_PrivateData* pD, const DSITX_HwIdAndVersion* id);
uint32_t DSITX_SanityFunction19(const DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode);
uint32_t DSITX_SanityFunction20(const DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode);
uint32_t DSITX_SanityFunction21(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode);
uint32_t DSITX_SanityFunction22(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode);
uint32_t DSITX_SanityFunction23(const DSITX_PrivateData* pD, const DSITX_VcaConfig* vca);
uint32_t DSITX_SanityFunction24(const DSITX_PrivateData* pD, const DSITX_VcaConfig* vca);
uint32_t DSITX_SanityFunction25(const DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize);
uint32_t DSITX_SanityFunction26(const DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize);
uint32_t DSITX_SanityFunction27(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config);
uint32_t DSITX_SanityFunction28(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config);
uint32_t DSITX_SanityFunction31(const DSITX_PrivateData* pD, const DSITX_DirectCommandRequest* dcr);
uint32_t DSITX_SanityFunction38(const DSITX_PrivateData* pD, const DSITX_TestGeneric* test);
uint32_t DSITX_SanityFunction39(const DSITX_PrivateData* pD, const DSITX_TestGeneric* test);
uint32_t DSITX_SanityFunction40(const DSITX_PrivateData* pD, const DSITX_Video3dConfig* cfg);
uint32_t DSITX_SanityFunction41(const DSITX_PrivateData* pD, const DSITX_Video3dConfig* cfg);
uint32_t DSITX_SanityFunction42(const DSITX_PrivateData* pD, const DSITX_AsfInfo* asfInfo);

#define	DSITX_ProbeSF DSITX_SanityFunction1
#define	DSITX_InitSF DSITX_SanityFunction2
#define	DSITX_IsrSF DSITX_SanityFunction3
#define	DSITX_StartSF DSITX_SanityFunction3
#define	DSITX_StopSF DSITX_SanityFunction3
#define	DSITX_DestroySF DSITX_SanityFunction3
#define	DSITX_SetDphyConfigSF DSITX_SanityFunction7
#define	DSITX_GetDphyConfigSF DSITX_SanityFunction8
#define	DSITX_SetDataPathConfigSF DSITX_SanityFunction9
#define	DSITX_GetDataPathConfigSF DSITX_SanityFunction10
#define	DSITX_SetPhyConfigSF DSITX_SanityFunction11
#define	DSITX_GetPhyConfigSF DSITX_SanityFunction12
#define	DSITX_SetDphyPwrAndRstCtrlSF DSITX_SanityFunction13
#define	DSITX_GetDphyPwrAndRstCtrlSF DSITX_SanityFunction14
#define	DSITX_SetDsiLinkConfigSF DSITX_SanityFunction15
#define	DSITX_GetDsiLinkConfigSF DSITX_SanityFunction16
#define	DSITX_GetIpConfSF DSITX_SanityFunction17
#define	DSITX_GetHwIdAndVersionSF DSITX_SanityFunction18
#define	DSITX_SetCommandModeSF DSITX_SanityFunction19
#define	DSITX_GetCommandModeSF DSITX_SanityFunction20
#define	DSITX_SetVideoModeSF DSITX_SanityFunction21
#define	DSITX_GetVideoModeSF DSITX_SanityFunction22
#define	DSITX_SetVcaConfigSF DSITX_SanityFunction23
#define	DSITX_GetVcaConfigSF DSITX_SanityFunction24
#define	DSITX_SetVideoSizeSF DSITX_SanityFunction25
#define	DSITX_GetVideoSizeSF DSITX_SanityFunction26
#define	DSITX_SetTvgConfigSF DSITX_SanityFunction27
#define	DSITX_GetTvgConfigSF DSITX_SanityFunction28
#define	DSITX_StartTvgSF DSITX_SanityFunction3
#define	DSITX_StopTvgSF DSITX_SanityFunction3
#define	DSITX_SendDirectCmdSF DSITX_SanityFunction31
#define	DSITX_SetDsiLinkEventHandlerSF DSITX_SanityFunction3
#define	DSITX_SetCmdModeEventHandlerSF DSITX_SanityFunction3
#define	DSITX_SetVidModeEventHandlerSF DSITX_SanityFunction3
#define	DSITX_SetTvgEventHandlerSF DSITX_SanityFunction3
#define	DSITX_SetDphyErrorEventHandlSF DSITX_SanityFunction3
#define	DSITX_SetDpiEventHandlerSF DSITX_SanityFunction3
#define	DSITX_SetTestGenericSF DSITX_SanityFunction38
#define	DSITX_GetTestGenericSF DSITX_SanityFunction39
#define	DSITX_SetVideo3dConfigSF DSITX_SanityFunction40
#define	DSITX_GetVideo3dConfigSF DSITX_SanityFunction41
#define	DSITX_GetAsfInfoSF DSITX_SanityFunction42
#define	DSITX_CheckLanesStateSF DSITX_SanityFunction3
#define	DSITX_WaitForPllLockSF DSITX_SanityFunction3


#endif	/* DSITX_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
