/*
 *  Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \file csirx_test.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the CSIRX test application.
 *
 */

#ifndef CSIRX_TEST_H_
#define CSIRX_TEST_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
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
#include <kernel/dpl/TaskP.h>

#include "ti_drivers_config.h"
#include <board/board_control.h>
#include "csirx_utils_mem.h"

#include <stdio.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSIRX_TEST_DEF_UDMA_INST                    UDMA_INST_ID_BCDMA_1

/**< Number of frames per stream                    */
#define CSIRX_TEST_CAPT_FRAMES_PER_CH               ((uint32_t)4U)
/* UART read timeout in msec                        */
#define CSIRX_TEST_UART_TIMEOUT_MSEC                (10000U)

#define CSIRX_TEST_PRINT_BUFSIZE                    (0x100U)

/* Application name string used in print statements */
#define APP_NAME                        "CSIRX_TEST"
#define CSIRX_TEST_MAX_TASKS             (10U)
#define CSIRX_TEST_MAX_CH                (CSIRX_NUM_CH)
#define CSIRX_TEST_MAX_INST              (CSIRX_INSTANCE_ID_MAX)
/* Default values */
#define CSIRX_TEST_USE_DEF               (0xFAFAU)
#if defined (QT_BUILD)
#define CSIRX_TEST_DEF_ITERATION_CNT     (1U)
#else
#define CSIRX_TEST_DEF_ITERATION_CNT     (1U)
#endif

/* Defined the following so that it is easy to understand a particular config */
#define DEF_HEAP_ID                      (UTILS_MEM_HEAP_ID_DDR)
#define TEST_ENABLE                      (BTRUE)
#define TEST_DISABLE                     (BFALSE)
#define PRF_ENABLE                       (BTRUE)
#define PRF_DISABLE                      (BFALSE)
#define PRINT_ENABLE                     (BTRUE)
#define PRINT_DISABLE                    (BFALSE)
#define TIMEST_ENABLE                    (BTRUE)
#define TIMEST_DISABLE                   (BFALSE)
#define DATA_CHECK_ENABLE                (BTRUE)
#define DATA_CHECK_DISABLE               (BFALSE)
#define PACING_NONE                      (0U)
#define DEF_PACING                       (20U)

#define CSIRX_TEST_RF_SOC_AM65XX         ((uint64_t) 0x00000001U)
#define CSIRX_TEST_RF_SOC_J7ES           ((uint64_t) 0x00000002U)
#define CSIRX_TEST_RF_SOC_ALL            ((uint64_t) 0xFFFFFFFFU)

#define CSIRX_TEST_RF_CORE_MPU1_0        ((uint64_t)(((uint64_t) 0x0001U) << 32U))
#define CSIRX_TEST_RF_CORE_MPU2_0        ((uint64_t)(((uint64_t) 0x0002U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU1_0        ((uint64_t)(((uint64_t) 0x0004U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU1_1        ((uint64_t)(((uint64_t) 0x0008U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU2_0        ((uint64_t)(((uint64_t) 0x0010U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU2_1        ((uint64_t)(((uint64_t) 0x0020U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU3_0        ((uint64_t)(((uint64_t) 0x0040U) << 32U))
#define CSIRX_TEST_RF_CORE_MCU3_1        ((uint64_t)(((uint64_t) 0x0080U) << 32U))
#define CSIRX_TEST_RF_CORE_C7X_1         ((uint64_t)(((uint64_t) 0x0100U) << 32U))
#define CSIRX_TEST_RF_CORE_C66X_1        ((uint64_t)(((uint64_t) 0x0200U) << 32U))
#define CSIRX_TEST_RF_CORE_C66X_2        ((uint64_t)(((uint64_t) 0x0400U) << 32U))
#define CSIRX_TEST_RF_CORE_ALL           ((uint64_t)(((uint64_t) 0xFFFFU) << 32U))
#define CSIRX_TEST_RF_CORE_MCU_ALL       (CSIRX_TEST_RF_CORE_MCU1_0 | CSIRX_TEST_RF_CORE_MCU1_1 | \
                                         CSIRX_TEST_RF_CORE_MCU2_0 | CSIRX_TEST_RF_CORE_MCU2_1 | \
                                         CSIRX_TEST_RF_CORE_MCU3_0 | CSIRX_TEST_RF_CORE_MCU3_1)

