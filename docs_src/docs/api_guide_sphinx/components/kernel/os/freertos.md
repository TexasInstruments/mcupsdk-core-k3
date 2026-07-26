# FreeRTOS

```{toctree}
:maxdepth: 1
:titlesonly:

freertos_important_guidelines
```

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

:::{admonition} Note
A53 will not be available on all SOCs. All references to A53 should be ignored on such SOCs.
:::

::::


## Introduction

FreeRTOS is a market-leading real-time operating system (RTOS) for microcontrollers and small microprocessors. Distributed freely under the MIT open source license, FreeRTOS includes a kernel and a growing set of libraries suitable for use across all industry sectors. FreeRTOS is built with an emphasis on reliability and ease of use.

{{ VAR_SDK_NAME }} supports FreeRTOS on below CPUS

::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X

- ARM M4F

::::

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- ARM R5F

::::

::::{only} SOC_AM64X

- ARM A53 (single core and SMP on both cores)

::::

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X

- TI C75

::::

::::{only} SOC_AM62X or SOC_AM62LX

- ARM A53 (single core and AMP on all cores)

::::

::::{only} SOC_AM62DX

- ARM A53 (single core and SMP on all cores)

::::

## Features Supported
- FreeRTOS Kernel {{ VAR_FREERTOS_KERNEL_VERSION }}
  - Tasks, semaphores, mutex, queues, timers, list, heap, event groups
  - preemptive priority based scheduler
  - static and/or dynamic memory allocation mode

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- FreeRTOS SMP Kernel {{ VAR_FREERTOS_SMP_KERNEL_VERSION }}
  - Tasks, semaphores, mutex, queues, timers, list, heap, event groups
  - preemptive priority based scheduler for multiple cores
  - static and/or dynamic memory allocation mode

::::

- FreeRTOS+POSIX
  - Limited POSIX API wrappers on top of FreeRTOS APIs
  - Clock, message queue, pthread, pthread cond, pthread mutex, semaphore, timer
- In order to keep the device drivers agnostic of FreeRTOS or NORTOS, additionally below [Driver Porting Layer (DPL)](../dpl/index.rst) APIs are implemented to call FreeRTOS APIs underneath,
  - Clock, task, semaphore, heap, cache, MPU, debug logs, HW interrupts, HW timers
- Floating point save/restore with tasks (make sure to call portTASK_USES_FLOATING_POINT() before using floating point operations )

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- R5F ISRs,
  - IRQ mode,
    - FPU save/restore is supported.

::::{only} SOC_AM263X

- nested interrupts are supported.

::::

::::


::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- M4F ISRs,
  - nested interrupts supported

::::


::::{only} SOC_AM62AX or SOC_AM62DX

- DM_R5F ISRs,
  - IRQ mode,
    - FPU save/restore is supported.
- MCU_R5 ISRs
  - IRQ mode,
    - nested interrupts supported

::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62LX

- A53 ISRs,
  - IRQ mode,
    - nested interrupts supported

::::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


SysConfig can be used to configure below modules with FreeRTOS
- Clock module, to setup system tick timer including the tick duration
- Debug Log module, to select the console to use for logging as well as enable/disable logging zones

::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- MPU ARMv7, to setup different MPU regions for R5F and M4F CPUs

::::


::::{only} SOC_AM62X or SOC_AM64X or SOC_AM62LX

- MMU ARMv8, to setup different MMU regions for A53 CPUs

::::


::::{only} SOC_AM62AX or SOC_AM62DX

- MPU ARMv7, to setup different MPU regions for DM_R5F and MCU_R5F CPUs
- MMU ARMv8, to setup different MMU regions for A53 CPUs and C75 core

::::


::::{only} SOC_AM62X or SOC_AM243X or SOC_AM64X

- Address Translate module, to setup  address translation regions, needed for M4F

::::


::::{only} SOC_AM62AX or SOC_AM62DX

- Address Translate module, to setup  address translation regions, needed for DM_R5F and MCU_R5F

::::

- HW Timer module, to setup HW timer available on the SOC, including enabling timer interrupt and ISR registration

## Features Not Supported

- Co-routines, stream buffer are not enabled and are not compiled by default. Users can add these to the FreeRTOS config and makefile if they want to use these features.
- Tickless IDLE mode
- Task level memory protection wrapper

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- R5F ISRs,

::::{only} SOC_AM243X or SOC_AM64X or SOC_AWR294X or SOC_AM273X or SOC_AM62AX or SOC_AM62DX

- IRQ mode,
  - nested interrupts is disabled, due to issues in some corner cases.

