/**
 * @file  csl_pktdma.c
 *
 * @brief
 *  C implementation file for the PKTDMA module CSL-FL.
 *
 *  Contains the different control command and status query functions definitions
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2025, Texas Instruments, Inc.
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
#include <string.h>
#include <stdbool.h>
#include <drivers/udma/v1/hw_include/csl_pktdma.h>

/*=============================================================================
 *  Internal definitions and functions
 *===========================================================================*/

#define CSL_PKTDMA_CHAN_PEER_REG_OFFSET_ENABLE      ((uint32_t) 8U)
#define CSL_PKTDMA_FETCH_WORD_SIZE_16               ((uint32_t) 16U)
#define CSL_PKTDMA_UNPAUSE_CHAN                     ((uint32_t) 0U)
#define CSL_PKTDMA_PAUSE_CHAN                       ((uint32_t) 1U)
#define CSL_PKTDMA_TEARDOWN_COMPLETE_WAIT_MAX_CNT   ((uint32_t) 128U)
#define CSL_PKTDMA_AUTOPAIR_MAX_TIMEOUT             ((uint32_t) 1000U)

static int32_t CSL_pktdmaSetChanEnable( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, bool bEnable );
int32_t CSL_pktdmaPauseChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, uint32_t pauseVal );
static int32_t CSL_pktdmaTriggerChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir );
void CSL_pktdmaClearChanError( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir );
static bool CSL_pktdmaIsChanEnabled( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir );
static bool CSL_pktdmaIsPairTDSet( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir );

static bool CSL_pktdmaIsChanEnabled( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir )
{
    uint32_t regVal = 0U;

    if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
    {
        regVal = CSL_REG32_FEXT( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, PKTDMA_CHRT_V2_CHAN_CTL_EN );
    }
    return ((regVal == 1U) ? (bool)true : (bool)false);
}

static bool CSL_pktdmaIsPairTDSet( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir )
{
    uint32_t regVal = 0U;

    if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
    {
        regVal = CSL_REG32_FEXT( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL );
    }
    return ((regVal == 1U) ? (bool)true : (bool)false);
}

static int32_t CSL_pktdmaSetChanEnable( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, bool bEnable )
{
    int32_t retVal = CSL_PASS;

    if(pCfg == NULL)
    {
        retVal = CSL_EFAIL;
    }
    else
    {
        if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
        {
            CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_EN,(bEnable ? (uint32_t)1 : (uint32_t)0)) );
        }
    }

    return retVal;
}

void CSL_pktdmaSetChanAutoPair( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint8_t val)
{

    if(val != 0U)
    {
        /* Set the Autopair bit for the channel */
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL,
            CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_PAIR, 1U ));
    }
    else
    {
        /* Reset the Autopair bit for the channel */
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL,
            CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_PAIR, 0U ));
    }
}

 int32_t CSL_pktdmaTeardownChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, bool bForce, bool bWait )
{
    int32_t  retVal = CSL_PASS;
    if( (pCfg == NULL) )
    {
        retVal = CSL_EFAIL;
    }
    else
    {
        /* Channel can be torn down only when it is enabled */
        if( CSL_pktdmaIsChanEnabled( pCfg, chanIdx, chanDir ) == (bool)true )
        {
            if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
            {
                CSL_REG32_FINS( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, 
                            PKTDMA_CHRT_V2_CHAN_CTL_TDOWN, (uint32_t)1U );
            }

            if( bWait == (bool)true )
            {
                uint32_t retryCnt = CSL_PKTDMA_TEARDOWN_COMPLETE_WAIT_MAX_CNT;
                if(CSL_pktdmaIsPairTDSet( pCfg, chanIdx, chanDir ) == (bool)true) 
                {
                    CSL_REG32_FINS( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL,
                                   PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL, (uint32_t)1U );
                }
                /* The channel's enable bit is cleared once teardown is complete */
                while( (CSL_pktdmaIsChanEnabled( pCfg, chanIdx, chanDir ) == (bool)true) && (retryCnt != (uint32_t)0U) )
                {
                    retryCnt--;
                }
                if( retryCnt == (uint32_t)0U ) {
                    retVal = CSL_EFAIL;
                }
            }
        }
    }
    return retVal;
}

 int32_t CSL_pktdmaPauseChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, uint32_t pauseVal )
{
    int32_t retVal = CSL_PASS;

    if(pCfg == NULL)
    {
        retVal = CSL_EFAIL;
    }
    else
    {
         /* Channel can be paused/un-paused only when it is enabled */
        if( CSL_pktdmaIsChanEnabled( pCfg, chanIdx, chanDir ) == (bool)true )
        {
            if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
            {
                CSL_REG32_FINS( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, PKTDMA_CHRT_V2_CHAN_CTL_PAUSE, pauseVal );
            }
        }
        else
        {
            retVal = CSL_EFAIL;
        }
   }
   return retVal;
}

