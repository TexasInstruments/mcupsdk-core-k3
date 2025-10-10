# CALCRATIO {#SW_CALCRATIO_PAGE}

[TOC]

## Introduction

The CalcRatio algorithm is a real-time sample rate ratio estimator designed to track clock mismatch between two asynchronous audio domains. It computes the ratio of output (Tx) to input (Rx) sample counters and applies a Two-stage moving average to deliver a smooth, stable actual ratio for Asynchronous Sample Rate Conversion (ASRC).

## Key Features

- DMA-Counter-Based Ratio Calculation
- Two-Stage Moving Average
- One-Shot Noise Rejection
- High Accuracy Ratio Tracking


## Algorithm Overview
The CalcRatio algorithm works as follows:

1. Initialization (#calcRatio_init()) :
    - Initializes the CALC_RATIO module with input and output sample rates.
    - Computes the target ratio (sampleRateOut / sampleRateIn).
    - Resets all internal states:
        - Moving-average buffers
        - Window pointers
        - Accumulated sums
        - Counters and the one-shot flag
    - Prepares the module for accurate ratio estimation.
2. First Stage Moving Average (MA1) :
    - Applies a 1024-point moving average to the instantaneous ratio.
    - Removes high-frequency noise and sudden spikes.
    - Produces a smoothed ratio that still responds to short-term changes.
3. Second Stage Filtering (MA2) :
    - Applies a 128-point moving average to the output of MA1.
    - Reduces long-term drift and stabilizes the ratio.
    - Generates a clean, low-noise ratio used by the resampling stage.
4. Ratio Calculation (#calcRatio_exec()) :
    - Reads instantaneous ratio from the TX/RX DMA counters.
    - Uses a one-shot skip to ignore the first noisy measurement.
    - Updates MA1 and MA2 buffers and their accumulated sums.
    - Computes the actual ratio using both filtering stages.
5. Output (#calcRatio_getActualratio())
    - Provides two key ratio values:
        - Target Ratio: Calculated at initialization.
        - Actual Ratio: Filtered, stable ratio for SW_ASRC operation.
    - Thread-safe access using a global semaphore to avoid race conditions.

### API Sequence

To use CALC_RATIO, the application should call the following APIs:

- #calcRatio_init():Initialize the CALC_RATIO module .
- #calcRatio_exec():Processes the instantaneous ratio input and computes the filtered, stable actual ratio.
- #calcRatio_getActualratio(): Returns the latest calculated actual ratio for use by the SW_ASRC

## API

\ref SW_CALCRATIO_MODULE