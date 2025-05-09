export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak

# To-Do : Update PSDK QNX Path
# #Processor SDK QNX image path
# PSDK_QNX_PATH?=<update path here>
QNX_IFS_PATH=$(MCU_PLUS_SDK_PATH)/tools/boot/hlos_prebuilt/j722s-evm/qnx

#Path for prebuit images in Processor SDK QNX
PSDK_QNX_PREBUILT_IMAGES=$(MCU_PLUS_SDK_PATH)/tools/boot/hlos_prebuilt/j722s-evm/linux

#Input qnx binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
QNX_BIN_NAME=qnx-ifs

#QNX image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
QNX_LOAD_ADDR=0x80080000

ifdef FDT_BIN_NAME
FDT_LOAD_ADDR=0x88000000
endif

#Output appimage name
QNX_BOOTIMAGE_NAME=qnx.appimage

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
