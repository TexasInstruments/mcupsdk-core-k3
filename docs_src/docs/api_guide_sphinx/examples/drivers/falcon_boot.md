# Falcon Boot Support
## Introduction

- In falcon boot mode, the device bypasses the A-core SPL and U-Boot stage, allowing for direct booting to the Linux kernel after OP-TEE and ATF.

- With Falcon Boot, devices can achieve fast boot times, making it an ideal solution for applications where boot times are critical.

## Pre-requisites for falcon boot mode

1) In falcon boot mode, A53 SPL and U-Boot are bypassed, and the boot sequence directly jumps to TF-A, then to the kernel.

2) To achieve faster booting,

    - A minimalistic file system (initramfs) is used.
    - A smaller kernel image is used.
        - It includes relevant drivers.
        - The boot messages are suppressed.
    - A Device tree blob from Processor SDK is used.

## How to obtain the kernel images and Initramfs

- Build the fastboot binaries(kernel image/initramfs) as per the documentation:


::::{only} SOC_AM62X
   - Refer to [**Processor SDK Linux - Developer Notes**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides_Developer_Notes.html) guide to optimize the time taken by bootloader in the boot sequence.
::::


::::{only} SOC_AM62AX
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html)  guide to optimize the time taken by bootloader in the boot sequence.
::::


::::{only} SOC_AM62PX
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html)  guide to optimize the time taken by bootloader in the boot sequence.
::::


## How to obtain the DTB, RTOS and linux Appimages

## Loading ATF at the Correct Location

- The Device Tree Binary (DTB) provided by the Processor SDK specifies the load address of the Arm Trust Firmware (ATF) as 0x9e780000.
- The U-Boot device tree fix-ups load the ATF at 0x80000000.
- In Falcon mode, the U-Boot is removed, and the MCU+SDK uses the default DTB from the Processor SDK to generate Falcon images.
- This may cause the ATF to be loaded at the location specified by the default DTB (0x9e780000).
- To load the ATF at the correct location, an overlay must be applied to load the ATF at 0x80000000.


### Device-Specific Overlay


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX
   - For AM62A, AM62P, AM62X-SK-LP, and AM62X-SK devices:
     - The overlay is applied to load the ATF at 0x80000000.
     - The overlay code is:

         ```
         /dts-v1/;
         /plugin/;

         / {
             #address-cells = <0x02>;
             #size-cells = <0x02>;
             fragment@0 {
                 #address-cells = <0x02>;
                 #size-cells = <0x02>;
                 ranges;
                 target-path = "/reserved-memory/tfa@9e780000";
                 __overlay__ {
                     #address-cells = <0x02>;
                     #size-cells = <0x02>;
                     ranges;
                     reg = <0x00 0x80000000 0x00 0x80000>;
                 };
             };
         };
         ```
::::


::::{only} SOC_AM62X
   - For the AM62SIP device:
     - Both the ATF and OPTEE load addresses change.
     - The overlay is applied to load the ATF at 0x80000000 and OPTEE at 0x80080000.
     - The overlay code is:

         ```
         /dts-v1/;
         /plugin/;

         / {
             #address-cells = <0x02>;
             #size-cells = <0x02>;
             fragment@0 {
                 #address-cells = <0x02>;
                 #size-cells = <0x02>;
                 ranges;
                 target-path = "/reserved-memory/tfa@9e780000";
                 __overlay__ {
                     #address-cells = <0x02>;
                     #size-cells = <0x02>;
                     ranges;
                     reg = <0x00 0x80000000 0x00 0x80000>;
                 };
             };
             fragment@1 {
                 #address-cells = <0x02>;
                 #size-cells = <0x02>;
                 ranges;
                 target-path = "/reserved-memory/optee@9e800000";
                 __overlay__ {
                     #address-cells = <0x02>;
                     #size-cells = <0x02>;
                     ranges;
                     reg = <0x00 0x80080000 0x00 0x01800000>;
                 };
             };
         };
         ```
:::::


### Generating a New DTBO File

