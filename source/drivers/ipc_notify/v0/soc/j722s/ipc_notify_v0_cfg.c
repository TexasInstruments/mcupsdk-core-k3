/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <drivers/ipc_notify/v0/ipc_notify_v0.h>

/* values to use when a mailbox config is not used in gIpcNotifyMailboxConfig */
#define MAILBOX_UNUSED      0U, 0U, 0U

/* All mailbox base addresses */
uint32_t gIpcNotifyMailboxBaseAddr[IPC_NOTIFY_MAILBOX_MAX_INSTANCES+1] = {
    0x29000000U,
    0x29010000U,
    0x29020000U,
    0x29030000U,
    0x29040000U,
    0x29050000U,
    0x29060000U,
    0x29070000U,
    0x0, /* MUST be terminated by 0x0 */
};

/* Pre-defined mailbox config to allow any CPU to send and receive messages from any CPU on this SOC
 *
 * Each element consists of [maibox base addr, hw fifo, user id]
 * These assignments need to be in sync with gIpcNotifyInterruptConfig* done later below,
 *
 * This is a 2D array
 * - 1st indexed by source core ID
 * - then indexed by destination core ID
 *
 * --------------------------------
 *  Cluster | FIFO |     IPC
 * --------------------------------
 *   0      |  0   | WKUP R5F -> A53SS0_0
 *   0      |  1   | A53SS0_0 -> WKUP R5F
 *   0      |  2   | MCU R5F  -> A53SS0_0
 *   0      |  3   | A53SS0_0 -> MCU R5F
 *   0      |  4   | A53SS1_0 -> WKUP R5F
 *   0      |  5   | WKUP R5F -> A53SS1_0
 *   0      |  6   | A53SS1_0 -> MCU R5F
 *   0      |  7   | MCU R5F  -> A53SS1_0
 *   0      |  8   | A53SS1_0 -> A53SS0_0
 *   0      |  9   | A53SS0_0 -> A53SS1_0
 *
 *   1      |  0   | WKUP R5F -> MCU R5F
 *   1      |  1   | MAIN R5F -> MCU R5F
 *   1      |  2   | C75SS0_0 -> MCU R5F
 *   1      |  3   | C75SS1_0 -> MCU R5F
 *
 *   2      |  0   | MAIN R5F -> A53SS0_0
 *   2      |  1   | A53SS0_0 -> MAIN R5F
 *   2      |  2   | C75SS0_0 -> A53SS0_0
 *   2      |  3   | A53SS0_0 -> C75SS0_0
 *   2      |  4   | A53SS1_0 -> MAIN R5F
 *   2      |  5   | MAIN R5F -> A53SS1_0
 *   2      |  6   | A53SS1_0 -> C75SS0_0
 *   2      |  7   | C75SS0_0 -> A53SS1_0
 *
 *   3      |  0   | C75SS1_0 -> A53SS0_0
 *   3      |  1   | A53SS0_0 -> C75SS1_0
 *   3      |  2   | A53SS1_0 -> C75SS1_0
 *   3      |  3   | C75SS1_0 -> A53SS1_0
 *
 *   4      |  0   | MCU R5F  -> WKUP R5F
 *   4      |  1   | MAIN R5F -> WKUP R5F
 *   4      |  2   | C75SS0_0 -> WKUP R5F
 *   4      |  3   | C75SS1_0 -> WKUP R5F
 *
 *   5      |  0   | WKUP R5F -> MAIN R5F
 *   5      |  1   | MCU R5F  -> MAIN R5F
 *   5      |  2   | C75SS0_0 -> MAIN R5F
 *   5      |  3   | C75SS1_0 -> MAIN R5F
 *
 *   6      |  0   | WKUP R5F -> C75SS0_0
 *   6      |  1   | MCU R5F  -> C75SS0_0
 *   6      |  2   | MAIN R5F -> C75SS0_0
 *   6      |  3   | C75SS1_0 -> C75SS0_0
 *
 *   7      |  0   | WKUP R5F -> C75SS1_0
 *   7      |  1   | MCU R5F  -> C75SS1_0
 *   7      |  2   | MAIN R5F -> C75SS1_0
 *   7      |  3   | C75SS0_0 -> C75SS1_0
 *
 * User ID (different IDs are used on different MB clusters):
 *     MCU R5F Rx : 2, 0
 *     WKUP R5F Rx: 1, 0
 *     MAIN R5F Rx: 1, 0
 *     C75SS0 Rx  : 2, 0
 *     C75SS1 Rx  : 1, 0
 *     A53SS0_0 Rx: 0
 *     A53SS0_1 Rx: n/a
 *     A53SS1_0 Rx: 3
 *     A53SS1_1 Rx: n/a
 */
