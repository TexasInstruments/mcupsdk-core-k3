/*
 *  Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     rti_app_main.c
 *
 *  \brief    This file contains RTI Example test code.
 *
 *  \details  RTI tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "rti_app_main.h"
#if defined (SOC_AM62X) || defined (SOC_AM62AX)
#include <drivers/sciclient.h>
#endif
#include <sdl/sdl_esm.h>
#include <sdl/sdl_rti.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"


/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/
/* None */

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/
/* None */

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

void test_sdl_rti_baremetal_test_app (void);
/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/
sdlRtiTest_t  sdlRtiTestList[] = {
    {SDL_RTI_exampleTest, "RTI EXAMPLE TEST" ,     SDL_APP_TEST_NOT_RUN },
    {NULL,             "TERMINATING CONDITION",  SDL_APP_TEST_NOT_RUN }
};

#if defined (SOC_AM62X)
#if defined (M4F_CORE)
SDL_ESM_config RTI_Test_esmInitConfig_wkup =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0xffffffffu, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0xffffffffu, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0xffffffffu, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};
#endif
#if defined (R5F_CORE)
SDL_ESM_config RTI_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0x000000e0u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000008u,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                     0x00000000u, 0x00000008u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x00000000u, 0x000000e0u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000008u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};
#endif
#endif
#if defined (SOC_AM62AX)
SDL_ESM_config RTI_Test_esmInitConfig_wkup =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
	.enableBitmap = {0x00000007u, 0x00000000u, 0x00200000u, 0x00000000u,
					  0x00000000u, 0x00000000u,
					 },
	/**< All events enable: except timer and self test  events, */
	/*    and Main ESM output.Configured based off esmErrorConfig to test high or low priorty events.*/
	.priorityBitmap = {0x00000007u, 0x00000000u, 0x00200000u, 0x00000000u,
						0x00000000u, 0x00000000u,
					   },
	/**< Configured based off esmErrorConfig to test high or low priorty events. */
	.errorpinBitmap = {0x00000007u, 0x00000000u, 0x00200000u, 0x00000000u,
						 0x00000000u, 0x00000000u,
						},
	/**< All events high priority:  */
};
#endif

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
static uint32_t arg;
/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

/*===========================================================================*/
/*                         Local Function definitions                        */
/*===========================================================================*/

#if defined (SOC_AM62X) || defined (SOC_AM62AX)
#define RTI_NUM_DEVICES 1
uint32_t RTI_devices[RTI_NUM_DEVICES] =
{
    TISCI_DEV_MCU_RTI0,
};
#endif

static int32_t sdlApp_initRTI(void)
{
    int32_t status = SDL_PASS;
    uint32_t i;

    for (i = 0; i < RTI_NUM_DEVICES; i++)
    {
        /* Power up RTI */
        status = Sciclient_pmSetModuleState(RTI_devices[i],
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);

        if (status != SDL_PASS)
        {
            DebugP_log("   RTI Sciclient_pmSetModuleState 0x%x ...FAILED: retValue %d\n",
                        RTI_devices[i], status);
        }
    }

    return status;
}

static int32_t sdlApp_dplInit(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    ret = SDL_TEST_dplInit();
    if (ret != SDL_PASS)
    {
        DebugP_log("Error: Init Failed\n");
    }

    return ret;
}
/*===========================================================================*/
/*                         Function definitions                              */
/*===========================================================================*/

void test_sdl_rti_baremetal_test_app (void)
{
    /* Declarations of variables */
    int32_t    testResult = SDL_APP_TEST_PASS;
    int32_t    i, result;
    void *ptr = (void *)&arg;
    DebugP_log("\n RTI Example Test Application\r\n");

	/* Init dpl */
    sdlApp_dplInit();
    /* Init the RTI modules */
    sdlApp_initRTI();
	
#if defined (SOC_AM62X)
#if defined (M4F_CORE)
    /* Initialize WKUP ESM module */
    result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &RTI_Test_esmInitConfig_wkup, SDL_ESM_applicationCallbackFunction, ptr);
#endif
#if defined (R5F_CORE)
    /* Initialize MAIN ESM module */
    result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &RTI_Test_esmInitConfig_MAIN, SDL_ESM_applicationCallbackFunction, ptr);
#endif
#endif
#if defined (SOC_AM62AX)
    /* Initialize MAIN ESM module */
    result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &RTI_Test_esmInitConfig_wkup, SDL_ESM_applicationCallbackFunction, ptr);
#endif

    if (result != SDL_PASS)
    {
        /* print error and quit */
#if defined (SOC_AM62X)
#if defined (M4F_CORE)
         DebugP_log("RTI_Test_init: Error initializing WKUP ESM: result = %d\n", result);
#endif
#if defined (R5F_CORE)
		 DebugP_log("RTI_Test_init: Error initializing MAIN ESM: result = %d\n", result);
#endif
#endif
#if defined (SOC_AM62AX)
		 DebugP_log("RTI_Test_init: Error initializing WKUP ESM: result = %d\n", result);
#endif
	}
    else
    {
#if defined (SOC_AM62X)
#if defined (M4F_CORE)
        DebugP_log("\nRTI_Test_init: Init WKUP ESM complete \n\n");
#endif
#if defined (R5F_CORE)
		DebugP_log("\nRTI_Test_init: Init MAIN ESM complete \n\n");
#endif
#endif
#if defined (SOC_AM62AX)
		DebugP_log("\nRTI_Test_init: Init WKUP ESM complete \n\n");
#endif
	}

    for ( i = 0; sdlRtiTestList[i].testFunction != NULL; i++)
    {
        testResult = sdlRtiTestList[i].testFunction();
        sdlRtiTestList[i].testStatus = testResult;
    }

    testResult = SDL_APP_TEST_PASS;
    for ( i = 0; sdlRtiTestList[i].testFunction != NULL; i++)
    {
        if (sdlRtiTestList[i].testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("Test Name: %s  FAILED \n", sdlRtiTestList[i].name);
            testResult = SDL_APP_TEST_FAILED;
            break;
        }
        else
        {
            DebugP_log("Test Name: %s  PASSED \n", sdlRtiTestList[i].name);
        }
    }

    if (testResult == SDL_APP_TEST_PASS)
    {
        DebugP_log("\n All tests have passed. \n");
    }
    else
    {
        DebugP_log("\n Few/all tests Failed \n");
    }
}

int32_t sdl_rti_example_uc3_main(void)
{
	Drivers_open();
	Board_driversOpen();
    test_sdl_rti_baremetal_test_app();
	Board_driversClose();
	Drivers_close();
    /* Stop the test and wait here */
    return 0;
}

/* Nothing past this point */
