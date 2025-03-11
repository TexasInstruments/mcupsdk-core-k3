/**********************************************************************
 * Copyright (C) 2012-2019 Cadence Design Systems, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
**********************************************************************
   csirx.c - CSIRX driver source file
**********************************************************************/

#include <drivers/hw_include/csl_csirx.h>
#include "cps_drv.h"
#include "csirx_sanity.h"

typedef struct {
    uint32_t mask;
    uint32_t shift;
} streamsDefs;

static const struct {
    uint32_t lineCntErrorIrqMask;
    uint32_t frameMismatchIrqMask;
    uint32_t frameCntErrorIrqMask;
    uint32_t fccStopIrqMask;
    uint32_t fccStartIrqMask;
    uint32_t frameIrqMask;
    uint32_t lbIrqMask;
    uint32_t timerIrqMask;
    uint32_t lineCntErrorIrqShift;
    uint32_t frameMismatchIrqShift;
    uint32_t frameCntErrorIrqShift;
    uint32_t fccStopIrqShift;
    uint32_t fccStartIrqShift;
    uint32_t frameIrqShift;
    uint32_t lbIrqShift;
    uint32_t timerIrqShift;
} monitorIrqsDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].lineCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM0_LINE_CNT_ERROR_IRQ_MASK,
    [0U].lineCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM0_LINE_CNT_ERROR_IRQ_SHIFT,
    [0U].frameMismatchIrqMask = CSIRX__MONITOR_IRQS__STREAM0_FRAME_MISMATCH_IRQ_MASK,
    [0U].frameMismatchIrqShift = CSIRX__MONITOR_IRQS__STREAM0_FRAME_MISMATCH_IRQ_SHIFT,
    [0U].frameCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM0_FRAME_CNT_ERROR_IRQ_MASK,
    [0U].frameCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM0_FRAME_CNT_ERROR_IRQ_SHIFT,
    [0U].fccStopIrqMask = CSIRX__MONITOR_IRQS__STREAM0_FCC_STOP_IRQ_MASK,
    [0U].fccStopIrqShift = CSIRX__MONITOR_IRQS__STREAM0_FCC_STOP_IRQ_SHIFT,
    [0U].fccStartIrqMask = CSIRX__MONITOR_IRQS__STREAM0_FCC_START_IRQ_MASK,
    [0U].fccStartIrqShift = CSIRX__MONITOR_IRQS__STREAM0_FCC_START_IRQ_SHIFT,
    [0U].frameIrqMask = CSIRX__MONITOR_IRQS__STREAM0_FRAME_IRQ_MASK,
    [0U].frameIrqShift = CSIRX__MONITOR_IRQS__STREAM0_FRAME_IRQ_SHIFT,
    [0U].lbIrqMask = CSIRX__MONITOR_IRQS__STREAM0_LB_IRQ_MASK,
    [0U].lbIrqShift = CSIRX__MONITOR_IRQS__STREAM0_LB_IRQ_SHIFT,
    [0U].timerIrqMask = CSIRX__MONITOR_IRQS__STREAM0_TIMER_IRQ_MASK,
    [0U].timerIrqShift = CSIRX__MONITOR_IRQS__STREAM0_TIMER_IRQ_SHIFT,

    [1U].lineCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM1_LINE_CNT_ERROR_IRQ_MASK,
    [1U].lineCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM1_LINE_CNT_ERROR_IRQ_SHIFT,
    [1U].frameMismatchIrqMask = CSIRX__MONITOR_IRQS__STREAM1_FRAME_MISMATCH_IRQ_MASK,
    [1U].frameMismatchIrqShift = CSIRX__MONITOR_IRQS__STREAM1_FRAME_MISMATCH_IRQ_SHIFT,
    [1U].frameCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM1_FRAME_CNT_ERROR_IRQ_MASK,
    [1U].frameCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM1_FRAME_CNT_ERROR_IRQ_SHIFT,
    [1U].fccStopIrqMask = CSIRX__MONITOR_IRQS__STREAM1_FCC_STOP_IRQ_MASK,
    [1U].fccStopIrqShift = CSIRX__MONITOR_IRQS__STREAM1_FCC_STOP_IRQ_SHIFT,
    [1U].fccStartIrqMask = CSIRX__MONITOR_IRQS__STREAM1_FCC_START_IRQ_MASK,
    [1U].fccStartIrqShift = CSIRX__MONITOR_IRQS__STREAM1_FCC_START_IRQ_SHIFT,
    [1U].frameIrqMask = CSIRX__MONITOR_IRQS__STREAM1_FRAME_IRQ_MASK,
    [1U].frameIrqShift = CSIRX__MONITOR_IRQS__STREAM1_FRAME_IRQ_SHIFT,
    [1U].lbIrqMask = CSIRX__MONITOR_IRQS__STREAM1_LB_IRQ_MASK,
    [1U].lbIrqShift = CSIRX__MONITOR_IRQS__STREAM1_LB_IRQ_SHIFT,
    [1U].timerIrqMask = CSIRX__MONITOR_IRQS__STREAM1_TIMER_IRQ_MASK,
    [1U].timerIrqShift = CSIRX__MONITOR_IRQS__STREAM1_TIMER_IRQ_SHIFT,

    [2U].lineCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM2_LINE_CNT_ERROR_IRQ_MASK,
    [2U].lineCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM2_LINE_CNT_ERROR_IRQ_SHIFT,
    [2U].frameMismatchIrqMask = CSIRX__MONITOR_IRQS__STREAM2_FRAME_MISMATCH_IRQ_MASK,
    [2U].frameMismatchIrqShift = CSIRX__MONITOR_IRQS__STREAM2_FRAME_MISMATCH_IRQ_SHIFT,
    [2U].frameCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM2_FRAME_CNT_ERROR_IRQ_MASK,
    [2U].frameCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM2_FRAME_CNT_ERROR_IRQ_SHIFT,
    [2U].fccStopIrqMask = CSIRX__MONITOR_IRQS__STREAM2_FCC_STOP_IRQ_MASK,
    [2U].fccStopIrqShift = CSIRX__MONITOR_IRQS__STREAM2_FCC_STOP_IRQ_SHIFT,
    [2U].fccStartIrqMask = CSIRX__MONITOR_IRQS__STREAM2_FCC_START_IRQ_MASK,
    [2U].fccStartIrqShift = CSIRX__MONITOR_IRQS__STREAM2_FCC_START_IRQ_SHIFT,
    [2U].frameIrqMask = CSIRX__MONITOR_IRQS__STREAM2_FRAME_IRQ_MASK,
    [2U].frameIrqShift = CSIRX__MONITOR_IRQS__STREAM2_FRAME_IRQ_SHIFT,
    [2U].lbIrqMask = CSIRX__MONITOR_IRQS__STREAM2_LB_IRQ_MASK,
    [2U].lbIrqShift = CSIRX__MONITOR_IRQS__STREAM2_LB_IRQ_SHIFT,
    [2U].timerIrqMask = CSIRX__MONITOR_IRQS__STREAM2_TIMER_IRQ_MASK,
    [2U].timerIrqShift = CSIRX__MONITOR_IRQS__STREAM2_TIMER_IRQ_SHIFT,

    [3U].lineCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM3_LINE_CNT_ERROR_IRQ_MASK,
    [3U].lineCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM3_LINE_CNT_ERROR_IRQ_SHIFT,
    [3U].frameMismatchIrqMask = CSIRX__MONITOR_IRQS__STREAM3_FRAME_MISMATCH_IRQ_MASK,
    [3U].frameMismatchIrqShift = CSIRX__MONITOR_IRQS__STREAM3_FRAME_MISMATCH_IRQ_SHIFT,
    [3U].frameCntErrorIrqMask = CSIRX__MONITOR_IRQS__STREAM3_FRAME_CNT_ERROR_IRQ_MASK,
    [3U].frameCntErrorIrqShift = CSIRX__MONITOR_IRQS__STREAM3_FRAME_CNT_ERROR_IRQ_SHIFT,
    [3U].fccStopIrqMask = CSIRX__MONITOR_IRQS__STREAM3_FCC_STOP_IRQ_MASK,
    [3U].fccStopIrqShift = CSIRX__MONITOR_IRQS__STREAM3_FCC_STOP_IRQ_SHIFT,
    [3U].fccStartIrqMask = CSIRX__MONITOR_IRQS__STREAM3_FCC_START_IRQ_MASK,
    [3U].fccStartIrqShift = CSIRX__MONITOR_IRQS__STREAM3_FCC_START_IRQ_SHIFT,
    [3U].frameIrqMask = CSIRX__MONITOR_IRQS__STREAM3_FRAME_IRQ_MASK,
    [3U].frameIrqShift = CSIRX__MONITOR_IRQS__STREAM3_FRAME_IRQ_SHIFT,
    [3U].lbIrqMask = CSIRX__MONITOR_IRQS__STREAM3_LB_IRQ_MASK,
    [3U].lbIrqShift = CSIRX__MONITOR_IRQS__STREAM3_LB_IRQ_SHIFT,
    [3U].timerIrqMask = CSIRX__MONITOR_IRQS__STREAM3_TIMER_IRQ_MASK,
    [3U].timerIrqShift = CSIRX__MONITOR_IRQS__STREAM3_TIMER_IRQ_SHIFT,
};

