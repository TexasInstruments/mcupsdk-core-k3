let path = require('path');

let device = "am62px";

const files = {
    common: [
        "test_uart.c",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_uart";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "UART",
        testCaseName: "UART Test Application",
        testCaseIds: "SITSW-1303 SITSW-1304 SITSW-1305 SITSW-8918 SITSW-8919 SITSW-8920 SITSW-8921 SITSW-8924 SITSW-8925 SITSW-8926 " +
             "SITSW-8928 SITSW-8929 SITSW-8930 SITSW-8932 SITSW-8933 SITSW-8934 SITSW-8935 SITSW-8936 SITSW-8938 SITSW-8939 " +
             "SITSW-8940 SITSW-8941 SITSW-8943 SITSW-8944 SITSW-8949 SITSW-8950 SITSW-8951 SITSW-8952 SITSW-8953 SITSW-8954 " +
             "SITSW-8955 SITSW-8956 SITSW-8957 SITSW-8958 SITSW-8959 SITSW-8960 SITSW-8961 SITSW-8962 SITSW-8963 SITSW-8964 " +
             "SITSW-8965 SITSW-8966 SITSW-8967 SITSW-8968 SITSW-8970 SITSW-8971 SITSW-8972 SITSW-8973 SITSW-8974 SITSW-8975 " +
             "SITSW-8976 SITSW-8980 SITSW-8981 SITSW-8983 SITSW-8984 SITSW-8985 SITSW-8986 SITSW-8987 SITSW-8989 SITSW-8990 " +
             "SITSW-8991 SITSW-8992 SITSW-8993 SITSW-8994 SITSW-8995 SITSW-9971 SITSW-9972 SITSW-9973 SITSW-9974 SITSW-9975 " +
             "SITSW-9976 SITSW-9977 SITSW-9978 SITSW-10109 SITSW-10110 SITSW-10111 SITSW-10112 SITSW-10113 SITSW-10114 SITSW-10115 " +
             "SITSW-10116 SITSW-10117 SITSW-10118 SITSW-10119 SITSW-10121 SITSW-10148 SITSW-11621 SITSW-11631 SITSW-11632 SITSW-11633 " +
             "SITSW-11634 SITSW-11636 SITSW-12113 SITSW-12114",
        expectTimeout: 60,
        timeout: 720,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_mcu_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
