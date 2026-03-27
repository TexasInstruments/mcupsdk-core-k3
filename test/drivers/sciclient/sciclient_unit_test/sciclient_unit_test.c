/*
 *  Copyright (C) 2021-2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <inttypes.h>
#include <string.h>
#if defined ENABLE_SCICLIENT_DIRECT
/* DM R5 will use the SCI Client direct */
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor Sciclient_TestEnables
 *  \name Sciclient Test Enable and Disable indexes
 *  @{
 *  Macros to enable or disable tests and printing.
 */
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)
/* @} */

/**
 *  \anchor Sciclient_ParserIds
 *  \name Sciclient Test case Parser Ids
 *  @{
 *  Parser ID used to identify the different test types.
 */
#define RUN_TEST_ID                 ('1')
#define RUN_TESTS_SANITY            ('2')
#define RUN_TESTS_REGRESSION        ('3')
#define RUN_TESTS_R5F               ('4')
#define RUN_TESTS_A53               ('5')
#define RUN_TESTS_ALL               ('A')
#define PRINT_ALLTESTS              ('d')
#define PRINT_TEST_ID               ('t')
#define PRINT_RESULTS               ('g')
#define PARSER_QUIT                 ('q')
/* @} */

#define App_sciclientGetChar UART_getc

#define APP_SCICLIENT_UT_AUTORUN 1

#define APP_PRINT_BUFFER_SIZE (256U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief CPU Id of the test to be run on.
 */
typedef enum
{
    APP_SCICLIENT_R5F = 0,
    /**< Select R5F for execution */
    APP_SCICLIENT_A53 = 1,
    /**< Select A53 for execution */
}App_sciclientCpuId;

/**
 *  \brief Test types.
 */
typedef enum
{
    APP_SCICLIENT_TEST_TYPE_SANITY      = 0x01,
    /**< Sanity testing */
    APP_SCICLIENT_TEST_TYPE_REGRESSION  = 0x02,
    /**< Regression testing */
    APP_SCICLIENT_TEST_TYPE_FULL        = 0x04,
    /**< Full testing */
    APP_SCICLIENT_TEST_TYPE_FUNCTIONAL  = 0x08,
    /**< Functional testing */
    APP_SCICLIENT_TEST_TYPE_STRESS      = 0x10,
    /**< Stress testing */
    APP_SCICLIENT_TEST_TYPE_NEGATIVE    = 0x20,
    /**< Negative testing */
    APP_SCICLIENT_TEST_TYPE_PERFORMANCE = 0x40,
    /**< Performance Testing */
    APP_SCICLIENT_TEST_TYPE_MISC        = 0x80,
    /**< Miscellaneous Testing */
    APP_SCICLIENT_TEST_TYPE_API         = 0x100
    /**< API testing */
} App_sciclientTestType;

/**
 * \brief Typedef for test case parameters.
 */
typedef struct App_sciclientTestParams App_sciclientTestParams_t;

/**
 * \brief Typedef for test case type function pointer.
 */
typedef void (*sciclientTestCaseFxnPtr)(App_sciclientTestParams_t *testPrms);

/**
 * \brief Typedef for test case configuration parameters.
 */
typedef struct
{

} App_sciclientTestConfigParams_t;

/**
 *  \brief Test case parameter structure.
 */
