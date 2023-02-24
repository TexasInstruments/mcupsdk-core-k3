/*
 * Copyright (C) 2022 Texas Instruments Incorporated
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


#define DDR_PLL_RESET

#if defined(DDR_PLL_RESET)

/* This is a piece of code that resets the DDR PLL to GEL configurable value which
    helps avoid us the DDR PLL entering a bad config after warm reset.
    This is a temporary fix and actual fix involves change in SCI client direct libs
*/

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

void DDR_programPLL(uint32_t Base_Address, uint32_t PLL_index, uint32_t Clocking_Scheme){

	uint32_t frefdiv = 0;
	uint32_t fbdiv = 0;
	int32_t frac = 0;
	uint32_t postdiv1 = 0;
	uint32_t postdiv2 = 0;
	int32_t div_val_0 = 0;
	int32_t div_val_1 = 0;
	int32_t div_val_2 = 0;
	int32_t div_val_3 = 0;
	int32_t div_val_4 = 0;
	int32_t div_val_5 = 0;
	int32_t div_val_6 = 0;
	int32_t div_val_7 = 0;
	int32_t div_val_8 = 0;
	int32_t div_val_9 = 0;
	uint32_t PLL_config_info;
	uint32_t HSDIV_Presence = 0;
	uint32_t Num_HSDIV = 0;
	uint32_t hsdiv_value = 0;
	uint32_t i = 0; //used for counting for any for loops.
	uint32_t temp = 0; //used for mathematical calculations.

	//Unlock the PLL
	DDR_unlockPLLMMR(Base_Address, PLL_index);

	//Grab the PLL configuration from memory.
	PLL_config_info = DDR_readMMR((Base_Address  + (PLL_index * 0x1000) + PLL_CONFIG), 0xFF, 0xFF);


	//Extract the PLL configuration from the register value.
	HSDIV_Presence = (PLL_config_info & 0xFFFF0000) >> 16; 	//Mask & shift the HSDIV presence field.

	//Need to reform Num_HSDIV. The index is programmed where each bit position represents the existence of a high speed divider.
	temp = HSDIV_Presence; //use a temp variable to avoid having to re-read the MMR to restore the value.

	while(temp != 0){
		temp = temp >> 1;	//shift right by 1.
		Num_HSDIV++; //Count how many bit positions are set to "1".
	}

	//*************************************************************************
	//Gather the PLL divider values for the speific PLL. Special programming modes will be provided later.
	if(Clocking_Scheme == OFC1){

		if(PLL_index == DDR_PLL_INDEX){
			fbdiv = MAIN_PLL12_OFC1_FBDIV;
			frac = MAIN_PLL12_OFC1_FRACDIV;
			frefdiv = MAIN_PLL12_OFC1_PREDIV;
			postdiv1 = MAIN_PLL12_OFC1_POSTDIV1;
			postdiv2 = MAIN_PLL12_OFC1_POSTDIV2;
            div_val_0 = MAIN_PLL12_OFC1_HSDIV0_DIV_VAL;
            div_val_1 = MAIN_PLL12_OFC1_HSDIV1_DIV_VAL;
            div_val_2 = MAIN_PLL12_OFC1_HSDIV2_DIV_VAL;
            div_val_3 = MAIN_PLL12_OFC1_HSDIV3_DIV_VAL;
            div_val_4 = MAIN_PLL12_OFC1_HSDIV4_DIV_VAL;
            div_val_5 = MAIN_PLL12_OFC1_HSDIV5_DIV_VAL;
            div_val_6 = MAIN_PLL12_OFC1_HSDIV6_DIV_VAL;
            div_val_7 = MAIN_PLL12_OFC1_HSDIV7_DIV_VAL;
            div_val_8 = MAIN_PLL12_OFC1_HSDIV8_DIV_VAL;
            div_val_9 = MAIN_PLL12_OFC1_HSDIV9_DIV_VAL;
		}
	}

	//Put the PLL in external bypass first. Write "1" to bit #31 in the control register.
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 1, 1, 31);


	//Disable PLL
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 0, 1, 15);


	//Set DACEN (Enable Factional DAC)
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 1, 1, 0);


	//Set DMEN (Enable Delta-Sigma Modulator)
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 1, 1, 1);


	//Set the reference divider value
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + OUTPUT_DIV_CONTROL), frefdiv, 6, 0);

	//Set the Feedback divider value (12-bit)
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + FREQ_CONTROL_0), fbdiv, 12, 0);


	//Set the fractional multipler/divider value (24-bit)
	if(frac >= 0){ //Sometimes, the fractional divider value will be set to a negative number.
		DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + FREQ_CONTROL_1), frac, 24, 0);
	}

	//Disable the 4-phase clock generator
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 0, 1, 5);

	//Set clk_postdiv_en (enables all the post-divider clocks, 4-phase, and synch. clocks)
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 1, 1, 4);


	//Set POSTDIV1
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + OUTPUT_DIV_CONTROL), postdiv1, 3, 16);

	//Set POSTDIV2
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + OUTPUT_DIV_CONTROL), postdiv2, 3, 24);

	//Program HSDIVs
	//HSDIV clocking scheme will already be present.
	if(Num_HSDIV){
		for(i = 0; i < Num_HSDIV; i++){
			//Program the HSDIVs.
			if(i == 0){
				hsdiv_value = div_val_0;
			}else if(i == 1){
				hsdiv_value = div_val_1;
			}else if(i == 2){
				hsdiv_value = div_val_2;
			}else if(i == 3){
				hsdiv_value = div_val_3;
			}else if(i == 4){
				hsdiv_value = div_val_4;
			}else if(i == 5){
				hsdiv_value = div_val_5;
			}else if(i == 6){
				hsdiv_value = div_val_6;
			}else if(i == 7){
				hsdiv_value = div_val_7;
			}else if(i == 8){
				hsdiv_value = div_val_8;
			}else if(i == 9){
				hsdiv_value = div_val_9;
			}
			if((int32_t)hsdiv_value >= (int32_t)0){ //If the HSDIV value is -1 then don't program the specific HSDIV.
				DDR_programHSDIV(Base_Address, PLL_index, i, hsdiv_value);
			}else{
				//Set the enable bit.
				DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + (i*0x4 + 0x80)), 0, 1, 15);

			}

		} //end of iterative loop over all existing HSDIVs
	}

	//Wait 1us
    ClockP_usleep(10);

	//Set the PLL enable bit.
	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 1, 1, 15);

	//Wait for the lock by polling on the lock bit to be set to "1"
	while(!DDR_readMMR((uint32_t)(Base_Address  + (PLL_index * 0x1000) + STATUS),0xFF,0xFF));

	DDR_writeMMR((Base_Address  + (PLL_index * 0x1000) + CONTROL), 0, 1, 31);
}

#endif

void DDR_ResetDDR_PLL(void){
#if defined(DDR_PLL_RESET)
    DDR_programPLL(CSL_PLL0_CFG_BASE, DDR_PLL_INDEX, OFC1);
#endif
}


