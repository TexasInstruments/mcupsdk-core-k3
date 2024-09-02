
let common = system.getScript("/common");

function getIntcBaseAddr() {

    let cpu = common.getSelfSysCfgCoreName();
}

exports = {
    getIntcBaseAddr,
};
