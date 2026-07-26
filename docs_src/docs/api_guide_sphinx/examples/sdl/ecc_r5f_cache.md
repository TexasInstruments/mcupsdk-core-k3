# SDL ECC R5F CACHE
## Introduction

The I-cache and D-cache are being protected by Error Correcting Code (ECC) which performs Single Error Correction (SEC) and Double Error Detection (DED).The detected errors are reported via ESM. Single bit errors are corrected, and double bit errors are detected.The following steps are performed to test the error injection and detection of I-cache and D-cache in R5F.

### Enabling ECC for R5 Cache memories

* ECC is enabled by setting the ACTLR Register in the startup sequence using the function - ecc_enable()
* Enabling ECC before the cache usage prevents unexpected aborts.
* The ACTLR Register is configured to abort only for non-correctable errors.

### Initializing ECC and ESM

* ECC_Memory_Init() initializes both ESM and ECC using the SDL_ESM_init() and SDL_ECC_init() APIs
* Enabling the export functionality of R5F Performance Monitors Control Register is required for routing R5F ECC error events to ESM/ Pulsar registers
* ECC_PMCR_export() function is used for enabling it before the initializations.

### Error Injection in I-Cache

* ECC_I_Cache_InjectTest() is being used for testing any I-Cache RAM ID.
* Cache invalidate is performed and the I-Cache is filled with dummy instructions using ecc_instructions_test_function() to make sure that the cache is accessible and ready for error injection.
* SDL_ECC_injectError() API is used for injecting the error.
* Loop through the entire ICache using ecc_instructions_test_function() to trigger error.
* R5F control register has the status of the error injection and ESM interrupts are recorded at the 400 offset of ESM base.
* After the detection, SDL_ESM_applicationCallbackFunction() API is called and the injected error is cleared.
* All errors detected in I-cache are correctable, hence there is no support for DED on I-cache.

### Error Injection in D-Cache

* ECC_D_Cache_InjectTest() is being used for testing any D-Cache RAM ID.
* Cache invalidate is performed and the D-Cache is filled with dummy values using SDL_ECC_cache_ddata array to make sure that the cache is accessible and ready for error injection.
* SDL_ECC_injectError() API is used for injecting the error.
* SDL_ECC_cache_ddata array is again used for error detection while parsing through the cache
* R5F control register has the status of the error injection and ESM interrupts are recorded at the 400 offset of ESM base.
* After the detection, if the error is correctable (SEC), the injected error is cleared.
* If the error is un-correctable (DED), the execution is redirected to SDL exception handler after the error is detected.
* The ESM interrupts are cleared using SDL_ESM_applicationCallbackFunction() API.

### Memory Allocation

* For effective error injection testing, proper memory allocation is required
* The test array (SDL_ECC_cache_ddata) and cache instructions function (ecc_instructions_test_function) should be placed in cached memory ,while the code execution must occur in non-cached memory.
* If both are in cached memory,the injected error might alter the cache itself,making detection unreliable.
* A Cached memory section is defined in the linker for the same.This separation ensures accurate error injection and validation.

### Error Injection Supported

The following cases are implemented in this example:

::::{only} SOC_AM62AX or SOC_AM275X or SOC_AM62X or SOC_AM62PX or SOC_AM62DX

| R5F RAM | Type of ECC error injection |
|---|---|
| Instruction cache tag RAM | Single bit repeated error injection |
| Instruction cache data RAM | Single bit N-row repeated error injection |
| Data cache tag RAM | Single bit repeated error injection |
| Data cache tag RAM | Double bit N-row repeated Error Injection |
| Data cache dirty RAM | Single bit N-row repeated error injection |
| Data cache dirty RAM | Double bit N-row repeated Error Injection |
| Data cache data RAM | Single bit N-row repeated error injection |
| Data cache data RAM | Double bit N-row repeated Error Injection |


::::


## Supported Combinations

::::{only} SOC_AM62X or SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/ecc_r5f_cache/ |


::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/ecc_r5f_cache/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

Shown below is a sample output when the application is run,

::::{only} SOC_AM62X or (SOC_AM275X) or (SOC_AM62AX) or (SOC_AM62PX) or (SOC_AM62DX)

```
ECC_Test_init: Exception init complete

ESM_Memory_init: Init ESM complete

ECC_Memory_init: R5FSS0 CORE0 ECC initialization is completed

ECC R5F Cache test started for aggregator = SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR

Starting Tests for Itag - single error correction

I_Cache 1-bit Error Injection : Starting for RAM ID = 0

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 0

I_Cache 1-bit Error Injection : Starting for RAM ID = 1

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 1

I_Cache 1-bit Error Injection : Starting for RAM ID = 2

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 2

I_Cache 1-bit Error Injection : Starting for RAM ID = 3

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 3

Starting Tests for IData - single error correction

I_Cache 1-bit Error Injection : Starting for RAM ID = 4

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 4

I_Cache 1-bit Error Injection : Starting for RAM ID = 5

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 5

I_Cache 1-bit Error Injection : Starting for RAM ID = 6

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 6

I_Cache 1-bit Error Injection : Starting for RAM ID = 7

Waiting for ESM Interrupt

Injected 1-bit error and got ESM Interrupt for ram_Id = 7

Starting Tests for Dtag - single error correction

D_Cache Error Injection : Starting for RAM ID = 8

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 8

D_Cache Error Injection : Starting for RAM ID = 9

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 9

D_Cache Error Injection : Starting for RAM ID = 10

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 10

D_Cache Error Injection : Starting for RAM ID = 11

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 11

Starting Tests for DDirty cache - single error correction

D_Cache Error Injection : Starting for RAM ID = 12

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 12

Starting Tests for Ddata cache - single error correction

D_Cache Error Injection : Starting for RAM ID = 13

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 13

D_Cache Error Injection : Starting for RAM ID = 14

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 14

D_Cache Error Injection : Starting for RAM ID = 15

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 15

D_Cache Error Injection : Starting for RAM ID = 16

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 16

D_Cache Error Injection : Starting for RAM ID = 17

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 17

D_Cache Error Injection : Starting for RAM ID = 18

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 18

D_Cache Error Injection : Starting for RAM ID = 19

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 19

D_Cache Error Injection : Starting for RAM ID = 20

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 20

Starting Tests for Dtag cache - double error detection

D_Cache Error Injection : Starting for RAM ID = 8

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 8

D_Cache Error Injection : Starting for RAM ID = 9

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 9

D_Cache Error Injection : Starting for RAM ID = 10

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 10

D_Cache Error Injection : Starting for RAM ID = 11

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 11

Starting Tests for Ddirty cache - double error detection

D_Cache Error Injection : Starting for RAM ID = 12

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 12

Starting Tests for Ddata cache - double error detection

D_Cache Error Injection : Starting for RAM ID = 13

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 13

D_Cache Error Injection : Starting for RAM ID = 14

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 14

D_Cache Error Injection : Starting for RAM ID = 15

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 15

D_Cache Error Injection : Starting for RAM ID = 16

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 16

D_Cache Error Injection : Starting for RAM ID = 17

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 17

D_Cache Error Injection : Starting for RAM ID = 18

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 18

D_Cache Error Injection : Starting for RAM ID = 19

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 19

D_Cache Error Injection : Starting for RAM ID = 20

Waiting for ESM Interrupt

Injected error and got ESM Interrupt for ram_Id = 20

All tests have passed.
```

::::

