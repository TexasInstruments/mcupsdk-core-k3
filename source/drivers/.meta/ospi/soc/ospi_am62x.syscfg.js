let common = system.getScript("/common");

let ospi_input_clk_freq = 166666666;

const ospi_config_r5fss = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        intrNum             : 171,
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS0", "TISCI_DEV_FSS0_FSAS_0", "TISCI_DEV_FSS0_OSPI_0" ],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS0_OSPI_0",
                clkId   : "TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
];

const ospi_config_a53ss = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        intrNum             : 171,
        phaseDelayElement   : 3,
        clockIds            : [ "TISCI_DEV_FSS0", "TISCI_DEV_FSS0_FSAS_0", "TISCI_DEV_FSS0_OSPI_0" ],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS0_OSPI_0",
                clkId   : "TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
];

const ospi_dma_restrict_regions = [
    { start : "CSL_WKUP_R5FSS0_ATCM_BASE", size : "CSL_WKUP_R5FSS0_ATCM_SIZE" },
    { start : "CSL_WKUP_R5FSS0_BTCM_BASE", size : "CSL_WKUP_R5FSS0_BTCM_SIZE" },
    { start : "CSL_MCU_M4FSS0_IRAM_BASE", size : "CSL_MCU_M4FSS0_IRAM_SIZE" },
    { start : "CSL_MCU_M4FSS0_DRAM_BASE", size : "CSL_MCU_M4FSS0_DRAM_SIZE" },
];

const ospi_phyTuning_ddr_config =
[
    {
        phyControlMode          : "PHY_MASTER_MODE",
        dllLockMode             : "HALF_CYCLE_LOCK",
        rdDelayMin              : 1,
        rdDelayMax              : 4,
        txDllLowWindowStart     : 28,
        txDllLowWindowEnd       : 48,
        txDllHighWindowStart    : 60,
        txDllHighWindowEnd      : 96,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 40,
        rxHighSearchStart       : 24,
        rxHighSearchEnd         : 107,
        txLowSearchStart        : 16,
        txLowSearchEnd          : 64,
        txHighSearchStart       : 78,
        txHighSearchEnd         : 127,
        txDLLSearchOffset       : 8,
        rxTxDLLSearchStep       : 4,
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
        rdDelayMin              : 1,
        rdDelayMax              : 2,
        txDllLowWindowStart     : 28,
        txDllLowWindowEnd       : 48,
        txDllHighWindowStart    : 60,
        txDllHighWindowEnd      : 96,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 40,
        rxHighSearchStart       : 24,
        rxHighSearchEnd         : 107,
        txLowSearchStart        : 16,
        txLowSearchEnd          : 64,
        txHighSearchStart       : 78,
        txHighSearchEnd         : 127,
        txDLLSearchOffset       : 8,
        rxTxDLLSearchStep       : 8,
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
    if(common.getSelfSysCfgCoreName().match(/r5f*/))
    {
        return ospi_config_r5fss[0];
    }
    else if(common.getSelfSysCfgCoreName().match(/a53*/))
    {
        return ospi_config_a53ss[0];
    }

}

function getConfigArr() {
    if(common.getSelfSysCfgCoreName().match(/r5f*/))
    {
        return ospi_config_r5fss;
    }
    if(common.getSelfSysCfgCoreName().match(/a53*/))
    {
        return ospi_config_a53ss;
    }

}

function getDmaRestrictedRegions() {

    return ospi_dma_restrict_regions;
}

function getSupportedDataLines() {
    return 8;
}

function getPhyTuningParams(protocol) {

    if(protocol != "8d_8d_8d" && protocol != "4s_4d_4d")
    {
        return ospi_phyTuning_sdr_config[0];
    }
    else
    {
        return ospi_phyTuning_ddr_config[0];
    }
}

function getFastPhyTuningParams(protocol) {

    if(protocol != "8d_8d_8d" && protocol != "4s_4d_4d")
    {
        return ospi_fast_phyTuning_sdr_config[0];
    }
    else
    {
        return ospi_fast_phyTuning_ddr_config[0];
    }
}

exports = {
    getDefaultConfig,
    getConfigArr,
    getDmaRestrictedRegions,
    getSupportedDataLines,
    getPhyTuningParams,
    getFastPhyTuningParams,
};


