/*
 * Copyright (C) 2024 Texas Instruments Incorporated
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
#include <kernel/dpl/DebugP.h>
#if defined ENABLE_SCICLIENT_DIRECT
/* DM R5 will use the SCI Client direct */
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* TISCI ID of the new host to hand over control to */
#if defined(SOC_AM62PX)
#define TISCI_MSG_PROC_HANDOVER_HOST_ID             (TISCI_HOST_ID_A53_0)
#elif defined(SOC_AM62AX)
#define TISCI_MSG_PROC_HANDOVER_HOST_ID             (TISCI_HOST_ID_MAIN_0_R5_1)
#endif
/* Processor ID of the core to be handed over to the host */
#define TISCI_MSG_PROC_HANDOVER_PROCESSOR_ID        (SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0)
/* Length of derived KEK in bytes */
#define TISCI_MSG_SA2UL_DKEK_KEY_LEN                (32U)
/* Length of SOC UID in bytes */
#define TISCI_MSG_SOC_UID_LEN                       (32U)

/* ========================================================================== */
/*                       Structure Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static int32_t TISCIApp_procHandover(uint8_t hostId, uint8_t processorId);
static int32_t TISCIApp_getUniqueID();
static int32_t TISCIApp_SA2ULSetDKEK();
static int32_t TISCIApp_SA2ULReleaseDKEK();
static int32_t TISCIApp_SA2ULGetDKEK();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void tisci_msg_main(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("TISCI message example!\r\n");

    status = TISCIApp_procHandover(TISCI_MSG_PROC_HANDOVER_HOST_ID, TISCI_MSG_PROC_HANDOVER_PROCESSOR_ID);

    if(status == SystemP_SUCCESS)
    {
        status = TISCIApp_getUniqueID();
    }

    if(status == SystemP_SUCCESS)
    {
        status = TISCIApp_SA2ULSetDKEK();
    }

    if(status == SystemP_SUCCESS)
    {
        status = TISCIApp_SA2ULReleaseDKEK();
    }

    if(status == SystemP_SUCCESS)
    {
        status = TISCIApp_SA2ULGetDKEK();
    }

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed\r\n");
    }

    return;
}

static int32_t TISCIApp_procHandover(uint8_t hostId, uint8_t processorId)
{
    int32_t status = SystemP_FAILURE;

    /* Request for physical processor control so that the processor can be handed over to other valid hosts */
    status = Sciclient_procBootRequestProcessor(processorId, SystemP_WAIT_FOREVER);

    if(status == SystemP_SUCCESS)
    {
        /* Request to handover control of a processor to another valid host */
        status = Sciclient_procBootHandoverProcessor(processorId, hostId, SystemP_WAIT_FOREVER);
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Handover physical processor core to requested host... DONE !!!\r\n");
    }
    else
    {
        DebugP_logError("Handover physical processor cores to requested host... Failed !!!\r\n");
    }

    return status;
}

