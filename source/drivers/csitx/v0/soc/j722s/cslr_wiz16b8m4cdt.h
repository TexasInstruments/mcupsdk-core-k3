/********************************************************************
 * Copyright (C) 2020-25 Texas Instruments Incorporated.
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
 *  Name        : cslr_wiz16b8m4cdt.h
*/
#ifndef CSLR_WIZ16B8M4CDT_H_
#define CSLR_WIZ16B8M4CDT_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_WIZ16B8M4CDT_REGS_BASE                                             (0x00000000U)


/**************************************************************************
* Hardware Region  : wiz16b8m4cdt registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CMN0_CMN_ANA_TBIT0;
    volatile uint32_t CMN0_CMN_ANA_TBIT1;
    volatile uint32_t CMN0_CMN_ANA_TBIT2;
    volatile uint32_t CMN0_CMN_ANA_TBIT3;
    volatile uint32_t CMN0_CMN_ANA_TBIT4;
    volatile uint32_t CMN0_CMN_ANA_TBIT5;
    volatile uint32_t CMN0_CMN_DIG_TBIT0;
    volatile uint32_t CMN0_CMN_DIG_TBIT1;
    volatile uint32_t CMN0_CMN_DIG_TBIT2;
    volatile uint32_t CMN0_CMN_DIG_TBIT3;
    volatile uint32_t CMN0_CMN_DIG_TBIT4;
    volatile uint32_t CMN0_CMN_DIG_TBIT5;
    volatile uint32_t CMN0_CMN_DIG_TBIT6;
    volatile uint32_t CMN0_CMN_DIG_TBIT7;
    volatile uint32_t CMN0_CMN_DIG_TBIT8;
    volatile uint32_t CMN0_CMN_DIG_TBIT9;
    volatile uint32_t CMN0_CMN_DIG_TBIT10;
    volatile uint32_t CMN0_CMN_DIG_TBIT11;
    volatile uint32_t CMN0_CMN_DIG_TBIT12;
    volatile uint32_t CMN0_CMN_DIG_TBIT13;
    volatile uint32_t CMN0_CMN_DIG_TBIT14;
    volatile uint8_t  Resv_104[20];
    volatile uint32_t CMN0_CMN_DIG_TBIT20;
    volatile uint32_t CMN0_CMN_DIG_TBIT21;
    volatile uint32_t CMN0_CMN_DIG_TBIT22;
    volatile uint32_t CMN0_CMN_DIG_TBIT23;
    volatile uint32_t CMN0_CMN_DIG_TBIT24;
    volatile uint32_t CMN0_CMN_DIG_TBIT25;
    volatile uint32_t CMN0_CMN_DIG_TBIT26;
    volatile uint32_t CMN0_CMN_DIG_TBIT27;
    volatile uint32_t CMN0_CMN_DIG_TBIT28;
    volatile uint8_t  Resv_148[8];
    volatile uint32_t CMN0_CMN_DIG_TBIT31;
    volatile uint32_t CMN0_CMN_DIG_TBIT32;
    volatile uint32_t CMN0_CMN_DIG_TBIT33;
    volatile uint32_t CMN0_CMN_DIG_TBIT34;
    volatile uint32_t CMN0_CMN_DIG_TBIT35;
    volatile uint32_t CMN0_CMN_DIG_TBIT36;
    volatile uint32_t CMN0_CMN_DIG_TBIT37;
    volatile uint8_t  Resv_180[4];
    volatile uint32_t CMN0_CMN_DIG_TBIT39;
    volatile uint8_t  Resv_216[32];
    volatile uint32_t CMN0_CMN_DIG_TBIT50;
    volatile uint8_t  Resv_228[8];
    volatile uint32_t CMN0_CMN_DIG_TBIT53;
    volatile uint32_t CMN0_CMN_DIG_TBIT54;
    volatile uint8_t  Resv_240[4];
    volatile uint32_t CMN0_CMN_DIG_TBIT56;
    volatile uint8_t  Resv_248[4];
    volatile uint32_t CMN0_CMN_DIG_TBIT58;
    volatile uint8_t  Resv_256[4];
    volatile uint32_t CLK0_TX_ANA_TBIT0;
    volatile uint32_t CLK0_TX_ANA_TBIT1;
    volatile uint32_t CLK0_TX_ANA_TBIT2;
    volatile uint32_t CLK0_TX_ANA_TBIT3;
    volatile uint32_t CLK0_TX_ANA_TBIT4;
    volatile uint8_t  Resv_284[8];
    volatile uint32_t CLK0_TX_DIG_TBIT0;
    volatile uint32_t CLK0_TX_DIG_TBIT1;
    volatile uint32_t CLK0_TX_DIG_TBIT2;
    volatile uint8_t  Resv_316[20];
    volatile uint32_t CLK0_TX_DIG_TBIT8;
    volatile uint32_t CLK0_TX_DIG_TBIT9;
    volatile uint32_t CLK0_TX_DIG_TBIT10;
    volatile uint8_t  Resv_340[12];
    volatile uint32_t CLK0_TX_DIG_TBIT14;
    volatile uint32_t CLK0_TX_DIG_TBIT15;
    volatile uint32_t CLK0_TX_DIG_TBIT16;
    volatile uint32_t CLK0_TX_DIG_TBIT17;
    volatile uint32_t CLK0_TX_DIG_TBIT18;
    volatile uint32_t CLK0_TX_DIG_TBIT19;
    volatile uint32_t CLK0_TX_DIG_TBIT20;
    volatile uint32_t CLK0_TX_ANA_TBIT5;
    volatile uint8_t  Resv_380[8];
    volatile uint32_t CLK0_TX_DIG_TBIT21;
    volatile uint32_t CLK0_TX_DIG_TBIT22;
    volatile uint8_t  Resv_392[4];
    volatile uint32_t CLK0_TX_DIG_TBIT24;
    volatile uint32_t CLK0_TX_DIG_TBIT25;
    volatile uint32_t CLK0_TX_DIG_TBIT26;
    volatile uint32_t CLK0_TX_DIG_TBIT27;
    volatile uint32_t CLK0_TX_DIG_TBIT28;
    volatile uint32_t CLK0_TX_DIG_TBIT29;
    volatile uint8_t  Resv_512[96];
    volatile uint32_t DL0_TX_ANA_TBIT0;
    volatile uint32_t DL0_TX_ANA_TBIT1;
    volatile uint32_t DL0_TX_ANA_TBIT2;
    volatile uint32_t DL0_TX_ANA_TBIT3;
    volatile uint32_t DL0_TX_ANA_TBIT4;
    volatile uint8_t  Resv_540[8];
    volatile uint32_t DL0_TX_DIG_TBIT0;
    volatile uint32_t DL0_TX_DIG_TBIT1;
    volatile uint32_t DL0_TX_DIG_TBIT2;
    volatile uint32_t DL0_TX_DIG_TBIT3;
    volatile uint32_t DL0_TX_DIG_TBIT4;
    volatile uint32_t DL0_TX_DIG_TBIT5;
    volatile uint32_t DL0_TX_DIG_TBIT6;
    volatile uint32_t DL0_TX_DIG_TBIT7;
    volatile uint32_t DL0_TX_DIG_TBIT8;
    volatile uint32_t DL0_TX_DIG_TBIT9;
    volatile uint32_t DL0_TX_DIG_TBIT10;
    volatile uint32_t DL0_TX_DIG_TBIT11;
    volatile uint32_t DL0_TX_DIG_TBIT12;
    volatile uint32_t DL0_TX_DIG_TBIT13;
    volatile uint32_t DL0_TX_DIG_TBIT14;
    volatile uint32_t DL0_TX_DIG_TBIT15;
    volatile uint32_t DL0_TX_DIG_TBIT16;
    volatile uint32_t DL0_TX_DIG_TBIT17;
    volatile uint32_t DL0_TX_DIG_TBIT18;
    volatile uint32_t DL0_TX_DIG_TBIT19;
    volatile uint32_t DL0_TX_DIG_TBIT20;
    volatile uint32_t DL0_TX_DIG_TBIT21;
    volatile uint32_t DL0_TX_DIG_TBIT22;
    volatile uint32_t DL0_TX_DIG_TBIT23;
    volatile uint32_t DL0_TX_DIG_TBIT24;
    volatile uint32_t DL0_TX_ANA_TBIT5;
    volatile uint8_t  Resv_652[8];
    volatile uint32_t DL0_TX_DIG_TBIT25;
    volatile uint32_t DL0_TX_DIG_TBIT26;
    volatile uint8_t  Resv_664[4];
    volatile uint32_t DL0_TX_DIG_TBIT28;
    volatile uint32_t DL0_TX_DIG_TBIT29;
    volatile uint32_t DL0_TX_DIG_TBIT30;
    volatile uint32_t DL0_TX_DIG_TBIT31;
    volatile uint32_t DL0_TX_DIG_TBIT32;
    volatile uint32_t DL0_TX_DIG_TBIT33;
    volatile uint32_t DL0_TX_DIG_TBIT34;
    volatile uint32_t DL0_TX_DIG_TBIT35;
    volatile uint32_t DL0_TX_DIG_TBIT36;
    volatile uint8_t  Resv_768[68];
    volatile uint32_t DL1_TX_ANA_TBIT0;
    volatile uint32_t DL1_TX_ANA_TBIT1;
    volatile uint32_t DL1_TX_ANA_TBIT2;
    volatile uint32_t DL1_TX_ANA_TBIT3;
    volatile uint32_t DL1_TX_ANA_TBIT4;
    volatile uint8_t  Resv_796[8];
    volatile uint32_t DL1_TX_DIG_TBIT0;
    volatile uint32_t DL1_TX_DIG_TBIT1;
    volatile uint32_t DL1_TX_DIG_TBIT2;
    volatile uint32_t DL1_TX_DIG_TBIT3;
    volatile uint32_t DL1_TX_DIG_TBIT4;
    volatile uint32_t DL1_TX_DIG_TBIT5;
    volatile uint32_t DL1_TX_DIG_TBIT6;
    volatile uint32_t DL1_TX_DIG_TBIT7;
    volatile uint32_t DL1_TX_DIG_TBIT8;
    volatile uint32_t DL1_TX_DIG_TBIT9;
    volatile uint32_t DL1_TX_DIG_TBIT10;
    volatile uint32_t DL1_TX_DIG_TBIT11;
    volatile uint32_t DL1_TX_DIG_TBIT12;
    volatile uint32_t DL1_TX_DIG_TBIT13;
    volatile uint32_t DL1_TX_DIG_TBIT14;
    volatile uint32_t DL1_TX_DIG_TBIT15;
    volatile uint32_t DL1_TX_DIG_TBIT16;
    volatile uint32_t DL1_TX_DIG_TBIT17;
    volatile uint32_t DL1_TX_DIG_TBIT18;
    volatile uint32_t DL1_TX_DIG_TBIT19;
    volatile uint32_t DL1_TX_DIG_TBIT20;
    volatile uint32_t DL1_TX_DIG_TBIT21;
    volatile uint32_t DL1_TX_DIG_TBIT22;
    volatile uint32_t DL1_TX_DIG_TBIT23;
    volatile uint32_t DL1_TX_DIG_TBIT24;
    volatile uint32_t DL1_TX_ANA_TBIT5;
    volatile uint8_t  Resv_908[8];
    volatile uint32_t DL1_TX_DIG_TBIT25;
    volatile uint32_t DL1_TX_DIG_TBIT26;
    volatile uint8_t  Resv_920[4];
    volatile uint32_t DL1_TX_DIG_TBIT28;
    volatile uint32_t DL1_TX_DIG_TBIT29;
    volatile uint32_t DL1_TX_DIG_TBIT30;
    volatile uint32_t DL1_TX_DIG_TBIT31;
    volatile uint32_t DL1_TX_DIG_TBIT32;
    volatile uint32_t DL1_TX_DIG_TBIT33;
    volatile uint32_t DL1_TX_DIG_TBIT34;
    volatile uint32_t DL1_TX_DIG_TBIT35;
    volatile uint32_t DL1_TX_DIG_TBIT36;
    volatile uint8_t  Resv_1024[68];
    volatile uint32_t DL2_TX_ANA_TBIT0;
    volatile uint32_t DL2_TX_ANA_TBIT1;
    volatile uint32_t DL2_TX_ANA_TBIT2;
    volatile uint32_t DL2_TX_ANA_TBIT3;
    volatile uint32_t DL2_TX_ANA_TBIT4;
    volatile uint8_t  Resv_1052[8];
    volatile uint32_t DL2_TX_DIG_TBIT0;
    volatile uint32_t DL2_TX_DIG_TBIT1;
    volatile uint32_t DL2_TX_DIG_TBIT2;
    volatile uint32_t DL2_TX_DIG_TBIT3;
    volatile uint32_t DL2_TX_DIG_TBIT4;
    volatile uint32_t DL2_TX_DIG_TBIT5;
    volatile uint32_t DL2_TX_DIG_TBIT6;
    volatile uint32_t DL2_TX_DIG_TBIT7;
    volatile uint32_t DL2_TX_DIG_TBIT8;
    volatile uint32_t DL2_TX_DIG_TBIT9;
    volatile uint32_t DL2_TX_DIG_TBIT10;
    volatile uint32_t DL2_TX_DIG_TBIT11;
    volatile uint32_t DL2_TX_DIG_TBIT12;
    volatile uint32_t DL2_TX_DIG_TBIT13;
    volatile uint32_t DL2_TX_DIG_TBIT14;
    volatile uint32_t DL2_TX_DIG_TBIT15;
    volatile uint32_t DL2_TX_DIG_TBIT16;
    volatile uint32_t DL2_TX_DIG_TBIT17;
    volatile uint32_t DL2_TX_DIG_TBIT18;
    volatile uint32_t DL2_TX_DIG_TBIT19;
    volatile uint32_t DL2_TX_DIG_TBIT20;
    volatile uint32_t DL2_TX_DIG_TBIT21;
    volatile uint32_t DL2_TX_DIG_TBIT22;
    volatile uint32_t DL2_TX_DIG_TBIT23;
    volatile uint32_t DL2_TX_DIG_TBIT24;
    volatile uint32_t DL2_TX_ANA_TBIT5;
    volatile uint8_t  Resv_1164[8];
    volatile uint32_t DL2_TX_DIG_TBIT25;
    volatile uint32_t DL2_TX_DIG_TBIT26;
    volatile uint8_t  Resv_1176[4];
    volatile uint32_t DL2_TX_DIG_TBIT28;
    volatile uint32_t DL2_TX_DIG_TBIT29;
    volatile uint32_t DL2_TX_DIG_TBIT30;
    volatile uint32_t DL2_TX_DIG_TBIT31;
    volatile uint32_t DL2_TX_DIG_TBIT32;
    volatile uint32_t DL2_TX_DIG_TBIT33;
    volatile uint32_t DL2_TX_DIG_TBIT34;
    volatile uint32_t DL2_TX_DIG_TBIT35;
    volatile uint32_t DL2_TX_DIG_TBIT36;
    volatile uint8_t  Resv_1280[68];
    volatile uint32_t DL3_TX_ANA_TBIT0;
    volatile uint32_t DL3_TX_ANA_TBIT1;
    volatile uint32_t DL3_TX_ANA_TBIT2;
    volatile uint32_t DL3_TX_ANA_TBIT3;
    volatile uint32_t DL3_TX_ANA_TBIT4;
    volatile uint8_t  Resv_1308[8];
    volatile uint32_t DL3_TX_DIG_TBIT0;
    volatile uint32_t DL3_TX_DIG_TBIT1;
    volatile uint32_t DL3_TX_DIG_TBIT2;
    volatile uint32_t DL3_TX_DIG_TBIT3;
    volatile uint32_t DL3_TX_DIG_TBIT4;
    volatile uint32_t DL3_TX_DIG_TBIT5;
    volatile uint32_t DL3_TX_DIG_TBIT6;
    volatile uint32_t DL3_TX_DIG_TBIT7;
    volatile uint32_t DL3_TX_DIG_TBIT8;
    volatile uint32_t DL3_TX_DIG_TBIT9;
    volatile uint32_t DL3_TX_DIG_TBIT10;
    volatile uint32_t DL3_TX_DIG_TBIT11;
    volatile uint32_t DL3_TX_DIG_TBIT12;
    volatile uint32_t DL3_TX_DIG_TBIT13;
    volatile uint32_t DL3_TX_DIG_TBIT14;
    volatile uint32_t DL3_TX_DIG_TBIT15;
    volatile uint32_t DL3_TX_DIG_TBIT16;
    volatile uint32_t DL3_TX_DIG_TBIT17;
    volatile uint32_t DL3_TX_DIG_TBIT18;
    volatile uint32_t DL3_TX_DIG_TBIT19;
    volatile uint32_t DL3_TX_DIG_TBIT20;
    volatile uint32_t DL3_TX_DIG_TBIT21;
    volatile uint32_t DL3_TX_DIG_TBIT22;
    volatile uint32_t DL3_TX_DIG_TBIT23;
    volatile uint32_t DL3_TX_DIG_TBIT24;
    volatile uint32_t DL3_TX_ANA_TBIT5;
    volatile uint8_t  Resv_1420[8];
    volatile uint32_t DL3_TX_DIG_TBIT25;
    volatile uint32_t DL3_TX_DIG_TBIT26;
    volatile uint8_t  Resv_1432[4];
    volatile uint32_t DL3_TX_DIG_TBIT28;
    volatile uint32_t DL3_TX_DIG_TBIT29;
    volatile uint32_t DL3_TX_DIG_TBIT30;
    volatile uint32_t DL3_TX_DIG_TBIT31;
    volatile uint32_t DL3_TX_DIG_TBIT32;
    volatile uint32_t DL3_TX_DIG_TBIT33;
    volatile uint32_t DL3_TX_DIG_TBIT34;
    volatile uint32_t DL3_TX_DIG_TBIT35;
    volatile uint32_t DL3_TX_DIG_TBIT36;
    volatile uint8_t  Resv_2816[1348];
    volatile uint32_t PCS_TX_DIG_TBIT0;
    volatile uint32_t PCS_TX_DIG_TBIT1;
    volatile uint32_t PCS_TX_DIG_TBIT2;
    volatile uint32_t PCS_TX_DIG_TBIT3;
    volatile uint32_t PCS_TX_DIG_TBIT4;
    volatile uint32_t PCS_TX_DIG_TBIT5;
    volatile uint32_t PCS_TX_DIG_TBIT6;
    volatile uint32_t PCS_TX_DIG_TBIT7;
    volatile uint32_t PCS_TX_DIG_TBIT8;
    volatile uint32_t PCS_TX_DIG_TBIT9;
    volatile uint32_t PCS_TX_DIG_TBIT10;
    volatile uint8_t  Resv_3072[212];
    volatile uint32_t ISO_PHY_ISO_CNTRL;
    volatile uint32_t ISO_PHY_ISO_RESET;
    volatile uint32_t ISO_PHY_ISO_ENABLE;
    volatile uint32_t ISO_PHY_ISO_CMN_CTRL;
    volatile uint32_t ISO_PHY_ISO_CMN_PLL;
    volatile uint32_t ISO_PHY_ISO_CL_CNTRL_L;
    volatile uint32_t ISO_PHY_ISO_DL_CTRL_L0;
    volatile uint32_t ISO_PHY_ISO_DL_HS_L0;
    volatile uint32_t ISO_PHY_ISO_DL_TX_ESC_L0;
    volatile uint32_t ISO_PHY_ISO_DL_RX_ESC_L0;
    volatile uint32_t ISO_PHY_ISO_DL_CTRL_L1;
    volatile uint32_t ISO_PHY_ISO_DL_HS_L1;
    volatile uint32_t ISO_PHY_ISO_DL_TX_ESC_L1;
    volatile uint32_t ISO_PHY_ISO_DL_RX_ESC_L1;
    volatile uint32_t ISO_PHY_ISO_SPARE_1;
    volatile uint32_t ISO_PHY_ISO_SPARE_2;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_CTRL_L2;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_HS_L2;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_TX_ESC_L2;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_RX_ESC_L2;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_CTRL_L3;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_HS_L3;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_TX_ESC_L3;
    volatile uint32_t ISO_LDD_PHY_ISO_DL_RX_ESC_L3;
} CSL_wiz16b8m4cdtRegs_DPHYTX;


typedef struct {
    volatile uint32_t MOD_VER;                   /* Module and Version */
    volatile uint32_t PLL_CTRL;                  /* PLL Control */
    volatile uint32_t STATUS;                    /* Status Register */
    volatile uint32_t RST_CTRL;                  /* RST Control */
    volatile uint32_t PSM_FREQ;                  /* PSM Frequency */
    volatile uint32_t IPCONFIG;                  /* IP Config */
    volatile uint8_t  Resv_248[224];
    volatile uint32_t PLLRES;                    /* PLL Reserved */
    volatile uint32_t DIAG_TEST;                 /* Diagnostic Test Register */
} CSL_wiz16b8m4cdtRegs_WIZ_CONFIG;


