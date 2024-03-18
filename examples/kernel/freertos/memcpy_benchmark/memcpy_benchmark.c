/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modifinstructionCacheAccesstion, are permitted provided that the following conditions
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


#include <FreeRTOS.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/QueueP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/nortos/dpl/r5/PmuP_armv7r.h>
#include <kernel/nortos/dpl/r5/CacheP_armv7r.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "task.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define NUM_TASK 16
#define NUM_TEST 10
#define BUF_SIZE 2048
#define MEM_CPY_OPER 500 // min > 10 msec
#define BUFFER_IN_USE 2
#define TASK_STACK_SIZE 0x1000

#define TASK_PRI  (2u)

#if !defined (SOC_AM62X)
#define MSRAM_REGION
#endif

#ifdef MSRAM_REGION
#define TOTAL_MEM_INDEX 2
#define NUM_TASK_MSRAM 10
#else
#define TOTAL_MEM_INDEX 1
#endif

QueueP_Handle gMyQueue[NUM_TASK] __attribute__((section(".buffDdrRegion"))) ;

static TaskP_Object gMasterTaskObj __attribute__((section(".buffDdrRegion"))) ;
static TaskP_Object gSlaveTaskObj[NUM_TASK] __attribute__((section(".buffDdrRegion"))) ;

/* Array to hold all the semaphores */
SemaphoreP_Object gSemaphorePHandle[NUM_TASK] __attribute__((section(".buffDdrRegion"))) ;
SemaphoreP_Object gSemMasterTaskEndPHandle;
SemaphoreP_Object gMutexTaskNum;

typedef struct
{
    QueueP_Elem elem;
    uint32_t taskCallNumber;
}QueueMsg;



enum TestMemories {MSRAM_MEM, DDR_MEM};

/* gTaskCalls is the number of random calls to the slave tasks for different
 * test cases. This can be used to controll the runtime of the code
*/
uint32_t gTaskCalls = 500;

/* For each test case the  size of the memcpy gBuffer can be defined
 * individually. Lesser the value more is the number of cache misses per
 * second but reduced run time as the number of instructions executed
 * reduces and the memcpy instructions still remain in the cache */
uint32_t gMemcopySizeArr[NUM_TEST] = {0, 50, 100, 200, 500, 750, 1000, 1250, \
                                        1500, BUF_SIZE};

/* Variable to pick up value from the gMemcopySizeArr for each test*/
uint32_t gMemcopySize = 0;

/* Number of times each slave task must repeat the operation.
 * This can be used the control the execution time of the code without much
 * impact on the cache misses
*/
uint32_t gIteration = 1;

/* Counter for the number of sysbios task switches that occur during the
 * execution of the code
 */
uint32_t gNumSwitches = 0;


/* Source gBuffers for all the memcpy operations. They can lie in the OCMC
 * or the same memory as the code like flash. The location can be changed
 * from the linker file.
 * 'gBufTarget' is the target gBuffer for all the memcpy operations.
 */
#ifdef MSRAM_REGION
uint32_t gBuffer[NUM_TASK][BUF_SIZE] __attribute__((section(".buffMsramRegion"))) ;
uint32_t gBufTarget[BUF_SIZE] __attribute__((section(".buffMsramRegion"),aligned (32U)));
#else
uint32_t gBuffer[NUM_TASK][BUF_SIZE] __attribute__((section(".buffDdrRegion"))) ;
uint32_t gBufTarget[BUF_SIZE] __attribute__((section(".buffDdrRegion"))) ;
#endif

uint32_t gHours, gMins, gSecs, gDurationInSecs, gUSecs;
uint32_t gStartTime, gelapsedTime;
volatile uint32_t gNumTasks;

TaskP_Params gTaskParams;

/* Slave Task Function Definition. All the tasks are same
 * functionally. The only differnce is their location in the memory. They
 * are placed in the memory such that all of them occupy the same cache entry
 * in the 4-way cahce. The sections are defined in the linker cmd file
 */

