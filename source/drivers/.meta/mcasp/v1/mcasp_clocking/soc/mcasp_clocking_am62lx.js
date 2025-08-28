
let auxClkMuxLongDescription = `
Aux clock source of McASP can be choosen here
Note: The frequency expected for internal clocks and
frequency supplied by external clocks needs to be specified at the Global Configuration of MCASP

![](../source/drivers/.meta/mcasp/v1/mcasp_clocking/soc/mcasp_clocking_am62lx.png)
`

let mcasp_auxclk_gf_sel = {
    type:"clk_source_mux",
    name: "mcasp_auxclk_gf_sel",
    displayName: "MCASP AUXCLK SEL",
    tisciDevice: "AM62LX_DEV_MCASP<n>",
    tisciClock: "AM62LX_DEV_MCASP<n>_AUX_CLK",
    longDescription: auxClkMuxLongDescription,
    muxOptions:[
        { name: 1, displayName: "WKUP PLL0 HSDIV1 CLKOUT",
            tisciOption: "AM62LX_DEV_MCASP0_AUX_CLK_PARENT_HSDIV4_16FFT_WKUP_0_HSDIVOUT1_CLK",
            isConfigurable: true,
            defaultFreq: 48000000,
        },
        { name: 0, displayName: "PLL0 HSDIV8 CLKOUT",
            tisciOption: "AM62LX_DEV_MCASP0_AUX_CLK_PARENT_POSTDIV4_16FF_MAIN_0_HSDIVOUT8_CLK",
            isConfigurable: true,
            defaultFreq: 50000000,
        }
    ]
};

exports = {
    mcasp_auxclk_gf_sel,
};
