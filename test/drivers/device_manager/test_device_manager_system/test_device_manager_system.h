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

#ifndef TEST_DEVICE_MANAGER_SYSTEM_H_
#define TEST_DEVICE_MANAGER_SYSTEM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

/* SoC-specific device/clock IDs (TEST_DM_SYS_R5F_DEV, TEST_DM_SYS_R5F_CLK,
 * TEST_DM_SYS_UART_DEV) are defined in per-device header files. */
#if defined(SOC_AM62DX)
#include "am62dx-evm/test_device_manager_system_val.h"
#elif defined(SOC_AM275X)
#include "am275x-evm/test_device_manager_system_val.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Framework initialization test — print core startup message.
 *
 * Simple test that prints a startup message to verify the core is running
 * and logging is initialized.
 */
int32_t TestDM_system_init(void *args);

/**
 * \brief Query DM firmware version via TISCI_MSG_VERSION.
 *
 * Runs on the DM R5F in direct mode and on all remote cores (mcu-r5f, a53,
 * c75) via the sciclient proxy path.  Returns SystemP_SUCCESS when the DM
 * responds with TISCI_MSG_FLAG_ACK.
 */
int32_t TestDM_system_versionQuery(void *args);

/**
 * \brief Query hardware state of MCU R5F device via TISCI_MSG_GET_DEVICE.
 *
 * Exercises the device power-management path through the DM.  Returns
 * SystemP_SUCCESS when the DM ACKs and the device state is readable.
 */
int32_t TestDM_system_getDeviceState(void *args);

/**
 * \brief Query MCU R5F CPU clock frequency via TISCI_MSG_GET_FREQ.
 *
 * Exercises the clock power-management path through the DM.  Returns
 * SystemP_SUCCESS when the DM ACKs and the returned frequency is non-zero.
 */
int32_t TestDM_system_getClockFreq(void *args);

/**
 * \brief Set MCU R5F CPU0 clock state via TISCI_MSG_SET_CLOCK, run on every core.
 *
 * Each core: sets clock to SW_STATE_REQ, verifies HW state is READY via
 * TISCI_MSG_GET_CLOCK, then restores to SW_STATE_AUTO.  Exercises the full
 * set-clock path through the DM simultaneously from all cores.
 */
int32_t TestDM_system_setClock(void *args);

/**
 * \brief Set MCU UART0 device to ON state and verify via TISCI_MSG_GET_DEVICE.
 *
 * Each core independently issues TISCI_MSG_SET_DEVICE (SW_STATE_ON) for
 * TISCI_DEV_MCU_UART0, then reads back the device state and confirms
 * current_state == HW_STATE_ON.  Exercises the device PM set+verify path
 * from all cores simultaneously.
 */
int32_t TestDM_system_setDeviceOn(void *args);

#ifdef __cplusplus
}
#endif

#endif /* TEST_DEVICE_MANAGER_SYSTEM_H_ */
