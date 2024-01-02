/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/soc.h>

/*
 * Firewall exception interrupt numbers may vary for device-core combinations.
 * In order to make the example work, it must be ensured that the MACRO
 * `FWL_EXCEPTION_NOTIFY_SYSFW_FWL_EXCEPTION` is an alias of the CSLR MACRO
 * which represents the dmsc fwl exception interrupt number for core on which this
 * example is to be executed. Similarly, the MACRO `FWL_EXCEPTION_NOTIFY_CMBN_FWL_EXCEPTION`
 * must be an alias of the CSLR MACRO which represents the combined fwl exception
 * interrupt number for the core on which this example is to be executed.
 */
#define FWL_EXCEPTION_NOTIFY_SYSFW_FWL_EXCEPTION (CSLR_WKUP_R5FSS0_CORE0_INTR_SMS0_TIFS_CBASS_0_FW_EXCEPTION_INTR_0)
#define FWL_EXCEPTION_NOTIFY_CMBN_FWL_EXCEPTION (CSLR_WKUP_R5FSS0_CORE0_INTR_SMS0_COMMON_0_COMBINED_SEC_IN_0)

/* Priority for firewall exception notify tasks */
#define FWL_EXCPT_NOTIFY_TASK_PRI         (configMAX_PRIORITIES-2U)
/* Stack size for firewall exception notify tasks */
#define FWL_EXCPT_NOTIFY_TASK_STACK_SIZE  (1024U)

/* Objects for registering exception handlers */
static HwiP_Params dmscFwlExcptParams;
static HwiP_Object dmscFwlExcptObj;
static HwiP_Params cmbnFwlExcptParams;
static HwiP_Object cmbnFwlExcptObj;

/* Semaphore to notify occurence of a SYSFW fwl exception */
static SemaphoreP_Object dmscFwlExcptNotify;
/* Semaphore to notify occurence of a Combined fwl exception */
static SemaphoreP_Object cmbnFwlExcptNotify;

TaskP_Params gDmscFwlExcptNotifyTaskParams;
TaskP_Params gCmbnFwlExcptNotifyTaskParams;
TaskP_Object gDmscFwlExcptNotifyTask;
TaskP_Object gCmbnFwlExcptNotifyTask;

