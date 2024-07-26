let path = require('path');

const files_r5f = {
    common: [
        // picked from nortos DPL
        "boot_armv7r.c",
        "DebugP_shmLogWriter.c",
        "DebugP_shmLogReader.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "DebugP_memTraceLogWriter.c",
        "DebugP_log.c",
        "TimerP.c",
        "HwiP_armv7r_vim.c",
        "MpuP_armv7r.c",
        "CacheP_armv7r.c",
        "CpuId_armv7r.c",
        "HeapP_internal.c",
        "printf.c",
        "AddrTranslateP.c",
        "PmuP_armv7r.c",
        "QueueP_nortos.c",
        // picked from freertos DPL
        "ClockP_freertos.c",
        "ClockP_freertos_r5.c",
        "SemaphoreP_freertos.c",
        "HwiP_armv7r_handlers_freertos.c",
        "HeapP_freertos.c",
        "DebugP_freertos.c",
        "DebugP_shmLogReader_freertos.c",
        "TaskP_freertos.c",
        "EventP_freertos.c",
        "MailboxP_freertos.c",
        // picked from freertos "kernel"
        "event_groups.c",
        "tasks.c",
        "timers.c",
        "queue.c",
        "list.c",
        "heap_3.c",
        // picked from freertos "posix"
        "FreeRTOS_POSIX_clock.c",
        "FreeRTOS_POSIX_mqueue.c",
        "FreeRTOS_POSIX_pthread_barrier.c",
        "FreeRTOS_POSIX_pthread_cond.c",
        "FreeRTOS_POSIX_pthread_mutex.c",
        "FreeRTOS_POSIX_pthread.c",
        "FreeRTOS_POSIX_sched.c",
        "FreeRTOS_POSIX_semaphore.c",
        "FreeRTOS_POSIX_timer.c",
        "FreeRTOS_POSIX_unistd.c",
        "FreeRTOS_POSIX_utils.c",
        // picked from freertos "portable"
        "port.c",
    ]
};

const files_c75x = {
    common: [
        // picked from nortos DPL c75
        "boot_c75.c",
        "CacheP_c75.c",
        "c7x_module_config.c",
        "CycleCounterP_c75.c",
        "Exception.c",
        "HwiP_c75.c",
        "HwiP_freertos_c7x.c",
        "IntrinsicsSupport.c",
        "MmuP_c75.c",
        "Startup.c",
        "TaskSupport.c",
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
        // picked from freertos DPL
        "ClockP_freertos.c",
        "ClockP_freertos_c75.c",
        //"freertos_mmu.c",  //defined in sysconfig hence not required
        "SemaphoreP_freertos.c",
        "HeapP_freertos.c",
        "DebugP_freertos.c",
        "DebugP_shmLogReader_freertos.c",
        "TaskP_freertos.c",
        "EventP_freertos.c",
        "MailboxP_freertos.c",
        // picked from freertos "kernel"
        "event_groups.c",
        "tasks.c",
        "timers.c",
        "queue.c",
        "list.c",
        "heap_4.c",
        // picked from freertos "posix"
        "FreeRTOS_POSIX_clock.c",
        "FreeRTOS_POSIX_mqueue.c",
        "FreeRTOS_POSIX_pthread_barrier.c",
        "FreeRTOS_POSIX_pthread_cond.c",
        "FreeRTOS_POSIX_pthread_mutex.c",
        "FreeRTOS_POSIX_pthread.c",
        "FreeRTOS_POSIX_sched.c",
        "FreeRTOS_POSIX_semaphore.c",
        "FreeRTOS_POSIX_timer.c",
        "FreeRTOS_POSIX_unistd.c",
        "FreeRTOS_POSIX_utils.c",
        // picked from freertos "portable"
        "csl_clec.c",
        "port.c",

    ]
}

