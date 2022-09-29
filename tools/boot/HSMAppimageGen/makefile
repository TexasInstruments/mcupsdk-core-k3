export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include board/$(BOARD)/config.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

HSM_BINARY = board/$(BOARD)/$(HSM_BINARY_NAME)
HSM_APPIMAGE = board/$(BOARD)/$(HSM_APPIMAGE_NAME)
HSM_APPIMAGE_HS = $(HSM_APPIMAGE).hs
HSM_APPIMAGE_HS_FS = $(HSM_APPIMAGE).hs_fs

HSM_RPRC_NAME = $(addsuffix .rprc, $(basename $(HSM_BINARY_NAME)))
HSM_ELF=  $(addsuffix .elf, $(basename $(HSM_BINARY_NAME)))
HSM_RPRC = board/$(BOARD)/$(HSM_RPRC_NAME)
HSM_APPIMAGE_PARAMS = $(BOOTIMAGE_CORE_ID_HSM) $(HSM_RPRC)

BOOTIMAGE_TEMP_OUT_FILE=temp_stdout.txt

#Path to the app image signing script
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

MULTI_CORE_IMAGE_GEN=$(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/MulticoreImageGen$(EXE_EXT)
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js

ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

#################################################################################
# Targets
#################################################################################
all: $(HSM_APPIMAGE)

.INTERMEDIATE: $(HSM_ELF)

$(HSM_APPIMAGE): $(HSM_RPRC)
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(HSM_APPIMAGE) $(HSM_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
ifeq ($(BOARD),am62x-sk)
ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --output $(HSM_APPIMAGE_HS)
else
	@echo Boot image signing: Encryption is enabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(HSM_APPIMAGE_HS)
	$(RM) $(HSM_APPIMAGE)-enc
endif
	$(RM) $(HSM_APPIMAGE)
else
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --output $(HSM_APPIMAGE_HS_FS)
	@echo $(APP_SIGNING_KEY)
endif
endif
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(HSM_RPRC): $(HSM_ELF)
	@echo Creating ATF RPRC image
	$(OUTRPRC_CMD) $(HSM_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(COPY) $(HSM_RPRC_NAME) $(HSM_RPRC) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM)	$(HSM_RPRC_NAME)

$(HSM_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(HSM_LOAD_ADDR) -e $(HSM_LOAD_ADDR) $(HSM_BINARY) -o $(HSM_ELF)


clean:
	@echo Cleaning: $(HSM_APPIMAGE)
	$(RM) $(HSM_APPIMAGE)*
	$(RM) $(HSM_RPRC)
	$(RM) *.elf
