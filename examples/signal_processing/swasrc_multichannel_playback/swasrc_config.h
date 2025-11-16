/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

/* Use this file to edit the AASRC Params */

#ifndef SWASRC_CONFIG_H
#define SWASRC_CONFIG_H

/* User editable parameters start  */

/**
 * \brief These values are used by the Calcratio-initialisation routine.
 *
 * \param[in] INPUT_FRAME_SYNC_CLOCK  – exact input sample-rate(fs) (Hz)
 * \param[in] OUTPUT_FRAME_SYNC_CLOCK – exact output sample-rate(fs) (Hz)
 *
 */
#if defined (SOC_AM275X)
#define INPUT_FRAME_SYNC_CLOCK              (32000) /* Internal clock (Hz)*/
#define OUTPUT_FRAME_SYNC_CLOCK             (48000) /* External clock (Hz)*/
#endif

#if defined (SOC_AM62DX)
#define INPUT_FRAME_SYNC_CLOCK              (32547) /* Internal clock (Hz)*/
#define OUTPUT_FRAME_SYNC_CLOCK             (48000) /* External clock (Hz)*/
#endif

/* User editable parameters end  */


/* ========================================================================== */
/*                          SWASRC Init Params                                */
/* ========================================================================== */

#define INPUT_SAMPLE_RATE                       (32000U)        /* Input sample rate in Hz */
#define OUTPUT_SAMPLE_RATE                      (48000U)        /* Output sample rate in Hz */
#define NUM_CHANNLES                            (8U)            /* number of channels */
#define INPUT_BLOCKSIZE                         (256U)          /* number of samples per channel per processing SWASRC block */
#define AUDIOLIB_FUNCTION                       (1U)            /* Library selection */
#define BYTES_PER_SAMPLE_ASRC                   (4U)            /* 4 bytes for float32 */
#define FRAME_MODULOFACTOR                      (4U)            /* Frame modulo factor, used to calculate the output sample count. */
#define Q31_TO_FLOAT_SCALE                      (2147483648.0f) /* Define Q31 normalization factor (2^31) */
#define FLOAT_TO_Q31_SCALE                      (2147483647.0f) /* Define Q31 normalization factor (2^31 - 1 for signed range) */
#define AUDIOLIB_ASRC_DOUBLE_BUFFERING_FACTOR   (2U)

/* ========================================================================== */
/*                        SWASRC Buffer Management                            */
/* ========================================================================== */
/* ASRC Filter Coefficients
 * This array holds the FIR filter coefficients used by the ASRC
 * when converting from 32 kHz to 48 kHz sample rate.
 * The coefficients are included from a pre-generated header file.
 */
__attribute__((section(".sw_asrc"), aligned(AUDIOLIB_L2DATA_ALIGNMENT))) float audiolib_asrc_filter_coeff[] = {
    #include "../src/AUDIOLIB_asrc/filt_coeffs/h32_32kHz_to_48kHz_rfmt.h"
};

/* Non-Interleaved Data Buffer */
__attribute__((section(".sw_asrc"), aligned(4096)))
 float nonInterleavedDatabuf[(int32_t)NUM_CHANNLES * (int32_t)INPUT_BLOCKSIZE * (int32_t)AUDIOLIB_ASRC_DOUBLE_BUFFERING_FACTOR * BYTES_PER_SAMPLE_ASRC];

/* SW ASRC Input Buffer */
__attribute__((section(".sw_asrc")))
 float inbuf[INPUT_BLOCKSIZE * NUM_CHANNLES];

/* Filter Remainder Buffer  */
__attribute__((section(".sw_asrc")))
 float filterRembuffer[NUM_CHANNLES * (FRAME_MODULOFACTOR -1) * BYTES_PER_SAMPLE_ASRC];

/* SW ASRC Output Buffer  */
 __attribute__((section(".sw_asrc"), aligned(512)))
float outbuf[((OUTPUT_SAMPLE_RATE/INPUT_SAMPLE_RATE)* INPUT_BLOCKSIZE * NUM_CHANNLES)+ (INPUT_BLOCKSIZE*2) * NUM_CHANNLES];

