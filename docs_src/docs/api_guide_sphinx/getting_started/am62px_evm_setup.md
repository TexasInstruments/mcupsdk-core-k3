#  EVM Setup

## SK-AM62P-LP

:::{admonition} Note
Refer to EVM page for more details on the EVM, https://www.ti.com/tool/SK-AM62P-LP
:::


### Cable Connections
- The figure below shows some important cable connections, ports and switches.
  - Take note of the location of the "BOOTMODE" switch, this is used to
    switch between different boot modes like OSPI, UART, SD, NOBOOT mode


  ![EVM Board](../images/am62px/evm_overview.png)

### Setup UART Terminal
:::{admonition} Attention
Remove the shunt from the Jumper J10 for the MCU UART to work.
:::


- Many examples use a standard UART terminal to log the output from the examples.
  You can use any UART terminal program for the same. Below steps show how to setup
  the UART terminal from CCS.

- First identify the UART port as enumerated on the host machine.

  - Make sure that the EVM and UART cable connected as shown in [Cable Connections](am62px_evm_setup.md)

  - In windows, you can use the "Device Manager" to see the detected UART ports
    - Search "Device Manager" in Windows Search Box in the Windows taskbar.

  - If dont see any USB serial ports listed in "Device Manager" under "Ports (COM & LPT)",
    then make sure you have installed the UART to USB driver from FTDI, https://www.ftdichip.com/FTDrivers.htm.


    ![Identify UART Port in Windows Device Manager](../images/am62px/ccs_uart_identify.png)
- In CCS, goto "View > Console > Serial Console"


    ![UART Terminal Menu](../images/ccs_uart/ccs_uart_00.png)
- Open a new UART terminal


    ![Open New UART Terminal](../images/ccs_uart/ccs_uart_01.png)
- Select the UART port, keep other options to default, i.e 115200 baud rate - 8 data bits - No parity - 1 stop bit,

  - We use the 1st USB serial port, as seen in the device manager, for below in the SDK
    - Flashing application via UART
    - Booting application via UART
    - Uboot and Linux terminal
  - We use the 3rd USB serial port, as seen in the device manager, as terminal output for examples which run from DM R5F (WKUP R5F)

  - We use the 4th USB serial port, as seen in the device manager, as terminal output for examples which run from MCU R5F


      ![Connect to UART port](../images/am62px/ccs_uart_02.png)
  - In this screenshot this happens to be COM27 and COM30. However on your machine this could be different.
    One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking in device manager.


## Flash SOC Initialization Binary
:::{admonition} Attention
- This is a recommended one time step that needs to be done before you can load and run programs via CCS.
- This step needs to be done once unless the OSPI flash has been erased or some other application has been flashed.
- If this step fails, maybe due to bad flash in EVM, then try one of the other SOC initialization steps mentioned at [SOC Initialization](am62px_evm_setup.md).
:::


- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in [Setup UART Terminal](am62px_evm_setup.md)
  - Make sure python3 is installed as mentioned in [Python3](download_and_install.md)
  - Make sure you have the EVM power cable and UART cable connected as shown in [Cable Connections](am62px_evm_setup.md)

- Build all the binaries from the mcu_plus_sdk installation path.
   - For Linux

           make -sj4 all
   - For Windows

           gmake -sj4 all

- **POWER-OFF** the EVM

- Set boot mode to UART BOOTMODE as shown in below image


  ![UART BOOT MODE](../images/am62px/boot_pins_uart_boot_mode.png)
- **POWER-ON** the EVM

- You should see character "C" getting printed on the UART terminal every 2-3 seconds as shown below


  ![UART output in UART BOOT MODE](../images/am62px/uart_rom_boot.png)
- Close the UART terminal as shown below. This is important, else the UART script in next step wont be able to connect to the UART port.


  ![Close UART terminal](../images/am62px/ccs_uart_close.png)

:::{admonition} Note
For HS-FS device, use default_sbl_null_hs_fs.cfg as the cfg file.
:::


- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_null_hs_fs.cfg

  - Here COM<x> is the port name of the identified UART port in Windows.
  - On Linux,
    - The name for UART port is typically something like `/dev/ttyUSB0`
    - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress you will see something like below


  ![Flash in progress](../images/am62px/flash_soc_init_in_progress.png)
- After all the flashing is done, you will see something like below


```none
Parsing config file ...
Parsing config file ... SUCCESS. Found 5 command(s) !!!

Executing command 1 of 5 ...
Found flash writer ... sending sbl_prebuilt/am62px-sk/sbl_uart_uniflash_stage1.release.tiimage
Sent flashwriter sbl_prebuilt/am62px-sk/sbl_uart_uniflash_stage1.release.tiimage of size 285896 bytes in 27.66s.

Executing command 2 of 5 ...
Command arguments : --file=../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.debug.appimage --operation=flash --flash-offset=0x0
Sending ../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.debug.appimage

Sent ../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.debug.appimage of size 154700 bytes in 16.12s.
[STATUS] SUCCESS !!!

Executing command 3 of 5 ...
Command arguments :  --operation=flash-phy-tuning-data
Sent flash phy tuning data in 3.13s.
[STATUS] SUCCESS !!!

Executing command 4 of 5 ...
Command arguments :  --file=../../examples/drivers/boot/sbl_null/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_null.release.tiimage --operation=flash --flash-offset=0x0
Sending ../../examples/drivers/boot/sbl_null/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_null.release.tiimage

Sent ../../examples/drivers/boot/sbl_null/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang/sbl_null.release.tiimage of size 323400 bytes in 33.34s.
[STATUS] SUCCESS !!!

Executing command 5 of 5 ...
Command arguments : --file=../../examples/drivers/sciclient/sciclient_get_version/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sciclient_get_version.release.appimage --operation=flash --flash-offset=0xC0000
Sending ../../examples/drivers/sciclient/sciclient_get_version/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sciclient_get_version.release.appimage

Sent ../../examples/drivers/sciclient/sciclient_get_version/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sciclient_get_version.release.appimage of size 123616 bytes in 14.62s.
[STATUS] SUCCESS !!!

All commands from config file are executed !!!

```
- If flashing has failed, see [Flash tool error messages and solutions](../components/tools/tools_flash.md), and resolve the errors.

- If flashing is successful, do the next steps ...

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NOR mode as shown below,


  ![OSPI NOR BOOT MODE](../images/am62px/boot_pins_ospi_mode.png)

- Re-connect the UART terminal in CCS window as shown in [Setup UART Terminal](am62px_evm_setup.md)

- **POWER-ON** the EVM

