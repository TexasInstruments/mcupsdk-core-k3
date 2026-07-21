let path = require('path');

let device = "am62px";

const files = {
    common: [
        "test_ecap.c",
        "main.c",
    ],
};

const files_rtos = {
    common: [
        "test_ecap_multi_thread.c",
        "test_ecap.c",
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

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const templates_nortos_r5f = [
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_r5f = [
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"  },
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ecap";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests_nortos.robot",
    options: {
        componentName: "ECAP",
        testCaseName: "ecap test application (nortos)",
        appName: "test_ecap(nortos)",
        testCaseIds: "SITSW-6990 SITSW-7274 SITSW-7275 SITSW-7276 SITSW-7277 SITSW-7278 SITSW-7279 SITSW-7280 SITSW-7281 SITSW-7282" +
                     " SITSW-7283 SITSW-7312 SITSW-7313 SITSW-10655 SITSW-10656 SITSW-10658 SITSW-10659 SITSW-10660",
        timeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests_freertos.robot",
    options: {
        componentName: "ECAP",
        testCaseName: "ecap test application (freertos)",
        appName: "test_ecap(freertos)",
        testCaseIds: "SITSW-6990 SITSW-7274 SITSW-7275 SITSW-7276 SITSW-7277 SITSW-7278 SITSW-7279 SITSW-7280 SITSW-7281 SITSW-7282" +
                     " SITSW-7283 SITSW-7312 SITSW-7313 SITSW-10655 SITSW-10656 SITSW-10658 SITSW-10659 SITSW-10660 SITSW-10661 SITSW-10662",
        timeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/mcu-r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.files     = files_rtos;
            build_property.includes  = includes_freertos_r5f;
            build_property.libdirs   = libdirs_freertos;
            build_property.libs      = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags    = cflags_free_rtos;
        } else {
            build_property.includes  = includes_nortos_r5f;
            build_property.libdirs   = libdirs_nortos;
            build_property.libs      = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }

    if (buildOption.os.match(/nortos/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    } else if (buildOption.os.match(/freertos/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
