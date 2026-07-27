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
 *  \file am62x-sk/test_sciclient_val.h
 *
 *  \brief AM62X-SK specific RM test values for the device manager UT.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am62x/tisci_devices.h
 *    - source/drivers/sciclient/include/tisci/am62x/tisci_clocks.h
 *    - source/drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_rm.c
 *    - source/drivers/sciclient/include/am62x/sciclient_fmwMsgParams.h
 *
 *  This header is shared by every AM62X-SK test image: m4fss0-0 and
 *  a53ss0-0 (AM62X has no C7x DSP). Sciclient_getContext()
 *  (source/drivers/sciclient/soc/am62x/sciclient_soc_priv.c) maps each
 *  core to a DIFFERENT TISCI host:
 *    - m4fss0-0  -> TISCI_HOST_ID_M4_0
 *    - a53ss0-0  -> TISCI_HOST_ID_A53_2
 *  All RM resource indices that depend on ownership are therefore selected
 *  per building core via the TEST_CORE_MCU_M4F / CORE_A53 macros defined
 *  by each core's makefile — see the "Per-core RM resource ownership"
 *  block below.
 *
 *  NOTE: These values are statically derived from the board RM
 *  configuration tables and have not been validated on hardware. On-target
 *  validation is recommended before relying on this header for release
 *  testing.
 */

#ifndef AM62X_SK_TEST_SCICLIENT_VAL_H_
#define AM62X_SK_TEST_SCICLIENT_VAL_H_

/* ========================================================================== */
/*                     RM Navigator Subsystem device IDs                      */
/* ========================================================================== */

#define TEST_RM_NAV_BCDMA_DEV_ID     TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define TEST_RM_NAV_PKTDMA_DEV_ID    TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define TEST_RM_NAV_INTAGGR_DEV_ID   TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */

/* ========================================================================== */
/*            Per-core RM resource ownership (all AM62X-SK cores)             */
/* ========================================================================== */

/* This header is shared by every AM62X-SK core build (m4fss0-0, a53ss0-0). */
#if defined(TEST_CORE_MCU_M4F)
#define TEST_RM_CORE_BCDMA_RING_IDX             (24U)
#define TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX   (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_BCDMA_TX_CH_IDX            (18U)
#define TEST_RM_CORE_BCDMA_RX_CH_IDX            (24U)
#define TEST_RM_CORE_PKTDMA_CH_IDX              (13U)
#define TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX    (0U)    /* owned by A53_2 */
#define TEST_RM_CORE_PSIL_CH_IDX                (13U)   /* 0x0D */
#define TEST_RM_CORE_IA_VINT_IDX                (168U)
#define TEST_RM_CORE_GLOBAL_SEVT_IDX             (781U)
#elif defined(CORE_A53)
#define TEST_RM_CORE_BCDMA_RING_IDX             (0U)
#define TEST_RM_CORE_BCDMA_RING_NOT_OWNED_IDX   (24U)   /* owned by M4_0 */
#define TEST_RM_CORE_BCDMA_TX_CH_IDX            (0U)
#define TEST_RM_CORE_BCDMA_RX_CH_IDX            (0U)
#define TEST_RM_CORE_PKTDMA_CH_IDX              (0U)
#define TEST_RM_CORE_PKTDMA_CH_NOT_OWNED_IDX    (13U)   /* owned by M4_0 */
#define TEST_RM_CORE_PSIL_CH_IDX                (0U)
#define TEST_RM_CORE_IA_VINT_IDX                (5U)
#define TEST_RM_CORE_GLOBAL_SEVT_IDX             (13U)
#else
#error "test_sciclient_val.h: define TEST_CORE_MCU_M4F or CORE_A53 in the core's makefile"
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

#define TEST_RM_IA_VINT_IDX          TEST_RM_CORE_IA_VINT_IDX
#define TEST_RM_GLOBAL_SEVT_IDX      TEST_RM_CORE_GLOBAL_SEVT_IDX

/* ========================================================================== */
/*                       BCDMA OES event trigger index                        */
/* ========================================================================== */

/* OES event ID for block-copy channel N data completion:
 *   TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START (8704) + N.
 * N is the per-core owned BCDMA_BLOCK_COPY_CHAN index (TEST_RM_CORE_BCDMA_RING_IDX). */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8704U + TEST_RM_CORE_BCDMA_RING_IDX)

/* ========================================================================== */
/*                              PSI-L thread IDs                              */
/* ========================================================================== */

