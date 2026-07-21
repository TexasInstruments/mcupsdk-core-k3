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
 *  \file test_sciclient_context.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the sciclient UT applications.
 */

#ifndef TEST_SCICLIENT_CONTEXT_H_
#define TEST_SCICLIENT_CONTEXT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_sciclient_val.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Internal Variables                             */
/* ========================================================================== */

uint32_t core_id_list[][4]={{CSL_CORE_ID_1,       SCICLIENT_CONTEXT_R5_SEC_0,            SCICLIENT_CONTEXT_R5_NONSEC_0,         TISCI_DEV_WKUP_R5FSS0_CORE0},
                            {CSL_CORE_ID_2,       SCICLIENT_CONTEXT_A53_SEC_0,           SCICLIENT_CONTEXT_A53_NONSEC_1,        TISCI_DEV_A53SS0_CORE_0},
                            {CSL_CORE_ID_3,       SCICLIENT_CONTEXT_MCU_R5_0_NONSEC_0,   SCICLIENT_CONTEXT_MCU_R5_0_NONSEC_0,   TISCI_DEV_MCU_R5FSS0_CORE0},
                            {CSL_CORE_ID_INVALID, SCICLIENT_CONTEXT_MAX_NUM,             SCICLIENT_CONTEXT_MAX_NUM,             SCICLIENT_DEV_ID_MAX},
                            };

/* ========================================================================== */
/*                             External Variables                             */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*None*/

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
