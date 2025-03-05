
let common = system.getScript("/common");

const staticConfig = [
    {
        name: "ADC0",
        baseAddr: "CSL_ADC0_BASE",
        intrNum: 285,
        clockIds: [ "AM62LX_DEV_ADC0_ADC_CLK" ],
        numBits: 10,
        clkSelMuxAddr : 0x09169000,
        lockUnlockDomain: "SOC_DOMAIN_ID_MAIN",
        lockUnlockPartition: 2,
    },
];

let adcClockSourceConfig = [
    {
        "name": "HFOSC0_CLKOUT",
    },
    {
        "name": "PER_SYSCLK0_DIV12",
    },
    {
        "name": "WKUP_PLL0_HSDIV8_CLKOUT",
    },
    {
        "name": "EXT_REFCLK1",
    },
];

function getStaticConfigArr() {
    return staticConfig;
}

function getAdcClockSelectParentValue(instance) {

    let clkSelParentValue = 0;

    switch(instance.clkSource) {
        default:
        case "HFOSC0_CLKOUT":
            clkSelParentValue = "AM62LX_DEV_ADC0_ADC_CLK_PARENT_GLUELOGIC_HFOSC0_CLK - AM62LX_DEV_ADC0_ADC_CLK - 1";
            break;
        case "PER_SYSCLK0_DIV12":
            clkSelParentValue = "AM62LX_DEV_ADC0_ADC_CLK_PARENT_SAM62_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK12 - AM62LX_DEV_ADC0_ADC_CLK - 1";
            break;
        case "WKUP_PLL0_HSDIV8_CLKOUT":
            clkSelParentValue = "AM62LX_DEV_ADC0_ADC_CLK_PARENT_POSTDIV4_16FF_WKUP_0_HSDIVOUT8_CLK - AM62LX_DEV_ADC0_ADC_CLK - 1";
            break;
        case "EXT_REFCLK1":
            clkSelParentValue = "AM62LX_DEV_ADC0_ADC_CLK_PARENT_BOARD_0_EXT_REFCLK1_OUT - AM62LX_DEV_ADC0_ADC_CLK - 1";
            break;
    }

    return clkSelParentValue;
}

function getAdcClockSourceConfigArr() {
    return adcClockSourceConfig;
}

function isPinmuxSupported(){
    return false;
}

function getExtTriggerNum(){
    return 2;
}

let soc = {
    getStaticConfigArr,
    getAdcClockSelectParentValue,
    getAdcClockSourceConfigArr,
    isPinmuxSupported,
    getExtTriggerNum,
};

exports = soc;
