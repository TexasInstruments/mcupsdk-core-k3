/*
 * System Firmware Source File
 *
 * DMSC Tx Routing Data for AM62PX device
 *
 * Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <hosts.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyRoutingDescription.h>

const uint16_t sproxy_route_data_count = AM62X_SEC_PROXY_TX_CONFIG_MAX;

const struct sproxy_host_tx_thread_data sproxy_route_data[AM62X_SEC_PROXY_TX_CONFIG_MAX] = {
	/*
	 * Secure Host WKUP_0_R5_0[35]
	 */
	[HOST_ID_WKUP_0_R5_0] = {
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_WKUP_0_R5_0_RESPONSE_TX_THR074_CONF000,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_WKUP_0_R5_0_RESPONSE_TX_THR074_CONF000,
	},
	/*
	 * Non Secure Host WKUP_0_R5_1[36]
	 */
	[HOST_ID_WKUP_0_R5_1] = {
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_WKUP_0_R5_1_RESPONSE_TX_THR069_CONF004,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_WKUP_0_R5_1_RESPONSE_TX_THR069_CONF004,
	},
	/*
	 * Secure Host A53_0[10]
	 */
	[HOST_ID_A53_0] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR073_CONF001,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR073_CONF001,
	},
	/*
	 * Secure Host A53_1[11]
	 */
	[HOST_ID_A53_1] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
	},
	/*
	 * Non Secure Host A53_2[12]
	 */
	[HOST_ID_A53_2] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
	},
	/*
	 * Non Secure Host A53_3[13]
	 */
	[HOST_ID_A53_3] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
	},
	/*
	 * Non Secure Host A53_4[14]
	 */
	[HOST_ID_A53_4] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_4_RESPONSE_TX_THR064_CONF009,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_4_RESPONSE_TX_THR064_CONF009,
	},
	/*
	 * Non Secure Host MCU R5[30]
	 */
	[HOST_ID_MCU_0_R5_0] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MCU_0_R5_0_RESPONSE_TX_THR063_CONF010,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MCU_0_R5_0_RESPONSE_TX_THR063_CONF010,
	},
	/*
	 * Non Secure Host GPU_0[31]
	 */
	[HOST_ID_GPU_0] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_0_RESPONSE_TX_THR068_CONF005,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_0_RESPONSE_TX_THR068_CONF005,
	},
	/*
	 * Non Secure Host GPU_1[32]
	 */
	[HOST_ID_GPU_1] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_1_RESPONSE_TX_THR067_CONF006,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_1_RESPONSE_TX_THR067_CONF006,
	},
	/*
	 * Secure Host DM2TIFS[250]
	 */
	[HOST_ID_DM2TIFS] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR071_CONF003,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR071_CONF003,
	},
	/*
	 * Non Secure Host TIFS2DM[251]
	 */
	[HOST_ID_TIFS2DM] =	{
		.sproxy_resp_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR062_CONF011,
		.sproxy_ntfy_conf_id	= AM62PX_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR062_CONF011,
	},
	/*
	 * Secure Host HSM[253]
	 */
	[HOST_ID_HSM] =	{
		.sproxy_resp_conf_id	= AM62PX_SA3_SS0_SEC_PROXY_0_TX_TIFS_HSM_SEC_HSM_RESPONSE_TX_THR014_CONF024,
		.sproxy_ntfy_conf_id	= AM62PX_SA3_SS0_SEC_PROXY_0_TX_TIFS_HSM_SEC_HSM_RESPONSE_TX_THR014_CONF024,
	},
};
