/*
 * Copyright (c) 2022, Texas Instruments Incorporated
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
#include <drivers/sciclient/include/tisci/am62ax/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_boardcfg_constraints.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_devices.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const struct tisci_boardcfg gBoardConfigLow_debug
__attribute__((aligned(128))) =
{
	/* boardcfg_abi_rev */
	.rev = {
		.tisci_boardcfg_abi_maj = TISCI_BOARDCFG_ABI_MAJ_VALUE,
		.tisci_boardcfg_abi_min = TISCI_BOARDCFG_ABI_MIN_VALUE,
	},

	/* boardcfg_control */
	.control = {
		.subhdr = {
			.magic = TISCI_BOARDCFG_CONTROL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_control),
		},
		.main_isolation_enable = 0x5A,
		.main_isolation_hostid = 0x2,
	},

	/* boardcfg sec_proxy */
	.secproxy = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_SECPROXY_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_secproxy),
		},
		.scaling_factor = 0x1,
		.scaling_profile = 0x1,
		.disable_main_nav_secure_proxy = 0,
	},

	/* boardcfg_msmc */
	.msmc = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_MSMC_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_msmc),
		},
		.msmc_cache_size = 0x10,
	},

	/* boardcfg_dbg_cfg */
	.debug_cfg = {
		.subhdr = {
            .magic = TISCI_BOARDCFG_DBG_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_dbg_cfg),
		},

        #ifdef SYSFW_TRACE_ENABLE
        .trace_dst_enables = (TISCI_BOARDCFG_TRACE_DST_UART0 |
                              TISCI_BOARDCFG_TRACE_DST_ITM |
                              TISCI_BOARDCFG_TRACE_DST_MEM),
        .trace_src_enables = (TISCI_BOARDCFG_TRACE_SRC_PM |
                              TISCI_BOARDCFG_TRACE_SRC_RM |
                              TISCI_BOARDCFG_TRACE_SRC_SEC |
                              TISCI_BOARDCFG_TRACE_SRC_BASE |
                              TISCI_BOARDCFG_TRACE_SRC_USER |
                              TISCI_BOARDCFG_TRACE_SRC_SUPR)
        #else
        .trace_dst_enables = 0,
        .trace_src_enables = 0,
        #endif
	},
};
