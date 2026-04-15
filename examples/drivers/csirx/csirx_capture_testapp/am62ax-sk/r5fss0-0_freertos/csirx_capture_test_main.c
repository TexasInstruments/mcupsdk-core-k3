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
 *  \file csirx_fusion2_test_main.c
 *
 *  \brief CSI RX Fusion 2 Example.
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
#include <kernel/dpl/CacheP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <board/ioexp/ioexp_tca6424.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< Application name */
#define APP_NAME                                  "CSIRX_F2_APP"
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

/**
 * @{
 * Macros to control Fusion board and Camera Sensor version for the capture
 */
/**< Fusion Board Revision.
     '0': for Rev B or older boards.
     '1': for Rev C board. */
/**< D3 IMX390 sensor type. */
#define D3IMX390_CM_MODULE                     (0U)
#define D3IMX390_RCM_MODULE                    (1U)

#define APP_CSIRX_INST0_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)
#define APP_CSIRX_INST1_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)

/**< Frame Attribute: Pitch in bytes */
#define APP_CAPT_FRAME_PITCH                      ((uint32_t)\
                                (APP_CAPT_FRAME_WIDTH * APP_CAPT_FRAME_BPP))
/**< Frame Attribute: size in bytes */
#define APP_CAPT_FRAME_SIZE                                ((uint32_t)\
            (APP_CAPT_FRAME_HEIGHT * APP_CAPT_FRAME_WIDTH * APP_CAPT_FRAME_BPP))

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

#define SENSOR_CFG_SIZE  (3078U)

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

/**< Number of channels */
#define APP_CAPT_CH_MAX                           ((uint32_t)4U)

#define CSIRX_APP_TAKE_I2CDUMP              (0U)
#define CSIRX_APP_TAKE_IMGDUMP              (0U)

TCA6424_Params TCA6424_IOexp_params =
{
    .i2cInstance = CONFIG_I2C1,
    .i2cAddress =  0x23
};

/* ========================================================================== */
/*                    Register Dump Storage                                   */
/* ========================================================================== */

/* UB9702 deserializer register dump: 0x00-0xFF (256 bytes) */
static uint8_t gUb9702RegDump[256];

/* UB971 serializer register dump: 0x00-0xF5 (246 bytes) */
static uint8_t gUb971RegDump[246];

/* IMX390 sensor register dump: 0x0000-0x545C (21597 bytes) */
static uint8_t gImx390RegDump[21597];

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

/**
 * \brief   Dump UB9702 deserializer registers 0x00-0xFF
 *
 * \param   i2cHandle   I2C handle to use
 * \param   i2cAddr     I2C address of UB9702 (typically 0x3D)
 *
 * \retval  None.
 */
static void CsirxApp_dumpUb9702Registers(I2C_Handle i2cHandle, uint8_t i2cAddr);

/**
 * \brief   Dump UB971 serializer registers 0x00-0xF5
 *
 * \param   i2cHandle   I2C handle to use
 * \param   i2cAddr     I2C address of UB971 (typically 0x18)
 *
 * \retval  None.
 */
static void CsirxApp_dumpUb971Registers(I2C_Handle i2cHandle, uint8_t i2cAddr);

/**
 * \brief   Dump IMX390 sensor registers 0x0000-0x545C
 *
 * \param   i2cHandle   I2C handle to use
 * \param   i2cAddr     I2C address of IMX390 (typically 0x40)
 *
 * \retval  None.
 */
static void CsirxApp_dumpImx390Registers(I2C_Handle i2cHandle, uint8_t i2cAddr);

/**
 * \brief   Dump all device registers (UB9702, UB971, IMX390)
 *
 * \param   i2cHandle       I2C handle to use
 * \param   isFusion2       BTRUE if Fusion2 board detected, BFALSE otherwise
 * \param   ub9702Addr      I2C address of UB9702 deserializer
 * \param   ub971Addr       I2C address of UB971 serializer
 * \param   imx390Addr      I2C address of IMX390 sensor
 *
 * \retval  None.
 */
static void CsirxApp_dumpAllRegisters(I2C_Handle i2cHandle,
                                      bool isFusion2,
                                      uint8_t ub9702Addr,
                                      uint8_t ub971Addr,
                                      uint8_t imx390Addr);

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

volatile int gFrmCbCnt = 0;

/* App common object */
CsirxApp_CaptCommonObj gAppCommonObj;

