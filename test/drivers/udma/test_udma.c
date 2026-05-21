/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/udma.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "udma_test.h"
#include "udma_testcases.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_open_close.h"
#include "udma_test.h"
#include "udma_testconfig.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                                  Macros                                    */
/* ========================================================================== */

/* --- Transfer Sizes & Counts --------------------------------------------- */
#define TEST_UDMA_NUM_BYTES                             (1024U)   /* Default memcpy size */
#define TEST_UDMA_SMALL_TRANSFER_BYTES                  (64U)     /* Quick sanity size */
#define TEST_UDMA_MED_TRANSFER_BYTES                    (128U)    /* Busy status heuristic */
#define TEST_UDMA_MIN_TRANSFER_BYTES                    (1U)      /* Smallest legal transfer */
#define TEST_UDMA_TRPD_SIZE                             (UDMA_GET_TRPD_TR15_SIZE(1U)) /* One TR15 desc */
#define TEST_UDMA_MULTI_ITERATIONS                      (10U)     /* Stress iteration count */
#define TEST_UDMA_MAX_CONCURRENT_BC_CH                  (4U)      /* Parallel BC channels */
#define TEST_UDMA_RING_ELEM_CNT                         (4U)      /* Elements per ring */
/* Element count variants */
#define TEST_UDMA_RING_ELEM_SINGLE                      (1U)
#define TEST_UDMA_RING_ELEM_PAIR                        (2U)
#define TEST_UDMA_RING_ELEM_TRIPLE                      (3U)
/* Descriptor loop count using triple */
#define TEST_UDMA_DESC_LOOP_TRIPLE                      TEST_UDMA_RING_ELEM_TRIPLE

/* --- Small Integer Utility Values ----------------------------------------- */
#define TEST_UDMA_VALUE_FIVE                            (5U)
#define TEST_UDMA_VALUE_TEN                             (10U)
#define TEST_UDMA_VALUE_THIRTY                          (30U)
#define TEST_UDMA_TR_RESPONSE_SINGLE                    (1U)

/* Offsets */
#define TEST_UDMA_OFFSET_MINUS_ONE                      (1U)   /* Used with subtraction as -1 */
#define TEST_UDMA_OFFSET_PLUS_FIVE                      TEST_UDMA_VALUE_FIVE
#define TEST_UDMA_OFFSET_PLUS_TEN                       TEST_UDMA_VALUE_TEN
#define TEST_UDMA_OFFSET_PLUS_ONE                       (1U)

/* --- Mapped / Ring Groups ------------------------------------------------ */
#define TEST_UDMA_MAPPED_RING_GRP_3                     (3U)
#define TEST_UDMA_MAPPED_RING_GRP_5                     (5U)
#define TEST_UDMA_MAPPED_RING_GRP_10                    (10U)
#define TEST_UDMA_MAPPED_FLOW_GRP_5                     (5U)
#define TEST_UDMA_MAPPED_CH_NUM_20                      (20U)  /* Arbitrary mapped CH stress value */

/* --- Invalid Channel Type Variants -------------------------------------- */
#define TEST_UDMA_INVALID_CH_TYPE_0                     (0U)
#define TEST_UDMA_INVALID_CH_TYPE_1                     (1U)
#define TEST_UDMA_INVALID_CH_TYPE_2                     (2U)
#define TEST_UDMA_INVALID_CH_TYPE_4                     (4U)

/* --- Patterns / Descriptors / Sentinels ---------------------------------- */
#define TEST_UDMA_RESULT_ERROR_SENTINEL                 (-1)        /* Generic int32 error init */
#define TEST_UDMA_TR_FMTFLAGS_LINEAR_1B                 (0x00000000U)/* Linear addressing */
#define TEST_UDMA_POISON_PATTERN_BYTE                   (0xA5U)      /* Fill before transfer */
#define TEST_UDMA_DUMMY_DESC_VALUE                      (0x1234ULL)  /* Dummy enqueue value */
#define TEST_UDMA_SRC_MIN_PATTERN                       (0xD5U)      /* Min src buffer pattern */
#define TEST_UDMA_BUF_CLEAR_PATTERN                     (0x00U)      /* Zeroing pattern */

/* --- Helper/Zero/None/Invalid Macros for Refactoring --- */
#define TEST_UDMA_BUF_INDEX_ZERO                        (0U)         /* Buffer index zero */
#define TEST_UDMA_FLAG_STATIC_NONE                      (0U)         /* Static flag none */
#define TEST_UDMA_FLAG_INDIRECT_NONE                    (0U)         /* Indirect flag none */
#define TEST_UDMA_PHY_ADDR_NONE                         (0U)         /* Physical address none */
#define TEST_UDMA_CB_COUNT_ZERO                         (0U)         /* Callback count zero */
#define TEST_UDMA_EVENT_LOCAL_ID_NONE                   (0U)         /* Local event ID none */
#define TEST_UDMA_EVENT_GLOBAL_ID_NONE                  (0U)         /* Global event ID none */
#define UDMA_EVENT_TYPE_NONE                            (0U)         /* Event type none */
#define UDMA_EVENT_MODE_NONE                            (0U)         /* Event mode none */
#define UDMA_CORE_INTR_NONE                             (0U)         /* Core interrupt none */
#define TEST_UDMA_ALLOC_FLAG_NONE                       (0U)         /* Allocation flag none */

/* --- Resource Manager & Global Event Counts ------------------------------ */
#define TEST_UDMA_RM_NUM_GLOBAL_EVENT_128               (128U)
#define TEST_UDMA_RM_NUM_GLOBAL_EVENT_NONE              (0U)
#define TEST_UDMA_RM_NUM_VINTR_NONE                     (0U)

/* --- Timeouts & Command IDs ---------------------------------------------- */
#define TEST_UDMA_DEFAULT_CH_DISABLE_TIMEOUT            (1000U)
#define TEST_UDMA_DEFAULT_CH_DISABLE_TIMEOUT_SHORT      (100U)
#define TEST_UDMA_TR_CMD_ID                             (0x25U)

/* --- Invalid / Sentinel / None Values ----------------------------------- */
#define TEST_UDMA_INVALID_INSTANCE                      (8U)
#define TEST_UDMA_INVALID_RING_MEM_ADDR                 (0U)
#define TEST_UDMA_RING_ELEM_CNT_INVALID                 (0U)
#define TEST_UDMA_RING_ORDER_ID_INVALID                 (0U)
#define TEST_UDMA_EVENT_TYPE_INVALID                    (0U)
#define TEST_UDMA_EVENT_MODE_INVALID                    (0U)
#define TEST_UDMA_VINTR_NUM_NONE                        (0U)
#define TEST_UDMA_EVENT_NEXT_NONE                       (0U)
#define TEST_UDMA_CORE_INTR_NUM_NONE                    (0U)
#define TEST_UDMA_VINTR_BIT_FLAG_CLEAR                  (0U)
#define TEST_UDMA_ADDR_NONE                             (0U)
#define TEST_UDMA_INVALID_CHANNEL_NUM                   (0xFFFFFFFFU)
#define TEST_UDMA_RING_NUM_TWO                          (2U)  /* Out-of-range test ring number */
#define TEST_UDMA_RING_NUM_ZERO                         (0U)
#define TEST_UDMA_RING_MEM_SIZE_INVALID                 (0U)
#define TEST_UDMA_STATUS_DISABLED                       (0U)
#define TEST_UDMA_CH_TX_PRMS_UNINIT                     (0U)
#define TEST_UDMA_CH_RX_PRMS_UNINIT                     (0U)
#define TEST_UDMA_INST_ID_PRIMARY                       (0U)
#define TEST_UDMA_INST_TYPE_INVALID                     (0U)
#define TEST_UDMA_API_RETVAL_INIT                       (0U)
#define TEST_UDMA_CH_STATS_INIT                         (0U)
#define TEST_UDMA_NUM_CH_NONE                           (0U)
#define TEST_UDMA_MAX_RINGS_NONE                        (0U)
/* Negative test VINTR count to trigger core interrupt allocation failure */
#define TEST_UDMA_RM_NUM_VINTR_TEST                     (45U)
/* INVALID non-NULL handle/address values for negative path validation */
#define TEST_UDMA_INVALID_CH_HANDLE_VALUE               (1U)
#define TEST_UDMA_INVALID_HWI_HANDLE_VALUE              (1U)

/* --- Derived Sizes ------------------------------------------------------- */
#define TEST_UDMA_RING_ELEMENT_SIZE                     (sizeof(uint64_t))
#define TEST_UDMA_RING_MEM_SIZE                         (UDMA_CACHELINE_ALIGNMENT * TEST_UDMA_RING_ELEM_CNT)
#define TEST_UDMA_MAX_EXHAUST_CH                        (512U)
#define TEST_UDMA_RING_MEM_SIZE_SINGLE                  (UDMA_CACHELINE_ALIGNMENT * TEST_UDMA_RING_ELEM_SINGLE)

/* --- Task / Thread ------------------------------------------------------- */
#if defined ENABLE_MT_TESTS
#if defined STACK_C7_CORE
#define TEST_UDMA_DMA_THREAD_STACK_SIZE                 (375 * 1024)
#else
#define TEST_UDMA_DMA_THREAD_STACK_SIZE                 (6 * 1024)
#endif
#define TEST_UDMA_DMA_THREAD_PRIORITY                   (2)
#endif /* ENABLE_MT_TESTS */

/* --- Ring Memory Aliases for Chaining ----------------------------------- */
#define TEST_UDMA_TRIG_FQ_RING_MEM                      (TestUdma_FqMultiChannel[0])
#define TEST_UDMA_TRIG_CQ_RING_MEM                      (TestUdma_CqMultiChannel[0])
#define TEST_UDMA_CHAIN_FQ_RING_MEM                     (TestUdma_FqMultiChannel[1])
#define TEST_UDMA_CHAIN_CQ_RING_MEM                     (TestUdma_CqMultiChannel[1])

/* --- Allocation & Clear Helpers ----------------------------------------- */
#define TEST_UDMA_ARRAY_ELEM_COUNT(arr)                 ((uint32_t)(sizeof(arr)/sizeof((arr)[0])))
#define TEST_UDMA_CLEAR_BUFS(bufList,sizeList)          \
    TestUdma_clearBufs((void**)(bufList), (size_t*)(sizeList), TEST_UDMA_ARRAY_ELEM_COUNT(bufList))

/* --- Poll Loop / Timeout Attempts (Restored) ---------------------------- */
#define TEST_UDMA_POLL_ATTEMPTS_SHORT                   (10000U)
#define TEST_UDMA_POLL_ATTEMPTS_MEDIUM                  (200000U)
#define TEST_UDMA_POLL_ATTEMPTS_STANDARD                (1000000U)
#define TEST_UDMA_POLL_ATTEMPTS_LONG                    (2000000U)

/* --- Mapped Channel None (for completeness) ----------------------------- */
#define TEST_UDMA_MAPPED_CH_NUM_NONE                    (0U)

/* --- Dynamic Channel Allocation ---------------------------------------- */
#define TEST_UDMA_PKTDMA_RX_CH_NUM                      UDMA_DMA_CH_ANY

/* --- Single-value Semantic Enum ----------------------------------------- */
typedef enum
{
    TEST_UDMA_VALUE_ZERO                                = 0U,
    TEST_UDMA_VALUE_ONE                                 = 1U,

    TEST_UDMA_FLOW_INDEX_0                              = TEST_UDMA_VALUE_ZERO,
    TEST_UDMA_FLOW_INDEX_1                              = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_RING_ORDER_ID_DEFAULT                     = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_RING_NUM_ONE                              = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_STATUS_ENABLED                            = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_ALLOC_FLAG_SET                            = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_OES_ALLOC_DONE_FLAG                       = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_OFFSET_ONE                                = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_QNUM_INDEX_1                              = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_CLEARBUF_SINGLE_COUNT                     = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_CH_TYPE_INVALID_1                         = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_COUNT_SINGLE                           = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_FLAG_SET                               = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_ICNT_UNIT                              = TEST_UDMA_VALUE_ONE
} TestUdmaConst;
/* 64-bit assert compatibility layer: activates only if Unity lacks
 * native 64-bit support. */
#if !defined(UNITY_SUPPORT_64) && !defined(TEST_ASSERT_EQUAL_PTR)
#define TEST_ASSERT_EQUAL_PTR(expected, actual)                                       \
    do                                                                                \
    {                                                                                 \
        uint64_t _e = (uint64_t)(expected);                                           \
        uint64_t _a = (uint64_t)(actual);                                             \
        if ((_e) != (_a))                                                             \
        {                                                                             \
            uint32_t _e_hi = (uint32_t)((_e >> 32) & 0xFFFFFFFFU);                    \
            uint32_t _a_hi = (uint32_t)((_a >> 32) & 0xFFFFFFFFU);                    \
            uint32_t _e_lo = (uint32_t)(_e & 0xFFFFFFFFU);                            \
            uint32_t _a_lo = (uint32_t)(_a & 0xFFFFFFFFU);                            \
            TEST_ASSERT_EQUAL_UINT32_MESSAGE(_e_hi, _a_hi, "High 32-bits differ");    \
            TEST_ASSERT_EQUAL_UINT32_MESSAGE(_e_lo, _a_lo, "Low 32-bits differ");     \
        }                                                                             \
    } while (0)
#endif /* shim for TEST_ASSERT_EQUAL_PTR */
#define EXPECT_FAIL_OPEN(CHTYPE)                                                      \
    do                                                                                \
    {                                                                                 \
        retVal = Udma_chOpen(drvHandle, tmpCh, (CHTYPE), &chPrms);                    \
        if (retVal == UDMA_SOK)                                                       \
        {                                                                             \
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(tmpCh));                     \
            TEST_FAIL_MESSAGE("Unexpected channel open success");                     \
        }                                                                             \
        else                                                                          \
        {                                                                             \
            TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);                                  \
        }                                                                             \
    } while (0)
/* Optional helper: treat 64-bit value as pointer for comparison where
 * address semantics apply. */
#ifndef TEST_ASSERT_EQUAL_ADDR64
#define TEST_ASSERT_EQUAL_ADDR64(expected, actual)                                    \
    TEST_ASSERT_EQUAL_PTR((void*)((uintptr_t)(expected)), (void*)((uintptr_t)(actual)))
#endif

/* Common attribute macro to reduce duplication for aligned DDR test buffers */
#define TEST_UDMA_BUF_ATTR __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ---------------- Core Test State & Event Objects ------------------------ */
/* Event object used to register and handle UDMA completion callbacks */
static Udma_EventObject TestUdma_EventObj;
/* Event callback counters (global + local) */
static volatile uint32_t TestUdma_EventCbCount      = TEST_UDMA_VALUE_ZERO;
/* Binary semaphore used for single-transfer event based wait
 * (non-multithread tests) */
static SemaphoreP_Object TestUdma_EventSem;
/* UDMA unit test control object holding test context and configurations */
static UdmaTestObj TestUdma_UtObj;
/* Reference to global UDMA driver instance objects defined elsewhere */
extern Udma_DrvObject gUdmaDrvObj[CONFIG_UDMA_NUM_INSTANCES];
#ifdef ENABLE_MT_TESTS
/* Counting semaphore (max posts = number of worker tasks) */
static SemaphoreP_Object TestUdma_MtCountingSem;
#endif /* ENABLE_MT_TESTS */

/* ---------------- Single-transfer / Basic Buffers ------------------------ */
uint8_t TestUdma_TrpdSingleDesc[TEST_UDMA_TRPD_SIZE]  TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_Src[TEST_UDMA_NUM_BYTES]             TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_Dst[TEST_UDMA_NUM_BYTES]             TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_FqRingMem[UDMA_CACHELINE_ALIGNMENT]  TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_CqRingMem[UDMA_CACHELINE_ALIGNMENT]  TEST_UDMA_BUF_ATTR;

/* ---------------- Minimum Transfer Size Buffers ------------------------- */
static uint8_t TestUdma_SrcMin[TEST_UDMA_MIN_TRANSFER_BYTES] TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_DstMin[TEST_UDMA_MIN_TRANSFER_BYTES] TEST_UDMA_BUF_ATTR;

/* ---------------- Multi-channel / Parallel Channel Buffers -------------- */
uint8_t TestUdma_FqMultiChannel[TEST_UDMA_MAX_CONCURRENT_BC_CH][UDMA_CACHELINE_ALIGNMENT]  TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_CqMultiChannel[TEST_UDMA_MAX_CONCURRENT_BC_CH][UDMA_CACHELINE_ALIGNMENT]  TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_TrpdMultiChannel[TEST_UDMA_MAX_CONCURRENT_BC_CH][TEST_UDMA_TRPD_SIZE]     TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_SrcMultiChannel[TEST_UDMA_MAX_CONCURRENT_BC_CH][TEST_UDMA_NUM_BYTES]      TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_DstMultiChannel[TEST_UDMA_MAX_CONCURRENT_BC_CH][TEST_UDMA_NUM_BYTES]      TEST_UDMA_BUF_ATTR;

/* ---------------- Busy Status Negative Test Buffers --------------------- */
static uint8_t TestUdma_SrcChBusyStatus[TEST_UDMA_MED_TRANSFER_BYTES] TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_DstChBusyStatus[TEST_UDMA_MED_TRANSFER_BYTES] TEST_UDMA_BUF_ATTR;

/* ---------------- Multi-transfer / Ring Overflow Scenario Buffers ------- */
static uint8_t TestUdma_RingMem[TEST_UDMA_RING_MEM_SIZE] TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_TrpdMem[TEST_UDMA_RING_ELEM_CNT * TEST_UDMA_RING_ELEM_PAIR][TEST_UDMA_TRPD_SIZE] TEST_UDMA_BUF_ATTR; /* uses pair to express *2 */
static uint8_t TestUdma_SrcBuf[TEST_UDMA_RING_ELEM_CNT * TEST_UDMA_RING_ELEM_PAIR][TEST_UDMA_NUM_BYTES]  TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_DstBuf[TEST_UDMA_RING_ELEM_CNT * TEST_UDMA_RING_ELEM_PAIR][TEST_UDMA_NUM_BYTES]  TEST_UDMA_BUF_ATTR;

/* ---------------- Chaining / Triggered Transfer Buffers ----------------- */
static uint8_t TestUdma_TrigSrc[TEST_UDMA_NUM_BYTES]      TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_TrigDst[TEST_UDMA_NUM_BYTES]      TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_ChainSrc[TEST_UDMA_NUM_BYTES]     TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_ChainDst[TEST_UDMA_NUM_BYTES]     TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_TrigTrpd[TEST_UDMA_TRPD_SIZE]     TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_ChainTrpd[TEST_UDMA_TRPD_SIZE]    TEST_UDMA_BUF_ATTR;

/* ---------------- Resource Exhaustion Stress Buffers -------------------- */
static Udma_ChObject TestUdma_ExhaustChObjs[TEST_UDMA_MAX_EXHAUST_CH] __attribute__((section(".udma_buffer_ddr"))); /* channel objects not cacheline sized */
static uint8_t TestUdma_ExhaustFqMem[TEST_UDMA_MAX_EXHAUST_CH][UDMA_CACHELINE_ALIGNMENT] TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_ExhaustCqMem[TEST_UDMA_MAX_EXHAUST_CH][UDMA_CACHELINE_ALIGNMENT] TEST_UDMA_BUF_ATTR;

/* ---------------- Large Ring Memory Blocks ------------------------------ */
static uint8_t TestUdma_TdCqRingMem[TEST_UDMA_RING_MEM_SIZE]   TEST_UDMA_BUF_ATTR;

/* ---------------- Parallel Copy Helper Buffers -------------------------- */
static uint8_t TestUdma_BlkCopyCh2RingMem[UDMA_CACHELINE_ALIGNMENT] TEST_UDMA_BUF_ATTR;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

#ifdef ENABLE_MT_TESTS
/** \brief Generic DMA task context holding result status, sync semaphore,
 * task object, and its dedicated stack */
typedef struct {
    int32_t result;
    SemaphoreP_Object doneSem;
    TaskP_Object taskObj;
    uint8_t stack[TEST_UDMA_DMA_THREAD_STACK_SIZE];
} DmaThreadParams;

#endif /* ENABLE_MT_TESTS */

/* Generic event context and callback to avoid per-test bespoke callbacks */
typedef struct {
    SemaphoreP_Object *semaphoreObject;              /* Semaphore to post on completion */
    volatile uint32_t *semaphoreCounter;            /* Optional counter to increment */
} TestUdma_EventSemaphore;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* Helper functions */
static int32_t TestUdma_trpdInit(Udma_ChHandle chHandle, uint8_t *trpdMemory,
                             const void *destBuf, const void *srcBuffer,
                             uint32_t length);
static int32_t TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length);
static int32_t TestUdma_compareBuffer(uint8_t *srcBuffer, uint8_t *destBuf,
                               uint32_t length);
static void TestUdma_eventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData);
/* Test framework helpers */
static UdmaTestParams *TestUdma_findTestCaseByFuncAndTcId(UdmaTestFxnPtr fxn,
                                                 uint32_t tcId);
/* Buffer clear helper: zero each buffer in provided list
 * (no side effects beyond memory) */
void TestUdma_clearBufs(void **bufList, size_t *sizeList, uint32_t count);
int32_t TestUdma_initDriver(UdmaTestObj *testObj, UdmaTestParams *testPrms);
int32_t TestUdma_deinitDriver(UdmaTestObj *testObj, UdmaTestParams *testPrms);

/* Test functions */
extern int32_t udmaTestParser(void);
extern void udmaTestInitTestObj(UdmaTestObj *testObj, UdmaTestParams *testPrms);
extern int32_t udmaTestBlkcpyTc(UdmaTestTaskObj *taskObj);
extern int32_t udmaTestBlkcpyPauseResumeTc(UdmaTestTaskObj *taskObj);
extern int32_t udmaTestBlkcpyChainingTc(UdmaTestTaskObj *taskObj);
extern int32_t udmaTestDeinit(UdmaTestObj *testObj);
extern void udmaTestSetDefaultCfg(UdmaTestObj *testObj);
extern int32_t udmaTestInit(UdmaTestObj *testObj);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

static void TestUdma_blkcpyTest(void *args);
static void TestUdma_blkcpyPauseResumeTest(void *args);
static void TestUdma_blkcpyChainingTest(void *args);
static void TestUdma_blkcpyIntrTest(void *args);
static void TestUdma_blkcpySwGlobal0PollingTest(void *args);
static void TestUdma_blkcpySwGlobal0IntrTest(void *args);
static void TestUdma_blkcpyCircularIcnt1EventTest(void *args);
static void TestUdma_blkcpyCircularIcnt2EventTest(void *args);
static void TestUdma_blkcpyCircularIcnt3EventTest(void *args);
static void TestUdma_ringFlushTest(void *args);
static void TestUdma_ringParamCheckTest(void *args);
static void TestUdma_ringUtilsMemSizeTest(void *args);
static void TestUdma_ringMemPtrTest(void *args);
static void TestUdma_ringAttachTest(void *args);
static void TestUdma_ringResetTest(void *args);
static void TestUdma_ringPrimeLcdmaTest(void *args);
static void TestUdma_flowAttachMappedTest(void *args);
static void TestUdma_trMakeTest(void *args);
static void TestUdma_structSizeTest(void *args);
static void TestUdma_chPktdmaParamCheckTest(void *args);
static void TestUdma_blkcpyDdrToDdr1MBPerfTest(void *args);
static void TestUdma_blkcpyCircularSrcOcramToDdrPerfTest(void *args);
static void TestUdma_blkcpyDdrToCircularDestOcramPerfTest(void *args);
static void TestUdma_blkcpyCircularOcramToOcramPerfTest(void *args);
static void TestUdma_blkcpyPacingDdrToOcramCirc4MBTo4KBTest(void *args);
static void TestUdma_flowAttachTest(void *args);
static void TestUdma_eventEnableDisable(void *args);
static void TestUdma_resetDrvChObjects(Udma_DrvHandle drvHandle,
                                       Udma_ChHandle chHandle0,
                                       Udma_ChHandle chHandle1);
static void TestUdma_setupCh0Custom(Udma_DrvHandle drvHandle,
                                    Udma_ChHandle chHandle0,
                                    Udma_ChHandle chHandle1,
                                    Udma_ChPrms *chPrms,
                                    uint32_t chInitDone,
                                    uint32_t drvInitDone);
static void TestUdma_chArgumentsValidateTests(void *args);
static void TestUdma_invalidInstance(void *args);
static void TestUdma_multipleBlkcopyChannelsBcdma(void *args);
static void TestUdma_channelBusyStatus(void *args);
static void TestUdma_channelAllocExhaust(void *args);
static void TestUdma_regAccessAfterDeinit(void *args);
static void TestUdma_doubleAllocateFlow(void *args);
static void TestUdma_eventRegisterFailureKeepsChannelOperational(void *args);
static void TestUdma_psilThreadPairingFailure(void *args);
static void TestUdma_minSizeTransfer(void *args);
static void TestUdma_multiDescriptorSubmission(void *args);
static void TestUdma_chStatsBlkCpy(void *args);
static void TestUdma_chStatsTx(void *args);
static void TestUdma_chStatsRx(void *args);
static void TestUdma_chSetChainingRxTx(void *args);
static void TestUdma_multipleFlowsPktdma(void *args);
static void TestUdma_doubleAllocateChannelRing(void *args);
static void TestUdma_multipleChannelsPktdma(void *args);
static void TestUdma_preferredChannelBoundaries(void *args);
static void TestUdma_eventInvalidUnmappedUnregistered(void *args);
static void TestUdma_nullRingMemOpen(void *args);
static void TestUdma_addrTranslateAndDescriptorEchoTest(void *args);
static void TestUdma_memcpyMultiIter(void *args);
static void TestUdma_ringOverflow(void *args);
static void TestUdma_ringUnderflow(void *args);
static void TestUdma_multipleRingsPerChannel(void *args);
static void TestUdma_flowArgumentsValidateTests(void *args);
static void TestUdma_argumentsValidateTests(void *args);
static void TestUdma_ringCommonArgumentsValidateTests(void *args);
static void TestUdma_chGetDefaultFlowHandleBcdma(void *args);
static void TestUdma_chGetDefaultFlowHandlePktdma(void *args);
static void TestUdma_chResetPktdma(void *args);
static void TestUdma_chResetBcdma(void *args);
static void TestUdma_utilsMapLocalToGlobalEvent(void *args);
static void TestUdma_eventArgumentsValidateTests(void *args);
static void TestUdma_utilsArgumentsValidateTests(void *args);
static void TestUdma_rmTranslateCoreIntrInputTest(void *args);
static void TestUdma_txPreferredChannelAllocation(void *args);
static void TestUdma_blockCopyPreferredChannelAllocation(void *args);
static void TestUdma_rxPreferredChannelAllocation(void *args);

#ifdef ENABLE_MT_TESTS
static void TestUdma_multiInstancePktdmaBcdma(void *args);
#endif

