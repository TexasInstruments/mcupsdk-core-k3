/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2022
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file csirx_recovery_test_main.c
 *
 *  \brief CSI RX Recovery Example.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <string.h>

#include <drivers/hw_include/tistdtypes.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/soc.h>
#include <drivers/uart.h>
#include <drivers/gpio.h>
#include <drivers/pinmux.h>
#include <drivers/csirx.h>
#include <drivers/i2c.h>
#include <kernel/nortos/dpl/common/ClockP_nortos_priv.h>
#include <kernel/dpl/TimerP.h>
#include "imx390.h"
#include <board/board_control.h>
#include <board/utils/board_utils.h>
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< Application name */
#define APP_NAME                                  "CSIRX_RCVY_APP"
/**< Number of CSIRX instances exist in SOC */
#define APP_TOTAL_CAPT_INST                       (CSIRX_INSTANCE_ID_MAX)
/**< Number of CSIRX instances to test parallelly */
#define APP_CAPT_TEST_INST_NUM                    ((uint32_t)1U)
/**< Number of channels */
#define APP_CAPT_CH_NUM                           ((uint32_t)1U)
/**< Input Image Data format */
#define APP_CAPT_IMAGE_DT                         (FVID2_CSI2_DF_RAW12)
/**< Frame storage format. Only valid for RAW12 DT. */
#define APP_CAPT_IMAGE_STORAGE_FORMAT             (FVID2_CCSF_BITS12_UNPACKED16)
/**< Number of frames per stream */
#define APP_CAPT_FRAMES_PER_CH                    ((uint32_t)4U)
/**< Frame Attribute: Width in pixels */
#define APP_CAPT_FRAME_WIDTH                      ((uint32_t)1936U)
/**< Frame Attribute: Height in pixels */
#define APP_CAPT_FRAME_HEIGHT                     ((uint32_t)1100U)
/**< Frame Attribute: Bytes per pixel */
#define APP_CAPT_FRAME_BPP                        ((uint32_t)2U)

/**< I2C transaction timeout */
#define APP_I2C_TRANSACTION_TIMEOUT               ((uint32_t)2000U)

/**< Time period to receive frames in app */
#define APP_TEST_PERIOD_IN_SEC                    ((uint32_t)10)

/**< Test to verify INFO events for CSIRX */
#define CSIRX_INFO_TEST                           (1U)

/**
 * @{
 * Macros to control Fusion board and Camera Sensor version for the capture
 */
/**< Fusion Board Revision.
     '0': for Rev B or older boards.
     '1': for Rev C board. */
#define FUSION_BOARD_VER                       (1U)

/**< D3 IMX390 sensor type. */
#define D3IMX390_CM_MODULE                     (0U)
#define D3IMX390_RCM_MODULE                    (1U)

#define APP_CSIRX_INST0_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)
#define APP_CSIRX_INST1_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)
#define APP_CSIRX_INST2_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)


#define UB960_USE_PATTERN_GENERATOR            (0U)

#define UB9702_DESER_RESET_CTL_REG_ADDR        (1U)
#define UB9702_DESER_RESET_VALUE               (2U)

#define BOARD_CSI_I2C_MUX_INSTANCE             (0U)
#define BOARD_CSI_I2C_SWITCH_INSTANCE          (1U)

/**< SOC GPIO0_68 CSI2_EXP_RSTz used with CSI Fusion2 Daughter Board */
#define CONFIG_GPIO0_PIN (68U)

/**< SOC GPIO0_68 CSI2_EXP_RSTz used with CSI Fusion2 Daughter Board */
#define I2C_SWITCH_TCA9543APWR_SLV_ADDR (0x70U)
/** @} */

/**< Frame Attribute: Pitch in bytes */
#define APP_CAPT_FRAME_PITCH                      ((uint32_t)\
                                (APP_CAPT_FRAME_WIDTH * APP_CAPT_FRAME_BPP))
/**< Frame Attribute: size in bytes */
#define APP_CAPT_FRAME_SIZE                                ((uint32_t)\
            (APP_CAPT_FRAME_HEIGHT * APP_CAPT_FRAME_WIDTH * APP_CAPT_FRAME_BPP))

/**< For Ub960 Pattern Generator, most significant byte of active line length in
 * bytes
 */
#define APP_CAPT_FRAME_LINE_LEN_HIGH           ((APP_CAPT_FRAME_PITCH & 0xFF00)>>8)

/**< For Ub960 Pattern Generator, least significant byte of active line length in
 * bytes
 */
#define APP_CAPT_FRAME_LINE_LEN_LOW            (APP_CAPT_FRAME_PITCH & 0x00FF)


/**< For Ub960 Pattern Generator, most significant byte of number of active
 * lines in frame
 */
#define APP_CAPT_FRAME_HEIGHT_HIGH             ((APP_CAPT_FRAME_HEIGHT & 0xFF00)>>8)

/**< For Ub960 Pattern Generator, least significant byte of number of active
 * lines per frame
 */
#define APP_CAPT_FRAME_HEIGHT_LOW              (APP_CAPT_FRAME_HEIGHT & 0x00FF)

/* Print buffer character limit for prints- UART or CCS Console */
#define APP_PRINT_BUFFER_SIZE                   ((uint32_t)4000)

/** \brief Log enable for CSIRX Sample application */
#define CsirxAppTrace                       ((uint32_t) GT_INFO   |\
                                             (uint32_t) GT_TraceState_Enable)

/**< Maximum number of error frame logs to store.
     It stores most recent errors.*/
#define APP_ERR_FRAME_LOG_MAX                                  ((uint32_t)500U)

/**< Print Driver Logs. Set to '1' to enable printing. */
#define APP_PRINT_DRV_LOGS                                     (0U)

#define SENSOR_CFG_SIZE  (3075U)

/**
 * @{
 * I2C Addresses for serialisers/Sensors attached to the UB960
 */
#define UB960_SERIALISER_ADDR                (0x18)
#define D3IMX390_SENSOR_ADDR_CM_MODULE       (0x21)
#define D3IMX390_SENSOR_ADDR_RCM_MODULE      (0x1A)
/** @} */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960 and UB9702 Instance0
 */
#define D3IMX390_INST0_PORT_0_SER_ADDR       (0x74U)
#define D3IMX390_INST0_PORT_1_SER_ADDR       (0x76U)
#define D3IMX390_INST0_PORT_2_SER_ADDR       (0x78U)
#define D3IMX390_INST0_PORT_3_SER_ADDR       (0x7AU)
/** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960 Instance0
 */
#define D3IMX390_INST0_PORT_0_SENSOR_ADDR    (0x40U)
#define D3IMX390_INST0_PORT_1_SENSOR_ADDR    (0x42U)
#define D3IMX390_INST0_PORT_2_SENSOR_ADDR    (0x44U)
#define D3IMX390_INST0_PORT_3_SENSOR_ADDR    (0x46U)
/** @} */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960 Instance1
 */
#define D3IMX390_INST1_PORT_0_SER_ADDR       (0x6CU)
#define D3IMX390_INST1_PORT_1_SER_ADDR       (0x6EU)
#define D3IMX390_INST1_PORT_2_SER_ADDR       (0x70U)
#define D3IMX390_INST1_PORT_3_SER_ADDR       (0x72U)
/** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960 Instance1
 */
#define D3IMX390_INST1_PORT_0_SENSOR_ADDR    (0x48U)
#define D3IMX390_INST1_PORT_1_SENSOR_ADDR    (0x4AU)
#define D3IMX390_INST1_PORT_2_SENSOR_ADDR    (0x4CU)
#define D3IMX390_INST1_PORT_3_SENSOR_ADDR    (0x4EU)

/** @} */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960 Instance1
 */
#define D3IMX390_INST2_PORT_0_SER_ADDR       (0x54U)
#define D3IMX390_INST2_PORT_1_SER_ADDR       (0x56U)
#define D3IMX390_INST2_PORT_2_SER_ADDR       (0x58U)
#define D3IMX390_INST2_PORT_3_SER_ADDR       (0x5AU)
/** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960 Instance1
 */
#define D3IMX390_INST2_PORT_0_SENSOR_ADDR    (0x50U)
#define D3IMX390_INST2_PORT_1_SENSOR_ADDR    (0x52U)
#define D3IMX390_INST2_PORT_2_SENSOR_ADDR    (0x5CU)
#define D3IMX390_INST2_PORT_3_SENSOR_ADDR    (0x5EU)



/**< Number of channels */
#define APP_CAPT_CH_MAX                           ((uint32_t)4U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Capture application object.
 */
