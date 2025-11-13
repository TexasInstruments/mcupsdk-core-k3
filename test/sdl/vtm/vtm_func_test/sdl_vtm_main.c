/*
 * VTM Test Application
 *
 * Voltage and Thermal Monitor (VTM) Test Application
 *
 *  Copyright (C) 2023-2025 Texas Instruments Incorporated
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
 */
/**
 *  \file vtm_main.c
 *
 *  \brief This file contains functions that provide main function
 *         for the Voltage and Thermal Monitor (VTM) application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* For Timer functions */
#include <kernel/dpl/DebugP.h>
#include <dpl_interface.h>
#include <sdl/esm/sdl_esm_priv.c>
#include "event_trig.h"
#include <sdl/sdl_esm.h>
#include <sdl/include/sdl_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define USE_CASES_RUN         (5)
#define USE_CASES             (5)
#define START_USE_CASE        (0)
#define MAX_ESM_EVENTS_LOGGED (20)
#define APP_ARG (1)

/* #define DEBUG */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t deactivateTrigger(SDL_ESM_Inst esmInstType,
                                 SDL_ESM_IntType esmIntType,
                                 uint32_t intEsmSrc);
static const char *printTestCaseStepResult(uint32_t result);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t totalEventsLogged   = 0;
static uint32_t totalHiEventsLogged = 0;
static uint32_t totalLoEventsLogged = 0;
static int32_t  thresholdsReset     = 0;
int32_t apparg = APP_ARG;

/* ESM event log entry */
typedef struct
{
    SDL_ESM_Inst esmInstance;
    SDL_ESM_IntType      intType;
    uint32_t             grpChannel;
    uint32_t             index;
    uint32_t             intSrc;
    uint8_t              useCaseNum;
} ESM_Example_log_entry_t;

static ESM_Example_log_entry_t esmEventLog[MAX_ESM_EVENTS_LOGGED];


/* State variable for each test case indicating input event trigger
 * has been completed */
volatile uint32_t esmEventInputTrig[USE_CASES] = {TEST_CASE_STATUS_NOT_RUN,
                                                  TEST_CASE_STATUS_NOT_RUN,
                                                  TEST_CASE_STATUS_NOT_RUN,
                                                  TEST_CASE_STATUS_NOT_RUN,
                                                  TEST_CASE_STATUS_NOT_RUN};

/* State variable for each test case indicating the ISR for the test case
 * has been completed */
volatile uint32_t esmOutputResult[USE_CASES] = {TEST_CASE_STATUS_NOT_RUN,
                                                TEST_CASE_STATUS_NOT_RUN,
                                                TEST_CASE_STATUS_NOT_RUN,
                                                TEST_CASE_STATUS_NOT_RUN,
                                                TEST_CASE_STATUS_NOT_RUN};


volatile uint8_t currTestCase = START_USE_CASE;

/* Flag to indicate callback triggered */
volatile bool VTM_intrDone = false;

