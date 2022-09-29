# Writing flash driver for a custom flash device {#CUSTOM_FLASH_SUPPORT_GUIDE}

[TOC]

## Introduction

The flash driver provided in the SDK package can communicate with a limited number of flashes as listed in \ref BOARD_FLASH_PAGE. While we can always talk to a flash in 1S-1S-1S mode of communication after a soft reset, the data throughput offered by this mode will be quite less compared the maximum supported by the flash (4S-4D-4D or 8D-8D-8D)

If a different external flash is being used, the flash driver will need certain modifications and configuration changes to work properly. This guide will help in the process of developing/modifying the flash driver to suit the custom external flash being used.

## Summary of steps needed to enable a new flash device

 - **Step 1**: Build the `ospi_flash_diag` example : \ref EXAMPLES_DRIVERS_OSPI_FLASH_DIAG. This example communicates with the flash in 1S-1S-1S mode and queries the flash for the SFDP table (if SFDP is supported by the flash) among other things. The logs from this example would be required later to configure the flash driver.

 - **Step 2**: Create a new driver in the SDK to support the new flash device.

 - **Step 3**: Obtain flash details from the SFDP table OR datasheet of the flash device and map it to the settings in flash driver.

 - **Step 4**: Test the new flash driver with the changes using `ospi_flash_io` example : \ref EXAMPLES_DRIVERS_OSPI_FLASH_IO

 - **Step 5**: Test the flash driver with OSPI bootloader \ref EXAMPLES_DRIVERS_SBL_OSPI and flash writer \ref EXAMPLES_DRIVERS_SBL_UART_UNIFLASH by flashing an example \ref GETTING_STARTED_FLASH


## Step 1: Building the OSPI Flash Diagnostic example

Refer the example page \ref EXAMPLES_DRIVERS_OSPI_FLASH_DIAG on building this application. You will need have to initialize the SOC in no boot mode as mentioned in \ref EVM_SOC_INIT_NOBOOT_MODE  and also load and run this example using CCS, as mentioned in \ref CCS_LAUNCH_PAGE. Take logs printed by the example and save it in a txt file. We would need to refer these logs later while configuring the flash driver.

## Step 2: Creating a new flash driver

### Flash driver structure in the SDK

The flash driver in the SDK composes of two layers :

 - Generic flash layer, which will then call the actual flash driver APIs using registered function pointers
 - Flash device specific layer which will communicate with the flash using the underlying NOR SPI controller APIs

The application should only use the APIs from the generic flash layer, this makes sure that there is no dependency on a particular flash type. This layer mostly needs no modifications to support a new flash. The generic flash driver has 5 major functions which will internally just call registered callbacks specific to the device. They are :

- \ref Flash_open
- \ref Flash_close
- \ref Flash_read
- \ref Flash_write
- \ref Flash_eraseBlk

Out of these, the \ref Flash_open is the most important one. That is where the flash would be configured to work in a specific mode and also set the NOR SPI controller to talk to the flash. The callbacks to these will be implemented in the device specific layer.

### Adding new files to device specific layer

There are 3 files needed per flash in the device specific layer as per the current driver structure :

 - `flash_nor_*spi.c`
 - `flash_nor_*spi.h`
 - `flash_nor_*spi_device_<flash-part-number>.c`

These files need to be located in the `${SDK_ROOT_DIRECTORY}/source/board/flash` folder. For example we have `flash_nor_xspi.c`, `flash_nor_xspi.h` and `flash_nor_xspi_device_S28HS512T.c` files for the S28HS512T device. These can be edited to support the new flash device. The implementation of the 5 callbacks mentioned in the above section can be found in `flash_nor_xspi.c`. A new device data file (similar to `flash_nor_xspi_device_S28HS512T.c`) needs to created with the appropriate flash part number. Copy from the existing file and change just the flash part numbers for now. Other details can be updated in a while.

To enable build support for this file, add it to the makefile `${SDK_ROOT_DIRECTORY}/source/board/makefile.{soc}.{core}.ti-arm-clang` under FILES_common.

The flash sysconfig also should be updated so that later in examples the flash can be selected appropriately. For this open the `$(SDK_ROOT_DIRECTORY)/source/board/.meta/flash/flash_{soc}.syscfg.js` file. The object `flash_devices` will have a number of entries corresponding to the currently supported flashes. Add a new entry corresponding the new flash.

 - For name, give the flash part number in ALL CAPS. Note, this has to match with the part number given in `flash_nor_xspi_device_<flash_part_number>.c` filename

 - For type, "NOR XSPI" or "NOR QSPI" depending on the flash type. When sysconfig registers the callbacks, it is going to look for `gFlashNorXspiFxns` if the type is "NOR XSPI", `gFlashNorQspiFxns` if the type is "NOR QSPI" and so on

 - For size, give the flash size in bytes

