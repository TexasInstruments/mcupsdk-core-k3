
let common = system.getScript("/common");

let ratBaseAddr_mcu_r5f = 0x7FE0000;
let ratBaseAddr_dm_r5f = 0x2FFE0000;

let longDescription_r5f =
`R5F has a Region Address Translate (RAT) to access memory and peripheral regions beyond 32b address space.
In most cases for R5F, there is no need to program RAT for R5F. Refer to the device TRM for regions that
need a RAT translation mapping.`
    ;

function getRatBaseAddr() {

    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr;

    if(cpu.match(/mcu-r5fss0-0/)) {
        return ratBaseAddr_mcu_r5f;
    }
    else if (cpu.match(/r5fss0-0/)){
        return ratBaseAddr_dm_r5f;
    }
    return ratBaseAddr_mcu_r5f;
}

function getLongDescription() {

    let cpu = common.getSelfSysCfgCoreName();
    let longDescription = longDescription_r5f;
    return longDescription;
}

exports = {
    getRatBaseAddr,
    getLongDescription,
};

