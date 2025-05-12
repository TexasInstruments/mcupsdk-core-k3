let common = system.getScript("/common");
let soc = system.getScript(`/drivers/soc/drivers_${common.getSocName()}`);

function getModule() {

    let driverVer = soc.getDriverVer("aasrc");

    return system.getScript(`/drivers/aasrc/${driverVer}/aasrc_${driverVer}`);
}

exports = getModule();
