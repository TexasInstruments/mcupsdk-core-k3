let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "test_watchdog_reset.c",
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const defines_a53 = {
    common:[
        "SOC_AM62DX",
        "CORE_A53",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableWdtResetNoinit: true,
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_reset_main",
        },
    }
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableWdtResetNoinit: true,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_reset_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableWdtResetNoinit: true,
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_reset_main",
        },
    },
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableWdtResetNoinit: true,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_reset_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
];

const robot_template_nortos_a53 = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Reset Test (A53 NoRTOS)",
        testCaseIds: "SITSW-12123 SITSW-12124",
        withCfg: true,
        cfgPath: "test/drivers/watchdog/test_watchdog_reset/{board}/{coreName}/test_watchdog_reset_sbl_ospi_${DEVICE_TYPE}.cfg",
        expectTimeout: 60,
    },
};

const robot_template_freertos_a53 = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Reset Test (A53 FreeRTOS)",
        testCaseIds: "SITSW-12123 SITSW-12124",
        withCfg: true,
        cfgPath: "test/drivers/watchdog/test_watchdog_reset/{board}/{coreName}/test_watchdog_reset_sbl_ospi_${DEVICE_TYPE}.cfg",
        expectTimeout: 60,
    },
};

const robot_template_nortos_r5f = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Reset Test (MCU-R5F NoRTOS)",
        testCaseIds: "SITSW-12123 SITSW-12124",
        withCfg: true,
        cfgPath: "test/drivers/watchdog/test_watchdog_reset/{board}/{coreName}/test_watchdog_reset_sbl_ospi_${DEVICE_TYPE}.cfg",
        expectTimeout: 60,
    },
};

const robot_template_freertos_r5f = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Reset Test (MCU-R5F FreeRTOS)",
        testCaseIds: "SITSW-12123 SITSW-12124",
        withCfg: true,
        cfgPath: "test/drivers/watchdog/test_watchdog_reset/{board}/{coreName}/test_watchdog_reset_sbl_ospi_${DEVICE_TYPE}.cfg",
        expectTimeout: 60,
    },
};

function getComponentProperty() {
    let property = {};
    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_watchdog_reset";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines_common;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_mcu_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.templates = [...(build_property.templates || []), robot_template_nortos_r5f];
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.includes = includes_freertos_mcu_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.templates = [...(build_property.templates || []), robot_template_freertos_r5f];
        }
    }
    else if(buildOption.cpu.match(/a53*/)){
        if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.defines = defines_a53;
            build_property.templates = [...(build_property.templates || []), robot_template_nortos_a53];
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.defines = defines_a53;
            build_property.templates = [...(build_property.templates || []), robot_template_freertos_a53];
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
