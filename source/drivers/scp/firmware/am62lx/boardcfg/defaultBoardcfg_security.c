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
/**
 *  \file am62lx/defaultBoardcfg_security.c
 *
 *  \brief File containing the security boardcfg data structure.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <inttypes.h>
#include <stdint.h>

/* ========================================================================== */
/*                            Structure declaration                           */
/* ========================================================================== */

struct boardcfg_substructure_header {
	uint16_t	magic;
	uint16_t	size;
} __attribute__((__packed__));

struct boardcfg_abi_rev {
	uint8_t	boardcfg_abi_maj;
	uint8_t	boardcfg_abi_min;
} __attribute__((__packed__));

struct boardcfg_proc_acl_entry {
	uint8_t	processor_id;
	uint8_t	proc_access_master;
	uint8_t	proc_access_secondary[3];
} __attribute__((__packed__));

struct boardcfg_proc_acl {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_proc_acl_entry		proc_acl_entries[32];
} __attribute__((__packed__));

struct boardcfg_host_hierarchy_entry {
	uint8_t	host_id;
	uint8_t	supervisor_host_id;
} __attribute__((__packed__));

struct boardcfg_host_hierarchy {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_host_hierarchy_entry	host_hierarchy_entries[32];
} __attribute__((__packed__));

struct boardcfg_extended_otp_entry {
	uint8_t	host_id;
	uint8_t	host_perms;
} __attribute__((__packed__));

struct boardcfg_extended_otp {
	struct boardcfg_substructure_header	subhdr;
	struct boardcfg_extended_otp_entry	otp_entry[32];
	uint8_t					write_host_id;
} __attribute__((__packed__));

struct boardcfg_dkek {
	struct boardcfg_substructure_header	subhdr;
	uint8_t					allowed_hosts[4];
	uint8_t					allow_dkek_export_tisci;
	uint8_t					rsvd[3];
} __attribute__((__packed__));

struct boardcfg_sec_resv0 {
	uint8_t resv[8];
};

struct boardcfg_secure_debug_config {
	struct boardcfg_substructure_header	subhdr;
	uint8_t					allow_jtag_unlock;
	uint8_t					allow_wildcard_unlock;
	uint8_t					allowed_debug_level_rsvd;
	uint8_t					rsvd;
	uint32_t					min_cert_rev;
	uint8_t					jtag_unlock_hosts[4];
} __attribute__((__packed__));

struct boardcfg_sec_resv1 {
	uint8_t resv[8];
};

struct boardcfg_sec {
	struct boardcfg_abi_rev			rev;
	struct boardcfg_proc_acl		processor_acl_list;
	struct boardcfg_host_hierarchy		host_hierarchy;
	struct boardcfg_extended_otp		otp_config;
	struct boardcfg_dkek		dkek_config;
	struct boardcfg_sec_resv0	resv0;
	struct boardcfg_secure_debug_config	sec_dbg_config;
	struct boardcfg_sec_resv1	resv1;
} __attribute__((__packed__));

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

struct boardcfg_sec test_boardcfg_security = {
	/* boardcfg_abi_rev */
	.rev = {
		.boardcfg_abi_maj = 0x0,
		.boardcfg_abi_min = 0x1,
	},

	/* boardcfg_proc_acl */
	.processor_acl_list = {
		.subhdr = {
			.magic = 0xF1EA,
			.size = sizeof(struct boardcfg_proc_acl),
		},
		.proc_acl_entries = {0},
	},

	/* boardcfg_host_hierarchy */
	.host_hierarchy = {
		.subhdr = {
			.magic = 0x8D27,
			.size = sizeof(struct boardcfg_host_hierarchy),
		},
		.host_hierarchy_entries = {0},
	},
	/* OTP access configuration */
	.otp_config = {
		.subhdr = {
			.magic = 0x4081,
			.size = sizeof(struct boardcfg_extended_otp),
		},
		.otp_entry = {0},
	},
	.dkek_config = {
		.subhdr = {
			.magic = 0x5170,
			.size = sizeof(struct boardcfg_dkek),
		},
		.allowed_hosts = { 10U, 128, 0, 0 },
		.allow_dkek_export_tisci = 0x5A,
		.rsvd = {0, 0, 0},
	},

	.resv0 = {0},

	.sec_dbg_config = {
		.subhdr = {
			.magic = 0x42AF,
			.size = sizeof(struct boardcfg_secure_debug_config),
		},
        .allow_jtag_unlock = 0U,
        .allow_wildcard_unlock = 0x0,
        .min_cert_rev = 0x0,
		.jtag_unlock_hosts = {0, 0, 0, 0},
    },

	.resv1 = {0},
};
