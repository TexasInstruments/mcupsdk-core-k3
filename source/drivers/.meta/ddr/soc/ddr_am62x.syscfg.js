
const staticConfig =
{
    clockIds: [ "TISCI_DEV_EMIF_DATA_ISO_VD", "TISCI_DEV_DDR16SS0" ],
};

let defaultDdrConfigFile = "drivers/ddr/v0/soc/am62x/board_ddrReginit.h"

function getDefaultDdrConfigFileName() {
    return defaultDdrConfigFile;
}

function getStaticConfig()
{
    return staticConfig;
}

exports = {
    getDefaultDdrConfigFileName,
    getStaticConfig,
};