Confirm that the files build and the new flash device is selectable in sysconfig. We can now update the files according to the new flash device.

## Step 3: Obtaining flash details from the SFDP table OR datasheet

### Flash configuration information

In order to program the flash device and NOR SPI controller to work in the best configuration (maximum data throughput) supported by the flash device, these are the bare minimum data required from the flash :

- Flash size in bytes
- Block size in bytes
- Page size in bytes
- Addressing mode support (3 byte or 4 byte)
- Support of a specific protocol (4-4-4, 8-8-8 etc)
- If supported how to enable the flash to work with this protocol
- Support of DTR (Dual Transfer Rate, or sampling on both edges of the clock)
- If supported how to enable DTR
- Read and Write opcodes for a particular protocol
- Dummy cycles required for a particular protocol
- How to set the dummy cycles
- Extension for opcodes if working with 8D protocol (Octal DTR)
- Erase and page program timeouts
- Order of bytes in 8D mode if 8D mode is supported
- Hybrid sector feature

Enabling a specific protocol or DTR or setting the dummy cycles are done by writing to various configuration registers in the flash. These data about the flash can be found out in 2 ways, from the flash datasheet or SFDP (Serial Flash Discoverable Parameters) standard. Strictly speaking the SFDP is not a complete replacement for the datasheet, but SFDP can provide data about all the details mentioned above. If the custom flash device supports SFDP, we can use that. If not, we'll have to rely on the flash datasheet to get these informations.

### Serial Flash Discoverable Parameters (SFDP)

The Serial Flash Discoverable Parameters (SFDP) is a standard which provides a consistent method of describing the functional and feature capabilities of the flash device in a standard set of internal parameter tables. This table can be queried to identify the configurations and adjustments needed to set the flash in a desired state.

The parsing of the SFDP table is time consuming. Considering this, the SFDP parsing feature in this SDK is tied with a diagnostic example of the NOR SPI driver. In flashes where the SFDP is supported, this example can be used to parse the details into a config structure which can aid in writing the custom flash driver. As of now the SFDP parsing in the SDK supports JEDS216D standard.

### Using the output of OSPI Flash Diagnostic example

The `ospi_flash_diag` example reads the SFDP table (in 1S-1S-1S mode) and prints the parsed result in the form of a struct which can be used to fill in your own device defines struct. Here is a sample output:

 \code
================================================
                      SFDP                      
================================================
SFDP Major Revision                       : 0x1
SFDP Minor Revision                       : 0x8
Number of Parameter Headers in this Table : 6

Types of Additional Parameter Tables in this flash
---------------------------------------------------
4 BYTE ADDRESSING MODE INSTRUCTIONS TABLE
XSPI PROFILE TABLE 
STATUS CONTROL AND CONFIGURATION REGISTER MAP TABLE
OCTAL DDR MODE COMMAND SEQUENCE TABLE
SECTOR MAP TABLE

Parsing of OCTAL DDR MODE COMMAND SEQUENCE TABLE table not yet supported. 

