/*
 * Copyright (c) 2015-2024, Texas Instruments Incorporated
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

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>



#include "CacheP_c75.h"

/*
 *  ======== CacheP_Module_startup ========
 */
void CacheP_Module_startup(void)
{
    CacheP_enable(CacheP_TYPE_L1D);
    CacheP_enableWT(CacheP_TYPE_L1D);
}

/*
 *  ======== CacheP_enable ========
*  Enables the L1D Cache
 */
void CacheP_enable(uint32_t type)
{
    /* Enable L1D cache */
    if (type & CacheP_TYPE_L1D)
    {
        uint64_t L1D_cfg = CacheP_getL1DCFG();
        L1D_cfg |= 1U;
        CacheP_setL1DCFG(L1D_cfg);
        CacheP_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== CacheP_disable ========
 *  Disables the L1D Cache
 */
void CacheP_disable(uint32_t type)
{
    /* Disable L1D cache */
    if (type & CacheP_TYPE_L1D)
    {
        uint64_t L1D_cfg = CacheP_getL1DCFG();
        L1D_cfg &= ~((uint64_t) 1);
        CacheP_setL1DCFG(L1D_cfg);
        CacheP_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== Cache_enableWB ========
 *  Enables the Cache writeback
 */
void CacheP_enableWB(uint32_t type)
{
     /* Enable writeback */
    if (type & CacheP_TYPE_L1D)
    {
        uint64_t L1D_cfg = CacheP_getL1DCFG();
        L1D_cfg |= 0x10U;
        CacheP_setL1DCFG(L1D_cfg);
        CacheP_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== Cache_enableWT ========
 *  Enables the Cache writeback
 */
void CacheP_enableWT(uint32_t type)
{
    /* Disabling the Writeback enable write through */
    if (type & CacheP_TYPE_L1D)
    {
        uint64_t L1D_cfg = CacheP_getL1DCFG();
        L1D_cfg &= ~((uint64_t) 0x10U);
        CacheP_setL1DCFG(L1D_cfg);
        CacheP_Module_state.L1DCFG = L1D_cfg;
    }

}

/*
 *  ======== Cache_getSize ========
 *  Returns the L1D size.
 */
void CacheP_getSize(CacheP_Size *size)
{
    /*
    * L1D is a non-configurable 64KB cache.
    */
    size->l1dSize = (CacheP_L1Size)CacheP_L1Size_64K;
}

/*
 *  ======== CacheP_wbAll ========
 *  Perform a global write back.  All cache lines are left valid in L1D
 *  cache and the data in L1D cache is written back external.
*/
void CacheP_wbAll(uint32_t type)
{
    if (type & CacheP_TYPE_L1D)
    {
        // Performs a global write back of L1D cache
        CacheP_setL1DWB(1);
    }

}

void Cache_wbInvL1dAll()
{
    CacheP_setL1DWBINV(1);
}

/*
 *  ======== CacheP_wbInvAll ========
 *  Performs a global write back and invalidate. All cache lines are written back
 *  to external then invalidated in L1D cache.
 */
void CacheP_wbInvAll(uint32_t type)
{
    if (type & CacheP_TYPE_L1D)
    {
        CacheP_setL1DWBINV(1);
    }
}

/*
 *  ======== Cache_invAll ========
 *  Performs a global invalidate of L1D cache. This does not trigger writeback.
 */
void CacheP_invL1dAll()
{
    CacheP_setL1DINV(1);
}

/*
 *  ======== CacheP_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1D
 *  cache.
 */
void CacheP_inv(void * blockPtr, uint32_t byteCnt, uint32_t type)
{
    bool wait = true;
    if (byteCnt < 1280)
    {
        __se_cache_op((void *)blockPtr, __DCCIC, 1280);
    }
    else
    {
        __se_cache_op((void *)blockPtr, __DCCMIC, byteCnt);
    }

    if (wait)
    {
        CacheP_wait();
    }
}

/*
 *  ======== CacheP_wb ========
 *  Writes back the range of memory within the specified starting address
 *  and byte count.  The range of addresses operated on gets quantized to
 *  whole cache lines in each cache.  All cache lines within the range
 *  are left valid in L1D cache and the data within the range in L1D cache
 *  will be written back to external.
 */
void CacheP_wb(void * blockPtr, uint32_t byteCnt, uint32_t type)
{
    bool wait= true;
    /*
     * There is no SE operation for just WB, so do the next closest thing
     * which is WBINV.
     */
    if (byteCnt < 1280)
    {
        __se_cache_op((void *)blockPtr, __DCCIC, 1280);
    }
    else
    {
        __se_cache_op((void *)blockPtr, __DCCIC, byteCnt);
    }

    if (wait)
    {
        CacheP_wait();
    }
}

/*
 *  ======== CacheP_wbInv ========
 *  Writes back and invalidates the range of memory within the specified
 *  starting address and byte count.  The range of addresses operated on gets
 *  quantized to whole cache lines in each cache.  All cache lines within
 *  the range are written back to external and then invalidated in L1D cache.
 */
void CacheP_wbInv(void * blockPtr, uint32_t byteCnt, uint32_t type)
{
    bool wait = true;
    if (byteCnt < 1280)
    {
        __se_cache_op((void *)blockPtr, __DCCIC, 1280);
    }
    else
    {
        __se_cache_op((void *)blockPtr, __DCCIC, byteCnt);
    }

    if (wait)
    {
        CacheP_wait();
    }
}

/*
 *  ======== CacheP_wait ========
 *  Wait for the cache operation to complete.
 */
void CacheP_wait()
{
    __SE0ADV(char);
    /*
     *  Stall CPU while memory system is busy.
     */
    _mfence();

}


/* Module_state */
#ifdef __ti__
CacheP_Module_State CacheP_Module_state __attribute__ ((section(".data:CacheP_Module_state")));
#elif !(defined(__MACH__) && defined(__APPLE__))
CacheP_Module_State CacheP_Module_state __attribute__ ((section(".data:CacheP_Module_state")));
#endif
CacheP_Module_State CacheP_Module_state = {
    (uint64_t)0x11U,  /* L1DCFG */ /* L1DWBEN and L1DON */
};


/* atomicBlockSize */
#pragma DATA_SECTION(CacheP_atomicBlockSize, ".const:CacheP_atomicBlockSize");
const uint32_t CacheP_atomicBlockSize = (uint32_t)0x400U;
