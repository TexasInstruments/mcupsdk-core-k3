/*
 * Copyright (C) 2026 Texas Instruments Incorporated
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

#include <unity.h>
#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/sciclient_lpm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Use a safe device for PM state transition validation */
#if defined(SOC_AM62DX)
#define TEST_DEVICE_ID          TISCI_DEV_MCU_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_MCU_UART0_FCLK_CLK
#elif defined(SOC_AM275X)
/* WKUP_UART0 FCLK_CLK is fixed-source on AM275x (no switchable parent mux) */
#define TEST_DEVICE_ID          TISCI_DEV_WKUP_UART0          /* 114U */
#define TEST_DEVICE_CLK_ID      TISCI_DEV_WKUP_UART0_FCLK_CLK /* 0U */
#else
#define TEST_DEVICE_ID          (0xFFFFU)
#define TEST_DEVICE_CLK_ID      (0U)
#endif

#define TEST_FIXED_SRC_CLK_DEVICE_ID  TEST_DEVICE_ID
#define TEST_FIXED_SRC_CLK_ID         TEST_DEVICE_CLK_ID

/* ---- Processor boot IDs: SOC-specific aliases ----------------------------
 * AM62DX / AM62AX define SCICLIENT_PROC_ID_xxx names directly.
 * AM275x defines the same hardware IDs under the PROC_ID_ prefix only.
 * AM275x has no A53 cores; SCICLIENT_PROC_ID_A53SS0_CORE_1 is mapped to
 * PROC_ID_C7X256V0_C7XV_CORE_0 (the C7X co-processor), and
 * TISCI_HOST_ID_A53_2 is mapped to TISCI_HOST_ID_C7X_1_0.
 * -------------------------------------------------------------------------- */
#if defined(SOC_AM275X)
#define SCICLIENT_PROC_ID_R5FSS0_CORE0            PROC_ID_R5FSS0_CORE0
#define SCICLIENT_PROC_ID_A53SS0_CORE_0           PROC_ID_C7X256V0_C7XV_CORE_0
#define SCICLIENT_PROC_ID_A53SS0_CORE_1           PROC_ID_C7X256V0_C7XV_CORE_0
#define TISCI_HOST_ID_A53_2                       TISCI_HOST_ID_C7X_1_0
#endif

/* ---- Resource ID macros ---------------------------------------------------
 * This wrapper is built/run as many different TISCI hosts depending on
 * SoC and core (e.g. TISCI_HOST_ID_MAIN_0_R5_1 or _R5_0, TISCI_HOST_ID_
 * MCU_0_R5_0, TISCI_HOST_ID_M4_0, TISCI_HOST_ID_C7X_0_0, TISCI_HOST_ID_
 * WKUP_0_R5_x ...). A single hardcoded resource index that is exclusively
 * owned by one specific host (e.g. ring 18 owned only by MAIN_0_R5_1 /
 * C7X_0_0 on AM62AX/AM62DX) fails with retVal=-1 (permission denied) on
 * every other host, e.g. TISCI_HOST_ID_MCU_0_R5_0 on the AM62AX/AM62DX/
 * AM62PX mcu-r5fss0-0 build, or TISCI_HOST_ID_M4_0 on the AM62X m4fss0-0
 * build (SITSW-12458).
 *
 * To stay host-agnostic, use resources from the TISCI_HOST_ID_ALL shared
 * pool instead (usable by every host regardless of which core built/runs
 * this test) -- the same approach already used elsewhere in this repo by
 * test_sciclient_val.h for this identical multi-host problem. See
 * sciclient_defaultBoardcfg_rm.c per SoC for the TISCI_HOST_ID_ALL ranges
 * used below. ------------------------------------------------------------ */
#define WRAP_RM_NAV_BCDMA_DEV_ID    TISCI_DEV_DMASS0_BCDMA_0    /* 26U */
#define WRAP_RM_NAV_PKTDMA_DEV_ID   TISCI_DEV_DMASS0_PKTDMA_0   /* 30U */
#define WRAP_RM_NAV_INTAGGR_DEV_ID  TISCI_DEV_DMASS0_INTAGGR_0  /* 28U */
/* BCDMA_RING_BLOCK_COPY_CHAN, TISCI_HOST_ID_ALL range:
 *   AM275X:                          start=17, count=7
 *   AM62PX:                          start=30, count=2
 *   AM62AX / AM62DX / AM62X:         start=26, count=6 */
#if defined(SOC_AM275X)
#define WRAP_RM_BCDMA_RING_IDX      (17U)
#else
#define WRAP_RM_BCDMA_RING_IDX      (26U)
#endif
/* PKTDMA_UNMAPPED_TX_CHAN / _RX_CHAN / FLOW_UNMAPPED_RX_CHAN, TISCI_HOST_ID_ALL range:
 *   AM275X:                          start=12, count=15
 *   AM62AX / AM62DX / AM62PX / AM62X: start=16, count=3 */
#if defined(SOC_AM275X)
#define WRAP_RM_PKTDMA_TX_CH_IDX    (12U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (12U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (12U)
#else
#define WRAP_RM_PKTDMA_TX_CH_IDX    (16U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (16U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (16U)
#endif
/* "Not owned by this host" index used by the RM negative test cases below
 * (ring/channel/flow index 0 is expected to NACK for the running host).
 * sciclient_defaultBoardcfg_rm.c (am275x): BCDMA_RING_BLOCK_COPY_CHAN /
 * PKTDMA_UNMAPPED_TX_CHAN / PKTDMA_UNMAPPED_RX_CHAN / PKTDMA_FLOW_UNMAPPED_
 * RX_CHAN all allocate index 0-4 to TISCI_HOST_ID_MAIN_0_R5_1 and index 5-7
 * to TISCI_HOST_ID_C7X_0_0. This project builds separately for each
 * r5fssX-Y core (all of which run as TISCI_HOST_ID_MAIN_0_R5_1 or another
 * R5/WKUP host that also does not own index 5) and for each c75ssX-0 core
 * (CORE_C7 defined, running as C7X_0_0/C7X_1_0, neither of which owns
 * index 0). Pick whichever index the current build does NOT own so the
 * negative test reliably NACKs on every AM275X core (SITSW-12458). */
#if defined(SOC_AM275X)
#if defined(CORE_C7)
#define WRAP_RM_NOT_OWNED_IDX       (0U)   /* owned by MAIN_0_R5_1 */
#else
#define WRAP_RM_NOT_OWNED_IDX       (5U)   /* owned by C7X_0_0 */
#endif
#else
#define WRAP_RM_NOT_OWNED_IDX       (0U)
#endif
#define WRAP_RM_IRQ_SRC_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_SRC_INDEX       (10U)
#define WRAP_RM_IRQ_DST_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_DST_HOST_IRQ    (0U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_A53_2                 /* 12U */
#define WRAP_RM_PSIL_NAV_ID         TISCI_DEV_DMASS0                    /* 25U */
/* PSIL thread numbers encode the PKTDMA TX/RX channel index in their low
 * bits (TX = 0x1000 | idx, RX = 0x9000 | idx). Reuse the same
 * TISCI_HOST_ID_ALL-owned channel index as the UDMAP TX/RX channel tests
 * above so pairing succeeds regardless of which host runs this test
 * (SITSW-12458 — a hardcoded thread 0x100B/0x900B, tied to a MAIN_0_R5_1/
 * _R5_0-exclusive channel, NACKs on other hosts e.g. TISCI_HOST_ID_MCU_0_R5_0). */
#define WRAP_RM_PSIL_SRC_THREAD     (0x1000U | WRAP_RM_PKTDMA_TX_CH_IDX)  /* PKTDMA TX */
#define WRAP_RM_PSIL_DST_THREAD     (0x9000U | WRAP_RM_PKTDMA_RX_CH_IDX)  /* PKTDMA RX (>= 0x8000) */
#define WRAP_RM_PSIL_TADDR          (0x0002U)  /* thread config reg offset */
#define WRAP_RM_PSIL_WRITE_DATA     (0x80000000U)

/* ---- Proc-boot handover target host --------------------------------------
 * testSciclient_procBootSciclientApis (Sciclient_procBootHandoverProcessor,
 * SITSW-12456) hands processor ownership of A53SS0_CORE_1 away from the
 * CURRENT host to verify that a subsequent handover attempt by the (now
 * former) owner is NACKed. A hardcoded target of TISCI_HOST_ID_A53_2 is
 * wrong when this test itself IS built/run as TISCI_HOST_ID_A53_2 (the
 * AM62AX/AM62DX/AM62X CORE_A53 a53ss0-0 build): handing over to yourself is
 * a no-op, ownership is never actually relinquished, and the "not owner
 * anymore" negative test (TC-03) unexpectedly ACKs instead of NACKing. Pick
 * a target host different from whichever host this test itself runs as.
 * (This whole section is skipped on SOC_AM275X, and AM62PX/AM62X's other
 * core -- MCU R5F / M4F -- are already distinct from TISCI_HOST_ID_A53_2.) */
