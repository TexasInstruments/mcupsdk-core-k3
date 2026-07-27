/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
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
 *  \file am62ax-sk/test_sciclient_val.h
 *
 *  \brief AM62AX-SK specific Sciclient test values for the device manager UT.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am62ax/tisci_devices.h
 *    - source/drivers/sciclient/include/tisci/am62ax/tisci_clocks.h
 *    - source/drivers/sciclient/sciclient_default_boardcfg/am62ax/sciclient_defaultBoardcfg_rm.c
 *    - source/drivers/sciclient/include/am62ax/sciclient_fmwMsgParams.h
 *
 *  This header is shared by every AM62AX-SK test image: mcu-r5fss0-0,
 *  a53ss0-0, and c75ss0-0. Sciclient_getContext()
 *  (source/drivers/sciclient/soc/am62ax/sciclient_soc_priv.c) maps each
 *  core to a DIFFERENT TISCI host:
 *    - mcu-r5fss0-0 -> SCICLIENT_CONTEXT_MCU_R5_0_NONSEC_0 -> TISCI_HOST_ID_MCU_0_R5_0
 *    - a53ss0-0     -> SCICLIENT_CONTEXT_A53_NONSEC_1      -> TISCI_HOST_ID_A53_2
 *    - c75ss0-0     -> SCICLIENT_CONTEXT_C7_NONSEC_0       -> TISCI_HOST_ID_C7X_0_0
 *  All RM resource indices that depend on ownership are therefore selected
 *  per building core via the TEST_CORE_MCU_R5F / CORE_A53 / CORE_C7 macros
 *  defined by each core's makefile — see the "Per-core RM resource
 *  ownership" block below.
 *
 *  NOTE: These values are statically derived from the board RM
 *  configuration tables and have not been validated on hardware. On-target
 *  validation is recommended before relying on this header for release
 *  testing (see the analogous caveats already present in
 *  am62dx-evm/test_sciclient_val.h and am275x-evm/test_sciclient_val.h).
 */

#ifndef AM62AX_SK_TEST_SCICLIENT_VAL_H_
#define AM62AX_SK_TEST_SCICLIENT_VAL_H_

/* ========================================================================== */
/*                     RM Navigator Subsystem device IDs                      */
/* ========================================================================== */

#define TEST_RM_NAV_BCDMA_DEV_ID     TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define TEST_RM_NAV_PKTDMA_DEV_ID    TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define TEST_RM_NAV_INTAGGR_DEV_ID   TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */

/* ========================================================================== */
/*            Per-core RM resource ownership (all AM62AX-SK cores)            */
/* ========================================================================== */

/* This header is shared by every AM62AX-SK core build (mcu-r5fss0-0,
 * a53ss0-0, c75ss0-0). Sciclient_getContext() resolves each core to a
 * DIFFERENT TISCI host, and RM resource ownership in
 * sciclient_defaultBoardcfg_rm.c differs per host, so the "owned" (positive
 * test) and "not-owned" (negative test) resource indices below MUST be
 * selected per building core:
 *
 *   TEST_CORE_MCU_R5F (mcu-r5fss0-0) -> TISCI_HOST_ID_MCU_0_R5_0
 *   CORE_A53          (a53ss0-0)     -> TISCI_HOST_ID_A53_2
 *   CORE_C7           (c75ss0-0)     -> TISCI_HOST_ID_C7X_0_0
 *
 * C7X_0_0 has no dedicated PKTDMA channel allocation of its own; it must use
 * the TISCI_HOST_ID_ALL shared pool, index 16, for a "positive" test. */
