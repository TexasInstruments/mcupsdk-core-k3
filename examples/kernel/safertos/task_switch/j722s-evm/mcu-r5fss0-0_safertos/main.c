/*
 *  Copyright (C) 2024-2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "SafeRTOS_API.h"
#include "taskAPI.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define configASSERT(x)                        DebugP_assert( (uint32_t)((x) != 0))

#define MAIN_TASK_PRI  (configMAX_PRIORITIES-1)

#define MAIN_TASK_SIZE (16384U)

portInt8Type gMainTaskStack[MAIN_TASK_SIZE] __attribute__((aligned(MAIN_TASK_SIZE)));
xTCB gTaskTCB;

void task_switch_main(void *args);

void safertos_main(void *args)
{
    /* Open drivers, including UART for SysFW logs */
    Drivers_open();

    /* Open board drivers */
    DebugP_assert(SystemP_SUCCESS==Board_driversOpen());

    task_switch_main(NULL);

    /* Delete the calling task with NULL argument. */
    xTaskDelete(NULL);
}

int main()
{
    portBaseType xStatus;

    /* init SOC specific modules */
    System_init();

    /* Do Board init */
    Board_init();

    xTaskParameters xTaskPParams =
    {
        ( pdTASK_CODE )&safertos_main,                  /* The function that implements the task being created. */
        ( portCharType* )"safertos_main",               /* The name of the task being created. The kernel does not use this itself, its just to assist debugging. */
        &gTaskTCB,                                      /* TCB for the task. */
        (portInt8Type *)gMainTaskStack,                 /* The buffer allocated for use as the task stack. */
        MAIN_TASK_SIZE,                                 /* The size of the buffer allocated for use as the task stack - note this is in BYTES! */
        NULL,                                           /* The task parameter. */
        (portUnsignedBaseType)MAIN_TASK_PRI,            /* The priority to assigned to the task being created. */
        NULL,                                           /* User-defined data. */
#if defined (BUILD_MCU)
        pdFALSE,                                        /* Check task does not use the FPU. */
        {                                               /* MPU task parameters. */
            mpuPRIVILEGED_TASK,                         /* Check task is privileged. */
            {
                { NULL, 0U, 0U, 0U },                   /* No additional region definitions are required. */
                { NULL, 0U, 0U, 0U },
            }
        }
#endif
    };

    xStatus = xTaskCreate(&xTaskPParams, NULL);
    configASSERT(pdPASS == xStatus);

    /* Start the scheduler to start the tasks executing. */
    xStatus = xTaskStartScheduler();
    configASSERT(pdPASS == xStatus);

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    /* Close all open drivers. */
    Drivers_close();

    /* Close all open board drivers */
    Board_driversClose();

    return 0;
}
