/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#include <drivers/soc.h>
#include <drivers/pinmux.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/CpuIdP.h>

/* PSC (Power Sleep Controller) timeout */
#define PSC_TIMEOUT                 (1000U)

/* PSC (Power Sleep Controller) Domain enable */
#define PSC_MODSTATE_ENABLE         (0x3U)
int32_t SOC_moduleClockEnable(uint32_t moduleId, uint32_t enable)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t moduleState = TISCI_MSG_VALUE_DEVICE_HW_STATE_TRANS;
    uint32_t resetState = 0U;
    uint32_t contextLossState = 0U;


    /* Get the module state.
       No need to change the module state if it
       is already in the required state
     */
    status = Sciclient_pmGetModuleState(moduleId,
                                        &moduleState,
                                        &resetState,
                                        &contextLossState,
                                        SystemP_WAIT_FOREVER);
    if(status == SystemP_SUCCESS)
    {
        if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF && (enable == 1))
        {
            /* enable the module */
            status = Sciclient_pmSetModuleState(moduleId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                                (TISCI_MSG_FLAG_AOP |
                                                TISCI_MSG_FLAG_DEVICE_RESET_ISO),
                                                SystemP_WAIT_FOREVER);
            if (status == SystemP_SUCCESS)
            {
                status = Sciclient_pmSetModuleRst(moduleId,
                                                0x0U,
                                                SystemP_WAIT_FOREVER);
            }
        }
        else
        if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_ON && (enable == 0))
        {
            /* disable the module */
            status = Sciclient_pmSetModuleState(moduleId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                (TISCI_MSG_FLAG_AOP),
                                                SystemP_WAIT_FOREVER);
        }
    }

    return status;
}

int32_t SOC_moduleSetClockFrequency(uint32_t moduleId, uint32_t clkId, uint64_t clkRate)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i = 0U;
    uint64_t respClkRate = 0;
    uint32_t numParents = 0U;
    uint32_t moduleClockParentChanged = 0U;
    uint32_t clockStatus = 0U;
    uint32_t origParent = 0U;
    uint32_t foundParent = 0U;
    uint64_t Clkfreq = clkRate;

    /* Check if the clock is enabled or not */
    status = Sciclient_pmModuleGetClkStatus(moduleId,
                                            clkId,
                                            &clockStatus,
                                            SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        /* Get the number of parents for the clock */
        status = Sciclient_pmGetModuleClkNumParent(moduleId,
                                                   clkId,
                                                   &numParents,
                                                   SystemP_WAIT_FOREVER);
    }
    if (status == SystemP_SUCCESS)
    {
        if(clkRate == 0xFF)
        {
            /* Get module clock if the clock is not provided by the application */
            status = Sciclient_pmGetModuleClkFreq(moduleId,
                                                  clkId,
                                                  &Clkfreq,
                                                  SystemP_WAIT_FOREVER);
        }
    }
    if (status == SystemP_SUCCESS)
    {
        if(numParents > 1U)
        {
            /* save the original parent to restore later */
            status = Sciclient_pmGetModuleClkParent(moduleId,
                                                    clkId,
                                                    &origParent,
                                                    SystemP_WAIT_FOREVER);
        }
    }
    if (status == SystemP_SUCCESS)
    {
        /* Disable the clock before changing the frequency */
        status = Sciclient_pmModuleClkRequest(moduleId,
                                              clkId,
                                              TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ,
                                              0U,
                                              SystemP_WAIT_FOREVER);
    }
    if (status == SystemP_SUCCESS)
    {
        foundParent = 0U;
        /* For each parent query and check if frequency can be set at that parent */
        for(i=0U;i<numParents;i++)
        {
            if (numParents > 1U)
            {
                /* Setting the new parent */
                status = Sciclient_pmSetModuleClkParent(moduleId,
                                                        clkId,
                                                        clkId+i+1,
                                                        SystemP_WAIT_FOREVER);

                if (status == SystemP_SUCCESS)
                {
                    moduleClockParentChanged = 1U;
                }
            }
            if (status == SystemP_SUCCESS)
            {
                /* Check if the clock can be set to desired freq at this parent */
                status = Sciclient_pmQueryModuleClkFreq(moduleId,
                                                        clkId,
                                                        Clkfreq,
                                                        &respClkRate,
                                                        SystemP_WAIT_FOREVER);
            }
            if (status == SystemP_SUCCESS)
            {
                if(respClkRate == Clkfreq)
                {
                    /* yes, found a parent at which this frequency can be set */
                    foundParent = 1U;
                }
            }
            if(foundParent)
            {
                break; /* found a parent to set clock frequency, rebak form the loop */
            }
        }
    }
    if (status == SystemP_SUCCESS)
    {
        if(foundParent == 1U)
        {
            /* Set the clock at the desired frequency at the currently selected parent */
            status = Sciclient_pmSetModuleClkFreq(moduleId,
                                                  clkId,
                                                  Clkfreq,
                                                  TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                                  SystemP_WAIT_FOREVER);
        }
        else
        {
            /* no parent found to set the desired frequency */
            status = SystemP_FAILURE;
        }

    }
    if (status == SystemP_SUCCESS)
    {
        if (clockStatus == TISCI_MSG_VALUE_CLOCK_HW_STATE_NOT_READY)
        {
            /* Restore the clock again to original state */
            status = Sciclient_pmModuleClkRequest(moduleId,
                                                  clkId,
                                                  clockStatus,
                                                  0U,
                                                  SystemP_WAIT_FOREVER);
        }
    }
    if (status != SystemP_SUCCESS)
    {
        if (moduleClockParentChanged == 1U)
        {
            /* No parent found or some error, restore the parent to original value */
            Sciclient_pmSetModuleClkParent(moduleId,
                                           clkId,
                                           origParent,
                                           SystemP_WAIT_FOREVER);
            /* let the failure status be returned, so not checking status for this API call */
        }
    }

    return status;
}

