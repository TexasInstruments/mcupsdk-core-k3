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
 *  \file am62dx-evm/test_device_manager_val.h
 *
 *  \brief AM62DX-EVM specific RM test values for the device manager UT.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am62dx/tisci_devices.h
 *    - source/drivers/sciclient/soc/am62dx/sciclient_defaultBoardcfg_rm.c
 *
 *  The DM firmware (r5fss0-0) runs as SCICLIENT_CONTEXT_NONSEC (index 1),
 *  which maps to TISCI_HOST_ID_MAIN_0_R5_1.  All RM resource indices below
 *  correspond to allocations owned by that host.
 */

#ifndef AM62DX_EVM_TEST_DEVICE_MANAGER_VAL_H_
#define AM62DX_EVM_TEST_DEVICE_MANAGER_VAL_H_

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
 *   BCDMA_RING_BLOCK_COPY_CHAN start=18, count=6
 *   BCDMA_BLOCK_COPY_CHAN      start=18, count=6
 *   BCDMA_SPLIT_TR_RX_CHAN     start=18, count=6
 *   BCDMA_SPLIT_TR_TX_CHAN     start=44, count=6  */
#define TEST_RM_BCDMA_RING_IDX       (18U)
/* TISCI_MSG_RM_UDMAP_TX_CH_CFG validates against BCDMA_SPLIT_TR_TX_CHAN. */
#define TEST_RM_BCDMA_TX_CH_IDX      (44U)
#define TEST_RM_BCDMA_RX_CH_IDX      (18U)

/* ========================================================================== */
/*                             PKTDMA channel / flow indices                  */
/* ========================================================================== */

/* sciclient_defaultBoardcfg_rm.c:
 *   PKTDMA_UNMAPPED_TX_CHAN       start=10, count=3
 *   PKTDMA_UNMAPPED_RX_CHAN       start=10, count=3
 *   PKTDMA_FLOW_UNMAPPED_RX_CHAN  start=10, count=3  */
#define TEST_RM_PKTDMA_TX_CH_IDX     (10U)
#define TEST_RM_PKTDMA_RX_CH_IDX     (10U)
#define TEST_RM_PKTDMA_FLOW_IDX      (10U)

/* ========================================================================== */
/*                             INTAGGR (interrupt aggregator) indices         */
/* ========================================================================== */

/* sciclient_defaultBoardcfg_rm.c:
 *   IA_VINT           start=44,  count=35
 *   GLOBAL_EVENT_SEVT start=526, count=256  */
#define TEST_RM_IA_VINT_IDX          (44U)
#define TEST_RM_GLOBAL_SEVT_IDX      (526U)

/* ========================================================================== */
/*                             BCDMA OES event trigger index                  */
/* ========================================================================== */

/* OES event ID for block-copy channel N data completion:
 *   TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START (8704) + N.
 * Board cfg: IA_BCDMA_CHAN_DATA_COMPLETION_OES start=8704 count=32 HOST_ID_ALL.
 * Channel 18 (owned by MAIN_0_R5_1): 8704 + 18 = 8722. */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8722U)

/* ========================================================================== */
/*                             PSI-L thread IDs                               */
/* ========================================================================== */

/* DMASS0 PKTDMA PSI-L system thread map (from test_sciclient_rm_irq.c):
 *   src=0x100B (PKTDMA TX thread), dst=0x900B (PKTDMA RX thread).
 *   nav_id = TISCI_DEV_DMASS0 (25U) selects the DMASS0 PSI-L config proxy. */
#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x100BU)                       /* PKTDMA TX thread */
#define TEST_RM_PSIL_DST_THREAD      (0x900BU)                       /* PKTDMA RX thread (>= 0x8000) */
#define TEST_RM_PSIL_TADDR           (0x0002U)                       /* Thread config register offset */
#define TEST_RM_PSIL_WRITE_DATA      (0x80000000U)                   /* Thread enable bit pattern */

/* ========================================================================== */
/*                             IRQ routing parameters                         */
/* ========================================================================== */

