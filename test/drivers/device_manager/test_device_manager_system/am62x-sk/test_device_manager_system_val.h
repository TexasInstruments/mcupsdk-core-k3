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
 *  \file am62x-sk/test_device_manager_system_val.h
 *
 *  \brief AM62X-SK specific device/clock IDs for the system test.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am62x/tisci_devices.h
 *    - source/drivers/sciclient/include/tisci/am62x/tisci_clocks.h
 *
 *  AM62X has an MCU M4F (MCU_M4FSS0_CORE0) instead of an MCU R5F.
 *  TEST_DM_SYS_R5F_DEV / TEST_DM_SYS_R5F_CLK map to the M4F core
 *  device/clock, which is the MCU-domain secondary core on AM62X.
 */

#ifndef AM62X_SK_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_
#define AM62X_SK_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_

/* ========================================================================== */
/*                         SOC-Specific Device / Clock IDs                    */
/* ========================================================================== */

/* MCU M4F core — used as the secondary-core device under test */
#define TEST_DM_SYS_R5F_DEV     TISCI_DEV_MCU_M4FSS0_CORE0
#define TEST_DM_SYS_R5F_CLK     TISCI_DEV_MCU_M4FSS0_CORE0_VBUS_CLK
#define TEST_DM_SYS_UART_DEV    TISCI_DEV_MCU_UART0

#endif /* AM62X_SK_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_ */
