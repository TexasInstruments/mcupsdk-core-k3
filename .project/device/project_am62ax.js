const common = require("../common.js");


const ThreadXEnabled = true;

function getThreadXEnabled()
{
    return ThreadXEnabled;
}

const component_file_list_common = [
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/udma/.project/project.js",
    "source/dhrystone_benchmark/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    "source/drivers/dmautils/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/safertos/.project/project.js",
    "source/sdl/.project/project.js",
    "source/sdl/sdl_sbl/.project/project.js",
    "source/security/.project/project.js",
    "source/safety_checkers/.project/project.js",

    "source/networking/enet/.project/project_cpsw.js",
    "source/networking/enet/.project/project_cpsw_lwipif_freertos.js",
    "source/networking/enet/.project/project_cpsw_lwipif_nortos.js",
    "source/networking/enet/.project/project_cpsw_lwipif_ic_freertos.js",
    "source/networking/ethfw/.project/project_ethfw.js",
    "source/networking/lwip/.project/project_contrib_freertos.js",
    "source/networking/lwip/.project/project_contrib_nortos.js",
    "source/networking/lwip/.project/project_stack_freertos.js",
    "source/networking/lwip/.project/project_stack_nortos.js",
    "source/networking/mbedtls_library/.project/project.js",
    "source/networking/tsn/.project/project_tsn_combase.js",
    "source/networking/tsn/.project/project_tsn_gptp.js",
    "source/networking/tsn/.project/project_tsn_uniconf.js",
    "source/networking/tsn/.project/project_tsn_unibase.js",
    "test/unity/.project/project.js",
    "test/kernel/smp_tests/disable_multiple_priorities/configs/.project/project.js",
    "test/kernel/smp_tests/disable_preemption/configs/.project/project.js",
    "test/kernel/smp_tests/interrupt_wait_critical/configs/.project/project.js",
    "test/kernel/smp_tests/multiple_tasks_running/configs/.project/project.js",
    "test/kernel/smp_tests/only_one_task_enter_critical/configs/.project/project.js",
    "test/kernel/smp_tests/only_one_task_enter_suspendall/configs/.project/project.js",
    "test/kernel/smp_tests/schedule_affinity/configs/.project/project.js",
    "test/kernel/smp_tests/schedule_equal_priority/configs/.project/project.js",
    "test/kernel/smp_tests/schedule_highest_priority/configs/.project/project.js",
    "test/kernel/smp_tests/suspend_scheduler/configs/.project/project.js",
    "test/kernel/smp_tests/task_delete/configs/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fault_inject/configs/.project/project.js",
    "test/drivers/uart/test_uart_fault_inject/configs/.project/project_am62ax.js",
    "test/drivers/mcspi/test_mcspi_fault_inject/configs/.project/project.js",
    "test/drivers/i2c/test_i2c_fault_inject/configs/.project/project_am62ax.js",
    "test/drivers/mcasp/test_mcasp_fault_injection/configs/.project/project.js",
    "test/drivers/udma/test_udma_fault_inject/configs/.project/project.js",
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
    "test/kernel/dpl_timer/test_dpl_timer_fault_inject/configs_freertos/.project/project.js",
    "test/kernel/dpl_timer/test_dpl_timer_fault_inject/configs_nortos/.project/project.js",
];

const component_file_list_freertos = [
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/freertos/.project/project.js",
];

const component_file_list_threadx = [
    "source/kernel/threadx/.project/project.js",
    "source/fs/filex/.project/project.js",
];

// List of components where makefile is not generated.
const component_file_list_with_makefile = [
    "source/drivers/device_manager/dm_stub/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/sbl/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM62AX",
    ],
};

