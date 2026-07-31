let path = require('path');

let device = "am62x";

const files_freertos = {
    common: [
        "test_uart.c",
        "test_uart_mt.c",
        "main.c",
    ],
};

const files_nortos = {
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

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libdirs_nortos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_prebuild_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libs_prebuild_freertos = {
    common: [
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const defines_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ]
};

const cflags_freertos_r5f = {
    common: [
        "-DCONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "-DCPU_R5F0",
        "-DSOC_AM62X",
    ],
};

const cflags_nortos_r5f = {
    common: [
        "-DCPU_R5F0",
        "-DSOC_AM62X",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53 = {
    common: [
        "CONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "A53_FREERTOS",
        "CPU_A53",
    ],
};

const defines_m4f = {
    common: [
        "CONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "DSOC_AM62X",
        "CPU_M4F",
    ],
};

const defines_nortos_m4f = {
    common: [
        "DSOC_AM62X",
        "CPU_M4F",
    ],
};

const defines_nortos_a53 = {
    common: [
        "CPU_A53",
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_m4f =
    [
        {
            input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        }
    ];

const templates_nortos_m4f =
    [
        {
            input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
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

const templates_freertos_r5f = [
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

const templates_nortos_r5f = [
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

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "freertos" },
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos" },
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "nortos" },
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "nortos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "freertos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "nortos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos" },
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


const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "UART",
        testCaseName: "UART Test Application",
        testCaseIds: "SITSW-1303 SITSW-1304 SITSW-1305 SITSW-2514 SITSW-8918 SITSW-8919 SITSW-8920 SITSW-8921 SITSW-8924 SITSW-8925 " +
            "SITSW-8926 SITSW-8928 SITSW-8929 SITSW-8930 SITSW-8932 SITSW-8933 SITSW-8934 SITSW-8935 SITSW-8936 SITSW-8938 " +
            "SITSW-8939 SITSW-8940 SITSW-8941 SITSW-8943 SITSW-8944 SITSW-8949 SITSW-8950 SITSW-8951 SITSW-8952 SITSW-8953 " +
            "SITSW-8954 SITSW-8955 SITSW-8956 SITSW-8957 SITSW-8958 SITSW-8959 SITSW-8960 SITSW-8961 SITSW-8962 SITSW-8963 " +
            "SITSW-8964 SITSW-8965 SITSW-8966 SITSW-8967 SITSW-8968 SITSW-8970 SITSW-8971 SITSW-8972 SITSW-8973 SITSW-8974 " +
            "SITSW-8975 SITSW-8976 SITSW-8980 SITSW-8981 SITSW-8983 SITSW-8984 SITSW-8985 SITSW-8986 SITSW-8987 SITSW-8989 " +
            "SITSW-8990 SITSW-8991 SITSW-8992 SITSW-8993 SITSW-8994 SITSW-8995 SITSW-9971 SITSW-9972 SITSW-9973 SITSW-9974 " +
            "SITSW-9975 SITSW-9976 SITSW-9977 SITSW-9978 SITSW-10109 SITSW-10110 SITSW-10111 SITSW-10112 SITSW-10113 SITSW-10114 " +
            "SITSW-10115 SITSW-10116 SITSW-10117 SITSW-10118 SITSW-10119 SITSW-10121 SITSW-11621 SITSW-11622 SITSW-11623 SITSW-11624 " +
            "SITSW-11625 SITSW-11626 SITSW-11627 SITSW-11628 SITSW-11629 SITSW-11630 SITSW-11631 SITSW-11632 SITSW-11633 SITSW-11634 " +
            "SITSW-11635 SITSW-11636 SITSW-12113 SITSW-12114 SITSW-12115",
        expectTimeout: 300,
        timeout: 720,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "UART",
        testCaseName: "UART Test Application",
        testCaseIds: "SITSW-1303 SITSW-1304 SITSW-1305 SITSW-2514 SITSW-8918 SITSW-8919 SITSW-8920 SITSW-8921 SITSW-8924 SITSW-8925 " +
            "SITSW-8926 SITSW-8929 SITSW-8930 SITSW-8932 SITSW-8933 SITSW-8934 SITSW-8935 SITSW-8936 SITSW-8938 SITSW-8939 " +
            "SITSW-8940 SITSW-8941 SITSW-8943 SITSW-8944 SITSW-8949 SITSW-8950 SITSW-8951 SITSW-8952 SITSW-8953 SITSW-8954 " +
            "SITSW-8955 SITSW-8956 SITSW-8957 SITSW-8958 SITSW-8959 SITSW-8960 SITSW-8961 SITSW-8962 SITSW-8963 SITSW-8964 " +
            "SITSW-8965 SITSW-8966 SITSW-8967 SITSW-8968 SITSW-8970 SITSW-8971 SITSW-8972 SITSW-8973 SITSW-8974 SITSW-8975 " +
            "SITSW-8976 SITSW-8980 SITSW-8981 SITSW-8983 SITSW-8984 SITSW-8985 SITSW-8986 SITSW-8987 SITSW-8989 SITSW-8990 " +
            "SITSW-8991 SITSW-8992 SITSW-8993 SITSW-8994 SITSW-8995 SITSW-10109 SITSW-10110 SITSW-10111 SITSW-10112 SITSW-10113 " +
            "SITSW-10114 SITSW-10115 SITSW-10116 SITSW-10117 SITSW-10118 SITSW-10119 SITSW-10121 SITSW-11621 SITSW-11622 SITSW-11623 " +
            "SITSW-11624 SITSW-11625 SITSW-11626 SITSW-11627 SITSW-11628 SITSW-11629 SITSW-11630 SITSW-11631 SITSW-11632 SITSW-11633 " +
            "SITSW-11634 SITSW-11635 SITSW-12113 SITSW-12114 SITSW-12115",
        expectTimeout: 300,
        timeout: 720,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.os.match(/freertos/)) {
        build_property.files = files_freertos;
    } else {
        build_property.files = files_nortos;
    }

    if (buildOption.cpu.match(/m4f*/)) {
        if (buildOption.os.match(/freertos/)) {
            build_property.includes = includes_freertos_m4f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_m4f;
            build_property.templates = templates_freertos_m4f;
            build_property.defines = defines_m4f;
        } else {
            build_property.includes = includes_nortos_m4f;
            build_property.libdirs = libdirs_nortos_m4f;
            build_property.libs = libs_nortos_m4f;
            build_property.templates = templates_nortos_m4f;
            build_property.defines = defines_nortos_m4f;
        }
    }
    if (buildOption.cpu.match(/r5f*/)) {
        build_property.defines = defines_r5f;
        build_property.libdirsprebuild = libdirs_prebuild_freertos;
        build_property.libsprebuild = libs_prebuild_freertos;
        if (buildOption.os.match(/freertos/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_freertos_r5f;
        } else {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.cflags = cflags_nortos_r5f;
        }
    }
    if (buildOption.cpu.match(/a53*/)) {
        if (buildOption.os.match(/freertos/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.defines = defines_a53;
        } else {
            build_property.includes = includes_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.defines = defines_nortos_a53;
        }
    }

    if (buildOption.os.match(/freertos/)) {
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
