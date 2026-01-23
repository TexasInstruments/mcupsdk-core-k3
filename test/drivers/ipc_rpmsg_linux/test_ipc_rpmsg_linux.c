/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#if defined(SOC_J722S)
#include <drivers/ipc_rpmsg/ipc_rpmsg_priv.h>
#endif


/* RPMessage object used to receive messages */
RPMessage_Object TestIpcRPMsg_recvMsgObject[2];

/* This is used to run the echo test with linux kernel */
#define TEST_IPC_RPMESSAGE_SERVICE_PING        "rpmsg-client-sample"
#define TEST_IPC_RPMESSAGE_ENDPT_PING          (13U)

/* This is used to run the echo test with user space kernel */
#define TEST_IPC_RPMESSAGE_SERVICE_CHRDEV      "rpmsg_chrdev"
#define TEST_IPC_RPMESSAGE_ENDPT_CHRDEV_PING   (14U)

/**
 * \brief Tests intialisation of R5F core and A53
 *  core in linux boot 
 *  
 *
 * Test Category: Functionality
 *
 * This test check initialisation of the A53 and R5F core
 * in linux boot
 *
 * The test ensures that the the IPC communication works with
 * linux.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters.
 *
 * \return None.
 */
void TestIpcRpmsg_linuxInitVerify(void *args)
{
    RPMessage_CreateParams createParams;
    int32_t status;

    /* Endpoint creation */
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TEST_IPC_RPMESSAGE_ENDPT_PING;
    status = RPMessage_construct(&TestIpcRPMsg_recvMsgObject[0], &createParams);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TEST_IPC_RPMESSAGE_ENDPT_CHRDEV_PING;
    status = RPMessage_construct(&TestIpcRPMsg_recvMsgObject[1], &createParams);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Wait for linux initialisation */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Announce the endpoints to the A53 core */
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, TEST_IPC_RPMESSAGE_ENDPT_PING, TEST_IPC_RPMESSAGE_SERVICE_PING);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, TEST_IPC_RPMESSAGE_ENDPT_CHRDEV_PING, TEST_IPC_RPMESSAGE_SERVICE_CHRDEV);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    
    RPMessage_destruct(&TestIpcRPMsg_recvMsgObject[0]);
    RPMessage_destruct(&TestIpcRPMsg_recvMsgObject[1]);

}
void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestIpcRpmsg_linuxInitVerify, 8000, NULL);

    UNITY_END();    
}

void setUp(void)
{
}

void tearDown(void)
{
}
