/*
 *   Copyright (c) Texas Instruments Incorporated 2025
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
 *  \file       ecc_main.c
 *
 * \brief       This file demonstrates using the Error Correcting Code Module (ECC),
 *              utilizing the ECC and ESM Software Diagnostic Reference (SDL) functions.
 *
 *  \details    ECC Safety Example module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ecc_main.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <sdl/dpl/sdl_dpl.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/sdl_ecc.h>
#include <dpl_interface.h>
#include <stdio.h>
#include "ti_drivers_config.h"
#include <sdl/include/sdl_types.h>


/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/*SDL ECC R5F Registers containing ECC error control bits */

#if defined (SOC_AM62DX) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
#define SDL_R5F_EVNT_BUS_ESM_CLR                                            (0x440001Cu)
#define SDL_R5F_VEC_REG                                                     (0x4707008u)
#define SDL_R5F_CTRL_REG                                                    (0x4707014u)
#define SDL_R5F_ERR_CTRL2_REG                                               (0x470701Cu)
#endif

#if defined (SOC_AM62X)
#define SDL_R5F_EVNT_BUS_ESM_CLR                                            (0x3c01801Cu)
#define SDL_R5F_VEC_REG                                                     (0x3f00d008u)
#define SDL_R5F_CTRL_REG                                                    (0x3f00d014u)
#define SDL_R5F_ERR_CTRL2_REG                                               (0x3f00d01Cu)
#endif

#if defined (SOC_AM275X)
#define SDL_R5F_EVNT_BUS_ESM_CLR                                            (0x5B0101Cu)
#define SDL_R5F_VEC_REG                                                     (0x730008u)
#define SDL_R5F_CTRL_REG                                                    (0x730014u)
#define SDL_R5F_ERR_CTRL2_REG                                               (0x73001Cu)
#endif

#define SDL_CLEAR_STATUS									(0x10u)
#define SDL_CLEAR_ALL_STATUS                                (0xffu)
#define SDL_ECC_SPECIFIC_VECTOR_VALUE                       (0x148000u)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile bool esmError = false;
volatile bool uknownErr = false;


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Prevents optimization to ensure error-clearing steps execute in order */

#pragma clang optimize off
void ECC_ERROR_CLEAR()
{

    uint32_t clearErr = 0;
    uint32_t evntbus_esm_clr;

    /* Stop the error injection from ECC aggr for dedicated ram_Id */
    SDL_REG32_WR(SDL_R5F_VEC_REG, ram_Id);                          /* Write ram_Id on ecc_vector register */
    SDL_REG32_WR(SDL_R5F_CTRL_REG, clearErr);                       /* Write 0 value on ecc control register */
    SDL_REG32_WR(SDL_R5F_VEC_REG, SDL_ECC_SPECIFIC_VECTOR_VALUE);
    /* Wait for ECC Aggrs. register update properly */

    while( ((*((uint32_t *)SDL_R5F_VEC_REG)>>24)&0X1) != 1u);

    evntbus_esm_clr = SDL_REG32_RD(SDL_R5F_EVNT_BUS_ESM_CLR);
    SDL_REG32_WR(SDL_R5F_EVNT_BUS_ESM_CLR, evntbus_esm_clr);
}
#pragma clang optimize on

int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInst,
                                            SDL_ESM_IntType esmIntrType,
                                            uint32_t grpChannel,
                                            uint32_t index,
                                            uint32_t intSrc,
                                            uintptr_t *arg)
{
    int32_t retVal = 0;
    ECC_ERROR_CLEAR();
    DebugP_log("\r\nESM Call back function called : instType 0x%x, intType 0x%x, " \
                "grpChannel 0x%x, index 0x%x, intSrc 0x%x \r\n",
                esmInst, esmIntrType, grpChannel, index, intSrc);
    DebugP_log("\r\nTake action \r\n");

    if(esmIntrType == SDL_ESM_INT_TYPE_HI){
        DebugP_log("\r\nHigh Priority Interrupt Executed\r\n");
    }
    else{
        DebugP_log("\r\nLow Priority Interrupt Executed\r\n");
    }

    esmError = true;
    return retVal;
}

void SDL_ECC_applicationCallbackFunction(SDL_ECC_MemType eccMemType,
                                         uint32_t errorSrc,
                                         uint32_t address,
                                         uint32_t ramId,
                                         uint64_t bitErrorOffset,
                                         uint32_t bitErrorGroup){

    DebugP_log("\r\n  ECC Error Call back function called : eccMemType %d, errorSrc 0x%x, " \
                "address 0x%x, ramId %d, bitErrorOffset 0x%04x%04x, bitErrorGroup %d\r\n",
                eccMemType, errorSrc, address, ramId, (uint32_t)(bitErrorOffset >> 32),
                (uint32_t)(bitErrorOffset & 0x00000000FFFFFFFF), bitErrorGroup);
    DebugP_log("\r\n Take action \r\n");

    /* Any additional customer specific actions can be added here */

}


void ecc_enable()
{
    asm("MRC p15, 0, r0, c1, c0, 0");              // Read System Control Register
    asm("BIC r0, r0, #0x1 << 2");                  // Disable data cache bit
    asm("BIC r0, r0, #0x1 << 12");                 // Disable instruction cache bit
    asm("DSB");
    asm("MCR p15, 0, r0, c1, c0, 0");              // Write System Control Register
    asm("ISB");                                    // Ensures following instructions are not executed from cache
    asm("MRC p15, 0, r1, c1, c0, 1");              // Read Auxiliary Control Register
    asm("ORR r1, r1, #(0x5 << 3)");                // Enable ECC for Cache
    asm("MCR p15, 0, r1, c1, c0, 1");              // Write Auxiliary Control Register
    asm("MCR p15, 0, r0, c15, c5, 0");             // Invalidate entire data cache
    asm("MCR p15, 0, r0, c7, c5, 0");              // Invalidate entire instruction cache
    asm("MRC p15, 0, r0, c1, c0, 0");              // Read System Control Register
    asm("ORR r0, r0, #0x1 << 2");                  // Enable data cache bit
    asm("ORR r0, r0, #0x1 << 12");                 // Enable instruction cache bit
    asm("DSB");
    asm("MCR p15, 0, r0, c1, c0, 0");              // Write System Control Register
    asm("ISB");
}

int32_t ecc_main(void)
{
	int32_t    testResult;

    /* Enable ECC for R5F Cache memories*/
    ecc_enable();

    DebugP_log("\r\nECC Application\r\n");
    testResult = ECC_funcTest();

    if (testResult == SDL_PASS)
    {
        DebugP_log("\r\nAll tests have passed. \r\n");
    }
    else
    {
        DebugP_log("\r\nSome tests have failed. \r\n");
    }

    /* Close drivers to close the UART driver for console */
    Board_driversClose();
    Drivers_close();
    while (true)
    {
    }
}

/* Nothing past this point */