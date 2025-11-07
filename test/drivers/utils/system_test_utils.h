/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file system_test_utils.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the system test framework (multi core)
 *
 */

#ifndef SYSTEM_TEST_UTILS_H_
#define SYSTEM_TEST_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/** \brief  Maximum wait time (ms) for execution of test case in remote core */
#define TEST_MAX_EXECUTION_TIME (20000u)

/** \brief  Macro to enable support for debugging System test cases */
#define TEST_ENABLE_SYSTEM_DEBUG (0)

/** \brief  Macro to define ID of test case for debugging */
#define TEST_DEBUG_TC_ID (0)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Function pointer type for test cases
 */
typedef int32_t (*testCaseFunction_t)(void *args);

/**
 * \brief  Structure for holding test case information
 */
typedef struct testCase{
    testCaseFunction_t testFptr;
    /**< function pointer for test case */
    int32_t      testCaseId;
    /**< test case ID */
} testCase_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* Externs */
extern testCase_t gTestCase[];


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
extern int32_t TestUtils_dummyTestCase(void *args);
extern int32_t TestUtils_syncRemoteCore(uint32_t remoteCoreId, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SYSTEM_TEST_UTILS_H_ */