/* Initialization structure for MAIN ESM instance */
#if defined (SOC_AM62X)
#if defined (R5F_CORE)
static SDL_ESM_config VTM_Test_esmInitConfig_Main =
{
 .esmErrorConfig = {0u, 3u}, /* Self test error config */
 .enableBitmap = {0x00000000u, 0x000000e0u, 0x00000000u, 0x00000000u,
                  0x00000700u, 0x00000000u,
                 },
      /**< All events enable: except timer and self test  events, */
     /*    and Main ESM output.Configured based off esmErrorConfig to test high or low priorty events.*/
 .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                    0x00000400u, 0x00000000u,
                   },
     /**< Configured based off esmErrorConfig to test high or low priorty events. */
  .errorpinBitmap = {0x00000000u, 0x000000e0u, 0x00000000u, 0x00000000u,
                     0x00000700u, 0x00000000u,
                    },
    /**< All events high priority:  */
};
#endif
/* Initialization structure for WKUP ESM instance */
#if defined (M4F_CORE)
static SDL_ESM_config VTM_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x00000707u, 0x00000000u, 0x00000000u,
                },
     /**< All events enable: except clkstop events for unused clocks */
    .priorityBitmap = {0x00000407u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks */
    .errorpinBitmap = {0x00000407u, 0x00000000u, 0x00000000,
                      },
    /**< All events high priority: except clkstop for unused clocks */
};
#endif
#endif
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
static SDL_ESM_config VTM_Test_esmInitConfig_Main =
{
 .esmErrorConfig = {0u, 3u}, /* Self test error config */
 .enableBitmap = {0x00000707u, 0x00000000u, 0x00000000u, 0x00000000u,
                  0x00000000u, 0x00000000u,
                 },
      /**< All events enable: except timer and self test  events, */
     /*    and Main ESM output.Configured based off esmErrorConfig to test high or low priorty events.*/
 .priorityBitmap = {0x00000407u, 0x00000000u, 0x00000000u, 0x00000000u,
                    0x00000000u, 0x00000000u,
                   },
     /**< Configured based off esmErrorConfig to test high or low priorty events. */
  .errorpinBitmap = {0x00000707u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000000u,
                    },
    /**< All events high priority:  */
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static const char *printEsmIntType(SDL_ESM_IntType esmIntType)
{
    char *pStr;

    switch(esmIntType)
    {
        case SDL_ESM_INT_TYPE_HI:
            pStr = "High Priority ESM event";
            break;
        case SDL_ESM_INT_TYPE_LO:
            pStr = "Low Priority ESM event";
            break;
        case SDL_ESM_INT_TYPE_CFG:
            pStr = "Config ESM event";
            break;
        default:
            pStr = NULL;
            break;
    }

    return pStr;
}

int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                         SDL_ESM_IntType esmIntType,
                                         uint32_t grpChannel,
                                         uint32_t index,
                                         uint32_t intSrc,
                                         void *arg)
{
    /* Log the event */
    esmEventLog[totalEventsLogged].useCaseNum  = currTestCase;
    esmEventLog[totalEventsLogged].esmInstance = esmInstType;
    esmEventLog[totalEventsLogged].intType     = esmIntType;
    esmEventLog[totalEventsLogged].grpChannel  = grpChannel;
    esmEventLog[totalEventsLogged].index       = index;
    esmEventLog[totalEventsLogged].intSrc      = intSrc;

    totalEventsLogged++;
    if (esmIntType == SDL_ESM_INT_TYPE_HI) {
        totalHiEventsLogged++;
    } else if (esmIntType == SDL_ESM_INT_TYPE_LO) {
        totalLoEventsLogged++;
    }

    /* Any additional customer-specific actions to address ESM event
     * can be added here */

    deactivateTrigger(esmInstType, esmIntType, intSrc);

    esmOutputResult[currTestCase]= TEST_CASE_STATUS_COMPLETED_SUCCESS;
    /* Update flag to indicate callback was triggered */
    VTM_intrDone = true;

    return SDL_PASS;
}

/*********************************************************************
* @fn      VTM_ESM_init
*
* @brief   Initializes Board and ESM module
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/
int32_t VTM_ESM_init (void)
{
    int32_t retValue=0;
    int32_t result;

#if defined (SOC_AM62X)
#if defined (R5F_CORE)
		result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &VTM_Test_esmInitConfig_Main, SDL_ESM_applicationCallbackFunction, &apparg);
#endif
#if defined (M4F_CORE)
		result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &VTM_Test_esmInitConfig_WKUP, SDL_ESM_applicationCallbackFunction, &apparg);
#endif
#endif
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
		result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &VTM_Test_esmInitConfig_Main, SDL_ESM_applicationCallbackFunction, &apparg);
#endif
        if (result != SDL_PASS) {
            /* print error and quit */
			#if defined (SOC_AM62X)
			#if defined (R5F_CORE)
            DebugP_log("VTM_ESM_init: Error initializing MAIN ESM: result = %d\r\n", result);
			#endif
			#if defined (M4F_CORE)
			DebugP_log("VTM_ESM_init: Error initializing WKUP ESM: result = %d\r\n", result);
			#endif
			#endif
			#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
			DebugP_log("VTM_ESM_init: Error initializing WKUP ESM: result = %d\r\n", result);
            #endif

            retValue = -1;
        } else {
		    #if defined (SOC_AM62X)
			#if defined (R5F_CORE)
            DebugP_log("\r\nVTM_ESM_init: Init MAIN ESM complete \r\n");
			#endif
			#if defined (M4F_CORE)
			DebugP_log("\r\nVTM_ESM_init: Init WKUP ESM complete \r\n");
			#endif
			#endif
			#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
			DebugP_log("\r\nVTM_ESM_init: Init WKUP ESM complete \r\n");
			#endif
        }
    return retValue;
}


