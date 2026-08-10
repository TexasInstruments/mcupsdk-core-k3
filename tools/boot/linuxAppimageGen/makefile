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
ifeq ($(DEVICE),$(filter $(DEVICE), am62dx))
BOARD?=$(DEVICE)-evm
endif

include board/$(BOARD)/config.mak

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

ifeq ($(FALCON_MODE), 1)
IMAGE_BIN_NAME=$(KERN_BIN_NAME)
IMAGE_LOAD_ADDR=$(KERN_LOAD_ADDR)
else
IMAGE_BIN_NAME=$(SPL_BIN_NAME)
IMAGE_LOAD_ADDR=$(SPL_LOAD_ADDR)
endif

LINUX_IMAGE_LIST = \
	$(ATF_BIN_NAME) \
	$(OPTEE_BIN_NAME) \
	$(IMAGE_BIN_NAME)

ifeq ($(FALCON_MODE), 1)
LINUX_IMAGE_LIST += $(FDT_BIN_NAME)
endif

ATF_RPRC = $(addsuffix .rprc, $(basename $(ATF_BIN_NAME)))
OPTEE_RPRC := $(addsuffix .rprc, $(basename $(OPTEE_BIN_NAME)))
IMAGE_RPRC := $(addsuffix .rprc, $(basename $(IMAGE_BIN_NAME)))

ATF_ELF =  board/$(BOARD)/$(addsuffix .elf, $(basename $(ATF_BIN_NAME)))
OPTEE_ELF :=  board/$(BOARD)/$(addsuffix .elf, $(basename $(OPTEE_BIN_NAME)))
IMAGE_ELF :=  board/$(BOARD)/$(addsuffix .elf, $(basename $(IMAGE_BIN_NAME)))

ifeq ($(FALCON_MODE), 1)
FDT_RPRC := $(addsuffix .rprc, $(basename $(FDT_BIN_NAME)))
FDT_ELF :=  board/$(BOARD)/$(addsuffix .elf, $(basename $(FDT_BIN_NAME)))
endif

RPRC_LIST = \
	$(ATF_RPRC) \
	$(OPTEE_RPRC) \
	$(IMAGE_RPRC)

ifeq ($(FALCON_MODE), 1)
RPRC_LIST += $(FDT_RPRC)
endif

ELF_FILE_LIST = $(RPRC_LIST:.rprc=.elf)

ifeq ($(BOARD), j722s-evm)
	COMBINED_APPIMAGE_PARAMS = \
		$(RTOS_IMG_LIST) \
		$(BOOTIMAGE_CORE_ID_a53ss0-0) $(ATF_RPRC) \
		$(BOOTIMAGE_CORE_ID_load_only) $(OPTEE_RPRC) \
		$(BOOTIMAGE_CORE_ID_load_only) $(IMAGE_RPRC)
else
	COMBINED_APPIMAGE_PARAMS = \
		$(BOOTIMAGE_CORE_ID_a53ss0-0) $(ATF_RPRC) \
		$(BOOTIMAGE_CORE_ID_load_only) $(OPTEE_RPRC) \
		$(BOOTIMAGE_CORE_ID_load_only) $(IMAGE_RPRC)
endif

ifeq ($(FALCON_MODE), 1)
COMBINED_APPIMAGE_PARAMS += $(BOOTIMAGE_CORE_ID_load_only) $(FDT_RPRC)
endif

BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(BOARD).txt


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
ifeq ($(DEVICE_TYPE),HS)
all: $(LINUX_BOOTIMAGE_HS)
else
all: $(LINUX_BOOTIMAGE) $(LINUX_BOOTIMAGE_HS_FS)
endif

