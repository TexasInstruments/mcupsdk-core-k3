/*
 * Copyright (c) 2017-2025, Texas Instruments Incorporated
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
 *  \file sciclient.c
 *
 *  \brief File containing the SCICLIENT driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/hw_include/cslr_soc.h>
#include <string.h> /*For memcpy*/
#include <drivers/device_manager/sciserver.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <lib/trace.h>
#include <drivers/device_manager/rm_pm_hal/rm_pm_hal_src/lpm/lpm_trace.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*Header size in words*/
#define SCICLIENT_HEADER_SIZE_IN_WORDS (sizeof (struct tisci_header) \
                                        / sizeof (uint32_t))

/** Indicate that this message is marked secure */
#define TISCI_MSG_FLAG_MASK    (TISCI_BIT(0) | TISCI_BIT(1))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   ISR called when a response is received from DMSC.
 *
 *  \param   arg    Not used.
 *
 *  \return None
 */
static void Sciclient_ISR(uintptr_t arg);

/**
 *  \brief   This utility function is to be used to setup
 *           response interrupts for various Sciclient contexts
 *
 *  \param   contextId                  Context ID to be used
 *  \param   sciclientRespIntrHandler   Response Interrupt Handler for the
 *                                      sciclient context to be used
 *
 *  \return  CSL_PASS on success, else failure
 */
static int32_t Sciclient_setupRespIntr(uint32_t contextId,
                                       uint8_t sciclientRespIntrHandler);

/**
 *  \brief   This utility function is to be used to take care of
 *           all non-aligned c66x accesses
 *
 *  \param   src            Source Buffer pointer
 *  \param   dest           Destination Buffer pointer
 *  \param   num_bytes      Number of Bytes to copy.
 *
 *  \return None
 */
static void Sciclient_utilByteCopy(uint8_t *src,
                                   uint8_t *dest,
                                   uint32_t num_bytes);
/**
 *  \brief   This utility function is to be used to get pay
 *           load size
 *
 *  \param   Sciclient_ReqPrm_t      Request Parameter
 *  \param   Sciclient_RespPrm_t     Response Parameter
 *  \param   txPayloadSize           Transmission Pay Load Size
 *  \param   rxPayloadSize           Reception Pay Load Size.
 *
 *  \return None
 */
static int32_t Sciclient_serviceGetPayloadSize(const Sciclient_ReqPrm_t *pReqPrm,
                                        const Sciclient_RespPrm_t      *pRespPrm,
                                        uint32_t *txPayloadSize,
                                        uint32_t *rxPayloadSize);

#if defined(_TMS320C6X)
/**
 *  \brief   This utility function is used to set the RAT for IRs for C66x
 *
 *  \param   ratRegion      Rat Region configuration
 *
 *  \return None
 */
static int32_t Sciclient_C66xRatMap(uint32_t ratRegion);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *   \brief Handle used by #Sciclient_service function
 */
Sciclient_ServiceHandle_t gSciclientHandle =
    (Sciclient_ServiceHandle_t){0};

/**
 *   \brief Size of secure header.This is initialized when the context is
 *          SECURE.
 */
static uint8_t gSecHeaderSizeWords = 0;

/**
 *   \brief Maximum size(bytes) of a sciclient message.
 */
static uint32_t gSciclient_maxMsgSizeBytes;

/** \brief Flag to mention write in progress or not */
static uint32_t gSciclient_writeInProgress = 0U;

/**
 *  \brief Static Header for Security Messages.
 */
static struct tisci_sec_header gSciclient_secHeader;

/** \brief Pointer to structure that contains configuration parameters for
*       the sec_proxy IP */
extern CSL_SecProxyCfg *pSciclient_secProxyCfg;

static SemaphoreP_Object gSciclient_semObjects[SCICLIENT_MAX_QUEUE_SIZE];

/**<  Interrupt for notification **/
static HwiP_Object           gRespIntrObj[SCICLIENT_MAX_RESP_INTR_HANDLER];
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef QNX_OS
uint64_t Sciclient_qnxVirtToPhyFxn(const void *virtAddr,
                                   void *appData)
{
    int ret;
    off64_t    phyAddr = 0;
    uint32_t   length;
    int errno;

    if(appData != NULL_PTR) {
        length = (uint32_t) *((uint32_t *) appData);
    }
    else {
        printf("%s: Must specify memory size to map\n", __func__);
        return (-1);
    }

    /* Get destination physical address */
    ret = mem_offset64(virtAddr, NOFD, length, &phyAddr, NULL);
    if (ret != 0) {
        if (errno != EAGAIN) {
            printf("%s:Error from mem_offset - errno=%d\n", __func__, errno);
        }
        else if (phyAddr == NULL) {
            printf("%s:Error from mem_offset - errno=%d and phyAddr is NULL \n", __func__, errno);
        }
    }

    QNX_DEBUG_PRINT("%s: physical/0x%lx virtual/%p\n",__func__,phyAddr,virtAddr);
    return (uint64_t ) phyAddr;
}

void * Sciclient_qnxPhyToVirtFxn(uint64_t phyAddr,
                                 void *appData)
{
    uint64_t *temp = 0;
    uint32_t length = 0;


    if(appData != NULL_PTR) {
        length = (uint32_t) *((uint32_t *) appData);
    }
    else {
        printf("%s: Must specify memory size to map\n", __func__);
        return (NULL);
    }

    temp  = mmap_device_memory(0, length, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, phyAddr);
    if((temp == MAP_FAILED))
    {
        printf("%s: mmmap_device_memory failed\n",__func__);
    }
    QNX_DEBUG_PRINT("%s: physical/0x%lx virtual/%p\n",__func__, phyAddr, temp);
    return ((void *) temp);
}
#endif

