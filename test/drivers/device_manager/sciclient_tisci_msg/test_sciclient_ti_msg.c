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
 */

/* ========================================================================== */
/*                           Include Files                                    */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_SCICLIENT_APP_TISCI_MSG_COUNT 55U

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

const int32_t gTestMessageType[TEST_SCICLIENT_APP_TISCI_MSG_COUNT] =
{
    TISCI_MSG_VERSION,
    TISCI_MSG_BOARD_CONFIG_RM,
    TISCI_MSG_SET_CLOCK,
    TISCI_MSG_GET_CLOCK,
    TISCI_MSG_SET_CLOCK_PARENT,
    TISCI_MSG_GET_CLOCK_PARENT,
    TISCI_MSG_GET_NUM_CLOCK_PARENTS,
    TISCI_MSG_SET_FREQ,
    TISCI_MSG_QUERY_FREQ,
    TISCI_MSG_GET_FREQ,
    TISCI_MSG_SET_DEVICE,
    TISCI_MSG_GET_DEVICE,
    TISCI_MSG_SET_DEVICE_RESETS,
    TISCI_MSG_RM_GET_RESOURCE_RANGE,
    TISCI_MSG_RM_UDMAP_FLOW_CFG,
    TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG,
    TISCI_MSG_RM_UDMAP_FLOW_DELEGATE,
    TISCI_MSG_RM_UDMAP_GCFG_CFG,
    TISCI_MSG_RM_IRQ_SET,
    TISCI_MSG_RM_IRQ_RELEASE,
    TISCI_MSG_RM_RING_CFG,
    TISCI_MSG_RM_RING_MON_CFG,
    TISCI_MSG_RM_UDMAP_TX_CH_CFG,
    TISCI_MSG_RM_UDMAP_RX_CH_CFG,
    TISCI_MSG_RM_PROXY_CFG,
    TISCI_MSG_BOARD_CONFIG_PM,
    TISCI_MSG_PREPARE_SLEEP,
    TISCI_MSG_LPM_WAKE_REASON,
    TISCI_MSG_SET_IO_ISOLATION,
    TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT,
    TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT,
    TISCI_MSG_QUERY_FW_CAPS,
    TISCI_MSG_KEY_WRITER,
    TISCI_MSG_WRITE_OTP_ROW,
    TISCI_MSG_READ_OTP_MMR,
    TISCI_MSG_RM_PSIL_PAIR,
    TISCI_MSG_RM_PSIL_UNPAIR,
    TISCI_MSG_RM_PSIL_READ,
    TISCI_MSG_RM_PSIL_WRITE,
    TISCI_MSG_SA2UL_SET_DSMEK,
    TISCI_MSG_SA2UL_GET_DSMEK,
    TISCI_MSG_SA2UL_RELEASE_DSMEK,
    TISCI_MSG_SET_ISC_REGION,
    TISCI_MSG_GET_ISC_REGION,
    TISCI_MSG_OPEN_DEBUG_FWLS,
    TISCI_MSG_LOCK_OTP_ROW,
    TISCI_MSG_SOFT_LOCK_OTP_WRITE_GLOBAL,
    TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
    TISCI_MSG_WRITE_SWREV,
    TISCI_MSG_READ_SWREV,
    TISCI_MSG_WRITE_KEYREV,
    TISCI_MSG_READ_KEYCNT_KEYREV,
    TISCI_MSG_KEY_WRITER,
    TISCI_MSG_SEC_HANDOVER,
    0xFFFF,  /* Negative test case */
};

/* ========================================================================== */
/*                         Function Definitions                               */
/* ========================================================================== */

void sciclient_testMessageType(void *args)
{
    int32_t         retVal = SystemP_SUCCESS;
    int32_t msgType = 0;
    struct tisci_msg_sys_reset_req resetRequest;
    resetRequest.domain = 1;
    const Sciclient_ReqPrm_t resetReqPrm =
    {
        TISCI_MSG_SYS_RESET,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &resetRequest,
        sizeof(resetRequest),
        SystemP_WAIT_FOREVER
    };
    struct tisci_msg_version_resp resetResponse;
    Sciclient_RespPrm_t           resetRespPrm =
    {
        0,
        (uint8_t *) &resetResponse,
        sizeof (resetResponse)
    };

    for(msgType = 0; msgType <= (sizeof(gTestMessageType)/sizeof(int32_t)); msgType++)
    {
        /* Check for the SYSFW version by sending a request */
        struct tisci_msg_version_req verRequest;
        const Sciclient_ReqPrm_t      verReqPrm =
        {
            gTestMessageType[msgType],
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &verRequest,
            sizeof(verRequest),
            SystemP_WAIT_FOREVER
        };

        struct tisci_msg_version_resp verResponse;
        Sciclient_RespPrm_t           verRespPrm =
        {
            0,
            (uint8_t *) &verResponse,
            sizeof (verResponse)
        };
        retVal = Sciclient_service(&verReqPrm, &verRespPrm);
        DebugP_log("\r\n msgType = %d retVal= %d and respPrm.flags = %d",msgType, retVal, verRespPrm.flags);
    }

    retVal = Sciclient_service(&resetReqPrm, &resetRespPrm);
    DebugP_log("\r\n msgType = %d retVal= %d and respPrm.flags = %d",msgType, retVal, resetRespPrm.flags);
}