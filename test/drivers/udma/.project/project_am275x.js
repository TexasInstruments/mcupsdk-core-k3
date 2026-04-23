let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_udma.c",
        "main.c",
        "udma_test_blkcpy.c",
        "udma_test_bug.c",
        "udma_test_ch.c",
        "udma_test_common.c",
        "udma_test_event.c",
        "udma_test_flow.c",
        "udma_test_misc.c",
        "udma_test_parser.c",
        "udma_test_ring.c",
        "utils_mem_baremetal.c",
        "utils_prf_baremetal.c",
        "utils_trace.c",
        "udma_test_soc.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",
        "../..",
        "../../..",
        "../../../..",
        "../../../soc/am275x"
    ],
};

const includes_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am275x",
    ],
};

const includes_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am275x",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am275x",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_nortos_dm_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f_freertos = {
    common:[
        "ENABLE_MT_TESTS"
    ]
}

const defines_wkupr5_freertos = {
    common:[
        "ENABLE_MT_TESTS",
	    "ENABLE_SCICLIENT_DIRECT"
    ]
}

const syscfgfile = "../example.syscfg";

const templates_nortos_dm_r5f =
[
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    },
];

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const robot_test_case_ids_nortos =
    "SITSW-8237 SITSW-8238 SITSW-8239 SITSW-8240 SITSW-8242 SITSW-8243 SITSW-8244 SITSW-8248 SITSW-8249 SITSW-8274 " +
    "SITSW-8250 SITSW-8251 SITSW-8252 SITSW-8275 SITSW-8276 SITSW-8278 SITSW-8279 SITSW-8280 SITSW-8285 SITSW-8287 " +
    "SITSW-8288 SITSW-8290 SITSW-8291 SITSW-8292 SITSW-8293 SITSW-8295 SITSW-8296 SITSW-8297 SITSW-8298 SITSW-8300 " +
    "SITSW-8301 SITSW-8304 SITSW-8595 SITSW-8596 SITSW-8598 SITSW-8599 SITSW-8600 SITSW-8601 SITSW-8604 SITSW-8605 " +
    "SITSW-8606 SITSW-8607 SITSW-8609 SITSW-8610 SITSW-8611 SITSW-8612 SITSW-8614 SITSW-8615 SITSW-8617 SITSW-8765 " +
    "SITSW-8767 SITSW-8768 SITSW-8769 SITSW-8770 SITSW-8771 SITSW-8772 SITSW-8773 SITSW-8774 SITSW-8775 SITSW-8776 " +
    "SITSW-8778 SITSW-8777 SITSW-8247 SITSW-8766 SITSW-8603 SITSW-8616 SITSW-9135 SITSW-9137 SITSW-9138 SITSW-9140 " +
    "SITSW-9141 SITSW-9142 SITSW-8289 SITSW-11048 SITSW-11049 SITSW-11050 SITSW-11051 SITSW-11052 SITSW-11053 SITSW-11054 " +
    "SITSW-11055 SITSW-11056 SITSW-11057 SITSW-11058 SITSW-11059 SITSW-11060 SITSW-11061 SITSW-11062 SITSW-11063 SITSW-11064 " +
    "SITSW-11065 SITSW-11066 SITSW-11069 SITSW-11070";

const robot_test_case_ids_freertos = robot_test_case_ids_nortos +
    " SITSW-8618 SITSW-9250 SITSW-9251 SITSW-9252";
const robot_test_case_ids_wkup_freertos = robot_test_case_ids_nortos.replace(" SITSW-8607", "") +
    " SITSW-8618 SITSW-9250 SITSW-9251 SITSW-9252";

function getRobotTemplate(testCaseIds) {
    return {
        input: ".project/templates/am275x/astra/tests.robot.xdt",
        output: "../tests.robot",
        options: {
            componentName: "UDMA",
            testCaseName: "UDMA Test Application",
            appName: "test_udma",
            testCaseIds: testCaseIds,
            expectTimeout: 500,
            timeout: 900,
        },
    };
}

const robot_templates = {
    "r5fss0-0_nortos": getRobotTemplate(robot_test_case_ids_nortos),
    "r5fss0-0_freertos": getRobotTemplate(robot_test_case_ids_freertos),
    "r5fss0-1_nortos": getRobotTemplate(robot_test_case_ids_nortos),
    "r5fss0-1_freertos": getRobotTemplate(robot_test_case_ids_freertos),
    "r5fss1-0_nortos": getRobotTemplate(robot_test_case_ids_nortos),
    "r5fss1-0_freertos": getRobotTemplate(robot_test_case_ids_freertos),
    "r5fss1-1_nortos": getRobotTemplate(robot_test_case_ids_nortos),
    "r5fss1-1_freertos": getRobotTemplate(robot_test_case_ids_freertos),
    "wkup-r5fss0-0_freertos": getRobotTemplate(robot_test_case_ids_wkup_freertos),
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},

];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_udma";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_udma";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.isBootLoader = true;
    property.skipProjectSpec = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    if(buildOption.cpu.match(/wkup-r5fss0-0*/)) {
        if(buildOption.os.match(/freertos*/))
        {
            build_property.defines = defines_wkupr5_freertos;
            build_property.includes = includes_freertos_wkup_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.templates = templates_nortos_dm_r5f;
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.defines = defines_dm_r5f_freertos;
            build_property.includes = includes_freertos_dm_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_dm_r5f;
        }
    }

    const robot_template_key = `${buildOption.cpu}_${buildOption.os}`;
    build_property.templates = [...(build_property.templates || []), robot_templates[robot_template_key]];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
