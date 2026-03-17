
let common = system.getScript("/common");

const driverVer = {
    "aasrc": {
        version: "v0",
    },
    "adc": {
        version: "v0",
    },
    "bootloader": {
        version: "v0",
    },
    "ecap": {
        version: "v0",
    },
    "epwm": {
        version: "v0",
    },
    "gpio":{
        version:"v0_1",
    },
    "gtc": {
        version: "v0",
    },
    "hyperbus": {
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
        version: "v0",
    },
    "ospi": {
        version: "v0",
    },
    "qos": {
        version: "v0",
    },
    "rtc": {
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
        version: "v1",
    },
};

const topModules_wkup = [
    "/drivers/bootloader/bootloader",
    "/drivers/gpio/gpio",
    "/drivers/gtc/gtc",
    "/drivers/hyperbus/hyperbus",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcu_bist/mcu_bist",
    "/drivers/mmcsd/mmcsd",
    "/drivers/ospi/ospi",
    "/drivers/qos/qos",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
    "/drivers/watchdog/watchdog",
];

const topModules_main = [
    "/drivers/aasrc/aasrc",
    "/drivers/adc/adc",
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/gtc/gtc",
    "/drivers/hyperbus/hyperbus",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
    "/drivers/mcan/mcan",
    "/drivers/mcasp/mcasp",
    "/drivers/mcspi/mcspi",
    "/drivers/mmcsd/mmcsd",
    "/drivers/ospi/ospi",
    "/drivers/rtc/rtc",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
    "/drivers/watchdog/watchdog",
];

const topModules_c75 = [
    "/drivers/aasrc/aasrc",
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/gtc/gtc",
    "/drivers/hyperbus/hyperbus",
    "/drivers/i2c/i2c",
    "/drivers/ipc/ipc",
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
        "wkup-r5fss0-0" : "CSL_CORE_ID_WKUP_R5FSS0_0",
        "r5fss0-0" : "CSL_CORE_ID_R5FSS0_0",
        "r5fss0-1" : "CSL_CORE_ID_R5FSS0_1",
        "r5fss1-0" : "CSL_CORE_ID_R5FSS1_0",
        "r5fss1-1" : "CSL_CORE_ID_R5FSS1_1",
        "c75ss0-0" : "CSL_CORE_ID_C75SS0_0",
        "c75ss1-0" : "CSL_CORE_ID_C75SS1_0",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {

        let topModules = topModules_wkup;

        if(common.getSelfSysCfgCoreName().includes("wkup-r5fss0-0")) {
            topModules = topModules_wkup;
        }
        else if(common.getSelfSysCfgCoreName().includes("r5fss")) {
            topModules = topModules_main;
        }else if(common.getSelfSysCfgCoreName().includes("c75ss")){
            topModules = topModules_c75;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};
