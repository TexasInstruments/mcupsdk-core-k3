

let common = system.getScript("/common");


let config = [
    {
        name: "m4fss0_0",
        displayName: "M4FSS0",
    },
    {
        name: "r5fss0_0",
        displayName: "R5FSS0 Core 0",
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
            description: `Enable IPC with Linux. Only IPC RP Message supported`,
            default: true,
        }
    );

    return configurables;
}

function getSelfIpcCoreName()
{
    let cpuName = common.getSelfSysCfgCoreName();

    switch(cpuName) {
        default:
        case "m4fss0-0":
            return "m4fss0_0";
        case "r5fss0-0":
            return "r5fss0_0";
        case "a53ss0-0":
            return "a53ss0_0";
    }
}

function getSysCfgCoreName(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "m4fss0_0":
            return "m4fss0-0";
        case "r5fss0_0":
            return "r5fss0-0";
        case "a53ss0_0":
            return "a53ss0-0";
    }
}

function getIPCCoreID(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "m4fss0_0":
            return 0;
        case "r5fss0_0":
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
