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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/CacheP.h>
#include "ShdMemCircularBufferP_nortos.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SHDMEM_CIRCULAR_BUFFER_GET_HEAD_ADDR(x) ((uint8_t*)x)
#define SHDMEM_CIRCULAR_BUFFER_GET_ELEM_START_ADDR(x) ((uint8_t*)x + sizeof(ShdMemCircularBufferP_Head))
#define SHDMEM_CIRCULAR_BUFFER_GET_ELEM_END_ADDR(x, count, elemSize) ((uint8_t*)x + sizeof(ShdMemCircularBufferP_Head) + (count-1)*sizeof(ShdMemCircularBufferP_Elem))
#define SHDMEM_CIRCULAR_BUFFER_GET_TAIL_ADDR(x, count, elemSize) ((uint8_t*)x + sizeof(ShdMemCircularBufferP_Head) + count*sizeof(ShdMemCircularBufferP_Elem))

#define ENABLE_CACHE_OPS    (0U) /*! Currently untested. Keeping it disabled */
#define ENABLE_MUTEX_LOCKS  (1U)

typedef struct ShdMemCircularBufferP_Head_t
{
    uint32_t magic;
    uint32_t writeIdx;
} ShdMemCircularBufferP_Head;

typedef struct ShdMemCircularBufferP_Elem_t
{
    uint32_t magic;
    uint32_t elemLen;
    uint8_t elemData[SHDMEM_CIRCULAR_BUFFER_MAX_ELEM_SIZE];
} ShdMemCircularBufferP_Elem;

typedef struct ShdMemCircularBufferP_Tail_t
{
    uint32_t magic;
    uint32_t readIdx;
} ShdMemCircularBufferP_Tail;

typedef struct ShdMemCircularBufferP_Obj_t
{
    volatile ShdMemCircularBufferP_Head* pHead;
    volatile ShdMemCircularBufferP_Tail* pTail;
    void*    pStartAddress;
    void*    pEndAddress; /*! Redundant with maxElements, used to ease of computation */
    uint32_t maxElements;
    uint32_t elementSizeBytes;
    uint32_t init;
    SemaphoreP_Object sem;
} ShdMemCircularBufferP_Obj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*! None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*! None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

ShdMemCircularBufferP_Handle ShdMemCircularBufferP_create(ShdMemCircularBufferP_Rsv* pObjMem,
                                                          const void* pShdMemBuffStartAdd,
                                                          const uint32_t elemCount,
                                                          const uint32_t elemSize)
{
    DebugP_assert(sizeof(ShdMemCircularBufferP_Rsv) >= sizeof(ShdMemCircularBufferP_Obj));

    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)pObjMem;
    uint8_t* pstartAdd     = (uint8_t*) pShdMemBuffStartAdd;
    pObj->pHead            = (ShdMemCircularBufferP_Head*)SHDMEM_CIRCULAR_BUFFER_GET_HEAD_ADDR(pstartAdd);
    pObj->pStartAddress    = (void*) SHDMEM_CIRCULAR_BUFFER_GET_ELEM_START_ADDR(pstartAdd);
    pObj->pEndAddress      = (void*) SHDMEM_CIRCULAR_BUFFER_GET_ELEM_END_ADDR(pstartAdd, elemCount, elemSize);
    pObj->pTail            = (ShdMemCircularBufferP_Tail*) SHDMEM_CIRCULAR_BUFFER_GET_TAIL_ADDR(pstartAdd, elemCount, elemSize);
    pObj->elementSizeBytes = elemSize;
    pObj->maxElements      = elemCount;
    pObj->init             = SHDMEM_CIRCULAR_BUFFER_MAGIC;

    //ToDo:validate Buffer region memory; Add check for element size with max elem size ; Check allignment
#if (ENABLE_MUTEX_LOCKS)
    int32_t status;
    status = SemaphoreP_constructMutex(&pObj->sem);
    DebugP_assert(SystemP_SUCCESS == status);
#endif /*! ENABLE_MUTEX_LOCKS */
    return (ShdMemCircularBufferP_Handle) pObj;
}

