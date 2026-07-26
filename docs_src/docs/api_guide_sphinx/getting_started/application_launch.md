# Application Run and debugging using CCS


```{note}
The steps on this page should be done each time EVM is power cycled or when a new CCS session is started.
```

## Prerequisites 

A quick recap of the steps that need to have been done before you proceed
- Make sure you have installed CCS as mentioned in [CCS_SETUP_PAGE](#ccs_setup_page)
- Make sure the UART port used for console is identified as mentioned in [CCS_UART_TERMINAL](#ccs_uart_terminal)
- Make sure you have the EVM power cable, JTAG cable, UART cable connected as shown in [EVM_CABLES](#evm_cables)
- Make sure the UART or CCS console logs on doing **EVM POWER-ON** indicate that SOC initialization is successful
- Make sure you have built the example of interest as mentioned in [GETTING_STARTED_BUILD](#getting_started_build)

## Send Application using USB-DFU 
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
- You will see the application being executed after this step. Each application will have TF-A logs and PSCI/SCMI version logs as shown below. This is because the application is running with TF-A and SCMI/PSCI init is done in the generated files for all examples.
\code
NOTICE:  bl1_plat_arch_setup arch setup
NOTICE:  Booting Trusted Firmware
NOTICE:  BL1: v2.12.0(release):11.00.13
NOTICE:  BL1: Built : 15:18:31, May 27 2025
NOTICE:  BL1: dram_class: 11
NOTICE:  lpddr4: post start - PI training status=0x27c0a000
NOTICE:  bl1_platform_setup DDR init done
NOTICE:  k3_bl1_handoff ENTERING WFI - end of bl1
NOTICE:  BL31: v2.12.0(release):11.00.13
NOTICE:  BL31: Built : 15:18:32, May 27 2025
NOTICE:  0_ADC0's parent is 0
NOTICE:  0_ADC0's parent (after set_parent) is 2
PSCI Major version 1
PSCI Minor version 1
SCMI: Base protocol version 20000
SCMI: Power Domain: Protocol version 21000
SCMI: Clock: Protocol version 30000
Hello World! from a53_core0
\endcode

## Using CCS for debugging 

Follow the below steps to debug an example application using CCS.
- Start Project-less Debug with the target configuration created with [CCS_NEW_TARGET_CONFIG](#ccs_new_target_config)

    \imageStyle{ccs_launch_00.png,width:30%}
    \image html ccs_launch_00.png "Start Project-less Debug"

- You will see the {{ VAR_SOC_NAME }} target configuration in the "Threads" tab of "Debug" window as shown below

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

- Here simply repeat the steps shows in [USB](#usb)-DFU_SEND

- You will need to power-cycle the EVM to reload the application or load a new application example.