
let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getModule() {

    let flashDriverVer = soc.getDriverVer("serialFlash");

    return system.getScript(`/board/flash/serialFlash/${flashDriverVer}/serialflash_${flashDriverVer}`);
}

exports = getModule();
