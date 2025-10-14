let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/mcasp/soc/mcasp_${common.getSocName()}`);
let clocking = system.getScript("/drivers/mcasp/v1/mcasp_clocking/mcasp_clocking.js");

const EXTERNAL_CLOCK = 0;
const INTERNAL_CLOCK = 1;

function getConfigArr() {
    return soc.getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let solution = moduleInstance[getInterfaceName(moduleInstance)].$solution;
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === solution.peripheralName);

     return {
        ...config,
        ...moduleInstance,
     };
};

function getClockEnableIds(instance) {
    let instConfig = getInstanceConfig(instance);
    return instConfig.clockIds;
}

function getClockFrequencies(inst) {
    let instConfig = getInstanceConfig(inst);

    return instConfig.clockFrequencies;
}

function pinmuxRequirements(inst) {

    let interfaceName = getInterfaceName(inst);
    let resources = [];
    let systemResources = [];
    if (inst.enableMcaspTx == true) {
        resources.push( pinmux.getPinRequirements(interfaceName, "AFSX", "Frame Sync Transmit Pin") );
        resources.push( pinmux.getPinRequirements(interfaceName, "ACLKX", "Audio Clock Transmit Pin") );
    }
    if (inst.enableMcaspRx == true) {
        resources.push( pinmux.getPinRequirements(interfaceName, "AFSR", "Frame Sync Receive Pin") );
        resources.push( pinmux.getPinRequirements(interfaceName, "ACLKR", "Audio Clock Receive") );

    }

    if (inst.txHclkSource == EXTERNAL_CLOCK || inst.rxHclkSource  == EXTERNAL_CLOCK)
    {
        systemResources = soc.getPinmuxReq(inst.txHclkSourceMux, inst.rxHclkSourceMux);
    }

    let mcasp = {
        name: interfaceName,
        displayName: "MCASP Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    let systemPinmux = soc.getSystemPinmux(systemResources);

    return [mcasp, systemPinmux];
}

function getPeripheralPinNames(inst) {

    let pins = [ "AFSR", "ACLKR", "AFSX", "ACLKX"];
    let extPins = soc.getExtClkPins();

    pins = pins.concat(extPins);

    return pins;
}

function calculateOptimalDividersTx(inst) {
    /* HCLKXDIV range: 1 to 4096
       CLKXDIV range: 1 to 32 */

    let AUXCLK = clocking.getMcaspAuxClkFreq(inst);

    let targetACLKX = inst.fsx*1000*inst.NumTxSlots*inst.TxSlotSize;

    let bestHCLKXDIV = 1;
    let bestCLKXDIV = 1;
    let closestACLKX = AUXCLK;
    let minDiff = Math.abs(AUXCLK - targetACLKX);

    /* The theoretical total division needed */
    const theoreticalDivider = AUXCLK / targetACLKX;

    /* For each possible HCLKXDIV value (2-4096) */
    /* Iteration start from 2 for legacy reason */
    for (let hclkxdiv = 2; hclkxdiv <= 4096; hclkxdiv++) {
        /* Calculate the ideal HCLKXDIV value for this CLKXDIV */
        const idealCLKXDIV = theoreticalDivider / hclkxdiv;

        /* Check the two closest integer values for HCLKXDIV */
        const candidates = [
            Math.floor(idealCLKXDIV),
            Math.ceil(idealCLKXDIV)
        ];

        for (const clkxdiv of candidates) {
            /* Ensure CLKXDIV is within valid range */
            if (clkxdiv < 1 || clkxdiv > 32) continue;

            /* Calculate the resulting frequency */
            const resultFreq = AUXCLK / (clkxdiv * hclkxdiv);
            const diff = Math.abs(resultFreq - targetACLKX);

            /* If this combination gives a closer frequency, update our best values */
            if (diff < minDiff) {
                minDiff = diff;
                bestHCLKXDIV = hclkxdiv;
                bestCLKXDIV = clkxdiv;
                closestACLKX = resultFreq;
            }
        }
    }

    /* Check if HCLKXDIV = 1 is the best */
    const resultFreq = AUXCLK / (1*1);
    const diff = Math.abs(resultFreq - targetACLKX);
    if(diff < minDiff) {
        minDiff = diff;
        bestHCLKXDIV = 1;
        bestCLKXDIV = 1;
        closestACLKX = resultFreq;
    }

    /* Above calculated dividers will be applicable if HCLK, BCLK, FSYNC is internal */
    if((inst.txHclkSource == INTERNAL_CLOCK) &&
       (inst.txAclkSource == INTERNAL_CLOCK))
    {
        inst.txHclkDiv = bestHCLKXDIV;
        inst.txClkDiv = bestCLKXDIV;
        return {
            HCLKXDIV: bestHCLKXDIV,
            CLKXDIV: bestCLKXDIV,
            calculatedACLKX: closestACLKX,
            error: minDiff,
            errorPercentage: (minDiff / targetACLKX) * 100
        };
    }

    /* (External HCLK) & (FSYNC, BCLK internal) */
    if((inst.txHclkSource == EXTERNAL_CLOCK) &&
       (inst.txAclkSource == INTERNAL_CLOCK))
    {
        inst.txHclkExpected = targetACLKX*bestCLKXDIV;
        inst.txHclkDiv = 1;
        inst.txClkDiv = bestCLKXDIV;
        return {
            HCLKXDIV: 1,
            CLKXDIV: bestCLKXDIV,
            calculatedACLKX: targetACLKX,
            error: 0,
            errorPercentage: 0
        };
    }

    /* External BCLK */
    if(inst.txAclkSource == EXTERNAL_CLOCK)
    {
        inst.txHclkDiv = bestHCLKXDIV;
        inst.txClkDiv = 1;
        return {
            HCLKXDIV: bestHCLKXDIV,
            CLKXDIV: 1,
            calculatedACLKX: targetACLKX,
            error: 0,
            errorPercentage: 0
        };
    }
    else
    {
        inst.txHclkDiv = bestHCLKXDIV;
        inst.txClkDiv = bestCLKXDIV;
        let hclkFreq = 0;
        let bclkFreq = 0;

        let error = 0;

        if(inst.txHclkSource == INTERNAL_CLOCK)
        {
            hclkFreq = clocking.getMcaspAuxClkFreq(inst)/bestHCLKXDIV;
            bclkFreq = hclkFreq/bestCLKXDIV;
            error = Math.abs(bclkFreq - targetACLKX);
            errorPercentage = (error / targetACLKX) * 100;
        }
        else
        {
            bestHCLKXDIV = 1;
            inst.txHclkDiv = bestHCLKXDIV;
            bclkFreq = targetACLKX;
        }
        return {
            HCLKXDIV: bestHCLKXDIV,
            CLKXDIV: bestCLKXDIV,
            calculatedACLKX: bclkFreq,
            error: error,
            errorPercentage: errorPercentage
        };
    }
}

function calculateOptimalDividersRx(inst) {
    /* HCLKRDIV range: 1 to 4096
       CLKRDIV range: 1 to 32 */
    let AUXCLK = clocking.getMcaspAuxClkFreq(inst);

    let targetACLKR = inst.fsr*1000*inst.NumRxSlots*inst.RxSlotSize;

    let bestHCLKRDIV = 1;
    let bestCLKRDIV = 1;
    let closestACLKR = AUXCLK;
    let minDiff = Math.abs(AUXCLK - targetACLKR);

    /* The theoretical total division needed */
    const theoreticalDivider = AUXCLK / targetACLKR;

    /* For each possible HCLKRDIV value (2-4096) */
    /* Iteration start from 2 for legacy reason */
    for (let hclkrdiv = 2; hclkrdiv <= 4096; hclkrdiv++) {
        /* Calculate the ideal HCLKRDIV value for this CLKRDIV */
        const idealCLKRDIV = theoreticalDivider / hclkrdiv;

        /* Check the two closest integer values for HCLKRDIV */
        const candidates = [
            Math.floor(idealCLKRDIV),
            Math.ceil(idealCLKRDIV)
        ];

        for (const clkrdiv of candidates) {
            /* Ensure CLKRDIV is within valid range */
            if (clkrdiv < 1 || clkrdiv > 32) continue;

            /* Calculate the resulting frequency */
            const resultFreq = AUXCLK / (clkrdiv * hclkrdiv);
            const diff = Math.abs(resultFreq - targetACLKR);

            /* If this combination gives a closer frequency, update our best values */
            if (diff < minDiff) {
                minDiff = diff;
                bestHCLKRDIV = hclkrdiv;
                bestCLKRDIV = clkrdiv;
                closestACLKR = resultFreq;
            }
        }
    }

    /* Check if HCLKRDIV = 1 is the best */
    const resultFreq = AUXCLK / (1*1);
    const diff = Math.abs(resultFreq - targetACLKR);
    if(diff < minDiff) {
        minDiff = diff;
        bestHCLKRDIV = 1;
        bestCLKRDIV = 1;
        closestACLKR = resultFreq;
    }

    /* Above calculated dividers will be applicable if HCLK, BCLK, FSYNC is internal */
    if((inst.rxHclkSource == INTERNAL_CLOCK) &&
       (inst.rxAclkSource == INTERNAL_CLOCK))
    {
        inst.rxHclkDiv = bestHCLKRDIV;
        inst.rxClkDiv = bestCLKRDIV;
        return {
            HCLKRDIV: bestHCLKRDIV,
            CLKRDIV: bestCLKRDIV,
            calculatedACLKR: closestACLKR,
            error: minDiff,
            errorPercentage: (minDiff / targetACLKR) * 100
        };
    }

    /* (External HCLK) & (FSYNC, BCLK internal) */
    if((inst.rxHclkSource == EXTERNAL_CLOCK) &&
       (inst.rxAclkSource == INTERNAL_CLOCK))
    {
        inst.rxHclkExpected = targetACLKR*bestCLKRDIV;
        inst.rxHclkDiv = 1;
        inst.rxClkDiv = bestCLKRDIV;
        return {
            HCLKRDIV: 1,
            CLKRDIV: bestCLKRDIV,
            calculatedACLKR: targetACLKR,
            error: 0,
            errorPercentage: 0
        };
    }

    /* External BCLK */
    if(inst.rxAclkSource == EXTERNAL_CLOCK)
    {
        inst.rxHclkDiv = bestHCLKRDIV;
        inst.rxClkDiv = 1;
        return {
            HCLKRDIV: bestHCLKRDIV,
            CLKRDIV: 1,
            calculatedACLKR: targetACLKR,
            error: 0,
            errorPercentage: 0
        };
    }
    else
    {
        inst.rxHclkDiv = bestHCLKRDIV;
        inst.rxClkDiv = bestCLKRDIV;
        let hclkFreq = 0;
        let bclkFreq = 0;

        let error = 0;

        if(inst.rxHclkSource == INTERNAL_CLOCK)
        {
            hclkFreq = clocking.getMcaspAuxClkFreq(inst)/bestHCLKRDIV;
            bclkFreq = hclkFreq/bestCLKRDIV;
            error = Math.abs(bclkFreq - targetACLKR);
            errorPercentage = (error / targetACLKR) * 100;
        }
        else
        {
            bestHCLKRDIV = 1;
            inst.rxHclkDiv = bestHCLKRDIV;
            bclkFreq = targetACLKR;
        }
        return {
            HCLKRDIV: bestHCLKRDIV,
            CLKRDIV: bestCLKRDIV,
            calculatedACLKR: bclkFreq,
            error: error,
            errorPercentage: errorPercentage
        };
    }
}

function applyTxClk(inst, ui)
{
    let targetFs = inst.fsx*1000;
    let targetBclk = targetFs*inst.NumTxSlots*inst.TxSlotSize;
    let auxClkFreq = clocking.getMcaspAuxClkFreq(inst);

    /* If internal HCLK */
    if(inst.txHclkSource == INTERNAL_CLOCK)
    {
        /* Calculate HCLK value from AUXCLK */
        inst.txHclkCalculated = auxClkFreq/inst.txHclkDiv;

        /* If BLCK is external */
        if(inst.txAclkSource == EXTERNAL_CLOCK)
        {
            inst.txBclkExpected = targetBclk;
        }
        else
        {
            /* Internal BCLK */
            inst.txBclkCalculated = inst.txHclkCalculated/inst.txClkDiv;
        }

        /* If FSYNC is external */
        if(inst.txFsSource == EXTERNAL_CLOCK)
        {
            inst.txFsyncExpected = targetFs;
        }
        else
        {
            /* Internal FSYNC */
            inst.txFsyncCalculated = inst.txHclkCalculated/(inst.txClkDiv*inst.NumTxSlots*inst.TxSlotSize);
        }
    }
    else
    {
        /* If external HCLK */
        inst.txHclkExpected = targetBclk*inst.txClkDiv;

        /* If BLCK is external */
        if(inst.txAclkSource == EXTERNAL_CLOCK)
        {
            inst.txBclkExpected = inst.fsx*1000*inst.NumTxSlots*inst.TxSlotSize;
        }
        else
        {
            /* Internal BCLK */
            inst.txBclkCalculated = inst.txHclkExpected/inst.txClkDiv;
        }

        /* If FSYNC is external */
        if(inst.txFsSource == EXTERNAL_CLOCK)
        {
            inst.txFsyncExpected = targetFs;
        }
        else
        {
            /* Internal FSYNC */
            inst.txFsyncCalculated = inst.txHclkExpected/(inst.txClkDiv*inst.NumTxSlots*inst.TxSlotSize);
        }
    }

    /* Alert to update Rx Clock if in SYNC mode */
    if(inst.clkSyncMode == "SYNC")
    {
        inst.rxClkApplyAlert = true;
    }
}

function applyRxClk(inst, ui)
{
    if(inst.clkSyncMode == "SYNC")
    {
        applyTxClk(inst, ui);

        /* Internal TX HCLK source */
        if(inst.txHclkSource == INTERNAL_CLOCK)
        {
            inst.rxHclkSource = INTERNAL_CLOCK;
            inst.rxHclkCalculated = inst.txHclkCalculated;
        }
        else
        {
            inst.rxHclkSource = EXTERNAL_CLOCK;
            inst.rxHclkExpected = inst.txHclkExpected;
        }

        /* Internal TX BCLK source */
        if(inst.txAclkSource == INTERNAL_CLOCK)
        {
            inst.rxAclkSource = INTERNAL_CLOCK;
            inst.rxBclkCalculated = inst.txBclkCalculated;
        }
        else
        {
            inst.rxAclkSource = EXTERNAL_CLOCK;
            inst.rxBclkExpected = inst.txBclkExpected;
        }

        /* Internal TX FSYNC source */
        if(inst.txFsSource == INTERNAL_CLOCK)
        {
            inst.rxFsSource = INTERNAL_CLOCK;
            inst.rxFsyncCalculated = inst.txFsyncCalculated;
        }
        else
        {
            inst.rxFsSource = EXTERNAL_CLOCK;
            inst.rxFsyncExpected = inst.txFsyncExpected;
        }

        return;
    }

    let targetFs = inst.fsr*1000;
    let targetBclk = targetFs*inst.NumRxSlots*inst.RxSlotSize;
    let auxClkFreq = clocking.getMcaspAuxClkFreq(inst);

    /* If internal HCLK */
    if(inst.rxHclkSource == INTERNAL_CLOCK)
    {
        /* Calculate HCLK value from AUXCLK */
        inst.rxHclkCalculated = auxClkFreq/inst.rxHclkDiv;

        /* If BLCK is external */
        if(inst.rxAclkSource == EXTERNAL_CLOCK)
        {
            inst.rxBclkExpected = targetBclk;
        }
        else
        {
            /* Internal BCLK */
            inst.rxBclkCalculated = inst.rxHclkCalculated/inst.rxClkDiv;
        }

        /* If FSYNC is external */
        if(inst.rxFsSource == EXTERNAL_CLOCK)
        {
            inst.rxFsyncExpected = targetFs;
        }
        else
        {
            /* Internal FSYNC */
            inst.rxFsyncCalculated = inst.rxHclkCalculated/(inst.rxClkDiv*inst.NumRxSlots*inst.RxSlotSize);
        }
    }
    else
    {
        /* If external HCLK */
        inst.rxHclkExpected = targetBclk*inst.rxClkDiv;

        /* If BLCK is external */
        if(inst.rxAclkSource == EXTERNAL_CLOCK)
        {
            inst.rxBclkExpected = inst.fsr*1000*inst.NumRxSlots*inst.RxSlotSize;
        }
        else
        {
            /* Internal BCLK */
            inst.rxBclkCalculated = inst.rxHclkExpected/inst.rxClkDiv;
        }

        /* If FSYNC is external */
        if(inst.rxFsSource == EXTERNAL_CLOCK)
        {
            inst.rxFsyncExpected = targetFs;
        }
        else
        {
            /* Internal FSYNC */
            inst.rxFsyncCalculated = inst.rxHclkExpected/(inst.rxClkDiv*inst.NumRxSlots*inst.RxSlotSize);
        }
    }

}

function recalculateTx(inst, ui) {
    let clkCfg = calculateOptimalDividersTx(inst);
    inst.txHclkDiv = clkCfg.HCLKXDIV;
    inst.txClkDiv = clkCfg.CLKXDIV;
}

function recalculateRx(inst, ui) {

    if(inst.clkSyncMode == "SYNC")
    {
        let txClkCfg = calculateOptimalDividersTx(inst);
        inst.rxHclkDiv = txClkCfg.HCLKXDIV;
        inst.rxClkDiv = txClkCfg.CLKXDIV;

        return;
    }
    let clkCfg = calculateOptimalDividersRx(inst);
    inst.rxHclkDiv = clkCfg.HCLKRDIV;
    inst.rxClkDiv = clkCfg.CLKRDIV;
}

let mcasp_module_name = "/drivers/mcasp/mcasp";
let mcasp_module= {
    displayName: "MCASP",

    templates: {
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: mcasp_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: mcasp_module_name,
        },
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/mcasp/templates/v1/mcasp_config.c.xdt",
            driver_init: "/drivers/mcasp/templates/v1/mcasp_init.c.xdt",
            driver_deinit: "/drivers/mcasp/templates/v1/mcasp_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/mcasp/templates/v1/mcasp.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/mcasp/templates/v1/mcasp_open_close_config.c.xdt",
            driver_close: "/drivers/mcasp/templates/v1/mcasp_close.c.xdt",
            driver_open: "/drivers/mcasp/templates/v1/mcasp_open.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/mcasp/templates/v1/mcasp_open_close.h.xdt",
        },
    },

    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_MCASP",
    config: [
        {
            name: "transferMode",
            displayName: "Mode of Transfer",
            default: "DMA",
            options: [
                { name: "INTERRUPT", displayName: "Interrupt" },
                { name: "DMA", displayName: "DMA" },
            ],
            description: "Mode of transfer as polled/Interrupt CPU or DMA",
            onChange: function (inst, ui) {
                if(inst.transferMode == "DMA")
                {
                    ui.txLoopjobEnable.readOnly = true;
                    ui.rxLoopjobEnable.readOnly = true;
                }
                else
                {
                    ui.txLoopjobEnable.readOnly = false;
                    ui.rxLoopjobEnable.readOnly = false;
                }
            }
        },
        {
            name: "skipDriverOpen",
            displayName: "Skip Driver Open",
            default: false,
            longDescription:
`Skip driver open in ti_drivers_open_close.c.
This can be used when external clocks needs to be configured before MCASP_Open.
Then MCASP_Open can be called from application after clock configurations are done`,
        },
        {
            name: "enableLoopback",
            displayName: "Enable McASP Loopback",
            default: true,
            description: `Enable McASP Loopback`,
            onChange: function (inst, ui) {
                if(inst.enableLoopback == true) {
                    inst.enableMcaspRx = true;
                    ui.enableMcaspRx.readOnly = true;
                    inst.enableMcaspTx = true;
                    ui.enableMcaspTx.readOnly = true;
                    inst.clkSyncMode = "SYNC";
                    ui.clkSyncMode.readOnly = true;
                }
                else {
                    ui.clkSyncMode.readOnly = false;
                    ui.enableMcaspTx.readOnly = false;
                    ui.enableMcaspRx.readOnly = false;
                }
            }
        },
        {
            name: "clkSyncMode",
            displayName: "Clock Synchronization Mode",
            default: "SYNC",
            readOnly: true,
            options: [
                { name: "SYNC", displayName: "Tx and Rx clock in Sync mode" },
                { name: "ASYNC", displayName: "Tx and Rx clocks are separate" },
            ],
        },
        {
            name: "xmtConfig",
            displayName: "MCASP Transmit Configuration",
            collapsed: true,
            config: [
                {
                    name: "enableMcaspTx",
                    displayName: "Enable McASP Transmission",
                    default: true,
                    readOnly: true,
                    description: "Enable McASP Transmission",
                    onChange: function (inst, ui) {
                        if(inst.enableMcaspTx == true) {
                            ui.TxMode.hidden = false;
                            ui.NumTxSlots.hidden = false;
                            ui.txDataDelay.hidden = false;
                            ui.txDataOrder.hidden = false;
                            ui.txPaddingMode.hidden = false;
                            ui.txPaddingBit.hidden = false;
                            ui.txDataRotation.hidden = false;
                            ui.txFsWidth.hidden = false;
                            ui.txFsPolarity.hidden = false;
                            ui.txBitClkPolarity.hidden = false;
                            ui.txBufferFormat.hidden = false;
                            ui.TxSlotSize.hidden = false;
                            ui.txDataMask.hidden = false;
                            ui.txActiveSlotMask.hidden = false;
                            ui.txFsSource.hidden = false;
                            ui.txAclkSource.hidden = false;
                            ui.txHclkSource.hidden = false;
                            ui.afsx.hidden = false;
                            ui.txCallbackFxn.hidden = false;
                            ui.txAfifoEnable.hidden = false;
                            ui.txAfifoNumEvt.hidden = false;
                            ui.txLoopjobEnable.hidden = false;
                            ui.txLoopjobBuf.hidden = false;
                            ui.txLoopjobBufLength.hidden = false;
                        }
                        else {
                            ui.TxMode.hidden = true;
                            ui.NumTxSlots.hidden = true;
                            ui.txDataDelay.hidden = true;
                            ui.txDataOrder.hidden = true;
                            ui.txPaddingMode.hidden = true;
                            ui.txPaddingBit.hidden = true;
                            ui.txDataRotation.hidden =true;
                            ui.txFsWidth.hidden = true;
                            ui.txFsPolarity.hidden = true;
                            ui.txBitClkPolarity.hidden = true;
                            ui.txBufferFormat.hidden =true;
                            ui.TxSlotSize.hidden = true;
                            ui.txDataMask.hidden = true;
                            ui.txActiveSlotMask.hidden = true;
                            ui.txFsSource.hidden = true;
                            ui.txAclkSource.hidden = true;
                            ui.txHclkSource.hidden = true;
                            ui.afsx.hidden = true;
                            ui.txCallbackFxn.hidden = true;
                            ui.txAfifoEnable.hidden = true;
                            ui.txAfifoNumEvt.hidden = true;
                            ui.txLoopjobEnable.hidden = true;
                            ui.txLoopjobBuf.hidden = true;
                            ui.txLoopjobBufLength.hidden = true;
                        }
                    },
                },
                {
                    name: "TxMode",
                    displayName: "Mode of Transmission",
                    default: "I2S",
                    options: [
                        { name: "I2S", displayName: "I2S"},
                        { name: "TDM", displayName: "TDM"},
                    ],
                    description: "Configure Mcasp transmission to either run in I2S or TDM mode",
                    onChange: function (inst, ui) {
                        if(inst.TxMode == "I2S") {
                            inst.NumTxSlots = 2;
                            ui.NumTxSlots.readOnly = true;
                            inst.txDataDelay = 1;
                            ui.txDataDelay.readOnly = true;
                            inst.txDataOrder = 1;
                            ui.txDataOrder.readOnly = true;
                            inst.txPaddingMode = 0;
                            ui.txPaddingMode.readOnly = true;
                            inst.txPaddingBit = 1;
                            ui.txPaddingBit.hidden = true;
                            inst.txDataRotation = 0;
                            ui.txDataRotation.readOnly = true;
                            inst.txFsWidth = 1;
                            ui.txFsWidth.readOnly = true;
                            inst.txFsPolarity = 1;
                            ui.txFsPolarity.readOnly = true;
                            inst.txBitClkPolarity = 1;
                            ui.txBitClkPolarity.readOnly = true;
                        }
                        else {
                            ui.NumTxSlots.readOnly = false;
                            ui.txDataDelay.readOnly = false;
                            ui.txDataOrder.readOnly = false;
                            ui.txPaddingMode.readOnly = false;
                            ui.txDataRotation.readOnly = false;
                            ui.txFsWidth.readOnly = false;
                            ui.txFsPolarity.readOnly = false;
                            ui.txBitClkPolarity.readOnly = false;
                        }
                    },
                },
                {
                    name: "NumTxSlots",
                    displayName: "Transmit Slot Count",
                    default: 2,
                    readOnly: true,
                    displayFormat: "dec",
                    description: "Configure number of slots in TDM mode",
                    onChange: function (inst, ui) {
                        inst.txClkApplyAlert = true;
                    }
                },
                {
                    name: "txDataDelay",
                    displayName: "Transmit Frame Sync Bit Delay",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "0-bit delay between FS and Data"},
                        { name: 1, displayName: "1-bit delay between FS and Data"},
                        { name: 2, displayName: "2-bit delay between FS and Data"},
                    ],
                    description: "Number of bits delay between Frame Sync and Data",
                },
                {
                    name: "txDataOrder",
                    displayName: "Transmit Serial Bitstream Order",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "LSB First"},
                        { name: 1, displayName: "MSB First"},
                    ],
                    description: "Configure McASP to send MSB first or LSB first",
                },
                {
                    name: "txPaddingMode",
                    displayName: "Transmit Slot Extra Bits Padding",
                    default: 0,
                    readOnly: false,
                    options: [
                        { name: 0, displayName: "Pad extra bits with 0"},
                        { name: 1, displayName: "Pad extra bits with 1"},
                        { name: 2, displayName: "Pad extra bits with existing bit"},
                    ],
                    description: "Configure McASP to pad extra bits not belonging to the word defined by Data Bitmask",
                    onChange: function (inst, ui) {
                        if(inst.txPaddingMode == 2) {
                            ui.txPaddingBit.hidden = false;
                        }
                        else {
                            ui.txPaddingBit.hidden = true;
                        }
                    },
                },
                {
                    name: "txPaddingBit",
                    displayName: "Transmit Slot bit to be used for padding",
                    default: 1,
                    hidden: true,
                    displayFormat: "dec",
                    description: "Configure McASP to use the bit position in the slot to be used for padding",
                },
                {
                    name: "txDataRotation",
                    displayName: "Transmit Right-rotation Value",
                    default: 0,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "No rotation"},
                        { name: 1, displayName: "Rotate Right by 4 bits"},
                        { name: 2, displayName: "Rotate Right by 8 bits"},
                        { name: 3, displayName: "Rotate Right by 12 bits"},
                        { name: 4, displayName: "Rotate Right by 16 bits"},
                        { name: 5, displayName: "Rotate Right by 20 bits"},
                        { name: 6, displayName: "Rotate Right by 24 bits"},
                        { name: 7, displayName: "Rotate Right by 28 bits"},
                    ],
                },
                {
                    name: "txFsWidth",
                    displayName: "Transmit Frame Sync Width",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Single Bit"},
                        { name: 1, displayName: "Single Word"},
                    ],
                },
                {
                    name: "txFsPolarity",
                    displayName: "Transmit Frame Sync Polarity",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Rising Edge Indicates Frame Start"},
                        { name: 1, displayName: "Falling Edge Indicates Frame Start"},
                    ],
                    description: "Configure new frame to start form rising edge or falling edge of frame sync signal",
                },
                {
                    name: "txBitClkPolarity",
                    displayName: "Transmit Bit Clock Polarity",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Data shift out in rising edge"},
                        { name: 1, displayName: "Data shift out in falling edge"},
                    ],
                    description: "Configure bit clock to shift out data in rising or falling edge",
                },
                {
                    name: "txBufferFormat",
                    displayName: "Transmit Audio Buffer Format",
                    default: "1SER_MULTISLOT_INTERLEAVED",
                    readOnly: true,
                    options: [
                        { name: "1SER_MULTISLOT_INTERLEAVED", displayName: "1-Serializer Multi-Slot Interleaved" },
                        { name: "1SER_MULTISLOT_NON_INTERLEAVED", displayName: "1-Serializer Multi-Slot NonInterleaved" },
                        { name: "MULTISER_MULTISLOT_SEMI_INTERLEAVED_1", displayName: "Multi-Serializer Multi-Slot Interleaved Type1" },
                        { name: "MULTISER_MULTISLOT_SEMI_INTERLEAVED_2", displayName: "Multi-Serializer Multi-Slot Interleaved Type2" },
                    ],
                    description: "Audio buffer format used by the application transmit buffer",
                },
                {
                    name: "txAfifoEnable",
                    displayName: "Transmit Audio FIFO Enable",
                    default: true,
                    description: "Transmit AFIFO Enable",
                    onChange: function (inst, ui) {
                        if(inst.txAfifoEnable == 1) {
                            ui.txAfifoNumEvt.hidden = false;
                        }
                        else {
                            ui.txAfifoNumEvt.hidden = true;
                        }
                    },
                },
                {
                    name: "txAfifoNumEvt",
                    displayName: "Transmit Audio FIFO Event Word Count",
                    default: 32,
                    displayFormat: "dec",
                    description: "Word count to generate TX even to host",
                },
                {
                    name: "TxSlotSize",
                    displayName: "Transmit Slot Size In Bits",
                    default: 32,
                    displayFormat: "dec",
                    options: [
                        { name: 8, displayName: "8"},
                        { name: 12, displayName: "12"},
                        { name: 16, displayName: "16"},
                        { name: 20, displayName: "20"},
                        { name: 24, displayName: "24"},
                        { name: 28, displayName: "28"},
                        { name: 32, displayName: "32"},
                    ],
                    description: "Number of bits in a slot",
                    onChange: function (inst, ui) {
                        inst.txClkApplyAlert = true;
                    }
                },
                {
                    name: "txDataMask",
                    displayName: "Transmit Data Bitmask",
                    default: 0,
                    displayFormat: "hex",
                    description: "Configure on which bits of the slot to send out data",
                },
                {
                    name: "txActiveSlotMask",
                    displayName: "Transmit Active Slot Bitmask",
                    default: 0,
                    displayFormat: "hex",
                    description: "Configure which slots of the frame are active (contains audio data)",
                },
                {
                    name: "txCallbackFxn",
                    displayName: "Transmit Callback Function",
                    default: "NULL",
                    description: "Transmit Callback Function",
                },
                {
                    name: "txLoopjobEnable",
                    displayName: "Transmit Loopjob Enable",
                    default: true,
                    readOnly: true,
                    description: "Transmit Loopjob Enable",
                },
                {
                    name: "externTxLoopjob",
                    displayName: "Extern Transmit Loopjob",
                    default: false,
                    description: "Extern Transmit Loopjob",
                    longDescription:
`Provide address to an external transmit loopjob defined elsewhere in the application.
This address will be typecasted to an unsigned char pointer.
The transaction buffer can itself be provided as an external loopjob.
Note: This buffer will be declared as extern "Extern Transmit Loopjob";`,
                    onChange: function (inst, ui) {
                        ui.txLoopjobBufExtern.hidden = !inst.externTxLoopjob;
                    },
                },
                {
                    name: "txLoopjobBufExtern",
                    displayName: "Transmit Loopjob Buffer Definition",
                    default: "NULL",
                    description: "Transmit loopjob buffer definition",
                    hidden: true,
                    longDescription:
`Provide the extern definition for the transmit loopjob buffer.`,
                },
                {
                    name: "txLoopjobBuf",
                    displayName: "Transmit Loopjob Buffer",
                    default: "gTxLoopjobBuf0",
                    description: "Transmit Loopjob Buffer",
                },
                {
                    name: "txLoopjobBufLength",
                    displayName: "Transmit Loopjob Buffer Length",
                    default: 256,
                    displayFormat: "dec",
                    description: "Transmit Loopjob Buffer Length in Bytes",
                    longDescription:
`Note: Loopjob length must be same as the transactions submitted by the application.`,
                },
                {
                    name: "xmtClockConfig",
                    displayName: "MCASP Transmit Clock Configuration",
                    collapsed: true,
                    config: [
                        {
                            name: "afsx",
                            displayName: "Transmit Frame Sync Rate",
                            default: 48,
                            displayFormat: "dec",
                            options: [
                                { name: 48, displayName: "48 KHz"},
                                { name: 96, displayName: "96 KHz"},
                                { name: 0,  displayName: "Custom"},
                            ],
                            description: "McASP Transmit Frame Sync frequency",
                            onChange: function (inst, ui) {
                                if(inst.afsx == 0) {
                                    ui.fsx.hidden = false;
                                }
                                else {
                                    ui.fsx.hidden = true;
                                    inst.fsx = inst.afsx;
                                }
                            },
                        },
                        {
                            name: "fsx",
                            displayName: "Custom Frame Sync Rate (KHz)",
                            default: 48,
                            hidden: true,
                            displayFormat: "dec",
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txFsSource",
                            displayName: "Transmit Frame Sync Source",
                            default: INTERNAL_CLOCK,
                            options: [
                                { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                            ],
                            description: "Transmit Frame Sync Source",
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txAclkSource",
                            displayName: "Transmit Bit Clock Source",
                            default: INTERNAL_CLOCK,
                            options: [
                                { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                            ],
                            description: "Transmit Bit Clock Source",
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "masterClkx",
                            displayName: "Transmit Master Clock Rate | Deprecated configurable",
                            default: 512,
                            displayFormat: "dec",
                            options: [
                                { name: 128,  displayName: "128 times Fs"},
                                { name: 256,  displayName: "256 times Fs"},
                                { name: 512,  displayName: "512 times Fs"},
                                { name: 1024, displayName: "1024 times Fs"},
                                { name: 0   , displayName: "Any"},
                            ],
                            description: "Transmit Master Clock Rate | Deprecated configurable",
                            longDescription: "This configurable is deprecated in the current version,\
                                            but maintained as a hiiden configurable for leagacy reason.",
                            hidden: true,
                        },
                        {
                            name: "txHclkSource",
                            displayName: "Transmit High Clock Source",
                            default: INTERNAL_CLOCK,
                            options: [
                                { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                            ],
                            description: "Transmit High Clock Source",
                            onChange: function (inst, ui) {
                                if(inst.txHclkSource == EXTERNAL_CLOCK) {
                                    ui.txHclkSourceMux.hidden = false;
                                    inst.txHclkSourceMux = 16;
                                }
                                else {
                                    ui.txHclkSourceMux.hidden = true;
                                }
                                inst.txClkApplyAlert = true;
                            },
                        },
                        {
                            name: "txHclkSourceMux",
                            displayName: "Trasmit High Clock Parent",
                            default: 16,
                            hidden: true,
                            options: soc.getExtTxHclkSrc(),
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txCalcOptimalDiv",
                            displayName: "Calculate Optimal Dividers",
                            buttonText: "Re-Calculate",
                            hidden: false,
                            longDescription: "Pressing this button would help in recalculating the optimal dividers for TX clocks \
                            to achieve the closest achievable frequency to the expected. Press the `Apply Tx Clock Changes` \
                            to viewing the frequencies Calculated/Expected.",
                            onComplete: (inst, _ui, result) => {
                                recalculateTx(inst, _ui);
                                return;
                            },
                        },
                        {
                            name: "txHclkDiv",
                            displayName: "TX HCLK Divider",
                            longDescription: `![](../source/drivers/.meta/mcasp/v1/mcasp_hclkdiv.png)`,
                            default: 2,
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txClkDiv",
                            displayName: "TX CLK Divider",
                            longDescription: `![](../source/drivers/.meta/mcasp/v1/mcasp_aclkdiv.png)`,
                            default: 8,
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txHclkExpected",
                            displayName: "TX HCLK Expected",
                            default: 0,
                            hidden: true,
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txHclkCalculated",
                            displayName: "TX HCLK Calculated",
                            default: soc.mcasp_input_clk_freq/(2),
                            hidden: true,
                        },

                        {
                            name: "txBclkExpected",
                            displayName: "TX BCLK Expected",
                            default: 0,
                            hidden: true,
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txBclkCalculated",
                            displayName: "TX BCLK Calculated",
                            default: soc.mcasp_input_clk_freq/(2*8),
                            hidden: true,
                        },

                        {
                            name: "txFsyncExpected",
                            displayName: "TX Fsync Expected",
                            default: 0,
                            hidden: true,
                            onChange: function (inst, ui) {
                                inst.txClkApplyAlert = true;
                            }
                        },
                        {
                            name: "txFsyncCalculated",
                            displayName: "TX Fsync Calculated",
                            default: soc.mcasp_input_clk_freq/(2*8*32*2),
                            hidden: true,
                        },
                        {
                            name: "txApplyChanges",
                            displayName: "Apply Tx Clock Changes",
                            buttonText: "Apply",
                            hidden: false,
                            longDescription: "Pressing this button would recalculate the TX Frame Sync, Bit Clock, High Clock Freq \
                                                  based on the configrations selected.",

                            onComplete: (inst, _ui, result) => {
                                applyTxClk(inst, _ui);
                                inst.txClkApplyAlert = false;
                                return;
                            },
                        },
                        {
                            name: "txClkApplyAlert",
                            displayName: "Tx Clock Apply Alert",
                            default: true,
                            hidden: true,
                        },

                    ]
                },
            ],
        },
        {
            name: "rcvConfig",
            displayName: "MCASP Receive Configuration",
            collapsed: true,
            config: [
                {
                    name: "enableMcaspRx",
                    displayName: "Enable McASP Reception",
                    default: true,
                    readOnly: true,
                    description: `Enable McASP Reception`,
                    onChange: function (inst, ui) {
                        if(inst.enableMcaspRx == true){
                            ui.RxMode.hidden = false;
                            ui.NumRxSlots.hidden = false;
                            ui.rxDataDelay.hidden = false;
                            ui.rxDataOrder.hidden = false;
                            ui.rxPaddingMode.hidden = false;
                            ui.rxPaddingBit.hidden = false;
                            ui.rxDataRotation.hidden = false;
                            ui.rxFsWidth.hidden = false;
                            ui.rxFsPolarity.hidden = false;
                            ui.rxBitClkPolarity.hidden = false;
                            ui.rxBufferFormat.hidden = false;
                            ui.RxSlotSize.hidden = false;
                            ui.rxDataMask.hidden = false;
                            ui.rxActiveSlotMask.hidden = false;
                            ui.rxFsSource.hidden = false;
                            ui.rxAclkSource.hidden = false;
                            ui.rxHclkSource.hidden = false;
                            ui.afsr.hidden = false;
                            ui.rxCallbackFxn.hidden = false;
                            ui.rxAfifoEnable.hidden = false;
                            ui.rxAfifoNumEvt.hidden = false;
                            ui.rxLoopjobEnable.hidden = false;
                            ui.rxLoopjobBuf.hidden = false;
                            ui.rxLoopjobBufLength.hidden = false;
                        }
                        else {
                            ui.RxMode.hidden = true;
                            ui.NumRxSlots.hidden = true;
                            ui.rxDataDelay.hidden = true;
                            ui.rxDataOrder.hidden = true;
                            ui.rxPaddingMode.hidden = true;
                            ui.rxPaddingBit.hidden = true;
                            ui.rxDataRotation.hidden = true;
                            ui.rxFsWidth.hidden = true;
                            ui.rxFsPolarity.hidden = true;
                            ui.rxBitClkPolarity.hidden = true;
                            ui.rxBufferFormat.hidden = true;
                            ui.RxSlotSize.hidden = true;
                            ui.rxDataMask.hidden = true;
                            ui.rxActiveSlotMask.hidden = true;
                            ui.rxFsSource.hidden = true;
                            ui.rxAclkSource.hidden = true;
                            ui.rxHclkSource.hidden = true;
                            ui.afsr.hidden = true;
                            ui.rxCallbackFxn.hidden = true;
                            ui.rxAfifoEnable.hidden = true;
                            ui.rxAfifoNumEvt.hidden = true;
                            ui.rxLoopjobEnable.hidden = true;
                            ui.rxLoopjobBuf.hidden = true;
                            ui.rxLoopjobBufLength.hidden = true;
                        }
                    },
                },
                {
                    name: "RxMode",
                    displayName: "Mode of Reception",
                    default: "I2S",
                    options: [
                        { name: "I2S", displayName: "I2S"},
                        { name: "TDM", displayName: "TDM"},
                    ],
                    description: "Configure Mcasp reception to either run in I2S or TDM mode",
                    onChange: function (inst, ui) {
                        if(inst.RxMode == "I2S") {
                            inst.NumRxSlots = 2;
                            ui.NumRxSlots.readOnly = true;
                            inst.rxDataDelay = 1;
                            ui.rxDataDelay.readOnly = true;
                            inst.rxDataOrder = 1;
                            ui.rxDataOrder.readOnly = true;
                            inst.rxPaddingMode = 0;
                            ui.rxPaddingMode.readOnly = true;
                            inst.rxPaddingBit = 1;
                            ui.rxPaddingBit.hidden = true;
                            inst.rxDataRotation = 0;
                            ui.rxDataRotation.readOnly = true;
                            inst.rxFsWidth = 1;
                            ui.rxFsWidth.readOnly = true;
                            inst.rxFsPolarity = 1;
                            ui.rxFsPolarity.readOnly = true;
                            inst.rxBitClkPolarity = 1;
                            ui.rxBitClkPolarity.readOnly = true;
                        }
                        else {
                            ui.NumRxSlots.readOnly = false;
                            ui.rxDataDelay.readOnly = false;
                            ui.rxDataOrder.readOnly = false;
                            ui.rxPaddingMode.readOnly = false;
                            ui.rxDataRotation.readOnly = false;
                            ui.rxFsWidth.readOnly = false;
                            ui.rxFsPolarity.readOnly = false;
                            ui.rxBitClkPolarity.readOnly = false;
                        }
                    },
                },
                {
                    name: "NumRxSlots",
                    displayName: "Receive Slot Count",
                    default: 2,
                    readOnly: true,
                    displayFormat: "dec",
                    description: "Configure number of slots in TDM mode",
                    onChange: function (inst, ui) {
                        inst.rxClkApplyAlert = true;
                    }
                },
                {
                    name: "rxDataDelay",
                    displayName: "Receive Frame Sync Bit Delay",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "0-bit delay between FS and Data"},
                        { name: 1, displayName: "1-bit delay between FS and Data"},
                        { name: 2, displayName: "2-bit delay between FS and Data"},
                    ],
                    description: "Number of bits delay between Frame Sync and Data",
                },
                {
                    name: "rxDataOrder",
                    displayName: "Receive Serial Bitstream Order",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "LSB First"},
                        { name: 1, displayName: "MSB First"},
                    ],
                    description: "Configure McASP to send MSB first or LSB first",
                },
                {
                    name: "rxPaddingMode",
                    displayName: "Receive Slot Extra Bits Padding",
                    default: 0,
                    readOnly: false,
                    options: [
                        { name: 0, displayName: "Pad extra bits with 0"},
                        { name: 1, displayName: "Pad extra bits with 1"},
                        { name: 2, displayName: "Pad extra bits with existing bit"},
                    ],
                    description: "Configure McASP to pad extra bits not belonging to the word defined by Data Bitmask",
                    onChange: function (inst, ui) {
                        if(inst.rxPaddingMode == 2) {
                            ui.rxPaddingBit.hidden = false;
                        }
                        else {
                            ui.rxPaddingBit.hidden = true;
                        }
                    },
                },
                {
                    name: "rxPaddingBit",
                    displayName: "Receive Slot bit to be used for padding",
                    default: 1,
                    hidden: true,
                    displayFormat: "dec",
                    description: "Configure McASP to use the bit position in the slot to be used for padding",
                },
                {
                    name: "rxDataRotation",
                    displayName: "Receive Right-rotation Value",
                    default: 0,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "No rotation"},
                        { name: 1, displayName: "Rotate Right by 4 bits"},
                        { name: 2, displayName: "Rotate Right by 8 bits"},
                        { name: 3, displayName: "Rotate Right by 12 bits"},
                        { name: 4, displayName: "Rotate Right by 16 bits"},
                        { name: 5, displayName: "Rotate Right by 20 bits"},
                        { name: 6, displayName: "Rotate Right by 24 bits"},
                        { name: 7, displayName: "Rotate Right by 28 bits"},
                    ],
                },
                {
                    name: "rxFsWidth",
                    displayName: "Receive Frame Sync Width",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Single Bit"},
                        { name: 1, displayName: "Single Word"},
                    ],
                },
                {
                    name: "rxFsPolarity",
                    displayName: "Receive Frame Sync Polarity",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Rising Edge Indicates Frame Start"},
                        { name: 1, displayName: "Falling Edge Indicates Frame Start"},
                    ],
                    description: "Configure new frame to start form rising edge or falling edge of frame sync signal",
                },
                {
                    name: "rxBitClkPolarity",
                    displayName: "Receive Bit Clock Polarity",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Data sampled in falling edge"},
                        { name: 1, displayName: "Data sampled in rising edge"},
                    ],
                    description: "Configure data to be sampled in rising or falling edge",
                },
                {
                    name: "rxBufferFormat",
                    displayName: "Receive Audio Buffer Format",
                    default: "1SER_MULTISLOT_INTERLEAVED",
                    readOnly: true,
                    options: [
                        { name: "1SER_MULTISLOT_INTERLEAVED", displayName: "1-Serializer Multi-Slot Interleaved" },
                        { name: "1SER_MULTISLOT_NON_INTERLEAVED", displayName: "1-Serializer Multi-Slot NonInterleaved" },
                        { name: "MULTISER_MULTISLOT_SEMI_INTERLEAVED_1", displayName: "Multi-Serializer Multi-Slot Interleaved Type1" },
                        { name: "MULTISER_MULTISLOT_SEMI_INTERLEAVED_2", displayName: "Multi-Serializer Multi-Slot Interleaved Type2" },
                    ],
                    description: "Audio buffer format used by the application receive buffer",
                },
                {
                    name: "rxAfifoEnable",
                    displayName: "Receive Audio FIFO Enable",
                    default: true,
                    description: "Receive AFIFO Enable",
                    onChange: function (inst, ui) {
                        if(inst.rxAfifoEnable == 1) {
                            ui.rxAfifoNumEvt.hidden = false;
                        }
                        else {
                            ui.rxAfifoNumEvt.hidden = true;
                        }
                    },
                },
                {
                    name: "rxAfifoNumEvt",
                    displayName: "Receive Audio FIFO Event Word Count",
                    default: 32,
                    displayFormat: "dec",
                    description: "Word count to generate RX even to host",
                },
                {
                    name: "RxSlotSize",
                    displayName: "Receive Slot Size In Bits",
                    default: 32,
                    displayFormat: "dec",
                    options: [
                        { name: 8, displayName: "8"},
                        { name: 12, displayName: "12"},
                        { name: 16, displayName: "16"},
                        { name: 20, displayName: "20"},
                        { name: 24, displayName: "24"},
                        { name: 28, displayName: "28"},
                        { name: 32, displayName: "32"},
                    ],
                    description: "Number of bits in a slot",
                    onChange: function (inst, ui) {
                        inst.rxClkApplyAlert = true;
                    }
                },
                {
                    name: "rxDataMask",
                    displayName: "Receive Data Bitmask",
                    default: 0,
                    displayFormat: "hex",
                    description: "Configure on which bits of the slot to receive data",
                },
                {
                    name: "rxActiveSlotMask",
                    displayName: "Receive Active Slot Bitmask",
                    default: 0,
                    displayFormat: "hex",
                    description: "Configure which slots of the frame are active (contains audio data)",
                },
                {
                    name: "rxCallbackFxn",
                    displayName: "Receive Callback Function",
                    default: "NULL",
                    description: "Receive Callback Function",
                },
                {
                    name: "rxLoopjobEnable",
                    displayName: "Receive Loopjob Enable",
                    default: true,
                    readOnly: true,
                    description: "Receive Loopjob Enable",

                },
                {
                    name: "externRxLoopjob",
                    displayName: "Extern Receive Loopjob",
                    default: false,
                    description: "Extern Receive Loopjob",
                    longDescription:
`Provide address to an external receive loopjob defined elsewhere in the application.
This address will be typecasted to an unsigned char pointer.
The transaction buffer can itself be provided as an external loopjob.
Note: This buffer will be declared as extern "Extern Transmit Loopjob";`,
                    onChange: function (inst, ui) {
                        ui.rxLoopjobBufExtern.hidden = !inst.externRxLoopjob;
                    }
                },
                {
                    name: "rxLoopjobBufExtern",
                    displayName: "Receive Loopjob Buffer Definition",
                    default: "NULL",
                    description: "Receive loopjob buffer definition",
                    hidden: true,
                    longDescription:
`Provide the extern definition for the receive loopjob buffer.`
                },
                {
                    name: "rxLoopjobBuf",
                    displayName: "Receive Loopjob Buffer",
                    default: "gRxLoopjobBuf0",
                    description: "Receive Loopjob Buffer",
                },
                {
                    name: "rxLoopjobBufLength",
                    displayName: "Receive Loopjob Buffer Length",
                    default: 256,
                    displayFormat: "dec",
                    description: "Receive Loopjob Buffer Length in Bytes",
                    longDescription:
`Note: Loopjob length must be same as the transactions submitted by the application.`,
                },
                {
                    name: "rcvClockConfig",
                        displayName: "MCASP Receive Clock Configuration",
                        collapsed: true,
                        config: [
                            {
                                name: "afsr",
                                displayName: "Receive Frame Sync Rate",
                                default: 48,
                                displayFormat: "dec",
                                options: [
                                    { name: 48, displayName: "48 KHz"},
                                    { name: 96, displayName: "96 KHz"},
                                    { name: 0,  displayName: "Custom"},
                                ],
                                description: "McASP Receive Frame Sync frequency",
                                onChange: function (inst, ui) {
                                    if(inst.afsr == 0) {
                                        ui.fsr.hidden = false;
                                    }
                                    else {
                                        ui.fsr.hidden = true;
                                        inst.fsr = inst.afsr;
                                    }
                                },
                            },
                            {
                                name: "fsr",
                                displayName: "Custom Frame Sync Rate (KHz)",
                                default: 48,
                                hidden: true,
                                displayFormat: "dec",
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxFsSource",
                                displayName: "Receive Frame Sync Source",
                                default: INTERNAL_CLOCK,
                                options: [
                                    { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                    { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                                ],
                                description: "Receive Frame Sync Source",
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxAclkSource",
                                displayName: "Receive Bit Clock Source",
                                default: INTERNAL_CLOCK,
                                options: [
                                    { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                    { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                                ],
                                description: "Receive Bit Clock Source",
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "masterClkr",
                                displayName: "Receive Master Clock Rate | Deprecated configurable",
                                default: 512,
                                displayFormat: "dec",
                                options: [
                                    { name: 128, displayName: "128 times Fs"},
                                    { name: 256, displayName: "256 times Fs"},
                                    { name: 512, displayName: "512 times Fs"},
                                    { name: 1024, displayName: "1024 times Fs"},
                                    { name: 0   , displayName: "Any"},
                                ],
                                description: "Receive Master Clock Rate | Deprecated configurable",
                                longDescription: "This configurable is deprecated in the current version,\
                                            but maintained as a hiiden configurable for leagacy reason.",
                                hidden: true,
                            },
                            {
                                name: "rxHclkSource",
                                displayName: "Receive High Clock Source",
                                default: INTERNAL_CLOCK,
                                options: [
                                    { name: EXTERNAL_CLOCK, displayName: "Externally Generated"},
                                    { name: INTERNAL_CLOCK, displayName: "Internally Generated"},
                                ],
                                description: "Receive High Clock Source",
                                onChange: function (inst, ui) {
                                    if(inst.rxHclkSource == EXTERNAL_CLOCK) {
                                        ui.rxHclkSourceMux.hidden = false;
                                        inst.rxHclkSourceMux = 16;
                                    }
                                    else {
                                        ui.rxHclkSourceMux.hidden = true;
                                    }
                                    inst.rxClkApplyAlert = true;
                                },
                            },
                            {
                                name: "rxHclkSourceMux",
                                displayName: "Receive High Clock Parent",
                                default: 16,
                                hidden: true,
                                options: soc.getExtRxHclkSrc(),
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxCalcOptimalDiv",
                                displayName: "Calculate Optimal Dividers",
                                buttonText: "Re-Calculate",
                                longDescription: "Pressing this button would help in recalculating the optimal dividers for RX clocks \
                                                  to achieve the closest achievable frequency to the expected. Press the `Apply Rx Clock Changes` \
                                                  to viewing the frequencies Calculated/Expected.",
                                hidden: false,

                                onComplete: (inst, _ui, result) => {
                                    recalculateRx(inst, _ui);
                                    return;
                                },
                            },
                            {
                                name: "rxHclkDiv",
                                displayName: "RX HCLK Divider",
                                longDescription: `![](../source/drivers/.meta/mcasp/v1/mcasp_hclkdiv.png)`,
                                default: 2,
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxClkDiv",
                                displayName: "RX CLK Divider",
                                longDescription: `![](../source/drivers/.meta/mcasp/v1/mcasp_aclkdiv.png)`,
                                default: 8,
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxHclkExpected",
                                displayName: "RX HCLK Expected",
                                default: 0,
                                hidden: true,
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxHclkCalculated",
                                displayName: "RX HCLK Calculated",
                                default: soc.mcasp_input_clk_freq/(2),
                                hidden: true,
                            },
                            {
                                name: "rxBclkExpected",
                                displayName: "RX BCLK Expected",
                                default: 0,
                                hidden: true,
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxBclkCalculated",
                                displayName: "RX BCLK Calculated",
                                default: soc.mcasp_input_clk_freq/(2*8),
                                hidden: true,
                            },
                            {
                                name: "rxFsyncExpected",
                                displayName: "RX Fsync Expected",
                                default: 0,
                                hidden: true,
                                onChange: function (inst, ui) {
                                    inst.rxClkApplyAlert = true;
                                }
                            },
                            {
                                name: "rxFsyncCalculated",
                                displayName: "RX Fsync Calculated",
                                default: soc.mcasp_input_clk_freq/(2*8*32*2),
                                hidden: true,
                            },
                            {
                                name: "rxApplyChanges",
                                displayName: "Apply Rx Clock Changes",
                                buttonText: "Apply",
                                hidden: false,
                                longDescription: "Pressing this button would recalculate the RX Frame Sync, Bit Clock, High Clock Freq \
                                                  based on the configrations selected.",

                                onComplete: (inst, _ui, result) => {
                                    applyRxClk(inst, _ui);
                                    inst.rxClkApplyAlert = false;
                                    return;
                                },
                            },
                            {
                                name: "rxClkApplyAlert",
                                displayName: "Rx Clock Apply Alert",
                                default: true,
                                hidden: true,
                            },
                        ]
                },
            ],
        },
    ],
    moduleStatic: {
        name: "mcaspGlobalClk",
        displayName: "MCASP Global Clocking",
        hidden: true,
        config: clocking.getStaticClockSources()
    },

    validate: validate,
    validatePinmux: validatePinmux,
    moduleInstances: moduleInstances,
    sharedModuleInstances: addModuleInstances,
    pinmuxRequirements,
    getPeripheralPinNames,
    getInterfaceName,
    getInstanceConfig,
    getClockEnableIds,
    getClockFrequencies,
}

function addModuleInstances(instance) {
    let modInstances = new Array();

    if(instance.transferMode == "DMA") {
        modInstances.push({
            name: "bcDmaDriver",
            displayName: "UDMA Configuration",
            moduleName: "/drivers/udma/udma",
            requiredArgs: {
                parentName: "MCASP",
                instance: "BCDMA_0",
            }
        });
    }

    return modInstances;
}

/*
 *  ======== validate ========
 */
function validate(inst, report) {
    if(inst.clkSyncMode == "SYNC") {
        if ((inst.NumTxSlots * inst.TxSlotSize) != (inst.NumRxSlots * inst.RxSlotSize)) {
            report.logError(`The total number of bits per frame must be the same in SYNC mode (XSSZ*XMOD = RSSZ*RMOD)`, inst,  "clkSyncMode");
        }
        if (inst.rxFsSource != inst.txFsSource) {
            report.logError(` TX and RX Frame Sync Source must match in SYNC mode`, inst,  "rxFsSource");
        }
        if (inst.rxFsWidth != inst.txFsWidth) {
            report.logError(` TX and RX Frame Sync width must match in SYNC mode`, inst,  "rxFsWidth");
        }
    }

    if (inst.txHclkSource == EXTERNAL_CLOCK && inst.txHclkSourceMux == 16)
    {
        report.logError(`Choose a valid external clock source`, inst, "txHclkSourceMux")
    }

    if (inst.rxHclkSource == EXTERNAL_CLOCK && inst.rxHclkSourceMux == 16)
    {
        report.logError(`Choose a valid external clock source`, inst, "rxHclkSourceMux")
    }

    common.validate.checkNumberRange(inst, report, "NumTxSlots", 2, 32, "dec");
    common.validate.checkNumberRange(inst, report, "NumRxSlots", 2, 32, "dec");
    common.validate.checkNumberRange(inst, report, "txPaddingBit", 0, 31, "dec");
    common.validate.checkNumberRange(inst, report, "rxPaddingBit", 0, 31, "dec");
    common.validate.checkNumberRange(inst, report, "txActiveSlotMask", 0, (1 << inst.NumTxSlots)-1, "dec");
    common.validate.checkNumberRange(inst, report, "rxActiveSlotMask", 0, (1 << inst.NumRxSlots)-1, "dec");
    common.validate.checkNumberRange(inst, report, "txAfifoNumEvt", 0, 64, "dec");
    common.validate.checkNumberRange(inst, report, "rxAfifoNumEvt", 0, 64, "dec");

    common.validate.checkValidCName(inst, report, "txCallbackFxn");
    common.validate.checkValidCName(inst, report, "rxCallbackFxn");

    if((inst.enableMcaspTx == true) &&
        ((inst.txCallbackFxn == "NULL") ||
            (inst.txCallbackFxn == ""))) {
        report.logError("Callback function MUST be provided", inst, "txCallbackFxn");
    }

    if((inst.enableMcaspRx == true) &&
        ((inst.rxCallbackFxn == "NULL") ||
            (inst.rxCallbackFxn == ""))) {
        report.logError("Callback function MUST be provided", inst, "rxCallbackFxn");
    }

    if((inst.enableMcaspTx == true) && (inst.txLoopjobEnable == true)) {
        common.validate.checkValidCName(inst, report, "txLoopjobBuf");
        if (inst.txLoopjobBuf == "NULL") {
            report.logError("tx loopjob buffer must be provided", inst, "txLoopjobBuf");
        }
    }

    if((inst.enableMcaspRx == true) && (inst.rxLoopjobEnable == true)) {
        common.validate.checkValidCName(inst, report, "rxLoopjobBuf");
        if (inst.rxLoopjobBuf == "NULL") {
            report.logError("rx loopjob buffer must be provided", inst, "rxLoopjobBuf");
        }
    }

    let resArray = [];
    let numSer = 16;
    for (let index = 0; index <= numSer; index++) {
        resArray[index] = false;
    }

    let serInstances = inst["mcaspSer"];

    for (let index = 0; index <= serInstances.length; index++) {
        let serInst = serInstances[index];
        if (serInst != null) {
            if (resArray[serInst.serNum] == false) {
                resArray[index] = true;
            } else {
                report.logError(`serializer number overlaps`, inst, "mcaspSer");
            }
        }
    }

    /* Alert to press Tx Freq apply Button */
    if(inst.txClkApplyAlert == true)
    {
        report.logWarning(`Please press Tx Freq Apply Button`, inst, "txApplyChanges");
    }

    /* Alert to press Rx Freq apply Button */
    if(inst.rxClkApplyAlert == true)
    {
        report.logWarning(`Please press Rx Freq Apply Button`, inst, "rxApplyChanges");
    }
}

function validatePinmux(inst, report)
{
    if(inst.txClkApplyAlert == true)
    {
        report.logWarning(`Press "Apply TX Clock changes" button for new Freq`, inst, "txHclkSource");
        report.logWarning(`Press "Apply TX Clock changes" button for new Freq`, inst, "txAclkSource");
        report.logWarning(`Press "Apply TX Clock changes" button for new Freq`, inst, "afsx");
    }
    else
    {
        if(inst.txHclkSource == EXTERNAL_CLOCK)
        {
            /* External HCLK */
            report.logInfo(`Expected AHCLK: ${Math.round(inst.txHclkExpected*1000)/1000} Hz`, inst, "txHclkSource");
        }
        else
        {
            /* Internal HCLK */
            report.logInfo(`Calculated AHCLK: ${Math.round(inst.txHclkCalculated*1000)/1000} Hz`, inst, "txHclkSource");
        }

        if(inst.txAclkSource == EXTERNAL_CLOCK)
        {
            /* External BCLK */
            report.logInfo(`Expected BCLK: ${Math.round(inst.txBclkExpected*1000)/1000} Hz`, inst, "txAclkSource");
        }
        else
        {
            /* Internal BCLK */
            report.logInfo(`Calculated BCLK: ${Math.round(inst.txBclkCalculated*1000)/1000} Hz`, inst, "txAclkSource");
        }

        if(inst.txFsSource == EXTERNAL_CLOCK)
        {
            /* External FSYNC */
            report.logInfo(`Expected FSX: ${inst.afsx} KHz`, inst, "afsx");
        }
        else
        {
            let fsyncKHz = Math.round(inst.txFsyncCalculated*1000)/1000000;
            /* Internal FSYNC */
            report.logInfo(`Calculated FSX: ${fsyncKHz} KHz`, inst, "afsx");
        }
    }

    if(inst.rxClkApplyAlert == true)
    {
        report.logWarning(`Press "Apply RX Clock changes" button for new Freq`, inst, "rxHclkSource");
        report.logWarning(`Press "Apply RX Clock changes" button for new Freq`, inst, "rxAclkSource");
        report.logWarning(`Press "Apply RX Clock changes" button for new Freq`, inst, "afsr");
    }
    else
    {
        if(inst.rxHclkSource == EXTERNAL_CLOCK)
        {
            /* External HCLK */
            report.logInfo(`Expected AHCLK: ${Math.round(inst.rxHclkExpected*1000)/1000} Hz`, inst, "rxHclkSource");
        }
        else
        {
            /* Internal HCLK */
            report.logInfo(`Calculated AHCLK: ${Math.round(inst.rxHclkCalculated*1000)/1000} Hz`, inst, "rxHclkSource");
        }

        if(inst.rxAclkSource == EXTERNAL_CLOCK)
        {
            /* External BCLK */
            report.logInfo(`Expected BCLK: ${Math.round(inst.rxBclkExpected*1000)/1000} Hz`, inst, "rxAclkSource");
        }
        else
        {
            /* Internal BCLK */
            report.logInfo(`Calculated BCLK: ${Math.round(inst.rxBclkCalculated*1000)/1000} Hz`, inst, "rxAclkSource");
        }

        if(inst.txFsSource == EXTERNAL_CLOCK)
        {
            /* External FSYNC */
            report.logInfo(`Expected FSR: ${inst.afsr} KHz`, inst, "afsr");
        }
        else
        {
            let fsyncKHz = Math.round(inst.rxFsyncCalculated*1000)/1000000;
            /* Internal FSYNC */
            report.logInfo(`Calculated FSR : ${fsyncKHz} KHz`, inst, "afsr");
        }
    }

    if(inst.externRxLoopjob == true)
    {
        if(inst.rxLoopjobBufExtern == "NULL")
        {
            report.logError(`Invalid Rx Loopback Buffer`, inst,  "rxLoopjobBufExtern");
        }
    }

    if(inst.externTxLoopjob == true)
    {
        if(inst.txLoopjobBufExtern == "NULL")
        {
            report.logError(`Invalid Tx Loopback Buffer`, inst, "txLoopjobBufExtern");
        }
    }
}

function getInterfaceName(inst) {
    return "MCASP";
}

function moduleInstances(inst) {

    let serInstances = new Array();

    serInstances.push({
        name: "mcaspSer",
        displayName: "MCASP Serializer Configuration",
        moduleName: '/drivers/mcasp/v1/mcasp_v1_ser',
        useArray: true,
        minInstanceCount: 0,
        args: {
            interfaceName: getInterfaceName(inst),
            enableLoopback: inst.enableLoopback,
        },
    });

    return (serInstances);
}

/* Concat AUX Clk source select option */
let clockingConfig = clocking.getConfigArr();

let mcasp_config = mcasp_module.config.concat(clockingConfig);

mcasp_module.config = mcasp_config;

exports = mcasp_module;
