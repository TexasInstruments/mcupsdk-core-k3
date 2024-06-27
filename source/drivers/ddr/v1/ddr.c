/******************************************************************************
 * Copyright (c) 2021-2024 Texas Instruments Incorporated - http://www.ti.com
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
 *
 *****************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/hw_include/hw_types.h>
#include <drivers/soc.h>
#include <drivers/ddr.h>
#include <drivers/ddr/v1/cdn_drv.h>
#include <drivers/ddr/v1/csl_emif.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/hw_include/cslr.h>

#if !defined (MCU_R5)
/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

#define DDR_CTL_REG_OFFSET              (0)
#define DDR_SRAM_MAX                    (512U)
#define DDR_TYPE_MASK                   (0xF00U)
#define DDR4_MEMORY                     (0xA00U)
#define LPDDR4_MEMORY                   (0xB00U)
/*FSP MAIN_CTRL_MMR register offsets*/
/* LPDDR4 FSP Clock Change Request Register - DDR Controller to request the DDR PLL clock frequency change (read only)*/
#define DDR_FSP_CLKCHNG_REQ    0x14080U
/* LPDDR4 FSP Clock Change Acknowledge Register - acknowledge a DDR PLL clock frequency change to the DDR Controller (r/w) */
#define DDR_FSP_CLKCHNG_ACK    0x140C0U

#define DDR_CTL_REG_BASE        0x0F308000U
#define DDR_PI_REG_BLOCK_OFFS   0x2000U
#define DDR_PI_0_SFR_OFFS       0x0U
#define DDR_CTL_0_SFR_OFFS      0x0U
#define DDR_PI_87_SFR_OFFS      0x15CU
#define DDR_CTL_350_SFR_OFFS    0x578U
/* Trigger Start bit*/
#define TRIGGER_START_BIT        0x00000B01U

#define KEY0                    0x68EF3490U
#define KEY1                    0xD172BC5AU

#define DDR_REQ_TYPE_0    0
#define DDR_REQ_TYPE_1    1
#define DDR_REQ_TYPE_2    2

/* Writing a 0x1 will clear 1-bit ecc error count */
#define DDR_ECC_1B_ERR_CNT_CLEAR        (1U)

#define DDR_GET_CFG_REG_ADDR(reg)       (DDR_CTL_CFG_BASE+reg)

#define DDR_ECC_REGION_START_RESET_VAL  0xFFFF0000U

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing ECC region params
 */
typedef struct {
    uint64_t startAddr;
    uint64_t endAddr;
    uint64_t pattern;
} DDR_ECCRegion;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t DDR_primeMem(uint64_t start, uint64_t end, uint64_t pattern);
static uint32_t DDR_utilLog2(uint64_t num);
static void DDR_isr(void *arg);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

static LPDDR4_Config gLpddrCfg;
static LPDDR4_PrivateData gLpddrPd;
static uint8_t gDDRInitDoneFlag = 0U;

static DDR_ECCRegion gDDRECCRegion[3] =
{
    {
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU
    },
    {
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU
    },
    {
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU,
        0xFFFFFFFFFFFFFFFFU
    },
};

/* ========================================================================== */
/*                         Extern Function declerations                       */
/* ========================================================================== */
extern void DDR_socEnableVttRegulator(void);
extern void DDR_ResetDDR_PLL(void);


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static void DDR_setFreq(uint64_t freq)
{
    uint32_t module = TISCI_DEV_DDR32SS0;
    uint32_t clock = TISCI_DEV_DDR32SS0_DDRSS_DDR_PLL_CLK;
    int32_t status = SystemP_SUCCESS;

    status = Sciclient_pmSetModuleClkFreq(module,
                                        clock,
                                        freq,
                                        TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                        SystemP_WAIT_FOREVER);

    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("SOC_moduleSetClockFrequency failed !!!\n");
    }
}

