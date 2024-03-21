/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
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

#include <string.h>
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_priv.h>
#include <drivers/bootloader/soc/bootloader_soc.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/soc.h>

#define BOOTLOADER_HSM_M4F_SRAM0_0_BASE        (0x00000000)
#define BOOTLOADER_HSM_M4F_SRAM1_BASE          (0x00030000)

#define BOOTLOADER_SYSFW_MAX_SIZE (0x42000U)

#define BOOTLOADER_SYS_STATUS_REG              (0x44234100U)
#define BOOTLOADER_SYS_STATUS_DEV_TYPE_MASK    (0x0000000FU)
#define BOOTLOADER_SYS_STATUS_DEV_SUBTYPE_MASK (0x00000F00U)

#define BOOTLOADER_SYS_STATUS_DEV_TYPE_GP      (0x03U)
#define BOOTLOADER_SYS_STATUS_DEV_TYPE_TEST    (0x05U)
#define BOOTLOADER_SYS_STATUS_DEV_SUBTYPE_FS   (0x00000A00U)

Bootloader_resMemSections gResMemSection =
{
    .numSections    = 1,
    .memSection[0].memStart   = 0x43c00000,
    .memSection[0].memEnd     = 0x43c3f000,
};

#undef BOOTLOADER_SOC_ATCM_FILL
#undef BOOTLOADER_SOC_BTCM_FILL

/* we will load a dummy while loop here, when there is nothing to load for A53.
 * This is used with SBL NULL, to init A53, so that we can load and run via CCS without
 * GEL files
 */
#define BOOTLOADER_A53_WHILELOOP_LOAD_ADDR      (0x70000040)

/* list the R5F cluster where this bootloader runs, this is fixed to R5FSS0-0*/
uint32_t gBootloaderSelfCpuList[] = {
    CSL_CORE_ID_R5FSS0_0,
    BOOTLOADER_INVALID_ID,
};

const uint32_t gSOC_r5fVectors[18] =
{
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0xE59FF018,
    0x00000040,
    0x00000040,
    0x00000040,
    0x00000040,
    0x00000040,
    0x00000040,
    0x00000040,
    0x00000040,
    0xE320F003, /* WFI */
    0xEBFFFFFD, /* loop back to WFI */
};

const uint32_t gSOC_a53WhileLoop[2]  =
{
    0xD503207F, /* WFI */
    0x17FFFFFF, /* loop back to WFI */
};

Bootloader_CoreBootInfo gCoreBootInfo[] =
{
    {
        .tisciProcId    = SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0,
        .tisciDevId     = TISCI_DEV_MCU_R5FSS0_CORE0,
        .tisciClockId   = TISCI_DEV_MCU_R5FSS0_CORE0_CPU0_CLK,
        .defaultClockHz = (uint32_t)(800*1000000),
        .coreName       = "mcu-r5f",
    },

    {
        .tisciProcId    = SCICLIENT_PROC_ID_R5FSS0_CORE0,
        .tisciDevId     = TISCI_DEV_WKUP_R5FSS0_CORE0,
        .tisciClockId   = TISCI_DEV_WKUP_R5FSS0_CORE0_CPU_CLK,
        .defaultClockHz = (uint32_t)(800*1000000),
        .coreName       = "r5f0-0",
    },

    {
        .tisciProcId    = SCICLIENT_PROC_ID_A53SS0_CORE_0,
        .tisciDevId     = TISCI_DEV_A53SS0_CORE_0,
        .tisciClockId   = TISCI_DEV_A53SS0_CORE_0_A53_CORE0_ARM_CLK_CLK,
        .defaultClockHz = (uint32_t)(1400*1000000),
        .coreName       = "a530-0",
    },

    {
        .tisciProcId    = SCICLIENT_PROC_ID_A53SS0_CORE_1,
        .tisciDevId     = TISCI_DEV_A53SS0_CORE_1,
        .tisciClockId   = TISCI_DEV_A53SS0_CORE_1_A53_CORE1_ARM_CLK_CLK,
        .defaultClockHz = (uint32_t)(1400*1000000),
        .coreName       = "a530-1",
    },

    {
        .tisciProcId    = SCICLIENT_PROC_ID_A53SS0_CORE_2,
        .tisciDevId     = TISCI_DEV_A53SS0_CORE_2,
        .tisciClockId   = TISCI_DEV_A53SS0_CORE_2_A53_CORE2_ARM_CLK_CLK,
        .defaultClockHz = (uint32_t)(1400*1000000),
        .coreName       = "a531-0",
    },

    {
        .tisciProcId    = SCICLIENT_PROC_ID_A53SS0_CORE_3,
        .tisciDevId     = TISCI_DEV_A53SS0_CORE_3,
        .tisciClockId   = TISCI_DEV_A53SS0_CORE_3_A53_CORE3_ARM_CLK_CLK,
        .defaultClockHz = (uint32_t)(1400*1000000),
        .coreName       = "a531-1",
    },

    {
    .tisciProcId    = SCICLIENT_PROC_ID_HSM_M4FSS0_CORE0,
    .tisciDevId     = TISCI_DEV_HSM0,
    .tisciClockId   = TISCI_DEV_HSM0_DAP_CLK,
    .defaultClockHz = (uint32_t)(400*1000000),
    .coreName       = "m4f1-0",
    },

    {
    .tisciProcId    = SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0,
    .tisciDevId     = TISCI_DEV_C7X256V0_C7XV_CORE_0,
    .tisciClockId   = TISCI_DEV_C7X256V0_C7XV_CORE_0_C7XV_CLK,
    .defaultClockHz = (uint32_t)(1000*1000000),
    .coreName       = "c7x0-0",
    },
};

