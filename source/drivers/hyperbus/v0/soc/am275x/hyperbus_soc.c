/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/hw_types.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/ClockP.h>
#include "hyperbus_soc.h"

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      API Function Definitions                              */
/* ========================================================================== */

uint32_t HYPERBUS_getInputClk(HYPERBUS_Handle handle)
{
    uint32_t retVal = 0U;
    if(handle != NULL)
    {
        const HYPERBUS_Attrs* attrs = ((HYPERBUS_Config *)handle)->attrs;
        retVal = attrs->inputClkFreq;
		if(retVal == 166666666U)
		{
			retVal = 333333333U;
		}
		else
		{
			retVal = retVal * 2U;
		}
    }
    return retVal;
}

int32_t HYPERBUS_powerClockInit(HYPERBUS_Handle handle)
{
	int32_t status = SystemP_SUCCESS;
    uint32_t clkfreq = 0U;

	status = SOC_moduleClockEnable(TISCI_DEV_FSS1_HYPERBUS1P0_0, 0U);

	if(SystemP_SUCCESS == status)
	{
		/* assert the reset */
		status = Sciclient_pmSetModuleRst(TISCI_DEV_FSS1_HYPERBUS1P0_0,
			0x1U,
			SystemP_WAIT_FOREVER);
	}

	if(SystemP_SUCCESS == status)
	{
		clkfreq = HYPERBUS_getInputClk(handle);

		status = SOC_moduleSetClockFrequency(
			TISCI_DEV_FSS1_HYPERBUS1P0_0,
			TISCI_DEV_FSS1_HYPERBUS1P0_0_HPB_CLKX2_CLK,
			clkfreq
			);
	}

	if(SystemP_SUCCESS == status)
	{
		status = SOC_moduleClockEnable(TISCI_DEV_FSS1_HYPERBUS1P0_0, 1U);
	}

	return status;
}