struct App_sciclientTestParams
{
    Bool                       enableTest;
    /**< Whether test case should be executed or not. */
    uint32_t                   testcaseId;
    /**< Test case ID. */
    char                      *reqId;
    /**< Requirements covered by this test case. */
    char                      *testCaseName;
    /**< Test case name. */
    char                      *userInfo;
    /**< Test case user Info. */
    char                      *disableReason;
    /**< Reason string for disabling a test case. */
    char                      *passFailCriteria;
    /**< Test case pass/fail criteria. */
    App_sciclientCpuId         cpuID;
    /**< Test case CPU ID field */
    App_sciclientTestConfigParams_t sciclientConfigParams;
    /**< Configuration parameters */
    Bool                       printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    uint32_t                   testType;
    /**< Refer #App_sciclientTestType */
    /*
     * Below variables are initialized in code and not in table!!
     */
    int32_t                    isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                      testResult;
    /**< Test result. */
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t  App_sciclientParser(void);
static uint32_t App_sciclientGetNumTests(void);
static int32_t  App_sciclientTestMain(App_sciclientTestParams_t *testParams);
static void App_sciclientResultInit(void);
static void App_sciclientShowMainMenu(void);
static void App_sciclientRun(App_sciclientTestParams_t *testParams);
static void App_sciclientPrintResults(void);
static void App_sciclientPrintTestName(void);

static int32_t App_getRevisionTestPol(void);
#if defined(ENABLE_INTERRUPT_TEST)
static int32_t App_getRevisionTestIntr(void);
#endif
static int32_t App_timeoutTest(void);
static int32_t App_invalidReqPrmTest(void);
#if defined(ENABLE_MSG_FWD)
static int32_t App_tifs2dmMsgForwardingTest(void);
#endif
static int32_t App_pmGetFrequency(void);
static int32_t App_pmSetFrequency(void);
static int32_t App_rmGetResourceRangeWithSecHost(void);
static int32_t App_getDMVersion(void);


#define SCICLIENT_NUM_TESTCASES   (sizeof (gSciclientTestcaseParams) / \
                                   sizeof (App_sciclientTestParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various SCICLIENT test cases. */
App_sciclientTestParams_t gSciclientTestcaseParams[] =
{
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        1U,
        /** *reqId **/
        "PDK-2142::PDK-2140::PDK-2139::PDK-2141",
        /** *testCaseName **/
        "SCICLIENT TIFS Get Firmware Version (Polled)",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient loads firmware and gets ACK after sending get revision\
         message to firmware without any error ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    },
#if defined(ENABLE_INTERRUPT_TEST)
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        2U,
        /** *reqId **/
        "PDK-2142::PDK-2140::PDK-2139::PDK-2141",
        /** *testCaseName **/
        "SCICLIENT TIFS Get Firmware Version (Interrupt)",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient loads firmware and gets ACK after sending get revision\
         message to firmware without any error ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    },
#endif
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        3U,
        /** *reqId **/
        "PDK-2490::PDK-2915::PDK-2907::PDK-2906",
        /** *testCaseName **/
        "SCICLIENT Check for Invalid Req Prm",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient_service should fail when \
         called with invalid parameters ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_NEGATIVE)
    },
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        4U,
        /** *reqId **/
        "PDK-2490::PDK-2915::PDK-2907::PDK-2906",
        /** *testCaseName **/
        "SCICLIENT Check Timeout",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient_service should fail with timeout when \
         called with invalid parameters ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_NEGATIVE)
    },
#if defined(ENABLE_MSG_FWD)
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        5U,
        /** *reqId **/
        "PDK:10418",
        /** *testCaseName **/
        "SCICLIENT TIFS2DM Message Forwarding Test",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient gets ACK and the DEV ID 0 state info, after sending get device\
         state message on a secure queue (to TIFS and then DM) without any error.",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    }
#endif
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        6U,
        /** *reqId **/
        "PDK:2145",
        /** *testCaseName **/
        "SCICLIENT RM Get Configuruation Test",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Sciclient_Get coniguration should return correctly for PG1.0 and PG2.0 ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    }
    ,{
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        7U,
        /** *reqId **/
        "PDK:XXX",
        /** *testCaseName **/
        "SCICLIENT PM Get Frequency Test",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Get Frequency for the particular clock ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        8U,
        /** *reqId **/
        "PDK:XXX",
        /** *testCaseName **/
        "SCICLIENT PM Set Frequency Test",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "Set Frequency for the particular clock ",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        TEST_ENABLE,
        /** testCaseId **/
        9U,
        /** *reqId **/
        "SYSFW-7448::PDK-17522",
        /** *testCaseName **/
        "SCICLIENT DM version api Test",
        /** *userInfo **/
        "None",
        /** *disableReason **/
        "None",
        /** *passFailCriteria **/
        "DM version api should Pass when called \
         with valid parameters and fail when called with invalid \
         parameters",
        /** cpuID **/
        APP_SCICLIENT_R5F,
        /** sciclientConfigParams **/
        {},
        /** printEnable **/
        PRINT_ENABLE,
        /** testType **/
        (APP_SCICLIENT_TEST_TYPE_SANITY)
    }
};


