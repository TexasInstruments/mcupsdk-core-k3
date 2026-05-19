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

#ifndef TEST_SCICLIENT_WRAPPER_H_
#define TEST_SCICLIENT_WRAPPER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_ra.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_udmap.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_irq.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_shared.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_psil.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/sciclient_lpm.h>

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */

/* SoC-specific test values (TEST_DEVICE_ID, WRAP_RM_*, proc-ID aliases) are
 * defined in per-device header files for AM62DX and AM275X.  Other SoCs use
 * inline fallback definitions below. */
#if defined(SOC_AM62DX)
#include "am62dx-evm/test_sciclient_val.h"
#elif defined(SOC_AM275X)
#include "am275x-evm/test_sciclient_val.h"
#endif

/* ========================================================================== */
/*                 Forward Declarations for External Visibility               */
/* ========================================================================== */

void testSciclient_powerManagement(void *args);
void testSciclient_firewallApis(void *args);
void testSciclient_coreVersion(void *args);
void testSciclient_resourceManagementSciclient(void *args);
void testSciclient_procBootSciclientApis(void *args);
void testSciclient_boardCfgApis(void *args);
void testSciclient_dkekApis(void *args);
void testSciclient_uartPrintf(void *args);
/* Sciclient_init / Sciclient_deinit wrapper (test_sciclient_wrapper.c) */
void testSciclient_initDeinit(void *args);
#if !(defined(SOC_AM275X) || defined(CORE_A53))
/* LPM API wrapper — 8 Sciclient_lpm* APIs (test_sciclient_wrapper.c) */
void testSciclient_lpmSciclient(void *args);
#endif /* !SOC_AM275X */

#endif /* TEST_SCICLIENT_WRAPPER_H_ */
