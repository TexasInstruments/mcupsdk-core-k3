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
 *  \file     ecc_main.c
 *
 * \brief This file demonstrates using the Error Correcting Code Module (ECC),
 *         utilizing the ECC and ESM Software Diagnostic Reference (SDL) functions.
 *
 *  \details  ESM Safety Example module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/sciclient.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <dpl_interface.h>
#include <kernel/dpl/DebugP.h>
#include <unity.h>
#if defined (SOC_AM62X)
#include "soc/am62x/ecc_func.h"
#endif /* SOC_AM62X */
#if defined (SOC_AM62AX)
#include "soc/am62ax/ecc_func.h"
#endif /* SOC_AM62AX */
#if defined (SOC_AM62PX)
#include "soc/am62px/ecc_func.h"
#endif /* SOC_AM62PX */
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <sdl/r5/v0/sdl_r5_utils.h>
#include <sdl/ecc/sdl_ecc_utils.h>
#include <kernel/dpl/AddrTranslateP.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#if defined (SOC_AM62X)
#define AUX_NUM_DEVICES 32
#endif
#if defined (SOC_AM62PX)
#define AUX_NUM_DEVICES 38
#endif
#if defined (SOC_AM62AX)
#define AUX_NUM_DEVICES 28
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile bool esmError = false;
int32_t status = SDL_PASS;
#if defined(SOC_AM62X)
uint32_t aux_devices[AUX_NUM_DEVICES] =
{
  TISCI_DEV_A53SS0,
  TISCI_DEV_A53SS0_CORE_0,
  TISCI_DEV_A53SS0_CORE_1,
  TISCI_DEV_A53SS0_CORE_2,
  TISCI_DEV_A53SS0_CORE_3,
  TISCI_DEV_COMPUTE_CLUSTER0,
  TISCI_DEV_CSI_RX_IF0,
  TISCI_DEV_DMASS0,
  TISCI_DEV_FSS0_OSPI_0,
  TISCI_DEV_GICSS0,
  TISCI_DEV_ICSSM0,
  TISCI_DEV_MCAN0,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MCU_MCAN0,
  TISCI_DEV_MCU_MCAN1,
  TISCI_DEV_MMCSD0,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MMCSD2,
  TISCI_DEV_CPSW0,
  TISCI_DEV_HSM0,
  TISCI_DEV_USB0,
  TISCI_DEV_MAIN_USB0_ISO_VD,
  TISCI_DEV_USB1,
  TISCI_DEV_MAIN_USB1_ISO_VD,
  TISCI_DEV_MCU_M4FSS0,
  TISCI_DEV_MCU_M4FSS0_CORE0,
  TISCI_DEV_MCU_M4FSS0_CBASS_0,
  TISCI_DEV_WKUP_ESM0,
  TISCI_DEV_WKUP_VTM0,
  TISCI_DEV_WKUP_R5FSS0_SS0,
  TISCI_DEV_WKUP_R5FSS0,
  TISCI_DEV_WKUP_R5FSS0_CORE0
};
#endif
#if defined (SOC_AM62PX)
uint32_t aux_devices[AUX_NUM_DEVICES] =
{
  TISCI_DEV_A53SS0,
  TISCI_DEV_A53SS0_CORE_0,
  TISCI_DEV_A53SS0_CORE_1,
  TISCI_DEV_A53SS0_CORE_2,
  TISCI_DEV_A53SS0_CORE_3,
  TISCI_DEV_COMPUTE_CLUSTER0,
  TISCI_DEV_CSI_RX_IF0,
  TISCI_DEV_DMASS0,
  TISCI_DEV_FSS0_OSPI_0,
  TISCI_DEV_GICSS0,
  TISCI_DEV_MCAN0,
  TISCI_DEV_MCAN1,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MCU_MCAN0,
  TISCI_DEV_MCU_MCAN1,
  TISCI_DEV_MMCSD0,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MMCSD2,
  TISCI_DEV_PSCSS0,
  TISCI_DEV_CPSW0,
  TISCI_DEV_HSM0,
  TISCI_DEV_USB0,
  TISCI_DEV_USB1,
  TISCI_DEV_MCU_R5FSS0,
  TISCI_DEV_MCU_R5FSS0_CORE0,
  TISCI_DEV_WKUP_ESM0,
  TISCI_DEV_WKUP_VTM0,
  TISCI_DEV_WKUP_R5FSS0_SS0,
  TISCI_DEV_WKUP_R5FSS0,
  TISCI_DEV_WKUP_R5FSS0_CORE0,
  TISCI_DEV_MAIN_USB0_ISO_VD,
  TISCI_DEV_MAIN_USB2_ISO_VD,
  TISCI_DEV_CSI_RX_IF0,
  TISCI_DEV_DSS0,
  TISCI_DEV_DSS_DSI0,
  TISCI_DEV_DSS1,
  TISCI_DEV_DSS1_DPI1_PLLSEL_DEV_VD,
  TISCI_DEV_DSS1_DPI0_PLLSEL_DEV_VD,
};
#endif
#if defined(SOC_AM62AX)
uint32_t aux_devices[AUX_NUM_DEVICES] =
{
  TISCI_DEV_A53SS0,
  TISCI_DEV_A53SS0_CORE_0,
  TISCI_DEV_A53SS0_CORE_1,
  TISCI_DEV_A53SS0_CORE_2,
  TISCI_DEV_A53SS0_CORE_3,
  TISCI_DEV_COMPUTE_CLUSTER0,
  TISCI_DEV_CSI_RX_IF0,
  TISCI_DEV_DMASS0,
  TISCI_DEV_FSS0_OSPI_0,
  TISCI_DEV_GICSS0,
  TISCI_DEV_MCAN0,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MCU_MCAN0,
  TISCI_DEV_MCU_MCAN1,
  TISCI_DEV_MMCSD0,
  TISCI_DEV_MMCSD1,
  TISCI_DEV_MMCSD2,
  TISCI_DEV_CPSW0,
  TISCI_DEV_HSM0,
  TISCI_DEV_USB0,
  TISCI_DEV_USB1,
  TISCI_DEV_MCU_R5FSS0,
  TISCI_DEV_MCU_R5FSS0_CORE0,
  TISCI_DEV_WKUP_ESM0,
  TISCI_DEV_WKUP_VTM0,
  TISCI_DEV_WKUP_R5FSS0_SS0,
  TISCI_DEV_WKUP_R5FSS0,
  TISCI_DEV_WKUP_R5FSS0_CORE0
};
#endif
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void ECC_func_app(void *args);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                          EXternal Function Definitions                              */
/* ========================================================================== */
extern int32_t ECC_funcTest(void);
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

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


