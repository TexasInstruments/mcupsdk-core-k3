let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");

let mcasp_input_clk_freq = 48000000;

const mcasp_config = [
    {
        name                        : "MCASP0",
        regBaseAddr                 : "CSL_MCASP0_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP0_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        wkupR5RxIntr                : 98,
        wkupR5TxIntr                : 99,
        c7xRxIntr                   : 53,
        c7xTxIntr                   : 54,
        c7xRxEvent                  : 235,
        c7xTxEvent                  : 236,
        a53RxIntr                   : 267,
        a53TxIntr                   : 268,
        clockIds                    : ["TISCI_DEV_MCASP0"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP0",
                clkId   : "TISCI_DEV_MCASP0_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP0_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP0_RX",
            }
        ],
    },
    {
        name                        : "MCASP1",
        regBaseAddr                 : "CSL_MCASP1_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP1_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        wkupR5RxIntr                : 165,
        wkupR5TxIntr                : 166,
        c7xRxIntr                   : 55,
        c7xTxIntr                   : 56,
        c7xRxEvent                  : 237,
        c7xTxEvent                  : 238,
        a53RxIntr                   : 269,
        a53TxIntr                   : 270,
        clockIds                    : ["TISCI_DEV_MCASP1"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP1",
                clkId   : "TISCI_DEV_MCASP1_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP1_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP1_RX",
            }
        ],
    },
    {
        name                        : "MCASP2",
        regBaseAddr                 : "CSL_MCASP2_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP2_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        wkupR5RxIntr                : 170,
        wkupR5TxIntr                : 209,
        c7xRxIntr                   : 57,
        c7xTxIntr                   : 58,
        c7xRxEvent                  : 239,
        c7xTxEvent                  : 240,
        a53RxIntr                   : 271,
        a53TxIntr                   : 272,
        clockIds                    : ["TISCI_DEV_MCASP2"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP2",
                clkId   : "TISCI_DEV_MCASP2_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP2_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP2_RX",
            }
        ],
    }
];

let mcasp_ext_rxhclk_src = [
    { name: 0, displayName: "EXT_REFCLK1"},
    { name: 1, displayName: "HFOSC0_CLKOUT"},
    { name: 2, displayName: "AUDIO_EXT_REFCLK0"},
    { name: 3, displayName: "AUDIO_EXT_REFCLK1"},
    { name: 16, displayName: "Invalid Clock"},
];

let mcasp_ext_txhclk_src = [
    { name: 0, displayName: "EXT_REFCLK1"},
    { name: 1, displayName: "HFOSC0_CLKOUT"},
    { name: 2, displayName: "AUDIO_EXT_REFCLK0"},
    { name: 3, displayName: "AUDIO_EXT_REFCLK1"},
    { name: 16, displayName: "Invalid Clock"},
];

function getConfigArr() {
    return mcasp_config;
}

let mcas_ext_hclk_src_list = [
    "EXT_REFCLK1", "CLKOUT0", "AUDIO_EXT_REFCLK0", "AUDIO_EXT_REFCLK1"
];

function getExtClkPins() {
    return mcas_ext_hclk_src_list;
}

function getExtRxHclkSrc() {
    return mcasp_ext_rxhclk_src;
}

function getExtTxHclkSrc() {
    return mcasp_ext_txhclk_src;
}

function getPinmuxReq(txHclkSourceMux, rxHclkSourceMux)
{
    let systemResources = [];
    let pinResource = {}

    if(txHclkSourceMux == 0 || rxHclkSourceMux == 0)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "EXT_REFCLK1", "External ref clk 1");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 1 || rxHclkSourceMux == 1)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "CLKOUT0", "High Frequency Oscillator clk out 0");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 2 || rxHclkSourceMux == 2)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "AUDIO_EXT_REFCLK0", "Audio external ref clk 0");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 3 || rxHclkSourceMux == 3)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "AUDIO_EXT_REFCLK1", "Audio external ref clk 1");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }

    return systemResources;
}

exports = {
    getConfigArr,
    mcasp_input_clk_freq,
    getExtRxHclkSrc,
    getExtTxHclkSrc,
    getExtClkPins,
    getPinmuxReq,
};
