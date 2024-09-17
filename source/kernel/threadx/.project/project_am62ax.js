let path = require('path');

const files_threadx = [
        "tx_block_allocate.c",
        "tx_block_pool_cleanup.c",
        "tx_block_pool_create.c",
        "tx_block_pool_delete.c",
        "tx_block_pool_info_get.c",
        "tx_block_pool_initialize.c",
        "tx_block_pool_performance_info_get.c",
        "tx_block_pool_performance_system_info_get.c",
        "tx_block_pool_prioritize.c",
        "tx_block_release.c",
        "tx_byte_allocate.c",
        "tx_byte_pool_cleanup.c",
        "tx_byte_pool_create.c",
        "tx_byte_pool_delete.c",
        "tx_byte_pool_info_get.c",
        "tx_byte_pool_initialize.c",
        "tx_byte_pool_performance_info_get.c",
        "tx_byte_pool_performance_system_info_get.c",
        "tx_byte_pool_prioritize.c",
        "tx_byte_pool_search.c",
        "tx_byte_release.c",
        "txe_block_allocate.c",
        "txe_block_pool_create.c",
        "txe_block_pool_delete.c",
        "txe_block_pool_info_get.c",
        "txe_block_pool_prioritize.c",
        "txe_block_release.c",
        "txe_byte_allocate.c",
        "txe_byte_pool_create.c",
        "txe_byte_pool_delete.c",
        "txe_byte_pool_info_get.c",
        "txe_byte_pool_prioritize.c",
        "txe_byte_release.c",
        "txe_event_flags_create.c",
        "txe_event_flags_delete.c",
        "txe_event_flags_get.c",
        "txe_event_flags_info_get.c",
        "txe_event_flags_set.c",
        "txe_event_flags_set_notify.c",
        "txe_mutex_create.c",
        "txe_mutex_delete.c",
        "txe_mutex_get.c",
        "txe_mutex_info_get.c",
        "txe_mutex_prioritize.c",
        "txe_mutex_put.c",
        "txe_queue_create.c",
        "txe_queue_delete.c",
        "txe_queue_flush.c",
        "txe_queue_front_send.c",
        "txe_queue_info_get.c",
        "txe_queue_prioritize.c",
        "txe_queue_receive.c",
        "txe_queue_send.c",
        "txe_queue_send_notify.c",
        "txe_semaphore_ceiling_put.c",
        "txe_semaphore_create.c",
        "txe_semaphore_delete.c",
        "txe_semaphore_get.c",
        "txe_semaphore_info_get.c",
        "txe_semaphore_prioritize.c",
        "txe_semaphore_put.c",
        "txe_semaphore_put_notify.c",
        "txe_thread_create.c",
        "txe_thread_delete.c",
        "txe_thread_entry_exit_notify.c",
        "txe_thread_info_get.c",
        "txe_thread_preemption_change.c",
        "txe_thread_priority_change.c",
        "txe_thread_relinquish.c",
        "txe_thread_reset.c",
        "txe_thread_resume.c",
        "txe_thread_suspend.c",
        "txe_thread_terminate.c",
        "txe_thread_time_slice_change.c",
        "txe_thread_wait_abort.c",
        "txe_timer_activate.c",
        "txe_timer_change.c",
        "txe_timer_create.c",
        "txe_timer_deactivate.c",
        "txe_timer_delete.c",
        "txe_timer_info_get.c",
        "tx_event_flags_cleanup.c",
        "tx_event_flags_create.c",
        "tx_event_flags_delete.c",
        "tx_event_flags_get.c",
        "tx_event_flags_info_get.c",
        "tx_event_flags_initialize.c",
        "tx_event_flags_performance_info_get.c",
        "tx_event_flags_performance_system_info_get.c",
        "tx_event_flags_set.c",
        "tx_event_flags_set_notify.c",
        "tx_initialize_high_level.c",
        "tx_initialize_kernel_enter.c",
        "tx_initialize_kernel_setup.c",
        "tx_misra.c",
        "tx_mutex_cleanup.c",
        "tx_mutex_create.c",
        "tx_mutex_delete.c",
        "tx_mutex_get.c",
        "tx_mutex_info_get.c",
        "tx_mutex_initialize.c",
        "tx_mutex_performance_info_get.c",
        "tx_mutex_performance_system_info_get.c",
        "tx_mutex_prioritize.c",
        "tx_mutex_priority_change.c",
        "tx_mutex_put.c",
        "tx_queue_cleanup.c",
        "tx_queue_create.c",
        "tx_queue_delete.c",
        "tx_queue_flush.c",
        "tx_queue_front_send.c",
        "tx_queue_info_get.c",
        "tx_queue_initialize.c",
        "tx_queue_performance_info_get.c",
        "tx_queue_performance_system_info_get.c",
        "tx_queue_prioritize.c",
        "tx_queue_receive.c",
        "tx_queue_send.c",
        "tx_queue_send_notify.c",
        "tx_semaphore_ceiling_put.c",
        "tx_semaphore_cleanup.c",
        "tx_semaphore_create.c",
        "tx_semaphore_delete.c",
        "tx_semaphore_get.c",
        "tx_semaphore_info_get.c",
        "tx_semaphore_initialize.c",
        "tx_semaphore_performance_info_get.c",
        "tx_semaphore_performance_system_info_get.c",
        "tx_semaphore_prioritize.c",
        "tx_semaphore_put.c",
        "tx_semaphore_put_notify.c",
        "tx_thread_create.c",
        "tx_thread_delete.c",
        "tx_thread_entry_exit_notify.c",
        "tx_thread_identify.c",
        "tx_thread_info_get.c",
        "tx_thread_initialize.c",
        "tx_thread_performance_info_get.c",
        "tx_thread_performance_system_info_get.c",
        "tx_thread_preemption_change.c",
        "tx_thread_priority_change.c",
        "tx_thread_relinquish.c",
        "tx_thread_reset.c",
        "tx_thread_resume.c",
        "tx_thread_shell_entry.c",
        "tx_thread_sleep.c",
        "tx_thread_stack_analyze.c",
        "tx_thread_stack_error_handler.c",
        "tx_thread_stack_error_notify.c",
        "tx_thread_suspend.c",
        "tx_thread_system_preempt_check.c",
        "tx_thread_system_resume.c",
        "tx_thread_system_suspend.c",
        "tx_thread_terminate.c",
        "tx_thread_timeout.c",
        "tx_thread_time_slice.c",
        "tx_thread_time_slice_change.c",
        "tx_thread_wait_abort.c",
        "tx_time_get.c",
        "tx_timer_activate.c",
        "tx_timer_change.c",
        "tx_timer_create.c",
        "tx_timer_deactivate.c",
        "tx_timer_delete.c",
        "tx_timer_expiration_process.c",
        "tx_timer_info_get.c",
        "tx_timer_initialize.c",
        "tx_timer_performance_info_get.c",
        "tx_timer_performance_system_info_get.c",
        "tx_timer_system_activate.c",
        "tx_timer_system_deactivate.c",
        "tx_timer_thread_entry.c",
        "tx_time_set.c",
        "tx_trace_buffer_full_notify.c",
        "tx_trace_disable.c",
        "tx_trace_enable.c",
        "tx_trace_event_filter.c",
        "tx_trace_event_unfilter.c",
        "tx_trace_initialize.c",
        "tx_trace_interrupt_control.c",
        "tx_trace_isr_enter_insert.c",
        "tx_trace_isr_exit_insert.c",
        "tx_trace_object_register.c",
        "tx_trace_object_unregister.c",
        "tx_trace_user_event_insert.c",
    ];