const example_file_list = [
    "examples/board/eeprom/eeprom_read_write/.project/project.js",
    "examples/dmautils/dmautils_autoinc_1d2d3d/.project/project.js",
    "examples/dmautils/dmautils_autoinc_circular/.project/project.js",
    "examples/dmautils/dmautils_autoinc_compression/.project/project.js",
    "examples/dmautils/dmautils_autoincrement/.project/project.js",
    "examples/drivers/boot/sbl_null/.project/project.js",
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage2/.project/project.js",
    // "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/.project/project.js",
    // "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_sd/.project/project.js",
    "examples/drivers/boot/sbl_sd_linux/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_multistage/sbl_ospi_nand_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_multistage/sbl_ospi_nand_stage2/.project/project.js",
    "examples/drivers/boot/sbl_uart/.project/project.js",
    "examples/drivers/boot/sbl_uart_linux/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage1/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/.project/project.js",
    "examples/drivers/csirx/csirx_capture_testapp/.project/project.js",
    "examples/drivers/ddr/ddr_ecc_test_main_esm/.project/project.js",
    "examples/drivers/ddr/ddr_perf/.project/project.js",
    "examples/drivers/ecap/ecap_apwm_mode/.project/project.js",
    "examples/drivers/ecap/ecap_epwm_loopback/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle_sync/.project/project.js",
    "examples/drivers/eqep/eqep_capture/.project/project.js",
    "examples/drivers/eqep/eqep_frequency_measurement/.project/project.js",
    "examples/drivers/eqep/eqep_position_speed/.project/project.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/ipc/ipc_notify_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_linux/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_qnx/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback_ext_hclk/.project/project.js",
    "examples/drivers/mcasp/mcasp_playback_codec_aic31/.project/project.js",
    // "examples/drivers/mcan/mcan_loopback_interrupt_kpi/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_dma/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/ospi/ospi_phy_grapher_uart/.project/project.js",
    "examples/drivers/pmu/pmu_multievent/.project/project.js",
    "examples/drivers/rtc/rtc_led_blink/.project/project.js",
    "examples/drivers/safety/fwl_isolation/.project/project.js",
    "examples/drivers/safety/reset_isolation/.project/project.js",
    "examples/drivers/safety/mcu_bist_result/.project/project.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/drivers/uart/uart_echo_dma/.project/project.js",
    "examples/drivers/uart/uart_echo_dma_multi_instance/.project/project.js",
    "examples/drivers/udma/udma_memcpy_polling/.project/project.js",
    "examples/drivers/udma/udma_memcpy_interrupt/.project/project.js",
    "examples/drivers/udma/udma_sw_trigger/.project/project.js",
    "examples/drivers/udma/udma_chaining/.project/project.js",
    "examples/drivers/watchdog/watchdog_interrupt/.project/project.js",
    "examples/empty/.project/project_freertos.js",
    "examples/empty/.project/project_nortos.js",
    "examples/hello_world/.project/project.js",
    "examples/hello_world/.project/project_safertos.js",
    "examples/hello_world_cpp/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project_safertos.js",
    "examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
    "examples/kernel/freertos/memcpy_benchmark/.project/project.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project.js",
    "examples/kernel/freertos/smp_task_switch/.project/project.js",
    "examples/kernel/safertos/task_switch/.project/project.js",
    "examples/lpm/lpm_mcu_mcan_wakeup/.project/project.js",
    "examples/lpm/lpm_mcu_dmtimer_wakeup/.project/project.js",
    "examples/lpm/lpm_mcu_uart_wakeup/.project/project.js",
    "examples/otp/ext_otp/.project/project.js",
    "examples/otp/otp_revision/.project/project.js",
    "examples/otp/runtime_keyrev/.project/project.js",
    "examples/safety/safety_app/.project/project.js",
    "examples/security/bootloader_test/.project/project.js",
    "examples/security/fwl_exception_log/.project/project.js",
    "examples/security/fwl_exception_trigger/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_cbc_128/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_cbc_256/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_cmac_128/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_cmac_256/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_ecb_128/.project/project.js",
    "examples/security/crypto/sa3ul_aes/crypto_aes_ecb_256/.project/project.js",
    "examples/security/crypto/sa3ul_hmac_sha/crypto_hmac_sha1/.project/project.js",
    "examples/security/crypto/sa3ul_hmac_sha/crypto_hmac_sha256/.project/project.js",
    "examples/security/crypto/sa3ul_hmac_sha/crypto_hmac_sha256_multishot/.project/project.js",
    "examples/security/crypto/sa3ul_hmac_sha/crypto_hmac_sha512/.project/project.js",
    "examples/security/crypto/sa3ul_rng/.project/project.js",
    "examples/security/crypto/sa3ul_sha/.project/project.js",
    "examples/security/mcu_core_test_app/.project/project.js",
    "examples/security/runtime_debug_unlock/.project/project.js",
    "examples/security/tisci_msg/.project/project.js",
    // Drivers and kernel tests
    "test/board/flash/.project/project.js",
    "test/drivers/boot/sbl_emmc_linux_multistage_falcon_mode/sbl_emmc_linux_stage1/.project/project.js",
    "test/drivers/boot/sbl_emmc_linux_multistage_falcon_mode/sbl_emmc_linux_stage2/.project/project.js",
    "test/drivers/boot/sbl_ospi_nand_linux_multistage_ddr_ecc/sbl_ospi_nand_linux_stage2/.project/project.js",
    "test/drivers/boot/sbl_ospi_nand_linux_multistage_ddr_ecc/sbl_ospi_nand_linux_stage1/.project/project.js",
    "test/drivers/boot/sbl_uart_custom_boardconfig/.project/project.js",
    "test/drivers/device_manager/sciclient_direct/.project/project.js",
    "test/drivers/device_manager/sciclient_tisci_msg/.project/project.js",
    "test/drivers/device_manager/dm_trace_config/.project/project.js",
    "test/drivers/device_manager/test_device_manager/.project/project.js",
    "test/drivers/device_manager/test_device_manager_system/.project/project.js",
    "test/drivers/epwm/.project/project.js",
    "test/drivers/epwm/test_epwm_system/.project/project.js",
    "test/drivers/ecap/.project/project.js",
    "test/drivers/eqep/.project/project.js",
    "test/drivers/eqep/test_eqep_system/.project/project.js",
    "test/board/eeprom/.project/project.js",
    "test/drivers/fvid2/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/gtc/.project/project.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/i2c/test_i2c_system/.project/project.js",
    "test/drivers/i2c/test_i2c_fault_inject/.project/project.js",
    "test/drivers/ospi/test_ospi_system/.project/project.js",
    "test/drivers/ipc_notify/.project/project.js",
    "test/drivers/ipc_notify_a53/.project/project.js",
    "test/drivers/ipc_notify_c7x/.project/project.js",
    "test/drivers/ipc_notify_mcu_r5/.project/project.js",
    "test/drivers/ipc_rpmsg/.project/project.js",
    "test/drivers/ipc_rpmsg_linux/.project/project.js",
    "test/drivers/ipc_rpmsg_c7x/.project/project.js",
    "test/drivers/ipc_rpmsg_a53/.project/project.js",
    "test/drivers/ipc_rpmsg_mcu_r5f/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Announce_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Diagnostic_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Example_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Multiple_End_Point_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_1_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_2_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_4_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_8_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_16_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_32_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_64_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_128_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal/ipc_rpmsg_mcal_Vring_256_Test/.project/project.js",
    "test/drivers/mcan/.project/project.js",
    "test/drivers/mcan/test_mcan_system/.project/project.js",
    "test/drivers/mcasp/mcasp_auxclk_sel/.project/project.js",
    "test/drivers/mcasp/mcasp_low_latency/.project/project.js",
    "test/drivers/mcasp/mcasp_multiinst_loopback/.project/project.js",
    "test/drivers/mcasp/mcasp_start_stop_test/.project/project.js",
    "test/drivers/mcasp/mcasp/.project/project.js",
    "test/drivers/mcasp/test_mcasp_fault_injection/.project/project.js",
    "test/drivers/mcasp/test_mcasp_system/.project/project.js",
    "test/drivers/pinmux_coverage/.project/project.js",
    "test/drivers/rtc/.project/project.js",
    "test/drivers/rtc/test_rtc_system/.project/project.js",
    "test/drivers/sciclient/sciclient_dynamic_analysis/.project/project.js",
    "test/drivers/sciclient/sciclient_get_version/.project/project.js",
    "test/drivers/sciclient/sciclient_interrupt_mode/.project/project.js",
    "test/drivers/soc_coverage/.project/project.js",
    "test/drivers/ospi/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/drivers/uart/test_uart_fault_inject/.project/project.js",
    "test/drivers/udma_coverage/.project/project.js",
    "test/drivers/mcspi/mcspi/.project/project.js",
    "test/drivers/mcspi/mcspi_master_slave/.project/project.js",
    "test/drivers/mcspi/mcspi_master_slave_dma/.project/project.js",
    "test/drivers/mcspi/test_mcspi_fault_inject/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fs_io/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_raw_io/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fault_inject/.project/project.js",
    "test/drivers/use_cases/audio/audio_player/.project/project.js",
    "test/drivers/udma/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_system/.project/project.js",
    "test/drivers/pmu/.project/project.js",
    "test/drivers/udma/test_udma_fault_inject/.project/project.js",
    "test/drivers/watchdog/.project/project.js",
    "test/drivers/watchdog/test_watchdog_reset/.project/project.js",
    "test/drivers/ddr/.project/project.js",
    "test/drivers/pmu/test_pmu_system/.project/project.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/dpl_mmu_test/.project/project.js",
    "test/kernel/dpl_mpu_test/.project/project.js",
    "test/kernel/dpl/.project/project_safertos.js",
    "test/kernel/freertos/.project/project.js",
    "test/kernel/freertos_smp/.project/project.js",
    "test/kernel/test_smp_kernel/.project/project.js",
    "test/kernel/rov/.project/project.js",
    "test/kernel/smp_tests/disable_multiple_priorities/.project/project.js",
    "test/kernel/smp_tests/disable_preemption/.project/project.js",
    "test/kernel/smp_tests/interrupt_wait_critical/.project/project.js",
    "test/kernel/smp_tests/multiple_tasks_running/.project/project.js",
    "test/kernel/smp_tests/only_one_task_enter_critical/.project/project.js",
    "test/kernel/smp_tests/only_one_task_enter_suspendall/.project/project.js",
    "test/kernel/smp_tests/schedule_affinity/.project/project.js",
    "test/kernel/smp_tests/schedule_equal_priority/.project/project.js",
    "test/kernel/smp_tests/schedule_highest_priority/.project/project.js",
    "test/kernel/smp_tests/suspend_scheduler/.project/project.js",
    "test/kernel/smp_tests/task_delete/.project/project.js",
    "test/security/crypto/test_sa3ul_aes/.project/project.js",
    "test/security/crypto/test_sa3ul_rng/.project/project.js",
    "test/security/crypto/test_sa3ul_sha/.project/project.js",
    "test/kernel/dpl_timer/.project/project.js",
    "test/kernel/dpl_timer/test_dpl_timer_fault_inject/.project/project.js",
    // SDL Examples and tests
    "examples/sdl/dcc/dcc_modes/.project/project.js",
    "examples/sdl/ecc/.project/project.js",
    "examples/sdl/ecc_r5f_cache/.project/project.js",
    "examples/sdl/ecc_sec/.project/project.js",
    "examples/sdl/ecc_tcm/.project/project.js",
    "examples/sdl/esm/mcu_esm0/.project/project.js",
    "examples/sdl/mcrc/mcrc_full_cpu/.project/project.js",
    "examples/sdl/mcrc/mcrc_auto/.project/project.js",
    "examples/sdl/mcrc/mcrc_semi_cpu/.project/project.js",
    "examples/sdl/mtog/mtog_example/.project/project.js",
    "examples/sdl/pbist/pbist_mpu/.project/project.js",
    "examples/sdl/pok/pok_mcu/.project/project.js",
    "examples/sdl/rom_checksum/.project/project.js",
    "examples/sdl/rti/UC1/.project/project.js",
    "examples/sdl/rti/UC2/.project/project.js",
    "examples/sdl/rti/UC3/.project/project.js",
    "examples/sdl/rti/UC4/.project/project.js",
    "examples/sdl/stog/.project/project.js",
    "examples/sdl/vtm/vtm_reset/.project/project.js",
    "examples/sdl/vtm/vtm_uc/.project/project.js",
    "test/sdl/dcc/dcc_unit_test/.project/project.js",
    "test/sdl/dcc/dcc_func_test/.project/project.js",
    "test/sdl/ecc/ecc_sdl_funcTest/.project/project.js",
    "test/sdl/ecc/ecc_sdl_unitTest/.project/project.js",
    "test/sdl/esm/esm_func_test/.project/project.js",
    "test/sdl/esm/esm_unit_test/.project/project.js",
    "test/sdl/lbist/.project/project.js",
    "test/sdl/mcrc/mcrcFuncTest/.project/project.js",
    "test/sdl/mcrc/mcrcUt/.project/project.js",
    "test/sdl/mcrc/mcrcAutomodeTest/.project/project.js",
  	"test/sdl/mcrc/mcrcSemimodeTest/.project/project.js",
    "test/sdl/mtog/mtog_functest/.project/project.js",
    "test/sdl/mtog/mtog_unit_test/.project/project.js",
    "test/sdl/pbist/ip_pbist_test/.project/project.js",
    "test/sdl/pbist/sdl_pbist_test/.project/project.js",
    "test/sdl/pok/pokFuncTest/.project/project.js",
    "test/sdl/pok/pokUt/.project/project.js",
    "test/sdl/rom_checksum/functional_test/.project/project.js",
    "test/sdl/rom_checksum/unit_test/.project/project.js",
    "test/sdl/rti/rtiFuncTest/.project/project.js",
    "test/sdl/rti/rtiUt/.project/project.js",
    "test/sdl/stog/stog_func_test/.project/project.js",
    "test/sdl/stog/stog_unit_test/.project/project.js",
    "test/sdl/vtm/vtm_func_test/.project/project.js",
    "test/sdl/vtm/vtm_unit_test/.project/project.js",

    //Ethfw
    "source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/.project/project.js",
    "source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/.project/project.js",

    // Safety checkers Examples
    "source/safety_checkers/examples/pm_checkers_app/.project/project.js",
    "source/safety_checkers/examples/pm_checkers_warm_reset/.project/project.js",
	"source/safety_checkers/examples/rm_checkers_app/.project/project.js",
    "source/safety_checkers/examples/tifs_checkers_app/.project/project.js",
    "test/drivers/udma/test_udma_system/.project/project.js",
    "test/drivers/ddr/test_ddr_system/.project/project.js",
];

