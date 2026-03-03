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
 * \file sciserver_secproxyConfigData.c
 *
 * \brief SoC configs for secure proxy for J722S device
 */

#include <stdint.h>
#include <types/errno.h>
#include "sciserver_commMemorySoc.h"
#include <hosts.h>
#include "sciserver_secproxyConfigData.h"
#include "sciserver_ringAcelConfigData.h"

#include "sciserver_secproxyDescription.h"
#include "sciserver_secproxySocData.h"
#include "sciserver_ringAcelSocData.h"

/** SAFE_EVENT Does NOT generate an IRQ or an event onto ETL */
#define SOC_SAFE_EVENT (0xFFFFU)


const uint16_t Sciserver_SecureProxyTxConfigNum = SOC_MAX_SPT_TX_CONFIG_INSTANCES;

const struct Sciserver_SecureProxyTxThreadConfig Sciserver_SecureProxyTxConfigurations[SOC_MAX_SPT_TX_CONFIG_INSTANCES] = {
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_WKUP_0_R5_0_RESPONSE_TX_THR074_CONF000] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 74U,
		.num_credits		= 11U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_WKUP_0_R5_0_RESPONSE_THR000_CONF003,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_MAIN_0_R5_0_RESPONSE_TX_THR073_CONF001] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 73U,
		.num_credits		= 6U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_MAIN_0_R5_0_RESPONSE_THR004_CONF005,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR072_CONF002] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 72U,
		.num_credits		= 11U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_0_RESPONSE_THR008_CONF007,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_1_RESPONSE_TX_THR071_CONF003] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 71U,
		.num_credits		= 11U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_1_RESPONSE_THR010_CONF008,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR070_CONF004] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 70U,
		.num_credits		= 4U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM2TIFS_RESPONSE_THR028_CONF017,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_WKUP_0_R5_1_RESPONSE_TX_THR068_CONF005] = {
		.host_id		= HOST_ID_DM,
		.thread_id		= 68U,
		.num_credits		= 11U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_WKUP_0_R5_1_RESPONSE_THR002_CONF004,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MAIN_0_R5_1_RESPONSE_TX_THR067_CONF006] = {
		.host_id		= HOST_ID_DM,
		.thread_id		= 67U,
		.num_credits		= 6U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_MAIN_0_R5_1_RESPONSE_THR006_CONF006,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 66U,
		.num_credits		= 6U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_2_RESPONSE_THR012_CONF009,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 65U,
		.num_credits		= 6U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_3_RESPONSE_THR014_CONF010,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_4_RESPONSE_TX_THR064_CONF009] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 64U,
		.num_credits		= 6U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_4_RESPONSE_THR016_CONF011,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_MCU_0_R5_0_RESPONSE_TX_THR063_CONF010] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 63U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_MCU_0_R5_0_RESPONSE_THR018_CONF012,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_0_0_RESPONSE_TX_THR062_CONF011] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 62U,
		.num_credits		= 4U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_C7X_0_0_RESPONSE_THR020_CONF013,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_C7X_1_0_RESPONSE_TX_THR061_CONF012] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 61U,
		.num_credits		= 4U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_C7X_1_0_RESPONSE_THR022_CONF014,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_5_RESPONSE_TX_THR060_CONF013] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 60U,
		.num_credits		= 1U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_A53_5_RESPONSE_THR024_CONF015,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_GPU_1_RESPONSE_TX_THR059_CONF014] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 59U,
		.num_credits		= 1U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_GPU_1_RESPONSE_THR026_CONF016,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR058_CONF015] =	 {
		.host_id		= HOST_ID_DM,
		.thread_id		= 58U,
		.num_credits		= 4U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS2DM_RESPONSE_THR030_CONF018,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_WKUP_0_R5_0_LOW_PRIORITY_THR001_CONF016] =		 {
		.host_id		= HOST_ID_WKUP_0_R5_0,
		.thread_id		= 1U,
		.num_credits		= 10U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_LOW_PRIORITY_RX_THR075_CONF000,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_WKUP_0_R5_1_LOW_PRIORITY_THR003_CONF017] =		 {
		.host_id		= HOST_ID_WKUP_0_R5_1,
		.thread_id		= 3U,
		.num_credits		= 10U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_MAIN_0_R5_0_LOW_PRIORITY_THR005_CONF018] =		 {
		.host_id		= HOST_ID_MAIN_0_R5_0,
		.thread_id		= 5U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_LOW_PRIORITY_RX_THR075_CONF000,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_MAIN_0_R5_1_LOW_PRIORITY_THR007_CONF019] =		 {
		.host_id		= HOST_ID_MAIN_0_R5_1,
		.thread_id		= 7U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_0_LOW_PRIORITY_THR009_CONF020] =		 {
		.host_id		= HOST_ID_A53_0,
		.thread_id		= 9U,
		.num_credits		= 10U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_LOW_PRIORITY_RX_THR075_CONF000,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_1_LOW_PRIORITY_THR011_CONF021] =		 {
		.host_id		= HOST_ID_A53_1,
		.thread_id		= 11U,
		.num_credits		= 10U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_LOW_PRIORITY_RX_THR075_CONF000,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_2_LOW_PRIORITY_THR013_CONF022] =		 {
		.host_id		= HOST_ID_A53_2,
		.thread_id		= 13U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_3_LOW_PRIORITY_THR015_CONF023] =		 {
		.host_id		= HOST_ID_A53_3,
		.thread_id		= 15U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_4_LOW_PRIORITY_THR017_CONF024] =		 {
		.host_id		= HOST_ID_A53_4,
		.thread_id		= 17U,
		.num_credits		= 5U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_MCU_0_R5_0_LOW_PRIORITY_THR019_CONF025] =		 {
		.host_id		= HOST_ID_MCU_0_R5_0,
		.thread_id		= 19U,
		.num_credits		= 4U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_C7X_0_0_LOW_PRIORITY_THR021_CONF026] =		 {
		.host_id		= HOST_ID_C7X_0_0,
		.thread_id		= 21U,
		.num_credits		= 3U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_C7X_1_0_LOW_PRIORITY_THR023_CONF027] =		 {
		.host_id		= HOST_ID_C7X_1_0,
		.thread_id		= 23U,
		.num_credits		= 3U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_A53_5_LOW_PRIORITY_THR025_CONF028] =		 {
		.host_id		= HOST_ID_A53_5,
		.thread_id		= 25U,
		.num_credits		= 1U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_GPU_1_LOW_PRIORITY_THR027_CONF029] =		 {
		.host_id		= HOST_ID_GPU_1,
		.thread_id		= 27U,
		.num_credits		= 1U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_DM2TIFS_LOW_PRIORITY_THR029_CONF030] =		 {
		.host_id		= HOST_ID_DM2TIFS,
		.thread_id		= 29U,
		.num_credits		= 2U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_DM2TIFS_LOW_PRIORITY_RX_THR057_CONF002,
	},
	[J722S_DMASS0_SEC_PROXY_0_TX_TIFS2DM_LOW_PRIORITY_THR031_CONF031] =		 {
		.host_id		= HOST_ID_TIFS2DM,
		.thread_id		= 31U,
		.num_credits		= 2U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001,
	},
	[J722S_SA3_SS0_SEC_PROXY_0_TX_TIFS_HSM_SEC_HSM_RESPONSE_TX_THR014_CONF032] =	 {
		.host_id		= HOST_ID_TIFS,
		.thread_id		= 14U,
		.num_credits		= 8U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_SA3_SS0_SEC_PROXY_0_RX_HSM_RESPONSE_THR000_CONF020,
	},
	[J722S_SA3_SS0_SEC_PROXY_0_TX_HSM_LOW_PRIORITY_THR001_CONF033] =		 {
		.host_id		= HOST_ID_HSM,
		.thread_id		= 1U,
		.num_credits		= 8U,
		.threshold		= 1U,
		.evt_threshold		= SOC_SAFE_EVENT,
		.evt_error		= SOC_SAFE_EVENT,
		.rx_thread_instance_id	= J722S_SA3_SS0_SEC_PROXY_0_RX_TIFS_HSM_SEC_LOW_PRIORITY_RX_THR015_CONF019,
	},
};