Flash_NorXspiDevDefines gFlashNorXspiDeviceDefines_<part-number> = {

    .XSPI_NOR_CMD_RSTEN = 0x66,
    .XSPI_NOR_CMD_RSTMEM = 0x99,
    .XSPI_NOR_CMD_WREN = 0x06,
    .XSPI_NOR_CMD_WRREG = 0x71,
    .XSPI_NOR_CMD_BULK_ERASE = 0xC7,
    .XSPI_NOR_CMD_SECTOR_ERASE_3B = 0x21,
    .XSPI_NOR_CMD_SECTOR_ERASE_4B = 0x21,
    .XSPI_NOR_CMD_BLOCK_ERASE_3B = 0xDC,
    .XSPI_NOR_CMD_BLOCK_ERASE_4B = 0xDC,
    .XSPI_NOR_CMD_PAGE_PROG_3B = 0x02,
    .XSPI_NOR_CMD_PAGE_PROG_4B = 0x12,
    .XSPI_NOR_CMD_RDSR = 0x05,
    .XSPI_NOR_CMD_RDREG = 0x65,
    .XSPI_NOR_CMD_RDID = 0x9F,
    .XSPI_NOR_CMD_READ = 0x03,
    .XSPI_NOR_CMD_888_SDR_READ = 0x00,
    .XSPI_NOR_CMD_888_DDR_READ = 0xEE,
    .XSPI_NOR_CMD_444_SDR_READ = 0x00,
    .XSPI_NOR_CMD_444_DDR_READ = 0x00,
    .XSPI_NOR_CMD_114_READ = 0x00,
    .XSPI_NOR_SR_WIP = 1,
    .XSPI_NOR_SR_WEL = 2,
    .XSPI_NOR_RDID_NUM_BYTES = 5,
    .XSPI_NOR_MANF_ID = 0x34,
    .XSPI_NOR_DEVICE_ID = 0x5B1A,
    .XSPI_NOR_114_READ_MODE_CLKS = 0,
    .XSPI_NOR_114_READ_DUMMY_CYCLES = 0,
    .XSPI_NOR_444_READ_MODE_CLKS = 0,
    .XSPI_NOR_444_READ_DUMMY_CYCLES = 0,
    .XSPI_NOR_444_READ_DUMMY_CYCLES_LC = 0xFF,
    .XSPI_NOR_QUAD_CMD_READ_DUMMY_CYCLES = 0x00,
    .XSPI_NOR_OCTAL_READ_DUMMY_CYCLE = 24,
    .XSPI_NOR_OCTAL_READ_DUMMY_CYCLE_LC = 0x0B,
    .XSPI_NOR_OCTAL_DDR_RDSR_DUMMY_CYCLE = 4,
    .XSPI_NOR_OCTAL_DDR_RDREG_ADDR_BYTES = 4, 
    .XSPI_NOR_OCTAL_DDR_WRREG_ADDR_BYTES = 4, 
    .XSPI_NOR_OCTAL_DDR_RDVREG_DUMMY_CYCLE = 4, 
    .XSPI_NOR_OCTAL_DDR_RDNVREG_DUMMY_CYCLE = 8, 
    .XSPI_NOR_OCTAL_RDSFDP_DUMMY_CYCLE = 8, 
    .XSPI_NOR_OCTAL_RDSFDP_ADDR_TYPE = 0, 
    .XSPI_NOR_WRR_WRITE_TIMEOUT = 5120,
    .XSPI_NOR_BULK_ERASE_TIMEOUT = 256000000,
    .XSPI_NOR_PAGE_PROG_TIMEOUT = 512,
    .XSPI_NOR_VREG_OFFSET = 0x800000,
    .XSPI_NOR_NVREG_OFFSET = 0x0,
    .XSPI_NOR_QUAD_MODE_CFG_ADDR = 0x0,
    .XSPI_NOR_QUAD_MODE_CFG_BIT_LOCATION = 0x0,
    .XSPI_NOR_DDR_OCTAL_MODE_CFG_ADDR = 0x6,
    .XSPI_NOR_DDR_OCTAL_MODE_CFG_BIT_LOCATION = 0x1,
    .XSPI_NOR_DUMMY_CYCLE_CFG_ADDR = 0x3,
    .XSPI_NOR_FLASH_SIZE = 67108864,
    .XSPI_NOR_PAGE_SIZE = 256,
    .XSPI_NOR_BLOCK_SIZE = 262144,
    .XSPI_NOR_SECTOR_SIZE = 4096,
    .addrByteSupport = 1,
    .dtrSupport = 1,
    .qeType = 0,
    .seq444Enable = { 0, 0, 0, 0, 0 },
    .seq444Disable = { 0, 0, 0, 0 },
    .oeType = 0,
    .cmdExtType = 0,
    .byteOrder = 0,
};

 \endcode

Comparing this output and the definitions in the `flash_nor_xspi_device_<flash_part_number>.c` file (This should currently have data corresponding to the S28HS512T flash device), we can update the different struct member values and macros like FLASH_PAGE_SIZE and FLASH_BLOCK_SIZE. Note, the sample output given here is from S28HS512T device.

Here are the changes to look out for in the driver depending on the SFDP parsed table print:

- If cmdExtType = 0, set the cmdExtType as \ref OSPI_CMD_EXT_TYPE_REPEAT. If 1, set as \ref OSPI_CMD_EXT_TYPE_INVERSE. You can do this using the API \ref OSPI_setCmdExtType