#ifdef MSRAM_REGION
void SlaveTaskFxnMsram0(void *args)  __attribute__((section(".task_msram0")));
void SlaveTaskFxnMsram1(void *args)  __attribute__((section(".task_msram1")));
void SlaveTaskFxnMsram2(void *args)  __attribute__((section(".task_msram2")));
void SlaveTaskFxnMsram3(void *args)  __attribute__((section(".task_msram3")));
void SlaveTaskFxnMsram4(void *args)  __attribute__((section(".task_msram4")));
void SlaveTaskFxnMsram5(void *args)  __attribute__((section(".task_msram5")));
void SlaveTaskFxnMsram6(void *args)  __attribute__((section(".task_msram6")));
void SlaveTaskFxnMsram7(void *args)  __attribute__((section(".task_msram7")));
void SlaveTaskFxnMsram8(void *args)  __attribute__((section(".task_msram8")));
void SlaveTaskFxnMsram9(void *args)  __attribute__((section(".task_msram9")));
static uint8_t slaveTaskStackMsram[NUM_TASK_MSRAM][TASK_STACK_SIZE];
#endif

void SlaveTaskFxnDdr0(void *args)  __attribute__((section(".task_ddr0")));
void SlaveTaskFxnDdr1(void *args)  __attribute__((section(".task_ddr1")));
void SlaveTaskFxnDdr2(void *args)  __attribute__((section(".task_ddr2")));
void SlaveTaskFxnDdr3(void *args)  __attribute__((section(".task_ddr3")));
void SlaveTaskFxnDdr4(void *args)  __attribute__((section(".task_ddr4")));
void SlaveTaskFxnDdr5(void *args)  __attribute__((section(".task_ddr5")));
void SlaveTaskFxnDdr6(void *args)  __attribute__((section(".task_ddr6")));
void SlaveTaskFxnDdr7(void *args)  __attribute__((section(".task_ddr7")));
void SlaveTaskFxnDdr8(void *args)  __attribute__((section(".task_ddr8")));
void SlaveTaskFxnDdr9(void *args)  __attribute__((section(".task_ddr9")));
void SlaveTaskFxnDdr10(void *args)  __attribute__((section(".task_ddr10")));
void SlaveTaskFxnDdr11(void *args)  __attribute__((section(".task_ddr11")));
void SlaveTaskFxnDdr12(void *args)  __attribute__((section(".task_ddr12")));
void SlaveTaskFxnDdr13(void *args)  __attribute__((section(".task_ddr13")));
void SlaveTaskFxnDdr14(void *args)  __attribute__((section(".task_ddr14")));
void SlaveTaskFxnDdr15(void *args)  __attribute__((section(".task_ddr15")));

static uint8_t MainApp_TaskStack[TASK_STACK_SIZE] __attribute__((section(".buffDdrRegion"))) ;
static uint8_t slaveTaskStack[NUM_TASK][TASK_STACK_SIZE] __attribute__((section(".buffDdrRegion")));

#define CMPLX_FNCT_1 \
                denominator = 2 / gBufTarget[33] + x1; \
                sinX = sinX * 1.23454 - gBufTarget[34]; \
                gBufTarget[55] = gBufTarget[55] / gBufTarget[43]; \
                gBufTarget[33] = gBufTarget[38] / gBufTarget[23]; \
                gBufTarget[44] = gBufTarget[26] / gBufTarget[28] / gBufTarget[56] * 1.235; \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \
                denominator = 2 / gBufTarget[33] + x1; \
                sinX = sinX * 1.23454 - gBufTarget[34]; \
                gBufTarget[55] = gBufTarget[55] / gBufTarget[43]; \
                gBufTarget[33] = gBufTarget[38] / gBufTarget[23]; \
                gBufTarget[44] = gBufTarget[26] / gBufTarget[28] / gBufTarget[56] * 1.235; \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \
                denominator = 2 / gBufTarget[33] + x1; \
                sinX = sinX * 1.23454 - gBufTarget[34]; \
                gBufTarget[55] = gBufTarget[55] / gBufTarget[43]; \
                gBufTarget[33] = gBufTarget[38] / gBufTarget[23]; \
                gBufTarget[44] = gBufTarget[26] / gBufTarget[28] / gBufTarget[56] * 1.235; \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \
                denominator = 2 / gBufTarget[33] + x1; \
                sinX = sinX * 1.23454 - gBufTarget[34]; \

