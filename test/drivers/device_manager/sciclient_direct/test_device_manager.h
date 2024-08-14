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
 *  \file test_device_manager.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  functions used by the device manager UT applications.
 */

#ifndef TEST_DEVICE_MANAGER_H_
#define TEST_DEVICE_MANAGER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciserver.h>
#include <drivers/device_manager/sciclient_direct/sciclient_priv.h>
#include <drivers/device_manager/version/sciserver_version.h>
#include <drivers/device_manager/sciserver/sciserver_init.h>
#include <drivers/device_manager/sciserver_tirtos.h>
#include <drivers/device_manager/sciserver/sciserver_secproxyRoutingDescription.h>
#include <drivers/device_manager/sciserver/sciserver_secproxyTransfer.h>
#include <drivers/device_manager/sciclient_direct/sciclient_rm_priv.h>
#include <drivers/device_manager/rm_pm_hal/rm_pm_hal_src/include/tisci/tisci_protocol.h>

#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"

#if defined (SOC_AM62X)
#include "am62x-sk/test_sciclient_val.h"
#include <drivers/sciclient/soc/am62x/sciclient_soc_priv.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_clocks.h>
#elif defined (SOC_AM62AX)
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
int8_t test_sciserver(void);
int8_t test_sciclient_rm(void);
int8_t test_sciclient_pm(void);
int8_t test_sciclient_dkek(void);
int8_t test_sciserver_init(void);
int8_t test_sciserver_tirtos(void);
int8_t test_sciclient_direct(void);
int8_t test_sciclient_rm_irq(void);
int8_t test_sciclient_firewall(void);
int8_t test_sciclient_procboot(void);
int8_t test_sciclient_boardcfg(void);
int8_t test_sciclient_setdevice(void);
int8_t test_sciclient_boardcfgRM(void);
int8_t test_sciclient_keyWriting(void);
int8_t test_sciclient_lowPowerReq(void);
int8_t test_sciclient_queryFwCaps(void);
int8_t test_sciclient_secureproxy(void);
int8_t test_sciclient_directWrapper(void);
int8_t test_sciclient_serviceSecProxy(void);
int8_t test_sciclient_boardCfgPrepHdr(void);
int8_t test_sciclient_boardCfgParseHdr(void);
int8_t test_sciclient_processPmMessage(void);
int8_t test_sciserver_secproxyTransfer(void);
int8_t test_sciclient_secproxyRoutingDescription(void);
void test_sciclient_version(void *args);
void test_sciclient_rm_ir_output(void *args);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
