/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/security/tisci_otp_revision.h>
#include <drivers/bootloader.h>
#include <kernel/dpl/CacheP.h>
#include "otp_revision.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}

int main()
{
    int32_t status;

    status = Bootloader_socWaitForFWBoot();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Board_init();
    Drivers_open();
    Board_driversOpen();

    DebugP_log("\r\n");
    DebugP_log("Starting Runtime OTP revision writer\r\n");

    uint32_t swrev = 0xFFFFFFFFU, keyrev = 0xFFFFFFFFU, keycount = 0xFFFFFFFFU;

    /* Enable VPP first */
    otp_revsion_setVpp();

    /* Fetch the current software revision */
    status = otp_revsion_readSwrev(OTP_REV_ID_SEC_BRDCFG, &swrev);

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Error reading SWREV \r\n");
    }
	else
	{
        DebugP_log("SWREV read : 0x%x \r\n", swrev);
	}

    if(SystemP_SUCCESS == status)
    {
        if(swrev != 0)
        {
            DebugP_log("SWREV already written to eFUSE, value : 0x%x \r\n", swrev);
        }
        else
        {
            /* Update software revision for boardcfg*/
            status = otp_revsion_writeSwrev(OTP_REV_ID_SEC_BRDCFG, swrev + 1);
        }
    }

    if(SystemP_SUCCESS == status)
    {
        /* Fetch the current key revision and key count */
        status = otp_revsion_readKeyrevKeycnt(&keycount, &keyrev);

        if(status != SystemP_SUCCESS )
        {
            DebugP_log("Error reading key REV and key count \r\n");
        }
        else
        {
            DebugP_log("Value of Key REV: 0x%x and key count: 0x%x \r\n", keyrev, keycount);
        }
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }
    else
    {
        DebugP_log("All tests have passed!!\r\n");
    }

    Drivers_close();
    System_deinit();

    return 0;
}
