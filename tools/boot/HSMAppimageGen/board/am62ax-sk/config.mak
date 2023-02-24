
export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak


#HSM image load address
HSM_LOAD_ADDR=0x43C00000

#Input binary name
HSM_BINARY_NAME = HSM_min_sample.bin

#Output appimage name
HSM_APPIMAGE_NAME=hsm.appimage

#HSM core boot ID for appimage
BOOTIMAGE_CORE_ID_HSM = 6

#SBL dev ID
SBL_DEV_ID=55

