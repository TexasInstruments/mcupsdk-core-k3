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
 *  \file am275x-evm/test_sciclient_val.h
 *
 *  \brief AM275X-EVM specific RM test values for the sciclient UT.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am275x/tisci_devices.h
 *    - source/drivers/sciclient/soc/am275x/sciclient_defaultBoardcfg_rm.c
 *
 *  The DM firmware (r5fss0-0) runs as SCICLIENT_CONTEXT_NONSEC (index 1),
 *  which maps to TISCI_HOST_ID_MAIN_0_R5_1.  All RM resource indices below
 *  correspond to allocations owned by that host.
 */

#ifndef AM275X_EVM_TEST_SCICLIENT_VAL_H_
#define AM275X_EVM_TEST_SCICLIENT_VAL_H_

#if defined(SOC_AM275X)
/* AM275X's sciclient_fmwMsgParams.h only defines PROC_ID_* (no SCICLIENT_
 * prefix, unlike AM62DX/AM62AX/J722S). Provide the compatibility aliases
 * used throughout the shared test sources. AM275X has no A53 cores, so the
 * two co-processors used below are the two C7x DSPs instead. */
#define SCICLIENT_PROC_ID_R5FSS0_CORE0            PROC_ID_R5FSS0_CORE0
#define SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0     PROC_ID_C7X256V0_C7XV_CORE_0
#define SCICLIENT_PROC_ID_C7X256V1_C7XV_CORE_0     PROC_ID_C7X256V1_C7XV_CORE_0
#endif /* SOC_AM275X - AM62DX's sciclient_fmwMsgParams.h already defines SCICLIENT_PROC_ID_* natively */

/* AM275X's test_sciclient project builds separately for c75ss0-0 (host
 * TISCI_HOST_ID_C7X_0_0) and c75ss1-0 (host TISCI_HOST_ID_C7X_1_0), but both
 * makefiles define the SAME CORE_C7 macro (no per-instance distinction is
 * possible at compile time). The "not owned" NOT_OWNED_IDX values below
 * must therefore be owned by NEITHER C7X_0_0 NOR C7X_1_0 when CORE_C7 is
 * building, while remaining owned by neither MAIN_0_R5_1/WKUP_0_R5_0/
 * WKUP_0_R5_1/C7X_1_0 when one of the four r5fssX-Y images is building
 * (CORE_C7 undefined). */

/* ========================================================================== */
/*                     RM Navigator Subsystem device IDs                      */
/* ========================================================================== */

#define TEST_RM_NAV_BCDMA_DEV_ID     TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define TEST_RM_NAV_PKTDMA_DEV_ID    TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define TEST_RM_NAV_INTAGGR_DEV_ID   TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */

/* ========================================================================== */
/*                        BCDMA ring / channel indices                        */
/* ========================================================================== */

#if defined(SOC_AM275X)
/* This project builds separately for r5fss0-0/0-1/1-0/1-1 (4 different TISCI
 * hosts); the actual on-target board cfg does not grant all 4 of those hosts
 * the same exclusive ring range (SITSW-12083: ring 0 NACKed on r5fss0-1 while
 * it ACKed on r5fss0-0), so use the TISCI_HOST_ID_ALL shared range instead,
 * which every core/host can use regardless of its individual allocation. */
#define TEST_RM_BCDMA_RING_IDX             (17U)   /* TISCI_HOST_ID_ALL range, usable by any core */
#if defined(CORE_C7)
/* c75ss0-0 (C7X_0_0) and c75ss1-0 (C7X_1_0) both define CORE_C7; ring 5 is
 * owned by C7X_0_0 itself, so use ring 0 (MAIN_0_R5_1-owned) instead, which
 * neither C7X core owns. */
