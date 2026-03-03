let path = require('path');

let device = "am62dx";

const files = {
	common: [
        "board.c",
		"swasrc_multichannel_playback.c",
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
        "../../",   /* Board base */
	],
};

const libdirs_freertos_c75 = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/source/signal_processing/lib",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName}",
	],
};



const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/src",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/src",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/src/AUDIOLIB_asrc",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/common",
        "${MCU_PLUS_SDK_PATH}/source/signal_processing/calcratio/src"
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "board.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "signal_processing.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "AUDIOLIB_C7504.lib",
        "AUDIOLIB_common_C7504.lib",
        "DSPLIB_C7504.lib",
        "DSPLIB_common_C7504.lib",
    ],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SWASRC_MULTICHANNEL_PLAYBACK";


const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",    board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "swasrc_multichannel_playback";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "This example verifies SWASRC Mulichannel playback"
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
    build_property.defines = defines_common;

    if(buildOption.cpu.match(/c75*/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