/* CSIRX instances to use in application */
uint32_t  gAppCapInst[APP_TOTAL_CAPT_INST] = {CSIRX_INSTANCE_ID_0};

/* Memory buffer to hold data */
static uint8_t gFrmDropBuf[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAME_PITCH)] __attribute__(( aligned(128), section(".data_buffer")));
static uint8_t gFrms[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAMES_PER_CH * APP_CAPT_CH_NUM)][APP_CAPT_FRAME_SIZE]__attribute__(( aligned(128), section(".data_buffer")));

/* Semaphore to indicate app completion */
SemaphoreP_Object gAppCompletionSem;

/* I2c Handle to access deserializer */

/* Fusion2 board detect flag */
bool gFusion2Det = BFALSE;

#if defined(FREERTOS)
/* Capture test Task handle */
extern TaskP_Handle gCsirxAppTask;
#endif
extern uint32_t gTimerBaseAddr[TIMER_NUM_INSTANCES];

uint16_t gSensorCfg[SENSOR_CFG_SIZE][3] = IMX390_LINEAR_1920X1080_CONFIG;

uint16_t gUb9702SensorCfg[][3] = {
    {0x3C, 0x3F, 0x10}, /* Disable lock lost feature */ //!

    /*Sets GPIOS*/
    {0x10, 0x00, 0x1},
    {0x11, 0x00, 0x1},
    {0x12, 0x00, 0x1},
    {0x13, 0x00, 0x1},

    {0xB0, 0x1C, 0x20},
    {0xB1, 0x92, 0x20},
    {0xB2, 0x80, 0x20},
    {0xB1, 0x4B, 0x20},
    {0xB2, 0x2A, 0x20},

    /*Port 0 Config*/
    {0xB0, 0x04, 0x20},
    {0xB1, 0xA8, 0x20},
    {0xB2, 0x80, 0x20},
    {0xB1, 0x0D, 0x20},
    {0xB2, 0x7F, 0x20},
    {0xB1, 0x2B, 0x20},
    {0xB2, 0x04, 0x20},
    {0xB1, 0xA9, 0x20},
    {0xB2, 0x23, 0x20},
    {0xB1, 0xAA, 0x20},
    {0xB2, 0x00, 0x20},
    {0xB1, 0x1B, 0x20},
    {0xB2, 0x48, 0x20},

    {0x4C, 0x01, 0x20},
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0xE4, 0x02, 0x10}, /* Set FPD functional mode to FPD3 Async CSI Mode */
    {0x58, 0x5E, 0x10}, /* BC_FREQ_SELECT=(PLL_FREQ/3200) Mbps */

    {0x0C, 0x01, 0x20}, /* Enable RX ports */   //!
    {0x01, 0x21, 0x20}, /* Soft Reset and Release GPIO Hold */


    /*Port 0 Config*/
    {0x4C, 0x01, 0x20},
    {0xD4, 0x00, 0x20}, /* Release State Machine in reset */
    {0xD4, 0x10, 0x20}, /* Hold State Machine in reset */
    {0x01, 0x21, 0x20}, /* Soft reset and release GPIO hold */
    {0xD4, 0x00, 0x20}, /* Release SM in reset */
    {0x32, 0x01, 0x20}, /* Enable TX ports */ //!
    {0x33, 0x42, 0x1}, /*Enable Continuous clock mode and CSI output*/
    {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_INST0_PORT_0_SER_ADDR << 1U), 0x1},
    {0x5E, (D3IMX390_SENSOR_ADDR_RCM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_INST0_PORT_0_SENSOR_ADDR << 1U), 0x1},
    {0x6D, 0x78,0x0}, /*CSI Mode*/ //!

    {0xA0, 0x10, 0x0}, /*VC Map */
    {0x01, 0x01, 0x50},
    {0x32, 0x01, 0x20},

    /*  2500mbps   */
    {0x1F, 0x00, 0x20},
    {0xC9, 0x10, 0x20},
    {0x20, 0xE0, 0x20},
    {0xC7, 0x00, 0x20},
    {0x3B, 0xFF, 0x20},

    /* Additional config */
    {0xC2, 0X01, 0X20},
    {0xD8, 0X07, 0X20},
    {0xD9, 0X7F, 0X20},
    {0xa0, 0x00, 0x20},
    {0xa1, 0x00, 0x20},
    {0xa2, 0x00, 0x20},
    {0xa3, 0x00, 0x20},
    {0xa4, 0x00, 0x20},
    {0xa5, 0x00, 0x20},
    {0xa6, 0x00, 0x20},
    {0xa7, 0x00, 0x20},
    {0x33, 0x43, 0x20},
};