Bootloader_CoreAddrTranslateInfo gAddrTranslateInfo[] =
{
    /* CSL_CORE_ID_MCU_R5FSS0_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
        {
            {
                .cpuLocalAddr = CSL_MCU_R5FSS0_ATCM_BASE,
                .socAddr      = CSL_MCU_R5FSS0_CORE0_ATCM_BASE,
                .regionSize   = CSL_MCU_R5FSS0_CORE0_ATCM_SIZE,
            },
            {
                .cpuLocalAddr = CSL_MCU_R5FSS0_BTCM_BASE,
                .socAddr      = CSL_MCU_R5FSS0_CORE0_BTCM_BASE,
                .regionSize   = CSL_MCU_R5FSS0_CORE0_BTCM_SIZE,
            },
        },
    },

    /* CSL_CORE_ID_R5FSS0_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
        {
            {
                .cpuLocalAddr = CSL_WKUP_R5FSS0_ATCM_BASE,
                .socAddr      = CSL_WKUP_R5FSS0_ATCM_BASE,
                .regionSize   = CSL_WKUP_R5FSS0_ATCM_SIZE,
            },
            {
                .cpuLocalAddr = CSL_WKUP_R5FSS0_BTCM_BASE,
                .socAddr      = CSL_WKUP_R5FSS0_BTCM_BASE,
                .regionSize   = CSL_WKUP_R5FSS0_BTCM_SIZE,
            },
        },
    },

    /* CSL_CORE_ID_A53SS0_0 */
    {
        .numRegions = 0,
    },
    /* CSL_CORE_ID_A53SS0_1 */
    {
        .numRegions = 0,
    },
    /* CSL_CORE_ID_A53SS1_0 */
    {
        .numRegions = 0,
    },
    /* CSL_CORE_ID_A53SS1_0 */
    {
        .numRegions = 0,
    },

    /* CSL_CORE_ID_HSM_M4FSS0_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
        {
            {
                .cpuLocalAddr = BOOTLOADER_HSM_M4F_SRAM0_0_BASE,
                .socAddr      = CSL_SMS0_HSM_SRAM0_0_BASE,
                .regionSize   = CSL_SMS0_HSM_SRAM0_0_SIZE + CSL_SMS0_HSM_SRAM0_1_SIZE,
            },
            {
                .cpuLocalAddr = BOOTLOADER_HSM_M4F_SRAM1_BASE,
                .socAddr      = CSL_SMS0_HSM_SRAM1_BASE,
                .regionSize   = CSL_SMS0_HSM_SRAM1_SIZE,
            },
        },
    },

    /* CSL_CORE_ID_C75SS0_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
        {
            {
                .cpuLocalAddr = CSL_C7X256V0_UMC_MEM_MAIN_BASE,
                .socAddr      = CSL_C7X256V0_UMC_MEM_MAIN_BASE,
                .regionSize   = CSL_C7X256V0_UMC_MEM_MAIN_SIZE,
            },
            {
                .cpuLocalAddr = CSL_C7X256V0_UMC_MEM_AUX_BASE,
                .socAddr      = CSL_C7X256V0_UMC_MEM_AUX_BASE,
                .regionSize   = CSL_C7X256V0_UMC_MEM_AUX_SIZE,
            },
        },
    },
};

Bootloader_SelfCoreJump selfcoreEntry = NULL;


extern int32_t Sciclient_triggerSecHandover(void);
extern int32_t Sciclient_waitForBootNotification(void);

static int32_t Bootloader_socOpenFirewallRegion(uint16_t fwl, uint16_t region, uint32_t control, uint64_t startAddr, uint64_t endAddr)
{
    int32_t status = SystemP_FAILURE;

    const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
    {
        .fwl_id = fwl,
        .region = region,
        .n_permission_regs = 3,
        /*
         * The firewall control register layout is
         *  ---------------------------------------------------------------------------
         * |  31:10   |      9     |     8      |     7:5    |      4      |   3:0     |
         *  ---------------------------------------------------------------------------
         * | Reserved | Cache Mode | Background |  Reserved  | Lock Config |  Enable   |
         *  ---------------------------------------------------------------------------
         *
         * Enable = 0xA implies firewall is enabled. Any other value means not enabled
         *
         */
        .control = control,
        /*
            * The firewall permission register layout is
            *  ---------------------------------------------------------------------------
            * |  31:24   |    23:16   |  15:12     |   11:8     |   7:4      |   3:0      |
            *  ---------------------------------------------------------------------------
            * | Reserved |   Priv ID  | NSUSR-DCRW | NSPRI-DCRW | SUSER-DCRW | SPRIV-DCRW |
            *  ---------------------------------------------------------------------------
            *
            * PRIV_ID = 0xC3 implies all.
            * In each of the 4 nibbles from 15:0 the 4 bits means Debug, Cache, Read, Write Access for
            * Non-secure user, Non-secure Priv, Secure user, Secure Priv respectively. To enable all access
            * bits for all users, we set each of these nibbles to 0b1111 = 0xF. So 15:0 becomes 0xFFFF
            *
            */
        .permissions[0] = 0xC3FFFF,
        .permissions[1] = 0xC3FFFF,
        .permissions[2] = 0xC3FFFF,
        .start_address  = startAddr,
        .end_address    = endAddr,
    };
    struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = { 0 };

    status = Sciclient_firewallSetRegion(&fwl_set_req, &fwl_set_resp, SystemP_TIMEOUT);

    return status;
}

