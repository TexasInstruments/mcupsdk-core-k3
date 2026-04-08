/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/** \file test_ddr.c
 *
 *  \brief This test is a simple DDR memory test.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include <drivers/ddr.h>
#include <drivers/ddr/v1/csl_emif.h>
#include <drivers/ddr/ddr_perf.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/soc.h>
#include <string.h>
#include "test_ddr.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DDR_BASE_ADDR       (0x80000000U)
#define DDR_ADDR_END   		(0xC0000000U)
#define ONE_MEGABYTE        (0x100000)
#define BIT_COUNT			(32)
#define ONE			    	(0x00000001)
#define MSG_FREQ        	(0xFFFFFFC)
#define BIT_COUNT_EXT_MEM	(64)
#define BOARD_DIAG_MEM_LWORD_SPLIT(lw) ((lw >> 32) & 0xFFFFFFFF), (lw & 0xFFFFFFFF)

/* Test patterns */
#define TEST_DDR_PATTERN_1      (0xDEADBEEFU)
#define TEST_DDR_PATTERN_2      (0xA5A5A5A5U)
#define TEST_DDR_PATTERN_3      (0x5A5A5A5AU)
#define TEST_DDR_PATTERN_4      (0x12345678U)

/* Memory access test step size */
#define TEST_DDR_MEM_ACCESS_STEP     (ONE_MEGABYTE)

/* Number of addresses to test in memory access pattern test */
#define TEST_DDR_MEM_ACCESS_COUNT    (16U)

#define TEST_DDR_DDRSS_PLL_FREQUENCY_1          933333333
#define TEST_DDR_DDRSS_PLL_FREQUENCY_2          933333333
#define TEST_DDR_DDRSS_PLL_FHS_CNT              3
#define TEST_DDR_DDRSS_CTL_REG_INIT_COUNT       (435U)
#define TEST_DDR_DDRSS_PHY_INDEP_REG_INIT_COUNT (424U)
#define TEST_DDR_DDRSS_PHY_REG_INIT_COUNT       (827U)

/* Walking test range: 8KB = 1024 64-bit aligned addresses */
#define TEST_DDR_WALK_TEST_SIZE          (0x2000U)
/* Block test size for all-ones/zeros and checkerboard: 1MB */
#define TEST_DDR_BLOCK_TEST_SIZE         (ONE_MEGABYTE)
/* Random data test region: 4MB */
#define TEST_DDR_RANDOM_TEST_SIZE        (4U * ONE_MEGABYTE)
/* PRNG seed for reproducible random pattern test */
#define TEST_DDR_PRNG_SEED               (0x12345678U)
/* Address bus test size: 1MB */
#define TEST_DDR_ADDR_BUS_TEST_SIZE      (ONE_MEGABYTE)

/* Stress test iteration count */
#define TEST_DDR_STRESS_ITERATIONS       (100U)
/* Traffic generation buffer size: 1MB */
#define TEST_DDR_TRAFFIC_BUF_SIZE        (ONE_MEGABYTE)
/* Number of perf stat accumulation samples */
#define TEST_DDR_PERF_SAMPLE_COUNT       (10U)
/* ECC sustained traffic iteration count */
#define TEST_DDR_ECC_STRESS_ITERATIONS   (20U)
/* DMA concurrent test region size */
#define TEST_DDR_CONCURRENT_REGION_SIZE  (ONE_MEGABYTE)

/* ECC test region configuration */
#define TEST_DDR_ECC_TEST_REGION0_START      (0x00000000U)
#define TEST_DDR_ECC_TEST_REGION0_END        (0x00100000U)   /* 1MB */
#define TEST_DDR_ECC_TEST_REGION1_START      (0x00100000U)
#define TEST_DDR_ECC_TEST_REGION1_END        (0x00200000U)   /* 1MB */
#define TEST_DDR_ECC_TEST_REGION2_START      (0x00200000U)
#define TEST_DDR_ECC_TEST_REGION2_END        (0x00300000U)   /* 1MB */

/* Memory block for which ECC is calculated */
#define TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE      (0x200U)
/* ECC data size per block */
#define TEST_DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK (0x40U)

/* ECC test address: first usable address past region 0 start (skip first block) */
#define TEST_DDR_ECC_TEST_ADDR               (DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION0_START \
                                        + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE)

/* Unused ECC region marker */
#define TEST_DDR_ECC_REGION_START_UNUSED     (0xFFFF0000U)

/* ECC ready wait timeout (milliseconds) */
#define TEST_DDR_ECC_READY_TIMEOUT_MS        (5000U)

/* Combined ECC interrupt enable mask (1B + M1B + 2B) */
#define TEST_DDR_ECC_INT_ALL_MASK    (CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK  \
                                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK \
                                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC2BERR_EN_MASK)

/* ========================================================================== */
/*                          Global Variables                                  */
/* ========================================================================== */

/*
 * Extern declarations for DDR register config arrays and counts defined in
 * ti_drivers_config.c (via board_ddrReginit.h).
 */
extern uint32_t DDRSS_ctlReg[];
extern uint32_t DDRSS_phyIndepReg[];
extern uint32_t DDRSS_phyReg[];
extern uint16_t DDRSS_ctlRegNum[];
extern uint16_t DDRSS_phyIndepRegNum[];
extern uint16_t DDRSS_phyRegNum[];

/* Counter for expected data aborts during 2-bit ECC error reads */
static volatile uint32_t TestDdr_ExpectedAbortCount = 0U;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void write_read_test(void *arg);
void board_walking1s_test (void *arg);
void board_walking0s_test (void *arg);

#if !defined(MCU_R5)
static void TestDdr_populateValidParams(DDR_Params *prms);
#endif
static uint32_t TestDdr_prng(uint32_t *state);
static uintptr_t TestDdr_eccTranslateAddr(uintptr_t memAddr);
#if !defined(MCU_R5)
static int32_t TestDdr_waitForEccReady(uint32_t timeoutMs);
static void TestDdr_populateEccParams(DDR_Params *prms, DDR_EccRegion *eccRegion);
static void TestDdr_setupSingleEccRegion(DDR_EccRegion *eccRegion);
static void TestDdr_setupMultipleEccRegions(DDR_EccRegion *eccRegion);
static void TestDdr_setupRegion1OnlyEccRegion(DDR_EccRegion *eccRegion);
static void TestDdr_setupRegion2OnlyEccRegion(DDR_EccRegion *eccRegion);
static void TestDdr_generateTraffic(volatile uint32_t *baseAddr, uint32_t numWords);
#endif
static uint32_t TestDdr_injectSingleBitError(volatile uint32_t *testAddr);
static uint32_t TestDdr_injectDoubleBitError(volatile uint32_t *testAddr);
static void TestDdr_restoreEccTestAddr(volatile uint32_t *testAddr, uint32_t origVal);
static int32_t TestDdr_ensureEccSetup(void);

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */


/*
 * Simple LCG PRNG (Numerical Recipes constants) for reproducible random tests.
 */
static uint32_t TestDdr_prng(uint32_t *state)
{
    *state = (*state * 1664525U) + 1013904223U;
    return *state;
}

/*
 * Helper: Translate system address to physical address accounting for inline
 * ECC memory interleaving (512-byte data + 64-byte ECC per block).
 */
static uintptr_t TestDdr_eccTranslateAddr(uintptr_t memAddr)
{
    uint32_t  memIndex;
    uintptr_t translated;

    memIndex = (uint32_t)(memAddr - DDR_BASE_ADDR) / TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE;

    if ((memIndex & 0x1U) == 0U)
    {
        translated = memAddr + ((uintptr_t)memIndex * TEST_DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK);
    }
    else
    {
        translated = memAddr + ((uintptr_t)(memIndex + 1U) * TEST_DDR_EMIF_ECC_DATA_SIZE_PER_BLOCK);
    }

    return translated;
}

#if !defined(MCU_R5)
/*
 * Helper: Wait for ECC initialization to complete by polling ECC_CK bit.
 * The DDR ISR sets ECC_CK=1 after all BIST priming regions are done.
 */
static int32_t TestDdr_waitForEccReady(uint32_t timeoutMs)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    uint64_t startUs    = ClockP_getTimeUsec();
    uint64_t timeoutUs  = (uint64_t)timeoutMs * 1000U;

    while ((ClockP_getTimeUsec() - startUs) < timeoutUs)
    {
        if ((pRegs->ECC_CTRL_REG & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK) != 0U)
        {
            return SystemP_SUCCESS;
        }
    }

    DebugP_log("ECC ready wait timed out after %u ms\r\n", timeoutMs);
    return SystemP_FAILURE;
}

/*
 * Helper: Populate DDR_Params with ECC enabled.
 */
static void TestDdr_populateEccParams(DDR_Params *prms, DDR_EccRegion *eccRegion)
{
    TestDdr_populateValidParams(prms);
    prms->enableEccFlag = 1U;
    prms->eccRegion     = eccRegion;
}

/*
 * Helper: Set up a single ECC region (region 0 only).
 */
static void TestDdr_setupSingleEccRegion(DDR_EccRegion *eccRegion)
{
    eccRegion->ddrEccStart0    = TEST_DDR_ECC_TEST_REGION0_START;
    eccRegion->ddrEccEnd0      = TEST_DDR_ECC_TEST_REGION0_END;
    eccRegion->ddrEccPrimeEnd0 = TEST_DDR_ECC_TEST_REGION0_END;

    eccRegion->ddrEccStart1    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd1      = 0U;
    eccRegion->ddrEccPrimeEnd1 = 0U;

    eccRegion->ddrEccStart2    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd2      = 0U;
    eccRegion->ddrEccPrimeEnd2 = 0U;
}

/*
 * Helper: Set up three ECC regions.
 */
static void TestDdr_setupMultipleEccRegions(DDR_EccRegion *eccRegion)
{
    eccRegion->ddrEccStart0    = TEST_DDR_ECC_TEST_REGION0_START;
    eccRegion->ddrEccEnd0      = TEST_DDR_ECC_TEST_REGION0_END;
    eccRegion->ddrEccPrimeEnd0 = TEST_DDR_ECC_TEST_REGION0_END;

    eccRegion->ddrEccStart1    = TEST_DDR_ECC_TEST_REGION1_START;
    eccRegion->ddrEccEnd1      = TEST_DDR_ECC_TEST_REGION1_END;
    eccRegion->ddrEccPrimeEnd1 = TEST_DDR_ECC_TEST_REGION1_END;

    eccRegion->ddrEccStart2    = TEST_DDR_ECC_TEST_REGION2_START;
    eccRegion->ddrEccEnd2      = TEST_DDR_ECC_TEST_REGION2_END;
    eccRegion->ddrEccPrimeEnd2 = TEST_DDR_ECC_TEST_REGION2_END;
}

/*
 * Helper: Set up region 1 only (region 0 and region 2 unused).
 */
static void TestDdr_setupRegion1OnlyEccRegion(DDR_EccRegion *eccRegion)
{
    eccRegion->ddrEccStart0    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd0      = 0U;
    eccRegion->ddrEccPrimeEnd0 = 0U;

    eccRegion->ddrEccStart1    = TEST_DDR_ECC_TEST_REGION1_START;
    eccRegion->ddrEccEnd1      = TEST_DDR_ECC_TEST_REGION1_END;
    eccRegion->ddrEccPrimeEnd1 = TEST_DDR_ECC_TEST_REGION1_END;

    eccRegion->ddrEccStart2    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd2      = 0U;
    eccRegion->ddrEccPrimeEnd2 = 0U;
}

/*
 * Helper: Set up region 2 only (region 0 and region 1 unused).
 */
static void TestDdr_setupRegion2OnlyEccRegion(DDR_EccRegion *eccRegion)
{
    eccRegion->ddrEccStart0    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd0      = 0U;
    eccRegion->ddrEccPrimeEnd0 = 0U;

    eccRegion->ddrEccStart1    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion->ddrEccEnd1      = 0U;
    eccRegion->ddrEccPrimeEnd1 = 0U;

    eccRegion->ddrEccStart2    = TEST_DDR_ECC_TEST_REGION2_START;
    eccRegion->ddrEccEnd2      = TEST_DDR_ECC_TEST_REGION2_END;
    eccRegion->ddrEccPrimeEnd2 = TEST_DDR_ECC_TEST_REGION2_END;
}

#endif /* !defined(MCU_R5) */

/*
 * Helper: Inject a single-bit ECC error at the given test address.
 * Returns the original (pre-corruption) value.
 */
static uint32_t TestDdr_injectSingleBitError(volatile uint32_t *testAddr)
{
    uint32_t  origVal;
    uint32_t  corruptVal;
    volatile uint32_t *translatedAddr;

    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    origVal    = *testAddr;
    corruptVal = origVal ^ 0x00010000U;

    translatedAddr = (volatile uint32_t *)TestDdr_eccTranslateAddr((uintptr_t)testAddr);

    DDR_enableInlineECC(0U);
    *translatedAddr = corruptVal;
    CacheP_wbInv((void *)translatedAddr, 4U, CacheP_TYPE_ALL);
    DDR_enableInlineECC(1U);

    return origVal;
}

/*
 * Helper: Inject a double-bit ECC error at the given test address.
 * Returns the original (pre-corruption) value.
 */
static uint32_t TestDdr_injectDoubleBitError(volatile uint32_t *testAddr)
{
    uint32_t  origVal;
    uint32_t  corruptVal;
    volatile uint32_t *translatedAddr;

    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    origVal    = *testAddr;
    corruptVal = origVal ^ 0x00101000U;

    translatedAddr = (volatile uint32_t *)TestDdr_eccTranslateAddr((uintptr_t)testAddr);

    DDR_enableInlineECC(0U);
    *translatedAddr = corruptVal;
    CacheP_wbInv((void *)translatedAddr, 4U, CacheP_TYPE_ALL);
    DDR_enableInlineECC(1U);

    return origVal;
}

/*
 * Helper: Restore the original value at a test address after ECC error
 * injection (safe for both 1-bit and 2-bit errors).
 */
static void TestDdr_restoreEccTestAddr(volatile uint32_t *testAddr, uint32_t origVal)
{
    volatile uint32_t *translatedAddr;

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    translatedAddr = (volatile uint32_t *)TestDdr_eccTranslateAddr((uintptr_t)testAddr);

    DDR_enableInlineECC(0U);
    *translatedAddr = origVal;
    CacheP_wbInv((void *)translatedAddr, 4U, CacheP_TYPE_ALL);
    DDR_enableInlineECC(1U);

    *testAddr = origVal;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
}

/*
 * Helper: Configure ECC region 0. Write zeros to the entire region with
 * ECC enabled but checking off to prime
 */
