/*
 *   Copyright (c) Texas Instruments Incorporated 2023
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
 *  \ingroup SDL_POK_MODULE
 *  \defgroup SDL_POK_API Power OK(POK)
 *
  */
/**
 *  \file    sdl_pok.h
 *
 *  \brief   This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of POK.
 *            This also contains some related macros. 
 */

#ifndef SDL_POK_H_
#define SDL_POK_H_
 
#include <sdl/pok/v1/sdl_ip_pok.h>
#include <sdl/esm/sdl_ip_esm.h>
#include <sdl/dpl/sdl_dpl.h>

#if defined (SOC_AM62x)
#include <sdl/include/am62x/sdlr_soc_baseaddress.h>
#include <sdl/include/am62x/sdlr_mcu_ctrl_mmr.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/** 
 *
 * \ingroup  SDL_MODULE
 * \defgroup SDL_POK_API Power OK(POK)
 *   Provides the APIs for POK.
 *
 */

/**
*\defgroup SDL_POK_DATASTRUCT  POK Data Structures
*\ingroup SDL_POK_API
*/
/**
*\defgroup SDL_POK_FUNCTION  POK Functions
*\ingroup SDL_POK_API
*/
/**
*
*                         Structures and Enums                               */

/** 
 *  @addtogroup SDL_POK_FUNCTION
 *  @{
 * 
 */

/** 
 * \brief POK Static Registers structure
 *
 * This structure defines the POK static configuration registers
 * 
 */



/** 
 *
 * \brief   POK Function to enable or disable ping/pong mode for a specified PRG.
 *          Only supported for v1 version of the IP.
 *
 * \param   instance: Instance of PRG
 * \param   enable: Enable or disable the ping/pong mode
 *
 * \return  SDL_PASS for success. SDL Error Code for failure.
 */
int32_t SDL_POK_enablePP(SDL_PRG_Inst instance, bool enable);

/** 
 *
 * \brief   POK Function to get the Static Registers.
 *          This function reads the values of the static registers such as
 *          hysteresis control, voltage detect mode, trim, PORGP and module
 *          status.
 *
 * \param   instance: Instance of POK
 * \param   pStaticRegs: Pointer to the static registers structure
 *
 * \return  SDL_PASS for success. SDL Error Code for Failure.
 */

int32_t SDL_POK_getStaticRegisters(SDL_POK_Inst instance,SDL_POK_staticRegs *pStaticRegs);

/** 
 *
 * \brief   POK module configuration API
 *
 * \param   instance: Instance of POK
 * \param   pConfig: Pointer to the configuration structure
 *
 * \return  SDL_PASS for success. SDL Error Code for Failure.
 */
int32_t SDL_POK_init(SDL_POK_Inst instance, SDL_POK_config *pConfig);

/** 
 *
 * \brief   POK Function to verify the written configuration.
 *          This function checks the provided config against the written config
 *          and returns the verification status.
 *
 * \param   instance: Instance of POK
 * \param   pConfig: Pointer to the configuration structure
 *
 * \return  SDL_PASS if configuration is verified to match.
 *          SDL Error Code for Failure.
 */
int32_t SDL_POK_verifyConfig(SDL_POK_Inst instance, SDL_POK_config *pConfig);

/** @} */

#ifdef __cplusplus
}
#endif
#endif /* SDL_POK_H_ */
