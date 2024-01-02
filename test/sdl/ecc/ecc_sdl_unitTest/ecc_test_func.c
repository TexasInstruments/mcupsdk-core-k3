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
 *  \file     ecc_test_func.c
 *
 *  \brief    This file contains ECC SDL Function test code for R5 core.
 *
 *  \details  ECC SDL API module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include "ecc_test_main.h"
#include <sdl/sdl_esm.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/dpl/sdl_dpl.h>
#include <sdl/ecc/sdl_ecc_utils.h>
#include <sdl/sdl_exception.h>
#include <sdl/r5/v0/sdl_interrupt.h>
#if defined(SOC_AM62X)
#include <sdl/include/am62x/sdlr_soc_baseaddress.h>
#include <sdl/ecc/soc/am62x/sdl_ecc_soc.h>


/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (M4F_CORE)
SDL_ESM_config ECC_Test_esmInitConfig_WKUP =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    .enableBitmap = {0x01bfd837, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                },
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x01bfd837, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x01bfd837, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
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
    .errorpinBitmap = {0x01bfd830, 0xffffffffu, 0xffffffffu, 0xffffffffu,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
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

#define SDL_PMU_CTR_MAX_VALUE (0xffffffffu)

#define SDL_ECC_ATCM_SINGLE_BIT_ERROR_EVENT (0x67u)
#endif

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
volatile uint32_t testLocationValue;

#if defined (M4F_CORE)
SDL_ECC_MemType geccMemType = SDL_MCU_M4FSS0_BLAZAR_ECC;
#endif

#if defined (R5F_CORE)
SDL_ECC_MemType geccMemType = SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Defines */
#define MAX_MEM_SECTIONS   (1u)

#define PSRAMECC_16K0_PSRAM16KX32E_ADD   (0x70000000u)


/* Function prototypes */
void ECC_Test_copyResetVector(void);
int32_t ECC_Test_EsmInitHandlerInit(SDL_ESM_Inst esmInstType);
int32_t ECC_Test_init (void);

#if defined (M4F_CORE)
static SDL_ECC_MemSubType ECC_Test_CoresubMemTypeList[MAX_MEM_SECTIONS] =
{
  SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
};
#endif

#if defined (R5F_CORE)
static SDL_ECC_MemSubType ECC_Test_CoresubMemTypeList[MAX_MEM_SECTIONS] =
{
  SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
};

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
    DebugP_log("\r\nUndefined Instruction exception\r\r\n");
}

void ECC_Test_swIntrExptnCallback(void)
{
    DebugP_log("\r\nSoftware interrupt exception\r\r\n");
}

void ECC_Test_prefetchAbortExptnCallback(void)
{
    DebugP_log("\r\nPrefetch Abort exception\r\r\n");
}
void ECC_Test_dataAbortExptnCallback(void)
{
    DebugP_log("\r\nData Abort exception\r\r\n");
}
void ECC_Test_irqExptnCallback(void)
{
    DebugP_log("\r\nIrq exception\r\r\n");
}

void ECC_Test_fiqExptnCallback(void)
{
    DebugP_log("\r\nFiq exception\r\r\n");
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
}
#endif

static SDL_ECC_InitConfig_t ECC_Test_CoreECCInitConfig =
{
    .numRams = MAX_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_CoresubMemTypeList[0]),
    /**< Sub type list  */
};

#define AGGR1_MEM_SECTIONS (2u)
static SDL_ECC_MemSubType ECC_Test_AGGR1_A0subMemTypeList[AGGR1_MEM_SECTIONS] =
{
    SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID,
    SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_MAINMSMCA0ECCInitConfig =
{
    .numRams = AGGR1_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_AGGR1_A0subMemTypeList[0]),
    /**< Sub type list  */
};

#endif

#if defined(SOC_AM62AX)
#include <sdl/include/am62ax/sdlr_soc_baseaddress.h>
#include <sdl/ecc/soc/am62ax/sdl_ecc_soc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define SDL_PMU_CTR_MAX_VALUE 				(0xffffffffu)

#define SDL_ECC_ATCM_SINGLE_BIT_ERROR_EVENT (0x67u)

/* Defines */
#define MAX_R5F_MEM_SECTIONS   			    (5u)
#define MAX_MCAN0_MEM_SECTIONS              (1u)
#define MAX_VTM0_MEM_SECTIONS               (1u)

#define SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR		(0x00000510u)
#define SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID	(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK0_RAM_ID)

