
let auxClkMuxLongDescription = `
Aux clock source of McASP can be choosen here
Note: The frequency expected for internal clocks and
frequency supplied by external clocks needs to be specified at the Global Configuration of MCASP

![](../source/drivers/.meta/mcasp/v1/mcasp_clocking/soc/mcasp_clocking_am62ax.png)
`

let mcasp_auxclk_gf_sel = {
    type:"clk_source_mux",
    name: "mcasp_auxclk_gf_sel",
    displayName: "MCASP AUXCLK SEL",
    tisciDevice: "TISCI_DEV_MCASP<n>",
    tisciClock: "TISCI_DEV_MCASP<n>_AUX_CLK",
    longDescription: auxClkMuxLongDescription,
    muxOptions:[
        { name: 1, displayName: "PLL1 HSDIV6 CLKOUT",
            tisciOption: "TISCI_DEV_MCASP<n>_AUX_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK",
            isConfigurable: true,
            defaultFreq: 48000000,
        },
        { name: 0, displayName: "PLL2 HSDIV8 CLKOUT",
            tisciOption: "TISCI_DEV_MCASP<n>_AUX_CLK_PARENT_POSTDIV4_16FF_MAIN_2_HSDIVOUT8_CLK",
            isConfigurable: true,
            defaultFreq: 50000000,
        }
    ]
};

exports = {
    mcasp_auxclk_gf_sel,
};
