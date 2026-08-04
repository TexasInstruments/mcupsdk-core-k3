let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "test_rtc.c",
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
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

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const libs_nortos_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_nortos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_prebuild_nortos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
    ],
};

const libdirs_freertos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_prebuild_nortos_r5 = {
    common: [
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_nortos_dm_r5f = {
    common: [
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f_freertos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "ENABLE_MT_TESTS",
    ]
}

const defines_dm_r5f_nortos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const defines_mcu_r5f_freertos = {
    common:[
        "ENABLE_MT_TESTS",
    ]
};

const defines_mcu_r5f_nortos = {
    common:[
    ]
};

const syscfgfile = "../example.syscfg";

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

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

const templates_nortos_dm_r5f =
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
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
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

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_rtc";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_mcu_r5f = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "RTC",
        testCaseName: "RTC Test Application",
        testCaseIds: "SITSW-5822 SITSW-5823 SITSW-5824 SITSW-11800 SITSW-11801 SITSW-11802 SITSW-11803 SITSW-11804 SITSW-11805 SITSW-11806 " +
                     "SITSW-11807 SITSW-11808 SITSW-11809 SITSW-11810 SITSW-11811 SITSW-11812 SITSW-11813 SITSW-11814 SITSW-11815 SITSW-11816 " +
                     "SITSW-11817 SITSW-11818 SITSW-11819 SITSW-11820 SITSW-11821 SITSW-11822 SITSW-11823 SITSW-11824 SITSW-11825 SITSW-11826 " +
                     "SITSW-11827 SITSW-11828 SITSW-11829 SITSW-11830 SITSW-11831 SITSW-11832 SITSW-11833 SITSW-11834 SITSW-11835 SITSW-11836 " +
                     "SITSW-11837 SITSW-11838 SITSW-11839 SITSW-11840 SITSW-11841 SITSW-11842 SITSW-11843 SITSW-11844 SITSW-11845 SITSW-11846 " +
                     "SITSW-11847 SITSW-11848 SITSW-11849",
        withCfg: true,
        cfgPath: "test/drivers/rtc/{board}/{coreName}/default_test_rtc_${DEVICE_TYPE}.cfg",
        appName: "test_rtc",
        expectPort: "USB3",
        expectTimeout: 1800,
        timeout: 9000,
    },
};

const robot_template_r5f = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "RTC",
        testCaseName: "RTC Test Application",
        testCaseIds: "SITSW-5822 SITSW-5823 SITSW-5824 SITSW-11800 SITSW-11801 SITSW-11802 SITSW-11803 SITSW-11804 SITSW-11805 SITSW-11806 " +
                     "SITSW-11807 SITSW-11808 SITSW-11809 SITSW-11810 SITSW-11811 SITSW-11812 SITSW-11813 SITSW-11814 SITSW-11815 SITSW-11816 " +
                     "SITSW-11817 SITSW-11818 SITSW-11819 SITSW-11820 SITSW-11821 SITSW-11822 SITSW-11823 SITSW-11824 SITSW-11825 SITSW-11826 " +
                     "SITSW-11827 SITSW-11828 SITSW-11829 SITSW-11830 SITSW-11831 SITSW-11832 SITSW-11833 SITSW-11834 SITSW-11835 SITSW-11836 " +
                     "SITSW-11837 SITSW-11838 SITSW-11839 SITSW-11840 SITSW-11841 SITSW-11842 SITSW-11843 SITSW-11844 SITSW-11845 SITSW-11846 " +
                     "SITSW-11847 SITSW-11848 SITSW-11849",
        withCfg: true,
        cfgPath: "test/drivers/rtc/{board}/{coreName}/default_test_rtc_${DEVICE_TYPE}.cfg",
        appName: "test_rtc",
        expectPort: "USB2",
        expectTimeout: 1800,
        timeout: 9000,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.defines = defines_mcu_r5f_freertos;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.defines = defines_mcu_r5f_nortos;
        }
        build_property.templates = [...(build_property.templates || []), robot_template_mcu_r5f];
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_dm_r5f;
            build_property.defines = defines_dm_r5f_freertos;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libdirs = libdirs_nortos_r5;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.libdirsprebuild = libdirs_prebuild_nortos_r5;
            build_property.libsprebuild = libs_prebuild_nortos_r5;
            build_property.templates = templates_nortos_dm_r5f;
            build_property.defines = defines_dm_r5f_nortos;
        }
        build_property.templates = [...(build_property.templates || []), robot_template_r5f];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
