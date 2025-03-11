/*
 *   Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \file     csitx_ss.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of CSI Tx SS.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/csl_csitx.h>

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
void CSL_csitxGetRevisionId(const CSL_csi_tx_ifRegs *ifRegisters,
                            CSL_CsitxRevisionId *revId)
{
    uint32_t regVal;

    regVal           = CSL_REG32_RD(&ifRegisters->CSITX_ID);
    revId->minor     = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_MINREV);
    revId->custom    = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_CUSTOM);
    revId->major     = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_MAJREV);
    revId->rtlRev    = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_RTLVER);
    revId->function  = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_FUNC);
    revId->bu        = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_BU);
    revId->scheme    = CSL_REG32_FEXT(&regVal, CSI_TX_IF_CSITX_ID_SCHEME);
}

int32_t CSL_csitxColorbarCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                             const CSL_CsitxColorbarGenCfg *cfg)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal;

    /* Check for configuration parameters validity */
    if ((cfg->vc         > CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_MAX) &&
        (cfg->dt         > CSL_CSI_TX_IF_COLOR_CNTL_DTYPE_MAX) &&
        (cfg->width      > CSL_CSI_TX_IF_COLOR_PARAM_IW_CFG_MAX) &&
        (cfg->height     > CSL_CSI_TX_IF_COLOR_PARAM_IH_CFG_MAX) &&
        (cfg->startDelay > CSL_CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY_MAX) &&
        (cfg->lineDelay  > CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_MAX) &&
        (cfg->frmDelay   > CSL_CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY_MAX))
    {
        /* Invalid parameters values */
        retVal = CSL_EFAIL;
    }
    else
    {
        /* Program parameters with proper values */
        regVal = CSL_REG32_RD(&ifRegisters->COLOR_CNTL);
        CSL_REG32_FINS(&regVal, CSI_TX_IF_COLOR_CNTL_VCHNL, cfg->vc);
        CSL_REG32_FINS(&regVal, CSI_TX_IF_COLOR_CNTL_DTYPE, cfg->dt);
        CSL_REG32_WR(&ifRegisters->COLOR_CNTL, regVal);

        regVal = CSL_REG32_RD(&ifRegisters->COLOR_PARAM);
        CSL_REG32_FINS(&regVal, CSI_TX_IF_COLOR_PARAM_IW_CFG, cfg->width);
        CSL_REG32_FINS(&regVal, CSI_TX_IF_COLOR_PARAM_IH_CFG, cfg->height);
        CSL_REG32_WR(&ifRegisters->COLOR_PARAM, regVal);

        CSL_REG32_FINS(&ifRegisters->COLOR_START_DELAY,
                       CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY,
                       cfg->startDelay);

        CSL_REG32_FINS(&ifRegisters->COLOR_LINE_DELAY,
                       CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY,
                       cfg->lineDelay);

        CSL_REG32_FINS(&ifRegisters->COLOR_FRAME_DELAY,
                       CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY,
                       cfg->frmDelay);
    }


    return (retVal);
}

void CSL_csitxEnableColorbarGen(CSL_csi_tx_ifRegs *ifRegisters,
                                uint32_t enable)
{
    uint32_t option;

    if (TRUE == enable)
    {
        option = 1U;
    }
    else
    {
        option = 0U;
    }
    /* Register offsets for all VP are same */
    CSL_REG32_FINS(&ifRegisters->COLOR_CNTL,
                   CSI_TX_IF_COLOR_CNTL_EN,
                   option);
}

int32_t CSL_csitxRetransCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                            const CSL_CsitxRetransCfg *cfg)
{
    int32_t retVal = CSL_PASS;
    /* Below register is not available in J721e */
    /* Select re-trans pins instead of PSIL, this mux config is needed for J721S2/J784S4 */
    CSL_REG32_FINS(&ifRegisters->CONTROL1, CSI_TX_IF_CONTROL1_STRM_SEL, 1U);

    return retVal;
}

