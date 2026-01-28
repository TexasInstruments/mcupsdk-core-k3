let common = system.getScript("/common");
let module = system.modules['/drivers/aasrc/aasrc'];

let aasrc_ch_module_name = "/drivers/aasrc/v0/aasrc_v0_channel";

let aasrc_ch_module = {
    displayName: "AASRC Channel Configuration",
    defaultInstanceName: "CONFIG_AASRC_CH",
    config: [
        /* Channel attributes */
        {
            name: "channelType",
            displayName: "Channel Type",
            default: "MONO",
            options: [
                {
                    name: "MONO",
                    displayName: "MONO"
                },
                {
                    name: "STEREO",
                    displayName: "STEREO"
                },
                {
                    name: "GROUP",
                    displayName: "GROUP"
                },
            ],

            onChange: function (inst, ui) {
                if (inst.channelType === "MONO") {
                    inst.channelCount = "1";
                    ui.channelCount.readOnly = true;
                } else if (inst.channelType === "STEREO") {
                    inst.channelCount = "2";
                    ui.channelCount.readOnly = true;
                } else if (inst.channelType === "GROUP") {
                    inst.channelCount = "2";
                    ui.channelCount.readOnly = false;
                }
            },
            description: "Channel Types",
            longDescription:
`MONO - Mono channel can take only single data stream \n
STEREO - Stereo channel can process two data stream in interleaved data format \n
GROUP - Group channel type can process multiple data stream (2-16) which are in interleaved format`,
        },
        {
            name: "channelCount",
            displayName: "Channel Count",
            default: "1",
            readOnly: true,
            options: [
                { name: "1" },
                { name: "2" },
                { name: "3" },
                { name: "4" },
                { name: "5" },
                { name: "6" },
                { name: "7" },
                { name: "8" },
                { name: "9" },
                { name: "10" },
                { name: "11" },
                { name: "12" },
                { name: "13" },
                { name: "14" },
                { name: "15" },
                { name: "16" },
            ],
            description: "Number of mono channels (1-16) included in the channel type",
            longDescription:
`MONO - Mono channel can take only one channel count \n
STEREO - Stereo channel can take only two channel count \n
GROUP - Group channel type can from 2 to 16 channel count`,
        },
        {
            name: "inClockZone",
            displayName: "Input Clock Zone",
            default: "0",
            options: [
                { name: "0", displayName: "Clock Zone 0" },
                { name: "1", displayName: "Clock Zone 1" },
                { name: "2", displayName: "Clock Zone 2" },
                { name: "3", displayName: "Clock Zone 3" },
            ],
            description: "Input clock zone to be used for the channel",
            longDescription:
`Total four clock zone are avaiable for the input clock. Selected input clock zone needs to be configured in Input Clockzone configuration`,
        },
        {
            name: "outClockZone",
            displayName: "Ouput Clock Zone",
            default: "0",
            options: [
                { name: "0", displayName: "Clock Zone 0" },
                { name: "1", displayName: "Clock Zone 1" },
                { name: "2", displayName: "Clock Zone 2" },
                { name: "3", displayName: "Clock Zone 3" },
            ],
            description: "Ouput clock zone to be used for the channel",
            longDescription:
`Total four clock zone are avaiable for the output clock. Selected output clock zone needs to be configured in Output Clockzone configuration`,
        },
        {
            name: "inWordLength",
            displayName: "Input Word Length",
            default: "24",
            options: [
                { name: "24", displayName: "24 Bits"},
                { name: "20", displayName: "20 Bits" },
                { name: "18", displayName: "18 Bits" },
                { name: "16", displayName: "16 Bits" },
            ],
            description: "Word length for the SRC input data 0:24 Bits",
        },
        {
            name: "outWordLength",
            displayName: "Output Word Length",
            default: "24",
            options: [
                { name: "24", displayName: "24 Bits"},
                { name: "20", displayName: "20 Bits" },
                { name: "18", displayName: "18 Bits" },
                { name: "16", displayName: "16 Bits" },
            ],
            description: "Word length for the SRC output data 0:24 Bits",
        },
        {
            name: "inThreshold",
            displayName: "Input FIFO Threshold",
            default: "16",
            options: [
                { name: "1" },
                { name: "2" },
                { name: "3" },
                { name: "4" },
                { name: "5" },
                { name: "6" },
                { name: "7" },
                { name: "8" },
                { name: "9" },
                { name: "10" },
                { name: "11" },
                { name: "12" },
                { name: "13" },
                { name: "14" },
                { name: "15" },
                { name: "16" },
                { name: "17" },
                { name: "18" },
                { name: "19" },
                { name: "20" },
                { name: "21" },
                { name: "22" },
                { name: "23" },
                { name: "24" },
                { name: "25" },
                { name: "26" },
                { name: "27" },
                { name: "28" },
                { name: "29" },
                { name: "30" },
                { name: "31" },
                { name: "32" },
            ],
            description: "The threshold sample value for input FIFO",
            longDescription:
`Each input channel is buffered by a 32 samples FIFO. The threshold values can be programmed to a value between \n
1 and 32 samples. The threshold value is used to trigger the event when the FIFO reaches the threshold level`,
        },
        {
            name: "outThreshold",
            displayName: "Ouput FIFO Threshold",
            default: "16",
            options: [
                { name: "1" },
                { name: "2" },
                { name: "3" },
                { name: "4" },
                { name: "5" },
                { name: "6" },
                { name: "7" },
                { name: "8" },
                { name: "9" },
                { name: "10" },
                { name: "11" },
                { name: "12" },
                { name: "13" },
                { name: "14" },
                { name: "15" },
                { name: "16" },
                { name: "17" },
                { name: "18" },
                { name: "19" },
                { name: "20" },
                { name: "21" },
                { name: "22" },
                { name: "23" },
                { name: "24" },
                { name: "25" },
                { name: "26" },
                { name: "27" },
                { name: "28" },
                { name: "29" },
                { name: "30" },
                { name: "31" },
                { name: "32" },
            ],
            description: "The threshold sample value for output FIFO",
            longDescription:
`Each output channel is buffered by a 32 samples FIFO. The threshold values can be programmed to a value between \n
1 and 32 samples. The threshold value is used to trigger the event when the FIFO reaches the threshold level`,
        },
        {
            name: "txCallbackFxn",
            displayName: "Transmit Callback Function",
            default: "NULL",
            description: "Transmit Callback Function",
        },
        {
            name: "rxCallbackFxn",
            displayName: "Receive Callback Function",
            default: "NULL",
            description: "Receive Callback Function",
        },
        {
            name: "errorCallbackFxn",
            displayName: "Error Callback Function",
            default: "NULL",
            description: "Error Callback Function",
        },
        {
            name: "transmitLoopjobEnable",
            displayName: "Transmit Loopjob Enable",
            default: true,
            readOnly: true,
            description: "Loopjob Enable for transmit",
        },
        {
            name: "txLoopjobBuf",
            displayName: "Transmit Loopjob Buffer",
            default: "gTxLoopjobBuf0",
            description: "Transmit Loopjob Buffer",
        },
        {
            name: "txLoopjobBufLength",
            displayName: "Transmit Loopjob Buffer Sample Count",
            default: 256,
            displayFormat: "dec",
            description: "Transmit Loopjob Buffer Length in 32 Bit Samples",
            longDescription:
`Note: Loopjob length must be same as the transmit transactions submitted by the application for this channel`,
        },
        {
            name: "receiveLoopjobEnable",
            displayName: "Receive Loopjob Enable",
            default: true,
            readOnly: true,
            description: "Loopjob Enable for Receive",
        },
        {
            name: "rxLoopjobBuf",
            displayName: "Receive Loopjob Buffer",
            default: "gRxLoopjobBuf0",
            description: "Receive Loopjob Buffer",
        },
        {
            name: "rxLoopjobBufLength",
            displayName: "Receive Loopjob Buffer Sample Count",
            default: 256,
            displayFormat: "dec",
            description: "Receive Loopjob Buffer Length in 32 Bit Samples",
            longDescription:
`Note: Loopjob length must be same as the receive transactions submitted by the application for this channel`,
        },
        /* Advanced parameters */
        {
            name: "advanced",
            displayName: "Show Advanced Channel Config",
            default: false,
            onChange: function(inst, ui) {
                if (inst.advanced == true) {
                    ui.dither.hidden = false;
                    ui.mute.hidden = false;
                    ui.directDownSample.hidden = false;
                    ui.attenuation.hidden = false;
                    ui.groupDelay.hidden = false;
                    ui.deEmphasis.hidden = false;
                }
                else {
                    ui.dither.hidden = true;
                    ui.mute.hidden = true;
                    ui.directDownSample.hidden = true;
                    ui.attenuation.hidden = true;
                    ui.groupDelay.hidden = true;
                    ui.deEmphasis.hidden = true;
                }
            },
        },
        {
            name: "dither",
            displayName: "Dither",
            default: false,
            hidden: true,
            description: "Enables the SRC filers dithering ",
        },
        {
            name: "deEmphasis",
            displayName: "De-Emphasis Filter",
            default: "Disabled",
            hidden: true,
            options: [
                {
                    name: "Disabled",
                },
                {
                    name: "Mode 1",
                },
                {
                    name: "Mode 2",
                },
                {
                    name: "Mode 3",
                },
            ],
            description: "Enables the De-emphasis filer ",
            longDescription:
`The de-emphasis filter is intended to process 50/15s pre-emphasized audio material at the following input sampling rates \n
Mode 1: De-Emphasis Enabled for fS = 48kHz \n
Mode 2: De-Emphasis Enabled for fS = 44.1kHz \n
Mode 3: De-Emphasis Enabled for fS = 32kHz`,
        },
        {
            name: "mute",
            displayName: "Mute Channel",
            default: false,
            hidden: true,
            description: "SRC ouput soft mute function, where output data set to all zeros",
        },
        {
            name: "directDownSample",
            displayName: "Direct Down Sample",
            default: false,
            hidden: true,
            description: "Selects the mode of decimation function",
        },
        {
            name: "attenuation",
            displayName: "Attenuation",
            default: 0,
            hidden: true,
            description: "SRC digital ouput attenuation for the Stream Output Attenuation",
        },
        {
            name: "groupDelay",
            displayName: "Group Delay",
            default: "64",
            hidden: true,
            options: [
                {
                    name: "64",
                },
                {
                    name: "32",
                },
                {
                    name: "16",
                },
                {
                    name: "8",
                },
            ],
            description: "Select the interpolation filter group delay by configuring the number of samples which are pre-buffered prior to resampler function",
        },
    ],
    validate : validate,
};