/* Temporary buffer used for holding ASRC input and output samples during processing */
int32_t local_buf_rx_tx[((OUTPUT_SAMPLE_RATE/INPUT_SAMPLE_RATE) * INPUT_BLOCKSIZE*2)*(NUM_CHANNLES)];


/* ========================================================================== */
/*                       SWASRC Kernel Handle                   *             */
/* ========================================================================== */

/**
 * \brief Handle for the SW_ASRC processing kernel instance.
 *
 * This structure maintains internal context and state information
 * required by the SW_ASRC library during initialization and execution.
 */
AUDIOLIB_kernelHandle handle;

/**
 * \brief Input arguments for SW_ASRC execution.
 *
 * Defines the number of input samples per processing block.
 * This value determines the frame size passed to each `SW_ASRC_process()` call.
 *
 * \note Must be initialized with a valid `INPUT_BLOCKSIZE` before use.
 */
AUDIOLIB_asrc_ExecInArgs  execInArgs  = {INPUT_BLOCKSIZE};
/**
 * \brief ASRC Execution Output Arguments.
 *
 * Contains the results of the ASRC processing, including the number
 * of output samples generated.
 */
AUDIOLIB_asrc_ExecOutArgs execOutArgs = {0};
/**
 * @brief Global status variable for ASRC API operations.
 *
 * Tracks the result of initialization, configuration, and processing calls
 * made to the ASRC library functions.
 */
AUDIOLIB_STATUS AUDIOLIB_status      = AUDIOLIB_SUCCESS;


/* ========================================================================== */
/*                       API Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief Initializes the synchronization semaphores for RX and TX buffers.
 *
 *  This function constructs binary semaphores used to protect access to the
 *  shared circular audio buffers (RX and TX). It must be called once during
 *  system initialization before any buffer operations are performed.
 *
 *  \param  None
 *
 *  \return  None
 *
 */
void buffer_init(void);

/**
 *  \brief Returns the number of bytes currently filled in the McASP RX buffer.
 *
 *  This function provides a thread-safe snapshot of how much valid audio data
 *  is currently stored in the RX circular buffer. Useful for monitoring buffer
 *  occupancy or making flow-control decisions.
 *
 *  \param  None
 *
 *  \return  Number of bytes filled in the RX buffer (0 to BUFFER_SIZE)
 *
 *  \remarks
 *      - Protected by rxLock semaphore to prevent race conditions with
 *        mcasp_storeRxSamples() and mcasp_getRxSamples().
 *      - Value is based on bufferFilled_rx, which is updated atomically
 *        within locked sections.
 */
int32_t mcasp_get_filled_space_rx(void);

/**
 *  \brief Returns the amount of free space available in the McASP TX buffer.
 *
 *  This function returns how many bytes can still be written to the TX circular
 *  buffer without causing overflow. Useful for rate control or preventing
 *  dropped samples during transmission.
 *
 *  \param  None
 *
 *  \return  Number of free bytes in the TX buffer (0 to BUFFER_SIZE)
 *
 *  \remarks
 *      - Thread-safe access via txLock semaphore.
 *      - Calculated as BUFFER_SIZE - bufferFilled.
 *      - A return value of 0 indicates the TX buffer is full.
 */
int32_t mcasp_tx_buffer_freespace(void);

/**
 *  \brief Stores captured McASP RX audio samples into the circular receive buffer.
 *
 *  This function is called from the McASP RX callback to safely copy incoming audio
 *  samples into the shared circular buffer. It handles wrap-around and prevents buffer
 *  overflow using a semaphore for thread-safe access.
 *
 *  \param [in] sampleSize   Size of the audio sample block in bytes
 *  \param [in] sample       Pointer to the source audio sample data
 *
 *  \return  None
 *
 *  \remarks
 *      - If adding the new samples would cause overflow, the function returns early
 *        without modifying the buffer.
 *      - The buffer uses rx_head for writing and bufferFilled_rx to track occupancy.
 *      - Thread-safe via rxLock semaphore.
 */
void mcasp_storeRxSamples(int32_t sampleSize, uint8_t *sample);

