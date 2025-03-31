/*
 *   Copyright (C) Texas Instruments Incorporated 2024-25
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
 *
 */

/*
 *  ======== sdl_cache.c ========
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sdl_arm_r5.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SDL_armR5CacheWb(const void * addr, int32_t size)
{
   uintptr_t i, firstAddr, lastAddr;
   uint32_t cacheLineSize = SDL_armR5CacheGetDcacheLineSize();

   /* Calculate the last address */
   lastAddr = (uintptr_t) addr + size;

   /* find the first address for cache Wb */
   firstAddr = (uintptr_t ) addr & ~(cacheLineSize -1U);

   for (i = firstAddr; i < lastAddr; i+=cacheLineSize)
   {
      /* clean single entry in DCache to PoC */
       SDL_armR5CacheCleanDcacheMva(i);
   }

   return;
}

void SDL_armR5CacheWbInv(const void * addr, int32_t size)
{
    uintptr_t i, firstAddr, lastAddr;
    uint32_t cacheLineSize = SDL_armR5CacheGetDcacheLineSize();

    /* Calculate the last address */
    lastAddr = (uintptr_t) addr + size;

    /* find the first address for cache Wb */
    firstAddr = (uintptr_t ) addr & ~(cacheLineSize -1U);

    for (i = firstAddr; i < lastAddr; i+=cacheLineSize)
    {
        /* clean and invalidate single entry in DCache to PoC */
        SDL_armR5CacheCleanInvalidateDcacheMva(i);
    }

    return;

}

void SDL_armR5CacheInv(const void * addr, int32_t size)
{
    uintptr_t i, firstAddr, lastAddr;
    uint32_t cacheLineSize = SDL_armR5CacheGetDcacheLineSize();

    /* Calculate the last address */
    lastAddr = (uintptr_t) addr + size;

    /* find the first address for cache Wb */
    firstAddr = (uintptr_t ) addr & ~(cacheLineSize -1U);

    for (i = firstAddr; i < lastAddr; i+=cacheLineSize)
    {
        /* invalidate single entry in DCache */
        SDL_armR5CacheInvalidateDcacheMva(i);
    }
    return;

}

/* Nothing past this point */
