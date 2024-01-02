/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 *  \file sciserver_hwi_data.h
 *
 *  \brief This file contains HWI data for the Sciserver
 */

#ifndef SCISERVER_HWI_DATA_H
#define SCISERVER_HWI_DATA_H

#include <string.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/hw_types.h>
#include <drivers/sciclient/csl_sec_proxy.h>
#include <drivers/hw_include/csl_utils.h>
#include <drivers/device_manager/sciserver.h>
#include <sciserver_secproxyConfigData.h>

#include <drivers/hw_include/cslr_soc.h>

/** Maximum number of Secure Proxy Instances */
#define SCISERVER_SECPROXY_INSTANCE_COUNT (0x2U)

/*
 * Task stacks are also static memory blocks so the size must be
 * defined below.
 */
#define SCISERVER_TASK_STACK_SIZE         (2*1024U)

/** Buffers to be used by user space */
static uint32_t user_hi_msg_buffer[SCISERVER_HW_QUEUE_SIZE];
static uint32_t user_lo_msg_buffer[SCISERVER_HW_QUEUE_SIZE];
static uint32_t user_hi_main_msg_buffer[SCISERVER_HW_QUEUE_SIZE];
static uint32_t user_lo_main_msg_buffer[SCISERVER_HW_QUEUE_SIZE];

static Sciserver_taskState user_hi_msg_state;
static Sciserver_taskState user_lo_msg_state;

static Sciserver_msgData user_hi_msg_data;
static Sciserver_msgData user_lo_msg_data;
static Sciserver_msgData user_hi_main_msg_data;
static Sciserver_msgData user_lo_main_msg_data;

/* Task stack memory regions */
static uint8_t user_hi_task_stack[SCISERVER_TASK_STACK_SIZE];
static uint8_t user_lo_task_stack[SCISERVER_TASK_STACK_SIZE];

static uint32_t *const user_hi_msg_buffer_list[SCISERVER_SECPROXY_INSTANCE_COUNT] = {
    user_hi_msg_buffer,
    user_hi_main_msg_buffer
};

static uint32_t *const user_lo_msg_buffer_list[SCISERVER_SECPROXY_INSTANCE_COUNT] = {
    user_lo_msg_buffer,
    user_lo_main_msg_buffer,
};

static Sciserver_msgData *const user_hi_msg_data_list[SCISERVER_SECPROXY_INSTANCE_COUNT] = {
    &user_hi_msg_data,
    &user_hi_main_msg_data,
};

static Sciserver_msgData *const user_lo_msg_data_list[SCISERVER_SECPROXY_INSTANCE_COUNT] = {
    &user_lo_msg_data,
    &user_lo_main_msg_data,
};

static const Sciserver_hwiData sciserver_hwi_list[] = {
       /* user_mcu_nav_low_priority */
    {
        .irq_num = CSLR_WKUP_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_43,
        .hw_msg_queue_id = AM62PX_DMASS0_SEC_PROXY_0_RX_DM_NONSEC_LOW_PRIORITY_RX_THR070_CONF001,
        .hw_msg_buffer = user_hi_msg_buffer,
        .semaphore_id = SCISERVER_SEMAPHORE_USER_HI,
        .user_msg_data = &user_hi_msg_data,
    },

};

static const Sciserver_taskData gSciserverTaskList[SCISERVER_TASK_MAX_CNT] = {
    /* user_hi_msg_task_data */
    {
        .task_id = SCISERVER_TASK_USER_HI,
        .hw_msg_buffer_list = user_hi_msg_buffer_list,
        .hw_msg_buffer_count = SCISERVER_SECPROXY_INSTANCE_COUNT,
        .hw_msg_buffer_sz = SCISERVER_HW_QUEUE_SIZE,
        .semaphore_id = SCISERVER_SEMAPHORE_USER_HI,
        .state = &user_hi_msg_state,
        .user_msg_data = user_hi_msg_data_list,
        .stack = user_hi_task_stack,
    },

    /* user_lo_msg_task_data */
    {
        .task_id = SCISERVER_TASK_USER_LO,
        .hw_msg_buffer_list = user_lo_msg_buffer_list,
        .hw_msg_buffer_count = SCISERVER_SECPROXY_INSTANCE_COUNT,
        .hw_msg_buffer_sz = SCISERVER_HW_QUEUE_SIZE,
        .semaphore_id = SCISERVER_SEMAPHORE_USER_LO,
        .state = &user_lo_msg_state,
        .user_msg_data = user_lo_msg_data_list,
        .stack = user_lo_task_stack,
    },
};

#endif /* SCISERVER_HWI_DATA_H */
