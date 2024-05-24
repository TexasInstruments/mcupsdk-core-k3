/*
 *  Copyright (c) 2024 Texas Instruments Incorporated
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
 *
 */

/*===========================================================================*/
/*                              Include files                                */
/*===========================================================================*/

#include "../test_sciclient.h"

/*===========================================================================*/
/*                                    Macros                                 */
/*===========================================================================*/

/** The offset is determined in CSL's m4 startup.c */
#define RAT_MAP_M4F_OFFSET 0x60000000U
/** Convert to M4F rat mapping */
#define RAT_MAP(_val)  ((_val) + RAT_MAP_M4F_OFFSET)

/*===========================================================================*/
/*                              Declarations                                 */
/*===========================================================================*/

struct tisci_msg_proc_set_config_req configReq =
{
    .processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0,
    .bootvector_lo = 0x43C00000,
    .config_flags_1_set   = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS,
    .config_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE
};

struct tisci_msg_proc_set_config_req configReq3 =
{
    .processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0,
    .bootvector_lo = 0x43C00000,
    .config_flags_1_set   = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS,
    .config_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE
};

struct tisci_msg_fwl_set_firewall_region_resp  setFwResp;
struct tisci_msg_fwl_set_firewall_region_req setFwReq =
{
    .fwl_id = 7,
    .region = 0,
    .n_permission_regs = 3,
    .control = 0x30A, /* 0x3 - Firewall background region, Unlocked. 0xA - Enable Firewall */
    .permissions[0] = 0xC3FFFF,
    .permissions[1] = 0xC3FFFF,
    .permissions[2] = 0xC3FFFF,
    .start_address  = 0x60000000U,
    .end_address    = 0x67ffffffU,
};

struct tisci_msg_proc_set_config_req configReq2 =
{
    .processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0,
    .bootvector_lo = 0x43C00000,
    .config_flags_1_set   = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS,
    .config_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE
};

struct tisci_get_trace_config_req request;
Sciclient_ReqPrm_t reqParam1 = {
    .messageType    = (uint16_t) TISCI_MSG_GET_TRACE_CONFIG,
    .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload    = (const uint8_t *) &request,
    .reqPayloadSize = (uint32_t) sizeof (request),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

struct tisci_get_trace_config_resp response;
Sciclient_RespPrm_t respParam1 = {
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &response,
    .respPayloadSize = (uint32_t) sizeof (response),
};

struct tisci_msg_fwl_get_firewall_region_resp fwGetResp;
struct tisci_msg_fwl_get_firewall_region_req fwGetReq =
{
    .fwl_id = 7,
    .region = 0,
    .n_permission_regs = 3,
};

struct tisci_msg_fwl_change_owner_info_req fwCngOwnerInfoReq =
{
    .fwl_id = 7,
    .region = 0,
    .owner_index = TISCI_HOST_ID_MAIN_0_R5_0,
};

struct tisci_msg_fwl_change_owner_info_req fwCngOwnerInfoReq2 =
{
    .fwl_id = 3,
    .region = 0,
    .owner_index = TISCI_HOST_ID_MAIN_0_R5_0,
};

struct tisci_msg_fwl_set_firewall_region_resp  setFwResp2;
struct tisci_msg_fwl_set_firewall_region_req setFwReq2 =
{
    .fwl_id = 3,
    .region = 0,
    .n_permission_regs = 3,
    .control = 0x30A, /* 0x3 - Firewall background region, Unlocked. 0xA - Enable Firewall */
    .permissions[0] = 0xC3FFFF,
    .permissions[1] = 0xC3FFFF,
    .permissions[2] = 0xC3FFFF,
    .start_address  = 0x70000000,
    .end_address    = 0x701FF000,
};

struct tisci_msg_keywriter_resp kwProgResp;
struct tisci_msg_keywriter_req kwProgCfg =
{
    .image_addr_lo = 0x43c18980,
    .image_addr_hi = 0,
};

Sciclient_RespPrm_t kwProgRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &kwProgResp,
    .respPayloadSize = (uint32_t) sizeof (kwProgResp),
};

Sciclient_ReqPrm_t kwProgReqParam =
{
    .messageType = 0x9031,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &kwProgCfg,
    .reqPayloadSize = (uint32_t) sizeof (kwProgCfg),
    .timeout = -1,
};

struct tisci_msg_read_otp_mmr_resp readOtpResp = {0};
struct tisci_msg_read_otp_mmr_req readOtpCfg =
{
    .mmr_idx = 31,
};

Sciclient_ReqPrm_t readOtpReqParam1 =
{
    .messageType = 0x9022,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &readOtpCfg,
    .reqPayloadSize = (uint32_t) sizeof (readOtpCfg),
    .timeout = -1,
};

Sciclient_RespPrm_t readOtpRespParam1 =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &readOtpResp,
    .respPayloadSize = (uint32_t) sizeof (readOtpResp),
};