.INTERMEDIATE: $(RPRC_LIST) $(ELF_FILE_LIST)
ifeq ($(DEVICE_TYPE),HS)
$(LINUX_BOOTIMAGE_HS): $(RPRC_LIST)
else
$(LINUX_BOOTIMAGE): $(RPRC_LIST)
$(LINUX_BOOTIMAGE_HS_FS): $(RPRC_LIST)
endif
	@echo .
	@echo Creating
	$(MULTI_CORE_IMAGE_GEN) LE $(SBL_DEV_ID) $(LINUX_BOOTIMAGE) $(COMBINED_APPIMAGE_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Copying u-boot.img
	$(COPY) $(PSDK_LINUX_PREBUILT_IMAGES)/u-boot.img board/$(BOARD)

ifeq ($(DEVICE_TYPE),HS)
# Sign the appimage using appimage signing script
ifeq ($(ENC_ENABLED),no)
	@echo Boot image signing: Encryption is disabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(LINUX_BOOTIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(LINUX_BOOTIMAGE_HS) --keyversion $(VERSION)
else
	@echo Boot image signing: Encryption is enabled.
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(LINUX_BOOTIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --enc y --enckey $(APP_ENCRYPTION_KEY) --output $(LINUX_BOOTIMAGE_HS) --keyversion $(VERSION)
	$(RM) $(LINUX_BOOTIMAGE)-enc
endif
else
    #
    #   Authentication type 0 with load address 0x84000000
    #
	$(PYTHON) $(APP_IMAGE_SIGN_CMD) --bin $(LINUX_BOOTIMAGE) --authtype 0 --loadaddr 84000000 --key $(APP_SIGNING_KEY) --output $(LINUX_BOOTIMAGE_HS_FS) --keyversion $(VERSION)
endif

	$(RM) board/$(BOARD)/$(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo Combined boot image: $@ Done !!!

$(ATF_RPRC): $(ATF_ELF)
	@echo Creating ATF RPRC image
	cd board/$(BOARD) && ${OUTRPRC_CMD} $(notdir $(ATF_ELF)) $(SW_VERSION) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(OPTEE_RPRC): $(OPTEE_ELF)
	@echo Creating OPTEE RPRC image
	cd board/$(BOARD) && ${OUTRPRC_CMD} $(notdir $(OPTEE_ELF)) $(SW_VERSION) >> $(BOOTIMAGE_TEMP_OUT_FILE)

$(IMAGE_RPRC): $(IMAGE_ELF)
	@echo Creating IMAGE RPRC image
	cd board/$(BOARD) && ${OUTRPRC_CMD} $(notdir $(IMAGE_ELF)) $(SW_VERSION) >> $(BOOTIMAGE_TEMP_OUT_FILE)

ifeq ($(FALCON_MODE), 1)
$(FDT_RPRC): $(FDT_ELF)
	@echo Creating FDT RPRC image
	cd board/$(BOARD) && ${OUTRPRC_CMD} $(notdir $(FDT_ELF)) $(SW_VERSION) >> $(BOOTIMAGE_TEMP_OUT_FILE)
endif

$(ATF_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(ATF_LOAD_ADDR) -e $(ATF_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(ATF_BIN_NAME) -o $(ATF_ELF)

$(OPTEE_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(OPTEE_LOAD_ADDR) -e $(OPTEE_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(OPTEE_BIN_NAME) -o $(OPTEE_ELF)

$(IMAGE_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(IMAGE_LOAD_ADDR) -e $(IMAGE_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(IMAGE_BIN_NAME) -o $(IMAGE_ELF)

ifeq ($(FALCON_MODE), 1)
$(FDT_ELF):
	$(LD) -b binary -A aarch64 --oformat elf64-littleaarch64 --section-start=.data=$(FDT_LOAD_ADDR) -e $(FDT_LOAD_ADDR) $(PSDK_LINUX_PREBUILT_IMAGES)/$(FDT_BIN_NAME) -o $(FDT_ELF)
endif

clean:
	@echo Cleaning: $(LINUX_BOOTIMAGE)
	$(RM) $(LINUX_BOOTIMAGE)*
	$(RM) *.rprc
	$(RM) *.img

scrub: clean

endif