/* For future when we have dynamic coverage testcases */
#define CSIRX_TEST_RF_CFG_ALL            ((uint64_t)(((uint64_t) 0xFFFFU) << 48U))

#define BOARD_CSI_I2C_MUX_INSTANCE             (0U)
#define BOARD_CSI_I2C_SWITCH_INSTANCE          (1U)

/**
 *  \brief Testcase types.
 */
typedef enum
{
    /* Category */
    CSIRX_TCT_SANITY     = 0x01U,
    CSIRX_TCT_REGRESSION = 0x02U,
    CSIRX_TCT_FULL       = 0x04U,
    /* Adequacy */
    CSIRX_TCT_FUNCTIONAL  = 0x08U,
    CSIRX_TCT_STRESS      = 0x10U,
    CSIRX_TCT_NEGATIVE    = 0x20U,
    CSIRX_TCT_PERFORMANCE = 0x40U,
    CSIRX_TCT_MISC        = 0x80U,
    CSIRX_TCT_API         = 0x100U,
    /* Used for Test parser dont use in test case */
    CSIRX_TCT_ALL = 0x1FFU
} CsirxTestCaseType;

/**
 *  \brief Test types.
 */
typedef enum
{
    CSIRX_TEST_TYPE_CAPTURE_ONLY             = 0U,
    /**< Test type: capture only, captured frames will be dumped into memory
         from which it can be viewed off line */
    CSIRX_TEST_TYPE_CAPTURE_DISPLAY_LOOPBACK = 1U,
    /**< Test type: capture display loop-back, captured frames will be sent
         DSS */
} CsirxTestTypes;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Forward declaration. */
typedef struct CsirxInstCfgInfo_t    CsirxInstCfgInfo;
typedef struct CsirxInstObj_t        CsirxInstObj;
typedef struct CsirxChObj_t          CsirxChObj;
typedef struct CsirxChCfgInfo_t      CsirxChCfgInfo;
typedef struct CsirxTestTaskObj_t    CsirxTestTaskObj;
typedef struct CsirxTestTaskCfg_t    CsirxTestTaskCfg;
typedef struct CsirxTestParams_t     CsirxTestParams;
typedef struct CsirxSensorCfg_t      CsirxSensorCfg;

/** \brief Typedef for test case type function pointer */
typedef int32_t (*CsirxTestFxnPtr)(CsirxTestTaskObj *taskObj);


/**
 *  \brief Streaming channel configurations.
 */
struct CsirxChCfgInfo_t
{
    const uint32_t          chCfgInfoId;
    /**< Id of the channel configuration & info structure instance */
    const uint32_t          numCaptFrames;
    /**< Number of frames to capture before stopping the channel. */
    const uint32_t          numFrames;
    /**< Number of frames buffer to allocate per channel. */
    const uint32_t          heapId;
    /**< Frame memory allocation. */
    const Csirx_ChCfg       *chCfg;
    /**< Channel configuration. */
};

/**
 *  \brief Streaming channel Object.
 */
struct CsirxChObj_t
{
    const CsirxChCfgInfo    *chCfgInfo;
    /**< Reference to channel configurations */
    uint32_t                captFrames;
    /**< Number of frames captured.
         This will be updated by application run time */
    uint32_t                captErrFrames;
    /**< Number of frames captured.
         This will be updated by application run time */
    Fvid2_Frame             frames[CSIRX_TEST_CAPT_FRAMES_PER_CH * CSIRX_TEST_MAX_CH];
    /**< FVID2 Frames that will be used for capture. */
    uint64_t                *frmAddr[CSIRX_TEST_CAPT_FRAMES_PER_CH];
    /**< FVID2 Frames address that will be used for capture. */
    uint32_t                firstTs;
    /**< time stamp in ms for first frame. */
    float                   fps;
    /**< Running frames/second. */
};

