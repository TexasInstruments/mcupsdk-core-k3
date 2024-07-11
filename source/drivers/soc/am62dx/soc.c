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
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/CpuIdP.h>
#include <string.h>

#define CSL_MAIN_CTRL_MMR_LOCKn_KICK0_OFFSET(n)   (0x1008 + 0x4000*(n))
#define CSL_MCU_CTRL_MMR_LOCKn_KICK0_OFFSET(n)    (0x1008 + 0x4000*(n))

/* define the unlock and lock values */
#define KICK_LOCK_VAL                           (0x00000000U)
#define KICK0_UNLOCK_VAL                        (0x68EF3490U)
#define KICK1_UNLOCK_VAL                        (0xD172BC5AU)

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
                                                        clkRate,
                                                        &respClkRate,
                                                        SystemP_WAIT_FOREVER);
            }
            if (status == SystemP_SUCCESS)
            {
                if(respClkRate == clkRate)
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
                                                  clkRate,
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
        "mcu-r5f0-0",
        "r5f0-0",
        "a530-0",
        "a530-1",
        "a531-0",
        "a531-1",
        "hsm-m4f0-0",
        "c75ss0",
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

uint32_t SOC_getCoreId(const char * coreName)
{
    if (strcmp("mcu-r5f0-0", coreName) == 0)
    {
        return CSL_CORE_ID_MCU_R5FSS0_0;
    }
    else if (strcmp("r5f0-0", coreName) == 0)
    {
        return CSL_CORE_ID_R5FSS0_0;
    }
    else if (strcmp("a530-0", coreName) == 0)
    {
        return CSL_CORE_ID_A53SS0_0;
    }
    else if (strcmp("a530-1", coreName) == 0)
    {
        return CSL_CORE_ID_A53SS0_1;
    }
    else if (strcmp("a531-0", coreName) == 0)
    {
        return CSL_CORE_ID_A53SS1_0;
    }
    else if (strcmp("a531-1", coreName) == 0)
    {
        return CSL_CORE_ID_A53SS1_1;
    }
    else if (strcmp("hsm-m4f0-0", coreName) == 0)
    {
        return CSL_CORE_ID_HSM_M4FSS0_0;
    }
    else if (strcmp("c75ss0", coreName) == 0)
    {
        return CSL_CORE_ID_C75SS0_0;
    }
    return CSL_CORE_ID_INVALID;
}

uint64_t SOC_getSelfCpuClk(void)
{
    uint64_t cpuClockRate = 0U;
    Sciclient_pmGetModuleClkFreq(
                    Sciclient_getSelfDevIdCore(),
                    0,
                    &cpuClockRate,
                    SystemP_WAIT_FOREVER);

    return cpuClockRate;
}

void SOC_controlModuleLockMMR(uint32_t domainId, uint32_t partition)
{
    uint32_t            baseAddr;
    volatile uint32_t  *kickAddr;

    if(SOC_DOMAIN_ID_MAIN == domainId)
    {
        /* in AM62Dx, main dowmin MMRs are left unlocked since when working with linux kernel, linux kernel assumes MMRs are unlocked */
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MAIN_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 1 */
    }

    if(SOC_DOMAIN_ID_MCU == domainId || SOC_DOMAIN_ID_WKUP == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MCU_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 1 */
    }

    if(SOC_DOMAIN_ID_WKUP == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MCU_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK_LOCK_VAL);      /* KICK 1 */
    }


    return;
}

void SOC_controlModuleUnlockMMR(uint32_t domainId, uint32_t partition)
{
    uint32_t            baseAddr;
    volatile uint32_t  *kickAddr;

    if(SOC_DOMAIN_ID_MAIN == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MAIN_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK0_UNLOCK_VAL);   /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK1_UNLOCK_VAL);   /* KICK 1 */
    }

    if(SOC_DOMAIN_ID_MCU == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MCU_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK0_UNLOCK_VAL);   /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK1_UNLOCK_VAL);   /* KICK 1 */
    }

    if(SOC_DOMAIN_ID_WKUP == domainId)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);
        kickAddr = (volatile uint32_t *) (baseAddr + CSL_MCU_CTRL_MMR_LOCKn_KICK0_OFFSET(partition));
        CSL_REG32_WR(kickAddr, KICK0_UNLOCK_VAL);   /* KICK 0 */
        kickAddr++;
        CSL_REG32_WR(kickAddr, KICK1_UNLOCK_VAL);   /* KICK 1 */
    }

    return;
}

