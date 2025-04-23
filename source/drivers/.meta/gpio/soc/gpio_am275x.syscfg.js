

function getInterfaceName(inst) {

    if(inst.useMcuGpioPins)
        return "MCU_GPIO"
    else if(inst.useAdcGpiPins)
        return "GPI"

    return "GPIO";
}

function getInstanceString(moduleInstance) {
    let interfaceName = getInterfaceName(moduleInstance);
    let peripheralName = interfaceName;
    let solution = moduleInstance[peripheralName].$solution

    if ( peripheralName == "GPIO" ){
        let splitStrings = (solution.peripheralPinName === null ) ? "": solution.peripheralPinName.split("_");
        let gpioBank = splitStrings[0];
        return gpioBank
    }
    else {
        return solution.peripheralName;
    }

}

function getPinIndex(moduleInstance) {
    let interfaceName = getInterfaceName(moduleInstance);
    let peripheralPinName;

    if( interfaceName == "GPIO")
        peripheralPinName = moduleInstance[interfaceName].$solution.peripheralPinName;
    else
        peripheralPinName = moduleInstance[interfaceName].gpioPin.$solution.peripheralPinName;

    if(! peripheralPinName)
        return "INVALID";

    let splitStrings = peripheralPinName.split("_");

    /* The last split is the GPIO number */
    return splitStrings[splitStrings.length-1];
}

exports = {
    getInterfaceName,
    getInstanceString,
    getPinIndex,
};
