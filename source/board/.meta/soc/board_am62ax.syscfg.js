
let common = system.getScript("/common");

const driverVer = {
    "flash": {
        version: "v0",
    },
    "serialFlash": {
        version: "v0",
    },
};

const topModules_mcu_r5 = [
    "/board/led/led",
    "/board/eeprom/eeprom",
];
const topModules_dm_r5 = [
    "/board/flash/flash",
    "/board/eeprom/eeprom",
];
const topModules_a53 = [
    "/board/led/led",
    "/board/flash/flash",
    "/board/eeprom/eeprom",
];

const topModules_c75x = [
];

exports = {
    getTopModules: function() {
        if (common.getSelfSysCfgCoreName().match(/mcu*/))
        {
            return topModules_mcu_r5;
        }
        else if(common.getSelfSysCfgCoreName().match(/a53*/))
        {
            return topModules_a53;
        }
        else if (common.getSelfSysCfgCoreName().match(/c75*/))
        {
            return topModules_c75x;
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
