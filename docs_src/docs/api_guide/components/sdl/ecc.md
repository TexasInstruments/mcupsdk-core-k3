# ECC {#SDL_ECC_PAGE}

[TOC]

To increase functional and system reliability, the memories in many device modules and subsystems are protected by Error Correcting Code (ECC), which performs Single Error Correction (SEC) and Double Error Detection (DED). Detected errors are reported via ESM. Single bit errors are corrected, and double bit errors are detected. The ECC Aggregator is connected to these memory and interconnect components which have the ECC. The ECC aggregator provides access to control and monitor the ECC protected memories in a module or subsystem.

SDL provides support for ECC aggregator configuration. Each ECC aggregator instance can be independently configured through the same SDL API by passing a different instance. The safety manual also defines test-for-diagnostics for the various IPs with ECC/parity support. The SDL also provides the support for executing ECC aggregator self-tests, using the error injection feature of the ECC aggregator.
The ECC aggregators should be configured at startup, after running BIST.

## Features Supported

The SDL provides support for the ECC through:

* ECC Configuration API
* ECC self-test API
* ECC error injection API
* ECC static register readback API
* ECC error status APIs

There are 37 ECC aggregators on the device each supporting multiple memories and interconnects.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

There are two types of ECC aggregator RAM IDs supported on the device (wrapper and interconnect). The wrapper types are used for memories where local computations are performed for particular processing cores in the device, and the interconnect types are utilized for interconnect bus signals between cores or to/from peripherals.

For wrapper RAM ID types, after injecting an error, the memory associated with that RAM ID needs to be accessed in order to trigger the error interrupt event. It is the application's responsibility to trigger the error event through memory access after injecting the error.

## Example Usage

The following shows an example of SDL ECC API usage by the application to set up the ECC to monitor for errors, as well as how to perform ECC self-test. The ESM should be configured to notify of the desired ECC events for the IPs. Please refer to the TRM for a list of the ESM events.

The following function is required to be defined by the application. It is used by the ECC module to notify the application in case of certain ECC errors that are reported through the R5F exception handlers. If it is not defined, it will result in a linker error. An example implementation is given below.


\code{.c}
void SDL_ECC_applicationCallbackFunction(SDL_ECC_MemType eccMemType,
                                         uint32_t errorSrc,
                                         uint32_t address,
                                         uint32_t ramId,
                                         uint64_t bitErrorOffset,
                                         uint32_t bitErrorGroup)
{

    DebugP_log("\r\n  ECC Error Call back function called : eccMemType %d, errorSrc 0x%x, " \
                "address 0x%x, ramId %d, bitErrorOffset 0x%04x%04x, bitErrorGroup %d\n",
                eccMemType, errorSrc, address, ramId, (uint32_t)(bitErrorOffset >> 32),
                (uint32_t)(bitErrorOffset & 0x00000000FFFFFFFF), bitErrorGroup);
    DebugP_log("\r  Take action \n");

    /* Any additional customer specific actions can be added here */

}
\endcode

Certain ECC events on CPU memory are reported as Exception events. In this case, the ECC SDL provdes a set of exception handlers that can be used to enable the SDL ECC self-test functionality and for notification of the ECC errors. The following example shows how to set up the exception handlers to use the SDL ECC implementations, and also provide application-specific handlers that will be called by the SDL handlers after the handler checks for ECC errors:
:

\code{.c}

const SDL_R5ExptnHandlers ECC_Test_R5ExptnHandlers =
{
    .udefExptnHandler = &SDL_EXCEPTION_undefInstructionExptnHandler,
    .swiExptnHandler = &SDL_EXCEPTION_swIntrExptnHandler,
    .pabtExptnHandler = &SDL_EXCEPTION_prefetchAbortExptnHandler,
    .dabtExptnHandler = &SDL_EXCEPTION_dataAbortExptnHandler,
    .irqExptnHandler = &SDL_EXCEPTION_irqExptnHandler,
    .fiqExptnHandler = &SDL_EXCEPTION_fiqExptnHandler,
    .udefExptnHandlerArgs = ((void *)0u),
    .swiExptnHandlerArgs = ((void *)0u),
    .pabtExptnHandlerArgs = ((void *)0u),
    .dabtExptnHandlerArgs = ((void *)0u),
    .irqExptnHandlerArgs = ((void *)0u),
};