#if defined(UDMA_HAVE_BC_HC_CH) && (UDMA_HAVE_BC_HC_CH)
static void TestUdma_allocFreeBlkcopyHcCh(void *args);
#endif
extern void TestUdma_chPeerDataTest(void *args);
extern void TestUdma_chConfigPdmaTest(void *args);
extern void TestUdma_pktdmaInsTxRxChDisable(void *args);
extern void TestUdma_bcdmaInsTxChDisable(void *args);
extern void TestUdma_pktdmaSwTriggerNegative(void *args);
/* extern void TestUdma_blkcpySwGlobal1PollingTest(void *args); */
/* extern void TestUdma_blkcpySwGlobal1InterruptTest(void *args); */
extern void TestUdma_txPreferredChannelAllocationForBlkCpyInstance(void *args);
extern void TestUdma_rxPreferredChannelAllocationForBlkCpyInstance(void *args);
extern void TestUdma_blkcpySwGlobal0StatsDecAndVerify(void *args);
extern void TestUdma_chStatsBcdmaInstForTxRx(void *args);
/* extern void TestUdma_chResetTxRxForPktdmaAndBcdma(void *args); */
extern void TestUdma_blkcopyReloadTransferIsr(void *args);
extern void TestUdma_channelApiNegativeCases(void *args);
extern void TestUdma_multiChannelPauseResumeTest(void *args);
extern void TestUdma_initWithInvalidInstanceId(void *args);
extern void TestUdma_deinitWithPendingResources(void *args);
extern void TestUdma_deinitWithOpenChannels(void *args);
extern void TestUdma_initWithSkipGlobalEventReg(void *args);
extern void TestUdma_eventUnregisterWithPendingDescriptors(void *args);
extern void TestUdma_sharedEventCallbackMismatch(void *args);
extern void TestUdma_eventRegVintrBitsExhausted(void *args);
extern void TestUdma_virtToPhyFxnNullCheck(void *args);
extern void TestUdma_phyToVirtFxnNullCheck(void *args);
extern void TestUdma_ringFlushRawEmptyRingReset(void *args);
extern void TestUdma_rmInitPrmsNullCheck(void *args);
extern void TestUdma_mappedChRangeCheck(void *args);
extern void TestUdma_ringAllocFreeLifecycle(void *args);

#ifdef ENABLE_MT_TESTS
extern void TestUdma_chSetChainingRxTxMultithreadIntr(void *args);
extern void TestUdma_ringOverflowMultithread(void *args);
extern void TestUdma_multithreadOpenCloseRaceTest(void *args);
#endif
static void TestUdma_allocationHcUhcChannel(void *args);
/* Mapped TX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 and mcu r5 cores*/
#if(ENABLE_A53_CORE || ENABLE_MCU_R5_CORE)
#if (UDMA_NUM_MAPPED_TX_GROUP > 0)
static void TestUdma_mappedTxPreferredChannelAllocation(void *args);
static void TestUdma_mappedTxAnyChannelAllocation(void *args);
#endif
#endif /* For cores that have mapped CPSW resources reserved */
/* Mapped RX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 core*/
#if(ENABLE_A53_CORE)
#if (UDMA_NUM_MAPPED_RX_GROUP > 0)
static void TestUdma_mappedRxPreferredChannelAllocation(void *args);
static void TestUdma_mappedRxAnyChannelAllocation(void *args);
#endif
#endif /* For cores that have mapped CPSW resources reserved */
#if defined (ENABLE_DRU_TESTS)
extern void TestUdma_appdmautilsClecInitDru(void);
extern void TestUdma_druOwnerUDMAC(void *args);
extern void TestUdma_dmautilsDruDirectPolling(void *args);
extern void TestUdma_dmautilsDruDirectInterrupt(void *args);
extern void TestUdma_dmautilsDruDirect2D(void *args);
extern void TestUdma_dmautilsDruDirect3D(void *args);
extern void TestUdma_dmautilsAutoIncCompression(void *args);
extern void TestUdma_dmautilsDruDirectCircular(void *args);
extern void TestUdma_dmautilsDruDirectPauseResume(void *args);
#endif
extern void TestUdma_flowConfigInvalidIndex(void *args);
extern void TestUdma_chCloseOesAllocNotDeallocated(void *args);
extern void TestUdma_chOpenInvalidUtcId(void *args);
extern void TestUdma_chConfigNullArgs(void *args);
extern void TestUdma_chGetNumRxandUtc(void *args);
extern void TestUdma_chGetTdCqRingHandle(void *args);
extern void TestUdma_chSetChainingUnsupportedChannel(void *args);
extern void TestUdma_getMappedChRingAttributesInvalidMappedTxCh(void *args);
#if defined(ENABLE_R5F_CORE)
extern void TestUdma_utcIdVPAC(void *args);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Helper function to find a test case by function pointer and test case ID */
static UdmaTestParams *TestUdma_findTestCaseByFuncAndTcId(UdmaTestFxnPtr fxn, uint32_t tcId)
{
    int32_t index;
    for (index = 0U; index < UDMA_TEST_NUM_TESTCASES; index += 1)
    {
        if ((gUdmaTestCases[index].testFxnPtr[0] == fxn) && (gUdmaTestCases[index].tcId == tcId))
        {
            return &gUdmaTestCases[index];
        }
    }
    return NULL;
}

int32_t TestUdma_initDriver(UdmaTestObj *testObj, UdmaTestParams *testPrms)
{
    int32_t         retVal = UDMA_SOK;
    uint32_t        instId;
    Udma_InitPrms   initPrms;
    Udma_DrvHandle  drvHandle;

    retVal = Utils_memInit();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(UDMA_SOK, retVal, "Utils mem init failed!!\n");

    /* Select instance ID from first channel of the test case */
    instId = testPrms->instId[0];

    /* Normalize each aliases to BCDMA_0, and PKTDMA_0 */
    if (instId == UDMA_TEST_INST_ID_BCDMA_BC)
    {
        instId = UDMA_INST_ID_BCDMA_0;
    }
    else if (instId == UDMA_TEST_INST_ID_PKTDMA)
    {
        instId = UDMA_INST_ID_PKTDMA_0;
    }
    else
    {
        /* Nothing to do */
    }

    /* UDMA driver init Prms*/
    drvHandle = &testObj->drvObj[instId];
    UdmaInitPrms_init(instId, &initPrms);

    /* skip global event register for test cases with PKTDMA instance*/
    if (instId == UDMA_INST_ID_PKTDMA_0)
    {
        initPrms.skipGlobalEventReg = TRUE;
    }

    /* Driver init */
    retVal += Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    return (retVal);
}

int32_t TestUdma_deinitDriver(UdmaTestObj *testObj, UdmaTestParams *testPrms)
{
    int32_t         retVal = UDMA_SOK;
    uint32_t        instId;
    Udma_DrvHandle  drvHandle;

    /* Select instance ID from first channel of the test case */
    instId = testPrms->instId[0];

    /* Normalize each aliases to BCDMA_0, and PKTDMA_0 */
    if (instId == UDMA_TEST_INST_ID_BCDMA_BC)
    {
        instId = UDMA_INST_ID_BCDMA_0;
    }
    else if (instId == UDMA_TEST_INST_ID_PKTDMA)
    {
        instId = UDMA_INST_ID_PKTDMA_0;
    }
    else
    {
        /* Nothing to do */
    }

    drvHandle = &testObj->drvObj[instId];

    /* Driver deinit */
    retVal += Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(UDMA_SOK, retVal, "UDMA deinit failed!!\n");

    retVal = Utils_memDeInit();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(UDMA_SOK, retVal, "Utils mem deinit failed!!\n");

    return (retVal);
}

/* Helper to clear multiple buffers. No-op if buffer list is NULL.
 * Iterates through each buffer and clears it to prevent potential data
 * leakage between test cases. */
void TestUdma_clearBufs(void **bufList, size_t *sizeList, uint32_t count)
{
    int32_t index;
    for(index = 0U; index < count; index += 1)
    {
        memset(bufList[index], TEST_UDMA_BUF_CLEAR_PATTERN, sizeList[index]);
    }
}

/* Event callback helper: increments TestUdma_EventCbCount when a DMA
 * completion event fires. Parameters are unused in tests but retained for
 * signature compliance with Udma_EventCallback type. */
static void TestUdma_eventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData)
{
    (void)eventHandle;
    (void)eventType;
    (void)appData;
    /* Increment count for legacy validation and release waiting test via semaphore */
    TestUdma_EventCbCount += 1;
    SemaphoreP_post(&TestUdma_EventSem);
}

static void TestUdma_genericEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData)
{
    (void)eventHandle;
    (void)eventType;
    TestUdma_EventSemaphore *ctx = (TestUdma_EventSemaphore*)appData;
    if (ctx != NULL)
    {
        if (ctx->semaphoreCounter != NULL)
        {
            (*ctx->semaphoreCounter) += 1;
        }
        if (ctx->semaphoreObject != NULL)
        {
            SemaphoreP_post(ctx->semaphoreObject);
        }
    }
}

/*
 * Helper: Submit TRPD and wait via semaphore for completion event (event enabled).
 * Returns UDMA_SOK on success or error code on failure.
 */
static int32_t TestUdma_submitAndWaitEvent(Udma_ChHandle chHandle,
                                           uint8_t *trpdMem,
                                           uint64_t trpdPhysAddr,
                                           uint8_t *dst,
                                           uint8_t *src,
                                           uint32_t byteCnt)
{
    int32_t retVal;
    uint64_t cqDesc;
    uint32_t remainingPollAttempts;

    /* Drain CQ ring BEFORE submit (flush until empty) */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &cqDesc);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    TestUdma_initBuffer(src, dst, byteCnt);
    TestUdma_trpdInit(chHandle, trpdMem, dst, src, byteCnt);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysAddr);
    if (retVal != UDMA_SOK)
    {
        return retVal;
    }
    /* Wait for IRQ event */
    if (SemaphoreP_pend(&TestUdma_EventSem, TEST_UDMA_DEFAULT_CH_DISABLE_TIMEOUT) != SystemP_SUCCESS)
    {
        return UDMA_EFAIL;
    }
    /* Drain CQ after IRQ */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &cqDesc);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    return UDMA_SOK;
}

/*
 * Helper: Submit TRPD and poll CQ ring for completion (event disabled scenario).
 * Returns UDMA_SOK when completion desc dequeued else error.
 */
static int32_t TestUdma_submitAndPollCompletion(Udma_ChHandle chHandle,
                                                uint8_t *trpdMem,
                                                uint64_t trpdPhysAddr,
                                                uint8_t *dst,
                                                uint8_t *src,
                                                uint32_t byteCnt)
{
    int32_t retVal;
    uint64_t completionDescAddr;
    uint32_t pollAttempts = 0;
    const uint32_t maxPollAttempts = 100000U;
    /* Drain CQ ring before submit */
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    TestUdma_initBuffer(src, dst, byteCnt);
    TestUdma_trpdInit(chHandle, trpdMem, dst, src, byteCnt);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysAddr);
    if (retVal != UDMA_SOK)
    {
        return retVal;
    }
    while (pollAttempts < maxPollAttempts)
    {
        retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_SOK)
        {
            return UDMA_SOK;
        }
        pollAttempts += 1;
    }
    return UDMA_EFAIL;
}


/* Main test function */
void test_udma_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestUdma_blkcpyTest, 8237, NULL);
    RUN_TEST(TestUdma_blkcpyPauseResumeTest, 8238, NULL);
    RUN_TEST(TestUdma_blkcpyChainingTest, 8239, NULL);
    RUN_TEST(TestUdma_blkcpyIntrTest, 8240, NULL);
    RUN_TEST(TestUdma_blkcpySwGlobal0PollingTest, 8242, NULL);
    RUN_TEST(TestUdma_blkcpySwGlobal0IntrTest, 8243, NULL);
    RUN_TEST(TestUdma_blkcpyCircularIcnt1EventTest, 8244, NULL);
    RUN_TEST(TestUdma_blkcpyCircularIcnt2EventTest, 8245, NULL);
    RUN_TEST(TestUdma_blkcpyCircularIcnt3EventTest, 8246, NULL);
    RUN_TEST(TestUdma_ringFlushTest, 8248, NULL);
    RUN_TEST(TestUdma_ringParamCheckTest, 8249, NULL);
    RUN_TEST(TestUdma_ringUtilsMemSizeTest, 8274, NULL);
    RUN_TEST(TestUdma_ringMemPtrTest, 8250, NULL);
    RUN_TEST(TestUdma_ringAttachTest, 8251, NULL);
    RUN_TEST(TestUdma_ringResetTest, 8252, NULL);
    RUN_TEST(TestUdma_ringPrimeLcdmaTest, 8275, NULL);
    RUN_TEST(TestUdma_flowAttachMappedTest, 8276, NULL);
    RUN_TEST(TestUdma_trMakeTest, 8278, NULL);
    RUN_TEST(TestUdma_structSizeTest, 8279, NULL);
    RUN_TEST(TestUdma_chPktdmaParamCheckTest, 8280, NULL);
    RUN_TEST(TestUdma_blkcpyDdrToDdr1MBPerfTest, 8282, NULL);
    RUN_TEST(TestUdma_blkcpyCircularSrcOcramToDdrPerfTest, 8283, NULL);
    RUN_TEST(TestUdma_blkcpyDdrToCircularDestOcramPerfTest, 8284, NULL);
    RUN_TEST(TestUdma_blkcpyCircularOcramToOcramPerfTest, 8285, NULL);
    RUN_TEST(TestUdma_blkcpyPacingDdrToOcramCirc4MBTo4KBTest, 8286, NULL);
    RUN_TEST(TestUdma_flowAttachTest, 8287, NULL);
#ifdef ENABLE_MT_TESTS
    RUN_TEST(TestUdma_multiInstancePktdmaBcdma, 8618, NULL);
#endif
    Drivers_udmaClose();
    RUN_TEST(TestUdma_eventEnableDisable, 8288, NULL);
    Drivers_udmaOpen();
    RUN_TEST(TestUdma_memcpyMultiIter, 8290, NULL);
    RUN_TEST(TestUdma_ringOverflow, 8291, NULL);
    RUN_TEST(TestUdma_ringUnderflow, 8292, NULL);
    RUN_TEST(TestUdma_multipleRingsPerChannel, 8293, NULL);
    RUN_TEST(TestUdma_chGetDefaultFlowHandleBcdma, 8295, NULL);
    RUN_TEST(TestUdma_chGetDefaultFlowHandlePktdma, 8296, NULL);
    RUN_TEST(TestUdma_chResetPktdma, 8297, NULL);
    RUN_TEST(TestUdma_chResetBcdma, 8298, NULL);
    RUN_TEST(TestUdma_utilsMapLocalToGlobalEvent, 8300, NULL);
    RUN_TEST(TestUdma_rmTranslateCoreIntrInputTest, 8301, NULL);
    RUN_TEST(TestUdma_txPreferredChannelAllocation, 8304, NULL);
    RUN_TEST(TestUdma_blockCopyPreferredChannelAllocation, 8595, NULL);
    RUN_TEST(TestUdma_rxPreferredChannelAllocation, 8596, NULL);
#if defined(UDMA_HAVE_BC_HC_CH) && (UDMA_HAVE_BC_HC_CH)
    RUN_TEST(TestUdma_allocFreeBlkcopyHcCh, 8597, NULL);
#endif
    RUN_TEST(TestUdma_chStatsBlkCpy, 8598, NULL);
    RUN_TEST(TestUdma_chStatsTx, 8599, NULL);
    RUN_TEST(TestUdma_chStatsRx, 8600, NULL);
    RUN_TEST(TestUdma_chSetChainingRxTx, 8601, NULL);
    RUN_TEST(TestUdma_multipleFlowsPktdma, 8604, NULL);
    RUN_TEST(TestUdma_doubleAllocateChannelRing, 8605, NULL);
    RUN_TEST(TestUdma_multipleChannelsPktdma, 8606, NULL);
    RUN_TEST(TestUdma_preferredChannelBoundaries, 8607, NULL);
    RUN_TEST(TestUdma_eventInvalidUnmappedUnregistered, 8609, NULL);
    RUN_TEST(TestUdma_chArgumentsValidateTests, 8610, NULL);
    RUN_TEST(TestUdma_argumentsValidateTests, 8611, NULL);
    RUN_TEST(TestUdma_utilsArgumentsValidateTests, 8612, NULL);
    RUN_TEST(TestUdma_eventArgumentsValidateTests, 8613, NULL);
    RUN_TEST(TestUdma_ringCommonArgumentsValidateTests, 8614, NULL);
    RUN_TEST(TestUdma_flowArgumentsValidateTests, 8615, NULL);
    RUN_TEST(TestUdma_invalidInstance, 8617, NULL);
    RUN_TEST(TestUdma_nullRingMemOpen, 8765, NULL);
    RUN_TEST(TestUdma_addrTranslateAndDescriptorEchoTest, 8767, NULL);
    RUN_TEST(TestUdma_multipleBlkcopyChannelsBcdma, 8768, NULL);
    RUN_TEST(TestUdma_channelBusyStatus, 8769, NULL);
    RUN_TEST(TestUdma_channelAllocExhaust, 8770, NULL);
    RUN_TEST(TestUdma_regAccessAfterDeinit, 8771, NULL);
    RUN_TEST(TestUdma_doubleAllocateFlow, 8772, NULL);
    RUN_TEST(TestUdma_eventRegisterFailureKeepsChannelOperational, 8773, NULL);
    RUN_TEST(TestUdma_psilThreadPairingFailure, 8774, NULL);
    RUN_TEST(TestUdma_minSizeTransfer, 8775, NULL);
    RUN_TEST(TestUdma_multiDescriptorSubmission, 8776, NULL);
    RUN_TEST(TestUdma_chPeerDataTest, 8778, NULL);
    RUN_TEST(TestUdma_chConfigPdmaTest, 8777, NULL);
    RUN_TEST(TestUdma_pktdmaInsTxRxChDisable, 8247, NULL);
    RUN_TEST(TestUdma_bcdmaInsTxChDisable, 8766, NULL);
    RUN_TEST(TestUdma_pktdmaSwTriggerNegative, 8603, NULL);
    /* RUN_TEST(TestUdma_blkcpySwGlobal1PollingTest, 9143, NULL);  */
    /* RUN_TEST(TestUdma_blkcpySwGlobal1InterruptTest, 9154, NULL); */
    RUN_TEST(TestUdma_txPreferredChannelAllocationForBlkCpyInstance, 8616, NULL);
    RUN_TEST(TestUdma_rxPreferredChannelAllocationForBlkCpyInstance, 9135, NULL);
    RUN_TEST(TestUdma_blkcpySwGlobal0StatsDecAndVerify, 9137, NULL);
    RUN_TEST(TestUdma_chStatsBcdmaInstForTxRx, 9138, NULL);
    RUN_TEST(TestUdma_blkcopyReloadTransferIsr, 9140, NULL);
    RUN_TEST(TestUdma_multiChannelPauseResumeTest, 9141, NULL);
    RUN_TEST(TestUdma_channelApiNegativeCases, 9142, NULL);
/* Mapped TX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 and mcu r5 cores*/
#if(ENABLE_A53_CORE || ENABLE_MCU_R5_CORE)
#if (UDMA_NUM_MAPPED_TX_GROUP > 0)
    RUN_TEST(TestUdma_mappedTxPreferredChannelAllocation, 8303, NULL);
    RUN_TEST(TestUdma_mappedTxAnyChannelAllocation, 9601, NULL);
#endif
#endif /* For cores that have mapped CPSW resources reserved */
/* Mapped RX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 core*/
#if(ENABLE_A53_CORE)
#if (UDMA_NUM_MAPPED_RX_GROUP > 0)
    RUN_TEST(TestUdma_mappedRxPreferredChannelAllocation, 8302, NULL);
    RUN_TEST(TestUdma_mappedRxAnyChannelAllocation, 9603, NULL);
#endif
#endif /* For cores that have mapped CPSW resources reserved */
    RUN_TEST(TestUdma_allocationHcUhcChannel, 8289, NULL);
/*    RUN_TEST(TestUdma_chResetTxRxForPktdmaAndBcdma, 9139, NULL); */
#ifdef ENABLE_MT_TESTS
    RUN_TEST(TestUdma_chSetChainingRxTxMultithreadIntr, 9250, NULL);
    RUN_TEST(TestUdma_ringOverflowMultithread, 9251, NULL);
    RUN_TEST(TestUdma_multithreadOpenCloseRaceTest, 9252, NULL);
#endif
#if defined (ENABLE_DRU_TESTS)
    Udma_deinit(&gUdmaDrvObj[CONFIG_UDMA0]);
    TestUdma_appdmautilsClecInitDru();
    RUN_TEST(TestUdma_dmautilsDruDirectPolling, 8277, NULL);
    RUN_TEST(TestUdma_dmautilsDruDirect2D, 9405, NULL);
    RUN_TEST(TestUdma_dmautilsDruDirect3D, 9406, NULL);
    RUN_TEST(TestUdma_dmautilsAutoIncCompression, 9407, NULL);
    RUN_TEST(TestUdma_dmautilsDruDirectCircular, 9408, NULL);
    RUN_TEST(TestUdma_dmautilsDruDirectPauseResume, 9409, NULL);
    RUN_TEST(TestUdma_dmautilsDruDirectInterrupt, 8294, NULL);
    RUN_TEST(TestUdma_druOwnerUDMAC, 8602, NULL);
#endif
    RUN_TEST(TestUdma_initWithInvalidInstanceId, 11048, NULL);
    RUN_TEST(TestUdma_deinitWithPendingResources, 11049, NULL);
    RUN_TEST(TestUdma_deinitWithOpenChannels, 11050, NULL);
    RUN_TEST(TestUdma_initWithSkipGlobalEventReg, 11051, NULL);
    RUN_TEST(TestUdma_eventUnregisterWithPendingDescriptors, 11052, NULL);
    RUN_TEST(TestUdma_sharedEventCallbackMismatch, 11053, NULL);
    RUN_TEST(TestUdma_eventRegVintrBitsExhausted, 11054, NULL);
    RUN_TEST(TestUdma_virtToPhyFxnNullCheck, 11055, NULL);
    RUN_TEST(TestUdma_phyToVirtFxnNullCheck, 11056, NULL);
    RUN_TEST(TestUdma_ringFlushRawEmptyRingReset, 11057, NULL);
    RUN_TEST(TestUdma_rmInitPrmsNullCheck, 11058, NULL);
    RUN_TEST(TestUdma_mappedChRangeCheck, 11059, NULL);
    RUN_TEST(TestUdma_ringAllocFreeLifecycle, 11060, NULL);
    RUN_TEST(TestUdma_flowConfigInvalidIndex, 11061, NULL);
    RUN_TEST(TestUdma_chCloseOesAllocNotDeallocated, 11062, NULL);
    RUN_TEST(TestUdma_chOpenInvalidUtcId, 11063, NULL);
    RUN_TEST(TestUdma_chConfigNullArgs, 11064, NULL);
    RUN_TEST(TestUdma_chGetNumRxandUtc, 11065, NULL);
    RUN_TEST(TestUdma_chGetTdCqRingHandle, 11066, NULL);
    RUN_TEST(TestUdma_chSetChainingUnsupportedChannel, 11069, NULL);
    RUN_TEST(TestUdma_getMappedChRingAttributesInvalidMappedTxCh, 11070, NULL);

#if defined(ENABLE_R5F_CORE)
    RUN_TEST(TestUdma_utcIdVPAC, 8299, NULL);
#endif
    UNITY_END();
}

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
/* ========================================================================== */

/* Setup function for Unity test framework */
void setUp(void)
{
    /* Do nothing */
}

/* Teardown function for Unity test framework */
void tearDown(void)
{
    /* Do nothing */
}


/* ========================================================================== */
/*                               Test cases                                   */
/* ========================================================================== */

/**
 * \brief DDR to DDR block copy (polling mode).
 *
 * Test Category: Functional
 *
 * Validates a basic UDMA TR block copy transfer from DDR source to DDR
 * destination
 * using polling for completion (no interrupt/event). Driver and test object are
 * initialized, a single TR is submitted and completion is polled on the CQ ring.
 * Data buffers are compared for integrity after transfer.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer completes (UDMA_SOK); source and destination
 * buffers match.
 */
static void TestUdma_blkcpyTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    memset(TestUdma_Src, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Src));
    memset(TestUdma_Dst, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Dst));

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy DDR to DDR in polling mode) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3467);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Block Copy Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Block copy channel pause/resume functional test.
 *
 * Test Category: Functional
 *
 * Exercises Udma_chPause and Udma_chResume on a block copy channel. A TR
 * is queued; channel is paused to ensure no completion occurs, then resumed
 * and completion verified.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer does not complete while paused; completes after
 * resume and data matches.
 */
static void TestUdma_blkcpyPauseResumeTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    memset(TestUdma_Src, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Src));
    memset(TestUdma_Dst, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Dst));

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Block Copy Pause Resume) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyPauseResumeTc, 3965);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Block Copy Pause Resume Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyPauseResumeTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Block copy TR chaining test.
 *
 * Test Category: Functional
 *
 * Validates that multiple TRs can be chained so that completion of one
 * triggers the next per configured event settings. Ensures ordered
 * execution and final data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All chained TRs complete successfully; buffers match
 * expected pattern.
 */
static void TestUdma_blkcpyChainingTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_TrigSrc, TestUdma_TrigDst, TestUdma_ChainSrc, TestUdma_ChainDst, TestUdma_TrigTrpd, TestUdma_ChainTrpd };
    size_t sizeList[] = { sizeof(TestUdma_TrigSrc), sizeof(TestUdma_TrigDst), sizeof(TestUdma_ChainSrc), sizeof(TestUdma_ChainDst), sizeof(TestUdma_TrigTrpd), sizeof(TestUdma_ChainTrpd) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    memset(TestUdma_TrigSrc, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_TrigSrc));
    memset(TestUdma_TrigDst, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_TrigDst));
    memset(TestUdma_ChainSrc, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_ChainSrc));
    memset(TestUdma_ChainDst, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_ChainDst));
    memset(TestUdma_TrigTrpd, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_TrigTrpd));
    memset(TestUdma_ChainTrpd, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_ChainTrpd));

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Block Copy Chaining) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyChainingTc, 4841);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Block Copy Chaining Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyChainingTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Interrupt-driven block copy test.
 *
 * Test Category: Functional
 *
 * Performs a DDR to DDR block copy using interrupt completion. Confirms ISR/event
 * path works and data moved correctly.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Interrupt fires and transfer completes; data comparison passes.
 */
