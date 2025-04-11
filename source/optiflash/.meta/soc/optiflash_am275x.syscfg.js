
let common = system.getScript("/common");

const topModules_main = [
    "/optiflash/flc/flc",
    "/optiflash/rl2/rl2",
];

const driverVersion = {
    'flc':
    {
        version: 'v0'
    },
    'rl2':
    {
        version: 'v0'
    }
};


exports = {
    getTopModules: function() {
        return common.getSelfSysCfgCoreName().includes("r5f") ? topModules_main:[];
    },
    getDriverVer: function (driverName)
    {
        return driverVersion[driverName].version;
    }
};
