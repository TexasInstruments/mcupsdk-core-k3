
export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include board/$(BOARD)/config.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

CG_TOOL_ROOT=$(CGT_TI_ARM_CLANG_PATH)

APP = board/$(BOARD)/$(APP_NAME)
APPIMAGE = board/$(BOARD)/$(APPIMAGE_NAME)
APPIMAGE_HS = $(APPIMAGE).hs
APPIMAGE_HS_FS = $(APPIMAGE).hs_fs

ELF =  $(APP)
RPRC_NAME = $(addsuffix .rprc, $(basename $(APP_NAME)))
RPRC = board/$(BOARD)/$(RPRC_NAME)
APPIMAGE_PARAMS = $(BOOTIMAGE_CORE_ID) $(RPRC)

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
all: $(APPIMAGE_HS)
else
all: $(APPIMAGE) $(APPIMAGE_HS_FS)
endif

ifeq ($(DEVICE_TYPE),HS)
$(APPIMAGE_HS): $(RPRC)
else
$(APPIMAGE): $(RPRC)
$(APPIMAGE_HS_FS): $(RPRC)
endif
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(APPIMAGE) $(APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)

ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
	#
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(APPIMAGE_HS)
else
	@echo Boot image signing: Encryption is enabled.
	#
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(APPIMAGE_HS)
	$(RM) $(APPIMAGE)-enc
endif
else
	#
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(APPIMAGE_HS_FS)
endif

	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(RPRC):
	@echo Creating ATF RPRC image
	$(OUTRPRC_CMD) $(ELF) $(SW_VERSION)>> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(COPY) $(RPRC_NAME) $(RPRC)  >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(RPRC_NAME)

clean:
	@echo Cleaning: $(APPIMAGE)
	$(RM) $(APPIMAGE)*
	$(RM) $(RPRC)