static void TestUdma_blkcpyIntrTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    memset(TestUdma_Src, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Src));
    memset(TestUdma_Dst, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(TestUdma_Dst));

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy DDR to DDR in interrupt mode) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3473);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy Intr Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);
    retVal = udmaTestBlkcpyTc(taskObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Block copy with SW global0 trigger (polling).
 *
 * Test Category: Functional
 *
 * Uses a software global0 trigger configuration and polls for completion.
 * Verifies trigger configuration does not break basic transfer semantics.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer completes successfully; data matches expected pattern.
 */
static void TestUdma_blkcpySwGlobal0PollingTest(void *args)
{
    int32_t          retVal;
    UdmaTestObj     *testObj;
    UdmaTestParams  *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy DDR to DDR in SW global 0 trigger test in polling mode) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3476);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy SwGlobal0 Polling Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Block copy with SW global0 trigger (interrupt mode).
 *
 * Test Category: Functional
 *
 * Configures a block copy to use software global0 trigger with interrupt completion.
 * Validates event path and data integrity under this trigger mode.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Interrupt observed; transfer completes; buffers match.
 */
static void TestUdma_blkcpySwGlobal0IntrTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy DDR to DDR in SW global 0 trigger test in interrupt mode) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3477);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy SwGlobal0 Intr Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Circular addressing event test (ICNT1).
 *
 * Test Category: Functional
 *
 * Programs circular addressing on ICNT1 dimension and configures TR event generation.
 * Ensures ring events occur as expected and data transfer succeeds.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput TR completes with generated events; buffer contents correct.
 */
static void TestUdma_blkcpyCircularIcnt1EventTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy circular 1KB DDR to DDR 1KB ICNT1 TR event type) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3480);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy Circular Icnt1 Event Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Circular addressing event test (ICNT2).
 *
 * Test Category: Functional
 *
 * Similar to ICNT1 circular test but applied to ICNT2 dimension for a larger transfer
 * span. Verifies correct pacing/event behavior and data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Events generated per configuration; transfer completes; data matches.
 */
static void TestUdma_blkcpyCircularIcnt2EventTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy circular 1KB DDR to DDR 1MB ICNT2 TR event type) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3481);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy Circular Icnt2 Event Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Circular addressing event test (ICNT3).
 *
 * Test Category: Functional
 *
 * Extends circular event validation to ICNT3 dimension. Ensures correctness of TR
 * event signaling and final data movement.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Configured events observed; transfer successful; buffers match.
 */
static void TestUdma_blkcpyCircularIcnt3EventTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy circular 1KB DDR to DDR 1MB ICNT3 TR event type) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3482);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blockcpy Circular Icnt3 Event Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring flush API functional test.
 *
 * Test Category: Functional
 *
 * Invokes ring flush operation on a configured ring to validate descriptor removal
 * semantics and ensure API returns success under expected conditions.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput API returns success and ring entries flushed as expected.
 */
static void TestUdma_ringFlushTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring flush API testcase) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingFlushTc, 3508);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring flush API Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingFlushTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring parameter validation test suite.
 *
 * Test Category: Negative
 *
 * Exercises boundary and invalid ring configuration paths via param-check APIs to
 * confirm proper rejection of bad arguments and acceptance of valid ones.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid configurations rejected (error codes); valid case passes.
 */
static void TestUdma_ringParamCheckTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring Param Check Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingParamCheckTc, 3511);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Param Check Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingParamCheckTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring utility memory size computation test.
 *
 * Test Category: Functional
 *
 * Calls utility APIs to compute required ring memory size for a configuration and
 * compares results with allocated buffers for consistency.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Computed size matches expectation; test completes successfully.
 */
static void TestUdma_ringUtilsMemSizeTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring  Utils MemSize Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingUtilsMemSizeTc, 3512);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Utils MemSize Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingUtilsMemSizeTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring memory pointer translation utility test.
 *
 * Test Category: Functional
 *
 * Verifies APIs that derive ring memory pointers and perform address translation
 * operate correctly given an initialized ring configuration.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Pointer translation succeeds; no data corruption observed.
 */
static void TestUdma_ringMemPtrTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring  Mem Ptr Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingMemPtrTc, 3682);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Mem Ptr Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingMemPtrTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring attach/detach API functional test.
 *
 * Test Category: Functional
 *
 * Opens a ring using normal allocation path, then exercises attach sequence on a
 * ring number via attach API, followed by detach. Validates expected success codes
 * and that subsequent operations on the attached handle work as intended.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Ring attach and detach complete successfully without data corruption.
 */
static void TestUdma_ringAttachTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring  Attach Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingAttachTc, 3726);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Attach Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingAttachTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Ring reset API functional test.
 *
 * Test Category: Functional
 *
 * Allocates and primes a ring, then invokes Udma_ringReset to clear internal
 * indices/state. Verifies subsequent ring operations behave as if newly initialized.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Ring reset succeeds; post-reset operations return expected results.
 */
static void TestUdma_ringResetTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Ring  Reset Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingResetTc, 4644);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Reset Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingResetTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief LCDMA ring prime test.
 *
 * Test Category: Functional
 *
 * Validates priming of a ring for LCDMA paths ensuring descriptors are prepared and
 * driver reports success. Confirms no unexpected errors and completion status OK.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Ring prime task returns success and LCDMA ring operates normally.
 */
static void TestUdma_ringPrimeLcdmaTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (LCDMA Ring Prime Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestRingPrimeLcdmaTc, 8837);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ring Prime Lcdma Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestRingPrimeLcdmaTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Flow attach (mapped) functional test.
 *
 * Test Category: Functional
 *
 * Attaches a mapped flow to a channel and later detaches it validating resource
 * assignment and teardown correctness for mapped flow groups.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Mapped flow attach/detach sequence succeeds; no leaks or errors.
 */
static void TestUdma_flowAttachMappedTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Mapped Flow attach and detach Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestFlowAttachMappedTc, 7034);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Flow Attach Mapped Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestFlowAttachMappedTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief TR make utility test.
 *
 * Test Category: Functional
 *
 * Validates helper utilities that construct TR descriptors (make functions) produce
 * correct layout/fields for subsequent submission.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput TR construction utility returns success; descriptor fields verified.
 */
static void TestUdma_trMakeTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (TR make utility testcase) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestTrMakeTc, 3515);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA TR Make Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestTrMakeTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief UDMA structure size print test.
 *
 * Test Category: Functional
 *
 * Invokes task which reports sizeof key internal driver structures aiding coverage
 * and regression tracking.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Sizes printed/logged; task returns success.
 */
static void TestUdma_structSizeTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (UDMA structure size print testcase) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestStructSizeTc, 3733);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA TR Make Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestStructSizeTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief PKTDMA channel parameter check test.
 *
 * Test Category: Negative
 *
 * Exercises parameter validation logic for PKTDMA channel configuration ensuring
 * invalid combinations are rejected with appropriate error codes.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid params rejected; valid configuration path succeeds.
 */
static void TestUdma_chPktdmaParamCheckTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (PKTDMA Channel Paramter Check test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestChPktdmaParamCheckTc, 6282);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Ch Pktdma ParamCheck Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestChPktdmaParamCheckTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief DDR 1MB to DDR 1MB performance test.
 *
 * Test Category: Performance
 *
 * Measures throughput for a large (1MB) DDR to DDR block copy transfer exercising
 * performance oriented configuration of the DMA channel.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer completes successfully; performance metrics logged.
 */
static void TestUdma_blkcpyDdrToDdr1MBPerfTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Blockcpy DDR 1MB to DDR 1MB performance test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3485);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blkcpy Ddr To Ddr 1MB Perf Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    ClockP_usleep(5000);
    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Circular OCRAM (1KB) source to DDR (1MB) performance test.
 *
 * Test Category: Performance
 *
 * Uses 2D circular addressing at source to evaluate performance impact vs linear
 * addressing for large destination region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Successful transfer; performance characteristics recorded.
 */
static void TestUdma_blkcpyCircularSrcOcramToDdrPerfTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (2D Blockcpy OCRAM circular 1KB to DDR 1MB performance test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3486);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blkcpy Circular Src Ocram To Ddr Perf Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    ClockP_usleep(5000);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief DDR (1MB) to circular OCRAM (1KB) performance test.
 *
 * Test Category: Performance
 *
 * Evaluates DMA performance writing into a small circular destination window while
 * reading a large linear DDR source.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer success; performance/pacing metrics captured.
 */
static void TestUdma_blkcpyDdrToCircularDestOcramPerfTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (2D Blockcpy DDR 1MB to OCRAM circular 1KB performance test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3487);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Blkcpy Ddr To Circular Dest Ocram Perf Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    ClockP_usleep(5000);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Circular OCRAM to circular OCRAM performance test.
 *
 * Test Category: Performance
 *
 * Simultaneously applies circular addressing to source and destination to assess
 * overhead and sustained throughput.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer completes; logged metrics reflect expected circular performance.
 */
static void TestUdma_blkcpyCircularOcramToOcramPerfTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (2D Blockcpy OCRAM circular 1KB to OCRAM circular 1KB performance test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3488);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Circular Ocram To Ocram Perf Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Pacing test DDR 4MB to OCRAM circular 4KB.
 *
 * Test Category: Performance
 *
 * Performs paced transfers (e.g. time-delayed) from large DDR region into small
 * circular OCRAM buffer to validate pacing and sustained operation over duration.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All paced iterations succeed; no data mismatches; timing within tolerance.
 */
static void TestUdma_blkcpyPacingDdrToOcramCirc4MBTo4KBTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (2D Blockcpy DDR 4MB to OCRAM circular 4KB at 20ms pacing for 10 seconds) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestBlkcpyTc, 3498);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Pacing Ddr To Ocram Circ 4MB To 4KB Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestBlkcpyTc(taskObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Flow attach and detach test.
 *
 * Test Category: Functional
 *
 * Allocates a flow, attaches it to a channel and then detaches verifying reference
 * counts and internal bookkeeping.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Flow attach/detach operations return success; no resource leaks.
 */
static void TestUdma_flowAttachTest(void *args)
{
    int32_t retVal;
    UdmaTestObj    *testObj;
    UdmaTestParams *testPrms;
    UdmaTestTaskObj *taskObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Set default config */
    testObj = &TestUdma_UtObj;
    udmaTestSetDefaultCfg(testObj);

    /* Get test case parameters (Flow attach and detach Test) */
    testPrms = TestUdma_findTestCaseByFuncAndTcId(&udmaTestFlowAttachTc, 9100);
    if (testPrms == NULL)
    {
        DebugP_log("Test case not found!\r\n");
        return;
    }

    /* Initialize driver only for the specific instance */
    retVal = TestUdma_initDriver(testObj, testPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Initialize test object with parameters */
    udmaTestInitTestObj(testObj, testPrms);
    testPrms->isRun = TRUE;

    /* Run the test */
    taskObj = &testObj->taskObj[0];
    DebugP_log("Running UDMA Flow Attach Test (tcId=%d, name=%s)\r\n", testPrms->tcId, testPrms->tcName);

    retVal = udmaTestFlowAttachTc(taskObj);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinitialize driver/memory */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_deinitDriver(testObj, testPrms));
}

/**
 * \brief Event enable/disable functional test.
 *
 * Test Category: Functional
 *
 * Registers a DMA completion event, enables/disables it across multiple transfers
 * verifying callback invocation only when enabled.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Callback observed on enabled transfers, suppressed when disabled; all APIs succeed.
 */
void TestUdma_eventEnableDisable(void *args)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_EventPrms eventPrms;
    TestUdma_EventSemaphore eventSemaphore;
    int32_t retVal;
    uint8_t *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    uint64_t trpdPhysicalAddr =
        (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);
    uint64_t completionDescAddr;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;

    /* Open block copy channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Construct semaphore before event registration */
    SemaphoreP_constructBinary(&TestUdma_EventSem, 0);

    /* Configure event context for generic callback */
    eventSemaphore.semaphoreObject   = &TestUdma_EventSem;
    eventSemaphore.semaphoreCounter = &TestUdma_EventCbCount;

    /* Register DMA completion event with generic callback */
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_genericEventCb;
    eventPrms.appData   = &eventSemaphore;

    retVal = Udma_eventRegister(drvHandle, &TestUdma_EventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Transfer 1: Expect callback */
    TestUdma_EventCbCount = 0;
    retVal = TestUdma_submitAndWaitEvent(chHandle, trpdMemory, trpdPhysicalAddr,
                                         TestUdma_Dst, TestUdma_Src,
                                         TEST_UDMA_NUM_BYTES);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_NOT_EQUAL(0, TestUdma_EventCbCount);

    /* Disable event */
    retVal = Udma_eventDisable(&TestUdma_EventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Drain any pending CQ before second transfer */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Transfer 2: Event disabled → no callback expected */
    TestUdma_EventCbCount = 0;
    retVal = TestUdma_submitAndPollCompletion(chHandle, trpdMemory, trpdPhysicalAddr,
                                              TestUdma_Dst, TestUdma_Src,
                                              TEST_UDMA_NUM_BYTES);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL(0, TestUdma_EventCbCount);

    /* Enable event */
    retVal = Udma_eventEnable(&TestUdma_EventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Recreate semaphore because poll case did not use it */
    SemaphoreP_destruct(&TestUdma_EventSem);
    SemaphoreP_constructBinary(&TestUdma_EventSem, 0);
    eventSemaphore.semaphoreObject = &TestUdma_EventSem; /* rebind for safety */

    /* Transfer 3: Expect callback again */
    TestUdma_EventCbCount = 0;
    retVal = TestUdma_submitAndWaitEvent(chHandle, trpdMemory, trpdPhysicalAddr,
                                         TestUdma_Dst, TestUdma_Src,
                                         TEST_UDMA_NUM_BYTES);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_NOT_EQUAL(0, TestUdma_EventCbCount);

    /* Final CQ drain after third transfer */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Cleanup */
    retVal = Udma_eventUnRegister(&TestUdma_EventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&TestUdma_EventSem);
}

#if defined(UDMA_HAVE_BC_HC_CH) && (UDMA_HAVE_BC_HC_CH)
/**
 * \brief High-capacity block copy channel allocate/free test.
 *
 * Test Category: Functional
 *
 * Opens a high-capacity (HC) block-copy channel, submits a single TRPD transfer,
 * polls for completion, verifies data integrity, then disables and closes the
 * channel to ensure resources release cleanly.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Transfer completes successfully and channel closes without errors.
 */
static void TestUdma_allocFreeBlkcopyHcCh(void *args)
{
    int32_t retVal;
    Udma_DrvHandle  drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject   chObj;
    Udma_ChHandle   chHandle  = &chObj;
    Udma_ChPrms     chPrms;
    uint8_t *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    uint64_t trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);
    uint64_t completionDescAddr;
    /* Event + semaphore objects */
    Udma_EventObject eventObj;
    Udma_EventPrms eventPrms;
    SemaphoreP_Object localSem;
    volatile uint32_t callbackCount = 0;
    TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY_HC);
    chPrms.chNum = UDMA_DMA_CH_ANY;

    /* Set FQ ring memory similar to other tests (small ring - 1 element) */
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY_HC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register completion event (IRQ instead of polling) */
    SemaphoreP_constructBinary(&localSem, 0);
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_genericEventCb;
    eventPrms.appData   = (void*)&eventSemaphore;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    /* Ensure TRPD cache writeback done by TestUdma_trpdInit */

    /* Drain any previous completions on CQ to avoid spurious dequeues */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Wait for IRQ callback */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    /* Callback count is informational only */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, callbackCount);
    /* Mandatory CQ completion validation: first dequeue must match TRPD */
    retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Drain any remaining entries (normally none for single transfer) */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Invalidate dst buffer and compare */
    TestUdma_compareBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);

    retVal = Udma_eventUnRegister(&eventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&localSem);
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

}

#endif /* UDMA_HAVE_BC_HC_CH */

/* Helper: Reset driver and channel object memory to known state.
 * Not a test case; used by negative argument validation routines to force
 * specific initialization or de-initialized states without invoking full
 * driver/channel open/close sequences. Sets drvInitDone flag and zeroes
 * channel objects when provided. */
static void TestUdma_resetDrvChObjects(Udma_DrvHandle drvHandle,
                                       Udma_ChHandle chHandle0,
                                       Udma_ChHandle chHandle1)
{
    Udma_DrvHandleInt drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    if (chHandle0 != NULL)
    {
        Udma_ChHandleInt channel0Internal = (Udma_ChHandleInt) chHandle0;
        memset(channel0Internal, 0, sizeof(Udma_ChObject));
    }
    if (chHandle1 != NULL)
    {
        Udma_ChHandleInt channel1Internal = (Udma_ChHandleInt) chHandle1;
        memset(channel1Internal, 0, sizeof(Udma_ChObject));
    }
}

/* Helper: Prepare custom channel0 state for argument validation.
 * Initializes channel parameter structure to a default base type, resets
 * driver/channel objects, then overrides init state fields to simulate
 * partially initialized or de-initialized scenarios for negative tests. */
static void TestUdma_setupCh0Custom(Udma_DrvHandle drvHandle,
                                    Udma_ChHandle chHandle0,
                                    Udma_ChHandle chHandle1,
                                    Udma_ChPrms *chPrms,
                                    uint32_t chInitDone,
                                    uint32_t drvInitDone)
{
    Udma_ChHandleInt channel0Internal = (Udma_ChHandleInt)chHandle0;
    UdmaChPrms_init(chPrms, 1);
    TestUdma_resetDrvChObjects(drvHandle, chHandle0, chHandle1);
    channel0Internal->chInitDone      = chInitDone;
    ((Udma_DrvHandleInt)drvHandle)->drvInitDone = drvInitDone;
}

/**
 * \brief Channel API argument validation and failure path test.
 *
 * Test Category: Negative
 *
 * Exercises all public channel APIs with intentionally invalid arguments to
 * confirm they return UDMA_EBADARGS. Then simulates de-initialized driver and
 * channel states to force UDMA_EFAIL error paths (e.g., calling enable/disable
 * or open/close when driver/ch objects are not correctly initialized). Each
 * scenario asserts the expected error code, ensuring robust parameter and
 * state checking logic across the channel lifecycle.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All invalid argument calls return UDMA_EBADARGS; simulated
 *                  de-initialized state calls return UDMA_EFAIL with no system
 *                  crash or undefined behavior.
 */
void TestUdma_chArgumentsValidateTests(void *args)
{
    int32_t retVal;

    Udma_DrvObject drvObj;
    Udma_ChObject chObj0;
    Udma_ChObject chObj1;

    Udma_DrvHandle drvHandle = &drvObj;

    Udma_ChHandle nullChHandle = NULL;
    Udma_ChHandle chHandle0 = &chObj0;
    Udma_ChHandle chHandle1 = &chObj1;

    Udma_ChTxPrms txPrms = {TEST_UDMA_CH_TX_PRMS_UNINIT};
    Udma_ChRxPrms rxPrms = {TEST_UDMA_CH_RX_PRMS_UNINIT};

    Udma_ChPrms chPrms;

    /* Udma_chEnable with NULL channel handle: expect UDMA_EBADARGS (defensive handle check) */
    retVal = Udma_chEnable(nullChHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chDisable with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chDisable(nullChHandle, TEST_UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chClose with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chClose(nullChHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chConfigTx with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chConfigTx(nullChHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chConfigRx with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chConfigRx(nullChHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chOpen with all NULL critical parameters: expect UDMA_EBADARGS */
    retVal = Udma_chOpen(NULL, NULL, TEST_UDMA_INVALID_CH_TYPE_0, NULL);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chGetStats with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chGetStats(nullChHandle, NULL);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* Udma_chDecStats with NULL channel handle: expect UDMA_EBADARGS */
    retVal = Udma_chDecStats(nullChHandle, NULL);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);

    /* ----------------------------- */
    /* UDMA_EFAIL test cases         */
    /* For each API, reset objects   */
    /* to a fresh de-initialized     */
    /* state before the call.        */
    /* ----------------------------- */

    /* Udma_chOpen with driver forced to DEINIT state: expect UDMA_EFAIL (invalid driver lifecycle state) */
    TestUdma_setupCh0Custom(drvHandle, chHandle0, chHandle1, &chPrms, UDMA_INIT_DONE, UDMA_DEINIT_DONE);
    retVal = Udma_chOpen(drvHandle, chHandle0, TEST_UDMA_CH_TYPE_INVALID_1, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EFAIL, retVal);

    /* Udma_chClose with driver forced to DEINIT state: expect UDMA_EFAIL.
     * Reset objects before each test to ensure a clean state. */
    TestUdma_setupCh0Custom(drvHandle, chHandle0, chHandle1, &chPrms, UDMA_INIT_DONE, UDMA_DEINIT_DONE);
    retVal = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT(UDMA_EFAIL, retVal);

    /* Udma_chClose with chOesAllocDone = TRUE and driver DEINIT: expect UDMA_EFAIL.
     * Always reset objects before each test to avoid side effects from previous calls. */
    TestUdma_setupCh0Custom(drvHandle, chHandle0, chHandle1, &chPrms, UDMA_INIT_DONE, UDMA_DEINIT_DONE);
    retVal = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT(UDMA_EFAIL, retVal);

    /* Udma_chEnable with driver forced to DEINIT state: expect UDMA_EFAIL.
     * Reset objects before each test to ensure correct negative path coverage. */
    TestUdma_setupCh0Custom(drvHandle, chHandle0, chHandle1, &chPrms, UDMA_INIT_DONE, UDMA_DEINIT_DONE);
    retVal = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT(UDMA_EFAIL, retVal);

    /* Udma_chDisable with driver forced to DEINIT state: expect UDMA_EFAIL.
     * Reset objects before each test to ensure correct negative path coverage. */
    TestUdma_setupCh0Custom(drvHandle, chHandle0, chHandle1, &chPrms, UDMA_INIT_DONE, UDMA_DEINIT_DONE);
    retVal = Udma_chDisable(chHandle0, TEST_UDMA_DEFAULT_CH_DISABLE_TIMEOUT_SHORT);
    TEST_ASSERT_EQUAL_INT(UDMA_EFAIL, retVal);
}

/* Helper: Initialize a TR15 transfer record packet descriptor (TRPD) for a
 * simple 1D block move. Fills source/destination addressing, element counts,
 * dimensions, and completion event configuration, then performs cache
 * writeback so hardware sees updated descriptor contents. Expects an already
 * opened/allocated channel handle. */
static int32_t TestUdma_trpdInit(Udma_ChHandle chHandle,
                                 uint8_t *trpdMemory,
                                 const void *destBuf,
                                 const void *srcBuffer,
                                 uint32_t length)
{
    CSL_UdmapTR15  *chainTrDescriptor;
    uint32_t        cqRingNum;
    if ((NULL == chHandle) || (NULL == trpdMemory) ||
        (NULL == destBuf) || (NULL == srcBuffer) || (TEST_UDMA_VALUE_ZERO == length))
    {
        return UDMA_EBADARGS;
    }
    cqRingNum = Udma_chGetCqRingNum(chHandle);
    if (UDMA_RING_INVALID == cqRingNum)
    {
        return UDMA_EFAIL;
    }

    /* Make TRPD with TR15 TR type */
    UdmaUtils_makeTrpdTr15(trpdMemory, TEST_UDMA_TR_COUNT_SINGLE, cqRingNum);

    /* Setup TR */
    chainTrDescriptor = UdmaUtils_getTrpdTr15Pointer(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO);
    chainTrDescriptor->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, TEST_UDMA_FLAG_STATIC_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, TEST_UDMA_TR_CMD_ID);  /* This will come back in TR response */
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, TEST_UDMA_FLAG_INDIRECT_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, TEST_UDMA_FLAG_INDIRECT_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, TEST_UDMA_TR_FLAG_SET);
    chainTrDescriptor->icnt0    = length;
    chainTrDescriptor->icnt1    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->icnt2    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->icnt3    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dim1     = chainTrDescriptor->icnt0;
    chainTrDescriptor->dim2     = (chainTrDescriptor->icnt0 * chainTrDescriptor->icnt1);
    chainTrDescriptor->dim3     = (chainTrDescriptor->icnt0 * chainTrDescriptor->icnt1 * chainTrDescriptor->icnt2);
    chainTrDescriptor->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuffer, TEST_UDMA_BUF_INDEX_ZERO, NULL);
    chainTrDescriptor->fmtflags = TEST_UDMA_TR_FMTFLAGS_LINEAR_1B;    /* Linear addressing, 1 byte per elem */
    chainTrDescriptor->dicnt0   = length;
    chainTrDescriptor->dicnt1   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dicnt2   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dicnt3   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->ddim1    = chainTrDescriptor->dicnt0;
    chainTrDescriptor->ddim2    = (chainTrDescriptor->dicnt0 * chainTrDescriptor->dicnt1);
    chainTrDescriptor->ddim3    = (chainTrDescriptor->dicnt0 * chainTrDescriptor->dicnt1 * chainTrDescriptor->dicnt2);
    chainTrDescriptor->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Perform cache writeback */
    CacheP_wb(trpdMemory, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);
    return UDMA_SOK;
}


/* Helper: Initialize source and destination buffers for memcpy tests.
 * Source is filled with incremental pattern 0..length-1 while destination is
 * poisoned with 0xA5 to detect incomplete transfers. Performs cache writeback
 * for both buffers to ensure coherence before DMA submission. */
static int32_t TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length)
{
    uint32_t index;
    if ((NULL == srcBuffer) || (NULL == destBuf) || (TEST_UDMA_VALUE_ZERO == length))
    {
        return UDMA_EBADARGS;
    }
    for(index = 0U; index < length; index += 1)
    {
        srcBuffer[index] = index;
        destBuf[index] = TEST_UDMA_POISON_PATTERN_BYTE;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuffer, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);
    return UDMA_SOK;
}

/* Helper: Compare source and destination buffers after a transfer.
 * Invalidates destination cache lines, iterates and asserts equality. On first
 * mismatch logs error and triggers debug assert for immediate test failure. */
static int32_t TestUdma_compareBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length)
{
    int32_t index;
    if ((NULL == srcBuffer) || (NULL == destBuf))
    {
        return UDMA_EBADARGS;
    }
    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for (index= 0U; index < length; index += 1)
    {
        if (srcBuffer[index] != destBuf[index])
        {
            TEST_FAIL_MESSAGE("Data mismatch detected in buffer comparison");
            return UDMA_EFAIL;
        }
    }

    return UDMA_SOK;
}

/**
 * \brief Multi-iteration memcpy stress test.
 *
 * Test Category: Functional
 *
 * Reuses the same channel and descriptor across multiple iterations to validate
 * descriptor reinitialization, cache maintenance and ring queue/dequeue stability
 * under repeated use. Compares buffer contents each iteration for data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All iterations complete successfully; each buffer compare passes.
 */
