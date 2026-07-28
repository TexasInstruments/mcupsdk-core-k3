let path = require('path');

let device = "j722s";

const files = {
    common: [
        "empty.c",
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

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/r5f",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/r5f",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_main_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
}

const libs_freertos_c75ss0 = {
    common: [
        "freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss0-0.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_c75ss1 = {
    common: [
        "freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss1-0.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_EMPTY";

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "empty_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "c75ss0-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "c75ss1-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "empty",
        tag: "freertos",
        skipProjectSpec: false,
        readmeDoxygenPageTag: readmeDoxygenPageTag,
        board: "j722s-evm",
        projects: [
            { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "c75ss0-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "c75ss1-0",      cgt: "ti-c7000",     board: "j722s-evm", os: "freertos", isPartOfSystemProject: true},
        ],
    },
]

const templates_freertos_c75ss0 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "empty_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_c75ss1 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "empty_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f.cmd.xdt",
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
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "empty_main",
        },
    }
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "empty";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "An Empty Example. This example is intended to be a starting point for new development"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

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
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
        }
    }
    else if(buildOption.cpu.match(/main-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_main_r5f;
            build_property.templates = templates_freertos_main_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75ss0-0*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75ss0;
            build_property.templates = templates_freertos_c75ss0;
        }
    }
    else if(buildOption.cpu.match(/c75ss1-0*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75ss1;
            build_property.templates = templates_freertos_c75ss1;
        }
    }
    return build_property;
}

function getSystemProjects(device)
{
    return systemProjects;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};
