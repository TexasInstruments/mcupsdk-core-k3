
let common = system.getScript("/common");

let timerClockSourceConfig_a53 = {
    name: "clkSource",
    displayName: "Input Clock Source",
    default: "HFOSC0_CLKOUT",
    options: [
        {
            "name": "HFOSC0_CLKOUT",
        },
    ],
};

function getTimerClockSourceValue(instance) {
    let clkSelMuxValue = 0;

    switch(instance.clkSource) {
        default:
        case "HFOSC0_CLKOUT":
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
        "a53ss0-0": 0,
        "a53ss0-1": 1,
    }
    return defaultInstanceMap[cpu];
}

function getStaticConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr;

    if(cpu.match(/a53*/)) {
        let staticConfig_a53 = [];

        for(let i=0; i<2; i++)
        {
            staticConfig_a53.push(
                {
                    name: `TIMER${i}`,
                    timerBaseAddr: 0x2b100000 + i*0x10000,
                    timerHwiIntNum: 222 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x43022000 + 4*i,
                    disableClkSourceConfig: false,
                    lockUnlockDomain: "SOC_DOMAIN_ID_WKUP",
                    lockUnlockPartition: 2,
                }
            )
        }
        for(let i=0; i<4; i++)
        {
            staticConfig_a53.push(
                {
                    name: `TIMER${i}`,
                    timerBaseAddr: 0x02400000 + i*0x10000,
                    timerHwiIntNum: 202 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x09115000 + 1000*i,
                    disableClkSourceConfig: true,
                }
            )
        }
        staticConfigArr = staticConfig_a53;
    }
    return staticConfigArr;
}

function getTimerClockSourceConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let timerClockSourceConfig = timerClockSourceConfig_a53;

    if(cpu.match(/a53*/)) {
        timerClockSourceConfig = timerClockSourceConfig_a53;
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