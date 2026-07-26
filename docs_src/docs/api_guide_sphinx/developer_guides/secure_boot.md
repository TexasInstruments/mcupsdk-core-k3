# Enabling Secure Boot
## Secure Devices and Secure Boot: An Introduction

To put it simply, **secure boot** refers to booting application images in a secure way. Secure boot is a feature/service available in **secure devices**. Out of the device types **GP** and **HS**, HS device type can do secure boot. In secure devices there are two subtypes:

1. Field Securable (FS)
2. Security Enforced (SE)

HS device type have FS and SE subtypes. Out of the two subtypes, FS and SE, this guide talks about secure boot in an **HS-SE** device. If the secure device received is an **HS-FS** subtype, it needs to be converted to an HS-SE variant with the customer keys burnt into the device eFUSEs. This is done using a special piece of software called an OTP keywriter. Keywriter documentation is out of scope for this guide.

## Secure Boot Process

Secure boot process, like the normal boot, consists of two stages - ROM loading and SBL loading. ROM loading is when the boot ROM loads the HSM runtime binary onto the HSM core, and the signed SBL binary into the primary boot core, which in most cases is an ARM Cortex R5F. SBL loading is when the SBL reads the signed application image from a boot media, authenticates it, decrypts it, and boots it. Here we describe how the secure process takes place in an HS-SE device.


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   :::{admonition} Note
   In AM62x/AM62Ax/AM62Dx/AM62Px devices, the HSM runtime binary mentioned is the System Firmware (SYSFW) and HSM core is the DMSC Cortex M4 core. Hereafter for generality sake we'll use the terms 'HSMRt' and 'HSM core' but understand that for AM62x/AM62Ax/AM62Dx/AM62Px this means the SYSFW and Cortex M4 core. :::
   :::


## Secure Boot Support in SDK

### Device configuration file

To make the secure/non-secure differences seamless for the user, a configuration file is provided at `${SDK_INSTALL_PATH}/devconfig/devconfig.mak`.
In this configuration file, you can set certain options like the device type, keys to be used for signing and encryption etc. By default they will point to the dummy customer MPKs and MEKs but if you're using a production device with your own keys burned into the eFUSEs, please change the paths here to point to the right key files. Configuration of this file is currently manual, this will be made configurable by a GUI in an upcoming release.

The devconfig.mak file looks something like this:

```
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
ENC_SBL_ENABLED?=yes

# Debug option for HS (yes/no)
DBG_ENABLED?=no

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
```
#### Configuration Parameters

The devconfig.mak file includes several configuration parameters:

- **DEVICE_TYPE**: Specifies whether the device is GP (General Purpose) or HS (High Security). Set to `HS` for secure boot functionality.

- **KEY_TYPE**: Specifies the cryptographic algorithm to use for signing:
  - `RSA`: Uses RSA keys for signing (default)
  - `ECDSA`: Uses Elliptic Curve Digital Signature Algorithm keys

- **VERSION**: Specifies the RSA version when using RSA keys:
  - `1.5`: RSA PKCS#1 v1.5 (default)
  - `2.2`: RSA PSS
  - Note: This parameter is automatically set to `1.5` when using ECDSA keys

- **ENC_ENABLED**: Controls application image encryption (`yes`/`no`). When enabled, application images are encrypted using the customer MEK.

- **ENC_SBL_ENABLED**: Controls SBL (Secondary Boot Loader) encryption (`yes`/`no`). This allows separate control over SBL encryption independent of application encryption.

- **DBG_ENABLED**: Enables debug features for HS devices (`yes`/`no`). This should typically be set to `no` for production devices.

The configuration automatically selects the appropriate signing key based on the device type and key type:
- For HS devices with ECDSA: Uses `CUST_MPK_ECDSA`
- For HS devices with RSA: Uses `CUST_MPK`
- For HSFS devices: Uses `APP_DEGENERATE_KEY`

**Key considerations when using ECDSA:**

