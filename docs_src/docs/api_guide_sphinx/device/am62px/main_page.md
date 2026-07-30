# Introduction
Welcome to **{{ VAR_SDK_NAME }} for {{ VAR_SOC_NAME }}**. This SDK contains examples, libraries and tools to develop **RTOS and no-RTOS** based applications for **ARM R5F** and related peripherals.

## Getting Started

To get started, see [Getting Started](../../getting_started/getting_started_am62px.md)

## Block Diagram

Given below is a block diagram of the SW modules in this SDK,
![Software Block Diagram](../../images/am62px/block_diagram_am62px.png)


The main software components in the block diagram are described below


| Software Components                                   | Documentation Page                                                                                    | Description                                                                                                                                           |
|-------------------------------------------------------|-------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| **OS Kernel**                                         |                                                                                                       |                                                                                                                                                       |
| No RTOS                                               | <a href="../../components/kernel/os/nortos.html">NO RTOS</a>                                          | Contains modules which implement no-RTOS execution environment consisting of timers, ISR, main thread. Allows software on top to run in bare metal mode. |
| FreeRTOS Kernel                                       | <a href="../../components/kernel/os/freertos.html">FreeRTOS</a>                                       | FreeRTOS Kernel, provides a execution environment consisting of tasks, semaphores, timers, see https://www.freertos.org/RTOS.html                      |
| FreeRTOS POSIX                                        | <a href="../../components/kernel/os/freertos.html">FreeRTOS</a>                                       | Limited POSIX APIs with FreeRTOS underneath, provides pthreads, mqueue, semaphore, see https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_POSIX/index.html |
| Driver Porting Layer (DPL)                            | <a href="../../components/kernel/dpl/dpl.html">Driver Porting Layer (DPL)</a>                         | APIs used by drivers to abstract the OS environment. Example, Semaphore, HW interrupts, mutex, clock.                                                 |
| **Device Drivers and HAL (Hardware Abstraction Layer)** |                                                                                                     |                                                                                                                                                       |
| SOC Peripheral Drivers                                | <a href="../../components/drivers/drivers.html">SOC Peripheral Drivers</a>                            | Device Drivers library and APIs for peripherals within the SOC. Example, I2C, GPIO, UART.                                                             |
| Board Peripheral Drivers                              | <a href="../../components/board/board.html">Board Peripheral Drivers</a>                              | Device Drivers library and APIs for peripherals on the board or EVM. Example, Flash.                                                                  |
| **Software Diagnostics Library**                      |                                                                                                       |                                                                                                                                                       |
| **Safety Checkers Library**                           |                                                                                                       |                                                                                                                                                       |
| Safety Checkers                                       | <a href="../../components/safety_checkers/safety_checkers.html">Safety Checkers Library</a>           | Safety Checkers Library                                                                                                                               |
| **Examples**                                          |                                                                                                       |                                                                                                                                                       |
| Examples                                              | <a href="../../examples/examples.html">Examples and Demos</a>                                         | Examples showing usage of different SW libraries and APIs                                                                                             |
| **Tools (used on host machine)**                      |                                                                                                       |                                                                                                                                                       |
| Code Composer Studio (CCS)                            | <a href="../../developer_guides/ccs_projects.html">Using SDK with CCS Projects</a>                    | IDE used to build projects, debug programs.                                                                                                           |
| TI CLANG Compiler Toolchain                           | [**TI CLANG CGT Homepage**](https://www.ti.com/tool/download/ARM-CGT-CLANG-1)                        | CLANG based ARM compiler from TI for ARM R5F and MCU-R5F                                                                                             |
| GCC AARCH64 Compiler                                  | [**GCC AARCH64 Homepage**](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads)                | AARCH64 compiler for Linux A53 builds and HSM appimage generation                                                                                     |
| SysConfig                                             | <a href="../../developer_guides/syscfg_intro.html">Using SDK with SysConfig</a>                       | System configuration tool, used to configure peripherals, pinmux, clocks and generate system initialization code                                      |
| TI Resource Explorer (TIREX)                          | <a href="../../developer_guides/tirex_intro.html">Using SDK with TI Resource Explorer</a>             | Web browser based tool to explore the SDK, select, import and run the examples                                                                        |
| SDK Tools and Utilities                               | <a href="../../components/tools/tools.html">Tools and Utilities</a>                                   | Additional tools and utilities, like flashing tools, booting tools, CCS loading scripts used with the SDK development flow                           |

## Directory Structure

Given below is a overview of the directory structure to help you navigate the SDK and related tools.

| Folder/Files                          | Description                                                                                          |
|---------------------------------------|------------------------------------------------------------------------------------------------------|
| **${SDK_INSTALL_PATH}/**              |                                                                                                      |
| README_FIRST_AM62PX.html              | Open this file in a web browser to reach this user guide                                             |
| makefile                              | Top level makefile to build the whole SDK using "make"                                               |
| imports.mak                           | Top level makefile to list paths to dependent tools                                                  |
| docs/                                 | Offline browseable HTML documentation                                                                |
| examples/                             | Example applications for AM62PX, across multiple boards, CPUs, NO-RTOS, RTOS                        |
| source/                               | Device drivers, middleware libraries and APIs                                                        |
| tools/                                | Tools and utilities like CCS loading scripts, initialization scripts.                                |
| **${SDK_INSTALL_PATH}/source/**       |                                                                                                      |
| board/                                | Board peripheral device drivers                                                                      |
| drivers/                              | Soc peripheral device drivers                                                                        |
| kernel/                               | NO RTOS and RTOS kernel and Driver Porting layer (DPL) for these environments.                       |
| **${SDK_INSTALL_PATH}/examples/**     |                                                                                                      |
| drivers/                              | SOC and board level focused device drivers examples. The examples are based on both NO-RTOS and RTOS |
| empty/                                | Template projects to copy to your workarea and then modify based on your custom application needs    |
| kernel/                               | NO RTOS and RTOS kernel focused examples                                                             |
| **${SDK_INSTALL_PATH}/tools/**        |                                                                                                      |
| /                                     | Additional tools and utilities used by the SDK                                                       |

Given below are the paths where the different tools needed outside the SDK, like CCS, SysConfig are installed by default in Windows.
In Linux, the tools are installed by default in ${HOME}/ti.

| Folder/Files                                        | Description                                                                                                       |
|-----------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|
| C:/ti/ccs{{ VAR_CCS_FOLDER_VERSION }}               | Code Composer Studio                                                                                              |
| C:/ti/sysconfig_{{ VAR_SYSCFG_VERSION }}            | SysConfig. **NOTE**, SysConfig is also installed as part of CCS at ${CCS_INSTALL_PATH}/ccs/utils/sysconfig_x.x.x |
| C:/ti/ti-cgt-armllvm_{{ VAR_TI_ARM_CLANG_VERSION }} | TI ARM CLANG compiler tool chain                                                                                  |
| C:/ti/gcc-arm-{{ VAR_GCC_AARCH64_VERSION }}         | GCC AARCH64 compiler                                                                                              |

## Licenses

The licensing information of this SDK, as well as any third-party components included which are made available under a number of other open-source licenses are enumerated as part of the manifest.
A complete manifest along with export control information is detailed here <a href="../../../mcu_plus_sdk_am62px_manifest.html">LINK</a>

## Help and Support

For additional help and support, see https://e2e.ti.com/support/processors/f/processors-forum

