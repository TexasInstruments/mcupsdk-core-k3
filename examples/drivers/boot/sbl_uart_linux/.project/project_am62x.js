let path = require('path');

let device = "am62x";

const files = {
    common: [
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "sciclient_direct_sbl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_UART_LINUX";

const robot_template = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: UART Linux SBL",
        testCaseIds: "SITSW-1758",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_uart_linux_${DEVICE_TYPE}.cfg",
        useBootloader: true,
        useNFS: true,
        bootMode: null,
        timeout: 900,
        expectTimeout: 30,
        boardExpectations: {
            "am62x-sk": [
                { port: "USB0", string: "Arago Project", timeout: 300 },
                { port: "USB0", string: "am62xx-evm login:", timeout: 300 },
                { port: "USB0", send: "root", string: "root@am62xx-evm" },
                { port: "USB0", send: "rpmsg_char_simple -r15", string: "TEST STATUS: PASSED" },
                { port: "USB0", send: "rpmsg_char_simple -r9", string: "TEST STATUS: PASSED" },
                { port: "USB2", string: "Starting Sciserver..... PASSED" },
                { port: "USB3", string: "Remote Core waiting for messages at end point" },
            ],
            "am62x-sip-sk": [
                { port: "USB0", string: "Arago Project", timeout: 300 },
                { port: "USB0", string: "am62xxsip-evm login:", timeout: 300 },
                { port: "USB0", send: "root", string: "root@am62xxsip-evm" },
                { port: "USB0", send: "rpmsg_char_simple -r15", string: "TEST STATUS: PASSED" },
                { port: "USB0", send: "rpmsg_char_simple -r9", string: "TEST STATUS: PASSED" },
                { port: "USB2", string: "Starting Sciserver..... PASSED" },
                { port: "USB3", string: "Remote Core waiting for messages at end point" },
            ],
            "am62x-sk-lp": [
                { port: "USB0", string: "Arago Project", timeout: 300 },
                { port: "USB0", string: "am62xx-lp-evm login:", timeout: 300 },
                { port: "USB0", send: "root", string: "root@am62xx-lp-evm" },
                { port: "USB0", send: "rpmsg_char_simple -r15", string: "TEST STATUS: PASSED" },
                { port: "USB0", send: "rpmsg_char_simple -r9", string: "TEST STATUS: PASSED" },
                { port: "USB2", string: "Starting Sciserver..... PASSED" },
                { port: "USB3", string: "Remote Core waiting for messages at end point" },
            ],
        },
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos"},

];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_uart_linux";
    property.isInternal = false;
    property.isBootLoader = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
