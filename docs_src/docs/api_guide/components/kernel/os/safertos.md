# SafeRTOS {#KERNEL_SAFERTOS_PAGE}

[TOC]

## Introduction

The SDK will include only the safertos dpl layer. This needs the SafeRTOS kernel to build and use.
Please contact WITTENSTEIN for SafeRTOS kernel package.

## Extraction of safertos package

The safertos package needs to be extracted and placed in the below location

\cond SOC_AM62AX
    ${SDK_INSTALL_PATH}/source/kernel/safertos/c75          (location for C7X package, renamed as c75)
    ${SDK_INSTALL_PATH}/source/kernel/safertos/r5f          (location for R5F package, renamed as r5f)
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

\cond SOC_AM62AX
    | - r5f                                                 (folder structure for R5F package)
        | - api
        | - config
        | - kernel
        | - portable
        | - queue_registry
        | - runtimestats
\endcond

## Building Safertos library {#KERNEL_SAFERTOS_LIB_BUILD}

The Safertos libs are not pre built when the SDK is installed.
You can use the makefiles to build please refer \ref MAKEFILE_BUILD_PAGE

The makefiles required to build safertos libs are part of the SDK package.

### Build for C7X

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

### Build for R5F

- To build the safertos library, do below,
\code
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_r5f.ti-arm-clang PROFILE=release
\endcode

- To clean  the safertos library, do below
\code
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_r5f.ti-arm-clang_clean PROFILE=release
\endcode

## Features Supported

\cond SOC_AM62AX
C75 Core
- C75 core support
- DPL interface for Task, semaphores, mutex, queues, timers
- C75 ISRs

R5F Core
- R5F core support
- DPL interface for Task, semaphores, mutex, queues, timers
- R5F ISRs
\endcond

\note The runtimestats (configured using configINCLUDE_RUNTIMESTATS for r5f, and c75) and queueregistry (configured using configQUEUE_REGISTRY_SIZE for r5f) features within the SDK are NOT supported with SafeRTOS but are enabled by default in config/SafeRTOSConfig.h. They should be disabled to avoid compilation issues.

## Migration of examples built with freertos to safertos

This section lists the changes required to build the example with safertos.
Assumption is application is using the DPL.
If it is calling any APIs of freertos directly they they need to be ported.

Refer the makefile and linker.cmd file from below path for building with safertos.
\cond SOC_AM62AX
    ${SDK_INSTALL_PATH}\examples\hello_world\am62ax-sk\c75ss0-0_safertos\ti-c7000       (for c7x applications)
    ${SDK_INSTALL_PATH}\examples\hello_world\am62ax-sk\r5fss0-0_safertos\ti-arm-clang   (for r5f applications)
\endcond

Listed below are some major differences:

- Update Include path for C75 core
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

- Update Include path for R5F core
    - Remove the below freertos include path in makefile
    \code
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f
    \endcode
    - Add the below safertos include path in makefile
    \code
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/kernel/include_api
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/199_TI_CR5
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/PrivWrapperStd
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5/024_Clang
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/config
    \endcode

- Update libraries provided for C75 Linker
    - Remove the freertos lib in makefile
    \code
        freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
    \endcode
    - Add the safertos lib in makefile
    \code
        safertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
    \endcode

- Update libraries provided for R5F Linker
    - Remove the freertos lib in makefile
    \code
        freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib
    \endcode
    - Add the safertos lib in makefile
    \code
        safertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib
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
