/*
 * Copyright (c) 2018-2020, Texas Instruments Incorporated
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
 *  \file sciclient_boardcfg.c
 *
 *  \brief File containing the APIs to send board configuration
 *       messages.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/CacheP.h>
//#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined (BUILD_DM_R5)
#if !defined (MCU_PLUS_SDK)
const uint32_t gSciclient_boardCfgLow[(SCICLIENT_BOARDCFG_SIZE_IN_BYTES+3U)/4U]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG;
const uint32_t gSciclient_boardCfgLow_rm[(SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES+3U)/4U]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_RM;
const uint32_t gSciclient_boardCfgLow_sec[(SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES+3U)/4U]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_SECURITY;
const uint32_t gSciclient_boardCfgLow_pm[(SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES+3U)/4U]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_PM;
#else
const uint32_t gSciclient_boardCfgLow[SCICLIENT_BOARDCFG_SIZE_IN_BYTES]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG;
const uint32_t gSciclient_boardCfgLow_rm[SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_RM;
const uint32_t gSciclient_boardCfgLow_sec[SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_SECURITY;
const uint32_t gSciclient_boardCfgLow_pm[SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_PM;
#endif

int32_t Sciclient_boardCfg(const Sciclient_BoardCfgPrms_t * pInPrms)
{
    int32_t retVal = CSL_PASS;
    struct tisci_msg_board_config_req request = {
        .tisci_boardcfgp_low  = (uint32_t) gSciclient_boardCfgLow,
        .tisci_boardcfgp_high = (uint32_t) 0x0U,
        .tisci_boardcfg_size  = (uint16_t) SCICLIENT_BOARDCFG_SIZE_IN_BYTES,
        .tisci_boardcfg_devgrp = (uint8_t) DEVGRP_ALL
    };

    /* NULL pInPrms will retain default values */
    if (pInPrms != NULL)
    {
        request.tisci_boardcfgp_low = pInPrms->boardConfigLow;
        request.tisci_boardcfgp_high = pInPrms->boardConfigHigh;
        request.tisci_boardcfg_size = pInPrms->boardConfigSize;
        request.tisci_boardcfg_devgrp = pInPrms->devGrp;
    }

    Sciclient_ReqPrm_t reqParam = {
        .messageType    = (uint16_t) TISCI_MSG_BOARD_CONFIG,
        .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
        .pReqPayload    = (const uint8_t *) &request,
        .reqPayloadSize = (uint32_t) sizeof (request),
        .timeout        = (uint32_t) SCICLIENT_SERVICE_WAIT_FOREVER
    };
    Sciclient_RespPrm_t respParam = {
        .flags           = (uint32_t) 0,   /* Populated by the API */
        .pRespPayload    = (uint8_t *) 0,
        .respPayloadSize = (uint32_t) 0
    };
#if !defined(MCU_PLUS_SDK)
    CacheP_wbInv((const void*) request.tisci_boardcfgp_low, request.tisci_boardcfg_size);

#else
    CacheP_wbInv((void*)request.tisci_boardcfgp_low,
                request.tisci_boardcfg_size,CacheP_TYPE_ALL);
#endif
    if((CSL_PASS != Sciclient_service(&reqParam, &respParam))
        || ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK))
    {
        retVal = CSL_EFAIL;
    }

    return retVal;
}

int32_t Sciclient_boardCfgPm(const Sciclient_BoardCfgPrms_t * pInPrms)
{
    int32_t retVal = CSL_PASS;
    struct tisci_msg_board_config_pm_req request = {
        .tisci_boardcfg_pmp_low  = (uint32_t) gSciclient_boardCfgLow_pm, /* PM Board Config structure
                                                 definition removed from TISCI */
        .tisci_boardcfg_pmp_high = (uint32_t) 0x0U,
        .tisci_boardcfg_pm_size  = (uint16_t) SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES,
        .tisci_boardcfg_pm_devgrp = (uint8_t) DEVGRP_ALL

    };

    /* NULL pInPrms will retain default values */
    if (pInPrms != NULL)
    {
        request.tisci_boardcfg_pmp_low = pInPrms->boardConfigLow;
        request.tisci_boardcfg_pmp_high = pInPrms->boardConfigHigh;
        request.tisci_boardcfg_pm_size = pInPrms->boardConfigSize;
        request.tisci_boardcfg_pm_devgrp = pInPrms->devGrp;
    }

    Sciclient_ReqPrm_t reqParam = {
        .messageType    = (uint16_t) TISCI_MSG_BOARD_CONFIG_PM,
        .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
        .pReqPayload    = (const uint8_t *) &request,
        .reqPayloadSize = (uint32_t) sizeof (request),
        .timeout        = (uint32_t) SCICLIENT_SERVICE_WAIT_FOREVER
    };
    Sciclient_RespPrm_t respParam = {
        .flags           = (uint32_t) 0,   /* Populated by the API */
        .pRespPayload    = (uint8_t *) 0,
        .respPayloadSize = (uint32_t) 0
    };
#if !defined(MCU_PLUS_SDK)
    CacheP_wbInv((const void*) request.tisci_boardcfg_pmp_low, request.tisci_boardcfg_pm_size);
#else
    CacheP_wbInv((void*)request.tisci_boardcfg_pmp_low,
                request.tisci_boardcfg_pm_size,CacheP_TYPE_ALL);
#endif
    if((CSL_PASS != Sciclient_service(&reqParam, &respParam))
        || ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK))
    {
        retVal = CSL_EFAIL;
    }
    return retVal;
}

