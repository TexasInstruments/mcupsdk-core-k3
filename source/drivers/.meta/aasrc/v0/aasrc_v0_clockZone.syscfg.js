
let common = system.getScript("/common");
let module = system.modules['/drivers/aasrc/aasrc'];
let soc = system.getScript(`/drivers/aasrc/soc/aasrc_${common.getSocName()}`);

let aasrc_clockZone_module_name = "/drivers/aasrc/v0/aasrc_v0_clockZone";

let aasrc_clockZone_module = {
    displayName: "AASRC Clock Zone Configuration",
    defaultInstanceName: "CONFIG_AASRC_CLOCKZONE",
    config: [
        /* Channel attributes */
        {
            name: "clkZoneDiv",
            displayName: "Clock Zone Division",
            default: 1,
            description: "Clock Zone Division Value",
        },
        {
            name: "isClkZoneDivEnable",
            displayName: "Clock Zone Division Enable",
            default: false,
            description: "Clock Zone divider enable",
            },
        {
            name: "syncPin",
            displayName: "Sync Pin",
            default: "0",
            options: [
                {
                    name: "0",
                },
                {
                    name: "1",
                },
                {
                    name: "2",
                },
                {
                    name: "3",
                },
            ],
            description: "Sync Pin to be routed to the clock zone for clock output",
        },
        {
            name: "extClkSrc",
            displayName: "External Clock Source",
            default: "MAIN_PLL4_HSDIV3_CLKOUT",
            options: function(inst) {
                let parentInstance = inst.$ownedBy;
                if (parentInstance && parentInstance.aasrcReceiveClockZone && parentInstance.aasrcReceiveClockZone.indexOf(inst) >= 0) {
                    return soc.rxExtClkSrcOptions;
                } else if (parentInstance && parentInstance.aasrcTransmitClockZone && parentInstance.aasrcTransmitClockZone.indexOf(inst) >= 0) {
                    return soc.txExtClkSrcOptions;
                }
            },
            description: "External clock source to be routed to the clock zone",
        },
        {
            name: "overrideClkSettle",
            displayName: "Clock Settle Override",
            default: false,
            description: "Override the settle of clock zone clock recovery loop",
        },
    ],
    validate : validate,
};

/*
 *  ======== validate ========
 */
function validate(inst, report, ui) {
    let parentInstance = inst.$ownedBy;

    /* Get the array of aasrcReceiveClockZone instances */
    let receiveClockZones = parentInstance.aasrcReceiveClockZone;
    let transmitClockZones = parentInstance.aasrcTransmitClockZone;

    /* Find the index of the current instance */
    let rxInstanceIndex = receiveClockZones.indexOf(inst);
    let txInstanceIndex = transmitClockZones.indexOf(inst);

    if(inst.isClkZoneDivEnable)
    {
        if(rxInstanceIndex >= 2)
        {
            report.logError(
                `Clock Zone Divider not available for Clock Configuration : ${rxInstanceIndex}`,
                inst,
                "isClkZoneDivEnable"
            );
        }
        if(txInstanceIndex >= 2)
            {
                report.logError(
                    `Clock Zone Divider not available for Clock Configuration : ${txInstanceIndex}`,
                    inst,
                    "isClkZoneDivEnable"
                );
            }
    }

    /* Validate same sync pin is not modified again */
    if (rxInstanceIndex >= 0) {
        for (let i = 0; i < receiveClockZones.length; i++) {
            if (i !== rxInstanceIndex && receiveClockZones[i].syncPin === inst.syncPin) {
                report.logError(
                    `Sync Pin ${inst.syncPin} already used by Clock Configuration : ${i}`,
                    inst,
                    "syncPin"
                );
            }
        }
    }
    if (txInstanceIndex >= 0) {
        for (let i = 0; i < transmitClockZones.length; i++) {
            if (i !== txInstanceIndex && transmitClockZones[i].syncPin === inst.syncPin) {
                report.logError(
                    `Sync Pin ${inst.syncPin} already used by Clock Configuration : ${i}`,
                    inst,
                    "syncPin"
                );
            }
        }
    }
}

exports = aasrc_clockZone_module;