/*
 *  ======== validate ========
 */
function validate(inst, report) {

    let parentInstance = inst.$ownedBy;

    common.validate.checkNumberRange(inst, report, "attenuation", 0, 255, "dec");

    /* Limit the channel count for MONO and STEREO Type*/
    if (inst.channelType === "MONO") {
        if (inst.channelCount !== "1") {
            report.logError(
                "Channel count must be exactly 1 for MONO channel type.",
                inst,
                "channelCount"
            );
        }
    }
    else if (inst.channelType === "STEREO") {
        if (inst.channelCount !== "2") {
            report.logError(
                "Channel count must be exactly 2 for STEREO channel type.",
                inst,
                "channelCount"
            );
        }
    }
    else if (inst.channelType === "GROUP") {
        if (parseInt(inst.channelCount, 10) < 2) {
            report.logError(
                "Channel count must be greater than or equal to 2 for GROUP channel type.",
                inst,
                "channelCount"
            );
        }
    }
    /* Validate total channel count across all channels under the parent instance falls
     * under total available channels per instance */

    let totalChannelCount = 0;
    let childInstances = parentInstance.aasrcChannel; /* Get all channel instances under the parent */
    let currChCount = 0;

    if (childInstances) {
        childInstances.forEach(channel => {
            currChCount = parseInt(channel.channelCount, 10);
            if(currChCount % 2 != 0)
            {
                currChCount += 1;
            }
            totalChannelCount += currChCount; /* Sum up the channel counts */
        });

        if (totalChannelCount > 16) {
            report.logError(
                `Total channel count across all channels exceeds the limit of 16. Current total: ${totalChannelCount}.`,
                inst,
                "channelCount"
            );
        }
    }

    /* Validate clock zones config are available */
    if(inst.inClockZone > parentInstance.aasrcReceiveClockZone.length - 1)
    {
        report.logError(
            `Input Clock Zone ${inst.inClockZone} is not configured in the Receive Clock configuration`,
            inst,
            "inClockZone"
        );
    }

    if(inst.outClockZone > parentInstance.aasrcTransmitClockZone.length -1 )
    {
        report.logError(
            `Output Clock Zone ${inst.outClockZone} is not configured in the Transmit Clock configuration`,
            inst,
            "outClockZone"
        );
    }

    /* Validate callback are not NULL */
     if((inst.txCallbackFxn == "NULL") ||
        (inst.txCallbackFxn == "")) {
            report.logError("Callback function MUST be provided", inst, "txCallbackFxn");
    }

    if((inst.rxCallbackFxn == "NULL") ||
        (inst.rxCallbackFxn == "")) {
            report.logError("Callback function MUST be provided", inst, "rxCallbackFxn");
    }

}

exports = aasrc_ch_module;