To generate a new DTBO file, use the following command:
```
dtc -I dts -O dtb -o output-filename.dtbo input-filename.dtsi
```
For example:
```
dtc -I dts -O dtb -o tfa-overlay.dtbo tfa-overlay.dtsi
```
This command generates a new DTBO file called tfa-overlay.dtbo from the tfa-overlay.dtsi file.

### Applying the Overlay

To apply the overlay, use the following command:

:::{admonition} Attention
Please modify the input/output filenames and path appropriately.
:::


```
fdtoverlay -i path-to-actual.dtb-used -o path-to-new-overlay.dtb path-to-obtained.dtbo
```
For example:


::::{only} SOC_AM62AX
      fdtoverlay -i <path-to-processor-sdk>/board-support/prebuilt-images/am62a-evm/k3-am62a7-sk.dtb -o <path-to-processor-sdk>/board-support/prebuilt-images/am62a-evm/k3-am62a7-sk-overlay.dtb tfa-overlay.dtbo
   ::::


::::{only} SOC_AM62PX
      fdtoverlay -i <path-to-processor-sdk>/board-support/prebuilt-images/am62pxx-evm/k3-am62p5.dtb -o <path-to-processor-sdk>/board-support/prebuilt-images/am62pxx-evm/k3-am62p5-sk-overlay.dtb tfa-overlay.dtbo
   ::::


::::{only} SOC_AM62X

   - For AM62X:
      fdtoverlay -i <path-to-processor-sdk>/board-support/prebuilt-images/am62xx-evm/k3-am625-sk.dtb -o <path-to-processor-sdk>/board-support/prebuilt-images/am62xx-evm/k3-am625-sk-overlay.dtb tfa-overlay.dtbo
   
   - For AM62SIP:
      fdtoverlay -i <path-to-processor-sdk>/board-support/prebuilt-images/am62xxsip-evm/k3-am6254xxl-sk.dtb -o <path-to-processor-sdk>/board-support/prebuilt-images/am62xxsip-evm/k3-am6254xxl-sk-overlay.dtb tfa-overlay.dtbo
   
   - For AM62-SK-LP:
      fdtoverlay -i <path-to-processor-sdk>/board-support/prebuilt-images/am62xx-lp-evm/k3-am62-lp-sk.dtb -o <path-to-processor-sdk>/board-support/prebuilt-images/am62xx-lp-evm/k3-am62-sk-lp-overlay.dtb tfa-overlay.dtbo
   ::::


This command applies the overlay to the default DTB file and generates a new DTB file with the overlay changes.

## Rebuilding ATF


::::{only} SOC_AM62PX
   - Refer to [**Processor SDK Linux - ARM Trusted Firmware-A**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/Foundational_Components_ATF.html) to rebuild ATF inside the ATF source directory:
::::


::::{only} SOC_AM62X
   - Refer to [**Processor SDK Linux - ARM Trusted Firmware-A**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Foundational_Components_ATF.html) to rebuild ATF inside the ATF source directory:
::::


::::{only} SOC_AM62AX
   - Refer to [**Processor SDK Linux - ARM Trusted Firmware-A**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/Foundational_Components_ATF.html) to rebuild ATF inside the ATF source directory:
::::


- Add the PRELOADED_BL33_BASE, K3_HW_CONFIG_BASE and BL32_BASE for respective devices.

  - For example:

- For AM62A, AM62P, AM62X-SK-LP, and AM62X-SK devices:
```
make CROSS_COMPILE=<path-to-compiler>/bin/aarch64-none-elf- ARCH=aarch64 PLAT=k3 TARGET_BOARD=lite SPD=opteed PRELOADED_BL33_BASE=0x82000000 K3_HW_CONFIG_BASE=0x88000000
```
- For AM62SIP device:
```
make CROSS_COMPILE=<path-to-compiler>/bin/aarch64-none-elf- ARCH=aarch64 PLAT=k3 TARGET_BOARD=lite SPD=opteed PRELOADED_BL33_BASE=0x82000000 K3_HW_CONFIG_BASE=0x88000000 BL32_BASE=0x80080000
```
- This command rebuilds ATF with the kernel load address at 0x82000000 and FDT at 0x88000000.


## Building the Fastboot Binaries

Refer to the section "How to obtain the kernel images and Initramfs" to build the fastboot binaries.

