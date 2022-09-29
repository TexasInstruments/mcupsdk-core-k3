let common = system.getScript("/common");

/*
 * MCU_UART and WKUP_UART are using same PLL.
 * So CLK frequecy should be matching between both.
 * DM firmware is using 48000000 as the frequency for WKUP_UART.
 * Same should be used for MCU_UART.
 */
let uart_input_clk_freq_mcu = 48000000;
let uart_input_clk_freq_main = 48000000;

/* On M4F, interrupt number as specified in TRM is input to the NVIC but from M4 point of view there are 16 internal interrupts
 * and then the NVIC input interrupts start, hence we need to add +16 to the value specified by TRM */
const uart_config_m4f = [
    {
        name            : "MCU_USART0",
        baseAddr        : "CSL_MCU_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_mcu,
        intrNum         : 24 + 16,
        clockIds        : [ "TISCI_DEV_MCU_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_MCU_UART0",
                clkId   : "TISCI_DEV_MCU_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_mcu,
            },
        ],
    },
    {
        name            : "WKUP_USART0",
        baseAddr        : "CSL_WKUP_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_mcu,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_WKUP_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_WKUP_UART0",
                clkId   : "TISCI_DEV_WKUP_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_mcu,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_WKUP0_UART1_TX",
                rxCh    : "UDMA_PDMA_CH_WKUP0_UART1_RX",
            },
        ],
    },
    {
        name            : "USART0",
        baseAddr        : "CSL_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART0",
                clkId   : "TISCI_DEV_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART0_RX",
            },
        ],
    },
    {
        name            : "USART1",
        baseAddr        : "CSL_UART1_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART1",
                clkId   : "TISCI_DEV_UART1_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART1_RX",
            },
        ],
    },
    {
        name            : "USART2",
        baseAddr        : "CSL_UART2_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART2",
                clkId   : "TISCI_DEV_UART2_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART2_RX",
            },
        ],
    },
    {
        name            : "USART3",
        baseAddr        : "CSL_UART3_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART3" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART3",
                clkId   : "TISCI_DEV_UART3_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART3_RX",
            },
        ],
    },
    {
        name            : "USART4",
        baseAddr        : "CSL_UART4_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART4" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART4",
                clkId   : "TISCI_DEV_UART4_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART4_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART4_RX",
            },
        ],
    },
    {
        name            : "USART5",
        baseAddr        : "CSL_UART5_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART5" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART5",
                clkId   : "TISCI_DEV_UART5_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART5_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART5_RX",
            },
        ],
    },
    {
        name            : "USART6",
        baseAddr        : "CSL_UART6_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : -1, // interrupts not supported
        clockIds        : [ "TISCI_DEV_UART6" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART6",
                clkId   : "TISCI_DEV_UART6_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART6_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART6_RX",
            },
        ],
    },
];

const uart_config_r5f = [
    {
        name            : "WKUP_USART0",
        baseAddr        : "CSL_WKUP_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 219,
        clockIds        : [ "TISCI_DEV_WKUP_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_WKUP_UART0",
                clkId   : "TISCI_DEV_WKUP_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_WKUP0_UART1_TX",
                rxCh    : "UDMA_PDMA_CH_WKUP0_UART1_RX",
            },
        ],
    },
    {
        name            : "MCU_USART0",
        baseAddr        : "CSL_MCU_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 217,
        clockIds        : [ "TISCI_DEV_MCU_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_MCU_UART0",
                clkId   : "TISCI_DEV_MCU_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
    },
    {
        name            : "USART0",
        baseAddr        : "CSL_UART0_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 210,
        clockIds        : [ "TISCI_DEV_UART0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART0",
                clkId   : "TISCI_DEV_UART0_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART0_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART0_RX",
            },
        ],
    },
    {
        name            : "USART1",
        baseAddr        : "CSL_UART1_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 211,
        clockIds        : [ "TISCI_DEV_UART1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART1",
                clkId   : "TISCI_DEV_UART1_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART1_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART1_RX",
            },
        ],
    },
    {
        name            : "USART2",
        baseAddr        : "CSL_UART2_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 212,
        clockIds        : [ "TISCI_DEV_UART2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART2",
                clkId   : "TISCI_DEV_UART2_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART2_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART2_RX",
            },
        ],
    },
    {
        name            : "USART3",
        baseAddr        : "CSL_UART3_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 213,
        clockIds        : [ "TISCI_DEV_UART3" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART3",
                clkId   : "TISCI_DEV_UART3_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART3_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART3_RX",
            },
        ],
    },
    {
        name            : "USART4",
        baseAddr        : "CSL_UART4_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 214,
        clockIds        : [ "TISCI_DEV_UART4" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART4",
                clkId   : "TISCI_DEV_UART4_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART4_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART4_RX",
            },
        ],
    },
    {
        name            : "USART5",
        baseAddr        : "CSL_UART5_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 215,
        clockIds        : [ "TISCI_DEV_UART5" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART5",
                clkId   : "TISCI_DEV_UART5_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART5_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART5_RX",
            },
        ],
    },
    {
        name            : "USART6",
        baseAddr        : "CSL_UART6_BASE",
        inputClkFreq    : uart_input_clk_freq_main,
        intrNum         : 216,
        clockIds        : [ "TISCI_DEV_UART6" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_UART6",
                clkId   : "TISCI_DEV_UART6_FCLK_CLK",
                clkRate : uart_input_clk_freq_main,
            },
        ],
        udmaPdmaChannels: [
            {
                txCh    : "UDMA_PDMA_CH_MAIN0_UART6_TX",
                rxCh    : "UDMA_PDMA_CH_MAIN0_UART6_RX",
            },
        ],
    },
];

function getConfigArr() {
    let uart_config;

    if(common.getSelfSysCfgCoreName().includes("m4f")) {
        uart_config = uart_config_m4f;
    }
    else if (common.getSelfSysCfgCoreName().includes("r5f")) {
        uart_config = uart_config_r5f;
    }

    return uart_config;
}

function getDefaultClkRate() {
    let uart_input_clk_freq;
    if(common.getSelfSysCfgCoreName().includes("m4f")) {
        uart_input_clk_freq = uart_input_clk_freq_mcu;
    }
    else
    {
        uart_input_clk_freq = uart_input_clk_freq_main;
    }
    return uart_input_clk_freq;
}

function validate(instance, report)
{
    let cpu = common.getSelfSysCfgCoreName();
    /*  Interrupts from main domain is not routed to MCU domain */
    if (cpu.match(/m4f*/) &&
        (instance.intrEnable == "ENABLE" || instance.intrEnable == "USER_INTR") &&
        (instance.useMcuDomainPeripherals == false || (instance.useWakeupDomainPeripherals == true)))
    {
        report.logError("Interrupt mode is not supported for Main domain UARTs on MCU M4", instance, "intrEnable");
    }
}

exports = {
    getConfigArr,
    getDefaultClkRate,
    validate
};
