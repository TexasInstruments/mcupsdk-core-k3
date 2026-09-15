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
 * Signal Chain Arena State - Implementation
 */

#include "signal_chain_arena.hpp"
#include <kernel/dpl/DebugP.h>

extern uint8_t __CUSTOM_STFT_MEM_START;
extern uint8_t __CUSTOM_STFT_MEM_END;

bool signal_chain_arena_ensure(SignalChainArenaState *state, const ArenaBufferSpec *specs, uint32_t num_specs,
                                const char *arena_label)
{
    if (state->ready)
    {
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
        DebugP_log("[%s ARENA] Already initialized - reusing buffers\r\n", arena_label);
#endif
        return true;
    }

    if (num_specs > SIGNAL_CHAIN_ARENA_MAX_BUFFERS)
    {
        DebugP_log("[%s ARENA] ERROR: %u buffers requested, max %u\r\n",
                   arena_label, num_specs, SIGNAL_CHAIN_ARENA_MAX_BUFFERS);
        return false;
    }

    uint8_t *base     = &__CUSTOM_STFT_MEM_START;
    uint32_t capacity = (uint32_t)(&__CUSTOM_STFT_MEM_END - &__CUSTOM_STFT_MEM_START);

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("[%s ARENA INIT]\r\n", arena_label);
    DebugP_log("Base      : 0x%08X\r\n", (uint32_t)(uintptr_t)base);
    DebugP_log("Size      : %u bytes\r\n", capacity);
#endif
    Arena tmp_arena;
    arena_init(&tmp_arena, base, capacity, 128);

    ArenaBuffer tmp_buffers[SIGNAL_CHAIN_ARENA_MAX_BUFFERS];
    for (uint32_t i = 0; i < num_specs; i++)
    {
        if (!arena_alloc(&tmp_arena, specs[i].name, specs[i].size, 128, &tmp_buffers[i]))
	{
            /* Leave state untouched (ready stays false) so a corrected retry can succeed. */
            return false;
        }
    }

    state->arena = tmp_arena;
    for (uint32_t i = 0; i < num_specs; i++)
    {
        state->buffers[i] = tmp_buffers[i];
    }
    state->ready = true;

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("[%s ARENA] Used: %u  Remaining: %u\r\n", arena_label, tmp_arena.offset, tmp_arena.remaining);
#endif
    return true;
}

void signal_chain_arena_reset_ready(SignalChainArenaState *state)
{
    /* Clear the ready flag so the next signal_chain_arena_ensure() call
     * re-partitions the arena from the ARM-provided buffer of the new
     * activation.  arena_reset() rewinds the bump pointer so the stale
     * per-buffer addresses stored in state->buffers[] are no longer valid. */
    state->ready = false;
    arena_reset(&state->arena);
}
