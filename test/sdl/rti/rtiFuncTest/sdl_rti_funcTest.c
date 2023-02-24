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
 *  \file     sdl_rti_funcTest.c
 *
 *  \brief    This file contains RTI DWWD Function test code.
 *
 **/


#include "rti_main.h"
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>
#include <sdl/dpl/sdl_dpl.h>

#define RTI_DWD_MIN_PRELOAD_VAL             (0x1FFFU)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32_t isrFlag = RTI_NO_INTERRUPT;
/**< Flag used to indicate interrupt is generated */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static inline uint32_t RTIDwwdReadTimeOut(uint32_t baseAddr)
{
    uint32_t timeOutValue;

    timeOutValue = ((HW_RD_REG32(baseAddr + RTI_RTIDWDPRLD)
                     << RTI_DWWDPRLD_MULTIPLIER_SHIFT) |
                    RTI_DWD_MIN_PRELOAD_VAL);

    return timeOutValue;
}

/* internal function to read the window size */
static inline uint32_t RTIDwwdReadWinSz(uint32_t baseAddr)
{
    uint32_t   windowSize;
    /* Get configured Window Size */
    windowSize = HW_RD_REG32(baseAddr + RTI_RTIDWWDSIZECTRL);
    return (windowSize);
}

static uint32_t RTIGetPreloadValue(uint32_t rtiClkSource, uint32_t timeoutVal)
{
    uint32_t clkFreqKHz       = (uint32_t) RTI_CLOCK_SOURCE_32KHZ_FREQ_KHZ,
             timeoutNumCycles = 0;

    switch (rtiClkSource)
    {
        case RTI_CLOCK_SOURCE_32KHZ:
            clkFreqKHz = (uint32_t) RTI_CLOCK_SOURCE_32KHZ_FREQ_KHZ;
            break;
        case RTI_CLOCK_SOURCE_200MHZ:
            clkFreqKHz = (uint32_t) RTI_CLOCK_SOURCE_200MHZ_FREQ_KHZ;
            break;
        default:
            break;
    }
    /* Get the clock ticks for given time-out value */
    timeoutNumCycles = timeoutVal * clkFreqKHz;
    return timeoutNumCycles;
}

int32_t RTIDwwdIsClosedWindow(uint32_t rtiModuleBase, uint32_t *pIsClosedWindow)
{
    uint32_t closedWindowstatus, currentDownCounter, windowSizeShift;
    uint32_t windowStartTime, timeOutValue, windowSize,baseAddr =0U;

    int32_t retVal = SDL_EFAIL;
    if ((rtiModuleBase        != ((uint32_t) NULL)) &&
        (pIsClosedWindow != (NULL_PTR)))
    {
        windowSizeShift    = (uint32_t)
                             RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
#if defined (M4F_CORE)
		SDL_RTI_getBaseaddr(SDL_INSTANCE_MCU_RTI0_CFG,&baseAddr);
#endif
#if defined (R5F_CORE)
		SDL_RTI_getBaseaddr(SDL_INSTANCE_WKUP_RTI0,&baseAddr);
#endif
        /* Get configured Window Size */
        windowSize = RTIDwwdReadWinSz(baseAddr);
        switch (windowSize)
        {
            case RTI_DWWD_WINDOWSIZE_100_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
                break;
            case RTI_DWWD_WINDOWSIZE_50_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT_SHIFT;
                break;
            case RTI_DWWD_WINDOWSIZE_25_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT_SHIFT;
                break;
            case RTI_DWWD_WINDOWSIZE_12_5_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT_SHIFT;
                break;
            case RTI_DWWD_WINDOWSIZE_6_25_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT_SHIFT;
                break;
            case RTI_DWWD_WINDOWSIZE_3_125_PERCENT:
                windowSizeShift = (uint32_t)
                                  RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT_SHIFT;
                break;
            default:
                break;
        }
        timeOutValue    = RTIDwwdReadTimeOut(baseAddr);
        windowStartTime = (timeOutValue /
                           (uint32_t) ((uint32_t) 0x1U << windowSizeShift));
        /* Get current down counter */
        currentDownCounter = HW_RD_REG32(baseAddr + RTI_RTIDWDCNTR);
        if (currentDownCounter > windowStartTime)
        {
            closedWindowstatus = TRUE;
        }
        else
        {
            closedWindowstatus = FALSE;
        }
        /* Update the status */
        *pIsClosedWindow = closedWindowstatus;
        retVal = SDL_PASS;
    }
    return (retVal);
}

static void RTISetClockSource(uint32_t rtiModuleSelect,
                              uint32_t rtiClockSourceSelect)
{
    uint32_t baseAddr;

	switch (rtiModuleSelect) {
#if defined (M4F_CORE)
        case SDL_MCU_RTI0_CFG_BASE:
#endif
#if defined (R5F_CORE)
        case SDL_WKUP_RTI0_CFG_BASE:
#endif
			baseAddr = (uint32_t)SDL_DPL_addrTranslate(SDL_MCU_CTRL_MMR_CFG0_MCU_RTI0_CLKSEL, SDL_WKUP_CTRL_MMR0_CFG0_SIZE);
            HW_WR_FIELD32(baseAddr,
                          SDL_MCU_CTRL_MMR_CFG0_MCU_RTI0_CLKSEL_CLK_SEL,
                          rtiClockSourceSelect);
            break;
    }
}

