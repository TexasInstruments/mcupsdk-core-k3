/*
 *   Copyright (c) Texas Instruments Incorporated 2019-2023
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
 *  \file     ecc_func.c
 *
 *  \brief    This file contains ECC SDL Function test code for R5 core.
 *
 *  \details  ECC SDL API module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/sdl_esm.h>
#if defined(SOC_AM62X)
#include <sdl/ecc/soc/am62x/sdl_ecc_soc.h>
#include "soc/am62x/ecc_func.h"
#endif

#if defined(SOC_AM62AX)
#include <sdl/ecc/soc/am62ax/sdl_ecc_soc.h>
#include "soc/am62ax/ecc_func.h"
#endif

#if defined(SOC_AM62PX)
#include <sdl/ecc/soc/am62px/sdl_ecc_soc.h>
#include "soc/am62px/ecc_func.h"
#endif

#include "ecc_test_main.h"
#include <sdl/dpl/sdl_dpl.h>
#include <drivers/soc.h>
#include <sdl/ecc/V0/sdlr_edc_ctl.h>
#include <dpl_interface.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* delay for 1us*/
#define DELAY 1
#define DEBUG

#define MAIN_MSMC_AGGR0_MAX_MEM_SECTIONS (2u)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern volatile bool esmError;
#if defined(SOC_AM62X)
#if defined (M4F_CORE)
SDL_ESM_config ECC_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x01bfd837, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x01bfd833, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x01bfd833, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c4eu, 0x03c08000u,
                     0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c4eu, 0x03c08000u,
                       0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x7705be0eu, 0x3fc3e01cu, 0xef017c4eu, 0x03c08000u,
                       0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif

#if defined (R5F_CORE)
SDL_ESM_config ECC_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c4eu, 0x03c08000u,
                     0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                     0xffffffffu,
                },
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c4eu, 0x03c08000u,
                       0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {0x7705be0eu, 0x3fc3e0fcu, 0xef017c4eu, 0x03c08000u,
                       0x06cc0000u, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                       0xffffffffu,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif
#endif

#if defined(SOC_AM62AX)
SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					 0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MCU =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {	0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = { 0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif

#if defined(SOC_AM62PX)
SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					 0x034cf800u, 0x000f3f03u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					   0x034cf800u, 0x000f3f03u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066cfeu, 0x03c0bf00u,
					   0x034cf800u, 0x000f3f03u, 0x00000000u, 0x00000000u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MCU =
{
    .esmErrorConfig = {10u, 8u}, /* Self test error config */
    .enableBitmap = {0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
					0x00000000u, 0x000f0000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {	0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
						0x00000000u, 0x000f0000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = { 0x003fc030u, 0x0000033fu, 0x000000f0u, 0x00000000u,
						0x00000000u, 0x000f0000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
						0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
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

int32_t ECC_Memory_init (void);

static uint32_t arg;
/*********************************************************************
* @fn      ECC_Memory_init
*
* @brief   Initializes Software Diagostics Test Framework
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/
int32_t ECC_Memory_init (void)
{
    int32_t retValue=0;
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;

    if (retValue == SDL_PASS) {
		/* Initialize MCU ESM module */
#if defined(SOC_AM62X)
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_WKUP, SDL_ESM_applicationCallbackFunction, ptr);
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_MCU, SDL_ESM_applicationCallbackFunction, ptr);
#endif
		if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Memory_init: Error initializing MCU ESM: result = %d\r\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Init MCU ESM complete \r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize MAIN ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ECC_Test_esmInitConfig_MAIN,SDL_ESM_applicationCallbackFunction,ptr);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\rECC_Memory_init: Error initializing MAIN ESM: result = %d\r\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Init MAIN ESM complete \r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the MCU ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_WKUP_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Memory_init: Error initializing ECC callback for MCU ESM: result = %d\r\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: ECC Callback Init complete for MCU ESM \r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the Main ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_MAIN_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Memory_init: Error initializing ECC callback for Main ESM: result = %d\r\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: ECC Callback Init complete for Main ESM \r\n");
        }
    }

    return retValue;
}

/********************************************************************
 * @fn      ecc_aggr_test
 *
 * @brief   Execute ECC single bit error self test on ecc_aggr_test ECC aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 *******************************************************************/
int32_t ecc_aggr_test(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t j,i,mainMem,k;
    SDL_ecc_aggrRegs *pEccAggr;
    uint32_t maxTimeOutMilliSeconds = 3000u;
    uint32_t timeOutCnt = 0u;
    SDL_ECC_InjectErrorType    intsrc;
    uint32_t errSrc;
    uintptr_t oldIntState = (uintptr_t)NULL;
#ifdef DEBUG
    int32_t selectedIndex = -1;
    bool exit = (bool)false;
#endif

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
#ifdef DEBUG
    while (exit != (bool)true)
    {
        DebugP_log("\r\nSelect the memory to test...\r\n");
        scanf("%d", &selectedIndex);

        if (selectedIndex == -1)
        {
            DebugP_log("\r\nExiting the test on request \r\n");
            exit = (bool)true;
            continue;
        }
        DebugP_log("\r\n...selected %d\r\n", selectedIndex);
        if (selectedIndex >= SDL_ECC_MEMTYPE_MAX)
        {
            DebugP_log("\r\necc_aggr_test: selection [%d] is not a valid memory id\r\n", selectedIndex);
            continue;
        }

#endif

		memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
		/* Run one shot test for ecc_aggr_test 1 bit error */
		/* Note the address is relative to start of ram */
		injectErrorConfig.pErrMem = (uint32_t *)(0u);

		injectErrorConfig.flipBitMask = 0x3;
#ifdef DEBUG
		mainMem = selectedIndex;
#else

#if defined(SOC_AM62X)
		for (mainMem = SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0; mainMem < SDL_ECC_MEMTYPE_MAX; mainMem++)
#endif
#if defined(SOC_AM62AX)
		for (mainMem = SDL_PSCSS0_SAM62A_MAIN_PSC_WRAP_ECC_AGGR; mainMem < SDL_ECC_MEMTYPE_MAX; mainMem++)
#endif
#if defined(SOC_AM62PX)
		for (mainMem = SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR; mainMem < SDL_ECC_MEMTYPE_MAX; mainMem++)
#endif
#endif
		{
#ifndef DEBUG
			if (mainMem >= SDL_ECC_MEMTYPE_MAX)
			{
				DebugP_log("\r\necc_aggr_test: selection [%d] is not a valid memory id\r\n", mainMem);
				continue;
			  DebugP_log("\r\necc_aggr_test: selection [%d] is not a valid memory id\r\n", mainMem);
			  continue;
			}
			else if (ECC_Test_config[mainMem].initConfig == NULL)
			{
				DebugP_log("\r\necc_aggr_test: [%d] Skipping %s due to missing information\r\n", mainMem, ECC_Test_config[mainMem].aggrName);
				continue;
			}
#endif
			DebugP_log("\r\necc_aggrtest: [%d] single bit error self test: %s starting\r\n\n", mainMem, ECC_Test_config[mainMem].aggrName);
			/* Sub memory list  entered in the for loop for perticular mem type*/

			if (ECC_Test_config[mainMem].initConfig != NULL)
			{

				/* Initialize ECC */
				result = SDL_ECC_init(mainMem, ECC_Test_config[mainMem].initConfig);
				if (result != SDL_PASS) {
					/* print error and quit */
					DebugP_log("\r\nECC_Memory_init: [%d] Error initializing %s: result = %d\r\n", mainMem, ECC_Test_config[mainMem].aggrName, result);

					result = -1;
				} else {
					DebugP_log("\r\nECC_Memory_init: [%d] %s ECC Init complete\r\n", mainMem, ECC_Test_config[mainMem].aggrName);
				}

			}
			else
			{
				DebugP_log("\r\nECC_Memory_init: [%d] Skipping %s due to missing data\r\n", mainMem, ECC_Test_config[mainMem].aggrName);
			}
			for (i=0; i< SDL_ECC_aggrTable[mainMem].numRams; i++)
			{
				if ((SDL_ECC_aggrTable[mainMem].ramTable[i].RAMId) != SDL_ECC_RAMID_INVALID)
				{
					if ((SDL_ECC_aggrTable[mainMem].ramTable[i].ramIdType) != SDL_ECC_AGGR_ECC_TYPE_ECC_WRAPPER)
					{
						DebugP_log("\r\nSelf test started RamId %d  starting\r\n",i );

						/* This for loop provide interconnect checkers group */
						for (j=0; j< SDL_ECC_aggrTable[mainMem].ramTable[i].numCheckers; j++)
						{
							injectErrorConfig.chkGrp = j;
							injectErrorConfig.pErrMem =((uint32_t *)SDL_ECC_aggrTable[mainMem].memConfigTable[j].memStartAddr);
							if(SDL_ECC_aggrTable[mainMem].esmIntSEC != 0u)
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE;

							}
							else
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE;
							}
#if (defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)) && defined (R5F_CORE)
#if defined (SOC_AM62PX)
							if ((mainMem != SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR) && (mainMem != SDL_DSS_DSI0_K3_DSS_DSI_DSI_TOP_ECC_AGGR_SYS))
#elif defined (SOC_AM62AX) || defined (SOC_AM62X)
                            if (mainMem != SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR)
#endif
							{
#endif
								result = SDL_ECC_selfTest(mainMem,
														i,
														intsrc,
														&injectErrorConfig,
														100000u);
#if (defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)) && defined (R5F_CORE)
							}
							else
							{
                                uint32_t regVal = 0x0u;

                                if (mainMem == SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR)
                                {
                                    /*
                                    * Although the endpoint is interconnect type, for CSI-RX, this
                                    * interconnect endpoint is still inject-only, and also requires
                                    * traffic on the endpoint in order for the error to propagate.
                                    * Therefore, we have special handling for this case
                                    * Steps:
                                    *     1. Inject the error
                                    *     2. Perform read of the CSI interface
                                    *     3. Wait for the ESM error event to be triggered
                                    */
                                    /* 1. Inject the error */
                                    result = SDL_ECC_injectError(mainMem, i, intsrc, &injectErrorConfig);
                                    /* Wait for some time for error to inject */
                                    ClockP_usleep(50);
                                    /* 2. Perform read access by reading the CSI registers */
                                    regVal = *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101908));
                                    if ( j == 0)
                                    {
                                        *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101908)) = regVal;
                                    }
                                }
                                else
                                {
                                    /*
                                    * Although the endpoint is interconnect type, for DSS_DSI0, this
                                    * interconnect endpoint is still inject-only, and also requires
                                    * traffic on the endpoint in order for the error to propagate.
                                    * Therefore, we have special handling for this case
                                    * Steps:
                                    *     1. Inject the error
                                    *     2. Perform read of the DSI interface
                                    *     3. Wait for the ESM error event to be triggered
                                    */
                                    /* 1. Inject the error */
                                    result = SDL_ECC_injectError(mainMem, i, intsrc, &injectErrorConfig);
                                    /* Wait for some time for error to inject */
                                    ClockP_usleep(50);
                                    /* 2. Perform read access by reading the DSI registers */
                                    regVal = *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30500208));
                                    *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30500208)) = regVal;
                                }
								/* Below line is to work around compiler warning */
								timeOutCnt = regVal;
								/* 3. Wait for ESM event to trigger */
								timeOutCnt = 0u;
								do
								{
									timeOutCnt += 10u;
									if (timeOutCnt > maxTimeOutMilliSeconds)
									{
										result = SDL_EFAIL;
										break;
									}
								} while (esmError == false);
								/* Reset esmError */
								esmError = false;
							}
