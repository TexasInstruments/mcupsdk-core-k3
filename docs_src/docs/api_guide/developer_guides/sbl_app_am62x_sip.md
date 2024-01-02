# Support for SK-AM62-SIP {#SUPPORT_FOR_SK_AM62_SIP}

[TOC]

## Introduction
AM62x SIP is the smallest AM62x module form factor, which integrates high-speed memory, power management, passive components into a single package.
All the examples (excpet SBL) avaiable for am62x-sk can be directly used for SK-AM62-SIP as well. All the SBL examples needs to be changed to use a different DDR configration.

## Steps to build SBL application for AM62x SIP

### STEP 1 - Download AM62x SIP DDR configuration file {#STEP1}
AM62x SIP is packaged with 512MB lpddr, it uses a different DDR configuration file. Download the the AM62x SIP DDR configuration file here, \htmllink{../am62x_SIP_ddrReginit-50-800.h,am62x_SIP_ddrReginit-50-800.h}.

### STEP 2 - Update DDR configuration file for UART uniflash
Update the DDR configuration file for uart_uniflash_stage1 with the path of the file downloaded in \ref STEP1 which is needed to flash application images via the UART.

````bash
    make -C ~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage1/am62x-sk/r5fss0-0_nortos/ti-arm-clang syscfg-gui
````
\imageStyle{uart_stage1_ddr_configuration.png,width:70%}
\image html uart_stage1_ddr_configuration.png "UART DDR CONFIGURATION"

### STEP 3 - Update DDR configuration file for SBL application
For all SBL applications, update the DDR configuration file with the file downloaded in \ref STEP1. For example, in case of sbl_ospi_linux_multistage, DDR driver is included in the sbl_ospi_linux_stage1, update the DDR configuration file .

````bash
    make -C ~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/am62x-sk/r5fss0-0_nortos/ti-arm-clang syscfg-gui
````

\imageStyle{ospi_linux_stage1_ddr_configuration.png,width:70%}
\image html ospi_linux_stage1_ddr_configuration.png "SBL OSPI DDR CONFIGURATION"

To build and flash binaries refer \ref EVM_SETUP_PAGE and \ref GETTING_STARTED_FLASH.