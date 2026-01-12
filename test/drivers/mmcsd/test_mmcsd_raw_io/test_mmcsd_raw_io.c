/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
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

    RUN_TEST(TestMmcsd_emmcRawIo, 3017, NULL);
    RUN_TEST(TestMmcsd_emmcEnableDisableBootPartition, 8308, NULL);
    RUN_TEST(TestMmcsd_sdEnableDisableBootPartition, 9031, NULL);
    RUN_TEST(TestMmcsd_emmcEnableDisableBootPartitionFail, 9032, NULL);
    RUN_TEST(TestMmcsd_emmcTuningConfig, 8312, NULL);
    RUN_TEST(TestMmcsd_emmcMultiblockRawIo, 8306, NULL);
    RUN_TEST(TestMmcsd_openInvalidInstance, 8309, NULL);
#if !defined (SOC_AM275X) && !defined (SOC_J722S)
    RUN_TEST(TestMmcsd_sdSingleBlockTransfer, 9034, NULL);
    RUN_TEST(TestMmcsd_sdRawIo, 1942, NULL);
    RUN_TEST(TestMmcsd_sdTuningConfig, 8313, NULL);
    RUN_TEST(TestMmcsd_emmcMultiplePhyconfig, 8339, NULL);
    RUN_TEST(TestMmcsd_getBlockCountValidate, 8580, NULL);
    RUN_TEST(TestMmcsd_multipleOpenClose, 8579, NULL);
    RUN_TEST(TestMmcsd_validateClkFreq, 8310, NULL);
    RUN_TEST(TestMmcsd_readArgumentValidate, 8582, NULL);
    RUN_TEST(TestMmcsd_writeArgumentValidate, 8583, NULL);
    RUN_TEST(TestMmcsd_dmaModes, 8315, NULL);
    /* This test fails causing next test cases to fail
    RUN_TEST(TestMmcsd_intrModes, 8881, NULL);
    */
    /* This test fails for bus width 1
    RUN_TEST(TestMmcsd_sdMultipleBusWidths, 8311, NULL);
    */
    /* This test fails for bus width is 1 and 4
    RUN_TEST(TestMmcsd_emmcMultipleBusWidths, 8581, NULL);
    */
    /* This test fails for unaligned buffer R/W
    RUN_TEST(TestMmcsd_unalignedBuffersRawIo, 8690, NULL);
    */
    RUN_TEST(TestMmcsd_openOpenFail, 8584, NULL);
    RUN_TEST(TestMmcsd_emmcSpeedSwitch, 8689, NULL);
#if !defined (C7_CORE)
    RUN_TEST(TestMmcsd_emmcWriteReadBootPartition, 8691, NULL);
    RUN_TEST(TestMmcsd_emmcWriteReadBootPartitionFail, 9036, NULL);
#endif
    RUN_TEST(TestMmcsd_crcRecovery, 8692, NULL);
#endif
    UNITY_END();
}

