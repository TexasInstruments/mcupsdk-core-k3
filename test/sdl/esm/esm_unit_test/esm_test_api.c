/*
 *  Copyright (C) 2021-25 Texas Instruments Incorporated
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
 *  \file     esm_test_api.c
 *
 *  \brief    This file contains ESM API test code.
 *
 **/

#define DISP_APP_ARGB32 (3U)

#include "esm_test_main.h"
#include <sdl/sdl_esm.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>

#define SDTF_NUM_RUNALL_TEST_COMMANDS 3
#define MASK_BIT (1u)
#define STATUS_NUM (1u)
#define SDL_ESM_EN_KEY_ENBALE_VAL (0xFU)

#if defined(SOC_AM64X)
#include <sdl/include/am64x_am243x/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am64x/sdl_esm_core.h>
#define SDL_TEST_ESM_BASE SDL_MCU_ESM0_CFG_BASE
#define INT_NUM_HI SDL_MCU_ESM_HI_INTNO
#define INT_NUM_LO SDL_MCU_ESM_LO_INTNO
#define INT_NUM_CFG SDL_MCU_ESM_CFG_INTNO
#endif

#if defined(SOC_AM62X)
#include <sdl/include/am62x/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am62x/sdl_esm_core.h>
#endif

#if defined(SOC_AM62AX)
#include <sdl/include/am62ax/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am62ax/sdl_esm_core.h>
#endif

#if defined(SOC_AM62PX)
#include <sdl/include/am62px/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am62px/sdl_esm_core.h>
#endif
#if defined(SOC_AM275X)
#include <sdl/include/am275x/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am275x/sdl_esm_core.h>
#endif

#if defined(SOC_AM62DX)
#include <sdl/include/am62dx/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/am62dx/sdl_esm_core.h>
#endif

#if defined(SOC_J722S)
#include <sdl/include/j722s/sdlr_soc_baseaddress.h>
#include <sdl/esm/soc/j722s/sdl_esm_core.h>
#endif

#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX) || \
    defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
#define SDL_TEST_ESM_BASE SDL_WKUP_ESM0_CFG_BASE
#define INT_NUM_HI SDL_WKUP_ESM_HI_INTNO
#define INT_NUM_LO SDL_WKUP_ESM_LO_INTNO
#define INT_NUM_CFG SDL_WKUP_ESM_CFG_INTNO
#endif

SDL_ESM_config ESM_esmInitConfig_MAIN_appcallback =
    {
        .esmErrorConfig = {1u, 8u}, /* Self test error config */
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
        .enableBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
        /**< All events enable: except clkstop events for unused clocks
         *   and PCIE events */
        .priorityBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0x00000001u,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
        /**< All events high priority: except clkstop events for unused clocks
         *   and PCIE events */
        .errorpinBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
/**< All events high priority: except clkstop for unused clocks
 *   and PCIE events */
#elif defined(SOC_AM275X)
        .enableBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFEFBFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
        /**< All events enable: except clkstop events for unused clocks
         *   and PCIE events */
        .priorityBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0x00000001u,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFEFBFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
        /**< All events high priority: except clkstop events for unused clocks
         *   and PCIE events */
        .errorpinBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFEFBFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
/**< All events high priority: except clkstop for unused clocks
 *   and PCIE events */
#elif defined(SOC_J722S)
        .enableBitmap = {
            0x00000000u,
            0xFFFFFFFBu,
            0x7FFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFBFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0xFFFFFFFFu,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0x00000000u,
            0xFFFFFFFFu,
        },
        /**< All events enable: except clkstop events for unused clocks
         *   and PCIE events */
        .priorityBitmap = {
            0X00000000U,
            0XFFFFFFFBU,
            0X7FFFFFFFU,
            0X00000001U,
            0XFFFFFFFFU,
            0XFFFFBFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0XFFFFFFFFU,
        },
        /**< All events high priority: except clkstop events for unused clocks
         *   and PCIE events */
        .errorpinBitmap = {
            0X00000000U,
            0XFFFFFFFBU,
            0X7FFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFBFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0XFFFFFFFFU,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0X00000000U,
            0XFFFFFFFFU,
        },
/**< All events high priority: except clkstop for unused clocks
 *   and PCIE events */
#endif
};

