/*
 * Copyright (c) 2023-2024, Texas Instruments Incorporated
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
 *  \file sciclient_direct.c
 *
 *  \brief File containing the SCICLIENT driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
//#include <ti/osal/osal.h>
#include<kernel/dpl/CacheP.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <boardcfg/boardcfg.h>
#include <startup.h>
#include <pm.h>
#include <rm.h>
#include <lpm_handler.h>
#include <fw_caps.h>
/* Sciclient APIs are kept in the end of the include list to make sure the
 * RM and PM HAL typedefs are used.
 */
#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/device_manager/sciserver.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_MAGIC_WORD_LEN
 * Length of magic word for extended boot info table.
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_MIN_COMPONENTS
 * Minimum number of components that should be present in combined image.
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_MAX_COMPONENTS
 * Max number of components in extended boot info table.
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_ROM_INFO_BASE
 * Base address where ROM loads the extended boot info.
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SYSFW_DATA
 * Component type corresponding to SYSFW data blob.
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SBL_DATA
 * Component type corresponding to SBL data blob.
 */
#define SCICLIENT_DIRECT_EXTBOOT_X509_MAGIC_WORD_LEN             (8U)
#define SCICLIENT_DIRECT_EXTBOOT_X509_MIN_COMPONENTS             (3U)
#define SCICLIENT_DIRECT_EXTBOOT_X509_MAX_COMPONENTS             (8U)
#define SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SYSFW_DATA        (0x12U)
#define SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SBL_DATA          (0x11U)

/**
 * \def SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_INDEX
 * Index of boardcfg in boardcfg descriptor table
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_SECURITY_INDEX
 * Index of security boardcfg in boardcfg descriptor table
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_PM_INDEX
 * Index of PM boardcfg in boardcfg descriptor table
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_RM_INDEX
 * Index of RM boardcfg in boardcfg descriptor table
 *
 * \def SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_NUM_DESCS
 * Number of boardcfg data in SYSFW data blob.
 */
#define SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_INDEX                  (0U)
#define SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_SECURITY_INDEX         (1U)
#define SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_PM_INDEX               (2U)
#define SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_RM_INDEX               (3U)
#define SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_NUM_DESCS              (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Component information populated by ROM. The combined image has
 *        multiple components.
 *        ROM populates this information for each component.
 *
 * \param comp_type Type of component
 * \param boot_core Core that loads or runs image
 * \param comp_opts Component options. Not used for now.
 * \param dest_addr Image destination address
 * \param comp_size Size of the component in bytes
 */
typedef struct {
    uint32_t comp_type;
    uint32_t boot_core;
    uint32_t comp_opts;
    uint64_t dest_addr;
    uint32_t comp_size;
} Sciclient_DirectExtBootX509Comp;

/**
 * \brief Component information table populated by ROM.
 *
 * \param magic_word Magic word for extended boot
 * \param num_comps Number of components present in extended boot info table
 * \param comps Information for each component
 */
typedef struct {
    uint8_t                             magic_word[
        SCICLIENT_DIRECT_EXTBOOT_X509_MAGIC_WORD_LEN];
    uint32_t                            num_comps;
    Sciclient_DirectExtBootX509Comp     comps[
        SCICLIENT_DIRECT_EXTBOOT_X509_MAX_COMPONENTS];
} Sciclient_DirectExtBootX509Table;

/**
 * \brief Describes the board config data
 *
 * \param type Type of board config data. This should map to corresponding TISCI
 *      message type. For example, a PM boardcfg should have a descriptor
 *      type TISCI_MSG_BOARD_CONFIG_PM.
 * \param offset Offset for board config data from beginning of SYSFW data
 *               binary blob
 * \param size Size of board config data
 * \param devgrp Device group to be used by SYSFW for automatic board
 *               config processing
 * \param reserved Reserved field. Not to be used.
 */
typedef struct {
    uint16_t type;
    uint16_t offset;
    uint16_t size;
    uint8_t  devgrp;
    uint8_t  reserved;
} __attribute__((__packed__)) Sciclient_DirectExtBootBoardCfgDesc ;

/**
 * \brief Boardcfg descriptor table provided by system integrator
 *
 * \param num_elems Number of elements in board config table.
 * \param sw_rev SW revision populated by system integrator.
 * \param descs Array of board config descriptors
 */
