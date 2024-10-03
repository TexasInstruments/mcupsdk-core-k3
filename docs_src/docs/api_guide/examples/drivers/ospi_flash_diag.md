# OSPI Flash Diagnostic {#EXAMPLES_DRIVERS_OSPI_FLASH_DIAG}

[TOC]

# Introduction

This is a diagnostic example for NOR-OSPI Flashes. This example doesn't use the flash driver and should ideally pass for any NOR-OSPI flash. For this particular example, the options in SysCfg
like the number of transfer lines used, or the clock divider value are ignored. This example will always talk to the flash in the lowest settings possible. The flash device is reset, and is
expected to support 1s1s1s mode after reset. Then the OSPI controller is programmed to work in 1s1s1s mode with 3 byte addressing mode.

The test itself is simple, first it tries to read the JEDEC ID of the flash which consists of the flash manufacturer ID and the flash device ID. These are then printed onto the logging console. When
doing flash bring-ups in new boards, this example can be run first for sanity. Users can cross check the printed ID with the one in flash datasheet to confirm that basic communication with flash is working.

The test then tries to erase a flash memory block at an offset of 512 KB and then write some known data to that memory. This data is then read back and verified to confirm that reads and writes are working
in 1s1s1s mode.

# Supported Combinations {#EXAMPLES_DRIVERS_OSPI_FLASH_DIAG_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/ospi/ospi_flash_diag

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ospi/ospi_flash_diag

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ospi/ospi_flash_diag

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_OSPI_PAGE

# Sample Output
\cond SOC_AM62X || SOC_AM62PX || SOC_AM62DX

\code
[OSPI Flash Diagnostic Test] Starting ...
[OSPI Flash Diagnostic Test] Flash Manufacturer ID : 0x34
[OSPI Flash Diagnostic Test] Flash Device ID       : 0x5B1A
[OSPI Flash Diagnostic Test] Executing Flash Erase on first block...
[OSPI Flash Diagnostic Test] Done !!!
[OSPI Flash Diagnostic Test] Performing Write-Read Test...
[OSPI Flash Diagnostic Test] Write-Read Test Passed!
[QSPI Flash Diagnostic Test] SFDP Information :
================================================
                      SFDP
================================================
SFDP Major Revision                       : 0x1
SFDP Minor Revision                       : 0x8
Number of Parameter Headers in this Table : 6

Types of Additional Parameter Tables in this flash
---------------------------------------------------
4 BYTE ADDRESSING MODE INSTRUCTIONS TABLE
NOR SPI PROFILE TABLE
STATUS CONTROL AND CONFIGURATION REGISTER MAP TABLE
OCTAL DDR MODE COMMAND SEQUENCE TABLE
SECTOR MAP TABLE

Parsing of OCTAL DDR MODE COMMAND SEQUENCE TABLE table not yet supported.
JSON Data for the flash :

{

        "flashSize": 67108864,
        "flashPageSize": 256,
        "flashManfId": "0x34",
        "flashDeviceId": "0x5B1A",
        "flashBlockSize": 262144,
        "flashSectorSize": 4096,
        "cmdBlockErase3B": "0xDC",
        "cmdBlockErase4B": "0xDC",
        "cmdSectorErase3B": "0x21",
        "cmdSectorErase4B": "0x21",
        "protos": {
                "p111": {
                        "isDtr": false,
                        "cmdRd": "0x03",
                        "cmdWr": "0x02",
                        "modeClksCmd": 0,
                        "modeClksRd": 0,
                        "dummyClksCmd": 0,
                        "dummyClksRd": 0,
                        "enableType": "0",
                        "enableSeq": "0x00",
                        "dummyCfg": null,
                        "protoCfg": null,
                        "strDtrCfg": null
                },
                "p112": null,
                "p114": null,
                "p118": null,
                "p444s": null,
                "p444d": null,
                "p888s": null,
                "p888d": {
                        "isDtr": true,
                        "cmdRd": "0xEE",
                        "cmdWr": "0x12",
                        "modeClksCmd": 0,
                        "modeClksRd": 0,
                        "dummyClksCmd": 4,
                        "dummyClksRd": 24,
                        "enableType": "0",
                        "enableSeq": "0x00",
                        "dummyCfg": {
                                "isAddrReg": true,
                                "cmdRegRd":"0x65",
                                "cmdRegWr":"0x71",
                                "cfgReg":"0x00800003",
                                "shift":0,
                                "mask":"0x03",
                                "bitP":11
                        },
                        "protoCfg": {
                                "isAddrReg": true,
                                "cmdRegRd": "0x65",
                                "cmdRegWr": "0x71",
                                "cfgReg": "0x00800006",
                                "shift": 0,
                                "mask": "0x00",
                                "bitP": 0
                        },
                        "strDtrCfg": {
                                "isAddrReg": true,
                                "cmdRegRd": "0x65",
                                "cmdRegWr": "0x71",
                                "cfgReg": "0x00800006",
                                "shift": 1,
                                "mask": "0x00",
                                "bitP": 1
                        }
                },
                "pCustom": {
                        "fxn": null
                }
        },
        "addrByteSupport": "1",
        "fourByteAddrEnSeq": "0xA0",
        "cmdExtType": "REPEAT",
        "resetType": "0x10",
        "deviceBusyType": "1",
        "cmdWren": "0x06",
        "cmdRdsr": "0x05",
        "srWip":  0,
        "srWel":  1,
        "cmdChipErase": "0xC7",
        "rdIdSettings": {
                "cmd": "0x9F",
                "numBytes": 5,
                "dummy4": 0,
                "dummy8": 0
        },
        "xspiWipRdCmd": "0x65",
        "xspiWipReg": "0x00800000",
        "xspiWipBit": 0,
        "flashDeviceBusyTimeout": 256000000,
        "flashPageProgTimeout": 512
}

All tests have passed!!
\endcode
\endcond