// List of examples available only for ThreadX
const example_file_list_threadx = [
    "examples/kernel/threadx/hello_world/.project/project.js",
    "examples/kernel/threadx/task_switch/.project/project.js",

    // Tests
    "test/kernel/threadx/.project/project.js",
];


function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
        "mcu-r5fss0-0": "MCUSS_Cortex_R5_0_0",
        "r5fss0-0": "MAIN_PULSAR_Cortex_R5_0_0",
        "a53ss0-0": "CortexA53_0",
        "a53ss0-1": "CortexA53_1",
        "a53ss1-0": "CortexA53_2",
        "a53ss1-1": "CortexA53_3",
        "c75ss0-0": "Dsp_core",
    }

    return projectSpecCpu[cpu];
}

function getComponentList() {
    if (getThreadXEnabled())
    {
        component_file_list = component_file_list_common.concat(component_file_list_threadx);
        component_file_list = component_file_list.concat(component_file_list_freertos);
    }
    else
    {
        component_file_list = component_file_list_common.concat(component_file_list_freertos);
    }
    return component_file_list;
}

function getComponentListWithMakefile() {
    return component_file_list_with_makefile;
}

function getExampleList() {

    if (getThreadXEnabled())
    {
        return (example_file_list.concat(example_file_list_threadx));
    }
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "AM62Ax";
}

