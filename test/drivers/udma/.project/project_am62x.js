let path = require('path');

let device = "am62x";

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

const files_smp = {
    common: [
        "test_udma_smp.c",
        "main.c",
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
        "../../../..",
        "../../../soc/am62x"
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62x/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62x/",
    ],
};

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62x/",
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

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
    ],
};

const libdirs_nortos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_freertos_dm_r5f = {
    common: [
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

/*
 * A53 support for AM62x
 */
const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f_nortos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "SOC_AM62X"
    ]
};

const defines_dm_r5f_freertos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "SOC_AM62X",
        "ENABLE_MT_TESTS"
    ]
};

const defines_a53_freertos = {
    common:[
        "ENABLE_MT_TESTS",
        "ENABLE_A53_CORE",
        "SOC_AM62X",
    ]
};

const defines_a53_nortos = {
    common:[
        "ENABLE_A53_CORE",
        "SOC_AM62X"
    ]
};

const defines_common = {
    common:[
        "SOC_AM62X",
    ]
};

const defines_a53_smp = {
    common: [
        "SOC_AM62X",
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            udmaDdrAddr:  0x90000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_nortos_dm_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            heapSize: 16*1024,
            isSingleCore: true,
            /* DDR buffers */
            udmaDdrAddr:  0x90000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 0x20000,
            stackSize: 0x10000,
            /* DDR UDMA buffer region */
            codeDataAddrDdrUdma: 0x88000000,
            codeDataSizeDdrUdma: 0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    },
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 0x20000,
            stackSize: 0x10000,
            /* DDR UDMA buffer region */
            codeDataAddrDdrUdma: 0x88000000,
            codeDataSizeDdrUdma: 0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_a53_smp =
[
    {
        input: ".project/templates/am62x/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_smp_main",
            stackSize: 64*1024,
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos-smp"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
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

const robot_test_case_ids_common = [
    "SITSW-11048", "SITSW-11049", "SITSW-11050", "SITSW-11051", "SITSW-11052", "SITSW-11053", "SITSW-11054",
    "SITSW-11055", "SITSW-11056", "SITSW-11057", "SITSW-11058", "SITSW-11059", "SITSW-11060", "SITSW-11061",
    "SITSW-11062", "SITSW-11063", "SITSW-11064", "SITSW-11065", "SITSW-11066", "SITSW-11069", "SITSW-11070",
    "SITSW-8237", "SITSW-8238", "SITSW-8239", "SITSW-8240", "SITSW-8242", "SITSW-8243", "SITSW-8244",
    "SITSW-8245", "SITSW-8246", "SITSW-8247", "SITSW-8248", "SITSW-8249", "SITSW-8250", "SITSW-8251",
    "SITSW-8252", "SITSW-8274", "SITSW-8275", "SITSW-8278", "SITSW-8279", "SITSW-8280", "SITSW-8282",
    "SITSW-8283", "SITSW-8284", "SITSW-8285", "SITSW-8286", "SITSW-8288", "SITSW-8289", "SITSW-8290",
    "SITSW-8291", "SITSW-8292", "SITSW-8293", "SITSW-8295", "SITSW-8296", "SITSW-8297", "SITSW-8298",
    "SITSW-8300", "SITSW-8301", "SITSW-8304", "SITSW-8595", "SITSW-8596", "SITSW-8598", "SITSW-8599",
    "SITSW-8600", "SITSW-8601", "SITSW-8603", "SITSW-8604", "SITSW-8605", "SITSW-8606", "SITSW-8607",
    "SITSW-8609", "SITSW-8610", "SITSW-8611", "SITSW-8612", "SITSW-8613", "SITSW-8614", "SITSW-8615",
    "SITSW-8616", "SITSW-8617", "SITSW-8765", "SITSW-8766", "SITSW-8767", "SITSW-8768", "SITSW-8769",
    "SITSW-8770", "SITSW-8771", "SITSW-8772", "SITSW-8773", "SITSW-8774", "SITSW-8775", "SITSW-8776",
    "SITSW-8777", "SITSW-8778", "SITSW-9135", "SITSW-9137", "SITSW-9138", "SITSW-9140", "SITSW-9141",
    "SITSW-9142",
];

const robot_test_case_ids = {
    "a53ss0-0_nortos": robot_test_case_ids_common.concat("SITSW-8302", "SITSW-8303", "SITSW-9601", "SITSW-9603"),
    "a53ss0-0_freertos": robot_test_case_ids_common.concat("SITSW-8302", "SITSW-8303", "SITSW-8618", "SITSW-9250", "SITSW-9251", "SITSW-9252", "SITSW-9601", "SITSW-9603"),
    "a53ss0-0_freertos-smp": ["SITSW-9594", "SITSW-9595", "SITSW-9596", "SITSW-9597", "SITSW-9631"],
    "r5fss0-0_nortos": robot_test_case_ids_common.concat("SITSW-8276", "SITSW-8287"),
    "r5fss0-0_freertos": robot_test_case_ids_common.concat("SITSW-8276", "SITSW-8287", "SITSW-8618", "SITSW-9250", "SITSW-9251", "SITSW-9252"),
};

function getRobotTemplate(testCaseIds) {
    return {
        input: ".project/templates/am62x/astra/tests.robot.xdt",
        output: "../tests.robot",
        options: {
            componentName: "UDMA",
            testCaseName: "UDMA Test Application",
            appName: "test_udma",
            testCaseIds: testCaseIds.join(" "),
            expectTimeout: 120,
        },
    };
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.defines = defines_common;
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.defines = defines_dm_r5f_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_dm_r5;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_dm_r5f;
        }
        else
        {
            build_property.defines = defines_dm_r5f_nortos;
            build_property.includes = includes;
            build_property.libdirsprebuild = libdirs_prebuild_nortos;
            build_property.libdirs = libdirs_nortos_dm_r5;
            build_property.libs = libs_nortos_r5f;
            build_property.libsprebuild = libs_prebuild_nortos_r5f;
            build_property.templates = templates_nortos_dm_r5f;
        }
    } else if(buildOption.cpu.match(/a53*/)){
        if ((buildOption.os.match(/freertos-smp*/)))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if(buildOption.os.match(/freertos*/))
        {
            build_property.defines = defines_a53_freertos;
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags = cflags_a53;
        }
        else
        {
            build_property.defines = defines_a53_nortos;
            build_property.includes = includes;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.cflags = cflags_a53;
        }
    }

    const robot_test_case_key = `${buildOption.cpu}_${buildOption.os}`;
    build_property.templates = [...(build_property.templates || []), getRobotTemplate(robot_test_case_ids[robot_test_case_key])];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
