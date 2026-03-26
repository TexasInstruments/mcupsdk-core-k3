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
 */

/**
 *  \file  dm_ut_testparser.h
 *
 *  \brief This file contains common structures, macros and function declarations
 *         used by the DM unit test parser.
 */

#ifndef DM_UT_TESTPARSER_H_
#define DM_UT_TESTPARSER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor DMApp_InputVal
 *  \name DM app input parameter value
 *  @{
 */
#define DM_APP_RUN_TEST_ID                 ('1')
#define DM_APP_RUN_TESTS_ALL               ('2')
#define DM_APP_PRINT_ALL_TESTS             ('d')
#define DM_APP_PRINT_TEST_ID               ('t')
#define DM_APP_PRINT_RESULTS               ('g')
#define DM_APP_PARSER_QUIT                 ('q')
/* @} */

#define DM_APP_DEVICE_TEST                 (1U)
#define DM_APP_CLOCK_TEST                  (2U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Parse the testcase data.
 *
 * \param   None.
 *
 * \return  None.
 */
void DMApp_parser(void);

/* ========================================================================== */
/*                        Internal Function Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Function Definitions                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Internal Function Definitions                       */
/* ========================================================================== */

/* None */

#endif /* DM_UT_TESTPARSER_H_ */
