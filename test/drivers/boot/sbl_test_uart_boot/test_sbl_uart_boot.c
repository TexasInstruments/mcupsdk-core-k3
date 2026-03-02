#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/bootloader.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/bootloader/bootloader_xmodem.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader/bootloader_profile.h>

#define BOOTLOADER_UART_STATUS_LOAD_SUCCESS           (0x53554343) 
#define BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL          (0x4641494C) 
#define BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED (0x45584344) 

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS          (5)
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH  (4) 
#if defined(SOC_AM275X)
/* AM275x uses MCELF format.  The full MCELF file is received via XMODEM
 * and then parsed + loaded from memory. */
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x100000U)
#define TEST_SBL_SCRATCH_BUF_SIZE        (0x1000U)
static uint8_t gScratchBuf[TEST_SBL_SCRATCH_BUF_SIZE] __attribute__((aligned(128), section(".bss.app")));
#else
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x1900000)
#endif

uint8_t gAppimage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__ ((section (".bss.app"), aligned (128)));
uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] = {0x45,0x4F,0x46,0x54};

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];
uint8_t socCpuCores[CSL_CORE_ID_MAX]    = {0};

void TestSbl_uartBoot(void *args);
void TestSbl_uartSmpBoot(void *args);

int32_t TestSbl_loadCpu();
int32_t TestSbl_runCpus();

void setUp(void)
{
    /* Setup function nothing to perform */
}

void tearDown(void)
{
    /* Tear down function nothing to perform */
}

void loop_forever()
{
    volatile uint32_t loop = 1;
    DebugP_log("Inside the loop...\r\n");
    while(loop)
        ;
}

void test_main(void * args)
{

    UNITY_BEGIN();

    //RUN_TEST(TestSbl_uartBoot,    8000, NULL);
    RUN_TEST(TestSbl_uartSmpBoot, 8000, NULL);

    UNITY_END();
}

void TestSbl_uartBoot(void *args)
{
    int32_t status;
    bool bEndOfTransfer = false;
    uint32_t fileSize;
    uint32_t response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;

    Bootloader_profileReset();

    while(bEndOfTransfer == false)
    {
        status = Bootloader_xmodemReceive(CONFIG_UART0, gAppimage, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        if(memcmp(gAppimage, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
        {
            bEndOfTransfer = true;
            DebugP_log("Starting TestSbl_uartBoot: All images received, running CPUs...\r\n");
            Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_UART, 0);
            Bootloader_profileAddProfilePoint("Running CPUs");
            ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);
            status = TestSbl_runCpus();
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_profilePrintProfileLog();
            DebugP_log("TestSbl_uartBoot: All CPUs booted and IPC sync done successfully!\r\n");
        }
        else
        {
            if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
            {
                status = SystemP_FAILURE;
                response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;
                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }

            if(SystemP_SUCCESS == status)
            {
                status = TestSbl_loadCpu();

                if(status != SystemP_SUCCESS)
                {
                    response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                }
                else
                {
                    Bootloader_profileAddProfilePoint("UART Image Load");
                }
                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }
}

void TestSbl_uartSmpBoot(void *args)
{
    int32_t status;
    bool bEndOfTransfer = false;
    uint32_t fileSize;
    uint32_t response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;

    Bootloader_profileReset();

    while(bEndOfTransfer == false)
    {
        status = Bootloader_xmodemReceive(CONFIG_UART0, gAppimage, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        if(memcmp(gAppimage, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
        {
            bEndOfTransfer = true;
            DebugP_log("Starting TestSbl_uartSmpBoot: All images received, running CPUs...\r\n");
            Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_UART, 0);
            Bootloader_profileAddProfilePoint("Running CPUs");
            ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);
            status = TestSbl_runCpus();
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_profilePrintProfileLog();
            DebugP_log("TestSbl_uartSmpBoot: All CPUs booted and IPC sync done successfully!\r\n");
        }
        else
        {
            if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
            {
                status = SystemP_FAILURE;
                response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;
                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }

            if(SystemP_SUCCESS == status)
            {
                status = TestSbl_loadCpu();

                if(status != SystemP_SUCCESS)
                {
                    response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                }
                else
                {
                    Bootloader_profileAddProfilePoint("UART Image Load");
                }
                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }
}

int32_t TestSbl_runCpus()
{
    int32_t status = SystemP_FAILURE;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        DebugP_log("CPU %d: Booting...\r\n", cpuId);
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
            DebugP_log("CPU %d: Image loaded, running CPU...\r\n", cpuId);
#if !defined(SOC_AM275X)
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
                {
                    DebugP_log("CPU %d: Running CPU...\r\n", cpuId);
                    status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);
                    DebugP_log("CPU %d: Bootloader_runCpu status = %d\r\n", cpuId, status);
                }
        }
    }

    /* Wait for sync from each loaded core using IPC */
    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
#if !defined(SOC_AM275X)
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", cpuId);
                status = IpcNotify_waitSync(cpuId, 30);
                DebugP_log("CPU %d: IPC sync status = %d\r\n", cpuId, status);
            }
        }
    }

    /* Reset the CPUs to the original state */
    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
            status = Bootloader_socCpuRequest(bootCpuInfo[cpuId].cpuId);
            Bootloader_socCpuPowerOff(bootCpuInfo[cpuId].cpuId);
            status = Bootloader_socCpuRelease(bootCpuInfo[cpuId].cpuId);
            DebugP_log("CPU %d: Reset complete\r\n", cpuId);
        }
    }

    Bootloader_close(bootHandle);
    return status;
}

