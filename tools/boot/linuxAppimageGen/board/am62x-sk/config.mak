export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

#Processor SDK linux install path
PSDK_LINUX_PATH=$(TOOLS_PATH)/ti-processor-sdk-linux-am62xx-evm-09.00.00.03

#Path for prebuit images in Processor SDK linux
PSDK_LINUX_PREBUILT_IMAGES=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/am62xx-evm

#Input linux binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
SPL_BIN_NAME=u-boot-spl.bin-am62xx-evm

#Linux image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
SPL_LOAD_ADDR=0x80080000

#Output appimage name
LINUX_BOOTIMAGE_NAME=linux.appimage

#a53ss0-0 core Id for app image
BOOTIMAGE_CORE_ID_a53ss0-0 = 0