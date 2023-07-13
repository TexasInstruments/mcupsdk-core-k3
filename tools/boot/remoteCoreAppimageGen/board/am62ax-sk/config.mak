export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak


#Input binary name
APP_NAME ?= vx_app_rtos_mcu1_0_strip.out

#Output appimage name
APPIMAGE_NAME ?=vx_app_rtos_mcu1_0_strip.appimage

# boot ID for appimage
BOOTIMAGE_CORE_ID ?= 4

#SBL dev ID
SBL_DEV_ID=55