int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInst,
                                            SDL_ESM_IntType esmIntrType,
                                            uint32_t grpChannel,
                                            uint32_t index,
                                            uint32_t intSrc,
                                            uintptr_t *arg)
{

    SDL_ECC_MemType eccmemtype;
    SDL_Ecc_AggrIntrSrc eccIntrSrc;
    SDL_ECC_ErrorInfo_t eccErrorInfo;
    int32_t retVal = 0u;


    DebugP_log("\r\nESM Call back function called : instType 0x%x, intType 0x%x, " \
                "grpChannel 0x%x, index 0x%x, intSrc 0x%x \r\n",
                esmInst, esmIntrType, grpChannel, index, intSrc);
    DebugP_log("\r\nTake action\r\n");
    if(esmIntrType == 1u){
        DebugP_log("\r\nHigh Priority Interrupt Executed\r\n");
    }
    else{
        DebugP_log("\r\nLow Priority Interrupt Executed\r\n");
    }

#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
#if defined (SOC_AM62X)
    if (intSrc == SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_FATAL_0)
#elif defined (SOC_AM62AX) || defined (SOC_AM62PX)
    if (intSrc == SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_CSI_FATAL_0)
#endif
    {
        uint32_t regVal;
        /*
         * To trigger the error on checker 0, a write to 0x30101908 was performed.
         * This caused the bit error to propogate to the same register.
         * In order to be able to clear the error event, we need to correct the
         * register contents to the expected value first.
         */
        *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101908)) = 0x70;

        /* Now, clear the CSI error event at the source */
        regVal = *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101904));
        *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101904)) = regVal;
    }
    else
    {
#endif
        retVal = SDL_ECC_getESMErrorInfo(esmInst, intSrc, &eccmemtype, &eccIntrSrc);

        /* Any additional customer specific actions can be added here */
        retVal = SDL_ECC_getErrorInfo(eccmemtype, eccIntrSrc, &eccErrorInfo);

        DebugP_log("\r\nECC Error Call back function called : eccMemType %d, errorSrc 0x%x, " \
                   "ramId %d, bitErrorOffset 0x%04x%04x, bitErrorGroup %d\r\n",
                   eccmemtype, eccIntrSrc, eccErrorInfo.memSubType, (uint32_t)(eccErrorInfo.bitErrorOffset >> 32),
                   (uint32_t)(eccErrorInfo.bitErrorOffset & 0x00000000FFFFFFFF), eccErrorInfo.bitErrorGroup);

        if (eccErrorInfo.injectBitErrCnt != 0)
        {
            SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_INJECT, eccErrorInfo.injectBitErrCnt);
        }
        else
        {
            SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_NORMAL, eccErrorInfo.bitErrCnt);
        }

        retVal = SDL_ECC_ackIntr(eccmemtype, eccIntrSrc);
