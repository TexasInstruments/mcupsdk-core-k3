/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
 *  \file test_fvid.c
 *
 *  \brief fvid test application listing all test cases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <board/panel/i2c/i2c_bridge_sii9022a.h>
#include <drivers/fvid2.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_FVID2_NUM_FRAMES                                   (2U)
#define TEST_FVID2_TIMEOUT                                      (1000U)
#define TEST_FVID2_FRAME_COUNT                                  (2U)
#define TEST_FVID2_DATA_FORMAT_STRING                           (1U)
#define TEST_FVID2_INVALID_DATA_FORMAT_STRING                   ((uint32_t) 0x0089U)
#define TEST_FVID2_STD_STRING                                   (0U)
#define TEST_FVID2_INVALID_STD_STRING2                          (0x3CU)
#define TEST_FVID2_INAVLID_FRAME_NUMBER1                        (65U)
#define TEST_FVID2_INAVLID_FRAME_NUMBER2                        (0U)
#define TEST_FVID2_WORD_COUNT                                   (10U)
#define TEST_FVID2_WORD                                         (0xAAAAU)
#define TEST_FVID2_PRIORITY_0                                   (0U)
#define TEST_FVID2_PRIORITY_1                                   (1U)
#define TEST_FVID2_PRIORITY_2                                   (2U)
#define TEST_FVID2_INVALID_LIST_TYPE                            (2U)
#define TEST_FVID2_INVALID_ADD_MODE                             (3U)
#define TEST_FVID2_NUM_ELEMENTS                                 (2U)
#define TEST_FVID2_DUMMY_PARAM                                  (42U)
#define TEST_FVID2_NODE_IN_USE                                  (1U)
#define TEST_FVID2_NODE_DUMMY                                   (0U)
#define TEST_FVID2_NODE_ID_0                                    (0U)
#define TEST_FVID2_NODE_ID_1                                    (1U)
#define TEST_FVID2_NODE_ID_2                                    (2U)
#define TEST_FVID2_NODE_ID_3                                    (3U)
#define TEST_FVID2_NODE_ID_4                                    (4U)
#define TEST_FVID2_GT_TRACE_MASK                                (GT_TRACECLASS_MASK | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    const Fvid2_DrvOps *drvOps;
    /**< Driver operation table pointer. */
    uint32_t            numOpens;
    /**< Number of times the driver is opened using create API. */
    uint32_t            isUsed;
    /**< Flag indicating whether the object is used or not. */
} Fdm_Driver;

typedef struct
{
    Fdm_Driver         *drv;
    /**< Pointer to the driver object to which this channel is created. */
    Fdrv_Handle         drvHandle;
    /**< Driver handle returned by the actual driver. */
    Fvid2_CbParams      cbParams;
    /**< Application call back parameters. */
    uint32_t            isUsed;
    /**< Flag indicating whether the object is used or not. */
} Fdm_Channel;

/* Test Cases */
void TestDss_fvid2DynamicCoverage(void *args);

/* Helper functions */
static void TestDss_fvid2drvMgrDynCoverage(void);
static void TestDss_fvid2UtilsDynCoverage(void);
static void TestDss_fvid2GraphDynCoverage(void);
static void TestDss_fvid2TraceDynCoverage(void);
static void TestDss_fvid2ReInitNodes(void);
static int32_t TestDss_fvid2ProcessRequest(Fvid2_Handle  handle, Fvid2_FrameList *inFrameList, Fvid2_FrameList *outFrameList, uint32_t  timeout)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Fvid2Utils_Node gNode,gNode1,gNode2,gNode3,gNode4;
static Fvid2UtilsLinkListObj gllobj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();
    
    RUN_TEST(TestDss_fvid2DynamicCoverage, 7183, NULL);
    
    UNITY_END();

    return;
}

void TestDss_fvid2DynamicCoverage(void *args)
{
    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);

    DebugP_log("FVID2 dynamic coverage test... \r\n\n");

    TestDss_fvid2drvMgrDynCoverage();
    TestDss_fvid2UtilsDynCoverage();
    TestDss_fvid2GraphDynCoverage();
    TestDss_fvid2TraceDynCoverage();

    DebugP_log("\r\n FVID2 dynamic coverage test: PASS \r\n");

    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static int32_t TestDss_fvid2ProcessRequest(Fvid2_Handle  handle, Fvid2_FrameList *inFrameList, Fvid2_FrameList *outFrameList, uint32_t  timeout)
{
    int32_t retVal = FVID2_SOK;
    return retVal;
}

static void TestDss_fvid2ReInitNodes(void)
{
    /* Reinitialize Circular linkedlist nodes */
    gNode1.next = &gNode2;
    gNode1.prev = &gNode2;
    gNode2.next = &gNode1;
    gNode2.prev = &gNode1;
    gllobj.headNode = NULL;
    gllobj.tailNode = NULL;

    /* Reinitialize Doubly linkedlist Nodes */
    gNode3.next = &gNode4;
    gNode3.prev = NULL;
    gNode4.next = NULL;
    gNode4.prev = &gNode3;
}

