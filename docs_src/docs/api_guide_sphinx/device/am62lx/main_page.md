# Introduction

:::{attention}
FreeRTOS SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the FreeRTOS SDK product. If these features need to be productized, TI can recommend third parties who can help.
:::

Welcome to **{{ VAR_SDK_NAME }} for {{ VAR_SOC_NAME }}**. This SDK contains examples, libraries and tools to develop **RTOS and no-RTOS** based applications for **ARM A53** and related peripherals.

## Getting Started

To get started, see [Getting Started](../../getting_started/getting_started.md)

## Block Diagram

Given below is a block diagram of the SW modules in this SDK,

![Software Block Diagram](../../images/am62lx/block_diagram_am62lx.png)

The main software components in the block diagram are described below

```{raw} html

<table class="docutils align-default">
<colgroup>
<col style="width: 25%;" />
<col style="width: 38%;" />
<col style="width: 37%;" />
</colgroup>
<thead>
<tr class="row-odd"><th class="head"><p>Software Components</p></th>
<th class="head"><p>Documentation Page</p></th>
<th class="head"><p>Description</p></th>
</tr>
</thead>
<tbody>
<tr class="row-even"><td colspan="3" style="background-color: #F0F0F0;"><p><b>OS Kernel</b></p></td></tr>
<tr class="row-odd"><td><p>No RTOS</p></td>
<td><p><a href="../../components/kernel/os/nortos.html">NO RTOS</a></p></td>
<td><p>Contains modules which implement no-RTOS execution environment consisting of timers, ISR, main thread. Allows software on top to run in bare metal mode.</p></td>
</tr>
<tr class="row-even"><td><p>FreeRTOS Kernel</p></td>
<td><p><a href="../../components/kernel/os/freertos.html">FreeRTOS</a></p></td>
<td><p>FreeRTOS Kernel, provides a execution environment consisting of tasks, semaphores, timers, see <a href="https://www.freertos.org/RTOS.html">https://www.freertos.org/RTOS.html</a></p></td>
</tr>
<tr class="row-odd"><td><p>FreeRTOS POSIX</p></td>
<td><p><a href="../../components/kernel/os/freertos.html">FreeRTOS</a></p></td>
<td><p>Limited POSIX APIs with FreeRTOS underneath, provides pthreads, mqueue, semaphore, see <a href="https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_POSIX/index.html">https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_POSIX/index.html</a></p></td>
</tr>
<tr class="row-even"><td><p>Driver Porting Layer (DPL)</p></td>
<td><p><a href="../../components/kernel/dpl/dpl.html">Driver Porting Layer (DPL)</a></p></td>
<td><p>APIs used by drivers to abstract the OS environment. Example, Semaphore, HW interrupts, mutex, clock.</p></td>
</tr>
<tr class="row-odd"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Device Drivers and HAL (Hardware Abstraction Layer)</b></p></td></tr>
<tr class="row-even"><td><p>SOC Peripheral Drivers</p></td>
<td><p><a href="../../components/drivers/drivers.html">SOC Peripheral Drivers</a></p></td>
<td><p>Device Drivers library and APIs for peripherals within the SOC. Example, I2C, GPIO, UART.</p></td>
</tr>
<tr class="row-odd"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Examples</b></p></td></tr>
<tr class="row-even"><td><p>Examples</p></td>
<td><p><a href="../../examples/examples.html">Examples and Demos</a></p></td>
<td><p>Examples showing usage of different SW libraries and APIs</p></td>
</tr>
<tr class="row-odd"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Tools (used on host machine)</b></p></td></tr>
<tr class="row-even"><td><p>Code Composer Studio (CCS)</p></td>
<td><p><a href="../../developer_guides/ccs_projects.html">Using SDK with CCS Projects</a></p></td>
<td><p>IDE used to build projects, debug programs.</p></td>
</tr>
<tr class="row-odd"><td><p>TI CLANG Compiler Toolchain</p></td>
<td><p><a href="https://www.ti.com/tool/download/ARM-CGT-CLANG-1"><b>TI CLANG CGT Homepage</b></a></p></td>
<td><p>CLANG based ARM compiler from TI for ARM R5F and MCU-R5F</p></td>
</tr>
<tr class="row-even"><td><p>SysConfig</p></td>
<td><p><a href="../../developer_guides/syscfg_intro.html">Using SDK with SysConfig</a></p></td>
<td><p>System configuration tool, used to configure peripherals, pinmux, clocks and generate system initialization code</p></td>
</tr>
<tr class="row-odd"><td><p>TI Resource Explorer (TIREX)</p></td>
<td><p><a href="../../developer_guides/tirex_intro.html">Using SDK with TI Resource Explorer</a></p></td>
<td><p>Web browser based tool to explore the SDK, select, import and run the examples</p></td>
</tr>
</tbody>
</table>

```