#define CMPLX_FNCT_2 \
                gBufTarget[53] = gBufTarget[53] + 1; \
                gBufTarget[54] = gBufTarget[54] + 1; \
                gBufTarget[55] = gBufTarget[55] + 1; \
                gBufTarget[56] = gBufTarget[56] + 1; \
                gBufTarget[57] = gBufTarget[57] + 1; \
                gBufTarget[58] = gBufTarget[58] + 1; \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \

#define CMPLX_FNCT_3 \
                gBufTarget[53] = gBufTarget[53] + 1; \
                gBufTarget[54] = gBufTarget[54] + 1; \
                gBufTarget[55] = gBufTarget[55] + 1; \
                gBufTarget[56] = gBufTarget[56] + 1; \
                gBufTarget[57] = gBufTarget[57] + 1; \
                gBufTarget[58] = gBufTarget[58] + 1; \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \

#define CMPLX_FNCT_4 \
                gBufTarget[43] = gBufTarget[53] + 1; \
                gBufTarget[44] = gBufTarget[54] + 1; \
                gBufTarget[45] = gBufTarget[55] + 1; \
                gBufTarget[46] = gBufTarget[56] + 1; \
                gBufTarget[47] = gBufTarget[57] + 1; \
                gBufTarget[48] = gBufTarget[58] + 1; \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \

/* The function definition for all the tasks.  */
#define TSKFN \
    QueueMsg* qMsgObj; \
    int i,j, arrNumber,m; \
    uint32_t argValue = *(uint32_t *)args; \
    while(1) \
    { \
        SemaphoreP_pend(&gSemaphorePHandle[(uint32_t)argValue], SystemP_WAIT_FOREVER); \
        while (QueueP_EMPTY != QueueP_isEmpty(gMyQueue[(uint32_t)argValue])) \
        { \
            qMsgObj = QueueP_get(gMyQueue[(uint32_t)argValue]); \
            for (i = 0; i < gIteration; ++i) \
            { \
                arrNumber = (rand()%gNumTasks) % BUFFER_IN_USE; \
                for (j = 0; j < gMemcopySize; ++j) \
                { \
                    gBufTarget[j] = gBuffer[arrNumber][j]; \
                } \
                /*sin calculation*/ \
                float denominator, sinX;  \
                float n = 30;        \
                n = n * (3.142 / 180.0);   \
                float x1 = n;  \
                sinX = n;           \
                m = 1;  \
                denominator = 2 * m * (2 * m + 1);  \
                x1 = -x1 * n * n / denominator;  \
                sinX = sinX + x1;  \
                m =  + 1;  \
                gBufTarget[23] = gBufTarget[23] + 1; \
                gBufTarget[24] = gBufTarget[24] + 1; \
                gBufTarget[25] = gBufTarget[25] + 1; \
                gBufTarget[26] = gBufTarget[26] + 1; \
                gBufTarget[27] = gBufTarget[27] + 1; \
                gBufTarget[28] = gBufTarget[28] + 1; \
                gBufTarget[29] = gBufTarget[29] + 1; \
                gBufTarget[30] = gBufTarget[30] + 1; \
                gBufTarget[31] = gBufTarget[31] + 1; \
                gBufTarget[32] = gBufTarget[32] + 1; \
                gBufTarget[33] = gBufTarget[33] + 1; \
                gBufTarget[34] = gBufTarget[34] + 1; \
                gBufTarget[35] = gBufTarget[35] + 1; \
                gBufTarget[36] = gBufTarget[36] + 1; \
                gBufTarget[37] = gBufTarget[37] + 1; \
                gBufTarget[38] = gBufTarget[38] + 1; \
                gBufTarget[39] = gBufTarget[39] + 1; \
                gBufTarget[40] = gBufTarget[40] + 1; \
                gBufTarget[41] = gBufTarget[41] + 1; \
                gBufTarget[42] = gBufTarget[42] + 1; \
                gBufTarget[43] = gBufTarget[43] + 1; \
                gBufTarget[44] = gBufTarget[44] + 1; \
                gBufTarget[45] = gBufTarget[45] + 1; \
                gBufTarget[46] = gBufTarget[46] + 1; \
                gBufTarget[47] = gBufTarget[47] + 1; \
                gBufTarget[48] = gBufTarget[48] + 1; \
                gBufTarget[49] = gBufTarget[49] + 1; \
                gBufTarget[50] = gBufTarget[50] + 1; \
                gBufTarget[51] = gBufTarget[51] + 1; \
                gBufTarget[52] = gBufTarget[52] + 1; \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_4 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_4 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_4 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_2 \
                CMPLX_FNCT_1 \
                CMPLX_FNCT_3 \
                CMPLX_FNCT_3 \
            } \
            qMsgObj->taskCallNumber = qMsgObj->taskCallNumber + 1; \
        } \
        SemaphoreP_post(&gSemaphorePHandle[(uint32_t)argValue]); \
        TaskP_yield(); \
    }