const files_a53 = {
    common: [
        // picked from nortos DPL
        "boot_armv8.c",
        "DebugP_shmLogWriter.c",
        "DebugP_shmLogReader.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "DebugP_memTraceLogWriter.c",
        "DebugP_log.c",
        "TimerP.c",
        "HwiP_armv8_gic.c",
        "MmuP_armv8.c",
        "CacheP_armv8.c",
        "HeapP_internal.c",
        "printf.c",
        "AddrTranslateP.c",
        "PmuP_armv8.c",
        "QueueP_nortos.c",
        // picked from freertos DPL
        "ClockP_freertos.c",
        "ClockP_freertos_a53.c",
        "SemaphoreP_freertos.c",
        "HwiP_armv8_handlers_freertos.c",
        "HeapP_freertos.c",
        "DebugP_freertos.c",
        "DebugP_shmLogReader_freertos.c",
        "TaskP_freertos.c",
        "EventP_freertos.c",
        "MailboxP_freertos.c",
        // picked from freertos "kernel"
        "event_groups.c",
        "tasks.c",
        "timers.c",
        "queue.c",
        "list.c",
        "heap_3.c",
        // picked from freertos "posix"
        "FreeRTOS_POSIX_clock.c",
        "FreeRTOS_POSIX_mqueue.c",
        "FreeRTOS_POSIX_pthread_barrier.c",
        "FreeRTOS_POSIX_pthread_cond.c",
        "FreeRTOS_POSIX_pthread_mutex.c",
        "FreeRTOS_POSIX_pthread.c",
        "FreeRTOS_POSIX_sched.c",
        "FreeRTOS_POSIX_semaphore.c",
        "FreeRTOS_POSIX_timer.c",
        "FreeRTOS_POSIX_unistd.c",
        "FreeRTOS_POSIX_utils.c",
        // picked from freertos "portable"
        "port.c",
    ]
};

const files_a53_smp = {
    common: [
        // picked from nortos DPL
        "boot_armv8.c",
        "DebugP_shmLogWriter.c",
        "DebugP_shmLogReader.c",
        "DebugP_uartLogWriter.c",
        "DebugP_uartScanf.c",
        "DebugP_memTraceLogWriter.c",
        "DebugP_log.c",
        "TimerP.c",
        "HwiP_armv8_gic.c",
        "MmuP_armv8.c",
        "CacheP_armv8.c",
        "HeapP_internal.c",
        "printf.c",
        "AddrTranslateP.c",
        "PmuP_armv8.c",
        "QueueP_nortos.c",
        // picked from freertos DPL
        "ClockP_freertos.c",
        "ClockP_freertos_a53.c",
        "SemaphoreP_freertos.c",
        "HwiP_armv8_handlers_freertos.c",
        "HeapP_freertos.c",
        "DebugP_freertos.c",
        "DebugP_shmLogReader_freertos.c",
        "TaskP_freertos.c",
        "EventP_freertos.c",
        "MailboxP_freertos.c",
        // picked from freertos "kernel"
        "event_groups.c",
        "tasks.c",
        "timers.c",
        "queue.c",
        "list.c",
        "heap_4.c",
        // picked from freertos "posix"
        "FreeRTOS_POSIX_clock.c",
        "FreeRTOS_POSIX_mqueue.c",
        "FreeRTOS_POSIX_pthread_barrier.c",
        "FreeRTOS_POSIX_pthread_cond.c",
        "FreeRTOS_POSIX_pthread_mutex.c",
        "FreeRTOS_POSIX_pthread.c",
        "FreeRTOS_POSIX_sched.c",
        "FreeRTOS_POSIX_semaphore.c",
        "FreeRTOS_POSIX_timer.c",
        "FreeRTOS_POSIX_unistd.c",
        "FreeRTOS_POSIX_utils.c",
        // picked from freertos "portable_smp"
        "port.c",
    ]
};

