/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include "dsp_offload.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "drivers/uart.h"
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SOC_AM275X) /* Core IDs for AM275x */
#define MAIN_CORE_ID CSL_CORE_ID_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

#if defined(SOC_AM62DX) /* Core IDs for AM62dx */
#define MAIN_CORE_ID CSL_CORE_ID_MCU_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

/* RPMessage endpoints */
#define MAIN_CORE_ACK_REPLY_END_PT (12U)
#define REMOTE_SERVICE_END_PT (13U)

/* MMCSD File I/O */
#define MMCSD_FILE_IO_FAT_PARTITION_SIZE (128U * 1024U * 1024U)
#define MMCSD_FILE_IO_FILE_LINE_CNT (1024U * 1024U)

/* File paths */
#define INPUT_FILE "/sd0/fft2d_input.bin"
#define EXPECTED_OUTPUT_FILE "/sd0/fft2d_output.bin"
#define ACTUAL_OUTPUT_FILE "/sd0/cx.bin"

/* DDR */
#define DDR_SIZE (1 * 1024 * 1024) /*  1 MB */
#define FFT_SIZE (128 * 128 * 2)   /*  Adjust as per your FFT output size */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((section(".ddrData"), aligned(128))) uint8_t ddrBuffer[DDR_SIZE];

float *pInput = (float *)ddrBuffer;
ipcMsgBuf_t iBuf;
params_t gDspParams;
/* RPMessage_Object MUST be global or static */
RPMessage_Object gAckReplyMsgObject;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static bool fft2d_loadTestData(const char *fileName, void *buffer, size_t sizeBytes);
static bool fft2d_compareFftOutputs(const char *expectedOutputFile, const char *actualOutputFile, size_t sizeBytes);
void fft2d_primary_main(void *args);
static bool fft2d_sendBufferToDsp();
static bool fft2d_receiveAndWriteToSd(const char *outputFile, size_t outputSize);

