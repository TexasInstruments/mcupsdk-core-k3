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

/**
 *  \file am275x-evm/test_device_manager_val.h
 *
 *  \brief AM275X-EVM specific RM test values for the device manager UT.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am275x/tisci_devices.h
 *    - source/drivers/sciclient/soc/am275x/sciclient_defaultBoardcfg_rm.c
 *
 *  The DM firmware runs as SCICLIENT_CONTEXT_NONSEC (index 1), mapping to
 *  TISCI_HOST_ID_WKUP_0_R5_1.  All RM resource indices below correspond to
 *  allocations owned by that host.
 *
 *  Note: TISCI_HOST_ID_A53_2 is aliased to TISCI_HOST_ID_C7X_1_0 on AM275X,
 *  which owns MAIN_GPIOMUX_INTROUTER0 IR_OUTPUT[0..7].
 */

#ifndef AM275X_EVM_TEST_DEVICE_MANAGER_VAL_H_
#define AM275X_EVM_TEST_DEVICE_MANAGER_VAL_H_

/* ========================================================================== */
/*                             RM Navigator Subsystem device IDs              */
/* ========================================================================== */

#define TEST_RM_NAV_BCDMA_DEV_ID     TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define TEST_RM_NAV_PKTDMA_DEV_ID    TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define TEST_RM_NAV_INTAGGR_DEV_ID   TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */

/* ========================================================================== */
/*                             BCDMA ring / channel indices                   */
/* ========================================================================== */

/* sciclient_defaultBoardcfg_rm.c:
 *   BCDMA_RING_BLOCK_COPY_CHAN start=15, count=2
 *   BCDMA_BLOCK_COPY_CHAN      start=15, count=2  */
#define TEST_RM_BCDMA_RING_IDX       (15U)
#define TEST_RM_BCDMA_TX_CH_IDX      (15U)
#define TEST_RM_BCDMA_RX_CH_IDX      (15U)

/* ========================================================================== */
/*                             PKTDMA channel / flow indices                  */
/* ========================================================================== */

/* sciclient_defaultBoardcfg_rm.c:
 *   PKTDMA_UNMAPPED_TX_CHAN       start=10, count=2
 *   PKTDMA_UNMAPPED_RX_CHAN       start=10, count=2
 *   PKTDMA_FLOW_UNMAPPED_RX_CHAN  start=10, count=2  */
#define TEST_RM_PKTDMA_TX_CH_IDX     (10U)
#define TEST_RM_PKTDMA_RX_CH_IDX     (10U)
#define TEST_RM_PKTDMA_FLOW_IDX      (10U)

/* ========================================================================== */
/*                             INTAGGR (interrupt aggregator) indices         */
/* ========================================================================== */

/* sciclient_defaultBoardcfg_rm.c:
 *   IA_VINT           start=45,   count=35
 *   GLOBAL_EVENT_SEVT start=1171, count=256  */
#define TEST_RM_IA_VINT_IDX          (45U)
#define TEST_RM_GLOBAL_SEVT_IDX      (1171U)

/* ========================================================================== */
/*                             BCDMA OES event trigger index                  */
/* ========================================================================== */

/* OES event ID for block-copy channel N data completion:
 *   IA_BCDMA_CHAN_DATA_COMPLETION_OES starts at 8704; channel 15 -> 8704+15. */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8719U)

/* ========================================================================== */
/*                             PSI-L thread IDs                               */
/* ========================================================================== */

/* PKTDMA PSI-L: TX channel 11 = 0x100B, RX channel 11 = 0x900B
 * (WKUP_0_R5_1 owns channels 10–11). */
#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x100BU)
#define TEST_RM_PSIL_DST_THREAD      (0x900BU)
#define TEST_RM_PSIL_TADDR           (0x0002U)
#define TEST_RM_PSIL_WRITE_DATA      (0x80000000U)

/* ========================================================================== */
/*                             IRQ routing parameters                         */
/* ========================================================================== */

/* MAIN_GPIOMUX_INTROUTER0; C7X_1_0 (= TISCI_HOST_ID_A53_2 alias) owns [0..7].
 * The alias is defined here so the shared RM test code can use the same
 * TISCI_HOST_ID_A53_2 symbol on both AM62DX and AM275X. */
#define TEST_RM_IRQ_SRC_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_SRC_INDEX        (10U)
#define TEST_RM_IRQ_DST_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_A53_2               /* = C7X_1_0 via alias */
#define TISCI_HOST_ID_A53_2          TISCI_HOST_ID_C7X_1_0

