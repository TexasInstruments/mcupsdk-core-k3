const common = require("../common.js");

const component_file_list = [
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    /* TODO: Add when DM adds AM62D support */
    /*
    "source/drivers/dmautils/.project/project.js",
    */
    "source/dhrystone_benchmark/.project/project.js",
    "source/drivers/udma/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "source/security/.project/project.js",
    "source/networking/enet/.project/project_cpsw.js",
    "source/networking/enet/.project/project_cpsw_lwipif_freertos.js",
    "source/networking/enet/.project/project_cpsw_lwipif_nortos.js",
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
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
];

// List of components where makefile is not generated.
const component_file_list_with_makefile = [
    "source/drivers/device_manager/dm_stub/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/sbl/.project/project.js",
];

const device_defines = {
    common: [
    ],
};

const example_file_list = [
    "examples/board/eeprom/eeprom_read_write/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage2/.project/project.js",
    "examples/drivers/boot/sbl_null/.project/project.js",
	"examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage1/.project/project.js",
	"examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage2/.project/project.js",
    "examples/drivers/boot/sbl_sd/.project/project.js",
    "examples/drivers/boot/sbl_uart/.project/project.js",
	"examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage1/.project/project.js",
	"examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/.project/project.js",
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
    "examples/drivers/mcan/mcan_external_read_write/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback/.project/project.js",
    "examples/drivers/mcasp/mcasp_multichannel_in_stereo_out/.project/project.js",
    "examples/drivers/mcasp/mcasp_multichannel_playback/.project/project.js",
    "examples/drivers/mcasp/mcasp_stereo_playback/.project/project.js",
	"examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_dma/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_turbo_mode/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
	"examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_memory_read/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
	"examples/drivers/ipc/ipc_notify_echo/.project/project.js",
	"examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
	"examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/spinlock/spinlock_example/.project/project.js",
	"examples/drivers/uart/uart_echo/.project/project.js",
	"examples/drivers/uart/uart_echo_callback/.project/project.js",
	"examples/drivers/uart/uart_echo_dma/.project/project.js",
	"examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
	"examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/drivers/udma/udma_chaining/.project/project.js",
	"examples/drivers/udma/udma_memcpy_interrupt/.project/project.js",
	"examples/drivers/udma/udma_memcpy_polling/.project/project.js",
	"examples/drivers/udma/udma_sw_trigger/.project/project.js",
	"examples/drivers/watchdog/watchdog_interrupt/.project/project.js",
    "examples/empty/.project/project_freertos.js",
	"examples/empty/.project/project_nortos.js",
	"examples/hello_world/.project/project.js",
	"examples/hello_world_cpp/.project/project.js",
	"examples/kernel/dpl/dpl_demo/.project/project.js",
	"examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
	"examples/kernel/freertos/memcpy_benchmark/.project/project.js",
	"examples/kernel/freertos/posix_demo/.project/project.js",
	"examples/kernel/freertos/smp_task_switch/.project/project.js",
	"examples/kernel/freertos/task_switch/.project/project.js",
    "examples/networking/enet_cpsw_est/.project/project.js",
    "examples/networking/enet_layer2_cpsw/.project/project.js",
    "examples/networking/enet_layer2_cpsw_switch/.project/project.js",
    "examples/networking/enet_loopback/enet_cpsw_loopback/.project/project.js",
    "examples/networking/lwip/cpsw_lwip_https/.project/project.js",
    "examples/networking/lwip/cpsw_lwip_mqtt/.project/project.js",
    "examples/networking/lwip/enet_cpsw_rawhttpserver/.project/project.js",
    "examples/networking/lwip/enet_cpsw_socket/.project/project.js",
    "examples/networking/lwip/enet_cpsw_tcpclient/.project/project.js",
    "examples/networking/lwip/enet_cpsw_tcpserver/.project/project.js",
    "examples/networking/lwip/enet_cpsw_udpclient/.project/project.js",
    "examples/networking/lwip/enet_cpsw_udp_igmp/.project/project.js",
    "examples/networking/lwip/enet_lwip_cpsw/.project/project.js",
    "examples/networking/tsn/gptp_cpsw_app/.project/project.js",
    "examples/networking/tsn/gptp_lwip_cpsw/.project/project.js",
    "examples/networking/tsn/lldp_cpsw_app/.project/project.js",
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
    "examples/security/tisci_msg/.project/project.js",
	"test/board/eeprom/.project/project.js",
	"test/board/flash/.project/project.js",
    "test/drivers/ecap/.project/project.js",
    "test/drivers/epwm/.project/project.js",
    "test/drivers/eqep/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/gtc/.project/project.js",
    "test/drivers/i2c/.project/project.js",
	"test/drivers/ipc_notify/.project/project.js",
    "test/drivers/ipc_notify_benchmark/.project/project.js",
    "test/drivers/ipc_notify_benchmark_l2ram/.project/project.js",
	"test/drivers/ipc_rpmsg/.project/project.js",
	"test/drivers/mcasp/mcasp_multiinst_loopback/.project/project.js",
    "test/drivers/mcasp/mcasp_start_stop_test/.project/project.js",
	"test/drivers/mmcsd/.project/project.js",
	"test/drivers/ospi/.project/project.js",
    "test/drivers/sciclient/.project/project.js",
	"test/drivers/uart/.project/project.js",
	"test/drivers/mcspi/mcspi/.project/project.js",
    "test/kernel/dpl/.project/project.js",
	"test/kernel/freertos/.project/project.js",
	"test/kernel/freertos_smp/.project/project.js",
	"test/kernel/rov/.project/project.js",
	"test/kernel/test_smp_kernel/.project/project.js",
    "test/security/crypto/test_sa3ul_aes/.project/project.js",
    "test/security/crypto/test_sa3ul_rng/.project/project.js",
    "test/security/crypto/test_sa3ul_sha/.project/project.js",
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
    return component_file_list;
}

function getComponentListWithMakefile() {
    return component_file_list_with_makefile;
}

function getExampleList() {
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "AM62Dx";
}

function getProjectSpecDevice(board) {
    return "AM62Dx";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "ANF";
}

function getSysCfgPart(board) {
    return "AM62D24-G";
}

function getDevToolTirex(board) {
    return "AM62Dx_EVM";
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
    return "MCU_PLUS_SDK_AM62DX";
}

function getTirexId() {
    return "com.ti.MCU-PLUS-SDK-AM62DX";
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
};
