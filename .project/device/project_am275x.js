const common = require("../common.js");

const component_file_list = [
    "source/board/.project/project.js",
    "source/cmsis/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/udma/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/drivers/dmautils/.project/project.js",
    "source/dhrystone_benchmark/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "source/networking/enet/.project/project_cpsw.js",
    "source/networking/enet/.project/project_cpsw_lwipif_freertos.js",
    "source/networking/enet/.project/project_cpsw_lwipif_nortos.js",
    "source/networking/lwip/.project/project_contrib_freertos.js",
    "source/networking/lwip/.project/project_contrib_nortos.js",
    "source/networking/lwip/.project/project_stack_freertos.js",
    "source/networking/lwip/.project/project_stack_nortos.js",
    "source/networking/tsn/.project/project_tsn_combase.js",
    "source/networking/tsn/.project/project_tsn_gptp.js",
    "source/networking/tsn/.project/project_tsn_uniconf.js",
    "source/networking/tsn/.project/project_tsn_unibase.js",
    "source/sdl/.project/project.js",
    "source/sdl/sdl_sbl/.project/project.js",
    "source/signal_processing/.project/project.js",
    "test/unity/.project/project.js",
    "test/drivers/i2c/test_i2c_fault_inject/configs/.project/project_am275x.js",
    "test/drivers/mmcsd/test_mmcsd_fault_inject/configs/.project/project.js",
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
];


// List of components where makefile is not generated.
// Linux-only components (not built on Windows)
const component_file_list_with_makefile_linux_only = [
    "source/fftlib/.project/project.js",
    "source/mathlib/.project/project.js",
    "source/vxlib/.project/project.js",
    "source/dsplib/.project/project.js",
    "source/audiolib/.project/project.js",
    "source/tisp/.project/project.js",
];

const component_file_list_with_makefile = [
    ...component_file_list_with_makefile_linux_only,
    "source/drivers/device_manager/rm_pm_hal/.project/project.js",
    // "source/drivers/device_manager/rm_pm_hal/sbl/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM275X",
    ],
};

