
DEVICE ?= am62px

GCC_ARCH64_VERSION=9.2-2019.12
CGT_C6X_VERSION=8.3.12
C6X_DSPLIB_VERSION=3_4_0_0
CGT_C7X_VERSION=4.1.0B1
CGT_ARMLLVM_VERSION=3.2.2.LTS
CGT_PRU_VERSION=2.3.3
SYSCONFIG_VERSION=1.19.0
SYSCONFIG_BUILD=3426

ifeq ($(OS),Windows_NT)
    TOOLS_PATH?=C:/ti
    CCS_PATH?=$(TOOLS_PATH)/ccs1260/ccs
    CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipsec
    CYGWIN_PATH?=$(CCS_PATH)/utils/cygwin
    MKDIR=$(CYGWIN_PATH)/mkdir -p
    RMDIR=$(CYGWIN_PATH)/rm -rf
    RM=$(CYGWIN_PATH)/rm -f
    COPY=$(CYGWIN_PATH)/cp
    TOUCH=$(CYGWIN_PATH)/touch
    PATHSEP=\\
    CHMOD=$(CYGWIN_PATH)/echo
    SHELL=cmd.exe
    CGT_GCC_AARCH64_PATH=$(TOOLS_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-mingw-w64-i686-aarch64-none-elf
    CGT_GCC_ARM_PATH=$(TOOLS_PATH)/gcc-arm-none-eabi-7-2017-q4-major-win32
    CGT_GCC_ARMV7_PATH=$(CGT_GCC_ARM_PATH)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        export TOOLS_PATH?=$(HOME)/ti
        export CCS_PATH?=$(TOOLS_PATH)/ccs1260/ccs
        export CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipse
        export MKDIR=mkdir -p
        export RMDIR=rm -rf
        export RM=rm -f
        export COPY=cp
        export TOUCH=touch
        export PATHSEP=/
        export CHMOD=chmod
        CGT_GCC_AARCH64_PATH=$(TOOLS_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-x86_64-aarch64-none-elf
        CGT_GCC_ARM_PATH=$(TOOLS_PATH)/gcc-arm-none-eabi-7-2017-q4-major
        CGT_GCC_ARMV7_PATH=$(CGT_GCC_ARM_PATH)
        CGT_TI_C7X_HOSTEMU_PATH=/usr
    endif
endif

CGT_TI_PRU_PATH=$(TOOLS_PATH)/ti-cgt-pru_$(CGT_PRU_VERSION)
CGT_TI_ARM_CLANG_PATH=$(CCS_PATH)/tools/compiler/ti-cgt-armllvm_$(CGT_ARMLLVM_VERSION)
ifeq ($(wildcard $(CGT_TI_ARM_CLANG_PATH)),)
    CGT_TI_ARM_CLANG_PATH=$(TOOLS_PATH)/ti-cgt-armllvm_$(CGT_ARMLLVM_VERSION)
endif
CGT_TI_C6000_PATH=$(CCS_PATH)/tools/compiler/ti-cgt-c6000_$(CGT_C6X_VERSION)
DSPLIB_PATH=$(MCU_PLUS_SDK_PATH)/source/dsplib_c66x_$(C6X_DSPLIB_VERSION)
CGT_TI_C7000_PATH=$(TOOLS_PATH)/ti-cgt-c7000_$(CGT_C7X_VERSION)
CCS_NODE = $(CCS_PATH)/tools/node/node
SYSCFG_PATH ?= $(TOOLS_PATH)/sysconfig_$(SYSCONFIG_VERSION)
SYSCFG_CLI_PATH ?= $(SYSCFG_PATH)
SYSCFG_NODE = $(SYSCFG_PATH)/nodejs/node
SYSCFG_NWJS = $(SYSCFG_PATH)/nw/nw
SYSCFG_SDKPRODUCT=$(MCU_PLUS_SDK_PATH)/.metadata/product.json

# Variable pointing to location of prebuilt industrial communication libraries
MCU_PLUS_SDK_IND_COMMS_LIBS_PATH ?= $(MCU_PLUS_SDK_PATH)/source/commercial/industrial_comms_libs