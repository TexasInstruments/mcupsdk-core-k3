let common = system.getScript("/common");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/dss/soc/dss_${common.getSocName()}`);

function getConfigArr() {
	return soc.getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let solution = moduleInstance[getInterfaceName(moduleInstance)].$solution;
    let configArr = getConfigArr();
    let config = configArr.find(o => o.name === solution.peripheralName);

    config.clockFrequencies[0].clkRate = moduleInstance.pixelClkFreq;

    return {
        ...config,
        ...moduleInstance,
    };
};

function getInterfaceName(inst) {

    return "DSS";
}

function getPeripheralPinNames(inst) {
    return [ "DATA0", "DATA1", "DATA2", "DATA3", "DATA4", "DATA5", "DATA6", "DATA7", "DATA8",
             "DATA9", "DATA10", "DATA11", "DATA12", "DATA13", "DATA14", "DATA15", "DATA16",
             "DATA17", "DATA18", "DATA19", "DATA20", "DATA21", "DATA22", "DATA23", "DE",
             "EXTPCLKIN", "HSYNC", "PCLK", "VSYNC" ];
}

function pinmuxRequirements(inst) {
   let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    if(inst.selectDisplayInterface != soc.getDefaultDisplayInterface().name)
    {
        pinResource = pinmux.getPinRequirements(interfaceName, "DATA0", "DSS DATA0 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA1", "DSS DATA1 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA2", "DSS DATA2 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA3", "DSS DATA3 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA4", "DSS DATA4 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA5", "DSS DATA5 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA6", "DSS DATA6 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA7", "DSS DATA7 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA8", "DSS DATA8 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA9", "DSS DATA9 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA10", "DSS DATA10 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA11", "DSS DATA11 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA12", "DSS DATA12 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA13", "DSS DATA13 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA14", "DSS DATA14 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA15", "DSS DATA15 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA16", "DSS DATA16 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA17", "DSS DATA17 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA18", "DSS DATA18 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA19", "DSS DATA19 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA20", "DSS DATA20 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA21", "DSS DATA21 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA22", "DSS DATA22 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DATA23", "DSS DATA23 Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "DE", "DSS DE Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "EXTPCLKIN", "DSS EXTPCLKIN Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "HSYNC", "DSS HSYNC Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "PCLK", "DSS PCLK Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

        pinResource = pinmux.getPinRequirements(interfaceName, "VSYNC", "DSS VSYNC Pin");
        pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
        resources.push( pinResource);

    }

    let peripheral = {
        name: interfaceName,
        displayName: "DSS Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    return [peripheral];
}

function getClockEnableIds(inst) {

    let instConfig = getInstanceConfig(inst);

    return instConfig.clockIds;
}

function getClockFrequencies(inst) {

    let instConfig = getInstanceConfig(inst);

    return instConfig.clockFrequencies;
}

let default_frame_format = "BGRA32_8888";

/* Add frame formats here and update the number of bytes pixel in the funtion below */
const dss_frame_formats = [
    { name : "BGRA32_8888", displayName : "BGRA32" },
    { name : "ARGB32_8888", displayName : "ARGB32" },
    { name : "RGBA32_8888", displayName : "RGBA32" },
    { name : "RGB24_888", displayName : "RGB24" },
    { name : "BGR24_888", displayName : "BGR24" },
];

function getBytesPerPixel(format)
{
    switch(format)
    {
        case "BGRA32_8888":
        case "ARGB32_8888":
        case "RGBA32_8888":
            return 4;
        case "RGB24_888":
        case "BGR24_888":
            return 3;
    }
}

function getVideoPipelineChange(inst,ui)
{
    inst.vidSafetyConfig = "false";
    inst.vidlSafetyConfig = "false";

    if (inst.selectVideoPipeline == "All") {
        inst.zorder0 = "VID1";
        inst.zorder1 = "VIDL1";

        ui.zorder1.hidden = false;

        ui.vidFrameFormat.hidden = false;
        ui.vidInputFrameWidth.hidden = false;
        ui.vidInputFrameheight.hidden = false;
        ui.vidOutputFrameWidth.hidden = false;
        ui.vidOutputFrameHeight.hidden = false;
        ui.vidPosX.hidden = false;
        ui.vidPosY.hidden = false;
        ui.vidGlobalAlpha.hidden = false;
        ui.vidPremultiplyAlpha.hidden = false;
        ui.vidScaler.hidden = false;
        ui.vidSafetyConfig.hidden = false;

        ui.vidlFrameFormat.hidden = false;
        ui.vidlInputFrameWidth.hidden = false;
        ui.vidlInputFrameheight.hidden = false;
        ui.vidlOutputFrameWidth.hidden = false;
        ui.vidlOutputFrameHeight.hidden = false;
        ui.vidlPosX.hidden = false;
        ui.vidlPosY.hidden = false;
        ui.vidlGlobalAlpha.hidden = false;
        ui.vidlPremultiplyAlpha.hidden = false;
        ui.vidlSafetyConfig.hidden = false;
    }
    else
    {

        if(inst.dispShare == true)
        {
            inst.zorder0 = "VID1";
            inst.zorder1 =  "VIDL1";
            ui.zorder1.hidden = false;
        }
        else
        {
            if(inst.selectVideoPipeline == "VID1")
            {
                inst.zorder0 = "VID1";
            }
            else
            {
                inst.zorder0 = "VIDL1";
            }

            ui.zorder1.hidden = true;
        }

        if(inst.selectVideoPipeline == "VIDL1")
        {
            ui.vidFrameFormat.hidden = true;
            ui.vidInputFrameWidth.hidden = true;
            ui.vidInputFrameheight.hidden = true;
            ui.vidOutputFrameWidth.hidden = true;
            ui.vidOutputFrameHeight.hidden = true;
            ui.vidPosX.hidden = true;
            ui.vidPosY.hidden = true;
            ui.vidGlobalAlpha.hidden = true;
            ui.vidPremultiplyAlpha.hidden = true;
            ui.vidScaler.hidden = true;
            ui.vidSafetyConfig.hidden = true;

            ui.vidlFrameFormat.hidden = false;
            ui.vidlInputFrameWidth.hidden = false;
            ui.vidlInputFrameheight.hidden = false;
            ui.vidlOutputFrameWidth.hidden = false;
            ui.vidlOutputFrameHeight.hidden = false;
            ui.vidlPosX.hidden = false;
            ui.vidlPosY.hidden = false;
            ui.vidlGlobalAlpha.hidden = false;
            ui.vidlPremultiplyAlpha.hidden = false;
            ui.vidlSafetyConfig.hidden = false;
        }
        else if(inst.selectVideoPipeline == "VID1")
        {
            ui.vidlFrameFormat.hidden = true;
            ui.vidlInputFrameWidth.hidden = true;
            ui.vidlInputFrameheight.hidden = true;
            ui.vidlOutputFrameWidth.hidden = true;
            ui.vidlOutputFrameHeight.hidden = true;
            ui.vidlPosX.hidden = true;
            ui.vidlPosY.hidden = true;
            ui.vidlGlobalAlpha.hidden = true;
            ui.vidlPremultiplyAlpha.hidden = true;
            ui.vidlSafetyConfig.hidden = true;


            ui.vidFrameFormat.hidden = false;
            ui.vidInputFrameWidth.hidden = false;
            ui.vidInputFrameheight.hidden = false;
            ui.vidOutputFrameWidth.hidden = false;
            ui.vidOutputFrameHeight.hidden = false;
            ui.vidPosX.hidden = false;
            ui.vidPosY.hidden = false;
            ui.vidGlobalAlpha.hidden = false;
            ui.vidPremultiplyAlpha.hidden = false;
            ui.vidScaler.hidden = false;
            ui.vidSafetyConfig.hidden = false;
        }
    }
}

let dss_module_name = "/drivers/dss/dss";

let dss_module = {
    displayName: "DSS",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/dss/templates/dss_config.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/dss/templates/dss.h.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/dss/templates/dss_open_close.h.xdt",
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: dss_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: dss_module_name,
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_DSS",
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    config : [
        {
            name: "selectVideoPipeline",
            displayName: "Video Pipeline",
            default: soc.getDefaultVideoPipeline().name,
            options: function (inst) {

                if(inst.dispShare == true)
                {
                    return [{ name : "VID1", displayName : "VID" },
                    { name : "VIDL1", displayName : "VIDL" }];
                }

                return soc.getVideoPipeline();
            },
            hidden: false,
            onChange: function(inst,ui){
                getVideoPipelineChange(inst,ui);
            }
        },
        {
            name: "selectOverlayManager",
            displayName: "Overlay Manager",
            default: soc.getDefaultOverlayManager().name,
            options: soc.getOverlayManager(),
            getDisabledOptions : () => soc.getDisabledOverlayManager(),
        },
        {
            name: "selectVP",
            displayName: "Video Port",
            default: soc.getDefaultVideoPort().name,
            options: soc.getVideoPort(),
            getDisabledOptions : () => soc.getDisabledVideoPort(),
        },
        {
            name: "selectDisplayInterface",
            displayName: "Display Interface",
            default: soc.getDefaultDisplayInterface().name,
            options: soc.getDisplayInterface(),
        },
        {
            name: "numFramesPerPipeline",
            displayName: "Pipeline Frames",
            description: "Number of frames per pipeline",
            default: 2,
            displayFormat : "dec"
        },
        {
            name : "dispShare",
            displayName : "Display Share With HLOS",
            default : false,
            hidden: false,
            onChange: function(inst,ui){

                if(inst.dispShare == true)
                {
                    inst.selectVideoPipeline = "VIDL1";
                    getVideoPipelineChange(inst,ui);
                }
                else
                {
                    inst.selectVideoPipeline = "All";
                    getVideoPipelineChange(inst,ui);
                }
            }
        },
        {
            name : "vidPipelineConfig",
            displayName: "VID Pipeline Config",
            collapsed : true,
            config: [
                {
                    name: "vidFrameFormat",
                    displayName: "Frame Format",
                    default: default_frame_format,
                    options: dss_frame_formats,
                    hidden : false,
                },
                {
                    name: "vidInputFrameWidth",
                    displayName: "Input Frame Width",
                    default : 480,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidInputFrameheight",
                    displayName: "Input Frame Height",
                    default : 360,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidOutputFrameWidth",
                    displayName: "Output Frame Width",
                    default : 720,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidOutputFrameHeight",
                    displayName: "Output Frame Height",
                    default : 540,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name : "vidPosX",
                    displayName: "X Axis Position",
                    description: "X axis position of frame in pixel",
                    default: 0,
                    displayFormat : "dec",
                    hidden: false
                },
                {
                    name : "vidPosY",
                    displayName: "Y Axis Position",
                    description: "Y axis position of frame in pixel",
                    default: 0,
                    displayFormat : "dec",
                    hidden: false
                },
                {
                    name : "vidGlobalAlpha",
                    displayName: "Global Alpha",
                    default : 0xFF,
                    displayFormat : "hex",
                    hidden : false,
                },
                {
                    name : "vidPremultiplyAlpha",
                    displayName: "Premultiply Alpha",
                    longDescription : "Frame data is already multiplied with Alpha,\n" + "\n" +
                                "The field configures the DISPC VID to process incoming data as\n"+ "\n" +
                                "premultiplied alpha data or non premultiplied alpha data",
                    default : "false",
                    options : [
                        {name :"false", displayName: "Disable"},
                        {name :"true", displayName : "Enable"}
                    ],
                    hidden : false,
                },
                {
                    name : "vidScaler",
                    displayName : "Scaler",
                    description :"Enable scaler for the pipeline",
                    default: "true",
                    options : [
                        {name : "true", displayName :"Enable"},
                        {name : "false", displayName : "Disable"}
                    ],
                    hidden : false,

                },
                {
                    name : "vidSafetyConfig",
                    displayName : "Enable VID Safety Config",
                    default : "false",
                    options: [
                        { name : "false", displayName: "Disable" },
                        { name : "true", displayName : "Enable" },
                    ],
                    hidden : false,
                }
            ]
        },
        {
            name : "vidlPipelineConfig",
            displayName: "VIDL Pipeline Config",
            collapsed : true,
            config: [
                {
                    name: "vidlFrameFormat",
                    displayName: "Frame Format",
                    default: default_frame_format,
                    options: dss_frame_formats,
                    hidden : false,
                },
                {
                    name: "vidlInputFrameWidth",
                    displayName: "Input Frame Width",
                    default : 480,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidlInputFrameheight",
                    displayName: "Input Frame Height",
                    default : 360,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidlOutputFrameWidth",
                    displayName: "Output Frame Width",
                    default : 480,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name: "vidlOutputFrameHeight",
                    displayName: "Output Frame Height",
                    default : 360,
                    displayFormat: "dec",
                    hidden : false,
                },
                {
                    name : "vidlPosX",
                    displayName: "X Axis Position",
                    description: "X axis position of frame in pixel",
                    default: 1440,
                    displayFormat : "dec",
                    hidden: false
                },
                {
                    name : "vidlPosY",
                    displayName: "Y Axis Position",
                    description: "Y axis position of frame in pixel",
                    default: 840,
                    displayFormat : "dec",
                    hidden: false
                },
                {
                    name : "vidlGlobalAlpha",
                    displayName: "Global Alpha",
                    default : 0xFF,
                    displayFormat : "hex",
                    hidden : false,
                },
                {
                    name : "vidlPremultiplyAlpha",
                    displayName: "Premultiply Alpha",
                    longDescription : "Frame data is already multiplied with Alpha,\n" + "\n" +
                                "The field configures the DISPC VID to process incoming data as\n" + "\n" +
                                "premultiplied alpha data or non premultiplied alpha data",
                    default : "false",
                    options : [
                        {name :"false", displayName: "Disable"},
                        {name :"true", displayName : "Enable"}
                    ],
                    hidden : false,
                },
                {
                    name : "vidlSafetyConfig",
                    displayName : "Enable VIDL Safety Config",
                    default : "false",
                    options: [
                        { name : "false", displayName: "Disable" },
                        { name : "true", displayName : "Enable" },
                    ],
                    hidden : false,
                }
            ]
        },
        {

            name: "ovrConfig",
            displayName: "Overlay Manager Configuration",
            collapsed: true,
            config: [
                {
                    name: "colorBarEnable",
                    displayName: "Colorbar",
                    description: "Enable colorbar",
                    default: "false",
                    options: [
                        { name: "true", displayName: "Enable" },
                        { name: "false", displayName: "Disable" }
                    ],
                    onChange : function(inst,ui) {
                        if (inst.colorBarEnable == "false") {

                            ui.vidFrameFormat.hidden = false;
                            ui.vidInputFrameWidth.hidden = false;
                            ui.vidInputFrameheight.hidden = false;
                            ui.vidOutputFrameWidth.hidden = false;
                            ui.vidOutputFrameHeight.hidden = false;
                            ui.vidPosX.hidden = false;
                            ui.vidPosY.hidden = false;
                            ui.vidGlobalAlpha.hidden = false;
                            ui.vidPremultiplyAlpha.hidden = false;
                            ui.vidScaler.hidden = false;

                            ui.vidlFrameFormat.hidden = false;
                            ui.vidlInputFrameWidth.hidden = false;
                            ui.vidlInputFrameheight.hidden = false;
                            ui.vidlOutputFrameWidth.hidden = false;
                            ui.vidlOutputFrameHeight.hidden = false;
                            ui.vidlPosX.hidden = false;
                            ui.vidlPosY.hidden = false;
                            ui.vidlGlobalAlpha.hidden = false;
                            ui.vidlPremultiplyAlpha.hidden = false;
                            ui.selectVideoPipeline.hidden = false;
                        }
                        else
                        {
                            ui.vidFrameFormat.hidden = true;
                            ui.vidInputFrameWidth.hidden = true;
                            ui.vidInputFrameheight.hidden = true;
                            ui.vidOutputFrameWidth.hidden = true;
                            ui.vidOutputFrameHeight.hidden = true;
                            ui.vidPosX.hidden = true;
                            ui.vidPosY.hidden = true;
                            ui.vidGlobalAlpha.hidden = true;
                            ui.vidPremultiplyAlpha.hidden = true;
                            ui.vidScaler.hidden = true;

                            ui.vidlFrameFormat.hidden = true;
                            ui.vidlInputFrameWidth.hidden = true;
                            ui.vidlInputFrameheight.hidden = true;
                            ui.vidlOutputFrameWidth.hidden = true;
                            ui.vidlOutputFrameHeight.hidden = true;
                            ui.vidlPosX.hidden = true;
                            ui.vidlPosY.hidden = true;
                            ui.vidlGlobalAlpha.hidden = true;
                            ui.vidlPremultiplyAlpha.hidden = true;
                            ui.selectVideoPipeline.hidden = true;
                        }
                    }
                },
                {
                    name: "colorKeyEnable",
                    displayName: "Transparency Color Key",
                    description: "Transparency Color Key Enable",
                    default: "false",
                    options: [
                        { name: "true", displayName: "Enable" },
                        { name: "false", displayName: "Disable" }
                    ]
                },
                {
                    name: "colorKeySelection",
                    displayName: "Transparency Color Key Selection",
                    longDescription: `Transparency Color Key Selection for Source or Destination\n` + "\n" +
                        `0 : Destination transparency color key selected\n` + "\n" +
                        `1 : Source transparency color key selected\n`,
                    default: "TRANS_COLOR_DEST",
                    options: [
                        { name: "TRANS_COLOR_DEST", displayName: "Destination" },
                        { name: "TRANS_COLOR_SRC", displayName: "Source" }
                    ]
                },
                {
                    name: "backgroundColor",
                    displayName: "Background Color",
                    description: "Default solid background color",
                    default: 0xc8c800,
                    displayFormat: "hex"
                },
                {
                    name: "layerConfig",
                    displayName: "Overlay Layer Configuration",
                    collapsed: true,
                    config: [
                        {
                            name: "zorder0",
                            displayName: "Layer 0 Input",
                            default: "VID1",
                            options: [
                                { name: "VID1", displayName: "VID" },
                                { name: "VIDL1", displayName: "VIDL" }
                            ],
                        },
                        {
                            name: "zorder1",
                            displayName: "Layer 1 Input",
                            default: "VIDL1",
                            hidden : false,
                            options: [
                                { name: "VID1", displayName: "VID" },
                                { name: "VIDL1", displayName: "VIDL" }
                            ],
                        }
                    ]
                }
            ]
        },
        {
            name: "vpConfig",
            displayName: "Video Port Timing Configuration",
            collapsed: true,
            config: [
                {
                    name: "pixelClkFreq",
                    displayName: "Pixel Clock Frequency (Hz)",
                    default: soc.getDefaultConfig().pixelClock,
                },
                {
                    name: "panelWidth",
                    displayName: "Panel Width",
                    description: "Width of Panel in pixel",
                    default: soc.getPanelAttributes().width,
                    displayFormat: "dec",
                },
                {
                    name: "panelHeight",
                    displayName: "Panel Height",
                    description: "Height of Panel in pixel",
                    default: soc.getPanelAttributes().height,
                    displayFormat: "dec",
                },
                {
                    name: "hBackPorch",
                    displayName: "Horizontal Back Porch",
                    description: "Horizontal Back Porch in pixel",
                    default: soc.getPanelAttributes().horizontalBackPorch,
                    displayFormat: "dec",
                },
                {
                    name: "hFrontPorch",
                    displayName: "Horizontal Front Porch",
                    description: "Horizontal Front Porch in pixel",
                    default: soc.getPanelAttributes().horizontalFrontPorch,
                    displayFormat: "dec",
                },
                {
                    name: "vBackPorch",
                    displayName: "Vertical Back Porch",
                    description: "Vertical Back Porch in pixel",
                    default: soc.getPanelAttributes().verticalBackPorch,
                    displayFormat: "dec",
                },
                {
                    name: "vFrontPorch",
                    displayName: "Vertical Front Porch",
                    description: "Veritcal Front Porch in pixel",
                    default: soc.getPanelAttributes().verticalFrontPorch,
                    displayFormat: "dec",
                },
                {
                    name: "hSyncLength",
                    displayName: "Horizontal Sync Length",
                    description: "Horizontal sync length in pixel",
                    default: soc.getPanelAttributes().hsycnLength,
                    displayFormat: "dec",
                },
                {
                    name: "vSyncLength",
                    displayName: "Vertical Sync Length",
                    description: "Vertical sync length in pixel",
                    default: soc.getPanelAttributes().vsyncLength,
                    displayFormat: "dec",
                },
                {
                    name : "advVPconfig",
                    displayName: "Advanced VP Configuration",
                    collapsed: true,
                    config : [
                        {
                            name : "videoInterfaceWidth",
                            displayName: "Video Interface Width",
                            default : "VIFW_24BIT",
                            options: [
                                {name : "VIFW_10BIT" , displayName: "10-BIT", description: "10-bit interface" },
                                {name : "VIFW_12BIT" , displayName: "12-BIT", description: "12-bit interface" },
                                {name : "VIFW_14BIT" , displayName: "14-BIT", description: "14-bit interface" },
                                {name : "VIFW_16BIT" , displayName: "16-BIT", description: "16-bit interface" },
                                {name : "VIFW_18BIT" , displayName: "18-BIT", description: "18-bit interface" },
                                {name : "VIFW_20BIT" , displayName: "20-BIT", description: "20-bit interface" },
                                {name : "VIFW_24BIT" , displayName: "24-BIT", description: "24-bit interface" },
                                {name : "VIFW_30BIT" , displayName: "30-BIT", description: "30-bit interface" },
                                {name : "VIFW_36BIT" , displayName: "36-BIT", description: "36-bit interface" },
                            ],
                        },
                        {
                            name : "activeVideoPolarity",
                            displayName : "Video Polarity",
                            description : "Invert Output Enable, 0 is active high, 1 is active low",
                            default : "POL_HIGH",
                            options: [
                                { name : "POL_HIGH", displayName : "High Polarity" },
                                { name : "POL_LOW", displayName : "Low Polarity"}
                            ]

                        },
                        {
                            name : "pixelClockPolarity",
                            displayName : "Pixel Clock Polarity",
                            longDescription : "Invert Pixel Clock\n" + "\n" +
                                           "0 : Data is driven on the LCD data lines on the rising-edge of the pixel clock\n" + "\n" +
                                           "1 : Data is driven on the LCD data lines on the falling-edge of the pixel clock",
                            default : "EDGE_POL_RISING",
                            options: [
                                { name : "EDGE_POL_RISING", displayName : "Rising Edge Polarity" },
                                { name : "EDGE_POL_FALLING", displayName : "Falling Edge Polarity"}
                            ]

                        },
                        {
                            name : "hSyncPolarity",
                            displayName : "Horizontal Sync Polarity",
                            longDescription : "Invert Horizontal Sync\n" + "\n" +
                                           "0 : HSYNC pin is active high and inactive low\n"+ "\n" +
                                           "1 : HSYNC pin is active low and inactive high",
                            default : "POL_HIGH",
                            options: [
                                { name : "POL_HIGH", displayName : "High Polarity" },
                                { name : "POL_LOW", displayName : "Low Polarity"}
                            ]

                        },
                        {
                            name : "vSyncPolarity",
                            displayName : "Vertical Sync Polarity",
                            longDescription : "Invert Vertical Sync\n" + "\n" +
                            "0 : VSYNC pin is active high and inactive low\n" + "\n" +
                            "1 : VSYNC pin is active low and inactive high",
                            default : "POL_HIGH",
                            options: [
                                { name : "POL_HIGH", displayName : "High Polarity" },
                                { name : "POL_LOW", displayName : "Low Polarity"}
                            ]

                        },
                        {
                            name : "hvSyncAlign",
                            displayName : "Hsync Vsync Align",
                            longDescription : "Alignment between HSYNC and VSYNC assertion\n" + "\n" +
                            "0 : HSYNC and VSYNC are not aligned\n" + "\n" +
                            "1 : HSYNC and VSYNC assertions are aligned",
                            default : "HVSYNC_ALIGNED",
                            options: [
                                { name : "HVSYNC_ALIGNED", displayName : "Align" },
                                { name : "HVSYNC_NOT_ALIGNED", displayName : "Not Align"}
                            ]
                        },
                        {
                            name : "hvSyncPixelClockControl",
                            displayName : "Hsync Vsync Pixel Clock Control",
                            longDescription : "HSYNC/VSYNC Pixel clock Control On/Off\n" + "\n" +
                            "0 : HSYNC and VSYNC are driven on opposite edges of pixel clock than pixel data\n" + "\n" +
                            "1 : HSYNC and VSYNC are driven on falling edge of pixel clock",
                            default : "HVCLK_CONTROL_ON",
                            options: [
                                { name : "HVCLK_CONTROL_ON", displayName : "Clock Control ON" },
                                { name : "HVCLK_CONTROL_OFF", displayName : "Clock Control OFF"}
                            ]
                        },
                        {
                            name : "vpSafetyConfig",
                            displayName : "Enable VP Safety Config",
                            default : "false",
                            options: [
                                { name : "false", displayName: "Disable" },
                                { name : "true", displayName : "Enable" },
                            ],
                        }
                    ],
                },
            ],
        },
        {
            name : "oldiConfig",
            displayName : "OLDI Configuration",
            collapsed : true,
            config: [
                {
                    name : "oldiMapType",
                    displayName: "OLDI Map Type",
                    default: "OLDI_MAP_TYPE_F",
                    options : [
                        { name: "OLDI_MAP_TYPE_F", displayName : "DUAL LINK 24 BIT VESA"},
                        { name: "OLDI_MAP_TYPE_C", displayName : "SINGLE LINK 24 BIT VESA"},

                    ]
                },
                {
                    name : "oldiBitDepth",
                    displayName: "Input Bit Depth",
                    description : "Input RGB data Bit Depth from DSS",
                    default : "24_BITS",
                    options : [
                        {name : "24_BITS", displayName : "24 Bit"},
                        {name : "18_BITS", displayName : "18 Bit"}
                    ]
                },
                {
                    name : "oldiDataEnablePolarity",
                    displayName : "Data Enable Polarity",
                    description : "Polarity of DE signal\n, \
                                   0 : DE is active-high\n, \
                                   1 : DE is active-low",
                    default : "POL_LOW",
                    options: [
                        { name : "POL_HIGH", displayName : "Active High Polarity" },
                        { name : "POL_LOW", displayName : "Active Low Polarity"}
                    ]

                },
                {
                    name : "dualModeSync",
                    displayName: "Dual Mode Sync",
                    default : "OLDI_DUALMODESYNC_ENABLE",
                    options : [
                        {name : "OLDI_DUALMODESYNC_ENABLE", displayName: "Enable"},
                        {name : "OLDI_DUALMODESYNC_DISABLE", displayName : "Disable"}
                    ]

                }
            ]
        },

    ],
    moduleInstances: addModuleInstances,
    pinmuxRequirements,
    getInstanceConfig,
    getInterfaceName,
    getPeripheralPinNames,
    getClockEnableIds,
    getClockFrequencies,
    getBytesPerPixel,

};


function addModuleInstances(instance) {
    let modInstances = new Array();

    if(instance.vpSafetyConfig == "true") {
            modInstances.push({
                name: "dssVPSafetyConfig",
                displayName: "VP Safety Region",
                moduleName: '/drivers/dss/v0/dss_safety_v0',
                useArray: true,
                minInstanceCount: 1,
                maxInstanceCount: 4,
                requiredArgs: {
                    panelWidth: instance.panelWidth,
                    panelHeight: instance.panelHeight
                },
            })
    }
    if(instance.selectVideoPipeline == "VID1" )
    {
        if(instance.vidSafetyConfig == "true")
        {
            modInstances.push({
                name: "dssVIDSafetyConfig",
                displayName: "VID Pipeline Safety Region",
                moduleName: '/drivers/dss/v0/dss_safety_v0',
                useArray: true,
                minInstanceCount: 1,
                maxInstanceCount: 1,
                requiredArgs: {
                    panelWidth: instance.panelWidth,
                    panelHeight: instance.panelHeight
                },
            })
        }
    }
    if(instance.selectVideoPipeline == "VIDL1" )
    {
        if(instance.vidlSafetyConfig == "true")
        {
            modInstances.push({
                name: "dssVIDLSafetyConfig",
                displayName: "VIDL Pipeline Safety Region",
                moduleName: '/drivers/dss/v0/dss_safety_v0',
                useArray: true,
                minInstanceCount: 1,
                maxInstanceCount: 1,
                requiredArgs: {
                    panelWidth: instance.panelWidth,
                    panelHeight: instance.panelHeight
                },
            })
        }
    }
    if(instance.selectVideoPipeline == "All" )
    {
        if(instance.vidSafetyConfig == "true")
        {
            modInstances.push({
                name: "dssVIDSafetyConfig",
                displayName: "VID Pipeline Safety Region",
                moduleName: '/drivers/dss/v0/dss_safety_v0',
                useArray: true,
                minInstanceCount: 1,
                maxInstanceCount: 1,
                requiredArgs: {
                    panelWidth: instance.panelWidth,
                    panelHeight: instance.panelHeight
                },
            })
        }
        if(instance.vidlSafetyConfig == "true")
        {
            modInstances.push({
                name: "dssVIDLSafetyConfig",
                displayName: "VIDL Pipeline Safety Region",
                moduleName: '/drivers/dss/v0/dss_safety_v0',
                useArray: true,
                minInstanceCount: 1,
                maxInstanceCount: 1,
                requiredArgs: {
                    panelWidth: instance.panelWidth,
                    panelHeight: instance.panelHeight
                },
            })
        }
    }

    return modInstances;
}

function validate(inst, report) {

    common.validate.checkNumberRange(inst, report, "vidlInputFrameWidth", 1, 3840, "dec");
    common.validate.checkNumberRange(inst, report, "vidlOutputFrameWidth", 1, 3840, "dec");
    common.validate.checkNumberRange(inst, report, "vidInputFrameWidth", 1, 3840, "dec");
    common.validate.checkNumberRange(inst, report, "vidOutputFrameWidth", 1, 3840, "dec");

    common.validate.checkNumberRange(inst, report, "vidlInputFrameHeight", 1, 2160, "dec");
    common.validate.checkNumberRange(inst, report, "vidlOutputFrameHeight", 1, 2160, "dec");
    common.validate.checkNumberRange(inst, report, "vidInputFrameHeight", 1, 2160, "dec");
    common.validate.checkNumberRange(inst, report, "vidOutputFrameHeight", 1, 2160, "dec");
    common.validate.checkNumberRange(inst, report, "numFramesPerPipeline", 1, 50, "dec");

    if(inst.selectVideoPipeline == "VID1" )
    {
        if(inst.vidOutputFrameWidth > inst.panelWidth){
            report.logError("Output frame width is more than the panel width in pixels.", inst, "vidOutputFrameWidth");
        }
        if(inst.vidOutputFrameHeight > inst.panelHeight){
            report.logError("Output frame height is more than the panel height in pixels.", inst, "vidOutputFrameHeight");
        }
        common.validate.checkNumberRange(inst, report, "vidGlobalAlpha", 0x0, 0xFF, "hex");
    }
    else if(inst.selectVideoPipeline == "VIDL1")
    {
        if(inst.vidlOutputFrameWidth > inst.panelWidth){
            report.logError("Output frame width is more than the panel width in pixels.", inst, "vidlOutputFrameWidth");
        }
        if(inst.vidlOutputFrameHeight > inst.panelHeight){
            report.logError("Output frame height is more than the panel height in pixels.", inst, "vidlOutputFrameHeight");
        }
        common.validate.checkNumberRange(inst, report, "vidlGlobalAlpha", 0x0, 0xFF, "hex");
    }
    else
    {
        if(inst.vidOutputFrameWidth > inst.panelWidth){
            report.logError("Output frame width is more than the panel width in pixels.", inst, "vidOutputFrameWidth");
        }
        if(inst.vidOutputFrameHeight > inst.panelHeight){
            report.logError("Output frame height is more than the panel height in pixels.", inst, "vidOutputFrameHeight");
        }
        if(inst.vidlOutputFrameWidth > inst.panelWidth){
            report.logError("Output frame width is more than the panel width in pixels.", inst, "vidlOutputFrameWidth");
        }
        if(inst.vidlOutputFrameHeight > inst.panelHeight){
            report.logError("Output frame height is more than the panel height in pixels.", inst, "vidlOutputFrameHeight");
        }

        common.validate.checkNumberRange(inst, report, "vidGlobalAlpha", 0x0, 0xFF, "hex");
        common.validate.checkNumberRange(inst, report, "vidlGlobalAlpha", 0x0, 0xFF, "hex");
    }

    common.validate.checkNumberRange(inst, report, "backgroundColor", 0x0, 0xFFFFFFFF, "hex");


    if((inst.selectVideoPipeline == "All" || inst.dispShare == true ) && inst.zorder0 == inst.zorder1)
    {
        report.logError("ZORDER for different layers can not point to the same pipeline", inst, "zorder0");
    }
    if(inst.selectVideoPipeline != "All" && inst.dispShare == false && inst.zorder0 != inst.selectVideoPipeline)
    {
        report.logError("Selected pipeline is different for Zorder",inst, "zorder0");
    }

}

exports = dss_module;