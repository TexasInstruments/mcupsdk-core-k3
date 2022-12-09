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
 *  \file sciclient_secureproxy.c
 *
 *  \brief File containing the SCICLIENT Secure proxy APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/hw_include/cslr_soc.h>
#include <string.h> /*For memcpy*/
#include <drivers/hw_include/csl_types.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Pointer to structure that contains configuration parameters for
*       the sec_proxy IP */
extern CSL_SecProxyCfg *pSciclient_secProxyCfg;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef QNX_OS
uintptr_t Sciclient_threadStatusReg(uint32_t thread)
{
    return ((uintptr_t)(pSciclient_secProxyCfg->pSecProxyRtRegs) +
        CSL_SEC_PROXY_RT_THREAD_STATUS(thread));
}
#else
uint32_t Sciclient_threadStatusReg(uint32_t thread)
{
    return ((uint32_t)(uintptr_t)(pSciclient_secProxyCfg->pSecProxyRtRegs) +
        CSL_SEC_PROXY_RT_THREAD_STATUS(thread));
}
#endif

uint32_t Sciclient_readThread32(uint32_t thread, uint8_t idx)
{
    uint32_t ret;
    ret = HW_RD_REG32(CSL_secProxyGetDataAddr(pSciclient_secProxyCfg,thread,0U) +
        ((uintptr_t) (0x4U) * (uintptr_t) idx));
    return ret;
}

uint32_t Sciclient_readThreadCount(uint32_t thread)
{
    return (HW_RD_REG32(Sciclient_threadStatusReg(thread)) &
        CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK);
}

int32_t Sciclient_verifyThread(uint32_t thread)
{
    int32_t status = CSL_PASS;
    /* Verify thread status before reading/writing */
    if ((HW_RD_REG32(Sciclient_threadStatusReg(thread)) &
        CSL_SEC_PROXY_RT_THREAD_STATUS_ERROR_MASK) != 0U)
    {
        status = CSL_EFAIL;
    }
    return status;
}

int32_t Sciclient_waitThread(uint32_t thread, uint32_t timeout)
{
    int32_t  status     = CSL_ETIMEOUT;
    uint32_t timeToWait = timeout;
    /* Checks the thread count is > 0 */
    while (timeToWait > 0U)
    {
        if ((HW_RD_REG32(Sciclient_threadStatusReg(thread)) &
            CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) > 0U)
        {
            status = CSL_PASS;
            break;
        }
        timeToWait--;
    }
    return status;
}

#if defined (BUILD_C7X)
#ifdef __cplusplus
#pragma FUNCTION_OPTIONS("--opt_level=off")
#else
#pragma FUNCTION_OPTIONS(Sciclient_sendMessage, "--opt_level=off")
#endif
#endif
void Sciclient_sendMessage(uint32_t        thread,
                           const uint8_t  *pSecHeader,
                           const uint8_t   secHeaderSizeWords,
                           const uint8_t  *pHeader,
                           const uint8_t  *pPayload,
                           uint32_t        payloadSize,
                           const uint32_t  maxMsgSizeBytes)
{
    uint32_t        i   = 0U;
    const uint8_t *msg = pSecHeader;
    uint32_t numWords   = 0U;
    uint32_t test = 0U;
    uintptr_t threadAddr = CSL_secProxyGetDataAddr(pSciclient_secProxyCfg, thread, 0U);

    if(pSecHeader != NULL)
    {
        /* Write secure header */
        for (i = 0U; i < secHeaderSizeWords; i++)
        {
            /*Change this when unaligned access is supported*/
            (void) memcpy((void *)&test, (const void *)msg, 4);
            CSL_REG32_WR(threadAddr, test);
            msg += 4;
            threadAddr+=sizeof(uint32_t);
        }
    }
    /* Write header */
    msg = pHeader;
    for (i = 0U; i < SCICLIENT_HEADER_SIZE_IN_WORDS; i++)
    {
        /*Change this when unaligned access is supported*/
        (void) memcpy((void *)&test, (const void *)msg, 4);
        CSL_REG32_WR(threadAddr, test);
        msg += 4;
        threadAddr+=sizeof(uint32_t);
    }
    /* Writing payload */
    if (payloadSize > 0U)
    {
        numWords   = (payloadSize+3U)/4U;
        msg = pPayload;
        for (; i < (SCICLIENT_HEADER_SIZE_IN_WORDS + numWords); i++)
        {
            /*Change this when unaligned access is supported*/
            (void) memcpy((void *)&test, (const void *)msg, 4);
            CSL_REG32_WR(threadAddr, test);
            msg += 4;
            threadAddr+=sizeof(uint32_t);
        }
    }
    /* Write to the last register of the TX thread */
    if ((((uint32_t) secHeaderSizeWords*4U)+(SCICLIENT_HEADER_SIZE_IN_WORDS*4U)+payloadSize) <=
        (maxMsgSizeBytes - 4U))
    {
        threadAddr = CSL_secProxyGetDataAddr(pSciclient_secProxyCfg, thread, 0U) +
        ((uintptr_t) maxMsgSizeBytes  - (uintptr_t) 4U) ;
        CSL_REG32_WR(threadAddr,0U);
    }
}

void Sciclient_flush(uint32_t thread, uint32_t maxMsgSizeBytes)
{
    while ((HW_RD_REG32(Sciclient_threadStatusReg(thread)) &
        CSL_SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) > 0U)
    {
        /* Reading from the last register of rxThread*/
        (void) Sciclient_readThread32(thread,
                        (uint8_t)((maxMsgSizeBytes/4U)-1U));
    }

    return ;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
