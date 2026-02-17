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

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE       (0x800000) 
#define BOOTLOADER_SD_A53_APPIMAGE_FILENAME     ("/sd0/app_a53")

uint8_t gAppimage[0x1900000] __attribute__ ((section (".bss.app"), aligned (128)));
uint8_t gAppImageBuf[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

void TestSbl_singleCoreImageEmmcBoot(void *args);
void TestSbl_singleCoreImageSdBoot(void *args);
void TestSbl_singleCoreImageOspiBoot(void *args);

int TestSbl_openSdImage(char* imageName);

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
    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();
    Bootloader_openDma();

    UNITY_BEGIN();

    RUN_TEST(TestSbl_singleCoreImageEmmcBoot, 8000, NULL);
    RUN_TEST(TestSbl_singleCoreImageOspiBoot, 8000, NULL);
    RUN_TEST(TestSbl_singleCoreImageSdBoot,   8000, NULL);

    Bootloader_closeDma();
    UNITY_END();
}

void TestSbl_singleCoreImageEmmcBoot(void *args)
{
    int32_t status = SystemP_SUCCESS;
    DebugP_log("Starting TestSbl_singleCoreImageEmmcBoot test...\r\n");   
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    Bootloader_BootImageInfo bootImageInfoMCU;
    Bootloader_Params bootParamsMCU;
    Bootloader_Handle bootHandleMCU = NULL;

    Bootloader_Params_init(&bootParamsMCU);
    Bootloader_BootImageInfo_init(&bootImageInfoMCU);

    bootHandleMCU = Bootloader_open(CONFIG_BOOTLOADER_EMMC_MCU, &bootParamsMCU);
    TEST_ASSERT_NOT_NULL(bootHandleMCU);
    
    ((Bootloader_Config *)bootHandleMCU)->scratchMemPtr = gAppimage;
    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandleMCU, &bootImageInfoMCU);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        bootImageInfoMCU.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
        Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);

        status = Bootloader_loadCpu(bootHandleMCU, &(bootImageInfoMCU.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
    Bootloader_profileAddProfilePoint("App_loadMCUImage");
    
      if (!Bootloader_socIsMCUResetIsoEnabled())
    {
        status = Bootloader_runCpu(bootHandleMCU, &(bootImageInfoMCU.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleMCU));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_EMMC, MMCSD_getInputClk(gMmcsdHandle[CONFIG_MMCSD_SBL]));

    Bootloader_close(bootHandleMCU);
}

void TestSbl_singleCoreImageOspiBoot(void *args)
{
    int32_t status = SystemP_SUCCESS;
    DebugP_log("Starting TestSbl_singleCoreImageOspiBoot test... \r\n");
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    Bootloader_BootImageInfo bootImageInfoDSP;
    Bootloader_Params bootParamsDSP;
    Bootloader_Handle bootHandleDSP = NULL;

    Bootloader_Params_init(&bootParamsDSP);
    Bootloader_BootImageInfo_init(&bootImageInfoDSP);
    
    bootHandleDSP = Bootloader_open(CONFIG_BOOTLOADER_FLASH_DSP, &bootParamsDSP);
    TEST_ASSERT_NOT_NULL(bootHandleDSP);

    ((Bootloader_Config *)bootHandleDSP)->scratchMemPtr = gAppimage;

    status = Bootloader_parseMultiCoreAppImage(bootHandleDSP, &bootImageInfoDSP);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    bootImageInfoDSP.cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
    Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);

    status = Bootloader_loadCpu(bootHandleDSP, &(bootImageInfoDSP.cpuInfo[CSL_CORE_ID_C75SS0_0]));
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
     
    Bootloader_profileAddProfilePoint("App_loadDSPImage");

    status = Bootloader_runCpu(bootHandleDSP, &(bootImageInfoDSP.cpuInfo[CSL_CORE_ID_C75SS0_0]));
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDSP));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI0]));
    
    Bootloader_close(bootHandleDSP);
}

void TestSbl_singleCoreImageSdBoot(void *args)
{
    int32_t status = SystemP_SUCCESS;
    DebugP_log("Starting TestSbl_singleCoreImageSdBoot test... \r\n");
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    Bootloader_BootImageInfo bootImageInfoA53;
    Bootloader_Params bootParamsA53;
    Bootloader_Handle bootHandleA53 = NULL;

    Bootloader_Params_init(&bootParamsA53);
    Bootloader_BootImageInfo_init(&bootImageInfoA53);
    bootParamsA53.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;
    
    status = TestSbl_openSdImage(BOOTLOADER_SD_A53_APPIMAGE_FILENAME); 
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    bootHandleA53 = Bootloader_open(CONFIG_BOOTLOADER_SD_A53, &bootParamsA53);

    Bootloader_Config *bootConfigA53;
    bootConfigA53 = (Bootloader_Config *)bootHandleA53;
    bootConfigA53->coresPresentMap = 0;
    status = Bootloader_parseMultiCoreAppImage(bootHandleA53, &bootImageInfoA53);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    status = Bootloader_isCorePresent(bootHandleA53, CSL_CORE_ID_A53SS0_0);
    TEST_ASSERT_EQUAL(status, 1);

    bootImageInfoA53.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
    status = Bootloader_loadCpu(bootHandleA53, &(bootImageInfoA53.cpuInfo[CSL_CORE_ID_A53SS0_0]));

    Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
    Bootloader_profileAddProfilePoint("App_loadImages(CSL_CORE_ID_A53SS0_0)");

    status = Bootloader_runCpu(bootHandleA53, &(bootImageInfoA53.cpuInfo[CSL_CORE_ID_A53SS0_0]));
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleA53));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0);

    Bootloader_close(bootHandleA53);
}

int TestSbl_openSdImage(char* imageName)
{
    int status = SystemP_SUCCESS;
    FF_FILE *appFp = ff_fopen(imageName, "rb");

    if(appFp == NULL)
    {
        status =  SystemP_FAILURE;
    }
    else
    {
        /* Check file size */
        uint32_t fileSize = ff_filelength(appFp);

        if(fileSize >= BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
        {
            status = SystemP_FAILURE;
            DebugP_log("Appimage size exceeded limit !!\r\n");
        }
        else
        {
            memset(gAppImageBuf, 0x0, sizeof(gAppImageBuf));
            ff_fread(gAppImageBuf, fileSize, 1, appFp);
        }

        ff_fclose(appFp);
    }
    return status;
}