#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
    }
#endif

    esmError = true;

    return retVal;
}

/* SDL_ECC_applicationCallbackFunction is expected to be defined by the application. It is
 * required by the SDL ECC module. It is called by the SDL ECC module to notify the
 * application of certain ECC errors that are reported as Exception events.
 * Note, however, that it is not executed in this example */
void SDL_ECC_applicationCallbackFunction(SDL_ECC_MemType eccMemType,
                                         uint32_t errorSrc,
                                         uint32_t address,
                                         uint32_t ramId,
                                         uint64_t bitErrorOffset,
                                         uint32_t bitErrorGroup)
{

    DebugP_log("\r\nECC Error Call back function called : eccMemType %d, errorSrc 0x%x, " \
                "address 0x%x, ramId %d, bitErrorOffset 0x%04x%04x, bitErrorGroup %d\r\n",
                eccMemType, errorSrc, address, ramId, (uint32_t)(bitErrorOffset >> 32),
                (uint32_t)(bitErrorOffset & 0x00000000FFFFFFFF), bitErrorGroup);
    DebugP_log("\r\nTake action\r\n");

    /* Any additional customer specific actions can be added here */

}

static int32_t sdlApp_dplInit(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    ret = SDL_TEST_dplInit();
    if (ret != SDL_PASS)
    {
        DebugP_log("\r\nError: Init Failed\r\n");
    }

    for (int i = 0; i < AUX_NUM_DEVICES; i++)
    {
        /* Power up RTI */
        status = Sciclient_pmSetModuleState(aux_devices[i],
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);

        if (status != SDL_PASS)
        {
            DebugP_log("\r\nSciclient_pmSetModuleState 0x%x ...FAILED: retValue %d\r\n",
                        aux_devices[i], status);
        }
    }

    return ret;
}

#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
static int32_t sdlInit_CsiEcc(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    /* Initialize the ASF registers to report parity errors */

    /*
     * set csi_rx_if_asf_int_mask register un-mask ECC error events
     * An ECC error on endpoint 0, checker 0 will result in the CSR error event.
     * An ECC error on endpoint 0, checker 1 will result in the DAP error event.
     */
    *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101908)) = 0x70;

    /*
     * set csi_rx_if_asf_fatal_nonfatal_select to 1's to set all errors as fatal
     * This will trigger the ESM event SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_FATAL_0
     */
    *(uint32_t *)(AddrTranslateP_getLocalAddr(0x30101910)) = 0x7F;

    return ret;
}
#endif

void ECC_func_app(void *args)
{
    int32_t    testResult;

    testResult = ECC_funcTest();
    DebugP_log("\r\nECC func Test\r\n");
    if (testResult == SDL_PASS)
    {
        DebugP_log("\r\nAll test have passed.\r\n");
    }
    else
    {
        DebugP_log("\r\nSome test have failed.\r\n");
    }

}

void ecc_app_runner(void)
{
#if defined(UNITY_INCLUDE_CONFIG_H)
    UNITY_BEGIN();
    RUN_TEST(ECC_func_app,0, NULL);
    UNITY_END();
#else
    ECC_func_app();
#endif
}


int32_t test_main(void)
{
    sdlApp_dplInit();
#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
    sdlInit_CsiEcc();
#endif

    #if defined (R5F_CORE)
    /*Enabling the ECC module*/
    SDL_ECC_UTILS_enableECCATCM();

    /*Enabling the Event bus*/
    SDL_UTILS_enable_event_bus();
    #endif

    ecc_app_runner();

    return (0);
}

/* Nothing past this point */
