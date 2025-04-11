
let common = system.getScript("/common");
let soc = system.getScript(`/optiflash/soc/optiflash_${common.getSocName()}`);

function getModule()
{
    let driverVer = soc.getDriverVer("rl2");
    return system.getScript(`/optiflash/rl2/${driverVer}/rl2_${driverVer}`);
}

exports = getModule();