const example_file_list = [
    /* SBLs */
    "examples/drivers/boot/sbl_emmc/.project/project.js",
    "examples/drivers/boot/sbl_eth_uniflash/.project/project.js",
    "examples/drivers/boot/sbl_null/.project/project.js",
    "examples/drivers/boot/sbl_ospi/.project/project.js",
    "examples/drivers/boot/sbl_sd/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash/.project/project.js",
    "examples/drivers/boot/sbl_uart/.project/project.js",
    "examples/drivers/boot/sbl_jtag_uniflash/.project/project_am275x_wkupr5.js",
    /* Examples */
    "examples/benchmarks/dhrystone_benchmark/.project/project_am275x.js",
    "examples/benchmarks/hyperRam_xip_benchmark/.project/project.js",
    "examples/benchmarks/memory_latency_benchmark/.project/project.js",
    "examples/benchmarks/xip_benchmark/.project/project.js",
    "examples/board/eeprom/eeprom_read_write/.project/project.js",
    "examples/board/hyperRam/hyperRam_ecc_esm_test/.project/project_am275x_wkupr5.js",
    "examples/board/hyperRam/hyperRam_ecc_esm_test/.project/project_am275x.js",
    "examples/board/hyperRam/hyperRam_ecc_test/.project/project_am275x_wkupr5.js",
    "examples/board/hyperRam/hyperRam_ecc_test/.project/project.js",
    "examples/board/hyperRam/hyperRam_perf/.project/project_am275x_wkupr5.js",
    "examples/board/hyperRam/hyperRam_perf/.project/project.js",
    "examples/dmautils/dmautils_autoinc_1d2d3d/.project/project.js",
    "examples/dmautils/dmautils_autoinc_circular/.project/project.js",
    "examples/dmautils/dmautils_autoincrement/.project/project.js",
    "examples/drivers/aasrc/aasrc_multichannel_playback/.project/project.js",
    "examples/drivers/aasrc/aasrc_sinewave_conversion/.project/project.js",
    "examples/drivers/aasrc/aasrc_stereo_playback/.project/project.js",
    "examples/drivers/adc/adc_singleshot/.project/project_am275x.js",
    "examples/drivers/ecap/ecap_apwm_mode/.project/project.js",
    "examples/drivers/ecap/ecap_epwm_loopback/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle_sync/.project/project.js",
    "examples/drivers/flc/.project/project_am275x.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_memory_read/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/ipc/ipc_notify_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_rtos_audio_filter_offload/.project/project.js",
    "examples/drivers/mcan/mcan_external_read_write/.project/project_am275x.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcasp/mcasp_audio_presentation_time/.project/project.js",
    "examples/drivers/mcasp/mcasp_aec_multichannel_playback/.project/project.js",
    "examples/drivers/mcasp/mcasp_chime_tad5212/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback/.project/project.js",
    "examples/drivers/mcasp/mcasp_multichannel_playback/.project/project.js",
    "examples/drivers/mcasp/mcasp_stereo_playback/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_dma/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_turbo_mode/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project_am275x_wkupr5.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project_am275x_wkupr5.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_diag/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project_am275x_wkupr5.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/ospi/ospi_phy_grapher_uart/.project/project.js",
    "examples/drivers/pmic/pmic_qa_watchdog_interrupt/.project/project.js",
    "examples/drivers/pmic/pmic_qa_watchdog_reset/.project/project.js",
    "examples/drivers/pmic/pmic_trigger_watchdog_interrupt/.project/project.js",
    "examples/drivers/pmic/pmic_trigger_watchdog_reset/.project/project.js",
    "examples/drivers/pmic/pmic_user_reg_cfg/.project/project.js",
    "examples/drivers/pmu/pmu_multievent/.project/project_am275x_wkupr5.js",
    "examples/drivers/pmu/pmu_multievent/.project/project.js",
    "examples/drivers/rl2/.project/project.js",
    "examples/drivers/rtc/rtc_led_blink/.project/project.js",
    "examples/drivers/sciclient/sciclient_ccs_init/.project/project_am275x_wkupr5.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project_am275x_wkupr5.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/spinlock/spinlock_example/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_dma/.project/project.js",
    "examples/drivers/uart/uart_echo_dma_multi_instance/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/drivers/udma/udma_chaining/.project/project.js",
    "examples/drivers/udma/udma_memcpy_interrupt/.project/project.js",
    "examples/drivers/udma/udma_memcpy_polling/.project/project_am275x_wkupr5.js",
	"examples/drivers/udma/udma_memcpy_polling/.project/project.js",
	"examples/drivers/udma/udma_sw_trigger/.project/project.js",
    "examples/drivers/watchdog/watchdog_interrupt/.project/project_am275x_wkupr5.js",
    "examples/drivers/watchdog/watchdog_interrupt/.project/project.js",
    "examples/empty/.project/project_nortos.js",
    "examples/empty/.project/project_am275x_freertos_wkupr5.js",
    "examples/empty/.project/project_freertos.js",
    "examples/hello_world/.project/project_am275x_wkupr5.js",
    "examples/hello_world/.project/project.js",
	"examples/hello_world_cpp/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project_am275x_wkupr5.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/dpl/test_data_abort/.project/project_am275x.js",
    "examples/kernel/dpl/test_prefetch_abort/.project/project_am275x.js",
    "examples/kernel/dpl/test_undef/.project/project_am275x.js",
    "examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
    "examples/kernel/freertos/memcpy_benchmark/.project/project_am275x_wkupr5.js",
    "examples/kernel/freertos/memcpy_benchmark/.project/project_am275x.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project_am275x_wkupr5.js",
    "examples/kernel/freertos/task_switch/.project/project.js",
    "examples/lpm/lpm_partial_io/.project/project.js",
    "examples/security/tisci_msg/.project/project_am275x.js",
    "source/networking/enet/core/examples/enet_cpsw_est/.project/project_am275x.js",
    "source/networking/enet/core/examples/enet_cpsw_fast_startup/.project/project.js",
    "source/networking/enet/core/examples/enet_layer2_cpsw/.project/project_am275x.js",
    "source/networking/enet/core/examples/enet_layer2_cpsw_switch/.project/project_am275x.js",
    "source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback/loopback_mac_end/.project/project.js",
    "source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback/loopback_phy_end/.project/project.js",
    "source/networking/enet/core/examples/lwip/enet_cpsw_tcpserver/.project/project.js",
    "source/networking/enet/core/examples/lwip/enet_lwip_cpsw/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcmlistener_app/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcmtalker_app/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcm_audio_demo/auto_amplifier/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcm_audio_demo/central_compute/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcm_audio_etherring_demo/auto_amplifier/.project/project.js",
    "source/networking/enet/core/examples/tsn/aafpcm_audio_etherring_demo/central_compute/.project/project.js",
    "source/networking/enet/core/examples/tsn/aes3_aaf/aes3_aaflistener_app/.project/project_am275x.js",
    "source/networking/enet/core/examples/tsn/aes3_aaf/aes3_aaftalker_app/.project/project_am275x.js",
    "source/networking/enet/core/examples/tsn/avb_autoamplifier_demo/audio_sink/.project/project.js",
    "source/networking/enet/core/examples/tsn/avb_autoamplifier_demo/audio_sink_with_crf/.project/project.js",
    "source/networking/enet/core/examples/tsn/avb_autoamplifier_demo/audio_source/.project/project.js",
    "source/networking/enet/core/examples/tsn/avb_autoamplifier_demo/audio_source_with_crf/.project/project.js",
    "source/networking/enet/core/examples/tsn/avtptalker_crflistener/.project/project.js",
    "source/networking/enet/core/examples/tsn/avtplistener_crftalker/.project/project.js",
    "source/networking/enet/core/examples/tsn/crflistener_app/.project/project.js",
    "source/networking/enet/core/examples/tsn/crftalker_app/.project/project.js",
    "source/networking/enet/core/examples/tsn/enet_multistream_mcr/crflistener/.project/project.js",
    "source/networking/enet/core/examples/tsn/enet_multistream_mcr/crftalker/.project/project.js",
    "source/networking/enet/core/examples/tsn/gptp_cpsw_app/.project/project.js",
    "source/networking/enet/core/test/clock_sync_demo/.project/project_am275x.js",
    /* SDL Examples */
    "examples/sdl/dcc/dcc_modes/.project/project_am275x.js",
    "examples/sdl/ecc/.project/project.js",
    "examples/sdl/ecc_r5f_cache/.project/project.js",
    "examples/sdl/ecc_sec/.project/project.js",
    "examples/sdl/ecc_tcm/.project/project.js",
    "examples/sdl/esm/mcu_esm0/.project/project.js",
    "examples/sdl/mcrc/mcrc_auto/.project/project.js",
    "examples/sdl/mcrc/mcrc_full_cpu/.project/project.js",
    "examples/sdl/mcrc/mcrc_semi_cpu/.project/project.js",
    "examples/sdl/pbist/pbist_mpu/.project/project_am275x.js",
    "examples/sdl/pok/pok_mcu/.project/project.js",
    "examples/sdl/rom_checksum/.project/project.js",
    "examples/sdl/rti/UC1/.project/project_am275x.js",
    "examples/sdl/rti/UC2/.project/project_am275x.js",
    "examples/sdl/rti/UC3/.project/project_am275x.js",
    "examples/sdl/rti/UC4/.project/project_am275x.js",
    "examples/sdl/vtm/vtm_reset/.project/project_am275x.js",
    "examples/sdl/vtm/vtm_uc/.project/project_am275x.js",
    // TISP Examples
    "examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload/.project/project.js",
    "examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/.project/project.js",
    "examples/tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch/.project/project.js",
    "examples/tisp/sigchain_dsp_rt/sigchain_eq_gain_mute/.project/project.js",
    "examples/tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain/.project/project.js",
    /* Signnal Processing Examples */
    "examples/signal_processing/calcratio/.project/project.js",
    "examples/signal_processing/swasrc_multichannel_playback/.project/project.js",
    /* SDL Tests */
    "test/sdl/dcc/dcc_func_test/.project/project_am275x.js",
    "test/sdl/dcc/dcc_unit_test/.project/project_am275x.js",
    "test/sdl/ecc/ecc_sdl_funcTest/.project/project.js",
    "test/sdl/ecc/ecc_sdl_unitTest/.project/project.js",
    "test/sdl/esm/esm_func_test/.project/project_am275x.js",
    "test/sdl/esm/esm_unit_test/.project/project_am275x.js",
    "test/sdl/lbist/.project/project.js",
    "test/sdl/mcrc/mcrcAutomodeTest/.project/project.js",
    "test/sdl/mcrc/mcrcFuncTest/.project/project.js",
    "test/sdl/mcrc/mcrcSemimodeTest/.project/project.js",
    "test/sdl/mcrc/mcrcUt/.project/project.js",
    "test/sdl/pbist/ip_pbist_test/.project/project_am275x.js",
    "test/sdl/pbist/sdl_pbist_test/.project/project_am275x.js",
    "test/sdl/pok/pokFuncTest/.project/project.js",
    "test/sdl/pok/pokUt/.project/project.js",
    "test/sdl/rom_checksum/functional_test/.project/project.js",
    "test/sdl/rom_checksum/unit_test/.project/project.js",
    "test/sdl/rti/rtiFuncTest/.project/project_am275.js",
    "test/sdl/rti/rtiUt/.project/project_am275x.js",
    "test/sdl/vtm/vtm_func_test/.project/project_am275x.js",
    "test/sdl/vtm/vtm_unit_test/.project/project_am275x.js",
    // Tests
    "test/drivers/adc/.project/project.js",
    "test/board/eeprom/.project/project.js",
    "test/board/hyperRam/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/gpio/.project/project_am275x_wkupr5.js",
    "test/drivers/gtc/.project/project.js",
    "test/drivers/gtc/.project/project_am275x_wkupr5.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/i2c/.project/project_am275x_wkupr5.js",
    "test/drivers/i2c/test_i2c_fault_inject/.project/project.js",
    "test/drivers/i2c/test_i2c_fault_inject/.project/project_am275x_wkupr5.js",
    "test/drivers/ipc_notify/.project/project.js",
    "test/drivers/ipc_notify_c7x/.project/project.js",
    "test/drivers/ipc_notify_benchmark/.project/project.js",
    "test/drivers/ipc_rpmsg/.project/project.js",
    "test/drivers/ipc_rpmsg_c7x/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Announce_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Diagnostic_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Example_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Multiple_End_Point_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Vring_1_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Vring_2_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Vring_4_Test/.project/project.js",
    "test/drivers/ipc_rpmsg_mcal_Vring_8_Test/.project/project.js",
    "test/drivers/mcasp/mcasp_300Hz/.project/project.js",
    "test/drivers/mcasp/mcasp_auxclk_sel/.project/project.js",
    "test/drivers/mcasp/mcasp_buffer_format/.project/project.js",
    "test/drivers/mcasp/mcasp_low_latency/.project/project.js",
    "test/drivers/mcasp/mcasp_multicore/.project/project.js",
    "test/drivers/mcasp/mcasp_multiinst_loopback/.project/project.js",
    "test/drivers/mcasp/mcasp_presentation_time/.project/project_am275x.js",
    "test/drivers/mcasp/mcasp_start_stop_test/.project/project_am275x.js",
    "test/drivers/mcspi/mcspi/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_raw_io/.project/project_am275x_wkupr5.js",
    "test/drivers/mmcsd/test_mmcsd_raw_io/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fault_inject/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fault_inject/.project/project_am275x_wkupr5.js",
    "test/drivers/mmcsd/test_mmcsd_fs_io/.project/project.js",
    "test/drivers/mmcsd/test_mmcsd_fs_io/.project/project_am275x_wkupr5.js",
    "test/drivers/optiflash/.project/project.js",
    "test/drivers/ospi/.project/project_am275x_wkupr5.js",
    "test/drivers/ospi/.project/project.js",
    "test/drivers/watchdog/test_watchdog_system/.project/project.js",
    "test/drivers/rtc/.project/project_am275x.js",
    "test/drivers/sciclient/sciclient_get_version/.project/project_am275x_wkupr5.js",
    "test/drivers/sciclient/sciclient_get_version/.project/project.js",
    "test/drivers/sciclient/sciclient_interrupt_mode/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/drivers/watchdog/.project/project.js",
    "test/fileio/.project/project.js",
    "test/kernel/dpl/.project/project_am275x_wkupr5.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/dpl_mmu_test/.project/project.js",
    "test/kernel/freertos/.project/project_am275x_wkupr5.js",
    "test/kernel/freertos/.project/project.js",
    "test/drivers/mcan/.project/project.js",
    "test/drivers/mcan/test_mcan_system/.project/project.js",

];

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
    }

    return projectSpecCpu[cpu];
}

function getComponentList() {
    return component_file_list;
}

function getComponentListWithMakefile() {
    return component_file_list_with_makefile;
}

function getLinuxOnlyComponentList() {
    return component_file_list_with_makefile_linux_only;
}

function getExampleList() {
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "AM275x";
}

function getProjectSpecDevice(board) {
    return "AM275x";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "ANJ";
}

function getSysCfgPart(board) {
    return "AM2754";
}

function getDevToolTirex(board) {
    return "AUDIO-AM275-EVM";
}

function getProperty() {
    let property = {};

    property.defines = device_defines;

    return property;
}

function getLinuxFwName(cpu) {
    return undefined;
}

function getProductNameProjectSpec() {
    return "AM275_FREERTOS_SDK";
}

function getTirexId() {
    return "AM275-FREERTOS-SDK";
}

function getSdkOpn() {
    return "AM275-FREERTOS-SDK";
}
function getFlashAddr() {
    return 0x60000000;
}

module.exports = {
    getComponentList,
    getComponentListWithMakefile,
    getLinuxOnlyComponentList,
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
    getSdkOpn,
    getFlashAddr,
};
