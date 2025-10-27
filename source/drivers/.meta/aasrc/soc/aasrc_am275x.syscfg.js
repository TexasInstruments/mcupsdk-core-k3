let common = system.getScript("/common");
let module = system.modules['/drivers/aasrc/aasrc'];

let aasrc_input_clk_freq = 200000000;

const aasrc_config = [
];

const aasrc_config_c7x = [
    {
        name                : "AASRC0",
        baseAddr            : "CSL_AASRC0_CFG_BASE",
        streamDataBaseAddr  : "CSL_AASRC0_DATA_R1_BASE",
        groupDataBaseAddr   : "CSL_AASRC0_DATA_R0_BASE",
        clockIds            : ["TISCI_DEV_AASRC0"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_AASRC0 ",
                clkId   : "TISCI_DEV_AASRC0_SYS_CLK",
                clkRate : aasrc_input_clk_freq,
            },
        ],
        intCfg              : [
            {
                intrNum  : 20,
                eventId  : 50,
                intrPriority : 4,
            },
            {
                intrNum  : 22,
                eventId  : 52,
                intrPriority : 4,
            },
            {
                intrNum  : 21,
                eventId  : 51,
                intrPriority : 4,
            },
            {
                intrNum  : 23,
                eventId  : 53,
                intrPriority : 4,
            },
            {
                intrNum  : 24,
                eventId  : 54,
                intrPriority : 4,
            },
        ],
        udmaPdmaChannels            : Array.from({ length: 16 }, (_, i) => ({
            txCh: `UDMA_PDMA_CH_MAIN0_AASRC0_CH${i}_TX`,
            rxCh: `UDMA_PDMA_CH_MAIN0_AASRC0_CH${i}_RX`,
        })),
    },
    {
        name                : "AASRC1",
        baseAddr            : "CSL_AASRC1_CFG_BASE",
        streamDataBaseAddr  : "CSL_AASRC1_DATA_R1_BASE",
        groupDataBaseAddr   : "CSL_AASRC1_DATA_R0_BASE",
        clockIds            : ["TISCI_DEV_AASRC1"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_AASRC1 ",
                clkId   : "TISCI_DEV_AASRC1_SYS_CLK",
                clkRate : aasrc_input_clk_freq,
            },
        ],
        intCfg:             [
            {
                intrNum  : 25,
                eventId  : 55,
                intrPriority : 4,
            },
            {
                intrNum  : 27,
                eventId  : 57,
                intrPriority : 4,
            },
            {
                intrNum  : 26,
                eventId  : 56,
                intrPriority : 4,
            },
            {
                intrNum  : 28,
                eventId  : 58,
                intrPriority : 4,
            },
            {
                intrNum  : 29,
                eventId  : 59,
                intrPriority : 4,
            },
        ],
        udmaPdmaChannels            : Array.from({ length: 16 }, (_, i) => ({
            txCh: `UDMA_PDMA_CH_MAIN0_AASRC1_CH${i}_TX`,
            rxCh: `UDMA_PDMA_CH_MAIN0_AASRC1_CH${i}_RX`,
        })),
    },
];


const aasrc_config_r5fss = [
    {
        name                : "AASRC0",
        baseAddr            : "CSL_AASRC0_CFG_BASE",
        streamDataBaseAddr  : "CSL_AASRC0_DATA_R1_BASE",
        groupDataBaseAddr   : "CSL_AASRC0_DATA_R0_BASE",
        clockIds            : ["TISCI_DEV_AASRC0"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_AASRC0 ",
                clkId   : "TISCI_DEV_AASRC0_SYS_CLK",
                clkRate : aasrc_input_clk_freq,
            },
        ],
        intCfg              : [
            {
                intrNum  : 50,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 52,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 51,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 53,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 54,
                eventId  : 0,
                intrPriority : 4,
            },
        ],
        udmaPdmaChannels            : Array.from({ length: 16 }, (_, i) => ({
            txCh: `UDMA_PDMA_CH_MAIN0_AASRC0_CH${i}_TX`,
            rxCh: `UDMA_PDMA_CH_MAIN0_AASRC0_CH${i}_RX`,
        })),
    },
    {
        name                : "AASRC1",
        baseAddr            : "CSL_AASRC1_CFG_BASE",
        streamDataBaseAddr  : "CSL_AASRC1_DATA_R1_BASE",
        groupDataBaseAddr   : "CSL_AASRC1_DATA_R0_BASE",
        clockIds            : ["TISCI_DEV_AASRC1"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_AASRC1 ",
                clkId   : "TISCI_DEV_AASRC1_SYS_CLK",
                clkRate : aasrc_input_clk_freq,
            },
        ],
        intCfg:             [
            {
                intrNum  : 55,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 57,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 56,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 58,
                eventId  : 0,
                intrPriority : 4,
            },
            {
                intrNum  : 59,
                eventId  : 0,
                intrPriority : 4,
            },
        ],
        udmaPdmaChannels            : Array.from({ length: 16 }, (_, i) => ({
            txCh: `UDMA_PDMA_CH_MAIN0_AASRC1_CH${i}_TX`,
            rxCh: `UDMA_PDMA_CH_MAIN0_AASRC1_CH${i}_RX`,
        })),
    },
];

