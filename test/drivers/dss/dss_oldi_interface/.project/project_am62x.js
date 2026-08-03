let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_dss_oldi.c",
        "test_display_control.c",
        "dss_display_pattern.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_dss_smp.c",
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

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const defines_a53_smp = {
    common: [
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const cflags_freertos_a53 = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
}

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

const templates_a53_smp =
    [
        {
            input: ".project/templates/am62x/common/linker_a53_smp.cmd.xdt",
            output: "linker.cmd",
            options: {
                dssFrameBuf: "true",
            },
        },
        {
            input: ".project/templates/am62x/freertos/main_freertos_smp.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_dss_smp_main",
            },
        },
    ];

const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "DSS: OLDI Interface - Test multiple frame input formats",
        testCaseIds: "SITSW-4560 SITSW-6069 SITSW-6070 SITSW-6071 SITSW-7529 SITSW-11256 SITSW-11257 SITSW-11258 SITSW-11259 SITSW-11260" +
            " SITSW-11261 SITSW-11262 SITSW-11263 SITSW-11264 SITSW-11266 SITSW-11267 SITSW-11268 SITSW-11269 SITSW-11270 SITSW-11271" +
            " SITSW-11272 SITSW-11273 SITSW-11274 SITSW-11275 SITSW-11276 SITSW-11277 SITSW-11278 SITSW-11279 SITSW-11280 SITSW-11282" +
            " SITSW-11283 SITSW-11284 SITSW-11285 SITSW-11286 SITSW-11297 SITSW-11281 SITSW-12726 SITSW-11366 SITSW-11367 SITSW-11368" +
            " SITSW-11369 SITSW-11370 SITSW-11371 SITSW-11372",
        expectTimeout: 600,
        timeout: 900,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "DSS: OLDI Interface - Test multiple frame input formats",
        testCaseIds: "SITSW-4560 SITSW-6069 SITSW-6071 SITSW-7529 SITSW-11256 SITSW-11257 SITSW-11258 SITSW-11259 SITSW-11260" +
            " SITSW-11261 SITSW-11262 SITSW-11263 SITSW-11264 SITSW-11266 SITSW-11267 SITSW-11268 SITSW-11269 SITSW-11270 SITSW-11271" +
            " SITSW-11272 SITSW-11273 SITSW-11274 SITSW-11275 SITSW-11278 SITSW-11279 SITSW-11280 SITSW-11282 SITSW-11283 SITSW-11284" +
            " SITSW-11285 SITSW-11286 SITSW-11281 SITSW-12726 SITSW-11366 SITSW-11367 SITSW-11368 SITSW-11369" +
            " SITSW-11370 SITSW-11371 SITSW-11372",
        expectTimeout: 600,
        timeout: 900,
    },
};

const robot_template_smp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "DSS: OLDI Interface - Test multiple frame input formats",
        appName: "test_dss_oldi(smp)",
        testCaseIds: "SITSW-11298 SITSW-11520",
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
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos-smp" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "freertos-smp" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos-smp" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dss_oldi";
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
        if ((buildOption.os.match(/freertos-smp*/))) {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags = cflags_freertos_a53;
        }
        else {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    }

    if (buildOption.os.match(/freertos-smp*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_smp];
    }
    else if (buildOption.os.match(/freertos*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    }
    else {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};