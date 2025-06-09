let path = require('path');

let device = "am62lx";

const files = {
    common: [
        "gpio_input_interrupt.c",
        "main.c",
        "board.c",
        "board_user_header.c",
        "board_gpio_expn_conn.c",
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

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62lx.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62lx.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};


const defines_a53_amp = {
    common: [
        "AMP_FREERTOS_A53",
    ],
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_GPIO_INPUT_INTERRUPT";

const templates_nortos_a53ss00 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "gpio_input_interrupt_main",
        },
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio.c.xdt",
        output: "../board.c",
        options: {
            exampleType: "input_interrupt",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board_user_header.c",
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio_expn_conn.c.xdt",
        output: "../board_gpio_expn_conn.c",
    },
];

const templates_nortos_a53ss01 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "gpio_input_interrupt_main",
        },
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio.c.xdt",
        output: "../board.c",
        options: {
            exampleType: "input_interrupt",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board_user_header.c",
    }
];

const templates_freertos_a53ss00 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "gpio_input_interrupt_main",
        },
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio.c.xdt",
        output: "../board.c",
        options: {
            exampleType: "input_interrupt",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board_user_header.c",
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio_expn_conn.c.xdt",
        output: "../board_gpio_expn_conn.c",
    },
];

const templates_freertos_a53ss01 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "gpio_input_interrupt_main",
        },
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio.c.xdt",
        output: "../board.c",
        options: {
            exampleType: "input_interrupt",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board_user_header.c",
    },
    {
        input: ".project/templates/am62lx/gpio/board_gpio_expn_conn.c.xdt",
        output: "../board_gpio_expn_conn.c",
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62lx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0",  cgt: "gcc-aarch64",  board: "am62lx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-1", cgt: "gcc-aarch64", board: "am62lx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-1",  cgt: "gcc-aarch64",  board: "am62lx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "gpio_input_interrupt";
    property.isInternal = false;
    property.userHeaderEnable = true;
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
    build_property.defines = defines_a53_amp;
    build_property.isAmpSHM = true;

    if(buildOption.cpu.match(/a53*/)) {
        if(buildOption.os.match(/nortos/))
        {
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            if(buildOption.cpu.match(/a53ss0-1/))
            {
                build_property.templates = templates_nortos_a53ss01;
            }
            else
            {
                build_property.templates = templates_nortos_a53ss00;
            }
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            if(buildOption.cpu.match(/a53ss0-1/))
            {
                build_property.templates = templates_freertos_a53ss01;
            }
            else
            {
                build_property.templates = templates_freertos_a53ss00;
            }
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