::::

- FIQ mode,
  - nested interrupts not supported
  - FPU save/restore not supported.

::::


::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- M4F ISRs,
  - FPU save/restore not supported.

::::


::::{only} SOC_AM62AX or SOC_AM62DX

- DM_R5F ISRs,
  - IRQ mode,
    - nested interrupts is disabled, due to issues in some corner cases.
  - FIQ mode,
    - nested interrupts not supported.
    - FPU save/restore not supported.
- MCU_R5F ISRs
  - FPU save/restore not supported.

::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- A53 ISRs,
  - FPU save/restore not supported.

::::


## Important files and directory structure

FreeRTOS source is distributed along with {{ VAR_SDK_NAME }} and given below are some important files and folders related to FreeRTOS.

<table>
<tr>
    <th>Folder/Files
    <th>Description
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/source/kernel/</td></tr>
<tr>
    <td>dpl/
    <td>APIs to access FreeRTOS features in a OS agnostic way</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/source/kernel/freertos</td></tr>
<tr>
    <td>lib/
    <td>FreeRTOS library to link against. Linking to the library in this path enables the application to operate in FreeRTOS mode </td>
</tr>
<tr>
    <td>config/
    <td>FreeRTOS and FreeRTOS POSIX configuration header files for different CPUs within a SOC.
</tr>
<tr>
    <td>FreeRTOS-Kernel/
    <td>FreeRTOS Kernel source code. MCU+ SDK simply clones the code from FreeRTOS github and does not modify anything in this folder</td>
</tr>

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

<tr>
    <td>FreeRTOS-Kernel-smp/
    <td>FreeRTOS Kernel source code for SMP. MCU+ SDK simply clones the code from FreeRTOS github and does not modify anything in this folder</td>
</tr>

::::

<tr>
    <td>FreeRTOS-POSIX/
    <td>FreeRTOS POSIX wrapper source code. MCU+ SDK simply clones the code from FreeRTOS POSIX github and does not modify anything in this folder</td>
</tr>
<tr>
    <td>portable/
    <td>SDK FreeRTOS porting related files for different CPUs</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/source/kernel/freertos/dpl</td></tr>
<tr>
    <td>common/
    <td>FreeRTOS DPL APIs that are common across all CPUs
</tr>
<tr>
    <td>m4/
    <td>FreeRTOS DPL APIs that are specific to M4F CPUs
</tr>
<tr>
    <td>r5/
    <td>FreeRTOS APIs that are specific to R5F CPUs
</tr>


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62LX
   <tr>
       <td>a53/
       <td>FreeRTOS APIs that are specific to A53 CPUs
   </tr>
:::


:::{only} SOC_AM62AX or SOC_AM62DX
   <tr>
       <td>C75/
       <td>FreeRTOS APIs that are specific to C75 Core
   </tr>
:::


</table>

In addition to above files, to enable features like HW interrupts, cache, MPU, the FreeRTOS library
in {{ VAR_SDK_NAME }} also shares some code with NORTOS, see to makefile in the folder `source\kernel\freertos` to see the exact list of files
that are included to build a freertos library.

## FreeRTOS usage guidelines

See [FreeRTOS usage guidelines](freertos_important_guidelines.md) for FreeRTOS usage guidelines and comparison to SysBIOS.

## Additional references

Given below are some references to learn more about FreeRTOS.

<table>
<tr>
    <th>Document Description
    <th>Web link
</tr>
<tr>
    <td>Easy to read FreeRTOS book
    <td>https://www.freertos.org/Documentation/RTOS_book.html
</tr>
<tr>
    <td>FreeRTOS user docs
    <td>https://www.freertos.org/features.html
</tr>
<tr>
    <td>User API reference
    <td>https://www.freertos.org/a00106.html
</tr>
<tr>
    <td>FreeRTOS core kernel source code
    <td>https://github.com/FreeRTOS/FreeRTOS-Kernel
</tr>
<tr>
    <td>FreeRTOS core kernel example source code
    <td>https://github.com/FreeRTOS/FreeRTOS/tree/master/FreeRTOS
</tr>
<tr>
    <td>Additional FreeRTOS.org maintained libraries (POSIX, TCP, Filesystem, …)
    <td>https://www.freertos.org/FreeRTOS-Labs/index.html \n
    https://www.freertos.org/FreeRTOS-Plus/index.html \n
    https://github.com/FreeRTOS
</tr>
</table>

## See also

[Driver Porting Layer (DPL)](../dpl/index.rst), [NO RTOS](nortos.md)
