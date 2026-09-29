

let common = system.getScript("/common");


let config = [
    {
        name: "wkup_r5fss0_0",
        displayName: "WKUP-R5FSS0 Core 0",
    },
    {
        name: "r5fss0_0",
        displayName: "R5FSS0 Core 0",
    },
    {
        name: "r5fss0_1",
        displayName: "R5FSS0 Core 1",
    },
    {
        name: "r5fss1_0",
        displayName: "R5FSS1 Core 0",
    },
    {
        name: "r5fss1_1",
        displayName: "R5FSS1 Core 1",
    },
    {
        name: "c75ss0_0",
        displayName: "C75SS0 Core 0",
    },
    {
        name: "c75ss1_0",
        displayName: "C75SS0 Core 1",
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

    return configurables;
}

function getSelfIpcCoreName()
{
    let cpuName = common.getSelfSysCfgCoreName();

    switch(cpuName) {
        default:
        case "r5fss0-0":
            return "r5fss0_0";
        case "r5fss0-1":
            return "r5fss0_1";
        case "r5fss1-0":
            return "r5fss1_0";
        case "r5fss1-1":
            return "r5fss1_1";
        case "c75ss0-0":
            return "c75ss0_0";
        case "c75ss1-0":
            return "c75ss1_0";
        case "wkup-r5fss0-0":
            return "wkup_r5fss0_0";
        }
}

function getSysCfgCoreName(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "r5fss0-0":
            return "r5fss0_0";
        case "r5fss0-1":
            return "r5fss0_1";
        case "r5fss1-0":
            return "r5fss1_0";
        case "r5fss1-1":
            return "r5fss1_1";
        case "c75ss0-0":
            return "c75ss0_0";
        case "c75ss1-0":
            return "c75ss1_0";
        case "wkup-r5fss0-0":
            return "wkup_r5fss0_0";
    }
}

function getIPCCoreID(ipcCoreName)
{
    switch(ipcCoreName) {
        default:
        case "wkup_r5fss0_0":
            return 0;
        case "r5fss0_0":
            return 1;
        case "r5fss0_1":
            return 2;
        case "r5fss1_0":
            return 3;
        case "r5fss1_1":
            return 4;
        case "c75ss0_0":
            return 5;
        case "c75ss1_0":
            return 6;
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