static const struct {
    uint32_t lineCntErrorIrqmMask;
    uint32_t lineCntErrorIrqmShift;
    uint32_t frameMismatchIrqmMask;
    uint32_t frameMismatchIrqmShift;
    uint32_t frameCntErrorIrqmMask;
    uint32_t frameCntErrorIrqmShift;
    uint32_t fccStopIrqmMask;
    uint32_t fccStopIrqmShift;
    uint32_t fccStartIrqmMask;
    uint32_t fccStartIrqmShift;
    uint32_t frameIrqmMask;
    uint32_t frameIrqmShift;
    uint32_t lbIrqmMask;
    uint32_t lbIrqmShift;
    uint32_t timerIrqmMask;
    uint32_t timerIrqmShift;
} monitorIrqsMaskCfgDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].lineCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_LINE_CNT_ERROR_IRQM_MASK,
    [0U].lineCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_LINE_CNT_ERROR_IRQM_SHIFT,
    [0U].frameMismatchIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_MISMATCH_IRQM_MASK,
    [0U].frameMismatchIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_MISMATCH_IRQM_SHIFT,
    [0U].frameCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_CNT_ERROR_IRQM_MASK,
    [0U].frameCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_CNT_ERROR_IRQM_SHIFT,
    [0U].fccStopIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FCC_STOP_IRQM_MASK,
    [0U].fccStopIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FCC_STOP_IRQM_SHIFT,
    [0U].fccStartIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FCC_START_IRQM_MASK,
    [0U].fccStartIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FCC_START_IRQM_SHIFT,
    [0U].frameIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_IRQM_MASK,
    [0U].frameIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_FRAME_IRQM_SHIFT,
    [0U].lbIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_LB_IRQM_MASK,
    [0U].lbIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_LB_IRQM_SHIFT,
    [0U].timerIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_TIMER_IRQM_MASK,
    [0U].timerIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM0_TIMER_IRQM_SHIFT,

    [1U].lineCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_LINE_CNT_ERROR_IRQM_MASK,
    [1U].lineCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_LINE_CNT_ERROR_IRQM_SHIFT,
    [1U].frameMismatchIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_MISMATCH_IRQM_MASK,
    [1U].frameMismatchIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_MISMATCH_IRQM_SHIFT,
    [1U].frameCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_CNT_ERROR_IRQM_MASK,
    [1U].frameCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_CNT_ERROR_IRQM_SHIFT,
    [1U].fccStopIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FCC_STOP_IRQM_MASK,
    [1U].fccStopIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FCC_STOP_IRQM_SHIFT,
    [1U].fccStartIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FCC_START_IRQM_MASK,
    [1U].fccStartIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FCC_START_IRQM_SHIFT,
    [1U].frameIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_IRQM_MASK,
    [1U].frameIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_FRAME_IRQM_SHIFT,
    [1U].lbIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_LB_IRQM_MASK,
    [1U].lbIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_LB_IRQM_SHIFT,
    [1U].timerIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_TIMER_IRQM_MASK,
    [1U].timerIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM1_TIMER_IRQM_SHIFT,

    [2U].lineCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_LINE_CNT_ERROR_IRQM_MASK,
    [2U].lineCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_LINE_CNT_ERROR_IRQM_SHIFT,
    [2U].frameMismatchIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_MISMATCH_IRQM_MASK,
    [2U].frameMismatchIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_MISMATCH_IRQM_SHIFT,
    [2U].frameCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_CNT_ERROR_IRQM_MASK,
    [2U].frameCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_CNT_ERROR_IRQM_SHIFT,
    [2U].fccStopIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FCC_STOP_IRQM_MASK,
    [2U].fccStopIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FCC_STOP_IRQM_SHIFT,
    [2U].fccStartIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FCC_START_IRQM_MASK,
    [2U].fccStartIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FCC_START_IRQM_SHIFT,
    [2U].frameIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_IRQM_MASK,
    [2U].frameIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_FRAME_IRQM_SHIFT,
    [2U].lbIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_LB_IRQM_MASK,
    [2U].lbIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_LB_IRQM_SHIFT,
    [2U].timerIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_TIMER_IRQM_MASK,
    [2U].timerIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM2_TIMER_IRQM_SHIFT,

    [3U].lineCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_LINE_CNT_ERROR_IRQM_MASK,
    [3U].lineCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_LINE_CNT_ERROR_IRQM_SHIFT,
    [3U].frameMismatchIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_MISMATCH_IRQM_MASK,
    [3U].frameMismatchIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_MISMATCH_IRQM_SHIFT,
    [3U].frameCntErrorIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_CNT_ERROR_IRQM_MASK,
    [3U].frameCntErrorIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_CNT_ERROR_IRQM_SHIFT,
    [3U].fccStopIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FCC_STOP_IRQM_MASK,
    [3U].fccStopIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FCC_STOP_IRQM_SHIFT,
    [3U].fccStartIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FCC_START_IRQM_MASK,
    [3U].fccStartIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FCC_START_IRQM_SHIFT,
    [3U].frameIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_IRQM_MASK,
    [3U].frameIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_FRAME_IRQM_SHIFT,
    [3U].lbIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_LB_IRQM_MASK,
    [3U].lbIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_LB_IRQM_SHIFT,
    [3U].timerIrqmMask = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_TIMER_IRQM_MASK,
    [3U].timerIrqmShift = CSIRX__MONITOR_IRQS_MASK_CFG__STREAM3_TIMER_IRQM_SHIFT,
};

static const struct {
    uint32_t fifoOverflowIrqMask;
    uint32_t fifoOverflowIrqShift;
} errorIrqsDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].fifoOverflowIrqMask = CSIRX__ERROR_IRQS__STREAM0_FIFO_OVERFLOW_IRQ_MASK,
    [0U].fifoOverflowIrqShift = CSIRX__ERROR_IRQS__STREAM0_FIFO_OVERFLOW_IRQ_SHIFT,

    [1U].fifoOverflowIrqMask = CSIRX__ERROR_IRQS__STREAM1_FIFO_OVERFLOW_IRQ_MASK,
    [1U].fifoOverflowIrqShift = CSIRX__ERROR_IRQS__STREAM1_FIFO_OVERFLOW_IRQ_SHIFT,

    [2U].fifoOverflowIrqMask = CSIRX__ERROR_IRQS__STREAM2_FIFO_OVERFLOW_IRQ_MASK,
    [2U].fifoOverflowIrqShift = CSIRX__ERROR_IRQS__STREAM2_FIFO_OVERFLOW_IRQ_SHIFT,

    [3U].fifoOverflowIrqMask = CSIRX__ERROR_IRQS__STREAM3_FIFO_OVERFLOW_IRQ_MASK,
    [3U].fifoOverflowIrqShift = CSIRX__ERROR_IRQS__STREAM3_FIFO_OVERFLOW_IRQ_SHIFT,
};

static const struct {
    uint32_t fifoOverflowIrqmMask;
    uint32_t fifoOverflowIrqmShift;
} errorIrqsMaskCfgDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].fifoOverflowIrqmMask = CSIRX__ERROR_IRQS_MASK_CFG__STREAM0_FIFO_OVERFLOW_IRQM_MASK,
    [0U].fifoOverflowIrqmShift = CSIRX__ERROR_IRQS_MASK_CFG__STREAM0_FIFO_OVERFLOW_IRQM_SHIFT,

    [1U].fifoOverflowIrqmMask = CSIRX__ERROR_IRQS_MASK_CFG__STREAM1_FIFO_OVERFLOW_IRQM_MASK,
    [1U].fifoOverflowIrqmShift = CSIRX__ERROR_IRQS_MASK_CFG__STREAM1_FIFO_OVERFLOW_IRQM_SHIFT,

    [2U].fifoOverflowIrqmMask = CSIRX__ERROR_IRQS_MASK_CFG__STREAM2_FIFO_OVERFLOW_IRQM_MASK,
    [2U].fifoOverflowIrqmShift = CSIRX__ERROR_IRQS_MASK_CFG__STREAM2_FIFO_OVERFLOW_IRQM_SHIFT,

    [3U].fifoOverflowIrqmMask = CSIRX__ERROR_IRQS_MASK_CFG__STREAM3_FIFO_OVERFLOW_IRQM_MASK,
    [3U].fifoOverflowIrqmShift = CSIRX__ERROR_IRQS_MASK_CFG__STREAM3_FIFO_OVERFLOW_IRQM_SHIFT,
};

static const struct {
    uint32_t abortIrqMask;
    uint32_t abortIrqShift;
    uint32_t stopIrqMask;
    uint32_t stopIrqShift;
} infoIrqsDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].abortIrqMask = CSIRX__INFO_IRQS__STREAM0_ABORT_IRQ_MASK,
    [0U].abortIrqShift = CSIRX__INFO_IRQS__STREAM0_ABORT_IRQ_SHIFT,
    [0U].stopIrqMask = CSIRX__INFO_IRQS__STREAM0_STOP_IRQ_MASK,
    [0U].stopIrqShift = CSIRX__INFO_IRQS__STREAM0_STOP_IRQ_SHIFT,

    [1U].abortIrqMask = CSIRX__INFO_IRQS__STREAM1_ABORT_IRQ_MASK,
    [1U].abortIrqShift = CSIRX__INFO_IRQS__STREAM1_ABORT_IRQ_SHIFT,
    [1U].stopIrqMask = CSIRX__INFO_IRQS__STREAM1_STOP_IRQ_MASK,
    [1U].stopIrqShift = CSIRX__INFO_IRQS__STREAM1_STOP_IRQ_SHIFT,

    [2U].abortIrqMask = CSIRX__INFO_IRQS__STREAM2_ABORT_IRQ_MASK,
    [2U].abortIrqShift = CSIRX__INFO_IRQS__STREAM2_ABORT_IRQ_SHIFT,
    [2U].stopIrqMask = CSIRX__INFO_IRQS__STREAM2_STOP_IRQ_MASK,
    [2U].stopIrqShift = CSIRX__INFO_IRQS__STREAM2_STOP_IRQ_SHIFT,

    [3U].abortIrqMask = CSIRX__INFO_IRQS__STREAM3_ABORT_IRQ_MASK,
    [3U].abortIrqShift = CSIRX__INFO_IRQS__STREAM3_ABORT_IRQ_SHIFT,
    [3U].stopIrqMask = CSIRX__INFO_IRQS__STREAM3_STOP_IRQ_MASK,
    [3U].stopIrqShift = CSIRX__INFO_IRQS__STREAM3_STOP_IRQ_SHIFT,
};

