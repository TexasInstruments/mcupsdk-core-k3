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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef __SIGCHAIN_CMD_PROC_H__
#define __SIGCHAIN_CMD_PROC_H__

#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(__cplusplus)
extern "C"
{
#endif

#define SIGCHAIN_CMD_BASE (0x1000U)
#define SIGCHAIN_CMD_INFO (SIGCHAIN_CMD_BASE + (0x1U))
#define SIGCHAIN_CMD_MUTE (SIGCHAIN_CMD_BASE + (0x2U))
#define SIGCHAIN_CMD_RT_INFO (SIGCHAIN_CMD_BASE + (0x3U))
#define SIGCHAIN_CMD_NODE_INFO (SIGCHAIN_CMD_BASE + (0x4U))
#define SIGCHAIN_CMD_CHNL_MAP (SIGCHAIN_CMD_BASE + (0x5U))
#define SIGCHAIN_CMD_CHNL_DATA (SIGCHAIN_CMD_BASE + (0x6U))
#define SIGCHAIN_CMD_PLOT_CAPTURE (SIGCHAIN_CMD_BASE + (0x7U))

#define SIGCHAIN_CMD_EXIT_APP (0x1900U)

#define SIGCHAIN_CMD_MAX_CHAR_NAME (16U)
#define SIGCHAIN_CMD_MAX_SIG_COUNT (16U)
#define SIGCHAIN_CMD_NODE_NAME_COUNT (32U)
#define SIGCHAIN_CMD_NODE_PARAM_COUNT (128U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct __attribute__((__packed__))
{
    char socName[SIGCHAIN_CMD_MAX_CHAR_NAME];
    char coreName[SIGCHAIN_CMD_MAX_CHAR_NAME];
    uint32_t samplingRate;
    uint32_t nodeCount;
} SignalChainCmd_SysInfo;

typedef struct __attribute__((__packed__))
{
    uint32_t nodeId;
    char name[SIGCHAIN_CMD_NODE_NAME_COUNT];
    char param[SIGCHAIN_CMD_NODE_PARAM_COUNT];
} NodeInfo;

#if defined(__cplusplus)
}
#endif

#endif /* __SIGCHAIN_CMD_PROC_H__ */
