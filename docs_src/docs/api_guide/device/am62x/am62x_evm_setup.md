#  EVM Setup {#EVM_SETUP_PAGE}

[TOC]

## @VAR_BOARD_NAME / @VAR_SK_LP_BOARD_NAME

\note Refer to EVM page for more details on the SK-AM62, https://www.ti.com/tool/SK-AM62
\note Refer to EVM page for more details on the SK-AM62-LP, https://www.ti.com/tool/SK-AM62-LP
\note Refer to EVM page for more details on the SK-AM62-LP, https://www.ti.com/tool/SK-AM62-SIP

\attention Bootmode settings mentioned in this page are for SK-AM62 E2 and E3 revisions only

### Cable Connections {#EVM_CABLES}

- The figure below shows some important cable connections, ports and switches.
  - Take note of the location of the "BOOTMODE" switch, this is used to
    switch between different boot modes like OSPI, UART, SD, NOBOOT mode

  \imageStyle{evm_overview.png,width:50%}
  \image html evm_overview.png "@VAR_BOARD_NAME"

### Setup UART Terminal {#CCS_UART_TERMINAL}

- Many examples use a standard UART terminal to log the output from the examples.
  You can use any UART terminal program for the same. Below steps show how to setup
  the UART terminal from CCS.

- First identify the UART port as enumerated on the host machine.

  - Make sure that the EVM and UART cable connected as shown in \ref EVM_CABLES

  - In windows, you can use the "Device Manager" to see the detected UART ports
    - Search "Device Manager" in Windows Search Box in the Windows taskbar.

  - If dont see any USB serial ports listed in "Device Manager" under "Ports (COM & LPT)",
    then make sure you have installed the UART to USB driver from FTDI, https://www.ftdichip.com/FTDrivers.htm.

    \imageStyle{ccs_uart_identify.png,width:30%}
    \image html ccs_uart_identify.png "Identify UART Port in Windows Device Manager"

  - In Linux, you can use the " ls /dev/ttyUSB* " to see the detected UART ports, It will results following

    \imageStyle{minicom_uart_ports.png,width:30%}
    \image html minicom_uart_ports.png " UART Port in Linux "

    \imageStyle{minicom_uart_identify.png,width:30%}
    \image html minicom_uart_identify.png "Identify UART Port in Linux "

- In CCS, goto "View > Terminal"

    \imageStyle{ccs_uart_00.png,width:20%}
    \image html ccs_uart_00.png "UART Terminal Menu"

- Open a new UART terminal

    \imageStyle{ccs_uart_01.png,width:50%}
    \image html ccs_uart_01.png "Open New UART Terminal"

- In Windows,
  - Select the UART port, keep other options to default, i.e 115200 baud rate - 8 data bits - No parity - 1 stop bit,

   - We use the 1st USB serial port, as seen in the device manager, for below in the SDK
     - Flashing application via UART
     - Booting application via UART
     - Uboot and Linux terminal
     - Output for examples which run from A53
   - We use the 3rd USB serial port, as seen in the device manager, as terminal output for examples which run from DM R5F (WKUP R5F)

   - We use the 4th USB serial port, as seen in the device manager, as terminal output for examples which run from MCU M4F

      \imageStyle{ccs_uart_02.png,width:25%}
      \image html ccs_uart_02.png "Connect to UART port"

 - In this screenshot this happens to be COM27 and COM30. However on your machine this could be different.One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking in device manager.


 - In Linux,
   - Select the UART port, keep other options to default, i.e 115200 baud rate - 8 data bits - No parity - 1 stop bit,

   - We use the 1st USB serial port, /dev/ttyUSB0, for below in the SDK.
     - Flashing application via UART
     - Booting application via UART
     - Uboot and Linux terminal
     - Output for examples which run from A53
   - We use the 3rd USB serial port, /dev/ttyUSB2, as terminal output for examples which run from DM R5F (WKUP R5F)

   - We use the 4th USB serial port, /dev/ttyUSB3, as terminal output for examples which run from MCU M4F

      \imageStyle{ccs_uart_linux.png,width:25%}
      \image html ccs_uart_linux.png "Connect to UART port"
      \imageStyle{ccs_uart_linux_0.png,width:25%}
      \image html ccs_uart_linux_0.png "UART with Default options"

 - In this screenshot this happens to be /dev/ttyUSB0 and /dev/ttyUSB2. However on your machine this could be different.One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking.


## Flash SOC Initialization Binary {#EVM_FLASH_SOC_INIT}

\attention This is a recommended one time step that needs to be done before
           you can load and run programs via CCS

\attention If this step fails, maybe due to bad flash in EVM, then try one of the other SOC initialization steps
           mentioned at \ref EVM_SOC_INIT

\attention This step needs to be done once unless the OSPI flash has been erased
           or some other application has been flashed

