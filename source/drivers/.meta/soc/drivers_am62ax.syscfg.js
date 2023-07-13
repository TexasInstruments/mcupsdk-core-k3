
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
    "mcu_bist": {
        version: "v0",
    },
    "sciclient": {
        version: "v0",
    },
    "bootloader": {
        version: "v0",
    },
    "mmcsd": {
        version: "v1",
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
};

const topModules_wkup = [
    "/drivers/mcu_bist/mcu_bist",
    "/drivers/gpio/gpio",
    "/drivers/bootloader/bootloader",
    "/drivers/ddr/ddr",
    "/drivers/mmcsd/mmcsd",
    "/drivers/gtc/gtc",
    "/drivers/ospi/ospi",
    "/drivers/mcasp/mcasp",
    "/drivers/uart/uart",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
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

const topModules_c75 = [
    "/drivers/i2c/i2c",
    "/drivers/mcasp/mcasp",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
    "/drivers/ipc/ipc",
];

const topModules_a53 = [
    "/drivers/gpio/gpio",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
    "/drivers/ipc/ipc",
    "/drivers/i2c/i2c",
];

function getCpuID() {
    let corename_map = {
        "mcu-r5fss0-0" : "CSL_CORE_ID_MCU_R5FSS0_0",
        "r5fss0-0" : "CSL_CORE_ID_R5FSS0_0",
        "a53ss0-0" : "CSL_CORE_ID_A53SS0_0",
        "a53ss0-1" : "CSL_CORE_ID_A53SS0_1",
        "a53ss1-0" : "CSL_CORE_ID_A53SS1_0",
        "a53ss1-1" : "CSL_CORE_ID_A53SS1_1",
        "c75ss0-0" : "CSL_CORE_ID_C75SS0_0",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {

        let topModules = topModules_wkup;

        if(common.getSelfSysCfgCoreName().includes("mcu-r5fss0-0")) {
            topModules = topModules_mcu;
        }
        else if(common.getSelfSysCfgCoreName().includes("r5f")) {
            topModules = topModules_wkup;
        }
        else if(common.getSelfSysCfgCoreName().includes("c75ss0-0")) {
            topModules = topModules_c75;
        }
        else if(common.getSelfSysCfgCoreName().includes("a53")) {
            topModules = topModules_a53;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};
