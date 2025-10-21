/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

#ifndef __SIGCHAIN_DSP_MCASP_H__
#define __SIGCHAIN_DSP_MCASP_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include <drivers/pinmux.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>

#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

#include "dsp_offload.hpp"

    /* ========================================================================== */
    /*                           Macros & Typedefs                                */
    /* ========================================================================== */

#define NUM_BUFS (3U)
#define DMA_AUDIO_SAMPLE_SIZE (4U) /* audio sample: 32-bit */
#define BUFALIGN (256U)            /* alignment of buffer */
#define ADC_CHANNEL_COUNT (8U)
#define DAC_CHANNEL_COUNT (8U)
#define ADC_CHANNEL_STRIDE (8U)
#define DAC_CHANNEL_STRIDE (8U)
#define MAX_CHNL_COUNT (32U)

#define INPUT_CHANNEL_COUNT (ADC_CHANNEL_COUNT + AVB_RX_CHANNEL_COUNT)
#define OUTPUT_CHANNEL_COUNT (DAC_CHANNEL_COUNT + AVB_TX_CHANNEL_COUNT)

#define BUFSIZE_PER_CHANNEL (AUDIO_BLOCK_SIZE * DMA_AUDIO_SAMPLE_SIZE)
#define DMA_RX_BUF_SIZE (BUFSIZE_PER_CHANNEL * ADC_CHANNEL_COUNT)
#define DMA_TX_BUF_SIZE (BUFSIZE_PER_CHANNEL * DAC_CHANNEL_COUNT)

#define SIGCHAIN_BUF_SIZE (BUFSIZE_PER_CHANNEL * MAX_CHNL_COUNT)

#define MCASP_PROCESS_TASK_PRI (6U)
#define MCASP_PROCESS_TASK_STACKSIZE (65536U / sizeof(configSTACK_DEPTH_TYPE))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void SigchainDSP_McASP_setupAudioIO();

#if defined(__cplusplus)
}
#endif

#endif /* __SIGCHAIN_DSP_MCASP_H__ */