static const struct {
    uint32_t abortIrqmMask;
    uint32_t abortIrqmShift;
    uint32_t stopIrqmMask;
    uint32_t stopIrqmShift;
} infoIrqsMaskCfgDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].abortIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM0_ABORT_IRQM_MASK,
    [0U].abortIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM0_ABORT_IRQM_SHIFT,
    [0U].stopIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM0_STOP_IRQM_MASK,
    [0U].stopIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM0_STOP_IRQM_SHIFT,

    [1U].abortIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM1_ABORT_IRQM_MASK,
    [1U].abortIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM1_ABORT_IRQM_SHIFT,
    [1U].stopIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM1_STOP_IRQM_MASK,
    [1U].stopIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM1_STOP_IRQM_SHIFT,

    [2U].abortIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM2_ABORT_IRQM_MASK,
    [2U].abortIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM2_ABORT_IRQM_SHIFT,
    [2U].stopIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM2_STOP_IRQM_MASK,
    [2U].stopIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM2_STOP_IRQM_SHIFT,

    [3U].abortIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM3_ABORT_IRQM_MASK,
    [3U].abortIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM3_ABORT_IRQM_SHIFT,
    [3U].stopIrqmMask = CSIRX__INFO_IRQS_MASK_CFG__STREAM3_STOP_IRQM_MASK,
    [3U].stopIrqmShift = CSIRX__INFO_IRQS_MASK_CFG__STREAM3_STOP_IRQM_SHIFT,
};

static const struct {
    uint32_t dlEnableMask;
    uint32_t dlEnableShift;
    uint32_t dlResetMask;
    uint32_t dlResetShift;
} dphyLaneControlDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].dlEnableMask = CSIRX__DPHY_LANE_CONTROL__DL0_ENABLE_MASK,
    [0U].dlEnableShift = CSIRX__DPHY_LANE_CONTROL__DL0_ENABLE_SHIFT,
    [0U].dlResetMask = CSIRX__DPHY_LANE_CONTROL__DL0_RESET_MASK,
    [0U].dlResetShift = CSIRX__DPHY_LANE_CONTROL__DL0_RESET_SHIFT,

    [1U].dlEnableMask = CSIRX__DPHY_LANE_CONTROL__DL1_ENABLE_MASK,
    [1U].dlEnableShift = CSIRX__DPHY_LANE_CONTROL__DL1_ENABLE_SHIFT,
    [1U].dlResetMask = CSIRX__DPHY_LANE_CONTROL__DL1_RESET_MASK,
    [1U].dlResetShift = CSIRX__DPHY_LANE_CONTROL__DL1_RESET_SHIFT,

    [2U].dlEnableMask = CSIRX__DPHY_LANE_CONTROL__DL2_ENABLE_MASK,
    [2U].dlEnableShift = CSIRX__DPHY_LANE_CONTROL__DL2_ENABLE_SHIFT,
    [2U].dlResetMask = CSIRX__DPHY_LANE_CONTROL__DL2_RESET_MASK,
    [2U].dlResetShift = CSIRX__DPHY_LANE_CONTROL__DL2_RESET_SHIFT,

    [3U].dlEnableMask = CSIRX__DPHY_LANE_CONTROL__DL3_ENABLE_MASK,
    [3U].dlEnableShift = CSIRX__DPHY_LANE_CONTROL__DL3_ENABLE_SHIFT,
    [3U].dlResetMask = CSIRX__DPHY_LANE_CONTROL__DL3_RESET_MASK,
    [3U].dlResetShift = CSIRX__DPHY_LANE_CONTROL__DL3_RESET_SHIFT,
};

static const struct {
    uint32_t dlErrSotHSIrqMask;
    uint32_t dlErrSotHSIrqShift;
} dphyErrStatusIrqDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].dlErrSotHSIrqMask = CSIRX__DPHY_ERR_STATUS_IRQ__DL0_ERRSOTHS_IRQ_MASK,
    [0U].dlErrSotHSIrqShift = CSIRX__DPHY_ERR_STATUS_IRQ__DL0_ERRSOTHS_IRQ_SHIFT,
    [1U].dlErrSotHSIrqMask = CSIRX__DPHY_ERR_STATUS_IRQ__DL1_ERRSOTHS_IRQ_MASK,
    [1U].dlErrSotHSIrqShift = CSIRX__DPHY_ERR_STATUS_IRQ__DL1_ERRSOTHS_IRQ_SHIFT,
    [2U].dlErrSotHSIrqMask = CSIRX__DPHY_ERR_STATUS_IRQ__DL2_ERRSOTHS_IRQ_MASK,
    [2U].dlErrSotHSIrqShift = CSIRX__DPHY_ERR_STATUS_IRQ__DL2_ERRSOTHS_IRQ_SHIFT,
    [3U].dlErrSotHSIrqMask = CSIRX__DPHY_ERR_STATUS_IRQ__DL3_ERRSOTHS_IRQ_MASK,
    [3U].dlErrSotHSIrqShift = CSIRX__DPHY_ERR_STATUS_IRQ__DL3_ERRSOTHS_IRQ_SHIFT,
};

static const struct {
    uint32_t dlErrSotHSIrqmMask;
    uint32_t dlErrSotHSIrqmShift;
} dphyErrIrqMaskCfgDefs[CSIRX_MAX_NUM_OF_STREAMS] = {
    [0U].dlErrSotHSIrqmMask = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL0_ERRSOTHS_IRQM_MASK,
    [0U].dlErrSotHSIrqmShift = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL0_ERRSOTHS_IRQM_SHIFT,
    [1U].dlErrSotHSIrqmMask = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL1_ERRSOTHS_IRQM_MASK,
    [1U].dlErrSotHSIrqmShift = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL1_ERRSOTHS_IRQM_SHIFT,
    [2U].dlErrSotHSIrqmMask = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL2_ERRSOTHS_IRQM_MASK,
    [2U].dlErrSotHSIrqmShift = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL2_ERRSOTHS_IRQM_SHIFT,
    [3U].dlErrSotHSIrqmMask = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL3_ERRSOTHS_IRQM_MASK,
    [3U].dlErrSotHSIrqmShift = CSIRX__DPHY_ERR_IRQ_MASK_CFG__DL3_ERRSOTHS_IRQM_SHIFT,
};

/* helper function */
static uint32_t checkMagicNumber(const CSIRX_Config *config) {
    uint32_t result = CDN_EOK;
    uint32_t volatile *idRegAddr = &((CSIRX_Regs volatile*)config->regBase)->id_prod_ver;
    uint32_t magicNumber = CPS_REG_READ(idRegAddr);
    if (magicNumber != CSIRX_MAGIC_NUMBER) {
        result = CDN_EINVAL;
    }
    return result;
}

/**
 * Get the driver's memory requirements to support the given
 * configuration.
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSIRX_Probe(const CSIRX_Config *config, CSIRX_SysReq *memReq)
{
    uint32_t status = CDN_EOK;

    /* check parameters */
    if ((CSIRX_ProbeSF(config, memReq) != CDN_EOK) || (checkMagicNumber(config) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        memReq->privDataSize = (uint32_t) sizeof(CSIRX_PrivateData);
    }
    return status;
}

/**
 * Initialize the driver. Must be called before all other access APIs.
 * The init function will retain the default value in the hardware.
 * @param[in] pD Memory pointer to the uninitialized private data of the size specified by probe.
 * @param[in] config specifies driver/hardware configuration
 * @param[in] irqs info interrupt handler
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_Init(CSIRX_PrivateData* pD, const CSIRX_Config *config, const CSIRX_InterruptsHandlers *irqs)
{
    uint32_t status = CDN_EOK;

    /* check parameters */
    if ((CSIRX_InitSF(pD, config, irqs) != CDN_EOK)
        || (checkMagicNumber(config) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        ((CSIRX_PrivateData *)pD)->cfg = *config;
        pD->regs = pD->cfg.regBase;
        pD->infoHandler = irqs->infoHandler;
        pD->monitorHandler = irqs->monitorHandler;
        pD->errorHandler = irqs->errorHandler;
        pD->dphyErrorHandler = irqs->dphyHandler;

        /* get configuration of IP */
        status = CSIRX_GetDeviceConfig(pD, &pD->deviceConfig);
    }
    return (status);
}

/* desctructor of the driver
 *
 * This funtion is intentionally kept empty - to conform common API shape */
void CSIRX_Destroy(void) {
    return;
}