- If the byteOrder is 1, there is no driver change. But you can only read back data in 8D mode if it was flashed in 8D mode in the first place. If byteOrder is 0, there is no difference between 1S mode and 8D mode.

- If the dtrSupport is 1, flash supports DTR. Set the dtrEnable of the Flash_NorXspiObject as true only if the flash supports it. Dual opcode mode also should be enabled if Octal DTR is supported. This can be done using \ref OSPI_setDualOpCodeMode

- For address bytes support,
	- If addrByteSupport = 0, only 3 byte addressing supported. This is the default set in controller
	- If addrByteSupport = 1, Both 3 and 4 byte supported, default is 3 byte mode. In this case you can switch to 4 byte mode whenever you want in the Flash_NorXspiOpen function. 
	- If addrByteSupport = 2, Only 4 byte addressing supported. Rare scenario. In this case the ospi_diag_example itself might fail to work. 

- Quad mode enabling is a tricky issue to deal with in the open function in case of QSPI flashes. The exact sequence for that can be found out using the information from values of qeType variable, seq444Enable and seq444Disable arrays.
	
- qeType - This can give values 0-6. This is mostly for enabling the 1-1-4 mode. This table explains what each value means:

	qeType Value | Implication
	-------------|--------------------------
	    0        | Device does not have a QE bit. Device detects 1-1-4 and 1-4-4 reads based on instruction.
	    1        | QE is bit 1 of status register 2. It is set via Write Status with two data bytes where bit 1 of the second byte is one. It is cleared via Write Status with two data bytes where bit 1 of the second byte is zero. Writing only one byte to the status register has the side-effect of clearing status register 2, including the QE bit.
	    2        | QE is bit 6 of status register 1. It is set via Write Status with one data byte where bit 6 is one. It is cleared via Write Status with one data byte where bit 6 is zero
	    3        | QE is bit 7 of status register 2. It is set via Write status register 2 instruction 3Eh with one data byte where bit 7 is one. It is cleared via Write status register 2 instruction `0x3E` with one data byte where bit 7 is zero. The status register 2 is read using instruction `0x3F`.
	    4        | QE is bit 1 of status register 2. It is set via Write Status with two data bytes where bit 1 of the second byte is one. It is cleared via Write Status with two data bytes where bit 1 of the second byte is zero. Writing one byte to the status register does not modify status register 2.
	    5        | QE is bit 1 of the status register 2. Status register 1 is read using Read Status instruction `0x05`. Status register 2 is read using instruction `0x35`. QE is set via Write Status instruction 01h with two data bytes where bit 1 of the second byte is one. It is cleared via Write Status with two data bytes where bit 1 of the second byte is zero.
	    6        | QE is bit 1 of the status register 2. Status register 1 is read using Read Status instruction `0x05`. Status register 2 is read using instruction `0x35`, and status register 3 is read using instruction `0x15`. QE is set via Write Status Register instruction `0x31` with one data byte where bit 1 is one. It is cleared via Write Status Register instruction `0x31` with one data byte where bit 1 is zero.

- seq444Enable - This is an array of 5 flags. Each flag denotes an operation. Depending on which flag is set, that operation needs to be done.

	Flag set          | Operation
	------------------|--------------------------
	  `seq444Enable[0]` | Enable quad mode as per qeType description above, then issue instruction `0x38`
	  `seq444Enable[1]` | Issue instruction `0x38`
	  `seq444Enable[2]` | Issue instruction `0x35`
	  `seq444Enable[3]` | Device uses a read-modify-write sequence of operations: read the `XSPI_NOR_QUAD_MODE_CFG_ADDR` (Make sure to add `XSPI_NOR_VREG_OFFSET`) using `XSPI_NOR_CMD_RDREG` command and set bit `XSPI_NOR_QUAD_MODE_CFG_BIT_LOCATION` to 1. Now write the modified value using `XSPI_NOR_CMD_WRREG`.
	  `seq444Enable[4]` | If this flag is set, don't care about the seq444Disable array. This is again a read-modify-write. Use the `XSPI_NOR_CMD_RDREG` cmd without any address, set bit 7 to 0. Now write back using `0x61` cmd. For disabling follow the same procedure, but set bit 7 to 1 instead.