static void TestDss_fvid2drvMgrDynCoverage(void)
{
    int32_t retVal = FVID2_SOK;
    const char *retPtr = NULL;
    const Fvid2_InitPrms *initPrms;
    Fvid2_ModeInfo modeInfo;
    Fvid2_Frame frame;
    Fvid2_Frame *frm = &frame;
    Fvid2_Handle handle;
    Fvid2_DrvOps drvOpsInstance;
    Fdm_Driver drvInstance;
    Fdm_Channel channelInstance;

    Fvid2_FrameList inFrameList = {0};
    Fvid2_FrameList outFrameList = {0};
    outFrameList.numFrames = TEST_FVID2_FRAME_COUNT;
    modeInfo.standard = FVID2_STD_NTSC;
    handle = &channelInstance;
    channelInstance.drv = &drvInstance;
    drvInstance.drvOps = &drvOpsInstance;
    drvOpsInstance.queueFxn = NULL;
    drvOpsInstance.dequeueFxn = NULL;
    drvOpsInstance.deleteFxn = NULL;
    drvOpsInstance.controlFxn = NULL;
    drvOpsInstance.processRequestFxn = NULL;
    drvOpsInstance.getProcessedRequestFxn = NULL;

    /* FVID2 init function */
    retVal = Fvid2_init(initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Get the version string for FVID2 interface */
    retPtr = Fvid2_getVersionString();
    UNITY_TEST_ASSERT_EQUAL_CHAR_ARRAY(FVID2_VERSION_STRING,retPtr,sizeof(FVID2_VERSION_STRING),__LINE__,"Fvid2_getVersionString Failed");

    /* Get the FVID2 driver version in uint32_t form */
    retVal = Fvid2_getVersionNumber();
    TEST_ASSERT_EQUAL_INT32(FVID2_VERSION_NUMBER, retVal);

    /* Passing NULL handle to Fvid2_processRequest */
    retVal = Fvid2_processRequest(NULL, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_processRequest */
    retVal = Fvid2_processRequest(handle, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EUNSUPPORTED_OPS, retVal);

    /* Passing a valid handle to Fvid2_processRequest and a call to dummy driver's process frame function */
    drvOpsInstance.processRequestFxn = &TestDss_fvid2ProcessRequest;
    retVal = Fvid2_processRequest(handle, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing NULL handle to Fvid2_getProcessedRequest */
    retVal = Fvid2_getProcessedRequest(NULL, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_getProcessedRequest */
    retVal = Fvid2_getProcessedRequest(handle, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EUNSUPPORTED_OPS, retVal);

    /* Passing a valid handle to Fvid2_getProcessedRequest and a call to dummy driver's process frame function */
    drvOpsInstance.getProcessedRequestFxn = &TestDss_fvid2ProcessRequest;
    retVal = Fvid2_getProcessedRequest(handle, &inFrameList, &outFrameList, TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing a valid parameter to get the name of the data format in printable string */
    retPtr = Fvid2_getDataFmtString(TEST_FVID2_DATA_FORMAT_STRING);
    UNITY_TEST_ASSERT_EQUAL_CHAR_ARRAY("YUV422I_YUYV",retPtr,sizeof("YUV422I_YUYV"),__LINE__,"Fvid2_getDataFmtString Failed");

    /* Passing a Invalid parameter to get the name of the data format in printable string */
    retPtr = Fvid2_getDataFmtString(TEST_FVID2_INVALID_DATA_FORMAT_STRING);
    UNITY_TEST_ASSERT_EQUAL_CHAR_ARRAY("UNKNOWN",retPtr,sizeof("UNKNOWN"),__LINE__,"Fvid2_getDataFmtString Failed");

    /* Passing a valid parameter to get the name of the standard in printable string */
    retPtr = Fvid2_getStandardString(TEST_FVID2_STD_STRING);
    UNITY_TEST_ASSERT_EQUAL_CHAR_ARRAY("NTSC",retPtr,sizeof("NTSC"),__LINE__,"Fvid2_getStandardString Failed");

    /* Passing a Invalid parameter to get the name of the standard in printable string */
    retPtr = Fvid2_getStandardString(TEST_FVID2_INVALID_STD_STRING2);
    UNITY_TEST_ASSERT_EQUAL_CHAR_ARRAY("UNKNOWN",retPtr,sizeof("UNKNOWN"),__LINE__,"Fvid2_getStandardString Failed");

    /* Passing a framelist to check the FVID2 frame list of dequeue call for error */
    retVal = Fvid2_checkDqFrameList(&inFrameList, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing a NULL param to Fvid2_checkDqFrameList */
    retVal = Fvid2_checkDqFrameList(NULL, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a framelist with more than max frame limit to Fvid2_checkDqFrameList */
    retVal = Fvid2_checkDqFrameList(&inFrameList, (FVID2_MAX_FRAME_PTR+1));
    TEST_ASSERT_EQUAL_INT32(FVID2_EOUT_OF_RANGE, retVal);

    /* Passing a NULL param to Fvid2_checkFrameList */
    retVal = Fvid2_checkFrameList(NULL, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid framelist but with invalid frame number to Fvid2_checkFrameList */
    inFrameList.numFrames = TEST_FVID2_INAVLID_FRAME_NUMBER1;
    retVal = Fvid2_checkFrameList(&inFrameList,FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_EOUT_OF_RANGE, retVal);

    /* Passing a valid framelist but with NULL frame number to Fvid2_checkFrameList */
    inFrameList.numFrames = TEST_FVID2_INAVLID_FRAME_NUMBER2;
    retVal = Fvid2_checkFrameList(&inFrameList, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_EOUT_OF_RANGE, retVal);

    /* Passing a valid framelist with second frame as NULL to Fvid2_checkFrameList */
    inFrameList.numFrames = TEST_FVID2_FRAME_COUNT;
    inFrameList.frames[0] = frm;
    inFrameList.frames[1] = NULL;
    retVal = Fvid2_checkFrameList(&inFrameList, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid framelist to Fvid2_checkFrameList */
    inFrameList.frames[1] = frm;
    retVal = Fvid2_checkFrameList(&inFrameList, FVID2_MAX_FRAME_PTR);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing NULL to Fvid2_getModeInfo get the information about various FVID2 modes */
    retVal = Fvid2_getModeInfo(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid standard pointed by a modeInfo ptr to get the information about FVID2 mode */
    modeInfo.standard = FVID2_STD_NTSC;
    retVal = Fvid2_getModeInfo(&modeInfo);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing a Invalid standard pointed by a modeInfo ptr to Fvid2_getModeInfo */
    modeInfo.standard = TEST_FVID2_INVALID_STD_STRING2;
    retVal = Fvid2_getModeInfo(&modeInfo);
    TEST_ASSERT_EQUAL_INT32(FVID2_EINVALID_PARAMS, retVal);

    /* Passing NULL params to Fvid2_queue */
    retVal = Fvid2_queue(NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_queue */
    retVal = Fvid2_queue(handle,NULL,0);
    TEST_ASSERT_EQUAL_INT32(FVID2_EUNSUPPORTED_OPS, retVal);

    /* Passing NULL params to Fvid2_dequeue */
    retVal = Fvid2_dequeue(NULL,NULL,0,TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_dequeue */
    retVal = Fvid2_dequeue(handle,NULL,0,TEST_FVID2_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(FVID2_EUNSUPPORTED_OPS, retVal);

    /* Passing NULL params to Fvid2_control */
    retVal = Fvid2_control(NULL, FVID2_START, NULL, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_control */
    retVal = Fvid2_control(handle, FVID2_START, NULL, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EUNSUPPORTED_OPS, retVal);

    /* Passing NULL params to Fvid2_delete */
    retVal = Fvid2_delete(NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Passing a valid handle to Fvid2_delete */
    retVal = Fvid2_delete(handle,NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing two frameLists to copy the Frames (Void function) */
    inFrameList.numFrames = TEST_FVID2_NUM_FRAMES;
    Fvid2_copyFrameList(&inFrameList,&outFrameList);
    retVal = memcmp(&inFrameList,&outFrameList,1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing two frameLists to duplicate the Frames (Void function) */
    Fvid2_duplicateFrameList(&inFrameList,&outFrameList);
    retVal = memcmp(&inFrameList,&outFrameList,1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* FVID2 init function call with a NULL parameter */
    retVal = Fvid2_init(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Fvid2_unRegisterDriver function call with a NULL parameter */
    retVal = Fvid2_unRegisterDriver(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EFAIL, retVal);
}

static void TestDss_fvid2UtilsDynCoverage(void)
{
    int32_t retVal = FVID2_SOK;
    Fvid2Utils_LinkListType listType = FVID2UTILS_LLT_CIRCULAR;
    Fvid2Utils_LinkAddMode addMode = FVID2UTILS_LAM_TOP;
    uint32_t *memPtr = NULL;
    uint8_t mem[20];

    /* Create and initialize new node pointers */
    Fvid2Utils_Node *nodePtr = &gNode;
    Fvid2Utils_Node *circularNodePtr = &gNode1;
    Fvid2Utils_Node *doubleNodePtr = &gNode3;
    Fvid2Utils_Node *retNode = NULL;

    /* Reinitialize the created sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Initializes the Util objects */
    retVal = Fvid2Utils_init();
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Sets the memory for the given Word and word count */
    memPtr = Fvid2Utils_memsetw(mem, TEST_FVID2_WORD, TEST_FVID2_WORD_COUNT);
    TEST_ASSERT_EQUAL_PTR(mem, memPtr);

    /* Compare memory block 1 with memory block 2 */
    retVal = Fvid2Utils_memcmp(mem, mem, TEST_FVID2_WORD_COUNT);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Releases all nodes */
    retVal = Fvid2Utils_unLinkAllNodes(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Constructs a Queue object */
    retVal = Fvid2Utils_constructQ(&gllobj);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Constructs a link list object */
    retVal = Fvid2Utils_constructLinkList(&gllobj, listType, addMode);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Constructs a link list object */
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    retVal = Fvid2Utils_constructLinkList(&gllobj, listType, addMode);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Releases all nodes */
    retVal = Fvid2Utils_unLinkAllNodes(&gllobj);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Links a node to the linked list (Void function) */
    Fvid2Utils_linkNodePri(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);

    /* Links a node to the doubly linked list (Void function) */
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    Fvid2Utils_linkNodePri(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);

    /* Passing a Invalid list type to Fvid2Utils_linkNodePri (Void function) */
    gllobj.listType = TEST_FVID2_INVALID_LIST_TYPE;
    Fvid2Utils_linkNodePri(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);

    /* Links a node to the circularly linked list (Void function) */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    nodePtr->priority = TEST_FVID2_PRIORITY_2;
    Fvid2Utils_linkNodePri(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);

    /* Links a circularly linked list with no two nodes with same priority */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    gllobj.headNode = NULL;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_0);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Initialize the linked list object */
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.headNode = NULL_PTR;
    gllobj.tailNode = NULL_PTR;
    gllobj.numElements = 0;
    gllobj.priorityCnt = 0;

    /* Links a doubly linked list with no two nodes with same priority */
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Links a doubly linked list with no two nodes with same priority */
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, retVal);

    /* Links a doubly linked list with no two nodes with same priority */
    gNode1.priority = TEST_FVID2_PRIORITY_2;
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, circularNodePtr, TEST_FVID2_PRIORITY_0);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Links a circularly linked list with no two nodes with same priority */
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, circularNodePtr, TEST_FVID2_PRIORITY_0);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    gNode1.priority = TEST_FVID2_PRIORITY_0;

    /* Reinitialize the created sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Links a doubly linked list with no two nodes with same priority */
    gllobj.addMode = FVID2UTILS_LAM_PRIORITY;
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    gllobj.headNode = &gNode1;
    gNode1.priority = TEST_FVID2_PRIORITY_2;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, &gNode2, TEST_FVID2_PRIORITY_0);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    gNode1.priority = TEST_FVID2_PRIORITY_0;

    /* Passing a Invalid list type to Fvid2Utils_linkUniqePriNode */
    gllobj.priorityCnt = TEST_FVID2_PRIORITY_0;
    gllobj.listType = TEST_FVID2_INVALID_LIST_TYPE;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing addMode as Top to Fvid2Utils_linkUniqePriNode */
    gllobj.priorityCnt = TEST_FVID2_PRIORITY_0;
    gllobj.addMode = FVID2UTILS_LAM_TOP;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing addMode as Bottom to Fvid2Utils_linkUniqePriNode */
    gllobj.priorityCnt = TEST_FVID2_PRIORITY_0;
    gllobj.addMode = FVID2UTILS_LAM_BOTTOM;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Passing an Invalid addMode to Fvid2Utils_linkUniqePriNode */
    gllobj.addMode = TEST_FVID2_INVALID_ADD_MODE;
    retVal = Fvid2Utils_linkUniqePriNode(&gllobj, nodePtr, TEST_FVID2_PRIORITY_1);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Reinitialize the created sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by nodePtr from circular link list (Void function) */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    Fvid2Utils_unLinkNodePri(&gllobj, nodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node from circular link list (Void function) */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    gllobj.headNode = &gNode2;
    gNode2.next = &gNode1;
    gNode2.prev = &gNode2;
    Fvid2Utils_unLinkNodePri(&gllobj, &gNode2);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by nodePtr from doubly link list (Void function) */
    gNode.prev = &gNode1;
    gNode.next = NULL;
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    Fvid2Utils_unLinkNodePri(&gllobj, nodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by circularNodePtr from circular link list (Void function) */
    gllobj.headNode = &gNode1;
    gNode1.next = &gNode1;
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    Fvid2Utils_unLinkNodePri(&gllobj, circularNodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by circularNodePtr from circular link list (Void function) */
    gllobj.headNode = &gNode1;
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    Fvid2Utils_unLinkNodePri(&gllobj, circularNodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by doubleNodePtr from double link list (Void function) */
    gllobj.headNode = &gNode3;
    gllobj.listType = FVID2UTILS_LLT_DOUBLE;
    Fvid2Utils_unLinkNodePri(&gllobj, doubleNodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node of a invalid list type (Void function) */
    gllobj.listType = TEST_FVID2_INVALID_LIST_TYPE;
    Fvid2Utils_unLinkNodePri(&gllobj, nodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by nodePtr (Void function) */
    Fvid2Utils_unLinkNode(&gllobj, nodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by circularNodePtr (Void function) */
    gllobj.headNode=&gNode1;
    Fvid2Utils_unLinkNode(&gllobj, circularNodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node pointed by circularNodePtr (Void function) */
    gllobj.headNode=&gNode1;
    gllobj.tailNode=gllobj.headNode;
    Fvid2Utils_unLinkNode(&gllobj, circularNodePtr);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node with invalid number of elements (Void function) */
    gllobj.headNode=&gNode1;
    gNode1.next=&gNode2;
    gllobj.tailNode=&gNode2;
    gllobj.numElements=TEST_FVID2_NUM_ELEMENTS;
    Fvid2Utils_unLinkNode(&gllobj, &gNode2);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Unlinking a node with invalid number of elements (Void function) */
    Fvid2Utils_Node Node5;
    gllobj.headNode=&gNode1;
    gNode1.next=&Node5;
    gllobj.numElements=TEST_FVID2_NUM_ELEMENTS;
    Fvid2Utils_unLinkNode(&gllobj, &Node5);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Passing a NULL parameter as node (Void function) */
    gllobj.headNode=&gNode1;
    gNode2.next=NULL;
    gllobj.tailNode=&gNode2;
    Fvid2Utils_unLinkNode(&gllobj, NULL);

    /* Reinitialize the sample nodes after unlinking */
    TestDss_fvid2ReInitNodes();

    /* Linking the node pointed by the nodePtr as tail (Void function) */
    Fvid2Utils_linkNodeToTail(&gllobj, nodePtr);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Linking the node pointed by the nodePtr as tail (Void function) */
    gllobj.headNode = NULL;
    gllobj.tailNode = &gNode2;
    Fvid2Utils_linkNodeToTail(&gllobj, nodePtr);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Linking the node pointed by the nodePtr as head node (Void function) */
    Fvid2Utils_linkNodeToHead(&gllobj, nodePtr);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Linking the node pointed by the nodePtr as head node (Void function) */
    gllobj.headNode = NULL;
    gllobj.tailNode = &gNode2;
    Fvid2Utils_linkNodeToHead(&gllobj, nodePtr);

    /* Unlinking the head node from the list */
    retNode = Fvid2Utils_unLinkNodeFromHead(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the head node from the list */
    gllobj.headNode=&gNode1;
    gNode1.next=NULL;
    gllobj.tailNode=&gNode2;
    retNode = Fvid2Utils_unLinkNodeFromHead(&gllobj);
    TEST_ASSERT_EQUAL_PTR(&gNode1,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the head node from the list */
    gllobj.headNode=NULL;
    gllobj.tailNode=&gNode2;
    retNode = Fvid2Utils_unLinkNodeFromHead(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the tail node  from the list */
    retNode = Fvid2Utils_unLinkNodeFromTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the tail node from the list */
    gllobj.headNode=&gNode1;
    gllobj.tailNode=NULL;
    retNode = Fvid2Utils_unLinkNodeFromTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the tail node from the list */
    gllobj.headNode=&gNode1;
    gNode2.prev=NULL;
    gllobj.tailNode=&gNode2;
    retNode = Fvid2Utils_unLinkNodeFromTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(&gNode2,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Unlinking the tail node from the list */
    gllobj.headNode=&gNode1;
    gllobj.tailNode=&gNode2;
    retNode = Fvid2Utils_unLinkNodeFromTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(&gNode2,retNode);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Returns a refrence to head node from list */
    retNode = Fvid2Utils_getHeadNode(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Returns a refrence to tail node from list */
    retNode = Fvid2Utils_getTailNode(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Passing NULL as parameter to Fvid2Utils_isListEmpty */
    retVal = Fvid2Utils_isListEmpty(NULL);
    TEST_ASSERT_EQUAL_INT32(TRUE, retVal);

    /* Passing a valid list to Fvid2Utils_isListEmpty */
    retVal = Fvid2Utils_isListEmpty(&gllobj);
    TEST_ASSERT_EQUAL_INT32(TRUE,retVal);

    /* Passing a valid circular list to get number of nodes */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    retVal = Fvid2Utils_getNumNodes(&gllobj);
    TEST_ASSERT_EQUAL_INT32(0,retVal);

    /* Passing a Invalid list type to get number of nodes */
    gllobj.listType = TEST_FVID2_INVALID_LIST_TYPE;
    retVal = Fvid2Utils_getNumNodes(&gllobj);
    TEST_ASSERT_EQUAL_INT32(0,retVal);

    /* Passing a list with no nodes to Fvid2Utils_getNumNodes */
    gllobj.headNode = NULL;
    retVal = Fvid2Utils_getNumNodes(&gllobj);
    TEST_ASSERT_EQUAL_INT32(0,retVal);

    /* Reinitialize the sample nodes */
    TestDss_fvid2ReInitNodes();

    /* Passing a valid circular list to get number of nodes */
    gllobj.listType = FVID2UTILS_LLT_CIRCULAR;
    gllobj.headNode = &gNode1;
    retVal = Fvid2Utils_getNumNodes(&gllobj);
    TEST_ASSERT_EQUAL_INT32(2,retVal);

    /* Returns a refrence to head node from queue */
    retNode = Fvid2Utils_peakHead(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Returns a refrence to tail node from queue */
    retNode = Fvid2Utils_peakTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Passing a list with a tail node as NULL */
    gllobj.tailNode = NULL;
    retNode = Fvid2Utils_peakTail(&gllobj);
    TEST_ASSERT_EQUAL_PTR(NULL,retNode);

    /* Passing a list to get the node count */
    retVal = Fvid2Utils_getNodeCnt(&gllobj);
    TEST_ASSERT_EQUAL_INT32(1 ,retVal);

    /* Passing a queue to check the emptiness */
    retVal = Fvid2Utils_isQEmpty(&gllobj);
    TEST_ASSERT_EQUAL_INT32(FALSE , retVal);

    /* De-Initializes the Util objects */
    retVal = Fvid2Utils_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK , retVal);

    /* Link the node to the tail of the list (Void function) */
    gllobj.tailNode = NULL;
    gllobj.headNode = &gNode1;
    Fvid2Utils_linkNodeToTail(&gllobj, nodePtr);
}

static void TestDss_fvid2GraphDynCoverage(void)
{
    uint32_t array[] = {0, 0, 3, 0, 5};
    uint32_t size = sizeof(array) / sizeof(array[0]);
    int32_t result;

    bool isInputAvailable;
    bool isOutputAvailable;

    /* Structure variable containing edge information and a handle */
    Fvid2_GraphEdgeInfo edge;
    Fvid2_GraphInfo graphHandle;

    /* Define input and output node sets for sample nodes */
    Fvid2_GraphNodeSet inputNodeSet = {
        .numNodes = 2,
        .isEnabled = {FVID2_GRAPH_NODE_MODE_DISABLE, FVID2_GRAPH_NODE_MODE_ENABLE}
    };

    Fvid2_GraphNodeSet outputNodeSet = {
        .numNodes = 2,
        .isEnabled = {FVID2_GRAPH_NODE_MODE_DISABLE, FVID2_GRAPH_NODE_MODE_ENABLE}
    };

    Fvid2_GraphNodeSet outputNodeSet2 = {
        .numNodes = 1,
        .isEnabled = {FVID2_GRAPH_NODE_MODE_ENABLE}
    };

    Fvid2_GraphNodeSet outputNodeSet3 = {
        .numNodes = 2,
        .isEnabled = {FVID2_GRAPH_NODE_MODE_DISABLE , FVID2_GRAPH_NODE_MODE_DISABLE}
    };

    /* Create an array of sample nodes */
    Fvid2_GraphNodeInfo nodeArray[4] = {
        {
            .nodeId = TEST_FVID2_NODE_ID_0,
            .nodeInNum = FVID2_GRAPH_NODE_IN_MULTI,
            .nodeOutNum = FVID2_GRAPH_NODE_OUT_SINGLE,
            .nodeType = FVID2_GRAPH_NODE_TYPE_DUMMY,
            .isDummy = TEST_FVID2_NODE_IN_USE,
            .inUse = TEST_FVID2_NODE_DUMMY,
            .inputNodeSet = inputNodeSet,
            .outputNodeSet = outputNodeSet3
        },
        {
            .nodeId = TEST_FVID2_NODE_ID_1,
            .nodeInNum = FVID2_GRAPH_NODE_IN_MULTI,
            .nodeOutNum = FVID2_GRAPH_NODE_OUT_SINGLE,
            .nodeType = FVID2_GRAPH_NODE_TYPE_DUMMY,
            .isDummy = TEST_FVID2_NODE_DUMMY,
            .inUse = TEST_FVID2_NODE_IN_USE,
            .inputNodeSet = inputNodeSet,
            .outputNodeSet = outputNodeSet
        },
        {
            .nodeId = TEST_FVID2_NODE_ID_2,
            .nodeInNum = FVID2_GRAPH_NODE_IN_SINGLE,
            .nodeOutNum = FVID2_GRAPH_NODE_OUT_NONE,
            .nodeType = FVID2_GRAPH_NODE_TYPE_DUMMY,
            .isDummy = TEST_FVID2_NODE_DUMMY,
            .inUse = TEST_FVID2_NODE_IN_USE,
            .inputNodeSet = {0},
            .outputNodeSet = {0}
        },
        {
            .nodeId = TEST_FVID2_NODE_ID_3,
            .nodeInNum = FVID2_GRAPH_NODE_IN_SINGLE,
            .nodeOutNum = FVID2_GRAPH_NODE_OUT_NONE,
            .nodeType = FVID2_GRAPH_NODE_TYPE_DUMMY,
            .isDummy = TEST_FVID2_NODE_DUMMY,
            .inUse = TEST_FVID2_NODE_IN_USE,
            .inputNodeSet = outputNodeSet2,
            .outputNodeSet = {0}
        }
    };

    Fvid2_GraphEdgeInfo edge_List[4] = {
        {
            .startNode=TEST_FVID2_NODE_ID_0,
            .endNode=TEST_FVID2_NODE_ID_1
        },
        {
            .startNode=TEST_FVID2_NODE_ID_1,
            .endNode=TEST_FVID2_NODE_ID_3
        },
        {
            .startNode=TEST_FVID2_NODE_ID_2,
            .endNode=TEST_FVID2_NODE_ID_0
        },
        {
            .startNode=TEST_FVID2_NODE_ID_0,
            .endNode=TEST_FVID2_NODE_ID_0
        }
    };

    /* Create a sample node list */
    Fvid2_GraphNodeList nodeList = {
        .numNodes = 4,
        .list = nodeArray
    };

    /* Create a NULL node list */
    Fvid2_GraphNodeList Null_nodeList = {
        .numNodes = 0,
        .list = NULL
    };

    /* Create a sample edge list */
    Fvid2_GraphEdgeList edgeList = {
        .numEdges = 4,
        .list = edge_List
    };

    /* Create a NULL edge list */
    Fvid2_GraphEdgeList Null_edgeList = {
        .numEdges = 0,
        .list = NULL
    };

    graphHandle.nodeList = &nodeList;
    graphHandle.edgeList = &edgeList;

    /* Passing sample nodelist and respective node id to check the input node availability */
    isInputAvailable = Fvid2_graphIsNodeInputAvailable(&nodeList, TEST_FVID2_NODE_ID_3);
    if(isInputAvailable)
        DebugP_log("Graph node input available\r\n");
    else
        DebugP_log("Graph node input not available\r\n");

    /* Passing sample nodelist and respective node id to check the input node availability */
    isInputAvailable = Fvid2_graphIsNodeInputAvailable(&nodeList, TEST_FVID2_NODE_ID_2);
    if(isInputAvailable)
        DebugP_log("Graph node input available\r\n");
    else
        DebugP_log("Graph node input not available\r\n");

    /* Passing sample nodelist and respective node id to check the input node availability */
    isInputAvailable = Fvid2_graphIsNodeInputAvailable(&nodeList, TEST_FVID2_NODE_ID_1);
    if(isInputAvailable)
        DebugP_log("Graph node input available\r\n");
    else
        DebugP_log("Graph node input not available\r\n");

    /* Passing sample nodelist and respective node id to check the input node availability */
    isInputAvailable = Fvid2_graphIsNodeInputAvailable(&nodeList, TEST_FVID2_NODE_ID_4);
    if(isInputAvailable)
        DebugP_log("Graph node input available\r\n");
    else
        DebugP_log("Graph node input not available\r\n");

    /* Passing sample nodelist and respective node id to check the output node availability */
    isOutputAvailable = Fvid2_graphIsNodeOutputAvailable(&nodeList, TEST_FVID2_NODE_ID_3);
    if(isOutputAvailable)
        DebugP_log("Graph node output available\r\n");
    else
        DebugP_log("Graph node output not available\r\n");

    /* Passing sample nodelist and respective node id to check the output node availability */
    isOutputAvailable = Fvid2_graphIsNodeOutputAvailable(&nodeList, TEST_FVID2_NODE_ID_2);
    if(isOutputAvailable)
        DebugP_log("Graph node output available\r\n");
    else
        DebugP_log("Graph node output not available\r\n");

    /* Passing sample nodelist and respective node id to check the output node availability */
    isOutputAvailable = Fvid2_graphIsNodeOutputAvailable(&nodeList, TEST_FVID2_NODE_ID_1);
    if(isOutputAvailable)
        DebugP_log("Graph node output available\r\n");
    else
        DebugP_log("Graph node output not available\r\n");

    /* Passing sample nodelist and respective node id to check the output node availability */
    isOutputAvailable = Fvid2_graphIsNodeOutputAvailable(&nodeList, TEST_FVID2_NODE_ID_4);
    if(isOutputAvailable)
        DebugP_log("Graph node output available\r\n");
    else
        DebugP_log("Graph node output not available\r\n");

    /* Passing the sample array and size to get enabled node index */
    result = Fvid2_graphGetEnabledIndex(array, size);
    if (result != FVID2_EFAIL)
        DebugP_log("non-zero element found\r\n");
    else
        DebugP_log("No non-zero element is found\r\n");

    /* Passing the sample array and it's size as null */
    result = Fvid2_graphGetEnabledIndex(array, 0);
    if (result != FVID2_EFAIL)
        DebugP_log("non-zero element found\r\n");
    else
        DebugP_log("No non-zero element is found\r\n");

    /* Test edge addition */
    Fvid2_graphAddEdge(&edge, TEST_FVID2_NODE_ID_1, TEST_FVID2_NODE_ID_2);
    DebugP_log("Edge added: startNode = 1, endNode = 2\r\n");

    /* Edge with same start and end nodes */
    Fvid2_graphAddEdge(&edge, TEST_FVID2_NODE_ID_3, TEST_FVID2_NODE_ID_3);
    DebugP_log("Edge added: startNode = 3, endNode = 3\r\n");

    /* Allocation of graph nodes */
    result = Fvid2_graphAllocNodes(&nodeList, &edgeList, FVID2_GRAPH_NODE_MODE_ENABLE);
    if (result != FVID2_SOK)
    {
        DebugP_log("Graph node allocation failed\r\n");
    }
    else
    {
        TEST_ASSERT_EQUAL_INT32(FVID2_SOK, result);
    }

    /* Passing node list and edge list to free them */
    result = Fvid2_graphFreePath(&Null_nodeList,&Null_edgeList);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, result);

    /* Passing a node list with a edge node in use */
    nodeArray[TEST_FVID2_NODE_ID_1].isDummy = TEST_FVID2_NODE_IN_USE;
    Fvid2_graphInit(&nodeList,&edgeList,&graphHandle);

    /* Passing a node list with a node input number as none */
    nodeArray[1].nodeInNum = FVID2_GRAPH_NODE_IN_NONE;
    result = Fvid2_graphAllocNodes(&nodeList, &edgeList, FVID2_GRAPH_NODE_MODE_ENABLE);
    DebugP_log("\r\n Fvid2_graphAllocNodes - %d\r\n",result);
}

static void TestDss_fvid2TraceDynCoverage(void)
{
    uintptr_t param0 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param1 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param2 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param3 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param4 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param5 = TEST_FVID2_DUMMY_PARAM;
    uintptr_t param6 = TEST_FVID2_DUMMY_PARAM;

    /* Passing default mask and class type to Trace with zero parameter */
    GT_trace0(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing NULL and default class type to Trace with zero parameter */
    GT_trace0(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with zero parameter */
    GT_trace0(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with zero parameter */
    GT_trace0(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with zero parameter */
    GT_trace0(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing default mask and NULL as class to Trace with zero parameter */
    GT_trace0(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace0 !!!");

    /* Passing default mask and class type to Trace with one parameter */
    GT_trace1(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing NULL and default class type to Trace with one parameter */
    GT_trace1(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with one parameter */
    GT_trace1(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with one parameter */
    GT_trace1(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with one parameter */
    GT_trace1(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing default mask and NULL as class to Trace with one parameter */
    GT_trace1(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace1 !!!",
        param0);

    /* Passing default mask and class type to Trace with two parameters */
    GT_trace2(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing NULL and default class type to Trace with two parameters */
    GT_trace2(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with two parameters */
    GT_trace2(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with two parameters */
    GT_trace2(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with two parameters */
    GT_trace2(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing default mask and NULL as class to Trace with two parameters */
    GT_trace2(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace2 !!!",
        param0,
        param1);

    /* Passing default mask and class type to Trace with three parameters */
    GT_trace3(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing NULL and default class type to Trace with three parameters */
    GT_trace3(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with three parameters */
    GT_trace3(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with three parameters */
    GT_trace3(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with three parameters */
    GT_trace3(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing default mask and NULL as class to Trace with three parameters */
    GT_trace3(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace3 !!!",
        param0,
        param1,
        param2);

    /* Passing default mask and class type to Trace with four parameters */
    GT_trace4(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing NULL and default class type to Trace with four parameters */
    GT_trace4(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with four parameters */
    GT_trace4(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with four parameters */
    GT_trace4(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with four parameters */
    GT_trace4(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing default mask and NULL as class to Trace with four parameters */
    GT_trace4(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace4 !!!",
        param0,
        param1,
        param2,
        param3);

    /* Passing default mask and class type to Trace with five parameters */
    GT_trace5(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing NULL and default class type to Trace with five parameters */
    GT_trace5(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with five parameters */
    GT_trace5(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with five parameters */
    GT_trace5(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with five parameters */
    GT_trace5(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing default mask and NULL as class to Trace with five parameters */
    GT_trace5(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace5 !!!",
        param0,
        param1,
        param2,
        param3,
        param4);

    /* Passing default mask and class type to Trace with six parameters */
    GT_trace6(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing NULL and default class type to Trace with six parameters */
    GT_trace6(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with six parameters */
    GT_trace6(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with six parameters */
    GT_trace6(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with six parameters */
    GT_trace6(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing default mask and NULL as class to Trace with six parameters */
    GT_trace6(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace6 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5);

    /* Passing default mask and class type to Trace with seven parameters */
    GT_trace7(
        Fvid2Trace, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);

    /* Passing NULL and default class type to Trace with seven parameters */
    GT_trace7(
        0, GT_ERR,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);

    /* Passing GT_TraceState_Enable and GT_TRACECLASS_MASK to Trace with seven parameters */
    GT_trace7(
        GT_TraceState_Enable, GT_TRACECLASS_MASK,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO to Trace with seven parameters */
    GT_trace7(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);

    /* Passing TEST_FVID2_GT_TRACE_MASK and GT_INFO1 to Trace with seven parameters */
    GT_trace7(
        TEST_FVID2_GT_TRACE_MASK, GT_INFO1,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);

    /* Passing default mask and NULL as class to Trace with seven parameters */
    GT_trace7(
        Fvid2Trace, 0,
        (const char *) __FILE__, (int32_t) __LINE__,
        (const char *)"\nAssertion GT_trace7 !!!",
        param0,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6);
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}
