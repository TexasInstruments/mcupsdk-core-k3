export MCU_PLUS_SDK_PATH?=$(abspath ../../../../)

# Default device
DEVICE?=am62px

# debug, release
PROFILE?=release

# GP, HS
DEVICE_TYPE?=GP

# Build all custom board config blobs
all:
ifeq ($(DEVICE),am62x)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/drivers/device_manager/sciclient_default_boardcfg/am62x
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62x-sk/sciclient_boardcfg
else ifeq ($(DEVICE),am62ax)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62ax-sk/sciclient_boardcfg
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62ax-sk/sciclient_boardcfg
else ifeq ($(DEVICE),am62px)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62px-sk/sciclient_boardcfg
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/tools/sysfw/boardcfg SOC=$(DEVICE) CFG_DIR=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62px-sk/sciclient_boardcfg
endif

# Now build the sbl uart for all the above custom board config blobs
ifeq ($(DEVICE),am62x)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62x-sk/r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=dm_test BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/drivers/device_manager/sciclient_default_boardcfg/am62x/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/drivers/device_manager/sciclient_default_boardcfg/am62x/boardcfg_sbldata_blob.bin

	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62x-sk/r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=tifs_safety_checker BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62x-sk/sciclient_boardcfg/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62x-sk/sciclient_boardcfg/boardcfg_sbldata_blob.bin
else ifeq ($(DEVICE),am62ax)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62ax-sk/r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=runtime_debug_unlock BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62ax-sk/sciclient_boardcfg/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62ax-sk/sciclient_boardcfg/boardcfg_sbldata_blob.bin

	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62ax-sk/r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=tifs_safety_checker BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62ax-sk/sciclient_boardcfg/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62ax-sk/sciclient_boardcfg/boardcfg_sbldata_blob.bin
else ifeq ($(DEVICE),am62px)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=runtime_debug_unlock BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62px-sk/sciclient_boardcfg/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/runtime_debug_unlock/am62px-sk/sciclient_boardcfg/boardcfg_sbldata_blob.bin

	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang DEVICE=$(DEVICE) DEVICE_TYPE=$(DEVICE_TYPE) \
	PROFILE=$(PROFILE) BRDCFG_MOD_NAME=tifs_safety_checker BOARDCFG_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62px-sk/sciclient_boardcfg/boardcfg_blob.bin \
	BOARDCFG_SBLDATA_BLOB=$(MCU_PLUS_SDK_PATH)/test/security/tifs_safety_checker/am62px-sk/sciclient_boardcfg/boardcfg_sbldata_blob.bin
endif

scrub:
ifeq ($(DEVICE),am62x)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62x-sk/r5fss0-0_nortos/ti-arm-clang scrub
endif
ifeq ($(DEVICE),am62ax)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62ax-sk/r5fss0-0_nortos/ti-arm-clang scrub
endif
ifeq ($(DEVICE),am62px)
	$(MAKE) -C $(MCU_PLUS_SDK_PATH)/test/drivers/boot/sbl_uart_custom_boardconfig/am62px-sk/wkup-r5fss0-0_nortos/ti-arm-clang scrub
endif