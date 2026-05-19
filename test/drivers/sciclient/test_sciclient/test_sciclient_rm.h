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

#ifndef TEST_SCICLIENT_RM_H_
#define TEST_SCICLIENT_RM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_ra.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_udmap.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_irq.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_shared.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_psil.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_proxy.h>

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */

/* SoC-specific RM test values are defined in per-device header files,
 * following the same pattern as test/drivers/sciclient/. */
#if defined(SOC_AM62DX)
#include "am62dx-evm/test_sciclient_val.h"
#elif defined(SOC_AM275X)
#include "am275x-evm/test_sciclient_val.h"
#else
/* Placeholder defaults for other SoCs — positive RM tests are SOC-specific */
#define TEST_RM_NAV_BCDMA_DEV_ID     (0xFFFFU)
#define TEST_RM_NAV_PKTDMA_DEV_ID    (0xFFFFU)
#define TEST_RM_NAV_INTAGGR_DEV_ID   (0xFFFFU)
#define TEST_RM_BCDMA_RING_IDX       (0U)
#define TEST_RM_BCDMA_TX_CH_IDX      (0U)
#define TEST_RM_BCDMA_RX_CH_IDX      (0U)
#define TEST_RM_PKTDMA_TX_CH_IDX     (0U)
#define TEST_RM_PKTDMA_RX_CH_IDX     (0U)
#define TEST_RM_PKTDMA_FLOW_IDX      (0U)
#define TEST_RM_IA_VINT_IDX          (0U)
#define TEST_RM_GLOBAL_SEVT_IDX      (0U)
#define TEST_RM_BCDMA_EVT_TRIG_IDX   (0U)
#define TEST_RM_PSIL_NAV_ID          (0xFFFFU)
#define TEST_RM_PSIL_SRC_THREAD      (0x0000U)
#define TEST_RM_PSIL_DST_THREAD      (0x8001U)
#define TEST_RM_PSIL_TADDR           (0U)
#define TEST_RM_PSIL_WRITE_DATA      (0U)
#define TEST_RM_IRQ_SRC_DEV_ID       (0xFFFFU)
#define TEST_RM_IRQ_SRC_INDEX        (0U)
#define TEST_RM_IRQ_DST_DEV_ID       (0xFFFFU)
#define TEST_RM_IRQ_DST_HOST_IRQ     (0U)
#define TEST_RM_IRQ_SECONDARY_HOST   (0U)
#endif

/* ========================================================================== */
/*                 Forward Declarations for External Visibility               */
/* ========================================================================== */

/* Test wrapper functions — implemented in test_sciclient_rm.c */
void testSciclient_rmRing(void *args);
void testSciclient_rmUdmap(void *args);
void testSciclient_rmIrqPsil(void *args);
void testSciclient_rmProxy(void *args);
void testSciclient_rmResourceRange(void *args);

#endif /* TEST_SCICLIENT_RM_H_ */
