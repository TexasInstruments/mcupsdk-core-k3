/*
 * Copyright (C) 2024 Texas Instruments Incorporated
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

#include <stdint.h>
#include <drivers/hw_include/hw_types.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/ClockP.h>


void DDR_socEnableVttRegulator(void)
{
    return;
}

#define CSL_PLL0_CFG_BASE 					(0x680000UL)
#define DDR_PLL_INDEX		                12

#define OFC1 		                        1

#define PLL_CONFIG 			                (0x08U)
#define CONTROL 			                (0x20U)
#define STATUS				                (0x24U)
#define FREQ_CONTROL_0 		                (0x30U)
#define FREQ_CONTROL_1 		                (0x34U)
#define OUTPUT_DIV_CONTROL 	                (0x38U)


#define MAIN_PLL12_OFC1_FBDIV               64
#define MAIN_PLL12_OFC1_FRACDIV             -1
#define MAIN_PLL12_OFC1_PREDIV              1
#define MAIN_PLL12_OFC1_POSTDIV1            1
#define MAIN_PLL12_OFC1_POSTDIV2            1
#define MAIN_PLL12_OFC1_HSDIV0_DIV_VAL      1 //2
#define MAIN_PLL12_OFC1_HSDIV1_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV2_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV3_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV4_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV5_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV6_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV7_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV8_DIV_VAL      -1
#define MAIN_PLL12_OFC1_HSDIV9_DIV_VAL      -1
#define MAIN_PLL12_OFC1_SSMOD_SPREAD        -1
#define MAIN_PLL12_OFC1_SSMOD_MODDIV        -1
#define MAIN_PLL12_OFC1_SSMOD_DOWNSPREAD    -1

#define KICK0_UNLOCK 	0x68EF3490
#define KICK1_UNLOCK 	0xD172BC5A

void DDR_unlockPLLMMR(uint32_t Base_Address,uint32_t PLL_index){
	volatile uint32_t* first_mmr;
    volatile uint32_t* second_mmr;
	first_mmr = (volatile uint32_t*)(0x10 + (PLL_index * 0x1000) + Base_Address);
	//Calculate tthe second lock register address based on the PLL index.
	second_mmr = (volatile uint32_t*)(0x14 + (PLL_index * 0x1000) + Base_Address);


    // if either of the kick lock registers are locked
    if (!(*first_mmr & 0x1) || !(*second_mmr & 0x1)){
        // unlock the partition by writing the unlock values to the kick lock registers
        *first_mmr = KICK0_UNLOCK;
        *second_mmr = KICK1_UNLOCK;
    }

}

void DDR_writeMMR(uint32_t mmr_address, uint32_t field_value, uint32_t width, uint32_t leftshift)
{
    volatile uint32_t *p_mmr;
    uint32_t mask;
    p_mmr = (volatile uint32_t *) mmr_address;
    mask = ((1 << width) - 1 ) << leftshift;
    mask = ~(mask);
    *p_mmr &= mask;
    *p_mmr |= (field_value << leftshift);
}

uint32_t DDR_readMMR(uint32_t mmr_address, uint32_t width, uint32_t leftshift){
    volatile uint32_t *p_mmr;
    uint32_t mask;
    uint32_t retval;
    p_mmr = (volatile uint32_t*) mmr_address;
    if(width == 0xFF && leftshift == 0xFF)
    {
        retval = *p_mmr;
    }
    else
    {
        mask = ((1 << width) - 1) << leftshift;
        retval = (*p_mmr & mask) >> leftshift;
    }

    return retval;
}

void DDR_programHSDIV(uint32_t Base_Address, uint32_t PLL_index, uint32_t HSDIV_index, uint32_t hsdiv_value){


	DDR_writeMMR((Base_Address + (PLL_index * 0x1000) + (HSDIV_index*0x4 + 0x80)), 1, 1, 31);

	DDR_writeMMR((Base_Address + (PLL_index * 0x1000) + (HSDIV_index*0x4 + 0x80)), hsdiv_value, 7, 0);

	if(!DDR_readMMR((Base_Address + (PLL_index * 0x1000) + (HSDIV_index*0x4 + 0x80)), 1, 15)){

		DDR_writeMMR((Base_Address + (PLL_index * 0x1000) + (HSDIV_index*0x4 + 0x80)), 1, 1, 15);
	}

	DDR_writeMMR((Base_Address + (PLL_index * 0x1000) + (HSDIV_index*0x4 + 0x80)), 0, 1, 31);
}
