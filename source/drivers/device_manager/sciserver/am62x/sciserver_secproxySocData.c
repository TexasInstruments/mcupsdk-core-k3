/*
 * System Firmware Source File
 *
 * SoC Data for Secure Proxy Instances for AM62X device
 *
 * Data version: 220527_134115
 *
 * Copyright (C) 2021-2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#include <types/errno.h>
#include <types/short_types.h>
#include <sciserver_commMemorySoc.h>
#include <soc_devgrps.h>

#include <sciserver_secproxyDescription.h>
#include <sciserver_secproxySocData.h>
#include <sciserver_ringAcelSocData.h>

const uint8_t Sciserver_SecureProxyInstancesNum  = SOC_MAX_SEC_PROXY_INSTANCES;

const struct Sciserver_SecureProxy gSciserverSecureProxyInstances[SOC_MAX_SEC_PROXY_INSTANCES] = {
	/*
	 * [0] AM62X_SPROXY_IDX_DMASS0_SEC_PROXY_0: Secure proxy instance:
	 * DMASS0_SEC_PROXY_0 linked to RA inst: DMASS0_RINGACC_0
	 */
	[AM62X_SPROXY_IDX_DMASS0_SEC_PROXY_0] =	 {
		.baseaddr_cfg_rt		= 0x4A600000ULL,
		.baseaddr_cfg_scfg		= 0x4A400000ULL,
		.baseaddr_src_target_data	= 0x4D000000ULL,
		.sproxy_target_hl		= 0x00400000ULL,
		.sproxy_ring_index_base		= 0U,
		.sproxy_ring_index_max		= 19U,
		.num_threads			= 76U,
		.devgrp				= SOC_DEVGRP_AM62X_TIFS_INTERNAL,
		.ra_idx				= AM62X_RA_IDX_DMASS0_RINGACC_0,
		.buffer_idx			= AM62X_SPROXY_MEM_IDX_DMSS_IPC_SRAM,
		.buffer_neg_offset		= 0x00001300U,
	},
	/*
	 * [1] AM62X_SPROXY_IDX_SA3_SS0_SEC_PROXY_0: Secure proxy instance:
	 * SA3_SS0_SEC_PROXY_0 linked to RA inst: SA3_SS0_RINGACC_0
	 */
	[AM62X_SPROXY_IDX_SA3_SS0_SEC_PROXY_0] = {
		.baseaddr_cfg_rt		= 0x44880000ULL,
		.baseaddr_cfg_scfg		= 0x44860000ULL,
		.baseaddr_src_target_data	= 0x43600000ULL,
		.sproxy_target_hl		= 0x00400000ULL,
		.sproxy_ring_index_base		= 0U,
		.sproxy_ring_index_max		= 5U,
		.num_threads			= 16U,
		.devgrp				= SOC_DEVGRP_AM62X_TIFS_INTERNAL,
		.ra_idx				= AM62X_RA_IDX_SA3_SS0_RINGACC_0,
		.buffer_idx			= AM62X_SPROXY_MEM_IDX_DMSS_HSM_IPC_SRAM,
		.buffer_neg_offset		= 0x00000400U,
	},
};