uint8_t gDmscFwlExcptNotifyTaskStack[FWL_EXCPT_NOTIFY_TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gCmbnFwlExcptNotifyTaskStack[FWL_EXCPT_NOTIFY_TASK_STACK_SIZE] __attribute__((aligned(32)));

/* Declaration of the SYSFW firewall exception handler */
void dmscFwlExcptHandler(void);
/* Declaration of the combined firewall exception handler */
void cmbnFwlExcptHandler(void);

void dmscFwlExcptNotifyTask(void *args);
void cmbnFwlExcptNotifyTask(void *args);

/* Function for the firewall exception notify task */
void fwl_exception_log_main(void *args)
{
    int32_t ret = SystemP_SUCCESS;

    DebugP_log("FWL Exception logging example!\r\n");

    /* Construct dmsc firewall exception notify semaphore */
    ret = SemaphoreP_constructBinary(&dmscFwlExcptNotify, 0U);
    if (SystemP_SUCCESS != ret) {
        DebugP_log("Could not construct SYSFW fwl excpt notify semaphore!\r\n");
    }

    if (SystemP_SUCCESS == ret)
    {
        /* Construct combined firewall exception notify semaphore for dmsc exceptions */
        ret = SemaphoreP_constructBinary(&cmbnFwlExcptNotify, 0U);
        if (SystemP_SUCCESS != ret) {
            DebugP_log("Could not construct CMBN fwl excpt notify semaphore!\r\n");
        }
    }

    if (SystemP_SUCCESS == ret)
    {
        /* Register handler for SYSFW firewall exceptions */
        HwiP_Params_init(&dmscFwlExcptParams);
        dmscFwlExcptParams.intNum = FWL_EXCEPTION_NOTIFY_SYSFW_FWL_EXCEPTION;
        dmscFwlExcptParams.callback = (HwiP_FxnCallback)dmscFwlExcptHandler;
        dmscFwlExcptParams.args = (void *)NULL;
        ret = HwiP_construct(&dmscFwlExcptObj, &dmscFwlExcptParams);
        if (SystemP_SUCCESS == ret)
        {
            DebugP_log("Registered handler for SYSFW firewall exception interrupt!\r\n");
        }
        else
        {
            DebugP_log("Could not register handler for SYSFW firewall exception!\r\n");
        }
    }

    if (SystemP_SUCCESS == ret)
    {
        /* Register handler for Combined firewall exceptions */
        HwiP_Params_init(&cmbnFwlExcptParams);
        cmbnFwlExcptParams.intNum = FWL_EXCEPTION_NOTIFY_CMBN_FWL_EXCEPTION;
        cmbnFwlExcptParams.callback = (HwiP_FxnCallback)cmbnFwlExcptHandler;
        cmbnFwlExcptParams.args = (void *)NULL;
        ret = HwiP_construct(&cmbnFwlExcptObj, &cmbnFwlExcptParams);
        if (SystemP_SUCCESS == ret)
        {
            DebugP_log("Registered handler for CMBN firewall exception!\r\n");
        }
        else
        {
            DebugP_log("Could not register handler for CMBN firewall exception!\r\n");
        }
    }

    if (SystemP_SUCCESS == ret)
    {
        /* Create the tasks that will wait for SYSFW firewall exception events */
        TaskP_Params_init(&gDmscFwlExcptNotifyTaskParams);
        gDmscFwlExcptNotifyTaskParams.name = "SYSFW_FW_EXP_NTFY";
        gDmscFwlExcptNotifyTaskParams.stackSize = FWL_EXCPT_NOTIFY_TASK_STACK_SIZE;
        gDmscFwlExcptNotifyTaskParams.stack = &gDmscFwlExcptNotifyTaskStack[0];
        gDmscFwlExcptNotifyTaskParams.priority = FWL_EXCPT_NOTIFY_TASK_PRI;
        gDmscFwlExcptNotifyTaskParams.args = NULL;
        gDmscFwlExcptNotifyTaskParams.taskMain = dmscFwlExcptNotifyTask;
        ret = TaskP_construct(&gDmscFwlExcptNotifyTask, &gDmscFwlExcptNotifyTaskParams);
        if (SystemP_SUCCESS == ret)
        {
            DebugP_log("Waiting for SYSFW firewall exceptions...\r\n");
        }
        else
        {
            DebugP_log("Could not create task for SYSFW firewall exceptions!\r\n");
        }
    }

    if (SystemP_SUCCESS == ret)
    {
        /* Create the tasks that will wait for CMBN firewall exception events */
        TaskP_Params_init(&gCmbnFwlExcptNotifyTaskParams);
        gCmbnFwlExcptNotifyTaskParams.name = "CMBN_FW_EXP_NTFY";
        gCmbnFwlExcptNotifyTaskParams.stackSize = FWL_EXCPT_NOTIFY_TASK_STACK_SIZE;
        gCmbnFwlExcptNotifyTaskParams.stack = &gCmbnFwlExcptNotifyTaskStack[0];
        gCmbnFwlExcptNotifyTaskParams.priority = FWL_EXCPT_NOTIFY_TASK_PRI;
        gCmbnFwlExcptNotifyTaskParams.args = NULL;
        gCmbnFwlExcptNotifyTaskParams.taskMain = cmbnFwlExcptNotifyTask;
        ret = TaskP_construct(&gCmbnFwlExcptNotifyTask, &gCmbnFwlExcptNotifyTaskParams);
        if (SystemP_SUCCESS == ret)
        {
            DebugP_log("Waiting for CMBN firewall exceptions...\r\n");
        }
        else
        {
            DebugP_log("Could not create task for CMBN firewall exceptions!\r\n");
        }
    }

}

/* SYSFW FWL Exception Handler */
void dmscFwlExcptHandler(void)
{
    SemaphoreP_post(&dmscFwlExcptNotify);
}

/* CMBN FWL Exception Handler */
void cmbnFwlExcptHandler(void)
{
    SemaphoreP_post(&cmbnFwlExcptNotify);
}

void dmscFwlExcptNotifyTask(void *args)
{
    while(SystemP_SUCCESS == SemaphoreP_pend(&dmscFwlExcptNotify, SystemP_WAIT_FOREVER))
    {
        DebugP_log("SYSFW Firewall Exception Occured!!\r\n");
    }
}

void cmbnFwlExcptNotifyTask(void *args)
{
    while(SystemP_SUCCESS == SemaphoreP_pend(&cmbnFwlExcptNotify, SystemP_WAIT_FOREVER))
    {
        DebugP_log("Combined Firewall Exception Occured!!\r\n");
    }
}