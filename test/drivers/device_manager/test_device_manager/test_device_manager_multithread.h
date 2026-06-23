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

#ifndef TEST_DEVICE_MANAGER_MULTITHREAD_H_
#define TEST_DEVICE_MANAGER_MULTITHREAD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of threads for concurrent version query test */
#define TEST_DM_MT_THREADS              (2U)

/* Number of threads for concurrent multi-API test */
#define TEST_DM_MT_MULTIAPI_THREADS     (3U)

/* Number of threads for PM priority contention test */
#define TEST_DM_MT_PM_THREADS           (2U)

/* Number of threads for four-service simultaneous test */
#define TEST_DM_MT4_THREADS             (4U)

/* Number of threads for PM+Clock Set/Get priority-contention test */
#define TEST_DM_MT_PMCLK_THREADS        (2U)

/* Task priority for DM multi-thread test threads */
#define TEST_DM_TASK_PRIORITY           (8U)

/* Task priorities for the PM Set/Get priority-contention test */
#define TEST_DM_PM_HI_PRIORITY          (10U)
#define TEST_DM_PM_LO_PRIORITY          (6U)

/* Stack size (in bytes) for each DM multi-thread test thread
 * AM275X WKUP_R5_MSRAM is limited (502 KB), so reduce stack for AM275X builds
 * Sciclient API calls have modest stack depth (~4-6 KB typical)
 * AM62DX has sufficient OCMC RAM (4 MB+) so uses larger stack */
#if defined(SOC_AM275X)
#define TEST_DM_STACK_SIZE              (12 * 1024)
#else
#define TEST_DM_STACK_SIZE              (32 * 1024)
#endif

/* Number of repeated API calls per thread per test */
#define TEST_DM_LOOP_COUNT              (1U)

/* Device used for PM Set/Get contention test */
#if defined(SOC_AM62DX)
#define TEST_DM_PM_DEVICE_ID        TISCI_DEV_MCU_UART0
#elif defined(SOC_AM275X)
#define TEST_DM_PM_DEVICE_ID        TISCI_DEV_TIMER0
#else
#define TEST_DM_PM_DEVICE_ID        TISCI_DEV_MCU_UART0
#endif

/* Clock ID for PM Set/Get, four-service simultaneous, and concurrent SetClk tests */
#if defined(SOC_AM275X)
#define TEST_DM_MT4_CLK_ID          TISCI_DEV_TIMER0_TIMER_TCLK_CLK
#else
#define TEST_DM_MT4_CLK_ID          TISCI_DEV_MCU_UART0_FCLK_CLK
#endif

/* INTAGGR device for RM resource-range query (HOST_ID_ALL, read-only) */
#define TEST_DM_MT4_RM_INTAGGR_ID   TISCI_DEV_DMASS0_INTAGGR_0

/* ========================================================================== */
/*                     Function Declarations                                  */
/* ========================================================================== */

/**
 * Test: two threads concurrently issue TISCI_MSG_VERSION and TISCI_MSG_DM_VERSION.
 */
void testDM_multithreadConcurrentVersion(void *args);

/**
 * Test: three threads concurrently issue TISCI_MSG_VERSION, TISCI_MSG_QUERY_FW_CAPS,
 * and TISCI_MSG_DM_VERSION.
 */
void testDM_multithreadConcurrentMultiApi(void *args);

/**
 * Test: high-priority thread calls Sciclient_pmSetModuleState while a
 * low-priority thread concurrently calls Sciclient_pmGetModuleState.
 * Verifies that the high-priority Set operation completes without error.
 */
void testDM_pmSetStateHighPriVsGetStateLowPri(void *args);

/**
 * Test: Version, PM, RM, and Clock service threads run simultaneously.
 * All four threads must complete every API call without error.
 */
void testDM_allServicesSimultaneous(void *args);

/**
 * Test: two threads concurrently call Sciclient_pmSetModuleClkFreq on the same device.
 * Verifies that concurrent SetClk operations are properly serialized and thread-safe.
 */
void testDM_concurrentSetClock(void *args);

/**
 * Test: high-priority thread calls PM Set + Clock Set while a low-priority thread
 * concurrently calls PM Get + Clock Get on the same device.
 * Verifies that high-priority Set operations complete without error and low-priority
 * Get operations are not corrupted by concurrent Set traffic.
 */
void testDM_pmClkSetHighPriVsGetLowPri(void *args);

/**
 * Test: two threads concurrently call Sciclient_pmSetModuleState on the same device.
 * Verifies that concurrent SetDevice operations are properly serialized and thread-safe.
 */
void testDM_concurrentSetDevice(void *args);

#ifdef __cplusplus
}
#endif

#endif /* TEST_DEVICE_MANAGER_MULTITHREAD_H_ */
