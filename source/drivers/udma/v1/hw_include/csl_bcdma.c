/**
 * @file  csl_bcdma.c
 *
 * @brief
 *  C implementation file for the BCDMA module CSL-FL.
 *
 *  Contains the different control command and status query functions definitions
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2019-2020, Texas Instruments, Inc.
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
#include <string.h>
#include <drivers/udma/v1/hw_include/csl_bcdma.h>

#define CSL_BCDMA_TEARDOWN_COMPLETE_WAIT_MAX_CNT    ((uint32_t) 128U)

/* ----------------------------------------------------------------------------
 *  Static internal functions
 * ----------------------------------------------------------------------------
 */
static int32_t CSL_bcdmaDoChanOp( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanOp chanOp, uint32_t chanIdx, void *pOpData );
static bool    CSL_bcdmaChanOpIsChanEnabled( CSL_BcdmaCfg *pCfg, uint32_t chanIdx );
static int32_t CSL_bcdmaChanOpCfgChan( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpSetChanEnable( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, uint32_t bEnable );
static int32_t CSL_bcdmaChanOpSetChanPause( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, bool bPause );
static int32_t CSL_bcdmaChanOpTeardownChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpTriggerChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx );
static int32_t CSL_bcdmaChanOpGetChanRT( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpSetChanRT( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpGetChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpDecChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpSetBurstSize( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData );
static int32_t CSL_bcdmaChanOpClearError( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx );

static int32_t CSL_bcdmaDoChanOp( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanOp chanOp, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_EFAIL;

    if( pCfg == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        CSL_BcdmaChanType chanType = 0U;
        /*
         * Call CSL_bcdmaGetCfg to populate the bcdma cfg structure if it appears
         * the caller has not yet done so.
         */
        if( (pCfg->bcChanCnt == (uint32_t)0U) || (pCfg->splitTxChanCnt == (uint32_t)0U) || (pCfg->splitRxChanCnt == (uint32_t)0U) ) {
            CSL_bcdmaGetCfg( pCfg );
        }

        retVal = CSL_bcdmaChanOp( pCfg, chanOp, chanType, chanIdx, pOpData );
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpCfgChan( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        uint32_t regVal;
        switch( chanType )
        {
            case CSL_BCDMA_CHAN_TYPE_BLOCK_COPY:
                {
                    CSL_BcdmaChanCfg *pChanCfg = (CSL_BcdmaChanCfg *)pOpData;
                    if( (pChanCfg->burstSize > CSL_BCDMA_CHAN_BURST_SIZE_128_BYTES)   ||    /* Block-copy supports 32, 64, and 128-byte bursts */
                        (pChanCfg->busPriority > ((uint32_t)7U) )                     ||
                        (pChanCfg->dmaPriority > ((uint32_t)3U) )
                      )
                    {
                        retVal = CSL_EINVALID_PARAMS;
                    }
                    else
                    {
                        uint32_t noTeardownCompletePkt = pChanCfg->noTDPkt;
                        /* CFG */
                        regVal = CSL_REG32_RD( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR, pChanCfg->pauseOnError);
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, pChanCfg->burstSize );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE, pChanCfg->chanType );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_TDTYPE, pChanCfg->tdType );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_NOTDPKT, noTeardownCompletePkt );
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG, regVal );
                        /* PRI_CTRL */
                        regVal = CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY, pChanCfg->busPriority )    |
                                 CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID, pChanCfg->busOrderId );
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].PRI_CTRL, regVal );
                        /* TST_SCHED */
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].TST_SCHED, CSL_FMK(BCDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY, pChanCfg->dmaPriority) );
                    }
                }
                break;
            case CSL_BCDMA_CHAN_TYPE_SPLIT_TX:
                {
                    CSL_BcdmaChanCfg *pChanCfg = (CSL_BcdmaChanCfg *)pOpData;
                    if( (pChanCfg->burstSize > CSL_BCDMA_CHAN_BURST_SIZE_64_BYTES)    ||    /* Split-tx supports 32, and 64-byte bursts */
                        (pChanCfg->busPriority > ((uint32_t)7U) )                     ||
                        (pChanCfg->dmaPriority > ((uint32_t)3U) )
                      )
                    {
                        retVal = CSL_EINVALID_PARAMS;
                    }
                    else
                    {
                        uint32_t noTeardownCompletePkt = pChanCfg->noTDPkt;
                        /* CFG */
                        regVal = CSL_REG32_RD( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR, pChanCfg->pauseOnError);
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, pChanCfg->burstSize );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE, pChanCfg->chanType );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_TDTYPE, pChanCfg->tdType );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_NOTDPKT, noTeardownCompletePkt );
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG, regVal );
                        /* PRI_CTRL */
                        regVal = CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY, pChanCfg->busPriority )    |
                                 CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID, pChanCfg->busOrderId );
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].PRI_CTRL, regVal );
                        /* TST_SCHED */
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].TST_SCHED, CSL_FMK(BCDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY, pChanCfg->dmaPriority) );
                    }
                }
                break;
            case CSL_BCDMA_CHAN_TYPE_SPLIT_RX:
                {
                    CSL_BcdmaChanCfg *pChanCfg = (CSL_BcdmaChanCfg *)pOpData;
                    if( (pChanCfg->burstSize > CSL_BCDMA_CHAN_BURST_SIZE_64_BYTES)    ||     /* Split-rx supports 32, and 64-byte bursts */
                        (pChanCfg->busPriority > ((uint32_t)7U) )                     ||
                        (pChanCfg->dmaPriority > ((uint32_t)3U) )
                      )
                    {
                        retVal = CSL_EINVALID_PARAMS;
                    }
                    else
                    {
                        /* CFG */
                        regVal = CSL_REG32_RD( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG );
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR, pChanCfg->pauseOnError);
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, pChanCfg->burstSize );
#ifdef CSL_BCDMA_RXCCFG_CHAN_RCFG_IGNORE_LONG_MASK
                        CSL_FINS( regVal, BCDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG, pChanCfg->rxIgnoreLong ? (uint32_t)1U : (uint32_t)0U );