volatile uint32_t ESM_callbackInvokedInInterrupt = 0;
volatile uint32_t ESM_callbackInst = 3;
volatile uint32_t ESM_callbackInterruptNum = 0xFFFFFFFF;

int32_t SDTF_runESMInjectHigh_MAIN(void);

int32_t SDL_ESM_callbackStatus()
{
    int32_t retValue = SDL_PASS;
    volatile uint32_t timeOutCnt = 0;
    DebugP_log("\r\nWaiting for ESM Interrupt...");
    do
    {
        timeOutCnt += 1;
        if (timeOutCnt > SDL_ESM_MAX_TIMEOUT_VALUE)
        {
            retValue = SDL_EFAIL;
            break;
        }
    } while (ESM_callbackInvokedInInterrupt == 0);

    if (ESM_callbackInvokedInInterrupt == 1)
    {
        /* It should be noted that for special interrupts, the instance number provided from callback may not be accurate */
        if (ESM_callbackInst == 1)
        {
            DebugP_log("\r\n ESM Callback for interrupt number %u triggered from WKUP ESM!\r\n", ESM_callbackInterruptNum);
        }
        else
        {
            DebugP_log("\r\n ESM Callback for interrupt number %u triggered from MAIN ESM!\r\n", ESM_callbackInterruptNum);
        }
        ESM_callbackInvokedInInterrupt = 0;
        ESM_callbackInst = 3;
        ESM_callbackInterruptNum = 0xFFFFFFFF;
    }
    return retValue;
}

int32_t SDR_ESM_errorInsert(const SDL_ESM_Inst esmInstType,
                            const SDL_ESM_ErrorConfig_t *esmErrorConfig)
{
    uint32_t esmInstBaseAddr;
    int32_t result = SDL_EFAIL;

    if (SDL_ESM_getBaseAddr(esmInstType, &esmInstBaseAddr) == ((bool)true))
    {
        if (esmErrorConfig != ((void *)0u))
        {
            if ((esmErrorConfig->groupNumber < SDL_ESM_MAX_EVENT_MAP_NUM_WORDS) && (esmErrorConfig->bitNumber < BITS_PER_WORD))
            {
                /* Insert error */
                (void)SDL_ESM_setIntrStatusRAW(esmInstBaseAddr,(esmErrorConfig->groupNumber * 32u) + esmErrorConfig->bitNumber);
                result = SDL_PASS;
            }
        }
    }

    return result;
}

int32_t SDL_ESM_triggerCfgIntr(SDL_ESM_Inst esm_instance,uint32_t group)
{
    int32_t retVal = SDL_PASS;
    uint32_t esm_base_addr = 0;

    if(esm_instance == SDL_ESM_INST_MAIN_ESM0)
    {
        SDL_ESM_getBaseAddr(SDL_ESM_INST_MAIN_ESM0,&esm_base_addr);
    }
    else if(esm_instance == SDL_ESM_INST_WKUP_ESM0)
    {
        SDL_ESM_getBaseAddr(SDL_ESM_INST_WKUP_ESM0,&esm_base_addr);
    }
    else
    {
        DebugP_log("Invalid instance for Cfg Interrupt");
        retVal = SDL_EBADARGS;
    }
    if (retVal == SDL_PASS)
    {
        retVal = SDL_ESM_setCfgIntrStatusRAW (esm_base_addr, group);
    }
    return retVal;
}

