
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/mcasp/soc/mcasp_${common.getSocName()}`);
let soc_clocking = system.getScript(`/drivers/.meta/mcasp/v1/mcasp_clocking/soc/mcasp_clocking_${common.getSocName()}.js`);

function getConfigArr()
{
    return processConfigArr(soc_clocking.mcasp_auxclk_gf_sel, false);
}

function getFreqVal(inst, x)
{
    let module = system.modules['/drivers/mcasp/mcasp'];

    return module.$static[x];
}

function processConfigArr(configEntry, hide) {
    let configArr = [];

    if(configEntry.type == "clk_mux")
    {
        let config = {};
        config.displayName = configEntry.displayName;
        config.name = configEntry.name.toString();
        config.default = configEntry.muxOptions[0].name.toString();
        config.hidden = hide;
        config.options = configEntry.muxOptions.map(option => (
            {
                name: option.name.toString(),
                displayName: option.displayName
            }
        ));

        /* Add onChange element to config */
        config.onChange = function(inst, ui) {
            configEntry.muxOptions.forEach(option => {
                if(inst[config.name] == option.name) {
                    ui[option.options.name.toString()].hidden = false;
                } else {
                    ui[option.options.name.toString()].hidden = true;
                }
            });
        };
        if(configEntry.longDescription) {
            config.longDescription = configEntry.longDescription.toString();
        }

        configArr.push(config);

        configEntry.muxOptions.forEach(option => {
            let isHidden = true;
            if(option.name == configEntry.muxOptions[0].name) {
                isHidden = false;
            }
            configArr = configArr.concat(processConfigArr(option.options, isHidden));
        });
    }
    else if (configEntry.type == "clk_source_mux")
    {
        let config = {};
        config.displayName = configEntry.displayName;
        config.name = configEntry.name.toString();
        let temp = config.name;
        config.default = configEntry.muxOptions[0].name.toString();
        config.hidden = hide;
        config.options = configEntry.muxOptions.map(option => (
            {
                name: option.name.toString(),
                displayName: option.displayName
            }
        ));
        if(configEntry.longDescription) {
            config.longDescription = configEntry.longDescription.toString();
        }

        configArr.push(config);

        config  = {};
        config.displayName = configEntry.displayName.toString() + " Freq";
        config.name = configEntry.name.toString() + "_freq";
        config.default = configEntry.muxOptions[0].defaultFreq.toString();
        config.getValue = (inst) => {
            return getMcaspAuxClkFreq(inst);
        };
        config.hidden = hide;
        configArr.push(config);
    }

    return configArr;
}

function getConfigTree() {
    return soc_clocking.mcasp_auxclk_gf_sel;
}

function recursiveGetTisciOptions(options) {
    let staticClockSources = [];
    if(options.muxOptions) {
        options.muxOptions.forEach(option => {
            if(option.tisciOption && options.type == "clk_source_mux") {
                let config = {};
                config.name = option.tisciOption.toString();
                config.displayName = option.displayName.toString();
                config.default = option.defaultFreq.toString();
                config.readOnly = false;
                staticClockSources.push(config);
            }
            if(option.options && option.options.muxOptions) {
                staticClockSources = staticClockSources.concat(recursiveGetTisciOptions(option.options));
            }
        });
    }
    return staticClockSources;
}

function getStaticClockSources() {
    return recursiveGetTisciOptions(soc_clocking.mcasp_auxclk_gf_sel);
}

function getTisciClockCfgList(instance, configEntry)
{
    let configArr = [];
    let module = system.modules['/drivers/mcasp/mcasp'];
    let mcaspName = module.getInstanceConfig(instance).name;
    let mcaspNumber = mcaspName.replace(/[^0-9]/g, '');

    if(configEntry.type == "clk_mux")
    {
        let config = {};

        config.tisciClock = configEntry.tisciClock;
        config.tisciClock = configEntry.tisciClock.replace('<n>', mcaspNumber);

        config.tisciDevice = configEntry.tisciDevice;
        config.tisciDevice = configEntry.tisciDevice.replace('<n>', mcaspNumber);

        config.type = "clk_mux";

        configEntry.muxOptions.forEach(option => {
            if(option.name == instance[configEntry.name])
            {
                config.option = option.tisciOption.toString();
                config.option = config.option.replace(/<n>/g, mcaspNumber);
                config.name = option.name.toString();
            }
        });

        configArr.push(config);

        configEntry.muxOptions.forEach(option => {
            let name1 = configEntry.name.toString();
            if(option.name == instance[name1])
            {
                configArr = configArr.concat(getTisciClockCfgList(instance, option.options));
            }
        });
    }
    else if (configEntry.type == "clk_source_mux")
    {
        let config = {};

        config.tisciClock = configEntry.tisciClock;
        config.tisciClock = configEntry.tisciClock.replace('<n>', mcaspNumber);

        config.tisciDevice = configEntry.tisciDevice;
        config.tisciDevice = configEntry.tisciDevice.replace('<n>', mcaspNumber);

        config.type = "clk_source_mux";

        let name1 = configEntry.name.toString();
        let matchingOption = configEntry.muxOptions.find(option => option.name == instance[name1]);
        config.isConfigurable = matchingOption.isConfigurable;
        config.freq = instance[name1+"_freq"];

        configEntry.muxOptions.forEach(option => {
            if(option.name == instance[configEntry.name])
            {
                config.option = option.tisciOption.toString();
                config.option = config.option.replace('<n>', mcaspNumber);
                config.name = option.name.toString();
            }
        });

        configArr.push(config);
    }

    return configArr;
}

function getMcaspAuxClkName(instance, configEntry) {
    let freq = "";
    if(configEntry.type == "clk_mux")
    {
        configEntry.muxOptions.forEach(option => {
            if(option.name == instance[configEntry.name])
            {
                freq += getMcaspAuxClkName(instance, option.options);
            }
        });
    }

    if(configEntry.type == "clk_source_mux")
    {
        configEntry.muxOptions.forEach(option => {
            if(option.name == instance[configEntry.name])
            {
                freq = option.tisciOption.toString();
            }
        });
    }

    return freq;
}

function getMcaspAuxClkFreq(instance) {
    let module = system.modules['/drivers/mcasp/mcasp'];

    return module.$static[getMcaspAuxClkName(instance, getConfigTree()).toString()];
}

exports = {
    getConfigArr,
    getConfigTree,
    getStaticClockSources,
    getTisciClockCfgList,
    getMcaspAuxClkFreq,
};