void SOC_setEpwmTbClk(uint32_t epwmInstance, uint32_t enable)
{
    if(epwmInstance < CSL_EPWM_PER_CNT)
    {
        /* Time base clock enable register belongs to partition 1 of the CTRL MMR */
        uint32_t epwmPartition = 1;
        /* Unlock CTLR_MMR0 registers */
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, epwmPartition);

        if(TRUE == enable)
        {
            /* Enable Time base clock in CTRL MMR */
            CSL_REG32_WR(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN,
                ((CSL_REG32_RD(CSL_CTRL_MMR0_CFG0_BASE +
                  CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN) & 0x1FF) | (1 << epwmInstance)));
        }
        else
        {
            /* Disable Time base clock in CTRL MMR */
            CSL_REG32_WR(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN,
                ((CSL_REG32_RD(CSL_CTRL_MMR0_CFG0_BASE +
                  CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN) & 0x1FF) & ~(1 << epwmInstance)));
        }

        /* CTRL_MMR0 registers are not locked again */
    }
}

void SOC_unlockAllMMR(void)
{
    /* Unlock all 8 partitions in the wakeup domain */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 0);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 1);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 2);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 3);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 4);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 5);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 6);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 7);

    /* Unlock all 6 partitions in the main domain
     * Partitions 3,7 are not used in main domain
     */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 0);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 1);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 4);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 5);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 6);

    /* Unlock all 6 partitions in the mcu domain
     * Partitions 5,7 are not used in mcu domain
     */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 0);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 1);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 2);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 3);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 4);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 6);

    /* Unlock PADCFG control MMRs */
    Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MAIN);
    Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MCU);
}

int32_t SOC_moduleGetClockFrequency(uint32_t moduleId, uint32_t clkId, uint64_t *clkRate)
{
    int32_t status = SystemP_SUCCESS;

    status = Sciclient_pmGetModuleClkFreq(moduleId,
                                            clkId, clkRate,
                                            SystemP_WAIT_FOREVER);

    return status;
}

void SOC_setDevStat(uint32_t bootMode)
{
    /* Unlock CTLR_MMR0 registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 0);

    /* Change bootmode by setting devstat register */
    CSL_REG32_WR(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT, bootMode);

    /* Lock CTLR_MMR0 registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_WKUP, 0);

    return;
}

void SOC_generateSwWarmResetMainDomain(void)
{
    /* Reset Ctrl belongs to partition 6 of the CTRL MMR */
    uint32_t     rstPartition = 6U;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    /* MAIN domain reset */
    CSL_REG32_FINS(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL,
                    WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST,
                    0x6U);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    /* execute wfi */
#if defined(__ARM_ARCH_7R__)
    __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
#endif
}

void SOC_generateSwPORResetMainDomain(void)
{
    /* Reset Ctrl belongs to partition 6 of the CTRL MMR */
    uint32_t     rstPartition = 6U;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    /* MCU domain reset */
    CSL_REG32_FINS(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL,
                   WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR,
                    0x6U);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    /* execute wfi */
#if defined(__ARM_ARCH_7R__)
    __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");
#endif
}

uint32_t SOC_getWarmResetCauseMainDomain(void)
{
    uint32_t     resetCause = 0U;
    /* Reset Src belongs to partition 6 of the CTRL MMR */
    uint32_t     rstPartition = 6U;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    /* Read the Reset Cause Register bits */
    resetCause = CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_RST_SRC);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, rstPartition);

    return resetCause;
}

void SOC_generateSwWarmResetMcuDomain(void)
{
    /* Reset Ctrl belongs to partition 6 of the MCU CTRL MMR */
    uint32_t     rstPartition = 6U, baseAddr;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    /* MAIN domain warm reset */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL,
                    MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MCU_WARMRST,
                    0x6U);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, rstPartition);
}

void SOC_generateSwWarmResetMainDomainFromMcuDomain(void)
{
    /* Reset Ctrl belongs to partition 6 of the MCU CTRL MMR */
    uint32_t     rstPartition = 6U, baseAddr;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    /* MAIN domain reset */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL,
                    MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST,
                    0x6U);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, rstPartition);
}

void SOC_generateSwPORResetMainDomainFromMcuDomain(void)
{
    /* Reset Ctrl belongs to partition 6 of the MCU CTRL MMR */
    uint32_t     rstPartition = 6U, baseAddr;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    /* MAIN domain POR reset */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL,
                    MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR,
                    0x6U);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, rstPartition);
}
void SOC_triggerMcuLpmWakeup(void)
{
    uint32_t baseAddr = 0;

    /* Unlock partition 0 to access IPC_SET MMR */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 0);

    /* Get the base address of MCU CTRL MMR */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr (CSL_MCU_CTRL_MMR0_CFG0_BASE);

    /* Set IPC SRC SET to 1 */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_IPC_SET0, \
            MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SRC_SET, 1);

    /* Set IPC SET to 1 */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_IPC_SET0, \
            MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SET, 1);

    /* Not locking the partition back as Linux expects it to be unlocked */
}

