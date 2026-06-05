let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "test_mcspi.c",
        "main.c",
    ],
};

const files_rtos = {
    common: [
        "test_mcspi.c",
        "test_mcspi_multi_thread.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_mcspi_multi_thread.c",
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

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
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

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/mcspi",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62dx.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_r5f = {
    common: [
        "SOC_AM62DX",
        "R5F_CORE"
    ],
};

const defines_a53 = {
    common: [
        "SOC_AM62DX",
        "A53_CORE"
    ],
};

const defines_c75 = {
    common:[
        "SOC_AM62DX",
        "C75_CORE",
        "BUILD_C7X",
    ]
};

const defines_a53_smp = {
    common: [
        "SOC_AM62DX",
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
        "A53_CORE"
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_mcu_r5f =
[
	{
		input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "test_main",
		},
	}
];

const templates_nortos_mcu_r5f =
[
	{
		input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "test_main",
		},
	}
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
            entryFunction: "test_main",
        },
    },
];

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
            entryFunction: "test_main",
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
            entryFunction: "test_main",
            stackSize: 16*1024,
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
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos-smp"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcspi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCSPI,UDMA",
        testCaseName: "MCSPI Test Application",
        testCaseIds: "SITSW-2894 SITSW-2895 SITSW-2901 SITSW-2902 SITSW-2903 SITSW-2904 SITSW-2905 SITSW-2906 SITSW-2908 SITSW-2910 SITSW-2911 SITSW-2912 SITSW-2914 SITSW-2915 SITSW-2916 SITSW-2917 SITSW-2918 SITSW-2919 SITSW-2920 SITSW-2921 SITSW-2922 SITSW-2923 SITSW-2924 SITSW-2925 SITSW-2926 SITSW-2927 SITSW-2928 SITSW-2929 SITSW-2930 SITSW-2931 SITSW-2932 SITSW-2933 SITSW-2934 SITSW-4003 SITSW-4004 SITSW-4025 SITSW-4026 SITSW-4027 SITSW-4029 SITSW-6864 SITSW-8055 SITSW-8056 SITSW-8057 SITSW-8373 SITSW-8397 SITSW-8398 SITSW-8399 SITSW-8402 SITSW-8403 SITSW-8404 SITSW-8405 SITSW-8406 SITSW-8407 SITSW-8408 SITSW-8409 SITSW-8410 SITSW-8411 SITSW-8412 SITSW-8413 SITSW-8414 SITSW-8424 SITSW-8425 SITSW-8428 SITSW-8430 SITSW-8431 SITSW-8433 SITSW-8434 SITSW-8435 SITSW-8440 SITSW-8441 SITSW-9227 SITSW-9233 SITSW-9234 SITSW-9235 SITSW-9236 SITSW-9237 SITSW-9238 SITSW-9239 SITSW-9240 SITSW-9241 SITSW-9271 SITSW-9272 SITSW-9274 SITSW-9355 SITSW-10719 SITSW-10720 SITSW-10721 SITSW-10722 SITSW-10723 SITSW-10724",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.defines = defines_r5f;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.cflags =  cflags_free_rtos;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
        }
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.defines = defines_a53;
        if(buildOption.os.match("freertos-smp"))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
            build_property.libdirs = libdirs_freertos;
            build_property.cflags =  cflags_free_rtos;
        }
        else if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags =  cflags_free_rtos;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.files = files_rtos;
        build_property.defines = defines_c75;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos_c75;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
        build_property.cflags =  cflags_free_rtos;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
