let common = system.getScript("/common");

let mcspi_input_clk_freq = 50000000;

const mcspi_config_a53 = [
    {
        name            : "SPI0",
        baseAddr        : "CSL_MCSPI0_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 112,
        clockIds        : [ "AM62LX_DEV_MCSPI0" ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_RX",
            },
        ],
    },
    {
        name            : "SPI1",
        baseAddr        : "CSL_MCSPI1_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 113,
        clockIds        : [ "AM62LX_DEV_MCSPI1" ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_RX",
            },
        ],
    },
    {
        name            : "SPI2",
        baseAddr        : "CSL_MCSPI2_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 114,
        clockIds        : [ "AM62LX_DEV_MCSPI0" ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_RX",
            },
        ],
    },
    {
        name            : "SPI3",
        baseAddr        : "CSL_MCSPI3_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 115,
        clockIds        : [ "AM62LX_DEV_MCSPI3" ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH0_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH1_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH2_RX",
            },
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI3_CH3_RX",
            },
        ],
    },
];

function getMaxChannels(inst) {
    return 4;   /* max number of channels per MCSPI */
}

function getConfigArr() {
    let mcspi_config;

    if(common.getSelfSysCfgCoreName().includes("a53")) {
        mcspi_config = mcspi_config_a53;
    }

    return mcspi_config;
}

function isFrequencyDefined()
{
    return false;
}

exports = {
    getConfigArr,
    getMaxChannels,
    isFrequencyDefined,
};