uint32_t Bootloader_socRprcToCslCoreId(uint32_t rprcCoreId)
{
    uint32_t cslCoreId = CSL_CORE_ID_MAX; //todo: Change core id max for HSM and add entry in CSL
    uint32_t i;

    uint32_t rprcCoreIds[CSL_CORE_ID_MAX] =
    {
        5U, 4U, 0U, 1U, 2U, 3U, 6U, 7U
    };

    if(Bootloader_socIsSmpEnable( rprcCoreId) == true)
    {
        cslCoreId = CSL_CORE_ID_A53SS0_0;
    }
    else
    {
        for(i = 0U; i < CSL_CORE_ID_MAX; i++)
        {
            if(rprcCoreId == rprcCoreIds[i])
            {
                cslCoreId = i;
                break;
            }
        }
    }

    return cslCoreId;
}

bool Bootloader_socIsSmpEnable(uint32_t rprcCoreId)
{
    bool smpEnable = false;
    if(rprcCoreId == FREERTOS_SMP_RPRC_CORE_ID)
    {
        smpEnable = true;
    }

    return smpEnable;
}

uint32_t Bootloader_socGetSciclientCpuProcId(uint32_t cpuId)
{
    uint32_t procId = BOOTLOADER_INVALID_ID;

    if(cpuId < CSL_CORE_ID_MAX)
    {
        procId = gCoreBootInfo[cpuId].tisciProcId;
    }

    return procId;
}

uint32_t Bootloader_socGetSciclientCpuDevId(uint32_t cpuId)
{
    uint32_t devId = BOOTLOADER_INVALID_ID;

    if(cpuId < CSL_CORE_ID_MAX)
    {
        devId = gCoreBootInfo[cpuId].tisciDevId;
    }

    return devId;
}

uint32_t Bootloader_socGetSciclientCpuClkId(uint32_t cpuId)
{
    uint32_t clockId = BOOTLOADER_INVALID_ID;

    if(cpuId < CSL_CORE_ID_MAX)
    {
        clockId = gCoreBootInfo[cpuId].tisciClockId;
    }

    return clockId;
}

uint32_t Bootloader_socCpuGetClkDefault(uint32_t cpuId)
{
    uint32_t defClock = 0U;

    if(cpuId < CSL_CORE_ID_MAX)
    {
        defClock = gCoreBootInfo[cpuId].defaultClockHz;
    }

    return defClock;
}

char* Bootloader_socGetCoreName(uint32_t cpuId)
{
    char *pName = NULL;

    if(cpuId < CSL_CORE_ID_MAX)
    {
        pName = gCoreBootInfo[cpuId].coreName;
    }

    return pName;
}

uint32_t* Bootloader_socGetSelfCpuList(void)
{
    return &gBootloaderSelfCpuList[0];
}

void Bootloader_socGetR5fAtcmAddrAndSize(uint32_t cpuId, uint32_t *addr, uint32_t *size)
{
    *size = CSL_WKUP_R5FSS0_ATCM_SIZE;

    switch(cpuId)
    {
        case CSL_CORE_ID_R5FSS0_0:
            *addr = CSL_WKUP_R5FSS0_CORE0_ATCM_BASE;
            break;
        case CSL_CORE_ID_MCU_R5FSS0_0:
            *addr = CSL_MCU_R5FSS0_CORE0_ATCM_BASE;
            break;
        default:
            *addr = BOOTLOADER_INVALID_ID;
            *size = 0;
            break;
    }
}