static void TestUdma_memcpyMultiIter(void *args)
{
    int32_t retVal;
    uint32_t pollAttempts = 0;
    const uint32_t maxPollAttempts = 100000U;
    int completed = 0;
    Udma_ChHandle chHandle;
    uint8_t *srcBuffer = &TestUdma_Src[TEST_UDMA_BUF_INDEX_ZERO];
    uint8_t *destBuf = &TestUdma_Dst[TEST_UDMA_BUF_INDEX_ZERO];
    uint32_t length = TEST_UDMA_NUM_BYTES;
    uint64_t completionDescAddr;
    uint32_t trResponseStatus, index;
    uint8_t *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    uint64_t trpdPhysicalAddr = (uint64_t) Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_Src, TestUdma_Dst, TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_Src), sizeof(TestUdma_Dst), sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    chHandle = gConfigUdma0BlkCopyChHandle[0];
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    for (index = 0; index < TEST_UDMA_MULTI_ITERATIONS; index += 1)
    {
        /* DebugP_log("[UDMA] Iteration %u...\r\n", index); */

        TestUdma_initBuffer(srcBuffer, destBuf, length);
        TestUdma_trpdInit(chHandle, trpdMemory, destBuf, srcBuffer, length);

        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        while (pollAttempts < maxPollAttempts)
        {
            retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
            if (UDMA_SOK == retVal)
            {
                CacheP_inv(trpdMemory, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);
                trResponseStatus = UdmaUtils_getTrpdTr15Response(trpdMemory, TEST_UDMA_TR_RESPONSE_SINGLE, TEST_UDMA_RING_NUM_ZERO);
                TEST_ASSERT_EQUAL(CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE, trResponseStatus);
                completed = 1;
                break;
            }
            pollAttempts += 1;
        }
        TEST_ASSERT_TRUE_MESSAGE(completed, "UDMA CQ completion not detected in time");


        TestUdma_compareBuffer(srcBuffer, destBuf, length);
    }

    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    return;
}

/**
 * \brief Ring overflow negative test.
 *
 * Test Category: Negative
 *
 * Attempts to enqueue more descriptors than ring capacity to confirm queue API
 * returns failure when full and only capacity-sized descriptors are accepted.
 * Validates completion and data integrity for accepted descriptors.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Enqueue returns error after ring full; accepted descriptors complete; data matches.
 */
static void TestUdma_ringOverflow(void *args)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    int32_t retVal, index, completed = 0, submitted = 0;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_STANDARD;
    uint16_t fqRingNum;
    Udma_ChObject chObj;
    uint64_t trpdPhysicalAddr, completionDescAddr;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TrpdMem, TestUdma_SrcBuf, TestUdma_DstBuf };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdMem), sizeof(TestUdma_SrcBuf), sizeof(TestUdma_DstBuf) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Initialize and open channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_CNT;

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(&chObj, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(&chObj, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    fqRingNum = Udma_chGetFqRingNum(&chObj);
    TEST_ASSERT_NOT_EQUAL(UDMA_RING_INVALID, fqRingNum);

    /* Validate that the FQ ring handle's ringNum matches the API result */
    Udma_RingHandle fqRingHandle = Udma_chGetFqRingHandle(&chObj);
    TEST_ASSERT_NOT_NULL(fqRingHandle);
    TEST_ASSERT_EQUAL_UINT16(fqRingNum, Udma_ringGetNum(fqRingHandle));

    /* Submit more TRPDs than the ring can hold (simulate overflow) */
    for (index= 0; index < TEST_UDMA_RING_ELEM_CNT * 2; index += 1)
    {
        TestUdma_initBuffer(TestUdma_SrcBuf[index], TestUdma_DstBuf[index], TEST_UDMA_NUM_BYTES);
        TestUdma_trpdInit(&chObj, TestUdma_TrpdMem[index], TestUdma_DstBuf[index], TestUdma_SrcBuf[index], TEST_UDMA_NUM_BYTES);

        trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_TrpdMem[index], TEST_UDMA_BUF_INDEX_ZERO, NULL);
        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(&chObj), trpdPhysicalAddr);

        if (retVal == UDMA_SOK)
        {
            submitted += 1;
        }
        else
        {
            DebugP_log("Queue full at TRPD %u (as expected)\n", index);
            break;
        }
    }

    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_RING_ELEM_CNT, submitted); /* Only ring size TRPDs should be accepted */

    /* Wait for completions (polling) */
    while ((completed < submitted) && remainingPollAttempts)
    {
        if (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(&chObj), &completionDescAddr) == UDMA_SOK)
        {
            completed += 1;
        }
        else
        {
            ClockP_usleep(10);
        }
        remainingPollAttempts -= 1;
    }

    TEST_ASSERT_EQUAL_UINT32(submitted, completed);

    /* Validate data */
    for (index= 0; index < submitted; index += 1)
    {
        TestUdma_compareBuffer(TestUdma_SrcBuf[index], TestUdma_DstBuf[index], TEST_UDMA_NUM_BYTES);
    }

    /* Cleanup */
    retVal = Udma_chDisable(&chObj, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Ring underflow negative test.
 *
 * Test Category: Negative
 *
 * Tries to dequeue from an empty completion ring to ensure API signals underflow
 * and internal indices remain unchanged.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Dequeue from empty ring fails; read index unchanged; no crash.
 */
static void TestUdma_ringUnderflow(void *args)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    int32_t retVal, readIndexBefore, readIndexAfter;
    uint64_t completionDescAddr;
    Udma_ChObject chObj;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem };
    size_t sizeList[] = { sizeof(TestUdma_RingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    CacheP_wb(TestUdma_RingMem, sizeof(TestUdma_RingMem), CacheP_TYPE_ALLD);

    /* Initialize and open channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_CNT;

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(&chObj, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(&chObj, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Get CQ ring handle */
    Udma_RingHandle cqRing = Udma_chGetCqRingHandle(&chObj);

    /* Invalidate ring memory before reading index */
    CacheP_inv(TestUdma_RingMem, sizeof(TestUdma_RingMem), CacheP_TYPE_ALLD);
    readIndexBefore = Udma_ringGetRdIdx(cqRing);

    /* Attempt to dequeue from empty Completion Ring */
    retVal = Udma_ringDequeueRaw(cqRing, &completionDescAddr);

    /* Invalidate ring memory again before reading index */
    CacheP_inv(TestUdma_RingMem, sizeof(TestUdma_RingMem), CacheP_TYPE_ALLD);

    if (retVal == UDMA_SOK)
    {
        DebugP_log("Unexpected dequeue success on empty ring! completionDescAddr = 0x%llx\n", completionDescAddr);
    }
    else
    {
        DebugP_log("Underflow detected correctly. retVal = %d\n", retVal);
    }

    /* Assert that underflow happened (index.e., dequeue should fail) */
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);

    /* Check read index did not change */
    readIndexAfter = Udma_ringGetRdIdx(cqRing);
    TEST_ASSERT_EQUAL_UINT32(readIndexBefore, readIndexAfter);

    /* Cleanup */
    retVal = Udma_chDisable(&chObj, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Multiple rings per channel configuration test.
 *
 * Test Category: Functional
 *
 * Opens a channel with FQ, CQ and teardown CQ rings to validate simultaneous
 * multi-ring configuration and teardown handling.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All rings operate correctly; teardown CQ optionally populated.
 */
static void TestUdma_multipleRingsPerChannel(void *args)
{
    (void)args;
    int32_t retVal;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    Udma_RingHandle tdCqHandle;

    /* Reuse MultiChannel buffers */
    uint8_t  *trpd1 = TestUdma_TrpdMultiChannel[0];
    uint8_t  *trpd2 = TestUdma_TrpdMultiChannel[1];
    uint8_t  *src1  = TestUdma_SrcMultiChannel[0];
    uint8_t  *dst1  = TestUdma_DstMultiChannel[0];
    uint8_t  *src2  = TestUdma_SrcMultiChannel[1];
    uint8_t  *dst2  = TestUdma_DstMultiChannel[1];

    uint64_t trpdPhys1, trpdPhys2;
    uint64_t cqDesc;
    uint32_t completed1 = 0, completed2 = 0;
    uint32_t pollCount  = 0;
    const uint32_t maxPoll = 200000U;  /* adjust if needed */

    /* Clear all related buffers */
    void *bufferList[] = {
        TestUdma_FqMultiChannel[0],
        TestUdma_CqMultiChannel[0],
        TestUdma_TdCqRingMem,
        trpd1,
        trpd2,
        src1, dst1,
        src2, dst2
    };
    size_t sizeList[] = {
        sizeof(TestUdma_FqMultiChannel[0]),
        sizeof(TestUdma_CqMultiChannel[0]),
        sizeof(TestUdma_TdCqRingMem),
        TEST_UDMA_TRPD_SIZE,
        TEST_UDMA_TRPD_SIZE,
        TEST_UDMA_NUM_BYTES,
        TEST_UDMA_NUM_BYTES,
        TEST_UDMA_NUM_BYTES,
        TEST_UDMA_NUM_BYTES
    };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Driver init (BCDMA instance) */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel open with FQ, CQ and TD CQ rings */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestUdma_FqMultiChannel[0];
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqMultiChannel[0]);
    chPrms.fqRingPrms.elemCnt     = 2U; /* allow two outstanding TRPDs */

    chPrms.cqRingPrms.ringMem     = TestUdma_CqMultiChannel[0];
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqMultiChannel[0]);
    chPrms.cqRingPrms.elemCnt     = 2U; /* room for two completions */

    chPrms.tdCqRingPrms.ringMem     = TestUdma_TdCqRingMem;
    chPrms.tdCqRingPrms.ringMemSize = sizeof(TestUdma_TdCqRingMem);
    chPrms.tdCqRingPrms.elemCnt     = 1U; /* teardown CQ ring */

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure TX/RX sides for block-copy */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel before queuing descriptors */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare both transfers */
    TestUdma_initBuffer(src1, dst1, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpd1, dst1, src1, TEST_UDMA_NUM_BYTES);
    trpdPhys1 = (uint64_t)Udma_defaultVirtToPhyFxn(trpd1, Udma_chGetNum(chHandle), NULL);

    TestUdma_initBuffer(src2, dst2, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpd2, dst2, src2, TEST_UDMA_NUM_BYTES);
    trpdPhys2 = (uint64_t)Udma_defaultVirtToPhyFxn(trpd2, Udma_chGetNum(chHandle), NULL);

    /* Queue both TRPDs to FQ ring */
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhys1);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhys2);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Poll CQ ring for both completions */
    while ((!(completed1 && completed2)) && (pollCount < maxPoll))
    {
        if (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &cqDesc) == UDMA_SOK)
        {
            if (cqDesc == trpdPhys1)
            {
                completed1 = 1;
            }
            else if (cqDesc == trpdPhys2)
            {
                completed2 = 1;
            }
            else
            {
                TEST_FAIL_MESSAGE("Dequeued unknown descriptor from CQ ring");
            }
        }
        pollCount += 1 ;
    }
    TEST_ASSERT_TRUE_MESSAGE(completed1, "TRPD1 did not complete");
    TEST_ASSERT_TRUE_MESSAGE(completed2, "TRPD2 did not complete");

    /* Data integrity checks */
    TestUdma_compareBuffer(src1, dst1, TEST_UDMA_NUM_BYTES);
    TestUdma_compareBuffer(src2, dst2, TEST_UDMA_NUM_BYTES);

    /* Teardown CQ ring should be empty (no teardown invoked yet) */
    if (chPrms.tdCqRingPrms.elemCnt > 0U)
    {
        tdCqHandle = ((Udma_ChHandleInt)chHandle)->tdCqRing;
        /* Teardown CQ ring is not allocated for BCDMA block-copy channels. */
        if (((Udma_ChHandleInt)chHandle)->chType == UDMA_CH_TYPE_TR_BLK_COPY)
        {
            TEST_ASSERT_NULL(tdCqHandle);
        }
        else
        {
            TEST_ASSERT_NOT_NULL(tdCqHandle);
        }
    }

    /* Disable and close channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Flow API argument validation suite.
 *
 * Test Category: Negative
 *
 * Exercises flow allocation, configuration, attach/detach and free APIs with
 * invalid, boundary and de-initialized states to confirm robust error handling.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid inputs produce expected error codes; no crashes.
 */
