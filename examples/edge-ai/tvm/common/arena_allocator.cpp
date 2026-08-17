/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/*
 * Generic Bump Arena Allocator - Implementation
 */

#include "arena_allocator.hpp"
#include <kernel/dpl/DebugP.h>

static uint32_t arena_align_up(uint32_t value, uint32_t alignment)
{
    return (value + (alignment - 1)) & ~(alignment - 1);
}

void arena_init(Arena *a, uint8_t *base, uint32_t capacity, uint32_t base_alignment)
{
    uint32_t addr    = (uint32_t)(uintptr_t)base;
    uint32_t aligned = arena_align_up(addr, base_alignment);
    uint32_t pad     = aligned - addr;

    a->base        = (uint8_t *)(uintptr_t)aligned;
    a->capacity    = (capacity > pad) ? (capacity - pad) : 0;
    a->offset      = 0;
    a->remaining   = a->capacity;
    a->initialized = true;

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("  Base: 0x%08x  Capacity: %u bytes\r\n", aligned, a->capacity);
#endif
}

bool arena_alloc(Arena *a, const char *name, uint32_t size, uint32_t alignment, ArenaBuffer *out)
{
    uint32_t aligned_offset = arena_align_up(a->offset, alignment);

    if (aligned_offset > a->capacity || size > (a->capacity - aligned_offset)) {
        DebugP_log("  [ALLOC FAIL] %s  Requested: %u  Offset: %u  Remaining: %u  Capacity: %u\r\n",
                   name, size, a->offset, a->remaining, a->capacity);
        return false;
    }

    out->name      = name;
    out->addr      = (void *)(a->base + aligned_offset);
    out->size      = size;
    out->offset    = aligned_offset;
    out->alignment = alignment;

    a->offset    = aligned_offset + size;
    a->remaining = a->capacity - a->offset;

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("  %s  Offset: %u  Size: %u  Address: 0x%08x\r\n",
               name, aligned_offset, size, (uint32_t)(uintptr_t)out->addr);
#endif
    return true;
}

void arena_reset(Arena *a)
{
    a->offset      = 0;
    a->remaining   = a->capacity;
    a->initialized = false;
}
