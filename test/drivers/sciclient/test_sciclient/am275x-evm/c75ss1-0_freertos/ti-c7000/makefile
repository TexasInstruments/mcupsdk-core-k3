#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

CG_TOOL_ROOT=$(CGT_TI_C7000_PATH)

CC=$(CG_TOOL_ROOT)/bin/cl7x
LNK=$(CG_TOOL_ROOT)/bin/cl7x
STRIP=$(CG_TOOL_ROOT)/bin/strip7x
OBJCOPY=$(CG_TOOL_ROOT)/bin/
ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

PROFILE?=release
ConfigName:=$(PROFILE)

OUTNAME:=test_functional_sciclient.$(PROFILE).out

BOOTIMAGE_PATH=$(abspath .)
BOOTIMAGE_NAME:=test_functional_sciclient.$(PROFILE).mcelf
BOOTIMAGE_NAME_XIP:=test_functional_sciclient.$(PROFILE).mcelf_xip
BOOTIMAGE_NAME_SIGNED:=test_functional_sciclient.$(PROFILE).mcelf.signed
BOOTIMAGE_NAME_HS:=test_functional_sciclient.$(PROFILE).mcelf.hs
BOOTIMAGE_NAME_HS_FS:=test_functional_sciclient.$(PROFILE).mcelf.hs_fs
TARGETS := $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
   TARGETS += $(BOOTIMAGE_NAME_HS)
endif

FILES_common := \
	test_sciclient_intr_polling.c \
	test_sciclient_lpm.c \
	test_sciclient_pm.c \
	test_sciclient_rm.c \
	test_sciclient_sec.c \
	test_sciclient_wrapper.c \
	test_sciclient_procboot.c \
	test_sciclient_multithread.c \
	test_sciclient.c \
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
	../../../.. \
	generated \

INCLUDES_common := \
	-I${CG_TOOL_ROOT}/include \
	-I${MCU_PLUS_SDK_PATH}/source \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x \
	-I${MCU_PLUS_SDK_PATH}/test/unity/ \
	-Igenerated \

DEFINES_common := \
	-DSOC_AM275X \
	-DCORE_C7 \
	-DSOC_AM275X \
	-DSCICLIENT_INTERRUPT_MODE \

CFLAGS_common := \
	-mv7524 \
	-q \
	-mo \
	-pden \
	-pds=238 \
	-pds=880 \
	-pds1110 \
	--disable_inlining \
	-ea.se71 \
	--emit_warnings_as_errors \
	--diag_suppress=770 \
	--diag_suppress=69 \
	--diag_suppress=70 \
	-DBUILD_C7X \
	-DBUILD_C7X_1 \
	-DSCICLIENT_MULTITHREAD \
	-DSKIP_SCICLIENT \

CFLAGS_debug := \
	-Dxdc_target_name__=C71 \
	-D_DEBUG_=1 \
	--opt_level=0 \
	--symdebug:dwarf \

CFLAGS_release := \
	-Dxdc_target_name__=C71 \
	--opt_level=3 \
	--symdebug:none \

LNK_FILES_common = \
	linker.cmd \

