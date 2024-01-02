
let common = system.getScript("/common");

let timerClockSourceConfig_r5f = {
    name: "clkSource",
    displayName: "Input Clock Source",
    default: "MCU_HFOSC0",
    options: [
        {
            "name": "MCU_HFOSC0",
        },
    ],
};

function getTimerClockSourceValue(instance) {
    let clkSelMuxValue = 0;

    switch(instance.clkSource) {
        default:
        case "MCU_HFOSC0":
            clkSelMuxValue = 0x0;
            break;
    }
    return clkSelMuxValue;
}

function makeInstanceConfig() {
    let config = {};
    let staticConfigArr = getStaticConfigArr();
    let defaultInstanceIndex = getDefaultInstance();

    if(staticConfigArr.length == 0)
        return undefined;

    config.name = "instance";
    config.displayName = "Instance";
    config.description = "Select Instance";
    config.default = staticConfigArr[defaultInstanceIndex].name;
    config.options = [];

    for (let i = 0; i < staticConfigArr.length; i++) {
        let option = {};

        option.name = staticConfigArr[i].name;
        config.options.push(option);
    }

    return config;
}

function getDefaultInstance() {
    let cpu = common.getSelfSysCfgCoreName();
    let defaultInstanceMap = {
        "mcu-r5fss0-0": 0,
        "wkup-r5fss0-0": 0,
        "a53ss0-0": 2,
        "a53ss0-1": 3,
        "a53ss1-0": 4,
        "a53ss1-1": 5,
    }
    return defaultInstanceMap[cpu];
}

function getStaticConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr;

    if(cpu.match(/mcu-r5fss0-0/)) {
        let staticConfig_mcu_r5f = [];

        for(let i=0; i<1; i++)
        {
            staticConfig_mcu_r5f.push(
                {
                    name: `MCU_TIMER${i}`,
                    timerBaseAddr: 0x04800000 + i*0x10000,
                    timerHwiIntNum: 28 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x04508060 + 4*i,
                    disableClkSourceConfig: false,
                    lockUnlockDomain: "SOC_DOMAIN_ID_MCU",
                    lockUnlockPartition: 2,
                }
            )
        }
        staticConfigArr = staticConfig_mcu_r5f;
    }
    else if (cpu.match(/wkup-r5fss0-0/)){
        let staticConfig_wkup_r5f = [];
        for(let i=1; i<2; i++)
        {
            staticConfig_wkup_r5f.push(
                {
                    name: `WKUP_TIMER${i}`,
                    timerBaseAddr: 0x2B100000+ i*0x10000,
                    timerHwiIntNum: 138 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x430081B0 + 4*i,
                    disableClkSourceConfig: false,
                    lockUnlockDomain: "SOC_DOMAIN_ID_WKUP",
                    lockUnlockPartition: 2,
                }
            )
        }
        staticConfigArr = staticConfig_wkup_r5f;
    }
    return staticConfigArr;
}

function getTimerClockSourceConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let timerClockSourceConfig = timerClockSourceConfig_r5f;

    if(cpu.match(/mcu-r5fss0-0/) || cpu.match(/wkup-r5fss0-0/)) {
        timerClockSourceConfig = timerClockSourceConfig_r5f;
    }

    return timerClockSourceConfig;
}

function getDefaultTimerClockSourceMhz() {
    let cpu = common.getSelfSysCfgCoreName();

    return 25000000;
}

exports = {
    getStaticConfigArr,
    getTimerClockSourceConfigArr,
    getTimerClockSourceValue,
    getDefaultTimerClockSourceMhz,
    makeInstanceConfig,
};
