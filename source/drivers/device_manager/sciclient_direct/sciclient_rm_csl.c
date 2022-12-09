/*
 * Copyright (c) 2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  \file sciclient_rm_csl.c
 *
 *  \brief File containing the SCICLIENT API interfaces to the resource
 *         management services through CSL API.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/device_manager/sciclient.h>

#include <drivers/hw_include/cslr_soc.h>
#include <ti/csl/csl_psilcfg.h>
#include <ti/csl/csl_ringacc.h>
#include <ti/csl/csl_udmap.h>
#include <drivers/hw_include/cslr_intaggr.h>
#include <drivers/hw_include/cslr_intr_router.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_AM65XX)
/** \brief Number of input virtual interrupts to IR in main NAVSS */
#define UDMA_NAVSS0_IR_NUM_IN_INTR      (440U)
/** \brief Number of output interrupts from IR in main NAVSS */
#define UDMA_NAVSS0_IR_NUM_OUT_INTR     (152U)
/** \brief Number of input virtual interrupts to IR in MCU NAVSS */
#define UDMA_MCU_NAVSS0_IR_NUM_IN_INTR  (440U)
/** \brief Number of output interrupts from IR in MCU NAVSS */
#define UDMA_MCU_NAVSS0_IR_NUM_OUT_INTR (152U)
#else
/** \brief Number of input virtual interrupts to IR in main NAVSS */
#define UDMA_NAVSS0_IR_NUM_IN_INTR      (512U)
/** \brief Number of output interrupts from IR in main NAVSS */
#define UDMA_NAVSS0_IR_NUM_OUT_INTR     (408U)
/** \brief Number of input virtual interrupts to IR in MCU NAVSS */
#define UDMA_MCU_NAVSS0_IR_NUM_IN_INTR  (512U)
/** \brief Number of output interrupts from IR in MCU NAVSS */
#define UDMA_MCU_NAVSS0_IR_NUM_OUT_INTR (64U)
#endif

/** \brief UTC start thread ID for a SOC */
#define UDMA_UTC_START_THREAD_ID        (CSL_PSILCFG_NAVSS_MAIN_MSMC0_PSILD_THREAD_OFFSET)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
#if defined (LOKI_BUILD)
#define HOST_EMULATION (1U)
#endif


#if defined (HOST_EMULATION)
/* These variables are defined for supporting host emulation ( PC emulation ) and
will not be used for target*/
extern CSL_udmap_gcfgRegs       gHost_udmap_gcfgRegs;
extern CSL_udmap_rxfcfgRegs     gHost_udmap_rxfcfgRegs;
extern CSL_udmap_txccfgRegs     gHost_udmap_txccfgRegs;
extern CSL_udmap_rxccfgRegs     gHost_udmap_rxccfgRegs;
extern CSL_udmap_txcrtRegs      gHost_udmap_txcrtRegs;
extern CSL_udmap_rxcrtRegs      gHost_udmap_rxcrtRegs;
extern CSL_ringacc_gcfgRegs     gHost_ringacc_gcfgRegs;
extern CSL_ringacc_cfgRegs      gHost_ringacc_cfgRegs;
extern CSL_ringacc_rtRegs       gHost_ringacc_rtRegs;
extern CSL_ringacc_monitorRegs  gHost_ringacc_monitorRegs;
extern CSL_ringacc_fifosRegs    gHost_ringacc_fifosRegs;
extern CSL_ringacc_iscRegs      gHost_ringacc_iscRegs;
extern CSL_psilcfgRegs          gHost_psilcfgRegs;
extern CSL_intaggr_cfgRegs      gHost_intaggr_cfgRegs;
extern CSL_intaggr_imapRegs     gHost_intaggr_imapRegs;
extern CSL_intaggr_intrRegs     gHost_intaggr_intrRegs;
extern CSL_intaggr_l2gRegs      gHost_intaggr_l2gRegs;
extern CSL_intaggr_mcastRegs    gHost_intaggr_mcastRegs;
extern CSL_intaggr_gcntcfgRegs  gHost_intaggr_gcntcfgRegs;
extern CSL_intaggr_gcntrtiRegs  gHost_intaggr_gcntrtiRegs;
#ifdef CSL_INTAGGR_UNMAP_UNMAP_MAP_MAPIDX_MASK
extern CSL_intaggr_unmapRegs    gHost_intaggr_unmapRegs;
#endif
extern CSL_intr_router_cfgRegs  gHost_intr_router_cfgRegs;
#endif

typedef struct
{
    CSL_UdmapCfg            udmapRegs;
    /**< UDMAP register configuration */
    CSL_RingAccCfg          raRegs;
    /**< RA register configuration */
    CSL_psilcfgRegs        *psilCfgRegs;
    /**< PSILCFG register configuration */
    CSL_IntaggrCfg          iaRegs;
    /**< Interrupt Aggregator configuration */
    CSL_IntrRouterCfg       irRegs;
    /**< Interrupt Router configuration */
    uint32_t                txUdmaThreadIdStart;
    uint32_t                txUdmaThreadIdEnd;
    uint32_t                rxUdmaThreadIdStart;
    uint32_t                rxUdmaThreadIdEnd;
} SciUdmaRmObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (HOST_EMULATION) || defined (LOKI_BUILD)
/* These variables are defined for supporting host emulation ( PC emulation ) and
will not be used for target*/
static SciUdmaRmObj gSciUdmaRmObjMain =
{
    {
        &gHost_udmap_gcfgRegs,
        &gHost_udmap_rxfcfgRegs,
        &gHost_udmap_txccfgRegs,
        &gHost_udmap_rxccfgRegs,
        &gHost_udmap_txcrtRegs,
        &gHost_udmap_rxcrtRegs
    },
    {
        &gHost_ringacc_gcfgRegs,
        &gHost_ringacc_cfgRegs,
        &gHost_ringacc_rtRegs,
        &gHost_ringacc_monitorRegs,
        &gHost_ringacc_fifosRegs,
        &gHost_ringacc_iscRegs,
        CSL_NAVSS_MAIN_RINGACC_RING_CNT
    },
    &gHost_psilcfgRegs,
    {
        &gHost_intaggr_cfgRegs,
        &gHost_intaggr_imapRegs,
        &gHost_intaggr_intrRegs,
        &gHost_intaggr_l2gRegs,
        &gHost_intaggr_mcastRegs,
        &gHost_intaggr_gcntcfgRegs,
        &gHost_intaggr_gcntrtiRegs,
#ifdef CSL_INTAGGR_UNMAP_UNMAP_MAP_MAPIDX_MASK
        &gHost_intaggr_unmapRegs,
#endif
        4608U,
        256U,
        4U,
        512U,
        512U
    },

    {
        &gHost_intr_router_cfgRegs,
        NULL,
        UDMA_NAVSS0_IR_NUM_IN_INTR,
        UDMA_NAVSS0_IR_NUM_OUT_INTR
    },
    CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_OFFSET,
    CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_CNT - 1,
    CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_OFFSET,
    CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_CNT - 1,
};

