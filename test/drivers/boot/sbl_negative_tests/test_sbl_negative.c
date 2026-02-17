#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/mmcsd.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"


void TestSbl_openCloseSuccess(void *args);
void TestSbl_openOpenFail(void *args);
void TestSbl_openCloseOpen(void *args);
void TestSbl_openFail(void *args);
void TestSbl_closeFail(void *args);
void TestSbl_getBootMedia(void *args);
void TestSbl_getBootMediaFail(void *args);
void TestSbl_getImageSzFail(void *args);

void setUp(void)
{
    /* Setup function nothing to perform */
}

void tearDown(void)
{
    /* Tear down function nothing to perform */
}

void test_main(void * args)
{
    UNITY_BEGIN();

    RUN_TEST(TestSbl_openCloseSuccess,     8000, NULL);
    RUN_TEST(TestSbl_openCloseOpen,        8000, NULL);
    RUN_TEST(TestSbl_openFail,             8000, NULL);
    RUN_TEST(TestSbl_closeFail,            8000, NULL);
    RUN_TEST(TestSbl_getBootMedia,         8000, NULL);
    RUN_TEST(TestSbl_getBootMediaFail,     8000, NULL);
    RUN_TEST(TestSbl_getImageSzFail,       8000, NULL);
    RUN_TEST(TestSbl_openOpenFail,         8000, NULL);

    UNITY_END();
}

void TestSbl_openCloseSuccess(void *args)
{
    uint32_t loopVar;

    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_OpenCloseSuccess test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle  = Bootloader_open(loopVar, &bootParams);
        TEST_ASSERT_NOT_NULL(bootHandle);
        Bootloader_close(bootHandle);
    }
}

void TestSbl_openOpenFail(void *args)
{
    uint32_t loopVar;

    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");

    Bootloader_BootImageInfo bootImageInfo1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_BootImageInfo bootImageInfo2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    Bootloader_Params bootParams1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    Bootloader_Handle bootHandle1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle1[loopVar] = NULL;
        bootHandle2[loopVar] = NULL;

        Bootloader_Params_init(&bootParams1[loopVar]);
        Bootloader_Params_init(&bootParams2[loopVar]);

        Bootloader_BootImageInfo_init(&bootImageInfo1[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo2[loopVar]);
    }

    /* Open the driver once */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle1[loopVar]  = Bootloader_open(loopVar, &bootParams1[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle1[loopVar]);
    }

    /* Second time it should fail */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle2[loopVar]  = Bootloader_open(loopVar, &bootParams2[loopVar]);
        TEST_ASSERT_NULL(bootHandle2[loopVar]);
    }

    /* Close the original handles */ 
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        Bootloader_close(bootHandle1[loopVar]);
    }
}

void TestSbl_openCloseOpen(void *args)
{
    uint32_t loopVar;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle[CONFIG_BOOTLOADER_NUM_INSTANCES];
    
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = NULL;
        Bootloader_Params_init(&bootParams[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo[loopVar]);
    }

    /* Open the driver once and close it */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        Bootloader_close(bootHandle[loopVar]);
    }
    
    /* Open should work for the second time as well */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        Bootloader_close(bootHandle[loopVar]);
    }
}

void  TestSbl_openFail(void *args)
{
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* Open for an invalid instance and check if fails */
    bootHandle = Bootloader_open((CONFIG_BOOTLOADER_NUM_INSTANCES + 1), 
                    &bootParams);
    TEST_ASSERT_NULL(bootHandle);

    /*Check if open works after failure */
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    Bootloader_close(bootHandle);
}

void TestSbl_closeFail(void *args)
{
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_closeFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;
    
    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* Open for an valid instance and check if fails */
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);

    /* No hang should happen */
    Bootloader_close(NULL);

    /* close the original handle */
    Bootloader_close(bootHandle);
}

void TestSbl_getBootMedia(void *args)
{
    uint32_t media = SystemP_SUCCESS;
    uint32_t loopVar;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getBootMedia test\r\n");
    Bootloader_BootImageInfo bootImageInfo[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle[CONFIG_BOOTLOADER_NUM_INSTANCES] = {NULL , NULL};

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++ )
    {
        Bootloader_Params_init(&bootParams[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo[loopVar]);
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);   
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        media = Bootloader_getBootMedia(bootHandle[loopVar]);
        if(loopVar == 0)
        {
            TEST_ASSERT_EQUAL(media, BOOTLOADER_MEDIA_EMMC);
        }
        else
        {
            TEST_ASSERT_EQUAL(media, BOOTLOADER_MEDIA_FLASH);
        }
        Bootloader_close(bootHandle[loopVar]);
    }
}
    
void TestSbl_getBootMediaFail(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getBootMediaFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    
    status = Bootloader_getBootMedia(NULL);
    TEST_ASSERT_EQUAL(status, BOOTLOADER_INVALID_ID);

    Bootloader_close(bootHandle);
}

void TestSbl_getImageSzFail(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getImageSzFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;
    
    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    
    /* For invalid handle the size should be zero */
    status = Bootloader_getMulticoreImageSize(NULL);
    TEST_ASSERT_EQUAL(status, 0);

    Bootloader_close(bootHandle);
}

