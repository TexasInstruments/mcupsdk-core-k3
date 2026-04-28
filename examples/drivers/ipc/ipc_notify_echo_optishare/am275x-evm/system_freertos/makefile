#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../../..)
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
MULTI_CORE_BOOTIMAGE_NAME:=ipc_notify_echo_optishare_system.$(PROFILE).mcelf
MULTI_CORE_BOOTIMAGE_NAME_SIGNED:=$(MULTI_CORE_BOOTIMAGE_NAME).signed
MULTI_CORE_BOOTIMAGE_NAME_XIP:=ipc_notify_echo_optishare_system.$(PROFILE).mcelf_xip
MULTI_CORE_BOOTIMAGE_NAME_HS:=$(MULTI_CORE_BOOTIMAGE_NAME).hs
MULTI_CORE_BOOTIMAGE_NAME_HS_FS:=$(MULTI_CORE_BOOTIMAGE_NAME).hs_fs
CORE_1=--script ../r5fss0-0_freertos/example.syscfg --context r5fss0-0 --output ../r5fss0-0_freertos/ti-arm-clang/generated
CORE_2=--script ../r5fss0-1_freertos/example.syscfg --context r5fss0-1 --output ../r5fss0-1_freertos/ti-arm-clang/generated
CORE_3=--script ../r5fss1-0_freertos/example.syscfg --context r5fss1-0 --output ../r5fss1-0_freertos/ti-arm-clang/generated
CORE_4=--script ../r5fss1-1_freertos/example.syscfg --context r5fss1-1 --output ../r5fss1-1_freertos/ti-arm-clang/generated

CORES = \
    $(CORE_1) \
    $(CORE_2) \
    $(CORE_3) \
    $(CORE_4) \

MULTI_CORE_BOOTIMAGE_NAME_OPTISHARE:=ipc_notify_echo_optishare_system.$(PROFILE).optishare.mcelf
MULTI_CORE_BOOTIMAGE_NAME_OPTISHARE_HS_FS:=ipc_notify_echo_optishare_system.$(PROFILE).optishare.mcelf.hs_fs

CORE_IMG_OPTISHARE_ARGS :=

CORE_1_OPTISHARE_IMG=../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.out
CORE_IMG_OPTISHARE_ARGS +=--core-img=1:$(CORE_1_OPTISHARE_IMG)

CORE_2_OPTISHARE_IMG=../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.out
CORE_IMG_OPTISHARE_ARGS +=--core-img=2:$(CORE_2_OPTISHARE_IMG)

CORE_3_OPTISHARE_IMG=../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.out
CORE_IMG_OPTISHARE_ARGS +=--core-img=3:$(CORE_3_OPTISHARE_IMG)

CORE_4_OPTISHARE_IMG=../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.out
CORE_IMG_OPTISHARE_ARGS +=--core-img=4:$(CORE_4_OPTISHARE_IMG)

COREXMLS = \
	../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml\
	../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml\
	../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml\
	../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml\

SYSTEM_FLAG := true

all: postBuild

corebuild: syscfg
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ all SYSTEM_FLAG=${SYSTEM_FLAG}
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ all SYSTEM_FLAG=${SYSTEM_FLAG}
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ all SYSTEM_FLAG=${SYSTEM_FLAG}
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ all SYSTEM_FLAG=${SYSTEM_FLAG}

postBuild: corebuild
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME_HS)
endif

clean:
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ clean
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_SIGNED)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_XIP)

scrub:
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
	$(RM) \*.tmp
	$(RM) \*.out
	$(RM) \*.map
	$(RM) \*.lnkxml
	$(RM) \*.mcelf-enc
else
	$(RM) *.tmp
	$(RM) *.out
	$(RM) *.map
	$(RM) *.lnkxml
	$(RM) *.mcelf
	$(RM) *.mcelf.signed
	$(RM) *.mcelf.hs
	$(RM) *.mcelf.hs_fs
	$(RM) *.mcelf_xip
	$(RM) *.mcelf-enc
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

CG_TOOL_ROOT=$(CGT_TI_ARM_CLANG_PATH)
CC=$(CG_TOOL_ROOT)/bin/tiarmclang
LNK=$(CG_TOOL_ROOT)/bin/tiarmclang

sso: optisave

coreout: sso.out
	@echo .
	@echo generating files with sso
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ coreout SYSTEM_FLAG=${SYSTEM_FLAG} SSO_PATH=../../system_freertos/sso.out
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ coreout SYSTEM_FLAG=${SYSTEM_FLAG} SSO_PATH=../../system_freertos/sso.out
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ coreout SYSTEM_FLAG=${SYSTEM_FLAG} SSO_PATH=../../system_freertos/sso.out
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ coreout SYSTEM_FLAG=${SYSTEM_FLAG} SSO_PATH=../../system_freertos/sso.out
	@echo generating files with sso done!
	@echo .

sso.out: sso.cmd
	@echo .
	@echo generating sso.out
	$(CC) -Wl,sso.cmd.tmp -o sso.out -Wl,--xml_link_info=sso.lnkxml -Wl,--gen_xml_func_hash
	@echo done
	@echo .

sso.cmd: all $(COREXMLS)
	@echo .
	@echo generating sso.cmd.tmp
	$(OPTISHARE) -o sso.cmd.tmp $(COREXMLS) -s sso.info.tmp --mem_spec optishare_memmap.json
	@echo generating sso.cmd done
	@echo .

optisave: buildmcelfsso
	$(OPTISAVE) ../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml ../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.lnkxml > ../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).ossr
	$(OPTISAVE) ../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml ../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.lnkxml > ../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).ossr
	$(OPTISAVE) ../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml ../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.lnkxml > ../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).ossr
	$(OPTISAVE) ../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).lnkxml ../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).optishare.lnkxml > ../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).ossr

buildmcelfsso: coreout
	@echo .
	@echo generating mcelf with sso
	$(PYTHON) $(MCELF_IMAGE_GEN) $(CORE_IMG_OPTISHARE_ARGS) --output=$(MULTI_CORE_BOOTIMAGE_NAME_OPTISHARE) --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION) --sso=sso.out
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(MULTI_CORE_BOOTIMAGE_NAME_OPTISHARE) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(MULTI_CORE_BOOTIMAGE_NAME_OPTISHARE_HS_FS) --keyversion $(VERSION)
	@echo  Boot multi-core ELF image: $(MULTI_CORE_BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	$(MAKE) sso.mcelf

sso.mcelf: sso.out
	@echo .
	@echo generating standalone sso.mcelf from sso.out ...
	$(PYTHON) $(MCELF_IMAGE_GEN) --core-img=1:sso.out --output=sso.mcelf --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION)
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin sso.mcelf --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output sso.mcelf.hs_fs --keyversion $(VERSION)
	@echo  sso.mcelf and sso.mcelf.hs_fs generated !!!
	@echo  .

MCELF_IMAGE_GEN = $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreELFImageGen/genimage.py
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

MULTI_CORE_APP_PARAMS = \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-0):../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss0-1):../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-0):../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    --core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \

MCELF_XIP_RANGE?=0x60100000:0x60200000

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../r5fss0-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    ../r5fss0-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    ../r5fss1-0_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \
    ../r5fss1-1_freertos/ti-arm-clang/ipc_notify_echo_optishare.$(PROFILE).out \

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
