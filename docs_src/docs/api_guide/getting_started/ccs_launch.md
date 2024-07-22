#  CCS Launch, Load and Run {#CCS_LAUNCH_PAGE}

[TOC]

\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL. This section is only applicable for MCU M4F Core and A53 Core.
\endcond

\cond SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL. This section is only applicable for MCU R5F Core.
\endcond

\note The steps on this page should be done each time EVM is power cycled or when a
      new CCS session is started.

## Prerequisites {#PREREQUISITES}

A quick recap of the steps that need to have been done before you proceed
- Make sure you have installed CCS as mentioned in \ref CCS_SETUP_PAGE
- Make sure the UART port used for console is identified as mentioned in \ref CCS_UART_TERMINAL
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in \ref EVM_CABLES
\cond SOC_AM273X
- Make sure you have done the steps for a SOC initialization method using \ref EVM_SOC_INIT
\endcond
\cond SOC_AM263X
- Make sure to follow below steps while running multi core applications.
  - Edit the CCS gel file at "{CCS_Installation_directory}\ccs1200\ccs\ccs_base\emulation\gel\AM263x\am263x.gel"
      \imageStyle{am263x_dualcore_gel_edit_path.PNG,width:50%}
      \image html am263x_dualcore_gel_edit_path.PNG "Gel file path"

  - Modify Line 113 from "mode = AM263x_Check_supported_mode();" to "mode = 1;"
      \imageStyle{am263x_dualcore_gel_update.png,width:50%}
      \image html am263x_dualcore_gel_update.png "Gel file update"

  - With this change, CCS always configures the device in "Dual Core Mode" and all four R5 cores can be used.
  - To revert to Lockstep Mode, undo this change.
\endcond
\cond SOC_AWR294X || SOC_AM263X || SOC_AM243X || SOC_AM64X
- Make sure you have done the steps for a SOC initialization method
  - **RECOMMENDED** method is \ref EVM_FLASH_SOC_INIT
  - Other options, if recommended method cannot be used, are mentioned in \ref EVM_SOC_INIT
- Make sure EVM boot mode switch is setup correctly based on the SOC initialization method
\endcond
\cond SOC_AWR294X || SOC_AM263X
  - For the **RECOMMENDED** method, \ref EVM_FLASH_SOC_INIT, the boot mode should be \ref BOOTMODE_QSPI
\endcond
\cond SOC_AM243X || SOC_AM64X
  - For the **RECOMMENDED** method, \ref EVM_FLASH_SOC_INIT, the boot mode should be \ref BOOTMODE_OSPI
\endcond
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
- Make sure you have done the steps for a SOC initialization method as per \ref EVM_FLASH_SOC_INIT
\endcond
- Make sure the UART or CCS console logs on doing **EVM POWER-ON** indicate that SOC initialization is successful
- Make sure you have built the example of interest as mentioned in \ref GETTING_STARTED_BUILD

## Launch CCS {#CCS_LAUNCH}

- Launch the target configuration created with \ref CCS_NEW_TARGET_CONFIG

    \imageStyle{ccs_launch_00.png,width:30%}
    \image html ccs_launch_00.png "Launch Target Configuration"

- You will see the @VAR_SOC_NAME target configuration in the "Debug" window as shown below

    \imageStyle{ccs_launch_01.png,width:40%}
    \image html ccs_launch_01.png "Target Configuration After Launch"


## Load and run example binaries {#CCS_LOAD_RUN}

- **POWER-ON** the EVM

\cond SOC_AM243X || SOC_AM64X
- If you dont see the expected SOC initialization logs on UART or CCS console, then recheck your \ref EVM_SETUP_PAGE
\endcond

\cond SOC_AM62X
- If SBL NULL is flashed on the board by following steps in \ref EVM_FLASH_SOC_INIT, wait for the following messages from UART

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

- If initialization is done by following steps in \ref EVM_SOC_INIT_SPL, wait for the Linux to be up on the A53 core.
    \imageStyle{linux_boot_01.png,width:60%}
    \image html linux_boot_01.png "Linux terminal"
\endcond

\cond SOC_AM62AX || SOC_AM62DX
- If SBL NULL is flashed on the board by following steps in \ref EVM_FLASH_SOC_INIT, wait for the following messages from UART

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
\cond SOC_AM62AX
- If initialization is done by following steps in \ref EVM_SOC_INIT_SPL, wait for the Linux to be up on the A53 core.
    \imageStyle{linux_boot_01.png,width:60%}
    \image html linux_boot_01.png "Linux terminal"
\endcond
\endcond

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62DX
- Connect the target CPU of interest if not already connected. For the "hello world" example this is `MAIN_Cortex_R5_0_0`

    \imageStyle{ccs_load_run_00.png,width:50%}
    \image html ccs_load_run_00.png "Connect CPU"

