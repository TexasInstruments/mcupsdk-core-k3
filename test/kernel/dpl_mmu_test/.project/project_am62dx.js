let path = require('path');

let device = "am62dx";

const files = {
	common: [
		"test_multi_thread_mmu.c",
		"test_single_thread_mmu.c",
		"test_mmu.c",
		"main.c",
	],
};

const files_smp = {
    common: [
        "test_mmu_smp.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
	common: [
		"..",       /* core_os_combo base */
        "../..",    /* Example base */
		"../../..", /* Example base */
	],
};

const libdirs_nortos = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
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

const libdirs_freertos_a53 = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

/**
 *  A53 support for AM62Dx
 */
const libs_nortos_a53 = {
	common: [
		"nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
		"drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
	],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62dx.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",

    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_a53_smp = {
    common: [
        "SOC_AM62DX",
    ],
};

const defines_a53_nortos = {
    common:[
        "SOC_AM62DX",
        "ENABLE_A53_CORE",
    ]
};

const defines_a53_freertos = {
    common:[
        "SOC_AM62DX",
        "ENABLE_MT_TESTS",
        "ENABLE_A53_CORE",
    ]
};

const defines_c75_freertos = {
    common:[
        "SOC_AM62DX",
        "ENABLE_MT_TESTS",
        "ENABLE_C75_CORE",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_mmu_main",
        },
    },
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_mmu_main",
        },
    }
];

const templates_a53_smp =
[
    {
        input: ".project/templates/am62dx/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_mmu_smp_main",
        },
    },
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_mmu_main",
            stackSize: 32*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",    board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos-smp"}
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mmu";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL MMU NoRTOS application",
        appName: "test_mmu(nortos)",
        testCaseIds: "SITSW-9984 SITSW-9989 SITSW-9993 SITSW-9995 SITSW-9996 SITSW-9997 SITSW-9998 SITSW-9999 SITSW-10000 SITSW-10001" +
                     " SITSW-10002 SITSW-10003 SITSW-10004 SITSW-10005 SITSW-10006 SITSW-10007 SITSW-10008 SITSW-10009 SITSW-10010 SITSW-10011" +
                     " SITSW-10012 SITSW-10013 SITSW-10014 SITSW-10017 SITSW-10018 SITSW-10019 SITSW-10020",
        timeout: 300,
        expectTimeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL MMU FreeRTOS application",
        appName: "test_mmu(freertos)",
        testCaseIds: "SITSW-9984 SITSW-9989 SITSW-9993 SITSW-9995 SITSW-9996 SITSW-9997 SITSW-9998 SITSW-9999 SITSW-10000 SITSW-10001" +
                     " SITSW-10002 SITSW-10003 SITSW-10004 SITSW-10005 SITSW-10006 SITSW-10007 SITSW-10008 SITSW-10009 SITSW-10010 SITSW-10011" +
                     " SITSW-10012 SITSW-10013 SITSW-10014 SITSW-10017 SITSW-10018 SITSW-10019 SITSW-10020 SITSW-10094 SITSW-10095 SITSW-10096" +
                     " SITSW-10097 SITSW-10098 SITSW-10099 SITSW-10100 SITSW-10165 SITSW-10166 SITSW-10167",
        timeout: 400,
        expectTimeout: 300,
    },
};

/* am62dx c75ss0-0 test app uses MAIN_UART4 (not MCU_UART), so the log port must
 * be overridden to USB0 instead of the template's C75 default of USB3. */
const robot_template_freertos_c75 = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL MMU FreeRTOS application",
        appName: "test_mmu(freertos)",
        testCaseIds: "SITSW-9984 SITSW-9989 SITSW-9993 SITSW-9995 SITSW-9996 SITSW-9997 SITSW-9998 SITSW-9999 SITSW-10000 SITSW-10001" +
                     " SITSW-10002 SITSW-10003 SITSW-10004 SITSW-10005 SITSW-10006 SITSW-10007 SITSW-10008 SITSW-10009 SITSW-10010 SITSW-10011" +
                     " SITSW-10012 SITSW-10013 SITSW-10014 SITSW-10017 SITSW-10018 SITSW-10020 SITSW-10094 SITSW-10095 SITSW-10096" +
                     " SITSW-10097 SITSW-10098 SITSW-10099 SITSW-10100 SITSW-10165 SITSW-10166 SITSW-10167",
        timeout: 400,
        expectTimeout: 300,
        logPort: "USB0",
    },
};

const robot_template_freertos_smp = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL MMU FreeRTOS SMP application",
        appName: "test_mmu(freertos-smp)",
        testCaseIds: "SITSW-11656 SITSW-11657 SITSW-11658 SITSW-11659",
        timeout: 400,
        expectTimeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
        build_property.defines = defines_c75_freertos;
        build_property.templates = [...(build_property.templates || []), robot_template_freertos_c75];
    }
    else if(buildOption.cpu.match(/a53*/)) {
        if(buildOption.os.match("freertos-smp"))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
            build_property.templates = [...(build_property.templates || []), robot_template_freertos_smp];
        }
        else if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.isLogSHM = true;
            build_property.templates = templates_freertos_a53;
            build_property.defines = defines_a53_freertos;
            build_property.templates = [...(build_property.templates || []), robot_template_freertos];
        }
        else
        {
            build_property.includes = includes_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.defines = defines_a53_nortos;
            build_property.templates = [...(build_property.templates || []), robot_template_nortos];
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