uint32_t SOC_getWarmResetCauseMcuDomain(void)
{
    uint32_t     resetCause = 0U;
    /* Reset Src belongs to partition 6 of the MCU CTRL MMR */
    uint32_t     rstPartition = 6U, baseAddr;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    /* Read the Reset Cause Register bits */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    resetCause = CSL_REG32_RD(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_SRC);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    return resetCause;
}

void SOC_clearResetCauseMainMcuDomain(uint32_t resetCause)
{
    /* Reset Src belongs to partition 6 of the CTRL MMR */
    uint32_t     rstPartition = 6U, baseAddr;

    /* Unlock CONTROL MMR registers */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    /* Clear the Reset Cause Register bits */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    CSL_REG32_WR(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_SRC, resetCause);

    /* Lock CONTROL MMR registers */
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, rstPartition);

    return;
}

int32_t SOC_getPSCState(uint32_t instNum, uint32_t domainNum, uint32_t moduleNum,
                    uint32_t *domainState, uint32_t *moduleState)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr = 0;

    if (instNum == SOC_PSC_DOMAIN_ID_MAIN)
    {
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_PSCSS0_BASE);
    }
    else if (instNum == SOC_PSC_DOMAIN_ID_MCU)
    {
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_WKUP_PSC0_BASE);
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
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_PSCSS0_BASE);
    }
    else if (instNum == SOC_PSC_DOMAIN_ID_MCU)
    {
        baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CSL_WKUP_PSC0_BASE);
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

int32_t SOC_enableResetIsolation(uint32_t main2McuIsolation,
                                uint32_t dm2McuIsolation,
                                uint32_t mcu2dmIsolation,
                                uint32_t debugIsolationEnable)
{
    uint32_t baseAddr = 0;
    int32_t status = SystemP_SUCCESS;
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 6);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 1);

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr (CSL_MCU_CTRL_MMR0_CFG0_BASE);

    /* Block MAIN domain reset */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL, \
            MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z, 1);

    /* Enable timeout gasket */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0, \
            MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_EN, 1);

    /* Write a non zero value to Magic Word */
    CSL_REG32_WR(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD, 0x1);

    if (debugIsolationEnable == 1)
    {
        /* Enable debug Isolation */
        CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL,
                MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_DBG_ISO_EN, 1);
    }

    /* Enable reset Isolation */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL, \
            MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_RST_ISO_EN, 1);

    /* Block TIFS to trigger reset of MCU domain */
    CSL_REG32_FINS(baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL, \
            MCU_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z, 1);

    if (main2McuIsolation == 1)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                        CSL_WKUP_LPSC_MAIN2MCU_ISO, SOC_PSC_DISABLE);
    }

    if (status == SystemP_SUCCESS)
    {
        if (dm2McuIsolation == 1)
        {
            status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                                CSL_WKUP_LPSC_DM2MCU_ISO, SOC_PSC_DISABLE);
        }
    }

    if (status == SystemP_SUCCESS)
    {
        if (mcu2dmIsolation == 1)
        {
            status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, CSL_WKUP_GP_CORE_CTL_MCU, \
                                    CSL_WKUP_LPSC_MCU2DM_ISO, SOC_PSC_DISABLE);

        }
    }

    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, 6);
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, 1);

    return status;
}

void SOC_setMCUResetIsolationDone(uint32_t value)
{
    uint32_t baseAddr;
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 6);

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr (CSL_MCU_CTRL_MMR0_CFG0_BASE);

    if (value == 1)
    {
        CSL_REG32_FINS (baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL, \
            MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z, 1);
    }
    else if (value == 0)
    {
        CSL_REG32_FINS (baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_CTRL, \
            MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z, 0);
    }

    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, 6);
}

void SOC_waitMainDomainReset(void)
{
    uint32_t baseAddr;
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 6);

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);

    while (CSL_REG32_FEXT (baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_STAT, \
                MCU_CTRL_MMR_CFG0_RST_STAT_MAIN_RESETSTATZ) != 0);

    while (CSL_REG32_FEXT (baseAddr + CSL_MCU_CTRL_MMR_CFG0_RST_STAT, \
                MCU_CTRL_MMR_CFG0_RST_STAT_MAIN_RESETSTATZ) != 1);

    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MCU, 6);
}

void SOC_setFSSCtrlFlashBootSize(void)
{
    uint32_t baseAddr;

    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 1U);

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_CTRL_MMR0_CFG0_BASE);

    /* Selects the size of the boot block to be used for the OSPI flash
     * interface. Default value is 1'b0 - S0_BOOT_SIZE_64MB for the MMR
     * register. Set 1'b1 - S0_BOOT_SIZE_128MB to update the value.
     */
    if(CSL_REG32_FEXT(baseAddr + CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL, \
                      MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SIZE) != 1U)
    {
        CSL_REG32_FINS(baseAddr + CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL, \
                       MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SIZE, 1U);
    }

    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 1U);
}