int32_t Sciclient_configPrmsInit(Sciclient_ConfigPrms_t *pCfgPrms)
{
    int32_t ret = CSL_PASS;

    if(NULL != pCfgPrms)
    {
#if defined(BUILD_DM_R5) && (defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_J722S)) || defined(SOC_AM275X)
        Sciclient_DefaultBoardCfgInfo_t boardCfgInfo = {0};

        /* populate the default board configuration */
        ret = Sciclient_getDefaultBoardCfgInfo(&boardCfgInfo);
        if (ret == CSL_PASS)
        {
            if (((uint64_t)boardCfgInfo.boardCfgLowPm >= (uint64_t)SCICLIENT_ALLOWED_BOARDCFG_BASE_START) &&
                    ((uint64_t)boardCfgInfo.boardCfgLowPm < SCICLIENT_ALLOWED_BOARDCFG_BASE_END) &&
                    ((uint64_t)boardCfgInfo.boardCfgLowRm >= (uint64_t)SCICLIENT_ALLOWED_BOARDCFG_BASE_START) &&
                    ((uint64_t)boardCfgInfo.boardCfgLowRm < SCICLIENT_ALLOWED_BOARDCFG_BASE_END))
            {
                pCfgPrms->inPmPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowPm;
                pCfgPrms->inPmPrms.boardConfigHigh = 0U;
                pCfgPrms->inPmPrms.boardConfigSize = (uint16_t) boardCfgInfo.boardCfgLowPmSize;
                pCfgPrms->inPmPrms.devGrp = DEVGRP_ALL;

                pCfgPrms->inRmPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowRm;
                pCfgPrms->inRmPrms.boardConfigHigh = 0U;
                pCfgPrms->inRmPrms.boardConfigSize = (uint16_t) boardCfgInfo.boardCfgLowRmSize;
                pCfgPrms->inRmPrms.devGrp = DEVGRP_ALL;
            }
            else
            {
                ret = Sciclient_boardCfgParseHeader(
                            (uint8_t *) SCICLIENT_COMMON_X509_HEADER_ADDR,
                            &pCfgPrms->inPmPrms, &pCfgPrms->inRmPrms);
            }
        }
#endif
        pCfgPrms->opModeFlag     = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
        pCfgPrms->pBoardCfgPrms  = NULL;
        pCfgPrms->isSecureMode   = 0U;
        pCfgPrms->c66xRatRegion  = 15U;
        pCfgPrms->skipLocalBoardCfgProcess = 0U;
    }
    else
    {
        ret = CSL_EFAIL;
    }

    return ret;
}

int32_t Sciclient_updateOperModeToInterrupt(void)
{
    int32_t  status = CSL_PASS;
    uint32_t i = 0U;

    if (gSciclientHandle.opModeFlag != SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT)
    {
        gSciclientHandle.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT;

        /* Create Sciclient_ServiceHandle_t.semHandles */
        for (i = 0; i < SCICLIENT_MAX_QUEUE_SIZE; i++)
        {
            gSciclientHandle.semStatus[i] = 0u;
            gSciclientHandle.semHandles[i] = &gSciclient_semObjects[i];
            if (SemaphoreP_constructBinary(gSciclientHandle.semHandles[i], 0U) != SystemP_SUCCESS)
            {
                gSciclientHandle.semHandles[i] = NULL;
                status = CSL_EFAIL;
                break;

            }
        }

        /* Initialize currSeqId. Make sure currSeqId is never 0 */
        gSciclientHandle.currSeqId = 1U;

        if(CSL_PASS == status)
        {
            status = Sciclient_setupRespIntr(SCICLIENT_CONTEXT_SEC, SCICLIENT_SEC_RESP_INTR_HANDLER);
        }
        if(CSL_PASS == status)
        {
            status = Sciclient_setupRespIntr(SCICLIENT_CONTEXT_NONSEC, SCICLIENT_NON_SEC_RESP_INTR_HANDLER);
        }
        if(CSL_PASS == status)
        {
            status = Sciclient_setupRespIntr(SCICLIENT_CONTEXT_DM2TIFS, SCICLIENT_DM2TIFS_RESP_INTR_HANDLER);
        }

        if(CSL_PASS != status)
        {
            Sciclient_updateOperModeToPolled();
            status = CSL_EFAIL;
        }
    }
    else
    {
        /* If the response interrupts are not configured correctly for all sciclient contexts
         * then set status as failure
        */
        if ((gSciclientHandle.respIntr[SCICLIENT_SEC_RESP_INTR_HANDLER] != &gRespIntrObj[SCICLIENT_SEC_RESP_INTR_HANDLER]) ||
            (gSciclientHandle.respIntr[SCICLIENT_NON_SEC_RESP_INTR_HANDLER] != &gRespIntrObj[SCICLIENT_NON_SEC_RESP_INTR_HANDLER]) ||
            (gSciclientHandle.respIntr[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER] != &gRespIntrObj[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER]))
        {
            status = CSL_EFAIL;
        }
    }

    return status;
}

void Sciclient_updateOperModeToPolled(void)
{
    uint32_t i = 0U;
    if (gSciclientHandle.opModeFlag == SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT)
    {
        /* Delete Sciclient_ServiceHandle_t.semHandles */
        for (i = 0U; i < SCICLIENT_MAX_QUEUE_SIZE; i++)
        {
            if (gSciclientHandle.semHandles[i] != NULL)
            {
                (void) SemaphoreP_destruct(gSciclientHandle.semHandles[i]);
            }
        }
        /* De-register interrupts */
        if (gSciclientHandle.respIntr[SCICLIENT_NON_SEC_RESP_INTR_HANDLER] != NULL)
        {
            (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_NON_SEC_RESP_INTR_HANDLER]);
        }
        if (gSciclientHandle.respIntr[SCICLIENT_SEC_RESP_INTR_HANDLER] != NULL)
        {
            (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_SEC_RESP_INTR_HANDLER]);
        }
        if (gSciclientHandle.respIntr[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER] != NULL)
        {
            (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER]);
        }
    }
    gSciclientHandle.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
}

