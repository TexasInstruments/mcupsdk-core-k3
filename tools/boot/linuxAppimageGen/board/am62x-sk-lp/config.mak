export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

#Processor SDK linux install path
PSDK_LINUX_PATH=$(TOOLS_PATH)/ti-processor-sdk-linux-am62xx-evm-10.00.05.02

#Path for prebuit images in Processor SDK linux
PSDK_LINUX_PREBUILT_IMAGES?=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/am62xx-lp-evm

FALCON_MODE?=0

#Input linux binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
SPL_BIN_NAME=u-boot-spl.bin-am62xx-lp-evm

ifeq ($(FALCON_MODE), 1)
#Load Kernel directly
KERN_BIN_NAME=Image
FDT_BIN_NAME=k3-am62x-lp-sk.dtb
endif

#Linux image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
SPL_LOAD_ADDR=0x80080000

ifeq ($(FALCON_MODE), 1)
KERN_LOAD_ADDR=0x80080000
FDT_LOAD_ADDR=0x82000000
endif

#Output appimage name
LINUX_BOOTIMAGE_NAME?=linux.appimage

#a53ss0-0 core Id for app image
BOOTIMAGE_CORE_ID_a53ss0-0 = 0