/* Board cfg: MAIN_GPIOMUX_INTROUTER0 IR_OUTPUT[0..15] allocated to
 * TISCI_HOST_ID_A53_2 (12).  DM proxies IRQ routing via secondary_host=A53_2.
 * Matches reference: test_sciclient_rm_irq.c rmIrqSetCfg
 *   (src_id=3, src_index=10, dst_id=3, dst_host_irq=0,
 *    valid_params=0x80000003, secondary_host=12). */
#define TEST_RM_IRQ_SRC_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_SRC_INDEX        (10U)
#define TEST_RM_IRQ_DST_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_A53_2                 /* 12U */

/* ========================================================================== */
/*                             PM / Clock test constants                      */
/* ========================================================================== */

/* Device and clock IDs for PM clock/device management tests.
 * Source: source/drivers/sciclient/include/tisci/am62dx/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am62dx/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_MCU_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_MCU_UART0_FCLK_CLK

/* Clock with a switchable parent mux — used in GET/SET_CLOCK_PARENT positive tests.
 * TIMER0 TIMER_TCLK_CLK (clk=2) has multiple muxed parents on AM62DX and AM275X. */
#define TEST_CLK_PARENT_DEV_ID  TISCI_DEV_TIMER0               /* 36U */
#define TEST_CLK_PARENT_CLK_ID  TISCI_DEV_TIMER0_TIMER_TCLK_CLK /* 2U */
#define TEST_DM_CLK_SSC         1

/* ========================================================================== */
/*                             Processor boot / host ID                       */
/* ========================================================================== */

/* Host ID used for processor handover in LPM and procboot tests.
 * On AM62DX the target hand-over host is the A53 cluster (host 12). */
#define TISCI_HOST_ID               TISCI_HOST_ID_A53_2

/* Co-processor used for proc-boot tests (REQUEST/RELEASE/HANDOVER/SET_CONTROL).
 * Must be a processor not actively used by the DM firmware itself. */
#define TEST_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0

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

/* ========================================================================== */
/*                             Firewall capability flags                      */
/* ========================================================================== */

/* fwl_id=0 is a valid, accessible firewall on AM62DX.  TIFS restricts
 * access to fwl_id=0 on AM275X, so firewall positive tests for that ID
 * must be compiled in only when this flag is defined. */
#define DM_TEST_FWL_ID0_SUPPORTED
#define TEST_DM_OTP_WKUP_HOST_RESTRICTED
/* ========================================================================== */
/*                         Wrapper test resource indices                      */
/* ========================================================================== */

#define WRAP_RM_NAV_BCDMA_DEV_ID    TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define WRAP_RM_NAV_PKTDMA_DEV_ID   TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define WRAP_RM_NAV_INTAGGR_DEV_ID  TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */
#define WRAP_RM_BCDMA_RING_IDX      (18U)
#define WRAP_RM_PKTDMA_TX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (10U)
#define WRAP_RM_IRQ_SRC_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_SRC_INDEX       (10U)
#define WRAP_RM_IRQ_DST_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_DST_HOST_IRQ    (0U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_A53_2                 /* 12U */
#define WRAP_RM_PSIL_NAV_ID         TISCI_DEV_DMASS0                    /* 25U */
#define WRAP_RM_PSIL_SRC_THREAD     (0x100BU)
#define WRAP_RM_PSIL_DST_THREAD     (0x900BU)
#define WRAP_RM_PSIL_TADDR          (0x0002U)
#define WRAP_RM_PSIL_WRITE_DATA     (0x80000000U)

/* Co-processor for proc-boot ownership tests (request/release/handover).
 * A53SS0_CORE_1 is in the free pool on AM62DX at test time. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_A53SS0_CORE_1

/* Host ID used as handover target in proc-boot handover tests.
 * On AM62DX the handover target is the A53 cluster non-secure context 2. */
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_A53_2                 /* 12U */

#endif /* AM62DX_EVM_TEST_DEVICE_MANAGER_VAL_H_ */
