let common = system.getScript("/common");

let dss_pixel_clk_freq = 1051925000;        // 1051.925 MHz
let dss_hdmi_pixel_clk_freq = 148500000;    // 148.5 MHz
let dss_dsi_pixel_clk_freq = 150000000         // 150 MHz


const dss_config_videoports =
[
    { name : "VP1", displayName : "VP1" },
    { name : "VP2", displayName : "VP2" },
    { name : "VP3", displayName : "VP3" },
    { name : "VP4", displayName : "VP4" }
];

const dss_config_videopipelines =
[
    { name : "VID1", displayName : "VID" },
    { name : "VIDL1", displayName : "VIDL" },
    { name : "All" , displayName : "VID and VIDL"}
];

const dss_config_overlaymanager =
[
    {name : "OVR1", displayName : "OVR1"},
    {name : "OVR2", displayName : "OVR2"},
    {name : "OVR3", displayName : "OVR3"},
    {name : "OVR4", displayName : "OVR4"}
];

const dss_display_interface =
[
    {name : "OLDI", displayName : "OLDI Panel"},
    {name : "HDMI", displayName : "HDMI Panel"},
    {name : "DSI", displayName : "DSI Panel"}
];

const dss_panel_attributes =
[
    {
        name: "OLDIPanel",
        width: 1920,
        height: 1200,
        horizontalFrontPorch: 52,
        horizontalBackPorch: 32,
        verticalFrontPorch: 8,
        verticalBackPorch: 24,
        hsycnLength: 24,
        vsyncLength: 3
    }
];

const dss_config_r5fss = [
    {
        name                : "DSS0",
        pixelClock          :  dss_pixel_clk_freq,
        clockIds            : [ "TISCI_DEV_DSS0", "TISCI_DEV_OLDI0_VD", "TISCI_DEV_OLDI1_VD" ],
        clockFrequencies    : [
                            {
                                moduleId: "TISCI_DEV_DSS0",
                                clkId   : "TISCI_DEV_DSS0_DPI_1_IN_CLK",
                                clkRate : dss_hdmi_pixel_clk_freq,
                            },
                            {
                                moduleId: "TISCI_DEV_DSS0",
                                clkId   : "TISCI_DEV_DSS0_DPI_0_IN_CLK",
                                clkRate : dss_pixel_clk_freq,
                            },
    ]
    },
    {
        name                : "DSS1",
        pixelClock          :  dss_pixel_clk_freq,
        clockIds            : [ "TISCI_DEV_DSS1", "TISCI_DEV_DSS_DSI0", "TISCI_DEV_DPHY_TX0"],
        clockFrequencies    : [
                            {
                                moduleId: "TISCI_DEV_DSS1",
                                clkId   : "TISCI_DEV_DSS1_DPI_1_IN_CLK",
                                clkRate : dss_dsi_pixel_clk_freq,
                            },
    ]
    },
];

function getDefaultConfig()
{
    return dss_config_r5fss[0];
}

function getConfigArr() {

    return dss_config_r5fss;
}

function getDefaultVideoPort()
{
    return dss_config_videoports[0];
}

function getVideoPort()
{
    return dss_config_videoports;
}

function getDefaultVideoPipeline()
{
    return dss_config_videopipelines[2];
}

function getVideoPipeline()
{
    return dss_config_videopipelines;
}

function getDefaultOverlayManager()
{
    return dss_config_overlaymanager[0];
}

function getOverlayManager()
{
    return dss_config_overlaymanager;
}

function getDefaultDisplayInterface()
{
    return dss_display_interface[0];
}

function getDisplayInterface()
{
    return dss_display_interface;
}

function getPanelAttributes()
{
    return dss_panel_attributes[0];
}


exports = {
    getDefaultConfig,
    getConfigArr,
    getDefaultVideoPort,
    getVideoPort,
    getDefaultVideoPipeline,
    getVideoPipeline,
    getDefaultOverlayManager,
    getOverlayManager,
    getDefaultDisplayInterface,
    getDisplayInterface,
    getPanelAttributes,
};


