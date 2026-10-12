let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "test_main.c",
		"sdl_pok_api_test_neg.c",
        "sdl_pok_api_test_pos.c",
		"sdl_pok_ip_test.c",
        "dpl_interface.c",
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
        "../../../../../dpl", /* SDL DPL base */
    ],
};


const r5_macro = {
    common: [
        "R5F_CORE",
        "SOC_AM62DX",
    ],

};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const libs_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

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

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "pok_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "POK",
        testCaseName: "POK Unit test testcase(s)",
        testCaseIds: "PROC_SDL-1128 PROC_SDL-1694 PROC_SDL-1695 PROC_SDL-1696 PROC_SDL-1697 PROC_SDL-1698 PROC_SDL-1699 PROC_SDL-1702 PROC_SDL-1730 PROC_SDL-1731 PROC_SDL-1733 PROC_SDL-1734 PROC_SDL-1735 PROC_SDL-1736 PROC_SDL-1737 PROC_SDL-1738 PROC_SDL-1739 PROC_SDL-1741 PROC_SDL-1742 PROC_SDL-1744 PROC_SDL-1745 PROC_SDL-1746 PROC_SDL-1747 PROC_SDL-1748 PROC_SDL-1750 PROC_SDL-1751 PROC_SDL-1763 PROC_SDL-1764 PROC_SDL-3296 PROC_SDL-3297 PROC_SDL-3298 PROC_SDL-3299",
        expectedString: "All tests have passed",
    },
};


function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
		build_property.defines = r5_macro;
    }
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
