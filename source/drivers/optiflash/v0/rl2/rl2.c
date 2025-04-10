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

/* *
 *  \file   rl2.c
 *
 *  \brief  File containing  RL2 Driver APIs implementation for V0.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <drivers/hw_include/cslr.h>
#include "rl2.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

RL2_API_STS_t RL2_configure(RL2_Params *config)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        uint32_t requried_cache_size = 0U;
        switch (config->cacheSize)
        {
        case RL2_CACHESIZE_8K:
        case RL2_CACHESIZE_16K:
        case RL2_CACHESIZE_32K:
        case RL2_CACHESIZE_64K:
        case RL2_CACHESIZE_128K:
        case RL2_CACHESIZE_256K:
            requried_cache_size = 1U;
            break;
        default:
            requried_cache_size = 0U;
            break;
        }

        /* check if region size is given something else which is not known */
        if(requried_cache_size == (uint32_t)0U)
        {
            retStatus = (RL2_API_STS_CANNOT_CONFIGURE | RL2_API_STS_UNKNOWN_CACHE_SIZE);
        }
        else
        {
            RL2_disable(config);
            CSL_rl2_of_cba4Regs *regs;
            regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
            /* set the regions */
            regs->REM.ADR = config->l2Sram0Base;
            regs->REM.LEN = config->l2Sram0Len;
            regs->L2_LO_LSW = config->rangeStart;
            regs->L2_HI = config->rangeEnd;
            regs->L2_CTRL |= CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK | \
                            ((((uint32_t)(config->cacheSize)) << CSL_RL2_OF_CBA4_L2_CTRL_SIZE_SHIFT) \
                            & CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MASK);
            while(regs->L2_STS != CSL_RL2_OF_CBA4_L2_STS_OK_TO_GO_MASK)
            {
                /* nothing */
            }
        }
    }
    return retStatus;
}

RL2_API_STS_t RL2_initparams(RL2_Params * config)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        (void)memset(config, 0U, sizeof(RL2_Params));
        config->cacheSize = RL2_CACHESIZE_128K;
    }
    return retStatus;
}

RL2_API_STS_t RL2_setInterrupt(RL2_Params * config, RL2_Interrupt intr)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        switch(intr)
        {
            case RL2_INTERRUPT_WRITE_HIT:
                regs->IRQENABLE_SET |= CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_HIT_MASK;
                break;
            case RL2_INTERRUPT_WRITE_ERROR:
                regs->IRQENABLE_SET |= CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MASK;
                break;
            default:
                retStatus = RL2_API_STS_UNKNOWN_INTERRUPT;
                break;
        }
    }
    return retStatus;
}

RL2_API_STS_t RL2_clearInterrupt(RL2_Params * config, RL2_Interrupt intr)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        switch(intr)
        {
            case RL2_INTERRUPT_WRITE_HIT:
                regs->IRQENABLE_CLR |= CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_HIT_MASK;
                break;
            case RL2_INTERRUPT_WRITE_ERROR:
                regs->IRQENABLE_CLR |= CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MASK;
                break;
            default:
                retStatus = RL2_API_STS_UNKNOWN_INTERRUPT;
                break;
        }
    }
    return retStatus;
}

RL2_API_STS_t RL2_readIRQMask(RL2_Params * config, uint32_t * status)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if((config == NULL) || (status == NULL))
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        *status = regs->IRQSTATUS_MSK;
    }
    return retStatus;
}

RL2_API_STS_t RL2_readIRQStatus(RL2_Params * config, uint32_t * status)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if((config == NULL) || (status == NULL))
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        *status = regs->IRQSTATUS_RAW;
    }
    return retStatus;
}

RL2_API_STS_t RL2_getCacheMiss(RL2_Params * config, uint32_t * miss)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if((NULL == config) || (NULL == miss))
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        *miss = regs->L2MC;
    }
    return retStatus;
}

RL2_API_STS_t RL2_getCacheHits(RL2_Params * config, uint32_t * hits)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    if((NULL == config) || (NULL == hits))
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        *hits = regs->L2HC;
    }
    return retStatus;
}

RL2_API_STS_t RL2_enable(RL2_Params * config)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;
    
    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        regs->L2_CTRL |= CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK | ((((uint32_t)(config->cacheSize)) << CSL_RL2_OF_CBA4_L2_CTRL_SIZE_SHIFT) & CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MASK);
        retStatus = RL2_API_STS_SUCCESS;
    }
    return retStatus;
}

RL2_API_STS_t RL2_disable(RL2_Params * config)
{
    RL2_API_STS_t retStatus = RL2_API_STS_SUCCESS;

    if(config == NULL)
    {
        retStatus = RL2_API_STS_CANNOT_CONFIGURE;
    }
    else
    {
        CSL_rl2_of_cba4Regs *regs;
        regs = (CSL_rl2_of_cba4Regs*)config->baseAddress;
        regs->L2_CTRL &= ~(CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK);
        retStatus = RL2_API_STS_SUCCESS;
    }
    return retStatus;
}
