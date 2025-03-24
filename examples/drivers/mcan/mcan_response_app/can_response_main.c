/*
 *  Copyright (c) Texas Instruments Incorporated 2024-25
 *  All rights reserved.
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
 *  \file can_response_main.c
 *
 *  \brief File containing main function implementation for CAN Response App
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <drivers/device_manager/sciclient.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "can_response_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define CAN_TASK_STACK                    (1024U)

/* Task Priority */
#define CAN_TASK_PRIORITY                 (2)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Stack for the CAN response task */
StackType_t  gCanResponseAppStack[CAN_TASK_STACK] __attribute__((aligned(32)));

/* Task Handle for CAN Reponse task */
TaskHandle_t gCanResponseAppTask;

/* Task object for CAN Reponse task */
StaticTask_t gCanResponseAppTaskObj;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 * \brief  CAN Response Task Function
 *
 * \param  None
 *
 * \return None
 */
static void CanResponseApp_taskFxn(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CanResponseApp_main(void *args)
{
    /* Create CAN Response Task */
    gCanResponseAppTask = xTaskCreateStatic(CanResponseApp_taskFxn,      /* Pointer to the function that implements the task. */
                                            "Can Response",              /* Text name for the task.  This is to facilitate debugging only. */
                                            CAN_TASK_STACK,              /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                            NULL,                        /* We are not using the task parameter. */
                                            CAN_TASK_PRIORITY,           /* Task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                            gCanResponseAppStack,        /* Pointer to stack base */
                                            &gCanResponseAppTaskObj) ;   /* Pointer to statically allocated task object memory */
    configASSERT(gCanResponseAppTask != NULL);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* CAN Response App Task Function of type 'TaskFunction_t' (aka 'void (*)(void *)') */
static void CanResponseApp_taskFxn(void *args)
{
    CanResponseApp_transmit();
}