\attention These steps are not applicable for HS-SE devices as JTAG can not be connected to HS-SE devices by default.
           Follow the steps in \ref GETTING_STARTED_FLASH for flashing the HS-SE device.

- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in \ref CCS_UART_TERMINAL
  - Make sure python3 is installed as mentioned in \ref INSTALL_PYTHON3
  - Make sure you have the EVM power cable and UART cable connected as shown in \ref EVM_CABLES

- Build all the binaries from the mcu_plus_sdk installation path.
   - For Linux

           make -sj4 all
   - For Windows

           gmake -sj4 all

- **POWER-OFF** the EVM

- Set boot mode to UART BOOTMODE as shown in below image

  \imageStyle{boot_pins_uart_boot_mode.png,width:30%}
  \image html boot_pins_uart_boot_mode.png "UART BOOT MODE"

- **POWER-ON** the EVM

- You should see character "C" getting printed on the UART terminal every 2-3 seconds as shown below

  \imageStyle{uart_rom_boot.png,width:80%}
  \image html uart_rom_boot.png "UART output in UART BOOT MODE"

- Close the UART terminal as shown below. This is important, else the UART script in next step wont be able to connect to the UART port.

  \imageStyle{ccs_uart_close.png,width:80%}
  \image html ccs_uart_close.png "Close UART terminal"

\note For HS-FS device, use default_sbl_null_hs_fs.cfg as the cfg file.

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.
  - For @VAR_BOARD_NAME

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_null.cfg

  - For @VAR_SK_LP_BOARD_NAME

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_null.cfg

  - For @VAR_SIP_SK_BOARD_NAME

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/@VAR_SIP_SK_BOARD_NAME_LOWER/default_sbl_null_hs_fs.cfg

  - Here COM<x> is the port name of the identified UART port in Windows.
  - On Linux,
    - The name for UART port is typically something like `/dev/ttyUSB0`
    - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress you will see something like below

  \imageStyle{flash_soc_init_in_progress.png,width:80%}
  \image html flash_soc_init_in_progress.png "Flash in progress"

- After all the flashing is done, you will see something like below

  \imageStyle{flash_soc_init_success.png,width:80%}
  \image html flash_soc_init_success.png "Flashing successful"

- If flashing has failed, see \ref TOOLS_FLASH_ERROR_MESSAGES, and resolve the errors.

- If flashing is successful, do the next steps ...

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NOR mode incase of AM62X-SK and AM62X-SIP-SK(or) OSPI NAND incase of AM62X-SK-LP as shown below,
  - For @VAR_BOARD_NAME and @VAR_SIP_SK_BOARD_NAME

    \imageStyle{boot_pins_ospi_mode.png,width:30%}
    \image html boot_pins_ospi_mode.png "OSPI NOR BOOT MODE (AM62X-SK/AM62X-SIP-SK)"

  - For @VAR_SK_LP_BOARD_NAME

    \imageStyle{boot_pins_ospi_nand_mode.png,width:30%}
    \image html boot_pins_ospi_nand_mode.png "OSPI NAND BOOT MODE  (AM62X-SK-LP)"

- Re-connect the UART terminal in CCS window as shown in \ref CCS_UART_TERMINAL

- **POWER-ON** the EVM

- You should see output like below on the UART terminal

        Starting NULL Bootloader ...

        SYSFW Version 8.6.4--v08.06.04 (Chill Capybar
        SYSFW revision 0x8
        DMSC ABI revision 3.1

        INFO: Bootloader_runCpu:155: CPU m4f0-0 is initialized to 400000000 Hz !!!
        INFO: Bootloader_runCpu:155: CPU a530-0 is initialized to 1400000000 Hz !!!
        INFO: Bootloader_runCpu:155: CPU a530-1 is initialized to 1400000000 Hz !!!
        INFO: Bootloader_runCpu:176: CPU a531-0 is initialized to 1400000000 Hz !!!
        INFO: Bootloader_runCpu:176: CPU a531-1 is initialized to 1400000000 Hz !!!
        INFO: Bootloader_loadSelfCpu:208: CPU r5f0-0 is initialized to 400000000 Hz !!!
        INFO: Bootloader_JumpSelfCpu:227: All done, jumping self ...



- Congratulations now the EVM is setup for loading and running from CCS !!!
- You dont need to do these steps again unless you have flashed some other binary to the flash.
- Now you can build a example of interest (see \ref GETTING_STARTED_BUILD) and then run it (see \ref CCS_LAUNCH_PAGE)

\attention If SBL NULL is used for development, GEL files aren't required for M4FSS0-0

## Additional Details

\note This section has more details on @VAR_BOARD_NAME. This is mainly for reference and can be skipped unless referred to by
other pages in this user guide.
### SOC Initialization {#EVM_SOC_INIT}

Before any program can be loaded and run on the EVM, the SOC needs to be initialized.
Below sections describes the various options available for SOC initialization.

#### SOC Initialization Using SPL {#EVM_SOC_INIT_SPL}

- Prepare a SD card with Linux image by following the \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Overview/Processor_SDK_Linux_create_SD_card.html, Processor SDK Linux - Create SD card} page.

