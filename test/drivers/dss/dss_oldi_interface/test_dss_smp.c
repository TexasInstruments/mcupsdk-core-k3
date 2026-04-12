/*
 *  Copyright (C) 2024-26 Texas Instruments Incorporated
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
 *  \file test_dss_smp.c
 *
 *  \brief DSS SMP tests - exercises DSS driver under FreeRTOS SMP by
 *         running display workloads pinned to different A53 cores.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/dss.h>
#include <drivers/fvid2.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Task stack size */
#define TEST_DSS_SMP_TASK_STACK_SIZE     (16U * 1024U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void TestDss_smpCrossCorDisplayTest(void *args);
static void TestDss_smpFramePrepTest(void *args);

/* Worker functions for spawned tasks */
static void TestDss_smpCore1DisplayWorker(void *arg);
static void TestDss_smpFramePrepWorker(void *arg);

/* Max frame size based on resolution (must match control.c) */
#define DISP_FRAME_SIZE_MAX                (3840U * 1080U)

/* Max pixel width (must match control.c) */
#define DISP_FRAME_PIXEL_WIDTH_MAX         (4U)

/* Extern: non-static functions from control.c */
extern int32_t TestDisp_displayControl(Dss_Object *appObj);

/* Extern: frame buffer globals from control.c */
extern uint8_t gFirstPipelineFrameBuf
    [][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX];
extern uint8_t gSecondPipelineFrameBuf
    [][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX];
extern void *firstPipeFrameBufferPointer[];
extern void *secondPipeFrameBufferPointer[];

/* Extern: frame buffer fill function from dss_display_pattern.c */
extern void Disp_prepareFrameBuffer(uint32_t instCount,
                                    uint32_t inDataFmt,
                                    uint32_t inWidth,
                                    uint32_t inHeight,
                                    uint32_t pitch,
                                    void *frameBuffer[]);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Context passed to each frame-preparation worker */
typedef struct
{
    uint32_t  pipeIdx;       /**< Pipeline index (0=VID, 1=VIDL) */
    int32_t   result;        /**< SystemP_SUCCESS or SystemP_FAILURE */
    uint64_t  elapsedUs;     /**< Time taken in microseconds */
} TestDss_SmpFramePrepCtx;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TaskP_Object TestDss_smpTaskObj[2U];
static uint8_t TestDss_smpTaskStack[2U][TEST_DSS_SMP_TASK_STACK_SIZE]
    __attribute__((aligned(32)));
static SemaphoreP_Object TestDss_smpDoneSem;
static SemaphoreP_Object TestDss_smpStartSem;
static volatile int32_t  TestDss_smpCore1Result;
static TestDss_SmpFramePrepCtx TestDss_smpFpCtx[2U];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief  Core 1 display task for the DSS SMP cross-core test.
 *
 * Runs a full display control cycle from Core 1 after Core 0 completes:
 * Executes TestDisp_displayControl for the OLDI test pattern.
 * Stores result in TestDss_smpCore1Result.
 * Signals completion via done semaphore.
 * Test case category: worker task
 *
 * \param arg  Unused argument.
 */
static void TestDss_smpCore1DisplayWorker(void *arg)
{
    (void)arg;

    DebugP_log("SMP Core 1: Running display control "
               "(test pattern on OLDI)\r\n");

    TestDss_smpCore1Result = TestDisp_displayControl(
                                 &gDssObjects[CONFIG_DSS0]);

    DebugP_log("SMP Core 1: display done - %s\r\n",
               (TestDss_smpCore1Result == SystemP_SUCCESS) ?
               "PASS" : "FAIL");

    SemaphoreP_post(&TestDss_smpDoneSem);

    /* Block forever — main task will delete us via TaskP_destruct.
     * A FreeRTOS task function must never return. */
    while(1)
    {
        ClockP_usleep(1000000);
    }
}

/**
 * \brief  DSS multicore cross-core display handoff test.
 *
 * Executes a display control cycle from each A53 core sequentially:
 * Core 0 runs a full display cycle (init, create, run, delete, deinit).
 * Creates a task pinned to Core 1 to run a second display cycle.
 * Waits for Core 1 task to complete.
 * Checks per-core results and cleans up semaphores and task objects.
 *
 * \param args  Unused argument.
 */
