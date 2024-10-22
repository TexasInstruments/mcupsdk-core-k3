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

#define SHDMEM_MAGIC                    (0xABCDABCD)
#define ShmCirBuf_assert(cond, ...)     assert(cond)

typedef enum ShdMemStatus_t
{
    SHDMEM_STATUS_OK = 0,
    SHDMEM_STATUS_ERR_EMPTY = -1,
    SHDMEM_STATUS_ERR_FULL = -2,
    SHDMEM_STATUS_ERR_HEAD_CURRUPT = -3, /*! Head refers to write Index */
    SHDMEM_STATUS_ERR_TAIL_CURRUPT = -4, /*! Tail refers to Read Index */
    SHDMEM_STATUS_ERR_ELEM_CURRUPT = -5,
    SHDMEM_STATUS_ERR_NO_INIT = -6,
    SHDMEM_STATUS_ERR_HANDLER_CORRUPT = -7,
    SHDMEM_STATUS_ERR_BAD_PKT = -8,
    SHDMEM_STATUS_ERR_READ_NO_DATA = -9,
} ShdMemStatus;

typedef void* shm_handle;

/**
 * \brief  This API creates shared-memory object.
 *
 * \param  pStartAdd      base address of the shared memory
 * \param  bufSize        total buffer size including overhead
 * \return shm_handle     handle of the shared-memory object
 *
 */
shm_handle shm_create(const uint32_t startAdd, const uint32_t bufSize);

/**
 * \brief  This API returns int16_t* data pointer for read AVB buffer.
 *
 * \param  hBuff          handle of shared memory object
 * \param  pData          Pointer to hold the buffer location
 * \param  dataLen        Size of requested buffer
 *
 */
ShdMemStatus shm_read(shm_handle hBuff, uint8_t* pData, uint16_t* pDataLen);

/**
 * \brief  This API returns int16_t* data pointer for read AVB buffer.
 *
 * \param  hBuff          handle of shared memory object
 * \param  pData          Pointer to hold the buffer location
 * \param  dataLen        Size of requested buffer
 *
 */
ShdMemStatus shm_readBufPtr(shm_handle hShmMem, uint8_t** pData, uint16_t* pDataLen);

/**
 * \brief  This API returns overhead of the shared-memory-object.
 *
 * \param  none          
 *
 */
uint32_t shm_metadata_overhead();

/**
 * \brief  This API returns int16_t* data pointer for write AVB buffer.
 *
 * \param  hBuff          handle of shared memory object
 * \param  pData          Pointer to hold the buffer location
 * \param  dataLen        Size of requested buffer
 *
 */
ShdMemStatus shm_writeBufPtr(shm_handle hBuff, int16_t** pData, uint32_t dataLen);

/**
 * \brief  This API writes AVB data to be consumed by remote core.
 *
 * \param  hBuff          handle of shared memory object
 * \param  pData          Pointer buffer to be written
 * \param  dataLen        Size of buffer
 *
 */
ShdMemStatus shm_write(shm_handle hBuff, void* pData, uint32_t dataLen);


#ifdef __cplusplus
}
#endif

#endif // SHM_CIRCULAR_BUFFERP_H
