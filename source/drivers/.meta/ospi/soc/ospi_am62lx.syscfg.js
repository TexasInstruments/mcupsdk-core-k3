let common = system.getScript("/common");

let ospi_input_clk_freq = 166666666;

const ospi_config_a53ss = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 4,
        intrNum             : 272,
        phaseDelayElement   : 3,
        clockIds            : [ "AM62LX_DEV_FSS0"],
        clockFrequencies    : [
            {
                moduleId: "AM62LX_DEV_FSS0",
                clkId   : "AM62LX_DEV_FSS0_OSPI0_RCLK_CLK",
                clkRate : ospi_input_clk_freq,
            },
        ],
    },
];

const ospi_dma_restrict_regions = [

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
        dllLockMode             : "HALF_CYCLE_LOCK",
        rdDelayMin              : 0,
        rdDelayMax              : 3,
        txDllLowWindowStart     : 0,
        txDllLowWindowEnd       : 0,
        txDllHighWindowStart    : 0,
        txDllHighWindowEnd      : 127,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 0,
        rxHighSearchStart       : 0,
        rxHighSearchEnd         : 127,
        txLowSearchStart        : 0,
        txLowSearchEnd          : 0,
        txHighSearchStart       : 0,
        txHighSearchEnd         : 0,
        txDLLSearchOffset       : 0,
        rxTxDLLSearchStep       : 4,
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
        dllLockMode             : "HALF_CYCLE_LOCK",
        rdDelayMin              : 0,
        rdDelayMax              : 1,
        txDllLowWindowStart     : 0,
        txDllLowWindowEnd       : 0,
        txDllHighWindowStart    : 0,
        txDllHighWindowEnd      : 127,
        rxLowSearchStart        : 0,
        rxLowSearchEnd          : 0,
        rxHighSearchStart       : 0,
        rxHighSearchEnd         : 127,
        txLowSearchStart        : 0,
        txLowSearchEnd          : 0,
        txHighSearchStart       : 0,
        txHighSearchEnd         : 0,
        txDLLSearchOffset       : 0,
        rxTxDLLSearchStep       : 8,
    }
];

function getDefaultConfig()
{

    if(common.getSelfSysCfgCoreName().match(/a53*/))
    {
        return ospi_config_a53ss[0];
    }

}

function getConfigArr() {
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

