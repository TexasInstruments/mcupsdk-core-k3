#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../../..)
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

OUTNAME:=dsp_edgeai.$(PROFILE).out

BOOTIMAGE_PATH=$(abspath .)
BOOTIMAGE_NAME:=dsp_edgeai.$(PROFILE).appimage
BOOTIMAGE_NAME_XIP:=dsp_edgeai.$(PROFILE).appimage_xip
BOOTIMAGE_NAME_SIGNED:=dsp_edgeai.$(PROFILE).appimage.signed
BOOTIMAGE_RPRC_NAME:=dsp_edgeai.$(PROFILE).rprc
BOOTIMAGE_RPRC_NAME_XIP:=dsp_edgeai.$(PROFILE).rprc_xip
BOOTIMAGE_RPRC_NAME_TMP:=dsp_edgeai.$(PROFILE).rprc_tmp
BOOTIMAGE_NAME_HS:=dsp_edgeai.$(PROFILE).appimage.hs
BOOTIMAGE_NAME_HS_FS:=dsp_edgeai.$(PROFILE).appimage.hs_fs
TARGETS := $(BOOTIMAGE_NAME)
ifeq ($(DEVICE_TYPE), HS)
   TARGETS += $(BOOTIMAGE_NAME_HS)
endif

FILES_common := \
	main.c \
	c7x_cxm.c \
	dual_task_main.c \
	tvm_service.c \
	dsp_service.c \
	compute_service.c \
	dyn_loader.c \
	tvm_model.c \
	shm_printf.c \
	tidl_support.c \
	dload.c \
	elf32.c \
	dload_endian.c \
	ArrayList.c \
	symtab.c \
	c70_dynamic.c \
	c70_reloc.c \
	dmautils_autoincrement_3d.c \
	udma.c \
	tvm_dsp_dma.c \
	ffi_types.c \
	object.c \
	array.c \
	ndarray.c \
	shape.c \
	constants.c \
	constants_c_api.c \
	stream.c \
	c7x_platform.c \
	memory_pool.c \
	tvm_int8_residual_add.c \
	ti_drivers_config.c \
	ti_drivers_open_close.c \
	ti_board_config.c \
	ti_board_open_close.c \
	ti_dpl_config.c \
	ti_pinmux_config.c \
	ti_power_clock_config.c \

FILES_cpp_common := \
	constants_loader.cpp \
	vm_builtins.cpp \
	storage.cpp \
	c_backend_api.cpp \
	registry.cpp \
	model.cpp \
	stft_istft_handler.cpp \
	stft_signal_chain.cpp \
	signal_chain_dispatch.cpp \
	arena_allocator.cpp \
	signal_chain_arena.cpp \
	stft_signal_chain_dccrn.cpp \
	stft_signal_chain_gtcrn.cpp \
	stft_signal_chain_gcrn.cpp \
	stft_signal_chain_vggish.cpp \
	stft_signal_chain_yamnet.cpp \
	mattrans_signal_chain.cpp \
	deinterleave_signal_chain.cpp \
	utils_handler.cpp \

FILES_PATH_common = \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/am62dx-evm/c75ss0-0_freertos \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/am62dx-evm \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD_SYM \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_DYN \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_REL \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dmautils \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/dma \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/ffi \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/container \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/constants \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/platform/c7x \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/platform/common \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/kernels \
	generated \

FILES_PATH_cpp_common = \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/constants \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/vm \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/ffi \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/registry \
	$(MCU_PLUS_SDK_PATH)/source/tvm/src/runtime/ti_dsp/cpp \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/dccrn \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/gtcrn \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/gcrn \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/vggish \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/yamnet \
	$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm/common/models/utils \