void sciclient_unit_test_main(void *args)
{
    /* UART driver should be open for terminal output via a call to
     * Drivers_open() before calling this function */

    App_sciclientParser();

    /* Board_driversClose() and Drivers_close() to follow after this function */
}

static uint32_t App_sciclientGetNumTests(void)
{
    return SCICLIENT_NUM_TESTCASES;
}

static int32_t App_sciclientTestMain(App_sciclientTestParams_t *testParams)
{
    switch (testParams->testcaseId)
    {
        case 1:
            testParams->testResult = App_getRevisionTestPol();
            break;
#if defined(ENABLE_INTERRUPT_TEST)
        case 2:
            testParams->testResult = App_getRevisionTestIntr();
            break;
#endif
        case 3:
            testParams->testResult = App_invalidReqPrmTest();
            break;
        case 4:
            testParams->testResult = App_timeoutTest();
            break;
#if defined(ENABLE_MSG_FWD)
        case 5:
            testParams->testResult = App_tifs2dmMsgForwardingTest();
            break;
#endif
        case 6:
            testParams->testResult = App_rmGetResourceRangeWithSecHost();
            break;
        case 7:
            testParams->testResult = App_pmGetFrequency();
            break;
        case 8:
            testParams->testResult = App_pmSetFrequency();
            break;
        case 9:
            testParams->testResult = App_getDMVersion();
            break;
        default:
            break;
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static int32_t App_getRevisionTestPol(void)
{
    int32_t status = CSL_PASS;
    struct tisci_msg_version_req request;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SystemP_WAIT_FOREVER
    };

    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    if (status == CSL_PASS)
    {
        status = Sciclient_service(&reqPrm, &respPrm);

        if (CSL_PASS == status)
        {
            if (respPrm.flags == TISCI_MSG_FLAG_ACK)
            {
                status = CSL_PASS;
                DebugP_log(
                                  " TIFS Firmware Version %s\n",
                                  (char *) response.str);
                DebugP_log(
                                  " Firmware revision 0x%x\n", response.version);
                DebugP_log(
                                  " ABI revision %d.%d\n", response.abi_major,
                                  response.abi_minor);
            }
            else
            {
                DebugP_log(
                                  " TIFS Firmware Get Version failed \n");
            }
        }
        else
        {
            DebugP_log(
                              " TIFS Firmware Get Version failed \n");
        }
    }
    return status;
}

#if defined(ENABLE_INTERRUPT_TEST)
static int32_t App_getRevisionTestIntr(void)
{
    int32_t status = CSL_PASS;

    struct tisci_msg_version_req request;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SystemP_WAIT_FOREVER
    };
    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    if (status == CSL_PASS)
    {
        status = Sciclient_service(&reqPrm, &respPrm);
        if (CSL_PASS == status)
        {
            if (respPrm.flags == TISCI_MSG_FLAG_ACK)
            {
                status = CSL_PASS;
                DebugP_log(
                                  " TIFS Firmware Version %s\n",
                                  (char *) response.str);
                DebugP_log(
                                  " Firmware revision 0x%x\n", response.version);
                DebugP_log(
                                  " ABI revision %d.%d\n", response.abi_major,
                                  response.abi_minor);
            }
            else
            {
                DebugP_log(
                                  " TIFS Firmware Get Version failed \n");
            }
        }
        else
        {
            DebugP_log(
                              " TIFS Firmware Get Version failed \n");
        }
    }
    return status;
}
#endif

