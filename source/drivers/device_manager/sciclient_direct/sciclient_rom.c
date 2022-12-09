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
 *  \file sciclient_rom.c
 *
 *  \brief File containing the SCICLIENT ROM APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/hw_include/csl_types.h>
#include <string.h>

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

/** \brief This structure contains configuration parameters for
 *         the sec_proxy IP
 */
extern CSL_SecProxyCfg gSciclient_secProxyCfg;

/** \brief Pointer to structure that contains configuration parameters for
 *         the sec_proxy IP
 */
CSL_SecProxyCfg *pSciclient_secProxyCfg = &gSciclient_secProxyCfg;

#if defined (CONFIG_MSG_M4_ROM_USE_ALTERNATE_SPROXY)
/** \brief This structure contains configuration parameters for
 *         the alternate sec_proxy IP used by ROM for firmware
 *         loading only
 */
extern CSL_SecProxyCfg gSciclient_secProxyCfg_rom;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciclient_loadFirmware(const uint32_t *pSciclient_firmware)
{
    int32_t  status   = CSL_PASS;
    uint32_t gSciclient_maxMsgSizeBytes;
    uint32_t txThread = SCICLIENT_ROM_R5_TX_NORMAL_THREAD;
    uint32_t rxThread = SCICLIENT_ROM_R5_RX_NORMAL_THREAD;
    Sciclient_RomFirmwareLoadHdr_t header      = {0};
    Sciclient_RomFirmwareLoadPayload_t payload = {0};
    uint32_t secHeaderSizeWords = sizeof(struct tisci_sec_header)/sizeof(uint32_t);
    volatile Sciclient_RomFirmwareLoadHdr_t *pLocalRespHdr;
    uint8_t  payloadSize = sizeof (Sciclient_RomFirmwareLoadPayload_t) /
                           sizeof (uint8_t);
#if defined (CONFIG_MSG_M4_ROM_USE_ALTERNATE_SPROXY)
    /* Switch pointer to struct with alternate sproxy cfg used by ROM for firmware loading */
    pSciclient_secProxyCfg = &gSciclient_secProxyCfg_rom;
#endif
    /* Update pLocalRespHdr and maxMsgSizeBytes vars, which are dependent on pointer selected above */
    pLocalRespHdr = (Sciclient_RomFirmwareLoadHdr_t *)CSL_secProxyGetDataAddr
                                        (pSciclient_secProxyCfg, rxThread, 0U);
    gSciclient_maxMsgSizeBytes = CSL_secProxyGetMaxMsgSize(pSciclient_secProxyCfg) -
                                CSL_SEC_PROXY_RSVD_MSG_BYTES;

    /* Construct header */
    header.type = SCICLIENT_ROM_MSG_R5_TO_M3_M3FW;
#if defined (SOC_AM64X) || defined (SOC_AM62X) || defined (SOC_AM62AX)
    header.host = TISCI_HOST_ID_MAIN_0_R5_0;
#elif defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
    header.host = TISCI_HOST_ID_MCU_0_R5_1;;
#else
    header.host = TISCI_HOST_ID_R5_1;
#endif
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
        status = Sciclient_verifyThread(txThread);
        if (CSL_PASS == status)
        {
            status = Sciclient_waitThread(txThread, SCICLIENT_SERVICE_WAIT_FOREVER);
        }
        if (CSL_PASS == status)
        {
            /* Writing header and payload */
            Sciclient_sendMessage(txThread,
                                  NULL,
                                  0,
                                  (uint8_t *) &header,
                                  (uint8_t *)&payload,
                                  payloadSize,
                                  gSciclient_maxMsgSizeBytes);

            /* CHECKING FOR FIRMWARE LOAD ACK */
            /* Verify thread status before reading/writing */
            status = Sciclient_verifyThread(rxThread);
        }
        if (CSL_PASS == status)
        {
            while ((HW_RD_REG32(Sciclient_threadStatusReg(rxThread)) &
                 CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) == 0U) {;}
            /* Check the message type and flag of the response */
            if ((pLocalRespHdr->type ==
                SCICLIENT_ROM_MSG_M3_TO_R5_M3FW_RESULT)
                && (pLocalRespHdr->flags == SCICLIENT_ROM_MSG_CERT_AUTH_PASS))
            {
                status = CSL_PASS;
            }
            else
            {
                status = CSL_EFAIL;
            }
            /* Reading from the last register of rxThread*/
            (void) Sciclient_readThread32(rxThread,
                            (uint8_t)((gSciclient_maxMsgSizeBytes/4U)-1U));
        }

        /* CHECKING FOR TISCI_MSG_BOOT_NOTIFICATION from DMSC*/
        pLocalRespHdr =
        (Sciclient_RomFirmwareLoadHdr_t *)(CSL_secProxyGetDataAddr(
                                            pSciclient_secProxyCfg, rxThread, 0U)
                                            + ((uintptr_t) secHeaderSizeWords * (uintptr_t) 4U));
        if (status == CSL_PASS)
        {
            status = Sciclient_verifyThread(rxThread);
        }
        if (status == CSL_PASS)
        {
            while ((HW_RD_REG32(Sciclient_threadStatusReg(rxThread)) &
                 CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) == 0U) {;}
            /* Check the message type and flag of the response */
            if (pLocalRespHdr->type ==
                TISCI_MSG_BOOT_NOTIFICATION)
            {
                status = CSL_PASS;
            }
            else
            {
                status = CSL_EFAIL;
            }
            /* Reading from the last register of rxThread*/
            (void) Sciclient_readThread32(rxThread,
                            (uint8_t)((gSciclient_maxMsgSizeBytes/4U)-1U));
        }
#if defined (CONFIG_MSG_M4_ROM_USE_ALTERNATE_SPROXY)
        /* Switch pointer back to regular sproxy cfg struct used after Boot Notification msg received */
        pSciclient_secProxyCfg = &gSciclient_secProxyCfg;
        gSciclient_maxMsgSizeBytes = CSL_secProxyGetMaxMsgSize(pSciclient_secProxyCfg) -
                                CSL_SEC_PROXY_RSVD_MSG_BYTES;
#endif
    }
    else
    {
        status = CSL_EFAIL;
    }

    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
