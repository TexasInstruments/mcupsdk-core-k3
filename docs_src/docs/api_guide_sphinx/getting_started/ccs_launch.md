#  CCS Launch, Load and Run
::::{only} SOC_AM62X
:::{admonition} Attention
As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL. This section is only applicable for MCU M4F Core and A53 Core.
:::
::::

::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
:::{admonition} Attention
As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL. This section is only applicable for MCU R5F Core.
:::
::::


:::{admonition} Note
The steps on this page should be done each time EVM is power cycled or when a new CCS session is started.
:::


## Prerequisites
A quick recap of the steps that need to have been done before you proceed
- Make sure you have installed CCS as mentioned in [Download, Install and Setup CCS](ccs_setup.md)

::::{only} SOC_AM62X
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am62x_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am62x_evm_setup.md)
::::
::::{only} SOC_AM62AX
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am62ax_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am62ax_evm_setup.md)
::::
::::{only} SOC_AM62DX
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am62dx_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am62dx_evm_setup.md)
::::
::::{only} SOC_AM62PX
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am62px_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am62px_evm_setup.md)
::::
::::{only} SOC_AM275X
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am275x_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am275x_evm_setup.md)
::::
::::{only} SOC_AM62LX
- Make sure the UART port used for console is identified as mentioned in [Setup UART Terminal](am62lx_evm_setup.md)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [Cable Connections](am62lx_evm_setup.md)
::::

::::{only} SOC_AM273X
- Make sure you have done the steps for a SOC initialization method using [SOC Initialization](am275x_evm_setup.md)
::::


::::{only} SOC_AM263X
- Make sure to follow below steps while running multi core applications.
  - Edit the CCS gel file at "{CCS_Installation_directory}\ccs1200\ccs\ccs_base\emulation\gel\AM263x\am263x.gel"

<!-- IMAGE NOT FOUND: am263x_dualcore_gel_edit_path.PNG -->

  - Modify Line 113 from "mode = AM263x_Check_supported_mode();" to "mode = 1;"

<!-- IMAGE NOT FOUND: am263x_dualcore_gel_update.png -->

  - With this change, CCS always configures the device in "Dual Core Mode" and all four R5 cores can be used.
  - To revert to Lockstep Mode, undo this change.
::::


::::{only} SOC_AWR294X or SOC_AM263X or SOC_AM243X or SOC_AM64X
- Make sure you have done the steps for a SOC initialization method
  - **RECOMMENDED** method is [Flash SOC Initialization Binary](am62x_evm_setup.md)
  - Other options, if recommended method cannot be used, are mentioned in [SOC Initialization](am62x_evm_setup.md)
- Make sure EVM boot mode switch is setup correctly based on the SOC initialization method
::::


::::{only} SOC_AWR294X or SOC_AM263X
- For the **RECOMMENDED** method, [Flash SOC Initialization Binary](am62x_evm_setup.md), the boot mode should be `BOOTMODE_QSPI`
::::


::::{only} SOC_AM243X or SOC_AM64X
- For the **RECOMMENDED** method, [Flash SOC Initialization Binary](am62x_evm_setup.md), the boot mode should be [OSPI NOR BOOT MODE](am62x_evm_setup.md)
::::


::::{only} SOC_AM62X or SOC_AM62AX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62x_evm_setup.md)
::::

::::{only} SOC_AM62PX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62px_evm_setup.md)
::::

::::{only} SOC_AM62DX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62dx_evm_setup.md)
::::
::::{only} SOC_AM62AX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62ax_evm_setup.md)
::::
::::{only} SOC_AM62PX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62px_evm_setup.md)
::::
::::{only} SOC_AM62DX
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62dx_evm_setup.md)
::::
::::{only} SOC_AM62X
- Make sure you have done the steps for a SOC initialization method as per [Flash SOC Initialization Binary](am62x_evm_setup.md)
::::
::::

- Make sure the UART or CCS console logs on doing **EVM POWER-ON** indicate that SOC initialization is successful
- Make sure you have built the example of interest as mentioned in [Build a Hello World example](getting_started_build.md)