/* helper function */
static const streamsDefs* getStreamMonitorPresentCfg(uint8_t streamNo) {

    static const streamsDefs monitorPresentDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_MONITOR_PRESENT_MASK,
        [0U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_MONITOR_PRESENT_SHIFT,
        [1U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_MONITOR_PRESENT_MASK,
        [1U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_MONITOR_PRESENT_SHIFT,
        [2U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_MONITOR_PRESENT_MASK,
        [2U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_MONITOR_PRESENT_SHIFT,
        [3U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_MONITOR_PRESENT_MASK,
        [3U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_MONITOR_PRESENT_SHIFT,
    };

    return (&monitorPresentDefsArr[streamNo]);
}

/* helper function */
static const streamsDefs* getStreamNumPixelsCfg(uint8_t streamNo) {

    static const streamsDefs numPixelsDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_NUM_PIXELS_MASK,
        [0U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_NUM_PIXELS_SHIFT,
        [1U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_NUM_PIXELS_MASK,
        [1U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_NUM_PIXELS_SHIFT,
        [2U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_NUM_PIXELS_MASK,
        [2U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_NUM_PIXELS_SHIFT,
        [3U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_NUM_PIXELS_MASK,
        [3U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_NUM_PIXELS_SHIFT,
    };

    return (&numPixelsDefsArr[streamNo]);
}

/* helper function */
static const streamsDefs* getStreamFifoModeCfg(uint8_t streamNo) {

    static const streamsDefs fifoModeDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_FIFO_MODE_MASK,
        [0U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM0_FIFO_MODE_SHIFT,
        [1U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_FIFO_MODE_MASK,
        [1U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM1_FIFO_MODE_SHIFT,
        [2U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_FIFO_MODE_MASK,
        [2U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM2_FIFO_MODE_SHIFT,
        [3U].mask = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_FIFO_MODE_MASK,
        [3U].shift = (uint32_t)CSIRX__DEVICE_CONFIG__STREAM3_FIFO_MODE_SHIFT,
    };

    return (&fifoModeDefsArr[streamNo]);
}

/**
 * getter for DeviceConfig
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDeviceConfig(const CSIRX_PrivateData *pD,
                               CSIRX_DeviceConfig *     value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetDeviceConfigSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get information related to the current configuration of the controller */
        regVal = CPS_REG_READ(&pD->regs->device_config);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->monitorPresent[i] = (uint8_t)(CPS_FldRead(getStreamMonitorPresentCfg(i)->mask, getStreamMonitorPresentCfg(i)->shift, regVal));
            value->numPixels[i] = (uint8_t)(CPS_FldRead(getStreamNumPixelsCfg(i)->mask, getStreamNumPixelsCfg(i)->shift, regVal));
            value->fifoMode[i] = (uint8_t)(CPS_FldRead(getStreamFifoModeCfg(i)->mask, getStreamFifoModeCfg(i)->shift, regVal));
        }

        value->datapathSize = (uint8_t)(CPS_FLD_READ(CSIRX__DEVICE_CONFIG, DATAPATH_SIZE, regVal));
        value->numStreams = (uint8_t)(CPS_FLD_READ(CSIRX__DEVICE_CONFIG, NUM_STREAMS, regVal));
        value->cdnsPhyPresent = (uint8_t)(CPS_FLD_READ(CSIRX__DEVICE_CONFIG, CDNS_PHY_PRESENT, regVal));
        value->maxLaneNb = (uint8_t)(CPS_FLD_READ(CSIRX__DEVICE_CONFIG, MAX_LANE_NB, regVal));
        value->vcxConfig = (uint8_t) (CPS_FLD_READ(CSIRX__DEVICE_CONFIG, VCX_CONFIG, regVal));
        value->asfConfig = (uint8_t) (CPS_FLD_READ(CSIRX__DEVICE_CONFIG, ASF_CONFIG, regVal));
    }
    return (status);
}

/**
 * getter for SoftReset
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetSoftReset(const CSIRX_PrivateData *pD,
                            CSIRX_SoftReset *        value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetSoftResetSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->soft_reset);
        value->protocol = (uint8_t)(CPS_FLD_READ(CSIRX__SOFT_RESET, PROTOCOL, regVal));
        value->front = (uint8_t)(CPS_FLD_READ(CSIRX__SOFT_RESET, FRONT, regVal));
    }
    return (status);
}

/**
 * setter for SoftReset
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetSoftReset(CSIRX_PrivateData *    pD,
                            const CSIRX_SoftReset *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetSoftResetSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = (CPS_FLD_WRITE(CSIRX__SOFT_RESET, PROTOCOL, regVal, value->protocol));
        regVal = (CPS_FLD_WRITE(CSIRX__SOFT_RESET, FRONT, regVal, value->front));
        CPS_REG_WRITE(&pD->regs->soft_reset, regVal);

    }
    return (status);
}

/**
 * getter for StaticCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStaticCfg(const CSIRX_PrivateData *pD,
                            CSIRX_StaticCfg *        value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStaticCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Lane mapping, ECC support, numbers of used lanes */
        regVal = CPS_REG_READ(&pD->regs->static_cfg);
        value->dlMap[3] = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, DL3_MAP, regVal));
        value->dlMap[2] = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, DL2_MAP, regVal));
        value->dlMap[1] = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, DL1_MAP, regVal));
        value->dlMap[0] = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, DL0_MAP, regVal));
        value->laneNb = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, LANE_NB, regVal));
        value->sel = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG, SEL, regVal));
        value->enable2p0Support = (uint8_t)(CPS_FLD_READ(CSIRX__STATIC_CFG,
                                                         V2P0_SUPPORT_ENABLE,
                                                         regVal));
    }
    return (status);
}

/**
 * setter for StaticCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStaticCfg(CSIRX_PrivateData *    pD,
                            const CSIRX_StaticCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStaticCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* set Lane mapping, ECC support, numbers of used lanes */
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, DL3_MAP, regVal, value->dlMap[3]));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, DL2_MAP, regVal, value->dlMap[2]));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, DL1_MAP, regVal, value->dlMap[1]));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, DL0_MAP, regVal, value->dlMap[0]));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, LANE_NB, regVal, value->laneNb));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG, SEL, regVal, value->sel));
        regVal = (CPS_FLD_WRITE(CSIRX__STATIC_CFG,
                                V2P0_SUPPORT_ENABLE,
                                regVal,
                                value->enable2p0Support));
        CPS_REG_WRITE(&pD->regs->static_cfg, regVal);
    }
    return (status);
}

/**
 * getter for ErrorBypassCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorBypassCfg(const CSIRX_PrivateData *pD,
                                 CSIRX_ErrorBypassCfg *   value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetErrorBypassCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->error_bypass_cfg);
        value->dataId = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_BYPASS_CFG, DATA_ID, regVal));
        value->ecc = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_BYPASS_CFG, ECC, regVal));
        value->crc = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_BYPASS_CFG, CRC, regVal));
    }
    return (status);
}

/**
 * setter for ErrorBypassCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorBypassCfg(CSIRX_PrivateData *         pD,
                                 const CSIRX_ErrorBypassCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetErrorBypassCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_BYPASS_CFG, DATA_ID, regVal, value->dataId));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_BYPASS_CFG, ECC, regVal, value->ecc));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_BYPASS_CFG, CRC, regVal, value->crc));
        CPS_REG_WRITE(&pD->regs->error_bypass_cfg, regVal);
    }
    return (status);
}

/**
 * getter for InfoIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetInfoIrqsMaskCfg(const CSIRX_PrivateData *pD,
                                  CSIRX_InfoIrqsMaskCfg *  value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetInfoIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Information Interrupt Mask for each stream */
        regVal = CPS_REG_READ(&pD->regs->info_irqs_mask_cfg);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->abortIrqm[i] = (uint8_t)(CPS_FldRead(infoIrqsMaskCfgDefs[i].abortIrqmMask, infoIrqsMaskCfgDefs[i].abortIrqmShift, regVal));
            value->stopIrqm[i] = (uint8_t)(CPS_FldRead(infoIrqsMaskCfgDefs[i].stopIrqmMask, infoIrqsMaskCfgDefs[i].stopIrqmShift, regVal));
        }

        value->spGenericRcvdIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, SP_GENERIC_RCVD_IRQM, regVal));
        value->deskewEntryIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, DESKEW_ENTRY_IRQM, regVal));
        value->eccSparesNonzeroIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, ECC_SPARES_NONZERO_IRQM, regVal));
        value->wakeupIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, WAKEUP_IRQM, regVal));
        value->sleepIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, SLEEP_IRQM, regVal));
        value->lpRcvdIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, LP_RCVD_IRQM, regVal));
        value->spRcvdIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS_MASK_CFG, SP_RCVD_IRQM, regVal));
    }
    return (status);
}

/**
 * setter for InfoIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetInfoIrqsMaskCfg(CSIRX_PrivateData *          pD,
                                  const CSIRX_InfoIrqsMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetInfoIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        /* set Information Interrupt Mask for each stream */
        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(infoIrqsMaskCfgDefs[i].abortIrqmMask, infoIrqsMaskCfgDefs[i].abortIrqmShift, regVal, value->abortIrqm[i]));
            regVal = (CPS_FldWrite(infoIrqsMaskCfgDefs[i].stopIrqmMask, infoIrqsMaskCfgDefs[i].stopIrqmShift, regVal, value->stopIrqm[i]));
        }

        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, SP_GENERIC_RCVD_IRQM, regVal, value->spGenericRcvdIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, DESKEW_ENTRY_IRQM, regVal, value->deskewEntryIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, ECC_SPARES_NONZERO_IRQM, regVal, value->eccSparesNonzeroIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, WAKEUP_IRQM, regVal, value->wakeupIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, SLEEP_IRQM, regVal, value->sleepIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, LP_RCVD_IRQM, regVal, value->lpRcvdIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS_MASK_CFG, SP_RCVD_IRQM, regVal, value->spRcvdIrqm));
        CPS_REG_WRITE(&pD->regs->info_irqs_mask_cfg, regVal);
    }
    return (status);
}