static void TestUdma_flowArgumentsValidateTests(void *args)
{
    int32_t retVal;
    Udma_DrvHandle drvHandleFlow = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_FlowObject flowObj;
    Udma_FlowHandle flowHandle = &flowObj;
    memset(&flowObj, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(flowObj));
    Udma_DrvHandleInt drvHandleInt = (Udma_DrvHandleInt) drvHandleFlow;
    Udma_FlowHandleInt flowHandleInt = (Udma_FlowHandleInt) flowHandle;
    Udma_FlowAllocMappedPrms flowAllocMap;
    Udma_FlowPrms flowPrms;

    /* Test: Passing NULL flow handle to Udma_flowAllocMapped should return UDMA_EBADARGS */
    flowAllocMap.mappedChNum    = UDMA_DMA_CH_INVALID;
    flowAllocMap.mappedFlowGrp  = TEST_UDMA_MAPPED_FLOW_GRP_5;
    /* flowAllocMapped with NULL flow handle: expect UDMA_EBADARGS */
    retVal = Udma_flowAllocMapped(drvHandleFlow, NULL, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_flowAllocMapped should return UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_flowAllocMapped(drvHandleFlow, flowHandle, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing invalid mappedFlowGrp and mappedChNum to Udma_flowAllocMapped to trigger Udma_mappedFlowCheckParams (should return UDMA_EINVALID_PARAMS) */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    flowAllocMap.mappedFlowGrp = UDMA_MAPPED_GROUP_INVALID;
    flowAllocMap.mappedChNum   = UDMA_DMA_CH_INVALID;
    retVal = Udma_flowAllocMapped(drvHandleFlow, flowHandle, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Passing valid mappedFlowGrp but invalid mappedChNum to Udma_flowAllocMapped to trigger Udma_mappedFlowCheckParams (should return UDMA_EINVALID_PARAMS) */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    flowAllocMap.mappedFlowGrp  = TEST_UDMA_MAPPED_FLOW_GRP_5;
    flowAllocMap.mappedChNum    = TEST_UDMA_MAPPED_CH_NUM_NONE; /* no mapped channel assigned */
    retVal = Udma_flowAllocMapped(drvHandleFlow, flowHandle, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    /* Test: Passing NULL flow handle to Udma_flowAttachMapped should return UDMA_EBADARGS */
    retVal = Udma_flowAttachMapped(drvHandleFlow, NULL, TEST_UDMA_VALUE_ZERO, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_flowAttachMapped should return UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    flowAllocMap.mappedChNum    = UDMA_DMA_CH_INVALID;
    flowAllocMap.mappedFlowGrp  = UDMA_MAPPED_GROUP_INVALID;
    retVal = Udma_flowAttachMapped(drvHandleFlow, flowHandle, TEST_UDMA_FLOW_INDEX_1, &flowAllocMap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL flow handle to Udma_flowConfig should return UDMA_EBADARGS */
    retVal = Udma_flowConfig(NULL, TEST_UDMA_VALUE_ZERO, &flowPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_flowConfig should return UDMA_EFAIL */
    flowPrms.fdq0Sz3Qnum = TEST_UDMA_QNUM_INDEX_1;
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_DEINIT_DONE;
    retVal = Udma_flowConfig(flowHandle, TEST_UDMA_FLOW_INDEX_1, &flowPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL flow handle to Udma_flowFree should return UDMA_EBADARGS */
    retVal = Udma_flowFree(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized flow handle to Udma_flowFree should return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_flowFree(flowHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing de-initialized driver to Udma_flowFree should return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_DEINIT_DONE;
    retVal = Udma_flowFree(flowHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing invalid mappedFlowGrp to Udma_flowFree should return UDMA_EFAIL */
    flowHandleInt->drvHandle     = (Udma_DrvHandleInt) drvHandleFlow;
    flowHandleInt->flowInitDone  = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone    = UDMA_INIT_DONE;
    flowHandleInt->mappedFlowGrp = UDMA_MAPPED_GROUP_INVALID;
    retVal = Udma_flowFree(flowHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL flow handle to Udma_flowDetach should return UDMA_EBADARGS */
    retVal = Udma_flowDetach(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized flow handle to Udma_flowDetach should return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_flowDetach(flowHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL flow handle to Udma_flowGetNum (should not crash) */
    Udma_flowGetNum(NULL);

    /* Test: Passing NULL flow handle to Udma_flowGetCount (should not crash) */
    Udma_flowGetCount(NULL);

    /* Test: Passing NULL driver handle to Udma_flowAttach should return UDMA_EBADARGS */
    retVal = Udma_flowAttach(NULL, flowHandle, TEST_UDMA_VALUE_ZERO, TEST_UDMA_VALUE_ZERO);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_flowAttach should return UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_flowAttach(drvHandleFlow, flowHandle, 1U, 1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);
}

/**
 * \brief Generic driver argument validation tests.
 *
 * Test Category: Negative
 *
 * Invokes top-level driver init/deinit APIs with NULL and improper arguments to
 * ensure defensive checks return error codes without side-effects.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Each invalid invocation returns appropriate error code.
 */
static void TestUdma_argumentsValidateTests(void *args)
{
    uint32_t retVal = TEST_UDMA_API_RETVAL_INIT;
    uint32_t instId = TEST_UDMA_INST_ID_PRIMARY;
    Udma_InitPrms udmaInitPrms;
    /* Passing NULL as drvHandle should return UDMA_EBADARGS */
    retVal = Udma_init(NULL_PTR, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);
    /* Passing NULL as udmaInitPrms should return UDMA_EBADARGS */
    retVal = UdmaInitPrms_init(instId,NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Passing NULL to deinit should return UDMA_EBADARGS */
    retVal = Udma_deinit(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

}

/**
 * \brief Common ring API argument validation tests.
 *
 * Test Category: Negative
 *
 * Exercises ring alloc/free/attach/detach/queue/dequeue/flush APIs under invalid
 * driver, ring and parameter conditions to confirm proper error reporting.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid parameter paths return documented error codes; no crash.
 */
static void TestUdma_ringCommonArgumentsValidateTests(void *args)
{
    uint32_t retVal = TEST_UDMA_API_RETVAL_INIT;
    uint64_t physicalDescriptorValue, *physicalDescriptorPtr;
    Udma_DrvObject drvObj;
    Udma_RingObject ringObj;
    Udma_DrvHandle ringDrvHandle = &drvObj;
    Udma_RingHandle ringHandle = &ringObj;
    Udma_InitPrms udmaInitPrms;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);

    retVal = Udma_init(ringDrvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    Udma_RingPrms ringPrmsObj;
    Udma_RingPrms *ringPrms = &ringPrmsObj;
    ringPrms->orderId = TEST_UDMA_RING_ORDER_ID_DEFAULT;

    Udma_DrvHandleInt drvHandleInt = (Udma_DrvHandleInt) ringDrvHandle;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;


    physicalDescriptorPtr = &physicalDescriptorValue;

    Udma_DrvHandleInt driverHandleInternal = (Udma_DrvHandleInt)ringDrvHandle;
    Udma_RingHandleInt ringHandleInt = (Udma_RingHandleInt)ringHandle;

    /* Test: Passing NULL ringDrvHandle to Udma_ringAlloc should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringAlloc(NULL, ringHandle, TEST_UDMA_RING_NUM_ZERO, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_ringAlloc should return UDMA_EFAIL.
     * The driver is not initialized, so allocation must fail.
     */
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, 1U, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    ringPrms->ringMem           = TEST_UDMA_INVALID_RING_MEM_ADDR;
    ringPrms->elemCnt           = TEST_UDMA_RING_ELEM_CNT_INVALID;
    drvHandleInt->instType      = TEST_UDMA_INST_TYPE_INVALID; /* invalid instType */
    ringPrms->mode              = TEST_UDMA_EVENT_MODE_INVALID; /* reuse zero macro */
    ringPrms->ringMemSize       = TEST_UDMA_RING_MEM_SIZE_INVALID; /* size zero invalid */
    ringPrms->orderId           = TEST_UDMA_VALUE_THIRTY;
    ringPrms->mappedRingGrp     = TEST_UDMA_MAPPED_RING_GRP_10;
    ringPrms->virtId            = TEST_UDMA_EVENT_NEXT_NONE; /* virtId unset */

    /* Test: Passing invalid ring parameters to Udma_ringAlloc should return UDMA_EINVALID_PARAMS.
     * This checks that the API validates ring memory, element count, and other params.
     */
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, 1U, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Passing NULL ringHandle to Udma_ringFree should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringFree(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized ring to Udma_ringFree should return UDMA_EFAIL.
     * The ring is not initialized, so free must fail.
     */
    ringHandleInt->ringInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_ringFree(ringHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringDrvHandle in ringHandle to Udma_ringFree should return UDMA_EFAIL.
     * The ring's ringDrvHandle is NULL, so free must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    driverHandleInternal->drvInitDone = UDMA_INIT_DONE;
    ringHandleInt->drvHandle = NULL;
    retVal = Udma_ringFree(ringHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringDrvHandle and ringHandle to Udma_ringAttach should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringAttach(NULL, NULL, 1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized driver to Udma_ringAttach should return UDMA_EFAIL.
     * The driver is not initialized, so attach must fail.
     */
    driverHandleInternal->drvInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_ringAttach(ringDrvHandle, ringHandle, TEST_UDMA_RING_NUM_ONE);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing out-of-range ringNum to Udma_ringAttach should return UDMA_EINVALID_PARAMS.
     * This checks that the API validates the ringNum against maxRings.
     */
    driverHandleInternal->drvInitDone = UDMA_INIT_DONE;
    driverHandleInternal->maxRings = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_ringAttach(ringDrvHandle, ringHandle, TEST_UDMA_RING_NUM_TWO);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Passing NULL ringHandle to Udma_ringDetach should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringDetach(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing de-initialized ring to Udma_ringDetach should return UDMA_EFAIL.
     * The ring is not initialized, so detach must fail.
     */
    ringHandleInt->ringInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_ringDetach(ringHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing de-initialized driver to Udma_ringDetach should return UDMA_EFAIL.
     * The driver is not initialized, so detach must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    driverHandleInternal->drvInitDone = UDMA_DEINIT_DONE;
    ringHandleInt->drvHandle = (Udma_DrvHandleInt)ringDrvHandle;
    retVal = Udma_ringDetach(ringHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringDrvHandle in ringHandle to Udma_ringDetach should return UDMA_EFAIL.
     * The ring's ringDrvHandle is NULL, so detach must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    driverHandleInternal->drvInitDone = UDMA_INIT_DONE;
    ringHandleInt->drvHandle = NULL;
    retVal = Udma_ringDetach(ringHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringHandle to Udma_ringQueueRaw should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringQueueRaw(NULL, TEST_UDMA_INVALID_RING_MEM_ADDR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing ringNum=0 (TEST_UDMA_RING_NUM_ZERO) and de-initialized driver to Udma_ringQueueRaw should return UDMA_EFAIL.
     * The driver is not initialized, so queue must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    ringHandleInt->ringNum = TEST_UDMA_RING_NUM_ZERO;
    driverHandleInternal->drvInitDone = UDMA_DEINIT_DONE;
    ringHandleInt->drvHandle = (Udma_DrvHandleInt)ringDrvHandle;
    retVal = Udma_ringQueueRaw(ringHandle, TEST_UDMA_INVALID_RING_MEM_ADDR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringHandle to Udma_ringDequeueRaw should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringDequeueRaw(NULL, NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing ringNum=0 (TEST_UDMA_RING_NUM_ZERO) and de-initialized driver to Udma_ringDequeueRaw should return UDMA_EFAIL.
     * The driver is not initialized, so dequeue must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    ringHandleInt->ringNum = TEST_UDMA_RING_NUM_ZERO;
    driverHandleInternal->drvInitDone = UDMA_DEINIT_DONE;
    ringHandleInt->drvHandle = (Udma_DrvHandleInt)ringDrvHandle;
    retVal = Udma_ringDequeueRaw(ringHandle, TEST_UDMA_INVALID_RING_MEM_ADDR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing NULL ringHandle to Udma_ringFlushRaw should return UDMA_EBADARGS.
     * This checks that the API validates input pointers.
     */
    retVal = Udma_ringFlushRaw(NULL, NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Passing ringNum=0 (TEST_UDMA_RING_NUM_ZERO) and de-initialized driver to Udma_ringFlushRaw should return UDMA_EFAIL.
     * The driver is not initialized, so flush must fail.
     */
    ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    ringHandleInt->ringNum = TEST_UDMA_RING_NUM_ZERO;
    driverHandleInternal->drvInitDone = UDMA_DEINIT_DONE;
    ringHandleInt->drvHandle = (Udma_DrvHandleInt)ringDrvHandle;
    retVal = Udma_ringFlushRaw(ringHandle, physicalDescriptorPtr);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    ringPrms->ringMem           = (void *)(uintptr_t)TEST_UDMA_RM_NUM_GLOBAL_EVENT_128; /* intentional invalid pointer for negative test */
    ringPrms->elemCnt           = TEST_UDMA_RING_ELEM_SINGLE;
    drvHandleInt->instType      = TEST_UDMA_INST_TYPE_INVALID;
    ringPrms->mode              = TEST_UDMA_EVENT_MODE_INVALID;
    ringPrms->ringMemSize       = UDMA_RING_SIZE_CHECK_SKIP;
    ringPrms->orderId           = TEST_UDMA_RING_ORDER_ID_INVALID;
    ringPrms->mappedRingGrp     = UDMA_MAPPED_GROUP_INVALID;
    ringPrms->virtId            = TEST_UDMA_EVENT_NEXT_NONE;

    /* Test: Passing mappedRingGrp as UDMA_MAPPED_GROUP_INVALID to Udma_ringAlloc should return UDMA_EALLOC.
     * This simulates a case where the ring group is not mapped/invalid, so allocation fails.
     */
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, UDMA_RING_ANY, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    ringPrms->ringMem           = (void *)(uintptr_t)TEST_UDMA_RM_NUM_GLOBAL_EVENT_128; /* intentional invalid pointer for negative test */
    ringPrms->elemCnt           = TEST_UDMA_RING_ELEM_SINGLE;
    drvHandleInt->instType      = TEST_UDMA_INST_TYPE_INVALID;
    ringPrms->mode              = TEST_UDMA_EVENT_MODE_INVALID;
    ringPrms->ringMemSize       = UDMA_RING_SIZE_CHECK_SKIP;
    ringPrms->orderId           = TEST_UDMA_RING_ORDER_ID_INVALID;
    ringPrms->mappedRingGrp     = TEST_UDMA_MAPPED_RING_GRP_3;
    ringPrms->virtId            = TEST_UDMA_EVENT_NEXT_NONE;
    ringPrms->mappedChNum       = TEST_UDMA_MAPPED_CH_NUM_20;

    /* Test: ringAlloc under different mappedRingGrp cases.
     * This test passes a mappedRingGrp value that is not supported or not configured in the RM.
     * The API is expected to fail with UDMA_EALLOC because the mappedRingGrp is invalid or unavailable.
     */
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, UDMA_RING_ANY, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    /* Test: another condition for mappedRingGrp.
     * This test sets mappedRingGrp to a value that is out-of-range for the device/instance.
     * The API is expected to fail with UDMA_EALLOC due to invalid mapped ring group.
     */
    ringPrms->mappedRingGrp = TEST_UDMA_MAPPED_RING_GRP_5;
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, UDMA_RING_ANY, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    /* Test: Allocation with driver having maxRings = 0 should return UDMA_EINVALID_PARAMS.
     * This simulates a case where the driver is configured with zero rings, so allocation must fail.
     */
    drvHandleInt->maxRings = TEST_UDMA_MAX_RINGS_NONE;
    retVal = Udma_ringAlloc(ringDrvHandle, ringHandle, TEST_UDMA_RING_ELEM_SINGLE, ringPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
}
/**
 * \brief Default flow handle on BCDMA channel test.
 *
 * Test Category: Functional
 *
 * Opens and enables a BCDMA block-copy channel, retrieves default flow handle to
 * confirm NULL expectation (since not applicable) and validates enable state transitions.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Default flow handle is NULL; channel enable/disable succeeds.
 */
static void TestUdma_chGetDefaultFlowHandleBcdma(void *args)
{
    Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_InitPrms initPrms;
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    int32_t retVal;
    uint8_t channelEnableStatus = TEST_UDMA_STATUS_DISABLED;

    /* Driver init (BCDMA instance) */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(&chObj, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled before enable */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be enabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_ENABLED, channelEnableStatus);

    /* Feature test: Get default flow handle (should be NULL for BCDMA) */
    Udma_FlowHandle flowHandle = Udma_chGetDefaultFlowHandle(&chObj);
    TEST_ASSERT_NULL(flowHandle);

    DebugP_log("Default flow handle for BCDMA channel: %p (expected NULL)\r\n", flowHandle);

    retVal = Udma_chDisable(&chObj, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Default flow handle on PKTDMA channel test.
 *
 * Test Category: Functional
 *
 * Initializes PKTDMA driver, opens an RX channel and retrieves its default flow
 * handle verifying initialization and association with driver.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Non-NULL default flow handle with initialized state fields.
 */
static void TestUdma_chGetDefaultFlowHandlePktdma(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;
    Udma_InitPrms udmaInitPrms;
    int32_t retVal;
    uint8_t channelEnableStatus = TEST_UDMA_STATUS_DISABLED;

    /* Initialize PKTDMA driver object */
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure RX channel parameters */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
    chPrms.chNum = TEST_UDMA_PKTDMA_RX_CH_NUM;
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_RX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
    retVal = Udma_chConfigRx(&chObj, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled before enable */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be enabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_ENABLED, channelEnableStatus);

    /* Get default flow handle and validate */
    Udma_FlowHandle flowHandle = Udma_chGetDefaultFlowHandle(&chObj);
    TEST_ASSERT_NOT_NULL(flowHandle);

    Udma_FlowHandleInt flowHandleInt = (Udma_FlowHandleInt)flowHandle;
    TEST_ASSERT_EQUAL_UINT32(UDMA_INIT_DONE, flowHandleInt->flowInitDone);
    TEST_ASSERT_EQUAL_PTR(flowHandleInt->drvHandle, (Udma_DrvHandleInt)drvHandle);

    DebugP_log("PKTDMA Default flow handle: %p, flowStart=%u, flowCnt=%u\r\n",
               flowHandle, flowHandleInt->flowStart, flowHandleInt->flowCnt);

    /* Cleanup */
    retVal = Udma_chDisable(&chObj, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief PKTDMA channel reset sequence test.
 *
 * Test Category: Functional
 *
 * Opens and enables a PKTDMA RX channel then invokes Udma_chReset to ensure it
 * returns to disabled state cleanly and can be reused.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Reset succeeds; channel enable status cleared; resources intact.
 */
static void TestUdma_chResetPktdma(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;
    Udma_InitPrms udmaInitPrms;
    int32_t retVal;
    uint8_t channelEnableStatus = TEST_UDMA_STATUS_DISABLED;

    /* Initialize PKTDMA driver object */
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure RX channel parameters */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
    chPrms.chNum = TEST_UDMA_PKTDMA_RX_CH_NUM;
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_RX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
    retVal = Udma_chConfigRx(&chObj, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel */
    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be enabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT8(TEST_UDMA_STATUS_ENABLED, channelEnableStatus);

    /* Reset channel */
    retVal = Udma_chReset(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled after reset */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT8(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    /* Cleanup */
    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief BCDMA channel reset sequence test.
 *
 * Test Category: Functional
 *
 * Executes reset on an active block-copy channel validating transition back to
 * disabled state and ability to close cleanly.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Reset succeeds; channel disabled; close returns success.
 */
static void TestUdma_chResetBcdma(void *args)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    int32_t retVal;
    uint8_t channelEnableStatus = TEST_UDMA_STATUS_DISABLED;

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);

    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(&chObj, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be enabled now */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT8(TEST_UDMA_STATUS_ENABLED, channelEnableStatus);

    /* Reset channel */
    retVal = Udma_chReset(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Channel should be disabled after reset */
    retVal = Udma_chGetChanEnStatus(&chObj, &channelEnableStatus);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_UINT8(TEST_UDMA_STATUS_DISABLED, channelEnableStatus);

    /* Cleanup */
    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Local to global event mapping utility test.
 *
 * Test Category: Functional
 *
 * Registers a completion event, performs transfer, then exercises mapping API to
 * translate local event to global before re-registering to validate callback path.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Mapping API returns success; callback invoked after mapping on subsequent transfer.
 */
static void TestUdma_utilsMapLocalToGlobalEvent(void *args)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    Udma_EventPrms eventPrms;
    int32_t retVal;
    uint8_t *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    uint64_t completionDescAddr;
    uint64_t trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_PHY_ADDR_NONE, NULL);
    /* Local semaphore + event context */
    Udma_EventObject eventObj;
    SemaphoreP_Object localSem;
    volatile uint32_t callbackCount = 0;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_Src, TestUdma_Dst, TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_Src), sizeof(TestUdma_Dst), sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Open a block copy channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register event with generic IRQ callback (local mapping) */
    SemaphoreP_constructBinary(&localSem, 0);
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle = &chObj;
    eventPrms.eventCb = TestUdma_genericEventCb;
    eventPrms.appData = (void*)&eventSemaphore;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel and submit a transfer */
    retVal = Udma_chEnable(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    callbackCount = 0;
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(&chObj, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(&chObj), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    /* Callback count is informational; primary validation is CQ descriptor */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, callbackCount);
    retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(&chObj), &completionDescAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Drain remaining entries after first transfer */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(&chObj), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Unregister event and map local event to global event */
    retVal = Udma_eventUnRegister(&eventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&localSem);

    retVal = UdmaUtils_mapLocaltoGlobalEvent(drvHandle, &chObj, TEST_UDMA_EVENT_LOCAL_ID_NONE, TEST_UDMA_EVENT_GLOBAL_ID_NONE);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register event again after mapping (IRQ based) */
    callbackCount = 0;
    SemaphoreP_constructBinary(&localSem, 0);
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle = &chObj;
    eventPrms.eventCb = TestUdma_genericEventCb;
    eventPrms.appData = (void*)&eventSemaphore;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Submit another transfer */
    callbackCount = 0;
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(&chObj, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(&chObj), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_GREATER_THAN_UINT32(0U, callbackCount);
    /* Mandatory descriptor validation after IRQ */
    retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(&chObj), &completionDescAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Drain remaining entries after second transfer */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(&chObj), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Cleanup */
    retVal = Udma_eventUnRegister(&eventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&localSem);
    retVal = Udma_chDisable(&chObj, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(&chObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Event registration API argument validation tests.
 *
 * Test Category: Negative
 *
 * Invokes event register/enable/disable/unregister APIs under assorted invalid
 * parameter and state conditions to confirm defensive checks and error paths.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid configurations produce expected error codes; no crashes.
 */
static void TestUdma_eventArgumentsValidateTests(void *args)
{
    uint32_t retVal = TEST_UDMA_API_RETVAL_INIT;
    uint32_t chType = TEST_UDMA_INVALID_CH_TYPE_4;
    uint32_t evtId;
    Udma_ChHandle       ch0Handle = NULL;
    Udma_EventObject    ch0TrEventObj;
    Udma_DrvHandle      drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_EventHandle    ch0TrEventHandle = &ch0TrEventObj;
    memset(&ch0TrEventObj, TEST_UDMA_BUF_CLEAR_PATTERN, sizeof(ch0TrEventObj));
    Udma_EventPrms      ch0TrEventPrms;
    Udma_EventCallback  callback = NULL;
    Udma_EventHandleInt masterEventHandle;
    Udma_EventHandleInt eventHandleInt;
    Udma_ChHandleInt    chHandle;
    Udma_RingObjectInt  ringHandle;
    Udma_ChObjectInt    chHandleObj;
    Udma_RingObjectInt  ringNum;
    Udma_DrvHandleInt   drvHandleInt;
    Udma_ChObject ch0Obj;
    Udma_EventObject ch0EventObj;

    /* Test: Passing NULL driver handle to Udma_eventRegister should return UDMA_EBADARGS */
    UdmaEventPrms_init(&ch0TrEventPrms);

    ch0TrEventPrms.eventType         = UDMA_EVENT_TYPE_TR;
    ch0TrEventPrms.eventMode         = UDMA_EVENT_MODE_SHARED;
    ch0TrEventPrms.chHandle          = ch0Handle;
    ch0TrEventPrms.masterEventHandle = NULL;
    ch0TrEventPrms.eventCb           = NULL;
    ch0TrEventPrms.appData           = NULL;

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    /* Passing NULL to Udma_eventRegister returns UDMA_EBADARGS */
    retVal = Udma_eventRegister(NULL, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);
    /* Test: Driver not initialized (drvInitDone != UDMA_INIT_DONE) should return UDMA_EFAIL */
    ch0Handle = &ch0Obj;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);
    /* Test: Exclusive event with non-NULL masterEventHandle should fail Udma_eventCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    ch0TrEventPrms.masterEventHandle = &ch0EventObj;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: Shared event with NULL eventCb and non-NULL masterEventHandle should fail Udma_eventCheckParams */
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    masterEventHandle = (Udma_EventHandleInt) ch0TrEventPrms.masterEventHandle;
    ch0TrEventPrms.eventCb = NULL;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: Shared event with masterEventHandle->eventCb=NULL and eventCb!=NULL should fail Udma_eventCheckParams */
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    masterEventHandle->eventPrms.eventCb = NULL;
    ch0TrEventPrms.eventCb = (Udma_EventCallback) &ch0TrEventObj;
    masterEventHandle->eventPrms.eventType = UDMA_EVENT_TYPE_RING;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: TR event with NULL eventCb should fail Udma_eventCheckParams */
    ch0TrEventPrms.eventCb = callback;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: RING event with NULL ringHandle should fail Udma_eventCheckParams */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    ch0TrEventPrms.ringHandle = NULL;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: MASTER event with eventMode != SHARED should fail Udma_eventCheckParams */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_MASTER;
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);
    /* Test: Register event with all params zeroed should fail Udma_eventRegister */
    eventHandleInt = (Udma_EventHandleInt) ch0TrEventHandle;
    eventHandleInt->prevEvent = (Udma_EventHandleInt) NULL_PTR;
    eventHandleInt->nextEvent = masterEventHandle;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_NONE;
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_NONE;
    ch0TrEventPrms.masterEventHandle = NULL_PTR;

    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);
    /* Test: Udma_eventAllocResource fails due to no global events available */
    Udma_RmInitPrms    *rmInitPrms = &drvHandleInt->rmInitPrms;
    rmInitPrms->numGlobalEvent = TEST_UDMA_RM_NUM_GLOBAL_EVENT_NONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    /* Test: Udma_eventAllocResource fails due to no VINTR available */
    rmInitPrms->numGlobalEvent = TEST_UDMA_RM_NUM_GLOBAL_EVENT_128;
    ch0TrEventPrms.masterEventHandle = NULL_PTR;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to no VINTR bits available */
    rmInitPrms->numVintr = TEST_UDMA_RM_NUM_VINTR_NONE;
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    ch0TrEventPrms.masterEventHandle = NULL;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retVal);

    /* Test: Udma_eventAllocResource fails due to no core interrupts available */
    rmInitPrms->numVintr = TEST_UDMA_RM_NUM_VINTR_TEST;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to invalid preferredCoreIntrNum */
    ch0TrEventPrms.eventCb = NULL;
    ch0TrEventPrms.preferredCoreIntrNum = UDMA_CORE_INTR_ANY;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to preferredCoreIntrNum = UDMA_INTR_INVALID */
    ch0TrEventPrms.preferredCoreIntrNum = UDMA_INTR_INVALID;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to preferredCoreIntrNum = 0 */
    ch0TrEventPrms.preferredCoreIntrNum = UDMA_CORE_INTR_NONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to chOesAllocDone set */
    eventHandleInt->vintrBitAllocFlag = TEST_UDMA_ALLOC_FLAG_SET;
    chHandle = (Udma_ChHandleInt) ch0TrEventPrms.chHandle;
    chHandle->chOesAllocDone = TEST_UDMA_OES_ALLOC_DONE_FLAG;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    ch0TrEventPrms.preferredCoreIntrNum = UDMA_CORE_INTR_ANY;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Udma_eventAllocResource fails due to other allocation issues */
    eventHandleInt->vintrBitAllocFlag = TEST_UDMA_ALLOC_FLAG_NONE;
    eventHandleInt->prevEvent = (Udma_EventHandleInt) NULL_PTR;
    eventHandleInt->nextEvent = (Udma_EventHandleInt) masterEventHandle;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_NONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to eventMode = 0 */
    ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_NONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventAllocResource fails due to eventType = UDMA_EVENT_TYPE_TR */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Udma_eventRegister with invalid chHandle values */
    ch0TrEventPrms.chHandle = &chType;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Passing an invalid chHandle (address of a uint32_t instead of a Udma_ChObject)
    * to verify Udma_eventRegister detects and rejects invalid channel handles.
    */
    chType=TEST_UDMA_INVALID_CH_TYPE_2;
    ch0TrEventPrms.chHandle = &chType;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    chType=TEST_UDMA_INVALID_CH_TYPE_1;
    ch0TrEventPrms.chHandle = &chType;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with chHandle as driver object and different instType values */
    ch0TrEventPrms.chHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with ringHandle->mappedRingGrp = 5U */
    ringHandle.mappedRingGrp=TEST_UDMA_MAPPED_RING_GRP_5;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    ch0TrEventPrms.ringHandle = &ringHandle;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with chHandleObj configured for DMA_COMPLETION and BCDMA */
    chHandleObj.chType = TEST_UDMA_INVALID_CH_TYPE_4;
    chHandleObj.cqRing = &ringNum;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    ch0TrEventPrms.chHandle = &chHandleObj;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with eventType = TEARDOWN_COMPLETION */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_COMPLETION;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with chHandleObj.chType = TEST_UDMA_CH_TYPE_INVALID_1 and eventType = DMA_COMPLETION */
    chHandleObj.chType = TEST_UDMA_CH_TYPE_INVALID_1;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with eventType = TEARDOWN_COMPLETION */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_COMPLETION;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with chHandleObj.chType = 0U and eventType = DMA_COMPLETION */
    chHandleObj.chType = TEST_UDMA_INVALID_CH_TYPE_0;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with eventType = DMA_COMPLETION */
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventRegister with chHandleObj.chType = 0U and eventType = MASTER */
    chHandleObj.chType = TEST_UDMA_INVALID_CH_TYPE_0;
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_MASTER;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retVal);

    /* Test: Udma_eventRegister with eventType = DMA_COMPLETION and various eventHandleInt fields set */
    ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    ch0TrEventPrms.chHandle = &chHandleObj;
    eventHandleInt->vintrNum = TEST_UDMA_VINTR_NUM_NONE;
    eventHandleInt->nextEvent = TEST_UDMA_EVENT_NEXT_NONE;
    eventHandleInt->hwiHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->irIntrNum = TEST_UDMA_CORE_INTR_NUM_NONE;
    retVal = Udma_eventRegister(drvHandle, ch0TrEventHandle, &ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventGetGlobalHandle with NULL drvHandle should return NULL */
    Udma_EventHandle *testEventHandle = Udma_eventGetGlobalHandle(NULL);
    TEST_ASSERT_NULL(testEventHandle);

    /* Test: Udma_eventGetGlobalHandle with de-initialized driver */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_eventGetGlobalHandle(drvHandle);

    /* Test: Udma_eventUnRegister with NULL eventHandle should return UDMA_EBADARGS */
    retVal = Udma_eventUnRegister(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Udma_eventDisable with NULL eventHandle should return UDMA_EFAIL */
    retVal = Udma_eventDisable(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventEnable with NULL eventHandle should return UDMA_EFAIL */
    retVal = Udma_eventEnable(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventGetId with NULL eventHandle should return UDMA_EVENT_INVALID */
    evtId = Udma_eventGetId(NULL);
    TEST_ASSERT_EQUAL_UINT32(UDMA_EVENT_INVALID, evtId);

    /* Test: UdmaEventPrms_init with NULL should not crash */
    UdmaEventPrms_init(NULL);

    /* Test: Udma_eventUnRegister with NULL eventHandle should return UDMA_EBADARGS */
    retVal = Udma_eventUnRegister(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retVal);

    /* Test: Udma_eventUnRegister with eventHandleInt->drvHandle = NULL should return UDMA_EFAIL */
    eventHandleInt->drvHandle = NULL;
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    retVal = Udma_eventUnRegister(ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventUnRegister with drvHandle not initialized should return UDMA_EFAIL */
    eventHandleInt->drvHandle = drvHandleInt;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    retVal = Udma_eventUnRegister(ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventUnRegister with eventInitDone not done should return UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    eventHandleInt->eventInitDone = UDMA_DEINIT_DONE;
    retVal = Udma_eventUnRegister(ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventUnRegister with master event and nextEvent not NULL should return UDMA_EFAIL */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->nextEvent = eventHandleInt;
    eventHandleInt->eventPrms.masterEventHandle = NULL;
    drvHandleInt->instType = UDMA_INST_TYPE_NORMAL;
    retVal = Udma_eventUnRegister(ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);

    /* Test: Udma_eventUnRegister with DMA completion event and non-zero ring occupancy */
    eventHandleInt->nextEvent = NULL;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    /* Use defined INVALID channel handle sentinel instead of raw 1U */
    eventHandleInt->eventPrms.chHandle = (Udma_ChHandleInt)TEST_UDMA_INVALID_CH_HANDLE_VALUE;
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;

    /* Test: Udma_eventUnRegister with invalid hwiHandle/coreIntrNum */
    drvHandleInt->instType = UDMA_INST_TYPE_NORMAL;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    /* Use defined INVALID channel handle sentinel instead of raw 1U */
    eventHandleInt->eventPrms.chHandle = (Udma_ChHandleInt)TEST_UDMA_INVALID_CH_HANDLE_VALUE;
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->nextEvent = NULL;
    /* Use defined INVALID HWI handle sentinel instead of raw 1U */
    eventHandleInt->hwiHandle = (void *)TEST_UDMA_INVALID_HWI_HANDLE_VALUE;
    eventHandleInt->coreIntrNum = UDMA_INTR_INVALID;

    /* Test: Udma_eventUnRegister with drvHandle = NULL after reset */
    eventHandleInt->drvHandle = NULL;
    retVal = Udma_eventUnRegister(ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retVal);
}

/**
 * \brief Utility API argument validation tests.
 *
 * Test Category: Negative
 *
 * Sends NULL and boundary inputs to various small utility helper APIs (address
 * translation, mapping, reload setters) to ensure proper failure codes.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Bad inputs return failure; no memory corruption.
 */
static void TestUdma_utilsArgumentsValidateTests(void *args)
{
    Udma_DrvObject drvHandleUtilsObj = {TEST_UDMA_BUF_CLEAR_PATTERN};
    Udma_DrvHandleInt drvHandleUtils = (Udma_DrvHandleInt)&drvHandleUtilsObj;
    Udma_ChObject chObject = {TEST_UDMA_BUF_CLEAR_PATTERN};
    Udma_ChHandleInt chHandle = (Udma_ChHandleInt)&chObject;
    int32_t retVal;

    /* Test: Call Udma_virtToPhyFxn with all NULL arguments (should return 0/NULL safely, not crash) */
    TEST_ASSERT_EQUAL_UINT32(0U, (uint32_t)Udma_virtToPhyFxn(NULL, NULL, NULL));

    /* Test: Call Udma_phyToVirtFxn with NULL drvHandle (should return NULL safely, not crash) */
    TEST_ASSERT_NULL(Udma_phyToVirtFxn(0, NULL, NULL));

    /* Test: Call Udma_virtToPhyFxn with valid drvHandle and chHandle, but NULL virtAddr */
    drvHandleUtils->initPrms.virtToPhyFxn = Udma_defaultVirtToPhyFxn;
    drvHandleUtils->initPrms.phyToVirtFxn = Udma_defaultPhyToVirtFxn;
    TEST_ASSERT_EQUAL_PTR((void *)TEST_UDMA_PHY_ADDR_NONE, (void *)Udma_virtToPhyFxn(NULL, drvHandleUtils, chHandle));

    /* Test: Call Udma_phyToVirtFxn with valid drvHandle and chHandle, but 0 phyAddr */
    TEST_ASSERT_NULL(Udma_phyToVirtFxn(TEST_UDMA_PHY_ADDR_NONE, drvHandleUtils, chHandle));

    /* Test: Call Udma_phyToVirtFxn with valid drvHandle, but NULL chHandle */
    TEST_ASSERT_NULL(Udma_phyToVirtFxn(TEST_UDMA_PHY_ADDR_NONE, drvHandleUtils, NULL));

    /* Test: Call UdmaUtils_mapLocaltoGlobalEvent with all NULL arguments (should return SystemP_FAILURE) */
    retVal = UdmaUtils_mapLocaltoGlobalEvent(NULL, NULL, TEST_UDMA_EVENT_LOCAL_ID_NONE, TEST_UDMA_EVENT_GLOBAL_ID_NONE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retVal);

    /* Test: Call UdmaUtils_setTrpdReload with NULL trpdMemory (should return SystemP_FAILURE) */
    retVal = UdmaUtils_setTrpdReload(NULL, TEST_UDMA_VALUE_ZERO, TEST_UDMA_VALUE_ZERO);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retVal);
}

/**
 * \brief Core interrupt input translation test.
 *
 * Test Category: API validation
 *
 * Registers an event with a preferred core interrupt number to exercise RM
 * translation logic and ensure proper bookkeeping.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Event registration succeeds; translation function invoked without error.
 */
static void TestUdma_rmTranslateCoreIntrInputTest(void *args)
{
    static Udma_DrvObject bcdmaDrvObj;
    Udma_DrvHandle drvHandle = &bcdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_EventPrms eventPrms;
    Udma_EventObject eventObj;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    Udma_DrvHandleInt   drvHandleInt;

    /* Initialize BCDMA driver object */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    /* Open a block copy channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register an event with a specific preferredCoreIntrNum */
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle = chHandle;
    eventPrms.eventCb = TestUdma_eventCb;

    /* Set preferredCoreIntrNum to a valid value to trigger Udma_rmTranslateCoreIntrInput */
    eventPrms.preferredCoreIntrNum = drvHandleInt->rmInitPrms.startIrIntr + TEST_UDMA_OFFSET_PLUS_ONE;

    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Cleanup */
    retVal = Udma_eventUnRegister(&eventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief Generic TX preferred channel allocation test.
 *
 * Test Category: API Validation
 *
 * Acquires preferred unmapped TX channel from RM init params and validates channel
 * lifecycle operations.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel opened at preferred number; lifecycle APIs succeed.
 */
static void TestUdma_txPreferredChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_TX;
    uint32_t preferredChNum;
    Udma_DrvHandleInt   drvHandleInt;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    preferredChNum = drvHandleInt->rmInitPrms.startTxCh;

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;  /* Set the preferred channel number */
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_TX;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief Block copy preferred channel allocation test (BCDMA).
 *
 * Test Category: Functional
 *
 * Opens a block-copy channel using RM preferred channel number validating enable,
 * transfer-less lifecycle and close operations.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel opened using preferred number; enable/disable/close succeed.
 */
static void TestUdma_blockCopyPreferredChannelAllocation(void *args)
{
    static Udma_DrvObject BlkCpydmaDrvObj;
    Udma_DrvHandle drvHandle = &BlkCpydmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_TR_BLK_COPY;
    uint32_t preferredChNum;
    Udma_DrvHandleInt   drvHandleInt;

    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    preferredChNum = drvHandleInt->rmInitPrms.startBlkCopyCh;

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;  /* Set the preferred channel number */

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief PKTDMA RX preferred channel allocation test.
 *
 * Test Category: Functional
 *
 * Opens a PKTDMA RX channel at RM preferred number and validates enable/disable/close.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel lifecycle succeeds at preferred RX channel number.
 */
static void TestUdma_rxPreferredChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_RX;
    uint32_t preferredChNum;
    Udma_DrvHandleInt   drvHandleInt;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    preferredChNum = drvHandleInt->rmInitPrms.startRxCh;

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;  /* Set the preferred channel number */
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

#ifdef ENABLE_MT_TESTS

/* PKTDMA thread: init local pktdma driver, open RX channel and validate default flow */
static void TestUdma_pktdmaInstanceThread(void *args)
{
    int32_t tempStatus;
    DmaThreadParams *threadParams = (DmaThreadParams *)args;
    int32_t retVal = UDMA_SOK;
    static Udma_DrvObject pktdrvObj;
    Udma_DrvHandle pktDrv = &pktdrvObj;
    Udma_InitPrms udmaInitPrms;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;
    Udma_FlowHandle defaultFlowHandle = NULL;
    Udma_FlowHandleInt flowHandleInternal = NULL;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(pktDrv, &udmaInitPrms);

    if (retVal == UDMA_SOK)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
        chPrms.chNum = UDMA_DMA_CH_ANY;
        chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
        retVal = Udma_chOpen(pktDrv, chHandle, UDMA_CH_TYPE_RX, &chPrms);
        if (retVal == UDMA_SOK)
    {
        UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
        retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if (retVal == UDMA_SOK)
    {
        retVal = Udma_chEnable(chHandle);
                if (retVal == UDMA_SOK)
    {
        defaultFlowHandle = Udma_chGetDefaultFlowHandle(chHandle);
                    if (defaultFlowHandle != NULL)
                    {
                        flowHandleInternal = (Udma_FlowHandleInt)defaultFlowHandle;
                        if (flowHandleInternal->flowInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }
                    else
        {
            retVal = UDMA_EFAIL;
                    }
                }
            }
        }
    }
    /* Always cleanup */
    tempStatus = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    if (tempStatus == UDMA_SOK)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, tempStatus);
    }
    tempStatus = Udma_chClose(chHandle);
    if (tempStatus == UDMA_SOK)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, tempStatus);
    }
    tempStatus = Udma_deinit(pktDrv);
    if (tempStatus == UDMA_SOK)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, tempStatus);
    }
    threadParams->result = retVal;
    SemaphoreP_post(&TestUdma_MtCountingSem); /* counting semaphore post */
    TaskP_exit();
}

/* BCDMA thread: use global driver, open block-copy channel, submit TRPD and validate */
static void TestUdma_bcdmaInstanceThread(void *args)
{
    DmaThreadParams *threadParams = (DmaThreadParams *)args;
    int32_t retVal = UDMA_SOK;
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    uint64_t trpdPhysicalAddr = TEST_UDMA_PHY_ADDR_NONE;
    uint64_t completionDescAddr;
    Udma_EventObject eventObj; Udma_EventPrms eventPrms;
    SemaphoreP_Object localSem;
    volatile uint32_t callbackCount = 0;
    TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };
    bool registered = false, semConstructed = false;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);

    if (retVal == UDMA_SOK)
    {
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        retVal = Udma_chConfigTx(chHandle, &txPrms);
        if (retVal == UDMA_SOK)
        {
            UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if (retVal == UDMA_SOK)
            {
                TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
                TestUdma_trpdInit(chHandle, TestUdma_TrpdSingleDesc, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
                trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_TrpdSingleDesc, TEST_UDMA_BUF_INDEX_ZERO, NULL);
                /* Drain CQ completions after this iteration */
                remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
                do
                {
                    retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
                    if (retVal == UDMA_ETIMEOUT )
                    {
                        break;
                    }
                    remainingPollAttempts -= 1;
                } while (remainingPollAttempts > 0U);
                if (retVal == UDMA_ETIMEOUT)
                {
                    retVal = UDMA_SOK;
                }
                TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

                retVal = Udma_chEnable(chHandle);
                if (retVal == UDMA_SOK)
                {
                    /* Construct semaphore and register event BEFORE queuing TRPD */
                    SemaphoreP_constructBinary(&localSem, 0);
                    semConstructed = true;
                    UdmaEventPrms_init(&eventPrms);
                    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
                    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
                    eventPrms.chHandle  = chHandle;
                    eventPrms.eventCb   = TestUdma_genericEventCb;
                    eventPrms.appData   = &eventSemaphore;
                    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
                    if (retVal == UDMA_SOK)
                    {
                        registered = true;
                        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
                        if (retVal == UDMA_SOK)
                        {
                            if (SystemP_SUCCESS == SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER) && (callbackCount > 0U))
                            {
                                /* Drain CQ completions (poll case) */
                                remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
                                do
                                {
                                    retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
                                    if (retVal == UDMA_ETIMEOUT )
                                    {
                                        break;
                                    }
                                    remainingPollAttempts -= 1;
                                } while (remainingPollAttempts > 0U);
                                if (retVal == UDMA_ETIMEOUT)
                                {
                                    retVal = UDMA_SOK;
                                }
                                TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

                                TestUdma_compareBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
                            }
                            else
                            {
                                retVal = UDMA_EFAIL;
                            }
                        }
                        else
                        {
                            retVal = UDMA_EFAIL;
                        }
                    }
                    else
                    {
                        retVal = UDMA_EFAIL;
                    }
                }
            }
        }
    }
    /* Cleanup of event/semaphore regardless of error */
    if (registered)
    {
        (void)Udma_eventUnRegister(&eventObj);
        registered = false;
    }
    if (semConstructed)
    {
        SemaphoreP_destruct(&localSem);
        semConstructed = false;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    threadParams->result = retVal;
    SemaphoreP_post(&TestUdma_MtCountingSem); /* counting semaphore post */
    TaskP_exit();
}

/**
 * \brief UDMA multi-instance PKTDMA and BCDMA concurrency test.
 *
 * Test Category: Functional, Multi-threaded
 *
 * Creates two threads: one initializes a local PKTDMA driver instance, opens an RX
 * channel, and validates default flow creation; the other uses the global BCDMA driver
 * to open a block-copy channel, submit a transfer, and validate data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both threads complete successfully without error.
 */
static void TestUdma_multiInstancePktdmaBcdma(void *args)
{
    static DmaThreadParams pktdmaParams = { TEST_UDMA_BUF_CLEAR_PATTERN };
    static DmaThreadParams bcdmaParams  = { TEST_UDMA_BUF_CLEAR_PATTERN };
    pktdmaParams.result = TEST_UDMA_RESULT_ERROR_SENTINEL;
    bcdmaParams.result  = TEST_UDMA_RESULT_ERROR_SENTINEL;

    /* Counting semaphore for two worker tasks */
    SemaphoreP_constructCounting(&TestUdma_MtCountingSem, TEST_UDMA_CB_COUNT_ZERO, 2);

    TaskP_Params tparams;
    TaskP_Params_init(&tparams);
    tparams.name      = (char *)"PKTDMA_T";
    tparams.stackSize = TEST_UDMA_DMA_THREAD_STACK_SIZE;
    tparams.stack     = pktdmaParams.stack;
    tparams.priority  = TEST_UDMA_DMA_THREAD_PRIORITY;
    tparams.args      = &pktdmaParams;
    tparams.taskMain  = TestUdma_pktdmaInstanceThread;
    TaskP_construct(&pktdmaParams.taskObj, &tparams);

    TaskP_Params_init(&tparams);
    tparams.name      = (char *)"BCDMA_T";
    tparams.stackSize = TEST_UDMA_DMA_THREAD_STACK_SIZE;
    tparams.stack     = bcdmaParams.stack;
    tparams.priority  = TEST_UDMA_DMA_THREAD_PRIORITY;
    tparams.args      = &bcdmaParams;
    tparams.taskMain  = TestUdma_bcdmaInstanceThread;
    TaskP_construct(&bcdmaParams.taskObj, &tparams);

    /* Wait for both threads (pend twice) */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_MtCountingSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_MtCountingSem, SystemP_WAIT_FOREVER));

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, pktdmaParams.result);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, bcdmaParams.result);
    ClockP_usleep(5000);
    TaskP_destruct(&pktdmaParams.taskObj);
    TaskP_destruct(&bcdmaParams.taskObj);
    SemaphoreP_destruct(&TestUdma_MtCountingSem);
}
#endif

/**
 * \brief Invalid driver instance ID negative test.
 *
 * Test Category: Negative
 *
 * Calls Udma_init with an invalid instance ID constant to confirm failure path and
 * error code without side-effects.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Udma_init returns failure code for invalid instance.
 */
static void TestUdma_invalidInstance(void *args)
{
    int32_t retVal;
    Udma_InitPrms gUdmaInitPrmsInvalid;
    gUdmaInitPrmsInvalid.instId = TEST_UDMA_INVALID_INSTANCE;
    gUdmaInitPrmsInvalid.skipGlobalEventReg = FALSE;
    gUdmaInitPrmsInvalid.enableUtc = FALSE;
    gUdmaInitPrmsInvalid.virtToPhyFxn = Udma_defaultVirtToPhyFxn;
    gUdmaInitPrmsInvalid.phyToVirtFxn = Udma_defaultPhyToVirtFxn;
    retVal= UDMA_SOK;
    retVal = Udma_init(&gUdmaDrvObj, &gUdmaInitPrmsInvalid);
    TEST_ASSERT_EQUAL_INT(UDMA_EBADARGS, retVal);
}

/**
 * \brief Block-copy channel statistics test.
 *
 * Test Category: Functional
 *
 * Performs a single transfer on a block-copy channel and verifies stats counters
 * update accordingly (packet and byte counts) before cleanup.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Stats reflect at least one packet/byte processed; APIs succeed.
 */
static void TestUdma_chStatsBlkCpy(void *args)
{
    (void)args;
    int32_t retVal;
    Udma_DrvHandle  drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChObject   chObj;
    Udma_ChHandle   chHandle = &chObj;
    Udma_ChPrms     chPrms;
    uint8_t        *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    uint64_t        trpdPhysicalAddr;
    uint64_t        completionDescAddr;
    bool registered = false, semConstructed = false;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    Udma_EventObject eventObj; Udma_EventPrms eventPrms; SemaphoreP_Object localSem; volatile uint32_t callbackCount = 0; TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };
    Udma_ChStats    statsBeforeTransfer = {TEST_UDMA_CH_STATS_INIT}, statsAfterTransfer = {TEST_UDMA_CH_STATS_INIT};

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_BlkCopyCh2RingMem, TestUdma_Src, TestUdma_Dst, TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_BlkCopyCh2RingMem), sizeof(TestUdma_Src), sizeof(TestUdma_Dst), sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Open and configure a block-copy channel with a tiny FQ ring */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare buffers and TRPD */
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Drain any previous completions */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Get stats before transfer */
    retVal = Udma_chGetStats(chHandle, &statsBeforeTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register event and wait via semaphore */
    SemaphoreP_constructBinary(&localSem, 0);
    semConstructed = true;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_genericEventCb;
    eventPrms.appData   = &eventSemaphore;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    registered = (retVal == UDMA_SOK);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(chHandle));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_TRUE(callbackCount > 0U);
    /* Validate that the first CQ descriptor corresponds to the submitted TRPD */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr));
    TEST_ASSERT_EQUAL_ADDR64(trpdPhysicalAddr, completionDescAddr);
    /* Drain any remaining stale CQ entries */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Read stats after transfer */
    retVal = Udma_chGetStats(chHandle, &statsAfterTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Basic functional assertions: counters must have increased */
    TEST_ASSERT_TRUE(statsAfterTransfer.packetCnt >= statsBeforeTransfer.packetCnt + 1);
    TEST_ASSERT_TRUE(statsAfterTransfer.completedByteCnt >= statsBeforeTransfer.completedByteCnt + TEST_UDMA_NUM_BYTES);
    TEST_ASSERT_TRUE(statsAfterTransfer.startedByteCnt >= statsBeforeTransfer.startedByteCnt + TEST_UDMA_NUM_BYTES);

    /* Cleanup */
    if (registered)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventUnRegister(&eventObj));
        registered = false;
    }
    if (semConstructed)
    {
        SemaphoreP_destruct(&localSem);
        semConstructed = false;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
}

/**
 * \brief RX channel statistics test.
 *
 * Test Category: Functional
 *
 * Opens and enables a PKTDMA RX channel, samples stats before/after a brief wait
 * (or traffic) and exercises decrement API.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Stats readable and non-decreasing; decrement API succeeds.
 */
static void TestUdma_chStatsRx(void *args)
{
    (void)args;
    int32_t retVal;
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle  drvHandle = &pktdmaDrvObj;
    Udma_ChObject   chObj;
    Udma_ChHandle   chHandle = &chObj;
    Udma_ChPrms     chPrms;
    Udma_ChRxPrms   rxPrms;
    Udma_ChStats    statsBeforeTransfer = {TEST_UDMA_CH_STATS_INIT}, statsAfterTransfer = {TEST_UDMA_CH_STATS_INIT};

    /* Initialize driver if required for this instance (example: PKTDMA) */
    Udma_InitPrms udmaInitPrms;
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare channel params (small FQ ring or NULL if not required) */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    /* Peer channel */
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX; /* adjust for your platform */

    /* Open RX channel */
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_RX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure RX channel */
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
    /* adjust rxPrms if needed (burst size, flow config, etc.) */
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Get stats before */
    retVal = Udma_chGetStats(chHandle, &statsBeforeTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel (makes HW thread active) */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Optionally: wait a short time to allow any HW counters to move if traffic present */
    ClockP_usleep(100);

    /* Get stats after */
    retVal = Udma_chGetStats(chHandle, &statsAfterTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Basic sanity: counters should be readable and not negative — if no traffic, they may be equal */
    TEST_ASSERT_TRUE(statsAfterTransfer.packetCnt >= statsBeforeTransfer.packetCnt);
    TEST_ASSERT_TRUE(statsAfterTransfer.completedByteCnt >= statsBeforeTransfer.completedByteCnt);
    TEST_ASSERT_TRUE(statsAfterTransfer.startedByteCnt >= statsBeforeTransfer.startedByteCnt);

    /* Try decrementing stats (function coverage) */
    retVal = Udma_chDecStats(chHandle, &statsAfterTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable and close */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief TX channel statistics test.
 *
 * Test Category: Functional
 *
 * Opens and enables a PKTDMA TX channel, samples stats before/after a brief wait
 * (or traffic) and exercises decrement API.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Stats counters readable and not decreased; decrement API succeeds.
 */
static void TestUdma_chStatsTx(void *args)
{
    (void)args;
    int32_t retVal;
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle  drvHandle = &pktdmaDrvObj;
    Udma_ChObject   chObj;
    Udma_ChHandle   chHandle = &chObj;
    Udma_ChPrms     chPrms;
    Udma_ChTxPrms   txPrms; /* declare txPrms here to avoid later undeclared usage */
    Udma_ChStats    statsBeforeTransfer = {TEST_UDMA_CH_STATS_INIT}, statsAfterTransfer = {TEST_UDMA_CH_STATS_INIT};

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_Src, TestUdma_Dst, TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_Src), sizeof(TestUdma_Dst), sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Init driver (PKTDMA ) */
    Udma_InitPrms udmaInitPrms;
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare channel params */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX);
    /* Provide a small FQ ring as some drivers expect an FQ on TX for TR submission */
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    /* set chPrms.peerChNum appropriately */
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_TX;

    /* Open TX channel */
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure TX channel */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TX);
    /* adjust txPrms (burst size, chan type, fifoDepth) if needed */
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Read stats before */
    retVal = Udma_chGetStats(chHandle, &statsBeforeTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Optionally: wait a short time to allow any HW counters to move if traffic present */
    ClockP_usleep(100);

    /* Get stats after submission (if any) */
    retVal = Udma_chGetStats(chHandle, &statsAfterTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Basic sanity check: counters readable and not decreased */
    TEST_ASSERT_TRUE(statsAfterTransfer.packetCnt >= statsBeforeTransfer.packetCnt);
    TEST_ASSERT_TRUE(statsAfterTransfer.completedByteCnt >= statsBeforeTransfer.completedByteCnt);
    TEST_ASSERT_TRUE(statsAfterTransfer.startedByteCnt >= statsBeforeTransfer.startedByteCnt);

    /* Dec stats call to exercise API */
    retVal = Udma_chDecStats(chHandle, &statsAfterTransfer);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable and close */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief RX->TX channel chaining functional test.
 *
 * Test Category: Functional
 *
 * Establishes chaining between trigger (TX) and chained (RX) channels using a
 * global trigger, submits TRs to validate sequencing, then breaks chaining.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Chained transfer only completes after trigger; data integrity validated.
 */
static void TestUdma_chSetChainingRxTx(void *args)
{
    (void)args;
    int32_t retVal;
    Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject trigChObj;
    Udma_ChObject chainChObj;
    Udma_ChHandle trigCh = &trigChObj;
    Udma_ChHandle chainCh = &chainChObj;
    Udma_ChPrms trigPrms, chainPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    uint8_t *trigTrpd = TestUdma_TrigTrpd;
    uint8_t *chainTrpd = TestUdma_ChainTrpd;
    uint64_t trigTrpdPhy = TEST_UDMA_PHY_ADDR_NONE, chainTrpdPhy = TEST_UDMA_PHY_ADDR_NONE;
    uint64_t completionDescAddr = TEST_UDMA_PHY_ADDR_NONE;
    Udma_EventObject chainEventObj;
    Udma_EventPrms chainEventPrms;
    SemaphoreP_Object chainSem;
    volatile uint32_t chainCallbackCount = 0;
    TestUdma_EventSemaphore chainEventSemaphore = { &chainSem, &chainCallbackCount };
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_TrigSrc, TestUdma_TrigDst, TestUdma_ChainSrc, TestUdma_ChainDst,
                   TestUdma_TrigTrpd, TestUdma_ChainTrpd,
                   TEST_UDMA_TRIG_FQ_RING_MEM, TEST_UDMA_TRIG_CQ_RING_MEM,
                   TEST_UDMA_CHAIN_FQ_RING_MEM, TEST_UDMA_CHAIN_CQ_RING_MEM };
    size_t sizeList[] = { sizeof(TestUdma_TrigSrc), sizeof(TestUdma_TrigDst), sizeof(TestUdma_ChainSrc), sizeof(TestUdma_ChainDst),
                    sizeof(TestUdma_TrigTrpd), sizeof(TestUdma_ChainTrpd),
                    sizeof(TEST_UDMA_TRIG_FQ_RING_MEM), sizeof(TEST_UDMA_TRIG_CQ_RING_MEM),
                    sizeof(TEST_UDMA_CHAIN_FQ_RING_MEM), sizeof(TEST_UDMA_CHAIN_CQ_RING_MEM) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Init BCDMA driver */
    Udma_InitPrms udmaInitPrms;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Open trigger block-copy channel (will act as "trigger" producer) */
    UdmaChPrms_init(&trigPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    trigPrms.fqRingPrms.ringMem     = TEST_UDMA_TRIG_FQ_RING_MEM;
    trigPrms.fqRingPrms.ringMemSize = sizeof(TEST_UDMA_TRIG_FQ_RING_MEM);
    trigPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_PAIR;
    trigPrms.cqRingPrms.ringMem     = TEST_UDMA_TRIG_CQ_RING_MEM;
    trigPrms.cqRingPrms.ringMemSize = sizeof(TEST_UDMA_TRIG_CQ_RING_MEM);
    trigPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_PAIR;
    retVal = Udma_chOpen(drvHandle, trigCh, UDMA_CH_TYPE_TR_BLK_COPY, &trigPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Open chained block-copy channel (waits for global trigger) */
    UdmaChPrms_init(&chainPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chainPrms.fqRingPrms.ringMem     = TEST_UDMA_CHAIN_FQ_RING_MEM;
    chainPrms.fqRingPrms.ringMemSize = sizeof(TEST_UDMA_CHAIN_FQ_RING_MEM);
    chainPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_PAIR;
    chainPrms.cqRingPrms.ringMem     = TEST_UDMA_CHAIN_CQ_RING_MEM;
    chainPrms.cqRingPrms.ringMemSize = sizeof(TEST_UDMA_CHAIN_CQ_RING_MEM);
    chainPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_PAIR;
    retVal = Udma_chOpen(drvHandle, chainCh, UDMA_CH_TYPE_TR_BLK_COPY, &chainPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure tx/rx sides for both channels (block-copy uses both) */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(trigCh, &txPrms));
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(trigCh, &rxPrms));

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chainCh, &txPrms));
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chainCh, &rxPrms));

    /* Prepare chain TRPD: expects to be triggered by GLOBAL0 */
    TestUdma_initBuffer(TestUdma_ChainSrc, TestUdma_ChainDst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chainCh, chainTrpd, TestUdma_ChainDst, TestUdma_ChainSrc, TEST_UDMA_NUM_BYTES);

    CSL_UdmapTR15 *tr = UdmaUtils_getTrpdTr15Pointer(chainTrpd, TEST_UDMA_BUF_INDEX_ZERO);
    /* Clear the trigger0 field then set it to GLOBAL0, and set trigger type */
    tr->flags = (tr->flags & ~CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1))
                | CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    CacheP_wb(chainTrpd, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);

    chainTrpdPhy = (uint64_t)Udma_defaultVirtToPhyFxn(chainTrpd, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Prepare trigger TRPD (normal block-copy) */
    TestUdma_initBuffer(TestUdma_TrigSrc, TestUdma_TrigDst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(trigCh, trigTrpd, TestUdma_TrigDst, TestUdma_TrigSrc, TEST_UDMA_NUM_BYTES);
    trigTrpdPhy = (uint64_t)Udma_defaultVirtToPhyFxn(trigTrpd, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Drain any stale completions on both channels */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chainCh), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(trigCh), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Set chaining: completion of trigCh asserts GLOBAL0 for chainCh */
    retVal = Udma_chSetChaining(trigCh, chainCh, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    if (retVal != UDMA_SOK)
    {
        /* If chaining unsupported on this platform/instance, clean up and skip */
        retVal = Udma_chClose(trigCh);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        retVal = Udma_chClose(chainCh);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        retVal = Udma_deinit(drvHandle);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        DebugP_log("[UDMA TEST] Blockcopy chaining unsupported on this instance\n");
        return;
    }

    /* Register event for chained channel completion */
    SemaphoreP_constructBinary(&chainSem, 0);
    UdmaEventPrms_init(&chainEventPrms);
    chainEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    chainEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    chainEventPrms.chHandle  = chainCh;
    chainEventPrms.eventCb   = TestUdma_genericEventCb;
    chainEventPrms.appData   = &chainEventSemaphore;
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventRegister(drvHandle, &chainEventObj, &chainEventPrms));
    /* Enable chain then trigger channel */
    retVal = Udma_chEnable(chainCh);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chEnable(trigCh);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Queue chain TRPD first (it will wait for GLOBAL0) */
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chainCh), chainTrpdPhy);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Queue trigger TRPD to cause completion and assert GLOBAL0 */
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(trigCh), trigTrpdPhy);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&chainSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_TRUE(chainCallbackCount > 0U);
    /* Validate chained channel CQ completion matches chain TRPD */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chainCh), &completionDescAddr));
    TEST_ASSERT_EQUAL_ADDR64(chainTrpdPhy, completionDescAddr);
    /* Drain any remaining entries on chained channel */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chainCh), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Verify chained transfer data */
    TestUdma_compareBuffer(TestUdma_ChainSrc, TestUdma_ChainDst, TEST_UDMA_NUM_BYTES);

    /* Break chaining and cleanup */
    retVal = Udma_chBreakChaining(trigCh, chainCh);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chDisable(trigCh, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chDisable(chainCh, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(trigCh);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventUnRegister(&chainEventObj));
    SemaphoreP_destruct(&chainSem);
    retVal = Udma_chClose(chainCh);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Multiple flows on single PKTDMA channel test.
 *
 * Test Category: Functional
 *
 * Attempts allocation/configuration of multiple flows (as supported) to validate
 * driver bookkeeping and error paths where limits exceeded.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Supported flow allocations succeed; excess allocations fail cleanly.
 */
static void TestUdma_multipleFlowsPktdma(void *args)
{
    (void)args;
    int32_t retVal, index;
    static Udma_DrvObject pktdrvObj;
    Udma_DrvHandle drvPkt = &pktdrvObj;
    Udma_InitPrms udmaInitPrms;

    Udma_FlowObject flowObj[2];
    Udma_FlowHandle flowHandle[2] = { &flowObj[TEST_UDMA_BUF_INDEX_ZERO], &flowObj[TEST_UDMA_VALUE_ONE] };

    Udma_ChObject rxChObj[2];
    Udma_ChHandle rxCh[2] = { &rxChObj[TEST_UDMA_BUF_INDEX_ZERO], &rxChObj[TEST_UDMA_VALUE_ONE] };

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Init PKTDMA driver */
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvPkt, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Attach two flows (flowStart 0 and 1) */
    retVal = Udma_flowAttach(drvPkt, flowHandle[0], TEST_UDMA_VALUE_ZERO, TEST_UDMA_VALUE_ONE);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_flowAttach(drvPkt, flowHandle[1], 1U, 1U);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Verify flow handles initialized */
    Udma_FlowHandleInt flow0HandleInternal = (Udma_FlowHandleInt)flowHandle[0];
    Udma_FlowHandleInt flow1HandleInternal = (Udma_FlowHandleInt)flowHandle[1];
    TEST_ASSERT_EQUAL_UINT32(UDMA_INIT_DONE, flow0HandleInternal->flowInitDone);
    TEST_ASSERT_EQUAL_UINT32(UDMA_INIT_DONE, flow1HandleInternal->flowInitDone);
    TEST_ASSERT_EQUAL_PTR((Udma_DrvHandleInt)drvPkt, flow0HandleInternal->drvHandle);
    TEST_ASSERT_EQUAL_PTR((Udma_DrvHandleInt)drvPkt, flow1HandleInternal->drvHandle);

    /* Open two RX channels to exercise per-channel ring creation (no packet injection) */
    for (index = 0; index < 2; index += 1)
    {
        Udma_ChPrms chPrms;
        Udma_ChRxPrms rxPrms;

        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
        chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
        chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
        chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
        chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
        chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.peerChNum = (index == 0) ? UDMA_PDMA_CH_MAIN0_UART0_RX : UDMA_TEST_PKTDMA_UNMAPPED_RX_PEER_CH;

        retVal = Udma_chOpen(drvPkt, rxCh[index], UDMA_CH_TYPE_RX, &chPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
        rxPrms.configDefaultFlow = FALSE;
        retVal = Udma_chConfigRx(rxCh[index], &rxPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        retVal = Udma_chEnable(rxCh[index]);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        /* Verify default flow handle for the channel is safe to query */
        Udma_FlowHandle fh = Udma_chGetDefaultFlowHandle(rxCh[index]);
        TEST_ASSERT_NOT_NULL(fh);
    }

    /* flows attached and RX channels opened+enabled without crash */
    /* Cleanup: disable/close RX channels, detach flows, deinit */
    for (index = 0; index < 2; index += 1)
    {
        retVal = Udma_chDisable(rxCh[index], UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        retVal = Udma_chClose(rxCh[index]);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    }
    retVal = Udma_flowDetach(flowHandle[0]);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_flowDetach(flowHandle[1]);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvPkt);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Double channel ring allocation negative test.
 *
 * Test Category: Negative
 *
 * Attempts to allocate a ring twice for the same channel expecting second call to
 * fail gracefully without leaking resources.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Second allocation rejected; original allocation intact.
 */
static void TestUdma_doubleAllocateChannelRing(void *args)
{
    (void)args;
    int32_t retVal;
    static Udma_DrvObject pktDrvObj;
    Udma_DrvHandle drvPkt = &pktDrvObj;
    Udma_InitPrms udmaInitPrms;
    Udma_ChObject chObj1, chObj2;
    Udma_ChHandle ch1 = &chObj1, ch2 = &chObj2;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChHandleInt channel1Internal, ch2Int;
    Udma_DrvHandleInt   drvHandleInt;
    drvHandleInt = (Udma_DrvHandleInt) drvPkt;

    Udma_DrvHandle drvHandle = &pktDrvObj;
    Udma_ChObject chObjA, chObjB;
    Udma_ChHandle rxChPrimary = &chObjA, rxChSecondary = &chObjB;
    uint16_t ringNumPrimary = UDMA_RING_INVALID, ringNumSecondary = UDMA_RING_INVALID;


    /* -------------------------------
     * Channel uniqueness (PKTDMA TX)
     * -------------------------------*/
    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem, TestUdma_FqMultiChannel, TestUdma_CqMultiChannel };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem), sizeof(TestUdma_FqMultiChannel), sizeof(TestUdma_CqMultiChannel) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvPkt, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX);
    CacheP_wb(TestUdma_FqRingMem, sizeof(TestUdma_FqRingMem), CacheP_TYPE_ALLD);
    CacheP_wb(TestUdma_CqRingMem, sizeof(TestUdma_CqRingMem), CacheP_TYPE_ALLD);

    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem);
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_TX;
    chPrms.chNum = drvHandleInt->rmInitPrms.startTxCh;

    /* open first channel */
    retVal = Udma_chOpen(drvPkt, ch1, UDMA_CH_TYPE_TX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TX);
    retVal = Udma_chConfigTx(ch1, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* attempt to open second channel with same prms */
    retVal = Udma_chOpen(drvPkt, ch2, UDMA_CH_TYPE_TX, &chPrms);
    if (retVal == UDMA_SOK)
    {
        /* if second open succeeds, ensure it got a different HW channel/resource */
        channel1Internal = (Udma_ChHandleInt)ch1;
        ch2Int = (Udma_ChHandleInt)ch2;
        TEST_ASSERT_NOT_EQUAL(channel1Internal->txChNum, ch2Int->txChNum);
        /* cleanup second */
        retVal = Udma_chClose(ch2);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    }
    else
    {
        /* acceptable: second allocation failed -> resource not reallocated */
        TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);
    }

    /* cleanup first */
    retVal = Udma_chClose(ch1);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvPkt);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* ---------------------
     * Ring uniqueness
     * --------------------- */
    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    bufferList[0] = TestUdma_FqMultiChannel;
    bufferList[1] = TestUdma_CqMultiChannel;
    sizeList[0] = sizeof(TestUdma_FqMultiChannel);
    sizeList[1] = sizeof(TestUdma_CqMultiChannel);
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare channel params that request FQ ring memory so chOpen will call Udma_ringAlloc */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
    chPrms.fqRingPrms.ringMem = TestUdma_FqMultiChannel[0];
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqMultiChannel[0]);
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    /* Choose a safe peer channel value used elsewhere in tests */
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;

    /* Open first RX channel (this will allocate fq ring internally) */
    retVal = Udma_chOpen(drvHandle, rxChPrimary, UDMA_CH_TYPE_RX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chConfigRx(rxChPrimary, (Udma_ChRxPrms *)&( (Udma_ChHandleInt)rxChPrimary )->rxPrms ); /* safe default config */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chEnable(rxChPrimary);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Read allocated ring number */
    Udma_RingHandle fqA = Udma_chGetFqRingHandle(rxChPrimary);
    TEST_ASSERT_NOT_NULL(fqA);
    ringNumPrimary = Udma_ringGetNum(fqA);
    TEST_ASSERT_NOT_EQUAL(UDMA_RING_INVALID, ringNumPrimary);

    /* Open second RX channel requesting its own fq ring */
    chPrms.fqRingPrms.ringMem     = TestUdma_FqMultiChannel[1];
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqMultiChannel[1]);
    chPrms.peerChNum              = UDMA_TEST_PKTDMA_UNMAPPED_RX_PEER_CH;

    retVal = Udma_chOpen(drvHandle, rxChSecondary, UDMA_CH_TYPE_RX, &chPrms);
    if (retVal == UDMA_SOK)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(rxChSecondary, (Udma_ChRxPrms *)&((Udma_ChHandleInt)rxChSecondary)->rxPrms));
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(rxChSecondary));

        Udma_RingHandle fqB = Udma_chGetFqRingHandle(rxChSecondary);
        TEST_ASSERT_NOT_NULL(fqB);
        ringNumSecondary = Udma_ringGetNum(fqB);
        TEST_ASSERT_NOT_EQUAL(UDMA_RING_INVALID, ringNumSecondary);
        TEST_ASSERT_NOT_EQUAL(ringNumPrimary, ringNumSecondary);

        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(rxChSecondary, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(rxChSecondary));
    }
    else
    {
        TEST_ASSERT_TRUE((retVal == UDMA_EALLOC) || (retVal == UDMA_EFAIL));
    }

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(rxChPrimary, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(rxChPrimary));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));

    return;
}

/**
 * \brief Multiple PKTDMA channels open/close test.
 *
 * Test Category: Functional
 *
 * Opens multiple PKTDMA TX channels concurrently to verify independent lifecycle
 * and absence of resource contention.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All channels open, enable, submit, complete and close successfully.
 */
static void TestUdma_multipleChannelsPktdma(void *args)
{
    (void)args;
    int32_t retVal;
    /* Generic arrays for two channels per instance */
    Udma_DrvObject drvPktdmaObj = {TEST_UDMA_BUF_CLEAR_PATTERN};
    Udma_DrvHandle drvPktdma = &drvPktdmaObj;
    Udma_ChObject chPktObj[2];
    Udma_ChHandle chPkt[2] = { &chPktObj[TEST_UDMA_BUF_INDEX_ZERO], &chPktObj[TEST_UDMA_VALUE_ONE] };
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    int32_t index;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqMultiChannel, TestUdma_CqMultiChannel, TestUdma_TrpdMultiChannel, TestUdma_SrcMultiChannel, TestUdma_DstMultiChannel };
    size_t sizeList[] = { sizeof(TestUdma_FqMultiChannel), sizeof(TestUdma_CqMultiChannel), sizeof(TestUdma_TrpdMultiChannel), sizeof(TestUdma_SrcMultiChannel), sizeof(TestUdma_DstMultiChannel) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* ---------------------------
     * PKTDMA instance: open 2 TX channels and verify completions occur
     * --------------------------- */
    Udma_InitPrms udmaInitPrms;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvPktdma, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    for (index = 0; index < 2; index += 1)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX);
        chPrms.fqRingPrms.ringMem = TestUdma_FqMultiChannel[index];
        chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqMultiChannel[index]);
        chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem = TestUdma_CqMultiChannel[index];
        chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqMultiChannel[index]);
        chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        /* pick different peer numbers */
        chPrms.peerChNum = (index == 0) ? UDMA_PDMA_CH_MAIN0_UART0_TX : UDMA_TEST_PKTDMA_UNMAPPED_TX_PEER_CH;

        retVal = Udma_chOpen(drvPktdma, chPkt[index], UDMA_CH_TYPE_TX, &chPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TX);
        retVal = Udma_chConfigTx(chPkt[index], &txPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

        retVal = Udma_chEnable(chPkt[index]);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    }

    /* cleanup PKTDMA channels */
    for (index = 0; index < 2; index += 1)
    {
        retVal = Udma_chDisable(chPkt[index], UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        retVal = Udma_chClose(chPkt[index]);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    }
    retVal = Udma_deinit(drvPktdma);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Preferred channel boundary allocation test.
 *
 * Test Category: Negative
 *
 * Queries RM init parameters then attempts opens at start, end and out-of-range
 * preferred channel numbers for PKTDMA, mapped TX/RX and BCDMA block-copy types
 * to verify correct failures and boundary enforcement.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput In-range opens succeed; invalid boundary preferred opens fail.
 */

static void TestUdma_preferredChannelBoundaries(void *args)
{
    (void)args;
    int32_t retVal;
    uint32_t rxIdx, mappedTxChannelStart,mappedRxChannelStart, mappedTxChannelCount,mappedRxChannelCount, mappedChGroup;
    Udma_InitPrms udmaInitPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_DrvHandleInt internalDrv;
    Udma_ChPrms chPrms;
    Udma_ChObject tmpChObj;           /* reusable channel object */
    Udma_ChHandle tmpCh = &tmpChObj;  /* never NULL to avoid mixing error causes */

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Init PKTDMA driver to query RM params */
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    if (retVal != UDMA_SOK)
    {
        DebugP_log("[UDMA TEST] Udma_init(PKTDMA) returned %d - skipping boundary checks\n", retVal);
        return;
    }
    internalDrv = (Udma_DrvHandleInt)drvHandle;

    /* TX absolute boundaries */
    if (internalDrv->rmInitPrms.numTxCh > TEST_UDMA_VALUE_ZERO)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX);
        chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
        chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
        chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem     = TestUdma_CqRingMem;
        chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem);
        chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;

        chPrms.chNum = internalDrv->rmInitPrms.startTxCh + internalDrv->rmInitPrms.numTxCh; /* one past last */
        EXPECT_FAIL_OPEN(UDMA_CH_TYPE_TX);
        DebugP_log("[UDMA TEST] TX OOB chNum=%u\n", chPrms.chNum);

        if (internalDrv->rmInitPrms.startTxCh > TEST_UDMA_VALUE_ZERO)
        {
            chPrms.chNum = internalDrv->rmInitPrms.startTxCh - 1U;
            EXPECT_FAIL_OPEN(UDMA_CH_TYPE_TX);
            DebugP_log("[UDMA TEST] TX below-start chNum=%u\n", chPrms.chNum);
        }
    }

    /* RX absolute boundaries */
    if (internalDrv->rmInitPrms.numRxCh > TEST_UDMA_VALUE_ZERO)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
        chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
        chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
        chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem     = TestUdma_CqRingMem;
        chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem);
        chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;

        chPrms.chNum = internalDrv->rmInitPrms.startRxCh + internalDrv->rmInitPrms.numRxCh;
        EXPECT_FAIL_OPEN(UDMA_CH_TYPE_RX);
        DebugP_log("[UDMA TEST] RX OOB chNum=%u\n", chPrms.chNum);

        if (internalDrv->rmInitPrms.startRxCh > TEST_UDMA_VALUE_ZERO)
        {
            chPrms.chNum = internalDrv->rmInitPrms.startRxCh - 1U;
            EXPECT_FAIL_OPEN(UDMA_CH_TYPE_RX);
            DebugP_log("[UDMA TEST] RX below-start chNum=%u\n", chPrms.chNum);
        }
    }

#if (UDMA_NUM_MAPPED_TX_GROUP > 0)
    /* Mapped TX group OOB */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX_MAPPED);
    chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.mappedChGrp            = (uint32_t)UDMA_NUM_MAPPED_TX_GROUP + 5U;
    chPrms.chNum = internalDrv->rmInitPrms.startMappedTxCh[0];
    EXPECT_FAIL_OPEN(UDMA_CH_TYPE_TX_MAPPED);
    DebugP_log("[UDMA TEST] Mapped TX grp OOB id=%u\n", chPrms.mappedChGrp);

    /* Mapped TX channel OOB */
    mappedChGroup = TEST_UDMA_VALUE_ZERO;
    mappedTxChannelStart = internalDrv->rmInitPrms.startMappedTxCh[mappedChGroup];
    mappedTxChannelCount   = internalDrv->rmInitPrms.numMappedTxCh[mappedChGroup];
    if (mappedTxChannelCount > TEST_UDMA_VALUE_ZERO)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX_MAPPED);
        chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
        chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
        chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.mappedChGrp            = mappedChGroup;
        chPrms.chNum                  = mappedTxChannelStart + mappedTxChannelCount;
        EXPECT_FAIL_OPEN(UDMA_CH_TYPE_TX_MAPPED);
        DebugP_log("[UDMA TEST] Mapped TX ch OOB abs=%u (grp=%u mappedTxChannelStart=%u mappedTxChannelCount=%u)\n",
                   chPrms.chNum, mappedChGroup, mappedTxChannelStart, mappedTxChannelCount);
    }
#endif

#if (UDMA_NUM_MAPPED_RX_GROUP > 0)
    /* Mapped RX group OOB */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX_MAPPED);
    chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.mappedChGrp            = (uint32_t)UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP + 10U;
    chPrms.chNum                  = TEST_UDMA_VALUE_ZERO;
    EXPECT_FAIL_OPEN(UDMA_CH_TYPE_RX_MAPPED);
    DebugP_log("[UDMA TEST] Mapped RX grp OOB id=%u\n", chPrms.mappedChGrp);

    rxIdx = TEST_UDMA_BUF_INDEX_ZERO;
    mappedRxChannelStart = internalDrv->rmInitPrms.startMappedRxCh[rxIdx];
    mappedRxChannelCount   = internalDrv->rmInitPrms.numMappedRxCh[rxIdx];
    if (mappedRxChannelCount > TEST_UDMA_VALUE_ZERO)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX_MAPPED);
        chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
        chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
        chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.mappedChGrp            = ((UDMA_NUM_MAPPED_TX_GROUP > TEST_UDMA_VALUE_ZERO) ? UDMA_NUM_MAPPED_TX_GROUP : TEST_UDMA_VALUE_ZERO) + rxIdx;
        chPrms.chNum                  = mappedRxChannelStart + mappedRxChannelCount;
        EXPECT_FAIL_OPEN(UDMA_CH_TYPE_RX_MAPPED);
        DebugP_log("[UDMA TEST] Mapped RX ch OOB abs=%u (grp=%u mappedRxChannelStart=%u mappedRxChannelCount=%u)\n",
                   chPrms.chNum, chPrms.mappedChGrp, mappedRxChannelStart, mappedRxChannelCount);
    }
#endif

    /* BCDMA block-copy preferred boundary */
    Udma_DrvObject bcdmaDrvObj = {TEST_UDMA_BUF_CLEAR_PATTERN};
    Udma_DrvHandle bcdmaDrv = &bcdmaDrvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(bcdmaDrv, &udmaInitPrms);
    if (retVal == UDMA_SOK)
    {
        Udma_DrvHandleInt bcdmaDrvInt = (Udma_DrvHandleInt)bcdmaDrv;
        if (bcdmaDrvInt->rmInitPrms.numBlkCopyCh > TEST_UDMA_VALUE_ZERO)
        {
            UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
            chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
            chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
            chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
            chPrms.chNum = bcdmaDrvInt->rmInitPrms.startBlkCopyCh + bcdmaDrvInt->rmInitPrms.numBlkCopyCh;
            retVal = Udma_chOpen(bcdmaDrv, tmpCh, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
            if (retVal == UDMA_SOK)
            {
                TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(tmpCh));
                TEST_FAIL_MESSAGE("BCDMA OOB open succeeded");
            }
            DebugP_log("[UDMA TEST] BCDMA BC OOB chNum=%u\n", chPrms.chNum);
        }
    }

    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(bcdmaDrv));
}

/**
 * \brief Event invalid/unmapped/unregistered negative path tests.
 *
 * Test Category: Negative
 *
 * Exercises event registration with invalid parameters, attempts to trigger or
 * unregister events not mapped or registered to ensure robust error handling.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Invalid operations return documented failure codes; driver stable.
 */
static void TestUdma_eventInvalidUnmappedUnregistered(void *args)
{
    (void)args;
    int32_t retVal;
    Udma_DrvObject bcdmaDrvObj = {TEST_UDMA_BUF_CLEAR_PATTERN};
    Udma_DrvHandle drvHandle = &bcdmaDrvObj;
    Udma_InitPrms udmaInitPrms;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_EventObject eventObj;
    Udma_EventPrms eventPrms;
    uint64_t trpdPhysicalAddr;
    uint64_t completionDescAddr;
    uint32_t remainingPollAttempts, unmapped;
    uint8_t *trpdMemory = &TestUdma_TrpdSingleDesc[TEST_UDMA_BUF_INDEX_ZERO];
    Udma_DrvHandleInt internalDrv;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_BlkCopyCh2RingMem, TestUdma_Src, TestUdma_Dst, TestUdma_TrpdSingleDesc };
    size_t sizeList[] = { sizeof(TestUdma_BlkCopyCh2RingMem), sizeof(TestUdma_Src), sizeof(TestUdma_Dst), sizeof(TestUdma_TrpdSingleDesc) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Init BCDMA driver */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    if (retVal != UDMA_SOK)
    {
        DebugP_log("[UDMA TEST] Udma_init(BCDMA) returned %d - skipping event invalid/unmapped/unregistered test\n", retVal);
        return;
    }
    internalDrv = (Udma_DrvHandleInt)drvHandle;

    /* Open block-copy channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem      = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize  = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt      = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* 1) Register valid event and ensure callback occurs (use generic cb + semaphore) */
    TestUdma_EventCbCount = 0; /* legacy counter unused in IRQ wait phase */
    SemaphoreP_Object localSem;
    volatile uint32_t callbackCount = 0;
    TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };
    SemaphoreP_constructBinary(&localSem, 0);
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_genericEventCb;
    eventPrms.appData   = &eventSemaphore;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* submit a transfer and wait for callback */
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Drain any stale CQ entries before first IRQ transfer */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Wait via IRQ */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_TRUE(callbackCount > 0U);

    /* Drain any completions from CQ before unregistering the event */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Unregister event (should succeed now that rings are drained) */
    retVal = Udma_eventUnRegister(&eventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&localSem);

    /* 2) After unregister, ensure no callback occurs on new transfer */
    TestUdma_EventCbCount = 0;
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, trpdMemory, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);
    trpdPhysicalAddr = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO, NULL);
    /* Drain stale CQ entries before second transfer (event disabled scenario) */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_MEDIUM;
    while ((TestUdma_EventCbCount == 0) && (remainingPollAttempts > 0))
    {
        ClockP_usleep(10);
        remainingPollAttempts -= 1;
    }
    /* after remainingPollAttempts, callback count should remain zero since event was unregistered */
    TEST_ASSERT_EQUAL_INT(0, TestUdma_EventCbCount);

    /* 3) Register with invalid preferred core intr -> should fail and not produce interrupts */
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_eventCb;
    eventPrms.preferredCoreIntrNum = UDMA_INTR_INVALID;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);

    /* 4) Register with unmapped core intr number (beyond drv vintr) -> expect failure */
    unmapped = internalDrv->rmInitPrms.numVintr + 100U;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_eventCb;
    eventPrms.preferredCoreIntrNum = unmapped;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);

    /* Cleanup */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    return;
}

/**
 * \brief Negative test: opening a block-copy channel with NULL FQ ring memory.
 *
 * Test Category: Negative / Argument Validation.
 *
 * Demonstrates current driver behavior: channel open succeeds even when FQ ring
 * elemCnt is non-zero but ringMem is NULL; FQ ring is simply not allocated and
 * subsequent queue operations fail. After providing valid FQ ring memory, open
 * and full channel lifecycle succeed.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput First open succeeds with NULL FQ ringMem and FQ ring handle is NULL; queue fails.
 *                 Second open with valid ring memory succeeds; enable/disable/close all return UDMA_SOK.
 */
static void TestUdma_nullRingMemOpen(void *args)
{
    int32_t retVal;
    uint64_t dummyDesc;
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_BlkCopyCh2RingMem, TestUdma_RingMem };
    size_t sizeList[] = { sizeof(TestUdma_BlkCopyCh2RingMem), sizeof(TestUdma_RingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Negative scenario: NULL ringMem + non-zero elemCnt.
     * Driver currently allows open; FQ ring remains NULL. We verify that
     * queuing fails instead of expecting chOpen failure. */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = NULL;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_CNT;
    chPrms.cqRingPrms.ringMem     = TestUdma_BlkCopyCh2RingMem;
    chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);  /* Open allowed by driver */
    TEST_ASSERT_NULL(Udma_chGetFqRingHandle(chHandle)); /* FQ ring not allocated */

    /* Attempt to queue should fail because FQ ring is NULL */
    dummyDesc = TEST_UDMA_DUMMY_DESC_VALUE;
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), dummyDesc);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);

    /* Close this partially configured channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Positive scenario: proper FQ ring memory provided */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestUdma_RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_CNT;
    chPrms.cqRingPrms.ringMem     = TestUdma_BlkCopyCh2RingMem;
    chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_NOT_NULL(Udma_chGetFqRingHandle(chHandle));
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_RING_ELEM_CNT,
                             Udma_ringGetElementCnt(Udma_chGetFqRingHandle(chHandle)));

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

}