/* Master task which will call the slave tasks randomly*/
void MasterTask(void *args)
{
    DebugP_log("\n\rMaster_task\n\r");
    uint32_t instructionCacheMiss, instructionCacheAccess, instructionCount, dataCacheMiss;
    QueueMsg r[NUM_TASK];
    int i, j;
    uint32_t set = 0, way = 0;
    uint32_t numSets,numWays;
    QueueP_Object qObj;
    uint32_t count = 0;

    for (i = 0; i < gNumTasks; ++i)
    {
        gMyQueue[i] = QueueP_create(&qObj);
    }

    DebugP_log("\n\rMaster_task -- start sending\n\r");

    /* this loop is for NUM_TEST with the specified task calls and memcpy_size*/
    for (i = 0; i < NUM_TEST; ++i)
    {
        /* counter to track the task calls already made*/
        count = 0;
        /*reset the value of task switch for that test*/
        gNumSwitches = 0;
        /* number of times each task should repeat its operation*/
        gIteration = 1;

        /* size of the memcpy to be performed by each task*/
        gMemcopySize = gMemcopySizeArr[i];
        /*invalidate all the cache to get fresh and reliable data*/
        numSets = CacheP_GetNumSets();
        numWays = CacheP_GetNumWays();
	    for (set = 0; set < numSets; set ++)
        {
            for (way = 0; way < numWays; way++)
            {
                CacheP_CleanInvalidateDcacheSetWay(set, way);
            }
        }

        CacheP_invL1pAll();

        /* reset the PMU counters to get relevant data */
        PmuP_ResetCounters();
        /* Wait for the cores to sync up (empty function if MULTICORE is not defined) */
        //multicore_wait();
        gStartTime = ClockP_getTimeUsec();

        /*start sending signals and messages to tasks*/
        while(count < gTaskCalls)
        {
            /* Get a random task number*/
            j = rand()%gNumTasks;
            r[j].taskCallNumber = count++;
            /* Add the message to the queue of the task */
            QueueP_put(gMyQueue[j], &(r[j].elem));
            /* Signal the task to start executing */
            SemaphoreP_post(&gSemaphorePHandle[j]);

            /* Yield the CPU for the other task to execute*/
            TaskP_yield();
            /* Wait for the task to complete */

            SemaphoreP_pend(&gSemaphorePHandle[j], SystemP_WAIT_FOREVER);
        }

        gelapsedTime = ClockP_getTimeUsec() - gStartTime;
        gDurationInSecs = ((gelapsedTime) / 1000U);
        gHours  = gDurationInSecs / (60U * 60U);
        gMins = (gDurationInSecs / 60U) - (gHours * 60U);
        gSecs = gDurationInSecs - (gHours * 60U * 60U) - (gMins * 60U);
        gUSecs = gelapsedTime - (((gHours * 60U * 60U) + (gMins * 60U) + gSecs) * 1000000U);

        /* Read the value of the PMU counters and print the result */
        instructionCacheMiss = PmuP_ReadCounter(0);
        instructionCacheAccess = PmuP_ReadCounter(2);
	    instructionCount = PmuP_ReadCounter(1);
        dataCacheMiss = PmuP_ReadCounter(3);
        DebugP_log("\r\nMemCopy Size : %d\r\n", (unsigned int) gMemcopySize);
        DebugP_log("Exec Time in Usec : %d\r\n", (unsigned int) gelapsedTime);
        DebugP_log("Iteration : %d\r\n", (unsigned int) gIteration);
        DebugP_log("Task Calls : %d\r\n",  gTaskCalls);
        DebugP_log("Instruction Cache Miss : %d\r\n",  instructionCacheMiss);
        DebugP_log("Instruction Cache Access : %d\r\n",  instructionCacheAccess);
        DebugP_log("Number of Instructions Executed : %d\r\n",  instructionCount);
        DebugP_log("Data Cache Miss : %d\r\n",  instructionCacheMiss);
        DebugP_log("InstructionCacheMiss/sec : %u\r\n", (unsigned int) (1000000 * ((float) (instructionCacheMiss*1.0)/(gelapsedTime*1.0))));  // (unsigned long)  ((uint64_t)instructionCacheMiss*1000000)/((uint64_t)gelapsedTime));
        DebugP_log("Instructions/sec : %u\r\n", (unsigned int) (1000000 * ((float) (instructionCount*1.0)/(gelapsedTime*1.0))));
        DebugP_log("DataCacheMiss/sec : %u\r\n", (unsigned int) (1000000 * ((float) (dataCacheMiss*1.0)/(gelapsedTime*1.0))));  // (unsigned long)  ((uint64_t)instructionCacheMiss*1000000)/((uint64_t)gelapsedTime));
    }

    DebugP_log("\r\nAll tests have passed!!\r\n");

    for (i = 0; i < gNumTasks; ++i)
    {
        TaskP_destruct(&gSlaveTaskObj[i]);
    }

    SemaphoreP_post(&gSemMasterTaskEndPHandle); //Signal to memcpy_benchmark_main task that Master task ends
    TaskP_destruct(&gMasterTaskObj);
}

