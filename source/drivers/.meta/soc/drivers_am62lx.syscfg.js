
let common = system.getScript("/common");

const driverVer = {
    "ecap": {
        version: "v0",
    },
    "epwm": {
        version: "v0",
    },
    "eqep": {
        version: "v0",
    },
    "gpio":{
        version:"v0_1",
    },
    "i2c": {
        version: "v0",
    },
    "mcan": {
        version: "v0",
    },
    "mcspi": {
        version: "v0",
    },
    "mmcsd": {
        version: "v1",
    },
    "ospi": {
        version: "v0",
    },
    "sciclient": {
        version: "v0",
    },
    "uart": {
        version: "v0",
    },
};

const topModules_a53 = [
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/eqep/eqep",
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/mcan/mcan",
    "/drivers/mcspi/mcspi",
    "/drivers/mmcsd/mmcsd",
    "/drivers/ospi/ospi",
    "/drivers/uart/uart",
];

function getCpuID() {
    let corename_map = {
        "a53ss0-0" : "CSL_CORE_ID_A53SS0_0",
        "a53ss0-1" : "CSL_CORE_ID_A53SS0_1",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {
        return topModules_a53;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};