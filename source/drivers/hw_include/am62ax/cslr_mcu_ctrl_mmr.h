/********************************************************************
 * Copyright (C) 2023 Texas Instruments Incorporated.
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
 *  Name        : cslr_mcu_ctrl_mmr.h
*/
#ifndef CSLR_MCU_CTRL_MMR_H_
#define CSLR_MCU_CTRL_MMR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_MCU_CTRL_MMR_CFG0_REGS_BASE                                  (0x00000000U)


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
    volatile uint8_t  Resv_256[244];
    volatile uint32_t IPC_SET0;
    volatile uint8_t  Resv_384[124];
    volatile uint32_t IPC_CLR0;
    volatile uint8_t  Resv_624[236];
    volatile uint32_t CBA_ERR_STAT;
    volatile uint8_t  Resv_640[12];
    volatile uint32_t ACCESS_ERR_STAT;
    volatile uint8_t  Resv_4104[3460];
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
    volatile uint8_t  Resv_8192[3816];
    volatile uint32_t PID_PROXY;                 /* PID register */
    volatile uint32_t MMR_CFG0_PROXY;
    volatile uint32_t MMR_CFG1_PROXY;
    volatile uint8_t  Resv_8448[244];
    volatile uint32_t IPC_SET0_PROXY;
    volatile uint8_t  Resv_8576[124];
    volatile uint32_t IPC_CLR0_PROXY;
    volatile uint8_t  Resv_8816[236];
    volatile uint32_t CBA_ERR_STAT_PROXY;
    volatile uint8_t  Resv_8832[12];
    volatile uint32_t ACCESS_ERR_STAT_PROXY;
    volatile uint8_t  Resv_12296[3460];
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
    volatile uint8_t  Resv_16416[3848];
    volatile uint32_t MCU_GPIO_CTRL;
    volatile uint8_t  Resv_16516[96];
    volatile uint32_t DBOUNCE_CFG1;
    volatile uint32_t DBOUNCE_CFG2;
    volatile uint32_t DBOUNCE_CFG3;
    volatile uint32_t DBOUNCE_CFG4;
    volatile uint32_t DBOUNCE_CFG5;
    volatile uint32_t DBOUNCE_CFG6;
    volatile uint8_t  Resv_16544[4];
    volatile uint32_t TEMP_DIODE_TRIM;
    volatile uint8_t  Resv_16560[12];
    volatile uint32_t IO_VOLTAGE_STAT;
    volatile uint8_t  Resv_16576[12];
    volatile uint32_t H_IO_DRVSTRNGTH0;
    volatile uint32_t H_IO_DRVSTRNGTH1;
    volatile uint32_t H_IO_DRVSTRNGTH2;
    volatile uint32_t H_IO_DRVSTRNGTH3;
    volatile uint32_t V_IO_DRVSTRNGTH0;
    volatile uint32_t V_IO_DRVSTRNGTH1;
    volatile uint32_t V_IO_DRVSTRNGTH2;
    volatile uint32_t V_IO_DRVSTRNGTH3;
    volatile uint8_t  Resv_16900[292];
    volatile uint32_t MCU_TIMER1_CTRL;
    volatile uint8_t  Resv_16908[4];
    volatile uint32_t MCU_TIMER3_CTRL;
    volatile uint8_t  Resv_17120[208];
    volatile uint32_t MCU_I2C0_CTRL;
    volatile uint8_t  Resv_17924[800];
    volatile uint32_t WKUP_MTOG_CTRL0;
    volatile uint32_t WKUP_MTOG_CTRL1;
    volatile uint8_t  Resv_17936[4];
    volatile uint32_t TOG_STAT;
    volatile uint8_t  Resv_20488[2548];
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
    volatile uint8_t  Resv_24608[3820];
    volatile uint32_t MCU_GPIO_CTRL_PROXY;
    volatile uint8_t  Resv_24708[96];
    volatile uint32_t DBOUNCE_CFG1_PROXY;
    volatile uint32_t DBOUNCE_CFG2_PROXY;
    volatile uint32_t DBOUNCE_CFG3_PROXY;
    volatile uint32_t DBOUNCE_CFG4_PROXY;
    volatile uint32_t DBOUNCE_CFG5_PROXY;
    volatile uint32_t DBOUNCE_CFG6_PROXY;
    volatile uint8_t  Resv_24736[4];
    volatile uint32_t TEMP_DIODE_TRIM_PROXY;
    volatile uint8_t  Resv_24752[12];
    volatile uint32_t IO_VOLTAGE_STAT_PROXY;
    volatile uint8_t  Resv_24768[12];
    volatile uint32_t H_IO_DRVSTRNGTH0_PROXY;
    volatile uint32_t H_IO_DRVSTRNGTH1_PROXY;
    volatile uint32_t H_IO_DRVSTRNGTH2_PROXY;
    volatile uint32_t H_IO_DRVSTRNGTH3_PROXY;
    volatile uint32_t V_IO_DRVSTRNGTH0_PROXY;
    volatile uint32_t V_IO_DRVSTRNGTH1_PROXY;
    volatile uint32_t V_IO_DRVSTRNGTH2_PROXY;
    volatile uint32_t V_IO_DRVSTRNGTH3_PROXY;
    volatile uint8_t  Resv_25092[292];
    volatile uint32_t MCU_TIMER1_CTRL_PROXY;
    volatile uint8_t  Resv_25100[4];
    volatile uint32_t MCU_TIMER3_CTRL_PROXY;
    volatile uint8_t  Resv_25312[208];
    volatile uint32_t MCU_I2C0_CTRL_PROXY;
    volatile uint8_t  Resv_26116[800];
    volatile uint32_t WKUP_MTOG_CTRL0_PROXY;
    volatile uint32_t WKUP_MTOG_CTRL1_PROXY;
    volatile uint8_t  Resv_26128[4];
    volatile uint32_t TOG_STAT_PROXY;
    volatile uint8_t  Resv_28680[2548];
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
    volatile uint8_t  Resv_32768[3788];
    volatile uint32_t MCU_OBSCLK_CTRL;
    volatile uint8_t  Resv_32784[12];
    volatile uint32_t HFOSC0_CTRL;
    volatile uint8_t  Resv_32792[4];
    volatile uint32_t HFOSC0_TRIM;
    volatile uint8_t  Resv_32800[4];
    volatile uint32_t HFOSC0_STAT;
    volatile uint32_t RC12M_OSC_TRIM;
    volatile uint8_t  Resv_32816[8];
    volatile uint32_t HFOSC0_CLKOUT_32K_CTRL;
    volatile uint8_t  Resv_32824[4];
    volatile uint32_t LFXOSC_CTRL;
    volatile uint32_t LFXOSC_TRIM;
    volatile uint8_t  Resv_32848[16];
    volatile uint32_t MCU_PLL_CLKSEL;
    volatile uint8_t  Resv_32856[4];
    volatile uint32_t DEVICE_CLKOUT_32K_CTRL;
    volatile uint8_t  Resv_32864[4];
    volatile uint32_t MCU_TIMER0_CLKSEL;
    volatile uint32_t MCU_TIMER1_CLKSEL;
    volatile uint32_t MCU_TIMER2_CLKSEL;
    volatile uint32_t MCU_TIMER3_CLKSEL;
    volatile uint32_t MCU_GPIO_CLKSEL;
    volatile uint8_t  Resv_32896[12];
    volatile uint32_t MCU_MCAN0_CLKSEL;
    volatile uint32_t MCU_MCAN1_CLKSEL;
    volatile uint8_t  Resv_32928[24];
    volatile uint32_t MCU_SPI0_CLKSEL;
    volatile uint32_t MCU_SPI1_CLKSEL;
    volatile uint8_t  Resv_32944[8];
    volatile uint32_t MCU_WWD0_CLKSEL;
    volatile uint8_t  Resv_36872[3924];
    volatile uint32_t LOCK2_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK2_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_37120[240];
    volatile uint32_t CLAIMREG_P2_R0_READONLY;   /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R1_READONLY;   /* Claim bits for Partition 2 */
    volatile uint8_t  Resv_40960[3832];
    volatile uint32_t MCU_OBSCLK_CTRL_PROXY;
    volatile uint8_t  Resv_40976[12];
    volatile uint32_t HFOSC0_CTRL_PROXY;
    volatile uint8_t  Resv_40984[4];
    volatile uint32_t HFOSC0_TRIM_PROXY;
    volatile uint8_t  Resv_40992[4];
    volatile uint32_t HFOSC0_STAT_PROXY;
    volatile uint32_t RC12M_OSC_TRIM_PROXY;
    volatile uint8_t  Resv_41008[8];
    volatile uint32_t HFOSC0_CLKOUT_32K_CTRL_PROXY;
    volatile uint8_t  Resv_41016[4];
    volatile uint32_t LFXOSC_CTRL_PROXY;
    volatile uint32_t LFXOSC_TRIM_PROXY;
    volatile uint8_t  Resv_41040[16];
    volatile uint32_t MCU_PLL_CLKSEL_PROXY;
    volatile uint8_t  Resv_41048[4];
    volatile uint32_t DEVICE_CLKOUT_32K_CTRL_PROXY;
    volatile uint8_t  Resv_41056[4];
    volatile uint32_t MCU_TIMER0_CLKSEL_PROXY;
    volatile uint32_t MCU_TIMER1_CLKSEL_PROXY;
    volatile uint32_t MCU_TIMER2_CLKSEL_PROXY;
    volatile uint32_t MCU_TIMER3_CLKSEL_PROXY;
    volatile uint32_t MCU_GPIO_CLKSEL_PROXY;
    volatile uint8_t  Resv_41088[12];
    volatile uint32_t MCU_MCAN0_CLKSEL_PROXY;
    volatile uint32_t MCU_MCAN1_CLKSEL_PROXY;
    volatile uint8_t  Resv_41120[24];
    volatile uint32_t MCU_SPI0_CLKSEL_PROXY;
    volatile uint32_t MCU_SPI1_CLKSEL_PROXY;
    volatile uint8_t  Resv_41136[8];
    volatile uint32_t MCU_WWD0_CLKSEL_PROXY;
    volatile uint8_t  Resv_45064[3924];
    volatile uint32_t LOCK2_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK2_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_45312[240];
    volatile uint32_t CLAIMREG_P2_R0;            /* Claim bits for Partition 2 */
    volatile uint32_t CLAIMREG_P2_R1;            /* Claim bits for Partition 2 */
    volatile uint8_t  Resv_49184[3864];
    volatile uint32_t MCU_R5FSS0_LBIST_CTRL;
    volatile uint32_t MCU_R5FSS0_LBIST_PATCOUNT;
    volatile uint32_t MCU_R5FSS0_LBIST_SEED0;
    volatile uint32_t MCU_R5FSS0_LBIST_SEED1;
    volatile uint32_t MCU_R5FSS0_LBIST_SPARE0;
    volatile uint32_t MCU_R5FSS0_LBIST_SPARE1;
    volatile uint32_t MCU_R5FSS0_LBIST_STAT;
    volatile uint32_t MCU_R5FSS0_LBIST_MISR;
    volatile uint8_t  Resv_53256[4040];
    volatile uint32_t LOCK3_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK3_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_53504[240];
    volatile uint32_t CLAIMREG_P3_R0_READONLY;   /* Claim bits for Partition 3 */
    volatile uint8_t  Resv_57376[3868];
    volatile uint32_t MCU_R5FSS0_LBIST_CTRL_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_PATCOUNT_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_SEED0_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_SEED1_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_SPARE0_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_SPARE1_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_STAT_PROXY;
    volatile uint32_t MCU_R5FSS0_LBIST_MISR_PROXY;
    volatile uint8_t  Resv_61448[4040];
    volatile uint32_t LOCK3_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK3_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_61696[240];
    volatile uint32_t CLAIMREG_P3_R0;            /* Claim bits for Partition 3 */
    volatile uint8_t  Resv_65536[3836];
    volatile uint32_t DV_REG0;
    volatile uint32_t DV_REG1;
    volatile uint32_t DV_REG2;
    volatile uint32_t DV_REG3;
    volatile uint32_t DV_REG4;
    volatile uint32_t DV_REG5;
    volatile uint32_t DV_REG6;
    volatile uint32_t DV_REG7;
    volatile uint8_t  Resv_66048[480];
    volatile uint32_t DV_REG0_SET;
    volatile uint32_t DV_REG1_SET;
    volatile uint32_t DV_REG2_SET;
    volatile uint32_t DV_REG3_SET;
    volatile uint8_t  Resv_66304[240];
    volatile uint32_t DV_REG0_CLR;
    volatile uint32_t DV_REG1_CLR;
    volatile uint32_t DV_REG2_CLR;
    volatile uint32_t DV_REG3_CLR;
    volatile uint8_t  Resv_66560[240];
    volatile uint32_t LED_CTRL;
    volatile uint8_t  Resv_66568[4];
    volatile uint32_t LED_ENABLE;
    volatile uint8_t  Resv_66592[20];
    volatile uint32_t LED_MCU_PLL_STAT_EN;
    volatile uint32_t LED_MAIN_PLL_STAT_EN;
    volatile uint32_t LED_PGD_STAT_EN;
    volatile uint32_t LED_EFC_STAT_EN;
    volatile uint32_t LED_STATUS_CTRL;
    volatile uint8_t  Resv_66688[76];
    volatile uint32_t SIM_CFG0;
    volatile uint32_t SIM_CFG1;
    volatile uint32_t SIM_CFG2;
    volatile uint32_t SIM_CFG3;
    volatile uint32_t SIM_CFG4;
    volatile uint32_t SIM_CFG5;
    volatile uint32_t SIM_CFG6;
    volatile uint32_t SIM_CFG7;
    volatile uint8_t  Resv_66800[80];
    volatile uint32_t MCU_PLL_TEST_CLKSEL;
    volatile uint8_t  Resv_66816[12];
    volatile uint32_t NON_AVS_MRGN_MODE0;
    volatile uint32_t NON_AVS_MRGN_MODE1;
    volatile uint32_t NON_AVS_MRGN_MODE2;
    volatile uint32_t NON_AVS_MRGN_MODE3;
    volatile uint32_t NON_AVS_MRGN_MODE4;
    volatile uint32_t NON_AVS_MRGN_MODE5;
    volatile uint32_t NON_AVS_MRGN_MODE6;
    volatile uint32_t NON_AVS_MRGN_MODE7;
    volatile uint32_t NON_AVS_MRGN_MODE8;
    volatile uint32_t NON_AVS_MRGN_MODE9;
    volatile uint8_t  Resv_67328[472];
    volatile uint32_t ATEST_RCOSC;
    volatile uint8_t  Resv_67360[28];
    volatile uint32_t ATEST_HFOSC;
    volatile uint8_t  Resv_67376[12];
    volatile uint32_t ATEST_LFOSC;
    volatile uint8_t  Resv_67392[12];
    volatile uint32_t ATEST_POR;
    volatile uint32_t ATEST_POK_VDDA_MCU_UV_CTRL;
    volatile uint32_t ATEST_POK_VDDA_MCU_OV_CTRL;
    volatile uint32_t ATEST_POK_VDD_CORE_UV_CTRL;
    volatile uint32_t ATEST_POK_VDDA_PMIC_IN;
    volatile uint8_t  Resv_67424[12];
    volatile uint32_t ATEST_POK_VDD_CORE_OV_CTRL;
    volatile uint32_t ATEST_POK_VDDR_CORE;
    volatile uint8_t  Resv_67440[8];
    volatile uint32_t ATEST_POK_VMON_CAP_MCU_GENERAL;
    volatile uint32_t ATEST_POK_VDDSHV_MAIN_1P8;
    volatile uint32_t ATEST_POK_VDDSHV_MAIN_3P3;
    volatile uint32_t ATEST_POK_VDDS_DDRIO;
    volatile uint8_t  Resv_67568[112];
    volatile uint32_t PVT0_TEST_REG_OBS;
    volatile uint32_t PVT1_TEST_REG_OBS;
    volatile uint32_t PVT2_TEST_REG_OBS;
    volatile uint8_t  Resv_67584[4];
    volatile uint32_t VTM_TEST_REG_CTRL;
    volatile uint8_t  Resv_67600[12];
    volatile uint32_t GP_TEST_REG;
    volatile uint8_t  Resv_67616[12];
    volatile uint32_t SDIO_TEST_REG_CTRL;
    volatile uint32_t SDIO_TEST_REG_OBS;
    volatile uint8_t  Resv_67632[8];
    volatile uint32_t SA3_UL_TRNG_TEST_REG;
    volatile uint32_t SA3_UL_TRNG_TEST_OBS;
    volatile uint8_t  Resv_67712[72];
    volatile uint32_t SPARE_RW_TEST_REG;
    volatile uint32_t SPARE_RO_TEST_REG;
    volatile uint8_t  Resv_67728[8];
    volatile uint32_t PBIST_EN_TEST_REG;
    volatile uint32_t PBIST_MARGIN_MODE_CTRL;
    volatile uint8_t  Resv_67840[104];
    volatile uint32_t PLL0_CAL_STAT_TEST_REG;
    volatile uint32_t PLL1_CAL_STAT_TEST_REG;
    volatile uint32_t PLL2_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67860[8];
    volatile uint32_t PLL5_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67868[4];
    volatile uint32_t PLL7_CAL_STAT_TEST_REG;
    volatile uint32_t PLL8_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67888[12];
    volatile uint32_t PLL12_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67900[8];
    volatile uint32_t PLL15_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67908[4];
    volatile uint32_t PLL17_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_67968[56];
    volatile uint32_t MCU_PLL0_CAL_STAT_TEST_REG;
    volatile uint8_t  Resv_69640[1668];
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
    volatile uint32_t CLAIMREG_P4_R11_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R12_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R13_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R14_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R15_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R16_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R17_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R18_READONLY;   /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R19_READONLY;   /* Claim bits for Partition 4 */
    volatile uint8_t  Resv_73728[3760];
    volatile uint32_t DV_REG0_PROXY;
    volatile uint32_t DV_REG1_PROXY;
    volatile uint32_t DV_REG2_PROXY;
    volatile uint32_t DV_REG3_PROXY;
    volatile uint32_t DV_REG4_PROXY;
    volatile uint32_t DV_REG5_PROXY;
    volatile uint32_t DV_REG6_PROXY;
    volatile uint32_t DV_REG7_PROXY;
    volatile uint8_t  Resv_74240[480];
    volatile uint32_t DV_REG0_SET_PROXY;
    volatile uint32_t DV_REG1_SET_PROXY;
    volatile uint32_t DV_REG2_SET_PROXY;
    volatile uint32_t DV_REG3_SET_PROXY;
    volatile uint8_t  Resv_74496[240];
    volatile uint32_t DV_REG0_CLR_PROXY;
    volatile uint32_t DV_REG1_CLR_PROXY;
    volatile uint32_t DV_REG2_CLR_PROXY;
    volatile uint32_t DV_REG3_CLR_PROXY;
    volatile uint8_t  Resv_74752[240];
    volatile uint32_t LED_CTRL_PROXY;
    volatile uint8_t  Resv_74760[4];
    volatile uint32_t LED_ENABLE_PROXY;
    volatile uint8_t  Resv_74784[20];
    volatile uint32_t LED_MCU_PLL_STAT_EN_PROXY;
    volatile uint32_t LED_MAIN_PLL_STAT_EN_PROXY;
    volatile uint32_t LED_PGD_STAT_EN_PROXY;
    volatile uint32_t LED_EFC_STAT_EN_PROXY;
    volatile uint32_t LED_STATUS_CTRL_PROXY;
    volatile uint8_t  Resv_74880[76];
    volatile uint32_t SIM_CFG0_PROXY;
    volatile uint32_t SIM_CFG1_PROXY;
    volatile uint32_t SIM_CFG2_PROXY;
    volatile uint32_t SIM_CFG3_PROXY;
    volatile uint32_t SIM_CFG4_PROXY;
    volatile uint32_t SIM_CFG5_PROXY;
    volatile uint32_t SIM_CFG6_PROXY;
    volatile uint32_t SIM_CFG7_PROXY;
    volatile uint8_t  Resv_74992[80];
    volatile uint32_t MCU_PLL_TEST_CLKSEL_PROXY;
    volatile uint8_t  Resv_75008[12];
    volatile uint32_t NON_AVS_MRGN_MODE0_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE1_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE2_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE3_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE4_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE5_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE6_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE7_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE8_PROXY;
    volatile uint32_t NON_AVS_MRGN_MODE9_PROXY;
    volatile uint8_t  Resv_75520[472];
    volatile uint32_t ATEST_RCOSC_PROXY;
    volatile uint8_t  Resv_75552[28];
    volatile uint32_t ATEST_HFOSC_PROXY;
    volatile uint8_t  Resv_75568[12];
    volatile uint32_t ATEST_LFOSC_PROXY;
    volatile uint8_t  Resv_75584[12];
    volatile uint32_t ATEST_POR_PROXY;
    volatile uint32_t ATEST_POK_VDDA_MCU_UV_CTRL_PROXY;
    volatile uint32_t ATEST_POK_VDDA_MCU_OV_CTRL_PROXY;
    volatile uint32_t ATEST_POK_VDD_CORE_UV_CTRL_PROXY;
    volatile uint32_t ATEST_POK_VDDA_PMIC_IN_PROXY;
    volatile uint8_t  Resv_75616[12];
    volatile uint32_t ATEST_POK_VDD_CORE_OV_CTRL_PROXY;
    volatile uint32_t ATEST_POK_VDDR_CORE_PROXY;
    volatile uint8_t  Resv_75632[8];
    volatile uint32_t ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY;
    volatile uint32_t ATEST_POK_VDDSHV_MAIN_1P8_PROXY;
    volatile uint32_t ATEST_POK_VDDSHV_MAIN_3P3_PROXY;
    volatile uint32_t ATEST_POK_VDDS_DDRIO_PROXY;
    volatile uint8_t  Resv_75760[112];
    volatile uint32_t PVT0_TEST_REG_OBS_PROXY;
    volatile uint32_t PVT1_TEST_REG_OBS_PROXY;
    volatile uint32_t PVT2_TEST_REG_OBS_PROXY;
    volatile uint8_t  Resv_75776[4];
    volatile uint32_t VTM_TEST_REG_CTRL_PROXY;
    volatile uint8_t  Resv_75792[12];
    volatile uint32_t GP_TEST_REG_PROXY;
    volatile uint8_t  Resv_75808[12];
    volatile uint32_t SDIO_TEST_REG_CTRL_PROXY;
    volatile uint32_t SDIO_TEST_REG_OBS_PROXY;
    volatile uint8_t  Resv_75824[8];
    volatile uint32_t SA3_UL_TRNG_TEST_REG_PROXY;
    volatile uint32_t SA3_UL_TRNG_TEST_OBS_PROXY;
    volatile uint8_t  Resv_75904[72];
    volatile uint32_t SPARE_RW_TEST_REG_PROXY;
    volatile uint32_t SPARE_RO_TEST_REG_PROXY;
    volatile uint8_t  Resv_75920[8];
    volatile uint32_t PBIST_EN_TEST_REG_PROXY;
    volatile uint32_t PBIST_MARGIN_MODE_CTRL_PROXY;
    volatile uint8_t  Resv_76032[104];
    volatile uint32_t PLL0_CAL_STAT_TEST_REG_PROXY;
    volatile uint32_t PLL1_CAL_STAT_TEST_REG_PROXY;
    volatile uint32_t PLL2_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76052[8];
    volatile uint32_t PLL5_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76060[4];
    volatile uint32_t PLL7_CAL_STAT_TEST_REG_PROXY;
    volatile uint32_t PLL8_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76080[12];
    volatile uint32_t PLL12_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76092[8];
    volatile uint32_t PLL15_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76100[4];
    volatile uint32_t PLL17_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_76160[56];
    volatile uint32_t MCU_PLL0_CAL_STAT_TEST_REG_PROXY;
    volatile uint8_t  Resv_77832[1668];
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
    volatile uint32_t CLAIMREG_P4_R11;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R12;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R13;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R14;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R15;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R16;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R17;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R18;           /* Claim bits for Partition 4 */
    volatile uint32_t CLAIMREG_P4_R19;           /* Claim bits for Partition 4 */
    volatile uint8_t  Resv_98304[20144];
    volatile uint32_t POR_CTRL;
    volatile uint32_t POR_STAT;
    volatile uint8_t  Resv_98560[248];
    volatile uint32_t POR_BANDGAP_CTRL;
    volatile uint8_t  Resv_98576[12];
    volatile uint32_t POK_VDDA_MCU_UV_CTRL;
    volatile uint32_t POK_VDDA_MCU_OV_CTRL;
    volatile uint32_t POK_VDD_CORE_UV_CTRL;
    volatile uint32_t POK_VDD_CORE_OV_CTRL;
    volatile uint32_t POK_VDDR_CORE_UV_CTRL;
    volatile uint32_t POK_VDDR_CORE_OV_CTRL;
    volatile uint8_t  Resv_98616[16];
    volatile uint32_t POK_VMON_CAP_MCU_GENERAL_UV_CTRL;
    volatile uint32_t POK_VMON_CAP_MCU_GENERAL_OV_CTRL;
    volatile uint32_t POK_VDDSHV_MAIN_1P8_UV_CTRL;
    volatile uint32_t POK_VDDSHV_MAIN_1P8_OV_CTRL;
    volatile uint32_t POK_VDDSHV_MAIN_3P3_UV_CTRL;
    volatile uint32_t POK_VDDSHV_MAIN_3P3_OV_CTRL;
    volatile uint32_t POK_VDDS_DDRIO_UV_CTRL;
    volatile uint32_t POK_VDDS_DDRIO_OV_CTRL;
    volatile uint8_t  Resv_98656[8];
    volatile uint32_t POK_VDDA_PMIC_IN_CTRL;
    volatile uint8_t  Resv_98672[12];
    volatile uint32_t RST_CTRL;
    volatile uint32_t RST_STAT;
    volatile uint32_t RST_SRC;
    volatile uint32_t RST_MAGIC_WORD;
    volatile uint32_t ISO_CTRL;
    volatile uint8_t  Resv_98704[12];
    volatile uint32_t VDD_CORE_GLDTC_CTRL;
    volatile uint8_t  Resv_98736[28];
    volatile uint32_t VDD_CORE_GLDTC_STAT;
    volatile uint8_t  Resv_98816[76];
    volatile uint32_t PRG_PP_0_CTRL;
    volatile uint32_t PRG_PP_0_STAT;
    volatile uint32_t PRG_PP_1_CTRL;
    volatile uint32_t PRG_PP_1_STAT;
    volatile uint8_t  Resv_98944[112];
    volatile uint32_t CLKGATE_CTRL;
    volatile uint8_t  Resv_102408[3460];
    volatile uint32_t LOCK6_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK6_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_102656[240];
    volatile uint32_t CLAIMREG_P6_R0_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R1_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R2_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R3_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R4_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R5_READONLY;   /* Claim bits for Partition 6 */
    volatile uint8_t  Resv_106496[3816];
    volatile uint32_t POR_CTRL_PROXY;
    volatile uint32_t POR_STAT_PROXY;
    volatile uint8_t  Resv_106752[248];
    volatile uint32_t POR_BANDGAP_CTRL_PROXY;
    volatile uint8_t  Resv_106768[12];
    volatile uint32_t POK_VDDA_MCU_UV_CTRL_PROXY;
    volatile uint32_t POK_VDDA_MCU_OV_CTRL_PROXY;
    volatile uint32_t POK_VDD_CORE_UV_CTRL_PROXY;
    volatile uint32_t POK_VDD_CORE_OV_CTRL_PROXY;
    volatile uint32_t POK_VDDR_CORE_UV_CTRL_PROXY;
    volatile uint32_t POK_VDDR_CORE_OV_CTRL_PROXY;
    volatile uint8_t  Resv_106808[16];
    volatile uint32_t POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY;
    volatile uint32_t POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY;
    volatile uint32_t POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY;
    volatile uint32_t POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY;
    volatile uint32_t POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY;
    volatile uint32_t POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY;
    volatile uint32_t POK_VDDS_DDRIO_UV_CTRL_PROXY;
    volatile uint32_t POK_VDDS_DDRIO_OV_CTRL_PROXY;
    volatile uint8_t  Resv_106848[8];
    volatile uint32_t POK_VDDA_PMIC_IN_CTRL_PROXY;
    volatile uint8_t  Resv_106864[12];
    volatile uint32_t RST_CTRL_PROXY;
    volatile uint32_t RST_STAT_PROXY;
    volatile uint32_t RST_SRC_PROXY;
    volatile uint32_t RST_MAGIC_WORD_PROXY;
    volatile uint32_t ISO_CTRL_PROXY;
    volatile uint8_t  Resv_106896[12];
    volatile uint32_t VDD_CORE_GLDTC_CTRL_PROXY;
    volatile uint8_t  Resv_106928[28];
    volatile uint32_t VDD_CORE_GLDTC_STAT_PROXY;
    volatile uint8_t  Resv_107008[76];
    volatile uint32_t PRG_PP_0_CTRL_PROXY;
    volatile uint32_t PRG_PP_0_STAT_PROXY;
    volatile uint32_t PRG_PP_1_CTRL_PROXY;
    volatile uint32_t PRG_PP_1_STAT_PROXY;
    volatile uint8_t  Resv_107136[112];
    volatile uint32_t CLKGATE_CTRL_PROXY;
    volatile uint8_t  Resv_110600[3460];
    volatile uint32_t LOCK6_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK6_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_110848[240];
    volatile uint32_t CLAIMREG_P6_R0;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R1;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R2;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R3;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R4;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R5;            /* Claim bits for Partition 6 */
} CSL_mcu_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MCU_CTRL_MMR_CFG0_PID                                        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0                                   (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1                                   (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0                                   (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0                                   (0x00000180U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT                               (0x00000270U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT                            (0x00000280U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0                                (0x00001008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1                                (0x0000100CU)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS                            (0x00001010U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR                  (0x00001014U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE                                (0x00001018U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                          (0x0000101CU)
#define CSL_MCU_CTRL_MMR_CFG0_EOI                                        (0x00001020U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS                              (0x00001024U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                          (0x00001028U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                          (0x0000102CU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR                                (0x00001030U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY                    (0x00001100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY                    (0x00001104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY                    (0x00001108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY                    (0x0000110CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY                    (0x00001110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY                    (0x00001114U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY                                  (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY                             (0x00002004U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY                             (0x00002008U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY                             (0x00002100U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY                             (0x00002180U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY                         (0x00002270U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY                      (0x00002280U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY                          (0x00003008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY                          (0x0000300CU)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY                      (0x00003010U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY            (0x00003014U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY                          (0x00003018U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY                    (0x0000301CU)
#define CSL_MCU_CTRL_MMR_CFG0_EOI_PROXY                                  (0x00003020U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY                        (0x00003024U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY                    (0x00003028U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY                    (0x0000302CU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY                          (0x00003030U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0                             (0x00003100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1                             (0x00003104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2                             (0x00003108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3                             (0x0000310CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4                             (0x00003110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5                             (0x00003114U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL                              (0x00004020U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1                               (0x00004084U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2                               (0x00004088U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3                               (0x0000408CU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4                               (0x00004090U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5                               (0x00004094U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6                               (0x00004098U)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM                            (0x000040A0U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT                            (0x000040B0U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0                           (0x000040C0U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1                           (0x000040C4U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2                           (0x000040C8U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3                           (0x000040CCU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0                           (0x000040D0U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1                           (0x000040D4U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2                           (0x000040D8U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3                           (0x000040DCU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL                            (0x00004204U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL                            (0x0000420CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL                              (0x000042E0U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0                            (0x00004604U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1                            (0x00004608U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT                                   (0x00004610U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0                                (0x00005008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1                                (0x0000500CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY                    (0x00005100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY                    (0x00005104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY                    (0x00005108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY                    (0x0000510CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY                    (0x00005110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY                    (0x00005114U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY                    (0x00005118U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY                    (0x0000511CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY                    (0x00005120U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY                    (0x00005124U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY                   (0x00005128U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY                   (0x0000512CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY                   (0x00005130U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_PROXY                        (0x00006020U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_PROXY                         (0x00006084U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_PROXY                         (0x00006088U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_PROXY                         (0x0000608CU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_PROXY                         (0x00006090U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_PROXY                         (0x00006094U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_PROXY                         (0x00006098U)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_PROXY                      (0x000060A0U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY                      (0x000060B0U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_PROXY                     (0x000060C0U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_PROXY                     (0x000060C4U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_PROXY                     (0x000060C8U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_PROXY                     (0x000060CCU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_PROXY                     (0x000060D0U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_PROXY                     (0x000060D4U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_PROXY                     (0x000060D8U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_PROXY                     (0x000060DCU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_PROXY                      (0x00006204U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_PROXY                      (0x0000620CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_PROXY                        (0x000062E0U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY                      (0x00006604U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY                      (0x00006608U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY                             (0x00006610U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY                          (0x00007008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY                          (0x0000700CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0                             (0x00007100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1                             (0x00007104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2                             (0x00007108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3                             (0x0000710CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4                             (0x00007110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5                             (0x00007114U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6                             (0x00007118U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7                             (0x0000711CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8                             (0x00007120U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9                             (0x00007124U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10                            (0x00007128U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11                            (0x0000712CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12                            (0x00007130U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL                            (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL                                (0x00008010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM                                (0x00008018U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT                                (0x00008020U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM                             (0x00008024U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL                     (0x00008030U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL                                (0x00008038U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM                                (0x0000803CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL                             (0x00008050U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL                     (0x00008058U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL                          (0x00008060U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL                          (0x00008064U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL                          (0x00008068U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL                          (0x0000806CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL                            (0x00008070U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL                           (0x00008080U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL                           (0x00008084U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL                            (0x000080A0U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL                            (0x000080A4U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL                            (0x000080B0U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0                                (0x00009008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1                                (0x0000900CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY                    (0x00009100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY                    (0x00009104U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY                      (0x0000A000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY                          (0x0000A010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY                          (0x0000A018U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_PROXY                          (0x0000A020U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY                       (0x0000A024U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY               (0x0000A030U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY                          (0x0000A038U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY                          (0x0000A03CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY                       (0x0000A050U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_PROXY               (0x0000A058U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_PROXY                    (0x0000A060U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_PROXY                    (0x0000A064U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_PROXY                    (0x0000A068U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_PROXY                    (0x0000A06CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_PROXY                      (0x0000A070U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_PROXY                     (0x0000A080U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_PROXY                     (0x0000A084U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_PROXY                      (0x0000A0A0U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_PROXY                      (0x0000A0A4U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY                      (0x0000A0B0U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY                          (0x0000B008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY                          (0x0000B00CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0                             (0x0000B100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1                             (0x0000B104U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL                      (0x0000C020U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT                  (0x0000C024U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0                     (0x0000C028U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1                     (0x0000C02CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0                    (0x0000C030U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1                    (0x0000C034U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT                      (0x0000C038U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR                      (0x0000C03CU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0                                (0x0000D008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1                                (0x0000D00CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY                    (0x0000D100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY                (0x0000E020U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY            (0x0000E024U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PROXY               (0x0000E028U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PROXY               (0x0000E02CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY              (0x0000E030U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_PROXY              (0x0000E034U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY                (0x0000E038U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_PROXY                (0x0000E03CU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY                          (0x0000F008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY                          (0x0000F00CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0                             (0x0000F100U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0                                    (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1                                    (0x00010004U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2                                    (0x00010008U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3                                    (0x0001000CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4                                    (0x00010010U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5                                    (0x00010014U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6                                    (0x00010018U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7                                    (0x0001001CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET                                (0x00010200U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET                                (0x00010204U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET                                (0x00010208U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET                                (0x0001020CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR                                (0x00010300U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR                                (0x00010304U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR                                (0x00010308U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR                                (0x0001030CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL                                   (0x00010400U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE                                 (0x00010408U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN                        (0x00010420U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN                       (0x00010424U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN                            (0x00010428U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN                            (0x0001042CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL                            (0x00010430U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0                                   (0x00010480U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1                                   (0x00010484U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2                                   (0x00010488U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3                                   (0x0001048CU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4                                   (0x00010490U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5                                   (0x00010494U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6                                   (0x00010498U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7                                   (0x0001049CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL                        (0x000104F0U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0                         (0x00010500U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1                         (0x00010504U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2                         (0x00010508U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3                         (0x0001050CU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4                         (0x00010510U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5                         (0x00010514U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6                         (0x00010518U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7                         (0x0001051CU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8                         (0x00010520U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9                         (0x00010524U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC                                (0x00010700U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC                                (0x00010720U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC                                (0x00010730U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR                                  (0x00010740U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL                 (0x00010744U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL                 (0x00010748U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL                 (0x0001074CU)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN                     (0x00010750U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL                 (0x00010760U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE                        (0x00010764U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL             (0x00010770U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8                  (0x00010774U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3                  (0x00010778U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO                       (0x0001077CU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS                          (0x000107F0U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS                          (0x000107F4U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS                          (0x000107F8U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL                          (0x00010800U)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG                                (0x00010810U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL                         (0x00010820U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS                          (0x00010824U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG                       (0x00010830U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS                       (0x00010834U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG                          (0x00010880U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG                          (0x00010884U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG                          (0x00010890U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL                     (0x00010894U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG                     (0x00010900U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG                     (0x00010904U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG                     (0x00010908U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG                     (0x00010914U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG                     (0x0001091CU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG                     (0x00010920U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG                    (0x00010930U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG                    (0x0001093CU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG                    (0x00010944U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG                 (0x00010980U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0                                (0x00011008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1                                (0x0001100CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY                    (0x00011100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY                    (0x00011104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY                    (0x00011108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY                    (0x0001110CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY                    (0x00011110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY                    (0x00011114U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY                    (0x00011118U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY                    (0x0001111CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY                    (0x00011120U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY                    (0x00011124U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY                   (0x00011128U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_READONLY                   (0x0001112CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_READONLY                   (0x00011130U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_READONLY                   (0x00011134U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_READONLY                   (0x00011138U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_READONLY                   (0x0001113CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_READONLY                   (0x00011140U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_READONLY                   (0x00011144U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_READONLY                   (0x00011148U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_READONLY                   (0x0001114CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_PROXY                              (0x00012000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_PROXY                              (0x00012004U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_PROXY                              (0x00012008U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_PROXY                              (0x0001200CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_PROXY                              (0x00012010U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_PROXY                              (0x00012014U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_PROXY                              (0x00012018U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_PROXY                              (0x0001201CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_PROXY                          (0x00012200U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_PROXY                          (0x00012204U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_PROXY                          (0x00012208U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_PROXY                          (0x0001220CU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_PROXY                          (0x00012300U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_PROXY                          (0x00012304U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_PROXY                          (0x00012308U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_PROXY                          (0x0001230CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY                             (0x00012400U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_PROXY                           (0x00012408U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_PROXY                  (0x00012420U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY                 (0x00012424U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_PROXY                      (0x00012428U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_PROXY                      (0x0001242CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY                      (0x00012430U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_PROXY                             (0x00012480U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_PROXY                             (0x00012484U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_PROXY                             (0x00012488U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_PROXY                             (0x0001248CU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_PROXY                             (0x00012490U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_PROXY                             (0x00012494U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_PROXY                             (0x00012498U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_PROXY                             (0x0001249CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_PROXY                  (0x000124F0U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_PROXY                   (0x00012500U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_PROXY                   (0x00012504U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_PROXY                   (0x00012508U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_PROXY                   (0x0001250CU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_PROXY                   (0x00012510U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_PROXY                   (0x00012514U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_PROXY                   (0x00012518U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_PROXY                   (0x0001251CU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_PROXY                   (0x00012520U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_PROXY                   (0x00012524U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY                          (0x00012700U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY                          (0x00012720U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY                          (0x00012730U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY                            (0x00012740U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_PROXY           (0x00012744U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_PROXY           (0x00012748U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_PROXY           (0x0001274CU)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_PROXY               (0x00012750U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_PROXY           (0x00012760U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_PROXY                  (0x00012764U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY       (0x00012770U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_PROXY            (0x00012774U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_PROXY            (0x00012778U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_PROXY                 (0x0001277CU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY                    (0x000127F0U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY                    (0x000127F4U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY                    (0x000127F8U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY                    (0x00012800U)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_PROXY                          (0x00012810U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY                   (0x00012820U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY                    (0x00012824U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY                 (0x00012830U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY                 (0x00012834U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_PROXY                    (0x00012880U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_PROXY                    (0x00012884U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY                    (0x00012890U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY               (0x00012894U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY               (0x00012900U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY               (0x00012904U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY               (0x00012908U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY               (0x00012914U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY               (0x0001291CU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY               (0x00012920U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY              (0x00012930U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY              (0x0001293CU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY              (0x00012944U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY           (0x00012980U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY                          (0x00013008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY                          (0x0001300CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0                             (0x00013100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1                             (0x00013104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2                             (0x00013108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3                             (0x0001310CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4                             (0x00013110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5                             (0x00013114U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6                             (0x00013118U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7                             (0x0001311CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8                             (0x00013120U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9                             (0x00013124U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10                            (0x00013128U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11                            (0x0001312CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12                            (0x00013130U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13                            (0x00013134U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14                            (0x00013138U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15                            (0x0001313CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16                            (0x00013140U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17                            (0x00013144U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18                            (0x00013148U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19                            (0x0001314CU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL                                   (0x00018000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT                                   (0x00018004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL                           (0x00018100U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL                       (0x00018110U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL                       (0x00018114U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL                       (0x00018118U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL                       (0x0001811CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL                      (0x00018120U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL                      (0x00018124U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL           (0x00018138U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL           (0x0001813CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL                (0x00018140U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL                (0x00018144U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL                (0x00018148U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL                (0x0001814CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL                     (0x00018150U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL                     (0x00018154U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL                      (0x00018160U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL                                   (0x00018170U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT                                   (0x00018174U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC                                    (0x00018178U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD                             (0x0001817CU)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL                                   (0x00018180U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL                        (0x00018190U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT                        (0x000181B0U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL                              (0x00018200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT                              (0x00018204U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL                              (0x00018208U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT                              (0x0001820CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL                               (0x00018280U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0                                (0x00019008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1                                (0x0001900CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY                    (0x00019100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY                    (0x00019104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY                    (0x00019108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY                    (0x0001910CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY                    (0x00019110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY                    (0x00019114U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY                             (0x0001A000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY                             (0x0001A004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY                     (0x0001A100U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY                 (0x0001A110U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY                 (0x0001A114U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY                 (0x0001A118U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY                 (0x0001A11CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY                (0x0001A120U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY                (0x0001A124U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY     (0x0001A138U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY     (0x0001A13CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY          (0x0001A140U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY          (0x0001A144U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY          (0x0001A148U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY          (0x0001A14CU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY               (0x0001A150U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY               (0x0001A154U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY                (0x0001A160U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY                             (0x0001A170U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_PROXY                             (0x0001A174U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY                              (0x0001A178U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY                       (0x0001A17CU)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY                             (0x0001A180U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY                  (0x0001A190U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY                  (0x0001A1B0U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY                        (0x0001A200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY                        (0x0001A204U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY                        (0x0001A208U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY                        (0x0001A20CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY                         (0x0001A280U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY                          (0x0001B008U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY                          (0x0001B00CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0                             (0x0001B100U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1                             (0x0001B104U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2                             (0x0001B108U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3                             (0x0001B10CU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4                             (0x0001B110U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5                             (0x0001B114U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                         (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                          (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                        (0x000000C0U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                       (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                         (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                         (0x00000700U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                        (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                          (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MISC_MASK                          (0x0000F800U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                         (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MISC_MAX                           (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                         (0xFFFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                        (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                          (0x0000FFFFU)

/* MMR_CFG0 */

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_MASK                     (0x0000FFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_SHIFT                    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_SPEC_REV_MAX                      (0x0000FFFFU)

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_MASK                      (0xFFFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_SHIFT                     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_CFG_REV_MAX                       (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                   (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                    (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                     (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                    (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                      (0x00000001U)

/* IPC_SET0 */

#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SET_MASK                      (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SET_SHIFT                     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SET_MAX                       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SRC_SET_MASK                  (0xFFFFFFF0U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SRC_SET_SHIFT                 (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_IPC_SRC_SET_MAX                   (0x0FFFFFFFU)

/* IPC_CLR0 */

#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_CLR_MASK                      (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_CLR_SHIFT                     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_CLR_MAX                       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_SRC_CLR_MASK                  (0xFFFFFFF0U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_SRC_CLR_SHIFT                 (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_IPC_SRC_CLR_MAX                   (0x0FFFFFFFU)

/* CBA_ERR_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_MASK              (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_SHIFT             (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_MASK        (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_SHIFT       (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_MAX         (0x00000001U)

/* ACCESS_ERR_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_MASK        (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_MASK        (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_SHIFT       (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_MASK        (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_SHIFT       (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_MASK        (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_SHIFT       (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_MASK        (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_SHIFT       (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_MAX         (0x00000001U)

/* LOCK0_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK0_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MAX                (0xFFFFFFFFU)

/* INTR_RAW_STATUS */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK              (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK              (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT             (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK              (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT             (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK             (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT            (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX              (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MAX (0x00000001U)

/* INTR_ENABLE */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK               (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK               (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT              (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK               (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT              (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT             (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX               (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK     (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT    (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT    (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT   (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX     (0x00000001U)

/* EOI */

#define CSL_MCU_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                        (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                         (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK              (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX               (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK          (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX           (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK            (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT           (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX             (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK        (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX         (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK       (0x000FFF00U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT      (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX        (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK           (0xFFF00000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT          (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX            (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK                 (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX                  (0x00000001U)

/* CLAIMREG_P0_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R1_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R2_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R3_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R4_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R5_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MAX (0xFFFFFFFFU)

/* PID_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MASK             (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_SHIFT            (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MAX              (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MASK            (0x000000C0U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_SHIFT           (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MAX             (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MASK             (0x00000700U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_SHIFT            (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MAX              (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MASK              (0x0000F800U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_SHIFT             (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MAX               (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MASK             (0xFFFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_SHIFT            (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MAX              (0x0000FFFFU)

/* MMR_CFG0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_MASK (0x0000FFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_SPEC_REV_PROXY_MAX (0x0000FFFFU)

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_MASK (0xFFFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG0_PROXY_MMR_CFG0_CFG_REV_PROXY_MAX  (0x0000FFFFU)

/* MMR_CFG1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MASK (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MAX (0x00000001U)

/* IPC_SET0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SET_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SET_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SET_PROXY_MAX  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SRC_SET_PROXY_MASK (0xFFFFFFF0U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SRC_SET_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_SET0_PROXY_IPC_SET0_IPC_SRC_SET_PROXY_MAX (0x0FFFFFFFU)

/* IPC_CLR0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_CLR_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_CLR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_CLR_PROXY_MAX  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_SRC_CLR_PROXY_MASK (0xFFFFFFF0U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_SRC_CLR_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IPC_CLR0_PROXY_IPC_CLR0_IPC_SRC_CLR_PROXY_MAX (0x0FFFFFFFU)

/* CBA_ERR_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_MASK (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_SHIFT (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_MAX (0x00000001U)

/* ACCESS_ERR_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_MAX (0x00000001U)

/* LOCK0_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK0_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* INTR_RAW_STATUS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MASK  (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MASK  (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MASK  (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MAX  (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MAX (0x00000001U)

/* INTR_ENABLE_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MASK   (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MASK   (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_SHIFT  (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MASK   (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_SHIFT  (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MASK  (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MAX   (0x00000001U)

/* INTR_ENABLE_CLEAR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MAX (0x00000001U)

/* EOI_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MASK            (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_SHIFT           (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MAX             (0x000000FFU)

/* FAULT_ADDRESS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MASK  (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MAX   (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MASK (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_SHIFT (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MAX (0x00000001U)

/* FAULT_ATTR_STATUS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MASK (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MASK (0x000FFF00U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MASK (0xFFF00000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_SHIFT (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MAX (0x00000FFFU)

/* FAULT_CLEAR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MASK     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MAX      (0x00000001U)

/* CLAIMREG_P0_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R1 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R2 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R3 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R4 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R5 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MAX          (0xFFFFFFFFU)

/* MCU_GPIO_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_WAKEN_MASK                   (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_WAKEN_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_WAKEN_MAX                    (0x00000001U)

/* DBOUNCE_CFG1 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_DB_CFG_MAX                    (0x0000003FU)

/* DBOUNCE_CFG2 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_DB_CFG_MAX                    (0x0000003FU)

/* DBOUNCE_CFG3 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_DB_CFG_MAX                    (0x0000003FU)

/* DBOUNCE_CFG4 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_DB_CFG_MAX                    (0x0000003FU)

/* DBOUNCE_CFG5 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_DB_CFG_MAX                    (0x0000003FU)

/* DBOUNCE_CFG6 */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_DB_CFG_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_DB_CFG_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_DB_CFG_MAX                    (0x0000003FU)

/* TEMP_DIODE_TRIM */

#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_TRIM_MASK                  (0x00003FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_TRIM_SHIFT                 (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_TRIM_MAX                   (0x00003FFFU)

/* IO_VOLTAGE_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_WKUP_MCU_MASK              (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_WKUP_MCU_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_WKUP_MCU_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_FLASH_MASK                 (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_FLASH_SHIFT                (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_FLASH_MAX                  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_CANUART_MASK               (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_CANUART_SHIFT              (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_CANUART_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GENERAL_MASK               (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GENERAL_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GENERAL_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC0_MASK                  (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC0_SHIFT                 (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC0_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC1_MASK                  (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC1_SHIFT                 (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC1_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC2_MASK                  (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC2_SHIFT                 (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_MMC2_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GEMAC_MASK                 (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GEMAC_SHIFT                (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GEMAC_MAX                  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GPMC_MASK                  (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GPMC_SHIFT                 (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_GPMC_MAX                   (0x00000001U)

/* H_IO_DRVSTRNGTH0 */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_DRV_STR_MAX               (0x0000000FU)

/* H_IO_DRVSTRNGTH1 */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_DRV_STR_MAX               (0x0000000FU)

/* H_IO_DRVSTRNGTH2 */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_DRV_STR_MAX               (0x0000000FU)

/* H_IO_DRVSTRNGTH3 */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_DRV_STR_MAX               (0x0000000FU)

/* V_IO_DRVSTRNGTH0 */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_DRV_STR_MAX               (0x0000000FU)

/* V_IO_DRVSTRNGTH1 */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_DRV_STR_MAX               (0x0000000FU)

/* V_IO_DRVSTRNGTH2 */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_DRV_STR_MAX               (0x0000000FU)

/* V_IO_DRVSTRNGTH3 */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_DRV_STR_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_DRV_STR_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_DRV_STR_MAX               (0x0000000FU)

/* MCU_TIMER1_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_CASCADE_EN_MASK            (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_CASCADE_EN_SHIFT           (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_CASCADE_EN_MAX             (0x00000001U)

/* MCU_TIMER3_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_CASCADE_EN_MASK            (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_CASCADE_EN_SHIFT           (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_CASCADE_EN_MAX             (0x00000001U)

/* MCU_I2C0_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_HS_MCS_EN_MASK               (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_HS_MCS_EN_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_HS_MCS_EN_MAX                (0x00000001U)

/* WKUP_MTOG_CTRL0 */

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_VAL_MASK           (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_VAL_SHIFT          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_VAL_MAX            (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_EN_MASK            (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_EN_SHIFT           (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_TIMEOUT_EN_MAX             (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_MASK         (0x00FF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_SHIFT        (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_MAX          (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_IDLE_STAT_MASK             (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_IDLE_STAT_SHIFT            (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_IDLE_STAT_MAX              (0x00000001U)

/* WKUP_MTOG_CTRL1 */

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_VAL_MASK           (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_VAL_SHIFT          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_VAL_MAX            (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_EN_MASK            (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_EN_SHIFT           (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_TIMEOUT_EN_MAX             (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_MASK         (0x00FF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_SHIFT        (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_MAX          (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_IDLE_STAT_MASK             (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_IDLE_STAT_SHIFT            (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_IDLE_STAT_MAX              (0x00000001U)

/* TOG_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_MASK                 (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_MAX                  (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_MASK                 (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_SHIFT                (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_MAX                  (0x00000001U)

/* LOCK1_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK1_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P1_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R1_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R2_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R3_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R4_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R5_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R6_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R7_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R8_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R9_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R10_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R11_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R12_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MAX (0xFFFFFFFFU)

/* MCU_GPIO_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_PROXY_MCU_GPIO_CTRL_WAKEN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_PROXY_MCU_GPIO_CTRL_WAKEN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CTRL_PROXY_MCU_GPIO_CTRL_WAKEN_PROXY_MAX (0x00000001U)

/* DBOUNCE_CFG1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_PROXY_DBOUNCE_CFG1_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_PROXY_DBOUNCE_CFG1_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG1_PROXY_DBOUNCE_CFG1_DB_CFG_PROXY_MAX (0x0000003FU)

/* DBOUNCE_CFG2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_PROXY_DBOUNCE_CFG2_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_PROXY_DBOUNCE_CFG2_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG2_PROXY_DBOUNCE_CFG2_DB_CFG_PROXY_MAX (0x0000003FU)

/* DBOUNCE_CFG3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_PROXY_DBOUNCE_CFG3_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_PROXY_DBOUNCE_CFG3_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG3_PROXY_DBOUNCE_CFG3_DB_CFG_PROXY_MAX (0x0000003FU)

/* DBOUNCE_CFG4_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_PROXY_DBOUNCE_CFG4_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_PROXY_DBOUNCE_CFG4_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG4_PROXY_DBOUNCE_CFG4_DB_CFG_PROXY_MAX (0x0000003FU)

/* DBOUNCE_CFG5_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_PROXY_DBOUNCE_CFG5_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_PROXY_DBOUNCE_CFG5_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG5_PROXY_DBOUNCE_CFG5_DB_CFG_PROXY_MAX (0x0000003FU)

/* DBOUNCE_CFG6_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_PROXY_DBOUNCE_CFG6_DB_CFG_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_PROXY_DBOUNCE_CFG6_DB_CFG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DBOUNCE_CFG6_PROXY_DBOUNCE_CFG6_DB_CFG_PROXY_MAX (0x0000003FU)

/* TEMP_DIODE_TRIM_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_PROXY_TEMP_DIODE_TRIM_TRIM_PROXY_MASK (0x00003FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_PROXY_TEMP_DIODE_TRIM_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_TEMP_DIODE_TRIM_PROXY_TEMP_DIODE_TRIM_TRIM_PROXY_MAX (0x00003FFFU)

/* IO_VOLTAGE_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_WKUP_MCU_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_WKUP_MCU_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_WKUP_MCU_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_FLASH_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_FLASH_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_FLASH_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_CANUART_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_CANUART_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_CANUART_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GENERAL_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GENERAL_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GENERAL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC0_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC0_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC0_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC1_PROXY_MASK (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC1_PROXY_SHIFT (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC1_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC2_PROXY_MASK (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC2_PROXY_SHIFT (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_MMC2_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GEMAC_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GEMAC_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GEMAC_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GPMC_PROXY_MASK (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GPMC_PROXY_SHIFT (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_IO_VOLTAGE_STAT_PROXY_IO_VOLTAGE_STAT_GPMC_PROXY_MAX (0x00000001U)

/* H_IO_DRVSTRNGTH0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_PROXY_H_IO_DRVSTRNGTH0_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_PROXY_H_IO_DRVSTRNGTH0_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH0_PROXY_H_IO_DRVSTRNGTH0_DRV_STR_PROXY_MAX (0x0000000FU)

/* H_IO_DRVSTRNGTH1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_PROXY_H_IO_DRVSTRNGTH1_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_PROXY_H_IO_DRVSTRNGTH1_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH1_PROXY_H_IO_DRVSTRNGTH1_DRV_STR_PROXY_MAX (0x0000000FU)

/* H_IO_DRVSTRNGTH2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_PROXY_H_IO_DRVSTRNGTH2_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_PROXY_H_IO_DRVSTRNGTH2_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH2_PROXY_H_IO_DRVSTRNGTH2_DRV_STR_PROXY_MAX (0x0000000FU)

/* H_IO_DRVSTRNGTH3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_PROXY_H_IO_DRVSTRNGTH3_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_PROXY_H_IO_DRVSTRNGTH3_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_H_IO_DRVSTRNGTH3_PROXY_H_IO_DRVSTRNGTH3_DRV_STR_PROXY_MAX (0x0000000FU)

/* V_IO_DRVSTRNGTH0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_PROXY_V_IO_DRVSTRNGTH0_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_PROXY_V_IO_DRVSTRNGTH0_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH0_PROXY_V_IO_DRVSTRNGTH0_DRV_STR_PROXY_MAX (0x0000000FU)

/* V_IO_DRVSTRNGTH1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_PROXY_V_IO_DRVSTRNGTH1_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_PROXY_V_IO_DRVSTRNGTH1_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH1_PROXY_V_IO_DRVSTRNGTH1_DRV_STR_PROXY_MAX (0x0000000FU)

/* V_IO_DRVSTRNGTH2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_PROXY_V_IO_DRVSTRNGTH2_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_PROXY_V_IO_DRVSTRNGTH2_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH2_PROXY_V_IO_DRVSTRNGTH2_DRV_STR_PROXY_MAX (0x0000000FU)

/* V_IO_DRVSTRNGTH3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_PROXY_V_IO_DRVSTRNGTH3_DRV_STR_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_PROXY_V_IO_DRVSTRNGTH3_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_V_IO_DRVSTRNGTH3_PROXY_V_IO_DRVSTRNGTH3_DRV_STR_PROXY_MAX (0x0000000FU)

/* MCU_TIMER1_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_PROXY_MCU_TIMER1_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_PROXY_MCU_TIMER1_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CTRL_PROXY_MCU_TIMER1_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* MCU_TIMER3_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_PROXY_MCU_TIMER3_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_PROXY_MCU_TIMER3_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CTRL_PROXY_MCU_TIMER3_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* MCU_I2C0_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_PROXY_MCU_I2C0_CTRL_HS_MCS_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_PROXY_MCU_I2C0_CTRL_HS_MCS_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_I2C0_CTRL_PROXY_MCU_I2C0_CTRL_HS_MCS_EN_PROXY_MAX (0x00000001U)

/* WKUP_MTOG_CTRL0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_VAL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_VAL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_VAL_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_EN_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_TIMEOUT_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_PROXY_MASK (0x00FF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_FORCE_TIMEOUT_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_IDLE_STAT_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_IDLE_STAT_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL0_PROXY_WKUP_MTOG_CTRL0_IDLE_STAT_PROXY_MAX (0x00000001U)

/* WKUP_MTOG_CTRL1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_VAL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_VAL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_VAL_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_EN_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_TIMEOUT_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_PROXY_MASK (0x00FF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_FORCE_TIMEOUT_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_IDLE_STAT_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_IDLE_STAT_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_WKUP_MTOG_CTRL1_PROXY_WKUP_MTOG_CTRL1_IDLE_STAT_PROXY_MAX (0x00000001U)

/* TOG_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_MAX (0x00000001U)

/* LOCK1_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK1_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P1_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R1 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R2 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R3 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R4 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R5 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R6 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R7 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R8 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R9 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R10 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R11 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R12 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MAX        (0xFFFFFFFFU)

/* MCU_OBSCLK_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_SEL_MASK               (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_SEL_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_SEL_MAX                (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_MASK               (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_MAX                (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_CLK_DIV_LD_MAX             (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_OUT_MUX_SEL_MASK           (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_OUT_MUX_SEL_SHIFT          (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_OUT_MUX_SEL_MAX            (0x00000001U)

/* HFOSC0_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_BP_C_MASK                      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_BP_C_SHIFT                     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_BP_C_MAX                       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PD_C_MASK                      (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PD_C_SHIFT                     (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PD_C_MAX                       (0x00000001U)

/* HFOSC0_TRIM */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_IBIAS_REF_MASK               (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_IBIAS_REF_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_IBIAS_REF_MAX                (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_IBIAS_COMP_MASK              (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_IBIAS_COMP_SHIFT             (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_IBIAS_COMP_MAX               (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_REF_MASK                     (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_REF_SHIFT                    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_R_REF_MAX                      (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_MULT_MASK                    (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_MULT_SHIFT                   (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_I_MULT_MAX                     (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_HYST_MASK                      (0x00300000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_HYST_SHIFT                     (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_HYST_MAX                       (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_TRIM_EN_MASK                   (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_TRIM_EN_SHIFT                  (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_TRIM_EN_MAX                    (0x00000001U)

/* HFOSC0_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_DS_ON_WFI_STAT_MASK            (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_DS_ON_WFI_STAT_SHIFT           (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_DS_ON_WFI_STAT_MAX             (0x00000001U)

/* RC12M_OSC_TRIM */

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_FINE_MASK           (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_FINE_SHIFT          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_FINE_MAX            (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_MASK         (0x00000038U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_SHIFT        (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_MAX          (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_MASK     (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_SHIFT    (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_MAX      (0x00000001U)

/* HFOSC0_CLKOUT_32K_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_HSDIV_MASK          (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_HSDIV_SHIFT         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_HSDIV_MAX           (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_MASK       (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_SHIFT      (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_MASK      (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_SHIFT     (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_RESET_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_RESET_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_RESET_MAX           (0x00000001U)

/* LFXOSC_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_BP_C_MASK                      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_BP_C_SHIFT                     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_BP_C_MAX                       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PD_C_MASK                      (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PD_C_SHIFT                     (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PD_C_MAX                       (0x00000001U)

/* LFXOSC_TRIM */

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_IBIAS_REF_MASK               (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_IBIAS_REF_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_IBIAS_REF_MAX                (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_IBIAS_COMP_MASK              (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_IBIAS_COMP_SHIFT             (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_IBIAS_COMP_MAX               (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_REF_MASK                     (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_REF_SHIFT                    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_R_REF_MAX                      (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_MULT_MASK                    (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_MULT_SHIFT                   (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_I_MULT_MAX                     (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_HYST_MASK                      (0x00300000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_HYST_SHIFT                     (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_HYST_MAX                       (0x00000003U)

/* MCU_PLL_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_MASK       (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_SHIFT      (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYP_WARM_RST_MASK           (0x00800000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYP_WARM_RST_SHIFT          (0x00000017U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYP_WARM_RST_MAX            (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_MASK         (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_SHIFT        (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_MAX          (0x00000001U)

/* DEVICE_CLKOUT_32K_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_MAX  (0x00000003U)

/* MCU_TIMER0_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_CLK_SEL_MASK             (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_CLK_SEL_SHIFT            (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_CLK_SEL_MAX              (0x00000007U)

/* MCU_TIMER1_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_CLK_SEL_MASK             (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_CLK_SEL_SHIFT            (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_CLK_SEL_MAX              (0x00000007U)

/* MCU_TIMER2_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_CLK_SEL_MASK             (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_CLK_SEL_SHIFT            (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_CLK_SEL_MAX              (0x00000007U)

/* MCU_TIMER3_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_CLK_SEL_MASK             (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_CLK_SEL_SHIFT            (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_CLK_SEL_MAX              (0x00000007U)

/* MCU_GPIO_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_CLK_SEL_MASK               (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_CLK_SEL_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_CLK_SEL_MAX                (0x00000003U)

/* MCU_MCAN0_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_CLK_SEL_MASK              (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_CLK_SEL_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_CLK_SEL_MAX               (0x00000003U)

/* MCU_MCAN1_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_CLK_SEL_MASK              (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_CLK_SEL_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_CLK_SEL_MAX               (0x00000003U)

/* MCU_SPI0_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_MASK        (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_SHIFT       (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_MAX         (0x00000001U)

/* MCU_SPI1_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_MASK        (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_SHIFT       (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_MAX         (0x00000001U)

/* MCU_WWD0_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_CLK_SEL_MASK               (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_CLK_SEL_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_CLK_SEL_MAX                (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_WRTLOCK_MASK               (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_WRTLOCK_SHIFT              (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_WRTLOCK_MAX                (0x00000001U)

/* LOCK2_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK2_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P2_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R1_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MAX (0xFFFFFFFFU)

/* MCU_OBSCLK_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_SEL_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_SEL_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_PROXY_MASK (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_LD_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_LD_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_CLK_DIV_LD_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_OUT_MUX_SEL_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_OUT_MUX_SEL_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_OBSCLK_CTRL_PROXY_MCU_OBSCLK_CTRL_OUT_MUX_SEL_PROXY_MAX (0x00000001U)

/* HFOSC0_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_BP_C_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_BP_C_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_BP_C_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_PD_C_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_PD_C_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CTRL_PROXY_HFOSC0_CTRL_PD_C_PROXY_MAX (0x00000001U)

/* HFOSC0_TRIM_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_IBIAS_REF_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_IBIAS_REF_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_IBIAS_REF_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_IBIAS_COMP_PROXY_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_IBIAS_COMP_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_IBIAS_COMP_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_REF_PROXY_MASK (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_REF_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_R_REF_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_MULT_PROXY_MASK (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_MULT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_I_MULT_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_HYST_PROXY_MASK (0x00300000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_HYST_PROXY_SHIFT (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_HYST_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_TRIM_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_TRIM_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_TRIM_PROXY_HFOSC0_TRIM_TRIM_EN_PROXY_MAX (0x00000001U)

/* HFOSC0_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_PROXY_HFOSC0_STAT_DS_ON_WFI_STAT_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_PROXY_HFOSC0_STAT_DS_ON_WFI_STAT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_STAT_PROXY_HFOSC0_STAT_DS_ON_WFI_STAT_PROXY_MAX (0x00000001U)

/* RC12M_OSC_TRIM_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_FINE_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_FINE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_FINE_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_PROXY_MASK (0x00000038U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_PROXY_MASK (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_PROXY_SHIFT (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_RC12M_OSC_TRIM_PROXY_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_PROXY_MAX (0x00000001U)

/* HFOSC0_CLKOUT_32K_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_HSDIV_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_HSDIV_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_HSDIV_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_RESET_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_RESET_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_HFOSC0_CLKOUT_32K_CTRL_PROXY_HFOSC0_CLKOUT_32K_CTRL_RESET_PROXY_MAX (0x00000001U)

/* LFXOSC_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_BP_C_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_BP_C_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_BP_C_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_PD_C_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_PD_C_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_CTRL_PROXY_LFXOSC_CTRL_PD_C_PROXY_MAX (0x00000001U)

/* LFXOSC_TRIM_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_IBIAS_REF_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_IBIAS_REF_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_IBIAS_REF_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_IBIAS_COMP_PROXY_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_IBIAS_COMP_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_IBIAS_COMP_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_REF_PROXY_MASK (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_REF_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_R_REF_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_MULT_PROXY_MASK (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_MULT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_I_MULT_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_HYST_PROXY_MASK (0x00300000U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_HYST_PROXY_SHIFT (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_LFXOSC_TRIM_PROXY_LFXOSC_TRIM_HYST_PROXY_MAX (0x00000003U)

/* MCU_PLL_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYP_WARM_RST_PROXY_MASK (0x00800000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYP_WARM_RST_PROXY_SHIFT (0x00000017U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYP_WARM_RST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_CLKSEL_PROXY_MCU_PLL_CLKSEL_BYPASS_SW_OVRD_PROXY_MAX (0x00000001U)

/* DEVICE_CLKOUT_32K_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_PROXY_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_PROXY_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DEVICE_CLKOUT_32K_CTRL_PROXY_DEVICE_CLKOUT_32K_CTRL_CLK_32K_RC_SEL_PROXY_MAX (0x00000003U)

/* MCU_TIMER0_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_PROXY_MCU_TIMER0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_PROXY_MCU_TIMER0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER0_CLKSEL_PROXY_MCU_TIMER0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* MCU_TIMER1_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_PROXY_MCU_TIMER1_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_PROXY_MCU_TIMER1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER1_CLKSEL_PROXY_MCU_TIMER1_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* MCU_TIMER2_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_PROXY_MCU_TIMER2_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_PROXY_MCU_TIMER2_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER2_CLKSEL_PROXY_MCU_TIMER2_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* MCU_TIMER3_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_PROXY_MCU_TIMER3_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_PROXY_MCU_TIMER3_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_TIMER3_CLKSEL_PROXY_MCU_TIMER3_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* MCU_GPIO_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_PROXY_MCU_GPIO_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_PROXY_MCU_GPIO_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_GPIO_CLKSEL_PROXY_MCU_GPIO_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

/* MCU_MCAN0_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_PROXY_MCU_MCAN0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_PROXY_MCU_MCAN0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN0_CLKSEL_PROXY_MCU_MCAN0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

/* MCU_MCAN1_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_PROXY_MCU_MCAN1_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_PROXY_MCU_MCAN1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_MCAN1_CLKSEL_PROXY_MCU_MCAN1_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

/* MCU_SPI0_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_PROXY_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_PROXY_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI0_CLKSEL_PROXY_MCU_SPI0_CLKSEL_MSTR_LB_CLKSEL_PROXY_MAX (0x00000001U)

/* MCU_SPI1_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_PROXY_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_PROXY_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_SPI1_CLKSEL_PROXY_MCU_SPI1_CLKSEL_MSTR_LB_CLKSEL_PROXY_MAX (0x00000001U)

/* MCU_WWD0_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_WWD0_CLKSEL_PROXY_MCU_WWD0_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* LOCK2_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK2_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P2_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R1 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MAX          (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_MASK    (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_SHIFT   (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_MAX     (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_MASK        (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_SHIFT       (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DC_DEF_MASK          (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DC_DEF_SHIFT         (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_DC_DEF_MAX           (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_MASK    (0x0000F000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_SHIFT   (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_MAX     (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_MASK      (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_MAX       (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_MASK        (0x0F000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_SHIFT       (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_MAX         (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_MASK      (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_SHIFT     (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_MAX       (0x00000001U)

/* MCU_R5FSS0_LBIST_PATCOUNT */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_MAX  (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_MASK  (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_MAX   (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_MASK (0x3FFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_MAX (0x00003FFFU)

/* MCU_R5FSS0_LBIST_SEED0 */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_MAX        (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_SEED1 */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_MASK       (0x001FFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_MAX        (0x001FFFFFU)

/* MCU_R5FSS0_LBIST_SPARE0 */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_SPARE0_MASK        (0xFFFFFFFCU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_SPARE0_SHIFT       (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_SPARE0_MAX         (0x3FFFFFFFU)

/* MCU_R5FSS0_LBIST_SPARE1 */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_SPARE1_MASK        (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_SPARE1_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_SPARE1_MAX         (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_MASK    (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_SHIFT   (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_MAX     (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_MASK     (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_SHIFT    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_MAX      (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_MASK    (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_SHIFT   (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_DONE_MASK       (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_DONE_SHIFT      (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_BIST_DONE_MAX        (0x00000001U)

/* MCU_R5FSS0_LBIST_MISR */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_MAX      (0xFFFFFFFFU)

/* LOCK3_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK3_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P3_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_MAX (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_PROXY_MASK (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DIVIDE_RATIO_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_LOAD_DIV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DC_DEF_PROXY_MASK (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DC_DEF_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_DC_DEF_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_PROXY_MASK (0x0000F000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_RUNBIST_MODE_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_PROXY_MASK (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_SUBCHIP_ID_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_PROXY_MASK (0x0F000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RUN_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL_PROXY_MCU_R5FSS0_LBIST_CTRL_BIST_RESET_PROXY_MAX (0x00000001U)

/* MCU_R5FSS0_LBIST_PATCOUNT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SCAN_PC_DEF_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_PROXY_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_RESET_PC_DEF_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_PROXY_MASK (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_SET_PC_DEF_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_PROXY_MASK (0x3FFF0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_PATCOUNT_PROXY_MCU_R5FSS0_LBIST_PATCOUNT_STATIC_PC_DEF_PROXY_MAX (0x00003FFFU)

/* MCU_R5FSS0_LBIST_SEED0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PROXY_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PROXY_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED0_PROXY_MCU_R5FSS0_LBIST_SEED0_PRPG_DEF_PROXY_MAX (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_SEED1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PROXY_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_PROXY_MASK (0x001FFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PROXY_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SEED1_PROXY_MCU_R5FSS0_LBIST_SEED1_PRPG_DEF_PROXY_MAX (0x001FFFFFU)

/* MCU_R5FSS0_LBIST_SPARE0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_LBIST_SELFTEST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_PBIST_SELFTEST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_SPARE0_PROXY_MASK (0xFFFFFFFCU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_SPARE0_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE0_PROXY_MCU_R5FSS0_LBIST_SPARE0_SPARE0_PROXY_MAX (0x3FFFFFFFU)

/* MCU_R5FSS0_LBIST_SPARE1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_PROXY_MCU_R5FSS0_LBIST_SPARE1_SPARE1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_PROXY_MCU_R5FSS0_LBIST_SPARE1_SPARE1_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_SPARE1_PROXY_MCU_R5FSS0_LBIST_SPARE1_SPARE1_PROXY_MAX (0xFFFFFFFFU)

/* MCU_R5FSS0_LBIST_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_PROXY_MASK (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_MISR_MUX_CTL_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_PROXY_MASK (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_OUT_MUX_CTL_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_RUNNING_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_DONE_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_DONE_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_STAT_PROXY_MCU_R5FSS0_LBIST_STAT_BIST_DONE_PROXY_MAX (0x00000001U)

/* MCU_R5FSS0_LBIST_MISR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_PROXY_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_PROXY_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_MISR_PROXY_MCU_R5FSS0_LBIST_MISR_MISR_RESULT_PROXY_MAX (0xFFFFFFFFU)

/* LOCK3_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK3_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P3_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_MAX          (0xFFFFFFFFU)

/* DV_REG0 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG1 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG2 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG3 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG4 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG5 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG6 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG7 */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_BIT_MASK                           (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_BIT_SHIFT                          (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_BIT_MAX                            (0xFFFFFFFFU)

/* DV_REG0_SET */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG1_SET */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG2_SET */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG3_SET */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG0_CLR */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG1_CLR */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG2_CLR */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_BIT_MAX                        (0xFFFFFFFFU)

/* DV_REG3_CLR */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_BIT_MASK                       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_BIT_SHIFT                      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_BIT_MAX                        (0xFFFFFFFFU)

/* LED_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_LED_MODE_MASK                     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_LED_MODE_SHIFT                    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_LED_MODE_MAX                      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_CONTROL_MASK                      (0xFFFFFFFEU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_CONTROL_SHIFT                     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_CONTROL_MAX                       (0x7FFFFFFFU)

/* LED_ENABLE */

#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_ENABLE_KEY_MASK                 (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_ENABLE_KEY_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_ENABLE_KEY_MAX                  (0xFFFFFFFFU)

/* LED_MCU_PLL_STAT_EN */

#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_MASK       (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_MAX        (0x00000001U)

/* LED_MAIN_PLL_STAT_EN */

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_MASK     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_MASK     (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_SHIFT    (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_MASK     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_SHIFT    (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_MASK     (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_SHIFT    (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_MASK     (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_SHIFT    (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_MASK     (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_SHIFT    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_MASK    (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_SHIFT   (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_MASK    (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_SHIFT   (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_MASK    (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_SHIFT   (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_MAX     (0x00000001U)

/* LED_PGD_STAT_EN */

#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_VDD_CORE_EN_MASK           (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_VDD_CORE_EN_SHIFT          (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_VDD_CORE_EN_MAX            (0x00000001U)

/* LED_EFC_STAT_EN */

#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_EFC_EN_MASK                (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_EFC_EN_SHIFT               (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_EFC_EN_MAX                 (0x00000001U)

/* LED_STATUS_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_STATUS_MASK         (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_STATUS_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_STATUS_MAX          (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_EN_MASK             (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_EN_SHIFT            (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_STICKY_EN_MAX              (0x00000001U)

/* SIM_CFG0 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG1 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG2 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG3 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG4 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG5 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG6 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_BIT_MAX                           (0xFFFFFFFFU)

/* SIM_CFG7 */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_BIT_MASK                          (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_BIT_SHIFT                         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_BIT_MAX                           (0xFFFFFFFFU)

/* MCU_PLL_TEST_CLKSEL */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_MASK      (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_SHIFT     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_MAX       (0x00000001U)

/* NON_AVS_MRGN_MODE0 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE1 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_MAX  (0x00000FFFU)

/* NON_AVS_MRGN_MODE2 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE3 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE4 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE5 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_MASK  (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_MAX   (0x00000FFFU)

/* NON_AVS_MRGN_MODE6 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_MAX  (0x00000FFFU)

/* NON_AVS_MRGN_MODE7 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_MAX  (0x00000FFFU)

/* NON_AVS_MRGN_MODE8 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE9 */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_MAX (0x00000FFFU)

/* ATEST_RCOSC */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_TEST_MASK                (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_TEST_SHIFT               (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_TEST_MAX                 (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_EN_MASK                  (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_EN_SHIFT                 (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_ATEST_EN_MAX                   (0x00000001U)

/* ATEST_HFOSC */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_TEST_EN_C_MASK                 (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_TEST_EN_C_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_TEST_EN_C_MAX                  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_FREQ_RANGE_C_MASK              (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_FREQ_RANGE_C_SHIFT             (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_FREQ_RANGE_C_MAX               (0x00000003U)

/* ATEST_LFOSC */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_TEST_EN_C_MASK                 (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_TEST_EN_C_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_TEST_EN_C_MAX                  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_FREQ_RANGE_C_MASK              (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_FREQ_RANGE_C_SHIFT             (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_FREQ_RANGE_C_MAX               (0x00000003U)

/* ATEST_POR */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATEST_MASK                   (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATEST_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATEST_MAX                    (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATESTIN_MASK                 (0x00000700U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATESTIN_SHIFT                (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SEL_ATESTIN_MAX                  (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_CLKIN_TST_MASK                   (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_CLKIN_TST_SHIFT                  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_CLKIN_TST_MAX                    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SELCLKIN_TST_MASK                (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SELCLKIN_TST_SHIFT               (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_SELCLKIN_TST_MAX                 (0x00000001U)

/* ATEST_POK_VDDA_MCU_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDA_MCU_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDD_CORE_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDA_PMIC_IN */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_MASK   (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_MAX    (0x00000007U)

/* ATEST_POK_VDD_CORE_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDR_CORE */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_MASK      (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_SHIFT     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_MAX       (0x00000007U)

/* ATEST_POK_VMON_CAP_MCU_GENERAL */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDSHV_MAIN_1P8 */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDSHV_MAIN_3P3 */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_MAX (0x00000007U)

/* ATEST_POK_VDDS_DDRIO */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_MASK     (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_MAX      (0x00000007U)

/* PVT0_TEST_REG_OBS */

#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMO_MASK               (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMO_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMO_MAX                (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMG_MASK               (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMG_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_TRIMG_MAX                (0x0000001FU)

/* PVT1_TEST_REG_OBS */

#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMO_MASK               (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMO_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMO_MAX                (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMG_MASK               (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMG_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_TRIMG_MAX                (0x0000001FU)

/* PVT2_TEST_REG_OBS */

#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMO_MASK               (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMO_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMO_MAX                (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMG_MASK               (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMG_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_TRIMG_MAX                (0x0000001FU)

/* VTM_TEST_REG_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMO_MASK               (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMO_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMO_MAX                (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMG_MASK               (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMG_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_TRIMG_MAX                (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMO_MASK          (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMO_SHIFT         (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMO_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMG_MASK          (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMG_SHIFT         (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_POST_TRIMG_MAX           (0x00000001U)

/* GP_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_GP_TEST_MASK                   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_GP_TEST_SHIFT                  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_GP_TEST_MAX                    (0xFFFFFFFFU)

/* SDIO_TEST_REG_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_MASK      (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_SHIFT     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_MAX       (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_MASK      (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_SHIFT     (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_MAX       (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_MASK      (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_MAX       (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_POST_TRIM_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_POST_TRIM_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_POST_TRIM_MAX           (0x00000001U)

/* SDIO_TEST_REG_OBS */

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_MASK       (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_MAX        (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_MASK       (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_SHIFT      (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_MAX        (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_MASK       (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_MAX        (0x0000001FU)

/* SA3_UL_TRNG_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TESTOSC_MASK          (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TESTOSC_SHIFT         (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TESTOSC_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_MASK      (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_SHIFT     (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_MAX       (0x0000001FU)

/* SA3_UL_TRNG_TEST_OBS */

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_MASK      (0x007F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_MAX       (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_FSM_STATE_MASK        (0x07000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_FSM_STATE_SHIFT       (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_FSM_STATE_MAX         (0x00000007U)

/* SPARE_RW_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_SPARE_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_SPARE_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_SPARE_MAX                (0xFFFFFFFFU)

/* SPARE_RO_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_SPARE_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_SPARE_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_SPARE_MAX                (0xFFFFFFFFU)

/* PBIST_EN_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_MASK      (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_SHIFT     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_MASK      (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_SHIFT     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_MASK      (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_SHIFT     (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB0_PBIST_EN_MASK       (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB0_PBIST_EN_SHIFT      (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB0_PBIST_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB1_PBIST_EN_MASK       (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB1_PBIST_EN_SHIFT      (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_USB1_PBIST_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_DSS0_PBIST_EN_MASK       (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_DSS0_PBIST_EN_SHIFT      (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_DSS0_PBIST_EN_MAX        (0x00000001U)

/* PBIST_MARGIN_MODE_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_MAX  (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_MAX  (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_MASK     (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_SHIFT    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_MAX      (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_MASK     (0x00007000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_SHIFT    (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_MAX      (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_MASK (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_MAX  (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_MASK  (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_MASK (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_SHIFT (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_MASK (0x04000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_SHIFT (0x0000001AU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_MAX (0x00000001U)

/* PLL0_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL1_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL2_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL5_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL7_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL8_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_CAL_OUT_MASK        (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_CAL_OUT_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_CAL_OUT_MAX         (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_MASK       (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_MAX        (0x0000000FU)

/* PLL12_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_CAL_OUT_MASK       (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_CAL_OUT_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_CAL_OUT_MAX        (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_MASK      (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_MAX       (0x0000000FU)

/* PLL15_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_CAL_OUT_MASK       (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_CAL_OUT_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_CAL_OUT_MAX        (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_MASK      (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_MAX       (0x0000000FU)

/* PLL17_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_CAL_OUT_MASK       (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_CAL_OUT_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_CAL_OUT_MAX        (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_MASK      (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_MAX       (0x0000000FU)

/* MCU_PLL0_CAL_STAT_TEST_REG */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_MASK    (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_SHIFT   (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_MAX     (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_MASK   (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_SHIFT  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_MAX    (0x0000000FU)

/* LOCK4_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK4_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P4_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R1_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R2_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R3_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R4_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R5_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R6_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R7_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R8_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R9_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_READONLY_CLAIMREG_P4_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R10_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_READONLY_CLAIMREG_P4_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R11_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_READONLY_CLAIMREG_P4_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_READONLY_CLAIMREG_P4_R11_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_READONLY_CLAIMREG_P4_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R12_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_READONLY_CLAIMREG_P4_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_READONLY_CLAIMREG_P4_R12_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_READONLY_CLAIMREG_P4_R12_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R13_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_READONLY_CLAIMREG_P4_R13_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_READONLY_CLAIMREG_P4_R13_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_READONLY_CLAIMREG_P4_R13_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R14_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_READONLY_CLAIMREG_P4_R14_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_READONLY_CLAIMREG_P4_R14_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_READONLY_CLAIMREG_P4_R14_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R15_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_READONLY_CLAIMREG_P4_R15_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_READONLY_CLAIMREG_P4_R15_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_READONLY_CLAIMREG_P4_R15_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R16_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_READONLY_CLAIMREG_P4_R16_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_READONLY_CLAIMREG_P4_R16_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_READONLY_CLAIMREG_P4_R16_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R17_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_READONLY_CLAIMREG_P4_R17_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_READONLY_CLAIMREG_P4_R17_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_READONLY_CLAIMREG_P4_R17_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R18_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_READONLY_CLAIMREG_P4_R18_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_READONLY_CLAIMREG_P4_R18_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_READONLY_CLAIMREG_P4_R18_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R19_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_READONLY_CLAIMREG_P4_R19_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_READONLY_CLAIMREG_P4_R19_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_READONLY_CLAIMREG_P4_R19_READONLY_MAX (0xFFFFFFFFU)

/* DV_REG0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_PROXY_DV_REG0_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_PROXY_DV_REG0_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_PROXY_DV_REG0_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_PROXY_DV_REG1_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_PROXY_DV_REG1_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_PROXY_DV_REG1_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_PROXY_DV_REG2_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_PROXY_DV_REG2_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_PROXY_DV_REG2_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_PROXY_DV_REG3_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_PROXY_DV_REG3_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_PROXY_DV_REG3_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG4_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_PROXY_DV_REG4_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_PROXY_DV_REG4_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG4_PROXY_DV_REG4_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG5_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_PROXY_DV_REG5_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_PROXY_DV_REG5_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG5_PROXY_DV_REG5_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG6_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_PROXY_DV_REG6_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_PROXY_DV_REG6_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG6_PROXY_DV_REG6_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG7_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_PROXY_DV_REG7_BIT_PROXY_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_PROXY_DV_REG7_BIT_PROXY_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG7_PROXY_DV_REG7_BIT_PROXY_MAX        (0xFFFFFFFFU)

/* DV_REG0_SET_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_PROXY_DV_REG0_SET_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_PROXY_DV_REG0_SET_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_SET_PROXY_DV_REG0_SET_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG1_SET_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_PROXY_DV_REG1_SET_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_PROXY_DV_REG1_SET_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_SET_PROXY_DV_REG1_SET_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG2_SET_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_PROXY_DV_REG2_SET_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_PROXY_DV_REG2_SET_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_SET_PROXY_DV_REG2_SET_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG3_SET_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_PROXY_DV_REG3_SET_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_PROXY_DV_REG3_SET_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_SET_PROXY_DV_REG3_SET_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG0_CLR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_PROXY_DV_REG0_CLR_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_PROXY_DV_REG0_CLR_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG0_CLR_PROXY_DV_REG0_CLR_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG1_CLR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_PROXY_DV_REG1_CLR_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_PROXY_DV_REG1_CLR_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG1_CLR_PROXY_DV_REG1_CLR_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG2_CLR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_PROXY_DV_REG2_CLR_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_PROXY_DV_REG2_CLR_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG2_CLR_PROXY_DV_REG2_CLR_BIT_PROXY_MAX (0xFFFFFFFFU)

/* DV_REG3_CLR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_PROXY_DV_REG3_CLR_BIT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_PROXY_DV_REG3_CLR_BIT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_DV_REG3_CLR_PROXY_DV_REG3_CLR_BIT_PROXY_MAX (0xFFFFFFFFU)

/* LED_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_LED_MODE_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_LED_MODE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_LED_MODE_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_CONTROL_PROXY_MASK (0xFFFFFFFEU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_CONTROL_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_CTRL_PROXY_LED_CTRL_CONTROL_PROXY_MAX  (0x7FFFFFFFU)

/* LED_ENABLE_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_PROXY_LED_ENABLE_ENABLE_KEY_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_PROXY_LED_ENABLE_ENABLE_KEY_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_ENABLE_PROXY_LED_ENABLE_ENABLE_KEY_PROXY_MAX (0xFFFFFFFFU)

/* LED_MCU_PLL_STAT_EN_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_PROXY_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_PROXY_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MCU_PLL_STAT_EN_PROXY_LED_MCU_PLL_STAT_EN_MCU_PLL0_EN_PROXY_MAX (0x00000001U)

/* LED_MAIN_PLL_STAT_EN_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL0_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL1_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL2_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_PROXY_MASK (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_PROXY_SHIFT (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL5_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL7_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL8_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_PROXY_MASK (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL12_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL15_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_PROXY_MASK (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_PROXY_SHIFT (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_MAIN_PLL_STAT_EN_PROXY_LED_MAIN_PLL_STAT_EN_MAIN_PLL17_EN_PROXY_MAX (0x00000001U)

/* LED_PGD_STAT_EN_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_PROXY_LED_PGD_STAT_EN_VDD_CORE_EN_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_PROXY_LED_PGD_STAT_EN_VDD_CORE_EN_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_PGD_STAT_EN_PROXY_LED_PGD_STAT_EN_VDD_CORE_EN_PROXY_MAX (0x00000001U)

/* LED_EFC_STAT_EN_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_PROXY_LED_EFC_STAT_EN_EFC_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_PROXY_LED_EFC_STAT_EN_EFC_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_EFC_STAT_EN_PROXY_LED_EFC_STAT_EN_EFC_EN_PROXY_MAX (0x00000001U)

/* LED_STATUS_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_STATUS_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_STATUS_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_STATUS_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_EN_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_EN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_LED_STATUS_CTRL_PROXY_LED_STATUS_CTRL_STICKY_EN_PROXY_MAX (0x00000001U)

/* SIM_CFG0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_PROXY_SIM_CFG0_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_PROXY_SIM_CFG0_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG0_PROXY_SIM_CFG0_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_PROXY_SIM_CFG1_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_PROXY_SIM_CFG1_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG1_PROXY_SIM_CFG1_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_PROXY_SIM_CFG2_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_PROXY_SIM_CFG2_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG2_PROXY_SIM_CFG2_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_PROXY_SIM_CFG3_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_PROXY_SIM_CFG3_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG3_PROXY_SIM_CFG3_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG4_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_PROXY_SIM_CFG4_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_PROXY_SIM_CFG4_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG4_PROXY_SIM_CFG4_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG5_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_PROXY_SIM_CFG5_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_PROXY_SIM_CFG5_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG5_PROXY_SIM_CFG5_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG6_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_PROXY_SIM_CFG6_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_PROXY_SIM_CFG6_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG6_PROXY_SIM_CFG6_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* SIM_CFG7_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_PROXY_SIM_CFG7_BIT_PROXY_MASK     (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_PROXY_SIM_CFG7_BIT_PROXY_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SIM_CFG7_PROXY_SIM_CFG7_BIT_PROXY_MAX      (0xFFFFFFFFU)

/* MCU_PLL_TEST_CLKSEL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_PROXY_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_PROXY_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL_TEST_CLKSEL_PROXY_MCU_PLL_TEST_CLKSEL_CLK_SEL_PLL0_PROXY_MAX (0x00000001U)

/* NON_AVS_MRGN_MODE0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_PROXY_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_PROXY_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE0_PROXY_NON_AVS_MRGN_MODE0_HS2PARF_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_PROXY_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_PROXY_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE1_PROXY_NON_AVS_MRGN_MODE1_HDDP_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE2_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_PROXY_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_PROXY_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE2_PROXY_NON_AVS_MRGN_MODE2_EHDSP_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_PROXY_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_PROXY_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE3_PROXY_NON_AVS_MRGN_MODE3_HD2PRF_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE4_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_PROXY_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_PROXY_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE4_PROXY_NON_AVS_MRGN_MODE4_UHD2PRF_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE5_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_PROXY_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_PROXY_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE5_PROXY_NON_AVS_MRGN_MODE5_ROM_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE6_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_PROXY_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_PROXY_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE6_PROXY_NON_AVS_MRGN_MODE6_HDSP_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE7_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_PROXY_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_PROXY_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE7_PROXY_NON_AVS_MRGN_MODE7_HSSP_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE8_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_PROXY_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_PROXY_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE8_PROXY_NON_AVS_MRGN_MODE8_HD1PRF_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* NON_AVS_MRGN_MODE9_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_PROXY_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_PROXY_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_NON_AVS_MRGN_MODE9_PROXY_NON_AVS_MRGN_MODE9_HS1PRF_MEM_MRGN_ASST_PROXY_MAX (0x00000FFFU)

/* ATEST_RCOSC_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_TEST_PROXY_MASK (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_TEST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_TEST_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_EN_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_EN_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_RCOSC_PROXY_ATEST_RCOSC_ATEST_EN_PROXY_MAX (0x00000001U)

/* ATEST_HFOSC_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_TEST_EN_C_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_TEST_EN_C_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_TEST_EN_C_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_FREQ_RANGE_C_PROXY_MASK (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_FREQ_RANGE_C_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_HFOSC_PROXY_ATEST_HFOSC_FREQ_RANGE_C_PROXY_MAX (0x00000003U)

/* ATEST_LFOSC_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_TEST_EN_C_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_TEST_EN_C_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_TEST_EN_C_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_FREQ_RANGE_C_PROXY_MASK (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_FREQ_RANGE_C_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_LFOSC_PROXY_ATEST_LFOSC_FREQ_RANGE_C_PROXY_MAX (0x00000003U)

/* ATEST_POR_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATEST_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATEST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATEST_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATESTIN_PROXY_MASK (0x00000700U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATESTIN_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SEL_ATESTIN_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_CLKIN_TST_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_CLKIN_TST_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_CLKIN_TST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SELCLKIN_TST_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SELCLKIN_TST_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POR_PROXY_ATEST_POR_SELCLKIN_TST_PROXY_MAX (0x00000001U)

/* ATEST_POK_VDDA_MCU_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_PROXY_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_PROXY_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_UV_CTRL_PROXY_ATEST_POK_VDDA_MCU_UV_CTRL_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDA_MCU_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_PROXY_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_PROXY_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_MCU_OV_CTRL_PROXY_ATEST_POK_VDDA_MCU_OV_CTRL_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDD_CORE_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_PROXY_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_PROXY_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_UV_CTRL_PROXY_ATEST_POK_VDD_CORE_UV_CTRL_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDA_PMIC_IN_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_PROXY_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_PROXY_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDA_PMIC_IN_PROXY_ATEST_POK_VDDA_PMIC_IN_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDD_CORE_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_PROXY_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_PROXY_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDD_CORE_OV_CTRL_PROXY_ATEST_POK_VDD_CORE_OV_CTRL_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDR_CORE_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_PROXY_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_PROXY_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDR_CORE_PROXY_ATEST_POK_VDDR_CORE_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VMON_CAP_MCU_GENERAL_PROXY_ATEST_POK_VMON_CAP_MCU_GENERAL_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDSHV_MAIN_1P8_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_PROXY_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_PROXY_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_1P8_PROXY_ATEST_POK_VDDSHV_MAIN_1P8_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDSHV_MAIN_3P3_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_PROXY_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_PROXY_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDSHV_MAIN_3P3_PROXY_ATEST_POK_VDDSHV_MAIN_3P3_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* ATEST_POK_VDDS_DDRIO_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_PROXY_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_PROXY_MASK (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_PROXY_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ATEST_POK_VDDS_DDRIO_PROXY_ATEST_POK_VDDS_DDRIO_POK_ATMUXSEL_PROXY_MAX (0x00000007U)

/* PVT0_TEST_REG_OBS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMO_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMO_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMO_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMG_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMG_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT0_TEST_REG_OBS_PROXY_PVT0_TEST_REG_OBS_TRIMG_PROXY_MAX (0x0000001FU)

/* PVT1_TEST_REG_OBS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMO_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMO_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMO_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMG_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMG_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT1_TEST_REG_OBS_PROXY_PVT1_TEST_REG_OBS_TRIMG_PROXY_MAX (0x0000001FU)

/* PVT2_TEST_REG_OBS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMO_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMO_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMO_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMG_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMG_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PVT2_TEST_REG_OBS_PROXY_PVT2_TEST_REG_OBS_TRIMG_PROXY_MAX (0x0000001FU)

/* VTM_TEST_REG_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMO_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMO_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMO_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMG_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMG_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_TRIMG_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMO_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMO_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMO_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMG_PROXY_MASK (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMG_PROXY_SHIFT (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_VTM_TEST_REG_CTRL_PROXY_VTM_TEST_REG_CTRL_POST_TRIMG_PROXY_MAX (0x00000001U)

/* GP_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_PROXY_GP_TEST_REG_GP_TEST_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_PROXY_GP_TEST_REG_GP_TEST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_GP_TEST_REG_PROXY_GP_TEST_REG_GP_TEST_PROXY_MAX (0xFFFFFFFFU)

/* SDIO_TEST_REG_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_PROXY_MASK (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO0_DRV_STR_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO1_DRV_STR_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_PROXY_MASK (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_SDIO2_DRV_STR_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_POST_TRIM_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_POST_TRIM_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_CTRL_PROXY_SDIO_TEST_REG_CTRL_POST_TRIM_PROXY_MAX (0x00000001U)

/* SDIO_TEST_REG_OBS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_PROXY_MASK (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO0_DRV_STR_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO1_DRV_STR_PROXY_MAX (0x0000001FU)

#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_PROXY_MASK (0x001F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SDIO_TEST_REG_OBS_PROXY_SDIO_TEST_REG_OBS_SDIO2_DRV_STR_PROXY_MAX (0x0000001FU)

/* SA3_UL_TRNG_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TESTOSC_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TESTOSC_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TESTOSC_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_PROXY_MASK (0x00001F00U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_REG_PROXY_SA3_UL_TRNG_TEST_REG_TST_FRO_SEL_PROXY_MAX (0x0000001FU)

/* SA3_UL_TRNG_TEST_OBS_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_PROXY_MASK (0x007F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_PPROC_STATE_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_FSM_STATE_PROXY_MASK (0x07000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_FSM_STATE_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_SA3_UL_TRNG_TEST_OBS_PROXY_SA3_UL_TRNG_TEST_OBS_FSM_STATE_PROXY_MAX (0x00000007U)

/* SPARE_RW_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_PROXY_SPARE_RW_TEST_REG_SPARE_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_PROXY_SPARE_RW_TEST_REG_SPARE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RW_TEST_REG_PROXY_SPARE_RW_TEST_REG_SPARE_PROXY_MAX (0xFFFFFFFFU)

/* SPARE_RO_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_PROXY_SPARE_RO_TEST_REG_SPARE_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_PROXY_SPARE_RO_TEST_REG_SPARE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_SPARE_RO_TEST_REG_PROXY_SPARE_RO_TEST_REG_SPARE_PROXY_MAX (0xFFFFFFFFU)

/* PBIST_EN_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC0_PBIST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC1_PBIST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_EMMC2_PBIST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB0_PBIST_EN_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB0_PBIST_EN_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB0_PBIST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB1_PBIST_EN_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB1_PBIST_EN_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_USB1_PBIST_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_DSS0_PBIST_EN_PROXY_MASK (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_DSS0_PBIST_EN_PROXY_SHIFT (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG_PROXY_PBIST_EN_TEST_REG_DSS0_PBIST_EN_PROXY_MAX (0x00000001U)

/* PBIST_MARGIN_MODE_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_ROM_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_PROXY_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MARGIN_RAM_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_PROXY_MASK (0x00000300U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_RA_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_PROXY_MASK (0x00007000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WA_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_PROXY_MASK (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_WPULSE_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TEST1_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_PROXY_MASK (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_PROXY_SHIFT (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRNM_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_PROXY_MASK (0x04000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_PROXY_SHIFT (0x0000001AU)
#define CSL_MCU_CTRL_MMR_CFG0_PBIST_MARGIN_MODE_CTRL_PROXY_PBIST_MARGIN_MODE_CTRL_DFT_MEM_TESTRWM_PROXY_MAX (0x00000001U)

/* PLL0_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL0_CAL_STAT_TEST_REG_PROXY_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL1_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL1_CAL_STAT_TEST_REG_PROXY_PLL1_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL2_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL2_CAL_STAT_TEST_REG_PROXY_PLL2_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL5_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL5_CAL_STAT_TEST_REG_PROXY_PLL5_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL7_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL7_CAL_STAT_TEST_REG_PROXY_PLL7_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL8_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL8_CAL_STAT_TEST_REG_PROXY_PLL8_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL12_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL12_CAL_STAT_TEST_REG_PROXY_PLL12_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL15_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL15_CAL_STAT_TEST_REG_PROXY_PLL15_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* PLL17_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PLL17_CAL_STAT_TEST_REG_PROXY_PLL17_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* MCU_PLL0_CAL_STAT_TEST_REG_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MASK (0x00000FFFU)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_CAL_OUT_PROXY_MAX (0x00000FFFU)

#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_MCU_PLL0_CAL_STAT_TEST_REG_PROXY_MCU_PLL0_CAL_STAT_TEST_REG_LOCK_CNT_PROXY_MAX (0x0000000FU)

/* LOCK4_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK4_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P4_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R1 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R2 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R3 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R4 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R5 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R6 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R7 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R8 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R9 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R9_CLAIMREG_P4_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R10 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R10_CLAIMREG_P4_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R11 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_CLAIMREG_P4_R11_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_CLAIMREG_P4_R11_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R11_CLAIMREG_P4_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R12 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_CLAIMREG_P4_R12_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_CLAIMREG_P4_R12_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R12_CLAIMREG_P4_R12_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R13 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_CLAIMREG_P4_R13_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_CLAIMREG_P4_R13_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R13_CLAIMREG_P4_R13_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R14 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_CLAIMREG_P4_R14_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_CLAIMREG_P4_R14_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R14_CLAIMREG_P4_R14_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R15 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_CLAIMREG_P4_R15_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_CLAIMREG_P4_R15_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R15_CLAIMREG_P4_R15_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R16 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_CLAIMREG_P4_R16_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_CLAIMREG_P4_R16_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R16_CLAIMREG_P4_R16_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R17 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_CLAIMREG_P4_R17_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_CLAIMREG_P4_R17_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R17_CLAIMREG_P4_R17_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R18 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_CLAIMREG_P4_R18_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_CLAIMREG_P4_R18_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R18_CLAIMREG_P4_R18_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P4_R19 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_CLAIMREG_P4_R19_MASK       (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_CLAIMREG_P4_R19_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P4_R19_CLAIMREG_P4_R19_MAX        (0xFFFFFFFFU)

/* POR_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_MASK_HHV_MASK                     (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_MASK_HHV_SHIFT                    (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_MASK_HHV_MAX                      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_TRIM_SEL_MASK                     (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_TRIM_SEL_SHIFT                    (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_TRIM_SEL_MAX                      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD0_MASK                        (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD0_SHIFT                       (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD0_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD1_MASK                        (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD1_SHIFT                       (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD1_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD2_MASK                        (0x00040000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD2_SHIFT                       (0x00000012U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD2_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD3_MASK                        (0x00080000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD3_SHIFT                       (0x00000013U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD3_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD4_MASK                        (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD4_SHIFT                       (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD4_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD5_MASK                        (0x00200000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD5_SHIFT                       (0x00000015U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD5_MAX                         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET0_MASK                    (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET0_SHIFT                   (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET0_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET1_MASK                    (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET1_SHIFT                   (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET1_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET2_MASK                    (0x04000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET2_SHIFT                   (0x0000001AU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET2_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET3_MASK                    (0x08000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET3_SHIFT                   (0x0000001BU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET3_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET4_MASK                    (0x10000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET4_SHIFT                   (0x0000001CU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET4_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET5_MASK                    (0x20000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET5_SHIFT                   (0x0000001DU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET5_MAX                     (0x00000001U)

/* POR_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_SOC_POR_MASK                      (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_SOC_POR_SHIFT                     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_SOC_POR_MAX                       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_BGOK_MASK                         (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_BGOK_SHIFT                        (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_BGOK_MAX                          (0x00000001U)

/* POR_BANDGAP_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPC_MASK                (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPC_SHIFT               (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPC_MAX                 (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPV_MASK                (0x0000FF00U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPV_SHIFT               (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPV_MAX                 (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPI_MASK                (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPI_SHIFT               (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_BGAPI_MAX                 (0x0000000FU)

/* POK_VDDA_MCU_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_POK_TRIM_MASK         (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_POK_TRIM_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_POK_TRIM_MAX          (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_MASK    (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_SHIFT   (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_HYST_EN_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_HYST_EN_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_HYST_EN_MAX           (0x00000001U)

/* POK_VDDA_MCU_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_POK_TRIM_MASK         (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_POK_TRIM_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_POK_TRIM_MAX          (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_MASK    (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_SHIFT   (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_HYST_EN_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_HYST_EN_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_HYST_EN_MAX           (0x00000001U)

/* POK_VDD_CORE_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_POK_TRIM_MASK         (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_POK_TRIM_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_POK_TRIM_MAX          (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_MASK    (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_SHIFT   (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_HYST_EN_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_HYST_EN_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_HYST_EN_MAX           (0x00000001U)

/* POK_VDD_CORE_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_POK_TRIM_MASK         (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_POK_TRIM_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_POK_TRIM_MAX          (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_MASK    (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_SHIFT   (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_HYST_EN_MASK          (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_HYST_EN_SHIFT         (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_HYST_EN_MAX           (0x00000001U)

/* POK_VDDR_CORE_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_POK_TRIM_MASK        (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_POK_TRIM_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_POK_TRIM_MAX         (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_MASK   (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_SHIFT  (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_HYST_EN_MASK         (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_HYST_EN_SHIFT        (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_HYST_EN_MAX          (0x00000001U)

/* POK_VDDR_CORE_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_POK_TRIM_MASK        (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_POK_TRIM_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_POK_TRIM_MAX         (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_MASK   (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_SHIFT  (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_HYST_EN_MASK         (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_HYST_EN_SHIFT        (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_HYST_EN_MAX          (0x00000001U)

/* POK_VMON_CAP_MCU_GENERAL_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_MAX (0x00000001U)

/* POK_VMON_CAP_MCU_GENERAL_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_MAX (0x00000001U)

/* POK_VDDSHV_MAIN_1P8_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_MASK  (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_MAX   (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_MASK   (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_SHIFT  (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_MAX    (0x00000001U)

/* POK_VDDSHV_MAIN_1P8_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_MASK  (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_MAX   (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_MASK   (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_SHIFT  (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_MAX    (0x00000001U)

/* POK_VDDSHV_MAIN_3P3_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_MASK  (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_MAX   (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_MASK   (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_SHIFT  (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_MAX    (0x00000001U)

/* POK_VDDSHV_MAIN_3P3_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_MASK  (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_MAX   (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_MASK   (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_SHIFT  (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_MAX    (0x00000001U)

/* POK_VDDS_DDRIO_UV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_MASK       (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_MAX        (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_MASK  (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_MASK        (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_SHIFT       (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_MAX         (0x00000001U)

/* POK_VDDS_DDRIO_OV_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_MASK       (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_SHIFT      (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_MAX        (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_MASK  (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_MASK        (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_SHIFT       (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_MAX         (0x00000001U)

/* POK_VDDA_PMIC_IN_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_MASK   (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_SHIFT  (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_HYST_EN_MASK         (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_HYST_EN_SHIFT        (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_HYST_EN_MAX          (0x00000001U)

/* RST_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_MASK              (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_MAX               (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_MASK                  (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_SHIFT                 (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_MAX                   (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MCU_WARMRST_MASK               (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MCU_WARMRST_SHIFT              (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SW_MCU_WARMRST_MAX                (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_MASK          (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_SHIFT         (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_MASK       (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_SHIFT      (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z_MASK         (0x00040000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z_SHIFT        (0x00000012U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_MCU_RESET_ISO_DONE_Z_MAX          (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_DM_WDT_RST_EN_Z_MASK              (0x00400000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_DM_WDT_RST_EN_Z_SHIFT             (0x00000016U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_DM_WDT_RST_EN_Z_MAX               (0x00000001U)

/* RST_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_MAIN_RESETSTATZ_MASK              (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_MAIN_RESETSTATZ_SHIFT             (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_MAIN_RESETSTATZ_MAX               (0x00000001U)

/* RST_SRC */

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_MASK                 (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_SHIFT                (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_MAX                  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_MASK                (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_SHIFT               (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_MAX                 (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_MASK                   (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_SHIFT                  (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_MAX                    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_MASK                     (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_SHIFT                    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_MAX                      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_MASK                  (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_SHIFT                 (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_MASK                  (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_SHIFT                 (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_MASK                (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_SHIFT               (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_MAX                 (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_MASK      (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_SHIFT     (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_MASK     (0x00200000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_SHIFT    (0x00000015U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_MASK                    (0x00400000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_SHIFT                   (0x00000016U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_MAX                     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DS_MAIN_PORZ_MASK                  (0x00800000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DS_MAIN_PORZ_SHIFT                 (0x00000017U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_DS_MAIN_PORZ_MAX                   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_MASK          (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_SHIFT         (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_MASK         (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_SHIFT        (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_MAX          (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_MASK                (0x40000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_SHIFT               (0x0000001EU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_MAX                 (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_MASK                 (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_SHIFT                (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_MAX                  (0x00000001U)

/* RST_MAGIC_WORD */

#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_MAX          (0xFFFFFFFFU)

/* ISO_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_RST_ISO_EN_MASK               (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_RST_ISO_EN_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_RST_ISO_EN_MAX                (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_DBG_ISO_EN_MASK               (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_DBG_ISO_EN_SHIFT              (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_MCU_DBG_ISO_EN_MAX                (0x00000001U)

/* VDD_CORE_GLDTC_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_MASK     (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_MAX      (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_MASK     (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_SHIFT    (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_MAX      (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_MASK     (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_SHIFT    (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_MAX      (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_RSTB_MASK              (0x40000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_RSTB_SHIFT             (0x0000001EU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_RSTB_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PWDB_MASK              (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PWDB_SHIFT             (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PWDB_MAX               (0x00000001U)

/* VDD_CORE_GLDTC_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_MASK   (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_MASK    (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_SHIFT   (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_MAX     (0x00000001U)

/* PRG_PP_0_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_MASK      (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_SHIFT     (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_MASK      (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_SHIFT     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_MAX       (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_MASK       (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_SHIFT      (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_MASK       (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_SHIFT      (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_MASK  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_EN_SEL_MASK              (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_EN_SEL_SHIFT             (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_POK_EN_SEL_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_DEGLITCH_SEL_MASK            (0x00030000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_DEGLITCH_SEL_SHIFT           (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_DEGLITCH_SEL_MAX             (0x00000003U)

/* PRG_PP_0_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_UV_MASK         (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_UV_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_UV_MAX          (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_UV_MASK          (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_UV_SHIFT         (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_UV_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_MASK     (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_SHIFT    (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_OV_MASK         (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_OV_SHIFT        (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDDA_MCU_OV_MAX          (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_OV_MASK          (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_OV_SHIFT         (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_VDD_MCU_OV_MAX           (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_CLR_MASK                 (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_CLR_SHIFT                (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_POK_CLR_MAX                  (0x00000001U)

/* PRG_PP_1_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_MASK        (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_MASK   (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_SHIFT  (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_MASK   (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_SHIFT  (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_MASK  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_MASK  (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_SHIFT (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_MASK       (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_SHIFT      (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_MASK    (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_SHIFT   (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_MAX     (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_MASK (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_SHIFT (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_MASK (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_SHIFT (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_MASK (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_MASK (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_SHIFT (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_MASK   (0x00004000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_SHIFT  (0x0000000EU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_EN_SEL_MASK              (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_EN_SEL_SHIFT             (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_EN_SEL_MAX               (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_DEGLITCH_SEL_MASK            (0x00030000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_DEGLITCH_SEL_SHIFT           (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_DEGLITCH_SEL_MAX             (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_PP_EN_MASK               (0x00080000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_PP_EN_SHIFT              (0x00000013U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_POK_PP_EN_MAX                (0x00000001U)

/* PRG_PP_1_STAT */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_UV_MASK        (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_UV_SHIFT       (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_UV_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_MASK   (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_SHIFT  (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_MASK   (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_SHIFT  (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_MASK  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_MASK  (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_SHIFT (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_MASK       (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_SHIFT      (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_OV_MASK        (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_OV_SHIFT       (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDR_CORE_OV_MAX         (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_MASK   (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_SHIFT  (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_MASK   (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_SHIFT  (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_MASK (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_SHIFT (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_MASK  (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_MASK  (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_SHIFT (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_MAX   (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_MASK       (0x00004000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_SHIFT      (0x0000000EU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_MAX        (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_CLR_MASK                 (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_CLR_SHIFT                (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_POK_CLR_MAX                  (0x00000001U)

/* CLKGATE_CTRL */

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_MASK     (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_SHIFT    (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_MAX      (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCU_CBA_NOGATE_MASK           (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCU_CBA_NOGATE_SHIFT          (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCU_CBA_NOGATE_MAX            (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCUSS_NOGATE_MASK             (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCUSS_NOGATE_SHIFT            (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_MCUSS_NOGATE_MAX              (0x00000001U)

/* LOCK6_KICK0 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK6_KICK1 */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_SHIFT              (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P6_R0_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R1_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R2_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R3_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R4_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R5_READONLY */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MAX (0xFFFFFFFFU)

/* POR_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_MASK_HHV_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_MASK_HHV_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_MASK_HHV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_TRIM_SEL_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_TRIM_SEL_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_TRIM_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD0_PROXY_MASK   (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD0_PROXY_SHIFT  (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD0_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD1_PROXY_MASK   (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD1_PROXY_SHIFT  (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD1_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD2_PROXY_MASK   (0x00040000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD2_PROXY_SHIFT  (0x00000012U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD2_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD3_PROXY_MASK   (0x00080000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD3_PROXY_SHIFT  (0x00000013U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD3_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD4_PROXY_MASK   (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD4_PROXY_SHIFT  (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD4_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD5_PROXY_MASK   (0x00200000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD5_PROXY_SHIFT  (0x00000015U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD5_PROXY_MAX    (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET0_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET0_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET0_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET1_PROXY_MASK (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET1_PROXY_SHIFT (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET1_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET2_PROXY_MASK (0x04000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET2_PROXY_SHIFT (0x0000001AU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET2_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET3_PROXY_MASK (0x08000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET3_PROXY_SHIFT (0x0000001BU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET3_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET4_PROXY_MASK (0x10000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET4_PROXY_SHIFT (0x0000001CU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET4_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET5_PROXY_MASK (0x20000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET5_PROXY_SHIFT (0x0000001DU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_CTRL_PROXY_POR_CTRL_OVRD_SET5_PROXY_MAX (0x00000001U)

/* POR_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_SOC_POR_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_SOC_POR_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_SOC_POR_PROXY_MAX  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_BGOK_PROXY_MASK    (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_BGOK_PROXY_SHIFT   (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_STAT_PROXY_POR_STAT_BGOK_PROXY_MAX     (0x00000001U)

/* POR_BANDGAP_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPC_PROXY_MASK (0x000000FFU)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPC_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPC_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPV_PROXY_MASK (0x0000FF00U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPV_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPV_PROXY_MAX (0x000000FFU)

#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPI_PROXY_MASK (0x000F0000U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPI_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_POR_BANDGAP_CTRL_PROXY_POR_BANDGAP_CTRL_BGAPI_PROXY_MAX (0x0000000FU)

/* POK_VDDA_MCU_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_UV_CTRL_PROXY_POK_VDDA_MCU_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDA_MCU_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_MCU_OV_CTRL_PROXY_POK_VDDA_MCU_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDD_CORE_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_PROXY_POK_VDD_CORE_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDD_CORE_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_PROXY_POK_VDD_CORE_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDR_CORE_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_PROXY_POK_VDDR_CORE_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDR_CORE_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_PROXY_POK_VDDR_CORE_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_PROXY_POK_VMON_CAP_MCU_GENERAL_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_UV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_1P8_OV_CTRL_PROXY_POK_VDDSHV_MAIN_1P8_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_UV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDSHV_MAIN_3P3_OV_CTRL_PROXY_POK_VDDSHV_MAIN_3P3_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDS_DDRIO_UV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_UV_CTRL_PROXY_POK_VDDS_DDRIO_UV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDS_DDRIO_OV_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_PROXY_MASK (0x0000007FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_POK_TRIM_PROXY_MAX (0x0000007FU)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00000080U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x00000007U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDS_DDRIO_OV_CTRL_PROXY_POK_VDDS_DDRIO_OV_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* POK_VDDA_PMIC_IN_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_HYST_EN_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_HYST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_PROXY_POK_VDDA_PMIC_IN_CTRL_HYST_EN_PROXY_MAX (0x00000001U)

/* RST_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_MASK (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_MASK (0x000000F0U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MCU_WARMRST_PROXY_MASK (0x00000F00U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MCU_WARMRST_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MCU_WARMRST_PROXY_MAX (0x0000000FU)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_PROXY_MASK (0x00020000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_PROXY_SHIFT (0x00000011U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_ESM_ERROR_RST_EN_Z_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_RESET_ISO_DONE_Z_PROXY_MASK (0x00040000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_RESET_ISO_DONE_Z_PROXY_SHIFT (0x00000012U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MCU_RESET_ISO_DONE_Z_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_DM_WDT_RST_EN_Z_PROXY_MASK (0x00400000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_DM_WDT_RST_EN_Z_PROXY_SHIFT (0x00000016U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_DM_WDT_RST_EN_Z_PROXY_MAX (0x00000001U)

/* RST_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MAIN_RESETSTATZ_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MAIN_RESETSTATZ_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MAIN_RESETSTATZ_PROXY_MAX (0x00000001U)

/* RST_SRC_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_MAX  (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_MASK (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_MASK (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_SHIFT (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_MASK (0x00010000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_MASK (0x00100000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_SHIFT (0x00000014U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_MASK (0x00200000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_SHIFT (0x00000015U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_MASK (0x00400000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_SHIFT (0x00000016U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DS_MAIN_PORZ_PROXY_MASK (0x00800000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DS_MAIN_PORZ_PROXY_SHIFT (0x00000017U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DS_MAIN_PORZ_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_MASK (0x01000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_SHIFT (0x00000018U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_MASK (0x02000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_SHIFT (0x00000019U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_MASK (0x40000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_SHIFT (0x0000001EU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_MAX (0x00000001U)

/* RST_MAGIC_WORD_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_MASK (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_MAX (0xFFFFFFFFU)

/* ISO_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_RST_ISO_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_RST_ISO_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_RST_ISO_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_DBG_ISO_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_DBG_ISO_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_ISO_CTRL_PROXY_ISO_CTRL_MCU_DBG_ISO_EN_PROXY_MAX (0x00000001U)

/* VDD_CORE_GLDTC_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_PROXY_MASK (0x0000003FU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_LO_SEL_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_PROXY_MASK (0x00003F00U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_THRESH_HI_SEL_PROXY_MAX (0x0000003FU)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_PROXY_MASK (0x00070000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_LP_FILTER_SEL_PROXY_MAX (0x00000007U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_RSTB_PROXY_MASK (0x40000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_RSTB_PROXY_SHIFT (0x0000001EU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_RSTB_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_PWDB_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_PWDB_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_CTRL_PROXY_VDD_CORE_GLDTC_CTRL_PWDB_PROXY_MAX (0x00000001U)

/* VDD_CORE_GLDTC_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_VDD_CORE_GLDTC_STAT_PROXY_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_PROXY_MAX (0x00000001U)

/* PRG_PP_0_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_UV_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_MCU_OV_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_UV_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDD_MCU_OV_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_VDDA_PMIC_IN_UV_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_EN_SEL_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_EN_SEL_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_POK_EN_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_DEGLITCH_SEL_PROXY_MASK (0x00030000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_DEGLITCH_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_CTRL_PROXY_PRG_PP_0_CTRL_DEGLITCH_SEL_PROXY_MAX (0x00000003U)

/* PRG_PP_0_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_UV_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_UV_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_UV_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_UV_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_PMIC_IN_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_OV_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_OV_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDDA_MCU_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_OV_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_OV_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_VDD_MCU_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_CLR_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_CLR_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_0_STAT_PROXY_PRG_PP_0_STAT_POK_CLR_PROXY_MAX (0x00000001U)

/* PRG_PP_1_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_PROXY_MASK (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_PROXY_SHIFT (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_PROXY_MASK (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_PROXY_SHIFT (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_EN_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDR_CORE_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_1P8_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_PROXY_MASK (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_PROXY_SHIFT (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MCU_3P3_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_PROXY_MASK (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_PROXY_SHIFT (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VMON_CAP_MCU_GENERAL_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_PROXY_MASK (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_1P8_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_PROXY_MASK (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_PROXY_SHIFT (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDSHV_MAIN_3P3_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_PROXY_MASK (0x00004000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_PROXY_SHIFT (0x0000000EU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_VDDS_DDRIO_OV_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_EN_SEL_PROXY_MASK (0x00008000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_EN_SEL_PROXY_SHIFT (0x0000000FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_EN_SEL_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_DEGLITCH_SEL_PROXY_MASK (0x00030000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_DEGLITCH_SEL_PROXY_SHIFT (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_DEGLITCH_SEL_PROXY_MAX (0x00000003U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_PP_EN_PROXY_MASK (0x00080000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_PP_EN_PROXY_SHIFT (0x00000013U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_CTRL_PROXY_PRG_PP_1_CTRL_POK_PP_EN_PROXY_MAX (0x00000001U)

/* PRG_PP_1_STAT_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_UV_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_UV_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_PROXY_MASK (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_PROXY_SHIFT (0x00000003U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_PROXY_MASK (0x00000010U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_PROXY_SHIFT (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_PROXY_MASK (0x00000020U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_PROXY_SHIFT (0x00000005U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_PROXY_MASK (0x00000040U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_PROXY_SHIFT (0x00000006U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_UV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_OV_PROXY_MASK (0x00000100U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_OV_PROXY_SHIFT (0x00000008U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDR_CORE_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_PROXY_MASK (0x00000200U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_PROXY_SHIFT (0x00000009U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_1P8_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_PROXY_MASK (0x00000400U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_PROXY_SHIFT (0x0000000AU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MCU_3P3_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_PROXY_MASK (0x00000800U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_PROXY_SHIFT (0x0000000BU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VMON_CAP_MCU_GENERAL_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_PROXY_MASK (0x00001000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_PROXY_SHIFT (0x0000000CU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_1P8_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_PROXY_MASK (0x00002000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_PROXY_SHIFT (0x0000000DU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDSHV_MAIN_3P3_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_PROXY_MASK (0x00004000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_PROXY_SHIFT (0x0000000EU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_VDDS_DDRIO_OV_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_CLR_PROXY_MASK (0x80000000U)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_CLR_PROXY_SHIFT (0x0000001FU)
#define CSL_MCU_CTRL_MMR_CFG0_PRG_PP_1_STAT_PROXY_PRG_PP_1_STAT_POK_CLR_PROXY_MAX (0x00000001U)

/* CLKGATE_CTRL_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_PROXY_MASK (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_PROXY_SHIFT (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_WKUP_SAFE_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCU_CBA_NOGATE_PROXY_MASK (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCU_CBA_NOGATE_PROXY_SHIFT (0x00000001U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCU_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCUSS_NOGATE_PROXY_MASK (0x00000004U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCUSS_NOGATE_PROXY_SHIFT (0x00000002U)
#define CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL_PROXY_CLKGATE_CTRL_MCUSS_NOGATE_PROXY_MAX (0x00000001U)

/* LOCK6_KICK0_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK6_KICK1_PROXY */

#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P6_R0 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R1 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R2 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R3 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R4 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R5 */

#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MASK         (0xFFFFFFFFU)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_SHIFT        (0x00000000U)
#define CSL_MCU_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MAX          (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif
