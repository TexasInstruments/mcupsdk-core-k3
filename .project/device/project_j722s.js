const common = require("../common.js");

const component_file_list = [
    /* Libraries */
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/drivers/dmautils/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "source/kernel/safertos/.project/project.js",

    /* Test Libraries */
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
    "test/unity/.project/project.js",
];

// List of components where makefile is not generated.
const component_file_list_with_makefile = [
    "source/drivers/device_manager/rm_pm_hal/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/sbl/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_J722S",
    ],
};

const example_file_list = [
    /* Example Applications */
    "examples/drivers/csirx/csirx_capture_testapp/.project/project.js",
    "examples/drivers/csirx/csirxtx_loopback_test/.project/project.js",
    "examples/drivers/csitx/csitx_transmit_test/.project/project.js",
    "examples/drivers/ddr/ddr_perf/.project/project.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/ipc/ipc_notify_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_linux/.project/project.js",
    "examples/drivers/ipc/ipc_rpmsg_echo_qnx/.project/project.js",
    "examples/drivers/mcan/mcan_response_app/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_tx_dma/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/sciclient/sciclient_ccs_init/.project/project.js",
    "examples/drivers/sciclient/sciclient_get_version/.project/project.js",
    "examples/drivers/sciclient/sciclient_unit_test/.project/project.js",
    "examples/drivers/spinlock/spinlock_demo/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_dma/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/drivers/udma/udma_chaining/.project/project.js",
    "examples/drivers/udma/udma_memcpy_interrupt/.project/project.js",
    "examples/drivers/udma/udma_memcpy_polling/.project/project.js",
    "examples/empty/.project/project_freertos.js",
    "examples/hello_world/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project_safertos.js",
    "examples/kernel/freertos/task_switch/.project/project.js",
    "examples/kernel/safertos/task_switch/.project/project.js",

    /* Test Applications */
    "test/board/flash/.project/project.js",
    "test/drivers/csirx/csirx_ut/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/ipc_notify/.project/project.js",
    "test/drivers/ipc_rpmsg/.project/project.js",
    "test/drivers/mcspi/mcspi/.project/project.js",
    "test/drivers/mmcsd/.project/project.js",
    "test/drivers/sciclient/sciclient_get_version/.project/project.js",
    "test/drivers/ospi/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/dpl_exception_test/.project/project.js",
    "test/kernel/dpl_core_r5_test/.project/project.js",
    "test/kernel/freertos/.project/project.js",
];

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
        "mcu-r5fss0-0": "MCUSS_Cortex_R5_0_0",
        "wkup-r5fss0-0": "WKUP_Cortex_R5_0_0",
        "main-r5fss0-0": "MAIN_Cortex_R5_0_0",
        "c75ss0-0": "DSP_Core_1",
        "c75ss1-0": "DSP_Core_2",
        "a53ss0-0": "CortexA53_0",
        "a53ss0-1": "CortexA53_1",
        "a53ss1-0": "CortexA53_2",
        "a53ss1-1": "CortexA53_3",
        "hsm0-0":   "HSM_Core_0"
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
    return "J722S_TDA4VEN_TDA4AEN_AM67";
}

function getProjectSpecDevice(board) {
    return "J722S";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "AMW";
}

function getSysCfgPart(board) {
    return "Default";
}

function getDevToolTirex(board) {
    return "J722SXH01EVM";
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
        case "wkup-r5fss0-0":
            return "wkup-r5f0_0";
        case "main-r5fss0-0":
            return "main-r5f0_0";
        case "c75ss0-0":
            return "c75ss0-0";
        case "c75ss1-0":
            return "c75ss1-0";
    }
    return undefined;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_J722S";
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
    getFlashAddr,
};