/* helper function  */
static void getMonitorIrqsMaskCfgStreamsFrm(CSIRX_MonitorIrqsMaskCfg *value, uint32_t regVal)
{
    uint8_t i;

    /* get Monitor Interrupt Mask for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        value->frameMismatchIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].frameMismatchIrqmMask, monitorIrqsMaskCfgDefs[i].frameMismatchIrqmShift, regVal));
        value->frameCntErrorIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].frameCntErrorIrqmMask, monitorIrqsMaskCfgDefs[i].frameCntErrorIrqmShift, regVal));
        value->frameIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].frameIrqmMask, monitorIrqsMaskCfgDefs[i].frameIrqmShift, regVal));
    }
    return;
}

/* helper function */
static void getMonitorIrqsMaskCfgStreams(CSIRX_MonitorIrqsMaskCfg *value, uint32_t regVal)
{
    uint8_t i;

    /* get Monitor Interrupt Mask for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        value->lineCntErrorIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].lineCntErrorIrqmMask, monitorIrqsMaskCfgDefs[i].lineCntErrorIrqmShift, regVal));
        value->fccStopIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].fccStopIrqmMask, monitorIrqsMaskCfgDefs[i].fccStopIrqmShift, regVal));
        value->fccStartIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].fccStartIrqmMask, monitorIrqsMaskCfgDefs[i].fccStartIrqmShift, regVal));
        value->lbIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].lbIrqmMask, monitorIrqsMaskCfgDefs[i].lbIrqmShift, regVal));
        value->timerIrqm[i] = (uint8_t)(CPS_FldRead(monitorIrqsMaskCfgDefs[i].timerIrqmMask, monitorIrqsMaskCfgDefs[i].timerIrqmShift, regVal));
    }
    return;
}

/**
 * getter for MonitorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetMonitorIrqsMaskCfg(const CSIRX_PrivateData * pD,
                                     CSIRX_MonitorIrqsMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetMonitorIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->monitor_irqs_mask_cfg);

        getMonitorIrqsMaskCfgStreamsFrm(value, regVal);
        getMonitorIrqsMaskCfgStreams(value, regVal);
    }
    return (status);
}

/* helper function */
static uint32_t setMonitorIrqsMaskCfgStreamsFrm(const CSIRX_MonitorIrqsMaskCfg *value, uint32_t regVal)
{
    uint32_t regValue = regVal;
    uint8_t i;

    /* set Monitor Interrupt Mask for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].frameMismatchIrqmMask, monitorIrqsMaskCfgDefs[i].frameMismatchIrqmShift, regValue, value->frameMismatchIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].frameCntErrorIrqmMask, monitorIrqsMaskCfgDefs[i].frameCntErrorIrqmShift, regValue, value->frameCntErrorIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].frameIrqmMask, monitorIrqsMaskCfgDefs[i].frameIrqmShift, regValue, value->frameIrqm[i]));
    }
    return (regValue);
}

/* helper function */
static uint32_t setMonitorIrqsMaskCfgStreams(const CSIRX_MonitorIrqsMaskCfg *value, uint32_t regVal)
{
    uint32_t regValue = regVal;
    uint8_t i;

    /* set Monitor Interrupt Mask for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].lineCntErrorIrqmMask, monitorIrqsMaskCfgDefs[i].lineCntErrorIrqmShift, regValue, value->lineCntErrorIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].fccStopIrqmMask, monitorIrqsMaskCfgDefs[i].fccStopIrqmShift, regValue, value->fccStopIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].fccStartIrqmMask, monitorIrqsMaskCfgDefs[i].fccStartIrqmShift, regValue, value->fccStartIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].lbIrqmMask, monitorIrqsMaskCfgDefs[i].lbIrqmShift, regValue, value->lbIrqm[i]));
        regValue = (CPS_FldWrite(monitorIrqsMaskCfgDefs[i].timerIrqmMask, monitorIrqsMaskCfgDefs[i].timerIrqmShift, regValue, value->timerIrqm[i]));
    }
    return (regValue);
}

/**
 * setter for MonitorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetMonitorIrqsMaskCfg(CSIRX_PrivateData *             pD,
                                     const CSIRX_MonitorIrqsMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetMonitorIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        regVal = setMonitorIrqsMaskCfgStreamsFrm(value, regVal);
        regVal = setMonitorIrqsMaskCfgStreams(value, regVal);

        CPS_REG_WRITE(&pD->regs->monitor_irqs_mask_cfg, regVal);
    }
    return (status);
}

/**
 * getter for ErrorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorIrqsMaskCfg(const CSIRX_PrivateData *pD,
                                   CSIRX_ErrorIrqsMaskCfg * value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetErrorIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Datapath Error Interrupt enable bits for each stream */
        regVal = CPS_REG_READ(&pD->regs->error_irqs_mask_cfg);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->fifoOverflowIrqm[i] = (uint8_t)(CPS_FldRead(errorIrqsMaskCfgDefs[i].fifoOverflowIrqmMask, errorIrqsMaskCfgDefs[i].fifoOverflowIrqmShift, regVal));
        }

        value->spInvalidRcvdIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, SP_INVALID_RCVD_IRQM, regVal));
        value->invalidAccessIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, INVALID_ACCESS_IRQM, regVal));
        value->dataIdIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, DATA_ID_IRQM, regVal));
        value->headerCorrectedEccIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, HEADER_CORRECTED_ECC_IRQM, regVal));
        value->headerEccIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, HEADER_ECC_IRQM, regVal));
        value->payloadCrcIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, PAYLOAD_CRC_IRQM, regVal));
        value->frontFifoOverflowIrqm = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS_MASK_CFG, FRONT_FIFO_OVERFLOW_IRQM, regVal));
    }
    return (status);
}

/**
 * setter for ErrorIrqsMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorIrqsMaskCfg(CSIRX_PrivateData *           pD,
                                   const CSIRX_ErrorIrqsMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetErrorIrqsMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        /* set Datapath Error Interrupt enable bits for each stream */
        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(errorIrqsMaskCfgDefs[i].fifoOverflowIrqmMask, errorIrqsMaskCfgDefs[i].fifoOverflowIrqmShift, regVal, value->fifoOverflowIrqm[i]));
        }

        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, SP_INVALID_RCVD_IRQM, regVal, value->spInvalidRcvdIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, INVALID_ACCESS_IRQM, regVal, value->invalidAccessIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, DATA_ID_IRQM, regVal, value->dataIdIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, HEADER_CORRECTED_ECC_IRQM, regVal, value->headerCorrectedEccIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, HEADER_ECC_IRQM, regVal, value->headerEccIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, PAYLOAD_CRC_IRQM, regVal, value->payloadCrcIrqm));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS_MASK_CFG, FRONT_FIFO_OVERFLOW_IRQM, regVal, value->frontFifoOverflowIrqm));
        CPS_REG_WRITE(&pD->regs->error_irqs_mask_cfg, regVal);
    }
    return (status);
}

/**
 * getter for DphyErrIrqMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyErrIrqMaskCfg(const CSIRX_PrivateData *pD,
                                    CSIRX_DphyErrIrqMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetDphyErrIrqMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->dphy_err_irq_mask_cfg);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->dlErrSotHSIrqm[i] = (uint8_t)(CPS_FldRead(dphyErrIrqMaskCfgDefs[i].dlErrSotHSIrqmMask, dphyErrIrqMaskCfgDefs[i].dlErrSotHSIrqmShift, regVal));
        }
    }
    return (status);
}

/**
 * setter for DphyErrIrqMaskCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyErrIrqMaskCfg(CSIRX_PrivateData *            pD,
                                    const CSIRX_DphyErrIrqMaskCfg *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetDphyErrIrqMaskCfgSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(dphyErrIrqMaskCfgDefs[i].dlErrSotHSIrqmMask, dphyErrIrqMaskCfgDefs[i].dlErrSotHSIrqmShift, regVal, value->dlErrSotHSIrqm[i]));
        }

        CPS_REG_WRITE(&pD->regs->dphy_err_irq_mask_cfg, regVal);
    }
    return (status);
}

/**
 * getter for InfoIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetInfoIrqs(const CSIRX_PrivateData *pD,
                           CSIRX_InfoIrqs *         value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetInfoIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Information type Interrupt status (non-error condition) for each stream */
        regVal = CPS_REG_READ(&pD->regs->info_irqs);

        for (i = 0; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->abortIrq[i] = (uint8_t)(CPS_FldRead(infoIrqsDefs[i].abortIrqMask, infoIrqsDefs[i].abortIrqShift, regVal));
            value->stopIrq[i] = (uint8_t)(CPS_FldRead(infoIrqsDefs[i].stopIrqMask, infoIrqsDefs[i].stopIrqShift, regVal));
        }

        value->spGenericRcvdIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, SP_GENERIC_RCVD_IRQ, regVal));
        value->deskewEntryIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, DESKEW_ENTRY_IRQ, regVal));
        value->eccSparesNonzeroIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, ECC_SPARES_NONZERO_IRQ, regVal));
        value->wakeupIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, WAKEUP_IRQ, regVal));
        value->sleepIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, SLEEP_IRQ, regVal));
        value->lpRcvdIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, LP_RCVD_IRQ, regVal));
        value->spRcvdIrq = (uint8_t)(CPS_FLD_READ(CSIRX__INFO_IRQS, SP_RCVD_IRQ, regVal));
    }
    return (status);
}

/**
 * setter for InfoIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetInfoIrqs(CSIRX_PrivateData *   pD,
                           const CSIRX_InfoIrqs *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetInfoIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        /* set Information type Interrupt status (non-error condition) for each stream */
        for (i = 0; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(infoIrqsDefs[i].abortIrqMask, infoIrqsDefs[i].abortIrqShift, regVal, value->abortIrq[i]));
            regVal = (CPS_FldWrite(infoIrqsDefs[i].stopIrqMask, infoIrqsDefs[i].stopIrqShift, regVal, value->stopIrq[i]));
        }

        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, SP_GENERIC_RCVD_IRQ, regVal, value->spGenericRcvdIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, DESKEW_ENTRY_IRQ, regVal, value->deskewEntryIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, ECC_SPARES_NONZERO_IRQ, regVal, value->eccSparesNonzeroIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, WAKEUP_IRQ, regVal, value->wakeupIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, SLEEP_IRQ, regVal, value->sleepIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, LP_RCVD_IRQ, regVal, value->lpRcvdIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__INFO_IRQS, SP_RCVD_IRQ, regVal, value->spRcvdIrq));
        CPS_REG_WRITE(&pD->regs->info_irqs, regVal);
    }
    return (status);
}

/* helper function */
static void getMonitorIrqsStreamsFrm(CSIRX_MonitorIrqs *value, uint32_t regVal)
{
    uint8_t i;

    /* get Information Interrupt status for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        value->lineCntErrorIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].lineCntErrorIrqMask, monitorIrqsDefs[i].lineCntErrorIrqShift, regVal));
        value->frameMismatchIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].frameMismatchIrqMask, monitorIrqsDefs[i].frameMismatchIrqShift, regVal));
        value->frameCntErrorIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].frameCntErrorIrqMask, monitorIrqsDefs[i].frameCntErrorIrqShift, regVal));
    }
    return;
}

/* helper function*/
static void getMonitorIrqsStreams(CSIRX_MonitorIrqs *value, uint32_t regVal)
{
    uint8_t i;

    /* get Information Interrupt status for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        value->fccStopIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].fccStopIrqMask, monitorIrqsDefs[i].fccStopIrqShift, regVal));
        value->fccStartIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].fccStartIrqMask, monitorIrqsDefs[i].fccStartIrqShift, regVal));
        value->frameIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].frameIrqMask, monitorIrqsDefs[i].frameIrqShift, regVal));
        value->lbIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].lbIrqMask, monitorIrqsDefs[i].lbIrqShift, regVal));
        value->timerIrq[i] = (uint8_t)(CPS_FldRead(monitorIrqsDefs[i].timerIrqMask, monitorIrqsDefs[i].timerIrqShift, regVal));
    }
    return;
}

/**
 * getter for MonitorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetMonitorIrqs(const CSIRX_PrivateData *pD,
                              CSIRX_MonitorIrqs *      value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetMonitorIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->monitor_irqs);
        getMonitorIrqsStreamsFrm(value, regVal);
        getMonitorIrqsStreams(value, regVal);
    }
    return (status);
}

/* helper function */
static uint32_t setMonitorIrqsStreamsFrm(const CSIRX_MonitorIrqs *value, uint32_t regVal)
{
    uint32_t regValue = regVal;
    uint8_t i;

    /* set Information Interrupt status for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].frameMismatchIrqMask, monitorIrqsDefs[i].frameMismatchIrqShift, regValue, value->frameMismatchIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].frameCntErrorIrqMask, monitorIrqsDefs[i].frameCntErrorIrqShift, regValue, value->frameCntErrorIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].frameIrqMask, monitorIrqsDefs[i].frameIrqShift, regValue, value->frameIrq[i]));
    }
    return (regValue);
}

/* helper function */
static uint32_t setMonitorIrqsStreams(const CSIRX_MonitorIrqs *value, uint32_t regVal)
{
    uint32_t regValue = regVal;
    uint8_t i;

    /* set Information Interrupt status for each stream */
    for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].lineCntErrorIrqMask, monitorIrqsDefs[i].lineCntErrorIrqShift, regValue, value->lineCntErrorIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].fccStopIrqMask, monitorIrqsDefs[i].fccStopIrqShift, regValue, value->fccStopIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].fccStartIrqMask, monitorIrqsDefs[i].fccStartIrqShift, regValue, value->fccStartIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].lbIrqMask, monitorIrqsDefs[i].lbIrqShift, regValue, value->lbIrq[i]));
        regValue = (CPS_FldWrite(monitorIrqsDefs[i].timerIrqMask, monitorIrqsDefs[i].timerIrqShift, regValue, value->timerIrq[i]));
    }
    return (regValue);
}

