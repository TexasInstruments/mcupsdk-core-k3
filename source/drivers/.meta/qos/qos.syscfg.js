
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/soc/drivers_${common.getSocName()}`);

function getModule() {

    let driverVer = soc.getDriverVer("qos");

    return system.getScript(`/drivers/qos/${driverVer}/qos_${driverVer}`);
}

exports = getModule();
