let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getModule() {

    let panelDriverVer = soc.getDriverVer("panel");

    return system.getScript(`/board/panel/${panelDriverVer}/panel_${panelDriverVer}`);
}

exports = getModule();