int32_t Sciclient_init(const Sciclient_ConfigPrms_t *pCfgPrms)
{
    int32_t   status = CSL_PASS;
    uintptr_t key;
    uint32_t b_doInit = 0U;

#ifdef QNX_OS

    /* Check if resource manager is already running, if so, do not initialize SCI */
    if(access("/dev/tisci",F_OK) != -1) {
        return status;
    }

    /* If using QNX at runtime need to remap addresses to be virtual */
    pSciclient_secProxyCfg->pSecProxyRegs     = (CSL_sec_proxyRegs *)
        mmap_device_memory(0, CSL_NAVSS0_SEC_PROXY0_CFG_MMRS_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_SEC_PROXY0_CFG_MMRS_BASE);
    pSciclient_secProxyCfg->pSecProxyScfgRegs = (CSL_sec_proxy_scfgRegs *)
        mmap_device_memory(0, CSL_NAVSS0_SEC_PROXY0_CFG_SCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_SEC_PROXY0_CFG_SCFG_BASE);
    pSciclient_secProxyCfg->pSecProxyRtRegs   = (CSL_sec_proxy_rtRegs *)
        mmap_device_memory(0, CSL_NAVSS0_SEC_PROXY0_CFG_RT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_SEC_PROXY0_CFG_RT_BASE);
    pSciclient_secProxyCfg->proxyTargetAddr   =  (uint64_t)
        mmap_device_io(CSL_NAVSS0_SEC_PROXY0_SRC_TARGET_DATA_SIZE, CSL_NAVSS0_SEC_PROXY0_SRC_TARGET_DATA_BASE);

    if((pSciclient_secProxyCfg->pSecProxyRegs == MAP_FAILED) ||
      (pSciclient_secProxyCfg->pSecProxyScfgRegs == MAP_FAILED) ||
      (pSciclient_secProxyCfg->pSecProxyRtRegs == MAP_FAILED)) {
        printf("%s: Failed to map device memory\n",__FUNCTION__);
        status = CSL_EBADARGS;
    }
    if(pSciclient_secProxyCfg->proxyTargetAddr == MAP_DEVICE_FAILED) {
        printf("%s: Failed to map device io  memory\n",__FUNCTION__);
        status = CSL_EBADARGS;
    }
#endif

    /* Updating gSciclientHandle.initCount is CRITICAL */
    key = HwiP_disable();
    gSciclientHandle.initCount++;
    if (gSciclientHandle.initCount == 1U)
    {
        b_doInit = 1U;
    }
    HwiP_restore(key);

    if(1U == b_doInit)
    {
        if (pCfgPrms != NULL)
        {
            /* Initialize Config params */
            if(pCfgPrms->opModeFlag ==
                SCICLIENT_SERVICE_OPERATION_MODE_POLLED)
            {
                Sciclient_updateOperModeToPolled();
            }
            else if (pCfgPrms->opModeFlag ==
                SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT)
            {
                status = Sciclient_updateOperModeToInterrupt();
            }
            else
            {
                status = CSL_EBADARGS;
            }
        }
        else
        {
            Sciclient_updateOperModeToPolled();
        }
        if (pCfgPrms != NULL)
        {
            if( (CSL_PASS==status) && ((pCfgPrms->isSecureMode==0U) ||
                    (pCfgPrms->isSecureMode==1U)) )
            {
                gSciclientHandle.isSecureMode = pCfgPrms->isSecureMode;
            }
            else
            {
                status = CSL_EBADARGS;
            }
        }
        else
        {
            gSciclientHandle.isSecureMode = 0U;
        }
#if defined(BUILD_DM_R5) && (defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined (SOC_J784S4)  || defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_J722S)) || defined(SOC_AM275X)
        if (pCfgPrms != NULL)
        {
            if (pCfgPrms->skipLocalBoardCfgProcess == FALSE)
            {
                /* set debug configuration */
                 if (status == CSL_PASS)
                {
                    status = Sciclient_setDebugConfig();
                }
                /* Run pm_init */
                if (status == CSL_PASS)
                {
                    status = Sciclient_boardCfgPm(&pCfgPrms->inPmPrms);
                    if (status == CSL_PASS)
                    {
                        gSciclientHandle.pmBoardConfigComplete = SCICLIENT_FT_PASS;
                    }
                    else
                    {
                        gSciclientHandle.pmBoardConfigComplete = SCICLIENT_FT_FAIL;
                    }
                }
                /* Run rm_init */
                if (status == CSL_PASS)
                {
                    status = Sciclient_boardCfgRm(&pCfgPrms->inRmPrms);
                    if (status == CSL_PASS)
                    {
                        gSciclientHandle.rmBoardConfigComplete = SCICLIENT_FT_PASS;
                    }
                    else
                    {
                        gSciclientHandle.rmBoardConfigComplete = SCICLIENT_FT_FAIL;
                    }
                }
            }
        }
#endif
#if defined(_TMS320C6X)
        if (pCfgPrms != NULL)
        {
            gSciclientHandle.c66xRatRegion = pCfgPrms->c66xRatRegion;
            status = Sciclient_C66xRatMap(pCfgPrms->c66xRatRegion);
        }
        else
        {
            gSciclientHandle.c66xRatRegion = SCICLIENT_RAT_ENTRY_DEFAULT;
            status = Sciclient_C66xRatMap(SCICLIENT_RAT_ENTRY_DEFAULT);
        }
#endif
    }
#ifndef QNX_OS
    if (status == CSL_PASS)
    {
        gSciclient_writeInProgress = 0U;
        status = Sciclient_abiCheck();
    }
#endif
    return status;
}

