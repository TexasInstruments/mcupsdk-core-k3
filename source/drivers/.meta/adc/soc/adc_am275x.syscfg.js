
let common = system.getScript("/common");

const adc_config_r5f = [
    {
        name: "ADC",
        baseAddr: "CSL_ADC12FCC0_ADC_BASE",
        intrNum: 151,
        clockIds: [ "TISCI_DEV_ADC0_ADC_CLK" ],
        numBits: 12,
    },
];

function getStaticConfigArr() {
    return adc_config_r5f;
}

/* Dummy functions for am275*/
function getAdcClockSelectParentValue(instance) {

    let clkSelParentValue ;

    return clkSelParentValue;
}

function getAdcClockSourceConfigArr() {

    let adcClockSourceConfig;

    return adcClockSourceConfig;
}

function isPinmuxSupported(){
    return true;
}

function getExtTriggerNum(){
    return 1;
}

let soc = {
    getStaticConfigArr,
    getAdcClockSelectParentValue,
    getAdcClockSourceConfigArr,
    isPinmuxSupported,
    getExtTriggerNum,
};

exports = soc;
