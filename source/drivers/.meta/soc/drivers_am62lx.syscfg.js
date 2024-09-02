
let common = system.getScript("/common");

const driverVer = {
    "gpio":{
        version:"v0",
    },
    "i2c": {
        version: "v0",
    },
    "sciclient": {
        version: "v0",
    },
    "gpio": {
        version: "v0",
    },
    "gpmc": {
        version: "v0",
    },
    "ospi": {
        version: "v0",
    },
    "uart": {
        version: "v0",
    },
    "watchdog": {
        version: "v0",
    },
};

const topModules_a53 = [
    "/drivers/gpio/gpio",
    "/drivers/gpmc/gpmc",
    "/drivers/i2c/i2c",
    "/drivers/ospi/ospi",
    "/drivers/uart/uart",
    "/drivers/watchdog/watchdog",
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