#define SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR	(0x41010000u)
#define SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID	(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK0_RAM_ID)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SDL_ECC_MemType geccMemType = SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR;

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					 0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MCU =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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
    .priorityBitmap = {	0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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
    .errorpinBitmap = { 0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
volatile uint32_t testLocationValue;


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t ECC_Test_init (void);
int32_t ECC_funcTest(void);

static SDL_ECC_MemSubType ECC_Test_CoresubMemTypeList[MAX_R5F_MEM_SECTIONS] =
{
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK1_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK1_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreECCInitConfig =
{
    .numRams = MAX_R5F_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_CoresubMemTypeList[0]),
    /**< Sub type list  */
};

static SDL_ECC_MemSubType ECC_Test_MCAN0MemTypeList[MAX_MCAN0_MEM_SECTIONS] =
{
    SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR_CTRL_EDC_VBUSS_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreMCAN0ECCInitConfig =
{
    .numRams = MAX_MCAN0_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_MCAN0MemTypeList[0]),
    /**< Sub type list  */
};

static SDL_ECC_MemSubType ECC_Test_VTM0MemTypeList[MAX_VTM0_MEM_SECTIONS] =
{
     SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR_K3VTM_N16FFC_CFG_CBASS_CFG_SCR_SCR_EDC_CTRL_0_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreVTM0ECCInitConfig =
{
    .numRams = MAX_VTM0_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_VTM0MemTypeList[0]),
    /**< Sub type list  */
};
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
    DebugP_log("\r\nUndefined Instruction exception\r\r\n");
}

void ECC_Test_swIntrExptnCallback(void)
{
    DebugP_log("\r\nSoftware interrupt exception\r\r\n");
}

void ECC_Test_prefetchAbortExptnCallback(void)
{
    DebugP_log("\r\nPrefetch Abort exception\r\r\n");
}
void ECC_Test_dataAbortExptnCallback(void)
{
    DebugP_log("\r\nData Abort exception\r\r\n");
}
void ECC_Test_irqExptnCallback(void)
{
    DebugP_log("\r\nIrq exception\r\r\n");
}

void ECC_Test_fiqExptnCallback(void)
{
    DebugP_log("\r\nFiq exception\r\r\n");
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
}
#endif

#if defined(SOC_AM62PX)
#include <sdl/include/am62px/sdlr_soc_baseaddress.h>
#include <sdl/ecc/soc/am62px/sdl_ecc_soc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define SDL_PMU_CTR_MAX_VALUE 				(0xffffffffu)

#define SDL_ECC_ATCM_SINGLE_BIT_ERROR_EVENT (0x67u)

/* Defines */
#define MAX_R5F_MEM_SECTIONS   			    (5u)
#define MAX_MCAN0_MEM_SECTIONS              (1u)
#define MAX_VTM0_MEM_SECTIONS               (1u)

#define SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR		(0x00000510u)
#define SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID	(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK0_RAM_ID)

#define SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR	(0x41010000u)
#define SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID	(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK0_RAM_ID)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SDL_ECC_MemType geccMemType = SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR;

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    .enableBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					 0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except timer and self test  events, and Main ESM output */
    /* Temporarily disabling vim compare error as well*/
    .priorityBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                        },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
    .errorpinBitmap = {0x77f1bf6eu, 0xffc3e0fcu, 0xef066c0eu, 0x03c0bf00u,
					   0x034c1800u, 0x00003f03u, 0x00000000u, 0x00000000u,
                      },
    /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MCU =
{
    .esmErrorConfig = {10u, 8u}, /* Self test error config */
    .enableBitmap = {0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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
    .priorityBitmap = {	0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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
    .errorpinBitmap = { 0x003fc030u, 0x00000333u, 0x00000000u, 0x00000000u,
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

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
volatile uint32_t testLocationValue;


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t ECC_Test_init (void);
int32_t ECC_funcTest(void);

static SDL_ECC_MemSubType ECC_Test_CoresubMemTypeList[MAX_R5F_MEM_SECTIONS] =
{
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK1_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK0_RAM_ID,
  SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK1_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreECCInitConfig =
{
    .numRams = MAX_R5F_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_CoresubMemTypeList[0]),
    /**< Sub type list  */
};

static SDL_ECC_MemSubType ECC_Test_MCAN0MemTypeList[MAX_MCAN0_MEM_SECTIONS] =
{
    SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR_CTRL_EDC_VBUSS_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreMCAN0ECCInitConfig =
{
    .numRams = MAX_MCAN0_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_MCAN0MemTypeList[0]),
    /**< Sub type list  */
};

static SDL_ECC_MemSubType ECC_Test_VTM0MemTypeList[MAX_VTM0_MEM_SECTIONS] =
{
     SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR_K3VTM_N16FFC_CFG_CBASS_CFG_SCR_SCR_EDC_CTRL_0_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_CoreVTM0ECCInitConfig =
{
    .numRams = MAX_VTM0_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(ECC_Test_VTM0MemTypeList[0]),
    /**< Sub type list  */
};
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
    DebugP_log("\r\nUndefined Instruction exception\r\r\n");
}

void ECC_Test_swIntrExptnCallback(void)
{
    DebugP_log("\r\nSoftware interrupt exception\r\r\n");
}

void ECC_Test_prefetchAbortExptnCallback(void)
{
    DebugP_log("\r\nPrefetch Abort exception\r\r\n");
}
void ECC_Test_dataAbortExptnCallback(void)
{
    DebugP_log("\r\nData Abort exception\r\r\n");
}
void ECC_Test_irqExptnCallback(void)
{
    DebugP_log("\r\nIrq exception\r\r\n");
}

void ECC_Test_fiqExptnCallback(void)
{
    DebugP_log("\r\nFiq exception\r\r\n");
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
}
#endif

static uint32_t arg;
/*********************************************************************
* @fn      ECC_Test_init
*
* @brief   Initializes Software Diagostics Test Framework
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/
int32_t ECC_Test_init (void)
{
    int32_t retValue=0;
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;
    SDL_ECC_staticRegs staticRegs;

    DebugP_log("\r\nECC_Test_init: UART ready to print, proceeding with ECC_Test init \n\r\n");

    DebugP_log("\r\nECC_Test_init: Profile init complete \r\n");
#if defined(SOC_AM62X)
#if defined (R5F_CORE)
    /* Initialise exception handler */
    ECC_Test_exceptionInit();

    if (retValue == SDL_PASS) {
        /* Initialize ECC Memory */
         result = SDL_ECC_initMemory(SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR, SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID);
         if (result != SDL_PASS) {
             /* print error and quit */
             DebugP_log("\rECC_Test_init: Error initializing Memory of R5FSS0 CORE0 ECC: result = %d\n", result);

             retValue = -1;
         } else {
             DebugP_log("\r\nECC_Test_init: Initialize of R5FSS0 CORE0 ECC Memory is complete \r\n");
         }
    }
#endif
    if (retValue == SDL_PASS) {
        /* Initialize MCU ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_WKUP, SDL_ESM_applicationCallbackFunction, ptr);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\rECC_Test_init: Error initializing MCU ESM: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Init MCU ESM complete \n\r\n");
        }
    }
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
    /* Initialise exception handler */
    ECC_Test_exceptionInit();

    if (retValue == SDL_PASS) {
        /* Initialize ECC Memory */
        result = SDL_ECC_initMemory(geccMemType, SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\rECC_Test_init: Error initializing Memory of MCU R5FSS0 ECC: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Initialize of MCU R5FSS0 ECC Memory is complete \r\n");
        }
    }

	if (retValue == SDL_PASS) {
        /* Initialize MCU ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_MCU, SDL_ESM_applicationCallbackFunction, ptr);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\rECC_Test_init: Error initializing MCU ESM: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Init MCU ESM complete \n\r\n");
        }
    }
#endif

    if (retValue == SDL_PASS) {
        /* Initialize MAIN ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ECC_Test_esmInitConfig_MAIN,SDL_ESM_applicationCallbackFunction,ptr);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error initializing MAIN ESM: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: Init MAIN ESM complete \n\r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(geccMemType, &ECC_Test_CoreECCInitConfig);
        if (result != SDL_PASS) {
#if defined(SOC_AM62X)
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error initializing M4F core ECC: result = %d\r\n", result);
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error initializing R5F core ECC: result = %d\r\n", result);
#endif
            retValue = -1;
        } else {
#if defined(SOC_AM62X)
            DebugP_log("\r\nECC_Test_init: M4F Core ECC Init complete \r\n");
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
            DebugP_log("\r\nECC_Test_init: R5F Core ECC Init complete \r\n");
#endif
        }
    }

    if (retValue == SDL_PASS) {
        /* Read back the static registers */
        result = SDL_ECC_getStaticRegisters(geccMemType, &staticRegs);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error reading the static registers: result = %d\n\r\n");
            retValue = -1;
        } else {
#if defined(SOC_AM62X)
            DebugP_log("\r\nECC_Test_init: M4F Memtype Register Readback successful \n\r\n");
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
            DebugP_log("\r\nECC_Test_init: R5F Memtype Register Readback successful \n\r\n");
#endif
        }
    }

#if defined(SOC_AM62AX) || defined (SOC_AM62PX)

    /* Initialize an ECC aggregator type that requires mapping.
     * This example only shows MCAN0 instance.*/
    if (retValue == SDL_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR, &ECC_Test_CoreMCAN0ECCInitConfig);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Test_init: Error initializing MCAN0 ECC: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: MCAN0 ECC Init complete \n\r\n");
        }
    }

    /* Test the path for MCAN0 mapping */
    if (retValue == SDL_PASS) {
        /* Read back the static registers */
        result = SDL_ECC_getStaticRegisters(SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR, &staticRegs);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error reading the static registers: result = %d\n\r\n");

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: MCAN0 Memtype Register Read back successful \n\r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR, &ECC_Test_CoreVTM0ECCInitConfig);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Test_init: Error initializing VTM0 ECC: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: VTM0 ECC Init complete \n\r\n");
        }
    }

    /* Test the path for VTM0 mapping */
    if (retValue == SDL_PASS) {
        /* Read back the static registers */
        result = SDL_ECC_getStaticRegisters(SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR, &staticRegs);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error reading the static registers: result = %d\n\r\n");

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: VTM0 Memtype Register Read back successful \n\r\n");
        }
    }
