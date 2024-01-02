/*
 *  Copyright (c) Texas Instruments Incorporated 2023
 *  All rights reserved.
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

/**
 *  \file csl_dssCommon.c
 *
 *  \brief File containing the DSS Common CSL FL APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_dss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static uint32_t CSL_dssMakeIntrEnableVal(uint32_t regVal,
                                         uint32_t intrMask,
                                         uint32_t intrEnable);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_dssModuleReset(CSL_dss_commRegs *commRegs)
{
    uint32_t regVal;

    /* Soft Reset */
    regVal = CSL_REG32_RD(&commRegs->DSS_SYSCONFIG);
    CSL_FINS(regVal,
             DSS_COMMON_DSS_SYSCONFIG_SOFTRESET,
             CSL_DSS_COMMON_DSS_SYSCONFIG_SOFTRESET_MAX);
    CSL_REG32_WR(&commRegs->DSS_SYSCONFIG, regVal);

    /* Wait for reset to complete */
    while (CSL_DSS_COMMON_DSS_SYSSTATUS_DISPC_FUNC_RESETDONE_VAL_RSTCOMP !=
            CSL_REG32_FEXT(&commRegs->DSS_SYSSTATUS,
                           DSS_COMMON_DSS_SYSSTATUS_DISPC_FUNC_RESETDONE))
    {
        /* Do nothing */
    }
}

uint32_t CSL_dssIsOldiResetDone(const CSL_dss_commRegs *commRegs)
{
    uint32_t regVal, resetDone;

    regVal = CSL_REG32_RD(&commRegs->DSS_SYSSTATUS);
    resetDone = CSL_FEXT(regVal, DSS_COMMON_DSS_SYSSTATUS_OLDI_RESETDONE);

    return resetDone;
}

void CSL_dssEnableDispcIntr(CSL_dss_commRegs *commRegs,
                            uint32_t intrMask,
                            uint32_t intrEnable)
{
    uint32_t regVal;

    /* To disable interrupt, write to IRQENABLE_CLR. To enable write to
     * IRQENABLE_SET */
    if(FALSE == intrEnable)
    {
        regVal = CSL_REG32_RD(&commRegs->DISPC_IRQENABLE_CLR);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->DISPC_IRQENABLE_CLR, regVal);
    }
    else
    {
        regVal = CSL_REG32_RD(&commRegs->DISPC_IRQENABLE_SET);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->DISPC_IRQENABLE_SET, regVal);
    }
}

void CSL_dssEnablePipeIntr(CSL_dss_commRegs *commRegs,
                           uint32_t vidPipeId,
                           uint32_t intrMask,
                           uint32_t intrEnable)
{
    uint32_t regVal;

    if(CSL_DSS_VID_PIPE_ID_VID1 == vidPipeId)
    {
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_0);
        regVal = CSL_dssMakeIntrEnableVal(regVal, intrMask, intrEnable);
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_0, regVal);
    }
    else /* CSL_DSS_VID_PIPE_ID_VIDL1 == vidPipeId */
    {
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_1);
        regVal = CSL_dssMakeIntrEnableVal(regVal, intrMask, intrEnable);
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_1, regVal);
    }
}

void CSL_dssEnableVpIntr(CSL_dss_commRegs *commRegs,
                         uint32_t portId,
                         uint32_t intrMask,
                         uint32_t intrEnable)
{
    uint32_t regVal;

    if(CSL_DSS_VP_ID_1 == portId)
    {
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_0);
        regVal = CSL_dssMakeIntrEnableVal(regVal, intrMask, intrEnable);
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_0, regVal);
    }
    else /* CSL_DSS_VP_ID_2 == portId */
    {
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_1);
        regVal = CSL_dssMakeIntrEnableVal(regVal, intrMask, intrEnable);
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_1, regVal);
    }
}

void CSL_dssClearDispcIntr(CSL_dss_commRegs *commRegs,
                           uint32_t intrMask)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&commRegs->DISPC_IRQSTATUS);
    regVal |= intrMask;
    CSL_REG32_WR(&commRegs->DISPC_IRQSTATUS, regVal);
}

void CSL_dssClearPipeIntr(CSL_dss_commRegs *commRegs,
                          uint32_t vidPipeId,
                          uint32_t intrMask)
{
    uint32_t regVal;

    if(CSL_DSS_VID_PIPE_ID_VID1 == vidPipeId)
    {
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_0);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_0, regVal);
    }
    else /* CSL_DSS_VID_PIPE_ID_VIDL1 == vidPipeId */
    {
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_1);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_1, regVal);
    }
}

void CSL_dssClearVpIntr(CSL_dss_commRegs *commRegs,
                        uint32_t portId,
                        uint32_t intrMask)
{
    uint32_t regVal;

    if(CSL_DSS_VP_ID_1 == portId)
    {
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_0);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_0, regVal);
    }
    else /* CSL_DSS_VP_ID_2 == portId */
    {
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_1);
        regVal |= intrMask;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_1, regVal);
    }
}

