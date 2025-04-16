let path = require('path');


const files_a53 = {
    common: [
        "AddrTranslateP.c",
        "boot_armv8.c",
        "CacheP_armv8.c",
        "ClockP_nortos.c",
        "ClockP_nortos_a53.c",
        "DebugP_log.c",
        "DebugP_memTraceLogWriter.c",
        "DebugP_nortos.c",
        "DebugP_shmLogWriter.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "EventP_nortos.c",
        "HeapP_internal.c",
        "HeapP_nortos.c",
        "HwiP_armv8_gic.c",
        "HwiP_armv8_handlers_nortos.c",
        "MmuP_armv8.c",
        "printf.c",
        "PmuP_armv8.c",
        "QueueP_nortos.c",
        "SemaphoreP_nortos.c",
        "TaskP_nortos.c",
        "TimerP.c",
    ],
};

const cflags_a53 = {
    common: [

    ]
};

const asmfiles_a53 = {
    common: [
        "boot_armv8_asm.S",
        "common_armv8_asm.S",
        "CacheP_armv8_asm.S",
        "HwiP_armv8_asm.S",
        "HwiP_armv8_handlers_nortos_asm.S",
        "HwiP_armv8_vectors_nortos_asm.S",
        "MmuP_armv8_asm.S",
        "PmuP_armv8_asm.S",
        "SpinlockP_armv8.S",
    ],
};


const filedirs_a53 = {
    common: [
        "dpl/common",
        "dpl/a53",
    ],
};


const defines_a53 = {
    common: [
        "OS_NORTOS",
        "AMP_FREERTOS_A53",
    ]
};

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64",  os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "nortos";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
        build_property.cflags = cflags_a53;
        build_property.asmfiles = asmfiles_a53;
        build_property.filedirs = filedirs_a53;
        build_property.defines = defines_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};