#endif
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG, regVal );
                        /* PRI_CTRL */
                        regVal = CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY, pChanCfg->busPriority )    |
                                 CSL_FMK( BCDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID, pChanCfg->busOrderId );
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].PRI_CTRL, regVal );
                        /* TST_SCHED */
                        CSL_REG32_WR( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].TST_SCHED, CSL_FMK(BCDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY, pChanCfg->dmaPriority) );
                    }
                }
                break;
            default:
                retVal = CSL_EBADARGS;
                break;
        }
    }
    return retVal;
}

static bool CSL_bcdmaChanOpIsChanEnabled( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    uint32_t regVal;

    regVal = CSL_REG32_FEXT( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, BCDMA_CHRT_V2_CHAN_CTL_EN );

    return ((regVal == 1U) ? (bool)true : (bool)false);
}

static int32_t CSL_bcdmaChanOpSetChanEnable( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, uint32_t bEnable )
{
    int32_t retVal = CSL_PASS;

    CSL_REG32_FINS(&pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, BCDMA_CHRT_V2_CHAN_CTL_EN, bEnable);

    return retVal;
}

static int32_t CSL_bcdmaChanOpSetChanPause( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, bool bPause )
{
    int32_t retVal = CSL_PASS;

    if( CSL_bcdmaChanOpIsChanEnabled( pCfg, chanIdx ) == (bool)false )
    {
        /* Channel must be enabled in order to be paused or resumed */
        retVal = CSL_EFAIL;
    }
    else
    {
        CSL_REG32_FINS( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, BCDMA_CHRT_V2_CHAN_CTL_PAUSE, ((bPause==(bool)false) ? (uint32_t)0U : (uint32_t)1U) );
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpTeardownChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData )
{
    int32_t  retVal = CSL_PASS;

    if( CSL_bcdmaChanOpIsChanEnabled( pCfg, chanIdx ) == (bool)false )
    {
        /* Channel can be torn down only when it is enabled */
        retVal = CSL_EFAIL;
    }
    else
    {
        uint32_t regVal;
        uint32_t force = (uint32_t)0U, wait = (uint32_t)0U;

        if( pOpData != NULL )
        {
            CSL_BcdmaTeardownOpts *pTdOpts = (CSL_BcdmaTeardownOpts *)pOpData;
            force = pTdOpts->force;
            wait  = pTdOpts->wait;
        }

        regVal = CSL_REG32_RD( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL );
        CSL_FINS( regVal, BCDMA_CHRT_V2_CHAN_CTL_TDOWN, (uint32_t)1U );
        CSL_FINS( regVal, BCDMA_CHRT_V2_CHAN_CTL_FTDOWN, (force==0U) ? (uint32_t)0U : (uint32_t)1U  );
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, regVal );

        if(wait != 0U)
        {
            uint32_t retryCnt = CSL_BCDMA_TEARDOWN_COMPLETE_WAIT_MAX_CNT;
            /* The channel's enable bit is cleared once teardown is complete */
            while( (CSL_bcdmaChanOpIsChanEnabled( pCfg, chanIdx ) == (bool)true) && (retryCnt != (uint32_t)0U) )
            {
                retryCnt--;
            }
            if( retryCnt == (uint32_t)0U ) {
                retVal = CSL_EFAIL;
            }
        }
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpTriggerChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal = CSL_PASS;

    CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chanIdx].SWTRIG, CSL_FMK(BCDMA_CHRT_V2_CHAN_SWTRIG_TRIGGER, (uint32_t)1U));

    return retVal;
}