struct tisci_msg_write_otp_row_resp writeOTPRowResp = {0};
struct tisci_msg_write_otp_row_req writeOTPRowCfg =
{
    .row_idx = 0,
    .row_mask = 0x10,
    .row_val = 0x10
};

Sciclient_ReqPrm_t writeOTPRowReqParam =
{
    .messageType = 0x9023,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &writeOTPRowCfg,
    .reqPayloadSize = (uint32_t) sizeof (writeOTPRowCfg),
    .timeout = -1,
};

Sciclient_RespPrm_t writeOTPRowRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &writeOTPRowResp,
    .respPayloadSize = (uint32_t) sizeof (writeOTPRowResp),
};

struct tisci_msg_prepare_sleep_resp prepSleepResp = {0};
struct tisci_msg_prepare_sleep_req prepSleepCfg =
{
    .mode = 0,
    .ctx_lo = 0x700000,
};

Sciclient_RespPrm_t prepSleepRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &prepSleepResp,
    .respPayloadSize = (uint32_t) sizeof (prepSleepResp),
};

Sciclient_ReqPrm_t prepSleepReqParam =
{
    .messageType = 0x300,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &prepSleepCfg,
    .reqPayloadSize = (uint32_t) sizeof (prepSleepCfg),
    .timeout = -1,
};

struct tisci_msg_prepare_sleep_resp prepSleepPassResp = {0};
struct tisci_msg_prepare_sleep_req prepSleepPassCfg =
{
    .mode = 0,
    .ctx_lo = 0x9B700000,
};

Sciclient_RespPrm_t prepSleepPassRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &prepSleepPassResp,
    .respPayloadSize = (uint32_t) sizeof (prepSleepPassResp),
};

Sciclient_ReqPrm_t prepSleepPassReqParam =
{
    .messageType = 0x300,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &prepSleepPassCfg,
    .reqPayloadSize = (uint32_t) sizeof (prepSleepPassCfg),
    .timeout = -1,
};

struct tisci_msg_set_io_isolation_req setIOIsolationCfg =
{
    .state = 2,
};

Sciclient_RespPrm_t setIOIsolationRespParam =
{
    .flags = 0,
    .pRespPayload = NULL,
};

Sciclient_ReqPrm_t setIOIsolationReqParam =
{
    .messageType = 0x307,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &setIOIsolationCfg,
    .reqPayloadSize = (uint32_t) sizeof (setIOIsolationCfg),
    .timeout = -1,
};

struct tisci_msg_set_device_resp setDevResp;
struct tisci_msg_set_device_req setDevCfg =
{
    .id = 121,
    .state = 1,
};

Sciclient_RespPrm_t setDevRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &setDevResp,
    .respPayloadSize = (uint32_t) sizeof (setDevResp),
};

Sciclient_ReqPrm_t setDevReqParam =
{
    .messageType = 0x200,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &setDevCfg,
    .reqPayloadSize = (uint32_t) sizeof (setDevCfg),
    .timeout = -1,
};

struct tisci_msg_set_device_resets_resp setDevRstResp;
struct tisci_msg_set_device_resets_req setDevRstCfg =
{
    .id = 121,
    .resets = 2,
};

Sciclient_RespPrm_t setDevRstRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &setDevRstResp,
    .respPayloadSize = (uint32_t) sizeof (setDevRstResp),
};

Sciclient_ReqPrm_t setDevRstReqParam =
{
    .messageType = 0x202,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &setDevRstCfg,
    .reqPayloadSize = (uint32_t) sizeof (setDevRstCfg),
    .timeout = -1,
};

struct tisci_msg_set_device_resp setDevResp1;
struct tisci_msg_set_device_req setDevCfg1 =
{
    .id = 121,
    .state = 0,
};

Sciclient_RespPrm_t setDevRespParam1 =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &setDevResp1,
    .respPayloadSize = (uint32_t) sizeof (setDevResp1),
};

Sciclient_ReqPrm_t setDevReqParam1 =
{
    .messageType = 0x200,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &setDevCfg1,
    .reqPayloadSize = (uint32_t) sizeof (setDevCfg1),
    .timeout = -1,
};

struct tisci_msg_set_device_resp setDevResp2;
struct tisci_msg_set_device_req setDevCfg2 =
{
    .id = 121,
    .state = 2,
};

Sciclient_RespPrm_t setDevRespParam2 =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &setDevResp2,
    .respPayloadSize = (uint32_t) sizeof (setDevResp2),
};

Sciclient_ReqPrm_t setDevReqParam2 =
{
    .messageType = 0x200,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &setDevCfg2,
    .reqPayloadSize = (uint32_t) sizeof (setDevCfg2),
    .timeout = -1,
};

struct tisci_header mockTxMsg =
{
    .type = 0xD,
};

struct tisci_msg_rm_irq_set_req mock_req;
struct tisci_msg_rm_irq_set_resp mock_resp;
Sciclient_RespPrm_t RespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &mock_resp,
    .respPayloadSize = (uint32_t) sizeof (mock_resp),
};

