/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
/*
 * SDL ESM
 *
 * Software Diagnostics Reference module for Error Signaling Module
 *
*/
/**
 *  @addtogroup SDL_ESM_MODULE APIs for SDL ESM
 *  @{
 */

/**
 * \file  sdl_esm.h
 *
 * \brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL Error Signaling Module interface.
 *
 *  The SDL ESM enumerations include:
 *      1. SDL ESM interrupt types
 *      2. SDL ESM interrupt sources
 *      3. SDL ESM Watchdog Timer IDs
 *
 *  The SDL ESM function macros include:
 *      1. Application provided callback function type for ECC/CCM specific ESM events
 *
 *  The SDL ESM data structures include:
 *      1. Structure of the ECC error sources which map to the ESM interrupt sources
 *      2. Structure of the ESM error configuration
 *      3. Structure of the initial ESM configuration
 *
 *  The SDL ESM APIs include:
 *      1. API to initialize the SDL ESM
 *      2. APIs to set/reset nERROR pin
 *      3. API to get nERROR pin status
 *      4. API to insert an ESM error
 *      5. API to execute self test of ESM module
 *      6. APIs to register handler for ECC/CCM with ESM
 *      7. APIs to handle ESM high priority/low prioirty/config interrupts
 *      8. API to get ESM Interrupt Number corresponding to the input ESM interrupt type
 *      9. Application provided external callback function for ESM handling
 */

#ifndef INCLUDE_SDL_ESM_H_
#define INCLUDE_SDL_ESM_H_

#include <stdint.h>
#include <stdbool.h>

#include <sdl/esm/soc/sdl_esm_soc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t SDL_Result;

/** ---------------------------------------------------------------------------
 * \brief This enumerator defines the values for ESM interrupt types
 * ----------------------------------------------------------------------------
 */

typedef enum {
   SDL_ESM_INT_TYPE_HI = 1,
    /**< Interrupt type Hi  */
   SDL_ESM_INT_TYPE_LO = 2,
    /**< Interrupt type Lo  */
   SDL_ESM_INT_TYPE_CFG = 3,
    /**< Interrupt type Config  */
   SDL_ESM_INT_TYPE_MAX = 4,
   /**< Interrupt type Max  */
} SDL_ESM_IntType;

/** ---------------------------------------------------------------------------
 * \brief Defines the different ESM instance types
 * ----------------------------------------------------------------------------
 */

/** \brief Invalid interrupt number */
#define SDL_ESM_INTNUMBER_INVALID (0xffffffffu)

/** \brief Invalid Esm Instance */
#define SDL_ESM_INST_INVALID      (0xfffffffeu)

/** \brief Address field: Error Address invalid */
#define SDL_ESM_ERRORADDR_INVALID (0xffffffffu)

/** \brief Address field: Error RAM ID invalid */
#define SDL_ESM_ERRORRAMID_INVALID (0xffffffffu)

/** \brief Address field: Error Bit Error Offset invalid */
#define SDL_ESM_ERRORBITOFFSET_INVALID (0xffffffffffffffffu)

/** \brief Address field: Error Bit Error Group invalid */
#define SDL_ESM_ERRORBITGROUP_INVALID (0xffffffffu)

/** \brief Maximum number of EVENT words */
#define SDL_ESM_MAX_EVENT_MAP_NUM_WORDS (32u)

/**
 *  \anchor sdlEsmEccErrorSource_t
 *  \name ESM ECC Error source type
 *  @{
 */
/**
 * \brief  Source of the ECC error which maps to the ESM interrupt source
 */
typedef uint32_t sdlEsmEccErrorSource_t;

/** \brief MCU CPU0 detected 1-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CPU0_SEC_ERROR (1u)
/** \brief MCU CPU0 detected 2-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CPU0_DED_ERROR (2u)
/** \brief MCU CPU1 detected 1-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CPU1_SEC_ERROR (3u)
/** \brief MCU CPU1 detected 2-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CPU1_DED_ERROR (4u)
/** \brief MCU CBASS detected 1-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CBASS_SEC_ERROR (5u)
/** \brief MCU CBASS detected 2-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MCU_CBASS_DED_ERROR (6u)

/** @} */

/** \brief Main MSMC ECC AGGR0 detected 1-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MAIN_MSMC_AGGR0_SEC_ERROR (10001u)
/** \brief Main MSMC ECC AGGR0  detected 2-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MAIN_MSMC_AGGR0_DED_ERROR (10002u)
/** \brief Main A72 ECC AGGR0 detected 1-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MAIN_A72_AGGR0_SEC_ERROR (10003u)
/** \brief Main A72 ECC AGGR0 detected 2-bit ECC error source */
#define SDL_ESM_ECC_PARAM_MAIN_A72_AGGR0_DED_ERROR (10004u)

typedef int32_t (* SDL_ESM_applicationCallback) (SDL_ESM_Inst instance, SDL_ESM_IntType intrType, uint32_t grpChannel, uint32_t index, uint32_t intSrc, void *arg);

/** ---------------------------------------------------------------------------
 * \brief ESM error configuration
 *
 * This structure defines the elements ESM error configuration
 * ----------------------------------------------------------------------------
 */
typedef struct SDL_ESM_Errorconfig_s
{
    uint32_t groupNumber;
    /**< Group number of error event  */
    uint32_t bitNumber;
    /**< Bit number within the group  */
} SDL_ESM_ErrorConfig_t;

/** ---------------------------------------------------------------------------
 * \brief ESM init configuration
 *
 * This structure defines ESM Init configuration
 * ----------------------------------------------------------------------------
 */
typedef struct SDL_ESM_InitConfig_s
{
    SDL_ESM_ErrorConfig_t esmErrorConfig;
    /**< Error event to be used for self test */
    uint32_t enableBitmap[SDL_ESM_MAX_EVENT_MAP_NUM_WORDS];
    /**< ESM Event bitmap */
    uint32_t priorityBitmap[SDL_ESM_MAX_EVENT_MAP_NUM_WORDS];
    /**< ESM Event Priority bitmap */
    uint32_t errorpinBitmap[SDL_ESM_MAX_EVENT_MAP_NUM_WORDS];
    /**< ESM bitmap for driving error pin: When selected error event occurs
     *  the error output pin will be asserted
     *  It is the application responsibility to reset the error
     *  if the system did not crash or lockup */
    uint32_t pinmininterval;
} SDL_ESM_config;

/** ============================================================================
 *
 * \brief   Esm Hi Interrupt Handler for MCU Esm Instance
 *
 * \param  arg: argument for handler
 */
void SDL_ESM_hiInterruptHandler (void *arg);

/** ============================================================================
 *
 * \brief   Esm Lo Interrupt Handler for MCU Esm Instance
 *
 * \param  arg: argument for handler
 */
void SDL_ESM_loInterruptHandler (void *arg);

/** ============================================================================
 *
 * \brief   Esm Config Interrupt Handler for MCU Instance
 *
 * \param   arg: argument for handler
 */
void SDL_ESM_configInterruptHandler(void *arg);

/** ============================================================================
 *
 * \brief   Esm get Interrupt Number corresponding to the
 *          input interrupt type
 *
 * \param   esmInstType: Instance of ESM
 * \param   esmIntType: ESM Interrupt type
 *
 * \return  Interrupt Number or SDL_ESM_INTNUMBER_INVALID error
 */
int32_t SDL_ESM_getIntNumber(SDL_ESM_Inst esmInstType,
                              SDL_ESM_IntType esmIntType);


/** @} */

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* INCLUDE_SDL_ESM_H_ */