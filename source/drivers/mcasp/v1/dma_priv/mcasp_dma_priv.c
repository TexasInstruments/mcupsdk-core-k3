/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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


#include <drivers/mcasp/v1/dma_priv/mcasp_dma_priv.h>

int32_t MCASP_getFreeTrpd(MCASP_DmaTrpdMemAlloc *trpdAlloc, uint8_t **pTrpdMem)
{
    int32_t status = SystemP_FAILURE;

    if(NULL != trpdAlloc)
    {
        while(MCASP_TRPD_INVALID_PTR != (uint32_t)trpdAlloc->pTrpdMem)
        {
            if(NULL != trpdAlloc->pTrpdMem)
            {
                if(0 == trpdAlloc->inUse)
                {
                    trpdAlloc->inUse = 1;
                    *pTrpdMem = trpdAlloc->pTrpdMem;

                    status = SystemP_SUCCESS;

                    break;
                }
            }
            trpdAlloc++;
        }
    }

    return status;
}

int32_t MCASP_postFreeTrpd(MCASP_DmaTrpdMemAlloc *trpdAlloc, uint64_t pTrpdMem)
{
    int32_t status = SystemP_FAILURE;

    if(NULL != trpdAlloc)
    {
        while(MCASP_TRPD_INVALID_PTR != (uint32_t)trpdAlloc->pTrpdMem )
        {
            if(trpdAlloc->pTrpdMem == (uint8_t *)pTrpdMem)
            {
                trpdAlloc->inUse = 0;
                status = SystemP_SUCCESS;
            }

            trpdAlloc++;
        }
    }

    return status;
}
