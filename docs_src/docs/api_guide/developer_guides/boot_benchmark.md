# Boot Benchmarking{#BOOT_BENCHMARK}

[TOC]

## Introduction
Debug logs are ON by default. It is recommended to disable all debug logs before figuring out performance figures to avoid delays due to printing logs. To analyze the boot time of an application running on a core, the debug log of SBL Stage1 Bootloader, SBL Stage2 Bootloader, DM firmware and application logs have to be disabled. Follow the below steps to do so taking OSPI bootloader as an example

 ##### Disable Stage1 Bootloader logs

Navigate to make file of SBL Stage1 Bootloader in mentioned path

\code
${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage1/am62dx-evm/r5fss0-0_nortos/ti-arm-clang/makefile
\endcode

Browse to 'DEFINES_common' section as below and add the flag ' DEBUG_LOG_DISABLE ' like below in makefile

\code
DEFINES_common := \
	-DSOC_AM62DX \
	-DENABLE_SCICLIENT_DIRECT \
    -DDEBUG_LOG_DISABLE \
\endcode

 ##### Disable Stage2 Bootloader logs

Navigate to make file of SBL Stage2 Bootloader in mentioned path

\code
  ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage2/am62dx-evm/r5fss0-0_freertos/ti-arm-clang/makefile\endcode

Browse to 'DEFINES_common' section as below and add the flag ' DEBUG_LOG_DISABLE ' like below in makefile

\code
DEFINES_common := \
	-DSOC_AM62DX \
	-DENABLE_SCICLIENT_DIRECT \
	-DR5F_CORE \
    -DDEBUG_LOG_DISABLE \
\endcode

 ##### Disable DM logs

Navigate to make file of sciserver driver in mentioned path

\code
${SDK_INSTALL_PATH}/source/drivers/device_manager/sciserver/makefile.am62dx.r5f.ti-arm-clang
\endcode

Browse to 'DEFINES_common' section as below and add the flag ' DEBUG_LOG_DISABLE ' like below in makefile

\code
DEFINES_common := \
    -DSOC_AM62AX \
    -DMCU_PLUS_SDK \
    -DBUILD_DM_R5 \
    -DBUILD_MCU1_0 \
    -DBUILD_MCU \
    -DCONFIG_LPM_DM \
    -DCONFIG_OSAL_MINIMAL_QUEUES \
    -DMAKEFILE_BUILD \
    -DDEBUG_LOG_DISABLE \
\endcode


 ##### Disable Application logs

Disable the debug logs of desired application to be run

Rebuild libraries, SBL Stage1 bootloader, SBL Stage2 bootloader and proceed with the benchmarking





