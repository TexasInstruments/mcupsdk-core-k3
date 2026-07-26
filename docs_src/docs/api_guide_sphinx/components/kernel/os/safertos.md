# SafeRTOS

## Introduction

The SDK will include only the safertos dpl layer. This needs the SafeRTOS kernel to build and use.
Please contact WITTENSTEIN for SafeRTOS kernel package.

## Extraction of safertos package

The safertos package needs to be extracted and placed in the below location

::::{only} SOC_AM62AX

```
${SDK_INSTALL_PATH}/source/kernel/safertos/c75          (location for C7X package, renamed as c75)
${SDK_INSTALL_PATH}/source/kernel/safertos/r5f          (location for R5F package, renamed as r5f)
```

::::


After extraction, the safeRTOS should have the below folders structure. This is to make sure the safertos package extraction is proper for building with the SDK build system.

::::{only} SOC_AM62AX

```
| - c75                                                 (folder structure for C7X package)
    | - api
    | - config
    | - kernel
    | - portable
    | - runtimestats
```

::::


::::{only} SOC_AM62AX

```
| - r5f                                                 (folder structure for R5F package)
    | - api
    | - config
    | - kernel
    | - portable
    | - queue_registry
    | - runtimestats
```

::::


## Building Safertos library
The Safertos libs are not pre built when the SDK is installed.
You can use the makefiles to build please refer [Using SDK with Makefiles](../../../../../developer_guides/makefile_build.md)

The makefiles required to build safertos libs are part of the SDK package.

### Build for C7X

- To build the safertos library, do below,
```
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_c75x.ti-c7000 PROFILE=release
```
- To clean  the safertos library, do below
```
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_c75x.ti-c7000_clean PROFILE=release
```
### Build for R5F

- To build the safertos library, do below,
```
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_r5f.ti-arm-clang PROFILE=release
```
- To clean  the safertos library, do below
```
    cd ${SDK_INSTALL_PATH}
    gmake -s -f makefile.am62ax safertos_r5f.ti-arm-clang_clean PROFILE=release
```
## Features Supported

::::{only} SOC_AM62AX

**C75 Core**
- C75 core support
- DPL interface for Task, semaphores, mutex, queues, timers
- C75 ISRs

**R5F Core**
- R5F core support
- DPL interface for Task, semaphores, mutex, queues, timers
- R5F ISRs

::::


Application-dependent parameters : queue registry size (only for R5F) and runtime statistics (for both R5F and C75) are disabled in configSafeRTOSConfig.h of source.
Enable them as required by your application.

## Migration of examples built with freertos to safertos

This section lists the changes required to build the example with safertos.
Assumption is application is using the DPL.
If it is calling any APIs of freertos directly they they need to be ported.

Refer the makefile and linker.cmd file from below path for building with safertos.

::::{only} SOC_AM62AX

```
${SDK_INSTALL_PATH}\examples\hello_world\am62ax-sk\c75ss0-0_safertos\ti-c7000       (for c7x applications)
${SDK_INSTALL_PATH}\examples\hello_world\am62ax-sk\r5fss0-0_safertos\ti-arm-clang   (for r5f applications)
```

::::


Listed below are some major differences:

- Update Include path for C75 core
    - Remove the below freertos include path in makefile
            ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/c75x
        - Add the below safertos include path in makefile
            ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/kernel/include_api
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/230_C7x
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/NoWrapper
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x/005_TI_CGT
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/config
    
- Update Include path for R5F core
    - Remove the below freertos include path in makefile
            ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f
        - Add the below safertos include path in makefile
            ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/kernel/include_api
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/199_TI_CR5
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/PrivWrapperStd
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5/024_Clang
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/config
    
- Update libraries provided for C75 Linker
    - Remove the freertos lib in makefile
            freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
        - Add the safertos lib in makefile
            safertos.am62ax.c75x.ti-c7000.${ConfigName}.lib
    
- Update libraries provided for R5F Linker
    - Remove the freertos lib in makefile
            freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib
        - Add the safertos lib in makefile
            safertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib
    
- Update the library path
    - Remove the lib path of freertos in makefile
        ${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib
        - Add the lib path of safertos in makefile
        ${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib
    
- Linker cmd file
    - Use the linker cmd file from the hello_world safertos example.
    - Please do the changes as required for the application on top of this.

## See also

[Driver Porting Layer (DPL)](../dpl/index.rst)