- **POWER-OFF** the EVM

- Make sure below cables are connected as shown in \ref EVM_CABLES
  - Power cable
  - JTAG cable
  - UART cable

- Set EVM in SDCARD BOOT mode as shown below
  \imageStyle{boot_pins_sd_card_boot_mode.png,width:30%}
  \image html boot_pins_sd_card_boot_mode.png "SD CARD BOOT MODE"

- Insert the prepared SD card on the SD card slot.

- Setup UART terminals for Uboot/Linux and the M4 console as per \ref CCS_UART_TERMINAL section.

- **POWER-ON** the EVM

- Uboot and Linux should come-up on the UART terminal.

- While Linux is booting, the remoteproc should start M4 as shown below.
\code
[    6.124861] k3-m4-rproc 5000000.m4fss: assigned reserved memory node m4f-dma-memory@9cb00000
[    6.141637] k3-m4-rproc 5000000.m4fss: configured M4 for remoteproc mode
[    6.154843] k3-m4-rproc 5000000.m4fss: local reset is deasserted for device
[    6.170602] remoteproc remoteproc0: 5000000.m4fss is available
[    6.196447] remoteproc remoteproc0: powering up 5000000.m4fss
[    6.202553] remoteproc remoteproc0: Booting fw image am62-mcu-m4f0_0-fw, size 78960
[    6.242673]  remoteproc0#vdev0buffer: assigned reserved memory node m4f-dma-memory@9cb00000
[    6.251498]  remoteproc0#vdev0buffer: registered virtio0 (type 7)
[    6.257790] remoteproc remoteproc0: remote processor 5000000.m4fss is now up
\endcode

- Setting up the board for Linux boot requires to be done only once with the EVM. But after every power cycle of the board, we need to wait for the linux to come up before loading binaries to AM62x M4 through CCS.

### BOOT MODE

#### UART BOOT MODE  {#BOOTMODE_UART}
This mode is used to flash files to the board flash via UART. It can also be used to boot applications via UART.
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1101 1100
    \endcode
  \imageStyle{boot_pins_uart_boot_mode.png,width:30%}
  \image html boot_pins_uart_boot_mode.png "UART BOOT MODE"

#### OSPI NOR BOOT MODE  {#BOOTMODE_OSPI}
This mode is used to boot flashed applications via EVM flash like OSPI NOR flash
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1100 1110
    \endcode
  \imageStyle{boot_pins_ospi_mode.png,width:30%}
  \image html boot_pins_ospi_mode.png "OSPI BOOT MODE"


#### OSPI SERIAL NAND BOOT MODE  {#BOOTMODE_OSPI_NAND}
This mode is used to boot flashed applications via EVM flash like OSPI Serial NAND flash
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1100 0000
    \endcode

  \imageStyle{boot_pins_ospi_nand_mode.png,width:30%}
  \image html boot_pins_ospi_nand_mode.png "OSPI NAND BOOT MODE"
#### SD BOOT MODE  {#BOOTMODE_SD}
This mode is used to boot applications via SD card on the EVM.
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1100 0010
    \endcode

  \imageStyle{boot_pins_sd_card_boot_mode.png,width:30%}
  \image html boot_pins_sd_card_boot_mode.png "SD BOOT MODE"

#### NOBOOT MODE  {#BOOTMODE_NOBOOT}
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1101 1111
    \endcode

  \imageStyle{boot_pins_noboot_mode.png,width:30%}
  \image html boot_pins_noboot_mode.png "NO BOOT MODE"
#### EMMC BOOT MODE  {#BOOTMODE_EMMC}
This mode is used to boot applications via eMMC on the EVM.
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1101 0011
    \endcode

  \imageStyle{boot_pins_emmc_mode.png,width:30%}
  \image html boot_pins_emmc_mode.png "EMMC BOOT MODE"
#### GPMC NAND BOOT MODE  {#BOOTMODE_GPMC_NAND}
This mode is used to boot applications via eMMC on the EVM.
    \code
    BOOTMODE [ 8 : 15 ] (SW2) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW1) = 1101 0011
    \endcode

  \imageStyle{boot_pins_gpmc_nand_mode.png,width:30%}
  \image html boot_pins_gpmc_nand_mode.png "GPMC NAND BOOT MODE"
### Troubleshooting EVM issues {#TROUBLESHOOT_ISSUES}

 - JTAG connection fails on some EVMs with the following error. Need to connect the JTAG cable after board is powered on.

  \imageStyle{jtag_connection_error.PNG,width:30%}
  \image html jtag_connection_error.PNG "JTAG Connection Error Dialog"
