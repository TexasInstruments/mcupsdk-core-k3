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

#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <SafeRTOS_API.h>
#include <taskAPI.h>
#include <semaphoreAPI.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#define NUM_TASK_SWITCHES      (1000000U)

#define PING_INT_NUM           (20U)
#define PONG_INT_NUM           (21U)

#define PING_TASK_PRI          (2U)
#define PONG_TASK_PRI          (3U)

#define PING_TASK_SIZE         (16U * 1024U)
#define PONG_TASK_SIZE         (16U * 1024U)


static portInt8Type  gPingTaskStack[PING_TASK_SIZE] __attribute__( ( aligned( PING_TASK_SIZE ) ) );

static portInt8Type  gPongTaskStack[PONG_TASK_SIZE] __attribute__( ( aligned( PONG_TASK_SIZE ) ) );


static xTCB xPingTaskTCB = { 0 };
static xTCB xPongTaskTCB = { 0 };

portTaskHandleType gPongTaskHandle, gPingTaskHandle;

/* Semaphore buffers. No actual data is stored into these buffers, so the
 * buffer need only be large enough to hold the queue structure itself. */
portInt8Type gPingSemBuf[ safertosapiQUEUE_OVERHEAD_BYTES ] __attribute__( ( aligned ( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };
portInt8Type gPongSemBuf[ safertosapiQUEUE_OVERHEAD_BYTES ] __attribute__( ( aligned ( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };
#if defined(SOC_J722S)
portInt8Type gPongTaskBuf[ safertosapiQUEUE_OVERHEAD_BYTES ] __attribute__( ( aligned ( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };
#endif
HwiP_Object gPingHwiObj;
HwiP_Object gPongHwiObj;

/* Semaphore Parameters. */
static xSemaphoreHandle gPingSem = NULL;
static xSemaphoreHandle gPongSem = NULL;
#if defined(SOC_J722S)
static xSemaphoreHandle gPongTaskTermination = NULL;
#endif


static void ping_isr(void *arg)
{
    xSemaphoreGiveFromISR( gPongSem ); /* wake up pong task */
    safertosapiYIELD_FROM_ISR();
}

static void pong_isr(void *arg)
{
    xSemaphoreGiveFromISR( gPingSem ); /* wake up ping task */
    safertosapiYIELD_FROM_ISR();
}

void ping_main(void *args)
{
    uint32_t count; /* loop `count` times */
    volatile uint64_t curTime; /* time in units of 10's of usecs */
    portBaseType semaphoreResult = pdPASS;

    DebugP_log("\r\n");
    DebugP_log("[SafeRTOS] ping task ... start !!!\r\n");
    { /* switch between ping and pong tasks using semaphores */
        count = NUM_TASK_SWITCHES;
        curTime = ClockP_getTimeUsec();
        while(count-- && ( pdPASS == semaphoreResult ) )
        {
            semaphoreResult = xSemaphoreGive( gPongSem );
            if( pdPASS == semaphoreResult )
            {
                semaphoreResult = xSemaphoreTake( gPingSem, safertosapiMAX_DELAY );
            }
        }
        DebugP_assert( pdPASS == semaphoreResult );

        curTime = ClockP_getTimeUsec() - curTime;

        DebugP_log("\r\n");
        DebugP_log("execution time for task switches = %" PRId64 " us\r\n", curTime);
        DebugP_log("number of task switches = %" PRId32 " \r\n", (uint32_t)NUM_TASK_SWITCHES*2);
        DebugP_log("time per task switch (semaphore give/take) = %" PRId32 " ns\r\n", (uint32_t)(curTime*1000/(NUM_TASK_SWITCHES*2)));
    }
    { /* switch from ping task to ISR to pong task and back to ping task using semaphores, here there is a task switch */
        HwiP_Params hwiParams;

        HwiP_Params_init(&hwiParams);
        hwiParams.intNum = PING_INT_NUM;
        hwiParams.eventId = HWIP_INVALID_EVENT_ID;
        hwiParams.callback = ping_isr;
        HwiP_construct(&gPingHwiObj, &hwiParams);

        count = NUM_TASK_SWITCHES;
        curTime = ClockP_getTimeUsec();
        while(count--)
        {
            HwiP_post(PING_INT_NUM);
            xSemaphoreTake( gPingSem, safertosapiMAX_DELAY); /* wait for ISR to signal */
        }
#if defined(SOC_J722S)
        xSemaphoreGive( gPongTaskTermination );
#endif
        curTime = ClockP_getTimeUsec() - curTime;

        HwiP_destruct(&gPingHwiObj);

        DebugP_log("\r\n");
        DebugP_log("execution time for task - ISR - task - task switches = %" PRId64 " us\r\n", curTime);
        DebugP_log("number of ISRs = %" PRId32 " \r\n", (uint32_t)NUM_TASK_SWITCHES*2);
        DebugP_log("time per task - ISR - task switch (semaphore give/take) = %" PRId32 " ns\r\n", (uint32_t)(curTime*1000/(2*NUM_TASK_SWITCHES)));
    }

    /* delay some time, just to show delay works */
    xTaskDelay( ClockP_usecToTicks(100*1000) );
    xTaskDelay( ClockP_usecToTicks(101*1000) );

    DebugP_log("\r\n");
    DebugP_log("[SafeRTOS] ping task ... done !!!\r\n");
    DebugP_log("\r\n");
    DebugP_log("All tests have passed!!\r\n");

    /* One MUST not return out of a SafeRTOS task instead one MUST call xTaskDelete */
    xTaskDelete(NULL);
}

void pong_main(void *args)
{
    uint32_t count; /* loop `count` times */
    portBaseType semaphoreResult = pdPASS;

    count = NUM_TASK_SWITCHES;
    while(count-- && ( pdPASS == semaphoreResult ))
    {
        semaphoreResult = xSemaphoreTake( gPongSem, safertosapiMAX_DELAY );
        if( pdPASS == semaphoreResult )
        {
            semaphoreResult = xSemaphoreGive( gPingSem );
        }
    }
    DebugP_assert( pdPASS == semaphoreResult );

    {
        HwiP_Params hwiParams;

        HwiP_Params_init(&hwiParams);
        hwiParams.intNum = PONG_INT_NUM;
        hwiParams.eventId = HWIP_INVALID_EVENT_ID;
        hwiParams.callback = pong_isr;
        HwiP_construct(&gPongHwiObj, &hwiParams);

        count = NUM_TASK_SWITCHES;
        while(count--)
        {
            xSemaphoreTake( gPongSem, safertosapiMAX_DELAY); /* wait for ISR to signal */
            HwiP_post(PONG_INT_NUM);
        }
#if defined(SOC_J722S)
        xSemaphoreTake( gPongTaskTermination, safertosapiMAX_DELAY);
#endif
        HwiP_destruct(&gPongHwiObj);
    }
    /* One MUST not return out of a SafeRTOS task instead one MUST call xTaskDelete */
    xTaskDelete(NULL);
}

void task_switch_main(void *args)
{
    portBaseType xStatus;

    /* Create the semaphore used by the first two tasks. */
    xSemaphoreCreateBinary( gPingSemBuf, &gPingSem );
    if( gPingSem == NULL )
    {
        xStatus = pdFAIL;
    }
    else
    {
        xStatus = xSemaphoreTake( gPingSem, safertosapiMAX_DELAY );
    }
    DebugP_assert(xStatus != pdFAIL);
    xSemaphoreCreateBinary( gPongSemBuf, &gPongSem );
    if( gPongSem == NULL )
    {
        xStatus = pdFAIL;
    }
    else
    {
        xStatus = xSemaphoreTake( gPongSem, safertosapiMAX_DELAY );
    }
    DebugP_assert(xStatus != pdFAIL);
#if defined(SOC_J722S)
    xSemaphoreCreateBinary( gPongTaskBuf, &gPongTaskTermination );
    if( gPongTaskTermination == NULL )
    {
        xStatus = pdFAIL;
    }
    else
    {
        xStatus = xSemaphoreTake( gPongTaskTermination, safertosapiMAX_DELAY );
    }
    DebugP_assert(xStatus != pdFAIL);
#endif

    xTaskParameters xPongMainParameters =
    {
        &pong_main,                         /* Task code */
        "pong",                             /* Task name */
        &xPongTaskTCB,                      /* TCB */
        gPongTaskStack,                     /* Stack buffer */
        PONG_TASK_SIZE,                     /* Stack depth bytes */
        NULL,                               /* Parameters */
        PONG_TASK_PRI,                      /* Priority */
        NULL,                               /* TLS object */
#if defined (BUILD_MCU)
        pdFALSE,                            /* Check task does not use the FPU. */
        {                                  /* MPU task parameters. */
            mpuPRIVILEGED_TASK,         /* Check task is privileged. */
            {
                { NULL, 0U, 0U, 0U },   /* No additional region definitions are required. */
                { NULL, 0U, 0U, 0U },
            }
        }                               /* Port-specific task parameters */
#endif
    };
    xTaskParameters xPingMainParameters =
    {
        &ping_main,                         /* Task code */
        "ping",                             /* Task name */
        &xPingTaskTCB,                      /* TCB */
        gPingTaskStack,                     /* Stack buffer */
        PING_TASK_SIZE,                     /* Stack depth bytes */
        NULL,                               /* Parameters */
        PING_TASK_PRI,                      /* Priority */
        NULL,                               /* TLS object */
#if defined (BUILD_MCU)
        pdFALSE,                            /* Check task does not use the FPU. */
        {                                  /* MPU task parameters. */
            mpuPRIVILEGED_TASK,         /* Check task is privileged. */
            {
                { NULL, 0U, 0U, 0U },   /* No additional region definitions are required. */
                { NULL, 0U, 0U, 0U },
            }
        }                               /* Port-specific task parameters */
#endif
    };

    /* Create the privileged test tasks. */
    if( xTaskCreate( &xPongMainParameters, &gPongTaskHandle ) != pdPASS )
    {
        xStatus = pdFAIL;
    }
    DebugP_assert(xStatus != pdFAIL);

    if( xTaskCreate( &xPingMainParameters, &gPingTaskHandle ) != pdPASS )
    {
        xStatus = pdFAIL;
    }
    DebugP_assert(xStatus != pdFAIL);
}