#endif

#if defined(SOC_AM62X)
    /* Initialize an ECC aggregator type that requires mapping.
     * This example only shows MSMC_AGGR0 instance.*/
    if (retValue == SDL_PASS) {
        /* Initialize ECC */
        result = SDL_ECC_init(SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR, &ECC_Test_MAINMSMCA0ECCInitConfig);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Test_init: Error initializing MCAN1 ECC: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: MCAN1 ECC Init complete \n\r\n");
        }
    }

    /* Test the path for MSMC mapping */
    if (retValue == SDL_PASS) {
        /* Read back the static registers */
        result = SDL_ECC_getStaticRegisters(SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR, &staticRegs);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\nECC_Test_init: Error reading the static registers: result = %d\n\r\n");

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: MCAN1 Memtype Register Readback successful \n\r\n");
        }
    }
#endif
    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the MCU ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_WKUP_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Test_init: Error initializing ECC callback for MCU ESM: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: ECC Callback Init complete for MCU ESM \n\r\n");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the Main ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_MAIN_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("\r\nECC_Test_init: Error initializing ECC callback for Main ESM: result = %d\n", result);

            retValue = -1;
        } else {
            DebugP_log("\r\nECC_Test_init: ECC Callback Init complete for Main ESM \n\r\n");
        }
    }

