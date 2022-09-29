
export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include board/$(BOARD)/config.mak

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

QNX_IMAGE_LIST = \
	$(ATF_BIN_NAME) \
	$(OPTEE_BIN_NAME) \
	$(QNX_BIN_NAME)

ATF_RPRC = $(addsuffix .rprc, $(basename $(ATF_BIN_NAME)))
OPTEE_RPRC := $(addsuffix .rprc, $(basename $(OPTEE_BIN_NAME)))
QNX_RPRC := $(addsuffix .rprc, $(basename $(QNX_BIN_NAME)))

ATF_ELF = $(addsuffix .elf, $(basename $(ATF_BIN_NAME)))
OPTEE_ELF := $(addsuffix .elf, $(basename $(OPTEE_BIN_NAME)))
QNX_ELF := $(addsuffix .elf, $(basename $(QNX_BIN_NAME)))

RPRC_LIST = \
	$(ATF_RPRC) \
	$(OPTEE_RPRC) \
	$(QNX_RPRC)

ELF_FILE_LIST = $(RPRC_LIST:.rprc=.elf)

COMBINED_APPIMAGE_PARAMS = \
	$(BOOTIMAGE_CORE_ID_a53ss0-0) $(ATF_RPRC) \
	$(BOOTIMAGE_CORE_ID_load_only) $(OPTEE_RPRC) \
	$(BOOTIMAGE_CORE_ID_load_only) $(QNX_RPRC)

BOOTIMAGE_TEMP_OUT_FILE=temp_stdout.txt


BOOTIMAGE_CORE_ID_load_only = 21
SBL_DEV_ID=55

MULTI_CORE_IMAGE_GEN=$(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/MulticoreImageGen$(EXE_EXT)
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js

QNX_BOOTIMAGE = board/$(BOARD)/$(QNX_BOOTIMAGE_NAME)
#################################################################################
# Targets
#################################################################################
all: $(QNX_BOOTIMAGE)

.INTERMEDIATE: $(RPRC_LIST) $(ELF_FILE_LIST)
$(QNX_BOOTIMAGE): $(RPRC_LIST)
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(QNX_BOOTIMAGE) $(COMBINED_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(ATF_RPRC): $(ATF_ELF)
	@echo Creating ATF RPRC image
	$(OUTRPRC_CMD) $(ATF_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(OPTEE_RPRC): $(OPTEE_ELF)
	@echo Creating OPTEE RPRC image
	$(OUTRPRC_CMD) $(OPTEE_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(QNX_RPRC): $(QNX_ELF)
	@echo Creating QNX RPRC image
	$(OUTRPRC_CMD) $(QNX_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(ATF_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(ATF_LOAD_ADDR) -e $(ATF_LOAD_ADDR) $(PSDK_QNX_PREBUILT_IMAGES)/$(ATF_BIN_NAME) -o $(ATF_ELF)

$(OPTEE_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(OPTEE_LOAD_ADDR) -e $(OPTEE_LOAD_ADDR) $(PSDK_QNX_PREBUILT_IMAGES)/$(OPTEE_BIN_NAME) -o $(OPTEE_ELF)

$(QNX_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(QNX_LOAD_ADDR) -e $(QNX_LOAD_ADDR) $(QNX_IFS_PATH)/$(QNX_BIN_NAME) -o $(QNX_ELF)

clean:
	@echo Cleaning: $(QNX_BOOTIMAGE)
	$(RM) $(QNX_BOOTIMAGE)
	$(RM) *.elf
	$(RM) *.rprc