static SciUdmaRmObj gSciUdmaRmObjMcu =
{
    {
        &gHost_udmap_gcfgRegs,
        &gHost_udmap_rxfcfgRegs,
        &gHost_udmap_txccfgRegs,
        &gHost_udmap_rxccfgRegs,
        &gHost_udmap_txcrtRegs,
        &gHost_udmap_rxcrtRegs
    },

    {
        &gHost_ringacc_gcfgRegs,
        &gHost_ringacc_cfgRegs,
        &gHost_ringacc_rtRegs,
        &gHost_ringacc_monitorRegs,
        &gHost_ringacc_fifosRegs,
        &gHost_ringacc_iscRegs,
        CSL_NAVSS_MCU_RINGACC_RING_CNT
    },
    &gHost_psilcfgRegs,

    {
        &gHost_intaggr_cfgRegs,
        &gHost_intaggr_imapRegs,
        &gHost_intaggr_intrRegs,
        &gHost_intaggr_l2gRegs,
        &gHost_intaggr_mcastRegs,
        &gHost_intaggr_gcntcfgRegs,
        &gHost_intaggr_gcntrtiRegs,
#ifdef CSL_INTAGGR_UNMAP_UNMAP_MAP_MAPIDX_MASK
        &gHost_intaggr_unmapRegs,
#endif
        1536,
        256U,
        4U,
        256U,
        128U
    },

    {
        &gHost_intr_router_cfgRegs,
        NULL,
        UDMA_MCU_NAVSS0_IR_NUM_IN_INTR,
        UDMA_MCU_NAVSS0_IR_NUM_OUT_INTR
    },
    CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_OFFSET,
    CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_CNT - 1,
    CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_OFFSET,
    CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_CNT - 1,
};
#else
static SciUdmaRmObj gSciUdmaRmObjMain =
{
    .udmapRegs =
    {
        .pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_BASE),
        .pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE),
        .pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE),
        .pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE),
        .pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE),
        .pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE)
    },
    .raRegs =
    {
        .pGlbRegs   = (CSL_ringacc_gcfgRegs *) CSL_NAVSS0_UDMASS_RINGACC0_GCFG_BASE,
        .pCfgRegs   = (CSL_ringacc_cfgRegs *) CSL_NAVSS0_UDMASS_RINGACC0_CFG_BASE,
        .pRtRegs    = (CSL_ringacc_rtRegs *) CSL_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE,
        .pMonRegs   = (CSL_ringacc_monitorRegs *) CSL_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE,
        .pFifoRegs  = (CSL_ringacc_fifosRegs *) CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE,
#if defined (SOC_AM65XX)
        .pIscRegs   = (CSL_ringacc_iscRegs *) CSL_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE,
#else
        .pIscRegs   = (CSL_ringacc_iscRegs *) CSL_NAVSS0_UDMASS_RINGACC0_ISC_BASE,
#endif
        .maxRings   = CSL_NAVSS_MAIN_RINGACC_RING_CNT
    },
    .psilCfgRegs         = (CSL_psilcfgRegs *) CSL_NAVSS0_UDMASS_PSILCFG0_CFG_PROXY_BASE,
    .iaRegs =
    {
        .pCfgRegs       = (CSL_intaggr_cfgRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_BASE,
        .pImapRegs      = (CSL_intaggr_imapRegs *) CSL_NAVSS0_UDMASS_INTA0_IMAP_BASE,
        .pIntrRegs      = (CSL_intaggr_intrRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE,
#if defined (SOC_AM65XX)
        .pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE,
#else
        .pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE,
#endif
        .pMcastRegs     = (CSL_intaggr_mcastRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE,
        .pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE,
        .pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE,
        .srcEventCnt    = 4608U,
        .virtIntrCnt    = 256U,
        .localEventCnt  = 4U,
        .globalEventCnt = 512U,
        .mcastEventCnt  = 512U
    },
    .irRegs =
    {
        .pIntrRouterRegs = (CSL_intr_router_cfgRegs *) CSL_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE,
        .pIntdRegs       = (CSL_intr_router_intd_cfgRegs *) NULL,
        .numInputIntrs   = UDMA_NAVSS0_IR_NUM_IN_INTR,
        .numOutputIntrs  = UDMA_NAVSS0_IR_NUM_OUT_INTR
    },
    .txUdmaThreadIdStart = CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_OFFSET,
    .txUdmaThreadIdEnd = CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_CNT - 1,
    .rxUdmaThreadIdStart = CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_OFFSET,
    .rxUdmaThreadIdEnd = CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_CNT - 1,
};

static SciUdmaRmObj gSciUdmaRmObjMcu =
{
    .udmapRegs =
    {
        .pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE),
        .pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE),
        .pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE),
        .pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE),
        .pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE),
        .pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) CSL_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE)
    },
    .raRegs =
    {
        .pGlbRegs   = (CSL_ringacc_gcfgRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE,
        .pCfgRegs   = (CSL_ringacc_cfgRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE,
        .pRtRegs    = (CSL_ringacc_rtRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE,
        .pMonRegs   = (CSL_ringacc_monitorRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE,
        .pFifoRegs  = (CSL_ringacc_fifosRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE,
#if defined (SOC_AM65XX)
        .pIscRegs   = (CSL_ringacc_iscRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE,
#else
        .pIscRegs   = (CSL_ringacc_iscRegs *) CSL_MCU_NAVSS0_UDMASS_RINGACC0_ISC_BASE,
#endif
        .maxRings   = CSL_NAVSS_MCU_RINGACC_RING_CNT
    },
    .psilCfgRegs         = (CSL_psilcfgRegs *) CSL_MCU_NAVSS0_UDMASS_PSILSS_CFG0_PROXY_BASE,
    .iaRegs =
    {
        .pCfgRegs       = (CSL_intaggr_cfgRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE,
        .pImapRegs      = (CSL_intaggr_imapRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE,
        .pIntrRegs      = (CSL_intaggr_intrRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE,
#if defined (SOC_AM65XX)
        .pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE,
#else
        .pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_I2G_BASE,
#endif
        .pMcastRegs     = (CSL_intaggr_mcastRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE,
        .pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE,
        .pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) CSL_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE,
        .srcEventCnt    = 1536,
        .virtIntrCnt    = 256U,
        .localEventCnt  = 4U,
        .globalEventCnt = 256U,
        .mcastEventCnt  = 128U
    },
    .irRegs =
    {
        .pIntrRouterRegs = (CSL_intr_router_cfgRegs *) CSL_MCU_NAVSS0_INTR0_CFG_BASE,
        .pIntdRegs       = (CSL_intr_router_intd_cfgRegs *) NULL,
        .numInputIntrs   = UDMA_MCU_NAVSS0_IR_NUM_IN_INTR,
        .numOutputIntrs  = UDMA_MCU_NAVSS0_IR_NUM_OUT_INTR
    },
    .txUdmaThreadIdStart = CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_OFFSET,
    .txUdmaThreadIdEnd = CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_CNT - 1,
    .rxUdmaThreadIdStart = CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_OFFSET,
    .rxUdmaThreadIdEnd = CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_OFFSET + CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_CNT - 1,
};
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Sciclient_rmInit(void)
{
/* UDMA not present in CC QT build. Only DRU is present */
#ifndef CC_QT_BUILD
    /*
     * UTC config init
     */
    /* One time setup of UTC thread base */
    CSL_udmapSetUtcCtrl(&gSciUdmaRmObjMain.udmapRegs, UDMA_UTC_START_THREAD_ID);
    CSL_udmapSetUtcCtrl(&gSciUdmaRmObjMcu.udmapRegs, UDMA_UTC_START_THREAD_ID);
#endif
}

int32_t Sciclient_rmIrqSet(const struct tisci_msg_rm_irq_set_req *req,
                           const struct tisci_msg_rm_irq_set_resp *resp,
                           uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    uint16_t            eventOffset;    /* Within a IA - convert from global to local offset within IA */
    uint32_t            chOffset;       /* Within a UDMA - convert from global source index to local offset within UDMAP */
    uint32_t            irOffset;       /* Within a IR - convert from cpu dest interrupt index to local IR offset within UDMAP */
    uint64_t            vintrBitNum;
    SciUdmaRmObj       *rmObj;

    /* Program ring OES */
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_RINGACC_0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id))
#else
    if((TISCI_DEV_NAVSS0_RINGACC0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id))
#endif
    {
        rmObj = &gSciUdmaRmObjMain;
        if(TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id)
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

        if(TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID & req->valid_params)
        {
            retVal += CSL_ringaccSetEvent(
                          &rmObj->raRegs, req->src_index, req->global_event);
        }
    }

    /* Program channel OES */
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_UDMAP_0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->src_id))
#else
    if((TISCI_DEV_NAVSS0_UDMAP0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->src_id))
#endif
    {
        rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
        if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->src_id)
#else
        if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->src_id)
#endif
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

        if(TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID & req->valid_params)
        {
            if(req->src_index < TISCI_UDMAP0_TX_EOES_IRQ_SRC_IDX_START)
            {
                /* TX OES programming */
                chOffset = req->src_index;
                CSL_REG32_WR(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[chOffset].TOES[0], CSL_FMK(UDMAP_TXCCFG_CHAN_TOES_EVT_NUM, req->global_event));
            }
            else if(req->src_index < TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START)
            {
                /* TX EOES programming */
                chOffset = req->src_index - TISCI_UDMAP0_TX_EOES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[chOffset].TEOES[0], CSL_FMK(UDMAP_TXCCFG_CHAN_TEOES_EVT_NUM, req->global_event));
            }
            else if(req->src_index < TISCI_UDMAP0_RX_EOES_IRQ_SRC_IDX_START)
            {
                /* RX OES programming */
                chOffset = req->src_index - TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[chOffset].ROES[0], CSL_FMK(UDMAP_RXCCFG_CHAN_ROES_EVT_NUM, req->global_event));
            }
            else
            {
                /* RX EOES programming */
                chOffset = req->src_index - TISCI_UDMAP0_RX_EOES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[chOffset].REOES[0], CSL_FMK(UDMAP_RXCCFG_CHAN_REOES_EVT_NUM, req->global_event));
            }
        }
    }

    /* Program IA/VINT */