#define TEST_RM_BCDMA_RING_NOT_OWNED_IDX   (0U)    /* owned by MAIN_0_R5_1 */
#else
#define TEST_RM_BCDMA_RING_NOT_OWNED_IDX   (5U)    /* owned by C7X_0_0; not owned by any r5fssX-Y host */
#endif
/* TISCI_MSG_RM_UDMAP_TX_CH_CFG validates against BCDMA_SPLIT_TR_TX_CHAN. */
#define TEST_RM_BCDMA_TX_CH_IDX      (0U)
#define TEST_RM_BCDMA_RX_CH_IDX      (0U)
#elif defined(SOC_AM62DX)
#define TEST_RM_BCDMA_RING_IDX             (18U)
#define TEST_RM_BCDMA_RING_NOT_OWNED_IDX   (24U)   /* owned by MCU_0_R5_0 */
/* TISCI_MSG_RM_UDMAP_TX_CH_CFG validates against BCDMA_SPLIT_TR_TX_CHAN. */
#define TEST_RM_BCDMA_TX_CH_IDX      (44U)
#define TEST_RM_BCDMA_RX_CH_IDX      (18U)
#endif

/* ========================================================================== */
/*                       PKTDMA channel / flow indices                        */
/* ========================================================================== */

#if defined(SOC_AM275X)
/* As with TEST_RM_BCDMA_RING_IDX (SITSW-12083/12084), the MAIN_0_R5_1-exclusive
 * range NACKed on r5fss0-1 while it ACKed on r5fss0-0, so use the
 * TISCI_HOST_ID_ALL shared range instead, which every core/host can use. */
#define TEST_RM_PKTDMA_TX_CH_IDX          (12U)
#define TEST_RM_PKTDMA_RX_CH_IDX          (12U)
#define TEST_RM_PKTDMA_FLOW_IDX           (12U)
#if defined(CORE_C7)
/* c75ss0-0 (C7X_0_0) and c75ss1-0 (C7X_1_0) both define CORE_C7; channel 5 is
 * owned by C7X_0_0 itself, so use channel 0 (MAIN_0_R5_1-owned) instead, which
 * neither C7X core owns. */
#define TEST_RM_PKTDMA_CH_NOT_OWNED_IDX   (0U)    /* owned by MAIN_0_R5_1 */
#else
#define TEST_RM_PKTDMA_CH_NOT_OWNED_IDX   (5U)    /* owned by C7X_0_0; not owned by any r5fssX-Y host */
#endif
#elif defined(SOC_AM62DX)
#define TEST_RM_PKTDMA_TX_CH_IDX          (10U)
#define TEST_RM_PKTDMA_RX_CH_IDX          (10U)
#define TEST_RM_PKTDMA_FLOW_IDX           (10U)
#define TEST_RM_PKTDMA_CH_NOT_OWNED_IDX   (0U)    /* owned by A53_2 */
#endif

/* ========================================================================== */
/*                   INTAGGR (interrupt aggregator) indices                   */
/* ========================================================================== */

#if defined(SOC_AM275X)
#define TEST_RM_IA_VINT_IDX          (156U)
#define TEST_RM_GLOBAL_SEVT_IDX      (19U)
#elif defined(SOC_AM62DX)
#define TEST_RM_IA_VINT_IDX          (44U)
#define TEST_RM_GLOBAL_SEVT_IDX      (526U)
#endif

/* ========================================================================== */
/*                       BCDMA OES event trigger index                        */
/* ========================================================================== */

#if defined(SOC_AM275X)
/* OES event ID for block-copy channel N data completion:
 *   TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START (8704) + N.
 * Channel 0 (owned by MAIN_0_R5_1): 8704 + 0 = 8704. */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8704U)
#elif defined(SOC_AM62DX)
/* OES event ID for block-copy channel N data completion:
 *   TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START (8704) + N.
 * Channel 18 (owned by MAIN_0_R5_1): 8704 + 18 = 8722. */
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (8722U)
#endif

/* ========================================================================== */
/*                              PSI-L thread IDs                              */
/* ========================================================================== */

/* DMASS0 PKTDMA PSI-L system thread map: thread = 0x1000|0x9000 + channel.
 * nav_id = TISCI_DEV_DMASS0 (25U) selects the DMASS0 PSI-L config proxy.
 * The channel used MUST be one actually owned by this build's host (see
 * TEST_RM_PKTDMA_TX_CH_IDX / TEST_RM_PKTDMA_RX_CH_IDX above), otherwise the
 * PAIR/UNPAIR/READ/WRITE requests are NACKed with flags=0x0 (SITSW-12085). */
#if defined(SOC_AM275X)
/* MAIN_0_R5_1 owns PKTDMA channels 0-4 (see TEST_RM_PKTDMA_TX/RX_CH_IDX
 * above), so use channel 0 (not the AM62DX-style hard-coded channel 11,
 * which MAIN_0_R5_1 does not own on AM275X). */
#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x1000U + TEST_RM_PKTDMA_TX_CH_IDX)  /* PKTDMA TX thread */
#define TEST_RM_PSIL_DST_THREAD      (0x9000U + TEST_RM_PKTDMA_RX_CH_IDX)  /* PKTDMA RX thread (>= 0x8000) */
#elif defined(SOC_AM62DX)
/* AM62DX MAIN_0_R5_1 owns PKTDMA channels 10-12, so channel 11 (0x100B/0x900B)
 * from test_sciclient_rm_irq.c rmPsilPairCfg is a valid owned resource. */
#define TEST_RM_PSIL_NAV_ID          TISCI_DEV_DMASS0               /* 25U */
#define TEST_RM_PSIL_SRC_THREAD      (0x100BU)                       /* PKTDMA TX thread */
#define TEST_RM_PSIL_DST_THREAD      (0x900BU)                       /* PKTDMA RX thread (>= 0x8000) */
#endif
#define TEST_RM_PSIL_TADDR           (0x0002U)                       /* Thread config register offset */
#define TEST_RM_PSIL_WRITE_DATA      (0x80000000U)                   /* Thread enable bit pattern */

/* ========================================================================== */
/*                           IRQ routing parameters                           */
/* ========================================================================== */

#define TEST_RM_IRQ_SRC_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define TEST_RM_IRQ_SRC_INDEX        (10U)
#define TEST_RM_IRQ_DST_DEV_ID       TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#if defined(SOC_AM275X)
/* This is the host this build runs as; DM proxies IRQ routing via
 * secondary_host=MAIN_0_R5_1 (self-owned resource). */
#define TEST_RM_IRQ_DST_HOST_IRQ     (16U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_MAIN_0_R5_1           /* 41U */
#elif defined(SOC_AM62DX)
/* DM proxies IRQ routing via secondary_host=A53_2.
 * Matches reference: test_sciclient_rm_irq.c rmIrqSetCfg
 *   (src_id=3, src_index=10, dst_id=3, dst_host_irq=0,
 *    valid_params=0x80000003, secondary_host=12). */
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   TISCI_HOST_ID_A53_2                 /* 12U */
#endif

/* Sciclient_rmIrqSet/Release (wrapper.c) high-level route-find test:
 * Sciclient_rmProgramInterruptRoute rejects IR devices as src/dst, so this
 * needs a real GPIO source and a real core destination (not the IR device
 * pair above). */
#if defined(SOC_AM275X)
/* Source: source/drivers/sciclient/soc/am275x/sciclient_irq_rm.c
 * GPIO1 pin 72 -> MAIN_GPIOMUX_INTROUTER0 input 168 (GPIO1_gpio_72_72_to_
 * MAIN_GPIO_INTROUTER0_in_168_168), and MAIN_GPIOMUX_INTROUTER0 output
 * 16-31 -> TISCI_DEV_R5FSS0_CORE1 (== TISCI_HOST_ID_MAIN_0_R5_1, this
 * build's own host) intr 32-47 (MAIN_GPIO_INTROUTER0_outp_16_31_to_
 * R5FSS0_CORE1_intr_32_47). WKUP_R5FSS0_CORE0 (the AM62DX-style target) is
 * not reachable from GPIO1 with secondary_host=MAIN_0_R5_1 on AM275X. */
#define TEST_RM_IRQSET_SRC_DEV_ID    TISCI_DEV_GPIO1                     /* 78U */
#define TEST_RM_IRQSET_SRC_INDEX     (72U)
#define TEST_RM_IRQSET_DST_DEV_ID    TISCI_DEV_R5FSS0_CORE1              /* 319U */
#define TEST_RM_IRQSET_DST_HOST_IRQ  (32U)
#elif defined(SOC_AM62DX)
/* Matches reference: test_sciclient_rm_irq.c — GPIO1(78):72 ->
 * WKUP_R5FSS0_CORE0(121):36, host=A53_2(12). */
#define TEST_RM_IRQSET_SRC_DEV_ID    TISCI_DEV_GPIO1                     /* 78U */
#define TEST_RM_IRQSET_SRC_INDEX     (72U)
#define TEST_RM_IRQSET_DST_DEV_ID    TISCI_DEV_WKUP_R5FSS0_CORE0         /* 121U */
#define TEST_RM_IRQSET_DST_HOST_IRQ  (36U)
#endif

/* ========================================================================== */
/*                         PM / Clock test constants                          */
/* ========================================================================== */

#if defined(SOC_AM275X)
/* Device and clock IDs for PM clock/device management tests.
 * AM275X has no MCU-domain UART (unlike AM62DX); use the MAIN domain UART0.
 * Source: source/drivers/sciclient/include/tisci/am275x/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am275x/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_UART0_FCLK_CLK
#elif defined(SOC_AM62DX)
/* Device and clock IDs for PM clock/device management tests.
 * Source: source/drivers/sciclient/include/tisci/am62dx/tisci_devices.h
 *         source/drivers/sciclient/include/tisci/am62dx/tisci_clocks.h */
#define TEST_DEVICE_ID          TISCI_DEV_MCU_UART0
#define TEST_DEVICE_CLK_ID      TISCI_DEV_MCU_UART0_FCLK_CLK
#endif

/* Clock with a switchable parent mux — used in GET/SET_CLOCK_PARENT positive tests.
 * TIMER0 TIMER_TCLK_CLK (clk=2) has multiple muxed parents on AM62DX and AM275X. */
#define TEST_CLK_PARENT_DEV_ID  TISCI_DEV_TIMER0               /* 36U */
#define TEST_CLK_PARENT_CLK_ID  TISCI_DEV_TIMER0_TIMER_TCLK_CLK /* 2U */

/* Fixed-source clock — used in GET/SET_CLOCK_PARENT negative tests to verify
 * firmware NACKs parent-change ops on a clock that has no selectable parent.
 * TEST_DEVICE_ID/TEST_DEVICE_CLK_ID (UART0 FCLK_CLK) is NOT fixed-source on
 * AM275X (it has 2 muxed parents, unlike AM62DX's MCU_UART0 FCLK_CLK, see
 * SITSW-12211), so a separate, genuinely fixed-source device/clock pair is
 * used for this specific negative test. */
#if defined(SOC_AM275X)
/* WKUP_UART0 FCLK_CLK (clk=0) has no PARENT_* alternatives in
 * tisci_clocks.h, i.e. it is fixed-source, unlike MAIN UART0's FCLK_CLK. */
#define TEST_FIXED_SRC_CLK_DEVICE_ID  TISCI_DEV_WKUP_UART0
#define TEST_FIXED_SRC_CLK_ID         TISCI_DEV_WKUP_UART0_FCLK_CLK
#elif defined(SOC_AM62DX)
#define TEST_FIXED_SRC_CLK_DEVICE_ID  TEST_DEVICE_ID
#define TEST_FIXED_SRC_CLK_ID         TEST_DEVICE_CLK_ID
#endif

