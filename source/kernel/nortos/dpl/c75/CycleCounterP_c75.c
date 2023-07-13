/*
 * Copyright (c) 2016-2021, Texas Instruments Incorporated
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
/*
 *  ======== TimestampProvider.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include <c7x.h>

#include "HwiP_c75.h"
#include "CycleCounterP_c75.h"


/*
 *  ======== TimestampProvider_get32 ========
 */
uint32_t CycleCounterP_getCount32()
{
    return (uint32_t)__TSC;
}

void CycleCounterP_reset()
{
    /* TSC already started by firmware, nothing to do here */
    return;
}

#define C7X_ENABLE_TSC_CALIBRATION (1)

#if (C7X_ENABLE_TSC_CALIBRATION == 1)
#define NOP5         do {          \
                         asm(" NOP "); \
                         asm(" NOP "); \
                         asm(" NOP "); \
                         asm(" NOP "); \
                         asm(" NOP "); \
                     } while (0)

#define NOP50        do {      \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                         NOP5; \
                     } while(0)

#define NOP500     do {         \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                         NOP50; \
                     } while(0)

#define NOP1000   do {           \
                        NOP500;  \
                        NOP500;  \
                  } while(0)

uint64_t gTscDeltaCalib = 0;

#endif /* #if (C7X_ENABLE_TSC_CALIBRATION == 1) */


/*
 *  ======== CycleCounterP_Module_startup ========
 */
void CycleCounterP_Module_startup( void )
{
#if (C7X_ENABLE_TSC_CALIBRATION == 1)
   uint64_t startTime,endTime,i;
   /*
    * Part of runtime. Called during first pass.
    * All APIs need to be ready after first pass.
    */
   /* TSC already started by firmware, nothing to do here */
   startTime = __TSC;
   for (i = 0; i < 1000; i++)
   {
       NOP1000;
   }
   endTime = __TSC;
   gTscDeltaCalib = endTime - startTime;
#endif
   return;
}

