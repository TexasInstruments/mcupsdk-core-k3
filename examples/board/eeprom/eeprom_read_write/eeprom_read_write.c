/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_BUF_SIZE                    (20)
#define APP_OFFSET                      (1000)
/* offsset + size shoud be less than 64KB */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


void  eeprom_read_write(void);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Allocate as uint32_t so that write pattern can be more than 256 so that we
 * can avoid any wrap around mistakes */
uint8_t gReadBuffer[APP_BUF_SIZE ];
uint8_t gWriteBuffer[APP_BUF_SIZE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void eeprom_main(void *args)
{
    eeprom_read_write();

    return;
}

void eeprom_read_write(void)
{
    int32_t status;

    EEPROM_Handle   eepromHandle = gEepromHandle[CONFIG_EEPROM0];
    uint32_t        offset = APP_OFFSET;
    uint32_t        size   = APP_BUF_SIZE;
    uint32_t        index;

    /* Write Buffer is filling with some values*/
    for(index = 0; index < APP_BUF_SIZE; index++)
    {
        gWriteBuffer[index] = index + 10;
    }

    DebugP_log("Writing to the EEPROM Started ...\n\r");
    status = EEPROM_write(eepromHandle, offset, gWriteBuffer, size);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("Writing to the EEPROM is SUCCESS...\n\r");
    }
    else
    {
        DebugP_log("Writing to the EEPROM is FAILED...\n\r");
        return;
    }

    DebugP_log("Reading  the EEPROM Started ...\n\r");
    status = EEPROM_read(eepromHandle, offset, gReadBuffer, size);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("Reading  the EEPROM is SUCCESS ...\n\r");

        for(index = 0; index < APP_BUF_SIZE; index++)
        {
            DebugP_log("Read samples are %u\r\n",gReadBuffer[index]);
        }
        DebugP_log("Reading  the EEPROM is Done...\n\r");
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Reading  the EEPROM is FAILED ...\n\r");
        return;
    }

}

