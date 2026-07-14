export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62px))
BOARD?=$(DEVICE)-sk
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62dx am275x))
BOARD?=$(DEVICE)-evm
endif

include board/$(BOARD)/config.mak

OBJCOPY=$(CGT_TI_ARM_CLANG_PATH)/bin/tiarmobjcopy
CC=$(CGT_TI_ARM_CLANG_PATH)/bin/tiarmclang

HSM_BINARY = board/$(BOARD)/$(HSM_BINARY_NAME)
HSM_APPIMAGE = board/$(BOARD)/$(HSM_APPIMAGE_NAME)
HSM_APPIMAGE_HS = $(HSM_APPIMAGE).hs
HSM_APPIMAGE_HS_FS = $(HSM_APPIMAGE).hs_fs

HSM_ELF = $(addsuffix .elf, $(basename $(HSM_BINARY_NAME)))
HSM_TMP_ELF = $(addsuffix .tmp.elf, $(basename $(HSM_BINARY_NAME)))

#Path to the app image signing script
APP_IMAGE_SIGN_CMD = $(MCU_PLUS_SDK_PATH)/tools/boot/signing/appimage_x509_cert_gen.py

MCELF_IMAGE_GEN = $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreELFImageGen/genimage.py

MULTI_CORE_IMAGE_PARAMS = $(BOOTIMAGE_CORE_ID_HSM):$(HSM_ELF)

ifeq ($(OS), Windows_NT)
	PYTHON=python
else
	PYTHON=python3
endif

#################################################################################
# Targets
#################################################################################
ifeq ($(DEVICE_TYPE),HS)
all: $(HSM_APPIMAGE_HS)
else
all: $(HSM_APPIMAGE) $(HSM_APPIMAGE_HS_FS)
endif

.INTERMEDIATE: $(HSM_ELF)
.INTERMEDIATE: $(HSM_TMP_ELF)
ifeq ($(DEVICE_TYPE),HS)
$(HSM_APPIMAGE_HS): $(HSM_ELF)
else
$(HSM_APPIMAGE): $(HSM_ELF)
$(HSM_APPIMAGE_HS_FS): $(HSM_ELF)
endif
	@echo .
	@echo Creating MCELF image
	$(PYTHON) $(MCELF_IMAGE_GEN) --core-img=$(MULTI_CORE_IMAGE_PARAMS) --output=$(HSM_APPIMAGE) --sw_version=$(SW_VERSION)

ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(HSM_APPIMAGE_HS) --keyversion $(VERSION)
else
	@echo Boot image signing: Encryption is enabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(HSM_APPIMAGE_HS) --keyversion $(VERSION)
	$(RM) $(HSM_APPIMAGE)-enc
endif
else
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(HSM_APPIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(HSM_APPIMAGE_HS_FS) --keyversion $(VERSION)
endif

	@echo Combined boot image: $@ Done !!!

$(HSM_ELF): $(HSM_TMP_ELF)
	$(CC) $(HSM_TMP_ELF) -o $(HSM_ELF) -Wl,board/$(BOARD)/linker.cmd

$(HSM_TMP_ELF):
	$(OBJCOPY) -I binary -O elf32-littlearm --set-start $(HSM_LOAD_ADDR) $(HSM_BINARY) $(HSM_TMP_ELF)

clean:
	@echo Cleaning: $(HSM_APPIMAGE)
	$(RM) $(HSM_APPIMAGE)*
	$(RM) $(HSM_TMP_ELF)
	$(RM) *.elf

scrub: clean