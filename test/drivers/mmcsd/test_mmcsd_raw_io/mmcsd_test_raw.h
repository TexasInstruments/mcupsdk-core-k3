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

#ifndef MMCSD_TEST_RAW_H
#define MMCSD_TEST_RAW_H

/**\file mmcsd_test_raw.h
 *
 * \brief Test functions for MMCSD file I/O and directory operations.
 */

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

void TestMmcsd_emmcRawIo(void *args);
void TestMmcsd_emmcEnableDisableBootPartition(void *args);
void TestMmcsd_emmcTuningConfig(void *args);
void TestMmcsd_emmcMultiblockRawIo(void *args);
void TestMmcsd_openInvalidInstance(void *args);
void TestMmcsd_sdRawIo(void *args);
void TestMmcsd_validateClkFreq(void *args);
void TestMmcsd_emmcMultipleBusWidths(void *args);
void TestMmcsd_sdMultipleBusWidths(void *args);
void TestMmcsd_sdTuningConfig(void *args);
void TestMmcsd_emmcMultiplePhyconfig(void *args);
void TestMmcsd_dmaModes(void *args);
void TestMmcsd_intrModes(void *args);
void TestMmcsd_getBlockCountValidate(void *args);
void TestMmcsd_openOpenFail(void *args);
void TestMmcsd_readArgumentValidate(void *args);
void TestMmcsd_writeArgumentValidate(void *args);
void TestMmcsd_multipleOpenClose(void *args);
void TestMmcsd_emmcWriteReadBootPartition(void *args);
void TestMmcsd_emmcWriteReadBootPartitionFail(void *args);
void TestMmcsd_unalignedBuffersRawIo(void *args);
void TestMmcsd_emmcSpeedSwitch(void *args);
void TestMmcsd_crcRecovery(void *args);


#endif /* MMCSD_TEST_RAW_H */

