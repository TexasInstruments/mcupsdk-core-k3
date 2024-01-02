/* Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     rti_main.c
 *
 *  \brief    This file contains rti test code.
 *
 *  \details  rti tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "rti_main.h"
#include <drivers/sciclient.h>
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
/* Unity functions */
void test_sdl_rti_baremetal_test_app_runner(void);
void test_sdl_rti_baremetal_test_app (void);

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/
sdlrtiTest_t  sdlrtiTestList[] = {
    {SDL_RTI_posTest,    "RTI POSITIVE TEST" ,        SDL_APP_TEST_NOT_RUN },
    {SDL_RTI_negTest,    "RTI NEGATIVE TEST" ,        SDL_APP_TEST_NOT_RUN },
    {NULL,               "TERMINATING CONDITION",     SDL_APP_TEST_NOT_RUN }
};

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/


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

#if defined (SOC_AM62X) || defined (SOC_AM62PX)
#define RTI_NUM_DEVICES SDL_RTI_MAX_INSTANCE
uint32_t RTI_devices[RTI_NUM_DEVICES] =
{
    TISCI_DEV_MCU_RTI0,
    TISCI_DEV_RTI0,
    TISCI_DEV_RTI1,
    TISCI_DEV_RTI2,
    TISCI_DEV_RTI3,
    TISCI_DEV_RTI15,
    TISCI_DEV_WKUP_RTI0
};
#endif
#if defined (SOC_AM62AX)
#define RTI_NUM_DEVICES SDL_RTI_MAX_INSTANCE
uint32_t RTI_devices[RTI_NUM_DEVICES] =
{
    TISCI_DEV_MCU_RTI0,
    TISCI_DEV_RTI0,
    TISCI_DEV_RTI1,
    TISCI_DEV_RTI2,
    TISCI_DEV_RTI3,
    TISCI_DEV_RTI4,
    TISCI_DEV_WKUP_RTI0
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
            printf("   RTI Sciclient_pmSetModuleState 0x%x ...FAILED: retValue %d\n",
                        RTI_devices[i], status);
        }
    }

    return status;
}

/*===========================================================================*/
/*                         Function definitions                              */
/*===========================================================================*/

void test_sdl_rti_baremetal_test_app (void)
{
    /* Declarations of variables */
    int32_t    testResult = SDL_APP_TEST_PASS;
    int32_t    i;

    /* Init dpl */
    sdlApp_dplInit();

    DebugP_log("\n rti Test Application\r\n");

	 /* Init the RTI modules */
        sdlApp_initRTI();

    for ( i = 0; sdlrtiTestList[i].testFunction != NULL; i++)
    {
        testResult = sdlrtiTestList[i].testFunction();
        sdlrtiTestList[i].testStatus = testResult;
    }

    testResult = SDL_APP_TEST_PASS;
    for ( i = 0; sdlrtiTestList[i].testFunction != NULL; i++)
    {
        if (sdlrtiTestList[i].testStatus != SDL_APP_TEST_PASS)
        {
            DebugP_log("Test Name: %s  FAILED \n", sdlrtiTestList[i].name);
            testResult = SDL_APP_TEST_FAILED;
            break;
        }
        else
        {
            DebugP_log("Test Name: %s  PASSED \n", sdlrtiTestList[i].name);
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

void test_sdl_rti_baremetal_test_app_runner(void)
{

    test_sdl_rti_baremetal_test_app();

    return;
}

int32_t test_main(void)
{

    test_sdl_rti_baremetal_test_app_runner();

    return 0;
}

/* Nothing past this point */
