let path = require('path');

let device = "am62px";

const files = {
    common: [
        "test_mcan.c",
        "test_mcanCommon.c",
        "test_mcanTxApp.c",
        "main.c",
        "test_mcan_multithread.c",
        "mcan_transceiver.c"
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

const libdirs_freertos_wkup_r5f = {
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/mcan/",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_common = {
    common:[
        "SOC_AM62PX",
    ]
};

const defines_r5_freertos = {
    common:[
        "SOC_AM62PX",
        "R5_FREERTOS_CORE",
        "FREERTOS_CORE",
        "MCU_FREERTOS_CORE",
    ]
};

const defines_wkup_r5f_freertos = {
    common:[
        "SOC_AM62PX",
        "R5_FREERTOS_CORE",
        "ENABLE_SCICLIENT_DIRECT",
        "FREERTOS_CORE",
    ]
};

const syscfgfile = "../example.syscfg"


const templates_nortos_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_r5f =
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

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcan";
    property.description = "test_mcan";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCAN",
        testCaseName: "MCAN: Rx FIFO 0 Message Lost Interrupt Test",
        testCaseIds: "SITSW-10222 SITSW-10223 SITSW-10224 SITSW-10225 SITSW-10226 SITSW-10227 SITSW-10228 SITSW-10229 SITSW-10230 SITSW-10231" +
                     " SITSW-10232 SITSW-10233 SITSW-10234 SITSW-10235 SITSW-10236 SITSW-10237 SITSW-10238 SITSW-10239 SITSW-10240 SITSW-10241" +
                     " SITSW-10242 SITSW-10243 SITSW-10244 SITSW-10245 SITSW-10246 SITSW-10247 SITSW-10248 SITSW-10249 SITSW-10250 SITSW-10251" +
                     " SITSW-10253 SITSW-10254 SITSW-10271 SITSW-10272 SITSW-10273 SITSW-10274 SITSW-10275 SITSW-11863" +
                     " SITSW-10477 SITSW-10478 SITSW-10479 SITSW-10480 SITSW-10481 SITSW-10482 SITSW-10483 SITSW-10484 SITSW-10485 SITSW-10486" +
                     " SITSW-10487 SITSW-10488 SITSW-10489 SITSW-10490 SITSW-10868" +
                     " SITSW-10869 SITSW-10870 SITSW-10871 SITSW-10872 SITSW-10875",
        expectTimeout: 120,
        timeout: 660,
    },
};

/* FreeRTOS template: includes multithread test IDs (guarded by #if defined(FREERTOS_CORE) in source).
 * Excludes SITSW-10233/10234/10235 which are guarded by #if !defined(R5_FREERTOS_CORE) and
 * SITSW-11863 which is not applicable to R5F FreeRTOS builds. */
const robot_template_freertos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests_freertos.robot",
    options: {
        componentName: "MCAN",
        testCaseName: "MCAN: Rx FIFO 0 Message Lost Interrupt Test",
        testCaseIds: "SITSW-10222 SITSW-10223 SITSW-10224 SITSW-10225 SITSW-10226 SITSW-10227 SITSW-10228 SITSW-10229 SITSW-10230 SITSW-10231" +
                     " SITSW-10232 SITSW-10236 SITSW-10237 SITSW-10238 SITSW-10239 SITSW-10240 SITSW-10241" +
                     " SITSW-10242 SITSW-10243 SITSW-10244 SITSW-10245 SITSW-10246 SITSW-10247 SITSW-10248 SITSW-10249 SITSW-10250 SITSW-10251" +
                     " SITSW-10253 SITSW-10254 SITSW-10271 SITSW-10272 SITSW-10273 SITSW-10274 SITSW-10275" +
                     " SITSW-10477 SITSW-10478 SITSW-10479 SITSW-10480 SITSW-10481 SITSW-10482 SITSW-10483 SITSW-10484 SITSW-10485 SITSW-10486" +
                     " SITSW-10487 SITSW-10488 SITSW-10489 SITSW-10490 SITSW-10491 SITSW-10492 SITSW-10493 SITSW-10494 SITSW-10495 SITSW-10868" +
                     " SITSW-10869 SITSW-10870 SITSW-10871 SITSW-10872 SITSW-10874 SITSW-10875",
        expectTimeout: 120,
        timeout: 660,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines_common;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.defines = defines_r5_freertos;
        }
        else
        {
            build_property.includes = includes;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }
    else if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_wkup_r5f;
        build_property.libs = libs_freertos_wkup_r5f;
        build_property.templates = templates_freertos_wkup_r5f;
        build_property.defines = defines_wkup_r5f_freertos;
    }

    if(buildOption.os.match(/freertos*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    } else {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