function getProjectSpecDevice(board) {
    return "AM62Ax";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "AMB";
}

function getSysCfgPart(board) {
    return "Default";
}

function getDevToolTirex(board) {
    return [
        "SK-AM62A-LP",
    ];
}

function getProperty() {
    let property = {};

    property.defines = device_defines;

    return property;
}

function getLinuxFwName(cpu) {

    switch(cpu) {
        case "mcu-r5fss0-0":
            return "mcu-r5f0_0";
        case "r5fss0-0":
            return "wkup-r5f0_0";
        case "c75ss0-0":
            return "c75ss0-0";
    }
    return undefined;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_AM62AX";
}

function getTirexId() {
    return "com.ti.MCU_PLUS_SDK_AM62AX";
}

function getSdkOpn() {
    return "MCU-PLUS-SDK-AM62A";
}

function getFlashAddr() {
    return 0x60000000;
}

module.exports = {
    getComponentList,
    getComponentListWithMakefile,
    getExampleList,
    getSysCfgDevice,
    getSysCfgCpu,
    getSysCfgPkg,
    getSysCfgPart,
    getProjectSpecDevice,
    getProjectSpecCpu,
    getDevToolTirex,
    getProperty,
    getLinuxFwName,
    getProductNameProjectSpec,
    getTirexId,
    getFlashAddr,
    getSdkOpn,
    getThreadXEnabled,
};
