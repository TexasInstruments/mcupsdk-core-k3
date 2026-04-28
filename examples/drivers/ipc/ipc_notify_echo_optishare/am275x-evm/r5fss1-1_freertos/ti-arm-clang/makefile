#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

CG_TOOL_ROOT=$(CGT_TI_ARM_CLANG_PATH)

CC=$(CG_TOOL_ROOT)/bin/tiarmclang
LNK=$(CG_TOOL_ROOT)/bin/tiarmclang
STRIP=$(CG_TOOL_ROOT)/bin/tiarmstrip
OBJCOPY=$(CG_TOOL_ROOT)/bin/tiarmobjcopy
ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

PROFILE?=release
ConfigName:=$(PROFILE)

OUTNAME:=ipc_notify_echo_optishare.$(PROFILE).out
COREOUTNAME:=ipc_notify_echo_optishare.$(PROFILE).optishare.out

BOOTIMAGE_PATH=$(abspath .)
BOOTIMAGE_NAME:=ipc_notify_echo_optishare.$(PROFILE).mcelf
BOOTIMAGE_NAME_XIP:=ipc_notify_echo_optishare.$(PROFILE).mcelf_xip
BOOTIMAGE_NAME_SIGNED:=ipc_notify_echo_optishare.$(PROFILE).mcelf.signed
BOOTIMAGE_NAME_HS:=ipc_notify_echo_optishare.$(PROFILE).mcelf.hs
BOOTIMAGE_NAME_HS_FS:=ipc_notify_echo_optishare.$(PROFILE).mcelf.hs_fs

MULTI_CORE_BOOTIMAGE_NAME_MCELF_OPTISHARE:=ipc_notify_echo_optishare.$(PROFILE).optishare.mcelf
MULTI_CORE_BOOTIMAGE_NAME_MCELF_OPTISHARE_HS_FS:=ipc_notify_echo_optishare.$(PROFILE).optishare.mcelf.hs_fs

TARGETS := $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
   TARGETS += $(BOOTIMAGE_NAME_HS)
endif

FILES_common := \
	ipc_notify_echo.c \
	main.c \
	ti_drivers_config.c \
	ti_drivers_open_close.c \
	ti_board_config.c \
	ti_board_open_close.c \
	ti_dpl_config.c \
	ti_pinmux_config.c \
	ti_power_clock_config.c \

FILES_PATH_common = \
	.. \
	../../.. \
	generated \

INCLUDES_common := \
	-I${CG_TOOL_ROOT}/include/c \
	-I${MCU_PLUS_SDK_PATH}/source \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f \
	-Igenerated \

DEFINES_common := \
	-DSOC_AM275X \

CFLAGS_common := \
	-mcpu=cortex-r5 \
	-mfloat-abi=hard \
	-mfpu=vfpv3-d16 \
	-mthumb \
	-Wall \
	-Werror \
	-g \
	-Wno-gnu-variable-sized-type-not-at-end \
	-Wno-unused-function \

CFLAGS_cpp_common := \
	-Wno-c99-designator \
	-Wno-extern-c-compat \
	-Wno-c++11-narrowing \
	-Wno-reorder-init-list \
	-Wno-deprecated-register \
	-Wno-writable-strings \
	-Wno-enum-compare \
	-Wno-reserved-user-defined-literal \
	-Wno-unused-const-variable \
	-x c++ \

CFLAGS_debug := \
	-D_DEBUG_=1 \

CFLAGS_release := \
	-Os \

LNK_FILES_common = \
	linker.cmd \

LIBS_PATH_common = \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	-Wl,-i${CG_TOOL_ROOT}/lib \

LIBS_common = \
	-lfreertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib \
	-ldrivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib \
	-llibc.a \
	-llibsysbm.a \

LFLAGS_common = \
	-Wl,--diag_suppress=10063 \
	-Wl,--priority \
	-Wl,--ram_model \
	-Wl,--reread_libs \
	-Wl,--gen_xml_func_hash \


LIBS_NAME = \
	freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib \
	drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib \
	libc.a \
	libsysbm.a \

LIBS_PATH_NAME = \
	${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	${CG_TOOL_ROOT}/lib \

FILES := $(FILES_common) $(FILES_$(PROFILE))
ASMFILES := $(ASMFILES_common) $(ASMFILES_$(PROFILE))
FILES_PATH := $(FILES_PATH_common) $(FILES_PATH_$(PROFILE))
CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
DEFINES := $(DEFINES_common) $(DEFINES_$(PROFILE))
INCLUDES := $(INCLUDES_common) $(INCLUDE_$(PROFILE))
LIBS := $(LIBS_common) $(LIBS_$(PROFILE))
LIBS_PATH := $(LIBS_PATH_common) $(LIBS_PATH_$(PROFILE))
LFLAGS := $(LFLAGS_common) $(LFLAGS_$(PROFILE))
LNKOPTFLAGS := $(LNKOPTFLAGS_common) $(LNKOPTFLAGS_$(PROFILE))
LNK_FILES := $(LNK_FILES_common) $(LNK_FILES_$(PROFILE))

LNK_FILES_OPTISHARE = \
	linker_optishare.cmd \

OBJDIR := obj/$(PROFILE)/
OBJS := $(FILES:%.c=%.obj)
OBJS += $(ASMFILES:%.S=%.obj)
DEPS := $(FILES:%.c=%.d)

vpath %.obj $(OBJDIR)
vpath %.c $(FILES_PATH)
vpath %.S $(FILES_PATH)
vpath %.lib $(LIBS_PATH_NAME)
vpath %.a $(LIBS_PATH_NAME)

$(OBJDIR)/%.obj %.obj: %.c
	@echo  Compiling: am275x:r5fss1-1:freertos:ti-arm-clang $(OUTNAME): $<
	$(CC) -c $(CFLAGS) $(INCLUDES) $(DEFINES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.obj %.obj: %.S
	@echo  Compiling: am275x:r5fss1-1:freertos:ti-arm-clang $(LIBNAME): $<
	$(CC) -c $(CFLAGS) -o $(OBJDIR)/$@ $<

all: $(TARGETS)

SYSCFG_GEN_FILES=generated/ti_drivers_config.c generated/ti_drivers_config.h
SYSCFG_GEN_FILES+=generated/ti_drivers_open_close.c generated/ti_drivers_open_close.h
SYSCFG_GEN_FILES+=generated/ti_dpl_config.c generated/ti_dpl_config.h
SYSCFG_GEN_FILES+=generated/ti_pinmux_config.c generated/ti_power_clock_config.c
SYSCFG_GEN_FILES+=generated/ti_board_config.c generated/ti_board_config.h
SYSCFG_GEN_FILES+=generated/ti_board_open_close.c generated/ti_board_open_close.h

$(OUTNAME): syscfg $(SYSCFG_GEN_FILES) $(OBJS) $(LNK_FILES) $(LIBS_NAME)
	@echo  .
	@echo  Linking: am275x:r5fss1-1:freertos:ti-arm-clang $@ ...
	$(LNK) $(LNKOPTFLAGS) $(LFLAGS) $(LIBS_PATH) -Wl,-m=$(basename $@).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(LIBS) $(LNK_FILES) -Wl,--xml_link_info=$(basename $@).lnkxml
	@echo  Linking: am275x:r5fss1-1:freertos:ti-arm-clang $@ Done !!!
	@echo  .

coreout: $(COREOUTNAME)
$(COREOUTNAME): linker_optishare.cmd $(SYSTEM_COMMAND)
	@echo  .
	@echo  Relinking Linking: am275x:r5fss1-1:freertos:ti-arm-clang $@ with OptiShare SSO..
	$(LNK) $(LNKOPTFLAGS) $(LFLAGS) $(LIBS_PATH) -Wl,-m=$(basename $@).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(LIBS) $(LNK_FILES_OPTISHARE) -Wl,--xml_link_info=$(basename $@).lnkxml -Wl,--import_sso=$(SSO_PATH)
	@echo  Relinking with optishare: am275x:r5fss1-1:freertos:ti-arm-clang $@ Done !!!
	@echo  .
	$(PYTHON) $(MCELF_IMAGE_GEN) $(CORE_IMG_OPTISHARE_ARGS) --output=$(MULTI_CORE_BOOTIMAGE_NAME_MCELF_OPTISHARE) --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION)
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(MULTI_CORE_BOOTIMAGE_NAME_MCELF_OPTISHARE) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(MULTI_CORE_BOOTIMAGE_NAME_MCELF_OPTISHARE_HS_FS) --keyversion $(VERSION)
	@echo  optishare.out to optishare.mcelf is generated

linker_optishare.cmd: $(OPTISHARE_MEMMAP)
	@echo  Generating optishare linker: $(CORE_NAME) ...
	$(PYTHON) $(OPTISHARE_GEN_SCRIPT) --core $(CORE_NAME) --memmap $(OPTISHARE_MEMMAP) --output $@

clean:
	@echo  Cleaning: am275x:r5fss1-1:freertos:ti-arm-clang $(OUTNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(OUTNAME)
	$(RM) $(BOOTIMAGE_NAME)
	$(RM) $(BOOTIMAGE_NAME_XIP)
	$(RM) $(BOOTIMAGE_NAME_SIGNED)
	$(RM) $(BOOTIMAGE_NAME_HS)
	$(RM) $(BOOTIMAGE_NAME_HS_FS)
	$(RMDIR) generated/

scrub:
	@echo  Scrubing: am275x:r5fss1-1:freertos:ti-arm-clang ipc_notify_echo_optishare ...
	$(RMDIR) obj
ifeq ($(OS),Windows_NT)
	$(RM) \*.out
	$(RM) \*.map
	$(RM) \*.lnkxml
	$(RM) \*.ossr
	$(RM) \*.mcelf*
	$(RM) \*.tiimage*
	$(RM) \*.bin
else
	$(RM) *.out
	$(RM) *.map
	$(RM) *.lnkxml
	$(RM) *.ossr
	$(RM) *.mcelf*
	$(RM) *.tiimage*
	$(RM) *.bin
endif
	$(RMDIR) generated

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR) $@

.NOTPARALLEL:

.INTERMEDIATE: syscfg
$(SYSCFG_GEN_FILES): syscfg

syscfg: ../example.syscfg
	@echo Generating SysConfig files ...
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --product $(SYSCFG_SDKPRODUCT) --device AM275x --context r5fss1-1 --part AM2754 --package ANJ --output generated/ ../example.syscfg

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device AM275x --context r5fss1-1 --part AM2754 --package ANJ --output generated/  ../example.syscfg

#
# Generation of boot image which can be loaded by Secondary Boot Loader (SBL)
#
ifeq ($(OS),Windows_NT)
EXE_EXT=.exe
endif
ifeq ($(OS),Windows_NT)
  BOOTIMAGE_CERT_GEN_CMD=powershell -executionpolicy unrestricted -command $(MCU_PLUS_SDK_PATH)/tools/boot/signing/x509CertificateGen.ps1
else
  BOOTIMAGE_CERT_GEN_CMD=$(MCU_PLUS_SDK_PATH)/tools/boot/signing/x509CertificateGen.sh
endif
BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(PROFILE).txt

BOOTIMAGE_CERT_KEY=$(APP_SIGNING_KEY)

BOOTIMAGE_CORE_ID_wkup-r5fss0-0 = 0
BOOTIMAGE_CORE_ID_r5fss0-0      = 1
BOOTIMAGE_CORE_ID_r5fss0-1      = 2
BOOTIMAGE_CORE_ID_r5fss1-0      = 3
BOOTIMAGE_CORE_ID_r5fss1-1      = 4
BOOTIMAGE_CORE_ID_c75ss0-0      = 5
BOOTIMAGE_CORE_ID_c75ss1-0      = 6
BOOTIMAGE_CORE_ID_hsm-m4fss0-0  = 7
SBL_RUN_ADDRESS=0x72000000
SBL_DEV_ID=55

MCELF_IMAGE_GEN = $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreELFImageGen/genimage.py
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

ifeq ($(OS),Windows_NT)
  XIPGEN_CMD=$(MCU_PLUS_SDK_PATH)/tools/boot/xipGen/xipGen.exe
else
  XIPGEN_CMD=$(MCU_PLUS_SDK_PATH)/tools/boot/xipGen/xipGen.out
endif

MULTI_CORE_IMAGE_PARAMS = \
    $(BOOTIMAGE_CORE_ID_r5fss1-1):$(OUTNAME) \

MCELF_XIP_RANGE?=0x60100000:0x60200000

CORE_IMG_OPTISHARE_ARGS :=

CORE_OPTISHARE_IMG=ipc_notify_echo_optishare.$(PROFILE).optishare.out 
CORE_IMG_OPTISHARE_ARGS +=--core-img=$(BOOTIMAGE_CORE_ID_r5fss1-1):$(CORE_OPTISHARE_IMG)

CORE_NAME := r5fss1-1
OPTISHARE_GEN_SCRIPT := $(abspath ../../system_freertos/gen_linker_optishare.py)
OPTISHARE_MEMMAP     := $(abspath ../../system_freertos/optishare_memmap.json)

$(BOOTIMAGE_NAME): $(OUTNAME)
	@echo  Boot image: am275x:r5fss1-1:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$@ ...
ifneq ($(OS),Windows_NT)
	$(CHMOD) a+x $(XIPGEN_CMD)
endif
	$(PYTHON) $(MCELF_IMAGE_GEN) --core-img=$(MULTI_CORE_IMAGE_PARAMS) --output=$(BOOTIMAGE_NAME) --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION)
# Sign the appimage for HS-FS using appimage signing script
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(BOOTIMAGE_NAME_HS_FS) --keyversion $(VERSION)
	@echo  Boot image: am275x:r5fss1-1:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	@echo  Boot image: am275x:r5fss1-1:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS_FS) Done !!!
	@echo  .

$(BOOTIMAGE_NAME_HS): $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --key $(APP_SIGNING_KEY) --output $(BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
else
	@echo Boot image signing: Encryption is enabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
	$(RM) $(BOOTIMAGE_NAME)-enc
endif
	@echo  Boot image: am275x:r5fss1-1:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS) Done !!!
	@echo  .
endif
-include $(addprefix $(OBJDIR)/, $(DEPS))