INCLUDES_common := \
	-I${CG_TOOL_ROOT}/include \
	-I${MCU_PLUS_SDK_PATH}/source \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x \
	-I${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/c75 \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/include \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/udma_standalone/include \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/udma_standalone \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/csl \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/udma/include \
	-I${MCU_PLUS_SDK_PATH}/source/drivers/hw_include \
	-I${MCU_PLUS_SDK_PATH}/source/audiolib/src \
	-I${MCU_PLUS_SDK_PATH}/source/tisp/includes \
	-I${MCU_PLUS_SDK_PATH}/source/tisp/src/common \
	-I${MCU_PLUS_SDK_PATH}/source/fftlib/src \
	-I${MCU_PLUS_SDK_PATH}/source/mathlib/src \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/dccrn \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/gtcrn \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/gcrn \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/vggish \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/yamnet \
	-I${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/utils \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/common \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/ffi \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/container \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/dlpack/include \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/constants \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/core \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/vm \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/registry \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/cpp \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform/common \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform/c7x \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/include \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD_API \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_DYN \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_REL \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/am62d \
	-I${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/dma \
	-Igenerated \

DEFINES_common := \
	-DSOC_AM62DX \
	-DBUILD_C7X \
	-DBUILD_C7X_1 \
	-DC70_TARGET \
	-DELF64=1 \
	-DHwI_bootToNonSecure__D=1 \
	-DMCU_PLUS_SDK \
	-DDMA_UTILS_STANDALONE \
	-DOS_FREERTOS \
	-DTVM_DSP_DEVICE_AM62DX \
	-DTVM_DSP_NO_EXCEPTIONS=1 \
	-DTVM_DSP_NO_THREADS=1 \
	-DTVM_DSP_TARGET_C7X \
	-D_SYS_BIOS \
	-DUSE_TIDL_RUNTIME=1 \

CFLAGS_common := \
	-mv7504 \
	-q \
	-pden \
	-pds=238 \
	-pds=880 \
	-pds1110 \
	-ea.se71 \
	--emit_warnings_as_errors \
	--diag_suppress=770 \
	--diag_suppress=69 \
	--diag_suppress=70 \
	-DBUILD_C7X \
	-DBUILD_C7X_1 \
	-mv7504 \
	-q \
	-pden \
	-pds=238 \
	-pds=880 \
	-pds1110 \
	-ea.se71 \
	--c99 \
	--diag_suppress=770 \
	--diag_suppress=69 \
	--diag_suppress=70 \
	--diag_suppress=2824 \
	--diag_suppress=1557 \
	--diag_suppress=1 \
	--diag_suppress=190 \
	--diag_suppress=225 \
	--diag_suppress=548 \
	-Dxdc_target_name__=C71 \
	--opt_level=2 \

CFLAGS_debug := \
	-Dxdc_target_name__=C71 \
	-D_DEBUG_=1 \
	--opt_level=0 \
	--symdebug:dwarf \

CFLAGS_release := \
	-Dxdc_target_name__=C71 \
	--symdebug:none \

LNK_FILES_common = \
	linker.cmd \

LIBS_PATH_common = \
	-i${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	-i${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	-i${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib \
	-i${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib \
	-i${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName} \
	-i${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName} \
	-i${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName} \
	-i${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName} \
	-i${MCU_PLUS_SDK_PATH}/source/mathlib/lib/${ConfigName} \
	-i${CG_TOOL_ROOT}/lib \
	-i${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_tidl_libs/ti_dl/lib/AM62A/dsp/algo/release \
	-i${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/contrib/tidl/c7x/7504_am62d \
	-i${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_mmalib_libs/lib/C7504/release \
	-i${CG_TOOL_ROOT}/lib \

LIBS_common = \
	-lfreertos.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	-ldrivers.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	-ludma.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	-ldmautils.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	-lTISP_C7504.lib \
	-lAUDIOLIB_C7504.lib \
	-lDSPLIB_C7504.lib \
	-lFFTLIB_C7504.lib \
	-lMATHLIB_C7504.lib \
	-llibc.a \
	-ltidl_algo.lib \
	-ltidl_priv.lib \
	-ltidl_custom.lib \
	-ltidl_kernels.lib \
	-ltidl_ref.lib \
	-ltidl_api.lib \
	-ltvm_crt.lib \
	-lmmalib_C7504.lib \
	-lmmalib_cn_C7504.lib \
	-lcommon_C7504.lib \
	-lperfEst_C7504.lib \
	-llibc.a \

LFLAGS_common = \
	-z \
	--emit_warnings_as_errors \
	--diag_suppress=10063 \
	--ram_model \
	--warn_sections \
	-x \
	--mapfile_contents=sym_defs \
	--reread_libs \
	--retain=TIDL_VISION_FXNS \


LIBS_NAME = \
	freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	udma.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	dmautils.am62dx.c75x.ti-c7000.${ConfigName}.lib \
	TISP_C7504.lib \
	AUDIOLIB_C7504.lib \
	DSPLIB_C7504.lib \
	FFTLIB_C7504.lib \
	MATHLIB_C7504.lib \
	libc.a \
	tidl_algo.lib \
	tidl_priv.lib \
	tidl_custom.lib \
	tidl_kernels.lib \
	tidl_ref.lib \
	tidl_api.lib \
	tvm_crt.lib \
	mmalib_C7504.lib \
	mmalib_cn_C7504.lib \
	common_C7504.lib \
	perfEst_C7504.lib \
	libc.a \

LIBS_PATH_NAME = \
	${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib \
	${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib \
	${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName} \
	${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName} \
	${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName} \
	${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName} \
	${MCU_PLUS_SDK_PATH}/source/mathlib/lib/${ConfigName} \
	${CG_TOOL_ROOT}/lib \
	${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_tidl_libs/ti_dl/lib/AM62A/dsp/algo/release \
	${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/contrib/tidl/c7x/7504_am62d \
	${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_mmalib_libs/lib/C7504/release \
	${CG_TOOL_ROOT}/lib \

FILES := $(FILES_common) $(FILES_$(PROFILE))
CPPFILES := $(FILES_cpp_common) $(FILES_cpp_$(PROFILE))
ASMFILES := $(ASMFILES_common) $(ASMFILES_$(PROFILE))
FILES_PATH := $(FILES_PATH_common) $(FILES_PATH_$(PROFILE))
CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
CPPFILES_PATH := $(FILES_PATH_cpp_common) $(FILES_PATH_$(PROFILE))
CPPFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE)) $(CFLAGS_cpp_common)
DEFINES := $(DEFINES_common) $(DEFINES_$(PROFILE))
INCLUDES := $(INCLUDES_common) $(INCLUDE_$(PROFILE))
LIBS := $(LIBS_common) $(LIBS_$(PROFILE))
LIBS_PATH := $(LIBS_PATH_common) $(LIBS_PATH_$(PROFILE))
LFLAGS := $(LFLAGS_common) $(LFLAGS_$(PROFILE))
LNK_FILES := $(LNK_FILES_common) $(LNK_FILES_$(PROFILE))

OBJDIR := obj/$(PROFILE)/
OBJS := $(FILES:%.c=%.obj)
OBJS += $(CPPFILES:%.cpp=%.obj)
OBJS += $(ASMFILES:%.S=%.obj)
DEPS := $(FILES:%.c=%.d)

vpath %.obj $(OBJDIR)
vpath %.c $(FILES_PATH)
vpath %.cpp $(CPPFILES_PATH)
vpath %.S $(FILES_PATH)
vpath %.lib $(LIBS_PATH_NAME)
vpath %.a $(LIBS_PATH_NAME)

$(OBJDIR)/%.obj %.obj: %.cpp
	@echo  Compiling: am62dx:c75ss0-0:freertos:ti-c7000 $(OUTNAME): $<
	$(CC) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -ppd=$(OBJDIR)/$(basename $@).d -ppa -fr=$(OBJDIR)/ -fp=$<

$(OBJDIR)/%.obj %.obj: %.c
	@echo  Compiling: am62dx:c75ss0-0:freertos:ti-c7000 $(OUTNAME): $<
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -ppd=$(OBJDIR)/$(basename $@).d -ppa -fr=$(OBJDIR)/ -fc=$<

$(OBJDIR)/%.obj %.obj: %.S
	@echo  Compiling: am62dx:c75ss0-0:freertos:ti-c7000 $(LIBNAME): $<
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
	@echo  Linking: am62dx:c75ss0-0:freertos:ti-c7000 $@ ...
	$(LNK) $(LFLAGS) $(LIBS_PATH) -m=$(basename $@).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(LIBS) $(LNK_FILES)
	$(RM) dsp_edgeai.c75ss0-0.${ConfigName}.strip.out
	$(STRIP) -p $@ -o=dsp_edgeai.c75ss0-0.${ConfigName}.strip.out
	@echo  Linking: am62dx:c75ss0-0:freertos:ti-c7000 $@ Done !!!
	@echo  .

clean:
	@echo  Cleaning: am62dx:c75ss0-0:freertos:ti-c7000 $(OUTNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(OUTNAME)
	$(RM) dsp_edgeai.c75ss0-0.${ConfigName}.strip.out
	$(RM) $(BOOTIMAGE_NAME)
	$(RM) $(BOOTIMAGE_NAME_XIP)
	$(RM) $(BOOTIMAGE_NAME_SIGNED)
	$(RM) $(BOOTIMAGE_NAME_HS)
	$(RM) $(BOOTIMAGE_NAME_HS_FS)
	$(RM) $(BOOTIMAGE_RPRC_NAME)
	$(RM) $(BOOTIMAGE_RPRC_NAME_XIP)
	$(RMDIR) generated/

scrub:
	@echo  Scrubing: am62dx:c75ss0-0:freertos:ti-c7000 dsp_edgeai ...
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
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --product $(SYSCFG_SDKPRODUCT) --device AM62Dx --context c75ss0-0 --part AM62D24-G --package ANF --output generated/ ../example.syscfg

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device AM62Dx --context c75ss0-0 --part AM62D24-G --package ANF --output generated/  ../example.syscfg

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
	$(BOOTIMAGE_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_c75ss0-0) \

MULTI_CORE_IMAGE_PARAMS_XIP = \
	$(BOOTIMAGE_RPRC_NAME_XIP)@$(BOOTIMAGE_CORE_ID_c75ss0-0) \

$(BOOTIMAGE_NAME): $(OUTNAME)
	@echo  Boot image: am62dx:c75ss0-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$@ ...
ifneq ($(OS),Windows_NT)
	$(CHMOD) a+x $(XIPGEN_CMD)
endif
	$(OUTRPRC_CMD) $(OUTNAME) $(SW_VERSION)>> $(BOOTIMAGE_TEMP_OUT_FILE)
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
	@echo  Boot image: am62dx:c75ss0-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
	@echo  Boot image: am62dx:c75ss0-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS_FS) Done !!!
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
	@echo  Boot image: am62dx:c75ss0-0:freertos:ti-c7000 $(BOOTIMAGE_PATH)/$(BOOTIMAGE_NAME_HS) Done !!!
	@echo  .
endif
-include $(addprefix $(OBJDIR)/, $(DEPS))
