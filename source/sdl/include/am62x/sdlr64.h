/*  ============================================================================
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
/**
 *  \file  sdlr64.h
 *
 *  \brief  This file contains the macro definitions for register layer or
 *  memory including 64-bit access.
 *
 *  Note: The register address is declared as pointer hence 64-bit pointer
 *  size depending on the machine is automatically taken care. Only the access
 *  type (depending on register) is 32 or 64 bit.
 */

#ifndef SDLR64_H_
#define SDLR64_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tistdtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief   This macro reads a 64-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 64-bit value read from a register.
 */
#define SDL_REG64_RD(p)             (SDL_REG64_RD_RAW( \
                                        (volatile uint64_t *) (p)))

/**
 *  \brief   This macro writes a 64-bit value to a hardware register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   v      Unsigned 64-bit value which has to be written to the
 *                  register.
 */
#define SDL_REG64_WR(p, v)          (SDL_REG64_WR_RAW( \
                                        (volatile uint64_t *) (p), \
                                        (uint64_t) (v)))

/**
 *  \brief This macro calls read field API for 64 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be read.
 *
 *  \return Value of the bit-field (absolute value - shifted to LSB position)
 */
#define SDL_REG64_FEXT(p, fld)      (SDL_REG64_FEXT_RAW( \
                                        ((volatile uint64_t *) (p)), \
                                        ((uint64_t) SDL_##fld##_MASK), \
                                        ((uint32_t) SDL_##fld##_SHIFT)))

/**
 *  \brief This macro calls read-modify-write API for 64 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   fld    Peripheral register bit field name, from which
 *                  specified bit-field value has to be set.
 *  \param   v      Value of the field which has to be set.
 */
#define SDL_REG64_FINS(p, fld, v)   (SDL_REG64_FINS_RAW( \
                                        ((volatile uint64_t *) (p)), \
                                        ((uint64_t) SDL_##fld##_MASK), \
                                        ((uint32_t) SDL_##fld##_SHIFT), \
                                        ((uint64_t) v)))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Global Variables Declarations                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   This function reads a 64-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 64-bit value read from a register.
 */
static inline uint64_t SDL_REG64_RD_RAW(volatile const uint64_t * const p);
static inline uint64_t SDL_REG64_RD_RAW(volatile const uint64_t * const p)
{
    return (*p);
}

/**
 *  \brief   This function writes a 64-bit value to a hardware register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   v      Unsigned 64-bit value which has to be written to the
 *                  register.
 */
static inline void SDL_REG64_WR_RAW(volatile uint64_t *p, uint64_t v);
static inline void SDL_REG64_WR_RAW(volatile uint64_t *p, uint64_t v)
{
    *p = v;
    return;
}

/**
 *  \brief   This function reads a 64 bit register, masks specific set of bits
 *           and returns the left shifted value.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline uint64_t SDL_REG64_FEXT_RAW(volatile const uint64_t * const p,
                                          uint64_t mask,
                                          uint32_t shift);
static inline uint64_t SDL_REG64_FEXT_RAW(volatile const uint64_t * const p,
                                          uint64_t mask,
                                          uint32_t shift)
{
    uint64_t regVal = SDL_REG64_RD_RAW(p);
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

/**
 *  \brief   This function reads a 64 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   p      Address of the memory mapped hardware register.
 *  \param   mask   Mask for the bit field.
 *  \param   shift  Bit field shift from LSB.
 *  \param   v      Value to be written to bit-field.
 */
static inline void SDL_REG64_FINS_RAW(volatile uint64_t * const p,
                                      uint64_t mask,
                                      uint32_t shift,
                                      uint64_t v);
static inline void SDL_REG64_FINS_RAW(volatile uint64_t * const p,
                                      uint64_t mask,
                                      uint32_t shift,
                                      uint64_t v)
{
    uint64_t regVal = SDL_REG64_RD_RAW(p);
    regVal = (regVal & ~(mask));
    regVal |= (v << shift) & mask;
    SDL_REG64_WR_RAW(p, regVal);
    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef SDLR64_H_ */
