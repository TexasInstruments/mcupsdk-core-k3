#include <sdl/sdl_esm.h>
#include <stdint.h>
#include "esm_test_main.h"
#include <kernel/dpl/DebugP.h>

#if defined (SOC_AM64X)
#define APP_ESM_INSTANCE  SDL_ESM_INST_MCU_ESM0
#elif defined (SOC_AM62X) || defined (SOC_AM62AX)
#define APP_ESM_INSTANCE  SDL_ESM_INST_WKUP_ESM0
#endif

#define SDTF_NUM_RUNALL_TEST_COMMANDS 4

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

#if defined (SOC_AM62X) || defined (SOC_AM62AX)
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
#elif defined(SOC_AM62X) || defined(SOC_AM62AX)
            DebugP_log("ESM_ECC_Example_init: Error initializing WKUP ESM: result = %d\n", result);
#endif
        }else{
            DebugP_log("ESM_ECC_Example_init: Error initializing MAIN ESM: result = %d\n", result);
        }

    } else {
        if(esmType == APP_ESM_INSTANCE){
#if defined(SOC_AM64X)
            DebugP_log("\nESM_ECC_Example_init: Init MCU ESM complete \n");
#elif defined(SOC_AM62X) || defined(SOC_AM62AX)
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
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
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
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
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