void ECC_Test_undefInstructionExptnCallback(void)
{
    DebugP_log("\r\nUndefined Instruction exception\r\n");
}

void ECC_Test_swIntrExptnCallback(void)
{
    DebugP_log("\r\nSoftware interrupt exception\r\n");
}

void ECC_Test_prefetchAbortExptnCallback(void)
{
    DebugP_log("\r\nPrefetch Abort exception\r\n");
}
void ECC_Test_dataAbortExptnCallback(void)
{
    DebugP_log("\r\nData Abort exception\r\n");
}
void ECC_Test_irqExptnCallback(void)
{
    DebugP_log("\r\nIrq exception\r\n");
}

void ECC_Test_fiqExptnCallback(void)
{
    DebugP_log("\r\nFiq exception\r\n");
}
void ECC_Test_exceptionInit(void)
{

    SDL_EXCEPTION_CallbackFunctions_t exceptionCallbackFunctions =
            {
             .udefExptnCallback = ECC_Test_undefInstructionExptnCallback,
             .swiExptnCallback = ECC_Test_swIntrExptnCallback,
             .pabtExptnCallback = ECC_Test_prefetchAbortExptnCallback,
             .dabtExptnCallback = ECC_Test_dataAbortExptnCallback,
             .irqExptnCallback = ECC_Test_irqExptnCallback,
             .fiqExptnCallback = ECC_Test_fiqExptnCallback,
            };

    /* Initialize SDL exception handler */
    SDL_EXCEPTION_init(&exceptionCallbackFunctions);
    /* Register SDL exception handler */
    Intc_RegisterExptnHandlers(&ECC_Test_R5ExptnHandlers);

    return;
}\endcode

To configure ECC for an instance and specified ram IDs:

\code{.c}
  static SDL_ECC_MemSubType ECC_Test_AGGR0_A0subMemTypeList[MAIN_AGGR0_AGGR0_MAX_MEM_SECTIONS] =
  {
      SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_IAM62_MAIN_IPCSS_CBASS_MAIN_0_AM62_MAIN_IPCSS_CBASS_HSM_CLK_2_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_2_BUSECC_RAM_ID,
      SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_AM62_MAIN_CENTRAL_CBASS_HSM_CLK_1_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_1_BUSECC_RAM_ID,
  };


  static SDL_ECC_InitConfig_t ECC_Test_AGGR0A0ECCInitConfig =
  {
      .numRams = MAIN_AGGR0_AGGR0_MAX_MEM_SECTIONS,
      /**< Number of Rams ECC is enabled  */
      .pMemSubTypeList = &(ECC_Test_AGGR0_A0subMemTypeList[0]),
      /**< Sub type list  */
  };

...

int32_t ECC_Example_init (void)
{
    int32_t retValue=0;
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;

    if (retValue == SDL_APP_TEST_PASS) {
        /* Initialize MAIN ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ECC_Test_esmInitConfig_MAIN, SDL_ESM_applicationCallbackFunction, ptr);
        if (result != SDL_APP_TEST_PASS) {
            /* print error and quit */
            DebugP_log("\rECC_Example_init: Error initializing MAIN ESM: result = %d\n\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\rECC_Example_init: Init MAIN ESM complete \n\n");
        }
    }

    if (retValue == SDL_APP_TEST_PASS) {
        /* Initialize WKUP ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_WKUP, SDL_ESM_applicationCallbackFunction, ptr);
        if (result != SDL_APP_TEST_PASS) {
            /* print error and quit */
            DebugP_log("\rECC_Example_init: Error initializing WKUP ESM: result = %d\n\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\rECC_Example_init: Init WKUP ESM complete \n\n");
        }
    }

    if (retValue == SDL_APP_TEST_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR, &ECC_Test_AGGR0A0ECCInitConfig);
        if (result != SDL_APP_TEST_PASS) {
            /* print error and quit */
             DebugP_log("\rSDTF_init: Error initializing M4F core ECC: result = %d\n\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\r\n\nSDTF_init: AGGR0 ECC Init complete \n\n");
        }
    }

    return retValue;
}
\endcode

