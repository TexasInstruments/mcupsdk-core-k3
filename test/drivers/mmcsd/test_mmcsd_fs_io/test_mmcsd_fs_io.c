/*
 * Copyright (C) 2021-25 Texas Instruments Incorporated
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

/**\file test_mmcsd_file_io.c
 *
 * \brief Test application for MMCSD file I/O operations.
 *
 * This file contains test routines to validate file input/output functionality
 * using the MMCSD driver in the MCU+ SDK.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "mmcsd_test_common.h"
#include "mmcsd_test_fs.h"

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * \brief Setup function for unity framework
 *
 * \param None.
 *
 * \return None.
 */
void setUp(void)
{
    /* Setup function nothing to execute */
}

/**
 * \brief Tear down function for unity framework
 *
 * \param None.
 *
 * \return None.
 */
void tearDown(void)
{
    /* Setup function nothing to execute */
}

/**
 * \brief Main function for unity framework
 *
 * \param None.
 *
 * \return None.
 */
void test_main(void *args)
{
    Drivers_mmcsdClose();
    UNITY_BEGIN();

    RUN_TEST(Test_Mmcsd_EmmcFileIo, 6630, NULL);
    RUN_TEST(Test_Mmcsd_EmmcNestedDirectories,  8317, NULL);
#if defined(ENABLE_MT_TESTS)
    /* This is a same instance multi threading test case which hangs
     *RUN_TEST(Test_Mmcsd_ConcurrentFatEmmcTransfer,  8341, NULL);
     */
    /* This is a same instance multi threading test case which hangs
     *RUN_TEST(Test_Mmcsd_ConcurrentFatSdTransfer,  8340, NULL);
     */
    RUN_TEST(Test_Mmcsd_testConcurrentFatEmmcSdTransfer,  8323, NULL);
    RUN_TEST(Test_Mmcsd_SdFileIo,  8342, NULL);
    RUN_TEST(Test_Mmcsd_SdNestedDirectories,  8329, NULL);
#if !defined (SOC_AM275X) && !defined (C7_CORE)
    RUN_TEST(Test_Mmcsd_LargeSdFileIo,  1948, NULL);
#endif
#endif

    UNITY_END();
}

