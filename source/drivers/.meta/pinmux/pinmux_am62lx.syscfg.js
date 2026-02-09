
/* SOC specific overrides for pinmux data */

function getPinModeOverRide(peripheralPin, muxSetting)
{
    let mode = muxSetting.mode;

    if( muxSetting.peripheralPin.peripheralName.includes("PRU_ICSS")
     && muxSetting.peripheralPin.peripheralName.includes("MII_G_RT") )
    {
        /* In MII_G_RT sub-peripheral within PRU_ICSS the mux value in device is not as expected.
         * Hence changing the value to match the requirement in SW
         */
        if(muxSetting.mode === "14")
            mode = "1";
        if(muxSetting.mode === "13")
            mode = "0";
    }

    return mode;
}

/* SOC specific configurables for pinmux */

function getPinConfigurables(interfaceName, pinName)
{
    let pinConfig;

    if (interfaceName === "GPIO"){
        pinConfig = _.cloneDeep(
            system.deviceData.interfaces[interfaceName].interfacePins[interfaceName].pinMappings[pinName].interfacePin.configurables
        );
    } else{
        pinConfig = _.cloneDeep(
            system.deviceData.interfaces[interfaceName].interfacePins[pinName].configurables
        );
    }

    return pinConfig;
}

function getPinMode(peripheralPin)
{
    let devicePin = system.deviceData.devicePins[peripheralPin.$solution.packagePinName];
    if (devicePin === undefined) return null
    let muxSetting = _.find(devicePin.mux.muxSetting,
                                function(muxSetting) {
                                    return (muxSetting.peripheralPin.name == peripheralPin.$solution.peripheralPinName);
                                }
                            );

    let muxMode = muxSetting.mode;

    /* work around to override issues in pinmux for a SOC */
    {
        muxMode = getPinModeOverRide(peripheralPin, muxSetting);
    }

    return muxMode;
}

function getPinConfigCStruct(pin, interfaceName, inst)
{
    let pu_pd = undefined;
    let drv_str = undefined;

    let obj;
    // if( interfaceName == "GPIO_n") obj = inst;
    if( interfaceName == "GPIO") obj = inst;
    else obj = pin;

    if(obj.pu_pd != undefined)
       pu_pd = obj.pu_pd;
    if(obj.pull != undefined)
       pu_pd = obj.pull;
    if(pin.drv_str != undefined)
       drv_str = pin.drv_str;

    let rx = obj.rx;
    let mode = getPinMode(pin);
    if (mode === null) return ""
    let settings = "( ";


    settings += `PIN_MODE(${mode}) `
    if(rx===true)
    {
        settings += "| PIN_INPUT_ENABLE ";
    }
    switch(pu_pd) {
        case "pu":
            settings += "| PIN_PULL_DIRECTION ";
            break;
        case "pd":
            break;
        case "nopull":
            settings += "| PIN_PULL_DISABLE ";
            break;
    }
    if(drv_str == 'fast')
    {
        settings += "| PIN_DRV_STR_FAST ";
    }
    if(drv_str == 'nom')
    {
        settings += "| PIN_DRV_STR_NOMINAL ";
    }
    settings += ")";

    let pinConfigString =
    `/* ${pin.$solution.peripheralPinName} -> ${pin.$solution.devicePinName} (${pin.$solution.packagePinName}) */
    {
        PIN_${pin.$solution.devicePinName.toUpperCase()},
        ${settings}
    },`

    return pinConfigString;
}

exports = {
    getPinModeOverRide,
    getPinConfigurables,
    getPinConfigCStruct,
};