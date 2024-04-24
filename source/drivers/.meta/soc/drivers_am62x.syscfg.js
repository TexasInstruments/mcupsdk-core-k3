
let common = system.getScript("/common");

const driverVer = {
    "epwm": {
        version: "v0",
    },
    "gpio":{
        version:"v0",
    },
    "i2c": {
        version: "v0",
    },
    "ipc": {
        version: "v0",
    },
    "mcan": {
        version: "v0",
    },
    "mcasp": {
        version: "v1",
    },
    "mcu_bist": {
        version: "v0",
    },
    "bootloader": {
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
    "mmcsd": {
        version: "v1",
    },
    "ddr": {
        version: "v0",
    },
    "gtc": {
        version: "v0",
    },
    "ospi": {
        version: "v0",
    },
    "uart": {
        version: "v0",
    },
    "mcspi": {
        version: "v0",
    },
    "udma": {
        version: "v0",
    },
    "dss": {
        version: "v0",
    },
    "watchdog": {
        version: "v0",
    },
};

const topModules_wkup = [
    "/drivers/mcu_bist/mcu_bist",
    "/drivers/gpio/gpio",
    "/drivers/bootloader/bootloader",
    "/drivers/ddr/ddr",
    "/drivers/dss/dss",
    "/drivers/mmcsd/mmcsd",
    "/drivers/gtc/gtc",
    "/drivers/gpmc/gpmc",
    "/drivers/ospi/ospi",
    "/drivers/i2c/i2c",
    "/drivers/uart/uart",
    "/drivers/ipc/ipc",
    "/drivers/udma/udma",
    "/drivers/mcspi/mcspi",
    "/drivers/mcan/mcan",
];

const topModules_mcu = [
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcan/mcan",
    "/drivers/uart/uart",
    "/drivers/mcspi/mcspi",
];

const topModules_a53 = [
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcan/mcan",
    "/drivers/mcasp/mcasp",
    "/drivers/mcspi/mcspi",
    "/drivers/mmcsd/mmcsd",
    "/drivers/ospi/ospi",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
    "/drivers/watchdog/watchdog",
];

function getCpuID() {
    let corename_map = {
        "m4fss0-0" : "CSL_CORE_ID_M4FSS0_0",
        "r5fss0-0" : "CSL_CORE_ID_R5FSS0_0",
        "a53ss0-0" : "CSL_CORE_ID_A53SS0_0",
        "a53ss0-1" : "CSL_CORE_ID_A53SS0_1",
        "a53ss1-0" : "CSL_CORE_ID_A53SS1_0",
        "a53ss1-1" : "CSL_CORE_ID_A53SS1_1",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {

        let topModules = topModules_wkup;

        if(common.getSelfSysCfgCoreName().includes("m4f")) {
            topModules = topModules_mcu;
        }
        if(common.getSelfSysCfgCoreName().includes("r5f")) {
            topModules = topModules_wkup;
        }
        if(common.getSelfSysCfgCoreName().includes("a53")) {
            topModules = topModules_a53;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};
