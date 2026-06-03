let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "test_ipc_notify.c",
        "test_ipcNotify_multithread.c",
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
        "../../../../ipc_notify",
    ],
};


const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_dm_r5f = {
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

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const libs_freertos_dm_r5f = {
    common: [
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const libs_nortos_a53 = {
    common: [
        "nortos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62ax.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const cflags_free_rtos = {
    common: [
        "-DIPC_NOTIFY_MULTITHREAD_TEST",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62ax/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62ax/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 16*1024,
        },
    }
];

const defines_dm_r5f = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "BUILD_C7X_AS_MASTER",
    ]
}

const defines_r5 = {
    common:[
        "BUILD_C7X_AS_MASTER",
    ]
}

const defines_a53 = {
    common:[
        "BUILD_C7X_AS_MASTER",
    ]
}

const defines_c7 = {
    common:[
        "BUILD_C7X_AS_MASTER",
    ]
}

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62ax-sk", os: "nortos",   isPartOfSystemProject: true},
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62ax-sk", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "test_ipc_notify_c7x",
        tag: "freertos_nortos",
        skipProjectSpec: true,
        board: "am62ax-sk",
        projects: [
            { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos", isPartOfSystemProject: false},
            { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62ax-sk", os: "nortos",   isPartOfSystemProject: true},
            { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62ax-sk", os: "freertos", isPartOfSystemProject: true},
        ],
    },
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ipc_notify_c7x";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLinuxInSystem = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;
    property.isLDRAEnable = false;

    return property;
}



const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "test_ipc_notify_c7x test application",
        appName: "test_ipc_notify_c7x",
        testCaseIds: "SITSW-9372 SITSW-9390 SITSW-9532 SITSW-9533 SITSW-9534 SITSW-9535 SITSW-9536 SITSW-9537 SITSW-9618 SITSW-9639 " +
             "SITSW-9640 SITSW-9642 SITSW-9643 SITSW-9644 SITSW-9645 SITSW-9646 SITSW-9647 SITSW-9648 SITSW-9649 SITSW-9650 " +
             "SITSW-9651 SITSW-9652 SITSW-9653 SITSW-9654 SITSW-9655 SITSW-9656 SITSW-9657 SITSW-9756 SITSW-9761 SITSW-9777 " +
             "SITSW-9778 SITSW-9779 SITSW-9780 SITSW-9781 SITSW-9782 SITSW-9784 SITSW-9785 SITSW-9786 SITSW-9787 SITSW-9788 " +
             "SITSW-9789 SITSW-9790 SITSW-9791 SITSW-9792 SITSW-9793 SITSW-9794 SITSW-9795 SITSW-9796 SITSW-9797 SITSW-9798 " +
             "SITSW-9799 SITSW-9800 SITSW-9801 SITSW-9802 SITSW-9803 SITSW-9804 SITSW-9805 SITSW-9806 SITSW-9807 SITSW-9808 " +
             "SITSW-9809",
        withCfg: true,
        cfgPath: "test/drivers/ipc_notify_c7x/{board}/ipc_notify_test_sbl_uart_${DEVICE_TYPE}.cfg",
        expectTimeout: 30,
    },
};
function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_mcu_r5f;
        build_property.libs = libs_freertos_mcu_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
        build_property.defines = defines_r5;
        build_property.cflags = cflags_free_rtos;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_dm_r5f;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
        build_property.cflags = cflags_free_rtos;
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.libs = libs_nortos_a53;
        build_property.templates = templates_nortos_a53;
        build_property.includes  = includes_a53;
        build_property.defines = defines_a53;
    }
    else if(buildOption.cpu.match(/c75*/))
    {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos_c75;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
        build_property.defines = defines_c7;
        build_property.cflags = cflags_free_rtos;
    }
    
    if (buildOption.cpu === "c75ss0-0") {
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
