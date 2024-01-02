/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *   0      |  0   | WKUP R5F -> A53
 *   0      |  1   | A53      -> WKUP R5F
 *   1      |  0   | MCU R5F  -> A53
 *   1      |  1   | A53      -> MCU R5F
 *   2      |  0   | MCU R5F  -> WKUP R5F
 *   2      |  1   | WKUP R5F -> MCU R5F
 *
 * User ID:
 *     MCU R5F Rx : 2
 *     WKUP R5F Rx: 3
 *     A53 Rx     : 0
 */
IpcNotify_MailboxConfig gIpcNotifyMailboxConfig[CSL_CORE_ID_MAX][CSL_CORE_ID_MAX] =
{
    /* from MCU R5FSS0-0 */
    {
        { /* to MCU R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to WKUP R5FSS0-0 */
            2U, 0U, 3U
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
            2U, 1U, 2U
        },
        { /* to WKUP R5FSS0-0 */
            MAILBOX_UNUSED
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
    /* from A53SS0_0 */
    {
        { /* to MCU R5FSS0-0 */
            1U, 1U, 2U
        },
        { /* to WKUP R5FSS0-0 */
            0U, 1U, 3U
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
#define IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM   (2u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_mcu_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM] = {
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_1_MAILBOX_CLUSTER_PEND_2,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID

        },
    },
    {
        .intNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_2,   /* interrupt line on MCU_R5FSS0_0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID

        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_mcu_r5fss0_0= IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM;

/* Interrupt config for A53SS0_0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM   (2u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_a53ss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM] = {
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_WKUP_R5FSS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID
        },
    },
    {
        .intNum = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_1_MAILBOX_CLUSTER_PEND_0,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_a53ss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM;

/* Interrupt config for WKUP_R5FSS0_0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM   (2u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_wkup_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM] = {
    {
        .intNum = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on WKUP_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID
        },
    },
    {
        .intNum = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_3,   /* interrupt line on WKUP_R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID,
            CSL_CORE_ID_INVALID
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_wkup_r5fss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_WKUP_R5FSS0_0_NUM;