static void DDR_changeFreqAck(DDR_Params *prms)
{
    uint32_t req, req_type, counter;

    /*unlock MMR reg 5*/
    /*Partition5 lockkey0*/
    HW_WR_REG32((CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0), KEY0);
    /*Partition5 lockkey1*/
    HW_WR_REG32(( CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1), KEY1);

    ClockP_usleep(500);

    for(counter = 0; counter < prms->fshcount; counter++)
    {
        req = (HW_RD_REG32(CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_REQ) & 0x80);
        while((req ) == 0x0)
        {
            req = (HW_RD_REG32(CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_REQ) & 0x80);
        }

        req_type = HW_RD_REG32(CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_REQ) & 0x03;

        if(req_type == DDR_REQ_TYPE_1)
        {
            DDR_setFreq(prms->clk1Freq);
        }
        else if(req_type == DDR_REQ_TYPE_2)
        {
            DDR_setFreq(prms->clk2Freq);
        }
        else if(req_type == DDR_REQ_TYPE_0)
        {
            DDR_setFreq(25000000);
        }

        /*set the ack bit*/
        HW_WR_REG32((CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_ACK), 0x1);
        while(((HW_RD_REG32((CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_REQ))) & 0x80) == 0x80);
        /*clear the ack bit */
        HW_WR_REG32((CSL_WKUP_CTRL_MMR0_CFG0_BASE + DDR_FSP_CLKCHNG_ACK), 0x0);
    }
}

static int32_t DDR_setClock(DDR_Params *prms)
{
    int32_t status = SystemP_SUCCESS;

    if((HW_RD_REG32(DDR_CTL_REG_BASE) & DDR_TYPE_MASK) == DDR4_MEMORY)
    {
        /* Type is DDR4*/
        DDR_setFreq(prms->clk1Freq);
    }
    else
    {
        /* Type is LPDDR4. Start Frequency handshake.*/
        DDR_setFreq(25000000);

        /*trigger the start bit (from PI)*/
        HW_WR_REG32(DDR_CTL_REG_BASE + DDR_PI_REG_BLOCK_OFFS + DDR_PI_0_SFR_OFFS,   TRIGGER_START_BIT);

        ClockP_usleep(500);

        /*trigger the start bit (from CTL)*/
        HW_WR_REG32(DDR_CTL_REG_BASE + DDR_CTL_0_SFR_OFFS,   TRIGGER_START_BIT);

        DDR_changeFreqAck(prms);

        ClockP_usleep(500);

        /*PI INT S`TATUS*/
        while(((HW_RD_REG32(DDR_CTL_REG_BASE + DDR_PI_REG_BLOCK_OFFS + DDR_PI_87_SFR_OFFS)) & 0x1) != 0x1);
        /*CTL_342[25] = int status init[1] = 1 - The MC initialization has been completed.*/
        while((HW_RD_REG32(DDR_CTL_REG_BASE + DDR_CTL_350_SFR_OFFS)&0x02000000)!= 0x02000000);
    }

    return status;
}

static int32_t DDR_probe(void)
{
    uint32_t status = 0U;
    uint16_t configsize = 0U;
    int32_t ret = SystemP_SUCCESS;

    status = LPDDR4_Probe(&gLpddrCfg, &configsize);
    if ((status != 0) || (configsize != sizeof(LPDDR4_PrivateData)) ||
        (configsize > DDR_SRAM_MAX))
    {
        DebugP_logError("DDR4/LPDDR4_Probe failed !!!\n");
        ret = SystemP_FAILURE;
    }

    return ret;
}