#if defined(SOC_AM62DX)
#define TEST_DM_CLK_SSC         1
#elif defined(SOC_AM275X)
/* TEST_DM_CLK_SSC intentionally left undefined on AM275X: the SET/GET_CLOCK_SSC
 * positive tests it guards are hard-coded to TISCI_DEV_DSS0, and AM275X has no
 * display subsystem (DSS) device. */
#endif

/* ========================================================================== */
/*                          Processor boot / host ID                          */
/* ========================================================================== */

#if defined(SOC_AM275X)
/* Host ID used for processor handover in LPM and procboot tests.
 * This build runs as TISCI_HOST_ID_MAIN_0_R5_1; AM275X has no A53 cluster,
 * so the handover target is the caller's own host (self-handover, since the
 * co-processor being handed over is not otherwise owned by this core). */
#define TISCI_HOST_ID               TISCI_HOST_ID_MAIN_0_R5_1
#elif defined(SOC_AM62DX)
/* Host ID used for processor handover in LPM and procboot tests.
 * On AM62DX the target hand-over host is the A53 cluster (host 12). */
#define TISCI_HOST_ID               TISCI_HOST_ID_A53_2
#endif

/* Co-processor used for proc-boot tests (REQUEST/RELEASE/HANDOVER/SET_CONTROL).
 * Must be a processor not actively used by the DM firmware itself. */
#define TEST_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0

/* ========================================================================== */
/*                       Pre-signed R5 boot certificate                       */
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
/*                         Firewall capability flags                          */
/* ========================================================================== */

/* fwl_id=0 is a valid, accessible firewall on AM62DX.  TIFS restricts
 * access to fwl_id=0 on AM275X (SITSW-12094: retVal=0 flags=0x0 NACK on
 * SET/GET/CHANGE_FWL_OWNER), so firewall positive tests for that ID
 * must be compiled in only when this flag is defined. */
#if defined(SOC_AM62DX)
#define DM_TEST_FWL_ID0_SUPPORTED
#endif
#define TEST_DM_OTP_WKUP_HOST_RESTRICTED

/* ========================================================================== */
/*                   Low Power Mode (LPM) capability flags                    */
/* ========================================================================== */
/* LPM (Low Power Mode) tests are supported on AM62DX. */
#define CONFIG_TEST_LPM

/* ========================================================================== */
/*                       Wrapper test resource indices                        */
/* ========================================================================== */

#define WRAP_RM_NAV_BCDMA_DEV_ID    TISCI_DEV_DMASS0_BCDMA_0      /* 26U */
#define WRAP_RM_NAV_PKTDMA_DEV_ID   TISCI_DEV_DMASS0_PKTDMA_0     /* 30U */
#define WRAP_RM_NAV_INTAGGR_DEV_ID  TISCI_DEV_DMASS0_INTAGGR_0    /* 28U */
#if defined(SOC_AM275X)
/* Use the TISCI_HOST_ID_ALL shared ring range (17-23), usable by every core
 * this project builds for (r5fss0-0/0-1/1-0/1-1) -- see TEST_RM_BCDMA_RING_IDX
 * comment above (SITSW-12083). */
#define WRAP_RM_BCDMA_RING_IDX             (17U)
#define WRAP_RM_BCDMA_RING_NOT_OWNED_IDX   (5U)    /* owned by C7X_0_0 */
/* TISCI_HOST_ID_ALL shared range (12-26) -- usable by every core, see
 * TEST_RM_PKTDMA_TX_CH_IDX comment above (SITSW-12084). */
