/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file hyperbus_soc.h
 *
 *  \brief HYPERBUS Driver AM275x SOC specific file.
 */

#ifndef HYPERBUS_SOC_H_
#define HYPERBUS_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/cslr_soc.h>
#include <drivers/hyperbus.h>
#include <drivers/soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This function returns the input clk frequency HYPERBUS was programmed at
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  handle  An #HYPERBUS_Handle returned from an #HYPERBUS_open()
 *
 *  \return HYPERBUS X2CLK in Hertz
 */
uint32_t HYPERBUS_getInputClk(HYPERBUS_Handle handle);

/**
 *  \brief  This function performs HYPERBUS power and clock initialization.
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  handle  An #HYPERBUS_Handle returned from an #HYPERBUS_open()
 * 
 *  \post   HYPERBUS clock is enabled and power domain is turned on.
 * 
 *  \return 0 on success, negative value on failure
 */
int32_t HYPERBUS_powerClockInit(HYPERBUS_Handle handle);


/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HYPERBUS_SOC_VO_H_ */