static int32_t App_invalidReqPrmTest(void)
{
    int32_t status = CSL_PASS;

    struct tisci_msg_version_req request;
    const Sciclient_ReqPrm_t      reqPrm_badTxSize =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t*) &request,
        100,
        SystemP_WAIT_FOREVER
    };

    const Sciclient_ReqPrm_t      reqPrm_good =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t*)&request,
        0,
        SystemP_WAIT_FOREVER
    };

    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm_badRxsize =
    {
        0,
        (uint8_t *) &response,
        100
    };

    Sciclient_RespPrm_t           respPrm_good =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    if (status == CSL_PASS)
    {
        status = Sciclient_service(NULL, &respPrm_good);
        if ((SystemP_FAILURE == status)||(CSL_EBADARGS == status))
        {
            status = CSL_PASS;
            DebugP_log(" NULL Arg Test PASSED \n");
        }
        else
        {
            DebugP_log(" NULL Arg Test FAILED \n");
        }
        status = Sciclient_service(&reqPrm_badTxSize, &respPrm_good);
        if ((SystemP_FAILURE == status)||(CSL_EBADARGS == status))
        {
            status = CSL_PASS;
            DebugP_log(" Tx Payload Check PASSED \n");
        }
        else
        {
            DebugP_log(" Tx Payload Check FAILED \n");
        }
        status = Sciclient_service(&reqPrm_good, &respPrm_badRxsize);
        if ((SystemP_FAILURE == status)||(CSL_EBADARGS == status))
        {
            status = CSL_PASS;
            DebugP_log(" Rx Payload Check PASSED \n");
        }
        else
        {
            DebugP_log(" Rx Payload Check FAILED \n");
        }
    }
    return status;
}

static int32_t App_timeoutTest(void)
{
    int32_t status = CSL_PASS;
    struct tisci_msg_version_req request;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *)&request,
        sizeof(request),
        (uint32_t)0x0A
    };
    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0U,
        (uint8_t *) &response,
        sizeof (response)
    };

    if (status == CSL_PASS)
    {
        status = Sciclient_service(&reqPrm, &respPrm);
        if ((SystemP_TIMEOUT == status)||(CSL_ETIMEOUT == status))
        {
            status = CSL_PASS;
            DebugP_log(" Timeout test PASSED \n");
        }
        else
        {
            DebugP_log(" Timeout Test FAILED \n");
        }
    }
    return status;
}

#if defined(ENABLE_MSG_FWD)
static int32_t App_tifs2dmMsgForwardingTest(void)
{
    int32_t status = CSL_PASS;
    Sciclient_ConfigPrms_t        config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        1 /* isSecure = 1 to test passing message on secure channel */
    };

    DebugP_log(" Starting TIFS2DM msg forwarding test (from secure queue)\n");

    struct tisci_msg_get_device_req request;
    request.id = 0x1; /* Use DEV ID of 1 as a device to check state (any DEV ID will do) */
    const Sciclient_ReqPrm_t        reqPrm =
    {
        TISCI_MSG_GET_DEVICE,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SystemP_WAIT_FOREVER
    };

    struct tisci_msg_get_device_resp response;
    Sciclient_RespPrm_t              respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof(response)
    };
    /* This is only needed as this test case is running with a different config on mcu1_0
     */
    status = Sciclient_deinit();

    if (status == CSL_PASS)
    {
        status = Sciclient_init(&config);
    }

    if (status == CSL_PASS)
    {
        status = Sciclient_service(&reqPrm, &respPrm);
        if (CSL_PASS == status)
        {
            if ((respPrm.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK)
            {
                status = CSL_PASS;
                DebugP_log(
                                  " Device ID 0 - Context Loss Count: %d\n",
                                  response.context_loss_count);
                DebugP_log(
                                  "             - Resets: %d\n",
                                  response.resets);
                DebugP_log(
                                  "             - Programmed state: %d\n",
                                  response.programmed_state);
                DebugP_log(
                                  "             - Current state: %d\n",
                                  response.current_state);
            }
            else
            {
                DebugP_log(
                                  " Device ID 0 - Get device state failed \n");
            }
        }
        else
        {
            DebugP_log(
                              " Device ID 0 - Get device state failed \n");
        }
    }
    if (status == CSL_PASS)
    {
        status = Sciclient_deinit();
    }
    return status;
}
#endif