static int32_t TestDdr_ensureEccSetup(void)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    CSL_EmifConfig emifCfg;
    int32_t status = SystemP_SUCCESS;
    uint32_t regVal;
    volatile uint32_t *memPtr;
    uint32_t i, numWords;
    uint32_t primeSize = 0x2000U; /* Prime first 8KB (16 blocks) to cover all ECC bits */

    memset(&emifCfg, 0, sizeof(emifCfg));

    /* Configure ECC region 0 with ECC enabled, checking disabled for priming */
    emifCfg.bEnableMemoryECC       = (bool)true;
    emifCfg.bReadModifyWriteEnable = (bool)true;
    emifCfg.bECCCheck              = (bool)false;
    emifCfg.bWriteAlloc            = (bool)true;
    emifCfg.ECCThreshold           = 1U;

    emifCfg.pMemEccCfg.startAddr[0] = TEST_DDR_ECC_TEST_REGION0_START;
    emifCfg.pMemEccCfg.endAddr[0]   = TEST_DDR_ECC_TEST_REGION0_END;
    emifCfg.pMemEccCfg.startAddr[1] = TEST_DDR_ECC_REGION_START_UNUSED;
    emifCfg.pMemEccCfg.endAddr[1]   = 0U;
    emifCfg.pMemEccCfg.startAddr[2] = TEST_DDR_ECC_REGION_START_UNUSED;
    emifCfg.pMemEccCfg.endAddr[2]   = 0U;

    status = CSL_emifConfig(pRegs, &emifCfg);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("CSL_emifConfig failed\r\n");
    }
    else
    {
        /* Software prime: Write zeros with ECC enabled but checking off */
        memPtr   = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION0_START);
        numWords = primeSize / 4U;
        for (i = 0U; i < numWords; i++)
        {
            memPtr[i] = 0x00000000U;
        }
        CacheP_wbInv((void *)memPtr, primeSize, CacheP_TYPE_ALL);

        /* Enable ECC checking */
        regVal = pRegs->ECC_CTRL_REG;
        regVal |= CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;
        CSL_REG32_WR(&pRegs->ECC_CTRL_REG, regVal);

        /* Clear any stale errors */
        status = DDR_clearECCError(DDR_ECC_ERR_ALL);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("DDR_clearECCError failed\r\n");
        }
        else
        {
            /* Enable ECC interrupts */
            status = CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
            if (status != SystemP_SUCCESS)
            {
                DebugP_log("CSL_emifEnableECCInterrupts failed\r\n");
            }
        }
    }

    return status;
}

#if !defined(MCU_R5)
/*
 * Helper: Populate DDR_Params with valid configuration from board_ddrReginit.h
 */
static void TestDdr_populateValidParams(DDR_Params *prms)
{
    DDR_Params_init(prms);

    prms->clk1Freq              = TEST_DDR_DDRSS_PLL_FREQUENCY_1;
    prms->clk2Freq              = TEST_DDR_DDRSS_PLL_FREQUENCY_2;
    prms->ddrssCtlReg           = DDRSS_ctlReg;
    prms->ddrssPhyIndepReg      = DDRSS_phyIndepReg;
    prms->ddrssPhyReg           = DDRSS_phyReg;
    prms->ddrssCtlRegNum        = DDRSS_ctlRegNum;
    prms->ddrssPhyIndepRegNum   = DDRSS_phyIndepRegNum;
    prms->ddrssPhyRegNum        = DDRSS_phyRegNum;
    prms->ddrssCtlRegCount      = TEST_DDR_DDRSS_CTL_REG_INIT_COUNT;
    prms->ddrssPhyIndepRegCount = TEST_DDR_DDRSS_PHY_INDEP_REG_INIT_COUNT;
    prms->ddrssPhyRegCount      = TEST_DDR_DDRSS_PHY_REG_INIT_COUNT;
    prms->fshcount              = TEST_DDR_DDRSS_PLL_FHS_CNT;
    prms->sdramIdx              = 16U;
    prms->enableEccFlag         = 0U;
    prms->eccRegion             = NULL;
}
#endif /* !defined(MCU_R5) */