static int32_t CSL_pktdmaTriggerChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir )
{
    return CSL_EUNSUPPORTED_CMD;
}

 void CSL_pktdmaClearChanError( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir )
{
    if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
    {
        CSL_REG32_FINS(&pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, PKTDMA_CHRT_V2_CHAN_CTL_ERROR, 0U);
    }
}

/*=============================================================================
 *  PKTDMA API functions
 *===========================================================================*/
uint32_t CSL_pktdmaGetRevision( const CSL_PktdmaCfg *pCfg )
{
    return CSL_REG32_RD( &pCfg->pGenCfgv2Regs->REVISION );
}

int32_t CSL_pktdmaGetRevisionInfo( const CSL_PktdmaCfg *pCfg, CSL_PktdmaRevision *pRev )
{
    uint32_t val;

    val = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->REVISION );
    pRev->modId     = CSL_FEXT( val, PKTDMA_GCFG_V2_REVISION_MODID );
    pRev->revRtl    = CSL_FEXT( val, PKTDMA_GCFG_V2_REVISION_REVRTL );
    pRev->revMajor  = CSL_FEXT( val, PKTDMA_GCFG_V2_REVISION_REVMAJ );
    pRev->custom    = CSL_FEXT( val, PKTDMA_GCFG_V2_REVISION_CUSTOM );
    pRev->revMinor  = CSL_FEXT( val, PKTDMA_GCFG_V2_REVISION_REVMIN );

    return CSL_PASS;
}

void CSL_pktdmaInitCfg( CSL_PktdmaCfg *pCfg )
{
    if( pCfg != NULL )
    {
        memset( (void *)pCfg, 0, sizeof(CSL_PktdmaCfg) );
    }
}

void CSL_pktdmaGetCfg( CSL_PktdmaCfg *pCfg )
{
    if( pCfg != NULL )
    {
        uint32_t regVal;
        pCfg->cap0 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP0 );
        pCfg->cap1 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP1 );
        pCfg->cap2 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP2 );
        pCfg->cap3 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP3 );
        pCfg->cap4 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP4 );
        pCfg->cap5 = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP5 );

        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP2 );
        pCfg->txChanCnt = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP2_TCHAN_CNT );
        pCfg->rxChanCnt = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP2_RCHAN_CNT );

        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP4 );
        pCfg->txHighCapacityChanCnt          = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP4_THCHAN_CNT );
        pCfg->txUltraHighCapacityChanCnt     = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP4_TUCHAN_CNT );
        pCfg->rxHighCapacityChanCnt          = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP4_RHCHAN_CNT );
        pCfg->rxUltraHighCapacityChanCnt     = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP4_RUCHAN_CNT );

        regVal = CSL_REG32_RD( &pCfg->pGenCfgv2Regs->CAP5 );
        pCfg->txFlowCnt     = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP5_TFLOW_CNT );
        pCfg->rxFlowCnt     = CSL_FEXT( regVal, PKTDMA_GCFG_V2_CAP5_RFLOW_CNT );
    }
}

void CSL_pktdmaInitChanCfg( CSL_PktdmaChanCfg *pChanCfg )
{
    if( pChanCfg != NULL )
    {
        /*-------------------------------------------------------------------------
         *  Start by initializing all structure members to 0
         *-----------------------------------------------------------------------*/
        memset( (void *)pChanCfg, 0, sizeof(CSL_PktdmaChanCfg) );
        /*-------------------------------------------------------------------------
         *  Now initialize non-zero structure members
         *-----------------------------------------------------------------------*/
        pChanCfg->chanType            = CSL_PKTDMA_CHAN_TYPE_NORMAL;
        pChanCfg->fetchWordSize       = CSL_PKTDMA_FETCH_WORD_SIZE_16;
        pChanCfg->trEventNum          = CSL_PKTDMA_NO_EVENT;
        pChanCfg->errEventNum         = CSL_PKTDMA_NO_EVENT;
        pChanCfg->flowIdFwRangeCnt    = 0x00004000U;
    }
}

void CSL_pktdmaSetPerfCtrl( CSL_PktdmaCfg *pCfg, uint32_t rxRetryTimeoutCnt )
{
    uint32_t regVal;
    regVal = CSL_FMK( PKTDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT, rxRetryTimeoutCnt );
    CSL_REG32_WR( &pCfg->pGenCfgv2Regs->PERF_CTRL, regVal );
}

void CSL_pktdmaSetUtcCtrl( CSL_PktdmaCfg *pCfg, uint32_t startingThreadNum )
{
}

int32_t CSL_pktdmaRxChanSetTrEvent( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t trEventNum )
{
    return CSL_EUNSUPPORTED_CMD;
}