typedef struct
{
    uint32_t instId;
   /**< Csirx Drv Instance ID. */
    uint32_t boardCsiInstID;
   /**< Csirx Drv Instance ID. */
    uint32_t cameraSensor;
   /**< Camera sensor type */
    Csirx_CreateParams createPrms;
   /**< Csirx create time parameters */
    Csirx_CreateStatus createStatus;
   /**< Csirx create time status */
    Fvid2_Handle drvHandle;
   /**< FVID2 capture driver handle. */
    Fvid2_CbParams cbPrms;
   /**< Callback params. */
    volatile uint32_t numFramesRcvd;
   /**< Number of frames received */
    uint32_t frameErrorCnt;
   /**< Number of erroneous frames received */
    uint32_t maxWidth;
   /**< Max width in pixels - used for buffer allocation for all instance. */
    uint32_t maxHeight;
   /**< Max height in lines - used for buffer allocation for all instance. */
    Fvid2_Frame frames[APP_CAPT_FRAMES_PER_CH * APP_CAPT_CH_NUM];
   /**< FVID2 Frames that will be used for capture. */
    Csirx_InstStatus captStatus;
   /**< CSIRX Capture status. */
    uint32_t chFrmCnt[APP_CAPT_CH_NUM];
   /**< Number of frames captured per channel. */
    uint32_t errFrmCh[APP_ERR_FRAME_LOG_MAX];
   /**< Channel to which error frame belongs. */
    uint32_t errFrmNo[APP_ERR_FRAME_LOG_MAX];
   /**< Error frame number for the channel. */
    uint32_t errFrmTs[APP_ERR_FRAME_LOG_MAX];
   /**< TS in ms. */
}CsirxApp_CaptInstObj;

/**
 *  \brief Common application object.
 */
typedef struct
{
    Csirx_InitParams initPrms;
   /**< Csirx init time parameters */
    CsirxApp_CaptInstObj appInstObj[APP_CAPT_TEST_INST_NUM];
   /**< Capture application objects */
    Udma_DrvObject udmaDrvObj;
   /**< UDMA driver objects */
}CsirxApp_CaptCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is wrapper function used to print message on
 *          respective consoles
 *
 * \param   pcString        Print contents.
 *
 * \retval  none.
 */
static void CsirxApp_consolePrintf(const char *pcString, ...);

/**
 * \brief   This function is ISR for timer interrupt
 *
 * \param   arg             CSI RX Capture Test Object
 *
 *
 * \retval  none.
 */
void CsirxApp_timerIsr(void *arg);
/**
 * \brief   This function is used to initialize test parameters
 *
 * \param   appInstObj          Type of print message.
 *                          Refer to struct #appCaptObj
 *
 * \retval  none.
 */
static void CsirxApp_initCaptParams(CsirxApp_CaptInstObj *appInstObj);

/**
 * \brief   App Init function.
 *
 * \param   appInstObj          CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_init(CsirxApp_CaptCommonObj *appCommonObj);

/**
 * \brief   App recover function.
 *
 * \param   appInstObj          CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_recover(CsirxApp_CaptInstObj* appInstObj);

/**
 * \brief   App create function.
 *
 * \param   appInstObj          CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_create(CsirxApp_CaptInstObj *appInstObj);

/**
 * \brief   App CSI test function: captures frames.
 *
 * \param   appCommonObj    CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_csiTest(CsirxApp_CaptCommonObj *appCommonObj);

/**
 * \brief   App delete function.
 *
 * \param   appInstObj          CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_delete(CsirxApp_CaptInstObj *appInstObj);

/**
 * \brief   App Init function.
 *
 * \param   appInstObj        CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_deinit(CsirxApp_CaptCommonObj *appCommonObj);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   handle        Fvid2 DRV handle
 *
 * \param   appData       App based back by to CB function
 *
 * \param   reserved      reserved, not used
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   appInstObj        CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_allocAndQFrames(CsirxApp_CaptInstObj *appInstObj);

/**
 * \brief   App Callback function for frame completion.
 *
 * \param   appInstObj        CSI RX Capture Test Object
 *
 * \retval  status          FVID2_SOK on successful
 *                          else otherwise.
 */
static int32_t CsirxApp_captFreeFrames(CsirxApp_CaptInstObj *appInstObj);

/**
 * \brief   App print function for FVID2 driver.
 *
 * \param   str             Print string
 *
 * \retval  None.
 */
void CsirxApp_fvidPrint(const char *str, ...);

/**
 * \brief   App print function for UDMA driver.
 *
 * \param   str             Print string
 *
 * \retval  None.
 */
static void CsirxApp_dmaPrint(const char *str);

/**
 * \brief   App function to configure remote sensors.
 *
 * \param   appInstObj        CSI RX Capture Test Object
 *
 * \retval  Sensor configuration status.
 */
static int32_t CsirxApp_sensorConfig(CsirxApp_CaptInstObj* appInstObj);

#if defined(FREERTOS)
/**
 * \brief   App function to print CPU load and Task load.
 *
 * \param   None.
 *
 * \retval  None.
 */
void CsirxApp_printLoad(void);
#endif

extern void App_wait(uint32_t wait_in_ms);
extern void Drivers_open(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* App common object */
CsirxApp_CaptCommonObj gAppCommonObj;

/* CSIRX instances to use in application */
uint32_t  gAppCapInst[APP_TOTAL_CAPT_INST] = {CSIRX_INSTANCE_ID_0,CSIRX_INSTANCE_ID_1};

/* Memory buffer to hold data */
static uint8_t gFrmDropBuf[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAME_PITCH)] __attribute__(( aligned(128), section(".data_buffer")));
static uint8_t gFrms[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAMES_PER_CH * APP_CAPT_CH_NUM)][APP_CAPT_FRAME_SIZE]__attribute__(( aligned(128), section(".data_buffer")));


/* Semaphore to indicate app completion */
SemaphoreP_Object gAppCompletionSem;

/* I2c Handle to access deserializer */
I2C_Handle gI2cHandle;

/* Fusion2 board detect flag */
bool gFusion2Det = BFALSE;

#if defined(FREERTOS)
/* Capture test Task handle */
extern TaskP_Handle gCsirxAppTask;
#endif
extern uint32_t gTimerBaseAddr[TIMER_NUM_INSTANCES];

static Pinmux_PerCfg_t gMainPinmuxData[] =
{
    {
        PIN_MMC2_DAT0, /* PADCONFIG Ball Name */
        /* Pin mode 7 for accessing GPIO_68 CSI2_EXP_RSTz */
        PIN_MODE(7) | ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION)) /* 0x50007 */
    },
    {PINMUX_END, PINMUX_END}
};

uint16_t gSensorCfg[SENSOR_CFG_SIZE][3] = IMX390_LINEAR_1920X1080_CONFIG;
uint16_t gUb960SensorCfg[][3] = {
#if UB960_USE_PATTERN_GENERATOR
    {0x32, 0x01, 0x50},
    {0x1F, 0x10, 0x1},
    {0xC9, 0x32, 0x1},
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x92, 0x1},
    {0xB2, 0x40, 0x1},
    {0xB0, 0x01, 0x1},
    {0xB1, 0x01, 0x1},
    {0xB2, 0x01, 0x1},
    {0xB1, 0x02, 0x1},
    {0xB2, 0xF3, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, APP_CAPT_IMAGE_DT, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, APP_CAPT_FRAME_LINE_LEN_HIGH, 0x1},
    {0xB1, 0x05, 0x1},
    {0xB2, APP_CAPT_FRAME_LINE_LEN_LOW, 0x1},
    {0xB1, 0x06, 0x1},
    {0xB2, 0x02, 0x1},
    {0xB1, 0x07, 0x1},
    {0xB2, 0x80, 0x1},/*D0*/
    {0xB1, 0x08, 0x1},
    {0xB2, APP_CAPT_FRAME_HEIGHT_HIGH, 0x1},
    {0xB1, 0x09, 0x1},
    {0xB2, APP_CAPT_FRAME_HEIGHT_LOW, 0x1},
    {0xB1, 0x0A, 0x1},
    {0xB2, 0x08, 0x1},
    {0xB1, 0x0B, 0x1},
    {0xB2, 0x80, 0x1},
    {0xB1, 0x0C, 0x1},
    {0xB2, 0x04, 0x1},
    {0xB1, 0x0D, 0x1},
    {0xB2, 0x7D, 0x1},
    {0xB1, 0x0E, 0x1},
    {0xB2, 0x07, 0x1},
    {0xB1, 0x0F, 0x1},
    {0xB2, 0x08, 0x1},
    {0x33, 0x02, 0x1},
    {0xFFFF, 0x00, 0x0} /*End of script */