/**
 * setter for MonitorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetMonitorIrqs(CSIRX_PrivateData *      pD,
                              const CSIRX_MonitorIrqs *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetMonitorIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        regVal = setMonitorIrqsStreamsFrm(value, regVal);
        regVal = setMonitorIrqsStreams(value, regVal);

        CPS_REG_WRITE(&pD->regs->monitor_irqs, regVal);
    }
    return (status);
}

/**
 * getter for ErrorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorIrqs(const CSIRX_PrivateData *pD,
                            CSIRX_ErrorIrqs *        value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetErrorIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Datapath Error Interrupt status */
        regVal = CPS_REG_READ(&pD->regs->error_irqs);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->fifoOverflowIrq[i] = (uint8_t)(CPS_FldRead(errorIrqsDefs[i].fifoOverflowIrqMask, errorIrqsDefs[i].fifoOverflowIrqShift, regVal));
        }

        value->spInvalidRcvdIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, SP_INVALID_RCVD_IRQ, regVal));
        value->invalidAccessIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, INVALID_ACCESS_IRQ, regVal));
        value->dataIdIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, DATA_ID_IRQ, regVal));
        value->headerCorrectedEccIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, HEADER_CORRECTED_ECC_IRQ, regVal));
        value->headerEccIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, HEADER_ECC_IRQ, regVal));
        value->payloadCrcIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, PAYLOAD_CRC_IRQ, regVal));
        value->frontFifoOverflowIrq = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_IRQS, FRONT_FIFO_OVERFLOW_IRQ, regVal));
    }
    return (status);
}

/**
 * setter for ErrorIrqs
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetErrorIrqs(CSIRX_PrivateData *    pD,
                            const CSIRX_ErrorIrqs *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetErrorIrqsSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        /* set Datapath Error Interrupt status */
        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(errorIrqsDefs[i].fifoOverflowIrqMask, errorIrqsDefs[i].fifoOverflowIrqShift, regVal, value->fifoOverflowIrq[i]));
        }

        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, SP_INVALID_RCVD_IRQ, regVal, value->spInvalidRcvdIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, INVALID_ACCESS_IRQ, regVal, value->invalidAccessIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, DATA_ID_IRQ, regVal, value->dataIdIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, HEADER_CORRECTED_ECC_IRQ, regVal, value->headerCorrectedEccIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, HEADER_ECC_IRQ, regVal, value->headerEccIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, PAYLOAD_CRC_IRQ, regVal, value->payloadCrcIrq));
        regVal = (CPS_FLD_WRITE(CSIRX__ERROR_IRQS, FRONT_FIFO_OVERFLOW_IRQ, regVal, value->frontFifoOverflowIrq));
        CPS_REG_WRITE(&pD->regs->error_irqs, regVal);
    }
    return (status);
}

/**
 * getter for DphyErrStatusIrq
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyErrStatusIrq(const CSIRX_PrivateData *pD,
                                   CSIRX_DphyErrStatusIrq * value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetDphyErrStatusIrqSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->dphy_err_status_irq);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->dlErrSotHSIrq[i] = (uint8_t)(CPS_FldRead(dphyErrStatusIrqDefs[i].dlErrSotHSIrqMask, dphyErrStatusIrqDefs[i].dlErrSotHSIrqShift, regVal));
        }
    }
    return (status);
}

/**
 * setter for DphyErrStatusIrq
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyErrStatusIrq(CSIRX_PrivateData *           pD,
                                   const CSIRX_DphyErrStatusIrq *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetDphyErrStatusIrqSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(dphyErrStatusIrqDefs[i].dlErrSotHSIrqMask, dphyErrStatusIrqDefs[i].dlErrSotHSIrqShift, regVal, value->dlErrSotHSIrq[i]));
        }

        CPS_REG_WRITE(&pD->regs->dphy_err_status_irq, regVal);
    }
    return (status);
}

/**
 * getter for DphyLaneControl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyLaneControl(const CSIRX_PrivateData *pD,
                                  CSIRX_DphyLaneControl *  value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetDphyLaneControlSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->dphy_lane_control);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->dlEnable[i] = (uint8_t)(CPS_FldRead(dphyLaneControlDefs[i].dlEnableMask, dphyLaneControlDefs[i].dlEnableShift, regVal));
            value->dlReset[i] = (uint8_t)(CPS_FldRead(dphyLaneControlDefs[i].dlResetMask, dphyLaneControlDefs[i].dlResetShift, regVal));
        }

        value->clEnable = (uint8_t)(CPS_FLD_READ(CSIRX__DPHY_LANE_CONTROL, CL_ENABLE, regVal));
        value->clReset = (uint8_t)(CPS_FLD_READ(CSIRX__DPHY_LANE_CONTROL, CL_RESET, regVal));
    }
    return (status);
}

/**
 * setter for DphyLaneControl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetDphyLaneControl(CSIRX_PrivateData *          pD,
                                  const CSIRX_DphyLaneControl *value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;
    uint8_t i;

    /* check parameters */
    if (CSIRX_SetDphyLaneControlSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            regVal = (CPS_FldWrite(dphyLaneControlDefs[i].dlEnableMask, dphyLaneControlDefs[i].dlEnableShift, regVal, value->dlEnable[i]));
            regVal = (CPS_FldWrite(dphyLaneControlDefs[i].dlResetMask, dphyLaneControlDefs[i].dlResetShift, regVal, value->dlReset[i]));
        }

        regVal = (CPS_FLD_WRITE(CSIRX__DPHY_LANE_CONTROL, CL_ENABLE, regVal, value->clEnable));
        regVal = (CPS_FLD_WRITE(CSIRX__DPHY_LANE_CONTROL, CL_RESET, regVal, value->clReset));
        CPS_REG_WRITE(&((CSIRX_PrivateData *)pD)->regs->dphy_lane_control, regVal);
    }
    return (status);
}

/* helper function */
static const streamsDefs* getDphyStatusDlStopState(uint8_t streamNo) {

    /* get mask and shift values for given stream */
    static const streamsDefs dlStopStateDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = CSIRX__DPHY_STATUS__DL0_STOPSTATE_MASK,
        [0U].shift = CSIRX__DPHY_STATUS__DL0_STOPSTATE_SHIFT,
        [1U].mask = CSIRX__DPHY_STATUS__DL1_STOPSTATE_MASK,
        [1U].shift = CSIRX__DPHY_STATUS__DL1_STOPSTATE_SHIFT,
        [2U].mask = CSIRX__DPHY_STATUS__DL2_STOPSTATE_MASK,
        [2U].shift = CSIRX__DPHY_STATUS__DL2_STOPSTATE_SHIFT,
        [3U].mask = CSIRX__DPHY_STATUS__DL3_STOPSTATE_MASK,
        [3U].shift = CSIRX__DPHY_STATUS__DL3_STOPSTATE_SHIFT,
    };

    return (&dlStopStateDefsArr[streamNo]);
}

/* helper function */
static const streamsDefs* getDphyStatusDlULPSActiveNot(uint8_t streamNo) {

    /* get mask and shift values for given stream */
    static const streamsDefs dlULPSActiveNotDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = CSIRX__DPHY_STATUS__DL0_ULPSACTIVENOT_MASK,
        [0U].shift = CSIRX__DPHY_STATUS__DL0_ULPSACTIVENOT_SHIFT,
        [1U].mask = CSIRX__DPHY_STATUS__DL1_ULPSACTIVENOT_MASK,
        [1U].shift = CSIRX__DPHY_STATUS__DL1_ULPSACTIVENOT_SHIFT,
        [2U].mask = CSIRX__DPHY_STATUS__DL2_ULPSACTIVENOT_MASK,
        [2U].shift = CSIRX__DPHY_STATUS__DL2_ULPSACTIVENOT_SHIFT,
        [3U].mask = CSIRX__DPHY_STATUS__DL3_ULPSACTIVENOT_MASK,
        [3U].shift = CSIRX__DPHY_STATUS__DL3_ULPSACTIVENOT_SHIFT,
    };

    return (&dlULPSActiveNotDefsArr[streamNo]);
}

/* helper function */
static const streamsDefs* getDphyStatusDlRxULPSEsc(uint8_t streamNo) {

    /* get mask and shift values for given stream */
    static const streamsDefs dlRxULPSEscDefsArr[CSIRX_MAX_NUM_OF_STREAMS] = {
        [0U].mask = CSIRX__DPHY_STATUS__DL0_RXULPSESC_MASK,
        [0U].shift = CSIRX__DPHY_STATUS__DL0_RXULPSESC_SHIFT,
        [1U].mask = CSIRX__DPHY_STATUS__DL1_RXULPSESC_MASK,
        [1U].shift = CSIRX__DPHY_STATUS__DL1_RXULPSESC_SHIFT,
        [2U].mask = CSIRX__DPHY_STATUS__DL2_RXULPSESC_MASK,
        [2U].shift = CSIRX__DPHY_STATUS__DL2_RXULPSESC_SHIFT,
        [3U].mask = CSIRX__DPHY_STATUS__DL3_RXULPSESC_MASK,
        [3U].shift = CSIRX__DPHY_STATUS__DL3_RXULPSESC_SHIFT,
    };

    return (&dlRxULPSEscDefsArr[streamNo]);
}

