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

function getMaxChannels(inst) {
    return 4;   /* max number of channels per MCSPI */
}

function getConfigArr() {
    let mcspi_config;

    if(common.getSelfSysCfgCoreName().includes("m4f")) {
        mcspi_config = mcspi_config_m4f;
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
