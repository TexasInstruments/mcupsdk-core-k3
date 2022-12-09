/*
 * System Firmware Source File
 *
 * TIFS Tx Routing Data for AM62X device
 *
 * Data version: 210623_104925
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <hosts.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyRoutingDescription.h>

/** Maximum Host Entries */
#define AM62X_CONFIG_MAX (0xFFU)

const uint16_t sproxy_route_data_count = AM62X_CONFIG_MAX;

const struct sproxy_host_tx_thread_data sproxy_route_data[AM62X_CONFIG_MAX] = {
	/*
	 * Non Secure Host MAIN_0_R5_0[35]
	 */
	[HOST_ID_MAIN_0_R5_1] = {
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_1_RESPONSE_TX_THR068_CONF005,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_1_RESPONSE_TX_THR068_CONF005,
	},
	/*
	 * Non Secure Host MAIN_0_R5_2[37]
	 */
	[HOST_ID_MAIN_0_R5_3] = {
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_3_RESPONSE_TX_THR067_CONF006,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_3_RESPONSE_TX_THR067_CONF006,
	},
	/*
	 * Secure Host A53_0[10]
	 */
	[HOST_ID_A53_0] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR072_CONF002,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR072_CONF002,
	},
	/*
	 * Non Secure Host A53_1[11]
	 */
	[HOST_ID_A53_1] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_1_RESPONSE_TX_THR071_CONF003,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_1_RESPONSE_TX_THR071_CONF003,
	},
	/*
	 * Secure Host A53_2[12]
	 */
	[HOST_ID_A53_2] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
	},
	/*
	 * Secure Host A53_3[13]
	 */
	[HOST_ID_A53_3] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
	},
	/*
	 * Secure Host A53_4[13]
	 */
	[HOST_ID_A53_4] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_RX_A53_4_RESPONSE_THR020_CONF013,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_RX_A53_4_RESPONSE_THR020_CONF013,
	},
	/*
	 * Secure Host DM2TIFS[250]
	 */
	[HOST_ID_DM2TIFS] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR070_CONF004,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR070_CONF004,
	},
	/*
	 * Non Secure Host TIFS2DM[251]
	 */
	[HOST_ID_TIFS2DM] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR061_CONF012,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR061_CONF012,
	},
	/*
	 * Non Secure Host M4_0[30]
	 */
	[HOST_ID_M4_0] =	{
		.sproxy_resp_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_M4_0_RESPONSE_TX_THR064_CONF009,
		.sproxy_ntfy_conf_id	= AM62X_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_M4_0_RESPONSE_TX_THR064_CONF009,
	},
};