static int32_t CSL_bcdmaChanOpGetChanRT( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        uint32_t val;
        val = CSL_REG32_RD( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL );

        if( retVal == CSL_PASS )
        {
            CSL_BcdmaRT *pRT = (CSL_BcdmaRT *)pOpData;
            pRT->enable         = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_EN );
            pRT->teardown       = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_TDOWN );
            pRT->forcedTeardown = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_FTDOWN );
            pRT->pause          = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_PAUSE );
            pRT->error          = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_ERROR );
            pRT->starvation = CSL_FEXT( val, BCDMA_CHRT_V2_CHAN_CTL_STARVATION );
        }
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpSetChanRT( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal;
    bool pairComp;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        uint32_t val;
        regVal = CSL_REG32_RD(&pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL);
        pairComp = CSL_FEXT(regVal, BCDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE) ;
        CSL_BcdmaRT *pRT = (CSL_BcdmaRT *)pOpData;
        val =   CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_EN,           pRT->enable)         |
                CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_TDOWN,        pRT->teardown)       |
                CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_FTDOWN,       pRT->forcedTeardown) |
                CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_PAUSE,        pRT->pause);
        switch( chanType )
        {
            case CSL_BCDMA_CHAN_TYPE_BLOCK_COPY:
                CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, val );
                break;
            case CSL_BCDMA_CHAN_TYPE_SPLIT_TX:
            case CSL_BCDMA_CHAN_TYPE_SPLIT_RX:
                if(!pairComp)
                {
                   CSL_bcdmaSetChanAutoPair(pCfg,chanIdx,1U);
                   regVal = CSL_REG32_RD(&pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL);
                }
                CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, regVal | val);
                break;
            default:
                retVal = CSL_EBADARGS;
                break;
        }
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpGetChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        CSL_BcdmaChanStats *pChanStats = (CSL_BcdmaChanStats *)pOpData;

        pChanStats->packetCnt        = CSL_REG32_RD( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].PCNT );
        pChanStats->completedByteCnt = CSL_REG32_RD( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].BCNT );
        pChanStats->startedByteCnt = CSL_REG32_RD( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].SBCNT );
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpDecChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        CSL_BcdmaChanStats *pChanStats = (CSL_BcdmaChanStats *)pOpData;
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].PCNT,   pChanStats->packetCnt );
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].BCNT,   pChanStats->completedByteCnt );
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].SBCNT,  pChanStats->startedByteCnt );
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpSetBurstSize( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( pOpData == NULL )
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        CSL_BcdmaChanBurstSize burstSize = *(CSL_BcdmaChanBurstSize *)pOpData;
        switch( chanType )
        {
            case CSL_BCDMA_CHAN_TYPE_BLOCK_COPY:
                if( burstSize > CSL_BCDMA_CHAN_BURST_SIZE_128_BYTES )   /* Block-copy supports 32, 64, and 128-byte bursts */
                {
                    retVal = CSL_EINVALID_PARAMS;
                }
                else
                {
                    CSL_REG32_FINS( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG, BCDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, burstSize );
                }
                break;
            case CSL_BCDMA_CHAN_TYPE_SPLIT_TX:
            case CSL_BCDMA_CHAN_TYPE_SPLIT_RX:
                if( burstSize > CSL_BCDMA_CHAN_BURST_SIZE_64_BYTES )    /* Split-tx supports 32, and 64-byte bursts */
                {
                    retVal = CSL_EINVALID_PARAMS;
                }
                else
                {
                    CSL_REG32_FINS( &pCfg->pBcChanCfgv2Regs->CHAN[chanIdx].CFG, BCDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, burstSize );
                }
                break;
            default:
                retVal = CSL_EBADARGS;
                break;
        }
    }
    return retVal;
}