#if defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_UDMASS_INTA_0 == req->ia_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id))
#else
    if((TISCI_DEV_NAVSS0_UDMASS_INTAGGR_0 == req->ia_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id))
#endif
    {
        if((TISCI_MSG_VALUE_RM_IA_ID_VALID & req->valid_params) &&
           (TISCI_MSG_VALUE_RM_VINT_VALID & req->valid_params) &&
           (TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID & req->valid_params))
        {
            rmObj = &gSciUdmaRmObjMain;
            eventOffset = req->global_event & 0x1FFFU;      /* Max 8K events */
            if(TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id)
            {
                rmObj = &gSciUdmaRmObjMcu;
                eventOffset = req->global_event & 0x7FFU;   /* Max 2K events */
            }

            vintrBitNum = req->vint * 64U;
            vintrBitNum += req->vint_status_bit_index;
            retVal += CSL_intaggrMapEventIntr(
                          &rmObj->iaRegs, eventOffset, vintrBitNum);
            retVal += CSL_intaggrClrIntr(&rmObj->iaRegs, vintrBitNum);
            retVal += CSL_intaggrSetIntrEnable(&rmObj->iaRegs, vintrBitNum, TRUE);
        }
    }

    /* Program IR */
    if((TISCI_MSG_VALUE_RM_DST_ID_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_VINT_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_IA_ID_VALID & req->valid_params))
    {
        rmObj = &gSciUdmaRmObjMain;
        if(TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id)
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

#if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)
        /* Program GIC IR */
    #if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2)
        if(TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS == req->dst_id)
    #elif defined (SOC_J784S4)
        if(TISCI_DEV_COMPUTE_CLUSTER_J7AHP0_GIC500SS_0 == req->dst_id)
    #endif
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq <= CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_63)
#else
            if(req->dst_host_irq <= CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_63)
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_0;
#else
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_0;
#endif
            }
            else
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_64;
#else
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_64;
#endif
                irOffset += 64U;
            }

            CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
        }

        //TODO: Hack till proper core support in TISCI