static void RTIAppExpiredDwwdService(uint32_t rtiModuleBase, uint32_t rtiWindow_size)
{
	uint32_t rtiModule =0U;
#if defined (M4F_CORE)
	SDL_RTI_getBaseaddr(rtiModuleBase,&rtiModule);
#endif
#if defined (R5F_CORE)
	SDL_RTI_getBaseaddr(SDL_INSTANCE_WKUP_RTI0,&rtiModule);
#endif
    /* Set dwwd window size to 100 percent. */
    SDL_RTI_writeWinSz(rtiModule, RTI_DWWD_WINDOWSIZE_100_PERCENT);
    SDL_DPL_delay(1U);
    /* Servicing watchdog will generate error. */
#if defined (M4F_CORE)
    SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
    SDL_RTI_writeWinSz(rtiModule, rtiWindow_size);
    SDL_DPL_delay(1U);
    /* Service watchdog again. */
    SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
#endif
#if defined (R5F_CORE)
    SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
    SDL_RTI_writeWinSz(rtiModule, rtiWindow_size);
    SDL_DPL_delay(1U);
    /* Service watchdog again. */
    SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
#endif
}

int32_t SDL_RTI_funcTest(void)
{
    uint32_t rtiModule;
    uint32_t closedWinStatus;
    int32_t  retVal = SDL_PASS;
    SDL_RTI_configParms     pConfig;
    SDL_RTI_staticRegs         pStaticRegs;

#if defined (M4F_CORE)
    rtiModule = SDL_MCU_RTI0_CFG_BASE;
#endif
#if defined (R5F_CORE)
    rtiModule = SDL_WKUP_RTI0_CFG_BASE;
#endif
    printf("RTI Function test started\n");

    /* Register Interrupt */
        isrFlag = RTI_NO_INTERRUPT;


    /* Configure RTI parameters */
    pConfig.SDL_RTI_dwwdPreloadVal = RTIGetPreloadValue(RTI_CLOCK_SOURCE_32KHZ, RTI_WDT_TIMEOUT);
    pConfig.SDL_RTI_dwwdWindowSize = RTI_DWWD_WINDOWSIZE_100_PERCENT;
    pConfig.SDL_RTI_dwwdReaction   = RTI_DWWD_REACTION_GENERATE_NMI;

    /* Select RTI module clock source */
    RTISetClockSource(rtiModule, RTI_CLOCK_SOURCE_32KHZ);
    printf("RTI Function test checking1 \n");
#if defined (M4F_CORE)
    retVal = SDL_RTI_config(SDL_INSTANCE_MCU_RTI0_CFG, &pConfig);
#endif
#if defined (R5F_CORE)
    retVal = SDL_RTI_config(SDL_INSTANCE_WKUP_RTI0, &pConfig);
#endif

    if (retVal == SDL_EFAIL)
    {
        printf("Error during Window configuration.\n");
    }

    /* Verify the config */
#if defined (M4F_CORE)
    retVal = SDL_RTI_verifyConfig(SDL_INSTANCE_MCU_RTI0_CFG, &pConfig);
#endif
#if defined (R5F_CORE)
    retVal = SDL_RTI_verifyConfig(SDL_INSTANCE_WKUP_RTI0, &pConfig);
#endif

    if (retVal == SDL_EFAIL)
    {
        printf("Error during Window Verify configuration.\n");
    }

    if (retVal == SDL_PASS)
    {
#if defined (M4F_CORE)
        SDL_RTI_readStaticRegs(SDL_INSTANCE_MCU_RTI0_CFG, &pStaticRegs);
#endif
#if defined (R5F_CORE)
        SDL_RTI_readStaticRegs(SDL_INSTANCE_WKUP_RTI0, &pStaticRegs);
#endif

        switch(pStaticRegs.RTI_WWDSIZECTRL)
        {
            case RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT:
                printf("    DWWD configured to 100 percent window size\n");
                break;
            case RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT:
                printf("    DWWD configured to 50 percent window size\n");
                break;
            case RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT:
                printf("    DWWD configured to 25 percent window size\n");
                break;
            case RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT:
                printf("    DWWD configured to 6.25 percent window size\n");
                break;
            case RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT:
                printf("    DWWD configured to 3.125 percent window size\n");
                break;
        }

        /* Configure RTI and do not service. Generates End time violation. */
        printf("    DWWD is configured for %u ms time-out \n", RTI_WDT_TIMEOUT);

        printf("    DWWD will generate interrupt after "
            "above time-out period.\n");
#if defined (M4F_CORE)
        SDL_RTI_start(SDL_INSTANCE_MCU_RTI0_CFG);
#endif
#if defined (R5F_CORE)
        SDL_RTI_start(SDL_INSTANCE_WKUP_RTI0);
#endif
        /* Let DWWD expire here */
        printf("\nWait for %u ms for interrupt "
            "to be generated by DWWD.\n", RTI_WDT_TIMEOUT);

        while (RTI_NO_INTERRUPT == isrFlag)
        {
            /* Wait for interrupt */
        }
        isrFlag = RTI_NO_INTERRUPT;

        RTIAppExpiredDwwdService(rtiModule, pConfig.SDL_RTI_dwwdWindowSize);

        if (retVal == SDL_PASS)
        {
            printf("\nRTI End time violation test successful. \n\n");
        }
        else
        {
            printf("RTI End time violation test failed. \n");
        }
    }


    if ((retVal == SDL_PASS) &&
        (pConfig.SDL_RTI_dwwdWindowSize != RTI_DWWD_WINDOWSIZE_100_PERCENT))
    {
        /* RTI is serviced in closed window. Generates DWWD violation.
         * Closed window violation cant be generated for 100% window size.
         */
        volatile uint32_t loopBreak = FALSE;
        isrFlag = RTI_NO_INTERRUPT;

        while (loopBreak == FALSE)
        {
            printf("RTI DWWD closed window violation test running. \n");
            RTIDwwdIsClosedWindow(rtiModule, &closedWinStatus);
            if (closedWinStatus == TRUE)
            {
                loopBreak = TRUE;
#if defined (M4F_CORE)
                SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
#endif
#if defined (R5F_CORE)
                SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
#endif
                while (RTI_NO_INTERRUPT == isrFlag)
                {
                    /* Wait for interrupt */
                }
            }
            else
            {
                /* DWWD is in open window, just service it. */
#if defined (M4F_CORE)
                SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
#endif
#if defined (R5F_CORE)
                SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
#endif
            }
        }
        if (retVal == SDL_PASS)
        {
            printf("RTI DWWD closed window violation test successful. \n\n");
        }
        else
        {
            printf("RTI DWWD closed window violation test failed. \n");
        }
    }

    if (retVal == SDL_PASS)
    {
        int32_t numIteration = 3;
        printf("    RTI DWWD proper servicing test running. \n");
        printf("    Please wait for max %d ms. \n\n", 3 * RTI_WDT_TIMEOUT);

        isrFlag = RTI_NO_INTERRUPT;

        /* Service DWWD in open window multiple times. Should not generate interrupt.
         * servicing 3 times, will run RTI for more than configured timeout for all window sizes. */
        while (numIteration-- >= 0)
        {
            RTIDwwdIsClosedWindow(rtiModule, &closedWinStatus);
            while (closedWinStatus == TRUE)
            {
                RTIDwwdIsClosedWindow(rtiModule, &closedWinStatus);
                /* Keep checking till window is open. */
#if !defined (R5F_CORE)
                SDL_DPL_delay(1U);
#endif
            }
#if defined (M4F_CORE)
            SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
#endif
#if defined (R5F_CORE)
            SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
#endif
        }
        if (isrFlag != RTI_NO_INTERRUPT)
        {
            /* DWWD interrupt is generated when it is not expected to. */
            retVal = SDL_EFAIL;
        }
        if (retVal == SDL_PASS)
        {
            printf("RTI DWWD proper servicing test successful. \n\n");
        }
        else
        {
            printf("RTI DWWD proper servicing test failed. \n");
        }
    }

    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static void IntrDisable(uint32_t intrSrc)
{
    uint32_t intrStatus;
#if defined (M4F_CORE)
    SDL_RTI_getStatus(SDL_INSTANCE_MCU_RTI0_CFG, &intrStatus);
    SDL_RTI_clearStatus(SDL_INSTANCE_MCU_RTI0_CFG, intrStatus);

	/* clear the ERROR pin */
    SDL_ESM_clrNError(SDL_ESM_INST_WKUP_ESM0);
#endif
#if defined (R5F_CORE)
    SDL_RTI_getStatus(SDL_INSTANCE_WKUP_RTI0, &intrStatus);
    SDL_RTI_clearStatus(SDL_INSTANCE_WKUP_RTI0, intrStatus);

	/* clear the ERROR pin */
    SDL_ESM_clrNError(SDL_ESM_INST_MAIN_ESM0);
#endif

    isrFlag  |= RTI_ESM_INTRPT;
}

int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInst, SDL_ESM_IntType esmIntrType,
                                            uint32_t grpChannel,  uint32_t index, uint32_t intSrc, void *arg)
{
    int32_t retVal = SDL_PASS;

    DebugP_log("\nInterrupt is generated to ESM\n");
    DebugP_log("    ESM Call back function called : instType 0x%x, intType 0x%x, " \
                "grpChannel 0x%x, index 0x%x, intSrc 0x%x \n",
                esmInst, esmIntrType, grpChannel, index, intSrc);
    DebugP_log("  Take action \n");

    /* For clearing the interrupt */
    IntrDisable(intSrc);

    return retVal;
}

/********************************* End of file ******************************/
