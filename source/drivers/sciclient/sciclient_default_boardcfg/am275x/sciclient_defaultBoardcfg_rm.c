/*
 * K3 System Firmware Resource Management Configuration Data
 * Auto generated from K3 Resource Partitioning tool
 *
 * Copyright (c) 2018-2026, Texas Instruments Incorporated
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
 *  \file sciclient_defaultBoardcfg_rm.c
 *
 *  \brief File containing the rm boardcfg default data structure to
 *      send TISCI_MSG_BOARD_CONFIG_RM message.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/am275x/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am275x/tisci_boardcfg_constraints.h>
#include <drivers/sciclient/include/tisci/am275x/tisci_devices.h>

#define TISCI_RESASG_ENTRIES                                 131
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* \brief Structure to hold the RM board configuration */
struct tisci_local_rm_boardcfg {
    struct tisci_boardcfg_rm      rm_boardcfg;
    /**< Board configuration parameter */
    struct tisci_boardcfg_rm_resasg_entry resasg_entries[TISCI_RESASG_ENTRIES];
    /**< Resource assignment entries */
};

const struct tisci_local_rm_boardcfg gBoardConfigLow_rm
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    .rm_boardcfg = {
        .rev = {
            .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_RM_ABI_MAJ_VALUE,
            .tisci_boardcfg_abi_min = TISCI_BOARDCFG_RM_ABI_MIN_VALUE,
        },
        .host_cfg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_HOST_CFG_MAGIC_NUM,
                .size = (uint16_t) sizeof(struct tisci_boardcfg_rm_host_cfg),
            },
            .host_cfg_entries = {
                {
                    .host_id = TISCI_HOST_ID_C7X_0_0,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_C7X_1_0,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_0_R5_3,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_1_R5_1,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_1_R5_3,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
            },
        },
        .resasg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_RESASG_MAGIC_NUM,
                .size = (uint16_t) sizeof(struct tisci_boardcfg_rm_resasg),
            },
            .resasg_entries_size = TISCI_RESASG_ENTRIES * sizeof(struct tisci_boardcfg_rm_resasg_entry),
        },
    },
    .resasg_entries = {
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 16,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 24,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_3,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 32,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 40,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_3,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 16,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 20,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_3,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 24,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_1,
        },
        {
            .num_resource = 4,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 28,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_3,
        },
        {
            .num_resource = 32,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_TIMESYNC_EVENT_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 244,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
            .start_resource = 50176,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_UDMAP_GLOBAL_CONFIG),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 15,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 15,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 7,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
            .start_resource = 17,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
            .start_resource = 72,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
            .start_resource = 80,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
            .start_resource = 88,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 26,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
            .start_resource = 96,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
            .start_resource = 24,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
            .start_resource = 32,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
            .start_resource = 40,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 24,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
            .start_resource = 48,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 15,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 15,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 7,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN),
            .start_resource = 17,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
            .start_resource = 16,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 26,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN),
            .start_resource = 24,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
            .start_resource = 16,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 24,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_BCDMA_0, TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN),
            .start_resource = 24,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 14,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 4,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_1,
        },
        {
            .num_resource = 14,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 18,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_3,
        },
        {
            .num_resource = 35,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 45,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 35,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 45,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 16,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 84,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 16,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 100,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 14,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 156,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 14,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT),
            .start_resource = 170,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_3,
        },
        {
            .num_resource = 256,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 19,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 192,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 275,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_3,
        },
        {
            .num_resource = 256,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 467,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_1,
        },
        {
            .num_resource = 192,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 723,
            .host_id = TISCI_HOST_ID_MAIN_1_R5_3,
        },
        {
            .num_resource = 128,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 915,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 128,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 1043,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 256,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 1171,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 256,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 1171,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 109,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 1427,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 37,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_TX_CHAN_ERROR_OES),
            .start_resource = 4096,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 107,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_TX_FLOW_COMPLETION_OES),
            .start_resource = 4608,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 32,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_CHAN_ERROR_OES),
            .start_resource = 5120,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 59,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_COMPLETION_OES),
            .start_resource = 5632,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 59,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_STARVATION_OES),
            .start_resource = 6144,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 24,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_ERROR_OES),
            .start_resource = 8192,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 24,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_DATA_COMPLETION_OES),
            .start_resource = 8704,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 24,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_RING_COMPLETION_OES),
            .start_resource = 9216,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 48,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_ERROR_OES),
            .start_resource = 9728,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 48,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_DATA_COMPLETION_OES),
            .start_resource = 10240,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 48,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_RING_COMPLETION_OES),
            .start_resource = 10752,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 50,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_ERROR_OES),
            .start_resource = 11264,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 50,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_DATA_COMPLETION_OES),
            .start_resource = 11776,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 50,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_RING_COMPLETION_OES),
            .start_resource = 12288,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_UDMAP_GLOBAL_CONFIG),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 3,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 15,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 64,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_CPSW_TX_CHAN),
            .start_resource = 27,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_0_CHAN),
            .start_resource = 91,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_1_CHAN),
            .start_resource = 99,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 107,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 3,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 112,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 115,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 117,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 117,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 15,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
            .start_resource = 119,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_CPSW_RX_CHAN),
            .start_resource = 134,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_0_CHAN),
            .start_resource = 150,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_1_CHAN),
            .start_resource = 150,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_2_CHAN),
            .start_resource = 158,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_3_CHAN),
            .start_resource = 158,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 3,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 15,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_CPSW_TX_CHAN),
            .start_resource = 27,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_TX_0_CHAN),
            .start_resource = 35,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_TX_1_CHAN),
            .start_resource = 36,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 3,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 15,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 5,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_MAIN_0_R5_1,
        },
        {
            .num_resource = 3,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 5,
            .host_id = TISCI_HOST_ID_C7X_0_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 8,
            .host_id = TISCI_HOST_ID_C7X_1_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_0,
        },
        {
            .num_resource = 2,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 10,
            .host_id = TISCI_HOST_ID_WKUP_0_R5_1,
        },
        {
            .num_resource = 15,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_UNMAPPED_RX_CHAN),
            .start_resource = 12,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_CPSW_RX_CHAN),
            .start_resource = 27,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_CPSW_RX_CHAN),
            .start_resource = 27,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_0_CHAN),
            .start_resource = 28,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_0_CHAN),
            .start_resource = 43,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_1_CHAN),
            .start_resource = 29,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_1_CHAN),
            .start_resource = 43,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_2_CHAN),
            .start_resource = 30,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_2_CHAN),
            .start_resource = 51,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_3_CHAN),
            .start_resource = 31,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_PKTDMA_0, TISCI_RESASG_SUBTYPE_PKTDMA_FLOW_SAUL_RX_3_CHAN),
            .start_resource = 51,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1,
            .type = TISCI_RESASG_UTYPE (TISCI_DEV_DMASS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_ERROR_OES),
            .start_resource = 0,
            .host_id = TISCI_HOST_ID_ALL,
        },
    }
};
