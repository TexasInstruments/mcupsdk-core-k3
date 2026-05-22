let path = require('path');

let device = "am275x";

const files = {
    common: [
        "main.c",
        "pmic_user_reg_cfg.c",
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

const libdirs_freertos= {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/include",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/include/cfg/lp8764x",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/include/cfg/tps6522x",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/include/cfg/tps6594x",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/src",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/src/cfg/lp8764x",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/src/cfg/tps6522x",
        "${MCU_PLUS_SDK_PATH}/source/board/pmic/pmic_lld/src/cfg/tps6594x",
    ],
};


const libs_freertos_r5f = {
    common: [
		"freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_PMIC_USER_REG_CFG";

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
		entryFunction: "pmic_user_reg_cfg_main",
		},
	}
];

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PMIC",
        testCaseName: "PMIC: User register configuration example",
        testCaseIds: "SITSW-4631",
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "pmic_user_reg_cfg";
    property.isInternal = false;
    property.description = "An example to show PMIC configuration for ADC, thermal, voltage and GPIO monitoring. "
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_freertos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5fss*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};