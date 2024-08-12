/*
*  Copyright (c) Texas Instruments Incorporated 2023-24
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
*  \file vhwa_msc_tirtos_cfg.h
*
*  \brief Configuration for TI RTOS
*/
#ifndef VHWA_MSC_TIRTOS_CFG_
#define VHWA_MSC_TIRTOS_CFG_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(VHWA_VPAC_IP_REV_VPAC3L)
#define VHWA_MSC_TIRTOS_CFG                                                    \
{                                                                              \
    /* 0 - Thread 0, 1-in 10-out 1920x1080 12bit packed input and 12bit packed output */    \
    {                                                                          \
        "TC_MSC_FUNC_TC00",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[3U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 1 - Thread 0, 1-in 5-out 1920x1080 Y12 UV8 */    \
    {                                                                          \
        "TC_MSC_FUNC_TC01",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[4U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 2 - Instance 0 TestCase 1-in 5-out 1920x1080 12bit packed input and 12bit packed output */    \
    {                                                                          \
        "TC_MSC_FUNC_TC02",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[5U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 3 - Instance 1 TestCase 1-in 5-out 1920x1080 12bit packed input and 12bit packed output */    \
    {                                                                          \
        "TC_MSC_FUNC_TC03",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[6U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 4 - Instance 0 TestCase 1-in 5-out 1920x1080 Y8 UV12 */    \
    {                                                                          \
        "TC_MSC_FUNC_TC04",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[7U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 5 - Instance 0 TestCase 1-in 5-out 1920x1080 Y8 Y8 */    \
    {                                                                          \
        "TC_MSC_FUNC_TC05",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[8U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 6 - Instance 0, 1920x1080 YUV422SP 12bit unpacked input/output */    \
    {                                                                          \
        "TC_MSC_FUNC_TC06",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[9U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
    /* 7 - Instance 0 TestCase 1-in 4-out 1920x1080 YUV422I 12bit unpacked input/output */    \
    {                                                                          \
        "TC_MSC_FUNC_TC07",                                                    \
        1u,                     /* NumHandles */                               \
        5u,                     /* Repeat Cnt */                               \
        TRUE,                  /* Is Performance Test */                      \
        {&gAppMscTestCfg[10U] },                                                \
        TRUE,                                                                  \
    },                                                                         \
}
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#endif /*VHWA_MSC_TIRTOS_CFG_*/
