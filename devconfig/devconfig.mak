# Device type (HS/GP)
DEVICE_TYPE?=GP

# Path to the signing tools, keys etc
SIGNING_TOOL_PATH=$(MCU_PLUS_SDK_PATH)/tools/boot/signing

# Path to the keys
ROM_DEGENERATE_KEY:=$(SIGNING_TOOL_PATH)/rom_degenerateKey.pem
APP_DEGENERATE_KEY:=$(SIGNING_TOOL_PATH)/app_degenerateKey.pem
ifeq ($(DEVICE),am263x)
    CUST_MPK=$(SIGNING_TOOL_PATH)/mcu_custMpk.pem
else ifeq ($(DEVICE),am273x)
    CUST_MPK=$(SIGNING_TOOL_PATH)/mcu_custMpk.pem
else ifeq ($(DEVICE),awr294x)
    CUST_MPK=$(SIGNING_TOOL_PATH)/mcu_custMpk.pem
else ifeq ($(DEVICE),am62x)
    CUST_MPK=$(SIGNING_TOOL_PATH)/custMpk_am62x.pem
    CUST_MEK=$(SIGNING_TOOL_PATH)/custMek_am62x.txt
else ifeq ($(DEVICE),am62ax)
    CUST_MPK=$(SIGNING_TOOL_PATH)/custMpk_am62ax.pem
    CUST_MEK=$(SIGNING_TOOL_PATH)/custMek_am62ax.txt
else
    CUST_MPK=$(SIGNING_TOOL_PATH)/custMpk_am64x_am243x.pem
    CUST_MEK=$(SIGNING_TOOL_PATH)/custMek_am64x_am243x.txt
endif

# Encryption option for application (yes/no)
ENC_ENABLED?=no

# Encryption option for SBL (yes/no)
ENC_SBL_ENABLED?=yes

# Debug option for HS (yes/no)
DBG_ENABLED?=no

# Generic macros to be used depending on the device type
APP_SIGNING_KEY=
APP_ENCRYPTION_KEY=

ifeq ($(DEVICE_TYPE),HS)
	APP_SIGNING_KEY=$(CUST_MPK)
	APP_ENCRYPTION_KEY=$(CUST_MEK)
else
	APP_SIGNING_KEY=$(APP_DEGENERATE_KEY)
endif
