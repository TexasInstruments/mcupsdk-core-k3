let path = require('path');

let device = "am62ax";

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

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const safertos_defines_c75 = {
    common: [
        "OS_SAFERTOS",
    ],
};

const safertos_defines_dm_r5 = {
    common: [
        "OS_SAFERTOS",
        "BUILD_MCU",
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_KERNEL_SAFERTOS_TASK_SWITCH";

const libdirs_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_safertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/kernel/include_api",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/NoWrapper",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x/005_TI_CGT",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/config",
    ],
};

const includes_safertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/kernel/include_api",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/199_TI_CR5",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/PrivWrapperStd",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5/024_Clang",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/config",
    ],
};

const libs_safertos_c75 = {
    common: [
        "safertos.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_safertos_dm_r5f = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "safertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const templates_safertos_c75 =
[
    {
        input: ".project/templates/am62ax/common/linker_c75_safertos.cmd.xdt",
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
        input: ".project/templates/am62ax/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "task_switch_main",
        },
    }
];

const templates_safertos_dm_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_dm_r5f_safertos.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x2000,
            svcStackSize: 0x1000,
            fiqStackSize: 0x1000,
            abortStackSize: 0x1000,
            undefinedStackSize: 0x1000,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62ax/safertos/main_safertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62ax-sk", os: "safertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "safertos"},
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "task_switch";
    property.isInternal = false;
    property.isSkipTopLevelBuild = true;
    property.skipProjectSpec = true;
    property.description = "A Task Switch example."
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SafeRTOS",
        testCaseName: "FreeRTOS Task Switch Application",
        testCaseIds: "SITSW-10831",
    },
};

const robot_template_c75 = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SafeRTOS",
        testCaseName: "FreeRTOS Task Switch Application",
        testCaseIds: "SITSW-10831",
        logPort: "USB1",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/c75/)) {
        if(buildOption.os.match(/safertos*/) )
        {
            build_property.includes = includes_safertos_c75;
            build_property.libdirs = libdirs_safertos_c75;
            build_property.libs = libs_safertos_c75;
            build_property.templates = templates_safertos_c75;
            build_property.defines = safertos_defines_c75;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/safertos*/) )
        {
            build_property.includes = includes_safertos_r5f;
            build_property.libdirs = libdirs_safertos_dm_r5f;
            build_property.libs = libs_safertos_dm_r5f;
            build_property.templates = templates_safertos_dm_r5f;
            build_property.defines = safertos_defines_dm_r5;
        }
    }


    if (buildOption.cpu.match(/c75/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_c75];
    } else {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};