/**
 *  \brief instance configurations.
 */
struct CsirxInstCfgInfo_t
{
    const uint32_t        instCfgInfoId;
    /**< Id of the instance configuration & info structure instance */
    const uint32_t        csiDrvInst;
    /**< CSIRX DRV instance. */
    const Csirx_InstCfg   *instCfg;
    /**< CSI Rx module configuration. */
    uint64_t        frameDropBuf;
    /**< Address of Frame Drop buffer,
      *  used when application has not queued any buffers
      *  If set to NULL (0), then driver will hold
      *  the last buffer for frame repeat */
    uint32_t        frameDropBufLen;
    /**< Frame Drop buffer length in bytes,
      *  used when application has not queued any buffers */
    const uint32_t        numCh;
    /**< Number of channels for given CSIRX DRV instance */
    const uint32_t        chCfgId[CSIRX_NUM_CH];
    /**< Pointer to CSIRX DRV channel configuration. */
};

/**
 *  \brief instance object.
 */
struct CsirxInstObj_t
{
    Csirx_InstStatus      instStatus;
    /**< Capture status structure used to get the current status */
    CsirxChObj            chObj[CSIRX_NUM_CH];
    /**< Channel configuration */
    Csirx_CreateStatus    createStatus;
    /**< Csirx create time status */
    Fvid2_CbParams        cbPrms;
    /**< Callback params. */
    SemaphoreP_Object     lockSem;
    /**< semaphore to indicate capture frame completion. */
    CsirxInstCfgInfo      *instCfgInfo;
    /**< Reference to instance configurations */
    Udma_DrvHandle        *drvHandle;
    /**< UDMA DRV Handle, will be updated during run, no need to
         provide to application */
};

/**
 *  \brief Structure used for CSIRX UT task configuration parameters.
 */
struct CsirxTestTaskCfg_t
{
    const uint32_t          taskCfgId;
    /**< Id of the test task obj */
    const uint32_t          instCfgId;
    /**< Pointer to CSIRX DRV instance configuration. */
    const CsirxTestFxnPtr   testFxnPtr;
    /**< Type of test case to run. */
    const uint32_t          taskId;
    /**< task Id */
};

/**
 *  \brief Structure used for CSIRX UT task object parameters.
 */
struct CsirxTestTaskObj_t
{
    CsirxTestTaskCfg        *taskCfg;
    /**< Pointer to CSIRX test task configuration. */
    CsirxInstObj            instObj;
    /**< Pointer to CSIRX DRV instance configuration. */
    Fvid2_Handle            drvHandle;
    /**< FVID2 capture driver handle. */
    int32_t                 testResult;
    /**< test result. */
    uint32_t                durationMs;
    /**< Time taken in ms */
    TaskP_Object            taskHandle;
    /**< task handle */
    SemaphoreP_Object       syncSem;
    /**< Semaphore to synch task start */
    CsirxTestParams         *testParams;
    /**< Reference to corresponding test parameters */
};

/**
 *  \brief Structure used for Sensor Configurations.
 */
struct CsirxSensorCfg_t
{
    uint32_t numDataLanes;
    /**< Number of data lanes used by the deserializer. */
    uint32_t numCh;
    /**< Number of channels/sensors to be configured. */
    uint32_t vcNum[CSIRX_NUM_CH];
    /**< virtual channel number of the sensors to be configured. */
    uint8_t usePatternGen;
    /**< Flag to use Pattern Generator for UB960 deserializer. */
    uint32_t frameWidth;
    /**< Frame width: Used in Pattern Generator of UB960 deserializer. */
    uint32_t frameHeight;
    /**< Frame height: Used in Pattern Generator of UB960 deserializer. */
    uint32_t dt;
    /**< Frame datatype: Used in Pattern Generator of UB960 deserializer. */
};

