/*
 *  Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \file   dthe.c
 *
 *  \brief  This file contains the implementation of Dthe driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <security/crypto/dthe/dthe.h>
#include <drivers/hw_include/cslr.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DTHE_init(void)
{
    return ;
}

void DTHE_deinit(void)
{
    return ;
}

DTHE_Handle DTHE_open(uint32_t index)
{
    uint32_t        status  = SystemP_SUCCESS;
    DTHE_Handle     handle  = NULL;
    DTHE_Config     *config = NULL;
    DTHE_Attrs      *attrs  = NULL;
    /* Check instance */
    if(index >= gDtheConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        config = &gDtheConfig[index];
        DebugP_assert(NULL != config->attrs);
        attrs = config->attrs;
        if(TRUE == attrs->isOpen)
        {
            /* Handle is already opened */
            status = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == status)
    {
        attrs->isOpen = TRUE;
        handle = (DTHE_Handle) config;
    }
    else
    {
        status = DTHE_close(handle);
    }
    return (handle);
}

int32_t DTHE_close(DTHE_Handle handle)
{
    int32_t status      = SystemP_FAILURE;
    DTHE_Config         *config;
    DTHE_Attrs          *attrs = NULL;
    config = (DTHE_Config *) handle;

    if((NULL != config) && (config->attrs->isOpen != (uint32_t)FALSE))
    {
        attrs = config->attrs;
        DebugP_assert(NULL != attrs);
        attrs->isOpen = FALSE;
        /* TO module disable */
        handle = NULL;
        status  = SystemP_SUCCESS;
    }
    return (status);
}

int32_t DTHE_enableSecureRequest(DTHE_Handle handle)
{
    int32_t status  = SystemP_FAILURE;
    CSL_DTHECfgRegs *pDtheRegs;
    DTHE_Config     *config;
    DTHE_Attrs      *attrs = NULL;
    if((attrs->isOpen) && (NULL != handle))
    {
        status = SystemP_SUCCESS;
    }

    if (status == SystemP_SUCCESS)
    {
        config      = (DTHE_Config *) handle;
        attrs       = config->attrs;
        pDtheRegs   = (CSL_DTHECfgRegs *)attrs->caBaseAddr;
        pDtheRegs->S_EIP_CONFIG = 0x3U;
    }
    return (status);
}

int32_t DTHE_disableSecureRequest(DTHE_Handle handle)
{
    int32_t status  = SystemP_FAILURE;
    CSL_DTHECfgRegs *pDtheRegs;
    DTHE_Config     *config;
    DTHE_Attrs      *attrs = NULL;
    if((attrs->isOpen) && (NULL != handle))
    {
        status = SystemP_SUCCESS;
    }

    if (status == SystemP_SUCCESS)
    {
        config      = (DTHE_Config *) handle;
        attrs       = config->attrs;
        pDtheRegs   = (CSL_DTHECfgRegs *)attrs->caBaseAddr;
        pDtheRegs->S_EIP_CONFIG = 0x0U;
    }
    return (status);
}

uint8_t DTHE_isSecureRequestEnabled(DTHE_Handle handle)
{
    uint8_t status = SystemP_FAILURE;
    CSL_DTHECfgRegs *pDtheRegs;
    DTHE_Config     *config;
    DTHE_Attrs      *attrs  = NULL;
    if((attrs->isOpen) && (NULL != handle))
    {
        status = SystemP_SUCCESS;
    }

    if (status == SystemP_SUCCESS)
    {
        config      = (DTHE_Config *) handle;
        attrs       = config->attrs;
        pDtheRegs   = (CSL_DTHECfgRegs *)attrs->caBaseAddr;
        if(pDtheRegs->S_EIP_CONFIG == 0x3U)
        {
            status = 1U;
        }
        else
        {
            status = 0U;
        }
    }
    return (status);
}