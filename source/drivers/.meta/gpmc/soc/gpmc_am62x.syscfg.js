let common = system.getScript("/common");

let gpmc_input_clk_freq = 133333333;

const gpmc_config_r5fss = [
    {
        name            : "GPMC0",
        baseAddr        : "CSL_GPMC0_CFG_BASE",
        dataBaseAddr    : "CSL_GPMC0_DATA_BASE",
        elmBaseAddr     : "CSL_ELM0_BASE",
        inputClkFreq    : gpmc_input_clk_freq,
        clockRateDiv    : 1,
        intrNum         : 103,
        dmaLocalEventID : 26,
        clockIds        : [ "TISCI_DEV_GPMC0", "TISCI_DEV_ELM0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_GPMC0",
                clkId   : "TISCI_DEV_GPMC0_FUNC_CLK",
                clkRate : gpmc_input_clk_freq,
            },
        ],
    },
];

const gpmc_dma_restrict_regions = [
    { start : "CSL_WKUP_R5FSS0_ATCM_BASE", size : "CSL_WKUP_R5FSS0_ATCM_SIZE" },
    { start : "CSL_WKUP_R5FSS0_BTCM_BASE", size : "CSL_WKUP_R5FSS0_BTCM_SIZE" },
    { start : "CSL_MCU_M4FSS0_IRAM_BASE", size : "CSL_MCU_M4FSS0_IRAM_SIZE" },
    { start : "CSL_MCU_M4FSS0_DRAM_BASE", size : "CSL_MCU_M4FSS0_DRAM_SIZE" },
];

const gpmc_config_nandlike_device = {
    waitPinPol         :   "CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL",
    addrDataMux        :   "NONMUX",
    timeLatency        :   "X1",
    timingParams       :
        {
            csOnTime               :   0,
            csRdOffTime            :   4,
            csWrOffTime            :   6,
            advOnTime              :   0,
            advRdOffTime           :   4,
            advWrOffTime           :   4,
            advAadMuxOnTime        :   0,
            advAadMuxRdOffTime     :   0,
            advAadMuxWrOffTime     :   0,
            weOnTtime              :   0,
            weOffTime              :   3,
            oeOnTime               :   1,
            oeOffTime              :   3,
            oeAadMuxOnTime         :   0,
            oeAadMuxOffTime        :   0,
            pageBurstAccess        :   0,
            rdAccessTime           :   4,
            wrAcessTime            :   6,
            rdCycleTime            :   4,
            wrCycleTime            :   5,
            wrDataOnMuxBusTime     :   0,
            cycle2CycleDelay       :   0,
            busTurnAroundTime      :   0,
            cycleDelaySameChipSel  :   "NOC2CDELAY",
            cycleDelayDiffChipSel  :   "NOC2CDELAY",
        },
    eccAlgo            :   "GPMC_NAND_ECC_ALGO_BCH_8BIT",
    readType           :   "CSL_GPMC_CONFIG1_READTYPE_RDASYNC",
    csExDelay          :   "CSL_GPMC_CONFIG2_CSEXTRADELAY_NOTDELAYED",
    accessType         :   "CSL_GPMC_CONFIG1_READMULTIPLE_RDSINGLE",
    optimisedAccess    :   "DISABLED",
    cycleOptimisation  :   0,
}

function getDefaultConfig()
{
    return gpmc_config_r5fss[0];
}

function getConfigArr() {

    return gpmc_config_r5fss;
}

function getDmaRestrictedRegions() {

    return gpmc_dma_restrict_regions;
}

function getNandlikeGpmcConfig ()
{
    return gpmc_config_nandlike_device;
}

exports = {
    getDefaultConfig,
    getConfigArr,
    getNandlikeGpmcConfig,
    getDmaRestrictedRegions,
};