#else
    {0x01, 0x02, 0x100},
    {0x1f, 0x00, 0x1},

    {0xB0, 0x1C,0x1},
    {0xB1, 0x16,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x17,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x18,0x1},
    {0xB2, 0x00,0x1},
    {0xB1, 0x19,0x1},
    {0xB2, 0x00,0x1},
    {0xB0, 0x1C,0x1},
    {0xB1, 0x15,0x1},
    {0xB2, 0x0A,0x1},
    {0xB2, 0x00,0x10},

    {0x0D, 0x90, 0x1}, /*I/O to 3V3 - Options not valid with datashee*/
    {0x0C, 0x0F, 0x1}, /*Enable All ports*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0x58, 0x5E, 0x1},
    {0x72, 0x00, 0x1}, /*VC map*/

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x04, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 1*/
    {0x4C, 0x12, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x08, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB0, 0x08, 0x1},
    {0x42, 0x71, 0x1}, /*Unknown*/
    {0x41, 0xF0, 0x1}, /*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 2*/
    {0x4C, 0x24, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x0C, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    /*Select Channel 3*/
    {0x4C, 0x38, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x03, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB1, 0x13, 0x1},
    {0xB2, 0x20, 0x1},
    {0xB0, 0x10, 0x1},
    {0xB1, 0x04, 0x1},
    {0xB2, 0x3F, 0x1},
    {0xB1, 0x14, 0x1},
    {0xB2, 0x3F, 0x1},
    {0x42, 0x71, 0x1},/*Unknown*/
    {0x41, 0xF0, 0x1},/*Unknown*/
    {0xB9, 0x18, 0x1},

    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x20, 0x00, 0x1}, /*Forwarding and using CSIport 0 */

    /*Sets GPIOS*/
    {0x10, 0x83, 0x1},
    {0x11, 0xA3, 0x1},
    {0x12, 0xC3, 0x1},
    {0x13, 0xE3, 0x1},

    {0x4C, 0x01, 0x1}, /* 0x01 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x00,0x1}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x12, 0x1}, /* 0x12 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_1_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_1_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0x55,0x1}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x24, 0x1}, /* 0x24 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_2_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_2_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xaa,0x1}, /*VC Map - All to 2 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x1},

    {0x4C, 0x38, 0x1}, /* 0x38 */
    {0x32, 0x01, 0x1}, /*Enable TX port 0*/
    {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x1}, /*Unknown*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_3_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_3_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x1}, /*CSI Mode*/
    {0x72, 0xFF,0x1}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x1},
    {0xB1, 0x15, 0x1},
    {0xB2, 0x0A, 0x1},
    {0xB2, 0x00, 0x100},
#endif
};

