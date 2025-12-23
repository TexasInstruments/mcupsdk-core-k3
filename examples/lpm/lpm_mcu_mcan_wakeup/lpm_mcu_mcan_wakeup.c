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
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/pinmux.h>
#include <kernel/dpl/AddrTranslateP.h>

/* This example shows message exchange between Linux and RTOS/NORTOS cores.
 * This example also demonstrates the MCAN rx wakeup capability in MCU Only
 * low power mode.
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
 * receive MCAN transition to resume from lpm.
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
#define LPM_APP_IPC_RPMESSAGE_SERVICE_PING          "ti.ipc4.ping-pong"
#define LPM_APP_IPC_RPMESSAGE_ENDPT_PING            (13U)

/* This is used to run the echo test with user space kernel */
#define LPM_APP_IPC_RPMESSAGE_SERVICE_CHRDEV        "rpmsg_chrdev"
#define LPM_APP_IPC_RPMESSAGE_ENDPT_CHRDEV_PING     (14U)

/* Maximum size that message can have in this example
 * RPMsg maximum size is 512 bytes in linux including the header of 16 bytes.
 * Message payload size without the header is 512 - 16 = 496
 */
#define LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE          (496U)

/*
 * Number of RP Message ping "servers" we will start,
 * - one for ping messages for linux kernel "sample ping" client
 * - and another for ping messages from linux "user space" client using "rpmsg char"
 */
#define LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS        (2U)

/* MCAN Base address */
#define LPM_APP_MCAN_BASE_ADDR                      (CONFIG_MCAN0_BASE_ADDR)

/* MCAN IP interrupt number */
#define LPM_APP_MCAN_INTR_NUM                       (CONFIG_MCAN0_INTR)

/* Number of standard Filter elements */
#define LPM_APP_MCAN_STD_ID_FILTER_CNT              (1U)

/* Number of extended Filter elements */
#define LPM_APP_MCAN_EXT_ID_FILTER_CNT              (0U)

/* Maximum number of elements that can be stored in RX FIFO 0 */
#define LPM_APP_MCAN_FIFO_0_CNT                     (0U)

/* Maximum number of elements that can be stored in RX FIFO 1 */
#define LPM_APP_MCAN_FIFO_1_CNT                     (0U)

/* Extended ID Mask */
#define LPM_APP_MCAN_EXT_ID_MASK                    (0x1FFFFFFFU)

/* Standard ID configured in this app */
#define LPM_APP_MCAN_STD_ID                         (0xC0U)

/* Task priority, stack, stack size and task objects, these MUST be global's */
#define LPM_APP_IPC_RPMESSAGE_TASK_PRI              (8U)
#define LPM_APP_MCU_SUSPEND_TASK_PRI                (8U)

