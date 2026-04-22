/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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

#include <stdint.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/ClockP.h>
#include "FreeRTOS.h"
#include "task.h"

/* Stack sizes — keep reasonable to avoid memory layout issues */
#if defined(__C7504__) || defined(__C7524__)
#define TASK_STACK_SIZE  (1024U * 64U)   /* Original: 64 KB */
#else
#define TASK_STACK_SIZE  (1024U * 4U)    /* Original: 4 KB */
#endif

#define NLC_TASK_PRI     (2U)
#define TEST_DURATION_S  (30U)

static uint8_t      gTaskAStack[TASK_STACK_SIZE] __attribute__((aligned(16 * 1024)));
static uint8_t      gTaskBStack[TASK_STACK_SIZE] __attribute__((aligned(16 * 1024)));
static TaskP_Object gTaskAObj, gTaskBObj;

volatile uint32_t gTaskAIter   = 0U;
volatile uint32_t gTaskBIter   = 0U;
volatile uint32_t gTaskAErrors = 0U;
volatile uint32_t gTaskBErrors = 0U;

/* -----------------------------------------------------------------------
 * NLC loop functions — C7x (cl7x) only
 * Task A inner=12, Task B inner=5: different ILCNT_INIT values are the
 * key requirement for the DOCU-470 bug to be detectable.
 * ----------------------------------------------------------------------- */
#if defined(__C7504__) || defined(__C7524__)

#define TASK_A_OUTER  (16U)
#define TASK_A_INNER  (12U)
#define TASK_A_TOTAL  (TASK_A_OUTER * TASK_A_INNER)   /* 192 */

#define TASK_B_OUTER  (8U)
#define TASK_B_INNER  (5U)
#define TASK_B_TOTAL  (TASK_B_OUTER * TASK_B_INNER)   /* 40 */

/* 8x buffers: DOCU-470 can corrupt the scalar clear/count loops too (single-level
 * NLC loops), causing them to run far beyond the expected count and overwrite
 * adjacent FreeRTOS structures. 8x provides safety margin for all loop corruption. */
static int32_t gBufA[TASK_A_TOTAL * 8U];
static int32_t gBufB[TASK_B_TOTAL * 8U];

static void nlc_write_a(void)
{
    int32_t i;
    int32_t j;
    for (i = 0; i < (int32_t)TASK_A_OUTER; i++)
        for (j = 0; j < (int32_t)TASK_A_INNER; j++)
        {
            gBufA[i * (int32_t)TASK_A_INNER + j] = 1;
        }
}

static void nlc_write_b(void)
{
    int32_t i;
    int32_t j;
    for (i = 0; i < (int32_t)TASK_B_OUTER; i++)
        for (j = 0; j < (int32_t)TASK_B_INNER; j++)
        {
            gBufB[i * (int32_t)TASK_B_INNER + j] = 1;
        }
}

static void taskA_func(void *args)
{
    int32_t k; 
    uint32_t count;
    for (;;)
    {
        /* memset: uses vectorized stores, not NLC — immune to DOCU-470 loop corruption */
        memset(gBufA, 0, sizeof(gBufA));
        nlc_write_a();
        count = 0U;
        for (k = 0; k < (int32_t)(TASK_A_TOTAL * 8U); k++) 
        { 
            count += (uint32_t)gBufA[k]; 
        }

        gTaskAIter++;
        if (count != TASK_A_TOTAL)
        {
            gTaskAErrors++;
            DebugP_log("[NLC] TASK-A iter %u: count=%u expected=%u CORRUPTION\r\n",(unsigned int)gTaskAIter, (unsigned int)count, (unsigned int)TASK_A_TOTAL);
        }
    }
}

static void taskB_func(void *args)
{
    int32_t k; 
    uint32_t count;
    for (;;)
    {
        memset(gBufB, 0, sizeof(gBufB));
        nlc_write_b();
        count = 0U;
        for (k = 0; k < (int32_t)(TASK_B_TOTAL * 8U); k++) 
        { 
            count += (uint32_t)gBufB[k]; 
        }
        gTaskBIter++;
        if (count != TASK_B_TOTAL)
        {
            gTaskBErrors++;
            DebugP_log("[NLC] TASK-B iter %u: count=%u expected=%u CORRUPTION\r\n",(unsigned int)gTaskBIter, (unsigned int)count, (unsigned int)TASK_B_TOTAL);
        }
    }
}

#endif /* __C7504__ || __C7524__ */

/* -----------------------------------------------------------------------
 * test_nlc_multitask_main
 * ----------------------------------------------------------------------- */
void test_nlc_multitask_main(void *args)
{
#if defined(__C7504__) || defined(__C7524__)
    TaskP_Params prm;
    int32_t      sts;
    uint32_t     i;

    DebugP_log("\r\n[NLC] DOCU-470 test start\r\n");

    TaskP_Params_init(&prm);
    prm.name = "nlcA"; prm.stackSize = TASK_STACK_SIZE;
    prm.stack = gTaskAStack; prm.priority = NLC_TASK_PRI;
    prm.taskMain = taskA_func;
    sts = TaskP_construct(&gTaskAObj, &prm);
    DebugP_assert(sts == SystemP_SUCCESS);

    TaskP_Params_init(&prm);
    prm.name = "nlcB"; prm.stackSize = TASK_STACK_SIZE;
    prm.stack = gTaskBStack; prm.priority = NLC_TASK_PRI;
    prm.taskMain = taskB_func;
    sts = TaskP_construct(&gTaskBObj, &prm);
    DebugP_assert(sts == SystemP_SUCCESS);

    uint32_t prevAIter = 0U, prevBIter = 0U;
    for (i = 0U; i < TEST_DURATION_S; i++)
    {
        ClockP_sleep(1U);
        DebugP_log("[NLC] t=%us A:iter=%u err=%u B:iter=%u err=%u\r\n",(unsigned int)i + 1U,(unsigned int)gTaskAIter, (unsigned int)gTaskAErrors,(unsigned int)gTaskBIter, (unsigned int)gTaskBErrors);

        /* Watchdog: if a task stops incrementing for 2 consecutive seconds
         * it is stuck inside an NLC loop due to DOCU-470.  Destroy it to
         * prevent buffer overflow from corrupting the kernel. */
        if ((i > 0U) && (gTaskAIter == prevAIter))
        {
            gTaskAErrors++;
            DebugP_log("[NLC] ERROR: TASK-A stuck (NLC infinite loop) at iter=%u — destroying\r\n",(unsigned int)gTaskAIter);
            TaskP_destruct(&gTaskAObj);
        }
        if ((i > 0U) && (gTaskBIter == prevBIter))
        {
            gTaskBErrors++;
            DebugP_log("[NLC] ERROR: TASK-B stuck (NLC infinite loop) at iter=%u — destroying\r\n",(unsigned int)gTaskBIter);
            TaskP_destruct(&gTaskBObj);
        }
        prevAIter = gTaskAIter;
        prevBIter = gTaskBIter;
    }

    TaskP_destruct(&gTaskAObj);
    TaskP_destruct(&gTaskBObj);

    if ((gTaskAErrors == 0U) && (gTaskBErrors == 0U))
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("\r\n[NLC] FAIL A_err=%u B_err=%u\r\n",(unsigned int)gTaskAErrors, (unsigned int)gTaskBErrors);
    }

#else
    DebugP_log("[NLC] C7x only, skipping\r\n");
    DebugP_log("All tests have passed!!\r\n");
#endif
}
