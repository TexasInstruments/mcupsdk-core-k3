
let common = system.getScript("/common");

const driverVer = {
    "flash": {
        version: "v0",
    },
    "serialFlash": {
        version: "v0",
    },
    "parallelFlash": {
        version: "v0",
    }
};

const topModules_mcu_m4 = [
    "/board/led/led",
];

const topModules_dm_r5 = [
    "/board/flash/flash",
    "/board/led/led",
];

const topModules_a53 = [
    "/board/eeprom/eeprom",
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
        if (common.getSelfSysCfgCoreName().match(/a53*/))
        {
            return topModules_a53;
        }
        if(common.getSelfSysCfgCoreName().match(/r5f*/))
        {
            topModules_dm_r5;
        }

        return topModules_dm_r5;
    },
    getDriverVer: function(driverName) {
            return driverVer[driverName].version;
    },
    getDriverInstanceValid: function(driverName) {
        let valid = false;
        if(driverName in driverVer)
        {
            valid = true;
        }
        return valid;
    }
};