\endcond

\cond SOC_AM263X
- This should initialize the device and initialize R5 to be able to connect
    \imageStyle{ccs_gel_output_1.PNG,width:50%}
    \image html ccs_gel_output_1.PNG " "
    \imageStyle{ccs_gel_output_2.PNG,width:50%}
    \image html ccs_gel_output_2.PNG "GEL Output"
\endcond


\cond SOC_AM62X
- Connect the target CPU of interest if not already connected
    - For the "hello world" example this is `BLAZAR_Cortex_M4F_1`

        \imageStyle{ccs_load_run_00.png,width:60%}
        \image html ccs_load_run_00.png "Connect CPU"

    - For the "hello world" example this is `A53SS0_0`

        \imageStyle{ccs_load_run_a53.png,width:60%}
        \image html ccs_load_run_a53.png "Connect A53 CPU"

\endcond

\cond SOC_AM62AX || SOC_AM62DX
- Connect the target CPU of interest if not already connected. For the "hello world" example this is `MCU_R5FSS0_0`

    \imageStyle{ccs_load_run_00.png,width:60%}
    \image html ccs_load_run_00.png "Connect CPU"

\endcond

- Reset the CPU

    \imageStyle{ccs_load_run_01.png,width:50%}
    \image html ccs_load_run_01.png "Reset CPU"

- Load program on the CPU

    \imageStyle{ccs_load_run_02.png,width:50%}
    \image html ccs_load_run_02.png "Load Program"

- **When using makefiles to build**,
  - In the "Load Program" dialog, select "Browse" and select the program from `examples/{example folder}/{board}/{cpu}_{os}/{compiler}` as shown below for the "hello world" program.

    \imageStyle{ccs_load_run_03.png,width:40%}
    \image html ccs_load_run_03.png "Select Program for Makefile Build"

\cond SOC_AM62X
-  For the A53 "Hello World" program

    \imageStyle{ccs_load_run_a53_01.png,width:40%}
    \image html ccs_load_run_a53_01.png "Select Program for Makefile Build"

\endcond

- **When using CCS projects**,
  - In the "Load Program" dialog, select "Browse Project",
    - select the project and then select the program as shown below,

    \imageStyle{ccs_load_run_04.png,width:40%}
    \image html ccs_load_run_04.png "Select Program for CCS Projects Build"

    \imageStyle{ccs_load_run_05.png,width:25%}
    \image html ccs_load_run_05.png "Select the Program from CCS Project"

\cond SOC_AM62X
   - For A53 program as shown below,

    \imageStyle{ccs_load_run_a53_02.png,width:25%}
    \image html ccs_load_run_a53_02.png "Select the Program from CCS Project"

\endcond

- After the program is loaded, you will see the program is halted at "main" as shown below

    \imageStyle{ccs_load_run_06.png,width:40%}
    \image html ccs_load_run_06.png "Program at main()

\cond SOC_AM62X
   - For A53

    \imageStyle{ccs_load_run_a53_03.png,width:40%}
    \image html ccs_load_run_a53_03.png "Program at main()"

\endcond

- Depending on the example you are running, you may need to load more programs on other CPUs
  for the example to work as expected. Typically, this is needed for multi-core interprocessor
  communication (IPC) examples. For the "hello world" program shown above, no more programs need to be loaded.

- Select "Resume" to run the program and debug using the various CCS debug options

    \imageStyle{ccs_load_run_07.png,width:30%}
    \image html ccs_load_run_07.png "Run the Program"

- The program output will be seen on CCS console, and/or UART terminal, if enabled.
  Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

    \imageStyle{ccs_load_run_08.png,width:50%}
    \image html ccs_load_run_08.png "Run the Program"

\cond SOC_AM62X
- For a53 example the sample output on UART Console (/dev/ttyUSB0) is  Hello World!
\endcond

\cond SOC_AM273X

\note When loading the examples on R5 core using the XDS560 or XDS200 CCS Hangs. Use below workaround

 - After connecting to the R5 Core

 - Open the Expression Window and enter as below

        symbol_loader=1

 - Now load the example as shown above

 - This is a known issue in CCS. Refer the below link for details https://sir.ext.ti.com/jira/browse/EXT_EP-10638

\endcond
## Re-load and run example binaries

- Here simply repeat the steps shows in \ref CCS_LOAD_RUN

- It is especially important to "reset the CPU" before reloading the program.

- In most cases, you don't need to power-cycle the EVM to reload the program or load a new program.

- In some cases, depending on whether the previous program execution was successful or not, the
  CPU or some SOC peripheral may be in a exception or hang state.
  In this case program reload may not work.
  - **SOLUTION**: Power cycle the EVM and repeat all steps shown on this page.
