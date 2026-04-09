let path = require('path');

const asmextnfiles_c75 = {
    common: [
        "portasm.asm",
    ],
};

const files_c75x = {
    common: [
        // picked from nortos DPL c75
        "boot_c75.c",
        "CacheP_c75.c",
        "c7x_module_config.c",
        "CycleCounterP_c75.c",
        "Exception.c",
        "csl_clec.c",
        "HwiP_c75.c",
        "MmuP_c75.c",
        "Startup.c",
        // picked from nortos DPL common
        "DebugP_shmLogWriter.c",
        "DebugP_shmLogReader.c",
        "DebugP_log.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "DebugP_memTraceLogWriter.c",
        "TimerP.c",
        "AddrTranslateP.c",
        "printf.c",
        "HeapP_internal.c",
        "QueueP_nortos.c",
        // picked from safertos DPL
        "ClockP_safertos.c",
        "ClockP_safertos_c75.c",
        "HwiP_safertos_c7x.c",
        "SemaphoreP_safertos.c",
        "StartuphooksP_safertos.c",
        "HeapP_safertos.c",
        "DebugP_safertos.c",
        "DebugP_shmLogReader_safertos.c",
        "TaskP_safertos.c",
        "EventP_safertos.c",
        // picked from safertos "kernel"
        "list.c",
        "eventgroups.c",
        "task.c",
        "queue.c",
        "evtmplx.c",
        "timers.c",
        "semaphore.c",
        "mutex.c",
        "streambuffer.c",
        "weakStubs.c",
        // picked from safertos "runtimestats"
        "runtimestats.c",
        // picked from safertos "portable"
        "portable.c",
    ]
};

const files_r5f = {
    common: [
        // picked from nortos DPL
        "boot_armv7r.c",
        "AddrTranslateP_null.c",
        "CacheP_armv7r.c",
        "HeapP_nortos.c",
        "HeapP_internal.c",
        "PmuP_armv7r.c",
        "MpuP_armv7r.c",
        "DebugP_shmLogWriter.c",
        "DebugP_shmLogReader.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "DebugP_memTraceLogWriter.c",
        "DebugP_log.c",
        "printf.c",
        "TimerP.c",
        "QueueP_nortos.c",
        // picked from safertos DPL
        "HwiP_armv7r_handlers_safertos.c",
        "HwiP_safertos_r5.c",
        "ClockP_safertos.c",
        "ClockP_safertos_r5.c",
        "DebugP_safertos.c",
        "DebugP_shmLogReader_safertos.c",
        "SemaphoreP_safertos.c",
        "StartuphooksP_safertos.c",
        "TaskP_safertos.c",
        "EventP_safertos.c",
        // picked from safertos "kernel"
        "list.c",
        "eventgroups.c",
        "task.c",
        "queue.c",
        "evtmplx.c",
        "timers.c",
        "semaphore.c",
        "mutex.c",
        "streambuffer.c",
        "weakStubs.c",
        // picked from safertos "portable"
        "portable.c",
        "mpuARM.c",
        "portmpu.c",
        // picked from safertos "api"
        "apiSemaphoreWrapper.c",
        "apiEvtMplxWrapper.c",
        "apiTimersWrapper.c",
        "apiMutexWrapper.c",
        "apiStreamBufferWrapper.c",
        "apiWrapper.c",
        "apiEventGroupsWrapper.c",
        // picked from safertos "runtimestats"
        "runtimestats.c",
        "apiRuntimestatsWrapper.c",
        // picked from safertos "queue_registry"
        "queue_register.c",
    ]
};

const includes_c75x = {
    common: [
        "../nortos/dpl/c75",
        "../nortos/dpl/c75/soc/am62ax",
        "dpl/c75",
        "c75/api/230_C7x",
        "c75/api/NoWrapper",
        "c75/portable/230_C7x/005_TI_CGT",
        "c75/portable/230_C7x",
        "c75/kernel/include_api",
        "c75/kernel/include_prv",
        "c75/config",
        "c75/runtimestats",
    ],
};