#if defined(TEST_CORE_MCU_R5F)
#define TEST_RM_CORE_BCDMA_RING_IDX             (24U)
#define TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX   (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_BCDMA_TX_CH_IDX            (18U)
#define TEST_RM_CORE_BCDMA_RX_CH_IDX            (24U)
#define TEST_RM_CORE_PKTDMA_CH_IDX              (13U)
#define TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX    (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_PSIL_CH_IDX                (13U)   /* 0x0D */
#define TEST_RM_CORE_IA_VINT_IDX                (168U)
#define TEST_RM_CORE_GLOBAL_SEVT_IDX             (782U)
#elif defined(CORE_A53)
#define TEST_RM_CORE_BCDMA_RING_IDX             (0U)
#define TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX   (24U)   /* owned by MCU_0_R5_0 */
#define TEST_RM_CORE_BCDMA_TX_CH_IDX            (0U)
#define TEST_RM_CORE_BCDMA_RX_CH_IDX            (0U)
#define TEST_RM_CORE_PKTDMA_CH_IDX              (0U)
#define TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX    (13U)   /* owned by MCU_0_R5_0 */
#define TEST_RM_CORE_PSIL_CH_IDX                (0U)
#define TEST_RM_CORE_IA_VINT_IDX                (6U)
#define TEST_RM_CORE_GLOBAL_SEVT_IDX             (14U)
#elif defined(CORE_C7)
#define TEST_RM_CORE_BCDMA_RING_IDX             (18U)
#define TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX   (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_BCDMA_TX_CH_IDX            (12U)
#define TEST_RM_CORE_BCDMA_RX_CH_IDX            (18U)
#define TEST_RM_CORE_PKTDMA_CH_IDX              (16U)   /* TISCI_HOST_ID_ALL shared pool */
#define TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX    (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_PSIL_CH_IDX                (16U)
#define TEST_RM_CORE_IA_VINT_IDX                (32U)
#define TEST_RM_CORE_GLOBAL_SEVT_IDX             (910U)
#else
#error "test_sciclient_val.h: define TEST_CORE_MCU_R5F, CORE_A53, or CORE_C7 in the core's makefile"
#endif

/* ========================================================================== */
/*                        BCDMA ring / channel indices                        */
/* ========================================================================== */

#define TEST_RM_BCDMA_RING_IDX             TEST_RM_CORE_BCDMA_RING_IDX
#define TEST_RM_BCDMA_RING_NOT_OWNED_IDX   TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX
/* TISCI_MSG_RM_UDMAP_TX_CH_CFG / RX_CH_CFG validate against
 * BCDMA_SPLIT_TR_TX_CHAN / BCDMA_SPLIT_TR_RX_CHAN (non-ring), selected
 * per building core above so the caller actually owns the channel tested. */
#define TEST_RM_BCDMA_TX_CH_IDX      TEST_RM_CORE_BCDMA_TX_CH_IDX
#define TEST_RM_BCDMA_RX_CH_IDX      TEST_RM_CORE_BCDMA_RX_CH_IDX

/* ========================================================================== */
/*                       PKTDMA channel / flow indices                        */
/* ========================================================================== */

#define TEST_RM_PKTDMA_TX_CH_IDX          TEST_RM_CORE_PKTDMA_CH_IDX
#define TEST_RM_PKTDMA_RX_CH_IDX          TEST_RM_CORE_PKTDMA_CH_IDX
#define TEST_RM_PKTDMA_FLOW_IDX           TEST_RM_CORE_PKTDMA_CH_IDX
#define TEST_RM_PKTDMA_CH_NOT_OWNED_IDX   TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX

/* ========================================================================== */
/*                   INTAGGR (interrupt aggregator) indices                   */
/* ========================================================================== */

/* IA_VINT / GLOBAL_EVENT_SEVT ranges are host-owned (see table above), so
 * these are selected per building core to guarantee ownership. */
#define TEST_RM_IA_VINT_IDX          TEST_RM_CORE_IA_VINT_IDX
#define TEST_RM_GLOBAL_SEVT_IDX      TEST_RM_CORE_GLOBAL_SEVT_IDX

/* ========================================================================== */
/*                       BCDMA OES event trigger index                        */
/* ========================================================================== */

/* OES event ID for block-copy channel N data completion:
 * TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START (8704) + N.
 * N is the per-core owned BCDMA_BLOCK_COPY_CHAN index (TEST_RM_CORE_BCDMA_RING_IDX). */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8704U + TEST_RM_CORE_BCDMA_RING_IDX)

/* ========================================================================== */
/*                              PSI-L thread IDs                              */
/* ========================================================================== */

