let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_ipc_rpmsg.c",
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
        "../../../../ipc_rpmsg",
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

const libdirs_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
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

const includes_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
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

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
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

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_mcu-r5f.cmd.xdt",
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

const templates_freertos_m4f =
[
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
            entryFunction: "test_main",
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
            entryFunction: "test_main",
        },
    }
];

const defines_dm_r5f = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "BUILD_A53_AS_MASTER",
    ]
}

const defines_r5 = {
    common:[
        "BUILD_A53_AS_MASTER",
    ]
}

const defines_a53 = {
    common:[
        "BUILD_A53_AS_MASTER",
    ]
}

const defines_m4 = {
    common:[
        "BUILD_A53_AS_MASTER",
        "BUILD_M4F",
    ]
}

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects = [
    {
        name: "test_ipc_rpmsg_a53",
        tag: "freertos",
        skipProjectSpec: true,
        board: "am62x-sk",
        projects: [
            { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos", isPartOfSystemProject: false},
            { device: device, cpu: "m4fss0-0",     cgt: "ti-arm-clang",     board: "am62x-sk", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos",   isPartOfSystemProject: true},
            { device: device, cpu: "a53ss0-1",     cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos",   isPartOfSystemProject: true},
        ],
    },
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ipc_rpmsg_a53";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.ipcVringRTOS = true;
    property.isLogSHM = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "IPC RPMSG: A53SS0_0 to R5FSS0_0 with varying messages sizes",
        testCaseIds: "SITSW-2458 SITSW-2463 SITSW-2464 SITSW-5649 SITSW-5671 SITSW-8000 SITSW-9730 SITSW-9813 SITSW-9814 SITSW-9815" +
                     " SITSW-9816 SITSW-9817 SITSW-9818 SITSW-9819 SITSW-9820 SITSW-9821 SITSW-9822 SITSW-9823 SITSW-9824 SITSW-12714" +
                     " SITSW-12762 SITSW-12763 SITSW-12764 SITSW-12765 SITSW-12766 SITSW-12767 SITSW-12768",
        withCfg: true,
        appName: "test_ipc_rpmsg_a53",
        cfgPath: "test/drivers/ipc_rpmsg_a53/{board}/ipc_rpmsg_test_sbl_uart_${DEVICE_TYPE}.cfg",
        expectTimeout: 500,
        timeout: 900,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_freertos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.includes = includes_freertos_r5f;
        build_property.libs = libs_freertos_mcu_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
        build_property.defines = defines_r5;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_dm_r5f;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
    }
    else if(buildOption.cpu.match(/m4f*/))
    {
        build_property.includes = includes_freertos_m4f;
        build_property.libs = libs_freertos_m4f;
        build_property.templates = templates_freertos_m4f;
        build_property.defines = defines_m4;
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.includes = includes_freertos_a53;
        build_property.libs = libs_freertos_a53;
        build_property.defines = defines_a53;
        if(buildOption.cpu.match(/a53ss0-0/))
            build_property.templates = templates_freertos_a53ss00;
        else if(buildOption.cpu.match(/a53ss0-1/))
            build_property.templates = templates_freertos_a53ss01;
    }

    // cfg boots all cores; only a53ss0-0 (master) needs robot test
    if (buildOption.cpu.match("a53ss0-0")) {
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