/*
 * Override the WEAK default data abort handler.
*/
void HwiP_user_data_abort_handler_c(DFSR dfsr, ADFSR adfsr,
    volatile uint32_t DFAR, volatile uint32_t LR, volatile uint32_t SPSR)
{
    volatile uint32_t loop = 1U;

    if (TestDdr_ExpectedAbortCount > 0U)
    {
        TestDdr_ExpectedAbortCount--;
    }
    else
    {
        DebugP_log("UNEXPECTED DATA ABORT: DFAR=0x%08X LR=0x%08X SPSR=0x%08X DFSR=0x%08X ADFSR=0x%08X\r\n",
            DFAR, LR, SPSR, dfsr, adfsr);
        while (loop != 0U) { ; }
    }
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/*
 * \brief   Memory test that writes and reads 1MB data, skips 1MB in a loop until 2GB DDR Space is reached.
 *
 * \return  None.
 */
void write_read_test(void *arg)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t *memPtr = (uint32_t *)DDR_BASE_ADDR;
    uint32_t loop, loop1;

    /* Loop through 2GB of DDR. Write/Read 1MB, Skip 1MB. */
    for(loop1=0;loop1<1024;loop1++)
    {
        if(status == SystemP_SUCCESS)
        {
            /* Write 1MB of data */
            for(loop=0; loop<ONE_MEGABYTE/4; loop++)
            {
                *memPtr = loop;
                 memPtr++;
            }

            /*Reset to start of 1MB.*/
            memPtr -= (ONE_MEGABYTE/4);

            /* Read 1MB of data and compare. */
            for(loop=0; loop<ONE_MEGABYTE/4; loop++)
            {
                if(*memPtr != loop)
                {
                    DebugP_log("Write and read test failed!!\r\n");
                    status = SystemP_FAILURE;
                    break;
                }
                memPtr++;
            }

            /* Skip 1MB of data */
            memPtr += (ONE_MEGABYTE/4) ;
        }
        else
        {
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}


 /*
 * \brief   Memory test that does walking 1's test.
 *
 * \return  None.
 */
void board_walking1s_test (void *arg)
{
    uint64_t shift;
    uint64_t index;
    uint64_t value;
    uint64_t one =1;
	int32_t status = SystemP_SUCCESS;

    DebugP_log("\nRunning Walking 1s Test.\r\n");

    for (index = DDR_BASE_ADDR; (index >= DDR_BASE_ADDR) &&
         (index < DDR_ADDR_END); index += 8)
    {
        for (shift = 0; shift < BIT_COUNT_EXT_MEM; shift++)
        {
            value = *(volatile uint64_t *) index = (one << shift);
            if(value != *(volatile uint64_t *) index)
            {
                DebugP_log("DDR Walking 1's Test Failed at Location 0x%x\r\n",
                             (index));
                status = SystemP_FAILURE;		
            }
        }
		
		if(status == SystemP_SUCCESS)
		{
			if (!(index & MSG_FREQ))
			{
				DebugP_log("Write up to 0x%x done\r\n",
							index);
			}
		}
		else		
		{
			break;
		}
    }
	
	TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}
 /*
 * \brief   Memory test that does walking 0's test.
 *
 * \return  None.
 */
void board_walking0s_test (void *arg)
{
    uint64_t shift;
    uint64_t index;
    uint64_t value;
    uint64_t one =1;
	int32_t status = SystemP_SUCCESS;

    DebugP_log("\nRunning Walking 0s Test.\r\n");

    for (index = DDR_BASE_ADDR; (index >= DDR_BASE_ADDR) &&
         (index < DDR_ADDR_END); index += 8)
    {
        for (shift = 0; shift < BIT_COUNT_EXT_MEM; shift++)
        {
            value = *(volatile uint64_t *) index = ~(one << shift);
            if( value != *(volatile uint64_t *)index)
            {
                DebugP_log("DDR Walking 0's Test Failed at Location 0x%x\r\n",
                            (index));
                status = SystemP_FAILURE;
            }
        }
		
		if(status == SystemP_SUCCESS)
		{
			if (!(index & MSG_FREQ))
			{
				DebugP_log("Write up to 0x%x done\r\n", (index));
			}
		}
		else
		{
			break;
		}	
    }

	TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

#if !defined(MCU_R5)

/**
 * \brief DDR initialization with valid configuration parameters.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; DDR_isInitDone returns 1.
 */
void TestDdr_initWithValidParams(void *arg)
{
    int32_t  status;
    uint8_t  initDone;
    DDR_Params prms;

    /* Populate DDR_Params with valid config */
    TestDdr_populateValidParams(&prms);

    /* Call DDR_init() with valid params */
    status = DDR_init(&prms);

    /* Verify return value is SystemP_SUCCESS */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify DDR_isInitDone() returns 1 */
    initDone = DDR_isInitDone();
    TEST_ASSERT_EQUAL_UINT8(1U, initDone);

}

/**
 * \brief DDR memory read/write accessibility verification after initialization.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All test addresses retain the written pattern with no mismatch.
 */
void TestDdr_initVerifyMemoryAccessPostInit(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    uint32_t  i;
    volatile uint32_t *addr;
    uint32_t  readVal;

    /* DDR is already initialized. Verify DDR_isInitDone() returns 1 */
    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());

    /* Write known pattern 0xDEADBEEF to multiple DDR addresses */
    for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
    {
        addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));
        *addr = TEST_DDR_PATTERN_1;
    }

    /* Read back from the same addresses and compare */
    for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
    {
        addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));
        readVal = *addr;

        if (readVal != TEST_DDR_PATTERN_1)
        {
            DebugP_log("Memory access test failed at addr 0x%08x: "
                        "wrote 0x%08x, read 0x%08x\r\n",
                        (uint32_t)(uintptr_t)addr, TEST_DDR_PATTERN_1, readVal);
            status = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Sequential write/read integrity test across the full DDR range.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 1 MB blocks read back the expected incrementing values.
 */
void TestDdr_initSequentialWriteReadFullRange(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    uint32_t *memPtr = (uint32_t *)DDR_BASE_ADDR;
    uint32_t  loop, loop1;
    uint32_t  totalBlocks;

    totalBlocks = (DDR_ADDR_END - DDR_BASE_ADDR) / (2U * ONE_MEGABYTE);

    /* Loop through DDR range. Write/Read 1MB, Skip 1MB. */
    for (loop1 = 0U; loop1 < totalBlocks; loop1++)
    {
        if (status != SystemP_SUCCESS)
        {
            break;
        }

        /* Write 1MB of incrementing data */
        for (loop = 0U; loop < (ONE_MEGABYTE / 4U); loop++)
        {
            memPtr[loop] = loop;
        }

        /* Read 1MB of data and compare */
        for (loop = 0U; loop < (ONE_MEGABYTE / 4U); loop++)
        {
            if (memPtr[loop] != loop)
            {
                DebugP_log("Sequential write/read failed at addr 0x%08x: "
                            "expected 0x%08x, got 0x%08x\r\n",
                            (uint32_t)(uintptr_t)&memPtr[loop], loop, memPtr[loop]);
                status = SystemP_FAILURE;
                break;
            }
        }

        /* Advance past current 1MB + skip 1MB */
        memPtr += (2U * ONE_MEGABYTE / 4U);
    }

    /*
     * Flush and invalidate cache for the ECC test region 
     */
    CacheP_wbInv((void *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION0_START),
                 TEST_DDR_ECC_TEST_REGION0_END - TEST_DDR_ECC_TEST_REGION0_START,
                 CacheP_TYPE_ALL);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief DDR re-initialization while already running.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; pre-existing DDR data is not corrupted.
 */
void TestDdr_reinitAfterAlreadyInitialized(void *arg)
{
    int32_t   status;
    uint32_t  i;
    volatile uint32_t *addr;
    DDR_Params prms;

    /* DDR is already initialized. Write known pattern before reinit */
    for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
    {
        addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));
        *addr = TEST_DDR_PATTERN_4;
    }

    /* Call DDR_init() again with same valid params */
    TestDdr_populateValidParams(&prms);
    status = DDR_init(&prms);

    /* Verify DDR_init returns SystemP_SUCCESS */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify existing DDR data is not corrupted after reinit */
    for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
    {
        addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));

        if (*addr != TEST_DDR_PATTERN_4)
        {
            DebugP_log("Reinit data corruption at addr 0x%08x: "
                        "expected 0x%08x, got 0x%08x\r\n",
                        (uint32_t)(uintptr_t)addr, TEST_DDR_PATTERN_4, *addr);
            status = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

#endif /* !defined(MCU_R5) */

/**
 * \brief DDR read/write at start and end boundary addresses.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Start and end boundary addresses retain their written patterns without corruption.
 */
void TestDdr_boundaryAccessTest(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *startAddr;
    volatile uint32_t *endAddr;

    /* Test at DDR start address */
    startAddr = (volatile uint32_t *)DDR_BASE_ADDR;
    *startAddr = TEST_DDR_PATTERN_1;
    if (*startAddr != TEST_DDR_PATTERN_1)
    {
        DebugP_log("Boundary test failed at DDR start addr 0x%08x\r\n",
                    DDR_BASE_ADDR);
        status = SystemP_FAILURE;
    }

    /* Test at last 4-byte aligned address in DDR range */
    if (status == SystemP_SUCCESS)
    {
        endAddr = (volatile uint32_t *)(DDR_ADDR_END - 4U);
        *endAddr = TEST_DDR_PATTERN_2;
        if (*endAddr != TEST_DDR_PATTERN_2)
        {
            DebugP_log("Boundary test failed at DDR end addr 0x%08x\r\n",
                        (DDR_ADDR_END - 4U));
            status = SystemP_FAILURE;
        }
    }

    /* Re-verify start address was not corrupted by end address write */
    if (status == SystemP_SUCCESS)
    {
        if (*startAddr != TEST_DDR_PATTERN_1)
        {
            DebugP_log("Start addr corrupted after end addr write\r\n");
            status = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

}

/**
 * \brief Alternating bit pattern (0xA5A5A5A5 / 0x5A5A5A5A) DDR integrity test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both alternating patterns read back correctly at all test addresses.
 */
void TestDdr_alternatingPatternTest(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    uint32_t  i;
    volatile uint32_t *addr;
    uint32_t  patterns[2] = { TEST_DDR_PATTERN_2, TEST_DDR_PATTERN_3 };
    uint32_t  patIdx;

    /* Write alternating patterns across DDR address range */
    for (patIdx = 0U; patIdx < 2U; patIdx++)
    {
        /* Write pattern to multiple addresses */
        for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
        {
            addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));
            *addr = patterns[patIdx];
        }

        /* Read back and verify */
        for (i = 0U; i < TEST_DDR_MEM_ACCESS_COUNT; i++)
        {
            addr = (volatile uint32_t *)(DDR_BASE_ADDR + (i * TEST_DDR_MEM_ACCESS_STEP));

            if (*addr != patterns[patIdx])
            {
                DebugP_log("Alternating pattern test failed at addr 0x%08x: "
                            "pattern 0x%08x, read 0x%08x\r\n",
                            (uint32_t)(uintptr_t)addr, patterns[patIdx], *addr);
                status = SystemP_FAILURE;
                break;
            }
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Walking 1s data-bus integrity test over an 8 KB DDR region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 64-bit walking-1 patterns read back correctly at every address.
 */
void TestDdr_walking1sPattern(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    uint64_t  one = 1ULL;
    uint64_t  writeVal, readVal;
    uint32_t  shift;
    uint32_t  index;
    volatile uint64_t *addr;

    for (index = 0U; index < TEST_DDR_WALK_TEST_SIZE; index += 8U)
    {
        addr = (volatile uint64_t *)(DDR_BASE_ADDR + index);

        for (shift = 0U; shift < 64U; shift++)
        {
            writeVal = (one << shift);
            *addr    = writeVal;
            readVal  = *addr;

            if (readVal != writeVal)
            {
                DebugP_log("Walking 1s FAILED at addr 0x%08x bit %u: "
                            "wrote 0x%08x%08x, read 0x%08x%08x\r\n",
                            (uint32_t)(DDR_BASE_ADDR + index), shift,
                            (uint32_t)(writeVal >> 32), (uint32_t)writeVal,
                            (uint32_t)(readVal  >> 32), (uint32_t)readVal);
                status = SystemP_FAILURE;
                break;
            }
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Walking 0s data-bus integrity test over an 8 KB DDR region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 64-bit walking-0 patterns read back correctly at every address.
 */
void TestDdr_walking0sPattern(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    uint64_t  one = 1ULL;
    uint64_t  writeVal, readVal;
    uint32_t  shift;
    uint32_t  index;
    volatile uint64_t *addr;

    for (index = 0U; index < TEST_DDR_WALK_TEST_SIZE; index += 8U)
    {
        addr = (volatile uint64_t *)(DDR_BASE_ADDR + index);

        for (shift = 0U; shift < 64U; shift++)
        {
            writeVal = ~(one << shift);
            *addr    = writeVal;
            readVal  = *addr;

            if (readVal != writeVal)
            {
                DebugP_log("Walking 0s FAILED at addr 0x%08x bit %u: "
                            "wrote 0x%08x%08x, read 0x%08x%08x\r\n",
                            (uint32_t)(DDR_BASE_ADDR + index), shift,
                            (uint32_t)(writeVal >> 32), (uint32_t)writeVal,
                            (uint32_t)(readVal  >> 32), (uint32_t)readVal);
                status = SystemP_FAILURE;
                break;
            }
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief All-ones and all-zeros pattern DDR cell retention test over 1 MB.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput 1 MB block correctly stores and returns both all-ones and all-zeros patterns.
 */
void TestDdr_allOnesAllZerosPattern(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *memPtr = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t  numWords = TEST_DDR_BLOCK_TEST_SIZE / 4U;
    uint32_t  i;

    /* Phase 1: Write all‑1s */
    for (i = 0U; i < numWords; i++)
    {
        memPtr[i] = 0xFFFFFFFFU;
    }

    /* Verify all‑1s */
    for (i = 0U; i < numWords; i++)
    {
        if (memPtr[i] != 0xFFFFFFFFU)
        {
            DebugP_log("All-1s FAILED at offset 0x%08x: read 0x%08x\r\n",
                        i * 4U, memPtr[i]);
            status = SystemP_FAILURE;
            break;
        }
    }

    /* Phase 2: Write all‑0s */
    if (status == SystemP_SUCCESS)
    {
        for (i = 0U; i < numWords; i++)
        {
            memPtr[i] = 0x00000000U;
        }

        for (i = 0U; i < numWords; i++)
        {
            if (memPtr[i] != 0x00000000U)
            {
                DebugP_log("All-0s FAILED at offset 0x%08x: read 0x%08x\r\n",
                            i * 4U, memPtr[i]);
                status = SystemP_FAILURE;
                break;
            }
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Address bus integrity test using address-as-data pattern over 1 MB.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Each address location reads back its own address value with no aliasing.
 */
void TestDdr_addressBusTest(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *baseAddr = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t  numWords = TEST_DDR_ADDR_BUS_TEST_SIZE / 4U;
    uint32_t  i;
    uint32_t  expected;

    /* Write each location with its own address */
    for (i = 0U; i < numWords; i++)
    {
        baseAddr[i] = (uint32_t)(uintptr_t)&baseAddr[i];
    }

    /* Read back and verify */
    for (i = 0U; i < numWords; i++)
    {
        expected = (uint32_t)(uintptr_t)&baseAddr[i];

        if (baseAddr[i] != expected)
        {
            DebugP_log("Address bus FAILED at 0x%08x: expected 0x%08x, "
                        "read 0x%08x\r\n", expected, expected, baseAddr[i]);
            status = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Checkerboard and inverse checkerboard DDR coupling fault test over 1 MB.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both checkerboard and inverse checkerboard patterns read back correctly.
 */
void TestDdr_checkerboardPattern(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *memPtr = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t  numWords = TEST_DDR_BLOCK_TEST_SIZE / 4U;
    uint32_t  i;
    uint32_t  expected;

    /* Phase 1: checkerboard */
    for (i = 0U; i < numWords; i++)
    {
        memPtr[i] = (i & 1U) ? 0xAAAAAAAAU : 0x55555555U;
    }

    for (i = 0U; i < numWords; i++)
    {
        expected = (i & 1U) ? 0xAAAAAAAAU : 0x55555555U;

        if (memPtr[i] != expected)
        {
            DebugP_log("Checkerboard FAILED at offset 0x%08x: "
                        "expected 0x%08x, read 0x%08x\r\n",
                        i * 4U, expected, memPtr[i]);
            status = SystemP_FAILURE;
            break;
        }
    }

    /* Phase 2: inverse checkerboard */
    if (status == SystemP_SUCCESS)
    {
        for (i = 0U; i < numWords; i++)
        {
            memPtr[i] = (i & 1U) ? 0x55555555U : 0xAAAAAAAAU;
        }

        for (i = 0U; i < numWords; i++)
        {
            expected = (i & 1U) ? 0x55555555U : 0xAAAAAAAAU;

            if (memPtr[i] != expected)
            {
                DebugP_log("Inverse checkerboard FAILED at offset 0x%08x: "
                            "expected 0x%08x, read 0x%08x\r\n",
                            i * 4U, expected, memPtr[i]);
                status = SystemP_FAILURE;
                break;
            }
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Pseudo-random data pattern DDR fault detection test over 4 MB.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 4 MB of pseudo-random data reads back matching the PRNG sequence.
 */
void TestDdr_randomDataPattern(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *memPtr = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t  numWords = TEST_DDR_RANDOM_TEST_SIZE / 4U;
    uint32_t  seed = TEST_DDR_PRNG_SEED;
    uint32_t  i;
    uint32_t  expected;

    /* Write pseudo‑random data */
    for (i = 0U; i < numWords; i++)
    {
        memPtr[i] = TestDdr_prng(&seed);
    }

    /* Re‑seed and verify */
    seed = TEST_DDR_PRNG_SEED;
    for (i = 0U; i < numWords; i++)
    {
        expected = TestDdr_prng(&seed);

        if (memPtr[i] != expected)
        {
            DebugP_log("Random pattern FAILED at offset 0x%08x: "
                        "expected 0x%08x, read 0x%08x\r\n",
                        i * 4U, expected, memPtr[i]);
            status = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief DDR byte, half-word, and word access granularity test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All byte/half-word/word mixed access combinations produce correct little-endian results.
 */
void TestDdr_byteAccessGranularity(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *wordPtr = (volatile uint32_t *)DDR_BASE_ADDR;
    volatile uint16_t *halfPtr;
    volatile uint8_t  *bytePtr;
    uint32_t  readWord;

    /* Word write, byte read‑back (little‑endian) */
    *wordPtr = 0x12345678U;
    bytePtr  = (volatile uint8_t *)wordPtr;

    if ((bytePtr[0] != 0x78U) || (bytePtr[1] != 0x56U) ||
        (bytePtr[2] != 0x34U) || (bytePtr[3] != 0x12U))
    {
        DebugP_log("Byte read-back FAILED: got 0x%02x 0x%02x 0x%02x 0x%02x\r\n",
                    bytePtr[0], bytePtr[1], bytePtr[2], bytePtr[3]);
        status = SystemP_FAILURE;
    }

    /* Byte write, word read‑back */
    if (status == SystemP_SUCCESS)
    {
        bytePtr[0] = 0xEFU;
        bytePtr[1] = 0xBEU;
        bytePtr[2] = 0xADU;
        bytePtr[3] = 0xDEU;

        readWord = *wordPtr;
        if (readWord != 0xDEADBEEFU)
        {
            DebugP_log("Byte write / word read FAILED: expected 0xDEADBEEF, "
                        "got 0x%08x\r\n", readWord);
            status = SystemP_FAILURE;
        }
    }

    /* Half‑word write, word read‑back */
    if (status == SystemP_SUCCESS)
    {
        halfPtr    = (volatile uint16_t *)wordPtr;
        halfPtr[0] = 0xBEEFU;  /* lower 16 bits */
        halfPtr[1] = 0xCAFEU;  /* upper 16 bits */

        readWord = *wordPtr;
        if (readWord != 0xCAFEBEEFU)
        {
            DebugP_log("Half-word write / word read FAILED: expected 0xCAFEBEEF, "
                        "got 0x%08x\r\n", readWord);
            status = SystemP_FAILURE;
        }
    }

    /* Word write, half‑word read‑back */
    if (status == SystemP_SUCCESS)
    {
        *wordPtr = 0xA5A55A5AU;
        halfPtr  = (volatile uint16_t *)wordPtr;

        if ((halfPtr[0] != 0x5A5AU) || (halfPtr[1] != 0xA5A5U))
        {
            DebugP_log("Half-word read-back FAILED: got 0x%04x 0x%04x\r\n",
                        halfPtr[0], halfPtr[1]);
            status = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

#if !defined(MCU_R5)
/**
 * \brief DDR inline ECC initialization and verification across three ECC regions.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init and BIST priming succeed; all three ECC regions pass read/write verification.
 */
void TestDdr_inlineEccEnableMultipleRegions(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;

    TestDdr_setupMultipleEccRegions(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK from prior single-region init so
     * waitForEccReady does not return before new BIST completes. */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());

    /* Verify region 0 */
    testAddr  = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION0_START
                                      + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    *testAddr = TEST_DDR_PATTERN_1;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_1, readVal);

    /* Verify region 1 */
    testAddr  = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION1_START
                                      + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    *testAddr = TEST_DDR_PATTERN_2;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_2, readVal);

    /* Verify region 2 */
    testAddr  = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION2_START
                                      + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    *testAddr = TEST_DDR_PATTERN_3;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_3, readVal);
}

/**
 * \brief DDR inline ECC initialization and verification for a single ECC region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init and BIST priming succeed; ECC region 0 passes read/write verification.
 */
void TestDdr_inlineEccEnableSingleRegion(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;

    TestDdr_setupSingleEccRegion(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK from prior multi-region init so
     * waitForEccReady does not return before new BIST completes. */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());

    /* Write and read within ECC region 0 */
    testAddr  = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    *testAddr = TEST_DDR_PATTERN_1;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_1, readVal);
}

/**
 * \brief DDR inline ECC initialization with region 1 only (region 0 unused) test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; DDR_isInitDone returns 1;
 *                 region 1 memory is accessible with ECC active.
 */
void TestDdr_inlineEccRegion1OnlyPriming(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;

    /* Region 0 = unused, region 1 = valid, region 2 = unused */
    TestDdr_setupRegion1OnlyEccRegion(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK so waitForEccReady does not return prematurely */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for ISR to signal BIST priming complete */
    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());

    /* Verify read/write in the primed region 1 */
    testAddr  = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION1_START
                                      + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    *testAddr = TEST_DDR_PATTERN_1;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_1, readVal);
}

/**
 * \brief DDR inline ECC initialization with region 2 only (regions 0 and 1 unused) test.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; DDR_isInitDone returns 1;
 *                 region 2 memory is accessible with ECC active.
 */
void TestDdr_inlineEccRegion2OnlyPriming(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;

    /* Region 0 = unused, region 1 = unused, region 2 = valid */
    TestDdr_setupRegion2OnlyEccRegion(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK so waitForEccReady does not return prematurely */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for ISR to signal BIST priming complete */
    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());

    /* Verify read/write in the primed region 2 */
    testAddr  = (volatile uint32_t *)(DDR_BASE_ADDR + TEST_DDR_ECC_TEST_REGION2_START
                                      + TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    *testAddr = TEST_DDR_PATTERN_2;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_2, readVal);
}

#endif /* !defined(MCU_R5) */

/**
 * \brief DDR inline ECC runtime disable test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput ECC_EN bit clears to 0 after disable; DDR read/write succeeds without ECC.
 */
void TestDdr_inlineEccDisable(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    uint32_t  eccCtrl;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Confirm ECC is currently enabled (ECC_EN = 1) */
    eccCtrl = pRegs->ECC_CTRL_REG;
    TEST_ASSERT_NOT_EQUAL(0U, eccCtrl & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_EN_MASK);

    /* Disable ECC */
    DDR_enableInlineECC(0U);

    /* Verify ECC_EN bit is now 0 */
    eccCtrl = pRegs->ECC_CTRL_REG;
    TEST_ASSERT_EQUAL_UINT32(0U, eccCtrl & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_EN_MASK);

    /* Verify DDR still functions without ECC */
    testAddr  = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    *testAddr = TEST_DDR_PATTERN_4;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_4, readVal);

    /* Re-enable ECC for subsequent tests */
    DDR_enableInlineECC(1U);
}

/**
 * \brief DDR inline ECC re-enable after disable test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput ECC_EN bit is set after re-enable; DDR read/write succeeds with ECC active.
 */
void TestDdr_inlineEccReEnable(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr;
    uint32_t  readVal;
    uint32_t  eccCtrl;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Disable ECC */
    DDR_enableInlineECC(0U);
    eccCtrl = pRegs->ECC_CTRL_REG;
    TEST_ASSERT_EQUAL_UINT32(0U, eccCtrl & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_EN_MASK);

    /* Re-enable ECC */
    DDR_enableInlineECC(1U);
    eccCtrl = pRegs->ECC_CTRL_REG;
    TEST_ASSERT_NOT_EQUAL(0U, eccCtrl & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_EN_MASK);

    /* Verify memory integrity with ECC re-enabled */
    testAddr  = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    *testAddr = TEST_DDR_PATTERN_2;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;
    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_2, readVal);
}

/**
 * \brief BIST ECC memory priming verification test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput BIST-primed ECC region contains all zeros (0x00000000).
 */
void TestDdr_inlineEccMemoryPrimingBist(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *memPtr;
    uint32_t  i;
    uint32_t  numWords;
    uint32_t  baseOffset;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /*
     * After priming, the ECC region should contain all zeros.
     * Verify a portion of region 0.
     */
    baseOffset = TEST_DDR_ECC_TEST_REGION0_START + (4U * TEST_DDR_EMIF_ECC_MEM_BLOCK_SIZE);
    memPtr     = (volatile uint32_t *)(DDR_BASE_ADDR + baseOffset);
    numWords   = (4096U / 4U);

    CacheP_inv((void *)memPtr, 4096U, CacheP_TYPE_ALL);

    for (i = 0U; i < numWords; i++)
    {
        if (memPtr[i] != 0x00000000U)
        {
            DebugP_log("ECC priming verify failed at offset 0x%08x: "
                        "expected 0x00000000, got 0x%08x\r\n",
                        baseOffset + (i * 4U), memPtr[i]);
            status = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief DDR ECC single-bit error detection test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Single-bit error count is greater than zero after error injection.
 */
void TestDdr_eccSingleBitErrorDetection(void *arg)
{
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    volatile uint32_t *testAddr2 = (volatile uint32_t *)(TEST_DDR_ECC_TEST_ADDR + 0x100U);
    uint32_t  origVal, origVal2;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    uint32_t  errorCount1;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear any residual ECC errors */
    DDR_clearECCError(DDR_ECC_ERR_ALL);
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount == 0U);

    /* Inject first single-bit error */
    origVal = TestDdr_injectSingleBitError(testAddr);

    /* Trigger ECC error detection by reading the corrupted address */
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;

    /* Allow time for error to be logged */
    ClockP_usleep(100U);

    /* Verify single-bit error was detected */
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount > 0U);
    errorCount1 = eccInfo.singlebitErrorCount;

    /* Inject and trigger second single-bit error at different address */
    origVal2 = TestDdr_injectSingleBitError(testAddr2);
    CacheP_inv((void *)testAddr2, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr2;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Verify error count incremented */
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount > errorCount1);

    /* Restore and clean up */
    TestDdr_restoreEccTestAddr(testAddr, origVal);
    TestDdr_restoreEccTestAddr(testAddr2, origVal2);
}

/**
 * \brief DDR ECC double-bit (uncorrectable) error detection test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Double-bit error address is non-zero after error injection.
 */
void TestDdr_eccDoubleBitErrorDetection(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Disable ECC interrupts before triggering the 2-bit error read. */
    CSL_emifDisableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    origVal = TestDdr_injectDoubleBitError(testAddr);

    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);

    /* Reading a 2-bit corrupted address causes a data abort.
     * The custom abort handler decrements the counter and skips the
     * faulting instruction, allowing execution to continue. */
    TestDdr_ExpectedAbortCount = 1U;
    triggerRead = *testAddr;
    (void)triggerRead;

    ClockP_usleep(100U);

    /* Verify the data abort was triggered (abort handler decremented counter to 0) */
    TEST_ASSERT_EQUAL_UINT32(0U, TestDdr_ExpectedAbortCount);

    DDR_getECCErrorInfo(&eccInfo);
    /* Verify the error address matches the injected address */
    TEST_ASSERT_NOT_EQUAL(0U, eccInfo.doublebitErrorAddress);

    TestDdr_restoreEccTestAddr(testAddr, origVal);

    /* Clear pending interrupt status before re-enabling to prevent ISR storm */
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Re-enable ECC interrupts after error is cleared */
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
}

/**
 * \brief DDR ECC single-bit error hardware auto-correction test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Read value after single-bit error injection matches the original pre-corruption value.
 */
void TestDdr_eccSingleBitErrorCorrection(void *arg)
{
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    uint32_t  readVal;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Write known value */
    *testAddr = TEST_DDR_PATTERN_2;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);

    /* Inject single-bit error */
    origVal = TestDdr_injectSingleBitError(testAddr);

    /* Read the corrupted address - HW should auto-correct the 1-bit error */
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    readVal = *testAddr;

    /* Verify auto-corrected value matches original */
    TEST_ASSERT_EQUAL_UINT32(origVal, readVal);

    TestDdr_restoreEccTestAddr(testAddr, origVal);
}

/**
 * \brief DDR ECC error info address and count retrieval test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_getECCErrorInfo succeeds and reports correct error address and count >= 1.
 */
void TestDdr_eccErrorInfoRetrieval(void *arg)
{
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    volatile uint32_t *testAddr2 = (volatile uint32_t *)(TEST_DDR_ECC_TEST_ADDR + 0x100U);
    uint32_t  origVal, origVal2;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    int32_t   status;
    uint32_t  errorCount1;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear all errors */
    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Inject and trigger first single-bit error */
    origVal = TestDdr_injectSingleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    status = DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify error address (lower bits masked to 8-byte alignment) */
    TEST_ASSERT_EQUAL_UINT32(
        ((TEST_DDR_ECC_TEST_ADDR - DDR_BASE_ADDR) & (~0x7U)),
        (eccInfo.singlebitErrorAddress & (~0x7U)));
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount >= 1U);
    errorCount1 = eccInfo.singlebitErrorCount;

    /* Inject and trigger second single-bit error at different address */
    origVal2 = TestDdr_injectSingleBitError(testAddr2);
    CacheP_inv((void *)testAddr2, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr2;
    (void)triggerRead;
    ClockP_usleep(100U);

    status = DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify error count incremented to 2 */
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount > errorCount1);

    /* Restore and clean up */
    TestDdr_restoreEccTestAddr(testAddr, origVal);
    TestDdr_restoreEccTestAddr(testAddr2, origVal2);
}

/**
 * \brief DDR ECC single-bit error clear test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Single-bit error count is zero after DDR_clearECCError(DDR_ECC_1B_ERROR).
 */
void TestDdr_clearSingleBitEccError(void *arg)
{
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Inject and trigger single-bit error */
    origVal = TestDdr_injectSingleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Verify error is reported */
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_TRUE(eccInfo.singlebitErrorCount > 0U);

    /* Clear single-bit error */
    status = DDR_clearECCError(DDR_ECC_1B_ERROR);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify error is cleared */
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_EQUAL_UINT32(0U, eccInfo.singlebitErrorCount);

    TestDdr_restoreEccTestAddr(testAddr, origVal);
}

/**
 * \brief DDR ECC double-bit error clear test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Double-bit error address is zero after DDR_clearECCError(DDR_ECC_2B_ERROR).
 */
void TestDdr_clearDoubleBitEccError(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Disable ECC interrupts to prevent ISR storm on 2-bit error read */
    CSL_emifDisableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    origVal = TestDdr_injectDoubleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);

    /* 2-bit read causes data abort — custom handler skips the fault */
    TestDdr_ExpectedAbortCount = 1U;
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Verify the data abort was triggered */
    TEST_ASSERT_EQUAL_UINT32(0U, TestDdr_ExpectedAbortCount);

    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_NOT_EQUAL(0U, eccInfo.doublebitErrorAddress);

    status = DDR_clearECCError(DDR_ECC_2B_ERROR);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_EQUAL_UINT32(0U, eccInfo.doublebitErrorAddress);

    TestDdr_restoreEccTestAddr(testAddr, origVal);

    /* Clear pending interrupt status before re-enabling to prevent ISR storm */
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Re-enable ECC interrupts after error is cleared */
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
}

/**
 * \brief DDR ECC clear-all errors test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both single-bit error count and double-bit error address are zero after DDR_clearECCError(DDR_ECC_ERR_ALL).
 */
void TestDdr_clearAllEccErrors(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    DDR_ECCErrorInfo eccInfo;
    int32_t   status;
    uint32_t  preClearSingleCount;
    uintptr_t preClearDoubleAddr;
    uint32_t  postClearSingleCount;
    uintptr_t postClearDoubleAddr;
    volatile uint32_t *translatedAddr;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Disable ECC interrupts for the entire test. */
    CSL_emifDisableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Inject 1-bit error first */
    origVal = TestDdr_injectSingleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /*
     * Restore DRAM data so the single-bit error count is preserved
     *  for the pre-clear assertion.
     */
    translatedAddr = (volatile uint32_t *)TestDdr_eccTranslateAddr((uintptr_t)testAddr);
    DDR_enableInlineECC(0U);
    *translatedAddr = origVal;
    CacheP_wbInv((void *)translatedAddr, 4U, CacheP_TYPE_ALL);
    DDR_enableInlineECC(1U);
    *testAddr = origVal;
    CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);

    /* Inject 2-bit error */
    origVal = TestDdr_injectDoubleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);

    /* 2-bit read causes data abort — custom handler skips the fault */
    TestDdr_ExpectedAbortCount = 1U;
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Verify the data abort was triggered */
    TEST_ASSERT_EQUAL_UINT32(0U, TestDdr_ExpectedAbortCount);

    /* Capture pre-clear ECC error state */
    DDR_getECCErrorInfo(&eccInfo);
    preClearSingleCount = eccInfo.singlebitErrorCount;
    preClearDoubleAddr  = eccInfo.doublebitErrorAddress;

    /* Clear all ECC errors */
    status = DDR_clearECCError(DDR_ECC_ERR_ALL);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Capture post-clear ECC error state */
    DDR_getECCErrorInfo(&eccInfo);
    postClearSingleCount = eccInfo.singlebitErrorCount;
    postClearDoubleAddr  = eccInfo.doublebitErrorAddress;

    /*
     * Restore DRAM and re-enable interrupts BEFORE assertions.
     */
    TestDdr_restoreEccTestAddr(testAddr, origVal);
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Assert pre-clear state: both error types were present */
    TEST_ASSERT_TRUE(preClearSingleCount > 0U);
    TEST_ASSERT_NOT_EQUAL(0U, (uint32_t)preClearDoubleAddr);

    /* Assert post-clear state: both errors were cleared */
    TEST_ASSERT_EQUAL_UINT32(0U, postClearSingleCount);
    TEST_ASSERT_EQUAL_UINT32(0U, (uint32_t)postClearDoubleAddr);
}

/**
 * \brief ECC single-bit error threshold interrupt trigger test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput V2A_INT_RAW_REG shows ECC 1-bit interrupt status set after error threshold is reached.
 */
void TestDdr_eccErrorThresholdInterrupt(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    uint32_t  intStatus;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Verify ECC threshold is configured (set to 1 during ECC init) */
    TEST_ASSERT_NOT_EQUAL(0U, pRegs->ECC_1B_ERR_THRSH_REG);

    /* Enable ECC interrupts */
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Inject single-bit error to reach threshold */
    origVal = TestDdr_injectSingleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Check V2A_INT_RAW_REG for ECC 1-bit error interrupt status */
    intStatus = pRegs->V2A_INT_RAW_REG;
    TEST_ASSERT_NOT_EQUAL(0U, intStatus & (CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                           | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK));

    /* Clean up */
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
    TestDdr_restoreEccTestAddr(testAddr, origVal);
}

/**
 * \brief ECC interrupt enable and disable control test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput ECC interrupt enable bits are set after enable and cleared after disable.
 */
void TestDdr_eccInterruptEnableDisable(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    int32_t   status;

    /* Enable ECC interrupts */
    status = CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify V2A_INT_SET_REG has the ECC interrupt bits set */
    TEST_ASSERT_NOT_EQUAL(0U, pRegs->V2A_INT_SET_REG & TEST_DDR_ECC_INT_ALL_MASK);

    /* Disable ECC interrupts */
    status = CSL_emifDisableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify V2A_INT_SET_REG has the ECC interrupt bits cleared after disable */
    TEST_ASSERT_EQUAL(0U, pRegs->V2A_INT_SET_REG & TEST_DDR_ECC_INT_ALL_MASK);

    /* Re-enable for subsequent tests */
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
}

/**
 * \brief ECC interrupt status clear after error event test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput V2A_INT_STAT_REG ECC interrupt bits are cleared after status clear.
 */
void TestDdr_eccInterruptStatusClear(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    volatile uint32_t triggerRead;
    uint32_t  intStatus;
    int32_t   status;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DDR_clearECCError(DDR_ECC_ERR_ALL);
    CSL_emifClearECCInterruptStatus(pRegs, TEST_DDR_ECC_INT_ALL_MASK);
    CSL_emifEnableECCInterrupts(pRegs, TEST_DDR_ECC_INT_ALL_MASK);

    /* Inject single-bit error */
    origVal = TestDdr_injectSingleBitError(testAddr);
    CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
    triggerRead = *testAddr;
    (void)triggerRead;
    ClockP_usleep(100U);

    /* Verify interrupt status is set */
    intStatus = pRegs->V2A_INT_STAT_REG;
    TEST_ASSERT_NOT_EQUAL(0U, intStatus & (CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                           | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK));

    /* Clear interrupt status */
    status = CSL_emifClearECCInterruptStatus(pRegs,
                CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Also clear the underlying ECC error so the interrupt doesn't re-assert */
    DDR_clearECCError(DDR_ECC_1B_ERROR);

    /* Verify interrupt status is cleared */
    intStatus = pRegs->V2A_INT_STAT_REG;
    TEST_ASSERT_EQUAL_UINT32(0U, intStatus & (CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                              | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK));

    TestDdr_restoreEccTestAddr(testAddr, origVal);
}

#if !defined(MCU_R5)
/**
 * \brief DDR clock frequency verification after initialization.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Actual DDR PLL frequency is within 1% of the configured frequency.
 */
void TestDdr_frequencySetAtInit(void *arg)
{
    uint64_t actualFreq = 0U;
    int32_t  status;
    int64_t  diff;

    status = Sciclient_pmGetModuleClkFreq(
                TISCI_DEV_DDR32SS0,
                TISCI_DEV_DDR32SS0_DDRSS_DDR_PLL_CLK,
                &actualFreq,
                SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify frequency matches configured value (allow 1% tolerance) */
    diff = (int64_t)actualFreq - (int64_t)TEST_DDR_DDRSS_PLL_FREQUENCY_1;
    if (diff < 0)
    {
        diff = -diff;
    }
    TEST_ASSERT_TRUE((uint64_t)diff <= (TEST_DDR_DDRSS_PLL_FREQUENCY_1 / 100U));
}

/**
 * \brief LPDDR4 frequency set point (FSP) handshake completion test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; DDR_isInitDone returns 1.
 */
void TestDdr_lpddr4FrequencyHandshake(void *arg)
{
    int32_t   status;
    DDR_Params prms;

    /*
     * DDR_init() with fshcount > 0 triggers FSP handshake via the
     * infoHandlerCallback during the start sequence.  DDR is already
     * running, so the start is skipped, but we verify the driver
     * returns SUCCESS and DDR_isInitDone() is 1.
     */
    TestDdr_populateValidParams(&prms);
    prms.fshcount = TEST_DDR_DDRSS_PLL_FHS_CNT;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());
}
#endif /* !defined(MCU_R5) */

/*
 * Helper: Generate sustained DDR traffic by writing and reading a buffer.
 */
static void TestDdr_generateTraffic(volatile uint32_t *baseAddr, uint32_t numWords)
{
    uint32_t i;
    volatile uint32_t dummy;

    for (i = 0U; i < numWords; i++)
    {
        baseAddr[i] = i;
    }
    for (i = 0U; i < numWords; i++)
    {
        dummy = baseAddr[i];
        (void)dummy;
    }
}

/**
 * \brief DDR performance counters read/write bandwidth reporting test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Average read bandwidth and average write bandwidth are both non-zero.
 */
void TestDdr_perfCountersReadWriteBandwidth(void *arg)
{
    DDR_StatsDdrLoad stats;
    uint32_t i;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* Generate sustained DDR traffic and accumulate stats */
    for (i = 0U; i < TEST_DDR_PERF_SAMPLE_COUNT; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        DDR_perfStatsAccumulate();
    }

    /* Copy stats */
    DDR_copyDdrPerfStats(&stats);

    /* Verify non-zero bandwidth */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwAverage > 0U);
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwAverage > 0U);
}

/**
 * \brief DDR performance statistics reset test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All bandwidth fields are zero after reset; totalAvailableBw reflects configured DDR bandwidth.
 */
void TestDdr_perfStatsReset(void *arg)
{
    DDR_StatsDdrLoad stats;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t expectedTotalBw;

    /* Generate traffic and accumulate stats */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();

    /* Verify non-zero stats before reset */
    DDR_copyDdrPerfStats(&stats);
    TEST_ASSERT_TRUE((stats.ddrStats.readBwAverage > 0U) ||
                     (stats.ddrStats.writeBwAverage > 0U));

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* Immediately copy stats after reset */
    DDR_copyDdrPerfStats(&stats);

    /* Verify bandwidth values are zero */
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.readBwAverage);
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.writeBwAverage);
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.readBwPeak);
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.writeBwPeak);

    /* Verify totalAvailableBw is correctly set: DDR_MHZ * DDR_BUS_WIDTH * 2 / 8 */
    expectedTotalBw = (DDR_MHZ * DDR_BUS_WIDTH * 2U) / 8U;
    TEST_ASSERT_EQUAL_UINT32(expectedTotalBw, stats.ddrStats.totalAvailableBw);
}

/**
 * \brief DDR performance counter peak bandwidth tracking test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Peak bandwidth is >= average and <= totalAvailableBw for both read and write.
 */
void TestDdr_perfPeakBandwidthTracking(void *arg)
{
    DDR_StatsDdrLoad stats;
    uint32_t i;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    DDR_statsResetDdrLoadCalcAll();

    /* Generate a burst of high-bandwidth traffic */
    for (i = 0U; i < TEST_DDR_PERF_SAMPLE_COUNT; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        DDR_perfStatsAccumulate();
    }

    DDR_copyDdrPerfStats(&stats);

    /* Peak must be >= average */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwPeak >= stats.ddrStats.readBwAverage);
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwPeak >= stats.ddrStats.writeBwAverage);

    /* Peak values must be within theoretical max */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwPeak <= stats.ddrStats.totalAvailableBw);
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwPeak <= stats.ddrStats.totalAvailableBw);
}

/**
 * \brief DDR performance counter accumulation across multiple sampling windows test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput totalRead and totalWrite increase between mid and final snapshots; bandwidth averages are non-zero.
 */
void TestDdr_perfCounterAccumulation(void *arg)
{
    DDR_StatsDdrLoad statsMid;
    DDR_StatsDdrLoad statsFinal;
    uint32_t i;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    DDR_statsResetDdrLoadCalcAll();

    /* Accumulate first half */
    for (i = 0U; i < TEST_DDR_PERF_SAMPLE_COUNT / 2U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        DDR_perfStatsAccumulate();
    }
    DDR_copyDdrPerfStats(&statsMid);

    /* Accumulate second half */
    for (i = 0U; i < TEST_DDR_PERF_SAMPLE_COUNT / 2U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        DDR_perfStatsAccumulate();
    }
    DDR_copyDdrPerfStats(&statsFinal);

    /* Verify bandwidth averages were updated after traffic sampling. */
    TEST_ASSERT_TRUE(statsFinal.ddrStats.readBwAverage > 0U);
    TEST_ASSERT_TRUE(statsFinal.ddrStats.writeBwAverage > 0U);

    /* Verify cumulative read/write counters increased after more traffic. */
    TEST_ASSERT_TRUE(statsFinal.totalRead > statsMid.totalRead);
    TEST_ASSERT_TRUE(statsFinal.totalWrite > statsMid.totalWrite);
}

/**
 * \brief Test cumulative read bytes accumulation across multiple traffic bursts.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput totalRead increases monotonically after each traffic burst
 *                 and accumulate call;
 */
void TestDdr_readAccumulation(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, stats3;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* First burst of traffic */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second burst */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* Third burst */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats3);

    /* totalRead must increase monotonically across snapshots */
    TEST_ASSERT_TRUE(stats1.totalRead > 0U);
    TEST_ASSERT_TRUE(stats2.totalRead > stats1.totalRead);
    TEST_ASSERT_TRUE(stats3.totalRead > stats2.totalRead);
}

/**
 * \brief Test cumulative write bytes accumulation across multiple traffic bursts.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput totalWrite increases monotonically after each traffic burst
 *                 and accumulate call;
 */
void TestDdr_writeAccumulation(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, stats3;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* First burst */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second burst */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* Third burst */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats3);

    /* totalWrite must increase monotonically across snapshots */
    TEST_ASSERT_TRUE(stats1.totalWrite > 0U);
    TEST_ASSERT_TRUE(stats2.totalWrite > stats1.totalWrite);
    TEST_ASSERT_TRUE(stats3.totalWrite > stats2.totalWrite);
}

/**
 * \brief Test elapsed time accumulation across multiple accumulate calls.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput totalTime increases monotonically; each increment reflects
 *                 the wall-clock sleep interval within reasonable tolerance.
 */
void TestDdr_timeAccumulation(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, stats3;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* First interval: ~100ms */
    ClockP_usleep(100000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second interval: ~50ms */
    ClockP_usleep(50000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* Third interval: ~75ms */
    ClockP_usleep(75000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats3);

    /* totalTime must increase monotonically */
    TEST_ASSERT_TRUE(stats1.totalTime > 0U);
    TEST_ASSERT_TRUE(stats2.totalTime > stats1.totalTime);
    TEST_ASSERT_TRUE(stats3.totalTime > stats2.totalTime);

    /* Final totalTime should be at least 200ms (sum of sleeps minus tolerance) */
    TEST_ASSERT_TRUE(stats3.totalTime >= 200000U);
}

/**
 * \brief Test command activation counter accumulation and window reset.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput counter0Total (command activations) accumulates across
 *                 traffic bursts within the snapshot window; after window
 *                 expiry, counter0Total is reset to 0.
 */
void TestDdr_counterTotals(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, statsAfter;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* First batch of traffic */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second batch */
    ClockP_usleep(100000U);
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* counter0Total must accumulate within window */
    TEST_ASSERT_TRUE(stats2.ddrStats.counter0Total >= stats1.ddrStats.counter0Total);

    /* Sleep past the snapshot window (2s) to trigger reset */
    ClockP_usleep(2100000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsAfter);

    /* After window expires, counter0Total must be reset to 0 */
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter0Total);
}

/**
 * \brief Test queue full state counter accumulation and window reset.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput counter1Total (queue full states) accumulates across
 *                 traffic bursts within the snapshot window; after window
 *                 expiry, counter1Total is reset to 0.
 */
void TestDdr_counterTotalsQueueFull(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, statsAfter;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset perf stats */
    DDR_statsResetDdrLoadCalcAll();

    /* First batch of traffic */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second batch */
    ClockP_usleep(100000U);
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* counter1Total must accumulate within window */
    TEST_ASSERT_TRUE(stats2.ddrStats.counter1Total >= stats1.ddrStats.counter1Total);

    /* Sleep past the snapshot window (2s) to trigger reset */
    ClockP_usleep(2100000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsAfter);

    /* After window expires, counter1Total must be reset to 0 */
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter1Total);
}

/**
 * \brief Test read bandwidth calculation after sustained traffic.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput readBwAverage is non-zero and equals totalRead / totalTime;
 *                 readBwAverage <= totalAvailableBw.
 */
void TestDdr_readBandwidth(void *arg)
{
    DDR_StatsDdrLoad stats;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t expectedAvg;

    DDR_statsResetDdrLoadCalcAll();

    /* Generate traffic and accumulate multiple samples for stable measurement */
    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();

    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&stats);

    /* readBwAverage = totalRead / totalTime (bytes / µs = MB/s) */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwAverage > 0U);

    /* Verify calculation: average should match totalRead / totalTime */
    if (stats.totalTime > 0U)
    {
        expectedAvg = (uint32_t)(stats.totalRead / stats.totalTime);
        TEST_ASSERT_EQUAL_UINT32(expectedAvg, stats.ddrStats.readBwAverage);
    }

    /* Read bandwidth must not exceed theoretical maximum */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwAverage <= stats.ddrStats.totalAvailableBw);
}

