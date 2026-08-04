let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_rtc.c",
        "main.c",
    ],
};

const defines_r5f_freertos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "ENABLE_MT_TESTS",
    ]
}

const defines_r5f_nortos = {
    common:[
        "SOC_AM62X",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const defines_a53_freertos = {
    common:[
        "ENABLE_MT_TESTS",
    ]
};

const defines_a53_nortos = {
    common:[
        "SOC_AM62X",
    ]
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* Board base */
        "../../..", /* Example base */
    ],
};

const filedirs_nortos_a53 = {
    common: [
        "..",
        "../..",
        "../../..",
    ],
};

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_dm_r5f = {
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

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_r5f = {
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
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const libs_dm_r5f = {
    common: [
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const libs_nortos_dm_r5f = {
    common: [
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function",
    ]
}

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_dm_r5f =
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
            globalScratchBuf: "true",
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

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
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

const templates_nortos_dm_r5f =
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
            globalScratchBuf: "true",
        },
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk",     os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp",  os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk",     os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp",  os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk",     os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp",  os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk",     os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp",  os: "nortos"},
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

const robot_template_common_options = {
    componentName: "RTC",
    testCaseName: "RTC Test Application",
    appName: "test_rtc",
    testCaseIds: "SITSW-5822 SITSW-5823 SITSW-5824 SITSW-11800 SITSW-11801 SITSW-11802 SITSW-11803 SITSW-11804 SITSW-11805 SITSW-11806 " +
                 "SITSW-11807 SITSW-11808 SITSW-11809 SITSW-11810 SITSW-11811 SITSW-11812 SITSW-11813 SITSW-11814 SITSW-11815 SITSW-11816 " +
                 "SITSW-11817 SITSW-11819 SITSW-11820 SITSW-11821 SITSW-11822 SITSW-11823 SITSW-11824 SITSW-11825 SITSW-11826 SITSW-11827 " +
                 "SITSW-11828 SITSW-11829 SITSW-11830 SITSW-11831 SITSW-11833 SITSW-11834 SITSW-11837 SITSW-11838 SITSW-11839 SITSW-11840 " +
                 "SITSW-11841 SITSW-11843 SITSW-11846 SITSW-11849",
        withCfg: true,
        cfgPath: "test/drivers/rtc/{board}/{coreName}/default_test_rtc_${DEVICE_TYPE}.cfg",
        appName: "test_rtc",
        expectTimeout: 1800,
        timeout: 9000,
};

const robot_template_nor      = { input: ".project/templates/am62x/astra/tests_sbl.robot.xdt", output: "../tests.robot",
    options: { ...robot_template_common_options, bootMode: "OSPI_NOR_BOOT_MODE",  expectPort: "USB2" } };
const robot_template_nand     = { input: ".project/templates/am62x/astra/tests_sbl.robot.xdt", output: "../tests.robot",
    options: { ...robot_template_common_options, bootMode: "OSPI_NAND_BOOT_MODE", expectPort: "USB2" } };
const robot_template_a53_nor  = { input: ".project/templates/am62x/astra/tests_sbl.robot.xdt", output: "../tests.robot",
    options: { ...robot_template_common_options, bootMode: "OSPI_NOR_BOOT_MODE",  expectPort: "USB0" } };
const robot_template_a53_nand = { input: ".project/templates/am62x/astra/tests_sbl.robot.xdt", output: "../tests.robot",
    options: { ...robot_template_common_options, bootMode: "OSPI_NAND_BOOT_MODE", expectPort: "USB0" } };

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.files = files;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os === "nortos") {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.libdirs = libdirs_nortos_r5f;
            build_property.templates = templates_nortos_dm_r5f;
            build_property.defines = defines_r5f_nortos;
        } else {
            build_property.includes = includes_r5f;
            build_property.libs = libs_dm_r5f;
            build_property.libdirs = libdirs_dm_r5f;
            build_property.templates = templates_dm_r5f;
            build_property.defines = defines_r5f_freertos;
        }
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.cflags = cflags_a53;
        if(buildOption.os === "nortos") {
            build_property.filedirs = filedirs_nortos_a53;
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.defines = defines_a53_nortos;
        } else {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.defines = defines_a53_freertos;
        }
    }


    const isLP  = buildOption.board === "am62x-sk-lp";
    const isA53 = buildOption.cpu.match(/a53*/);
    let robot_template;
    if      (isA53 && isLP)  robot_template = robot_template_a53_nand;
    else if (isA53)          robot_template = robot_template_a53_nor;
    else if (isLP)           robot_template = robot_template_nand;
    else                     robot_template = robot_template_nor;
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
