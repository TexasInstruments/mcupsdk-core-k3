 /*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <drivers/soc.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/pinmux.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/sciclient.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>

/*
 * Example: MCU Master-Initiated Partial I/O Mode Entry
 *
 * This example demonstrates MCU as the master initiator for Partial I/O mode entry.
 * - Enables MCU MCAN IO activity as wakeup source.
 * - Waits for user to press a character on console.
 * - Once character is pressed, sends mailbox message to Linux to trigger poweroff.
 * - Requests device manager core to initiate partial I/O low power mode entry.
 */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Remote core service end point
 *
 * pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
 * the value need not be unique across cores
 *
 * The service names MUST match what linux is expecting
 */
/* This is used to run the echo test with linux kernel */
#define LPM_APP_IPC_RPMESSAGE_SERVICE_PING        "ti.ipc4.ping-pong"
#define LPM_APP_IPC_RPMESSAGE_ENDPT_PING          (13U)

/* This is used to run the echo test with user space kernel */
#define LPM_APP_IPC_RPMESSAGE_SERVICE_CHRDEV      "rpmsg_chrdev"
#define LPM_APP_IPC_RPMESSAGE_ENDPT_CHRDEV_PING   (14U)

/* Maximum size that message can have in this example
 * RPMsg maximum size is 512 bytes in linux including the header of 16 bytes.
 * Message payload size without the header is 512 - 16 = 496
 */
#define LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE        (496U)

/*
 * Number of RP Message ping "servers" we will start,
 * - one for ping messages for linux kernel "sample ping" client
 * - and another for ping messages from linux "user space" client using "rpmsg char"
 */
#define LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS      (2U)

/* Task priority, stack, stack size and task objects, these MUST be global's */
#define LPM_APP_IPC_RPMESSAGE_TASK_PRI            (8U)
#define LPM_APP_SUSPEND_TASK_PRIORITY             (9U)

#define LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE     (8*1024U)
#define LPM_APP_SUSPEND_TASK_STACK_SIZE           1024U

/* A53 poweroff can vary based on system load/logging */
#define LPM_APP_POWEROFF_WAIT_TIMEOUT_US          5000000U              
#define LPM_APP_A53_STATE_POLL_DELAY_US           500000U                
#define LPM_APP_A53_STATE_POLL_TIMEOUT_US         (LPM_APP_A53_STATE_POLL_DELAY_US + 100000U) /* Slightly longer than poll delay */

#define LPM_APP_IPC_WAIT_FOR_FIFO_NOT_FULL        1U


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

UART_Transaction gLpmTrans;
SemaphoreP_Object gLpmSuspendReadySem;
uint8_t gLpmRxByte;

/* RPMessage object used to receive messages */
RPMessage_Object gIpcRecvMsgObject[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

uint8_t gIpcTaskStack[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS][LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gIpcTask[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

static uint8_t gSuspendTaskStack[LPM_APP_SUSPEND_TASK_STACK_SIZE] __attribute__((aligned(8)));
static TaskP_Object gSuspendTaskObj;

static Pinmux_PerCfg_t gPinMuxWakeupEnableCfg[] = {
    /* MCU_MCAN0 pin config to enable mcan pins as wakeup source */
    {
        PIN_MCU_MCAN0_RX,
        (PIN_MODE(0U) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL | PIN_WAKEUP_ENABLE)
    },

    {PINMUX_END, 0U}
};

volatile uint8_t gbShutdown = 0U;
volatile uint8_t gRecvTaskExitCounter = 0U;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *trans);
static void LpmApp_recvTaskMain(void *args);
static void LpmApp_createRecvTasks(void);
static void LpmApp_triggerShutdown(void);
static void LpmApp_createSuspendTask(void);
static void LpmApp_suspendTask(void *args);
static int32_t LpmApp_sendMailboxToLinux(uint32_t message);
static int32_t LpmApp_waitForA53Poweroff(void);
static inline void LpmApp_putCPUInWFI(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void LpmApp_PartialIOMain(void *args)
{
    int32_t status;

    DebugP_log("[LPM PARTIAL IO APP] Example Application Started...\r\n");

    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status==SystemP_SUCCESS);

    /* Create Suspend task */
    LpmApp_createSuspendTask();

    /* create message receive tasks, these tasks always run and never exit */
    LpmApp_createRecvTasks();

    /* Synchronize all the cores */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);
    
    /* exit from this task, vTaskDelete() is called outside this function, so simply return */
}

void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *trans)
{
    gLpmRxByte = *((uint8_t *)(trans->buf));
    if (UART_TRANSFER_STATUS_SUCCESS == trans->status)
    {
        SemaphoreP_post(&gLpmSuspendReadySem);
    }
}