static int32_t DDR_initDrv(void)
{
    uint32_t status = 0U;
    int32_t ret = SystemP_SUCCESS;

    if ((sizeof(gLpddrPd) != sizeof(LPDDR4_PrivateData)) ||
        (sizeof(gLpddrPd) > DDR_SRAM_MAX))
    {
        DebugP_logError("Invalid parameters !!!\n");
        ret = SystemP_FAILURE;
    }

    if(ret == SystemP_SUCCESS)
    {
        gLpddrCfg.ctlBase = (struct LPDDR4_CtlRegs_s *)DDR_CTL_CFG_BASE;
        gLpddrCfg.infoHandler = NULL;

        status = LPDDR4_Init(&gLpddrPd, &gLpddrCfg);
        if ((status > 0U) ||
            (gLpddrPd.ctlBase != (struct LPDDR4_CtlRegs_s *)gLpddrCfg.ctlBase) ||
            (gLpddrPd.ctlInterruptHandler != gLpddrCfg.ctlInterruptHandler) ||
            (gLpddrPd.phyIndepInterruptHandler != gLpddrCfg.phyIndepInterruptHandler))
        {
            DebugP_logError("DDR4/LPDDR4_Init failed !!!\n");
            ret = SystemP_FAILURE;
        }
    }

    return ret;
}

static int32_t DDR_initHwRegs(DDR_Params *prms)
{
    uint32_t status = 0U;
    int32_t ret = SystemP_SUCCESS;

    status = LPDDR4_WriteCtlConfig(&gLpddrPd,
                                    prms->ddrssCtlReg,
                                    prms->ddrssCtlRegNum,
                                    prms->ddrssCtlRegCount);
    if (status == SystemP_SUCCESS)
    {
        status = LPDDR4_WritePhyIndepConfig(&gLpddrPd,
                                            prms->ddrssPhyIndepReg,
                                            prms->ddrssPhyIndepRegNum,
                                            prms->ddrssPhyIndepRegCount);
    }
    if (status == SystemP_SUCCESS)
    {
        status = LPDDR4_WritePhyConfig(&gLpddrPd,
                                        prms->ddrssPhyReg,
                                        prms->ddrssPhyRegNum,
                                        prms->ddrssPhyRegCount);
    }

    if (status != SystemP_SUCCESS)
    {
        DebugP_logError("DDR config write failed !!!\r\n");
        ret = SystemP_FAILURE;
    }
    return ret;
}

static int32_t DDR_start(void)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t offset = 0U;
    int32_t ret = SystemP_SUCCESS;

    offset = DDR_CTL_REG_OFFSET;

    status = LPDDR4_ReadReg(&gLpddrPd, LPDDR4_CTL_REGS, offset, &regval);

    if((HW_RD_REG32(DDR_CTL_REG_BASE) & DDR_TYPE_MASK) == DDR4_MEMORY)
    {
        /* DDR4 memory */
        if ((status > 0U) || ((regval & 0x1U) != 0U))
        {
            DebugP_logError("DDR4_ReadReg failed !!!\r\n");
            ret = SystemP_FAILURE;
        }
    }
    else
    {
        /* LPDDR4 memory */
        if ((status > 0U) || ((regval & 0x1U) != 1U))
        {
            DebugP_logError("LPDDR4_ReadReg failed !!!\r\n");
            ret = SystemP_FAILURE;
        }
    }

    if(ret == SystemP_SUCCESS)
    {
        status = LPDDR4_Start(&gLpddrPd);
        if (status > 0U)
        {
            DebugP_logError("DDR4/LPDDR4_Start failed !!!\r\n");
            ret = SystemP_FAILURE;
        }

        if(ret == SystemP_SUCCESS)
        {
            status = LPDDR4_ReadReg(&gLpddrPd, LPDDR4_CTL_REGS, offset, &regval);
            if ((status > 0U) || ((regval & 0x1U) != 1U))
            {
                DebugP_logError("DDR4/LPDDR4_ReadReg failed !!!\r\n");
                ret = SystemP_FAILURE;
            }
        }
    }

    return ret;
}

