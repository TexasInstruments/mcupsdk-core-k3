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

#ifndef TEST_DEVICE_MANAGER_SEC_H_
#define TEST_DEVICE_MANAGER_SEC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/security/tisci_ext_otp.h>
#include <drivers/sciclient/include/tisci/security/tisci_otp_revision.h>
#include <drivers/sciclient/include/tisci/security/tisci_sec_handover.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
#include <drivers/sciclient/include/tisci/security/tisci_dsmek.h>
#include <drivers/sciclient/include/tisci/security/tisci_keywriter.h>
#include <drivers/sciclient/include/tisci/security/tisci_keyring.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */

/* SoC-specific capability flags (DM_TEST_FWL_ID0_SUPPORTED, etc.) are
 * defined in per-device header files. */
#if defined(SOC_AM62DX)
#include "am62dx-evm/test_device_manager_val.h"
#elif defined(SOC_AM62AX)
#include "am62ax-sk/test_device_manager_val.h"
#elif defined(SOC_AM275X)
#include "am275x-evm/test_device_manager_val.h"
#elif defined(SOC_AM62PX)
#include "am62px-sk/test_device_manager_val.h"
#endif

/* ========================================================================== */
/*            Test Wrapper Function Declarations                              */
/* ========================================================================== */

/* wrapper — OTP & Key Management (read-only safe queries) */
void testDM_otpKeyMgmt(void *args);

/* wrapper — Security & Encryption (SEC_HANDOVER, KEY_WRITER, KEYRING_IMPORT) */
void testDM_securityEncryption(void *args);

/* wrapper — SA2UL Crypto Accelerator (DKEK / DSMEK) */
void testDM_sa2ulCrypto(void *args);

/* wrapper — Firewall Management */
void testDM_firewallMgmt(void *args);

#endif /* TEST_DEVICE_MANAGER_SEC_H_ */