static int32_t CSL_bcdmaChanOpClearError( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanType chanType, uint32_t chanIdx )
{
    int32_t retVal = CSL_PASS;
    CSL_REG32_FINS( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL, BCDMA_CHRT_V2_CHAN_CTL_ERROR, (uint32_t)0U );
    
    return retVal;
}

/* ----------------------------------------------------------------------------
 *  Global API functions
 * ----------------------------------------------------------------------------
 */
int32_t CSL_bcdmaChanOp( CSL_BcdmaCfg *pCfg, CSL_BcdmaChanOp chanOp, CSL_BcdmaChanType chanType, uint32_t chanIdx, void *pOpData )
{
    int32_t retVal = CSL_PASS;

    if( ( pCfg == NULL )                                    ||
        ( chanType > CSL_BCDMA_CHAN_TYPE_SPLIT_RX ))
    {
        retVal = CSL_EBADARGS;
    }
    else
    {
        switch(chanOp )
        {
            case CSL_BCDMA_CHAN_OP_CONFIG:
                retVal = CSL_bcdmaChanOpCfgChan( pCfg, chanType, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_ENABLE:
                retVal = CSL_bcdmaChanOpSetChanEnable( pCfg, chanIdx, (bool)true );
                break;
            case CSL_BCDMA_CHAN_OP_DISABLE:
                retVal = CSL_bcdmaChanOpSetChanEnable( pCfg, chanIdx, (bool)false );
                break;
            case CSL_BCDMA_CHAN_OP_PAUSE:
                retVal = CSL_bcdmaChanOpSetChanPause( pCfg, chanIdx, (bool)true );
                break;
            case CSL_BCDMA_CHAN_OP_RESUME:
                retVal = CSL_bcdmaChanOpSetChanPause( pCfg, chanIdx, (bool)false );
                break;
            case CSL_BCDMA_CHAN_OP_TEARDOWN:
                retVal = CSL_bcdmaChanOpTeardownChan( pCfg, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_TRIGGER:
                retVal = CSL_bcdmaChanOpTriggerChan( pCfg, chanIdx );
                break;
            case CSL_BCDMA_CHAN_OP_GET_RT:
                retVal = CSL_bcdmaChanOpGetChanRT( pCfg, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_SET_RT:
                retVal = CSL_bcdmaChanOpSetChanRT( pCfg, chanType, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_GET_STATS:
                retVal = CSL_bcdmaChanOpGetChanStats( pCfg, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_DEC_STATS:
                retVal = CSL_bcdmaChanOpDecChanStats( pCfg, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_SET_BURST_SIZE:
                retVal = CSL_bcdmaChanOpSetBurstSize( pCfg, chanType, chanIdx, pOpData );
                break;
            case CSL_BCDMA_CHAN_OP_CLEAR_ERROR:
                retVal = CSL_bcdmaChanOpClearError( pCfg, chanType, chanIdx );
                break;
            default:
                retVal = CSL_EBADARGS;
                break;
        }
    }
    return retVal;
}

uint32_t CSL_bcdmaGetRevision( const CSL_BcdmaCfg *pCfg )
{
    uint32_t retVal = 0U;
    if( (pCfg != NULL) && (pCfg->pGenCfgv2Regs != NULL) )
    {
       retVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->REVISION );
    }
    return retVal;
}

int32_t CSL_bcdmaGetRevisionInfo( const CSL_BcdmaCfg *pCfg, CSL_BcdmaRevision *pRev )
{
    int32_t retVal = CSL_PASS;
    if( (pCfg == NULL) || (pCfg->pGenCfgv2Regs == NULL) || (pRev == NULL) )
    {
        retVal = CSL_EFAIL;
    }
    else
    {
        uint32_t val;
        val = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->REVISION );
        pRev->modId     = CSL_FEXT( val, BCDMA_GCFG_V2_REVISION_MODID );
        pRev->revRtl    = CSL_FEXT( val, BCDMA_GCFG_V2_REVISION_REVRTL );
        pRev->revMajor  = CSL_FEXT( val, BCDMA_GCFG_V2_REVISION_REVMAJ );
        pRev->custom    = CSL_FEXT( val, BCDMA_GCFG_V2_REVISION_CUSTOM );
        pRev->revMinor  = CSL_FEXT( val, BCDMA_GCFG_V2_REVISION_REVMIN );
    }
    return retVal;
}

void CSL_bcdmaInitCfg( CSL_BcdmaCfg *pCfg )
{
    if( pCfg != NULL )
    {
        memset( (void *)pCfg, 0, sizeof(CSL_BcdmaCfg) );
    }
}

void CSL_bcdmaGetCfg( CSL_BcdmaCfg *pCfg )
{
    uint32_t regVal;
    if( ! ((pCfg == NULL) || (pCfg->pGenCfgv2Regs == NULL)) )
    {
        pCfg->cap0 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP0 );
        pCfg->cap1 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP1 );
        pCfg->cap2 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP2 );
        pCfg->cap3 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP3 ); 
        pCfg->cap4 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP4 );
        pCfg->cap5 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP5 ); 

        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP2 );
        pCfg->bcChanCnt = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP2_CHAN_CNT );
        pCfg->txChanCnt = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP2_TCHAN_CNT );
        pCfg->rxChanCnt = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP2_RCHAN_CNT );

        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP3 );
        pCfg->bcHighCapacityChanCnt = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP3_HCHAN_CNT );
        pCfg->bcUltraHighCapacityChanCnt = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP3_UCHAN_CNT );
        
        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP4 );
        pCfg->txHighCapacityChanCnt          = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP4_THCHAN_CNT );
        pCfg->txUltraHighCapacityChanCnt     = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP4_TUCHAN_CNT );
        pCfg->rxHighCapacityChanCnt          = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP4_RHCHAN_CNT );
        pCfg->rxUltraHighCapacityChanCnt     = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP4_RUCHAN_CNT );
        
        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP5 );
        pCfg->tflowCnt     = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP5_TFLOW_CNT );
        pCfg->rflowCnt     = CSL_FEXT( regVal, BCDMA_GCFG_V2_CAP5_RFLOW_CNT );
    }       
}