#if defined (BUILD_C66X)
        /* Program C66x IR */
        if((TISCI_DEV_C66SS0 == req->dst_id) ||
           (TISCI_DEV_C66SS1 == req->dst_id))
        {
            CSL_IntrRouterCfg       c66xIrRegs;
            uint32_t                c66xIrOffset;

            /* Program NAVSS IR */
#if defined (BUILD_C66X_1)
            irOffset = (req->dst_host_irq - CSLR_C66_COREPAC0_C66_EVENT_IN_C66_0_INTROUTER0_OUTL_54) + 320;
#endif
#if defined (BUILD_C66X_2)
            irOffset = (req->dst_host_irq - CSLR_C66_COREPAC1_C66_EVENT_IN_C66_1_INTROUTER0_OUTL_54) + 352;
#endif
            CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);

            /* Program C66x IR */
            c66xIrRegs.pIntdRegs       = (CSL_intr_router_intd_cfgRegs *) NULL;
            c66xIrRegs.numInputIntrs   = 400;
            c66xIrRegs.numOutputIntrs  = 97;
#if defined (BUILD_C66X_1)
            c66xIrRegs.pIntrRouterRegs = (CSL_intr_router_cfgRegs *) 0x10000000;
            c66xIrOffset = (req->dst_host_irq - CSLR_C66_COREPAC0_C66_EVENT_IN_C66_0_INTROUTER0_OUTL_54) + 54;
#endif
#if defined (BUILD_C66X_2)
            c66xIrRegs.pIntrRouterRegs = (CSL_intr_router_cfgRegs *) 0x10000000;
            c66xIrOffset = (req->dst_host_irq - CSLR_C66_COREPAC1_C66_EVENT_IN_C66_1_INTROUTER0_OUTL_54) + 54;
#endif
            CSL_intrRouterCfgMux(&c66xIrRegs, 0, c66xIrOffset);
        }
#endif  /* (BUILD_C66X) */

        /* Program MCU1 IR */
        if((TISCI_DEV_MCU_R5FSS0_CORE0 == req->dst_id) ||
           (TISCI_DEV_MCU_R5FSS0_CORE1 == req->dst_id))
        {
            if(req->dst_host_irq >= CSLR_MCU_R5FSS0_CORE0_INTR_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_0)
            {
                irOffset = req->dst_host_irq - CSLR_MCU_R5FSS0_CORE0_INTR_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_0;
                CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
            }
        }

        /* Program MCU2_0 IR */
        if(TISCI_DEV_R5FSS0_CORE0 == req->dst_id)
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq >= (CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_0_OUTL_INTR_192 - 192))
#else
            if(req->dst_host_irq >= (CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_192 - 192))
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_0_OUTL_INTR_192 - 192);
#else
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_192 - 192);
#endif
                CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
            }
        }

        /* Program MCU2_1 IR */
        if(TISCI_DEV_R5FSS0_CORE1 == req->dst_id)
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq > (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_0_OUTL_INTR_224 - 224))
#else
            if(req->dst_host_irq > (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_224 - 224))
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_0_OUTL_INTR_224 - 224);
#else
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_224 - 224);
#endif
                CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
            }
        }

        /* Program MCU3_0 IR */
        if(TISCI_DEV_R5FSS1_CORE0 == req->dst_id)
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq >= (CSLR_R5FSS1_CORE0_INTR_NAVSS0_INTR_0_OUTL_INTR_256 - 256))
#else
            if(req->dst_host_irq >= (CSLR_R5FSS1_CORE0_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_256 - 256))
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_0_OUTL_INTR_224 - 256);
#else
                irOffset = req->dst_host_irq - (CSLR_R5FSS0_CORE1_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_224 - 256);
#endif
                CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
            }
        }

        /* Program MCU3_1 IR */
        if(TISCI_DEV_R5FSS1_CORE1 == req->dst_id)
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq >= (CSLR_R5FSS1_CORE1_INTR_NAVSS0_INTR_0_OUTL_INTR_288 - 288))
#else
            if(req->dst_host_irq >= (CSLR_R5FSS1_CORE1_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_288 - 288))
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - (CSLR_R5FSS1_CORE1_INTR_NAVSS0_INTR_0_OUTL_INTR_288 - 288);
#else
                irOffset = req->dst_host_irq - (CSLR_R5FSS1_CORE1_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_288 - 288);
#endif
                CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
            }
        }

        /* Program NAVSS IR, used for IPC/Mailbox */
#if defined (SOC_J721S2) || defined (SOC_J784S4)
        if( TISCI_DEV_NAVSS0_INTR_0 == req->dst_id)
#else
        if( TISCI_DEV_NAVSS0_INTR_ROUTER_0 == req->dst_id)
#endif
        {
            irOffset = req->dst_host_irq;
            CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
        }

#else   /* J721E */
        /* Program GIC IR */
        if(TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS == req->dst_id)
        {
            if(req->dst_host_irq <= CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_63)
            {
                irOffset = req->dst_host_irq - CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_0;
            }
            else
            {
                irOffset = req->dst_host_irq - CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_64;
                irOffset += 64U;
            }

            CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
        }

        /* Program MCU IR */
        if((TISCI_DEV_MCU_R5FSS0_CORE0 == req->dst_id) ||
           (TISCI_DEV_MCU_R5FSS0_CORE1 == req->dst_id))
        {
            irOffset = req->dst_host_irq - CSL_MCU0_INTR_NAVSS0_R5_0_PEND_0;
            CSL_intrRouterCfgMux(&rmObj->irRegs, req->vint, irOffset);
        }
