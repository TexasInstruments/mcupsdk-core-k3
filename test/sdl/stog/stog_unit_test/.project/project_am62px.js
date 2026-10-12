let path = require('path');

let device = "am62px";

const files = {
    common: [
        "tog_test_main.c",
        "tog_test_api.c",
        "tog_test_err.c",
        "tog_test_run.c",
        "dpl_interface.c",
        "main.c",
    ],
};

const asmfiles_r5f = {
    common: [
        "tog_test_utils.S",
        "resetvecs.S",
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

const r5f_macro = {
    common: [
        "R5F_CORE",
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


const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
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
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];
const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "tog_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "STOG",
        testCaseName: "STOG Unit test testcase(s)",
        testCaseIds: "PROC_SDL-1615 PROC_SDL-1616 PROC_SDL-1617 PROC_SDL-1621 PROC_SDL-1622 PROC_SDL-1623 PROC_SDL-1624 PROC_SDL-1625 PROC_SDL-1626 PROC_SDL-1627 PROC_SDL-1628 PROC_SDL-1629 PROC_SDL-1630 PROC_SDL-1631 PROC_SDL-1632 PROC_SDL-1633 PROC_SDL-1634 PROC_SDL-1635 PROC_SDL-1636 PROC_SDL-1637 PROC_SDL-1638 PROC_SDL-1639 PROC_SDL-1640 PROC_SDL-1641 PROC_SDL-1642 PROC_SDL-1643 PROC_SDL-1644 PROC_SDL-1645 PROC_SDL-1646 PROC_SDL-1647 PROC_SDL-1648 PROC_SDL-1649 PROC_SDL-1650 PROC_SDL-1651 PROC_SDL-1652 PROC_SDL-1653 PROC_SDL-1657 PROC_SDL-1658 PROC_SDL-1659 PROC_SDL-1660 PROC_SDL-1661 PROC_SDL-1662 PROC_SDL-1663 PROC_SDL-1664 PROC_SDL-1665 PROC_SDL-1666 PROC_SDL-1667 PROC_SDL-1668 PROC_SDL-1669 PROC_SDL-1670 PROC_SDL-1671 PROC_SDL-1672 PROC_SDL-1673 PROC_SDL-1674 PROC_SDL-1675 PROC_SDL-1676 PROC_SDL-1677 PROC_SDL-1678 PROC_SDL-1679 PROC_SDL-1681 PROC_SDL-1682 PROC_SDL-1683 PROC_SDL-3284 PROC_SDL-3285 PROC_SDL-3287 PROC_SDL-3288 PROC_SDL-849 PROC_SDL-850 PROC_SDL-852 PROC_SDL-854 PROC_SDL-855 PROC_SDL-856 PROC_SDL-857 PROC_SDL-859 PROC_SDL-860 PROC_SDL-861",
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
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
	    build_property.defines = r5f_macro;
        build_property.asmfiles = asmfiles_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
