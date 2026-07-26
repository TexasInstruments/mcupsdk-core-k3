# Graceful shutdown of remote cores from Linux
## Introduction


:::{only} SOC_AM62X
   Linux running on A53 core can load the firmware to the remote cores. MCU M4F core incase of AM62X. Refer [Linux Academy for AM62X](https://dev.ti.com/tirex/explore/node?node=A__AISILbMWZ4d84U2oSmXcdA__linux_academy_am62x__XaWts8R__LATEST) for more details on how to boot the remotecores. This section explains how to add support for graceful shutdown on the remotecore.
:::


:::{only} SOC_AM62AX
   Linux running on A53 core can load the firmware to the remote cores. MCU R5F/ C7X core incase of AM62AX. Refer [AM62Ax Academy](https://dev.ti.com/tirex/explore/node?node=A__AS4TbXvv.-OIrnxuMySmZg__AM62A-ACADEMY__WeZ9SsL__LATEST) for more details on how to boot the remotecores. This section explains how to add support for graceful shutdown on the remotecore.
:::

:::{only} SOC_AM62DX
   Linux running on A53 core can load the firmware to the remote cores. MCU R5F core in case of AM62DX. This section explains how to add support for graceful shutdown on the remotecore.
:::


:::{only} SOC_AM62PX
   Linux running on A53 core can load the firmware to the remote cores. MCU R5F core incase of AM62PX. This section explains how to add support for graceful shutdown on the remotecore.
:::


## Implementing graceful shutdown on remotecore

 - When the following command is used on the Linux to shutdown the remotecore, an IPC message is send to the remote core before shutting it down.

````bash
echo stop > /sys/class/remoteproc/remoteproc0/state
````

 - To receive and handle this IPC message, register a callback as shown below.

````C
    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &ipc_rp_mbox_callback, NULL);
````

 - On the callback unblock the RPMessage for all the RPMsg objects used in the code.
````C
volatile uint8_t gbShutdown = 0u;
volatile uint8_t gbShutdownRemotecoreID = 0u;
void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remotecore */
        {
            gbShutdown = 1u;
            gbShutdownRemotecoreID = remoteCoreId;
            RPMessage_unblock(&gIpcRecvMsgObject[0]);
            RPMessage_unblock(&gIpcRecvMsgObject[1]);
        }
    }
}
````
 - On the suspend thread which is waiting for next lpm suspend message, break all the loops when gbShutdown == 1
 - On the main thread where the IPC is happening, break all the loops when gbShutdown == 1

````C
    /* wait for messages forever in a loop */
    while(1)
    {
        /* set 'recvMsgSize' to size of recv buffer,
        * after return `recvMsgSize` contains actual size of valid data in recv buffer
        */
        recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;
        status = RPMessage_recv(pRpmsgObj,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);

        if (gbShutdown == 1u)
        {
            break;
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
````

- Then follow the below sequence to go to WFI
   - Close all the drivers used
   - Deinit system (It will disable the interrupts and stops the tick timer)
   - Send acknowledgement to Linux core that the core is ready for shutdown
   - Go to WFI / IDLE

````C
    /* Follow the sequence for graceful shutdown for the last recv task */
    DebugP_log("[IPC RPMSG ECHO] Closing all drivers and going to WFI ... !!!\r\n");

    /* Close the drivers */
    Drivers_close();

    /* Deinit System */
    System_deinit();

    if (gbShutdownRemotecoreID)
    {
        /* ACK the shutdown message */
        IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);
    }

    #if (__ARM_ARCH_PROFILE == 'R') ||  (__ARM_ARCH_PROFILE == 'M')
        /* For ARM R and M cores*/
        __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
    #endif
    #if defined(BUILD_C7X)
        asm("    IDLE");
    #endif
````
This is implemented on [IPC RP Message Linux Echo](../examples/drivers/ipc_rpmessage_linux_echo.md)