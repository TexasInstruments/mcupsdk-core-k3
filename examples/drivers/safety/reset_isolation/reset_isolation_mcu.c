/*
 *  Copyright (C) 2018-2022 Texas Instruments Incorporated
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
 */

#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "stdbool.h"
#include <drivers/soc.h>

#if defined (SOC_AM62X)
#define RESET_REQ_INTR_NUM (CSLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MAINRESET_REQUEST_GLUE_MAIN_RESETZ_SYNC_STRETCH_0 + 16U)
#elif defined (SOC_AM62AX) || defined (SOC_AM62PX)
#define RESET_REQ_INTR_NUM (CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_GLUELOGIC_MAINRESET_REQUEST_GLUE_MAIN_RESETZ_SYNC_STRETCH_0)
#endif
void resetReqIsr(void *args)
{
    int32_t status;
    uint32_t resetSrc;
    uint32_t pscDomainState;
    uint32_t pscModuleStateMain2MCU = 0;
    uint32_t pscModuleStateMCU2Main = 0;

    /* Disable LPSC Main2MCU */
    status = SOC_getPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU,
            CSL_WKUP_LPSC_MAIN2MCU_ISO, &pscDomainState, &pscModuleStateMain2MCU);
    if ((status == SystemP_SUCCESS) && (pscDomainState == SOC_PSC_DOMAIN_ON)
        && (pscModuleStateMain2MCU != SOC_PSC_DISABLE))
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                        CSL_WKUP_LPSC_MAIN2MCU_ISO, SOC_PSC_DISABLE);
    }

    if (status == SystemP_SUCCESS)
    {
#if defined(SOX_AM62X)
        /* Disable LPSC MCU2Main */
        status = SOC_getPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU,
                CSL_WKUP_LPSC_MCU2MAIN_ISO, &pscDomainState, &pscModuleStateMCU2Main);
        if ((status == SystemP_SUCCESS) && (pscDomainState == SOC_PSC_DOMAIN_ON)
            && (pscModuleStateMCU2Main != SOC_PSC_DISABLE))
        {
            status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                            CSL_WKUP_LPSC_MCU2MAIN_ISO, SOC_PSC_DISABLE);
        }
#elif defined (SOX_AM62AX) || defined (SOC_AM62PX)
        /* Disable LPSC DM2MCU */
        status = SOC_getPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU,
                CSL_WKUP_LPSC_DM2MCU_ISO, &pscDomainState, &pscModuleStateMCU2Main);
        if ((status == SystemP_SUCCESS) && (pscDomainState == SOC_PSC_DOMAIN_ON)
            && (pscModuleStateMCU2Main != SOC_PSC_DISABLE))
        {
            status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                            CSL_WKUP_LPSC_DM2MCU_ISO, SOC_PSC_DISABLE);
        }
#endif
    }

    if (status == SystemP_SUCCESS)
    {
        /* Clear reset source */
        resetSrc = SOC_getWarmResetCauseMcuDomain();
        SOC_clearResetCauseMainMcuDomain (resetSrc);

        /* Allow main domain reset to propogate */
        SOC_setMCUResetIsolationDone(0);

        SOC_waitMainDomainReset();

        /* Enable back reset isolation */
        SOC_setMCUResetIsolationDone(1);
    }

    /* Restore back previous state of LSPC Main2MCU */
    if ((status == SystemP_SUCCESS) && (pscModuleStateMain2MCU != SOC_PSC_DISABLE))
    {
        SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                        CSL_WKUP_LPSC_MAIN2MCU_ISO, pscModuleStateMain2MCU);
    }

    /* Restore back previous state of LSPC MCU2Main */
    if (((status == SystemP_SUCCESS)) && (pscModuleStateMCU2Main != SOC_PSC_DISABLE))
    {
        SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                        CSL_WKUP_LPSC_MAIN2MCU_ISO, pscModuleStateMCU2Main);
    }
}

void reset_isolation_main (void * args)
{
    int32_t status = SystemP_FAILURE;
    uint32_t pscMain2MCUDisable, pscMCU2MainDisable, debugIsolationEnable, psMCU2DMDisable;

    /* Disabling Main2MCU PSC. This would restrict the main domain from accessing
    MCU domain peripherals/registers. Care must be taken no Main domain cores access
    MCU domain registers after this */
    pscMain2MCUDisable = 1;
    /* Disabling MCU2Main PSC. This would restrict the MCU domain from accessing
    Main domain peripherals/registers. Care must be taken no MCU domain cores access
    Main domain registers after this */
    pscMCU2MainDisable = 1;
    psMCU2DMDisable = 1;
    /* Enabling debug isolation will restrict the JTAG access to MCU domain */
    debugIsolationEnable = 0;

    status = SOC_enableResetIsolation (pscMain2MCUDisable, pscMCU2MainDisable,
                                       psMCU2DMDisable,
                                       debugIsolationEnable);
    DebugP_assert (status == SystemP_SUCCESS);

    {
        HwiP_Params resetHwiParams;
        HwiP_Object resetObject;

        HwiP_Params_init(&resetHwiParams);
        resetHwiParams.intNum = RESET_REQ_INTR_NUM;
        resetHwiParams.callback = resetReqIsr;
        resetHwiParams.isPulse = 0;
        HwiP_construct(&resetObject, &resetHwiParams);
    }

    {
        for(uint32_t count = 0; count < 10u; count++)
        {
            ClockP_sleep(1);
            DebugP_log("I am running (MCU) !!:- %d\r\n", count);

            if (count == 5u)
            {
                /* Reset */
                DebugP_log("Resetting Main domain !!\r\n");
                SOC_generateSwWarmResetMainDomainFromMcuDomain();
            }
        }
    }

    DebugP_log("All tests have passed!!\r\n");

}
