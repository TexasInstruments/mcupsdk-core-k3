/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
 *   0      |  0   | DM R5 -> A53
 *   0      |  1   | A53 -> DM R5
 *   0      |  2   | C7x -> MCU R5
 *   0      |  3   | MCU R5 -> C7x
 *   1      |  0   | C7x -> A53
 *   1      |  1   | A53 -> C7x
 *   1      |  2   | MCU R5 -> DM R5
 *   1      |  3   | DM R5 -> MCU R5
 *   2      |  0   | MCU R5 -> A53
 *   2      |  1   | A53 -> MCU R5
 *   3      |  0   | C7x -> DM R5
 *   3      |  1   | DM R5 -> C7x
 *
 *
 * User ID:
 * A53 Rx: 0
 * C7x Rx: 1, 0
 * MCU R5 Rx: 2
 * DM R5 Rx: 3
 */
IpcNotify_MailboxConfig gIpcNotifyMailboxConfig[CSL_CORE_ID_MAX][CSL_CORE_ID_MAX] =
{
    /* from MCU_R5FSS0-0 */
    {
        { /* to MCU_R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to R5FSS0-0 */
            1U, 2U, 3U
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            0U, 3U, 1U
        },
    },
    /* from R5FSS0-0 */
    {
        { /* to MCU_R5FSS0-0 */
            1U, 3U, 2U
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            3U, 1U, 1U
        },
    },
    /* from A53SS0_0 */
    {
        { /* to MCU_R5FSS0-0 */
            2U, 1U, 2U
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            1U , 1U, 1U
        },
    },
    /* from A53SS0_1 */
    {
        { /* to MCU_R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS1_0 */
    {
        { /* to MCU_R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            MAILBOX_UNUSED
        },
    },
    /* from A53SS1_1 */
    {
        { /* to MCU_R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            MAILBOX_UNUSED
        },
    },
    /* from HSM_M4FSS0 */
    {
        { /* to MCU_R5FSS0-0 */
            MAILBOX_UNUSED
        },
        { /* to R5FSS0-0 */
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            MAILBOX_UNUSED
        },
    },
    /* from c75ss0 */
    {
        { /* to MCU_R5FSS0-0 */
            0U, 2U, 2U
        },
        { /* to R5FSS0-0 */
            3U, 0U, 3U
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
        { /* to HSM_M4FSS0 */
            MAILBOX_UNUSED
        },
        { /* to c75ss0 */
            MAILBOX_UNUSED
        },
    },
};

/* Interrupt config for MCU_R5FSS0-0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM   (3u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_mcu_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM] = {
    {
        .intNum = 240U,   /* interrupt line on MCU_R5FSS0-0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = 241U,   /* interrupt line on MCU_R5FSS0-0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_R5FSS0_0
        },
    },
    {
        .intNum = 242U,   /* interrupt line on MCU_R5FSS0-0 CPU */
        .eventId = 0U,   /* not used */
        .numCores = 1U,  /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = { /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    }
};
uint32_t gIpcNotifyInterruptConfigNum_mcu_r5fss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_MCU_R5FSS0_0_NUM;

/* Interrupt config for A53SS0_0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM   (3u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_a53ss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM] = {
    {
        .intNum = 108U,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_R5FSS0_0
        },
    },
    {
        .intNum = 109U,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS0_0
        },
    },
    {
        .intNum = 140U,   /* interrupt line on A53SS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_a53ss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_A53SS0_0_NUM;

/* Interrupt config for R5FSS0_0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM   (3u)
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM] = {
    {
        .intNum = 240U,   /* interrupt line on R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = 241U,   /* interrupt line on R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0
        },
    },
    {
        .intNum = 243U,   /* interrupt line on R5FSS0_0 CPU */
        .eventId = 0U,    /* not used */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_C75SS0_0
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_r5fss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM;

/* Interrupt config for C75SS0_0 */
#define IPC_NOFTIY_INTERRUPT_CONFIG_C75SS0_0_NUM   (3u)
#define CLEC_SOC_INT_START                         (192u)   /* (192 - soc interrupt start, ref: clec_spec am62d_soc_event_out_mapping)*/
IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_c75ss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_C75SS0_0_NUM] = {
    {
        .intNum = 59U,   /* interrupt line on C75SS0_0 CPU */
        .eventId = 192,    /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_MCU_R5FSS0_0
        },
    },
    {
        .intNum = 60U,   /* interrupt line on C75SS0_0 CPU */
        .eventId = 193,    /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_A53SS0_0
        },
    },
    {
        .intNum = 62U,   /* interrupt line on C75SS0_0 CPU */
        .eventId = 195,    /* CSL int num + CLEC SOC offset */
        .numCores = 1U,   /* number of cores that send messages which tied to this interrupt line */
        .coreIdList = {   /* core ID's tied to this interrupt line */
            CSL_CORE_ID_R5FSS0_0
        },
    },
};
uint32_t gIpcNotifyInterruptConfigNum_c75ss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_C75SS0_0_NUM;
