const common = require("../common.js");

const isDMR5Supported = 0;

const component_file_list = [
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "test/unity/.project/project.js",
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM62X",
    ],
};

const example_file_list = [
    //"examples/drivers/boot/sbl_emmc_linux/.project/project.js",
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/.project/project.js",
    "examples/drivers/boot/sbl_null/.project/project.js",
    // "examples/drivers/boot/sbl_ospi_linux/.project/project.js",
    "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/.project/project.js",
    // "examples/drivers/boot/sbl_ospi_nand_linux/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/.project/project.js",
    "examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage2/.project/project.js",
    // "examples/drivers/boot/sbl_sd/.project/project.js",
    "examples/drivers/boot/sbl_uart/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage1/.project/project.js",
    "examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_linux/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_qnx/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/empty/.project/project_freertos.js",
    "examples/empty/.project/project_nortos.js",
    "examples/hello_world/.project/project.js",
    "examples/hello_world_cpp/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/sciclient/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/freertos/.project/project.js",
];

// The following list contains the list of examples only supported by DM R5.
// This will be added  as part of seperate DM R5 package
// THe package in ti.com will not contain these examples

const example_file_list_dm_r5 = [
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/ipc/ipc_notify_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_diag/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
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

function getExampleList() {
    if (isDMR5Supported == 1)
    {
        return example_file_list.concat(example_file_list_dm_r5);
    }
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "AM62x";
}

function getProjectSpecDevice(board) {
    return "AM62x";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "ALW";
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
            return "am62-mcu-m4f0_0-fw";
        case "r5fss0-0":
            return "am62-mcu-r5f0_0-fw";
    }
    return undefined;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_AM62X";
}

function getFlashAddr() {
    return 0x60000000;
}

module.exports = {
    getComponentList,
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
    getFlashAddr,
    getIsDMR5Supported,
};
