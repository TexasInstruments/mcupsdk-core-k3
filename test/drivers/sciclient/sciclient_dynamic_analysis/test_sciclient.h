/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file test_sciclient.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  functions used by the device manager UT applications.
 */

#ifndef TEST_SCICLIENT_H_
#define TEST_SCICLIENT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "../../../unity/unity.h"
#include "../../../../source/drivers/sciclient.h"
#include "../../../../source/drivers/sciclient/sciclient_priv.h"
#include "../../../../source/drivers/sciclient/sciclient_rm_priv.h"
#include <drivers/sciclient/include/tisci/security/tisci_ext_otp.h>
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#if defined (SOC_AM62AX)
#include "am62ax-sk/test_sciclient_val.h"
#include <drivers/sciclient/soc/am62ax/sciclient_soc_priv.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_clocks.h>
#elif defined (SOC_AM62PX)
#include "am62px-sk/test_sciclient_val.h"
#include <drivers/sciclient/soc/am62px/sciclient_soc_priv.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_clocks.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

int8_t test_sciclient(void);
int8_t test_sciclient_rm(void);
int8_t test_sciclient_pm(void);
int8_t test_sciclient_lpm(void);
int8_t test_sciclient_rm_irq(void);
int8_t test_sciclient_firewall(void);
int8_t test_sciclient_procboot(void);
int8_t test_sciclient_soc_priv(void);
int8_t test_csl_sec_proxy(void);

/* ========================================================================== */
/*                           External Function                                */
/* ========================================================================== */

extern void localFpMemAccess( uintptr_t addr, uint8_t *pData, uint32_t elemSizeBytes, uint32_t elemCnt );


#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
