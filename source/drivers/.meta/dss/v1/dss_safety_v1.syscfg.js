let common = system.getScript("/common");
let soc = system.getScript(`/drivers/soc/drivers_${common.getSocName()}`);
let dssScript = system.getScript(`/drivers/dss/${soc.getDriverVer("dss")}/dss_${soc.getDriverVer("dss")}`);

function getInstanceConfig(moduleInstance) {
    return {
        ...moduleInstance,
    };
};

let dss_vp_safety_module = {
    displayName: "VP Safety Check Region",
    longDescription: `
These are VP safety region configuration.
There is a max of four regions that can be configured for VP to perform safety checks.
It supports either Freeze frame or MISR safety check.

The safety region in the video pipeline captures data only if the embedded alpha
data is not equal to 0 (that is, non-transparent pixels). So the region for video
pipeline must lie within the input frame region. The safety regions in the
display video port output captures all active video pixels within the region
boundary.
    `,
    alwaysShowLongDescription: true,

    config: [
        {
            name: "safetyCheckMode",
            displayName: "Safety Check Mode",
            description: "Safety check mode : Freeze frame or MISR check",
            default : "FRAME_FREEZE_DETECT",
            options:  [
                { name : "FRAME_FREEZE_DETECT" , displayName : "Freeze Frame Detect" },
                { name : "DATA_INTEGRITY", displayName: "Data Integrity Check" }
            ],
            onChange: function(inst, ui){
                if(inst.safetyCheckMode == "FRAME_FREEZE_DETECT")
                {
                    ui.referenceSign.hidden = true;
                    ui.thresholdValue.hidden = false;
                }
                else
                {
                    ui.referenceSign.hidden = false;
                    ui.thresholdValue.hidden = true;
                }
            }
        },
        {
            name : "seedSelectEnable",
            displayName : "Seed Select Enable",
            description: "This value needs to be set if you alter seed value for a particular region.",
            default : "false",
            options: [
                { name: "false", displayName: "Disable" },
                { name: "true", displayName: "Enable" }
            ]
        },
        {
            name : "safetySignSeedVal",
            displayName : "Safety Sign Seed Value",
            longDescription: "Safety Signature Seed Value, only one non-zero value is possible in a\n" + "\n" +
                "particular context. In case user passes multiple non-zero values for different regions, \n"  + "\n" +
                "previous value is overwritten.  Note that a same seed must be used to compare signatures\n " + "\n" +
                "between two frames. If different than the default seed value is desired, then a seed select\n" + "\n" +
                "enable parameter must be set.",
            default: 0xFFFFFFFF,
            displayFormat: "hex",
        },
        {
            name : "referenceSign",
            displayName : "Reference Signature",
            displayFormat : "hex",
            default : 0x00000000,
            hidden : true,
        },
        {
            name : "thresholdValue",
            displayName: "Threshold Value Freeze Frame",
            description: "Number for frames to skip before freeze frame detection.",
            displayFormat: "dec",
            default : 10,
            hidden : false,
            range: [0,255]
        },
        {
            name : "skipFrames",
            displayName: "Skip Frames",
            description: "Indicates which frames to be skipped while doing safety checks",
            default: "FRAME_SKIP_NO",
            options: [
                { name :"FRAME_SKIP_NO", displayName: "Zero Frames Skip"},
                { name : "FRAME_SKIP_ODD", displayName:"Odd Frames Skip"},
                { name : "FRAME_SKIP_EVEN", displayName:"Even Frames Skip"}
            ]
        },
        {
            name: "regionXstart",
            displayName : "X Position Safety Region",
            description: "Horizontal position of safety region in pixels",
            default: 0,
            displayFormat: "dec",
        },
        {
            name: "regionYstart",
            displayName : "Y Position Safety Region",
            description: "Vertical position of safety region in pixels",
            default: 0,
            displayFormat: "dec"
        },
        {
            name : "widthSafetyRegion",
            displayName : "Width Safety Region",
            description : "Width of safety region in pixels",
            default: 240,
            displayFormat : "dec"
        },
        {
            name : "heightSafetyRegion",
            displayName : "Height Safety Region",
            description : "Height of safety region in pixels",
            default: 120,
            displayFormat : "dec"
        },
        {
            name : "panelWidth",
            default : 0,
            hidden: true,
        },
        {
            name : "panelHeight",
            default : 0,
            hidden : true,
        }

    ],
    validate: validate,
    getInstanceConfig,
};

/*
 *  ======== validate ========
 */
function validate(instance, report) {

    common.validate.checkNumberRange(instance, report, "widthSafetyRegion", 1, 3840, "dec");
    common.validate.checkNumberRange(instance, report, "heightSafetyRegion", 1, 3840, "dec");

    if(instance.widthSafetyRegion > instance.panelWidth){
        report.logError("Safety region width is more than the panel width in pixels.", instance, "widthSafetyRegion");
    }
    if(instance.heightSafetyRegion > instance.panelHeight){
        report.logError("Safety region height is more than the panel height in pixels.", instance, "heightSafetyRegion");
    }

}

exports = dss_vp_safety_module;