const uint16_t gSciserverSecureProxyRxConfigNum = SOC_MAX_SPT_RX_CONFIG_INSTANCES;

const struct Sciserver_SecureProxyRxThreadConfig gSciserverSecureProxyRxConfigurations[SOC_MAX_SPT_RX_CONFIG_INSTANCES] = {
	[J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_LOW_PRIORITY_RX_THR075_CONF000] =		{
		.host_id			= HOST_ID_TIFS,
		.thread_id			= 75U,
		.threshold			= 1U,
		.evt_threshold			= 0x000CU,
		.evt_error			= 0x000BU,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0019_CONF_000,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR069_CONF001] =	{
		.host_id			= HOST_ID_DM,
		.thread_id			= 69U,
		.threshold			= 1U,
		.evt_threshold			= 0x0010U,
		.evt_error			= 0x000FU,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0018_CONF_001,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_TIFS_SEC_DM2TIFS_LOW_PRIORITY_RX_THR057_CONF002] = {
		.host_id			= HOST_ID_TIFS,
		.thread_id			= 57U,
		.threshold			= 1U,
		.evt_threshold			= 0x000DU,
		.evt_error			= 0x000BU,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0001_CONF_018,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_WKUP_0_R5_0_RESPONSE_THR000_CONF003] =		{
		.host_id			= HOST_ID_WKUP_0_R5_0,
		.thread_id			= 0U,
		.threshold			= 1U,
		.evt_threshold			= 0x0000U,
		.evt_error			= 0x0000U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0017_CONF_002,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_WKUP_0_R5_1_RESPONSE_THR002_CONF004] =		{
		.host_id			= HOST_ID_WKUP_0_R5_1,
		.thread_id			= 2U,
		.threshold			= 1U,
		.evt_threshold			= 0x0001U,
		.evt_error			= 0x0001U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0016_CONF_003,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_MAIN_0_R5_0_RESPONSE_THR004_CONF005] =		{
		.host_id			= HOST_ID_MAIN_0_R5_0,
		.thread_id			= 4U,
		.threshold			= 1U,
		.evt_threshold			= 0x0002U,
		.evt_error			= 0x0002U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0015_CONF_004,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_MAIN_0_R5_1_RESPONSE_THR006_CONF006] =		{
		.host_id			= HOST_ID_MAIN_0_R5_1,
		.thread_id			= 6U,
		.threshold			= 1U,
		.evt_threshold			= 0x0003U,
		.evt_error			= 0x0003U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0014_CONF_005,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_0_RESPONSE_THR008_CONF007] =			{
		.host_id			= HOST_ID_A53_0,
		.thread_id			= 8U,
		.threshold			= 1U,
		.evt_threshold			= 0x0004U,
		.evt_error			= 0x0004U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0013_CONF_006,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_1_RESPONSE_THR010_CONF008] =			{
		.host_id			= HOST_ID_A53_1,
		.thread_id			= 10U,
		.threshold			= 1U,
		.evt_threshold			= 0x0005U,
		.evt_error			= 0x0005U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0012_CONF_007,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_2_RESPONSE_THR012_CONF009] =			{
		.host_id			= HOST_ID_A53_2,
		.thread_id			= 12U,
		.threshold			= 1U,
		.evt_threshold			= 0x0006U,
		.evt_error			= 0x0006U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0011_CONF_008,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_3_RESPONSE_THR014_CONF010] =			{
		.host_id			= HOST_ID_A53_3,
		.thread_id			= 14U,
		.threshold			= 1U,
		.evt_threshold			= 0x0007U,
		.evt_error			= 0x0007U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0010_CONF_009,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_4_RESPONSE_THR016_CONF011] =			{
		.host_id			= HOST_ID_A53_4,
		.thread_id			= 16U,
		.threshold			= 1U,
		.evt_threshold			= 0x0008U,
		.evt_error			= 0x0008U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0009_CONF_010,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_MCU_0_R5_0_RESPONSE_THR018_CONF012] =		{
		.host_id			= HOST_ID_MCU_0_R5_0,
		.thread_id			= 18U,
		.threshold			= 1U,
		.evt_threshold			= SOC_SAFE_EVENT,
		.evt_error			= SOC_SAFE_EVENT,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0008_CONF_011,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_C7X_0_0_RESPONSE_THR020_CONF013] =			{
		.host_id			= HOST_ID_C7X_0_0,
		.thread_id			= 20U,
		.threshold			= 1U,
		.evt_threshold			= 0x0009U,
		.evt_error			= 0x0009U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0007_CONF_012,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_C7X_1_0_RESPONSE_THR022_CONF014] =			{
		.host_id			= HOST_ID_C7X_1_0,
		.thread_id			= 22U,
		.threshold			= 1U,
		.evt_threshold			= 0x000AU,
		.evt_error			= 0x000AU,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0006_CONF_013,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_A53_5_RESPONSE_THR024_CONF015] =			{
		.host_id			= HOST_ID_A53_5,
		.thread_id			= 24U,
		.threshold			= 1U,
		.evt_threshold			= SOC_SAFE_EVENT,
		.evt_error			= SOC_SAFE_EVENT,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0005_CONF_014,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_GPU_1_RESPONSE_THR026_CONF016] =			{
		.host_id			= HOST_ID_GPU_1,
		.thread_id			= 26U,
		.threshold			= 1U,
		.evt_threshold			= SOC_SAFE_EVENT,
		.evt_error			= SOC_SAFE_EVENT,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0004_CONF_015,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_DM2TIFS_RESPONSE_THR028_CONF017] =			{
		.host_id			= HOST_ID_DM2TIFS,
		.thread_id			= 28U,
		.threshold			= 1U,
		.evt_threshold			= SOC_SAFE_EVENT,
		.evt_error			= SOC_SAFE_EVENT,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0003_CONF_016,
	},
	[J722S_DMASS0_SEC_PROXY_0_RX_TIFS2DM_RESPONSE_THR030_CONF018] =			{
		.host_id			= HOST_ID_TIFS2DM,
		.thread_id			= 30U,
		.threshold			= 1U,
		.evt_threshold			= 0x000EU,
		.evt_error			= 0x000BU,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_DMASS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_DMASS0_RINGACC_0_RING_0002_CONF_017,
	},
	[J722S_SA3_SS0_SEC_PROXY_0_RX_TIFS_HSM_SEC_LOW_PRIORITY_RX_THR015_CONF019] =	{
		.host_id			= HOST_ID_TIFS,
		.thread_id			= 15U,
		.threshold			= 1U,
		.evt_threshold			= 0x0001U,
		.evt_error			= 0x0000U,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_SA3_SS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_SA3_SS0_RINGACC_0_RING_0005_CONF_019,
	},
	[J722S_SA3_SS0_SEC_PROXY_0_RX_HSM_RESPONSE_THR000_CONF020] =			{
		.host_id			= HOST_ID_HSM,
		.thread_id			= 0U,
		.threshold			= 1U,
		.evt_threshold			= SOC_SAFE_EVENT,
		.evt_error			= SOC_SAFE_EVENT,
		.secure_proxy_instance_id	= J722S_SPROXY_IDX_SA3_SS0_SEC_PROXY_0,
		.ring_config_instance_id	= J722S_SA3_SS0_RINGACC_0_RING_0004_CONF_020,
	},
};
