let path = require('path');

let device = "am62x";

// Baseline files for NoRTOS cores
const files_nortos = {
    common: [
        "test_ipc_notify.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_ipc_notify.c",
        "test_ipcNotify_multithread.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated:
 * <mcu_plus_sdk>/test/drivers/ipc_notify_m4f/am62x-sk/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",                       /* core_os_combo base (for generated main.c) */
        "../../..",                 /* Example base (ipc_notify_m4f) */
        "../../../../ipc_notify",   /* Shared test source directory */
    ],
};

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
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
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
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

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
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

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_free_rtos = {
    common: [
        "-DIPC_NOTIFY_MULTITHREAD_TEST",
    ],
};

const cflags_nortos = {
    common: [
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

// Master Macro Defines - M4 is the master for all builds
const defines_dm_r5f = {
    common:[
        "SOC_AM62X",
        "ENABLE_SCICLIENT_DIRECT",
        "BUILD_M4F_AS_MASTER",
    ]
}

const defines_common = {
    common:[
        "SOC_AM62X",
        "BUILD_M4F_AS_MASTER",
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
        name: "test_ipc_notify_m4f",
        tag: "freertos_nortos",
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
    property.name = "test_ipc_notify_m4f";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLinuxInSystem = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;
    property.isLDRAEnable = false;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/m4f*/))
    {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_m4f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_m4f;
        build_property.templates = templates_freertos_m4f;
        build_property.defines = defines_common;
        build_property.cflags = cflags_free_rtos;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_r5f;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
        build_property.cflags = cflags_free_rtos;
    }
    else if(buildOption.cpu.match(/a53ss0-0/))
    {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_a53;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_a53;
        build_property.templates = templates_freertos_a53ss00;
        build_property.defines = defines_a53_amp;
        build_property.isAmpSHM = true;
        build_property.cflags = cflags_free_rtos;
    }
    else if(buildOption.cpu.match(/a53ss0-1/))
    {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_a53;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_a53;
        build_property.templates = templates_freertos_a53ss01;
        build_property.defines = defines_a53_amp;
        build_property.isAmpSHM = true;
        build_property.cflags = cflags_free_rtos;
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