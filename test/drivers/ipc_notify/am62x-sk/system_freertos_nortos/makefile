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

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

MULTI_CORE_BOOTIMAGE_PATH=$(abspath .)
MULTI_CORE_BOOTIMAGE_NAME:=test_ipc_notify_system.$(PROFILE).appimage
MULTI_CORE_BOOTIMAGE_NAME_SIGNED:=$(MULTI_CORE_BOOTIMAGE_NAME).signed
MULTI_CORE_BOOTIMAGE_NAME_XIP:=test_ipc_notify_system.$(PROFILE).appimage_xip
MULTI_CORE_BOOTIMAGE_NAME_HS:=$(MULTI_CORE_BOOTIMAGE_NAME).hs
ATF_LOAD_ADDR:=0x80000000
ATF_OUTNAME:=bl31.$(PROFILE).out
ATF_RPRC_NAME:=bl31.$(PROFILE).rprc
ATF_BIN_NAME:=bl31.bin
ATF_BUILD_PATH:=$(MCU_PLUS_SDK_PATH)/source/atf/trusted-firmware-a/build/k3/lite/$(PROFILE)

CORE_0=--script ../r5fss0-0_freertos/example.syscfg --context r5fss0-0 --output ../r5fss0-0_freertos/ti-arm-clang/generated
CORE_1=--script ../m4fss0-0_nortos/example.syscfg --context m4fss0-0 --output ../m4fss0-0_nortos/ti-arm-clang/generated
CORE_2=--script ../a53ss0-0_freertos/example.syscfg --context a53ss0-0 --output ../a53ss0-0_freertos/gcc-aarch64/generated

CORES = \
    $(CORE_2) \
    $(CORE_1) \
    $(CORE_0) \

all: syscfg
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../m4fss0-0_nortos/ti-arm-clang/ all
	$(MAKE) -C ../a53ss0-0_freertos/gcc-aarch64/ all
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME_HS)
endif

clean:
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../m4fss0-0_nortos/ti-arm-clang/ clean
	$(MAKE) -C ../a53ss0-0_freertos/gcc-aarch64/ clean
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_SIGNED)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_XIP)

scrub:
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../m4fss0-0_nortos/ti-arm-clang/ scrub
	$(MAKE) -C ../a53ss0-0_freertos/gcc-aarch64/ scrub
ifeq ($(OS),Windows_NT)
	$(RM) \*.appimage
	$(RM) \*.appimage.signed
	$(RM) \*.appimage.hs
	$(RM) \*.appimage_xip
else
	$(RM) *.appimage
	$(RM) *.appimage.signed
	$(RM) \*.appimage.hs
	$(RM) *.appimage_xip
endif

syscfg:
	@echo Generating SysConfig files ...
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --product $(SYSCFG_SDKPRODUCT) $(CORES)

syscfg-gui:
	$(SYSCFG_NWJS) $(SYSCFG_PATH) --product $(SYSCFG_SDKPRODUCT) --device AM62x --part Default --package ALW $(CORES)

#
# Generation of multi-core boot image which can be loaded by Secondary Boot Loader (SBL)
#
ifeq ($(OS),Windows_NT)
EXE_EXT=.exe
endif
BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(PROFILE).txt

BOOTIMAGE_CORE_ID_a53ss0-0 = 0
BOOTIMAGE_CORE_ID_a53ss0-1 = 1
BOOTIMAGE_CORE_ID_a53ss1-0 = 2
BOOTIMAGE_CORE_ID_a53ss1-1 = 3
BOOTIMAGE_CORE_ID_r5fss0-0 = 4
BOOTIMAGE_CORE_ID_m4fss0-0 = 5
BOOTIMAGE_CORE_ID_hsm-m4fss0-0 = 6
BOOTIMAGE_CORE_ID_load_only = 21
SBL_RUN_ADDRESS=0x43C00000
SBL_DEV_ID=55
MULTI_CORE_IMAGE_GEN = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/multicoreImageGen.js
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

ifeq ($(ATF_INTEGRATED_BOOT), yes)
MULTI_CORE_APP_PARAMS = \
	$(ATF_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_a53ss0-0) \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss0-0) \
    ../m4fss0-0_nortos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_m4fss0-0) \
    ../a53ss0-0_freertos/gcc-aarch64/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_load_only) \

else
MULTI_CORE_APP_PARAMS = \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss0-0) \
    ../m4fss0-0_nortos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_m4fss0-0) \
    ../a53ss0-0_freertos/gcc-aarch64/test_ipc_notify.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_a53ss0-0) \

endif

MULTI_CORE_APP_PARAMS_XIP = \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_r5fss0-0) \
    ../m4fss0-0_nortos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_m4fss0-0) \
    ../a53ss0-0_freertos/gcc-aarch64/test_ipc_notify.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_a53ss0-0) \

ifeq ($(ATF_INTEGRATED_BOOT), yes)
MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
	$(ATF_RPRC_NAME) \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc \
    ../m4fss0-0_nortos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc \
    ../a53ss0-0_freertos/gcc-aarch64/test_ipc_notify.$(PROFILE).rprc \

else
MULTI_CORE_IMAGE_PARAMS = \
    ../r5fss0-0_freertos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc \
    ../m4fss0-0_nortos/ti-arm-clang/test_ipc_notify.$(PROFILE).rprc \
    ../a53ss0-0_freertos/gcc-aarch64/test_ipc_notify.$(PROFILE).rprc \

endif

$(MULTI_CORE_BOOTIMAGE_DEPENDENCY):

$(MULTI_CORE_BOOTIMAGE_NAME): $(MULTI_CORE_BOOTIMAGE_DEPENDENCY)
ifeq ($(ATF_INTEGRATED_BOOT), yes)
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(ATF_LOAD_ADDR) -e $(ATF_LOAD_ADDR) $(ATF_BUILD_PATH)/$(ATF_BIN_NAME) -o $(ATF_OUTNAME)
	$(OUTRPRC_CMD) $(ATF_OUTNAME) >> $(BOOTIMAGE_TEMP_OUT_FILE)
endif
	@echo  Boot multi-core image: $@ ...
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(MULTI_CORE_BOOTIMAGE_NAME) $(MULTI_CORE_APP_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(MULTI_CORE_BOOTIMAGE_NAME_XIP) $(MULTI_CORE_APP_PARAMS_XIP) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
ifeq ($(ATF_INTEGRATED_BOOT), yes)
	$(RM) $(ATF_OUTNAME)
	$(RM) $(ATF_RPRC_NAME)
endif
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
