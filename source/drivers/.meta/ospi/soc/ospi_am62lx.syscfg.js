let common = system.getScript("/common");

let ospi_input_clk_freq = 166666666;

const ospi_config_a53ss = [
    {
        name                : "OSPI0",
        baseAddr            : "CSL_FSS0_OSPI0_CTRL_BASE",
        dataBaseAddr        : "CSL_FSS0_DAT_REG1_BASE",
        inputClkFreq        : ospi_input_clk_freq,
        dacEnable           : false,
        baudRateDiv         : 8,
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
        radius                  : 10,
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
        radius                  : 10,
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

