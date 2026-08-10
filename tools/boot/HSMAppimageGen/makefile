export MCU_PLUS_SDK_PATH?=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak
include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

# am62x has multiple boards (am62x-sk, am62x-sk-lp, am62x-sip-sk); build all
# of them when BOARD is not explicitly passed on the command line.
ifeq ($(origin BOARD), undefined)
ifeq ($(DEVICE),am62x)
BOARD_LIST = am62x-sk am62x-sk-lp am62x-sip-sk
endif
endif

ifdef BOARD_LIST

.PHONY: all clean scrub
.PHONY: $(BOARD_LIST:%=%-all) $(BOARD_LIST:%=%-clean) $(BOARD_LIST:%=%-scrub)

all: $(BOARD_LIST:%=%-all)
clean: $(BOARD_LIST:%=%-clean)
scrub: $(BOARD_LIST:%=%-scrub)

$(BOARD_LIST:%=%-all): %-all:
	$(MAKE) --no-print-directory BOARD=$* all || exit 1

$(BOARD_LIST:%=%-clean): %-clean:
	$(MAKE) --no-print-directory BOARD=$* clean || exit 1

$(BOARD_LIST:%=%-scrub): %-scrub:
	$(MAKE) --no-print-directory BOARD=$* scrub || exit 1

else

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62px))
BOARD?=$(DEVICE)-sk
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62dx am275x))
BOARD?=$(DEVICE)-evm
endif

include board/$(BOARD)/config.mak

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

HSM_BINARY = board/$(BOARD)/$(HSM_BINARY_NAME)
HSM_APPIMAGE = board/$(BOARD)/$(HSM_APPIMAGE_NAME)
HSM_APPIMAGE_HS = $(HSM_APPIMAGE).hs
HSM_APPIMAGE_HS_FS = $(HSM_APPIMAGE).hs_fs

HSM_RPRC_NAME = $(addsuffix .rprc, $(basename $(HSM_BINARY_NAME)))
HSM_ELF = board/$(BOARD)/$(addsuffix .elf, $(basename $(HSM_BINARY_NAME)))
HSM_RPRC = board/$(BOARD)/$(HSM_RPRC_NAME)
HSM_APPIMAGE_PARAMS = $(BOOTIMAGE_CORE_ID_HSM) $(HSM_RPRC)

BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(BOARD).txt

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
all: $(HSM_APPIMAGE_HS)
else
all: $(HSM_APPIMAGE) $(HSM_APPIMAGE_HS_FS)
endif

.INTERMEDIATE: $(HSM_ELF)
ifeq ($(DEVICE_TYPE),HS)
$(HSM_APPIMAGE_HS): $(HSM_RPRC)
else
$(HSM_APPIMAGE): $(HSM_RPRC)
$(HSM_APPIMAGE_HS_FS): $(HSM_RPRC)
endif
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(HSM_APPIMAGE) $(HSM_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)

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

	$(RM) board/$(BOARD)/$(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(HSM_RPRC): $(HSM_ELF)
	@echo Creating ATF RPRC image
	cd board/$(BOARD) && ${OUTRPRC_CMD} $(notdir $(HSM_ELF)) $(SW_VERSION) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(HSM_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(HSM_LOAD_ADDR) -e $(HSM_LOAD_ADDR) $(HSM_BINARY) -o $(HSM_ELF)


clean:
	@echo Cleaning: $(HSM_APPIMAGE)
	$(RM) $(HSM_APPIMAGE)*
	$(RM) $(HSM_RPRC)
	$(RM) *.elf

scrub: clean

endif
