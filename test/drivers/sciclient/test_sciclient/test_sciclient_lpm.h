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

#ifndef TEST_SCICLIENT_LPM_H_
#define TEST_SCICLIENT_LPM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#include "test_sciclient_pm.h"

/* SoC-specific LPM test values (TISCI_HOST_ID, SCICLIENT_PROC_ID_* aliases)
 * are defined in per-device header files. */
#if defined(SOC_AM62DX)
#include "am62dx-evm/test_sciclient_val.h"
#elif defined(SOC_AM275X)
#include "am275x-evm/test_sciclient_val.h"
#elif defined(SOC_AM62AX)
#include "am62ax-sk/test_sciclient_val.h"
#elif defined(SOC_AM62PX)
#include "am62px-sk/test_sciclient_val.h"
#elif defined(SOC_AM62X)
#include "am62x-sk/test_sciclient_val.h"
#endif

/* ========================================================================== */
/*            Test Wrapper Function Declarations                              */
/* ========================================================================== */

/* wrapper — Low Power Management tests */
void testSciclient_lpm(void *args);
#endif /* TEST_SCICLIENT_LPM_H_ */
