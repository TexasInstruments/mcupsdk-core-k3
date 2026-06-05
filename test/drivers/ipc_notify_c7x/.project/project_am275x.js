let path = require('path');

let device = "am275x";

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

const libdirs_freertos = {
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libdirs_freertos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_c75_1 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    }
];

const defines_dm_r5f = {
    common:[
        "SOC_AM275X",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const defines_common = {
    common:[
        "SOC_AM275X",
    ]
};

const defines_c7 = {
    common:[
        "BUILD_C7X_AS_MASTER",
    ]
}

const cflags_free_rtos = {
    common: [
        "-DIPC_NOTIFY_MULTITHREAD_TEST",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "test_ipc_notify_c7x",
        tag: "freertos",
        skipProjectSpec: true,
        board: "am275x-evm",
        projects: [
            { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "c75ss1-0",     cgt: "ti-c7000",     board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "r5fss0-1",     cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "r5fss1-0",     cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "r5fss1-1",     cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
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

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines_c7;
    build_property.cflags = cflags_free_rtos;
    if(buildOption.cpu.match(/r5fss*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;

        if(buildOption.cpu.match("c75ss0-0"))
        {
            build_property.templates = templates_freertos_c75_0;
        }
        else if (buildOption.cpu.match("c75ss1-0"))
        {
            build_property.templates = templates_freertos_c75_1;
        }
    }

    const robot_template = {
        input: ".project/templates/am275x/astra/tests.robot.xdt",
        output: "../tests.robot",
        options: {
            componentName: "IPC",
            testCaseName: "test_ipc_notify_c7x test application",
            appName: "test_ipc_notify_c7x",
            testCaseIds: "SITSW-9372 SITSW-9390 SITSW-9532 SITSW-9533 SITSW-9534 SITSW-9535 SITSW-9536 SITSW-9537 SITSW-9618 SITSW-9639 " +
                 "SITSW-9640 SITSW-9642 SITSW-9643 SITSW-9644 SITSW-9645 SITSW-9646 SITSW-9647 SITSW-9648 SITSW-9649 SITSW-9650 " +
                 "SITSW-9651 SITSW-9652 SITSW-9653 SITSW-9654 SITSW-9655 SITSW-9656 SITSW-9657 SITSW-9761 SITSW-9777 SITSW-9778 " +
                 "SITSW-9779 SITSW-9780 SITSW-9781 SITSW-9782 SITSW-9784 SITSW-9785 SITSW-9786 SITSW-9787 SITSW-9788 SITSW-9789 " +
                 "SITSW-9790 SITSW-9791 SITSW-9792 SITSW-9793 SITSW-9794 SITSW-9795 SITSW-9796 SITSW-9797 SITSW-9798 SITSW-9799 " +
                 "SITSW-9800 SITSW-9801 SITSW-9802 SITSW-9803 SITSW-9804 SITSW-9805 SITSW-9806 SITSW-9807 SITSW-9808 SITSW-9809",
            withCfg: true,
            cfgPath: "test/drivers/ipc_notify_c7x/{board}/ipc_notify_test_sbl_uart_${DEVICE_TYPE}.cfg",
            expectTimeout: 30,
        },
    };

    build_property.templates = [...(build_property.templates || []), robot_template];
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
