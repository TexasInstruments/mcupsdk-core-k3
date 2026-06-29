let path = require('path');

let device = "am62x";

const files = {
    common: [
        "task_switch.c",
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

const includes_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
    ],
};

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53_amp = {
    common: [
        "AMP_FREERTOS_A53",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_KERNEL_FREERTOS_TASK_SWITCH";

const templates_m4f =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const templates_freertos_a53ss00 =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    }
];

const templates_freertos_a53ss01 =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];
const templates_freertos_a53ss10 =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss1-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];
const templates_freertos_a53ss11 =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss1-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "FreeRTOS",
        testCaseName: "FreeRTOS Task Switch Application",
        testCaseIds: "SITSW-1461",
        expectTimeout: 60,
    },
};

const robot_template_amp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests_amp.robot",
    options: {
        componentName: "AMP",
        testCaseName: "FreeRTOS Task Switch:FreeRTOS-AMP",
        appName: "task_switch(amp)",
        testCaseIds: "SITSW-5783",
        withCfg: true,
        cfgPath: "examples/kernel/freertos/task_switch/{board}/task_switch_freertos-amp_sbl_uart_${DEVICE_TYPE}.cfg",
    },
};

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss1-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss1-1", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},
    { device: device, cpu: "a53ss1-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},
    { device: device, cpu: "a53ss1-1", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss1-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss1-1", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "task_switch";
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.includes("m4f")) {
        build_property.includes = includes_m4f;
        build_property.templates = templates_m4f;
        build_property.libs = libs_m4f;
    }
    if(buildOption.cpu.includes("a53")) {
        build_property.includes = includes_a53;
        build_property.defines = defines_a53_amp;
        build_property.libs = libs_a53;
        build_property.libdirs = libdirs;
        build_property.isAmpSHM = true;
        property.isLogSHM = true;
        if(buildOption.cpu.match(/a53ss0-0/))
        {
            build_property.templates = templates_freertos_a53ss00;
        }
        else if(buildOption.cpu.match(/a53ss0-1/))
        {
            build_property.templates = templates_freertos_a53ss01;
        }
        else if(buildOption.cpu.match(/a53ss1-0/))
        {
            build_property.templates = templates_freertos_a53ss10;
        }
        else if(buildOption.cpu.match(/a53ss1-1/))
        {
            build_property.templates = templates_freertos_a53ss11;
        }
    }

    if (buildOption.cpu.match(/r5f*/) || buildOption.cpu.match(/m4f*/) || buildOption.cpu.match(/a53ss0-0/)) {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    if (buildOption.cpu.match(/a53ss0-0/) && buildOption.os === "freertos") {
        build_property.templates = [...(build_property.templates || []), robot_template_amp];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
