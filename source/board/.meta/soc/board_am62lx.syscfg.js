
let common = system.getScript("/common");

const driverVer = {
    "ethphy": {
        version: "v1",
    },
    "flash": {
        version: "v0",
    },
    "serialFlash": {
        version: "v0",
    },
    "panel" : {
        version: "v0",
    },
    "parallelFlash": {
        version: "v0",
    }
};

const topModules_a53 = [
    "/board/eeprom/eeprom",
    "board/flash/flash",
    "/board/led/led",
    "/board/panel/panel",
    "/board/ethphy_cpsw_icssg/ethphy_cpsw_icssg",
];

exports = {
    getTopModules: function() {

        return topModules_a53;
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