static void LpmApp_recvTaskMain(void *args)
{
    int32_t status;
    char recvMsg[LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE+1]; /* +1 for NULL char in worst case */
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;

    DebugP_log("[LPM PARTIAL IO APP] Remote Core waiting for messages at end point %d ... !!!\r\n",
        RPMessage_getLocalEndPt(pRpmsgObj)
        );

    /* wait for messages forever in a loop */
    while(1)
    {
        /* set 'recvMsgSize' to size of recv buffer,
        * after return `recvMsgSize` contains actual size of valid data in recv buffer
        */
        recvMsgSize = LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE;
        status = RPMessage_recv(pRpmsgObj,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);

        if (gbShutdown == 1U)
        {
            break;
        }

        DebugP_assert(status == SystemP_SUCCESS);

        /* Send ack to sender CPU at the sender end point */
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(pRpmsgObj),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    gRecvTaskExitCounter++;
    if (gRecvTaskExitCounter >= LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS)
    {
        /* Follow the sequence for graceful shutdown for the last recv task */
        DebugP_log("[LPM PARTIAL IO APP] Closing all drivers and going to WFI ... !!!\r\n");

        /* Close the drivers */
        Drivers_close();

        /* Deinit system */
        System_deinit();

        LpmApp_putCPUInWFI();
    }

    vTaskDelete(NULL);
}

static void LpmApp_createRecvTasks(void)
{
    int32_t status;
    RPMessage_CreateParams createParams;
    TaskP_Params taskParams;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = LPM_APP_IPC_RPMESSAGE_ENDPT_PING;
    status = RPMessage_construct(&gIpcRecvMsgObject[0], &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = LPM_APP_IPC_RPMESSAGE_ENDPT_CHRDEV_PING;
    status = RPMessage_construct(&gIpcRecvMsgObject[1], &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    /* We need to "announce" to Linux client else Linux does not know a service exists on this CPU
     * This is not mandatory to do for RTOS clients
     */
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, LPM_APP_IPC_RPMESSAGE_ENDPT_PING, LPM_APP_IPC_RPMESSAGE_SERVICE_PING);
    DebugP_assert(status==SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, LPM_APP_IPC_RPMESSAGE_ENDPT_CHRDEV_PING, LPM_APP_IPC_RPMESSAGE_SERVICE_CHRDEV);
    DebugP_assert(status==SystemP_SUCCESS);

    /* Create the tasks which will handle the ping service */
    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_PING";
    taskParams.stackSize = LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[0];
    taskParams.priority = LPM_APP_IPC_RPMESSAGE_TASK_PRI;
    /* we use the same task function for echo but pass the appropiate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[0];
    taskParams.taskMain = LpmApp_recvTaskMain;

    status = TaskP_construct(&gIpcTask[0], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_CHAR_PING";
    taskParams.stackSize = LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[1];
    taskParams.priority = LPM_APP_IPC_RPMESSAGE_TASK_PRI;
    /* we use the same task function for echo but pass the appropiate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[1];
    taskParams.taskMain = LpmApp_recvTaskMain;

    status = TaskP_construct(&gIpcTask[1], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);
}

static void LpmApp_triggerShutdown(void)
{
    gbShutdown = 1U;
    RPMessage_unblock(&gIpcRecvMsgObject[0]);
    RPMessage_unblock(&gIpcRecvMsgObject[1]);
}

static void LpmApp_createSuspendTask(void)
{
    int32_t status;
    TaskP_Params params;

    TaskP_Params_init(&params);
    params.name = "LPM_Suspend_Task";
    params.stackSize = LPM_APP_SUSPEND_TASK_STACK_SIZE;
    params.stack = gSuspendTaskStack;
    params.priority = LPM_APP_SUSPEND_TASK_PRIORITY;
    params.taskMain = (TaskP_FxnMain)LpmApp_suspendTask;
    
    status = TaskP_construct(&gSuspendTaskObj, &params);
    DebugP_assert(status == SystemP_SUCCESS);
}

static void LpmApp_suspendTask(void *args)
{
    int32_t status;

    /* This API must enable the wakeup sources to ensure that system is recoverable */
    Pinmux_config(gPinMuxWakeupEnableCfg, PINMUX_DOMAIN_ID_MCU);

    /* Initialize semaphores */
    status = SemaphoreP_constructBinary(&gLpmSuspendReadySem, 0);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Initialize UART transaction */
    UART_Transaction_init(&gLpmTrans);
    gLpmTrans.buf = &gLpmRxByte;
    gLpmTrans.count = 1U;

    DebugP_log("[LPM PARTIAL IO APP] Press 'P' to enter partial I/O\r\n");
    
    while (1U)
    {
        /* Initialize UART Read */
        UART_read(gUartHandle[CONFIG_UART0], &gLpmTrans);  
        
        /* Wait for UART interrupt */
        SemaphoreP_pend(&gLpmSuspendReadySem, SystemP_WAIT_FOREVER);

        if(gLpmRxByte == 'P')
        {
            /* Send poweroff request to Linux */
            status = LpmApp_sendMailboxToLinux(IPC_NOTIFY_RP_MBOX_SHUTDOWN_SYSTEM);
            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[LPM PARTIAL IO APP] ERROR: Mailbox send failed\r\n");
            } 
            else 
            {
                DebugP_log("[LPM PARTIAL IO APP] Sent poweroff req to Linux\r\n");
            }

            status = LpmApp_waitForA53Poweroff();
            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[LPM PARTIAL IO APP] ERROR: A53 did not enter WFI\r\n");
            }

            DebugP_log("[LPM PARTIAL IO APP] Entering partial I/O\r\n");

            /* Whether the cores have hit WFI or not, we need to send Partial I/O sleep message to DM to recover the system */
            status = Sciclient_lpmSendPrepareSleepMessage(TISCI_MSG_VALUE_SLEEP_MODE_PARTIAL_IO, SystemP_WAIT_FOREVER);

            /* If system is unable to enter this mode, assert failure */
            DebugP_assert(status == SystemP_SUCCESS);

            break;
        }
    }

    SemaphoreP_destruct(&gLpmSuspendReadySem);

    LpmApp_triggerShutdown();
}

