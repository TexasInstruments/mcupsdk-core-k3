
let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getModule() {

    let hyperRamDriverVer = soc.getDriverVer("hyperRam");

    return system.getScript(`/board/hyperRam/${hyperRamDriverVer}/hyperRam_${hyperRamDriverVer}`);
}

exports = getModule();