void memcpy_benchmark_main(void *args)
{
    int i,j;
#ifdef MSRAM_REGION
    uint8_t testMemories[TOTAL_MEM_INDEX] = {MSRAM_MEM, DDR_MEM};
#else
    uint8_t testMemories[TOTAL_MEM_INDEX] = {DDR_MEM};
#endif
    uint32_t countVal0,countVal1,countVal2,countVal3;
    int32_t status;
    /*task Function pointer array*/
    void *tasks[NUM_TASK];
    void *taskStacks[NUM_TASK];

    PmuP_ResetCounters();
    PmuP_Config(0,0,1);
    PmuP_EnableAllCounters(1);
    PmuP_ConfigCounter(0, PmuP_EVENT_TYPE_ICACHE_MISS);
    PmuP_ConfigCounter(1, PmuP_EVENT_TYPE_I_X);
    PmuP_ConfigCounter(2, PmuP_EVENT_TYPE_ICACHE_ACCESS);
    PmuP_ConfigCounter(3, PmuP_EVENT_TYPE_DCACHE_MISS);

    PmuP_EnableCounterOverflowInterrupt(0, 0);
    PmuP_EnableCounterOverflowInterrupt(1, 0);
    PmuP_EnableCounterOverflowInterrupt(2, 0);
    PmuP_EnableCounterOverflowInterrupt(3, 0);

    SemaphoreP_constructMutex(&gMutexTaskNum);

    for(int memIndex = 0; memIndex< TOTAL_MEM_INDEX; memIndex++)
    {
        PmuP_ResetCounters();
        PmuP_enableCounter(0, 1);
        PmuP_enableCounter(1, 1);
        PmuP_enableCounter(2, 1);
        PmuP_enableCounter(3, 1);

        switch(testMemories[memIndex])
        {
#ifdef MSRAM_REGION
            case MSRAM_MEM:
                DebugP_log("\r\nMemcpy Benchmarking for MSRAM memory:\r\n");
                SemaphoreP_pend(&gMutexTaskNum, SystemP_WAIT_FOREVER);
                gNumTasks = NUM_TASK_MSRAM;
                SemaphoreP_post(&gMutexTaskNum);
                tasks[0] = SlaveTaskFxnMsram0;
                tasks[1] = SlaveTaskFxnMsram1;
                tasks[2] = SlaveTaskFxnMsram2;
                tasks[3] = SlaveTaskFxnMsram3;
                tasks[4] = SlaveTaskFxnMsram4;
                tasks[5] = SlaveTaskFxnMsram5;
                tasks[6] = SlaveTaskFxnMsram6;
                tasks[7] = SlaveTaskFxnMsram7;
                tasks[8] = SlaveTaskFxnMsram8;
                tasks[9] = SlaveTaskFxnMsram9;
                break;
#endif
        case DDR_MEM:
                DebugP_log("\r\nMemcpy Benchmarking for DDR memory:\r\n");
                SemaphoreP_pend(&gMutexTaskNum, SystemP_WAIT_FOREVER);
                gNumTasks = NUM_TASK;
                SemaphoreP_post(&gMutexTaskNum);
                tasks[0] = SlaveTaskFxnDdr0;
                tasks[1] = SlaveTaskFxnDdr1;
                tasks[2] = SlaveTaskFxnDdr2;
                tasks[3] = SlaveTaskFxnDdr3;
                tasks[4] = SlaveTaskFxnDdr4;
                tasks[5] = SlaveTaskFxnDdr5;
                tasks[6] = SlaveTaskFxnDdr6;
                tasks[7] = SlaveTaskFxnDdr7;
                tasks[8] = SlaveTaskFxnDdr8;
                tasks[9] = SlaveTaskFxnDdr9;
                tasks[10] = SlaveTaskFxnDdr10;
                tasks[11] = SlaveTaskFxnDdr11;
                tasks[12] = SlaveTaskFxnDdr12;
                tasks[13] = SlaveTaskFxnDdr13;
                tasks[14] = SlaveTaskFxnDdr14;
                tasks[15] = SlaveTaskFxnDdr15;
                break;
        }

        for (i = 0; i < gNumTasks; ++i)
        {
#ifdef MSRAM_REGION
            if(gNumTasks == NUM_TASK)
            {
                taskStacks[i] = slaveTaskStack[i];
            }
            else
            {
                taskStacks[i] = slaveTaskStackMsram[i];
            }
#else
            taskStacks[i] = slaveTaskStack[i];
#endif
        }

        /* Filling up the gBuffers with if they do not lie in the flash */
        DebugP_log("Filling up the gBuffers\r\n");
        for (i = 0; i < gNumTasks; ++i)
        {
            for (j = 0; j < BUF_SIZE; ++j)
            {
                gBuffer[i][j] = j;
            }
        }

        for (i = 0; i < gNumTasks; ++i)
        {
            status = SemaphoreP_constructBinary(&gSemaphorePHandle[i], 0);
            DebugP_assert(SystemP_SUCCESS == status);

        }

        status = SemaphoreP_constructBinary(&gSemMasterTaskEndPHandle, 0);
        DebugP_assert(SystemP_SUCCESS == status);

        PmuP_ResetCounters();
        countVal0 = PmuP_ReadCounter(0);
        countVal2 = PmuP_ReadCounter(2);
        countVal1 = PmuP_ReadCounter(1);
        countVal3 = PmuP_ReadCounter(3);

        /* Sanity checking for PMU counters*/
        DebugP_log("Sanity checking for PMU counters\r\n");
        DebugP_log("Inst Cache Miss: %u\r\n", countVal0);
        DebugP_log("Inst Cache Access: %u\r\n", countVal2);
        DebugP_log("Number of instructions: %u\r\n", countVal1);
        DebugP_log("Data Cache Miss: %u\r\n", countVal3);

        TaskP_Params_init(&gTaskParams);
        gTaskParams.name = "masterTask";
        gTaskParams.stackSize = TASK_STACK_SIZE;
        gTaskParams.stack = &MainApp_TaskStack[0];
        gTaskParams.priority = TASK_PRI;
        gTaskParams.taskMain = MasterTask;

        status = TaskP_construct(&gMasterTaskObj, &gTaskParams);
        DebugP_assert(SystemP_SUCCESS == status);
        DebugP_log("Created MasterTask\r\n");

        for (i = 0; i < gNumTasks; ++i)
        {
            gTaskParams.args = (void *) &i;
            gTaskParams.stack = &slaveTaskStack[i][0];
            gTaskParams.taskMain = tasks[i];

            status = TaskP_construct(&gSlaveTaskObj[i], &gTaskParams);
            DebugP_assert(SystemP_SUCCESS == status);
            if(i == gNumTasks-1)
            {
                DebugP_log("Created all %d slaveTasks\r\n",gNumTasks-1);
            }
        }

        SemaphoreP_pend(&gSemMasterTaskEndPHandle, SystemP_WAIT_FOREVER);

    }
    return;
}

