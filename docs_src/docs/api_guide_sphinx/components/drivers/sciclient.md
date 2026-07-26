# SCICLIENT

```{contents}
:depth: 2
:local:
```

:::{only} SOC_AM64X or SOC_AM243X
   Devices AM64x and AM243x fall under the K3 SoC family and has a concept of centralized Power, Resource and Security management to allow mitigating the challenges of the traditional approach to system control. System Firmware (hereafter referred to as SYSFW) is the collective name for the security and device management firmware which offers these centralized services. In this concept a processing unit (for example an R5F) can request the SYSFW to control power, grant resources or provide secure services. This is done via a special messaging channel called a **secure proxy**. The messages are sent obeying a proprietary protocol called TISCI (TI System Controller Interface) protocol. For more information on TISCI protocol you can refer to the [**TISCI Public Documentation**](https://software-dl.ti.com/tisci/esd/latest/index.html).
:::


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X
   Device AM62x fall under the K3 SoC family and has a concept of centralized Power, Resource and Security management to allow mitigating the challenges of the traditional approach to system control. System Firmware (hereafter referred to as SYSFW) is the collective name for the TI foundational security(TIFS) and device management firmware (DM firmware) which offers these centralized services. In this concept a processing unit (for example an M4F) can request the DM firmware to control power, grant resources or provide secure services. This is done via a special messaging channel called a **secure proxy**. The messages are sent obeying a proprietary protocol called TISCI (TI System Controller Interface) protocol. For more information on TISCI protocol you can refer to the [**TISCI Public Documentation**](https://software-dl.ti.com/tisci/esd/latest/index.html).
:::


Sciclient as a software block has multiple functional sub-blocks inside it, as shown in the below image:
![Sciclient Sub-blocks](../../images/sciclient/sciclient_block.png)


More details on the APIs provided on these layers can be found in the API section, linked towards the end of this page.

Generally speaking, the Sciclient driver provides API to communicate with the SYSFW using the TISCI protocol. As mentioned above, this would be for system level tasks like resource allocation, peripheral power on/off, peripheral clock setting, secure services and so on. The sciclient will be part of the application code running on each core.
![Typical Sciclient Operation](../../images/sciclient/sciclient_sysfw.png)


The above image shows the operation for only one core, but the same thing happens for all the cores. SYSFW deals with all the requests coming from each of the cores.

Sciclient is mostly used by other drivers, like DMA, GPIO etc. Sciclient acts as an interface to the SYSFW for these drivers when they need say a resource like DMA channel, or configure an interrupt route. Below are the high level features supported by the driver:

## Features Supported


:::{only} SOC_AM64X or SOC_AM243X
   - APIs to load the SYSFW onto the DMSC core
   - APIs to pass a specific board configuration to the SYSFW
   - Abstracted APIs for Power and Resource Management
   - APIs for Processor Boot including secure boot
   - APIs for configuring firewalls
:::


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X
   - Abstracted APIs for Power and Resource Management
   - APIs for Processor Boot including secure boot
   - APIs for configuring firewalls
   - Ability to change and re-build the board configuration data
   - Ability to sign the board configuration blobs for HS devices
:::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- There are no user programmable features for Sciclient SysConfig. However, adding any module makes the PowerClock_init() initialize the module power and clock. This is indirectly done using Sciclient APIs.

## Features NOT Supported

NA

## Important Usage Guidelines

- Sciclient is mostly used by other peripheral drivers, and mostly not directly by an application. From an application point of view, major usage of Sciclient APIs would be to power on/off a module, set/get the clock of a module, etc.

:::{only} SOC_AM64X or SOC_AM243X
   This is abstracted in the SOC specific layer.
:::


## Board Configuration Overview
SYSFW Board Config files in the sciclient driver is a SOC specific configuration data regarding the various system attributes
controlled by the SYSFW. These include resources, power and clock, security etc. This configuration is sent to SYSFW during boot
time. The default configuration is stored in `source/drivers/sciclient/sciclient_defaultBoardCfg/{{ VAR_SOC_NAME_LOWER }}/`

- Default Boardcfg - sciclient_defaultBoardcfg.c
- Resource Management BoardCfg - sciclient_defaultBoardCfg_rm.c
- Power Management BoardCfg - sciclient_defaultBoardCfg_pm.c
- Security BoardCfg - sciclient_defaultBoardCfg_security.c

The user can change the board configuration data based on their requirement and rebuild the board configuration by following
the steps in [SYSFW Board Config Generation](../tools/tools_sysfw.md).

Refer [SYSFW board config documentation](http://downloads.ti.com/tisci/esd/latest/3_boardcfg/index.html)


:::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X
   ### Enforcing Processor Access Control List

   - The Access Control List(ACL) for a processor can be set using the Security Boardcfg data. There can be one primary
   host and three secondary hosts that can control a processor.

   - For example, set the WKUP-R5 core as primary host and A53 core as secondary host for ACL of MCU-R5 processor
   in the `source/drivers/sciclient/sciclient_defaultBoardCfg/{{ VAR_SOC_NAME_LOWER }}/sciclient_defaultBoardCfg_security.c` file.

   ::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X

      ```
      .proc_acl_entries = {
      {
          .processor_id = SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0,
          .proc_access_master = TISCI_HOST_ID_MAIN_0_R5_0,
          .proc_access_secondary = {TISCI_HOST_ID_A53_0, TISCI_HOST_ID_TIFS, TISCI_HOST_ID_TIFS},
      },
      /* set the remaining entries to zero */
      {
          0,
      },
      .
      .
      .
      {
          0,
      },
      },
      ```

   ::::

   ::::{only} SOC_AM62PX

      ```
      .proc_acl_entries = {
      {
          .processor_id = SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0,
          .proc_access_master = TISCI_HOST_ID_WKUP_0_R5_0,
          .proc_access_secondary = {TISCI_HOST_ID_A53_0, TISCI_HOST_ID_TIFS, TISCI_HOST_ID_TIFS},
      },
      /* set the remaining entries to zero */
      {
          0,
      },
      .
      .
      .
      {
          0,
      },
      },
      ```

   ::::


   - Then rebuild the board config blobs using the steps in [SYSFW Board Config Generation](../tools/tools_sysfw.md).
   - Check on [SYSFW documentation](https://downloads.ti.com/tisci/esd/latest/3_boardcfg/BOARDCFG_SEC.html#processor-access-list) for more info.
:::


## Example Usage

### Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Sciclient_sample.c
:language: c
:lines: 3-4
```

### Module Power ON Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Sciclient_sample.c
:language: c
:lines: 10-35
```


:::{only} SOC_AM64X or SOC_AM243X
   ### Interrupt configuration Example

   Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
   Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer [AM64x/AM243x TRM](https://www.ti.com/lit/ug/spruim2c/spruim2c.pdf) Chapter 9 on interrupts. The `INTRTR Integration` subsection explains the routing with a diagram.
:::


:::{only} SOC_AM62X
   ### Interrupt configuration Example

   Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
   Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer [AM62x TRM](https://www.ti.com/lit/ug/spruiv7/spruiv7.pdf) Chapter 9 on interrupts.
:::


:::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X
   ### Interrupt configuration Example

   Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
   Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer [AM62Ax TRM](https://www.ti.com) Chapter 9 on interrupts.
:::

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Sciclient_sample.c
:language: c
:lines: 45-104
```

### Configuring the Flag Field in TISCI Messages

To receive a response message, `TISCI_MSG_FLAG_AOP` is used in the flag field of the outgoing message. But, if a response is not needed, then the flag field can be set to 0 instead. That being said, setting the flag field to 0 means no response will be returned, even if the message fails.

When sending TISCI messages, it is recommended to avoid directly writing to the generic header in the payload (request.hdr.flags). Instead, we use the `Sciclient_service` API and pass the field value to the Sciclient request parameter (reqParam.flags).

To utilize the `Sciclient_service` API, the following components must be defined:

- TISCI Request - Define an empty TISCI request structure for the TISCI message type and specify the various required fields in it. We can leave the fields of `tisci_header` structure as empty.
- TISCI Response - Define an empty TISCI response structure for the TISCI message type.
- Request Parameters - Define the structure of the Sciclient request message, and specify the following fields in it -
  - Message Type - Specify the type of message being transmitted.
  - Flags - Determine the custom flag options, selecting either `TISCI_MSG_FLAG_AOP` for messages requiring a response or `0` for messages that do not require a response.
  - Request Payload - Pass the TISCI Request structure.
  - Request Payload Size - Pass the size of the TISCI Request structure.
  - Timeout - Specify the timeout value for the message.
- Response Parameters - Define the expected structure of the Sciclient response message, and specify the following fields in it -
  - Response Payload - Pass the TISCI Response structure.
  - Response Payload Size - Pass the size of the TISCI Response structure.

The `Sciclient_service` call will then copy the message type and the flag value specified in the Sciclient request structure (reqParam.flags) into the TISCI Generic Messaging Header (request.hdr.flags) of the TISCI Request message. This enables users to send messages with AOP or empty flag settings without directly manipulating the TISCI Generic Header.

To learn more about the TISCI Generic Messaging Header, refer to the [TISCI Generic Messaging Header](https://software-dl.ti.com/tisci/esd/latest/2_tisci_msgs/general/TISCI_header.html#tisci-generic-messaging-header) documentation. And for more information on supported message types and required parameters, refer to the `DRV_SCICLIENT_MODULE` documentation.

Example -
```
    int32_t retVal = SystemP_SUCCESS;
    struct tisci_msg_get_device_req request = {0};
    struct tisci_msg_get_device_resp response = {0};
    Sciclient_ReqPrm_t reqParam = {0};

    Sciclient_RespPrm_t respParam = {0};

    request.id = (uint32_t) TISCI_DEV_A53SS0;

    reqParam.messageType    = (uint16_t) TISCI_MSG_GET_DEVICE;
    reqParam.flags          = (uint32_t) 0;    /* We can set this value to either 0 or `TISCI_MSG_FLAG_AOP` */
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) timeout;

    respParam.flags           = (uint32_t) 0;    /* Populated by the API when `TISCI_MSG_FLAG_AOP` flag is set in the request */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof (response);

    retVal = Sciclient_service(&reqParam, &respParam);
    if(retVal != SystemP_SUCCESS)
    {
        retVal = SystemP_FAILURE;
    }
```
:::{admonition} Note
Setting the flags value to 0 in the request parameter structure using the `Sciclient_service` API may cause the message to fail.
:::


## Enabling Interrupt Mode
Sciclient can operate in two modes for processing TISCI messages:

- **Polling Mode (Default)**: The driver polls for the response from SYSFW/DM after sending a request. This is the default mode.
- **Interrupt Mode**: The driver uses interrupts to detect when a response is available, allowing the CPU to perform other tasks while waiting.

To switch the mode to Interrupt Mode, follow the steps below:


:::{only} SOC_AM62X
- Add the line `-DENABLE_SCICLIENT_INTERRUPT_MODE \` to `DEFINES_common` in `source/drivers/makefile.am62x.m4f.ti-arm-clang`.
:::


:::{only} SOC_AM62AX
- Add the line `-DENABLE_SCICLIENT_INTERRUPT_MODE \` to `DEFINES_common` in `source/drivers/makefile.am62ax.r5f.ti-arm-clang`.
:::


:::{only} SOC_AM62DX
- Add the line `-DENABLE_SCICLIENT_INTERRUPT_MODE \` to `DEFINES_common` in `source/drivers/makefile.am62dx.r5f.ti-arm-clang`.
:::


:::{only} SOC_AM62PX
- Add the line `-DENABLE_SCICLIENT_INTERRUPT_MODE \` to `DEFINES_common` in `source/drivers/makefile.am62px.mcu-r5f.ti-arm-clang`.
:::


:::{only} SOC_AM275X
- Add the line `-DENABLE_SCICLIENT_INTERRUPT_MODE \` to `DEFINES_common` in `source/drivers/makefile.am275x.r5f.ti-arm-clang`.
:::

  - Rebuild the libraries and application.


## API Reference

```{doxygenfile} sciclient.h
```
