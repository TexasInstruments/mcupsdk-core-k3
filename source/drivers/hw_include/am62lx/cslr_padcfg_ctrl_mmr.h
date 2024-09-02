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
 *  Name        : cslr_padcfg_ctrl_mmr.h
*/
#ifndef CSLR_PADCFG_CTRL_MMR_H_
#define CSLR_PADCFG_CTRL_MMR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_PADCFG_CTRL_MMR_CFG0_REGS_BASE                               (0x00000000U)


/**************************************************************************
* Hardware Region  : MMRs in region 0
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* PID register */
    volatile uint8_t  Resv_8[4];
    volatile uint32_t MMR_CFG1;                  /* Configuration register 1 */
    volatile uint8_t  Resv_4112[4100];
    volatile uint32_t INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    volatile uint32_t INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    volatile uint32_t INTR_ENABLE;               /* Interrupt Enable register */
    volatile uint32_t INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    volatile uint32_t EOI;                       /* EOI register */
    volatile uint32_t FAULT_ADDRESS;             /* Fault Address register */
    volatile uint32_t FAULT_TYPE_STATUS;         /* Fault Type Status register */
    volatile uint32_t FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    volatile uint32_t FAULT_CLEAR;               /* Fault Clear register */
    volatile uint8_t  Resv_16384[12236];
    volatile uint32_t PADCONFIG0;                /* PAD Configuration Register 0 */
    volatile uint32_t PADCONFIG1;                /* PAD Configuration Register 1 */
    volatile uint32_t PADCONFIG2;                /* PAD Configuration Register 2 */
    volatile uint32_t PADCONFIG3;                /* PAD Configuration Register 3 */
    volatile uint32_t PADCONFIG4;                /* PAD Configuration Register 4 */
    volatile uint32_t PADCONFIG5;                /* PAD Configuration Register 5 */
    volatile uint32_t PADCONFIG6;                /* PAD Configuration Register 6 */
    volatile uint32_t PADCONFIG7;                /* PAD Configuration Register 7 */
    volatile uint32_t PADCONFIG8;                /* PAD Configuration Register 8 */
    volatile uint32_t PADCONFIG9;                /* PAD Configuration Register 9 */
    volatile uint32_t PADCONFIG10;               /* PAD Configuration Register 10 */
    volatile uint32_t PADCONFIG11;               /* PAD Configuration Register 11 */
    volatile uint32_t PADCONFIG12;               /* PAD Configuration Register 12 */
    volatile uint32_t PADCONFIG13;               /* PAD Configuration Register 13 */
    volatile uint32_t PADCONFIG14;               /* PAD Configuration Register 14 */
    volatile uint32_t PADCONFIG15;               /* PAD Configuration Register 15 */
    volatile uint32_t PADCONFIG16;               /* PAD Configuration Register 16 */
    volatile uint32_t PADCONFIG17;               /* PAD Configuration Register 17 */
    volatile uint32_t PADCONFIG18;               /* PAD Configuration Register 18 */
    volatile uint32_t PADCONFIG19;               /* PAD Configuration Register 19 */
    volatile uint32_t PADCONFIG20;               /* PAD Configuration Register 20 */
    volatile uint32_t PADCONFIG21;               /* PAD Configuration Register 21 */
    volatile uint32_t PADCONFIG22;               /* PAD Configuration Register 22 */
    volatile uint32_t PADCONFIG23;               /* PAD Configuration Register 23 */
    volatile uint32_t PADCONFIG24;               /* PAD Configuration Register 24 */
    volatile uint32_t PADCONFIG25;               /* PAD Configuration Register 25 */
    volatile uint32_t PADCONFIG26;               /* PAD Configuration Register 26 */
    volatile uint32_t PADCONFIG27;               /* PAD Configuration Register 27 */
    volatile uint32_t PADCONFIG28;               /* PAD Configuration Register 28 */
    volatile uint32_t PADCONFIG29;               /* PAD Configuration Register 29 */
    volatile uint32_t PADCONFIG30;               /* PAD Configuration Register 30 */
    volatile uint32_t PADCONFIG31;               /* PAD Configuration Register 31 */
    volatile uint32_t PADCONFIG32;               /* PAD Configuration Register 32 */
    volatile uint32_t PADCONFIG33;               /* PAD Configuration Register 33 */
    volatile uint32_t PADCONFIG34;               /* PAD Configuration Register 34 */
    volatile uint32_t PADCONFIG35;               /* PAD Configuration Register 35 */
    volatile uint32_t PADCONFIG36;               /* PAD Configuration Register 36 */
    volatile uint32_t PADCONFIG37;               /* PAD Configuration Register 37 */
    volatile uint32_t PADCONFIG38;               /* PAD Configuration Register 38 */
    volatile uint32_t PADCONFIG39;               /* PAD Configuration Register 39 */
    volatile uint32_t PADCONFIG40;               /* PAD Configuration Register 40 */
    volatile uint32_t PADCONFIG41;               /* PAD Configuration Register 41 */
    volatile uint32_t PADCONFIG42;               /* PAD Configuration Register 42 */
    volatile uint32_t PADCONFIG43;               /* PAD Configuration Register 43 */
    volatile uint32_t PADCONFIG44;               /* PAD Configuration Register 44 */
    volatile uint32_t PADCONFIG45;               /* PAD Configuration Register 45 */
    volatile uint32_t PADCONFIG46;               /* PAD Configuration Register 46 */
    volatile uint32_t PADCONFIG47;               /* PAD Configuration Register 47 */
    volatile uint32_t PADCONFIG48;               /* PAD Configuration Register 48 */
    volatile uint32_t PADCONFIG49;               /* PAD Configuration Register 49 */
    volatile uint32_t PADCONFIG50;               /* PAD Configuration Register 50 */
    volatile uint32_t PADCONFIG51;               /* PAD Configuration Register 51 */
    volatile uint32_t PADCONFIG52;               /* PAD Configuration Register 52 */
    volatile uint32_t PADCONFIG53;               /* PAD Configuration Register 53 */
    volatile uint32_t PADCONFIG54;               /* PAD Configuration Register 54 */
    volatile uint32_t PADCONFIG55;               /* PAD Configuration Register 55 */
    volatile uint32_t PADCONFIG56;               /* PAD Configuration Register 56 */
    volatile uint32_t PADCONFIG57;               /* PAD Configuration Register 57 */
    volatile uint32_t PADCONFIG58;               /* PAD Configuration Register 58 */
    volatile uint32_t PADCONFIG59;               /* PAD Configuration Register 59 */
    volatile uint32_t PADCONFIG60;               /* PAD Configuration Register 60 */
    volatile uint32_t PADCONFIG61;               /* PAD Configuration Register 61 */
    volatile uint32_t PADCONFIG62;               /* PAD Configuration Register 62 */
    volatile uint32_t PADCONFIG63;               /* PAD Configuration Register 63 */
    volatile uint32_t PADCONFIG64;               /* PAD Configuration Register 64 */
    volatile uint32_t PADCONFIG65;               /* PAD Configuration Register 65 */
    volatile uint32_t PADCONFIG66;               /* PAD Configuration Register 66 */
    volatile uint32_t PADCONFIG67;               /* PAD Configuration Register 67 */
    volatile uint32_t PADCONFIG68;               /* PAD Configuration Register 68 */
    volatile uint32_t PADCONFIG69;               /* PAD Configuration Register 69 */
    volatile uint32_t PADCONFIG70;               /* PAD Configuration Register 70 */
    volatile uint32_t PADCONFIG71;               /* PAD Configuration Register 71 */
    volatile uint32_t PADCONFIG72;               /* PAD Configuration Register 72 */
    volatile uint32_t PADCONFIG73;               /* PAD Configuration Register 73 */
    volatile uint32_t PADCONFIG74;               /* PAD Configuration Register 74 */
    volatile uint32_t PADCONFIG75;               /* PAD Configuration Register 75 */
    volatile uint32_t PADCONFIG76;               /* PAD Configuration Register 76 */
    volatile uint32_t PADCONFIG77;               /* PAD Configuration Register 77 */
    volatile uint32_t PADCONFIG78;               /* PAD Configuration Register 78 */
    volatile uint32_t PADCONFIG79;               /* PAD Configuration Register 79 */
    volatile uint32_t PADCONFIG80;               /* PAD Configuration Register 80 */
    volatile uint32_t PADCONFIG81;               /* PAD Configuration Register 81 */
    volatile uint32_t PADCONFIG82;               /* PAD Configuration Register 82 */
    volatile uint32_t PADCONFIG83;               /* PAD Configuration Register 83 */
    volatile uint32_t PADCONFIG84;               /* PAD Configuration Register 84 */
    volatile uint32_t PADCONFIG85;               /* PAD Configuration Register 85 */
    volatile uint32_t PADCONFIG86;               /* PAD Configuration Register 86 */
    volatile uint32_t PADCONFIG87;               /* PAD Configuration Register 87 */
    volatile uint32_t PADCONFIG88;               /* PAD Configuration Register 88 */
    volatile uint32_t PADCONFIG89;               /* PAD Configuration Register 89 */
    volatile uint32_t PADCONFIG90;               /* PAD Configuration Register 90 */
    volatile uint32_t PADCONFIG91;               /* PAD Configuration Register 91 */
    volatile uint32_t PADCONFIG92;               /* PAD Configuration Register 92 */
    volatile uint32_t PADCONFIG93;               /* PAD Configuration Register 93 */
    volatile uint32_t PADCONFIG94;               /* PAD Configuration Register 94 */
    volatile uint32_t PADCONFIG95;               /* PAD Configuration Register 95 */
    volatile uint32_t PADCONFIG96;               /* PAD Configuration Register 96 */
    volatile uint32_t PADCONFIG97;               /* PAD Configuration Register 97 */
    volatile uint32_t PADCONFIG98;               /* PAD Configuration Register 98 */
    volatile uint32_t PADCONFIG99;               /* PAD Configuration Register 99 */
    volatile uint32_t PADCONFIG100;              /* PAD Configuration Register 100 */
    volatile uint32_t PADCONFIG101;              /* PAD Configuration Register 101 */
    volatile uint32_t PADCONFIG102;              /* PAD Configuration Register 102 */
    volatile uint32_t PADCONFIG103;              /* PAD Configuration Register 103 */
    volatile uint32_t PADCONFIG104;              /* PAD Configuration Register 104 */
    volatile uint32_t PADCONFIG105;              /* PAD Configuration Register 105 */
    volatile uint32_t PADCONFIG106;              /* PAD Configuration Register 106 */
    volatile uint32_t PADCONFIG107;              /* PAD Configuration Register 107 */
    volatile uint32_t PADCONFIG108;              /* PAD Configuration Register 108 */
    volatile uint32_t PADCONFIG109;              /* PAD Configuration Register 109 */
    volatile uint32_t PADCONFIG110;              /* PAD Configuration Register 110 */
    volatile uint32_t PADCONFIG111;              /* PAD Configuration Register 111 */
    volatile uint32_t PADCONFIG112;              /* PAD Configuration Register 112 */
    volatile uint32_t PADCONFIG113;              /* PAD Configuration Register 113 */
    volatile uint32_t PADCONFIG114;              /* PAD Configuration Register 114 */
    volatile uint32_t PADCONFIG115;              /* PAD Configuration Register 115 */
    volatile uint32_t PADCONFIG116;              /* PAD Configuration Register 116 */
    volatile uint32_t PADCONFIG117;              /* PAD Configuration Register 117 */
    volatile uint32_t PADCONFIG118;              /* PAD Configuration Register 118 */
    volatile uint32_t PADCONFIG119;              /* PAD Configuration Register 119 */
    volatile uint32_t PADCONFIG120;              /* PAD Configuration Register 120 */
    volatile uint32_t PADCONFIG121;              /* PAD Configuration Register 121 */
    volatile uint32_t PADCONFIG122;              /* PAD Configuration Register 122 */
    volatile uint32_t PADCONFIG123;              /* PAD Configuration Register 123 */
    volatile uint32_t PADCONFIG124;              /* PAD Configuration Register 124 */
    volatile uint32_t PADCONFIG125;              /* PAD Configuration Register 125 */
    volatile uint32_t PADCONFIG126;              /* PAD Configuration Register 126 */
    volatile uint32_t PADCONFIG127;              /* PAD Configuration Register 127 */
    volatile uint32_t PADCONFIG128;              /* PAD Configuration Register 128 */
    volatile uint32_t PADCONFIG129;              /* PAD Configuration Register 129 */
    volatile uint32_t PADCONFIG130;              /* PAD Configuration Register 130 */
    volatile uint32_t PADCONFIG131;              /* PAD Configuration Register 131 */
    volatile uint32_t PADCONFIG132;              /* PAD Configuration Register 132 */
    volatile uint32_t PADCONFIG133;              /* PAD Configuration Register 133 */
    volatile uint32_t PADCONFIG134;              /* PAD Configuration Register 134 */
    volatile uint32_t PADCONFIG135;              /* PAD Configuration Register 135 */
    volatile uint32_t PADCONFIG136;              /* PAD Configuration Register 136 */
    volatile uint32_t PADCONFIG137;              /* PAD Configuration Register 137 */
    volatile uint32_t PADCONFIG138;              /* PAD Configuration Register 138 */
    volatile uint32_t PADCONFIG139;              /* PAD Configuration Register 139 */
    volatile uint32_t PADCONFIG140;              /* PAD Configuration Register 140 */
    volatile uint32_t PADCONFIG141;              /* PAD Configuration Register 141 */
    volatile uint32_t PADCONFIG142;              /* PAD Configuration Register 142 */
    volatile uint32_t PADCONFIG143;              /* PAD Configuration Register 143 */
    volatile uint32_t PADCONFIG144;              /* PAD Configuration Register 144 */
    volatile uint32_t PADCONFIG145;              /* PAD Configuration Register 145 */
    volatile uint32_t PADCONFIG146;              /* PAD Configuration Register 146 */
} CSL_padcfg_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PADCFG_CTRL_MMR_CFG0_PID                                     (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1                                (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS                         (0x00001010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR               (0x00001014U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE                             (0x00001018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                       (0x0000101CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_EOI                                     (0x00001020U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ADDRESS                           (0x00001024U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                       (0x00001028U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                       (0x0000102CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_CLEAR                             (0x00001030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0                              (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1                              (0x00004004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2                              (0x00004008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3                              (0x0000400CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4                              (0x00004010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5                              (0x00004014U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6                              (0x00004018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7                              (0x0000401CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8                              (0x00004020U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9                              (0x00004024U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10                             (0x00004028U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11                             (0x0000402CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12                             (0x00004030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13                             (0x00004034U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14                             (0x00004038U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15                             (0x0000403CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16                             (0x00004040U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17                             (0x00004044U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18                             (0x00004048U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19                             (0x0000404CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20                             (0x00004050U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21                             (0x00004054U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22                             (0x00004058U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23                             (0x0000405CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24                             (0x00004060U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25                             (0x00004064U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26                             (0x00004068U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27                             (0x0000406CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28                             (0x00004070U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29                             (0x00004074U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30                             (0x00004078U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31                             (0x0000407CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32                             (0x00004080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33                             (0x00004084U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34                             (0x00004088U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35                             (0x0000408CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36                             (0x00004090U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37                             (0x00004094U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38                             (0x00004098U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39                             (0x0000409CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40                             (0x000040A0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41                             (0x000040A4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42                             (0x000040A8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43                             (0x000040ACU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44                             (0x000040B0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45                             (0x000040B4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46                             (0x000040B8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47                             (0x000040BCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48                             (0x000040C0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49                             (0x000040C4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50                             (0x000040C8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51                             (0x000040CCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52                             (0x000040D0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53                             (0x000040D4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54                             (0x000040D8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55                             (0x000040DCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56                             (0x000040E0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57                             (0x000040E4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58                             (0x000040E8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59                             (0x000040ECU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60                             (0x000040F0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61                             (0x000040F4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62                             (0x000040F8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63                             (0x000040FCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64                             (0x00004100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65                             (0x00004104U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66                             (0x00004108U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67                             (0x0000410CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68                             (0x00004110U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69                             (0x00004114U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70                             (0x00004118U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71                             (0x0000411CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72                             (0x00004120U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73                             (0x00004124U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74                             (0x00004128U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75                             (0x0000412CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76                             (0x00004130U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77                             (0x00004134U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78                             (0x00004138U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79                             (0x0000413CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80                             (0x00004140U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81                             (0x00004144U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82                             (0x00004148U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83                             (0x0000414CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84                             (0x00004150U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85                             (0x00004154U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86                             (0x00004158U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87                             (0x0000415CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88                             (0x00004160U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89                             (0x00004164U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90                             (0x00004168U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91                             (0x0000416CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92                             (0x00004170U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93                             (0x00004174U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94                             (0x00004178U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95                             (0x0000417CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96                             (0x00004180U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97                             (0x00004184U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98                             (0x00004188U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99                             (0x0000418CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100                            (0x00004190U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101                            (0x00004194U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102                            (0x00004198U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103                            (0x0000419CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104                            (0x000041A0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105                            (0x000041A4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106                            (0x000041A8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107                            (0x000041ACU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108                            (0x000041B0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109                            (0x000041B4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110                            (0x000041B8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111                            (0x000041BCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112                            (0x000041C0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113                            (0x000041C4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114                            (0x000041C8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115                            (0x000041CCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116                            (0x000041D0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117                            (0x000041D4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118                            (0x000041D8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119                            (0x000041DCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120                            (0x000041E0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121                            (0x000041E4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122                            (0x000041E8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123                            (0x000041ECU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124                            (0x000041F0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125                            (0x000041F4U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126                            (0x000041F8U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127                            (0x000041FCU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128                            (0x00004200U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129                            (0x00004204U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130                            (0x00004208U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131                            (0x0000420CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132                            (0x00004210U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133                            (0x00004214U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134                            (0x00004218U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135                            (0x0000421CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136                            (0x00004220U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137                            (0x00004224U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138                            (0x00004228U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139                            (0x0000422CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140                            (0x00004230U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141                            (0x00004234U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142                            (0x00004238U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143                            (0x0000423CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144                            (0x00004240U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145                            (0x00004244U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146                            (0x00004248U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                      (0x0000003FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                     (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                       (0x0000003FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                     (0x000000C0U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                    (0x00000006U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                      (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                      (0x00000700U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                     (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                       (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MISC_MASK                       (0x0000F800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                      (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MISC_MAX                        (0x0000001FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                      (0xFFFF0000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                     (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                       (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                (0x000000FFU)
#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                 (0x000000FFU)

#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                  (0x80000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                 (0x0000001FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                   (0x00000001U)

/* INTR_RAW_STATUS */

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK           (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT          (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK           (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT          (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK           (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT          (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK          (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT         (0x00000003U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX           (0x00000001U)

/* INTR_ENABLED_STATUS_CLEAR */

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_SHIFT (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MAX (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_SHIFT (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MAX (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MASK (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_SHIFT (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_KICK_ERR_MAX (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MASK (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_SHIFT (0x00000003U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR_ENABLED_PROXY_ERR_MAX (0x00000001U)

/* INTR_ENABLE */

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK            (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT           (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK            (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT           (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT           (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT          (0x00000003U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX            (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK  (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK  (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK  (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT (0x00000002U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT (0x00000003U)
#define CSL_PADCFG_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX  (0x00000001U)

/* EOI */

#define CSL_PADCFG_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                     (0x000000FFU)
#define CSL_PADCFG_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                    (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                      (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK           (0xFFFFFFFFU)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT          (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX            (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK       (0x0000003FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT      (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX        (0x0000003FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK         (0x00000040U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT        (0x00000006U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX          (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK     (0x000000FFU)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT    (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX      (0x000000FFU)

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK    (0x000FFF00U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT   (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX     (0x00000FFFU)

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK        (0xFFF00000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT       (0x00000014U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX         (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK              (0x00000001U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT             (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX               (0x00000001U)

/* PADCONFIG0 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG0_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG1 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG1_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG2 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG2_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG3 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG3_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG4 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG4_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG5 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG5_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG6 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG6_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG7 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG7_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG8 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG8_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG9 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_MUXMODE_MASK                 (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_MUXMODE_SHIFT                (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_MUXMODE_MAX                  (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_VGPIO_SEL_MASK               (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_VGPIO_SEL_SHIFT              (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_VGPIO_SEL_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_EN_MASK               (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_EN_SHIFT              (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_POL_MASK              (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_POL_SHIFT             (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WK_LVL_POL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DEBOUNCE_SEL_MASK            (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DEBOUNCE_SEL_SHIFT           (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DEBOUNCE_SEL_MAX             (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ST_EN_MASK                   (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ST_EN_SHIFT                  (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ST_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_FORCE_DS_EN_MASK             (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_FORCE_DS_EN_SHIFT            (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_FORCE_DS_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLUDEN_MASK                (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLUDEN_SHIFT               (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLUDEN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLTYPESEL_MASK             (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLTYPESEL_SHIFT            (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_PULLTYPESEL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_RXACTIVE_MASK                (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_RXACTIVE_SHIFT               (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_RXACTIVE_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DRV_STR_MASK                 (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DRV_STR_SHIFT                (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DRV_STR_MAX                  (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_TX_DIS_MASK                  (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_TX_DIS_SHIFT                 (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_TX_DIS_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_OVR_MASK                 (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_OVR_SHIFT                (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_OVR_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_BYP_MASK                 (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_BYP_SHIFT                (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_ISO_BYP_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_EN_MASK                   (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_EN_SHIFT                  (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_EN_MAX                    (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_DIS_MASK               (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_DIS_SHIFT              (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_DIS_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_VAL_MASK               (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_VAL_SHIFT              (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DSOUT_VAL_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLUD_EN_MASK            (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLUD_EN_SHIFT           (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLUD_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLTYPE_SEL_MASK         (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLTYPE_SEL_SHIFT        (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_DS_PULLTYPE_SEL_MAX          (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EN_MASK                 (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EN_SHIFT                (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EVT_MASK                (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EVT_SHIFT               (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG9_WKUP_EVT_MAX                 (0x00000001U)

/* PADCONFIG10 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG10_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG11 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG11_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG12 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG12_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG13 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG13_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG14 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG14_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG15 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG15_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG16 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG16_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG17 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG17_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG18 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG18_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG19 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG19_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG20 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG20_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG21 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG21_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG22 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG22_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG23 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG23_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG24 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG24_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG25 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG25_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG26 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG26_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG27 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG27_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG28 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG28_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG29 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG29_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG30 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG30_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG31 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG31_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG32 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG32_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG33 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG33_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG34 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG34_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG35 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG35_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG36 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG36_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG37 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG37_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG38 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG38_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG39 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG39_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG40 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG40_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG41 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG41_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG42 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG42_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG43 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG43_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG44 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG44_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG45 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG45_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG46 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG46_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG47 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG47_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG48 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG48_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG49 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG49_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG50 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG50_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG51 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG51_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG52 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG52_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG53 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG53_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG54 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG54_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG55 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG55_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG56 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG56_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG57 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG57_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG58 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG58_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG59 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG59_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG60 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG60_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG61 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG61_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG62 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG62_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG63 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG63_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG64 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG64_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG65 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG65_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG66 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG66_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG67 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG67_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG68 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG68_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG69 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG69_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG70 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG70_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG71 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG71_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG72 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG72_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG73 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG73_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG74 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG74_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG75 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG75_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG76 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG76_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG77 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG77_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG78 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG78_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG79 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG79_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG80 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG80_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG81 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG81_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG82 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG82_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG83 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG83_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG84 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG84_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG85 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG85_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG86 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG86_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG87 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG87_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG88 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG88_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG89 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG89_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG90 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG90_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG91 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG91_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG92 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG92_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG93 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG93_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG94 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG94_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG95 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG95_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG96 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG96_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG97 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG97_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG98 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG98_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG99 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_MUXMODE_MASK                (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_MUXMODE_SHIFT               (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_MUXMODE_MAX                 (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_VGPIO_SEL_MASK              (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_VGPIO_SEL_SHIFT             (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_VGPIO_SEL_MAX               (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_EN_MASK              (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_EN_SHIFT             (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_EN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_POL_MASK             (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_POL_SHIFT            (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WK_LVL_POL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DEBOUNCE_SEL_MASK           (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DEBOUNCE_SEL_SHIFT          (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DEBOUNCE_SEL_MAX            (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ST_EN_MASK                  (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ST_EN_SHIFT                 (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ST_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_FORCE_DS_EN_MASK            (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_FORCE_DS_EN_SHIFT           (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_FORCE_DS_EN_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLUDEN_MASK               (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLUDEN_SHIFT              (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLUDEN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLTYPESEL_MASK            (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLTYPESEL_SHIFT           (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_PULLTYPESEL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_RXACTIVE_MASK               (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_RXACTIVE_SHIFT              (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_RXACTIVE_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DRV_STR_MASK                (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DRV_STR_SHIFT               (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DRV_STR_MAX                 (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_TX_DIS_MASK                 (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_TX_DIS_SHIFT                (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_TX_DIS_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_OVR_MASK                (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_OVR_SHIFT               (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_OVR_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_BYP_MASK                (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_BYP_SHIFT               (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_ISO_BYP_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_EN_MASK                  (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_EN_SHIFT                 (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_EN_MAX                   (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_DIS_MASK              (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_DIS_SHIFT             (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_DIS_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_VAL_MASK              (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_VAL_SHIFT             (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DSOUT_VAL_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLUD_EN_MASK           (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLUD_EN_SHIFT          (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLUD_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLTYPE_SEL_MASK        (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLTYPE_SEL_SHIFT       (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_DS_PULLTYPE_SEL_MAX         (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EN_MASK                (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EN_SHIFT               (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EN_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EVT_MASK               (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EVT_SHIFT              (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG99_WKUP_EVT_MAX                (0x00000001U)

/* PADCONFIG100 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG100_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG101 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG101_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG102 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG102_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG103 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG103_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG104 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG104_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG105 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG105_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG106 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG106_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG107 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG107_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG108 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG108_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG109 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG109_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG110 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG110_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG111 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG111_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG112 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG112_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG113 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG113_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG114 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG114_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG115 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG115_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG116 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG116_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG117 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG117_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG118 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG118_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG119 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG119_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG120 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG120_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG121 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG121_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG122 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG122_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG123 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG123_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG124 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG124_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG125 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG125_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG126 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG126_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG127 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG127_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG128 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG128_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG129 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG129_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG130 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG130_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG131 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG131_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG132 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG132_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG133 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG133_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG134 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG134_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG135 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG135_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG136 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG136_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG137 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG137_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG138 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG138_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG139 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG139_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG140 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG140_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG141 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG141_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG142 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG142_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG143 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG143_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG144 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG144_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG145 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG145_WKUP_EVT_MAX               (0x00000001U)

/* PADCONFIG146 */

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_MUXMODE_MASK               (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_MUXMODE_SHIFT              (0x00000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_MUXMODE_MAX                (0x0000000FU)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_VGPIO_SEL_MASK             (0x00000030U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_VGPIO_SEL_SHIFT            (0x00000004U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_VGPIO_SEL_MAX              (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_EN_MASK             (0x00000080U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_EN_SHIFT            (0x00000007U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_EN_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_POL_MASK            (0x00000100U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_POL_SHIFT           (0x00000008U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WK_LVL_POL_MAX             (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DEBOUNCE_SEL_MASK          (0x00003800U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DEBOUNCE_SEL_SHIFT         (0x0000000BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DEBOUNCE_SEL_MAX           (0x00000007U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ST_EN_MASK                 (0x00004000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ST_EN_SHIFT                (0x0000000EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ST_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_FORCE_DS_EN_MASK           (0x00008000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_FORCE_DS_EN_SHIFT          (0x0000000FU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_FORCE_DS_EN_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLUDEN_MASK              (0x00010000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLUDEN_SHIFT             (0x00000010U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLUDEN_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLTYPESEL_MASK           (0x00020000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLTYPESEL_SHIFT          (0x00000011U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_PULLTYPESEL_MAX            (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_RXACTIVE_MASK              (0x00040000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_RXACTIVE_SHIFT             (0x00000012U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_RXACTIVE_MAX               (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DRV_STR_MASK               (0x00180000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DRV_STR_SHIFT              (0x00000013U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DRV_STR_MAX                (0x00000003U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_TX_DIS_MASK                (0x00200000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_TX_DIS_SHIFT               (0x00000015U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_TX_DIS_MAX                 (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_OVR_MASK               (0x00400000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_OVR_SHIFT              (0x00000016U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_OVR_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_BYP_MASK               (0x00800000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_BYP_SHIFT              (0x00000017U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_ISO_BYP_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_EN_MASK                 (0x01000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_EN_SHIFT                (0x00000018U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_EN_MAX                  (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_DIS_MASK             (0x02000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_DIS_SHIFT            (0x00000019U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_DIS_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_VAL_MASK             (0x04000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_VAL_SHIFT            (0x0000001AU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DSOUT_VAL_MAX              (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLUD_EN_MASK          (0x08000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLUD_EN_SHIFT         (0x0000001BU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLUD_EN_MAX           (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLTYPE_SEL_MASK       (0x10000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLTYPE_SEL_SHIFT      (0x0000001CU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_DS_PULLTYPE_SEL_MAX        (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EN_MASK               (0x20000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EN_SHIFT              (0x0000001DU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EN_MAX                (0x00000001U)

#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EVT_MASK              (0x40000000U)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EVT_SHIFT             (0x0000001EU)
#define CSL_PADCFG_CTRL_MMR_CFG0_PADCONFIG146_WKUP_EVT_MAX               (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif