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

#include "drivers/hyperbus.h"
#include <drivers/pinmux.h>
#include <drivers/soc.h>
#include <inttypes.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <string.h>
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define HYPERRAM_START_ADDR (0x68000000u)

/* Memory block for which ECC is calculated (32 Bytes) */
#define HYPERRAM_ECC_MEM_BLOCK_SIZE       0x20U
/* ECC data size per block (4 Bytes) */
#define HYPERRAM_ECC_DATA_SIZE_PER_BLOCK  0x4U

#define HYPERRAM_ECC_TEST_ADDR_OFFSET     (0x80U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32_t gSecTestPass;
volatile uint32_t gDedTestPass;

volatile uint32_t gHyperBusEccRegionStartAddr = 0x0U;
volatile uint32_t gHyperBusEccRegionSize = 0x0U;

volatile uint32_t gTest_Addr = 0x0U;

uint8_t test_values_buffer[32];
uint8_t test_values_buffer_check[32];

/* Semaphore to signal from single bit and double bit ecc errror handler to main thread */
static SemaphoreP_Object gSecISRDoneSem,gDedISRDoneSem;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

uintptr_t hyperRam_getTranslatedAddress (uintptr_t memAddress)
{
    uint32_t memIndex;
    uintptr_t translatedMemAddr;

    memIndex = (memAddress - HYPERRAM_START_ADDR)/HYPERRAM_ECC_MEM_BLOCK_SIZE;

    if ((memIndex & 0x1u) == 0)
    {
        translatedMemAddr = memAddress + ((memIndex)*HYPERRAM_ECC_DATA_SIZE_PER_BLOCK);
    }
    else
    {
        translatedMemAddr = memAddress + ((memIndex+1u)*HYPERRAM_ECC_DATA_SIZE_PER_BLOCK);
    }
    return  translatedMemAddr;
}

/* Handler for single bit ECC error */
void hyperRam_secHandler (HYPERBUS_Handle hyperbusHandle)
{
    uint32_t baseAddress = 0U;
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);

    gSecTestPass = TRUE;

    memcpy((uint32_t *)(baseAddress + gTest_Addr), test_values_buffer_check, 32);
    CacheP_wb((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);

    SemaphoreP_post(&gSecISRDoneSem);
}

/* Handler for double bit ECC error */
void hyperRam_dedHandler (HYPERBUS_Handle hyperbusHandle)
{
    uint32_t baseAddress = 0U;
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);

    gDedTestPass = TRUE;

    /* This section corrects the ECC error simulated */
    /* In a real application the user must take necessary corrective action */
    /******************************************************************/

    /* Now replace location with original value as 2b errors are not corrected */
    memcpy((uint32_t *)(baseAddress + gTest_Addr), test_values_buffer_check, 32);
    CacheP_wb((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);

    /******************************************************************/

    SemaphoreP_post(&gDedISRDoneSem);
}

int32_t hyperRam_secErrTest (HYPERBUS_Handle hyperbusHandle)
{
    int32_t status = SystemP_SUCCESS;
    volatile uint32_t *translatedMemPtr;
    uint32_t baseAddress = 0U;

    gSecTestPass = FALSE;

    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);

    SemaphoreP_constructBinary(&gSecISRDoneSem, 0);

    gTest_Addr = (gHyperBusEccRegionStartAddr + HYPERRAM_ECC_TEST_ADDR_OFFSET);

    memset((uint32_t *)(baseAddress + gTest_Addr), 0xF8U, 32);
    CacheP_wbInv((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);
    memcpy(test_values_buffer, (uint32_t *)(baseAddress + gTest_Addr), 32);
    memcpy(test_values_buffer_check, (uint32_t *)(baseAddress + gTest_Addr), 32);

    test_values_buffer[0] ^= 0x01U;

    translatedMemPtr = (volatile uint32_t *)(hyperRam_getTranslatedAddress ((uintptr_t)(baseAddress + gTest_Addr)));

    /* Generating a 1b ECC error */
    /* NOTE: The following section should NOT be useed in actual application */
    /* ================================================================================ */

    /* Temporarily disable ECC */
    HYPERBUS_enableECC(hyperbusHandle, 0U);
    ClockP_usleep(10);

    /* Inject error */
    memcpy((uint32_t *)(translatedMemPtr), test_values_buffer, 32);

    /* Write back any pending writes */
    CacheP_wb ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    HYPERBUS_enableECC(hyperbusHandle, 1U);
    ClockP_usleep(10);

    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);
    /* Access memory to trigger error */
    memcpy(test_values_buffer, (uint32_t *)(baseAddress + gTest_Addr), 32);

    DebugP_log ("Waiting on Single bit Error Correction Interrupt...\r\n");

    /* wait for ecc interrupt to be handled*/
    status = SemaphoreP_pend(&gSecISRDoneSem, ClockP_usecToTicks(10*1000));

    if ((gSecTestPass == TRUE) && (status == SystemP_SUCCESS))
    {
        DebugP_log ("1b ECC error detected and corrected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError ("1b Inline ECC test failed timedout ...\r\n");
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t hyperRam_dedErrTest (HYPERBUS_Handle hyperbusHandle)
{
    int32_t status = SystemP_SUCCESS;
    volatile uint32_t *translatedMemPtr;
    uint32_t baseAddress = 0U;

    gSecTestPass = FALSE;

    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);

    SemaphoreP_constructBinary(&gDedISRDoneSem, 0);

    gTest_Addr = (gHyperBusEccRegionStartAddr + HYPERRAM_ECC_TEST_ADDR_OFFSET);

    memset((uint32_t *)(baseAddress + gTest_Addr), 0xF8U, 32);
    CacheP_wbInv((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);
    memcpy(test_values_buffer, (uint32_t *)(baseAddress + gTest_Addr), 32);
    memcpy(test_values_buffer_check, (uint32_t *)(baseAddress + gTest_Addr), 32);

    /* flip 2 bits */
    test_values_buffer[0] ^= 0x11U;

    /* Calculate translated address */
    translatedMemPtr = (volatile uint32_t *)(hyperRam_getTranslatedAddress ((uintptr_t)(baseAddress + gTest_Addr)));

    /* Generating a 2b ECC error */
    /* NOTE: The following section should NOT be used in actual application */
    /* ================================================================================ */

    /* Temporarily disable ECC */
    HYPERBUS_enableECC(hyperbusHandle, 0U);
    ClockP_usleep(10);

    /* Inject error */
    memcpy((uint32_t *)(translatedMemPtr), test_values_buffer, 32);

    /* Write back any pending writes */
    CacheP_wb ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    HYPERBUS_enableECC(hyperbusHandle, 1U);
    ClockP_usleep(10);
    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv((uint32_t *)(baseAddress + gTest_Addr), 32, CacheP_TYPE_ALLD);
    /* Access memory to trigger error */
    memcpy(test_values_buffer, (uint32_t *)(baseAddress + gTest_Addr), 32);

    DebugP_log ("Waiting on Dual bit error detection Interrupt...\r\n");

    /* wait for ecc interrupt to be handled*/
    status = SemaphoreP_pend(&gDedISRDoneSem, ClockP_usecToTicks(100*1000));

    if ((gDedTestPass == TRUE) && (status == SystemP_SUCCESS))
    {
        DebugP_log ("2b ECC error detected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError ("2b Inline ECC Test failed timedout ...\r\n");
        status = SystemP_FAILURE;
    }

    return status;
}

void hyperRam_ecc_callback (HYPERBUS_Handle hyperbusHandle, uint8_t errorType)
{
    if(hyperbusHandle != NULL)
    {
        if(errorType == HYPERBUS_ECC_1B_ERROR)
        {
            hyperRam_secHandler (hyperbusHandle);
        }
        else if(errorType == HYPERBUS_ECC_2B_ERROR)
        {
            hyperRam_dedHandler (hyperbusHandle);
        }
        else if(errorType == HYPERBUS_ECC_ERR_ALL)
        {
            hyperRam_secHandler (hyperbusHandle);
            hyperRam_dedHandler (hyperbusHandle);
        }
    }
}

void hyperRam_ecc_test_main (void *arg)
{
    int32_t status = SystemP_SUCCESS;
    HYPERRAM_Handle   hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HYPERBUS_Handle hyperbusHandle = NULL;
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;


    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);

    HYPERBUS_Config *hyperBusConfig = ((HYPERBUS_Config *)hyperbusHandle);
    const HYPERBUS_Attrs *hyperBusAttrs = hyperBusConfig->attrs;
    const HYPERBUS_ECCRegions *eccRegion = hyperBusAttrs->eccRegion;

    gHyperBusEccRegionStartAddr = eccRegion->eccRegionStart0;
    gHyperBusEccRegionSize = eccRegion->eccRegionSize0;

    status = hyperRam_secErrTest (hyperbusHandle);

    if (status == SystemP_SUCCESS)
    {
        status = hyperRam_dedErrTest (hyperbusHandle);
    }

    if (status == SystemP_SUCCESS)
    {
        DebugP_log ("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed\r\n");
    }
}