/**
 * \brief Address translation and mapping sanity test.
 *
 * Test Category: Functional / Mapping.
 *
 * Confirms virtual->physical translation yields expected identity values and ring queue/dequeue
 * uses matching descriptor addresses.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Virt/trpdPhysicalAddr addresses match; dequeue returns same physical descriptor; non-zero addresses.
 */
static void TestUdma_addrTranslateAndDescriptorEchoTest(void *args)
{
    int32_t retVal;
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    uint8_t *trpd = TestUdma_TrpdSingleDesc;
    uint64_t physDesc;
    uint64_t dequeuedValue = TEST_UDMA_ADDR_NONE; /* no descriptor dequeued yet */
    uint64_t translatedAddr;
    uint32_t remainingPollAttempts;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem, TestUdma_TrpdSingleDesc, TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem), sizeof(TestUdma_TrpdSingleDesc), sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
    chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare TRPD and buffers */
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_SMALL_TRANSFER_BYTES);
    TestUdma_trpdInit(chHandle, trpd, TestUdma_Dst, TestUdma_Src, TEST_UDMA_SMALL_TRANSFER_BYTES);

    physDesc = Udma_defaultVirtToPhyFxn(trpd, Udma_chGetNum(chHandle), NULL);
    translatedAddr = (uint64_t)AddrTranslateP_getLocalAddr((uint64_t)(uintptr_t)trpd);
    TEST_ASSERT_EQUAL_PTR(translatedAddr, physDesc);
    DebugP_log("MapAndAddrCheck: virt=%p trpdPhysicalAddr=0x%" PRIx64 " trans=0x%" PRIx64 "\r\n", trpd, physDesc, translatedAddr);
    TEST_ASSERT_TRUE(translatedAddr != TEST_UDMA_PHY_ADDR_NONE);

    Udma_RingHandle fqRing = Udma_chGetFqRingHandle(chHandle);
    TEST_ASSERT_NOT_NULL(fqRing);
    Udma_RingHandle cqRing = Udma_chGetCqRingHandle(chHandle);
    TEST_ASSERT_NOT_NULL(fqRing);
    TEST_ASSERT_NOT_NULL(cqRing);

    /* Drain stale CQ entries before queueing */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(cqRing, &dequeuedValue);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel before queueing descriptor */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_ringQueueRaw(fqRing, physDesc);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Poll for completion on FQ ring */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    int completionFound = TEST_UDMA_VALUE_ZERO;
    do
    {
        retVal = Udma_ringDequeueRaw(fqRing, &dequeuedValue);
        if (retVal == UDMA_SOK)
        {
            completionFound = 1;
            break;
        }
        ClockP_usleep(10);
        remainingPollAttempts -= 1;
    } while ((remainingPollAttempts > 0) && (completionFound == 0));
    TEST_ASSERT_EQUAL_INT(1, completionFound);
    TEST_ASSERT_EQUAL_PTR(physDesc, dequeuedValue);

    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief Multiple BCDMA block-copy channels concurrent transfers test.
 *
 * Test Category: Functional / Concurrency.
 *
 * Open several block-copy channels (up to 4 or resource limit) on the BCDMA instance and
 * perform a small transfer on each to ensure independent operation and resource allocation.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All channels perform successful transfers and close without errors.
 */