typedef struct {
    CSL_wiz16b8m4cdtRegs_DPHYTX DPHYTX;
    volatile uint8_t  Resv_3840[672];
    CSL_wiz16b8m4cdtRegs_WIZ_CONFIG WIZ_CONFIG;
} CSL_wiz16b8m4cdtRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0                             (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1                             (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2                             (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3                             (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4                             (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5                             (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0                             (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1                             (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2                             (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3                             (0x00000024U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4                             (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5                             (0x0000002CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6                             (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7                             (0x00000034U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8                             (0x00000038U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9                             (0x0000003CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10                            (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11                            (0x00000044U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12                            (0x00000048U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13                            (0x0000004CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14                            (0x00000050U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20                            (0x00000068U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21                            (0x0000006CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22                            (0x00000070U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23                            (0x00000074U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24                            (0x00000078U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25                            (0x0000007CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26                            (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27                            (0x00000084U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28                            (0x00000088U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31                            (0x00000094U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32                            (0x00000098U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33                            (0x0000009CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34                            (0x000000A0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35                            (0x000000A4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36                            (0x000000A8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37                            (0x000000ACU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39                            (0x000000B4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50                            (0x000000D8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53                            (0x000000E4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54                            (0x000000E8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56                            (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58                            (0x000000F8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0                              (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1                              (0x00000104U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2                              (0x00000108U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3                              (0x0000010CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4                              (0x00000110U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0                              (0x0000011CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1                              (0x00000120U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2                              (0x00000124U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8                              (0x0000013CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9                              (0x00000140U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10                             (0x00000144U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14                             (0x00000154U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15                             (0x00000158U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16                             (0x0000015CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17                             (0x00000160U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18                             (0x00000164U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19                             (0x00000168U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20                             (0x0000016CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5                              (0x00000170U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21                             (0x0000017CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22                             (0x00000180U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24                             (0x00000188U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25                             (0x0000018CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26                             (0x00000190U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27                             (0x00000194U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28                             (0x00000198U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29                             (0x0000019CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0                               (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1                               (0x00000204U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2                               (0x00000208U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3                               (0x0000020CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4                               (0x00000210U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0                               (0x0000021CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1                               (0x00000220U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2                               (0x00000224U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3                               (0x00000228U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4                               (0x0000022CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5                               (0x00000230U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6                               (0x00000234U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7                               (0x00000238U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8                               (0x0000023CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9                               (0x00000240U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10                              (0x00000244U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11                              (0x00000248U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12                              (0x0000024CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13                              (0x00000250U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14                              (0x00000254U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15                              (0x00000258U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16                              (0x0000025CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17                              (0x00000260U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18                              (0x00000264U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19                              (0x00000268U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20                              (0x0000026CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21                              (0x00000270U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22                              (0x00000274U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23                              (0x00000278U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24                              (0x0000027CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5                               (0x00000280U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25                              (0x0000028CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26                              (0x00000290U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28                              (0x00000298U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29                              (0x0000029CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30                              (0x000002A0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31                              (0x000002A4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32                              (0x000002A8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33                              (0x000002ACU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34                              (0x000002B0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35                              (0x000002B4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36                              (0x000002B8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0                               (0x00000300U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1                               (0x00000304U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2                               (0x00000308U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3                               (0x0000030CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4                               (0x00000310U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0                               (0x0000031CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1                               (0x00000320U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2                               (0x00000324U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3                               (0x00000328U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4                               (0x0000032CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5                               (0x00000330U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6                               (0x00000334U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7                               (0x00000338U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8                               (0x0000033CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9                               (0x00000340U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10                              (0x00000344U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11                              (0x00000348U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12                              (0x0000034CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13                              (0x00000350U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14                              (0x00000354U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15                              (0x00000358U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16                              (0x0000035CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17                              (0x00000360U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18                              (0x00000364U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19                              (0x00000368U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20                              (0x0000036CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21                              (0x00000370U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22                              (0x00000374U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23                              (0x00000378U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24                              (0x0000037CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5                               (0x00000380U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25                              (0x0000038CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26                              (0x00000390U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28                              (0x00000398U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29                              (0x0000039CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30                              (0x000003A0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31                              (0x000003A4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32                              (0x000003A8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33                              (0x000003ACU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34                              (0x000003B0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35                              (0x000003B4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36                              (0x000003B8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0                               (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1                               (0x00000404U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2                               (0x00000408U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3                               (0x0000040CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4                               (0x00000410U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0                               (0x0000041CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1                               (0x00000420U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2                               (0x00000424U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3                               (0x00000428U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4                               (0x0000042CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5                               (0x00000430U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6                               (0x00000434U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7                               (0x00000438U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8                               (0x0000043CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9                               (0x00000440U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10                              (0x00000444U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11                              (0x00000448U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12                              (0x0000044CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13                              (0x00000450U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14                              (0x00000454U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15                              (0x00000458U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16                              (0x0000045CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17                              (0x00000460U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18                              (0x00000464U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19                              (0x00000468U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20                              (0x0000046CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21                              (0x00000470U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22                              (0x00000474U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23                              (0x00000478U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24                              (0x0000047CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5                               (0x00000480U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25                              (0x0000048CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26                              (0x00000490U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28                              (0x00000498U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29                              (0x0000049CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30                              (0x000004A0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31                              (0x000004A4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32                              (0x000004A8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33                              (0x000004ACU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34                              (0x000004B0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35                              (0x000004B4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36                              (0x000004B8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0                               (0x00000500U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1                               (0x00000504U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2                               (0x00000508U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3                               (0x0000050CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4                               (0x00000510U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0                               (0x0000051CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1                               (0x00000520U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2                               (0x00000524U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3                               (0x00000528U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4                               (0x0000052CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5                               (0x00000530U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6                               (0x00000534U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7                               (0x00000538U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8                               (0x0000053CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9                               (0x00000540U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10                              (0x00000544U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11                              (0x00000548U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12                              (0x0000054CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13                              (0x00000550U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14                              (0x00000554U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15                              (0x00000558U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16                              (0x0000055CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17                              (0x00000560U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18                              (0x00000564U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19                              (0x00000568U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20                              (0x0000056CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21                              (0x00000570U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22                              (0x00000574U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23                              (0x00000578U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24                              (0x0000057CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5                               (0x00000580U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25                              (0x0000058CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26                              (0x00000590U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28                              (0x00000598U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29                              (0x0000059CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30                              (0x000005A0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31                              (0x000005A4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32                              (0x000005A8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33                              (0x000005ACU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34                              (0x000005B0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35                              (0x000005B4U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36                              (0x000005B8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0                               (0x00000B00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1                               (0x00000B04U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2                               (0x00000B08U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3                               (0x00000B0CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4                               (0x00000B10U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5                               (0x00000B14U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6                               (0x00000B18U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7                               (0x00000B1CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8                               (0x00000B20U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9                               (0x00000B24U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10                              (0x00000B28U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL                              (0x00000C00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET                              (0x00000C04U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE                             (0x00000C08U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL                           (0x00000C0CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL                            (0x00000C10U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L                         (0x00000C14U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0                         (0x00000C18U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0                           (0x00000C1CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0                       (0x00000C20U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0                       (0x00000C24U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1                         (0x00000C28U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1                           (0x00000C2CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1                       (0x00000C30U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1                       (0x00000C34U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1                            (0x00000C38U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2                            (0x00000C3CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2                     (0x00000C40U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2                       (0x00000C44U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2                   (0x00000C48U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2                   (0x00000C4CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3                     (0x00000C50U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3                       (0x00000C54U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3                   (0x00000C58U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3                   (0x00000C5CU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER                                    (0x00000F00U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL                                   (0x00000F04U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS                                     (0x00000F08U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL                                   (0x00000F0CU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ                                   (0x00000F10U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG                                   (0x00000F14U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES                                     (0x00000FF8U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST                                  (0x00000FFCU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CMN0_CMN_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0_CMN0_ANA_TBIT0_MASK         (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0_CMN0_ANA_TBIT0_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0_CMN0_ANA_TBIT0_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0_CMN0_ANA_TBIT0_MAX          (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT0_RESETVAL                    (0x00000000U)

/* CMN0_CMN_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1_CMN0_ANA_TBIT1_MASK         (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1_CMN0_ANA_TBIT1_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1_CMN0_ANA_TBIT1_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1_CMN0_ANA_TBIT1_MAX          (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT1_RESETVAL                    (0x00000000U)

/* CMN0_CMN_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2_CMN0_ANA_TBIT2_MASK         (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2_CMN0_ANA_TBIT2_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2_CMN0_ANA_TBIT2_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2_CMN0_ANA_TBIT2_MAX          (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT2_RESETVAL                    (0x00000000U)

/* CMN0_CMN_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3_CMN0_ANA_TBIT3_MASK         (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3_CMN0_ANA_TBIT3_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3_CMN0_ANA_TBIT3_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3_CMN0_ANA_TBIT3_MAX          (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT3_RESETVAL                    (0x00000000U)

/* CMN0_CMN_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4_CMN0_ANA_TBIT4_MASK         (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4_CMN0_ANA_TBIT4_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4_CMN0_ANA_TBIT4_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4_CMN0_ANA_TBIT4_MAX          (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT4_RESETVAL                    (0x00000000U)

/* CMN0_CMN_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5_CMN0_ANA_TBIT5_MASK         (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5_CMN0_ANA_TBIT5_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5_CMN0_ANA_TBIT5_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5_CMN0_ANA_TBIT5_MAX          (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_ANA_TBIT5_RESETVAL                    (0x00000000U)

/* CMN0_CMN_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_MASK (0x10000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_SEL_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_SEL_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CAL_START_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_COMP_OUT_POL_INV_TM_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_COMP_OUT_POL_INV_TM_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_COMP_OUT_POL_INV_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_COMP_OUT_POL_INV_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_LOW_TM_MASK (0x03C00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_LOW_TM_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_LOW_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_LOW_TM_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_DEC_TM_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_DEC_TM_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_DEC_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_DEC_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_TM_SEL_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_TM_SEL_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_LOW_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_HIGH_TM_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_HIGH_TM_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_HIGH_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_TEST_HIGH_TM_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_DEC_TM_MASK (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_DEC_TM_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_DEC_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_DEC_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_TM_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_TM_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_TX_OFFSET_HIGH_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_DECISION_WAIT_TM_MASK (0x00003C00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_DECISION_WAIT_TM_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_DECISION_WAIT_TM_RESETVAL (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_DECISION_WAIT_TM_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_INIT_WAIT_TM_MASK (0x000003C0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_INIT_WAIT_TM_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_INIT_WAIT_TM_RESETVAL (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_INIT_WAIT_TM_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_SEL_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_SEL_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_CMN0_O_RES_CALIB_RSTB_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT0_RESETVAL                    (0x00001140U)

/* CMN0_CMN_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_EN_MASK          (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_EN_SHIFT         (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_EN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_EN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_SRC_MASK         (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_SRC_SHIFT        (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_SRC_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ATB_SRC_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_BF_29_17_MASK          (0x3FFE0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_BF_29_17_SHIFT         (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_BF_29_17_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_BF_29_17_MAX           (0x00001FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATB_CP_CUR_SEL_MASK (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATB_CP_CUR_SEL_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATB_CP_CUR_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATB_CP_CUR_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATBH_GM_CUR_SEL_MASK (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATBH_GM_CUR_SEL_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATBH_GM_CUR_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_PLL_ATBH_GM_CUR_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_MASK    (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_SHIFT   (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_SEL_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_SEL_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_BG_PD_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_SEL_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_SEL_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_PD_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_MASK (0x0000003EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_CMN0_O_ANA_RES_CALIB_CODE_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT1_RESETVAL                    (0x00000000U)

/* CMN0_CMN_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_RX_MODE_EN_MASK  (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_RX_MODE_EN_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_RX_MODE_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_RX_MODE_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_TX_MODE_EN_MASK  (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_TX_MODE_EN_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_TX_MODE_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_TX_MODE_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_SSM_WAIT_BGCAL_EN_MASK (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_SSM_WAIT_BGCAL_EN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_SSM_WAIT_BGCAL_EN_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_SSM_WAIT_BGCAL_EN_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_SSM_EN_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_SSM_EN_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_SSM_EN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_SSM_EN_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_RESETVAL                    (0x00000028U)

/* CMN0_CMN_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_ACCINV_MASK (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_ACCINV_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_ACCINV_RESETVAL (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_ACCINV_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_BIAS_MASK (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_BIAS_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_BIAS_RESETVAL (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_BIAS_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_DEL_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_DEL_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_DEL_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_DEL_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_CMN0_O_PLL_WAIT_PLL_EN_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT3_RESETVAL                    (0x05030101U)

/* CMN0_CMN_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_LOCK_DET_WAIT_MASK (0x0FFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_LOCK_DET_WAIT_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_LOCK_DET_WAIT_RESETVAL (0x00000032U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_LOCK_DET_WAIT_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_2_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_2_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_2_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_2_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_RESETVAL (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_CMN0_O_PLL_WAIT_PLL_RST_DEASSERT_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT4_RESETVAL                    (0x0032011EU)

/* CMN0_CMN_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_CMN_TX_READY_TM_SEL_MASK (0xC0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_CMN_TX_READY_TM_SEL_SHIFT (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_CMN_TX_READY_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_CMN_TX_READY_TM_SEL_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_PROCEED_WITH_LOCK_FAIL_TM_MASK (0x20000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_PROCEED_WITH_LOCK_FAIL_TM_SHIFT (0x0000001DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_PROCEED_WITH_LOCK_FAIL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_PROCEED_WITH_LOCK_FAIL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_MASK   (0x10000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_SHIFT  (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_SEL_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_SEL_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCKED_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_SEL_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_SEL_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_LOCK_DET_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_WAIT_PLL_LOCK_TIMEOUT_MASK (0x0003FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_WAIT_PLL_LOCK_TIMEOUT_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_WAIT_PLL_LOCK_TIMEOUT_RESETVAL (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_CMN0_O_PLL_WAIT_PLL_LOCK_TIMEOUT_MAX (0x0003FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT5_RESETVAL                    (0x00000400U)

/* CMN0_CMN_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_IDLE_VALUE_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_IDLE_VALUE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_IDLE_VALUE_RESETVAL (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_IDLE_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_START_VALUE_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_START_VALUE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_START_VALUE_RESETVAL (0x000000C8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_CMN0_O_LOCKDET_REFCNT_START_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT6_RESETVAL                    (0x000400C8U)

/* CMN0_CMN_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE_RESETVAL (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE_RESETVAL (0x000000C8U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_RESETVAL                    (0x000300C8U)

/* CMN0_CMN_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCTRL_TUNE_MASK (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCTRL_TUNE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCTRL_TUNE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCTRL_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_TUNE_MASK (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_TUNE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_TUNE_RESETVAL (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_GM_TUNE_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_GM_TUNE_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_GM_TUNE_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_GM_TUNE_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_CP_TUNE_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_CP_TUNE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_CP_TUNE_RESETVAL (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_CMN0_O_ANA_PLL_CP_TUNE_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT8_RESETVAL                    (0x00080103U)

/* CMN0_CMN_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VREF_VCO_BIAS_TUNE_MASK (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VREF_VCO_BIAS_TUNE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VREF_VCO_BIAS_TUNE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VREF_VCO_BIAS_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VCO_BIAS_TUNE_MASK (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VCO_BIAS_TUNE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VCO_BIAS_TUNE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_VCO_BIAS_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_GMBYC_CAP_TUNE_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_GMBYC_CAP_TUNE_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_GMBYC_CAP_TUNE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_GMBYC_CAP_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_LOOP_FILTER_TUNE_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_LOOP_FILTER_TUNE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_LOOP_FILTER_TUNE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_CMN0_O_ANA_PLL_LOOP_FILTER_TUNE_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT9_RESETVAL                    (0x00000000U)

/* CMN0_CMN_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_BYTECLK_DIV_MASK (0x0FF00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_BYTECLK_DIV_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_BYTECLK_DIV_RESETVAL (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_BYTECLK_DIV_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW_MASK (0x000FFC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH_MASK (0x000003FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_RESETVAL                   (0x00800000U)

/* CMN0_CMN_DIG_TBIT11 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_CYA_MASK    (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_CYA_SHIFT   (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_CYA_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_CYA_MAX     (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_PFD_EN_1U_DEL_TM_SEL_MASK (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_PFD_EN_1U_DEL_TM_SEL_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_PFD_EN_1U_DEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_PFD_EN_1U_DEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCO_BIAS_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCTRL_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCTRL_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCTRL_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_VRESET_VCTRL_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_SEL_FBCLK_GM_PWM_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_SEL_FBCLK_GM_PWM_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_SEL_FBCLK_GM_PWM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_SEL_FBCLK_GM_PWM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_BY2_BYPASS_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_BY2_BYPASS_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_BY2_BYPASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_BY2_BYPASS_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_BYPASS_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_BYPASS_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_BYPASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_BYPASS_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FBDIV_CLKINBY2_EN_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FBDIV_CLKINBY2_EN_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FBDIV_CLKINBY2_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FBDIV_CLKINBY2_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_DSM_CLK_EN_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_DSM_CLK_EN_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_DSM_CLK_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_DSM_CLK_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_GM_PWM_EN_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_GM_PWM_EN_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_GM_PWM_EN_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_GM_PWM_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_DIV_CLK_EN_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_DIV_CLK_EN_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_DIV_CLK_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_OP_DIV_CLK_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_IP_DIV_CLK_EN_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_IP_DIV_CLK_EN_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_IP_DIV_CLK_EN_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_IP_DIV_CLK_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_REF_CLK_EN_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_REF_CLK_EN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_REF_CLK_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_REF_CLK_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FB_DIV_CLK_EN_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FB_DIV_CLK_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FB_DIV_CLK_EN_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_CMN0_O_ANA_PLL_FB_DIV_CLK_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT11_RESETVAL                   (0x00000015U)

/* CMN0_CMN_DIG_TBIT12 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_MASK (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_SHIFT (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_SEL_MASK (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_SEL_SHIFT (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_VRESET_GEN_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_MASK (0x20000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_SHIFT (0x0000001DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_SEL_MASK (0x10000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_SEL_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_PFD_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_LOOP_FILTER_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_SEL_MASK (0x01000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_SEL_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GM_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_SEL_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_SEL_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_GMBYC_CAP_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_SEL_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_SEL_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_CP_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_SEL_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_SEL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_ACCINV_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_SEL_MASK (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_SEL_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLL_BIAS_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_MASK (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_DEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_SEL_MASK (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_SEL_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_PLLDA_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_BY2_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_SEL_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_SEL_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_OP_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_SEL_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_SEL_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_IP_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_SEL_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_SEL_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_FB_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_SEL_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_SEL_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_GM_PWM_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_CMN0_O_ANA_BYTECLK_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT12_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT13 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_MASK (0xFFC00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_SEL_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_SEL_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_LOW_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_MASK (0x001FF800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_CMN0_O_ANA_PLL_FB_DIV_HIGH_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT13_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_MASK (0x00001F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_MAX (0x0000003FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_SEL_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_SEL_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_OP_DIV_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_MASK (0x0000003EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_CMN0_O_ANA_PLL_IP_DIV_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT14_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_REF_CLK_TMR_VALUE_MASK (0x000FFFF0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_REF_CLK_TMR_VALUE_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_REF_CLK_TMR_VALUE_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_REF_CLK_TMR_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_BF_3_1_MASK           (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_BF_3_1_SHIFT          (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_BF_3_1_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_BF_3_1_MAX            (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_MEASUREMENT_RUN_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_MEASUREMENT_RUN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_MEASUREMENT_RUN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_CMN0_O_CMSMT_MEASUREMENT_RUN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT20_RESETVAL                   (0x00000140U)

/* CMN0_CMN_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_CLK_SERSYNTH_SWAPDPDN_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_CLK_SERSYNTH_SWAPDPDN_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_CLK_SERSYNTH_SWAPDPDN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_CLK_SERSYNTH_SWAPDPDN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_DATA_SERSYNTH_SWAPDPDN_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_DATA_SERSYNTH_SWAPDPDN_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_DATA_SERSYNTH_SWAPDPDN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_HSRX_BIST_DATA_SERSYNTH_SWAPDPDN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_SEL_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_SEL_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_DEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_SEL_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_SEL_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_CMNDA_RX_BIST_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_RX_DIG_BIST_EN_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_RX_DIG_BIST_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_RX_DIG_BIST_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_CMN0_O_RX_DIG_BIST_EN_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT21_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_SEL_MASK (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_SEL_SHIFT (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_MASK (0x7F800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_SKEW_CAL_SYNC_PKT_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_SEL_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_SEL_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_MASK   (0x003FC000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_SHIFT  (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_TM_HS_SYNC_PKT_MAX    (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_LENGTH_OF_DESKEW_MASK (0x00003F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_LENGTH_OF_DESKEW_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_LENGTH_OF_DESKEW_RESETVAL (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_LENGTH_OF_DESKEW_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_SEND_CONFIG_MASK (0x00000060U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_SEND_CONFIG_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_SEND_CONFIG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_SEND_CONFIG_MAX  (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_MODE_ENTRY_WAIT_TIME_MASK (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_MODE_ENTRY_WAIT_TIME_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_MODE_ENTRY_WAIT_TIME_RESETVAL (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_MODE_ENTRY_WAIT_TIME_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_CONTROLLER_EN_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_CONTROLLER_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_CONTROLLER_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_CMN0_BIST_CONTROLLER_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT22_RESETVAL                   (0x00000694U)

/* CMN0_CMN_DIG_TBIT23 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_MASK    (0x007F8000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_TX_DATA_HS_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_MASK (0x00003E00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_BIST_TM_BAND_CTRL_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_SEL_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_SEL_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_CMN0_TM_SKEW_CAL_PATTERN_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT23_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_IDLE_TIME_MASK (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_IDLE_TIME_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_IDLE_TIME_RESETVAL (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_IDLE_TIME_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PKT_NUM_MASK     (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PKT_NUM_SHIFT    (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PKT_NUM_RESETVAL (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PKT_NUM_MAX      (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_INF_MODE_MASK    (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_INF_MODE_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_INF_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_INF_MODE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_NUM_MASK     (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_NUM_SHIFT    (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_NUM_RESETVAL (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_FRM_NUM_MAX      (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_CLEAR_MASK       (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_CLEAR_SHIFT      (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_CLEAR_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_CLEAR_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PRBS_MASK        (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PRBS_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PRBS_RESETVAL    (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_PRBS_MAX         (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_TEST_MODE_MASK   (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_TEST_MODE_SHIFT  (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_TEST_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_BIST_TEST_MODE_MAX    (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_UNUSED_0_MASK         (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_UNUSED_0_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_UNUSED_0_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_CMN0_UNUSED_0_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT24_RESETVAL                   (0x0F0501B0U)

/* CMN0_CMN_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25_CMN0_BIST_RUN_LENGTH_MASK  (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25_CMN0_BIST_RUN_LENGTH_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25_CMN0_BIST_RUN_LENGTH_RESETVAL (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25_CMN0_BIST_RUN_LENGTH_MAX   (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT25_RESETVAL                   (0x00000028U)

/* CMN0_CMN_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_UNUSED_31_8_MASK      (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_UNUSED_31_8_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_UNUSED_31_8_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_UNUSED_31_8_MAX       (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_BIST_IDLE_TIME_MASK   (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_BIST_IDLE_TIME_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_BIST_IDLE_TIME_RESETVAL (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_CMN0_BIST_IDLE_TIME_MAX    (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT26_RESETVAL                   (0x0000000AU)

/* CMN0_CMN_DIG_TBIT27 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT4_MASK        (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT4_SHIFT       (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT4_RESETVAL    (0x000000DEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT4_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT3_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT3_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT3_RESETVAL    (0x000000CDU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT3_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT2_MASK        (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT2_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT2_RESETVAL    (0x000000BCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT2_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT1_MASK        (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT1_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT1_RESETVAL    (0x000000ABU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_CMN0_BIST_PKT1_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT27_RESETVAL                   (0xDECDBCABU)

/* CMN0_CMN_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_VAL_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_VAL_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_VAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DP_VAL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_SEL_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_SEL_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_VAL_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_VAL_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_VAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_CLOCK_LP_DN_VAL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_VAL_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_VAL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_VAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DP_VAL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_SEL_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_SEL_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_VAL_MASK (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_VAL_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_VAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_TM_DATA_LP_DN_VAL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_UNUSED_INT_MASK       (0x0000C000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_UNUSED_INT_SHIFT      (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_UNUSED_INT_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_UNUSED_INT_MAX        (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_LFSR_FREEZE_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_LFSR_FREEZE_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_LFSR_FREEZE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_LFSR_FREEZE_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_POINT_MASK (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_POINT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_POINT_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_POINT_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_EN_MASK  (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_CMN0_BIST_ERR_INJ_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT28_RESETVAL                   (0x00000028U)

/* CMN0_CMN_DIG_TBIT31 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_REF_TMR_MASK (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_REF_TMR_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_REF_TMR_RESETVAL (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_REF_TMR_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_DEL_TMR_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_DEL_TMR_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_DEL_TMR_RESETVAL (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_DEL_TMR_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_TMR_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_TMR_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_TMR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_CMN0_O_RX_SSM_LDO_EN_TMR_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT31_RESETVAL                   (0x00040400U)

/* CMN0_CMN_DIG_TBIT32 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_ISO_DIS_TMR_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_ISO_DIS_TMR_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_ISO_DIS_TMR_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_ISO_DIS_TMR_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_EN_DEL_TMR_MASK (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_EN_DEL_TMR_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_EN_DEL_TMR_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_CMN0_O_RX_SSM_ANA_BIST_EN_DEL_TMR_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT32_RESETVAL                   (0x00000201U)

/* CMN0_CMN_DIG_TBIT33 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_OSC_CAL_TIMER_SCALE_SEL_MASK (0xE0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_OSC_CAL_TIMER_SCALE_SEL_SHIFT (0x0000001DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_OSC_CAL_TIMER_SCALE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_OSC_CAL_TIMER_SCALE_SEL_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_MASK (0x03FFC000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_SEL_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_SEL_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_ITER_VALUE_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_MASK (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_CMN0_O_RX_REFCLK_TIMER_INIT_VALUE_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT33_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT34 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_MASK (0x03FFC000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_SEL_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_SEL_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_OSC_EN_DEL_TMR_VALUE_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_MASK (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_CMN0_O_RX_REFCLK_TIMER_START_VALUE_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT34_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT35 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_2_MASK (0x00FFF000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_2_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_2_RESETVAL (0x00000138U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_2_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_1_MASK (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_1_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_1_RESETVAL (0x000000BBU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_CMN0_O_RX_PLLCNT_COUNT_START_VALUE_1_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT35_RESETVAL                   (0x001380BBU)

/* CMN0_CMN_DIG_TBIT36 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCOCAL_OVRD_VALUE_MASK (0x000FE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCOCAL_OVRD_VALUE_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCOCAL_OVRD_VALUE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCOCAL_OVRD_VALUE_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCO_CAL_OVERRIDE_EN_MASK (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCO_CAL_OVERRIDE_EN_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCO_CAL_OVERRIDE_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_VCO_CAL_OVERRIDE_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_START_MASK (0x00000FE0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_START_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_START_RESETVAL (0x00000077U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_START_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_INIT_STEP_MASK (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_INIT_STEP_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_INIT_STEP_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_OSC_CAL_CODE_INIT_STEP_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_SEL_1P5G_MODE_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_SEL_1P5G_MODE_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_SEL_1P5G_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_SEL_1P5G_MODE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_OSC_CAL_EN_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_OSC_CAL_EN_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_OSC_CAL_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_CMN0_O_RX_TM_OSC_CAL_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT36_RESETVAL                   (0x00000EE8U)

/* CMN0_CMN_DIG_TBIT37 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_SEL_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_SEL_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_HSRX_OSC_CALIB_SEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_MASK (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_DIV_RESET_N_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_SEL_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_SEL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_DEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_SEL_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_SEL_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_OSC_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_BYPASS_TM_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_BYPASS_TM_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_BYPASS_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_BYPASS_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_SEL_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_SEL_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_REF_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_SEL_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_SEL_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_DEL_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_SEL_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_SEL_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_CMN0_O_CMNDA_RX_LDO_EN_TM_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT37_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT39 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39_CMN0_SPARE_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39_CMN0_SPARE_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39_CMN0_SPARE_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39_CMN0_SPARE_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT39_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT50 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_COMPLETE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_COMPLETE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_COMPLETE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_COMPLETE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_EN_ACK_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_EN_ACK_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_EN_ACK_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_CMN0_BIST_EN_ACK_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT50_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT53 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_TEST_CLK_CNT_VALUE_MASK (0x0001FFFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_TEST_CLK_CNT_VALUE_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_TEST_CLK_CNT_VALUE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_TEST_CLK_CNT_VALUE_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_MEASUREMENT_DONE_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_MEASUREMENT_DONE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_MEASUREMENT_DONE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_CMN0_I_CMSMT_MEASUREMENT_DONE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT53_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT54 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_PLL_SSM_STATE_MASK (0xFFF00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_PLL_SSM_STATE_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_PLL_SSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_PLL_SSM_STATE_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_DIG_PG_ACK_MASK     (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_DIG_PG_ACK_SHIFT    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_DIG_PG_ACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_DIG_PG_ACK_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_NOT_LOCKED_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_NOT_LOCKED_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_NOT_LOCKED_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_NOT_LOCKED_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_LOCKED_MASK     (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_LOCKED_SHIFT    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_LOCKED_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_PLL_LOCKED_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_ANA_RES_COMP_OUT_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_ANA_RES_COMP_OUT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_ANA_RES_COMP_OUT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_ANA_RES_COMP_OUT_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_TX_READY_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_TX_READY_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_TX_READY_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_CMN0_I_CMN_TX_READY_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT54_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT56 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMNDA_RX_OSC_CALCODE_MASK (0x0FE00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMNDA_RX_OSC_CALCODE_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMNDA_RX_OSC_CALCODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMNDA_RX_OSC_CALCODE_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_SSM_STATE_MASK (0x001FF800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_SSM_STATE_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_SSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_SSM_STATE_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_RX_OSC_CAL_FSM_STATE_MASK (0x000007FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_RX_OSC_CAL_FSM_STATE_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_RX_OSC_CAL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_RX_OSC_CAL_FSM_STATE_MAX (0x000001FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_ANA_RES_COMP_OUT_X_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_ANA_RES_COMP_OUT_X_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_ANA_RES_COMP_OUT_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_ANA_RES_COMP_OUT_X_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_READY_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_READY_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_READY_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_CMN0_I_CMN_RX_READY_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT56_RESETVAL                   (0x00000000U)

/* CMN0_CMN_DIG_TBIT58 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_CODE_MASK (0x0000003EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_CODE_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_CODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_CODE_MAX  (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_DONE_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_DONE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_DONE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_CMN0_I_RES_CALIB_DONE_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT58_RESETVAL                   (0x00000000U)

/* CLK0_TX_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MASK       (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_MASK        (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_SHIFT       (0x00000006U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MASK       (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_SHIFT      (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_MASK        (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_SHIFT       (0x0000000EU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MASK         (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_SHIFT        (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_EN_MASK          (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_EN_SHIFT         (0x00000016U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX          (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MAX        (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MAX        (32U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_RESETVAL                     (0x00000000U)

/* CLK0_TX_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1_CLK0_ANA_TBIT1_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1_CLK0_ANA_TBIT1_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1_CLK0_ANA_TBIT1_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1_CLK0_ANA_TBIT1_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT1_RESETVAL                     (0x00000000U)

/* CLK0_TX_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2_CLK0_ANA_TBIT2_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2_CLK0_ANA_TBIT2_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2_CLK0_ANA_TBIT2_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2_CLK0_ANA_TBIT2_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT2_RESETVAL                     (0x00000000U)

/* CLK0_TX_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3_CLK0_ANA_TBIT3_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3_CLK0_ANA_TBIT3_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3_CLK0_ANA_TBIT3_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3_CLK0_ANA_TBIT3_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT3_RESETVAL                     (0x00000000U)

/* CLK0_TX_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4_CLK0_ANA_TBIT4_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4_CLK0_ANA_TBIT4_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4_CLK0_ANA_TBIT4_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4_CLK0_ANA_TBIT4_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT4_RESETVAL                     (0x00000000U)

/* CLK0_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_ULPS_PULLDN_CNT_MASK    (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_ULPS_PULLDN_CNT_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_ULPS_PULLDN_CNT_RESETVAL (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_ULPS_PULLDN_CNT_MAX     (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_UNUSED_7_5_MASK         (0x000000E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_UNUSED_7_5_SHIFT        (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_UNUSED_7_5_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_UNUSED_7_5_MAX          (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_LDO_EN_CNT_MASK         (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_LDO_EN_CNT_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_LDO_EN_CNT_RESETVAL     (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_CLK0_LDO_EN_CNT_MAX          (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT0_RESETVAL                     (0x00000606U)

/* CLK0_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_SEL_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_SEL_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_EN_MASK (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_EN_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_HS_PREP_HALF_CYC_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_TRAIL_OFFSET_MASK   (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_TRAIL_OFFSET_SHIFT  (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_TRAIL_OFFSET_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_TRAIL_OFFSET_MAX    (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_ZERO_OFFSET_MASK    (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_ZERO_OFFSET_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_ZERO_OFFSET_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_ZERO_OFFSET_MAX     (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_PREP_OFFSET_MASK    (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_PREP_OFFSET_SHIFT   (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_PREP_OFFSET_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_CLK_PREP_OFFSET_MAX     (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_TLPX_OFFSET_MASK        (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_TLPX_OFFSET_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_TLPX_OFFSET_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_CLK0_TLPX_OFFSET_MAX         (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT1_RESETVAL                     (0x00000000U)

/* CLK0_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_SERSYNTH_LOOPBACK_MASK  (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_SERSYNTH_LOOPBACK_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_SERSYNTH_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_SERSYNTH_LOOPBACK_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_STATE_MASK    (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_STATE_SHIFT   (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_STATE_MAX     (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_EN_MASK       (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_EN_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_CLK0_BAL_FORCE_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT2_RESETVAL                     (0x00000000U)

/* CLK0_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_WAIT_TIME_MASK          (0x3C000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_WAIT_TIME_SHIFT         (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_WAIT_TIME_RESETVAL      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_WAIT_TIME_MAX           (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_ULPTX_TEST_TIME_MASK    (0x03FC0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_ULPTX_TEST_TIME_SHIFT   (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_ULPTX_TEST_TIME_RESETVAL (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_ULPTX_TEST_TIME_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_HS_CLK_CHECK_TIME_MASK  (0x0003FFFCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_HS_CLK_CHECK_TIME_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_HS_CLK_CHECK_TIME_RESETVAL (0x00000064U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_HS_CLK_CHECK_TIME_MAX   (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_LOOPBACK_MODE_MASK      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_LOOPBACK_MODE_SHIFT     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_LOOPBACK_MODE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_LOOPBACK_MODE_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_BIST_EN_MASK            (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_BIST_EN_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_BIST_EN_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_CLK0_BIST_EN_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT8_RESETVAL                     (0x11000190U)

/* CLK0_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_BIST_DIG_TO_DIG_LOOPBACK_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_BIST_DIG_TO_DIG_LOOPBACK_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_BIST_DIG_TO_DIG_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_BIST_DIG_TO_DIG_LOOPBACK_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_UNUSED_9_5_MASK         (0x000003E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_UNUSED_9_5_SHIFT        (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_UNUSED_9_5_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_UNUSED_9_5_MAX          (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_HS_CLK_CHECK_EXTRA_TIME_MASK (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_HS_CLK_CHECK_EXTRA_TIME_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_HS_CLK_CHECK_EXTRA_TIME_RESETVAL (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_CLK0_HS_CLK_CHECK_EXTRA_TIME_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT9_RESETVAL                     (0x0000000AU)

/* CLK0_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10_CLK0_SPARE_MASK             (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10_CLK0_SPARE_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10_CLK0_SPARE_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10_CLK0_SPARE_MAX              (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT10_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ISO_EN_MASK         (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ISO_EN_SHIFT        (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ISO_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ISO_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_SEL_MASK  (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_SEL_SHIFT (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_MASK      (0x38000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_SHIFT     (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LOAD_DPDN_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATA_RATE_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATA_RATE_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATA_RATE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATA_RATE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATE_RATE_MASK (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATE_RATE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATE_RATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_DATE_RATE_MAX  (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_ULP_RCV_EN_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_SEL_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_SEL_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_SEL_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_MASK     (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_SHIFT    (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_ULPS_PULDN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_SMPLR_CLK_EDGE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_SEL_MASK    (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_SEL_SHIFT   (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_MASK        (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_BIST_EN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_SEL_MASK  (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_SEL_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_MASK      (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_SHIFT     (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_TRST_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_SEL_MASK   (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_SEL_SHIFT  (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_MASK       (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_SHIFT      (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_RST_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_SEL_MASK    (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_SEL_SHIFT   (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_MASK        (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_SHIFT       (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DP_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_SEL_MASK    (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_SEL_SHIFT   (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_MASK        (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LPTX_DN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_SEL_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_SEL_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_SEL_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_MASK     (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_SHIFT    (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_LDO_REF_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_SEL_MASK  (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_SEL_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_MASK      (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_SHIFT     (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_TRST_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_SEL_MASK  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_SEL_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_MASK      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_SHIFT     (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_HSTX_RQST_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_SEL_MASK  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_SEL_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_CLK0_TM_GLOBAL_PD_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT14_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT15 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_MASK (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_RST_N_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_SEL_MASK  (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_SEL_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_EN_MASK   (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_EN_SHIFT  (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SWAP_DPDN_EN_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_MASK    (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_SHIFT   (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_SERSYNTH_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_SEL_MASK (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_SEL_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_SEL_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_MASK     (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_CLK0_TM_TX_DATA_HS_MAX      (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT15_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT16 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16_CLK0_DIG_TBIT16_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16_CLK0_DIG_TBIT16_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16_CLK0_DIG_TBIT16_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16_CLK0_DIG_TBIT16_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT16_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT17 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17_CLK0_DIG_TBIT17_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17_CLK0_DIG_TBIT17_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17_CLK0_DIG_TBIT17_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17_CLK0_DIG_TBIT17_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT17_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT18 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18_CLK0_DIG_TBIT18_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18_CLK0_DIG_TBIT18_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18_CLK0_DIG_TBIT18_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18_CLK0_DIG_TBIT18_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT18_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT19 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19_CLK0_DIG_TBIT19_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19_CLK0_DIG_TBIT19_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19_CLK0_DIG_TBIT19_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19_CLK0_DIG_TBIT19_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT19_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20_CLK0_DIG_TBIT20_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20_CLK0_DIG_TBIT20_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20_CLK0_DIG_TBIT20_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20_CLK0_DIG_TBIT20_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT20_RESETVAL                    (0x00000000U)

/* CLK0_TX_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5_CLK0_ANA_TBIT5_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5_CLK0_ANA_TBIT5_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5_CLK0_ANA_TBIT5_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5_CLK0_ANA_TBIT5_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT5_RESETVAL                     (0x00000000U)

/* CLK0_TX_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_ANA_CTRL_FSM_STATE_MASK (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_ANA_CTRL_FSM_STATE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_ANA_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_ANA_CTRL_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_BIST_BAL_STATUS_MASK   (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_BIST_BAL_STATUS_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_BIST_BAL_STATUS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_CLK0_BIST_BAL_STATUS_MAX    (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT21_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_ESC_FSM_STATE_MASK  (0x003FF000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_ESC_FSM_STATE_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_ESC_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_ESC_FSM_STATE_MAX   (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_HS_FSM_STATE_MASK   (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_HS_FSM_STATE_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_HS_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_CLK0_TM_HS_FSM_STATE_MAX    (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT22_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DP_MASK       (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DP_SHIFT      (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DP_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DP_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DN_MASK       (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DN_SHIFT      (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ULP_DN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BAL_FAIL_MASK          (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BAL_FAIL_SHIFT         (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BAL_FAIL_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BAL_FAIL_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_CHE_FSM_STATE_MASK (0x00006000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_CHE_FSM_STATE_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_CHE_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_CHE_FSM_STATE_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_CHE_FSM_STATE_MASK (0x00001C00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_CHE_FSM_STATE_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_CHE_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_CHE_FSM_STATE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_CTRLR_FSM_STATE_MASK   (0x00000380U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_CTRLR_FSM_STATE_SHIFT  (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_CTRLR_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_CTRLR_FSM_STATE_MAX    (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_PASS_MASK         (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_PASS_SHIFT        (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_PASS_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_PASS_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_BIST_PASS_MASK   (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_BIST_PASS_SHIFT  (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_BIST_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_ULPTX_BIST_PASS_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_BIST_PASS_MASK    (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_BIST_PASS_SHIFT   (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_BIST_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_LPTX_BIST_PASS_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_POS_MASK   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_POS_SHIFT  (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_POS_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_NEG_MASK   (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_NEG_SHIFT  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_HS_BIST_ERR_NEG_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_CMPLT_MASK        (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_CMPLT_SHIFT       (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_CMPLT_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_CMPLT_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ENABLED_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ENABLED_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ENABLED_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_CLK0_BIST_ENABLED_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT24_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25_CLK0_DIG_TBIT25_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25_CLK0_DIG_TBIT25_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25_CLK0_DIG_TBIT25_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25_CLK0_DIG_TBIT25_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT25_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26_CLK0_DIG_TBIT26_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26_CLK0_DIG_TBIT26_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26_CLK0_DIG_TBIT26_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26_CLK0_DIG_TBIT26_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT26_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT27 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27_CLK0_DIG_TBIT27_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27_CLK0_DIG_TBIT27_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27_CLK0_DIG_TBIT27_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27_CLK0_DIG_TBIT27_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT27_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28_CLK0_DIG_TBIT28_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28_CLK0_DIG_TBIT28_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28_CLK0_DIG_TBIT28_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28_CLK0_DIG_TBIT28_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT28_RESETVAL                    (0x00000000U)

/* CLK0_TX_DIG_TBIT29 */

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29_CLK0_DIG_TBIT29_MASK        (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29_CLK0_DIG_TBIT29_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29_CLK0_DIG_TBIT29_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29_CLK0_DIG_TBIT29_MAX         (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_DIG_TBIT29_RESETVAL                    (0x00000000U)

/* DL0_TX_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_DL0_ANA_TBIT0_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_DL0_ANA_TBIT0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_DL0_ANA_TBIT0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_DL0_ANA_TBIT0_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MASK           (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MAX            (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MASK        (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_MASK         (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_SHIFT        (0x00000006U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MASK        (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_MASK         (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_SHIFT        (0x0000000EU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MASK          (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_SHIFT         (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_EN_MASK           (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_EN_SHIFT          (0x00000016U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX           (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MAX         (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MAX         (32U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_RESETVAL                      (0x00000000U)

/* DL0_TX_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1_DL0_ANA_TBIT1_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1_DL0_ANA_TBIT1_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1_DL0_ANA_TBIT1_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1_DL0_ANA_TBIT1_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT1_RESETVAL                      (0x00000000U)

/* DL0_TX_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2_DL0_ANA_TBIT2_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2_DL0_ANA_TBIT2_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2_DL0_ANA_TBIT2_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2_DL0_ANA_TBIT2_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT2_RESETVAL                      (0x00000000U)

/* DL0_TX_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3_DL0_ANA_TBIT3_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3_DL0_ANA_TBIT3_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3_DL0_ANA_TBIT3_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3_DL0_ANA_TBIT3_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT3_RESETVAL                      (0x00000000U)

/* DL0_TX_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4_DL0_ANA_TBIT4_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4_DL0_ANA_TBIT4_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4_DL0_ANA_TBIT4_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4_DL0_ANA_TBIT4_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT4_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_31_13_MASK         (0xFFFFE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_31_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_31_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_31_13_MAX          (0x0007FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_ULPS_PULLDN_CNT_MASK      (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_ULPS_PULLDN_CNT_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_ULPS_PULLDN_CNT_RESETVAL  (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_ULPS_PULLDN_CNT_MAX       (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_7_5_MASK           (0x000000E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_7_5_SHIFT          (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_7_5_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_UNUSED_7_5_MAX            (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_LDO_EN_CNT_MASK           (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_LDO_EN_CNT_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_LDO_EN_CNT_RESETVAL       (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_DL0_LDO_EN_CNT_MAX            (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT0_RESETVAL                      (0x00000606U)

/* DL0_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DP_MASK         (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DP_SHIFT        (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DP_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DP_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DN_MASK         (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DN_SHIFT        (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_DN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_EN_MASK         (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_EN_SHIFT        (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TEST_LPTX_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_READY_SKEW_CAL_MASK    (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_READY_SKEW_CAL_SHIFT   (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_READY_SKEW_CAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_READY_SKEW_CAL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HAFCYC_OVERRIDE_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HAFCYC_OVERRIDE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HAFCYC_OVERRIDE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HAFCYC_OVERRIDE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HSFCYC_MASK    (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HSFCYC_SHIFT   (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HSFCYC_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_TM_HS_PREP_HSFCYC_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TRAIL_OFFSET_MASK      (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TRAIL_OFFSET_SHIFT     (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TRAIL_OFFSET_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TRAIL_OFFSET_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_ZERO_OFFSET_MASK       (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_ZERO_OFFSET_SHIFT      (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_ZERO_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_ZERO_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_PREP_OFFSET_MASK       (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_PREP_OFFSET_SHIFT      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_PREP_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_PREP_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TLPX_OFFSET_MASK       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TLPX_OFFSET_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TLPX_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_DL0_HS_TLPX_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT1_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_MASK      (0x07F80000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_SHIFT     (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_SEL_MASK  (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_SEL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SEQ_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_MASK (0x0003FC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_SEL_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_SEL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_SKEW_CAL_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_MASK       (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_SEL_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_SEL_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_DL0_TM_HS_SYNC_PKT_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT2_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_SERSYNTH_LOOPBACK_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_SERSYNTH_LOOPBACK_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_SERSYNTH_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_SERSYNTH_LOOPBACK_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_STATE_MASK      (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_STATE_SHIFT     (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_STATE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_STATE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_EN_MASK         (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_EN_SHIFT        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_DL0_BAL_FORCE_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT3_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_CONTENTION_EN_MASK        (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_CONTENTION_EN_SHIFT       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_CONTENTION_EN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_CONTENTION_EN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_UNUSED_14_13_MASK         (0x00006000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_UNUSED_14_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_UNUSED_14_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_UNUSED_14_13_MAX          (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_FORCE_RX_MODE_MASK        (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_FORCE_RX_MODE_SHIFT       (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_FORCE_RX_MODE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_FORCE_RX_MODE_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DP_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DP_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DN_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_MASK       (0x000003FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_RSTN_MASK  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_RSTN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_RSTN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_RSTN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_EN_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_EN_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_DL0_TEST_DATA_LPTX_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT4_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5_DL0_DIG_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5_DL0_DIG_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5_DL0_DIG_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5_DL0_DIG_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT5_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6_DL0_DIG_TBIT6_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6_DL0_DIG_TBIT6_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6_DL0_DIG_TBIT6_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6_DL0_DIG_TBIT6_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT6_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7_DL0_DIG_TBIT7_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7_DL0_DIG_TBIT7_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7_DL0_DIG_TBIT7_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7_DL0_DIG_TBIT7_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT7_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8_DL0_DIG_TBIT8_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8_DL0_DIG_TBIT8_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8_DL0_DIG_TBIT8_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8_DL0_DIG_TBIT8_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT8_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9_DL0_DIG_TBIT9_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9_DL0_DIG_TBIT9_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9_DL0_DIG_TBIT9_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9_DL0_DIG_TBIT9_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT9_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_WAIT_TIME_MASK      (0x01E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_WAIT_TIME_SHIFT     (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_WAIT_TIME_RESETVAL  (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_WAIT_TIME_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_ULPTX_TEST_TIME_MASK (0x001FE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_ULPTX_TEST_TIME_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_ULPTX_TEST_TIME_RESETVAL (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_ULPTX_TEST_TIME_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_SEND_CONFIG_MASK    (0x00001800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_SEND_CONFIG_SHIFT   (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_SEND_CONFIG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_SEND_CONFIG_MAX     (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_DIG_TO_DIG_LOOPBK_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_DIG_TO_DIG_LOOPBK_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_DIG_TO_DIG_LOOPBK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_DIG_TO_DIG_LOOPBK_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_RUN_NEGEDGE_FIRST_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_RUN_NEGEDGE_FIRST_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_RUN_NEGEDGE_FIRST_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_RUN_NEGEDGE_FIRST_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LENGTH_OF_DESKEW_MASK (0x000001FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LENGTH_OF_DESKEW_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LENGTH_OF_DESKEW_RESETVAL (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LENGTH_OF_DESKEW_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LOOPBK_MODE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LOOPBK_MODE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LOOPBK_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_LOOPBK_MODE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_EN_MASK             (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_EN_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_EN_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_DL0_BIST_EN_MAX              (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT10_RESETVAL                     (0x0088002CU)

/* DL0_TX_DIG_TBIT11 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_IDLE_TIME_MASK  (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_IDLE_TIME_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_IDLE_TIME_RESETVAL (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_IDLE_TIME_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PKT_NUM_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PKT_NUM_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PKT_NUM_RESETVAL    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PKT_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_INF_MODE_MASK       (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_INF_MODE_SHIFT      (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_INF_MODE_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_INF_MODE_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_NUM_MASK        (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_NUM_SHIFT       (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_NUM_RESETVAL    (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_FRM_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_CLEAR_MASK          (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_CLEAR_SHIFT         (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_CLEAR_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_CLEAR_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PRBS_MASK           (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PRBS_SHIFT          (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PRBS_RESETVAL       (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_PRBS_MAX            (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_TEST_MODE_MASK      (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_TEST_MODE_SHIFT     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_TEST_MODE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_BIST_TEST_MODE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_UNUSED_0_MASK            (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_UNUSED_0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_UNUSED_0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_DL0_UNUSED_0_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT11_RESETVAL                     (0x0F0501B0U)

/* DL0_TX_DIG_TBIT12 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12_DL0_BIST_RUN_LENGTH_MASK     (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12_DL0_BIST_RUN_LENGTH_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12_DL0_BIST_RUN_LENGTH_RESETVAL (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12_DL0_BIST_RUN_LENGTH_MAX      (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT12_RESETVAL                     (0x00000028U)

/* DL0_TX_DIG_TBIT13 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_UNUSED_31_8_MASK         (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_UNUSED_31_8_SHIFT        (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_UNUSED_31_8_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_UNUSED_31_8_MAX          (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_BIST_IDLE_TIME_MASK      (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_BIST_IDLE_TIME_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_BIST_IDLE_TIME_RESETVAL  (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_DL0_BIST_IDLE_TIME_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT13_RESETVAL                     (0x0000000AU)

/* DL0_TX_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT4_MASK           (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT4_SHIFT          (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT4_RESETVAL       (0x000000DEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT4_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT3_MASK           (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT3_SHIFT          (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT3_RESETVAL       (0x000000CDU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT3_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT2_MASK           (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT2_SHIFT          (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT2_RESETVAL       (0x000000BCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT2_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT1_MASK           (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT1_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT1_RESETVAL       (0x000000ABU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_DL0_BIST_PKT1_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT14_RESETVAL                     (0xDECDBCABU)

/* DL0_TX_DIG_TBIT15 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_LFSR_FREEZE_MASK    (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_LFSR_FREEZE_SHIFT   (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_LFSR_FREEZE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_LFSR_FREEZE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_POINT_MASK  (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_POINT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_POINT_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_POINT_MAX   (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_EN_MASK     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_EN_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_DL0_BIST_ERR_INJ_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT15_RESETVAL                     (0x00000028U)

/* DL0_TX_DIG_TBIT16 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16_DL0_DIG_TBIT16_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16_DL0_DIG_TBIT16_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16_DL0_DIG_TBIT16_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16_DL0_DIG_TBIT16_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT16_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT17 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17_DL0_DIG_TBIT17_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17_DL0_DIG_TBIT17_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17_DL0_DIG_TBIT17_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17_DL0_DIG_TBIT17_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT17_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT18 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18_DL0_DIG_TBIT18_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18_DL0_DIG_TBIT18_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18_DL0_DIG_TBIT18_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18_DL0_DIG_TBIT18_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT18_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT19 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19_DL0_DIG_TBIT19_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19_DL0_DIG_TBIT19_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19_DL0_DIG_TBIT19_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19_DL0_DIG_TBIT19_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT19_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ISO_EN_MASK           (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ISO_EN_SHIFT          (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ISO_EN_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ISO_EN_MAX            (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_SEL_MASK    (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_SEL_SHIFT   (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_MASK        (0x38000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_SHIFT       (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LOAD_DPDN_MAX         (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATA_RATE_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATA_RATE_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATA_RATE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATA_RATE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATE_RATE_MASK   (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATE_RATE_SHIFT  (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATE_RATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_DATE_RATE_MAX    (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_MASK  (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_ULP_RCV_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_SEL_MASK   (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_SEL_SHIFT  (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_MASK       (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_SHIFT      (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_ULPS_PULDN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_SMPLR_CLK_EDGE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_SEL_MASK      (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_SEL_SHIFT     (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_MASK          (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_SHIFT         (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_BIST_EN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_SEL_MASK    (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_SEL_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_MASK        (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_SHIFT       (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_SEL_MASK     (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_SEL_SHIFT    (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_SEL_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_MASK         (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_SHIFT        (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_RST_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_SEL_MASK      (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_SEL_SHIFT     (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_MASK          (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_SHIFT         (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DP_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_SEL_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_SEL_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_MASK          (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LPTX_DN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_SEL_MASK   (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_SEL_SHIFT  (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_MASK       (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_SHIFT      (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_LDO_REF_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_SEL_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_SEL_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_MASK        (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_SEL_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_SEL_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_MASK        (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_SHIFT       (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_HSTX_RQST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_SEL_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_SEL_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_MASK        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_DL0_TM_GLOBAL_PD_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT20_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_MASK   (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_SHIFT  (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_RST_N_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_SEL_MASK    (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_SEL_SHIFT   (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_EN_MASK     (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_EN_SHIFT    (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SWAP_DPDN_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_SEL_MASK  (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_SERSYNTH_EN_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_SEL_MASK   (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_SEL_SHIFT  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_MASK       (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_DL0_TM_TX_DATA_HS_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT21_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22_DL0_DIG_TBIT22_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22_DL0_DIG_TBIT22_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22_DL0_DIG_TBIT22_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22_DL0_DIG_TBIT22_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT22_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT23 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23_DL0_DIG_TBIT23_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23_DL0_DIG_TBIT23_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23_DL0_DIG_TBIT23_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23_DL0_DIG_TBIT23_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT23_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24_DL0_DIG_TBIT24_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24_DL0_DIG_TBIT24_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24_DL0_DIG_TBIT24_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24_DL0_DIG_TBIT24_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT24_RESETVAL                     (0x00000000U)

/* DL0_TX_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5_DL0_ANA_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5_DL0_ANA_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5_DL0_ANA_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5_DL0_ANA_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT5_RESETVAL                      (0x00000000U)

/* DL0_TX_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_ANA_CTRL_FSM_STATE_MASK  (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_ANA_CTRL_FSM_STATE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_ANA_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_ANA_CTRL_FSM_STATE_MAX   (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_BIST_BAL_STATUS_MASK     (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_BIST_BAL_STATUS_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_BIST_BAL_STATUS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_DL0_BIST_BAL_STATUS_MAX      (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT25_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESC_RX_FSM_STATE_MASK (0xF8000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESC_RX_FSM_STATE_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESC_RX_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESC_RX_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_CTRL_FSM_STATE_MASK (0x07FE0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_CTRL_FSM_STATE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_CTRL_FSM_STATE_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_DATA_FSM_STATE_MASK (0x0001F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_DATA_FSM_STATE_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_DATA_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_DATA_ESCTX_DATA_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_HS_PATH_FSM_STATE_MASK (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_HS_PATH_FSM_STATE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_HS_PATH_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_DL0_TM_HS_PATH_FSM_STATE_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT26_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_TM_ANA_COMP_OUTS_MASK    (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_TM_ANA_COMP_OUTS_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_TM_ANA_COMP_OUTS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_TM_ANA_COMP_OUTS_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_UNUSED_7_0_MASK          (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_UNUSED_7_0_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_UNUSED_7_0_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_DL0_UNUSED_7_0_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT28_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT29 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPTX_CHE_MASK (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPTX_CHE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPTX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPTX_CHE_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPRX_CHE_MASK (0x00E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPRX_CHE_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_ULPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPCD_CHE_MASK (0x001C0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPCD_CHE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPCD_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPCD_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPRX_CHE_MASK (0x00038000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPRX_CHE_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_LPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_CTRLR_MASK  (0x00007800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_CTRLR_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_CTRLR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_TM_CUR_STATE_CTRLR_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_DATA_LANE_PASS_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_DATA_LANE_PASS_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_DATA_LANE_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_DATA_LANE_PASS_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPRX_PASS_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPRX_PASS_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPRX_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPRX_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPCD_PASS_MASK      (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPCD_PASS_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPCD_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_LPCD_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPRX_PASS_MASK     (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPRX_PASS_SHIFT    (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPRX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPRX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPTX_PASS_MASK     (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPTX_PASS_SHIFT    (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPTX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_ULPTX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_NEG_ERR_MASK     (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_NEG_ERR_SHIFT    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_NEG_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_NEG_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_POS_ERR_MASK     (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_POS_ERR_SHIFT    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_POS_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_HS_POS_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_POS_SYNC_MASK       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_POS_SYNC_SHIFT      (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_POS_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_POS_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_NEG_SYNC_MASK       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_NEG_SYNC_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_NEG_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_NEG_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_CMPLT_MASK          (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_CMPLT_SHIFT         (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_CMPLT_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_CMPLT_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_EN_STATUS_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_EN_STATUS_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_EN_STATUS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_DL0_BIST_EN_STATUS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT29_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT30 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_DL0_BIST_PAT_CHE_PKT_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT30_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT31 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_DL0_BIST_PAT_CHE_ERR_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT31_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT32 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32_DL0_DIG_TBIT32_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32_DL0_DIG_TBIT32_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32_DL0_DIG_TBIT32_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32_DL0_DIG_TBIT32_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT32_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT33 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33_DL0_DIG_TBIT33_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33_DL0_DIG_TBIT33_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33_DL0_DIG_TBIT33_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33_DL0_DIG_TBIT33_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT33_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT34 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34_DL0_DIG_TBIT34_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34_DL0_DIG_TBIT34_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34_DL0_DIG_TBIT34_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34_DL0_DIG_TBIT34_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT34_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT35 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35_DL0_DIG_TBIT35_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35_DL0_DIG_TBIT35_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35_DL0_DIG_TBIT35_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35_DL0_DIG_TBIT35_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT35_RESETVAL                     (0x00000000U)

/* DL0_TX_DIG_TBIT36 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36_DL0_DIG_TBIT36_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36_DL0_DIG_TBIT36_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36_DL0_DIG_TBIT36_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36_DL0_DIG_TBIT36_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_DIG_TBIT36_RESETVAL                     (0x00000000U)

/* DL1_TX_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_DL1_ANA_TBIT0_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_DL1_ANA_TBIT0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_DL1_ANA_TBIT0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_DL1_ANA_TBIT0_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MASK           (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_CLK0_ANA_TBIT0_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_CLK0_ANA_TBIT0_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MAX            (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MASK        (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_MASK         (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_SHIFT        (0x00000006U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MASK        (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_MASK         (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_SHIFT        (0x0000000EU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MASK          (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_SHIFT         (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_EN_MASK           (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_EN_SHIFT          (0x00000016U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX           (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MAX         (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MAX         (32U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_RESETVAL                      (0x00000000U)

/* DL1_TX_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1_DL1_ANA_TBIT1_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1_DL1_ANA_TBIT1_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1_DL1_ANA_TBIT1_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1_DL1_ANA_TBIT1_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT1_RESETVAL                      (0x00000000U)

/* DL1_TX_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2_DL1_ANA_TBIT2_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2_DL1_ANA_TBIT2_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2_DL1_ANA_TBIT2_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2_DL1_ANA_TBIT2_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT2_RESETVAL                      (0x00000000U)

/* DL1_TX_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3_DL1_ANA_TBIT3_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3_DL1_ANA_TBIT3_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3_DL1_ANA_TBIT3_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3_DL1_ANA_TBIT3_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT3_RESETVAL                      (0x00000000U)

/* DL1_TX_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4_DL1_ANA_TBIT4_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4_DL1_ANA_TBIT4_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4_DL1_ANA_TBIT4_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4_DL1_ANA_TBIT4_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT4_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_31_13_MASK         (0xFFFFE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_31_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_31_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_31_13_MAX          (0x0007FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_ULPS_PULLDN_CNT_MASK      (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_ULPS_PULLDN_CNT_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_ULPS_PULLDN_CNT_RESETVAL  (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_ULPS_PULLDN_CNT_MAX       (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_7_5_MASK           (0x000000E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_7_5_SHIFT          (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_7_5_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_UNUSED_7_5_MAX            (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_LDO_EN_CNT_MASK           (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_LDO_EN_CNT_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_LDO_EN_CNT_RESETVAL       (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_DL1_LDO_EN_CNT_MAX            (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT0_RESETVAL                      (0x00000606U)

/* DL1_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DP_MASK         (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DP_SHIFT        (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DP_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DP_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DN_MASK         (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DN_SHIFT        (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_DN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_EN_MASK         (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_EN_SHIFT        (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TEST_LPTX_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_READY_SKEW_CAL_MASK    (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_READY_SKEW_CAL_SHIFT   (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_READY_SKEW_CAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_READY_SKEW_CAL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HAFCYC_OVERRIDE_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HAFCYC_OVERRIDE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HAFCYC_OVERRIDE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HAFCYC_OVERRIDE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HSFCYC_MASK    (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HSFCYC_SHIFT   (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HSFCYC_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_TM_HS_PREP_HSFCYC_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TRAIL_OFFSET_MASK      (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TRAIL_OFFSET_SHIFT     (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TRAIL_OFFSET_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TRAIL_OFFSET_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_ZERO_OFFSET_MASK       (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_ZERO_OFFSET_SHIFT      (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_ZERO_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_ZERO_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_PREP_OFFSET_MASK       (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_PREP_OFFSET_SHIFT      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_PREP_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_PREP_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TLPX_OFFSET_MASK       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TLPX_OFFSET_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TLPX_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_DL1_HS_TLPX_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT1_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_MASK      (0x07F80000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_SHIFT     (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_SEL_MASK  (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_SEL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SEQ_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_MASK (0x0003FC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_SEL_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_SEL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_SKEW_CAL_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_MASK       (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_SEL_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_SEL_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_DL1_TM_HS_SYNC_PKT_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT2_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_SERSYNTH_LOOPBACK_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_SERSYNTH_LOOPBACK_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_SERSYNTH_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_SERSYNTH_LOOPBACK_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_STATE_MASK      (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_STATE_SHIFT     (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_STATE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_STATE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_EN_MASK         (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_EN_SHIFT        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_DL1_BAL_FORCE_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT3_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_CONTENTION_EN_MASK        (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_CONTENTION_EN_SHIFT       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_CONTENTION_EN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_CONTENTION_EN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_UNUSED_14_13_MASK         (0x00006000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_UNUSED_14_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_UNUSED_14_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_UNUSED_14_13_MAX          (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_FORCE_RX_MODE_MASK        (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_FORCE_RX_MODE_SHIFT       (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_FORCE_RX_MODE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_FORCE_RX_MODE_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DP_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DP_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DN_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_MASK       (0x000003FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_RSTN_MASK  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_RSTN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_RSTN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_RSTN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_EN_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_EN_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_DL1_TEST_DATA_LPTX_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT4_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5_DL1_DIG_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5_DL1_DIG_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5_DL1_DIG_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5_DL1_DIG_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT5_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6_DL1_DIG_TBIT6_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6_DL1_DIG_TBIT6_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6_DL1_DIG_TBIT6_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6_DL1_DIG_TBIT6_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT6_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7_DL1_DIG_TBIT7_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7_DL1_DIG_TBIT7_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7_DL1_DIG_TBIT7_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7_DL1_DIG_TBIT7_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT7_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8_DL1_DIG_TBIT8_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8_DL1_DIG_TBIT8_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8_DL1_DIG_TBIT8_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8_DL1_DIG_TBIT8_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT8_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9_DL1_DIG_TBIT9_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9_DL1_DIG_TBIT9_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9_DL1_DIG_TBIT9_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9_DL1_DIG_TBIT9_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT9_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_WAIT_TIME_MASK      (0x01E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_WAIT_TIME_SHIFT     (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_WAIT_TIME_RESETVAL  (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_WAIT_TIME_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_ULPTX_TEST_TIME_MASK (0x001FE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_ULPTX_TEST_TIME_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_ULPTX_TEST_TIME_RESETVAL (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_ULPTX_TEST_TIME_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_SEND_CONFIG_MASK    (0x00001800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_SEND_CONFIG_SHIFT   (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_SEND_CONFIG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_SEND_CONFIG_MAX     (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_DIG_TO_DIG_LOOPBK_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_DIG_TO_DIG_LOOPBK_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_DIG_TO_DIG_LOOPBK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_DIG_TO_DIG_LOOPBK_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_RUN_NEGEDGE_FIRST_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_RUN_NEGEDGE_FIRST_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_RUN_NEGEDGE_FIRST_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_RUN_NEGEDGE_FIRST_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LENGTH_OF_DESKEW_MASK (0x000001FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LENGTH_OF_DESKEW_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LENGTH_OF_DESKEW_RESETVAL (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LENGTH_OF_DESKEW_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LOOPBK_MODE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LOOPBK_MODE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LOOPBK_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_LOOPBK_MODE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_EN_MASK             (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_EN_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_EN_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_DL1_BIST_EN_MAX              (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT10_RESETVAL                     (0x0088002CU)

/* DL1_TX_DIG_TBIT11 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_IDLE_TIME_MASK  (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_IDLE_TIME_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_IDLE_TIME_RESETVAL (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_IDLE_TIME_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PKT_NUM_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PKT_NUM_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PKT_NUM_RESETVAL    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PKT_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_INF_MODE_MASK       (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_INF_MODE_SHIFT      (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_INF_MODE_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_INF_MODE_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_NUM_MASK        (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_NUM_SHIFT       (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_NUM_RESETVAL    (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_FRM_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_CLEAR_MASK          (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_CLEAR_SHIFT         (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_CLEAR_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_CLEAR_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PRBS_MASK           (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PRBS_SHIFT          (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PRBS_RESETVAL       (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_PRBS_MAX            (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_TEST_MODE_MASK      (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_TEST_MODE_SHIFT     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_TEST_MODE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_BIST_TEST_MODE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_UNUSED_0_MASK            (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_UNUSED_0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_UNUSED_0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_DL1_UNUSED_0_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT11_RESETVAL                     (0x0F0501B0U)

/* DL1_TX_DIG_TBIT12 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12_DL1_BIST_RUN_LENGTH_MASK     (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12_DL1_BIST_RUN_LENGTH_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12_DL1_BIST_RUN_LENGTH_RESETVAL (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12_DL1_BIST_RUN_LENGTH_MAX      (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT12_RESETVAL                     (0x00000028U)

/* DL1_TX_DIG_TBIT13 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_UNUSED_31_8_MASK         (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_UNUSED_31_8_SHIFT        (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_UNUSED_31_8_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_UNUSED_31_8_MAX          (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_BIST_IDLE_TIME_MASK      (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_BIST_IDLE_TIME_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_BIST_IDLE_TIME_RESETVAL  (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_DL1_BIST_IDLE_TIME_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT13_RESETVAL                     (0x0000000AU)

/* DL1_TX_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT4_MASK           (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT4_SHIFT          (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT4_RESETVAL       (0x000000DEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT4_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT3_MASK           (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT3_SHIFT          (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT3_RESETVAL       (0x000000CDU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT3_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT2_MASK           (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT2_SHIFT          (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT2_RESETVAL       (0x000000BCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT2_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT1_MASK           (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT1_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT1_RESETVAL       (0x000000ABU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_DL1_BIST_PKT1_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT14_RESETVAL                     (0xDECDBCABU)

/* DL1_TX_DIG_TBIT15 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_LFSR_FREEZE_MASK    (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_LFSR_FREEZE_SHIFT   (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_LFSR_FREEZE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_LFSR_FREEZE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_POINT_MASK  (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_POINT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_POINT_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_POINT_MAX   (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_EN_MASK     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_EN_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_DL1_BIST_ERR_INJ_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT15_RESETVAL                     (0x00000028U)

/* DL1_TX_DIG_TBIT16 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16_DL1_DIG_TBIT16_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16_DL1_DIG_TBIT16_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16_DL1_DIG_TBIT16_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16_DL1_DIG_TBIT16_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT16_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT17 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17_DL1_DIG_TBIT17_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17_DL1_DIG_TBIT17_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17_DL1_DIG_TBIT17_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17_DL1_DIG_TBIT17_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT17_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT18 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18_DL1_DIG_TBIT18_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18_DL1_DIG_TBIT18_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18_DL1_DIG_TBIT18_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18_DL1_DIG_TBIT18_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT18_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT19 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19_DL1_DIG_TBIT19_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19_DL1_DIG_TBIT19_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19_DL1_DIG_TBIT19_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19_DL1_DIG_TBIT19_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT19_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ISO_EN_MASK           (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ISO_EN_SHIFT          (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ISO_EN_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ISO_EN_MAX            (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_SEL_MASK    (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_SEL_SHIFT   (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_MASK        (0x38000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_SHIFT       (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LOAD_DPDN_MAX         (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATA_RATE_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATA_RATE_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATA_RATE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATA_RATE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATE_RATE_MASK   (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATE_RATE_SHIFT  (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATE_RATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_DATE_RATE_MAX    (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_MASK  (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_ULP_RCV_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_SEL_MASK   (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_SEL_SHIFT  (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_MASK       (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_SHIFT      (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_ULPS_PULDN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_SMPLR_CLK_EDGE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_SEL_MASK      (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_SEL_SHIFT     (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_MASK          (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_SHIFT         (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_BIST_EN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_SEL_MASK    (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_SEL_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_MASK        (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_SHIFT       (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_SEL_MASK     (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_SEL_SHIFT    (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_SEL_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_MASK         (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_SHIFT        (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_RST_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_SEL_MASK      (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_SEL_SHIFT     (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_MASK          (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_SHIFT         (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DP_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_SEL_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_SEL_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_MASK          (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LPTX_DN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_SEL_MASK   (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_SEL_SHIFT  (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_MASK       (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_SHIFT      (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_LDO_REF_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_SEL_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_SEL_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_MASK        (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_SEL_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_SEL_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_MASK        (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_SHIFT       (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_HSTX_RQST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_SEL_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_SEL_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_MASK        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_DL1_TM_GLOBAL_PD_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT20_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_MASK   (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_SHIFT  (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_RST_N_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_SEL_MASK    (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_SEL_SHIFT   (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_EN_MASK     (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_EN_SHIFT    (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SWAP_DPDN_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_SEL_MASK  (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_SERSYNTH_EN_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_SEL_MASK   (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_SEL_SHIFT  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_MASK       (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_DL1_TM_TX_DATA_HS_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT21_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22_DL1_DIG_TBIT22_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22_DL1_DIG_TBIT22_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22_DL1_DIG_TBIT22_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22_DL1_DIG_TBIT22_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT22_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT23 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23_DL1_DIG_TBIT23_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23_DL1_DIG_TBIT23_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23_DL1_DIG_TBIT23_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23_DL1_DIG_TBIT23_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT23_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24_DL1_DIG_TBIT24_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24_DL1_DIG_TBIT24_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24_DL1_DIG_TBIT24_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24_DL1_DIG_TBIT24_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT24_RESETVAL                     (0x00000000U)

/* DL1_TX_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5_DL1_ANA_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5_DL1_ANA_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5_DL1_ANA_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5_DL1_ANA_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT5_RESETVAL                      (0x00000000U)

/* DL1_TX_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_ANA_CTRL_FSM_STATE_MASK  (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_ANA_CTRL_FSM_STATE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_ANA_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_ANA_CTRL_FSM_STATE_MAX   (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_BIST_BAL_STATUS_MASK     (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_BIST_BAL_STATUS_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_BIST_BAL_STATUS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_DL1_BIST_BAL_STATUS_MAX      (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT25_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESC_RX_FSM_STATE_MASK (0xF8000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESC_RX_FSM_STATE_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESC_RX_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESC_RX_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_CTRL_FSM_STATE_MASK (0x07FE0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_CTRL_FSM_STATE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_CTRL_FSM_STATE_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_DATA_FSM_STATE_MASK (0x0001F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_DATA_FSM_STATE_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_DATA_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_DATA_ESCTX_DATA_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_HS_PATH_FSM_STATE_MASK (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_HS_PATH_FSM_STATE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_HS_PATH_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_DL1_TM_HS_PATH_FSM_STATE_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT26_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_TM_ANA_COMP_OUTS_MASK    (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_TM_ANA_COMP_OUTS_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_TM_ANA_COMP_OUTS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_TM_ANA_COMP_OUTS_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_UNUSED_7_0_MASK          (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_UNUSED_7_0_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_UNUSED_7_0_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_DL1_UNUSED_7_0_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT28_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT29 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPTX_CHE_MASK (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPTX_CHE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPTX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPTX_CHE_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPRX_CHE_MASK (0x00E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPRX_CHE_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_ULPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPCD_CHE_MASK (0x001C0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPCD_CHE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPCD_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPCD_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPRX_CHE_MASK (0x00038000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPRX_CHE_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_LPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_CTRLR_MASK  (0x00007800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_CTRLR_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_CTRLR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_TM_CUR_STATE_CTRLR_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_DATA_LANE_PASS_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_DATA_LANE_PASS_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_DATA_LANE_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_DATA_LANE_PASS_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPRX_PASS_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPRX_PASS_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPRX_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPRX_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPCD_PASS_MASK      (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPCD_PASS_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPCD_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_LPCD_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPRX_PASS_MASK     (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPRX_PASS_SHIFT    (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPRX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPRX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPTX_PASS_MASK     (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPTX_PASS_SHIFT    (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPTX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_ULPTX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_NEG_ERR_MASK     (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_NEG_ERR_SHIFT    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_NEG_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_NEG_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_POS_ERR_MASK     (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_POS_ERR_SHIFT    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_POS_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_HS_POS_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_POS_SYNC_MASK       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_POS_SYNC_SHIFT      (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_POS_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_POS_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_NEG_SYNC_MASK       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_NEG_SYNC_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_NEG_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_NEG_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_CMPLT_MASK          (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_CMPLT_SHIFT         (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_CMPLT_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_CMPLT_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_EN_STATUS_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_EN_STATUS_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_EN_STATUS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_DL1_BIST_EN_STATUS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT29_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT30 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_DL1_BIST_PAT_CHE_PKT_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT30_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT31 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_DL1_BIST_PAT_CHE_ERR_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT31_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT32 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32_DL1_DIG_TBIT32_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32_DL1_DIG_TBIT32_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32_DL1_DIG_TBIT32_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32_DL1_DIG_TBIT32_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT32_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT33 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33_DL1_DIG_TBIT33_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33_DL1_DIG_TBIT33_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33_DL1_DIG_TBIT33_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33_DL1_DIG_TBIT33_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT33_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT34 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34_DL1_DIG_TBIT34_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34_DL1_DIG_TBIT34_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34_DL1_DIG_TBIT34_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34_DL1_DIG_TBIT34_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT34_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT35 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35_DL1_DIG_TBIT35_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35_DL1_DIG_TBIT35_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35_DL1_DIG_TBIT35_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35_DL1_DIG_TBIT35_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT35_RESETVAL                     (0x00000000U)

/* DL1_TX_DIG_TBIT36 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36_DL1_DIG_TBIT36_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36_DL1_DIG_TBIT36_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36_DL1_DIG_TBIT36_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36_DL1_DIG_TBIT36_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_DIG_TBIT36_RESETVAL                     (0x00000000U)

/* DL2_TX_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_DL2_ANA_TBIT0_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_DL2_ANA_TBIT0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_DL2_ANA_TBIT0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_DL2_ANA_TBIT0_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MASK           (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_CLK0_ANA_TBIT0_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_CLK0_ANA_TBIT0_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MAX            (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MASK        (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_MASK         (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_SHIFT        (0x00000006U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MASK        (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_MASK         (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_SHIFT        (0x0000000EU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MASK          (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_SHIFT         (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_EN_MASK           (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_EN_SHIFT          (0x00000016U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX           (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MAX         (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MAX         (32U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_RESETVAL                      (0x00000000U)

/* DL2_TX_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1_DL2_ANA_TBIT1_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1_DL2_ANA_TBIT1_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1_DL2_ANA_TBIT1_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1_DL2_ANA_TBIT1_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT1_RESETVAL                      (0x00000000U)

/* DL2_TX_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2_DL2_ANA_TBIT2_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2_DL2_ANA_TBIT2_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2_DL2_ANA_TBIT2_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2_DL2_ANA_TBIT2_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT2_RESETVAL                      (0x00000000U)

/* DL2_TX_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3_DL2_ANA_TBIT3_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3_DL2_ANA_TBIT3_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3_DL2_ANA_TBIT3_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3_DL2_ANA_TBIT3_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT3_RESETVAL                      (0x00000000U)

/* DL2_TX_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4_DL2_ANA_TBIT4_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4_DL2_ANA_TBIT4_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4_DL2_ANA_TBIT4_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4_DL2_ANA_TBIT4_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT4_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_31_13_MASK         (0xFFFFE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_31_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_31_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_31_13_MAX          (0x0007FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_ULPS_PULLDN_CNT_MASK      (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_ULPS_PULLDN_CNT_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_ULPS_PULLDN_CNT_RESETVAL  (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_ULPS_PULLDN_CNT_MAX       (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_7_5_MASK           (0x000000E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_7_5_SHIFT          (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_7_5_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_UNUSED_7_5_MAX            (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_LDO_EN_CNT_MASK           (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_LDO_EN_CNT_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_LDO_EN_CNT_RESETVAL       (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_DL2_LDO_EN_CNT_MAX            (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT0_RESETVAL                      (0x00000606U)

/* DL2_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DP_MASK         (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DP_SHIFT        (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DP_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DP_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DN_MASK         (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DN_SHIFT        (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_DN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_EN_MASK         (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_EN_SHIFT        (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TEST_LPTX_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_READY_SKEW_CAL_MASK    (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_READY_SKEW_CAL_SHIFT   (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_READY_SKEW_CAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_READY_SKEW_CAL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HAFCYC_OVERRIDE_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HAFCYC_OVERRIDE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HAFCYC_OVERRIDE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HAFCYC_OVERRIDE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HSFCYC_MASK    (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HSFCYC_SHIFT   (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HSFCYC_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_TM_HS_PREP_HSFCYC_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TRAIL_OFFSET_MASK      (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TRAIL_OFFSET_SHIFT     (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TRAIL_OFFSET_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TRAIL_OFFSET_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_ZERO_OFFSET_MASK       (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_ZERO_OFFSET_SHIFT      (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_ZERO_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_ZERO_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_PREP_OFFSET_MASK       (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_PREP_OFFSET_SHIFT      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_PREP_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_PREP_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TLPX_OFFSET_MASK       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TLPX_OFFSET_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TLPX_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_DL2_HS_TLPX_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT1_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_MASK      (0x07F80000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_SHIFT     (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_SEL_MASK  (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_SEL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SEQ_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_MASK (0x0003FC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_SEL_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_SEL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_SKEW_CAL_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_MASK       (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_SEL_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_SEL_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_DL2_TM_HS_SYNC_PKT_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT2_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_SERSYNTH_LOOPBACK_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_SERSYNTH_LOOPBACK_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_SERSYNTH_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_SERSYNTH_LOOPBACK_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_STATE_MASK      (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_STATE_SHIFT     (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_STATE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_STATE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_EN_MASK         (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_EN_SHIFT        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_DL2_BAL_FORCE_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT3_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_CONTENTION_EN_MASK        (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_CONTENTION_EN_SHIFT       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_CONTENTION_EN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_CONTENTION_EN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_UNUSED_14_13_MASK         (0x00006000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_UNUSED_14_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_UNUSED_14_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_UNUSED_14_13_MAX          (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_FORCE_RX_MODE_MASK        (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_FORCE_RX_MODE_SHIFT       (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_FORCE_RX_MODE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_FORCE_RX_MODE_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DP_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DP_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DN_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_MASK       (0x000003FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_RSTN_MASK  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_RSTN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_RSTN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_RSTN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_EN_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_EN_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_DL2_TEST_DATA_LPTX_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT4_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5_DL2_DIG_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5_DL2_DIG_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5_DL2_DIG_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5_DL2_DIG_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT5_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6_DL2_DIG_TBIT6_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6_DL2_DIG_TBIT6_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6_DL2_DIG_TBIT6_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6_DL2_DIG_TBIT6_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT6_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7_DL2_DIG_TBIT7_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7_DL2_DIG_TBIT7_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7_DL2_DIG_TBIT7_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7_DL2_DIG_TBIT7_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT7_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8_DL2_DIG_TBIT8_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8_DL2_DIG_TBIT8_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8_DL2_DIG_TBIT8_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8_DL2_DIG_TBIT8_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT8_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9_DL2_DIG_TBIT9_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9_DL2_DIG_TBIT9_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9_DL2_DIG_TBIT9_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9_DL2_DIG_TBIT9_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT9_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_WAIT_TIME_MASK      (0x01E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_WAIT_TIME_SHIFT     (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_WAIT_TIME_RESETVAL  (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_WAIT_TIME_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_ULPTX_TEST_TIME_MASK (0x001FE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_ULPTX_TEST_TIME_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_ULPTX_TEST_TIME_RESETVAL (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_ULPTX_TEST_TIME_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_SEND_CONFIG_MASK    (0x00001800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_SEND_CONFIG_SHIFT   (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_SEND_CONFIG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_SEND_CONFIG_MAX     (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_DIG_TO_DIG_LOOPBK_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_DIG_TO_DIG_LOOPBK_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_DIG_TO_DIG_LOOPBK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_DIG_TO_DIG_LOOPBK_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_RUN_NEGEDGE_FIRST_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_RUN_NEGEDGE_FIRST_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_RUN_NEGEDGE_FIRST_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_RUN_NEGEDGE_FIRST_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LENGTH_OF_DESKEW_MASK (0x000001FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LENGTH_OF_DESKEW_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LENGTH_OF_DESKEW_RESETVAL (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LENGTH_OF_DESKEW_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LOOPBK_MODE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LOOPBK_MODE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LOOPBK_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_LOOPBK_MODE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_EN_MASK             (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_EN_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_EN_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_DL2_BIST_EN_MAX              (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT10_RESETVAL                     (0x0088002CU)

/* DL2_TX_DIG_TBIT11 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_IDLE_TIME_MASK  (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_IDLE_TIME_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_IDLE_TIME_RESETVAL (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_IDLE_TIME_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PKT_NUM_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PKT_NUM_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PKT_NUM_RESETVAL    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PKT_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_INF_MODE_MASK       (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_INF_MODE_SHIFT      (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_INF_MODE_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_INF_MODE_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_NUM_MASK        (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_NUM_SHIFT       (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_NUM_RESETVAL    (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_FRM_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_CLEAR_MASK          (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_CLEAR_SHIFT         (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_CLEAR_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_CLEAR_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PRBS_MASK           (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PRBS_SHIFT          (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PRBS_RESETVAL       (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_PRBS_MAX            (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_TEST_MODE_MASK      (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_TEST_MODE_SHIFT     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_TEST_MODE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_BIST_TEST_MODE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_UNUSED_0_MASK            (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_UNUSED_0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_UNUSED_0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_DL2_UNUSED_0_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT11_RESETVAL                     (0x0F0501B0U)

/* DL2_TX_DIG_TBIT12 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12_DL2_BIST_RUN_LENGTH_MASK     (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12_DL2_BIST_RUN_LENGTH_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12_DL2_BIST_RUN_LENGTH_RESETVAL (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12_DL2_BIST_RUN_LENGTH_MAX      (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT12_RESETVAL                     (0x00000028U)

/* DL2_TX_DIG_TBIT13 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_UNUSED_31_8_MASK         (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_UNUSED_31_8_SHIFT        (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_UNUSED_31_8_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_UNUSED_31_8_MAX          (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_BIST_IDLE_TIME_MASK      (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_BIST_IDLE_TIME_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_BIST_IDLE_TIME_RESETVAL  (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_DL2_BIST_IDLE_TIME_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT13_RESETVAL                     (0x0000000AU)

/* DL2_TX_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT4_MASK           (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT4_SHIFT          (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT4_RESETVAL       (0x000000DEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT4_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT3_MASK           (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT3_SHIFT          (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT3_RESETVAL       (0x000000CDU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT3_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT2_MASK           (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT2_SHIFT          (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT2_RESETVAL       (0x000000BCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT2_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT1_MASK           (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT1_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT1_RESETVAL       (0x000000ABU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_DL2_BIST_PKT1_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT14_RESETVAL                     (0xDECDBCABU)

/* DL2_TX_DIG_TBIT15 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_LFSR_FREEZE_MASK    (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_LFSR_FREEZE_SHIFT   (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_LFSR_FREEZE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_LFSR_FREEZE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_POINT_MASK  (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_POINT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_POINT_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_POINT_MAX   (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_EN_MASK     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_EN_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_DL2_BIST_ERR_INJ_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT15_RESETVAL                     (0x00000028U)

/* DL2_TX_DIG_TBIT16 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16_DL2_DIG_TBIT16_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16_DL2_DIG_TBIT16_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16_DL2_DIG_TBIT16_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16_DL2_DIG_TBIT16_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT16_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT17 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17_DL2_DIG_TBIT17_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17_DL2_DIG_TBIT17_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17_DL2_DIG_TBIT17_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17_DL2_DIG_TBIT17_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT17_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT18 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18_DL2_DIG_TBIT18_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18_DL2_DIG_TBIT18_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18_DL2_DIG_TBIT18_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18_DL2_DIG_TBIT18_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT18_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT19 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19_DL2_DIG_TBIT19_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19_DL2_DIG_TBIT19_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19_DL2_DIG_TBIT19_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19_DL2_DIG_TBIT19_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT19_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ISO_EN_MASK           (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ISO_EN_SHIFT          (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ISO_EN_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ISO_EN_MAX            (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_SEL_MASK    (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_SEL_SHIFT   (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_MASK        (0x38000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_SHIFT       (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LOAD_DPDN_MAX         (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATA_RATE_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATA_RATE_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATA_RATE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATA_RATE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATE_RATE_MASK   (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATE_RATE_SHIFT  (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATE_RATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_DATE_RATE_MAX    (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_MASK  (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_ULP_RCV_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_SEL_MASK   (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_SEL_SHIFT  (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_MASK       (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_SHIFT      (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_ULPS_PULDN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_SMPLR_CLK_EDGE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_SEL_MASK      (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_SEL_SHIFT     (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_MASK          (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_SHIFT         (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_BIST_EN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_SEL_MASK    (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_SEL_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_MASK        (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_SHIFT       (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_SEL_MASK     (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_SEL_SHIFT    (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_SEL_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_MASK         (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_SHIFT        (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_RST_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_SEL_MASK      (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_SEL_SHIFT     (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_MASK          (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_SHIFT         (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DP_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_SEL_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_SEL_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_MASK          (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LPTX_DN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_SEL_MASK   (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_SEL_SHIFT  (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_MASK       (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_SHIFT      (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_LDO_REF_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_SEL_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_SEL_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_MASK        (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_SEL_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_SEL_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_MASK        (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_SHIFT       (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_HSTX_RQST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_SEL_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_SEL_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_MASK        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_DL2_TM_GLOBAL_PD_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT20_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_MASK   (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_SHIFT  (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_RST_N_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_SEL_MASK    (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_SEL_SHIFT   (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_EN_MASK     (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_EN_SHIFT    (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SWAP_DPDN_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_SEL_MASK  (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_SERSYNTH_EN_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_SEL_MASK   (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_SEL_SHIFT  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_MASK       (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_DL2_TM_TX_DATA_HS_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT21_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22_DL2_DIG_TBIT22_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22_DL2_DIG_TBIT22_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22_DL2_DIG_TBIT22_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22_DL2_DIG_TBIT22_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT22_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT23 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23_DL2_DIG_TBIT23_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23_DL2_DIG_TBIT23_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23_DL2_DIG_TBIT23_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23_DL2_DIG_TBIT23_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT23_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24_DL2_DIG_TBIT24_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24_DL2_DIG_TBIT24_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24_DL2_DIG_TBIT24_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24_DL2_DIG_TBIT24_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT24_RESETVAL                     (0x00000000U)

/* DL2_TX_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5_DL2_ANA_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5_DL2_ANA_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5_DL2_ANA_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5_DL2_ANA_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT5_RESETVAL                      (0x00000000U)

/* DL2_TX_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_ANA_CTRL_FSM_STATE_MASK  (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_ANA_CTRL_FSM_STATE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_ANA_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_ANA_CTRL_FSM_STATE_MAX   (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_BIST_BAL_STATUS_MASK     (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_BIST_BAL_STATUS_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_BIST_BAL_STATUS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_DL2_BIST_BAL_STATUS_MAX      (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT25_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESC_RX_FSM_STATE_MASK (0xF8000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESC_RX_FSM_STATE_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESC_RX_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESC_RX_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_CTRL_FSM_STATE_MASK (0x07FE0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_CTRL_FSM_STATE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_CTRL_FSM_STATE_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_DATA_FSM_STATE_MASK (0x0001F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_DATA_FSM_STATE_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_DATA_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_DATA_ESCTX_DATA_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_HS_PATH_FSM_STATE_MASK (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_HS_PATH_FSM_STATE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_HS_PATH_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_DL2_TM_HS_PATH_FSM_STATE_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT26_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_TM_ANA_COMP_OUTS_MASK    (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_TM_ANA_COMP_OUTS_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_TM_ANA_COMP_OUTS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_TM_ANA_COMP_OUTS_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_UNUSED_7_0_MASK          (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_UNUSED_7_0_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_UNUSED_7_0_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_DL2_UNUSED_7_0_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT28_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT29 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPTX_CHE_MASK (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPTX_CHE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPTX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPTX_CHE_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPRX_CHE_MASK (0x00E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPRX_CHE_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_ULPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPCD_CHE_MASK (0x001C0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPCD_CHE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPCD_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPCD_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPRX_CHE_MASK (0x00038000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPRX_CHE_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_LPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_CTRLR_MASK  (0x00007800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_CTRLR_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_CTRLR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_TM_CUR_STATE_CTRLR_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_DATA_LANE_PASS_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_DATA_LANE_PASS_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_DATA_LANE_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_DATA_LANE_PASS_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPRX_PASS_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPRX_PASS_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPRX_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPRX_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPCD_PASS_MASK      (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPCD_PASS_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPCD_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_LPCD_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPRX_PASS_MASK     (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPRX_PASS_SHIFT    (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPRX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPRX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPTX_PASS_MASK     (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPTX_PASS_SHIFT    (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPTX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_ULPTX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_NEG_ERR_MASK     (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_NEG_ERR_SHIFT    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_NEG_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_NEG_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_POS_ERR_MASK     (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_POS_ERR_SHIFT    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_POS_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_HS_POS_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_POS_SYNC_MASK       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_POS_SYNC_SHIFT      (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_POS_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_POS_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_NEG_SYNC_MASK       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_NEG_SYNC_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_NEG_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_NEG_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_CMPLT_MASK          (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_CMPLT_SHIFT         (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_CMPLT_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_CMPLT_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_EN_STATUS_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_EN_STATUS_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_EN_STATUS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_DL2_BIST_EN_STATUS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT29_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT30 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_DL2_BIST_PAT_CHE_PKT_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT30_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT31 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_DL2_BIST_PAT_CHE_ERR_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT31_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT32 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32_DL2_DIG_TBIT32_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32_DL2_DIG_TBIT32_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32_DL2_DIG_TBIT32_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32_DL2_DIG_TBIT32_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT32_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT33 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33_DL2_DIG_TBIT33_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33_DL2_DIG_TBIT33_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33_DL2_DIG_TBIT33_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33_DL2_DIG_TBIT33_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT33_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT34 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34_DL2_DIG_TBIT34_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34_DL2_DIG_TBIT34_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34_DL2_DIG_TBIT34_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34_DL2_DIG_TBIT34_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT34_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT35 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35_DL2_DIG_TBIT35_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35_DL2_DIG_TBIT35_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35_DL2_DIG_TBIT35_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35_DL2_DIG_TBIT35_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT35_RESETVAL                     (0x00000000U)

/* DL2_TX_DIG_TBIT36 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36_DL2_DIG_TBIT36_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36_DL2_DIG_TBIT36_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36_DL2_DIG_TBIT36_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36_DL2_DIG_TBIT36_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_DIG_TBIT36_RESETVAL                     (0x00000000U)

/* DL3_TX_ANA_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_DL3_ANA_TBIT0_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_DL3_ANA_TBIT0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_DL3_ANA_TBIT0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_DL3_ANA_TBIT0_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MASK           (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_CLK0_ANA_TBIT0_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_CLK0_ANA_TBIT0_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_CLK0_ANA_TBIT0_MAX            (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MASK        (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_MASK         (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN_SHIFT        (0x00000006U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MASK        (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_MASK         (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN_SHIFT        (0x0000000EU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MASK          (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_SHIFT         (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_EN_MASK           (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_EN_SHIFT          (0x00000016U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX           (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL_MAX         (32U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL_MAX         (32U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_RESETVAL                      (0x00000000U)

/* DL3_TX_ANA_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1_DL3_ANA_TBIT1_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1_DL3_ANA_TBIT1_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1_DL3_ANA_TBIT1_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1_DL3_ANA_TBIT1_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT1_RESETVAL                      (0x00000000U)

/* DL3_TX_ANA_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2_DL3_ANA_TBIT2_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2_DL3_ANA_TBIT2_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2_DL3_ANA_TBIT2_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2_DL3_ANA_TBIT2_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT2_RESETVAL                      (0x00000000U)

/* DL3_TX_ANA_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3_DL3_ANA_TBIT3_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3_DL3_ANA_TBIT3_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3_DL3_ANA_TBIT3_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3_DL3_ANA_TBIT3_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT3_RESETVAL                      (0x00000000U)

/* DL3_TX_ANA_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4_DL3_ANA_TBIT4_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4_DL3_ANA_TBIT4_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4_DL3_ANA_TBIT4_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4_DL3_ANA_TBIT4_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT4_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_31_13_MASK         (0xFFFFE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_31_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_31_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_31_13_MAX          (0x0007FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_ULPS_PULLDN_CNT_MASK      (0x00001F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_ULPS_PULLDN_CNT_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_ULPS_PULLDN_CNT_RESETVAL  (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_ULPS_PULLDN_CNT_MAX       (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_7_5_MASK           (0x000000E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_7_5_SHIFT          (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_7_5_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_UNUSED_7_5_MAX            (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_LDO_EN_CNT_MASK           (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_LDO_EN_CNT_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_LDO_EN_CNT_RESETVAL       (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_DL3_LDO_EN_CNT_MAX            (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT0_RESETVAL                      (0x00000606U)

/* DL3_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DP_MASK         (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DP_SHIFT        (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DP_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DP_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DN_MASK         (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DN_SHIFT        (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_DN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_EN_MASK         (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_EN_SHIFT        (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TEST_LPTX_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_READY_SKEW_CAL_MASK    (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_READY_SKEW_CAL_SHIFT   (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_READY_SKEW_CAL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_READY_SKEW_CAL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HAFCYC_OVERRIDE_MASK (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HAFCYC_OVERRIDE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HAFCYC_OVERRIDE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HAFCYC_OVERRIDE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HSFCYC_MASK    (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HSFCYC_SHIFT   (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HSFCYC_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_TM_HS_PREP_HSFCYC_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TRAIL_OFFSET_MASK      (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TRAIL_OFFSET_SHIFT     (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TRAIL_OFFSET_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TRAIL_OFFSET_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_ZERO_OFFSET_MASK       (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_ZERO_OFFSET_SHIFT      (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_ZERO_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_ZERO_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_PREP_OFFSET_MASK       (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_PREP_OFFSET_SHIFT      (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_PREP_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_PREP_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TLPX_OFFSET_MASK       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TLPX_OFFSET_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TLPX_OFFSET_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_DL3_HS_TLPX_OFFSET_MAX        (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT1_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_MASK      (0x07F80000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_SHIFT     (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_SEL_MASK  (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_SEL_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SEQ_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_MASK (0x0003FC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_MAX  (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_SEL_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_SEL_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_SKEW_CAL_SYNC_PKT_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_MASK       (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_SEL_MASK   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_SEL_SHIFT  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_DL3_TM_HS_SYNC_PKT_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT2_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_SERSYNTH_LOOPBACK_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_SERSYNTH_LOOPBACK_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_SERSYNTH_LOOPBACK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_SERSYNTH_LOOPBACK_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_STATE_MASK      (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_STATE_SHIFT     (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_STATE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_STATE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_EN_MASK         (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_EN_SHIFT        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_EN_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_DL3_BAL_FORCE_EN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT3_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_CONTENTION_EN_MASK        (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_CONTENTION_EN_SHIFT       (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_CONTENTION_EN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_CONTENTION_EN_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_UNUSED_14_13_MASK         (0x00006000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_UNUSED_14_13_SHIFT        (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_UNUSED_14_13_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_UNUSED_14_13_MAX          (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_FORCE_RX_MODE_MASK        (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_FORCE_RX_MODE_SHIFT       (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_FORCE_RX_MODE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_FORCE_RX_MODE_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DP_SEL_MASK (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DP_SEL_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DP_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DP_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DN_SEL_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_DN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_MASK       (0x000003FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_RSTN_MASK  (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_RSTN_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_RSTN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_RSTN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_EN_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_EN_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_DL3_TEST_DATA_LPTX_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT4_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5_DL3_DIG_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5_DL3_DIG_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5_DL3_DIG_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5_DL3_DIG_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT5_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6_DL3_DIG_TBIT6_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6_DL3_DIG_TBIT6_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6_DL3_DIG_TBIT6_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6_DL3_DIG_TBIT6_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT6_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7_DL3_DIG_TBIT7_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7_DL3_DIG_TBIT7_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7_DL3_DIG_TBIT7_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7_DL3_DIG_TBIT7_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT7_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8_DL3_DIG_TBIT8_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8_DL3_DIG_TBIT8_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8_DL3_DIG_TBIT8_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8_DL3_DIG_TBIT8_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT8_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9_DL3_DIG_TBIT9_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9_DL3_DIG_TBIT9_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9_DL3_DIG_TBIT9_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9_DL3_DIG_TBIT9_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT9_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_WAIT_TIME_MASK      (0x01E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_WAIT_TIME_SHIFT     (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_WAIT_TIME_RESETVAL  (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_WAIT_TIME_MAX       (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_ULPTX_TEST_TIME_MASK (0x001FE000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_ULPTX_TEST_TIME_SHIFT (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_ULPTX_TEST_TIME_RESETVAL (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_ULPTX_TEST_TIME_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_SEND_CONFIG_MASK    (0x00001800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_SEND_CONFIG_SHIFT   (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_SEND_CONFIG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_SEND_CONFIG_MAX     (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_DIG_TO_DIG_LOOPBK_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_DIG_TO_DIG_LOOPBK_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_DIG_TO_DIG_LOOPBK_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_DIG_TO_DIG_LOOPBK_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_RUN_NEGEDGE_FIRST_MASK (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_RUN_NEGEDGE_FIRST_SHIFT (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_RUN_NEGEDGE_FIRST_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_RUN_NEGEDGE_FIRST_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LENGTH_OF_DESKEW_MASK (0x000001FCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LENGTH_OF_DESKEW_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LENGTH_OF_DESKEW_RESETVAL (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LENGTH_OF_DESKEW_MAX (0x0000007FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LOOPBK_MODE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LOOPBK_MODE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LOOPBK_MODE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_LOOPBK_MODE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_EN_MASK             (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_EN_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_EN_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_DL3_BIST_EN_MAX              (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT10_RESETVAL                     (0x0088002CU)

/* DL3_TX_DIG_TBIT11 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_IDLE_TIME_MASK  (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_IDLE_TIME_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_IDLE_TIME_RESETVAL (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_IDLE_TIME_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PKT_NUM_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PKT_NUM_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PKT_NUM_RESETVAL    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PKT_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_INF_MODE_MASK       (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_INF_MODE_SHIFT      (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_INF_MODE_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_INF_MODE_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_NUM_MASK        (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_NUM_SHIFT       (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_NUM_RESETVAL    (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_FRM_NUM_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_CLEAR_MASK          (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_CLEAR_SHIFT         (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_CLEAR_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_CLEAR_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PRBS_MASK           (0x00000030U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PRBS_SHIFT          (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PRBS_RESETVAL       (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_PRBS_MAX            (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_TEST_MODE_MASK      (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_TEST_MODE_SHIFT     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_TEST_MODE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_BIST_TEST_MODE_MAX       (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_UNUSED_0_MASK            (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_UNUSED_0_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_UNUSED_0_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_DL3_UNUSED_0_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT11_RESETVAL                     (0x0F0501B0U)

/* DL3_TX_DIG_TBIT12 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12_DL3_BIST_RUN_LENGTH_MASK     (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12_DL3_BIST_RUN_LENGTH_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12_DL3_BIST_RUN_LENGTH_RESETVAL (0x00000028U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12_DL3_BIST_RUN_LENGTH_MAX      (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT12_RESETVAL                     (0x00000028U)

/* DL3_TX_DIG_TBIT13 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_UNUSED_31_8_MASK         (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_UNUSED_31_8_SHIFT        (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_UNUSED_31_8_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_UNUSED_31_8_MAX          (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_BIST_IDLE_TIME_MASK      (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_BIST_IDLE_TIME_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_BIST_IDLE_TIME_RESETVAL  (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_DL3_BIST_IDLE_TIME_MAX       (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT13_RESETVAL                     (0x0000000AU)

/* DL3_TX_DIG_TBIT14 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT4_MASK           (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT4_SHIFT          (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT4_RESETVAL       (0x000000DEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT4_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT3_MASK           (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT3_SHIFT          (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT3_RESETVAL       (0x000000CDU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT3_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT2_MASK           (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT2_SHIFT          (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT2_RESETVAL       (0x000000BCU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT2_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT1_MASK           (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT1_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT1_RESETVAL       (0x000000ABU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_DL3_BIST_PKT1_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT14_RESETVAL                     (0xDECDBCABU)

/* DL3_TX_DIG_TBIT15 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_LFSR_FREEZE_MASK    (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_LFSR_FREEZE_SHIFT   (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_LFSR_FREEZE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_LFSR_FREEZE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_POINT_MASK  (0x00001FFEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_POINT_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_POINT_RESETVAL (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_POINT_MAX   (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_EN_MASK     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_EN_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_DL3_BIST_ERR_INJ_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT15_RESETVAL                     (0x00000028U)

/* DL3_TX_DIG_TBIT16 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16_DL3_DIG_TBIT16_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16_DL3_DIG_TBIT16_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16_DL3_DIG_TBIT16_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16_DL3_DIG_TBIT16_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT16_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT17 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17_DL3_DIG_TBIT17_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17_DL3_DIG_TBIT17_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17_DL3_DIG_TBIT17_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17_DL3_DIG_TBIT17_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT17_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT18 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18_DL3_DIG_TBIT18_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18_DL3_DIG_TBIT18_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18_DL3_DIG_TBIT18_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18_DL3_DIG_TBIT18_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT18_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT19 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19_DL3_DIG_TBIT19_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19_DL3_DIG_TBIT19_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19_DL3_DIG_TBIT19_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19_DL3_DIG_TBIT19_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT19_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT20 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ISO_EN_MASK           (0x80000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ISO_EN_SHIFT          (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ISO_EN_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ISO_EN_MAX            (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_SEL_MASK    (0x40000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_SEL_SHIFT   (0x0000001EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_MASK        (0x38000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_SHIFT       (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LOAD_DPDN_MAX         (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATA_RATE_SEL_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATA_RATE_SEL_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATA_RATE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATA_RATE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATE_RATE_MASK   (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATE_RATE_SHIFT  (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATE_RATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_DATE_RATE_MAX    (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_SEL_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_SEL_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_MASK  (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_ULP_RCV_EN_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_SEL_MASK   (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_SEL_SHIFT  (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_MASK       (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_SHIFT      (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_ULPS_PULDN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_SEL_MASK (0x00080000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_SEL_SHIFT (0x00000013U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_MASK (0x00040000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_SMPLR_CLK_EDGE_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_SEL_MASK      (0x00020000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_SEL_SHIFT     (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_MASK          (0x00010000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_SHIFT         (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_BIST_EN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_SEL_MASK    (0x00008000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_SEL_SHIFT   (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_MASK        (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_SHIFT       (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_SEL_MASK     (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_SEL_SHIFT    (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_SEL_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_MASK         (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_SHIFT        (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_RST_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_SEL_MASK      (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_SEL_SHIFT     (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_MASK          (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_SHIFT         (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DP_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_SEL_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_SEL_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_SEL_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_SEL_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_MASK          (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LPTX_DN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_SEL_MASK   (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_SEL_SHIFT  (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_MASK       (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_SHIFT      (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_LDO_REF_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_SEL_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_SEL_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_MASK        (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_TRST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_SEL_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_SEL_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_MASK        (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_SHIFT       (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_HSTX_RQST_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_SEL_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_SEL_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_MASK        (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_DL3_TM_GLOBAL_PD_MAX         (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT20_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT21 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_SEL_MASK (0x00004000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_SEL_SHIFT (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_SEL_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_MASK   (0x00002000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_SHIFT  (0x0000000DU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_RST_N_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_SEL_MASK    (0x00001000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_SEL_SHIFT   (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_SEL_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_EN_MASK     (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_EN_SHIFT    (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SWAP_DPDN_EN_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_SEL_MASK  (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_SEL_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_SEL_MAX   (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_SERSYNTH_EN_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_SEL_MASK   (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_SEL_SHIFT  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_SEL_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_SEL_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_MASK       (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_DL3_TM_TX_DATA_HS_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT21_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT22 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22_DL3_DIG_TBIT22_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22_DL3_DIG_TBIT22_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22_DL3_DIG_TBIT22_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22_DL3_DIG_TBIT22_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT22_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT23 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23_DL3_DIG_TBIT23_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23_DL3_DIG_TBIT23_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23_DL3_DIG_TBIT23_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23_DL3_DIG_TBIT23_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT23_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT24 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24_DL3_DIG_TBIT24_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24_DL3_DIG_TBIT24_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24_DL3_DIG_TBIT24_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24_DL3_DIG_TBIT24_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT24_RESETVAL                     (0x00000000U)

/* DL3_TX_ANA_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5_DL3_ANA_TBIT5_MASK            (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5_DL3_ANA_TBIT5_SHIFT           (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5_DL3_ANA_TBIT5_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5_DL3_ANA_TBIT5_MAX             (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT5_RESETVAL                      (0x00000000U)

/* DL3_TX_DIG_TBIT25 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_ANA_CTRL_FSM_STATE_MASK  (0x001F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_ANA_CTRL_FSM_STATE_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_ANA_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_ANA_CTRL_FSM_STATE_MAX   (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_BIST_BAL_STATUS_MASK     (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_BIST_BAL_STATUS_SHIFT    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_BIST_BAL_STATUS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_DL3_BIST_BAL_STATUS_MAX      (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT25_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT26 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESC_RX_FSM_STATE_MASK (0xF8000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESC_RX_FSM_STATE_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESC_RX_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESC_RX_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_CTRL_FSM_STATE_MASK (0x07FE0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_CTRL_FSM_STATE_SHIFT (0x00000011U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_CTRL_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_CTRL_FSM_STATE_MAX (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_DATA_FSM_STATE_MASK (0x0001F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_DATA_FSM_STATE_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_DATA_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_DATA_ESCTX_DATA_FSM_STATE_MAX (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_HS_PATH_FSM_STATE_MASK (0x00000FFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_HS_PATH_FSM_STATE_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_HS_PATH_FSM_STATE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_DL3_TM_HS_PATH_FSM_STATE_MAX (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT26_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT28 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_TM_ANA_COMP_OUTS_MASK    (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_TM_ANA_COMP_OUTS_SHIFT   (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_TM_ANA_COMP_OUTS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_TM_ANA_COMP_OUTS_MAX     (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_UNUSED_7_0_MASK          (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_UNUSED_7_0_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_UNUSED_7_0_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_DL3_UNUSED_7_0_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT28_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT29 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPTX_CHE_MASK (0x03000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPTX_CHE_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPTX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPTX_CHE_MAX (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPRX_CHE_MASK (0x00E00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPRX_CHE_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_ULPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPCD_CHE_MASK (0x001C0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPCD_CHE_SHIFT (0x00000012U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPCD_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPCD_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPRX_CHE_MASK (0x00038000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPRX_CHE_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPRX_CHE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_LPRX_CHE_MAX (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_CTRLR_MASK  (0x00007800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_CTRLR_SHIFT (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_CTRLR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_TM_CUR_STATE_CTRLR_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_DATA_LANE_PASS_MASK (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_DATA_LANE_PASS_SHIFT (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_DATA_LANE_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_DATA_LANE_PASS_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPRX_PASS_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPRX_PASS_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPRX_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPRX_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPCD_PASS_MASK      (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPCD_PASS_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPCD_PASS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_LPCD_PASS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPRX_PASS_MASK     (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPRX_PASS_SHIFT    (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPRX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPRX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPTX_PASS_MASK     (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPTX_PASS_SHIFT    (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPTX_PASS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_ULPTX_PASS_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_NEG_ERR_MASK     (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_NEG_ERR_SHIFT    (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_NEG_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_NEG_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_POS_ERR_MASK     (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_POS_ERR_SHIFT    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_POS_ERR_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_HS_POS_ERR_MAX      (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_POS_SYNC_MASK       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_POS_SYNC_SHIFT      (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_POS_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_POS_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_NEG_SYNC_MASK       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_NEG_SYNC_SHIFT      (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_NEG_SYNC_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_NEG_SYNC_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_CMPLT_MASK          (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_CMPLT_SHIFT         (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_CMPLT_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_CMPLT_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_EN_STATUS_MASK      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_EN_STATUS_SHIFT     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_EN_STATUS_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_DL3_BIST_EN_STATUS_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT29_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT30 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_DL3_BIST_PAT_CHE_PKT_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT30_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT31 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_NEG_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_NEG_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_NEG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_NEG_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_POS_MASK (0x0000FFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_POS_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_POS_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_DL3_BIST_PAT_CHE_ERR_CNT_POS_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT31_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT32 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32_DL3_DIG_TBIT32_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32_DL3_DIG_TBIT32_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32_DL3_DIG_TBIT32_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32_DL3_DIG_TBIT32_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT32_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT33 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33_DL3_DIG_TBIT33_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33_DL3_DIG_TBIT33_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33_DL3_DIG_TBIT33_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33_DL3_DIG_TBIT33_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT33_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT34 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34_DL3_DIG_TBIT34_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34_DL3_DIG_TBIT34_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34_DL3_DIG_TBIT34_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34_DL3_DIG_TBIT34_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT34_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT35 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35_DL3_DIG_TBIT35_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35_DL3_DIG_TBIT35_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35_DL3_DIG_TBIT35_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35_DL3_DIG_TBIT35_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT35_RESETVAL                     (0x00000000U)

/* DL3_TX_DIG_TBIT36 */

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36_DL3_DIG_TBIT36_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36_DL3_DIG_TBIT36_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36_DL3_DIG_TBIT36_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36_DL3_DIG_TBIT36_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_DIG_TBIT36_RESETVAL                     (0x00000000U)

/* PCS_TX_DIG_TBIT0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_R_MASK       (0x000003E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_R_SHIFT      (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_R_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_R_MAX        (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_L_MASK       (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_L_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_L_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_L_MAX        (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_MASK       (0x000001FEU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_SHIFT      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_MAX        (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_EN_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_EN_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_EN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_PCS_PSM_CLOCK_FREQ_EN_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT1_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_3_MASK (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_3_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_3_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_2_MASK (0x0F000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_2_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_2_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_1_MASK (0x00F00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_1_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_1_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_0_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_0_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_0_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_R_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_3_MASK (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_3_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_3_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_2_MASK (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_2_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_2_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_1_MASK (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_1_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_1_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_0_MASK (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_0_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_PCS_POWER_SW_2_TIME_DL_L_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT2_RESETVAL                      (0x22222222U)

/* PCS_TX_DIG_TBIT3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CMN_MASK  (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CMN_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CMN_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CMN_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_R_MASK (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_R_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_R_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_R_MAX  (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_L_MASK (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_L_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_L_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_PCS_POWER_SW_2_TIME_CL_L_MAX  (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT3_RESETVAL                      (0x00000222U)

/* PCS_TX_DIG_TBIT4 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_3_MASK (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_3_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_3_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_2_MASK (0x0F000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_2_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_2_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_1_MASK (0x00F00000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_1_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_1_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_0_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_0_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_0_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_R_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_3_MASK (0x0000F000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_3_SHIFT (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_3_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_2_MASK (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_2_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_2_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_1_MASK (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_1_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_1_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_0_MASK (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_0_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_PCS_POWER_SW_1_TIME_DL_L_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT4_RESETVAL                      (0x22222222U)

/* PCS_TX_DIG_TBIT5 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CMN_MASK  (0x00000F00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CMN_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CMN_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CMN_MAX   (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_R_MASK (0x000000F0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_R_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_R_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_R_MAX  (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_L_MASK (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_L_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_L_RESETVAL (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_PCS_POWER_SW_1_TIME_CL_L_MAX  (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT5_RESETVAL                      (0x00000222U)

/* PCS_TX_DIG_TBIT6 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_3_SPARE_MASK        (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_3_SPARE_SHIFT       (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_3_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_3_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_2_SPARE_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_2_SPARE_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_2_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_2_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_1_SPARE_MASK        (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_1_SPARE_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_1_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_1_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_0_SPARE_MASK        (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_0_SPARE_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_0_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_PCS_DTX_L_0_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT6_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT7 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_3_SPARE_MASK        (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_3_SPARE_SHIFT       (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_3_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_3_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_2_SPARE_MASK        (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_2_SPARE_SHIFT       (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_2_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_2_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_1_SPARE_MASK        (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_1_SPARE_SHIFT       (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_1_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_1_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_0_SPARE_MASK        (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_0_SPARE_SHIFT       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_0_SPARE_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_PCS_DTX_R_0_SPARE_MAX         (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT7_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT8 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CMN_SPARE_MASK            (0x00FF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CMN_SPARE_SHIFT           (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CMN_SPARE_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CMN_SPARE_MAX             (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_R_SPARE_MASK           (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_R_SPARE_SHIFT          (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_R_SPARE_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_R_SPARE_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_L_SPARE_MASK           (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_L_SPARE_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_L_SPARE_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_PCS_CL_L_SPARE_MAX            (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT8_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT9 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_VALUE_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_VALUE_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_VALUE_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_VALUE_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_EN_MASK       (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_EN_SHIFT      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_EN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_PCS_PSO_DISABLE_EN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT9_RESETVAL                      (0x00000000U)

/* PCS_TX_DIG_TBIT10 */

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10_PCS_DIG_TBIT10_MASK          (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10_PCS_DIG_TBIT10_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10_PCS_DIG_TBIT10_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10_PCS_DIG_TBIT10_MAX           (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT10_RESETVAL                     (0x00000000U)

/* ISO_PHY_ISO_CNTRL */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_BF_31_12_MASK            (0xFFFFF000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_BF_31_12_SHIFT           (0x0000000CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_BF_31_12_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_BF_31_12_MAX             (0x000FFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISOLATION_MASK       (0x00000800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISOLATION_SHIFT      (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISOLATION_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISOLATION_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CMN_MASK         (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CMN_SHIFT        (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CMN_RESETVAL     (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CMN_MAX          (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CL_MASK          (0x00000300U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CL_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CL_RESETVAL      (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_CL_MAX           (0x00000003U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_DL_MASK          (0x000000FFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_DL_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_DL_RESETVAL      (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_ISO_PHY_ISO_DL_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CNTRL_RESETVAL                     (0x0000050FU)

/* ISO_PHY_ISO_RESET */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_BF_31_11_MASK            (0xFFFFF800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_BF_31_11_SHIFT           (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_BF_31_11_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_BF_31_11_MAX             (0x001FFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CMN_MASK       (0x00000400U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CMN_SHIFT      (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CMN_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CMN_MAX        (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_R_MASK      (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_R_SHIFT     (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_R_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_R_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_L_MASK      (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_L_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_L_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_CL_L_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_3_MASK    (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_3_SHIFT   (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_3_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_2_MASK    (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_2_SHIFT   (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_2_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_1_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_1_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_1_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_0_MASK    (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_0_SHIFT   (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_R_0_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_3_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_3_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_3_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_2_MASK    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_2_SHIFT   (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_2_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_1_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_1_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_1_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_0_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_0_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_ISO_LANE_RSTB_DL_L_0_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_RESET_RESETVAL                     (0x00000000U)

/* ISO_PHY_ISO_ENABLE */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_BF_31_10_MASK           (0xFFFFFC00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_BF_31_10_SHIFT          (0x0000000AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_BF_31_10_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_BF_31_10_MAX            (0x003FFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_R_MASK   (0x00000200U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_R_SHIFT  (0x00000009U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_R_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_R_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_L_MASK   (0x00000100U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_L_SHIFT  (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_L_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_TXENABLECLK_CL_L_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_3_MASK    (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_3_SHIFT   (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_3_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_2_MASK    (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_2_SHIFT   (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_2_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_1_MASK    (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_1_SHIFT   (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_1_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_0_MASK    (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_0_SHIFT   (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_R_0_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_3_MASK    (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_3_SHIFT   (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_3_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_3_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_2_MASK    (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_2_SHIFT   (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_2_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_2_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_1_MASK    (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_1_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_1_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_1_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_0_MASK    (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_0_SHIFT   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_0_RESETVAL (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_ISO_M_ENABLE_DL_L_0_MAX     (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_ENABLE_RESETVAL                    (0x0000010FU)

/* ISO_PHY_ISO_CMN_CTRL */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_BF_31_8_MASK          (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_BF_31_8_SHIFT         (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_BF_31_8_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_BF_31_8_MAX           (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_DISABLE_MASK      (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_DISABLE_SHIFT     (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_DISABLE_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_DISABLE_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_IO_PG_MASK   (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_IO_PG_SHIFT  (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_IO_PG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_IO_PG_MAX    (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_CORE_PG_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_CORE_PG_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_CORE_PG_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_SUPPLY_CORE_PG_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_CMN_READY_MASK      (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_CMN_READY_SHIFT     (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_CMN_READY_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_O_CMN_READY_MAX       (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_IP_CONFIG_CMN_MASK    (0x0000000EU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_IP_CONFIG_CMN_SHIFT   (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_IP_CONFIG_CMN_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_IP_CONFIG_CMN_MAX     (0x00000007U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_CMN_MASK          (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_CMN_SHIFT         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_CMN_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_ISO_PSO_CMN_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_CTRL_RESETVAL                  (0x00000000U)

/* ISO_PHY_ISO_CMN_PLL */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_BF_31_24_MASK          (0xFF000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_BF_31_24_SHIFT         (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_BF_31_24_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_BF_31_24_MAX           (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_LOCK_MASK          (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_LOCK_SHIFT         (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_LOCK_RESETVAL      (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_LOCK_MAX           (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PSO_MASK           (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PSO_SHIFT          (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PSO_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PSO_MAX            (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PD_MASK            (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PD_SHIFT           (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PD_RESETVAL        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_PD_MAX             (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_FBDIV_MASK         (0x001FF800U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_FBDIV_SHIFT        (0x0000000BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_FBDIV_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_FBDIV_MAX          (0x000003FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_OPDIV_MASK         (0x000007E0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_OPDIV_SHIFT        (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_OPDIV_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_OPDIV_MAX          (0x0000003FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_IPDIV_MASK         (0x0000001FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_IPDIV_SHIFT        (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_IPDIV_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_ISO_PLL_IPDIV_MAX          (0x0000001FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CMN_PLL_RESETVAL                   (0x00000000U)

/* ISO_PHY_ISO_CL_CNTRL_L */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_BF_31_8_X_MASK      (0xFFFFFF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_BF_31_8_X_SHIFT     (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_BF_31_8_X_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_BF_31_8_X_MAX       (0x00FFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L_MASK (0x00000080U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXSTOPSTATECLK_CL_L_MASK (0x00000040U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXSTOPSTATECLK_CL_L_SHIFT (0x00000006U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXSTOPSTATECLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXSTOPSTATECLK_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSACTIVENOTCLK_CL_L_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSACTIVENOTCLK_CL_L_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSACTIVENOTCLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSACTIVENOTCLK_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREADYHSCLK_CL_L_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREADYHSCLK_CL_L_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREADYHSCLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREADYHSCLK_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_M_CLK_SWAPDPDN_CL_L_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_M_CLK_SWAPDPDN_CL_L_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_M_CLK_SWAPDPDN_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_M_CLK_SWAPDPDN_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSEXITCLK_CL_L_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSEXITCLK_CL_L_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSEXITCLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSEXITCLK_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSCLK_CL_L_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSCLK_CL_L_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSCLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXULPSCLK_CL_L_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREQUESTHSCLK_CL_L_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREQUESTHSCLK_CL_L_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREQUESTHSCLK_CL_L_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_TXREQUESTHSCLK_CL_L_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_RESETVAL                (0x00000000U)

/* ISO_PHY_ISO_DL_CTRL_L0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_BF_31_4_MASK        (0xFFFFFFF0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_BF_31_4_SHIFT       (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_BF_31_4_RESETVAL    (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_BF_31_4_MAX         (0x0FFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_DATA_SWAPDPDN_DL_L_0_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_DATA_SWAPDPDN_DL_L_0_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_DATA_SWAPDPDN_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_DATA_SWAPDPDN_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_FORCETXSTOPMODE_DL_L_0_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_FORCETXSTOPMODE_DL_L_0_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_FORCETXSTOPMODE_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_FORCETXSTOPMODE_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_TURNREQUEST_DL_L_0_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_TURNREQUEST_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_TURNREQUEST_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_M_TURNREQUEST_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_RESETVAL                (0x00000000U)

/* ISO_PHY_ISO_DL_HS_L0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_BF_31_16_MASK         (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_BF_31_16_SHIFT        (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_BF_31_16_RESETVAL     (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_BF_31_16_MAX          (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXDATAHS_DL_L_0_MASK  (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXDATAHS_DL_L_0_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXDATAHS_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXDATAHS_DL_L_0_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREADYHS_DL_L_0_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREADYHS_DL_L_0_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREADYHS_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREADYHS_DL_L_0_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHS_DL_L_0_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHS_DL_L_0_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHS_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHS_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHSINIT_DL_L_0_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHSINIT_DL_L_0_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHSINIT_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXSKEWCALHSINIT_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREQUESTHS_DL_L_0_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREQUESTHS_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREQUESTHS_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_ISO_TXREQUESTHS_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L0_RESETVAL                  (0x00000000U)

/* ISO_PHY_ISO_DL_TX_ESC_L0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_BF_31_28_MASK     (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_BF_31_28_SHIFT    (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_BF_31_28_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_BF_31_28_MAX      (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ULPSACTIVENOT_DL_L_0_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ULPSACTIVENOT_DL_L_0_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ULPSACTIVENOT_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ULPSACTIVENOT_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_DIRECTION_DL_L_0_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_DIRECTION_DL_L_0_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_DIRECTION_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_DIRECTION_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_STOPSTATE_DL_L_0_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_STOPSTATE_DL_L_0_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_STOPSTATE_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_STOPSTATE_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP1_DL_L_0_MASK (0x01000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP1_DL_L_0_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP1_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP1_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP0_DL_L_0_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP0_DL_L_0_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP0_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTENTIONLP0_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRSYNCESC_DL_L_0_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRSYNCESC_DL_L_0_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRSYNCESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRSYNCESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTROL_DL_L_0_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTROL_DL_L_0_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTROL_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRCONTROL_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRESC_DL_L_0_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRESC_DL_L_0_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_ERRESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXTRIGGERESC_DL_L_0_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXTRIGGERESC_DL_L_0_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXTRIGGERESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXTRIGGERESC_DL_L_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXDATAESC_DL_L_0_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXDATAESC_DL_L_0_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXDATAESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXDATAESC_DL_L_0_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREADYESC_DL_L_0_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREADYESC_DL_L_0_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREADYESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREADYESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSEXITESC_DL_L_0_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSEXITESC_DL_L_0_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSEXITESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSEXITESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSESC_DL_L_0_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSESC_DL_L_0_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXULPSESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXVALIDESC_DL_L_0_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXVALIDESC_DL_L_0_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXVALIDESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXVALIDESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXLPDTESC_DL_L_0_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXLPDTESC_DL_L_0_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXLPDTESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXLPDTESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREQUESTESC_DL_L_0_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREQUESTESC_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREQUESTESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_ISO_M_TXREQUESTESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L0_RESETVAL              (0x00000000U)

/* ISO_PHY_ISO_DL_RX_ESC_L0 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_BF_31_15_MASK     (0xFFFF8000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_BF_31_15_SHIFT    (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_BF_31_15_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_BF_31_15_MAX      (0x0001FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXDATAESC_DL_L_0_MASK (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXDATAESC_DL_L_0_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXDATAESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXDATAESC_DL_L_0_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXTRIGGERESC_DL_L_0_MASK (0x00000078U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXTRIGGERESC_DL_L_0_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXTRIGGERESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXTRIGGERESC_DL_L_0_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXULPSESC_DL_L_0_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXULPSESC_DL_L_0_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXULPSESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXULPSESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXVALIDESC_DL_L_0_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXVALIDESC_DL_L_0_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXVALIDESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXVALIDESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXLPDTESC_DL_L_0_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXLPDTESC_DL_L_0_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXLPDTESC_DL_L_0_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_ISO_M_RXLPDTESC_DL_L_0_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L0_RESETVAL              (0x00000000U)

/* ISO_PHY_ISO_DL_CTRL_L1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_BF_31_4_X_MASK      (0xFFFFFFF0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_BF_31_4_X_SHIFT     (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_BF_31_4_X_RESETVAL  (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_BF_31_4_X_MAX       (0x0FFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_DATA_SWAPDPDN_DL_L_1_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_DATA_SWAPDPDN_DL_L_1_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_DATA_SWAPDPDN_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_DATA_SWAPDPDN_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_FORCETXSTOPMODE_DL_L_1_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_FORCETXSTOPMODE_DL_L_1_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_FORCETXSTOPMODE_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_FORCETXSTOPMODE_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_TURNREQUEST_DL_L_1_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_TURNREQUEST_DL_L_1_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_TURNREQUEST_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_M_TURNREQUEST_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_RESETVAL                (0x00000000U)

/* ISO_PHY_ISO_DL_HS_L1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_BF_31_16_X_MASK       (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_BF_31_16_X_SHIFT      (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_BF_31_16_X_RESETVAL   (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_BF_31_16_X_MAX        (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXDATAHS_DL_L_1_MASK  (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXDATAHS_DL_L_1_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXDATAHS_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXDATAHS_DL_L_1_MAX   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREADYHS_DL_L_1_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREADYHS_DL_L_1_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREADYHS_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREADYHS_DL_L_1_MAX  (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHS_DL_L_1_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHS_DL_L_1_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHS_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHS_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHSINIT_DL_L_1_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHSINIT_DL_L_1_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHSINIT_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXSKEWCALHSINIT_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREQUESTHS_DL_L_1_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREQUESTHS_DL_L_1_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREQUESTHS_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_ISO_TXREQUESTHS_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_HS_L1_RESETVAL                  (0x00000000U)

/* ISO_PHY_ISO_DL_TX_ESC_L1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_BF_31_28_X_MASK   (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_BF_31_28_X_SHIFT  (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_BF_31_28_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_BF_31_28_X_MAX    (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ULPSACTIVENOT_DL_L_1_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ULPSACTIVENOT_DL_L_1_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ULPSACTIVENOT_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ULPSACTIVENOT_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_DIRECTION_DL_L_1_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_DIRECTION_DL_L_1_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_DIRECTION_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_DIRECTION_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_STOPSTATE_DL_L_1_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_STOPSTATE_DL_L_1_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_STOPSTATE_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_STOPSTATE_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP1_DL_L_1_MASK (0x01000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP1_DL_L_1_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP1_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP1_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP0_DL_L_1_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP0_DL_L_1_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP0_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTENTIONLP0_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRSYNCESC_DL_L_1_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRSYNCESC_DL_L_1_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRSYNCESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRSYNCESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTROL_DL_L_1_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTROL_DL_L_1_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTROL_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRCONTROL_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRESC_DL_L_1_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRESC_DL_L_1_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_ERRESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXTRIGGERESC_DL_L_1_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXTRIGGERESC_DL_L_1_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXTRIGGERESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXTRIGGERESC_DL_L_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXDATAESC_DL_L_1_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXDATAESC_DL_L_1_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXDATAESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXDATAESC_DL_L_1_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREADYESC_DL_L_1_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREADYESC_DL_L_1_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREADYESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREADYESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSEXITESC_DL_L_1_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSEXITESC_DL_L_1_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSEXITESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSEXITESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSESC_DL_L_1_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSESC_DL_L_1_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXULPSESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXVALIDESC_DL_L_1_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXVALIDESC_DL_L_1_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXVALIDESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXVALIDESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXLPDTESC_DL_L_1_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXLPDTESC_DL_L_1_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXLPDTESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXLPDTESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREQUESTESC_DL_L_1_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREQUESTESC_DL_L_1_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREQUESTESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_ISO_M_TXREQUESTESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_TX_ESC_L1_RESETVAL              (0x00000000U)

/* ISO_PHY_ISO_DL_RX_ESC_L1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_BF_31_15_X_MASK   (0xFFFF8000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_BF_31_15_X_SHIFT  (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_BF_31_15_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_BF_31_15_X_MAX    (0x0001FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXDATAESC_DL_L_1_MASK (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXDATAESC_DL_L_1_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXDATAESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXDATAESC_DL_L_1_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXTRIGGERESC_DL_L_1_MASK (0x00000078U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXTRIGGERESC_DL_L_1_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXTRIGGERESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXTRIGGERESC_DL_L_1_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXULPSESC_DL_L_1_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXULPSESC_DL_L_1_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXULPSESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXULPSESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXVALIDESC_DL_L_1_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXVALIDESC_DL_L_1_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXVALIDESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXVALIDESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXLPDTESC_DL_L_1_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXLPDTESC_DL_L_1_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXLPDTESC_DL_L_1_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_ISO_M_RXLPDTESC_DL_L_1_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_RX_ESC_L1_RESETVAL              (0x00000000U)

/* ISO_PHY_ISO_SPARE_1 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1_ISO_SPARE_MASK             (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1_ISO_SPARE_SHIFT            (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1_ISO_SPARE_RESETVAL         (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1_ISO_SPARE_MAX              (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_1_RESETVAL                   (0x00000000U)

/* ISO_PHY_ISO_SPARE_2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2_ISO_SPARE_X_MASK           (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2_ISO_SPARE_X_SHIFT          (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2_ISO_SPARE_X_RESETVAL       (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2_ISO_SPARE_X_MAX            (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_SPARE_2_RESETVAL                   (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_CTRL_L2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_BF_31_4_X_X_MASK (0xFFFFFFF0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_BF_31_4_X_X_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_BF_31_4_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_BF_31_4_X_X_MAX (0x0FFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_DATA_SWAPDPDN_DL_L_2_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_DATA_SWAPDPDN_DL_L_2_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_DATA_SWAPDPDN_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_DATA_SWAPDPDN_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_FORCETXSTOPMODE_DL_L_2_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_FORCETXSTOPMODE_DL_L_2_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_FORCETXSTOPMODE_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_FORCETXSTOPMODE_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_TURNREQUEST_DL_L_2_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_TURNREQUEST_DL_L_2_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_TURNREQUEST_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_M_TURNREQUEST_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_RESETVAL            (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_HS_L2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_BF_31_16_X_X_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_BF_31_16_X_X_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_BF_31_16_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_BF_31_16_X_X_MAX  (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXDATAHS_DL_L_2_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXDATAHS_DL_L_2_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXDATAHS_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXDATAHS_DL_L_2_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREADYHS_DL_L_2_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREADYHS_DL_L_2_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREADYHS_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREADYHS_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHS_DL_L_2_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHS_DL_L_2_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHS_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHS_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHSINIT_DL_L_2_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHSINIT_DL_L_2_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHSINIT_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXSKEWCALHSINIT_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREQUESTHS_DL_L_2_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREQUESTHS_DL_L_2_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREQUESTHS_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_ISO_TXREQUESTHS_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L2_RESETVAL              (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_TX_ESC_L2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_BF_31_28_X_X_MASK (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_BF_31_28_X_X_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_BF_31_28_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_BF_31_28_X_X_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ULPSACTIVENOT_DL_L_2_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ULPSACTIVENOT_DL_L_2_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ULPSACTIVENOT_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ULPSACTIVENOT_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_DIRECTION_DL_L_2_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_DIRECTION_DL_L_2_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_DIRECTION_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_DIRECTION_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_STOPSTATE_DL_L_2_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_STOPSTATE_DL_L_2_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_STOPSTATE_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_STOPSTATE_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP1_DL_L_2_MASK (0x01000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP1_DL_L_2_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP1_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP1_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP0_DL_L_2_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP0_DL_L_2_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP0_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTENTIONLP0_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRSYNCESC_DL_L_2_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRSYNCESC_DL_L_2_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRSYNCESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRSYNCESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTROL_DL_L_2_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTROL_DL_L_2_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTROL_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRCONTROL_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRESC_DL_L_2_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRESC_DL_L_2_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_ERRESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXTRIGGERESC_DL_L_2_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXTRIGGERESC_DL_L_2_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXTRIGGERESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXTRIGGERESC_DL_L_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXDATAESC_DL_L_2_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXDATAESC_DL_L_2_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXDATAESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXDATAESC_DL_L_2_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREADYESC_DL_L_2_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREADYESC_DL_L_2_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREADYESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREADYESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSEXITESC_DL_L_2_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSEXITESC_DL_L_2_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSEXITESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSEXITESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSESC_DL_L_2_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSESC_DL_L_2_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXULPSESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXVALIDESC_DL_L_2_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXVALIDESC_DL_L_2_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXVALIDESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXVALIDESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXLPDTESC_DL_L_2_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXLPDTESC_DL_L_2_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXLPDTESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXLPDTESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREQUESTESC_DL_L_2_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREQUESTESC_DL_L_2_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREQUESTESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_ISO_M_TXREQUESTESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L2_RESETVAL          (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_RX_ESC_L2 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_BF_31_15_X_X_MASK (0xFFFF8000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_BF_31_15_X_X_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_BF_31_15_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_BF_31_15_X_X_MAX (0x0001FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXDATAESC_DL_L_2_MASK (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXDATAESC_DL_L_2_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXDATAESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXDATAESC_DL_L_2_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXTRIGGERESC_DL_L_2_MASK (0x00000078U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXTRIGGERESC_DL_L_2_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXTRIGGERESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXTRIGGERESC_DL_L_2_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXULPSESC_DL_L_2_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXULPSESC_DL_L_2_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXULPSESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXULPSESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXVALIDESC_DL_L_2_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXVALIDESC_DL_L_2_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXVALIDESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXVALIDESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXLPDTESC_DL_L_2_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXLPDTESC_DL_L_2_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXLPDTESC_DL_L_2_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_ISO_M_RXLPDTESC_DL_L_2_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L2_RESETVAL          (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_CTRL_L3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_BF_31_4_X_X_X_MASK (0xFFFFFFF0U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_BF_31_4_X_X_X_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_BF_31_4_X_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_BF_31_4_X_X_X_MAX (0x0FFFFFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_DATA_SWAPDPDN_DL_L_3_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_DATA_SWAPDPDN_DL_L_3_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_DATA_SWAPDPDN_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_DATA_SWAPDPDN_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_FORCETXSTOPMODE_DL_L_3_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_FORCETXSTOPMODE_DL_L_3_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_FORCETXSTOPMODE_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_FORCETXSTOPMODE_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_TURNREQUEST_DL_L_3_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_TURNREQUEST_DL_L_3_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_TURNREQUEST_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_M_TURNREQUEST_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_RESETVAL            (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_HS_L3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_BF_31_16_X_X_X_MASK (0xFFFF0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_BF_31_16_X_X_X_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_BF_31_16_X_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_BF_31_16_X_X_X_MAX (0x0000FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXDATAHS_DL_L_3_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXDATAHS_DL_L_3_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXDATAHS_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXDATAHS_DL_L_3_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREADYHS_DL_L_3_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREADYHS_DL_L_3_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREADYHS_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREADYHS_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHS_DL_L_3_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHS_DL_L_3_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHS_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHS_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHSINIT_DL_L_3_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHSINIT_DL_L_3_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHSINIT_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXSKEWCALHSINIT_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREQUESTHS_DL_L_3_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREQUESTHS_DL_L_3_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREQUESTHS_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_ISO_TXREQUESTHS_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_HS_L3_RESETVAL              (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_TX_ESC_L3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_BF_31_28_X_X_X_MASK (0xF0000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_BF_31_28_X_X_X_SHIFT (0x0000001CU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_BF_31_28_X_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_BF_31_28_X_X_X_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ULPSACTIVENOT_DL_L_3_MASK (0x08000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ULPSACTIVENOT_DL_L_3_SHIFT (0x0000001BU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ULPSACTIVENOT_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ULPSACTIVENOT_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_DIRECTION_DL_L_3_MASK (0x04000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_DIRECTION_DL_L_3_SHIFT (0x0000001AU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_DIRECTION_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_DIRECTION_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_STOPSTATE_DL_L_3_MASK (0x02000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_STOPSTATE_DL_L_3_SHIFT (0x00000019U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_STOPSTATE_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_STOPSTATE_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP1_DL_L_3_MASK (0x01000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP1_DL_L_3_SHIFT (0x00000018U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP1_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP1_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP0_DL_L_3_MASK (0x00800000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP0_DL_L_3_SHIFT (0x00000017U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP0_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTENTIONLP0_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRSYNCESC_DL_L_3_MASK (0x00400000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRSYNCESC_DL_L_3_SHIFT (0x00000016U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRSYNCESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRSYNCESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTROL_DL_L_3_MASK (0x00200000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTROL_DL_L_3_SHIFT (0x00000015U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTROL_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRCONTROL_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRESC_DL_L_3_MASK (0x00100000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRESC_DL_L_3_SHIFT (0x00000014U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_ERRESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXTRIGGERESC_DL_L_3_MASK (0x000F0000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXTRIGGERESC_DL_L_3_SHIFT (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXTRIGGERESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXTRIGGERESC_DL_L_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXDATAESC_DL_L_3_MASK (0x0000FF00U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXDATAESC_DL_L_3_SHIFT (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXDATAESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXDATAESC_DL_L_3_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREADYESC_DL_L_3_MASK (0x00000020U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREADYESC_DL_L_3_SHIFT (0x00000005U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREADYESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREADYESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSEXITESC_DL_L_3_MASK (0x00000010U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSEXITESC_DL_L_3_SHIFT (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSEXITESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSEXITESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSESC_DL_L_3_MASK (0x00000008U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSESC_DL_L_3_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXULPSESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXVALIDESC_DL_L_3_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXVALIDESC_DL_L_3_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXVALIDESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXVALIDESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXLPDTESC_DL_L_3_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXLPDTESC_DL_L_3_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXLPDTESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXLPDTESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREQUESTESC_DL_L_3_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREQUESTESC_DL_L_3_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREQUESTESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_ISO_M_TXREQUESTESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_TX_ESC_L3_RESETVAL          (0x00000000U)

/* ISO_LDD_PHY_ISO_DL_RX_ESC_L3 */

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_BF_31_15_X_X_X_MASK (0xFFFF8000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_BF_31_15_X_X_X_SHIFT (0x0000000FU)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_BF_31_15_X_X_X_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_BF_31_15_X_X_X_MAX (0x0001FFFFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXDATAESC_DL_L_3_MASK (0x00007F80U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXDATAESC_DL_L_3_SHIFT (0x00000007U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXDATAESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXDATAESC_DL_L_3_MAX (0x000000FFU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXTRIGGERESC_DL_L_3_MASK (0x00000078U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXTRIGGERESC_DL_L_3_SHIFT (0x00000003U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXTRIGGERESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXTRIGGERESC_DL_L_3_MAX (0x0000000FU)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXULPSESC_DL_L_3_MASK (0x00000004U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXULPSESC_DL_L_3_SHIFT (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXULPSESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXULPSESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXVALIDESC_DL_L_3_MASK (0x00000002U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXVALIDESC_DL_L_3_SHIFT (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXVALIDESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXVALIDESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXLPDTESC_DL_L_3_MASK (0x00000001U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXLPDTESC_DL_L_3_SHIFT (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXLPDTESC_DL_L_3_RESETVAL (0x00000000U)
#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_ISO_M_RXLPDTESC_DL_L_3_MAX (0x00000001U)

#define CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_RX_ESC_L3_RESETVAL          (0x00000000U)

/* MOD_VER */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_SCHEME_MASK                        (0xC0000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_SCHEME_SHIFT                       (0x0000001EU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_SCHEME_RESETVAL                    (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_SCHEME_MAX                         (0x00000003U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_BU_MASK                            (0x30000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_BU_SHIFT                           (0x0000001CU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_BU_RESETVAL                        (0x00000002U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_BU_MAX                             (0x00000003U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MODULE_ID_MASK                     (0x0FFF0000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MODULE_ID_SHIFT                    (0x00000010U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MODULE_ID_RESETVAL                 (0x00000992U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MODULE_ID_MAX                      (0x00000FFFU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_RTL_VERSION_MASK                   (0x0000F800U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_RTL_VERSION_SHIFT                  (0x0000000BU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_RTL_VERSION_RESETVAL               (0x00000007U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_RTL_VERSION_MAX                    (0x0000001FU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MAJOR_REVISION_MASK                (0x00000700U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MAJOR_REVISION_SHIFT               (0x00000008U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MAJOR_REVISION_RESETVAL            (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MAJOR_REVISION_MAX                 (0x00000007U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_CUSTOM_REVISION_MASK               (0x000000C0U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_CUSTOM_REVISION_SHIFT              (0x00000006U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_CUSTOM_REVISION_RESETVAL           (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_CUSTOM_REVISION_MAX                (0x00000003U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MINOR_REVISION_MASK                (0x0000003FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MINOR_REVISION_SHIFT               (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MINOR_REVISION_RESETVAL            (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_MINOR_REVISION_MAX                 (0x0000003FU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_MOD_VER_RESETVAL                           (0x69923801U)

/* PLL_CTRL */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK_MASK                     (0x80000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK_SHIFT                    (0x0000001FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK_RESETVAL                 (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK_MAX                      (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PSO_DISABLE_MASK                  (0x40000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PSO_DISABLE_SHIFT                 (0x0000001EU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PSO_DISABLE_RESETVAL              (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PSO_DISABLE_MAX                   (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PSO_MASK                      (0x20000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PSO_SHIFT                     (0x0000001DU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PSO_RESETVAL                  (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PSO_MAX                       (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PD_MASK                       (0x10000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PD_SHIFT                      (0x0000001CU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PD_RESETVAL                   (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PD_MAX                        (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV_MASK                    (0x03FF0000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV_SHIFT                   (0x00000010U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV_RESETVAL                (0x000000FFU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV_MAX                     (0x000003FFU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV_MASK                    (0x00003F00U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV_SHIFT                   (0x00000008U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV_RESETVAL                (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV_MAX                     (0x0000003FU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV_MASK                    (0x0000001FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV_SHIFT                   (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV_RESETVAL                (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV_MAX                     (0x0000001FU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_RESETVAL                          (0x10FF0101U)

/* STATUS */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY_MASK                    (0x80000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY_SHIFT                   (0x0000001FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY_RESETVAL                (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY_MAX                     (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_CORE_PG_MASK               (0x00000004U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_CORE_PG_SHIFT              (0x00000002U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_CORE_PG_RESETVAL           (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_CORE_PG_MAX                (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_IO_PG_MASK                 (0x00000002U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_IO_PG_SHIFT                (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_IO_PG_RESETVAL             (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_SUPPLY_IO_PG_MAX                  (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_RESETVAL                            (0x00000000U)

/* RST_CTRL */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_LANE_RSTB_CMN_MASK                (0x80000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_LANE_RSTB_CMN_SHIFT               (0x0000001FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_LANE_RSTB_CMN_RESETVAL            (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_LANE_RSTB_CMN_MAX                 (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_RESETVAL                          (0x00000000U)

/* PSM_FREQ */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_PSM_CLOCK_FREQ_MASK               (0x000000FFU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_PSM_CLOCK_FREQ_SHIFT              (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_PSM_CLOCK_FREQ_RESETVAL           (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_PSM_CLOCK_FREQ_MAX                (0x000000FFU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_RESETVAL                          (0x00000001U)

/* IPCONFIG */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_PSO_CMN_MASK                      (0x80000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_PSO_CMN_SHIFT                     (0x0000001FU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_PSO_CMN_RESETVAL                  (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_PSO_CMN_MAX                       (0x00000001U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_IPCONFIG_CMN_MASK                 (0x00000007U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_IPCONFIG_CMN_SHIFT                (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_IPCONFIG_CMN_RESETVAL             (0x00000001U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_IPCONFIG_CMN_MAX                  (0x00000007U)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_IPCONFIG_RESETVAL                          (0x00000001U)

/* PLLRES */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES_PLLREFSEL_CMN_MASK                  (0x000000FFU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES_PLLREFSEL_CMN_SHIFT                 (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES_PLLREFSEL_CMN_RESETVAL              (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES_PLLREFSEL_CMN_MAX                   (0x000000FFU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLLRES_RESETVAL                            (0x00000000U)

/* DIAG_TEST */

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST_DIAG_REG_MASK                    (0xFFFFFFFFU)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST_DIAG_REG_SHIFT                   (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST_DIAG_REG_RESETVAL                (0x00000000U)
#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST_DIAG_REG_MAX                     (0xFFFFFFFFU)

#define CSL_WIZ16B8M4CDT_WIZ_CONFIG_DIAG_TEST_RESETVAL                         (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