const files_r5f_port = [
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
        // DPL common
        "ClockP_threadx.c",
        "DebugP_shmLogReader_threadx.c",
        "DebugP_threadx.c",
        "EventP_threadx.c",
        "HeapP_threadx.c",
        "SemaphoreP_threadx.c",
        "TaskP_threadx.c",
        // DPL R5
        "ClockP_threadx_r5.c",
        "HwiP_armv7r_handlers_threadx.c",
        "tx_thread_stack_build_c.c",
    ];


const files_c75x_port = [
        // picked from nortos DPL c75
        "boot_c75.c",
        "CacheP_c75.c",
        "c7x_module_config.c",
        "CycleCounterP_c75.c",
        "Exception.c",
        // "HwiP_c75.c", // includes FreeRTOS.h
        "IntrinsicsSupport.c",
        "MmuP_c75.c",
        "Startup.c",
        // "TaskSupport.c", // includes FreeRTOS.h
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
    ];

const files_a53_port = [
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
        // DPL common
        "ClockP_threadx.c",
        "DebugP_shmLogReader_threadx.c",
        "DebugP_threadx.c",
        "EventP_threadx.c",
        "HeapP_threadx.c",
        "SemaphoreP_threadx.c",
        "TaskP_threadx.c",
        // DPL A53
        "ClockP_threadx_a53.c",
        "HwiP_armv8a_handlers_threadx.c",
    ];