void CSL_bcdmaInitChanCfg( CSL_BcdmaChanCfg *pChanCfg )
{
    /*-------------------------------------------------------------------------
     *  Start by initializing all structure members to 0
     *-----------------------------------------------------------------------*/
    memset( (void *)pChanCfg, 0, sizeof(CSL_BcdmaChanCfg) );
    /*-------------------------------------------------------------------------
     *  Now initialize non-zero structure members
     *-----------------------------------------------------------------------*/
    pChanCfg->chanType        = CSL_BCDMA_CHAN_TYPE_REF_PKT_RING;
    pChanCfg->fetchWordSize   = CSL_BCDMA_FETCH_WORD_SIZE_16;
    pChanCfg->trEventNum      = CSL_BCDMA_NO_EVENT;
    pChanCfg->errEventNum     = CSL_BCDMA_NO_EVENT;
}

int32_t CSL_bcdmaChanCfg( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, const CSL_BcdmaChanCfg *pChanCfg )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_CONFIG, chanIdx, (void *)pChanCfg );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

void CSL_bcdmaSetChanAutoPair( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, uint8_t val)
{
    
    if(val != 0U)
    {
        /* Set the Autopair bit for the channel */
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL,
            CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_PAIR, 1U ));
    }
    else
    {
        /* Reset the Autopair bit for the channel */
        CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chanIdx].CTL,
            CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_PAIR, 0U ));
    }
}

