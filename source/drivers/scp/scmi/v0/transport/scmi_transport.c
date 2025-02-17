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
 *  \file scmi_transport.c
 *
 *  \brief File containing scmi transport APIs implementation.
 *
 */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SCMITransport_processMessage(SCMI_Handle handle,
                                     SCMI_MessageData *message)
{
    int32_t status = SystemP_FAILURE;

    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;
        SCMI_TransportObject *transport = (SCMI_TransportObject *)obj->transferObject;

        if(transport->trptFxns && transport->trptFxns->processMessageFxn)
        {
            /* Take the instance semaphore */
            status = SemaphoreP_pend(&transport->transportLock, SystemP_WAIT_FOREVER);

            status += transport->trptFxns->processMessageFxn(handle, message);

            /* Post the instance Semaphore. */
            SemaphoreP_post(&transport->transportLock);
        }

    }

    return status;
}

int32_t SCMITransport_fetchResponse(SCMI_Handle handle,
                                    SCMI_MessageData *message)
{
    int32_t status = SystemP_FAILURE;

    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;
        SCMI_TransportObject *transport = (SCMI_TransportObject *)obj->transferObject;

        if(transport->trptFxns && transport->trptFxns->fetchResponseFxn)
        {
            /* Take the instance semaphore */
            status = SemaphoreP_pend(&transport->transportLock, SystemP_WAIT_FOREVER);

            status += transport->trptFxns->fetchResponseFxn(handle, message);

            /* Post the instance Semaphore. */
            SemaphoreP_post(&transport->transportLock);
        }
    }

    return status;
}