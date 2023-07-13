
let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getModule() {

    let flashDriverVer = soc.getDriverVer("parallelFlash");

    return system.getScript(`/board/flash/parallelFlash/${flashDriverVer}/parallelflash_${flashDriverVer}`);
}

exports = getModule();
