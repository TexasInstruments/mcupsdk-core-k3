
let common = system.getScript("/common");

const driverVer = {
    "bootloader": {
        version: "v0",
    },
    "ddr": {
        version: "v1",
    },
    "ecap": {
        version: "v0",
    },
    "epwm": {
        version: "v0",
    },
    "eqep": {
        version: "v0",
    },
    "gpio": {
        version: "v0",
    },
    "gtc": {
        version: "v0",
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
    "udma": {
        version: "v0",
    },
    "watchdog": {
        version: "v0",
    },
};

const topModules_wkup = [
    "/drivers/gpio/gpio",
    "/drivers/bootloader/bootloader",
    "/drivers/ddr/ddr",
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/gtc/gtc",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
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
    "/drivers/udma/udma",
    "/drivers/watchdog/watchdog",
];

const topModules_c75 = [
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcasp/mcasp",
    "/drivers/mmcsd/mmcsd",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
];

const topModules_a53 = [
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/eqep/eqep",
    "/drivers/gpio/gpio",
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