const includes_r5f = {
    common: [
        "FreeRTOS-Kernel/include",
        "portable/TI_ARM_CLANG/ARM_CR5F",
        "config/am62dx/r5f",
        "FreeRTOS-POSIX/include",
        "FreeRTOS-POSIX/include/private",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
    ],
};

const includes_a53 = {
    common: [
        "FreeRTOS-Kernel/include",
        "portable/GCC/ARM_CA53",
        "config/am62dx/a53",
        "FreeRTOS-POSIX/include",
        "FreeRTOS-POSIX/include/private",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable/ti/cc3220_launchpad",
    ],
};

const includes_a53_smp = {
    common: [
        "FreeRTOS-Kernel/include",
        "portable_smp/GCC/ARM_CA53",
        "config/am62dx/a53-smp",
        "FreeRTOS-POSIX/include",
        "FreeRTOS-POSIX/include/private",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
    ],
};

const includes_c75x = {
    common: [
        "FreeRTOS-Kernel/include",
        "portable/TI_CGT/DSP_C75X",
        "config/am62dx/c75x",
        "FreeRTOS-POSIX/include",
        "FreeRTOS-POSIX/include/private",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
    ],
};

const cflags_r5f = {
    common: [
        "-Wno-extra"
    ]
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function", /* needed to supress warnings in FreeRTOS-POSIX */
        "-Wno-maybe-uninitialized", /* needed to supress warnings in FreeRTOS-POSIX */
    ]
};

const defines_a53_smp = {
    common: [
        "SOC_AM62DX",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const cflags_c75x = {
    common: [
        "-DHwi_bootToNonSecure__D=true",
        "-DException_vectors__D",
    ]
};

const asmfiles_r5f = {
    common: [
        // picked from nortos DPL
        "boot_armv7r_asm.S",
        "HwiP_armv7r_asm.S",
        "MpuP_armv7r_asm.S",
        "CacheP_armv7r_asm.S",
        "CpuId_armv7r_asm.S",
        "PmuP_armv7r_asm.S",
        // picked from freertos DPL
        "HwiP_armv7r_vectors_freertos_asm.S",
        // picked from freertos "portable"
        "portASM.S",
    ],
};

const asmfiles_a53 = {
    common: [
        // picked from nortos DPL
        "boot_armv8_asm.S",
        "HwiP_armv8_asm.S",
        "MmuP_armv8_asm.S",
        "CacheP_armv8_asm.S",
        "PmuP_armv8_asm.S",
        "common_armv8_asm.S",
        // picked from freertos DPL
        // none
        // picked from freertos "portable"
        "portASM.S",
    ],
};

const asmfiles_a53_smp = {
    common: [
        // picked from nortos DPL
        "boot_armv8_asm.S",
        "HwiP_armv8_asm.S",
        "MmuP_armv8_asm.S",
        "CacheP_armv8_asm.S",
        "PmuP_armv8_asm.S",
        "common_armv8_asm.S",
        // picked from freertos DPL
        // none
        // picked from freertos "portable"
        "portASM.S",
    ],
};

const asmfiles_c75x = {
    common: [
        "CacheP_c75_asm.S",
        "Clobber_asm.S",
        "Exception_asm.S",
        "Hwi_asm.S",
        "Hwi_switch_asm.S",
        "Hwi_disp_always_asm.S",
        "Mmu_asm.S",
        "TaskSupport_asm.S",
        "csl_c7xecr.S",
    ],
};

const filedirs_r5f = {
    common: [
        // picked from nortos DPL
        "../nortos/dpl/r5",
        "../nortos/dpl/common",
        // picked from freertos DPL
        "dpl/common",
        "dpl/r5",
        // picked from freertos "kernel"
        "FreeRTOS-Kernel/",
        "FreeRTOS-Kernel/portable/MemMang",
        // picked from freertos "posix"
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/source/",
        // picked from freertos "portable"
        "portable/TI_ARM_CLANG/ARM_CR5F",
    ],
};

const filedirs_a53 = {
    common: [
        // picked from nortos DPL
        "../nortos/dpl/a53",
        "../nortos/dpl/common",
        // picked from freertos DPL
        "dpl/common",
        "dpl/a53",
        // picked from freertos "kernel"
        "FreeRTOS-Kernel/",
        "FreeRTOS-Kernel/portable/MemMang",
        // picked from freertos "posix"
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/source/",
        // picked from freertos "portable"
        "portable/GCC/ARM_CA53",
    ],
};

const filedirs_a53_smp = {
    common: [
        // picked from nortos DPL
        "../nortos/dpl/a53",
        "../nortos/dpl/common",
        // picked from freertos DPL
        "dpl/common",
        "dpl/a53",
        // picked from freertos "kernel"
        "FreeRTOS-Kernel/",
        "FreeRTOS-Kernel/portable/MemMang",
        // picked from freertos "posix"
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/source/",
        // picked from freertos "portable"
        "portable_smp/GCC/ARM_CA53",
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
        // picked from freertos "kernel"
        "FreeRTOS-Kernel/",
        "FreeRTOS-Kernel/portable/MemMang",
        // picked from freertos "posix"
        "FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/source/",
        // picked from freertos "portable"
        "portable/TI_CGT/DSP_C75X",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f",  cgt: "ti-arm-clang", os: "freertos"},
    { device: device, cpu: "c75x", cgt: "ti-c7000",     os: "freertos"},
    { device: device, cpu: "a53",  cgt: "gcc-aarch64",  os: "freertos"},
    { device: device, cpu: "a53-smp", cgt: "gcc-aarch64",  os: "freertos"},
];

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62dx/freertos/FreeRTOSConfig.h.xdt",
        output: "config/am62dx/r5f/FreeRTOSConfig.h",
        options: {

        },
    }
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62dx/freertos/FreeRTOSConfig.h.xdt",
        output: "config/am62dx/a53/FreeRTOSConfig.h",
        options: {

        },
    }
];