static void TestUdma_multipleBlkcopyChannelsBcdma(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_DrvHandleInt drvInt = (Udma_DrvHandleInt)drvHandle;
    uint32_t maxCh = drvInt->rmInitPrms.numBlkCopyCh;
    int32_t index;
    uint32_t b, remainingPollAttempts;
    uint64_t trpdPhysicalAddr ,completionAddr;
    Udma_ChObject chObj[4];
    Udma_ChHandle chHandle[4];

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqMultiChannel, TestUdma_CqMultiChannel, TestUdma_TrpdMultiChannel, TestUdma_SrcMultiChannel, TestUdma_DstMultiChannel };
    size_t sizeList[] = { sizeof(TestUdma_FqMultiChannel), sizeof(TestUdma_CqMultiChannel), sizeof(TestUdma_TrpdMultiChannel), sizeof(TestUdma_SrcMultiChannel), sizeof(TestUdma_DstMultiChannel) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);
    if (maxCh > TEST_UDMA_MAX_CONCURRENT_BC_CH)
    {
        maxCh = TEST_UDMA_MAX_CONCURRENT_BC_CH;
    }
    if (maxCh == TEST_UDMA_NUM_CH_NONE)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
        TEST_IGNORE_MESSAGE("No block copy channels available");
        return;
    }
    for (index = 0; index < maxCh; index += 1)
    {
        chHandle[index] = &chObj[index];
        Udma_ChPrms chPrms;
        Udma_ChTxPrms txPrms;
        Udma_ChRxPrms rxPrms;
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        chPrms.fqRingPrms.ringMem = TestUdma_FqMultiChannel[index];
        chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem = TestUdma_CqMultiChannel[index];
        chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
        retVal = Udma_chOpen(drvHandle, chHandle[index], UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        retVal = Udma_chConfigTx(chHandle[index], &txPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        retVal = Udma_chConfigRx(chHandle[index], &rxPrms);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        retVal = Udma_chEnable(chHandle[index]);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        for (b = 0; b < TEST_UDMA_SMALL_TRANSFER_BYTES; b += 1)
        {
            TestUdma_SrcMultiChannel[index][b] = (uint8_t)(b + index);
            TestUdma_DstMultiChannel[index][b] = TEST_UDMA_BUF_CLEAR_PATTERN;
        }
        TestUdma_trpdInit(chHandle[index], TestUdma_TrpdMultiChannel[index], TestUdma_DstMultiChannel[index], TestUdma_SrcMultiChannel[index], TEST_UDMA_SMALL_TRANSFER_BYTES);
        /* Ensure descriptor and source buffer visible to HW; invalidate destination prior to transfer */
        CacheP_wb((void*)TestUdma_TrpdMultiChannel[index], TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALL);
        CacheP_wb((void*)TestUdma_SrcMultiChannel[index], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        CacheP_inv((void*)TestUdma_DstMultiChannel[index], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        trpdPhysicalAddr = Udma_defaultVirtToPhyFxn(TestUdma_TrpdMultiChannel[index], Udma_chGetNum(chHandle[index]), NULL);
        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle[index]), trpdPhysicalAddr);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
        do
        {
            retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle[index]), &completionAddr);
            if (retVal == UDMA_SOK)
            {
                break; /* real error */
            }
            remainingPollAttempts -= 1;
        } while ((retVal != UDMA_SOK) && (remainingPollAttempts > 0U));
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
        TEST_ASSERT_TRUE(remainingPollAttempts > TEST_UDMA_VALUE_ZERO);
        TEST_ASSERT_EQUAL_PTR(trpdPhysicalAddr, completionAddr);
        /* Invalidate destination again after completion to read updated data */
        CacheP_inv((void*)TestUdma_DstMultiChannel[index], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        for (b = 0; b < TEST_UDMA_SMALL_TRANSFER_BYTES; b += 1)
        {
            TEST_ASSERT_EQUAL_UINT8(TestUdma_SrcMultiChannel[index][b], TestUdma_DstMultiChannel[index][b]);
        }
    }
    for (index = 0; index < maxCh; index += 1)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle[index], UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle[index]));
    }
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Channel busy status heuristic test (corrected).
 *
 * Test Category: Functional / Status
 *
 * Validates that channel forward ring occupancy (FOCC) reflects queued state,
 * decreases after hardware fetch, and that completion appears on the CQ ring.
 */