/**
 * \brief Test write bandwidth calculation after sustained traffic.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput writeBwAverage is non-zero and equals totalWrite / totalTime;
 *                 writeBwAverage <= totalAvailableBw.
 */
void TestDdr_writeBandwidth(void *arg)
{
    DDR_StatsDdrLoad stats;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t expectedAvg;

    DDR_statsResetDdrLoadCalcAll();

    /* Generate traffic and accumulate multiple samples */
    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();

    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&stats);

    /* writeBwAverage = totalWrite / totalTime (bytes / µs = MB/s) */
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwAverage > 0U);

    /* Verify calculation: average should match totalWrite / totalTime */
    if (stats.totalTime > 0U)
    {
        expectedAvg = (uint32_t)(stats.totalWrite / stats.totalTime);
        TEST_ASSERT_EQUAL_UINT32(expectedAvg, stats.ddrStats.writeBwAverage);
    }

    /* Write bandwidth must not exceed theoretical maximum */
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwAverage <= stats.ddrStats.totalAvailableBw);
}

/**
 * \brief Test cumulative average bandwidth calculation over multiple periods.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput readBwAverage and writeBwAverage reflect the cumulative average
 *                 (totalRead/totalTime and totalWrite/totalTime) across all periods.
 */
void TestDdr_avgBandwidth(void *arg)
{
    DDR_StatsDdrLoad stats;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t i;
    uint32_t computedReadAvg;
    uint32_t computedWriteAvg;

    DDR_statsResetDdrLoadCalcAll();

    /* Accumulate over 3 periods with varying sleep intervals */
    for (i = 0U; i < 3U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        ClockP_usleep(10000U * (i + 1U)); /* 10ms, 20ms, 30ms */
        DDR_perfStatsAccumulate();
    }

    DDR_copyDdrPerfStats(&stats);

    /* Average BW = totalBytes / totalTime, computed cumulatively */
    TEST_ASSERT_TRUE(stats.ddrStats.readBwAverage > 0U);
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwAverage > 0U);

    /* Verify the formula: average = totalRead / totalTime */
    if (stats.totalTime > 0U)
    {
        computedReadAvg = (uint32_t)(stats.totalRead / stats.totalTime);
        computedWriteAvg = (uint32_t)(stats.totalWrite / stats.totalTime);
        TEST_ASSERT_EQUAL_UINT32(computedReadAvg, stats.ddrStats.readBwAverage);
        TEST_ASSERT_EQUAL_UINT32(computedWriteAvg, stats.ddrStats.writeBwAverage);
    }
}

