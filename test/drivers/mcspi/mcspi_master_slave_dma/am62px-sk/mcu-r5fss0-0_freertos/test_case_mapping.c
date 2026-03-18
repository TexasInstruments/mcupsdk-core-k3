/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
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
 */

 /**
 *  \file test_case_mapping.c
 *
 *  \brief This file contains mapping of test case IDs to test functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "system_test_utils.h"
#include "test_mcspi_master_dma.h"
#include "test_mcspi_slave_dma.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TEST_MCSPI_SLAVE_CORE_ID      (CSL_CORE_ID_MCU_R5FSS0_0)
#define TEST_MCSPI_MASTER_CORE_ID     (CSL_CORE_ID_WKUP_R5FSS0_0)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* DMA is not supported in MCU Domain on AM62PX.
 * Master-Slave DMA test requires slave to run with DMA on main domain (SPI0/SPI1/SPI2),
 * but only uses interrupt mode in MCU domain. This architectural constraint prevents
 * proper master-slave DMA communication over the same physical bus.
 * Tests SITSW-9016 and SITSW-9015 are disabled for AM62PX.
 */
#if !defined(SOC_AM62PX)
testCase_t gTestCase[] =
{
    {TestMcspi_slaveTest1, 9016},
    {TestMcspi_slaveTest2, 9015},
    {NULL, 0}
};
#else
testCase_t gTestCase[] =
{
    {NULL, 0}
};
#endif

/* ========================================================================== */
/*                              Function Definitions                          */
/* ========================================================================== */

uint32_t get_master_core_id(void)
{
    return TEST_MCSPI_MASTER_CORE_ID;
}

uint32_t get_slave_core_id(void)
{
    return TEST_MCSPI_SLAVE_CORE_ID;
}
