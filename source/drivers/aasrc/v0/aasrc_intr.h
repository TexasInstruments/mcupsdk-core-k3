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
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_INTERRUPTS_MODULE AASRC Interrupt Service Routines
 *            This is AASRC interrupts related APIs, parameters and
 *            local functions
 *
 *  @{
 */

/**
 *  \file aacrc_intr.h
 *
 *  \brief AASRC Interrupt service routines and parameters
 */

#ifndef AASRC_INTR_H_
#define AASRC_INTR_H_

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

/** \brief Total number of interrupts to processor */
#define AASRC_PROCESSOR_INTERRUPT_COUNT         (5U)

/** \brief AASRC interrupt indexes
 *         The order is based on EOI order
 *         so DON'T CHANGE these values.
*/

#define AASRC_INFIFO_INTERUPT                   (0U)
#define AASRC_OUTFIFO_INTERUPT                  (1U)
#define AASRC_INGROUP_INTERUPT                  (2U)
#define AASRC_OUTGROUP_INTERUPT                 (3U)
#define AASRC_ERROR_INTERUPT                    (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief AASRC Interrupt structure
 */
typedef struct
{
    uint32_t intrNum;
    /**< Receive interrupt number */
    uint16_t evntNum;
    /**< Receive event number (Used for C7x only) */
    uint8_t intrPriority;
    /**< Interrupt priority */
} AASRC_HwIntCfg;

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Local Function Definitions                          */
/* ========================================================================== */

/**
 *  \brief AASRC hardware interrupt configuration
 *
 *  This function registers all the AASRC event interrupts with the SoC processors
 *
 *  \param drvHandle                [IN] driver handle returned from AASRC_open()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_RegisterHwEventInterrupts(AASRC_Handle drvHandle);

/**
 *  \brief AASRC hardware interrupt configuration
 *
 *  This function registers all the AASRC error interrupts with the SoC processors
 *
 *  \param drvHandle                [IN] driver handle returned from AASRC_open()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_RegisterHwErrorInterrupts(AASRC_Handle drvHandle);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_INTR_H_ */

/** @} */