void Bootloader_socGetR5fBtcmAddrAndSize(uint32_t cpuId, uint32_t *addr, uint32_t *size)
{
    *size = CSL_WKUP_R5FSS0_BTCM_SIZE;

    switch(cpuId)
    {
        case CSL_CORE_ID_R5FSS0_0:
            *addr = CSL_WKUP_R5FSS0_CORE0_BTCM_BASE;
            break;
        case CSL_CORE_ID_MCU_R5FSS0_0:
            *addr = CSL_MCU_R5FSS0_CORE0_BTCM_BASE;
            break;
        default:
            *addr = BOOTLOADER_INVALID_ID;
            *size = 0;
            break;
    }
}

/* init ATCM and BTCM and load valid reset vectors and wait instruction */
void Bootloader_socInitR5FAtcmBtcm(uint32_t cpuId)
{
    uint32_t addr, size, i;
    volatile uint32_t *pAddr;

    Bootloader_socGetR5fAtcmAddrAndSize(cpuId, &addr, &size);
    if(addr != BOOTLOADER_INVALID_ID && size > 0)
    {
        #ifdef BOOTLOADER_SOC_ATCM_FILL
        pAddr = (volatile uint32_t *)addr;
        for(i=0; i< size/sizeof(uint32_t); i++)
        {
            pAddr[i] = 0xFFFFFFFF;
        }
        #endif
        pAddr = (volatile uint32_t *)addr;
        for(i=0; i< sizeof(gSOC_r5fVectors)/sizeof(uint32_t); i++)
        {
            pAddr[i] = gSOC_r5fVectors[i];
        }
    }
    Bootloader_socGetR5fBtcmAddrAndSize(cpuId, &addr, &size);
    #ifdef BOOTLOADER_SOC_BTCM_FILL
    if(addr != BOOTLOADER_INVALID_ID && size > 0)
    {
        pAddr = (volatile uint32_t *)addr;
        for(i=0; i< size/sizeof(uint32_t); i++)
        {
            pAddr[i] = 0xFFFFFFFF;
        }
    }
    #endif
}

/* init M4 IRAM with valid reset vector and valid wait instruction */
void Bootloader_socInitHSMM4fIram()
{
    uint32_t m4f_iram_base_addr = CSL_SMS0_HSM_SRAM0_0_BASE;

    *(volatile uint32_t *)(m4f_iram_base_addr + 0) = 0x1000; /* stack size */
    *(volatile uint32_t *)(m4f_iram_base_addr + 4) = 0x400 + 1; /* reset vector */
    *(volatile uint32_t *)(m4f_iram_base_addr + 0x400) = 0xBF30BF30; /* WFI instruction */
}

/*init c7x L2SRAM with valid wait instruction*/
void Bootloader_socInitC7xL2Sram()
{
    uint32_t c75_l2sram_base_addr = CSL_C7X256V0_UMC_MEM_MAIN_BASE;

    *(volatile uint32_t *)(c75_l2sram_base_addr + 0) = 0x0000084E;  /* NOP instruction */
    *(volatile uint32_t *)(c75_l2sram_base_addr + 4) = 0x0000009E;  /* Loop back to NOP */
}