#define LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE       (8U * 1024U)
#define LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE         (1024U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* RPMessage object used to receive messages */
RPMessage_Object gIpcRecvMsgObject[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

uint8_t gIpcTaskStack[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS][LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gIpcTask[LPM_APP_IPC_RPMESSAGE_NUM_RECV_TASKS];

uint8_t gLpmSuspendTaskStack[LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gLpmSuspendTask;

/* MCU I/Os are isolated in lpm that can prevent the CAN signal from reaching IP, so bypass the isolation.
 * If the MCAN Base address corresponds to MCAN0, then bypass isolation for MCAN0 pins and vice versa.
 */
#if (CSL_MCU_MCAN0_CFG_BASE == CONFIG_MCAN0_BASE_ADDR)
static Pinmux_PerCfg_t gPinMuxMcuDomainCfg[] = {
    /* MCU_MCAN0 pin config */
            /* MCU_MCAN0_RX -> MCU_MCAN0_RX */
    {
        PIN_MCU_MCAN0_RX,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },
            /* MCU_MCAN1_TX -> MCU_MCAN0_TX */
    {
        PIN_MCU_MCAN0_TX,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },

    {PINMUX_END, 0U}
};
#else
static Pinmux_PerCfg_t gPinMuxMcuDomainCfg[] = {
    /* MCU_MCAN1 pin config */
            /* MCU_MCAN1_RX -> MCU_MCAN1_RX */
    {
        PIN_MCU_MCAN1_RX,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },
            /* MCU_MCAN1_TX -> MCU_MCAN1_TX */
    {
        PIN_MCU_MCAN1_TX,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_ISOLATION_BYPASS )
    },

    {PINMUX_END, 0U}
};
#endif

volatile uint8_t    gbShutdown = 0U;
volatile uint8_t    gbShutdownRemotecoreID = 0U;
volatile uint8_t    gbSuspended = 0U;
volatile uint8_t    gbSuspendRemotecoreID = 0U;
volatile uint32_t   gMCANMsgRcvd = 0U;
volatile uint8_t    gRecvTaskExitCounter = 0U;
static uint32_t     gMcanBaseAddr;
static HwiP_Object  gMcanHwiObject;

SemaphoreP_Object gLpmResumeSem;
SemaphoreP_Object gLpmSuspendSem;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpmApp_mcanInitMsgRamConfigParams(MCAN_MsgRAMConfigParams
                                           *msgRAMConfigParams);
static void LpmApp_mcanInitStdFilterElemParams(MCAN_StdMsgIDFilterElement *stdFiltElem,
                                            uint32_t bufNum);
static void LpmApp_mcanEnableIntr(void);
static void LpmApp_mcanRxCallback(void *arg);
static void LpmApp_mcanConfig(void);
static void LpmApp_registerMCANIntr(void);
static void LpmApp_mcuWaitForMCAN(void);
static void LpmApp_mcanRxIntrService(void);
static void LpmApp_triggerShutdown(void);
static inline void LpmApp_putCPUInWFI(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void LpmApp_ipcRecvTaskMain(void *args)
{
    int32_t status;
    char recvMsg[LPM_APP_IPC_RPMESSAGE_MAX_MSG_SIZE+1]; /* +1 for NULL char in worst case */
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;

    DebugP_log("Remote Core waiting for messages at end point %d ... !!!\r\n",
        RPMessage_getLocalEndPt(pRpmsgObj)
        );

    /* Wait for messages forever in a loop */
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
        DebugP_log("Closing all drivers and going to WFI ... !!!\r\n");

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

void LpmApp_ipcRpmsgCreateRecvTasks(void)
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
    /* We use the same task function for echo but pass the appropriate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[0];
    taskParams.taskMain = LpmApp_ipcRecvTaskMain;

    status = TaskP_construct(&gIpcTask[0], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_CHAR_PING";
    taskParams.stackSize = LPM_APP_IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[1];
    taskParams.priority = LPM_APP_IPC_RPMESSAGE_TASK_PRI;
    /* We use the same task function for echo but pass the appropriate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[1];
    taskParams.taskMain = LpmApp_ipcRecvTaskMain;

    status = TaskP_construct(&gIpcTask[1], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);
}

void LpmApp_ipcRpMboxCallback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
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

            if (gMCANMsgRcvd != 0U)
            {
                /* Post this only for MCU IPs Wakeup */
                SemaphoreP_post(&gLpmResumeSem);
            }
            DebugP_shmLogWriterResume();

            IpcNotify_sendMsg(remoteCoreId, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_ECHO_REPLY, 1U);
        }
    }
}

void LpmApp_mcuSuspendTask(void* args)
{
    int32_t status;

    /* Enable isolation bypass bit to enable wakeup from MCAN */
    Pinmux_config(gPinMuxMcuDomainCfg, PINMUX_DOMAIN_ID_MCU);

    LpmApp_registerMCANIntr();
    /* Configure MCAN IP to receive */
    LpmApp_mcanConfig();
    /* Enable the MCAN interrupt */
    LpmApp_mcanEnableIntr();

    DebugP_log("MCAN configured to receive packet ... !!!\r\n");

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
            DebugP_log("Failed to get next system state. Canceling suspend.\r\n");
            IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_CANCEL, 1U);
            continue;
        }

        DebugP_log("Next MCU mode is %d\r\n", nextHostState);

        switch (nextHostState)
        {
            case TISCI_MSG_VALUE_HOST_STATE_OFF:
                IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_ACK, 1U);
                break;
            case TISCI_MSG_VALUE_HOST_STATE_ON:
                gbSuspended = 1U;

                /* Print before sending ACK, otherwise IO isolation is enabled while printing */
                DebugP_log("Suspend request to MCU-only mode received \r\n");
                DebugP_log("Send MCAN packet to resume the kernel from MCU only mode \r\n");

                IpcNotify_sendMsg(gbSuspendRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SUSPEND_AUTO, 1U);
                LpmApp_mcuWaitForMCAN();
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

    /* Unregister MCAN interrupt */
    HwiP_destruct(&gMcanHwiObject);

    /* De-Construct Suspend resume Semaphore objects */
    SemaphoreP_destruct(&gLpmSuspendSem);
    SemaphoreP_destruct(&gLpmResumeSem);

    vTaskDelete(NULL);
}

