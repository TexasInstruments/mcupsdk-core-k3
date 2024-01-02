let common = system.getScript("/common");

let dss_pixel_clk_freq = 1051925000;

const dss_config_videoports =
[
    { name : "VP1", displayName : "VP1" },
    { name : "VP2", displayName : "VP2" }
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
    {name : "OVR2", displayName : "OVR2"}
];

const dss_display_interface =
[
    {name : "OLDI", displayName : "OLDI Panel"},
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
        clockIds            : [ "TISCI_DEV_DSS0" , "TISCI_DEV_OLDI0_VD", "TISCI_DEV_OLDI1_VD"],
        clockFrequencies    : [
                            {
                                moduleId: "TISCI_DEV_DSS0",
                                clkId   : "TISCI_DEV_DSS0_DPI_0_IN_CLK",
                                clkRate : dss_pixel_clk_freq,
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

function getDisabledVideoPort()
{
    return [{ name : "VP2", displayName : "VP2", reason:"Not supported for configuration"}];
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

function getDisabledOverlayManager()
{
    return [{ name : "OVR2", displayName : "OVR2", reason:"Not supported for configuration"}];
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
    getDisabledVideoPort,
    getDefaultVideoPipeline,
    getVideoPipeline,
    getDefaultOverlayManager,
    getOverlayManager,
    getDisabledOverlayManager,
    getDefaultDisplayInterface,
    getDisplayInterface,
    getPanelAttributes,
};