struct appSciclientRmGetRangeTest
{
    uint16_t           type;
    uint8_t            subtype;
    int32_t            expectedResult;
    int32_t            secondary_host;
};
struct appSciclientRmGetRangeTest gAppSciclientTstParams [] =
{
#if defined(SOC_AM62PX) || defined(SOC_J722S)
    {TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT, CSL_PASS, TISCI_HOST_ID_WKUP_0_R5_1},
    {TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT, CSL_PASS, TISCI_HOST_ID_WKUP_0_R5_1},
#else
    {TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT, CSL_PASS, TISCI_HOST_ID_MAIN_0_R5_1},
    {TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT, CSL_PASS, TISCI_HOST_ID_MAIN_0_R5_1},
#endif
    {TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, 32, CSL_PASS, 0},
    {(TISCI_RESASG_TYPE_MASK >>TISCI_RESASG_TYPE_SHIFT) + 1, TISCI_RESASG_SUBTYPE_IR_OUTPUT, CSL_EFAIL, 0},
    {TISCI_DEV_DMASS0_INTAGGR_0, (TISCI_RESASG_SUBTYPE_MASK >>TISCI_RESASG_SUBTYPE_SHIFT) + 1, CSL_EFAIL, 0}
};

static int32_t App_rmGetResourceRangeWithSecHost(void)
{
    int32_t status = CSL_PASS;
    uint32_t i = 0U;

    for (i = 0U; i < sizeof (gAppSciclientTstParams)/sizeof (struct appSciclientRmGetRangeTest); i++)
    {
        struct tisci_msg_rm_get_resource_range_resp res;
        struct tisci_msg_rm_get_resource_range_req  req;
        if (status == CSL_PASS)
        {
            req.type           = gAppSciclientTstParams[i].type;
            req.subtype        = gAppSciclientTstParams[i].subtype;
            if(gAppSciclientTstParams[i].secondary_host ==0){
                req.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
            }else{
               req.secondary_host = gAppSciclientTstParams[i].secondary_host;
            }

            /* Get interrupt number range */
            status =  Sciclient_rmGetResourceRange(
                        &req,
                        &res,
                        0xFFFFFFFFU);
        }
        if (status == CSL_PASS)
        {
            DebugP_log("\n\rType: %d, Subtype : %d, SecHost: %d, Start: %d, Num: %d, sec_stat: %d, sec_count: %d",
                                gAppSciclientTstParams[i].type,
                                gAppSciclientTstParams[i].subtype,
                                gAppSciclientTstParams[i].secondary_host,
                                res.range_start,
                                res.range_num,
                                res.range_start_sec,
                                res.range_num_sec);
        }
        else
        {
            if (status == gAppSciclientTstParams[i].expectedResult)
            {
                DebugP_log("\n\rType: %d, Subtype : %d, Expected Failure",
                                gAppSciclientTstParams[i].type,
                                gAppSciclientTstParams[i].subtype);
                status = CSL_PASS;
            }
            else
            {
                DebugP_log("\n\rType: %d, Subtype : %d, Unexpected Failure!!!!!!!",
                                gAppSciclientTstParams[i].type,
                                gAppSciclientTstParams[i].subtype);
            }
        }
    }

    return status;
}

static int32_t App_pmGetFrequency(void)
{
    int32_t status = CSL_PASS;

    if (status == CSL_PASS)
    {
        uint64_t freqHz;
        status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);


        if (CSL_PASS == status)
        {
            status = CSL_PASS;
            DebugP_log(" GTC Frequency  %lld\n", freqHz);
        }
        else
        {
            DebugP_log(" TIFS Firmware Get Frequency failed \n");
        }
    }
    return status;
}

