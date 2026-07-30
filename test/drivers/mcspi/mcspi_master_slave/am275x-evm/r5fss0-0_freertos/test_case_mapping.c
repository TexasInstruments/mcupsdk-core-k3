/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
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
 *  \file test_case_mapping.c
 *
 *  \brief This file contains mapping of test case IDs to test functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "system_test_utils.h"
#include "test_mcspi_master.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TEST_MCSPI_SLAVE_CORE_ID      (CSL_CORE_ID_C75SS0_0)
#define TEST_MCSPI_MASTER_CORE_ID     (CSL_CORE_ID_R5FSS0_0)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
testCase_t gTestCase[] =
{
    {TestMcspi_masterTest1, 8650},
    {TestMcspi_masterTest2, 8651},
    {TestMcspi_masterTest2, 8652},
    {TestMcspi_masterTest2, 8653},
    {TestMcspi_masterTest2, 8654},
    {TestMcspi_masterTest2, 8655},
    {TestMcspi_masterTest2, 8656},
    {TestMcspi_masterTest2, 8657},
    {TestMcspi_masterTest2, 8658},
    {TestMcspi_masterTest2, 8659},
    {TestMcspi_masterTest2, 8660},
    {TestMcspi_masterTest2, 8661},
    {TestMcspi_masterTest2, 8662},
    {TestMcspi_masterTest3, 8663},
    {TestMcspi_masterTest4, 8664},
    {TestMcspi_masterTest2, 8665},
    {TestMcspi_masterTest2, 8666},
    {TestMcspi_masterTest2, 8667},
    {TestMcspi_masterTest2, 8668},
    {TestMcspi_masterTest2, 8669},
    {TestMcspi_masterTest2, 8670},
    {TestMcspi_masterTest2, 8671},
    {TestMcspi_masterTest2, 8673},
    {TestMcspi_masterTest2, 8674},
    {TestMcspi_masterTest2, 8675},
    {TestMcspi_masterTest2, 8676},
    {TestMcspi_masterTest3, 8677},
    {TestMcspi_masterTest4, 8678},
    {TestMcspi_masterTest5, 8679},
    {TestMcspi_masterTest2, 8680},
    {TestMcspi_masterTest6, 8681},
    {NULL, 0}
};

/* ========================================================================== */
/*                              Function Definitions                          */
/* ========================================================================== */

uint32_t get_master_core_id(void)
{
    return TEST_MCSPI_MASTER_CORE_ID;
}

uint32_t get_slave_core_id(void)
{
    return TEST_MCSPI_SLAVE_CORE_ID;
}