/* External Clock Source Options for Rx */
const rxExtClkSrcOptions = [
    { name: "McASP0_AFSR" },
    { name: "McASP1_AFSR" },
    { name: "McASP2_AFSR" },
    { name: "McASP3_AFSR" },
    { name: "McASP4_AFSR" },
    { name: "McASP0_AFSX" },
    { name: "McASP1_AFSX" },
    { name: "McASP2_AFSX" },
    { name: "McASP3_AFSX" },
    { name: "McASP4_AFSX" },
    { name: "AUDIO_EXT_REFCLK0_Pin" },
    { name: "AUDIO_EXT_REFCLK1_Pin" },
    { name: "AUDIO_EXT_REFCLK2_Pin" },
    { name: "ADC0_CLK" },
    { name: "MLB_IO_CLK" },
    { name: "MAIN_PLL4_HSDIV3_CLKOUT" },
    { name: "MCU_EXT_REFCLK0_Pin" },
    { name: "EXT_REFCLK1_Pin" },
    { name: "CPSW_CPTS_GENF0" },
    { name: "CPSW_CPTS_GENF1" },
];

/* External Clock Source Options for Tx */
const txExtClkSrcOptions = [
    { name: "McASP0_AFSX" },
    { name: "McASP1_AFSX" },
    { name: "McASP2_AFSX" },
    { name: "McASP3_AFSX" },
    { name: "McASP4_AFSX" },
    { name: "AUDIO_EXT_REFCLK0_Pin" },
    { name: "AUDIO_EXT_REFCLK1_Pin" },
    { name: "AUDIO_EXT_REFCLK2_Pin" },
    { name: "ADC0_CLK" },
    { name: "MLB_IO_CLK" },
    { name: "MAIN_PLL4_HSDIV3_CLKOUT" },
    { name: "MCU_EXT_REFCLK0_Pin" },
    { name: "EXT_REFCLK1_Pin" },
    { name: "CPSW_CPTS_GENF0" },
    { name: "CPSW_CPTS_GENF1" },
];

function getMaxChannels(inst) {
    return 8;   /* max number of channels per AASRC */
}

function getMaxClockzone(inst) {
    return 4;   /* max number of clock zones per AASRC */
}

/* Helper function to get the mapped value */
function getDeEmphasisValue(mode) {

    // Mapping object for deEmphasis modes
    const deEmphasisMapping = {
        "Disabled": 0,
        "Mode 1": 1,
        "Mode 2": 2,
        "Mode 3": 3,
    };
        return deEmphasisMapping[mode] || 0; /* Default to 0 if mode is not found */
    }

function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let aasrc_config;
    if(cpu.match(/r5f*/))
    {
        aasrc_config = aasrc_config_r5fss;
    }
    else if (cpu.match(/c75*/))
    {
        aasrc_config = aasrc_config_c7x;
    }

    return aasrc_config;
}

function getInstanceConfig(instance) {
    let cpu = common.getSelfSysCfgCoreName();
    let aasrc_config;
    if(cpu.match(/r5f*/))
    {
        aasrc_config = aasrc_config_r5fss;
    }
    else if (cpu.match(/c75*/))
    {
        aasrc_config = aasrc_config_c7x;
    }

    /* Get the instance index */
    let instanceIndex = system.modules["/drivers/aasrc/aasrc"].$instances.indexOf(instance);
    let config = aasrc_config[instanceIndex];

    return config;
}

function isFrequencyDefined()
{
    return false;
}

exports = {
    getInstanceConfig,
    getConfigArr,
    getMaxChannels,
    getMaxClockzone,
    isFrequencyDefined,
    getDeEmphasisValue,
    rxExtClkSrcOptions,
    txExtClkSrcOptions,
};
