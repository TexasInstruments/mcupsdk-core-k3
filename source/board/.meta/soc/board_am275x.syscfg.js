
let common = system.getScript("/common");

const driverVer = {
    "ethphy": {
        version: "am275x",
    },
    "flash": {
        version: "v0",
    },
    "serialFlash": {
        version: "v0",
    },
    "hyperRam": {
        version: "v0",
    },
};

const topModules_r5 = [
    "/board/eeprom/eeprom",
    "board/ethphy_cpsw_icssg/ethphy_cpsw_icssg",
    "/board/flash/flash",
    "/board/hyperRam/hyperRam",
    "/board/led/led",
];
const topModules_wkup_r5 = [
    "/board/flash/flash",
    "/board/hyperRam/hyperRam",
];

const topModules_c75x = [
    "/board/flash/flash",
    "/board/hyperRam/hyperRam",
    "/board/led/led",
];

exports = {
    getTopModules: function() {
    if (common.getSelfSysCfgCoreName().match(/wkup-r5f*/))
        {
            return topModules_wkup_r5;
        }
        else if (common.getSelfSysCfgCoreName().match(/c75*/))
        {
            return topModules_c75x;
        }

        return topModules_r5;
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