static void TestDss_smpCrossCorDisplayTest(void *args)
{
    int32_t  status;
    int32_t  core0Result;
    TaskP_Params taskParams;

    (void)args;

    DebugP_log("======================================================\r\n");
    DebugP_log("SMP Test 1: Cross-Core Display Handoff\r\n");
    DebugP_log("======================================================\r\n");

    /* --- Phase 1: Core 0 runs display --- */
    DebugP_log("SMP Core 0: Running display control "
               "(test pattern on OLDI)\r\n");

    core0Result = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("SMP Core 0: display done - %s\r\n",
               (core0Result == SystemP_SUCCESS) ? "PASS" : "FAIL");
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, core0Result);

    /* --- Phase 2: Spawn task on Core 1 for second pass --- */
    status = SemaphoreP_constructBinary(&TestDss_smpDoneSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestDss_smpCore1Result = SystemP_FAILURE;

    TaskP_Params_init(&taskParams);
    taskParams.name         = "DSS_SMP_C1";
    taskParams.stackSize    = TEST_DSS_SMP_TASK_STACK_SIZE;
    taskParams.stack        = TestDss_smpTaskStack[0U];
    taskParams.priority     = 2U;
    taskParams.args         = NULL;
    taskParams.taskMain     = TestDss_smpCore1DisplayWorker;
    taskParams.coreAffinity = 1U << 1;  /* Pin to Core 1 */

    status = TaskP_construct(&TestDss_smpTaskObj[0U], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for Core 1 to finish */
    SemaphoreP_pend(&TestDss_smpDoneSem, SystemP_WAIT_FOREVER);

    TaskP_destruct(&TestDss_smpTaskObj[0U]);
    SemaphoreP_destruct(&TestDss_smpDoneSem);

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("  Core 0 : %s\r\n",
               (core0Result == SystemP_SUCCESS) ? "PASS" : "FAIL");
    DebugP_log("  Core 1 : %s\r\n",
               (TestDss_smpCore1Result == SystemP_SUCCESS) ?
               "PASS" : "FAIL");
    DebugP_log("SMP Test 1: %s\r\n",
               ((core0Result == SystemP_SUCCESS) &&
                (TestDss_smpCore1Result == SystemP_SUCCESS)) ?
               "PASSED" : "FAILED");
    DebugP_log("======================================================\r\n");

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestDss_smpCore1Result);
}

/**
 * \brief  Frame-buffer preparation task for the DSS SMP parallel test.
 *
 * Performs per-pipeline frame buffer preparation on the assigned core:
 * Waits on start barrier until main releases all workers simultaneously.
 * Sets up frame buffer pointers for the assigned pipeline.
 * Fills frame buffers with test pattern (CPU-intensive, no driver locks).
 * Records elapsed time and stores result in ctx->result.
 * Signals completion via done semaphore.
 * Test case category: worker task
 *
 * \param arg  Pointer to TestDss_SmpFramePrepCtx for the pipeline instance.
 */
static void TestDss_smpFramePrepWorker(void *arg)
{
    TestDss_SmpFramePrepCtx *ctx = (TestDss_SmpFramePrepCtx *)arg;
    uint32_t pipeIdx = ctx->pipeIdx;
    uint64_t t0, t1;
    void **fbPtr;

    ctx->result    = SystemP_FAILURE;
    ctx->elapsedUs = 0U;

    /* Wait for main task to release both workers simultaneously */
    SemaphoreP_pend(&TestDss_smpStartSem, SystemP_WAIT_FOREVER);

    DebugP_log("SMP Core %u: Preparing frame buffers for pipe %u\r\n",
               pipeIdx, pipeIdx);

    t0 = ClockP_getTimeUsec();

    /* Set up frame buffer pointers for this pipeline */
    if(pipeIdx == 0U)
    {
        fbPtr = firstPipeFrameBufferPointer;
        for(uint32_t i = 0U; i < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; i++)
        {
            fbPtr[i] = &gFirstPipelineFrameBuf[i];
        }
    }
    else
    {
        fbPtr = secondPipeFrameBufferPointer;
        for(uint32_t i = 0U; i < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; i++)
        {
            fbPtr[i] = &gSecondPipelineFrameBuf[i];
        }
    }

    /* Fill frame buffers with test pattern (CPU-intensive, no locks) */
    Disp_prepareFrameBuffer(
        pipeIdx,
        gDssConfigPipelineParams.inDataFmt[pipeIdx],
        gDssConfigPipelineParams.inWidth[pipeIdx],
        gDssConfigPipelineParams.inHeight[pipeIdx],
        gDssConfigPipelineParams.pitch[pipeIdx][0],
        fbPtr);

    t1 = ClockP_getTimeUsec();

    ctx->elapsedUs = t1 - t0;
    ctx->result    = SystemP_SUCCESS;

    DebugP_log("SMP Core %u: Frame prep done for pipe %u "
               "(%u us)\r\n",
               pipeIdx, pipeIdx, (uint32_t)ctx->elapsedUs);

    SemaphoreP_post(&TestDss_smpDoneSem);

    /* Block forever — main task will delete us via TaskP_destruct.
     * A FreeRTOS task function must never return. */
    while(1)
    {
        ClockP_usleep(1000000);
    }
}

