let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_ipc_rpmsg.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated:
 * <mcu_plus_sdk>/test/drivers/ipc_rpmsg_m4f/am62x-sk/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",                       /* core_os_combo base (for generated main.c) */
        "../../..",                 /* Example base (ipc_rpmsg_m4f) */
        "../../../../ipc_rpmsg",   /* Shared test source directory */
    ],
};

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
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

const includes_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_m4f = [
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
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

const templates_freertos_dm_r5f = [
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_a53ss00 = [
    {
        input: ".project/templates/am62x/common/linker_a53ss0-0.cmd.xdt",
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

const templates_freertos_a53ss01 = [
    {
        input: ".project/templates/am62x/common/linker_a53ss0-1.cmd.xdt",
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

// Master Macro Defines - M4 is the main core for this configuration
const defines_dm_r5f = {
    common:[
        "SOC_AM62X",
        "ENABLE_SCICLIENT_DIRECT",
        "BUILD_M4F_AS_MASTER",
    ]
}

const defines_common = {
    common:[
        "BUILD_M4F_AS_MASTER",
        "BUILD_M4F",
    ]
}

const defines_a53_amp = {
    common:[
        "SOC_AM62X",
        "BUILD_M4F_AS_MASTER",
        "AMP_FREERTOS_A53",
    ]
}

// Strictly am62x-sk configurations
const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects = [
    {
        name: "test_ipc_rpmsg_m4f",
        tag: "freertos",
        skipProjectSpec: true,
        board: "am62x-sk",
        projects: [
            { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
            { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
            { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
            { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
        ],
    },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ipc_rpmsg_m4f";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLinuxInSystem = true;
    property.ipcVringRTOS = true;

    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;
    property.isLDRAEnable = false;

    return property;
}

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "test_ipc_rpmsg_m4f test application",
        appName: "test_ipc_rpmsg_m4f",
        testCaseIds: "SITSW-2469 SITSW-9360 SITSW-9370 SITSW-9373 SITSW-9499 SITSW-9500 SITSW-9860 SITSW-9900" +
                     " SITSW-12769 SITSW-12770 SITSW-12771 SITSW-12772",
        withCfg: true,
        cfgPath: "test/drivers/ipc_rpmsg_m4f/{board}/ipc_rpmsg_test_sbl_uart_${DEVICE_TYPE}.cfg",
        expectTimeout: 500,
        timeout: 900,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/m4f*/))
    {
        build_property.files = files;
        build_property.includes = includes_freertos_m4f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_m4f;
        build_property.templates = templates_freertos_m4f;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_r5f;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
    }
    else if(buildOption.cpu.match(/a53ss0-0/))
    {
        build_property.files = files;
        build_property.includes = includes_freertos_a53;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_a53;
        build_property.templates = templates_freertos_a53ss00;
        build_property.defines = defines_a53_amp;
        build_property.isAmpSHM = true;
    }
    else if(buildOption.cpu.match(/a53ss0-1/))
    {
        build_property.files = files;
        build_property.includes = includes_freertos_a53;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_a53;
        build_property.templates = templates_freertos_a53ss01;
        build_property.defines = defines_a53_amp;
        build_property.isAmpSHM = true;
    }

    if (buildOption.cpu.match(/m4f*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template];
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
