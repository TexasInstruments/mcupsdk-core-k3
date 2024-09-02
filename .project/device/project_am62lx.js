const common = require("../common.js");

const component_file_list = [

];

const device_defines = {
    common: [
        "SOC_AM62LX",
    ],
};

const example_file_list = [

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
};