- Set `KEY_TYPE=ECDSA` in the devconfig.mak file
- Ensure your customer MPK is in ECDSA format and placed at `${SDK_INSTALL_PATH}/tools/boot/signing/custMpk_ecdsa.pem`
- The VERSION parameter is automatically set to `1.5` when using ECDSA, as version selection is not applicable for ECDSA keys
- ECDSA keys must be burned into the device eFUSEs in the correct format for HS-SE devices

**Choosing between RSA and ECDSA:**

- Use **RSA** for maximum compatibility and when working with existing RSA-based infrastructure
- Use **ECDSA** when you need smaller signatures, faster signing operations, or lower power consumption
- Ensure your target device supports the chosen key type before making the selection

This file will be included in all example makefiles

### Signing tool

For signing the binaries, two different scripts are used:

1. ROM signing script - This is a python script used for signing the SBL. The x509 certificate template used in this script is expected by the ROM.
2. Application signing script - This is a python script used for signing the application image. The x509 certificate template used in this script is expected by the HSMRt.

 For more details on the usage of the script, see [Signing Scripts](../components/tools/tools_boot.md)

### Signing steps in an HS-SE device

#### Signing the SBL


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   A combined boot method is employed in these devices, by virtue of which the SBL, SYSFW and the SYSFW-BoardConfig are combined and signed with the same certificate. This is built into the make system of the SBL applications in the SDK - SBL_UART, SBL_OSPI, SBL_SD, SBL_NULL, etc. So whenever an SBL application is built, the loadable `*.tiimage` will be a concatenation of the x509 certificate, SBL binary, SYSFW binary and the boardcfg binary blob. In case of HS devices, the SYSFW inner certificate will also be concatenated.
:::


The SBL is signed with a dummy customer MPK in the SDK. This is supposed to be used only with the devices with the same dummy customer MPK burnt into the eFUSEes. If the SDK is supposed to be used with a production/development device with actual customer MPKs burnt into the device, please replace the file at ${SDK_INSTALL_PATH}/tools/boot/signing/custMpk_${SOC}.pem. This is true for also the encryption key used, which can also be found at ${SDK_INSTALL_PATH}/tools/boot/signing/custMek_${SOC}.txt. Whenever any SBL is built, it will be signed with dummy customer MPK, and the signed image generated will have an extension of `*.hs.tiimage`. There is no extra step required other than making sure that the MPK used is indeed the one burnt into the eFUSEs.

:::{admonition} Note
**Encryption key format**: The signing scripts (both ROM and appimage) expect the SMEK/BMEK encryption key in **hex text format** - one hex byte per line (e.g. `custMek_${SOC}.txt`). The OTP Keywriter, however, generates keys in **binary format**. To convert a binary key file to the required hex text format, use the following command:

```bash
# Linux
xxd -p -c 1 <key.bin> > custMek_${SOC}.txt

# Windows (PowerShell)
Format-Hex <key.bin> | ForEach-Object { $_.Bytes | ForEach-Object { "{0:x2}" -f $_ } } | Out-File custMek_${SOC}.txt
```
:::


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   #### Signing the HSM Runtime binary (SYSFW)
   As mentioned above, since we follow a combined boot method, SYSFW and SBL is signed with the same certificate using the same key. In case of a GP device this will be a degenerate key for easy parsing from ROM. In the case of an HS device, SYSFW will be already signed with TI MPK (and encrypted). This is then countersigned again with dummy customer MPK during the combined image generation process.
:::


#### Signing the application image

Depending on the options given in the device configuration file (`devconfig.mak` mentioned above), appimage is generated for HS devices. If encryption is enabled in the configuration file, the binary will be first encrypted with the key specified and then the certificate will be generated using the customer MPK specified. If the device type is set as HS in the configuration file, nothing extra needs to be done for the appimage generation. The final `*.appimage.hs` file generated would be signed with customer MPK (and encrypted with customer MEK if that option is selected). To dig into the details of the process, one can refer to https://software-dl.ti.com/tisci/esd/latest/6_topic_user_guides/secure_boot_signing.html
