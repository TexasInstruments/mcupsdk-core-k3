/*
*  Copyright (c) Texas Instruments Incorporated 2023
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
*  \file vhwa_ldc_tirtos_cfg.h
*
*  \brief Configuration for TI RTOS
*/
#ifndef VHWA_LDC_TIRTOS_CFG_
#define VHWA_LDC_TIRTOS_CFG_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VHWA_LDC_TIRTOS_CFG                                                    \
{                                                                              \
    /* 0, 2MP NV12 8p to 8p, with block size aligned */                        \
    {                                                                          \
        "TC_LDC_FUNC_000",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        4u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[0U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
    /* 1, 2MP YUV422I 12p, with block size aligned */                          \
    {                                                                          \
        "TC_LDC_FUNC_001",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        1u,                     /* Repeat Cnt */                               \
        FALSE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[1U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
    /* 2, 2MP YUV422SP 12u to 12u, with block size aligned */                  \
    {                                                                          \
        "TC_LDC_FUNC_002",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        1u,                     /* Repeat Cnt */                               \
        FALSE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[2U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
    /* 3, 2MP Y8 + Y8 , with block size aligned */                             \
    {                                                                          \
        "TC_LDC_FUNC_003",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        1u,                     /* Repeat Cnt */                               \
        FALSE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[3U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
     /* 4, 2MP YUV420SP Y12 UV8, with block size aligned */                    \
    {                                                                          \
        "TC_LDC_FUNC_004",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        1u,                     /* Repeat Cnt */                               \
        FALSE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[4U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
     /* 5, 2MP YUV420SP Y8 UV12, with block size aligned */                    \
    {                                                                          \
        "TC_LDC_FUNC_005",      /* Test Name */                                \
        1u,                     /* Num Handles */                              \
        1u,                     /* Repeat Cnt */                               \
        FALSE,                  /* Is Performance Test */                       \
        /* Test Configuration */                                               \
        {                                                                      \
            &gAppLdcTestCfg[5U]                                                \
        },                                                                     \
        TRUE                                                                   \
    },                                                                         \
}

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#endif /*VHWA_LDC_TIRTOS_CFG_*/
