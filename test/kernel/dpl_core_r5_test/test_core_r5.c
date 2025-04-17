/**
 *  Copyright (C) 2023-25 Texas Instruments Incorporated.
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
 *  \file     test_core_r5.c
 *
 *  \brief    This file contains R5 Core test
 *
 *  \details  Core R5 read/write, configuration tests
 **/

/* =========================================================================== */
/*                          Include files                                      */
/* =========================================================================== */

#include "core_r5_test.h"

/* =========================================================================== */
/*                          Declarations                                       */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                          Macros                                             */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                          Internal function declarations                     */
/* =========================================================================== */

void core_r5_test_main(void);

/* =========================================================================== */
/*                          Global Variables                                   */
/* =========================================================================== */

coreR5Test_t  coreR5TestList[] = {
    /* Do not change the order mpu test as this needs to be the first one
     * to be run to setup the mpu for the application */
    {core_r5_mpuTest,        "MPU CFG TEST"             },
    {core_r5_pmuTest,        "PMU CFG TEST"             },
    {core_r5_hardErrTest,    "HARDERR CFG TEST"         },
    {core_r5_cacheTest,      "CACHE APIS TEST"          },
    {NULL,                   "TERMINATING CONDITION"    }
};

/* =========================================================================== */
/*                          Function definitions                               */
/* =========================================================================== */

void core_r5_test_main(void)
{
    /* Declarations of variables */
    int32_t    testResult = CORE_R5_APP_TEST_PASS;
    int32_t    i;

    DebugP_log("\nR5 CORE Test Application\r\n");

    for ( i = 0; coreR5TestList[i].testFunction != NULL; i++)
    {
        testResult = coreR5TestList[i].testFunction();
        /* stop the test if result is not successful */
        if (testResult != CORE_R5_APP_TEST_PASS)
        {
             break;
        }
    }

    if (testResult == CORE_R5_APP_TEST_PASS)
    {
        DebugP_log("\n All tests have passed.\r\n");
    }
    else
    {
        DebugP_log("\n Few/all tests have failed.\r\n");
    }
}

