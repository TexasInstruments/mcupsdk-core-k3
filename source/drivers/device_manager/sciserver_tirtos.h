/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file sciserver_tirtos.h
 *
 *  \brief This file contains prototypes for APIs contained
 *         as a part of SCISERVER as well as the structures
 *         of their arguments for building an TI-RTOS Application.
 */

#ifndef SCISERVER_TIRTOS_H_
#define SCISERVER_TIRTOS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <drivers/device_manager/sciserver.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define SCISERVER_DEBUG_LOG_LEVEL_0     (0U)
/** Disables debug logs */
#define SCISERVER_DEBUG_LOG_LEVEL_1     (1U)
/** Enables level 1 of debug logs */

#define SCISERVER_EN_DEBUG_LOG_LEVEL    (SCISERVER_DEBUG_LOG_LEVEL_0)
/**< Enable SCI server logs */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Sciserver App Configuration Parameters */
typedef struct {
    uint32_t taskPriority[SCISERVER_TASK_MAX_CNT];
    /**< Task Priorities */
} Sciserver_TirtosCfgPrms_t ;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Sciserver TI-RTOS Application Init.
 * 
 *         NOTE: If this function is called form a Task Context
 *         (i.e, not from main / after starting the Schedular),
 *         the callee Task should be of priority higher than  
 *         max of passed init param(pPrms) Task priorities
 *         i.e Sciserver_TirtosCfgPrms_t->taskPriority[x]
 * 
 *  \param pPrms Pointer to #Sciserver_TirtosCfgPrms_t
 *  \return CSL_PASS if the init has happened correctly.
 *          CSL_EFAIL if otherwise.
 */
int32_t Sciserver_tirtosInit(Sciserver_TirtosCfgPrms_t *pPrms);

/** \brief Sciserver TI-RTOS Application Deinit.
 *  \param None
 *  \return None
 */
void Sciserver_tirtosDeinit();

/** \brief Sciserver enable interrupt
 *  \param None
 *  \return None
 */
void Sciserver_tirtosEnableIntr();

/** \brief Sciserver disable interrupt
 *  \param None
 *  \return None
 */
void Sciserver_tirtosDisableIntr();

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/** \brief Initialize the init params for SCISERVER.
 *  \param pPrms Pointer to the init parameters.
 *  \return CSL_PASS if init Params are initilized with some default.
 *          CSL_EFAIL otherwise.
 */
static int32_t Sciserver_tirtosInitPrms_Init(Sciserver_TirtosCfgPrms_t *pPrms)
{
    int32_t ret = CSL_PASS;
    if (pPrms != NULL)
    {
        pPrms->taskPriority[SCISERVER_TASK_USER_LO] = 1U;
        pPrms->taskPriority[SCISERVER_TASK_USER_HI] = 3U;
    }
    else
    {
        ret = CSL_EFAIL;
    }
    return ret;
}

#endif /* #ifndef SCISERVER_TIRTOS_H_ */