int32_t Sciclient_serviceGetThreadIds (const Sciclient_ReqPrm_t *pReqPrm,
                                       uint32_t *contextId,
                                       uint32_t *txThread,
                                       uint32_t *rxThread)
{
    int32_t  status    = CSL_PASS;

    *contextId = SCICLIENT_CONTEXT_MAX_NUM;
    if(pReqPrm == NULL)
    {
        status = CSL_EBADARGS;
    }
    if (status == CSL_PASS)
    {
        /* Get the context ID from the message */
        *contextId = Sciclient_getCurrentContext(pReqPrm->messageType);
    }
    if(*contextId < SCICLIENT_CONTEXT_MAX_NUM)
    {
#if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)  || defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM275X) || defined (SOC_J722S)
        /*
         * Derive the thread ID from the context. If the message is to be
         * forwarded, use the dedicated DM2DMSC queue. Otherwise, use the queue
         * determined by the global map.
         *
         * We should only ever get here in MCU1_0 builds. Otherwise there is an
         * error with the forwarding state, and we will see a firewall exception
         * when attempting to write to the queue.
         */
        if (pReqPrm->forwardStatus == SCISERVER_FORWARD_MSG)
        {
#if ! (defined(SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM275X) || defined (SOC_J722S))
            *txThread = TISCI_SEC_PROXY_DM2DMSC_WRITE_NOTIFY_RESP_THREAD_ID;
#else
            *txThread = TISCI_SEC_PROXY_DM2TIFS_WRITE_LOW_PRIORITY_THREAD_ID;
#endif
            *rxThread = TISCI_SEC_PROXY_DM2TIFS_READ_RESPONSE_THREAD_ID;
           /*
            * On j721e and j7200 devices, all services sent on non-secure queues
            * are first processed by the Sciserver instance on MCU R5F0 and
            * forwarded to DMSC if security-related configurations are required.
            *
            * In a similar manner, all applications running locally on MCU R5F0
            * will be handled directly and only forwarded to DMSC for additional
            * security-related processing if necessary.
            *
            * All service forwarding to DMSC is performed over the secure queue.
            * Therefore, we force Sciclient to use secure mode in this build
            * configuration.
            */
            *contextId = SCICLIENT_CONTEXT_DM2TIFS;
        }
        else
        {
#endif
#if defined (SOC_AM64X) || defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM275X) || defined (SOC_J722S)
            *txThread = gSciclientMap[*contextId].reqLowPrioThreadId;
#else
            *txThread = gSciclientMap[*contextId].reqHighPrioThreadId;
#endif
            *rxThread = gSciclientMap[*contextId].respThreadId;
#if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)  || defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM275X) || defined (SOC_J722S)
        }
#endif


        /* Find the Secure Message Header Size from the Context */
        if (gSciclientMap[*contextId].context == SCICLIENT_SECURE_CONTEXT)
        {
            gSecHeaderSizeWords = sizeof(struct tisci_sec_header)/sizeof(uint32_t);
        }
        else
        {
            gSecHeaderSizeWords = 0;
        }
        /* Secure Header is still not implemented in SYSFW. This is a place holder
         * to init the Secure Header.
         */
        gSciclient_secHeader.integ_check = (uint16_t)0;
        gSciclient_secHeader.rsvd = (uint16_t)0;
        /* Get the Max Message Size */
        gSciclient_maxMsgSizeBytes =
                CSL_secProxyGetMaxMsgSize(pSciclient_secProxyCfg) -
                CSL_SEC_PROXY_RSVD_MSG_BYTES;
    }
    else
    {
        status = CSL_EBADARGS;
    }

    return status;
}

int32_t Sciclient_servicePrepareHeader(const Sciclient_ReqPrm_t *pReqPrm,
                                       uint8_t *localSeqId,
                                       uint32_t contextId,
                                       struct tisci_header **header)
{
    int32_t  status    = CSL_PASS;
    struct tisci_header *dummyHdr;
    /* Run all error checks */
    if((pReqPrm == NULL) || (contextId == SCICLIENT_CONTEXT_MAX_NUM))
    {
        status = CSL_EBADARGS;
    }
    if(status == CSL_PASS)
    {
        dummyHdr = &((struct tisci_msg_version_req *)pReqPrm->pReqPayload)->hdr;
        if (dummyHdr == NULL)
        {
            status = CSL_EBADARGS;
        }
    }
    if(status == CSL_PASS)
    {
        *header = dummyHdr;
        /* This is done in such a fashion as the C66x does not honor a non word aligned
         * write.
         */
        Sciclient_utilByteCopy((uint8_t *)&(pReqPrm->messageType),
                               (uint8_t *)&((*header)->type),
                               sizeof(pReqPrm->messageType));

        (*header)->seq = (uint8_t) gSciclientHandle.currSeqId;
        *localSeqId = (uint8_t) gSciclientHandle.currSeqId;
        /* This is done in such a fashion as the C66x does not honor a non word aligned
         * write.
         */
        Sciclient_utilByteCopy((uint8_t *)&(pReqPrm->flags),
                               (uint8_t *)&((*header)->flags),
                               sizeof(pReqPrm->flags));
        /*
         * If the message is to be forwarded, do not override the host id
         * already present in the header.
         */
        if (pReqPrm->forwardStatus != SCISERVER_FORWARD_MSG)
        {
            /* Set host if this is not a forwarded message */
            (*header)->host = (uint8_t) gSciclientMap[contextId].hostId;
        } else {
            /* Set AOP flag if this is a forwarded message */
            (*header)->flags |= (uint32_t) TISCI_MSG_FLAG_AOP;
        }
    }
    return status;
}

static int32_t Sciclient_serviceGetPayloadSize(const Sciclient_ReqPrm_t *pReqPrm,
                                        const Sciclient_RespPrm_t      *pRespPrm,
                                        uint32_t *txPayloadSize,
                                        uint32_t *rxPayloadSize)
{
    int32_t status = CSL_PASS;
    if((pReqPrm == NULL) || (pRespPrm == NULL))
    {
        status = CSL_EBADARGS;
    }
    if (status == CSL_PASS)
    {
        /* The request Payload is expected to have the Header the payload */
        if (pReqPrm->reqPayloadSize > 0U)
        {
            *txPayloadSize = pReqPrm->reqPayloadSize -
                            sizeof(struct tisci_header);
        }
        else
        {
            *txPayloadSize = 0U;
        }
        /* Check if the payload is greater than the total message size */
        if (*txPayloadSize > gSciclient_maxMsgSizeBytes)
        {
            status = CSL_EBADARGS;
        }
        /* If the payload size is non zero as the payload pointer is 0
         * then we must error out.
         */
        if ((*txPayloadSize > 0U) && (pReqPrm->pReqPayload == NULL))
        {
            status = CSL_EBADARGS;
        }
        /* The response Payload is expected to have the Header the payload */
        if (pRespPrm->respPayloadSize > 0U)
        {
            *rxPayloadSize = pRespPrm->respPayloadSize;
        }
        else
        {
            *rxPayloadSize = 0U;
        }
        /* Check if the payload is greater than the total message size */
        if (*rxPayloadSize > gSciclient_maxMsgSizeBytes)
        {
            status = CSL_EBADARGS;
        }
        /* If the payload size is non zero as the payload pointer is 0
         * then we must error out.
         */
        if ((*rxPayloadSize > 0U) && (pRespPrm->pRespPayload == NULL))
        {
            status = CSL_EBADARGS;
        }
    }
    return status;
}