int32_t CSL_bcdmaEnableChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_ENABLE, chanIdx, NULL );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaGetRT( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, CSL_BcdmaRT *pRT )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_GET_RT, chanIdx, (void *)pRT );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaSetRT( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, const CSL_BcdmaRT *pRT )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_SET_RT, chanIdx, (void *)pRT );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaDisableChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_DISABLE, chanIdx, NULL );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaTeardownChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, bool bForce, bool bWait )
{
    int32_t retVal;
    CSL_BcdmaTeardownOpts   teardownOpts;

    teardownOpts.force  = (bForce == (bool)false) ? (uint32_t)0U : (uint32_t)1U;
    teardownOpts.wait   = (bWait  == (bool)false) ? (uint32_t)0U : (uint32_t)1U;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_TEARDOWN, chanIdx, (void *)&teardownOpts );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaPauseChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_PAUSE, chanIdx, NULL );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaUnpauseChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_RESUME, chanIdx, NULL );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

int32_t CSL_bcdmaTriggerChan( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    int32_t retVal;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_TRIGGER, chanIdx, NULL );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

void CSL_bcdmaGetChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, CSL_BcdmaChanDir chanDir, CSL_BcdmaChanStats *pChanStats )
{
    CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_GET_STATS, chanIdx, (void *)pChanStats );
}

void CSL_bcdmaDecChanStats( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, CSL_BcdmaChanDir chanDir, const CSL_BcdmaChanStats *pChanStats )
{
    CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_DEC_STATS, chanIdx, (void *)pChanStats );
}

int32_t CSL_bcdmaChanSetBurstSize( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, CSL_BcdmaChanBurstSize burstSize )
{
    int32_t retVal;
    CSL_BcdmaChanBurstSize parm = burstSize;
    retVal = CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_SET_BURST_SIZE, chanIdx, (void *)&parm );
    if( retVal != CSL_PASS )
    {
        retVal = CSL_EFAIL;     /* API returns CSL_EFAIL on failure for backwards compatibility with udmap API */
    }
    return retVal;
}

void CSL_bcdmaClearChanError( CSL_BcdmaCfg *pCfg, uint32_t chanIdx )
{
    CSL_bcdmaDoChanOp( pCfg, CSL_BCDMA_CHAN_OP_CLEAR_ERROR, chanIdx, NULL );
}