static int32_t App_pmSetFrequency(void)
{
    int32_t status = CSL_PASS;

    if (status == CSL_PASS)
    {
        uint64_t freqHz;
        status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_MCU_I2C0, TISCI_DEV_MCU_I2C0_PISYS_CLK,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);

        if (CSL_PASS == status)
        {
            status = CSL_PASS;
            DebugP_log(" Current Frequency %lld\n", freqHz);
        }
        else
        {
            DebugP_log(" TIFS Firmware Get Frequency failed \n");
        }

        uint64_t targetFreHz = 0x02dc6c00;
        status = Sciclient_pmQueryModuleClkFreq(TISCI_DEV_MCU_I2C0, TISCI_DEV_MCU_I2C0_PISYS_CLK,targetFreHz,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);

        if (CSL_PASS == status)
        {
            status = CSL_PASS;
            DebugP_log(" Query Response Frequency %lld\n", freqHz);
        }
        else
        {
            DebugP_log(" TIFS Firmware Query Frequency failed \n");
        }


        status = Sciclient_pmSetModuleClkFreq(TISCI_DEV_MCU_I2C0, TISCI_DEV_MCU_I2C0_PISYS_CLK,
            freqHz,TISCI_MSG_FLAG_AOP,SystemP_WAIT_FOREVER);

        if (CSL_PASS == status)
        {
            status = CSL_PASS;
            DebugP_log(" Set  Frequency success\n");
        }
        else
        {
            DebugP_log(" TIFS Firmware Set Frequency failed \n");
        }

        status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_MCU_I2C0, TISCI_DEV_MCU_I2C0_PISYS_CLK,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);

        if (CSL_PASS == status)
        {
            status = CSL_PASS;
            DebugP_log(" New Frequency %lld\n", freqHz);
        }
        else
        {
            DebugP_log(" TIFS Firmware Get Frequency failed \n");
        }

    }
    return status;
}

static int32_t App_getDMVersion(void)
{
    int32_t status = CSL_EFAIL;

    struct tisci_msg_dm_version_req request;
    const Sciclient_ReqPrm_t reqPrm =
    {
        TISCI_MSG_DM_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SystemP_WAIT_FOREVER
    };

    struct tisci_msg_dm_version_resp response;
    Sciclient_RespPrm_t     respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    if (CSL_PASS == status)
    {
        DebugP_log(" Sciserver Version %s\n", (char *) response.sciserver_version);
        DebugP_log(" rm_pm_hal Version %s\n", (char *) response.rm_pm_hal_version);
        DebugP_log(" ABI revision %d.%d\n", response.abi_major, response.abi_minor);
    }
    else
    {
        DebugP_log(" DM Firmware Get Version failed \n");
    }

    return status;
}

