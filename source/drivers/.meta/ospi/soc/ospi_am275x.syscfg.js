let common = system.getScript("/common");

let ospi_input_clk_freq = 166666666;

const ospi_config_r5fss = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        intrNum             : 178,
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS0"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS0",
                clkId   : "TISCI_DEV_FSS0_OSPI0_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
    {
        name                : "OSPI1",
        baseAddr            : "CSL_FSS1_OSPI1_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS1_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        intrNum             : 0, //interrupt is not routed
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS1", "TISCI_DEV_FSS1_FSAS_0", "TISCI_DEV_FSS1_OSPI_1" ],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS0_OSPI_1",
                clkId   : "TISCI_DEV_FSS0_OSPI_1_OSPI_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
];

const ospi_config_c7x = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        eventId             : 146 + 256,
        intrNum             : 13,
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS1", "TISCI_DEV_FSS1_FSAS_0", "TISCI_DEV_FSS1_OSPI_0" ],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS1_OSPI_0",
                clkId   : "TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
    {
        name                : "OSPI1",
        baseAddr            : "CSL_FSS1_OSPI1_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS1_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 7,
        eventId             : 0 + 256, //interrupt is not routed
        intrNum             : 0,      //interrupt is not routed
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS1", "TISCI_DEV_FSS1_FSAS_0", "TISCI_DEV_FSS1_OSPI_1" ],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS0_OSPI_1",
                clkId   : "TISCI_DEV_FSS0_OSPI_1_OSPI_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
];

const ospi_dma_restrict_regions = [
    { start : "CSL_R5FSS0_CORE0_ATCM_BASE", size : "CSL_R5FSS0_CORE0_ATCM_SIZE" },
    { start : "CSL_R5FSS0_CORE0_BTCM_BASE", size : "CSL_R5FSS0_CORE0_BTCM_SIZE" },
    { start : "CSL_R5FSS0_CORE1_ATCM_BASE", size : "CSL_R5FSS0_CORE1_ATCM_SIZE" },
    { start : "CSL_R5FSS0_CORE1_BTCM_BASE", size : "CSL_R5FSS0_CORE1_BTCM_SIZE" },
    { start : "CSL_R5FSS1_CORE0_ATCM_BASE", size : "CSL_R5FSS1_CORE0_ATCM_SIZE" },
    { start : "CSL_R5FSS1_CORE0_BTCM_BASE", size : "CSL_R5FSS1_CORE0_BTCM_SIZE" },
    { start : "CSL_R5FSS1_CORE1_ATCM_BASE", size : "CSL_R5FSS1_CORE1_ATCM_SIZE" },
    { start : "CSL_R5FSS1_CORE1_BTCM_BASE", size : "CSL_R5FSS1_CORE1_BTCM_SIZE" },
    { start : "CSL_WKUP_R5FSS0_CORE0_ATCM_BASE", size : "CSL_WKUP_R5FSS0_CORE0_ATCM_SIZE" },
    { start : "CSL_WKUP_R5FSS0_CORE0_BTCM_BASE", size : "CSL_WKUP_R5FSS0_CORE0_BTCM_SIZE" },
];

const ospi_phyTuning_ddr_config =
[
    {
        phyControlMode          : "PHY_MASTER_MODE",
        dllLockMode             : "HALF_CYCLE_LOCK",
        radius                  : 5,
        rxTxDllMin              : 0,
        rxTxDllMax              : 127,
        minReadDelay            : 0,
        maxReadDelay            : 4,
        minPassSize             : 100,
        diagonalShift           : 10,
        maxDiagonalShift        : 70,
        numConsecutiveFail      : 5,
        numConsecutivePass      : 10,
        rdDelaySearchStep       : 16,
    }
];

const ospi_phyTuning_sdr_config =
[
    {
        phyControlMode          : "PHY_MASTER_MODE",
        dllLockMode             : "FULL_CYCLE_LOCK",
        rdDelayMin              : 0,
        rdDelayMax              : 3,
        txDllLowWindowStart     : 18,
        txDllLowWindowEnd       : 24,
        txDllHighWindowStart    : 38,
        txDllHighWindowEnd      : 48,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 15,
        rxHighSearchStart       : 25,
        rxHighSearchEnd         : 63,
        txLowSearchStart        : 0,
        txLowSearchEnd          : 32,
        txHighSearchStart       : 48,
        txHighSearchEnd         : 63,
        txDLLSearchOffset       : 1,
        rxTxDLLSearchStep       : 1,
    }
];

const ospi_fast_phyTuning_ddr_config =
[
    {
        phyControlMode          : "PHY_MASTER_MODE",
        dllLockMode             : "HALF_CYCLE_LOCK",
        radius                  : 5,
        rxTxDllMin              : 0,
        rxTxDllMax              : 127,
        minReadDelay            : 0,
        maxReadDelay            : 4,
        minPassSize             : 100,
        diagonalShift           : 10,
        maxDiagonalShift        : 70,
        numConsecutiveFail      : 5,
        numConsecutivePass      : 10,
        rdDelaySearchStep       : 16,
    }
];

const ospi_fast_phyTuning_sdr_config =
[
    {
        phyControlMode          : "PHY_MASTER_MODE",
        dllLockMode             : "FULL_CYCLE_LOCK",
        rdDelayMin              : 0,
        rdDelayMax              : 2,
        txDllLowWindowStart     : 18,
        txDllLowWindowEnd       : 24,
        txDllHighWindowStart    : 38,
        txDllHighWindowEnd      : 48,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 15,
        rxHighSearchStart       : 25,
        rxHighSearchEnd         : 63,
        txLowSearchStart        : 0,
        txLowSearchEnd          : 32,
        txHighSearchStart       : 48,
        txHighSearchEnd         : 63,
        txDLLSearchOffset       : 4,
        rxTxDLLSearchStep       : 4,
    }
];

function getDefaultConfig()
{
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
            return ospi_config_r5fss[0];
    }
    else if(common.getSelfSysCfgCoreName().match(/c7x*/))
    {
            return ospi_config_c7x[0];
    }
}

function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let ospi_config;
    if(cpu.includes("r5f"))
    {
        ospi_config = ospi_config_r5fss;
    }
    else if (cpu.match(/c75*/))
    {
        ospi_config = ospi_config_c7x;
    }

    return ospi_config;
}

function getDmaRestrictedRegions() {

    return ospi_dma_restrict_regions;
}

function getSupportedDataLines() {
    return 8;
}

function getPhyTuningParamsDDR() {

    return ospi_phyTuning_ddr_config[0];
}

function getPhyTuningParamsSDR() {
    return ospi_phyTuning_sdr_config[0];
}

function getFastPhyTuningParamsDDR() {
    return ospi_fast_phyTuning_ddr_config[0];
}

function getFastPhyTuningParamsSDR() {
    return ospi_fast_phyTuning_sdr_config[0];
}

function getDefaultPhyControlMode()
{
    return ospi_phyTuning_ddr_config[0];
}

function getDefaultDllLockMode()
{
    return ospi_phyTuning_ddr_config[0];
}

exports = {
    getDefaultConfig,
    getConfigArr,
    getDmaRestrictedRegions,
    getSupportedDataLines,
    getPhyTuningParamsDDR,
    getPhyTuningParamsSDR,
    getFastPhyTuningParamsDDR,
    getFastPhyTuningParamsSDR,
    getDefaultPhyControlMode,
    getDefaultDllLockMode,
};

