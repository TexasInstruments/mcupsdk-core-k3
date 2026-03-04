/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
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
 *  \file csirx_capture_test_main.c
 *
 *  \brief CSI RX Capture Example.
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
#include <drivers/csirx.h>
#include <drivers/i2c.h>
#include <kernel/nortos/dpl/common/ClockP_nortos_priv.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/CacheP.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_dpl_config.h"
#include "imx219_drv.h"
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< Application name */
#define APP_NAME                                  "CSIRX_CAPT_APP"
/**< Number of CSIRX instances exist in SOC */
#define APP_TOTAL_CAPT_INST                       (CSIRX_INSTANCE_ID_MAX)
/**< Number of CSIRX instances to test parallelly */
#define APP_CAPT_TEST_INST_NUM                    ((uint32_t)1U)
/**< Number of channels */
#define APP_CAPT_CH_NUM                           ((uint32_t)1U)
/**< Input Image Data format */
#define APP_CAPT_IMAGE_DT                         (FVID2_CSI2_DF_RAW8)
/**< Frame storage format. Only valid for RAW12 DT. */
#define APP_CAPT_IMAGE_STORAGE_FORMAT             (FVID2_CCSF_BITS12_UNPACKED16)
/**< Number of frames per stream */
#define APP_CAPT_FRAMES_PER_CH                    ((uint32_t)1U)
/**< Frame Attribute: Width in pixels */
#define APP_CAPT_FRAME_WIDTH                      ((uint32_t)3280)
/**< Frame Attribute: Height in pixels */
#define APP_CAPT_FRAME_HEIGHT                     ((uint32_t)2464)
/**< Frame Attribute: Bytes per pixel */
#define APP_CAPT_FRAME_BPP                        ((uint32_t)1U)

/**< I2C transaction timeout */
#define APP_I2C_TRANSACTION_TIMEOUT               ((uint32_t)2000U)

/**< Time period to receive frames in app */
#define APP_TEST_PERIOD_IN_SEC                    ((uint32_t)20)
/**
 * @{
 * Macros to control Fusion board and Camera Sensor version for the capture
 */
/**< Fusion Board Revision.
     '0': for Rev B or older boards.
     '1': for Rev C board. */
#define FUSION_BOARD_VER                       (1U)
/**< D3 IMX390 sensor type. */
#define D3IMX390_CM_MODULE                     (0)
#define D3IMX390_RCM_MODULE                    (1)

#define APP_CSIRX_INST0_CAMERA_SENSOR          (D3IMX390_CM_MODULE)
#define APP_CSIRX_INST1_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)
#define APP_CSIRX_INST2_CAMERA_SENSOR          (D3IMX390_RCM_MODULE)

#define UB960_USE_PATTERN_GENERATOR            (0U)

#define BOARD_CSI_I2C_MUX_INSTANCE             (0U)
#define BOARD_CSI_I2C_SWITCH_INSTANCE          (1U)
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

#define SENSOR_CFG_SIZE  (3075)

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
#define APP_CAPT_CH_MAX                       ((uint32_t)4U)
#define TIMER_NUM_INSTANCES                   (1u)

#define IMX219_REG_VTPXCK_DIV       0x0301
#define IMX219_REG_VTSYCK_DIV       0x0303
#define IMX219_REG_PREPLLCK_VT_DIV  0x0304
#define IMX219_REG_PREPLLCK_OP_DIV  0x0305
#define IMX219_REG_PLL_VT_MPY0      0x0306
#define IMX219_REG_PLL_VT_MPY8      0x0307
#define IMX219_REG_OPPXCK_DIV       0x0309
#define IMX219_REG_OPSYCK_DIV       0x030b
#define IMX219_REG_PLL_OP_MPY0      0x030c
#define IMX219_REG_PLL_OP_MPY8      0x030d
#define IMX219_REG_LINE_LENGTH_A    0x0162
#define IMX219_REG_X_ODD_INC_A      0x0170
#define IMX219_REG_Y_ODD_INC_A      0x0171
#define IMX219_REG_DPHY_CTRL        0x0128
#define IMX219_REG_EXCK_FREQ        0x012a

/* External clock frequency is 24.0M */
#define IMX219_XCLK_FREQ                24000000U
#define IMX219_DPHY_CTRL_TIMING_AUTO    0U
#define IMX219_EXCK_FREQ(n)             ((n) * 256) /* n expressed in MHz */

