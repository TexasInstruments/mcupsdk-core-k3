let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/mcasp/soc/mcasp_${common.getSocName()}`);

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

    if (inst.txHclkSource == 0 || inst.rxHclkSource  == 0)
    {
        systemResources = soc.getPinmuxReq(inst.txHclkSourceMux, inst.rxHclkSourceMux);
    }

    let mcasp = {
        name: interfaceName,
        displayName: "MCASP Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    let systemPinmux = {
        name: "SYSTEM",
        displayName: "System",
        interfaceName: "SYSTEM",
        resources: systemResources
    };

    return [mcasp, systemPinmux];
}

function getPeripheralPinNames(inst) {

    let pins = [ "AFSR", "ACLKR", "AFSX", "ACLKX"];
    let extPins = soc.getExtClkPins();

    pins = pins.concat(extPins);

    return pins;
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
                            ui.masterClkx.hidden = false;
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
                            ui.masterClkx.hidden = true;
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
                    onChange: function (inst, ui) {
                        if(inst.TxMode == "I2S") {
                            inst.NumTxSlots = 2;
                            ui.NumTxSlots.readOnly = true;
                            inst.txDataDelay = 1;
                            ui.txDataDelay.readOnly = true;
                            inst.txDataOrder = 1;
                            ui.txDataOrder.readOnly = true;
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
                },
                {
                    name: "txDataMask",
                    displayName: "Transmit Data Bitmask",
                    default: 0,
                    displayFormat: "hex",
                },
                {
                    name: "txActiveSlotMask",
                    displayName: "Transmit Active Slot Bitmask",
                    default: 0,
                    displayFormat: "hex",
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
                },
                {
                    name: "xmtClockConfig",
                    displayName: "MCASP Transmit Clock Configuration",
                    collapsed: true,
                    config: [
                        {
                            name: "txAuxClk",
                            displayName: "McASP AUXCLK Rate",
                            default: soc.mcasp_input_clk_freq,
                            readOnly: true,
                            displayFormat: "dec",
                        },
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
                        },
                        {
                            name: "txFsSource",
                            displayName: "Transmit Frame Sync Source",
                            default: 1,
                            options: [
                                { name: 0, displayName: "Externally Generated"},
                                { name: 1, displayName: "Internally Generated"},
                            ],
                        },
                        {
                            name: "txAclkSource",
                            displayName: "Transmit Bit Clock Source",
                            default: 1,
                            options: [
                                { name: 0, displayName: "Externally Generated"},
                                { name: 1, displayName: "Internally Generated"},
                            ],
                        },
                        {
                            name: "masterClkx",
                            displayName: "Transmit Master Clock Rate",
                            default: 512,
                            displayFormat: "dec",
                            options: [
                                { name: 128, displayName: "128 times Fs"},
                                { name: 256, displayName: "256 times Fs"},
                                { name: 512, displayName: "512 times Fs"},
                                { name: 1024, displayName: "1024 times Fs"},
                            ],
                        },
                        {
                            name: "txHclkSource",
                            displayName: "Transmit High Clock Source",
                            default: 1,
                            options: [
                                { name: 0, displayName: "Externally Generated"},
                                { name: 1, displayName: "Internally Generated"},
                            ],
                            onChange: function (inst, ui) {
                                if(inst.txHclkSource == 0) {
                                    ui.txHclkSourceMux.hidden = false;
                                    inst.txHclkSourceMux = 16;
                                }
                                else {
                                    ui.txHclkSourceMux.hidden = true;
                                }
                            },
                        },
                        {
                            name: "txHclkSourceMux",
                            displayName: "Trasmit High Clock Parent",
                            default: 16,
                            hidden: true,
                            options: soc.getExtTxHclkSrc(),
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
                            ui.masterClkr.hidden = false;
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
                            ui.masterClkr.hidden = true;
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
                    onChange: function (inst, ui) {
                        if(inst.RxMode == "I2S") {
                            inst.NumRxSlots = 2;
                            ui.NumRxSlots.readOnly = true;
                            inst.rxDataDelay = 1;
                            ui.rxDataDelay.readOnly = true;
                            inst.rxDataOrder = 1;
                            ui.rxDataOrder.readOnly = true;
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
                },
                {
                    name: "rxBitClkPolarity",
                    displayName: "Receive Bit Clock Polarity",
                    default: 1,
                    readOnly: true,
                    options: [
                        { name: 0, displayName: "Data sampled in falling edge"},
                        { name: 1, displayName: "Data sampled out in rising edge"},
                    ],
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
                },
                {
                    name: "rxDataMask",
                    displayName: "Receive Data Bitmask",
                    default: 0,
                    displayFormat: "hex",
                },
                {
                    name: "rxActiveSlotMask",
                    displayName: "Receive Active Slot Bitmask",
                    default: 0,
                    displayFormat: "hex",
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
                },
                {
                    name: "rcvClockConfig",
                        displayName: "MCASP Receive Clock Configuration",
                        collapsed: true,
                        config: [
                            {
                                name: "rxAuxClk",
                                displayName: "McASP AUXCLK Rate",
                                default: soc.mcasp_input_clk_freq,
                                readOnly: true,
                                displayFormat: "dec",
                            },
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
                            },
                            {
                                name: "rxFsSource",
                                displayName: "Receive Frame Sync Source",
                                default: 1,
                                options: [
                                    { name: 0, displayName: "Externally Generated"},
                                    { name: 1, displayName: "Internally Generated"},
                                ],
                            },
                            {
                                name: "rxAclkSource",
                                displayName: "Receive Bit Clock Source",
                                default: 1,
                                options: [
                                    { name: 0, displayName: "Externally Generated"},
                                    { name: 1, displayName: "Internally Generated"},
                                ],
                            },
                            {
                                name: "masterClkr",
                                displayName: "Receive Master Clock Rate",
                                default: 512,
                                displayFormat: "dec",
                                options: [
                                    { name: 128, displayName: "128 times Fs"},
                                    { name: 256, displayName: "256 times Fs"},
                                    { name: 512, displayName: "512 times Fs"},
                                    { name: 1024, displayName: "1024 times Fs"},
                                ],
                            },
                            {
                                name: "rxHclkSource",
                                displayName: "Receive High Clock Source",
                                default: 1,
                                options: [
                                    { name: 0, displayName: "Externally Generated"},
                                    { name: 1, displayName: "Internally Generated"},
                                ],
                                onChange: function (inst, ui) {
                                    if(inst.rxHclkSource == 0) {
                                        ui.rxHclkSourceMux.hidden = false;
                                        inst.rxHclkSourceMux = 16;
                                    }
                                    else {
                                        ui.rxHclkSourceMux.hidden = true;
                                    }
                                },
                            },
                            {
                                name: "rxHclkSourceMux",
                                displayName: "Receive High Clock Parent",
                                default: 16,
                                hidden: true,
                                options: soc.getExtRxHclkSrc(),
                            },
                        ]
                },
            ],
        },
    ],

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

        modInstances.push({
            name: "pktDmaDriver",
            displayName: "UDMA Configuration",
            moduleName: "/drivers/udma/udma",
            requiredArgs: {
                parentName: "MCASP",
                instance: "PKTDMA_0",
            }
        });
    }

    return modInstances;
}

/*
 *  ======== validate ========
 */
function validate(inst, report) {
    if (inst.NumTxSlots * inst.TxSlotSize > inst.masterClkx) {
        report.logError(`masterClkx not supported. Master Clk Multiplier should greater than Slot width * num slots`, inst,  "masterClkx");
    }
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

    if (inst.txHclkSource == 0 && inst.txHclkSourceMux == 16)
    {
        report.logError(`Choose a valid external clock source`, inst, "txHclkSourceMux")
    }

    if (inst.rxHclkSource == 0 && inst.rxHclkSourceMux == 16)
    {
        report.logError(`Choose a valid external clock source`, inst, "rxHclkSourceMux")
    }

    common.validate.checkNumberRange(inst, report, "NumTxSlots", 2, 32, "dec");
    common.validate.checkNumberRange(inst, report, "NumRxSlots", 2, 32, "dec");
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
}

function validatePinmux(inst, report)
{
    let instConfig = getInstanceConfig(inst);
    let aclkr_ext = inst.NumRxSlots * inst.RxSlotSize * inst.fsr * 1000;
    let ahclkr_ext = inst.masterClkr * inst.fsr * 1000;
    let aclkx_ext = inst.NumTxSlots * inst.TxSlotSize * inst.fsx * 1000;
    let ahclkx_ext = inst.masterClkx * inst.fsx * 1000;
    let ahclkr = 0, ahclkx = 0, aclkr = 0, aclkx = 0;

    if (inst.rxHclkSource == 0)
    {
        ahclkr = ahclkr_ext;
        report.logInfo(`Expected AHCLKR: ${ahclkr} Hz`, inst, "rxHclkSource");
    }
    else
    {
        if ((ahclkr_ext > instConfig.inputClkFreq))
        {
            report.logError(`AHCLKR outside scope`, inst,  "masterClkr");
        }
        else
        {
            ahclkr = instConfig.inputClkFreq / Math.round(instConfig.inputClkFreq / ahclkr_ext);
            report.logInfo(`Calculated AHCLKR: ${ahclkr} Hz`, inst, "rxHclkSource");
        }
    }

    if (inst.rxAclkSource == 0)
    {
        aclkr = aclkr_ext;
        report.logInfo(`Expected ACLKR: ${aclkr} Hz`, inst, "rxAclkSource");
    }
    else
    {
        aclkr = ahclkr / Math.round(ahclkr/(inst.NumRxSlots * inst.RxSlotSize * inst.fsr * 1000));
        report.logInfo(`Calculated ACLKR: ${aclkr} Hz`, inst, "rxAclkSource");
    }

    if ((inst.rxAclkSource == 1) && ((ahclkr % aclkr) != 0))
    {
        report.logError(`AHCLKR is not multiple of ACLKR`, inst,  "masterClkr");
    }

    let afsr_int = aclkr / (inst.NumRxSlots * inst.RxSlotSize * 1000);
    if (inst.rxFsSource == 1)
    {
        report.logInfo(`Calculated FSR: ${afsr_int} KHz`, inst, "afsr");
    }

    if (inst.txHclkSource == 0)
    {
        ahclkx = ahclkx_ext;
        report.logInfo(`Expected AHCLKX: ${ahclkx} Hz`, inst, "txHclkSource");
    }
    else
    {
        if ((ahclkx_ext > instConfig.inputClkFreq))
        {
            report.logError(`AHCLKX outside scope`, inst,  "masterClkx");
        }
        else
        {
            ahclkx = instConfig.inputClkFreq / Math.round(instConfig.inputClkFreq / ahclkx_ext);
            report.logInfo(`Calculated AHCLKX: ${ahclkx} Hz`, inst, "txHclkSource");
        }
    }

    if (inst.txAclkSource == 0)
    {
        aclkx = aclkx_ext;
        report.logInfo(`Expected ACLKX: ${aclkx} Hz`, inst, "txAclkSource");
    }
    else
    {
        aclkx = ahclkx / Math.round(ahclkx/(inst.NumTxSlots * inst.TxSlotSize * inst.fsx * 1000));
        report.logInfo(`Calculated ACLKX: ${aclkx} Hz`, inst, "txAclkSource");
    }

    if ((inst.txAclkSource == 1) && ((ahclkx % aclkx) != 0))
    {
        report.logError(`AHCLKX is not multiple of ACLKX`, inst,  "masterClkx");
    }

    let afsx_int = aclkx / (inst.NumTxSlots * inst.TxSlotSize * 1000);
    if (inst.txFsSource == 1)
    {
        report.logInfo(`Calculated FSX: ${afsx_int} KHz`, inst, "afsx");
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

exports = mcasp_module;
