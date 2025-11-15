/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
/* \file circular_buffer.h
 * \brief Test file: Circular (ring) buffer API for byte streams.
 */

/*===================================================================*/
/* 				Include Files 				      */
/*===================================================================*/
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*===================================================================*/
/* 				Macro Defines 				      */
/*===================================================================*/
/* None */

/*===================================================================*/
/* 				Typedefs 				      */
/*===================================================================*/
typedef struct
{
    uint8_t *data;
    size_t   capacity;
    size_t   head;
    size_t   tail;
    size_t   count;
} CircularBuffer;

/*===================================================================*/
/* 				Global Variables 			      */
/*===================================================================*/
/* None */

/*===================================================================*/
/* 				Function Declarations 		      */
/*===================================================================*/
static inline int CircBuf_Init(CircularBuffer *cb, uint8_t *storage, size_t capacity);
static inline void CircBuf_Reset(CircularBuffer *cb);
static inline size_t CircBuf_Available(const CircularBuffer *cb);
static inline size_t CircBuf_Space(const CircularBuffer *cb);
static inline int CircBuf_IsEmpty(const CircularBuffer *cb);
static inline int CircBuf_IsFull(const CircularBuffer *cb);
static inline size_t CircBuf_Write(CircularBuffer *cb, const uint8_t *src, size_t len);
static inline size_t CircBuf_Read(CircularBuffer *cb, uint8_t *dst, size_t len);

/*===================================================================*/
/* 				Function Definitions 		      */
/*===================================================================*/
/**
 * \brief  Initialize a circular buffer with user storage.
 *
 * Test Category: Functionality
 *
 * Sets indices and count to zero and assigns user buffer.
 * Returns -1 on invalid arguments or zero capacity.
 *
 * \param cb       Pointer to CircularBuffer structure
 * \param storage  Backing storage pointer
 * \param capacity Capacity in bytes
 * \return 0 on success, -1 on error
 */
static inline int CircBuf_Init(CircularBuffer *cb, uint8_t *storage, size_t capacity)
{
    if ((cb == NULL) || (storage == NULL) || (capacity == 0U))
    {
        return -1;
    }
    cb->data = storage;
    cb->capacity = capacity;
    cb->head = 0U;
    cb->tail = 0U;
    cb->count = 0U;
    return 0;
}
/**
 * \brief  Reset circular buffer to empty state.
 *
 * Test Category: Functionality
 *
 * Sets head, tail, count to zero.
 *
 * \param cb Pointer to CircularBuffer
 * \return None.
 */
static inline void CircBuf_Reset(CircularBuffer *cb)
{
    if (cb != NULL)
    {
        cb->head = 0U;
        cb->tail = 0U;
        cb->count = 0U;
    }
}
/**
 * \brief  Get readable byte count.
 *
 * Test Category: Functionality
 *
 * Returns current stored byte count.
 *
 * \param cb Pointer to CircularBuffer
 * \return Readable bytes
 */
static inline size_t CircBuf_Available(const CircularBuffer *cb)
{
    if (cb == NULL)
    {
        return 0U;
    }
    return cb->count;
}
/**
 * \brief  Get writable byte space.
 *
 * Test Category: Functionality
 *
 * Computes remaining capacity.
 *
 * \param cb Pointer to CircularBuffer
 * \return Writable bytes
 */
static inline size_t CircBuf_Space(const CircularBuffer *cb)
{
    if (cb == NULL)
    {
        return 0U;
    }
    return cb->capacity - cb->count;
}
/**
 * \brief  Check if buffer is empty.
 *
 * Test Category: Functionality
 *
 * Returns 1 if no stored bytes.
 *
 * \param cb Pointer to CircularBuffer
 * \return 1 if empty, 0 otherwise
 */
static inline int CircBuf_IsEmpty(const CircularBuffer *cb)
{
    if (cb == NULL)
    {
        return 1;
    }
    return (cb->count == 0U) ? 1 : 0;
}
/**
 * \brief  Check if buffer is full.
 *
 * Test Category: Functionality
 *
 * Returns 1 when count equals capacity.
 *
 * \param cb Pointer to CircularBuffer
 * \return 1 if full, 0 otherwise
 */
static inline int CircBuf_IsFull(const CircularBuffer *cb)
{
    if (cb == NULL)
    {
        return 0;
    }
    return (cb->count == cb->capacity) ? 1 : 0;
}
/**
 * \brief  Write bytes to circular buffer.
 *
 * Test Category: Functionality
 *
 * Writes up to len bytes (truncated to available space). Handles wrap.
 *
 * \param cb  Pointer to CircularBuffer
 * \param src Source data pointer
 * \param len Requested byte count
 * \return Number of bytes written
 */
static inline size_t CircBuf_Write(CircularBuffer *cb, const uint8_t *src, size_t len)
{
    if ((cb == NULL) || (src == NULL) || (len == 0U))
    {
        return 0U;
    }
    size_t space = CircBuf_Space(cb);
    if (len > space)
    {
        len = space;
    }
    size_t written = len;
    size_t first = cb->capacity - cb->head;
    if (first > len)
    {
        first = len;
    }
    memcpy(&cb->data[cb->head], src, first);
    cb->head = (cb->head + first) % cb->capacity;
    size_t remaining = len - first;
    if (remaining != 0U)
    {
        memcpy(&cb->data[cb->head], src + first, remaining);
        cb->head = (cb->head + remaining) % cb->capacity;
    }
    cb->count += written;
    return written;
}
/**
 * \brief  Read bytes from circular buffer.
 *
 * Test Category: Functionality
 *
 * Reads up to len bytes (truncated to available count). Handles wrap.
 *
 * \param cb  Pointer to CircularBuffer
 * \param dst Destination buffer pointer
 * \param len Requested byte count
 * \return Number of bytes read
 */
static inline size_t CircBuf_Read(CircularBuffer *cb, uint8_t *dst, size_t len)
{
    if ((cb == NULL) || (dst == NULL) || (len == 0U))
    {
        return 0U;
    }
    if (len > cb->count)
    {
        len = cb->count;
    }
    size_t read = len;
    size_t first = cb->capacity - cb->tail;
    if (first > len)
    {
        first = len;
    }
    memcpy(dst, &cb->data[cb->tail], first);
    cb->tail = (cb->tail + first) % cb->capacity;
    size_t remaining = len - first;
    if (remaining != 0U)
    {
        memcpy(dst + first, &cb->data[cb->tail], remaining);
        cb->tail = (cb->tail + remaining) % cb->capacity;
    }
    cb->count -= read;
    return read;
}

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_H */
