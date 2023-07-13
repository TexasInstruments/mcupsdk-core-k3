/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include <stdio.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/ddr.h>
#include <drivers/ddr/v0/cslr_emif.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <sdl/sdl_esm.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "dpl_interface.h"

#define ESM0_DDR1BECC_INDEX     (6U)
#define ESM0_DDR2BECC_INDEX     (69U)

#define DDR_START_ADDR (0x80000000u)

/* Memory block for which ECC is calculated (256 Bytes) */
#define DDR_EMIF_ECC_MEM_BLOCK_SIZE       0x100
/* ECC data size per block (32 Bytes) */
#define DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK  0x20

/* ECC is enabled in SBL, DDR_ECC_REGION0_START is defined in the sysconfig of SBL.
 * Adding ECC region 0 start macro for testing
 */
#define DDR_ECC_REGION0_START 0x0

#define DDR_ECC_TEST_ADDR               (DDR_START_ADDR + DDR_ECC_REGION0_START \
                                        + DDR_EMIF_ECC_MEM_BLOCK_SIZE)

volatile uint32_t gSecTestPass;
volatile uint32_t gDedTestPass;

volatile uint32_t *gTest_Addr = NULL;
volatile uint32_t testVal;

/* semaphore to signal from single bit and double bit ecc errror handler to main thread */
static SemaphoreP_Object gSecISRDoneSem,gDedISRDoneSem;

/* Initialization structure for MAIN ESM instance */
static SDL_ESM_config ESM_Example_esmInitConfig_MainESM0 =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    /**< Enabled DDR inline ECC 1b error index (6) and 2b error index(69) */
    .enableBitmap = {0x00000040u, 0x00000000u, 0x00000020u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                },
     /**< Configured based off esmErrorConfig to test high or low priorty events.*/
    .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000020u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    /**< Configured based off esmErrorConfig to test high or low priorty events. */
    .errorpinBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                      },
};

/* Initialization structure for MCU ESM instance */
static SDL_ESM_config ESM_Example_esmInitConfig_MCUESM0 =
{
    .esmErrorConfig = {0u, 3u}, /* Self test error config */
    /**< Enabled MAIN ESM high level index (1) and low level index(2) */
    .enableBitmap = {0x00000006u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                },
     /**< Configured based off esmErrorConfig to test high or low priorty events.*/
    .priorityBitmap = {0x00000002u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        },
    /**< Configured based off esmErrorConfig to test high or low priorty events. */
    .errorpinBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                       0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                      },
};

uintptr_t DDRGetTranslatedAddress (uintptr_t memAddress)
{
    uint32_t memIndex;
    uintptr_t translatedMemAddr;

    memIndex = (memAddress - (uintptr_t)AddrTranslateP_getLocalAddr(DDR_START_ADDR))/DDR_EMIF_ECC_MEM_BLOCK_SIZE;

    if ((memIndex & 0x1u) == 0)
    {
        translatedMemAddr = memAddress + ((memIndex)*DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK);
    }
    else
    {
        translatedMemAddr = memAddress + ((memIndex+1u)*DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK);
    }
    return  translatedMemAddr;
}

/* Handler for single bit ECC error */
void DDR_secHandler (void *args)
{
    int32_t status = SystemP_SUCCESS;
    DDR_ECCErrorInfo ECCErrorInfo;

    /* Read ECC registers and double check address */
    status = DDR_getECCErrorInfo (&ECCErrorInfo);

    if (status == SystemP_SUCCESS)
    {
        if ((ECCErrorInfo.singlebitErrorAddress & (~0x7u))
            == ((DDR_ECC_TEST_ADDR - DDR_START_ADDR) & (~0x7u)))
        {
            gSecTestPass = TRUE;
        }

        /* Clear Specific ECC error */
        status = DDR_clearECCError (DDR_ECC_1B_ERROR);
        SemaphoreP_post(&gSecISRDoneSem);
    }
}

/* Handler for double bit ECC error */
void DDR_dedHandler (void *args)
{
    int32_t status = SystemP_SUCCESS;
    DDR_ECCErrorInfo ECCErrorInfo;
    volatile uint32_t *translatedMemPtr;

    /* Read ECC registers and double check address */
    status = DDR_getECCErrorInfo (&ECCErrorInfo);

    if (status == SystemP_SUCCESS)
    {
        if ((ECCErrorInfo.doublebitErrorAddress & (~0x7u))
            == ((DDR_ECC_TEST_ADDR - DDR_START_ADDR) & (~0x7u)))
        {
            gDedTestPass = TRUE;

            /* This section corrects the ECC error simulated */
            /* In a real application the user must take necessary corrective action */
            /******************************************************************/

            /* Disable Inline ECC */
            DDR_enableInlineECC(0);

            translatedMemPtr = (volatile uint32_t *)(DDRGetTranslatedAddress ((uintptr_t)gTest_Addr));

            /* Now replace location with original value as 2b errors are not corrected */
            *(translatedMemPtr) = testVal;

            /* Write back any pending writes */
            CacheP_wbInv ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

            /* Enable back ECC */
            DDR_enableInlineECC (1);

            /******************************************************************/
        }

        /* Clear specific error */
        status = DDR_clearECCError (DDR_ECC_2B_ERROR);
        SemaphoreP_post(&gDedISRDoneSem);
    }

}

