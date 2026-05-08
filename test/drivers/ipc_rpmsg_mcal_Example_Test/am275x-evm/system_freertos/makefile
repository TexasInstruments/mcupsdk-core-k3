#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

PROFILE?=release
CFG?=6core

# CFG selects syscfg variant:
#   6core (default):  example.syscfg - 6 cores, vringNumBuf=8
#   cfg3:             example_cfg3.syscfg - 4 cores (C75SS1_0 excluded), vringNumBuf=8
#   cfg4:             example_cfg4.syscfg - 4 cores (C75SS1_0 excluded), vringNumBuf=4
#   cfg5:             example_cfg5.syscfg - 4 cores (C75SS1_0 excluded), vringNumBuf=2
#   cfg8:             example_cfg8.syscfg - 4 cores (C75SS1_0 excluded), vringNumBuf=1
ifeq ($(CFG), cfg3)
    SYSCFG_VARIANT=example_cfg3.syscfg
    $(info Building 4-core configuration, vringNumBuf=8 (C75SS1_0 excluded))
else ifeq ($(CFG), cfg4)
    SYSCFG_VARIANT=example_cfg4.syscfg
    $(info Building 4-core configuration, vringNumBuf=4 (C75SS1_0 excluded))
else ifeq ($(CFG), cfg5)
    SYSCFG_VARIANT=example_cfg5.syscfg
    $(info Building 4-core configuration, vringNumBuf=2 (C75SS1_0 excluded))
else ifeq ($(CFG), cfg8)
    SYSCFG_VARIANT=example_cfg8.syscfg
    $(info Building 4-core configuration, vringNumBuf=1 (C75SS1_0 excluded))
else
    SYSCFG_VARIANT=example.syscfg
    $(info Building 6-core configuration, vringNumBuf=8 (all cores enabled))
endif

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

MULTI_CORE_BOOTIMAGE_PATH=$(abspath .)
MULTI_CORE_BOOTIMAGE_NAME:=test_ipc_rpmsg_system.$(PROFILE).mcelf
MULTI_CORE_BOOTIMAGE_NAME_SIGNED:=$(MULTI_CORE_BOOTIMAGE_NAME).signed
MULTI_CORE_BOOTIMAGE_NAME_XIP:=test_ipc_rpmsg_system.$(PROFILE).mcelf_xip

CORE_0=--script ../c75ss0-0_freertos/$(SYSCFG_VARIANT) --context c75ss0-0 --output ../c75ss0-0_freertos/ti-c7000/generated
CORE_1=--script ../c75ss1-0_freertos/example.syscfg --context c75ss1-0 --output ../c75ss1-0_freertos/ti-c7000/generated
CORE_2=--script ../r5fss0-0_freertos/$(SYSCFG_VARIANT) --context r5fss0-0 --output ../r5fss0-0_freertos/ti-arm-clang/generated
CORE_3=--script ../r5fss0-1_freertos/$(SYSCFG_VARIANT) --context r5fss0-1 --output ../r5fss0-1_freertos/ti-arm-clang/generated
CORE_4=--script ../r5fss1-0_freertos/$(SYSCFG_VARIANT) --context r5fss1-0 --output ../r5fss1-0_freertos/ti-arm-clang/generated
CORE_5=--script ../r5fss1-1_freertos/$(SYSCFG_VARIANT) --context r5fss1-1 --output ../r5fss1-1_freertos/ti-arm-clang/generated

# CORE_1 (c75ss1-0) is only included in 6-core config; cfg3, cfg4, cfg5, cfg8 exclude it
ifeq ($(CFG), cfg3)
    CORES = \
        $(CORE_5) \
        $(CORE_4) \
        $(CORE_3) \
        $(CORE_2) \
        $(CORE_0) \

else ifeq ($(CFG), cfg4)
    CORES = \
        $(CORE_5) \
        $(CORE_4) \
        $(CORE_3) \
        $(CORE_2) \
        $(CORE_0) \

else ifeq ($(CFG), cfg5)
    CORES = \
        $(CORE_5) \
        $(CORE_4) \
        $(CORE_3) \
        $(CORE_2) \
        $(CORE_0) \

else ifeq ($(CFG), cfg8)
    CORES = \
        $(CORE_5) \
        $(CORE_4) \
        $(CORE_3) \
        $(CORE_2) \
        $(CORE_0) \

else
    CORES = \
        $(CORE_5) \
        $(CORE_4) \
        $(CORE_3) \
        $(CORE_2) \
        $(CORE_1) \
        $(CORE_0) \

endif

