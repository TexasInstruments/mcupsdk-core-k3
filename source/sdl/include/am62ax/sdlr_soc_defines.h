/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
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
 *
 */

#ifndef SDLR_SOC_DEFINES_H_
#define SDLR_SOC_DEFINES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Cache line size definitions	*/
#if defined(__aarch64__) /* A53 */
#define SDL_CACHE_L1P_LINESIZE     (64U)
#define SDL_CACHE_L1D_LINESIZE     (64U)
#define SDL_CACHE_L2_LINESIZE      (64U)
#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R') /* R5F */
#define SDL_CACHE_L1P_LINESIZE     (32U)
#define SDL_CACHE_L1D_LINESIZE     (32U)
#elif (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'M') /* M4F */
/* No cache support */
#endif


#define MCAN_MSG_RAM_MAX_WORD_COUNT     (4352U)

/**
 * \anchor SDL_CoreID
 * \name Core ID's of core or CPUs present on this SOC
 *
 * @{
 */
#define SDL_CORE_ID_MCU_R5FSS0_0     (0U)
#define SDL_CORE_ID_R5FSS0_0         (1U)
#define SDL_CORE_ID_A53SS0_0         (2U)
#define SDL_CORE_ID_A53SS0_1         (3U)
#define SDL_CORE_ID_A53SS1_0         (4U)
#define SDL_CORE_ID_A53SS1_1         (5U)
#define SDL_CORE_ID_HSM_M4FSS0_0     (6U)
#define SDL_CORE_ID_C7XSS0_0         (7U)
#define SDL_CORE_ID_MAX              (8U)
/** @} */

/**
 *  \anchor SDL_ArmR5ClusterGroupID
 *  \name R5 Cluster Group IDs
 *
 *  @{
 */
/** \brief R5 Cluster Group ID0 */
#define SDL_ARM_R5_CLUSTER_GROUP_ID_0                 ((uint32_t) 0x00U)
/** @} */

/**
 *  \anchor SDL_ArmR5CPUID
 *  \name R5 Core IDs
 *
 *  @{
 */
/** \brief R5 Core ID0 */
#define SDL_ARM_R5_CPU_ID_0                          ((uint32_t) 0x00U)
/** @} */

/** @brief Number of ePWM instances */
#define SDL_EPWM_PER_CNT (9U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* SDLR_SOC_DEFINES_H_ */