- seq444Disable - This is an array of 4 flags. Each flag denotes an operation. Depending on which flag is set, that operation needs to be done.

	Flag set           | Operation
	-------------------|--------------------------
	  `seq444Disable[0]` | Issue instruction `0xFF`
	  `seq444Disable[1]` | Issue instruction `0xF5`
	  `seq444Disable[2]` | Device uses a read-modify-write sequence of operations: read the `XSPI_NOR_QUAD_MODE_CFG_ADDR` (Make sure to add `XSPI_NOR_VREG_OFFSET`) using `XSPI_NOR_CMD_RDREG` command and set bit `XSPI_NOR_QUAD_MODE_CFG_BIT_LOCATION` to 0. Now write the modified value using `XSPI_NOR_CMD_WRREG`.
	  `seq444Disable[3]` | Issue soft reset by sending `XSPI_NOR_CMD_RSTEN` cmd followed by `XSPI_NOR_CMD_RSTMEM` cmd.

- For all other commands and dummy cycles, the mapping is pretty much direct to the ones already present in `flash_nor_xspi_device_<flash_part_number>.c`. Pointing out some specifics :
	- For changing to DDR mode or to set the dummy cycles in the flash, write to volatile flash registers.
	
	- The function `Flash_norXspiSetDummyCycles` sets the dummy cycles required. The dummy cycles need to be programmed in the flash and the controller. `XSPI_NOR_OCTAL_READ_DUMMY_CYCLE` is the value for octal mode which needs to be programmed in the controller. This can be done using the \ref OSPI_setReadDummyCycles function. This part must be there already. In case of flash setting, a register read-modify-write will be done to an address. Make sure this address is calculated correctly using `XSPI_NOR_VREG_OFFSET` + `XSPI_NOR_DUMMY_CYCLE_CFG_ADDR` in the driver. Follow the same for setting the octal DTR mode.

	- The value for `cmdDummyCycles` is almost always 4. This is the dummyCycles needed while reading the flash status register or flash config register. However it can change depending on flash, so set this to `XSPI_NOR_OCTAL_DDR_RDVREG_DUMMY_CYCLE`.

### Using the flash datasheet

This section can be ignored if the flash supports SFDP.

All the details regarding the flash including fast read opcodes, supported erase sizes, dummy clocks needed for each instruction and flash configuration registers information will be available from the flash data sheet. 

- Flash size, page size and block size can be obtained from the introduction/overview section of the datasheet.
- The read, write, register read, register write, read ID and other opcodes can be obtained from "Transaction tables". There will be transaction tables for each protocol (For example 1S-1S-1S transaction table, 8D-8D-8D transaction table)

- The number of dummy cycles required for the read opcodes will also be available from the transaction table.

- 4 byte addressing mode will be supported in most flashes. Some of the legacy flashes which had < 16 MB density might still use 3 byte addressing mode

- Check the datasheet to see if 4 byte addressing mode is supported. There are multiple ways flash devices support 4 byte addressing mode. Sometimes there will be a configuration register which can be set so that flash switches to 4 byte addressing mode. In most cases, the flash will have separate set of opcodes for 4 byte addressing mode.

- Configuration registers for setting various protocols, DTR clocking, and dummy cycles can be obtained from register configuration section.

These opcodes and register address values can then be updated in the `flash_nor_xspi_device_<flash_part_number>.c` file. Make necessary changes in the `Flash_norXspiOpen` function to set the 4 byte addressing mode correctly. If it is a case of separate opcodes, you only need to set this for the NOR SPI controller. If it needs a register write to one of the flash config registers, then that needs to be done.

## Step 4: Test the new flash driver with the changes using OSPI Flash I/O example

- Update the example.syscfg of the `ospi_flash_io` example \ref EXAMPLES_DRIVERS_OSPI_FLASH_IO using SysConfig GUI to select the new flash device you have added.

- Build and run the example

## Step 5: Test the flash driver with OSPI bootloader and flash writer

- Similar to the `ospi_flash_io` example, update the example.syscfg for OSPI bootloader (`sbl_ospi`) \ref EXAMPLES_DRIVERS_SBL_OSPI and flash writer (`sbl_uart_uniflash`) \ref EXAMPLES_DRIVERS_SBL_UART_UNIFLASH

- Build the flash writer and the OSPI bootloader.

- Try to flash an application and boot it using the OSPI bootloader. Follow the steps mentioned in \ref GETTING_STARTED_FLASH

## Miscellaneous tips and tricks

- Device delay settings of the OSPI controller might need a change depending on the AC characteristics of the flash. The default value should work for most cases, but if there is a read issue especially at higher clock speeds and octal mode, this might be something to check for.