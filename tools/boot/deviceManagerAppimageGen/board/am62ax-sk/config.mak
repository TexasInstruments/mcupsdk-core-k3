export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak


#Input binary name
DM_APP_NAME ?= sciserver_freertos.release.xer5f

#Output appimage name
DM_APPIMAGE_NAME?=sciserver_freertos.release.appimage

#DM core boot ID for appimage
BOOTIMAGE_CORE_ID_DM = 4

#SBL dev ID
SBL_DEV_ID=55