#if defined(CORE_A53)
#define WRAP_PROCBOOT_HANDOVER_HOST TISCI_HOST_ID_MAIN_0_R5_1
#else
#define WRAP_PROCBOOT_HANDOVER_HOST TISCI_HOST_ID_A53_2
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void testSciclient_powerManagement(void *args)
{
    int32_t  retVal;
    int32_t  retValFailCnt = 0;
    uint32_t moduleState;
    uint32_t resetState;
    uint32_t contextLossState;
    uint32_t clkState;
    uint32_t numParent;
    uint32_t parent;
    uint64_t freqHz;
    uint64_t respFreqHz;

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleState — TISCI_MSG_SET_DEVICE (0x0200)          */
    /* ------------------------------------------------------------------ */

    /* Positive: set device ON */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState: Positive: set device ON  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleState — TISCI_MSG_GET_DEVICE (0x0201)          */
    /* ------------------------------------------------------------------ */

    /* Positive: query state of the device that was just set ON */
    retVal = Sciclient_pmGetModuleState(
        TEST_DEVICE_ID,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState: Positive: query state of the device that was just set ON  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid module ID 0xFF */
    retVal = Sciclient_pmGetModuleState(
        0xFFFEU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState: Negative: invalid module ID 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid module ID 0xFFFF */
    retVal = Sciclient_pmGetModuleState(
        0xFFFFU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState: Negative: invalid module ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: module ID 0xFFFD (out-of-range, rejected by firmware) */
    retVal = Sciclient_pmGetModuleState(
        0xFFFDU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState: Negative: module ID 0xFFFD (out-of-range, rejected by firmware)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmModuleClkRequest — TISCI_MSG_SET_CLOCK (0x0100)         */
    /* ------------------------------------------------------------------ */

    /* Positive: enable clock for the device (device must be ON first) */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Positive: enable clock for the device (device must be ON first)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: out-of-range clock ID (256) for a valid device */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        256U,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Negative: out-of-range clock ID (256) for a valid device  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFF */
    retVal = Sciclient_pmModuleClkRequest(
        0xFFFEU,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Negative: invalid device ID 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFF */
    retVal = Sciclient_pmModuleClkRequest(
        0xFFFFU,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Negative: invalid device ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid clock state value 0xFF */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        0xFFFEU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Negative: invalid clock state value 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device ID 0x0 with out-of-range clock ID 256 */
    retVal = Sciclient_pmModuleClkRequest(
        0x0U,
        256U,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest: Negative: device ID 0x0 with out-of-range clock ID 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmModuleGetClkStatus — TISCI_MSG_GET_CLOCK (0x0101)       */
    /* ------------------------------------------------------------------ */

    /* Positive: read clock state */
    retVal = Sciclient_pmModuleGetClkStatus(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus: Positive: read clock state  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: out-of-range clock ID (256) */
    retVal = Sciclient_pmModuleGetClkStatus(
        TEST_DEVICE_ID,
        256U,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus: Negative: out-of-range clock ID (256)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFF */
    retVal = Sciclient_pmModuleGetClkStatus(
        0xFFFEU,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus: Negative: invalid device ID 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFF */
    retVal = Sciclient_pmModuleGetClkStatus(
        0xFFFFU,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus: Negative: invalid device ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device ID 0x0 with out-of-range clock ID 256 */
    retVal = Sciclient_pmModuleGetClkStatus(
        0x0U,
        256U,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus: Negative: device ID 0x0 with out-of-range clock ID 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleRst — TISCI_MSG_SET_DEVICE_RESETS (0x0202)     */
    /* ------------------------------------------------------------------ */

    /* Positive: assert reset then de-assert */
    retVal = Sciclient_pmSetModuleRst(
        TEST_DEVICE_ID,
        1U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst: Positive: assert reset  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    retVal = Sciclient_pmSetModuleRst(
        TEST_DEVICE_ID,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst: Positive: de-assert reset  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFF */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFEU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst: Negative: invalid device ID 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFF */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFFU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst: Negative: invalid device ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFD */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFDU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst: Negative: invalid device ID 0xFFFD  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleRst_flags — TISCI_MSG_SET_DEVICE_RESETS (0x0202)*/
    /* ------------------------------------------------------------------ */

    /* Positive: assert reset with AOP flag, then de-assert */
    retVal = Sciclient_pmSetModuleRst_flags(
        TEST_DEVICE_ID,
        1U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags: Positive: assert reset with AOP flag  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(
        TEST_DEVICE_ID,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags: Positive: de-assert with AOP flag  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFF */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFEU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags: Negative: invalid device ID 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFF */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFFU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags: Negative: invalid device ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device ID 0xFFFD */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFDU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags: Negative: invalid device ID 0xFFFD  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleState negative cases                           */
    /* ------------------------------------------------------------------ */

    /* Restore device to AUTO_OFF */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState: Positive: restore device to AUTO_OFF  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid module ID */
    retVal = Sciclient_pmSetModuleState(
        0xFFFFU,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState: Negative: invalid module ID  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid state value */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        0xFFFEU,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState: Negative: invalid state value  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device ID 0xFFFD (out-of-range, rejected by firmware) */
    retVal = Sciclient_pmSetModuleState(
        0xFFFDU,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState: Negative: device ID 0xFFFD (out-of-range, rejected by firmware)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleClkParent — TISCI_MSG_SET_CLOCK_PARENT (0x0102)*/
    /* Fixed-source clock (TEST_FIXED_SRC_CLK_DEVICE_ID/_ID): firmware      */
    /* NACKs parent ops, wrapper returns CSL_EFAIL — all cases below       */
    /* expect failure.                                                      */
    /* ------------------------------------------------------------------ */

    /* Fixed-source clock → firmware NACK */
    retVal = Sciclient_pmSetModuleClkParent(
        TEST_FIXED_SRC_CLK_DEVICE_ID,
        TEST_FIXED_SRC_CLK_ID,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent: Negative: fixed-source clock -> firmware NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFF, clock 0, parent 0 */
    retVal = Sciclient_pmSetModuleClkParent(
        0xFFFEU, 0x0U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent: Negative: invalid device 0xFF, clock 0, parent 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmSetModuleClkParent(
        0xFFFFU, 0x0U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmSetModuleClkParent(
        0x0U, 256U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, clock 0, out-of-range parent 256 */
    retVal = Sciclient_pmSetModuleClkParent(
        0x0U, 0x0U, 256U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent: Negative: device 0x0, clock 0, out-of-range parent 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkParent — TISCI_MSG_GET_CLOCK_PARENT (0x0103)*/
    /* ------------------------------------------------------------------ */

    /* Fixed-source clock → firmware NACK */
    retVal = Sciclient_pmGetModuleClkParent(
        TEST_FIXED_SRC_CLK_DEVICE_ID,
        TEST_FIXED_SRC_CLK_ID,
        &parent,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkParent: Negative: fixed-source clock -> firmware NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFF */
    retVal = Sciclient_pmGetModuleClkParent(
        0xFFFEU, 0x0U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkParent: Negative: invalid device 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmGetModuleClkParent(
        0xFFFFU, 0x0U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkParent: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkParent(
        0x0U, 256U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkParent: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkNumParent — TISCI_MSG_GET_NUM_CLOCK_PARENTS */
    /*                                     (0x0104)                       */
    /* ------------------------------------------------------------------ */

    /* Positive: valid device / clock → SUCCESS */
    retVal = Sciclient_pmGetModuleClkNumParent(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &numParent,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent: Positive: valid device / clock -> SUCCESS  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFF */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0xFFFEU, 0x0U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent: Negative: invalid device 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0xFFFFU, 0x0U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0x0U, 256U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkFreq — TISCI_MSG_GET_FREQ (0x010E)         */
    /* ------------------------------------------------------------------ */

    /* Positive: read current clock frequency (device must be ON) */
    freqHz = 0ULL;
    retVal = Sciclient_pmGetModuleClkFreq(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &freqHz,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq: Positive: read current clock frequency (device must be ON)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFF */
    retVal = Sciclient_pmGetModuleClkFreq(
        0xFFFEU, 0x0U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq: Negative: invalid device 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmGetModuleClkFreq(
        0xFFFFU, 0x0U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkFreq(
        0x0U, 256U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleClkFreq — TISCI_MSG_SET_FREQ (0x010C)         */
    /* ------------------------------------------------------------------ */

    /* Positive: re-read current frequency and set it back (no-op change) */
    retVal = Sciclient_pmGetModuleClkFreq(
        TEST_DEVICE_ID, TEST_DEVICE_CLK_ID, &freqHz, SystemP_WAIT_FOREVER);
    if (retVal == SystemP_SUCCESS)
    {
        retVal = Sciclient_pmSetModuleClkFreq(
            TEST_DEVICE_ID,
            TEST_DEVICE_CLK_ID,
            freqHz,
            0U,
            SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq: Positive: re-read current frequency and set it back (no-op change)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* Negative: invalid device 0xFF */
    retVal = Sciclient_pmSetModuleClkFreq(
        0xFFFEU, 0x0U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq: Negative: invalid device 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmSetModuleClkFreq(
        0xFFFFU, 0x0U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmSetModuleClkFreq(
        0x0U, 256U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: unreachable frequency (1 Hz) on valid device/clock */
    retVal = Sciclient_pmSetModuleClkFreq(
        TEST_DEVICE_ID, TEST_DEVICE_CLK_ID, 1ULL, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq: Negative: unreachable frequency (1 Hz) on valid device/clock  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmQueryModuleClkFreq — TISCI_MSG_QUERY_FREQ (0x010D)     */
    /* ------------------------------------------------------------------ */

    /* Positive: query achievable frequency using last-read freqHz value */
    retVal = Sciclient_pmQueryModuleClkFreq(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        freqHz,
        &respFreqHz,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq: Positive: query achievable frequency using last-read freqHz value  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFF */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0xFFFEU, 0x0U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq: Negative: invalid device 0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0xFFFFU, 0x0U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0x0U, 256U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmDeviceReset — TISCI_MSG_SYS_RESET (0x0005)             */
    /* Positive test resets the board immediately; guard manually.        */
    /* ------------------------------------------------------------------ */
#ifdef ENABLE_MANUAL_TEST
    retVal = Sciclient_pmDeviceReset(SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmDeviceReset: Positive  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }
#endif /* ENABLE_MANUAL_TEST */

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmDomainReset — TISCI_MSG_SYS_RESET (domain variant)     */
    /* A positive test would reset the specified power domain, which is   */
    /* destructive.  Only negative tests (invalid domGrp) are safe here. */
    /* Sciclient_pmDomainReset() is only implemented in the              */
    /* ENABLE_SCICLIENT_DIRECT (DM R5F ROM) build path                   */
    /* (source/drivers/device_manager/sciclient_direct/sciclient_pm.c) — */
    /* it is not available in the regular mailbox-based sciclient_pm.c   */
    /* used by a53/mcu-r5f/c7 builds, so skip it there.                  */
    /* ------------------------------------------------------------------ */
#if !defined(SKIP_SCICLIENT)
    /* TC-01: Negative – invalid domGrp 0xFF → NACK */
    retVal = Sciclient_pmDomainReset(0xFFU, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmDomainReset TC-01: Negative: domGrp=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }
    
    /* TC-02: Negative – invalid domGrp 0x70 → NACK */
    retVal = Sciclient_pmDomainReset(0x70U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmDomainReset TC-02: Negative: domGrp=0x70  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }
    
#endif /* SKIP_SCICLIENT */

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ========================================================================== */
/*                                                                            */
/*   testSciclient_firewallApis                                                      */
/*   Firewall API wrapper tests — JIRA 12097                                  */
/*                                                                            */
/*   Covers:                                                                  */
/*     Sciclient_firewallGetRegion       (TISCI_MSG_GET_FWL_REGION    0x9001) */
/*     Sciclient_firewallSetRegion       (TISCI_MSG_SET_FWL_REGION    0x9000) */
/*     Sciclient_firewallChangeOwnerInfo (TISCI_MSG_CHANGE_FWL_OWNER  0x9002) */
/*                                                                            */
/* ========================================================================== */

void testSciclient_firewallApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallGetRegion — TISCI_MSG_GET_FWL_REGION (0x9001)        */
    /* ---------------------------------------------------------------------- */

    /* Positive: query fwl_id=7 (FSS0 — owned by DM on AM62DX), region=0 */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 7U;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);

        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion: Positive: query fwl_id=7 region=0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallGetRegion(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_firewallGetRegion: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 0xFFFFU;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 0xFFU;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallSetRegion — TISCI_MSG_SET_FWL_REGION (0x9000)        */
    /* ---------------------------------------------------------------------- */

    /* Positive: read-then-restore — GET fwl_id=7 (FSS0, DM-owned) region=0,
     * then SET back the exact same values.  No-op write that safely exercises
     * the full SET code path without changing permissions or address range. */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 7U;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);

        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion: Positive: read-then-restore GET fwl_id=7 region=0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        {
            struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
            struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

            setReq.fwl_id            = getResp.fwl_id;
            setReq.region            = getResp.region;
            setReq.n_permission_regs = getResp.n_permission_regs;
            setReq.control           = getResp.control;
            setReq.permissions[0]    = getResp.permissions[0];
            setReq.permissions[1]    = getResp.permissions[1];
            setReq.permissions[2]    = getResp.permissions[2];
            setReq.start_address     = getResp.start_address;
            setReq.end_address       = getResp.end_address;

            retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);

            if(retVal != SystemP_SUCCESS)
            {
                DebugP_log("FAIL: Sciclient_firewallSetRegion: Positive: read-then-restore SET  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
                retValFailCnt++;
            }
        }
    }

    /* Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallSetRegion(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_firewallSetRegion: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK) */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 3U;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;
        setReq.control           = 0x30AU;
        setReq.permissions[0]    = 0xC3FFFFU;
        setReq.permissions[1]    = 0xC3FFFFU;
        setReq.permissions[2]    = 0xC3FFFFU;
        setReq.start_address     = 0x70000000U;
        setReq.end_address       = 0x701FF000U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion: Negative: fwl_id=3 (not owned by DM on AM62DX)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 0xFFFFU;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 0xFFU;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallChangeOwnerInfo — TISCI_MSG_CHANGE_FWL_OWNER (0x9002)*/
    /* ---------------------------------------------------------------------- */

    /* Positive: fwl_id=7 (FSS0, DM-owned), region=0,
     * owner_index=TISCI_HOST_ID_MAIN_0_R5_0 (DM R5F — re-asserting current
     * ownership is a no-op and always succeeds). */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 7U;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Positive: fwl_id=7 region=0 owner_index=MAIN_0_R5_0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallChangeOwnerInfo(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK) */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 3U;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Negative: fwl_id=3 (not owned by DM on AM62DX)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 0xFFFFU;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 0xFFU;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* Negative: invalid owner_index=0xFF with valid fwl_id=7 */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 7U;
        req.region      = 0U;
        req.owner_index = 0xFFU;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo: Negative: invalid owner_index=0xFF with valid fwl_id=7  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ========================================================================== */
/*                                                                            */
/*   testSciclient_coreVersion                                                     */
/*   Combined version / ABI / DM-version / SEC-handover API tests            */
/*                                                                            */
/*   Covers (one RUN_TEST, single JIRA):                                      */
/*     Sciclient_abiCheck          TISCI_MSG_VERSION     0x0002              */
/*     Sciclient_getVersionCheck   TISCI_MSG_VERSION     0x0002              */
/*     Sciclient_getDMVersion      TISCI_MSG_DM_VERSION  0x000F              */
/*     Sciclient_triggerSecHandover TISCI_MSG_SEC_HANDOVER 0x9030            */
/*                                                                            */
/* ========================================================================== */

void testSciclient_coreVersion(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_abiCheck — TISCI_MSG_VERSION (0x0002)                     */
    /* Validates SYSFW ABI major version against SCICLIENT_FIRMWARE_ABI_MAJOR */
    /* ------------------------------------------------------------------ */

    /* Positive: firmware running, ABI major version matches expected */
    retVal = Sciclient_abiCheck();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_abiCheck: Positive: firmware running, ABI major version matches expected  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /*
     * Note: Sciclient_abiCheck() takes no arguments. The only way to produce
     * a failure is if the runtime ABI major reported by SYSFW differs from
     * SCICLIENT_FIRMWARE_ABI_MAJOR, which cannot be forced at runtime.
     * No parameter-driven negative case.
     */

    /* ------------------------------------------------------------------ */
    /* Sciclient_getVersionCheck — TISCI_MSG_VERSION (0x0002)             */
    /* Sends TISCI_MSG_VERSION to SYSFW and verifies ACK.                 */
    /* doLog controls console output only, not pass/fail.                 */
    /* ------------------------------------------------------------------ */

    /* Positive: with logging enabled (doLog=1) */
    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_getVersionCheck: Positive: with logging enabled (doLog=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Positive: with logging disabled (doLog=0) */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_getVersionCheck: Positive: with logging disabled (doLog=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /*
     * Note: doLog is a logging flag only. TISCI_MSG_VERSION always succeeds
     * on a running system. No parameter-driven negative case.
     */

#if !defined(SKIP_SCICLIENT)

    /* ------------------------------------------------------------------ */
    /* Sciclient_getDMVersion — TISCI_MSG_DM_VERSION (0x000F)             */
    /* In ENABLE_SCICLIENT_DIRECT builds Sciclient_getDMVersion() from     */
    /* drivers.lib cannot be linked (duplicate symbols with               */
    /* sciclient_direct.lib). Sciclient_direct_getDMVersion() is the       */
    /* sciclient_direct equivalent declared in                            */
    /* source/drivers/sciclient.h and provides identical   */
    /* behaviour.                                                         */
    /* ------------------------------------------------------------------ */

    /* Positive: with logging enabled (doLog=1) */
    retVal = Sciclient_direct_getDMVersion(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_direct_getDMVersion: Positive: with logging enabled (doLog=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Positive: with logging disabled (doLog=0) */
    retVal = Sciclient_direct_getDMVersion(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_direct_getDMVersion: Positive: with logging disabled (doLog=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

#endif

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testSciclient_resourceManagementSciclient — Resource Management (RM) API coverage
 *
 * Covers all 13 Sciclient_rm* APIs compiled into sciclient_direct.lib:
 *   Sciclient_rmGetResourceRange
 *   Sciclient_rmIrqSetRaw / Sciclient_rmIrqReleaseRaw
 *   Sciclient_rmRingCfg
 *   Sciclient_rmUdmapGcfgCfg
 *   Sciclient_rmUdmapTxChCfg / Sciclient_rmUdmapRxChCfg
 *   Sciclient_rmUdmapFlowCfg / Sciclient_rmUdmapFlowSizeThreshCfg
 *   Sciclient_rmPsilPair / Sciclient_rmPsilUnpair
 *   Sciclient_rmPsilRead  / Sciclient_rmPsilWrite
 *
 * AM62DX resource allocation (default RM board config):
 *   TISCI_HOST_ID_MAIN_0_R5_1 owns:
 *     BCDMA ring indices 18-23 (DMASS0_BCDMA_0, nav_id=26)
 *     PKTDMA unmapped TX ch 10, RX ch 10, RX flow 10 (DMASS0_PKTDMA_0, nav_id=30)
 *     UDMAP_GLOBAL_CONFIG allocated to TISCI_HOST_ID_ALL
 *     MAIN_GPIOMUX_INTROUTER0 IR_OUTPUT[0..15] allocated to A53_2 (secondary_host)
 *     DMASS0 PSIL threads 0x100B (PKTDMA TX) / 0x900B (PKTDMA RX)
 *
 * Test strategy for configurable APIs: use valid_params=0 (no-op) where
 * possible — only the ownership permission check fires; no HW registers written.
 * IRQ: set route in IrqSetRaw, release it in IrqReleaseRaw.
 * PSIL: pair threads in PsilPair, read/write, then unpair in PsilUnpair.
 * ========================================================================== */

void testSciclient_resourceManagementSciclient(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* 1. Sciclient_rmGetResourceRange — TISCI_MSG_RM_GET_RESOURCE_RANGE   */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_get_resource_range_req  req;
        struct tisci_msg_rm_get_resource_range_resp resp;

        /* TC-01: Positive – query IA_VINT resources for INTAGGR_0.
         * TISCI_HOST_ID_ALL → range_num > 0 expected. */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = (uint16_t) WRAP_RM_NAV_INTAGGR_DEV_ID;
        req.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-01: Positive: query IA_VINT resources for INTAGGR_0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid device type (0xFFFF) */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = 0xFFFFU;
        req.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-02: Negative: invalid device type (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid subtype (0xFF) with valid device type */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = (uint16_t) WRAP_RM_NAV_INTAGGR_DEV_ID;
        req.subtype        = 0xFFU;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-03: Negative: invalid subtype (0xFF) with valid device type  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmGetResourceRange(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 2. Sciclient_rmIrqSetRaw — TISCI_MSG_RM_IRQ_SET (0x1000)           */
    /* Routes MAIN_GPIOMUX_INTROUTER0 input 10 → output 0 for A53_2.     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_irq_set_req  req;
        struct tisci_msg_rm_irq_set_resp resp;

        /* TC-01: Positive – valid direct IR mux route, secondary_host=A53_2 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = (uint16_t) WRAP_RM_IRQ_SRC_DEV_ID;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSetRaw(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-01: Positive: valid direct IR mux route, secondary_host=A53_2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – invalid src_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = 0xFFFFU;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSetRaw(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-02: Negative: invalid src_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqSetRaw(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 3. Sciclient_rmIrqReleaseRaw — TISCI_MSG_RM_IRQ_RELEASE (0x1001)  */
    /* Releases the route set in step 2 TC-01 above.                     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_irq_release_req req;

        /* TC-01: Positive – release the route set by IrqSetRaw TC-01 */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = (uint16_t) WRAP_RM_IRQ_SRC_DEV_ID;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqReleaseRaw(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-01: Positive: release the route set by IrqSetRaw TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – invalid src_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = 0xFFFFU;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqReleaseRaw(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-02: Negative: invalid src_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqReleaseRaw(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 4. Sciclient_rmRingCfg — TISCI_MSG_RM_RING_CFG (0x1110)           */
    /* BCDMA ring 18 is owned by MAIN_0_R5_1 (start=18, count=6).        */
    /* valid_params=0 → no-op permission-only check; no HW writes.       */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_ring_cfg_req  req;
        struct tisci_msg_rm_ring_cfg_resp resp;

        /* TC-01: Positive – valid_params=0 on owned BCDMA ring 18 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_BCDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_BCDMA_RING_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-01: Positive: valid_params=0 on owned BCDMA ring 18  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – ring not owned by this host */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_BCDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_NOT_OWNED_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-02: Negative: ring not owned by this host  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmRingCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 5. Sciclient_rmUdmapGcfgCfg — TISCI_MSG_RM_UDMAP_GCFG_CFG (0x1240) */
    /* UDMAP_GLOBAL_CONFIG is allocated to TISCI_HOST_ID_ALL.             */
    /* valid_params=0xf writes all four GCFG fields to their reset values. */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_gcfg_cfg_req  req;
        struct tisci_msg_rm_udmap_gcfg_cfg_resp resp;

        /* TC-01: Positive – PKTDMA GCFG with valid_params=0xf (reset values) */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.valid_params = 0xfU;
        req.perf_ctrl    = 0x20U;
        req.emu_ctrl     = 0x1U;
        req.psil_to      = 0x200U;
        req.rflowfwstat  = 0x0U;
        retVal = Sciclient_rmUdmapGcfgCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-01: Positive: PKTDMA GCFG with valid_params=0xf (reset values)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapGcfgCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapGcfgCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 6. Sciclient_rmUdmapTxChCfg — TISCI_MSG_RM_UDMAP_TX_CH_CFG (0x1205) */
    /* PKTDMA unmapped TX channel 10 is owned by MAIN_0_R5_1.            */
    /* valid_params=0 → permission-only check; no HW channel writes.     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_tx_ch_cfg_req  req;
        struct tisci_msg_rm_udmap_tx_ch_cfg_resp resp;

        /* TC-01: Positive – valid_params=0 on owned PKTDMA TX ch 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_PKTDMA_TX_CH_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-01: Positive: valid_params=0 on owned PKTDMA TX ch 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – channel not owned by this host */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_NOT_OWNED_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-02: Negative: channel not owned by this host  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapTxChCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 7. Sciclient_rmUdmapRxChCfg — TISCI_MSG_RM_UDMAP_RX_CH_CFG (0x1215) */
    /* PKTDMA unmapped RX channel 10 is owned by MAIN_0_R5_1.            */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_rx_ch_cfg_req  req;
        struct tisci_msg_rm_udmap_rx_ch_cfg_resp resp;

        /* TC-01: Positive – valid_params=0 on owned PKTDMA RX ch 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_PKTDMA_RX_CH_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX ch 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – channel not owned by this host */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_NOT_OWNED_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-02: Negative: channel not owned by this host  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapRxChCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 8. Sciclient_rmUdmapFlowCfg — TISCI_MSG_RM_UDMAP_FLOW_CFG (0x1230) */
    /* PKTDMA unmapped RX flow 10 is owned by MAIN_0_R5_1.               */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_flow_cfg_req  req;
        struct tisci_msg_rm_udmap_flow_cfg_resp resp;

        /* TC-01: Positive – valid_params=0 on owned PKTDMA RX flow 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = (uint16_t) WRAP_RM_PKTDMA_FLOW_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX flow 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – flow not owned by this host */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = (uint16_t) WRAP_RM_NOT_OWNED_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-02: Negative: flow not owned by this host  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.flow_index   = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapFlowCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 9. Sciclient_rmUdmapFlowSizeThreshCfg                              */
    /*    TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG (0x1231)                */
    /* PKTDMA RX flow 10 is owned by MAIN_0_R5_1; valid_params=0 no-op.  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req  req;
        struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp resp;

        /* TC-01: Positive – valid_params=0 on owned PKTDMA RX flow 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = (uint16_t) WRAP_RM_PKTDMA_FLOW_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowSizeThreshCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowSizeThreshCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX flow 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        
        /* TC-02: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.flow_index   = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowSizeThreshCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowSizeThreshCfg TC-02: Negative: invalid nav_id  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapFlowSizeThreshCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowSizeThreshCfg TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 10. Sciclient_rmPsilPair — TISCI_MSG_RM_PSIL_PAIR (0x1280)         */
    /* Pairs PKTDMA TX thread 0x100B to RX thread 0x900B on DMASS0.      */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_pair_req req;

        /* Setup: clear THREAD_EN on thread 0x100B before pairing.
         * testSciclient_rmIrqPsil (JIRA 12085) runs before this test and its
         * test_msgRmPsilWrite TC-01 sets THREAD_EN=1 (writes 0x80000000
         * to taddr=2 of thread 0x100B). PSI-L requires THREAD_EN=0 on the
         * source thread before a pair operation; leaving it enabled causes
         * the firmware to NACK the PSIL_PAIR message. */
        {
            struct tisci_msg_rm_psil_write_req wreq;
            memset(&wreq, 0, sizeof(wreq));
            wreq.valid_params = 0U;
            wreq.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
            wreq.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
            wreq.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
            wreq.data         = 0U; /* clear THREAD_EN */
            (void) Sciclient_rmPsilWrite(&wreq, SystemP_WAIT_FOREVER);
        }

        /* TC-01: Positive – pair TX thread 0x100B to RX thread 0x900B */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-01: Positive: pair TX thread 0x100B to RX thread 0x900B  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – dst_thread < 0x8000 (spec mandates NACK) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = 0x0000U;
        req.dst_thread = 0x0001U;  /* invalid: RX thread must be >= 0x8000 */
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-02: Negative: dst_thread < 0x8000 (spec mandates NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = 0xFFFFU;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilPair(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 11. Sciclient_rmPsilRead — TISCI_MSG_RM_PSIL_READ (0x1282)         */
    /* Reads thread config register taddr=0x2 of thread 0x100B.          */
    /* Pre-condition: PsilPair TC-01 has paired 0x100B → 0x900B.         */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_read_req  req;
        struct tisci_msg_rm_psil_read_resp resp;

        /* TC-01: Positive – read taddr=0x2 from thread 0x100B */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.valid_params = 0U;
        req.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        retVal = Sciclient_rmPsilRead(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-01: Positive: read taddr=0x2 from thread 0x100B  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = 0xFFFFU;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        retVal = Sciclient_rmPsilRead(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilRead(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 12. Sciclient_rmPsilWrite — TISCI_MSG_RM_PSIL_WRITE (0x1283)       */
    /* Writes thread enable bit (0x80000000) to taddr=0x2 of thread 0x100B */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_write_req req;

        /* TC-01: Positive – write thread enable pattern to taddr=0x2 */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        req.data         = WRAP_RM_PSIL_WRITE_DATA;
        retVal = Sciclient_rmPsilWrite(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-01: Positive: write thread enable pattern to taddr=0x2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = 0xFFFFU;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        req.data         = WRAP_RM_PSIL_WRITE_DATA;
        retVal = Sciclient_rmPsilWrite(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilWrite(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 13. Sciclient_rmPsilUnpair — TISCI_MSG_RM_PSIL_UNPAIR (0x1281)     */
    /* Releases the pair created by PsilPair TC-01.                       */
    /* Must execute AFTER PsilRead/Write to keep pre/post symmetry.       */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_unpair_req req;

        /* TC-01: Positive – unpair the threads paired in PsilPair TC-01 */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilUnpair(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-01: Positive: unpair the threads paired in PsilPair TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – dst_thread < 0x8000 (spec mandates NACK) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = 0x0000U;
        req.dst_thread = 0x0001U;
        retVal = Sciclient_rmPsilUnpair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-02: Negative: dst_thread < 0x8000 (spec mandates NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilUnpair(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 14. Sciclient_rmIrqSet — high-level route-find wrapper for         */
    /*     Sciclient_rmProgramInterruptRoute                              */
    /*                                                                    */
    /* NOTE: rmProgramInterruptRoute rejects IR devices as src/dst.       */
    /* Use GPIO1(78):72 → WKUP_R5FSS0_CORE0(121):36, host=A53_2(12)      */
    /* which is the same route used by the sciclient_direct reference     */
    /* test (test_sciclient_rm_irq.c).                                    */
    /* ================================================================== */
    {
        struct tisci_msg_rm_irq_set_req  irqSetReq;
        struct tisci_msg_rm_irq_set_resp irqSetResp;

        /* TC-01: Positive – GPIO1:72 → WKUP_R5FSS0_CORE0:36, host=A53_2 */
        memset(&irqSetReq, 0, sizeof(irqSetReq));
        irqSetReq.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                   TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                   TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        irqSetReq.src_id         = TISCI_DEV_GPIO1;
        irqSetReq.src_index      = 72U;
        irqSetReq.dst_id         = TISCI_DEV_WKUP_R5FSS0_CORE0;
        irqSetReq.dst_host_irq   = 36U;
        irqSetReq.secondary_host = (uint8_t)WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSet(&irqSetReq, &irqSetResp,
                                    SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSet TC-01: Positive: GPIO1:72 -> WKUP_R5FSS0_CORE0:36 host=A53_2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqSet(NULL, NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSet TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 15. Sciclient_rmIrqRelease — high-level wrapper for                */
    /*     Sciclient_rmClearInterruptRoute                                */
    /* ================================================================== */
    {
        struct tisci_msg_rm_irq_release_req irqRelReq;

        /* TC-01: Positive – release the route set in rmIrqSet TC-01 */
        memset(&irqRelReq, 0, sizeof(irqRelReq));
        irqRelReq.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                   TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                   TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        irqRelReq.src_id         = TISCI_DEV_GPIO1;
        irqRelReq.src_index      = 72U;
        irqRelReq.dst_id         = TISCI_DEV_WKUP_R5FSS0_CORE0;
        irqRelReq.dst_host_irq   = 36U;
        irqRelReq.secondary_host = (uint8_t)WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqRelease(&irqRelReq, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqRelease TC-01: Positive: release the route set in rmIrqSet TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqRelease(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqRelease TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 16. Sciclient_rmIrOutpIsFree — check if IR output is free          */
    /*     Output 0 is special: inp0_mapping defaults to 0, so output 0  */
    /*     always appears occupied.  Use output 1 for the positive test.  */
    /* ================================================================== */
    {
        /* TC-01: Positive – GPIOMUX_IR0 output 1 is free (hardware default) */
        retVal = Sciclient_rmIrOutpIsFree(WRAP_RM_IRQ_SRC_DEV_ID, 1U);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrOutpIsFree TC-01: Positive: GPIOMUX_IR0 output 1 is free (hardware default)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid device ID (0xFFFF) */
        retVal = Sciclient_rmIrOutpIsFree(0xFFFFU, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrOutpIsFree TC-02: Negative: invalid device ID (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 18. Sciclient_rmIrqTranslateIrOutput — translate IR output to      */
    /*     destination peripheral input                                   */
    /* ================================================================== */
    {
        uint16_t dstInput = 0U;

        /* TC-01: Negative – NULL dst_input pointer */
        retVal = Sciclient_rmIrqTranslateIrOutput(WRAP_RM_IRQ_SRC_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrOutput TC-01: Negative: NULL dst_input pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIrOutput(0U, 0U, 0U, &dstInput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrOutput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 19. Sciclient_rmIrqTranslateIaOutput — translate IA output to      */
    /*     destination peripheral input                                   */
    /* ================================================================== */
    {
        uint16_t dstInput = 0U;

        /* TC-01: Negative – NULL dst_input pointer */
        retVal = Sciclient_rmIrqTranslateIaOutput(WRAP_RM_NAV_INTAGGR_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIaOutput TC-01: Negative: NULL dst_input pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
       
        /* TC-02: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIaOutput(0U, 0U, 0U, &dstInput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIaOutput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 20. Sciclient_rmIrqTranslateIrqInput — translate peripheral input  */
    /*     back to IR/IA output                                           */
    /* ================================================================== */
    {
        uint16_t srcOutput = 0U;

        /* TC-01: Negative – NULL src_output pointer */
        retVal = Sciclient_rmIrqTranslateIrqInput(WRAP_RM_IRQ_DST_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrqInput TC-01: Negative: NULL src_output pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-02: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIrqInput(0U, 0U, 0U, &srcOutput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrqInput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ========================================================================== */
/* testSciclient_procBootSciclientApis — JIRA SITSW-12101                            */
/*                                                                            */
/* Covers 8 Sciclient_procBoot* high-level wrapper APIs:                     */
/*   Sciclient_procBootRequestProcessor   (TISCI_MSG_PROC_REQUEST  0xC000)   */
/*   Sciclient_procBootReleaseProcessor   (TISCI_MSG_PROC_RELEASE  0xC001)   */
/*   Sciclient_procBootHandoverProcessor  (TISCI_MSG_PROC_HANDOVER 0xC005)   */
/*   Sciclient_procBootSetProcessorCfg    (TISCI_MSG_PROC_SET_CONFIG  0xC100)*/
/*   Sciclient_procBootSetSequenceCtrl    (TISCI_MSG_PROC_SET_CONTROL 0xC101)*/
/*   Sciclient_procBootAuthAndStart       (TISCI_MSG_PROC_AUTH_BOOT  0xC120) */
/*   Sciclient_procBootGetProcessorState  (TISCI_MSG_PROC_GET_STATUS  0xC400)*/
/*   Sciclient_procBootWaitProcessorState (TISCI_MSG_PROC_WAIT_STATUS 0xC401)*/
/*                                                                            */
/* Safe processor for ownership tests: A53SS0_CORE_1 (id=0x21).              */
/* C7X256V0_CORE0 cannot be used because testSciclient_procBoot (JIRA 12095) runs   */
/* first and hands C7X to TISCI_HOST_ID_A53_2 without releasing it.  The DM  */
/* R5F host cannot re-request a processor already owned by another host.     */
/* A53SS0_CORE_1 is in the free pool (no prior test claims it; Linux has not  */
/* booted yet during this DM test).                                          */
/* SetProcessorCfg and AuthAndStart: negative-only (positive test would      */
/* require setting a running processor's boot vector, which is destructive). */
/* ========================================================================== */
void testSciclient_procBootSciclientApis(void *args)
{
    int32_t  retVal;
    int32_t  retValFailCnt = 0;
    struct tisci_msg_proc_get_status_resp procStatus;
    struct tisci_msg_proc_set_config_req  cfgReq;
    struct tisci_msg_proc_auth_boot_req   authReq;
    struct tisci_msg_proc_auth_boot_resp  authResp;

    /* ---------------------------------------------------------------------- */
    /* 1. Sciclient_procBootGetProcessorState — TISCI_MSG_PROC_GET_STATUS      */
    /* Read-only status query; no ownership required.                          */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – get state of R5FSS0_CORE0 (the running DM processor) */
    memset(&procStatus, 0, sizeof(procStatus));
    retVal = Sciclient_procBootGetProcessorState(
                 SCICLIENT_PROC_ID_R5FSS0_CORE0,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-01: Positive: get state of R5FSS0_CORE0 (the running DM processor)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    if(procStatus.processor_id != SCICLIENT_PROC_ID_R5FSS0_CORE0)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-01: Positive: processor not running is SCICLIENT_PROC_ID_R5FSS0_CORE0\r\n");
        retValFailCnt++;
    }

    /* TC-02: Positive – get state of A53SS0_CORE_1 (co-processor, readable) */
    memset(&procStatus, 0, sizeof(procStatus));
    retVal = Sciclient_procBootGetProcessorState(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-02: Positive: get state of A53SS0_CORE_1 (co-processor, readable)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-03: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootGetProcessorState(
                 0xFFU,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-03: Negative: invalid processor ID (0xFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 2. Sciclient_procBootRequestProcessor — TISCI_MSG_PROC_REQUEST          */
    /* ---------------------------------------------------------------------- */
    /* Note: AM275X maps SCICLIENT_PROC_ID_A53SS0_CORE_1 to C7X, which is     */
    /* already claimed by testSciclient_procBoot. Skip on AM275X.                    */
#if !defined(SOC_AM275X)

    /* TC-01: Positive – request A53SS0_CORE_1 (free pool; no prior test      */
    /*        claims it and Linux has not booted yet)                          */
    retVal = Sciclient_procBootRequestProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor TC-01: Positive: request A53SS0_CORE_1 (free pool)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootRequestProcessor(
                 0xFFU,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor TC-02: Negative: invalid processor ID (0xFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 3. Sciclient_procBootSetSequenceCtrl — TISCI_MSG_PROC_SET_CONTROL       */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – fire-and-forget (reqFlag=0) on owned A53SS0_CORE_1.  */
    /*        reqFlag=0 means no ACK is requested; Sciclient_service returns   */
    /*        SUCCESS immediately after enqueuing (mirrors dm_self_reset.c).   */
    retVal = Sciclient_procBootSetSequenceCtrl(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 0U,                /* control_flags_1_set   */
                 0U,                /* control_flags_1_clear */
                 0U,                /* reqFlag = fire-and-forget, no AOP */
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetSequenceCtrl TC-01: Positive: fire-and-forget (reqFlag=0) on owned A53SS0_CORE_1  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) with AOP flag → NACK */
    retVal = Sciclient_procBootSetSequenceCtrl(
                 0xFFU,
                 0U,
                 0U,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetSequenceCtrl TC-02: Negative: invalid processor ID (0xFF) with AOP flag  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 4. Sciclient_procBootReleaseProcessor — TISCI_MSG_PROC_RELEASE          */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – release A53SS0_CORE_1 (owned since section 2 TC-01) */
    retVal = Sciclient_procBootReleaseProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-01: Positive: release A53SS0_CORE_1 (owned since section 2 TC-01)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – release again (caller no longer owner) → NACK */
    retVal = Sciclient_procBootReleaseProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-02: Negative: release again (caller no longer owner)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootReleaseProcessor(
                 0xFFU,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-03: Negative: invalid processor ID (0xFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 5. Sciclient_procBootHandoverProcessor — TISCI_MSG_PROC_HANDOVER        */
    /* ---------------------------------------------------------------------- */

    /* Setup: re-acquire A53SS0_CORE_1 (released in section 4 TC-01) */
    retVal = Sciclient_procBootRequestProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor Setup: re-acquire A53SS0_CORE_1 (released in section 4 TC-01)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-01: Positive – handover A53_CORE1 to WRAP_PROCBOOT_HANDOVER_HOST,   */
    /*        a host different from whichever host is running this test      */
    retVal = Sciclient_procBootHandoverProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 WRAP_PROCBOOT_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-01: Positive: handover A53_CORE1 to WRAP_PROCBOOT_HANDOVER_HOST  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootHandoverProcessor(
                 0xFFU,
                 WRAP_PROCBOOT_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-02: Negative: invalid processor ID (0xFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – attempt handover when no longer owner               */
    /*        (ownership transferred away in TC-01) → NACK                   */
    retVal = Sciclient_procBootHandoverProcessor(
                 SCICLIENT_PROC_ID_A53SS0_CORE_1,
                 WRAP_PROCBOOT_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-03: Negative: attempt handover when no longer owner  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

#endif /* !SOC_AM275X */

    /* ---------------------------------------------------------------------- */
    /* 6. Sciclient_procBootSetProcessorCfg — TISCI_MSG_PROC_SET_CONFIG        */
    /* NOTE: Setting the boot vector of a running processor is destructive on  */
    /* warm reset. Only negative tests are performed here.                     */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Negative – NULL configReq pointer → SystemP_FAILURE */
    retVal = Sciclient_procBootSetProcessorCfg(NULL, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetProcessorCfg TC-01: Negative: NULL configReq pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-02: Negative – caller does not own A53_CORE1 (handed over) → NACK */
    memset(&cfgReq, 0, sizeof(cfgReq));
    cfgReq.processor_id         = SCICLIENT_PROC_ID_A53SS0_CORE_1;
    cfgReq.bootvector_lo        = 0x0U;
    cfgReq.bootvector_hi        = 0x0U;
    cfgReq.config_flags_1_set   = 0U;
    cfgReq.config_flags_1_clear = 0U;
    retVal = Sciclient_procBootSetProcessorCfg(&cfgReq, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetProcessorCfg TC-02: Negative: caller does not own A53_CORE1 (handed over)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 7. Sciclient_procBootAuthAndStart — TISCI_MSG_PROC_AUTH_BOOT            */
    /* NOTE: A valid HS-FS signed x509 certificate is required for a positive  */
    /* test. Only negative tests are performed here.                           */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Negative – NULL authBootCfg pointer → SystemP_FAILURE */
    retVal = Sciclient_procBootAuthAndStart(NULL, NULL, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootAuthAndStart TC-01: Negative: NULL authBootCfg pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-02: Negative – zero certificate address (0x0) → NACK (cert parse fails) */
    memset(&authReq,  0, sizeof(authReq));
    memset(&authResp, 0, sizeof(authResp));
    authReq.certificate_address_lo = 0x0U;
    authReq.certificate_address_hi = 0x0U;
    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootAuthAndStart TC-02: Negative: zero certificate address (0x0)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 8. Sciclient_procBootWaitProcessorState — TISCI_MSG_PROC_WAIT_STATUS    */
    /* ---------------------------------------------------------------------- */
    /* Note: AM275X maps SCICLIENT_PROC_ID_A53SS0_CORE_0 to C7X, which is     */
    /* already claimed by testSciclient_procBoot. Skip on AM275X.                    */
#if !defined(SOC_AM275X)

    /* TC-01: Positive – A53SS0_CORE_0 is not in WFE (bit0) or WFI (bit1) in */
    /*        a running system; clr_any_wait=3 is immediately satisfied on    */
    /*        the first iteration (status bits already clear).                 */
    retVal = Sciclient_procBootWaitProcessorState(
                 SCICLIENT_PROC_ID_A53SS0_CORE_0,
                 1U,     /* num_match_iterations     */
                 1U,     /* delay_per_iteration_us   */
                 0U,     /* status_flags_1_set_all_wait */
                 0U,     /* status_flags_1_set_any_wait */
                 0U,     /* status_flags_1_clr_all_wait */
                 3U,     /* status_flags_1_clr_any_wait: bit0=WFE, bit1=WFI */
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-01: Positive: A53SS0_CORE_0 not in WFE/WFI, clr_any=3 AOP  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – TISCI_MSG_FLAG_SEC reqFlag → NACK */
    retVal = Sciclient_procBootWaitProcessorState(
                 SCICLIENT_PROC_ID_A53SS0_CORE_0,
                 1U,
                 1U,
                 0U,
                 0U,
                 0U,
                 3U,
                 TISCI_MSG_FLAG_SEC,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-02: Negative: TISCI_MSG_FLAG_SEC reqFlag  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootWaitProcessorState(
                 0xFFU,
                 1U,
                 1U,
                 0U,
                 0U,
                 0U,
                 3U,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-03: Negative: invalid processor ID (0xFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

#endif /* !SOC_AM275X */

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testSciclient_boardCfgApis
 *
 * Covers board-configuration wrappers (positive + negative):
 *   1. Sciclient_boardCfgPm  — PM board config
 *
 * NULL parameter applies the default (already-loaded) config → SUCCESS.
 * ========================================================================== */
void testSciclient_boardCfgApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfgPm                                               */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default PM board config */
    retVal = Sciclient_boardCfgPm(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_boardCfgPm TC-01: Positive: NULL re-applies default PM board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid devGrp 0x70 */
    {
        Sciclient_BoardCfgPrms_t brdCfg;
        memset(&brdCfg, 0, sizeof(brdCfg));
        brdCfg.devGrp = 0x70U;
        retVal = Sciclient_boardCfgPm(&brdCfg);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfgPm TC-02: Negative: invalid devGrp 0x70  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfgRm                                               */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default RM board config */
    retVal = Sciclient_boardCfgRm(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_boardCfgRm TC-01: Positive: NULL re-applies default RM board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testSciclient_dkekApis
 *
 * Covers SA2UL DKEK (Derived KEK) wrappers (positive + negative):
 *   1. Sciclient_setDKEK      — TISCI_MSG_SA2UL_SET_DKEK
 *   2. Sciclient_getDKEK      — TISCI_MSG_SA2UL_GET_DKEK
 *   3. Sciclient_releaseDKEK  — TISCI_MSG_SA2UL_RELEASE_DKEK
 *
 * Positive tests use sa2ul_instance=0 with a valid KDF label/context.
 * NULL parameter tests verify graceful failure.
 * ========================================================================== */
void testSciclient_dkekApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_setDKEK                                                  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_set_dkek_req  setReq;
        struct tisci_msg_sa2ul_set_dkek_resp setResp;
        char *label = "Secure storage key";
        const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

        /* TC-01: Positive – set DKEK with valid label/context */
        memset(&setReq, 0, sizeof(setReq));
        setReq.hdr.type  = TISCI_MSG_SA2UL_SET_DKEK;
        setReq.hdr.seq   = 0;
        setReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        setReq.sa2ul_instance = 0;
        memcpy(&setReq.kdf_label_and_context[0], label, strlen(label));
        setReq.kdf_label_len = (uint8_t)strlen(label);
        memcpy(&setReq.kdf_label_and_context[setReq.kdf_label_len],
               context, sizeof(context));
        setReq.kdf_context_len = sizeof(context);
        retVal = Sciclient_setDKEK(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_setDKEK TC-01: Positive: set DKEK with valid label/context  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – NULL req pointer */
        retVal = Sciclient_setDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_setDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_getDKEK                                                  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_get_dkek_req  getReq;
        struct tisci_msg_sa2ul_get_dkek_resp getResp;
        char *label = "Secure storage key";
        const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

        /* TC-01: Positive – get DKEK (after setDKEK above) */
        memset(&getReq, 0, sizeof(getReq));
        memset(&getResp, 0, sizeof(getResp));
        getReq.hdr.type  = TISCI_MSG_SA2UL_GET_DKEK;
        getReq.hdr.seq   = 0;
        getReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        getReq.sa2ul_instance = 0;
        memcpy(&getReq.kdf_label_and_context[0], label, strlen(label));
        getReq.kdf_label_len = (uint8_t)strlen(label);
        memcpy(&getReq.kdf_label_and_context[getReq.kdf_label_len],
               context, sizeof(context));
        getReq.kdf_context_len = sizeof(context);
        retVal = Sciclient_getDKEK(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getDKEK TC-01: Positive: get DKEK (after setDKEK above)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – NULL req pointer */
        retVal = Sciclient_getDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_releaseDKEK                                              */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_release_dkek_req  relReq;
        struct tisci_msg_sa2ul_release_dkek_resp relResp;

        /* TC-01: Positive – release DKEK set earlier */
        memset(&relReq, 0, sizeof(relReq));
        relReq.hdr.type  = TISCI_MSG_SA2UL_RELEASE_DKEK;
        relReq.hdr.seq   = 0;
        relReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        relReq.sa2ul_instance = 0;
        retVal = Sciclient_releaseDKEK(&relReq, &relResp,
                                       SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_releaseDKEK TC-01: Positive: release DKEK set earlier  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Negative – NULL req pointer */
        retVal = Sciclient_releaseDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_releaseDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testSciclient_initDeinit
 *
 * Covers Sciclient_init():
 *   Sciclient_init(pCfgPrms) — intended to be ref-counted (only perform the
 *   actual initialization work the first time the internal ref count
 *   transitions to 1, per sciclient.c). In practice, on this platform a
 *   matched Sciclient_deinit() call (even when the ref count should remain
 *   >= 1 because ti_drivers_config.c holds a reference) was observed to
 *   tear down the handle for real — unregistering interrupts and
 *   destructing semaphores — which breaks every subsequent RUN_TEST in
 *   this suite that depends on Sciclient_service() (verified experimentally
 *   on am62ax-sk MCU R5F0: rmGetResourceRange, rmIrqSetRaw, rmRingCfg,
 *   rmUdmap*, rmPsil*, lpm* all started returning SystemP_FAILURE after
 *   Sciclient_deinit() was called once, matched or not).
 *
 * Sciclient_deinit() is therefore intentionally NOT exercised here — it is
 * NOT SAFE to call in a running system once other drivers/tests depend on
 * Sciclient being initialized. Only the (idempotent, always-safe) extra
 * Sciclient_init() call is tested.
 * ========================================================================== */

void testSciclient_initDeinit(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* This build's Sciclient_init() takes the calling core's CSL_CORE_ID_*
     * (see source/drivers/sciclient.h), matching the coreId passed by the
     * generated ti_drivers_config.c for this core - NOT a config pointer. */
#if defined(TEST_CORE_MCU_R5F)
#define TEST_SCICLIENT_INIT_CORE_ID     CSL_CORE_ID_MCU_R5FSS0_0
#elif defined(TEST_CORE_MCU_M4F)
/* AM62X wakeup-domain M4F core. */
#define TEST_SCICLIENT_INIT_CORE_ID     CSL_CORE_ID_M4FSS0_0
#elif defined(CORE_A53)
#define TEST_SCICLIENT_INIT_CORE_ID     CSL_CORE_ID_A53SS0_0
#elif defined(CORE_C7)
#define TEST_SCICLIENT_INIT_CORE_ID     CSL_CORE_ID_C75SS0_0
#elif defined(SOC_AM275X)
/* AM275X has no MCU-domain R5F; its r5fss0-0/0-1/1-0/1-1 builds define
 * none of TEST_CORE_MCU_R5F/CORE_A53/CORE_C7 (project_am275x.js only adds
 * SOC_AM275X for r5fss* cpus - there is no per-instance core macro). By
 * the time this test runs, Sciclient is already initialized by
 * ti_drivers_config.c, so Sciclient_init() only hits its early-return
 * "already initialized" branch and never actually uses this coreId value
 * - any valid CSL_CORE_ID_* is safe here. */
#define TEST_SCICLIENT_INIT_CORE_ID     CSL_CORE_ID_R5FSS0_0
#else
#error "Unknown core - add TEST_SCICLIENT_INIT_CORE_ID mapping for this core"
#endif

    /* TC-1: Positive: Sciclient_init(coreId) while already initialized —
     * increments the ref count and uses default config params.
     * Always returns SystemP_SUCCESS, and is safe to call repeatedly since
     * it does not repeat the one-time init work while already initialized. */
    retVal = Sciclient_init(TEST_SCICLIENT_INIT_CORE_ID);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_init TC-1: Positive: re-init while already initialized  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* Confirm sciclient is still functional after the extra init. */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_init TC-1 functional verify: Sciclient_getVersionCheck  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* NOTE: Sciclient_loadFirmware(),
 * CSL_SecProxyCfg and CSL_SEC_PROXY_RT_THREAD_STATUS() are part of the ROM
 * bootloader API (sciclient_direct/sciclient_romMessages.h) and are not
 * part of the Sciclient device-manager API exercised by this test
 * project, so they are not declared/available in this build. */


 #if !(defined(SOC_AM275X) || defined(CORE_A53))
/* ==========================================================================
 * testSciclient_lpmSciclient
 *
 * Covers all 8 Sciclient_lpm* wrappers (positive + negative combinations):
 *   1. Sciclient_lpmSetModuleConstraint   TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT  (0x0309)
 *   2. Sciclient_lpmGetModuleConstraint   TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT  (0x030B)
 *   3. Sciclient_lpmSetLatencyConstraint  TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT (0x030A)
 *   4. Sciclient_lpmGetLatencyConstraint  TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT (0x030C)
 *   5. Sciclient_lpmGetNextSysMode        TISCI_MSG_LPM_GET_NEXT_SYS_MODE      (0x030D)
 *   6. Sciclient_lpmGetNextHostState      TISCI_MSG_LPM_GET_NEXT_HOST_STATE    (0x030E)
 *   7. Sciclient_lpmGetWakeReason         TISCI_MSG_LPM_WAKE_REASON            (0x0306)
 *   8. Sciclient_lpmSendPrepareSleepMessage TISCI_MSG_PREPARE_SLEEP            (0x0300)
 *
 * NOTE — timeout=0 negative tests are NOT included:
 * In the ENABLE_SCICLIENT_DIRECT build (DM R5F), Sciclient_service()
 * processes TISCI messages locally and synchronously — there is no IPC
 * mailbox round-trip.  The timeout parameter is never checked because the
 * request completes inline before any wait.  Therefore timeout=0 returns
 * SUCCESS for every valid request.  Timeout-based negative tests are only
 * meaningful on remote cores that use the mailbox IPC path.
 * ========================================================================== */
void testSciclient_lpmSciclient(void *args)
{
    int32_t  retVal;
    int32_t  retValFailCnt = 0;
    uint8_t  moduleState;
    uint8_t  sysMode;
    uint8_t  hostState;
    uint16_t latency;
    uint8_t  latState;
    uint32_t wakeSource;
    uint64_t wakeTimestamp;
    uint8_t  wakePin;
    uint8_t  wakeMode;

    /* ---------------------------------------------------------------------- */
    /* 1. Sciclient_lpmSetModuleConstraint                                     */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – set constraint on a valid module */
        retVal = Sciclient_lpmSetModuleConstraint(TEST_DEVICE_ID,
                                                  TISCI_MSG_VALUE_STATE_SET,
                                                  SystemP_WAIT_FOREVER);
    
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-01: Positive: set constraint on a valid module  retVal=%d expected=%d fail count %d\r\n", retVal, SystemP_SUCCESS,retValFailCnt);
            retValFailCnt++;
        }
        
        /* TC-02: Positive – clear constraint on the same module */
        retVal = Sciclient_lpmSetModuleConstraint(TEST_DEVICE_ID,
                                                  TISCI_MSG_VALUE_STATE_CLEAR,
                                                  SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-02: Positive: clear constraint on the same module  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
 
        /* TC-03: Negative – invalid module ID (0xFFFF), DM NACKs */
        retVal = Sciclient_lpmSetModuleConstraint(0xFFFFU,
                                                  TISCI_MSG_VALUE_STATE_SET,
                                                  SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-03: Negative: invalid module ID (0xFFFF), DM NACKs  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Negative – invalid module ID (0xFFFE), DM NACKs */
        retVal = Sciclient_lpmSetModuleConstraint(0xFFFEU,
                                                  TISCI_MSG_VALUE_STATE_SET,
                                                  SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-04: Negative: invalid module ID (0xFFFE), DM NACKs  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 2. Sciclient_lpmGetModuleConstraint                                     */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – read back constraint (cleared in Set TC-02 above) */
        moduleState = 0xFFU; /* sentinel */
        retVal = Sciclient_lpmGetModuleConstraint(TEST_DEVICE_ID,
                                                  &moduleState,
                                                  SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetModuleConstraint TC-01: Positive: read back constraint (cleared in Set TC-02 above)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        /* TC-02: Negative – invalid module ID (0xFFFF) */
        retVal = Sciclient_lpmGetModuleConstraint(0xFFFFU,
                                                  &moduleState,
                                                  SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetModuleConstraint TC-02: Negative: invalid module ID (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-03: Negative – invalid module ID (0xFFFE) */
        retVal = Sciclient_lpmGetModuleConstraint(0xFFFEU,
                                                  &moduleState,
                                                  SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetModuleConstraint TC-03: Negative: invalid module ID (0xFFFE)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-04: Positive – set then get (verify round-trip) */
        retVal = Sciclient_lpmSetModuleConstraint(TEST_DEVICE_ID,
                                                  TISCI_MSG_VALUE_STATE_SET,
                                                  SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-04: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        moduleState = 0xFFU;
        retVal = Sciclient_lpmGetModuleConstraint(TEST_DEVICE_ID,
                                                  &moduleState,
                                                  SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetModuleConstraint TC-04: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        /* Clean up: clear the constraint */
        retVal = Sciclient_lpmSetModuleConstraint(TEST_DEVICE_ID,
                                                  TISCI_MSG_VALUE_STATE_CLEAR,
                                                  SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetModuleConstraint TC-04: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }
    /* ---------------------------------------------------------------------- */
    /* 3. Sciclient_lpmSetLatencyConstraint                                    */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – set latency constraint to 1000 ms */
        retVal = Sciclient_lpmSetLatencyConstraint(1000U,
                                                   TISCI_MSG_VALUE_STATE_SET,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-01: Positive: set latency constraint to 1000 ms  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Positive – clear latency constraint */
        retVal = Sciclient_lpmSetLatencyConstraint(0U,
                                                   TISCI_MSG_VALUE_STATE_CLEAR,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-02: Positive: clear latency constraint  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-03: Positive – set with max latency (0xFFFF) */
        retVal = Sciclient_lpmSetLatencyConstraint(0xFFFFU,
                                                   TISCI_MSG_VALUE_STATE_SET,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-03: Positive: set with max latency (0xFFFF)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* Clean up: clear the constraint */
        retVal = Sciclient_lpmSetLatencyConstraint(0U,
                                                   TISCI_MSG_VALUE_STATE_CLEAR,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-03: Positive: set with max latency (0xFFFF)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 4. Sciclient_lpmGetLatencyConstraint                                    */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – read back latency (cleared above, expect state=0) */
        latency  = 0xFFFFU; /* sentinel */
        latState = 0xFFU;
        retVal = Sciclient_lpmGetLatencyConstraint(&latency,
                                                   &latState,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetLatencyConstraint TC-01: Positive: read back latency (cleared above, expect state=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-02: Positive – set then get (verify round-trip) */
        retVal = Sciclient_lpmSetLatencyConstraint(500U,
                                                   TISCI_MSG_VALUE_STATE_SET,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-02: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        latency  = 0xFFFFU;
        latState = 0xFFU;
        retVal = Sciclient_lpmGetLatencyConstraint(&latency,
                                                   &latState,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetLatencyConstraint TC-02: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* Clean up: clear the constraint */
        retVal = Sciclient_lpmSetLatencyConstraint(0U,
                                                   TISCI_MSG_VALUE_STATE_CLEAR,
                                                   SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSetLatencyConstraint TC-02: Positive: set then get (verify round-trip)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 5. Sciclient_lpmGetNextSysMode                                          */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – DM returns NOT_SELECTED (0xFE) when no LPM      */
        /*        sequence is in progress.                                     */
        sysMode = 0x00U;
        retVal = Sciclient_lpmGetNextSysMode(SystemP_WAIT_FOREVER, &sysMode);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetNextSysMode TC-01: Positive: DM returns NOT_SELECTED (0xFE) when no LPM  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 6. Sciclient_lpmGetNextHostState                                        */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – DM returns state of the calling host */
        hostState = 0xFFU;
        retVal = Sciclient_lpmGetNextHostState(SystemP_WAIT_FOREVER, &hostState);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetNextHostState TC-01: Positive: DM returns state of the calling host  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 7. Sciclient_lpmGetWakeReason                                           */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Positive – DM returns last wake reason; when no prior LPM  */
        /*        entry has occurred the source is INVALID (0xFF), which is   */
        /*        still a valid SUCCESS response.                              */
        retVal = Sciclient_lpmGetWakeReason(&wakeSource, &wakeTimestamp,
                                            &wakePin, &wakeMode,
                                            SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmGetWakeReason TC-01: Positive: DM returns last wake reason; when no prior LPM  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* 8. Sciclient_lpmSendPrepareSleepMessage                                 */
    /* TISCI_MSG_PREPARE_SLEEP is NACK'd by DM for the modes below because    */
    /* the system is not in a suspend sequence.  Only modes that return NACK  */
    /* immediately are safe to test here.                                     */
    /*                                                                        */
    /* DO NOT test PARTIAL_IO, STANDBY, or other modes that AM62DX DM        */
    /* actually accepts: those modes trigger a real sleep entry and the       */
    /* system will hang rather than returning from the call.                  */
    /* ---------------------------------------------------------------------- */
    {
        /* TC-01: Negative – DEEP_SLEEP (DM NACK, not in sleep sequence) */
        retVal = Sciclient_lpmSendPrepareSleepMessage(
                     TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP,
                     SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSendPrepareSleepMessage TC-01: Negative: DEEP_SLEEP (DM NACK, not in sleep sequence)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-02: Negative – MCU_ONLY mode */
        retVal = Sciclient_lpmSendPrepareSleepMessage(
                     TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY,
                     SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSendPrepareSleepMessage TC-02: Negative: MCU_ONLY mode  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
        /* TC-03: Negative – IO_ONLY_PLUS_DDR mode */
        retVal = Sciclient_lpmSendPrepareSleepMessage(
                     TISCI_MSG_VALUE_SLEEP_MODE_IO_ONLY_PLUS_DDR,
                     SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_lpmSendPrepareSleepMessage TC-03: Negative: IO_ONLY_PLUS_DDR mode  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}
#endif /* !SOC_AM275X */