typedef enum
{
    PCA9543A_DISABLE_ALL = 0x00,
    PCA9543A_ENABLE_CH0  = 0x01,
    PCA9543A_ENABLE_CH1  = 0x02,
    PCA9543A_ENABLE_ALL  = 0x03
}pca9543a_t;

TCA6424_Params TCA6424_IOexp_params =
{
    .i2cInstance = CONFIG_I2C1,
    .i2cAddress =  0x22
};

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

/**
 *  \brief I2C register read/write object.
 */
typedef struct
{
    uint32_t reg;
    /**< Destination address */
    uint32_t val;
    /**< Value to be written */
    uint8_t size;
    /**< Size of addr+data in double words */
} imx219_regs_t;

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
 * \brief   App function to Imager start stream.
 *
 * \param   appInstObj        CSI RX Capture Test Object
 *
 * \retval  Sensor configuration status.
 */
static int32_t CsirxApp_startStream(void);

static void CsirxApp_sensorDeInit(void);

/**
 * \brief   App function to get current time in msec.
 *
 * \param   None.
 *
 * \retval  I2C instance setup status.
 */
uint32_t CsirxApp_getCurTimeInMsec(void);

/**
 * \brief   App function to calculate the elapsed time from 'startTime' in msec.
 *
 * \param   None.
 *
 * \retval  I2C instance setup status.
 */
uint32_t CsirxApp_getElapsedTimeInMsec(uint32_t startTime);

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

void App_wait(uint32_t wait_in_ms);
extern void Drivers_open(void);
static void i2c_read_error_handler(uint16_t sample, int32_t status);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* App common object */
CsirxApp_CaptCommonObj gAppCommonObj;

/* CSIRX instances to use in application */
uint32_t  gAppCapInst[APP_CAPT_TEST_INST_NUM] = {CSIRX_INSTANCE_ID_0}; //,CSIRX_INSTANCE_ID_1};

/* Memory buffer to hold data */
static uint8_t gFrmDropBuf[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAME_PITCH)] __attribute__(( aligned(128), section(".data_buffer")));
static uint8_t gFrms[APP_TOTAL_CAPT_INST][(APP_CAPT_FRAMES_PER_CH * APP_CAPT_CH_NUM)][APP_CAPT_FRAME_SIZE]__attribute__(( aligned(128), section(".data_buffer")));

/* Semaphore to indicate app completion */
SemaphoreP_Object gAppCompletionSem;

#if defined(FREERTOS)
/* Capture test Task handle */
extern TaskP_Handle gCsirxAppTask;
#endif
extern uint32_t gTimerBaseAddr[TIMER_NUM_INSTANCES];

uint8_t gSensorCfg[17][5] = IMX219_CONFIG;
// uint16_t gUb960SensorCfg[][3]={
// #if UB960_USE_PATTERN_GENERATOR
//     {0x32, 0x01, 0x50},
//     {0x1F, 0x10, 0x1},
//     {0xC9, 0x32, 0x1},
//     {0xB0, 0x1C, 0x1},
//     {0xB1, 0x92, 0x1},
//     {0xB2, 0x40, 0x1},
//     {0xB0, 0x01, 0x1},
//     {0xB1, 0x01, 0x1},
//     {0xB2, 0x01, 0x1},
//     {0xB1, 0x02, 0x1},
//     {0xB2, 0xF3, 0x1},
//     {0xB1, 0x03, 0x1},
//     {0xB2, APP_CAPT_IMAGE_DT, 0x1},
//     {0xB1, 0x04, 0x1},
//     {0xB2, APP_CAPT_FRAME_LINE_LEN_HIGH, 0x1},
//     {0xB1, 0x05, 0x1},
//     {0xB2, APP_CAPT_FRAME_LINE_LEN_LOW, 0x1},
//     {0xB1, 0x06, 0x1},
//     {0xB2, 0x02, 0x1},
//     {0xB1, 0x07, 0x1},
//     {0xB2, 0x80, 0x1},/*D0*/
//     {0xB1, 0x08, 0x1},
//     {0xB2, APP_CAPT_FRAME_HEIGHT_HIGH, 0x1},
//     {0xB1, 0x09, 0x1},
//     {0xB2, APP_CAPT_FRAME_HEIGHT_LOW, 0x1},
//     {0xB1, 0x0A, 0x1},
//     {0xB2, 0x08, 0x1},
//     {0xB1, 0x0B, 0x1},
//     {0xB2, 0x80, 0x1},
//     {0xB1, 0x0C, 0x1},
//     {0xB2, 0x04, 0x1},
//     {0xB1, 0x0D, 0x1},
//     {0xB2, 0x7D, 0x1},
//     {0xB1, 0x0E, 0x1},
//     {0xB2, 0x07, 0x1},
//     {0xB1, 0x0F, 0x1},
//     {0xB2, 0x08, 0x1},
//     {0x33, 0x02, 0x1},
//     {0xFFFF, 0x00, 0x0} /*End of script */
// #else
//     {0x01, 0x02, 0x100},
//     {0x1f, 0x00, 0x1},

