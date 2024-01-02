
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/soc/drivers_${common.getSocName()}`);

function getModule() {

    let driverVer = soc.getDriverVer("dss");

    return system.getScript(`/drivers/dss/${driverVer}/dss_${driverVer}`);
}

exports = getModule();
