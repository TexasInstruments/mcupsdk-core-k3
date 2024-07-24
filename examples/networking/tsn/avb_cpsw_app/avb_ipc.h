/*

 * Copyright (c) 2013-2014, Texas Instruments Incorporated

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



/*

 *  ======== ti_avb_defs.h ========

 *

 */



#ifndef __TI_AVB_DEFS_H__

#define __TI_AVB_DEFS_H__



#if defined (__cplusplus)

extern "C"

{

#endif



#include <kernel/dpl/ClockP.h>

#include <kernel/dpl/SemaphoreP.h>

#include <drivers/ipc_notify.h>



/* AVB Control Command/response */

#define TI_AVB_CMD_BASE                 (0x1000)

#define TI_AVB_OPEN_STREAM_CMD          (TI_AVB_CMD_BASE + 1)

#define TI_AVB_START_STREAM_CMD         (TI_AVB_CMD_BASE + 2)

#define TI_AVB_SUSPEND_STREAM_CMD       (TI_AVB_CMD_BASE + 3)

#define TI_AVB_RESUME_STREAM_CMD        (TI_AVB_CMD_BASE + 4)

#define TI_AVB_CLOSE_STREAM_CMD         (TI_AVB_CMD_BASE + 5)



#define TI_AVB_RESP_BASE                (0x2000)

#define TI_AVB_OPEN_STREAM_RESP         (TI_AVB_RESP_BASE + 1)

#define TI_AVB_START_STREAM_RESP        (TI_AVB_RESP_BASE + 2)

#define TI_AVB_SUSPEND_STREAM_RESP      (TI_AVB_RESP_BASE + 3)

#define TI_AVB_RESUME_STREAM_RESP       (TI_AVB_RESP_BASE + 4)



typedef enum StreamType

{

    CLASS_A,

    CLASS_D,

    StreamType_Cnt

}StreamType;



typedef enum StreamStutus

{

    StreamResp_ACK,

    StreamResp_NACK,

    StreamResp_TIMEOUT

}StreamStatus;



typedef struct

{

    uint32_t        streamId;

    uint32_t        numCounts;

    uint32_t        sampleRate;

    StreamType      stream;

}TI_AVB_StreamOpenCmd;



typedef struct

{

    uint32_t        streamId;

    uint32_t        bufAddress;

    uint32_t        bufCnt;

    uint32_t        bufSize;

    StreamType      stream;

}TI_AVB_StreamStartCmd;



typedef struct

{

    uint32_t        streamId;

    StreamStatus    status;

}TI_AVB_StreamGenResp;



#if defined (__cplusplus)

}

#endif



#endif /* __TI_AVB_DEFS_H__ */