## Launch CCS
- Start Project-less Debug with the target configuration created with [Create Target Configuration](ccs_setup.md)


```{figure} ../images/am62dx/ccs_launch_02.png
:align: center

**Start Project-less Debug**
```
- You will see the {{ VAR_SOC_NAME }} target configuration in the "Threads" tab of "Debug" window as shown below

```{figure} ../images/am62dx/ccs_launch_03.png
:align: center

**Target Configuration After Launch**
```


## Load and run example binaries
- **POWER-ON** the EVM


::::{only} SOC_AM243X or SOC_AM64X
- If you dont see the expected SOC initialization logs on UART or CCS console, then recheck your [EVM Setup](am62x_evm_setup.md)
::::


::::{only} SOC_AM62X
- If SBL NULL is flashed on the board by following steps in [Flash SOC Initialization Binary](am62x_evm_setup.md), wait for the following messages from UART

       Starting NULL Bootloader ...

       SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
       SYSFW Firmware revision 0x9
       SYSFW ABI revision 3.1


       INFO: Bootloader_runCpu:176: CPU m4f0-0 is initialized to 400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a530-0 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a530-1 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a531-0 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a531-1 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_loadSelfCpu:229: CPU r5f0-0 is initialized to 400000000 Hz !!!
       INFO: Bootloader_JumpSelfCpu:248: All done, jumping self ...

- If initialization is done by following steps in [SOC Initialization Using SPL](am62x_evm_setup.md), wait for the Linux to be up on the A53 core.

   ```{figure} ../images/am62dx/linux_boot_01.png
   :align: center

   **Linux terminal**
   ```
::::


::::{only} SOC_AM62AX or SOC_AM62DX
::::{only} SOC_AM62AX
- If SBL NULL is flashed on the board by following steps in [Flash SOC Initialization Binary](am62ax_evm_setup.md), wait for the following messages from UART
::::
::::{only} SOC_AM62DX
- If SBL NULL is flashed on the board by following steps in [Flash SOC Initialization Binary](am62dx_evm_setup.md), wait for the following messages from UART
::::

       Starting NULL Bootloader ...

       SYSFW Firmware Version 10.0.7--v10.00.07 (Fiery Fox)
       SYSFW Firmware revision 0xa
       SYSFW ABI revision 4.0

       INFO: Bootloader_runCpu:176: CPU mcu-r5f is initialized to 800000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a530-0 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a530-1 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a531-0 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU a531-1 is initialized to 1400000000 Hz !!!
       INFO: Bootloader_runCpu:176: CPU c7x0-0 is initialized to 1000000000 Hz !!!
       INFO: Bootloader_loadSelfCpu:229: CPU r5f0-0 is initialized to 800000000 Hz !!!
       INFO: Bootloader_JumpSelfCpu:248: All done, jumping self ...

::::{only} SOC_AM62AX
- If initialization is done by following steps in [SOC Initialization Using SPL](am62ax_evm_setup.md), wait for the Linux to be up on the A53 core.

   ```{figure} ../images/am62dx/linux_boot_01.png
   :align: center

   **Linux terminal**
   ```
::::

::::


::::{only} SOC_AM62PX or SOC_AM62LX or SOC_J722S
- Connect the target CPU of interest if not already connected. For the "hello world" example this is `MAIN_Cortex_R5_0_0`

   ```{figure} ../images/am62dx/ccs_load_run_00.png
   :align: center

   **Connect CPU**
   ```

::::


::::{only} SOC_AM263X
- This should initialize the device and initialize R5 to be able to connect

<!-- IMAGE NOT FOUND: ccs_gel_output_1.PNG -->

<!-- IMAGE NOT FOUND: ccs_gel_output_2.PNG -->
::::


