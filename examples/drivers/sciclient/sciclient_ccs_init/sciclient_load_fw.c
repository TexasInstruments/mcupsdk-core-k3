/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file sbl_load_fw.c
 *
 *  \brief Implementation of System firmware Load with secure ROM
 *
 */

#include <kernel/dpl/SystemP.h>
#include <drivers/sciclient/csl_sec_proxy.h>
#include <drivers/device_manager/sciclient_direct/sciclient_romMessages.h>
#if defined ENABLE_SCICLIENT_DIRECT
/* WKUP R5 will use the SCI Client direct */
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif

/* ========================================================================== */
/*                            Extern Variables                                */
/* ========================================================================== */
extern CSL_SecProxyCfg gSciclient_secProxyCfg;
extern CSL_SecProxyCfg gSciclientRomSecProxyCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static inline uint32_t Sciclient_secProxyReadThread32(uint32_t thread, uint8_t idx);
static inline uint32_t Sciclient_secProxyThreadStatusReg(uint32_t thread);
static int32_t Sciclient_secProxyWaitThread(uint32_t thread, uint32_t timeout);
static int32_t Sciclient_secProxyVerifyThread(uint32_t thread);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline uint32_t Sciclient_secProxyReadThread32(uint32_t thread, uint8_t idx)
{
    uint32_t ret;
    ret = CSL_REG32_RD(CSL_secProxyGetDataAddr(&gSciclientRomSecProxyCfg,thread,0U) +
        ((uintptr_t) (0x4U) * (uintptr_t) idx));
    return ret;
}

static inline uint32_t Sciclient_secProxyThreadStatusReg(uint32_t thread)
{
    return ((uint32_t)(uintptr_t)(gSciclientRomSecProxyCfg.pSecProxyRtRegs) +
        CSL_SEC_PROXY_RT_THREAD_STATUS(thread));
}

static int32_t Sciclient_secProxyVerifyThread(uint32_t thread)
{
    int32_t status = SystemP_SUCCESS;
    /* Verify thread status before reading/writing */
    if ((CSL_REG32_RD(Sciclient_secProxyThreadStatusReg(thread)) &
        CSL_SEC_PROXY_RT_THREAD_STATUS_ERROR_MASK) != 0U)
    {
        status = SystemP_FAILURE;
    }
    return status;
}

static int32_t Sciclient_secProxyWaitThread(uint32_t thread, uint32_t timeout)
{
    int32_t  status     = CSL_ETIMEOUT;
    uint32_t timeToWait = timeout;
    /* Checks the thread count is > 0 */
    while (timeToWait > 0U)
    {
        if ((CSL_REG32_RD(Sciclient_secProxyThreadStatusReg(thread)) &
            CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) > 0U)
        {
            status = SystemP_SUCCESS;
            break;
        }
        timeToWait--;
    }
    return status;
}
int32_t Sciclient_loadFirmware(const uint32_t *pSciclient_firmware)
{
    int32_t  status   = SystemP_SUCCESS;
    uint32_t txThread = SCICLIENT_ROM_R5_TX_NORMAL_THREAD;
    uint32_t rxThread = SCICLIENT_ROM_R5_RX_NORMAL_THREAD;
    Sciclient_RomFirmwareLoadHdr_t header      = {0};
    Sciclient_RomFirmwareLoadPayload_t payload = {0};
    uint8_t secHeaderSizeWords = sizeof(struct tisci_sec_header)/sizeof(uint32_t);
    const uint32_t  maxMsgSizeBytes = CSL_secProxyGetMaxMsgSize(&gSciclientRomSecProxyCfg) - CSL_SEC_PROXY_RSVD_MSG_BYTES;

    volatile Sciclient_RomFirmwareLoadHdr_t *pLocalRespHdr =
        (Sciclient_RomFirmwareLoadHdr_t *)CSL_secProxyGetDataAddr(&gSciclientRomSecProxyCfg, rxThread, 0U);
    uint8_t  payloadSize = sizeof (Sciclient_RomFirmwareLoadPayload_t) /
                           sizeof (uint8_t);
    uint64_t proxyTargetAddr = gSciclient_secProxyCfg.proxyTargetAddr;
    /* Require ROM secure proxy target address for SYSFW load */
    gSciclient_secProxyCfg.proxyTargetAddr = gSciclientRomSecProxyCfg.proxyTargetAddr;
    /* Construct header */
    header.type = SCICLIENT_ROM_MSG_R5_TO_M3_M3FW;

    header.host = TISCI_HOST_ID_DEVICE_MANAGER;
    /* ROM expects a sequence number of 0 */
    header.seq  = 0U;
    /* ROM doesn't check for flags */
    header.flags = 0U;

    if (pSciclient_firmware != NULL)
    {
        payload.bufferAddress = (uint32_t)(uintptr_t)pSciclient_firmware;

        /*Size is not needed actually.It is taken from x509 certificate*/
        payload.bufferSizeBytes = 0xffffffffU;

        /* Verify thread status before reading/writing */
        status = Sciclient_secProxyVerifyThread(txThread);
        if (SystemP_SUCCESS == status)
        {
            status = Sciclient_secProxyWaitThread(txThread, SystemP_WAIT_FOREVER);
        }
        if (SystemP_SUCCESS == status)
        {
            /* Writing header and payload */
            Sciclient_sendMessage(txThread, NULL, secHeaderSizeWords,(uint8_t *) &header,
                                  (uint8_t *)&payload, payloadSize, maxMsgSizeBytes);

            /* CHECKING FOR FIRMWARE LOAD ACK */
            /* Verify thread status before reading/writing */
            status = Sciclient_secProxyVerifyThread(rxThread);
        }
        if (SystemP_SUCCESS == status)
        {
            while ((CSL_REG32_RD(Sciclient_secProxyThreadStatusReg(rxThread)) &
                 CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) == 0U) {;}
            /* Check the message type and flag of the response */
            if ((pLocalRespHdr->type ==
                SCICLIENT_ROM_MSG_M3_TO_R5_M3FW_RESULT)
                && (pLocalRespHdr->flags == SCICLIENT_ROM_MSG_CERT_AUTH_PASS))
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
            /* Reading from the last register of rxThread. This flushes the thread*/
            (void) Sciclient_secProxyReadThread32(rxThread,
                            (uint8_t)((maxMsgSizeBytes/4U)-1U));
        }

        /* CHECKING FOR TISCI_MSG_BOOT_NOTIFICATION from SYSFW*/
        pLocalRespHdr =
        (Sciclient_RomFirmwareLoadHdr_t *)(CSL_secProxyGetDataAddr(
                                            &gSciclientRomSecProxyCfg, rxThread, 0U)
                                            + ((uintptr_t) secHeaderSizeWords * (uintptr_t) 4U));
        if (status == SystemP_SUCCESS)
        {
            status = Sciclient_secProxyVerifyThread(rxThread);
        }
        if (status == SystemP_SUCCESS)
        {
            while ((CSL_REG32_RD(Sciclient_secProxyThreadStatusReg(rxThread)) &
                 CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) == 0U) {;}
            /* Check the message type and flag of the response */
            if (pLocalRespHdr->type ==
                TISCI_MSG_BOOT_NOTIFICATION)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
            /* Reading from the last register of rxThread*/
            (void) Sciclient_secProxyReadThread32(rxThread,
                            (uint8_t)((maxMsgSizeBytes/4U)-1U));
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }
    /* Setting the previous target address */
    gSciclient_secProxyCfg.proxyTargetAddr = proxyTargetAddr;

    return status;
}