const files_a53_smp_port = [
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
    ];

const files_r5f = {
    common : files_threadx.concat(files_r5f_port)
}

const files_c75x = {
    common : files_threadx.concat(files_c75x_port)
}

const files_a53 = {
    common : files_threadx.concat(files_a53_port)
}

const files_a53_smp = {
    common : files_threadx.concat(files_a53_smp_port)
}


const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_r5/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common"
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common"
    ],
};

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common"
    ],
};

const includes_c75x = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_c7x/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common"
    ]
};

const cflags_r5f = {
    common: [
        "-Wno-extra",
    ]
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function", 
        "-Wno-maybe-uninitialized",
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
        // DPL R5
        "HwiP_armv7r_handlers_threadx_asm.S",
        "HwiP_armv7r_vectors_threadx_asm.S",
        // R5 port
        "tx_thread_context_restore.S",
        "tx_thread_context_save.S",
        "tx_thread_interrupt_control.S",
        "tx_thread_interrupt_disable.S",
        "tx_thread_interrupt_restore.S",
        "tx_thread_irq_nesting_end.S",
        "tx_thread_irq_nesting_start.S",
        "tx_thread_schedule.S",
        "tx_thread_stack_build.S",
        "tx_thread_system_return.S",
        "tx_thread_vectored_context_save.S",
        "tx_timer_interrupt.S",
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
        // DPL A53
        "HwiP_armv8a_vectors_threadx_asm.S",
        "HwiP_armv8a_handlers_threadx_asm.S", 
        // A53 port
        "tx_initialize_low_level.S",
        "tx_thread_context_restore.S",
        "tx_thread_context_save.S",
        "tx_thread_interrupt_control.S",
        "tx_thread_interrupt_disable.S",
        "tx_thread_interrupt_restore.S",
        "tx_thread_schedule.S",
        "tx_thread_stack_build.S",
        "tx_thread_system_return.S",
        "tx_timer_interrupt.S",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_r5/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/r5",
        // picked from nortos DPL
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/r5",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/common",
    ],
};

const filedirs_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/a53",
        // picked from nortos DPL
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/a53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/common",
    ],
};

const filedirs_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/a53",
        // picked from nortos DPL
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/a53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/common",
    ],
};

const filedirs_c75x = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_c7x/src",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/common",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/dpl/c7x",
        // picked from nortos DPL
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/c75",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/common",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang", os: "threadx"},
    // { device: device, cpu: "c75x", cgt: "ti-c7000", os: "threadx"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64", os: "threadx"},
    // { device: device, cpu: "a53-smp", cgt: "gcc-aarch64", os: "threadx"},
];


function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "threadx";
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
    } 
    else if(buildOption.cpu == "c75x") {
        build_property.files = files_c75x;
        build_property.includes = includes_c75x;
        build_property.asmfiles = asmfiles_c75x;
        build_property.filedirs = filedirs_c75x;
        build_property.cflags = cflags_c75x;
    }
    else if(buildOption.cpu == "a53") {
        build_property.files = files_a53;
        build_property.includes = includes_a53;
        build_property.asmfiles = asmfiles_a53;
        build_property.filedirs = filedirs_a53;
        build_property.cflags = cflags_a53;
    }
    else if(buildOption.cpu == "a53-smp") {
        build_property.files = files_a53_smp;
        build_property.includes = includes_a53_smp;
        build_property.asmfiles = asmfiles_a53_smp;
        build_property.filedirs = filedirs_a53_smp;
        build_property.cflags   = cflags_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
