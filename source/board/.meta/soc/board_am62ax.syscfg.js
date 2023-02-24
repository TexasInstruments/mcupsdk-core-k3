
let common = system.getScript("/common");

const driverVer = {
    "flash": {
        version: "v0",
    },
};

const topModules_mcu_r5 = [
    "/board/led/led",
];
const topModules_dm_r5 = [
    "/board/flash/flash",
];

exports = {
    getTopModules: function() {
        if (common.getSelfSysCfgCoreName().match(/mcu*/))
        {
            return topModules_mcu_r5;
        }
        return topModules_dm_r5;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
};