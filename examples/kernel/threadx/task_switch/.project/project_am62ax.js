let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "threadx_task_switch.c",
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

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_r5/inc",
    ],
};

const includes_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_c7x/inc",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/inc",
    ],
};

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_r5f = {
    common: [
        "threadx.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_c75 = {
    common: [
        "threadx.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_a53 = {
    common: [
        "threadx.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_ECLIPSE_THREADX_THREADX_TASK_SWITCH";


const templates_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/threadx/main_threadx.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "threadx_task_switch_main",
        },
    },
];

const templates_c75 =
[
    {
        input: ".project/templates/am62ax/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/threadx/main_threadx.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "threadx_task_switch_main",
            stackSize: 64*1024,
        },
    }
];

const templates_a53 =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/threadx/main_threadx.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "threadx_task_switch_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "threadx"},
    // { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62ax-sk", os: "threadx"},
    // { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62ax-sk", os: "threadx"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "threadx_task_switch";
    property.description = "ThreadX task switching example."
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

    if(buildOption.cpu.match(/r5f*/)) {
        build_property.includes = includes_r5f;
        build_property.templates = templates_r5f;
        build_property.libs = libs_r5f;
    } 
    else if (buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_c75;
        build_property.templates = templates_c75;
        build_property.libs = libs_c75;
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.includes = includes_a53;
        build_property.templates = templates_a53;
        build_property.libs = libs_a53;
    } 

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
