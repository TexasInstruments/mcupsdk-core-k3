
export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include board/$(BOARD)/config.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

CG_TOOL_ROOT=$(CGT_TI_ARM_CLANG_PATH)

DM_APP = board/$(BOARD)/$(DM_APP_NAME)
DM_APPIMAGE = board/$(BOARD)/$(DM_APPIMAGE_NAME)
DM_APPIMAGE_HS = $(DM_APPIMAGE).hs
DM_APPIMAGE_HS_FS = $(DM_APPIMAGE).hs_fs

DM_ELF =  $(DM_APP)
DM_RPRC_NAME = $(addsuffix .rprc, $(basename $(DM_APP_NAME)))
DM_RPRC = board/$(BOARD)/$(DM_RPRC_NAME)
DM_APPIMAGE_PARAMS = $(BOOTIMAGE_CORE_ID_DM) $(DM_RPRC)

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
ifeq ($(DEVICE_TYPE),HS)
all: $(DM_APPIMAGE_HS)
else
all: $(DM_APPIMAGE) $(DM_APPIMAGE_HS_FS)
endif

ifeq ($(DEVICE_TYPE),HS)
$(DM_APPIMAGE_HS): $(DM_RPRC)
else
$(DM_APPIMAGE): $(DM_RPRC)
$(DM_APPIMAGE_HS_FS): $(DM_RPRC)
endif
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(DM_APPIMAGE) $(DM_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)

ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(DM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --output $(DM_APPIMAGE_HS)
else
	@echo Boot image signing: Encryption is enabled.
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(DM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(DM_APPIMAGE_HS)
	$(RM) $(DM_APPIMAGE)-enc
endif
	$(RM) $(DM_APPIMAGE)
	$(RM) $(DM_APPIMAGE_HS_FS)
else
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(DM_APPIMAGE) --authtype 1 --key $(APP_SIGNING_KEY) --output $(DM_APPIMAGE_HS_FS)
	$(RM) $(DM_APPIMAGE_HS)
endif

	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(DM_RPRC):
	@echo Creating ATF RPRC image
	$(OUTRPRC_CMD) $(DM_ELF) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(COPY) $(DM_RPRC_NAME) $(DM_RPRC)  >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(DM_RPRC_NAME)

clean:
	@echo Cleaning: $(DM_APPIMAGE)
	$(RM) $(DM_APPIMAGE)*
	$(RM) $(DM_RPRC)