/**
 * getter for DphyStatus
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetDphyStatus(const CSIRX_PrivateData *pD,
                             CSIRX_DphyStatus *       value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint8_t i;

    /* check parameters */
    if (CSIRX_GetDphyStatusSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get DPHY Clock and Data Lane mode status */
        regVal = CPS_REG_READ(&pD->regs->dphy_status);

        for (i = 0U; i < (uint8_t)CSIRX_MAX_NUM_OF_STREAMS; ++i) {
            value->dlStopState[i] = (uint8_t)(CPS_FldRead(getDphyStatusDlStopState(i)->mask, getDphyStatusDlStopState(i)->shift, regVal));
            value->dlULPSActiveNot[i] = (uint8_t)(CPS_FldRead(getDphyStatusDlULPSActiveNot(i)->mask, getDphyStatusDlULPSActiveNot(i)->shift, regVal));
            value->dlRxULPSEsc[i] = (uint8_t)(CPS_FldRead(getDphyStatusDlRxULPSEsc(i)->mask, getDphyStatusDlRxULPSEsc(i)->shift, regVal));
        }

        value->cl_StopState = (uint8_t)(CPS_FLD_READ(CSIRX__DPHY_STATUS, CL_STOPSTATE, regVal));
        value->cl_ULPSActiveNot = (uint8_t)(CPS_FLD_READ(CSIRX__DPHY_STATUS, CL_ULPSACTIVENOT, regVal));
        value->cl_RxULPSClkNot = (uint8_t)(CPS_FLD_READ(CSIRX__DPHY_STATUS, CL_RXULPSCLKNOT, regVal));
    }
    return (status);
}

/**
 * getter for IntegrationDebug
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetIntegrationDebug(const CSIRX_PrivateData *pD,
                                   CSIRX_IntegrationDebug * value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetIntegrationDebugSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->integration_debug);
        value->protFsmState = (uint8_t)(CPS_FLD_READ(CSIRX__INTEGRATION_DEBUG, PROT_FSM_STATE, regVal));
        value->protVc = (uint8_t)(CPS_FLD_READ(CSIRX__INTEGRATION_DEBUG, PROT_VC, regVal));
        value->protDt = (uint8_t)(CPS_FLD_READ(CSIRX__INTEGRATION_DEBUG, PROT_DT, regVal));
        value->protWordCount = (uint16_t)(CPS_FLD_READ(CSIRX__INTEGRATION_DEBUG, PROT_WORD_COUNT, regVal));
    }
    return (status);
}

/**
 * getter for ErrorDebug
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetErrorDebug(const CSIRX_PrivateData *pD,
                             CSIRX_ErrorDebug *       value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetErrorDebugSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->error_debug);
        value->dataField = (uint16_t)(CPS_FLD_READ(CSIRX__ERROR_DEBUG, DATA_FIELD, regVal));
        value->vc = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_DEBUG, VC, regVal));
        value->dt = (uint8_t)(CPS_FLD_READ(CSIRX__ERROR_DEBUG, DT, regVal));
    }
    return (status);
}

/**
 * getter for testGeneric
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetTestGeneric(const CSIRX_PrivateData *pD,
                              CSIRX_TestGeneric *      value)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetTestGenericSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_REG_READ(&pD->regs->test_generic);
        value->ctrl = (uint16_t)(CPS_FLD_READ(CSIRX__TEST_GENERIC, CTRL, regVal));
        value->status = (uint16_t)(CPS_FLD_READ(CSIRX__TEST_GENERIC, STATUS, regVal));
    }
    return (status);
}

/**
 * getter for StreamCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamCtrl(const CSIRX_PrivateData *pD,
                             CSIRX_StreamCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    status = CSIRX_GetStreamCtrlSF(pD, value, streamNo);
    if (status != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get settings for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_ctrl);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_ctrl);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_ctrl);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_ctrl);
        }

        value->softRst = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CTRL, SOFT_RST, regVal);
    }
    return (status);
}

/**
 * setter for StreamCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamCtrl(const CSIRX_PrivateData *pD,
                             const CSIRX_StreamCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamCtrlSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CTRL, SOFT_RST, regVal, value->softRst);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CTRL, ABORT, regVal, value->abrt);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CTRL, STOP, regVal, value->stop);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CTRL, START, regVal, value->start);

        /* set configuration for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_ctrl, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_ctrl, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_ctrl, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_ctrl, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamStatus
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamStatus(const CSIRX_PrivateData *pD,
                               CSIRX_StreamStatus *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamStatusSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Controller Status for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_status);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_status);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_status);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_status);
        }

        value->running = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_STATUS, RUNNING, regVal);
        value->readyState = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_STATUS, READY_STATE, regVal);
        value->streamFsm = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_STATUS, STREAM_FSM, regVal);
        value->protocolFsm = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_STATUS, PROTOCOL_FSM, regVal);
    }
    return (status);
}

/**
 * getter for StreamCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamCfg(const CSIRX_PrivateData *pD,
                            CSIRX_StreamCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Controller Data pixel outputs configuration for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_cfg);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_cfg);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_cfg);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_cfg);
        }

        /* get common values for Controller Data pixel outputs configuration */
        value->fifoFill = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, FIFO_FILL, regVal);
        value->bppBypass = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, BPP_BYPASS, regVal);
        value->fifoMode = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, FIFO_MODE, regVal);
        value->numPixels = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, NUM_PIXELS, regVal);
        value->lsLeMode = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, LS_LE_MODE, regVal);
        value->interfaceMode = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_CFG, INTERFACE_MODE, regVal);
    }
    return (status);
}

/* helper function */
static uint32_t setStreamCfgReg(const CSIRX_StreamCfg *value,
                                uint32_t               regValue)
{
    uint32_t regVal = regValue;

    /* set common values for Controller Data pixel outputs configuration */
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, FIFO_FILL, regVal, value->fifoFill);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, BPP_BYPASS, regVal, value->bppBypass);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, FIFO_MODE, regVal, value->fifoMode);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, NUM_PIXELS, regVal, value->numPixels);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, LS_LE_MODE, regVal, value->lsLeMode);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_CFG, INTERFACE_MODE, regVal, value->interfaceMode);

    return (regVal);
}

/**
 * setter for StreamCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamCfg(const CSIRX_PrivateData *pD,
                            const CSIRX_StreamCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        regVal = setStreamCfgReg(value, regVal);

        /* set Controller Data pixel outputs configuration for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_cfg, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_cfg, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_cfg, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_cfg, regVal);
        }
    }
    return (status);
}

/* helper function */
static void getStreamDataCfgReg(CSIRX_StreamDataCfg *value, uint32_t regVal)
{
    /* get common fields for Stream Controller Data outputs configuration */
    value->vcSelect = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_DATA_CFG, VC_SELECT, regVal);
    value->enableDt1 = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_DATA_CFG, ENABLE_DT1, regVal);
    value->datatypeSelect1 = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_DATA_CFG, DATATYPE_SELECT1, regVal);
    value->enableDt0 = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_DATA_CFG, ENABLE_DT0, regVal);
    value->datatypeSelect0 = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_DATA_CFG, DATATYPE_SELECT0, regVal);

    return;
}

/**
 * getter for StreamDataCfgl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamDataCfg(const CSIRX_PrivateData *pD,
                                CSIRX_StreamDataCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamDataCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Controller Data outputs configuration for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_data_cfg);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_data_cfg);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_data_cfg);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_data_cfg);
        }

        getStreamDataCfgReg(value, regVal);
    }
    return (status);
}

/* helper function */
static uint32_t setStreamDataCfgReg(const CSIRX_StreamDataCfg *value,
                                    uint32_t                   regValue)
{
    uint32_t regVal = regValue;

    /* set common fields for Stream Controller Data outputs configuration */
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_DATA_CFG, VC_SELECT, regVal, value->vcSelect);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_DATA_CFG, ENABLE_DT1, regVal, value->enableDt1);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_DATA_CFG, DATATYPE_SELECT1, regVal, value->datatypeSelect1);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_DATA_CFG, ENABLE_DT0, regVal, value->enableDt0);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_DATA_CFG, DATATYPE_SELECT0, regVal, value->datatypeSelect0);

    return (regVal);
}

/**
 * setter for StreamDataCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamDataCfg(const CSIRX_PrivateData *pD,
                                const CSIRX_StreamDataCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamDataCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else if ((value->vcSelect > 0xFU) && (pD->deviceConfig.vcxConfig == 0U)) {
        status = CDN_EINVAL;
    } else {

        regVal = setStreamDataCfgReg(value, regVal);

        /* set Controller Data outputs configuration for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_data_cfg, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_data_cfg, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_data_cfg, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_data_cfg, regVal);
        }
    }
    return (status);
}

/* helper function */
static void getStreamMonitorCtrlReg(CSIRX_StreamMonitorCtrl *value,
                                    uint32_t                 regVal)
{
    /* get Stream Monitor configuration common values */
    value->frameLength = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, FRAME_LENGTH, regVal);
    value->frameMonEn = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, FRAME_MON_EN, regVal);
    value->frameMonVc = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, FRAME_MON_VC, regVal);
    value->timerEof = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, TIMER_EOF, regVal);
    value->timerEn = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, TIMER_EN, regVal);
    value->timerVc = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, TIMER_VC, regVal);
    value->lbEn = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, LB_EN, regVal);
    value->lbVc = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_CTRL, LB_VC, regVal);

    return;
}

/**
 * getter for StreamMonitorCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorCtrl(const CSIRX_PrivateData *pD,
                                    CSIRX_StreamMonitorCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamMonitorCtrlSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Stream Monitor configuration for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_monitor_ctrl);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_monitor_ctrl);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_monitor_ctrl);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_monitor_ctrl);
        }

        getStreamMonitorCtrlReg(value, regVal);
    }
    return (status);
}

/* helper function */
static uint32_t setStreamMonitorCtrlFrame(const CSIRX_StreamMonitorCtrl *value, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* set common parameters for Stream Monitor configuration */
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, FRAME_LENGTH, regVal, value->frameLength);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, FRAME_MON_EN, regVal, value->frameMonEn);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, FRAME_MON_VC, regVal, value->frameMonVc);

    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, TIMER_EOF, regVal, value->timerEof);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, TIMER_EN, regVal, value->timerEn);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, TIMER_VC, regVal, value->timerVc);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, LB_EN, regVal, value->lbEn);
    regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_CTRL, LB_VC, regVal, value->lbVc);

    return (regVal);
}

