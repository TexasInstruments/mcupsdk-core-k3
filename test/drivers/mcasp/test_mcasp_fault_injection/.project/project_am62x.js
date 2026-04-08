let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_mcasp_fault_injection.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../",    /* Board base */
        "../../..", /* Example base */
    ],
};

const cflags_freertos_a53 = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DAPP_MCASP_TASK_STACK_SIZE_MT=0xA000"   // 40*1024
    ],
}

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "../../../configs/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "../../../configs/lib",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers-mcasp-inject-fault.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers-mcasp-inject-fault.am62x.a53.gcc-aarch64.${ConfigName}.lib",
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
        },
        {
            input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        },
    ];

const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "test_mcasp_fault_injection test application",
        appName: "test_mcasp_fault_inject",
        testCaseIds: "SITSW-9253 SITSW-9254 SITSW-9255 SITSW-9256 SITSW-9257 SITSW-9258 SITSW-9259 SITSW-9260 SITSW-9261 SITSW-9262",
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "test_mcasp_fault_injection test application",
        appName: "test_mcasp_fault_inject",
        testCaseIds: "SITSW-9253 SITSW-9254 SITSW-9255 SITSW-9256 SITSW-9257 SITSW-9258 SITSW-9259 SITSW-9260 SITSW-9261 SITSW-9262",
    },
};

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcasp_fault_inject";
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
            build_property.cflags = cflags_freertos_a53;
        }
        else if (buildOption.os.match(/nortos*/)) {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    }

    if (buildOption.os.match(/freertos*/)) {
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
