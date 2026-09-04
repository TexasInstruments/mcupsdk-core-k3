/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/*
 * Dual Task Orchestration - Main Task Creation
 *
 * Creates and manages both TVM compute and DSP service tasks
 */

#include <FreeRTOS.h>
#include <task.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/MmuP_armv8.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <kernel/nortos/dpl/c75/CacheP_c75.h>
#include <kernel/nortos/dpl/c75/HwiP_c75.h>
#include <kernel/nortos/dpl/c75/MmuP_c75.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/hw_include/csl_clec.h>
#include <drivers/hw_include/am62ax/cslr_soc_baseaddress.h>

#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "c7x_compute_protocol.h"
#include "dsp_service.h"

extern MmuP_Config gMmuConfig;
extern MmuP_RegionConfig gMmuRegionConfig[];

/* Defined in am62dx-evm/c7x_cxm.c (board-specific inline asm) */
extern void c7x_set_l1dcfg(uint64_t val);

#define C7x_EL2_SNOOP_CFG_REG (0x7C00000Cu)

static void setC7xSnoopCfgReg()
{
    volatile uint32_t *pReg = (uint32_t *)C7x_EL2_SNOOP_CFG_REG;

    /* This operation overrides the existing value of snoop config!*/
    *pReg = (uint32_t)(0u);
}

static void configureC7xL1DCacheAsWriteThrough()
{
    volatile uint64_t l1dcfg = 0x1U;
#if !defined(MCU_PLUS_SDK)
    Cache_wbInvL1dAll();
#else
    CacheP_wbInvAll(CacheP_TYPE_L1D);
#endif
    c7x_set_l1dcfg(l1dcfg);
}

static void appC75ClecInitDru(void)
{
    CSL_ClecEventConfig   cfgClec;
    CSL_CLEC_EVTRegs   *clecBaseAddr = (CSL_CLEC_EVTRegs*) CSL_C7X256V0_CLEC_BASE;

    uint32_t i;
    uint32_t dru_input_num   = 16;

    /* DRU Local event start ref: AM62A clec spec*/
    uint32_t dru_input_start = 128;

    /* program CLEC events from DRU used for polling by TIDL
     * to map to required events in C7x
     */
    for(i = dru_input_start; i < (dru_input_start + dru_input_num); i++)
    {
        /* Configure CLEC */
        cfgClec.secureClaimEnable = FALSE;
        cfgClec.evtSendEnable     = TRUE;
        cfgClec.rtMap             = CSL_CLEC_RTMAP_CPU_ALL;
        cfgClec.extEvtNum         = 0;
        cfgClec.c7xEvtNum         = (i - dru_input_start) + 32;
        CSL_clecConfigEvent(clecBaseAddr, i, &cfgClec);
    }
}

void appCacheInit()
{
    /* Going with default cache setting on reset */
    /* L1P - 32kb$, L1D - 64kb$, L2 - 0kb$ */
    configureC7xL1DCacheAsWriteThrough();
    setC7xSnoopCfgReg();
}

/*
 * =============================================================================
 * Firmware-wide IPC Shutdown Handling
 * =============================================================================
 */

/* Stored by ISR callback, used by main task to send ACK after cleanup */
static volatile uint16_t gShutdownRemoteCoreId = 0;

/**
 * IPC mailbox callback for shutdown notification from Linux.
 */
static void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t localClientId,
                                  uint32_t msgValue, void *args)
{
    if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN)
    {
        DebugP_log("[IPC] Received SHUTDOWN request from Linux\r\n");

        /* Store remote core ID for sending ACK later (from task context) */
        gShutdownRemoteCoreId = remoteCoreId;

        /* Signal TVM service loop to stop (unblocks RPMessage_recv) */
        extern void compute_service_stop(void);
        compute_service_stop();

        /* Signal DSP service loop to stop */
        dsp_service_stop();

        /* Note: Shutdown ACK will be sent after both services complete cleanup */
    }
}

/*
 * =============================================================================
 * Task Configuration
 * =============================================================================
 */

