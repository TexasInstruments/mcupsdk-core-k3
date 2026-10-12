let path = require('path');

let device = "am275x";

const files = {
    common: [
        "dpl_interface.c",
        "ecc_func.c",
        "ecc_main.c",
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
        "soc/am275x"
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
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"


const templates_nortos_r5f =
[
	{
		input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
		output: "linker.cmd",
        options: {
			heapSize: 0x8000,
			stackSize: 0x4000,
			irqStackSize: 0x2000,
			svcStackSize: 0x2000,
			fiqStackSize: 0x2000,
			abortStackSize: 0x0100,
			undefinedStackSize: 0x0100,
			dmStubstacksize: 0x0400,
		},
	},
	{
		input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_main",
		},
	}
];


const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_ecc_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "ECC",
        testCaseName: "ECC Func test testcase(s)",
        testCaseIds: "PROC_SDL-1836 PROC_SDL-1838 PROC_SDL-1840 PROC_SDL-1842 PROC_SDL-1843 PROC_SDL-1845 PROC_SDL-1847 PROC_SDL-1848 PROC_SDL-1850 PROC_SDL-1852 PROC_SDL-1854 PROC_SDL-1855 PROC_SDL-1856 PROC_SDL-1858 PROC_SDL-1861 PROC_SDL-1862 PROC_SDL-1863 PROC_SDL-1865 PROC_SDL-1866 PROC_SDL-1868 PROC_SDL-1870 PROC_SDL-1872 PROC_SDL-1873 PROC_SDL-1875 PROC_SDL-1876 PROC_SDL-1878 PROC_SDL-1879 PROC_SDL-1880 PROC_SDL-1881 PROC_SDL-1882 PROC_SDL-1883 PROC_SDL-1884 PROC_SDL-1885 PROC_SDL-2333 PROC_SDL-2334 PROC_SDL-2335 PROC_SDL-2336 PROC_SDL-2337 PROC_SDL-2338 PROC_SDL-2339 PROC_SDL-2340 PROC_SDL-5771 PROC_SDL-5806 PROC_SDL-8810 PROC_SDL-8811 PROC_SDL-8812 PROC_SDL-8813 PROC_SDL-8814 PROC_SDL-8815",
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

	if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_r5f;
		build_property.defines = r5_macro;
    }
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