Once the ECC is configured, then error notifications will come to the ESM module, and will activate the ESM-registered application callback.
The application callback may want to retrive the error information in order to take some action based on the error, like clearing the ECC interrupts, logging the error information, or some other action:

\code{.c}
retVal = SDL_ECC_getESMErrorInfo(esmInst, intSrc, &eccmemtype, &eccIntrSrc);

/* Any additional customer specific actions can be added here */
retVal = SDL_ECC_getErrorInfo(eccmemtype, eccIntrSrc, &eccErrorInfo);
\endcode

To clear and acknowledge the ECC interrupt:

\code{.c}
if (eccErrorInfo.injectBitErrCnt != 0)
{
    SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_INJECT, eccErrorInfo.injectBitErrCnt);
}
else
{
    SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_NORMAL, eccErrorInfo.bitErrCnt);
}

retVal = SDL_ECC_ackIntr(eccmemtype, eccIntrSrc);

\endcode

Execute an ECC Self-Test for a specified ECC aggregator (memtype) and RAM Id (subtype):

\code{.c}

/* Run one shot test for M4FSS0 1 bit error */
injectErrorConfig.flipBitMask = 0x10;

#if defined (M4F_CORE)
/* Note the address is relative to start of ram */
injectErrorConfig.pErrMem = (uint32_t *)(0x100);
result = SDL_ECC_selfTest(geccMemType,
                          SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                          SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                          &injectErrorConfig,
                          100000);
#endif
#if defined (R5F_CORE)
/* Note the address is relative to start of ram */
injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
result = SDL_ECC_selfTest(geccMemType,
                          SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                          SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                          &injectErrorConfig,
                          100000);
#endif
if (result != SDL_PASS ) {
     DebugP_log("\r\n Single bit error self test at pErrMem 0x%p test failed",
                 injectErrorConfig.pErrMem);
    retVal = -1;
} else {

    DebugP_log("\r\n Single bit error self test at pErrMem 0x%p: test complete",
                injectErrorConfig.pErrMem);
}

return retVal;
\endcode

Inject an error for a specified ECC aggregator (memtype) and RAM Id (subtype)
\code{.c}

/* Note the address is relative to start of ram */
injectErrorConfig.pErrMem = (uint32_t *)(0x00);

/* Run one shot test for M4FSS0 1 bit error */
injectErrorConfig.flipBitMask = 0x10;
result = SDL_ECC_injectError(geccMemType,
                             SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IDRAM_ECC_RAM_ID,
                             SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                             &injectErrorConfig);


if (result != SDL_EFAIL ) {
    DebugP_log("\r\n Error inject at pErrMem 0x%p EFAIL test failed",
                injectErrorConfig.pErrMem);
    retVal = -1;
} else {
    /* Access the memory where injection is expected */
    testLocationValue = injectErrorConfig.pErrMem[0];

    DebugP_log("\r\n Error inject at pErrMem 0x%p: EFAIL test complete",
                injectErrorConfig.pErrMem);
}

return retVal;
\endcode

Read the Static registers:

\code{.c}

/* Read back the static registers */
result = SDL_ECC_getStaticRegisters(geccMemType, &staticRegs);
if (result != SDL_PASS) {
    /* print error and quit */
    DebugP_log("\r\nECC_Test_init: Error reading the static registers: result = %d\n\n");

    retValue = -1;
} else {
    DebugP_log("\r\nECC_Test_init: M4F Memtype Register Readback successful \n\n");
}
\endcode
## API

\ref SDL_ECC_MODULE