#if defined(SOC_AM62X)
    if (retValue == SDL_PASS) {
        result = SDL_ECC_initMemory(geccMemType, 1U);
        if (result != SDL_PASS) {
             /* print error and quit */
              DebugP_log("\r\nECC_Test_init: Error initializing ECC memory: retValue = %d\n", retValue);
             retValue = -1;
         } else {
             DebugP_log("\r\nECC_Test_init: ECC Memory init complete \n\r\n");
         }
    }
#endif

    return retValue;
}

#if defined(SOC_AM62X)
/*********************************************************************
 * @fn      ECC_Test_runECC1BitInjectTest
 *
 * @brief   Execute ECC 1 bit inject test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Single bit error inject: test starting\r\n");

    /* Run one shot test for M4FSS0 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                 &injectErrorConfig);
    #endif
    #if defined (R5F_CORE)
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                 &injectErrorConfig);
    #endif


    if (result != SDL_PASS ) {
        DebugP_log("\r\n Single bit error inject at pErrMem 0x%p test failed",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\n Single bit error inject at pErrMem 0x%p: test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

/*********************************************************************
 * @fn      ECC_Test_runECC2BitInjectTest
 *
 * @brief   Execute ECC 2 bit Inject test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;


    DebugP_log("\r\n Double bit error inject: starting\r\n");

    /* Run one shot test for M4FSS0 2 bit error */


    injectErrorConfig.flipBitMask = 0x101;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x200u);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                                 &injectErrorConfig);
    #endif

    #if defined (R5F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                                 &injectErrorConfig);
    #endif
    /* Access the memory where injection is expected */
    testLocationValue = injectErrorConfig.pErrMem[0];

    if (result != SDL_PASS ) {
        DebugP_log("\r\n Double bit error inject: at pErrMem 0x%p: fixed location once test failed",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\n Double bit error inject: pErrMem 0x%p fixed location once test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}



/*********************************************************************
 * @fn      ECC_Test_runECC1BitSelfTest
 *
 * @brief   Execute ECC 1 bit Self test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitSelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Single bit error self test: starting\r\n");


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
}

int32_t ECC_Test_runECC1BitNeg1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Single bit error negative-1 self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x100);

    /* To get EFAIL  passing invalid chkgrp*/
    injectErrorConfig.chkGrp = 50U;
    result = SDL_ECC_selfTest(geccMemType,
                              28U,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);


    if (result != SDL_EFAIL ) {
         DebugP_log("\r\n Single bit error negative-1 self test at pErrMem 0x%p test failed",
                     injectErrorConfig.pErrMem);
        retVal = -1;
    } else {

        DebugP_log("\r\n Single bit error negative-1 self test at pErrMem 0x%p: test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

/*********************************************************************
 * @fn      ECC_Test_runECC2BitSelfTest
 *
 * @brief   Execute ECC 2 bit Self Test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitSelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Double bit error self test: starting\r\n");

    /* Run one shot test for M4FSS0 2 bit error */

    injectErrorConfig.flipBitMask = 0x101;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x400u);
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);
    #endif

    #if defined (R5F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);
    #endif

    if (result != SDL_PASS ) {
        DebugP_log("\r\n Double bit error self test: at pErrMem 0x%p: fixed location once test failed",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\n Double bit error self test: pErrMem 0x%p fixed location once test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

/*********************************************************************
 * @fn      ECC_Test_runECC1BitMCAN1SelfTest
 *
 * @brief   Execute ECC Single bit error self test on MSMC_BUSECC_RAM aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitMCAN1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Single bit error self test: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    /* Run one shot test for SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR 1 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(PSRAMECC_16K0_PSRAM16KX32E_ADD);

    injectErrorConfig.flipBitMask = 0x1;
    injectErrorConfig.chkGrp = 0x4;
#if defined(SOC_AM62X)
    subType = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID;
#endif
    result = SDL_ECC_selfTest(SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR,
                              subType,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR  Single bit error self test: Subtype %d: test failed",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Single bit error self test: Subtype 0x%p test complete",
                    subType);
    }

    return retVal;
}

/*********************************************************************
 * @fn      ECC_Test_runECC2BitMCAN1SelfTest
 *
 * @brief   Execute ECC Double bit error self test on MSMC_BUSECC_RAM ECC aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitMCAN1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType, mainMem;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Double bit error self test: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
	/* Run one shot test for MSMC_BUSECC_RAM 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(PSRAMECC_16K0_PSRAM16KX32E_ADD);


#if defined(SOC_AM62X)
    injectErrorConfig.flipBitMask = 0x3;
    injectErrorConfig.chkGrp = 0x1;
	mainMem = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR;
    subType = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID;
#endif

    result = SDL_ECC_selfTest(mainMem,
                              subType,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
							  10000);

	#if defined(SOC_AM62X)
    if (result != SDL_PASS ) {
        DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR  Double bit error self test: Subtype %d: fixed location once test failed",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Double bit error self test: Subtype 0x%p fixed location once test complete",
                    subType);
    }
	#endif

    return retVal;
}

#if defined(SOC_AM62X)
static bool ECC_Test_ECC_DEDTriggerFlag = false;
/*********************************************************************
 *
 * @brief   indicate DED trigger
 *
 *
 * @return  0 : Success; < 0 for failures
 */
void ECC_Test_ECC_indicateDEDTrigger(void)
{
    ECC_Test_ECC_DEDTriggerFlag = true;
}

int32_t ECC_Test_runECC_ErrMemInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Error inject: EFAIL test starting\r\n");

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
}

int32_t ECC_Test_runECC1BitNrowInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Single bit N row error inject: test starting\r\n");


    /* Run one shot test for M4FSS0 1 bit N row error */
    injectErrorConfig.flipBitMask = 0x10;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_N_ROW_ONCE,
                                 &injectErrorConfig);
    #endif
    #if defined (R5F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_N_ROW_ONCE,
                                 &injectErrorConfig);
    #endif

    if (result != SDL_PASS ) {
        DebugP_log("\r\n Single bit N row error inject at pErrMem 0x%p test failed",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\n Single bit N row error inject at pErrMem 0x%p: test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

int32_t ECC_Test_runECC1BitRepeatInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Single bit Repeat error inject: test starting\r\n");


    /* Run one shot test for M4FSS0 1 bit Repeat error */
    injectErrorConfig.flipBitMask = 0x10;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_REPEAT,
                                 &injectErrorConfig);
    #endif

    #if defined (R5F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_REPEAT,
                                 &injectErrorConfig);
    #endif

    if (result != SDL_PASS ) {
        DebugP_log("\r\n Single bit Repeat error inject at pErrMem 0x%p test failed",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\n Single bit Repeat error inject at pErrMem 0x%p: test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

int32_t ECC_Test_runECC2BitNrowInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n Double bit N row error inject: test starting\r\n");

    /* Run one shot test for M4FSS0 2 bit N row error */
    injectErrorConfig.flipBitMask = 0x101;
    #if defined (M4F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_M4FSS0_BLAZAR_ECC_BLAZAR_IIRAM_ECC_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_N_ROW_ONCE,
                                 &injectErrorConfig);
    #endif

    #if defined (R5F_CORE)
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00000510u);
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR_PULSAR_UL_ATCM0_BANK0_RAM_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_N_ROW_ONCE,
                                 &injectErrorConfig);
    #endif

    if (result != SDL_PASS ) {
        DebugP_log("\r\n Double bit N row error inject at pErrMem 0x%p test failed",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\n Double bit N row error inject at pErrMem 0x%p: test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}

#endif

#if defined (SOC_AM62X)
int32_t ECC_Test_runECC2BitRepeatInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
   uint32_t subType, mainMem;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Double bit repeat error inject: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
	/* Run one shot test for MSMC_BUSECC_RAM 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(PSRAMECC_16K0_PSRAM16KX32E_ADD);

	injectErrorConfig.flipBitMask = 0x5;
    subType = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID;
	mainMem = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR;

    result = SDL_ECC_injectError(mainMem,
                                subType,
                                SDL_INJECT_ECC_ERROR_FORCING_2BIT_REPEAT,
                                 &injectErrorConfig);

    if (result != SDL_PASS ) {
        DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR  Double bit repeat error inject: Subtype %d: fixed location once test failed",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\n MSMC_BUSECC_RAM Double bit repeat error inject: Subtype 0x%p fixed location once test complete",
                    subType);
    }

    return retVal;
}
#endif

 /*********************************************************************
 * @fn      ECC_Test_runECCSEC_DED_MCAN1SelfTest
 *
 * @brief   Execute ECC Single bit error self test on MSMC_BUSECC_RAM aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECCSEC_DED_MCAN1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType, i;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR Single bit error self test: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    /* Run one shot test for MSMC_BUSECC_RAM 1 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(PSRAMECC_16K0_PSRAM16KX32E_ADD);

    injectErrorConfig.flipBitMask = 0x5;
#if defined(SOC_AM62X)
    subType = SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_PSRAM16KX32E_PSRAM0_ECC_RAM_ID;
#endif
	for(i = SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE; i<= SDL_INJECT_ECC_ERROR_FORCING_2BIT_N_ROW_REPEAT; i++)
	{
		result = SDL_ECC_selfTest(SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR,
                                  subType,
                                  i,
                                  &injectErrorConfig,
                                  1000);

	}
    if (result == SDL_PASS ) {
        DebugP_log("\r\n ECC_Test_runECCSEC_DED_MCAN1SelfTest  Single bit error self test: Subtype %d: test complete",
                    subType);
		retVal = 0;
    } else {
        DebugP_log("\r\n ECC_Test_runECCSEC_DED_MCAN1SelfTest Single bit error self test: Subtype 0x%p test failed",
                    subType);
		retVal = -1;
    }

    return retVal;
}

#endif

#if defined(SOC_AM62AX) || defined (SOC_AM62PX)

/*********************************************************************
 * @fn      ECC_Test_runECC1BitInjectTest
 *
 * @brief   Execute ECC 1 bit inject test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nATCM Single bit error inject: test starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* Run one shot test for ATCM 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                 &injectErrorConfig);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Single bit error inject at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\nATCM Single bit error inject at pErrMem 0x%p and the value is 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitInjectTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitInjectTest
 *
 * @brief   Execute ECC 2 bit Inject test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nATCM Double bit error inject: starting\r\n");

    /* Run one shot test for ATCM 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    injectErrorConfig.flipBitMask = 0x101;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                                 &injectErrorConfig);

    /* Access the memory where injection is expected */
    testLocationValue = injectErrorConfig.pErrMem[0];

    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Double bit error inject: at pErrMem 0x%p: fixed location once test failed\r\n",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\nATCM Double bit error inject: pErrMem 0x%p fixed location once test complete and the value is 0x%p\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitInjectTest()*/

/*********************************************************************
 * @fn      ECC_Test_runECC1BitSelfTest
 *
 * @brief   Execute ECC 1 bit Self test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitSelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nATCM Single bit error self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* Run one shot test for ATCM 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;

    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);

    if (result != SDL_PASS ) {
         DebugP_log("\r\nATCM Single bit error self test at pErrMem 0x%p test failed\r\n",
                     injectErrorConfig.pErrMem);
        retVal = -1;
    } else {

        DebugP_log("\r\nATCM Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitSelfTest*/

int32_t ECC_Test_runECC_nonAccessable1BitSelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nITAG non accessable Single bit error self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x100);

    /* Run one shot test for ATCM 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_CPU0_ITAG_RAM0_RAM_ID,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);

    if (result != SDL_EFAIL ) {
         DebugP_log("\r\nITAG non accessable Single bit error self test at pErrMem 0x%p test failed\r\n",
                     injectErrorConfig.pErrMem);
        retVal = -1;
    } else {

        DebugP_log("\r\nITAG non accessable Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC_nonAccessable1BitSelfTest*/

