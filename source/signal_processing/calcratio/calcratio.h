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

/**
 *  \defgroup SW_CALCRATIO_MODULE APIs for CALCRATIO
 *  \ingroup SIGNAL_PROCESSING_MODULE
 *
 *  This module contains APIs to program and use the CALCRATIO module.
 *
 *  @{
 */

 /**
 *  \file calcratio.h
 *
 *  \brief CALCRATIO API/interface file.
 */

#ifndef CALCRATIO_H
#define CALCRATIO_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/AddrTranslateP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Length of the first-stage moving average filter used in ratio smoothing
 *
 * CALCRATIO_MA1_LENGTH: Defines the window size (1024 samples) for the coarse
 * moving average filter. This large window effectively suppresses high-frequency
 * jitter in the measured TX/RX sample ratio before finer filtering.
 */
 #define CALCRATIO_MA1_LENGTH   (1024U)
/**
 * \brief Length of the second-stage moving average filter for refined smoothing.
 *
 * CALCRATIO_MA2_LENGTH: Defines the window size (128 samples) for the secondary
 * moving average filter. Applied after the first stage to further reduce residual
 * noise and provide a stable, smooth ratio value for resampling control.
 */
 #define CALCRATIO_MA2_LENGTH   (128U)

/* ========================================================================== */
/*                             Structure Definitions                          */
/* ========================================================================== */

/**
 * \brief CALCRATIO Parameters
 *
 * The CALCRATIO algorithm estimates the ratio between an input fs and an
 * output fs (e.g., sample-rate conversion, clock scaling, etc.) by
 * measuring timing periods and smoothing them with a **two-stage moving-average
 * filter**.  This structure holds:
 *
 * 1. **User-provided sample rates** (`fsi`, `fso`) – the nominal input and
 *     output rates set by the user.
 * 2. **Target ratio** – the ideal `fso / fsi` ratio computed once at
 *     initialization.
 * 3. **Actual ratio** – the smoothed ratio produced on every execution of
 *     `calcRatio_exec()`.  It converges toward the target ratio as the
 *     filters settle.
 * 4. **Two-stage moving-average state** – separate buffers, sums, and
 *     pointers for the first-stage (coarse) and second-stage (fine) filters.
 * 5. **Auxiliary counters** – used to manage filter updates and to discard
 *     the first (often noisy) measurement.
 *
 * The first stage (`MA1`) uses a long window (`CALCRATIO_MA1_LENGTH = 1024`)
 * to heavily dampen jitter.  Its output feeds the second stage (`MA2`),
 * which uses a shorter window (`CALCRATIO_MA2_LENGTH = 128`) for finer
 * smoothing.  The final smoothed period yields `actual_ratio`.
 */
