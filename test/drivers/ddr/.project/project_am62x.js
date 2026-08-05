let path = require('path');

let device = "am62x";

const files = {
    common: [
        "main.c",
        "test_ddr.c",
    ],
};

const files_freertos = {
    common: [
        "main.c",
        "test_ddr.c",
        "test_ddr_mt.c",
    ],
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

/* r5fss0-0 (DM-R5F) - inline DM libs, appimage output */
const includes_r5f = {
    common: [
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

const libdirs_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
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

const libdirs_freertos_r5f = {
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

const libs_nortos_r5f = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const defines_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

/* m4fss0-0 (secondary M4F core) - appimage output, DDR already initialised by SBL */
const includes_m4f = {
    common: [
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

const libdirs_nortos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_nortos_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const defines_m4f = {
    common: [
        "M4F_CORE",
    ],
};

const cflags_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
];

const robot_template_r5f_nortos = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (r5fss0-0, No RTOS)",
        testCaseIds: "SITSW-3246 SITSW-3247 SITSW-3248 SITSW-11865 SITSW-11866 SITSW-11867 SITSW-11868 SITSW-11869 SITSW-11870" +
                     " SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877 SITSW-11880 SITSW-11881 SITSW-11882" +
                     " SITSW-11883 SITSW-11884 SITSW-11885 SITSW-11886 SITSW-11887 SITSW-11888 SITSW-11889 SITSW-11890 SITSW-11891 SITSW-11892" +
                     " SITSW-11893 SITSW-11894 SITSW-11895 SITSW-11896 SITSW-11897 SITSW-11898 SITSW-11899 SITSW-11900 SITSW-11901 SITSW-11902" +
                     " SITSW-11903 SITSW-11904 SITSW-11905 SITSW-11906 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915" +
                     " SITSW-11916 SITSW-11917 SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11921 SITSW-11922 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11927 SITSW-11928 SITSW-11929 SITSW-11930 SITSW-11931 SITSW-11932 SITSW-11938",
        withCfg: true,
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        expectPort: "USB2",
        appName: "test_ddr(r5f_nortos)",
        timeout: 1800,
        expectTimeout: 1200,
    },
};

const robot_template_m4f_nortos = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests_m4f.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (m4fss0-0, No RTOS)",
        testCaseIds: "SITSW-11869 SITSW-11870 SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877" +
                     " SITSW-11903 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915 SITSW-11916" +
                     " SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11928 SITSW-11931 SITSW-11932",
        withCfg: true,
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        expectPort: "USB3",
        appName: "test_ddr(m4f_nortos)",
        timeout: 1200,
        expectTimeout: 600,
    },
};

const robot_template_m4f_freertos = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests_m4f_freertos.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (m4fss0-0, FreeRTOS)",
        testCaseIds: "SITSW-11869 SITSW-11870 SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877" +
                     " SITSW-11903 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915 SITSW-11916" +
                     " SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11928 SITSW-11931 SITSW-11932 SITSW-11937",
        withCfg: true,
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        expectPort: "USB3",
        appName: "test_ddr(m4f_freertos)",
        timeout: 1200,
        expectTimeout: 600,
    },
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ddr";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isBootLoader = false; /* all am62x combos produce appimage, not tiimage */
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/m4fss0-0/)) {
        /* M4F: DDR already initialised by SBL before this appimage is loaded */
        build_property.includes = includes_m4f;
        build_property.libdirs = libdirs_nortos_m4f;
        build_property.libs = libs_nortos_m4f;
        build_property.defines = defines_m4f;

        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_m4f;
            build_property.libdirs = libdirs_freertos_m4f;
            build_property.libs = libs_freertos_m4f;
            build_property.files = files_freertos;
            build_property.cflags = cflags_freertos;
            build_property.templates = [...(build_property.templates || []), robot_template_m4f_freertos];
        } else {
            build_property.templates = [...(build_property.templates || []), robot_template_m4f_nortos];
        }
    } else if(buildOption.cpu.match(/r5fss0-0/)) {
        /* r5fss0-0: DM-R5F, runs as DM appimage, inline DM libs */
        build_property.includes = includes_r5f;
        build_property.libdirs = libdirs_nortos_r5f;
        build_property.libs = libs_nortos_r5f;
        build_property.defines = defines_r5f;

        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.files = files_freertos;
            build_property.cflags = cflags_freertos;
        } else {
            build_property.templates = [...(build_property.templates || []), robot_template_r5f_nortos];
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
