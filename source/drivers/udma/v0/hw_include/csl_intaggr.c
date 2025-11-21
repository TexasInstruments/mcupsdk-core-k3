/**
 * @file  csl_intaggr.c
 *
 * @brief
 *  C implementation file for the INTAGGR module CSL-FL.
 *
 *  Contains the different control command and status query functions definitions
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2016-2019, Texas Instruments, Inc.
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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <drivers/udma/v0/hw_include/csl_intaggr.h>

/* Static functions */
static bool CSL_intaggrIsValidStatusBitNum( const CSL_IntaggrCfg *pCfg, uint32_t statusBitNum );

static bool CSL_intaggrIsValidStatusBitNum( const CSL_IntaggrCfg *pCfg, uint32_t statusBitNum )
{
    bool bRetVal;
    uint32_t localStatusBitNum = statusBitNum;

    localStatusBitNum &= ~CSL_INTAGGR_INTR_MODE_FLAG;   /* Remove intr mode flag */
    if( localStatusBitNum < (pCfg->virtIntrCnt << 6U) )
    {
        bRetVal = (bool)true;
    }
    else
    {
        bRetVal = (bool)false;
    }
    return bRetVal;
}

/* API functions */

void CSL_intaggrGetCfg( CSL_IntaggrCfg *pCfg )
{
    uint64_t regVal;

    regVal = CSL_REG64_RD( &pCfg->pCfgRegs->INTCAP );
    pCfg->srcEventCnt       = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_INTCAP_SEVT_CNT );
    pCfg->virtIntrCnt       = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_INTCAP_VINTR_CNT );
    regVal = CSL_REG64_RD( &pCfg->pCfgRegs->AUXCAP );
    pCfg->localEventCnt     = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_AUXCAP_LEVI_CNT );
    pCfg->globalEventCnt    = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_AUXCAP_GEVI_CNT );
    pCfg->mcastEventCnt     = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_AUXCAP_MEVI_CNT );
#ifdef CSL_INTAGGR_CFG_AUXCAP_UNMAP_CNT_MASK
    pCfg->unmapEventCnt     = (uint32_t)CSL_FEXT( regVal, INTAGGR_CFG_AUXCAP_UNMAP_CNT );
#else
    pCfg->unmapEventCnt     = 0U;
#endif
}

int32_t CSL_intaggrMapEventToLocalEvent( CSL_IntaggrCfg *pCfg, uint32_t globalEventIdx, uint32_t localEventIdx, CSL_IntaggrEventDetectMode localEventDetectMode )
{
    int32_t  retVal;
    uint64_t regVal;

    if( (pCfg->pL2gRegs == NULL) || (pCfg->localEventCnt == 0U) )
    {
        retVal = CSL_EFAIL;    /* INTAGGR does not support this feature */
    }
    else if( (localEventIdx >= pCfg->localEventCnt)     ||
             (localEventDetectMode >= CSL_INTAGGR_EVT_DETECT_MODE_INVALID) )
    {
        retVal = CSL_EBADARGS;    /* Invalid localEventIdx or localEventDetectMode parameter */
    }
    else
    {
        regVal = CSL_FMK( INTAGGR_L2G_LEVI_MAP_MODE, (uint64_t)localEventDetectMode )   |
                 CSL_FMK( INTAGGR_L2G_LEVI_MAP_GEVIDX, (uint64_t)globalEventIdx );
        CSL_REG64_WR( &pCfg->pL2gRegs->LEVI[localEventIdx].MAP, regVal );
        retVal = CSL_PASS;
    }
    return retVal;
}

int32_t CSL_intaggrSetIntrEnable( CSL_IntaggrCfg *pCfg, uint32_t statusBitNum, bool bEnable )
{
    int32_t  retVal = CSL_EFAIL;
    uint64_t regVal;
    uint32_t regNum, bitNum;

    if( CSL_intaggrIsValidStatusBitNum(pCfg, statusBitNum) )
    {
        regNum = statusBitNum >> 6U;
        bitNum = statusBitNum & (uint32_t)0x003FU;
        if( bEnable == (bool)true )
        {
            regVal = CSL_REG64_RD( &pCfg->pIntrRegs->VINT[regNum].ENABLE_SET );
            regVal |= (((uint64_t)1U) << bitNum);
            CSL_REG64_WR( &pCfg->pIntrRegs->VINT[regNum].ENABLE_SET, regVal );
        }
        else
        {
            regVal = (((uint64_t)1U) << bitNum);
            CSL_REG64_WR( &pCfg->pIntrRegs->VINT[regNum].ENABLE_CLEAR, regVal );
        }
        retVal = CSL_PASS;
    }
    return retVal;
}

bool CSL_intaggrIsIntrPending( const CSL_IntaggrCfg *pCfg, uint32_t statusBitNum, bool bMaskedStatus )
{
    bool     retVal = (bool)false;
    uint64_t regVal;
    uint32_t regNum, bitNum;

    if( CSL_intaggrIsValidStatusBitNum(pCfg, statusBitNum) )
    {
        regNum = statusBitNum >> 6U;
        bitNum = statusBitNum & (uint32_t)0x003FU;
        if( bMaskedStatus == (bool)true )
        {
            regVal = CSL_REG64_RD( &pCfg->pIntrRegs->VINT[regNum].STATUSM );
        }
        else
        {
#ifdef CSL_INTAGGR_INTR_VINT_STATUS_SET_STATUS_MASK
            regVal = CSL_REG64_RD( &pCfg->pIntrRegs->VINT[regNum].STATUS_SET );
#else
            regVal = CSL_REG64_RD( &pCfg->pIntrRegs->VINT[regNum].STATUS );
#endif
        }
        if( (regVal & (((uint64_t)1U) << bitNum)) == 0U )
        {
            retVal = (bool)false; /* Interrupt is not pending */
        }
        else
        {
            retVal = (bool)true;  /* Interrupt is pending */
        }
    }
    return retVal;
}

int32_t CSL_intaggrClrIntr( CSL_IntaggrCfg *pCfg, uint32_t statusBitNum )
{
    int32_t  retVal = CSL_EFAIL;
    uint64_t regVal;
    uint32_t regNum, bitNum;

    if( CSL_intaggrIsValidStatusBitNum(pCfg, statusBitNum) )
    {
        regNum = statusBitNum >> 6U;
        bitNum = statusBitNum & (uint32_t)0x003FU;
        regVal = (((uint64_t)1U) << bitNum);
#ifdef CSL_INTAGGR_INTR_VINT_STATUS_CLEAR_STATUS_MASK
        CSL_REG64_WR( &pCfg->pIntrRegs->VINT[regNum].STATUS_CLEAR, regVal );
#else
        CSL_REG64_WR( &pCfg->pIntrRegs->VINT[regNum].STATUS, regVal );
#endif
        retVal = CSL_PASS;
    }
    return retVal;
}
