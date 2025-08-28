let auxClkMuxLongDescription = `
Aux clock source of McASP can be choosen here
Note: The frequency expected for internal clocks and
frequency supplied by external clocks needs to be specified at the Global Configuration of MCASP

![](../source/drivers/.meta/mcasp/v1/mcasp_clocking/soc/mcasp_clocking_am275x.png)
`

let mcasp_auxclk_sel = {
    type: "clk_source_mux",
    name: "aux_clk_sel",
    displayName: "MCASP AUXCLK External Clk Sel",
    tisciDevice: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD",
    tisciClock: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK",
    muxOptions: [
        { name: 0, displayName: "MAIN PLL2 HSDIV8 CLKOUT",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_POSTDIV4_16FF_MAIN_2_HSDIVOUT8_CLK",
            isConfigurable: true,
            defaultFreq: 100000000 },
        { name: 1, displayName: "MAIN PLL1 HSDIV6 CLKOUT",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK",
            isConfigurable: true,
            defaultFreq: 96000000 },
        { name: 3, displayName: "AUDIO EXT REFCLK 0",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_BOARD_0_AUDIO_EXT_REFCLK0_OUT",
            isConfigurable: false,
            defaultFreq: 49152000 },
        { name: 4, displayName: "AUDIO EXT REFCLK 1",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_BOARD_0_AUDIO_EXT_REFCLK1_OUT",
            isConfigurable: false,
            defaultFreq: 49152000 },
        { name: 5, displayName: "AUDIO EXT REFCLK 2",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_BOARD_0_AUDIO_EXT_REFCLK2_OUT",
            isConfigurable: false,
            defaultFreq: 49152000 },
        { name: 6, displayName: "ATCLK 0",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT",
            isConfigurable: false,
            defaultFreq: 49152000 },
        { name: 7, displayName: "ATCLK 1",
            tisciOption: "TISCI_DEV_MCASP<n>_AUXCLK_SEL_DEV_VD_CLK_PARENT_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1",
            isConfigurable: false,
            defaultFreq: 49152000 },
    ]
};

let mcasp_auxclk_loc_sel = {
    type: "clk_source_mux",
    name: "aux_loc",
    displayName: "MCASP AUXCLK Local Clk Sel",
    tisciDevice: "TISCI_DEV_MCASP<n>_LOCAL_AUXCLK_SEL_DEV_VD",
    tisciClock: "TISCI_DEV_MCASP<n>_LOCAL_AUXCLK_SEL_DEV_VD_CLK",
    muxOptions: [
        { name: 2, displayName: "Main PLL4 HSCLK HSDIV 0",
            tisciOption: "TISCI_DEV_MCASP<n>_LOCAL_AUXCLK_SEL_DEV_VD_CLK_PARENT_HSDIV3_16FFT_MAIN_4_HSDIVOUT0_CLK",
            isConfigurable: true,
            defaultFreq: 49152000 },
        { name: 0, displayName: "PLL4 REFCLK",
            tisciOption: "TISCI_DEV_MCASP<n>_LOCAL_AUXCLK_SEL_DEV_VD_CLK_PARENT_MAIN_PLL4_HFOSC_SEL_OUT0",
            isConfigurable: true,
            defaultFreq: 12500000 },
        { name: 1, displayName: "PLL4 REFCLK DIV 2",
            tisciOption: "TISCI_DEV_MCASP<n>_LOCAL_AUXCLK_SEL_DEV_VD_CLK_PARENT_MAIN_PLL4_HFOSC_SEL_OUT02",
            isConfigurable: true,
            defaultFreq: 25000000 },
    ]
};

let mcasp_auxclk_gf_sel = {
    type:"clk_mux",
    name: "mcasp_auxclk_gf_sel",
    displayName: "MCASP AUXCLK GF SEL0",
    tisciDevice: "TISCI_DEV_MCASP<n>",
    tisciClock: "TISCI_DEV_MCASP<n>_AUX_CLK",
    longDescription: auxClkMuxLongDescription,
    muxOptions:[
        {
            displayName: "MCASP AUXCLK Local Clk Sel",
            name: 0,
            options: mcasp_auxclk_loc_sel,
            tisciOption: "TISCI_DEV_MCASP<n>_AUX_CLK_PARENT_MCASPN_AUXCLK_LOCAL_SEL_OUT<n>",
        },
        {
            displayName: "MCASP AUXCLK External clk Sel",
            name: 1,
            options: mcasp_auxclk_sel,
            tisciOption: "TISCI_DEV_MCASP<n>_AUX_CLK_PARENT_MCASPN_AUXCLK_SEL_OUT<n>",
        }
    ]
};

exports = {
    mcasp_auxclk_gf_sel,
};