void CSL_bcdmaSetPerfCtrl( CSL_BcdmaCfg *pCfg, uint32_t rxRetryTimeoutCnt )
{
    uint32_t regVal;
    regVal = CSL_FMK( BCDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT, rxRetryTimeoutCnt );
    CSL_REG32_WR( &pCfg->pGenCfgv2Regs->PERF_CTRL, regVal );
}

void CSL_bcdmaSetUtcCtrl( CSL_BcdmaCfg *pCfg, uint32_t startingThreadNum )
{
}

int32_t CSL_bcdmaRxChanSetTrEvent( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, uint32_t trEventNum )
{
    return CSL_EFAIL;
}

int32_t CSL_bcdmaTxChanSetTrEvent( CSL_BcdmaCfg *pCfg, uint32_t chanIdx, uint32_t trEventNum )
{
    return CSL_EFAIL;
}

void CSL_bcdmaCfgRxFlowIdFirewall( CSL_BcdmaCfg *pCfg, uint32_t outEvtNum )
{
}

bool CSL_bcdmaGetRxFlowIdFirewallStatus( CSL_BcdmaCfg *pCfg, CSL_BcdmaRxFlowIdFirewallStatus *pRxFlowIdFwStatus )
{
    return (bool)false;
}

int32_t CSL_bcdmaSetLocalTrig(CSL_BcdmaCfg *pCfg, uint32_t trigType, uint32_t chNum, uint32_t trigIndex, uint32_t trigger)
{
    int32_t retVal = CSL_PASS;
    uint32_t    triggerEvent = 0U;
    if(pCfg != NULL)
    {
        if(CSL_UDMAP_TR_FLAGS_TRIGGER_LOCAL0 == trigger)
        {
            CSL_FINS(triggerEvent, BCDMA_CHRT_V2_CHAN_LOCTRIG0_TRIGTYPE, trigType); /* Set local event */
            CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chNum].LOCTRIG0 , (triggerEvent | (trigIndex)));
        }
        else if(CSL_UDMAP_TR_FLAGS_TRIGGER_LOCAL1 == trigger)
        {
            CSL_FINS(triggerEvent, BCDMA_CHRT_V2_CHAN_LOCTRIG1_TRIGTYPE, trigType); /* Set local event */
            CSL_REG32_WR( &pCfg->pBcChanRtv2Regs->CHAN[chNum].LOCTRIG1 , (triggerEvent | (trigIndex)));
        }
        else
        {
            retVal = CSL_EFAIL; /* Unsupported Trigger Type*/
        }
    }
    else
    {
        retVal = CSL_EBADARGS;
    }
    return retVal;
}

int32_t CSL_bcdmaSet_TR_XY(CSL_BcdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1;
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chNum].STATIC_TR_XY, val);
       retVal = 0;
    }
    return retVal;
}

int32_t CSL_bcdmaSet_TR_Z(CSL_BcdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1;
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chNum].STATIC_TR_Z, val);
       retVal = 0;
    }
    return retVal;
}

uint32_t CSL_bcdmaGetPeerData(CSL_BcdmaCfg *pCfg, uint32_t chNum)
{
    uint32_t regVal = 0U;
    if(pCfg != NULL)
    {
       regVal = CSL_REG32_RD(&pCfg->pBcChanRtv2Regs->CHAN[chNum].PERIPH_BCNT);
    }
    return regVal;
}

int32_t CSL_bcdmaSetPeerData(CSL_BcdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1;
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chNum].PERIPH_BCNT, val);
       retVal = 0;
    }
    return retVal;
}

int32_t CSL_bcdmaIsPairComp(CSL_BcdmaCfg *pCfg, uint32_t chNum)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal;
    uint32_t pairComp = 0u;

    if(pCfg != NULL)
    {
        regVal = CSL_REG32_RD(&pCfg->pBcChanRtv2Regs->CHAN[chNum].CTL) ;
        pairComp = CSL_FEXT(regVal, BCDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE) ;
    }

    if(pairComp != 1U)
    {
        retVal = CSL_EFAIL;
    }
    return retVal;
}