void LpmApp_createSuspendTask(void)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Create the tasks which will handle the ping service */
    TaskP_Params_init(&taskParams);
    taskParams.name = "LPM_MCU_SUSPEND";
    taskParams.stackSize = LPM_APP_MCU_SUSPEND_TASK_STACK_SIZE;
    taskParams.stack = gLpmSuspendTaskStack;
    taskParams.priority = LPM_APP_MCU_SUSPEND_TASK_PRI;
    taskParams.taskMain = LpmApp_mcuSuspendTask;

    status = TaskP_construct(&gLpmSuspendTask, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);
}

void lpm_mcu_mcan_wakeup_main(void *args)
{
    int32_t status;

    DebugP_log("LPM MCU MCAN WAKEUP Application Started!! \r\n");

    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status==SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver */
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &LpmApp_ipcRpMboxCallback, NULL);

    /* Create task to enable graceful lpm suspend support for remotecore */
    LpmApp_createSuspendTask();

    /* create message receive tasks, these tasks always run and never exit */
    LpmApp_ipcRpmsgCreateRecvTasks();

    /* Wait for all non-Linux cores to be ready, this ensure that when we send messages below
     * they wont be lost due to rpmsg end point not created at remote core
     */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    /* Exit from this task, vTaskDelete() is called outside this function, so simply return */

}

static void LpmApp_mcanInitMsgRamConfigParams(MCAN_MsgRAMConfigParams
                                           *msgRAMConfigParams)
{
    int32_t status;

    MCAN_initMsgRamConfigParams(msgRAMConfigParams);

    /* Configure the user required msg ram params */
    msgRAMConfigParams->lss = LPM_APP_MCAN_STD_ID_FILTER_CNT;
    msgRAMConfigParams->lse = LPM_APP_MCAN_EXT_ID_FILTER_CNT;

    msgRAMConfigParams->rxFIFO0Cnt = LPM_APP_MCAN_FIFO_0_CNT;
    msgRAMConfigParams->rxFIFO1Cnt = LPM_APP_MCAN_FIFO_1_CNT;

    /* FIFO blocking mode is selected */
    msgRAMConfigParams->rxFIFO0OpMode = MCAN_RX_FIFO_OPERATION_MODE_BLOCKING;
    msgRAMConfigParams->rxFIFO1OpMode = MCAN_RX_FIFO_OPERATION_MODE_BLOCKING;

    status = MCAN_calcMsgRamParamsStartAddr(msgRAMConfigParams);
    DebugP_assert(status == CSL_PASS);

    return;
}

static void LpmApp_mcanInitStdFilterElemParams(MCAN_StdMsgIDFilterElement *stdFiltElem,
                                            uint32_t bufNum)
{
    /* sfid1 defines the ID of the standard message to be stored. */
    stdFiltElem->sfid1 = LPM_APP_MCAN_STD_ID;
    /* As buffer mode is selected, sfid2 should be bufNum[0 - 63] */
    stdFiltElem->sfid2 = bufNum;
    /* Store message in buffer */
    stdFiltElem->sfec  = MCAN_STD_FILT_ELEM_BUFFER;
    /* Below configuration is ignored if message is stored in buffer */
    stdFiltElem->sft   = MCAN_STD_FILT_TYPE_RANGE;

    return;
}

static void LpmApp_mcanEnableIntr(void)
{
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(gMcanBaseAddr,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line 0 */
    MCAN_selectIntrLine(gMcanBaseAddr, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_0);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr, MCAN_INTR_LINE_NUM_0, (uint32_t)TRUE);

    return;
}

static void LpmApp_mcanRxIntrService(void)
{
    MCAN_RxNewDataStatus    newDataStatus;
    MCAN_ErrCntStatus       errCounter;
    uint32_t                bufNum, fifoNum, bitPos = 0U;
    MCAN_RxBufElement       rxMsg;

    /* Check for Rx Errors */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    /* Assert only for errors encountered during lpm */
    if (gbSuspended == 1U)
    {
        DebugP_assert((0U == errCounter.recErrCnt) && (0U == errCounter.canErrLogCnt));
    }

    /* Get the new data status, indicates buffer num which received message */
    MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
    MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);

    /* Select buffer and fifo number, Buffer is used in this app */
    bufNum = 0U;
    fifoNum = MCAN_RX_FIFO_NUM_0;

    bitPos = (1U << bufNum);
    if (bitPos == (newDataStatus.statusLow & bitPos))
    {
        MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, bufNum, fifoNum, &rxMsg);
    }
    else if (gbSuspended == 1U)
    {
        DebugP_assert(FALSE);
    }
}