//     {0xB0, 0x1C,0x1},
//     {0xB1, 0x16,0x1},
//     {0xB2, 0x00,0x1},
//     {0xB1, 0x17,0x1},
//     {0xB2, 0x00,0x1},
//     {0xB1, 0x18,0x1},
//     {0xB2, 0x00,0x1},
//     {0xB1, 0x19,0x1},
//     {0xB2, 0x00,0x1},
//     {0xB0, 0x1C,0x1},
//     {0xB1, 0x15,0x1},
//     {0xB2, 0x0A,0x1},
//     {0xB2, 0x00,0x10},

//     {0x0D, 0x90, 0x1}, /*I/O to 3V3 - Options not valid with datashee*/
//     {0x0C, 0x0F, 0x1}, /*Enable All ports*/

//     /*Select Channel 0*/
//     {0x4C, 0x01, 0x1},
//     {0x58, 0x5E, 0x1},
//     {0x72, 0x00, 0x1}, /*VC map*/

//     /*Select Channel 1*/
//     {0x4C, 0x12, 0x1},
//     {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

//     /*Select Channel 2*/
//     {0x4C, 0x24, 0x1},
//     {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

//     /*Select Channel 3*/
//     {0x4C, 0x38, 0x1},
//     {0x58, 0x5E, 0x1},/*Enable Back channel, set to 50Mbs*/

//     /*Select Channel 0*/
//     {0x4C, 0x01, 0x1},
//     {0xB0, 0x04, 0x1},
//     {0xB1, 0x03, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB1, 0x13, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB0, 0x04, 0x1},
//     {0xB1, 0x04, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0xB1, 0x14, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0x42, 0x71, 0x1}, /*Unknown*/
//     {0x41, 0xF0, 0x1}, /*Unknown*/
//     {0xB9, 0x18, 0x1},

//     /*Select Channel 1*/
//     {0x4C, 0x12, 0x1},
//     {0xB0, 0x08, 0x1},
//     {0xB1, 0x03, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB1, 0x13, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB0, 0x08, 0x1},
//     {0xB1, 0x04, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0xB1, 0x14, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0xB0, 0x08, 0x1},
//     {0x42, 0x71, 0x1}, /*Unknown*/
//     {0x41, 0xF0, 0x1}, /*Unknown*/
//     {0xB9, 0x18, 0x1},

//     /*Select Channel 2*/
//     {0x4C, 0x24, 0x1},
//     {0xB0, 0x0C, 0x1},
//     {0xB1, 0x03, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB1, 0x13, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB0, 0x0C, 0x1},
//     {0xB1, 0x04, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0xB1, 0x14, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0x42, 0x71, 0x1},/*Unknown*/
//     {0x41, 0xF0, 0x1},/*Unknown*/
//     {0xB9, 0x18, 0x1},

//     /*Select Channel 3*/
//     {0x4C, 0x38, 0x1},
//     {0xB0, 0x10, 0x1},
//     {0xB1, 0x03, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB1, 0x13, 0x1},
//     {0xB2, 0x20, 0x1},
//     {0xB0, 0x10, 0x1},
//     {0xB1, 0x04, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0xB1, 0x14, 0x1},
//     {0xB2, 0x3F, 0x1},
//     {0x42, 0x71, 0x1},/*Unknown*/
//     {0x41, 0xF0, 0x1},/*Unknown*/
//     {0xB9, 0x18, 0x1},

//     {0x32, 0x01, 0x1}, /*Enable TX port 0*/
//     {0x20, 0x00, 0x1}, /*Forwarding and using CSIport 0 */

//     /*Sets GPIOS*/
//     {0x10, 0x83, 0x1},
//     {0x11, 0xA3, 0x1},
//     {0x12, 0xC3, 0x1},
//     {0x13, 0xE3, 0x1},

