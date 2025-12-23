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
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <drivers/soc.h>
#include <drivers/pinmux.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"

/* This example shows message exchange between Linux and RTOS/NORTOS cores.
 * This example also demonstrates the capability of MCU UART input event to wake
 * the entire SOC in MCU Only low power mode.
 *
 * The Linux core initiates IPC with other core's by sending it a message.
 * The other cores echo the same message to the Linux core.
 *
 * This example can very well have been NORTOS based, however for convenience
 * of creating two tasks to talk to two clients on linux side, we use FreeRTOS
 * for the same.
 *
 * The linux core initiates low power mode suspend by sending a message to
 * remotecore. The remotecore queries the device manager for its next state and
 * responds the same to linux. In case of MCU Only mode, the remotecore waits to
 * receive UART input to resume from lpm.
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
#define LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS         (2U)

/* Task priority, stack, stack size and task objects, these MUST be global's */
#define LPM_APP_IPC_RPMESSAGE_TASK_PRI         (8U)
#define LPM_APP_MCU_SUSPEND_TASK_PRI       (8U)

#define LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE  (8*1024U)
#define LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE   (1024U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* RPMessage object used to receive messages */
RPMessage_Object gIpcRecvMsgObject[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

uint8_t gIpcTaskStack[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS][LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gIpcTask[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

uint8_t gLpmSuspendTaskStack[LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gLpmSuspendTask;

/* Wakeup is disabled by default for UART pins, so enable it to allow wakeup in deep sleep lpm */
static Pinmux_PerCfg_t gPinMuxWakeupEnableCfg[] = {
    /* MCU_USART0 pin config */
            /* MCU_UART0_RXD -> MCU_UART0_RXD (D8) */
    {
        PIN_MCU_UART0_RXD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_WAKEUP_ENABLE )
    },
            /* MCU_UART0_TXD -> MCU_UART0_TXD (F8) */
    {
        PIN_MCU_UART0_TXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },

    {PINMUX_END, 0U}
};

/* MCU I/Os are isolated in lpm that can prevent the UART input from reaching IP, so bypass the isolation. */
static Pinmux_PerCfg_t gPinMuxIsolationBypassCfg[] = {

    /* MCU_USART0 pin config */
            /* MCU_UART0_RXD -> MCU_UART0_RXD (D8) */
    {
        PIN_MCU_UART0_RXD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },
            /* MCU_UART0_TXD -> MCU_UART0_TXD (F8) */
    {
        PIN_MCU_UART0_TXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },

    {PINMUX_END, 0U}
};

volatile uint8_t gbShutdown = 0U;
volatile uint8_t gbShutdownRemotecoreID = 0U;
volatile uint8_t gbSuspended = 0U;
volatile uint8_t gbSuspendRemotecoreID = 0U;
volatile uint8_t gNumBytesRead = 0U;
volatile uint8_t gRecvTaskExitCounter = 0U;

SemaphoreP_Object gLpmResumeSem;
SemaphoreP_Object gLpmSuspendSem;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpmApp_recvTaskMain(void *args);
static void LpmApp_createRecvTasks(void);
static void LpmApp_triggerShutdown(void);
static void LpmApp_ipcRpMboxCallback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args);
static void LpmApp_waitForUART(void);
void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *trans);
static void LpmApp_suspendTask(void *args);
static void LpmApp_createSuspendTask(void);
static inline void LpmApp_putCPUInWFI(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void LpmApp_recvTaskMain(void *args)
{
    int32_t status;
    char recvMsg[LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE+1]; /* +1 for NULL char in worst case */
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;

    DebugP_log("[LPM UART WAKEUP] Remote Core waiting for messages at end point %d ... !!!\r\n",
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

        if (gbSuspended == 1U)
        {
            continue;
        }

        DebugP_assert(status==SystemP_SUCCESS);

        /* send ack to sender CPU at the sender end point */
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(pRpmsgObj),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);
    }

    gRecvTaskExitCounter++;
    if (gRecvTaskExitCounter >= LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS)
    {
        /* Follow the sequence for graceful shutdown for the last recv task */
        DebugP_log("[LPM UART WAKEUP] Closing all drivers and going to WFI ... !!!\r\n");

        /* Close the drivers */
        Drivers_close();

        /* deinit system */
        System_deinit();

        if (gbShutdownRemotecoreID)
        {
            /* ACK the shutdown message */
            IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1U);
        }

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
    /* Enable wakeup bit in the pinmux config for the UART pin for wake up via I/O in deep sleep */
    Pinmux_config(gPinMuxWakeupEnableCfg, PINMUX_DOMAIN_ID_MCU);

    gbShutdown = 1U;
    RPMessage_unblock(&gIpcRecvMsgObject[0]);
    RPMessage_unblock(&gIpcRecvMsgObject[1]);
}

static void LpmApp_ipcRpMboxCallback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remoteproc */
        {
            gbShutdownRemotecoreID = remoteCoreId;
            LpmApp_triggerShutdown();
        }
        else if (msgValue == IPC_NOTIFY_RP_MBOX_SUSPEND_SYSTEM) /* Suspend request received from linux during LPM suspend */
        {
            gbSuspendRemotecoreID = remoteCoreId;
            SemaphoreP_post(&gLpmSuspendSem);
        }
        else if (msgValue == IPC_NOTIFY_RP_MBOX_ECHO_REQUEST) /* This message is received after resuming from the MCU only LPM. */
        {
            gbSuspended = 0U;

            if (gNumBytesRead != 0U)
            {
                /* post this only for MCU UART Wakeup */
                SemaphoreP_post(&gLpmResumeSem);
            }
            DebugP_shmLogWriterResume();

            IpcNotify_sendMsg(remoteCoreId, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_ECHO_REPLY, 1U);
        }
    }
}

