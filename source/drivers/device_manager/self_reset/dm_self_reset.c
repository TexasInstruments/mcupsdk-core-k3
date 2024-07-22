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
/**
 *  \file dm_self_reset.c
 *
 *  \brief File containing the Device Manager R5 self reset implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <self_reset_config.h>
#include "dm_self_reset.h"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern  int32_t sproxy_receive_msg_r5_to_tifs_fw(void *msg, size_t len);
extern  int32_t sproxy_send_msg_r5_to_tifs_fw(void *msg, size_t len);
static void SelfReset_abortReset(void);
static void SelfReset_deviceManagerEnterWFI(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern uint32_t _vectors[16];
uint8_t gSelfReset_bootVector[0x40] __attribute__((location(SELF_RESET_TCM_ADDRESS_OFFSET)));

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SelfReset_deviceManagerReset(void)
{
    /* Request the processor core(s) */
    struct tisci_msg_proc_request_req proc_request_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_REQUEST,
	        .seq = 0,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };
	struct tisci_msg_proc_request_resp proc_request_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_request_req , sizeof(proc_request_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_request_resp, sizeof(proc_request_resp));
    if ((proc_request_resp.hdr.type != TISCI_MSG_PROC_REQUEST) || ((proc_request_resp.hdr.flags & TISCI_MSG_FLAG_ACK )!= TISCI_MSG_FLAG_ACK )) {
		SelfReset_abortReset();
	}


    /* get  the current status(es) */
    struct tisci_msg_proc_get_status_req proc_get_status_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_GET_STATUS,
	        .seq = 0x0,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };
    struct tisci_msg_proc_get_status_resp proc_get_status_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_get_status_req , sizeof(proc_get_status_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_get_status_resp, sizeof(proc_get_status_resp));
     if ((proc_get_status_resp.hdr.type != TISCI_MSG_PROC_GET_STATUS) || ((proc_get_status_resp.hdr.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK )) {
		SelfReset_abortReset();
	}

    struct tisci_msg_proc_set_config_req proc_set_config_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_SET_CONFIG,
	        .seq = 0x22,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .bootvector_lo = SELF_RESET_BOOT_ADDRESS_LOW, //boot_addr_lo
        .config_flags_1_set   = SELF_RESET_SET_CONFIG_FLAGS, // set_config_flags,
        .config_flags_1_clear = SELF_RESET_CLEAR_CONFIGD_FLAGS //clr_config_flags;
    };
	struct tisci_msg_proc_set_config_resp proc_set_config_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_set_config_req , sizeof(proc_set_config_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_set_config_resp , sizeof(proc_set_config_resp));
	 if ((proc_set_config_resp.hdr.type != TISCI_MSG_PROC_SET_CONFIG) || ((proc_set_config_resp.hdr.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK )) {
		SelfReset_abortReset();
	}

	/* Copy reset vectors to TCM base */

    /* Klocwork tool does not recognize the _vectors array as a pointer.
     * Introduce a temporary pointer variable boot_vector_temp and _vectors_temp to use as arguments to memcpy.
     */
    uint8_t *bootVectorTemp = gSelfReset_bootVector;
	uint32_t *vectorsTemp = _vectors;
	memcpy((void *)bootVectorTemp, (void *)vectorsTemp, 0x40);

    /* 1. Send TISCI_MSG_PROC_WAIT_STATUS but DO NOT wait for a response */
    struct tisci_msg_proc_status_wait_req proc_status_wait_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_WAIT_STATUS,
	        .seq = 0x44,
	        .flags = 0,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .num_wait_iterations = 255,
        .num_match_iterations = 1,
        .delay_per_iteration_us = 1,
        .status_flags_1_set_any_wait = (TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFE | TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI)
    };
	sproxy_send_msg_r5_to_tifs_fw(&proc_status_wait_req , sizeof(proc_status_wait_req));

	/**
	 * 2. Send TISCI message to assert R5 local reset but DO NOT wait for a response
	 * Assert reset for core 1 (slave) (if exists) before core 0
	 */
    struct tisci_msg_proc_set_control_req proc_set_assert_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_SET_CONTROL,
	        .seq = 0x55,
	        .flags = 0,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .control_flags_1_set = TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET
    };
	sproxy_send_msg_r5_to_tifs_fw(&proc_set_assert_req , sizeof(proc_set_assert_req));

	/**
	 * 3. Send TISCI message to de-assert R5 local reset but DO NOT wait for a response
	 * De-assert reset for core 0 before core 1 (slave) (if exists)
	 * Reason: core 1 may never ben in a higher functional state than core 0
	 */
    struct tisci_msg_proc_set_control_req  proc_set_deassert_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_SET_CONTROL,
	        .seq = 0x66,
	        .flags = 0,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .control_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET,
    };
	sproxy_send_msg_r5_to_tifs_fw(&proc_set_deassert_req , sizeof(proc_set_deassert_req));

     /* Release the processor core(s) */
    struct tisci_msg_proc_release_req proc_release_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_RELEASE,
	        .seq = 0,
	        .flags = 0,
            .host = SELF_RESET_DM_R5_HOST_ID
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };

    sproxy_send_msg_r5_to_tifs_fw(&proc_release_req , sizeof(proc_release_req));

	/* 4. Call WFI */
	SelfReset_deviceManagerEnterWFI();

    return 0;

}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void SelfReset_abortReset(void)
{
    while(true){}
}

static void SelfReset_deviceManagerEnterWFI(void)
{
    while (true) {
        __asm__ __volatile__ ("wfi" "\n\t": : : "memory");
    }
}