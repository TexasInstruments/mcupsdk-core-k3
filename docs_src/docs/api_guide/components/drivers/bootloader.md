# BOOTLOADER {#DRIVERS_BOOTLOADER_PAGE}

[TOC]

The Bootloader module provides APIs to write bootloader applications for various boot media like OSPI, UART, SOC memory etc.

\note The bootloader driver is tested only in the context of a single thread and should be used only sequentially to boot cores to prevent potential errors and ensure stability. Also the current design of bootloader does not support parallel boot even when run in multiple threads.

## Bootloader Migration Guidelines {#BOOTLOADER_MIGRATION_GUIDELINE}
While migrating to 11.00.00 @VAR_SDK_NAME, using the older example.syscfg file for bootloader examples with ospi dma enabled, can throw following error in gui, while running the command make syscfg-gui
\imageStyle{bootloader_udma_multiple_instances.png,width:60%}
\image html bootloader_udma_multiple_instances.png "Bootloader adds multiple udma instances"

While using make command to build the example, it will throw following error
\code
error: CONFIG_BOOTLOADER_FLASH_LINUX(/drivers/bootloader/bootloader) udmaDriver.$name: Duplicate name: 'CONFIG_UDMA0' also exists on instance(s) of UDMA
error: CONFIG_FLASH0(/board/flash/flash) serialFlashDriver.peripheralDriver.udmaDriver.$name: Duplicate name: 'CONFIG_UDMA0' also exists on instance(s) of UDMA
error: CONFIG_BOOTLOADER_FLASH_LINUX(/drivers/bootloader/bootloader) udmaBlkCopyChannel.$name: Duplicate name: 'CONFIG_UDMA_BLKCOPY_CH0' also exists on instance(s) of UDMA Block Copy Channel Configuration
error: CONFIG_FLASH0(/board/flash/flash) serialFlashDriver.peripheralDriver.udmaBlkCopyChannel.$name: Duplicate name: 'CONFIG_UDMA_BLKCOPY_CH0' also exists on instance(s) of UDMA Block Copy Channel Configuration
error: CONFIG_BOOTLOADER_FLASH_LINUX(/drivers/bootloader/bootloader) udmaDriver.instance: Same instance cannot be selected
error: CONFIG_FLASH0(/board/flash/flash) serialFlashDriver.peripheralDriver.udmaDriver.instance: Same instance cannot be selected
\endcode

To fix this, update the example.syscfg, for every instance of bootloader define udma driver and udma block copy channel, refer the below lines to update example.syscfg
\code
const udma                                           = scripting.addModule("/drivers/udma/udma", {}, false);
const udma1                                          = udma.addInstance({}, false);
udma1.$name                                          = "CONFIG_UDMA0";
flash1.serialFlashDriver.peripheralDriver.udmaDriver = udma1;
bootloader1.udmaDriver                               = udma1;
bootloader2.udmaDriver                               = udma1;
bootloader3.udmaDriver                               = udma1;

const udma_blkcopy_channel                                   = scripting.addModule("/drivers/udma/udma_blkcopy_channel", {}, false);
const udma_blkcopy_channel1                                  = udma_blkcopy_channel.addInstance({}, false);
udma_blkcopy_channel1.$name                                  = "CONFIG_UDMA_BLKCOPY_CH0";
flash1.serialFlashDriver.peripheralDriver.udmaBlkCopyChannel = udma_blkcopy_channel1;
bootloader1.udmaBlkCopyChannel                               = udma_blkcopy_channel1;
bootloader2.udmaBlkCopyChannel                               = udma_blkcopy_channel1;
bootloader3.udmaBlkCopyChannel                               = udma_blkcopy_channel1;
\endcode

## Features Supported

- OSPI Boot
- MEM Boot (Boot media is SOC memory)
- API to parse multicore appimage
- Separate APIs to boot self and non-self cores

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Bootloader instance name
- Boot Media to be used
- Boot Image offset

## R5 Dual Core Support

RBL boots the R5 in eFUSE default, which is **split mode**. SBL (Secondary Boot Loader) follows the same and keeps the R5s in split mode. As of now the lock step configuration of dual R5 is not supported from bootloader.

## Example Usage

Include the below file to access the APIs
\snippet Bootloader_sample.c include

Instance Open Example
\snippet Bootloader_sample.c open

Booting Cores Example
\if SOC_AM64X
\snippet Bootloader_sample.c bootcores_am64x
\else
\snippet Bootloader_sample.c bootcores
\endif

Instance Close Example
\snippet Bootloader_sample.c close

## API

\ref DRV_BOOTLOADER_MODULE
