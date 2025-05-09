export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak

#Path for prebuit images in Processor SDK linux
PSDK_LINUX_PREBUILT_IMAGES=$(MCU_PLUS_SDK_PATH)/tools/boot/hlos_prebuilt/j722s-evm/linux

FASTBOOT_LINUX?=0

#Input linux binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
SPL_BIN_NAME=u-boot-spl-j722s-evm.bin

ifeq ($(FASTBOOT_LINUX), 1)
#Load Kernel directly
KERN_BIN_NAME=Image
FDT_BIN_NAME=k3-j722s-evm.dtb
endif

#Linux image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
SPL_LOAD_ADDR=0x80080000

ifeq ($(FASTBOOT_LINUX), 1)
KERN_LOAD_ADDR=0x80080000
FDT_LOAD_ADDR=0x82000000
endif

#Output appimage name
LINUX_BOOTIMAGE_NAME=linux.appimage

#core Ids to generate app image
BOOTIMAGE_CORE_ID_mcu-r5fss0-0  = 0
BOOTIMAGE_CORE_ID_wkup-r5fss0-0 = 1
BOOTIMAGE_CORE_ID_main-r5fss0-0 = 2
BOOTIMAGE_CORE_ID_c75ss0-0      = 3
BOOTIMAGE_CORE_ID_c75ss1-0      = 4
BOOTIMAGE_CORE_ID_a53ss0-0      = 5
BOOTIMAGE_CORE_ID_a53ss0-1      = 6
BOOTIMAGE_CORE_ID_a53ss1-0      = 7
BOOTIMAGE_CORE_ID_a53ss1-1      = 8

# Add path to executable binaries that you want to run along with the Linux
IMG1 = $(BOOTIMAGE_CORE_ID_wkup-r5fss0-0) $(MCU_PLUS_SDK_PATH)/tools/sysfw/sciserver_binary/j722s/sciclient_get_version.release.rprc
IMG2 =
IMG3 =

RTOS_IMG_LIST = $(IMG1) $(IMG2) $(IMG3)



