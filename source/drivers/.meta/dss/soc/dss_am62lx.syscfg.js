let common = system.getScript("/common");

let dss_pixel_clk_freq_oldi = 1051925000;
let dss_pixel_clk_freq_dpi = 148500000;

const dss_config_videoports =
[
    { name : "VP1", displayName : "VP1" },
];

const dss_config_videopipelines =
[
    { name : "VIDL1", displayName : "VIDL" },
];

const dss_config_overlaymanager =
[
    {name : "OVR1", displayName : "OVR1"},
];

const dss_display_interface =
[
    {name : "DPI", displayName : "DPI Panel/Bridge"}
];

const dss_oldi_panel_attributes =
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

const dss_config_a53ss = [
    {
        name                : "DSS0",
        pixelClock          :  dss_pixel_clk_freq_dpi,
        clockIds            : [ "AM62LX_DEV_DSS0"],
        clockFrequencies    : [
                                {
                                    moduleId: "AM62LX_DEV_DSS0",
                                    clkId   : "AM62LX_DEV_DSS0_DPI_0_IN_CLK",
                                    clkRate : dss_pixel_clk_freq_dpi,
                                }
                              ],
        clockIdsVP1         : [ "AM62LX_DEV_DSS0" ],
        clockFrequenciesVP1 : [
                                {
                                    moduleId: "AM62LX_DEV_DSS0",
                                    clkId   : "AM62LX_DEV_DSS0_DPI_0_IN_CLK",
                                    clkRate : dss_pixel_clk_freq_dpi,
                                }
                              ],
    },
];

function getDefaultConfig()
{
    return dss_config_a53ss[0];
}

function getConfigArr() {

    return dss_config_a53ss;
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
    return [];
}

function getDefaultVideoPipeline()
{
    return dss_config_videopipelines[0];
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
    return [];
}

function getDefaultDisplayInterface()
{
    return dss_display_interface[0];
}

function getDisplayInterface()
{
    return dss_display_interface;
}

function getDefaultOldiPanelAttributes()
{
    return dss_oldi_panel_attributes[0];
}

function getDefaultOldiPixelFreq()
{
    return dss_pixel_clk_freq_oldi;
}

function getDefaultDPIPixelFreq()
{
    return dss_pixel_clk_freq_dpi;
}

function getOldiPanelAttributes()
{
    return dss_oldi_panel_attributes;
}

function getConnectDisplayInterface(vpInstance)
{
    if(vpInstance == "VP1")
        return "DPI";
}

function getDefaultVIDPipeline()
{
    return false;
}

function getDefaultVIDLPipeline()
{
    return true;
}

function getZorder0DefaultLayer()
{
    return { name : "VIDL1", ui : false}
}

function getZorder1DefaultLayer()
{
    return { name : "VIDL1", ui : true}
}

function getZorderOptions()
{
    return [
        { name: "VIDL1", displayName: "VIDL" }
    ];
}

function getOLDISupported()
{
    return false;
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
    getDefaultOldiPanelAttributes,
    getOldiPanelAttributes,
    getDefaultOldiPixelFreq,
    getDefaultDPIPixelFreq,
    getConnectDisplayInterface,
    getDefaultVIDPipeline,
    getDefaultVIDLPipeline,
    getZorder0DefaultLayer,
    getZorder1DefaultLayer,
    getZorderOptions,
    getOLDISupported
};