static int32_t TISCIApp_getUniqueID()
{
    int32_t status = SystemP_FAILURE;
    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;
    struct tisci_msg_get_soc_uid_req request;
    struct tisci_msg_get_soc_uid_resp response;

    /* Byte array to store the SOC UID*/
    uint8_t soc_uid[TISCI_MSG_SOC_UID_LEN] = {0};

    /* Request to get the SOC unique ID */
    reqParam.messageType      = (uint16_t) TISCI_MSG_GET_SOC_UID;
    reqParam.flags            = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

	if ((status == SystemP_SUCCESS) && ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
	{
		DebugP_log("Get unique SOC ID... DONE !!! \r\n");

        /* Copy the SOC UID response to the byte array*/
        memcpy(&soc_uid[0], response.soc_uid, TISCI_MSG_SOC_UID_LEN);

        /* Print the SOC UID*/
        DebugP_log("SOC UID: 0x");
        for(volatile int i = 0; i < TISCI_MSG_SOC_UID_LEN; i++)
            DebugP_log("%02x",soc_uid[i]);
        DebugP_log("\r\n");
	}
	else
	{
		DebugP_logError("Get unique SOC ID... Failed !!!\r\n");
		status = SystemP_FAILURE;
	}

    return status;
}

static int32_t TISCIApp_SA2ULSetDKEK()
{
    int32_t status = SystemP_FAILURE;
    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;
    struct tisci_msg_sa2ul_set_dkek_req request;
    struct tisci_msg_sa2ul_set_dkek_resp response;

    char *label = "Secure storage key";
    const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

    /* set label and context of the DKEK*/
    request.sa2ul_instance = 0;
    memcpy(&request.kdf_label_and_context[0], label, sizeof(*label));
    request.kdf_label_len = sizeof(*label);
    memcpy(&request.kdf_label_and_context[request.kdf_label_len], context, sizeof(context));
    request.kdf_context_len = sizeof(context);

    /* Request to set the DKEK SA2UL instance 0 */
    reqParam.messageType      = (uint16_t) TISCI_MSG_SA2UL_SET_DKEK;
    reqParam.flags            = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

	if ((status == SystemP_SUCCESS) && ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
	{
		DebugP_log("Set DKEK to SA2UL instance... DONE !!! \r\n");
	}
	else
	{
		DebugP_logError("Set DKEK to SA2UL instance.. Failed !!!\r\n");
		status = SystemP_FAILURE;
	}

    return status;
}

static int32_t TISCIApp_SA2ULReleaseDKEK()
{
    int32_t status = SystemP_FAILURE;
    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;
    struct tisci_msg_sa2ul_release_dkek_req request;
    struct tisci_msg_sa2ul_release_dkek_resp response;

    request.sa2ul_instance = 0;

    /* Request to release the DKEK SA2UL instance 0 */
    reqParam.messageType      = (uint16_t) TISCI_MSG_SA2UL_RELEASE_DKEK;
    reqParam.flags            = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

	if ((status == SystemP_SUCCESS) && ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
	{
		DebugP_log("Release DKEK from SA2UL DKEK register... DONE !!! \r\n");
	}
	else
	{
		DebugP_logError("Release DKEK from SA2UL DKEK register.. Failed !!!\r\n");
		status = SystemP_FAILURE;
	}

    return status;
}

static int32_t TISCIApp_SA2ULGetDKEK()
{
    int32_t status = SystemP_FAILURE;
    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;
    struct tisci_msg_sa2ul_get_dkek_req request;
    struct tisci_msg_sa2ul_get_dkek_resp response = {0};

    char *label = "Secure storage key";
    const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

    /* Byte array to store the DKEK*/
    uint8_t dkek[TISCI_MSG_SA2UL_DKEK_KEY_LEN] = {0};

    /* set label and context of the DKEK*/
    request.sa2ul_instance = 0;
    memcpy(&request.kdf_label_and_context[0], label, sizeof(*label));
    request.kdf_label_len = sizeof(*label);
    memcpy(&request.kdf_label_and_context[request.kdf_label_len], context, sizeof(context));
    request.kdf_context_len = sizeof(context);

    /* Request to set the DKEK SA2UL instance 0 */
    reqParam.messageType      = (uint16_t) TISCI_MSG_SA2UL_GET_DKEK;
    reqParam.flags            = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

	if ((status == SystemP_SUCCESS) && ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK))
	{
		DebugP_log("Get DKEK for the given label and context... DONE !!! \r\n");

        /* Copy the DKEK response value to the byte array*/
        memcpy(&dkek[0], response.dkek, SA2UL_DKEK_KEY_LEN);

        /* Print the derived KEK */
        DebugP_log("DKEK: 0x");
        for(volatile int i = 0; i < TISCI_MSG_SA2UL_DKEK_KEY_LEN; i++)
            DebugP_log("%02x",dkek[i]);
        DebugP_log("\r\n");
	}
	else
	{
		DebugP_logError("Get DKEK for the given label and context.. Failed !!!\r\n");
		status = SystemP_FAILURE;
	}

    return status;
}
