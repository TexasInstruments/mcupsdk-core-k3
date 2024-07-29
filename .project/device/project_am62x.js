const common = require("../common.js");

const isDMR5Supported = 1;

const component_file_list = [
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    "source/dhrystone_benchmark/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/sdl/.project/project.js",
    "source/sdl/sdl_sbl/.project/project.js",
    "source/safety_checkers/.project/project.js",
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
        "SOC_AM62X",
    ],
};

const example_file_list = [
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_multistage/sbl_emmc_stage2/.project/project.js",
    "examples/drivers/boot/sbl_gpmc_nand_linux_multistage/sbl_gpmc_nand_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_gpmc_nand_linux_multistage/sbl_gpmc_nand_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_null/.project/project.js",
    "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_multistage/sbl_ospi_nand_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_multistage/sbl_ospi_nand_stage2/.project/project.js",
    "examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage2/.project/project.js",
    "examples/drivers/boot/sbl_sd/.project/project.js",
    "examples/drivers/boot/sbl_uart/.project/project.js",
    "examples/drivers/boot/sbl_uart_linux/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage1/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/.project/project.js",
    "examples/drivers/ddr/ddr_ecc_test_main_esm/.project/project.js",
    "examples/drivers/ddr/ddr_ecc_test_mcu_esm/.project/project.js",
    "examples/drivers/ddr/ddr_perf/.project/project.js",
    "examples/drivers/ecap/ecap_apwm_mode/.project/project.js",
    "examples/drivers/ecap/ecap_epwm_loopback/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle_sync/.project/project.js",
    "examples/drivers/eqep/eqep_capture/.project/project.js",
    "examples/drivers/eqep/eqep_frequency_measurement/.project/project.js",
    "examples/drivers/eqep/eqep_position_speed/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/gpmc/gpmc_flash_io/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/ipc/ipc_notify_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_linux/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_qnx/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback/.project/project.js",
    "examples/drivers/mcasp/mcasp_playback_codec_aic31/.project/project.js",
    "examples/drivers/mcasp/mcasp_loopback_ext_hclk/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback_dma/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/safety/mcu_bist_result/.project/project.js",
    "examples/drivers/safety/reset_isolation/.project/project.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/spinlock/spinlock_example/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_dma/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/drivers/udma/udma_memcpy_polling/.project/project.js",
    "examples/drivers/udma/udma_memcpy_interrupt/.project/project.js",
    "examples/drivers/udma/udma_chaining/.project/project_am62x.js",
    "examples/drivers/udma/udma_sw_trigger/.project/project_am62x.js",
    "examples/drivers/watchdog/watchdog_interrupt/.project/project.js",
    "examples/empty/.project/project_freertos.js",
    "examples/empty/.project/project_nortos.js",
    "examples/hello_world/.project/project.js",
    "examples/hello_world_cpp/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/freertos/memcpy_benchmark/.project/project.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project.js",
    "examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
    "examples/otp/ext_otp/.project/project.js",
    "examples/safety/safety_app/.project/project.js",
    "examples/security/fwl_exception_log/.project/project.js",
    "examples/security/fwl_exception_trigger/.project/project.js",

    // Driver/Kernel tests
    "test/board/flash/.project/project.js",
    "test/drivers/boot/sbl_ospi_linux_multistage_ddr_ecc/sbl_ospi_linux_stage1/.project/project.js",
    "test/drivers/boot/sbl_ospi_linux_multistage_ddr_ecc/sbl_ospi_linux_stage2/.project/project.js",
    "test/drivers/boot/sbl_ospi_nand_linux_multistage_ddr_ecc/sbl_ospi_nand_linux_stage1/.project/project.js",
    "test/drivers/boot/sbl_ospi_nand_linux_multistage_ddr_ecc/sbl_ospi_nand_linux_stage2/.project/project.js",
    "test/drivers/boot/sbl_uart_custom_boardconfig/.project/project.js",
    "test/drivers/device_manager/sciclient_direct/.project/project.js",
    "test/drivers/device_manager/sciclient_tisci_msg/.project/project.js",
    "test/drivers/ecap/.project/project.js",
    "test/drivers/epwm/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/gpmc/.project/project.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/sciclient/sciclient_get_version/.project/project.js",
    "test/drivers/ipc_notify/.project/project.js",
    "test/drivers/ipc_rpmsg/.project/project.js",
    "test/drivers/mcasp/mcasp_start_stop_test/.project/project.js",
    "test/drivers/mcasp/mcasp_multiinst_loopback/.project/project.js",
    "test/drivers/mcspi/mcspi/.project/project.js",
    "test/drivers/mmcsd/.project/project.js",
    "test/drivers/ospi/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/freertos/.project/project.js",

    // SDL Examples and Tests
    "examples/sdl/dcc/dcc_modes/.project/project.js",
    "examples/sdl/ecc/.project/project.js",
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
    "examples/sdl/stog_r5f/.project/project.js",
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
    "test/sdl/stog/stog_func_test/.project/project.js",
    "test/sdl/stog/stog_func_test_r5f_1/.project/project.js",
    "test/sdl/stog/stog_func_test_r5f_2/.project/project.js",
    "test/sdl/stog/stog_unit_test/.project/project.js",
    "test/sdl/rom_checksum/functional_test/.project/project.js",
    "test/sdl/rom_checksum/unit_test/.project/project.js",
    "test/sdl/rti/rtiUt/.project/project.js",
    "test/sdl/rti/rtiFuncTest/.project/project.js",
    "test/sdl/vtm/vtm_func_test/.project/project.js",
    "test/sdl/vtm/vtm_unit_test/.project/project.js",

    // Safety checkers Examples
    "source/safety_checkers/examples/pm_checkers_app/.project/project.js",
    "source/safety_checkers/examples/pm_checkers_warm_reset/.project/project.js",
	"source/safety_checkers/examples/rm_checkers_app/.project/project.js",
    "source/safety_checkers/examples/tifs_checkers_app/.project/project.js",
];

function getIsDMR5Supported()
{
    return isDMR5Supported;
}

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
        "r5fss0-0": "MAIN_PULSAR_Cortex_R5_0_0",
        "m4fss0-0": "Cortex_M4F_0",
        "a53ss0-0": "CortexA53_0",
        "a53ss0-1": "CortexA53_1",
        "a53ss1-0": "CortexA53_2",
        "a53ss1-1": "CortexA53_3",
        "icssm-pru0": "ICSSM_PRU_0",
        "icssm-pru1": "ICSSM_PRU_1",
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
    if (board == "am62x-sip-sk")
    {
        return "AM62SIP";
    }
    else
    {
        return "AM62x";
    }
}

function getProjectSpecDevice(board) {
    return "AM62x";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    if (board == "am62x-sk-lp")
    {
        return "AMC";
    }
    else if (board == "am62x-sip-sk")
    {
        return "AMK";
    }
    else
    {
        return "ALW";
    }

}

function getSysCfgPart(board) {
    return "Default";
}

function getDevToolTirex(board) {
    return "AM62x_SK_EVM";
}

function getProperty() {
    let property = {};

    property.defines = device_defines;

    return property;
}

function getLinuxFwName(cpu) {

    switch(cpu) {
        case "m4fss0-0":
            return "mcu-m4f0_0";
        case "r5fss0-0":
            return "wkup-r5f0_0";
    }
    return undefined;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_AM62X";
}

function getTirexId() {
    return "com.ti.MCU_PLUS_SDK_AM62X";
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
    getIsDMR5Supported,
};
