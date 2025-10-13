/*
 * FreeRTOS V202212.00
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 *  Copyright (C) 2024-25 Texas Instruments Incorporated
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
 * @file multiple_tasks_running.c
 * @brief The user shall be able to schedule tasks across multiple identical processor cores
 *        with one instance of FreeRTOS scheduler.
 *
 * Procedure:
 *   - Create ( num of cores - 1 ) tasks and keep them in busy loop.
 * Expected:
 *   - All tasks are in running state.
 */

/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */

/* Unity includes. */
#include "unity.h"
/*-----------------------------------------------------------*/

#ifndef TEST_CONFIG_H
    #error test_config.h must be included at the end of FreeRTOSConfig.h.
#endif

#if ( configNUMBER_OF_CORES < 2 )
    #error This test is for FreeRTOS SMP and therefore, requires at least 2 cores.
#endif /* if configNUMBER_OF_CORES != 2 */

#if ( configRUN_MULTIPLE_PRIORITIES != 1 )
    #error configRUN_MULTIPLE_PRIORITIES must be set to 1 for this test.
#endif /* if ( configRUN_MULTIPLE_PRIORITIES != 1 ) */

#if ( configMAX_PRIORITIES <= 2 )
    #error configMAX_PRIORITIES must be larger than 2 to avoid scheduling idle tasks unexpectedly.
#endif /* if ( configMAX_PRIORITIES <= 2 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Function that implements a never blocking FreeRTOS task.
 */
static void prvEverRunningTask( void * pvParameters );

/**
 * @brief Test case "Multiple Tasks Running".
 */
static void Test_MultipleTasksRunning( void *args );
/*-----------------------------------------------------------*/

/**
 * @brief Handles of the tasks created in this test.
 */
static TaskHandle_t xTaskHandles[ configNUMBER_OF_CORES - 1 ];
/*-----------------------------------------------------------*/

static void Test_MultipleTasksRunning( void *args )
{
    int i;
    eTaskState xTaskState;

    /* Delay for other cores to run tasks. */
    vTaskDelay( pdMS_TO_TICKS( 10 ) );

    /* Ensure that all the tasks are running. */
    for( i = 0; i < ( configNUMBER_OF_CORES - 1 ); i++ )
    {
        xTaskState = eTaskGetState( xTaskHandles[ i ] );

        TEST_ASSERT_EQUAL_MESSAGE( eRunning, xTaskState, "Task is not running." );
    }
}
/*-----------------------------------------------------------*/

static void prvEverRunningTask( void * pvParameters )
{
    /* Silence warnings about unused parameters. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Always running, put asm here to avoid optimization by compiler. */
        __asm volatile ( "nop" );
    }
}
/*-----------------------------------------------------------*/

/* Runs before every test, put init calls here. */
void setUp( void )
{
    int i;
    BaseType_t xTaskCreationResult;

    /* Create configNUMBER_OF_CORES - 1 low priority tasks. */
    for( i = 0; i < ( configNUMBER_OF_CORES - 1 ); i++ )
    {
        xTaskCreationResult = xTaskCreate( prvEverRunningTask,
                                           "EverRunning",
                                           configMINIMAL_STACK_SIZE,
                                           NULL,
                                           configMAX_PRIORITIES - 2,
                                           &( xTaskHandles[ i ] ) );

        TEST_ASSERT_EQUAL_MESSAGE( pdPASS, xTaskCreationResult, "Task creation failed." );
    }
}
/*-----------------------------------------------------------*/

/* Runs after every test, put clean-up calls here. */
void tearDown( void )
{
    int i;

    /* Delete all the tasks. */
    for( i = 0; i < ( configNUMBER_OF_CORES - 1 ); i++ )
    {
        if( xTaskHandles[ i ] != NULL )
        {
            vTaskDelete( xTaskHandles[ i ] );
        }
    }
}

/*-----------------------------------------------------------*/
/**
 * @brief Entry point for test runner to run multiple tasks running test.
 */
void test_multiple_tasks_running( void *args )
{
    UNITY_BEGIN();

    RUN_TEST(Test_MultipleTasksRunning, 8376, NULL);

    UNITY_END();
}
/*-----------------------------------------------------------*/