IpcNotify_MailboxConfig gIpcNotifyMailboxConfig[CSL_CORE_ID_MAX][CSL_CORE_ID_MAX] =
{
    /* from MCU R5FSS0-0 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            0U, 2U, 3U
        },
        { /* to MAIN R5FSS0-0 */
            6U, 2U, 3U
        },
        { /* to C75SS0_0 */
            6U, 4U, 1U
        },
        { /* to C75SS1_0 */
            7U, 2U, 2U
        },
        { /* to A53SS0_0 */
            1U, 0U, 0U
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from WKUP R5FSS0-0 */
    {
        { /* to MCU R5FSS0-0 */
            0U, 3U, 2U
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to MAIN R5FSS0-0 */
            4U, 2U, 3U
        },
        { /* to C75SS0_0 */
            4U, 3U, 1U
        },
        { /* to C75SS1_0 */
            5U, 2U, 2U
        },
        { /* to A53SS0_0 */
            0U, 0U, 0U
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from MAIN R5FSS0-0 */
    {
        { /* to MCU R5FSS0-0 */
            6U, 0U, 0U
        },
        { /* to WKUP R5FSS0-0 */
            4U, 0U, 0U
        },
        { /* to MAIN R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS0_0 */
            6U, 5U, 1U
        },
        { /* to C75SS1_0 */
            7U, 3U, 2U
        },
        { /* to A53SS0_0 */
            3U, 0U, 0U
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from C75SS0_0 */
    {
        { /* to MCU R5FSS0-0 */
            6U, 1U, 0U
        },
        { /* to WKUP R5FSS0-0 */
            4U, 1U, 0U
        },
        { /* to MAIN R5FSS0-0 */
            6U, 3U, 3U
        },
        { /* to C75SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS1_0 */
            5U, 3U, 2U
        },
        { /* to A53SS0_0 */
            2U, 0U, 0U
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from C75SS1_0 */
    {
        { /* to MCU R5FSS0-0 */
            7U, 0U, 0U
        },
        { /* to WKUP R5FSS0-0 */
            5U, 0U, 0U
        },
        { /* to MAIN R5FSS0-0 */
            7U, 1U, 3U
        },
        { /* to C75SS0_0 */
            5U, 1U, 1U
        },
        { /* to C75SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_0 */
            3U, 2U, 0U
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS0_0 */
    {
        { /* to MCU R5FSS0-0 */
            1U, 1U, 2U
        },
        { /* to WKUP R5FSS0-0 */
            0U, 1U, 3U
        },
        { /* to MAIN R5FSS0-0 */
            3U, 1U, 3U
        },
        { /* to C75SS0_0 */
            2U, 1U, 1U
        },
        { /* to C75SS1_0 */
            3U, 3U, 2U
        },
        { /* to A53SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS0_1 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to MAIN R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS1_0 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to MAIN R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS1_1 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to MAIN R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
    /* from HSM_R5FSS0_0 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to MAIN R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to C75SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS0_1 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_0 */
            MAILBOX_UNUSED
        },
        { /* to A53SS1_1 */
            MAILBOX_UNUSED
        },
        { /* to HSM_R5FSS0_0 */
            MAILBOX_UNUSED
        },
    },
};

/* Interrupt config for MCU_R5FSS0_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM   (4u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_mcu_r5fss0_0[IPC_NOTIFY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM] = {
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_2,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0
        },
    },
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_1_MAILBOX_CLUSTER_PEND_2,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_6_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 2U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MAIN_R5FSS0_0,
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_7_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS1_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_mcu_r5fss0_0= IPC_NOTIFY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM;

/* Interrupt config for WKUP_R5FSS0_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM   (3u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_wkup_r5fss0_0[IPC_NOTIFY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM] = {
    {
        .intNum = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on WKUP_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0,
            CSL_CORE_ID_MCU_R5FSS0_0
        },
    },
    {
        .intNum = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_4_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on WKUP_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MAIN_R5FSS0_0,
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_5_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on WKUP_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS1_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_wkup_r5fss0_0 = IPC_NOTIFY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM;

/* Interrupt config for MAIN_R5FSS0_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_MAIN_R5FSS0_0_NUM   (4u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_main_r5fss0_0[IPC_NOTIFY_INTERRUPT_CONFIG_MAIN_R5FSS0_0_NUM] = {
    {
        .intNum = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_3_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on MAIN_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_4_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on MAIN_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0
        },
    },
    {
        .intNum = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_6_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on MAIN_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0,
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_7_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on MAIN_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS1_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_main_r5fss0_0 = IPC_NOTIFY_INTERRUPT_CONFIG_MAIN_R5FSS0_0_NUM;

/* Interrupt config for C75SS0_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_C75SS0_0_NUM   (4u)
#define CLEC0_SOC_INT_START                        (192u)   /* (192 - soc interrupt start, ref: clec_spec: am62a_soc_event_out_mapping)*/
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_c75ss0_0[IPC_NOTIFY_INTERRUPT_CONFIG_C75SS0_0_NUM] = {
    {
        .intNum = (59U), /* interrupt line on C75SS0_0 CPU */
        .eventId = (CLEC0_SOC_INT_START + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_1), /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = (60U),   /* interrupt line on C75SS0_0 CPU */
        .eventId = (CLEC0_SOC_INT_START + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_4_MAILBOX_CLUSTER_PEND_1), /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0
        },
    },
    {
        .intNum = (61U),   /* interrupt line on C75SS0_0 CPU */
        .eventId = (CLEC0_SOC_INT_START + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_5_MAILBOX_CLUSTER_PEND_1), /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS1_0
        },
    },
    {
        .intNum = (62U),   /* interrupt line on C75SS0_0 CPU */
        .eventId = (CLEC0_SOC_INT_START + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_6_MAILBOX_CLUSTER_PEND_1), /* CSL int num + CLEC SOC offset */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0,
            CSL_CORE_ID_MAIN_R5FSS0_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_c75ss0_0 = IPC_NOTIFY_INTERRUPT_CONFIG_C75SS0_0_NUM;

/* Interrupt config for C75SS1_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_C75SS1_0_NUM   (3u)
#define CLEC1_SOC_INT_START                        (192u)   /* (192 - soc interrupt start, ref: clec_spec: am62a_soc_event_out_mapping)*/
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_c75ss1_0[IPC_NOTIFY_INTERRUPT_CONFIG_C75SS1_0_NUM] = {
    {
        .intNum = (59U), /* interrupt line on C75SS1_0 CPU */
        .eventId = (CLEC1_SOC_INT_START + CSLR_C7X256V1_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_3_MAILBOX_CLUSTER_PEND_2), /* CSL int num + CLEC SOC offset */
        .numCores = 1,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = (60U), /* interrupt line on C75SS1_0 CPU */
        .eventId = (CLEC1_SOC_INT_START + CSLR_C7X256V1_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_5_MAILBOX_CLUSTER_PEND_2), /* CSL int num + CLEC SOC offset */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0,
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = (61U), /* interrupt line on C75SS1_0 CPU */
        .eventId = (CLEC1_SOC_INT_START + CSLR_C7X256V1_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_7_MAILBOX_CLUSTER_PEND_2), /* CSL int num + CLEC SOC offset */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0,
            CSL_CORE_ID_MAIN_R5FSS0_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_c75ss1_0 = IPC_NOTIFY_INTERRUPT_CONFIG_C75SS1_0_NUM;

/* Interrupt config for A53SS0_0 */
#define IPC_NOTIFY_INTERRUPT_CONFIG_A53SS0_0_NUM   (4u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_a53ss0_0[IPC_NOTIFY_INTERRUPT_CONFIG_A53SS0_0_NUM] = {
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0
        },
    },
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_1_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0
        },
    },
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_3_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 2U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MAIN_R5FSS0_0,
            CSL_CORE_ID_C75SS1_0
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_a53ss0_0 = IPC_NOTIFY_INTERRUPT_CONFIG_A53SS0_0_NUM;
