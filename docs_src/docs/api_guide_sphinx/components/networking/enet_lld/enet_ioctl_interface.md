# Enet LLD IOCTL interface

```{contents}
:depth: 2
:local:
```

## Introduction

The Enet LLD provides an IOCTL interface to configure the control related functionality of the Ethernet hardware, via `Enet_ioctl()` function.

The IOCTLs commands are classified according to the Enet LLD layer they belong: peripheral or module. The module IOCTL commands are further grouped into sets related to hardware modules typically found in Ethernet peripherals.

- Peripheral layer IOCTLs: `EnetPer_Ioctl_e`
- Module layer IOCTLs
  - Host port IOCTLs: `EnetHostPort_Ioctl`
  - MAC port IOCTLs: `EnetMacPort_Ioctl`
  - Forwarding database (FDB) IOCTLs: `EnetFdb_Ioctl`
  - MDIO IOCTLs: `EnetMdio_Ioctl`
  - Statistics IOCTLs: `EnetStats_Ioctl`
  - Time synchronization IOCTLs: `EnetTimeSync_Ioctl`

## Using the IOCTL interface

The `Enet_ioctl()` function takes the following parameters:

- Enet driver handle which is obtained after opening the driver via `Enet_open()` function.
- Core id of the caller which is needed to identify calls originated locally or from a remote core.
- IOCTL command id.
- IOCTL arguments, which can be either input argument, output argument, both or none. Please refer to the description of each IOCTL to find out the required parameters and their types.

Enet LLD provides helper macros to setup the IOCTL parameters. There are four helper macros available to choose depending on the number of arguments:

- `ENET_IOCTL_SET_NO_ARGS` for IOCTLs that don't take any arguments.
- `ENET_IOCTL_SET_IN_ARGS` for IOCTLs that take only input arguments.
- `ENET_IOCTL_SET_OUT_ARGS` for IOCTLs that take only output arguments.
- `ENET_IOCTL_SET_INOUT_ARGS` for IOCTLs that take both, input and output arguments.

The code snippet below shows an example of the Enet LLD IOCTL interface, used for reading the version of an Ethernet peripheral.

```c
void myFunction(void)
{
    Enet_Handle hEnet;
    Enet_IoctlPrms prms;
    Enet_Version version;
    int32_t status;

    ...

    /* Open the Enet LLD */
    hEnet = Enet_open(enetType, 0U, cfg, cfgSize);

    ...

    /* Prepare IOCTL params */
    ENET_IOCTL_SET_OUT_ARGS(&prms, &version);

    /* Do the IOCTL command */
    status = Enet_ioctl(hEnet, coreId, ENET_PER_IOCTL_GET_VERSION, &prms);
    if (status != ENET_SOK)
    {
        printf("Failed to get Enet peripheral version: %d\n", status);
    }

    ...

    /* Close the Enet LLD */
    Enet_close(hEnet);

    ...
}
```

## Synchronous and Asynchronous IOCTLs

The IOCTLs commands can be synchronous or asynchronous in nature. Synchronous IOCTLs execute immediately and return the operation status. Asynchronous IOCTLs initiate an operation but don't wait for completion, they return `ENET_SINPROGRESS` code. The application must call `Enet_poll()` function to poll for the operation completion event.

The synchronous or asynchronous nature of IOCTLs is peripheral dependent, please refer to the peripheral specific documentation for further details.

The sample code in previous section corresponds to a synchronous IOCTL. The code snippet below shows the Enet LLD APIs involved in handling an asynchronous IOCTL.

```c
Enet_Handle hEnet;
Semaphore_Handle sem;

void myFunc(void)
{
    Enet_IoctlPrms prms;
    Enet_Event evt;
    SemaphoreP_Status semStatus;
    int32_t status;

    ...

    /* Open the Enet LLD */
    hEnet = Enet_open(enetType, 0U, cfg, cfgSize);

    ...

    /* Register an event callback function. This function is called upon event
     * detection in Enet_poll() */
    Enet_registerEventCb(hEnet, ENET_EVT_ASYNC_CMD_RESP, 0U, myEventCallbackFunc, NULL);

    ...

    /* Prepare IOCTL params */
    ENET_IOCTL_SET_NO_ARGS(&prms);

    /* Run asynchronous IOCTL command */
    status = Enet_ioctl(hEnet, coreId, ENET_FDB_IOCTL_REMOVE_ALL_ENTRIES, &prms);
    if (status == ENET_SINPROGRESS)
    {
        /* Wait for async ioctl to complete */
        do
        {
            Enet_poll(hEnet, ENET_EVT_ASYNC_CMD_RESP, NULL, 0);
            semStatus = SemaphoreP_pend(sem, 1U);
        } while (semStatus != SemaphoreP_OK);

        status = ENET_SOK;
    }
    else if (status != ENET_SOK)
    {
        printf("Failed to run IOCTL command: %d\n", status);
    }

    ...

    /* Unregister event callback function */
    Enet_registerEventCb(hEnet, evt, 0U);

    ...

    /* Close the Enet LLD */
    Enet_close(hEnet);

    ...
}

void myEventCallbackFunc(Enet_Event evt,
                         uint32_t evtNum,
                         void *evtCbArgs,
                         void *arg1,
                         void *arg2)
{
    /* ENET_EVT_ASYNC_CMD_RESP has occurred! */
    Semaphore_post(sem);
}
```
