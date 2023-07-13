let common = system.getScript("/common");

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

function getConfigArr() {
    return mcasp_config;
}

exports = {
    getConfigArr,
    mcasp_input_clk_freq,
};
