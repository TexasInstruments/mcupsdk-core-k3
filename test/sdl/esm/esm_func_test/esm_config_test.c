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
 *  \file     esm_config_test.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM tests
 **/

#include <sdl/sdl_esm.h>
#include <stdint.h>
#include "esm_test_main.h"
#include <kernel/dpl/DebugP.h>

#if defined (SOC_AM64X)
#define APP_ESM_INSTANCE  SDL_ESM_INST_MCU_ESM0
#elif defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
#define APP_ESM_INSTANCE  SDL_ESM_INST_WKUP_ESM0
#endif

#define SDTF_NUM_RUNALL_TEST_COMMANDS 4U
#define SDL_ESM_PWM_TEST_MAX_NUM     10U

SDL_ESM_config SDTF_esmInitConfig_Inst_config =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x00000000u, 0xff0fffffu, 0x7fffffffu, 0x00000007u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};


#if defined (SOC_AM64X) || defined (SOC_AM62X)
#if defined (M4F_CORE)
SDL_ESM_config SDTF_esmInitConfig_MAIN =
{
    .esmErrorConfig = {0u, 8u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
#endif

#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
#if defined (R5F_CORE)
SDL_ESM_config SDTF_esmInitConfig_MAIN =
{
    .esmErrorConfig = {0u, 8u}, /* Self test error config */
    .enableBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0xffffffffu, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u,0xffffffffu, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0xffffffffu, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
#endif
extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                         SDL_ESM_IntType esmIntType,
                                         uint32_t grpChannel,
                                         uint32_t index,
                                         uint32_t intSrc,
                                         void *arg);

static uint32_t arg;
void  esm_init(SDL_ESM_Inst esmType)
{
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;
    /* Initialize MAIN ESM module */
    if(esmType == APP_ESM_INSTANCE)
    {
        result = SDL_ESM_init(esmType, &SDTF_esmInitConfig_Inst_config,SDL_ESM_applicationCallbackFunction,ptr);
    }
    else
    {
        result = SDL_ESM_init(esmType, &SDTF_esmInitConfig_MAIN,SDL_ESM_applicationCallbackFunction,ptr);
    }

    if (result != SDL_PASS) {
        /* print error and quit */
        if(esmType == APP_ESM_INSTANCE){
#if defined(SOC_AM64X)
            DebugP_log("ESM_ECC_Example_init: Error initializing MCU ESM: result = %d\n", result);
#elif defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
            DebugP_log("ESM_ECC_Example_init: Error initializing WKUP ESM: result = %d\n", result);
#endif
        }else{
            DebugP_log("ESM_ECC_Example_init: Error initializing MAIN ESM: result = %d\n", result);
        }

    } else {
        if(esmType == APP_ESM_INSTANCE){
#if defined(SOC_AM64X)
            DebugP_log("\nESM_ECC_Example_init: Init MCU ESM complete \n");
#elif defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
			DebugP_log("\nESM_ECC_Example_init: Init WKUP ESM complete \n");
#endif
        }else{
            DebugP_log("\nESM_ECC_Example_init: Init MAIN ESM complete \n");
        }
    }
}

uint8_t config_param = 1;
int32_t retVal=0;

/*********************************************************************
 * @fn      SDTF_runESMInject_MCU
 *
 * @brief   Execute ESM Inject for MCU
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
#if defined(SOC_AM64X)
int32_t sdl_config_MCU(void)
{

    esm_init(APP_ESM_INSTANCE);
    SDL_ESM_setNError(APP_ESM_INSTANCE);
    return retVal;
}

int32_t sdl_configGrp_MCU(void)
{

    esm_init(APP_ESM_INSTANCE);
    SDL_ESM_setNError(APP_ESM_INSTANCE);
    return retVal;
}
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
int32_t sdl_config_WKUP(void)
{
    esm_init(APP_ESM_INSTANCE );
    SDL_ESM_setNError(APP_ESM_INSTANCE );
    return retVal;
}
int32_t sdl_configGrp_WKUP(void)
{
    esm_init(APP_ESM_INSTANCE );
    SDL_ESM_setNError(APP_ESM_INSTANCE );
    return retVal;
}
#endif
/*********************************************************************
 * @fn      SDTF_runESMInject_MAIN
 *
 * @brief   Execute ESM Inject for MAIN
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t sdl_config_MAIN(void)
{

    esm_init(SDL_ESM_INST_MAIN_ESM0);
    SDL_ESM_setNError(SDL_ESM_INST_MAIN_ESM0);
    SDL_ESM_clrNError(SDL_ESM_INST_MAIN_ESM0);

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
SDTF_commandList_t SDTF_commandList_config[SDTF_MAX_COMMANDS] =
{
#if defined(SOC_AM64X)
    { "esm_config_MCU",              sdl_config_MCU },
    { "esm_configGrp_MCU",           sdl_configGrp_MCU },
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined (SOC_AM62PX)
    { "esm_config_WKUP",              sdl_config_WKUP},
    { "esm_configGrp_WKUP",           sdl_configGrp_WKUP},
#endif
    { "esm_config_MAIN",             sdl_config_MAIN },
};

int32_t sdl_config_test(void)
{
    /* Declarations of variables */
    int32_t retVal = 0;
    int32_t i;

    DebugP_log("\n Running all sdr test commands supported");
    for(i = 0u; i< SDTF_NUM_RUNALL_TEST_COMMANDS; i++) {
        if (SDTF_commandList_config[i].commandFunction!= ((void *)(0u))) {
            retVal = (*SDTF_commandList_config[i].commandFunction)();
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

int32_t sdl_config_pwm_test(void)
{
    /* Declarations of variables */
    int32_t retVal = 0;
    uint32_t errorStatus;
    uint32_t baseAddr;
    esmErrOutMode_t  mode;
    bool prevStatusValue, currStatusValue;
    uint32_t i = 0;

    DebugP_log("\n sdl_config_pwm_test is started. \n");
    SDL_ESM_getBaseAddr(SDL_ESM_INST_WKUP_ESM0, &baseAddr);
    esm_init(SDL_ESM_INST_WKUP_ESM0);

    retVal = SDL_ESM_setPinOutMode(SDL_ESM_INST_WKUP_ESM0, SDL_ESM_PWM_PINOUT);
    if (retVal == SDL_PASS)
    {
        retVal = SDL_ESM_getErrorOutMode(baseAddr, &mode);

        if (retVal == SDL_PASS)
        {
            (mode == SDL_ESM_PWM_PINOUT) ? printf("\n Error out mode is in PWM mode. \n")
                                         : printf("\n Error out mode is in LVL mode. \n");
        }
    }

    do
    {
        retVal = SDL_ESM_getErrPinStatus(baseAddr, &errorStatus);
        currStatusValue = (bool) errorStatus;
        if(i == 0)
        {
            prevStatusValue = !(currStatusValue);
        }

        if (prevStatusValue != currStatusValue)
        {
            DebugP_log("\n Error status Value in PWM mode is = %d. \n", currStatusValue);
            i++;
        }

        prevStatusValue = currStatusValue;
        ClockP_usleep (10);

    } while(i <= SDL_ESM_PWM_TEST_MAX_NUM);

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