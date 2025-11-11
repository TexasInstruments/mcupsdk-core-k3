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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/pinmux.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/CpuIdP.h>
#include <drivers/scmi.h>
#include <drivers/psci.h>
#include <kernel/nortos/dpl/a53/common_armv8.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* PSC (Power Sleep Controller) timeout */
#define PSC_TIMEOUT                 (1000U)

/* PSC (Power Sleep Controller) Domain enable */
#define PSC_MODSTATE_ENABLE         (0x3U)

/* ========================================================================== */
/*                       Structure Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SOC_moduleClockEnable(uint32_t moduleId, uint32_t enable)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t pstate;
    uint32_t flags = 0U;
    SCMI_Handle handle = SCMI_getHandle(SCMI_getInitDriverIndex());

    if(handle != NULL)
    {
        /* Get the module state. No need to change the module state if it
         * is already in the required state.
         */
        status = SCMI_powerDomainStateGet(handle, moduleId, &pstate);

        if(status == SystemP_SUCCESS)
        {
            if((pstate == SCMI_PWD_POWER_STATE_OFF) && (enable == 1U))
            {
                status = SCMI_powerDomainStateSet(handle, moduleId,
                                      flags, SCMI_PWD_POWER_STATE_ON);
            }
            else if((pstate == SCMI_PWD_POWER_STATE_ON) && (enable == 0U))
            {
                status = SCMI_powerDomainStateSet(handle, moduleId,
                                      flags, SCMI_PWD_POWER_STATE_OFF);
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SOC_moduleSetClockFrequency(uint32_t moduleId, uint32_t clkId, uint64_t clkRate)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t clockState = 0U;
    uint64_t clkfreq = clkRate;
    uint64_t setClkFreq = 0U;
    uint32_t numPosParents;
    uint32_t originParent;
    uint32_t possibleParents[SCMI_CLK_POSSIBLE_PARENTS_MASK];
    uint32_t moduleClockParentChanged = 0U;
    uint32_t foundParent = 0U;

    SCMI_Handle handle = SCMI_getHandle(SCMI_getInitDriverIndex());

    if(handle != NULL)
    {
        /* Check if the clock is enabled or not */
        status = SCMI_clockConfigGet(handle, clkId, &clockState);

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_clockGetPossibleParents(handle, clkId, &numPosParents,
                                                  possibleParents);
        }

        if(status == SystemP_SUCCESS)
        {
            if(numPosParents > 1U)
            {
                /* Store the original parent */
                status = SCMI_clockParentGet(handle, clkId, &originParent);
            }
        }

        if (status == SystemP_SUCCESS)
        {
            if(clkRate == 0xFFU)
            {
                /* Get module clock if the clock is not provided by the
                 * application.
                 */
                status = SCMI_clockRateGet(handle, clkId, &clkfreq);
            }
        }

        if(status == SystemP_SUCCESS)
        {
            foundParent = 0U;

            /* For each parent query and check if frequency can be set
             * at that parent.
             */
            for(uint32_t count = 0U; (count < numPosParents) && \
               (status == SystemP_SUCCESS); count++)
            {
                if(numPosParents > 1U)
                {
                    status = SCMI_clockParentSet(handle, clkId, \
                                                possibleParents[count]);
                    if(status == SystemP_SUCCESS)
                    {
                        moduleClockParentChanged = 1U;
                    }
                }

                if(status == SystemP_SUCCESS)
                {
                    /* Set the clock at the desired frequency at the currently selected parent */
                    status = SCMI_clockRateSet(handle, clkId, clkfreq);
                }

                if(status == SystemP_SUCCESS)
                {
                    status = SCMI_clockRateGet(handle, clkId, &setClkFreq);
                }

                if(status == SystemP_SUCCESS)
                {
                    if((setClkFreq == clkfreq) || \
                       (setClkFreq > (clkfreq - 5U)) || \
                       (setClkFreq < (clkfreq + 5U)))
                    {
                        /* yes, found a parent at which this frequency
                         * can be set */
                        foundParent = 1U;
                        break;
                    }
                }
            }
        }

        if (status == SystemP_SUCCESS)
        {
            if(foundParent != 1U)
            {
                /* Unable to set the parent */
                status = SystemP_FAILURE;
            }
        }

        if(status == SystemP_SUCCESS)
        {
            if(clockState != SCMI_CLK_CONFIG_SET_ENABLE)
            {
                status = SCMI_clockConfigSet(handle, clkId, \
                                             SCMI_CLK_CONFIG_SET_ENABLE);
            }
        }

        if(status != SystemP_SUCCESS)
        {
            if(moduleClockParentChanged == 1U)
            {
                status = SCMI_clockParentSet(handle, clkId, originParent);
            }
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

const char *SOC_getCoreName(uint16_t coreId)
{
    static const char *coreIdNames[CSL_CORE_ID_MAX+1U] = {
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
    uint32_t cpuClockId = 0U;
    uint64_t cpuClockRate = 0U;

    /* Get self CPU Clock ID */
    switch(Armv8_getCoreId())
        {
        case 0:
            cpuClockId = AM62LX_DEV_COMPUTE_CLUSTER0_A53_0_A53_CORE0_ARM_CLK_CLK;
            break;
        case 1:
            cpuClockId = AM62LX_DEV_COMPUTE_CLUSTER0_A53_1_A53_CORE1_ARM_CLK_CLK;
            break;
        default:
            break;
    }

    SCMI_Handle handle = SCMI_getHandle(SCMI_getInitDriverIndex());

    if(handle != NULL)
    {
        (void) SCMI_clockRateGet(handle, cpuClockId, &cpuClockRate);
    }

    return cpuClockRate;
}

void SOC_controlModuleLockMMR(uint32_t domainId, uint32_t partition)
{

    /* Do nothing */
    return;
}

void SOC_controlModuleUnlockMMR(uint32_t domainId, uint32_t partition)
{

    /* Do nothing */
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
                  CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN) & 0x1FFU) | (1U << epwmInstance)));
        }
        else
        {
            /* Disable Time base clock in CTRL MMR */
            CSL_REG32_WR(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE + CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN,
                ((CSL_REG32_RD(CSL_CTRL_MMR0_IP_CTRL_MMRS_BASE +
                  CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN) & 0x1FFU) & ~(1U << epwmInstance)));
        }

        /* CTRL_MMR0 registers are not locked again */
    }
}

void SOC_setDevStat(uint32_t bootMode)
{

    /* Change bootmode by setting devstat register */
    CSL_REG32_WR(CSL_WKUP_CTRL_MMR0_BOOT_MMRS_BASE + CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT, bootMode);

    return;
}

int32_t SOC_moduleGetClockFrequency(uint32_t moduleId, uint32_t clkId, uint64_t *clkRate)
{
    int32_t status = SystemP_SUCCESS;

    SCMI_Handle handle = SCMI_getHandle(SCMI_getInitDriverIndex());

    if(handle != NULL)
    {
        status = SCMI_clockRateGet(handle, clkId, clkRate);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

void SOC_generateSwWarmResetMainDomain(void)
{
    PSCI_Handle handle = PSCI_getHandle(PSCI_getInitDriverIndex());

    if(handle != NULL)
    {
        /* Reset of the system */
        (void) PSCI_systemReset(handle);
    }
}

uint32_t SOC_getWarmResetCauseMainDomain(void)
{
    uint32_t     resetCause = 0U;

    /* Read the Reset Cause Register bits */
    resetCause = CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_DEVICE_MANAGEMENT_BASE  + CSL_WKUP_CTRL_MMR_CFG5_RST_SRC);

    return resetCause;
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
