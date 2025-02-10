const common = require("../common.js");

const component_file_list = [
    "source/board/.project/project.js",
    "source/dhrystone_benchmark/.project/project.js",
    "source/drivers/.project/project.js",
    "source/fs/freertos_fat/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "test/unity/.project/project.js",
    "docs_src/docs/api_guide/doxy_samples/.project/project.js",
];

// List of components where makefile is not generated.
const component_file_list_with_makefile = [
    "source/atf/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM62LX",
    ],
};

const example_file_list = [
    "examples/benchmarks/coremark_pro_benchmark/cjpeg-rose7-preset/.project/project.js",
    'examples/benchmarks/coremark_pro_benchmark/core/.project/project.js',
    "examples/benchmarks/coremark_pro_benchmark/linear_alg-mid-100x100-sp/.project/project.js",
    "examples/benchmarks/coremark_pro_benchmark/loops-all-mid-10k-sp/.project/project.js",
    "examples/benchmarks/coremark_pro_benchmark/nnet_test/.project/project.js",
    "examples/benchmarks/coremark_pro_benchmark/parser-125k/.project/project.js",
    "examples/benchmarks/coremark_pro_benchmark/radix2-big-64k/.project/project.js",
    "examples/benchmarks/dhrystone_benchmark/.project/project.js",
    "examples/benchmarks/interrupt_latency_benchmark/.project/project.js",
    "examples/drivers/ecap/ecap_apwm_mode/.project/project.js",
    "examples/drivers/ecap/ecap_epwm_loopback/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle/.project/project.js",
    "examples/drivers/epwm/epwm_duty_cycle_sync/.project/project.js",
    "examples/drivers/eqep/eqep_capture/.project/project.js",
    "examples/drivers/eqep/eqep_frequency_measurement/.project/project.js",
    "examples/drivers/eqep/eqep_position_speed/.project/project.js",
    "examples/drivers/gpio/gpio_input_interrupt/.project/project.js",
    "examples/drivers/gpio/gpio_led_blink/.project/project.js",
    //"examples/drivers/gpmc/gpmc_flash_io/.project/project.js",
    "examples/drivers/i2c/i2c_led_blink/.project/project.js",
    "examples/drivers/i2c/i2c_read/.project/project.js",
    "examples/drivers/i2c/i2c_temperature/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_interrupt/.project/project.js",
    "examples/drivers/mcan/mcan_loopback_polling/.project/project.js",
    "examples/drivers/mcspi/mcspi_loopback/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_8bit/.project/project.js",
    "examples/drivers/mcspi/mcspi_performance_32bit/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_file_io/.project/project.js",
    "examples/drivers/mmcsd/mmcsd_raw_io/.project/project.js",
    "examples/drivers/ospi/ospi_flash_diag/.project/project.js",
    "examples/drivers/ospi/ospi_flash_io/.project/project.js",
    "examples/drivers/uart/uart_echo/.project/project.js",
    "examples/drivers/uart/uart_echo_callback/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_interrupt/.project/project.js",
    "examples/drivers/uart/uart_echo_low_latency_polling/.project/project.js",
    "examples/empty/.project/project_freertos.js",
    "examples/empty/.project/project_nortos.js",
    "examples/hello_world/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project.js",

    // Tests
    "test/drivers/ecap/.project/project.js",
    "test/drivers/epwm/.project/project.js",
    "test/drivers/eqep/.project/project.js",
    "test/drivers/gpio/.project/project.js",
    //"test/drivers/gpmc/.project/project.js",
    "test/drivers/gtc/.project/project.js",
    "test/drivers/i2c/.project/project.js",
    "test/drivers/mmcsd/.project/project.js",
    "test/drivers/ospi/.project/project.js",
    "test/drivers/scp/scmi/.project/project.js",
    "test/drivers/uart/.project/project.js",
    "test/kernel/dpl/.project/project.js",
    "test/kernel/freertos/.project/project.js",
    "test/kernel/rov/.project/project.js",
];

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
        "a53ss0-0": "CortexA53_0",
        "a53ss0-1": "CortexA53_1",
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
    return "AM62Lx";
}

function getProjectSpecDevice(board) {
    return "AM62Lx";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "ANB";
}

function getSysCfgPart(board) {
    return "AM62L32-G-ANB";
}

function getDevToolTirex(board) {
    return "AM62Lx_SK_EVM";
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
    return "MCU_PLUS_SDK_AM62LX";
}

function getTirexId() {
    return "com.ti.MCU_PLUS_SDK_AM62LX";
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