/* DMASS0 PKTDMA PSI-L system thread map:
 * PSI-L thread ID = CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS/D_THREAD_OFFSET + UDMAP channel index
 * (see source/drivers/udma/v0/udma_ch.c: rmPairReq.src_thread = txChNum + udmapSrcThreadOffset).
 * PSILS (TX) offset = 0x1000, PSILD (RX) offset = 0x9000 (0x8000 | 0x1000).
 * The channel index (TEST_RM_CORE_PSIL_CH_IDX above) is selected per building
 * core so it corresponds to a channel actually owned by that core's host.
 * nav_id = TISCI_DEV_DMASS0 (25U) selects the DMASS0 PSI-L config proxy. */
#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x1000U + TEST_RM_CORE_PSIL_CH_IDX)  /* PKTDMA TX thread */
#define TEST_RM_PSIL_DST_THREAD      (0x9000U + TEST_RM_CORE_PSIL_CH_IDX)  /* PKTDMA RX thread (>= 0x8000) */
#define TEST_RM_PSIL_TADDR           (0x0002U)                       /* Thread config register offset */
#define TEST_RM_PSIL_WRITE_DATA      (0x80000000U)                   /* Thread enable bit pattern */

/* ========================================================================== */
/*                           IRQ routing parameters                           */
/* ========================================================================== */

/* DM proxies IRQ routing via secondary_host=A53_2 regardless of building core,
 * matching the reference AM62DX-EVM behavior. */
#define TEST_RM_IRQ_SRC_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_SRC_INDEX        (10U)
#define TEST_RM_IRQ_DST_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_A53_2                 /* 12U */

/* Sciclient_rmIrqSet/Release (wrapper.c) high-level route-find test:
 * Sciclient_rmProgramInterruptRoute rejects IR devices as src/dst, so this
 * needs a real GPIO source and a real core destination. Reused from the
 * AM62DX-EVM reference (GPIO1(78):72 -> WKUP_R5FSS0_CORE0(121):36,
 * host=A53_2(12)); GPIO1 / WKUP_R5FSS0_CORE0 device IDs are identical on
 * AM62AX. NOTE: the exact pin-to-intr routing (72 -> 36) was not
 * independently re-derived for AM62AX's pinmux/IR tree and should be
 * confirmed on target hardware. */
#define TEST_RM_IRQSET_SRC_DEV_ID    TISCI_DEV_GPIO1                     /* 78U */
#define TEST_RM_IRQSET_SRC_INDEX     (72U)
#define TEST_RM_IRQSET_DST_DEV_ID    TISCI_DEV_WKUP_R5FSS0_CORE0         /* 121U */
#define TEST_RM_IRQSET_DST_HOST_IRQ  (36U)

/* ========================================================================== */
/*                         PM / Clock test constants                          */
/* ========================================================================== */

/* Device and clock IDs for PM clock/device management tests.
 * Source: source/drivers/sciclient/include/tisci/am62ax/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am62ax/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_MCU_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_MCU_UART0_FCLK_CLK

/* Clock with a switchable parent mux — used in GET/SET_CLOCK_PARENT positive tests.
 * TIMER0 TIMER_TCLK_CLK (clk=2) has multiple muxed parents on AM62AX. */
#define TEST_CLK_PARENT_DEV_ID  TISCI_DEV_TIMER0               /* 36U */
#define TEST_CLK_PARENT_CLK_ID  TISCI_DEV_TIMER0_TIMER_TCLK_CLK /* 2U */
#define TEST_DM_CLK_SSC         1

/* Fixed-source clock — used in GET/SET_CLOCK_PARENT negative tests to verify
 * firmware NACKs parent-change ops. MCU_UART0 FCLK_CLK has no selectable
 * parent on AM62AX. */
#define TEST_FIXED_SRC_CLK_DEVICE_ID  TEST_DEVICE_ID
#define TEST_FIXED_SRC_CLK_ID         TEST_DEVICE_CLK_ID

/* ========================================================================== */
/*                          Processor boot / host ID                          */
/* ========================================================================== */

