/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 #ifndef TEST_EXECUTE_H_
 #define TEST_EXECUTE_H_

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include <stdint.h>
#include <unity.h>

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

/* SOC index mapping */
enum
{
    TEST_SOC_IDX_DEFAULT = 0,
    TEST_SOC_IDX_AM62AX,
    TEST_SOC_IDX_AM62DX,
    TEST_SOC_IDX_AM62LX,
    TEST_SOC_IDX_AM62PX,
    TEST_SOC_IDX_AM62X,
    TEST_SOC_IDX_AM275X,
    TEST_SOC_IDX_J722S,
    TEST_SOC_COUNT
};

/* CORE index mapping */
enum
{
    TEST_CORE_IDX_DEFAULT = 0,
    TEST_CORE_IDX_A53,
    TEST_CORE_IDX_R5F0,
    TEST_CORE_IDX_MCU_R5F0,
    TEST_CORE_IDX_C7X,
    TEST_CORE_IDX_C75_0,
    TEST_CORE_IDX_C75_1,
    TEST_CORE_IDX_R5F0_0,
    TEST_CORE_IDX_R5F0_1,
    TEST_CORE_IDX_R5F1_0,
    TEST_CORE_IDX_R5F1_1,
    TEST_CORE_COUNT
};

/* CORE index mapping */
enum
{
    TEST_INSTANCE_COUNT_0 = 0,
    TEST_INSTANCE_COUNT_1,
    TEST_INSTANCE_COUNT_2,
    TEST_INSTANCE_COUNT_3,
    TEST_INSTANCE_COUNT_4,
    TEST_INSTANCE_COUNT_5,
    TEST_INSTANCE_COUNT_6,
    TEST_INSTANCE_COUNT_7,
    TEST_INSTANCE_COUNT_8,
    TEST_INSTANCE_COUNT
};

/* Derive current SOC index from build-time defines */
#if defined(SOC_AM62AX)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM62AX
#elif defined(SOC_AM62DX)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM62DX
#elif defined(SOC_AM62LX)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM62LX
#elif defined(SOC_AM62PX)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM62PX
#elif defined(SOC_AM62X)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM62X
#elif defined(SOC_AM275X)
#define TEST_SOC_INDEX TEST_SOC_IDX_AM275X
#elif defined(SOC_J722S)
#define TEST_SOC_INDEX TEST_SOC_IDX_J722S
#else
#define TEST_SOC_INDEX TEST_SOC_IDX_DEFAULT
#endif

/* Derive current CORE index from build-time defines */
#if defined(CPU_A53)
#define TEST_CORE_INDEX TEST_CORE_IDX_A53
#elif defined(CPU_R5F0)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F0
#elif defined(CPU_MCU_R5F0)
#define TEST_CORE_INDEX TEST_CORE_IDX_MCU_R5F0
#elif defined(CPU_C7X)
#define TEST_CORE_INDEX TEST_CORE_IDX_C7X
#elif defined(CPU_C75_0)
#define TEST_CORE_INDEX TEST_CORE_IDX_C75_0
#elif defined(CPU_C75_1)
#define TEST_CORE_INDEX TEST_CORE_IDX_C75_1
#elif defined(CPU_R5F0_0)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F0_0
#elif defined(CPU_R5F0_1)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F0_1
#elif defined(CPU_R5F1_0)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F1_0
#elif defined(CPU_R5F1_1)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F1_1
#elif defined(CPU_WKUP_R5F)
#define TEST_CORE_INDEX TEST_CORE_IDX_R5F0
#else
#define TEST_CORE_INDEX TEST_CORE_IDX_DEFAULT
#endif

#define TEST_PP_RSEQ_N() 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define TEST_PP_ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16, N, ...) N
#define TEST_PP_NARG_(...) TEST_PP_ARG_N(__VA_ARGS__)
#define TEST_PP_NARG(...)  TEST_PP_NARG_(__VA_ARGS__, TEST_PP_RSEQ_N())

#define TEST_EXECUTE_TEST_CASE_SELECT(N) TEST_EXECUTE_TEST_CASE_##N
#define TEST_EXECUTE_TEST_CASE_DISPATCH(N, ...) TEST_EXECUTE_TEST_CASE_SELECT(N)(__VA_ARGS__)
#define TEST_EXECUTE_TEST_CASE(...)  TEST_EXECUTE_TEST_CASE_DISPATCH(TEST_PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define TEST_EXECUTE_SKIP_ENTRY_SELECT(N) TEST_EXECUTE_SKIP_ENTRY_##N
#define TEST_EXECUTE_SKIP_ENTRY_DISPATCH(N, ...) TEST_EXECUTE_SKIP_ENTRY_SELECT(N)(__VA_ARGS__)
#define TEST_EXECUTE_SKIP_ENTRY(...) TEST_EXECUTE_SKIP_ENTRY_DISPATCH(TEST_PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define TEST_EXECUTE_SKIP_IDS(name, ...) static const uint16_t name[] = { __VA_ARGS__ };

