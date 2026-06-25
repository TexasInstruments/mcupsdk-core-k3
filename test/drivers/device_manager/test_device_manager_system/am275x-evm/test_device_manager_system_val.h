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
 *  \file am275x-evm/test_device_manager_system_val.h
 *
 *  \brief AM275X-EVM specific device/clock IDs for the system test.
 *
 *  All values are derived from:
 *    - source/drivers/sciclient/include/tisci/am275x/tisci_devices.h
 *    - source/drivers/sciclient/include/tisci/am275x/tisci_clocks.h
 */

#ifndef AM275X_EVM_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_
#define AM275X_EVM_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_

/* ========================================================================== */
/*                         SOC-Specific Device / Clock IDs                    */
/* ========================================================================== */

#define TEST_DM_SYS_R5F_DEV     TISCI_DEV_WKUP_R5FSS0_CORE0
#define TEST_DM_SYS_R5F_CLK     TISCI_DEV_WKUP_R5FSS0_CORE0_CPU_CLK
#define TEST_DM_SYS_UART_DEV    TISCI_DEV_WKUP_UART0

#endif /* AM275X_EVM_TEST_DEVICE_MANAGER_SYSTEM_VAL_H_ */
