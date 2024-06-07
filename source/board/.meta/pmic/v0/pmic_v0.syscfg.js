
let common = system.getScript("/common");
let soc = system.getScript(`/board/pmic/soc/pmic_${common.getSocName()}`);

function getInstanceConfig(moduleInstance) {
    let configArr = soc.getConfigArr();
    let config = configArr.find(o => o.name === moduleInstance.name);

    return {
        ...config,
        ...moduleInstance,
    };
};

function getConfigurables() {

    let config = [];
    let staticConfig = soc.getConfigArr();
    let defaultConfig = soc.getDefaultConfig();

    config.push(
        {
            ...common.ui.makeConfig(staticConfig, "name", "PMIC"),
        },
        {
            name: "mainI2cAddress",
            displayName: "PMIC User Page I2C Address",
            default: defaultConfig.i2cUserAddress,
            displayFormat: "hex",
        },
        {
            name: "nvmI2cAddress",
            displayName: "NVM Page I2C Address",
            default: defaultConfig.i2cNvmAddress,
            displayFormat: "hex",
        },
        {
            name: "wdogI2CAddress",
            displayName: "Watchdog Page I2C Address",
            default: defaultConfig.i2cWdogAddress,
            displayFormat: "hex",
        },
        {
            name: "wdogEnable",
            displayName: "Use Watchdog To Monitor MCU",
            longDescription: "Watchdog in PMIC can monitor the correct operation of MCU core in the SOC. " +
                             "If it is enabled, MCU core has to send periodic signals in the watchdog " +
                             "widnow to prevent unnecessary warm reset.",
            default: false,
            onChange: function (inst, ui) {
                let hideWdogCfg = true;
                if (inst.wdogEnable == true)
                {
                    hideWdogCfg = false;
                }
                else
                {
                    inst.wdogMode = "triggerMode";
                    inst.enableReset = false;
                    inst.win1Time = 70400;
                    inst.win2Time = 70400;
                    inst.longWinTime = 5000;
                    inst.qaI2CEnable = false;
                    inst.failThreshold = 0;
                    inst.resetThreshold = 0;
                    inst.qaFdbk = 0;
                    inst.qaLfsr = 0;
                    inst.qaSeed = 0;
                    ui.qaI2CEnable.hidden = true;
                    ui.qaFdbk.hidden = true;
                    ui.qaLfsr.hidden = true;
                    ui.qaSeed.hidden = true;
                }
                ui.wdogMode.hidden = hideWdogCfg;
                ui.enableReset.hidden = hideWdogCfg;
                ui.win1Time.hidden = hideWdogCfg;
                ui.win2Time.hidden = hideWdogCfg;
                ui.longWinTime.hidden = hideWdogCfg;
                ui.failThreshold.hidden = hideWdogCfg;
                ui.resetThreshold.hidden = hideWdogCfg;
            }
        },
        {
            name: "wdogMode",
            displayName: "Watchdog Mode",
            longDescription: "Watchdog supports two operating modes -> Trigger and Q&A",
            default: "triggerMode",
            options: [
                {
                    name: "triggerMode",
                    displayName: "Trigger Mode"
                },
                {
                    name: "qaMode",
                    displayName: "Question-Answer(Q&A) Mode"
                },
            ],
            hidden: true,
            onChange: function (inst, ui) {
                let hideWdogCfg = true;
                if (inst.wdogMode == "qaMode")
                {
                    hideWdogCfg = false;
                }
                else
                {
                    inst.qaI2CEnable = false;
                    inst.qaFdbk = 0;
                    inst.qaLfsr = 0;
                    inst.qaSeed = 0;
                }
                ui.qaI2CEnable.hidden = hideWdogCfg;
                ui.qaFdbk.hidden = hideWdogCfg;
                ui.qaLfsr.hidden = hideWdogCfg;
                ui.qaSeed.hidden = hideWdogCfg;
            }
        },
        {
            name: "qaI2CEnable",
            displayName: "Use Separate I2C For Q&A Watchdog",
            longDescription: "If dual I2C mode is supported in the PMIC DEVICE, dedicated I2C can be used for Q&A watchdog",
            default: false,
            hidden:true,
        },
        {
            name: "win1Time",
            displayName: "Window-1 Time In Micro-seconds",
            longDescription: "Watchdog window-1 duration in Micro Seconds.To get more effective results,"+
                             "program window1 with multiples of 550. The range is from 550us to 70400us.",
            default: 70400,
            hidden:true,
        },
        {
            name: "win2Time",
            displayName: "Window-2 Time In Micro-seconds",
            longDescription: "Watchdog window-2 duration in Micro Seconds.To get more effective results,"+
                             "program window1 with multiples of 550. The range is from 550us to 70400us.",
            default: 70400,
            hidden:true,
        },
        {
            name: "longWinTime",
            displayName: "Lone Window Time In Milli-seconds",
            longDescription: "Long Window duration in milli seconds. The value can be either 80ms or"+
                             "from 125ms to 772000ms",
            default: 5000,
            hidden:true,
        },
        {
            name: "enableReset",
            displayName: "Enable Warm Reset",
            longDescription: "If this is set, watchdog triggers a warm reset when " +
                             "fail counter > fail threshold + reset threshold",
            default: false,
            hidden:true,
        },
        {
            name: "failThreshold",
            displayName: "Fail Threshold Value",
            longDescription: "1st threshold value for the watchdog fail counter. Watchdog generates a interrupt if" +
                             " fail counter > fail threshold",
            default: 0,
            hidden:true,
        },
        {
            name: "resetThreshold",
            displayName: "Reset Threshold Value",
            longDescription: "2nd threshold value for the watchdog fail counter. Watchdog generates a warm reset(if enabled) when" +
                             " fail counter > fail threshold + reset threshold",
            default: 0,
            hidden:true,
        },
        {
            name: "qaFdbk",
            displayName: "Q&A Feedback Configuration Bits",
            longDescription: "Feedback configuration bits for the watchdog question. These bits control " +
                             "the sequence of the generated questions and respective reference answers",
            default: 0,
            displayFormat: "hex",
            hidden:true,
        },
        {
            name: "qaLfsr",
            displayName: "Q&A LFSR-equation Configuration Bits",
            longDescription: "LFSR-equation configuration bits for Q&A watchdog",
            default: 0,
            displayFormat: "hex",
            hidden:true,
        },
        {
            name: "qaSeed",
            displayName: "Q&A Question Seed Value",
            longDescription: "The MCU can update the question-seed value to generate a set of new of questions",
            default: 0,
            displayFormat: "hex",
            hidden:true,
        },
    );

    return config;
}