int32_t ECC_Test_runECC1BitNeg1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nATCM Single bit error negative-1 self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* To get EFAIL  passing invalid chkgrp*/
    injectErrorConfig.chkGrp = 50U;
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);


    if (result != SDL_EFAIL ) {
         DebugP_log("\r\nATCM Single bit error negative-1 self test at pErrMem 0x%p test failed\r\n",
                     injectErrorConfig.pErrMem);
        retVal = -1;
    } else {

        DebugP_log("\r\nATCM Single bit error negative-1 self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitNeg1SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitSelfTest
 *
 * @brief   Execute ECC 2 bit Self Test
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitSelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nATCM Double bit error self test: starting\r\n");

    /* Run one shot test for ATCM 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    injectErrorConfig.flipBitMask = 0x101;
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Double bit error self test: at pErrMem 0x%p: fixed location once test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\nATCM Double bit error self test: pErrMem 0x%p fixed location once test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitSelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC1BitB0TCM0Bank0SelfTest
 *
 * @brief   Execute ECC single bit error test on BTCM0 Bank 0 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitB0TCM0Bank0SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB0TCM0 Bank0 Single bit error self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR);

    /* Run one shot test for BTCM0 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB0TCM0 Bank0 Single bit error self test at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\nB0TCM0 Bank0 Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitB0TCM0Bank0SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitB0TCM0Bank0SelfTest
 *
 * @brief   Execute ECC Double bit error test on BTCM0 Bank 0 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitB0TCM0Bank0SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB0TCM0 Bank0 Double bit error self test: starting\r\n");

    /* Run one shot test for BTCM0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR);

    injectErrorConfig.flipBitMask = 0x201;
    result = SDL_ECC_selfTest(geccMemType,
                              SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\n B0TCM0 Bank0 Double bit error self test: at pErrMem 0x%p: fixed location once test failed",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\n B0TCM0 Bank0 Double bit error self test: pErrMem 0x%p fixed location once test complete",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitB0TCM0Bank0SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC1BitB0TCM0Bank1SelfTest
 *
 * @brief   Execute ECC Single bit error test on BTCM0 Bank 1 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitB0TCM0Bank1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB0TCM0 Bank1 Single bit error self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 4u);

    /* Run one shot test for BTCM0 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_selfTest(geccMemType,
                              (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 1),
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB0TCM0 Bank1 Single bit error self test at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\nB0TCM0 Bank1 Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitB0TCM0Bank1SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitB0TCM0Bank1SelfTest
 *
 * @brief   Execute ECC Double bit error test on BTCM0 Bank 1 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitB0TCM0Bank1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\n B0TCM0 Bank1 Double bit error self test: starting");

    /* Run one shot test for BTCM0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 4u);

    injectErrorConfig.flipBitMask = 0x201;
    result = SDL_ECC_selfTest(geccMemType,
                              (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 1),
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB0TCM0 Bank1 Double bit error self test: at pErrMem 0x%p: fixed location once test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\nB0TCM0 Bank1 Double bit error self test: pErrMem 0x%p fixed location once test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitB0TCM0Bank1SelfTest()*/

/*********************************************************************
 * @fn      ECC_Test_runECC1BitB1TCM0Bank0SelfTest
 *
 * @brief   Execute ECC Double bit error test on B1TCM0 Bank 0 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitB1TCM0Bank0SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB1TCM0 Bank0 Single bit error self test: starting\r\n");

     /* Note the address is relative to start of ram */
     injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 8u);

     /* Run one shot test for BTCM0 1 bit error */
     injectErrorConfig.flipBitMask = 0x20;
     result = SDL_ECC_selfTest(geccMemType,
                               (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 2),
                               SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                               &injectErrorConfig,
                               100000);


     if (result != SDL_PASS ) {
         DebugP_log("\r\nB1TCM0 Bank0 Single bit error self test at pErrMem 0x%p test failed\r\n",
                     injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\nB1TCM0 Bank0 Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitB1TCM0Bank0SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitB1TCM0Bank0SelfTest
 *
 * @brief   Execute ECC Double bit error test on B1TCM0 Bank 0 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitB1TCM0Bank0SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB1TCM0 Bank0 Double bit error self test: starting\r\n");

    /* Run one shot test for BTCM0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 8u);

    injectErrorConfig.flipBitMask = 0x201;
    result = SDL_ECC_selfTest(geccMemType,
                              (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 2),
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB1TCM0 Bank0 Double bit error self test: at pErrMem 0x%p: fixed location once test failed\r\n",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\nB1TCM0 Bank0 Double bit error self test: pErrMem 0x%p fixed location once test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitB1TCM0Bank0SelfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC1BitB1TCM0Bank1SelfTest
 *
 * @brief   Execute ECC Single bit error test on B1TCM0 Bank 1 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitB1TCM0Bank1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB1TCM0 Bank1 Single bit error self test: starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 0xcu);

    /* Run one shot test for BTCM0 1 bit error */
    injectErrorConfig.flipBitMask = 0x20;
    result = SDL_ECC_selfTest(geccMemType,
                              (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 3),
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              100000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB1TCM0 Bank1 Single bit error self test at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\nB1TCM0 Bank1 Single bit error self test at pErrMem 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitB1TCM0Bank1SelfTest()*/

/*********************************************************************
 * @fn      ECC_Test_runECC2BitB1TCM0Bank1SelfTest
 *
 * @brief   Execute ECC Single bit error test on B1TCM0 Bank 1 memory
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitB1TCM0Bank1SelfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nB1TCM0 Bank1 Double bit error self test: starting\r\n");

    /* Run one shot test for BTCM0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_B0TCM0_BANK0_ADDR + 0xcu);

    injectErrorConfig.flipBitMask = 0x201;
    result = SDL_ECC_selfTest(geccMemType,
                              (SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID + 3),
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nB1TCM0 Bank1 Double bit error self test: at pErrMem 0x%p: fixed location once test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        DebugP_log("\r\nB1TCM0 Bank1 Double bit error self test: pErrMem 0x%p fixed location once test complete\r\n",
                    injectErrorConfig.pErrMem);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitB1TCM0Bank1SelfTest() */

int32_t ECC_Test_runECC_ErrMemInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nError inject: EFAIL test starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0x00);

    /* Run one shot test for B0TCM 1 bit error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_B0TCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                                 &injectErrorConfig);


    if (result != SDL_EFAIL ) {
        DebugP_log("\r\nError inject at pErrMem 0x%p EFAIL test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\nError inject at pErrMem 0x%p and the value is 0x%p: EFAIL test complete\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC_ErrMemInjectTest() */

int32_t ECC_Test_runECC1BitNrowInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nATCM Single bit N row error inject: test starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* Run one shot test for ATCM 1 bit N row error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_N_ROW_ONCE,
                                 &injectErrorConfig);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Single bit N row error inject at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\nATCM Single bit N row error inject at pErrMem 0x%p and the value is 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitNrowInjectTest() */

int32_t ECC_Test_runECC1BitRepeatInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nATCM Single bit Repeat error inject: test starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* Run one shot test for ATCM 1 bit Repeat error */
    injectErrorConfig.flipBitMask = 0x10;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_1BIT_REPEAT,
                                 &injectErrorConfig);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Single bit Repeat error inject at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\nATCM Single bit Repeat error inject at pErrMem 0x%p and the value is 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitRepeatInjectTest() */

int32_t ECC_Test_runECC2BitNrowInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    volatile uint32_t testLocationValue;

    DebugP_log("\r\nATCM Double bit N row error inject: test starting\r\n");

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    /* Run one shot test for ATCM 2 bit N row error */
    injectErrorConfig.flipBitMask = 0x101;
    result = SDL_ECC_injectError(geccMemType,
                                 SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_N_ROW_ONCE,
                                 &injectErrorConfig);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Double bit N row error inject at pErrMem 0x%p test failed\r\n",
                    injectErrorConfig.pErrMem);
        retVal = -1;
    } else {
        /* Access the memory where injection is expected */
        testLocationValue = injectErrorConfig.pErrMem[0];

        DebugP_log("\r\nATCM Double bit N row error inject at pErrMem 0x%p and the value is 0x%p: test complete\r\n",
                    injectErrorConfig.pErrMem, testLocationValue);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitNrowInjectTest() */

int32_t ECC_Test_runECC2BitRepeatInjectTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nATCM Double bit repeat error inject: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
	/* Run one shot test for ATCM 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(SDL_MCU_R5FSS0_ATCM0_BANK0_ADDR);

    injectErrorConfig.flipBitMask = 0x101;

    subType = SDL_MCU_R5FSS0_ATCM0_BANK0_RAMID;

    result = SDL_ECC_injectError(geccMemType,
                                 subType,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_REPEAT,
                                 &injectErrorConfig);

    /* Access the memory where injection is expected */
    testLocationValue = injectErrorConfig.pErrMem[0];

    if (result != SDL_PASS ) {
        DebugP_log("\r\nATCM Double bit repeat error inject: Subtype %d: fixed location once test failed\r\n",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\nATCM Double bit repeat error inject: Subtype 0x%p fixed location once test complete\r\n",
                    subType);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitRepeatInjectTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC1BitMCANselfTest
 *
 * @brief   Execute ECC Single bit error self test on MCAN aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC1BitMCANselfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nMCAN Single bit error self test: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));

    /* Run one shot test for MCAN 1 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0u);

    injectErrorConfig.flipBitMask = 0x1;
    injectErrorConfig.chkGrp = 0x0;
    subType = SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR_CTRL_EDC_VBUSS_RAM_ID;

    result = SDL_ECC_selfTest(SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR,
                              subType,
                              SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE,
                              &injectErrorConfig,
                              1000);


    if (result != SDL_PASS ) {
        DebugP_log("\r\nMCAN Single bit error self test: Subtype %d: test failed\r\n",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\nMCANSingle bit error self test: Subtype 0x%p test complete\r\n",
                    subType);
    }

    return retVal;
}/* End of ECC_Test_runECC1BitMCANselfTest() */

