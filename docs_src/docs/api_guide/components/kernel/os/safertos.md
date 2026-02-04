# SafeRTOS {#KERNEL_SAFERTOS_PAGE}

[TOC]

## Introduction

The SDK will include only the safertos dpl layer. This needs the SafeRTOS kernel to build and use.
Please contact WITTENSTEIN for SafeRTOS kernel package.

## Extraction of safertos package

The safertos package needs to be extracted and placed in the below location

\cond SOC_AM62AX
    ${SDK_INSTALL_PATH}/source/kernel/safertos/c75          (location for C7X package, renamed as c75)
\endcond

After extraction, the safeRTOS should have the below folders structure. This is to make sure the safertos package extraction is proper for building with the SDK build system.

\cond SOC_AM62AX
    | - c75                                                 (folder structure for C7X package)
        | - api
        | - config
        | - kernel
        | - portable
        | - runtimestats
\endcond

## Building Safertos library {#KERNEL_SAFERTOS_LIB_BUILD}

The Safertos libs are not pre built when the SDK is installed.
You can use the makefiles to build please refer \ref MAKEFILE_BUILD_PAGE

The makefiles required to build safertos libs are part of the SDK package.

- To build the safertos library, do below,
\code
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_c75x.ti-c7000 PROFILE=release
\endcode

- To clean  the safertos library, do below
\code
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_c75x.ti-c7000_clean PROFILE=release
\endcode

## Features Supported

\cond SOC_AM62AX
- C75 core support
- DPL interface for Task, semaphores, mutex, queues, timers
- C75 ISRs
\endcond

## Migration of examples built with freertos to safertos

This section lists the changes required to build the example with safertos.
Assumption is application is using the DPL.
If it is calling any APIs of freertos directly they they need to be ported.

Refer the makefile and linker.cmd file from below path for building with safertos.
\cond SOC_AM62AX
    ${SDK_INSTALL_PATH}\examples\hello_world\am62ax-sk\c75ss0-0_safertos\ti-c7000
\endcond
Listed below are some major differences
- Update Include path
    - Remove the below freertos include path in makefile
    \code
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/c75x
    \endcode
    - Add the below safertos include path in makefile
    \code
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/kernel/include_api
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/230_C7x
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/NoWrapper
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x/005_TI_CGT
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/config
    \endcode

- Update libraries provided for Linker
    - Remove the freertos lib in makefile
    \code
        freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
    \endcode
    - Add the safertos lib in makefile
    \code
        safertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
    \endcode

- Update the library path
    - Remove the lib path of freertos in makefile
    \code
    ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib
    \endcode
    - Add the lib path of safertos in makefile
    \code
    ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib
    \endcode

- Linker cmd file
    - Use the linker cmd file from the hello_world safertos example.
    - Please do the changes as required for the application on top of this.

## See also

\ref KERNEL_DPL_PAGE