typedef struct {
    uint8_t                                 num_elems;
    uint8_t                                 sw_rev;
    Sciclient_DirectExtBootBoardCfgDesc     descs[
        SCICLIENT_DIRECT_EXTBOOT_BOARDCFG_NUM_DESCS];
} __attribute__((__packed__)) Sciclient_DirectBoardCfgDescTable;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t board_config_pm_handler(uint32_t *msg_recv);
__attribute__((optnone)) static uint16_t boardcfgRmFindCertSize(uint32_t *msg);
static int32_t boardcfg_RmAdjustReq(uint32_t *msg, uint16_t adjSize);
static int32_t Sciclient_pmSetMsgProxy(uint32_t *msg_recv, uint32_t reqFlags,
                                      uint8_t procId);
static int32_t Sciclient_pmSetCpuResetMsgProxy(uint32_t *msg_recv, uint8_t procId);
static int32_t tisci_msg_board_config_rm_handler(uint32_t *msg_recv);
#ifdef CONFIG_LPM_DM
static void lpm_UpdateCtxtAddr(uint32_t *msg);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \def gcSciclientDirectExtBootX509MagicWord
 * Magic word that specifies whether combined image is being used.
 */
const uint8_t gcSciclientDirectExtBootX509MagicWord[
    SCICLIENT_DIRECT_EXTBOOT_X509_MAGIC_WORD_LEN] =
    { 'E', 'X', 'T', 'B', 'O', 'O', 'T', 0 };