//     {0x4C, 0x01, 0x1}, /* 0x01 */
//     {0x32, 0x01, 0x1}, /*Enable TX port 0*/
//     {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
//     {0xBC, 0x00, 0x1}, /*Unknown*/
//     {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
//     {0x65, (D3IMX390_INST0_PORT_0_SER_ADDR << 1U), 0x1},
//     {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
//     {0x66, (D3IMX390_INST0_PORT_0_SENSOR_ADDR << 1U), 0x1},
//     {0x6D, 0x6C,0x1}, /*CSI Mode*/
//     {0x72, 0x00,0x1}, /*VC Map - All to 0 */
//     {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
//     {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
//     {0xB0,0x1C, 0x1},
//     {0xB1,0x15, 0x1},
//     {0xB2,0x0A, 0x1},
//     {0xB2,0x00, 0x1},

//     {0x4C, 0x12, 0x1}, /* 0x12 */
//     {0x32, 0x01, 0x1}, /*Enable TX port 0*/
//     {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
//     {0xBC, 0x00, 0x1}, /*Unknown*/
//     {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
//     {0x65, (D3IMX390_INST0_PORT_1_SER_ADDR << 1U), 0x1},
//     {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
//     {0x66, (D3IMX390_INST0_PORT_1_SENSOR_ADDR << 1U), 0x1},
//     {0x6D, 0x6C,0x1}, /*CSI Mode*/
//     {0x72, 0x55,0x1}, /*VC Map - All to 1 */
//     {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
//     {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
//     {0xB0,0x1C, 0x1},
//     {0xB1,0x15, 0x1},
//     {0xB2,0x0A, 0x1},
//     {0xB2,0x00, 0x1},

//     {0x4C, 0x24, 0x1}, /* 0x24 */
//     {0x32, 0x01, 0x1}, /*Enable TX port 0*/
//     {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
//     {0xBC, 0x00, 0x1}, /*Unknown*/
//     {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
//     {0x65, (D3IMX390_INST0_PORT_2_SER_ADDR << 1U), 0x1},
//     {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
//     {0x66, (D3IMX390_INST0_PORT_2_SENSOR_ADDR << 1U), 0x1},
//     {0x6D, 0x6C,0x1}, /*CSI Mode*/
//     {0x72, 0xaa,0x1}, /*VC Map - All to 2 */
//     {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
//     {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
//     {0xB0,0x1C, 0x1},
//     {0xB1,0x15, 0x1},
//     {0xB2,0x0A, 0x1},
//     {0xB2,0x00, 0x1},

//     {0x4C, 0x38, 0x1}, /* 0x38 */
//     {0x32, 0x01, 0x1}, /*Enable TX port 0*/
//     {0x33, 0x02, 0x1}, /*Enable Continuous clock mode and CSI output*/
//     {0xBC, 0x00, 0x1}, /*Unknown*/
//     {0x5D, (UB960_SERIALISER_ADDR << 1U), 0x1}, /*Serializer I2C Address*/
//     {0x65, (D3IMX390_INST0_PORT_3_SER_ADDR << 1U), 0x1},
//     {0x5E, (D3IMX390_SENSOR_ADDR_CM_MODULE << 1U), 0x1}, /*Sensor I2C Address*/
//     {0x66, (D3IMX390_INST0_PORT_3_SENSOR_ADDR << 1U), 0x1},
//     {0x6D, 0x6C,0x1}, /*CSI Mode*/
//     {0x72, 0xFF,0x1}, /*VC Map - All to 3 */
//     {0x7C, 0x20, 0x10}, /*Line Valid active high, Frame Valid active high*/
//     {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/
//     {0xB0,0x1C, 0x1},
//     {0xB1,0x15, 0x1},
//     {0xB2,0x0A, 0x1},
//     {0xB2,0x00, 0x100},
// #endif
// };

// uint16_t gUb953SensorCfg[][3] = {
//     {0x01, 0x01, 0x80},
//     {0x02, 0x72, 0x10},

// #if (FUSION_BOARD_VER == 0)
//     {0x06, 0x21, 0x1F},
// #elif (FUSION_BOARD_VER == 1)
//     {0x06, 0x41, 0x1F},
// #else
// /* Unsupported version */
// #endif
//     {0x07, 0x28, 0x1F},
//     {0x0D, 0x01, 0x10},

//     {0x0E, 0xF0, 0x10},
//     {0xB0, 0x04, 0x10},
//     {0xB1, 0x08, 0x10},
//     {0xB2, 0x07, 0x80},
// };