int32_t DDR_secErrTest ()
{
    int32_t status = SystemP_SUCCESS;
    volatile uint32_t testVal2;
    volatile uint32_t *translatedMemPtr;

    gSecTestPass = FALSE;

    SemaphoreP_constructBinary(&gSecISRDoneSem, 0);

    /* Clear any residual ECC errors */
    DDR_clearECCError (DDR_ECC_ERR_ALL);

    /* Inject error */
    gTest_Addr = (uint32_t *)AddrTranslateP_getLocalAddr(DDR_ECC_TEST_ADDR);

    /* Write back any pending writes */
    CacheP_wbInv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Read value from test location */
    testVal = gTest_Addr[0];

    /* Flip one bit to introduce error */
    testVal2 = testVal ^ 0x00010000u;

    /* Calculate translated address */
    translatedMemPtr = (volatile uint32_t *)(DDRGetTranslatedAddress ((uintptr_t)gTest_Addr));

    /* Generating a 1b ECC error */
    /* NOTE: The following section should NOT be useed in actual application */
    /* ================================================================================ */

    /* Temporarily disable ECC */
    DDR_enableInlineECC (0);
    ClockP_usleep(10);

    /* Now corrupt the value */
    *(translatedMemPtr) = testVal2;
    CacheP_wbInv ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    DDR_enableInlineECC (1);
    ClockP_usleep(10);

    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Access memory to trigger error */
    testVal2 = gTest_Addr[0];

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

    /* Restore original value */
    gTest_Addr[0] = testVal;

    /* Write back any pending writes */
    CacheP_wbInv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    return status;
}

int32_t DDR_dedErrTest ()
{
    int32_t status = SystemP_SUCCESS;
    volatile uint32_t testVal;
    volatile uint32_t testVal2;
    volatile uint32_t *translatedMemPtr;

    gDedTestPass = FALSE;

    SemaphoreP_constructBinary(&gDedISRDoneSem, 0);

    /* Clear any residual ECC errors */
    DDR_clearECCError (DDR_ECC_ERR_ALL);

    gTest_Addr = (uint32_t *)AddrTranslateP_getLocalAddr(DDR_ECC_TEST_ADDR);

     /* Write back any pending writes */
    CacheP_wbInv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Read reference value */
    testVal       = gTest_Addr[0];

    /* flip 2 bits */
    testVal2       = testVal ^ 0x00101000u;

    /* Calculate translated address */
    translatedMemPtr = (volatile uint32_t *)(DDRGetTranslatedAddress ((uintptr_t)gTest_Addr));

    /* Generating a 2b ECC error */
    /* NOTE: The following section should NOT be useed in actual application */
    /* ================================================================================ */

    /* Temporarily disable ECC */
    DDR_enableInlineECC (0);
    ClockP_usleep(10);

    /* Now corrupt the value */
    *(translatedMemPtr) = testVal2;

    /* Make sure the values are written back */
    CacheP_wbInv ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    DDR_enableInlineECC (1);
    ClockP_usleep(10);
    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Access memory to trigger error */
    gTest_Addr[0] = 1;
    CacheP_wbInv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

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

    /* Restore original value */
    gTest_Addr[0] = testVal;

    return status;
}

int32_t ESM_callback (SDL_ESM_Inst esmInstType,
                                         SDL_ESM_IntType esmIntType,
                                         uint32_t grpChannel,
                                         uint32_t index,
                                         uint32_t intSrc,
                                         void *arg)
{
    if (intSrc == ESM0_DDR1BECC_INDEX)
    {
        DDR_secHandler (NULL);
    }
    else if (intSrc == ESM0_DDR2BECC_INDEX)
    {
        DDR_dedHandler (NULL);
    }
    else
    {

    }

    return SystemP_SUCCESS;
}

void ddr_ecc_test_main (void *arg)
{
    int32_t status;

    /* Open drivers to open the UART driver for console */
    Drivers_open();
    Board_driversOpen();

    gSecTestPass = FALSE;
    gDedTestPass = FALSE;

    status = SDL_dplInit ();

    DebugP_assert (status == SystemP_SUCCESS);

    /* Initialize main ESM instance */
    status = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ESM_Example_esmInitConfig_MainESM0, ESM_callback, NULL);

    DebugP_assert (status == SystemP_SUCCESS);

    /* Initialize MCU ESM instance */
    status = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ESM_Example_esmInitConfig_MCUESM0, ESM_callback, NULL);

    DebugP_assert (status == SystemP_SUCCESS);

    status = DDR_secErrTest ();

    if (status == SystemP_SUCCESS)
    {
        status = DDR_dedErrTest ();
    }

    if (status == SystemP_SUCCESS)
    {
        DebugP_log ("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed\r\n");
    }

    Board_driversClose();
    Drivers_close();
}