typedef struct
{
    /** \brief Input sample rate set by the user (Hz). */
    float     fsi;
    /** \brief Output sample rate set by the user (Hz). */
    float     fso;
    /**
     * \brief Target ratio produced by \ref calcRatio_init.
     *
     * Computed as <tt>target_ratio = (double)fso / (double)fsi</tt>.
     * This is the ideal ratio the algorithm tries to track.
     */
    double  target_ratio;
    /**
     * \brief Actual ratio produced by \ref calcRatio_exec on each call.
     *
     * Starts near zero and converges to `target_ratio` as the two-stage
     * moving-average filters accumulate enough samples.
     */
    double  actual_ratio;
    /** \brief Accumulator for the first-stage moving-average sum. */
    double  movingAvg1Sum;
    /**
     * \brief Circular buffer holding the most recent period measurements
     *        for the **first-stage** moving-average filter.
     *
     * Size = \ref CALCRATIO_MA1_LENGTH (1024 entries).  Each entry stores
     * the measured period (in seconds) between successive input events.
     */
    double  capture_history[CALCRATIO_MA1_LENGTH];
    /**
     * \brief Pointer into `capture_history` indicating where the next
     *        period sample will be written.
     *
     * Updated in a wrap-around fashion; the filter logic uses
     * <tt>(P2_capture_hist - capture_history)</tt> as the current index.
     */
    double *P2_capture_hist;
    /** \brief Accumulator for the second-stage moving-average sum. */
    double  movingAvg2Sum;
    /**
     * \brief Circular buffer for the **second-stage** moving-average filter.
     *
     * Holds the per-sample output of the first-stage filter.
     * Size = \ref CALCRATIO_MA2_LENGTH (128 entries).
     */
    double  capture2_history[CALCRATIO_MA2_LENGTH];
    /**
     * \brief Pointer into `capture2_history` for the next write location.
     *
     * Behaves identically to `P2_capture_hist` but for the second stage.
     */
    double *P2_capture2_hist;
    /**
     * \brief Counter for the graduated (incremental) update of the second-stage
     *        average.
     *
     * When the first-stage filter produces a new value, this counter is
     * incremented until it reaches `CALCRATIO_MA2_LENGTH`; only then is the
     * oldest entry subtracted from `movingAvg2Sum`.  This implements a
     * “graduated average” that avoids abrupt changes when the buffer wraps.
     */
    uint32_t  movingAvg2Count;
    /**
     * \brief One-shot flag to discard the very first captured period.
     *
     * The first measurement is often spurious (e.g., due to startup
     * transients).  Setting `one_shot = 1` causes `calcRatio_exec()` to
     * ignore it and clear the flag immediately afterward.
     */
    uint16_t  one_shot;
} CalcRatio_t;

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Initializes the ratio calculation module for ASRC (Asynchronous Sample Rate Converter)
 *        with input and output sample rates.
 *
 * This function configures the CALCRATIO module by setting the input and output sample rates,
 * computing the target ratio (`fso / fsi`), and resetting all internal filter states
 * (moving average buffers, pointers, sums, and counters) to prepare for accurate ratio tracking.
 *
 * \param calcRatioInstance     Pointer to the \ref CalcRatio_t instance to initialize.
 * \param [in] sampleRateIn     Input sampling frequency in Hz.
 * \param [in] sampleRateOut    Output sampling frequency in Hz.
 *
 * \return                      The computed target ratio (same value written to *targetRatio).
 *
 */

int32_t calcRatio_init(
    CalcRatio_t *calcRatioInstance,
    float sampleRateIn,
    float sampleRateOut
);


/**
 * \brief Executes the CALCRATIO algorithm to derive and update the smoothed actual sample rate ratio.
 *
 * This function must not be called from an ISR context because it uses semaphores for synchronization.
 *
 * It performs one iteration of the two-stage moving average filter
 * 1. If enabled, it discards the first (noisy) measurement using the `one_shot` flag.
 * 2. Stores the incoming `instantaneousRatio` into the first-stage circular buffer (`capture_history`).
 * 3. Updates the first-stage moving average sum (`movingAvg1Sum`).
 * 4. Feeds the first-stage average into the second-stage buffer (`capture2_history`).
 * 5. Updates the second-stage moving average sum (`movingAvg2Sum`) using a graduated counter.
 * 6. Computes and returns the **smoothed actual ratio** via `actualRatio`.
 *
 * The result converges to `target_ratio` as more samples are processed.
 *
 * \param calcRatioInstance  Pointer to a valid, initialized \ref CalcRatio_t instance.
 * \param [in] Tx_Counter    Pointer to the latest sampled TX DMA transfer count (double).
 * \param [in] Rx_Counter    Pointer to the latest sampled RX DMA transfer count (double).
 *
 * \return                   Success/Failure for configuration.
 *
 */
int32_t calcRatio_exec(CalcRatio_t *calcRatioInstance,double *Tx_Counter,double *Rx_Counter);


/**
 * \brief   Safely retrieve the derived actual sample rate ratio.
 *
 * This function retrieves the current value of `actual_ratio` from the
 * specified `CalcRatio_t` instance in a thread-safe manner. It uses a
 * global binary semaphore (`gBinarySem_obj`) to guarantee exclusive
 * access and avoid race conditions when `calcRatio_exec()` updates the
 * ratio concurrently (for example, from a timer callback or another task).
 * It must not be invoked from an ISR context because semaphore-based
 * synchronization is used internally.
 *
 * \param   calcRatioInstance  Pointer to the CalcRatio instance.
 *
 * \return  The current value of `actual_ratio`.
 */

double calcRatio_getActualratio(CalcRatio_t *calcRatioInstance);


/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CALCRATIO_H_ */

/** @} */
