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
 *  \file am62ax/sciclient_irq_rm.c
 *
 *  \brief File containing the AM62x specific interrupt management data for
 *         RM.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/sciclient/sciclient_rm_priv.h>
#include <drivers/sciclient/soc/am62ax/sciclient_irq_rm.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static struct Sciclient_rmIaUsedMapping rom_usage_DMASS0_INTAGGR_0[1U] = {
	{
		.event = 30U,
		.cleared = false,
	},
};
uint8_t vint_usage_count_DMSS_AM62_0_INTAGGR_0[184U]= {0};

static struct Sciclient_rmIaUsedMapping rom_usage_DMASS1_INTAGGR_0[1U] = {
{
    .event = 5651U,
    .cleared = false,
},
};
uint8_t vint_usage_count_DMSS_AM62_1_INTAGGR_0[8]= {0};
struct Sciclient_rmIaInst gRmIaInstances[SCICLIENT_RM_IA_NUM_INST] =
{
    {
        .dev_id             = TISCI_DEV_DMASS0_INTAGGR_0,
        .imap               = 0x48100000,
        .sevt_offset        = 0u,
        .n_sevt             = 1536u,
        .n_vint             = 184,
        .vint_usage_count   = &vint_usage_count_DMSS_AM62_0_INTAGGR_0[0],
        .v0_b0_evt          = 0,
        .rom_usage = &rom_usage_DMASS0_INTAGGR_0[0U],
		.n_rom_usage = 1,
    },
    {
        .dev_id             = TISCI_DEV_DMASS1_INTAGGR_0,
        .imap               = 0x4e0b0000,
        .sevt_offset        = 0u,
        .n_sevt             = 128u,
        .n_vint             = 8,
        .vint_usage_count   = &vint_usage_count_DMSS_AM62_1_INTAGGR_0[0],
        .v0_b0_evt          = 0,
        .rom_usage = &rom_usage_DMASS1_INTAGGR_0[0U],
		.n_rom_usage = 1,
    }
};

