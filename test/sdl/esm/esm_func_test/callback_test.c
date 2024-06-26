/* Copyright (c) 2021-24 Texas Instruments Incorporated
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
 *  \file     callback_test.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM tests
 **/


#include <kernel/dpl/DebugP.h>
#include <sdl/sdl_esm.h>
#include "esm_test_main.h"
#define SDTF_NUM_RUNALL_TEST_COMMANDS    10

#if defined (SOC_AM64X)
#define APP_ESM_INSTANCE  SDL_ESM_INST_MCU_ESM0
#elif defined (SOC_AM62X)
#define APP_ESM_INSTANCE  SDL_ESM_INST_WKUP_ESM0
#endif

#if defined (SOC_AM62AX) || defined (SOC_AM62PX)
#define APP_ESM_INSTANCE  SDL_ESM_INST_WKUP_ESM0
#endif
volatile uint8_t cfg_triggered = 0x0u;


#if defined (SOC_AM64X) ||	defined (SOC_AM62X)
#if defined (M4F_CORE)
SDL_ESM_config SDTF_esmInitConfig_Inst_appcallback =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x00000007u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x0000003u, 0xff0ffffeu, 0x7fffffffu, 0x00000007u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config SDTF_esmInitConfig_MAIN_appcallback =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0xffffffffu,
                 0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                 0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                 0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0xffffffffu,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0x00000001u,
                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0xffffffffu,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0xffffffffu,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
#endif

#if defined (SOC_AM62X) ||defined (SOC_AM62AX) || defined (SOC_AM62PX)
#if defined (R5F_CORE)
SDL_ESM_config SDTF_esmInitConfig_Inst_appcallback =
{

    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,},
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x0000000u, 0xff0ffffeu, 0x7fffffffu, 0x00000007u, },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,},
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config SDTF_esmInitConfig_MAIN_appcallback =
{

    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0xffffffffu,
                 0xfffff380u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                 0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                 0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0xffffffffu,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0x00000001u,
                         0xfffff380u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0xffffffffu,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x00000000u, 0xfffffffbu, 0x7fffffffu, 0xffffffffu,
                       0xfffff380u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0xffffffffu,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
#endif
extern int32_t SDR_ESM_errorInsert (const SDL_ESM_Inst esmInstType,
                                const SDL_ESM_ErrorConfig_t *esmErrorConfig);

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                         SDL_ESM_IntType esmIntType,
                                         uint32_t grpChannel,
                                         uint32_t index,
                                         uint32_t intSrc,
                                         void *arg);

void  esm_init_appcb(SDL_ESM_Inst esmType)
{
    SDL_ErrType_t result;
    /* Initialize MAIN ESM module */
    if(esmType == APP_ESM_INSTANCE)
    {
        result = SDL_ESM_init(esmType, &SDTF_esmInitConfig_Inst_appcallback,SDL_ESM_applicationCallbackFunction, NULL);
    }
    else
    {
        result = SDL_ESM_init(esmType, &SDTF_esmInitConfig_MAIN_appcallback,SDL_ESM_applicationCallbackFunction, NULL);
    }

    if (result != SDL_PASS)
	{
        /* print error and quit */
        if(esmType == APP_ESM_INSTANCE)
        {
#if defined(SOC_AM64X)
            DebugP_log("ESM_ECC_Example_init: Error initializing MCU ESM: result = %d\n", result);
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
           DebugP_log("ESM_ECC_Example_init: Error initializing WKUP ESM: result = %d\n", result);
#endif
        }
		else
		{

            DebugP_log("ESM_ECC_Example_init: Error initializing MAIN ESM: result = %d\n", result);
        }
    }
	else
	{
        if(esmType == APP_ESM_INSTANCE)
        {
#if defined(SOC_AM64X)
            DebugP_log("\nESM_ECC_Example_init: Init MCU ESM complete \n");
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
			DebugP_log("\nESM_ECC_Example_init: Init WKUP ESM complete \n");
#endif
        }
		else
		{
            DebugP_log("\nESM_ECC_Example_init: Init MAIN ESM complete \n");
        }
    }
}

/*********************************************************************
 * @fn      SDTF_runESMInject
 *
 * @brief   Execute ESM Inject
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
static int32_t SDTF_runESMInjectInstance(SDL_ESM_Inst esmType,
                                         uint32_t groupNumber,
                                         uint32_t bitNumber)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ESM_ErrorConfig_t esmErrorConfig;

    esmErrorConfig.groupNumber = groupNumber;
    esmErrorConfig.bitNumber = bitNumber;

    DebugP_log("\n ESM inject: test starting for Esm instance %d \n", esmType);

    /* Run esm test 2*/
    result = SDR_ESM_errorInsert(esmType, &esmErrorConfig);

    if (result != SDL_PASS ) {
        DebugP_log("\n ESM inject test for Esm instance %d failed \n", esmType);
        retVal = -1;
    } else {
        DebugP_log("\n ESM inject test for Esm instance %d Done \n", esmType);

    }
    SDL_ESM_clrNError(esmType);
    return retVal;
}

