/*
 *   Copyright (c) Texas Instruments Incorporated 2023
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

 /**
 *  \file    ecc_trigger.c
 *
 *  \brief    This file contains functions that provide input event triggers
 *            for the Error Correcting Code (ECC) Module application.
 *
 *  \details  ECC Safety Example module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <sdl/sdl_esm.h>
#include "ecc_main.h"
#include <sdl/dpl/sdl_dpl.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* delay for 1us*/
#define DELAY 1
#if defined (M4F_CORE)
/* Initialization structure for WKUP ESM instance */
static SDL_ESM_config ECC_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x01bfd837, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                },
    .priorityBitmap = {0x01bfd837, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    .errorpinBitmap = {0x01bfd837, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                      },
};

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c0eu, 0x03c08000u,
                     0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c0eu, 0x03c08000u,
                       0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c0eu, 0x03c08000u,
                       0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif

#if defined (R5F_CORE)
/* Initialization structure for WKUP ESM instance */
static SDL_ESM_config ECC_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                },
    .priorityBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    .errorpinBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                      },
};

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c0eu, 0x03c08000u,
                     0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c0eu, 0x03c08000u,
                       0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c0eu, 0x03c08000u,
                       0x06cc0000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Defines */
#define MAIN_AGGR0_AGGR0_MAX_MEM_SECTIONS (2u)


int32_t ECC_Test_EsmInitHandlerInit(SDL_ESM_Inst esmInstType);
int32_t ECC_Example_init (void);

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


static uint32_t arg;
/*********************************************************************
* @fn      ECC_Example_init
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/
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
            DebugP_log("\rECC_Example_init: Error initializing MAIN ESM: result = %d\r\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\rECC_Example_init: Init MAIN ESM complete \r\n");
        }
    }

    if (retValue == SDL_APP_TEST_PASS) {
        /* Initialize WKUP ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_WKUP, SDL_ESM_applicationCallbackFunction, ptr);
        if (result != SDL_APP_TEST_PASS) {
            /* print error and quit */
            DebugP_log("\rECC_Example_init: Error initializing WKUP ESM: result = %d\r\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\rECC_Example_init: Init WKUP ESM complete \r\n");
        }
    }

    if (retValue == SDL_APP_TEST_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR, &ECC_Test_AGGR0A0ECCInitConfig);
        if (result != SDL_APP_TEST_PASS) {
            /* print error and quit */
             DebugP_log("\rSDTF_init: Error initializing M4F core ECC: result = %d\r\n", result);

            retValue = SDL_APP_TEST_FAILED;
        } else {
            DebugP_log("\r\n\nSDTF_init: AGGR0 ECC Init complete \r\n");
        }
    }

    return retValue;
}


