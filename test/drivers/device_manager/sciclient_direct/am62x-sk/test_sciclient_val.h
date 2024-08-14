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
 *
 */

/**
 *  \file test_sciclient_val.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the sciclient UT applications.
 */

#ifndef TEST_SCICLIENT_VAL_H_
#define TEST_SCICLIENT_VAL_H_

/*===========================================================================*/
/*                                    Macros                                 */
/*===========================================================================*/

#define TEST_SCICLIENT_PROC_ID                 SCICLIENT_PROC_ID_R5FSS0_CORE0

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "../test_device_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Internal Variables                             */
/* ========================================================================== */

typedef struct {
    uint32_t comp_type;
    uint32_t boot_core;
    uint32_t comp_opts;
    uint64_t dest_addr;
    uint32_t comp_size;
} Sciclient_DirectExtBootX509Comp;

typedef struct {
    uint8_t                             magic_word[8];
    uint32_t                            num_comps;
    Sciclient_DirectExtBootX509Comp     comps[8];
} Sciclient_DirectExtBootX509Table;

typedef struct {
    uint16_t type;
    uint16_t offset;
    uint16_t size;
    uint8_t  devgrp;
    uint8_t  reserved;
} __attribute__((__packed__)) Sciclient_DirectExtBootBoardCfgDesc ;

typedef struct {
    uint8_t                                 num_elems;
    uint8_t                                 sw_rev;
    Sciclient_DirectExtBootBoardCfgDesc     descs[8];
} __attribute__((__packed__)) Sciclient_DirectBoardCfgDescTable;

static const uint8_t r5_cl0_c0_binary_hs[] = {
#include "test_sciclient_r5_cl0_c0_image.h"
};

static const uint8_t a53_cl0_c0_binary_hs[] = {
#include "test_sciclient_a53_cl0_c0_image.h"
};

static const uint8_t bcfg_rm_consumed_by_tifs[] = {
#include "test_sciclient_bcfg_rm_tifs.h"
};

static const uint8_t bcfg_rm_consumed_by_tifs_and_dm[] = {
#include "test_sciclient_bcfg_rm_dm_tifs.h"
};

/* ========================================================================== */
/*                             External Variables                             */
/* ========================================================================== */

extern Sciclient_ServiceHandle_t gSciclientHandle;
extern struct tisci_msg_proc_set_config_req configReq;
extern struct tisci_msg_fwl_set_firewall_region_resp  setFwResp;
extern struct tisci_msg_fwl_set_firewall_region_req setFwReq;
extern struct tisci_msg_proc_set_config_req configReq3;
struct tisci_msg_proc_set_config_req configReq2_1;
extern struct tisci_msg_proc_set_config_req configReq2;
extern Sciclient_RespPrm_t respParam1;
extern Sciclient_ReqPrm_t reqParam1 ;
extern struct tisci_msg_fwl_get_firewall_region_resp fwGetResp;
extern struct tisci_msg_fwl_get_firewall_region_req fwGetReq;
extern struct tisci_msg_fwl_change_owner_info_req fwCngOwnerInfoReq;
extern struct tisci_msg_fwl_set_firewall_region_resp  setFwResp2;
extern struct tisci_msg_fwl_set_firewall_region_req setFwReq2;
extern struct tisci_msg_fwl_change_owner_info_req fwCngOwnerInfoReq2;
extern Sciclient_ReqPrm_t kwProgReqParam;
extern Sciclient_RespPrm_t kwProgRespParam;
extern Sciclient_RespPrm_t writeOTPRowRespParam;
extern Sciclient_ReqPrm_t writeOTPRowReqParam;
extern Sciclient_RespPrm_t readOtpRespParam1;
extern Sciclient_ReqPrm_t readOtpReqParam1;
extern Sciclient_ReqPrm_t setIOIsolationReqParam;
extern Sciclient_RespPrm_t setIOIsolationRespParam;
extern Sciclient_ReqPrm_t prepSleepPassReqParam1;
extern Sciclient_RespPrm_t prepSleepPassRespParam1;
extern Sciclient_ReqPrm_t prepSleepPassReqParam2;
extern Sciclient_RespPrm_t prepSleepPassRespParam2;
extern Sciclient_ReqPrm_t prepSleepFailReqParam1;
extern Sciclient_RespPrm_t prepSleepFailRespParam1;
extern Sciclient_ReqPrm_t prepSleepFailReqParam2;
extern Sciclient_RespPrm_t prepSleepFailRespParam2;
extern Sciclient_ReqPrm_t setDevReqParam2;
extern Sciclient_RespPrm_t setDevRespParam2;
extern Sciclient_ReqPrm_t setDevReqParam1;
extern Sciclient_RespPrm_t setDevRespParam1;
extern Sciclient_ReqPrm_t setDevRstReqParam;
extern Sciclient_RespPrm_t setDevRstRespParam;
extern Sciclient_ReqPrm_t setDevReqParam;
extern Sciclient_RespPrm_t setDevRespParam;
extern struct tisci_header mockTxMsg ;
extern struct tisci_msg_rm_irq_set_req mock_req;
extern Sciclient_RespPrm_t readOtpRespParam2;
extern Sciclient_ReqPrm_t readOtpReqParam2;
extern Sciclient_RespPrm_t RespParam;
extern Sciclient_ReqPrm_t ReqParam;
extern Sciclient_DirectExtBootX509Table mockX509TblMagicWord;
extern Sciclient_DirectExtBootX509Table mockX509Tbl;
extern Sciclient_DirectExtBootX509Table mockX509Tbl;
extern Sciclient_DirectExtBootX509Comp mockBootComp;
extern Sciclient_RespPrm_t queryFwCapsRespParam;
extern Sciclient_ReqPrm_t queryFwCapsReqParam;
extern Sciclient_ReqPrm_t reqParam2;
extern Sciclient_RespPrm_t respParam2;
extern const Sciserver_hwiData uhd1[];
extern const Sciserver_taskData utdTest1[];

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*None*/

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
