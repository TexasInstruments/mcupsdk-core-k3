let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "rtc_led_blink.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_freertos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f = {
    common:[
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_RTC_LED_BLINK";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "rtc_led_blink",
        },
    }
];

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x8000,
            stackSize: 0x4000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "rtc_led_blink",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "rtc_led_blink";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "RTC",
        testCaseName: "RTC Led Blink Example",
        testCaseIds: "SITSW-6021",
        withCfg: true,
        cfgPath: "examples/drivers/rtc/rtc_led_blink/{board}/{coreName}/default_rtc_led_blink_${DEVICE_TYPE}.cfg",
        expectedString: "RTC LED blink test passed!!",
        timeout: 300,
    },
};

const robot_template_mcu = {
    input: ".project/templates/am62dx/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "RTC",
        testCaseName: "RTC Led Blink Example",
        testCaseIds: "SITSW-6021",
        withCfg: true,
        cfgPath: "examples/drivers/rtc/rtc_led_blink/{board}/{coreName}/default_rtc_led_blink_${DEVICE_TYPE}.cfg",
        expectedString: "RTC LED blink test passed!!",
        timeout: 300,
        expectPort: "USB3",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.defines = defines_common;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_r5;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
    }

    if (buildOption.cpu.match(/mcu-r5f/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_mcu];
    } else {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
