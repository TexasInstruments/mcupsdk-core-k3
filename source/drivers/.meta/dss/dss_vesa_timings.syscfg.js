let common = system.getScript("/common");

let vesa_resolution =
[
    {name :"1080P_60", displayName: "1080p 60Hz"},
    {name :"1080P_50", displayName: "1080p 50Hz"},
    {name :"1080P_30", displayName: "1080p 30Hz"},
    {name :"720P_60", displayName: "720p 60Hz"},
    {name :"720P_50", displayName: "720p 50Hz"}
];

let vesa_timings_config =
[
    {
        /* 1920x1080 60FPS progressive HD standard. */
        resolution : {name :"1080P_60", displayName: "1080p 60Hz"},
        pixelClock :  148500000,
        width: 1920,
        height: 1080,
        horizontalFrontPorch: 88,
        horizontalBackPorch: 148,
        verticalFrontPorch: 4,
        verticalBackPorch: 36,
        hsycnLength: 44,
        vsyncLength: 5
    },
    {
        /* 1920x1080 50FPS progressive HD standard. */
        resolution : {name :"1080P_50", displayName: "1080p 50Hz"},
        pixelClock :  148500000,
        width: 1920,
        height: 1080,
        horizontalFrontPorch: 528,
        horizontalBackPorch: 148,
        verticalFrontPorch: 4,
        verticalBackPorch: 36,
        hsycnLength: 44,
        vsyncLength: 5
    },
    {
        /* 1920x1080 30FPS progressive HD standard. */
        resolution : {name :"1080P_30", displayName: "1080p 30Hz"},
        pixelClock :  74250000,
        width: 1920,
        height: 1080,
        horizontalFrontPorch: 88,
        horizontalBackPorch: 148,
        verticalFrontPorch: 4,
        verticalBackPorch: 36,
        hsycnLength: 44,
        vsyncLength: 5
    },
    {
        /* 1280x720 60FPS progressive HD standard. */
        resolution : {name :"720P_60", displayName: "720p 60Hz"},
        pixelClock :  74250000,
        width: 1280,
        height: 720,
        horizontalFrontPorch: 110,
        horizontalBackPorch: 220,
        verticalFrontPorch: 5,
        verticalBackPorch: 20,
        hsycnLength: 40,
        vsyncLength: 5
    },
    {
        /* 1280x720 50FPS progressive HD standard. */
        resolution : {name :"720P_50", displayName: "720p 50Hz"},
        pixelClock :  74250000,
        width: 1280,
        height: 720,
        horizontalFrontPorch: 440,
        horizontalBackPorch: 220,
        verticalFrontPorch: 5,
        verticalBackPorch: 20,
        hsycnLength: 40,
        vsyncLength: 5
    },
];

function getDefaultVesaTiming()
{
    return vesa_timings_config[0];
}

function getVesaTiming()
{
    return vesa_timings_config;
}

function getVesaResolution()
{
    return vesa_resolution;
}

exports = {
    getDefaultVesaTiming,
    getVesaTiming,
    getVesaResolution
};