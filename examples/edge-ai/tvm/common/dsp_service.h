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

#ifndef DSP_SERVICE_H
#define DSP_SERVICE_H

#include <stdint.h>
#include "c7x_compute_protocol.h"

#define C7X_SERVICE_ENDPOINT_GENERIC  13

/* STFT/ISTFT message types */
#define C7X_MSG_STFT_ANALYZE               0x1020
#define C7X_MSG_STFT_ANALYZE_RESP          0x2020
#define C7X_MSG_ISTFT_SYNTHESIZE           0x1030
#define C7X_MSG_ISTFT_SYNTHESIZE_RESP      0x2030

/* Utility signal chain message types (deinterleave, interleave, mattrans) */
#define C7X_UTILS_MSG_ANALYZE              0x1040
#define C7X_UTILS_MSG_ANALYZE_RESP         0x2040

int32_t dsp_service_init(void);
void    dsp_service_run(void);
void    dsp_service_stop(void);
void    dsp_service_main(void *args);

#endif /* DSP_SERVICE_H */
