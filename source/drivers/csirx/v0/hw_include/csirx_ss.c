/*
 *   Copyright (c) Texas Instruments Incorporated 2018-25
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
 *  \file     csirx_ss.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of CSI Rx SS.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/csl_csirx.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_csirxGetRevisionId(const CSL_csi_rx_ifRegs *ifRegisters,
                            CSL_CsirxRevisionId *revId)
{
    uint32_t regVal;

    regVal           = CSL_REG32_RD(&ifRegisters->CSIRX_ID);
    revId->minor     = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_MINREV);
    revId->custom    = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_CUSTOM);
    revId->major     = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_MAJREV);
    revId->rtlRev    = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_RTLVER);
    revId->function  = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_FUNC);
    revId->bu        = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_BU);
    revId->scheme    = CSL_REG32_FEXT(&regVal, CSI_RX_IF_CSIRX_ID_SCHEME);
}

int32_t CSL_csirxEnableVP(CSL_csi_rx_ifRegs *ifRegisters,
                       uint32_t instance, uint32_t enable)
{
    int32_t retVal = CSL_PASS;
    uint32_t option;
    volatile uint32_t *regAddr;

    if (TRUE == enable)
    {
        option = 1U;
    }
    else
    {
        option = 0U;
    }
    if (instance == (uint32_t)CSL_CSIRX_VP_INSTANCE_0)
    {
        regAddr = &ifRegisters->VP0;
    }
    else if (instance == (uint32_t)CSL_CSIRX_VP_INSTANCE_1)
    {
        regAddr = &ifRegisters->VP1;
    }
    else
    {
        retVal = CSL_EFAIL;
    }
    if (retVal == CSL_PASS)
    {
        /* Register offsets for all VP are same */
        CSL_REG32_FINS(regAddr, CSI_RX_IF_VP0_EN_CFG, option);
    }

    return retVal;
}

int32_t CSL_csirxConfigVP(CSL_csi_rx_ifRegs *ifRegisters,
                          const CSL_CsirxVPConfig* config)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal = 0U;
    volatile uint32_t *regAddr;

    if (config->instance == (uint32_t)CSL_CSIRX_VP_INSTANCE_0)
    {
        regAddr = &ifRegisters->VP0;
    }
    else if (config->instance == (uint32_t)CSL_CSIRX_VP_INSTANCE_1)
    {
        regAddr = &ifRegisters->VP1;
    }
    else
    {
        retVal = CSL_EFAIL;
    }
    if (retVal == CSL_PASS)
    {
        CSL_REG32_FINS(&regVal, CSI_RX_IF_VP0_IH_CFG, config->inHeight);
        CSL_REG32_FINS(&regVal, CSI_RX_IF_VP0_IW_CFG, config->inWidth);
        CSL_REG32_WR(regAddr, regVal);
    }

    return retVal;
}

void CSL_csirxAssertPixelIfReset(CSL_csi_rx_ifRegs *ifRegisters,
                                 uint32_t assert_stat)
{
    uint32_t option;

    if (TRUE == assert_stat)
    {
        option = 0U;
    }
    else
    {
        option = 1U;
    }
    CSL_REG32_FINS(&ifRegisters->CNTL,
                  CSI_RX_IF_CNTL_PIXEL_RESET,
                  option);
}

int32_t CSL_csirxEnableDMA(CSL_csi_rx_ifRegs *ifRegisters,
                           uint32_t threadNum,
                           uint32_t enable)
{
    int32_t retVal = CSL_PASS;
    uint32_t option;

    if (threadNum < CSL_CSIRX_PSI_L_THREAD_NUM_MAX)
    {
        if (TRUE == enable)
        {
            option = 1U;
        }
        else
        {
            option = 0U;
        }
        /* Register offsets for all VP are same */
        CSL_REG32_FINS(&ifRegisters->CNTX_CNTL[threadNum].DMACNTX,
                      CSI_RX_IF_CNTX_CNTL_DMACNTX_EN_CFG,
                      option);
    }
    else
    {
        retVal =  CSL_EFAIL;
    }

    return retVal;
}

int32_t CSL_csirxConfigDMA(CSL_csi_rx_ifRegs *ifRegisters,
                           const CSL_CsirxDMAConfig* config)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal = 0U;

    if (config->chNum < CSL_CSIRX_PSI_L_THREAD_NUM_MAX)
    {
        /* Configure DMA Channel Context */
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_VIRTCH_CFG,
                       config->virtCh);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_DATTYP_CFG,
                       config->dataType);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_PCK12_CFG,
                       config->pck12CfgEnable);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_SIZE_CFG,
                       config->dataSizeShift);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_DUAL_PCK_CFG,
                       config->dualPkgEnable);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_DMACNTX_YUV422_MODE_CFG,
                       config->yuv422Mode);
        CSL_REG32_WR(&ifRegisters->CNTX_CNTL[config->chNum].DMACNTX, regVal);
        /* Configure PSI Configuration Register0 */
        regVal = 0U;
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_PSI_CFG0_SRC_TAG,
                       config->srcTag);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_PSI_CFG0_DST_TAG,
                       config->dstTag);
        CSL_REG32_WR(&ifRegisters->CNTX_CNTL[config->chNum].PSI_CFG0, regVal);
        /* Configure PSI Configuration Register1 */
        regVal = 0U;
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PKT_TYPE,
                       config->pktType);
        CSL_REG32_FINS(&regVal,
                       CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PS_FLAGS,
                       config->psFlags);
        CSL_REG32_WR(&ifRegisters->CNTX_CNTL[config->chNum].PSI_CFG1, regVal);
    }
    else
    {
        retVal =  CSL_EFAIL;
    }

    return retVal;
}