uint32_t CSL_dssGetDispcIntrStatus(const CSL_dss_commRegs *commRegs)
{
    uint32_t intrStatus;
    intrStatus = CSL_REG32_RD(&commRegs->DISPC_IRQSTATUS);
    return intrStatus;
}

uint32_t CSL_dssGetPipeIntrStatus(const CSL_dss_commRegs *commRegs,
                                  uint32_t vidPipeId)
{
    uint32_t intrStatus;
    if(CSL_DSS_VID_PIPE_ID_VID1 == vidPipeId)
    {
        intrStatus = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_0);
    }
    else /* CSL_DSS_VID_PIPE_ID_VIDL1 == vidPipeId */
    {
        intrStatus = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_1);
    }
    return intrStatus;
}

uint32_t CSL_dssGetVpIntrStatus(const CSL_dss_commRegs *commRegs,
                                uint32_t portId)
{
    uint32_t intrStatus;
    if(CSL_DSS_VP_ID_1 == portId)
    {
        intrStatus = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_0);
    }
    else /* CSL_DSS_VP_ID_2 == portId */
    {
        intrStatus = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_1);
    }
    return intrStatus;
}

void CSL_dssSetGlobalMflagConfig(CSL_dss_commRegs *commRegs,
                                 const CSL_DssGlobalMFlagCfg *mflagCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&commRegs->DISPC_GLOBAL_MFLAG_ATTRIBUTE);
    CSL_FINS(regVal,
             DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_START,
             mflagCfg->globalMflagStart);
    CSL_FINS(regVal,
             DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL,
             mflagCfg->globalMflagCtrl);
    CSL_REG32_WR(&commRegs->DISPC_GLOBAL_MFLAG_ATTRIBUTE, regVal);
}

void CSL_dssGlobalVpEnable(CSL_dss_commRegs *commRegs,
                           uint32_t portIdMask, uint32_t enable)
{
    uint32_t regVal, enableVal, val;

    if(TRUE == enable)
    {
        val = CSL_DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_ENABLE_VAL_ENABLE;
    }
    else
    {
        val = CSL_DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_ENABLE_VAL_DISABLE;
    }

    regVal = CSL_REG32_RD(&commRegs->DISPC_GLOBAL_OUTPUT_ENABLE);
    enableVal = CSL_FEXT(regVal, DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_ENABLE);

    if(CSL_DSS_VP_ID_1_MASK == (CSL_DSS_VP_ID_1_MASK & portIdMask))
    {
        CSL_FINSR(enableVal, CSL_DSS_VP_ID_1, CSL_DSS_VP_ID_1, val);
    }
    if(CSL_DSS_VP_ID_2_MASK == (CSL_DSS_VP_ID_2_MASK & portIdMask))
    {
        CSL_FINSR(enableVal, CSL_DSS_VP_ID_2, CSL_DSS_VP_ID_2, val);
    }

    CSL_FINS(regVal,
             DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_ENABLE,
             enableVal);
    CSL_REG32_WR(&commRegs->DISPC_GLOBAL_OUTPUT_ENABLE, regVal);
}

void CSL_dssGlobalVpGoBitEnable(CSL_dss_commRegs *commRegs,
                                uint32_t portIdMask)
{
    uint32_t regVal, enableVal;

    regVal = CSL_REG32_RD(&commRegs->DISPC_GLOBAL_OUTPUT_ENABLE);
    enableVal = CSL_FEXT(regVal, DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_GO);

    if(CSL_DSS_VP_ID_1_MASK == (CSL_DSS_VP_ID_1_MASK & portIdMask))
    {
        CSL_FINSR(enableVal, CSL_DSS_VP_ID_1, CSL_DSS_VP_ID_1, 0x1);
    }
    if(CSL_DSS_VP_ID_2_MASK == (CSL_DSS_VP_ID_2_MASK & portIdMask))
    {
        CSL_FINSR(enableVal, CSL_DSS_VP_ID_2, CSL_DSS_VP_ID_2, 0x1);
    }

    CSL_FINS(regVal,
             DSS_COMMON_DISPC_GLOBAL_OUTPUT_ENABLE_VP_GO,
             enableVal);
    CSL_REG32_WR(&commRegs->DISPC_GLOBAL_OUTPUT_ENABLE, regVal);
}

void CSL_dssSetCbaConfig(CSL_dss_commRegs *commRegs,
                         const CSL_DssCbaCfg *cbaCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&commRegs->DSS_CBA_CFG);
    CSL_FINS(regVal,
             DSS_COMMON_DSS_CBA_CFG_PRI_HI,
             cbaCfg->priHigh);
    CSL_FINS(regVal,
             DSS_COMMON_DSS_CBA_CFG_PRI_LO,
             cbaCfg->priLow);
    CSL_REG32_WR(&commRegs->DSS_CBA_CFG, regVal);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static uint32_t CSL_dssMakeIntrEnableVal(uint32_t regVal,
                                         uint32_t intrMask,
                                         uint32_t intrEnable)
{
    uint32_t tempVal = regVal;
    if(TRUE == intrEnable)
    {
        tempVal |= intrMask;
    }
    else
    {
        tempVal &= ~intrMask;
    }
    return (tempVal);
}