/**
 *  \brief Test case parameter structure.
 */
struct CsirxTestParams_t
{
    const bool              enableTest;
    /**< Whether test case should be executed or not. */
    const uint32_t          tcId;
    /**< Test case ID. */
    const char              *tcName;
    /**< Test case name. */
    const char              *disableInfo;
    /**< Reason string for disabling a test case. */
    const bool              printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    const bool              profilingEnable;
    /**< Enable Profiling prints. */
    const uint32_t          tcType;
    /**< Type of testcase  - like BFT, stress etc... */
    const uint32_t          dcEnable;
    /**< Enable/disable data check - used for performance. */
    const uint32_t          iterationCnt;
    /**< Count for iteration, how many times this test should be run. */

    const uint32_t          numTasks;
    /**< Number of tasks to test */
    const uint32_t          testType[CSIRX_TEST_MAX_TASKS];
    /**< Type of test, Refer enum #CsirxTestTypes */
    const uint32_t          taskCfgId[CSIRX_TEST_MAX_TASKS];
    /**< Id of the test task cfg */
    SemaphoreP_Object       taskCompleteSem;
    /**< Semaphore to indicate task completion */
    Csirx_InitParams        initPrms;
    /**< Csirx init time parameters */
    CsirxTestTaskObj        taskObj[CSIRX_TEST_MAX_TASKS];
    /**< CSIRX Test Task Object. This object is filled runtime.
         This is not a input parameter */

    /*
     * Below variables are initialized in code and not in table!!
     */
    bool                    isRun;
    /**< Flag to indicate whether the test case is run or not. */
    int32_t                 testResult;
    /**< Test result. */
};
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Parser functions
 */
int32_t csirxTestParser(void);
void CsirxUT_testPrint(const char *str, ...);
void udmaDrvPrint(const char *str);


/*
 * Parser functions
 */
int32_t Csirx_captureTest(CsirxTestTaskObj *taskObj);
void csirxTestLogTestResult(const CsirxTestParams *testParams,
                           int32_t                testResult,
                           uint32_t               testCaseId,
                           char                   *testcaseInfo);

void csirxTestPrintTestResult(const CsirxTestParams *testParams,
                             uint32_t           skipCount,
                             uint32_t           disableCount);

void csirxTestResetTestResult(void);
/*
 * CSIRX common functions
 */
void App_consolePrintf(const char *pcString, ...);
void App_fvidPrint(const char *str, ...);
void App_dmaPrint(const char *str);

void CsirxUT_testResetTestResult(void);
void CsirxUT_testCalcPerformance(CsirxTestTaskObj *taskObj,
                                 uint32_t durationMs);

char AppUtils_getChar(void);
int32_t AppUtils_getCharTimeout(char *ch, uint32_t msec);
int32_t AppUtils_getNum(void);

uint32_t AppUtils_getCurTimeInMsec(void);
uint32_t AppUtils_getElapsedTimeInMsec(uint32_t startTime);

/* cache APIs */
void AppUtils_cacheWbInv(const void * addr, uint32_t size);

int32_t App_setupI2CInst(void);
void App_closeI2CInst(void);
void App_wait(uint32_t wait_in_ms);

/**
 * \brief   App function to get current time in msec.
 *
 * \param   None.
 *
 * \retval  I2C instance setup status.
 */
uint32_t App_getCurTimeInMsec(void);

/**
 * \brief   App function to calculate the elapsed time from 'startTime' in msec.
 *
 * \param   None.
 *
 * \retval  I2C instance setup status.
 */
uint32_t App_getElapsedTimeInMsec(uint32_t startTime);
/* ========================================================================== */
/*      Internal Function Declarations (Needed for other static inlines)      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_TEST_H_ */