/* Host ID used for processor handover in LPM and procboot tests.
 * On AM62AX the target hand-over host is the A53 cluster (host 12). */
#define TISCI_HOST_ID               TISCI_HOST_ID_A53_2

/* Co-processor used for proc-boot tests (REQUEST/RELEASE/HANDOVER/SET_CONTROL).
 * Must be a processor not actively used by the DM firmware itself. */
#define TEST_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0

/* ========================================================================== */
/*                         Firewall capability flags                          */
/* ========================================================================== */

/* fwl_id=0 is a valid, accessible firewall on AM62DX; AM62AX shares the same
 * boardcfg RM structure and is expected to behave identically. */
#define DM_TEST_FWL_ID0_SUPPORTED
#define TEST_DM_OTP_WKUP_HOST_RESTRICTED

/* ========================================================================== */
/*                   Low Power Mode (LPM) capability flags                    */
/* ========================================================================== */
/* LPM (Low Power Mode) tests are supported on AM62AX (see examples/lpm/). */
#define CONFIG_TEST_LPM

/* ========================================================================== */
/*                       Wrapper test resource indices                        */
/* ========================================================================== */

#define WRAP_RM_NAV_BCDMA_DEV_ID    TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define WRAP_RM_NAV_PKTDMA_DEV_ID   TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define WRAP_RM_NAV_INTAGGR_DEV_ID  TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */
/* Same per-core ownership rules as TEST_RM_* above (see the
 * "Per-core RM resource ownership" block) — reuse the same TEST_RM_CORE_*
 * values so the wrapper-API tests exercise the same owned/not-owned
 * resources regardless of which core (mcu-r5fss0-0 / a53ss0-0 / c75ss0-0)
 * this image is built for. */
#define WRAP_RM_BCDMA_RING_IDX            TEST_RM_CORE_BCDMA_RING_IDX
#define WRAP_RM_BCDMA_RING_NOT_OWNED_IDX  TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX
#define WRAP_RM_PKTDMA_TX_CH_IDX          TEST_RM_CORE_PKTDMA_CH_IDX
#define WRAP_RM_PKTDMA_RX_CH_IDX          TEST_RM_CORE_PKTDMA_CH_IDX
#define WRAP_RM_PKTDMA_FLOW_IDX           TEST_RM_CORE_PKTDMA_CH_IDX
#define WRAP_RM_PKTDMA_CH_NOT_OWNED_IDX   TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX
#define WRAP_RM_IRQ_SRC_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_SRC_INDEX       (10U)
#define WRAP_RM_IRQ_DST_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_DST_HOST_IRQ    (0U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_A53_2                 /* 12U */
#define WRAP_RM_PSIL_NAV_ID         TISCI_DEV_DMASS0                    /* 25U */
/* PSI-L thread ID = offset + UDMAP channel index (see TEST_RM_PSIL_SRC_THREAD
 * above); the channel index is selected per building core. */
#define WRAP_RM_PSIL_SRC_THREAD     (0x1000U + TEST_RM_CORE_PSIL_CH_IDX)
#define WRAP_RM_PSIL_DST_THREAD     (0x9000U + TEST_RM_CORE_PSIL_CH_IDX)
#define WRAP_RM_PSIL_TADDR          (0x0002U)
#define WRAP_RM_PSIL_WRITE_DATA     (0x80000000U)

/* Co-processor for proc-boot ownership tests (request/release/handover).
 * A53SS0_CORE_1 is in the free pool on AM62AX at test time. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_A53SS0_CORE_1

/* Host ID used as handover target in proc-boot handover tests.
 * MUST be a host different from the CALLING core's own TISCI host, or the
 * handover becomes a self-transfer no-op. On AM62AX the handover target is
 * normally the A53 cluster non-secure context 2, except when the test
 * itself runs ON A53_2, in which case MCU_0_R5_0 is used instead. */
#if defined(CORE_A53)
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_MCU_0_R5_0            /* 30U */
#else
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_A53_2                 /* 12U */
#endif


#endif /* AM62AX_SK_TEST_SCICLIENT_VAL_H_ */