// uint32_t gUb953I2CAddrInst0[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST0_PORT_0_SER_ADDR,
//     D3IMX390_INST0_PORT_1_SER_ADDR,
//     D3IMX390_INST0_PORT_2_SER_ADDR,
//     D3IMX390_INST0_PORT_3_SER_ADDR
// };

// uint32_t gSensorI2CAddrInst0[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST0_PORT_0_SENSOR_ADDR,
//     D3IMX390_INST0_PORT_1_SENSOR_ADDR,
//     D3IMX390_INST0_PORT_2_SENSOR_ADDR,
//     D3IMX390_INST0_PORT_3_SENSOR_ADDR
// };
// uint32_t gUb953I2CAddrInst1[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST1_PORT_0_SER_ADDR,
//     D3IMX390_INST1_PORT_1_SER_ADDR,
//     D3IMX390_INST1_PORT_2_SER_ADDR,
//     D3IMX390_INST1_PORT_3_SER_ADDR
// };

// uint32_t gSensorI2CAddrInst1[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST1_PORT_0_SENSOR_ADDR,
//     D3IMX390_INST1_PORT_1_SENSOR_ADDR,
//     D3IMX390_INST1_PORT_2_SENSOR_ADDR,
//     D3IMX390_INST1_PORT_3_SENSOR_ADDR
// };
// uint32_t gUb953I2CAddrInst2[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST2_PORT_0_SER_ADDR,
//     D3IMX390_INST2_PORT_1_SER_ADDR,
//     D3IMX390_INST2_PORT_2_SER_ADDR,
//     D3IMX390_INST2_PORT_3_SER_ADDR
// };

// uint32_t gSensorI2CAddrInst2[APP_CAPT_CH_MAX] =
// {
//     D3IMX390_INST2_PORT_0_SENSOR_ADDR,
//     D3IMX390_INST2_PORT_1_SENSOR_ADDR,
//     D3IMX390_INST2_PORT_2_SENSOR_ADDR,
//     D3IMX390_INST2_PORT_3_SENSOR_ADDR
// };

/* IMX219 common configuration register data */
static const imx219_regs_t imx219_common_regs[] =
{
    /* To Access Addresses 3000-5fff, send the following commands */
    {0x30eb, 0x05, 3},
    {0x30eb, 0x0c, 3},
    {0x300a, 0xff, 3},
    {0x300b, 0xff, 3},
    {0x30eb, 0x05, 3},
    {0x30eb, 0x09, 3},

    /* PLL Clock Table */
    { IMX219_REG_PREPLLCK_VT_DIV, 3, 3}, /* OK - Auto - Pre PLL clock Video Timing System Div = 0x03=auto set for 24MHz-27MHz */
    { IMX219_REG_PREPLLCK_OP_DIV, 3, 3}, /* OK - Auto - Pre PLL clock Output System Div Value=0x03= auto set for 24MHz-27MHz*/
    { IMX219_REG_PLL_VT_MPY8, 57, 3},     /* PLL Video Timing System Multiplier Value (PLL_VT_MPY[10:8] = 57) */
    { IMX219_REG_PLL_OP_MPY8, 114, 3},    /* PLL Output System Multiplier Value = 114*/

	/* Undocumented registers */
    {0x455e, 0x00,3},
    {0x471e, 0x4b,3},
    {0x4767, 0x0f,3},
    {0x4750, 0x14,3},
    {0x4540, 0x00,3},
    {0x47b4, 0x14,3},
    {0x4713, 0x30,3},
    {0x478b, 0x10,3},
    {0x478f, 0x10,3},
    {0x4793, 0x10,3},
    {0x4797, 0x0e,3},
    {0x479b, 0x0e,3},

    /* Output setup registers */
    { IMX219_REG_DPHY_CTRL, IMX219_DPHY_CTRL_TIMING_AUTO, 3 }, /* MIPI Global Timing - Auto Mode */
    { IMX219_REG_EXCK_FREQ, IMX219_EXCK_FREQ(IMX219_XCLK_FREQ / 1000000), 4} /* Table 39 - EXCK Frequency = 0x1800 */
};