static int32_t deactivateTrigger(SDL_ESM_Inst esmInstType,
                                 SDL_ESM_IntType esmIntType,
                                 uint32_t intEsmSrc)
{
    int32_t retVal = 0;
	uint32_t esmInstBaseAddr;
#if defined (SOC_AM62X)
#if defined (R5F_CORE)
	SDL_ESM_getBaseAddr(SDL_ESM_INST_MAIN_ESM0, &esmInstBaseAddr);
    if ((esmInstType == SDL_ESM_INST_MAIN_ESM0) && (esmIntType == SDL_ESM_INT_TYPE_LO)) {
        /* UC-1: Low Priority interrupt on MAIN ESM -
         * VTM greater than THR1 */
        if (intEsmSrc ==
                SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH1_INTR_0)
		{
#endif
#if defined (M4F_CORE)
	SDL_ESM_getBaseAddr(SDL_ESM_INST_WKUP_ESM0, &esmInstBaseAddr);
    if ((esmInstType == SDL_ESM_INST_WKUP_ESM0) && (esmIntType == SDL_ESM_INT_TYPE_LO)) {
        /* UC-1: Low Priority interrupt on WKUP ESM -
         * VTM greater than THR1 */
        if (intEsmSrc ==
            SDLR_WKUP_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH1_INTR_0)
        {
#endif
#endif
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
        SDL_ESM_getBaseAddr(SDL_ESM_INST_WKUP_ESM0, &esmInstBaseAddr);
        if ((esmInstType == SDL_ESM_INST_WKUP_ESM0) && (esmIntType == SDL_ESM_INT_TYPE_LO)) {
        /* UC-1: Low Priority interrupt on MAIN ESM -
         * VTM greater than THR1 */
        if (intEsmSrc ==
                SDLR_WKUP_ESM0_ESM_LVL_EVENT_WKUP_VTM0_THERM_LVL_GT_TH1_INTR_0)
		{
#endif
            if (currTestCase == 0)
            {
                if (thresholdsReset == 0)
                {
                    /* Simulate thresholds as if temperature is going to be reduced
                     * below lt_Thr0 */
                    vtm_setNormalThresholds();

                    thresholdsReset = 1;
                }
                vtm_GtThr1CrossedUpdateInt();
            } else if ((currTestCase == 1) || (currTestCase == 2))
            {
                if (thresholdsReset == 0)
                {
                    /* Don't do anything as we want to simulate further increase of temperature */

                    thresholdsReset = 1;
                }
                vtm_GtThr1CrossedUpdateInt();
            }
#if defined (SOC_AM62X)
#if defined (R5F_CORE)
        } else if (intEsmSrc == SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_LT_TH0_INTR_0)
		{
#endif
#if defined (M4F_CORE)
        } else if (intEsmSrc == SDLR_WKUP_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_LT_TH0_INTR_0)
		{
#endif
#endif
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
        } else if (intEsmSrc == SDLR_WKUP_ESM0_ESM_LVL_EVENT_WKUP_VTM0_THERM_LVL_LT_TH0_INTR_0)
        {
#endif
            vtm_LtThr0CrossedUpdateInt();

            thresholdsReset = 0;
            esmOutputResult[currTestCase] = TEST_CASE_STATUS_COMPLETED_SUCCESS;
            if (currTestCase == 1) {
                /* At end of this test case, clear the Pin that was left on
                 * throughout the test case*/
            }
        }
#if defined (SOC_AM62X)
#if defined (R5F_CORE)
    } else if ((esmInstType == SDL_ESM_INST_MAIN_ESM0) &&
               (esmIntType == SDL_ESM_INT_TYPE_HI)) {
#endif
#if defined (M4F_CORE)
    } else if ((esmInstType == SDL_ESM_INST_WKUP_ESM0) &&
               (esmIntType == SDL_ESM_INT_TYPE_HI)) {
#endif
#endif
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || defined (SOC_J722S)
	} else if ((esmInstType == SDL_ESM_INST_WKUP_ESM0) &&
               (esmIntType == SDL_ESM_INT_TYPE_HI)) {
#endif
        if ((currTestCase == 1) || (currTestCase == 2)) {
            /* TC-2: High Priority interrupt on MCU ESM -
             * VTM greater than THR2 */
            /* TC-3: High Priority interrupt on MCU ESM */
            if (thresholdsReset == 1)
            {
                /* Simulate thresholds as if temperature is going to be reduced
                 * below lt_Thr0 */
                vtm_setNormalThresholds();

                thresholdsReset = 2;
            }
            if (currTestCase == 2) {

            }
            vtm_GtThr2CrossedUpdateInt();
        } else {
            retVal = -1;
        }
    } else {
        DebugP_log("ERR: Unexpected ESM Instance %d and ESM Interrupt Type %d \r\n",
                    esmInstType, esmIntType);
        retVal = -1;
    }

   return (retVal);
}



/*********************************************************************
* @fn      VTM_test_printSummary
*
* @brief   Print summary of all the test cases run
*
* @param   None
*
* @return  None
*/
void VTM_test_printSummary(void)
{
    int32_t i;

    DebugP_log("\r\r\n\r\r\n");
    DebugP_log("ESM Example Application summary\r\n");
    DebugP_log("-------------------------------\r\n");
    DebugP_log("Completed %d Test Cases\r\n", currTestCase);
    DebugP_log("Received %d High Priority Interrupts\r\n", totalHiEventsLogged);
    DebugP_log("Received %d Low Priority Interrupts\r\n", totalLoEventsLogged);

    DebugP_log("\r\nTest Case Event Log\r\n");
    DebugP_log("------------------\r\n");
    for (i = 0; i < totalEventsLogged; i++) {
        DebugP_log("\r\nTest Case %d: ESM Call back function called : grpChannel 0x%x, " \
                    "index 0x%x, intSrc 0x%x \r\n",
                    esmEventLog[i].useCaseNum,
                    esmEventLog[i].grpChannel,
                    esmEventLog[i].index,
                    esmEventLog[i].intSrc);
        DebugP_log("  ESM instance #%d, ESM interrupt type = %s\r\n",
                    esmEventLog[i].esmInstance,
                    printEsmIntType(esmEventLog[i].intType));

    }
}

/*****************************************************************************
 * This is the main function for the Voltage and Thermal Monitor (VTM) example
 * application.
 * It runs through 5 test cases to demonstrate usage of the ESM modules
 * for receiving errors and controlling the error pin.
 */
void vtm_test_app(void)
{
    int32_t testErrCount = 0;
    int32_t retValue;
    uint8_t i;

    /* Initialize the ESM instances and handlers */
    retValue = VTM_ESM_init();

    if (retValue < 0) {
        /* print and exit */
        DebugP_log("\r\nERR: VTM_ESM_init failed");
        testErrCount++;
    }

    DebugP_log("\r\nESM example init complete");

    for (i = START_USE_CASE; i < 3; i++) {
        retValue = vtm_runTestCaseTrigger(i);

        if (retValue != 0) {
            DebugP_log("\r\nERR: Test Case Trigger for Test Case %d failed \r\n",
                        retValue);
            break;
        }

		while((esmEventInputTrig[i] == TEST_CASE_STATUS_NOT_RUN) ||
              (esmOutputResult[i] == TEST_CASE_STATUS_NOT_RUN))
        {
#ifdef DEBUG
            DebugP_log("InputTrig = %d, OutputResult = %d\r\n",
                        esmEventInputTrig[i],
                        esmOutputResult[i]);
#endif
        }

        DebugP_log("\r\nTest Case %d completed: Input Event Trigger = %s, \r\n" \
                    "                       Event Handler Complete = %s, \r\n",
                    i,
                    printTestCaseStepResult(esmEventInputTrig[i]),
                    printTestCaseStepResult(esmOutputResult[i]));
        currTestCase++;
    }

    /* Check results of all the tests */
    for (i = 0; i < 3; i++) {
        if ((esmEventInputTrig[i] != TEST_CASE_STATUS_COMPLETED_SUCCESS) ||
            (esmOutputResult[i] != TEST_CASE_STATUS_COMPLETED_SUCCESS)) {
            testErrCount++;
        }
    }

    /* Print results and logs of the Test Cases */
    VTM_test_printSummary();
    DebugP_log("\r\nESM Example Application: Complete");

    if (testErrCount == 0)
    {
        DebugP_log("\r\n All tests have passed. \r\n");
    }
    else
    {
        DebugP_log("\r\n ESM Example app failed. \r\n");
    }
    return;
}

static const char *printTestCaseStepResult(uint32_t result)
{
    char *pStr;

    switch(result)
    {
        case TEST_CASE_STATUS_NOT_RUN:
            pStr = "Step Not yet run";
            break;
        case TEST_CASE_STATUS_COMPLETED_SUCCESS:
            pStr = "Step completed successfully";
            break;
        case TEST_CASE_STATUS_COMPLETED_FAILURE:
            pStr = "Step completed with failure";
            break;
        default:
            pStr = NULL;
            break;
    }

    return pStr;
}
#ifdef UNITY_INCLUDE_CONFIG_H
/*
 *  ======== Unity set up and tear down ========
 */
void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}
#endif

int32_t VTM_dplInit(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    ret = SDL_TEST_dplInit();
    if (ret != SDL_PASS)
    {
        DebugP_log("Error: Init Failed\r\n");
    }

    return ret;
}

void test_sdl_vtm_test_app_runner(void)
{
#if defined(UNITY_INCLUDE_CONFIG_H)
    UNITY_BEGIN();
    RUN_TEST (vtm_test_app);
    UNITY_END();
    /* Function to print results defined in our unity_config.h file */
    print_unityOutputBuffer_usingUARTstdio();
#else
    vtm_test_app();
#endif
    return;
}

int32_t test_main(void)
{
    VTM_dplInit();

    DebugP_log("\r\nVTM Test Application\r\n");
    (void)test_sdl_vtm_test_app_runner();

	return 0;
}

/* Nothing past this point */