uint16_t gUb9702SensorCfg[][3] = {
    {0x3C, 0x0F, 0x10}, /* Disable lock lost feature */

    /*Sets GPIOS*/
    {0x10, 0x83, 0x1},
    {0x11, 0xA3, 0x1},
    {0x12, 0xC3, 0x1},
    {0x13, 0xE3, 0x1},

    /*Port 0 Config*/
    {0x4C, 0x01, 0x20},
    {0xB0, 0x04, 0x20},
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ max to 0 */
    {0xE4, 0x02, 0x10}, /* Set FPD functional mode to FPD3 Async CSI Mode */
    {0x58, 0x5E, 0x10}, /* BC_FREQ_SELECT=(PLL_FREQ/3200) Mbps */
    {0xB1, 0xA8, 0x20},
    {0xB2, 0x00, 0x20}, /* Set aeq_lock_mode = 1 */
    {0xB1, 0x04, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */
    {0xB1, 0x1B, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */


    /*Port 1 Config*/
    {0x4C, 0x12, 0x20},
    {0xB0, 0x08, 0x20},
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ max to 0 */
    {0xE4, 0x02, 0x10}, /* Set FPD functional mode to FPD3 Async CSI Mode */
    {0x58, 0x5E, 0x10}, /* BC_FREQ_SELECT=(PLL_FREQ/3200) Mbps */
    {0xB1, 0xA8, 0x20},
    {0xB2, 0x00, 0x20}, /* Set aeq_lock_mode = 1 */
    {0xB1, 0x04, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */
    {0xB1, 0x1B, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */


    /*Port 2 Config*/
    {0x4C, 0x24, 0x20},
    {0xB0, 0x0C, 0x20},
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ max to 0 */
    {0xE4, 0x02, 0x10}, /* Set FPD functional mode to FPD3 Async CSI Mode */
    {0x58, 0x5E, 0x10}, /* BC_FREQ_SELECT=(PLL_FREQ/3200) Mbps */
    {0xB1, 0xA8, 0x20},
    {0xB2, 0x00, 0x20}, /* Set aeq_lock_mode = 1 */
    {0xB1, 0x04, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */
    {0xB1, 0x1B, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */


     /*Port 3 Config*/
    {0x4C, 0x38, 0x20},
    {0xB0, 0x10, 0x20},
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ max to 0 */
    {0xE4, 0x02, 0x10}, /* Set FPD functional mode to FPD3 Async CSI Mode */
    {0x58, 0x5E, 0x10}, /* BC_FREQ_SELECT=(PLL_FREQ/3200) Mbps */
    {0xB1, 0xA8, 0x20},
    {0xB2, 0x00, 0x20}, /* Set aeq_lock_mode = 1 */
    {0xB1, 0x04, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */
    {0xB1, 0x1B, 0x20},
    {0xB2, 0x00, 0x20}, /* Set FPD PBC drv into FPD IV mode */


    {0x0C, 0x0F, 0x20}, /* Enable RX ports */
    {0x01, 0x21, 0x20}, /* Soft Reset and Release GPIO Hold */


    /*Port 0 Config*/
    {0x4C, 0x01, 0x20},
    {0xB0, 0x04, 0x20},
    {0xD4, 0x00, 0x20}, /* Release State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x23, 0x20}, /* AEQ restart to provide more deterministic AEQ code prior to AEQ LMS */
    /* First Time Power Up */
    {0xB1, 0x2C, 0x20},
    {0xB1, 0x27, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ Min */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x01, 0x20}, /* Set AEQ Max */
    {0xB1, 0x2B, 0x20}, /* Set AEQ offset */
    {0xB2, 0x00, 0x20}, /* Set Offset to 0 */
    {0xB1, 0x9E, 0x20},
    {0xB2, 0x00, 0x20}, /* Enable AEQ tap2 */
    {0xB1, 0xF1, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA Gain 1 Gain 2 override to 0 */
    {0xB1, 0x77, 0x20},
    {0xB2, 0x80, 0x20}, /* Set VGA Initial Sweep Gain to 0 */
    {0xB1, 0x74, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA_Adapt (VGA Gain) override to 0 (thermometer encoded) */
    {0xB1, 0x2E, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable VGA_SWEEP */
    {0xB1, 0xF0, 0x20},
    {0xB2, 0x00, 0x20}, /* Disable VGA_SWEEP_GAIN_OV, disable VGA_TUNE_OV */
    {0xB1, 0x72, 0x20},
    {0xB2, 0x2B, 0x20}, /* Set VGA HIGH Threshold to 43 */
    {0xB1, 0x73, 0x20},
    {0xB2, 0x12, 0x20}, /* Set VGA LOW Threshold to 18 */
    {0xB1, 0x87, 0x20},
    {0xB2, 0x20, 0x20}, /* Set vga_sweep_th to 32 */
    {0xB1, 0x21, 0x20},
    {0xB2, 0xEF, 0x20}, /* Set AEQ timer to 400us/step and parity threshold to 7 */
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0x01, 0x21, 0x20}, /* Soft reset and release GPIO hold */
    {0xD4, 0x00, 0x20}, /* Release SM in reset */
    {0xB1, 0x90, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable DFE LMS */
    {0xB1, 0x71, 0x20},
    {0xB2, 0x20, 0x20}, /* Disable VGA Gain1 override */
    {0xB2, 0x00, 0x20}, /* Disable VGA Gain2 override */
    {0x32, 0x03, 0x20}, /* Enable TX ports */
    {0x33, 0x42, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_RCM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C,0x0}, /*CSI Mode*/

    {0xA0, 0x10, 0x0}, /*VC Map */
    {0xB0, 0x04, 0x20},
    {0x01, 0x01, 0x50},

    /*Port 1 Config*/
    {0x4C, 0x12, 0x20},
    {0xB0, 0x08, 0x20},
    {0xD4, 0x00, 0x20}, /* Release State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x23, 0x20}, /* AEQ restart to provide more deterministic AEQ code prior to AEQ LMS */
    /* First Time Power Up */
    {0xB1, 0x2C, 0x20},
    {0xB1, 0x27, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ Min */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x01, 0x20}, /* Set AEQ Max */
    {0xB1, 0x2B, 0x20}, /* Set AEQ offset */
    {0xB2, 0x00, 0x20}, /* Set Offset to 0 */
    {0xB1, 0x9E, 0x20},
    {0xB2, 0x00, 0x20}, /* Enable AEQ tap2 */
    {0xB1, 0xF1, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA Gain 1 Gain 2 override to 0 */
    {0xB1, 0x77, 0x20},
    {0xB2, 0x80, 0x20}, /* Set VGA Initial Sweep Gain to 0 */
    {0xB1, 0x74, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA_Adapt (VGA Gain) override to 0 (thermometer encoded) */
    {0xB1, 0x2E, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable VGA_SWEEP */
    {0xB1, 0xF0, 0x20},
    {0xB2, 0x00, 0x20}, /* Disable VGA_SWEEP_GAIN_OV, disable VGA_TUNE_OV */
    {0xB1, 0x72, 0x20},
    {0xB2, 0x2B, 0x20}, /* Set VGA HIGH Threshold to 43 */
    {0xB1, 0x73, 0x20},
    {0xB2, 0x12, 0x20}, /* Set VGA LOW Threshold to 18 */
    {0xB1, 0x87, 0x20},
    {0xB2, 0x20, 0x20}, /* Set vga_sweep_th to 32 */
    {0xB1, 0x21, 0x20},
    {0xB2, 0xEF, 0x20}, /* Set AEQ timer to 400us/step and parity threshold to 7 */
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0x01, 0x21, 0x20}, /* Soft reset and release GPIO hold */
    {0xD4, 0x00, 0x20}, /* Release SM in reset */
    {0xB1, 0x90, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable DFE LMS */
    {0xB1, 0x71, 0x20},
    {0xB2, 0x20, 0x20}, /* Disable VGA Gain1 override */
    {0xB2, 0x00, 0x20}, /* Disable VGA Gain2 override */
    {0x32, 0x03, 0x20}, /* Enable TX ports */
    {0x33, 0x42, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_1_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_RCM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_1_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C, 0x0}, /*CSI Mode*/

    {0xA0, 0x11, 0x0}, /*VC Map */
    {0xB0, 0x08, 0x20},
    {0x01, 0x01, 0x50},


    /*Port 2 Config*/
    {0x4C, 0x24, 0x20},
    {0xB0, 0x0C, 0x20},
    {0xD4, 0x00, 0x20}, /* Release State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x23, 0x20}, /* AEQ restart to provide more deterministic AEQ code prior to AEQ LMS */
    /* First Time Power Up */
    {0xB1, 0x2C, 0x20},
    {0xB1, 0x27, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ Min */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x01, 0x20}, /* Set AEQ Max */
    {0xB1, 0x2B, 0x20}, /* Set AEQ offset */
    {0xB2, 0x00, 0x20}, /* Set Offset to 0 */
    {0xB1, 0x9E, 0x20},
    {0xB2, 0x00, 0x20}, /* Enable AEQ tap2 */
    {0xB1, 0xF1, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA Gain 1 Gain 2 override to 0 */
    {0xB1, 0x77, 0x20},
    {0xB2, 0x80, 0x20}, /* Set VGA Initial Sweep Gain to 0 */
    {0xB1, 0x74, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA_Adapt (VGA Gain) override to 0 (thermometer encoded) */
    {0xB1, 0x2E, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable VGA_SWEEP */
    {0xB1, 0xF0, 0x20},
    {0xB2, 0x00, 0x20}, /* Disable VGA_SWEEP_GAIN_OV, disable VGA_TUNE_OV */
    {0xB1, 0x72, 0x20},
    {0xB2, 0x2B, 0x20}, /* Set VGA HIGH Threshold to 43 */
    {0xB1, 0x73, 0x20},
    {0xB2, 0x12, 0x20}, /* Set VGA LOW Threshold to 18 */
    {0xB1, 0x87, 0x20},
    {0xB2, 0x20, 0x20}, /* Set vga_sweep_th to 32 */
    {0xB1, 0x21, 0x20},
    {0xB2, 0xEF, 0x20}, /* Set AEQ timer to 400us/step and parity threshold to 7 */
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0x01, 0x21, 0x20}, /* Soft reset and release GPIO hold */
    {0xD4, 0x00, 0x20}, /* Release SM in reset */
    {0xB1, 0x90, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable DFE LMS */
    {0xB1, 0x71, 0x20},
    {0xB2, 0x20, 0x20}, /* Disable VGA Gain1 override */
    {0xB2, 0x00, 0x20}, /* Disable VGA Gain2 override */
    {0x32, 0x03, 0x20}, /* Enable TX ports */
    {0x33, 0x42, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_2_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_RCM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_2_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C, 0x0}, /*CSI Mode*/

    {0xA0, 0x12, 0x0}, /*VC Map */
    {0xB0, 0x0C, 0x20},
    {0x01, 0x01, 0x50},


    /*Port 3 Config*/
    {0x4C, 0x38, 0x20},
    {0xB0, 0x10, 0x20},
    {0xD4, 0x00, 0x20}, /* Release State Machine in reset */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x23, 0x20}, /* AEQ restart to provide more deterministic AEQ code prior to AEQ LMS */
    /* First Time Power Up */
    {0xB1, 0x2C, 0x20},
    {0xB1, 0x27, 0x20},
    {0xB2, 0x00, 0x20}, /* Set AEQ Min */
    {0xB1, 0x28, 0x20},
    {0xB2, 0x01, 0x20}, /* Set AEQ Max */
    {0xB1, 0x2B, 0x20}, /* Set AEQ offset */
    {0xB2, 0x00, 0x20}, /* Set Offset to 0 */
    {0xB1, 0x9E, 0x20},
    {0xB2, 0x00, 0x20}, /* Enable AEQ tap2 */
    {0xB1, 0xF1, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA Gain 1 Gain 2 override to 0 */
    {0xB1, 0x77, 0x20},
    {0xB2, 0x80, 0x20}, /* Set VGA Initial Sweep Gain to 0 */
    {0xB1, 0x74, 0x20},
    {0xB2, 0x00, 0x20}, /* Set VGA_Adapt (VGA Gain) override to 0 (thermometer encoded) */
    {0xB1, 0x2E, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable VGA_SWEEP */
    {0xB1, 0xF0, 0x20},
    {0xB2, 0x00, 0x20}, /* Disable VGA_SWEEP_GAIN_OV, disable VGA_TUNE_OV */
    {0xB1, 0x72, 0x20},
    {0xB2, 0x2B, 0x20}, /* Set VGA HIGH Threshold to 43 */
    {0xB1, 0x73, 0x20},
    {0xB2, 0x12, 0x20}, /* Set VGA LOW Threshold to 18 */
    {0xB1, 0x87, 0x20},
    {0xB2, 0x20, 0x20}, /* Set vga_sweep_th to 32 */
    {0xB1, 0x21, 0x20},
    {0xB2, 0xEF, 0x20}, /* Set AEQ timer to 400us/step and parity threshold to 7 */
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0x01, 0x21, 0x20}, /* Soft reset and release GPIO hold */
    {0xD4, 0x00, 0x20}, /* Release SM in reset */
    {0xB1, 0x90, 0x20},
    {0xB2, 0x40, 0x20}, /* Enable DFE LMS */
    {0xB1, 0x71, 0x20},
    {0xB2, 0x20, 0x20}, /* Disable VGA Gain1 override */
    {0xB2, 0x00, 0x20}, /* Disable VGA Gain2 override */
    {0x32, 0x03, 0x20}, /* Enable TX ports */
    {0x33, 0x42, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_3_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_RCM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_3_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x6C, 0x0}, /*CSI Mode*/

    {0xA0, 0x13, 0x0}, /*VC Map */
    {0xB0, 0x10, 0x20},
    {0x01, 0x01, 0x50},

    {0x32, 0x03, 0x20},

    /*  2500mbps   */
    {0x1F, 0x10, 0x20},
    {0xC9, 0x19, 0x20},
    {0xB0, 0x1C, 0x20},
    {0xB1, 0x92, 0x20},
    {0xB2, 0x80, 0x20},

    {0x20, 0xF0, 0x20},
    {0xC7, 0x10, 0x20},
    {0x33, 0x43, 0x20},
    {0x20, 0x00, 0x20},

    {0x3B, 0xFF, 0x20},
};

uint16_t gUb953SensorCfg[][3] = {
    {0x01, 0x01, 0x80},
    {0x02, 0x72, 0x10},

#if (0U == FUSION_BOARD_VER)
    {0x06, 0x21, 0x1F},
#elif (1U == FUSION_BOARD_VER)
    {0x06, 0x41, 0x1F},
#else
/* Unsupported version */
#endif
    {0x07, 0x28, 0x1F},
    {0x0D, 0x01, 0x10},

    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x80},
};

uint32_t gUb953I2CAddrInst0[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST0_PORT_0_SER_ADDR,
    D3IMX390_INST0_PORT_1_SER_ADDR,
    D3IMX390_INST0_PORT_2_SER_ADDR,
    D3IMX390_INST0_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddrInst0[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST0_PORT_0_SENSOR_ADDR,
    D3IMX390_INST0_PORT_1_SENSOR_ADDR,
    D3IMX390_INST0_PORT_2_SENSOR_ADDR,
    D3IMX390_INST0_PORT_3_SENSOR_ADDR
};
uint32_t gUb953I2CAddrInst1[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST1_PORT_0_SER_ADDR,
    D3IMX390_INST1_PORT_1_SER_ADDR,
    D3IMX390_INST1_PORT_2_SER_ADDR,
    D3IMX390_INST1_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddrInst1[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST1_PORT_0_SENSOR_ADDR,
    D3IMX390_INST1_PORT_1_SENSOR_ADDR,
    D3IMX390_INST1_PORT_2_SENSOR_ADDR,
    D3IMX390_INST1_PORT_3_SENSOR_ADDR
};
uint32_t gUb953I2CAddrInst2[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST2_PORT_0_SER_ADDR,
    D3IMX390_INST2_PORT_1_SER_ADDR,
    D3IMX390_INST2_PORT_2_SER_ADDR,
    D3IMX390_INST2_PORT_3_SER_ADDR
};

uint32_t gSensorI2CAddrInst2[APP_CAPT_CH_MAX] =
{
    D3IMX390_INST2_PORT_0_SENSOR_ADDR,
    D3IMX390_INST2_PORT_1_SENSOR_ADDR,
    D3IMX390_INST2_PORT_2_SENSOR_ADDR,
    D3IMX390_INST2_PORT_3_SENSOR_ADDR
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int Csirx_recoveryTest(void)
{
    int retVal = FVID2_SOK;
    CsirxApp_CaptInstObj *appInstObj[APP_CAPT_TEST_INST_NUM];
    CsirxApp_CaptCommonObj *appCommonObj;
    appCommonObj = &gAppCommonObj;

    Drivers_open();

    /* Creating semaphore to indicate application completion of each Instance */
    SemaphoreP_constructBinary(&gAppCompletionSem,0U);

    for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
    {
        appInstObj[i] = &appCommonObj->appInstObj[i];
        memset(appInstObj[i], 0x0, sizeof (CsirxApp_CaptInstObj));
    }
    /* Initialize application object for current capture context */
    for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
    {
        appInstObj[i]->instId = gAppCapInst[i];
        CsirxApp_initCaptParams(appInstObj[i]);
    }

    /* App Init */
    retVal += CsirxApp_init(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsirxApp_init() FAILED!!!\r\n");
    }

    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ":===================Setup Details===================\r\n");


    if ((1U == APP_CAPT_TEST_INST_NUM) && (CSIRX_INSTANCE_ID_0 == appInstObj[0]->instId))
    {
        GT_0trace(CsirxAppTrace, GT_INFO, APP_NAME ": Capture Instance: 0\r\n");
    }
    else if ((1U == APP_CAPT_TEST_INST_NUM) && (CSIRX_INSTANCE_ID_1 == appInstObj[0]->instId))
    {
        GT_0trace(CsirxAppTrace, GT_INFO, APP_NAME ": Capture Instance: 1\r\n");
    }
#if defined(SOC_J784S4) || defined(SOC_J742S2)
    else if ((1U == APP_CAPT_TEST_INST_NUM) && (CSIRX_INSTANCE_ID_2 == appInstObj[0]->instId))
    {
        GT_0trace(CsirxAppTrace, GT_INFO, APP_NAME ": Capture Instance: 2\r\n");
    }
#endif
    else if ((2U == APP_CAPT_TEST_INST_NUM) && (CSIRX_INSTANCE_ID_0 == appInstObj[0]->instId) && (CSIRX_INSTANCE_ID_1 == appInstObj[1]->instId))
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Both Capture Instance 0 and Capture Instance 1\r\n");
    }
    GT_1trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": Capture DF:0x%x\r\n", APP_CAPT_IMAGE_DT);
    GT_2trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": Capture Resolution:%d x %d\r\n",
              APP_CAPT_FRAME_WIDTH,
              APP_CAPT_FRAME_HEIGHT);
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ":===================================================\r\n");

    /* App Create */
    if (FVID2_SOK == retVal)
    {
        for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
        {
            retVal += CsirxApp_create(appInstObj[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": [ERROR]CsirxApp_create() FAILED!!!\r\n");
            }
        }
    }

    /*  APP start */
    retVal = CsirxApp_csiTest(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsirxApp_csiTest() FAILED!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
        {
            retVal += CsirxApp_recover(appInstObj[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": [ERROR]CsirxApp_recover() FAILED!!!\r\n");
            }
        }
    }

    /*  start APP again */
    retVal = CsirxApp_csiTest(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsirxApp_csiTest() FAILED!!!\r\n");
    }

    /* App CSI delete function */
    if (FVID2_SOK == retVal)
    {
        for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
        {
            retVal += CsirxApp_delete(appInstObj[i]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(CsirxAppTrace, GT_ERR,
                          APP_NAME ": [ERROR]CsirxApp_delete() FAILED!!!\r\n");
            }
        }
    }

    /* App CSI De-initialization function */
    if (FVID2_SOK == retVal)
    {
        retVal += CsirxApp_deinit(appCommonObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsirxAppTrace, GT_ERR,
                      APP_NAME ": [ERROR]CsirxApp_deinit() FAILED!!!\r\n");
        }
    }

    /* using 'CsirxApp_consolePrintf' instead of GT trace as Fvid2_deInit has happend */
    CsirxApp_consolePrintf("Sample Application - DONE !!!\r\n");

    return (retVal);
}

void CsirxApp_timerIsr(void *arg)
{
    // int32_t retVal = FVID2_SOK;
    static volatile uint32_t timerIsrCount=0;
    timerIsrCount++;
    if (timerIsrCount == APP_TEST_PERIOD_IN_SEC)
    {
        TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);
        timerIsrCount = 0;

        // CsirxApp_CaptCommonObj *appCommonObj=(CsirxApp_CaptCommonObj*)arg;
        // /* Stop the streams immediately after the timeout is reached */
        // for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
        // {
        //     retVal += Fvid2_stop(appCommonObj->appInstObj[i].drvHandle, NULL);
        //     if (FVID2_SOK != retVal)
        //     {
        //         GT_1trace(CsirxAppTrace, GT_ERR,
        //                 APP_NAME ": Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObj[i].instId);
        //     }
        // }
        /* Post semaphore to print the results */
        SemaphoreP_post(&gAppCompletionSem);
    }
}

static void CsirxApp_initCaptParams(CsirxApp_CaptInstObj* appInstObj)
{
    uint32_t loopCnt = 0U;

    if (appInstObj->instId == CSIRX_INSTANCE_ID_0)
    {
        appInstObj->boardCsiInstID = 0;
        appInstObj->cameraSensor = APP_CSIRX_INST0_CAMERA_SENSOR;
    }
    else if (appInstObj->instId == CSIRX_INSTANCE_ID_1)
    {
        appInstObj->boardCsiInstID = 1;
        appInstObj->cameraSensor = APP_CSIRX_INST1_CAMERA_SENSOR;
    }
    else
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Invalid Capture Instance\r\n");
    }

    /* set instance configuration parameters */
    Csirx_createParamsInit(&appInstObj->createPrms);
    appInstObj->createPrms.numCh = APP_CAPT_CH_NUM;
    /* set channel configuration parameters */
    for (loopCnt = 0U ; loopCnt < appInstObj->createPrms.numCh ; loopCnt++)
    {
        appInstObj->chFrmCnt[loopCnt] = 0U;
        appInstObj->createPrms.chCfg[loopCnt].chId = loopCnt;
        appInstObj->createPrms.chCfg[loopCnt].chType = CSIRX_CH_TYPE_CAPT;
        appInstObj->createPrms.chCfg[loopCnt].vcNum = loopCnt;
        appInstObj->createPrms.chCfg[loopCnt].inCsiDataType = APP_CAPT_IMAGE_DT;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.width = APP_CAPT_FRAME_WIDTH;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.height = APP_CAPT_FRAME_HEIGHT;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.pitch[0U] =
                                                APP_CAPT_FRAME_PITCH;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.dataFormat =
                                                FVID2_DF_BGRX32_8888;
        appInstObj->createPrms.chCfg[loopCnt].outFmt.ccsFormat =
                                                APP_CAPT_IMAGE_STORAGE_FORMAT;
    }
    /* set module configuration parameters */
    appInstObj->createPrms.instCfg.enableCsiv2p0Support = (uint32_t)TRUE;
    appInstObj->createPrms.instCfg.numDataLanes = 4U;
    appInstObj->createPrms.instCfg.enableErrbypass = (uint32_t)FALSE;
    appInstObj->createPrms.instCfg.enableStrm[CSIRX_CAPT_STREAM_ID] = 1U;
    for (loopCnt = 0U ;
         loopCnt < appInstObj->createPrms.instCfg.numDataLanes ;
         loopCnt++)
    {
        appInstObj->createPrms.instCfg.dataLanesMap[loopCnt] = (loopCnt + 1U);
    }
    /* set frame drop buffer parameters */
    appInstObj->createPrms.frameDropBufLen =
                                (APP_CAPT_FRAME_WIDTH * APP_CAPT_FRAME_BPP);
    appInstObj->createPrms.frameDropBuf = (uint64_t)&gFrmDropBuf;
    /* This will be updated once Fvid2_create() is done */
    appInstObj->createStatus.retVal = FVID2_SOK;
    appInstObj->drvHandle = NULL;
    Fvid2CbParams_init(&appInstObj->cbPrms);
    appInstObj->cbPrms.cbFxn   = (Fvid2_CbFxn) &CsirxApp_frameCompletionCb;
    appInstObj->cbPrms.appData = appInstObj;

    appInstObj->numFramesRcvd = 0U;
    appInstObj->frameErrorCnt = 0U;
    appInstObj->maxWidth = APP_CAPT_FRAME_WIDTH;
    appInstObj->maxHeight = APP_CAPT_FRAME_HEIGHT;

    /* Initialize capture instance status */
    Csirx_instStatusInit(&appInstObj->captStatus);
}


static int32_t CsirxApp_init(CsirxApp_CaptCommonObj* appCommonObj)
{
    int32_t retVal = FVID2_SOK, dmaStatus = UDMA_SOK;
    uint32_t instId;
    Fvid2_InitPrms initPrms;
    Udma_InitPrms   udmaInitPrms;
    Udma_DrvHandle drvHandle;

    /* set instance initialization parameters */
    /* This will be updated once UDMA init is done */
    Csirx_initParamsInit(&appCommonObj->initPrms);
    drvHandle = &appCommonObj->udmaDrvObj;
    appCommonObj->initPrms.drvHandle = drvHandle;
    /* Fvid2 init */
    Fvid2InitPrms_init(&initPrms);
    initPrms.printFxn = &CsirxApp_fvidPrint;
    retVal = Fvid2_init(&initPrms);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Fvid2 Init Failed!!!\r\n");
    }

    /* Do UDMA init before CSIRX Init */
    /* UDMA driver init */
    instId = UDMA_INST_ID_BCDMA_1;
    UdmaInitPrms_init(instId, &udmaInitPrms);
    dmaStatus = Udma_init(drvHandle, &udmaInitPrms);
    if(UDMA_SOK != dmaStatus)
    {
        retVal = FVID2_EFAIL;
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": UDMA Init Failed!!!\r\n");
    }
    retVal = Csirx_init(&appCommonObj->initPrms);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }

    return (retVal);
}

static int32_t CsirxApp_recover(CsirxApp_CaptInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    Csirx_DPhyCfg dphyCfg;
    uint8_t i2cAddr = 0U, regAddr8, regVal;

    /* Fvid2_Stop */
    /* Stopped as part of the timer ISR, hence can be skipped here. */

    /* Soft Resetting Deserializer */
    Board_fpdUb9702GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);

    regAddr8 = UB9702_DESER_RESET_CTL_REG_ADDR;
    regVal = UB9702_DESER_RESET_VALUE;
    Board_i2c8BitRegWr(gI2cHandle, i2cAddr, regAddr8, &regVal, 1,
                                APP_I2C_TRANSACTION_TIMEOUT);

    /* Allocate, Queue available frames and Sensor Configuration */
    retVal += CsirxApp_allocAndQFrames(appInstObj);
    retVal += CsirxApp_sensorConfig(appInstObj);

    /* Reinitialize DPHY */
    Csirx_initDPhyCfg(&dphyCfg);
    dphyCfg.inst = appInstObj->instId;
    dphyCfg.leftLaneBandSpeed  = CSIRX_LANE_BAND_SPEED_2250_TO_2500_MBPS;
    dphyCfg.rightLaneBandSpeed = CSIRX_LANE_BAND_SPEED_2250_TO_2500_MBPS;
    retVal = Fvid2_control(appInstObj->drvHandle,
                            IOCTL_CSIRX_SET_DPHY_CONFIG,
                            &dphyCfg,
                            NULL);
    if(FVID2_SOK != retVal)
    {
        GT_1trace(CsirxAppTrace,
                    GT_ERR,
                    APP_NAME
                    " :Set D-PHY Configuration FAILED for CSIRX instance %d!!!\r\n",appInstObj->instId);
    }
    else
    {
        GT_1trace(CsirxAppTrace,
                    GT_INFO,
                    APP_NAME
                    " :Set D-PHY Configuration Successful for CSIRX instance %d!!!\r\n",appInstObj->instId);
    }

    /* Fvid2 Start */
    Fvid2_start(appInstObj->drvHandle, NULL);

    return (retVal);
}

static int32_t CsirxApp_create(CsirxApp_CaptInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    Csirx_DPhyCfg dphyCfg;
    Csirx_EventPrms eventPrms;

    /* Fvid2_create() */
    appInstObj->drvHandle = Fvid2_create(
        CSIRX_CAPT_DRV_ID,
        appInstObj->instId,
        &appInstObj->createPrms,
        &appInstObj->createStatus,
        &appInstObj->cbPrms);

    if ((NULL == appInstObj->drvHandle) ||
        (appInstObj->createStatus.retVal != FVID2_SOK))
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Capture Create Failed!!!\r\n");
        retVal = appInstObj->createStatus.retVal;
    }
    if (retVal == FVID2_SOK)
    {
        /* Set CSIRX D-PHY configuration parameters */
        Csirx_initDPhyCfg(&dphyCfg);
        dphyCfg.inst = appInstObj->instId;
        dphyCfg.leftLaneBandSpeed  = CSIRX_LANE_BAND_SPEED_2250_TO_2500_MBPS;
        dphyCfg.rightLaneBandSpeed = CSIRX_LANE_BAND_SPEED_2250_TO_2500_MBPS;
        retVal = Fvid2_control(appInstObj->drvHandle,
                                IOCTL_CSIRX_SET_DPHY_CONFIG,
                                &dphyCfg,
                                NULL);
        if(FVID2_SOK != retVal)
        {
            GT_1trace(CsirxAppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Set D-PHY Configuration FAILED for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
        else
        {
            GT_1trace(CsirxAppTrace,
                      GT_INFO,
                      APP_NAME
                      ":Set D-PHY Configuration Successful for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Register Error Events */
        Csirx_eventPrmsInit(&eventPrms);
        retVal = Fvid2_control(appInstObj->drvHandle,
                               IOCTL_CSIRX_REGISTER_EVENT,
                               &eventPrms,
                               NULL);
#if CSIRX_INFO_TEST
        eventPrms.eventGroup = CSIRX_EVENT_GROUP_INFO;
        eventPrms.eventMasks = CSIRX_EVENT_TYPE_INFO_ALL;

        retVal = Fvid2_control(appInstObj->drvHandle,
                               IOCTL_CSIRX_REGISTER_EVENT,
                               &eventPrms,
                               NULL);
#endif
        if(FVID2_SOK != retVal)
        {
            GT_1trace(CsirxAppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Error Events Registration FAILED for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
        else
        {
            GT_1trace(CsirxAppTrace,
                      GT_INFO,
                      APP_NAME
                      ":Error Events Registration Successful for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
    }
    if (FVID2_SOK == retVal)
    {
        GT_1trace(CsirxAppTrace,
                  GT_INFO,
                  APP_NAME ": CSIRX Capture created for CSIRX instance %d\r\n",appInstObj->instId);
    }
    /* Allocate and queue all available frames */
    retVal += CsirxApp_allocAndQFrames(appInstObj);
    /* Configure sensor here */
    retVal += CsirxApp_sensorConfig(appInstObj);
    return (retVal);
}

static int32_t CsirxApp_csiTest(CsirxApp_CaptCommonObj* appCommonObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t loopCnt;
    uint32_t elapsedTime, fps;
    uint64_t tempVar;

#if defined(FREERTOS)
    LoadP_reset();
    GT_0trace(CsirxAppTrace,
              GT_INFO,
              APP_NAME
              ":Before stream start\r\n");
    CsirxApp_printLoad();
#endif
    for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
    {
        if (FVID2_SOK == retVal)
        {
            retVal += Fvid2_start(appCommonObj->appInstObj[i].drvHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(CsirxAppTrace, GT_ERR,
                         APP_NAME " : Capture Start Failed for instance %d!!!\r\n",appCommonObj->appInstObj[i].instId);
            }
        }
    }
    /* start the tick timer */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
    SemaphoreP_pend(&gAppCompletionSem, SystemP_WAIT_FOREVER);
    /* Stop the streams immediately after the timeout is reached */
    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
    {
        retVal += Fvid2_stop(appCommonObj->appInstObj[i].drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(CsirxAppTrace, GT_ERR,
                      APP_NAME " : Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObj[i].instId);
        }
    }
#if defined(FREERTOS)
    GT_0trace(CsirxAppTrace,
              GT_INFO,
              APP_NAME
              ":After stream end\r\n");
    CsirxApp_printLoad();
#endif
    /* fps calculation and some x100 for precision */
    for(uint32_t i = 0U; i < APP_CAPT_TEST_INST_NUM; i++)
    {
        retVal += CsirxApp_captFreeFrames(&appCommonObj->appInstObj[i]);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(CsirxAppTrace, GT_ERR,
                      APP_NAME ": Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObj[i].instId);
        }
        elapsedTime = (APP_TEST_PERIOD_IN_SEC * 1000);
        tempVar = ((uint64_t)(appCommonObj->appInstObj[i].numFramesRcvd * 100000U)) / elapsedTime;
        fps = (uint32_t)tempVar;
        Csirx_instStatusInit(&appCommonObj->appInstObj[i].captStatus);
#if (1U == APP_PRINT_DRV_LOGS)
        /* print debug logs if enabled */
        retVal += Fvid2_control(appCommonObj->appInstObj[i].drvHandle,
                                IOCTL_CSIRX_PRINT_DEBUG_LOGS,
                                NULL,
                                NULL);
#endif

        retVal += Fvid2_control(appCommonObj->appInstObj[i].drvHandle,
                                IOCTL_CSIRX_GET_INST_STATUS,
                                &appCommonObj->appInstObj[i].captStatus,
                                NULL);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(CsirxAppTrace,
                      GT_INFO,
                      APP_NAME
                      ":Get Capture Status Failed!!!\r\n");
        }
        GT_0trace(CsirxAppTrace, GT_INFO,
            "\n\r==========================================================\r\n");
        GT_0trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Capture Status:\r\n");
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Capture instance:%d\r\n",appCommonObj->appInstObj[i].instId);
        GT_0trace(CsirxAppTrace, GT_INFO,
                  "==========================================================\r\n");
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Frames Received: %d\r\n",
                  appCommonObj->appInstObj[i].numFramesRcvd);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": De Skew Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.deSkewEntryCount);
        for(loopCnt = 0U ; loopCnt < APP_CAPT_CH_NUM ; loopCnt++)
        {
            GT_4trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ":[Channel No: %d] | Frame Queue Count: %d |"
                  " Frame De-queue Count: %d | Frame Drop Count: %d \r\n",
                  loopCnt,
                  appCommonObj->appInstObj[i].captStatus.queueCount[loopCnt],
                  appCommonObj->appInstObj[i].captStatus.dequeueCount[loopCnt],
                  appCommonObj->appInstObj[i].captStatus.dropCount[loopCnt]);
        }
#if (1U == APP_PRINT_DRV_LOGS)
        if (0U < appInstObj->frameErrorCnt)
        {
            GT_0trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Error Frames Info...\r\n");
            tempVar = appCommonObj->appInstObj[i].frameErrorCnt;
            if (appCommonObj->appInstObj[i].frameErrorCnt > APP_ERR_FRAME_LOG_MAX)
            {
                tempVar = APP_ERR_FRAME_LOG_MAX;
            }
            for (loopCnt = 0U ; loopCnt < tempVar ; loopCnt++)
            {
                GT_4trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ":[Frame No.: %d] | Channel Id: %d |"
                  " Ch Error Frame Number: %d | Time-stamp(ms): %d \r\n",
                  loopCnt,
                  appCommonObj->appInstObj[i].errFrmCh[loopCnt],
                  appCommonObj->appInstObj[i].errFrmNo[loopCnt],
                  appCommonObj->appInstObj[i].errFrmTs[loopCnt]);
            }

        }
#endif
        GT_4trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": %d frames captured in %d msec"
                  " at the rate of %d.%2d frames/sec.\r\n",
                  appCommonObj->appInstObj[i].numFramesRcvd,
                  elapsedTime,
                  (fps / 100U),
                  (fps % 100U));
    }
    return retVal;
}

static int32_t CsirxApp_delete(CsirxApp_CaptInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    /* Dequeue all the request from the driver */
    retVal = Fvid2_dequeue(
                    appInstObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);

    if ((FVID2_SOK != retVal) && (FVID2_ENO_MORE_BUFFERS != retVal))
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Capture De-queue Failed!!!\r\n");
    }
    if ((FVID2_SOK == retVal) || (FVID2_ENO_MORE_BUFFERS == retVal))
    {
        retVal = FVID2_SOK;
        /* Disable Error Events */
        retVal = Fvid2_control(appInstObj->drvHandle,
                               IOCTL_CSIRX_UNREGISTER_EVENT,
                               (void *)CSIRX_EVENT_GROUP_ERROR,
                               NULL);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(CsirxAppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Error Events un-registration FAILED!!!\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_delete(appInstObj->drvHandle, NULL);
    }
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": FVID2 Delete Failed!!!\r\n");
    }
    else
    {
        appInstObj->drvHandle = NULL;
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(CsirxAppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\r\n");
    }

    return (retVal);
}

static int32_t CsirxApp_deinit(CsirxApp_CaptCommonObj *appCommonObj)
{
    int32_t retVal = FVID2_SOK;
    Udma_DrvHandle drvHandle = &appCommonObj->udmaDrvObj;

    /* TODO: sensor config de-init if needed */
    retVal = Csirx_deInit();
    /* System de-init */
    if(UDMA_SOK != Udma_deinit(drvHandle))
    {
        retVal = FVID2_EFAIL;
        GT_0trace(CsirxAppTrace,
                  GT_ERR,
                  APP_NAME ": UDMA deinit failed!!!\r\n");
    }
    Fvid2_deInit(NULL);
    /* Close I2C channel */
    I2C_close(gI2cHandle);
    /* Delete semaphore */
    SemaphoreP_destruct(&gAppCompletionSem);
    /* Delete Timer */
    return (retVal);
}

static void CsirxApp_consolePrintf(const char *pcString, ...)
{
    char printBuffer[APP_PRINT_BUFFER_SIZE];
    va_list arguments;

    /* Start the var args processing. */
    va_start(arguments, pcString);
    vsnprintf (printBuffer, sizeof(printBuffer), pcString, arguments);
    printf("%s",printBuffer);
    /* End the var args processing. */
    va_end(arguments);
}

void CsirxApp_fvidPrint(const char *str, ...)
{
    CsirxApp_consolePrintf(str);

    return;
}

static void CsirxApp_dmaPrint(const char *str)
{
    CsirxApp_consolePrintf(str);

    return;
}

static int32_t CsirxApp_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmIdx = 0U, idx = 0U;
    static Fvid2_FrameList frmList;
    Fvid2_Frame *pFrm;
    CsirxApp_CaptInstObj *appInstObj = (CsirxApp_CaptInstObj *) appData;

    GT_assert(CsirxAppTrace, (NULL != appData));

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(
        appInstObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        appInstObj->numFramesRcvd += frmList.numFrames;
        for (frmIdx = 0U; frmIdx < frmList.numFrames; frmIdx++)
        {
            pFrm = frmList.frames[frmIdx];
            appInstObj->chFrmCnt[pFrm->chNum]++;
            if (FVID2_FRAME_STATUS_COMPLETED != pFrm->status)
            {
                idx = (appInstObj->frameErrorCnt % APP_ERR_FRAME_LOG_MAX);
                appInstObj->errFrmCh[idx] = pFrm->chNum;
                appInstObj->errFrmNo[idx] = appInstObj->chFrmCnt[pFrm->chNum];
                appInstObj->errFrmTs[idx] = (uint32_t)(pFrm->timeStamp64 / 1000U);
                appInstObj->frameErrorCnt++;
            }
        }

        /* Queue back de-queued frames,
           last param i.e. streamId is unused in DRV */
        retVal = Fvid2_queue(appInstObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(CsirxAppTrace, GT_ERR,
                      APP_NAME ": Capture Queue Failed!!!\r\n");
        }
    }

    /* always return 'FVID2_SOK' */

    return FVID2_SOK;
}

static int32_t CsirxApp_allocAndQFrames(CsirxApp_CaptInstObj *appInstObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx = 0U, frmIdx = 0U;
    static Fvid2_FrameList frmList;
    Fvid2_Frame  *pFrm;

    /* for every channel in a capture handle,
       allocate memory for and queue frames */
    Fvid2FrameList_init(&frmList);
    frmList.numFrames = 0U;
    for (chIdx = 0U; chIdx < appInstObj->createPrms.numCh ; chIdx++)
    {
        for (frmIdx = 0U; frmIdx < APP_CAPT_FRAMES_PER_CH ; frmIdx++)
        {
            /* assign frames memory */
            /* Only following fields are used in CSIRX DRV */
            pFrm = (Fvid2_Frame *)
                    &appInstObj->frames[(chIdx * APP_CAPT_FRAMES_PER_CH) + frmIdx];
            pFrm->addr[0U] =
               (uint64_t)&gFrms[appInstObj->instId][(chIdx * APP_CAPT_FRAMES_PER_CH) + frmIdx][0U];
            pFrm->chNum = appInstObj->createPrms.chCfg[chIdx].chId;
            pFrm->appData = appInstObj;
            frmList.frames[frmList.numFrames] = pFrm;
            frmList.numFrames++;
        }
    }
    /* queue the frames in frmList
     * All allocated frames are queued here as an example.
     * In general at least 2 frames per stream/channel need to queued
     * before capture can be started.
     * Failing which, frame could be dropped.
     */
    /* last parameter, i.e. streamId is unused in CSIRX DRV */
    retVal = Fvid2_queue(appInstObj->drvHandle, &frmList, 0U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": Capture Queue Failed!!!\r\n");
    }

    return retVal;
}

static int32_t CsirxApp_captFreeFrames(CsirxApp_CaptInstObj *appInstObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);

    /* Deq-queue any frames queued more than needed */
    retVal = Fvid2_dequeue(
                    appInstObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);
    if (FVID2_ENO_MORE_BUFFERS == retVal)
    {
        /* All buffer might be de-queued during stop,
           in this case no error shall be returned */
        retVal = FVID2_SOK;
    }
    /* TODO: Free up frame allocated memories here */
    /* it is global variable here so not needed */

    return (retVal);
}

static int32_t CsirxApp_sensorConfig(CsirxApp_CaptInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t timeOut = 0;
    int32_t status = FVID2_SOK;
    uint32_t cnt;
#if !UB960_USE_PATTERN_GENERATOR
    uint32_t sensorIdx;
    uint16_t regAddr;
    uint8_t i2cswitchreg;
#else
    uint8_t i2cswitchreg;
#endif
    uint8_t i2cInst = 0U, i2cAddr = 0U, regAddr8, regVal;

    uint32_t *ub953I2cAddr, portNum=0;
    uint32_t *sensorI2cAddr;
    uint16_t deSerConfig[500][3] = {};

    /*
     * SOC GPIO0_68 CSI2_EXP_RSTz is muxed to Padconfig Package MMC2_DAT0
     * Muxmode = 7 configures MMC2_DAT0 as GPIO_68
     */
    Pinmux_config(gMainPinmuxData, PINMUX_DOMAIN_ID_MAIN);

    /*
     * Set SOC GPIO0_68 CSI2_EXP_RSTz CSI2 Expansion Interface Reset as output
     * and write high for normal operation
     */
    GPIO_setDirMode(CSL_GPIO0_BASE, CONFIG_GPIO0_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_pinWriteHigh(CSL_GPIO0_BASE, CONFIG_GPIO0_PIN);

    /*
     * 24bit I2C GPIO EXP1 TCA6424ARGJR (SLV ADDR 0x23) is connected to I2C0
     * which needs to be programmed to use CSI fusion expansion boards connected
     * to Main I2C2 instance bus.
     */
    status = Board_enableCSII2c(BOARD_CSI_I2C_MUX_INSTANCE);
    if (FVID2_SOK == status)
    {
        gI2cHandle = I2C_getHandle(BOARD_CSI_I2C_SWITCH_INSTANCE);
        /*
         * CSI2_A Expansion Connector is connected to channel 0 of 2-Channel
         * I2C Bus Switch TCA9543APWR (Switch 1). A value of 0x01 needs to
         * be programmed to enable Channel 0. The address of TCA9543APWR is
         * 0x70 on J7AEN (defined by hardware).
         */
        i2cswitchreg = 0x01;
        status = Board_i2c8BitRegWrSingle(gI2cHandle, I2C_SWITCH_TCA9543APWR_SLV_ADDR, &i2cswitchreg, APP_I2C_TRANSACTION_TIMEOUT);
    }

    /* Check for the Fusion2 board */
    uint8_t bDet = BFALSE;
    bDet = Board_detectBoard(BOARD_ID_FUSION2, BOARD_CSI_I2C_SWITCH_INSTANCE);
    if (BTRUE == bDet)
    {
        gFusion2Det = BTRUE;
    }

    if (FVID2_SOK == status)
    {
        if (gFusion2Det == BTRUE)
        {
            Board_fpdUb9702GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
            memcpy(deSerConfig, gUb9702SensorCfg, (sizeof(gUb9702SensorCfg)));
        } else {
            Board_fpdUb960GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
            memcpy(deSerConfig, gUb960SensorCfg, (sizeof(gUb960SensorCfg)));
        }
    }

    if(appInstObj->instId == CSIRX_INSTANCE_ID_0)
    {
        ub953I2cAddr = gUb953I2CAddrInst0;
        sensorI2cAddr = gSensorI2CAddrInst0;
    }
    else if(appInstObj->instId == CSIRX_INSTANCE_ID_1)
    {
        ub953I2cAddr = gUb953I2CAddrInst1;
        sensorI2cAddr = gSensorI2CAddrInst1;
    }

    if ((i2cInst == 0U) && (i2cAddr == 0U))
    {
        retVal = FVID2_EFAIL;
    }
    else
    {
        for (cnt = 0U;
             cnt < sizeof(deSerConfig)/(sizeof(deSerConfig[0]));
             cnt ++)
        {
            regAddr8 =deSerConfig[cnt][0] & 0xFF;

            if(D3IMX390_INST2_PORT_3_SENSOR_ADDR == regAddr8)
            {
                if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_CM_MODULE) << 1) & 0xFF ;
                }
                else if (D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_RCM_MODULE) << 1) & 0xFF ;
                }
            }
            else if(0x65 == regAddr8)
            {
                regVal = ((ub953I2cAddr[portNum]) << 1) & 0xFF ;
            }
            else if(0x66 == regAddr8)
            {
                regVal = ((sensorI2cAddr[portNum]) << 1) & 0xFF ;
                portNum++;
            }
            else
            {
                regVal = deSerConfig[cnt][1] & 0xFF;
            }

            timeOut = deSerConfig[cnt][2];
            status = Board_i2c8BitRegWr(gI2cHandle, i2cAddr, regAddr8, &regVal, 1,
                                        APP_I2C_TRANSACTION_TIMEOUT);
            if (0U != status)
            {
                GT_3trace(CsirxAppTrace,
                        GT_INFO,
                        APP_NAME ": Failed to Set de-serializer register %x: Value:%x\n instance %d\n",
                        deSerConfig[cnt][0],
                        deSerConfig[cnt][1],
                        appInstObj->instId);
                break;
            }
            else
            {
                App_wait(timeOut);
            }
        }

#if !UB960_USE_PATTERN_GENERATOR
        for (sensorIdx = 0U ; sensorIdx < APP_CAPT_CH_NUM ; sensorIdx++)
        {
            if (0U == status)
            {
                /* UB953 serializer Port configuration */
                i2cAddr = ub953I2cAddr[sensorIdx];
                for (cnt = 0U;
                     cnt < sizeof(gUb953SensorCfg)/(sizeof(gUb953SensorCfg[0]));
                     cnt ++)
                {
                    regAddr8 = gUb953SensorCfg[cnt][0] & 0xFF;
                    if(0x07 == regAddr8)
                    {
                        if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal = 0x28;
                            timeOut = 0x1F;
                        }
                        else if(D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal =  0x25;
                            timeOut = 0x80;
                        }
                    }
                    else if(0x0D == regAddr8)
                    {
                        if(D3IMX390_CM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal =  0x01;
                            timeOut = 0x10;
                        }
                        else if (D3IMX390_RCM_MODULE == appInstObj->cameraSensor)
                        {
                            regVal =  0x03;
                            timeOut = 0x10;
                        }
                    }
                    else
                    {
                        regVal = gUb953SensorCfg[cnt][1] & 0xFF;
                        timeOut = gUb953SensorCfg[cnt][2];
                    }
                    status = Board_i2c8BitRegWr(gI2cHandle,
                                                i2cAddr,
                                                regAddr8,
                                                &regVal,
                                                1,
                                                APP_I2C_TRANSACTION_TIMEOUT);

                    if (0 != status)
                    {
                        GT_3trace(CsirxAppTrace, GT_INFO,
                                APP_NAME
                                ": Failed to Set UB953 register %x: Value:%x for CSIRX instance %d\n",
                                gUb953SensorCfg[cnt][0],
                                gUb953SensorCfg[cnt][1],
                                appInstObj->instId);
                        break;
                    }
                    else
                    {
                        App_wait(timeOut);
                    }
                }
             }
             else
             {
                 break;
             }
        }

        if (0 == status)
        {
            GT_1trace(CsirxAppTrace, GT_INFO,
                      APP_NAME ": Configuring IMX390 Sensor for CSIRX instance %d\r\n",appInstObj->instId);
        }
        for (sensorIdx = 0U ; sensorIdx < APP_CAPT_CH_NUM ; sensorIdx++)
        {
            if (0 == status)
            {
                /* Sensor 0 configuration */
                i2cAddr = sensorI2cAddr[sensorIdx];
                for (cnt = 0; cnt < SENSOR_CFG_SIZE; cnt ++)
                {
                    regAddr = gSensorCfg[cnt][0];
                    regVal = gSensorCfg[cnt][1];

                    status = Board_i2c16BitRegWr(gI2cHandle,
                                                i2cAddr,
                                                regAddr,
                                                &regVal,
                                                1,
                                                0,
                                                APP_I2C_TRANSACTION_TIMEOUT);
                    if (0 != status)
                    {
                        GT_4trace(CsirxAppTrace, GT_INFO,
                                APP_NAME
                                ": Failed to Set Sensor%x register %x: Value:0x%x for CSIRX instance %d\n",
                                sensorIdx,
                                regAddr,
                                regVal,
                                appInstObj->instId);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
#endif
        if (0 == status)
        {
            if(BTRUE == gFusion2Det)
            {
                Board_fpdUb9702GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
            }
            else
            {
                Board_fpdUb960GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
            }

            if(BTRUE != gFusion2Det)
            {
                if (CSIRX_INSTANCE_ID_1 == appInstObj->instId)
                {
                    i2cAddr = 0x36U;
                }
            }
            regAddr8 = 0x33;
            regVal = 0x3;
            status = Board_i2c8BitRegWr(gI2cHandle,
                                        i2cAddr,
                                        regAddr8,
                                        &regVal,
                                        1,
                                        APP_I2C_TRANSACTION_TIMEOUT);

            if (0 != status)
            {
                GT_1trace(CsirxAppTrace, GT_INFO,
                        APP_NAME ": Failed to enable CSI port for CSIRX instance %d\n", appInstObj->instId);
            }
            if (0U != retVal)
            {
                GT_1trace(CsirxAppTrace, GT_INFO,
                        APP_NAME ": ERROR in Sensor Configuration for CSIRX instace %d!!!\r\n",appInstObj->instId);
            }
            else
            {
                GT_1trace(CsirxAppTrace, GT_INFO,
                         APP_NAME ": Sensor Configuration done for CSIRX instance %d!!!\r\n",appInstObj->instId);
            }
        }
        else
        {
            GT_1trace(CsirxAppTrace, GT_INFO,
                    APP_NAME ": Sensor Configuration Failed for CSIRX instance %d!!!\r\n",appInstObj->instId);
        }
    }

    return (retVal);
}


#if defined(FREERTOS)
void CsirxApp_printLoad(void)
{
    LoadP_Stats loadStatsTask;
    uint32_t cpuLoad;

    /* Query CPU Load */
    cpuLoad = LoadP_getCPULoad();
    GT_1trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": CPU Load is:%d percent\r\n", cpuLoad);
    /* Get task loads */
    LoadP_getTaskLoad(gCsirxAppTask, &loadStatsTask);
    if(loadStatsTask.percentLoad > 0U)
    {
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Task Load is: %d percent\r\n", loadStatsTask.percentLoad);
    }
    else
    {
        GT_0trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Task Load is: < 1 percent \n");
    }
}
#endif
