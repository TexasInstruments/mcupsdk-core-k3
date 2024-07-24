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

OUTNAME:=avtp_apps.$(PROFILE).out

BOOTIMAGE_PATH=$(abspath .)
BOOTIMAGE_NAME:=avtp_apps.$(PROFILE).appimage
BOOTIMAGE_NAME_XIP:=avtp_apps.$(PROFILE).appimage_xip
BOOTIMAGE_NAME_SIGNED:=avtp_apps.$(PROFILE).appimage.signed
BOOTIMAGE_RPRC_NAME:=avtp_apps.$(PROFILE).rprc
BOOTIMAGE_RPRC_NAME_XIP:=avtp_apps.$(PROFILE).rprc_xip
BOOTIMAGE_RPRC_NAME_TMP:=avtp_apps.$(PROFILE).rprc_tmp
BOOTIMAGE_NAME_HS:=avtp_apps.$(PROFILE).appimage.hs
BOOTIMAGE_NAME_HS_FS:=avtp_apps.$(PROFILE).appimage.hs_fs
TARGETS := $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
   TARGETS += $(BOOTIMAGE_NAME_HS)
endif

FILES_common := \
	gptp_init.c \
	default_flow_cfg.c \
	tsninit.c \
	avtp_init.c \
	debug_log.c \
	enetapp_cpsw.c \
	tsnapp_cpsw_main.c \
	default_flow_cpsw.c \
	main.c \
	avtp_testclient.c \
	ti_drivers_config.c \
	ti_drivers_open_close.c \
	ti_board_config.c \
	ti_board_open_close.c \
	ti_dpl_config.c \
	ti_pinmux_config.c \
	ti_power_clock_config.c \
    ti_enet_config.c \
    ti_enet_open_close.c \
    ti_enet_soc.c \
    ti_enet_lwipif.c \

FILES_PATH_common = \
	.. \
	../../.. \
	../../../.. \
	../../../../nrt_flow \
	generated \