/* ========================================================================== */
/*                             PM / Clock test constants                      */
/* ========================================================================== */

/* Device and clock IDs for PM clock/device management tests.
 * Source: source/drivers/sciclient/include/tisci/am275x/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am275x/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_WKUP_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_WKUP_UART0_FCLK_CLK

/* ========================================================================== */
/*                             Processor boot / host ID                       */
/* ========================================================================== */

/* AM275X uses PROC_ID_* names (no SCICLIENT_ prefix); alias them to the
 * SCICLIENT_PROC_ID_* names used by the shared test code. */
#define SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0  (PROC_ID_C7X256V0_C7XV_CORE_0)
#define SCICLIENT_PROC_ID_R5FSS0_CORE0           (PROC_ID_R5FSS0_CORE0)

/* AM275X has no A53 cluster; TISCI_HOST_ID_C7X_1_0 serves as the
 * handover target.  TISCI_HOST_ID_A53_2 is already aliased above for RM
 * tests; define the generic TISCI_HOST_ID alias used by LPM tests. */
#define TISCI_HOST_ID               TISCI_HOST_ID_C7X_1_0

/* Co-processor used for proc-boot tests (REQUEST/RELEASE/HANDOVER/SET_CONTROL).
 * Must be a processor not actively used by the DM firmware itself. */
#define TEST_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0

/* Clock with a switchable parent mux — used in GET/SET_CLOCK_PARENT positive tests.
 * TIMER0 TIMER_TCLK_CLK (clk=2) has multiple muxed parents on AM62DX and AM275X. */
#define TEST_CLK_PARENT_DEV_ID  TISCI_DEV_TIMER0               /* 36U */
#define TEST_CLK_PARENT_CLK_ID  TISCI_DEV_TIMER0_TIMER_TCLK_CLK /* 2U */

/* ========================================================================== */
/*                             Pre-signed R5 boot certificate                 */
/* ========================================================================== */

/* Pre-signed R5 boot certificate for PROC_AUTH_BOOT positive test.
 * test_sciclient_r5_cl0_c0_image.h is on the include path via
 * -I.../sciclient_direct/am62dx-evm/ in the makefile.
 * Define TEST_PROC_AUTH_BOOT_CERT_AVAILABLE to enable TC-01. */
#define TEST_PROC_AUTH_BOOT_CERT_AVAILABLE
static const uint8_t r5_cl0_c0_binary_hs[] = {
#include "test_sciclient_r5_cl0_c0_image.h"
};


/* Alias for C7X256V1 using the SCICLIENT_ prefix convention */
#define SCICLIENT_PROC_ID_C7X256V1_C7XV_CORE_0  (PROC_ID_C7X256V1_C7XV_CORE_0)

/* ========================================================================== */
/*                         Wrapper test resource indices                      */
/* ========================================================================== */

#define WRAP_RM_NAV_BCDMA_DEV_ID    TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define WRAP_RM_NAV_PKTDMA_DEV_ID   TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define WRAP_RM_NAV_INTAGGR_DEV_ID  TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */
#define WRAP_RM_BCDMA_RING_IDX      (15U)
#define WRAP_RM_PKTDMA_TX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (10U)
#define WRAP_RM_IRQ_SRC_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_SRC_INDEX       (10U)
#define WRAP_RM_IRQ_DST_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_DST_HOST_IRQ    (0U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_A53_2                 /* = C7X_1_0 via alias */
#define WRAP_RM_PSIL_NAV_ID         TISCI_DEV_DMASS0                    /* 25U */
#define WRAP_RM_PSIL_SRC_THREAD     (0x100BU)
#define WRAP_RM_PSIL_DST_THREAD     (0x900BU)
#define WRAP_RM_PSIL_TADDR          (0x0002U)
#define WRAP_RM_PSIL_WRITE_DATA     (0x80000000U)

/* Co-processor for proc-boot ownership tests (request/release/handover).
 * C7X256V0 is claimed by testDM_procBoot; use C7X256V1 which is free. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V1_C7XV_CORE_0

/* Host ID used as handover target in proc-boot handover tests.
 * On AM275X there is no A53 cluster; C7X_1_0 serves as the handover target
 * (aliased to TISCI_HOST_ID_A53_2 above for RM test compatibility). */
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_C7X_1_0

#endif /* AM275X_EVM_TEST_DEVICE_MANAGER_VAL_H_ */
