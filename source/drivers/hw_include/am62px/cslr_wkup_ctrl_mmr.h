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
 *  Name        : cslr_wkup_ctrl_mmr.h
*/
#ifndef CSLR_WKUP_CTRL_MMR_H_
#define CSLR_WKUP_CTRL_MMR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG0_REGS_BASE                                  (0x00000000U)


/**************************************************************************
* Hardware Region  : MMRs in region 0
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* PID register */
    volatile uint8_t  Resv_8[4];
    volatile uint32_t MMR_CFG1;
    volatile uint8_t  Resv_20[8];
    volatile uint32_t JTAGID;
    volatile uint32_t JTAG_USER_ID;
    volatile uint8_t  Resv_48[20];
    volatile uint32_t MAIN_DEVSTAT;
    volatile uint32_t MAIN_BOOTCFG;
    volatile uint8_t  Resv_68[12];
    volatile uint32_t BOOT_PROGRESS;
    volatile uint8_t  Resv_96[24];
    volatile uint32_t DEVICE_FEATURE0;
    volatile uint32_t DEVICE_FEATURE1;
    volatile uint32_t DEVICE_FEATURE2;
    volatile uint32_t DEVICE_FEATURE3;
    volatile uint8_t  Resv_120[8];
    volatile uint32_t DEVICE_FEATURE6;
    volatile uint8_t  Resv_512[388];
    volatile uint32_t MAC_ID0;
    volatile uint32_t MAC_ID1;
    volatile uint8_t  Resv_528[8];
    volatile uint32_t PCI_DEVICE_ID0;
    volatile uint32_t PCI_DEVICE_ID1;
    volatile uint8_t  Resv_544[8];
    volatile uint32_t USB_DEVICE_ID0;
    volatile uint32_t USB_DEVICE_ID1;
    volatile uint8_t  Resv_560[8];
    volatile uint32_t GP_SW0;
    volatile uint32_t GP_SW1;
    volatile uint32_t GP_SW2;
    volatile uint32_t GP_SW3;
    volatile uint8_t  Resv_624[48];
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
    volatile uint32_t CLAIMREG_P0_R6_READONLY;   /* Claim bits for Partition 0 */
    volatile uint8_t  Resv_8192[3812];
    volatile uint32_t PID_PROXY;                 /* PID register */
    volatile uint8_t  Resv_8200[4];
    volatile uint32_t MMR_CFG1_PROXY;
    volatile uint8_t  Resv_8212[8];
    volatile uint32_t JTAGID_PROXY;
    volatile uint32_t JTAG_USER_ID_PROXY;
    volatile uint8_t  Resv_8240[20];
    volatile uint32_t MAIN_DEVSTAT_PROXY;
    volatile uint32_t MAIN_BOOTCFG_PROXY;
    volatile uint8_t  Resv_8260[12];
    volatile uint32_t BOOT_PROGRESS_PROXY;
    volatile uint8_t  Resv_8288[24];
    volatile uint32_t DEVICE_FEATURE0_PROXY;
    volatile uint32_t DEVICE_FEATURE1_PROXY;
    volatile uint32_t DEVICE_FEATURE2_PROXY;
    volatile uint32_t DEVICE_FEATURE3_PROXY;
    volatile uint8_t  Resv_8312[8];
    volatile uint32_t DEVICE_FEATURE6_PROXY;
    volatile uint8_t  Resv_8704[388];
    volatile uint32_t MAC_ID0_PROXY;
    volatile uint32_t MAC_ID1_PROXY;
    volatile uint8_t  Resv_8720[8];
    volatile uint32_t PCI_DEVICE_ID0_PROXY;
    volatile uint32_t PCI_DEVICE_ID1_PROXY;
    volatile uint8_t  Resv_8736[8];
    volatile uint32_t USB_DEVICE_ID0_PROXY;
    volatile uint32_t USB_DEVICE_ID1_PROXY;
    volatile uint8_t  Resv_8752[8];
    volatile uint32_t GP_SW0_PROXY;
    volatile uint32_t GP_SW1_PROXY;
    volatile uint32_t GP_SW2_PROXY;
    volatile uint32_t GP_SW3_PROXY;
    volatile uint8_t  Resv_8816[48];
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
    volatile uint32_t CLAIMREG_P0_R6;            /* Claim bits for Partition 0 */
    volatile uint8_t  Resv_16392[3820];
    volatile uint32_t USB0_PHY_CTRL;
    volatile uint8_t  Resv_16408[12];
    volatile uint32_t USB1_PHY_CTRL;
    volatile uint8_t  Resv_16496[84];
    volatile uint32_t PCIE0_CTRL;
    volatile uint8_t  Resv_16820[320];
    volatile uint32_t SDIO0_CTRL;
    volatile uint32_t SDIO1_CTRL;
    volatile uint32_t SDIO2_CTRL;
    volatile uint8_t  Resv_16900[68];
    volatile uint32_t WKUP_TIMER1_CTRL;
    volatile uint8_t  Resv_17120[216];
    volatile uint32_t WKUP_I2C0_CTRL;
    volatile uint8_t  Resv_17856[732];
    volatile uint32_t GPU_PWR_REQ;
    volatile uint32_t GPU_PWR_ACK;
    volatile uint8_t  Resv_17936[72];
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
    volatile uint32_t CLAIMREG_P1_R13_READONLY;   /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R14_READONLY;   /* Claim bits for Partition 1 */
    volatile uint8_t  Resv_24584[3788];
    volatile uint32_t USB0_PHY_CTRL_PROXY;
    volatile uint8_t  Resv_24600[12];
    volatile uint32_t USB1_PHY_CTRL_PROXY;
    volatile uint8_t  Resv_24688[84];
    volatile uint32_t PCIE0_CTRL_PROXY;
    volatile uint8_t  Resv_25012[320];
    volatile uint32_t SDIO0_CTRL_PROXY;
    volatile uint32_t SDIO1_CTRL_PROXY;
    volatile uint32_t SDIO2_CTRL_PROXY;
    volatile uint8_t  Resv_25092[68];
    volatile uint32_t WKUP_TIMER1_CTRL_PROXY;
    volatile uint8_t  Resv_25312[216];
    volatile uint32_t WKUP_I2C0_CTRL_PROXY;
    volatile uint8_t  Resv_26048[732];
    volatile uint32_t GPU_PWR_REQ_PROXY;
    volatile uint32_t GPU_PWR_ACK_PROXY;
    volatile uint8_t  Resv_26128[72];
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
    volatile uint32_t CLAIMREG_P1_R13;           /* Claim bits for Partition 1 */
    volatile uint32_t CLAIMREG_P1_R14;           /* Claim bits for Partition 1 */
    volatile uint8_t  Resv_32784[3796];
    volatile uint32_t WKUP_CLKSEL;
    volatile uint8_t  Resv_32800[12];
    volatile uint32_t CLKOUT_CTRL;
    volatile uint8_t  Resv_32816[12];
    volatile uint32_t WKUP_GTC_CLKSEL;
    volatile uint8_t  Resv_32828[8];
    volatile uint32_t EFUSE_CLKSEL;
    volatile uint8_t  Resv_32976[144];
    volatile uint32_t DDR32SS_PMCTRL;
    volatile uint8_t  Resv_33168[188];
    volatile uint32_t USB0_CLKSEL;
    volatile uint32_t USB1_CLKSEL;
    volatile uint8_t  Resv_33200[24];
    volatile uint32_t WKUP_TIMER0_CLKSEL;
    volatile uint32_t WKUP_TIMER1_CLKSEL;
    volatile uint8_t  Resv_33600[392];
    volatile uint32_t WKUP_WWD0_CTRL;
    volatile uint8_t  Resv_33664[60];
    volatile uint32_t WKUP_WWD0_CLKSEL;
    volatile uint8_t  Resv_34304[636];
    volatile uint32_t WKUP_RTC_CLKSEL;
    volatile uint8_t  Resv_36872[2564];
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
    volatile uint8_t  Resv_40976[3804];
    volatile uint32_t WKUP_CLKSEL_PROXY;
    volatile uint8_t  Resv_40992[12];
    volatile uint32_t CLKOUT_CTRL_PROXY;
    volatile uint8_t  Resv_41008[12];
    volatile uint32_t WKUP_GTC_CLKSEL_PROXY;
    volatile uint8_t  Resv_41020[8];
    volatile uint32_t EFUSE_CLKSEL_PROXY;
    volatile uint8_t  Resv_41168[144];
    volatile uint32_t DDR32SS_PMCTRL_PROXY;
    volatile uint8_t  Resv_41360[188];
    volatile uint32_t USB0_CLKSEL_PROXY;
    volatile uint32_t USB1_CLKSEL_PROXY;
    volatile uint8_t  Resv_41392[24];
    volatile uint32_t WKUP_TIMER0_CLKSEL_PROXY;
    volatile uint32_t WKUP_TIMER1_CLKSEL_PROXY;
    volatile uint8_t  Resv_41792[392];
    volatile uint32_t WKUP_WWD0_CTRL_PROXY;
    volatile uint8_t  Resv_41856[60];
    volatile uint32_t WKUP_WWD0_CLKSEL_PROXY;
    volatile uint8_t  Resv_42496[636];
    volatile uint32_t WKUP_RTC_CLKSEL_PROXY;
    volatile uint8_t  Resv_45064[2564];
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
    volatile uint8_t  Resv_49856[4492];
    volatile uint32_t POST_STAT;
    volatile uint32_t POST_CFG;
    volatile uint8_t  Resv_49952[88];
    volatile uint32_t FUSE_CRC_STAT;
    volatile uint8_t  Resv_49984[28];
    volatile uint32_t FUSE_CTRL_STAT;
    volatile uint8_t  Resv_50176[188];
    volatile uint32_t PBIST_EN;
    volatile uint8_t  Resv_53256[3076];
    volatile uint32_t LOCK3_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK3_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_53504[240];
    volatile uint32_t CLAIMREG_P3_R0_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R1_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R2_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R3_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R4_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R5_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R6_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R7_READONLY;   /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R8_READONLY;   /* Claim bits for Partition 3 */
    volatile uint8_t  Resv_58048[4508];
    volatile uint32_t POST_STAT_PROXY;
    volatile uint32_t POST_CFG_PROXY;
    volatile uint8_t  Resv_58144[88];
    volatile uint32_t FUSE_CRC_STAT_PROXY;
    volatile uint8_t  Resv_58176[28];
    volatile uint32_t FUSE_CTRL_STAT_PROXY;
    volatile uint8_t  Resv_58368[188];
    volatile uint32_t PBIST_EN_PROXY;
    volatile uint8_t  Resv_61448[3076];
    volatile uint32_t LOCK3_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK3_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_61696[240];
    volatile uint32_t CLAIMREG_P3_R0;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R1;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R2;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R3;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R4;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R5;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R6;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R7;            /* Claim bits for Partition 3 */
    volatile uint32_t CLAIMREG_P3_R8;            /* Claim bits for Partition 3 */
    volatile uint8_t  Resv_69640[7908];
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
    volatile uint8_t  Resv_77832[7908];
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
    volatile uint8_t  Resv_81920[3804];
    volatile uint32_t CHNG_DDR4_FSP_REQ;
    volatile uint32_t CHNG_DDR4_FSP_ACK;
    volatile uint8_t  Resv_82048[120];
    volatile uint32_t DDR4_FSP_CLKCHNG_REQ;
    volatile uint8_t  Resv_82112[60];
    volatile uint32_t DDR4_FSP_CLKCHNG_ACK;
    volatile uint8_t  Resv_86024[3908];
    volatile uint32_t LOCK5_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK5_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_86272[240];
    volatile uint32_t CLAIMREG_P5_R0_READONLY;   /* Claim bits for Partition 5 */
    volatile uint32_t CLAIMREG_P5_R1_READONLY;   /* Claim bits for Partition 5 */
    volatile uint8_t  Resv_90112[3832];
    volatile uint32_t CHNG_DDR4_FSP_REQ_PROXY;
    volatile uint32_t CHNG_DDR4_FSP_ACK_PROXY;
    volatile uint8_t  Resv_90240[120];
    volatile uint32_t DDR4_FSP_CLKCHNG_REQ_PROXY;
    volatile uint8_t  Resv_90304[60];
    volatile uint32_t DDR4_FSP_CLKCHNG_ACK_PROXY;
    volatile uint8_t  Resv_94216[3908];
    volatile uint32_t LOCK5_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK5_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_94464[240];
    volatile uint32_t CLAIMREG_P5_R0;            /* Claim bits for Partition 5 */
    volatile uint32_t CLAIMREG_P5_R1;            /* Claim bits for Partition 5 */
    volatile uint8_t  Resv_98368[3896];
    volatile uint32_t FW_CTRL_OUT0;
    volatile uint32_t FW_CTRL_OUT0_SET;
    volatile uint32_t FW_CTRL_OUT0_CLR;
    volatile uint32_t FW_STS_IN0;
    volatile uint32_t FW_CTRL_OUT1;
    volatile uint32_t FW_CTRL_OUT1_SET;
    volatile uint32_t FW_CTRL_OUT1_CLR;
    volatile uint32_t FW_STS_IN1;
    volatile uint8_t  Resv_98432[32];
    volatile uint32_t PMCTRL_SYS;
    volatile uint32_t PMCTRL_IO_0;
    volatile uint32_t PMCTRL_IO_1;
    volatile uint8_t  Resv_98448[4];
    volatile uint32_t PMCTRL_MOSC;
    volatile uint8_t  Resv_98456[4];
    volatile uint32_t PM_MISC_STATUS;
    volatile uint32_t PMCTRL_IO_GLB;
    volatile uint32_t PM_PERMISSION;
    volatile uint8_t  Resv_98656[188];
    volatile uint32_t DEEPSLEEP_CTRL;
    volatile uint8_t  Resv_98672[12];
    volatile uint32_t RST_CTRL;
    volatile uint32_t RST_STAT;
    volatile uint32_t RST_SRC;
    volatile uint32_t RST_MAGIC_WORD;
    volatile uint32_t WKUP0_EN;
    volatile uint8_t  Resv_98944[252];
    volatile uint32_t CLKGATE_CTRL0;
    volatile uint32_t CLKGATE_CTRL1;
    volatile uint8_t  Resv_99072[120];
    volatile uint32_t CANUART_WAKE_CTRL;
    volatile uint8_t  Resv_99080[4];
    volatile uint32_t CANUART_WAKE_STAT0;
    volatile uint32_t CANUART_WAKE_STAT1;
    volatile uint32_t CANUART_WAKE_OFF_MODE;
    volatile uint8_t  Resv_99096[4];
    volatile uint32_t CANUART_WAKE_OFF_MODE_STAT;
    volatile uint8_t  Resv_99104[4];
    volatile uint32_t CANUART_WAKE_RESUME_KEY[4];
    volatile uint8_t  Resv_99136[16];
    volatile uint32_t CANUART_WAKE_RESUME_KEY_STAT[4];
    volatile uint8_t  Resv_99328[176];
    volatile uint32_t WFI_STATUS;
    volatile uint8_t  Resv_99344[12];
    volatile uint32_t SLEEP_STATUS;
    volatile uint8_t  Resv_99352[4];
    volatile uint32_t DS_MAGIC_WORD;
    volatile uint8_t  Resv_99360[4];
    volatile uint32_t DS_MAIN;
    volatile uint8_t  Resv_99392[28];
    volatile uint32_t DS_DM_RESET;
    volatile uint8_t  Resv_99424[28];
    volatile uint32_t DS_USB0_RESET;
    volatile uint32_t DS_USB1_RESET;
    volatile uint8_t  Resv_99456[24];
    volatile uint32_t DM_CLKSTOP_EN;
    volatile uint8_t  Resv_99472[12];
    volatile uint32_t DM_CLKSTOP_ACK;
    volatile uint8_t  Resv_99488[12];
    volatile uint32_t DM_GRP_CLKSTOP_REQ;
    volatile uint32_t DM_GRP_CLKSTOP_ACK;
    volatile uint8_t  Resv_99584[88];
    volatile uint32_t DEVICE_TYPE;
    volatile uint8_t  Resv_102408[2820];
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
    volatile uint32_t CLAIMREG_P6_R9_READONLY;   /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R10_READONLY;   /* Claim bits for Partition 6 */
    volatile uint8_t  Resv_106560[3860];
    volatile uint32_t FW_CTRL_OUT0_PROXY;
    volatile uint32_t FW_CTRL_OUT0_SET_PROXY;
    volatile uint32_t FW_CTRL_OUT0_CLR_PROXY;
    volatile uint32_t FW_STS_IN0_PROXY;
    volatile uint32_t FW_CTRL_OUT1_PROXY;
    volatile uint32_t FW_CTRL_OUT1_SET_PROXY;
    volatile uint32_t FW_CTRL_OUT1_CLR_PROXY;
    volatile uint32_t FW_STS_IN1_PROXY;
    volatile uint8_t  Resv_106624[32];
    volatile uint32_t PMCTRL_SYS_PROXY;
    volatile uint32_t PMCTRL_IO_0_PROXY;
    volatile uint32_t PMCTRL_IO_1_PROXY;
    volatile uint8_t  Resv_106640[4];
    volatile uint32_t PMCTRL_MOSC_PROXY;
    volatile uint8_t  Resv_106648[4];
    volatile uint32_t PM_MISC_STATUS_PROXY;
    volatile uint32_t PMCTRL_IO_GLB_PROXY;
    volatile uint32_t PM_PERMISSION_PROXY;
    volatile uint8_t  Resv_106848[188];
    volatile uint32_t DEEPSLEEP_CTRL_PROXY;
    volatile uint8_t  Resv_106864[12];
    volatile uint32_t RST_CTRL_PROXY;
    volatile uint32_t RST_STAT_PROXY;
    volatile uint32_t RST_SRC_PROXY;
    volatile uint32_t RST_MAGIC_WORD_PROXY;
    volatile uint32_t WKUP0_EN_PROXY;
    volatile uint8_t  Resv_107136[252];
    volatile uint32_t CLKGATE_CTRL0_PROXY;
    volatile uint32_t CLKGATE_CTRL1_PROXY;
    volatile uint8_t  Resv_107264[120];
    volatile uint32_t CANUART_WAKE_CTRL_PROXY;
    volatile uint8_t  Resv_107272[4];
    volatile uint32_t CANUART_WAKE_STAT0_PROXY;
    volatile uint32_t CANUART_WAKE_STAT1_PROXY;
    volatile uint32_t CANUART_WAKE_OFF_MODE_PROXY;
    volatile uint8_t  Resv_107288[4];
    volatile uint32_t CANUART_WAKE_OFF_MODE_STAT_PROXY;
    volatile uint8_t  Resv_107296[4];
    volatile uint32_t CANUART_WAKE_RESUME_KEY_PROXY[4];
    volatile uint8_t  Resv_107328[16];
    volatile uint32_t CANUART_WAKE_RESUME_KEY_STAT_PROXY[4];
    volatile uint8_t  Resv_107520[176];
    volatile uint32_t WFI_STATUS_PROXY;
    volatile uint8_t  Resv_107536[12];
    volatile uint32_t SLEEP_STATUS_PROXY;
    volatile uint8_t  Resv_107544[4];
    volatile uint32_t DS_MAGIC_WORD_PROXY;
    volatile uint8_t  Resv_107552[4];
    volatile uint32_t DS_MAIN_PROXY;
    volatile uint8_t  Resv_107584[28];
    volatile uint32_t DS_DM_RESET_PROXY;
    volatile uint8_t  Resv_107616[28];
    volatile uint32_t DS_USB0_RESET_PROXY;
    volatile uint32_t DS_USB1_RESET_PROXY;
    volatile uint8_t  Resv_107648[24];
    volatile uint32_t DM_CLKSTOP_EN_PROXY;
    volatile uint8_t  Resv_107664[12];
    volatile uint32_t DM_CLKSTOP_ACK_PROXY;
    volatile uint8_t  Resv_107680[12];
    volatile uint32_t DM_GRP_CLKSTOP_REQ_PROXY;
    volatile uint32_t DM_GRP_CLKSTOP_ACK_PROXY;
    volatile uint8_t  Resv_107776[88];
    volatile uint32_t DEVICE_TYPE_PROXY;
    volatile uint8_t  Resv_110600[2820];
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
    volatile uint32_t CLAIMREG_P6_R9;            /* Claim bits for Partition 6 */
    volatile uint32_t CLAIMREG_P6_R10;           /* Claim bits for Partition 6 */
    volatile uint8_t  Resv_114944[4052];
    volatile uint32_t BACKUP_REG[24];
    volatile uint8_t  Resv_118792[3752];
    volatile uint32_t LOCK7_KICK0;               /*  - KICK0 component */
    volatile uint32_t LOCK7_KICK1;               /*  - KICK1 component */
    volatile uint8_t  Resv_119040[240];
    volatile uint32_t CLAIMREG_P7_R0_READONLY;   /* Claim bits for Partition 7 */
    volatile uint32_t CLAIMREG_P7_R1_READONLY;   /* Claim bits for Partition 7 */
    volatile uint32_t CLAIMREG_P7_R2_READONLY;   /* Claim bits for Partition 7 */
    volatile uint8_t  Resv_123136[4084];
    volatile uint32_t BACKUP_REG_PROXY[24];
    volatile uint8_t  Resv_126984[3752];
    volatile uint32_t LOCK7_KICK0_PROXY;         /*  - KICK0 component */
    volatile uint32_t LOCK7_KICK1_PROXY;         /*  - KICK1 component */
    volatile uint8_t  Resv_127232[240];
    volatile uint32_t CLAIMREG_P7_R0;            /* Claim bits for Partition 7 */
    volatile uint32_t CLAIMREG_P7_R1;            /* Claim bits for Partition 7 */
    volatile uint32_t CLAIMREG_P7_R2;            /* Claim bits for Partition 7 */
} CSL_wkup_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG0_PID                                        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1                                   (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID                                     (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID                               (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT                               (0x00000030U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG                               (0x00000034U)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS                              (0x00000044U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0                            (0x00000060U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1                            (0x00000064U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2                            (0x00000068U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3                            (0x0000006CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6                            (0x00000078U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0                                    (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1                                    (0x00000204U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0                             (0x00000210U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1                             (0x00000214U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0                             (0x00000220U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1                             (0x00000224U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0                                     (0x00000230U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1                                     (0x00000234U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2                                     (0x00000238U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3                                     (0x0000023CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT                               (0x00000270U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT                            (0x00000280U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0                                (0x00001008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1                                (0x0000100CU)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS                            (0x00001010U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR                  (0x00001014U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE                                (0x00001018U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                          (0x0000101CU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI                                        (0x00001020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS                              (0x00001024U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                          (0x00001028U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                          (0x0000102CU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR                                (0x00001030U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY                    (0x00001100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY                    (0x00001104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY                    (0x00001108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY                    (0x0000110CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY                    (0x00001110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY                    (0x00001114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY                    (0x00001118U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY                                  (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY                             (0x00002008U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY                               (0x00002014U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_PROXY                         (0x00002018U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_PROXY                         (0x00002030U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_PROXY                         (0x00002034U)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROXY                        (0x00002044U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY                      (0x00002060U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY                      (0x00002064U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY                      (0x00002068U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY                      (0x0000206CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_PROXY                      (0x00002078U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_PROXY                              (0x00002200U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_PROXY                              (0x00002204U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_PROXY                       (0x00002210U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_PROXY                       (0x00002214U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_PROXY                       (0x00002220U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_PROXY                       (0x00002224U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_PROXY                               (0x00002230U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_PROXY                               (0x00002234U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_PROXY                               (0x00002238U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_PROXY                               (0x0000223CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY                         (0x00002270U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY                      (0x00002280U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY                          (0x00003008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY                          (0x0000300CU)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY                      (0x00003010U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY            (0x00003014U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY                          (0x00003018U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY                    (0x0000301CU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_PROXY                                  (0x00003020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY                        (0x00003024U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY                    (0x00003028U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY                    (0x0000302CU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY                          (0x00003030U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0                             (0x00003100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1                             (0x00003104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2                             (0x00003108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3                             (0x0000310CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4                             (0x00003110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5                             (0x00003114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6                             (0x00003118U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL                              (0x00004008U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL                              (0x00004018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL                                 (0x00004070U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL                                 (0x000041B4U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL                                 (0x000041B8U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL                                 (0x000041BCU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL                           (0x00004204U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL                             (0x000042E0U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ                                (0x000045C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK                                (0x000045C4U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT                                   (0x00004610U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0                                (0x00005008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1                                (0x0000500CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY                    (0x00005100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY                    (0x00005104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY                    (0x00005108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY                    (0x0000510CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY                    (0x00005110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY                    (0x00005114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY                    (0x00005118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY                    (0x0000511CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY                    (0x00005120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY                    (0x00005124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY                   (0x00005128U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY                   (0x0000512CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY                   (0x00005130U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY                   (0x00005134U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY                   (0x00005138U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY                        (0x00006008U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY                        (0x00006018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY                           (0x00006070U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_PROXY                           (0x000061B4U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_PROXY                           (0x000061B8U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_PROXY                           (0x000061BCU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_PROXY                     (0x00006204U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_PROXY                       (0x000062E0U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY                          (0x000065C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY                          (0x000065C4U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY                             (0x00006610U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY                          (0x00007008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY                          (0x0000700CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0                             (0x00007100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1                             (0x00007104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2                             (0x00007108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3                             (0x0000710CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4                             (0x00007110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5                             (0x00007114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6                             (0x00007118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7                             (0x0000711CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8                             (0x00007120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9                             (0x00007124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10                            (0x00007128U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11                            (0x0000712CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12                            (0x00007130U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13                            (0x00007134U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14                            (0x00007138U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL                                (0x00008010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL                                (0x00008020U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL                            (0x00008030U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL                               (0x0000803CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL                             (0x000080D0U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL                                (0x00008190U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL                                (0x00008194U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL                         (0x000081B0U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL                         (0x000081B4U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL                             (0x00008340U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL                           (0x00008380U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL                            (0x00008600U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0                                (0x00009008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1                                (0x0000900CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY                    (0x00009100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY                    (0x00009104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY                    (0x00009108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY                    (0x0000910CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY                    (0x00009110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY                    (0x00009114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY                    (0x00009118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY                    (0x0000911CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY                    (0x00009120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY                    (0x00009124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY                   (0x00009128U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY                   (0x0000912CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY                   (0x00009130U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_PROXY                          (0x0000A010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY                          (0x0000A020U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_PROXY                      (0x0000A030U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_PROXY                         (0x0000A03CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY                       (0x0000A0D0U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_PROXY                          (0x0000A190U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_PROXY                          (0x0000A194U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_PROXY                   (0x0000A1B0U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_PROXY                   (0x0000A1B4U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_PROXY                       (0x0000A340U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY                     (0x0000A380U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_PROXY                      (0x0000A600U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY                          (0x0000B008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY                          (0x0000B00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0                             (0x0000B100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1                             (0x0000B104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2                             (0x0000B108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3                             (0x0000B10CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4                             (0x0000B110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5                             (0x0000B114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6                             (0x0000B118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7                             (0x0000B11CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8                             (0x0000B120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9                             (0x0000B124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10                            (0x0000B128U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11                            (0x0000B12CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12                            (0x0000B130U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT                                  (0x0000C2C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG                                   (0x0000C2C4U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT                              (0x0000C320U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT                             (0x0000C340U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN                                   (0x0000C400U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0                                (0x0000D008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1                                (0x0000D00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY                    (0x0000D100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_READONLY                    (0x0000D104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_READONLY                    (0x0000D108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_READONLY                    (0x0000D10CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_READONLY                    (0x0000D110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_READONLY                    (0x0000D114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_READONLY                    (0x0000D118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_READONLY                    (0x0000D11CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_READONLY                    (0x0000D120U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY                            (0x0000E2C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY                             (0x0000E2C4U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY                        (0x0000E320U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY                       (0x0000E340U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY                             (0x0000E400U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY                          (0x0000F008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY                          (0x0000F00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0                             (0x0000F100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1                             (0x0000F104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2                             (0x0000F108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3                             (0x0000F10CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4                             (0x0000F110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5                             (0x0000F114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6                             (0x0000F118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7                             (0x0000F11CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8                             (0x0000F120U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0                                (0x00011008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1                                (0x0001100CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY                    (0x00011100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY                    (0x00011104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY                    (0x00011108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY                    (0x0001110CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY                    (0x00011110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY                    (0x00011114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY                    (0x00011118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY                    (0x0001111CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY                    (0x00011120U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY                          (0x00013008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY                          (0x0001300CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0                             (0x00013100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1                             (0x00013104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2                             (0x00013108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3                             (0x0001310CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4                             (0x00013110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5                             (0x00013114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6                             (0x00013118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7                             (0x0001311CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8                             (0x00013120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ                          (0x00014000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK                          (0x00014004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ                       (0x00014080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK                       (0x000140C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0                                (0x00015008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1                                (0x0001500CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_READONLY                    (0x00015100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_READONLY                    (0x00015104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY                    (0x00016000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY                    (0x00016004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY                 (0x00016080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_PROXY                 (0x000160C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_PROXY                          (0x00017008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_PROXY                          (0x0001700CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0                             (0x00017100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1                             (0x00017104U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0                               (0x00018040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET                           (0x00018044U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR                           (0x00018048U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0                                 (0x0001804CU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1                               (0x00018050U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET                           (0x00018054U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR                           (0x00018058U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1                                 (0x0001805CU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS                                 (0x00018080U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0                                (0x00018084U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1                                (0x00018088U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC                                (0x00018090U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS                             (0x00018098U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB                              (0x0001809CU)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION                              (0x000180A0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL                             (0x00018160U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL                                   (0x00018170U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT                                   (0x00018174U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC                                    (0x00018178U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD                             (0x0001817CU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN                                   (0x00018180U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0                              (0x00018280U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1                              (0x00018284U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL                          (0x00018300U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0                         (0x00018308U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1                         (0x0001830CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE                      (0x00018310U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT                 (0x00018318U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY(CANUART_WAKE_RESUME_KEY) (0x00018320U+((CANUART_WAKE_RESUME_KEY)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT(CANUART_WAKE_RESUME_KEY_STAT) (0x00018340U+((CANUART_WAKE_RESUME_KEY_STAT)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS                                 (0x00018400U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS                               (0x00018410U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD                              (0x00018418U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN                                    (0x00018420U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET                                (0x00018440U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET                              (0x00018460U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET                              (0x00018464U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN                              (0x00018480U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK                             (0x00018490U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ                         (0x000184A0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK                         (0x000184A4U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE                                (0x00018500U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0                                (0x00019008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1                                (0x0001900CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY                    (0x00019100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY                    (0x00019104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY                    (0x00019108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY                    (0x0001910CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY                    (0x00019110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY                    (0x00019114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY                    (0x00019118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY                    (0x0001911CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY                    (0x00019120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_READONLY                    (0x00019124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_READONLY                   (0x00019128U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_PROXY                         (0x0001A040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_PROXY                     (0x0001A044U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_PROXY                     (0x0001A048U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_PROXY                           (0x0001A04CU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_PROXY                         (0x0001A050U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_PROXY                     (0x0001A054U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_PROXY                     (0x0001A058U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_PROXY                           (0x0001A05CU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY                           (0x0001A080U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY                          (0x0001A084U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY                          (0x0001A088U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY                          (0x0001A090U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_PROXY                       (0x0001A098U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_PROXY                        (0x0001A09CU)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY                        (0x0001A0A0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY                       (0x0001A160U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY                             (0x0001A170U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_PROXY                             (0x0001A174U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY                              (0x0001A178U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY                       (0x0001A17CU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_PROXY                             (0x0001A180U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY                        (0x0001A280U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY                        (0x0001A284U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY                    (0x0001A300U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY                   (0x0001A308U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_PROXY                   (0x0001A30CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_PROXY                (0x0001A310U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_PROXY           (0x0001A318U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_PROXY(CANUART_WAKE_RESUME_KEY_PROXY) (0x0001A320U+((CANUART_WAKE_RESUME_KEY_PROXY)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_PROXY(CANUART_WAKE_RESUME_KEY_STAT_PROXY) (0x0001A340U+((CANUART_WAKE_RESUME_KEY_STAT_PROXY)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY                           (0x0001A400U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY                         (0x0001A410U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_PROXY                        (0x0001A418U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_PROXY                              (0x0001A420U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_PROXY                          (0x0001A440U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_PROXY                        (0x0001A460U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_PROXY                        (0x0001A464U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY                        (0x0001A480U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY                       (0x0001A490U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_PROXY                   (0x0001A4A0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_PROXY                   (0x0001A4A4U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_PROXY                          (0x0001A500U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY                          (0x0001B008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY                          (0x0001B00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0                             (0x0001B100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1                             (0x0001B104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2                             (0x0001B108U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3                             (0x0001B10CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4                             (0x0001B110U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5                             (0x0001B114U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6                             (0x0001B118U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7                             (0x0001B11CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8                             (0x0001B120U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9                             (0x0001B124U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10                            (0x0001B128U)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG(BACKUP_REG)                     (0x0001C100U+((BACKUP_REG)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0                                (0x0001D008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1                                (0x0001D00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_READONLY                    (0x0001D100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_READONLY                    (0x0001D104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_READONLY                    (0x0001D108U)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_PROXY(BACKUP_REG_PROXY)         (0x0001E100U+((BACKUP_REG_PROXY)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_PROXY                          (0x0001F008U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_PROXY                          (0x0001F00CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0                             (0x0001F100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1                             (0x0001F104U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2                             (0x0001F108U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                         (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                          (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                        (0x000000C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                       (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                         (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                         (0x00000700U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                          (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_MASK                          (0x0000F800U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                         (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_MAX                           (0x0000001FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                         (0xFFFF0000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                        (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                          (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                   (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                    (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                     (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                    (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                      (0x00000001U)

/* JTAGID */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_MASK                            (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_SHIFT                           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_MAX                             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_MASK                            (0x00000FFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_SHIFT                           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_MAX                             (0x000007FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_MASK                         (0x0FFFF000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_SHIFT                        (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_MAX                          (0x0000FFFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_MASK                        (0xF0000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_SHIFT                       (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_MAX                         (0x0000000FU)

/* JTAG_USER_ID */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_MASK                 (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_MAX                  (0xFFFFFFFFU)

/* MAIN_DEVSTAT */

#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_BOOTMODE_MASK                 (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_BOOTMODE_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_BOOTMODE_MAX                  (0x0000FFFFU)

/* MAIN_BOOTCFG */

#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_BOOTMODE_MASK                 (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_BOOTMODE_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_BOOTMODE_MAX                  (0x0000FFFFU)

/* BOOT_PROGRESS */

#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROGRESS_MASK                (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROGRESS_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROGRESS_MAX                 (0xFFFFFFFFU)

/* DEVICE_FEATURE0 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_MASK    (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_SHIFT   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_MASK    (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_SHIFT   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_MASK    (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_SHIFT   (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_MASK    (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_SHIFT   (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_R5FSS0_CORE0_MASK          (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_R5FSS0_CORE0_SHIFT         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_R5FSS0_CORE0_MAX           (0x00000001U)

/* DEVICE_FEATURE1 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VPAC0_EN_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VPAC0_EN_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VPAC0_EN_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_JPEG_ENC_EN_MASK           (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_JPEG_ENC_EN_SHIFT          (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_JPEG_ENC_EN_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_EN_MASK        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_EN_SHIFT       (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_EN_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_EN_MASK                (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_EN_SHIFT               (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_EN_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_ASTC_EN_MASK           (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_ASTC_EN_SHIFT          (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_GPU_ASTC_EN_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_CORE_EN_MASK           (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_CORE_EN_SHIFT          (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_CORE_EN_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_1_CORE_EN_MASK         (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_1_CORE_EN_SHIFT        (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_C7X_1_CORE_EN_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_ATL_EN_MASK                (0x00800000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_ATL_EN_SHIFT               (0x00000017U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_ATL_EN_MAX                 (0x00000001U)

/* DEVICE_FEATURE2 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MCAN_FD_MODE_MASK          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MCAN_FD_MODE_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MCAN_FD_MODE_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_AES_AUTH_EN_MASK           (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_AES_AUTH_EN_SHIFT          (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_AES_AUTH_EN_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SHA_EN_MASK         (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SHA_EN_SHIFT        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SHA_EN_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_ENCR_EN_MASK        (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_ENCR_EN_SHIFT       (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_ENCR_EN_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_PKA_EN_MASK         (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_PKA_EN_SHIFT        (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_PKA_EN_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SM_EN_MASK          (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SM_EN_SHIFT         (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_CRYPTO_SM_EN_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_0_MASK         (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_0_SHIFT        (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_0_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_1_MASK         (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_1_SHIFT        (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_MAIN_SRAM4M_1_MAX          (0x00000001U)

/* DEVICE_FEATURE3 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_MASK           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_1_MASK         (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_1_SHIFT        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_MMA_PRESENT_1_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_MASK     (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_SHIFT    (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_MASK     (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_SHIFT    (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_MAX      (0x00000001U)

/* DEVICE_FEATURE6 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_SA3_UL_MASK                (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_SA3_UL_SHIFT               (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_SA3_UL_MAX                 (0x00000001U)

/* MAC_ID0 */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_MASK                      (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_MAX                       (0xFFFFFFFFU)

/* MAC_ID1 */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_MASK                      (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_MAX                       (0x0000FFFFU)

/* PCI_DEVICE_ID0 */

#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_ID0_MASK                    (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_ID0_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_ID0_MAX                     (0xFFFFFFFFU)

/* PCI_DEVICE_ID1 */

#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_ID1_MASK                    (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_ID1_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_ID1_MAX                     (0xFFFFFFFFU)

/* USB_DEVICE_ID0 */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_MASK                    (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_MAX                     (0xFFFFFFFFU)

/* USB_DEVICE_ID1 */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_MASK                    (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_MAX                     (0xFFFFFFFFU)

/* GP_SW0 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_MASK                            (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_SHIFT                           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_MAX                             (0xFFFFFFFFU)

/* GP_SW1 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_MASK                            (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_SHIFT                           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_MAX                             (0xFFFFFFFFU)

/* GP_SW2 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_MASK                            (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_SHIFT                           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_MAX                             (0xFFFFFFFFU)

/* GP_SW3 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_MASK                            (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_SHIFT                           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_MAX                             (0x0000000FU)

/* CBA_ERR_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_MASK       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_MASK     (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_SHIFT    (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_MASK        (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_SHIFT       (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_FW_CBA_ERR_MASK          (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_FW_CBA_ERR_SHIFT         (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_FW_CBA_ERR_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_MASK   (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_SHIFT  (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_MASK       (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_SHIFT      (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_MASK       (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_SHIFT      (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_MASK      (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_SHIFT     (0x0000000EU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_MASK     (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_SHIFT    (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_MASK       (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_SHIFT      (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_MASK              (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_SHIFT             (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_MCU_CBA_ERR_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_MASK        (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_SHIFT       (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_DM_CBA_ERR_MASK          (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_DM_CBA_ERR_SHIFT         (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_WKUP_DM_CBA_ERR_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_DBG_CBA_ERR_MASK              (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_DBG_CBA_ERR_SHIFT             (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_DBG_CBA_ERR_MAX               (0x00000001U)

/* ACCESS_ERR_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_MASK        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN0_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_MASK        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_SHIFT       (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN3_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_MASK        (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_SHIFT       (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN4_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_MASK        (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_SHIFT       (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN8_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_MASK        (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_SHIFT       (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_ACCESS_ERR_IN9_MAX         (0x00000001U)

/* LOCK0_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_LOCK0_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK0_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_LOCK0_KICK1_MAX                (0xFFFFFFFFU)

/* INTR_RAW_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK              (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT             (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK             (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX              (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MAX (0x00000001U)

/* INTR_ENABLE */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK               (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK               (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK              (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT             (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX               (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK     (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK     (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT    (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK     (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT    (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK    (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT   (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX     (0x00000001U)

/* EOI */

#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                        (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                         (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK              (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX               (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK          (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX           (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK            (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT           (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX             (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK        (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX         (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK       (0x000FFF00U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT      (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX        (0x00000FFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK           (0xFFF00000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT          (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX            (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK                 (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX                  (0x00000001U)

/* CLAIMREG_P0_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_READONLY_CLAIMREG_P0_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_READONLY_CLAIMREG_P0_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_READONLY_CLAIMREG_P0_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_READONLY_CLAIMREG_P0_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_READONLY_CLAIMREG_P0_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_READONLY_CLAIMREG_P0_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P0_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_READONLY_CLAIMREG_P0_R6_READONLY_MAX (0xFFFFFFFFU)

/* PID_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MASK             (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MINOR_PROXY_MAX              (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MASK            (0x000000C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_SHIFT           (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_CUSTOM_PROXY_MAX             (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MASK             (0x00000700U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_SHIFT            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MAJOR_PROXY_MAX              (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MASK              (0x0000F800U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_SHIFT             (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MISC_PROXY_MAX               (0x0000001FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MASK             (0xFFFF0000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_SHIFT            (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PROXY_PID_MSB16_PROXY_MAX              (0x0000FFFFU)

/* MMR_CFG1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MASK (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PARTITIONS_PROXY_MAX (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_MMR_CFG1_PROXY_EN_PROXY_MAX (0x00000001U)

/* JTAGID_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_LSB_PROXY_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_LSB_PROXY_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_LSB_PROXY_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_MFG_PROXY_MASK         (0x00000FFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_MFG_PROXY_SHIFT        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_MFG_PROXY_MAX          (0x000007FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_PARTNO_PROXY_MASK      (0x0FFFF000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_PARTNO_PROXY_SHIFT     (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_PARTNO_PROXY_MAX       (0x0000FFFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_VARIANT_PROXY_MASK     (0xF0000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_VARIANT_PROXY_SHIFT    (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PROXY_JTAGID_VARIANT_PROXY_MAX      (0x0000000FU)

/* JTAG_USER_ID_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_PROXY_JTAG_USER_ID_USERCODE_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_PROXY_JTAG_USER_ID_USERCODE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_PROXY_JTAG_USER_ID_USERCODE_PROXY_MAX (0xFFFFFFFFU)

/* MAIN_DEVSTAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_PROXY_MAIN_DEVSTAT_BOOTMODE_PROXY_MASK (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_PROXY_MAIN_DEVSTAT_BOOTMODE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_DEVSTAT_PROXY_MAIN_DEVSTAT_BOOTMODE_PROXY_MAX (0x0000FFFFU)

/* MAIN_BOOTCFG_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_PROXY_MAIN_BOOTCFG_BOOTMODE_PROXY_MASK (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_PROXY_MAIN_BOOTCFG_BOOTMODE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAIN_BOOTCFG_PROXY_MAIN_BOOTCFG_BOOTMODE_PROXY_MAX (0x0000FFFFU)

/* BOOT_PROGRESS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROXY_BOOT_PROGRESS_PROGRESS_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROXY_BOOT_PROGRESS_PROGRESS_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_BOOT_PROGRESS_PROXY_BOOT_PROGRESS_PROGRESS_PROXY_MAX (0xFFFFFFFFU)

/* DEVICE_FEATURE0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_R5FSS0_CORE0_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_R5FSS0_CORE0_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PROXY_DEVICE_FEATURE0_R5FSS0_CORE0_PROXY_MAX (0x00000001U)

/* DEVICE_FEATURE1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VPAC0_EN_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VPAC0_EN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VPAC0_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_JPEG_ENC_EN_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_JPEG_ENC_EN_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_JPEG_ENC_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_EN_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_EN_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_ENCODE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_HEVC_DECODE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_ENCODE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_VID_ENCODER_AVC_DECODE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_EN_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_EN_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_ASTC_EN_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_ASTC_EN_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_GPU_ASTC_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_CORE_EN_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_CORE_EN_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_CORE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_1_CORE_EN_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_1_CORE_EN_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_C7X_1_CORE_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_ATL_EN_PROXY_MASK (0x00800000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_ATL_EN_PROXY_SHIFT (0x00000017U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE1_PROXY_DEVICE_FEATURE1_ATL_EN_PROXY_MAX (0x00000001U)

/* DEVICE_FEATURE2_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MCAN_FD_MODE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MCAN_FD_MODE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MCAN_FD_MODE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_AES_AUTH_EN_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_AES_AUTH_EN_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_AES_AUTH_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SHA_EN_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SHA_EN_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SHA_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_ENCR_EN_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_ENCR_EN_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_ENCR_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_PKA_EN_PROXY_MASK (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_PKA_EN_PROXY_SHIFT (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_PKA_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SM_EN_PROXY_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SM_EN_PROXY_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_CRYPTO_SM_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_0_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_0_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_1_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_1_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE2_PROXY_DEVICE_FEATURE2_MAIN_SRAM4M_1_PROXY_MAX (0x00000001U)

/* DEVICE_FEATURE3_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_1_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_1_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_MMA_PRESENT_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE3_PROXY_DEVICE_FEATURE3_VPAC_FEATURE_DIS1_PROXY_MAX (0x00000001U)

/* DEVICE_FEATURE6_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_PROXY_DEVICE_FEATURE6_SA3_UL_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_PROXY_DEVICE_FEATURE6_SA3_UL_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE6_PROXY_DEVICE_FEATURE6_SA3_UL_PROXY_MAX (0x00000001U)

/* MAC_ID0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_PROXY_MAC_ID0_MACID_LO_PROXY_MASK  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_PROXY_MAC_ID0_MACID_LO_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_PROXY_MAC_ID0_MACID_LO_PROXY_MAX   (0xFFFFFFFFU)

/* MAC_ID1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_PROXY_MAC_ID1_MACID_HI_PROXY_MASK  (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_PROXY_MAC_ID1_MACID_HI_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_PROXY_MAC_ID1_MACID_HI_PROXY_MAX   (0x0000FFFFU)

/* PCI_DEVICE_ID0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_PROXY_PCI_DEVICE_ID0_ID0_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_PROXY_PCI_DEVICE_ID0_ID0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID0_PROXY_PCI_DEVICE_ID0_ID0_PROXY_MAX (0xFFFFFFFFU)

/* PCI_DEVICE_ID1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_PROXY_PCI_DEVICE_ID1_ID1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_PROXY_PCI_DEVICE_ID1_ID1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCI_DEVICE_ID1_PROXY_PCI_DEVICE_ID1_ID1_PROXY_MAX (0xFFFFFFFFU)

/* USB_DEVICE_ID0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_PROXY_USB_DEVICE_ID0_ID0_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_PROXY_USB_DEVICE_ID0_ID0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_PROXY_USB_DEVICE_ID0_ID0_PROXY_MAX (0xFFFFFFFFU)

/* USB_DEVICE_ID1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_PROXY_USB_DEVICE_ID1_ID1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_PROXY_USB_DEVICE_ID1_ID1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_PROXY_USB_DEVICE_ID1_ID1_PROXY_MAX (0xFFFFFFFFU)

/* GP_SW0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_PROXY_GP_SW0_VAL_PROXY_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_PROXY_GP_SW0_VAL_PROXY_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_PROXY_GP_SW0_VAL_PROXY_MAX          (0xFFFFFFFFU)

/* GP_SW1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_PROXY_GP_SW1_VAL_PROXY_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_PROXY_GP_SW1_VAL_PROXY_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_PROXY_GP_SW1_VAL_PROXY_MAX          (0xFFFFFFFFU)

/* GP_SW2_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_PROXY_GP_SW2_VAL_PROXY_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_PROXY_GP_SW2_VAL_PROXY_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_PROXY_GP_SW2_VAL_PROXY_MAX          (0xFFFFFFFFU)

/* GP_SW3_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_PROXY_GP_SW3_VAL_PROXY_MASK         (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_PROXY_GP_SW3_VAL_PROXY_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_PROXY_GP_SW3_VAL_PROXY_MAX          (0x0000000FU)

/* CBA_ERR_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_INFRA_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_CENTRAL_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_DATA_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_FW_CBA_ERR_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_FW_CBA_ERR_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_FW_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_PROXY_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_PROXY_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MISC_PERI_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_MCASP_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_PROXY_MASK (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_PROXY_SHIFT (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_IPCSS_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_PROXY_MASK (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_PROXY_SHIFT (0x0000000EU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_CFG_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_RT_DATA_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MAIN_AUDIO_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_MASK (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_SHIFT (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_MCU_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_SAFE_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_DM_CBA_ERR_PROXY_MASK (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_DM_CBA_ERR_PROXY_SHIFT (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_WKUP_DM_CBA_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_DBG_CBA_ERR_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_DBG_CBA_ERR_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CBA_ERR_STAT_PROXY_CBA_ERR_STAT_DBG_CBA_ERR_PROXY_MAX (0x00000001U)

/* ACCESS_ERR_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN4_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN8_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_ACCESS_ERR_STAT_PROXY_ACCESS_ERR_STAT_ACCESS_ERR_IN9_PROXY_MAX (0x00000001U)

/* LOCK0_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK0_PROXY_LOCK0_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK0_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK0_KICK1_PROXY_LOCK0_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* INTR_RAW_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MASK  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROT_ERR_PROXY_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MASK  (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ADDR_ERR_PROXY_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MASK  (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_KICK_ERR_PROXY_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_PROXY_ERR_PROXY_MAX  (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROT_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_ADDR_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_KICK_ERR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_PROXY_ENABLED_PROXY_ERR_PROXY_MAX (0x00000001U)

/* INTR_ENABLE_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MASK   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROT_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MASK   (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_SHIFT  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ADDR_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MASK   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_SHIFT  (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_KICK_ERR_EN_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MASK  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_PROXY_ERR_EN_PROXY_MAX   (0x00000001U)

/* INTR_ENABLE_CLEAR_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROT_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ADDR_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_KICK_ERR_EN_CLR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_PROXY_ERR_EN_CLR_PROXY_MAX (0x00000001U)

/* EOI_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MASK            (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_PROXY_EOI_VECTOR_PROXY_MAX             (0x000000FFU)

/* FAULT_ADDRESS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MASK  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_PROXY_FAULT_ADDR_PROXY_MAX   (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MASK (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_TYPE_PROXY_MAX (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_PROXY_FAULT_NS_PROXY_MAX (0x00000001U)

/* FAULT_ATTR_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MASK (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_PRIVID_PROXY_MAX (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MASK (0x000FFF00U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_ROUTEID_PROXY_MAX (0x00000FFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MASK (0xFFF00000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_SHIFT (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_PROXY_FAULT_XID_PROXY_MAX (0x00000FFFU)

/* FAULT_CLEAR_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MASK     (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_SHIFT    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_PROXY_FAULT_CLR_PROXY_MAX      (0x00000001U)

/* CLAIMREG_P0_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R0_CLAIMREG_P0_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R1_CLAIMREG_P0_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R2_CLAIMREG_P0_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R3_CLAIMREG_P0_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R4_CLAIMREG_P0_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R5_CLAIMREG_P0_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P0_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P0_R6_CLAIMREG_P0_R6_MAX          (0xFFFFFFFFU)

/* USB0_PHY_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PLL_REF_SEL_MASK             (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PLL_REF_SEL_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PLL_REF_SEL_MAX              (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_CORE_VOLTAGE_MASK            (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_CORE_VOLTAGE_SHIFT           (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_CORE_VOLTAGE_MAX             (0x00000001U)

/* USB1_PHY_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PLL_REF_SEL_MASK             (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PLL_REF_SEL_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PLL_REF_SEL_MAX              (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_CORE_VOLTAGE_MASK            (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_CORE_VOLTAGE_SHIFT           (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_CORE_VOLTAGE_MAX             (0x00000001U)

/* PCIE0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_GENERATION_SEL_MASK             (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_GENERATION_SEL_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_GENERATION_SEL_MAX              (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_MODE_SEL_MASK                   (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_MODE_SEL_SHIFT                  (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_MODE_SEL_MAX                    (0x00000001U)

/* SDIO0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_DRV_STR_MASK                    (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_DRV_STR_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_DRV_STR_MAX                     (0x0000001FU)

/* SDIO1_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_DRV_STR_MASK                    (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_DRV_STR_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_DRV_STR_MAX                     (0x0000001FU)

/* SDIO2_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_DRV_STR_MASK                    (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_DRV_STR_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_DRV_STR_MAX                     (0x0000001FU)

/* WKUP_TIMER1_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_CASCADE_EN_MASK           (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_CASCADE_EN_SHIFT          (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_CASCADE_EN_MAX            (0x00000001U)

/* WKUP_I2C0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_HS_MCS_EN_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_HS_MCS_EN_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_HS_MCS_EN_MAX               (0x00000001U)

/* GPU_PWR_REQ */

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_GPU_MASK_MASK                  (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_GPU_MASK_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_GPU_MASK_MAX                   (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_DOMAIN_MASK                    (0x00000700U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_DOMAIN_SHIFT                   (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_DOMAIN_MAX                     (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_TYPE_MASK                      (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_TYPE_SHIFT                     (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_TYPE_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_REQ_MASK                       (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_REQ_SHIFT                      (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_REQ_MAX                        (0x00000001U)

/* GPU_PWR_ACK */

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_COMPLETE_MASK                  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_COMPLETE_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_COMPLETE_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_ABORT_MASK                     (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_ABORT_SHIFT                    (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_ABORT_MAX                      (0x00000001U)

/* TOG_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_MASK                 (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_MST_TOG_STAT_MAX                  (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_MASK                 (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_SHIFT                (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_SLV_TOG_STAT_MAX                  (0x00000001U)

/* LOCK1_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_LOCK1_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK1_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_LOCK1_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P1_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_READONLY_CLAIMREG_P1_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_READONLY_CLAIMREG_P1_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_READONLY_CLAIMREG_P1_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_READONLY_CLAIMREG_P1_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_READONLY_CLAIMREG_P1_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_READONLY_CLAIMREG_P1_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_READONLY_CLAIMREG_P1_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R7_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_READONLY_CLAIMREG_P1_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R8_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_READONLY_CLAIMREG_P1_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R9_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_READONLY_CLAIMREG_P1_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R10_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_READONLY_CLAIMREG_P1_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R11_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_READONLY_CLAIMREG_P1_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R12_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_READONLY_CLAIMREG_P1_R12_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R13_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_READONLY_CLAIMREG_P1_R13_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P1_R14_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_READONLY_CLAIMREG_P1_R14_READONLY_MAX (0xFFFFFFFFU)

/* USB0_PHY_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_PLL_REF_SEL_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_PLL_REF_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_PLL_REF_SEL_PROXY_MAX (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_CORE_VOLTAGE_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_CORE_VOLTAGE_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_PHY_CTRL_PROXY_USB0_PHY_CTRL_CORE_VOLTAGE_PROXY_MAX (0x00000001U)

/* USB1_PHY_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_PLL_REF_SEL_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_PLL_REF_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_PLL_REF_SEL_PROXY_MAX (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_CORE_VOLTAGE_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_CORE_VOLTAGE_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_PHY_CTRL_PROXY_USB1_PHY_CTRL_CORE_VOLTAGE_PROXY_MAX (0x00000001U)

/* PCIE0_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_GENERATION_SEL_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_GENERATION_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_GENERATION_SEL_PROXY_MAX (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_MODE_SEL_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_MODE_SEL_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_PCIE0_CTRL_PROXY_PCIE0_CTRL_MODE_SEL_PROXY_MAX (0x00000001U)

/* SDIO0_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_PROXY_SDIO0_CTRL_DRV_STR_PROXY_MASK (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_PROXY_SDIO0_CTRL_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO0_CTRL_PROXY_SDIO0_CTRL_DRV_STR_PROXY_MAX (0x0000001FU)

/* SDIO1_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_PROXY_SDIO1_CTRL_DRV_STR_PROXY_MASK (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_PROXY_SDIO1_CTRL_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO1_CTRL_PROXY_SDIO1_CTRL_DRV_STR_PROXY_MAX (0x0000001FU)

/* SDIO2_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_PROXY_SDIO2_CTRL_DRV_STR_PROXY_MASK (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_PROXY_SDIO2_CTRL_DRV_STR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SDIO2_CTRL_PROXY_SDIO2_CTRL_DRV_STR_PROXY_MAX (0x0000001FU)

/* WKUP_TIMER1_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_PROXY_WKUP_TIMER1_CTRL_CASCADE_EN_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_PROXY_WKUP_TIMER1_CTRL_CASCADE_EN_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CTRL_PROXY_WKUP_TIMER1_CTRL_CASCADE_EN_PROXY_MAX (0x00000001U)

/* WKUP_I2C0_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_PROXY_WKUP_I2C0_CTRL_HS_MCS_EN_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_PROXY_WKUP_I2C0_CTRL_HS_MCS_EN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_I2C0_CTRL_PROXY_WKUP_I2C0_CTRL_HS_MCS_EN_PROXY_MAX (0x00000001U)

/* GPU_PWR_REQ_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_GPU_MASK_PROXY_MASK (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_GPU_MASK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_GPU_MASK_PROXY_MAX (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_DOMAIN_PROXY_MASK (0x00000700U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_DOMAIN_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_DOMAIN_PROXY_MAX (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_TYPE_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_TYPE_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_TYPE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_REQ_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_REQ_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_REQ_PROXY_GPU_PWR_REQ_REQ_PROXY_MAX (0x00000001U)

/* GPU_PWR_ACK_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_COMPLETE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_COMPLETE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_COMPLETE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_ABORT_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_ABORT_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_GPU_PWR_ACK_PROXY_GPU_PWR_ACK_ABORT_PROXY_MAX (0x00000001U)

/* TOG_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_MST_TOG_STAT_PROXY_MAX (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_TOG_STAT_PROXY_TOG_STAT_SLV_TOG_STAT_PROXY_MAX (0x00000001U)

/* LOCK1_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK0_PROXY_LOCK1_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK1_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK1_KICK1_PROXY_LOCK1_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P1_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R0_CLAIMREG_P1_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R1_CLAIMREG_P1_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R2_CLAIMREG_P1_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R3_CLAIMREG_P1_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R4_CLAIMREG_P1_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R5_CLAIMREG_P1_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R6_CLAIMREG_P1_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R7 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R7_CLAIMREG_P1_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R8 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R8_CLAIMREG_P1_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R9 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R9_CLAIMREG_P1_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P1_R10 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R10_CLAIMREG_P1_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R11 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R11_CLAIMREG_P1_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R12 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R12_CLAIMREG_P1_R12_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R13 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R13_CLAIMREG_P1_R13_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P1_R14 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P1_R14_CLAIMREG_P1_R14_MAX        (0xFFFFFFFFU)

/* WKUP_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_CLK_SEL_MASK                   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_CLK_SEL_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_CLK_SEL_MAX                    (0x00000001U)

/* CLKOUT_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_WKUP_CLKOUT_SEL_MASK           (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_WKUP_CLKOUT_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_WKUP_CLKOUT_SEL_MAX            (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_OUT_MUX_SEL_MASK               (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_OUT_MUX_SEL_SHIFT              (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_OUT_MUX_SEL_MAX                (0x00000001U)

/* WKUP_GTC_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_CLK_SEL_MASK               (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_CLK_SEL_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_CLK_SEL_MAX                (0x00000007U)

/* EFUSE_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_CLK_SEL_MASK                  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_CLK_SEL_MAX                   (0x00000001U)

/* DDR32SS_PMCTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RETENTION_MASK         (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RETENTION_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RETENTION_MAX          (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RET_LD_MASK            (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RET_LD_SHIFT           (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_DATA_RET_LD_MAX             (0x00000001U)

/* USB0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_REFCLK_SEL_MASK                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_REFCLK_SEL_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_REFCLK_SEL_MAX                 (0x00000001U)

/* USB1_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_REFCLK_SEL_MASK                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_REFCLK_SEL_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_REFCLK_SEL_MAX                 (0x00000001U)

/* WKUP_TIMER0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_CLK_SEL_MASK            (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_CLK_SEL_MAX             (0x00000007U)

/* WKUP_TIMER1_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_CLK_SEL_MASK            (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_CLK_SEL_MAX             (0x00000007U)

/* WKUP_WWD0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_WWD_STOP_MASK               (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_WWD_STOP_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_WWD_STOP_MAX                (0x0000000FU)

/* WKUP_WWD0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_CLK_SEL_MASK              (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_CLK_SEL_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_CLK_SEL_MAX               (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_WRTLOCK_MASK              (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_WRTLOCK_SHIFT             (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_WRTLOCK_MAX               (0x00000001U)

/* WKUP_RTC_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_CLK_SEL_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_CLK_SEL_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_CLK_SEL_MAX                (0x00000001U)

/* LOCK2_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_LOCK2_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK2_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_LOCK2_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P2_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_READONLY_CLAIMREG_P2_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_READONLY_CLAIMREG_P2_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_READONLY_CLAIMREG_P2_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_READONLY_CLAIMREG_P2_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_READONLY_CLAIMREG_P2_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_READONLY_CLAIMREG_P2_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_READONLY_CLAIMREG_P2_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R7_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_READONLY_CLAIMREG_P2_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R8_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_READONLY_CLAIMREG_P2_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R9_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_READONLY_CLAIMREG_P2_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R10_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_READONLY_CLAIMREG_P2_R10_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R11_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_READONLY_CLAIMREG_P2_R11_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P2_R12_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_READONLY_CLAIMREG_P2_R12_READONLY_MAX (0xFFFFFFFFU)

/* WKUP_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_PROXY_WKUP_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_PROXY_WKUP_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_CLKSEL_PROXY_WKUP_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* CLKOUT_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_WKUP_CLKOUT_SEL_PROXY_MASK (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_WKUP_CLKOUT_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_WKUP_CLKOUT_SEL_PROXY_MAX (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_OUT_MUX_SEL_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_OUT_MUX_SEL_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKOUT_CTRL_PROXY_CLKOUT_CTRL_OUT_MUX_SEL_PROXY_MAX (0x00000001U)

/* WKUP_GTC_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_PROXY_WKUP_GTC_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_PROXY_WKUP_GTC_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_GTC_CLKSEL_PROXY_WKUP_GTC_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* EFUSE_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_PROXY_EFUSE_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_PROXY_EFUSE_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_EFUSE_CLKSEL_PROXY_EFUSE_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* DDR32SS_PMCTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RETENTION_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RETENTION_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RETENTION_PROXY_MAX (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RET_LD_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RET_LD_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR32SS_PMCTRL_PROXY_DDR32SS_PMCTRL_DATA_RET_LD_PROXY_MAX (0x00000001U)

/* USB0_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_PROXY_USB0_CLKSEL_REFCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_PROXY_USB0_CLKSEL_REFCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB0_CLKSEL_PROXY_USB0_CLKSEL_REFCLK_SEL_PROXY_MAX (0x00000001U)

/* USB1_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_PROXY_USB1_CLKSEL_REFCLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_PROXY_USB1_CLKSEL_REFCLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB1_CLKSEL_PROXY_USB1_CLKSEL_REFCLK_SEL_PROXY_MAX (0x00000001U)

/* WKUP_TIMER0_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_PROXY_WKUP_TIMER0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_PROXY_WKUP_TIMER0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER0_CLKSEL_PROXY_WKUP_TIMER0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* WKUP_TIMER1_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_PROXY_WKUP_TIMER1_CLKSEL_CLK_SEL_PROXY_MASK (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_PROXY_WKUP_TIMER1_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_TIMER1_CLKSEL_PROXY_WKUP_TIMER1_CLKSEL_CLK_SEL_PROXY_MAX (0x00000007U)

/* WKUP_WWD0_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_PROXY_WKUP_WWD0_CTRL_WWD_STOP_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_PROXY_WKUP_WWD0_CTRL_WWD_STOP_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CTRL_PROXY_WKUP_WWD0_CTRL_WWD_STOP_PROXY_MAX (0x0000000FU)

/* WKUP_WWD0_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_CLK_SEL_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_CLK_SEL_PROXY_MAX (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_WRTLOCK_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_WRTLOCK_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_WWD0_CLKSEL_PROXY_WKUP_WWD0_CLKSEL_WRTLOCK_PROXY_MAX (0x00000001U)

/* WKUP_RTC_CLKSEL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_PROXY_WKUP_RTC_CLKSEL_CLK_SEL_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_PROXY_WKUP_RTC_CLKSEL_CLK_SEL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP_RTC_CLKSEL_PROXY_WKUP_RTC_CLKSEL_CLK_SEL_PROXY_MAX (0x00000001U)

/* LOCK2_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0_PROXY_LOCK2_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK2_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1_PROXY_LOCK2_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P2_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R0_CLAIMREG_P2_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R1_CLAIMREG_P2_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R2_CLAIMREG_P2_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R3_CLAIMREG_P2_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R4_CLAIMREG_P2_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R5_CLAIMREG_P2_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R6_CLAIMREG_P2_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R7 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R7_CLAIMREG_P2_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R8 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R8_CLAIMREG_P2_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R9 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R9_CLAIMREG_P2_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P2_R10 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R10_CLAIMREG_P2_R10_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R11 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R11_CLAIMREG_P2_R11_MAX        (0xFFFFFFFFU)

/* CLAIMREG_P2_R12 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P2_R12_CLAIMREG_P2_R12_MAX        (0xFFFFFFFFU)

/* POST_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_DONE_MASK             (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_DONE_SHIFT            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_DONE_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_TIMEOUT_MASK          (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_TIMEOUT_SHIFT         (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_TIMEOUT_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_FAIL_MASK             (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_FAIL_SHIFT            (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_FAIL_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCKLOSS_MASK          (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCKLOSS_SHIFT         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCKLOSS_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_MASK      (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_SHIFT     (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_MAX       (0x00000001U)

/* POST_CFG */

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FB_DIV_INT_MASK                   (0x00000FFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FB_DIV_INT_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FB_DIV_INT_MAX                    (0x00000FFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_REF_DIV_MASK                      (0x003F0000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_REF_DIV_SHIFT                     (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_REF_DIV_MAX                       (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV1_MASK                    (0x07000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV1_SHIFT                   (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV1_MAX                     (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV2_MASK                    (0x70000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV2_SHIFT                   (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_POST_DIV2_MAX                     (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FAST_POST_EN_MASK                 (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FAST_POST_EN_SHIFT                (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_FAST_POST_EN_MAX                  (0x00000001U)

/* FUSE_CRC_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_1_MASK               (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_1_SHIFT              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_1_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_2_MASK               (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_2_SHIFT              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_2_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_3_MASK               (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_3_SHIFT              (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_3_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_4_MASK               (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_4_SHIFT              (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_4_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_5_MASK               (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_5_SHIFT              (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_5_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_6_MASK               (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_6_SHIFT              (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_6_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_7_MASK               (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_7_SHIFT              (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_CRC_ERR_7_MAX                (0x00000001U)

/* FUSE_CTRL_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_MASK         (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_SHIFT        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_MASK         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_SHIFT        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_MASK         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_SHIFT        (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_MASK         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_SHIFT        (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_MASK         (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_SHIFT        (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_MASK         (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_SHIFT        (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_MASK         (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_SHIFT        (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_MAX          (0x00000001U)

/* PBIST_EN */

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC0_MASK                        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC0_SHIFT                       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC0_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC1_MASK                        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC1_SHIFT                       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC1_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC2_MASK                        (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC2_SHIFT                       (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_EMMC2_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB0_MASK                         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB0_SHIFT                        (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB0_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB1_MASK                         (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB1_SHIFT                        (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_USB1_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PCIE0_MASK                        (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PCIE0_SHIFT                       (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PCIE0_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_DSS0_MASK                         (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_DSS0_SHIFT                        (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_DSS0_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_CSI_TX0_MASK                      (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_CSI_TX0_SHIFT                     (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_CSI_TX0_MAX                       (0x00000001U)

/* LOCK3_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_LOCK3_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK3_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_LOCK3_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P3_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_READONLY_CLAIMREG_P3_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_READONLY_CLAIMREG_P3_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_READONLY_CLAIMREG_P3_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_READONLY_CLAIMREG_P3_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_READONLY_CLAIMREG_P3_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_READONLY_CLAIMREG_P3_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_READONLY_CLAIMREG_P3_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_READONLY_CLAIMREG_P3_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_READONLY_CLAIMREG_P3_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_READONLY_CLAIMREG_P3_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_READONLY_CLAIMREG_P3_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_READONLY_CLAIMREG_P3_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_READONLY_CLAIMREG_P3_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_READONLY_CLAIMREG_P3_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_READONLY_CLAIMREG_P3_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_READONLY_CLAIMREG_P3_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_READONLY_CLAIMREG_P3_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_READONLY_CLAIMREG_P3_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_READONLY_CLAIMREG_P3_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R7_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_READONLY_CLAIMREG_P3_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_READONLY_CLAIMREG_P3_R7_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_READONLY_CLAIMREG_P3_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P3_R8_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_READONLY_CLAIMREG_P3_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_READONLY_CLAIMREG_P3_R8_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_READONLY_CLAIMREG_P3_R8_READONLY_MAX (0xFFFFFFFFU)

/* POST_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_DONE_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_DONE_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_DONE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_TIMEOUT_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_TIMEOUT_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_TIMEOUT_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_FAIL_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_FAIL_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_POST_PBIST_FAIL_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCKLOSS_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCKLOSS_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCKLOSS_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_STAT_PROXY_POST_STAT_FPOST_PLL_LOCK_TIMEOUT_PROXY_MAX (0x00000001U)

/* POST_CFG_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FB_DIV_INT_PROXY_MASK (0x00000FFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FB_DIV_INT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FB_DIV_INT_PROXY_MAX (0x00000FFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_REF_DIV_PROXY_MASK (0x003F0000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_REF_DIV_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_REF_DIV_PROXY_MAX  (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV1_PROXY_MASK (0x07000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV1_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV1_PROXY_MAX (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV2_PROXY_MASK (0x70000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV2_PROXY_SHIFT (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_POST_DIV2_PROXY_MAX (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FAST_POST_EN_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FAST_POST_EN_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_POST_CFG_PROXY_POST_CFG_FAST_POST_EN_PROXY_MAX (0x00000001U)

/* FUSE_CRC_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_1_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_1_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_2_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_2_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_2_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_4_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_4_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_4_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_5_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_5_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_5_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_6_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_6_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_6_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_7_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_7_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CRC_STAT_PROXY_FUSE_CRC_STAT_CRC_ERR_7_PROXY_MAX (0x00000001U)

/* FUSE_CTRL_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_4_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_5_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_6_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_FUSE_CTRL_STAT_PROXY_FUSE_CTRL_STAT_AUTOLOAD_ERR_7_PROXY_MAX (0x00000001U)

/* PBIST_EN_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC0_PROXY_MASK   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC0_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC1_PROXY_MASK   (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC1_PROXY_SHIFT  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC1_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC2_PROXY_MASK   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC2_PROXY_SHIFT  (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_EMMC2_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB0_PROXY_MASK    (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB0_PROXY_SHIFT   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB0_PROXY_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB1_PROXY_MASK    (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB1_PROXY_SHIFT   (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_USB1_PROXY_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_PCIE0_PROXY_MASK   (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_PCIE0_PROXY_SHIFT  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_PCIE0_PROXY_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_DSS0_PROXY_MASK    (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_DSS0_PROXY_SHIFT   (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_DSS0_PROXY_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_CSI_TX0_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_CSI_TX0_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN_PROXY_PBIST_EN_CSI_TX0_PROXY_MAX  (0x00000001U)

/* LOCK3_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0_PROXY_LOCK3_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK3_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1_PROXY_LOCK3_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P3_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R0_CLAIMREG_P3_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_CLAIMREG_P3_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_CLAIMREG_P3_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R1_CLAIMREG_P3_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_CLAIMREG_P3_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_CLAIMREG_P3_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R2_CLAIMREG_P3_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_CLAIMREG_P3_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_CLAIMREG_P3_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R3_CLAIMREG_P3_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_CLAIMREG_P3_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_CLAIMREG_P3_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R4_CLAIMREG_P3_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_CLAIMREG_P3_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_CLAIMREG_P3_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R5_CLAIMREG_P3_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_CLAIMREG_P3_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_CLAIMREG_P3_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R6_CLAIMREG_P3_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R7 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_CLAIMREG_P3_R7_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_CLAIMREG_P3_R7_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R7_CLAIMREG_P3_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P3_R8 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_CLAIMREG_P3_R8_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_CLAIMREG_P3_R8_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P3_R8_CLAIMREG_P3_R8_MAX          (0xFFFFFFFFU)

/* LOCK4_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_LOCK4_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK4_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_LOCK4_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P4_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_READONLY_CLAIMREG_P4_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_READONLY_CLAIMREG_P4_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_READONLY_CLAIMREG_P4_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_READONLY_CLAIMREG_P4_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_READONLY_CLAIMREG_P4_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_READONLY_CLAIMREG_P4_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_READONLY_CLAIMREG_P4_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R7_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_READONLY_CLAIMREG_P4_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P4_R8_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_READONLY_CLAIMREG_P4_R8_READONLY_MAX (0xFFFFFFFFU)

/* LOCK4_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0_PROXY_LOCK4_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK4_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1_PROXY_LOCK4_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P4_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R0_CLAIMREG_P4_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R1_CLAIMREG_P4_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R2_CLAIMREG_P4_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R3_CLAIMREG_P4_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R4_CLAIMREG_P4_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R5_CLAIMREG_P4_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R6_CLAIMREG_P4_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R7 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R7_CLAIMREG_P4_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P4_R8 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P4_R8_CLAIMREG_P4_R8_MAX          (0xFFFFFFFFU)

/* CHNG_DDR4_FSP_REQ */

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_TYPE_MASK            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_TYPE_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_TYPE_MAX             (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_MASK                 (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_SHIFT                (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_REQ_MAX                  (0x00000001U)

/* CHNG_DDR4_FSP_ACK */

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ERROR_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ERROR_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ERROR_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ACK_MASK                 (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ACK_SHIFT                (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_ACK_MAX                  (0x00000001U)

/* DDR4_FSP_CLKCHNG_REQ */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_MASK         (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_MAX          (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_MASK              (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_SHIFT             (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_REQ_MAX               (0x00000001U)

/* DDR4_FSP_CLKCHNG_ACK */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_ACK_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_ACK_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_ACK_MAX               (0x00000001U)

/* LOCK5_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_LOCK5_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_LOCK5_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_LOCK5_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK5_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_LOCK5_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_LOCK5_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_LOCK5_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P5_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_READONLY_CLAIMREG_P5_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_READONLY_CLAIMREG_P5_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_READONLY_CLAIMREG_P5_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P5_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_READONLY_CLAIMREG_P5_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_READONLY_CLAIMREG_P5_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_READONLY_CLAIMREG_P5_R1_READONLY_MAX (0xFFFFFFFFU)

/* CHNG_DDR4_FSP_REQ_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_TYPE_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_TYPE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_TYPE_PROXY_MAX (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_REQ_PROXY_CHNG_DDR4_FSP_REQ_REQ_PROXY_MAX (0x00000001U)

/* CHNG_DDR4_FSP_ACK_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ERROR_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ERROR_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ERROR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ACK_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ACK_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CHNG_DDR4_FSP_ACK_PROXY_CHNG_DDR4_FSP_ACK_ACK_PROXY_MAX (0x00000001U)

/* DDR4_FSP_CLKCHNG_REQ_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_PROXY_MAX (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_REQ_PROXY_DDR4_FSP_CLKCHNG_REQ_REQ_PROXY_MAX (0x00000001U)

/* DDR4_FSP_CLKCHNG_ACK_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_PROXY_DDR4_FSP_CLKCHNG_ACK_ACK_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_PROXY_DDR4_FSP_CLKCHNG_ACK_ACK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DDR4_FSP_CLKCHNG_ACK_PROXY_DDR4_FSP_CLKCHNG_ACK_ACK_PROXY_MAX (0x00000001U)

/* LOCK5_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_PROXY_LOCK5_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_PROXY_LOCK5_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK0_PROXY_LOCK5_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK5_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_PROXY_LOCK5_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_PROXY_LOCK5_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK5_KICK1_PROXY_LOCK5_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P5_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_CLAIMREG_P5_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_CLAIMREG_P5_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R0_CLAIMREG_P5_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P5_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_CLAIMREG_P5_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_CLAIMREG_P5_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P5_R1_CLAIMREG_P5_R1_MAX          (0xFFFFFFFFU)

/* FW_CTRL_OUT0 */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_FW_CTRL_OUT0_MASK             (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_FW_CTRL_OUT0_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_FW_CTRL_OUT0_MAX              (0xFFFFFFFFU)

/* FW_CTRL_OUT0_SET */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_MAX          (0xFFFFFFFFU)

/* FW_CTRL_OUT0_CLR */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_MAX          (0xFFFFFFFFU)

/* FW_STS_IN0 */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_EVENT_MASK                      (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_EVENT_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_EVENT_MAX                       (0xFFFFFFFFU)

/* FW_CTRL_OUT1 */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_FW_CTRL_OUT1_MASK             (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_FW_CTRL_OUT1_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_FW_CTRL_OUT1_MAX              (0xFFFFFFFFU)

/* FW_CTRL_OUT1_SET */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_MAX          (0xFFFFFFFFU)

/* FW_CTRL_OUT1_CLR */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_MAX          (0xFFFFFFFFU)

/* FW_STS_IN1 */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_EVENT_MASK                      (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_EVENT_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_EVENT_MAX                       (0xFFFFFFFFU)

/* PMCTRL_SYS */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_MASK                     (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_MAX                      (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_WE_MASK                  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_WE_SHIFT                 (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_LPM_EN_WE_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_MASK                    (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_SHIFT                   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_MAX                     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_WE_MASK                 (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_WE_SHIFT                (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PMIC_EN_WE_MAX                  (0x00000001U)

/* PMCTRL_IO_0 */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_OVRD_0_MASK             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_OVRD_0_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_OVRD_0_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_STATUS_0_MASK           (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_STATUS_0_SHIFT          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOCLK_STATUS_0_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOOVR_EXTEND_0_MASK           (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOOVR_EXTEND_0_SHIFT          (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOOVR_EXTEND_0_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ON_STATUS_0_MASK            (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ON_STATUS_0_SHIFT           (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ON_STATUS_0_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOBYPASS_OVR_0_MASK           (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOBYPASS_OVR_0_SHIFT          (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_ISOBYPASS_OVR_0_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_CTRL_0_MASK              (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_CTRL_0_SHIFT             (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_CTRL_0_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_STATUS_0_MASK            (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_STATUS_0_SHIFT           (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_WUCLK_STATUS_0_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_GLOBAL_WUEN_0_MASK             (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_GLOBAL_WUEN_0_SHIFT            (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_GLOBAL_WUEN_0_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_CTRL_0_MASK             (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_CTRL_0_SHIFT            (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_CTRL_0_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_STATUS_0_MASK           (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_STATUS_0_SHIFT          (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_IO_ISO_STATUS_0_MAX            (0x00000001U)

/* PMCTRL_IO_1 */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_OVRD_1_MASK             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_OVRD_1_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_OVRD_1_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_STATUS_1_MASK           (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_STATUS_1_SHIFT          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOCLK_STATUS_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOOVR_EXTEND_1_MASK           (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOOVR_EXTEND_1_SHIFT          (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOOVR_EXTEND_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ON_STATUS_1_MASK            (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ON_STATUS_1_SHIFT           (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ON_STATUS_1_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOBYPASS_OVR_1_MASK           (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOBYPASS_OVR_1_SHIFT          (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_ISOBYPASS_OVR_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_CTRL_1_MASK              (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_CTRL_1_SHIFT             (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_CTRL_1_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_STATUS_1_MASK            (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_STATUS_1_SHIFT           (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_WUCLK_STATUS_1_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_GLOBAL_WUEN_1_MASK             (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_GLOBAL_WUEN_1_SHIFT            (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_GLOBAL_WUEN_1_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_CTRL_1_MASK             (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_CTRL_1_SHIFT            (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_CTRL_1_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_STATUS_1_MASK           (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_STATUS_1_SHIFT          (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_IO_ISO_STATUS_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_RESERVED4_MASK                 (0xFC000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_RESERVED4_SHIFT                (0x0000001AU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_RESERVED4_MAX                  (0x0000003FU)

/* PMCTRL_MOSC */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_SETUP_TIME_MASK                (0x000FFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_SETUP_TIME_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_SETUP_TIME_MAX                 (0x000FFFFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_OSC_CG_ON_WFI_MASK             (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_OSC_CG_ON_WFI_SHIFT            (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_OSC_CG_ON_WFI_MAX              (0x00000001U)

/* PM_MISC_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_OSC_CG_STAT_MASK            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_OSC_CG_STAT_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_OSC_CG_STAT_MAX             (0x00000003U)

/* PMCTRL_IO_GLB */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_DSEN_QUALIFIED_MASK          (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_DSEN_QUALIFIED_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_DSEN_QUALIFIED_MAX           (0x00000003U)

/* PM_PERMISSION */

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_DEBUG_ACTIVE_MASK            (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_DEBUG_ACTIVE_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_DEBUG_ACTIVE_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_SECURITY_ACTIVE_MASK         (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_SECURITY_ACTIVE_SHIFT        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_SECURITY_ACTIVE_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_MCU_SAFETY_ACTIVE_MASK       (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_MCU_SAFETY_ACTIVE_SHIFT      (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_MCU_SAFETY_ACTIVE_MAX        (0x00000001U)

/* DEEPSLEEP_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_WKUP_MASK          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_WKUP_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_WKUP_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_MAIN_MASK          (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_MAIN_SHIFT         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_FORCE_DS_MAIN_MAX           (0x00000001U)

/* RST_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_MASK              (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_WARMRST_MAX               (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_MASK                  (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_SHIFT                 (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SW_MAIN_POR_MAX                   (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_MASK          (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_SHIFT         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_SMS_COLD_RESET_EN_Z_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_MASK      (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_SHIFT     (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_RESET_ISO_DONE_Z_MASK        (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_RESET_ISO_DONE_Z_SHIFT       (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_MAIN_RESET_ISO_DONE_Z_MAX         (0x00000001U)

/* RST_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_MCU_RESET_ISO_DONE_Z_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_MCU_RESET_ISO_DONE_Z_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_MCU_RESET_ISO_DONE_Z_MAX          (0x00000001U)

/* RST_SRC */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_MASK                 (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_RESET_PIN_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_MASK                (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_SHIFT               (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_RESET_REQ_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_MASK                   (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_SHIFT                  (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_THERMAL_RST_MAX                    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_MASK                     (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_SHIFT                    (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DEBUG_RST_MAX                      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_MASK                  (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_SHIFT                 (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_COLD_OUT_RST_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_MASK                  (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_SHIFT                 (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_WARM_OUT_RST_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_MASK                (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_SHIFT               (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MCU_WARMRST_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_MASK      (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_SHIFT     (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_MASK     (0x00200000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_SHIFT    (0x00000015U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_MASK                    (0x00400000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_SHIFT                   (0x00000016U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_DM_WDT_RST_MAX                     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_MASK          (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_SHIFT         (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MCU_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_MASK         (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_SHIFT        (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_SW_MAIN_POR_FROM_MAIN_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_MASK                (0x40000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_SHIFT               (0x0000001EU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MAIN_ESM_ERROR_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_MASK                 (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_SHIFT                (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_MCU_ESM_ERROR_MAX                  (0x00000001U)

/* RST_MAGIC_WORD */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_MCU_MAGIC_WORD_MAX          (0xFFFFFFFFU)

/* WKUP0_EN */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_WKUPEN_MASK                       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_WKUPEN_SHIFT                      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_WKUPEN_MAX                        (0xFFFFFFFFU)

/* CLKGATE_CTRL0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_MASK   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_MASK      (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_SHIFT     (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_MASK      (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_SHIFT     (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_MAX  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_MASK    (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_SHIFT   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_MASK      (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_SHIFT     (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_MASK       (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_SHIFT      (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_MASK   (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_SHIFT  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_MASK   (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_SHIFT  (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_MASK   (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_SHIFT  (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_MASK   (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_SHIFT  (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_MASK   (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_SHIFT  (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_MASK   (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_SHIFT  (0x0000000EU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_MASK      (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_SHIFT     (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_MASK        (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_SHIFT       (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_MASK       (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_SHIFT      (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_MASK       (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_SHIFT      (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_MASK       (0x00080000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_SHIFT      (0x00000013U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_MASK       (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_SHIFT      (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_MASK      (0x00400000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_SHIFT     (0x00000016U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_MASK     (0x00800000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_SHIFT    (0x00000017U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_MASK       (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_SHIFT      (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_MASK     (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_SHIFT    (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_MASK       (0x04000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_SHIFT      (0x0000001AU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_MASK     (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_SHIFT    (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_MASK       (0x20000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_SHIFT      (0x0000001DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SMS_NOGATE_MASK         (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SMS_NOGATE_SHIFT        (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_MAIN_SMS_NOGATE_MAX          (0x00000001U)

/* CLKGATE_CTRL1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_DMSS_CSI_NOGATE_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_DMSS_CSI_NOGATE_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_DMSS_CSI_NOGATE_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_MASK      (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_SHIFT     (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_JPEG_ENC_NOGATE_MASK         (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_JPEG_ENC_NOGATE_SHIFT        (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_JPEG_ENC_NOGATE_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_NOGATE_MASK              (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_NOGATE_SHIFT             (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_NOGATE_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_1_NOGATE_MASK            (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_1_NOGATE_SHIFT           (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_C7X_1_NOGATE_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VPAC0_NOGATE_MASK            (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VPAC0_NOGATE_SHIFT           (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_VPAC0_NOGATE_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_CSITX0_NOGATE_MASK           (0x00080000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_CSITX0_NOGATE_SHIFT          (0x00000013U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_CSITX0_NOGATE_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_RAM0_NOGATE_MASK             (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_RAM0_NOGATE_SHIFT            (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_RAM0_NOGATE_MAX              (0x00000001U)

/* CANUART_WAKE_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_LOAD_EN_MASK          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_LOAD_EN_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_LOAD_EN_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_MASK                  (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_SHIFT                 (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_MW_MAX                   (0x7FFFFFFFU)

/* CANUART_WAKE_STAT0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_LOAD_STAT_MASK       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_LOAD_STAT_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_LOAD_STAT_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_STAT_MASK            (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_STAT_SHIFT           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_MW_STAT_MAX             (0x7FFFFFFFU)

/* CANUART_WAKE_STAT1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_CANUART_IO_MODE_MASK    (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_CANUART_IO_MODE_SHIFT   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_CANUART_IO_MODE_MAX     (0x00000001U)

/* CANUART_WAKE_OFF_MODE */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_MW_MASK              (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_MW_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_MW_MAX               (0xFFFFFFFFU)

/* CANUART_WAKE_OFF_MODE_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_MW_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_MW_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_MW_MAX          (0xFFFFFFFFU)

/* CANUART_WAKE_RESUME_KEY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_KEYVAL_MASK        (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_KEYVAL_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_KEYVAL_MAX         (0xFFFFFFFFU)

/* CANUART_WAKE_RESUME_KEY_STAT */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_MAX    (0xFFFFFFFFU)

/* WFI_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_WKUP_R5F_WFI_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_WKUP_R5F_WFI_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_WKUP_R5F_WFI_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU0_WFI_MASK               (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU0_WFI_SHIFT              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU0_WFI_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU1_WFI_MASK               (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU1_WFI_SHIFT              (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_SMS_CPU1_WFI_MAX                (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MCU_R5F_WFI_MASK                (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MCU_R5F_WFI_SHIFT               (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MCU_R5F_WFI_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MAIN_R5F_0_WFI_MASK             (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MAIN_R5F_0_WFI_SHIFT            (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MAIN_R5F_0_WFI_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU0_WFI_MASK            (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU0_WFI_SHIFT           (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU0_WFI_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU1_WFI_MASK            (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU1_WFI_SHIFT           (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU1_WFI_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU2_WFI_MASK            (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU2_WFI_SHIFT           (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU2_WFI_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU3_WFI_MASK            (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU3_WFI_SHIFT           (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_MPUSS0_CPU3_WFI_MAX             (0x00000001U)

/* SLEEP_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_RESETSTATZ_MASK          (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_RESETSTATZ_SHIFT         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_RESETSTATZ_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_DS_MASK                  (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_DS_SHIFT                 (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_MAIN_DS_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_MASK             (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_SHIFT            (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_EXITED_SLEEP_MAX              (0x00000001U)

/* DS_MAGIC_WORD */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_DS_MAGIC_WORD_MASK           (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_DS_MAGIC_WORD_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_DS_MAGIC_WORD_MAX            (0xFFFFFFFFU)

/* DS_MAIN */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_POR_PDOFF_MASK                     (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_POR_PDOFF_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_POR_PDOFF_MAX                      (0x0000000FU)

/* DS_DM_RESET */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_MASK_MASK                      (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_MASK_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_MASK_MAX                       (0x0000000FU)

/* DS_USB0_RESET */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_MASK_MASK                    (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_MASK_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_MASK_MAX                     (0x0000000FU)

/* DS_USB1_RESET */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_MASK_MASK                    (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_MASK_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_MASK_MAX                     (0x0000000FU)

/* DM_CLKSTOP_EN */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_0_MASK                    (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_0_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_0_MAX                     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_3_MASK                    (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_3_SHIFT                   (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_3_MAX                     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_16_MASK                   (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_16_SHIFT                  (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_16_MAX                    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_17_MASK                   (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_17_SHIFT                  (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_EN_17_MAX                    (0x00000001U)

/* DM_CLKSTOP_ACK */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_0_MASK                  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_0_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_0_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_3_MASK                  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_3_SHIFT                 (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_3_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_16_MASK                 (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_16_SHIFT                (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_16_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_17_MASK                 (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_17_SHIFT                (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_ACK_17_MAX                  (0x00000001U)

/* DM_GRP_CLKSTOP_REQ */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_REQ_MASK                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_REQ_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_REQ_MAX                 (0x00000001U)

/* DM_GRP_CLKSTOP_ACK */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_ACK_MASK                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_ACK_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_ACK_MAX                 (0x00000001U)

/* DEVICE_TYPE */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_SMS_DEV_TYPE_MASK              (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_SMS_DEV_TYPE_SHIFT             (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_SMS_DEV_TYPE_MAX               (0x0000000FU)

/* LOCK6_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_LOCK6_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK6_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_LOCK6_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P6_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_READONLY_CLAIMREG_P6_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_READONLY_CLAIMREG_P6_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_READONLY_CLAIMREG_P6_R2_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R3_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_READONLY_CLAIMREG_P6_R3_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R4_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_READONLY_CLAIMREG_P6_R4_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R5_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_READONLY_CLAIMREG_P6_R5_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R6_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_READONLY_CLAIMREG_P6_R6_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R7_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_READONLY_CLAIMREG_P6_R7_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R8_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_READONLY_CLAIMREG_P6_R8_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R9_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_READONLY_CLAIMREG_P6_R9_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_READONLY_CLAIMREG_P6_R9_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_READONLY_CLAIMREG_P6_R9_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P6_R10_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_READONLY_CLAIMREG_P6_R10_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_READONLY_CLAIMREG_P6_R10_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_READONLY_CLAIMREG_P6_R10_READONLY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_PROXY_FW_CTRL_OUT0_FW_CTRL_OUT0_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_PROXY_FW_CTRL_OUT0_FW_CTRL_OUT0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_PROXY_FW_CTRL_OUT0_FW_CTRL_OUT0_PROXY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT0_SET_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_PROXY_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_PROXY_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_SET_PROXY_FW_CTRL_OUT0_SET_FW_CTRL_OUT0_PROXY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT0_CLR_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_PROXY_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_PROXY_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT0_CLR_PROXY_FW_CTRL_OUT0_CLR_FW_CTRL_OUT0_PROXY_MAX (0xFFFFFFFFU)

/* FW_STS_IN0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_PROXY_FW_STS_IN0_EVENT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_PROXY_FW_STS_IN0_EVENT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN0_PROXY_FW_STS_IN0_EVENT_PROXY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_PROXY_FW_CTRL_OUT1_FW_CTRL_OUT1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_PROXY_FW_CTRL_OUT1_FW_CTRL_OUT1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_PROXY_FW_CTRL_OUT1_FW_CTRL_OUT1_PROXY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT1_SET_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_PROXY_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_PROXY_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_SET_PROXY_FW_CTRL_OUT1_SET_FW_CTRL_OUT1_PROXY_MAX (0xFFFFFFFFU)

/* FW_CTRL_OUT1_CLR_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_PROXY_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_PROXY_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_CTRL_OUT1_CLR_PROXY_FW_CTRL_OUT1_CLR_FW_CTRL_OUT1_PROXY_MAX (0xFFFFFFFFU)

/* FW_STS_IN1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_PROXY_FW_STS_IN1_EVENT_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_PROXY_FW_STS_IN1_EVENT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FW_STS_IN1_PROXY_FW_STS_IN1_EVENT_PROXY_MAX (0xFFFFFFFFU)

/* PMCTRL_SYS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_PROXY_MASK (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_PROXY_MAX (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_WE_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_WE_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_LPM_EN_WE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_WE_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_WE_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_SYS_PROXY_PMCTRL_SYS_PMIC_EN_WE_PROXY_MAX (0x00000001U)

/* PMCTRL_IO_0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_OVRD_0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_OVRD_0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_OVRD_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_STATUS_0_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_STATUS_0_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOCLK_STATUS_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOOVR_EXTEND_0_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOOVR_EXTEND_0_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOOVR_EXTEND_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ON_STATUS_0_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ON_STATUS_0_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ON_STATUS_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOBYPASS_OVR_0_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOBYPASS_OVR_0_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_ISOBYPASS_OVR_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_CTRL_0_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_CTRL_0_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_CTRL_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_STATUS_0_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_STATUS_0_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_WUCLK_STATUS_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_GLOBAL_WUEN_0_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_GLOBAL_WUEN_0_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_GLOBAL_WUEN_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_CTRL_0_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_CTRL_0_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_CTRL_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_STATUS_0_PROXY_MASK (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_STATUS_0_PROXY_SHIFT (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_0_PROXY_PMCTRL_IO_0_IO_ISO_STATUS_0_PROXY_MAX (0x00000001U)

/* PMCTRL_IO_1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_OVRD_1_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_OVRD_1_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_OVRD_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_STATUS_1_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_STATUS_1_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOCLK_STATUS_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOOVR_EXTEND_1_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOOVR_EXTEND_1_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOOVR_EXTEND_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ON_STATUS_1_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ON_STATUS_1_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ON_STATUS_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOBYPASS_OVR_1_PROXY_MASK (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOBYPASS_OVR_1_PROXY_SHIFT (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_ISOBYPASS_OVR_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_CTRL_1_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_CTRL_1_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_CTRL_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_STATUS_1_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_STATUS_1_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_WUCLK_STATUS_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_GLOBAL_WUEN_1_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_GLOBAL_WUEN_1_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_GLOBAL_WUEN_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_CTRL_1_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_CTRL_1_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_CTRL_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_STATUS_1_PROXY_MASK (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_STATUS_1_PROXY_SHIFT (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_IO_ISO_STATUS_1_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_RESERVED4_PROXY_MASK (0xFC000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_RESERVED4_PROXY_SHIFT (0x0000001AU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_1_PROXY_PMCTRL_IO_1_RESERVED4_PROXY_MAX (0x0000003FU)

/* PMCTRL_MOSC_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_SETUP_TIME_PROXY_MASK (0x000FFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_SETUP_TIME_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_SETUP_TIME_PROXY_MAX (0x000FFFFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_OSC_CG_ON_WFI_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_OSC_CG_ON_WFI_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_MOSC_PROXY_PMCTRL_MOSC_OSC_CG_ON_WFI_PROXY_MAX (0x00000001U)

/* PM_MISC_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_PROXY_PM_MISC_STATUS_OSC_CG_STAT_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_PROXY_PM_MISC_STATUS_OSC_CG_STAT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_MISC_STATUS_PROXY_PM_MISC_STATUS_OSC_CG_STAT_PROXY_MAX (0x00000003U)

/* PMCTRL_IO_GLB_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_PROXY_PMCTRL_IO_GLB_DSEN_QUALIFIED_PROXY_MASK (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_PROXY_PMCTRL_IO_GLB_DSEN_QUALIFIED_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PMCTRL_IO_GLB_PROXY_PMCTRL_IO_GLB_DSEN_QUALIFIED_PROXY_MAX (0x00000003U)

/* PM_PERMISSION_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_DEBUG_ACTIVE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_DEBUG_ACTIVE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_DEBUG_ACTIVE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_SECURITY_ACTIVE_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_SECURITY_ACTIVE_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_SECURITY_ACTIVE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_MCU_SAFETY_ACTIVE_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_MCU_SAFETY_ACTIVE_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_PM_PERMISSION_PROXY_PM_PERMISSION_MCU_SAFETY_ACTIVE_PROXY_MAX (0x00000001U)

/* DEEPSLEEP_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_WKUP_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_WKUP_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_WKUP_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_MAIN_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_MAIN_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL_PROXY_DEEPSLEEP_CTRL_FORCE_DS_MAIN_PROXY_MAX (0x00000001U)

/* RST_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_WARMRST_PROXY_MAX (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_MASK (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SW_MAIN_POR_PROXY_MAX (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_SMS_COLD_RESET_EN_Z_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_ESM_ERROR_RST_EN_Z_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_RESET_ISO_DONE_Z_PROXY_MASK (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_RESET_ISO_DONE_Z_PROXY_SHIFT (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_CTRL_PROXY_RST_CTRL_MAIN_RESET_ISO_DONE_Z_PROXY_MAX (0x00000001U)

/* RST_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MCU_RESET_ISO_DONE_Z_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MCU_RESET_ISO_DONE_Z_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_STAT_PROXY_RST_STAT_MCU_RESET_ISO_DONE_Z_PROXY_MAX (0x00000001U)

/* RST_SRC_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MCU_RESET_PIN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_RESET_REQ_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_THERMAL_RST_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DEBUG_RST_PROXY_MAX  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_COLD_OUT_RST_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_MASK (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_SHIFT (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_WARM_OUT_RST_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MCU_WARMRST_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_MASK (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_SHIFT (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MCU_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_MASK (0x00200000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_SHIFT (0x00000015U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_WARMRST_FROM_MAIN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_MASK (0x00400000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_SHIFT (0x00000016U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_DM_WDT_RST_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MCU_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_MASK (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_SHIFT (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SW_MAIN_POR_FROM_MAIN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_MASK (0x40000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_SHIFT (0x0000001EU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_MAIN_ESM_ERROR_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_SRC_PROXY_RST_SRC_SAFETY_ERROR_PROXY_MAX (0x00000001U)

/* RST_MAGIC_WORD_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_RST_MAGIC_WORD_PROXY_RST_MAGIC_WORD_MCU_MAGIC_WORD_PROXY_MAX (0xFFFFFFFFU)

/* WKUP0_EN_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_PROXY_WKUP0_EN_WKUPEN_PROXY_MASK  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_PROXY_WKUP0_EN_WKUPEN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WKUP0_EN_PROXY_WKUP0_EN_WKUPEN_PROXY_MAX   (0xFFFFFFFFU)

/* CLKGATE_CTRL0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_INFRA_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_PROXY_MASK (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_WKUP_DM_PWR_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_CENTRAL_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DATA_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_PROXY_MASK (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_PROXY_SHIFT (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_PROXY_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_PROXY_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MISC_PERI_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_MCASP_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_PROXY_MASK (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_PROXY_SHIFT (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_IPCSS_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_PROXY_MASK (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_PROXY_SHIFT (0x0000000EU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_AUDIO_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_PROXY_MASK (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_PROXY_SHIFT (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_PROXY_MASK (0x00080000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_PROXY_SHIFT (0x00000013U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_PROXY_MASK (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_PROXY_SHIFT (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_PDMA3_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_PROXY_MASK (0x00400000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_PROXY_SHIFT (0x00000016U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_CFG_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_PROXY_MASK (0x00800000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_PROXY_SHIFT (0x00000017U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_DATA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_RT_FW_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_PROXY_MASK (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_PROXY_SHIFT (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MCU_FW_CBASS_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_PROXY_MASK (0x04000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_PROXY_SHIFT (0x0000001AU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_R5F_0_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_PROXY_MASK (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_PROXY_SHIFT (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_PROXY_MASK (0x20000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_PROXY_SHIFT (0x0000001DU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SA3SS_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SMS_NOGATE_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SMS_NOGATE_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0_PROXY_CLKGATE_CTRL0_MAIN_SMS_NOGATE_PROXY_MAX (0x00000001U)

/* CLKGATE_CTRL1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_DMSS_CSI_NOGATE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_DMSS_CSI_NOGATE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_DMSS_CSI_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VIDEO_CODEC_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_JPEG_ENC_NOGATE_PROXY_MASK (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_JPEG_ENC_NOGATE_PROXY_SHIFT (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_JPEG_ENC_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_NOGATE_PROXY_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_NOGATE_PROXY_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_1_NOGATE_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_1_NOGATE_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_C7X_1_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VPAC0_NOGATE_PROXY_MASK (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VPAC0_NOGATE_PROXY_SHIFT (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_VPAC0_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_CSITX0_NOGATE_PROXY_MASK (0x00080000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_CSITX0_NOGATE_PROXY_SHIFT (0x00000013U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_CSITX0_NOGATE_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_RAM0_NOGATE_PROXY_MASK (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_RAM0_NOGATE_PROXY_SHIFT (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1_PROXY_CLKGATE_CTRL1_RAM0_NOGATE_PROXY_MAX (0x00000001U)

/* CANUART_WAKE_CTRL_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_LOAD_EN_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_LOAD_EN_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_LOAD_EN_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_PROXY_MASK (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL_PROXY_CANUART_WAKE_CTRL_MW_PROXY_MAX (0x7FFFFFFFU)

/* CANUART_WAKE_STAT0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_LOAD_STAT_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_LOAD_STAT_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_LOAD_STAT_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_STAT_PROXY_MASK (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_STAT_PROXY_SHIFT (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT0_PROXY_CANUART_WAKE_STAT0_MW_STAT_PROXY_MAX (0x7FFFFFFFU)

/* CANUART_WAKE_STAT1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_PROXY_CANUART_WAKE_STAT1_CANUART_IO_MODE_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_PROXY_CANUART_WAKE_STAT1_CANUART_IO_MODE_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_STAT1_PROXY_CANUART_WAKE_STAT1_CANUART_IO_MODE_PROXY_MAX (0x00000001U)

/* CANUART_WAKE_OFF_MODE_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_PROXY_CANUART_WAKE_OFF_MODE_MW_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_PROXY_CANUART_WAKE_OFF_MODE_MW_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_PROXY_CANUART_WAKE_OFF_MODE_MW_PROXY_MAX (0xFFFFFFFFU)

/* CANUART_WAKE_OFF_MODE_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_PROXY_CANUART_WAKE_OFF_MODE_STAT_MW_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_PROXY_CANUART_WAKE_OFF_MODE_STAT_MW_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT_PROXY_CANUART_WAKE_OFF_MODE_STAT_MW_PROXY_MAX (0xFFFFFFFFU)

/* CANUART_WAKE_RESUME_KEY_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_PROXY_KEYVAL_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_PROXY_KEYVAL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_PROXY_KEYVAL_PROXY_MAX (0xFFFFFFFFU)

/* CANUART_WAKE_RESUME_KEY_STAT_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_PROXY_KEYVAL_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_PROXY_KEYVAL_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_RESUME_KEY_STAT_PROXY_KEYVAL_PROXY_MAX (0xFFFFFFFFU)

/* WFI_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_WKUP_R5F_WFI_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_WKUP_R5F_WFI_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_WKUP_R5F_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU0_WFI_PROXY_MASK (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU0_WFI_PROXY_SHIFT (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU0_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU1_WFI_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU1_WFI_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_SMS_CPU1_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MCU_R5F_WFI_PROXY_MASK (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MCU_R5F_WFI_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MCU_R5F_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MAIN_R5F_0_WFI_PROXY_MASK (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MAIN_R5F_0_WFI_PROXY_SHIFT (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MAIN_R5F_0_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU0_WFI_PROXY_MASK (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU0_WFI_PROXY_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU0_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU1_WFI_PROXY_MASK (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU1_WFI_PROXY_SHIFT (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU1_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU2_WFI_PROXY_MASK (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU2_WFI_PROXY_SHIFT (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU2_WFI_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU3_WFI_PROXY_MASK (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU3_WFI_PROXY_SHIFT (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_WFI_STATUS_PROXY_WFI_STATUS_MPUSS0_CPU3_WFI_PROXY_MAX (0x00000001U)

/* SLEEP_STATUS_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_RESETSTATZ_PROXY_MASK (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_RESETSTATZ_PROXY_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_RESETSTATZ_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_DS_PROXY_MASK (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_DS_PROXY_SHIFT (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_MAIN_DS_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_MASK (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_SHIFT (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_SLEEP_STATUS_PROXY_SLEEP_STATUS_EXITED_SLEEP_PROXY_MAX (0x00000001U)

/* DS_MAGIC_WORD_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_PROXY_DS_MAGIC_WORD_DS_MAGIC_WORD_PROXY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_PROXY_DS_MAGIC_WORD_DS_MAGIC_WORD_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAGIC_WORD_PROXY_DS_MAGIC_WORD_DS_MAGIC_WORD_PROXY_MAX (0xFFFFFFFFU)

/* DS_MAIN_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_PROXY_DS_MAIN_POR_PDOFF_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_PROXY_DS_MAIN_POR_PDOFF_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_MAIN_PROXY_DS_MAIN_POR_PDOFF_PROXY_MAX  (0x0000000FU)

/* DS_DM_RESET_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_PROXY_DS_DM_RESET_MASK_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_PROXY_DS_DM_RESET_MASK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_DM_RESET_PROXY_DS_DM_RESET_MASK_PROXY_MAX (0x0000000FU)

/* DS_USB0_RESET_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_PROXY_DS_USB0_RESET_MASK_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_PROXY_DS_USB0_RESET_MASK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB0_RESET_PROXY_DS_USB0_RESET_MASK_PROXY_MAX (0x0000000FU)

/* DS_USB1_RESET_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_PROXY_DS_USB1_RESET_MASK_PROXY_MASK (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_PROXY_DS_USB1_RESET_MASK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DS_USB1_RESET_PROXY_DS_USB1_RESET_MASK_PROXY_MAX (0x0000000FU)

/* DM_CLKSTOP_EN_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_16_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_16_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_16_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_17_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_17_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_EN_PROXY_DM_CLKSTOP_EN_EN_17_PROXY_MAX (0x00000001U)

/* DM_CLKSTOP_ACK_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_0_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_0_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_0_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_3_PROXY_MASK (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_3_PROXY_SHIFT (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_3_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_16_PROXY_MASK (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_16_PROXY_SHIFT (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_16_PROXY_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_17_PROXY_MASK (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_17_PROXY_SHIFT (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_CLKSTOP_ACK_PROXY_DM_CLKSTOP_ACK_ACK_17_PROXY_MAX (0x00000001U)

/* DM_GRP_CLKSTOP_REQ_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_PROXY_DM_GRP_CLKSTOP_REQ_REQ_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_PROXY_DM_GRP_CLKSTOP_REQ_REQ_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_REQ_PROXY_DM_GRP_CLKSTOP_REQ_REQ_PROXY_MAX (0x00000001U)

/* DM_GRP_CLKSTOP_ACK_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_PROXY_DM_GRP_CLKSTOP_ACK_ACK_PROXY_MASK (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_PROXY_DM_GRP_CLKSTOP_ACK_ACK_PROXY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DM_GRP_CLKSTOP_ACK_PROXY_DM_GRP_CLKSTOP_ACK_ACK_PROXY_MAX (0x00000001U)

/* DEVICE_TYPE_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_PROXY_DEVICE_TYPE_SMS_DEV_TYPE_PROXY_MASK (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_PROXY_DEVICE_TYPE_SMS_DEV_TYPE_PROXY_SHIFT (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_TYPE_PROXY_DEVICE_TYPE_SMS_DEV_TYPE_PROXY_MAX (0x0000000FU)

/* LOCK6_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0_PROXY_LOCK6_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK6_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1_PROXY_LOCK6_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P6_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R0_CLAIMREG_P6_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R1_CLAIMREG_P6_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R2_CLAIMREG_P6_R2_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R3 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R3_CLAIMREG_P6_R3_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R4 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R4_CLAIMREG_P6_R4_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R5 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R5_CLAIMREG_P6_R5_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R6 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R6_CLAIMREG_P6_R6_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R7 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R7_CLAIMREG_P6_R7_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R8 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R8_CLAIMREG_P6_R8_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R9 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_CLAIMREG_P6_R9_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_CLAIMREG_P6_R9_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R9_CLAIMREG_P6_R9_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P6_R10 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_CLAIMREG_P6_R10_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_CLAIMREG_P6_R10_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P6_R10_CLAIMREG_P6_R10_MAX        (0xFFFFFFFFU)

/* BACKUP_REG */

#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_BACKUP_DATA_MASK                (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_BACKUP_DATA_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_BACKUP_DATA_MAX                 (0xFFFFFFFFU)

/* LOCK7_KICK0 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_LOCK7_KICK0_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_LOCK7_KICK0_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_LOCK7_KICK0_MAX                (0xFFFFFFFFU)

/* LOCK7_KICK1 */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_LOCK7_KICK1_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_LOCK7_KICK1_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_LOCK7_KICK1_MAX                (0xFFFFFFFFU)

/* CLAIMREG_P7_R0_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_READONLY_CLAIMREG_P7_R0_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_READONLY_CLAIMREG_P7_R0_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_READONLY_CLAIMREG_P7_R0_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P7_R1_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_READONLY_CLAIMREG_P7_R1_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_READONLY_CLAIMREG_P7_R1_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_READONLY_CLAIMREG_P7_R1_READONLY_MAX (0xFFFFFFFFU)

/* CLAIMREG_P7_R2_READONLY */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_READONLY_CLAIMREG_P7_R2_READONLY_MASK (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_READONLY_CLAIMREG_P7_R2_READONLY_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_READONLY_CLAIMREG_P7_R2_READONLY_MAX (0xFFFFFFFFU)

/* BACKUP_REG_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_PROXY_BACKUP_DATA_PROXY_MASK    (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_PROXY_BACKUP_DATA_PROXY_SHIFT   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG_PROXY_BACKUP_DATA_PROXY_MAX     (0xFFFFFFFFU)

/* LOCK7_KICK0_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_PROXY_LOCK7_KICK0_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_PROXY_LOCK7_KICK0_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK0_PROXY_LOCK7_KICK0_PROXY_MAX    (0xFFFFFFFFU)

/* LOCK7_KICK1_PROXY */

#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_PROXY_LOCK7_KICK1_PROXY_MASK   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_PROXY_LOCK7_KICK1_PROXY_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_LOCK7_KICK1_PROXY_LOCK7_KICK1_PROXY_MAX    (0xFFFFFFFFU)

/* CLAIMREG_P7_R0 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_CLAIMREG_P7_R0_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_CLAIMREG_P7_R0_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R0_CLAIMREG_P7_R0_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P7_R1 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_CLAIMREG_P7_R1_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_CLAIMREG_P7_R1_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R1_CLAIMREG_P7_R1_MAX          (0xFFFFFFFFU)

/* CLAIMREG_P7_R2 */

#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_CLAIMREG_P7_R2_MASK         (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_CLAIMREG_P7_R2_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_CLAIMREG_P7_R2_CLAIMREG_P7_R2_MAX          (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif
