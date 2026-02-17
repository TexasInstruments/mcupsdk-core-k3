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
 *  \file am275x/sciclient_fmwSecureProxyMap.c
 *
 *  \brief File containing the secure proxy map for all hosts.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#if defined (ENABLE_SCICLIENT_DIRECT)
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif
#include <drivers/sciclient/sciclient_priv.h>

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

const Sciclient_MapStruct_t gSciclientMap[SCICLIENT_CONTEXT_MAX_NUM] =
{
    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** Host ID of the WKUP-R5(secure) */
        TISCI_HOST_ID_WKUP_0_R5_0,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_WKUP_0_R5_0_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_WKUP_0_R5_0_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_WKUP_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_40

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the WKUP-R5(non-secure) */
        TISCI_HOST_ID_WKUP_0_R5_1,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_WKUP_0_R5_1_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_WKUP_0_R5_1_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_WKUP_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_41

    },

    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_0_0(secure) */
        TISCI_HOST_ID_MAIN_0_R5_0,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_0_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_152

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_0_0(non-secure) */
        TISCI_HOST_ID_MAIN_0_R5_1,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_1_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_153

    },

    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_0_1(secure) */
        TISCI_HOST_ID_MAIN_0_R5_2,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_2_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS0_CORE1_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_154

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_0_1(non-secure) */
        TISCI_HOST_ID_MAIN_0_R5_3,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_0_R5_3_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS0_CORE1_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_155

    },

    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_1_0(secure) */
        TISCI_HOST_ID_MAIN_1_R5_0,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_0_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS1_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_0

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_1_0(non-secure) */
        TISCI_HOST_ID_MAIN_1_R5_1,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_1_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS1_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_1

    },

    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_1_1(secure) */
        TISCI_HOST_ID_MAIN_1_R5_2,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_2_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS1_CORE1_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_2

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the MAIN-R5_1_1(non-secure) */
        TISCI_HOST_ID_MAIN_1_R5_3,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_MAIN_1_R5_3_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number */
        CSLR_R5FSS1_CORE1_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_3

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the C7x_0_0(non-secure) */
        TISCI_HOST_ID_C7X_0_0,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_C7X_0_0_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_C7X_0_0_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number.**/
        CSLR_C7X256V0_CLEC_GIC_SPI_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_32

    },

    {
        /** Context **/
        SCICLIENT_NON_SECURE_CONTEXT,

        /** Host ID of the C7x_1_0(non-secure) */
        TISCI_HOST_ID_C7X_1_0,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_C7X_1_0_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_C7X_1_0_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number.**/
        CSLR_C7X256V1_CLEC_GIC_SPI_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_33

    },

    {
        /** Context **/
        SCICLIENT_SECURE_CONTEXT,

        /** DM to TIFS host id */
        TISCI_HOST_ID_DM2TIFS,

        /** Thread ID of the low priority thread(write) allowed for the CPU */
        TISCI_SEC_PROXY_DM2TIFS_WRITE_LOW_PRIORITY_THREAD_ID,

        /** Thread ID of the response thread(read) available for the CPU */
        TISCI_SEC_PROXY_DM2TIFS_READ_RESPONSE_THREAD_ID,

        /** Notification Interrupt Number.**/
        CSLR_WKUP_R5FSS0_CORE0_INTR_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_42

    }
};
