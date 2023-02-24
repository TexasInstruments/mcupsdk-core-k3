
let common = system.getScript("/common");

let intcBaseAddr_mcu_r5f = 0x7ff0000;
let intcBaseAddr_dm_r5f = 0x2fff0000;

function getIntcBaseAddr() {

    let cpu = common.getSelfSysCfgCoreName();
    let intcAddr = intcBaseAddr_mcu_r5f;

    if(cpu.match(/mcu-r5fss0-0/))
    {
        intcAddr = intcBaseAddr_mcu_r5f;
    }
    else if(cpu.match(/r5fss0-0/))
    {
        intcAddr = intcBaseAddr_dm_r5f;
    }
    return intcAddr;
}

exports = {
    getIntcBaseAddr,
};