## Creating a Linux Falcon Appimage

To create a Linux Falcon Appimage, run the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in the config.mak file.
- Refer [Linux Appimage Generator Tool](../../components/tools/tools_boot.md) for more details

## Loading the Falcon Image

The generated falcon image size ranges up to ~23MB. To load the necessary RTOS appimages and Linux appimage, use the default sbl_emmc_linux_falcon_hs_fs.cfg or default_sbl_ospi_linux_falcon_hs_fs.cfg configuration file, depending on the storage device used. Boot the device using the generated falcon image.

:::{admonition} Note
SBL EMMC Linux boots from the boot partition 0 of eMMC and does not use a filesystem boot. The appimage is flashed to the offsets in eMMC as configured using syscfg.
:::

:::{admonition} Attention
Care should be taken to ensure that the R5, M4 appimage and the Linux appimage flashed does NOT overwrite the Linux binaries in eMMC.
:::

:::{admonition} Note
The load address of resource table for R5 and M4 cores must be consistent with the address in the Linux dts file.
:::


## Running the Example

- To run the example, you can use the SBL images obtained using the SBL EMMC Linux Multistage and SBL OSPI Linux Multistage examples for eMMC and OSPI falcon boot, respectively.

## Refer to the Examples

For more information, refer to the following examples:

- [EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE](sbl_emmc_linux_multistage.md) for eMMC boot
- [SBL OSPI Linux Multistage](sbl_ospi_linux_multistage.md) for OSPI boot

## SBL Images and Flash Config Files

### EMMC

- The above mentioned example is the SBL that needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs, and Linux Appimage.

- The default flash config file for eMMC is located at: ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_linux_hs_fs.cfg

- The eMMC appimage offsets need to be modified to fit within the eMMC boot partition of size 31.5 MB.

- Please refer the following changes to modify the offsets.


::::{only} SOC_AM62AX
   **Syscfg changes**

   - In EMMC Linux stage1:

      ```
      bootloader1.bootMedia          = "EMMC";
      bootloader1.$name              = "CONFIG_BOOTLOADER_EMMC_MCU";
      bootloader1.EMMCAppImageOffset = "0x600000";

      bootloader2.bootMedia          = "EMMC";
      bootloader2.$name              = "CONFIG_BOOTLOADER_EMMC_SBL";
      bootloader2.EMMCAppImageOffset = "0x80000";
      ```

   - In EMMC Linux Stage2:

      ```
      bootloader1.bootMedia          = "EMMC";
      bootloader1.$name              = "CONFIG_BOOTLOADER_EMMC_HSM";
      bootloader1.EMMCAppImageOffset = "0x240000";

      bootloader2.bootMedia          = "EMMC";
      bootloader2.$name              = "CONFIG_BOOTLOADER_EMMC_DM";
      bootloader2.EMMCAppImageOffset = "0xC0000";

      bootloader3.$name              = "CONFIG_BOOTLOADER_EMMC_LINUX";
      bootloader3.bootMedia          = "EMMC";
      bootloader3.EMMCAppImageOffset = "0x800000";

      bootloader4.$name              = "CONFIG_BOOTLOADER_EMMC_DSP";
      bootloader4.bootMedia          = "EMMC";
      bootloader4.EMMCAppImageOffset = "0x700000";
      ```

   **Default sbl_emmc_linux config file changes**

   ```
   --file=sbl_prebuilt/am62ax-sk/sbl_emmc_linux_stage1.release.hs_fs.tiimage --operation=flash-emmc --flash-offset=0x0

   --file=../../examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/am62ax-sk/r5fss0-0_nortos/ti-arm-clang/sbl_emmc_linux_stage2.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x80000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62ax-sk/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0xC0000

   --file=../../tools/boot/HSMAppimageGen/board/am62ax-sk/hsm.appimage.hs_fs --operation=flash-emmc --flash-offset=0x240000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62ax-sk/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x600000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62ax-sk/c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x700000

   --file=../../tools/boot/linuxAppimageGen/board/am62ax-sk/linux.falcon.appimage.hs_fs --operation=flash-emmc --flash-offset=0x800000
   ```
::::


