
let common = system.getScript("/common");

const driverVer = {
    "flash": {
        version: "v0",
    },
};

const topModules_mcu_m4 = [
    "/board/led/led",
];

const topModules_dm_r5 = [
    "/board/flash/flash",
    "/board/led/led",
];

const topModules = [
];

exports = {
    getTopModules: function() {
        if (common.getSelfSysCfgCoreName().match(/m4f*/))
        {
            return topModules_mcu_m4;
        }
        return topModules_dm_r5;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
};