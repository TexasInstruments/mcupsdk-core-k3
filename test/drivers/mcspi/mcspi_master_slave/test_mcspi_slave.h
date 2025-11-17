/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file test_mcspi_slave.h
 *
 *  \brief This file contains all the structures, macros, enums,
 *  function declarations used by the MCSPI slave test cases
 *
 */

#ifndef TEST_MCSPI_SLAVE_H_
#define TEST_MCSPI_SLAVE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "ti_drivers_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */



/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern int32_t TestMcspi_slaveTest1(void *args);
extern int32_t TestMcspi_slaveTest2(void *args);
extern int32_t TestMcspi_slaveTest3(void *args);
extern int32_t TestMcspi_slaveTest4(void *args);
extern int32_t TestMcspi_slaveTest5(void *args);
extern int32_t TestMcspi_slaveTest6(void *args);
extern int32_t TestMcspi_slaveTest7(void *args);
extern int32_t TestMcspi_slaveTest8(void *args);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef TEST_MCSPI_SLAVE_H_ */