extern uint64_t SOC_phyToVirtFxn(uint64_t phyAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static bool fft2d_loadTestData(const char *fileName, void *buffer, size_t sizeBytes)
{
    int32_t status = SystemP_SUCCESS;

    FF_MMCSD_PartitionDetails partDetails;
    memset(&partDetails, 0, sizeof(FF_MMCSD_PartitionDetails));
    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];
    FF_MMCSDGetPartitionDetails(pDisk, &partDetails);
    if (partDetails.sectorCount == 0U)
    {
        /* No partition, create partition */
        uint32_t sectorCount = (MMCSD_FILE_IO_FAT_PARTITION_SIZE / 512U);
        FF_MMCSDCreateAndFormatPartition(pDisk, sectorCount);
        /* Now mount the partition */
        FF_MMCSDMountPartition(pDisk, "/sd0");
        /* Check the sector count now */
        FF_MMCSDGetPartitionDetails(pDisk, &partDetails);
        if (partDetails.sectorCount > 0U)
        {
            /* Success, can continue */
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else
    {
        /* Partition is present. Can proceed further */
    }
    DebugP_assert(status == SystemP_SUCCESS);

    FF_FILE *fp;
    fp = ff_fopen(fileName, "rb");
    if (fp == NULL)
    {
        DebugP_log("File open failed. Please check sd card or file name\r\n");
        return false;
    }
    size_t readBytes = ff_fread(buffer, sizeof(double), sizeBytes, fp);
    ff_fclose(fp);
    return (readBytes == sizeBytes);
}

static bool fft2d_compareFftOutputs(const char *expectedOutputFile, const char *actualOutputFile, size_t sizeBytes)
{
    FF_FILE *fpPy = ff_fopen(expectedOutputFile, "rb");
    FF_FILE *fpC7x = ff_fopen(actualOutputFile, "rb");
    if (!fpPy)
    {
        DebugP_log("Error opening python output file!!\r\n");
        return false;
    }
    if (!fpC7x)
    {
        DebugP_log("Error opening c7x output file!!\r\n");
        return false;
    }
    float outPy[2];
    float outC7x[2];

    double maxAbsErr = 0.0, sumAbsErr = 0.0, sumSqErr = 0.0, maxVal = 0.0;
    for (int i = 0; i < sizeBytes; i++)
    {
        ff_fread(outPy, sizeof(float), 1, fpPy);
        ff_fread(outC7x, sizeof(float), 1, fpC7x);
        double err = fabs(outPy[0] - outC7x[0]);
        sumAbsErr += err;
        sumSqErr += err * err;
        if (err > maxAbsErr)
            maxAbsErr = err;
        if (fabs(outPy[0]) > maxVal)
            maxVal = fabs(outPy[0]);
    }
    ff_fclose(fpPy);
    ff_fclose(fpC7x);
    double meanAbsErr = sumAbsErr / FFT_SIZE;
    double rmse = sqrt(sumSqErr / FFT_SIZE);
    double relMaxErr = maxAbsErr / (maxVal + 1e-12);

    DebugP_log("======FFT Output Comparison With Python Results===========\r\n");
    DebugP_log("  Max Absolute Error   : %e\r\n", maxAbsErr);
    DebugP_log("  Mean Absolute Error  : %e\r\n", meanAbsErr);
    DebugP_log("  RMSE                 : %e\r\n", rmse);
    DebugP_log("  Relative Max Error   : %e\r\n", relMaxErr);
    return (relMaxErr < 0.01);
}

static bool fft2d_sendBufferToDsp()
{
    /* Initialize RPMessage */
    RPMessage_CreateParams createParams;
    int32_t status;
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = MAIN_CORE_ACK_REPLY_END_PT;
    status = RPMessage_construct(&gAckReplyMsgObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Synchronize with remote core */
    IpcNotify_sendSync(REMOTE_CORE_ID);
    IpcNotify_waitSync(REMOTE_CORE_ID, SystemP_WAIT_FOREVER);

    iBuf.dataBuffer = (uint32_t)(uintptr_t)pInput;        /* pointer to input data buffer */
    iBuf.paramsBuffer = (uint32_t)(uintptr_t)&gDspParams; /* pointer to params buffer (if any) */
    iBuf.dataSize = FFT_SIZE;                             /* size in bytes or elements */
    iBuf.paramsSize = sizeof(gDspParams);                 /* size of params */

    /* Send the message to C7x */
    status = RPMessage_send(
        (char *)&iBuf, sizeof(ipcMsgBuf_t),
        REMOTE_CORE_ID, REMOTE_SERVICE_END_PT,
        RPMessage_getLocalEndPt(&gAckReplyMsgObject),
        SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);
    return (status == SystemP_SUCCESS);
}

static bool fft2d_receiveAndWriteToSd(const char *outputFile, size_t outputSize)
{
    uint16_t msgSize = sizeof(ipcMsgBuf_t);
    uint16_t remoteCoreId;
    uint32_t remoteCoreEndPt;

    int32_t status = RPMessage_recv(
        &gAckReplyMsgObject,
        (char *)&iBuf, &msgSize,
        &remoteCoreId, &remoteCoreEndPt,
        SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);
#if defined(SOC_AM275X)
    iBuf.dataBuffer = SOC_phyToVirtFxn(iBuf.dataBuffer);
    params_t *dspParams = (params_t *)SOC_phyToVirtFxn(iBuf.paramsBuffer);
#endif
#if defined(SOC_AM62DX)
    params_t *dspParams = (params_t *)(iBuf.paramsBuffer);
#endif
    CacheP_inv((void *)iBuf.dataBuffer, iBuf.dataSize, CacheP_TYPE_ALLD);
    CacheP_inv((void *)dspParams, sizeof(params_t), CacheP_TYPE_ALLD);
    DebugP_log("\r\n=========FFT Performance Results=========\r\n");
    DebugP_log("  DSP Load           : %d\r\n", dspParams->dspLoad);
    DebugP_log("  Cycle Count        : %d\r\n", dspParams->cycleCount);
    DebugP_log("  Mem Throughput     : %.2f GB/s\r\n\n", dspParams->ddrThroughput);

    /* write the output data to a file */
    FF_FILE *fpOut = ff_fopen(outputFile, "w+");
    size_t writtenSize = 0;

    if (fpOut == NULL)
    {
        DebugP_log("File open failed for %s\r\n", outputFile);
    }
    else
    {
        writtenSize = ff_fwrite((float *)(iBuf.dataBuffer), sizeof(float), outputSize, fpOut);
        ff_fclose(fpOut);
    }
    return (writtenSize == outputSize);
}

void fft2d_primary_main(void *args)
{
    bool ret = false;
    DebugP_log("\r\nStarting FFT2D DSP Offload example\r\n");

    DebugP_log("\r\nLoading test data...\r\n");
    ret = fft2d_loadTestData(INPUT_FILE, pInput, FFT_SIZE / 2);
    if (ret == false)
    {
        DebugP_logError("Failed to load input binary\r\n");
        return;
    }

    DebugP_log("Input data samples (a+ib):\r\n");
    for (int i = 0; i < 2; i++)
    {
        float real = ((float *)pInput)[i * 2];
        float imag = ((float *)pInput)[i * 2 + 1];
        DebugP_log("%.2f + %.2fj\r\n", real, imag);
    }

    DebugP_log("\r\nOffloading FFT to DSP...\r\n");
    ret = fft2d_sendBufferToDsp();
    if (ret == false)
    {
        DebugP_logError("Sending buffer to DSP failed\r\n");
        return;
    }

    DebugP_log("\r\nReceiving FFT output from DSP...\r\n");
    ret = fft2d_receiveAndWriteToSd(ACTUAL_OUTPUT_FILE, FFT_SIZE);
    if (ret == false)
    {
        DebugP_logError("FFT output write to file failed\r\n");
        return;
    }

    DebugP_log("Output data samples (a+ib):\r\n");
    for (int i = 0; i < 2; i++)
    {
        float real = ((float *)pInput)[i * 2];
        float imag = ((float *)pInput)[i * 2 + 1];
        DebugP_log("%.2f + %.2fj\r\n", real, imag);
    }

    DebugP_log("\r\nComparing FFT output with expected output...\r\n");
    ret = fft2d_compareFftOutputs(EXPECTED_OUTPUT_FILE, ACTUAL_OUTPUT_FILE, FFT_SIZE);
    if (ret == false)
    {
        DebugP_logError("FFT output comparison failed\r\n");
        return;
    }

    ClockP_usleep(3000 * 1000); /* wait for log messages from remote cores to be flushed, otherwise this delay is not needed */

    DebugP_log("\r\nAll tests have completed!!\r\n");
}
