# Introduction

:::{attention}
MCU+SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the MCU+SDK product. If these features need to be productized, TI can recommend third parties who can help.
:::

Welcome to **{{ VAR_SDK_NAME }} for {{ VAR_SOC_NAME }}**. This SDK contains examples, libraries and tools to develop **RTOS and no-RTOS** based applications for **ARM M4F, ARM R5F, ARM A53** and related peripherals.

This SDK also contains examples to interface these ARM M4F applications with Processor SDK Linux based Cortex-A applications.

## Getting Started

To get started, see [Getting Started](../../getting_started/getting_started.md)

## Block Diagram

Given below is a block diagram of the SW modules in this SDK,
![Software Block Diagram](../../images/am62x/block_diagram_am62x.png)


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
<tr class="row-odd"><td><p>Board Peripheral Drivers</p></td>
<td><p><a href="../../components/board/board.html">Board Peripheral Drivers</a></p></td>
<td><p>Device Drivers library and APIs for peripherals on the board or EVM. Example, Flash.</p></td>
</tr>
<tr class="row-even"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Software Diagnostics Library</b></p></td></tr>
<tr class="row-odd"><td><p>SDL</p></td>
<td><p><a href="../../components/sdl/sdl.html">Software Diagnostics Library</a></p></td>
<td><p>Software Diagnostics Library</p></td>
</tr>
<tr class="row-even"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Safety Checkers Library</b></p></td></tr>
<tr class="row-odd"><td><p>Safety Checkers</p></td>
<td><p><a href="../../components/safety_checkers/safety_checkers.html">Safety Checkers Library</a></p></td>
<td><p>Safety Checkers Library</p></td>
</tr>
<tr class="row-even"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Examples</b></p></td></tr>
<tr class="row-odd"><td><p>Examples</p></td>
<td><p><a href="../../examples/examples.html">Examples and Demos</a></p></td>
<td><p>Examples showing usage of different SW libraries and APIs</p></td>
</tr>
<tr class="row-even"><td colspan="3" style="background-color: #F0F0F0;"><p><b>Tools (used on host machine)</b></p></td></tr>
<tr class="row-odd"><td><p>Code Composer Studio (CCS)</p></td>
<td><p><a href="../../developer_guides/ccs_projects.html">Using SDK with CCS Projects</a></p></td>
<td><p>IDE used to build projects, debug programs.</p></td>
</tr>
<tr class="row-even"><td><p>TI CLANG Compiler Toolchain</p></td>
<td><p><a href="https://www.ti.com/tool/download/ARM-CGT-CLANG-1"><b>TI CLANG CGT Homepage</b></a></p></td>
<td><p>CLANG based ARM compiler from TI for ARM R5F</p></td>
</tr>
<tr class="row-odd"><td><p>SysConfig</p></td>
<td><p><a href="../../developer_guides/syscfg_intro.html">Using SDK with SysConfig</a></p></td>
<td><p>System configuration tool, used to configure peripherals, pinmux, clocks and generate system initialization code</p></td>
</tr>
<tr class="row-even"><td><p>TI Resource Explorer (TIREX)</p></td>
<td><p><a href="../../developer_guides/tirex_intro.html">Using SDK with TI Resource Explorer</a></p></td>
<td><p>Web browser based tool to explore the SDK, select, import and run the examples</p></td>
</tr>
<tr class="row-odd"><td><p>SDK Tools and Utilities</p></td>
<td><p><a href="../../components/tools/tools.html">Tools and Utilities</a></p></td>
<td><p>Additional tools and utilities, like flashing tools, booting tools, CCS loading scripts used with the SDK development flow</p></td>
</tr>
</tbody>
</table>

```

## Directory Structure

Given below is a overview of the directory structure to help you navigate the SDK and related tools.

```{raw} html