static int32_t App_sciclientParser(void)
{
    uint32_t testcaseId;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    char     option;
    App_sciclientTestParams_t *testParams;
#if (APP_ENTER_TEST_CHOICE == 1)
    int32_t  testcaseIdx, testIp;
#endif

    App_sciclientResultInit();

    while (!done)
    {
        App_sciclientShowMainMenu();
#if (APP_SCICLIENT_UT_AUTORUN == 1)
        option = RUN_TESTS_ALL;
#elif (APP_ENTER_TEST_CHOICE == 1)
         DebugP_log( "\nEnter your choice: ");
         option = App_sciclientGetChar();
         DebugP_log( "%c\n", option);
#endif

        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
#if (APP_ENTER_TEST_CHOICE == 1)
            case RUN_TEST_ID:
                DebugP_log(
                                  "\nEnter testcase ID to run: ");
                testIp      = App_sciclientGetNum();
                testcaseIdx = App_sciclientGetIndex(testIp);
                if (testcaseIdx < 0)
                {
                    DebugP_log(
                                      "Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gSciclientTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gSciclientTestcaseParams[testcaseIdx];
                    if (APP_SCICLIENT_R5F == testParams->cpuID)
                    {
                        totalTCRun++;
                        App_sciclientRun(testParams);
                        if (CSL_PASS == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                }
                DebugP_log(
                                  "\nSCICLIENT: Total Testcases run:%u/%u\n",
                                  totalTCRun,
                                  App_sciclientGetNumTests());
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Passed:%u\n",
                                  numTCPass);
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Failed:%u\n",
                                  numTCFail);
                break;
#endif
            case RUN_TESTS_SANITY:
                for (testcaseId = 0;
                     testcaseId < App_sciclientGetNumTests();
                     testcaseId++)
                {
                    testParams = &gSciclientTestcaseParams[testcaseId];
                    if (TEST_ENABLE ==
                        testParams->enableTest)
                    {
                        if (APP_SCICLIENT_TEST_TYPE_SANITY ==
                            (testParams->testType & APP_SCICLIENT_TEST_TYPE_SANITY))
                        {
                            if (APP_SCICLIENT_R5F == testParams->cpuID)
                            {
                                totalTCRun++;
                                App_sciclientRun(testParams);
                                if (CSL_PASS == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                        }
                    }
                }
                DebugP_log(
                                  "\nSCICLIENT: Total Testcases run:%u/%u\n",
                                  totalTCRun,
                                  App_sciclientGetNumTests());
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Passed:%u\n",
                                  numTCPass);
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Failed:%u\n",
                                  numTCFail);
                App_sciclientPrintResults();
                break;
            case RUN_TESTS_ALL:
                for (testcaseId = 0;
                     testcaseId < App_sciclientGetNumTests();
                     testcaseId++)
                {
                    testParams = &gSciclientTestcaseParams[testcaseId];
                    if (TEST_ENABLE ==
                        testParams->enableTest)
                    {
                        totalTCRun++;
                        App_sciclientRun(testParams);
                        if (CSL_PASS == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                }
                DebugP_log(
                                  "\nSCICLIENT: Total Testcases run:%u/%u\n",
                                  totalTCRun,
                                  App_sciclientGetNumTests());
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Passed:%u\n",
                                  numTCPass);
                DebugP_log(
                                  "SCICLIENT: Number of Testcases Failed:%u\n",
                                  numTCFail);
                App_sciclientPrintResults();
                done = 1;
                break;
            case PRINT_ALLTESTS:
                App_sciclientPrintTestName();
                break;
#if (APP_ENTER_TEST_CHOICE == 1)
            case PRINT_TEST_ID:
                DebugP_log(
                                  "\nEnter testcase ID: ");
                testIp      = App_sciclientGetNum();
                testcaseIdx = App_sciclientGetIndex(testIp);
                if (testcaseIdx < 0)
                {
                    DebugP_log(
                                      "Invalid test case Id.");
                }
                else
                {
                    App_sciclientPrintTestDetails(testcaseIdx);
                }
                break;
#endif
            case PRINT_RESULTS:
                App_sciclientPrintResults();
                break;
            case PARSER_QUIT:
                DebugP_log(
                                  "Exiting Sciclient Test application.\n");
                done = 1;
                break;
            default: DebugP_log(
                    "Unsupported Option. Please try again.\n");
        }
        if (0U == numTCFail)
        {
            DebugP_log(
                              "\nAll tests have PASSED.\n");
        }
        else
        {
            DebugP_log(
                              "\nSome of the Test-cases have FAILED.\n");
        }

    }
    return 0;
}

#if (APP_ENTER_TEST_CHOICE == 1)
static int32_t App_sciclientGetIndex(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const App_sciclientTestParams_t *testParams;

    testParams = &gSciclientTestcaseParams[0u];
    for (testCnt = 0; testCnt < App_sciclientGetNumTests(); testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}
#endif

static void App_sciclientRun(App_sciclientTestParams_t *testParams)
{
    DebugP_log( "\n|TEST START|:: %u ::\n",
                      testParams->testcaseId);
    DebugP_log( "|TEST PARAM|:: %s ::\n",
                      testParams->testCaseName);
    DebugP_log( "|SR|:: %s ::\n",
                      testParams->reqId);

    DebugP_log(
        "--------------------------------------------------------------\n");
    DebugP_log(
        "=========================RUNNING==============================\n");
    App_sciclientTestMain(testParams);
    testParams->isRun = CSL_PASS;
    DebugP_log(
        "\n======================FINISHED==========================\n");
    if (testParams->testResult == 0U)
    {
        DebugP_log( "|TEST RESULT|PASS|%u|\n",
                          testParams->testcaseId);
    }
    else
    {
        DebugP_log( "|TEST RESULT|FAIL|%u|\n",
                          testParams->testcaseId);
    }
    DebugP_log( "|TEST INFO|:: %s ::\n",
                      testParams->testCaseName);
    DebugP_log( "|TEST END|:: %u ::\n",
                      testParams->testcaseId);
}

static void App_sciclientShowMainMenu(void)
{
    DebugP_log( "\n=====================\n");
    DebugP_log( "SCICLIENT UT Select\n");
    DebugP_log( "=======================\n");
    DebugP_log( "\nSCICLIENT UT main menu:\n");
    DebugP_log( "1: Manual testing (select specific test case to run)\n");
    DebugP_log( "2. Sanity testing.\n");
    DebugP_log( "d: Display test cases.\n");
    DebugP_log( "t: Display test case Details.\n");
    DebugP_log( "g: Generate test report.\n");
    DebugP_log( "q: Quit.\n");
}

static void App_sciclientPrintTestName(void)
{
    uint32_t loopCnt;
    const App_sciclientTestParams_t *testParams;

    DebugP_log( "SCICLIENT Testcase:\n");
    DebugP_log(
        "--------------------------------------------------------------\n");
    DebugP_log( "TC Id\tTC name\n");
    DebugP_log(
        "--------------------------------------------------------------\n");

    for (loopCnt = 0; loopCnt < App_sciclientGetNumTests(); loopCnt++)
    {
        testParams = &gSciclientTestcaseParams[loopCnt];
        DebugP_log( "%d\t%s\n",
                          testParams->testcaseId,
                          testParams->testCaseName);
    }

    DebugP_log(
        "--------------------------------------------------------------\n");
}

#if (APP_ENTER_TEST_CHOICE == 1)
static void App_sciclientPrintTestDetails(uint32_t testId)
{
    const App_sciclientTestParams_t *testParams;

    testParams = &gSciclientTestcaseParams[testId];
    DebugP_log( "\nTestcase Id : %d\n",
                      testParams->testcaseId);
    DebugP_log( "Testcase Name : %s",
                      testParams->testCaseName);
    DebugP_log( "\nTestcase Enabled(0-Disabled/1-Enabled) : %d",
                      testParams->enableTest);
    DebugP_log( "\nTestcase Req. Id : %s",
                      testParams->reqId);
    DebugP_log( "\nTestcase User Info. : %s",
                      testParams->userInfo);
    DebugP_log( "\nTestcase Disable Reason : %s",
                      testParams->disableReason);
    DebugP_log( "\nTestcase CPU ID : %d",
                      testParams->cpuID);
    DebugP_log( "\nTestcase Type : %d",
                      testParams->testType);
    DebugP_log( "\nTestcase Print Enable(0-Disabled/1-Enabled) : %d\n",
                      testParams->printEnable);
}
#endif

static void App_sciclientResultInit(void)
{
    uint32_t loopCnt;
    App_sciclientTestParams_t *testParams;

    for (loopCnt = 0; loopCnt < App_sciclientGetNumTests(); loopCnt++)
    {
        testParams             = &gSciclientTestcaseParams[loopCnt];
        testParams->isRun      = CSL_EFAIL;
        testParams->testResult = CSL_EFAIL;
    }
}

static void App_sciclientPrintResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    App_sciclientTestParams_t *testParams;
    char     testResult[10];

    DebugP_log(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    DebugP_log(
        "ID\t         Description\t\t\t                         Status\r\n");
    DebugP_log(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 0; loopCnt < App_sciclientGetNumTests(); loopCnt++)
    {
        testParams  = &gSciclientTestcaseParams[loopCnt];
        testcaseIdx = testParams->testcaseId;
        if (CSL_PASS == testParams->testResult)
        {
            strcpy(testResult, "PASS");
        }
        else if (CSL_PASS == testParams->isRun)
        {
            strcpy(testResult, "FAIL");
        }
        else
        {
            strcpy(testResult, "NRY");
        }

        DebugP_log("%d\t\t%s\t\t\t\t",
                   testcaseIdx, testParams->testCaseName);
        DebugP_log("%s\r\n", testResult);
    }

    DebugP_log(
        "\n-----------------------------------------------------------------------------------------------------------\r\n");
}

#if (APP_ENTER_TEST_CHOICE == 1)
static uint32_t App_sciclientGetNum()
{
    uint32_t number=0U, numberOfBytes=0U;
    char buffer[APP_PRINT_BUFFER_SIZE];
    numberOfBytes = UART_gets(buffer, APP_PRINT_BUFFER_SIZE);
    if (numberOfBytes != 0U)
    {
        sscanf(buffer, "%u", &number);
    }
    return number;
}
#endif