void CSL_csitxAssertPixelIfReset(CSL_csi_tx_ifRegs *ifRegisters,
                                 uint32_t assert)
{
    uint32_t option;

    if (TRUE == assert)
    {
        option = 0U;
    }
    else
    {
        option = 1U;
    }
    CSL_REG32_FINS(&ifRegisters->CONTROL1,
                   CSI_TX_IF_CONTROL1_PIXEL_RESET,
                   option);
}

void CSL_csitxGetStrmStatus(const CSL_csi_tx_ifRegs *ifRegisters,
                            CSL_CsitxStrmStatus *status)
{
    uint32_t regVal;

    /* Get the stream idle status */
    regVal            = CSL_REG32_RD(&ifRegisters->CONTROL1);
    status->strm0Idle = CSL_REG32_FEXT(&regVal,
                                       CSI_TX_IF_CONTROL1_STREAM0_IDLE);
    status->strm1Idle = CSL_REG32_FEXT(&regVal,
                                       CSI_TX_IF_CONTROL1_STREAM1_IDLE);
}

int32_t CSL_csitxFrmToFrmDelayCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                                  const uint32_t vc,
                                  const uint32_t delay)
{
    int32_t retVal = CSL_PASS;

    if ((vc > CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_MAX) &&
        (delay > CSL_CSI_TX_IF_F2F_DELAY_DELAY_MAX))
    {
        /* Invalid parameters values */
        retVal = CSL_EFAIL;
    }
    else
    {
        /* Program parameters with proper values */
        CSL_REG32_FINS(&ifRegisters->F2F_DELAY[vc],
                       CSI_TX_IF_F2F_DELAY_DELAY,
                       delay);
    }

    return (retVal);
}

int32_t CSL_csitxConfigDMA(CSL_csi_tx_ifRegs *ifRegisters,
                           const CSL_CsitxDMAConfig* cfg)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal = 0U, dtRange = 0U;

    dtRange = CSL_CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG_MAX;
    if ((cfg->chNum        < CSL_CSITX_PSI_L_THREAD_NUM_MAX) &&
        (cfg->vc           < CSL_CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG_MAX) &&
        (cfg->dt           < dtRange) &&
        (cfg->l2lDelay     < CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_MAX) &&
        (cfg->numBytesLine < CSL_CSI_TX_IF_CNTL_BYTECNT_BYTECNT_MAX))
    {
        regVal = 0U;
        /* Configure DMA Channel Context */
        CSL_REG32_FINS(&regVal,
                       CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG,
                       cfg->vc);
        CSL_REG32_FINS(&regVal,
                       CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG,
                       cfg->dt);
        CSL_REG32_FINS(&regVal,
                       CSI_TX_IF_CNTL_DMACNTX_PACK12_CFG,
                       cfg->pck12CfgEnable);
        CSL_REG32_FINS(&regVal,
                       CSI_TX_IF_CNTL_DMACNTX_SIZE_CFG,
                       cfg->dataSizeShift);
        CSL_REG32_FINS(&regVal,
                       CSI_TX_IF_CNTL_DMACNTX_YUV422_MODE_CFG,
                       cfg->yuv422Mode);
        CSL_REG32_WR(&ifRegisters->CNTL[cfg->chNum].DMACNTX, regVal);
        /* Configure Line to Line delay */
        CSL_REG32_FINS(&ifRegisters->CNTL[cfg->chNum].L2L_DELAY,
                       CSI_TX_IF_CNTL_L2L_DELAY_DELAY,
                       cfg->l2lDelay);
        /* Configure number of bytes per line */
        CSL_REG32_FINS(&ifRegisters->CNTL[cfg->chNum].BYTECNT,
                       CSI_TX_IF_CNTL_BYTECNT_BYTECNT,
                       cfg->numBytesLine);
    /* Select PSIL instead of re-trans pins, this mux is only needed for J721S2/J784S4 */
    CSL_REG32_FINS(&ifRegisters->CONTROL1, CSI_TX_IF_CONTROL1_STRM_SEL, 0U);
    }
    else
    {
        retVal =  CSL_EFAIL;
    }

    return retVal;
}