ShdMemCircularBufferStatus ShdMemCircularBufferP_initQ(ShdMemCircularBufferP_Handle hBuff, uint32_t queueId, uint32_t maxSize)
{
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
    ShdMemCircularBufferStatus retVal = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;

    ShmCirBuf_assert(pObj != NULL);

    /* initialize the shdMem Buffer metadeta */
    pObj->pHead->magic    = SHDMEM_CIRCULAR_BUFFER_MAGIC;
    pObj->pHead->writeIdx = 0;
    pObj->pTail->magic    = SHDMEM_CIRCULAR_BUFFER_MAGIC;
    pObj->pTail->readIdx  = 0;

    /* Clear all the nodes */
    memset(pObj->pStartAddress, 0x00, maxSize * sizeof(ShdMemCircularBufferP_Elem));

#if (ENABLE_CACHE_OPS)
    /* Cache_Inv head the latest to avoid race conditions */
    CacheP_wbInv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
    CacheP_wbInv((void *)pObj->pHead, sizeof(ShdMemCircularBufferP_Head), CacheP_TYPE_ALLD);
    CacheP_wbInv((void *)pObj->pStartAddress, maxSize * sizeof(ShdMemCircularBufferP_Elem), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */

    return retVal;
}

/*!
 * \brief Returns true if the given queue is initialized
 *
 * @param[in] hBuff      Handle to ShdMemCircularBufferP_Obj object
 *
 * @return True if the given queue is valid.
 */
bool ShdMemCircularBufferP_isInitDone(ShdMemCircularBufferP_Handle hBuff)
{
    bool status = false;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;

    ShmCirBuf_assert(pObj != NULL);

    if (SHDMEM_CIRCULAR_BUFFER_MAGIC == pObj->init)
    {
        status = true;
    }

    return status;
}

/*!
 * \brief Returns true if the given queue is valid for head and tail operations
 *
 * @param[in] hBuff      Handle to ShdMemCircularBufferP_Obj object
 *
 * @return True if the given queue is valid.
 */
bool ShdMemCircularBufferP_isQValid(ShdMemCircularBufferP_Handle hBuff)
{
    bool headValid = false;
    bool tailValid = false;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;

    ShmCirBuf_assert(hBuff != NULL);

#if (ENABLE_CACHE_OPS)
    /* Cache_Inv tail the latest to avoid race conditions */
    CacheP_inv((void *)pObj->pHead, sizeof(ShdMemCircularBufferP_Head), CacheP_TYPE_ALLD);
    CacheP_inv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
    if (SHDMEM_CIRCULAR_BUFFER_MAGIC == pObj->pHead->magic)
    {
        headValid = true;
    }

    if (SHDMEM_CIRCULAR_BUFFER_MAGIC == pObj->pTail->magic)
    {
        tailValid = true;
    }

    return (headValid && tailValid);
}

ShdMemCircularBufferStatus ShdMemCircularBufferP_readElem(ShdMemCircularBufferP_Handle hBuff, uint16_t* pDataLen, void* pData)
{
    ShdMemCircularBufferStatus status = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
    uint32_t readIdx = pObj->pTail->readIdx;

    ShmCirBuf_assert(pObj != NULL);
    ShmCirBuf_assert(pObj->pStartAddress != NULL);

    if (pObj->pHead->writeIdx == readIdx)
    {
        status = SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_EMPTY;
    }
    else
    {
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_pend(&pObj->sem, SystemP_WAIT_FOREVER);
#endif /*! ENABLE_MUTEX_LOCKS */

        ShdMemCircularBufferP_Elem* pElemAdd = (ShdMemCircularBufferP_Elem*)(((uint8_t*) pObj->pStartAddress) +
                                                                             (sizeof(ShdMemCircularBufferP_Elem)*readIdx++));
        if (readIdx == pObj->maxElements)
        {
            readIdx = 0;
        }
#if (ENABLE_CACHE_OPS)
        CacheP_inv((void *)pElemAdd, sizeof(ShdMemCircularBufferP_Elem), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
        *pDataLen = pElemAdd->elemLen;
        memcpy((void*)pData, (uint8_t*)&pElemAdd->elemData[0], *pDataLen);
        pObj->pTail->readIdx = readIdx;
#if (ENABLE_CACHE_OPS)
        /* Write back only after successful read. Else, sender might write into this buffer while we are still reading */
        CacheP_wbInv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_post(&pObj->sem);
#endif /*! ENABLE_MUTEX_LOCKS */
    }
    return status;
}

ShdMemCircularBufferStatus ShdMemCircularBufferP_writeElem(ShdMemCircularBufferP_Handle hBuff, const uint32_t arrLen, void* pDataArr[], uint32_t* dataLenArr)
{
    ShdMemCircularBufferStatus status = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
    uint32_t writeIdx = pObj->pHead->writeIdx;
    uint32_t i, copyLen;

    ShmCirBuf_assert(pObj != NULL);
    ShmCirBuf_assert(pObj->pStartAddress != NULL);

#if (ENABLE_CACHE_OPS)
    /* Cache_Inv tail the latest to avoid race conditions */
    CacheP_inv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
    if (((writeIdx + 1) % pObj->maxElements) == pObj->pTail->readIdx)
    {
        status = SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_FULL;
    }
    else
    {
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_pend(&pObj->sem, SystemP_WAIT_FOREVER);
#endif /*! ENABLE_MUTEX_LOCKS */

        ShdMemCircularBufferP_Elem* pElemAdd = (ShdMemCircularBufferP_Elem*)(((uint8_t*) pObj->pStartAddress) +
                                                                             (sizeof(ShdMemCircularBufferP_Elem)*(writeIdx++)));
#if (ENABLE_CACHE_OPS)
        CacheP_inv((void *)pElemAdd, sizeof(ShdMemCircularBufferP_Elem), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
        if (writeIdx == pObj->maxElements)
        {
            writeIdx = 0;
        }
        copyLen = 0U;
        for(i = 0; i < arrLen; i++)
        {
            if((copyLen + dataLenArr[i]) < SHDMEM_CIRCULAR_BUFFER_MAX_ELEM_SIZE)
            {
                memcpy((void*)&pElemAdd->elemData[copyLen], pDataArr[i], dataLenArr[i]);
                copyLen +=dataLenArr[i];
            }
            else
            {
                status = SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_BAD_PKT;
            }
        }
        if(status == SHDMEM_CIRCULAR_BUFFER_STATUS_OK)
        {
            pElemAdd->elemLen = copyLen;
            pObj->pHead->writeIdx = writeIdx;
#if (ENABLE_CACHE_OPS)
            /* Write back head only after successful write, and its Wb.
             * Else, receiver might read from this invalid buffer while we are still writing
             */
            CacheP_wbInv((void *)pElemAdd, sizeof(ShdMemCircularBufferP_Elem), CacheP_TYPE_ALLD);
            CacheP_wbInv((void *)pObj->pHead, sizeof(ShdMemCircularBufferP_Head), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
        }
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_post(&pObj->sem);
#endif /*! ENABLE_MUTEX_LOCKS */
    }
    return status;
}

bool ShdMemCircularBufferP_isQEmpty(ShdMemCircularBufferP_Handle hBuff)
{
    bool status = false;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
#if (ENABLE_CACHE_OPS)
    /* Cache_Inv head the latest to avoid race conditions */
    CacheP_inv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
    CacheP_inv((void *)pObj->pHead, sizeof(ShdMemCircularBufferP_Head), CacheP_TYPE_ALLD);
#endif /*! ENABLE_CACHE_OPS */
    if (pObj->pHead->writeIdx == pObj->pTail->readIdx)
    {
        status = true;
    }
    return status;
}

bool ShdMemCircularBufferP_isQFull(ShdMemCircularBufferP_Handle hBuff)
{
    bool status = false;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
#if (ENABLE_CACHE_OPS)
    /* Cache_Inv tail the latest to avoid race conditions */
    CacheP_inv((void *)pObj->pHead, sizeof(ShdMemCircularBufferP_Head), CacheP_TYPE_ALLD);
    CacheP_inv((void *)pObj->pTail, sizeof(ShdMemCircularBufferP_Tail), CacheP_TYPE_ALLD);
#endif /* ENABLE_CACHE_OPS */
    if (((pObj->pHead->writeIdx + 1) % pObj->maxElements) == pObj->pTail->readIdx)
    {
        status = true;
    }
    return status;
}

ShdMemCircularBufferStatus ShdMemCircularBufferP_peekReadElem(ShdMemCircularBufferP_Handle hBuff, uint16_t *pDataLen)
{
    ShdMemCircularBufferStatus status = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;

    uint32_t readIdx = pObj->pTail->readIdx;

    if (pObj->pHead->writeIdx == readIdx)
    {
        status = SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_EMPTY;
    }
    else
    {
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_pend(&pObj->sem, SystemP_WAIT_FOREVER);
#endif /* ENABLE_MUTEX_LOCKS */
        ShdMemCircularBufferP_Elem* pElemAdd = (ShdMemCircularBufferP_Elem*)(((uint8_t*) pObj->pStartAddress) + (sizeof(ShdMemCircularBufferP_Elem)*readIdx++));
#if (ENABLE_CACHE_OPS)
        CacheP_inv((void *)pElemAdd, sizeof(ShdMemCircularBufferP_Elem), CacheP_TYPE_ALLD);
#endif /* ENABLE_CACHE_OPS */
        *pDataLen = pElemAdd->elemLen;
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_post(&pObj->sem);
#endif /* ENABLE_MUTEX_LOCKS */
    }
    return status;
}

ShdMemCircularBufferStatus ShdMemCircularBufferP_moveReadIdx(ShdMemCircularBufferP_Handle hBuff)
{
    ShdMemCircularBufferStatus status = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;
    ShdMemCircularBufferP_Obj* pObj = (ShdMemCircularBufferP_Obj*)hBuff;
    uint32_t readIdx = pObj->pTail->readIdx;

    if (pObj->pHead->writeIdx == readIdx)
    {
        status = SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_EMPTY;
    }
    else
    {
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_pend(&pObj->sem, SystemP_WAIT_FOREVER);
#endif /* ENABLE_MUTEX_LOCKS */
        pObj->pTail->readIdx++;
#if (ENABLE_MUTEX_LOCKS)
        SemaphoreP_post(&pObj->sem);
#endif /* ENABLE_MUTEX_LOCKS */
    }
    return status;
}
