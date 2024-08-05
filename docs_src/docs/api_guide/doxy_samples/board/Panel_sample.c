//! [include]
#include <board/panel/panel_i2c.h>

BridgeSii9022a_Object gBridgeSii9022aObj =
{
    .modeInfo = {
        .standard = FVID2_STD_1080P_60,
        .modeCode = 16,
        .pixClk = 14850,
        .vFreq = 60,
        .pixels = 2200,
        .lines = 1125,
        .embSyncPrms = {
            .hBitToHSync = 88,
            .field2Offset = 0,
            .hWidth = 44,
            .vBitToVSync = 4,
            .vWidth = 5.
        },
        .extSyncPrms = {
            .deDelay = 192,
            .deTop = 41,
            .deCnt = 1920,
            .deLine = 1080,
        }
    }
};

/* PANEL Driver handles - opened during Board_panelOpen() */
Panel_Handle gPanelHandle[CONFIG_PANEL_NUM_INSTANCES];

Panel_Params gPanelParams[CONFIG_PANEL_NUM_INSTANCES] =
{
    {
        .bridgeParams = {
            .deviceI2cInstId = HDMI_I2C_CONFIG,
            .deviceI2cAddr = 0x3B,
            .inpClk = 0U,
            .hotPlugGpioIntrLine = 0U,
            .clkEdge = FALSE,
            .outputFormat = BRIDGE_SII9022A_HDMI_RGB,
        },
        .vidOutParams = {
            .standard = FVID2_STD_1080P_60,
            .videoDataFormat = FVID2_DF_RGB24_888,
            .videoIfMode = FVID2_VIFM_SCH_DS_AVID_VSYNC,
            .videoIfWidth = FVID2_VIFW_24BIT,
        }
    },
};

Panel_PinCtrl gPinCtrlConfig[CONFIG_PANEL_NUM_INSTANCES] =
{
    {
        .pinCtrlI2cInstance = HDMI_I2C_CONFIG,
        .pinCtrlI2cAddr = 0x23,
        .numPins = 1,
        .pinConf = {
           {
                .pinIoNum = 21,
                .pinType  = TCA6424_MODE_OUTPUT,
                .pinVal   = TCA6424_OUT_STATE_HIGH,
           }
        },
    },
};

/* PANEL Config */
Panel_Config gPanelConfig[CONFIG_PANEL_NUM_INSTANCES] =
{
    {
        .panelType = CONFIG_PANEL_TYPE_I2C,
        .fxns = &gPanelBridgeSii9022aFxns,
        .object = (void *)&gBridgeSii9022aObj,
        .pinConfig = &gPinCtrlConfig[0],

    },
};

uint32_t gPanelConfigNum = CONFIG_PANEL_NUM_INSTANCES;

//! [include]

void open(void)
{
//! [open]
    gPanelHandle[CONFIG_PANEL0] = NULL;
    gPanelHandle[CONFIG_PANEL0] = Panel_open(CONFIG_PANEL0, &gPanelParams[CONFIG_PANEL0]);
    if (!gPanelHandle[CONFIG_PANEL0])
    {
        DebugP_assert(FALSE);
    }
//! [open]
}

void close(void)
{
//! [close]
    Panel_close(gPanelHandle[CONFIG_PANEL0]);
//! [close]
}