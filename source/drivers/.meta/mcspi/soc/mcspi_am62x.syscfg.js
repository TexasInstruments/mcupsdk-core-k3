let common = system.getScript("/common");


let mcspi_input_clk_freq = 50000000;

/* On M4F, interrupt number as specified in TRM is input to the NVIC but from M4 point of view there are 16 internal interrupts
 * and then the NVIC input interrupts start, hence we need to add +16 to the value specified by TRM */
const mcspi_config_m4f = [
    {
        name            : "MCU_SPI0",
        baseAddr        : "CSL_MCU_MCSPI0_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 22 + 16,
        clockIds        : [ "TISCI_DEV_MCU_MCSPI0" ],
    },
    {
        name            : "MCU_SPI1",
        baseAddr        : "CSL_MCU_MCSPI1_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 23 + 16,
        clockIds        : [ "TISCI_DEV_MCU_MCSPI1" ],
    },
    {
        name            : "SPI0",
        baseAddr        : "CSL_MCSPI0_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : -1, // Interrupt not supported
        clockIds        : [ "TISCI_DEV_MCSPI0" ],
    },
    {
        name            : "SPI1",
        baseAddr        : "CSL_MCSPI1_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : -1, // Interrupt not supported
        clockIds        : [ "TISCI_DEV_MCSPI1" ],
    },
    {
        name            : "SPI2",
        baseAddr        : "CSL_MCSPI2_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : -1, // Interrupt not supported
        clockIds        : [ "TISCI_DEV_MCSPI2" ],
    },
];

const mcspi_config_r5f = [
    {
        name            : "MCU_SPI0",
        baseAddr        : "CSL_MCU_MCSPI0_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 207,
        clockIds        : [ "TISCI_DEV_MCU_MCSPI0" ],
    },
    {
        name            : "MCU_SPI1",
        baseAddr        : "CSL_MCU_MCSPI1_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 208,
        clockIds        : [ "TISCI_DEV_MCU_MCSPI1" ],
    },
    {
        name            : "SPI0",
        baseAddr        : "CSL_MCSPI0_CFG_BASE",
        inputClkFreq    : mcspi_input_clk_freq,
        intrNum         : 204,
        clockIds        : [ "TISCI_DEV_MCSPI0" ],
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
                rxCh    : "UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_RX",
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
        intrNum         : 205,
        clockIds        : [ "TISCI_DEV_MCSPI1" ],
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
        intrNum         : 206,
        clockIds        : [ "TISCI_DEV_MCSPI2" ],
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
];

function getMaxChannels(inst) {
    return 4;   /* max number of channels per MCSPI */
}

function getConfigArr() {
    let mcspi_config;

    if(common.getSelfSysCfgCoreName().includes("m4f")) {
        mcspi_config = mcspi_config_m4f;
    }

    if(common.getSelfSysCfgCoreName().includes("r5f")) {
        mcspi_config = mcspi_config_r5f;
    }

    return mcspi_config;
}

function isFrequencyDefined()
{
    return false;
}
function validate(instance, report)
{
    let cpu = common.getSelfSysCfgCoreName();
    /*  Interrupts from main domain is not routed to MCU domain */
    if (cpu.match(/m4f*/) &&
        instance.intrEnable == "INTERRUPT" &&
        instance.useMcuDomainPeripherals == false)
    {
        report.logError("Interrupt mode is not supported for Main domain MCSPIs on MCU M4", instance, "intrEnable");
    }
}

exports = {
    getConfigArr,
    getMaxChannels,
    isFrequencyDefined,
    validate,
};