const includes_r5f = {
    common: [
        "dpl/r5",
        "r5f/api/199_TI_CR5",
        "r5f/api/PrivWrapperStd",
        "r5f/portable/199_TI_CR5",
        "r5f/portable/199_TI_CR5/024_Clang",
        "r5f/kernel/include_api",
        "r5f/kernel/include_prv",
        "r5f/config",
        "r5f/runtimestats",
        "r5f/runtimestats/PrivWrapperStd",
        "r5f/queue_registry",
    ],
};

const cflags_c75x = {
    common: [
        "-DHwi_bootToNonSecure__D=true",
        "-DException_vectors__D",
        "--advice:performance=none ",
    ],
    release: [
        "--symdebug:dwarf",
    ],
    remove: [
        "--symdebug:none",
    ]
};

const cflags_r5f = {
    common: [
        "-Wno-extra"
    ]
};

const asmfiles_c75x = {
    common: [
        "CacheP_c75_asm.S",
        "Clobber_asm.S",
        "Exception_asm.S",
        "Hwi_asm.S",
        "Mmu_asm.S",
        "csl_c7xecr.S",
    ],
};

const asmfiles_r5f = {
    common: [
        // picked from nortos DPL
        "HwiP_armv7r_asm.S",
        "MpuP_armv7r_asm.S",
        "PmuP_armv7r_asm.S",
        "boot_armv7r_asm.S",
        // Picked from DPL safertos
        "HwiP_armv7r_vectors_safertos_asm.S",
        "HwiP_armv7r_handlers_safertos_asm.S",
        "CacheP_armv7r_asm.S",
        // Picked from safertos "portable"
        "portasm.S",
    ],
};

const filedirs_c75x = {
    common: [
        // picked from nortos DPL
        "../nortos/dpl/c75",
        "../nortos/dpl/common",
        // picked from freertos DPL
        "dpl/common",
        "dpl/c75",
        // picked from safertos "kernel"
        "c75/kernel",
        // picked from safertos "portable"
        "c75/portable/230_C7x",
        "c75/portable/230_C7x/005_TI_CGT",
        "c75/portable/230_C7x/005_TI_CGT/c75x",
        // picked from safertos "runtimestats"
        "c75/runtimestats",
        // picked from safertos "api"
        "c75/api/NoWrapper"
    ],
};

const filedirs_r5f = {
    common: [
        // picked from nortos DPL
        "../nortos/dpl/r5",
        "../nortos/dpl/common",
        // picked from safertos DPL
        "dpl/r5",
        "dpl/common",
        // picked from safertos "kernel"
        "r5f/kernel",
        // picked from safertos "portable"
        "r5f/portable/199_TI_CR5",
        "r5f/portable/199_TI_CR5/024_Clang",
        // picked from safertos "runtimestats"
        "r5f/runtimestats",
        "r5f/runtimestats/PrivWrapperStd",
        // picked from safertos "api"
        "r5f/api/PrivWrapperStd",
        // picked from safertos "queue_registry"
        "r5f/queue_registry"
    ],
};

const defines_c75_safertos = {
    common: [
        "OS_SAFERTOS",
        "BUILD_C7X",
    ],
};

const defines_r5_safertos = {
    common: [
        "OS_SAFERTOS",
        "BUILD_MCU",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "c75x", cgt: "ti-c7000", os: "safertos"},
    { device: device, cpu: "r5f",  cgt: "ti-arm-clang", os: "safertos"}
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "safertos";
    property.isInternal = false;
    property.isSkipTopLevelBuild = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu == "c75x") {
        build_property.files = files_c75x;
        build_property.includes = includes_c75x;
        build_property.asmfiles = asmfiles_c75x;
        build_property.asmextnfiles = asmextnfiles_c75;
        build_property.filedirs = filedirs_c75x;
        build_property.cflags = cflags_c75x;
        build_property.defines = defines_c75_safertos;
    }
    else if(buildOption.cpu == "r5f") {
        build_property.files = files_r5f;
        build_property.includes = includes_r5f;
        build_property.asmfiles = asmfiles_r5f;
        build_property.filedirs = filedirs_r5f;
        build_property.cflags = cflags_r5f;
        build_property.defines = defines_r5_safertos;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};