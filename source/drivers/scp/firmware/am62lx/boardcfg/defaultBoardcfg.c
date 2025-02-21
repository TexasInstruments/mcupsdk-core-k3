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
 *  \file am62lx/defaultBoardcfg.c
 *
 *  \brief File containing the default board config data structure.
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

struct boardcfg_control {
	struct boardcfg_substructure_header	subhdr;
	uint8_t					main_isolation_enable;
	uint16_t					main_isolation_hostid;
} __attribute__((__packed__));

struct boardcfg_resv0 {
	uint8_t resv[7];
} __attribute__((__packed__));

struct boardcfg_resv1 {
	uint8_t resv[5];
} __attribute__((__packed__));

struct boardcfg_dbg_cfg {
	struct boardcfg_substructure_header	subhdr;
	uint16_t					trace_dst_enables;
	uint16_t					trace_src_enables;
} __attribute__((__packed__));

struct boardcfg {
	struct boardcfg_abi_rev		rev;
	struct boardcfg_control		control;
	struct boardcfg_resv0		resv0;
	struct boardcfg_resv1		resv1;
	struct boardcfg_dbg_cfg		debug_cfg;
} __attribute__((__packed__));

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

struct boardcfg test_boardcfg = {
	/* boardcfg_abi_rev */
	.rev = {
		.boardcfg_abi_maj = 0x0,
		.boardcfg_abi_min = 0x1,
	},

	/* boardcfg_control */
	.control = {
		.subhdr = {
			.magic = 0xC1D3U,
			.size = sizeof(struct boardcfg_control),
		},
		.main_isolation_enable = 0x5A,
		.main_isolation_hostid = 0x2,
	},

	/* boardcfg resv 0 */
	.resv0 = { 0u },

	/* boardcfg_msmc */
	.resv1 = { 0u },

	/* boardcfg_dbg_cfg */
	.debug_cfg = {
		.subhdr = {
			.magic = 0x020CU,
			.size = sizeof(struct boardcfg_dbg_cfg),
		},

		.trace_dst_enables = 0x0000,
		.trace_src_enables = 0x0000,
	},
};