## Directory Structure

Given below is a overview of the directory structure to help you navigate the SDK and related tools.

| Folder/Files                          | Description                                                                                          |
|---------------------------------------|------------------------------------------------------------------------------------------------------|
| **${SDK_INSTALL_PATH}/**              |                                                                                                       |
| README_FIRST_AM62LX.html              | Open this file in a web browser to reach this user guide                                             |
| makefile                              | Top level makefile to build the whole SDK using "make"                                               |
| imports.mak                           | Top level makefile to list paths to dependent tools                                                  |
| docs/                                 | Offline browseable HTML documentation                                                                |
| examples/                             | Example applications for AM62LX, across multiple boards, CPUs, NO-RTOS, RTOS                         |
| source/                               | Device drivers, middleware libraries and APIs                                                        |
| tools/                                | Tools and utilities like CCS loading scripts, initialization scripts.                                |
| **${SDK_INSTALL_PATH}/source/**       |                                                                                                        |
| board/                                | Board peripheral device drivers                                                                      |
| drivers/                              | Soc peripheral device drivers                                                                        |
| kernel/                               | NO RTOS and RTOS kernel and Driver Porting layer (DPL) for these environments.                       |
| **${SDK_INSTALL_PATH}/examples/**     |                                                                                                        |
| drivers/                              | SOC and board level focused device drivers examples. The examples are based on both NO-RTOS and RTOS |
| empty/                                | Template projects to copy to your workarea and then modify based on your custom application needs    |
| kernel/                               | NO RTOS and RTOS kernel focused examples                                                              |
| **${SDK_INSTALL_PATH}/tools/**        |                                                                                                        |
| /                                     | Additional tools and utilities used by the SDK                                                       |

Given below are the paths where the different tools needed outside the SDK, like CCS, SysConfig are installed by default in Windows.
In Linux, the tools are installed by default in ${HOME}/ti.

| Folder/Files                                        | Description                                                                                                       |
|-----------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|
| C:/ti/ccs{{ VAR_CCS_FOLDER_VERSION }}               | Code Composer Studio                                                                                               |
| C:/ti/sysconfig_{{ VAR_SYSCFG_VERSION }}            | SysConfig. **NOTE**, SysConfig is also installed as part of CCS at ${CCS_INSTALL_PATH}/ccs/utils/sysconfig_x.x.x  |
| C:/ti/gcc-arm-{{ VAR_GCC_AARCH64_VERSION }}         | GCC AARCH64 compiler                                                                                               |

## Licenses

The licensing information of this SDK, as well as any third-party components included which are made available under a number of other open-source licenses are enumerated as part of the manifest.
A complete manifest along with export control information is detailed here <a href="../../../freertos_sdk_am62lx_manifest.html">LINK</a>

## Help and Support

For additional help and support, see https://e2e.ti.com/support/processors/f/processors-forum

## Documentation Credits

This user guide is generated using doxygen, v1.8.20. See https://www.doxygen.nl/index.html