#endif
    }

    return (retVal);
}

int32_t Sciclient_rmIrqRelease(const struct tisci_msg_rm_irq_release_req *req,
                               uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    uint16_t            eventOffset;    /* Within a IA - convert from global to local offset within IA */
    uint32_t            chOffset;       /* Within a UDMA - convert from global source index to local offset within UDMAP */
    uint32_t            irOffset;       /* Within a IR - convert from cpu dest interrupt index to local IR offset within UDMAP */
    uint64_t            vintrBitNum;
    SciUdmaRmObj       *rmObj;

    /* Reset ring OES */
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_RINGACC_0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id))
#else
    if((TISCI_DEV_NAVSS0_RINGACC0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id))
#endif
    {
        rmObj = &gSciUdmaRmObjMain;
        if(TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->src_id)
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

        if(TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID & req->valid_params)
        {
            retVal += CSL_ringaccSetEvent(
                          &rmObj->raRegs, req->src_index, CSL_UDMAP_NO_EVENT);
        }
    }

    /* Reset channel OES */
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_UDMAP_0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->src_id))
#else
    if((TISCI_DEV_NAVSS0_UDMAP0 == req->src_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->src_id))
#endif
    {
        rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
        if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->src_id)
#else
        if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->src_id)
#endif
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

        if(TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID & req->valid_params)
        {
            if(req->src_index < TISCI_UDMAP0_TX_EOES_IRQ_SRC_IDX_START)
            {
                /* TX OES programming */
                chOffset = req->src_index;
                CSL_REG32_WR(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[chOffset].TOES[0], CSL_FMK(UDMAP_TXCCFG_CHAN_TOES_EVT_NUM, CSL_UDMAP_NO_EVENT));
            }
            else if(req->src_index < TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START)
            {
                /* TX EOES programming */
                chOffset = req->src_index - TISCI_UDMAP0_TX_EOES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[chOffset].TEOES[0], CSL_FMK(UDMAP_TXCCFG_CHAN_TEOES_EVT_NUM, CSL_UDMAP_NO_EVENT));
            }
            else if(req->src_index < TISCI_UDMAP0_RX_EOES_IRQ_SRC_IDX_START)
            {
                /* RX OES programming */
                chOffset = req->src_index - TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[chOffset].ROES[0], CSL_FMK(UDMAP_RXCCFG_CHAN_ROES_EVT_NUM, CSL_UDMAP_NO_EVENT));
            }
            else
            {
                /* RX EOES programming */
                chOffset = req->src_index - TISCI_UDMAP0_RX_EOES_IRQ_SRC_IDX_START;
                CSL_REG32_WR(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[chOffset].REOES[0], CSL_FMK(UDMAP_RXCCFG_CHAN_REOES_EVT_NUM, CSL_UDMAP_NO_EVENT));
            }
        }
    }

    /* Disable IA/VINT */
#if defined (SOC_J721S2) || defined (SOC_J784S4)
    if((TISCI_DEV_NAVSS0_UDMASS_INTA_0 == req->ia_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id))
#else
    if((TISCI_DEV_NAVSS0_UDMASS_INTAGGR_0 == req->ia_id) ||
       (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id))
#endif
    {
        if((TISCI_MSG_VALUE_RM_IA_ID_VALID & req->valid_params) &&
           (TISCI_MSG_VALUE_RM_VINT_VALID & req->valid_params) &&
           (TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID & req->valid_params))
        {
            rmObj = &gSciUdmaRmObjMain;
            eventOffset = req->global_event & 0x1FFFU;      /* Max 8K events */
            if(TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id)
            {
                rmObj = &gSciUdmaRmObjMcu;
                eventOffset = req->global_event & 0x7FFU;   /* Max 2K events */
            }

            vintrBitNum = req->vint * 64U;
            vintrBitNum += req->vint_status_bit_index;
            retVal += CSL_intaggrMapEventIntr(&rmObj->iaRegs, eventOffset, 0U);
            retVal += CSL_intaggrSetIntrEnable(&rmObj->iaRegs, vintrBitNum, FALSE);
            retVal += CSL_intaggrClrIntr(&rmObj->iaRegs, vintrBitNum);
        }
    }

    /* Reset IR */
    if((TISCI_MSG_VALUE_RM_DST_ID_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_VINT_VALID & req->valid_params) &&
       (TISCI_MSG_VALUE_RM_IA_ID_VALID & req->valid_params))
    {
        rmObj = &gSciUdmaRmObjMain;
        if(TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 == req->ia_id)
        {
            rmObj = &gSciUdmaRmObjMcu;
        }

#if defined (SOC_J721E) || (SOC_J721S2) || (SOC_J784S4)
        /* Reset GIC IR */
    #if defined (SOC_J721E) || (SOC_J721S2)
        if(TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS == req->dst_id)
    #elif defined (SOC_J784S4)
        if(TISCI_DEV_COMPUTE_CLUSTER_J7AHP0_GIC500SS_0 == req->dst_id)
    #endif
        {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
            if(req->dst_host_irq <= CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_63)
#else
            if(req->dst_host_irq <= CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_63)
#endif
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_0;
#else
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_0;
#endif
            }
            else
            {
#if defined (SOC_J721S2) || defined (SOC_J784S4)
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_0_OUTL_INTR_64;
#else
                irOffset = req->dst_host_irq - CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_64;
#endif
                irOffset += 64U;
            }

            CSL_intrRouterCfgMux(&rmObj->irRegs, 0U, irOffset);
        }