int32_t Bootloader_socCpuRequest(uint32_t cpuId)
{
    int32_t status = SystemP_FAILURE;
    uint32_t sciclientCpuProcId;

    sciclientCpuProcId = Bootloader_socGetSciclientCpuProcId(cpuId);
    if(sciclientCpuProcId != BOOTLOADER_INVALID_ID)
    {
        status = Sciclient_procBootRequestProcessor(sciclientCpuProcId, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU request failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }
    return status;
}

int32_t Bootloader_socCpuRelease(uint32_t cpuId)
{
    int32_t status = SystemP_FAILURE;
    uint32_t sciclientCpuProcId;

    sciclientCpuProcId = Bootloader_socGetSciclientCpuProcId(cpuId);
    if(sciclientCpuProcId != BOOTLOADER_INVALID_ID)
    {
        status = Sciclient_procBootReleaseProcessor(sciclientCpuProcId, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU release failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }

    return status;
}

int32_t Bootloader_socCpuSetClock(uint32_t cpuId, uint32_t cpuHz)
{
    int32_t status = SystemP_FAILURE;
    uint32_t sciclientCpuDevId;
    uint32_t sciclientCpuClkId;

    if((cpuId != CSL_CORE_ID_HSM_M4FSS0_0) && (cpuId != CSL_CORE_ID_C75SS0_0))
    {
        sciclientCpuDevId = Bootloader_socGetSciclientCpuDevId(cpuId);
        sciclientCpuClkId = Bootloader_socGetSciclientCpuClkId(cpuId);
        if(sciclientCpuDevId != BOOTLOADER_INVALID_ID && sciclientCpuClkId != BOOTLOADER_INVALID_ID)
        {
            status = Sciclient_pmSetModuleClkFreq(sciclientCpuDevId,
                                                    sciclientCpuClkId,
                                                    cpuHz,
                                                    TISCI_MSG_FLAG_AOP,
                                                    SystemP_WAIT_FOREVER);
            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("CPU clock set for %d Hz failed for %s\r\n", cpuHz, Bootloader_socGetCoreName(cpuId));
            }
        }
    }
    else
    {
        return SystemP_SUCCESS;
    }

    return status;
}

uint64_t Bootloader_socCpuGetClock(uint32_t cpuId)
{
    int32_t status = SystemP_FAILURE;
    uint64_t clkRate = 0;
    uint32_t sciclientCpuDevId;
    uint32_t sciclientCpuClkId;

    if(cpuId != CSL_CORE_ID_HSM_M4FSS0_0)
    {
        sciclientCpuDevId = Bootloader_socGetSciclientCpuDevId(cpuId);
        sciclientCpuClkId = Bootloader_socGetSciclientCpuClkId(cpuId);
        if(sciclientCpuDevId != BOOTLOADER_INVALID_ID && sciclientCpuClkId != BOOTLOADER_INVALID_ID)
        {
            status = Sciclient_pmGetModuleClkFreq(
                        sciclientCpuDevId,
                        sciclientCpuClkId,
                        &clkRate,
                        SystemP_WAIT_FOREVER);

            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("CPU clock get failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
            }
        }
    }
    return clkRate;
}

int32_t Bootloader_socCpuPowerOnResetHSMM4f(uint32_t cpuId, uint32_t initRam)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t sciclientCpuProcId;
    struct tisci_msg_proc_get_status_resp proc_get_status;
    struct tisci_msg_proc_set_config_req  proc_set_config;

    sciclientCpuProcId = Bootloader_socGetSciclientCpuProcId(cpuId);

    if(status == SystemP_SUCCESS)
    {
        status = Sciclient_procBootGetProcessorState(sciclientCpuProcId,
                    &proc_get_status,
                    SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU get state failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }

    if(status == SystemP_SUCCESS)
    {
        status =  Sciclient_procBootSetSequenceCtrl(sciclientCpuProcId,
                            TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_HSM_M4_RESET,
                            0,
                            TISCI_MSG_FLAG_AOP,
                            SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU halt set failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }

    if(status == SystemP_SUCCESS)
    {
        proc_set_config.processor_id = proc_get_status.processor_id;
        proc_set_config.bootvector_lo = 0;
        proc_set_config.bootvector_hi = 0;
        proc_set_config.config_flags_1_set = 0;
        proc_set_config.config_flags_1_clear = 0;

        status = Sciclient_procBootSetProcessorCfg(&proc_set_config, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU set config failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }

    if(status == SystemP_SUCCESS)
    {
        if(initRam)
        {
            /* initialize the RAMs only if requested
             */
            Bootloader_socInitHSMM4fIram();
        }
    }
    return status;
}

/* applicable for all R5F's except the boot R5F cluster */
int32_t Bootloader_socCpuPowerOnResetR5f(uint32_t cpuId, uintptr_t entry_point, uint32_t initRam)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t sciclientCpuProcId, sciclientCpuDevId;
    struct tisci_msg_proc_get_status_resp proc_get_status;
    struct tisci_msg_proc_set_config_req  proc_set_config;

    proc_get_status.processor_id = 0;

    sciclientCpuProcId = Bootloader_socGetSciclientCpuProcId(cpuId);
    sciclientCpuDevId = Bootloader_socGetSciclientCpuDevId(cpuId);

    status = Sciclient_pmSetModuleState(sciclientCpuDevId,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CPU power off failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
    }

    if(status == SystemP_SUCCESS)
    {
        status = Sciclient_procBootGetProcessorState(sciclientCpuProcId,
                    &proc_get_status,
                    SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU get state failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }
    if(status == SystemP_SUCCESS)
    {
        proc_set_config.processor_id = proc_get_status.processor_id;
        proc_set_config.bootvector_lo = entry_point;
        proc_set_config.bootvector_hi = 0;
        proc_set_config.config_flags_1_set = 0;
        proc_set_config.config_flags_1_clear = 0;
        proc_set_config.config_flags_1_set |= TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN;
        proc_set_config.config_flags_1_set |= (TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN |
                                                TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE);

        status = Sciclient_procBootSetProcessorCfg(&proc_set_config, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU set config failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }
    if(status == SystemP_SUCCESS)
    {
        status =  Sciclient_procBootSetSequenceCtrl(sciclientCpuProcId,
                            TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT,
                            0,
                            TISCI_MSG_FLAG_AOP,
                            SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU halt set failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }
    if(status == SystemP_SUCCESS)
    {
        status = Sciclient_pmSetModuleState(sciclientCpuDevId,
                        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                        TISCI_MSG_FLAG_AOP,
                        SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU power on failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
        }
    }
    if(status == SystemP_SUCCESS)
    {
        if(initRam)
        {
            /* initialize the RAMs only if requested
             */
            Bootloader_socInitR5FAtcmBtcm(cpuId);
        }
    }
    return status;
}

int32_t Bootloader_socCpuPowerOnResetA53(uint32_t cpuId)
{
    int32_t status = SystemP_SUCCESS;

    /* nothing to do, we keep A53 powered off since we dont need it powered-on to load code for it */
    status = Sciclient_pmSetModuleState(TISCI_DEV_A53SS0, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0, SystemP_WAIT_FOREVER);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CPU cluster power on failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
    }

    /* copy while(1) loop to load addr and flush it to memory */
    memcpy( (void*)BOOTLOADER_A53_WHILELOOP_LOAD_ADDR, gSOC_a53WhileLoop, sizeof(gSOC_a53WhileLoop));
    CacheP_wbInv((void*)BOOTLOADER_A53_WHILELOOP_LOAD_ADDR, sizeof(gSOC_a53WhileLoop), CacheP_TYPE_ALL);

    return status;
}

int32_t Bootloader_socCpuPowerOnResetC7x(uint32_t cpuId, uintptr_t entry_point, uint32_t initRam)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t sciclientCpuDevId;

    sciclientCpuDevId = Bootloader_socGetSciclientCpuDevId(cpuId);

    /* Turn on LPSC for C7x UMC memory. This is required to load in to C7x UMC memory */
    status = Sciclient_pmSetModuleState(TISCI_DEV_C7X256V0_CORE0, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                                    TISCI_MSG_FLAG_AOP,
                                                    SystemP_WAIT_FOREVER);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("UMC memory power on failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
    }

    status = Sciclient_pmSetModuleState(sciclientCpuDevId,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CPU power off failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
    }

    if(status == SystemP_SUCCESS)
    {
        if(initRam)
        {
            /* initialize the RAMs only if requested
             */
            Bootloader_socInitC7xL2Sram();
        }
    }
    return status;
}

/* Power ON, init the RAMs, load a dummy while loop and hold CPU in reset, do not release the reset */
int32_t Bootloader_socCpuPowerOnReset(uint32_t cpuId, void *socCoreOpMode)
{
    int32_t status = SystemP_FAILURE;

    switch(cpuId)
    {
        case CSL_CORE_ID_R5FSS0_0:
            /* nothing to do CPU's are already powred on, we dont want to hold
               them in reset since bootloader is running here
             */
            break;

        case CSL_CORE_ID_MCU_R5FSS0_0:
            status = Bootloader_socCpuPowerOnResetR5f(cpuId, 0,1);
            break;

        case CSL_CORE_ID_HSM_M4FSS0_0:
            status = Bootloader_socCpuPowerOnResetHSMM4f(cpuId, 1);
            break;
        case CSL_CORE_ID_A53SS0_0:
        case CSL_CORE_ID_A53SS0_1:
        case CSL_CORE_ID_A53SS1_0:
        case CSL_CORE_ID_A53SS1_1:
            status = Bootloader_socCpuPowerOnResetA53(cpuId);
            break;
        case CSL_CORE_ID_C75SS0_0:
            status = Bootloader_socCpuPowerOnResetC7x(cpuId,0,1);
            break;
    }
    return status;
}

int32_t Bootloader_socCpuResetRelease(uint32_t cpuId, uintptr_t entryPoint)
{
    int32_t status = SystemP_FAILURE;
    uint32_t sciclientCpuProcId, sciclientCpuDevId;

    struct tisci_msg_proc_set_config_req  proc_set_config;

    sciclientCpuProcId = Bootloader_socGetSciclientCpuProcId(cpuId);
    sciclientCpuDevId = Bootloader_socGetSciclientCpuDevId(cpuId);

    switch(cpuId)
    {
        case CSL_CORE_ID_R5FSS0_0:
            /* use SOC_cpuResetReleaseSelf instead */
            break;
        case CSL_CORE_ID_MCU_R5FSS0_0:
                        /* set boot address */
            {
                proc_set_config.processor_id = sciclientCpuProcId;
                proc_set_config.bootvector_lo = entryPoint;
                proc_set_config.bootvector_hi = 0;
                proc_set_config.config_flags_1_set = 0;
                proc_set_config.config_flags_1_clear = 0;

                status = Sciclient_procBootSetProcessorCfg(&proc_set_config, SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU set boot address failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }
            }
            if(status == SystemP_SUCCESS)
            {
                status =  Sciclient_procBootSetSequenceCtrl(sciclientCpuProcId,
                                    0,
                                    TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT,
                                    TISCI_MSG_FLAG_AOP,
                                    SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU halt clear failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }
            }
            break;
        case CSL_CORE_ID_HSM_M4FSS0_0:
            {
                status =  Sciclient_procBootSetSequenceCtrl(sciclientCpuProcId,
                                    0,
                                    TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_HSM_M4_RESET,
                                    TISCI_MSG_FLAG_AOP,
                                    SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU halt clear failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }
            }
            break;
        case CSL_CORE_ID_A53SS0_0:
        case CSL_CORE_ID_A53SS0_1:
        case CSL_CORE_ID_A53SS1_0:
        case CSL_CORE_ID_A53SS1_1:
            /* set boot address */
            {
                if(entryPoint==0)
                {
                    /* start A53 pointing to previously loaded while(1) loop */
                    entryPoint = (uintptr_t)BOOTLOADER_A53_WHILELOOP_LOAD_ADDR;
                }
                proc_set_config.processor_id = sciclientCpuProcId;
                proc_set_config.bootvector_lo = entryPoint;
                proc_set_config.bootvector_hi = 0;
                proc_set_config.config_flags_1_set = 0;
                proc_set_config.config_flags_1_clear = 0;

                status = Sciclient_procBootSetProcessorCfg(&proc_set_config, SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU set boot address failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }

                status = Sciclient_pmSetModuleState(sciclientCpuDevId,
                        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                        TISCI_MSG_FLAG_AOP,
                        SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU power off failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }

                status = Sciclient_pmSetModuleState(sciclientCpuDevId,
                        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                        TISCI_MSG_FLAG_AOP,
                        SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU power on failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }
            }

            break;
        case CSL_CORE_ID_C75SS0_0:
            {
                if(entryPoint == 0)
                {
                    entryPoint = (uintptr_t)CSL_C7X256V0_UMC_MEM_MAIN_BASE;
                }
                proc_set_config.processor_id = sciclientCpuProcId;
                proc_set_config.bootvector_lo = entryPoint;
                proc_set_config.bootvector_hi = 0;
                proc_set_config.config_flags_1_set = 0;
                proc_set_config.config_flags_1_clear = 0;

                status = Sciclient_procBootSetProcessorCfg(&proc_set_config, SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU set boot address failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }

                status = Sciclient_pmSetModuleState(sciclientCpuDevId,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SystemP_WAIT_FOREVER);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_logError("CPU power on failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
                }
            }
            break;
    }
    return status;
}

int32_t Bootloader_socCpuSetEntryPoint(uint32_t cpuId, uintptr_t entryPoint)
{
    int32_t status = SystemP_SUCCESS;

    selfcoreEntry = (Bootloader_SelfCoreJump)entryPoint;

    return status;
}

void __attribute__((__noreturn__)) Bootloader_socSelfCPUjump()
{
    selfcoreEntry();
}

int32_t Bootloader_socCpuResetReleaseSelf()
{
    int32_t status = SystemP_SUCCESS;
    uint32_t sciclientCpuProcIdCore0, sciclientCpuDevIdCore0;

    sciclientCpuProcIdCore0 = Bootloader_socGetSciclientCpuProcId(CSL_CORE_ID_R5FSS0_0);
    sciclientCpuDevIdCore0 = Bootloader_socGetSciclientCpuDevId(CSL_CORE_ID_R5FSS0_0);

    /*
     *   SYSFW will block until a WFI is issued, thus allowing the following commands
     *   to be queued so this cluster may be reset by SYSFW (queue length is defined in
     *   "source/drivers/sciclient/include/tisci/{soc}/tisci_sec_proxy.h". If these commands
     *   were to be issued and executed prior to WFI, the cluster would enter reset and
     *   bootloader would not be able to tell SYSFW to take itself out of reset.
     */
    status = Sciclient_procBootWaitProcessorState(sciclientCpuProcIdCore0,
                    1, 1, 0, 3, 0, 0, 0, SystemP_WAIT_FOREVER);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CPU boot wait command failed for %s\r\n", Bootloader_socGetCoreName(CSL_CORE_ID_R5FSS0_0));
    }

    if(status==SystemP_SUCCESS)
    {

        /* after this point you cannot single step in CCS */
        if(status==SystemP_SUCCESS)
        {
            status = Sciclient_pmSetModuleRst_flags(sciclientCpuDevIdCore0, 1, 0, SystemP_WAIT_FOREVER);
        }

        /* release the CPUs */
        if(status==SystemP_SUCCESS)
        {
            status = Sciclient_procBootReleaseProcessor(sciclientCpuProcIdCore0, 0, SystemP_WAIT_FOREVER);
        }
        /* release the reset for the CPUs */
        if(status==SystemP_SUCCESS)
        {
            status = Sciclient_pmSetModuleRst_flags(sciclientCpuDevIdCore0, 0, 0, SystemP_WAIT_FOREVER);
        }
        if(status==SystemP_SUCCESS)
        {
            /* disable interrupts if enabled */
            HwiP_disable();

            /* flush all caches */
            CacheP_wbInvAll(CacheP_TYPE_ALL);

            /* execute wfi, now SYSFW will execute the above commands and reset core0 and core 1 */
            __asm__ __volatile__ ("wfi" "\n\t": : : "memory");
        }
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CPU reset sequence failed for %s\r\n", Bootloader_socGetCoreName(CSL_CORE_ID_R5FSS0_0));
        }
    }
    return status;
}

uint32_t Bootloader_socTranslateSectionAddr(uint32_t cslCoreId, uint32_t addr)
{
    uint32_t outputAddr = addr;

    Bootloader_CoreAddrTranslateInfo *addrTranslateInfo = &gAddrTranslateInfo[cslCoreId];

    uint32_t i;

    for(i=0; i<addrTranslateInfo->numRegions; i++)
    {
        uint32_t cpuLocalAddr = addrTranslateInfo->addrRegionInfo[i].cpuLocalAddr;
        uint32_t socAddr      = addrTranslateInfo->addrRegionInfo[i].socAddr;
        uint32_t regionSize   = addrTranslateInfo->addrRegionInfo[i].regionSize;

        if((addr >= cpuLocalAddr) && (addr <  cpuLocalAddr + regionSize))
        {
            uint32_t offset = addr - cpuLocalAddr;
            outputAddr = socAddr + offset;
            break;
        }
    }

    return outputAddr;
}

int32_t Bootloader_socMemInitCpu(uint32_t cpuId)
{
    int32_t status = SystemP_SUCCESS;

    switch(cpuId) {
        case CSL_CORE_ID_R5FSS0_0:
        case CSL_CORE_ID_MCU_R5FSS0_0:
            Bootloader_socInitR5FAtcmBtcm(cpuId);
            break;
        case CSL_CORE_ID_HSM_M4FSS0_0:
            Bootloader_socInitHSMM4fIram();
            break;
        case CSL_CORE_ID_C75SS0_0:
            Bootloader_socInitC7xL2Sram();
            break;

        default:
            break;
    }

    return status;
}

int32_t Bootloader_socSecHandover(void)
{
    int32_t status = SystemP_SUCCESS;

    status = Sciclient_triggerSecHandover();

    return status;
}

uint32_t Bootloader_socIsAuthRequired(void)
{
    uint32_t isAuthRequired = TRUE;

    uint32_t devType    = CSL_REG32_RD(BOOTLOADER_SYS_STATUS_REG) & BOOTLOADER_SYS_STATUS_DEV_TYPE_MASK;

    if((devType == BOOTLOADER_SYS_STATUS_DEV_TYPE_GP)   ||
       (devType == BOOTLOADER_SYS_STATUS_DEV_TYPE_TEST))
    {
        isAuthRequired = FALSE;
    }
    else
    {
        isAuthRequired = TRUE;
    }

    return isAuthRequired;
}

int32_t Bootloader_socWaitForFWBoot(void)
{
    return Sciclient_waitForBootNotification();
}

int32_t Bootloader_socOpenFirewalls(void)
{
    int32_t status = SystemP_FAILURE;

    /* Nibbles from left to right, 3 implies cached, background region, 0 implies config is unlocked, and A implies enable firewall  */
    uint32_t fwlControl = 0x30A;

    /* There are 3 firewall regions, 1 per FSS memory region. We need to open all these regions. */
    status = Bootloader_socOpenFirewallRegion(CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_ID, 0, fwlControl,
            CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_START,
            CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_END);

    if(status==SystemP_SUCCESS)
    {
        status = Bootloader_socOpenFirewallRegion(CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_ID, 1, fwlControl,
                CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_START,
                CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_END);
    }

    if(status==SystemP_SUCCESS)
    {
        status = Bootloader_socOpenFirewallRegion(CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_ID, 2, fwlControl,
                CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_START,
                CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_END);
    }

    return status;
}

int32_t Bootloader_socAuthImage(uint32_t certLoadAddr)
{
    int32_t status = SystemP_FAILURE;

    struct tisci_msg_proc_auth_boot_req authReq;

    /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
    authReq.certificate_address_hi = 0U;
    authReq.certificate_address_lo = certLoadAddr;

    status = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);

    return status;
}

Bootloader_resMemSections* Bootloader_socGetSBLMem(void)
{
    return &gResMemSection;
}

uint32_t Bootloader_socIsMCUResetIsoEnabled()
{
    uint32_t status = 0;

    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP, 6);

    /* If MAGIC WORD is non zero reset isolation is enabled */
    if (CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD))
    {
        status = 1;
    }

    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_WKUP, 6);

    return status;
}

void Bootloader_socSetSBLMem(uint32_t startAddress, uint32_t regionlength)
{
    gResMemSection.memSection[0].memStart = startAddress;
    gResMemSection.memSection[0].memEnd = startAddress + regionlength;
}