/* HWI_disable instead of semaphores for MCAL polling based. define in separate files*/
int32_t Sciclient_serviceSecureProxy(const Sciclient_ReqPrm_t *pReqPrm,
                                     Sciclient_RespPrm_t      *pRespPrm)
{
    int32_t           status       = CSL_PASS;
    uint32_t          i            = 0U;
    uint32_t          initialCount = 0U;
    /* size of request payload in bytes  */
    uint32_t          txPayloadSize =0U;
    /* size of response payload in bytes */
    uint32_t          rxPayloadSize =0U;
    uint8_t           *pLocalRespPayload = NULL;
    volatile Sciclient_RomFirmwareLoadHdr_t *pLocalRespHdr = NULL;
    uint32_t          txThread;
    uint32_t          contextId;
    uint32_t          rxThread;
    uint8_t           localSeqId;
    uintptr_t         key = 0U;
    uint32_t          timeToWait;
    uint32_t numWords = 0U;
    uint8_t  trailBytes = 0;
    struct tisci_header *header;

    status = Sciclient_serviceGetThreadIds (pReqPrm, &contextId, &txThread,
                                            &rxThread);
    if (status == CSL_PASS)
    {
        status = Sciclient_serviceGetPayloadSize(pReqPrm, pRespPrm,
                 &txPayloadSize, &rxPayloadSize);
    }
    if (status == CSL_PASS)
    {
        pLocalRespPayload = (uint8_t *)(pRespPrm->pRespPayload);
    }

    /* CRITICAL Section */
    key = HwiP_disable();
    timeToWait = pReqPrm->timeout;
    while (gSciclient_writeInProgress == 1U)
    {
        HwiP_restore(key);
        if (timeToWait > 0U)
        {
            timeToWait--;
        }
        else
        {
            status = CSL_ETIMEOUT;
            break;
        }
        ClockP_usleep((uint32_t)ClockP_ticksToUsec(10));
        key = HwiP_disable();
    }
    gSciclient_writeInProgress = 1U;
    HwiP_restore(key);

    if (CSL_PASS == status)
    {
        status = Sciclient_servicePrepareHeader(pReqPrm, &localSeqId,
                 contextId, &header);
    }
    if (CSL_PASS == status)
    {
        /* This is done to remove stray messages(due to timeout) in a thread
         * in case of "polling". */
        if (gSciclientHandle.opModeFlag ==
             SCICLIENT_SERVICE_OPERATION_MODE_POLLED)
        {
            Sciclient_flush(rxThread, gSciclient_maxMsgSizeBytes);
        }
        /* Verify thread status before reading/writing */
        status = Sciclient_verifyThread(txThread);
    }
    if (CSL_PASS == status)
    {
        status = Sciclient_waitThread(txThread, pReqPrm->timeout);
    }
    if (CSL_PASS == status)
    {
        /* Send Message */
        initialCount = Sciclient_readThreadCount(rxThread);
        Sciclient_sendMessage(txThread,
                              (const uint8_t *)&gSciclient_secHeader,
                              gSecHeaderSizeWords,
                              (uint8_t *) header,
                              (pReqPrm->pReqPayload +
                              sizeof(struct tisci_header)),
                              txPayloadSize,
                              gSciclient_maxMsgSizeBytes);

        timeToWait = pReqPrm->timeout;
        pLocalRespHdr = (struct tisci_header *)(CSL_secProxyGetDataAddr(
            pSciclient_secProxyCfg, rxThread, 0U)
            + ((uintptr_t) gSecHeaderSizeWords * (uintptr_t) 4U));
        /* Verify thread status before reading/writing */
        status = Sciclient_verifyThread(rxThread);
    }
    /* Wait for response: Polling based waiting */
    /* Poll for response if the operating mode is polled and
     * it is a message with TISCI_MSG_FLAG_AOP flag set in the header.
     */
    if ((gSciclientHandle.opModeFlag == SCICLIENT_SERVICE_OPERATION_MODE_POLLED) &&
        (status == CSL_PASS) &&
        ((header->flags & TISCI_MSG_FLAG_MASK) != 0U) &&
        (pLocalRespHdr != NULL))
    {
        /* Check if some message is received*/
        while (((HW_RD_REG32(Sciclient_threadStatusReg(rxThread)) &
                CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) - initialCount) <= 0U)
        {
            if (timeToWait > 0U)
            {
                timeToWait--;
            }
            else
            {
                status = CSL_ETIMEOUT;
                break;
            }
        }
        if (status == CSL_PASS)
        {
            /* Check the seqId of response*/
            status = CSL_ETIMEOUT;
            timeToWait =  pReqPrm->timeout;
            while (timeToWait > 0U)
            {
                uint32_t numCurrentMsgs =
                        (HW_RD_REG32(Sciclient_threadStatusReg(rxThread)) &
                        CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) -
                        initialCount;
                if (pLocalRespHdr != NULL)
                {
                    if (pLocalRespHdr->seq == ((uint32_t) localSeqId))
                    {
                        status = CSL_PASS;
                        break;
                    }
                }
                if (numCurrentMsgs > 1U)
                {
                    (void) Sciclient_readThread32(rxThread,
                           (uint8_t)((gSciclient_maxMsgSizeBytes/4U) - 1U));
                }
                timeToWait--;
            }
        }
    }
    key = HwiP_disable();
    gSciclient_writeInProgress = 0U;
    HwiP_restore(key);

    /* Wait for response: Interrupt based waiting */
    /* Wait for interrupt if the operating mode is interrupt mode and
     * it is a message with TISCI_MSG_FLAG_AOP flag set in the header.
     */
    if ((gSciclientHandle.opModeFlag ==
         SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT) &&
        (status == CSL_PASS) &&
        ((header->flags & TISCI_MSG_FLAG_MASK) != 0U))
    {
        status = SemaphoreP_pend(gSciclientHandle.semHandles[localSeqId],timeToWait);
        gSciclientHandle.semStatus[localSeqId] = status;
    }

    if(status == CSL_PASS)
    {
        numWords   = (uint32_t) (rxPayloadSize / 4U);
        trailBytes = (uint8_t) (rxPayloadSize - (numWords * 4U));
        /* Read the full message */
        pRespPrm->flags = Sciclient_readThread32(rxThread, 1U+gSecHeaderSizeWords);

        for (i = 0; i < numWords; i++)
        {
            uint32_t tempWord = Sciclient_readThread32(
                rxThread,
                ((uint8_t) i + gSecHeaderSizeWords));
            uint8_t * tempWordPtr = (uint8_t*) & tempWord;
            uint32_t j = 0U;
            for (j = 0U; j < 4U; j++)
            {
                *(pLocalRespPayload + (i * 4U) + j) = *tempWordPtr;
                tempWordPtr++;
            }

        }

        if (trailBytes > 0U)
        {
            uint32_t tempWord = Sciclient_readThread32(
                    rxThread,
                    ((uint8_t)i + gSecHeaderSizeWords));
            uint8_t * pTempWord = (uint8_t*) &tempWord;
            Sciclient_utilByteCopy(pTempWord,
                                   (uint8_t*)pLocalRespPayload + (i * 4U),
                                   trailBytes);
        }

        /* Read the last register of the rxThread */
        (void) Sciclient_readThread32(rxThread,
                            (uint8_t)((gSciclient_maxMsgSizeBytes/4U) - 1U));
    }

    if ((status == CSL_PASS) &&
        (gSciclientHandle.opModeFlag == SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT) &&
        (contextId != SCICLIENT_CONTEXT_MAX_NUM)
       )
    {
        (void)HwiP_clearInt( gSciclientMap[contextId].respIntrNum);
        (void)HwiP_enableInt( gSciclientMap[contextId].respIntrNum);
    }
    return status;
}

int32_t Sciclient_deinit(void)
{
    int32_t   status = CSL_PASS;
    /* gSciclientHandle.initCount is critical */
    uint32_t doDeInit = 0;
    uintptr_t key = HwiP_disable();

#if defined(_TMS320C6X)
    CSL_ratRegs *pC66xRatRegs = (CSL_ratRegs *)CSL_C66_COREPAC_C66_RATCFG_BASE;
#endif

    if (gSciclientHandle.initCount == 1U)
    {
        doDeInit = 1U;
    }
    gSciclientHandle.initCount--;
    HwiP_restore(key);

    if (1U == doDeInit)
    {
        uint32_t i = 0U;
        if ((gSciclientHandle.opModeFlag ==
         SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT) &&
        (status == CSL_PASS))
        {
            /* Delete Sciclient_ServiceHandle_t.semHandles */
            for (i = 0U; i < SCICLIENT_MAX_QUEUE_SIZE; i++)
            {
                if (gSciclientHandle.semHandles[i] != NULL)
                {
                    (void) SemaphoreP_destruct(gSciclientHandle.semHandles[i]);
                }
            }
            /* De-register interrupts */
            if (gSciclientHandle.respIntr[SCICLIENT_NON_SEC_RESP_INTR_HANDLER] != NULL)
            {
                (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_NON_SEC_RESP_INTR_HANDLER]);
            }
            if (gSciclientHandle.respIntr[SCICLIENT_SEC_RESP_INTR_HANDLER] != NULL)
            {
                (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_SEC_RESP_INTR_HANDLER]);
            }
            if (gSciclientHandle.respIntr[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER] != NULL)
            {
                (void) HwiP_destruct(gSciclientHandle.respIntr[SCICLIENT_DM2TIFS_RESP_INTR_HANDLER]);
            }

        }
        gSciclientHandle.opModeFlag = 0xDEAD;