uint16_t gUb953SensorCfg[][3] = {
    {0x01, 0x01, 0x80},
    {0x02, 0x72, 0x10},
    {0x06, 0x41, 0x1F},
    {0x07, 0x23, 0x1F},
    {0x0D, 0x02, 0x10},
    {0x0E, 0x2D, 0x10},
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

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int Csirx_fusion2Test(void)
{
    int retVal = FVID2_SOK;
    CsirxApp_CaptInstObj *appInstObj[APP_CAPT_TEST_INST_NUM];
    CsirxApp_CaptCommonObj *appCommonObj;
    appCommonObj = &gAppCommonObj;

    /* Creating semaphore to indicate application completion of each Instance */
    SemaphoreP_constructBinary(&gAppCompletionSem,0U);

    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
    {
        appInstObj[i] = &appCommonObj->appInstObj[i];
        memset(appInstObj[i], 0x0, sizeof (CsirxApp_CaptInstObj));
    }
    /* Initialize application object for current capture context */
    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
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
        for(int i=0; i< APP_CAPT_TEST_INST_NUM; i++)
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
    retVal += CsirxApp_csiTest(appCommonObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(CsirxAppTrace, GT_ERR,
              APP_NAME ": [ERROR]CsirxApp_csiTest() FAILED!!!\r\n");
    }

    /* App CSI delete function */
    if (FVID2_SOK == retVal)
    {
        for(int i=0; i< APP_CAPT_TEST_INST_NUM; i++)
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
    static volatile uint32_t timerIsrCount=0;
    timerIsrCount++;
    if (timerIsrCount == APP_TEST_PERIOD_IN_SEC)
    {
        TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);
        timerIsrCount = 0;
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
    appInstObj->createPrms.instCfg.enableCsiv2p0Support = (uint32_t)FALSE;
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
    if (retVal == FVID2_SOK)
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
    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
    {
        if (retVal == FVID2_SOK)
        {
            retVal += Fvid2_start(appCommonObj->appInstObj[i].drvHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(CsirxAppTrace, GT_ERR,
                         APP_NAME ": Capture Start Failed for instance %d!!!\r\n",appCommonObj->appInstObj[i].instId);
            }
        }
    }
    /* Enable this macro to dump all device registers after configuration */
#if (CSIRX_APP_TAKE_I2CDUMP)
    CsirxApp_dumpAllRegisters(gI2cHandle[CONFIG_I2C2],
                              gFusion2Det,
                              0x3D,  /* UB9702 address */
                              D3IMX390_INST0_PORT_0_SER_ADDR,  /* UB971 address */
                              D3IMX390_INST0_PORT_0_SENSOR_ADDR);  /* IMX390 address */
#endif
    /* start the tick timer */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
    SemaphoreP_pend(&gAppCompletionSem, SystemP_WAIT_FOREVER);
    DebugP_log("Finished capturing! \r\n");
    /* Enable this macro to visualize the camera capture - access gFrms and take its dump after the console log */
#if (CSIRX_APP_TAKE_IMGDUMP)
    volatile int a = 1;
    while(a);
#endif
    /* Stop the streams immediately after the timeout is reached */
    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
    {
        retVal += Fvid2_stop(appCommonObj->appInstObj[i].drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(CsirxAppTrace, GT_ERR,
                      APP_NAME ": Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObj[i].instId);
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
    for(int i=0; i<APP_CAPT_TEST_INST_NUM; i++)
    {
        retVal += CsirxApp_captFreeFrames(&appCommonObj->appInstObj[i]);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(CsirxAppTrace, GT_ERR,
                      APP_NAME ": Capture Stop Failed for instance %d!!!\r\n", appCommonObj->appInstObj[i].instId);
        }
        elapsedTime = (APP_TEST_PERIOD_IN_SEC * 1000);
        tempVar = ((uint64_t)(appCommonObj->appInstObj[i].numFramesRcvd * 100000U)) / elapsedTime;
        fps = (uint32_t)tempVar;
        
        Csirx_instStatusInit(&appCommonObj->appInstObj[i].captStatus);
#if (APP_PRINT_DRV_LOGS == 1U)
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
        DebugP_log("Number of times Frame Completion callback triggered: %d\r\n", gFrmCbCnt);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Frames Received: %d\r\n",
                  appCommonObj->appInstObj[i].numFramesRcvd);

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
#if (APP_PRINT_DRV_LOGS == 1U)
        if (appCommonObj->appInstObj[i].frameErrorCnt > 0U)
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
    if (retVal == FVID2_SOK)
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
    Drivers_i2cClose();
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

    GT_assert(CsirxAppTrace, (appData != NULL));

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(
        appInstObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        appInstObj->numFramesRcvd += frmList.numFrames;
        for (frmIdx = 0; frmIdx < frmList.numFrames; frmIdx++)
        {
            pFrm = frmList.frames[frmIdx];

            /* Invalidate cache after DMA transfer */
            CacheP_inv((void *)pFrm->addr[0U], APP_CAPT_FRAME_SIZE, CacheP_TYPE_ALLD);

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

    gFrmCbCnt++;

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
    if (retVal == FVID2_ENO_MORE_BUFFERS)
    {
        /* All buffer might be de-queued during stop,
           in this case no error shall be returned */
        retVal = FVID2_SOK;
    }
    /* TODO: Free up frame allocated memories here */
    /* it is global variable here so not needed */

    return (retVal);
}

static void CsirxApp_dumpUb9702Registers(I2C_Handle i2cHandle, uint8_t i2cAddr)
{
    int32_t status;
    uint16_t regAddr;

    DebugP_log("\n=== UB9702 Register Dump (0x%02X) ===\r\n", i2cAddr);
    DebugP_log("Dumping registers 0x00-0xFF (256 bytes)...\r\n");

    for (regAddr = 0x00; regAddr <= 0xFF; regAddr++)
    {
        status = Board_i2c8BitRegRd(i2cHandle, i2cAddr,
                                    (uint8_t)regAddr, &gUb9702RegDump[regAddr], 1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("WARNING: Failed to read UB9702 register 0x%02X\r\n", regAddr);
            gUb9702RegDump[regAddr] = 0xFF;  /* Mark as invalid */
        }
    }

    DebugP_log("UB9702 register dump complete\r\n");
}

static void CsirxApp_dumpUb971Registers(I2C_Handle i2cHandle, uint8_t i2cAddr)
{
    int32_t status;
    uint16_t regAddr;

    DebugP_log("\n=== UB971 Register Dump (0x%02X) ===\r\n", i2cAddr);
    DebugP_log("Dumping registers 0x00-0xF5 (246 bytes)...\r\n");

    for (regAddr = 0x00; regAddr <= 0xF5; regAddr++)
    {
        status = Board_i2c8BitRegRd(i2cHandle, i2cAddr,
                                    (uint8_t)regAddr, &gUb971RegDump[regAddr], 1,
                                    APP_I2C_TRANSACTION_TIMEOUT);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("WARNING: Failed to read UB971 register 0x%02X\r\n", regAddr);
            gUb971RegDump[regAddr] = 0xFF;  /* Mark as invalid */
        }
    }

    DebugP_log("UB971 register dump complete\r\n");
}

static void CsirxApp_dumpImx390Registers(I2C_Handle i2cHandle, uint8_t i2cAddr)
{
    int32_t status;
    uint32_t regAddr;
    uint8_t addrBuf[2];
    uint8_t dataBuf[2];
    uint32_t dumpIdx = 0;
    I2C_Transaction i2cTransaction;

    DebugP_log("\n=== IMX390 Register Dump (0x%02X) ===\r\n", i2cAddr);
    DebugP_log("Dumping registers 0x0000-0x545C (21597 bytes)...\r\n");
    DebugP_log("WARNING: This will take several seconds...\r\n");

    for (regAddr = 0x0000; regAddr <= 0x545C; regAddr += 2)
    {
        addrBuf[0] = (regAddr >> 8) & 0xFF;  /* High byte */
        addrBuf[1] = regAddr & 0xFF;         /* Low byte */

        /* Write register address (16-bit) - this sets the internal pointer */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.targetAddress = i2cAddr;
        i2cTransaction.writeBuf = addrBuf;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (status == SystemP_SUCCESS)
        {
            /* Read back 2 bytes of data */
            I2C_Transaction_init(&i2cTransaction);
            i2cTransaction.targetAddress = i2cAddr;
            i2cTransaction.writeBuf = NULL;
            i2cTransaction.writeCount = 0;
            i2cTransaction.readBuf = dataBuf;
            i2cTransaction.readCount = 2;
            status = I2C_transfer(i2cHandle, &i2cTransaction);

            if (status == SystemP_SUCCESS)
            {
                gImx390RegDump[dumpIdx++] = dataBuf[0];
                gImx390RegDump[dumpIdx++] = dataBuf[1];
            }
            else
            {
                gImx390RegDump[dumpIdx++] = 0xFF;
                gImx390RegDump[dumpIdx++] = 0xFF;
            }
        }
        else
        {
            gImx390RegDump[dumpIdx++] = 0xFF;
            gImx390RegDump[dumpIdx++] = 0xFF;
        }

        /* Progress indicator every 1000 bytes */
        if ((dumpIdx % 1000) == 0)
        {
            DebugP_log("  Progress: %d/%d bytes\r\n", dumpIdx, 21597);
        }
    }

    DebugP_log("IMX390 register dump complete\r\n");
}

static void CsirxApp_dumpAllRegisters(I2C_Handle i2cHandle,
                                      bool isFusion2,
                                      uint8_t ub9702Addr,
                                      uint8_t ub971Addr,
                                      uint8_t imx390Addr)
{
    DebugP_log("\n========== POST-CONFIGURATION REGISTER DUMPS ==========\r\n");

    if (isFusion2)
    {
        /* Dump UB9702 deserializer registers */
        CsirxApp_dumpUb9702Registers(i2cHandle, ub9702Addr);

        /* Dump UB971 serializer registers */
        CsirxApp_dumpUb971Registers(i2cHandle, ub971Addr);
    }

    /* Dump IMX390 sensor registers */
    CsirxApp_dumpImx390Registers(i2cHandle, imx390Addr);

    DebugP_log("========== REGISTER DUMPS COMPLETE ==========\r\n\n");
}

static uint8_t ub953_probe()
{
    uint8_t ret = 0;
    uint32_t status;
    DebugP_log("Now probing for ub953\r\n");
    for (uint8_t adr = D3IMX390_INST0_PORT_0_SER_ADDR - 10; adr<=D3IMX390_INST0_PORT_0_SER_ADDR + 10; adr++)
    {
        status = I2C_probe(gI2cHandle[CONFIG_I2C2], adr);
        if (status == SystemP_SUCCESS)
        {
            DebugP_log("Found ub953 at 0x%02X\r\n", adr);
            ret = adr;
        }
    }
    return ret;
}

static uint8_t imx390_probe()
{
    uint8_t ret = D3IMX390_INST0_PORT_0_SENSOR_ADDR;
    uint32_t status;
    DebugP_log("Now probing for imx390\r\n");
    for (uint8_t adr = D3IMX390_INST0_PORT_0_SENSOR_ADDR-10; adr<=D3IMX390_INST0_PORT_0_SENSOR_ADDR+10; adr++)
    {
        status = I2C_probe(gI2cHandle[CONFIG_I2C2], adr);
        if (status == SystemP_SUCCESS)
        {
            DebugP_log("Found imx390 at 0x%02X\r\n", adr);
            ret = adr;
        }
    }
    return ret;
}

static int32_t CsirxApp_sensorConfig(CsirxApp_CaptInstObj* appInstObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t timeOut = 0;
    int32_t status = FVID2_SOK;
    uint32_t cnt;
    uint32_t sensorIdx;
    uint16_t regAddr;
    uint8_t i2cInst = 0U, i2cAddr = 0U, regAddr8, regVal;

    uint32_t *ub953I2cAddr, portNum=0;
    uint32_t *sensorI2cAddr = NULL;
    static uint16_t deSerConfig[500][3] = {};

    TCA6424_Config TCA6424_IOexp_config;

    retVal |= TCA6424_open(&TCA6424_IOexp_config, &TCA6424_IOexp_params);

    retVal |= TCA6424_config(&TCA6424_IOexp_config, 20, TCA6424_MODE_OUTPUT);

    retVal |= TCA6424_setOutput(&TCA6424_IOexp_config, 20, TCA6424_OUT_STATE_HIGH);

    if (retVal == SystemP_SUCCESS)
    {
        DebugP_log("Pin 20 (CSI_EN) set HIGH\r\n");
    }
    else
    {
        DebugP_log("ERROR: Pin 20 (CSI_EN) configuration FAILED (status=%d)\r\n", retVal);
    }

    ClockP_usleep(50000);

    retVal |= TCA6424_config(&TCA6424_IOexp_config, 9, TCA6424_MODE_OUTPUT);

    retVal |= TCA6424_setOutput(&TCA6424_IOexp_config, 9, TCA6424_OUT_STATE_HIGH);

    if (retVal == SystemP_SUCCESS)
    {
        DebugP_log("Pin 9 (CSI_RSTz) set HIGH\r\n");
    }
    else
    {
        DebugP_log("ERROR: Pin 9 (CSI_RSTz) configuration FAILED (status=%d)\r\n", retVal);
    }

    retVal |= TCA6424_config(&TCA6424_IOexp_config, 19, TCA6424_MODE_OUTPUT);

    retVal |= TCA6424_setOutput(&TCA6424_IOexp_config, 19, TCA6424_OUT_STATE_LOW);

    if (retVal == SystemP_SUCCESS)
    {
        DebugP_log("Pin 19 (CSI_SEL2) set LOW\r\n");
    }
    else
    {
        DebugP_log("ERROR: Pin 19 (CSI_SEL2) configuration FAILED (status=%d)\r\n", retVal);
    }

    if (retVal == SystemP_SUCCESS)
    {
        DebugP_log("TCA6424@0x23 Pin 9 (CSI_RSTz) set HIGH - releasing reset\r\n");
        DebugP_log("Waiting 200ms for UB9702 power-up and I2C to become ready...\r\n");
        ClockP_usleep(200000);  // Wait 200ms after reset release
    }
    else
    {
        DebugP_log("ERROR: TCA6424@0x23 configuration FAILED (status=%d)\r\n", retVal);
    }

    if (FVID2_SOK == status)
    {
        DebugP_log("Success in Board_enableCSII2c in line 1829\r\n");
        uint8_t switchConfig = 0x02;
        I2C_Transaction i2cTransaction;

        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.targetAddress = 0x71;
        i2cTransaction.writeBuf = &switchConfig;
        i2cTransaction.writeCount = 1;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;

        status = I2C_transfer(gI2cHandle[CONFIG_I2C2], &i2cTransaction);
        if (status == SystemP_SUCCESS) {
            DebugP_log("I2C switch configured to 0x01 (both channels enabled)\r\n");
        } else {
            DebugP_log("ERROR: Failed to configure I2C switch!\r\n");
        }

        uint8_t readback;
        i2cTransaction.writeBuf = NULL;
        i2cTransaction.writeCount = 0;
        i2cTransaction.readBuf = &readback;
        i2cTransaction.readCount = 1;
        I2C_transfer(gI2cHandle[CONFIG_I2C2], &i2cTransaction);
        DebugP_log("Switch readback: 0x%02X (should be 0x02)\r\n", readback);
    }

    if (gI2cHandle[CONFIG_I2C2] != NULL)
    {
        DebugP_log("\n=== COMPLETE I2C2 Bus Scan (After Pin 11 Reset) ===\r\n");
        DebugP_log("Scanning all addresses 0x03 to 0x77...\r\n");

        int devicesFound = 0;
        for (uint8_t addr = 0x03; addr <= 0x77; addr++)
        {
            int32_t scanStatus = I2C_probe(gI2cHandle[CONFIG_I2C2], addr);
            if (scanStatus == SystemP_SUCCESS)
            {
                DebugP_log("  Device found at 0x%02X", addr);
                devicesFound++;

                /* Targeted reads based on device type */
                if (addr == 0x71 || addr == 0x70)
                {
                    /* I2C Switch: Pure read (no register address write) */
                    uint8_t switchState = 0;
                    I2C_Transaction i2cTxn;
                    I2C_Transaction_init(&i2cTxn);
                    i2cTxn.targetAddress = addr;
                    i2cTxn.readBuf = &switchState;
                    i2cTxn.readCount = 1;
                    i2cTxn.writeBuf = NULL;
                    i2cTxn.writeCount = 0;
                    if (I2C_transfer(gI2cHandle[CONFIG_I2C2], &i2cTxn) == SystemP_SUCCESS)
                    {
                        DebugP_log(" -> State = 0x%02X (I2C Switch)", switchState);
                    }
                    else
                    {
                        DebugP_log(" (I2C Switch - read failed)");
                    }
                }
                else if (addr == 0x18 || addr == 0x1A)
                {
                    /* UB971 Serializer: Register read */
                    uint8_t reg00 = 0;
                    if (Board_i2c8BitRegRd(gI2cHandle[CONFIG_I2C2], addr, 0x00, &reg00, 1,
                                          APP_I2C_TRANSACTION_TIMEOUT) == SystemP_SUCCESS)
                    {
                        DebugP_log(" -> Reg 0x00 = 0x%02X (UB971 Serializer)", reg00);
                    }
                    else
                    {
                        DebugP_log(" (UB971 Serializer - read failed)");
                    }
                }
                else if (addr >= 0x30 && addr <= 0x3D)
                {
                    /* UB9702 Deserializer: Register read */
                    uint8_t reg00 = 0;
                    if (Board_i2c8BitRegRd(gI2cHandle[CONFIG_I2C2], addr, 0x00, &reg00, 1,
                                          APP_I2C_TRANSACTION_TIMEOUT) == SystemP_SUCCESS)
                    {
                        DebugP_log(" -> Reg 0x00 = 0x%02X **POSSIBLE UB9702 DESERIALIZER!!!**", reg00);
                        gFusion2Det = BTRUE;
                    }
                    else
                    {
                        DebugP_log(" **POSSIBLE UB9702 DESERIALIZER!!!** (read failed)");
                        gFusion2Det = BTRUE;
                    }
                }
                else if (addr == 0x52 || addr == 0x50)
                {
                    DebugP_log(" (EEPROM)");
                }
                else
                {
                    DebugP_log(" (Unknown device)");
                }
                DebugP_log("\r\n");
            }
        }

        DebugP_log("Total devices found: %d\r\n", devicesFound);
        DebugP_log("=== I2C Scan Complete ===\r\n\r\n");

        /* Restore I2C switch configuration after scan (scan may have disrupted it) */
        uint8_t switchConfig = 0x02;
        I2C_Transaction i2cTransaction;
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.targetAddress = 0x71;
        i2cTransaction.writeBuf = &switchConfig;
        i2cTransaction.writeCount = 1;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.readCount = 0;
        status = I2C_transfer(gI2cHandle[CONFIG_I2C2], &i2cTransaction);
        if (status == SystemP_SUCCESS) {
            DebugP_log("I2C switch restored to 0x02 after scan\r\n");
        } else {
            DebugP_log("WARNING: Failed to restore I2C switch after scan\r\n");
        }

        /* Specific probe for UB9702 at expected address */
        DebugP_log("=== Probing for UB9702 at 0x3D ===\r\n");
        uint8_t ub9702Addr = 0x3D;
        int32_t probeStatus = I2C_probe(gI2cHandle[CONFIG_I2C2], ub9702Addr);

        if (probeStatus == SystemP_SUCCESS)
        {
            DebugP_log("SUCCESS!!! UB9702 detected at 0x%02X!\r\n", ub9702Addr);
            gFusion2Det = BTRUE;

            /* Try reading device ID register */
            uint8_t regVal = 0;
            int32_t readStatus = Board_i2c8BitRegRd(gI2cHandle[CONFIG_I2C2], ub9702Addr,
                                                    0x00, &regVal, 1,
                                                    APP_I2C_TRANSACTION_TIMEOUT);
            if (readStatus == SystemP_SUCCESS)
            {
                DebugP_log("UB9702 Register 0x00 (Device ID) = 0x%02X\r\n", regVal);
            }

            /* Read DEVICE_STS register to verify REFCLK */
            readStatus = Board_i2c8BitRegRd(gI2cHandle[CONFIG_I2C2], ub9702Addr,
                                            0x04, &regVal, 1,
                                            APP_I2C_TRANSACTION_TIMEOUT);
            if (readStatus == SystemP_SUCCESS)
            {
                DebugP_log("UB9702 Register 0x04 (DEVICE_STS) = 0x%02X", regVal);
                if (regVal & (1 << 4))
                {
                    DebugP_log(" [REFCLK_VALID: YES]\r\n");
                }
                else
                {
                    DebugP_log(" [REFCLK_VALID: NO - CHECK 25MHz CLOCK!]\r\n");
                }
            }
        }
        else
        {
            DebugP_log("UB9702 NOT detected at 0x%02X (status=%d)\r\n", ub9702Addr, probeStatus);
        }
    }

    /* Check for the Fusion2 board via EEPROM */
    uint8_t bDet = BFALSE;
    bDet = Board_detectBoard(BOARD_ID_FUSION2, 0);
    if (BTRUE == bDet)
    {
        DebugP_log("Fusion 2 board detected via EEPROM!!!\r\n");
        gFusion2Det = BTRUE;
    }
    else
    {
        DebugP_log("Fusion 2 board NOT detected via EEPROM (EEPROM may not be programmed)\r\n");
        if (gFusion2Det == BTRUE)
        {
            DebugP_log("But UB9702 was detected, so treating as Fusion2 board!\r\n");
        }
    }

    if (FVID2_SOK == status)
    {
        if (gFusion2Det == BTRUE)
        {
            Board_fpdUb9702GetI2CAddr(&i2cAddr, appInstObj->boardCsiInstID);
            memcpy(deSerConfig, gUb9702SensorCfg, (sizeof(gUb9702SensorCfg)));
        }
        else
        {
            DebugP_log("Fusion 2 board NOT detected!");
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
    if (*sensorI2cAddr || portNum || *ub953I2cAddr)
    {

    }

    if ((i2cInst == 0U) && (i2cAddr == 0U))
    {
        retVal = FVID2_EFAIL;
    }
    else
    {
        for (cnt = 0;
             cnt < sizeof(deSerConfig)/(sizeof(deSerConfig[0]));
             cnt ++)
        {
            regAddr8 =deSerConfig[cnt][0] & 0xFF;

            if(regAddr8 == 0x5E)
            {
                if(appInstObj->cameraSensor == D3IMX390_CM_MODULE)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_CM_MODULE) << 1) & 0xFF ;
                }
                else if (appInstObj->cameraSensor == D3IMX390_RCM_MODULE)
                {
                    regVal = ((D3IMX390_SENSOR_ADDR_RCM_MODULE) << 1) & 0xFF ;
                }
            }
            else if(regAddr8 == 0x65)
            {
                regVal = ((ub953I2cAddr[portNum]) << 1) & 0xFF ;
            }
            else if(regAddr8 == 0x66)
            {
                regVal = ((sensorI2cAddr[portNum]) << 1) & 0xFF ;
                portNum++;
            }
            else
            {
                regVal = deSerConfig[cnt][1] & 0xFF;
            }

            timeOut = deSerConfig[cnt][2];
            status = Board_i2c8BitRegWr(gI2cHandle[CONFIG_I2C2], i2cAddr, regAddr8, &regVal, 1,
                                     APP_I2C_TRANSACTION_TIMEOUT);
            if (0 != status)
            {
                GT_3trace(CsirxAppTrace,
                          GT_INFO,
                          APP_NAME ": Failed to Set de-serializer register %x: Value:%x\n instance %d\n",
                          deSerConfig[cnt][0],
                          deSerConfig[cnt][1],
              appInstObj->instId
              );
                break;
            }
            else
            {
                App_wait(timeOut);
            }
        }

        for (sensorIdx = 0U ; sensorIdx < APP_CAPT_CH_NUM ; sensorIdx++)
        {
            if (0 == status)
            {
                /* UB953 serializer Port configuration */
                i2cAddr = D3IMX390_INST0_PORT_0_SER_ADDR;
                for (cnt = 0;
                     cnt < sizeof(gUb953SensorCfg)/(sizeof(gUb953SensorCfg[0]));
                     cnt ++)
                {
                    regAddr8 = gUb953SensorCfg[cnt][0] & 0xFF;
                    regVal = gUb953SensorCfg[cnt][1] & 0xFF;
                    timeOut = gUb953SensorCfg[cnt][2];
                    status = Board_i2c8BitRegWr(gI2cHandle[CONFIG_I2C2],
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
                i2cAddr = D3IMX390_INST0_PORT_0_SENSOR_ADDR;
                for (cnt = 0; cnt < SENSOR_CFG_SIZE; cnt ++)
                {
                    regAddr = gSensorCfg[cnt][0];
                    regVal = gSensorCfg[cnt][1];

                    status = Board_i2c16BitRegWr(gI2cHandle[CONFIG_I2C2],
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
                if (appInstObj->instId == CSIRX_INSTANCE_ID_1)
                {
                    i2cAddr = 0x36U;
                }
                regAddr8 = 0x33;
                regVal = 0x3;
                status = Board_i2c8BitRegWr(gI2cHandle[CONFIG_I2C2],
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
