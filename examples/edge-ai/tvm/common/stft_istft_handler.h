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

#ifndef STFT_ISTFT_HANDLER_H
#define STFT_ISTFT_HANDLER_H

#include <stdint.h>
#include "dsp_service.h"

/* STFT/ISTFT message structure */
struct stft_istft_msg
{
    struct c7x_msg_hdr hdr;
    uint32_t selected_model; /* ModelId: MODEL_DCCRN=0, MODEL_GTCRN=1, MODEL_GCRN=2,
                              *          MODEL_VGGISH=3, MODEL_YAMNET=4 (see model_config.h) */
    uint32_t input_buffer;
    uint32_t output_buffer;
    uint32_t input_frame;
    uint32_t output_frame;
};

/* RPMsg handlers for STFT/ISTFT processing (in stft_istft_handler.cpp) */
extern int32_t stft_analyze_handler(void *req, void *resp);
extern int32_t istft_synthesize_handler(void *req, void *resp);
#endif /* STFT_ISTFT_HANDLER_H */