all: syscfg
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ all
ifeq ($(CFG), cfg3)
else ifeq ($(CFG), cfg4)
else ifeq ($(CFG), cfg5)
else ifeq ($(CFG), cfg8)
else
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ all
endif
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ all
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME)

clean:
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ clean
ifeq ($(CFG), cfg3)
else ifeq ($(CFG), cfg4)
else ifeq ($(CFG), cfg5)
else ifeq ($(CFG), cfg8)
else
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ clean
endif
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ clean
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_SIGNED)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_XIP)

scrub:
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ scrub
ifeq ($(CFG), cfg3)
else ifeq ($(CFG), cfg4)
else ifeq ($(CFG), cfg5)
else ifeq ($(CFG), cfg8)
else
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ scrub
endif
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ scrub
ifeq ($(OS),Windows_NT)
	$(RM) \*.mcelf
	$(RM) \*.mcelf.signed
	$(RM) \*.mcelf.hs_fs
	$(RM) \*.mcelf.hs
	$(RM) \*.mcelf_xip
else
	$(RM) *.mcelf
	$(RM) *.mcelf.signed
	$(RM) *.mcelf.hs
	$(RM) *.mcelf.hs_fs
	$(RM) *.mcelf_xip
endif

syscfg:
	@echo Generating SysConfig files ...
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --device AM275x --product $(SYSCFG_SDKPRODUCT) $(CORES)

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device AM275x --part AM2754 --package ANJ $(CORES)

#
# Generation of multi-core boot image which can be loaded by Secondary Boot Loader (SBL)
#
ifeq ($(OS),Windows_NT)
EXE_EXT=.exe
endif
BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(PROFILE).txt

BOOTIMAGE_CORE_ID_wkup-r5fss0-0 = 0
BOOTIMAGE_CORE_ID_r5fss0-0      = 1
BOOTIMAGE_CORE_ID_r5fss0-1      = 2
BOOTIMAGE_CORE_ID_r5fss1-0      = 3
BOOTIMAGE_CORE_ID_r5fss1-1      = 4
BOOTIMAGE_CORE_ID_c75ss0-0      = 5
BOOTIMAGE_CORE_ID_c75ss1-0      = 6
BOOTIMAGE_CORE_ID_hsm-m4fss0-0  = 7
SBL_RUN_ADDRESS=0x43C00000
SBL_DEV_ID=55
MCELF_IMAGE_GEN = $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreELFImageGen/genimage.py
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

ifeq ($(CFG), cfg3)
MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss0-0):../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

else ifeq ($(CFG), cfg4)
MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss0-0):../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

else ifeq ($(CFG), cfg5)
MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss0-0):../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

else ifeq ($(CFG), cfg8)
MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss0-0):../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

else
MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss0-0):../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_c75ss1-0):../c75ss1-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../c75ss0-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../c75ss1-0_freertos/ti-c7000/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/test_ipc_rpmsg.$(PROFILE).out \

endif

MCELF_XIP_RANGE?=0x60100000:0x60200000

$(MULTI_CORE_BOOTIMAGE_DEPENDENCY):

$(MULTI_CORE_BOOTIMAGE_NAME): $(MULTI_CORE_BOOTIMAGE_DEPENDENCY)
	@echo  Boot multi-core image: $@ ...
	$(PYTHON) $(MCELF_IMAGE_GEN) $(MULTI_CORE_APP_PARAMS) --output=$(MULTI_CORE_BOOTIMAGE_NAME) --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION)
	@echo  Boot multi-core image: $(MULTI_CORE_BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(MULTI_CORE_BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(MULTI_CORE_BOOTIMAGE_NAME).hs_fs --keyversion $(VERSION)
	@echo  Boot multi-core image: $(MULTI_CORE_BOOTIMAGE_PATH)/$(MULTI_CORE_BOOTIMAGE_NAME).hs_fs Done !!!
	@echo  .

$(MULTI_CORE_BOOTIMAGE_NAME_HS): $(MULTI_CORE_BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(MULTI_CORE_BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(MULTI_CORE_BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
else
	@echo Boot image signing: Encryption is enabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(MULTI_CORE_BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(MULTI_CORE_BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME)-enc
endif
	@echo  Boot multi-core image: $(MULTI_CORE_BOOTIMAGE_PATH)/$@ Done !!!
	@echo  Boot multi-core image: $(MULTI_CORE_BOOTIMAGE_PATH)/$(MULTI_CORE_BOOTIMAGE_NAME_HS) Done !!!
	@echo  .
endif
