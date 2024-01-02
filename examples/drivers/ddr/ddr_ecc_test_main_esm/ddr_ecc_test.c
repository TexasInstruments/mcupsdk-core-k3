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
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <sdl/sdl_esm.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "dpl_interface.h"

/*******************************************************************************
This example simulates a 1b and 2b ECC error in DDR  ECC enabled region.
The application receives a Low priority interrupt through the ESM module
when a 1b error is generated.
A high priority interrupt is received through ESM module when a 2b error
is generated.

The single bit ECC errors will be corrected by the DDR, but the dual bit ECC
errors is only detected and is not corrected.
User could do a warm reset or do necessaryy corrective action to resolve the
dual bit ECC errors
*******************************************************************************/

#define DDR_START_ADDR (0x80000000u)

#if defined (SOC_AM62X)
#define ESM0_DDR1BECC_INDEX     (6U)
#define ESM0_DDR2BECC_INDEX     (69U)

/* Memory block for which ECC is calculated (256 Bytes) */
#define DDR_EMIF_ECC_MEM_BLOCK_SIZE       0x100
/* ECC data size per block (32 Bytes) */
#define DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK  0x20
#endif

#if defined (SOC_AM62AX)
#define ESM0_DDR1BECC_INDEX     (174U)
#define ESM0_DDR2BECC_INDEX     (175U)

/* Memory block for which ECC is calculated (512 Bytes) */
#define DDR_EMIF_ECC_MEM_BLOCK_SIZE       0x200
/* ECC data size per block (64 Bytes) */
#define DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK  0x40
#endif

/* ECC is enabled in SBL, DDR_ECC_REGION0_START is defined in the sysconfig of SBL.
 * Adding ECC region 0 start macro for testing
 */

#define DDR_ECC_REGION0_START 0x0

#define DDR_ECC_TEST_ADDR               (DDR_START_ADDR + DDR_ECC_REGION0_START \
                                        + DDR_EMIF_ECC_MEM_BLOCK_SIZE)

/* esm_lvl_event for DDR single error */
#define DDR_ECC_AGGR0_SEC_ERR_EVENT    (CSLR_ESM0_ESM_LVL_EVENT_DDR16SS0_DDRSS_DRAM_ECC_CORR_ERR_LVL_0)
/* esm_lvl_event for DDR double error */
#define DDR_ECC_AGGR0_DED_ERR_EVENT    (CSLR_ESM0_ESM_LVL_EVENT_DDR16SS0_DDRSS_DRAM_ECC_UNCORR_ERR_LVL_0)

volatile uint32_t gSecTestPass;
volatile uint32_t gDedTestPass;

volatile uint32_t *gTest_Addr = NULL;
volatile uint32_t testVal;

#if defined (SOC_AM62X)
/* Initialization structure for Main ESM instance */
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
#endif

#if defined (SOC_AM62AX)
/* Initialization structure for Main ESM instance */
static SDL_ESM_config ESM_Example_esmInitConfig_MainESM0 =
{
    .esmErrorConfig = {1u, 8u}, /* Self test error config */
    /**< Enabled DDR inline ECC 1b error index (174) and 2b error index(175) */
    .enableBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x0000C000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                },
     /**< Configured based off esmErrorConfig to test high or low priorty events.*/
    .priorityBitmap = {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                         0x00000000u, 0x00008000u, 0x00000000u, 0x00000000u,
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
#endif

uintptr_t DDRGetTranslatedAddress (uintptr_t memAddress)
{
    uint32_t memIndex;
    uintptr_t translatedMemAddr;

    memIndex = (memAddress - DDR_START_ADDR)/DDR_EMIF_ECC_MEM_BLOCK_SIZE;

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
    }
}

/* Handler for double bit ECC error */
void DDR_dedHandler (void *args)
{
    int32_t status = SystemP_SUCCESS;
    DDR_ECCErrorInfo ECCErrorInfo;
    volatile uint32_t *translatedMemPtr;

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
    }

}

int32_t DDR_secErrTest ()
{
    int32_t status = SystemP_SUCCESS;
    volatile uint32_t testVal2;
    volatile uint32_t *translatedMemPtr;
    uint32_t waitCount = 0;

    gSecTestPass = FALSE;

    /* Clear any residual ECC errors */
    DDR_clearECCError (DDR_ECC_ERR_ALL);

    /* Inject error */
    gTest_Addr = (uint32_t *) (DDR_ECC_TEST_ADDR);

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

    /* Now corrupt the value */
    *(translatedMemPtr) = testVal2;
    CacheP_wbInv ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    DDR_enableInlineECC (1);

    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Read value to trigger error */
    testVal2 = gTest_Addr[0];

    DebugP_log ("Waiting on Single bit Error Correction Interrupt...\r\n");

    while ((gSecTestPass == FALSE) && (waitCount++ < 100u))
    {
        ClockP_usleep(10);
    }

    if (gSecTestPass == TRUE)
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
    uint32_t waitCount = 0;

    gDedTestPass = FALSE;

    /* Clear any residual ECC errors */
    DDR_clearECCError (DDR_ECC_ERR_ALL);

    gTest_Addr = (uint32_t *) (DDR_ECC_TEST_ADDR);

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

    /* Now corrupt the value */
    *(translatedMemPtr) = testVal2;

    /* Make sure the values are written back */
    CacheP_wbInv ((void *)translatedMemPtr, 4, CacheP_TYPE_ALL);

    /* Enable back ECC */
    DDR_enableInlineECC (1);

    /* ================================================================================ */

    /* Invalidate cache */
    CacheP_inv ((void *)gTest_Addr, 4, CacheP_TYPE_ALL);

    /* Read value to trigger error */
    testVal2 = gTest_Addr[0];

    DebugP_log ("Waiting on Dual bit error detection Interrupt...\r\n");

    while ((gDedTestPass == FALSE) && (waitCount++ < 100u))
    {
        ClockP_usleep (100);
    }

    if (gDedTestPass == TRUE)
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

void ddr_ecc_test_main (void *args)
{
    int32_t status;

    gSecTestPass = FALSE;
    gDedTestPass = FALSE;

    status = SDL_dplInit ();

    DebugP_assert (status == SystemP_SUCCESS);

    /* Initialize main ESM instance */
    status = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ESM_Example_esmInitConfig_MainESM0, ESM_callback, NULL);

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

}
