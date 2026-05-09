# Device type (HS/GP)
DEVICE_TYPE?=GP

# Possible key types:
# ECDSA
# RSA
KEY_TYPE?=RSA
# RSA VERSIONS: 1.5, 2.2
# ECDSA VERSIONS: None
VERSION?=1.5

# Path to the signing tools, keys etc
SIGNING_TOOL_PATH=$(MCU_PLUS_SDK_PATH)/tools/boot/signing

# Path to the keys
ROM_DEGENERATE_KEY:=$(SIGNING_TOOL_PATH)/rom_degenerateKey.pem
APP_DEGENERATE_KEY:=$(SIGNING_TOOL_PATH)/app_degenerateKey.pem
CUST_MPK=$(SIGNING_TOOL_PATH)/custMpk.pem
CUST_MPK_ECDSA=$(SIGNING_TOOL_PATH)/custMpk_ecdsa.pem
CUST_MEK=$(SIGNING_TOOL_PATH)/custMek.txt

# Encryption option for application (yes/no)
ENC_ENABLED?=no

# Encryption option for SBL (yes/no)
# NOTE: Disabled by default. Enable only when encryption keys are programmed
# into the device eFUSEs. Enabling this OOB on HSSE devices without programmed
# keys will cause boot failures.
ENC_SBL_ENABLED?=no

# Debug option for HS (yes/no)
DBG_ENABLED?=no

# X509 certificate software revision
X509_SW_REV?=1

# Generic macros to be used depending on the device type
APP_SIGNING_KEY=
APP_ENCRYPTION_KEY=

ifeq ($(DEVICE_TYPE),HS)
ifeq ($(KEY_TYPE), ECDSA)
	APP_SIGNING_KEY=$(CUST_MPK_ECDSA)
# Version for ECDSA is invalid, setting it to default value
	VERSION = 1.5
else
	APP_SIGNING_KEY=$(CUST_MPK)
endif
	APP_ENCRYPTION_KEY=$(CUST_MEK)
else
	APP_SIGNING_KEY=$(APP_DEGENERATE_KEY)
endif
