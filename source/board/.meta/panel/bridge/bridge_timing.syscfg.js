let common = system.getScript("/common");

let sii9022a_output_format =
[
    {name : "HDMI_RGB", displayName : "HDMI RGB"},
    {name : "HDMI_YUV444", displayName : "HDMI YUV444"},
    {name : "HDMI_YUV422", displayName : "HDMI YUV422"},
    {name : "DVI_RGB", displayName : "DVI RGB"},
];

let sii9022a_resolution =
[
    {name :"1080P_60", displayName: "1080p 60Hz"},
    {name :"1080P_50", displayName: "1080p 50Hz"},
    {name :"1080P_30", displayName: "1080p 30Hz"},
    {name :"720P_60", displayName: "720p 60Hz"},
    {name :"720P_50", displayName: "720p 50Hz"}
];

let sii9022a_timing_config =
[
    {
        /* 1920x1080 60FPS progressive HD standard. */
        resolution : {name :"1080P_60", displayName: "1080p 60Hz"},
        modeCode : 16,
        pixClk   : 14850,
        vFreq    : 60,
        pixels   : 2200,
        lines    : 1125,
        hBitToHSync : 88,
        field2Offset : 0,
        hWidth : 44,
        vBitToVSync : 4,
        vWidth : 5,
        deDelay : 192,
        deTop : 41,
        deCnt : 1920,
        deLine : 1080,
    },
    {
        /* 1920x1080 50FPS progressive HD standard. */
        resolution : {name :"1080P_50", displayName: "1080p 50Hz"},
        modeCode : 16,
        pixClk   : 14850,
        vFreq    : 50,
        pixels   : 2640,
        lines    : 1125,
        hBitToHSync : 528,
        field2Offset : 0,
        hWidth : 44,
        vBitToVSync : 4,
        vWidth : 5,
        deDelay : 192,
        deTop : 41,
        deCnt : 1920,
        deLine : 1080,
    },
    {
        /* 1920x1080 30FPS progressive HD standard. */
        resolution : {name :"1080P_30", displayName: "1080p 30Hz"},
        modeCode : 34,
        pixClk   : 7425,
        vFreq    : 30,
        pixels   : 2200,
        lines    : 1125,
        hBitToHSync : 88,
        field2Offset : 0,
        hWidth : 44,
        vBitToVSync : 4,
        vWidth : 5,
        deDelay : 192,
        deTop : 41,
        deCnt : 1920,
        deLine : 1080,
    },
    {
        /* 1280x720 60FPS progressive HD standard. */
        resolution : {name :"720P_60", displayName: "720p 60Hz"},
        modeCode : 4,
        pixClk   : 7425,
        vFreq    : 60,
        pixels   : 1650,
        lines    : 750,
        hBitToHSync : 110,
        field2Offset : 0,
        hWidth : 40,
        vBitToVSync : 5,
        vWidth : 5,
        deDelay : 260,
        deTop : 25,
        deCnt : 1280,
        deLine : 720,
    },
    {
        /* 1280x720 50FPS progressive HD standard. */
        resolution : {name :"720P_50", displayName: "720p 50Hz"},
        modeCode : 19,
        pixClk   : 7425,
        vFreq    : 50,
        pixels   : 1980,
        lines    : 750,
        hBitToHSync : 440,
        field2Offset : 0,
        hWidth : 40,
        vBitToVSync : 5,
        vWidth : 5,
        deDelay : 260,
        deTop : 25,
        deCnt : 1280,
        deLine : 720,
    },
];

function getSii9022aTimingParams()
{
    return sii9022a_timing_config;
}

function getDefaultSii9022aTimingParams()
{
    return sii9022a_timing_config[0];
}

function getDefaultOutputFormat()
{
    return sii9022a_output_format[0];
}

function getOutputFormat()
{
    return sii9022a_output_format;
}

function getBridgeResolution()
{
    return sii9022a_resolution;
}

exports = {
    getSii9022aTimingParams,
    getDefaultSii9022aTimingParams,
    getDefaultOutputFormat,
    getOutputFormat,
    getBridgeResolution
};