INCLUDES_common := \
	-I${CG_TOOL_ROOT}/include/c \
	-I${MCU_PLUS_SDK_PATH}/source \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/utils \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/utils/include \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/utils/V3 \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/core \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/phy \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62ax \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include \
	-I${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include/mdio/V4 \
	-I${MCU_PLUS_SDK_PATH}/examples/networking/tsn \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_inc \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_inc/tsn_l2 \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_unibase \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/tilld \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_combase/tilld/sitara \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/gptpconf \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf \
	-I${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs \
	-Igenerated \

DEFINES_common := \
	-DSOC_AM62AX \
	-DENET_ENABLE_PER_CPSW=1 \
	-DPRINT_FORMAT_NO_WARNING \
	-DSITARA \
	-DAVTP_TESTCLIENT_MAIN=avtp_testclient \
	-DNO_GETOPT_LONG=1 \
	-DUB_LOGCAT=5 \
	-DHAVE_NO_SELECT=1 \
	-DHAVE_NO_POSIX_CLOCK=1 \
	-DAVTP_ENABLED=1 \
	-DAVTP_HAVE_NO_SIGNAL=1 \
	-DGPTP_ENABLED=1 \
	-DAVTP_TALKER_ENABLED=1 \
	-DAVTP_LISTENER_ENABLED=1 \
	-DAVTP_TALKER_NUM=1 \
	-DAVTP_LISTENER_NUM=1 \

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
	--include tsn_buildconf/sitara_buildconf.h \

CFLAGS_release := \
	-Os \
	-Oz \
	-flto \

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

LNK_FILES_common = \
	linker.cmd \

LIBS_PATH_common = \
	-Wl,-igenerated \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/board/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/networking/enet/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/networking/tsn/lib \
	-Wl,-i${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_lib \
	-Wl,-i${CG_TOOL_ROOT}/lib \

LIBS_common = \
	-lfreertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-ldrivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-lenet-cpsw.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-lboard.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-llibc.a \
	-llibsysbm.a \
	-ltsn_combase-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-ltsn_unibase-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-ltsn_gptp-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-ltsn_uniconf-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	-ltsn_l2-freertos.am62ax.r5f.ti-arm-clang.lib \
	-llibc.a \
	-llibsysbm.a \

LFLAGS_common = \
	-Wl,--diag_suppress=10063 \
	-Wl,--priority \
	-Wl,--ram_model \
	-Wl,--reread_libs \
	-Wl,--zero_init=on \
	-Wl,--use_memset=fast \
	-Wl,--use_memcpy=fast \

LNKOPTFLAGS_release = \
	       -mcpu=cortex-r5 \
	       -mfloat-abi=hard \
	       -mfpu=vfpv3-d16 \
	       -mthumb \
	       -Oz \
	       -flto \

LIBS_NAME = \
	freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	enet-cpsw.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	libc.a \
	libsysbm.a \
	tsn_combase-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	tsn_unibase-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	tsn_gptp-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	tsn_uniconf-freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib \
	tsn_l2-freertos.am62ax.r5f.ti-arm-clang.lib \
	libc.a \
	libsysbm.a \

LIBS_PATH_NAME = \
	generated \
	${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	${MCU_PLUS_SDK_PATH}/source/board/lib \
	${MCU_PLUS_SDK_PATH}/source/networking/enet/lib \
	${MCU_PLUS_SDK_PATH}/source/networking/tsn/lib \
	${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_lib \
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
	@echo  Compiling: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(OUTNAME): $<
	$(CC) -c $(CFLAGS) $(INCLUDES) $(DEFINES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.obj %.obj: %.S
	@echo  Compiling: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(LIBNAME): $<
	$(CC) -c $(CFLAGS) -o $(OBJDIR)/$@ $<

all: $(TARGETS)

SYSCFG_GEN_FILES=generated/ti_drivers_config.c generated/ti_drivers_config.h
SYSCFG_GEN_FILES+=generated/ti_drivers_open_close.c generated/ti_drivers_open_close.h
SYSCFG_GEN_FILES+=generated/ti_dpl_config.c generated/ti_dpl_config.h
SYSCFG_GEN_FILES+=generated/ti_pinmux_config.c generated/ti_power_clock_config.c
SYSCFG_GEN_FILES+=generated/ti_board_config.c generated/ti_board_config.h
SYSCFG_GEN_FILES+=generated/ti_board_open_close.c generated/ti_board_open_close.h
SYSCFG_GEN_FILES+=generated/ti_enet_config.c generated/ti_enet_config.h
SYSCFG_GEN_FILES+=generated/ti_enet_open_close.c generated/ti_enet_open_close.h
SYSCFG_GEN_FILES+=generated/ti_enet_soc.c
SYSCFG_GEN_FILES+=generated/ti_enet_lwipif.c generated/ti_enet_lwipif.h

$(OUTNAME): syscfg $(SYSCFG_GEN_FILES) $(OBJS) $(LNK_FILES) $(LIBS_NAME)
	@echo  .
	@echo  Linking: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $@ ...
	$(LNK) $(LNKOPTFLAGS) $(LFLAGS) $(LIBS_PATH) -Wl,-m=$(basename $@).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(LIBS) $(LNK_FILES)
	@echo  Linking: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $@ Done !!!
	@echo  .

clean:
	@echo  Cleaning: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(OUTNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(OUTNAME)
	$(RM) $(BOOTIMAGE_NAME)
	$(RM) $(BOOTIMAGE_NAME_XIP)
	$(RM) $(BOOTIMAGE_NAME_SIGNED)
	$(RM) $(BOOTIMAGE_NAME_HS)
	$(RM) $(BOOTIMAGE_NAME_HS_FS)
	$(RM) $(BOOTIMAGE_RPRC_NAME)
	$(RM) $(BOOTIMAGE_RPRC_NAME_XIP)
	$(RMDIR) generated/

scrub:
	@echo  Scrubing: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang avtp_apps ...
	$(RMDIR) obj
ifeq ($(OS),Windows_NT)
	$(RM) \*.out
	$(RM) \*.map
	$(RM) \*.appimage*
	$(RM) \*.rprc*
	$(RM) \*.tiimage*
	$(RM) \*.bin
else
	$(RM) *.out
	$(RM) *.map
	$(RM) *.appimage*
	$(RM) *.rprc*
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
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --product $(SYSCFG_SDKPRODUCT) --device AM62Ax --context mcu-r5fss0-0 --part Default --package AMB --output generated/ ../example.syscfg

syscfg-gui:
	$(SYSCFG_NWJS) $(SYSCFG_PATH) --product $(SYSCFG_SDKPRODUCT) --device AM62Ax --context mcu-r5fss0-0 --part Default --package AMB --output generated/  ../example.syscfg

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

BOOTIMAGE_CORE_ID_a53ss0-0 = 0
BOOTIMAGE_CORE_ID_a53ss0-1 = 1
BOOTIMAGE_CORE_ID_a53ss1-0 = 2
BOOTIMAGE_CORE_ID_a53ss1-1 = 3
BOOTIMAGE_CORE_ID_r5fss0-0 = 4
BOOTIMAGE_CORE_ID_mcu-r5fss0-0 = 5
BOOTIMAGE_CORE_ID_hsm-m4fss0-0 = 6
BOOTIMAGE_CORE_ID_c75ss0-0 = 7
SBL_RUN_ADDRESS=0x43C00000
SBL_DEV_ID=55

MULTI_CORE_IMAGE_GEN = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/multicoreImageGen.js
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

ifeq ($(OS),Windows_NT)
  XIPGEN_CMD=$(MCU_PLUS_SDK_PATH)/tools/boot/xipGen/xipGen.exe
else
  XIPGEN_CMD=$(MCU_PLUS_SDK_PATH)/tools/boot/xipGen/xipGen.out
endif

MULTI_CORE_IMAGE_PARAMS = \
	$(BOOTIMAGE_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_mcu-r5fss0-0) \

MULTI_CORE_IMAGE_PARAMS_XIP = \
	$(BOOTIMAGE_RPRC_NAME_XIP)@$(BOOTIMAGE_CORE_ID_mcu-r5fss0-0) \

$(BOOTIMAGE_NAME): $(OUTNAME)
	@echo  Boot image: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$@ ...
ifneq ($(OS),Windows_NT)
	$(CHMOD) a+x $(XIPGEN_CMD)
endif
	$(OUTRPRC_CMD) $(OUTNAME) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(COPY) $(BOOTIMAGE_RPRC_NAME) $(BOOTIMAGE_RPRC_NAME_TMP)
	$(RM) $(BOOTIMAGE_RPRC_NAME)
	$(XIPGEN_CMD) -i $(BOOTIMAGE_RPRC_NAME_TMP) -o $(BOOTIMAGE_RPRC_NAME) -x $(BOOTIMAGE_RPRC_NAME_XIP) --flash-start-addr 0x60000000 -v > $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(BOOTIMAGE_NAME) $(MULTI_CORE_IMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(BOOTIMAGE_NAME_XIP) $(MULTI_CORE_IMAGE_PARAMS_XIP) >> $(BOOTIMAGE_TEMP_OUT_FILE)
# Sign the appimage for HS-FS using appimage signing script
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(BOOTIMAGE_NAME_HS_FS) --keyversion $(VERSION)
	$(RM) $(BOOTIMAGE_RPRC_NAME_TMP)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo  Boot image: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	@echo  Boot image: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS_FS) Done !!!
	@echo  .

$(BOOTIMAGE_NAME_HS): $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
else
	@echo Boot image signing: Encryption is enabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(BOOTIMAGE_NAME) --authtype 0  --loadaddr 84000000 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(BOOTIMAGE_NAME_HS) --keyversion $(VERSION)
	$(RM) $(BOOTIMAGE_NAME)-enc
endif
	@echo  Boot image: am62ax:mcu-r5fss0-0:freertos:ti-arm-clang $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS) Done !!!
	@echo  .
endif
-include $(addprefix $(OBJDIR)/, $(DEPS))