#if defined (BUILD_C66X)
        /* Reset MCU IR */
        if((TISCI_DEV_C66SS0 == req->dst_id) ||
           (TISCI_DEV_C66SS1 == req->dst_id))
        {
            CSL_IntrRouterCfg       c66xIrRegs;
            uint32_t                c66xIrOffset;

            /* Program NAVSS IR */
#if defined (BUILD_C66X_1)
            irOffset = (req->dst_host_irq - CSLR_C66_COREPAC0_C66_EVENT_IN_C66_0_INTROUTER0_OUTL_54) + 320;
#endif
#if defined (BUILD_C66X_2)
            irOffset = (req->dst_host_irq - CSLR_C66_COREPAC1_C66_EVENT_IN_C66_1_INTROUTER0_OUTL_54) + 352;
#endif
            CSL_intrRouterCfgMux(&rmObj->irRegs, 0U, irOffset);

            /* Program C66x IR */
            c66xIrRegs.pIntdRegs       = (CSL_intr_router_intd_cfgRegs *) NULL;
            c66xIrRegs.numInputIntrs   = 400;
            c66xIrRegs.numOutputIntrs  = 97;
#if defined (BUILD_C66X_1)
            c66xIrRegs.pIntrRouterRegs = (CSL_intr_router_cfgRegs *) 0x10000000;
            c66xIrOffset = (req->dst_host_irq - CSLR_C66_COREPAC0_C66_EVENT_IN_C66_0_INTROUTER0_OUTL_54) + 54;
#endif
#if defined (BUILD_C66X_2)
            c66xIrRegs.pIntrRouterRegs = (CSL_intr_router_cfgRegs *) 0x10000000;
            c66xIrOffset = (req->dst_host_irq - CSLR_C66_COREPAC1_C66_EVENT_IN_C66_1_INTROUTER0_OUTL_54) + 54;
#endif
            CSL_intrRouterCfgMux(&c66xIrRegs, 0U, c66xIrOffset);
        }
#else
        //TODO: Hack till proper core support in TISCI
#if defined (SOC_J721S2) || defined (SOC_J784S4)
        if(req->dst_host_irq >= CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_0_OUTL_INTR_192)
#else
        if(req->dst_host_irq >= CSLR_R5FSS0_CORE0_INTR_NAVSS0_INTR_ROUTER_0_OUTL_INTR_192)
#endif
        {
#if defined (BUILD_MCU2_0) || defined (BUILD_MCU2_1)
            irOffset = req->dst_host_irq - 32U;
            if(TISCI_DEV_MCU_R5FSS0_CORE1 == req->dst_id)
            {
                irOffset = req->dst_host_irq;
            }
#else
            irOffset = req->dst_host_irq + 32U;
            if(TISCI_DEV_MCU_R5FSS0_CORE1 == req->dst_id)
            {
                irOffset = req->dst_host_irq + 64U;
            }
#endif
        }
        else
        {
            irOffset = req->dst_host_irq - CSLR_MCU_R5FSS0_CORE0_INTR_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_0;
        }
        CSL_intrRouterCfgMux(&rmObj->irRegs, 0U, irOffset);
#endif

#else
        /* Reset GIC IR */
        if(TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS == req->dst_id)
        {
            if(req->dst_host_irq <= CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_63)
            {
                irOffset = req->dst_host_irq - CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_0;
            }
            else
            {
                irOffset = req->dst_host_irq - CSL_GIC0_INTR_NAVSS0_BUS_A53_PEND_64;
                irOffset += 64U;
            }

            CSL_intrRouterCfgMux(&rmObj->irRegs, 0U, irOffset);
        }

        /* Reset MCU IR */
        if((TISCI_DEV_MCU_R5FSS0_CORE0 == req->dst_id) ||
           (TISCI_DEV_MCU_R5FSS0_CORE1 == req->dst_id))
        {
            irOffset = req->dst_host_irq - CSL_MCU0_INTR_NAVSS0_R5_0_PEND_0;
            CSL_intrRouterCfgMux(&rmObj->irRegs, 0U, irOffset);
        }
#endif
    }

    return (retVal);
}

int32_t Sciclient_rmRingCfg(const struct tisci_msg_rm_ring_cfg_req *req,
                            const struct tisci_msg_rm_ring_cfg_resp *resp,
                            uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    uint32_t            orderId;
    CSL_RingAccRingCfg  ringCfg;
    SciUdmaRmObj       *rmObj;

    rmObj = &gSciUdmaRmObjMain;
    if(TISCI_DEV_MCU_NAVSS0_RINGACC0 == req->nav_id)
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    /* Copy params */
    ringCfg.physBase    = ((uint64_t) req->addr_lo |
                          (((uint64_t) req->addr_hi) << 32U));
    ringCfg.virtBase    = (void *) ((uintptr_t) ringCfg.physBase);/* Assume same as physical address */
    ringCfg.mode        = req->mode;
    ringCfg.elCnt       = req->count;
    ringCfg.elSz        = ((uint32_t) 1U << (req->size + 2U));
    ringCfg.evtNum      = CSL_UDMAP_NO_EVENT;
    ringCfg.credSecure  = 0U;
    ringCfg.credPriv    = 0U;
    ringCfg.credPrivId  = CSL_RINGACC_CRED_PASSTHRU;
    ringCfg.credVirtId  = CSL_RINGACC_CRED_PASSTHRU;
    retVal = CSL_ringaccInitRing(&rmObj->raRegs, req->index, &ringCfg);

    /* Set order ID */
    orderId = req->order_id;
    if(TISCI_MSG_VALUE_RM_NULL_ORDER_ID == orderId)
    {
        orderId = CSL_RINGACC_ORDERID_BYPASS;
    }
    CSL_ringaccSetRingOrderId(&rmObj->raRegs, &ringCfg, orderId);

    /* Ring reset */
    CSL_ringaccResetRing(&rmObj->raRegs, &ringCfg);

    return (retVal);
}

int32_t Sciclient_rmRingMonCfg(const struct tisci_msg_rm_ring_mon_cfg_req *req,
                               const struct tisci_msg_rm_ring_mon_cfg_resp *resp,
                               uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;

    /* No plan to support CSL implementation */

    return (retVal);
}

int32_t Sciclient_rmUdmapTxChCfg(
            const struct tisci_msg_rm_udmap_tx_ch_cfg_req *req,
            const struct tisci_msg_rm_udmap_tx_ch_cfg_resp *resp,
            uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    CSL_UdmapTxChanCfg  txChCfg;
    SciUdmaRmObj       *rmObj;

    rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->nav_id)
