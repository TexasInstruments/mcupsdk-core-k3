/*
 *  Copyright (C) 2018-2024 Texas Instruments Incorporated
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

#ifndef SHM_CIRCULAR_BUFFERP_H
#define SHM_CIRCULAR_BUFFERP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <kernel/dpl/SystemP.h>

#define SHDMEM_CIRCULAR_BUFFER_MAGIC             (0xABCDABCD)
#define SHDMEM_CIRCULAR_BUFFER_MAX_ELEM_SIZE     (1540U)
#define SHDMEM_CIRCULAR_BUFFER_MAX_QUEUE_SIZE    (2048U)
#define SHDMEM_CIRCULAR_BUFFER_MAX_QUEUES        (4U)

/*! \brief Assert wrapper */
#if defined(__KLOCWORK__) || defined(__cplusplus)
#define ShmCirBuf_assert(cond, ...)        do { if (!(cond)) abort(); } while (0)
#else
#define ShmCirBuf_assert(cond, ...)        assert(cond)
#endif


typedef enum ShdMemCircularBufferStatus_t
{
    SHDMEM_CIRCULAR_BUFFER_STATUS_OK = 0,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_EMPTY = -1,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_FULL = -2,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_HEAD_CURRUPT = -3, /*! Head refers to write Index */
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_TAIL_CURRUPT = -4, /*! Tail refers to Read Index */
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_ELEM_CURRUPT = -5,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_NO_INIT = -6,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_HANDLER_CORRUPT = -7,
    SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_BAD_PKT = -8,
} ShdMemCircularBufferStatus;

typedef struct ShdMemCircularBufferP_Rsv_t
{
    uint8_t rsv[1024U];
} ShdMemCircularBufferP_Rsv;

typedef void* ShdMemCircularBufferP_Handle;

ShdMemCircularBufferP_Handle ShdMemCircularBufferP_create(ShdMemCircularBufferP_Rsv* pObjMem, const void* pShdMemBuffStartAdd, const uint32_t elemCount, const uint32_t elemSize);

ShdMemCircularBufferStatus ShdMemCircularBufferP_readElem(ShdMemCircularBufferP_Handle hBuff, uint16_t* pDataLen, void* pData);

ShdMemCircularBufferStatus ShdMemCircularBufferP_writeElem(ShdMemCircularBufferP_Handle hBuff, const uint32_t arrLen, void* pDataArr[], uint32_t* dataLenArr);

ShdMemCircularBufferStatus ShdMemCircularBufferP_initQ(ShdMemCircularBufferP_Handle hShmBufQ, uint32_t queueId, uint32_t maxSize);

ShdMemCircularBufferStatus ShdMemCircularBufferP_peekReadElem(ShdMemCircularBufferP_Handle hBuff, uint16_t *pDataLen);

ShdMemCircularBufferStatus ShdMemCircularBufferP_moveReadIdx(ShdMemCircularBufferP_Handle hBuff);

bool ShdMemCircularBufferP_isQEmpty(ShdMemCircularBufferP_Handle hBuff);

bool ShdMemCircularBufferP_isQFull(ShdMemCircularBufferP_Handle hBuff);

bool ShdMemCircularBufferP_isInitDone(ShdMemCircularBufferP_Handle hBuff);

bool ShdMemCircularBufferP_isQValid(ShdMemCircularBufferP_Handle hBuff);

#ifdef __cplusplus
}
#endif

#endif // SHM_CIRCULAR_BUFFERP_H
