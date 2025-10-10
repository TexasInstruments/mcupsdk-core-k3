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
 *   \file   calcratio.c
 *
 *   \brief  File containing CALCRATIO SW APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "calcratio.h"
#include <math.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore object for protecting actual ratio access */
SemaphoreP_Object gBinarySem_obj;

/* ========================================================================== */
/*                          API Function Definitions                          */
/* ========================================================================== */
int32_t calcRatio_init(CalcRatio_t *calcRatioInstance,
    float           inputSampleRate,
    float           outputSampleRate
    )
{
    int32_t status = SystemP_SUCCESS;

    /* Create semaphore for protecting actual ratio access */
    SemaphoreP_constructBinary(&gBinarySem_obj, 0);
    /* Post semaphore to make it available */
    SemaphoreP_post(&gBinarySem_obj);

    /* Initialize variables */
    uint32_t loopIndex;
    float tempSampleFloat  = 0.0;
    uint32_t tempSampleInt;

    /* Initialize moving average sums */
    calcRatioInstance->movingAvg1Sum = 0;
    calcRatioInstance->movingAvg2Count = 0;
    calcRatioInstance->movingAvg2Sum = 0;
    calcRatioInstance->one_shot = 0;

    /* Direct fills to instance */
    calcRatioInstance->fsi = inputSampleRate;
    calcRatioInstance->fso = outputSampleRate;

    /* Derived fills to instance */
    double ratioFloat = (double)calcRatioInstance->fso / (double)calcRatioInstance->fsi;
    calcRatioInstance->target_ratio = ratioFloat;

    /* Calculate moving average 1 */
    for (loopIndex = 0; loopIndex < CALCRATIO_MA1_LENGTH; loopIndex++)
    {
        tempSampleFloat += ratioFloat;
        tempSampleInt = floorf(tempSampleFloat);
        calcRatioInstance->movingAvg1Sum += (double)tempSampleInt;
        calcRatioInstance->capture_history[loopIndex] = (double)tempSampleInt;
        tempSampleFloat -= (double)tempSampleInt;
    }

    /* Initialize capture history */
    for (loopIndex = 0; loopIndex < CALCRATIO_MA2_LENGTH; loopIndex++)
    {
        calcRatioInstance->capture2_history[loopIndex] = 0;
    }

    /* Set up pointers to capture history */
    calcRatioInstance->P2_capture_hist = &(calcRatioInstance->capture_history[0]);
    calcRatioInstance->P2_capture2_hist = &(calcRatioInstance->capture2_history[0]);

    return status;
}

int32_t calcRatio_exec(CalcRatio_t *calcRatioInstance,double *Tx_Counter,double *Rx_Counter)
{
    int32_t status = SystemP_SUCCESS;
    double sampleDelta;
    double movingAverageSum, movingAverage;
    double tempActualRatio;
    double capture2HistoryTemp;

    /* Read actual ratio in a thread safe manner */
    SemaphoreP_pend(&gBinarySem_obj, SystemP_WAIT_FOREVER);

    if (calcRatioInstance->one_shot == 0U)
    {
        /* Make one shot a non-zero value */
        calcRatioInstance->one_shot     = (uint16_t)0xAAAA;
        calcRatioInstance->actual_ratio = calcRatioInstance->target_ratio;
    }
    else
    {
        sampleDelta = ((*Tx_Counter)/(*Rx_Counter));

        /* Remove oldest value from sum */
        calcRatioInstance->movingAvg1Sum -= *calcRatioInstance->P2_capture_hist;
        /* Store new value at current position */
        *calcRatioInstance->P2_capture_hist = sampleDelta;
        /* Increment pointer */
        *calcRatioInstance->P2_capture_hist++;
        calcRatioInstance->movingAvg1Sum += sampleDelta;

        /* Modulo wrap around for capture circular buffer */
        if ((calcRatioInstance->P2_capture_hist >= &(calcRatioInstance->capture_history[CALCRATIO_MA1_LENGTH])))
        {
            calcRatioInstance->P2_capture_hist = &(calcRatioInstance->capture_history[0]);
        }

        movingAverageSum      = calcRatioInstance->movingAvg1Sum;
        movingAverage         = movingAverageSum * ((1.0f/(float)CALCRATIO_MA1_LENGTH));
        tempActualRatio       = ((movingAverage));


        capture2HistoryTemp = *calcRatioInstance->P2_capture2_hist;
        *calcRatioInstance->P2_capture2_hist = tempActualRatio;
        calcRatioInstance->P2_capture2_hist++;
        calcRatioInstance->movingAvg2Sum += tempActualRatio;

        /* Modulo wrap around for capture2 pointer */
        if ((calcRatioInstance->P2_capture2_hist >= &(calcRatioInstance->capture2_history[CALCRATIO_MA2_LENGTH])))
        {
            calcRatioInstance->P2_capture2_hist = &(calcRatioInstance->capture2_history[0]);
        }

        /* Get 2nd moving average */
        if (calcRatioInstance->movingAvg2Count < CALCRATIO_MA2_LENGTH)
        {
            calcRatioInstance->movingAvg2Count++;
            calcRatioInstance->actual_ratio = ((double)calcRatioInstance->movingAvg2Sum) / (double)calcRatioInstance->movingAvg2Count;
        }
        else
        {
            calcRatioInstance->movingAvg2Sum -= capture2HistoryTemp;
            calcRatioInstance->actual_ratio =((double)calcRatioInstance->movingAvg2Sum) / (double)CALCRATIO_MA2_LENGTH;
        }

    }
    /* Post semaphore */
    SemaphoreP_post(&gBinarySem_obj);

    return status;
}

double calcRatio_getActualratio(CalcRatio_t *calcRatioInstance)
{
    double actualratio;
    /* Read actual ratio in a thread safe manner */
    SemaphoreP_pend(&gBinarySem_obj, SystemP_WAIT_FOREVER);
    /* Read actual ratio */
    actualratio = calcRatioInstance->actual_ratio;
    /* Post semaphore */
    SemaphoreP_post(&gBinarySem_obj);

    return actualratio;
}
