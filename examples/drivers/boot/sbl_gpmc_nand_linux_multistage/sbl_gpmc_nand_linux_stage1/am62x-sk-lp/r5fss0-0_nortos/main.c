/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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

#include <stdlib.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>

#include <drivers/soc.h>
#include <board/flash.h>
#include <board/flash/flash_nand_gpmc.h>
#include <drivers/gpmc.h>
#include "ti_board_config.h"
#include <drivers/bootloader.h>


#define SOC_MODULES_END     (0xFFFFFFFFu)

typedef struct {

    uint32_t moduleId;
    uint32_t clkId;
    uint32_t clkRate;

} SOC_ModuleClockFrequency;

static uint32_t gSocModules[] = {
    TISCI_DEV_GPMC0,
    TISCI_DEV_ELM0,

    SOC_MODULES_END,
};

static SOC_ModuleClockFrequency gSocModulesClockFrequency[] = {
    { TISCI_DEV_GPMC0, TISCI_DEV_GPMC0_FUNC_CLK, 133333333 },

    { SOC_MODULES_END, SOC_MODULES_END, SOC_MODULES_END },
};

static void Module_clockEnableGPMC(void)
{
    int32_t status;
    uint32_t i = 0;

    while(gSocModules[i]!=SOC_MODULES_END)
    {
        status = SOC_moduleClockEnable(gSocModules[i], 1);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

static void Module_clockSetFrequencyGPMC(void)
{
    int32_t status;
    uint32_t i = 0;

    while(gSocModulesClockFrequency[i].moduleId!=SOC_MODULES_END)
    {
        status = SOC_moduleSetClockFrequency(
                    gSocModulesClockFrequency[i].moduleId,
                    gSocModulesClockFrequency[i].clkId,
                    gSocModulesClockFrequency[i].clkRate
                    );
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

static Pinmux_PerCfg_t gPinMuxMainDomainCfg[] = {
            /* MMC0 pin config */
    /* MMC0_CLK -> MMC0_CLK (AB1) */
    {
        PIN_GPMC0_AD0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_CMD -> MMC0_CMD (Y3) */
    {
        PIN_GPMC0_AD1,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT0 -> MMC0_DAT0 (AA2) */
    {
        PIN_GPMC0_AD2,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT1 -> MMC0_DAT1 (AA1) */
    {
        PIN_GPMC0_AD3,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT2 -> MMC0_DAT2 (AA3) */
    {
        PIN_GPMC0_AD4,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT3 -> MMC0_DAT3 (Y4) */
    {
        PIN_GPMC0_AD5,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT4 -> MMC0_DAT4 (AB2) */
    {
        PIN_GPMC0_AD6,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT5 -> MMC0_DAT5 (AC1) */
    {
        PIN_GPMC0_AD7,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT6 -> MMC0_DAT6 (AD2) */
    {
        PIN_GPMC0_ADVN_ALE,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },
    /* MMC0_DAT7 -> MMC0_DAT7 (AC2) */
    {
        PIN_GPMC0_OEN_REN,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },
        /* MMC0_DAT7 -> MMC0_DAT7 (AC2) */
    {
        PIN_GPMC0_WEN,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },
        /* MMC0_DAT7 -> MMC0_DAT7 (AC2) */
    {
        PIN_GPMC0_BE0N_CLE,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },
    {
        PIN_GPMC0_CSN0,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },
    {
        PIN_GPMC0_WAIT0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },

    {PINMUX_END, PINMUX_END}
};

static Pinmux_PerCfg_t gPinMuxMcuDomainCfg[] = {

    {PINMUX_END, PINMUX_END}
};

/* FLASH Instance Macros */
#define CONFIG_FLASH0 (0U)
#define CONFIG_FLASH_NUM_INSTANCES (1U)
#define CONFIG_GPMC0 (0U)
#define CONFIG_GPMC_NUM_INSTANCES (1U)

GPMC_Handle gGpmcHandle[CONFIG_GPMC_NUM_INSTANCES];

/* GPMC Driver Parameters */
GPMC_Params gGpmcParams[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        .gpmcDmaChIndex         =   -1,
        .devType                =   CSL_GPMC_CONFIG1_DEVICETYPE_NANDLIKE,
        .devSize                =   CSL_GPMC_CONFIG1_DEVICESIZE_EIGHTBITS,
        .chipSel                =   GPMC_CHIP_SELECT_0,
        .intrEnable             =   FALSE,
        .dmaEnable              =   FALSE,
        .transferMode           =   GPMC_TRANSFER_MODE_BLOCKING,
        .transferCallBckFunc    =   NULL,
    },
};


static GPMC_HwAttrs gGpmcAttrs[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        .gpmcBaseAddr       =   CSL_GPMC0_CFG_BASE,
        .dataBaseAddr       =   CSL_GPMC0_DATA_BASE,
        .elmBaseAddr        =   CSL_ELM0_BASE,
        .inputClkFreq       =   133333333,
        .intrNum            =   CSLR_R5FSS0_CORE0_INTR_GPMC0_GPMC_SINTERRUPT_0,
        .intrPriority       =   4,
        .clkDivider         =   CSL_GPMC_CONFIG1_GPMCFCLKDIVIDER_DIVBY1,
        .addrDataMux        =   CSL_GPMC_CONFIG1_MUXADDDATA_NONMUX,
        .timeLatency        =   CSL_GPMC_CONFIG1_TIMEPARAGRANULARITY_X2,
        .chipSelBaseAddr    =   0x10000000U,
        .chipSelAddrSize    =   GPMC_CS_MASK_ADDR_SIZE_16MB,
        .waitPinNum         =   CSL_GPMC_CONFIG1_WAITPINSELECT_W0,
        .waitPinPol         =   CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL,
        .timingParams       =
        {
            .csOnTime               =   GPMC_NAND_CS_ON_TIME,
            .csRdOffTime            =   GMPC_NAND_CS_RD_OFF_TIME,
            .csWrOffTime            =   GMPC_NAND_CS_WR_OFF_TIME,
            .advOnTime              =   GMPC_NAND_ADV_ON_TIME,
            .advRdOffTime           =   GMPC_NAND_ADV_RD_OFF_TIME,
            .advWrOffTime           =   GMPC_NAND_ADV_WR_OFF_TIME,
            .advAadMuxOnTime        =   GMPC_NAND_ADV_AADMUX_ON_TIME,
            .advAadMuxRdOffTime     =   GMPC_NAND_ADV_AADMUX_RD_OFF_TIME,
            .advAadMuxWrOffTime     =   GMPC_NAND_ADV_AADMUX_WR_OFF_TIME,
            .weOnTtime              =   GMPC_NAND_WE_ON_TIME,
            .weOffTime              =   GMPC_NAND_WE_OFF_TIME,
            .oeOnTime               =   GMPC_NAND_OE_ON_TIME,
            .oeOffTime              =   GMPC_NAND_OE_OFF_TIME,
            .oeAadMuxOnTime         =   GMPC_NAND_OE_AADMUX_ON_TIME,
            .oeAadMuxOffTime        =   GMPC_NAND_OE_AADMUX_OFF_TIME,
            .pageBurstAccess        =   GPMC_NAND_PAGEBURST_ACCESS_TIME,
            .rdAccessTime           =   GMPC_NAND_RD_ACCESS_TIME,
            .wrAcessTime            =   GMPC_NAND_WR_ACCESS_TIME,
            .rdCycleTime            =   GMPC_NAND_RD_CYCLE_TIME,
            .wrCycleTime            =   GMPC_NAND_WR_CYCLE_TIME,
            .wrDataOnMuxBusTime     =   GMPC_NAND_ADMUX_DATA_VALID,
            .cycle2CycleDelay       =   GMPC_NAND_C2C_DELAY,
            .cycleDelaySameChipSel  =   CSL_GPMC_CONFIG6_CYCLE2CYCLESAMECSEN_C2CDELAY,
            .cycleDelayDiffChipSel  =   CSL_GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY,
            .busTurnAroundTime      =   GMPC_NAND_BRST_TAROUND_TIME,
        },
        .eccAlgo            =   GPMC_NAND_ECC_ALGO_BCH_8BIT,
        .readType           =   CSL_GPMC_CONFIG1_READTYPE_RDASYNC,
        .csExDelay          =   CSL_GPMC_CONFIG2_CSEXTRADELAY_NOTDELAYED,
        .accessType         =   CSL_GPMC_CONFIG1_READMULTIPLE_RDSINGLE,
    },
};

/* GPMC objects - initialized by the driver */
static GPMC_Object gGpmcObjects[CONFIG_GPMC_NUM_INSTANCES];
/* GPMC driver configuration */
GPMC_Config gGpmcConfig[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        &gGpmcAttrs[CONFIG_GPMC0],
        &gGpmcObjects[CONFIG_GPMC0],
    },
};

uint32_t gGpmcConfigNum = CONFIG_GPMC_NUM_INSTANCES;

/* BOOTLOADER Instance Macros */
#define CONFIG_BOOTLOADER_FLASH_MCU (0U)
#define CONFIG_BOOTLOADER_FLASH_SBL (1U)
#define CONFIG_BOOTLOADER_NUM_INSTANCES (2U)

/* Bootloader boot media specific arguments */
Bootloader_FlashArgs gBootloader0Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x100000,
};
Bootloader_FlashArgs gBootloader1Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x80000,
};

/* Configuration option for lockstep or standalone */
void* operatingMode = NULL;


/* Bootloader driver configuration */
Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES] =
{
    {
        &gBootloaderFlashFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_FLASH,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
    },
    {
        &gBootloaderFlashFxns,
        &gBootloader1Args,
        BOOTLOADER_MEDIA_FLASH,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
    },
};

uint32_t gBootloaderConfigNum = CONFIG_BOOTLOADER_NUM_INSTANCES;


uint8_t gNandReadData[4096] __attribute__ ((aligned (4))) ; //todo: this is an issue
/*
 * FLASH
 */
/* FLASH Object - initialized during Flash_open() */
Flash_NandGpmcObject gFlashObject_MT29F8G08ADAFAH4 =
{
    NULL,
    {
        .deviceType = CSL_GPMC_CONFIG1_DEVICETYPE_NANDLIKE,
        .busWidth   = CSL_GPMC_CONFIG1_DEVICESIZE_EIGHTBITS,
        .bbOffeset  = NAND_BAD_BLK_OFFSET,
        .eccAlgo    = GPMC_NAND_ECC_ALGO_BCH_8BIT,
    },
    .memScratch = gNandReadData,
};

/* FLASH Driver handles - opened during Board_flashOpen() */
Flash_Handle gFlashHandle[CONFIG_FLASH_NUM_INSTANCES];

/* FLASH Config */
Flash_Config gFlashConfig[CONFIG_FLASH_NUM_INSTANCES] =
{
    {
        .attrs = &gFlashNandGpmcAttrs_MT29F8G08ADAFAH4,
        .fxns = &gFlashNandGpmcFxns,
        .devConfig = (void *)&gFlashNandGpmcDeviceDefines_MT29F8G08ADAFAH4,
        .object = (void *)&gFlashObject_MT29F8G08ADAFAH4,
    },
};
uint32_t gFlashConfigNum = CONFIG_FLASH_NUM_INSTANCES;

extern Flash_Handle gFlashHandle[CONFIG_FLASH_NUM_INSTANCES];

void Drivers_gpmcClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        if(gGpmcHandle[instCnt] != NULL)
        {
            GPMC_close(gGpmcHandle[instCnt]);
            gGpmcHandle[instCnt] = NULL;
        }
    }

    return;
}


void Drivers_gpmcOpen(void)
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        gGpmcHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        gGpmcHandle[instCnt] = GPMC_open(instCnt, &gGpmcParams[instCnt]);
        if(NULL == gGpmcHandle[instCnt])
        {
            DebugP_logError("GPMC open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Drivers_gpmcClose();   /* Exit gracefully */
    }

    return;
}



void Board_flashClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {
        if(gFlashHandle[instCnt] != NULL)
        {
            Flash_close(gFlashHandle[instCnt]);
            gFlashHandle[instCnt] = NULL;
        }
    }
    return;
}

int32_t Board_flashOpen()
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    /* Set the peripheral instance to use in the under lying flash implementation */
    gFlashConfig[CONFIG_FLASH0].attrs->driverInstance = CONFIG_GPMC0;

    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {
        gFlashHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Set the underlying driver instance to the FLASH config */
    gFlashNandGpmcAttrs_MT29F8G08ADAFAH4.driverInstance = CONFIG_GPMC0;

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {

        gFlashHandle[instCnt] = Flash_open(instCnt, NULL);
        if(NULL == gFlashHandle[instCnt])
        {
            DebugP_logError("FLASH open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Board_flashClose();   /* Exit gracefully */
    }
    return status;
}


/*
 * Pinmux
 */
static void Pinmux_initGPMC(void)
{
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
    Pinmux_config(gPinMuxMcuDomainCfg, PINMUX_DOMAIN_ID_MCU);
}




/*  In this sample bootloader, we load appimages for RTO/Baremetal and Linux at different offset
    i.e the appimage for Linux (for A53) and RTOS/Baremetal (for M4) is flashed at different offset in flash

    Here at one flash offset, there is a multi-core .appimage that holds RPRC for M4, another appimage for selfcore
    flashed at another offset and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (for M4 cores) flash at offset 0x100000
    Linux appimage (for A53) flash at offset 0xC00000
*/

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

            /* Load CPUs */
            if(status == SystemP_SUCCESS)
            {
                bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_M4FSS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_M4FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }

    return status;
}

int32_t App_loadSelfcoreImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        if(status == SystemP_SUCCESS)
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }
    }

    return status;
}

int32_t App_loadLinuxImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
		status = Bootloader_parseAndLoadLinuxAppImage(bootHandle, bootImageInfo);

		if(status == SystemP_SUCCESS)
		{
			bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
		}
	}

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;
    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
	    status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));
    }
    else
    {
        status = SystemP_SUCCESS;
    }

	return status;
}

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}

