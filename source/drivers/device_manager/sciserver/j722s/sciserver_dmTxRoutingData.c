/*
 * Copyright (c) 2025-2026 Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file sciserver_dmTxRoutingData.c
 *
 * \brief DM Tx Routing Data for J722S device
 */

#include <hosts.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyRoutingDescription.h>

/** Maximum Host Entries */
#define J722S_CONFIG_MAX (0xFFU)

const uint16_t sproxy_route_data_count = J722S_CONFIG_MAX;

const struct sproxy_host_tx_thread_data sproxy_route_data[J722S_CONFIG_MAX] = {
	/*
	 * Non Secure Host WKUP_0_R5_1[36]
	 */
	[HOST_ID_WKUP_0_R5_1] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_WKUP_0_R5_1_RESPONSE_TX_THR068_CONF005,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_WKUP_0_R5_1_RESPONSE_TX_THR068_CONF005,
	},
	/*
	 * Non Secure Host MAIN_0_R5_1[38]
	 */
	[HOST_ID_MAIN_0_R5_1] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_1_RESPONSE_TX_THR067_CONF006,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_1_RESPONSE_TX_THR067_CONF006,
	},
	/*
	 * Non Secure Host A53_2[12]
	 */
	[HOST_ID_A53_2] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
	},
	/*
	 * Non Secure Host A53_3[13]
	 */
	[HOST_ID_A53_3] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
	},
	/*
	 * Non Secure Host A53_4[14]
	 */
	[HOST_ID_A53_4] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_4_RESPONSE_TX_THR064_CONF009,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_4_RESPONSE_TX_THR064_CONF009,
	},
	/*
	 * Non Secure Host MCU_0_R5_0[30]
	 */
	[HOST_ID_MCU_0_R5_0] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MCU_0_R5_0_RESPONSE_TX_THR063_CONF010,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MCU_0_R5_0_RESPONSE_TX_THR063_CONF010,
	},
	/*
	 * Non Secure Host C7X_0_0[20]
	 */
	[HOST_ID_C7X_0_0] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_0_0_RESPONSE_TX_THR062_CONF011,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_0_0_RESPONSE_TX_THR062_CONF011,
	},
	/*
	 * Non Secure Host C7X_1_0[22]
	 */
	[HOST_ID_C7X_1_0] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_1_0_RESPONSE_TX_THR061_CONF012,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_1_0_RESPONSE_TX_THR061_CONF012,
	},
	/*
	 * Non Secure Host A53_5[31]
	 */
	[HOST_ID_A53_5] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_5_RESPONSE_TX_THR060_CONF013,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_5_RESPONSE_TX_THR060_CONF013,
	},
	/*
	 * Non Secure Host GPU_1[32]
	 */
	[HOST_ID_GPU_1] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_1_RESPONSE_TX_THR059_CONF014,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_1_RESPONSE_TX_THR059_CONF014,
	},
	/*
	 * Non Secure Host DM2TIFS[250]
	 */
	[HOST_ID_DM2TIFS] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR070_CONF004,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR070_CONF004,
	},
	/*
	 * Non Secure Host TIFS2DM[251]
	 */
	[HOST_ID_TIFS2DM] = {
		.sproxy_resp_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR058_CONF015,
		.sproxy_ntfy_conf_id = J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR058_CONF015,
	},
	/*
	 * Secure Host HSM[253]
	 */
	[HOST_ID_HSM] = {
		.sproxy_resp_conf_id = J722S_SA3_SS0_SEC_PROXY_0_TX_TIFS_HSM_SEC_HSM_RESPONSE_TX_THR014_CONF032,
		.sproxy_ntfy_conf_id = J722S_SA3_SS0_SEC_PROXY_0_TX_TIFS_HSM_SEC_HSM_RESPONSE_TX_THR014_CONF032,
	},
};
