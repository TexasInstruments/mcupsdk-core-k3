/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file   dm_ut_clocks_list.c
 *
 *  \brief  This file contains lists of different types of clocks for C7X and A72 core present on J784S4.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/sciclient/include/tisci/j722s/tisci_devices.h>
#include <drivers/sciclient/include/tisci/j722s/tisci_clocks.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max frequency supported by C7X core (1GHz) */
#define DM_APP_C7X_MAX_FREQ          ((uint64_t) 1000000000U)

/* Max frequency supported by A72 core (2GHz) */
#define DM_APP_A72_MAX_FREQ          ((uint64_t) 2000000000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

const uint32_t gDMAppProcessorClocks[][3] = {
    /* These are C7XV clocks */
    {
        TISCI_DEV_C7X256V0_C7XV_CORE_0,
        TISCI_DEV_C7X256V0_C7XV_CORE_0_C7XV_CLK,
        DM_APP_C7X_MAX_FREQ
    },

    {
        TISCI_DEV_C7X256V0_CLK,
        TISCI_DEV_C7X256V0_CLK_C7XV_CLK,
        DM_APP_C7X_MAX_FREQ
    },

    /* These are A53 Clocks comming from main_PLL8 */
    {
        TISCI_DEV_A53SS0_CORE_0,
        TISCI_DEV_A53SS0_CORE_0_A53_CORE0_ARM_CLK_CLK,
        DM_APP_A72_MAX_FREQ
    },

    {
        TISCI_DEV_A53SS0_CORE_1,
        TISCI_DEV_A53SS0_CORE_1_A53_CORE1_ARM_CLK_CLK,
        DM_APP_A72_MAX_FREQ
    },

    {
        TISCI_DEV_A53SS0_CORE_2,
        TISCI_DEV_A53SS0_CORE_2_A53_CORE2_ARM_CLK_CLK,
        DM_APP_A72_MAX_FREQ
    },

    {
        TISCI_DEV_A53SS0_CORE_3,
        TISCI_DEV_A53SS0_CORE_3_A53_CORE3_ARM_CLK_CLK,
        DM_APP_A72_MAX_FREQ
    },

    {
        TISCI_DEV_A53SS0,
        TISCI_DEV_A53SS0_COREPAC_ARM_CLK_CLK,
        DM_APP_A72_MAX_FREQ
    },

    {
        TISCI_DEV_COMPUTE_CLUSTER0_CLKDIV_0,
        TISCI_DEV_COMPUTE_CLUSTER0_CLKDIV_0_FUNC_CLKIN_CLK,
        DM_APP_A72_MAX_FREQ
    }
};

uint32_t gDMAppProcessorClocksSize = sizeof(gDMAppProcessorClocks)/sizeof(gDMAppProcessorClocks[0]);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */
