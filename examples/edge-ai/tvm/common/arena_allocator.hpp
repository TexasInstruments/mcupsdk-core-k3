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
 * Generic Bump Arena Allocator
 *
 * A linear/bump allocator over a caller-supplied memory region. Never calls
 * malloc/free -- the region itself is always owned and provided by the
 * caller (see signal_chain_arena.hpp for how the signal chains use this over
 * host-provided IPC memory). This file has no knowledge of IPC messages or
 * signal chains; it only manages offsets within a fixed base+capacity.
 */

#ifndef ARENA_ALLOCATOR_HPP
#define ARENA_ALLOCATOR_HPP

#include <stdint.h>

typedef struct {
    uint8_t *base;         /* aligned up from whatever pointer arena_init() was given */
    uint32_t capacity;     /* usable bytes after base, i.e. after alignment padding is removed */
    uint32_t offset;       /* next free byte, relative to base */
    uint32_t remaining;    /* capacity - offset */
    bool     initialized;
} Arena;

typedef struct {
    const char *name;
    void       *addr;
    uint32_t    size;
    uint32_t    offset;
    uint32_t    alignment;
} ArenaBuffer;

/**
 * Initialize an arena over [base, base+capacity). base is aligned UP to
 * base_alignment first (a caller-supplied base, e.g. from an IPC message,
 * has no compiler-guaranteed alignment) -- any padding consumed this way is
 * subtracted from the usable capacity.
 */
void arena_init(Arena *a, uint8_t *base, uint32_t capacity, uint32_t base_alignment);

/**
 * Bump-allocate `size` bytes aligned to `alignment` from the arena.
 * On success fills *out and returns true. On failure (insufficient
 * remaining capacity) logs requested/offset/remaining/capacity and returns
 * false, leaving the arena's offset unchanged.
 */
bool arena_alloc(Arena *a, const char *name, uint32_t size, uint32_t alignment, ArenaBuffer *out);

/**
 * Rewind the arena to empty. Only for model-change/shutdown -- never called
 * per IPC message.
 */
void arena_reset(Arena *a);

#endif /* ARENA_ALLOCATOR_HPP */