<table class="docutils align-default">
<colgroup>
<col style="width: 25%;" />
<col style="width: 75%;" />
</colgroup>
<thead>
<tr class="row-odd"><th class="head"><p>Folder/Files</p></th>
<th class="head"><p>Description</p></th>
</tr>
</thead>
<tbody>
<tr class="row-even"><td colspan="2" style="background-color: #F0F0F0;"><p>${SDK_INSTALL_PATH}/</p></td></tr>
<tr class="row-odd"><td><p>README_FIRST_AM62X.html</p></td>
<td><p>Open this file in a web browser to reach this user guide</p></td>
</tr>
<tr class="row-even"><td><p>makefile</p></td>
<td><p>Top level makefile to build the whole SDK using "make"</p></td>
</tr>
<tr class="row-odd"><td><p>imports.mak</p></td>
<td><p>Top level makefile to list paths to dependent tools</p></td>
</tr>
<tr class="row-even"><td><p>docs/</p></td>
<td><p>Offline browseable HTML documentation</p></td>
</tr>
<tr class="row-odd"><td><p>examples/</p></td>
<td><p>Example applications for AM62X, across multiple boards, CPUs, NO-RTOS, RTOS</p></td>
</tr>
<tr class="row-even"><td><p>source/</p></td>
<td><p>Device drivers, middleware libraries and APIs</p></td>
</tr>
<tr class="row-odd"><td><p>tools/</p></td>
<td><p>Tools and utilities like CCS loading scripts, initialization scripts.</p></td>
</tr>
<tr class="row-even"><td colspan="2" style="background-color: #F0F0F0;"><p>${SDK_INSTALL_PATH}/source/</p></td></tr>
<tr class="row-odd"><td><p>board/</p></td>
<td><p>Board peripheral device drivers</p></td>
</tr>
<tr class="row-even"><td><p>drivers/</p></td>
<td><p>Soc peripheral device drivers</p></td>
</tr>
<tr class="row-odd"><td><p>kernel/</p></td>
<td><p>NO RTOS and RTOS kernel and Driver Porting layer (DPL) for these environments.</p></td>
</tr>
<tr class="row-even"><td><p>sdl/</p></td>
<td><p>Software Diagnostics Library</p></td>
</tr>
<tr class="row-odd"><td colspan="2" style="background-color: #F0F0F0;"><p>${SDK_INSTALL_PATH}/examples/</p></td></tr>
<tr class="row-even"><td><p>drivers/</p></td>
<td><p>SOC and board level focused device drivers examples. The examples are based on both NO-RTOS and RTOS</p></td>
</tr>
<tr class="row-odd"><td><p>empty/</p></td>
<td><p>Template projects to copy to your workarea and then modify based on your custom application needs</p></td>
</tr>
<tr class="row-even"><td><p>kernel/</p></td>
<td><p>NO RTOS and RTOS kernel focused examples</p></td>
</tr>
<tr class="row-odd"><td><p>sdl/</p></td>
<td><p>SDL focused examples</p></td>
</tr>
<tr class="row-even"><td><p>security/</p></td>
<td><p>Security focused examples</p></td>
</tr>
<tr class="row-odd"><td colspan="2" style="background-color: #F0F0F0;"><p>${SDK_INSTALL_PATH}/tools/</p></td></tr>
<tr class="row-even"><td><p>/</p></td>
<td><p>Additional tools and utilities used by the SDK</p></td>
</tr>
</tbody>
</table>

```

Given below are the paths where the different tools needed outside the SDK, like CCS, SysConfig are installed by default in Windows.
In Linux, the tools are installed by default in ${HOME}/ti.

| Folder/Files | Description |
|---|---|
| C:/ti/ccs{{ VAR_CCS_FOLDER_VERSION }} | Code Composer Studio |
| C:/ti/sysconfig_{{ VAR_SYSCFG_VERSION }} | SysConfig. **NOTE**, SysConfig is also installed as part of CCS at ${CCS_INSTALL_PATH}/ccs/utils/sysconfig_x.x.x |
| C:/ti/ti-cgt-armllvm_{{ VAR_TI_ARM_CLANG_VERSION }} | TI ARM CLANG compiler tool chain |
| C:/ti/gcc-arm-{{ VAR_GCC_AARCH64_VERSION }} | GCC AARCH64 compiler |

## Licenses

The licensing information of this SDK, as well as any third-party components included which are made available under a number of other open-source licenses are enumerated as part of the manifest.
A complete manifest along with export control information is detailed here <a href="../../../freertos_sdk_am62x_manifest.html">LINK</a>

## Help and Support

For additional help and support, see https://e2e.ti.com/support/processors/f/processors-forum
