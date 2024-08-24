/*
 *  Copyright (C) 2021-2023 Texas Instruments Incorporated
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

#include "utils.h"
/* This is needed for memset/memcpy */
#include <string.h>

#define PTR_COPY_SRC_ALIGNMENT   sizeof(uintptr_t)

void Utils_memcpyWord(uint8_t *source, uint8_t *destination, uint32_t length)
{
    if((((uintptr_t)source % PTR_COPY_SRC_ALIGNMENT) == ((uintptr_t)destination % PTR_COPY_SRC_ALIGNMENT)) ||
       ((length % PTR_COPY_SRC_ALIGNMENT) != 0))
    {
        uint8_t *temp8Src = source;
        uint8_t *temp8Dst = destination;
        uintptr_t *tempSrc = (uintptr_t *)source;
        uintptr_t *tempDst = (uintptr_t *)destination;
        uint32_t remainingBytes = length, i;

        /* Check for Byte alignment of source address */
        if(((uintptr_t)source % PTR_COPY_SRC_ALIGNMENT) != 0)
        {
            uint32_t initResidualBytes = PTR_COPY_SRC_ALIGNMENT - (((uintptr_t)source) % PTR_COPY_SRC_ALIGNMENT);
            i = initResidualBytes;

            /* Do 8-bit pointer copy for initial unaligned bytes*/
            while(i != 0)
            {
                *temp8Dst = *temp8Src;
                temp8Src++;
                temp8Dst++;
                i--;
            }

            tempDst = (uintptr_t *)((uintptr_t)destination + initResidualBytes);
            tempSrc = (uintptr_t *)((uintptr_t)source + initResidualBytes);
            remainingBytes -= initResidualBytes;
        }

        /* Do pointer copy for aligned bytes */
        uint32_t unalignedBytes = remainingBytes % PTR_COPY_SRC_ALIGNMENT;
        i = (remainingBytes - unalignedBytes) / 4 ;

        while(i != 0)
        {
            *tempDst = *tempSrc;
            tempSrc++;
            tempDst++;
            i--;
        }

        /* Do 8-bit pointer copy for unaligned bytes if any */
        if(unalignedBytes > 0)
        {
            temp8Dst = (uint8_t *)tempDst;
            temp8Src = (uint8_t *)tempSrc;
            i = unalignedBytes;
            while(i != 0)
            {
                *temp8Dst = *temp8Src;
                temp8Src++;
                temp8Dst++;
                i--;
            }
        }
    }
    else
    {
        memcpy(destination, source, length);
    }
}

void Utils_dataAndInstructionBarrier(void)
{

    #if defined(__aarch64__) || defined(__arm__)
    __asm__ __volatile__ ( "dsb sy"  "\n\t": : : "memory");
    __asm__ __volatile__ ( "isb sy"  "\n\t": : : "memory");
    #endif
    #if defined(_TMS320C6X)
    _mfence();
    _mfence();
    #endif
}