static void LpmApp_mcanRxCallback(void *arg)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(gMcanBaseAddr);
    MCAN_clearIntrStatus(gMcanBaseAddr, intrStatus);

    /* If FIFO0/FIFO1 is used, then MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG macro
     * needs to be replaced by MCAN_INTR_SRC_RX_FIFO0_NEW_MSG or
     * MCAN_INTR_SRC_RX_FIFO1_NEW_MSG respectively
     */
    if (MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG ==
        (intrStatus & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG))
    {
        LpmApp_mcanRxIntrService();
        gMCANMsgRcvd = 1U;
    }

    return;
}

static void LpmApp_mcanConfig(void)
{
    MCAN_StdMsgIDFilterElement stdFiltElem[LPM_APP_MCAN_STD_ID_FILTER_CNT] = {0U};
    MCAN_InitParams            initParams = {0U};
    MCAN_ConfigParams          configParams = {0U};
    MCAN_MsgRAMConfigParams    msgRAMConfigParams = {0U};
    MCAN_BitTimingParams       bitTimes = {0U};
    uint32_t                   i;

    /* Assign MCAN instance address */
    gMcanBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(LPM_APP_MCAN_BASE_ADDR);

    /* Initialize MCAN module initParams (CAN FD Mode and Bit Rate Switch Enabled)  */
    MCAN_initOperModeParams(&initParams);

    /* Initialize MCAN module Global Filter Params */
    MCAN_initGlobalFilterConfigParams(&configParams);

    /* Initialize MCAN module Bit Time Params */
    /* Configuring default 1Mbps and 5Mbps as nominal and data bit-rate resp */
    MCAN_initSetBitTimeParams(&bitTimes);

    /* Initialize MCAN module Message Ram Params */
    LpmApp_mcanInitMsgRamConfigParams(&msgRAMConfigParams);

    /* Initialize Filter element to receive msg */
    for (i = 0U; i < LPM_APP_MCAN_STD_ID_FILTER_CNT; i++)
    {
        LpmApp_mcanInitStdFilterElemParams(&stdFiltElem[i], i);
    }
    /* Wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(gMcanBaseAddr))
    {
        /* do nothing */
    }

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {
        /* do nothing */
    }

    /* Initialize MCAN module */
    MCAN_init(gMcanBaseAddr, &initParams);
    /* Configure MCAN module Global Filter */
    MCAN_config(gMcanBaseAddr, &configParams);
    /* Configure Bit timings */
    MCAN_setBitTime(gMcanBaseAddr, &bitTimes);
    /* Configure Message RAM Sections */
    MCAN_msgRAMConfig(gMcanBaseAddr, &msgRAMConfigParams);
    /* Set Extended ID Mask */
    MCAN_setExtIDAndMask(gMcanBaseAddr, LPM_APP_MCAN_EXT_ID_MASK);

    /* Configure Standard ID filter element */
    for (i = 0U; i < LPM_APP_MCAN_STD_ID_FILTER_CNT; i++)
    {
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, i, &stdFiltElem[i]);
    }

    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {
        /* do nothing */
    }

    return;
}

static void LpmApp_registerMCANIntr(void)
{
    int32_t                 status = SystemP_SUCCESS;
    HwiP_Params             hwiPrms;

    /* Register interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = LPM_APP_MCAN_INTR_NUM;
    hwiPrms.callback    = &LpmApp_mcanRxCallback;
    status              = HwiP_construct(&gMcanHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);
}

static void LpmApp_mcuWaitForMCAN(void)
{
    /* Update the global variable in handler/callback */
    gMCANMsgRcvd = 0U;

    DebugP_memLogWriterPause();

    /* Wait for MCAN event or other event */
    while (gMCANMsgRcvd == 0U && gbSuspended == 1U)
    {
        LpmApp_putCPUInWFI();
    }

    if (gMCANMsgRcvd != 0U)
    {
        DebugP_log("MCAN event detected. Notifying DM to wakeup main domain\r\n");
        SOC_triggerMcuLpmWakeup();
        /* Wait for resuming the main domain */
        SemaphoreP_pend(&gLpmResumeSem, SystemP_WAIT_FOREVER);

        DebugP_log("Main domain resumed due to MCU MCAN\r\n");
    }
    else if (gbSuspended == 0U)
    {
        DebugP_log("Main domain resumed from a different wakeup source \r\n");
    }

    DebugP_memLogWriterResume();
}

static void LpmApp_triggerShutdown(void)
{
    gbShutdown = 1U;
    RPMessage_unblock(&gIpcRecvMsgObject[0]);
    RPMessage_unblock(&gIpcRecvMsgObject[1]);
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