#define WRAP_RM_PKTDMA_TX_CH_IDX    (12U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (12U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (12U)
#define WRAP_RM_PKTDMA_CH_NOT_OWNED_IDX    (5U)    /* owned by C7X_0_0 */
#elif defined(SOC_AM62DX)
#define WRAP_RM_BCDMA_RING_IDX             (18U)
#define WRAP_RM_BCDMA_RING_NOT_OWNED_IDX   (24U)   /* owned by MCU_0_R5_0 */
#define WRAP_RM_PKTDMA_TX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_RX_CH_IDX    (10U)
#define WRAP_RM_PKTDMA_FLOW_IDX     (10U)
#define WRAP_RM_PKTDMA_CH_NOT_OWNED_IDX    (0U)    /* owned by A53_2 */
#endif
#define WRAP_RM_IRQ_SRC_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#define WRAP_RM_IRQ_SRC_INDEX       (10U)
#define WRAP_RM_IRQ_DST_DEV_ID      TISCI_DEV_MAIN_GPIOMUX_INTROUTER0  /* 3U */
#if defined(SOC_AM275X)
#define WRAP_RM_IRQ_DST_HOST_IRQ    (16U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_MAIN_0_R5_1           /* 41U */
#elif defined(SOC_AM62DX)
#define WRAP_RM_IRQ_DST_HOST_IRQ    (0U)
#define WRAP_RM_IRQ_SECONDARY_HOST  TISCI_HOST_ID_A53_2                 /* 12U */
#endif
#define WRAP_RM_PSIL_NAV_ID         TISCI_DEV_DMASS0                    /* 25U */
#if defined(SOC_AM275X)
/* MAIN_0_R5_1 owns PKTDMA channels 0-4 (see WRAP_RM_PKTDMA_TX/RX_CH_IDX
 * above); use channel 0, not the AM62DX-style hard-coded channel 11 which
 * MAIN_0_R5_1 does not own on AM275X (see TEST_RM_PSIL_* comment above). */
#define WRAP_RM_PSIL_SRC_THREAD     (0x1000U + WRAP_RM_PKTDMA_TX_CH_IDX)
#define WRAP_RM_PSIL_DST_THREAD     (0x9000U + WRAP_RM_PKTDMA_RX_CH_IDX)
#elif defined(SOC_AM62DX)
#define WRAP_RM_PSIL_SRC_THREAD     (0x100BU)
#define WRAP_RM_PSIL_DST_THREAD     (0x900BU)
#endif
#define WRAP_RM_PSIL_TADDR          (0x0002U)
#define WRAP_RM_PSIL_WRITE_DATA     (0x80000000U)

#if defined(SOC_AM275X)
/* Co-processor for proc-boot ownership tests (request/release/handover).
 * AM275X has no A53 cores; use the second C7x DSP (distinct from
 * TEST_PROC_ID_COPROCESSOR above) as the free-pool co-processor. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_C7X256V1_C7XV_CORE_0

/* Host ID used as handover target in proc-boot handover tests. MUST differ
 * from this build's own host or the handover becomes a self-transfer no-op
 * (SITSW-12215: using TISCI_HOST_ID_MAIN_0_R5_3 NACKed correctly on
 * r5fss0-0 but silently self-transferred -- no-op -- on r5fss0-1, since this
 * project builds identically for 4 different R5 hosts and the MAIN_0_R5_*
 * per-core mapping is not reliable, see repo notes). Use a host from a
 * completely different domain (WKUP R5) so it can never alias any of the
 * 4 MAIN R5FSS build hosts. */
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_WKUP_0_R5_1           /* 36U */
#elif defined(SOC_AM62DX)
/* Co-processor for proc-boot ownership tests (request/release/handover).
 * A53SS0_CORE_1 is in the free pool on AM62DX at test time. */
#define WRAP_PROC_ID_COPROCESSOR    SCICLIENT_PROC_ID_A53SS0_CORE_1

/* Host ID used as handover target in proc-boot handover tests.
 * On AM62DX the handover target is the A53 cluster non-secure context 2. */
#define WRAP_PROC_HANDOVER_HOST     TISCI_HOST_ID_A53_2                 /* 12U */
#endif

#endif /* AM275X_EVM_TEST_SCICLIENT_VAL_H_ */
