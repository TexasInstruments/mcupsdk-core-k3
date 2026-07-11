let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_aasrc.c",
        "main.c",
        "board.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../",   /* Board base */
    ],
};

const cflags_c7 = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DC75_CORE",
    ],
}

const cflags_r5f = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DR5F_CORE",
    ],
}

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/lib",
    ],
};


const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/DSP/Include",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/Core/Include",
        "../.."
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/DSP/Include",
        "${MCU_PLUS_SDK_PATH}/source/cmsis/Core/Include",
        "../.."
    ],
};


const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "cmsis.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "cmsis.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
}

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/src",
        "../.."
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "FFTLIB_C7524.lib",
        "FFTLIB_common_C7524.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_r5f = {
    common: [
        "R5F_CORE"
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_r5f =
    [
        {
            input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
            output: "linker.cmd",
            options: {
                enableAasrcBuffers: "true",
            },
        },
        {
            input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        }
    ];

const templates_nortos_r5f =
    [
        {
            input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
            output: "linker.cmd",
            options: {
                enableAasrcBuffers: "true",
            },
        },
        {
            input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
            output: "../main.c",
            options: { entryFunction: "test_main" },
        }
    ]

const templates_freertos_c75_0 = [
    { input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt", output: "linker.cmd" },
    { input: ".project/templates/am275x/freertos/main_freertos.c.xdt", output: "../main.c", options: { entryFunction: "test_main", stackSize: 64 * 1024 } },
];

const templates_freertos_c75_1 = [
    { input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt", output: "linker.cmd" },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: { entryFunction: "test_main", stackSize: 256 * 1024 }
    },
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_aasrc";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isXlibs = true;

    return property;
}

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "AASRC",
        testCaseName: "AASRC FreeRTOS test cases",
        appName: "test_aasrc",
        testCaseIds: "SITSW-10062 SITSW-10065 SITSW-10069 SITSW-10071 SITSW-10072 SITSW-10073 SITSW-10157 " +
            "SITSW-10158 SITSW-10159 SITSW-10160 SITSW-10161 SITSW-10162 SITSW-10300 SITSW-10301 SITSW-10302 " +
            "SITSW-10306 SITSW-10307 SITSW-10308 SITSW-10309 SITSW-10310 SITSW-10311 SITSW-12151 SITSW-12152 " +
            "SITSW-12153 SITSW-12154 SITSW-12155 SITSW-12156 SITSW-12157 SITSW-12158 SITSW-12159 SITSW-12160",
        expectTimeout: 60,
        timeout: 660,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "AASRC",
        testCaseName: "AASRC NoRTOS test cases",
        appName: "test_aasrc",
        testCaseIds: "SITSW-10158 SITSW-10159 SITSW-10160 SITSW-10161 SITSW-10162 " +
            "SITSW-10300 SITSW-10301 SITSW-10307 SITSW-10308 SITSW-12151 SITSW-12152 " +
            "SITSW-12153 SITSW-12154 SITSW-12155 SITSW-12156 SITSW-12157 SITSW-12158 " +
            "SITSW-12159 SITSW-12160",
        expectTimeout: 60,
        timeout: 660,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/r5f*/)) {
        build_property.defines = defines_r5f;
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_r5f;
        }
        else {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }

    if (buildOption.cpu.match(/c75*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75;
            build_property.cflags = cflags_c7;
            if (buildOption.cpu.match("c75ss0-0")) {
                build_property.templates = templates_freertos_c75_0;
            }
            else if (buildOption.cpu.match("c75ss1-0")) {
                build_property.templates = templates_freertos_c75_1;
            }

        }
    }

    if (buildOption.os.match(/freertos*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    } else {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
