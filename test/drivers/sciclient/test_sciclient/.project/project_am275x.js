let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_sciclient_intr_polling.c",
        "test_sciclient_lpm.c",
        "test_sciclient_pm.c",
        "test_sciclient_rm.c",
        "test_sciclient_sec.c",
        "test_sciclient_wrapper.c",
        "test_sciclient_procboot.c",
        "test_sciclient.c",
        "main.c",
    ],
};

const files_rtos = {
    common: [
        "test_sciclient_intr_polling.c",
        "test_sciclient_lpm.c",
        "test_sciclient_pm.c",
        "test_sciclient_rm.c",
        "test_sciclient_sec.c",
        "test_sciclient_wrapper.c",
        "test_sciclient_procboot.c",
        "test_sciclient_multithread.c",
        "test_sciclient.c",
        "main.c",
    ],
};

const defines_common = {
    common: [
        "SOC_AM275X",
        "SCICLIENT_INTERRUPT_MODE",
    ],
};

const defines_c7 = {
    common: [
        "CORE_C7",
        "SOC_AM275X",
        "SCICLIENT_INTERRUPT_MODE",
    ],
};

/* None of this project's AM275X build targets link against
 * sciclient_direct.lib (that library is only built for the wkup-r5f
 * core, which this project does not target), so the
 * Sciclient_boardCfg/getDKEK/direct_getDMVersion/etc. direct-API test
 * sections must be excluded via -DSKIP_SCICLIENT, same as AM62DX does
 * for its non-DM cores (see project_am62dx.js nortos_cflags/freertos_cflags). */
const cflags_rtos = {
    common: [
        "-DSCICLIENT_MULTITHREAD",
        "-DSKIP_SCICLIENT",
    ],
};

const cflags_nortos = {
    common: [
        "-DSKIP_SCICLIENT",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Board base */
        "../../../..", /* Example base */
    ],
};

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
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

const libs_nortos_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_DEVICE_MANAGER";

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

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_c75ss0 =
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
            stackSize: 16*1024,
        },
    }
];

const templates_freertos_c75ss1 =
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
            stackSize: 16*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_functional_sciclient";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

/* SITSW-12080/12216/12217/12214 never run (SKIP_SCICLIENT always defined for this device).
 * SITSW-12457 never runs on AM275X (guarded off via `#if !(SOC_AM275X || CORE_A53)`).
 * SITSW-1245x multithread IDs only run under SCICLIENT_MULTITHREAD (freertos only). */
const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Sciclient",
        testCaseIds: "SITSW-12478 SITSW-12476 SITSW-12475 SITSW-12474 SITSW-12473 SITSW-12472 SITSW-12471 SITSW-12470" +
                     " SITSW-12469 SITSW-12468 SITSW-12467 SITSW-12466 SITSW-12464 SITSW-12463 SITSW-12462 SITSW-12454" +
                     " SITSW-12453 SITSW-12452 SITSW-12486 SITSW-12460 SITSW-12461 SITSW-12459 SITSW-12477 SITSW-12458" +
                     " SITSW-12456",
    },
};

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Sciclient",
        testCaseIds: "SITSW-12478 SITSW-12476 SITSW-12475 SITSW-12474 SITSW-12473 SITSW-12472 SITSW-12471 SITSW-12470" +
                     " SITSW-12469 SITSW-12468 SITSW-12467 SITSW-12466 SITSW-12464 SITSW-12463 SITSW-12462 SITSW-12454" +
                     " SITSW-12453 SITSW-12452 SITSW-12486 SITSW-12460 SITSW-12461 SITSW-12459 SITSW-12477 SITSW-12458" +
                     " SITSW-12456 SITSW-12451 SITSW-12450 SITSW-12449 SITSW-12448 SITSW-12447 SITSW-12446 SITSW-12481",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5fss*/)) {
        build_property.defines = defines_common;
        if(buildOption.os.match(/nortos/)) {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.libdirs = libdirs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.cflags = cflags_nortos;
        }
        else {
            build_property.includes = includes_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_rtos;
            build_property.files = files_rtos;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libs = libs_freertos_c75;
        build_property.libdirs = libdirs_freertos_c75;
        build_property.defines = defines_c7;
        build_property.cflags = cflags_rtos;
        build_property.files = files_rtos;
        if(buildOption.cpu.match("c75ss0-0")) {
            build_property.templates = templates_freertos_c75ss0;
        }
        else if(buildOption.cpu.match("c75ss1-0")) {
            build_property.templates = templates_freertos_c75ss1;
        }
    }

    const robot_template = buildOption.os.match(/nortos/) ? robot_template_nortos : robot_template_freertos;
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