- You should see output like below on the UART terminal

        Starting NULL Bootloader ...

        SYSFW Version 9.0.6--w09.00.04-am62p (Kool Ko
        SYSFW revision 0x9
        DMSC ABI revision 3.1

        INFO: Bootloader_runCpu:162: CPU mcu-r5f is initialized to 800000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a530-0 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a530-1 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a531-0 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a531-1 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_loadSelfCpu:215: CPU wkup-r5f  is initialized to 800000000 Hz !!!


- Congratulations now the EVM is setup for loading and running from CCS !!!
- You dont need to do these steps again unless you have flashed some other binary to the flash.
- Now you can build a example of interest (see [Build a Hello World example](getting_started_build.md)) and then run it (see [CCS Launch, Load and Run](ccs_launch.md))

:::{admonition} Attention
If SBL NULL is used for development, GEL files aren't required for MCU-R5FSS0-0
:::


## Additional Details

:::{admonition} Note
This section has more details on {{ VAR_BOARD_NAME }}. This is mainly for reference and can be skipped unless referred to by other pages in this user guide.
:::

### SOC Initialization

Before any program can be loaded and run on the EVM, the SOC needs to be initialized. Below sections describes the various options available for SOC initialization.


#### SOC Initialization Using SPL
- Prepare a SD card with Linux image by following the [Processor SDK Linux - Create SD card](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Overview/Processor_SDK_Linux_create_SD_card.html) page.

- **POWER-OFF** the EVM

- Make sure below cables are connected as shown in [Cable Connections](am62px_evm_setup.md)
  - Power cable
  - JTAG cable
  - UART cable

- Set EVM in SDCARD BOOT mode as shown below

  ![SD CARD BOOT MODE](../images/am62px/boot_pins_sd_card_boot_mode.png)
- Insert the prepared SD card on the SD card slot.

- Setup UART terminals for Uboot/Linux and the MCU R5 console as per [Setup UART Terminal](am62px_evm_setup.md) section.

- **POWER-ON** the EVM

- Uboot and Linux should come-up on the UART terminal.

- While Linux is booting, the remoteproc should start MCU R5 as shown below.
```none
[    9.276880] platform 79000000.r5f: configured R5F for remoteproc mode
[    9.544692] platform 79000000.r5f: assigned reserved memory node r5f-dma-memory@9b800000
[    9.551482] random: systemd: uninitialized urandom read (16 bytes read)
[    9.598523] remoteproc remoteproc1: 79000000.r5f is available
[    9.671824] remoteproc remoteproc1: powering up 79000000.r5f
[    9.677585] remoteproc remoteproc1: Booting fw image am62p-mcu-r5f0_0-fw, size 93468
[   10.123496] virtio_rpmsg_bus virtio1: rpmsg host is online
[   10.124434] virtio_rpmsg_bus virtio1: creating channel ti.ipc4.ping-pong addr 0xd
[   10.175580]  remoteproc1#vdev0buffer: registered virtio2 (type 7)
[   10.185823] remoteproc remoteproc1: remote processor 79000000.r5f is now up
[   10.443139] virtio_rpmsg_bus virtio2: creating channel ti.ipc4.ping-pong addr 0xd
[   10.450979] virtio_rpmsg_bus virtio2: creating channel rpmsg_chrdev addr 0xe
```
- Setting up the board for Linux boot requires to be done only once with the EVM. But after every power cycle of the board, we need to wait for the linux to come up before loading binaries to AM62P MCU R5 through CCS.


### BOOT MODE

#### UART BOOT MODE
This mode is used to flash files to the board flash via UART. It can also be used to boot applications via UART.

        BOOTMODE [ 8 : 15 ] (SW5) = 0000 0000
        BOOTMODE [ 0 :  7 ] (SW4) = 1101 1100

  ![UART BOOT MODE](../images/am62px/boot_pins_uart_boot_mode.png)

#### OSPI NOR BOOT MODE
This mode is used to boot flashed applications via EVM flash like OSPI NOR flash

        BOOTMODE [ 8 : 15 ] (SW5) = 0100 0000
        BOOTMODE [ 0 :  7 ] (SW4) = 1100 1110

  ![OSPI NOR BOOT MODE](../images/am62px/boot_pins_ospi_mode.png)

#### OSPI SERIAL NAND BOOT MODE
This mode is used to boot flashed applications via EVM flash like OSPI Serial NAND flash

        BOOTMODE [ 8 : 15 ] (SW5) = 0000 0000
        BOOTMODE [ 0 :  7 ] (SW4) = 1100 0000

  ![OSPI NAND BOOT MODE](../images/am62px/boot_pins_ospi_nand_mode.png)

#### SD BOOT MODE
This mode is used to boot applications via SD card on the EVM.

        BOOTMODE [ 8 : 15 ] (SW5) = 0100 0000
        BOOTMODE [ 0 :  7 ] (SW4) = 1100 0010

  ![SD CARD BOOT MODE](../images/am62px/boot_pins_sd_card_boot_mode.png)

#### EMMC BOOT MODE
This mode is used to boot applications via eMMC on the EVM.
        BOOTMODE [ 8 : 15 ] (SW5) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW4) = 1101 0011
    

  ![EMMC BOOT MODE](../images/am62px/boot_pins_emmc_mode.png)
### Troubleshooting EVM issues
 - JTAG connection fails on some EVMs with the following error. Need to connect the JTAG cable after board is powered on.


  ![JTAG Connection Error Dialog](../images/am62px/jtag_connection_error.PNG)