/* Debug Variables */
volatile uint32_t gFrmCntr = 0;
volatile CsirxApp_CaptInstObj *appInstObj;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int Csirx_captureTest(void)
{
    int retVal = FVID2_SOK;
    CsirxApp_CaptInstObj *appInstObj[APP_CAPT_TEST_INST_NUM];
    CsirxApp_CaptCommonObj *appCommonObj;
    appCommonObj = &gAppCommonObj;

    //Drivers_open(); This is already oppend in main

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
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ":===================Setup Details===================\r\n");
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    GT_0trace(CsirxAppTrace, GT_INFO,
              APP_NAME ":===================Setup Details===================\r\n");

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
    if (FVID2_SOK == retVal)
    {
        CsirxApp_consolePrintf("All tests have passed!\r\n");
    }

    return (retVal);
}

void CsirxApp_timerIsr(void *arg)
{
    static volatile uint32_t timerIsrCount=0;
    timerIsrCount++;
    DebugP_log("CsirxApp_timerIsr timer is: %d\r\n", timerIsrCount);
    if (timerIsrCount == APP_TEST_PERIOD_IN_SEC)
    {
        TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);
        /* Post semaphore to print the results */
        SemaphoreP_post(&gAppCompletionSem);
    }
}

static void CsirxApp_initCaptParams(CsirxApp_CaptInstObj* appInstObj)
{
    uint32_t loopCnt = 0U, i;

    for (i = 0; i < (APP_CAPT_FRAME_SIZE);i++)
    {
        gFrms[0][0][i] = 0;
    }
    for (i = 0; i < (APP_CAPT_FRAME_PITCH); i++)
    {
        gFrmDropBuf[0][i] = 0;
    }

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
    appInstObj->createPrms.instCfg.numDataLanes = 2U; /* IMX219, 2 Lanes Only */
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
    UdmaInitPrms_init(UDMA1_INST_ID_BCDMA_0, &udmaInitPrms);
    dmaStatus = Udma_init(drvHandle, &udmaInitPrms);
    if(UDMA_SOK != dmaStatus)
    {
        retVal = FVID2_EFAIL;
        DebugP_log("UDMA Init Failed!!!\r\n");
        GT_0trace(CsirxAppTrace, GT_ERR,
                  APP_NAME ": UDMA Init Failed!!!\r\n");
    }
    retVal = Csirx_init(&appCommonObj->initPrms);
    if (retVal != FVID2_SOK)
    {
        DebugP_log("System Init Failed!!!\r\n");
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
        DebugP_log("Capture Create Failed!!!\r\n");
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
    uint32_t elapsedTime = 0, fps = 0;
    uint64_t tempVar = 0;

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
    /* Start the imager stream */
    retVal += CsirxApp_startStream();

    if (retVal == 0)
    {
        DebugP_log("Started Camera Sensor Stream\r\n");
    }
    else
    {
        DebugP_log("Unable to start Camera Sensor Stream\r\n");
    }

    /* start the tick timer */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
    SemaphoreP_pend(&gAppCompletionSem, SystemP_WAIT_FOREVER);

    // /* Uncomment below to take dump of sensor configuration - remove before release */
    // uint8_t dump[1576];
    // uint8_t temp[2];
    // for (int i=0; i<1576; i+=2)
    // {
    //     temp[0] = (i>>8) & 0xFF;
    //     temp[1] = i & 0xFF;

    //     /* Write to Access MODEL_ID Register */
    //     retVal = I2C_Sns_Write(gI2cHandle[CONFIG_I2C2], 0x10, &temp[0], 2);

    //     /* Read Back MODEL_ID[15:0] Register */
    //     retVal |= I2C_Sns_Read(gI2cHandle[CONFIG_I2C2], 0x10, &temp[0], 2);

    //     dump[i] = temp[0];
    //     dump[i+1] = temp[1];
    // }
    /* Stop IMX219 Stream */
    CsirxApp_sensorDeInit();
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

    /* Uncomment below to take dump of capture - clean up before release */
    GT_0trace(CsirxAppTrace, GT_INFO,"Finished capturing!\r\n");

    /* Ensure all frame buffers are flushed from cache before memory dump */
    CacheP_inv((void *)gFrms, sizeof(gFrms), CacheP_TYPE_ALLD);

    volatile int loop = 1;
    while (loop);

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
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Frames Received: %d\r\n",
                  appCommonObj->appInstObj[i].numFramesRcvd);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Frames Received with errors: %d\r\n",
                  appCommonObj->appInstObj[i].frameErrorCnt);
        GT_0trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Capture Application Completed!!!\r\n");
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": FIFO Overflow Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.overflowCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Spurious UDMA interrupt count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.spuriousUdmaIntrCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Front FIFO Overflow Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.frontFIFOOvflCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": CRC Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.crcCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Un-corrected ECC Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.eccCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Corrected ECC Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.correctedEccCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Data ID Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.dataIdErrorCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Invalid Access Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.invalidAccessCount);
        GT_1trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Invalid Short Packet Receive Error Count: %d\r\n",
                  appCommonObj->appInstObj[i].captStatus.invalidSpCount);
        for(loopCnt = 0U ; loopCnt < CSIRX_NUM_STREAM ; loopCnt++)
        {
            GT_2trace(CsirxAppTrace, GT_INFO,
                  APP_NAME ": Stream%d FIFO Overflow Error Count: %d\r\n",
                  loopCnt,
                  appCommonObj->appInstObj[i].captStatus.strmFIFOOvflCount[loopCnt]);
        }
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
        if (appInstObj->frameErrorCnt > 0U)
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
        DebugP_log("CSIRX_CAPT_APP : %d frames captured in %d msec at the rate of %d.%2d fps\r\n",
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

    /* Stop Camera Sensor */
    CsirxApp_sensorDeInit();

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
    appInstObj = (CsirxApp_CaptInstObj *) appData;

    gFrmCntr++;

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

            /* Invalidate cache for frame buffer after DMA write */
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

static int32_t PCA9543A_WriteCtrlReg(I2C_Handle han, uint8_t addr, pca9543a_t data)
{
    int32_t    status = 0;
    volatile uint8_t buf = 0;
    I2C_Transaction i2cTransaction;

    /* Init I2C TCA9543APWR Read Control Reg Operation */
    I2C_Transaction_init(&i2cTransaction);
    buf = data;
    i2cTransaction.writeBuf   = (uint8_t *)&buf;
    i2cTransaction.writeCount = 1;
    i2cTransaction.targetAddress = addr;

    /* Transmit Write */
    status = I2C_transfer(han, &i2cTransaction);

    if(status == I2C_STS_SUCCESS)
    {
        DebugP_log("PCA9543A_WriteCtrlReg Success\n\r");
    }
    else
    {
        DebugP_log("PCA9543A_WriteCtrlReg Failure\n\r");
    }

    return status;
}

static int32_t PCA9543A_Probe(I2C_Handle han, uint8_t addr)
{
    int32_t    status = 0;

    status = I2C_probe(han, addr);

    return status;
}

static int32_t PCA9543A_ReadCtrlReg(I2C_Handle han, uint8_t addr, uint8_t *buf)
{
    int32_t    status = 0;
    I2C_Transaction i2cTransaction;

    /* read the results */
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.readBuf = &buf[0];
    i2cTransaction.readCount = 1;
    i2cTransaction.targetAddress = addr;

    status = I2C_transfer(han, &i2cTransaction);

    return status;
}

static int32_t I2C_Sns_Write(I2C_Handle  handle,
                        uint8_t  i2cAddr,
                        uint8_t  *txBuf,
                        uint16_t  cnt)
{
    int32_t  status = IMX219_OK;
    I2C_Transaction i2cTransaction;

    if(NULL == handle)
    {
        status = IMX219_NOT_OK;
    }
    {
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.targetAddress = i2cAddr;
        i2cTransaction.writeBuf      = &txBuf[0];
        i2cTransaction.writeCount    = cnt;
        status = I2C_transfer(handle, &i2cTransaction);
    }

    return (status);
}

static int32_t I2C_Sns_Read(I2C_Handle handle,
                    uint8_t    i2cAddr,
                    uint8_t   *rxBuf,
                    uint16_t   cnt)
{
    int32_t  status = IMX219_OK;
    I2C_Transaction i2cTransaction;

    if(NULL == handle)
    {
        status = IMX219_NOT_OK;
    }
    else
    {
        /* read the results */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.targetAddress = i2cAddr;
        i2cTransaction.readBuf = &rxBuf[0];
        i2cTransaction.readCount = cnt;
        status = I2C_transfer(handle, &i2cTransaction);
    }

    return (status);
}

int32_t I2C_Sns_Init_Regs(I2C_Handle handle, uint8_t  i2cAddr)
{
    uint8_t i, buf[4];
    int32_t status = 0;
    uint16_t size = (sizeof(imx219_common_regs) / sizeof(imx219_common_regs[0]));

    for (i = 0; i < size; i++)
    {
        buf[0] = (uint8_t)((imx219_common_regs[i].reg >> 8) & 0xFF);
        buf[1] = (uint8_t)(imx219_common_regs[i].reg & 0xFF);

        /* Adjust I2C Data for Transfer size */
        if (imx219_common_regs[i].size == 3)
        {
            buf[2] = (uint8_t)(imx219_common_regs[i].val & 0xFF);
            buf[3] = 0; /* DC */
        }
        else
        {   /* Assume Transfer Size of 4 */
            buf[2] = (uint8_t)((imx219_common_regs[i].val >> 8) & 0xFF);
            buf[3] = (uint8_t)(imx219_common_regs[i].val & 0xFF);
        }

        status |= I2C_Sns_Write(handle, i2cAddr, &buf[0], imx219_common_regs[i].size);
    }

    return status;
}

static int32_t CsirxApp_sensorConfig(CsirxApp_CaptInstObj* appInstObj)
{
    TCA6424_Config TCA6424_IOexp_config;
    int32_t retVal = FVID2_SOK;
    volatile uint16_t id = 0;
    uint8_t getIDbuf[2];

    //Drivers_i2cOpen();

    retVal |= TCA6424_open(&TCA6424_IOexp_config, &TCA6424_IOexp_params);

    retVal |= TCA6424_config(&TCA6424_IOexp_config, 13, TCA6424_MODE_OUTPUT);

    retVal |= TCA6424_setOutput(&TCA6424_IOexp_config, 13, TCA6424_OUT_STATE_HIGH);

    if (gI2cHandle[CONFIG_I2C2] != NULL)
    {
        retVal |= PCA9543A_Probe(gI2cHandle[CONFIG_I2C2], 0x71);

        /* Write a Value of 0x2 to the Control Register to enable Ch1 */
        retVal |= PCA9543A_WriteCtrlReg(gI2cHandle[CONFIG_I2C2], 0x71, PCA9543A_ENABLE_CH1);

        /* Get IMX219 Sensor ID */
        getIDbuf[0] = 0;
        getIDbuf[1] = 0;

        /* Write to Access MODEL_ID Register */
        retVal |= I2C_Sns_Write(gI2cHandle[CONFIG_I2C2], 0x10, &getIDbuf[0], 2);

        /* Read Back MODEL_ID[15:0] Register */
        retVal |= I2C_Sns_Read(gI2cHandle[CONFIG_I2C2], 0x10, &getIDbuf[0], 2);

        id = ((getIDbuf[0] << 8) | (getIDbuf[1]));

        if((retVal == IMX219_OK) && (id == 0x0219U))
        {
            DebugP_log("IMX219 Read ID Success!!! \r\n");

            for(int i=0; i<17; i++)
            {
                if ((i != 2) && (i != 5))
                {
                    retVal = I2C_Sns_Write(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
                }
                else
                {
                    retVal = I2C_Sns_Read(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
                    if (i == 2)
                    {
                        App_wait(10);
                    }
                    else
                    {
                        retVal |= I2C_Sns_Init_Regs(gI2cHandle[CONFIG_I2C2], 0x10);
                    }
                }

                if (retVal != IMX219_OK)
                {
                    DebugP_logError("IMX219 Configuration Failure!!! \r\n");
                    break;
                }
            }
        }
        else
        {
            DebugP_logError("IMX219 Read ID Failure!!! \r\n");
        }
    }
    else
    {
        retVal = FVID2_EFAIL;
        DebugP_logError("[I2C] Handle is NULL \r\n");
    }

    return (retVal);
}

static int32_t CsirxApp_startStream(void)
{
    int32_t retVal = FVID2_SOK;

    if(NULL != gI2cHandle[CONFIG_I2C2])
    {
        /* Start the IMX219 stream */
        for (int i=0; i<3; i++)
        {
            if (i != 2)
            {
                retVal = I2C_Sns_Write(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
            }
            else
            {
                retVal = I2C_Sns_Read(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
            }
            if (retVal != IMX219_OK)
            {
                break;
            }
        }
    }

    return retVal;
}

static void CsirxApp_sensorDeInit(void)
{
    /* Stop IMX219 Stream */
    for (int i=3; i<6; i++)
    {
        if (i != 5)
        {
            I2C_Sns_Write(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
        }
        else
        {
            I2C_Sns_Read(gI2cHandle[CONFIG_I2C2], 0x10, &(gSensorCfg[i][1]), gSensorCfg[i][0]);
        }
    }
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
