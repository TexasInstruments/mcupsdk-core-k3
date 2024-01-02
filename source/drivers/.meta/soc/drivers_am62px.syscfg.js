
let common = system.getScript("/common");

const driverVer = {
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
    "mcspi": {
        version: "v0",
    },
    "sciclient": {
        version: "v0",
    },
    "bootloader": {
        version: "v0",
    },
    "mmcsd": {
        version: "v0",
    },
    "ddr": {
        version: "v1",
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
    "udma": {
        version: "v0",
    },
    "ddr": {
        version: "v1",
    },
    "gtc": {
        version: "v0",
    },
    "dss": {
        version: "v0",
    },
};

const topModules_wkup = [
    "/drivers/bootloader/bootloader",
    "/drivers/ddr/ddr",
    "/drivers/dss/dss",
    "/drivers/gpio/gpio",
    "/drivers/gtc/gtc",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcan/mcan",
    "/drivers/mcasp/mcasp",
    "/drivers/mcspi/mcspi",
    "/drivers/mmcsd/mmcsd",
    "/drivers/ospi/ospi",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
];

const topModules_mcu = [
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcan/mcan",
    "/drivers/mcspi/mcspi",
    "/drivers/uart/uart",
];

function getCpuID() {
    let corename_map = {
        "mcu-r5fss0-0" : "CSL_CORE_ID_MCU_R5FSS0_0",
        "wkup-r5fss0-0" : "CSL_CORE_ID_WKUP_R5FSS0_0",
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

        if(common.getSelfSysCfgCoreName().includes("mcu-r5fss0-0")) {
            topModules = topModules_mcu;
        }
        else if(common.getSelfSysCfgCoreName().includes("wkup-r5fss0-0")) {
            topModules = topModules_wkup;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};
