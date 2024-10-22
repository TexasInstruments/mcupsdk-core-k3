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
#include <kernel/dpl/CacheP.h>
#include "shm_cirbuf.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef struct ShdMemObj_t
{
	uint32_t 	header;
	uint32_t	readAddr;
	uint32_t	writeAddr;
	uint32_t	startAddr;
	uint32_t    endAddr;
	uint32_t    dataAvail;
	uint32_t 	readErrCnt;
	uint32_t 	writeErrCnt;
	uint32_t	readErrorEmpty;
	uint32_t	writeErrorFull;
	uint32_t 	readError;
	uint32_t 	writeError;
	uint32_t    totalBufSize;
	uint32_t	tail;
} ShdMemObj;

#define CACHE_LINE_SIZE		128

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

uint32_t shm_metadata_overhead()
{
	//return sizeof(ShdMemObj);
	return CACHE_LINE_SIZE;
}

shm_handle shm_create(const uint32_t startAdd, const uint32_t bufSize)
{
	ShdMemObj*	obj = (ShdMemObj*)startAdd;
	if(obj->header != SHDMEM_MAGIC)
	{
		uint32_t  dataAddr	= startAdd + CACHE_LINE_SIZE; //sizeof(ShdMemObj);
		uint32_t  dataSize 	= bufSize - CACHE_LINE_SIZE; //sizeof(ShdMemObj);
		obj->header 		= SHDMEM_MAGIC;
		obj->readAddr 		= dataAddr;
		obj->writeAddr 		= dataAddr;
		obj->startAddr		= dataAddr;
		obj->endAddr 		= dataAddr + dataSize;
		obj->readErrCnt 	= 0;
		obj->writeErrCnt	= 0;
		obj->readErrorEmpty	= 0;
		obj->writeErrorFull	= 0;
		obj->tail 			= SHDMEM_MAGIC;
		obj->totalBufSize 	= dataSize;
		obj->dataAvail  	= 0;
	}

	return (shm_handle)obj;
}

ShdMemStatus shm_read(shm_handle hShmMem, uint8_t* pData, uint16_t* pDataLen)
{
	ShdMemStatus	status 		= SHDMEM_STATUS_OK;
	ShdMemObj*		obj    		= (ShdMemObj*)hShmMem;
	uint32_t 		rqtSize 	= *pDataLen;
	uint32_t		readAddr 	= obj->readAddr;
	uint32_t		wrtAddr 	= obj->writeAddr;
	uint32_t		endAddr 	= obj->endAddr;
	uint32_t		dataSize 	= obj->totalBufSize;
	uint32_t 		dataAvail	= 0;

	if(wrtAddr >= readAddr)
	{
		dataAvail = wrtAddr - readAddr;
	}
	else
	{
		dataAvail = dataSize - readAddr - wrtAddr;
	}

	if((obj->header == SHDMEM_MAGIC) &&
	   (dataAvail >= rqtSize))
	{
		if((readAddr + rqtSize) <= endAddr)
		{
			memcpy((void*)pData, (void*)readAddr, rqtSize);
			readAddr += rqtSize;
			*pDataLen = rqtSize;

			if(readAddr == endAddr)
			{
				readAddr = obj->startAddr;
			}

			obj->readAddr = readAddr;
			CacheP_wb((void *)&(obj->readAddr), sizeof(readAddr), CacheP_TYPE_ALL);
		}
		else
		{
			obj->readErrorEmpty++;
		}
	}
	else
	{
		*pDataLen = 0;
		obj->readErrCnt++;
	}

	return status;
}

ShdMemStatus shm_readBufPtr(shm_handle hShmMem, uint8_t** pData, uint16_t* pDataLen)
{
	ShdMemStatus	status 		= SHDMEM_STATUS_OK;
	ShdMemObj*		obj    		= (ShdMemObj*)hShmMem;
	uint32_t 		rqtSize 	= *pDataLen;
	uint32_t		readAddr 	= obj->readAddr;
	uint32_t		wrtAddr 	= obj->writeAddr;
	uint32_t		endAddr 	= obj->endAddr;
	uint32_t		dataSize 	= obj->totalBufSize;
	uint32_t 		dataAvail	= 0;

	if(wrtAddr >= readAddr)
	{
		dataAvail = wrtAddr - readAddr;
	}
	else
	{
		dataAvail = dataSize - readAddr - wrtAddr;
	}

	if((obj->header == SHDMEM_MAGIC) &&
	   (dataAvail >= rqtSize))
	{
		if((readAddr + rqtSize) <= endAddr)
		{
			*pData = (uint8_t*)readAddr;
			readAddr += rqtSize;
			*pDataLen = rqtSize;

			if(readAddr == endAddr)
			{
				readAddr = obj->startAddr;
			}

			obj->readAddr = readAddr;
			CacheP_wb((void *)&(obj->readAddr), sizeof(readAddr), CacheP_TYPE_ALL);
		}
		else
		{
			obj->readErrorEmpty++;
		}
	}
	else
	{
		*pDataLen = 0;
		obj->readErrCnt++;
	}

	return status;
}

ShdMemStatus shm_write(shm_handle hShmMem, void* pData, uint32_t dataLen)
{
	ShdMemStatus	status 	= SHDMEM_STATUS_OK;
	ShdMemObj*		obj    	= (ShdMemObj*)hShmMem;
	uint32_t		wrtAddr = obj->writeAddr;
	uint32_t		endAddr = obj->endAddr;

	if(obj->header == SHDMEM_MAGIC)
	{
		if(wrtAddr+dataLen <= endAddr)
		{
			memcpy((void*)wrtAddr, pData, dataLen);
			CacheP_wb((void *)wrtAddr, dataLen, CacheP_TYPE_ALL);
			wrtAddr += dataLen;

			if(wrtAddr == endAddr)
			{
				wrtAddr = obj->startAddr;
			}

			obj->writeAddr = wrtAddr;
			CacheP_wb((void *)&(obj->writeAddr), sizeof(wrtAddr), CacheP_TYPE_ALL);

		} else {
			obj->writeErrorFull++;
		}
	}

	return status;
}

ShdMemStatus shm_writeBufPtr(shm_handle hShmMem, int16_t** pData, uint32_t dataLen)
{
	ShdMemStatus	status 	= SHDMEM_STATUS_OK;
	ShdMemObj*		obj    	= (ShdMemObj*)hShmMem;
	uint32_t		wrtAddr = obj->writeAddr;
	uint32_t		endAddr = obj->endAddr;

	if(obj->header == SHDMEM_MAGIC)
	{
		if(wrtAddr+dataLen <= endAddr)
		{
			*pData = (int16_t*)wrtAddr;
			wrtAddr += dataLen;

			if(wrtAddr == endAddr)
			{
				wrtAddr = obj->startAddr;
			}

			obj->writeAddr = wrtAddr;
			CacheP_wb((void *)&(obj->writeAddr), sizeof(wrtAddr), CacheP_TYPE_ALL);

		} else {
			obj->writeErrorFull++;
		}
	}

	return status;
}