#else
    if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->nav_id)
#endif
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    CSL_udmapInitTxChanCfg(&txChCfg);

    /* Copy params */
    txChCfg.pauseOnError        = req->tx_pause_on_err;
    txChCfg.filterEinfo         = req->tx_filt_einfo;
    txChCfg.filterPsWords       = req->tx_filt_pswords;
    txChCfg.addrType            = req->tx_atype;
    txChCfg.chanType            = req->tx_chan_type;
    txChCfg.fetchWordSize       = req->tx_fetch_size;
    txChCfg.trEventNum          = CSL_UDMAP_NO_EVENT;
    txChCfg.errEventNum         = CSL_UDMAP_NO_EVENT;
    txChCfg.busPriority         = req->tx_priority;
    txChCfg.busQos              = req->tx_qos;
    txChCfg.busOrderId          = req->tx_orderid;
    txChCfg.dmaPriority         = req->tx_sched_priority;
    txChCfg.txCredit            = req->tx_credit_count;
    txChCfg.txThread            = CSL_REG32_RD(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[req->index].THREAD);/* Already set in pair - don't overwrite */
    txChCfg.txTrCQ                  = req->txcq_qnum;
    txChCfg.bNoTeardownCompletePkt  = req->tx_supr_tdpkt;

    /* Config UDMAP TX channel */
    CSL_udmapTxChanCfg(&rmObj->udmapRegs, req->index, &txChCfg);

    return (retVal);
}

int32_t Sciclient_rmUdmapRxChCfg(
            const struct tisci_msg_rm_udmap_rx_ch_cfg_req *req,
            const struct tisci_msg_rm_udmap_rx_ch_cfg_resp *resp,
            uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    CSL_UdmapRxChanCfg  rxChCfg;
    SciUdmaRmObj       *rmObj;

    rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->nav_id)
#else
    if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->nav_id)
#endif
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    CSL_udmapInitRxChanCfg(&rxChCfg);

    /* Copy params */
    rxChCfg.pauseOnError        = req->rx_pause_on_err;
    rxChCfg.addrType            = req->rx_atype;
    rxChCfg.chanType            = req->rx_chan_type;
    rxChCfg.fetchWordSize       = req->rx_fetch_size;
    rxChCfg.trEventNum          = CSL_UDMAP_NO_EVENT;
    rxChCfg.errEventNum         = CSL_UDMAP_NO_EVENT;
    rxChCfg.busPriority         = req->rx_priority;
    rxChCfg.busQos              = req->rx_qos;
    rxChCfg.busOrderId          = req->rx_orderid;
    rxChCfg.dmaPriority         = req->rx_sched_priority;
    rxChCfg.flowIdFwRangeStart  = req->flowid_start;
    rxChCfg.flowIdFwRangeCnt    = req->flowid_cnt;
    rxChCfg.bIgnoreShortPkts    = req->rx_ignore_short;
    rxChCfg.bIgnoreLongPkts     = req->rx_ignore_long;
    rxChCfg.rxThread            = CSL_REG32_RD(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[req->index].THREAD);/* Already set in pair - don't overwrite */
    rxChCfg.rxTrCQ              = req->rxcq_qnum;

    /* Config UDMAP RX channel */
    CSL_udmapRxChanCfg(&rmObj->udmapRegs, req->index, &rxChCfg);

    return (retVal);
}

int32_t Sciclient_rmUdmapFlowCfg(
            const struct tisci_msg_rm_udmap_flow_cfg_req *req,
            const struct tisci_msg_rm_udmap_flow_cfg_resp *resp,
            uint32_t timeout)
{
    int32_t             retVal = CSL_PASS;
    CSL_UdmapRxFlowCfg  flowCfg;
    SciUdmaRmObj       *rmObj;

    rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->nav_id)
#else
    if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->nav_id)
#endif
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    flowCfg.einfoPresent            = req->rx_einfo_present;
    flowCfg.psInfoPresent           = req->rx_psinfo_present;
    flowCfg.errorHandling           = req->rx_error_handling;
    flowCfg.descType                = req->rx_desc_type;
    flowCfg.psLocation              = req->rx_ps_location;
    flowCfg.sopOffset               = req->rx_sop_offset;
    flowCfg.defaultRxCQ             = req->rx_dest_qnum;
    flowCfg.srcTag.loSel            = req->rx_src_tag_lo_sel;
    flowCfg.srcTag.loVal            = req->rx_src_tag_lo;
    flowCfg.srcTag.hiSel            = req->rx_src_tag_hi_sel;
    flowCfg.srcTag.hiVal            = req->rx_src_tag_hi;
    flowCfg.dstTag.loSel            = req->rx_dest_tag_lo_sel;
    flowCfg.dstTag.loVal            = req->rx_dest_tag_lo;
    flowCfg.dstTag.hiSel            = req->rx_dest_tag_hi_sel;
    flowCfg.dstTag.hiVal            = req->rx_dest_tag_hi;
    flowCfg.fdqThresh[0].fEnable    = 0U;       /* Set through optional config */
    flowCfg.fdqThresh[0].pktSize    = 0U;       /* Set through optional config */
    flowCfg.fdqThresh[0].queue      = req->rx_fdq0_sz0_qnum;
    flowCfg.fdq[0]                  = req->rx_fdq0_sz0_qnum;
    flowCfg.fdqThresh[1].fEnable    = 0U;
    flowCfg.fdqThresh[1].pktSize    = 0U;       /* Set through optional config */
    flowCfg.fdqThresh[1].queue      = req->rx_fdq1_qnum;
    flowCfg.fdq[1]                  = req->rx_fdq1_qnum;
    flowCfg.fdqThresh[2].fEnable    = 0U;       /* Set through optional config */
    flowCfg.fdqThresh[2].pktSize    = 0U;       /* Set through optional config */
    flowCfg.fdqThresh[2].queue      = req->rx_fdq2_qnum;
    flowCfg.fdq[2]                  = req->rx_fdq2_qnum;
    flowCfg.fdqThresh[3].fEnable    = 0U;   /* Not Used */
    flowCfg.fdqThresh[3].pktSize    = 0U;   /* Not Used */
    flowCfg.fdqThresh[3].queue      = req->rx_fdq3_qnum;
    flowCfg.fdq[3]                  = req->rx_fdq3_qnum;
    CSL_udmapRxFlowCfg(&rmObj->udmapRegs, req->flow_index, &flowCfg);

    return (retVal);
}