LIBS_PATH_common = \
	-i${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	-i${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	-i${MCU_PLUS_SDK_PATH}/test/unity/lib \
	-i${CG_TOOL_ROOT}/lib \

LIBS_common = \
	-lfreertos.am275x.c75x.ti-c7000.${ConfigName}.lib \
	-ldrivers.am275x.c75x.ti-c7000.${ConfigName}.lib \
	-lunity.am275x.c75x.ti-c7000.${ConfigName}.lib \
	-llibc.a \

LFLAGS_common = \
	-z \
	--emit_warnings_as_errors \
	--diag_suppress=10063 \
	--ram_model \
	--warn_sections \
	-x \


LIBS_NAME = \
	freertos.am275x.c75x.ti-c7000.${ConfigName}.lib \
	drivers.am275x.c75x.ti-c7000.${ConfigName}.lib \
	unity.am275x.c75x.ti-c7000.${ConfigName}.lib \
	libc.a \

LIBS_PATH_NAME = \
	${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	${MCU_PLUS_SDK_PATH}/test/unity/lib \
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
LNK_FILES := $(LNK_FILES_common) $(LNK_FILES_$(PROFILE))

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
	@echo  Compiling: am275x:c75ss1-0:freertos:ti-c7000 $(OUTNAME): $<
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -ppd=$(OBJDIR)/$(basename $@).d -ppa -fr=$(OBJDIR)/ -fc=$<

$(OBJDIR)/%.obj %.obj: %.S
	@echo  Compiling: am275x:c75ss1-0:freertos:ti-c7000 $(LIBNAME): $<
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -ppd=$(OBJDIR)/$(basename $@).d -ppa -fr=$(OBJDIR)/ -fa=$<

all: $(TARGETS)

SYSCFG_GEN_FILES=generated/ti_drivers_config.c generated/ti_drivers_config.h
SYSCFG_GEN_FILES+=generated/ti_drivers_open_close.c generated/ti_drivers_open_close.h
SYSCFG_GEN_FILES+=generated/ti_dpl_config.c generated/ti_dpl_config.h
SYSCFG_GEN_FILES+=generated/ti_pinmux_config.c generated/ti_power_clock_config.c
SYSCFG_GEN_FILES+=generated/ti_board_config.c generated/ti_board_config.h
SYSCFG_GEN_FILES+=generated/ti_board_open_close.c generated/ti_board_open_close.h

$(OUTNAME): syscfg $(SYSCFG_GEN_FILES) $(OBJS) $(LNK_FILES) $(LIBS_NAME)
	@echo  .
	@echo  Linking: am275x:c75ss1-0:freertos:ti-c7000 $@ ...
	$(LNK) $(LFLAGS) $(LIBS_PATH) -m=$(basename $@).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(LIBS) $(LNK_FILES)
	@echo  Linking: am275x:c75ss1-0:freertos:ti-c7000 $@ Done !!!
	@echo  .

clean:
	@echo  Cleaning: am275x:c75ss1-0:freertos:ti-c7000 $(OUTNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(OUTNAME)
	$(RM) $(BOOTIMAGE_NAME)
	$(RM) $(BOOTIMAGE_NAME_XIP)
	$(RM) $(BOOTIMAGE_NAME_SIGNED)
	$(RM) $(BOOTIMAGE_NAME_HS)
	$(RM) $(BOOTIMAGE_NAME_HS_FS)
	$(RMDIR) generated/

scrub:
	@echo  Scrubing: am275x:c75ss1-0:freertos:ti-c7000 test_functional_sciclient ...
	$(RMDIR) obj
ifeq ($(OS),Windows_NT)
	$(RM) \*.out
	$(RM) \*.map
	$(RM) \*.mcelf*
	$(RM) \*.tiimage*
	$(RM) \*.bin
else
	$(RM) *.out
	$(RM) *.map
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
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --product $(SYSCFG_SDKPRODUCT) --device AM275x --context c75ss1-0 --part AM2754 --package ANJ --output generated/ ../example.syscfg

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device AM275x --context c75ss1-0 --part AM2754 --package ANJ --output generated/  ../example.syscfg

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
    $(BOOTIMAGE_CORE_ID_c75ss1-0):$(OUTNAME) \

MCELF_XIP_RANGE?=0x60100000:0x60200000

$(BOOTIMAGE_NAME): $(OUTNAME)
	@echo  Boot image: am275x:c75ss1-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$@ ...
ifneq ($(OS),Windows_NT)
	$(CHMOD) a+x $(XIPGEN_CMD)
endif
	$(PYTHON) $(MCELF_IMAGE_GEN) --core-img=$(MULTI_CORE_IMAGE_PARAMS) --output=$(BOOTIMAGE_NAME) --xip=$(MCELF_XIP_RANGE) --sw_version=$(SW_VERSION)
# Sign the appimage for HS-FS using appimage signing script
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(BOOTIMAGE_NAME_HS_FS) --keyversion $(VERSION)
	@echo  Boot image: am275x:c75ss1-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	@echo  Boot image: am275x:c75ss1-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS_FS) Done !!!
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
	@echo  Boot image: am275x:c75ss1-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS) Done !!!
	@echo  .
endif
-include $(addprefix $(OBJDIR)/, $(DEPS))
