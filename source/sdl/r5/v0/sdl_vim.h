/*
 *   Copyright (c) Texas Instruments Incorporated 2024
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

/**
 *
 * @defgroup SDL_VIM_API APIs for SDL VIM
 * @ingroup SDL_MODULE
 * @{
 */

#ifndef SDL_VIM_H
#define SDL_VIM_H

#include <stdint.h>
#include <stdbool.h>
#include "sdlr_vim.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief This enumerator defines the maximum interrupt groups in VIM
 */

#define SDL_VIM_MAX_INTR_GROUPS     (32U)

/**
 * \brief This enumerator defines the number of interrupts per group in VIM
 */
#define SDL_VIM_NUM_INTRS_PER_GROUP (32U)

/**
 * \brief This enumerator defines the possible interrupt types. Each source
 *        interrupt is either an active high level or active high pulse.
 */
typedef uint32_t SDL_VimIntrType;

/**
 *  \brief  vim interrupt types
 */

/** Interrupt source is a level interrupt type */
#define SDL_VIM_INTR_TYPE_LEVEL ((uint32_t)0U)

/** Interrupt source is a pulse interrupt type */
#define SDL_VIM_INTR_TYPE_PULSE ((uint32_t)1U)

/**
 * \brief This enumerator defines the possible output interrupt types. Each
 *        source interrupt can be configured to drive either the IRQ or FIQ
 *        output signal.
 */
typedef uint32_t SDL_VimIntrMap;

/**
 * \brief Output interrupt is mapped to IRQ
 */

#define SDL_VIM_INTR_MAP_IRQ    ((uint32_t)0U)

/**
 * \brief Output interrupt is mapped to FIQ
 */

#define SDL_VIM_INTR_MAP_FIQ    ((uint32_t)1U)

/**
 * \brief Output interrupt is mapped to IRQ or FIQ
 */
#define SDL_VIM_INTR_MAP_ALL    ((uint32_t)2U)

/**
 * \brief This structure defines the group registers identified for VIM static
 * registers
 */
typedef struct {
    volatile uint32_t INTR_EN_SET;
    /**< Interrupt Enable Set Register */
    volatile uint32_t INTR_EN_CLR;
    /**< Interrupt Enabled Clear Register */
    volatile uint32_t INTMAP;
    /**< Interrupt Map Register */
    volatile uint32_t INTTYPE;
    /**< Interrupt Type Register */
} SDL_vimStaticRegs_GRP;

/**
  * \brief This structure defines the static register groups identified for VIM
 */
typedef struct {
    SDL_vimStaticRegs_GRP GRP[SDL_VIM_MAX_INTR_GROUPS];
    /**< Group Registers */
    SDL_vimRegs_PRI PRI[SDL_VIM_MAX_INTR_GROUPS*SDL_VIM_NUM_INTRS_PER_GROUP];
    /**< Priority Regs */
    SDL_vimRegs_VEC VEC[SDL_VIM_MAX_INTR_GROUPS*SDL_VIM_NUM_INTRS_PER_GROUP];
    /**< Vec addr regs */
    volatile uint32_t PID;
    /**< Revision Register */
    volatile uint32_t INFO;
    /**< Info Register */
} SDL_vimStaticRegs;

/** @} */

/**
 *  \brief Set the DED interrupt vector address
 *
 *  This function sets the 32-bit interrupt vector address (the address must
 *  be 32-bit aligned) of an interrupt to be used if an uncorrectable
 *  double-bit error (DED) is detected in any of the interrupt vector
 *  addresses. If there is a DED, the pVectorAddr argument of the
 *  SDL_VIM_getActivePendingIntr function will be populated with the value
 *  in this field instead of their normal vector.
 *
 *  \param pRegs            [IN]    Pointer to the SDL_vimRegs register structure
 *  \param dedVectorAddr    [IN]    The 32-bit DED interrupt vector address
 *
 */
void SDL_VIM_setDedVectorAddr( SDL_vimRegs *pRegs, uint32_t dedVectorAddr );

/**
 *  \brief Get the DED interrupt vector address
 *
 *  This function sets the 32-bit interrupt vector address (the address must
 *  be 32-bit aligned) of an interrupt to be used if an uncorrectable
 *  double-bit error (DED) is detected in any of the interrupt vector
 *  addresses. If there is a DED, the pVectorAddr argument of the
 *  SDL_VIM_getActivePendingIntr function will be populated with the value
 *  in this field instead of their normal vector.
 *
 *  \param pRegs            [IN]    Pointer to the SDL_vimRegs register structure
 *  \param pDedVectorAddr   [OUT]   Pointer to the 32-bit DED interrupt vector address
 *
 *  \return  0 = Success
 *           SDL_ESYS_FAIL = Failure
 */
int32_t SDL_VIM_getDedVectorAddr( SDL_vimRegs *pRegs, uint32_t *pDedVectorAddr );


#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif  /* end of SDL_VIM_H_ definition */
