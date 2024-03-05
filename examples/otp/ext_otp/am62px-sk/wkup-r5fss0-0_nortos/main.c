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
#include <drivers/bootloader.h>
#include <kernel/dpl/CacheP.h>
#include "ext_otp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_ROW_IDX                    0x0U
#define INVALID_ROW_IDX                 45U
#define OTP_SET_ROW_LOCK_TRUE_VALUE     0x5AU
#define OTP_SET_ROW_LOCK_FALSE_VALUE    0xA5U



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
	uint32_t testMmrVal;
	uint32_t testRowValRdBk;
    uint8_t testGlobalsoftLock, testHwWriteLock, testHwReadLock;

    status = Bootloader_socWaitForFWBoot();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Board_init();
    Drivers_open();
    Board_driversOpen();

    DebugP_log("\r\n");
    DebugP_log("Starting EXT OTP writer\r\n");

	ext_otp_setVpp();
    DebugP_log("Enabled VPP\r\n");

    /* Program USB VID and PID */
    status = ext_otp_writeUsbVidPid(0x45a0, 0xe047);

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Error programming VID/PID \r\n");
    }
	else
	{
        DebugP_log("Success programming VID/PID \r\n");
	}

    if(status == SystemP_SUCCESS )
    {
        /* Test reading OTP MMR (non-zero results after POR) */
        status = ext_otp_readMmr(31, &testMmrVal);
    }

    if(status == SystemP_SUCCESS )
    {
        status = ext_otp_printMmrs();
    }

    if(status == SystemP_SUCCESS )
    {
        /* Read USB VID PID from control MMRs (non-zero results after POR) */
        status = ext_otp_getUsbVid(&testMmrVal);
        DebugP_log("USB VID: 0x%x \r\n", testMmrVal);
    }

    if(status == SystemP_SUCCESS )
    {
        status = ext_otp_getUsbPid(&testMmrVal);
        DebugP_log("USB PID: 0x%x \r\n", testMmrVal);
    }

    if(status == SystemP_SUCCESS )
    {
        /* Test writing OTP ROW */
        status = ext_otp_writeRow(TEST_ROW_IDX, 0x10, 0x10, &testRowValRdBk);
    }

    if(status == SystemP_SUCCESS )
    {
        /* Test Locking OTP ROW. The row index is set to invalid value.
         * The user can determine the rows to be locked based on the device
         * running the example.
         */
        status = ext_otp_lockRow(INVALID_ROW_IDX, OTP_SET_ROW_LOCK_TRUE_VALUE, OTP_SET_ROW_LOCK_TRUE_VALUE);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Lock row failed as expected for invalid row index\r\n");
            status = SystemP_SUCCESS;
        }
    }

    if(status == SystemP_SUCCESS )
    {
        /* Test Global soft write lock of OTP rows */
        status = ext_otp_softLockWriteGlobal();
        if(status == SystemP_SUCCESS)
        {
            DebugP_log("Success enabling global soft write lock of OTP rows \r\n");
        }
    }

    if(status == SystemP_SUCCESS )
    {
        /* Test get row lock status */
        status = ext_otp_getRowLockStatus(TEST_ROW_IDX, &testGlobalsoftLock, &testHwWriteLock, &testHwReadLock);
        DebugP_log("Lock status of row %d -> global soft lock: 0x%x, hw write lock: 0x%x, hw read lock: 0x%x\r\n",
                TEST_ROW_IDX,
                testGlobalsoftLock,
                testHwWriteLock,
                testHwReadLock);
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
