/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_device_manager.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Function Definitions                               */
/* ========================================================================== */

int8_t test_sciserver_init(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciserver_tirtosInitPrms_Init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciserver_secproxyTransfer(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint32_t rxBuff, txBuff;
    uint16_t rxConfigId=4U, txConfigId = 1U;
    uint32_t rx_num_words = 5U;
    uint32_t tx_num_words = 5U;
    uint32_t senderHostId;
    uint16_t host_id = 35U;

    retVal = Sciserver_SproxyCanSend(txConfigId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSendAtOffset(txConfigId, &txBuff, tx_num_words, 1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSend(txConfigId, &txBuff, tx_num_words);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgFinish(txConfigId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgIsPending(rxConfigId);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgReadAtOffset(rxConfigId, &rxBuff, rx_num_words, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgRead(rxConfigId, &rxBuff, rx_num_words);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgGetSenderHostId(rxConfigId, &senderHostId);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgValidateHostId(host_id);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgAck(rxConfigId);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    uint16_t txConfigId2 = 1U;
    uint32_t tx_num_words2 = 5U;

    retVal = Sciserver_SproxyMsgIsPending(100U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgReadAtOffset(100U, &rxBuff, 5U, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgReadAtOffset(1U, NULL, 5U, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgReadAtOffset(100U, &rxBuff, 0xFFU, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgReadAtOffset(100U, &rxBuff, 0x0, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgGetSenderHostId(0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgValidateHostId(255U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgAck(100U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyCanSend(0xFF);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSendAtOffset(0xFF, &txBuff, tx_num_words2, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSendAtOffset(txConfigId2, NULL, tx_num_words2, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSendAtOffset(txConfigId2, &txBuff, 0xFF, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgSendAtOffset(txConfigId2, &txBuff, 0x0, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgFinish(0xFF);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyMsgIsPending(0x3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    uint8_t checkTest=0;
    uint16_t txIdTest=1, rxIdTest=3;
#if defined (SOC_AM62X) || defined (SOC_AM62AX)
    for(checkTest=0; checkTest<5;checkTest++)
    {
        retVal = Sciserver_SproxyMsgIsPending(rxIdTest);
    }
    /* Continuous call for occur error */
    for(checkTest=0; checkTest<5;checkTest++)
    {
        retVal = Sciserver_SproxyMsgFinish(txIdTest);
    }
#elif defined (SOC_AM62PX)
    for(checkTest=0; checkTest<20;checkTest++)
    {
        retVal = Sciserver_SproxyMsgIsPending(rxIdTest);
    }
    /* Continuous call for occur error */
    for(checkTest=0; checkTest<20;checkTest++)
    {
        retVal = Sciserver_SproxyMsgFinish(txIdTest);
    }
#endif
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciserver(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    /* no return type */
    (void)Sciserver_setProcessState(SCISERVER_PROCESS_STATE_WAIT);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_getProcessState();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    /* Negative testcase */
    HW_WR_REG32(0x4D003000, 0xD);
    HW_WR_REG32(0x4D003004, 0xC010E);
    HW_WR_REG32(0x4D003008, 0x2);
    HW_WR_REG32(0x4D00300C, 0x87);
    HW_WR_REG32(0x4D003010, 0xABA9500);
    HW_WR_REG32(0x4D00303C, 0x0);

    /* Positive testcase */
    HW_WR_REG32(0x4D003000, 0xD);
    HW_WR_REG32(0x4D003004, 0x24010E);
    HW_WR_REG32(0x4D003008, 0x2);
    HW_WR_REG32(0x4D00300C, 0x87);
    HW_WR_REG32(0x4D003010, 0xABA9500);
    HW_WR_REG32(0x4D00303C, 0x0);

#if defined (SOC_AM62X) || defined (SOC_AM62AX)
    ClockP_sleep(5);
    HW_WR_REG32(0x4D019000, 0xD);
    HW_WR_REG32(0x4D019004, 0xFB010E);
    HW_WR_REG32(0x4D019008, 0x2);
    HW_WR_REG32(0x4D01900C, 0x87);
    HW_WR_REG32(0x4D019010, 0xABA9500);
    HW_WR_REG32(0x4D01903C, 0x0);
    ClockP_sleep(5);
    HW_WR_REG32(0x4D019000, 0xD);
    HW_WR_REG32(0x4D019004, 0xFB1000);
    HW_WR_REG32(0x4D019008, 0x2);
    HW_WR_REG32(0x4D01900C, 0x87);
    HW_WR_REG32(0x4D019010, 0xABA9500);
    HW_WR_REG32(0x4D01903C, 0x0);
    ClockP_sleep(5);
    HW_WR_REG32(0x4D019000, 0xD);
    HW_WR_REG32(0x4D019004, 0x0C1000);
    HW_WR_REG32(0x4D019008, 0x0);
    HW_WR_REG32(0x4D01900C, 0x87);
    HW_WR_REG32(0x4D019010, 0xABA9500);
    HW_WR_REG32(0x4D01903C, 0x0);
    ClockP_sleep(5);

#elif defined (SOC_AM62PX)
    ClockP_sleep(5);
    HW_WR_REG32(0x4D017000, 0xD);
    HW_WR_REG32(0x4D017004, 0xFB010E);
    HW_WR_REG32(0x4D017008, 0x2);
    HW_WR_REG32(0x4D01700C, 0x87);
    HW_WR_REG32(0x4D017010, 0xABA9500);
    HW_WR_REG32(0x4D01703C, 0x0);
    ClockP_sleep(5);
    HW_WR_REG32(0x4D017000, 0xD);
    HW_WR_REG32(0x4D017004, 0xFB1000);
    HW_WR_REG32(0x4D017008, 0x2);
    HW_WR_REG32(0x4D01700C, 0x87);
    HW_WR_REG32(0x4D017010, 0xABA9500);
    HW_WR_REG32(0x4D01703C, 0x0);
    ClockP_sleep(5);
    HW_WR_REG32(0x4D017000, 0xD);
    HW_WR_REG32(0x4D017004, 0x0C1000);
    HW_WR_REG32(0x4D017008, 0x0);
    HW_WR_REG32(0x4D01700C, 0x87);
    HW_WR_REG32(0x4D017010, 0xABA9500);
    HW_WR_REG32(0x4D01703C, 0x0);
    ClockP_sleep(5);
#endif
    retVal = Sciserver_init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_init(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_deinit();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

#if defined (SOC_AM62X)
    retVal = Sciserver_processtask(NULL);

    const Sciserver_taskData utdTest2[] = {
        {
            .task_id = 0,
            .hw_msg_buffer_list = 0,
            .hw_msg_buffer_count = 2,
            .hw_msg_buffer_sz = 52U,
            .semaphore_id = 0,
            .state = 0,
            .user_msg_data = 0,
            .stack = 0,
        },
    };
    utdTest2->state->state = SCISERVER_TASK_PENDING;
    retVal = Sciserver_processtask((Sciserver_taskData *)utdTest2);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

#elif defined (SOC_AM62AX) || defined (SOC_AM62PX)
    retVal = Sciserver_processtask((Sciserver_taskData *)utdTest3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
#endif

    bool soft_error = false;
    retVal = Sciserver_interruptHandler((Sciserver_hwiData *)uhd1, &soft_error);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    utdTest1->state->state = SCISERVER_TASK_PENDING;
    retVal = Sciserver_processtask((Sciserver_taskData *)utdTest1);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciserver_tirtos(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    Sciserver_TirtosCfgPrms_t appPrms;

    retVal = Sciserver_tirtosInit(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	appPrms.taskPriority[SCISERVER_TASK_USER_LO] = 1U;
	appPrms.taskPriority[SCISERVER_TASK_USER_HI] = 3U;
	Sciserver_deinit();
	retVal = Sciserver_tirtosInit(&appPrms);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* These tests must remain in this order */
	Sciserver_tirtosDisableIntr();
	Sciserver_tirtosEnableIntr();
	Sciserver_tirtosDeinit();
	Sciserver_tirtosDeinit();
	Sciserver_tirtosDisableIntr();
	Sciserver_tirtosEnableIntr();
	Sciserver_tirtosEnableIntr();

	Sciserver_tirtosDeinit();
	retVal = Sciserver_tirtosInit(&appPrms);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	Sciserver_deinit();
	retVal = Sciserver_tirtosInit(&appPrms);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	return failCount;
}