const templates_freertos_a53_smp =
[
    {
        input: ".project/templates/am62dx/freertos/FreeRTOSConfig_smp.h.xdt",
        output: "config/am62dx/a53-smp/FreeRTOSConfig.h",
        options: {

        },
    }
];

const templates_freertos_c75x =
[
    {
        input: ".project/templates/am62dx/freertos/FreeRTOSConfig_c75.h.xdt",
        output: "config/am62dx/c75x/FreeRTOSConfig.h",
        options: {

        },
    }
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "freertos";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu == "r5f") {
        build_property.files = files_r5f;
        build_property.includes = includes_r5f;
        build_property.asmfiles = asmfiles_r5f;
        build_property.filedirs = filedirs_r5f;
        build_property.cflags = cflags_r5f;
        build_property.templates = templates_freertos_r5f;
        build_property.defines = defines_common;
    }

    if(buildOption.cpu == "c75x") {
        build_property.files = files_c75x;
        build_property.includes = includes_c75x;
        build_property.asmfiles = asmfiles_c75x;
        build_property.filedirs = filedirs_c75x;
        build_property.cflags = cflags_c75x;
        build_property.templates = templates_freertos_c75x;
        build_property.defines = defines_common;
    }

    if(buildOption.cpu == "a53") {
        build_property.files = files_a53;
        build_property.includes = includes_a53;
        build_property.asmfiles = asmfiles_a53;
        build_property.filedirs = filedirs_a53;
        build_property.cflags = cflags_a53;
        build_property.templates = templates_freertos_a53;
        build_property.defines = defines_common;
    }

    if(buildOption.cpu == "a53-smp")
    {
        build_property.files = files_a53_smp;
        build_property.includes = includes_a53_smp;
        build_property.asmfiles = asmfiles_a53_smp;
        build_property.filedirs = filedirs_a53_smp;
        build_property.cflags   = cflags_a53;
        build_property.templates = templates_freertos_a53_smp;
        build_property.defines = defines_a53_smp;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
