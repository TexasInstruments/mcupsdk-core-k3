/*
 *  Copyright (C) 2013-2025 Texas Instruments Incorporated
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

#ifndef __SIGCHAIN_IPC_H__
#define __SIGCHAIN_IPC_H__

#if defined(__cplusplus)
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SOC_AM275X) /* Core IDs for AM275x */
#define MAIN_CORE_ID CSL_CORE_ID_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

#if defined(SOC_AM62DX) /* Core IDs for AM62dx */
#define MAIN_CORE_ID CSL_CORE_ID_MCU_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

#define SIGCHAIN_RPMESSAGE_SERVICE "rpmsg_chrdev"
#define SIGCHAIN_ENDPT_APP (14U)

/* RPMessage endpoints */
#define MAIN_CORE_ACK_REPLY_END_PT (12U)
#define REMOTE_SERVICE_END_PT (13U)

#define MAX_ALPHA_CMD_BUFFER (2048U)
#define IPC_RPMESSAGE_MAX_MSG_SIZE (496U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*---- Define EQ control params structure ----*/
typedef struct __attribute__((__packed__))
{
    int32_t dspLoad;
    int32_t cycleCount;
    float throughput;
} params_t;

/*------- Define C7 IPC message structure --------*/
typedef struct __attribute__((__packed__))
{
    uint32_t dataBuffer;
    uint32_t paramsBuffer;
    int32_t dataSize;
    int32_t paramsSize;
} ipcMsgBuf_t;

#if defined(__cplusplus)
}
#endif

#endif /* __SIGCHAIN_IPC_H__ */
