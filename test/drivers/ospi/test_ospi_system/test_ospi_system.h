/*
 *  Copyright (c)  2021-2026 Texas Instruments Incorporated
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
 *  \file test_ospi_system.h
 *
 *  \brief This file contains all the structures, macros, enums,
 *  function declarations used by the MMCSD emmc test cases
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <board/flash.h>
#include <drivers/ospi.h>
#include <drivers/ospi/v0/ospi.h>
#include <drivers/ospi/v0/dma/ospi_dma.h>
#include <drivers/soc.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macro  Defines                                   */
/* ========================================================================== */

#define TEST_OSPI_FLASH_OFFSET_BASE        (0x200000U)
#define TEST_OSPI_FLASH_PHY_TUNING_OFFSET  (0x300000U)
#define TEST_OSPI_DATA_SIZE                (256U) /* has to be 256 B aligned */

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
#define TEST_OSPI_1KB_SIZE                 (256*4U)
#define TEST_OSPI_2KB_SIZE                 (TEST_OSPI_1KB_SIZE*2U)
#define TEST_OSPI_1MB_SIZE                 (TEST_OSPI_1KB_SIZE*TEST_OSPI_1KB_SIZE)
#define TEST_OSPI_10MB_SIZE                (TEST_OSPI_1MB_SIZE*10U)
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_10MB_SIZE)
#endif /* defined(SOC_AM62AX) || defined(SOC_AM62DX) */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t TestOspi_writeReadIndirectFunctional(void *args);
int32_t TestOspi_getHandle(void *args);

