# SA3UL AES ECB-256 Test
## Introduction

This example demonstrates the AES ECB-256 Encryption and Decryptions using SA3UL module.

## Supported Combinations
::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/crypto/sa3ul_aes/crypto_aes_ecb_256/crypto_aes_ecb_256.c |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../../getting_started/ccs_launch.md)

## See Also

[SA3UL](../../../components/security/crypto/sa3ul.md)

## Sample Output

Shown below is a sample output when the application is run.


CCS Console:
```
[CRYPTO] AES ECB-256 example started ...
[CRYPTO] AES ECB-256 example completed!!
All tests have passed!!

```