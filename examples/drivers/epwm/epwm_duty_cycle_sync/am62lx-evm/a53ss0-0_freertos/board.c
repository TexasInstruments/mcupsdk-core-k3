/*
 *  Copyright (C) 2024-2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <drivers/hw_include/cslr_soc.h>
#include "ti_board_open_close.h"
#include <board/ioexp/ioexp_tca6424.h>
#include <kernel/dpl/DebugP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOARD_I2C_ADDRESS_IO_EXAPANDER                  0x23U
#define BOARD_I2C_IO_EXPANDER_PIN_NUM                   0x01U

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TCA6424_Config ioExpConfig;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Board_userExpansionHeaderEnable(void)
{
    TCA6424_Params  tca6424Params;
    int32_t status = SystemP_SUCCESS;

    TCA6424_Params_init(&tca6424Params);
    tca6424Params.i2cInstance = CONFIG_I2C0;
    tca6424Params.i2cAddress = BOARD_I2C_ADDRESS_IO_EXAPANDER;

    status = TCA6424_open(&ioExpConfig, &tca6424Params);

    if(status == SystemP_SUCCESS)
    {
        status += TCA6424_config(&ioExpConfig, \
                                BOARD_I2C_IO_EXPANDER_PIN_NUM, \
                                TCA6424_MODE_OUTPUT);

        status += TCA6424_setOutput(&ioExpConfig, \
                                    BOARD_I2C_IO_EXPANDER_PIN_NUM,\
                                    TCA6424_OUT_STATE_HIGH);
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("Board User Exapansion header enable : Failed!!!\r\n");
    }
}