#endif

							if (result != SDL_PASS )
							{
								DebugP_log("\r\necc_aggr_test self test: mainMem %d: fixed location test failed,Interconnect type RAM id = %d, checker group = %d\r\n",
										mainMem, i, j);
								retVal = -1;
							}

						}
						if (result == SDL_PASS )
						{
							DebugP_log("\r\nSelf test started RamId %d  completed\r\n",i );
						}
					}
					else
					{
						for (k=0; k< SDL_ECC_aggrTable[mainMem].numMemEntries; k++)
						{
							if ((SDL_ECC_aggrTable[mainMem].memConfigTable[k].memSubType) == (SDL_ECC_aggrTable[mainMem].ramTable[i].RAMId))
							{
							  injectErrorConfig.pErrMem =((uint32_t *)SDL_ECC_aggrTable[mainMem].memConfigTable[k].memStartAddr);
								break;
							}

						}
						if (SDL_ECC_aggrTable[mainMem].memConfigTable[k].readable == ((bool)true))
						{
							DebugP_log("\r\nSelf test started accessable RamId %d  starting \r\n",i );
							if(SDL_ECC_aggrTable[mainMem].esmIntSEC != 0u)
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE;
							}
							else
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE;
							}
							if (SDL_ECC_aggrTable[mainMem].ramTable[i].aggregatorTypeInjectOnly == 1U)
							{
								DebugP_log("\r\nInject Error Started for RamId %d inject only type\r\n",i );
								result = SDL_ECC_injectError(mainMem,i,intsrc,&injectErrorConfig);
								if ((result == SDL_PASS) && (mainMem < SDL_ECC_MEMTYPE_MAX))
								{
										pEccAggr = SDL_ECC_aggrTransBaseAddressTable[mainMem];
										SDL_ecc_aggrSetEccRamIntrPending(pEccAggr, i, errSrc);
									do
									{
										timeOutCnt += 10u;
											if (timeOutCnt > maxTimeOutMilliSeconds)
											{
												result = SDL_EFAIL;
												break;
											}
									} while (esmError == false);
									timeOutCnt = 0u;
									esmError = false;
									DebugP_log("\r\n...skipped because this is Inject Only type\r\n");
									result = SDL_PASS;
								}
								DebugP_log("\r\nInject Error completed for RamId %d inject only type\r\n",i );
							}
							else
							{
								result = SDL_ECC_selfTest(mainMem,
														i,
														intsrc,
														&injectErrorConfig,
														100000u);
								if (result != SDL_PASS )
								{
									DebugP_log("\r\necc_aggr_test self test: mainMem %d: accessable mem type test failed, Wrapper type RAM id = %d\r\n",
												mainMem, i);
									retVal = -1;
								}
								else
								{
									DebugP_log("\r\nSelf Test completed for accessable RamId %d\r\n",i);
								}
							}
						}
						else
						{
							DebugP_log("\r\nInject test started not accessable RamId %d starting\r\n",i );

							if(SDL_ECC_aggrTable[mainMem].esmIntSEC != 0u)
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE;
								errSrc = SDL_ECC_AGGR_INTR_SRC_SINGLE_BIT;
							}
							else
							{
								intsrc = SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE;
								errSrc = SDL_ECC_AGGR_INTR_SRC_DOUBLE_BIT;
							}
							result = SDL_ECC_injectError(mainMem,i,intsrc,&injectErrorConfig);
							if ((result == SDL_PASS) && (mainMem < SDL_ECC_MEMTYPE_MAX) )
							{
								if (SDL_ECC_aggrTable[mainMem].ramTable[i].aggregatorTypeInjectOnly != 1)
								{
									pEccAggr = SDL_ECC_aggrTransBaseAddressTable[mainMem];
									SDL_TEST_globalDisableInterrupts(&oldIntState);
									SDL_ecc_aggrSetEccRamIntrPending(pEccAggr, i, errSrc);
									SDL_TEST_globalRestoreInterrupts(oldIntState);
									do
									{
										timeOutCnt += 10u;
										if (timeOutCnt > maxTimeOutMilliSeconds)
										{
											result = SDL_EFAIL;
											break;
										}
									} while (esmError == false);

									timeOutCnt = 0u;
									esmError = false;
									if (result == SDL_PASS)
									{
										DebugP_log("\r\nInjected ECC error and got ESM Interrupt\r\n");
									}
									else
									{
										DebugP_log("\r\nInjected ECC error and ESM Interrupt not triggered and Failed\r\n");
									}
								}
								else
								{
									do
									{
										timeOutCnt += 10u;
										if (timeOutCnt > maxTimeOutMilliSeconds)
										{
											result = SDL_EFAIL;
											break;
										}
									} while (esmError == false);
									timeOutCnt = 0u;
									esmError = false;
									DebugP_log("\r\n...skipped because this is Inject Only type\r\n");
									result = SDL_PASS;
								}
							}
							else {
								DebugP_log("\r\nInject error failed!\r\n");
							}
							if (result != SDL_PASS ) {
							DebugP_log("\r\necc_aggr_test self test: mainMem %d: fixed location test failed, Wrapper type RAM id = %d\r\n",
										mainMem, i);
							retVal = -1;
							}
						}


					}
				}
			}
		}
	}
    return retVal;
}

static int32_t ECC_sdlFuncTest(void)
{
    int32_t result;
    int32_t retVal = 0;

    DebugP_log("\r\nECC SDL API tests: starting\r\n");
    if (retVal == SDL_PASS) {
       result = ecc_aggr_test();
       if (result != SDL_PASS) {
           retVal = -1;
            DebugP_log("\r\necc_aggr test has failed...\r\n");
       }
    }
    return retVal;
}

/* ECC Function module test */
int32_t ECC_funcTest(void)
{
    int32_t testResult;
    testResult = ECC_Memory_init();
    if (testResult != 0)
    {
        DebugP_log("\r\nECC func tests: unsuccessful\r\n");
        return SDL_EFAIL;
    }

    testResult = ECC_sdlFuncTest();


    return (testResult);
}

/* Nothing past this point */