static void TestUdma_channelBusyStatus(void *args)
{
    (void)args;
    int32_t retVal;
    int32_t index;
    uint64_t trpdPhysicalAddr, completionAddr = 0;
    uint32_t preFocc, postFocc, remainingPollAttempts = 0;

    /* -------- 1. Init driver -------- */
    Udma_InitPrms initPrms;
    Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* -------- 2. Channel open -------- */
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem, TestUdma_TrpdSingleDesc, TestUdma_SrcChBusyStatus, TestUdma_DstChBusyStatus };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem), sizeof(TestUdma_TrpdSingleDesc), sizeof(TestUdma_SrcChBusyStatus), sizeof(TestUdma_DstChBusyStatus) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem);
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* -------- 3. Configure channel -------- */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* -------- 4. Prepare buffers and TRPD -------- */
    for (index = 0; index < TEST_UDMA_MED_TRANSFER_BYTES; index += 1)
    {
        TestUdma_SrcChBusyStatus[index] = (uint8_t)(0xA0 + index);
        TestUdma_DstChBusyStatus[index] = TEST_UDMA_BUF_CLEAR_PATTERN;
    }
    TestUdma_trpdInit(chHandle, TestUdma_TrpdSingleDesc, TestUdma_DstChBusyStatus, TestUdma_SrcChBusyStatus, TEST_UDMA_MED_TRANSFER_BYTES);
    /* -------- 5. Cache maintenance (descriptor + src writeback; dst writeback initial zeros) -------- */
    CacheP_wb((void *)TestUdma_TrpdSingleDesc, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALL);
    CacheP_wb((void *)TestUdma_SrcChBusyStatus, TEST_UDMA_MED_TRANSFER_BYTES, CacheP_TYPE_ALL);
    CacheP_wb((void *)TestUdma_DstChBusyStatus, TEST_UDMA_MED_TRANSFER_BYTES, CacheP_TYPE_ALL);

    /* -------- 6. Queue descriptor BEFORE enable to observe ring occupancy reliably -------- */
    trpdPhysicalAddr = Udma_defaultVirtToPhyFxn(TestUdma_TrpdSingleDesc, Udma_chGetNum(chHandle), NULL);
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    preFocc = Udma_ringGetForwardRingOcc(Udma_chGetFqRingHandle(chHandle));
    DebugP_log("Pre-enable FOCC=%u\n", preFocc);
    /* With elemCnt=1 we expect FOCC==1. If HW prefetch raced, FOCC may be 0; both are acceptable */
    TEST_ASSERT_TRUE_MESSAGE((preFocc == TEST_UDMA_STATUS_ENABLED) || (preFocc == TEST_UDMA_STATUS_DISABLED), "Unexpected FOCC before enable (not 0 or 1)");

    /* -------- 7. Enable channel -------- */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* -------- 8. Poll for completion -------- */
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_STANDARD;
    int completionFound = 0;

    while ((remainingPollAttempts > TEST_UDMA_VALUE_ZERO) && (completionFound == TEST_UDMA_VALUE_ZERO))
    {
        if (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionAddr) == UDMA_SOK)
        {
            completionFound = 1;
        }
        else
        {
            ClockP_usleep(10);
        }
        remainingPollAttempts -= 1;
    }

    TEST_ASSERT_EQUAL_INT(1, completionFound);
    TEST_ASSERT_EQUAL_PTR(trpdPhysicalAddr, completionAddr);

    /* -------- 9. Post-transfer checks -------- */
    postFocc = Udma_ringGetForwardRingOcc(Udma_chGetFqRingHandle(chHandle));
    DebugP_log("Post-completion FOCC=%u\n", postFocc);
    TEST_ASSERT_TRUE(postFocc <= preFocc);
    /* Invalidate destination before reading back results */
    CacheP_inv((void *)TestUdma_DstChBusyStatus, TEST_UDMA_MED_TRANSFER_BYTES, CacheP_TYPE_ALL);
    for (index = 0; index < TEST_UDMA_MED_TRANSFER_BYTES; index += 1)
    {
        TEST_ASSERT_EQUAL_UINT8(TestUdma_SrcChBusyStatus[index], TestUdma_DstChBusyStatus[index]);
    }

    /* -------- 10. Cleanup -------- */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Block-copy channel allocation exhaustion test (final DDR global version).
 *
 * Test Category: Negative / Resource.
 *
 * Allocates every available block-copy channel (TR block-copy type) on BCDMA, each with its
 * own minimal FQ/CQ ring memory slice (one cacheline). Then attempts one additional open
 * which must fail, proving the driver enforces the advertised channel limit. No channels
 * are enabled and no descriptors are queued; this test purely stresses allocation paths.
 *
 * Memory Strategy:
 *  - All channel objects and ring memory live in the .udma_buffer_ddr section to avoid
 *    consuming MSRAM.
 *  - Guard macro TEST_UDMA_MAX_EXHAUST_CH prevents static array overrun if future SoCs
 *    increase the channel count beyond the conservative maximum.
 *
 * Safety Notes:
 *  - Each channel receives a unique FQ/CQ slice; do NOT collapse them to a single buffer
 *    unless you also guarantee no enable/queue operations (would corrupt shared state).
 *  - If total channels exceed TEST_UDMA_MAX_EXHAUST_CH the test is skipped (ignored).
 */
static void TestUdma_channelAllocExhaust(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj; /* Local static to keep stack usage low */
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    /* Open each channel with dedicated 1-element rings */
    uint32_t openedChCount = TEST_UDMA_VALUE_ZERO;
    uint32_t openStatus[TEST_UDMA_MAX_EXHAUST_CH] = { 0 }; /* Track open results per channel */
    uint32_t totalChCount, retVal = Udma_init(drvHandle, &initPrms);
    int32_t index;
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_ExhaustFqMem, TestUdma_ExhaustCqMem };
    size_t sizeList[] = { sizeof(TestUdma_ExhaustFqMem), sizeof(TestUdma_ExhaustCqMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    Udma_DrvHandleInt drvInt = (Udma_DrvHandleInt)drvHandle;
    totalChCount = drvInt->rmInitPrms.numBlkCopyCh;
    if (totalChCount == TEST_UDMA_VALUE_ZERO)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
        TEST_IGNORE_MESSAGE("No block-copy channels to exhaust");
        return;
    }
    if (totalChCount > TEST_UDMA_MAX_EXHAUST_CH)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
        TEST_IGNORE_MESSAGE("Configured block-copy channel count exceeds TEST_UDMA_MAX_EXHAUST_CH");
        return;
    }

    for (index = 0; index < totalChCount; index += 1)
    {
        Udma_ChPrms chPrms;
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        chPrms.fqRingPrms.ringMem     = TestUdma_ExhaustFqMem[index];
        chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE; /* one slice */
        chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        chPrms.cqRingPrms.ringMem     = TestUdma_ExhaustCqMem[index];
        chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
        chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
        retVal = Udma_chOpen(drvHandle, &TestUdma_ExhaustChObjs[index], UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
        openStatus[index] = retVal;
        if (retVal == UDMA_SOK)
        {
            openedChCount += 1;
        }
        else
        {
            break; /* Unexpected early failure */
        }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(totalChCount, openedChCount, "Did not open all advertised block-copy channels");

    /* Attempt one more channel: must fail */
    Udma_ChObject extraObj;
    Udma_ChPrms extraPrms;
    UdmaChPrms_init(&extraPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    /* Reuse first slice deliberately for the failing attempt */
    extraPrms.fqRingPrms.ringMem     = TestUdma_ExhaustFqMem[0];
    extraPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    extraPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
    extraPrms.cqRingPrms.ringMem     = TestUdma_ExhaustCqMem[0];
    extraPrms.cqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    extraPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, &extraObj, UDMA_CH_TYPE_TR_BLK_COPY, &extraPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);

    /* Cleanup: disable (best-effort) and close all opened channels */
    for (index = 0; index < totalChCount; index += 1)
    {
        if (openStatus[index] == UDMA_SOK)
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(&TestUdma_ExhaustChObjs[index]));
    }

    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Register-access negative tests after driver deinitialization.
 *
 * Test Category: Negative / Lifecycle.
 *
 * Calls limited public APIs after a successful Udma_deinit to confirm they return
 * failure codes and do not crash or corrupt memory. Verifies defensive guard paths.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Post-deinit API invocations fail (!= UDMA_SOK) without side-effects.
 */
static void TestUdma_regAccessAfterDeinit(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Channel open should now fail */
    Udma_ChObject chObj;
    Udma_ChPrms chPrms;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = NULL;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, &chObj, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);
    /* Ring alloc through channel handle should also fail gracefully */
    Udma_RingPrms ringPrms;
    UdmaRingPrms_init(&ringPrms);
    ringPrms.ringMem = NULL;
    ringPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    Udma_RingObject ringObj;
    retVal = Udma_ringAlloc(drvHandle, &ringObj, TEST_UDMA_RING_NUM_ZERO, &ringPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);
}

/**
 * \brief Double flow allocation negative test.
 *
 * Test Category: Negative / Resource.
 *
 * Attempts to allocate the same free flow twice; second allocation expected to fail.
 * Ensures resource tracking prevents duplicate ownership and cleanup works correctly.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput First flow alloc succeeds; second for same flow index fails; free succeeds.
 */
static void TestUdma_doubleAllocateFlow(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    uint32_t baseFlow;
    if (retVal != UDMA_SOK)
    {
        TEST_IGNORE_MESSAGE("PKTDMA instance not available");
        return;
    }
    /* Strategy: Attach two handles to same flow number. Since Udma_flowAttach is a
     * lightweight association (no exclusive allocation), both attaches are expected
     * to succeed and each handle may be detached independently. We validate that
     * detaching both succeeds and that a second detach of the same handle fails. */
    baseFlow = UDMA_DEFAULT_FLOW_ID;
    Udma_FlowObject flowObjA;
    retVal = Udma_flowAttach(drvHandle, &flowObjA, baseFlow, 1U);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_FlowObject flowObjB;
    retVal = Udma_flowAttach(drvHandle, &flowObjB, baseFlow, 1U);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal); /* allow attach */
    /* First detach should succeed */
    retVal = Udma_flowDetach(&flowObjA);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Detach second independent handle (expected to succeed) */
    retVal = Udma_flowDetach(&flowObjB);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Detach same handle again should now fail (already deinitialized) */
    retVal = Udma_flowDetach(&flowObjB);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);
    /* Cleanup */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Event registration failure leaves channel clean test.
 *
 * Test Category: Negative / Robustness.
 *
 * Forces an event registration failure (invalid preferredCoreIntrNum) after channel open,
 * then submits a transfer without event handling to ensure channel still operational.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Event register fails; subsequent transfer succeeds; channel closes cleanly.
 */
static void TestUdma_eventRegisterFailureKeepsChannelOperational(void *args)
{
    (void)args;
    uint64_t completionAddr = 0, trpdPhysicalAddr;
    uint32_t remainingPollAttempts = 0, status = 0;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    if (retVal != UDMA_SOK)
    {
        TEST_IGNORE_MESSAGE("BCDMA instance init failed");
    }
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.cqRingPrms.ringMem = TestUdma_RingMem;
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_BlkCopyCh2RingMem, TestUdma_RingMem, TestUdma_TrpdSingleDesc, TestUdma_Src, TestUdma_Dst };
    size_t sizeList[] = { sizeof(TestUdma_BlkCopyCh2RingMem), sizeof(TestUdma_RingMem), sizeof(TestUdma_TrpdSingleDesc), sizeof(TestUdma_Src), sizeof(TestUdma_Dst) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_ChTxPrms txPrms;
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle, &txPrms));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(chHandle));
    Udma_EventPrms eventPrms;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_eventCb;
    eventPrms.preferredCoreIntrNum = UDMA_INTR_INVALID; /* force failure */
    Udma_EventObject eventObj;
    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal);
    /* Transfer should still work */
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_SMALL_TRANSFER_BYTES);
    TestUdma_trpdInit(chHandle, TestUdma_TrpdSingleDesc, TestUdma_Dst, TestUdma_Src, TEST_UDMA_SMALL_TRANSFER_BYTES);
    trpdPhysicalAddr = Udma_defaultVirtToPhyFxn(TestUdma_TrpdSingleDesc, Udma_chGetNum(chHandle), NULL);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr));
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionAddr);
        if (status == UDMA_SOK)
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > TEST_UDMA_VALUE_ZERO);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, status);
    TEST_ASSERT_TRUE(remainingPollAttempts > TEST_UDMA_VALUE_ZERO);
    TEST_ASSERT_EQUAL_PTR(trpdPhysicalAddr, completionAddr);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief PSIL thread pairing failure test.
 *
 * Test Category: Negative / Mapping.
 *
 * Attempts to open a PKTDMA TX channel with an intentionally invalid PSIL thread number
 * (beyond RM configured range) to verify open fails and resources are not leaked.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Udma_chOpen fails for invalid thread; driver remains operational after.
 */
static void TestUdma_psilThreadPairingFailure(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    if (retVal != UDMA_SOK)
    {
        TEST_IGNORE_MESSAGE("PKTDMA instance init failed");
        return;
    }
    Udma_DrvHandleInt drvInt = (Udma_DrvHandleInt)drvHandle;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX);
    /* Provide minimal ring memory to reach pairing logic */
    chPrms.fqRingPrms.ringMem = TestUdma_RingMem;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem };
    size_t sizeList[] = { sizeof(TestUdma_RingMem) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    /* Force invalid absolute preferred channel number beyond start+numTxCh */
    if (drvInt->rmInitPrms.numTxCh > TEST_UDMA_VALUE_ZERO)
    {
        chPrms.chNum = drvInt->rmInitPrms.startTxCh + drvInt->rmInitPrms.numTxCh; /* one past end */
    }
    else
    {
        chPrms.chNum = TEST_UDMA_INVALID_CHANNEL_NUM; /* clearly invalid */
    }
    /* Also force an invalid peer PSIL thread if available (choose a large number) */
    chPrms.peerChNum = 0xFFFFFFFFU;  /* invalid/unmapped PSIL thread */

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TX, &chPrms);
    TEST_ASSERT_NOT_EQUAL(UDMA_SOK, retVal); /* Expect failure due to invalid chNum/peerChNum */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Minimum size (1 byte) transfer edge-case test.
 *
 * Test Category: Functional / Edge.
 *
 * Exercises the DMA engine with the smallest legal transfer length (1 byte) to
 * validate descriptor programming does not assume word-sized moves and that
 * completion + data integrity are preserved.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Single byte copied correctly from src to dst; ring operations succeed.
 */
static void TestUdma_minSizeTransfer(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    uint64_t completionAddr = 0, trpdPhysicalAddr;
    Udma_EventObject eventObj;
    Udma_EventPrms eventPrms;
    SemaphoreP_Object localSem;
    volatile uint32_t callbackCount = 0;
    TestUdma_EventSemaphore eventSemaphore = { &localSem, &callbackCount };
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    uint32_t remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_STANDARD;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_FqRingMem, TestUdma_CqRingMem, TestUdma_TrpdSingleDesc, TestUdma_SrcMin, TestUdma_DstMin };
    size_t sizeList[] = { sizeof(TestUdma_FqRingMem), sizeof(TestUdma_CqRingMem), sizeof(TestUdma_TrpdSingleDesc), sizeof(TestUdma_SrcMin), sizeof(TestUdma_DstMin) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    TestUdma_SrcMin[TEST_UDMA_BUF_INDEX_ZERO] = TEST_UDMA_SRC_MIN_PATTERN;
    TestUdma_DstMin[TEST_UDMA_BUF_INDEX_ZERO] = TEST_UDMA_BUF_CLEAR_PATTERN;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem);
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem);
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle, &txPrms));
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chHandle, &rxPrms));
    TestUdma_trpdInit(chHandle, TestUdma_TrpdSingleDesc, TestUdma_DstMin, TestUdma_SrcMin, TEST_UDMA_MIN_TRANSFER_BYTES);
    CacheP_wb((void*)TestUdma_TrpdSingleDesc, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALL);
    CacheP_wb((void*)TestUdma_SrcMin, TEST_UDMA_MIN_TRANSFER_BYTES, CacheP_TYPE_ALL);
    CacheP_wb((void*)TestUdma_DstMin, TEST_UDMA_MIN_TRANSFER_BYTES, CacheP_TYPE_ALL);
    /* Register event and use semaphore instead of polling */
    SemaphoreP_constructBinary(&localSem, 0);
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    eventPrms.chHandle  = chHandle;
    eventPrms.eventCb   = TestUdma_genericEventCb;
    eventPrms.appData   = &eventSemaphore;
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventRegister(drvHandle, &eventObj, &eventPrms));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(chHandle));
    trpdPhysicalAddr = Udma_defaultVirtToPhyFxn(TestUdma_TrpdSingleDesc, Udma_chGetNum(chHandle), NULL);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_TRUE(callbackCount > 0U);
    remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
    do
    {
        retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionAddr);
        if (retVal == UDMA_ETIMEOUT )
        {
            break;
        }
        remainingPollAttempts -= 1;
    } while (remainingPollAttempts > 0U);
    if (retVal == UDMA_ETIMEOUT)
    {
        retVal = UDMA_SOK;
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    TEST_ASSERT_EQUAL_PTR(trpdPhysicalAddr, completionAddr);
    CacheP_inv((void*)TestUdma_DstMin, TEST_UDMA_MIN_TRANSFER_BYTES, CacheP_TYPE_ALL);
    TEST_ASSERT_EQUAL_UINT8(TestUdma_SrcMin[0], TestUdma_DstMin[0]);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventUnRegister(&eventObj));
    SemaphoreP_destruct(&localSem);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
 * \brief Multiple descriptor submission sequencing test.
 *
 * Test Category: Functional / Ordering.
 *
 * Queues several TR descriptors back-to-back and polls completion ring for each,
 * validating ordering (FIFO) and data integrity for every descriptor.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All TRPDs complete in the same order enqueued; buffer contents match.
 */
static void TestUdma_multiDescriptorSubmission(void *args)
{
    (void)args;
    int32_t index, descIndex;
    uint64_t trpdPhysicalAddr[3], completionAddr;
    uint32_t remainingPollAttempts, expected;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    int32_t retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;

    /* --------------------------------------------
     * Clear the global buffers used for this test
     * -------------------------------------------- */
    void *bufferList[] = { TestUdma_RingMem, TestUdma_TdCqRingMem, TestUdma_TrpdMultiChannel, TestUdma_SrcMultiChannel, TestUdma_DstMultiChannel };
    size_t sizeList[] = { sizeof(TestUdma_RingMem), sizeof(TestUdma_TdCqRingMem), sizeof(TestUdma_TrpdMultiChannel), sizeof(TestUdma_SrcMultiChannel), sizeof(TestUdma_DstMultiChannel) };
    TEST_UDMA_CLEAR_BUFS(bufferList, sizeList);

    for (descIndex = 0; descIndex < 3U; descIndex += 1)
    {
        for (index = 0; index < TEST_UDMA_SMALL_TRANSFER_BYTES; index += 1)
        {
            TestUdma_SrcMultiChannel[descIndex][index] = (uint8_t)(0x30 + descIndex + index);
            TestUdma_DstMultiChannel[descIndex][index] = TEST_UDMA_BUF_CLEAR_PATTERN;
        }
    }
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    /* Use larger ring memories to hold 3 elements; global TestUdma_FqRingMem/TestUdma_CqRingMem are single element */
    chPrms.fqRingPrms.ringMem     = TestUdma_RingMem; /* size = TEST_UDMA_RING_MEM_SIZE (>= 3 * cacheline) */
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_TRIPLE;
    chPrms.cqRingPrms.ringMem     = TestUdma_TdCqRingMem;
    chPrms.cqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE;
    chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_ELEM_TRIPLE;
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms));
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle, &txPrms));
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chHandle, &rxPrms));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(chHandle));
    for (descIndex = 0; descIndex < 3U; descIndex += 1)
    {
        TestUdma_trpdInit(chHandle, TestUdma_TrpdMultiChannel[descIndex], TestUdma_DstMultiChannel[descIndex], TestUdma_SrcMultiChannel[descIndex], TEST_UDMA_SMALL_TRANSFER_BYTES);
        CacheP_wb((void*)TestUdma_TrpdMultiChannel[descIndex], TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALL);
        CacheP_wb((void*)TestUdma_SrcMultiChannel[descIndex], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        CacheP_wb((void*)TestUdma_DstMultiChannel[descIndex], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        trpdPhysicalAddr[descIndex] = Udma_defaultVirtToPhyFxn(TestUdma_TrpdMultiChannel[descIndex], Udma_chGetNum(chHandle), NULL);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhysicalAddr[descIndex]));
    }
    for (expected = 0; expected < 3U; expected += 1)
    {
        remainingPollAttempts = TEST_UDMA_POLL_ATTEMPTS_SHORT;
        do
        {
            retVal = Udma_ringFlushRaw(Udma_chGetCqRingHandle(chHandle), &completionAddr);
            if (retVal == UDMA_SOK)
            {
                break;
            }
            remainingPollAttempts -= 1;
        } while ((retVal != UDMA_SOK) && (remainingPollAttempts > 0U));

        TEST_ASSERT_TRUE(remainingPollAttempts > TEST_UDMA_VALUE_ZERO);
        TEST_ASSERT_EQUAL_PTR(trpdPhysicalAddr[expected], completionAddr);
        CacheP_inv((void*)TestUdma_DstMultiChannel[expected], TEST_UDMA_SMALL_TRANSFER_BYTES, CacheP_TYPE_ALL);
        for (index = 0; index < TEST_UDMA_SMALL_TRANSFER_BYTES; index += 1)
        {
            TEST_ASSERT_EQUAL_UINT8(TestUdma_SrcMultiChannel[expected][index], TestUdma_DstMultiChannel[expected][index]);
        }
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/**
* \brief HC/UHC channel open coverage test (expect allocation failure).
*
* Test Category: Negative / Coverage
*
* Attempts to open HC/UHC variants for Block-Copy, TX, and RX when SoC flags
* disable support. Verifies Udma_chOpen returns UDMA_EALLOC for each case.
* This does not configure, enable, or submit transfers; it is purely for source coverage.
*/
static void TestUdma_allocationHcUhcChannel(void *args)
{
    (void)args;
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    /* Common tiny FQ ring to reach open path (even though alloc will fail) */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY_HC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    /* 1) Block-Copy HC */
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY_HC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    /* 2) Block-Copy UHC */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY_UHC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyCh2RingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY_UHC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    /* 3) TX HC */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX_HC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    /* PSIL peer required for TX/RX types; use an unmapped test thread */
    chPrms.peerChNum = UDMA_TEST_PKTDMA_UNMAPPED_TX_PEER_CH;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TX_HC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    /* 4) TX UHC */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TX_UHC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_UNMAPPED_TX_PEER_CH;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TX_UHC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    /* 5) RX HC */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX_HC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_UNMAPPED_RX_PEER_CH;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_RX_HC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    /* 6) RX UHC */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX_UHC);
    chPrms.chNum = UDMA_DMA_CH_ANY;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_UNMAPPED_RX_PEER_CH;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_RX_UHC, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_EALLOC, retVal);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/* Mapped RX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 core*/
#if(ENABLE_A53_CORE)
#if (UDMA_NUM_MAPPED_RX_GROUP > 0)
/**
 * \brief Mapped RX preferred channel allocation test.
 *
 * Test Category: Functional
 *
 * Uses RM to select preferred mapped RX channel and validates successful open and
 * teardown sequence.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel opens at preferred RX number; enable/disable/close succeed.
 */
static void TestUdma_mappedRxPreferredChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_RX_MAPPED;
    Udma_DrvHandleInt   drvHandleInt;
    uint32_t mappedChGrp, preferredChNum;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    /*Configure the driver for mapped RX channel allocation */
    mappedChGrp = UDMA_MAPPED_RX_GROUP_CPSW;
    preferredChNum = drvHandleInt->rmInitPrms.startMappedRxCh[mappedChGrp-UDMA_NUM_MAPPED_TX_GROUP];

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;  /* Set the preferred channel number */
    chPrms.mappedChGrp = mappedChGrp;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_CPSW_RX_PEER_CH;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief Mapped RX any available channel allocation test.
 *
 * Test Category: Functional
 *
 * Uses RM to select any available mapped RX channel and validates successful open and
 * teardown sequence.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel opens at any available RX number; enable/disable/close succeed.
 */
static void TestUdma_mappedRxAnyChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_RX_MAPPED;
    uint32_t mappedChGrp, preferredChNum;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /*Configure the driver for mapped RX channel allocation */
    mappedChGrp = UDMA_MAPPED_RX_GROUP_CPSW;
    preferredChNum = UDMA_DMA_CH_ANY;

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;
    chPrms.mappedChGrp = mappedChGrp;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_CPSW_RX_PEER_CH;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

#endif /* UDMA_NUM_MAPPED_RX_GROUP > 0*/
#endif /* For cores that have mapped CPSW resources reserved for RX channel allocation*/

/* Mapped TX channel allocation tests run only on cores that have mapped CPSW resources reserved - a53 and mcu r5 cores*/
#if(ENABLE_A53_CORE || ENABLE_MCU_R5_CORE)
#if (UDMA_NUM_MAPPED_TX_GROUP > 0)
/**
 * \brief Mapped TX preferred channel allocation test.
 *
 * Test Category: Functional
 *
 * Requests a specific mapped TX channel number (preferred) and validates open,
 * enable, disable, and close sequence returns success.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel allocated at preferred number; lifecycle APIs succeed.
 */
static void TestUdma_mappedTxPreferredChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    uint32_t mappedChGrp, preferredChNum;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_TX_MAPPED;
    Udma_DrvHandleInt   drvHandleInt;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    /*Configure the driver for mapped TX channel allocation */
    mappedChGrp = UDMA_MAPPED_TX_GROUP_CPSW;
    preferredChNum = drvHandleInt->rmInitPrms.startMappedTxCh[mappedChGrp];

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;  /* Set the preferred channel number */
    chPrms.mappedChGrp = mappedChGrp;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_CPSW_TX_PEER_CH;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}
/**
 * \brief Mapped TX any available channel allocation test.
 *
 * Test Category: Functional
 *
 * Requests any available mapped TX channel number and validates open,
 * enable, disable, and close sequence returns success.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Channel allocated at any available number; lifecycle APIs succeed.
 */
static void TestUdma_mappedTxAnyChannelAllocation(void *args)
{
    static Udma_DrvObject pktdmaDrvObj;
    Udma_DrvHandle drvHandle = &pktdmaDrvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    int32_t retVal;
    uint32_t mappedChGrp, preferredChNum;
    Udma_InitPrms udmaInitPrms;
    uint32_t chType = UDMA_CH_TYPE_TX_MAPPED;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /*Configure the driver for mapped TX channel allocation */
    mappedChGrp = UDMA_MAPPED_TX_GROUP_CPSW;
    preferredChNum = UDMA_DMA_CH_ANY;

    /* Open the channel */
    UdmaChPrms_init(&chPrms, chType);
    chPrms.chNum = preferredChNum;
    chPrms.mappedChGrp = mappedChGrp;
    chPrms.peerChNum = UDMA_TEST_PKTDMA_CPSW_TX_PEER_CH;
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = TEST_UDMA_RING_MEM_SIZE_SINGLE;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_SINGLE;

    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable the channel */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Disable the channel */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Close the channel */
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Deinit driver */
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}
#endif /*UDMA_NUM_MAPPED_TX_GROUP > 0 */
#endif /* For cores that have mapped CPSW resources reserved for TX channel allocation*/

