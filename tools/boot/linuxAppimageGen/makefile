export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include board/$(BOARD)/config.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

LINUX_IMAGE_LIST = \
	$(ATF_BIN_NAME) \
	$(OPTEE_BIN_NAME) \
	$(SPL_BIN_NAME)

ATF_RPRC = $(addsuffix .rprc, $(basename $(ATF_BIN_NAME)))
OPTEE_RPRC := $(addsuffix .rprc, $(basename $(OPTEE_BIN_NAME)))
SPL_RPRC := $(addsuffix .rprc, $(basename $(SPL_BIN_NAME)))

ATF_ELF = $(addsuffix .elf, $(basename $(ATF_BIN_NAME)))
OPTEE_ELF := $(addsuffix .elf, $(basename $(OPTEE_BIN_NAME)))
SPL_ELF := $(addsuffix .elf, $(basename $(SPL_BIN_NAME)))

RPRC_LIST = \
	$(ATF_RPRC) \
	$(OPTEE_RPRC) \
	$(SPL_RPRC)

ELF_FILE_LIST = $(RPRC_LIST:.rprc=.elf)

COMBINED_APPIMAGE_PARAMS = \
	$(BOOTIMAGE_CORE_ID_a53ss0-0) $(ATF_RPRC) \
	$(BOOTIMAGE_CORE_ID_load_only) $(OPTEE_RPRC) \
	$(BOOTIMAGE_CORE_ID_load_only) $(SPL_RPRC)

BOOTIMAGE_TEMP_OUT_FILE=temp_stdout.txt


BOOTIMAGE_CORE_ID_load_only = 21
SBL_DEV_ID=55

MULTI_CORE_IMAGE_GEN=$(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/MulticoreImageGen$(EXE_EXT)
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js

#Path to the app image signing script
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

LINUX_BOOTIMAGE = board/$(BOARD)/$(LINUX_BOOTIMAGE_NAME)
LINUX_BOOTIMAGE_HS = $(LINUX_BOOTIMAGE).hs
LINUX_BOOTIMAGE_HS_FS = $(LINUX_BOOTIMAGE).hs_fs

#################################################################################
# Targets
#################################################################################
all: $(LINUX_BOOTIMAGE)

.INTERMEDIATE: $(RPRC_LIST) $(ELF_FILE_LIST)
$(LINUX_BOOTIMAGE): $(RPRC_LIST)
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(LINUX_BOOTIMAGE) $(COMBINED_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
ifeq ($(BOARD),am62x-sk)
ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(LINUX_BOOTIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --output $(LINUX_BOOTIMAGE_HS)
else
	@echo Boot image signing: Encryption is enabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(LINUX_BOOTIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(LINUX_BOOTIMAGE_HS)
	$(RM) $(LINUX_BOOTIMAGE)-enc
endif
	$(RM) $(LINUX_BOOTIMAGE)
endif
endif
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(ATF_RPRC): $(ATF_ELF)
	@echo Creating ATF RPRC image
	$(OUTRPRC_CMD) $(ATF_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(OPTEE_RPRC): $(OPTEE_ELF)
	@echo Creating OPTEE RPRC image
	$(OUTRPRC_CMD) $(OPTEE_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(SPL_RPRC): $(SPL_ELF)
	@echo Creating SPL RPRC image
	$(OUTRPRC_CMD) $(SPL_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(ATF_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(ATF_LOAD_ADDR) -e $(ATF_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(ATF_BIN_NAME) -o $(ATF_ELF)

$(OPTEE_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(OPTEE_LOAD_ADDR) -e $(OPTEE_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(OPTEE_BIN_NAME) -o $(OPTEE_ELF)

$(SPL_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(SPL_LOAD_ADDR) -e $(SPL_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(SPL_BIN_NAME) -o $(SPL_ELF)

clean:
	@echo Cleaning: $(LINUX_BOOTIMAGE)
	$(RM) $(LINUX_BOOTIMAGE)*
	#$(RM) *.elf
	$(RM) *.rprc