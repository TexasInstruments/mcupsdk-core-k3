# Flashing Tools

## Introduction

Flashing tools allow flashing binaries to the flash on an EVM.

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
- [Snagfactory](#snagfactory)
- [UART Uniflash](#uart-uniflash)
::::

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X
- [UART Uniflash](#uart-uniflash)
- [JTAG Uniflash](#jtag-uniflash)
::::

::::{only} SOC_AM275X or SOC_J722S
- [UART Uniflash](#uart-uniflash)
::::

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
:::{admonition} Note
It is recommended to flash using snagfactory for AM62x, AM62Ax, AM62Px, AM62Dx.
:::
::::


:::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

## Snagfactory

(snagfactory)=

Snagfactory is an open-source tool developed by [Bootlin](https://github.com/bootlin/snagboot) for flashing and recovery using the fastboot protocol over USB. It is based on Snagboot — a fully open-source and vendor-agnostic recovery and flashing tool. It is designed to simplify the process of flashing non-volatile storage devices and recovering target boards during development and production environments.

Snagfactory is composed of two components:
- `Snagrecover` — Loads recovery firmware binaries (tiboot3, tispl, u-boot) to the board over USB DFU, initializes the SOC, and enables Fastboot mode for subsequent flashing.
- `Snagflash` — Flashes binaries to the on-board memory using the Fastboot protocol over USB.


### Important files and folders

<table>
<tr>
    <th>Folder/Files</th>
    <th>Description</th>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/boot/snagfactory/</td></tr>
<tr>
    <td>snagfactory_flash.py</td>
    <td>Main flash utility script. Wraps `snagrecover` and `snagflash` for AM62x family boards. Accepts a `.cfg` file and board name to generate snagflash `.cmd` files and snagrecover YAML files.</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/boot/snagfactory/{board}/</td></tr>
<tr>
    <td>params.yaml</td>
    <td>Per-board configuration file. Defines USB IDs, SOC model, framebuffer settings, recovery firmware paths, and flash targets (`emmc`, `ospi-nor`, `ospi-nand`).</td>
</tr>
<tr>
    <td>{board}_{target}_{sec}.cmd</td>
    <td>Generated snagflash command file. Contains `set target`, `set fb-addr`, `set fb-size`, `set eraseblk-size` (OSPI only), and `flash` commands with offsets and `hwpart` (eMMC only).</td>
</tr>
<tr>
    <td>{board}_{target}_{sec}.yaml</td>
    <td>Generated snagrecover YAML file. Contains board USB ID mapping, SOC firmware paths, and flash task definitions with offsets and partition settings.</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/boot/snagfactory/logs/</td></tr>
<tr>
    <td>flash_{board}_{target}_{timestamp}.log</td>
    <td>Timestamped log file generated per flash run. Contains output from `snagrecover`, `snagflash`, validation results, and error messages.</td>
</tr>
</table>


### Tool requirements on host PC

- The tool is implemented using Python and needs Python version 3.x. Refer to [Python3](../../getting_started/download_and_install.md) to install Python and the required Python packages on your PC.

- `Snagboot` — provides `Snagrecover` and `Snagflash`.
  - Snagfactory tool is hosted here [Snagfactory](https://github.com/bootlin/snagfactory).
  - More info about installation can be found in [Snagfactory Readme](https://github.com/bootlin/snagfactory/blob/main/README.md).
  - Snagfactory is also available on pip.

        $ python3 -m pip install --user snagboot
        $ python3 -m pip install --user snagboot[gui]

### Flash configuration file

(flash-configuration-file)=

- Create a flash configuration file using a default configuration file as reference:

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux_hs_fs.cfg

- In this configuration file, specify only the application binaries to flash with their offsets:

        --file={path to application .appimage.hs_fs} --operation=flash --flash-offset=0x80000

:::{admonition} Note
Recovery binaries (tiboot3, tispl, u-boot) are specified separately in `params.yaml` under the board-specific directory. Snagfactory automatically loads these during the recovery phase via `snagrecover`.
:::

- The `.cfg` file is processed by `snagfactory_flash.py` script which generates:
  - `.cmd` file — Contains Fastboot commands for `snagflash`
  - `.yaml` file — Contains board configuration and USB parameters for `snagrecover`

- These generated files are used directly by the Snagfactory GUI or CLI for flashing.

#### Example .cmd file

The `.cmd` file contains Fastboot commands that `snagflash` executes in sequence:

        set target mmc0
        set fb-addr 0x82000000
        set fb-size 0x7000000

        flash "/path/to/sbl_emmc_linux_stage1.release.hs_fs.tiimage" 0x0 hwpart 1
        flash "/path/to/sbl_emmc_linux_stage2.release.appimage.hs_fs" 0x80000 hwpart 1
        flash "/path/to/hsm.appimage.hs_fs" 0x240000 hwpart 1
        flash "/path/to/hello_world.release.appimage.hs_fs" 0x800000 hwpart 1
        flash "/path/to/linux.appimage.hs_fs" 0x1200000 hwpart 1
        flash "/path/to/u-boot.img" 0x280000 hwpart 1

        exit

#### Example .yaml file

The `.yaml` file contains board configuration and recovery firmware paths for `snagrecover`.

        boards:
          "0451:6165": "<soc-model>"
        soc-models:
          <soc-model>-firmware:
            tiboot3:
              path: <board-directory>/tiboot3.bin
            tispl:
              path: <board-directory>/tispl.bin
            u-boot:
              path: <board-directory>/u-boot.img
          <soc-model>-tasks:
          - target-device: mmc0
            fb-buffer-addr: 0x82000000
            fb-buffer-size: 0x7000000
          - task: reset
          - task: flash
            args:
            - image: /path/to/sbl_emmc_linux_stage1.release.hs_fs.tiimage
              image-offset: 0x0
              part: "hwpart 1"
            - image: /path/to/sbl_emmc_linux_stage2.release.appimage.hs_fs
              image-offset: 0x80000
              part: "hwpart 1"
            - image: /path/to/hsm.appimage.hs_fs
              image-offset: 0x240000
              part: "hwpart 1"
            - image: /path/to/hello_world.release.appimage.hs_fs
              image-offset: 0x800000
              part: "hwpart 1"
            - image: /path/to/linux.appimage.hs_fs
              image-offset: 0x1200000
              part: "hwpart 1"
            - image: /path/to/u-boot.img
              image-offset: 0x280000
              part: "hwpart 1"

### Basic steps to flash files

#### Getting ready to flash

(getting-ready-to-flash)=

- Make sure the required bootloader binaries are built for the EVM. For Snagrecover, bootloader images must support DFU boot and fastboot download.
  In addition to USB DFU fragment config (which enables DFU boot) for the u-boot build, an additional fragment config **am6x_a53_snagfactory.config** needs to be used, which enables fastboot support in U-Boot and other required configs for snagfactory.

  To build bootloader images for recovery using SDK, following change is needed in **Rules.make** file present in the top
  level of Linux SDK Installer.

::::{only} SOC_AM62X

        # For AM62X

        UBOOT_MACHINE_R5=am62x_evm_r5_defconfig am62x_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62x_evm_r5_defconfig am62x_a53_usbdfu.config am6x_a53_snagfactory.config

        # For AM62X LP

        UBOOT_MACHINE_R5=am62x_lpsk_r5_defconfig am62x_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62x_lpsk_a53_defconfig am62x_a53_usbdfu.config am6x_a53_snagfactory.config

        # For AM62X SIP

        UBOOT_MACHINE_R5=am62xsip_evm_r5_defconfig am62x_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62xsip_evm_a53_defconfig am62x_a53_usbdfu.config am6x_a53_snagfactory.config

::::

::::{only} SOC_AM62PX

        UBOOT_MACHINE_R5=am62px_evm_r5_defconfig am62px_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62px_evm_a53_defconfig am62px_a53_usbdfu.config am6x_a53_snagfactory.config

::::

::::{only} SOC_AM62AX

        UBOOT_MACHINE_R5=am62ax_evm_r5_defconfig am62ax_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62ax_evm_a53_defconfig am62ax_a53_usbdfu.config am6x_a53_snagfactory.config

::::

::::{only} SOC_AM62DX

        UBOOT_MACHINE_R5=am62dx_evm_r5_defconfig am62dx_r5_usbdfu.config
        UBOOT_MACHINE_A53=am62dx_evm_a53_defconfig am62dx_a53_usbdfu.config am6x_a53_snagfactory.config

::::

  Generate the bootloader images using top-level makefile by running following commands on the terminal from the
  top-level of the Linux SDK installer.

        $ make u-boot_clean
        $ make u-boot
        $ make u-boot_stage

  Save the bootloader binaries generated in a separate directory. These bootloader images will be used for recovery and
  to start flashing the images. The bootloader images after make can be found in **board-support/built-images**. **Copy** the generated binaries to the board-specific snagfactory directory:

        $ cp board-support/built-images/tiboot3.bin  $(MCU_PLUS_SDK_PATH)/tools/boot/snagfactory/<board>/
        $ cp board-support/built-images/tispl.bin    $(MCU_PLUS_SDK_PATH)/tools/boot/snagfactory/<board>/
        $ cp board-support/built-images/u-boot.img   $(MCU_PLUS_SDK_PATH)/tools/boot/snagfactory/<board>/

  :::{admonition} Note
  **CONFIG_FASTBOOT_BUF_SIZE** is defined in **am6x_a53_snagfactory.config** and specifies the maximum buffer size
  for flashing files. Its value must be equal or greater than the largest file size being flashed. If smaller,
  non-sparse images will not flash correctly due to issues with chunked processing.
  :::

- Make sure you have **Snagfactory** installed on your host machine.

::::{only} SOC_AM62X
- Make sure you have identified the correct **USB DFU** interface on the EVM.

  ![USB DFU BOOT MODE](../../images/am62x/boot_pins_dfu_boot_mode.png)
::::

::::{only} SOC_AM62PX
- Make sure you have identified the correct **USB DFU** interface on the EVM.

  ![USB DFU BOOT MODE](../../images/am62px/boot_pins_dfu_boot_mode.png)
::::

::::{only} SOC_AM62AX
- Make sure you have identified the correct **USB DFU** interface on the EVM.

  ![USB DFU BOOT MODE](../../images/am62ax/boot_pins_dfu_boot_mode.png)
::::

::::{only} SOC_AM62DX
- Make sure you have identified the correct **USB DFU** interface on the EVM.

  ![USB DFU BOOT MODE](../../images/am62dx/boot_pins_dfu_boot_mode.png)
::::

- Create a flash configuration file, refer to the [Flash configuration file](#flash-configuration-file) section for more details.


### Flash tool options

- Type below to see all the possible options with the flashing tool:

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --help


#### Flashing using GUI

- Set EVM in **USB DFU** boot mode (see [Getting ready to flash](#getting-ready-to-flash)) and power on the EVM.

- Run the below command to generate the configuration files (`.cmd` and `.yaml`) required by Snagfactory GUI,
  replacing `<boot-media>` with the appropriate target and `<path-to-edited-cfg-file>` with the path to your
  edited flash configuration file.

::::{only} SOC_AM62X

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62x-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file> --gen-cfg

::::

::::{only} SOC_AM62PX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62px-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file> --gen-cfg

::::

::::{only} SOC_AM62AX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62ax-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file> --gen-cfg

::::

::::{only} SOC_AM62DX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62dx-evm --target <boot-media> --cfg-file <path-to-edited-cfg-file> --gen-cfg

::::


**Step 1: Launch SnagFactory GUI Tool**
- Launch the SnagFactory GUI tool to begin the configuration and device flashing process.

The following steps outline the process for configuring and flashing a device by using the SnagFactory GUI tool.

::::{only} SOC_AM62X
![SnagFactory GUI](../../images/am62x/snagfactory_gui.png)
::::

::::{only} SOC_AM62PX
![SnagFactory GUI](../../images/am62px/snagfactory_gui.png)
::::

::::{only} SOC_AM62AX
![SnagFactory GUI](../../images/am62ax/snagfactory_gui.png)
::::

::::{only} SOC_AM62DX
![SnagFactory GUI](../../images/am62dx/snagfactory_gui.png)
::::

**Step 2: Select Configuration File Option**
- Upon launch, the SnagFactory GUI tool will present the option to add a configuration file.
  Select the **conf** option to proceed with loading the configuration file.

**Step 3: Load YAML Configuration File**
- Load the **Generated YAML configuration file** for the platform. The YAML file follows the naming pattern: `{board}_{target}_{security}.yaml` (e.g., `am62px-sk_emmc_hs_fs.yaml`, `am62x-sk_ospi-nor_hs_fs.yaml`).
- This file contains the platform-specific settings and parameters required for device flashing, including:
  - **Board USB Device Mapping:** Maps the USB device ID (vendor:product code) to the corresponding SOC model name
  - **Recovery Firmware Paths:** Specifies locations of tiboot3.bin, tispl.bin, and u-boot.img for ROM-level bootloader initialization
  - **Flash Target Configuration:** Defines the target storage medium (eMMC, OSPI-NOR, or OSPI-NAND) and its associated parameters
  - **Memory Buffer Settings:** Provides framebuffer address and size for recovery operations
  - **Flash Task Definitions:** Contains detailed flash commands with image file offsets, partition information (hwpart), and execution sequence

::::{only} SOC_AM62X
![](../../images/am62x/snagfactory_load.png)
::::

::::{only} SOC_AM62PX
![](../../images/am62px/snagfactory_load.png)
::::

::::{only} SOC_AM62AX
![](../../images/am62ax/snagfactory_load.png)
::::

::::{only} SOC_AM62DX
![](../../images/am62dx/snagfactory_load.png)
::::

- The board name mapping for the params.yaml file is as follows. This mapping defines the SOC model name used in the generated YAML configuration file for Snagfactory, which must match the board being flashed:

  Evaluation Board | Family | Board
  -----------------|--------|------
  am62pxx-evm      | am6x   | am62p
  am62xx-evm       | am6x   | am625
  am62xx-lp-evm    | am6x   | am625
  am62sip-evm      | am6x   | am625
  am62ax-evm       | am6x   | am62a7
  am62dxx-evm      | am6x   | am62d2

**Step 4: Flash the Device**
- Once you load the generated YAML configuration file (`.yaml` file with format `{board}_{target}_{security}.yaml`), the SnagFactory GUI tool will execute the flashing sequence.
- The tool automatically runs `snagrecover` to load recovery firmware and then `snagflash` to flash application images at their specified offsets.
- Monitor the progress display and wait for the flashing to complete successfully.

::::{only} SOC_AM62X
![](../../images/am62x/snagfactory_flash.png)
::::

::::{only} SOC_AM62PX
![](../../images/am62px/snagfactory_flash.png)
::::

::::{only} SOC_AM62AX
![](../../images/am62ax/snagfactory_flash.png)
::::

::::{only} SOC_AM62DX
![](../../images/am62dx/snagfactory_flash.png)
::::

- If flashing fails at any point, check the **Show Logs** option in the GUI for more details.


#### Flashing using CLI

- Set EVM in **USB DFU** boot mode (see [Getting ready to flash](#getting-ready-to-flash)) and power on the EVM.

- If the USB ID has changed, update the `usb-path` parameter in the `params.yaml` file of the
  respective board (it is `null` by default). You can find the correct USB path by running:

        dfu-util -l

- Run the below command to flash the files, replacing `<boot-media>` with the appropriate target and `<path-to-edited-cfg-file>` with the path to your edited flash configuration file.

::::{only} SOC_AM62X

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62x-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file>

::::

::::{only} SOC_AM62PX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62px-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file>

::::

::::{only} SOC_AM62AX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62ax-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file>

::::

::::{only} SOC_AM62DX

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62dx-evm --target <boot-media> --cfg-file <path-to-edited-cfg-file>

::::

- At each step of the flashing you will see success or error messages, including progress as the
  file is being transferred.
- If flashing is not successful, then check the error messages and take appropriate action
  (See [Error messages and solutions](#error-messages-and-solutions)).
- Detailed logs for each flashing session are also saved to:

        ${SDK_INSTALL_PATH}/tools/boot/snagfactory/logs

  Review the log files in this directory for a full trace of the flashing process, which can be
  helpful for diagnosing failures.

### Error messages and solutions

(error-messages-and-solutions)=

If the tool fails, the error message will give a hint as to why it failed.
Some common error messages, reasons and potential solutions are listed below.

<table>
<tr>
    <th>Error</th>
    <th>Possible Reason</th>
    <th>Solution</th>
</tr>
<tr>
    <td>Unknown board 'BOARD'. Available: [...]</td>
    <td>The board name passed to <code>--board</code> is not defined in <code>BOARD_CONFIGS</code>.</td>
    <td>Check the supported board names using <code>--help</code> and pass a valid <code>--board</code> value.</td>
</tr>
<tr>
    <td>Unknown target 'TARGET' for board 'BOARD'. Available: [...]</td>
    <td>The flash target passed to <code>--target</code> is not defined for the selected board in <code>BOARD_CONFIGS</code>.</td>
    <td>Run the script with <code>--help</code> to see supported targets, or check <code>board_configs.py</code> for valid targets for your board.</td>
</tr>
<tr>
    <td>Config generation failed: ...</td>
    <td><code>generate_cmd()</code> raised a <code>ValueError</code> or <code>FileNotFoundError</code> — either a bad configuration or a missing input file.</td>
    <td>Check the error detail printed below the message. Verify board config entries and ensure all referenced files exist.</td>
</tr>
<tr>
    <td>snagrecover not found in PATH. Is snagboot installed?</td>
    <td>The <code>snagrecover</code> utility is not installed or not available in the system PATH.</td>
    <td>Install snagboot using: <code>pip install snagboot</code></td>
</tr>
<tr>
    <td>Recovery firmware not found: FILE_PATH</td>
    <td>One or more recovery firmware binaries defined in <code>board_configs.py</code> under <code>recovery_fw</code> are missing from the Processor SDK path.</td>
    <td>Verify the <code>--proc-sdk-path</code> argument points to a valid Processor SDK installation and that all recovery firmware binaries are present at the expected paths.</td>
</tr>
<tr>
    <td>snagrecover failed (exit code CODE). Aborting.</td>
    <td>The <code>snagrecover</code> tool exited with a non-zero return code during ROM-level firmware upload over USB DFU.</td>
    <td>Check USB connection and ensure the board is powered on in <code>BOOTMODE_USB_DFU</code> mode. Verify that the recovery firmware binaries are correct for the SOC and Processor SDK version.</td>
</tr>
<tr>
    <td>snagflash not found in PATH. Is snagboot installed?</td>
    <td>The <code>snagflash</code> utility is not installed or not available in the system PATH.</td>
    <td>Install snagboot using: <code>pip install snagboot</code></td>
</tr>
<tr>
    <td>snagflash failed (exit code CODE).</td>
    <td>The <code>snagflash</code> tool exited with a non-zero return code during Fastboot image flashing.</td>
    <td>Review the generated <code>.cmd</code> file under the <code>configs/</code> directory. Verify flash offsets and image paths are correct, and ensure the board enumerated successfully as a Fastboot device after <code>snagrecover</code> completed.</td>
</tr>
<tr>
    <td>eMMC target requires a GPT image.</td>
    <td>The <code>--target emmc</code> was selected but no <code>--gpt-image</code> argument was provided.</td>
    <td>Generate a GPT binary and pass it using <code>--gpt-image /path/to/gpt.bin</code>. Refer to the error output for the exact <code>sgdisk</code> and <code>dd</code> commands to generate the GPT image.</td>
</tr>
<tr>
    <td>SDK path not found: PATH</td>
    <td>The path passed to <code>--sdk-path</code> does not exist on the host machine.</td>
    <td>Verify the MCU+ SDK installation path and pass the correct value to <code>--sdk-path</code>.</td>
</tr>
<tr>
    <td>Processor SDK path not found: PATH</td>
    <td>The path passed to <code>--proc-sdk-path</code> does not exist on the host machine.</td>
    <td>Verify the TI Processor SDK installation path and pass the correct value to <code>--proc-sdk-path</code>.</td>
</tr>
</table>

### Detailed sequence of steps that happen when flashing files

:::{admonition} Note
This section has more detailed sequence of steps that happen underneath the tool and on the EVM for reference.
:::

- Set EVM in **USB DFU** boot mode (see [Getting ready to flash](#getting-ready-to-flash)) and power on the EVM.
- The host PC runs `snagrecover`, which loads the recovery firmware binaries over USB DFU.
- U-Boot initializes and enumerates the board as a **USB Fastboot device** on the host PC.
- The host PC detects the Fastboot device and runs `snagflash`, which sends one or more of the
  below commands with the file data, one after the other, until it is done:
    - Flash a file at a given offset in the flash memory
    - Verify a previously flashed file at a given offset in the flash memory
    - Erase a region of flash memory
- The flashing application does not care what the file contains — it will simply flash it at
  the user specified location.
- On successful completion, the tool logs `Flash complete!` and exits. If any step fails,
  an error message is logged with the exit code and the script exits immediately
  (See [Error messages and solutions](#error-messages-and-solutions)).

:::::

## UART Uniflash

(uart-uniflash)=

   UART is used as the transport or interface to send the file to flash to the EVM.

   ### Tool requirements on host PC

   - The tool is implemented using python and needs python version 3.x
   - The tool uses additional python packages as listed below.
     - pyserial for UART access on PC
     - xmodem for the file transfer protocol
     - tqdm for progress bar when the tool is run
   - Refer to the page, [Python3](../../getting_started/download_and_install.md) , to install python and the required python packages on your PC.

   ### Important files and folders

   <table>
   <tr>
       <th>Folder/Files
       <th>Description
   </tr>
   <tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/boot/</td></tr>
   <tr>
       <td>uart_uniflash.py
       <td>Flashing tool
   </tr>
   <tr>
       <td>sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}
       <td>Pre-built bootloader images and default flash configuration files for a supported EVM
   </tr>
   <tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/examples/drivers/boot/</td></tr>
   <tr>
       <td>sbl_uart_uniflash
       <td>Flashing application that is run on the EVM to receive files to flash
   </tr>

   ::::{only} SOC_AM64X or SOC_AM243X
      <tr>
          <td>sbl_ospi
          <td>OSPI bootloader application that needs to be flashed at offset 0x0. When in OSPI boot mode, this bootloader application
          will boot the user application file for all the CPUs
      </tr>
   ::::


   ::::{only} SOC_AM263X
      <tr>
          <td>sbl_qspi
          <td>QSPI bootloader application that needs to be flashed at offset 0x0. When in QSPI boot mode, this bootloader application
          will boot the user application file for all the CPUs
      </tr>
   ::::

   <tr>
       <td>sbl_null
       <td>SOC init bootloader application that can be used to init the SOC when working in CCS IDE environment.
   </tr>
   </table>

   ### Basic steps to flash files
   ::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

      #### Getting ready to flash


      ::::{only} SOC_AM64X or SOC_AM243X
         - Make sure the flashing application (`sbl_uart_uniflash`), OSPI bootloader (`sbl_ospi`), and the user application (`*.appimage`) you want to flash is built for the EVM.
           - For every supported EVM pre-built flashing application and OSPI bootloader can be found below

                 {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}
      ::::


      ::::{only} SOC_AM62X
         - Make sure the flashing application (`sbl_uart_uniflash_multistage`), OSPI NAbootloader (`sbl_ospi_linux_multistage`), OSPI NAND bootloader (`sbl_ospi_nand_linux_multistage`), EMMC bootloader (`sbl_emmc_linux_multistage`) and the user application (`*.appimage`) you want to flash is built for the EVM.
           - For every supported EVM pre-built flashing application and OSPI bootloader can be found below

                 {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}
      ::::


      ::::{only} SOC_AM62PX
         - Make sure the flashing application (`sbl_uart_uniflash_multistage`), OSPI bootloader (`sbl_ospi_linux_multistage`), EMMC bootloader (`sbl_emmc_linux_multistage`) and the user application (`*.appimage`) you want to flash is built for the EVM.
           - For every supported EVM pre-built flashing application and OSPI bootloader can be found below

                 {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}
      ::::


      ::::{only} SOC_AM62AX
         - Make sure the flashing application (`sbl_uart_uniflash_multistage`), OSPI NAND bootloader (`sbl_ospi_nand_linux_multistage`), EMMC bootloader (`sbl_emmc_linux_multistage`) and the user application (`*.appimage`) you want to flash is built for the EVM.
           - For every supported EVM pre-built flashing application and OSPI bootloader can be found below

                 {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}
      ::::


      ::::{only} SOC_AM62DX
         - Make sure the flashing application (`sbl_uart_uniflash_multistage`), OSPI bootloader (`sbl_ospi_multistage`), EMMC bootloader (`sbl_emmc_multistage`) and the user application (`*.appimage`) you want to flash is built for the EVM.
           - For every supported EVM pre-built flashing application and OSPI bootloader can be found below

                 {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}
      ::::


        - The flashing application and OSPI bootloader source code can be found at below path

              {SDK_INSTALL_PATH}/examples/drivers/boot

        - If you have modified the flashing or bootloader applications, make sure to rebuild these applications and note the path to the `.tiimage` files
          that are generated as part of the build.

        - To build your application follow the steps mentioned in [Build a Hello World example](../../getting_started/getting_started_build.md) to build the application you want.
          Note the path to the `*.appimage` file that is generated as part of the build.

      - Make sure you have installed python as mention in [Python3](../../getting_started/download_and_install.md)

      ::::{only} SOC_AM62X
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62x_evm_setup.md)
      ::::
      ::::{only} SOC_AM62AX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62ax_evm_setup.md)
      ::::
      ::::{only} SOC_AM62DX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62dx_evm_setup.md)
      ::::
      ::::{only} SOC_AM62PX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62px_evm_setup.md)
      ::::
      ::::{only} SOC_AM275X
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am275x_evm_setup.md)
      ::::
      ::::{only} SOC_AM62LX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62lx_evm_setup.md)
      ::::

      #### Flash configuration file


      ::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X
         - Create a flash configuration file, using the default flash configuration file present at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi.cfg

      ::::


      ::::{only} SOC_AM62X or SOC_AM62PX
         - Create a flash configuration file, using the default flash configuration file present at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux.cfg

         :::{admonition} Note
         For HS-SE device, use default_sbl_ospi_linux_hs.cfg as the cfg file.
         :::

         :::{admonition} Note
         For HS-FS device, use default_sbl_ospi_linux_hs_fs.cfg as the cfg file.
         :::


      ::::


      ::::{only} SOC_AM62AX
         - Create a flash configuration file, using the default flash configuration file present at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux_hs_fs.cfg

         :::{admonition} Note
         For HS-SE device, use default_sbl_ospi_linux_hs.cfg as the cfg file.
         :::

         :::{admonition} Note
         For HS-FS device, use default_sbl_ospi_linux_hs_fs.cfg as the cfg file.
         :::


      ::::


      ::::{only} SOC_AM62DX
         - Create a flash configuration file, using the default flash configuration file present at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_hs_fs.cfg

         :::{admonition} Note
         For HS-SE device, use default_sbl_ospi_hs.cfg as the cfg file.
         :::

         :::{admonition} Note
         For HS-FS device, use default_sbl_ospi_hs_fs.cfg as the cfg file.
         :::


      ::::


      - In this config file, modify the paths to the flashing application and OSPI bootloader, in case you are not using the pre-built applications

              --flash-writer={path to flash application .tiimage}
              --file={path to OSPI bootloader .tiimage} --operation=flash --flash-offset=0x0

      - Edit below line to point to the user application (`.appimage`) file

              --file={path to your application .appimage file} --operation=flash --flash-offset=0x80000

      - Edit below line to point to the user application XIP image (`.appimage_xip`) file. When not using XIP mode, this file input is optional.

              --file={path to your application .appimage_xip file} --operation=flash-xip


      ::::{only} SOC_AM64X

         #### Flash configuration file for flashing to eMMC

         - Create a flash configuration file, check the flash configuration file preset at below as reference

                 ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_emmc_linux/am64x-evm/r5fss0-0_nortos/default_sbl_emmc_linux.cfg

         - The flashing application and the eMMC bootloader needs to be specified in this file as

                 --flash-writer={path to flash application .tiimage}
                 --file={path to eMMC bootloader .tiimage} --operation=flash-emmc --flash-offset=0x0

         - The user application (`.appimage`) file needs to be specified in the configuration file as

                 --file={path to your application .appimage file} --operation=flash-emmc --flash-offset=0x800000

      ::::


      ::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX

         #### Flash configuration file for flashing to eMMC

         - Create a flash configuration file, check the flash configuration file preset at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_emmc_linux.cfg


         :::{admonition} Note
         For HS-SE device, use default_sbl_emmc_linux_hs.cfg as the cfg file.
         :::

         :::{admonition} Note
         For HS-FS device, use default_sbl_emmc_linux_hs_fs.cfg as the cfg file.
         :::


         - The flashing application and the eMMC bootloader needs to be specified in this file as

                 --flash-writer={path to flash application .tiimage}
                 --file={path to eMMC bootloader .tiimage} --operation=flash-emmc --flash-offset=0x0

         - The user application (`.appimage`) file needs to be specified in the configuration file as

                 --file={path to your application .appimage file} --operation=flash-emmc --flash-offset=0x800000

      ::::


      ::::{only} SOC_AM62DX

         #### Flash configuration file for flashing to eMMC

         - Create a flash configuration file, check the flash configuration file preset at below as reference

                 ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_emmc.cfg

         :::{admonition} Note
         For HS-SE device, use default_sbl_emmc_hs.cfg as the cfg file.
         :::

         :::{admonition} Note
         For HS-FS device, use default_sbl_emmc_hs_fs.cfg as the cfg file.
         :::


         - The flashing application and the eMMC bootloader needs to be specified in this file as

                 --flash-writer={path to flash application .tiimage}
                 --file={path to eMMC bootloader .tiimage} --operation=flash-emmc --flash-offset=0x0

         - The user application (`.appimage`) file needs to be specified in the configuration file as

                 --file={path to your application .appimage file} --operation=flash-emmc --flash-offset=0x800000

      ::::

   ::::


   ::::{only} SOC_AM263X or SOC_AM273X or SOC_AWR294X

      **Getting ready to flash**

      - Make sure the flashing application (`sbl_uart_uniflash`), QSPI bootloader (`sbl_qspi`), and the user application (`*.appimage`) you want to flash is built for the EVM.
        - For every supported EVM pre-built flashing application and QSPI bootloader can be found below

              {SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}

        - The flashing application and QSPI bootloader source code can be found at below path

              {SDK_INSTALL_PATH}/examples/drivers/boot

        - If you have modified the flashing or bootloader applications, make sure to rebuild these applications and note the path to the `.tiimage` files
          that are generated as part of the build.

        - To build your application follow the steps mentioned in [Build a Hello World example](../../getting_started/getting_started_build.md) to build the application you want.
          Note the path to the `*.appimage` file that is generated as part of the build.

      - Make sure you have installed python as mention in [Python3](../../getting_started/download_and_install.md)

      ::::{only} SOC_AM62X
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62x_evm_setup.md)
      ::::
      ::::{only} SOC_AM62AX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62ax_evm_setup.md)
      ::::
      ::::{only} SOC_AM62DX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62dx_evm_setup.md)
      ::::
      ::::{only} SOC_AM62PX
      - Make sure you have identified the UART port on the EVM as mentioned in [EVM Setup](../../getting_started/am62px_evm_setup.md)
      ::::

      #### Flash configuration file

      - Create a flash configuration file, using the default flash configuration file present at below as reference

              ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_qspi.cfg

      - In this config file, modify the paths to the flashing application and QSPI bootloader, in case you are not using the pre-built applications

              --flash-writer={path to flash application .tiimage}
              --file={path to QSPI bootloader .tiimage} --operation=flash --flash-offset=0x0

      - Edit below line to point to the user application (`.appimage`) file

              --file={path to your application .appimage file} --operation=flash --flash-offset=0x80000

   ::::


   #### Flashing the files

   ::::{only} SOC_AM62X
   - Set EVM in [UART BOOT MODE](../../getting_started/am62x_evm_setup.md) and power on the EVM
   ::::
   ::::{only} SOC_AM62AX
   - Set EVM in [UART BOOT MODE](../../getting_started/am62ax_evm_setup.md) and power on the EVM
   ::::
   ::::{only} SOC_AM62DX
   - Set EVM in [UART BOOT MODE](../../getting_started/am62dx_evm_setup.md) and power on the EVM
   ::::
   ::::{only} SOC_AM62PX
   - Set EVM in [UART BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM
   ::::
   ::::{only} SOC_AM275X
   - Set EVM in [UART BOOT MODE](../../getting_started/am275x_evm_setup.md) and power on the EVM
   ::::
   ::::{only} SOC_AM62LX
   - Set EVM in [UART BOOT MODE](../../getting_started/am62lx_evm_setup.md) and power on the EVM
   ::::

   - Run below python command on the Windows command prompt (`cmd.exe`) or Linux bash shell to flash the files.

           cd ${SDK_INSTALL_PATH}/tools/boot
           python uart_uniflash.py -p {name of your UART com port} --cfg={path to your edited config file}

   - At each step in the flashing your will see success or error messages, including progress as the file is being transferred.


   ::::{only} SOC_AM243X or SOC_AM64X

      ::::{only} SOC_AM64X
      - If flashing is successful, power OFF the EVM, set the EVM to [OSPI NOR BOOT MODE](../../getting_started/am62x_evm_setup.md) and power ON the EVM to run the flashed application.
      ::::
      ::::{only} SOC_AM243X
      - If flashing is successful, power OFF the EVM, set the EVM to OSPI NOR BOOT MODE and power ON the EVM to run the flashed application.
      ::::
   ::::


   ::::{only} SOC_AM273X or SOC_AWR294X or SOC_AM263X
      - If flashing is successful, power OFF the EVM, set the EVM to `BOOTMODE_QSPI` and power ON the EVM to run the flashed application.
   ::::


   - If flashing is not successful, then check the error messages and take appropriate action (See [Flash tool error messages and solutions](tools_flash.md)).

   #### Flash tool options

   - Type below to see all the possible options with the flashing tool and also see the default .cfg file for syntax and options possible in the config file

           cd ${SDK_INSTALL_PATH}/tools/boot
           python uart_uniflash.py --help

   ### Flash tool error messages and solutions
   If the flashing fails, the error message will give a hint as to why it failed.
   Some common error messages, reasons and potential solutions are listed below.

   <table>
   <tr>
       <th>Error
       <th>Possible Reason
       <th>Solution
   </tr>
   <tr>
       <td> Serial port not found or not accessible
       <td> Wrong UART port passed as argument or the UART port is open in some other terminal application.
       <td> Check the UART port, UART ports are named as <code>COM1</code>, <code>COM2</code>, and so on in Windows and as <code>/dev/ttyUSB0</code>, <code>/dev/ttyUSB1</code>, and so on in Linux.
            Also make sure to close all open UART terminals and try again.
   </tr>
   <tr>
       <td> No response or error response from EVM.
       <td> Either EVM is not in power-ON state or EVM is not setup in UART boot mode.
       <td> Use Ctrl-C to terminate the script if it is stuck. Check UART boot mode switch setting, check power to EVM, power-cycle EVM and try again
   </tr>
   <tr>
       <td> Flashing failed error message
       <td> This should not happen ideally on TI EVMs. On custom EVM this could happen if there is some issue in the flash driver on the EVM.
       <td> Power cycle EVM and try again. If the problem still does not go away, then likely
       the flash on the EVM has gone bad. Try other SOC initialization options and check the flash driver via CCS IDE debug.
   </tr>
   <tr>
       <td> Config file parsing error
       <td> Wrong config file passed or input files not found.
       <td> Check the message that is printed, and edit the config file to fix the parsing errors.
           Make sure to specify file paths with forward slash <code>/</code>, including in Windows.
           The default config file should not have any errors though.
   </tr>
   <tr>
       <td> Python not found error or python packages not not found error
       <td> Python or python packages needed for this script are not installed
       <td> Follow steps mentioned in <a href="../../getting_started/download_and_install.html">Python3</a> to install python and related packages
   </tr>
   <tr>
       <td> Parsing config file error
       <td> SBL binaries are missing from the prebuilt folder
       <td> Build sbl using below command: \n make -s sbl DEVICE={{ VAR_SOC_NAME_LOWER }}
   </tr>
   </table>

   ### Detailed sequence of steps that happen when flashing files

   :::{admonition} Note
   This section has more detailed sequence of steps that happen underneath the tools and on the EVM for reference.
   :::


   The detailed sequence of steps that happen when flashing files is listed below. Refer to the appropriate EVM Setup guide to setup the EVM in different boot modes that are needed for this sequence of steps:
   ::::{only} SOC_AM62X
   [EVM Setup](../../getting_started/am62x_evm_setup.md)
   ::::
   ::::{only} SOC_AM62AX
   [EVM Setup](../../getting_started/am62ax_evm_setup.md)
   ::::
   ::::{only} SOC_AM62DX
   [EVM Setup](../../getting_started/am62dx_evm_setup.md)
   ::::
   ::::{only} SOC_AM62PX
   [EVM Setup](../../getting_started/am62px_evm_setup.md)
   ::::
   ::::{only} SOC_AM275X
   [EVM Setup](../../getting_started/am275x_evm_setup.md)
   ::::
   ::::{only} SOC_AM62LX
   [EVM Setup](../../getting_started/am62lx_evm_setup.md)
   ::::

   - Set EVM in UART boot mode and power it on, the SOC ROM bootloader waits to receive a file using the UART+XMODEM protocol.

   ::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X
      - PC sends the flashing application file (`sbl_uart_uniflash.release.tiimage`) via the flashing tool using UART+XMODEM protocol underneath.
   ::::


   ::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
      - PC sends the flashing application file (`sbl_uart_uniflash_stage1.release.tiimage`) via the flashing tool using UART+XMODEM protocol underneath.
   ::::

   - The ROM bootloader, boots the flashing application
   - The flashing application now initializes the flash on the EVM and waits for additional commands using UART+XMODEM protocol
   - The PC tool can now send one or more of below commands with the file data, one after the other, until it is done.
     - Flash a file at a given offset in the flash
     - Verify a previously flashed file at a given offset in the flash
     - Erase a region of flash memory
   - The flashing application as such does not care what the file contains, it will simply flash it at the user specified location.

   ::::{only} SOC_AM273X or SOC_AWR294X or SOC_AM263X
      - However typically one needs to at least send the below files to flash
        - Send a QSPI flash bootloader application and flash it at offset 0x0 (`sbl_qspi.release.tiimage`). If the QSPI bootloader is
          already flashed previously then this step can be skipped.
        - Send your application image multi-core image and flash it at offset 0x80000 (`*.appimage`).
          The offset 0x80000 is the offset that is specified in the QSPI bootloader and when the EVM boots in QSPI mode, it
          will attempt to find a application at this location.
      - After flashing is done, power OFF the EVM
      - Set EVM in QSPI boot mode and power ON the EVM.
        - The ROM bootloader will now boot the QSPI bootloader by reading offset 0x0
        - And the QSPI bootloader will boot the application by reading from offset 0x80000.
      - The initial flashing application and the subsequent commands to send and flash the QSPI bootloader and application files are all specified
        in a single configuration file which is provided as input to the tool.
   ::::


   ::::{only} SOC_AM243X or SOC_AM64X
      - However typically one needs to at least send the below files to flash
        - Send a OSPI flash bootloader application and flash it at offset 0x0 (`sbl_ospi.release.tiimage`). If the OSPI bootloader is
          already flashed previously then this step can be skipped.
        - Send your application image multi-core image and flash it at offset 0x80000 (`*.appimage`).
          The offset 0x80000 is the offset that is specified in the OSPI bootloader and when the EVM boots in OSPI mode, it
          will attempt to find a application at this location.
      - After flashing is done, power OFF the EVM
      - Set EVM in OSPI boot mode and power ON the EVM.
        - The ROM bootloader will now boot the OSPI bootloader by reading offset 0x0
        - And the OSPI bootloader will boot the application by reading from offset 0x80000.
      - The initial flashing application and the subsequent commands to send and flash the OSPI bootloader and application files are all specified
        in a single configuration file which is provided as input to the tool.
   ::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X
```{rubric} GUI for UART Uniflash (Experimental)
```
      UART Uniflash GUI is a GUI wrapper around the UART Uniflash tool already present (`uart_uniflash.py`). This is a strictly experimental feature with minimal testing from TI side. Can be used if GUI is more comfortable. Since most of the CLI tool is used underneath, it is the same functionality wise

```{rubric} Pre-Requisites for UART Uniflash GUI
```

      This GUI is built on top of the python based UART Uniflash CLI tool already mentioned, and specifically based on the PyQt5 binding of the QT5 framework. So it is expected that python3 and other dependencies (xmodem, pyserial etc) are already installed. In addition to this, one also needs to install the PyQt5 python library for the GUI to work.

      - In windows, you can install PyQt5 by doing below:

        `python -m pip install pyqt5`

      - In Ubuntu (or other Debian based distros) you can install PyQt5 by doing below:

        `sudo apt install python3-pyqt5`

```{rubric} Using the UART Uniflash GUI
```

      The UART Uniflash GUI can be used to flash files arbitrarily into the device flash
![UART Uniflash GUI : Serial Port Selection](../../images/uart_uniflash_gui/uniflash_gui_manual_config_sport.png)

      At the top there is a drop down to select the UART COM port which will be used for flashing. Please connect the target to the EVM before running the GUI so that the serial port we are interested will show up here.

      - For choosing what to flash and how to flash there are two high level choices in UART Uniflash GUI:
        - Manual Config
        - From File

      <table style="border: 0 px">
          <tr>
              <td> <img src="../../images/uart_uniflash_gui/uniflash_gui_manual_config.png" alt="UART Uniflash GUI : Manual Config based flashing"> </td>
              <td> <img src="../../images/uart_uniflash_gui/uniflash_gui_file_config.png" alt="UART Uniflash GUI : Config file based flashing"> </td>
          </tr>
      </table>

      - **Manual Config** : Manual configuration of the files to be flashed. There will be drop down file browse options to select the various files you will need to flash/send to the target. It provides options / slots to select below:

        - **Flash writer binary** : This is the sbl_uart_uniflash binary. This needs to be send first for the ROM to receive and boot. Once this boots up you can send any number of files arbitrarily for flashing.

        - **Bootloader binary** : It is assumed that the eventual goal of the flashing process is to boot your application from the flash device. For this a bootloader capable of reading an image from flash device needs to be flashed at offset 0 (generally) of the flash. This would be the `sbl_ospi` or `sbl_qspi`. Although this is no different than flashing any other file to a particular offset, we have decided to keep it a separate option for better clarity. Although the offset is almost always 0, we have provided an offset edit box as well if there is any change whatsoever.

        - **Appimage binary** : You can select the application image to be flashed from this slot. SDK convention is to flash at a 512 KB offset (0x80000). This can be changed, but keep in mind that the bootloader booting this application should be aware of this offset as well. It is a configurable option in the Sysconfig of the bootloader.

        - **Appimage XIP binary** : You can select the XIP component to your application from this slot. These files will be of the format (`*.appimage_xip`). These files already contain details as to where these need to be flashed, so no need to provide any offset in this case.

        - **Custom data** : This slot can be used to flash any custom data file at an arbitrary offset. Don't forget to provide the offset

        - **Flash PHY tuning data** : In certain NOR SPI drivers, for tuning the PHY, known data needs to be present in the flash. This is a fixed size (usually 128 bytes) array written to the last block of the flash. This check box needs to be ticked if you're flashing for the first time to the target so that this known data can be written to the flash.


        ![UART Uniflash GUI : Saving the manual configuration](../../images/uart_uniflash_gui/uniflash_gui_manual_config_flash_phy_tuning.png)
        - There is an option to save the settings you selected manually as a config file using the **Save CFG** button towards the bottom right of the Manual Config group.
![UART Uniflash GUI : Saving the manual configuration](../../images/uart_uniflash_gui/uniflash_gui_manual_config_save_cfg.png)

      - **From File** : Flash using a configuration file (`*.cfg` extension) specifying what needs to be flashed. This is a convenient option if the files to be flashed are pretty much the same for every try. In fact even in the manual config case, a cfg file is created internally and used for flashing. This `cfg` follows the same format used by the CLI script.

      After selecting the config options and files, just press the **FLASH** button to start the flashing. A progress bar will show the flashing progress.

      There is also a log area which will show detailed logs in addition to the pop up messages.
![UART Uniflash GUI : LOGS](../../images/uart_uniflash_gui/uniflash_gui_manual_config_log_area.png)


```{rubric} Important Notes and Common Pitfalls in UART Uniflash GUI
```

      - Make sure that the target device is powered ON and is in UART boot mode before attempting to flash
      - Make sure that the correct COM port is selected from the drop down. If the wrong port is selected, the flasher might take time to exit out as it will wait for the device to send the XMODEM control character.
      - If the GUI seems to hang, re-check the selected COM port and make sure the EVM is **powered ON** and in **UART boot mode**
      - The GUI is based on the `uart_uniflash.py` CLI script, and reuses a lot of objects and functions, so core functionality is the same among both.
      - In manual config case, if a drop down is non blank it is assumed that the file provided there needs to be flashed. So it will be picked up and used when `FLASH` button is clicked. If this is not required, make sure to delete it and keep it blank, the drop down is editable. This is true for the config file drop down as well, but the mishap is more probable in manual config case.
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X
```{rubric} JTAG Uniflash
```
      JTAG is used as the transport or interface to send the file to flash to the EVM.

```{rubric} Important files and folders
```

      <table>
      <tr>
          <th>Folder/Files
          <th>Description
      </tr>
      <tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/examples/drivers/boot/</td></tr>
      <tr>
          <td>sbl_jtag_uniflash
          <td> Flash-writer example which uses JTAG to write files or erase flash
      </tr>

      </table>

```{rubric} Basic steps to flash files
```

      Refer the example `EXAMPLES_DRIVERS_SBL_JTAG_UNIFLASH`
::::
