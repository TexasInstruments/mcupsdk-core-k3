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
 * Signal Chain Arena State
 *
 * One-time buffer partitioning over host-provided IPC memory, shared by all
 * five models (DCCRN, GTCRN, GCRN, VGGish, YAMNet) via a per-model,
 * per-direction static spec table instead of hand-written per-model structs.
 *
 * The arena's backing memory is a fixed 1 MB DDR region defined in the linker
 * script, starting at __CUSTOM_STFT_MEM_START.
 * ARM no longer provides workspace memory via the IPC buffer.
 *
 * Allocation happens on the first call for a given (model, direction) only.
 * Every later call returns the cached buffers immediately.
 */

#ifndef SIGNAL_CHAIN_ARENA_HPP
#define SIGNAL_CHAIN_ARENA_HPP

#include <stdint.h>
#include "arena_allocator.hpp"

#define SIGNAL_CHAIN_ARENA_MAX_BUFFERS 8

typedef struct {
    const char *name;
    uint32_t    size;
} ArenaBufferSpec;

typedef struct {
    Arena       arena;
    bool        ready;   /* true after a successful partition; reset to false on model
                          * deactivation (see signal_chain_arena_reset_ready) */

    ArenaBuffer buffers[SIGNAL_CHAIN_ARENA_MAX_BUFFERS];
} SignalChainArenaState;

/**
 * First call (state->ready == false): partitions the fixed DDR region
 * per `specs`, logs each allocation under `arena_label`
 * ("STFT"/"ISTFT"), sets state->ready = true, fills state->buffers[0..num_specs).
 * Returns false only if a spec doesn't fit (state->ready stays false, so the
 * next message gets another first-call attempt).
 *
 * Every later call (state->ready == true): logs a single "reusing buffers"
 * line and returns true immediately.
 */
bool signal_chain_arena_ensure(SignalChainArenaState *state, const ArenaBufferSpec *specs, uint32_t num_specs,
                                const char *arena_label);

/**
 * Mark the arena as not-ready so the next signal_chain_arena_ensure() call
 * re-partitions it from the new ARM-provided buffer. Called on model
 * deactivation (stft_deinit) to avoid the old model's workspace addresses
 * being silently reused when the same model is re-activated later.
 */
void signal_chain_arena_reset_ready(SignalChainArenaState *state);

#endif /* SIGNAL_CHAIN_ARENA_HPP */