/*********************************************************************
 * @fn      ECC_Test_runECC2BitVTM0selfTest
 *
 * @brief   Execute ECC Double bit error self test on MCAN ECC aggregator
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t ECC_Test_runECC2BitVTM0selfTest(void)
{
    SDL_ErrType_t result;
    int32_t retVal=0;
    uint32_t subType;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\nVTM0 Double bit error self test: starting\r\n");

    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
	/* Run one shot test for VTM0 2 bit error */
    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem = (uint32_t *)(0u);

    injectErrorConfig.flipBitMask = 0x101;
    injectErrorConfig.chkGrp = 0x1;
    subType = SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR_K3VTM_N16FFC_CFG_CBASS_CFG_SCR_SCR_EDC_CTRL_0_RAM_ID;

    result = SDL_ECC_selfTest(SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR,
                              subType,
                              SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                              &injectErrorConfig,
                              1000);

    if (result != SDL_PASS ) {
        DebugP_log("\r\nVTM0 Double bit error self test: Subtype %d: fixed location once test failed\r\n",
                    subType);
        retVal = -1;
    } else {
        DebugP_log("\r\nVTM0 Double bit error self test: Subtype 0x%p fixed location once test complete\r\n",
                    subType);
    }

    return retVal;
}/* End of ECC_Test_runECC2BitVTM0selfTest() */

