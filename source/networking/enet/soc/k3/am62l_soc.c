/*
 *  Copyright (C) Texas Instruments Incorporated 2025
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

/*!
 * \file  k3_soc.c
 *
 * \brief This file contains the implementation of the common operations
 *        (such as interrupt configuration) found in Keystone 3 devices.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <include/core/enet_soc.h>
#include <include/core/enet_types.h>
#include <include/core/enet_utils.h>
#include "k3_soc.h"

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

static int32_t EnetSocJ7x_rmIrqSet(uint16_t coreDevId,
                                   uint16_t perDevId,
                                   uint32_t srcIdx,
                                   uint32_t coreIntNum);

static int32_t EnetSocJ7x_rmIrqRelease(uint16_t coreDevId,
                                       uint16_t perDevId,
                                       uint32_t srcIdx,
                                       uint32_t coreIntNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t EnetSocJ7x_setupIntrCfg(uint32_t intrId,
                                uint16_t coreDevId,
                                uint16_t perDevId,
                                const EnetSoc_IntrConnCfg *socIntrs,
                                uint32_t numSocIntrs)
{
    
    int32_t status = ENET_SOK;
    return status;
}

int32_t EnetSocJ7x_releaseIntrCfg(uint32_t intrId,
                                  uint16_t coreDevId,
                                  uint16_t perDevId,
                                  const EnetSoc_IntrConnCfg *socIntrs,
                                  uint32_t numSocIntrs)
{
    int32_t status = ENET_SOK;
    return status;
}

uint32_t EnetSocJ7x_getIntrNum(uint32_t intrId,
                               const EnetSoc_IntrConnCfg *socIntrs,
                               uint32_t numSocIntrs)
{
    const EnetSoc_IntrConnCfg *intrCfg = NULL;
    uint32_t intrNum = 0U;
    uint32_t i;

    /* Get interrupt connection info */
    for (i = 0U; i < numSocIntrs; i++)
    {
        if (socIntrs[i].intrId == intrId)
        {
            intrCfg = &socIntrs[i];
            break;
        }
    }

    EnetSoc_assert((intrCfg != NULL), "No config found for intr %u\n", intrId);

    intrNum = intrCfg->coreIntNum;

    return intrNum;
}

static int32_t EnetSocJ7x_rmIrqSet(uint16_t coreDevId,
                                   uint16_t perDevId,
                                   uint32_t srcIdx,
                                   uint32_t coreIntNum)
{
    int32_t status = ENET_SOK;
    return status;
}

static int32_t EnetSocJ7x_rmIrqRelease(uint16_t coreDevId,
                                       uint16_t perDevId,
                                       uint32_t srcIdx,
                                       uint32_t coreIntNum)
{
    int32_t status = ENET_SOK;
    return status;
}
