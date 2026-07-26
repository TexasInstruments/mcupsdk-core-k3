#  EVM Setup

## AM275-EVM

:::{note}
Refer to EVM page for more details on the EVM, TBD
:::

### Cable Connections
The figure below shows some important cable connections, ports and switches.
  - Take note of the location of the "BOOTMODE" switch, this is used to
    switch between different boot modes like OSPI, UART, eMMC, SD, NOBOOT mode

:::{attention}
Dip Switch (SW9) - MMC0_SEL needs to be selected to switch the interface between eMMC and SD
MMC0_SELECT         | Interface
------------------  |--------------------
OFF                 | eMMC
ON                  | SD
This switch also needs to selected alongside bootmedia switch to select the bootmedia between SD & eMMC
:::

![{{ VAR_BOARD_NAME }}](../images/am275x/evm_overview.png)

### Setup UART Terminal
:::{attention}
Both JTAG and UART0 is enumerated to same USB port - J17
:::
:::{attention}
UART2, UART3 and WKUP_UART0 is available from USB port - J22
:::

- Many examples use a standard UART terminal to log the output from the examples.
  You can use any UART terminal program for the same. Below steps show how to setup
  the UART terminal from CCS.

- First identify the UART port as enumerated on the host machine.

  - Make sure that the EVM and UART cable connected as shown in EVM_CABLES

  - In windows, you can use the "Device Manager" to see the detected UART ports
    - Search "Device Manager" in Windows Search Box in the Windows taskbar.

  - If dont see any USB serial ports listed in "Device Manager" under "Ports (COM & LPT)",
    then make sure you have installed the UART to USB driver from FTDI, https://www.ftdichip.com/FTDrivers.htm.

![Identify UART Port in Windows Device Manager](../images/am275x/ccs_uart_identify.png)

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

![Connect to UART port](../images/am275x/ccs_uart_02.png)

  - In this screenshot this happens to be COM27 and COM30. However on your machine this could be different.
    One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking in device manager.


## Flash SOC Initialization Binary
:::{attention}
This is a recommended one time step that needs to be done before
you can load and run programs via CCS
:::

:::{attention}
This step needs to be done once unless the OSPI flash has been erased
or some other application has been flashed
:::

:::{attention}
These steps are not applicable for HS-SE devices as JTAG can not be connected to HS-SE devices by default.
Follow the steps in GETTING_STARTED_FLASH for flashing the HS-SE device.
:::

- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in CCS_UART_TERMINAL
  - Make sure python3 is installed as mentioned in INSTALL_PYTHON3
  - Make sure you have the EVM power cable and UART cable connected as shown in EVM_CABLES

- Build all the binaries from the mcu_plus_sdk installation path.
   - For Linux

           make -sj4 all
   - For Windows

           gmake -sj4 all

- **POWER-OFF** the EVM

- Set boot mode to UART BOOTMODE as shown in below image

![UART BOOT MODE](../images/am275x/boot_pins_uart_boot_mode.png)

- Switch the MMC0_SELECT switch(SW9) to OFF position

![MMC INTERFACE SELECT](../images/am275x/mmc_interface.png)

- **POWER-ON** the EVM

- You should see character "C" getting printed on the UART terminal every 2-3 seconds as shown below

![UART output in UART BOOT MODE](../images/am275x/uart_rom_boot.png)

- Close the UART terminal as shown below. This is important, else the UART script in next step wont be able to connect to the UART port.

![Close UART terminal](../images/am275x/ccs_uart_close.png)

:::{note}
For HS-FS device, use sbl_null_hs_fs.cfg as the cfg file.
:::

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/sbl_null_hs_fs.cfg

  - Here COM<x> is the port name of the identified UART port in Windows.
  - On Linux,
    - The name for UART port is typically something like `/dev/ttyACM0`
    - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress you will see something like below

![Flash in progress](../images/am275x/flash_soc_init_in_progress.png)

- After all the flashing is done, you will see something like below

![Flashing successful](../images/am275x/flash_soc_init_success.png)

- If flashing has failed, see TOOLS_FLASH_ERROR_MESSAGES, and resolve the errors.

- If flashing is successful, do the next steps ...

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NOR mode as shown below,

![OSPI NOR BOOT MODE](../images/am275x/boot_pins_ospi_mode.png)

- Re-connect the UART terminal in CCS window as shown in CCS_UART_TERMINAL

- **POWER-ON** the EVM

- You should see output like below on the UART terminal

        Sciserver Testapp Built On: Nov  6 2024 13:17:23
        Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
        RM_PM_HAL Version: vMM.NN.PP
        Starting Sciserver..... PASSED

        Starting NULL Bootloader ...

        SYSFW Firmware Version 10.0.8--w2024.02-am275x (Fiery
        SYSFW Firmware revision 0xa
        SYSFW ABI revision 4.0

        [KPI] Boot Media       : undefined
        [KPI] Boot Image Size  : 0 KB
        [KPI] Cores present    :
        [KPI] Sciclient Get Version            :      13224us
        [KPI] SBL Total Time Taken             :      13224us






- Congratulations now the EVM is setup for loading and running from CCS !!!
- You dont need to do these steps again unless you have flashed some other binary to the flash.
- Now you can build a example of interest (see GETTING_STARTED_BUILD) and then run it (see CCS_LAUNCH_PAGE)

:::{attention}
If SBL NULL is used for development, GEL files aren't required for R5FSS
:::

### BOOT MODE

#### MMC INTERFACE
Select the MMC interface between eMMC and SD using switch MMC0_SELECT (SW9). This selection also required with bootmedia switch to select the bootmedia between eMMC and SD

 MMC0_SELECT         | Interface
 ------------------  |--------------------
 OFF                 | eMMC
 ON                  | SD

![MMC INTERFACE SELECT](../images/am275x/mmc_interface.png)

#### UART BOOT MODE
This mode is used to flash files to the board flash via UART. It can also be used to boot applications via UART.
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1101 1100
```
![UART BOOT MODE](../images/am275x/boot_pins_uart_boot_mode.png)

#### OSPI NOR BOOT MODE
This mode is used to boot flashed applications via EVM flash like OSPI NOR flash
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1100 1110
```
![OSPI BOOT MODE](../images/am275x/boot_pins_ospi_mode.png)

#### Fast-xSPI BOOT MODE
This mode is used to boot flashed applications via EVM flash like OSPI NOR flash in Fast-xSPI mode
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1101 0110
```
![Fast-xSPI BOOT MODE](../images/am275x/boot_pins_fastxSPI.png)

#### SD BOOT MODE
This mode is used to boot applications via SD card on the EVM.
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1100 0010
```

![SD BOOT MODE](../images/am275x/boot_pins_sd_card_boot_mode.png)

#### NOBOOT MODE
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1101 1111
```

![NO BOOT MODE](../images/am275x/boot_pins_noboot_mode.png)

#### DEVBOOT MODE
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1101 1110
```

![DEV BOOT MODE](../images/am275x/boot_pins_dev_boot_mode.png)

#### EMMC BOOT MODE
This mode is used to boot applications via eMMC on the EVM.
```
    BOOTMODE [ 8 : 15 ] (SW1) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1101 0011
```

![EMMC BOOT MODE](../images/am275x/boot_pins_emmc_mode.png)
### Troubleshooting EVM issues
 - JTAG connection fails on some EVMs with the following error. Need to connect the JTAG cable after board is powered on.

![JTAG Connection Error Dialog](../images/am275x/jtag_connection_error.PNG)