#endif

static int32_t ECC_sdlFuncTest(void)
{
    int32_t result;
    int32_t retVal = 0;
    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    memset(&injectErrorConfig, 0, sizeof(injectErrorConfig));
    injectErrorConfig.pErrMem = (uint32_t *)(0u);
    injectErrorConfig.flipBitMask = 0x3;

    DebugP_log("\r\nECC SDL API tests: starting\r\n");
#if defined(SOC_AM62X)
    result = ECC_Test_runECC1BitInjectTest();
    if (result != SDL_PASS) {
        retVal = -1;
        DebugP_log("\r\n ECC_Test_runECC1BitInjectTest has failed...\r\n");
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC2BitInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitSelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC1BitSelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitNeg1SelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC1BitNeg1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitSelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC2BitSelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitMCAN1SelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC1BitMCAN1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitMCAN1SelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC2BitMCAN1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC_ErrMemInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC_ErrMemInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitNrowInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC1BitNrowInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitRepeatInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC1BitRepeatInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitNrowInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC2BitNrowInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitRepeatInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECC2BitRepeatInjectTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECCSEC_DED_MCAN1SelfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n ECC_Test_runECCSEC_DED_MCAN1SelfTest has failed...\r\n");
        }
    }
#endif