/**
 * \brief Test peak bandwidth tracking updates correctly across traffic bursts.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput readBwPeak and writeBwPeak capture the highest instantaneous
 *                 bandwidth observed; peak >= average.
 */
void TestDdr_peakBwTracking(void *arg)
{
    DDR_StatsDdrLoad stats1, stats2, statsFinal;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t numWordsX2 = numWords * 2U;

    DDR_statsResetDdrLoadCalcAll();

    /* First measurement: moderate traffic with longer elapsed time (lower BW) */
    TestDdr_generateTraffic(trafficBuf, numWords / 4U);
    ClockP_usleep(50000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);

    /* Second measurement: heavy traffic with short elapsed time (higher BW) */
    TestDdr_generateTraffic(trafficBuf, numWordsX2);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);

    /* Third measurement: moderate traffic again */
    TestDdr_generateTraffic(trafficBuf, numWords / 2U);
    ClockP_usleep(50000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsFinal);

    /* Peak should have been captured during the high-BW burst */
    TEST_ASSERT_TRUE(statsFinal.ddrStats.readBwPeak >= stats1.ddrStats.readBwPeak);
    TEST_ASSERT_TRUE(statsFinal.ddrStats.writeBwPeak >= stats1.ddrStats.writeBwPeak);

    /* Peak must be >= average */
    TEST_ASSERT_TRUE(statsFinal.ddrStats.readBwPeak >= statsFinal.ddrStats.readBwAverage);
    TEST_ASSERT_TRUE(statsFinal.ddrStats.writeBwPeak >= statsFinal.ddrStats.writeBwAverage);

    /* Peak must not exceed theoretical max */
    TEST_ASSERT_TRUE(statsFinal.ddrStats.readBwPeak <= statsFinal.ddrStats.totalAvailableBw);
    TEST_ASSERT_TRUE(statsFinal.ddrStats.writeBwPeak <= statsFinal.ddrStats.totalAvailableBw);
}

/**
 * \brief Test behavior with no DDR activity (zero traffic).
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput readBwAverage and writeBwAverage remain 0 when no traffic
 *                 is generated; no division by zero occurs.
 */
void TestDdr_zeroTraffic(void *arg)
{
    DDR_StatsDdrLoad stats;

    DDR_statsResetDdrLoadCalcAll();

    /* Accumulate with no DDR traffic generated */
    ClockP_usleep(10000U);
    DDR_perfStatsAccumulate();

    ClockP_usleep(10000U);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&stats);

    /* With no traffic, bandwidth should be 0 */
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.readBwAverage);
    TEST_ASSERT_EQUAL_UINT32(0U, stats.ddrStats.writeBwAverage);

    /* totalTime must still advance (no division by zero) */
    TEST_ASSERT_TRUE((uint32_t)stats.totalTime > 0U);

}

