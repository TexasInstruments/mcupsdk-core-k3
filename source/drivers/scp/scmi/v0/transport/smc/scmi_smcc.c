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
 */

/**
 *  \file scmi_smcc.c
 *
 *  \brief File containing scmi smcc APIs implementation.
 *
 */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/scp/smccc/smccc.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/transport/scmi_sm.h>
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCMI_SMCCC_RET_NOT_SUPPORTED                            ((uint32_t)-1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t SCMI_smccProcessMessage(SCMI_Handle handle,
                                            SCMI_MessageData *message);
static int32_t SCMI_smccFetchResponse(SCMI_Handle handle,
                                           SCMI_MessageData *message);
static inline uint32_t SCMI_smccFunction(uint32_t functionId, uint32_t arg0,
                                         uint32_t arg1, uint32_t arg2);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SCMI_TransportFxns gScmiSmccTransportFxns =
{
    .fetchResponseFxn = SCMI_smccFetchResponse,
    .processMessageFxn = SCMI_smccProcessMessage,
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static int32_t SCMI_smccProcessMessage(SCMI_Handle handle,
                                            SCMI_MessageData *message)
{
    int32_t status = SystemP_FAILURE;
    SCMI_Object *obj = ((SCMI_Config *)handle)->object;
    SCMI_TransportObject *transport = (SCMI_TransportObject *)obj->transferObject;

    status = SCMI_writeMessageToSharedMemory(handle, message);

    if(status == SystemP_SUCCESS)
    {
        if(SCMI_smccFunction(transport->smccFuntionID, 0U, 0U, 0U) == \
                             SCMI_SMCCC_RET_NOT_SUPPORTED)
        {
            status = SystemP_FAILURE;
        }
        else
        {
            status = SCMI_readResponseFromSharedMemory(handle, message);
        }
    }

    SCMI_clearSharedMemoryChannel(handle);

    return status;
}

static int32_t SCMI_smccFetchResponse(SCMI_Handle handle,
                                           SCMI_MessageData *message)
{
    int32_t status = SystemP_FAILURE;

    status = SCMI_readResponseFromSharedMemory(handle, message);

    return status;
}

static inline uint32_t SCMI_smccFunction(uint32_t functionId, uint32_t arg0,
                                         uint32_t arg1, uint32_t arg2)
{
	SMCCC_Res res;
	smccc_smc(functionId, arg0, arg1, arg2, 0, 0, 0, 0, &res);

    return (uint32_t) res.a0;
}