#define MAIN_TASK_STACK_SIZE    (16 * 1024)  /* in StackType_t units (8 bytes each) = 128KB */
#define MAIN_TASK_PRIORITY      (configMAX_PRIORITIES - 1)

#define DSP_TASK_STACK_SIZE (6 * 1024)   /* in StackType_t units (8 bytes each) = 48KB */
#define DSP_TASK_PRIORITY   (configMAX_PRIORITIES - 2)

static StaticTask_t gMainTaskObj;
static StackType_t  gMainTaskStack[MAIN_TASK_STACK_SIZE] __attribute__((aligned(0x2000)));

static StaticTask_t gDspTaskObj;
static StackType_t  gDspTaskStack[DSP_TASK_STACK_SIZE] __attribute__((aligned(0x2000)));

/*
 * =============================================================================
 * External Task Entry Points
 * =============================================================================
 */

extern void tvm_compute_main(void *args);

/*
 * =============================================================================
 * Dual Task Orchestration
 * =============================================================================
 */

void dual_task_main(void *args)
{
    int32_t status;
    uint32_t mmuEnabled;

    DebugP_log("\r\n");
    DebugP_log("===========================================\r\n");
    DebugP_log("      DSP EdgeAI Firmware\r\n");
    DebugP_log("      Built: %s %s\r\n", __DATE__, __TIME__);
    DebugP_log("===========================================\r\n");
    DebugP_log("\r\n");

    appC75ClecInitDru();

    /* Verify MMU is enabled */
    mmuEnabled = MmuP_isEnabled();
    if (mmuEnabled)
    {
        DebugP_log("Cache coherent access to shared memory enabled\r\n");
    }
    else
    {
        DebugP_log("WARNING: MMU disabled, cache coherency may not work\r\n");
    }

    /* Wait for Linux to initialize virtio vrings (polls resource table status) */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Linux ready wait failed: %d\r\n", status);
    }

    /* Register shutdown callback */
    status = IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                                       ipc_rp_mbox_callback, NULL);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to register RP_MBOX callback: %d\r\n", status);
    }

    /* Create TVM compute service task */
    xTaskCreateStatic(tvm_compute_main,
                      "tvm_compute",
                      MAIN_TASK_STACK_SIZE,
                      NULL,
                      MAIN_TASK_PRIORITY,
                      gMainTaskStack,
                      &gMainTaskObj);

    /* Create DSP service task */
    xTaskCreateStatic(dsp_service_main,
                      "dsp_service",
                      DSP_TASK_STACK_SIZE,
                      NULL,
                      DSP_TASK_PRIORITY,
                      gDspTaskStack,
                      &gDspTaskObj);

    /* Wait for shutdown signal if needed */
    while (gShutdownRemoteCoreId == 0)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));  /* Check every second */
    }

    /* Both service tasks will self-delete when stopped.
     * Allow time for cleanup, then send shutdown ACK */
    vTaskDelay(pdMS_TO_TICKS(500));

    /* Send shutdown ACK to Linux */
    DebugP_log("[SHUTDOWN] Sending SHUTDOWN_ACK to core %u\r\n", gShutdownRemoteCoreId);
    IpcNotify_sendMsg(gShutdownRemoteCoreId,
                      IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                      IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1);

    /* Close drivers and board */
    Board_driversClose();
    Drivers_close();

    DebugP_log("[SHUTDOWN] Entering IDLE state for remoteproc stop\r\n");

    /* Disable interrupts and halt */
    HwiP_disable();
    __asm(" IDLE");
}

void MmuP_setConfig(void)
{
    uint32_t i;
    int32_t status;

    for(i = 0; i < gMmuConfig.numRegions; i++)
    {
        status = MmuP_map(gMmuRegionConfig[i].vaddr, gMmuRegionConfig[i].paddr,
                                                gMmuRegionConfig[i].size, &gMmuRegionConfig[i].attr);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        (void)status;
    }

    /* Initialize clec */
    HwiP_configClecAccessCtrl();
    appCacheInit();
}

void CacheP_Module_startup(void)
{
    CacheP_enable(CacheP_TYPE_L1D);
    CacheP_enableWB(CacheP_TYPE_L1D);
}