extern Sciclient_ServiceHandle_t gSciclientHandle;
#ifdef CONFIG_LPM_DM
extern volatile uint64_t gFSctxtaddr;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciclient_service (const Sciclient_ReqPrm_t *pReqPrm,
                           Sciclient_RespPrm_t      *pRespPrm)
{
    int32_t ret = CSL_PASS;
    uint32_t msgType;
    uint32_t message[20] = {0};
    struct tisci_header *hdr;
    uint16_t adjSize = 0;
    uint8_t *fwdStatus = (uint8_t *)&pReqPrm->forwardStatus;
    uint8_t localSeqId;
    uint32_t contextId;
    uint32_t txThread __attribute__((unused));
    uint32_t rxThread __attribute__((unused));

    if ((pReqPrm == NULL) || (pRespPrm == NULL))
    {
        ret = CSL_EBADARGS;
    }

    /*
     * Below functions serve only to check the context and format the header for
     * local processing. If the message is to be forwarded, then these functions
     * will be called again to obtain the necessary transfer parameters.
     */
    if (CSL_PASS == ret)
    {
        msgType = (uint32_t)pReqPrm->messageType;
        ret = Sciclient_serviceGetThreadIds (pReqPrm, &contextId, &txThread,
                                         &rxThread);
    }
    if (CSL_PASS == ret)
    {
        ret = Sciclient_servicePrepareHeader(pReqPrm, &localSeqId,
                 contextId, &hdr);
    }
    if (CSL_PASS == ret)
    {
        switch (msgType) {
            case TISCI_MSG_BOARD_CONFIG_PM:
            case TISCI_MSG_SET_CLOCK:
            case TISCI_MSG_GET_CLOCK:
            case TISCI_MSG_SET_CLOCK_PARENT:
            case TISCI_MSG_GET_CLOCK_PARENT:
            case TISCI_MSG_GET_NUM_CLOCK_PARENTS:
            case TISCI_MSG_SET_FREQ:
            case TISCI_MSG_QUERY_FREQ:
            case TISCI_MSG_GET_FREQ:
            case TISCI_MSG_SET_DEVICE:
            case TISCI_MSG_GET_DEVICE:
            case TISCI_MSG_SET_DEVICE_RESETS:
            case TISCI_MSG_SYS_RESET:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                ret = Sciclient_ProcessPmMessage(pReqPrm->flags, message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;
                break;
            /* RM messages processed solely by RM within DM on MCU R5F */
            case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            case TISCI_MSG_RM_UDMAP_GCFG_CFG:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                ret = Sciclient_ProcessRmMessage(message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;
                break;
            /*
             * RM messages processed by RM within DM on MCU R5F and Secure
             * RM within TIFS on M3
             */
            case TISCI_MSG_RM_IRQ_SET:
            case TISCI_MSG_RM_IRQ_RELEASE:
            case TISCI_MSG_RM_RING_CFG:
            case TISCI_MSG_RM_RING_MON_CFG:
            case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            case TISCI_MSG_RM_PROXY_CFG:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                ret = Sciclient_ProcessRmMessage(message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;

                if ((ret == CSL_PASS) &&
                        ((pRespPrm->flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
                {
                    /*
                     * This message is forwarded to DMSC for continued
                     * processing of secure RM configuration.
                     */
                    *fwdStatus = SCISERVER_FORWARD_MSG;
                    ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
                }

                break;
            /* RM boardcfg must be sent to TIFS before local processing */
            case TISCI_MSG_BOARD_CONFIG_RM:

                /* If RM boardcfg has a certificate, find the length */
                adjSize = boardcfgRmFindCertSize((uint32_t *)pReqPrm->pReqPayload);

                /* Send to TIFS */
               *fwdStatus = SCISERVER_FORWARD_MSG;
                ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
                if ((ret == CSL_PASS) &&
                        ((pRespPrm->flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
                {
                    /*
                     * Invalidate the cache since TIFS will overwrite the memory
                     * to replace the certificate.
                     *
                     * If the certificate is consumed, need to adjust the size
                     * of the boardcfg request.
                     *
                     * If the certificate is not consumed (duplicate RM boardcfg
                     * send), then the pointer to the boardcfg structure needs
                     * to be advanced.
                     */
                    ret = boardcfg_RmAdjustReq((uint32_t *)pReqPrm->pReqPayload, adjSize);
                }
                if ((ret == CSL_PASS) &&
                        ((pRespPrm->flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
                {

                    memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                    ret = Sciclient_ProcessRmMessage(message);
                    if (pRespPrm->pRespPayload != NULL)
                    {
                        memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                    }
                    hdr = (struct tisci_header *) &message;
                    pRespPrm->flags = hdr->flags;
                }
                else
                {
                    ret = CSL_EFAIL;
                }
                break;

#ifdef CONFIG_LPM_DM    /* Low power mode handling */
            case TISCI_MSG_PREPARE_SLEEP:
                /* Copy the original message for local processing */
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);

                /* Update the context save address if required */
                lpm_UpdateCtxtAddr((uint32_t *)pReqPrm->pReqPayload);

                /* Sending to TIFS for further processing */
                *fwdStatus = SCISERVER_FORWARD_MSG;
                ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);

                if ((ret == CSL_PASS) &&
                        ((pRespPrm->flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
                {
                    /* Processing prepare sleep message locally */
                    ret = Sciclient_ProcessPmMessage(pReqPrm->flags,message);
                    if (pRespPrm->pRespPayload != NULL)
                    {
                        memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                    }

                    hdr = (struct tisci_header *) &message;
                    pRespPrm->flags = hdr->flags;
                }
                else
                {
                    /* local processing of prepare sleep failed, send NACK to power master */
                    ret = CSL_EFAIL;
                }
                break;
            case TISCI_MSG_ENTER_SLEEP:
            case TISCI_MSG_LPM_WAKE_REASON:
            case TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT:
            case TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT:
            case TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT:
            case TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT:
            case TISCI_MSG_LPM_GET_NEXT_SYS_MODE:
            case TISCI_MSG_LPM_GET_NEXT_HOST_STATE:
            case TISCI_MSG_SET_IO_ISOLATION:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                /* Processing enter sleep message locally */
                ret = Sciclient_ProcessPmMessage(pReqPrm->flags,message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;
                break;
#endif
            case TISCI_MSG_QUERY_FW_CAPS:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                /* Processing enter sleep message locally */
                ret = Sciclient_query_fw_caps_handler(pReqPrm->flags,message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;

                break;
            case TISCI_MSG_WRITE_OTP_ROW:
            case TISCI_MSG_READ_OTP_MMR:
            case TISCI_MSG_LOCK_OTP_ROW:
            case TISCI_MSG_SOFT_LOCK_OTP_WRITE_GLOBAL:
            case TISCI_MSG_GET_OTP_ROW_LOCK_STATUS:
            case TISCI_MSG_READ_SWREV:
            case TISCI_MSG_WRITE_SWREV:
            case TISCI_MSG_READ_KEYCNT_KEYREV:
            case TISCI_MSG_WRITE_KEYREV:
            case TISCI_MSG_KEY_WRITER:
            case TISCI_MSG_SA2UL_SET_DKEK :
            case TISCI_MSG_SA2UL_GET_DKEK :
            case TISCI_MSG_SA2UL_RELEASE_DKEK :
            case TISCI_MSG_SA2UL_SET_DSMEK :
            case TISCI_MSG_SA2UL_GET_DSMEK :
            case TISCI_MSG_SA2UL_RELEASE_DSMEK :
            case TISCI_MSG_OPEN_DEBUG_FWLS :
                ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
                break;
            /* RM messages processed by Secure RM within TIFS on M3 */
            case TISCI_MSG_RM_PSIL_PAIR:
            case TISCI_MSG_RM_PSIL_UNPAIR:
            case TISCI_MSG_RM_PSIL_READ:
            case TISCI_MSG_RM_PSIL_WRITE:
            default:
            {
                /*
                 * These RM messages and all baseport and security messages are
                 * entirely processed on DMSC. When called on mcu1_0 directly,
                 * these are treated as native calls to DMSC. If these requests
                 * are made from other CPUs, the sciserver will take care of
                 * setting the forward status prior to calling this function.
                 */
                *fwdStatus = SCISERVER_FORWARD_MSG;
                ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
                break;
            }
        }
    }

    /*
     * Reset the forward status. This prevents possible accidental reuse of
     * stack memory with flag previously set and not properly cleared by the
     * application.
     */
    *fwdStatus = SCISERVER_NO_FORWARD_MSG;

    return ret;
}

void Sciclient_TisciMsgSetAckResp(struct tisci_header *hdr)
{
    hdr->flags |= TISCI_MSG_FLAG_ACK;
}

void Sciclient_TisciMsgSetNakResp(struct tisci_header *hdr)
{
    hdr->flags &= (~TISCI_MSG_FLAG_ACK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t board_config_pm_handler(uint32_t *msg_recv)
{
    int32_t ret;
    struct tisci_msg_board_config_pm_req *req =
        (struct tisci_msg_board_config_pm_req *) msg_recv;

    ret = boardcfg_pm_receive_and_validate(req->hdr.host,
                           req->tisci_boardcfg_pmp_low,
                           req->tisci_boardcfg_pmp_high,
                           req->tisci_boardcfg_pm_size,
                           req->tisci_boardcfg_pm_devgrp);

    if (ret == CSL_PASS) {
        ret = pm_init();
    }

    return ret;
}

static int32_t Sciclient_pmSetMsgProxy(uint32_t *msg_recv, uint32_t reqFlags, uint8_t procId)
{
    int32_t ret = CSL_PASS;
    /* Special device handling when performing the LPSC config for
     * MCU R5.
     */
    struct tisci_msg_set_device_req *req =
        (struct tisci_msg_set_device_req *) msg_recv;
    uint8_t state = req->state;

    switch (state) {
        case TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF:
            Sciclient_procBootSetSequenceCtrl(procId,
                                              0,
                                              TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_LPSC,
                                              reqFlags,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
            break;
        case TISCI_MSG_VALUE_DEVICE_SW_STATE_ON:
            Sciclient_procBootSetSequenceCtrl(procId,
                                              TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_LPSC,
                                              0,
                                              reqFlags,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
            break;
        default:
            ret = -EINVAL;
            break;
    }
    return ret;
}

static int32_t Sciclient_pmSetCpuResetMsgProxy(uint32_t *msg_recv, uint8_t procId)
{
    int32_t ret = CSL_PASS;
    /* Special device handling when performing targeted CPU resets
     * for MCU R5.
     */
    struct tisci_msg_set_device_resets_req *req =
        (struct tisci_msg_set_device_resets_req *) msg_recv;
    uint32_t reset = req->resets;

    switch (reset) {
        case 0: /* Take CPU out of RESET */
            Sciclient_procBootSetSequenceCtrl(procId,
                                              0,
                                              TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET,
                                              0,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
            break;
        case 1: /* Put CPU into RESET */
            Sciclient_procBootSetSequenceCtrl(procId,
                                              TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_RESET,
                                              0,
                                              0,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
            break;
        default:
            ret = -EINVAL;
            break;
    }
    return ret;
}
int32_t Sciclient_query_fw_caps_handler(const uint32_t reqFlags __attribute__((unused)), void *tx_msg)
{
    int32_t ret = CSL_PASS;
    uint32_t flags = ((struct tisci_header *) tx_msg)->flags;

    ret = query_fw_caps_handler((uint32_t*)tx_msg);

    if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
        if (ret == CSL_PASS) {
            Sciclient_TisciMsgSetAckResp((struct tisci_header *) tx_msg);
        } else {
            Sciclient_TisciMsgSetNakResp((struct tisci_header *) tx_msg);
        }
    }

    return ret;
}

int32_t Sciclient_ProcessPmMessage(const uint32_t reqFlags, void *tx_msg)
{
    int32_t ret = CSL_PASS;
    bool msg_inval = false;
    uint32_t msgType = ((struct tisci_header *) tx_msg)->type;
    uint32_t flags = ((struct tisci_header *) tx_msg)->flags;
    switch (msgType)
    {
        case TISCI_MSG_BOARD_CONFIG_PM         :
            ret = board_config_pm_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_CLOCK               :
            ret = set_clock_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_CLOCK               :
            ret = get_clock_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_CLOCK_PARENT        :
            ret = set_clock_parent_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_CLOCK_PARENT        :
            ret = get_clock_parent_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_NUM_CLOCK_PARENTS   :
            ret = get_num_clock_parents_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_FREQ                :
            ret = set_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_QUERY_FREQ              :
            ret = query_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_FREQ                :
            ret = get_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_DEVICE              :
            {
                struct tisci_msg_set_device_req *req =
                    (struct tisci_msg_set_device_req *) tx_msg;
                uint32_t id = req->id;
                switch (id)
                {
                    case SCICLIENT_DEV_MCU_R5FSS0_CORE0:
                        ret = Sciclient_pmSetMsgProxy((uint32_t*)tx_msg,
                                reqFlags,
                                SCICLIENT_DEV_MCU_R5FSS0_CORE0_PROCID);
                    break;
#if ! (defined(SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX))
                    case SCICLIENT_DEV_MCU_R5FSS0_CORE1:
                        ret = Sciclient_pmSetMsgProxy((uint32_t*)tx_msg,
                                reqFlags,
                                SCICLIENT_DEV_MCU_R5FSS0_CORE1_PROCID);
                    break;
#endif
                    default:
                        ret = set_device_handler((uint32_t*)tx_msg);
                    break;
                }
            }
            break;
        case TISCI_MSG_GET_DEVICE              :
            ret = get_device_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_DEVICE_RESETS       :
            {
                struct tisci_msg_set_device_resets_req *req =
                    (struct tisci_msg_set_device_resets_req *) tx_msg;
                uint32_t id = req->id;
                switch (id)
                {
                    case SCICLIENT_DEV_MCU_R5FSS0_CORE0:
                        ret = Sciclient_pmSetCpuResetMsgProxy((uint32_t*)tx_msg,
                                SCICLIENT_DEV_MCU_R5FSS0_CORE0_PROCID);
                    break;
#if ! (defined(SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX))
                    case SCICLIENT_DEV_MCU_R5FSS0_CORE1:
                        ret = Sciclient_pmSetCpuResetMsgProxy((uint32_t*)tx_msg,
                                SCICLIENT_DEV_MCU_R5FSS0_CORE1_PROCID);
                    break;
#endif
                    default:
                        ret = set_device_resets_handler((uint32_t*)tx_msg);
                    break;
                }
            }
            break;
        case TISCI_MSG_SYS_RESET               :
            ret = sys_reset_handler((uint32_t*)tx_msg); break;
#ifdef CONFIG_LPM_DM
        case TISCI_MSG_PREPARE_SLEEP             :
            ret = dm_prepare_sleep_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_ENTER_SLEEP               :
            ret = dm_enter_sleep_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_WAKE_REASON               :
            ret = dm_lpm_wake_reason_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_IO_ISOLATION          :
            ret = dm_set_io_isolation_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT:
            ret = dm_lpm_set_device_constraint((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT:
            ret = dm_lpm_set_latency_constraint((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT:
            ret = dm_lpm_get_device_constraint((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT:
            ret = dm_lpm_get_latency_constraint((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_GET_NEXT_SYS_MODE:
            ret = dm_lpm_get_next_sys_mode((uint32_t*)tx_msg); break;
        case TISCI_MSG_LPM_GET_NEXT_HOST_STATE:
            ret = dm_lpm_get_next_host_state((uint32_t*)tx_msg); break;
#endif
        default:
            ret = CSL_EFAIL; msg_inval = 1U;
        break;
    }
    if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
        if (ret == CSL_PASS) {
            Sciclient_TisciMsgSetAckResp((struct tisci_header *) tx_msg);
        } else {
            Sciclient_TisciMsgSetNakResp((struct tisci_header *) tx_msg);
        }
    }
    /*
     * Avoid overwriting status of calling message handler if the message
     * handler has a failure status.
     */
    if ((ret != CSL_PASS) && !msg_inval) {
        /*
         * NACK will be sent in message if error so send CSL_PASS back
         * in return status
         */
        ret = CSL_PASS;
    }
    return ret;
}

__attribute__((optnone)) static uint16_t boardcfgRmFindCertSize(uint32_t *msg_recv)
{
    uint16_t cert_len = 0U;
    uint8_t *cert_len_ptr = (uint8_t *)&cert_len;
    uint8_t *x509_cert_ptr;
    uint16_t ret = 0;

    struct tisci_msg_board_config_rm_req *req =
        (struct tisci_msg_board_config_rm_req *) msg_recv;

   x509_cert_ptr = (uint8_t *)req->tisci_boardcfg_rmp_low;


    if (*x509_cert_ptr == 0x30U)
    {

        cert_len = *(x509_cert_ptr + 1U);

        if (cert_len == 0x82U)
        {
            *cert_len_ptr = *(x509_cert_ptr + 3);
            *(cert_len_ptr + 1) = *(x509_cert_ptr + 2);

            /* add current offset from start of x509 cert */
            cert_len += 3U;

            /* cert_len now contains the offset of the last byte */
            /* of the cert from the ccert_start. To get the size */
            /* of certificate, add 1                             */
            cert_len = (cert_len + 1U);
        }

        /* If you need more than 2 bytes to store the cert length  */
        /* it means that the cert length is greater than 64 Kbytes */
        /* and we do not support it                                */
        else if ((cert_len != 0x82U) && (cert_len > 0x80U))
        {
            cert_len = 0U;

        }
        else
        {
            /* add current offset from start of x509 cert  */
            /* if cert len was obtained from 2nd byte i.e. */
            /* cert size is 127 bytes or less              */
            cert_len += 1U;

            /* cert_len now contains the offset of the last byte */
            /* of the cert from the ccert_start. To get the size */
            /* of certificate, add 1                             */
            cert_len = (cert_len + 1U);
        }

        ret = cert_len;

    }
    else
    {
        /* The data does not contain a certificate - return */
        ret = 0;
    }

    return ret;
}

static int32_t boardcfg_RmAdjustReq(uint32_t *msg, uint16_t adjSize)
{
    int32_t r = CSL_PASS;
    uint16_t newSize = 0;
    struct tisci_msg_board_config_rm_req *req =
        (struct tisci_msg_board_config_rm_req *) msg;

    /* If there was no certificate to begin with, do not adjust anything */
    if (adjSize != 0U)
    {

#if !defined(MCU_PLUS_SDK)
    /* Invalidate the cache */
    CacheP_Inv((const void*) req->tisci_boardcfg_rmp_low,
            req->tisci_boardcfg_rm_size);
#else
    CacheP_inv((void*)req->tisci_boardcfg_rmp_low,
            req->tisci_boardcfg_rm_size, CacheP_TYPE_ALL);
#endif
    /*
     * See if there is still a certificate that needs to be compensated for (in
     * case TIFS did not process this upon multiple requests for RM board cfg).
     *
     * If there is no certificate, then we adjust the size of the RM boardcfg
     * request. If there is a certificate, it should match the size we retrieved
     * earlier. Advance the base pointer. If the size does not match, then this
     * is an error.
     */
    newSize = boardcfgRmFindCertSize(msg);

        if (newSize == 0U)
        {
            req->tisci_boardcfg_rm_size -= adjSize;
        }
        else if (newSize == adjSize)
        {
            req->tisci_boardcfg_rm_size -= adjSize;
            req->tisci_boardcfg_rmp_low = req->tisci_boardcfg_rmp_low + adjSize;
        }
        else
        {
            r = CSL_EFAIL;
        }
    }
    else
    {
        r = CSL_PASS;
    }
    return r;
}

static int32_t tisci_msg_board_config_rm_handler(uint32_t *msg_recv)
{
    int32_t r = CSL_PASS;
    struct tisci_msg_board_config_rm_req *req =
        (struct tisci_msg_board_config_rm_req *) msg_recv;

    r = boardcfg_rm_receive_and_validate(req->hdr.host,
                         req->tisci_boardcfg_rmp_low,
                         req->tisci_boardcfg_rmp_high,
                         req->tisci_boardcfg_rm_size,
                         req->tisci_boardcfg_rm_devgrp);

    if (r == CSL_PASS) {
        r = rm_init();
    }

    return r;
}

#ifdef CONFIG_LPM_DM
static void lpm_UpdateCtxtAddr(uint32_t *msg)
{
    struct tisci_msg_prepare_sleep_req *req =
        (struct tisci_msg_prepare_sleep_req *) msg;

    /*
     * If context address value is non-zero, the address is already allocated,
     * do not adjust anything.
     *
     * If context address value is zero, then update the address value with address
     * allocated in linker file.
     */
    if ((req->ctx_lo == 0U) && (req->ctx_hi == 0U))
    {
        /* Update the context address */
        req->ctx_lo = (uint32_t) gFSctxtaddr;
        req->ctx_hi = (uint32_t) (gFSctxtaddr >> 32);
    }
}
#endif

int32_t Sciclient_ProcessRmMessage(void *tx_msg)
{
    int32_t r = CSL_PASS;
    bool msg_inval = false;
    uint32_t msgType = ((struct tisci_header *) tx_msg)->type;

    switch (msgType) {
        case TISCI_MSG_BOARD_CONFIG_RM:
            r = tisci_msg_board_config_rm_handler((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            r = rm_core_get_resource_range((uint32_t *)tx_msg, (uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_IRQ_SET:
            r = rm_irq_set((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_IRQ_RELEASE:
            r = rm_irq_release((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_RING_CFG:
            r = rm_ra_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_RING_MON_CFG:
            r = rm_ra_mon_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            r = rm_udmap_tx_ch_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            r = rm_udmap_rx_ch_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            r = rm_udmap_flow_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            r = rm_udmap_flow_size_thresh_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            r = rm_udmap_flow_delegate((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_GCFG_CFG:
            r = rm_udmap_gcfg_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_PROXY_CFG:
            r = rm_proxy_cfg((uint32_t *)tx_msg);
            break;
        default:
            r = CSL_EFAIL;
            msg_inval = 1U;
            break;
    }

    if ((((struct tisci_header *) tx_msg)->flags & TISCI_MSG_FLAG_AOP) != 0U) {
        if (r != CSL_PASS) {
            Sciclient_TisciMsgSetNakResp((struct tisci_header *)tx_msg);
        } else {
            Sciclient_TisciMsgSetAckResp((struct tisci_header *)tx_msg);
        }
    }

    /*
     * Avoid overwriting status of calling message handler if the message
     * handler has a failure status.
     */
    if ((r != CSL_PASS) && !msg_inval) {
        /*
         * NACK will be sent in message if error so send CSL_PASS back
         * in return status
         */
        r = CSL_PASS;
    }

    return r;
}

int32_t Sciclient_boardCfgPrepHeader (
    uint8_t * pCommonHeader, uint8_t * pBoardCfgHeader,
    const Sciclient_BoardCfgPrms_t * pInPmPrms,
    const Sciclient_BoardCfgPrms_t * pInRmPrms)
{
    int32_t ret = CSL_PASS;
    if ((pCommonHeader == NULL) || (pBoardCfgHeader == NULL) ||
        (pInPmPrms == NULL) || (pInRmPrms == NULL))
    {
        ret = CSL_EBADARGS;
    }
    /* Populate the common header which will be loaded by ROM in case of
     * combined boot image format.
     */
    if (CSL_PASS == ret)
    {
        Sciclient_DirectExtBootX509Table  *pX509Table =
            (Sciclient_DirectExtBootX509Table *) pCommonHeader;
        memcpy(pX509Table->magic_word, gcSciclientDirectExtBootX509MagicWord,
               sizeof(gcSciclientDirectExtBootX509MagicWord));
        pX509Table->num_comps = 1;
        pX509Table->comps[0].comp_type =
            SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SBL_DATA;
        pX509Table->comps[0].boot_core = 0x10;
        pX509Table->comps[0].comp_opts = 0;
        pX509Table->comps[0].dest_addr = (uint64_t) pBoardCfgHeader;
        pX509Table->comps[0].comp_size =
            sizeof(Sciclient_DirectBoardCfgDescTable) +
            SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES +
            SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES;
    }
    /* Populate the Board config structure */
    if (CSL_PASS == ret)
    {
        Sciclient_DirectBoardCfgDescTable * pBoardCfgDesc =
            (Sciclient_DirectBoardCfgDescTable *) pBoardCfgHeader;
        pBoardCfgDesc->num_elems = 2U;
        pBoardCfgDesc->sw_rev  = 0U; /* Not Used for RM and PM */
        pBoardCfgDesc->descs[0].type = TISCI_MSG_BOARD_CONFIG_PM;
        pBoardCfgDesc->descs[0].offset = (uint16_t)((uint32_t) pInPmPrms->boardConfigLow -
                                         (uint32_t) pBoardCfgHeader);
        pBoardCfgDesc->descs[0].size = pInPmPrms->boardConfigSize;
        pBoardCfgDesc->descs[0].devgrp = pInPmPrms->devGrp;
        pBoardCfgDesc->descs[0].reserved = 0x0;
        pBoardCfgDesc->descs[1].type = TISCI_MSG_BOARD_CONFIG_RM;
        pBoardCfgDesc->descs[1].offset = (uint16_t)((uint32_t) pInRmPrms->boardConfigLow -
                                         (uint32_t) pBoardCfgHeader);
        pBoardCfgDesc->descs[1].size = pInRmPrms->boardConfigSize;
        pBoardCfgDesc->descs[1].devgrp = pInRmPrms->devGrp;
        pBoardCfgDesc->descs[1].reserved = 0x0;
    }
    return ret;
}

int32_t Sciclient_boardCfgParseHeader (
    uint8_t * pCommonHeader,
    Sciclient_BoardCfgPrms_t * pInPmPrms,
    Sciclient_BoardCfgPrms_t * pInRmPrms)
{
    int32_t ret = CSL_PASS;
    Sciclient_DirectExtBootX509Table  *pX509Table =
            (Sciclient_DirectExtBootX509Table *) pCommonHeader;
    if ((pCommonHeader == NULL) || (pInPmPrms == NULL) || (pInRmPrms == NULL))
    {
        ret = CSL_EBADARGS;
    }
    /* Populate the common header which will be loaded by ROM in case of
     * combined boot image format.
     */
    if (CSL_PASS == ret)
    {
        if (memcmp(pX509Table->magic_word,
            gcSciclientDirectExtBootX509MagicWord,
            sizeof(gcSciclientDirectExtBootX509MagicWord)) == 0)
        {
            ret = CSL_PASS;
        }
        else
        {
            ret = CSL_EFAIL;
        }
    }
    if (CSL_PASS == ret)
    {
        uint32_t i = 0U;
        uint32_t foundRm = 0U, foundPm = 0U;
        uint32_t j = 0U;
        for (j = 0U; j < pX509Table->num_comps; j++)
        {
            uint32_t addr = (uint32_t) (pX509Table->comps[j].dest_addr
                 & (uint64_t) 0xFFFFFFFFU);
            if (pX509Table->comps[j].comp_type !=
                SCICLIENT_DIRECT_EXTBOOT_X509_COMPTYPE_SBL_DATA)
            {
                continue;
            }
            Sciclient_DirectBoardCfgDescTable *pBoardCfgDesc =
                (Sciclient_DirectBoardCfgDescTable *) addr;
            for (i = 0U; i < pBoardCfgDesc->num_elems; i++)
            {
                if (pBoardCfgDesc->descs[i].type == TISCI_MSG_BOARD_CONFIG_PM)
                {
                    pInPmPrms->boardConfigLow = pBoardCfgDesc->descs[i].offset +
                        (uint32_t) pBoardCfgDesc;
                    pInPmPrms->boardConfigSize = pBoardCfgDesc->descs[i].size;
                    pInPmPrms->devGrp = pBoardCfgDesc->descs[i].devgrp;
                    pInPmPrms->boardConfigHigh = 0U;
                    foundPm = 1U;
                }
                if (pBoardCfgDesc->descs[i].type == TISCI_MSG_BOARD_CONFIG_RM)
                {
                    pInRmPrms->boardConfigLow = pBoardCfgDesc->descs[i].offset +
                        (uint32_t) pBoardCfgDesc;
                    pInRmPrms->boardConfigSize = pBoardCfgDesc->descs[i].size;
                    pInRmPrms->devGrp = pBoardCfgDesc->descs[i].devgrp;
                    pInRmPrms->boardConfigHigh = 0U;
                    foundRm = 1U;
                }
            }
        }
        if ((foundPm == 1U) && (foundRm == 1U))
        {
            ret = CSL_PASS;
        }
        else
        {
            ret = CSL_EFAIL;
        }
    }
    return ret;
}