static int32_t SDTF_runESMInjectCfgInstance(SDL_ESM_Inst esmType,
                                            uint32_t groupNumber)
{
    uint32_t esmInstBaseAddr;
    int32_t retVal;

    SDL_ESM_getBaseAddr(esmType, &esmInstBaseAddr);
    retVal = SDL_ESM_setCfgIntrStatusRAW (esmInstBaseAddr, groupNumber);
    return retVal;
}
#if defined(SOC_AM64X)
int32_t SDTF_runESMInjectCfg_MCU(void)
{
    int32_t retVal = 0x0;

    cfg_triggered = 0x0;

    esm_init_appcb(APP_ESM_INSTANCE);
    SDTF_runESMInjectCfgInstance(APP_ESM_INSTANCE, 0x1);
    while(cfg_triggered != 0x1);

    cfg_triggered = 0x0;
    return retVal;
}
#endif


#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
int32_t SDTF_runESMInjectCfg_WKUP(void)
{
    int32_t retVal = 0x0;

    cfg_triggered = 0x0;
#if defined (R5F_CORE)
    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
#endif
    esm_init_appcb(APP_ESM_INSTANCE );
    SDTF_runESMInjectCfgInstance(APP_ESM_INSTANCE , 0x1);

    while(cfg_triggered != 0x1);

    cfg_triggered = 0x0;
    return retVal;
}
#endif


int32_t SDTF_runESMInjectCfg_MAIN(void)
{
    int32_t retVal = 0x0;

    cfg_triggered = 0x0;

    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
    SDTF_runESMInjectCfgInstance(SDL_ESM_INST_MAIN_ESM0, 0x1);

    while(cfg_triggered != 0x1);

    cfg_triggered = 0x0;
    return retVal;
}

/*********************************************************************
 * @fn      SDTF_runESMInjectHigh_MCU
 *
 * @brief   Execute ESM Inject for MCU
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
#if defined (SOC_AM64X)
int32_t SDTF_runESMInjectHigh_MCU(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE);
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE, 1, 4);

    return retVal;
}

int32_t SDTF_runESMInjectLow1_MCU(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE);
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE, 1, 0);

    return retVal;
}

int32_t SDTF_runESMInjectLow2_MCU(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE);
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE, 3, 0);

    return retVal;
}
#endif


#if defined (SOC_AM62X)|| defined (SOC_AM62AX) || defined (SOC_AM62PX)
int32_t SDTF_runESMInjectHigh_WKUP(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE );
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE , 1, 4);
    return retVal;
}

int32_t SDTF_runESMInjectLow1_WKUP(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE );
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE , 1, 0);
    return retVal;
}

int32_t SDTF_runESMInjectLow2_WKUP(void)
{
    int32_t retVal=0;
    esm_init_appcb(APP_ESM_INSTANCE );
    retVal = SDTF_runESMInjectInstance(APP_ESM_INSTANCE , 3, 0);
    return retVal;
}
#endif
/*********************************************************************
 * @fn      SDTF_runESMInjectHigh_MAIN
 *
 * @brief   Execute ESM Inject for MAIN
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */

int32_t SDTF_runESMInjectHigh_MAIN(void)
{
    int32_t retVal=0;
    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
    retVal = SDTF_runESMInjectInstance(SDL_ESM_INST_MAIN_ESM0, 3, 0);
    SDL_ESM_clrNError(SDL_ESM_INST_MAIN_ESM0);
    return retVal;
}

int32_t SDTF_runESMInjectLow_MAIN(void)
{
    int32_t retVal=0;
    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
    retVal = SDTF_runESMInjectInstance(SDL_ESM_INST_MAIN_ESM0, 3, 1);
    SDL_ESM_clrNError(SDL_ESM_INST_MAIN_ESM0);
    return retVal;
}

int32_t SDTF_runESMInjectSelfTest_MAIN(void)
{
    int32_t retVal=0;
    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
    retVal = SDTF_runESMInjectInstance(SDL_ESM_INST_MAIN_ESM0, 1, 8);
    SDL_ESM_clrNError(SDL_ESM_INST_MAIN_ESM0);
    return retVal;
}

