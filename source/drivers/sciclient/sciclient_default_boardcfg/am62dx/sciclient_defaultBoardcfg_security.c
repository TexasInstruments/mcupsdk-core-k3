/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/am62dx/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62dx/tisci_boardcfg_constraints.h>
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


#define SYSFW_TEST_HOST_ID TISCI_HOST_ID_MAIN_0_R5_0
#define OTHER_HOST_ID TISCI_HOST_ID_A53_0

const struct tisci_boardcfg_sec gBoardConfigLow_security
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    /* boardcfg_abi_rev */
    .rev = {
        .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_SEC_ABI_MAJ_VALUE,
        .tisci_boardcfg_abi_min = TISCI_BOARDCFG_SEC_ABI_MIN_VALUE,
    },

	/* boardcfg_proc_acl */
	.processor_acl_list = {
		.subhdr = {
			.magic = TISCI_BOARDCFG_PROC_ACL_MAGIC_NUM,
            .size = (uint16_t) sizeof(struct tisci_boardcfg_proc_acl),
		},
		.proc_acl_entries = {{ 0 }},
	},

	/* boardcfg_host_hierarchy */
	.host_hierarchy = {
		.subhdr = {
			.magic = TISCI_BOARDCFG_HOST_HIERARCHY_MAGIC_NUM,
            .size = (uint16_t) sizeof(struct tisci_boardcfg_host_hierarchy),
		},
		.host_hierarchy_entries = {{ 0 }},
	},

	/* OTP access configuration */
	.otp_config = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_OTP_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_extended_otp),
		},
		.write_host_id = TISCI_HOST_ID_MAIN_0_R5_0,
		/* This is an array with 32 entries */
        .otp_entry = {
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},
				{
					.host_id = TISCI_HOST_ID_ALL,
					.host_perms = 0x2,
				},

		},
	},

	/* DKEK configuration */
	.dkek_config = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_DKEK_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_dkek),
		},
		.allowed_hosts = { TISCI_HOST_ID_ALL, 0, 0, 0 },
		.allow_dkek_export_tisci = 0x5A,
		.rsvd = {0, 0, 0},
	},

	/* SA2UL configuration */
	.sa2ul_auth_cfg = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD,
            .size = 0,
		},
		.auth_resource_owner = 0,
		.enable_saul_psil_global_config_writes = 0x5A,
        .safety_host_present = 0,
        .safety_host = 0
	},

	/* Secure JTAG Unlock Configuration */
	.sec_dbg_config = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_SEC_DBG_CTRL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_secure_debug_config),
		},
		.allow_jtag_unlock = 0x5A,
		.allow_wildcard_unlock = 0x5A,
		.min_cert_rev = 0x0,
		.jtag_unlock_hosts = {0, 0, 0, 0},
	},

	.sec_handover_cfg = {
		.subhdr = {
			.magic = TISCI_BOARDCFG_SEC_HANDOVER_CFG_MAGIC_NUM,
			.size = sizeof(struct tisci_boardcfg_sec_handover),
		},
		.handover_msg_sender = 0,
		.handover_to_host_id = 0,
		.rsvd = {0,0,0,0},
	},
};