/*********************************************************************
 * @fn    runECC2BitAGGR0InjectTest
 *
 * @brief   Execute ECC Doule bit error example test on AGGR0 ECC aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t runECC2BitAGGR0_RAMInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=SDL_APP_TEST_PASS;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    DebugP_log("\r\n\n AGGR0 Double bit error inject Example test UC-2: starting");

    /* Run one shot test for AGGR0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x100u);

    injectErrorConfig.flipBitMask = 0x5;
    injectErrorConfig.chkGrp = 0x1;

    subType = SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_IAM62_MAIN_IPCSS_CBASS_MAIN_0_AM62_MAIN_IPCSS_CBASS_HSM_CLK_2_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_2_BUSECC_RAM_ID;

    result = SDL_ECC_injectError(SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR,
                                subType,
                                SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                &injectErrorConfig);

    if (result != SDL_APP_TEST_PASS ) {
        DebugP_log("\r\n\n AGGR0  Double bit error inject test: Subtype %d: test failed",
                    subType);
        retVal = SDL_APP_TEST_FAILED;
    } else {
        DebugP_log("\r\n\n AGGR0 Double bit error inject test: Subtype 0x%p test complete",
                    subType);
    }

    return retVal;
}

int32_t runECC2BitAGGR0_InjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    DebugP_log("\r\n\n AGGR0 Double bit error inject Example test UC-1: starting");

    /* Run one shot test for AGGR0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0u);

    injectErrorConfig.flipBitMask = 0x5;
    injectErrorConfig.chkGrp = 0x1;

    subType = SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_AM62_MAIN_CENTRAL_CBASS_HSM_CLK_1_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_1_BUSECC_RAM_ID;

    result = SDL_ECC_injectError(SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR,
                              subType,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig);

    if (result != SDL_APP_TEST_PASS ) {
        DebugP_log("\r\n\n AGGR0  Double bit error inject test: Subtype %d: test failed",
                    subType);
        retVal = SDL_APP_TEST_FAILED;
    } else {
        DebugP_log("\r\n\n AGGR0 Double bit error inject test: Subtype 0x%p test complete",
                    subType);
    }

    return retVal;
}

int32_t ECC_Test_runECC1BitAGGR0ParityInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

     DebugP_log("\r\n\n\n\n**** AGGR0 Memory Parity TEST ****\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    /* Run one shot test for AGGR0_BUSECC_RAM 1 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0u);

    injectErrorConfig.flipBitMask = 0x1;
    injectErrorConfig.chkGrp = SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_AM62_MAIN_CENTRAL_CBASS_HSM_CLK_1_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_1_BUSECC_GROUP_3_ID;
    subType = SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR_AM62_MAIN_CENTRAL_CBASS_HSM_CLK_1_CLK_EDC_CTRL_CBASS_INT_HSM_CLK_1_BUSECC_RAM_ID;

    result = SDL_ECC_injectError(SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR,
                                subType,
                                SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                &injectErrorConfig);

    if (result != SDL_APP_TEST_PASS ) {
        DebugP_log("\r\n\n AGGR0  Single bit error self test: Subtype %d: test failed",
                    subType);
        retVal = SDL_APP_TEST_FAILED;
    } else {
        DebugP_log("\r\n\n AGGR0 Single bit error self test: Subtype 0x%p test complete",
                    subType);
    }

    return retVal;
}


static int32_t ECC_sdlFuncTest(void)
{
    int32_t result;
    int32_t retVal = 0;
    uint32_t maxTimeOutMilliSeconds = 10000;
    uint32_t timeOutCnt = 0;

    DebugP_log("\r\n\n ESM Safety Example tests: starting");

    if (retVal == SDL_APP_TEST_PASS)
    {
        result = runECC2BitAGGR0_InjectTest();
        if (result == SDL_APP_TEST_PASS)
        {
        DebugP_log("\r\n\n Waiting for ESM Interrupt \r\n");
        do
            {
                /* dummy wait for the interrupt */
                SDL_DPL_delay(DELAY);;
                timeOutCnt += 10;
                if (timeOutCnt > maxTimeOutMilliSeconds)
                {
                    result = SDL_EFAIL;
                    break;
                }
            } while (esmError == false);
        }
        if(result == SDL_APP_TEST_PASS){
            DebugP_log("\r\n\nUC-1: Got Low priority ESM Interrupt \r\n");
            esmError = false;
        }

        if (result != SDL_APP_TEST_PASS) {
            retVal = SDL_APP_TEST_FAILED;
            DebugP_log("\r\n\nESM_ECC_Example_run: UC-1 has failed...");
            /* UC-1 Low priority AGGR0 interrupt */
        }
    }

    if (retVal == SDL_APP_TEST_PASS)
    {
        result = runECC2BitAGGR0_RAMInjectTest();
        if (result == SDL_APP_TEST_PASS)
        {
            DebugP_log("\r\n\n Waiting for ESM Interrupt \r\n");
        do
            {
                /* dummy wait for the interrupt */
                SDL_DPL_delay(DELAY);;
                timeOutCnt += 10;
                if (timeOutCnt > maxTimeOutMilliSeconds)
                {
                    result = SDL_EFAIL;
                    break;
                }
            } while (esmError == false);
        }
        if(result == SDL_APP_TEST_PASS){
            DebugP_log("\r\n\n UC-2: Got High priority ESM Interrupt \r\n");
            esmError = false;
        }

        if (result != SDL_APP_TEST_PASS) {
            retVal = SDL_APP_TEST_FAILED;
            DebugP_log("\r\n\n ESM_ECC_Example_run: UC-2 has failed....");
            /* UC-2 High priority AGGR0 interrupt */
        }
    }

    if (retVal == SDL_APP_TEST_PASS)
    {
        result = ECC_Test_runECC1BitAGGR0ParityInjectTest();
        if (result == SDL_APP_TEST_PASS)
        {
        DebugP_log("\r\n\n Waiting for ESM Interrupt \r\n");
        do
            {
                /* dummy wait for the interrupt */
                SDL_DPL_delay(DELAY);;
                timeOutCnt += 10;
                if (timeOutCnt > maxTimeOutMilliSeconds)
                {
                    result = SDL_EFAIL;
                    break;
                }
            } while (esmError == false);
        }
        if(result == SDL_APP_TEST_PASS){
            DebugP_log("\r\n\n Memory Parity Error Test Complete \r\n");
            esmError = false;
        }

        if (result != SDL_APP_TEST_PASS) {
            retVal = SDL_APP_TEST_FAILED;
            DebugP_log("\r\n\n Memory Parity Error Test has failed...");
        }
    }


    if ( retVal == SDL_APP_TEST_PASS) {
        DebugP_log("\r\n\n ECC Safety Example tests: success");
    } else {
        DebugP_log("\r\n\n ECC Safety Example tests: failed");
    }

    return retVal;
}

/* ECC Function module test */
int32_t ECC_funcTest(void)
{
    int32_t testResult;

    testResult = ECC_Example_init();

    if (testResult != SDL_APP_TEST_PASS)
    {
        DebugP_log("\r\n\n ECC Safety Example tests: unsuccessful");
        return SDL_EFAIL;
    }

    testResult = ECC_sdlFuncTest();


    return (testResult);
}

/* Nothing past this point */