#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x1000U + TEST_RM_CORE_PSIL_CH_IDX)  /* PKTDMA TX thread */
#define TEST_RM_PSIL_DST_THREAD      (0x9000U + TEST_RM_CORE_PSIL_CH_IDX)  /* PKTDMA RX thread (>= 0x8000) */
#define TEST_RM_PSIL_TADDR           (0x0002U)                       /* Thread config register offset */
#define TEST_RM_PSIL_WRITE_DATA      (0x80000000U)                   /* Thread enable bit pattern */

/* ========================================================================== */
/*                           IRQ routing parameters                           */
/* ========================================================================== */

#define TEST_RM_IRQ_SRC_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_SRC_INDEX        (10U)
#define TEST_RM_IRQ_DST_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_A53_2                 /* 12U */

/* Sciclient_rmIrqSet/Release (wrapper.c) high-level route-find test:
 * reused from the AM62DX-EVM reference (GPIO1(78):72 ->
 * WKUP_R5FSS0_CORE0(121):36, host=A53_2(12)); device IDs are identical on
 * AM62X. NOTE: the exact pin-to-intr routing (72 -> 36) was not
 * independently re-derived for AM62X's pinmux/IR tree and should be
 * confirmed on target hardware. */
#define TEST_RM_IRQSET_SRC_DEV_ID    TISCI_DEV_GPIO1                     /* 78U */
#define TEST_RM_IRQSET_SRC_INDEX     (72U)
#define TEST_RM_IRQSET_DST_DEV_ID    TISCI_DEV_WKUP_R5FSS0_CORE0         /* 121U */
#define TEST_RM_IRQSET_DST_HOST_IRQ  (36U)

/* ========================================================================== */
/*                         PM / Clock test constants                          */
/* ========================================================================== */

/* Device and clock IDs for PM clock/device management tests.
 * Source: source/drivers/sciclient/include/tisci/am62x/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am62x/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_MCU_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_MCU_UART0_FCLK_CLK

/* Clock with a switchable parent mux — used in GET/SET_CLOCK_PARENT positive tests.
 * TIMER0 TIMER_TCLK_CLK (clk=2) has multiple muxed parents on AM62X. */
#define TEST_CLK_PARENT_DEV_ID  TISCI_DEV_TIMER0               /* 36U */
#define TEST_CLK_PARENT_CLK_ID  TISCI_DEV_TIMER0_TIMER_TCLK_CLK /* 2U */
#define TEST_DM_CLK_SSC         1

/* Fixed-source clock — used in GET/SET_CLOCK_PARENT negative tests to verify
 * firmware NACKs parent-change ops. MCU_UART0 FCLK_CLK has no selectable
 * parent on AM62X. */
#define TEST_FIXED_SRC_CLK_DEVICE_ID  TEST_DEVICE_ID
#define TEST_FIXED_SRC_CLK_ID         TEST_DEVICE_CLK_ID

/* ========================================================================== */
/*                          Processor boot / host ID                          */
/* ========================================================================== */

/* Host ID used for processor handover in LPM and procboot tests.
 * On AM62X the target hand-over host is the A53 cluster (host 12). */
#define TISCI_HOST_ID               TISCI_HOST_ID_A53_2

/* Co-processor used for proc-boot tests (REQUEST/RELEASE/HANDOVER/SET_CONTROL).
 * AM62X has no C7x DSP; A53SS0_CORE_2 is used instead as a processor not
 * actively used by the DM firmware itself. */
#define TEST_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_A53SS0_CORE_2

/* ========================================================================== */
/*                         Firewall capability flags                          */
/* ========================================================================== */

/* fwl_id=0 support was NOT independently confirmed for AM62X (unlike
 * AM62DX/AM62AX). DM_TEST_FWL_ID0_SUPPORTED is intentionally left undefined;
 * define it here once fwl_id=0 access has been confirmed on target hardware. */
#define TEST_DM_OTP_WKUP_HOST_RESTRICTED

/* ========================================================================== */
/*                   Low Power Mode (LPM) capability flags                    */
/* ========================================================================== */
/* LPM (Low Power Mode) tests are supported on AM62X (see examples/lpm/). */
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
 * resources regardless of which core (m4fss0-0 / a53ss0-0) this image is
 * built for. */
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
 * A53SS0_CORE_1 is in the free pool on AM62X at test time. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_A53SS0_CORE_1

/* Host ID used as handover target in proc-boot handover tests.
 * MUST be a host different from the CALLING core's own TISCI host, or the
 * handover becomes a self-transfer no-op. On AM62X the handover target is
 * normally the A53 cluster non-secure context 2, except when the test
 * itself runs ON A53_2, in which case M4_0 is used instead. */
#if defined(CORE_A53)
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_M4_0                  /* 30U */
#else
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_A53_2                 /* 12U */
#endif


#endif /* AM62X_SK_TEST_SCICLIENT_VAL_H_ */