/**
 * \brief  DSS multicore parallel frame buffer preparation test.
 *
 * Prepares frame buffers for each pipeline on a separate A53 core:
 * Creates per-instance semaphore and task pinned to core (inst % cores).
 * Releases all tasks simultaneously via start barrier.
 * Waits for all tasks to complete.
 * Checks per-instance results.
 * Runs TestDisp_displayControl to verify buffers render correctly.
 * Cleans up semaphores and task objects.
 *
 * \param args  Unused argument.
 */
static void TestDss_smpFramePrepTest(void *args)
{
    int32_t  status;
    int32_t  displayResult;
    uint32_t numPipes;
    uint32_t idx;
    TaskP_Params taskParams;

    (void)args;

    DebugP_log("======================================================\r\n");
    DebugP_log("SMP Test 2: Parallel Frame Buffer Preparation\r\n");
    DebugP_log("  Core 0: Prepare VID  pipe frame buffers\r\n");
    DebugP_log("  Core 1: Prepare VIDL pipe frame buffers\r\n");
    DebugP_log("======================================================\r\n");

    numPipes = gDssConfigPipelineParams.numTestPipes;
    if(numPipes > 2U)
    {
        numPipes = 2U;
    }

    /* Construct synchronisation primitives */
    status = SemaphoreP_constructCounting(&TestDss_smpDoneSem, 0, numPipes);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructCounting(&TestDss_smpStartSem, 0, numPipes);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* --- Phase 1: Spawn one worker per pipeline, each pinned to its core --- */
    for(idx = 0U; idx < numPipes; idx++)
    {
        TestDss_smpFpCtx[idx].pipeIdx   = idx;
        TestDss_smpFpCtx[idx].result    = SystemP_FAILURE;
        TestDss_smpFpCtx[idx].elapsedUs = 0U;

        TaskP_Params_init(&taskParams);
        taskParams.name         = (idx == 0U) ? "DSS_SMP_FP0" :
                                                 "DSS_SMP_FP1";
        taskParams.stackSize    = TEST_DSS_SMP_TASK_STACK_SIZE;
        taskParams.stack        = TestDss_smpTaskStack[idx];
        taskParams.priority     = 2U;
        taskParams.args         = (void *)&TestDss_smpFpCtx[idx];
        taskParams.taskMain     = TestDss_smpFramePrepWorker;
        taskParams.coreAffinity = 1U << idx;  /* Core 0 or Core 1 */

        status = TaskP_construct(&TestDss_smpTaskObj[idx], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Release all workers simultaneously */
    for(idx = 0U; idx < numPipes; idx++)
    {
        SemaphoreP_post(&TestDss_smpStartSem);
    }

    /* Wait for all workers to finish */
    for(idx = 0U; idx < numPipes; idx++)
    {
        SemaphoreP_pend(&TestDss_smpDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Clean up worker tasks */
    for(idx = 0U; idx < numPipes; idx++)
    {
        TaskP_destruct(&TestDss_smpTaskObj[idx]);
    }

    SemaphoreP_destruct(&TestDss_smpDoneSem);
    SemaphoreP_destruct(&TestDss_smpStartSem);

    /* Check frame-prep results */
    for(idx = 0U; idx < numPipes; idx++)
    {
        DebugP_log("  Pipe %u frame prep: %s (%u us)\r\n",
                   idx,
                   (TestDss_smpFpCtx[idx].result == SystemP_SUCCESS) ?
                   "PASS" : "FAIL",
                   (uint32_t)TestDss_smpFpCtx[idx].elapsedUs);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                                TestDss_smpFpCtx[idx].result);
    }

    /* --- Phase 2: Run display to verify buffers render correctly --- */
    DebugP_log("SMP Main: Running display with parallel-prepared "
               "buffers...\r\n");

    displayResult = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("SMP Main: Display result: %s\r\n",
               (displayResult == SystemP_SUCCESS) ? "PASS" : "FAIL");

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("SMP Test 2: %s\r\n",
               (displayResult == SystemP_SUCCESS) ?
               "PASSED" : "FAILED");
    DebugP_log("======================================================\r\n");

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, displayResult);
}

/* ========================================================================== */
/*                     Unity Framework Functions                              */
/* ========================================================================== */

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * \brief  Main entry point for DSS SMP tests.
 *
 * Initializes Unity and runs the multicore DSS display tests.
 *
 * \param args  Unused argument.
 */
void test_dss_smp_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestDss_smpCrossCorDisplayTest, 11298, NULL);
    RUN_TEST(TestDss_smpFramePrepTest, 11520, NULL);

    UNITY_END();
}