int32_t TestSbl_loadCpu()
{
    int32_t status = SystemP_SUCCESS;

    /* The test exeecutable to be booted is ipc_rpmsg
     * system project for AM62DX which has the following
     * cores enabled
     */
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootParams.bufIoTempBuf     = gAppimage;
    bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
    bootParams.bufIoDeviceIndex = CONFIG_UART0;
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppimage;

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
    if(bootHandle != NULL)
    {
#if defined(SOC_AM275X)
        /*
         * AM275x uses MCELF format.  The full MCELF file was received via
         * XMODEM into gAppimage.  Override bootMedia to EMMC so that
         * Bootloader_parseAndLoadMultiCoreELF takes the SD/EMMC auth code
         * path (seek+read+authUpdate).  The underlying imgReadFxn/imgSeekFxn
         * still read from the memory buffer.
         */
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)bootHandle;
            bootConfig->coresPresentMap = 0;
            bootConfig->bootMedia       = BOOTLOADER_MEDIA_EMMC;
            bootConfig->scratchMemPtr   = gScratchBuf;
        }

        status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Bootloader_parseAndLoadMultiCoreELF failed, status = %d\r\n", status);
            return status;
        }

        /* Record which cores were loaded so TestSbl_runCpus can run them */
        {
            Bootloader_Config *config = (Bootloader_Config *)bootHandle;
            uint8_t cpuId;
            for(cpuId = 0U; cpuId < CSL_CORE_ID_MAX; cpuId++)
            {
                if(config->coresPresentMap & ((uint32_t)1U << cpuId))
                {
                    socCpuCores[cpuId] = BOOTLOADER_IMAGE_LOADED;
                    bootCpuInfo[cpuId] = bootImageInfo.cpuInfo[cpuId];
                    Bootloader_profileAddCore(cpuId);
                }
            }
        }
#else
        status = Bootloader_parseMultiCoreAppImage(bootHandle, &bootImageInfo);

        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Bootloader_parseMultiCoreAppImage failed with status = %d\r\n", status);
            return status;
        }

        /* Load CPUs */
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
            }
        }
        if(((status == SystemP_SUCCESS) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0))))
        {
            if(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].smpEnable != true)
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));
                socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            }
            else
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_1].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_1);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_1].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_1);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));

                socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
                socCpuCores[CSL_CORE_ID_A53SS0_1] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_1] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_1];
                socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0];
                socCpuCores[CSL_CORE_ID_A53SS1_1] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS1_1] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_1];
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_1);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_1);

            }
        }
        if(((status == SystemP_SUCCESS) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS0_0))))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]));
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0];
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
        }
#endif
        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle));
    }
    return status;
}

