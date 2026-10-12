let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "esm_test_main.c",
        "esm_test_api.c",
        "esm_test_err.c",
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
        "../../../../../dpl", /* SDL DPL base add an extra lvl*/
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


const r5_macro = {
    common: [
        "R5F_CORE",
        "SOC_AM62DX",
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
    property.name = "esm_test_app";
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
        componentName: "ESM",
        testCaseName: "ESM Unit test testcase(s)",
        testCaseIds: "PROC_SDL-1752 PROC_SDL-1754 PROC_SDL-1755 PROC_SDL-1756 PROC_SDL-1757 PROC_SDL-1758 PROC_SDL-1759 PROC_SDL-1760 PROC_SDL-1761 PROC_SDL-1762 PROC_SDL-1766 PROC_SDL-1767 PROC_SDL-1768 PROC_SDL-1769 PROC_SDL-1770 PROC_SDL-1771 PROC_SDL-1772 PROC_SDL-1773 PROC_SDL-1774 PROC_SDL-1775 PROC_SDL-1776 PROC_SDL-1777 PROC_SDL-1778 PROC_SDL-1779 PROC_SDL-1780 PROC_SDL-1781 PROC_SDL-1782 PROC_SDL-1784 PROC_SDL-1785 PROC_SDL-1786 PROC_SDL-1787 PROC_SDL-1788 PROC_SDL-1789 PROC_SDL-1790 PROC_SDL-1791 PROC_SDL-1792 PROC_SDL-1793 PROC_SDL-1794 PROC_SDL-1795 PROC_SDL-1796 PROC_SDL-1798 PROC_SDL-1799 PROC_SDL-1800 PROC_SDL-1801 PROC_SDL-1802 PROC_SDL-1806 PROC_SDL-1817 PROC_SDL-1820 PROC_SDL-1825 PROC_SDL-1826 PROC_SDL-1827 PROC_SDL-1828 PROC_SDL-1829 PROC_SDL-1830 PROC_SDL-1895 PROC_SDL-1982 PROC_SDL-1983 PROC_SDL-1984 PROC_SDL-1985 PROC_SDL-1986 PROC_SDL-1987 PROC_SDL-1988 PROC_SDL-1989 PROC_SDL-1990 PROC_SDL-1991 PROC_SDL-1993 PROC_SDL-1994 PROC_SDL-1995 PROC_SDL-1996 PROC_SDL-1997 PROC_SDL-1998 PROC_SDL-1999 PROC_SDL-2011 PROC_SDL-2012 PROC_SDL-2013 PROC_SDL-2014 PROC_SDL-2015 PROC_SDL-2016 PROC_SDL-2017 PROC_SDL-2018 PROC_SDL-2019 PROC_SDL-2020 PROC_SDL-2021 PROC_SDL-2022 PROC_SDL-2023 PROC_SDL-2024 PROC_SDL-2025 PROC_SDL-2026 PROC_SDL-2027 PROC_SDL-2028 PROC_SDL-2029 PROC_SDL-2030 PROC_SDL-2031 PROC_SDL-2032 PROC_SDL-2033 PROC_SDL-2034 PROC_SDL-2035 PROC_SDL-2036 PROC_SDL-2037 PROC_SDL-2038 PROC_SDL-2039 PROC_SDL-2040 PROC_SDL-2041 PROC_SDL-2042 PROC_SDL-2062 PROC_SDL-5807 PROC_SDL-7438 PROC_SDL-7439 PROC_SDL-7440 PROC_SDL-7441 PROC_SDL-7506 PROC_SDL-7507 PROC_SDL-7508 PROC_SDL-7509 PROC_SDL-7510 PROC_SDL-7511 PROC_SDL-7512 PROC_SDL-7513 PROC_SDL-7514 PROC_SDL-7515 PROC_SDL-7516 PROC_SDL-7517 PROC_SDL-7518 PROC_SDL-7519",
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