::::{only} SOC_AM62PX
   **Syscfg changes**

   - In EMMC Linux Stage2:

      ```
      bootloader1.$name              = "CONFIG_BOOTLOADER_EMMC_HSM";
      bootloader1.bootMedia          = "EMMC";
      bootloader1.EMMCAppImageOffset = "0x240000";

      bootloader2.$name              = "CONFIG_BOOTLOADER_EMMC_MCU";
      bootloader2.bootMedia          = "EMMC";
      bootloader2.EMMCAppImageOffset = "0x600000";

      bootloader3.$name              = "CONFIG_BOOTLOADER_EMMC_LINUX";
      bootloader3.bootMedia          = "EMMC";
      bootloader3.EMMCAppImageOffset = "0x800000";
      ```

   **Default sbl_emmc_linux config file changes**

   ```
   --file=sbl_prebuilt/am62px-sk/sbl_emmc_linux_stage1.release.hs_fs.tiimage --operation=flash-emmc --flash-offset=0x0

   --file=../../examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sbl_emmc_linux_stage2.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x80000

   --file=HSMAppimageGen/board/am62px-sk/hsm.appimage.hs_fs --operation=flash-emmc --flash-offset=0x240000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62px-sk/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x600000

   --file=linuxAppimageGen/board/am62px-sk/linux.falcon.appimage.hs_fs	 --operation=flash-emmc --flash-offset=0x800000
   ```
::::


::::{only} SOC_AM62X
   **Syscfg changes**

   - In EMMC Linux Stage2:

      ```
      bootloader1.bootMedia          = "EMMC";
      bootloader1.$name              = "CONFIG_BOOTLOADER_EMMC_HSM";
      bootloader1.EMMCAppImageOffset = "0x240000";

      bootloader2.bootMedia          = "EMMC";
      bootloader2.$name              = "CONFIG_BOOTLOADER_EMMC_DM";
      bootloader2.EMMCAppImageOffset = "0x700000";

      bootloader3.$name              = "CONFIG_BOOTLOADER_EMMC_LINUX";
      bootloader3.bootMedia          = "EMMC";
      bootloader3.EMMCAppImageOffset = "0x800000";
      ```

   **Default sbl_emmc_linux config file changes**

   ```
   --file=sbl_prebuilt/am62x-sip-sk/sbl_emmc_linux_stage1.release.hs_fs.tiimage --operation=flash-emmc --flash-offset=0x0

   --file=../../examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/am62x-sip-sk/r5fss0-0_nortos/ti-arm-clang/sbl_emmc_linux_stage2.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x80000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sip-sk/m4fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x100000

   --file=../../tools/boot/HSMAppimageGen/board/am62x-sip-sk/hsm.appimage.hs_fs --operation=flash-emmc --flash-offset=0x240000

   --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sip-sk/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash-emmc --flash-offset=0x700000

   --file=../../tools/boot/linuxAppimageGen/board/am62x-sip-sk/linux.falcon.appimage.hs_fs --operation=flash-emmc --flash-offset=0x800000
   ```
::::


:::{admonition} Note
U-boot image is not required to be flashed as Falcon mode skips U-boot and jumps to kernel directly.
::::


### OSPI

- The above mentioned example is the SBL that needs to be flashed on the OSPI, along with sample application images for R5, M4 CPUs, and Linux Appimage.

- The default flash config file for OSPI is located at: ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_falcon_hs_fs.cfg

:::{admonition} Note
Falcon boot wih OSPI does not require config file or syscfg changes.
:::


## Booting the EVM

- With the required images flashed using the config file, proceed to boot the EVM in either eMMC or OSPI boot mode. This will launch the boot process, resulting in Linux booting on the A53 core and the RTOS or baremetal application booting on the R5 and M4 cores.

## Sample Output

After flashing and booting the EVM, you will see below output on the UART console

### EMMC