static uint32_t DDR_isEnabled (DDR_Params *prm)
{
    uint32_t isEnabled = 0;
    struct LPDDR4_CtlRegs_s * ctlRegBase = (struct LPDDR4_CtlRegs_s *)gLpddrCfg.ctlBase;

    if ((HW_RD_REG32(&(ctlRegBase->LPDDR4__PI_START__REG)) & 0x1) &&
            (HW_RD_REG32(&(ctlRegBase->LPDDR4__START__REG)) & 0x1))
    {
        isEnabled = 1;
    }

    return isEnabled;
}

static void DDR_isr(void *arg)
{
    bool irqStatus;
    int32_t status;
    static uint8_t isrCnt = 0;
    uint32_t regVal = 0U;
    CSL_emif_sscfgRegs *pEmifSsRegs;

    status = LPDDR4_CheckCtlInterrupt(&gLpddrPd, LPDDR4_INTR_BIST_DONE,
						     &irqStatus);
    if ((status == 0U) && irqStatus)
    {
        /* Clear LPDDR4_INTR_BIST_DONE */
        status = LPDDR4_AckCtlInterrupt(&gLpddrPd, LPDDR4_INTR_BIST_DONE);
        if (status == 0U)
        {
            isrCnt++;
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        /* Before continuing we have to stop BIST - BIST_GO = 0 */
        LPDDR4_WriteReg(&gLpddrPd, LPDDR4_CTL_REGS, DDR_BIST_GO_REG/sizeof(uint32_t), 0);

        switch (isrCnt)
        {
            case 1:
                if(gDDRECCRegion[1].startAddr != 0xFFFFFFFFFFFFFFFF && gDDRECCRegion[1].endAddr != 0xFFFFFFFFFFFFFFFF)
                {
                    DDR_primeMem(gDDRECCRegion[1].startAddr, gDDRECCRegion[1].endAddr, gDDRECCRegion[1].pattern);
                    break;
                }

            case 2:
                if(gDDRECCRegion[2].startAddr != 0xFFFFFFFFFFFFFFFF && gDDRECCRegion[2].endAddr != 0xFFFFFFFFFFFFFFFF)
                {
                    DDR_primeMem(gDDRECCRegion[2].startAddr, gDDRECCRegion[2].endAddr, gDDRECCRegion[2].pattern);
                    break;
                }

            default:
                pEmifSsRegs = (CSL_emif_sscfgRegs *)AddrTranslateP_getLocalAddr(DDR_SS_CFG_BASE);

                if (status == SystemP_SUCCESS)
                {
                    CSL_REG32_WR( &pEmifSsRegs->ECC_1B_ERR_CNT_REG, 1u );

                    status = CSL_emifClearECCInterruptStatus((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                                            CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                                            | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK
                                                            | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC2BERR_EN_MASK);

                    if (status == SystemP_SUCCESS)
                    {
                        status = CSL_emifEnableECCInterrupts((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                                            CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                                            | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK
                                                            | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC2BERR_EN_MASK);
                    }
                }

                regVal = pEmifSsRegs->ECC_CTRL_REG;
                regVal |= CSL_FMK(EMIF_SSCFG_ECC_CTRL_REG_ECC_CK, 1U);
                CSL_REG32_WR( &pEmifSsRegs->ECC_CTRL_REG, regVal );

                gDDRInitDoneFlag = 1U;

                break;
        }
    }
}

static uint32_t DDR_utilLog2(uint64_t num)
{
    uint32_t i=0, k;

    if(num != 0)
    {
        for(i = 63; i >= 0; i--)
        {
            k = (num >> i) & 0x01;
            if(k == 1)
            {
                break;
            }
        }
    }

    return i;
}

static int32_t DDR_primeMem(uint64_t start, uint64_t end, uint64_t pattern)
{
    uint64_t size = end - start + 1;
    uint64_t bistStart;
    uint32_t regVal;
    uint32_t tmp;
    uint32_t i = 0;

    /* When inline ECC is enabled, from system point of view the 8/9th of the SDRAM
     * data space are seen as consecutive byte addresses. But BIST engine data space
     * view is not consecutive, it is with data and inline ECC values together. i.e
     * 512-byte data block and it's 64-byte ECC. BIST view for a given address will
     * be 1/9th lesser.
     *      BIST VIEW = BIST START ADDRESS - (BIST START ADDRESS / 9);       --> (1)
     *
     * Change the start address to match the BIST engine view with the actual system
     * point of view. The start address given to the bist engine should be in such
     * a way that BIST VIEW matches with given start address.
     * i.e,           BIST VIEW = START ADDRESS;
     * Using (1) =>   BIST START ADDRESS - (BIST START ADDRESS / 9) = START ADDRESS;
     *                BIST START ADDRESS = (START ADDRESS * 9) / 8;           --> (2)
     *
     * For example, let START ADDRESS = 0x20000
     * Using (2) =>     BIST START ADDRESS = 0x24000
     * Using (1) =>     BIST VIEW = 0x20000 which is equal to the START ADDRESS.
     */
    bistStart = (start * 9U) / 8U;

    /* Set BIST_START_ADDR_0 [31:0] */
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_START_ADDRESS_0_REG), bistStart & DDR_BIST_START_ADDR_0_MASK);

    /* Set BIST_START_ADDR_0 [32] */
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_START_ADDRESS_1_REG), (bistStart >> 32) & DDR_BIST_START_ADDR_1_MASK);

    tmp = (uint32_t)DDR_utilLog2(size);
    regVal = CSL_FMK(DDR_ADDRESS_SPACE, tmp);
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_ADDRESS_SPACE_REG), regVal);

    /* Enable BIST data check bit */
    regVal = CSL_REG32_RD(DDR_GET_CFG_REG_ADDR(DDR_BIST_DATA_CHECK_REG));
    regVal |= CSL_FMK(BIST_DATA_CHECK_REG, regVal);
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_DATA_CHECK_REG), regVal);
    /* Clear the address check bit */
    regVal = CSL_REG32_RD(DDR_GET_CFG_REG_ADDR(DDR_BIST_ADDRESS_CHECK_REG));
    regVal &= ~CSL_FMK(BIST_ADDRESS_CHECK_REG, regVal);
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_ADDRESS_CHECK_REG), regVal);

    regVal = BIST_MODE_MEM_INIT;
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_TEST_MODE_REG), regVal);

    regVal = pattern & (DDR_BIST_DATA_PATTERN0_MASK);
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_DATA_PATTERN_0_REG), regVal);

    regVal = (pattern >> 32) & (DDR_BIST_DATA_PATTERN1_MASK);
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_DATA_PATTERN_1_REG), regVal);

    while (i < BIST_GO_START_TIMEOUT)
    {
        i++;
    }

    regVal = CSL_REG32_RD(DDR_GET_CFG_REG_ADDR(DDR_BIST_GO_REG));
    regVal |= DDR_BIST_GO_MASK;
    CSL_REG32_WR(DDR_GET_CFG_REG_ADDR(DDR_BIST_GO_REG), regVal);

    return SystemP_SUCCESS;
}