int32_t SDL_ESM_runPositiveTests(void)
{

#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
    SDL_ESM_Inst instance = SDL_ESM_INST_WKUP_ESM0;
    SDL_ESM_Inst startInstance = SDL_ESM_INST_WKUP_ESM0;
    SDL_ESM_Inst endInstance = SDL_ESM_INST_MAIN_ESM0;
#endif
    SDL_ESM_Inst i;
    int32_t testStatus = SDL_APP_TEST_PASS, apparg;
    SDL_ESM_staticRegs staticRegs;
    uint32_t esmBaseAddr, val;
    uint32_t esmMaxNumEvents;
    SDL_ESM_Instance_t *pEsmInstancePtr;
    esmOperationMode_t esmOpMode;
    uint32_t influence;
    uint32_t lowTime;
    uint32_t pinCntrPre;
    uint32_t status;
    esmGroupIntrStatus_t intrstatus;
    esmInfo_t info;
    esmRevisionId_t revId;
    SDL_ESM_config pCofnig;
    uint32_t esmTestAddr;

    esmTestAddr = (uint32_t)AddrTranslateP_getLocalAddr(SDL_TEST_ESM_BASE);

    /* ESMSetInfluenceOnErrPin API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = startInstance; i <= endInstance; i++)
        {
            if (SDL_ESM_setNError(i) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    /* ESMGetInfluenceOnErrPin API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = startInstance; i <= endInstance; i++)
        {
            if (SDL_ESM_clrNError(i) != SDL_PASS)
            {
                /* Delay some time to allow pin to clear */
                ClockP_usleep(1000);
                if (SDL_ESM_clrNError(i) != SDL_PASS)
                {
                    testStatus = SDL_APP_TEST_FAILED;
                    DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
                }
            }
        }
    }

    /* SDL_ESM_getNErrorStatus API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = startInstance; i <= endInstance; i++)
        {
            if (SDL_ESM_getNErrorStatus(i, &val) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    /* ESMReadStaticRegs API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = startInstance; i <= endInstance; i++)
        {
            if ((SDL_ESM_getStaticRegisters(i, &staticRegs)) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    /* SDL_ESM_registerECCCallback API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = startInstance; i <= endInstance; i++)
        {
            if ((SDL_ESM_registerECCCallback(i, ESM_esmInitConfig_MAIN_appcallback.enableBitmap,
                                             SDL_ESM_applicationCallbackFunction, &apparg)) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    /* SDL_ESM_init API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if ((SDL_ESM_init(instance, &pCofnig, NULL, &apparg)) == SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        for (i = 1; i <= endInstance; i++)
        {

            if (SDL_ESM_getBaseAddr((SDL_ESM_Inst)i, &esmBaseAddr) != true)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        for (i = 1; i <= endInstance; i++)
        {
            if (SDL_ESM_getMaxNumEvents((SDL_ESM_Inst)i, &esmMaxNumEvents) != true)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        for (i = 1; i <= endInstance; i++)
        {
            if (SDL_ESM_selectEsmInst((SDL_ESM_Inst)i, &pEsmInstancePtr) != true)
            {
                testStatus = SDL_APP_TEST_FAILED;
                DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
            }
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setMode(SDL_ESM0_CFG_BASE, ESM_OPERATION_MODE_NORMAL) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setMode(SDL_ESM0_CFG_BASE, ESM_OPERATION_MODE_ERROR_FORCE) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getPinMode(SDL_ESM0_CFG_BASE, &esmOpMode) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getErrorOutMode(SDL_ESM0_CFG_BASE, &esmOpMode) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setInfluenceOnErrPin(SDL_ESM0_CFG_BASE, 5U, true) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getInfluenceOnErrPin(SDL_ESM0_CFG_BASE, 5U, &influence) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setInfluenceOnErrPin(SDL_ESM0_CFG_BASE, 5U, false) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getInfluenceOnErrPin(SDL_ESM0_CFG_BASE, 5U, &influence) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setErrPinLowTimePreload(SDL_ESM0_CFG_BASE, 0x0000FFFFU) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWML_setErrPinLowTimePreload(SDL_ESM0_CFG_BASE, 0x0000FFFFU) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWMH_setErrPinHighTimePreload(SDL_ESM0_CFG_BASE, 0x0000FFFFU) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getErrPinLowTimePreload(SDL_ESM0_CFG_BASE, &lowTime) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWMH_getErrPinHighTimePreload(SDL_ESM0_CFG_BASE, &lowTime) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWML_getErrPinLowTimePreload(SDL_ESM0_CFG_BASE, &lowTime) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getCurrErrPinLowTimeCnt(SDL_ESM0_CFG_BASE, &pinCntrPre) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWMH_getCurrErrPinHighTimeCnt(SDL_ESM0_CFG_BASE, &pinCntrPre) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_PWML_getCurrErrPinLowTimeCnt(SDL_ESM0_CFG_BASE, &pinCntrPre) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getErrPinStatus(SDL_ESM0_CFG_BASE, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_resetErrPin(SDL_ESM0_CFG_BASE) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_enableIntr(SDL_ESM0_CFG_BASE, 5U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_isEnableIntr(SDL_ESM0_CFG_BASE, 5U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_enableIntr(SDL_ESM0_CFG_BASE, 12U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_isEnableIntr(SDL_ESM0_CFG_BASE, 12U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_disableIntr(SDL_ESM0_CFG_BASE, 5U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setIntrPriorityLvl(SDL_ESM0_CFG_BASE, 5U, ESM_INTR_PRIORITY_LEVEL_LOW) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getIntrPriorityLvl(SDL_ESM0_CFG_BASE, 5U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_setIntrPriorityLvl(SDL_ESM0_CFG_BASE, 5U, ESM_INTR_PRIORITY_LEVEL_HIGH) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getIntrPriorityLvl(SDL_ESM0_CFG_BASE, 5U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getIntrStatus(SDL_ESM0_CFG_BASE, 5U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getGroupIntrStatus(SDL_ESM0_CFG_BASE, ESM_INTR_PRIORITY_LEVEL_LOW, &intrstatus) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getGroupIntrStatus(SDL_ESM0_CFG_BASE, ESM_INTR_PRIORITY_LEVEL_HIGH, &intrstatus) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_clearIntrStatus(SDL_ESM0_CFG_BASE, 5U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_setIntrStatusRAW(SDL_ESM0_CFG_BASE, 5U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntrStatusRAW(SDL_ESM0_CFG_BASE, 5U, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_writeEOI(SDL_ESM0_CFG_BASE, 5U) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getRevisionId(SDL_ESM0_CFG_BASE, &revId) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getInfo(SDL_ESM0_CFG_BASE, &info) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getGlobalIntrEnabledStatus(SDL_ESM0_CFG_BASE, &status) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_enableGlobalIntr(SDL_ESM0_CFG_BASE) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_disableGlobalIntr(SDL_ESM0_CFG_BASE) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_reset(SDL_ESM0_CFG_BASE) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
#if defined(SOC_AM64X) || defined(SOC_AM62X)
#if defined(M4F_CORE)
        if (SDL_ESM_getIntNumber(instance, SDL_ESM_INT_TYPE_HI) != INT_NUM_HI)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
#if defined(R5F_CORE)
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_MAIN_ESM0, SDL_ESM_INT_TYPE_HI) != SDL_MAIN_ESM_HI_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
#if defined(SOC_AM64X) || defined(SOC_AM62X)
#if defined(M4F_CORE)
        if (SDL_ESM_getIntNumber(instance, SDL_ESM_INT_TYPE_CFG) != INT_NUM_CFG)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
#if defined(R5F_CORE)
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_MAIN_ESM0, SDL_ESM_INT_TYPE_CFG) != SDL_MAIN_ESM_CFG_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
#if defined(SOC_AM64X) || defined(SOC_AM62X)
#if defined(M4F_CORE)
        if (SDL_ESM_getIntNumber(instance, SDL_ESM_INT_TYPE_LO) != INT_NUM_LO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
#if defined(R5F_CORE)
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_MAIN_ESM0, SDL_ESM_INT_TYPE_LO) != SDL_MAIN_ESM_LO_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
#endif
#endif
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_MAIN_ESM0, SDL_ESM_INT_TYPE_MAX) != SDL_ESM_INTNUMBER_INVALID)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S) || (defined(SOC_AM62X) && defined(M4F_CORE))
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_WKUP_ESM0, SDL_ESM_INT_TYPE_HI) != SDL_WKUP_ESM_HI_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_WKUP_ESM0, SDL_ESM_INT_TYPE_CFG) != SDL_WKUP_ESM_CFG_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_WKUP_ESM0, SDL_ESM_INT_TYPE_LO) != SDL_WKUP_ESM_LO_INTNO)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }
    #endif
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INST_WKUP_ESM0, SDL_ESM_INT_TYPE_MAX) != SDL_ESM_INTNUMBER_INVALID)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getIntNumber(SDL_ESM_INSTANCE_MAX, SDL_ESM_INT_TYPE_HI) != SDL_ESM_INTNUMBER_INVALID)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_enableCfgIntr API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_enableCfgIntr(esmTestAddr, 0x0) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_enableCfgIntr(esmTestAddr, 31) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_enableCfgIntr(esmTestAddr, 0x2) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_disableCfgIntr API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_disableCfgIntr(esmTestAddr, 0x0) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_disableCfgIntr(esmTestAddr, 31) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_disableCfgIntr(esmTestAddr, 0x2) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_getCfgIntrStatus API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_ESM_getCfgIntrStatus(esmTestAddr, 0x0, &val) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getCfgIntrStatus(esmTestAddr, 31, &val) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_getCfgIntrStatus(esmTestAddr, 0x2, &val) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_clearCfgIntrStatus API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_clearCfgIntrStatus(esmTestAddr, 0x0) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_clearCfgIntrStatus(esmTestAddr, 31) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_clearCfgIntrStatus(esmTestAddr, 0x2) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_setCfgIntrStatusRAW API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_setCfgIntrStatusRAW(esmTestAddr, 0x0) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_setCfgIntrStatusRAW(esmTestAddr, 31) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if (SDL_ESM_setCfgIntrStatusRAW(esmTestAddr, 0x2) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("SDLEsm_apiTest: failure on line no %d \r\n", __LINE__);
        }
    }

    /* SDL_ESM_init API test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        if ((SDL_ESM_init(instance, &pCofnig, NULL, &apparg)) == SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pCofnig.enableBitmap[1] = 0x00180003;
        pCofnig.priorityBitmap[1] = 0x000000ff;
        pCofnig.errorpinBitmap[1] = 0xffffffff;
        i = startInstance;
        SDL_ESM_init(i, &pCofnig, NULL, &apparg);
        pCofnig.enableBitmap[1] = 0x00000000;
        pCofnig.priorityBitmap[1] = 0x000000ff;
        pCofnig.errorpinBitmap[1] = 0xffffffff;
        if ((SDL_ESM_verifyConfig(i, &pCofnig)) != SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pCofnig.esmErrorConfig.groupNumber = 0;
        pCofnig.esmErrorConfig.bitNumber = 8;
        pCofnig.enableBitmap[1] = 0x00180003;
        pCofnig.priorityBitmap[1] = 0x000000ff;
        pCofnig.errorpinBitmap[1] = 0xffffffff;
        i = startInstance;
        SDL_ESM_init(i, &pCofnig, NULL, &apparg);
        pCofnig.esmErrorConfig.groupNumber = 8;
        pCofnig.esmErrorConfig.bitNumber = 8;
        pCofnig.enableBitmap[1] = 0x00000000;
        pCofnig.priorityBitmap[1] = 0x000000ff;
        pCofnig.errorpinBitmap[1] = 0xffffffff;
        if ((SDL_ESM_verifyConfig(i, &pCofnig)) != SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pCofnig.enableBitmap[1] = 0x00180003u;
        pCofnig.priorityBitmap[1] = 0x000000ff;
        pCofnig.errorpinBitmap[1] = 0xffffffff;
        i = startInstance;
        SDL_ESM_init(i, &pCofnig, NULL, &apparg);
        if ((SDL_ESM_clrNError(i)) == SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
            DebugP_log("sdlEsm_pos_apiTest: failure on line no. %d \r\n", __LINE__);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-7438 */
        if (SDL_ESM_setPinOutMode(i, SDL_ESM_PWM_PINOUT) != SDL_PASS)
        {
            DebugP_log("SDLEsm_negTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-7439 */
        if (SDL_ESM_setPinOutMode(i, SDL_ESM_LVL_PINOUT) != SDL_PASS)
        {
            DebugP_log("SDLEsm_negTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-7439 */
        if (SDL_ESM_setPinOutMode(SDL_ESM_INSTANCE_MAX, SDL_ESM_LVL_PINOUT) != SDL_EBADARGS)
        {
            DebugP_log("SDLEsm_negTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-2011 */
        if (SDL_ESM_isEnableCfgIntr(0u, 0x0u, &val) != SDL_EBADARGS)
        {
            DebugP_log("SDLEsm_negTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-2013 */
        if (SDL_ESM_isEnableCfgIntr(esmTestAddr, 0x0, NULL) != SDL_EBADARGS)
        {
            DebugP_log("SDLEsm_negTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus == SDL_APP_TEST_PASS)
    {
        uint32_t group = 0x1;
        SDL_ESM_disableCfgIntr(esmTestAddr, group);
        if (SDL_ESM_isEnableCfgIntr(esmTestAddr, group, &val) != SDL_PASS)
        {
            DebugP_log("SDLEsm_posTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_WKUP_ESM0_ESM_LVL_EVENT_ESM0_ESM_INT_LOW_LVL_0
     * (interrupt 2 with group 0 and bit 2) with selfTest
     */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_Inst test_instance = SDL_ESM_INST_WKUP_ESM0;
        SDL_ESM_config pConfig;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[0] = 0x00000004;
        /* Set low priority (not set) */
        pConfig.priorityBitmap[0] = 0x00000000;
        /* Enable error pin */
        pConfig.errorpinBitmap[0] = 0x00000004;
        pConfig.esmErrorConfig.bitNumber = 2;
        pConfig.esmErrorConfig.groupNumber = 0;

        retValue = SDL_ESM_init(test_instance, &pConfig, SDL_ESM_applicationCallbackFunction, &apparg);

        if (retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        retValue = SDR_ESM_errorInsert (test_instance,&pConfig.esmErrorConfig);

        if (retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

    }

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_WKUP_ESM0_ESM_LVL_EVENT_ESM0_ESM_INT_LOW_LVL_0
     * (interrupt 2 with group 0 and bit 2)
     */
#if defined (SOC_AM62PX) || defined (SOC_AM62AX) || defined (SOC_AM62DX) || defined (SOC_AM275X) || (defined (SOC_AM62X) && defined (M4F_CORE))
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_Inst test_instance = SDL_ESM_INST_WKUP_ESM0;
        SDL_ESM_config pConfig;
        SDL_ESM_config pConfig_test;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[0] = 0x00000004;
        /* Set low priority (not set) */
        pConfig.priorityBitmap[0] = 0x00000000;
        /* Enable error pin */
        pConfig.errorpinBitmap[0] = 0x00000004;
        pConfig_test.esmErrorConfig.bitNumber = 2;
        pConfig_test.esmErrorConfig.groupNumber = 0;

        retValue = SDL_ESM_init(test_instance,&pConfig,SDL_ESM_applicationCallbackFunction,&apparg);

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        retValue = SDR_ESM_errorInsert (test_instance,&pConfig_test.esmErrorConfig);
        retValue = SDL_ESM_callbackStatus();

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

    }
#endif

    /**
     * ESM instance setup for config tests - config
     * interrupts are enabled in both instances
     */
#if defined (SOC_AM62PX) || defined (SOC_AM62AX) || defined (SOC_AM62DX) || defined (SOC_AM275X)
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_Inst test_instance = SDL_ESM_INST_WKUP_ESM0;
        SDL_ESM_config pConfig;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[0] = 0x00000001;
        /* Set high priority */
        pConfig.priorityBitmap[0] = 0x00000001;
        /* Enable error pin */
        pConfig.errorpinBitmap[0] = 0x00000001;

        retValue = SDL_ESM_init(test_instance,&pConfig,SDL_ESM_applicationCallbackFunction,&apparg);
        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        test_instance = SDL_ESM_INST_MAIN_ESM0;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[1] = 0x00000020;
        /* Set high priority */
        pConfig.priorityBitmap[1] = 0x00000020;
        /* Enable error pin */
        pConfig.errorpinBitmap[1] = 0x00000020;

        retValue = SDL_ESM_init(test_instance,&pConfig,SDL_ESM_applicationCallbackFunction,&apparg);
        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_WKUP_ESM0_ESM_LVL_EVENT_ESM0_ESM_INT_CFG_LVL_0
     * (interrupt 0 with group 0 and bit 0)
     */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_config pConfig_main_test;
        pConfig_main_test.esmErrorConfig.groupNumber = 1;

        retValue = SDL_ESM_triggerCfgIntr(SDL_ESM_INST_MAIN_ESM0,pConfig_main_test.esmErrorConfig.groupNumber);
        retValue = SDL_ESM_callbackStatus ();

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_ESM0_ESM_LVL_EVENT_WKUP_ESM0_ESM_INT_CFG_LVL_0
     * (interrupt 37 with group 1 and bit 5)
     */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_config pConfig_wkup_test;
        pConfig_wkup_test.esmErrorConfig.groupNumber = 1;

        retValue = SDL_ESM_triggerCfgIntr(SDL_ESM_INST_WKUP_ESM0,pConfig_wkup_test.esmErrorConfig.groupNumber);
        retValue = SDL_ESM_callbackStatus();

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
#endif

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_ESM0_ESM_LVL_EVENT_WKUP_ESM0_ESM_INT_HI_LVL_0
     * (interrupt 38 with group 1 and bit 6)
     */
#if defined (R5F_CORE)
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_Inst test_instance = SDL_ESM_INST_MAIN_ESM0;
        SDL_ESM_config pConfig;
        SDL_ESM_config pConfig_test;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[1] = 0x00000040;
        /* Set high priority */
        pConfig.priorityBitmap[1] = 0x00000040;
        /* Enable error pin */
        pConfig.errorpinBitmap[1] = 0x00000040;
        pConfig_test.esmErrorConfig.bitNumber = 6;
        pConfig_test.esmErrorConfig.groupNumber = 1;

        /* First, reset the WKUP ESM instance so we don't have any pending interrupts */
        retValue = SDL_ESM_reset(SDL_WKUP_ESM0_CFG_BASE);

        retValue = SDL_ESM_init(test_instance,&pConfig,SDL_ESM_applicationCallbackFunction,&apparg);

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        retValue = SDR_ESM_errorInsert (test_instance,&pConfig_test.esmErrorConfig);
        retValue = SDL_ESM_callbackStatus();

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

    }
#endif
    if (testStatus == SDL_APP_TEST_PASS)
    {
        /* Test case: PROC_SDL-2013 */
    #if defined (R5F_CORE)
        if (SDTF_runESMInjectHigh_MAIN() != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    #endif
    }

    /**
     * Test case for running SDL_ESM_checkSpecialEvent on
     * SDLR_WKUP_ESM0_ESM_LVL_EVENT_ESM0_ESM_INT_HI_LVL_0
     * (interrupt 1 with group 0 and bit 1)
     */
#if defined (SOC_AM62PX) || defined (SOC_AM62AX) || defined (SOC_AM62DX) || defined (SOC_AM275X)
    if (testStatus == SDL_APP_TEST_PASS)
    {
        int32_t retValue;
        SDL_ESM_Inst test_instance_wkup = SDL_ESM_INST_WKUP_ESM0;
        SDL_ESM_Inst test_instance_main = SDL_ESM_INST_MAIN_ESM0;
        SDL_ESM_config pConfig;
        SDL_ESM_config pConfig_test;

        /* Enable interrupt for ESM instance */
        pConfig.enableBitmap[0] = 0x00000002;
        /* Set high priority */
        pConfig.priorityBitmap[0] = 0x00000002;
        /* Enable error pin */
        pConfig.errorpinBitmap[0] = 0x00000002;

        static SDL_ESM_config ESM_Example_esmInitConfig_Inst_wkup =
        {
            .enableBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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
            .priorityBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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
            .errorpinBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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


        static SDL_ESM_config ESM_Example_esmInitConfig_Inst_main =
        {
            .enableBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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
            .priorityBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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
            .errorpinBitmap = {
                         0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
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

        pConfig_test.esmErrorConfig.bitNumber = 1;
        pConfig_test.esmErrorConfig.groupNumber = 0;

        retValue = SDL_ESM_init(test_instance_wkup,&ESM_Example_esmInitConfig_Inst_wkup,SDL_ESM_applicationCallbackFunction,&apparg);

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        retValue = SDL_ESM_init(test_instance_main,&ESM_Example_esmInitConfig_Inst_main,SDL_ESM_applicationCallbackFunction,&apparg);

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }

        retValue = SDR_ESM_errorInsert(test_instance_wkup,&pConfig_test.esmErrorConfig);
        retValue = SDL_ESM_callbackStatus();

        if(retValue != SDL_PASS)
        {
            DebugP_log("SDLEsm_PosTest: failure on line no. %d \r\n", __LINE__);
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
#endif

    return (testStatus);
}

static uint32_t arg;
void esm_init_appcb(SDL_ESM_Inst esmType)
{
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;
    result = SDL_ESM_init(esmType, &ESM_esmInitConfig_MAIN_appcallback, SDL_ESM_applicationCallbackFunction, ptr);
    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log("ESM_ECC_Example_init: Error initializing MAIN ESM: result = %d\r\n", result);
    }
    else
    {
        DebugP_log("\r\nESM_ECC_Example_init: Init MAIN ESM complete \r\n");
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
    int32_t retVal = 0;
    SDL_ESM_ErrorConfig_t esmErrorConfig;

    esmErrorConfig.groupNumber = groupNumber;
    esmErrorConfig.bitNumber = bitNumber;

    DebugP_log("\r\n ESM inject: test starting for Esm instance %d \r\n", esmType);

    /* Run esm test 2*/
    result = SDL_ESM_errorInsert(esmType, &esmErrorConfig);
    result = SDL_ESM_callbackStatus();

    if (result != SDL_PASS)
    {
        DebugP_log("\r\n ESM inject test for Esm instance %d failed\r\n", esmType);
        retVal = -1;
    }
    else
    {
        DebugP_log("\r\n ESM inject test for Esm instance %d Done\r\n", esmType);
    }
    uint32_t   esmInstBaseAddr;
    if (retVal == 0)
    {
        SDL_ESM_getBaseAddr(esmType, &esmInstBaseAddr);
        result = SDL_ESM_clearIntrStatus(esmInstBaseAddr, groupNumber*32+bitNumber);
        if (result != SDL_PASS)
        {
            DebugP_log("\r\n ESM clear interrupt test for Esm instance %d failed", esmType);
            retVal = -1;
        }
    }
    return retVal;
}

int32_t SDTF_runESMInjectHigh_MAIN(void)
{
    int32_t retVal = 0;
    /* First, reset the MAIN ESM instance so we don't have any pending interrupts */
    retVal = SDL_ESM_reset(SDL_ESM0_CFG_BASE);
    esm_init_appcb(SDL_ESM_INST_MAIN_ESM0);
    retVal = SDTF_runESMInjectInstance(SDL_ESM_INST_MAIN_ESM0, 3, 0);
    return retVal;
}