Sciclient_ReqPrm_t ReqParam =
{
    .messageType = 0x1000,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &mock_req,
    .reqPayloadSize = (uint32_t) sizeof (mock_req),
    .timeout = 0,
};

struct tisci_msg_read_otp_mmr_resp readOtpResp2 = {0};
struct tisci_msg_read_otp_mmr_req readOtpCfg2 =
{
    .mmr_idx = 31,
};

Sciclient_ReqPrm_t readOtpReqParam2 =
{
    .messageType = (uint16_t) TISCI_MSG_READ_OTP_MMR,
    .flags = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload = (const uint8_t *) &readOtpCfg2,
    .reqPayloadSize = (uint32_t) sizeof (readOtpCfg2),
    .timeout = (uint32_t) (0xFFFFFFFFU),
};

Sciclient_RespPrm_t readOtpRespParam2 =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &readOtpResp2,
    .respPayloadSize = (uint32_t) sizeof (readOtpResp2),
};

struct tisci_query_fw_caps_resp queryFwCapsResp;
struct tisci_query_fw_caps_req queryFwCapsCfg;
Sciclient_RespPrm_t queryFwCapsRespParam =
{
    .flags = 0,
    .pRespPayload = (uint8_t *) &queryFwCapsResp,
    .respPayloadSize = (uint32_t) sizeof (queryFwCapsResp),
};

Sciclient_ReqPrm_t queryFwCapsReqParam =
{
    .messageType = 0x22,
    .flags = 2,
    .pReqPayload = (const uint8_t *) &queryFwCapsCfg,
    .reqPayloadSize = (uint32_t) sizeof (queryFwCapsCfg),
    .timeout = -1,
};

struct tisci_get_trace_config_req request2;
Sciclient_ReqPrm_t reqParam2 =
{
    .messageType = (uint16_t) TISCI_MSG_GET_TRACE_CONFIG,
    .flags = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload = (const uint8_t *) &request2,
    .reqPayloadSize = (uint32_t) sizeof (request2),
    .timeout = (uint32_t) (0xFFFFFFFFU),
};

struct tisci_get_trace_config_resp response2;
Sciclient_RespPrm_t respParam2 =
{
    .flags = (uint32_t) 0,
    .pRespPayload = (uint8_t *) &response2,
    .respPayloadSize = (uint32_t) sizeof (response2),
};

struct tisci_get_trace_config_req request4;
Sciclient_ReqPrm_t reqParam4 = {
    .messageType    = (uint16_t) TISCI_MSG_BOOT_NOTIFICATION,
    .flags          = (uint32_t) 0,
    .pReqPayload    = (const uint8_t *) &request4,
    .reqPayloadSize = (uint32_t) sizeof (request4),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

struct tisci_get_trace_config_resp response4;
Sciclient_RespPrm_t respParam4 = {
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &response4,
    .respPayloadSize = (uint32_t) sizeof (response4),
};

struct tisci_msg_fwl_get_firewall_region_req fwGetReq2 =
{
    .fwl_id = 0xFF,
    .region = 0,
    .n_permission_regs = 3,
};
struct tisci_msg_fwl_get_firewall_region_resp fwGetResp2;

CSL_SecProxyCfg secProxyCfg =
{
    (CSL_sec_proxyRegs *)       RAT_MAP(CSL_DMASS0_SEC_PROXY_MMRS_BASE),
    /*< pSecProxyRegs */
    (CSL_sec_proxy_scfgRegs *)  RAT_MAP(CSL_DMASS0_SEC_PROXY_SCFG_BASE),
    /*< pSecProxyScfgRegs */
    (CSL_sec_proxy_rtRegs *)    RAT_MAP(CSL_DMASS0_SEC_PROXY_RT_BASE),
    /*< pSecProxyRtRegs */
    (uint64_t)                  RAT_MAP(CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE),
    /*< proxyTargetAddr */
    0
    /*< maxMsgSize */
};
CSL_sec_proxyRegs sec_proxyRegs = {
    .CONFIG = 0xFFFF,
    .PID    = 0x0000,
};

CSL_SecProxyCfg test_error_secProxyCfg = {
    (CSL_sec_proxyRegs *)       &sec_proxyRegs,
    /*< pSecProxyRegs */
    (CSL_sec_proxy_scfgRegs *)  RAT_MAP(CSL_DMASS0_SEC_PROXY_SCFG_BASE),
    /*< pSecProxyScfgRegs */
    (CSL_sec_proxy_rtRegs *)    RAT_MAP(CSL_DMASS0_SEC_PROXY_RT_BASE),
    /*< pSecProxyRtRegs */
    (uint64_t)                  RAT_MAP(CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE),
    /*< proxyTargetAddr */
    0
    /*< maxMsgSize */
};
/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

/*None*/

/*===========================================================================*/
/*                         External function declarations                    */
/*===========================================================================*/

/*None*/

/*===========================================================================*/
/*                          Local Function definitions                       */
/*===========================================================================*/

/*None*/

/* Nothing past this point */