```
SYSFW Firmware Version 11.1.5--v11.01.05 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : eMMC
[KPI] Boot Media Clock : 200.000 MHz
[KPI] Boot Image Size  : 183 KB
[KPI] Cores present    :
m4f0-0
r5f0-0
[KPI] System_init                      :       5513us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :      82210us
[KPI] Board_driversOpen                :          0us
[KPI] Sciclient Get Version            :      10200us
[KPI] App_loadImages                   :       6977us
[KPI] App_loadSelfcoreImage            :       7571us
[KPI] SBL Total Time Taken             :     112474us

Image loading done, switching to application ...
Starting MCU-m4f and 2nd stage bootloader

SYSFW Firmware Version 11.1.5--v11.01.05 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : eMMC
[KPI] Boot Media Clock : 200.000 MHz
[KPI] Boot Image Size  : 22446 KB
[KPI] Cores present    :
hsm-m4f0-0
r5f0-0
a530-0
[KPI] System_init                      :       2833us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :      20820us
[KPI] Board_driversOpen                :          0us
[KPI] Sciclient Get Version            :      10240us
[KPI] App_loadImages                   :       5684us
[KPI] App_loadSelfcoreImage            :       8419us
[KPI] App_loadLinuxImages              :     366136us
[KPI] SBL Total Time Taken             :     414135us

Image loading done, switching to application ...
Starting linux and RTOS/Baremetal applications
NOTICE:  BL31: v2.13.0(release):v2.13.0-710-gcd08e7883
NOTICE:  BL31: Built : 14:10:13, Sep 19 2025
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x410fd034]
[    0.000000] Linux version 6.12.35-ge3e551586dfa-dirty (user-Workstation-Desktop-PC) (aarch64-oe-linux-gcc (GCC) 13.4.0, GNU ld (GNU Binutils) 2.42.0.20240723) #1 SMP PREEMPT Fri Sep 19 16:45:01 IST 2025
[    0.000000] KASLR disabled due to lack of seed
[    0.000000] Machine model: Texas Instruments AM625 SK
[    0.000000] earlycon: ns16550a0 at MMIO32 0x0000000002800000 (options '')
[    0.000000] printk: legacy bootconsole [ns16550a0] enabled
[    0.280611] Warning: unable to open an initial console.

am62xx-evm login:
```

### OSPI

```
SYSFW Firmware Version 11.1.5--v11.01.05 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 192 KB
[KPI] Cores present    :
m4f0-0
r5f0-0
[KPI] System_init                      :      23591us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :        208us
[KPI] Board_driversOpen                :       1360us
[KPI] Sciclient Get Version            :      10206us
[KPI] App_waitForMcuPbist              :        106us
[KPI] App_waitForMcuLbist              :       7689us
[KPI] App_loadImages                   :       3678us
[KPI] App_loadSelfcoreImage            :       4157us
[KPI] SBL Total Time Taken             :      50999us

Image loading done, switching to application ...
Starting MCU-m4f and 2nd stage bootloader

SYSFW Firmware Version 11.1.5--v11.01.05 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 22445 KB
[KPI] Cores present    :
hsm-m4f0-0
r5f0-0
a530-0
[KPI] System_init                      :       2768us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :        259us
[KPI] Board_driversOpen                :        250us
[KPI] Sciclient Get Version            :      10259us
[KPI] App_loadImages                   :       2882us
[KPI] App_loadSelfcoreImage            :       4699us
[KPI] App_loadLinuxImages              :     235223us
[KPI] SBL Total Time Taken             :     256345us

Image loading done, switching to application ...
Starting linux and RTOS/Baremetal applications
NOTICE:  BL31: v2.13.0(release):v2.13.0-710-gcd08e7883
NOTICE:  BL31: Built : 17:54:37, Sep 19 2025
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x410fd034]
[    0.000000] Linux version 6.12.35-ge3e551586dfa-dirty (user-Workstation-Desktop-PC) (aarch64-oe-linux-gcc (GCC) 13.4.0, GNU ld (GNU Binutils) 2.42.0.20240723) #1 SMP PREEMPT Fri Sep 19 18:12:05 IST 2025
[    0.000000] KASLR disabled due to lack of seed
[    0.000000] Machine model: Texas Instruments AM6254xxl SK
[    0.000000] earlycon: ns16550a0 at MMIO32 0x0000000002800000 (options '')
[    0.000000] printk: legacy bootconsole [ns16550a0] enabled
[    0.274576] Warning: unable to open an initial console.

am62xx-evm login:
```