static int32_t LpmApp_sendMailboxToLinux(uint32_t message)
{
    int32_t status = SystemP_SUCCESS;

    /* Send remoteproc mailbox message to Linux A53 core via IPC_NOTIFY
     * Using IPC_NOTIFY_CLIENT_ID_RP_MBOX for remoteproc communication
     */
    status = IpcNotify_sendMsg(CSL_CORE_ID_A53SS0_0, IPC_NOTIFY_CLIENT_ID_RP_MBOX, message, LPM_APP_IPC_WAIT_FOR_FIFO_NOT_FULL);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[LPM PARTIAL IO APP] ERROR: Failed to send remoteproc mailbox message (Status: %d)\r\n", status);
    }
    else
    {
        DebugP_log("[LPM PARTIAL IO APP] Remoteproc mailbox message sent successfully\r\n");
    }

    return status;
}

static int32_t LpmApp_waitForA53Poweroff(void)
{
    uint32_t moduleState = 0U;
    uint32_t elapsed = 0U;
    int32_t status;

    while (elapsed < LPM_APP_POWEROFF_WAIT_TIMEOUT_US)
    {
        status = Sciclient_pmGetModuleState(
            TISCI_DEV_BOARD0,
            &moduleState,
            NULL,
            NULL,
            LPM_APP_A53_STATE_POLL_TIMEOUT_US);

        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[LPM PARTIAL IO APP] ERROR: failed to query DM\r\n");
            return SystemP_FAILURE;
        }

        if (moduleState == 0U)
        {
            DebugP_log("[LPM PARTIAL IO APP] A53 powered off (took %u ms)\r\n", elapsed / 1000U);
            return SystemP_SUCCESS;
        }
        else
        {
            ClockP_usleep(LPM_APP_A53_STATE_POLL_DELAY_US);
            elapsed += LPM_APP_A53_STATE_POLL_DELAY_US;
        }
    }

    DebugP_log("[LPM PARTIAL IO APP] ERROR: A53 poweroff timeout after %u ms, moduleState = 0x%x\r\n",
               elapsed / 1000U, moduleState);

    return SystemP_FAILURE;
}

/**
 * \brief Wait For Interrupt - puts CPU into low power state until interrupt
 *
 * This inline function executes the ARM WFI instruction to put the CPU core
 * into a low-power state. The CPU will remain in this state until an interrupt
 * or exception occurs.
 */
static inline void LpmApp_putCPUInWFI(void)
{
#if (__ARM_ARCH_PROFILE == 'R') ||  (__ARM_ARCH_PROFILE == 'M')
    /* For ARM R and M cores*/
    __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
#endif
}
