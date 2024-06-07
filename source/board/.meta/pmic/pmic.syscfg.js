
let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getModule() {

    let pmicDriverVer = soc.getDriverVer("pmic");

    return system.getScript(`/board/pmic/${pmicDriverVer}/pmic_${pmicDriverVer}`);
}

exports = getModule();
