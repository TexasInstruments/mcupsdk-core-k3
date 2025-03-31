let path = require('path');

let device = "j722s";
const files= {
    common: [
        "dpl_interface.c",
        "lbist_test_err.c",
        "lbist_test_main.c",
        "lbist_test_cfg.c",
        "lbist_test_func.c",
        "main.c",
    ],
};


const filedirs= {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../dpl", /* SDL DPL base */
        "../../../../lbist/soc/j722s",
        "../../../../lbist/j722s-evm",
        "../../../../lbist/j722s",
    ],
};


const libdirs_main_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const libdirs_freertos_main_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/lbist/soc/j722s/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/lbist/",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/lbist/soc/j722s/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/lbist/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/",
    ],
};


const libs_nortos_main_r5f = {
    common: [
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_main_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};


const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_DSS_DISPLAY_TEST";

const templates_nortos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f_nortos.cmd.xdt",
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
		input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_main",
		},
	}
];

const templates_freertos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f.cmd.xdt",
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
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
    { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_lbist_test_app";
    property.isInternal = true;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "Lbist test"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/main-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_main_r5f;
            build_property.libs = libs_freertos_main_r5f;
            build_property.templates = templates_freertos_main_r5f;
        }
        else
        {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_main_r5f;
            build_property.templates = templates_nortos_main_r5f;
            build_property.libdirs = libdirs_main_nortos;
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};