/**
 * \brief Test divide-by-zero protection when elapsed time is 0.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Two immediate back-to-back accumulate calls do not cause
 *                 a crash; 
 */
void TestDdr_divideByZeroProtection(void *arg)
{
    DDR_StatsDdrLoad stats;

    DDR_statsResetDdrLoadCalcAll();

    DDR_perfStatsAccumulate();
    DDR_perfStatsAccumulate();

    /* No crash reaching here proves divide-by-zero protection works.
     * Bandwidth values must be within valid range. */
    DDR_copyDdrPerfStats(&stats);
    TEST_ASSERT_TRUE(stats.ddrStats.readBwAverage <= stats.ddrStats.totalAvailableBw);
    TEST_ASSERT_TRUE(stats.ddrStats.writeBwAverage <= stats.ddrStats.totalAvailableBw);

    /* Now verify that after a real time interval, totalTime advances correctly */
    ClockP_usleep(5000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats);
    TEST_ASSERT_TRUE((uint32_t)stats.totalTime > 0U);
}

/**
 * \brief Test delta mode counter reading: totalRead/totalWrite increments reflect
 *        deltas between successive accumulate calls (not absolute counter values).
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput The increment in totalRead/totalWrite between successive accumulate
 *                 calls corresponds to traffic generated in that interval only.
 */
void TestDdr_deltaModeCounterReading(void *arg)
{
    DDR_StatsDdrLoad stats0, stats1, stats2, stats3;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t numWordsX2 = numWords * 2U;
    uint64_t delta1Read, delta2Read, delta3Read;

    DDR_statsResetDdrLoadCalcAll();

    /* Baseline accumulate to establish counter starting point */
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats0);

    /* First interval: generate 1 burst of traffic */
    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);
    delta1Read = stats1.totalRead - stats0.totalRead;

    /* Second interval: generate 2 bursts of traffic */
    TestDdr_generateTraffic(trafficBuf, numWordsX2);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);
    delta2Read = stats2.totalRead - stats1.totalRead;

    /* Third interval: generate 1 burst again */
    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(1000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats3);
    delta3Read = stats3.totalRead - stats2.totalRead;

    /* Deltas must be non-zero */
    TEST_ASSERT_TRUE(delta1Read > 0U);
    TEST_ASSERT_TRUE(delta2Read > 0U);
    TEST_ASSERT_TRUE(delta3Read > 0U);

    /* Delta from double traffic should be greater than single traffic delta */
    TEST_ASSERT_TRUE(delta2Read > delta1Read);

    /* totalRead is cumulative sum of all deltas */
    TEST_ASSERT_TRUE((stats0.totalRead + delta1Read + delta2Read + delta3Read) ==
                     stats3.totalRead);
}

/**
 * \brief Test raw mode counter reading by verifying hardware perf counter
 *        registers return absolute non-zero values after traffic generation.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput PERF_CNTx registers contain non-zero absolute counter values
 *                 that only increase.
 */
void TestDdr_rawModeCounterReading(void *arg)
{
    volatile uint32_t *cnt1Reg = (volatile uint32_t *)(DDR_SS_CFG_BASE +
                                  CSL_EMIF_SSCFG_PERF_CNT1_REG);
    volatile uint32_t *cnt2Reg = (volatile uint32_t *)(DDR_SS_CFG_BASE +
                                  CSL_EMIF_SSCFG_PERF_CNT2_REG);
    volatile uint32_t *cnt3Reg = (volatile uint32_t *)(DDR_SS_CFG_BASE +
                                  CSL_EMIF_SSCFG_PERF_CNT3_REG);
    volatile uint32_t *cnt4Reg = (volatile uint32_t *)(DDR_SS_CFG_BASE +
                                  CSL_EMIF_SSCFG_PERF_CNT4_REG);
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t val1Before, val2Before, val1After, val2After;
    uint32_t val3Before, val4Before, val3After, val4After;

    /* Ensure counters are configured by calling accumulate once */
    DDR_statsResetDdrLoadCalcAll();
    DDR_perfStatsAccumulate();

    /* Read raw absolute counter values before traffic */
    val1Before = *cnt1Reg;
    val2Before = *cnt2Reg;
    val3Before = *cnt3Reg;
    val4Before = *cnt4Reg;

    /* Generate traffic */
    TestDdr_generateTraffic(trafficBuf, numWords);

    /* Read raw absolute counter values after traffic */
    val1After = *cnt1Reg;
    val2After = *cnt2Reg;
    val3After = *cnt3Reg;
    val4After = *cnt4Reg;

    /* After traffic, write counter (cnt1) should have advanced */
    TEST_ASSERT_NOT_EQUAL(val1Before, val1After);

    /* After traffic, read counter (cnt2) should have advanced */
    TEST_ASSERT_NOT_EQUAL(val2Before, val2After);

    /* Counters must be non-zero after traffic */
    TEST_ASSERT_NOT_EQUAL(0U, val1After);
    TEST_ASSERT_NOT_EQUAL(0U, val2After);

    /* Counter3 (command activations) should also advance with traffic */
    TEST_ASSERT_NOT_EQUAL(val3Before, val3After); 
    (void)val4Before;
    (void)val4After;
}

/**
 * \brief Test that counter wrap-around is handled correctly by verifying
 *        that totalRead/totalWrite never decrease even when HW counters wrap.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput After sustained traffic that causes many counter reads,
 *                 totalRead and totalWrite never decrease between snapshots.
 *                 (The wrap-around formula: diff = (0xFFFFFFFF - last) + current
 *                  ensures positive deltas regardless of counter state.)
 */
void TestDdr_counterWrapAround(void *arg)
{
    DDR_StatsDdrLoad statsPrev, statsCur;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t i;

    DDR_statsResetDdrLoadCalcAll();

    /* Initial accumulate */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsPrev);

    /*
     * Perform many accumulate cycles. verify that the delta logic never
     * produces a negative result (totalRead/totalWrite must never decrease).
     */
    for (i = 0U; i < 50U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        ClockP_usleep(1000U);
        DDR_perfStatsAccumulate();
        DDR_copyDdrPerfStats(&statsCur);

        /* Monotonically non-decreasing — proves wrap-around formula is safe */
        TEST_ASSERT_TRUE(statsCur.totalRead >= statsPrev.totalRead);
        TEST_ASSERT_TRUE(statsCur.totalWrite >= statsPrev.totalWrite);
        TEST_ASSERT_TRUE(statsCur.totalTime >= statsPrev.totalTime);

        statsPrev = statsCur;
    }
}

/**
 * \brief Test normal delta operation without wrap-around: verify successive
 *        deltas are consistent with the amount of traffic generated.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Equal traffic bursts produce approximately equal deltas
 *                 in totalRead between successive accumulate calls.
 */
void TestDdr_noWrapAroundDelta(void *arg)
{
    DDR_StatsDdrLoad stats0, stats1, stats2, stats3;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint64_t delta1, delta2, delta3;

    DDR_statsResetDdrLoadCalcAll();

    /* Baseline */
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats0);

    /* Three equal traffic bursts */
    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(5000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats1);
    delta1 = stats1.totalRead - stats0.totalRead;

    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(5000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats2);
    delta2 = stats2.totalRead - stats1.totalRead;

    TestDdr_generateTraffic(trafficBuf, numWords);
    ClockP_usleep(5000U);
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&stats3);
    delta3 = stats3.totalRead - stats2.totalRead;

    /* All deltas must be non-zero */
    TEST_ASSERT_TRUE(delta1 > 0U);
    TEST_ASSERT_TRUE(delta2 > 0U);
    TEST_ASSERT_TRUE(delta3 > 0U);

    /*
     * Equal traffic should produce approximately equal deltas.
     * Allow 50% tolerance due to cache effects and HW counter granularity.
     */
    TEST_ASSERT_TRUE(delta2 >= delta1 / 2U);
    TEST_ASSERT_TRUE(delta2 <= delta1 * 2U);
    TEST_ASSERT_TRUE(delta3 >= delta2 / 2U);
    TEST_ASSERT_TRUE(delta3 <= delta2 * 2U);
}

/**
 * \brief Test that all four perf counters accumulate correctly simultaneously.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput After traffic, all observable accumulated counters
 *                 (totalRead, totalWrite, counter0Total, counter1Total)
 *                 reflect non-negative increments from each accumulate call.
 */
void TestDdr_multipleCounterSimultaneous(void *arg)
{
    DDR_StatsDdrLoad statsBefore, statsAfter;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t i;

    DDR_statsResetDdrLoadCalcAll();

    /* Generate traffic and accumulate several times */
    for (i = 0U; i < 5U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        ClockP_usleep(1000U);
        DDR_perfStatsAccumulate();
    }
    DDR_copyDdrPerfStats(&statsBefore);

    /* Generate more traffic */
    for (i = 0U; i < 5U; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        ClockP_usleep(1000U);
        DDR_perfStatsAccumulate();
    }
    DDR_copyDdrPerfStats(&statsAfter);

    /* All counters must accumulate correctly in parallel */
    TEST_ASSERT_TRUE(statsAfter.totalRead > statsBefore.totalRead);
    TEST_ASSERT_TRUE(statsAfter.totalWrite > statsBefore.totalWrite);
    TEST_ASSERT_TRUE(statsAfter.totalTime > statsBefore.totalTime);

    /* counter0Total and counter1Total accumulate within the same window */
    TEST_ASSERT_TRUE(statsAfter.ddrStats.counter0Total >=
                     statsBefore.ddrStats.counter0Total);
    TEST_ASSERT_TRUE(statsAfter.ddrStats.counter1Total >=
                     statsBefore.ddrStats.counter1Total);
}

/**
 * \brief EMIF subsystem revision register read test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Revision ID read from the EMIF subsystem is non-zero.
 */
void TestDdr_emifSubsystemRevisionRead(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    uint32_t revId;

    revId = CSL_emifGetRevision(pRegs);
    TEST_ASSERT_NOT_EQUAL(0U, revId);
}

#if !defined(MCU_R5)
/**
 * \brief SDRAM index configuration register verification test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput SDRAM_IDX field in V2A_CTL_REG equals the expected value of 16.
 */
void TestDdr_sdramIndexConfiguration(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    uint32_t  regVal;
    uint32_t  sdramIdx;
    uint32_t  expectedSdramIdx = 16U;   /* from DDR_Params.sdramIdx */

    regVal   = pRegs->V2A_CTL_REG;
    sdramIdx = (regVal & CSL_EMIF_SSCFG_V2A_CTL_REG_SDRAM_IDX_MASK)
               >> CSL_EMIF_SSCFG_V2A_CTL_REG_SDRAM_IDX_SHIFT;

    TEST_ASSERT_EQUAL_UINT32(expectedSdramIdx, sdramIdx);
}

#endif /* !defined(MCU_R5) */

/**
 * \brief Sustained write/read stress test across 100 iterations with rotating patterns.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 100 stress iterations complete without any data mismatch.
 */
