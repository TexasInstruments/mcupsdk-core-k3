
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/soc/drivers_${common.getSocName()}`);

function getModule() {

    let driverVer = soc.getDriverVer("hyperbus");

    return system.getScript(`/drivers/hyperbus/${driverVer}/hyperbus_${driverVer}`);
}

exports = getModule();
