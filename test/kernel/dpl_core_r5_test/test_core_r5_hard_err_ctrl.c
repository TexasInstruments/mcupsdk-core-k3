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
 *  \file     test_core_r5_hard_err_ctrl.c
 *
 *  \brief    This file contains hard error control test code for R5 core.
 *
 *  \details  Hard error related register read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "core_r5_test.h"
#include <kernel/nortos/dpl/r5/UtilsP_armv7r.h>

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                        Test Function definitions                          */
/*===========================================================================*/

/* This test demonstrates the APIs to enable hard error cache
 */
int32_t core_r5_hardErrTest(void)
{
    /* Declarations of variables */
    int32_t    testResult = CORE_R5_APP_TEST_PASS;
    uint32_t   atcmRegionReg, btcmRegionReg;

    /* Read the ATCM and BTCM register values and write it back */
    atcmRegionReg = UtilsP_ReadATCMRegionRegister();
    btcmRegionReg = UtilsP_ReadBTCMRegionRegister();
    UtilsP_WriteATCMRegionRegister(atcmRegionReg);
    UtilsP_WriteBTCMRegionRegister(btcmRegionReg);

    /* disable the hard error Cache */
    UtilsP_CacheEnableHardErrCache(FALSE);

    /* Enable the hard error cahce for TCM */
    UtilsP_CacheEnableHardErrCache(TRUE);

   return (testResult);
}