/**
 * setter for StreamMonitorCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamMonitorCtrl(const CSIRX_PrivateData *pD,
                                    const CSIRX_StreamMonitorCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamMonitorCtrlSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = setStreamMonitorCtrlFrame(value, regVal);

        /* set Stream Monitor configuration for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_monitor_ctrl, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_monitor_ctrl, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_monitor_ctrl, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_monitor_ctrl, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamMonitorFrame
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorFrame(const CSIRX_PrivateData *pD,
                                     CSIRX_StreamMonitorFrame *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamMonitorFrameSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Stream Monitor Frame for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_monitor_ctrl);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_monitor_ctrl);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_monitor_ctrl);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_monitor_ctrl);
        }

        value->packetSize = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_FRAME, PACKET_SIZE, regVal);
        value->nb = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_FRAME, NB, regVal);
    }
    return (status);
}

/**
 * getter for StreamMonitorLb
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamMonitorLb(const CSIRX_PrivateData *pD,
                                  CSIRX_StreamMonitorLb *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamMonitorLbSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Stream Monitor Line for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_monitor_lb);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_monitor_lb);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_monitor_lb);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_monitor_lb);
        }

        value->lineCount = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_LB, LINE_COUNT, regVal);
        value->byteCount = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_MONITOR_LB, BYTE_COUNT, regVal);
    }
    return (status);
}

/**
 * setter for StreamMonitorLb
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamMonitorLb(const CSIRX_PrivateData *pD,
                                  const CSIRX_StreamMonitorLb *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamMonitorLbSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {

        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_LB, LINE_COUNT, regVal, value->lineCount);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_MONITOR_LB, BYTE_COUNT, regVal, value->byteCount);

        /* set Stream Monitor Line for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_monitor_lb, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_monitor_lb, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_monitor_lb, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_monitor_lb, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamTimer
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamTimer(const CSIRX_PrivateData *pD,
                              CSIRX_StreamTimer *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamTimerSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Stream Timer for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_timer);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_timer);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_timer);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_timer);
        }

        value->count = CPS_FLD_READ(CSIRX__STREAM0_TIMER, COUNT, regVal);
    }
    return (status);
}

/**
 * setter for StreamTimer
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamTimer(const CSIRX_PrivateData *pD,
                              const CSIRX_StreamTimer *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamTimerSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_TIMER, COUNT, regVal, value->count);

        /* set Stream Timer for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_timer, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_timer, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_timer, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_timer, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamFccCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFccCfg(const CSIRX_PrivateData *pD,
                               CSIRX_StreamFccCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamFccCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Frame Capture Control configuration for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_fcc_cfg);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_fcc_cfg);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_fcc_cfg);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_fcc_cfg);
        }

        /* set common values for each stream */
        value->frameCountStop = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_FCC_CFG, FRAME_COUNT_STOP, regVal);
        value->frameCountStart = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_FCC_CFG, FRAME_COUNT_START, regVal);
    }
    return (status);
}

/**
 * setter for StreamFccCfg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFccCfg(const CSIRX_PrivateData *pD,
                               const CSIRX_StreamFccCfg *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if (CSIRX_SetStreamFccCfgSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* set common values for each stream */
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_FCC_CFG, FRAME_COUNT_STOP, regVal, value->frameCountStop);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_FCC_CFG, FRAME_COUNT_START, regVal, value->frameCountStart);

        /* set Frame Capture Control configuration for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_fcc_cfg, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_fcc_cfg, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_fcc_cfg, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_fcc_cfg, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamFccCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFccCtrl(const CSIRX_PrivateData *pD,
                                CSIRX_StreamFccCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamFccCtrlSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get Frame Capture Counter control for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_fcc_ctrl);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_fcc_ctrl);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_fcc_ctrl);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_fcc_ctrl);
        }

        /* take common for each stream */
        value->frameCounter = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_FCC_CTRL, FRAME_COUNTER, regVal);
        value->fccVc = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_FCC_CTRL, FCC_VC, regVal);
        value->fccEn = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_FCC_CTRL, FCC_EN, regVal);
    }
    return (status);
}

/**
 * setter for StreamFccCtrl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFccCtrl(const CSIRX_PrivateData *pD,
                                const CSIRX_StreamFccCtrl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CSIRX_SetStreamFccCtrlSF(pD, value, streamNo) != CDN_EOK)
        || (value->frameCounter != 0U)) {
        status = CDN_EINVAL;
    } else {
        /* build value common for each stream */
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_FCC_CTRL, FCC_VC, regVal, value->fccVc);
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_FCC_CTRL, FCC_EN, regVal, value->fccEn);

        /* set Frame Capture Counter control for given stream */
        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_fcc_ctrl, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_fcc_ctrl, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_fcc_ctrl, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_fcc_ctrl, regVal);
        }
    }
    return (status);
}

/**
 * getter for StreamFifoFillLvl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_GetStreamFifoFillLvl(const CSIRX_PrivateData *pD,
                                    CSIRX_StreamFifoFillLvl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CSIRX_GetStreamFifoFillLvlSF(pD, value, streamNo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get fill level for given stream */
        if (streamNo == 0U) {
            regVal = CPS_REG_READ(&pD->regs->stream0_fifo_fill_lvl);
        }
        else if (streamNo == 1U) {
            regVal = CPS_REG_READ(&pD->regs->stream1_fifo_fill_lvl);
        }
        else if (streamNo == 2U) {
            regVal = CPS_REG_READ(&pD->regs->stream2_fifo_fill_lvl);
        }
        else {
            regVal = CPS_REG_READ(&pD->regs->stream3_fifo_fill_lvl);
        }

        value->mode = (uint8_t)CPS_FLD_READ(CSIRX__STREAM0_FIFO_FILL_LVL, MODE, regVal);
        value->count = (uint16_t)CPS_FLD_READ(CSIRX__STREAM0_FIFO_FILL_LVL, COUNT, regVal);
    }
    return (status);
}

/**
 * setter for StreamFifoFillLvl
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSIRX_SetStreamFifoFillLvl(const CSIRX_PrivateData *pD,
                                    const CSIRX_StreamFifoFillLvl *value, uint32_t streamNo)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CSIRX_SetStreamFifoFillLvlSF(pD, value, streamNo) != CDN_EOK)
        || (value->count != 0U)) {
        status = CDN_EINVAL;
    } else {
        /* set fill level for given stream */
        regVal = CPS_FLD_WRITE(CSIRX__STREAM0_FIFO_FILL_LVL, MODE, regVal, value->mode);

        if (streamNo == 0U) {
            CPS_REG_WRITE(&pD->regs->stream0_fifo_fill_lvl, regVal);
        }
        else if (streamNo == 1U) {
            CPS_REG_WRITE(&pD->regs->stream1_fifo_fill_lvl, regVal);
        }
        else if (streamNo == 2U) {
            CPS_REG_WRITE(&pD->regs->stream2_fifo_fill_lvl, regVal);
        }
        else {
            CPS_REG_WRITE(&pD->regs->stream3_fifo_fill_lvl, regVal);
        }
    }
    return (status);
}

/**
 * Driver ISR. Platform-specific code is responsible for ensuring this
 * gets called when the corresponding hardware's interrupt is
 * asserted. The driver's ISR will not attempt to lock any locks, but
 * will perform client callbacks. If the client wishes to defer
 * processing to non-interrupt time, it is responsible for doing so.
 * Should not be called before init.
 * @param[in] pD Pointer to the private data initialized by init
 */
void CSIRX_Isr(CSIRX_PrivateData *pD)
{
    /* check parameters */
    if (CSIRX_IsrSF(pD) == CDN_EOK) {
        CSIRX_InfoIrqs info;
        CSIRX_ErrorIrqs error;
        CSIRX_DphyErrStatusIrq dphy;
        CSIRX_MonitorIrqs monitor;
        uint32_t regVal;

        /* Read various interupt registers for int source  */
        /* Info interrupts */
        regVal = CPS_REG_READ(&pD->regs->info_irqs);
        if (regVal != 0U) {
            (void) CSIRX_GetInfoIrqs(pD, &info);
            pD->infoHandler(pD,&info);
        }
        /* Controller Error interrupts */
        regVal = CPS_REG_READ(&pD->regs->error_irqs);
        if (regVal != 0U) {
            (void) CSIRX_GetErrorIrqs(pD, &error);
            pD->errorHandler(pD, &error);
        }
        /* Monitor interrupts */
        regVal = CPS_REG_READ(&pD->regs->monitor_irqs);
        if (regVal != 0U) {
            (void) CSIRX_GetMonitorIrqs(pD, &monitor);
            pD->monitorHandler(pD, &monitor);
        }
        /* DPHY Error interrupts */
        regVal = CPS_REG_READ(&pD->regs->dphy_err_status_irq);
        if (regVal != 0U) {
            (void) CSIRX_GetDphyErrStatusIrq(pD, &dphy);
            pD->dphyErrorHandler(pD, &dphy);
        }
    }
}

/**
 * Retrieves ASF information from CSIRX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return CDN_EINVAL If pD or asfInfo is NULL.
 * @return CDN_ENOTSUP If ASF is not available.
 * @return CDN_EOK On success.
 */
uint32_t CSIRX_GetAsfInfo(const CSIRX_PrivateData *pD, CSIRX_AsfInfo* asfInfo)
{
    uint32_t status = CDN_EOK;

    /* check parameters */
    if (CSIRX_GetAsfInfoSF(pD, asfInfo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* Get address of ASF module */
        if (pD->deviceConfig.asfConfig == 1U) {
            asfInfo->regBase = &(pD->regs->asf_int_status);
        } else {
            status = CDN_ENOTSUP;
        }
    }
    return status;
}
