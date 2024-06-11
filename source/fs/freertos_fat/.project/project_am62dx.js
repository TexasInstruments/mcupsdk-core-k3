let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "ff_crc.c",
        "ff_dir.c",
        "ff_error.c",
        "ff_fat.c",
        "ff_file.c",
        "ff_ioman.c",
        "ff_memory.c",
        "ff_stdio.c",
        "ff_string.c",
        "ff_sys.c",
        "ff_format.c",
        "ff_mmcsd.c",
        "portable.c"
    ],
};

const filedirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
    ],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
    ],
};

const includes_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
    ],
};

const cflags = {
    common: [
        "-Wno-extra",
        "-Wno-uninitialized",
        "-Wno-unused-but-set-variable",
    ],
    debug: [
        "-Oz",
    ],
    release: [
        "-Oz",
    ],
};

const cflags_c75 = {
    common: [
        "--diag_suppress=552",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-extra",
        "-Wno-uninitialized",
        "-Wno-unused-but-set-variable",
        "-Wno-overflow",
    ],
    debug: [
        "-Og",
    ],
    release: [
        "-Og",
    ],
};

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
    { device: device, cpu: "c75", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "freertos_fat";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.files = files;
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.includes = includes_r5f;
        build_property.cflags = cflags;
        build_property.defines = defines_common;
    }
    if(buildOption.cpu.match(/a53*/)) {
        build_property.includes = includes_a53;
        build_property.cflags = cflags_a53;
        build_property.defines = defines_common;
    }
    if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_c75;
        build_property.cflags = cflags_c75;
        build_property.defines = defines_common;

    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
