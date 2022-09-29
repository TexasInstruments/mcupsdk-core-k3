export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

#Processor SDK linux install path
PSDK_LINUX_PATH=$(TOOLS_PATH)/ti-processor-sdk-linux-am62xx-evm-08.04.01.03
# If device type is HS, PSDK_LINUX_HS_IMAGE_PATH need to point to the path where A53 uboot is build,
# and has unsigned images of ATF (bl31), OPTEE (bl32.bin) and A53 SPL (u-boot-spl.bin).
# This is because we requires unsigned images for creating a signed linux.appimage and
# the HS Processor SDK Linux installer has the signed binaries in the prebuild images folder
PSDK_LINUX_HS_IMAGE_PATH=$(TOOLS_PATH)/a53-uboot-build/

#Path for prebuit images in Processor SDK linux
ifeq ($(DEVICE_TYPE),HS)
	PSDK_LINUX_PREBUILT_IMAGES=$(PSDK_LINUX_HS_IMAGE_PATH)
else
	PSDK_LINUX_PREBUILT_IMAGES=$(PSDK_LINUX_PATH)/board-support/prebuilt-images
endif

#Input linux binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
ifeq ($(DEVICE_TYPE),HS)
	SPL_BIN_NAME=u-boot-spl.bin
else
	SPL_BIN_NAME=u-boot-spl.bin-am62xx-evm
endif

#Linux image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
SPL_LOAD_ADDR=0x80080000

#Output appimage name
LINUX_BOOTIMAGE_NAME=linux.appimage

#a53ss0-0 core Id for app image
BOOTIMAGE_CORE_ID_a53ss0-0 = 0