int32_t ESMIntNumberTest(void)
{
    int32_t retVal=0;
    uint32_t intNum;
    intNum = SDL_ESM_getIntNumber(SDL_ESM_INST_MAIN_ESM0, SDL_ESM_INT_TYPE_MAX);
    if(intNum == 0xffffffffu)
    {
       intNum = SDL_ESM_getIntNumber(APP_ESM_INSTANCE, SDL_ESM_INT_TYPE_MAX);
    }
    else
    {
        retVal = -1;
    }
    if(intNum == 0xffffffffu)
    {
       intNum = SDL_ESM_getIntNumber(SDL_ESM_INSTANCE_MAX, SDL_ESM_INT_TYPE_MAX);
    }
    else
    {
        retVal = -1;
    }
    return retVal;
}

int32_t Negative_test_priv_file(void)
{
    int32_t retVal=0;
    uint32_t esmInstBaseAddr;
    SDL_ErrType_t result;
    result = SDL_ESM_init(APP_ESM_INSTANCE,&SDTF_esmInitConfig_Inst_appcallback,SDL_ESM_applicationCallbackFunction, NULL);
    if(result != SDL_PASS)
    {
        DebugP_log("SDL_ESM_init: failure \n");
    }
    SDL_ESM_getBaseAddr(APP_ESM_INSTANCE,&esmInstBaseAddr);
    if (SDL_ESM_enableIntr(esmInstBaseAddr, 40U) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    if (SDL_ESM_setIntrPriorityLvl(esmInstBaseAddr, 40U, ESM_INTR_PRIORITY_LEVEL_LOW) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    if (SDL_ESM_setIntrStatusRAW(esmInstBaseAddr, 40U) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    if (SDL_ESM_enableGlobalIntr(esmInstBaseAddr) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    if (SDL_ESM_setInfluenceOnErrPin(esmInstBaseAddr, 40U, true) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    if (SDL_ESM_setMode(esmInstBaseAddr, ESM_OPERATION_MODE_NORMAL) != SDL_PASS)
    {
        DebugP_log("sdlEsm_apiTest: failure on line no. %d \n", __LINE__);
    }
    retVal =SDTF_runESMInjectInstance(APP_ESM_INSTANCE, 1, 8);
    return retVal;
}

/* Other commands not covered by run_all */
#define SDTF_NUM_OTHER_TEST_COMMANDS (0u)
#define SDTF_MAX_COMMANDS (SDTF_NUM_RUNALL_TEST_COMMANDS+SDTF_NUM_OTHER_TEST_COMMANDS)

#define SDTF_MAX_COMMAND_LEN (64u)
typedef int32_t (* SDTF_testFunctionPtr_t) (void);

typedef struct SDTF_commandList_s
{
    char commandString[SDTF_MAX_COMMAND_LEN+1];
    SDTF_testFunctionPtr_t commandFunction;
}SDTF_commandList_t;
/* Full list of commands */
SDTF_commandList_t SDTF_commandList[SDTF_MAX_COMMANDS] =
{
#if defined(SOC_AM64X)
    { "esm_injectHigh_MCU",            SDTF_runESMInjectHigh_MCU },
    { "esm_injectLow1_MCU",            SDTF_runESMInjectLow1_MCU },
    { "esm_injectLow2_MCU",            SDTF_runESMInjectLow2_MCU },
	{ "esm_injectCfg_MCU",             SDTF_runESMInjectCfg_MCU},
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
    { "esm_injectHigh_WKUP",            SDTF_runESMInjectHigh_WKUP },
    { "esm_injectLow1_WKUP",            SDTF_runESMInjectLow1_WKUP },
    { "esm_injectLow2_WKUP",            SDTF_runESMInjectLow2_WKUP },
	{ "esm_injectCfg_WKUP",             SDTF_runESMInjectCfg_WKUP },
#endif
    { "esm_injectHigh_MAIN",            SDTF_runESMInjectHigh_MAIN },
    { "esm_injectLow_MAIN",             SDTF_runESMInjectLow_MAIN },
    { "esm_injectSelfTest_MAIN",        SDTF_runESMInjectSelfTest_MAIN },
    { "esm_injectCfg_MAIN",             SDTF_runESMInjectCfg_MAIN },
    { "Negative_test_priv_file",        Negative_test_priv_file },
    { "ESMIntNumberTest",               ESMIntNumberTest },
};

int32_t test_sdr_test(void)
{
    /* Declarations of variables */
    int32_t retVal = 0;
    int32_t i;

    DebugP_log("\n Running all sdr test commands supported");
    for(i = 0u; i< SDTF_NUM_RUNALL_TEST_COMMANDS; i++) {
        if (SDTF_commandList[i].commandFunction!= ((void *)(0u))) {
            retVal = (*SDTF_commandList[i].commandFunction)();
            if ( retVal != 0) {
                break;
            }
        }
    }

    if (retVal == 0)
    {
        DebugP_log("\n All tests have passed. \n");
    }
    else
    {
        DebugP_log("\n Few/all tests Failed \n");
    }

return retVal;
}