let pmic_module_name = "/board/pmic/pmic";

let pmic_module = {
    displayName: "PMIC",

    templates: {
        "/board/board/board_open_close.c.xdt": {
            board_open_close_config: "/board/pmic/templates/pmic_open_close_config.c.xdt",
            board_open: "/board/pmic/templates/pmic_open.c.xdt",
            board_close: "/board/pmic/templates/pmic_close.c.xdt",
        },
        "/board/board/board_open_close.h.xdt": {
            board_open_close_config: "/board/pmic/templates/pmic_open_close.h.xdt",
        },
        "/board/board/board_config.h.xdt": {
            board_config: "/board/pmic/templates/pmic.h.xdt",
        },
        "/board/board/board_config.c.xdt": {
            board_init: "/board/pmic/templates/pmic_init.c.xdt",
            board_deinit: "/board/pmic/templates/pmic_deinit.c.xdt",
        },
    },
    defaultInstanceName: "CONFIG_PMIC",
    config: getConfigurables(),
    validate: validate,
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    maxInstances: 1,
    sharedModuleInstances: addModuleInstances,
    getInstanceConfig,
};

function validate(instance, report) {
    common.validate.checkNumberRange(instance, report, "mainI2cAddress", 0x0, 0x7F, "hex");
    common.validate.checkNumberRange(instance, report, "nvmI2cAddress", 0x0, 0x7F, "hex");
    common.validate.checkNumberRange(instance, report, "wdogI2CAddress", 0x0, 0x7F, "hex");
    common.validate.checkNumberRange(instance, report, "win1Time", 550, 70400);
    common.validate.checkNumberRange(instance, report, "win2Time", 550, 70400);
    common.validate.checkNumberRange(instance, report, "failThreshold", 0, 7);
    common.validate.checkNumberRange(instance, report, "resetThreshold", 0, 7);
    common.validate.checkNumberRange(instance, report, "qaLfsr", 0, 3);
    common.validate.checkNumberRange(instance, report, "qaFdbk", 0, 3);
    common.validate.checkNumberRange(instance, report, "qaSeed", 0, 15);
    if ((instance.longWinTime != 80) && (instance.longWinTime < 125 || instance.longWinTime > 772000))
    {
        report.logError( `Long window time should be either 80ms or from 125ms to 772000ms`,
            instance, "longWinTime");
    }
}

function addModuleInstances(instance) {
    let modInstances = new Array();
    let configArr = soc.getConfigArr();
    let config = configArr.find(o => o.name === instance.name);

    if(config.commMode == "I2C") {
        modInstances.push({
            name: "mainPeripheralDriver",
            displayName: "Main interface I2C Configuration",
            moduleName: '/drivers/i2c/i2c',
            requiredArgs: {
                $name: "MAIN_I2C",
            }
        });

        if(instance.qaI2CEnable == true){
            modInstances.push({
                name: "QaWatchdogPeripheralDriver",
                displayName: "Q&A watchdog I2C interface Configuration",
                moduleName: '/drivers/i2c/i2c',
                requiredArgs: {
                    $name: "QA_I2C",
                }
            });
        }
    }

    return (modInstances);
}

exports = pmic_module;
