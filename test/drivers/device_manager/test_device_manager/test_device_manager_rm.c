/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_ra.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_udmap.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_irq.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_shared.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_psil.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_proxy.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_device_manager_rm.h"

/* ========================================================================== */
/*            Helper Function Implementations - RM Tests                      */
/* ========================================================================== */

static int32_t test_msgRmRingCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_ring_cfg_req  request;
    struct tisci_msg_rm_ring_cfg_resp response;

    /* TC-01: Positive - valid_params=0 (no-op permission check) on owned ring.*/
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_BCDMA_DEV_ID;
        request.index        = (uint16_t) TEST_RM_BCDMA_RING_IDX;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingCfg TC-01 Positive - valid_params=0 on owned ring idx=%u: retVal=%d flags=0x%x\r\n",
                       request.index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_BCDMA_DEV_ID;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingCfg TC-02 Negative - ring 0 not owned by MAIN_0_R5_1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingCfg TC-03 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingCfg TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmRingMonCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_ring_mon_cfg_req  request;
    struct tisci_msg_rm_ring_mon_cfg_resp response;

    /* TC-01: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_MON_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingMonCfg TC-01 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_RING_MON_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmRingMonCfg TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapTxChCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_tx_ch_cfg_req  request;
    struct tisci_msg_rm_udmap_tx_ch_cfg_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id            = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.index             = (uint16_t) TEST_RM_PKTDMA_TX_CH_IDX;
        request.valid_params      = 0xffffU;
        request.tx_pause_on_err   = 1U;
        request.tx_filt_einfo     = 1U;
        request.tx_filt_pswords   = 1U;
        request.tx_atype          = 2U;
        request.tx_chan_type       = 2U;
        request.tx_supr_tdpkt     = 1U;
        request.tx_fetch_size     = 64U;
        request.tx_credit_count   = 1U;
        request.txcq_qnum         = 0U;
        request.tx_priority       = 1U;
        request.tx_qos            = 1U;
        request.tx_orderid        = 1U;
        request.fdepth            = 64U;
        request.tx_sched_priority = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_TX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapTxChCfg TC-01 Positive - PKTDMA unmapped TX ch idx=%u: retVal=%d flags=0x%x\r\n",
                       request.index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - channel 0 is owned by A53_2, not MAIN_0_R5_1 */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_TX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapTxChCfg TC-02 Negative - ch 0 not owned by MAIN_0_R5_1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_TX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapTxChCfg TC-03 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_TX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapTxChCfg TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapRxChCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_rx_ch_cfg_req  request;
    struct tisci_msg_rm_udmap_rx_ch_cfg_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id            = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.index             = (uint16_t) TEST_RM_PKTDMA_RX_CH_IDX;
        request.valid_params      = 0x5fffU;
        request.rx_fetch_size     = 64U;
        request.rxcq_qnum         = 0U;
        request.rx_priority       = 1U;
        request.rx_qos            = 1U;
        request.rx_orderid        = 1U;
        request.rx_sched_priority = 1U;
        request.flowid_start      = 0U;
        request.flowid_cnt        = 4U;
        request.rx_pause_on_err   = 1U;
        request.rx_atype          = 2U;
        request.rx_chan_type       = 2U;
        request.rx_ignore_short   = 1U;
        request.rx_ignore_long    = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_RX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapRxChCfg TC-01 Positive - PKTDMA unmapped RX ch idx=%u: retVal=%d flags=0x%x\r\n",
                       request.index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - channel 0 is owned by A53_2, not MAIN_0_R5_1 */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_RX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapRxChCfg TC-02 Negative - ch 0 not owned by MAIN_0_R5_1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_RX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapRxChCfg TC-03 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_RX_CH_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapRxChCfg TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapFlowCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_flow_cfg_req  request;
    struct tisci_msg_rm_udmap_flow_cfg_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id               = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.flow_index           = (uint16_t) TEST_RM_PKTDMA_FLOW_IDX;
        request.valid_params         = 0x7ffffU;
        request.rx_einfo_present     = 1U;
        request.rx_psinfo_present    = 1U;
        request.rx_error_handling    = 0U;
        request.rx_desc_type         = 0U;
        request.rx_sop_offset        = 32U;
        request.rx_dest_qnum         = 0U;
        request.rx_src_tag_hi        = 4U;
        request.rx_src_tag_lo        = 3U;
        request.rx_dest_tag_hi       = 2U;
        request.rx_dest_tag_lo       = 1U;
        request.rx_src_tag_hi_sel    = 0U;
        request.rx_src_tag_lo_sel    = 0U;
        request.rx_dest_tag_hi_sel   = 0U;
        request.rx_dest_tag_lo_sel   = 0U;
        request.rx_fdq0_sz0_qnum     = 1U;
        request.rx_fdq1_qnum         = 2U;
        request.rx_fdq2_qnum         = 3U;
        request.rx_fdq3_qnum         = 4U;
        request.rx_ps_location       = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowCfg TC-01 Positive - PKTDMA unmapped RX flow idx=%u: retVal=%d flags=0x%x\r\n",
                       request.flow_index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - flow 0 is not owned by MAIN_0_R5_1 */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.flow_index   = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowCfg TC-02 Negative - flow 0 not owned by MAIN_0_R5_1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.flow_index   = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowCfg TC-03 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowCfg TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapFlowSizeThreshCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req  request;
    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.flow_index   = (uint16_t) TEST_RM_PKTDMA_FLOW_IDX;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowSizeThreshCfg TC-01 Positive - valid_params=0 on PKTDMA flow idx=%u: retVal=%d flags=0x%x\r\n",
                       request.flow_index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowSizeThreshCfg TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapFlowDelegate(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_flow_delegate_req  request;
    struct tisci_msg_rm_udmap_flow_delegate_resp response;

    /* TC-01: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.dev_id       = 0xFFFFU;
        request.flow_index   = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_DELEGATE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowDelegate TC-01 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_FLOW_DELEGATE,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapFlowDelegate TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmUdmapGcfgCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_udmap_gcfg_cfg_req  request;
    struct tisci_msg_rm_udmap_gcfg_cfg_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id      = (uint16_t) TEST_RM_NAV_PKTDMA_DEV_ID;
        request.valid_params = 0xfU;
        request.perf_ctrl   = 0x20U;
        request.emu_ctrl    = 0x1U;
        request.psil_to     = 0x200U;
        request.rflowfwstat = 0x0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_GCFG_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapGcfgCfg TC-01 Positive - PKTDMA GCFG valid_params=0xf: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_GCFG_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapGcfgCfg TC-02 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_UDMAP_GCFG_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmUdmapGcfgCfg TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmIrqSet(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_irq_set_req  request;
    struct tisci_msg_rm_irq_set_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                 TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                 TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        request.src_id         = (uint16_t) TEST_RM_IRQ_SRC_DEV_ID;
        request.src_index      = (uint16_t) TEST_RM_IRQ_SRC_INDEX;
        request.dst_id         = (uint16_t) TEST_RM_IRQ_DST_DEV_ID;
        request.dst_host_irq   = (uint16_t) TEST_RM_IRQ_DST_HOST_IRQ;
        request.secondary_host = (uint8_t)  TEST_RM_IRQ_SECONDARY_HOST;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_SET,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqSet TC-01 Positive - IR mux route via GPIOMUX_INTROUTER0 src=%u dst=%u: retVal=%d flags=0x%x\r\n",
                       request.src_index, request.dst_host_irq,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - invalid src_id (0xFFFF not a valid TISCI device) */
    {
        memset(&request, 0, sizeof(request));
        request.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                 TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                 TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        request.src_id         = 0xFFFFU;
        request.src_index      = (uint16_t) TEST_RM_IRQ_SRC_INDEX;
        request.dst_id         = (uint16_t) TEST_RM_IRQ_DST_DEV_ID;
        request.dst_host_irq   = (uint16_t) TEST_RM_IRQ_DST_HOST_IRQ;
        request.secondary_host = (uint8_t)  TEST_RM_IRQ_SECONDARY_HOST;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_SET,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqSet TC-02 Negative - invalid src_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_SET,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqSet TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmIrqRelease(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_irq_release_req  request;
    struct tisci_msg_rm_irq_release_resp response;

    /* TC-01: Positive */
    {
        memset(&request, 0, sizeof(request));
        request.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                 TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                 TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        request.src_id         = (uint16_t) TEST_RM_IRQ_SRC_DEV_ID;
        request.src_index      = (uint16_t) TEST_RM_IRQ_SRC_INDEX;
        request.dst_id         = (uint16_t) TEST_RM_IRQ_DST_DEV_ID;
        request.dst_host_irq   = (uint16_t) TEST_RM_IRQ_DST_HOST_IRQ;
        request.secondary_host = (uint8_t)  TEST_RM_IRQ_SECONDARY_HOST;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_RELEASE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqRelease TC-01 Positive - release GPIOMUX_INTROUTER0 route src=%u: retVal=%d flags=0x%x\r\n",
                       request.src_index,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - invalid src_id (0xFFFF not a valid TISCI device) */
    {
        memset(&request, 0, sizeof(request));
        request.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                 TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                 TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        request.src_id         = 0xFFFFU;
        request.src_index      = (uint16_t) TEST_RM_IRQ_SRC_INDEX;
        request.dst_id         = (uint16_t) TEST_RM_IRQ_DST_DEV_ID;
        request.dst_host_irq   = (uint16_t) TEST_RM_IRQ_DST_HOST_IRQ;
        request.secondary_host = (uint8_t)  TEST_RM_IRQ_SECONDARY_HOST;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_RELEASE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqRelease TC-02 Negative - invalid src_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_IRQ_RELEASE,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmIrqRelease TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmPsilPair(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_psil_pair_req  request;
    struct tisci_msg_rm_psil_pair_resp response;

    /* TC-01: Positive */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.nav_id     = TEST_RM_PSIL_NAV_ID;
        request.src_thread = TEST_RM_PSIL_SRC_THREAD;
        request.dst_thread = TEST_RM_PSIL_DST_THREAD;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_PAIR,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilPair TC-01 Positive - pair TX 0x%04x to RX 0x%04x: retVal=%d flags=0x%x\r\n",
                       request.src_thread, request.dst_thread,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - dst_thread=0x0001 (< 0x8000 — spec mandates NACK) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.nav_id     = TEST_RM_PSIL_NAV_ID;
        request.src_thread = 0x0000U;
        request.dst_thread = 0x0001U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_PAIR,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilPair TC-02 Negative - dst_thread 0x0001 < 0x8000: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_PAIR,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilPair TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - invalid nav_id (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.nav_id     = 0xFFFFU;
        request.src_thread = TEST_RM_PSIL_SRC_THREAD;
        request.dst_thread = TEST_RM_PSIL_DST_THREAD;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_PAIR,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilPair TC-04 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmPsilUnpair(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_psil_unpair_req  request;
    struct tisci_msg_rm_psil_unpair_resp response;

    /* TC-01: Positive - unpair the threads paired in test_msgRmPsilPair TC-01.
     * After unpairing, both threads are NRT-disabled. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.nav_id     = TEST_RM_PSIL_NAV_ID;
        request.src_thread = TEST_RM_PSIL_SRC_THREAD;
        request.dst_thread = TEST_RM_PSIL_DST_THREAD;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_UNPAIR,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilUnpair TC-01 Positive - unpair TX 0x%04x / RX 0x%04x: retVal=%d flags=0x%x\r\n",
                       request.src_thread, request.dst_thread,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - dst_thread=0x0001 (< 0x8000 — spec mandates NACK) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.nav_id     = TEST_RM_PSIL_NAV_ID;
        request.src_thread = 0x0000U;
        request.dst_thread = 0x0001U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_UNPAIR,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilUnpair TC-02 Negative - dst_thread 0x0001 < 0x8000: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_UNPAIR,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilUnpair TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmPsilRead(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_psil_read_req  request;
    struct tisci_msg_rm_psil_read_resp response;

    /* TC-01: Positive */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.valid_params = 0U;
        request.nav_id       = (uint16_t) TEST_RM_PSIL_NAV_ID;
        request.thread       = (uint16_t) TEST_RM_PSIL_SRC_THREAD;
        request.taddr        = (uint16_t) TEST_RM_PSIL_TADDR;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_READ,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilRead TC-01 Positive - read thread 0x%04x taddr=0x%x: retVal=%d flags=0x%x\r\n",
                       request.thread, request.taddr,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - invalid nav_id=0xFFFF */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.valid_params = 0U;
        request.nav_id       = (uint16_t) 0xFFFFU;
        request.thread       = (uint16_t) 0x0000U;
        request.taddr        = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_READ,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilRead TC-02 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_READ,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilRead TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmPsilWrite(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_psil_write_req  writeRequest;
    struct tisci_msg_rm_psil_write_resp writeResponse;
    struct tisci_msg_rm_psil_read_req   readRequest;
    struct tisci_msg_rm_psil_read_resp  readResponse;

    /* TC-01: Positive - write known value 0x80000000 to thread 0x100B, taddr=0x2. */
    {
        memset(&writeRequest,  0, sizeof(writeRequest));
        memset(&writeResponse, 0, sizeof(writeResponse));
        writeRequest.valid_params = 0U;
        writeRequest.nav_id       = (uint16_t) TEST_RM_PSIL_NAV_ID;
        writeRequest.thread       = (uint16_t) TEST_RM_PSIL_SRC_THREAD;
        writeRequest.taddr        = (uint16_t) TEST_RM_PSIL_TADDR;
        writeRequest.data         = TEST_RM_PSIL_WRITE_DATA;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_WRITE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &writeRequest,
            sizeof(writeRequest),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &writeResponse,
            sizeof(writeResponse)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilWrite TC-01 Positive - write 0x%08x to thread 0x%04x taddr=0x%x: retVal=%d flags=0x%x\r\n",
                       writeRequest.data, writeRequest.thread, writeRequest.taddr,
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Positive - READ back taddr=0x2 to verify response.data==0x80000000. */
    {
        memset(&readRequest,  0, sizeof(readRequest));
        memset(&readResponse, 0, sizeof(readResponse));
        readRequest.valid_params = 0U;
        readRequest.nav_id       = (uint16_t) TEST_RM_PSIL_NAV_ID;
        readRequest.thread       = (uint16_t) TEST_RM_PSIL_SRC_THREAD;
        readRequest.taddr        = (uint16_t) TEST_RM_PSIL_TADDR;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_READ,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &readRequest,
            sizeof(readRequest),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &readResponse,
            sizeof(readResponse)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilWrite TC-02 Positive - readback thread 0x%04x taddr=0x%x: retVal=%d flags=0x%x\r\n",
                       readRequest.thread, readRequest.taddr,
                       retVal, respPrm.flags);
            failCount++;
        }
        if ((uint32_t)(readResponse.data) != (uint32_t)(TEST_RM_PSIL_WRITE_DATA))
        {
            DebugP_log("FAIL: test_msgRmPsilWrite TC-02: expected=%d actual=%d\r\n",
                       (int32_t)(uint32_t)(TEST_RM_PSIL_WRITE_DATA), (int32_t)(uint32_t)(readResponse.data));
            failCount++;
        }
    }

    /* TC-03: Negative - invalid nav_id=0xFFFF */
    {
        memset(&writeRequest,  0, sizeof(writeRequest));
        memset(&writeResponse, 0, sizeof(writeResponse));
        writeRequest.valid_params = 0U;
        writeRequest.nav_id       = (uint16_t) 0xFFFFU;
        writeRequest.thread       = (uint16_t) 0x0000U;
        writeRequest.taddr        = 0U;
        writeRequest.data         = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_WRITE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &writeRequest,
            sizeof(writeRequest),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &writeResponse,
            sizeof(writeResponse)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilWrite TC-03 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PSIL_WRITE,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &writeResponse,
            sizeof(writeResponse)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmPsilWrite TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmProxyCfg(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_proxy_cfg_req  request;
    struct tisci_msg_rm_proxy_cfg_resp response;

    /* TC-01: Negative */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = (uint16_t) TEST_RM_NAV_BCDMA_DEV_ID;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PROXY_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

          retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmProxyCfg TC-01 Negative - no proxy resources for MAIN_0_R5_1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - invalid nav_id */
    {
        memset(&request, 0, sizeof(request));
        request.nav_id       = 0xFFFFU;
        request.index        = 0U;
        request.valid_params = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PROXY_CFG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmProxyCfg TC-02 Negative - invalid nav_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_PROXY_CFG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmProxyCfg TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

static int32_t test_msgRmGetResourceRange(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_rm_get_resource_range_req  request;
    struct tisci_msg_rm_get_resource_range_resp response;

    /* TC-01: Positive - query IA_VINT resources for INTAGGR_0 */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.type           = TEST_RM_NAV_INTAGGR_DEV_ID;
        request.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        request.secondary_host = TISCI_HOST_ID_ALL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_GET_RESOURCE_RANGE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmGetResourceRange TC-01 Positive - IA_VINT for INTAGGR_0 host=ALL: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative - NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_GET_RESOURCE_RANGE,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmGetResourceRange TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative - invalid device type (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.type           = 0xFFFFU;
        request.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        request.secondary_host = TISCI_HOST_ID_ALL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_GET_RESOURCE_RANGE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmGetResourceRange TC-03 Negative - invalid device type 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative - invalid subtype (0xFF) with valid type */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.type           = TEST_RM_NAV_INTAGGR_DEV_ID;
        request.subtype        = 0xFFU;
        request.secondary_host = TISCI_HOST_ID_ALL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_RM_GET_RESOURCE_RANGE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgRmGetResourceRange TC-04 Negative - invalid subtype 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    
    return failCount;
}

/* ========================================================================== */
/*            Test Wrapper Function Implementations                         */
/* ========================================================================== */

void testDM_rmProxy(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgRmProxyCfg(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

void testDM_rmResourceRange(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgRmGetResourceRange(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

void testDM_rmRing(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgRmRingCfg(NULL);
    testfailcount += test_msgRmRingMonCfg(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

void testDM_rmUdmap(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgRmUdmapTxChCfg(NULL);
    testfailcount += test_msgRmUdmapRxChCfg(NULL);
    testfailcount += test_msgRmUdmapFlowCfg(NULL);
    testfailcount += test_msgRmUdmapFlowSizeThreshCfg(NULL);
    testfailcount += test_msgRmUdmapFlowDelegate(NULL);
    testfailcount += test_msgRmUdmapGcfgCfg(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

void testDM_rmIrqPsil(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgRmIrqSet(NULL);
    testfailcount += test_msgRmIrqRelease(NULL);
    testfailcount += test_msgRmPsilPair(NULL);
    testfailcount += test_msgRmPsilUnpair(NULL);
    testfailcount += test_msgRmPsilRead(NULL);
    testfailcount += test_msgRmPsilWrite(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}
