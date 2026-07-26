---
orphan: true
---

#  EVM Setup

## AM62L-EVM

### Cable Connections
- The figure below shows some important cable connections, ports and switches.
  - Take note of the location of the "BOOTMODE" switch, this is used to
    switch between different boot modes like USB-DFU, OSPI, UART, SD, NOBOOT mode

![{{ VAR_BOARD_NAME }}](../images/am62lx/evm_overview.png)

### Setup UART Terminal
- Many examples use a standard UART terminal to log the output from the examples.
  You can use any UART terminal program for the same. Below steps show how to setup
  the UART terminal from CCS.

- First identify the UART port as enumerated on the host machine.

  - Make sure that the EVM and UART cable connected as shown in [Cable Connections](am62lx_evm_setup.md)

  - In linux, if you can see `/dev/ttyUSB*` directories, those are the UART ports.

- `Main UART 0` which corresponds to `/dev/ttyUSB0` is the port where UART logs of the application come.
- To open `Main UART 0`, enter the following command on the terminal:
```
        picocom -b 115200 -s "sx -vv" /dev/ttyUSB0
```

- Keep other options to default, i.e 115200 baud rate - 8 data bits - No parity - 1 stop bit,

  - We use the 1st USB serial port for below in the SDK
    - FreeRTOS application terminal
  - We use the 3rd USB serial port, which is the wakeup UART, as logs from the security firmware (TIFS M4).

![Connect to UART port](../images/am62lx/uart_picocom.png)

  - One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking.

## Additional Details

:::{note}
This section has more details on {{ VAR_BOARD_NAME }}. This is mainly for reference and can be skipped unless referred to by
other pages in this user guide.
:::

### BOOT MODE

#### USB-DFU BOOT MODE
This mode is used to send files to the board via USB-DFU. It is used to boot applications via USB-DFU.
```
    BOOTMODE [ 8 : 15 ] (SW4) = 1100 1010
    BOOTMODE [ 4 :  7 ] (SW3) = 0000
    BOOTMODE [ 0 :  3 ] (SW2) = 0000
```
![USB-DFU BOOT MODE](../images/am62lx/boot_pins_usb-dfu_boot_mode.png)

### Troubleshooting EVM issues
 - JTAG connection fails on some EVMs with the following error. Need to connect the JTAG cable after board is powered on.

![JTAG Connection Error Dialog](../images/am62lx/jtag_connection_error.PNG)
