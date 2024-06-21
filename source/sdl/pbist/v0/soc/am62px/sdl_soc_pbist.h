/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *   @file  sdl/pbist/v0/soc/am62px/sdl_soc_pbist.h
 *
 *   @brief This file contains the SoC-specific SDL PBIST API's and
 *          definitions.
 *
 *   @defgroup SDL_PBIST_MODULE APIs for PBIST (Memory Built-In Self Test)
 *
 *   Provides the APIs for PBIST.
 *
 *   @{
 */

#ifndef SDL_PBIST_SOC_H_
#define SDL_PBIST_SOC_H_

#include <stdint.h>
#include <sdl/include/am62px/sdlr_soc_pbist.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief PBIST instance
 *
 *  This enum defines the PBIST instances supported by the SDL_PBIST_selfTest API.
 */
typedef enum {
    /*!
     * COMPUTE_CLUSTER0_PBIST :A53
     */
    SDL_PBIST_INST_MPU,
    /*!
     * PBIST3 : Encoder
     */
    SDL_PBIST_INST_ENCODE,
    /*!
     * PBIST1 :
     */
	SDL_PBIST_INST_PBIST1,
    /*!
     * WKUP_PBIST1 :
     */
	SDL_PBIST_INST_WKUP_PBIST1,
    /*!
     * GPU0 : GPU IP
     */
	SDL_PBIST_INST_GPU,
    /*!
     * PBIST0 : Main IP
     */
	SDL_PBIST_INST_MAIN,
	/*!
     * MCU_PBIST0 : MCU Pulsar
     */
    SDL_PBIST_INST_MCU,
} SDL_PBIST_inst;

typedef enum {
    /*!
     * MCU Instance
     */
    SDL_PBIST_HWPOST_INST_MCU,
} SDL_PBIST_hwpostInst;

typedef enum {
    /*!
     * The HW POST PBIST completed and the test passed
     */
    SDL_PBIST_POST_COMPLETED_SUCCESS,
    /*!
     * The HW POST PBIST completed and the test failed
     */
    SDL_PBIST_POST_COMPLETED_FAILURE,
    /*!
     * The HW POST PBIST was run but timed out
     */
    SDL_PBIST_POST_TIMEOUT,
    /*!
     * The HW POST PBIST was not performed on this device
     */
    SDL_PBIST_POST_NOT_RUN
} SDL_PBIST_postStatus;

/* Total number of instances*/
#define SDL_PBIST_NUM_INSTANCES 7U

typedef struct {
    /*!
     * HW POST PBIST status for MCU
     */
    SDL_PBIST_postStatus mcuPostStatus;
} SDL_PBIST_postResult;

int32_t SDL_PBIST_getDevicePostStatus(SDL_PBIST_postResult *pResult);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SDL_PBIST_SOC_H_ */