typedef struct {
    const uint16_t *ids;   /* pointer to list of test IDs to skip */
    uint16_t        count; /* number of entries in ids */
} TestExecute_idList;

__attribute__((weak)) const TestExecute_idList TestExecute_SkipTestIdMatrix[TEST_SOC_COUNT][TEST_CORE_COUNT] = { { { NULL, 0 } } };
__attribute__((weak)) const TestExecute_idList TestExecute_SkipTestIdMatrixWithInstance[TEST_SOC_COUNT][TEST_CORE_COUNT][TEST_INSTANCE_COUNT] = { { { { NULL, 0} } } };

#define TEST_EXECUTE_TEST_CASE_3(testFunction, testId, testArgs)                                            \
    do                                                                                                      \
    {                                                                                                       \
        const TestExecute_idList *list1 = &TestExecute_SkipTestIdMatrix[TEST_SOC_INDEX][TEST_CORE_INDEX];   \
        uint16_t _skip1 = 0;                                                                                \
        uint16_t counter1 = 0;                                                                              \
        if (list1 && list1->ids && list1->count)                                                            \
        {                                                                                                   \
            for (counter1 = 0; counter1 < list1->count; counter1++)                                         \
            {                                                                                               \
                if (list1->ids[counter1] == (uint16_t)(testId))                                             \
                {                                                                                           \
                    _skip1 = 1;                                                                             \
                    break;                                                                                  \
                }                                                                                           \
            }                                                                                               \
        }                                                                                                   \
        if (!_skip1)                                                                                        \
        {                                                                                                   \
            RUN_TEST(testFunction, testId, testArgs);                                                       \
        }                                                                                                   \
        else                                                                                                \
        {                                                                                                   \
            DebugP_log("Skipped test ID %d\n\r", testId);                                                       \
        }                                                                                                   \
    } while(0)

#define TEST_EXECUTE_TEST_CASE_4(testFunction, testId, testArgs, instance)                                                          \
    do                                                                                                                              \
    {                                                                                                                               \
        const TestExecute_idList *list2 = &TestExecute_SkipTestIdMatrixWithInstance[TEST_SOC_INDEX][TEST_CORE_INDEX][instance];     \
        uint16_t skip2 = 0;                                                                                                         \
        uint16_t counter2;                                                                                                          \
        if (list2 && list2->ids && list2->count)                                                                                    \
        {                                                                                                                           \
            for (counter2 = 0; counter2 < list2->count; counter2++)                                                                 \
            {                                                                                                                       \
                if (list2->ids[counter2] == (uint16_t)(testId))                                                                     \
                {                                                                                                                   \
                    skip2 = 1;                                                                              \
                    break;                                                                                  \
                }                                                                                           \
            }                                                                                               \
        }                                                                                                   \
        if (!skip2)                                                                                         \
        {                                                                                                   \
            RUN_TEST(testFunction, testId, testArgs);                                                       \
        }                                                                                                   \
        else                                                                                                \
        {                                                                                                   \
            DebugP_log("Skipped test ID %d for instance %d\n\r", testId, instance);                             \
        }                                                                                                   \
    } while(0)

/* Helper to emit one matrix entry using a 2D designator */
#define TEST_EXECUTE_SKIP_ENTRY_3(SOC_IDX, CORE_IDX, TC_ID)             \
    [SOC_IDX][CORE_IDX] =                                               \
    {                                                                   \
        .ids = TC_ID,                                                   \
        .count = (uint16_t)(sizeof(TC_ID)/sizeof((TC_ID)[0]))           \
    }

#define TEST_EXECUTE_SKIP_ENTRY_4(SOC_IDX, CORE_IDX, INSTANCE, TC_ID)   \
    [SOC_IDX][CORE_IDX][INSTANCE] =                                     \
    {                                                                   \
        .ids = TC_ID,                                                   \
        .count = (uint16_t)(sizeof(TC_ID)/sizeof((TC_ID)[0]))           \
    }

#endif /*  */
