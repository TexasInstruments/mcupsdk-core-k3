#  Application Run and debugging using CCS {#CCS_LAUNCH_PAGE}

[TOC]

\note The steps on this page should be done each time EVM is power cycled or when a
      new CCS session is started.

## Prerequisites {#PREREQUISITES}

A quick recap of the steps that need to have been done before you proceed
- Make sure you have installed CCS as mentioned in \ref CCS_SETUP_PAGE
- Make sure the UART port used for console is identified as mentioned in \ref CCS_UART_TERMINAL
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in \ref EVM_CABLES
- Make sure the UART or CCS console logs on doing **EVM POWER-ON** indicate that SOC initialization is successful
- Make sure you have built the example of interest as mentioned in \ref GETTING_STARTED_BUILD

## Send Application using USB-DFU {#USB-DFU_SEND}
- Setup the EVM in USB-DFU bootmode.
- **POWER-ON** the EVM.
- Send the prebuilt binary "tiboot3.bin" present at `${MCU_PLUS_SDK_PATH}/tools/boot/sbl_prebuilt/am62lx-evm/` as follows:
\code
sudo dfu-util -R -a bootloader -D tools/boot/sbl_prebuilt/am62lx-evm/tiboot3.bin
\endcode
- You will see pre-BL logs on the UART console after this.
- Send the application binary, say, `hello_world.release.appimage.hs_fs`  after the first binary is sent:
\code
sudo dfu-util -R -a bootloader -D examples/hello_world/am62lx-evm/a53ss0-0_freertos/gcc-aarch64/hello_world.release.appimage.hs_fs
\endcode
- You will see the application being executed after this step.

    \imageStyle{application_run.png,width:30%}
    \image html application_run.png "Application logs"

## Using CCS for debugging {#CCS_LAUNCH}

Follow the below steps to debug an example application using CCS.
- Start Project-less Debug with the target configuration created with \ref CCS_NEW_TARGET_CONFIG

    \imageStyle{ccs_launch_00.png,width:30%}
    \image html ccs_launch_00.png "Start Project-less Debug"

- You will see the @VAR_SOC_NAME target configuration in the "Threads" tab of "Debug" window as shown below

    \imageStyle{ccs_launch_01.png,width:30%}
    \image html ccs_launch_01.png "Target Configuration After Launch"

- Connect the target CPU of interest if not already connected. For the "hello world" example this is `CortexA53_0`

    \imageStyle{ccs_load_run_00.png,width:30%}
    \image html ccs_load_run_00.png "Connect CPU"

- Load the symbols of the application .out file as desired for debugging.

    \imageStyle{ccs_load_run_10.png,width:50%}
    \image html ccs_load_run_10.png "Load Symbols"

- In the "Load Symbols" dialog, select "Browse" and select the program from `examples/{example folder}/{board}/{cpu}_{os}/{compiler}` as shown below for the "hello world" program.

    \imageStyle{ccs_load_run_03.png,width:50%}
    \image html ccs_load_run_03.png "Select File for loading symbols"

- After this step, you can see the symbols being loaded through the debugger and the entire call stack.

    \imageStyle{ccs_load_run_12.png,width:80%}
    \image html ccs_load_run_12.png "Debugging the application"

## Re-load and run example binaries

- Here simply repeat the steps shows in \ref USB-DFU_SEND

- You will need to power-cycle the EVM to reload the application or load a new application example.