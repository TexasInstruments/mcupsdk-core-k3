let common = system.getScript("/common");
let bridgeTiming = system.getScript(`/board/panel/bridge/bridge_timing`);

function getInstanceConfig(moduleInstance) {
    return {
        ...moduleInstance,
    };
};

let bridge_sii9022a_module = {

    displayName: "Bridge SII9022A",
    collapsed: true,
    longDescription: "Select the correct I2C instance for the bridge. \
    Please refer to the TI EVM schematics",
    alwaysShowLongDescription: true,
    config: [
        {
            name : "resolution",
            displayName : "Resolution",
            default : bridgeTiming.getDefaultSii9022aTimingParams().resolution.name,
            options : bridgeTiming.getBridgeResolution(),
            onChange: function(inst)
            {
                let configArr = bridgeTiming.getSii9022aTimingParams();
                let config = configArr.find(o => o.resolution.name === inst.resolution);

                inst.outputFormat = bridgeTiming.getDefaultOutputFormat().name;
                inst.modeCode = config.modeCode;
                inst.pixClk = config.pixClk;
                inst.vFreq = config.vFreq;
                inst.pixels = config.pixels;
                inst.lines = config.lines;
                inst.hBitToHSync = config.hBitToHSync;
                inst.field2Offset = config.field2Offset;
                inst.hWidth = config.hWidth;
                inst.vBitToVSync = config.vBitToVSync;
                inst.vWidth = config.vWidth;
                inst.deDelay = config.deDelay;
                inst.deTop = config.deTop;
                inst.deCnt = config.deCnt;
                inst.deLine = config.deLine;
            }
        },
        {
            name : "outputFormat",
            displayName : "Ouput Format",
            default : bridgeTiming.getDefaultOutputFormat().name,
            options : bridgeTiming.getOutputFormat(),
        },
        {
            name : "modeCode",
            displayName : "Video Format Identification Code",
            default : bridgeTiming.getDefaultSii9022aTimingParams().modeCode,
            displayFormat: "dec",
        },
        {
            name : "pixClk",
            displayName : "Pixel Clock",
            default : bridgeTiming.getDefaultSii9022aTimingParams().pixClk,
            displayFormat: "dec",
        },
        {
            name : "vFreq",
            displayName : "Vertical Frequency",
            default : bridgeTiming.getDefaultSii9022aTimingParams().vFreq,
            displayFormat: "dec",
        },
        {
            name : "pixels",
            displayName : "Pixels Per Line",
            longDescription : "Number of pixels per line.",
            default : bridgeTiming.getDefaultSii9022aTimingParams().pixels,
            displayFormat: "dec",
        },
        {
            name : "lines",
            displayName : "Pixel Lines",
            longDescription : "Total number of pixel lines. ",
            default : bridgeTiming.getDefaultSii9022aTimingParams().lines,
            displayFormat: "dec",
        },
        {
            name : "hBitToHSync",
            displayName : "HBIT_TO_HSYNC",
            longDescription : "Set register to the delay from the detection of an \
            EAV sequence (H bit change from 1 to 0) to the active edge of \
            HSYNC. Unit of measure is pixels. Valid 1–1023",
            default : bridgeTiming.getDefaultSii9022aTimingParams().hBitToHSync,
            displayFormat: "dec",
        },
        {
            name : "field2Offset",
            displayName : "FIELD2_OFST",
            longDescription : "Determines VSYNC pixel offset for the odd field of \
            an interlaced source. Set this to half the number of pixels/line.\
            Valid 0–4095",
            default : bridgeTiming.getDefaultSii9022aTimingParams().field2Offset,
            displayFormat: "dec",
        },
        {
            name : "hWidth",
            displayName : "HWIDTH",
            longDescription : "Set the width of the HSYNC pulses. Set to the \
            desired HSYNC pulse width. Unit of measure is pixels. \
            Valid 1–1023",
            default : bridgeTiming.getDefaultSii9022aTimingParams().hWidth,
            displayFormat: "dec",
        },
        {
            name : "vBitToVSync",
            displayName : "VBIT_TO_VSYNC",
            longDescription : "Sets the delay from the detection of V bit changing \
            from 1 to 0 in an EAV sequence, to the asserting edge of VSYNC. \
            Unit of measure is lines. Valid 1–63",
            default : bridgeTiming.getDefaultSii9022aTimingParams().vBitToVSync,
            displayFormat: "dec",
        },
        {
            name : "vWidth",
            displayName : "VWIDTH",
            longDescription : "Sets the width of the VSYNC pulse. Unit of measure \
            is lines. Valid 1–63",
            default : bridgeTiming.getDefaultSii9022aTimingParams().vWidth,
            displayFormat: "dec",
        },
        {
            name : "deDelay",
            displayName : "DE_DLY",
            longDescription : "Set the width of the area to the left of the active \
            display. Unit of measure is pixels. This should be set to \
            the sum of (HSYNC width) + (horizontal back porch) + \
            (horizontal left border), and is used only for DE generation. \
            Valid range is 1–1023. 0 is invalid",
            default : bridgeTiming.getDefaultSii9022aTimingParams().deDelay,
            displayFormat: "dec",
        },
        {
            name : "deTop",
            displayName : "DE_TOP",
            longDescription : "Define the height of the area above the active \
            display. The unit of measure is lines (HSYNC pulses). This \
            should be set to the sum of (VSYNC width) + (vertical back porch) +\
            (vertical top border). Valid 1–127. 0 is invalid.",
            default : bridgeTiming.getDefaultSii9022aTimingParams().deTop,
            displayFormat: "dec",
        },
        {
            name : "deCnt",
            displayName : "DE_CNT",
            longDescription : "define the width of the active display. Unit of \
            measure is pixels. This should be set to the desired \
            horizontal resolution. The DE_CNT is 12 bits (valid values are 1 \
            through 2047, 0 is invalid).",
            default : bridgeTiming.getDefaultSii9022aTimingParams().deCnt,
            displayFormat: "dec",
        },
        {
            name : "deLine",
            displayName : "DE_LIN",
            longDescription : "Define the height of the active display. The unit of\
            measure is lines (HSYNC pulses). This should be set to the\
            desired vertical resolution. The DE_LIN is 11 bits (valid values \
            are 1 through 2047, 0 is invalid).",
            default : bridgeTiming.getDefaultSii9022aTimingParams().deLine,
            displayFormat: "dec",
        },
    ],
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
};

function validate(inst, report) {

    common.validate.checkNumberRange(inst, report, "hBitToHSync", 1, 1023, "dec");
    common.validate.checkNumberRange(inst, report, "field2Offset", 0, 4095, "dec");
    common.validate.checkNumberRange(inst, report, "hWidth", 1, 1023, "dec");
    common.validate.checkNumberRange(inst, report, "vBitToVSync", 1, 63, "dec");
    common.validate.checkNumberRange(inst, report, "vWidth", 1, 63, "dec");
    common.validate.checkNumberRange(inst, report, "deDelay", 1, 1023, "dec");
    common.validate.checkNumberRange(inst, report, "deTop", 1, 127, "dec");
    common.validate.checkNumberRange(inst, report, "deCnt", 1, 2047, "dec");
    common.validate.checkNumberRange(inst, report, "deLine", 1, 2047, "dec");
}

exports = bridge_sii9022a_module;
