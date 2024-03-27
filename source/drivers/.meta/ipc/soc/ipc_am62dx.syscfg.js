

let common = system.getScript("/common");


let config = [
    {
        name: "a53ss0_0",
        displayName: "A53SS0 Core 0",
    },
    {
        name: "r5fss0_0",
        displayName: "R5FSS0 Core 0",
    },
    {
        name: "c75ss0_0",
        displayName: "C75SS0 Core 0",
    },
    {
        name: "mcu_r5fss0_0",
        displayName: "MCU R5FSS0 Core 0",
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
        case "mcu-r5fss0-0":
            return "mcu_r5fss0_0";
        case "r5fss0-0":
            return "r5fss0_0";
        case "a53ss0-0":
            return "a53ss0_0";
        case "c75ss0-0":
            return "c75ss0_0";
    }
}

function getSysCfgCoreName(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "mcu_r5fss0_0":
            return "mcu-r5fss0-0";
        case "r5fss0_0":
            return "r5fss0-0";
        case "a53ss0_0":
            return "a53ss0-0";
        case "c75ss0_0":
            return "c75ss0-0";
    }
}

function getIPCCoreID(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "a53ss0_0":
            return 0;
        case "r5fss0_0":
            return 1;
        case "c75ss0_0":
            return 2;
        case "mcu_r5fss0_0":
            return 3;
    }
}

function getMaxVringSize()
{
    /* The limit is determined by space set aside in OCRAM, but keep a reasonable default
     */
    return (512*256*5*4*3*2);
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
    getIPCCoreID
};