int32_t Sciclient_rmUdmapFlowSizeThreshCfg(
            const struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req *req,
            const struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp *resp,
            uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;
    uint32_t        regVal;
    SciUdmaRmObj   *rmObj;

    rmObj = &gSciUdmaRmObjMain;
#if defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    if(TISCI_DEV_MCU_NAVSS0_UDMAP_0 == req->nav_id)
#else
    if(TISCI_DEV_MCU_NAVSS0_UDMAP0 == req->nav_id)
#endif
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    regVal = CSL_REG32_RD(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFC);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFC_SIZE_THRESH_EN, req->rx_size_thresh_en);
    CSL_REG32_WR(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFC, regVal);

    regVal = CSL_REG32_RD(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFF);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFF_SIZE_THRESH0, req->rx_size_thresh0);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFF_SIZE_THRESH1, req->rx_size_thresh1);
    CSL_REG32_WR(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFF, regVal);

    regVal = CSL_REG32_RD(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFG);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFG_SIZE_THRESH2, req->rx_size_thresh2);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFG_FDQ0_SZ1_QNUM, req->rx_fdq0_sz1_qnum);
    CSL_REG32_WR(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFG, regVal);

    regVal = CSL_REG32_RD(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFH);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFH_FDQ0_SZ2_QNUM, req->rx_fdq0_sz2_qnum);
    CSL_FINS(regVal, UDMAP_RXFCFG_FLOW_RFH_FDQ0_SZ2_QNUM, req->rx_fdq0_sz3_qnum);
    CSL_REG32_WR(&rmObj->udmapRegs.pRxFlowCfgRegs->FLOW[req->flow_index].RFH, regVal);

    return (retVal);
}

int32_t Sciclient_rmPsilPair(const struct tisci_msg_rm_psil_pair_req *req,
                             uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;
    uint32_t        chIdx;
    bool            cslRetVal;
    SciUdmaRmObj   *rmObj;

    rmObj = &gSciUdmaRmObjMain;
    if(TISCI_DEV_MCU_NAVSS0 == req->nav_id)
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    /* Pair source thread with destination thread */
    cslRetVal = CSL_psilcfgCreateRoute(
                    rmObj->psilCfgRegs, req->src_thread, req->dst_thread);
    if(TRUE != cslRetVal)
    {
        retVal = CSL_EFAIL;
    }

    if((req->src_thread >= rmObj->txUdmaThreadIdStart) &&
       (req->src_thread <= rmObj->txUdmaThreadIdEnd))
    {
        /* Program peer thread ID to TX channel */
        chIdx = req->src_thread - rmObj->txUdmaThreadIdStart;
        CSL_REG32_WR(&rmObj->udmapRegs.pTxChanCfgRegs->CHAN[chIdx].THREAD, req->dst_thread);
    }
    if((req->dst_thread >= rmObj->rxUdmaThreadIdStart) &&
       (req->dst_thread <= rmObj->rxUdmaThreadIdEnd))
    {
        /* Program peer thread ID to RX channel */
        chIdx = req->dst_thread - rmObj->rxUdmaThreadIdStart;
        CSL_REG32_WR(&rmObj->udmapRegs.pRxChanCfgRegs->CHAN[chIdx].THREAD, req->src_thread);
    }

    return (retVal);
}

int32_t Sciclient_rmPsilUnpair(const struct tisci_msg_rm_psil_unpair_req *req,
                               uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;
    bool            cslRetVal;
    SciUdmaRmObj   *rmObj;

    rmObj = &gSciUdmaRmObjMain;
    if(TISCI_DEV_MCU_NAVSS0 == req->nav_id)
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    cslRetVal = CSL_psilcfgSetThreadRealtimeEnable(
                    rmObj->psilCfgRegs, req->src_thread, FALSE);
    if(TRUE != cslRetVal)
    {
        retVal = CSL_EFAIL;
    }

    cslRetVal = CSL_psilcfgSetThreadRealtimeEnable(
                    rmObj->psilCfgRegs, req->dst_thread, FALSE);
    if(TRUE != cslRetVal)
    {
        retVal = CSL_EFAIL;
    }

    return (retVal);
}

int32_t Sciclient_rmUdmapGcfgCfg(
            const struct tisci_msg_rm_udmap_gcfg_cfg_req *req,
            const struct tisci_msg_rm_udmap_gcfg_cfg_resp *resp,
            uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;

    /* Not required to be supported in CSL method. Just return pass */

    return (retVal);
}

int32_t Sciclient_rmPsilRead(const struct tisci_msg_rm_psil_read_req *req,
                             struct tisci_msg_rm_psil_read_resp *resp,
                             uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;
    bool            cslRetVal;
    SciUdmaRmObj   *rmObj;

    rmObj = &gSciUdmaRmObjMain;
    if(TISCI_DEV_MCU_NAVSS0 == req->nav_id)
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    cslRetVal = CSL_psilcfgRead(
                    rmObj->psilCfgRegs,
                    req->thread,
                    req->taddr,
                    &resp->data);
    if(TRUE != cslRetVal)
    {
        retVal = CSL_EFAIL;
    }

    return (retVal);
}

int32_t Sciclient_rmPsilWrite(const struct tisci_msg_rm_psil_write_req *req,
                              uint32_t timeout)
{
    int32_t         retVal = CSL_PASS;
    bool            cslRetVal;
    SciUdmaRmObj   *rmObj;

    rmObj = &gSciUdmaRmObjMain;
    if(TISCI_DEV_MCU_NAVSS0 == req->nav_id)
    {
        rmObj = &gSciUdmaRmObjMcu;
    }

    cslRetVal = CSL_psilcfgWrite(
                    rmObj->psilCfgRegs,
                    req->thread,
                    req->taddr,
                    req->data);
    if(TRUE != cslRetVal)
    {
        retVal = CSL_EFAIL;
    }

    return (retVal);
}


/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
