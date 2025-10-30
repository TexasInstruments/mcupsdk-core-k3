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

/**\file test_mmcsd_raw_io.c
 *
 * \brief Test application for MMCSD raw I/O operations.
 *
 * This file contains test routines to validate file input/output functionality
 * using the MMCSD driver in the MCU+ SDK.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "mmcsd_test_common.h"
#include "mmcsd_test_raw.h"

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
* \brief Setup fuction for unity framework
*
* \param None.
*
* \return None.
*/
void setUp(void)
{
    /* Setup function nothing to perform */
}

/**
* \brief Tear down fuction for unity framework
*
* \param None.
*
* \return None.
*/
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

/**
* \brief Main fuction for unity framework
*
* \param None.
*
* \return None.
*/
void test_main(void *args)
{
    Drivers_mmcsdClose();
    UNITY_BEGIN();

    RUN_TEST(Test_Mmcsd_EmmcRawIo, 3017, NULL);
    RUN_TEST(Test_Mmcsd_EmmcEnableDisableBootPartition, 8308, NULL);
    RUN_TEST(Test_Mmcsd_EmmcTuningConfig, 8312, NULL);
    RUN_TEST(Test_Mmcsd_EmmcMultiblockRawIo, 8306, NULL);
    RUN_TEST(Test_Mmcsd_OpenInvalidInstance, 8309, NULL);
#if !defined (SOC_AM275X) && !defined (SOC_J722S)
    RUN_TEST(Test_Mmcsd_SdRawIo, 1942, NULL);
    RUN_TEST(Test_Mmcsd_SdTuningConfig, 8313, NULL);
    RUN_TEST(Test_Mmcsd_EmmcMultiplePhyconfig, 8339, NULL);
    RUN_TEST(Test_Mmcsd_GetBlockCountValidate, 8580, NULL);
    RUN_TEST(Test_Mmcsd_MultipleOpenClose, 8579, NULL);
#if !defined (C7_CORE)
    RUN_TEST(Test_Mmcsd_ValidateClkFreq, 8310, NULL);
#endif
    /* This test fails and hangs when we pass NULL buffer to read
    RUN_TEST(Test_Mmcsd_ReadArgumentValidate, 8582, NULL);
    */
    /* This test fails and hangs when we pass NULL buffer to write
    RUN_TEST(Test_Mmcsd_WriteArgumentValidate, 8583, NULL);
    */
    /* This test hangs when DMA is disabled
    RUN_TEST(Test_Mmcsd_DmaModes, 8315, NULL);
    */
    /* This test hangs when bus width is 1
    RUN_TEST(Test_Mmmcsd_SdMultipleBusWidths, 8311, NULL);
    */
    /* This test hangs when bus width is 1 and 4
    RUN_TEST(Test_Mmmcsd_EmmcMultipleBusWidths, 8581, NULL);
    */
    /* This test hangs on execution
    RUN_TEST(Test_Mmcsd_OpenOpenFail, 8584, NULL);
    */
#endif
    UNITY_END();
}

