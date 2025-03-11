#
# This file is the makefile for building CSI loopback test app for FreeRTOS
#
ifeq ($(RULES_MAKE), )
include $(PDK_INSTALL_PATH)/ti/build/Rules.make
else
include $(RULES_MAKE)
endif

APP_NAME = csirxtx_loopback_testapp_$(BUILD_OS_TYPE)

SRCDIR = src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
COMP_LIST_COMMON = fvid2 csirx csitx

ifeq ($(BUILD_OS_TYPE),freertos)
  CFLAGS_OS_DEFINES = -DFREERTOS
  COMP_LIST_COMMON += $(PDK_COMMON_FREERTOS_COMP)
  SRCS_COMMON += main_rtos.c
  INCLUDE_EXTERNAL_INTERFACES += freertos
endif

# Common source files and CFLAGS across all platforms and cores
# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON += csi_loopback_test_main.c serdes_sensor_config.c csi_loopback_app_utils.c
CFLAGS_LOCAL_COMMON += $(PDK_CFLAGS) $(CSIRX_CFLAGS) $(CFLAGS_OS_DEFINES)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