::::{only} SOC_AM62X
- Connect the target CPU of interest if not already connected
  - For the "hello world" example this is `BLAZAR_Cortex_M4F_1`

     ```{figure} ../images/am62dx/ccs_load_run_00.png
     :align: center

     **Connect CPU**
     ```
  - For the "hello world" example this is `A53SS0_0`

     ```{figure} ../images/am62x/ccs_load_run_a53.png
     :align: center

     **Connect A53 CPU**
     ```

::::


::::{only} SOC_AM62AX or SOC_AM62DX
- Connect the target CPU of interest if not already connected. For the "hello world" example this is `MCU_R5FSS0_0`

   ```{figure} ../images/am62dx/ccs_load_run_00.png
   :align: center

   **Connect CPU**
   ```

::::


- Reset the CPU

```{figure} ../images/am62dx/ccs_load_run_01.png
:align: center

**Reset CPU**
```
- Load program on the CPU

```{figure} ../images/ccs_load_and_run/ccs_load_run_02.png
:align: center

**Load Program**
```
- **When using makefiles to build**,
  - In the "Load Program" dialog, select "Browse" and select the program from `examples/{example folder}/{board}/{cpu}_{os}/{compiler}` as shown below for the "hello world" program.

   ```{figure} ../images/am62dx/ccs_load_run_03.png
   :align: center

   **Select Program for Makefile Build**
   ```


::::{only} SOC_AM62X
- For the A53 "Hello World" program

   ```{figure} ../images/am62x/ccs_load_run_a53_01.png
   :align: center

   **Select Program for Makefile Build**
   ```

::::


- **When using CCS projects**,
  - In the "Load Program" dialog, select "Browse Project",
    - select the project and then select the program as shown below,

   ```{figure} ../images/ccs_load_and_run/ccs_load_run_04.png
   :align: center

   **Select Program for CCS Projects Build**
   ```

   ```{figure} ../images/am62dx/ccs_load_run_05.png
   :align: center

   **Select the Program from CCS Project**
   ```


::::{only} SOC_AM62X
- For A53 program as shown below,

   ```{figure} ../images/am62x/ccs_load_run_a53_02.png
   :align: center

   **Select the Program from CCS Project**
   ```

::::


- After the program is loaded, you will see the program is halted at "main" as shown below

```{figure} ../images/am62dx/ccs_load_run_06.png
:align: center

**Program at main()**
```

::::{only} SOC_AM62X
- For A53

   ```{figure} ../images/am62x/ccs_load_run_a53_03.png
   :align: center

   **Program at main()**
   ```

::::


- Depending on the example you are running, you may need to load more programs on other CPUs
  for the example to work as expected. Typically, this is needed for multi-core interprocessor
  communication (IPC) examples. For the "hello world" program shown above, no more programs need to be loaded.

- Select "Continue" to run the program and debug using the various CCS debug options

```{figure} ../images/ccs_load_and_run/ccs_load_run_07.png
:align: center

**Run the Program**
```
- The program output will be seen on CCS console, and/or UART terminal, if enabled.
  Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

```{figure} ../images/am62dx/ccs_load_run_08.png
:align: center

**Run the Program**
```

::::{only} SOC_AM62X
- For a53 example the sample output on UART Console (/dev/ttyUSB0) is  Hello World!
::::


::::{only} SOC_AM273X

   :::{admonition} Note
   When loading the examples on R5 core using the XDS560 or XDS200 CCS Hangs. Use below workaround
   :::


- After connecting to the R5 Core

- Open the Expression Window and enter as below

        symbol_loader=1

- Now load the example as shown above

- This is a known issue in CCS. Refer the below link for details https://sir.ext.ti.com/jira/browse/EXT_EP-10638

::::

## Re-load and run example binaries

- Here simply repeat the steps shows in [Load and run example binaries](ccs_launch.md)

- It is especially important to "reset the CPU" before reloading the program.

- In most cases, you don't need to power-cycle the EVM to reload the program or load a new program.

- In some cases, depending on whether the previous program execution was successful or not, the
  CPU or some SOC peripheral may be in a exception or hang state.
  In this case program reload may not work.
  - **SOLUTION**: Power cycle the EVM and repeat all steps shown on this page.