#if defined(SOC_AM62AX) || defined (SOC_AM62PX)
	result = ECC_Test_runECC1BitInjectTest();
    if (result != SDL_PASS) {
        retVal = -1;
        DebugP_log("\r\nECC_Test_runECC1BitInjectTest has failed...\r\n");
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC2BitInjectTest has failed...\r\n");
        }
    }


	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC_ErrMemInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC_ErrMemInjectTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitNrowInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC1BitNrowInjectTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitRepeatInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC1BitRepeatInjectTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitNrowInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC2BitNrowInjectTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitRepeatInjectTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC2BitRepeatInjectTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitMCANselfTest();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\nECC_Test_runECC1BitMCANselfTest has failed...\r\n");
        }
    }

	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitVTM0selfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC2BitVTM0selfTest has failed...\r\n");
        }
    }
	if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitSelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitSelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
       result = ECC_Test_runECC_nonAccessable1BitSelfTest();
       if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC_nonAccessable1BitSelfTest has failed...\r\n");
       }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitNeg1SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitNeg1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitB0TCM0Bank0SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitB0TCM0Bank0SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
       result = ECC_Test_runECC2BitB0TCM0Bank0SelfTest();
         if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC2BitB0TCM0Bank0SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitB0TCM0Bank1SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitB0TCM0Bank1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitB0TCM0Bank1SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC2BitB0TCM0Bank1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitB1TCM0Bank0SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitB1TCM0Bank0SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitB1TCM0Bank0SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC2BitB1TCM0Bank0SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC1BitB1TCM0Bank1SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC1BitB1TCM0Bank1SelfTest has failed...\r\n");
        }
    }

    if (retVal == SDL_PASS) {
        result = ECC_Test_runECC2BitB1TCM0Bank1SelfTest();
        if (result != SDL_PASS) {
           retVal = -1;
           DebugP_log("\r\nECC_Test_runECC2BitB1TCM0Bank1SelfTest has failed...\r\n");
        }
    }

#endif
    /* This needs to be last as it is destructive */

    if ( retVal == SDL_PASS) {
        DebugP_log("\r\nECC SDL API tests: success\r\n");
    } else {
        DebugP_log("\r\nECC SDL API tests: failed\r\n");
    }

    return retVal;

}

/* ECC Function module test */
int32_t ECC_funcTest(void)
{
    int32_t testResult;

    testResult = ECC_Test_init();

    if (testResult != SDL_PASS)
    {
        DebugP_log("\r\n ECC SDL API tests: unsuccessful\r\n");
        return SDL_EFAIL;
    }

    testResult = ECC_sdlFuncTest();


    return (testResult);
}

/* Nothing past this point */
