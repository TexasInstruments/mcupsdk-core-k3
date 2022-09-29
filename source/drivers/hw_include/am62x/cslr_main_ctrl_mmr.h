/********************************************************************
 * Copyright (C) 2021 Texas Instruments Incorporated.
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
 *  Name        : cslr_main_ctrl_mmr.h
*/
#ifndef CSLR_MAIN_CTRL_MMR_H_
#define CSLR_MAIN_CTRL_MMR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE                                  (0x00000000U)


/**************************************************************************
* Hardware Region  : MMRs in region 0
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* PID register */
    volatile uint32_t MMR_CFG0;
    volatile uint32_t MMR_CFG1;
    volatile uint8_t  Resv_768[756];
    volatile uint32_t SPARE_FUSE0;
    volatile uint8_t  Resv_4104[3332];
    volatile uint32_t LOCK0_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK0_KICK1;               /*  - KICK1 component */
    volatile uint32_t INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    volatile uint32_t INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    volatile uint32_t INTR_ENABLE;               /* Interrupt Enable register */
    volatile uint32_t INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    volatile uint32_t EOI;                       /* EOI register */
    volatile uint32_t FAULT_ADDRESS;             /* Fault Address register */
    volatile uint32_t FAULT_TYPE_STATUS;         /* Fault Type Status register */
    volatile uint32_t FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    volatile uint32_t FAULT_CLEAR;               /* Fault Clear register */
    volatile uint8_t  Resv_4352[204];
    volatile uint32_t CLAIMREG_P0_R0_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R1_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R2_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R3_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R4_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R5_READONLY;   /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R6_READONLY;   /* Claim bits for Partition 0 */
    volatile uint8_t  Resv_8192[3812];
    volatile uint32_t PID_PROXY;                 /* PID register */
    volatile uint32_t MMR_CFG0_PROXY;
    volatile uint32_t MMR_CFG1_PROXY;
    volatile uint8_t  Resv_8960[756];
    volatile uint32_t SPARE_FUSE0_PROXY;
    volatile uint8_t  Resv_12296[3332];
    volatile uint32_t LOCK0_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK0_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint32_t INTR_RAW_STATUS_PROXY;     /* Interrupt Raw Status/Set Register */
    volatile uint32_t INTR_ENABLED_STATUS_CLEAR_PROXY;   /* Interrupt Enabled Status/Clear register */
    volatile uint32_t INTR_ENABLE_PROXY;         /* Interrupt Enable register */
    volatile uint32_t INTR_ENABLE_CLEAR_PROXY;   /* Interrupt Enable Clear register */
    volatile uint32_t EOI_PROXY;                 /* EOI register */
    volatile uint32_t FAULT_ADDRESS_PROXY;       /* Fault Address register */
    volatile uint32_t FAULT_TYPE_STATUS_PROXY;   /* Fault Type Status register */
    volatile uint32_t FAULT_ATTR_STATUS_PROXY;   /* Fault Attribute Status register */
    volatile uint32_t FAULT_CLEAR_PROXY;         /* Fault Clear register */
    volatile uint8_t  Resv_12544[204];
    volatile uint32_t CLAIMREG_P0_R0;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R1;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R2;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R3;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R4;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R5;            /* Claim bits for Partition 0 */
    volatile uint32_t CLAIMREG_P0_R6;            /* Claim bits for Partition 0 */
    volatile uint8_t  Resv_16452[3880];
    volatile uint32_t ENET1_CTRL;
    volatile uint32_t ENET2_CTRL;
    volatile uint8_t  Resv_16640[180];
    volatile uint32_t ICSSM0_CTRL0;
    volatile uint8_t  Resv_16688[44];
    volatile uint32_t EPWM_TB_CLKEN;
    volatile uint8_t  Resv_16700[8];
    volatile uint32_t EPWM_ERR_STAT;
    volatile uint32_t EPWM0_CTRL;
    volatile uint32_t EPWM1_CTRL;
    volatile uint32_t EPWM2_CTRL;
    volatile uint8_t  Resv_16752[36];
    volatile uint32_t SOCA_SEL;
    volatile uint32_t SOCB_SEL;
    volatile uint8_t  Resv_16768[8];
    volatile uint32_t EQEP0_CTRL;
    volatile uint32_t EQEP1_CTRL;
    volatile uint32_t EQEP2_CTRL;
    volatile uint8_t  Resv_16800[20];
    volatile uint32_t EQEP_STAT;
    volatile uint8_t  Resv_16900[96];
    volatile uint32_t TIMER1_CTRL;
    volatile uint8_t  Resv_16908[4];
    volatile uint32_t TIMER3_CTRL;
    volatile uint8_t  Resv_16916[4];
    volatile uint32_t TIMER5_CTRL;
    volatile uint8_t  Resv_16924[4];
    volatile uint32_t TIMER7_CTRL;
    volatile uint8_t  Resv_17408[480];
    volatile uint32_t SPARE_CTRL0;
    volatile uint32_t SPARE_CTRL1;
    volatile uint8_t  Resv_17472[56];
    volatile uint32_t SPARE_STAT0;
    volatile uint32_t SPARE_STAT1;
    volatile uint8_t  Resv_17536[56];
    volatile uint32_t SPARE_TRIM0;
    volatile uint8_t  Resv_17600[60];
    volatile uint32_t EMMC0_STAT;
    volatile uint32_t EMMC1_STAT;
    volatile uint32_t EMMC2_STAT;
    volatile uint8_t  Resv_18176[564];
    volatile uint32_t FSS_CTRL;
    volatile uint8_t  Resv_18256[76];
    volatile uint32_t DCC_STAT;
    volatile uint8_t  Resv_20488[2228];
    volatile uint32_t LOCK1_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK1_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_20736[240];
    volatile uint32_t CLAIMREG_P1_R0_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R1_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R2_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R3_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R4_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R5_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R6_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R7_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R8_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R9_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R10_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R11_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R12_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R13_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R14_READONLY;   /* Claim bits for Partition 1 */
    volatile uint8_t  Resv_24644[3848];
    volatile uint32_t ENET1_CTRL_PROXY;
    volatile uint32_t ENET2_CTRL_PROXY;
    volatile uint8_t  Resv_24832[180];
    volatile uint32_t ICSSM0_CTRL0_PROXY;
    volatile uint8_t  Resv_24880[44];
    volatile uint32_t EPWM_TB_CLKEN_PROXY;
    volatile uint8_t  Resv_24892[8];
    volatile uint32_t EPWM_ERR_STAT_PROXY;
    volatile uint32_t EPWM0_CTRL_PROXY;
    volatile uint32_t EPWM1_CTRL_PROXY;
    volatile uint32_t EPWM2_CTRL_PROXY;
    volatile uint8_t  Resv_24944[36];
    volatile uint32_t SOCA_SEL_PROXY;
    volatile uint32_t SOCB_SEL_PROXY;
    volatile uint8_t  Resv_24960[8];
    volatile uint32_t EQEP0_CTRL_PROXY;
    volatile uint32_t EQEP1_CTRL_PROXY;
    volatile uint32_t EQEP2_CTRL_PROXY;
    volatile uint8_t  Resv_24992[20];
    volatile uint32_t EQEP_STAT_PROXY;
    volatile uint8_t  Resv_25092[96];
    volatile uint32_t TIMER1_CTRL_PROXY;
    volatile uint8_t  Resv_25100[4];
    volatile uint32_t TIMER3_CTRL_PROXY;
    volatile uint8_t  Resv_25108[4];
    volatile uint32_t TIMER5_CTRL_PROXY;
    volatile uint8_t  Resv_25116[4];
    volatile uint32_t TIMER7_CTRL_PROXY;
    volatile uint8_t  Resv_25600[480];
    volatile uint32_t SPARE_CTRL0_PROXY;
    volatile uint32_t SPARE_CTRL1_PROXY;
    volatile uint8_t  Resv_25664[56];
    volatile uint32_t SPARE_STAT0_PROXY;
    volatile uint32_t SPARE_STAT1_PROXY;
    volatile uint8_t  Resv_25728[56];
    volatile uint32_t SPARE_TRIM0_PROXY;
    volatile uint8_t  Resv_25792[60];
    volatile uint32_t EMMC0_STAT_PROXY;
    volatile uint32_t EMMC1_STAT_PROXY;
    volatile uint32_t EMMC2_STAT_PROXY;
    volatile uint8_t  Resv_26368[564];
    volatile uint32_t FSS_CTRL_PROXY;
    volatile uint8_t  Resv_26448[76];
    volatile uint32_t DCC_STAT_PROXY;
    volatile uint8_t  Resv_28680[2228];
    volatile uint32_t LOCK1_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK1_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_28928[240];
    volatile uint32_t CLAIMREG_P1_R0;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R1;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R2;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R3;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R4;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R5;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R6;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R7;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R8;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R9;            /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R10;           /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R11;           /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R12;           /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R13;           /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R14;           /* Claim bits for Partition 1 */
    volatile uint8_t  Resv_32768[3780];
    volatile uint32_t OBSCLK0_CTRL;
    volatile uint8_t  Resv_32784[12];
    volatile uint32_t CLKOUT_CTRL;
    volatile uint8_t  Resv_32832[44];
    volatile uint32_t ICSSM0_CLKSEL;
    volatile uint8_t  Resv_32864[28];
    volatile uint32_t MAIN_PLL0_CLKSEL;
    volatile uint32_t MAIN_PLL1_CLKSEL;
    volatile uint32_t MAIN_PLL2_CLKSEL;
    volatile uint8_t  Resv_32896[20];
    volatile uint32_t MAIN_PLL8_CLKSEL;
    volatile uint8_t  Resv_32912[12];
    volatile uint32_t MAIN_PLL12_CLKSEL;
    volatile uint8_t  Resv_32928[12];
    volatile uint32_t MAIN_PLL16_CLKSEL;
    volatile uint32_t MAIN_PLL17_CLKSEL;
    volatile uint8_t  Resv_33088[152];
    volatile uint32_t CPSW_CLKSEL;
    volatile uint8_t  Resv_33120[28];
    volatile uint32_t EMMC0_CLKSEL;
    volatile uint8_t  Resv_33128[4];
    volatile uint32_t EMMC1_CLKSEL;
    volatile uint32_t EMMC2_CLKSEL;
    volatile uint8_t  Resv_33152[16];
    volatile uint32_t GPMC_CLKSEL;
    volatile uint8_t  Resv_33200[44];
    volatile uint32_t TIMER0_CLKSEL;
    volatile uint32_t TIMER1_CLKSEL;
    volatile uint32_t TIMER2_CLKSEL;
    volatile uint32_t TIMER3_CLKSEL;
    volatile uint32_t TIMER4_CLKSEL;
    volatile uint32_t TIMER5_CLKSEL;
    volatile uint32_t TIMER6_CLKSEL;
    volatile uint32_t TIMER7_CLKSEL;
    volatile uint8_t  Resv_33280[48];
    volatile uint32_t SPI0_CLKSEL;
    volatile uint32_t SPI1_CLKSEL;
    volatile uint32_t SPI2_CLKSEL;
    volatile uint8_t  Resv_33344[52];
    volatile uint32_t USART0_CLK_CTRL;
    volatile uint32_t USART1_CLK_CTRL;
    volatile uint32_t USART2_CLK_CTRL;
    volatile uint32_t USART3_CLK_CTRL;
    volatile uint32_t USART4_CLK_CTRL;
    volatile uint32_t USART5_CLK_CTRL;
    volatile uint32_t USART6_CLK_CTRL;
    volatile uint8_t  Resv_33408[36];
    volatile uint32_t USART0_CLKSEL;
    volatile uint32_t USART1_CLKSEL;
    volatile uint32_t USART2_CLKSEL;
    volatile uint32_t USART3_CLKSEL;
    volatile uint32_t USART4_CLKSEL;
    volatile uint32_t USART5_CLKSEL;
    volatile uint32_t USART6_CLKSEL;
    volatile uint8_t  Resv_33504[68];
    volatile uint32_t AUDIO_REFCLK0_CTRL;
    volatile uint32_t AUDIO_REFCLK1_CTRL;
    volatile uint8_t  Resv_33536[24];
    volatile uint32_t DPI0_CLK_CTRL;
    volatile uint8_t  Resv_33568[28];
    volatile uint32_t DSS_DISPC0_CLKSEL1;
    volatile uint8_t  Resv_33584[12];
    volatile uint32_t MCASP0_CLKSEL;
    volatile uint32_t MCASP1_CLKSEL;
    volatile uint32_t MCASP2_CLKSEL;
    volatile uint8_t  Resv_33616[20];
    volatile uint32_t MCASP0_AHCLKSEL;
    volatile uint32_t MCASP1_AHCLKSEL;
    volatile uint32_t MCASP2_AHCLKSEL;
    volatile uint8_t  Resv_33664[36];
    volatile uint32_t WWD0_CLKSEL;
    volatile uint32_t WWD1_CLKSEL;
    volatile uint32_t WWD2_CLKSEL;
    volatile uint32_t WWD3_CLKSEL;
    volatile uint8_t  Resv_33724[44];
    volatile uint32_t WWD15_CLKSEL;
    volatile uint8_t  Resv_33920[192];
    volatile uint32_t MCAN0_CLKSEL;
    volatile uint8_t  Resv_34048[124];
    volatile uint32_t OSPI0_CLKSEL;
    volatile uint8_t  Resv_34144[92];
    volatile uint32_t DDR0_RFCLK_TEST0_CLK_CTRL;
    volatile uint32_t DDR0_RFCLK_TEST1_CLK_CTRL;
    volatile uint8_t  Resv_34160[8];
    volatile uint32_t DDR0_TESTOUT0_CLK_CTRL;
    volatile uint32_t DDR0_TESTOUT1_CLK_CTRL;
    volatile uint8_t  Resv_34304[136];
    volatile uint32_t OLDI0_DAT0_IO_CTRL;
    volatile uint32_t OLDI0_DAT1_IO_CTRL;
    volatile uint32_t OLDI0_DAT2_IO_CTRL;
    volatile uint32_t OLDI0_DAT3_IO_CTRL;
    volatile uint32_t OLDI0_CLK_IO_CTRL;
    volatile uint8_t  Resv_34336[12];
    volatile uint32_t OLDI1_DAT0_IO_CTRL;
    volatile uint32_t OLDI1_DAT1_IO_CTRL;
    volatile uint32_t OLDI1_DAT2_IO_CTRL;
    volatile uint32_t OLDI1_DAT3_IO_CTRL;
    volatile uint32_t OLDI1_CLK_IO_CTRL;
    volatile uint8_t  Resv_34560[204];
    volatile uint32_t OLDI_PD_CTRL;
    volatile uint32_t OLDI_LB_CTRL;
    volatile uint8_t  Resv_36872[2304];
    volatile uint32_t LOCK2_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK2_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_37120[240];
    volatile uint32_t CLAIMREG_P2_R0_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R1_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R2_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R3_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R4_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R5_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R6_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R7_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R8_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R9_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R10_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R11_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R12_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R13_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R14_READONLY;   /* Claim bits for Partition 2 */
    volatile uint8_t  Resv_40960[3780];
    volatile uint32_t OBSCLK0_CTRL_PROXY;
    volatile uint8_t  Resv_40976[12];
    volatile uint32_t CLKOUT_CTRL_PROXY;
    volatile uint8_t  Resv_41024[44];
    volatile uint32_t ICSSM0_CLKSEL_PROXY;
    volatile uint8_t  Resv_41056[28];
    volatile uint32_t MAIN_PLL0_CLKSEL_PROXY;
    volatile uint32_t MAIN_PLL1_CLKSEL_PROXY;
    volatile uint32_t MAIN_PLL2_CLKSEL_PROXY;
    volatile uint8_t  Resv_41088[20];
    volatile uint32_t MAIN_PLL8_CLKSEL_PROXY;
    volatile uint8_t  Resv_41104[12];
    volatile uint32_t MAIN_PLL12_CLKSEL_PROXY;
    volatile uint8_t  Resv_41120[12];
    volatile uint32_t MAIN_PLL16_CLKSEL_PROXY;
    volatile uint32_t MAIN_PLL17_CLKSEL_PROXY;
    volatile uint8_t  Resv_41280[152];
    volatile uint32_t CPSW_CLKSEL_PROXY;
    volatile uint8_t  Resv_41312[28];
    volatile uint32_t EMMC0_CLKSEL_PROXY;
    volatile uint8_t  Resv_41320[4];
    volatile uint32_t EMMC1_CLKSEL_PROXY;
    volatile uint32_t EMMC2_CLKSEL_PROXY;
    volatile uint8_t  Resv_41344[16];
    volatile uint32_t GPMC_CLKSEL_PROXY;
    volatile uint8_t  Resv_41392[44];
    volatile uint32_t TIMER0_CLKSEL_PROXY;
    volatile uint32_t TIMER1_CLKSEL_PROXY;
    volatile uint32_t TIMER2_CLKSEL_PROXY;
    volatile uint32_t TIMER3_CLKSEL_PROXY;
    volatile uint32_t TIMER4_CLKSEL_PROXY;
    volatile uint32_t TIMER5_CLKSEL_PROXY;
    volatile uint32_t TIMER6_CLKSEL_PROXY;
    volatile uint32_t TIMER7_CLKSEL_PROXY;
    volatile uint8_t  Resv_41472[48];
    volatile uint32_t SPI0_CLKSEL_PROXY;
    volatile uint32_t SPI1_CLKSEL_PROXY;
    volatile uint32_t SPI2_CLKSEL_PROXY;
    volatile uint8_t  Resv_41536[52];
    volatile uint32_t USART0_CLK_CTRL_PROXY;
    volatile uint32_t USART1_CLK_CTRL_PROXY;
    volatile uint32_t USART2_CLK_CTRL_PROXY;
    volatile uint32_t USART3_CLK_CTRL_PROXY;
    volatile uint32_t USART4_CLK_CTRL_PROXY;
    volatile uint32_t USART5_CLK_CTRL_PROXY;
    volatile uint32_t USART6_CLK_CTRL_PROXY;
    volatile uint8_t  Resv_41600[36];
    volatile uint32_t USART0_CLKSEL_PROXY;
    volatile uint32_t USART1_CLKSEL_PROXY;
    volatile uint32_t USART2_CLKSEL_PROXY;
    volatile uint32_t USART3_CLKSEL_PROXY;
    volatile uint32_t USART4_CLKSEL_PROXY;
    volatile uint32_t USART5_CLKSEL_PROXY;
    volatile uint32_t USART6_CLKSEL_PROXY;
    volatile uint8_t  Resv_41696[68];
    volatile uint32_t AUDIO_REFCLK0_CTRL_PROXY;
    volatile uint32_t AUDIO_REFCLK1_CTRL_PROXY;
    volatile uint8_t  Resv_41728[24];
    volatile uint32_t DPI0_CLK_CTRL_PROXY;
    volatile uint8_t  Resv_41760[28];
    volatile uint32_t DSS_DISPC0_CLKSEL1_PROXY;
    volatile uint8_t  Resv_41776[12];
    volatile uint32_t MCASP0_CLKSEL_PROXY;
    volatile uint32_t MCASP1_CLKSEL_PROXY;
    volatile uint32_t MCASP2_CLKSEL_PROXY;
    volatile uint8_t  Resv_41808[20];
    volatile uint32_t MCASP0_AHCLKSEL_PROXY;
    volatile uint32_t MCASP1_AHCLKSEL_PROXY;
    volatile uint32_t MCASP2_AHCLKSEL_PROXY;
    volatile uint8_t  Resv_41856[36];
    volatile uint32_t WWD0_CLKSEL_PROXY;
    volatile uint32_t WWD1_CLKSEL_PROXY;
    volatile uint32_t WWD2_CLKSEL_PROXY;
    volatile uint32_t WWD3_CLKSEL_PROXY;
    volatile uint8_t  Resv_41916[44];
    volatile uint32_t WWD15_CLKSEL_PROXY;
    volatile uint8_t  Resv_42112[192];
    volatile uint32_t MCAN0_CLKSEL_PROXY;
    volatile uint8_t  Resv_42240[124];
    volatile uint32_t OSPI0_CLKSEL_PROXY;
    volatile uint8_t  Resv_42336[92];
    volatile uint32_t DDR0_RFCLK_TEST0_CLK_CTRL_PROXY;
    volatile uint32_t DDR0_RFCLK_TEST1_CLK_CTRL_PROXY;
    volatile uint8_t  Resv_42352[8];
    volatile uint32_t DDR0_TESTOUT0_CLK_CTRL_PROXY;
    volatile uint32_t DDR0_TESTOUT1_CLK_CTRL_PROXY;
    volatile uint8_t  Resv_42496[136];
    volatile uint32_t OLDI0_DAT0_IO_CTRL_PROXY;
    volatile uint32_t OLDI0_DAT1_IO_CTRL_PROXY;
    volatile uint32_t OLDI0_DAT2_IO_CTRL_PROXY;
    volatile uint32_t OLDI0_DAT3_IO_CTRL_PROXY;
    volatile uint32_t OLDI0_CLK_IO_CTRL_PROXY;
    volatile uint8_t  Resv_42528[12];
    volatile uint32_t OLDI1_DAT0_IO_CTRL_PROXY;
    volatile uint32_t OLDI1_DAT1_IO_CTRL_PROXY;
    volatile uint32_t OLDI1_DAT2_IO_CTRL_PROXY;
    volatile uint32_t OLDI1_DAT3_IO_CTRL_PROXY;
    volatile uint32_t OLDI1_CLK_IO_CTRL_PROXY;
    volatile uint8_t  Resv_42752[204];
    volatile uint32_t OLDI_PD_CTRL_PROXY;
    volatile uint32_t OLDI_LB_CTRL_PROXY;
    volatile uint8_t  Resv_45064[2304];
    volatile uint32_t LOCK2_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK2_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_45312[240];
    volatile uint32_t CLAIMREG_P2_R0;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R1;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R2;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R3;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R4;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R5;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R6;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R7;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R8;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R9;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R10;           /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R11;           /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R12;           /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R13;           /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R14;           /* Claim bits for Partition 2 */
    volatile uint8_t  Resv_66816[21444];
    volatile uint32_t MAIN_PLL_TEST_CLKSEL;
    volatile uint8_t  Resv_69640[2820];
    volatile uint32_t LOCK4_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK4_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_69888[240];
    volatile uint32_t CLAIMREG_P4_R0_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R1_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R2_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R3_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R4_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R5_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R6_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R7_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R8_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R9_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R10_READONLY;   /* Claim bits for Partition 4 */
    volatile uint8_t  Resv_75008[5076];
    volatile uint32_t MAIN_PLL_TEST_CLKSEL_PROXY;
    volatile uint8_t  Resv_77832[2820];
    volatile uint32_t LOCK4_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK4_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_78080[240];
    volatile uint32_t CLAIMREG_P4_R0;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R1;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R2;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R3;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R4;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R5;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R6;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R7;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R8;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R9;            /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R10;           /* Claim bits for Partition 4 */
    volatile uint8_t  Resv_99344[21220];
    volatile uint32_t SLEEP_STATUS;
    volatile uint8_t  Resv_102408[3060];
    volatile uint32_t LOCK6_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK6_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_102656[240];
    volatile uint32_t CLAIMREG_P6_R0_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R1_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R2_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R3_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R4_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R5_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R6_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R7_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R8_READONLY;   /* Claim bits for Partition 6 */
    volatile uint8_t  Resv_107536[4844];
    volatile uint32_t SLEEP_STATUS_PROXY;
    volatile uint8_t  Resv_110600[3060];
    volatile uint32_t LOCK6_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK6_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_110848[240];
    volatile uint32_t CLAIMREG_P6_R0;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R1;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R2;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R3;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R4;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R5;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R6;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R7;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R8;            /* Claim bits for Partition 6 */
} CSL_main_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG0_PID                                        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0                                   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1                                   (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0                                (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0                                (0x00001008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1                                (0x0000100CU)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS                            (0x00001010U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR                  (0x00001014U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE                                (0x00001018U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                          (0x0000101CU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI                                        (0x00001020U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS                              (0x00001024U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                          (0x00001028U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                          (0x0000102CU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR                                (0x00001030U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY                    (0x00001100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY                    (0x00001104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY                    (0x00001108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY                    (0x0000110CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY                    (0x00001110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY                    (0x00001114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY                    (0x00001118U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY                                  (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY                             (0x00002004U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY                             (0x00002008U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_PROXY                          (0x00002300U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY                          (0x00003008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY                          (0x0000300CU)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY                      (0x00003010U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY            (0x00003014U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY                          (0x00003018U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY                    (0x0000301CU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_PROXY                                  (0x00003020U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY                        (0x00003024U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY                    (0x00003028U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY                    (0x0000302CU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY                          (0x00003030U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0                             (0x00003100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1                             (0x00003104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2                             (0x00003108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3                             (0x0000310CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4                             (0x00003110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5                             (0x00003114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6                             (0x00003118U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL                                 (0x00004044U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL                                 (0x00004048U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0                               (0x00004100U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN                              (0x00004130U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT                              (0x0000413CU)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL                                 (0x00004140U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL                                 (0x00004144U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL                                 (0x00004148U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL                                   (0x00004170U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL                                   (0x00004174U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL                                 (0x00004180U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL                                 (0x00004184U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL                                 (0x00004188U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT                                  (0x000041A0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL                                (0x00004204U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL                                (0x0000420CU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL                                (0x00004214U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL                                (0x0000421CU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0                                (0x00004400U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1                                (0x00004404U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0                                (0x00004440U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1                                (0x00004444U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0                                (0x00004480U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT                                 (0x000044C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT                                 (0x000044C4U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT                                 (0x000044C8U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL                                   (0x00004700U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT                                   (0x00004750U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0                                (0x00005008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1                                (0x0000500CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY                    (0x00005100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY                    (0x00005104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY                    (0x00005108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY                    (0x0000510CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY                    (0x00005110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY                    (0x00005114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY                    (0x00005118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY                    (0x0000511CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY                    (0x00005120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY                    (0x00005124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY                   (0x00005128U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY                   (0x0000512CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY                   (0x00005130U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY                   (0x00005134U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY                   (0x00005138U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY                           (0x00006044U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY                           (0x00006048U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_PROXY                         (0x00006100U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY                        (0x00006130U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY                        (0x0000613CU)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY                           (0x00006140U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_PROXY                           (0x00006144U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_PROXY                           (0x00006148U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_PROXY                             (0x00006170U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_PROXY                             (0x00006174U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_PROXY                           (0x00006180U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_PROXY                           (0x00006184U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_PROXY                           (0x00006188U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY                            (0x000061A0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_PROXY                          (0x00006204U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_PROXY                          (0x0000620CU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_PROXY                          (0x00006214U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_PROXY                          (0x0000621CU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_PROXY                          (0x00006400U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_PROXY                          (0x00006404U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_PROXY                          (0x00006440U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_PROXY                          (0x00006444U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_PROXY                          (0x00006480U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_PROXY                           (0x000064C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_PROXY                           (0x000064C4U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_PROXY                           (0x000064C8U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY                             (0x00006700U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY                             (0x00006750U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY                          (0x00007008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY                          (0x0000700CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0                             (0x00007100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1                             (0x00007104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2                             (0x00007108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3                             (0x0000710CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4                             (0x00007110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5                             (0x00007114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6                             (0x00007118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7                             (0x0000711CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8                             (0x00007120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9                             (0x00007124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10                            (0x00007128U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11                            (0x0000712CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12                            (0x00007130U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13                            (0x00007134U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14                            (0x00007138U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL                               (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL                                (0x00008010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL                              (0x00008040U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL                           (0x00008060U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL                           (0x00008064U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL                           (0x00008068U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL                           (0x00008080U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL                          (0x00008090U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL                          (0x000080A0U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL                          (0x000080A4U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL                                (0x00008140U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL                               (0x00008160U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL                               (0x00008168U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL                               (0x0000816CU)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL                                (0x00008180U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL                              (0x000081B0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL                              (0x000081B4U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL                              (0x000081B8U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL                              (0x000081BCU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL                              (0x000081C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL                              (0x000081C4U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL                              (0x000081C8U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL                              (0x000081CCU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL                                (0x00008200U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL                                (0x00008204U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL                                (0x00008208U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL                            (0x00008240U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL                            (0x00008244U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL                            (0x00008248U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL                            (0x0000824CU)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL                            (0x00008250U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL                            (0x00008254U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL                            (0x00008258U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL                              (0x00008280U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL                              (0x00008284U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL                              (0x00008288U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL                              (0x0000828CU)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL                              (0x00008290U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL                              (0x00008294U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL                              (0x00008298U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL                         (0x000082E0U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL                         (0x000082E4U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL                              (0x00008300U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1                         (0x00008320U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL                              (0x00008330U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL                              (0x00008334U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL                              (0x00008338U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL                            (0x00008350U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL                            (0x00008354U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL                            (0x00008358U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL                                (0x00008380U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL                                (0x00008384U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL                                (0x00008388U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL                                (0x0000838CU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL                               (0x000083BCU)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL                               (0x00008480U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL                               (0x00008500U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL                  (0x00008560U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL                  (0x00008564U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL                     (0x00008570U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL                     (0x00008574U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL                         (0x00008600U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL                         (0x00008604U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL                         (0x00008608U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL                         (0x0000860CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL                          (0x00008610U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL                         (0x00008620U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL                         (0x00008624U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL                         (0x00008628U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL                         (0x0000862CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL                          (0x00008630U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL                               (0x00008700U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL                               (0x00008704U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0                                (0x00009008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1                                (0x0000900CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY                    (0x00009100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY                    (0x00009104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY                    (0x00009108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY                    (0x0000910CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY                    (0x00009110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY                    (0x00009114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY                    (0x00009118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY                    (0x0000911CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY                    (0x00009120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY                    (0x00009124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY                   (0x00009128U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY                   (0x0000912CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY                   (0x00009130U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_READONLY                   (0x00009134U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_READONLY                   (0x00009138U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY                         (0x0000A000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY                          (0x0000A010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY                        (0x0000A040U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY                     (0x0000A060U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY                     (0x0000A064U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY                     (0x0000A068U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY                     (0x0000A080U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY                    (0x0000A090U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY                    (0x0000A0A0U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY                    (0x0000A0A4U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_PROXY                          (0x0000A140U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY                         (0x0000A160U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY                         (0x0000A168U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY                         (0x0000A16CU)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_PROXY                          (0x0000A180U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_PROXY                        (0x0000A1B0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_PROXY                        (0x0000A1B4U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_PROXY                        (0x0000A1B8U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_PROXY                        (0x0000A1BCU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_PROXY                        (0x0000A1C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_PROXY                        (0x0000A1C4U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_PROXY                        (0x0000A1C8U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_PROXY                        (0x0000A1CCU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_PROXY                          (0x0000A200U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_PROXY                          (0x0000A204U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_PROXY                          (0x0000A208U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY                      (0x0000A240U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY                      (0x0000A244U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY                      (0x0000A248U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY                      (0x0000A24CU)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY                      (0x0000A250U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY                      (0x0000A254U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY                      (0x0000A258U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_PROXY                        (0x0000A280U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_PROXY                        (0x0000A284U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_PROXY                        (0x0000A288U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_PROXY                        (0x0000A28CU)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_PROXY                        (0x0000A290U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_PROXY                        (0x0000A294U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_PROXY                        (0x0000A298U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY                   (0x0000A2E0U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY                   (0x0000A2E4U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY                        (0x0000A300U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_PROXY                   (0x0000A320U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_PROXY                        (0x0000A330U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_PROXY                        (0x0000A334U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_PROXY                        (0x0000A338U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY                      (0x0000A350U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY                      (0x0000A354U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY                      (0x0000A358U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY                          (0x0000A380U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY                          (0x0000A384U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY                          (0x0000A388U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY                          (0x0000A38CU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY                         (0x0000A3BCU)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_PROXY                         (0x0000A480U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY                         (0x0000A500U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY            (0x0000A560U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY            (0x0000A564U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY               (0x0000A570U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY               (0x0000A574U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY                   (0x0000A600U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY                   (0x0000A604U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY                   (0x0000A608U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY                   (0x0000A60CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY                    (0x0000A610U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY                   (0x0000A620U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY                   (0x0000A624U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY                   (0x0000A628U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY                   (0x0000A62CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY                    (0x0000A630U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY                         (0x0000A700U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_PROXY                         (0x0000A704U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY                          (0x0000B008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY                          (0x0000B00CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0                             (0x0000B100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1                             (0x0000B104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2                             (0x0000B108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3                             (0x0000B10CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4                             (0x0000B110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5                             (0x0000B114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6                             (0x0000B118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7                             (0x0000B11CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8                             (0x0000B120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9                             (0x0000B124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10                            (0x0000B128U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11                            (0x0000B12CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12                            (0x0000B130U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13                            (0x0000B134U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14                            (0x0000B138U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL                       (0x00010500U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0                                (0x00011008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1                                (0x0001100CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY                    (0x00011100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY                    (0x00011104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY                    (0x00011108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY                    (0x0001110CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY                    (0x00011110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY                    (0x00011114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY                    (0x00011118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY                    (0x0001111CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY                    (0x00011120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY                    (0x00011124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY                   (0x00011128U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY                 (0x00012500U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY                          (0x00013008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY                          (0x0001300CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0                             (0x00013100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1                             (0x00013104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2                             (0x00013108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3                             (0x0001310CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4                             (0x00013110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5                             (0x00013114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6                             (0x00013118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7                             (0x0001311CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8                             (0x00013120U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9                             (0x00013124U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10                            (0x00013128U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS                               (0x00018410U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0                                (0x00019008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1                                (0x0001900CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY                    (0x00019100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY                    (0x00019104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY                    (0x00019108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY                    (0x0001910CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY                    (0x00019110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY                    (0x00019114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY                    (0x00019118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY                    (0x0001911CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY                    (0x00019120U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY                         (0x0001A410U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY                          (0x0001B008U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY                          (0x0001B00CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0                             (0x0001B100U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1                             (0x0001B104U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2                             (0x0001B108U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3                             (0x0001B10CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4                             (0x0001B110U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5                             (0x0001B114U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6                             (0x0001B118U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7                             (0x0001B11CU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8                             (0x0001B120U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                         (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                          (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                        (0x000000C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                       (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                         (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                         (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                        (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                          (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_MASK                          (0x0000F800U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                         (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_MAX                           (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                         (0xFFFF0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                        (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                          (0x0000FFFFU)

/* MMR_CFG0 */

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_MASK                     (0x0000FFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_SHIFT                    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_MAX                      (0x0000FFFFU)

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_MASK                      (0xFFFF0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_SHIFT                     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_MAX                       (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                   (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                    (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                     (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                    (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                      (0x00000001U)

/* SPARE_FUSE0 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_FUSE_VAL_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_FUSE_VAL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_FUSE_VAL_MAX                   (0xFFFFFFFFU)

/* LOCK0_KICK0 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK0_KICK1 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MAX                (0xFFFFFFFFU)

/* INTR_RAW_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK              (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK              (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT             (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK             (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT            (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX              (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MASK (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MAX (0x00000001U)

/* INTR_ENABLE */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK               (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK               (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK               (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT              (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT             (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX               (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK     (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK     (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT    (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK     (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT    (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK    (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT   (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX     (0x00000001U)

/* EOI */

#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                        (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                         (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK              (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX               (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK          (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT         (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX           (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK            (0x00000040U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT           (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX             (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK        (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX         (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK       (0x000FFF00U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT      (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX        (0x00000FFFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK           (0xFFF00000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT          (0x00000014U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX            (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX                  (0x00000001U)

/* CLAIMREG_P0_R0_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R1_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R2_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R3_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R4_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R5_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R6_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_MAX (0xFFFFFFFFU)

/* PID_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MASK             (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MAX              (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MASK            (0x000000C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_SHIFT           (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MAX             (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MASK             (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_SHIFT            (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MAX              (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MASK              (0x0000F800U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_SHIFT             (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MAX               (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MASK             (0xFFFF0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MAX              (0x0000FFFFU)

/* MMR_CFG0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_MASK (0x0000FFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_MAX (0x0000FFFFU)

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_MASK (0xFFFF0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_MAX  (0x0000FFFFU)

/* MMR_CFG1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MAX (0x00000001U)

/* SPARE_FUSE0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_PROXY_SPARE_FUSE0_FUSE_VAL_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_PROXY_SPARE_FUSE0_FUSE_VAL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_FUSE0_PROXY_SPARE_FUSE0_FUSE_VAL_PROXY_MAX (0xFFFFFFFFU)

/* LOCK0_KICK0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK0_KICK1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* INTR_RAW_STATUS_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MASK  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MASK  (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MASK  (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MAX  (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MAX (0x00000001U)

/* INTR_ENABLE_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MASK   (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MASK   (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_SHIFT  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MASK   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_SHIFT  (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MASK  (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MAX   (0x00000001U)

/* INTR_ENABLE_CLEAR_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MASK (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MAX (0x00000001U)

/* EOI_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MASK            (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MAX             (0x000000FFU)

/* FAULT_ADDRESS_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MASK  (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MAX   (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MASK (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MAX (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MASK (0x00000040U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_SHIFT (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MAX (0x00000001U)

/* FAULT_ATTR_STATUS_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MASK (0x000FFF00U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MAX (0x00000FFFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MASK (0xFFF00000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_SHIFT (0x00000014U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MAX (0x00000FFFU)

/* FAULT_CLEAR_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MASK     (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_SHIFT    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MAX      (0x00000001U)

/* CLAIMREG_P0_R0 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R1 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R2 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R3 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R4 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R5 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R6 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_MAX          (0xFFFFFFFFU)

/* ENET1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PORT_MODE_SEL_MASK              (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PORT_MODE_SEL_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PORT_MODE_SEL_MAX               (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_RGMII_ID_MODE_MASK              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_RGMII_ID_MODE_SHIFT             (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_RGMII_ID_MODE_MAX               (0x00000001U)

/* ENET2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PORT_MODE_SEL_MASK              (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PORT_MODE_SEL_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PORT_MODE_SEL_MAX               (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_RGMII_ID_MODE_MASK              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_RGMII_ID_MODE_SHIFT             (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_RGMII_ID_MODE_MAX               (0x00000001U)

/* ICSSM0_CTRL0 */

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_GPM_BIDI_MASK                 (0x000FFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_GPM_BIDI_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_GPM_BIDI_MAX                  (0x000FFFFFU)

/* EPWM_TB_CLKEN */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_MASK          (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_SHIFT         (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_MAX           (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_MASK          (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_MAX           (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_MASK          (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_SHIFT         (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_MAX           (0x00000001U)

/* EPWM_ERR_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM0_TZ_ERR_MASK            (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM0_TZ_ERR_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM0_TZ_ERR_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM1_TZ_ERR_MASK            (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM1_TZ_ERR_SHIFT           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM1_TZ_ERR_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM2_TZ_ERR_MASK            (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM2_TZ_ERR_SHIFT           (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_EPWM2_TZ_ERR_MAX             (0x00000001U)

/* EPWM0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_EALLOW_MASK                     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_EALLOW_SHIFT                    (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_EALLOW_MAX                      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_SYNCIN_SEL_MASK                 (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_SYNCIN_SEL_SHIFT                (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_SYNCIN_SEL_MAX                  (0x00000007U)

/* EPWM1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_EALLOW_MASK                     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_EALLOW_SHIFT                    (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_EALLOW_MAX                      (0x00000001U)

/* EPWM2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_EALLOW_MASK                     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_EALLOW_SHIFT                    (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_EALLOW_MAX                      (0x00000001U)

/* SOCA_SEL */

#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_SOCA_SEL_MASK                     (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_SOCA_SEL_SHIFT                    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_SOCA_SEL_MAX                      (0x00000003U)

/* SOCB_SEL */

#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_SOCB_SEL_MASK                     (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_SOCB_SEL_SHIFT                    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_SOCB_SEL_MAX                      (0x00000003U)

/* EQEP0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_SOCA_SEL_MASK                   (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_SOCA_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_SOCA_SEL_MAX                    (0x0000001FU)

/* EQEP1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_SOCA_SEL_MASK                   (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_SOCA_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_SOCA_SEL_MAX                    (0x0000001FU)

/* EQEP2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_SOCA_SEL_MASK                   (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_SOCA_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_SOCA_SEL_MAX                    (0x0000001FU)

/* EQEP_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR0_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR0_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR0_MAX                   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR1_MASK                  (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR1_SHIFT                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR1_MAX                   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR2_MASK                  (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR2_SHIFT                 (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PHASE_ERR2_MAX                   (0x00000001U)

/* TIMER1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_CASCADE_EN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_CASCADE_EN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_CASCADE_EN_MAX                 (0x00000001U)

/* TIMER3_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_CASCADE_EN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_CASCADE_EN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_CASCADE_EN_MAX                 (0x00000001U)

/* TIMER5_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_CASCADE_EN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_CASCADE_EN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_CASCADE_EN_MAX                 (0x00000001U)

/* TIMER7_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_CASCADE_EN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_CASCADE_EN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_CASCADE_EN_MAX                 (0x00000001U)

/* SPARE_CTRL0 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_SPARE_OUT_MASK                 (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_SPARE_OUT_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_SPARE_OUT_MAX                  (0xFFFFFFFFU)

/* SPARE_CTRL1 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_SPARE_OUT_MASK                 (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_SPARE_OUT_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_SPARE_OUT_MAX                  (0xFFFFFFFFU)

/* SPARE_STAT0 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_SPARE_IN_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_SPARE_IN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_SPARE_IN_MAX                   (0xFFFFFFFFU)

/* SPARE_STAT1 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_SPARE_IN_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_SPARE_IN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_SPARE_IN_MAX                   (0xFFFFFFFFU)

/* SPARE_TRIM0 */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_TRIM_MASK                      (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_TRIM_SHIFT                     (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_TRIM_MAX                       (0xFFFFFFFFU)

/* EMMC0_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_SIG1P8_EN_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_SIG1P8_EN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_SIG1P8_EN_MAX                   (0x00000001U)

/* EMMC1_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_SIG1P8_EN_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_SIG1P8_EN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_SIG1P8_EN_MAX                   (0x00000001U)

/* EMMC2_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_SIG1P8_EN_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_SIG1P8_EN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_SIG1P8_EN_MAX                   (0x00000001U)

/* FSS_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SEG_MASK                  (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SEG_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SEG_MAX                   (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SIZE_MASK                 (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SIZE_SHIFT                (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_S0_BOOT_SIZE_MAX                  (0x00000001U)

/* DCC_STAT */

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC0_INTR_DONE_MASK               (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC0_INTR_DONE_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC0_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC1_INTR_DONE_MASK               (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC1_INTR_DONE_SHIFT              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC1_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC2_INTR_DONE_MASK               (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC2_INTR_DONE_SHIFT              (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC2_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC3_INTR_DONE_MASK               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC3_INTR_DONE_SHIFT              (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC3_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC4_INTR_DONE_MASK               (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC4_INTR_DONE_SHIFT              (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC4_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC5_INTR_DONE_MASK               (0x00000020U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC5_INTR_DONE_SHIFT              (0x00000005U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC5_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC6_INTR_DONE_MASK               (0x00000040U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC6_INTR_DONE_SHIFT              (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_DCC6_INTR_DONE_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_MCU_DCC0_INTR_DONE_MASK           (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_MCU_DCC0_INTR_DONE_SHIFT          (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_MCU_DCC0_INTR_DONE_MAX            (0x00000001U)

/* LOCK1_KICK0 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK1_KICK1 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P1_R0_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R1_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R2_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R3_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R4_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R5_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R6_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R7_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R8_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R9_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R10_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R11_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R12_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R13_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R14_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_MAX (0xFFFFFFFFU)

/* ENET1_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_PORT_MODE_SEL_PROXY_MASK (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_PORT_MODE_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_PORT_MODE_SEL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_RGMII_ID_MODE_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_RGMII_ID_MODE_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET1_CTRL_PROXY_ENET1_CTRL_RGMII_ID_MODE_PROXY_MAX (0x00000001U)

/* ENET2_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_PORT_MODE_SEL_PROXY_MASK (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_PORT_MODE_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_PORT_MODE_SEL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_RGMII_ID_MODE_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_RGMII_ID_MODE_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_ENET2_CTRL_PROXY_ENET2_CTRL_RGMII_ID_MODE_PROXY_MAX (0x00000001U)

/* ICSSM0_CTRL0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_PROXY_ICSSM0_CTRL0_GPM_BIDI_PROXY_MASK (0x000FFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_PROXY_ICSSM0_CTRL0_GPM_BIDI_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CTRL0_PROXY_ICSSM0_CTRL0_GPM_BIDI_PROXY_MAX (0x000FFFFFU)

/* EPWM_TB_CLKEN_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_TB_CLKEN_PROXY_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_PROXY_MAX (0x00000001U)

/* EPWM_ERR_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM0_TZ_ERR_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM0_TZ_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM0_TZ_ERR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM1_TZ_ERR_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM1_TZ_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM1_TZ_ERR_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM2_TZ_ERR_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM2_TZ_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM_ERR_STAT_PROXY_EPWM_ERR_STAT_EPWM2_TZ_ERR_PROXY_MAX (0x00000001U)

/* EPWM0_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_EALLOW_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_EALLOW_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_EALLOW_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_SYNCIN_SEL_PROXY_MASK (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_SYNCIN_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_PROXY_EPWM0_CTRL_SYNCIN_SEL_PROXY_MAX (0x00000007U)

/* EPWM1_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_PROXY_EPWM1_CTRL_EALLOW_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_PROXY_EPWM1_CTRL_EALLOW_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM1_CTRL_PROXY_EPWM1_CTRL_EALLOW_PROXY_MAX (0x00000001U)

/* EPWM2_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_PROXY_EPWM2_CTRL_EALLOW_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_PROXY_EPWM2_CTRL_EALLOW_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EPWM2_CTRL_PROXY_EPWM2_CTRL_EALLOW_PROXY_MAX (0x00000001U)

/* SOCA_SEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_PROXY_SOCA_SEL_SOCA_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_PROXY_SOCA_SEL_SOCA_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCA_SEL_PROXY_SOCA_SEL_SOCA_SEL_PROXY_MAX (0x00000003U)

/* SOCB_SEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_PROXY_SOCB_SEL_SOCB_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_PROXY_SOCB_SEL_SOCB_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SOCB_SEL_PROXY_SOCB_SEL_SOCB_SEL_PROXY_MAX (0x00000003U)

/* EQEP0_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_PROXY_EQEP0_CTRL_SOCA_SEL_PROXY_MASK (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_PROXY_EQEP0_CTRL_SOCA_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP0_CTRL_PROXY_EQEP0_CTRL_SOCA_SEL_PROXY_MAX (0x0000001FU)

/* EQEP1_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_PROXY_EQEP1_CTRL_SOCA_SEL_PROXY_MASK (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_PROXY_EQEP1_CTRL_SOCA_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP1_CTRL_PROXY_EQEP1_CTRL_SOCA_SEL_PROXY_MAX (0x0000001FU)

/* EQEP2_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_PROXY_EQEP2_CTRL_SOCA_SEL_PROXY_MASK (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_PROXY_EQEP2_CTRL_SOCA_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP2_CTRL_PROXY_EQEP2_CTRL_SOCA_SEL_PROXY_MAX (0x0000001FU)

/* EQEP_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR0_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR0_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR0_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR1_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR1_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR1_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR2_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR2_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_EQEP_STAT_PROXY_EQEP_STAT_PHASE_ERR2_PROXY_MAX (0x00000001U)

/* TIMER1_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_PROXY_TIMER1_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_PROXY_TIMER1_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CTRL_PROXY_TIMER1_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* TIMER3_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_PROXY_TIMER3_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_PROXY_TIMER3_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CTRL_PROXY_TIMER3_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* TIMER5_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_PROXY_TIMER5_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_PROXY_TIMER5_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CTRL_PROXY_TIMER5_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* TIMER7_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_PROXY_TIMER7_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_PROXY_TIMER7_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CTRL_PROXY_TIMER7_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* SPARE_CTRL0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_PROXY_SPARE_CTRL0_SPARE_OUT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_PROXY_SPARE_CTRL0_SPARE_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL0_PROXY_SPARE_CTRL0_SPARE_OUT_PROXY_MAX (0xFFFFFFFFU)

/* SPARE_CTRL1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_PROXY_SPARE_CTRL1_SPARE_OUT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_PROXY_SPARE_CTRL1_SPARE_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_CTRL1_PROXY_SPARE_CTRL1_SPARE_OUT_PROXY_MAX (0xFFFFFFFFU)

/* SPARE_STAT0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_PROXY_SPARE_STAT0_SPARE_IN_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_PROXY_SPARE_STAT0_SPARE_IN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT0_PROXY_SPARE_STAT0_SPARE_IN_PROXY_MAX (0xFFFFFFFFU)

/* SPARE_STAT1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_PROXY_SPARE_STAT1_SPARE_IN_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_PROXY_SPARE_STAT1_SPARE_IN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_STAT1_PROXY_SPARE_STAT1_SPARE_IN_PROXY_MAX (0xFFFFFFFFU)

/* SPARE_TRIM0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_PROXY_SPARE_TRIM0_TRIM_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_PROXY_SPARE_TRIM0_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPARE_TRIM0_PROXY_SPARE_TRIM0_TRIM_PROXY_MAX (0xFFFFFFFFU)

/* EMMC0_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_PROXY_EMMC0_STAT_SIG1P8_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_PROXY_EMMC0_STAT_SIG1P8_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_STAT_PROXY_EMMC0_STAT_SIG1P8_EN_PROXY_MAX (0x00000001U)

/* EMMC1_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_PROXY_EMMC1_STAT_SIG1P8_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_PROXY_EMMC1_STAT_SIG1P8_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_STAT_PROXY_EMMC1_STAT_SIG1P8_EN_PROXY_MAX (0x00000001U)

/* EMMC2_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_PROXY_EMMC2_STAT_SIG1P8_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_PROXY_EMMC2_STAT_SIG1P8_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_STAT_PROXY_EMMC2_STAT_SIG1P8_EN_PROXY_MAX (0x00000001U)

/* FSS_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SEG_PROXY_MASK (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SEG_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SEG_PROXY_MAX (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SIZE_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SIZE_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_FSS_CTRL_PROXY_FSS_CTRL_S0_BOOT_SIZE_PROXY_MAX (0x00000001U)

/* DCC_STAT_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC0_INTR_DONE_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC0_INTR_DONE_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC0_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC1_INTR_DONE_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC1_INTR_DONE_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC1_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC2_INTR_DONE_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC2_INTR_DONE_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC2_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC3_INTR_DONE_PROXY_MASK (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC3_INTR_DONE_PROXY_SHIFT (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC3_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC4_INTR_DONE_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC4_INTR_DONE_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC4_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC5_INTR_DONE_PROXY_MASK (0x00000020U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC5_INTR_DONE_PROXY_SHIFT (0x00000005U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC5_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC6_INTR_DONE_PROXY_MASK (0x00000040U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC6_INTR_DONE_PROXY_SHIFT (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_DCC6_INTR_DONE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_MCU_DCC0_INTR_DONE_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_MCU_DCC0_INTR_DONE_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_DCC_STAT_PROXY_DCC_STAT_MCU_DCC0_INTR_DONE_PROXY_MAX (0x00000001U)

/* LOCK1_KICK0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK1_KICK1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P1_R0 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R1 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R2 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R3 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R4 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R5 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R6 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R7 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R8 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R9 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R10 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R11 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R12 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R13 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R14 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_MAX        (0xFFFFFFFFU)

/* OBSCLK0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_SEL_MASK                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_SEL_MAX                   (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_MASK                  (0x0000FF00U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_SHIFT                 (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_MAX                   (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_LD_MASK               (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_LD_SHIFT              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_CLK_DIV_LD_MAX                (0x00000001U)

/* CLKOUT_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_SEL_MASK                   (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_SEL_MAX                    (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_EN_MASK                    (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_EN_SHIFT                   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_CLK_EN_MAX                     (0x00000001U)

/* ICSSM0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_CORE_CLKSEL_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_CORE_CLKSEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_CORE_CLKSEL_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_IEP_CLKSEL_MASK              (0x00070000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_IEP_CLKSEL_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_IEP_CLKSEL_MAX               (0x00000007U)

/* MAIN_PLL0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYP_WARM_RST_MASK         (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYP_WARM_RST_SHIFT        (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYP_WARM_RST_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_MASK       (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_SHIFT      (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_MAX        (0x00000001U)

/* MAIN_PLL1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYP_WARM_RST_MASK         (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYP_WARM_RST_SHIFT        (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYP_WARM_RST_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_MASK       (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_SHIFT      (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_MAX        (0x00000001U)

/* MAIN_PLL2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYP_WARM_RST_MASK         (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYP_WARM_RST_SHIFT        (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYP_WARM_RST_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_MASK       (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_SHIFT      (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_MAX        (0x00000001U)

/* MAIN_PLL8_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYP_WARM_RST_MASK         (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYP_WARM_RST_SHIFT        (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYP_WARM_RST_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_MASK       (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_SHIFT      (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_MAX        (0x00000001U)

/* MAIN_PLL12_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYP_WARM_RST_MASK        (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYP_WARM_RST_SHIFT       (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYP_WARM_RST_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_MASK      (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_SHIFT     (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_MAX       (0x00000001U)

/* MAIN_PLL16_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYP_WARM_RST_MASK        (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYP_WARM_RST_SHIFT       (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYP_WARM_RST_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_MASK      (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_SHIFT     (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_MAX       (0x00000001U)

/* MAIN_PLL17_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYP_WARM_RST_MASK        (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYP_WARM_RST_SHIFT       (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYP_WARM_RST_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_MASK      (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_SHIFT     (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_MAX       (0x00000001U)

/* CPSW_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_CPTS_CLKSEL_MASK               (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_CPTS_CLKSEL_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_CPTS_CLKSEL_MAX                (0x00000007U)

/* EMMC0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_MASK        (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_MASK      (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_SHIFT     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_MAX       (0x00000001U)

/* EMMC1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_MASK        (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_MASK      (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_SHIFT     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_MAX       (0x00000001U)

/* EMMC2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_MASK        (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_MASK      (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_SHIFT     (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_MAX       (0x00000001U)

/* GPMC_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_CLK_SEL_MASK                   (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_CLK_SEL_MAX                    (0x00000001U)

/* TIMER0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER3_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER4_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER5_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER6_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* TIMER7_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_CLK_SEL_MAX                  (0x0000000FU)

/* SPI0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_MSTR_LB_CLKSEL_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_MSTR_LB_CLKSEL_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_MSTR_LB_CLKSEL_MAX             (0x00000001U)

/* SPI1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_MSTR_LB_CLKSEL_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_MSTR_LB_CLKSEL_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_MSTR_LB_CLKSEL_MAX             (0x00000001U)

/* SPI2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_MSTR_LB_CLKSEL_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_MSTR_LB_CLKSEL_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_MSTR_LB_CLKSEL_MAX             (0x00000001U)

/* USART0_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART1_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART2_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART3_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART4_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART5_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART6_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_MASK               (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_MAX                (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

/* USART0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART3_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART4_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART5_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* USART6_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* AUDIO_REFCLK0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLK_SEL_MASK            (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLK_SEL_MAX             (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLKOUT_EN_MASK          (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLKOUT_EN_SHIFT         (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_CLKOUT_EN_MAX           (0x00000001U)

/* AUDIO_REFCLK1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLK_SEL_MASK            (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLK_SEL_MAX             (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLKOUT_EN_MASK          (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLKOUT_EN_SHIFT         (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_CLKOUT_EN_MAX           (0x00000001U)

/* DPI0_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_DATA_CLK_INVDIS_MASK         (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_DATA_CLK_INVDIS_SHIFT        (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_DATA_CLK_INVDIS_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_MASK         (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_SHIFT        (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_MAX          (0x00000001U)

/* DSS_DISPC0_CLKSEL1 */

#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_DPI1_PCLK_MASK          (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_DPI1_PCLK_SHIFT         (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_DPI1_PCLK_MAX           (0x00000001U)

/* MCASP0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_AUXCLK_SEL_MASK              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_AUXCLK_SEL_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_AUXCLK_SEL_MAX               (0x00000001U)

/* MCASP1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_AUXCLK_SEL_MASK              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_AUXCLK_SEL_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_AUXCLK_SEL_MAX               (0x00000001U)

/* MCASP2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_AUXCLK_SEL_MASK              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_AUXCLK_SEL_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_AUXCLK_SEL_MAX               (0x00000001U)

/* MCASP0_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKR_SEL_MASK            (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKR_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKR_SEL_MAX             (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKX_SEL_MASK            (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKX_SEL_SHIFT           (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKX_SEL_MAX             (0x00000003U)

/* MCASP1_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKR_SEL_MASK            (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKR_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKR_SEL_MAX             (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKX_SEL_MASK            (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKX_SEL_SHIFT           (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKX_SEL_MAX             (0x00000003U)

/* MCASP2_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKR_SEL_MASK            (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKR_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKR_SEL_MAX             (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKX_SEL_MASK            (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKX_SEL_SHIFT           (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKX_SEL_MAX             (0x00000003U)

/* WWD0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_CLK_SEL_MASK                   (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_CLK_SEL_MAX                    (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_WRTLOCK_MASK                   (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_WRTLOCK_SHIFT                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_WRTLOCK_MAX                    (0x00000001U)

/* WWD1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_CLK_SEL_MASK                   (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_CLK_SEL_MAX                    (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_WRTLOCK_MASK                   (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_WRTLOCK_SHIFT                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_WRTLOCK_MAX                    (0x00000001U)

/* WWD2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_CLK_SEL_MASK                   (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_CLK_SEL_MAX                    (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_WRTLOCK_MASK                   (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_WRTLOCK_SHIFT                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_WRTLOCK_MAX                    (0x00000001U)

/* WWD3_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_CLK_SEL_MASK                   (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_CLK_SEL_MAX                    (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_WRTLOCK_MASK                   (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_WRTLOCK_SHIFT                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_WRTLOCK_MAX                    (0x00000001U)

/* WWD15_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_CLK_SEL_MASK                  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_CLK_SEL_MAX                   (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_WRTLOCK_MASK                  (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_WRTLOCK_SHIFT                 (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_WRTLOCK_MAX                   (0x00000001U)

/* MCAN0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_CLK_SEL_MASK                  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_CLK_SEL_MAX                   (0x00000003U)

/* OSPI0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_CLK_SEL_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_CLK_SEL_MAX                   (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_LOOPCLK_SEL_MASK              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_LOOPCLK_SEL_SHIFT             (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_LOOPCLK_SEL_MAX               (0x00000001U)

/* DDR0_RFCLK_TEST0_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_MASK   (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_MAX    (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_EN_MASK          (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_EN_SHIFT         (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_EN_MAX           (0x00000001U)

/* DDR0_RFCLK_TEST1_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_MASK   (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_MAX    (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_EN_MASK          (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_EN_SHIFT         (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_EN_MAX           (0x00000001U)

/* DDR0_TESTOUT0_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_MASK      (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_SHIFT     (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_MAX       (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_EN_MASK             (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_EN_SHIFT            (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_EN_MAX              (0x00000001U)

/* DDR0_TESTOUT1_CLK_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_MASK      (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_SHIFT     (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_MAX       (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_EN_MASK             (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_EN_SHIFT            (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_EN_MAX              (0x00000001U)

/* OLDI0_DAT0_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI0_DAT1_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI0_DAT2_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI0_DAT3_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI0_CLK_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_EN_MASK            (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_EN_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_VAL_MASK           (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_VAL_SHIFT          (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RTERM_VAL_MAX            (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXEN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXEN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXEN_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXCM_EN_MASK             (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXCM_EN_SHIFT            (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_RXCM_EN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_MASK        (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_SHIFT       (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TX_TRISTATE_MASK         (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TX_TRISTATE_SHIFT        (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TX_TRISTATE_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXEN_MASK                (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXEN_SHIFT               (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXEN_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXCM_MASK                (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXCM_SHIFT               (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXCM_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXDRV_MASK               (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXDRV_SHIFT              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXDRV_MAX                (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXTRIM_MASK              (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXTRIM_SHIFT             (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_TXTRIM_MAX               (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PULLDN_MASK              (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PULLDN_SHIFT             (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PULLDN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_BIASEN_MASK              (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_BIASEN_SHIFT             (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_BIASEN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_VBIAS_SEL_MASK           (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_VBIAS_SEL_SHIFT          (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_VBIAS_SEL_MAX            (0x00000001U)

/* OLDI1_DAT0_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI1_DAT1_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI1_DAT2_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI1_DAT3_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_EN_MASK           (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_EN_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_EN_MAX            (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_VAL_MASK          (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_VAL_SHIFT         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RTERM_VAL_MAX           (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXEN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXEN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXCM_EN_MASK            (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXCM_EN_SHIFT           (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_RXCM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_MASK       (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_SHIFT      (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_MAX        (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_MASK        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_SHIFT       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXEN_MASK               (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXEN_SHIFT              (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXEN_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXCM_MASK               (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXCM_SHIFT              (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXCM_MAX                (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXDRV_MASK              (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXDRV_SHIFT             (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXDRV_MAX               (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXTRIM_MASK             (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXTRIM_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_TXTRIM_MAX              (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PULLDN_MASK             (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PULLDN_SHIFT            (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PULLDN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_BIASEN_MASK             (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_BIASEN_SHIFT            (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_BIASEN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_MASK          (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_SHIFT         (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_MAX           (0x00000001U)

/* OLDI1_CLK_IO_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_EN_MASK            (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_EN_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_EN_MAX             (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_VAL_MASK           (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_VAL_SHIFT          (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RTERM_VAL_MAX            (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXEN_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXEN_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXEN_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXCM_EN_MASK             (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXCM_EN_SHIFT            (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_RXCM_EN_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_MASK        (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_SHIFT       (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_MAX         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TX_TRISTATE_MASK         (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TX_TRISTATE_SHIFT        (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TX_TRISTATE_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXEN_MASK                (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXEN_SHIFT               (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXEN_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXCM_MASK                (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXCM_SHIFT               (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXCM_MAX                 (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXDRV_MASK               (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXDRV_SHIFT              (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXDRV_MAX                (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXTRIM_MASK              (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXTRIM_SHIFT             (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_TXTRIM_MAX               (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PULLDN_MASK              (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PULLDN_SHIFT             (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PULLDN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_BIASEN_MASK              (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_BIASEN_SHIFT             (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_BIASEN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_VBIAS_SEL_MASK           (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_VBIAS_SEL_SHIFT          (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_VBIAS_SEL_MAX            (0x00000001U)

/* OLDI_PD_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0_MAX                  (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1_MASK                 (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1_SHIFT                (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1_MAX                  (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG_MASK                    (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG_SHIFT                   (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG_MAX                     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_BGOK_MASK                     (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_BGOK_SHIFT                    (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_BGOK_MAX                      (0x00000001U)

/* OLDI_LB_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_OLDI_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_OLDI_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_OLDI_SEL_MAX                  (0x00000001U)

/* LOCK2_KICK0 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK2_KICK1 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P2_R0_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R1_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R2_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R3_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R4_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R5_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R6_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R7_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R8_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R9_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R10_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R11_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R12_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R13_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_READONLY_CLAIMREG_P2_R13_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_READONLY_CLAIMREG_P2_R13_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_READONLY_CLAIMREG_P2_R13_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R14_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_READONLY_CLAIMREG_P2_R14_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_READONLY_CLAIMREG_P2_R14_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_READONLY_CLAIMREG_P2_R14_READONLY_MAX (0xFFFFFFFFU)

/* OBSCLK0_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_SEL_PROXY_MASK (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_SEL_PROXY_MAX (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_PROXY_MASK (0x0000FF00U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OBSCLK0_CTRL_PROXY_OBSCLK0_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* CLKOUT_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_SEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_EN_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_EN_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_CLK_EN_PROXY_MAX (0x00000001U)

/* ICSSM0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_CORE_CLKSEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_CORE_CLKSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_CORE_CLKSEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_IEP_CLKSEL_PROXY_MASK (0x00070000U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_IEP_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_ICSSM0_CLKSEL_PROXY_ICSSM0_CLKSEL_IEP_CLKSEL_PROXY_MAX (0x00000007U)

/* MAIN_PLL0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL0_CLKSEL_PROXY_MAIN_PLL0_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL1_CLKSEL_PROXY_MAIN_PLL1_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL2_CLKSEL_PROXY_MAIN_PLL2_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL8_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL8_CLKSEL_PROXY_MAIN_PLL8_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL12_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL12_CLKSEL_PROXY_MAIN_PLL12_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL16_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL16_CLKSEL_PROXY_MAIN_PLL16_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* MAIN_PLL17_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL17_CLKSEL_PROXY_MAIN_PLL17_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* CPSW_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_PROXY_CPSW_CLKSEL_CPTS_CLKSEL_PROXY_MASK (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_PROXY_CPSW_CLKSEL_CPTS_CLKSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CPSW_CLKSEL_PROXY_CPSW_CLKSEL_CPTS_CLKSEL_PROXY_MAX (0x00000007U)

/* EMMC0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC0_CLKSEL_PROXY_EMMC0_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MAX (0x00000001U)

/* EMMC1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC1_CLKSEL_PROXY_EMMC1_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MAX (0x00000001U)

/* EMMC2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_EMMC2_CLKSEL_PROXY_EMMC2_CLKSEL_EMMCSD_IO_CLKLB_SEL_PROXY_MAX (0x00000001U)

/* GPMC_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_PROXY_GPMC_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_PROXY_GPMC_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_GPMC_CLKSEL_PROXY_GPMC_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* TIMER0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_PROXY_TIMER0_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_PROXY_TIMER0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER0_CLKSEL_PROXY_TIMER0_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_PROXY_TIMER1_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_PROXY_TIMER1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER1_CLKSEL_PROXY_TIMER1_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_PROXY_TIMER2_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_PROXY_TIMER2_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER2_CLKSEL_PROXY_TIMER2_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER3_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_PROXY_TIMER3_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_PROXY_TIMER3_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER3_CLKSEL_PROXY_TIMER3_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER4_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_PROXY_TIMER4_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_PROXY_TIMER4_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER4_CLKSEL_PROXY_TIMER4_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER5_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_PROXY_TIMER5_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_PROXY_TIMER5_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER5_CLKSEL_PROXY_TIMER5_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER6_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_PROXY_TIMER6_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_PROXY_TIMER6_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER6_CLKSEL_PROXY_TIMER6_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* TIMER7_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_PROXY_TIMER7_CLKSEL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_PROXY_TIMER7_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_TIMER7_CLKSEL_PROXY_TIMER7_CLKSEL_CLK_SEL_PROXY_MAX (0x0000000FU)

/* SPI0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_PROXY_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_PROXY_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI0_CLKSEL_PROXY_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_MAX (0x00000001U)

/* SPI1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_PROXY_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_PROXY_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI1_CLKSEL_PROXY_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_MAX (0x00000001U)

/* SPI2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_PROXY_SPI2_CLKSEL_MSTR_LB_CLKSEL_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_PROXY_SPI2_CLKSEL_MSTR_LB_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SPI2_CLKSEL_PROXY_SPI2_CLKSEL_MSTR_LB_CLKSEL_PROXY_MAX (0x00000001U)

/* USART0_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLK_CTRL_PROXY_USART0_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART1_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLK_CTRL_PROXY_USART1_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART2_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLK_CTRL_PROXY_USART2_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART3_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLK_CTRL_PROXY_USART3_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART4_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLK_CTRL_PROXY_USART4_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART5_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLK_CTRL_PROXY_USART5_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART6_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLK_CTRL_PROXY_USART6_CLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

/* USART0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_PROXY_USART0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_PROXY_USART0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART0_CLKSEL_PROXY_USART0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_PROXY_USART1_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_PROXY_USART1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART1_CLKSEL_PROXY_USART1_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_PROXY_USART2_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_PROXY_USART2_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART2_CLKSEL_PROXY_USART2_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART3_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_PROXY_USART3_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_PROXY_USART3_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART3_CLKSEL_PROXY_USART3_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART4_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_PROXY_USART4_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_PROXY_USART4_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART4_CLKSEL_PROXY_USART4_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART5_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_PROXY_USART5_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_PROXY_USART5_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART5_CLKSEL_PROXY_USART5_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* USART6_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_PROXY_USART6_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_PROXY_USART6_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_USART6_CLKSEL_PROXY_USART6_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* AUDIO_REFCLK0_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLK_SEL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLKOUT_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLKOUT_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK0_CTRL_PROXY_AUDIO_REFCLK0_CTRL_CLKOUT_EN_PROXY_MAX (0x00000001U)

/* AUDIO_REFCLK1_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLK_SEL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLKOUT_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLKOUT_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_AUDIO_REFCLK1_CTRL_PROXY_AUDIO_REFCLK1_CTRL_CLKOUT_EN_PROXY_MAX (0x00000001U)

/* DPI0_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_DATA_CLK_INVDIS_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_DATA_CLK_INVDIS_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_DATA_CLK_INVDIS_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_DPI0_CLK_CTRL_PROXY_DPI0_CLK_CTRL_SYNC_CLK_INVDIS_PROXY_MAX (0x00000001U)

/* DSS_DISPC0_CLKSEL1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_PROXY_DSS_DISPC0_CLKSEL1_DPI1_PCLK_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_PROXY_DSS_DISPC0_CLKSEL1_DPI1_PCLK_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DSS_DISPC0_CLKSEL1_PROXY_DSS_DISPC0_CLKSEL1_DPI1_PCLK_PROXY_MAX (0x00000001U)

/* MCASP0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_PROXY_MCASP0_CLKSEL_AUXCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_PROXY_MCASP0_CLKSEL_AUXCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_CLKSEL_PROXY_MCASP0_CLKSEL_AUXCLK_SEL_PROXY_MAX (0x00000001U)

/* MCASP1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_PROXY_MCASP1_CLKSEL_AUXCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_PROXY_MCASP1_CLKSEL_AUXCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_CLKSEL_PROXY_MCASP1_CLKSEL_AUXCLK_SEL_PROXY_MAX (0x00000001U)

/* MCASP2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_PROXY_MCASP2_CLKSEL_AUXCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_PROXY_MCASP2_CLKSEL_AUXCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_CLKSEL_PROXY_MCASP2_CLKSEL_AUXCLK_SEL_PROXY_MAX (0x00000001U)

/* MCASP0_AHCLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKR_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKR_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKR_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKX_SEL_PROXY_MASK (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKX_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_PROXY_MCASP0_AHCLKSEL_AHCLKX_SEL_PROXY_MAX (0x00000003U)

/* MCASP1_AHCLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKR_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKR_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKR_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKX_SEL_PROXY_MASK (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKX_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_PROXY_MCASP1_AHCLKSEL_AHCLKX_SEL_PROXY_MAX (0x00000003U)

/* MCASP2_AHCLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKR_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKR_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKR_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKX_SEL_PROXY_MASK (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKX_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_PROXY_MCASP2_AHCLKSEL_AHCLKX_SEL_PROXY_MAX (0x00000003U)

/* WWD0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD0_CLKSEL_PROXY_WWD0_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* WWD1_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD1_CLKSEL_PROXY_WWD1_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* WWD2_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD2_CLKSEL_PROXY_WWD2_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* WWD3_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD3_CLKSEL_PROXY_WWD3_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* WWD15_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_WWD15_CLKSEL_PROXY_WWD15_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* MCAN0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_PROXY_MCAN0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_PROXY_MCAN0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MCAN0_CLKSEL_PROXY_MCAN0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

/* OSPI0_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_LOOPCLK_SEL_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_LOOPCLK_SEL_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_OSPI0_CLKSEL_PROXY_OSPI0_CLKSEL_LOOPCLK_SEL_PROXY_MAX (0x00000001U)

/* DDR0_RFCLK_TEST0_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_DIV_RATIO_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST0_CLK_CTRL_PROXY_DDR0_RFCLK_TEST0_CLK_CTRL_EN_PROXY_MAX (0x00000001U)

/* DDR0_RFCLK_TEST1_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_DIV_RATIO_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_RFCLK_TEST1_CLK_CTRL_PROXY_DDR0_RFCLK_TEST1_CLK_CTRL_EN_PROXY_MAX (0x00000001U)

/* DDR0_TESTOUT0_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_DIV_RATIO_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT0_CLK_CTRL_PROXY_DDR0_TESTOUT0_CLK_CTRL_EN_PROXY_MAX (0x00000001U)

/* DDR0_TESTOUT1_CLK_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_PROXY_MASK (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_DIV_RATIO_PROXY_MAX (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_EN_PROXY_MASK (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG0_DDR0_TESTOUT1_CLK_CTRL_PROXY_DDR0_TESTOUT1_CLK_CTRL_EN_PROXY_MAX (0x00000001U)

/* OLDI0_DAT0_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT0_IO_CTRL_PROXY_OLDI0_DAT0_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI0_DAT1_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT1_IO_CTRL_PROXY_OLDI0_DAT1_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI0_DAT2_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT2_IO_CTRL_PROXY_OLDI0_DAT2_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI0_DAT3_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_DAT3_IO_CTRL_PROXY_OLDI0_DAT3_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI0_CLK_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI0_CLK_IO_CTRL_PROXY_OLDI0_CLK_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI1_DAT0_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT0_IO_CTRL_PROXY_OLDI1_DAT0_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI1_DAT1_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT1_IO_CTRL_PROXY_OLDI1_DAT1_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI1_DAT2_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT2_IO_CTRL_PROXY_OLDI1_DAT2_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI1_DAT3_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_DAT3_IO_CTRL_PROXY_OLDI1_DAT3_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI1_CLK_IO_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_EN_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_VAL_PROXY_MASK (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_VAL_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RTERM_VAL_PROXY_MAX (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXEN_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXEN_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXCM_EN_PROXY_MASK (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXCM_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_RXCM_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_MASK (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_LVDS_HYST_EN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TX_TRISTATE_PROXY_MASK (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TX_TRISTATE_PROXY_SHIFT (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TX_TRISTATE_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXEN_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXEN_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXCM_PROXY_MASK (0x00002000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXCM_PROXY_SHIFT (0x0000000DU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXCM_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXDRV_PROXY_MASK (0x000F0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXDRV_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXDRV_PROXY_MAX (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXTRIM_PROXY_MASK (0x03000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXTRIM_PROXY_SHIFT (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_TXTRIM_PROXY_MAX (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_PULLDN_PROXY_MASK (0x10000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_PULLDN_PROXY_SHIFT (0x0000001CU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_PULLDN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_BIASEN_PROXY_MASK (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_BIASEN_PROXY_SHIFT (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_BIASEN_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_VBIAS_SEL_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_VBIAS_SEL_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI1_CLK_IO_CTRL_PROXY_OLDI1_CLK_IO_CTRL_VBIAS_SEL_PROXY_MAX (0x00000001U)

/* OLDI_PD_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI0_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI0_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI0_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI1_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI1_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_OLDI1_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_BG_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_BG_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_PD_BG_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_BGOK_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_BGOK_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PROXY_OLDI_PD_CTRL_BGOK_PROXY_MAX (0x00000001U)

/* OLDI_LB_CTRL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_PROXY_OLDI_LB_CTRL_OLDI_SEL_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_PROXY_OLDI_LB_CTRL_OLDI_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_OLDI_LB_CTRL_PROXY_OLDI_LB_CTRL_OLDI_SEL_PROXY_MAX (0x00000001U)

/* LOCK2_KICK0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK2_KICK1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P2_R0 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R1 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R2 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R3 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R4 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R5 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R6 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R7 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R8 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R9 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R10 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R11 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R12 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R13 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_CLAIMREG_P2_R13_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_CLAIMREG_P2_R13_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R13_CLAIMREG_P2_R13_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R14 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_CLAIMREG_P2_R14_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_CLAIMREG_P2_R14_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P2_R14_CLAIMREG_P2_R14_MAX        (0xFFFFFFFFU)

/* MAIN_PLL_TEST_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_MASK     (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_SHIFT    (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_MASK     (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_SHIFT    (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_MASK     (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_SHIFT    (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_MASK     (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_SHIFT    (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_MAX      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_MASK    (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_SHIFT   (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_MAX     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_MASK    (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_SHIFT   (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_MAX     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_MASK    (0x00020000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_SHIFT   (0x00000011U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_MAX     (0x00000001U)

/* LOCK4_KICK0 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK4_KICK1 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P4_R0_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R1_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R2_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R3_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R4_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R5_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R6_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R7_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R8_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R9_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R10_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_MAX (0xFFFFFFFFU)

/* MAIN_PLL_TEST_CLKSEL_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_MASK (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_PROXY_MASK (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_PROXY_SHIFT (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL1_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_PROXY_MASK (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_PROXY_SHIFT (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL2_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_PROXY_MASK (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_PROXY_SHIFT (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL8_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_PROXY_MASK (0x00001000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_PROXY_SHIFT (0x0000000CU)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL12_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_PROXY_MASK (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_PROXY_SHIFT (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL16_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_PROXY_MASK (0x00020000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_PROXY_SHIFT (0x00000011U)
#define CSL_MAIN_CTRL_MMR_CFG0_MAIN_PLL_TEST_CLKSEL_PROXY_MAIN_PLL_TEST_CLKSEL_CLK_SEL_PLL17_PROXY_MAX (0x00000001U)

/* LOCK4_KICK0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK4_KICK1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P4_R0 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R1 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R2 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R3 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R4 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R5 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R6 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R7 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R8 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R9 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R10 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_MASK       (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_MAX        (0xFFFFFFFFU)

/* SLEEP_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_WKUP_RDY_MASK                 (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_WKUP_RDY_SHIFT                (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_WKUP_RDY_MAX                  (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_MASK             (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_SHIFT            (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_MAX              (0x00000001U)

/* LOCK6_KICK0 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK6_KICK1 */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P6_R0_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R1_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R2_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R3_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R4_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R5_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R6_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R7_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R8_READONLY */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_MAX (0xFFFFFFFFU)

/* SLEEP_STATUS_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_WKUP_RDY_PROXY_MASK (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_WKUP_RDY_PROXY_SHIFT (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_WKUP_RDY_PROXY_MAX (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_MASK (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_SHIFT (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_MAX (0x00000001U)

/* LOCK6_KICK0_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK6_KICK1_PROXY */

#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P6_R0 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R1 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R2 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R3 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R4 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R5 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R6 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R7 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R8 */

#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_MASK         (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_MAX          (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif