export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak

#Processor SDK QNX image path
PSDK_QNX_PATH?=/home/shiva/workstation/62p/psdkqa
QNX_IFS_PATH=$(PSDK_QNX_PATH)/bootfs

#Path for prebuit images in Processor SDK QNX
PSDK_QNX_PREBUILT_IMAGES=$(PSDK_QNX_PATH)/sbl_bootfiles/atf_optee_dir

#Input qnx binaries
ATF_BIN_NAME=bl31.bin
OPTEE_BIN_NAME=bl32.bin
QNX_BIN_NAME=qnx-ifs

#QNX image load address
ATF_LOAD_ADDR=0x9e780000
OPTEE_LOAD_ADDR=0x9e800000
QNX_LOAD_ADDR=0x80080000

#Output appimage name
QNX_BOOTIMAGE_NAME=qnx.appimage

#a53ss0-0 core Id for app image
BOOTIMAGE_CORE_ID_a53ss0-0 = 0
