

let common = system.getScript("/common");


let config = [
    {
        name: "mcu_r5fss0_0",
        displayName: "MCU-R5FSS0",
    },
    {
        name: "wkup_r5fss0_0",
        displayName: "WKUP-R5FSS0",
    },
    {
        name: "a53ss0_0",
        displayName: "A53SS0 Core 0",
    },
];

function getConfigurables() {

    let configurables = [];

    for( let cpuConfig of config)
    {
        if(cpuConfig.name == getSelfIpcCoreName())
        {
            /* mark self CPU with the text 'self' and make it read only */
            cpuConfig = _.cloneDeep(cpuConfig);

            cpuConfig.displayName += " (self)";
            cpuConfig.readOnly = true;
            cpuConfig.description = "CPU on which this application is running";
        }
        configurables.push(cpuConfig);
    }
    configurables.push (
        {
            name: "enableLinuxIpc",
            displayName: "Linux A53 IPC RP Message",
            longDescription: `Enable IPC communication with Linux. Only the RP Message protocol. This option generates the required resource table for interaction with Linux.`,
            default: true,
        }
    );


    /*
     * isDMR5: true when building for wkup_r5fss0_0, which runs TI Device
     * Manager firmware on AM62Px and is always-on by design.
     * All other cores participate in graceful-shutdown and LPM handshake.
     */
    let isDMR5 = (getSelfIpcCoreName() === "wkup_r5fss0_0");
    configurables.push(
        {
            name: "mcuAlwaysOn",
            displayName: "TI MCU ALWAYS ON",
            description: `DM R5 is independently always on (valid for DMR5 builds)`,
            default: isDMR5,
            hidden: false,
        },
        {
            name: "mcuGsSupport",
            displayName: "TI MCU GS SUPPORT",
            description: `Graceful shutdown protocol support`,
            default: !isDMR5,
            hidden: false,
        },
        {
            name: "mcuLpmSupport",
            displayName: "TI MCU LPM SUPPORT",
            description: `Low power mode support`,
            default: !isDMR5,
            hidden: false,
        }
    );

    return configurables;
}

function getSelfIpcCoreName()
{
    let cpuName = common.getSelfSysCfgCoreName();

    switch(cpuName) {
        default:
        case "mcu-r5fss0-0":
            return "mcu_r5fss0_0";
        case "wkup-r5fss0-0":
            return "wkup_r5fss0_0";
        case "a53ss0-0":
            return "a53ss0_0";
    }
}

function getSysCfgCoreName(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "mcu_r5fss0_0":
            return "mcu-r5fss0-0";
        case "wkup_r5fss0_0":
            return "wkup-r5fss0-0";
        case "a53ss0_0":
            return "a53ss0-0";
    }
}

function getIPCCoreID(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "mcu_r5fss0_0":
            return 0;
        case "wkup_r5fss0_0":
            return 1;
        case "a53ss0_0":
            return 2;
    }
}

function getMaxVringSize()
{
    /* The limit is determined by space set aside in OCRAM, but keep a reasonable default
     */
    return (512*256*5*4*3);
}

function getImplementationVersion()
{
    return "v0";
}

exports = {
    getConfigurables,
    getSelfIpcCoreName,
    getSysCfgCoreName,
    getMaxVringSize,
    getImplementationVersion,
    getIPCCoreID,
};