static void LpmApp_waitForUART(void)
{
    UART_Transaction trans;
    uint8_t uartData;
    int32_t status;

    UART_Transaction_init(&trans);

    /* Read 1 byte */
    trans.buf   = &uartData;
    trans.count = 1U;

    DebugP_memLogWriterPause();

    /*
     * Flush any stale data in RX FIFO before waiting for keypress.
     * This ensures only fresh keypresses (after LPM suspend request) trigger wake,
     * not any old data that was in the FIFO from before the suspend.
     */
    {
        uint8_t staleData;
        uint32_t baseAddr = UART_getBaseAddr(gUartHandle[CONFIG_UART0]);

        /* Drain all bytes currently in RX FIFO */
        while (UART_getChar(baseAddr, &staleData) != FALSE)
        {
            /* Discard stale byte */
        }
    }

    gNumBytesRead = 0U;

    /* Wait for any key to be pressed */
    status = UART_read(gUartHandle[CONFIG_UART0], &trans);
    DebugP_assert(status == SystemP_SUCCESS);

    while (gNumBytesRead == 0U && gbSuspended == 1U)
    {
        LpmApp_putCPUInWFI();
    }

    if (gNumBytesRead != 0U)
    {
        DebugP_log("[LPM UART WAKEUP] Key pressed. Notifying DM to wakeup main domain\r\n");
        SOC_triggerMcuLpmWakeup();
        /* Wait for resuming the main domain */
        SemaphoreP_pend(&gLpmResumeSem, SystemP_WAIT_FOREVER);

        DebugP_log("[LPM UART WAKEUP] Main domain resumed due to MCU UART \r\n");
    }
    else if (gbSuspended == 0U)
    {
        UART_readCancel(gUartHandle[CONFIG_UART0], &trans);
        DebugP_log("[LPM UART WAKEUP] Main domain resumed from a different wakeup source \r\n");
    }

    DebugP_memLogWriterResume();
}

void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *trans)
{
    if (UART_TRANSFER_STATUS_SUCCESS == trans->status)
    {
        gNumBytesRead = trans->count;
    }
}

static void LpmApp_suspendTask(void* args)
{
    int32_t status;

    status = SemaphoreP_constructBinary(&gLpmSuspendSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    status = SemaphoreP_constructBinary(&gLpmResumeSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    while (1)
    {
        uint8_t nextHostState;

        /* Wait for suspend from linux */
        SemaphoreP_pend(&gLpmSuspendSem, SystemP_WAIT_FOREVER);

        status = Sciclient_lpmGetNextHostState(SystemP_WAIT_FOREVER, &nextHostState);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[LPM UART WAKEUP] Failed to get next system state. Canceling suspend.\r\n");
            IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_CANCEL, 1U);
            continue;
        }

        DebugP_log("[LPM UART WAKEUP] Next MCU mode is %d\r\n", nextHostState);

        switch (nextHostState)
        {
            case TISCI_MSG_VALUE_HOST_STATE_OFF:
                IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_ACK, 1U);
                break;

            case TISCI_MSG_VALUE_HOST_STATE_ON:
                gbSuspended = 1U;

                /* Enable isolation bypass for the UART pinmux */
                Pinmux_config(gPinMuxIsolationBypassCfg, PINMUX_DOMAIN_ID_MCU);

                /* Print before sending ACK, otherwise IO isolation is enabled while printing */
                DebugP_log("[LPM UART WAKEUP] Suspend request to MCU-only mode received \r\n");
                DebugP_log("[LPM UART WAKEUP] Press a single key on this terminal to resume the kernel from MCU only mode \r\n");

                IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_AUTO, 1U);
                LpmApp_waitForUART();
                gbSuspended = 0U;
                break;

            case TISCI_MSG_VALUE_HOST_STATE_INVALID:
            default:
                IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_CANCEL, 1U);
                break;
        }

        if (gbShutdown == 1U)
        {
            break;
        }
    }
    SemaphoreP_destruct(&gLpmSuspendSem);

    SemaphoreP_destruct(&gLpmResumeSem);

    vTaskDelete(NULL);
}

static void LpmApp_createSuspendTask(void)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Create the tasks which will handle the ping service */
    TaskP_Params_init(&taskParams);
    taskParams.name = "LPM_MCU_SUSPEND";
    taskParams.stackSize = LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE;
    taskParams.stack = gLpmSuspendTaskStack;
    taskParams.priority = LPM_APP_MCU_SUSPEND_TASK_PRI;
    taskParams.taskMain = LpmApp_suspendTask;

    status = TaskP_construct(&gLpmSuspendTask, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);
}

void LpmApp_wakeupMain(void *args)
{
    int32_t status;

    DebugP_log("[LPM UART WAKEUP] Example Application Started...\r\n");

    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status==SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &LpmApp_ipcRpMboxCallback, NULL);

    /* Create task to enable graceful lpm suspend support for remotecore   */
    LpmApp_createSuspendTask();

    /* create message receive tasks, these tasks always run and never exit */
    LpmApp_createRecvTasks();

    /* wait for all non-Linux cores to be ready, this ensure that when we send messages below
     * they wont be lost due to rpmsg end point not created at remote core
     */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    /* exit from this task, vTaskDelete() is called outside this function, so simply return */

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
#if defined(BUILD_C7X)
    asm("    IDLE");
#endif
}