#if defined(_TMS320C6X)
        CSL_ratDisableRegionTranslation(pC66xRatRegs, gSciclientHandle.c66xRatRegion);
#endif
    }
    return status;
}

int32_t Sciclient_abiCheck(void)
{
    int32_t status = CSL_PASS;
    /* Send getRevision message for ABI Revision Check */
    /*THINK: What should be the appropriate timeout value here? */
    struct tisci_msg_version_req request;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof (request),
        SCICLIENT_SERVICE_WAIT_FOREVER,
        SCISERVER_NO_FORWARD_MSG
    };

    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        (uint32_t) sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    if ((status != CSL_PASS) ||
        (respPrm.flags != TISCI_MSG_FLAG_ACK) ||
        ((uint32_t)(response.abi_major) != SCICLIENT_FIRMWARE_ABI_MAJOR) )
    {
        status = CSL_EFAIL;
    }

    return status;
}

#if defined(BUILD_DM_R5) && (defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_J722S)) || defined(SOC_AM275X)
int32_t Sciclient_setDebugConfig(void)
{
    int32_t retVal = CSL_PASS;

    struct tisci_get_trace_config_req request;
    Sciclient_ReqPrm_t reqParam = {0};

    struct tisci_get_trace_config_resp response;
    Sciclient_RespPrm_t respParam = {0};

    reqParam.messageType    = (uint16_t) TISCI_MSG_GET_TRACE_CONFIG;
    reqParam.flags          = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) SCICLIENT_SERVICE_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof (response);

    retVal = Sciclient_service(&reqParam, &respParam);

    if((retVal != CSL_PASS) ||
        ((reqParam.flags != 0U) &&
        ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK)))
    {
        retVal = CSL_EFAIL;
    }

    if(retVal == CSL_PASS){
        trace_reconfigure(response.trace_src_enables, response.trace_dst_enables);
#if defined(CONFIG_LPM_DM)
        lpm_trace_reconfigure(response.trace_src_enables, response.trace_dst_enables);
#endif
    }

    return retVal;
}
#endif
uint32_t Sciclient_getCurrentContext(uint16_t messageType)
{
    uint32_t retVal = SCICLIENT_CONTEXT_MAX_NUM;

    switch (messageType) {
        case TISCI_MSG_BOOT_NOTIFICATION:
        case TISCI_MSG_SEC_HANDOVER:
        case TISCI_MSG_BOARD_CONFIG:
        case TISCI_MSG_BOARD_CONFIG_SECURITY:
        case TISCI_MSG_SA2UL_SET_DKEK:
        case TISCI_MSG_SA2UL_GET_DKEK:
        case TISCI_MSG_SA2UL_RELEASE_DKEK:
        case TISCI_MSG_SA2UL_SET_DSMEK:
        case TISCI_MSG_SA2UL_GET_DSMEK:
        case TISCI_MSG_SA2UL_RELEASE_DSMEK:
        case TISCI_MSG_OPEN_DEBUG_FWLS:
        case TISCI_MSG_WRITE_OTP_ROW:
        case TISCI_MSG_READ_OTP_MMR:
        case TISCI_MSG_LOCK_OTP_ROW:
        case TISCI_MSG_GET_OTP_ROW_LOCK_STATUS:
        case TISCI_MSG_SOFT_LOCK_OTP_WRITE_GLOBAL:
        case TISCI_MSG_READ_SWREV:
        case TISCI_MSG_WRITE_SWREV:
        case TISCI_MSG_READ_KEYCNT_KEYREV:
        case TISCI_MSG_KEY_WRITER:
        case TISCI_MSG_WRITE_KEYREV:
        case TISCI_MSG_ENTER_SLEEP:
            retVal = SCICLIENT_CONTEXT_SEC;
            break;

        default:
            /* For all other message type use non-secure context */
            retVal = SCICLIENT_CONTEXT_NONSEC;
            if(gSciclientHandle.isSecureMode == 1U)
            {
                retVal = SCICLIENT_CONTEXT_SEC;
            }
            break;
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void Sciclient_ISR(uintptr_t arg)
{
    int32_t contextId = (int32_t )(arg);
    if(contextId  >= 0)
    {
        uint32_t rxThread = gSciclientMap[contextId].respThreadId;
        if(gSciclientMap[contextId].context == SCICLIENT_SECURE_CONTEXT)
        {
            gSecHeaderSizeWords = sizeof(struct tisci_sec_header)/sizeof(uint32_t);
        }
        else
        {
            gSecHeaderSizeWords = 0;
        }
        volatile Sciclient_RomFirmwareLoadHdr_t *pLocalRespHdr =
                (struct tisci_header *)(CSL_secProxyGetDataAddr(
                                                pSciclient_secProxyCfg,rxThread,0U)
                                        + ((uintptr_t) gSecHeaderSizeWords * (uintptr_t) 4U));
        uint8_t seqId = pLocalRespHdr->seq;
        if ((gSciclientHandle.semStatus[seqId] == 0) && (seqId != 0U))
        {
            HwiP_disableInt( (uint32_t) gSciclientMap[contextId].respIntrNum);
            (void) SemaphoreP_post(gSciclientHandle.semHandles[seqId]);
            HwiP_clearInt( (uint32_t) gSciclientMap[contextId].respIntrNum);
        }
        else
        {
            /* This implies that the SemaphoreP_pend for this seqId failed.
            *  So, we need to flush this message.*/
            (void) Sciclient_readThread32(rxThread,
                                (uint8_t)((gSciclient_maxMsgSizeBytes/4U) - 1U));
            gSciclientHandle.semStatus[seqId] = 0;
            HwiP_clearInt( (uint32_t) gSciclientMap[contextId].respIntrNum);
        }
    }
}

int32_t Sciclient_contextIdFromIntrNum(uint32_t intrNum)
{
    int32_t retVal = CSL_EFAIL;
    uint32_t i = 0U;
    while ((i < SCICLIENT_CONTEXT_MAX_NUM) &&
        (gSciclientMap[i].respIntrNum != intrNum))
    {
        i++;
    }
    if (i < SCICLIENT_CONTEXT_MAX_NUM)
    {
        retVal = (int32_t)i;
    }
    return retVal;
}

static int32_t Sciclient_setupRespIntr(uint32_t contextId, uint8_t sciclientRespIntrHandler)
{
    int32_t status = CSL_PASS;
    if(contextId < SCICLIENT_CONTEXT_MAX_NUM)
    {
        if ((uint32_t) gSciclientMap[contextId].respIntrNum != 0U)
        {
            HwiP_Params  hwiInputParams;
            uint32_t     rxThread;

            HwiP_clearInt((uint32_t) gSciclientMap[contextId].respIntrNum);
            rxThread = gSciclientMap[contextId].respThreadId;
            CSL_secProxyGetDataAddr(pSciclient_secProxyCfg, rxThread, 0U);

            /* Get the Max Message Size */
            gSciclient_maxMsgSizeBytes =
                    CSL_secProxyGetMaxMsgSize(pSciclient_secProxyCfg) -
                    CSL_SEC_PROXY_RSVD_MSG_BYTES;
            Sciclient_flush(rxThread, gSciclient_maxMsgSizeBytes);

            HwiP_Params_init(&hwiInputParams);

            /* Populate the interrupt parameters */
            hwiInputParams.intNum   = (uint32_t) gSciclientMap[contextId].respIntrNum;
            hwiInputParams.callback = (HwiP_FxnCallback) &Sciclient_ISR;
            hwiInputParams.args     = (void*) contextId;

            /* Disable and Clear Interrupt */
            HwiP_disableInt(hwiInputParams.intNum);
            HwiP_clearInt(hwiInputParams.intNum);

            /* Register interrupts based on the corresponding response interrupt handler */
            gSciclientHandle.respIntr[sciclientRespIntrHandler] = &gRespIntrObj[sciclientRespIntrHandler];
            status =  HwiP_construct(gSciclientHandle.respIntr[sciclientRespIntrHandler],&hwiInputParams);
            if(SystemP_SUCCESS != status)
            {
                gSciclientHandle.respIntr[sciclientRespIntrHandler] = (HwiP_Object*) NULL;
            }
            (void)HwiP_enableInt(hwiInputParams.intNum);
        }
    }
    else
    {
        status = CSL_EFAIL;
    }

    return status;
}

static void Sciclient_utilByteCopy(uint8_t *src,
                                   uint8_t *dest,
                                   uint32_t num_bytes)
{
    uint32_t i;
    uint8_t *srcP = src;
    uint8_t *destP = dest;

    for(i=0; i < num_bytes; i++)
    {
        *destP = *srcP;
         destP++;
         srcP++;
    }
}

#if defined(_TMS320C6X)
static int32_t Sciclient_C66xRatMap(uint32_t ratRegion)
{
    int32_t status = CSL_PASS;
    CSL_ratRegs *pC66xRatRegs = (CSL_ratRegs *)CSL_C66_COREPAC_C66_RATCFG_BASE;
    CSL_RatTranslationCfgInfo TranslationCfg;

#if defined(BUILD_C66X_1)
    TranslationCfg.sizeInBytes = CSL_C66SS0_INTROUTER0_INTR_ROUTER_CFG_SIZE;
    TranslationCfg.baseAddress = CSL_C66SS0_INTROUTER0_INTR_ROUTER_CFG_BASE + CSL_C66_COREPAC_RAT_REGION_BASE;
    TranslationCfg.translatedAddress = CSL_C66SS0_INTROUTER0_INTR_ROUTER_CFG_BASE;
#endif
#if defined(BUILD_C66X_2)
    TranslationCfg.sizeInBytes = CSL_C66SS1_INTROUTER0_INTR_ROUTER_CFG_SIZE;
    TranslationCfg.baseAddress = CSL_C66SS1_INTROUTER0_INTR_ROUTER_CFG_BASE + CSL_C66_COREPAC_RAT_REGION_BASE;
    TranslationCfg.translatedAddress = CSL_C66SS1_INTROUTER0_INTR_ROUTER_CFG_BASE;
#endif

    if (ratRegion < CSL_ratGetMaxRegions(pC66xRatRegs)) {
        if (CSL_ratIsRegionTranslationEnabled(pC66xRatRegs, ratRegion) == false) {
            CSL_ratEnableRegionTranslation(pC66xRatRegs, ratRegion);
            CSL_ratConfigRegionTranslation(pC66xRatRegs, ratRegion, &TranslationCfg);
        }
        else
        {
            status = CSL_EFAIL;
        }
    }
    else
    {
        status = CSL_EBADARGS;
    }

    return status;
}
#endif
