# SCICLIENT {#DRIVERS_SCICLIENT_PAGE}

[TOC]

\cond SOC_AM64X || SOC_AM243X
Devices AM64x and AM243x fall under the K3 SoC family and has a concept of centralized Power, Resource and Security management to allow mitigating the challenges of the traditional approach to system control. System Firmware (hereafter referred to as SYSFW) is the collective name for the security and device management firmware which offers these centralized services. In this concept a processing unit (for example an R5F) can request the SYSFW to control power, grant resources or provide secure services. This is done via a special messaging channel called a **secure proxy**. The messages are sent obeying a proprietary protocol called TISCI (TI System Controller Interface) protocol. For more information on TISCI protocol you can refer to the \htmllink{https://software-dl.ti.com/tisci/esd/latest/index.html, **TISCI Public Documentation**}.
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX
Device AM62x fall under the K3 SoC family and has a concept of centralized Power, Resource and Security management to allow mitigating the challenges of the traditional approach to system control. System Firmware (hereafter referred to as SYSFW) is the collective name for the TI foundational security(TIFS) and device management firmware (DM firmware) which offers these centralized services. In this concept a processing unit (for example an M4F) can request the DM firmware to control power, grant resources or provide secure services. This is done via a special messaging channel called a **secure proxy**. The messages are sent obeying a proprietary protocol called TISCI (TI System Controller Interface) protocol. For more information on TISCI protocol you can refer to the \htmllink{https://software-dl.ti.com/tisci/esd/latest/index.html, **TISCI Public Documentation**}.
\endcond

Sciclient as a software block has multiple functional sub-blocks inside it, as shown in the below image:

\imageStyle{sciclient_block.png,width:60%}
\image html sciclient_block.png "Sciclient Sub-blocks"

More details on the APIs provided on these layers can be found in the API section, linked towards the end of this page.

Generally speaking, the Sciclient driver provides API to communicate with the SYSFW using the TISCI protocol. As mentioned above, this would be for system level tasks like resource allocation, peripheral power on/off, peripheral clock setting, secure services and so on. The sciclient will be part of the application code running on each core.

\imageStyle{sciclient_sysfw.png,width:60%}
\image html sciclient_sysfw.png "Typical Sciclient Operation"

The above image shows the operation for only one core, but the same thing happens for all the cores. SYSFW deals with all the requests coming from each of the cores.

Sciclient is mostly used by other drivers, like DMA, GPIO etc. Sciclient acts as an interface to the SYSFW for these drivers when they need say a resource like DMA channel, or configure an interrupt route. Below are the high level features supported by the driver:

## Features Supported

\cond SOC_AM64X || SOC_AM243X
- APIs to load the SYSFW onto the DMSC core
- APIs to pass a specific board configuration to the SYSFW
- Abstracted APIs for Power and Resource Management
- APIs for Processor Boot including secure boot
- APIs for configuring firewalls
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX || SOC_AM62PX
- Abstracted APIs for Power and Resource Management
- APIs for Processor Boot including secure boot
- APIs for configuring firewalls
- Ability to change and re-build the board configuration data
- Ability to sign the board configuration blobs for HS devices
\endcond

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- There are no user programmable features for Sciclient SysConfig. However, adding any module makes the PowerClock_init() initialize the module power and clock. This is indirectly done using Sciclient APIs.

## Features NOT Supported

NA

## Important Usage Guidelines

- Sciclient is mostly used by other peripheral drivers, and mostly not directly by an application. From an application point of view, major usage of Sciclient APIs would be to power on/off a module, set/get the clock of a module, etc.
\cond SOC_AM64X || SOC_AM243X
This is abstracted in the SOC specific layer.
\endcond

## Board Configuration Overview {#BOARD_CONFIGURATION}

SYSFW Board Config files in the sciclient driver is a SOC specific configuration data regarding the various system attributes
controlled by the SYSFW. These include resources, power and clock, security etc. This configuration is sent to SYSFW during boot
time. The default configuration is stored in `source/drivers/sciclient/sciclient_defaultBoardCfg/@VAR_SOC_NAME_LOWER/`

- Default Boardcfg - sciclient_defaultBoardcfg.c
- Resource Management BoardCfg - sciclient_defaultBoardCfg_rm.c
- Power Management BoardCfg - sciclient_defaultBoardCfg_pm.c
- Security BoardCfg - sciclient_defaultBoardCfg_security.c

The user can change the board configuration data based on their requirement and rebuild the board configuration by following
the steps in \ref BOARCFG_GEN.

Refer \htmllink{http://downloads.ti.com/tisci/esd/latest/3_boardcfg/index.html,SYSFW board config documentation}

\cond SOC_AM62AX || SOC_AM62DX || SOC_AM62PX
### Enforcing Processor Access Control List

- The Access Control List(ACL) for a processor can be set using the Security Boardcfg data. There can be one primary
host and three secondary hosts that can control a processor.

- For example, set the WKUP-R5 core as primary host and A53 core as secondary host for ACL of MCU-R5 processor
in the `source/drivers/sciclient/sciclient_defaultBoardCfg/@VAR_SOC_NAME_LOWER/sciclient_defaultBoardCfg_security.c` file.
\cond SOC_AM62AX || SOC_AM62DX
\code
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
\endcode
\endcond

\cond SOC_AM62PX
\code
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
\endcode
\endcond

- Then rebuild the board config blobs using the steps in \ref BOARCFG_GEN.
- Check on \htmllink{https://downloads.ti.com/tisci/esd/latest/3_boardcfg/BOARDCFG_SEC.html#processor-access-list,
SYSFW documentation} for more info.
\endcond

## Example Usage

Include the below file to access the APIs
\snippet Sciclient_sample.c include

**Module Power ON Example**
\snippet Sciclient_sample.c sciclient_module_power_on

\cond SOC_AM64X || SOC_AM243X
**Interrupt configuration Example**

Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer \htmllink{https://www.ti.com/lit/ug/spruim2c/spruim2c.pdf, AM64x/AM243x TRM} Chapter 9 on interrupts. The `INTRTR Integration` subsection explains the routing with a diagram.
\endcond

\cond SOC_AM62X
**Interrupt configuration Example**

Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer \htmllink{https://www.ti.com/lit/ug/spruiv7/spruiv7.pdf, AM62x TRM} Chapter 9 on interrupts.
\endcond


\cond SOC_AM62AX || SOC_AM62DX
**Interrupt configuration Example**

Since interrupt router outputs are shared resources, we need Sciclient to configure interrupt routers for certain peripherals like GPIO.
Here is a snippet explaining this with an example of configuring a GPIO interrupt. For more details on the ideas used below, refer \htmllink{https://www.ti.com, AM62Ax TRM} Chapter 9 on interrupts.
\endcond
\snippet Sciclient_sample.c sciclient_rm_irq_gpio

## API

\ref DRV_SCICLIENT_MODULE