#ifdef MSRAM_REGION
/*From msram*/
void SlaveTaskFxnMsram0(void *args)
{TSKFN}

void SlaveTaskFxnMsram1(void *args)
{TSKFN}

void SlaveTaskFxnMsram2(void *args)
{TSKFN}

void SlaveTaskFxnMsram3(void *args)
{TSKFN}

void SlaveTaskFxnMsram4(void *args)
{TSKFN}

void SlaveTaskFxnMsram5(void *args)
{TSKFN}

void SlaveTaskFxnMsram6(void *args)
{TSKFN}

void SlaveTaskFxnMsram7(void *args)
{TSKFN}

void SlaveTaskFxnMsram8(void *args)
{TSKFN}

void SlaveTaskFxnMsram9(void *args)
{TSKFN}
#endif
/*From DDR*/
void SlaveTaskFxnDdr0(void *args)
{TSKFN}

void SlaveTaskFxnDdr1(void *args)
{TSKFN}

void SlaveTaskFxnDdr2(void *args)
{TSKFN}

void SlaveTaskFxnDdr3(void *args)
{TSKFN}

void SlaveTaskFxnDdr4(void *args)
{TSKFN}

void SlaveTaskFxnDdr5(void *args)
{TSKFN}

void SlaveTaskFxnDdr6(void *args)
{TSKFN}

void SlaveTaskFxnDdr7(void *args)
{TSKFN}

void SlaveTaskFxnDdr8(void *args)
{TSKFN}

void SlaveTaskFxnDdr9(void *args)
{TSKFN}

void SlaveTaskFxnDdr10(void *args)
{TSKFN}

void SlaveTaskFxnDdr11(void *args)
{TSKFN}

void SlaveTaskFxnDdr12(void *args)
{TSKFN}

void SlaveTaskFxnDdr13(void *args)
{TSKFN}

void SlaveTaskFxnDdr14(void *args)
{TSKFN}

void SlaveTaskFxnDdr15(void *args)
{TSKFN}