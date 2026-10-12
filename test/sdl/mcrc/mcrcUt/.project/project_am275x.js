let path = require('path');

let device = "am275x";

const files = {
    common: [
        "mcrc_main.c",
        "sdl_mcrc_ip_test.c",
        "sdl_mcrc_api_test_pos.c",
        "sdl_mcrc_api_test_neg.c",
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
        "../../../../../dpl", /* SDL dpl base */
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

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
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
    property.name = "mcrc_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCRC",
        testCaseName: "MCRC Unit test testcase(s)",
        testCaseIds: "PROC_SDL-2215 PROC_SDL-2216 PROC_SDL-2217 PROC_SDL-2218 PROC_SDL-2219 PROC_SDL-2220 PROC_SDL-2221 PROC_SDL-2222 PROC_SDL-2223 PROC_SDL-2224 PROC_SDL-2225 PROC_SDL-2226 PROC_SDL-2227 PROC_SDL-2228 PROC_SDL-2229 PROC_SDL-2230 PROC_SDL-2231 PROC_SDL-2232 PROC_SDL-2233 PROC_SDL-2234 PROC_SDL-2253 PROC_SDL-2254 PROC_SDL-2255 PROC_SDL-2256 PROC_SDL-2257 PROC_SDL-2258 PROC_SDL-2259 PROC_SDL-2260 PROC_SDL-2261 PROC_SDL-2262 PROC_SDL-2263 PROC_SDL-2264 PROC_SDL-2265 PROC_SDL-2266 PROC_SDL-2267 PROC_SDL-2268 PROC_SDL-2269 PROC_SDL-2270 PROC_SDL-2271 PROC_SDL-2272 PROC_SDL-2274 PROC_SDL-2275 PROC_SDL-2276",
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
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