static int32_t DDR_inlineECCCfg (DDR_Params *prm)
{
    int32_t status = SystemP_SUCCESS;

    if (prm->eccRegion != NULL)
    {
        CSL_EmifConfig emifCfg;
        memset(&emifCfg, 0, sizeof(emifCfg));

        emifCfg.bEnableMemoryECC = TRUE;
        emifCfg.bReadModifyWriteEnable = TRUE;
        emifCfg.bECCCheck = FALSE;
        emifCfg.bWriteAlloc = TRUE;
        emifCfg.ECCThreshold = 1U;

        emifCfg.pMemEccCfg.startAddr[0] = prm->eccRegion->ddrEccStart0;
        emifCfg.pMemEccCfg.endAddr[0] = prm->eccRegion->ddrEccPrimeEnd0;
        emifCfg.pMemEccCfg.startAddr[1] = prm->eccRegion->ddrEccStart1;
        emifCfg.pMemEccCfg.endAddr[1] = prm->eccRegion->ddrEccPrimeEnd1;
        emifCfg.pMemEccCfg.startAddr[2] = prm->eccRegion->ddrEccStart2;
        emifCfg.pMemEccCfg.endAddr[2] = prm->eccRegion->ddrEccPrimeEnd2;

        status = CSL_emifConfig((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                            &emifCfg);

        if (status == SystemP_SUCCESS)
        {
            if(prm->eccRegion->ddrEccStart0 != DDR_ECC_REGION_START_RESET_VAL &&
                                                    prm->eccRegion->ddrEccEnd0)
            {
                gDDRECCRegion[0].startAddr = prm->eccRegion->ddrEccStart0;
                gDDRECCRegion[0].endAddr = prm->eccRegion->ddrEccEnd0;
                gDDRECCRegion[0].pattern = 0x0;
            }
            if(prm->eccRegion->ddrEccStart1 != DDR_ECC_REGION_START_RESET_VAL &&
                                                    prm->eccRegion->ddrEccEnd1)
            {
                gDDRECCRegion[1].startAddr = prm->eccRegion->ddrEccStart1;
                gDDRECCRegion[1].endAddr = prm->eccRegion->ddrEccEnd1;
                gDDRECCRegion[1].pattern = 0x0;
            }
            if(prm->eccRegion->ddrEccStart2 != DDR_ECC_REGION_START_RESET_VAL &&
                                                    prm->eccRegion->ddrEccEnd2)
            {
                gDDRECCRegion[2].startAddr = prm->eccRegion->ddrEccStart2;
                gDDRECCRegion[2].endAddr = prm->eccRegion->ddrEccEnd2;
                gDDRECCRegion[2].pattern = 0x0;
            }

            HwiP_Params hwiParams;
            HwiP_Object hwiObj;
            HwiP_Params_init(&hwiParams);
            hwiParams.intNum = DDR_IRQ_NUM;
            hwiParams.eventId = HWIP_INVALID_EVENT_ID;
            hwiParams.callback = DDR_isr;
            HwiP_construct(&hwiObj, &hwiParams);

            /* Start DDR primeing */
            if(gDDRECCRegion[0].startAddr != 0xFFFFFFFFFFFFFFFF && gDDRECCRegion[0].endAddr != 0xFFFFFFFFFFFFFFFF)
            {
                DDR_primeMem(gDDRECCRegion[0].startAddr, gDDRECCRegion[0].endAddr, gDDRECCRegion[0].pattern);
            }
            else if(gDDRECCRegion[1].startAddr != 0xFFFFFFFFFFFFFFFF && gDDRECCRegion[1].endAddr != 0xFFFFFFFFFFFFFFFF)
            {
                DDR_primeMem(gDDRECCRegion[1].startAddr, gDDRECCRegion[1].endAddr, gDDRECCRegion[1].pattern);
            }
            else if(gDDRECCRegion[2].startAddr != 0xFFFFFFFFFFFFFFFF && gDDRECCRegion[2].endAddr != 0xFFFFFFFFFFFFFFFF)
            {
                DDR_primeMem(gDDRECCRegion[2].startAddr, gDDRECCRegion[2].endAddr, gDDRECCRegion[2].pattern);
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

uint8_t DDR_isInitDone(void)
{
    return gDDRInitDoneFlag;
}

int32_t DDR_init(DDR_Params *prm)
{
    uint32_t isEnabled = 0;
    int32_t status = SystemP_SUCCESS;

    DDR_socEnableVttRegulator();
    DDR_ResetDDR_PLL();


    /* power and clock to DDR and EMIF is done form outside using SysConfig */

    /* Configure MSMC2DDR Bridge Control register. Configure REGION_IDX, SDRAM_IDX and SDRAM_3QT.*/
    CSL_emif_sscfgRegs *pEmifSsRegs = (CSL_emif_sscfgRegs *)AddrTranslateP_getLocalAddr(DDR_SS_CFG_BASE);
    CSL_REG32_FINS(&pEmifSsRegs->V2A_CTL_REG, EMIF_SSCFG_V2A_CTL_REG_SDRAM_IDX, prm->sdramIdx);

    /* Configure DDRSS_ECC_CTRL_REG register. Disable ECC. */
    HW_WR_REG32((DDR_SS_CFG_BASE + 0x120), 0x00);
    status = DDR_probe();
    if(status == SystemP_SUCCESS)
    {
        status = DDR_initDrv();
    }

    isEnabled = DDR_isEnabled(prm);

    if (!isEnabled)
    {
        if(status == SystemP_SUCCESS)
        {
            status = DDR_initHwRegs(prm);
        }
        if(status == SystemP_SUCCESS)
        {
            status = DDR_setClock(prm);
        }
        if(status == SystemP_SUCCESS)
        {
            status = DDR_start();
        }
    }

    if (status == SystemP_SUCCESS)
    {
        if (prm->enableEccFlag)
        {
            status = DDR_inlineECCCfg (prm);
        }
        else
        {
            gDDRInitDoneFlag = 1U;
        }
    }

    return status;
}


void DDR_Params_init(DDR_Params *prms)
{
    memset((void*)prms, 0, sizeof(DDR_Params));
}
#endif

void DDR_enableInlineECC (uint8_t enableFlag)
{
    if (1U == enableFlag)
    {
        CSL_emifEnableECC ((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE);
    }
    else
    {
        /* Disable inline ECC */
        CSL_emifDisableECC ((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE);
    }
}

int32_t DDR_clearECCError (uint8_t errorType)
{
    int32_t status = SystemP_SUCCESS;

    if (DDR_ECC_1B_ERROR == errorType)
    {
        /* Clear Specific ECC error */
        status = CSL_emifClearECCError((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                           CSL_EMIF_ECC_ERROR_TYPE_SINGLE_BIT);

        if (status == SystemP_SUCCESS)
        {
            /* Clear ECC interrupt bits */
            status = CSL_emifClearECCInterruptStatus((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                                CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK);
        }
    }
    else if (DDR_ECC_2B_ERROR == errorType)
    {
        /* Clear specific error */
        status = CSL_emifClearECCError((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                           CSL_EMIF_ECC_ERROR_TYPE_DOUBLE_BIT);

        if (status == SystemP_SUCCESS)
        {
            /* Clear ECC interrupt bits */
            status = CSL_emifClearECCInterruptStatus((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                                     CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC2BERR_EN_MASK);
        }
    }
    else
    {
        /* Clear all errors */
        status = CSL_emifClearAllECCErrors ((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE);

        if (status == SystemP_SUCCESS)
        {
            status = CSL_emifClearECCInterruptStatus((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE,
                                                CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC1BERR_EN_MASK
                                                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECCM1BERR_EN_MASK
                                                | CSL_EMIF_SSCFG_V2A_INT_SET_REG_ECC2BERR_EN_MASK);
        }
    }

    return status;
}

int32_t DDR_getECCErrorInfo (DDR_ECCErrorInfo *ECCErrorInfo)
{
    int32_t status = SystemP_SUCCESS;
    CSL_ECCErrorInfo csl_ECCErrorInfo = {0};

    if (ECCErrorInfo != NULL)
    {
        status = CSL_emifGetECCErrorInfo ((CSL_emif_sscfgRegs *)DDR_SS_CFG_BASE, &csl_ECCErrorInfo);

        memcpy ((void *)ECCErrorInfo, (void *)&csl_ECCErrorInfo, sizeof(csl_ECCErrorInfo));
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

void DDR_qosSetup(DDR_QosInfo *qosData, uint32_t qosCount)
{
	uint32_t i;

	for(i = 0U; i < qosCount; i++)
    {
		CSL_REG32_WR(qosData[i].reg, qosData[i].val);
    }

    return;
}