int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    //Bootloader_socOpenFirewalls();


    System_init();
    /* GPMC related initialisations */
    Module_clockEnableGPMC();
    Module_clockSetFrequencyGPMC();
    Pinmux_initGPMC();
    GPMC_init();
    Bootloader_profileAddProfilePoint("System_init");

    Drivers_open();
    Drivers_gpmcOpen();
    Bootloader_profileAddProfilePoint("Drivers_open");

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    status = Board_flashOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo bootImageInfoDM;
		Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsDM);

		Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER_FLASH_MCU, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_SBL, &bootParamsDM);

        if(bootHandle != NULL)
        {
			status = App_loadImages(bootHandle, &bootImageInfo);
            Bootloader_profileAddProfilePoint("App_loadImages");
        }

        if(SystemP_SUCCESS == status)
		{
            if(bootHandleDM != NULL)
            {
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM) + \
                                            Bootloader_getMulticoreImageSize(bootHandle));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, GPMC_getInputClk(gGpmcHandle[CONFIG_GPMC0]));

		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting MCU-m4f and 2nd stage bootloader\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
		}

        if(SystemP_SUCCESS == status)
		{
			status = App_runCpus(bootHandle, &bootImageInfo);
		}

        Bootloader_close(bootHandle);
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    Bootloader_JumpSelfCpu();

    Board_flashClose();
    Drivers_gpmcClose();
    GPMC_deinit();

    Drivers_close();
    System_deinit();

    return 0;
}
