let path = require('path');

const files = {
    common: [
        "fx_directory_attributes_read.c",
        "fx_directory_attributes_set.c",
        "fx_directory_create.c",
        "fx_directory_default_get.c",
        "fx_directory_default_get_copy.c",
        "fx_directory_default_set.c",
        "fx_directory_delete.c",
        "fx_directory_entry_read.c",
        "fx_directory_entry_write.c",
        "fx_directory_first_entry_find.c",
        "fx_directory_first_full_entry_find.c",
        "fx_directory_free_search.c",
        "fx_directory_information_get.c",
        "fx_directory_local_path_clear.c",
        "fx_directory_local_path_get.c",
        "fx_directory_local_path_get_copy.c",
        "fx_directory_local_path_restore.c",
        "fx_directory_local_path_set.c",
        "fx_directory_long_name_get.c",
        "fx_directory_long_name_get_extended.c",
        "fx_directory_name_extract.c",
        "fx_directory_name_test.c",
        "fx_directory_next_entry_find.c",
        "fx_directory_next_full_entry_find.c",
        "fx_directory_rename.c",
        "fx_directory_search.c",
        "fx_directory_short_name_get.c",
        "fx_directory_short_name_get_extended.c",
        "fxe_directory_attributes_read.c",
        "fxe_directory_attributes_set.c",
        "fxe_directory_create.c",
        "fxe_directory_default_get.c",
        "fxe_directory_default_get_copy.c",
        "fxe_directory_default_set.c",
        "fxe_directory_delete.c",
        "fxe_directory_first_entry_find.c",
        "fxe_directory_first_full_entry_find.c",
        "fxe_directory_information_get.c",
        "fxe_directory_local_path_clear.c",
        "fxe_directory_local_path_get.c",
        "fxe_directory_local_path_get_copy.c",
        "fxe_directory_local_path_restore.c",
        "fxe_directory_local_path_set.c",
        "fxe_directory_long_name_get.c",
        "fxe_directory_long_name_get_extended.c",
        "fxe_directory_name_test.c",
        "fxe_directory_next_entry_find.c",
        "fxe_directory_next_full_entry_find.c",
        "fxe_directory_rename.c",
        "fxe_directory_short_name_get.c",
        "fxe_directory_short_name_get_extended.c",
        "fxe_fault_tolerant_enable.c",
        "fxe_file_allocate.c",
        "fxe_file_attributes_read.c",
        "fxe_file_attributes_set.c",
        "fxe_file_best_effort_allocate.c",
        "fxe_file_close.c",
        "fxe_file_create.c",
        "fxe_file_date_time_set.c",
        "fxe_file_delete.c",
        "fxe_file_extended_allocate.c",
        "fxe_file_extended_best_effort_allocate.c",
        "fxe_file_extended_relative_seek.c",
        "fxe_file_extended_seek.c",
        "fxe_file_extended_truncate.c",
        "fxe_file_extended_truncate_release.c",
        "fxe_file_open.c",
        "fxe_file_read.c",
        "fxe_file_relative_seek.c",
        "fxe_file_rename.c",
        "fxe_file_seek.c",
        "fxe_file_truncate.c",
        "fxe_file_truncate_release.c",
        "fxe_file_write.c",
        "fxe_file_write_notify_set.c",
        "fxe_media_abort.c",
        "fxe_media_cache_invalidate.c",
        "fxe_media_check.c",
        "fxe_media_close.c",
        "fxe_media_close_notify_set.c",
        "fxe_media_extended_space_available.c",
        "fxe_media_flush.c",
        "fxe_media_format.c",
        "fxe_media_open.c",
        "fxe_media_open_notify_set.c",
        "fxe_media_read.c",
        "fxe_media_space_available.c",
        "fxe_media_volume_get.c",
        "fxe_media_volume_get_extended.c",
        "fxe_media_volume_set.c",
        "fxe_media_write.c",
        "fxe_system_date_get.c",
        "fxe_system_date_set.c",
        "fxe_system_time_get.c",
        "fxe_system_time_set.c",
        "fxe_unicode_directory_create.c",
        "fxe_unicode_directory_rename.c",
        "fxe_unicode_file_create.c",
        "fxe_unicode_file_rename.c",
        "fxe_unicode_name_get.c",
        "fxe_unicode_name_get_extended.c",
        "fxe_unicode_short_name_get.c",
        "fxe_unicode_short_name_get_extended.c",
        "fx_fault_tolerant_add_bitmap_log.c",
        "fx_fault_tolerant_add_checksum_log.c",
        "fx_fault_tolerant_add_dir_log.c",
        "fx_fault_tolerant_add_FAT_log.c",
        "fx_fault_tolerant_apply_logs.c",
        "fx_fault_tolerant_calculate_checksum.c",
        "fx_fault_tolerant_cleanup_FAT_chain.c",
        "fx_fault_tolerant_create_log_file.c",
        "fx_fault_tolerant_enable.c",
        "fx_fault_tolerant_read_directory_sector.c",
        "fx_fault_tolerant_read_FAT.c",
        "fx_fault_tolerant_read_log_file.c",
        "fx_fault_tolerant_recover.c",
        "fx_fault_tolerant_reset_log_file.c",
        "fx_fault_tolerant_set_FAT_chain.c",
        "fx_fault_tolerant_transaction_end.c",
        "fx_fault_tolerant_transaction_fail.c",
        "fx_fault_tolerant_transaction_start.c",
        "fx_fault_tolerant_write_log_file.c",
        "fx_file_allocate.c",
        "fx_file_attributes_read.c",
        "fx_file_attributes_set.c",
        "fx_file_best_effort_allocate.c",
        "fx_file_close.c",
        "fx_file_create.c",
        "fx_file_date_time_set.c",
        "fx_file_delete.c",
        "fx_file_extended_allocate.c",
        "fx_file_extended_best_effort_allocate.c",
        "fx_file_extended_relative_seek.c",
        "fx_file_extended_seek.c",
        "fx_file_extended_truncate.c",
        "fx_file_extended_truncate_release.c",
        "fx_file_open.c",
        "fx_file_read.c",
        "fx_file_relative_seek.c",
        "fx_file_rename.c",
        "fx_file_seek.c",
        "fx_file_truncate.c",
        "fx_file_truncate_release.c",
        "fx_file_write.c",
        "fx_file_write_notify_set.c",
        "fx_media_abort.c",
        "fx_media_boot_info_extract.c",
        "fx_media_cache_invalidate.c",
        "fx_media_check.c",
        "fx_media_check_FAT_chain_check.c",
        "fx_media_check_lost_cluster_check.c",
        "fx_media_close.c",
        "fx_media_close_notify_set.c",
        "fx_media_extended_space_available.c",
        "fx_media_flush.c",
        "fx_media_format.c",
        "fx_media_format_oem_name_set.c",
        "fx_media_format_type_set.c",
        "fx_media_format_volume_id_set.c",
        "fx_media_open.c",
        "fx_media_open_notify_set.c",
        "fx_media_read.c",
        "fx_media_space_available.c",
        "fx_media_volume_get.c",
        "fx_media_volume_get_extended.c",
        "fx_media_volume_set.c",
        "fx_media_write.c",
        "fx_partition_offset_calculate.c",
        "fx_ram_driver.c",
        "fx_system_date_get.c",
        "fx_system_date_set.c",
        "fx_system_initialize.c",
        "fx_system_time_get.c",
        "fx_system_timer_entry.c",
        "fx_system_time_set.c",
        "fx_trace_event_insert.c",
        "fx_trace_event_update.c",
        "fx_trace_object_register.c",
        "fx_trace_object_unregister.c",
        "fx_unicode_directory_create.c",
        "fx_unicode_directory_entry_change.c",
        "fx_unicode_directory_entry_read.c",
        "fx_unicode_directory_rename.c",
        "fx_unicode_directory_search.c",
        "fx_unicode_file_create.c",
        "fx_unicode_file_rename.c",
        "fx_unicode_length_get.c",
        "fx_unicode_length_get_extended.c",
        "fx_unicode_name_get.c",
        "fx_unicode_name_get_extended.c",
        "fx_unicode_short_name_get.c",
        "fx_unicode_short_name_get_extended.c",
        "fx_utility_16_unsigned_read.c",
        "fx_utility_16_unsigned_write.c",
        "fx_utility_32_unsigned_read.c",
        "fx_utility_32_unsigned_write.c",
        "fx_utility_64_unsigned_read.c",
        "fx_utility_64_unsigned_write.c",
        "fx_utility_absolute_path_get.c",
        "fx_utility_FAT_entry_read.c",
        "fx_utility_FAT_entry_write.c",
        "fx_utility_FAT_flush.c",
        "fx_utility_FAT_map_flush.c",
        "fx_utility_FAT_sector_get.c",
        "fx_utility_logical_sector_cache_entry_read.c",
        "fx_utility_logical_sector_flush.c",
        "fx_utility_logical_sector_read.c",
        "fx_utility_logical_sector_write.c",
        "fx_utility_memory_copy.c",
        "fx_utility_memory_set.c",
        "fx_utility_string_length_get.c",
        "fx_utility_token_length_get.c",
    ],
};

const filedirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/common/src",
    ],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_r5/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/ports/generic/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/common/inc",
    ],
};

const includes_c75x = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_c75x/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/ports/generic/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/common/inc",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/ports/ti_arm_gcc_clang_cortex_a53/inc",
        "${MCU_PLUS_SDK_PATH}/source/kernel/threadx/threadx_src/common/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/ports/generic/inc",
        "${MCU_PLUS_SDK_PATH}/source/fs/filex/filex_src/common/inc",
    ],
};


const cflags = {
    common: [
        "-Wno-extra",
        "-Wno-uninitialized",
        "-Wno-unused-but-set-variable",
        "-Wno-unused-variable", // temporary for building port/dpl stubs
        "-Wno-unused-function" // temporary for building port/dpl stubs
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f",  cgt: "ti-arm-clang", os: "threadx"},
    // { device: device, cpu: "a53",  cgt: "gcc-aarch64",  os: "threadx"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "filex";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.files = files;
    build_property.cflags = cflags;
    if(buildOption.cpu == "r5f") {
        build_property.includes = includes_r5f;
    }
    else if(buildOption.cpu == "c75x") {
        build_property.includes = includes_c75x;
    }
    else if(buildOption.cpu == "a53") {
        build_property.includes = includes_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};