int32_t CSL_pktdmaRxChanSetBurstSize( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanBurstSize burstSize )
{
    int32_t retVal = CSL_EFAIL;

    if( (burstSize >= CSL_PKTDMA_CHAN_BURST_SIZE_64_BYTES) && (burstSize <= CSL_PKTDMA_CHAN_BURST_SIZE_256_BYTES) )
    {
        CSL_REG32_FINS( &pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].CFG, PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, burstSize );
        retVal = CSL_PASS;
    }
    return retVal;
}

int32_t CSL_pktdmaTxChanSetTrEvent( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t trEventNum )
{
    return CSL_EUNSUPPORTED_CMD;
}

int32_t CSL_pktdmaTxChanSetBurstSize( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanBurstSize burstSize )
{
    int32_t retVal = CSL_EFAIL;

    if( (burstSize >= CSL_PKTDMA_CHAN_BURST_SIZE_64_BYTES) && (burstSize <= CSL_PKTDMA_CHAN_BURST_SIZE_256_BYTES) )
    {
        CSL_REG32_FINS( &pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].CFG, PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE, burstSize );
        retVal = CSL_PASS;
    }
    return retVal;
}

int32_t CSL_pktdmaChanCfg( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, const CSL_PktdmaChanCfg *pChanCfg )
{
    int32_t retVal;

    if( (pCfg == NULL) || (pChanCfg == NULL) )
    {
        retVal = CSL_EFAIL;
    }
    else
    {
        uint32_t regVal;
        regVal = CSL_REG32_RD( &pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].CFG );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR,    pChanCfg->pauseOnError );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO,      pChanCfg->filterEinfo );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS,    pChanCfg->filterPsWords );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_NOTDPKT,         ((pChanCfg->bNoTeardownCompletePkt) ? (uint32_t)1U : (uint32_t)0U) );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE,       pChanCfg->chanType );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_TDTYPE,          pChanCfg->tdType );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE,      pChanCfg->burstSize );
        CSL_FINS( regVal, PKTDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG,     pChanCfg->bIgnoreLongPkts );
        CSL_REG32_WR( &pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].CFG, regVal );

        CSL_REG32_WR(&pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].PRI_CTRL,
                        CSL_FMK(PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY, pChanCfg->busPriority) |
                        CSL_FMK(PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID,  pChanCfg->busOrderId ) );

        CSL_REG32_WR(&pCfg->pPktChanCfgv2Regs->CHAN[chanIdx].TST_SCHED,
                        CSL_FMK(PKTDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY, pChanCfg->dmaPriority) );
        retVal = CSL_PASS;
    }
    return retVal;
}

int32_t CSL_pktdmaGetRT( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaRT *pRT )
{
    uint32_t val;
    val = CSL_REG32_RD( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL );
    pRT->enable         = CSL_FEXT( val, PKTDMA_CHRT_V2_CHAN_CTL_EN );
    pRT->teardown       = CSL_FEXT( val, PKTDMA_CHRT_V2_CHAN_CTL_TDOWN );
    pRT->forcedTeardown = (uint32_t)0U;
    pRT->pause          = CSL_FEXT( val, PKTDMA_CHRT_V2_CHAN_CTL_PAUSE );
    pRT->error          = CSL_FEXT( val, PKTDMA_CHRT_V2_CHAN_CTL_ERROR );

    return CSL_PASS;
}

uint32_t CSL_pktdmaSetRT( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, const CSL_PktdmaRT *pRT )
{
    uint32_t retVal = CSL_PASS;
    uint32_t val;
    uint32_t regVal;
    bool pairComp;
    regVal = CSL_REG32_RD(&pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL);
    pairComp = CSL_FEXT(regVal, PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE) ;

    val =   CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_EN,           pRT->enable)         |
            CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_TDOWN,        pRT->teardown)       |
            CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_FTDOWN,       pRT->forcedTeardown) |
            CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_PAUSE,        pRT->pause);
            
    if(!pairComp)
    {
        CSL_pktdmaSetChanAutoPair(pCfg,chanIdx,1U);
        regVal = CSL_REG32_RD(&pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL);
    }
    CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chanIdx].CTL, (regVal) | val);

    return retVal;
}

int32_t CSL_pktdmaEnableChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    return CSL_pktdmaSetChanEnable( pCfg, chanIdx, chanType, (bool)true );
}

int32_t CSL_pktdmaDisableChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    return CSL_pktdmaSetChanEnable( pCfg, chanIdx, chanType, (bool)false );
}

int32_t CSL_pktdmaTeardownChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, bool bForce, bool bWait, uint32_t chanType )
{
    return CSL_pktdmaTeardownChan( pCfg, chanIdx, chanType, bForce, bWait );
}

int32_t CSL_pktdmaPauseChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    return CSL_pktdmaPauseChan( pCfg, chanIdx, chanType, CSL_PKTDMA_PAUSE_CHAN );
}

