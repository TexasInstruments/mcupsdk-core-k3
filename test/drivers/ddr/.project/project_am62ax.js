let path = require('path');

let device = "am62ax";

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

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "sciclient_direct_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const asmfiles_freertos_r5f = {
    common: [
        "vectors_sbl.S",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_freertos_r5f = {
    common: [
        "sciclient_direct_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

/* mcu-r5fss0-0 (MCU domain R5F) configurations */
const includes_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const defines_mcu_r5f = {
    common: [
        "SOC_AM62AX",
        "MCU_R5",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const defines = {
    common:[
        "SOC_AM62AX",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const cflags_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
}

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ddr";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isBootLoader = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_r5f_nortos = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
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
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectPort: "USB2",
        appName: "test_ddr(r5f_nortos)",
        timeout: 1800,
        expectTimeout: 1200,
    },
};

const robot_template_r5f_freertos = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_freertos.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (r5fss0-0, FreeRTOS)",
        testCaseIds: "SITSW-3246 SITSW-3247 SITSW-3248 SITSW-11865 SITSW-11866 SITSW-11867 SITSW-11868 SITSW-11869 SITSW-11870" +
                     " SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877 SITSW-11880 SITSW-11881 SITSW-11882" +
                     " SITSW-11883 SITSW-11884 SITSW-11885 SITSW-11886 SITSW-11887 SITSW-11888 SITSW-11889 SITSW-11890 SITSW-11891 SITSW-11892" +
                     " SITSW-11893 SITSW-11894 SITSW-11895 SITSW-11896 SITSW-11897 SITSW-11898 SITSW-11899 SITSW-11900 SITSW-11901 SITSW-11902" +
                     " SITSW-11903 SITSW-11904 SITSW-11905 SITSW-11906 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915" +
                     " SITSW-11916 SITSW-11917 SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11921 SITSW-11922 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11927 SITSW-11928 SITSW-11929 SITSW-11930 SITSW-11931 SITSW-11932 SITSW-11933 SITSW-11934 SITSW-11935 SITSW-11936" +
                     " SITSW-11937 SITSW-11938",
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectPort: "USB2",
        appName: "test_ddr(r5f_freertos)",
        timeout: 1800,
        expectTimeout: 1200,
    },
};

const robot_template_mcu_r5f_nortos = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_mcu.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (mcu-r5fss0-0, No RTOS)",
        testCaseIds: "SITSW-11869 SITSW-11870 SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877" +
                     " SITSW-11903 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915 SITSW-11916" +
                     " SITSW-11917 SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11921 SITSW-11922 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11928 SITSW-11931 SITSW-11932 SITSW-11938",
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectPort: "USB3",
        appName: "test_ddr(mcu_nortos)",
        timeout: 1200,
        expectTimeout: 600,
    },
};

const robot_template_mcu_r5f_freertos = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_mcu_freertos.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR: Memory and ECC tests (mcu-r5fss0-0, FreeRTOS)",
        testCaseIds: "SITSW-11869 SITSW-11870 SITSW-11871 SITSW-11872 SITSW-11873 SITSW-11874 SITSW-11875 SITSW-11876 SITSW-11877" +
                     " SITSW-11903 SITSW-11907 SITSW-11908 SITSW-11909 SITSW-11913 SITSW-11914 SITSW-11915 SITSW-11916" +
                     " SITSW-11917 SITSW-11918 SITSW-11919 SITSW-11920 SITSW-11921 SITSW-11922 SITSW-11923 SITSW-11924 SITSW-11925" +
                     " SITSW-11928 SITSW-11931 SITSW-11932 SITSW-11938",
        cfgPath: "test/drivers/ddr/{board}/{coreName}/default_test_ddr_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectPort: "USB3",
        appName: "test_ddr(mcu_freertos)",
        timeout: 1200,
        expectTimeout: 600,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.includes = includes;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        /* MCU domain R5F: DDR already initialized by DM-R5F */
        build_property.isBootLoader = false;
        build_property.includes = includes_nortos_mcu_r5f;
        build_property.libdirs = libdirs_nortos_mcu_r5f;
        build_property.libs = libs_nortos_mcu_r5f;
        build_property.defines = defines_mcu_r5f;

        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_mcu_r5f;
            build_property.libdirs = libdirs_freertos_mcu_r5f;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.files = files_freertos;
            build_property.cflags = cflags_freertos;
            build_property.templates = [...(build_property.templates || []), robot_template_mcu_r5f_freertos];
        } else {
            build_property.templates = [...(build_property.templates || []), robot_template_mcu_r5f_nortos];
        }
    } else if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;

        if(buildOption.os.match(/freertos*/))
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.libsprebuild = libs_prebuild_freertos_r5f;
            build_property.asmfiles = asmfiles_freertos_r5f;
            build_property.files = files_freertos;
            build_property.cflags = cflags_freertos;
            build_property.templates = [...(build_property.templates || []), robot_template_r5f_freertos];
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
