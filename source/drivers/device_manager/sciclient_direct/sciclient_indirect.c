/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 *  \file sciclient_indirect.c
 *
 *  \brief File containing the SCICLIENT driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <ti/drv/sciclient/sciserver.h>

#ifdef QNX_OS
#include <ti/drv/sciclient/src/sciclient/sciclient_qnx.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciclient_service (const Sciclient_ReqPrm_t *pReqPrm,
                           Sciclient_RespPrm_t      *pRespPrm)
{
#ifdef QNX_OS
    /* Inserting a resource manager layer, to serialize communication, between
     * multiple processes running on multiple cores,
     */
    int     fd;
    int32_t status       = CSL_PASS;
    char    *devname = "/dev/tisci";
    iov_t   siov[1], riov[1];
    int rc = EOK;

    /* Open up resource manager */
    fd = open(devname, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "open(%s): %s\n", devname, strerror(errno));
        status = CSL_EFAIL;
        return status;
    }

    /* Copy user buffers into a local copy, TODO should not be necessary */
    tisci_msg_t tisci_msg = {0};


    /* Fill out request */
    uint64_t reqPhyPayloadPtr = 0;
    if((pReqPrm->pReqPayload != 0) && (pReqPrm->reqPayloadSize != 0)){
        //printf("%s: translate request\n",__func__);
        reqPhyPayloadPtr = Sciclient_qnxVirtToPhyFxn((uint64_t *) pReqPrm->pReqPayload, (void *)&pReqPrm->reqPayloadSize);
    }
    tisci_msg.reqPrm.messageType = pReqPrm->messageType;
    tisci_msg.reqPrm.flags       = pReqPrm->flags;
    tisci_msg.reqPrm.pReqPayload = (uint8_t *) reqPhyPayloadPtr;
    tisci_msg.reqPrm.reqPayloadSize = pReqPrm->reqPayloadSize;
    tisci_msg.reqPrm.timeout = pReqPrm->timeout;


    /* Define expected response */
    uint64_t responsePayloadPhyPtr = 0;
    if((pRespPrm->pRespPayload != 0) && (pRespPrm->respPayloadSize != 0)){
        //printf("%s: translate response\n",__func__);
        responsePayloadPhyPtr = Sciclient_qnxVirtToPhyFxn((uint64_t *) pRespPrm->pRespPayload, (void *)&pReqPrm->reqPayloadSize);
    }
    tisci_msg.respPrm.flags = pRespPrm->flags;
    tisci_msg.respPrm.pRespPayload = (uint8_t *) responsePayloadPhyPtr;
    tisci_msg.respPrm.respPayloadSize =  pRespPrm->respPayloadSize;

    /* Get message ready to send */
    SETIOV(&siov[0], &tisci_msg, sizeof(tisci_msg_t));
    SETIOV(&riov[0], &tisci_msg, sizeof(tisci_msg_t));

    /*  Send message to /dev/tisci */
    if ((rc = devctlv(fd, DCMD_TISCI_MESSAGE, 1, 1, siov, riov, NULL)) != EOK) {
        fprintf(stderr, "devctl failed:%d errno/%d rc/%d\n", status, errno, rc);
        status = CSL_EFAIL;
        if(fd > 0) {
            close(fd);
        }
    }

    /* Flags parameter not getting set sometimes, ensure the response to user has correct flags value  */
    QNX_DEBUG_PRINT("%s: tisci_msg.respPrm.flags = 0x%08x\n",__func__,tisci_msg.respPrm.flags);
    QNX_DEBUG_PRINT("%s: pRespPrm->flags = 0x%08x\n",__func__,pRespPrm->flags);
    pRespPrm->flags = tisci_msg.respPrm.flags;
    QNX_DEBUG_PRINT("%s: pRespPrm->flags = 0x%08x\n",__func__,pRespPrm->flags);

    /* Close fd */
    // TODO: keep fd open to save time
    if(fd > 0) {
        close(fd);
    }

    return status;
}


int32_t Sciclient_service_rsmgr(const Sciclient_ReqPrm_t *pReqPrm,
                                Sciclient_RespPrm_t      *pRespPrm)
{
#endif
    uint8_t *fwdStatus = (uint8_t *)&pReqPrm->forwardStatus;
    /*
     * Never forward messages for this build. Set this flag explicitly to
     * prevent accidental setting by the application.
     */
    *fwdStatus = SCISERVER_NO_FORWARD_MSG;

    return Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

