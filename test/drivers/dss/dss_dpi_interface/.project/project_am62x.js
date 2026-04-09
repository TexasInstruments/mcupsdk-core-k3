let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_dss_dpi.c",
        "test_display_control.c",
        "dss_display_pattern.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* Board base */
        "../../..", /* Example base */
        "../../../..", /* Driver test base */
        "../../../../../../../examples/drivers/dss/dss_test_pattern"
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

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_a53 =
    [
        {
            input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
            output: "linker.cmd",
            options: {
                dssFrameBuf: "true",
            },
        },
        {
            input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        }
    ];

const templates_nortos_a53 =
    [
        {
            input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
            output: "linker.cmd",
            options: {
                dssFrameBuf: "true",
            },
        },
        {
            input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        },
    ];

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "DSS: DPI Interface - Test output DPI resolution",
        testCaseIds: "SITSW-4796 SITSW-4797",
        expectTimeout: 600,
        timeout: 900,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "nortos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dss_dpi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/a53*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
        }
        else {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