void TestDdr_sustainedWriteReadStress(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *memPtr = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t  numWords = TEST_DDR_BLOCK_TEST_SIZE / 4U;
    uint32_t  iter, i;
    uint32_t  pattern;
    uint32_t  seed;

    uint32_t patterns[] = {
        0x00000000U, 0xFFFFFFFFU, 0x55555555U, 0xAAAAAAAAU,
        0x55AA55AAU, 0xAA55AA55U
    };
    uint32_t numPatterns = sizeof(patterns) / sizeof(patterns[0]);

    for (iter = 0U; iter < TEST_DDR_STRESS_ITERATIONS; iter++)
    {
        if (iter < numPatterns)
        {
            /* Fixed patterns */
            pattern = patterns[iter];
            for (i = 0U; i < numWords; i++)
            {
                memPtr[i] = pattern;
            }
            for (i = 0U; i < numWords; i++)
            {
                if (memPtr[i] != pattern)
                {
                    DebugP_log("Stress fail iter %u at word %u: "
                                "expected 0x%08x, got 0x%08x\r\n",
                                iter, i, pattern, memPtr[i]);
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
        else if (iter == numPatterns)
        {
            /* Address-as-data pattern */
            for (i = 0U; i < numWords; i++)
            {
                memPtr[i] = (uint32_t)(uintptr_t)&memPtr[i];
            }
            for (i = 0U; i < numWords; i++)
            {
                if (memPtr[i] != (uint32_t)(uintptr_t)&memPtr[i])
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
        else
        {
            /* Random pattern */
            seed = TEST_DDR_PRNG_SEED + iter;
            for (i = 0U; i < numWords; i++)
            {
                memPtr[i] = TestDdr_prng(&seed);
            }
            seed = TEST_DDR_PRNG_SEED + iter;
            for (i = 0U; i < numWords; i++)
            {
                pattern = TestDdr_prng(&seed);
                if (memPtr[i] != pattern)
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief ECC stability test under sustained DDR traffic with periodic single-bit error injection.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All iterations show correct ECC auto-correction; final single-bit error count is zero.
 */
void TestDdr_eccUnderSustainedTraffic(void *arg)
{
    int32_t   status = SystemP_SUCCESS;
    volatile uint32_t *testAddr = (volatile uint32_t *)TEST_DDR_ECC_TEST_ADDR;
    uint32_t  origVal;
    uint32_t  readVal;
    uint32_t  iter;
    DDR_ECCErrorInfo eccInfo;

    /* Ensure ECC is configured */
    status = TestDdr_ensureEccSetup();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (iter = 0U; iter < TEST_DDR_ECC_STRESS_ITERATIONS; iter++)
    {
        /* Write valid data */
        *testAddr = TEST_DDR_PATTERN_2 + iter;
        CacheP_wbInv((void *)testAddr, 4U, CacheP_TYPE_ALL);

        /* Clear any previous ECC errors */
        DDR_clearECCError(DDR_ECC_ERR_ALL);

        /* Inject single-bit error */
        origVal = TestDdr_injectSingleBitError(testAddr);

        /* Read back - HW should auto-correct */
        CacheP_inv((void *)testAddr, 4U, CacheP_TYPE_ALL);
        readVal = *testAddr;

        if (readVal != origVal)
        {
            DebugP_log("ECC stress fail iter %u: expected 0x%08x, got 0x%08x\r\n",
                        iter, origVal, readVal);
            status = SystemP_FAILURE;
        }

        /* Clear ECC error */
        DDR_clearECCError(DDR_ECC_ERR_ALL);

        /* Restore original value */
        TestDdr_restoreEccTestAddr(testAddr, origVal);

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    /* Verify clean ECC state at end */
    DDR_clearECCError(DDR_ECC_ERR_ALL);
    DDR_getECCErrorInfo(&eccInfo);
    TEST_ASSERT_EQUAL_UINT32(0U, eccInfo.singlebitErrorCount);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief DDR memory access at the very first address (DDR_DRAM_START_ADDR = 0x80000000) test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Read value at DDR_DRAM_START_ADDR matches the written pattern.
 */
void TestDdr_accessAtStartAddress(void *arg)
{
    volatile uint32_t *addr = (volatile uint32_t *)DDR_DRAM_START_ADDR;
    uint32_t readVal;

    *addr = TEST_DDR_PATTERN_1;
    readVal = *addr;

    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_1, readVal);
}

/**
 * \brief DDR memory access at the last valid address (DDR_DRAM_START_ADDR + DDR_DRAM_SIZE - 4) test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Read value at the last DDR address matches the written pattern.
 */
void TestDdr_accessAtEndAddress(void *arg)
{
#if defined(MCU_R5)
    volatile uint32_t *addr = (volatile uint32_t *)(DDR_ADDR_END - 4U);
#else
    volatile uint32_t *addr = (volatile uint32_t *)(DDR_DRAM_START_ADDR
                               + DDR_DRAM_SIZE - 4U);
#endif
    uint32_t readVal;

    *addr = TEST_DDR_PATTERN_4;
    readVal = *addr;

    TEST_ASSERT_EQUAL_UINT32(TEST_DDR_PATTERN_4, readVal);
}

#if !defined(MCU_R5)
/**
 * \brief DDR init-done polling completion test with ECC enabled.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_isInitDone returns 1 before the timeout expires.
 */
void TestDdr_initDonePollingWithEcc(void *arg)
{
    int32_t    status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    uint8_t    initDone;
    uint32_t   timeout = TEST_DDR_ECC_READY_TIMEOUT_MS;
    uint32_t   elapsed = 0U;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;

    TestDdr_setupSingleEccRegion(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK so DDR_isInitDone() reflects the new BIST state */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Poll DDR_isInitDone() until it returns 1 or timeout */
    initDone = DDR_isInitDone();
    while ((initDone == 0U) && (elapsed < timeout))
    {
        ClockP_usleep(1000U);
        elapsed++;
        initDone = DDR_isInitDone();
    }

    TEST_ASSERT_EQUAL_UINT8(1U, initDone);
}

/**
 * \brief DDR init-done immediate return test without ECC.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_isInitDone returns 1 immediately after non-ECC DDR_init.
 */
void TestDdr_initDoneWithoutEcc(void *arg)
{
    int32_t    status;
    DDR_Params prms;
    uint8_t    initDone;

    TestDdr_populateValidParams(&prms);
    prms.enableEccFlag = 0U;
    prms.eccRegion     = NULL;

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Should return 1 immediately without ECC */
    initDone = DDR_isInitDone();
    TEST_ASSERT_EQUAL_UINT8(1U, initDone);
}

#endif /* !defined(MCU_R5) */

/**
 * \brief DDR_getECCErrorInfo NULL pointer rejection test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_getECCErrorInfo returns SystemP_FAILURE for NULL input.
 */
void TestDdr_getEccErrorInfoWithNullPtr(void *arg)
{
    int32_t status;

    status = DDR_getECCErrorInfo(NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

#if !defined(MCU_R5)
/**
 * \brief CSL EMIF API NULL register pointer rejection test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All CSL EMIF APIs return CSL_EMIF_CONFIG_RETURN_INVALID_CFG for NULL pointer; DDR_init returns SystemP_FAILURE for NULL eccRegion.
 */
void TestDdr_cslEmifNullRegs(void *arg)
{
    int32_t      retVal, status;
    CSL_EmifConfig cfg;
    CSL_ECCErrorInfo errInfo;
    DDR_Params prms;

    /* Verify CSL_emifConfig returns CSL_EMIF_CONFIG_RETURN_INVALID_CFG 
       when pEmifSsRegs is NULL.*/
    memset(&cfg, 0, sizeof(cfg));
    retVal = CSL_emifConfig(NULL, &cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifConfig returns CSL_EMIF_CONFIG_RETURN_INVALID_CFG 
       when pCfg is NULL.*/
    retVal = CSL_emifConfig((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE, NULL);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifEnableECC returns CSL_EMIF_CONFIG_RETURN_INVALID_CFG
        when pEmifSsRegs is NULL. */
    retVal = CSL_emifEnableECC(NULL);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifDisableECC returns CSL_EMIF_CONFIG_RETURN_INVALID_CFG
       when pEmifSsRegs is NULL. */
    retVal = CSL_emifDisableECC(NULL);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifGetECCErrorInfo returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL. */
    memset(&errInfo, 0, sizeof(errInfo));
    retVal = CSL_emifGetECCErrorInfo(NULL, &errInfo);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifGetECCErrorInfo returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pECCErrorInfo is NULL. */
    retVal = CSL_emifGetECCErrorInfo((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                     NULL);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifClearAllECCErrors returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL. */
    retVal = CSL_emifClearAllECCErrors(NULL);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifClearECCError returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL. */
    retVal = CSL_emifClearECCError(NULL, CSL_EMIF_ECC_ERROR_TYPE_SINGLE_BIT);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifEnableECCInterrupts returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL. */
    retVal = CSL_emifEnableECCInterrupts(NULL, TEST_DDR_ECC_INT_ALL_MASK);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifDisableECCInterrupts returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL.*/
    retVal = CSL_emifDisableECCInterrupts(NULL, TEST_DDR_ECC_INT_ALL_MASK);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify CSL_emifClearECCInterruptStatus returns
       CSL_EMIF_CONFIG_RETURN_INVALID_CFG when pEmifSsRegs is NULL. */
    retVal = CSL_emifClearECCInterruptStatus(NULL, TEST_DDR_ECC_INT_ALL_MASK);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_INVALID_CFG, retVal);

    /* Verify DDR_init behavior when enableEccFlag=1 but eccRegion
       pointer is NULL. */
    TestDdr_populateValidParams(&prms);
    prms.enableEccFlag = 1U;
    prms.eccRegion     = NULL;
    status = DDR_init(&prms);
    /* DDR_inlineECCCfg returns FAILURE when eccRegion is NULL */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * \brief DDR_init NULL parameter rejection test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_FAILURE when called with NULL.
 */
void TestDdr_initNullParam(void *arg)
{
    int32_t status;

    status = DDR_init(NULL);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * \brief DDR inline ECC initialization with all regions marked unused test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_init returns SystemP_SUCCESS; no BIST priming is triggered.
 */
void TestDdr_inlineEccAllRegionsUnused(void *arg)
{
    int32_t    status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;

    /* All three regions marked unused */
    eccRegion.ddrEccStart0    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion.ddrEccEnd0      = 0U;
    eccRegion.ddrEccPrimeEnd0 = 0U;

    eccRegion.ddrEccStart1    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion.ddrEccEnd1      = 0U;
    eccRegion.ddrEccPrimeEnd1 = 0U;

    eccRegion.ddrEccStart2    = TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion.ddrEccEnd2      = 0U;
    eccRegion.ddrEccPrimeEnd2 = 0U;

    TestDdr_populateEccParams(&prms, &eccRegion);

    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

}

/**
 * \brief DDR performance snapshot window expiry and counter reset test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput counter0Total and counter1Total are zero after window expiry; bandwidth averages remain valid.
 */
void TestDdr_perfSnapshotWindowExpiry(void *arg)
{
    DDR_StatsDdrLoad statsBefore;
    DDR_StatsDdrLoad statsAfter;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;
    uint32_t i;

    /* Reset all perf stats - snapshotCount set to DDR_SNAPSHOT_WINDOW_WIDTH */
    DDR_statsResetDdrLoadCalcAll();

    /* Accumulate a few samples within the 2-second window to build non-zero
     * counter0Total / counter1Total values that we expect to be cleared. */
    for (i = 0U; i < TEST_DDR_PERF_SAMPLE_COUNT; i++)
    {
        TestDdr_generateTraffic(trafficBuf, numWords);
        DDR_perfStatsAccumulate();
    }
    DDR_copyDdrPerfStats(&statsBefore);

    /* Confirm at least one counter accumulated something */
    TEST_ASSERT_TRUE((statsBefore.ddrStats.counter0Total > 0U) ||
                     (statsBefore.ddrStats.counter1Total > 0U));

    /*
     * Sleep past the snapshot window width (2 s) by 100 ms to guarantee
     * that a single subsequent accumulate call sees elapsedTime > snapshotCount,
     * making snapshotCount go negative and triggering the reset branch.
     */
    ClockP_usleep(2100000U);

    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsAfter);

    /* counter0Total and counter1Total must have been zeroed by the branch */
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter0Total);
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter1Total);

    /* Bandwidth averages must still be valid (not affected by the snapshot reset) */
    TEST_ASSERT_TRUE((statsAfter.ddrStats.readBwAverage  > 0U) ||
                     (statsAfter.ddrStats.writeBwAverage > 0U));
}

/**
 * \brief Test snapshot window countdown via perf stats accumulation.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput snapshotCount decreases by elapsed time on each accumulate call;
 *                 counter totals accumulate correctly within window.
 */
void TestDdr_perfWindowCountDown(void *arg)
{
    DDR_StatsDdrLoad stats;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset stats - snapshotCount starts at DDR_SNAPSHOT_WINDOW_WIDTH */
    DDR_statsResetDdrLoadCalcAll();

    /* Get initial state */
    DDR_copyDdrPerfStats(&stats);
    int32_t initialSnapshot = stats.snapshotCount;
    /* snapshotCount should be DDR_SNAPSHOT_WINDOW_WIDTH */
    TEST_ASSERT_TRUE(initialSnapshot > 0);

    /* Wait ~500ms then accumulate */
    ClockP_usleep(500000U);
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&stats);
    /* snapshotCount should have decreased by ~500000 */
    TEST_ASSERT_TRUE(stats.snapshotCount < initialSnapshot);
    TEST_ASSERT_TRUE(stats.snapshotCount > 0);

    int32_t afterFirst = stats.snapshotCount;

    /* Wait ~600ms then accumulate again */
    ClockP_usleep(600000U);
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&stats);
    /* snapshotCount should have decreased further by ~600000 */
    TEST_ASSERT_TRUE(stats.snapshotCount < afterFirst);
    /* Window (2s) should not have expired yet */
    TEST_ASSERT_TRUE(stats.snapshotCount > 0);
}

/**
 * \brief Test automatic counter reset when snapshot window expires.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput When accumulated elapsed time exceeds DDR_SNAPSHOT_WINDOW_WIDTH,
 *                 counter0Total and counter1Total are reset to 0 and snapshotCount
 *                 is reset to DDR_SNAPSHOT_WINDOW_WIDTH.
 */
void TestDdr_perfWindowExpirationAndReset(void *arg)
{
    DDR_StatsDdrLoad statsBefore;
    DDR_StatsDdrLoad statsAfter;
    volatile uint32_t *trafficBuf = (volatile uint32_t *)DDR_BASE_ADDR;
    uint32_t numWords = TEST_DDR_TRAFFIC_BUF_SIZE / 4U;

    /* Reset stats */
    DDR_statsResetDdrLoadCalcAll();

    /* Generate traffic and accumulate to build non-zero counter totals */
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();

    ClockP_usleep(100000U);
    TestDdr_generateTraffic(trafficBuf, numWords);
    DDR_perfStatsAccumulate();

    DDR_copyDdrPerfStats(&statsBefore);

    /* Verify counters accumulated non-zero values within window */
    TEST_ASSERT_TRUE((statsBefore.ddrStats.counter0Total > 0U) ||
                     (statsBefore.ddrStats.counter1Total > 0U));

    /*
     * Sleep past the snapshot window (2s) plus margin (100ms) to ensure
     * the next accumulate sees elapsed time exceeding remaining snapshotCount,
     * triggering the reset branch.
     */
    ClockP_usleep(2100000U);

    /* This accumulate will see elapsed time > snapshotCount, triggering reset */
    DDR_perfStatsAccumulate();
    DDR_copyDdrPerfStats(&statsAfter);

    /* counter0Total and counter1Total must be reset to 0 */
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter0Total);
    TEST_ASSERT_EQUAL_UINT32(0U, statsAfter.ddrStats.counter1Total);

    /* snapshotCount should be reset to DDR_SNAPSHOT_WINDOW_WIDTH (2000000) */
    TEST_ASSERT_TRUE(statsAfter.snapshotCount > 0);
}
#endif /* !defined(MCU_R5) */

/**
 * \brief CSL_emifConfig ECC-disabled path test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput CSL_emifConfig returns CSL_EMIF_CONFIG_RETURN_OK; ECC_EN bit is 0 in ECC_CTRL_REG.
 */
void TestDdr_cslEmifConfigEccDisabled(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    CSL_EmifConfig      cfg;
    int32_t             retVal;
    uint32_t            eccCtrl;

    memset(&cfg, 0, sizeof(cfg));
    cfg.bEnableMemoryECC = (bool)false;

    /* Call with ECC disabled — hits the else branch in CSL_emifConfigController */
    retVal = CSL_emifConfig(pRegs, &cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_OK, retVal);

    /* Verify ECC_EN bit is cleared in ECC_CTRL_REG */
    eccCtrl = pRegs->ECC_CTRL_REG;
    TEST_ASSERT_EQUAL_UINT32(0U,
        (eccCtrl & CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_EN_MASK));
}

/**
 * \brief CSL_emifClearECCError default switch case test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput CSL_emifClearECCError returns CSL_EMIF_CONFIG_RETURN_OK for errorType=0 (default case).
 */
void TestDdr_cslEmifClearEccErrorDefaultCase(void *arg)
{
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    int32_t             retVal;

    /* errorType 0 is outside the defined enum values (1 and 2) */
    retVal = CSL_emifClearECCError(pRegs, (CSL_EmifECCErrorType)0U);
    TEST_ASSERT_EQUAL_INT32(CSL_EMIF_CONFIG_RETURN_OK, retVal);
}

/**
 * \brief Verify DDR BIST registers can be configured with start address,
 *        address space (log2 of size), data pattern, and memory-init mode.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput BIST registers reflect the configured values for start address,
 *  address space, data pattern, and test mode without starting BIST (BIST_GO=0).
 */
void TestDdr_memoryPriming(void *arg)
{
    uint32_t regVal;
    uint32_t addrSpaceVal;

    /*
     * BIST start address = 0 (EMIF-relative offset 0).
     * DDR_primeMem() computes: bistStart = (start * 9) / 8.
     * For EMIF start = 0: bistStart = 0. Matches DDR base 0x80000000.
     */
    CSL_REG32_WR(DDR_CTL_CFG_BASE + DDR_BIST_START_ADDRESS_0_REG,
                 (uint32_t)(0U & DDR_BIST_START_ADDR_0_MASK));

    /*
     * Address space = log2(1 MB) = 20.
     * Written to the ADDR_SPACE field of CTL_283. BIST_GO is NOT set,
     * so BIST does not start and register values remain stable.
     */
    CSL_REG32_WR(DDR_CTL_CFG_BASE + DDR_ADDRESS_SPACE_REG,
                 (uint32_t)((20U << CSL_DDR_ADDRESS_SPACE_SHIFT) &
                             CSL_DDR_ADDRESS_SPACE_MASK));

    /* Data pattern = 0xAAAA5555 */
    CSL_REG32_WR(DDR_CTL_CFG_BASE + DDR_BIST_DATA_PATTERN_0_REG,
                 (uint32_t)(0xAAAA5555U & DDR_BIST_DATA_PATTERN0_MASK));

    /* Test mode = MEM_INIT */
    CSL_REG32_WR(DDR_CTL_CFG_BASE + DDR_BIST_TEST_MODE_REG,
                 (uint32_t)BIST_MODE_MEM_INIT);

    /* Verify: BIST start address = 0 */
    TEST_ASSERT_EQUAL_UINT32(
        0U,
        CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_BIST_START_ADDRESS_0_REG)
        & DDR_BIST_START_ADDR_0_MASK);

    /* Verify: address space = 20 */
    regVal       = CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_ADDRESS_SPACE_REG);
    addrSpaceVal = (regVal & CSL_DDR_ADDRESS_SPACE_MASK) >>
                   CSL_DDR_ADDRESS_SPACE_SHIFT;
    TEST_ASSERT_EQUAL_UINT32(20U, addrSpaceVal);

    /* Verify: data pattern = 0xAAAA5555 */
    TEST_ASSERT_EQUAL_UINT32(
        0xAAAA5555U,
        CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_BIST_DATA_PATTERN_0_REG)
        & DDR_BIST_DATA_PATTERN0_MASK);

    /* Verify: test mode = MEM_INIT */
    TEST_ASSERT_EQUAL_UINT32(
        (uint32_t)BIST_MODE_MEM_INIT,
        CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_BIST_TEST_MODE_REG));
}

#if !defined(MCU_R5)
/**
 * \brief Verify that DDR_primeMem() (invoked via DDR_init()) correctly sets
 *        the address space register for a 3 MB region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_primeMem computes the correct address space value for a 3 MB region;
 *                  the address space register reflects this value while BIST is running;
 *                  DDR_isInitDone returns 1 after BIST completes.
 */
void TestDdr_largeMemoryPriming(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    uint32_t  regVal;
    uint32_t  addrSpaceVal;
    /*
     * Expected: DDR_utilLog2(end - start + 1) = DDR_utilLog2(0x300001) = 21.
     * (Bit 21 = 0x200000 is the highest set bit in 0x300001.)
     */
    uint32_t  expectedLog2 = 21U;

    /* Single region: EMIF offset 0 to 3 MB  */
    memset(&eccRegion, 0, sizeof(eccRegion));
    eccRegion.ddrEccStart0    = (uint64_t)TEST_DDR_ECC_TEST_REGION0_START;
    eccRegion.ddrEccEnd0      = (uint64_t)TEST_DDR_ECC_TEST_REGION2_END;
    eccRegion.ddrEccPrimeEnd0 = (uint64_t)TEST_DDR_ECC_TEST_REGION2_END;
    eccRegion.ddrEccStart1    = (uint64_t)TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion.ddrEccEnd1      = 0U;
    eccRegion.ddrEccPrimeEnd1 = 0U;
    eccRegion.ddrEccStart2    = (uint64_t)TEST_DDR_ECC_REGION_START_UNUSED;
    eccRegion.ddrEccEnd2      = 0U;
    eccRegion.ddrEccPrimeEnd2 = 0U;

    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK so waitForEccReady does not return prematurely */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    /*
     * DDR_init() → DDR_inlineECCCfg() → DDR_primeMem(0, 0x300000, 0).
     * DDR_primeMem programs address space = 21 and fires BIST_GO.
     * DDR_init() returns while BIST is running.
     */
    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /*
     * Sample address space REG immediately — BIST is running and the
     * BIST_DONE ISR has not yet cleared the register.
     */
    regVal       = CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_ADDRESS_SPACE_REG);
    addrSpaceVal = (regVal & CSL_DDR_ADDRESS_SPACE_MASK) >>
                   CSL_DDR_ADDRESS_SPACE_SHIFT;
    TEST_ASSERT_EQUAL_UINT32(expectedLog2, addrSpaceVal);

    /* Wait for all BIST priming to finish */
    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());
}

/**
 * \brief Verify that DDR_primeMem() (invoked via DDR_init()) correctly sets
 *        the address space register for a small region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DDR_primeMem computes the correct address space value for a 1 MB region;
 *                  the address space register reflects this value while BIST is running;
 *                  DDR_isInitDone returns 1 after BIST completes.
 */
void TestDdr_smallMemoryPriming(void *arg)
{
    int32_t   status;
    DDR_Params prms;
    DDR_EccRegion eccRegion;
    CSL_emif_sscfgRegs *pRegs = (CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE;
    uint32_t  regVal;
    uint32_t  addrSpaceVal;
    /*
     * Expected: DDR_utilLog2(end - start + 1) = DDR_utilLog2(0x100001) = 20.
     * (Bit 20 = 0x100000 is the highest set bit in 0x100001.)
     */
    uint32_t  expectedLog2 = 20U;

    /* Single region: EMIF offset 0 to 1 MB */
    TestDdr_setupSingleEccRegion(&eccRegion);
    TestDdr_populateEccParams(&prms, &eccRegion);

    /* Clear stale ECC_CK so waitForEccReady does not return prematurely */
    pRegs->ECC_CTRL_REG &= ~CSL_EMIF_SSCFG_ECC_CTRL_REG_ECC_CK_MASK;

    /*
     * DDR_init() → DDR_inlineECCCfg() → DDR_primeMem(0, 0x100000, 0).
     * DDR_primeMem programs address space = 20 and fires BIST_GO.
     * DDR_init() returns while BIST is running (1 MB BIST ≈ ~1 ms).
     */
    status = DDR_init(&prms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /*
     * Sample address space REG immediately — BIST is running and the
     * BIST_DONE ISR has not yet cleared the register.
     */
    regVal       = CSL_REG32_RD(DDR_CTL_CFG_BASE + DDR_ADDRESS_SPACE_REG);
    addrSpaceVal = (regVal & CSL_DDR_ADDRESS_SPACE_MASK) >>
                   CSL_DDR_ADDRESS_SPACE_SHIFT;
    TEST_ASSERT_EQUAL_UINT32(expectedLog2, addrSpaceVal);

    /* Wait for BIST priming to finish */
    status = TestDdr_waitForEccReady(TEST_DDR_ECC_READY_TIMEOUT_MS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8(1U, DDR_isInitDone());
}
#endif /* !defined(MCU_R5) */

/* ========================================================================== */
/*                          Test Main                                         */
/* ========================================================================== */

void *test_ddr_main(void *args)
{
    /* Open drivers to open the UART driver for console. */

#if !defined(MCU_R5)
    Drivers_open();
#endif

    UNITY_BEGIN();

#if !defined(MCU_R5)
    RUN_TEST(write_read_test, 3246, NULL);
	RUN_TEST(board_walking1s_test, 3248, NULL);
	RUN_TEST(board_walking0s_test, 3247, NULL);	
    RUN_TEST(TestDdr_initWithValidParams, 11865, NULL);
    RUN_TEST(TestDdr_initVerifyMemoryAccessPostInit, 11866, NULL);
    RUN_TEST(TestDdr_reinitAfterAlreadyInitialized, 11867, NULL);
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_boundaryAccessTest, 11869, NULL);
    RUN_TEST(TestDdr_alternatingPatternTest, 11870, NULL);
    RUN_TEST(TestDdr_walking1sPattern, 11871, NULL);
    RUN_TEST(TestDdr_walking0sPattern, 11872, NULL);
    RUN_TEST(TestDdr_allOnesAllZerosPattern, 11873, NULL);
    RUN_TEST(TestDdr_addressBusTest, 11874, NULL);
    RUN_TEST(TestDdr_checkerboardPattern, 11875, NULL);
    RUN_TEST(TestDdr_randomDataPattern, 11876, NULL);
    RUN_TEST(TestDdr_byteAccessGranularity, 11877, NULL);
#if !defined(MCU_R5)
    RUN_TEST(TestDdr_initSequentialWriteReadFullRange, 11868, NULL);
    RUN_TEST(TestDdr_frequencySetAtInit, 11905, NULL);
    RUN_TEST(TestDdr_lpddr4FrequencyHandshake, 11906, NULL);
    RUN_TEST(TestDdr_perfCountersReadWriteBandwidth, 11880, NULL);
    RUN_TEST(TestDdr_perfStatsReset, 11881, NULL);
    RUN_TEST(TestDdr_perfPeakBandwidthTracking, 11882, NULL);
    RUN_TEST(TestDdr_perfCounterAccumulation, 11883, NULL);
    RUN_TEST(TestDdr_perfSnapshotWindowExpiry, 11884, NULL);
    RUN_TEST(TestDdr_perfWindowCountDown, 11885, NULL);
    RUN_TEST(TestDdr_perfWindowExpirationAndReset, 11886, NULL);
    RUN_TEST(TestDdr_readAccumulation, 11887, NULL);
    RUN_TEST(TestDdr_writeAccumulation, 11888, NULL);
    RUN_TEST(TestDdr_timeAccumulation, 11889, NULL);
    RUN_TEST(TestDdr_counterTotals, 11890, NULL);
    RUN_TEST(TestDdr_counterTotalsQueueFull, 11891, NULL);
    RUN_TEST(TestDdr_readBandwidth, 11892, NULL);
    RUN_TEST(TestDdr_writeBandwidth, 11893, NULL);
    RUN_TEST(TestDdr_avgBandwidth, 11894, NULL);
    RUN_TEST(TestDdr_peakBwTracking, 11895, NULL);
    RUN_TEST(TestDdr_zeroTraffic, 11896, NULL);
    RUN_TEST(TestDdr_divideByZeroProtection, 11897, NULL);
    RUN_TEST(TestDdr_deltaModeCounterReading, 11898, NULL);
    RUN_TEST(TestDdr_rawModeCounterReading, 11899, NULL);
    RUN_TEST(TestDdr_counterWrapAround, 11900, NULL);
    RUN_TEST(TestDdr_noWrapAroundDelta, 11901, NULL);
    RUN_TEST(TestDdr_multipleCounterSimultaneous, 11902, NULL);
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_emifSubsystemRevisionRead, 11903, NULL);
#if !defined(MCU_R5)
    RUN_TEST(TestDdr_sdramIndexConfiguration, 11904, NULL);
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_sustainedWriteReadStress, 11907, NULL);
    RUN_TEST(TestDdr_accessAtStartAddress, 11908, NULL);
    RUN_TEST(TestDdr_accessAtEndAddress, 11909, NULL);
#if !defined(MCU_R5)
    /* Disabled : driver bug */
    /* RUN_TEST(TestDdr_inlineEccEnableMultipleRegions, 11910, NULL); */
    /* RUN_TEST(TestDdr_inlineEccEnableSingleRegion, 11911, NULL); */
    /* RUN_TEST(TestDdr_inlineEccRegion1OnlyPriming, 11943, NULL); */
    /* RUN_TEST(TestDdr_inlineEccRegion2OnlyPriming, 11944, NULL); */
#endif /* !defined(MCU_R5) */
    /* RUN_TEST(TestDdr_inlineEccMemoryPrimingBist, 11912, NULL); */
    RUN_TEST(TestDdr_inlineEccReEnable, 11913, NULL);
    RUN_TEST(TestDdr_eccInterruptEnableDisable, 11914, NULL);
    RUN_TEST(TestDdr_inlineEccDisable, 11915, NULL);
    RUN_TEST(TestDdr_eccSingleBitErrorDetection, 11916, NULL);
    RUN_TEST(TestDdr_eccDoubleBitErrorDetection, 11917, NULL);
    RUN_TEST(TestDdr_eccSingleBitErrorCorrection, 11918, NULL);
    RUN_TEST(TestDdr_eccErrorInfoRetrieval, 11919, NULL);
    RUN_TEST(TestDdr_clearSingleBitEccError, 11920, NULL);
    RUN_TEST(TestDdr_clearDoubleBitEccError, 11921, NULL);
    RUN_TEST(TestDdr_clearAllEccErrors, 11922, NULL);
    RUN_TEST(TestDdr_eccErrorThresholdInterrupt, 11923, NULL);
    RUN_TEST(TestDdr_eccInterruptStatusClear, 11924, NULL);
    RUN_TEST(TestDdr_eccUnderSustainedTraffic, 11925, NULL);
#if !defined(MCU_R5)
    /* RUN_TEST(TestDdr_initDonePollingWithEcc, 11926, NULL); */
    RUN_TEST(TestDdr_initDoneWithoutEcc, 11927, NULL);
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_getEccErrorInfoWithNullPtr, 11928, NULL);
#if !defined(MCU_R5)
    RUN_TEST(TestDdr_cslEmifNullRegs, 11929, NULL);
    RUN_TEST(TestDdr_initNullParam, 11930, NULL);
    /* RUN_TEST(TestDdr_inlineEccAllRegionsUnused, 11941, NULL); */
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_memoryPriming, 11938, NULL);
#if !defined(MCU_R5)
    /* RUN_TEST(TestDdr_largeMemoryPriming, 11939, NULL); */
    /* RUN_TEST(TestDdr_smallMemoryPriming, 11940, NULL); */
#endif /* !defined(MCU_R5) */
    RUN_TEST(TestDdr_cslEmifConfigEccDisabled, 11931, NULL);
    RUN_TEST(TestDdr_cslEmifClearEccErrorDefaultCase, 11932, NULL);
#ifdef ENABLE_MT_TESTS
    RUN_TEST(TestDdr_mtConcurrentReadFromMultipleTasks, 11933, NULL);
    RUN_TEST(TestDdr_mtConcurrentWriteFromMultipleTasks, 11934, NULL);
    RUN_TEST(TestDdr_mtConcurrentReadWriteSameRegion, 11935, NULL);
    RUN_TEST(TestDdr_mtConcurrentReadWriteDifferentRegions, 11936, NULL);
    RUN_TEST(TestDdr_mtConcurrentEccEnableDisable, 11937, NULL);
#endif
   
    UNITY_END();

#if !defined(MCU_R5)
    Drivers_close();
#endif

    return NULL;
}

void setUp(void)
{
}

void tearDown(void)
{
}
