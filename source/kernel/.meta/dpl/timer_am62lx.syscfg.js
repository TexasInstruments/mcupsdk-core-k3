
let common = system.getScript("/common");

let timerClockSourceConfig_a53 = [
        {
            "name": "HFOSC0_CLKOUT",
        },
        {
            "name": "DEVICE_CLKOUT_32K",
        },
        {
            "name": "MAIN_PLL0_HSDIV6_CLKOUT",
        },
        {
            "name": "CLK_12M_RC",
        },
        {
            "name": "WKUP_EXT_REFCLK0",
        },
        {
            "name": "EXT_REFCLK1",
        },
        {
            "name": "CP_GEMAC_CPTS0_RFT_CLK",
        },
        {
            "name": "WKUP_PLL0_HSDIV1_CLKOUT",
        },
        {
            "name": "WKUP_PLL0_HSDIV7_CLKOUT",
        },
        {
            "name": "CPSW0_CPTS_GENF0",
        },
        {
            "name": "CPSW0_CPTS_GENF1",
        },
];
let timerClockSourceConfig_wkup = [
        {
            "name": "HFOSC0_CLKOUT",
        },
        {
            "name": "PER_SYSCLK0_DIV2",
        },
        {
            "name": "CLK_12M_RC",
        },
        {
            "name": "WKUP_PLL0_HSDIV7_CLKOUT",
        },
        {
            "name": "WKUP_EXT_REFCLK0",
        },
        {
            "name": "DEVICE_CLKOUT_32K",
        },
        {
            "name": "CPSW0_CPTS_GENF0",
        },
        {
            "name": "CLK_32K_RC",
        },
];

function getTimerClockSourceValue(instance) {
    let cpu = common.getSelfSysCfgCoreName();
    let clkSelMuxValue = 0;

    if(cpu.match(/a53*/)) {
        switch(instance.clkSource) {
            default:
            case "HFOSC0_CLKOUT":
                clkSelMuxValue = 0x0;
                break;
            case "DEVICE_CLKOUT_32K":
                clkSelMuxValue = 0x1;
                break;
            case "MAIN_PLL0_HSDIV6_CLKOUT":
                clkSelMuxValue = 0x2;
                break;
            case "CLK_12M_RC":
                clkSelMuxValue = 0x3;
                break;
            case "WKUP_EXT_REFCLK0":
                clkSelMuxValue = 0x4;
                break;
            case "EXT_REFCLK1":
                clkSelMuxValue = 0x5;
                break;
            case "CP_GEMAC_CPTS0_RFT_CLK":
                clkSelMuxValue = 0x7;
                break;
            case "WKUP_PLL0_HSDIV1_CLKOUT":
                clkSelMuxValue = 0x8;
                break;
            case "WKUP_PLL0_HSDIV7_CLKOUT":
                clkSelMuxValue = 0x9;
                break;
            case "CPSW0_CPTS_GENF0":
                clkSelMuxValue = 0xA;
                break;
            case "CPSW0_CPTS_GENF1":
                clkSelMuxValue = 0xB;
                break;
        }
    }
    else
    {
        switch(instance.clkSource) {
            default:
            case "HFOSC0_CLKOUT":
                clkSelMuxValue = 0x0;
                break;
            case "PER_SYSCLK0_DIV2":
                clkSelMuxValue = 0x1;
                break;
            case "CLK_12M_RC":
                clkSelMuxValue = 0x2;
                break;
            case "WKUP_PLL0_HSDIV7_CLKOUT":
                clkSelMuxValue = 0x3;
                break;
            case "WKUP_EXT_REFCLK0":
                clkSelMuxValue = 0x4;
                break;
            case "DEVICE_CLKOUT_32K":
                clkSelMuxValue = 0x5;
                break;
            case "CPSW0_CPTS_GENF0":
                clkSelMuxValue = 0x6;
                break;
            case "CLK_32K_RC":
                clkSelMuxValue = 0x7;
                break;
        }

    }
    return clkSelMuxValue;
}

function getStaticConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr;

    if (cpu.match(/a53*/)){
        let staticConfig_a53 = [];

        for(let i=0; i<2; i++)
        {
            staticConfig_a53.push(
                {
                    timerName: `WKUP_DMTIMER${i}`,
                    timerBaseAddr: 0x2b100000 + i*0x10000,
                    timerHwiIntNum: 222 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x43022000 + 4*i,
                    lockUnlockDomain: "SOC_DOMAIN_ID_WKUP",
                    lockUnlockPartition: 2,
                }
            )
        }

        for(let i=0; i<4; i++)
        {
            staticConfig_a53.push(
                {
                    timerName: `DMTIMER${i}`,
                    timerBaseAddr: 0x02400000+ i*0x10000,
                    timerHwiIntNum: 202 + i,
                    timerInputPreScaler: 1,
                    clkSelMuxAddr: 0x09115000 + 1000*i,
                    disableClkSourceConfig: false,
                    lockUnlockDomain: "SOC_DOMAIN_ID_MAIN",
                    lockUnlockPartition: 2,
                }
            )
        }

        staticConfigArr = staticConfig_a53;
    }

    return staticConfigArr;
}

function getInterfaceName(inst) {
    let cpu = common.getSelfSysCfgCoreName();
    if(cpu.match(/a53*/)){
        return "TIMER";
    }
    return "WKUP_TIMER";
}

function getTimerClockSourceConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    if(cpu.match(/a53*/)) {
        return timerClockSourceConfig_a53;
    }

    return timerClockSourceConfig_wkup;
}

function getTimerClockSourceHz(clkSource) {
    let cpu = common.getSelfSysCfgCoreName();
    let clkSourceHz = 0;

    if(cpu.match(/a53*/)) {
        /* A53 */
        switch(clkSource) {
            default:clkSourceHz
            case "HFOSC0_CLKOUT":
                clkSourceHz = 25*1000000;
                break;
            case "DEVICE_CLKOUT_32K":
                clkSourceHz = 32*1000;
                break;
            case "MAIN_PLL0_HSDIV6_CLKOUT":
                clkSourceHz = 250*1000000;
                break;
            case "CLK_12M_RC":
                clkSourceHz = 12*1000000;
                break;
            case "WKUP_EXT_REFCLK0":
                clkSourceHz = 100*1000000;
                break;
            case "EXT_REFCLK1":
                clkSourceHz = 100*1000000;
                break;
            case "CP_GEMAC_CPTS0_RFT_CLK":
                clkSourceHz = 200*1000000;
                break;
            case "WKUP_PLL0_HSDIV1_CLKOUT":
                clkSourceHz = 96*1000000;
                break;
            case "WKUP_PLL0_HSDIV7_CLKOUT":
                clkSourceHz = 200*1000000;
                break;
            case "CPSW2G_CPTS_GENF0":
                clkSourceHz = 32*1000;
                break;
            case "CPSW2G_CPTS_GENF1":
                clkSourceHz = 32*1000;
                break;
        }
    }
    else
    {
        switch(clkSource) {
            default:
            case "HFOSC0_CLKOUT":
                clkSourceHz = 25*1000000;
                break;
            case "PER_SYSCLK0_DIV2":
                clkSourceHz = 200*1000000;
                break;
            case "CLK_12M_RC":
                clkSourceHz = 12*1000000;
                break;
            case "WKUP_PLL0_HSDIV7_CLKOUT":
                clkSourceHz = 200*1000000;
                break;
            case "WKUP_EXT_REFCLK0":
                clkSourceHz = 100*1000000;
                break;
            case "DEVICE_CLKOUT_32K":
                clkSourceHz = 32*1000;
                break;
            case "CPSW0_CPTS_GENF0":
                clkSourceHz = 1*1000000;
                break;
            case "CLK_32K_RC":
                clkSourceHz = 32*1000;
                break;
        }
    }

    return clkSourceHz;
}

function getBlockedTimers() {
    let cpu = common.getSelfSysCfgCoreName();
    return [];
}

exports = {
    getStaticConfigArr,
    getTimerClockSourceConfigArr,
    getTimerClockSourceValue,
    getTimerClockSourceHz,
    getInterfaceName,
    getBlockedTimers,
};