const char *SOC_getCoreName(uint16_t coreId)
{
    static char *coreIdNames[CSL_CORE_ID_MAX+1] = {
        "a530-0",
        "a530-1",
        "unknown"
    };
    const char *name;

    if(coreId < CSL_CORE_ID_MAX)
    {
        name = coreIdNames[coreId];
    }
    else
    {
        name = coreIdNames[CSL_CORE_ID_MAX];
    }
    return name;
}

uint64_t SOC_getSelfCpuClk(void)
{
    uint64_t cpuClockRate = 1250*1000000;

    return cpuClockRate;
}

void SOC_controlModuleLockMMR(uint32_t domainId, uint32_t partition)
{
    uint32_t            baseAddr;

    if(SOC_DOMAIN_ID_MAIN == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_MMR_ID_BASE);
    }

}

void SOC_controlModuleUnlockMMR(uint32_t domainId, uint32_t partition)
{
    uint32_t            baseAddr;

    if(SOC_DOMAIN_ID_MAIN == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_MMR_ID_BASE);
    }

    if(SOC_DOMAIN_ID_WKUP == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_ID_MMRS_BASE);
    }

    return;
}

void SOC_setEpwmTbClk(uint32_t epwmInstance, uint32_t enable)
{
    if(epwmInstance < CSL_EPWM_PER_CNT)
    {

        if(TRUE == enable)
        {
            /* Enable Time base clock in CTRL MMR */
            
            CSL_REG32_WR(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE + CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN,
                ((CSL_REG32_RD(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE +
                  CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN) & 0x1FF) | (1 << epwmInstance)));
        }
        else
        {
            /* Disable Time base clock in CTRL MMR */
            CSL_REG32_WR(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE + CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN,
                ((CSL_REG32_RD(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE +
                  CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN) & 0x1FF) & ~(1 << epwmInstance)));
        }

        /* CTRL_MMR0 registers are not locked again */
    }
}

void SOC_setDevStat(uint32_t bootMode)
{

    /* Change bootmode by setting devstat register */
    CSL_REG32_WR(CSL_WKUP_CTRL_MMR0_ID_MMRS_BASE + CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT, bootMode);

    return;
}