int32_t Sciclient_boardCfgRm(const Sciclient_BoardCfgPrms_t * pInPrms)
{
    int32_t retVal = CSL_PASS;

    struct tisci_msg_board_config_rm_req request = {
        .tisci_boardcfg_rmp_low  = (uint32_t) gSciclient_boardCfgLow_rm,
        .tisci_boardcfg_rmp_high = (uint32_t) 0x0U,
        .tisci_boardcfg_rm_size  = (uint16_t) SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
        .tisci_boardcfg_rm_devgrp = (uint8_t) DEVGRP_ALL
    };

    /* NULL pInPrms will retain default values */
    if (pInPrms != NULL)
    {
        request.tisci_boardcfg_rmp_low = pInPrms->boardConfigLow;
        request.tisci_boardcfg_rmp_high = pInPrms->boardConfigHigh;
        request.tisci_boardcfg_rm_size = pInPrms->boardConfigSize;
        request.tisci_boardcfg_rm_devgrp = pInPrms->devGrp;
    }

    Sciclient_ReqPrm_t reqParam = {
        .messageType    = (uint16_t) TISCI_MSG_BOARD_CONFIG_RM,
        .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
        .pReqPayload    = (const uint8_t *) &request,
        .reqPayloadSize = (uint32_t) sizeof (request),
        .timeout        = (uint32_t) SCICLIENT_SERVICE_WAIT_FOREVER
    };
    Sciclient_RespPrm_t respParam = {
        .flags           = (uint32_t) 0,   /* Populated by the API */
        .pRespPayload    = (uint8_t *) 0,
        .respPayloadSize = (uint32_t) 0
    };
#if !defined(MCU_PLUS_SDK)
    CacheP_wbInv((const void*) request.tisci_boardcfg_rmp_low, request.tisci_boardcfg_rm_size);
#else
    CacheP_wbInv((void*)request.tisci_boardcfg_rmp_low,
                request.tisci_boardcfg_rm_size,CacheP_TYPE_ALL);
#endif
    if((CSL_PASS != Sciclient_service(&reqParam, &respParam))
        || ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK))
    {
        retVal = CSL_EFAIL;
    }
    return retVal;
}

int32_t Sciclient_boardCfgSec(const Sciclient_BoardCfgPrms_t * pInPrms)
{
    int32_t retVal = CSL_PASS;
    struct tisci_msg_board_config_security_req request = {
        .tisci_boardcfg_securityp_low  = (uint32_t) gSciclient_boardCfgLow_sec,
        .tisci_boardcfg_securityp_high = (uint32_t) 0x0U,
        .tisci_boardcfg_security_size  = (uint16_t) SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES,
        .tisci_boardcfg_security_devgrp = (uint8_t) DEVGRP_ALL
    };

    /* NULL pInPrms will retain default values */
    if (pInPrms != NULL)
    {
        request.tisci_boardcfg_securityp_low = pInPrms->boardConfigLow;
        request.tisci_boardcfg_securityp_high = pInPrms->boardConfigHigh;
        request.tisci_boardcfg_security_size = pInPrms->boardConfigSize;
        request.tisci_boardcfg_security_devgrp = pInPrms->devGrp;
    }

    Sciclient_ReqPrm_t reqParam = {
        .messageType    = (uint16_t) TISCI_MSG_BOARD_CONFIG_SECURITY,
        .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
        .pReqPayload    = (const uint8_t *) &request,
        .reqPayloadSize = (uint32_t) sizeof (request),
        .timeout        = (uint32_t) SCICLIENT_SERVICE_WAIT_FOREVER
    };
    Sciclient_RespPrm_t respParam = {
        .flags           = (uint32_t) 0,   /* Populated by the API */
        .pRespPayload    = (uint8_t *) 0,
        .respPayloadSize = (uint32_t) 0
    };
#if !defined(MCU_PLUS_SDK)
    CacheP_wbInv((const void*) request.tisci_boardcfg_securityp_low, request.tisci_boardcfg_security_size);
#else
    CacheP_wbInv((void*)request.tisci_boardcfg_securityp_low,
                request.tisci_boardcfg_security_size,CacheP_TYPE_ALL);
#endif
    if((CSL_PASS != Sciclient_service(&reqParam, &respParam))
        || ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK))
    {
        retVal = CSL_EFAIL;
    }
    return retVal;
}

int32_t Sciclient_getDefaultBoardCfgInfo(Sciclient_DefaultBoardCfgInfo_t *pBoardCfgInfo)
{
    int32_t retVal = CSL_PASS;

    if(NULL == pBoardCfgInfo)
    {
        retVal = CSL_EFAIL;
    }

    if(CSL_PASS == retVal)
    {
        pBoardCfgInfo->boardCfgLow          = &gSciclient_boardCfgLow[0U];
        pBoardCfgInfo->boardCfgLowRm        = &gSciclient_boardCfgLow_rm[0U];
        pBoardCfgInfo->boardCfgLowSec       = &gSciclient_boardCfgLow_sec[0U];
        pBoardCfgInfo->boardCfgLowPm        = &gSciclient_boardCfgLow_pm[0U];
        pBoardCfgInfo->boardCfgLowSize      = SCICLIENT_BOARDCFG_SIZE_IN_BYTES;
        pBoardCfgInfo->boardCfgLowRmSize    = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES;
        pBoardCfgInfo->boardCfgLowSecSize   = SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES;
        pBoardCfgInfo->boardCfgLowPmSize    = SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES;
    }

    return retVal;
}
#endif