int32_t CSL_pktdmaUnpauseChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    return CSL_pktdmaPauseChan( pCfg, chanIdx, chanType, CSL_PKTDMA_UNPAUSE_CHAN );
}

int32_t CSL_pktdmaTriggerChannel( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    return CSL_pktdmaTriggerChan( pCfg, chanIdx, chanType );
}

void CSL_pktdmaClearChanErr( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, uint32_t chanType )
{
    CSL_pktdmaClearChanError( pCfg, chanIdx, chanType );
}

void CSL_pktdmaCfgRxFlowIdFirewall( CSL_PktdmaCfg *pCfg, uint32_t outEvtNum )
{
}

bool CSL_pktdmaGetRxFlowIdFirewallStatus( CSL_PktdmaCfg *pCfg, CSL_PktdmaRxFlowIdFirewallStatus *pRxFlowIdFwStatus )
{
    bool bRetVal = (bool)false;
#ifdef CSL_PKTDMA_GCFG_RFLOWFWSTAT_PEND_MASK
    uint32_t regVal;

    regVal = CSL_REG32_RD( &pCfg->pGenCfgRegs->RFLOWFWSTAT );
    if( CSL_FEXT( regVal, PKTDMA_GCFG_RFLOWFWSTAT_PEND ) != (uint32_t)0U )
    {
        pRxFlowIdFwStatus->flowId = CSL_FEXT( regVal, PKTDMA_GCFG_RFLOWFWSTAT_FLOWID );
        pRxFlowIdFwStatus->chnIdx = CSL_FEXT( regVal, PKTDMA_GCFG_RFLOWFWSTAT_CHANNEL );
        /* Clear pending bit to ready flow id firewall to capture next error */
        CSL_FINS( regVal, PKTDMA_GCFG_RFLOWFWSTAT_PEND, (uint32_t)0U );
        CSL_REG32_WR( &pCfg->pGenCfgRegs->RFLOWFWSTAT, regVal );
        bRetVal = (bool)true;
    }
#endif
    return bRetVal;
}

void CSL_pktdmaGetChanStats( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, CSL_PktdmaChanStats *pChanStats )
{
    if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
    {
        pChanStats->packetCnt        = CSL_REG32_RD( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].PCNT );
        pChanStats->completedByteCnt = CSL_REG32_RD( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].BCNT );
        pChanStats->startedByteCnt   = CSL_REG32_RD( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].SBCNT );
        pChanStats->droppedPacketCnt = CSL_REG32_RD( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].DCNT );
    }
}

void CSL_pktdmaDecChanStats( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, const CSL_PktdmaChanStats *pChanStats )
{
    if( (chanDir == CSL_PKTDMA_CHAN_DIR_TX) || (chanDir == CSL_PKTDMA_CHAN_DIR_RX) )
    {
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].PCNT,  pChanStats->packetCnt );
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].BCNT,  pChanStats->completedByteCnt );
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].SBCNT, pChanStats->startedByteCnt );
        CSL_REG32_WR( &pCfg->pPktChanRtv2Regs->CHAN[chanIdx].DCNT,  pChanStats->droppedPacketCnt );
    }
}

int32_t CSL_pktdmaSet_TR_XY(CSL_PktdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1;
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chNum].STATIC_TR_XY, val);
       retVal = 0;
    }
    return retVal;
}

int32_t CSL_pktdmaSet_TR_Z(CSL_PktdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1;
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chNum].STATIC_TR_Z, val);
       retVal = 0;
    }
    return retVal;
}

uint32_t CSL_pktdmaGetPeerData(CSL_PktdmaCfg *pCfg, uint32_t chNum)
{
    uint32_t regVal = 0U;
    if(pCfg != NULL)
    {
       regVal = CSL_REG32_RD(&pCfg->pPktChanRtv2Regs->CHAN[chNum].PERIPH_BCNT);
    }
    return regVal;
}

int32_t CSL_pktdmaSetPeerData(CSL_PktdmaCfg *pCfg, uint32_t val, uint32_t chNum)
{
    int32_t retVal = -1; 
    if(pCfg != NULL)
    {
       CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chNum].PERIPH_BCNT, val);
       retVal = 0;
    }
    return retVal;
}

int32_t CSL_pktdmaIsPairComp(CSL_PktdmaCfg *pCfg, uint32_t chNum)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal;
    uint32_t pairComp = 0u;

    if(pCfg != NULL)
    {
        regVal = CSL_REG32_RD(&pCfg->pPktChanRtv2Regs->CHAN[chNum].CTL) ;
        pairComp = CSL_FEXT(regVal, PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE) ;
    }

    if(pairComp != 1U)
    {
        retVal = CSL_EFAIL;
    }
    return retVal;
}