struct Sciclient_rmIrInst gRmIrInstances[SCICLIENT_RM_IR_NUM_INST] =
{
    {
        .dev_id         = TISCI_DEV_CMP_EVENT_INTROUTER0,
        .cfg            = 0xa30000,
        .n_inp          = 32u,
        .n_outp         = 42u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
        .cfg            = 0xa00000,
        .n_inp          = 200u,
        .n_outp         = 36u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
        .cfg            = 0x4210000,
        .n_inp          = 32u,
        .n_outp         = 13u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
        .cfg            = 0xa40000,
        .n_inp          = 20u,
        .n_outp         = 26u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
};

/* IRQ Tree definition */

/* Start of CMP_EVENT_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_0_15_to_GICSS0_spi_48_63 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_16_31 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_16_23_to_R5FSS0_CORE0_intr_48_55 = {
	.lbase = 16,
	.len = 8,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_0_7 = {
	.lbase = 24,
	.len = 8,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_34_37_to_MCU_R5FSS0_CORE0_cpu0_intr_58_61 = {
	.lbase = 34,
	.len = 4,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 58,
};
const struct Sciclient_rmIrqIf CMP_EVENT_INTROUTER0_outp_38_41_to_HSM0_nvic_51_54 = {
	.lbase = 38,
	.len = 4,
	.rid = TISCI_DEV_HSM0,
	.rbase = 51,
};
const struct Sciclient_rmIrqIf * const tisci_if_CMP_EVENT_INTROUTER0[] = {
	&CMP_EVENT_INTROUTER0_outp_0_15_to_GICSS0_spi_48_63,
	&CMP_EVENT_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_16_31,
	&CMP_EVENT_INTROUTER0_outp_16_23_to_R5FSS0_CORE0_intr_48_55,
	&CMP_EVENT_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_0_7,
	&CMP_EVENT_INTROUTER0_outp_34_37_to_MCU_R5FSS0_CORE0_cpu0_intr_58_61,
	&CMP_EVENT_INTROUTER0_outp_38_41_to_HSM0_nvic_51_54,
};
static const struct Sciclient_rmIrqNode tisci_irq_CMP_EVENT_INTROUTER0 = {
	.id = TISCI_DEV_CMP_EVENT_INTROUTER0,
	.n_if = 6,
	.p_if = &tisci_if_CMP_EVENT_INTROUTER0[0],
};

/* Start of MAIN_GPIOMUX_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_GICSS0_spi_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_R5FSS0_CORE0_intr_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_0_15 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_7_to_HSM0_nvic_208_215 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_HSM0,
	.rbase = 208,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_16_23 = {
	.lbase = 24,
	.len = 8,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_22_23_to_DMASS0_INTAGGR_0_intaggr_levi_pend_24_25 = {
	.lbase = 22,
	.len = 2,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 24,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_34_35_to_MCU_R5FSS0_CORE0_cpu0_intr_32_33 = {
	.lbase = 34,
	.len = 2,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf * const tisci_if_MAIN_GPIOMUX_INTROUTER0[] = {
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_GICSS0_spi_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_R5FSS0_CORE0_intr_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_0_15,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_7_to_HSM0_nvic_208_215,
	&MAIN_GPIOMUX_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_16_23,
	&MAIN_GPIOMUX_INTROUTER0_outp_22_23_to_DMASS0_INTAGGR_0_intaggr_levi_pend_24_25,
	&MAIN_GPIOMUX_INTROUTER0_outp_34_35_to_MCU_R5FSS0_CORE0_cpu0_intr_32_33,
};
static const struct Sciclient_rmIrqNode tisci_irq_MAIN_GPIOMUX_INTROUTER0 = {
	.id = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.n_if = 7,
	.p_if = &tisci_if_MAIN_GPIOMUX_INTROUTER0[0],
};

/* Start of WKUP_MCU_GPIOMUX_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_GICSS0_spi_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_R5FSS0_CORE0_intr_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V0_CLEC_gic_spi_72_75 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 72,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_MCU_R5FSS0_CORE0_cpu0_intr_104_107 = {
	.lbase = 4,
	.len = 4,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_HSM0_nvic_78_81 = {
	.lbase = 4,
	.len = 4,
	.rid = TISCI_DEV_HSM0,
	.rbase = 78,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event0_88_91 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 88,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event1_92_95 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 92,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event2_96_99 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 96,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_MCU_GPIOMUX_INTROUTER0[] = {
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_GICSS0_spi_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_R5FSS0_CORE0_intr_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V0_CLEC_gic_spi_72_75,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_MCU_R5FSS0_CORE0_cpu0_intr_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_HSM0_nvic_78_81,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event0_88_91,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event1_92_95,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event2_96_99,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_MCU_GPIOMUX_INTROUTER0 = {
	.id = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.n_if = 8,
	.p_if = &tisci_if_WKUP_MCU_GPIOMUX_INTROUTER0[0],
};

/* Start of TIMESYNC_EVENT_ROUTER0 interface definition */
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_0_7_to_DMASS0_INTAGGR_0_intaggr_levi_pend_8_15 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_10_10_to_CPSW0_cpts_hw1_push_0_0 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_11_11_to_CPSW0_cpts_hw2_push_1_1 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_12_12_to_CPSW0_cpts_hw3_push_2_2 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_13_13_to_CPSW0_cpts_hw4_push_3_3 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_14_14_to_CPSW0_cpts_hw5_push_4_4 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_15_15_to_CPSW0_cpts_hw6_push_5_5 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_16_16_to_CPSW0_cpts_hw7_push_6_6 = {
	.lbase = 16,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_ROUTER0_outl_17_17_to_CPSW0_cpts_hw8_push_7_7 = {
	.lbase = 17,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMESYNC_EVENT_ROUTER0[] = {
	&TIMESYNC_EVENT_ROUTER0_outl_0_7_to_DMASS0_INTAGGR_0_intaggr_levi_pend_8_15,
	&TIMESYNC_EVENT_ROUTER0_outl_10_10_to_CPSW0_cpts_hw1_push_0_0,
	&TIMESYNC_EVENT_ROUTER0_outl_11_11_to_CPSW0_cpts_hw2_push_1_1,
	&TIMESYNC_EVENT_ROUTER0_outl_12_12_to_CPSW0_cpts_hw3_push_2_2,
	&TIMESYNC_EVENT_ROUTER0_outl_13_13_to_CPSW0_cpts_hw4_push_3_3,
	&TIMESYNC_EVENT_ROUTER0_outl_14_14_to_CPSW0_cpts_hw5_push_4_4,
	&TIMESYNC_EVENT_ROUTER0_outl_15_15_to_CPSW0_cpts_hw6_push_5_5,
	&TIMESYNC_EVENT_ROUTER0_outl_16_16_to_CPSW0_cpts_hw7_push_6_6,
	&TIMESYNC_EVENT_ROUTER0_outl_17_17_to_CPSW0_cpts_hw8_push_7_7,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMESYNC_EVENT_ROUTER0 = {
	.id = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.n_if = 9,
	.p_if = &tisci_if_TIMESYNC_EVENT_ROUTER0[0],
};

/* Start of CPSW0 interface definition */
const struct Sciclient_rmIrqIf CPSW0_cpts_comp_0_0_to_CMP_EVENT_INTROUTER0_in_24_24 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMP_EVENT_INTROUTER0,
	.rbase = 24,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_genf0_1_1_to_TIMESYNC_EVENT_ROUTER0_in_16_16 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_genf1_2_2_to_TIMESYNC_EVENT_ROUTER0_in_17_17 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 17,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_sync_3_3_to_TIMESYNC_EVENT_ROUTER0_in_18_18 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 18,
};
const struct Sciclient_rmIrqIf * const tisci_if_CPSW0[] = {
	&CPSW0_cpts_comp_0_0_to_CMP_EVENT_INTROUTER0_in_24_24,
	&CPSW0_cpts_genf0_1_1_to_TIMESYNC_EVENT_ROUTER0_in_16_16,
	&CPSW0_cpts_genf1_2_2_to_TIMESYNC_EVENT_ROUTER0_in_17_17,
	&CPSW0_cpts_sync_3_3_to_TIMESYNC_EVENT_ROUTER0_in_18_18,
};
static const struct Sciclient_rmIrqNode tisci_irq_CPSW0 = {
	.id = TISCI_DEV_CPSW0,
	.n_if = 4,
	.p_if = &tisci_if_CPSW0[0],
};

/* Start of DMASS0_INTAGGR_0 interface definition */
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_GICSS0_spi_64_103 = {
	.lbase = 0,
	.len = 40,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V0_CLEC_gic_spi_32_71 = {
	.lbase = 0,
	.len = 40,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_84_99_to_C7X256V0_CLEC_soc_events_in_209_224 = {
	.lbase = 84,
	.len = 16,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 209,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_72_79_to_R5FSS0_CORE0_intr_8_15 = {
	.lbase = 72,
	.len = 8,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_40_71_to_R5FSS0_CORE0_intr_64_95 = {
	.lbase = 40,
	.len = 32,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_136_151_to_HSM0_nvic_176_191 = {
	.lbase = 136,
	.len = 16,
	.rid = TISCI_DEV_HSM0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_168_183_to_MCU_R5FSS0_CORE0_cpu0_intr_64_79 = {
	.lbase = 168,
	.len = 16,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf * const tisci_if_DMASS0_INTAGGR_0[] = {
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_GICSS0_spi_64_103,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V0_CLEC_gic_spi_32_71,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_84_99_to_C7X256V0_CLEC_soc_events_in_209_224,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_72_79_to_R5FSS0_CORE0_intr_8_15,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_40_71_to_R5FSS0_CORE0_intr_64_95,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_136_151_to_HSM0_nvic_176_191,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_168_183_to_MCU_R5FSS0_CORE0_cpu0_intr_64_79,
};
static const struct Sciclient_rmIrqNode tisci_irq_DMASS0_INTAGGR_0 = {
	.id = TISCI_DEV_DMASS0_INTAGGR_0,
	.n_if = 7,
	.p_if = &tisci_if_DMASS0_INTAGGR_0[0],
};

/* Start of TIMER0 interface definition */
const struct Sciclient_rmIrqIf TIMER0_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_0_0 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER0[] = {
	&TIMER0_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_0_0,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER0 = {
	.id = TISCI_DEV_TIMER0,
	.n_if = 1,
	.p_if = &tisci_if_TIMER0[0],
};

/* Start of TIMER1 interface definition */
const struct Sciclient_rmIrqIf TIMER1_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_1_1 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER1[] = {
	&TIMER1_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_1_1,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER1 = {
	.id = TISCI_DEV_TIMER1,
	.n_if = 1,
	.p_if = &tisci_if_TIMER1[0],
};

/* Start of TIMER2 interface definition */
const struct Sciclient_rmIrqIf TIMER2_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_2_2 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER2[] = {
	&TIMER2_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_2_2,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER2 = {
	.id = TISCI_DEV_TIMER2,
	.n_if = 1,
	.p_if = &tisci_if_TIMER2[0],
};

/* Start of TIMER3 interface definition */
const struct Sciclient_rmIrqIf TIMER3_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_3_3 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER3[] = {
	&TIMER3_timer_pwm_0_0_to_TIMESYNC_EVENT_ROUTER0_in_3_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER3 = {
	.id = TISCI_DEV_TIMER3,
	.n_if = 1,
	.p_if = &tisci_if_TIMER3[0],
};

/* Start of WKUP_GTC0 interface definition */
const struct Sciclient_rmIrqIf WKUP_GTC0_gtc_push_event_0_0_to_TIMESYNC_EVENT_ROUTER0_in_11_11 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_GTC0[] = {
	&WKUP_GTC0_gtc_push_event_0_0_to_TIMESYNC_EVENT_ROUTER0_in_11_11,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_GTC0 = {
	.id = TISCI_DEV_WKUP_GTC0,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_GTC0[0],
};

/* Start of GPIO0 interface definition */
const struct Sciclient_rmIrqIf GPIO0_gpio_0_89_to_MAIN_GPIOMUX_INTROUTER0_in_0_89 = {
	.lbase = 0,
	.len = 90,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf GPIO0_gpio_90_91_to_MAIN_GPIOMUX_INTROUTER0_in_176_177 = {
	.lbase = 90,
	.len = 2,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIO0_gpio_bank_92_97_to_MAIN_GPIOMUX_INTROUTER0_in_190_195 = {
	.lbase = 92,
	.len = 6,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 190,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO0[] = {
	&GPIO0_gpio_0_89_to_MAIN_GPIOMUX_INTROUTER0_in_0_89,
	&GPIO0_gpio_90_91_to_MAIN_GPIOMUX_INTROUTER0_in_176_177,
	&GPIO0_gpio_bank_92_97_to_MAIN_GPIOMUX_INTROUTER0_in_190_195,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO0 = {
	.id = TISCI_DEV_GPIO0,
	.n_if = 3,
	.p_if = &tisci_if_GPIO0[0],
};

/* Start of GPIO1 interface definition */
const struct Sciclient_rmIrqIf GPIO1_gpio_0_71_to_MAIN_GPIOMUX_INTROUTER0_in_90_161 = {
	.lbase = 0,
	.len = 72,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 90,
};
const struct Sciclient_rmIrqIf GPIO1_gpio_bank_72_76_to_MAIN_GPIOMUX_INTROUTER0_in_180_184 = {
	.lbase = 72,
	.len = 5,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 180,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO1[] = {
	&GPIO1_gpio_0_71_to_MAIN_GPIOMUX_INTROUTER0_in_90_161,
	&GPIO1_gpio_bank_72_76_to_MAIN_GPIOMUX_INTROUTER0_in_180_184,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO1 = {
	.id = TISCI_DEV_GPIO1,
	.n_if = 2,
	.p_if = &tisci_if_GPIO1[0],
};

/* Start of MCU_GPIO0 interface definition */
const struct Sciclient_rmIrqIf MCU_GPIO0_gpio_0_23_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_0_23 = {
	.lbase = 0,
	.len = 24,
	.rid = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf MCU_GPIO0_gpio_bank_24_25_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_30_31 = {
	.lbase = 24,
	.len = 2,
	.rid = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.rbase = 30,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_GPIO0[] = {
	&MCU_GPIO0_gpio_0_23_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_0_23,
	&MCU_GPIO0_gpio_bank_24_25_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_30_31,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_GPIO0 = {
	.id = TISCI_DEV_MCU_GPIO0,
	.n_if = 2,
	.p_if = &tisci_if_MCU_GPIO0[0],
};

/* Start of GPMC0 interface definition */
const struct Sciclient_rmIrqIf GPMC0_gpmc_sdmareq_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_26_26 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 26,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPMC0[] = {
	&GPMC0_gpmc_sdmareq_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_26_26,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPMC0 = {
	.id = TISCI_DEV_GPMC0,
	.n_if = 1,
	.p_if = &tisci_if_GPMC0[0],
};

/* Start of EPWM0 interface definition */
const struct Sciclient_rmIrqIf EPWM0_epwm_synco_o_0_0_to_TIMESYNC_EVENT_ROUTER0_in_8_8 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM0[] = {
	&EPWM0_epwm_synco_o_0_0_to_TIMESYNC_EVENT_ROUTER0_in_8_8,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM0 = {
	.id = TISCI_DEV_EPWM0,
	.n_if = 1,
	.p_if = &tisci_if_EPWM0[0],
};

/* Start of MCRC64_0 interface definition */
const struct Sciclient_rmIrqIf MCRC64_0_dma_event_0_3_to_DMASS0_INTAGGR_0_intaggr_levi_pend_28_31 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 28,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCRC64_0[] = {
	&MCRC64_0_dma_event_0_3_to_DMASS0_INTAGGR_0_intaggr_levi_pend_28_31,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCRC64_0 = {
	.id = TISCI_DEV_MCRC64_0,
	.n_if = 1,
	.p_if = &tisci_if_MCRC64_0[0],
};

/* Start of DEBUGSS0 interface definition */
const struct Sciclient_rmIrqIf DEBUGSS0_davdma_level_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_27_27 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 27,
};
const struct Sciclient_rmIrqIf * const tisci_if_DEBUGSS0[] = {
	&DEBUGSS0_davdma_level_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_27_27,
};
static const struct Sciclient_rmIrqNode tisci_irq_DEBUGSS0 = {
	.id = TISCI_DEV_DEBUGSS0,
	.n_if = 1,
	.p_if = &tisci_if_DEBUGSS0[0],
};

/* Start of DMASS1_INTAGGR_0 interface definition */
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_GICSS0_spi_237_244 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 237,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_R5FSS0_CORE0_intr_129_132 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 129,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_4_4_to_R5FSS0_CORE0_intr_150_150 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_5_7_to_R5FSS0_CORE0_intr_158_160 = {
	.lbase = 5,
	.len = 3,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 158,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_MCU_R5FSS0_CORE0_cpu0_intr_129_132 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 129,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_4_4_to_MCU_R5FSS0_CORE0_cpu0_intr_150_150 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_5_7_to_MCU_R5FSS0_CORE0_cpu0_intr_158_160 = {
	.lbase = 5,
	.len = 3,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 158,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_C7X256V0_CLEC_gic_spi_205_208 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 205,
};
const struct Sciclient_rmIrqIf * const tisci_if_DMASS1_INTAGGR_0[] = {
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_GICSS0_spi_237_244,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_R5FSS0_CORE0_intr_129_132,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_4_4_to_R5FSS0_CORE0_intr_150_150,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_5_7_to_R5FSS0_CORE0_intr_158_160,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_MCU_R5FSS0_CORE0_cpu0_intr_129_132,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_4_4_to_MCU_R5FSS0_CORE0_cpu0_intr_150_150,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_5_7_to_MCU_R5FSS0_CORE0_cpu0_intr_158_160,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_3_to_C7X256V0_CLEC_gic_spi_205_208,
};
static const struct Sciclient_rmIrqNode tisci_irq_DMASS1_INTAGGR_0 = {
	.id = TISCI_DEV_DMASS1_INTAGGR_0,
	.n_if = 8,
	.p_if = &tisci_if_DMASS1_INTAGGR_0[0],
};


const struct Sciclient_rmIrqNode *const gRmIrqTree[RM_IRQ_TREE_MAX] = {
	&tisci_irq_CMP_EVENT_INTROUTER0,
	&tisci_irq_MAIN_GPIOMUX_INTROUTER0,
	&tisci_irq_WKUP_MCU_GPIOMUX_INTROUTER0,
	&tisci_irq_TIMESYNC_EVENT_ROUTER0,
	&tisci_irq_CPSW0,
	&tisci_irq_DMASS0_INTAGGR_0,
	&tisci_irq_TIMER0,
	&tisci_irq_TIMER1,
	&tisci_irq_TIMER2,
	&tisci_irq_TIMER3,
	&tisci_irq_WKUP_GTC0,
	&tisci_irq_GPIO0,
	&tisci_irq_GPIO1,
	&tisci_irq_MCU_GPIO0,
	&tisci_irq_GPMC0,
	&tisci_irq_EPWM0,
	&tisci_irq_MCRC64_0,
	&tisci_irq_DEBUGSS0,
	&tisci_irq_DMASS1_INTAGGR_0,
};

const uint32_t gRmIrqTreeCount = sizeof(gRmIrqTree)/sizeof(gRmIrqTree[0]);