int32_t SOC_moduleGetClockFrequency(uint32_t moduleId, uint32_t clkId, uint64_t *clkRate)
{
    int32_t status = SystemP_SUCCESS;

    status = Sciclient_pmGetModuleClkFreq(moduleId,
                                            clkId, clkRate,
                                            SystemP_WAIT_FOREVER);

    return status;
}

void SOC_generateSwWarmResetMainDomain(void)
{

    /* MAIN domain reset */
    CSL_REG32_FINS(CSL_WKUP_CTRL_MMR0_ID_MMRS_BASE + CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL,
                    WKUP_CTRL_MMR_CFG5_RST_CTRL_SW_WARMRESET,
                    0x6U);


    /* execute wfi */
#if defined(__ARM_ARCH_7R__)
    __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
#endif
}

uint32_t SOC_getWarmResetCauseMainDomain(void)
{
    uint32_t     resetCause = 0U;

    /* Read the Reset Cause Register bits */
    resetCause = CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_ID_MMRS_BASE + CSL_WKUP_CTRL_MMR_CFG5_RST_SRC);

    return resetCause;
}

int32_t SOC_getPSCState(uint32_t instNum, uint32_t domainNum, uint32_t moduleNum,
                    uint32_t *domainState, uint32_t *moduleState)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr = 0;

    if (instNum == SOC_PSC_DOMAIN_ID_MAIN)
    {
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_PSC0_BASE);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        *domainState = CSL_REG32_FEXT(baseAddr + CSL_PSC_PDSTAT(domainNum), PSC_PDSTAT_STATE);
        *moduleState = CSL_REG32_FEXT(baseAddr + CSL_PSC_MDSTAT(moduleNum), PSC_MDSTAT_STATE);
    }

    return status;
}

int32_t SOC_setPSCState(uint32_t instNum, uint32_t domainNum, uint32_t moduleNum, uint32_t pscState)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr = 0;
    CSL_PscRegs *pscRegs = NULL;
    uint32_t loopCnt = 0;
    uint32_t pdTransStatus;

    if (instNum == SOC_PSC_DOMAIN_ID_MAIN)
    {
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_PSC0_BASE);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        pscRegs = (CSL_PscRegs *)baseAddr;
        if (CSL_REG32_FEXT(baseAddr + CSL_PSC_MDSTAT(moduleNum), PSC_MDSTAT_STATE) == pscState)
        {
            ;
        }
        else
        {
            if (pscState == PSC_MODSTATE_ENABLE)
            {
                CSL_FINS( pscRegs->PDCTL[domainNum], PSC_PDCTL_NEXT, 1);
            }

            /* Enable the clock for the module */
            CSL_FINS( pscRegs->MDCTL[moduleNum] , PSC_MDCTL_NEXT, pscState );

            /* Start the state transition */
            uint32_t pwrDmnGrp = domainNum >> 5U;
            uint32_t pwrDmnNumInGrp = domainNum & 0x1FU;
            CSL_REG32_WR (baseAddr + CSL_PSC_PTCMD(pwrDmnGrp), 1 << pwrDmnNumInGrp);

            do {
                pdTransStatus = CSL_FEXTR( baseAddr + CSL_PSC_PTSTAT(pwrDmnGrp), \
                                pwrDmnNumInGrp, pwrDmnNumInGrp );
                loopCnt++;
            } while (pdTransStatus && (loopCnt < PSC_TIMEOUT));

            if (pdTransStatus == 0)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }

        }
    }

    return status;
}

void SOC_setFSSCtrlFlashBootSize(void)
{
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_MMR_ID_BASE);

    /* Selects the size of the boot block to be used for the OSPI flash
     * interface. Default value is 1'b0 - S0_BOOT_SIZE_64MB for the MMR
     * register. Set 1'b1 - S0_BOOT_SIZE_128MB to update the value.
     */
    if(CSL_REG32_FEXT(baseAddr + CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL, \
                      MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SIZE) != 1U)
    {
        CSL_REG32_FINS(baseAddr + CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL, \
                       MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SIZE, 1U);
    }

}

uint64_t Soc_getPhyAddr(uint64_t virtAddr)
{
    return virtAddr;
}