/**
 *  \brief Retrieves processed samples from the RX buffer for ASRC input.
 *
 *  Copies the requested number of samples from the circular RX buffer to the destination
 *  pointer for further processing (e.g., input to ASRC). Handles wrap-around and prevents
 *  underflow.
 *
 *  \param [in]  totalSamplesToProcess  Number of bytes to copy from RX buffer
 *  \param [out] ptr                    Pointer to destination buffer
 *
 *  \return  1 on success, 0 if insufficient samples available (underflow)
 *
 *  \remarks
 *      - Uses rx_tail for reading and decrements bufferFilled_rx on success.
 *      - Thread-safe via rxLock semaphore.
 *      - Caller should check return value before using the data in ptr.
 */
int32_t mcasp_getRxSamples(int32_t totalSamplesToProcess, uint8_t *ptr);

/**
 *  \brief Stores processed (float-to-int converted) TX samples into the transmit buffer.
 *
 *  Called after ASRC output conversion to store integer samples into the TX circular
 *  buffer for playback via McASP. Handles wrap-around and prevents overflow.
 *
 *  \param [in] sampleSize   Size of the audio sample block in bytes
 *  \param [in] sample       Pointer to the source audio sample data (integer format)
 *
 *  \return  None
 *
 *  \remarks
 *      - If buffer is full, samples are dropped silently.
 *      - Uses tx_head for writing and bufferFilled to track occupancy.
 *      - Thread-safe via txLock semaphore.
 */
void mcasp_storeTxSamples(int32_t sampleSize, uint8_t *sample);

/**
 *  \brief Provides audio samples from TX buffer to McASP transmitter callback.
 *
 *  Supplies the McASP TX callback with the next block of audio samples from the
 *  circular transmit buffer. Handles wrap-around and underflow conditions.
 *
 *  \param [in]  totalSamplesToProcess  Number of bytes requested by McASP TX
 *  \param [out] ptr                    Pointer to destination buffer for McASP
 *
 *  \return  None
 *
 *  \remarks
 *      - If not enough samples are available, the function returns early (underflow).
 *      - Uses tx_tail for reading and decrements bufferFilled on success.
 *      - Thread-safe via txLock semaphore.
 *      - McASP may play silence or previous data if underflow occurs.
 */
void mcasp_getTxSamples(int32_t totalSamplesToProcess, uint8_t *ptr);

/**
 *  \brief Initializes the Software Asynchronous Sample Rate Converter (SWASRC) module.
 *
 *  Sets up internal state, filter coefficients, delay lines, and control parameters
 *  required for real-time rate conversion. Must be called once during system startup
 *  before any audio processing begins.
 *
 *  \param [in]  args  Pointer to configuration structure (SWASRC_Config_t) containing:
 *                     - input/output sample rates
 *                     - block size
 *                     - filter quality
 *                     - optional work buffer
 *
 *  \return  None
 *
 */
void swasrc_init(void *args);

/**
 *  @brief Executes the SWASRC processing on a block of input audio samples.
 *
 *  Core processing routine of the Software Asynchronous Sample Rate Converter
 *  (SWASRC). Takes captured input samples from the RX buffer, performs rate
 *  conversion and fractional delay, and outputs integer samples ready
 *  for McASP TX playback.
 *
 *  @param [in]  g_inbuf  Pointer to input buffer containing audio samples
 *                        (typically int32_t in Q31 format or raw integer)
 *
 *  @return  None
 *
 *  @remarks
 *      - Called from swasrc_RxTask() after retrieving a block via
 *        mcasp_getRxSamples().
 *      - Input buffer size must match the configured SW_ASRC block size.
 *      - Output is written directly to the TX circular buffer using
 *        mcasp_storeTxSamples().
 *      - Internally handles float conversion, filtering, interpolation/
 *        decimation, and integer dithering if enabled.
 *      - Must be highly efficient and reentrant for real-time execution.
 *      - Uses global SWASRC instance state (filter history, phase, ratio).
 */
void swasrc_exec(int32_t *g_inbuf);


#endif /* SWASRC_CONFIG_H_ */

/** @} */
