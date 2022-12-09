#include <stdint.h>
#include <string.h>
#include <self_reset_config.h>
#include "dm_self_reset.h"

#if defined (MCU_PLUS_SDK)
extern void _vectors(void);
#else
extern void _freertosresetvectors(void);
#endif

extern  int32_t sproxy_receive_msg_r5_to_tifs_fw(void *msg, uint32_t len);
extern  int32_t sproxy_send_msg_r5_to_tifs_fw(void *msg, uint32_t len);



static void abort(){
    while(1){}
}

uint32_t dm_r5_self_reset(){

    /* Request the processor core(s) */
    struct tisci_msg_proc_request_req proc_request_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_REQUEST,
	        .seq = 0,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };
	struct tisci_msg_proc_request_resp proc_request_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_request_req , sizeof(proc_request_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_request_resp, sizeof(proc_request_resp));
    if (proc_request_resp.hdr.type != TISCI_MSG_PROC_REQUEST || ((proc_request_resp.hdr.flags & TISCI_MSG_FLAG_ACK )!= TISCI_MSG_FLAG_ACK )) {
		abort();
	}

    //TODO if r5 has dual core do the tisci_proc_boot_request_data for the second core also


    /* get  the current status(es) */
    struct tisci_msg_proc_get_status_req proc_get_status_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_GET_STATUS,
	        .seq = 0x0,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };
    struct tisci_msg_proc_get_status_resp proc_get_status_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_get_status_req , sizeof(proc_get_status_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_get_status_resp, sizeof(proc_get_status_resp));
     if (proc_get_status_resp.hdr.type != TISCI_MSG_PROC_GET_STATUS || ((proc_get_status_resp.hdr.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK )) {
		abort();
	}

    //TODO if r5 has dual core do the tisci_proc_boot_status_req_data for the second core also

    struct tisci_msg_proc_set_config_req proc_set_config_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_SET_CONFIG,
	        .seq = 0x22,
	        .flags = TISCI_MSG_FLAG_AOP,
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .bootvector_lo = SELF_RESET_BOOT_ADDRESS_LOW, //boot_addr_lo
        .config_flags_1_set   = SELF_RESET_SET_CONFIG_FLAGS, // set_config_flags,
        .config_flags_1_clear = SELF_RESET_CLEAR_CONFIGD_FLAGS //clr_config_flags;
    };
	struct tisci_msg_proc_set_config_resp proc_set_config_resp = { 0 };

    sproxy_send_msg_r5_to_tifs_fw(&proc_set_config_req , sizeof(proc_set_config_req));
    sproxy_receive_msg_r5_to_tifs_fw(&proc_set_config_resp , sizeof(proc_set_config_resp));
	 if (proc_set_config_resp.hdr.type != TISCI_MSG_PROC_SET_CONFIG || ((proc_set_config_resp.hdr.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK )) {
		abort();
	}

	// TODO: do the same for second core is present
    
	/* Copy reset vectors to TCM base */
#if defined (MCU_PLUS_SDK)
	memcpy((void *)0x41010000,(void *)((int32_t)_vectors + SELF_RESET_TCM_ADDRESS_OFFSET), 0x40);
#else
	memcpy((void *)0x41010000,(void *)((int32_t)_freertosresetvectors + SELF_RESET_TCM_ADDRESS_OFFSET), 0x40);
#endif    

    /* 1. Send TISCI_MSG_PROC_WAIT_STATUS but DO NOT wait for a response */
    struct tisci_msg_proc_status_wait_req proc_status_wait_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_WAIT_STATUS,
	        .seq = 0x44,
	        .flags = 0,
            .host = TISCI_HOST_ID_MAIN_0_R5_0
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
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .control_flags_1_set = TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET
    };
	sproxy_send_msg_r5_to_tifs_fw(&proc_set_assert_req , sizeof(proc_set_assert_req));
    //TODO for the second core also

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
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID,
        .control_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET,
    };
	sproxy_send_msg_r5_to_tifs_fw(&proc_set_deassert_req , sizeof(proc_set_deassert_req));

	// TODO do this for second core also

     /* Release the processor core(s) */
    struct tisci_msg_proc_release_req proc_release_req = {
        .hdr = {
            .type = TISCI_MSG_PROC_RELEASE,
	        .seq = 0,
	        .flags = 0,
            .host = TISCI_HOST_ID_MAIN_0_R5_0
        },
        .processor_id = SELF_RESET_PROCESSOR_ID
    };

    sproxy_send_msg_r5_to_tifs_fw(&proc_release_req , sizeof(proc_release_req));

	/* 4. Call WFI */
	__asm__ __volatile__ ("wfi" "\n\t": : : "memory");

    return 0;

}
