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
 *  Name        : cslr_ctset2.h
*/
#ifndef CSLR_CTSET2_H_
#define CSLR_CTSET2_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : System Events
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CTSETID;
    volatile uint8_t  Resv_16[12];
    volatile uint32_t CTSETSYSCFG;
    volatile uint32_t SETSTR;
    volatile uint32_t DBGTIMELOW;
    volatile uint32_t DBGTIMEHI;
    volatile uint8_t  Resv_36[4];
    volatile uint32_t CTSETCFG;
    volatile uint32_t SETSPLREG;
    volatile uint8_t  Resv_48[4];
    volatile uint32_t SETEVTENBL1;
    volatile uint32_t SETEVTENBL2;
    volatile uint32_t SETEVTENBL3;
    volatile uint32_t SETEVTENBL4;
    volatile uint32_t SETEVTENBL5;
    volatile uint32_t SETEVTENBL6;
    volatile uint32_t SETEVTENBL7;
    volatile uint32_t SETEVTENBL8;
    volatile uint32_t SETMSTID;
    volatile uint8_t  Resv_2048[1964];
    volatile uint32_t CTCNTL;
    volatile uint32_t CTNUMDBG;
    volatile uint32_t CTUSERACCCTL;
    volatile uint8_t  Resv_2080[20];
    volatile uint32_t CTSTMCNTL;
    volatile uint32_t CTSTMMSTID;
    volatile uint32_t CTSTMINTVL;
    volatile uint32_t CTSTMSEL0;
    volatile uint32_t CTSTMSEL1;
    volatile uint8_t  Resv_2112[12];
    volatile uint32_t CTINTVLR0;
    volatile uint32_t CTINTVLR1;
    volatile uint32_t CTINTVLR2;
    volatile uint32_t CTINTVLR3;
    volatile uint32_t CTINTVLR4;
    volatile uint32_t CTINTVLR5;
    volatile uint32_t CTINTVLR6;
    volatile uint32_t CTINTVLR7;
    volatile uint32_t CTINTVLR8;
    volatile uint32_t CTINTVLR9;
    volatile uint32_t CTINTVLR10;
    volatile uint32_t CTINTVLR11;
    volatile uint32_t CTINTVLR12;
    volatile uint32_t CTINTVLR13;
    volatile uint32_t CTINTVLR14;
    volatile uint32_t CTINTVLR15;
    volatile uint8_t  Resv_2208[32];
    volatile uint32_t CTDBGSGL0;
    volatile uint32_t CTDBGSGL1;
    volatile uint32_t CTDBGSGL2;
    volatile uint32_t CTDBGSGL3;
    volatile uint32_t CTDBGSGL4;
    volatile uint32_t CTDBGSGL5;
    volatile uint32_t CTDBGSGL6;
    volatile uint32_t CTDBGSGL7;
    volatile uint8_t  Resv_2544[304];
    volatile uint32_t CTGNBL0;
    volatile uint32_t CTGNBL1;
    volatile uint32_t CTGRST0;
    volatile uint32_t CTGRST1;
    volatile uint32_t CTCR0;
    volatile uint32_t CTCR1;
    volatile uint32_t CTCR2;
    volatile uint32_t CTCR3;
    volatile uint32_t CTCR4;
    volatile uint32_t CTCR5;
    volatile uint32_t CTCR6;
    volatile uint32_t CTCR7;
    volatile uint32_t CTCR8;
    volatile uint32_t CTCR9;
    volatile uint32_t CTCR10;
    volatile uint32_t CTCR11;
    volatile uint32_t CTCR12;
    volatile uint32_t CTCR13;
    volatile uint32_t CTCR14;
    volatile uint32_t CTCR15;
    volatile uint32_t CTCR16;
    volatile uint32_t CTCR17;
    volatile uint32_t CTCR18;
    volatile uint32_t CTCR19;
    volatile uint32_t CTCR20;
    volatile uint32_t CTCR21;
    volatile uint32_t CTCR22;
    volatile uint32_t CTCR23;
    volatile uint32_t CTCR24;
    volatile uint32_t CTCR25;
    volatile uint32_t CTCR26;
    volatile uint32_t CTCR27;
    volatile uint32_t CTCR28;
    volatile uint32_t CTCR29;
    volatile uint32_t CTCR30;
    volatile uint32_t CTCR31;
    volatile uint32_t CTOWN0;
    volatile uint32_t CTOWN1;
    volatile uint32_t CTOWN2;
    volatile uint32_t CTOWN3;
    volatile uint32_t CTOWN4;
    volatile uint32_t CTOWN5;
    volatile uint32_t CTOWN6;
    volatile uint32_t CTOWN7;
    volatile uint32_t CTOWN8;
    volatile uint32_t CTOWN9;
    volatile uint32_t CTOWN10;
    volatile uint32_t CTOWN11;
    volatile uint32_t CTOWN12;
    volatile uint32_t CTOWN13;
    volatile uint32_t CTOWN14;
    volatile uint32_t CTOWN15;
    volatile uint32_t CTOWN16;
    volatile uint32_t CTOWN17;
    volatile uint32_t CTOWN18;
    volatile uint32_t CTOWN19;
    volatile uint32_t CTOWN20;
    volatile uint32_t CTOWN21;
    volatile uint32_t CTOWN22;
    volatile uint32_t CTOWN23;
    volatile uint32_t CTOWN24;
    volatile uint32_t CTOWN25;
    volatile uint32_t CTOWN26;
    volatile uint32_t CTOWN27;
    volatile uint32_t CTOWN28;
    volatile uint32_t CTOWN29;
    volatile uint32_t CTOWN30;
    volatile uint32_t CTOWN31;
    volatile uint32_t CTFILT0;
    volatile uint32_t CTFILT1;
    volatile uint32_t CTFILT2;
    volatile uint32_t CTFILT3;
    volatile uint32_t CTFILT4;
    volatile uint32_t CTFILT5;
    volatile uint32_t CTFILT6;
    volatile uint32_t CTFILT7;
    volatile uint32_t CTFILT8;
    volatile uint32_t CTFILT9;
    volatile uint32_t CTFILT10;
    volatile uint32_t CTFILT11;
    volatile uint32_t CTFILT12;
    volatile uint32_t CTFILT13;
    volatile uint32_t CTFILT14;
    volatile uint32_t CTFILT15;
    volatile uint32_t CTFILT16;
    volatile uint32_t CTFILT17;
    volatile uint32_t CTFILT18;
    volatile uint32_t CTFILT19;
    volatile uint32_t CTFILT20;
    volatile uint32_t CTFILT21;
    volatile uint32_t CTFILT22;
    volatile uint32_t CTFILT23;
    volatile uint32_t CTFILT24;
    volatile uint32_t CTFILT25;
    volatile uint32_t CTFILT26;
    volatile uint32_t CTFILT27;
    volatile uint32_t CTFILT28;
    volatile uint32_t CTFILT29;
    volatile uint32_t CTFILT30;
    volatile uint32_t CTFILT31;
    volatile uint32_t CTCNTR0;
    volatile uint32_t CTCNTR1;
    volatile uint32_t CTCNTR2;
    volatile uint32_t CTCNTR3;
    volatile uint32_t CTCNTR4;
    volatile uint32_t CTCNTR5;
    volatile uint32_t CTCNTR6;
    volatile uint32_t CTCNTR7;
    volatile uint32_t CTCNTR8;
    volatile uint32_t CTCNTR9;
    volatile uint32_t CTCNTR10;
    volatile uint32_t CTCNTR11;
    volatile uint32_t CTCNTR12;
    volatile uint32_t CTCNTR13;
    volatile uint32_t CTCNTR14;
    volatile uint32_t CTCNTR15;
    volatile uint32_t CTCNTR16;
    volatile uint32_t CTCNTR17;
    volatile uint32_t CTCNTR18;
    volatile uint32_t CTCNTR19;
    volatile uint32_t CTCNTR20;
    volatile uint32_t CTCNTR21;
    volatile uint32_t CTCNTR22;
    volatile uint32_t CTCNTR23;
    volatile uint32_t CTCNTR24;
    volatile uint32_t CTCNTR25;
    volatile uint32_t CTCNTR26;
    volatile uint32_t CTCNTR27;
    volatile uint32_t CTCNTR28;
    volatile uint32_t CTCNTR29;
    volatile uint32_t CTCNTR30;
    volatile uint32_t CTCNTR31;
    volatile uint32_t CT_EOI;
    volatile uint32_t CTIRQSTAT_RAW;
    volatile uint32_t CTIRQSTAT;
    volatile uint32_t CTIRQENABLE_SET;
    volatile uint32_t CTIRQENABLE_CLR;
    volatile uint8_t  Resv_6144[3052];
    volatile uint32_t STPTCR;
    volatile uint32_t STPTID;
    volatile uint8_t  Resv_6160[8];
    volatile uint32_t STPASYNC;
    volatile uint32_t STPFFCR;
    volatile uint32_t STPFEAT1;
} CSL_ctset2_cfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CTSET2_CFG_CTSETID                                                 (0x00000000U)
#define CSL_CTSET2_CFG_CTSETSYSCFG                                             (0x00000010U)
#define CSL_CTSET2_CFG_SETSTR                                                  (0x00000014U)
#define CSL_CTSET2_CFG_DBGTIMELOW                                              (0x00000018U)
#define CSL_CTSET2_CFG_DBGTIMEHI                                               (0x0000001CU)
#define CSL_CTSET2_CFG_CTSETCFG                                                (0x00000024U)
#define CSL_CTSET2_CFG_SETSPLREG                                               (0x00000028U)
#define CSL_CTSET2_CFG_SETEVTENBL1                                             (0x00000030U)
#define CSL_CTSET2_CFG_SETEVTENBL2                                             (0x00000034U)
#define CSL_CTSET2_CFG_SETEVTENBL3                                             (0x00000038U)
#define CSL_CTSET2_CFG_SETEVTENBL4                                             (0x0000003CU)
#define CSL_CTSET2_CFG_SETEVTENBL5                                             (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL6                                             (0x00000044U)
#define CSL_CTSET2_CFG_SETEVTENBL7                                             (0x00000048U)
#define CSL_CTSET2_CFG_SETEVTENBL8                                             (0x0000004CU)
#define CSL_CTSET2_CFG_SETMSTID                                                (0x00000050U)
#define CSL_CTSET2_CFG_CTCNTL                                                  (0x00000800U)
#define CSL_CTSET2_CFG_CTNUMDBG                                                (0x00000804U)
#define CSL_CTSET2_CFG_CTUSERACCCTL                                            (0x00000808U)
#define CSL_CTSET2_CFG_CTSTMCNTL                                               (0x00000820U)
#define CSL_CTSET2_CFG_CTSTMMSTID                                              (0x00000824U)
#define CSL_CTSET2_CFG_CTSTMINTVL                                              (0x00000828U)
#define CSL_CTSET2_CFG_CTSTMSEL0                                               (0x0000082CU)
#define CSL_CTSET2_CFG_CTSTMSEL1                                               (0x00000830U)
#define CSL_CTSET2_CFG_CTINTVLR0                                               (0x00000840U)
#define CSL_CTSET2_CFG_CTINTVLR1                                               (0x00000844U)
#define CSL_CTSET2_CFG_CTINTVLR2                                               (0x00000848U)
#define CSL_CTSET2_CFG_CTINTVLR3                                               (0x0000084CU)
#define CSL_CTSET2_CFG_CTINTVLR4                                               (0x00000850U)
#define CSL_CTSET2_CFG_CTINTVLR5                                               (0x00000854U)
#define CSL_CTSET2_CFG_CTINTVLR6                                               (0x00000858U)
#define CSL_CTSET2_CFG_CTINTVLR7                                               (0x0000085CU)
#define CSL_CTSET2_CFG_CTINTVLR8                                               (0x00000860U)
#define CSL_CTSET2_CFG_CTINTVLR9                                               (0x00000864U)
#define CSL_CTSET2_CFG_CTINTVLR10                                              (0x00000868U)
#define CSL_CTSET2_CFG_CTINTVLR11                                              (0x0000086CU)
#define CSL_CTSET2_CFG_CTINTVLR12                                              (0x00000870U)
#define CSL_CTSET2_CFG_CTINTVLR13                                              (0x00000874U)
#define CSL_CTSET2_CFG_CTINTVLR14                                              (0x00000878U)
#define CSL_CTSET2_CFG_CTINTVLR15                                              (0x0000087CU)
#define CSL_CTSET2_CFG_CTDBGSGL0                                               (0x000008A0U)
#define CSL_CTSET2_CFG_CTDBGSGL1                                               (0x000008A4U)
#define CSL_CTSET2_CFG_CTDBGSGL2                                               (0x000008A8U)
#define CSL_CTSET2_CFG_CTDBGSGL3                                               (0x000008ACU)
#define CSL_CTSET2_CFG_CTDBGSGL4                                               (0x000008B0U)
#define CSL_CTSET2_CFG_CTDBGSGL5                                               (0x000008B4U)
#define CSL_CTSET2_CFG_CTDBGSGL6                                               (0x000008B8U)
#define CSL_CTSET2_CFG_CTDBGSGL7                                               (0x000008BCU)
#define CSL_CTSET2_CFG_CTGNBL0                                                 (0x000009F0U)
#define CSL_CTSET2_CFG_CTGNBL1                                                 (0x000009F4U)
#define CSL_CTSET2_CFG_CTGRST0                                                 (0x000009F8U)
#define CSL_CTSET2_CFG_CTGRST1                                                 (0x000009FCU)
#define CSL_CTSET2_CFG_CTCR0                                                   (0x00000A00U)
#define CSL_CTSET2_CFG_CTCR1                                                   (0x00000A04U)
#define CSL_CTSET2_CFG_CTCR2                                                   (0x00000A08U)
#define CSL_CTSET2_CFG_CTCR3                                                   (0x00000A0CU)
#define CSL_CTSET2_CFG_CTCR4                                                   (0x00000A10U)
#define CSL_CTSET2_CFG_CTCR5                                                   (0x00000A14U)
#define CSL_CTSET2_CFG_CTCR6                                                   (0x00000A18U)
#define CSL_CTSET2_CFG_CTCR7                                                   (0x00000A1CU)
#define CSL_CTSET2_CFG_CTCR8                                                   (0x00000A20U)
#define CSL_CTSET2_CFG_CTCR9                                                   (0x00000A24U)
#define CSL_CTSET2_CFG_CTCR10                                                  (0x00000A28U)
#define CSL_CTSET2_CFG_CTCR11                                                  (0x00000A2CU)
#define CSL_CTSET2_CFG_CTCR12                                                  (0x00000A30U)
#define CSL_CTSET2_CFG_CTCR13                                                  (0x00000A34U)
#define CSL_CTSET2_CFG_CTCR14                                                  (0x00000A38U)
#define CSL_CTSET2_CFG_CTCR15                                                  (0x00000A3CU)
#define CSL_CTSET2_CFG_CTCR16                                                  (0x00000A40U)
#define CSL_CTSET2_CFG_CTCR17                                                  (0x00000A44U)
#define CSL_CTSET2_CFG_CTCR18                                                  (0x00000A48U)
#define CSL_CTSET2_CFG_CTCR19                                                  (0x00000A4CU)
#define CSL_CTSET2_CFG_CTCR20                                                  (0x00000A50U)
#define CSL_CTSET2_CFG_CTCR21                                                  (0x00000A54U)
#define CSL_CTSET2_CFG_CTCR22                                                  (0x00000A58U)
#define CSL_CTSET2_CFG_CTCR23                                                  (0x00000A5CU)
#define CSL_CTSET2_CFG_CTCR24                                                  (0x00000A60U)
#define CSL_CTSET2_CFG_CTCR25                                                  (0x00000A64U)
#define CSL_CTSET2_CFG_CTCR26                                                  (0x00000A68U)
#define CSL_CTSET2_CFG_CTCR27                                                  (0x00000A6CU)
#define CSL_CTSET2_CFG_CTCR28                                                  (0x00000A70U)
#define CSL_CTSET2_CFG_CTCR29                                                  (0x00000A74U)
#define CSL_CTSET2_CFG_CTCR30                                                  (0x00000A78U)
#define CSL_CTSET2_CFG_CTCR31                                                  (0x00000A7CU)
#define CSL_CTSET2_CFG_CTOWN0                                                  (0x00000A80U)
#define CSL_CTSET2_CFG_CTOWN1                                                  (0x00000A84U)
#define CSL_CTSET2_CFG_CTOWN2                                                  (0x00000A88U)
#define CSL_CTSET2_CFG_CTOWN3                                                  (0x00000A8CU)
#define CSL_CTSET2_CFG_CTOWN4                                                  (0x00000A90U)
#define CSL_CTSET2_CFG_CTOWN5                                                  (0x00000A94U)
#define CSL_CTSET2_CFG_CTOWN6                                                  (0x00000A98U)
#define CSL_CTSET2_CFG_CTOWN7                                                  (0x00000A9CU)
#define CSL_CTSET2_CFG_CTOWN8                                                  (0x00000AA0U)
#define CSL_CTSET2_CFG_CTOWN9                                                  (0x00000AA4U)
#define CSL_CTSET2_CFG_CTOWN10                                                 (0x00000AA8U)
#define CSL_CTSET2_CFG_CTOWN11                                                 (0x00000AACU)
#define CSL_CTSET2_CFG_CTOWN12                                                 (0x00000AB0U)
#define CSL_CTSET2_CFG_CTOWN13                                                 (0x00000AB4U)
#define CSL_CTSET2_CFG_CTOWN14                                                 (0x00000AB8U)
#define CSL_CTSET2_CFG_CTOWN15                                                 (0x00000ABCU)
#define CSL_CTSET2_CFG_CTOWN16                                                 (0x00000AC0U)
#define CSL_CTSET2_CFG_CTOWN17                                                 (0x00000AC4U)
#define CSL_CTSET2_CFG_CTOWN18                                                 (0x00000AC8U)
#define CSL_CTSET2_CFG_CTOWN19                                                 (0x00000ACCU)
#define CSL_CTSET2_CFG_CTOWN20                                                 (0x00000AD0U)
#define CSL_CTSET2_CFG_CTOWN21                                                 (0x00000AD4U)
#define CSL_CTSET2_CFG_CTOWN22                                                 (0x00000AD8U)
#define CSL_CTSET2_CFG_CTOWN23                                                 (0x00000ADCU)
#define CSL_CTSET2_CFG_CTOWN24                                                 (0x00000AE0U)
#define CSL_CTSET2_CFG_CTOWN25                                                 (0x00000AE4U)
#define CSL_CTSET2_CFG_CTOWN26                                                 (0x00000AE8U)
#define CSL_CTSET2_CFG_CTOWN27                                                 (0x00000AECU)
#define CSL_CTSET2_CFG_CTOWN28                                                 (0x00000AF0U)
#define CSL_CTSET2_CFG_CTOWN29                                                 (0x00000AF4U)
#define CSL_CTSET2_CFG_CTOWN30                                                 (0x00000AF8U)
#define CSL_CTSET2_CFG_CTOWN31                                                 (0x00000AFCU)
#define CSL_CTSET2_CFG_CTFILT0                                                 (0x00000B00U)
#define CSL_CTSET2_CFG_CTFILT1                                                 (0x00000B04U)
#define CSL_CTSET2_CFG_CTFILT2                                                 (0x00000B08U)
#define CSL_CTSET2_CFG_CTFILT3                                                 (0x00000B0CU)
#define CSL_CTSET2_CFG_CTFILT4                                                 (0x00000B10U)
#define CSL_CTSET2_CFG_CTFILT5                                                 (0x00000B14U)
#define CSL_CTSET2_CFG_CTFILT6                                                 (0x00000B18U)
#define CSL_CTSET2_CFG_CTFILT7                                                 (0x00000B1CU)
#define CSL_CTSET2_CFG_CTFILT8                                                 (0x00000B20U)
#define CSL_CTSET2_CFG_CTFILT9                                                 (0x00000B24U)
#define CSL_CTSET2_CFG_CTFILT10                                                (0x00000B28U)
#define CSL_CTSET2_CFG_CTFILT11                                                (0x00000B2CU)
#define CSL_CTSET2_CFG_CTFILT12                                                (0x00000B30U)
#define CSL_CTSET2_CFG_CTFILT13                                                (0x00000B34U)
#define CSL_CTSET2_CFG_CTFILT14                                                (0x00000B38U)
#define CSL_CTSET2_CFG_CTFILT15                                                (0x00000B3CU)
#define CSL_CTSET2_CFG_CTFILT16                                                (0x00000B40U)
#define CSL_CTSET2_CFG_CTFILT17                                                (0x00000B44U)
#define CSL_CTSET2_CFG_CTFILT18                                                (0x00000B48U)
#define CSL_CTSET2_CFG_CTFILT19                                                (0x00000B4CU)
#define CSL_CTSET2_CFG_CTFILT20                                                (0x00000B50U)
#define CSL_CTSET2_CFG_CTFILT21                                                (0x00000B54U)
#define CSL_CTSET2_CFG_CTFILT22                                                (0x00000B58U)
#define CSL_CTSET2_CFG_CTFILT23                                                (0x00000B5CU)
#define CSL_CTSET2_CFG_CTFILT24                                                (0x00000B60U)
#define CSL_CTSET2_CFG_CTFILT25                                                (0x00000B64U)
#define CSL_CTSET2_CFG_CTFILT26                                                (0x00000B68U)
#define CSL_CTSET2_CFG_CTFILT27                                                (0x00000B6CU)
#define CSL_CTSET2_CFG_CTFILT28                                                (0x00000B70U)
#define CSL_CTSET2_CFG_CTFILT29                                                (0x00000B74U)
#define CSL_CTSET2_CFG_CTFILT30                                                (0x00000B78U)
#define CSL_CTSET2_CFG_CTFILT31                                                (0x00000B7CU)
#define CSL_CTSET2_CFG_CTCNTR0                                                 (0x00000B80U)
#define CSL_CTSET2_CFG_CTCNTR1                                                 (0x00000B84U)
#define CSL_CTSET2_CFG_CTCNTR2                                                 (0x00000B88U)
#define CSL_CTSET2_CFG_CTCNTR3                                                 (0x00000B8CU)
#define CSL_CTSET2_CFG_CTCNTR4                                                 (0x00000B90U)
#define CSL_CTSET2_CFG_CTCNTR5                                                 (0x00000B94U)
#define CSL_CTSET2_CFG_CTCNTR6                                                 (0x00000B98U)
#define CSL_CTSET2_CFG_CTCNTR7                                                 (0x00000B9CU)
#define CSL_CTSET2_CFG_CTCNTR8                                                 (0x00000BA0U)
#define CSL_CTSET2_CFG_CTCNTR9                                                 (0x00000BA4U)
#define CSL_CTSET2_CFG_CTCNTR10                                                (0x00000BA8U)
#define CSL_CTSET2_CFG_CTCNTR11                                                (0x00000BACU)
#define CSL_CTSET2_CFG_CTCNTR12                                                (0x00000BB0U)
#define CSL_CTSET2_CFG_CTCNTR13                                                (0x00000BB4U)
#define CSL_CTSET2_CFG_CTCNTR14                                                (0x00000BB8U)
#define CSL_CTSET2_CFG_CTCNTR15                                                (0x00000BBCU)
#define CSL_CTSET2_CFG_CTCNTR16                                                (0x00000BC0U)
#define CSL_CTSET2_CFG_CTCNTR17                                                (0x00000BC4U)
#define CSL_CTSET2_CFG_CTCNTR18                                                (0x00000BC8U)
#define CSL_CTSET2_CFG_CTCNTR19                                                (0x00000BCCU)
#define CSL_CTSET2_CFG_CTCNTR20                                                (0x00000BD0U)
#define CSL_CTSET2_CFG_CTCNTR21                                                (0x00000BD4U)
#define CSL_CTSET2_CFG_CTCNTR22                                                (0x00000BD8U)
#define CSL_CTSET2_CFG_CTCNTR23                                                (0x00000BDCU)
#define CSL_CTSET2_CFG_CTCNTR24                                                (0x00000BE0U)
#define CSL_CTSET2_CFG_CTCNTR25                                                (0x00000BE4U)
#define CSL_CTSET2_CFG_CTCNTR26                                                (0x00000BE8U)
#define CSL_CTSET2_CFG_CTCNTR27                                                (0x00000BECU)
#define CSL_CTSET2_CFG_CTCNTR28                                                (0x00000BF0U)
#define CSL_CTSET2_CFG_CTCNTR29                                                (0x00000BF4U)
#define CSL_CTSET2_CFG_CTCNTR30                                                (0x00000BF8U)
#define CSL_CTSET2_CFG_CTCNTR31                                                (0x00000BFCU)
#define CSL_CTSET2_CFG_CT_EOI                                                  (0x00000C00U)
#define CSL_CTSET2_CFG_CTIRQSTAT_RAW                                           (0x00000C04U)
#define CSL_CTSET2_CFG_CTIRQSTAT                                               (0x00000C08U)
#define CSL_CTSET2_CFG_CTIRQENABLE_SET                                         (0x00000C0CU)
#define CSL_CTSET2_CFG_CTIRQENABLE_CLR                                         (0x00000C10U)
#define CSL_CTSET2_CFG_STPTCR                                                  (0x00001800U)
#define CSL_CTSET2_CFG_STPTID                                                  (0x00001804U)
#define CSL_CTSET2_CFG_STPASYNC                                                (0x00001810U)
#define CSL_CTSET2_CFG_STPFFCR                                                 (0x00001814U)
#define CSL_CTSET2_CFG_STPFEAT1                                                (0x00001818U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CTSETID */

#define CSL_CTSET2_CFG_CTSETID_MINOR_REV_MASK                                  (0x0000003FU)
#define CSL_CTSET2_CFG_CTSETID_MINOR_REV_SHIFT                                 (0x00000000U)
#define CSL_CTSET2_CFG_CTSETID_MINOR_REV_MAX                                   (0x0000003FU)

#define CSL_CTSET2_CFG_CTSETID_CUSTOM_MASK                                     (0x000000C0U)
#define CSL_CTSET2_CFG_CTSETID_CUSTOM_SHIFT                                    (0x00000006U)
#define CSL_CTSET2_CFG_CTSETID_CUSTOM_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTSETID_MAJOR_REV_MASK                                  (0x00000700U)
#define CSL_CTSET2_CFG_CTSETID_MAJOR_REV_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTSETID_MAJOR_REV_MAX                                   (0x00000007U)

#define CSL_CTSET2_CFG_CTSETID_RTL_VERSION_MASK                                (0x0000F800U)
#define CSL_CTSET2_CFG_CTSETID_RTL_VERSION_SHIFT                               (0x0000000BU)
#define CSL_CTSET2_CFG_CTSETID_RTL_VERSION_MAX                                 (0x0000001FU)

#define CSL_CTSET2_CFG_CTSETID_FUNCTION_MASK                                   (0x0FFF0000U)
#define CSL_CTSET2_CFG_CTSETID_FUNCTION_SHIFT                                  (0x00000010U)
#define CSL_CTSET2_CFG_CTSETID_FUNCTION_MAX                                    (0x00000FFFU)

#define CSL_CTSET2_CFG_CTSETID_BU_MASK                                         (0x30000000U)
#define CSL_CTSET2_CFG_CTSETID_BU_SHIFT                                        (0x0000001CU)
#define CSL_CTSET2_CFG_CTSETID_BU_MAX                                          (0x00000003U)

#define CSL_CTSET2_CFG_CTSETID_SCHEME_MASK                                     (0xC0000000U)
#define CSL_CTSET2_CFG_CTSETID_SCHEME_SHIFT                                    (0x0000001EU)
#define CSL_CTSET2_CFG_CTSETID_SCHEME_MAX                                      (0x00000003U)

/* CTSETSYSCFG */

#define CSL_CTSET2_CFG_CTSETSYSCFG_SOFTRESET_MASK                              (0x00000001U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_SOFTRESET_SHIFT                             (0x00000000U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_SOFTRESET_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED_MASK                               (0x00000002U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED_SHIFT                              (0x00000001U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTSETSYSCFG_IDLEMODE_MASK                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTSETSYSCFG_IDLEMODE_SHIFT                              (0x00000002U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_IDLEMODE_MAX                                (0x00000003U)

#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED1_MASK                              (0xFFFFFFF0U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED1_SHIFT                             (0x00000004U)
#define CSL_CTSET2_CFG_CTSETSYSCFG_RESERVED1_MAX                               (0x0FFFFFFFU)

/* SETSTR */

#define CSL_CTSET2_CFG_SETSTR_RESETDONE_MASK                                   (0x00000001U)
#define CSL_CTSET2_CFG_SETSTR_RESETDONE_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_SETSTR_RESETDONE_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_SETSTR_RESERVED_MASK                                    (0x000000FEU)
#define CSL_CTSET2_CFG_SETSTR_RESERVED_SHIFT                                   (0x00000001U)
#define CSL_CTSET2_CFG_SETSTR_RESERVED_MAX                                     (0x0000007FU)

#define CSL_CTSET2_CFG_SETSTR_HWFIFOEMPTY_MASK                                 (0x00000100U)
#define CSL_CTSET2_CFG_SETSTR_HWFIFOEMPTY_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_SETSTR_HWFIFOEMPTY_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_SETSTR_RESERVED1_MASK                                   (0xFFFFFE00U)
#define CSL_CTSET2_CFG_SETSTR_RESERVED1_SHIFT                                  (0x00000009U)
#define CSL_CTSET2_CFG_SETSTR_RESERVED1_MAX                                    (0x007FFFFFU)

/* DBGTIMELOW */

#define CSL_CTSET2_CFG_DBGTIMELOW_DBGTIME_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_DBGTIMELOW_DBGTIME_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_DBGTIMELOW_DBGTIME_MAX                                  (0xFFFFFFFFU)

/* DBGTIMEHI */

#define CSL_CTSET2_CFG_DBGTIMEHI_DBGTIME_MASK                                  (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_DBGTIMEHI_DBGTIME_SHIFT                                 (0x00000000U)
#define CSL_CTSET2_CFG_DBGTIMEHI_DBGTIME_MAX                                   (0xFFFFFFFFU)

/* CTSETCFG */

#define CSL_CTSET2_CFG_CTSETCFG_RESERVED_MASK                                  (0x00000001U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED_SHIFT                                 (0x00000000U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_STARTCAPT_MASK                                 (0x00000002U)
#define CSL_CTSET2_CFG_CTSETCFG_STARTCAPT_SHIFT                                (0x00000001U)
#define CSL_CTSET2_CFG_CTSETCFG_STARTCAPT_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_STOPCAPT_MASK                                  (0x00000004U)
#define CSL_CTSET2_CFG_CTSETCFG_STOPCAPT_SHIFT                                 (0x00000002U)
#define CSL_CTSET2_CFG_CTSETCFG_STOPCAPT_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_MSGMODE_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTSETCFG_MSGMODE_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTSETCFG_MSGMODE_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_EVENTLEVEL_MASK                                (0x00000010U)
#define CSL_CTSET2_CFG_CTSETCFG_EVENTLEVEL_SHIFT                               (0x00000004U)
#define CSL_CTSET2_CFG_CTSETCFG_EVENTLEVEL_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_RESERVED1_MASK                                 (0x00000060U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED1_SHIFT                                (0x00000005U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED1_MAX                                  (0x00000003U)

#define CSL_CTSET2_CFG_CTSETCFG_SYSEVENTCAPTEN_MASK                            (0x00000080U)
#define CSL_CTSET2_CFG_CTSETCFG_SYSEVENTCAPTEN_SHIFT                           (0x00000007U)
#define CSL_CTSET2_CFG_CTSETCFG_SYSEVENTCAPTEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_CTSETCFG_RESERVED2_MASK                                 (0x0FFFFF00U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED2_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTSETCFG_RESERVED2_MAX                                  (0x000FFFFFU)

#define CSL_CTSET2_CFG_CTSETCFG_CLAIM_MASK                                     (0xF0000000U)
#define CSL_CTSET2_CFG_CTSETCFG_CLAIM_SHIFT                                    (0x0000001CU)
#define CSL_CTSET2_CFG_CTSETCFG_CLAIM_MAX                                      (0x0000000FU)

/* SETSPLREG */

#define CSL_CTSET2_CFG_SETSPLREG_WINDOWSIZE_MASK                               (0x000000FFU)
#define CSL_CTSET2_CFG_SETSPLREG_WINDOWSIZE_SHIFT                              (0x00000000U)
#define CSL_CTSET2_CFG_SETSPLREG_WINDOWSIZE_MAX                                (0x000000FFU)

#define CSL_CTSET2_CFG_SETSPLREG_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_SETSPLREG_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_SETSPLREG_RESERVED_MAX                                  (0x00FFFFFFU)

/* SETEVTENBL1 */

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT1DETEN_MASK                            (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT1DETEN_SHIFT                           (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT1DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT2DETEN_MASK                            (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT2DETEN_SHIFT                           (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT2DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT3DETEN_MASK                            (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT3DETEN_SHIFT                           (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT3DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT4DETEN_MASK                            (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT4DETEN_SHIFT                           (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT4DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT5DETEN_MASK                            (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT5DETEN_SHIFT                           (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT5DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT6DETEN_MASK                            (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT6DETEN_SHIFT                           (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT6DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT7DETEN_MASK                            (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT7DETEN_SHIFT                           (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT7DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT8DETEN_MASK                            (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT8DETEN_SHIFT                           (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT8DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT9DETEN_MASK                            (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT9DETEN_SHIFT                           (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT9DETEN_MAX                             (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT10DETEN_MASK                           (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT10DETEN_SHIFT                          (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT10DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT11DETEN_MASK                           (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT11DETEN_SHIFT                          (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT11DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT12DETEN_MASK                           (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT12DETEN_SHIFT                          (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT12DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT13DETEN_MASK                           (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT13DETEN_SHIFT                          (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT13DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT14DETEN_MASK                           (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT14DETEN_SHIFT                          (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT14DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT15DETEN_MASK                           (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT15DETEN_SHIFT                          (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT15DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT16DETEN_MASK                           (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT16DETEN_SHIFT                          (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT16DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT17DETEN_MASK                           (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT17DETEN_SHIFT                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT17DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT18DETEN_MASK                           (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT18DETEN_SHIFT                          (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT18DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT19DETEN_MASK                           (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT19DETEN_SHIFT                          (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT19DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT20DETEN_MASK                           (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT20DETEN_SHIFT                          (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT20DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT21DETEN_MASK                           (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT21DETEN_SHIFT                          (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT21DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT22DETEN_MASK                           (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT22DETEN_SHIFT                          (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT22DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT23DETEN_MASK                           (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT23DETEN_SHIFT                          (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT23DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT24DETEN_MASK                           (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT24DETEN_SHIFT                          (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT24DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT25DETEN_MASK                           (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT25DETEN_SHIFT                          (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT25DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT26DETEN_MASK                           (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT26DETEN_SHIFT                          (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT26DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT27DETEN_MASK                           (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT27DETEN_SHIFT                          (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT27DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT28DETEN_MASK                           (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT28DETEN_SHIFT                          (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT28DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT29DETEN_MASK                           (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT29DETEN_SHIFT                          (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT29DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT30DETEN_MASK                           (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT30DETEN_SHIFT                          (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT30DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT31DETEN_MASK                           (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT31DETEN_SHIFT                          (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT31DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT32DETEN_MASK                           (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT32DETEN_SHIFT                          (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL1_EVENT32DETEN_MAX                            (0x00000001U)

/* SETEVTENBL2 */

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT33DETEN_MASK                           (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT33DETEN_SHIFT                          (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT33DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT34DETEN_MASK                           (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT34DETEN_SHIFT                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT34DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT35DETEN_MASK                           (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT35DETEN_SHIFT                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT35DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT36DETEN_MASK                           (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT36DETEN_SHIFT                          (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT36DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT37DETEN_MASK                           (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT37DETEN_SHIFT                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT37DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT38DETEN_MASK                           (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT38DETEN_SHIFT                          (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT38DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT39DETEN_MASK                           (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT39DETEN_SHIFT                          (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT39DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT40DETEN_MASK                           (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT40DETEN_SHIFT                          (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT40DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT41DETEN_MASK                           (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT41DETEN_SHIFT                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT41DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT42DETEN_MASK                           (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT42DETEN_SHIFT                          (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT42DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT43DETEN_MASK                           (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT43DETEN_SHIFT                          (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT43DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT44DETEN_MASK                           (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT44DETEN_SHIFT                          (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT44DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT45DETEN_MASK                           (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT45DETEN_SHIFT                          (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT45DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT46DETEN_MASK                           (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT46DETEN_SHIFT                          (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT46DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT47DETEN_MASK                           (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT47DETEN_SHIFT                          (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT47DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT48DETEN_MASK                           (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT48DETEN_SHIFT                          (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT48DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT49DETEN_MASK                           (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT49DETEN_SHIFT                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT49DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT50DETEN_MASK                           (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT50DETEN_SHIFT                          (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT50DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT51DETEN_MASK                           (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT51DETEN_SHIFT                          (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT51DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT52DETEN_MASK                           (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT52DETEN_SHIFT                          (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT52DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT53DETEN_MASK                           (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT53DETEN_SHIFT                          (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT53DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT54DETEN_MASK                           (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT54DETEN_SHIFT                          (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT54DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT55DETEN_MASK                           (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT55DETEN_SHIFT                          (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT55DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT56DETEN_MASK                           (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT56DETEN_SHIFT                          (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT56DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT57DETEN_MASK                           (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT57DETEN_SHIFT                          (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT57DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT58DETEN_MASK                           (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT58DETEN_SHIFT                          (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT58DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT59DETEN_MASK                           (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT59DETEN_SHIFT                          (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT59DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT60DETEN_MASK                           (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT60DETEN_SHIFT                          (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT60DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT61DETEN_MASK                           (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT61DETEN_SHIFT                          (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT61DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT62DETEN_MASK                           (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT62DETEN_SHIFT                          (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT62DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT63DETEN_MASK                           (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT63DETEN_SHIFT                          (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT63DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT64DETEN_MASK                           (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT64DETEN_SHIFT                          (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL2_EVENT64DETEN_MAX                            (0x00000001U)

/* SETEVTENBL3 */

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT65DETEN_MASK                           (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT65DETEN_SHIFT                          (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT65DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT66DETEN_MASK                           (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT66DETEN_SHIFT                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT66DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT67DETEN_MASK                           (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT67DETEN_SHIFT                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT67DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT68DETEN_MASK                           (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT68DETEN_SHIFT                          (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT68DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT69DETEN_MASK                           (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT69DETEN_SHIFT                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT69DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT70DETEN_MASK                           (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT70DETEN_SHIFT                          (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT70DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT71DETEN_MASK                           (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT71DETEN_SHIFT                          (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT71DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT72DETEN_MASK                           (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT72DETEN_SHIFT                          (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT72DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT73DETEN_MASK                           (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT73DETEN_SHIFT                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT73DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT74DETEN_MASK                           (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT74DETEN_SHIFT                          (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT74DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT75DETEN_MASK                           (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT75DETEN_SHIFT                          (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT75DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT76DETEN_MASK                           (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT76DETEN_SHIFT                          (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT76DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT77DETEN_MASK                           (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT77DETEN_SHIFT                          (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT77DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT78DETEN_MASK                           (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT78DETEN_SHIFT                          (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT78DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT79DETEN_MASK                           (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT79DETEN_SHIFT                          (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT79DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT80DETEN_MASK                           (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT80DETEN_SHIFT                          (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT80DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT81DETEN_MASK                           (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT81DETEN_SHIFT                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT81DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT82DETEN_MASK                           (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT82DETEN_SHIFT                          (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT82DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT83DETEN_MASK                           (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT83DETEN_SHIFT                          (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT83DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT84DETEN_MASK                           (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT84DETEN_SHIFT                          (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT84DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT85DETEN_MASK                           (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT85DETEN_SHIFT                          (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT85DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT86DETEN_MASK                           (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT86DETEN_SHIFT                          (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT86DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT87DETEN_MASK                           (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT87DETEN_SHIFT                          (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT87DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT88DETEN_MASK                           (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT88DETEN_SHIFT                          (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT88DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT89DETEN_MASK                           (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT89DETEN_SHIFT                          (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT89DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT90DETEN_MASK                           (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT90DETEN_SHIFT                          (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT90DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT91DETEN_MASK                           (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT91DETEN_SHIFT                          (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT91DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT92DETEN_MASK                           (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT92DETEN_SHIFT                          (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT92DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT93DETEN_MASK                           (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT93DETEN_SHIFT                          (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT93DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT94DETEN_MASK                           (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT94DETEN_SHIFT                          (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT94DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT95DETEN_MASK                           (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT95DETEN_SHIFT                          (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT95DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT96DETEN_MASK                           (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT96DETEN_SHIFT                          (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL3_EVENT96DETEN_MAX                            (0x00000001U)

/* SETEVTENBL4 */

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT97DETEN_MASK                           (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT97DETEN_SHIFT                          (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT97DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT98DETEN_MASK                           (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT98DETEN_SHIFT                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT98DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT99DETEN_MASK                           (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT99DETEN_SHIFT                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT99DETEN_MAX                            (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT100DETEN_MASK                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT100DETEN_SHIFT                         (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT100DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT101DETEN_MASK                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT101DETEN_SHIFT                         (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT101DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT102DETEN_MASK                          (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT102DETEN_SHIFT                         (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT102DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT103DETEN_MASK                          (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT103DETEN_SHIFT                         (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT103DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT104DETEN_MASK                          (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT104DETEN_SHIFT                         (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT104DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT105DETEN_MASK                          (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT105DETEN_SHIFT                         (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT105DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT106DETEN_MASK                          (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT106DETEN_SHIFT                         (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT106DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT107DETEN_MASK                          (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT107DETEN_SHIFT                         (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT107DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT108DETEN_MASK                          (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT108DETEN_SHIFT                         (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT108DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT109DETEN_MASK                          (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT109DETEN_SHIFT                         (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT109DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT110DETEN_MASK                          (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT110DETEN_SHIFT                         (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT110DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT111DETEN_MASK                          (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT111DETEN_SHIFT                         (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT111DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT112DETEN_MASK                          (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT112DETEN_SHIFT                         (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT112DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT113DETEN_MASK                          (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT113DETEN_SHIFT                         (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT113DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT114DETEN_MASK                          (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT114DETEN_SHIFT                         (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT114DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT115DETEN_MASK                          (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT115DETEN_SHIFT                         (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT115DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT116DETEN_MASK                          (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT116DETEN_SHIFT                         (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT116DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT117DETEN_MASK                          (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT117DETEN_SHIFT                         (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT117DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT118DETEN_MASK                          (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT118DETEN_SHIFT                         (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT118DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT119DETEN_MASK                          (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT119DETEN_SHIFT                         (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT119DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT120DETEN_MASK                          (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT120DETEN_SHIFT                         (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT120DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT121DETEN_MASK                          (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT121DETEN_SHIFT                         (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT121DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT122DETEN_MASK                          (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT122DETEN_SHIFT                         (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT122DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT123DETEN_MASK                          (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT123DETEN_SHIFT                         (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT123DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT124DETEN_MASK                          (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT124DETEN_SHIFT                         (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT124DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT125DETEN_MASK                          (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT125DETEN_SHIFT                         (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT125DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT126DETEN_MASK                          (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT126DETEN_SHIFT                         (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT126DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT127DETEN_MASK                          (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT127DETEN_SHIFT                         (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT127DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT128DETEN_MASK                          (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT128DETEN_SHIFT                         (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL4_EVENT128DETEN_MAX                           (0x00000001U)

/* SETEVTENBL5 */

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT129DETEN_MASK                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT129DETEN_SHIFT                         (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT129DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT130DETEN_MASK                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT130DETEN_SHIFT                         (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT130DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT131DETEN_MASK                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT131DETEN_SHIFT                         (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT131DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT132DETEN_MASK                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT132DETEN_SHIFT                         (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT132DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT133DETEN_MASK                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT133DETEN_SHIFT                         (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT133DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT134DETEN_MASK                          (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT134DETEN_SHIFT                         (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT134DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT135DETEN_MASK                          (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT135DETEN_SHIFT                         (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT135DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT136DETEN_MASK                          (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT136DETEN_SHIFT                         (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT136DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT137DETEN_MASK                          (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT137DETEN_SHIFT                         (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT137DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT138DETEN_MASK                          (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT138DETEN_SHIFT                         (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT138DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT139DETEN_MASK                          (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT139DETEN_SHIFT                         (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT139DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT140DETEN_MASK                          (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT140DETEN_SHIFT                         (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT140DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT141DETEN_MASK                          (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT141DETEN_SHIFT                         (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT141DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT142DETEN_MASK                          (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT142DETEN_SHIFT                         (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT142DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT143DETEN_MASK                          (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT143DETEN_SHIFT                         (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT143DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT144DETEN_MASK                          (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT144DETEN_SHIFT                         (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT144DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT145DETEN_MASK                          (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT145DETEN_SHIFT                         (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT145DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT1468DETEN_MASK                         (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT1468DETEN_SHIFT                        (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT1468DETEN_MAX                          (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT147DETEN_MASK                          (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT147DETEN_SHIFT                         (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT147DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT148DETEN_MASK                          (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT148DETEN_SHIFT                         (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT148DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT149DETEN_MASK                          (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT149DETEN_SHIFT                         (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT149DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT150DETEN_MASK                          (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT150DETEN_SHIFT                         (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT150DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT151DETEN_MASK                          (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT151DETEN_SHIFT                         (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT151DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT152DETEN_MASK                          (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT152DETEN_SHIFT                         (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT152DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT153DETEN_MASK                          (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT153DETEN_SHIFT                         (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT153DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT154DETEN_MASK                          (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT154DETEN_SHIFT                         (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT154DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT155DETEN_MASK                          (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT155DETEN_SHIFT                         (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT155DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT156DETEN_MASK                          (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT156DETEN_SHIFT                         (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT156DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT157DETEN_MASK                          (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT157DETEN_SHIFT                         (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT157DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT158DETEN_MASK                          (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT158DETEN_SHIFT                         (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT158DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT159DETEN_MASK                          (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT159DETEN_SHIFT                         (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT159DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT160DETEN_MASK                          (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT160DETEN_SHIFT                         (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL5_EVENT160DETEN_MAX                           (0x00000001U)

/* SETEVTENBL6 */

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT161DETEN_MASK                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT161DETEN_SHIFT                         (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT161DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT162DETEN_MASK                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT162DETEN_SHIFT                         (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT162DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT163DETEN_MASK                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT163DETEN_SHIFT                         (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT163DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT164DETEN_MASK                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT164DETEN_SHIFT                         (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT164DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT165DETEN_MASK                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT165DETEN_SHIFT                         (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT165DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT166DETEN_MASK                          (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT166DETEN_SHIFT                         (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT166DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT167DETEN_MASK                          (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT167DETEN_SHIFT                         (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT167DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT168DETEN_MASK                          (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT168DETEN_SHIFT                         (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT168DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT169DETEN_MASK                          (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT169DETEN_SHIFT                         (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT169DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT170DETEN_MASK                          (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT170DETEN_SHIFT                         (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT170DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT171DETEN_MASK                          (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT171DETEN_SHIFT                         (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT171DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT172DETEN_MASK                          (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT172DETEN_SHIFT                         (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT172DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT173DETEN_MASK                          (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT173DETEN_SHIFT                         (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT173DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT174DETEN_MASK                          (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT174DETEN_SHIFT                         (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT174DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT175DETEN_MASK                          (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT175DETEN_SHIFT                         (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT175DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT176DETEN_MASK                          (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT176DETEN_SHIFT                         (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT176DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT177DETEN_MASK                          (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT177DETEN_SHIFT                         (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT177DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT178DETEN_MASK                          (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT178DETEN_SHIFT                         (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT178DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT179DETEN_MASK                          (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT179DETEN_SHIFT                         (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT179DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT180DETEN_MASK                          (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT180DETEN_SHIFT                         (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT180DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT181DETEN_MASK                          (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT181DETEN_SHIFT                         (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT181DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT182DETEN_MASK                          (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT182DETEN_SHIFT                         (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT182DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT183DETEN_MASK                          (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT183DETEN_SHIFT                         (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT183DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT184DETEN_MASK                          (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT184DETEN_SHIFT                         (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT184DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT185DETEN_MASK                          (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT185DETEN_SHIFT                         (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT185DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT186DETEN_MASK                          (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT186DETEN_SHIFT                         (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT186DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT187DETEN_MASK                          (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT187DETEN_SHIFT                         (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT187DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT188DETEN_MASK                          (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT188DETEN_SHIFT                         (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT188DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT189DETEN_MASK                          (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT189DETEN_SHIFT                         (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT189DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT190DETEN_MASK                          (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT190DETEN_SHIFT                         (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT190DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT191DETEN_MASK                          (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT191DETEN_SHIFT                         (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT191DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT192DETEN_MASK                          (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT192DETEN_SHIFT                         (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL6_EVENT192DETEN_MAX                           (0x00000001U)

/* SETEVTENBL7 */

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT193DETEN_MASK                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT193DETEN_SHIFT                         (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT193DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT194DETEN_MASK                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT194DETEN_SHIFT                         (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT194DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT195DETEN_MASK                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT195DETEN_SHIFT                         (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT195DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT196DETEN_MASK                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT196DETEN_SHIFT                         (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT196DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT197DETEN_MASK                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT197DETEN_SHIFT                         (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT197DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT198DETEN_MASK                          (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT198DETEN_SHIFT                         (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT198DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT199DETEN_MASK                          (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT199DETEN_SHIFT                         (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT199DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT200DETEN_MASK                          (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT200DETEN_SHIFT                         (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT200DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT201DETEN_MASK                          (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT201DETEN_SHIFT                         (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT201DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT202DETEN_MASK                          (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT202DETEN_SHIFT                         (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT202DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT203DETEN_MASK                          (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT203DETEN_SHIFT                         (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT203DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT204DETEN_MASK                          (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT204DETEN_SHIFT                         (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT204DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT205DETEN_MASK                          (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT205DETEN_SHIFT                         (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT205DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT206DETEN_MASK                          (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT206DETEN_SHIFT                         (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT206DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT207DETEN_MASK                          (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT207DETEN_SHIFT                         (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT207DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT208DETEN_MASK                          (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT208DETEN_SHIFT                         (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT208DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT209DETEN_MASK                          (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT209DETEN_SHIFT                         (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT209DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT210DETEN_MASK                          (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT210DETEN_SHIFT                         (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT210DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT211DETEN_MASK                          (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT211DETEN_SHIFT                         (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT211DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT212DETEN_MASK                          (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT212DETEN_SHIFT                         (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT212DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT213DETEN_MASK                          (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT213DETEN_SHIFT                         (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT213DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT214DETEN_MASK                          (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT214DETEN_SHIFT                         (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT214DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT215DETEN_MASK                          (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT215DETEN_SHIFT                         (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT215DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT216DETEN_MASK                          (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT216DETEN_SHIFT                         (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT216DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT217DETEN_MASK                          (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT217DETEN_SHIFT                         (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT217DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT218DETEN_MASK                          (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT218DETEN_SHIFT                         (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT218DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT219DETEN_MASK                          (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT219DETEN_SHIFT                         (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT219DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT220DETEN_MASK                          (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT220DETEN_SHIFT                         (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT220DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT221DETEN_MASK                          (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT221DETEN_SHIFT                         (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT221DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT222DETEN_MASK                          (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT222DETEN_SHIFT                         (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT222DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT223DETEN_MASK                          (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT223DETEN_SHIFT                         (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT223DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT224DETEN_MASK                          (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT224DETEN_SHIFT                         (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL7_EVENT224DETEN_MAX                           (0x00000001U)

/* SETEVTENBL8 */

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT225DETEN_MASK                          (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT225DETEN_SHIFT                         (0x00000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT225DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT226DETEN_MASK                          (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT226DETEN_SHIFT                         (0x00000001U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT226DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT227DETEN_MASK                          (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT227DETEN_SHIFT                         (0x00000002U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT227DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT228DETEN_MASK                          (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT228DETEN_SHIFT                         (0x00000003U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT228DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT229DETEN_MASK                          (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT229DETEN_SHIFT                         (0x00000004U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT229DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT230DETEN_MASK                          (0x00000020U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT230DETEN_SHIFT                         (0x00000005U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT230DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT231DETEN_MASK                          (0x00000040U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT231DETEN_SHIFT                         (0x00000006U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT231DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT232DETEN_MASK                          (0x00000080U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT232DETEN_SHIFT                         (0x00000007U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT232DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT233DETEN_MASK                          (0x00000100U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT233DETEN_SHIFT                         (0x00000008U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT233DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT234DETEN_MASK                          (0x00000200U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT234DETEN_SHIFT                         (0x00000009U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT234DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT235DETEN_MASK                          (0x00000400U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT235DETEN_SHIFT                         (0x0000000AU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT235DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT236DETEN_MASK                          (0x00000800U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT236DETEN_SHIFT                         (0x0000000BU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT236DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT237DETEN_MASK                          (0x00001000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT237DETEN_SHIFT                         (0x0000000CU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT237DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT238DETEN_MASK                          (0x00002000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT238DETEN_SHIFT                         (0x0000000DU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT238DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT239DETEN_MASK                          (0x00004000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT239DETEN_SHIFT                         (0x0000000EU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT239DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT240DETEN_MASK                          (0x00008000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT240DETEN_SHIFT                         (0x0000000FU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT240DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT241DETEN_MASK                          (0x00010000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT241DETEN_SHIFT                         (0x00000010U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT241DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT242DETEN_MASK                          (0x00020000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT242DETEN_SHIFT                         (0x00000011U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT242DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT243DETEN_MASK                          (0x00040000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT243DETEN_SHIFT                         (0x00000012U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT243DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT244DETEN_MASK                          (0x00080000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT244DETEN_SHIFT                         (0x00000013U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT244DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT245DETEN_MASK                          (0x00100000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT245DETEN_SHIFT                         (0x00000014U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT245DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT246DETEN_MASK                          (0x00200000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT246DETEN_SHIFT                         (0x00000015U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT246DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT247DETEN_MASK                          (0x00400000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT247DETEN_SHIFT                         (0x00000016U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT247DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT248DETEN_MASK                          (0x00800000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT248DETEN_SHIFT                         (0x00000017U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT248DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT249DETEN_MASK                          (0x01000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT249DETEN_SHIFT                         (0x00000018U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT249DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT250DETEN_MASK                          (0x02000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT250DETEN_SHIFT                         (0x00000019U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT250DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT251DETEN_MASK                          (0x04000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT251DETEN_SHIFT                         (0x0000001AU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT251DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT252DETEN_MASK                          (0x08000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT252DETEN_SHIFT                         (0x0000001BU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT252DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT253DETEN_MASK                          (0x10000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT253DETEN_SHIFT                         (0x0000001CU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT253DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT254DETEN_MASK                          (0x20000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT254DETEN_SHIFT                         (0x0000001DU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT254DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT255DETEN_MASK                          (0x40000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT255DETEN_SHIFT                         (0x0000001EU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT255DETEN_MAX                           (0x00000001U)

#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT256DETEN_MASK                          (0x80000000U)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT256DETEN_SHIFT                         (0x0000001FU)
#define CSL_CTSET2_CFG_SETEVTENBL8_EVENT256DETEN_MAX                           (0x00000001U)

/* SETMSTID */

#define CSL_CTSET2_CFG_SETMSTID_MASTID_MASK                                    (0x000000FFU)
#define CSL_CTSET2_CFG_SETMSTID_MASTID_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_SETMSTID_MASTID_MAX                                     (0x000000FFU)

#define CSL_CTSET2_CFG_SETMSTID_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_SETMSTID_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_SETMSTID_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTCNTL */

#define CSL_CTSET2_CFG_CTCNTL_NUMCOREMD_MASK                                   (0x00000001U)
#define CSL_CTSET2_CFG_CTCNTL_NUMCOREMD_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTL_NUMCOREMD_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTCNTL_RESERVED_MASK                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTCNTL_RESERVED_SHIFT                                   (0x00000001U)
#define CSL_CTSET2_CFG_CTCNTL_RESERVED_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTCNTL_REVID_MASK                                       (0x00000078U)
#define CSL_CTSET2_CFG_CTCNTL_REVID_SHIFT                                      (0x00000003U)
#define CSL_CTSET2_CFG_CTCNTL_REVID_MAX                                        (0x0000000FU)

#define CSL_CTSET2_CFG_CTCNTL_NUMCNTR_MASK                                     (0x00001F80U)
#define CSL_CTSET2_CFG_CTCNTL_NUMCNTR_SHIFT                                    (0x00000007U)
#define CSL_CTSET2_CFG_CTCNTL_NUMCNTR_MAX                                      (0x0000003FU)

#define CSL_CTSET2_CFG_CTCNTL_NUMTIMR_MASK                                     (0x0003E000U)
#define CSL_CTSET2_CFG_CTCNTL_NUMTIMR_SHIFT                                    (0x0000000DU)
#define CSL_CTSET2_CFG_CTCNTL_NUMTIMR_MAX                                      (0x0000001FU)

#define CSL_CTSET2_CFG_CTCNTL_NUMINPT_MASK                                     (0x03FC0000U)
#define CSL_CTSET2_CFG_CTCNTL_NUMINPT_SHIFT                                    (0x00000012U)
#define CSL_CTSET2_CFG_CTCNTL_NUMINPT_MAX                                      (0x000000FFU)

#define CSL_CTSET2_CFG_CTCNTL_NUMSTM_MASK                                      (0xFC000000U)
#define CSL_CTSET2_CFG_CTCNTL_NUMSTM_SHIFT                                     (0x0000001AU)
#define CSL_CTSET2_CFG_CTCNTL_NUMSTM_MAX                                       (0x0000003FU)

/* CTNUMDBG */

#define CSL_CTSET2_CFG_CTNUMDBG_NUMEVT_MASK                                    (0x00000007U)
#define CSL_CTSET2_CFG_CTNUMDBG_NUMEVT_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTNUMDBG_NUMEVT_MAX                                     (0x00000007U)

#define CSL_CTSET2_CFG_CTNUMDBG_RESERVED_MASK                                  (0xFFFFFFF0U)
#define CSL_CTSET2_CFG_CTNUMDBG_RESERVED_SHIFT                                 (0x00000004U)
#define CSL_CTSET2_CFG_CTNUMDBG_RESERVED_MAX                                   (0x0FFFFFFFU)

/* CTUSERACCCTL */

#define CSL_CTSET2_CFG_CTUSERACCCTL_NRUSER_MASK                                (0x00000001U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_NRUSER_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_NRUSER_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTUSERACCCTL_RUSER_MASK                                 (0x00000002U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_RUSER_SHIFT                                (0x00000001U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_RUSER_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTUSERACCCTL_SECUSER_MASK                               (0x00000004U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_SECUSER_SHIFT                              (0x00000002U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_SECUSER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTUSERACCCTL_RESERVED_MASK                              (0xFFFFFFF8U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_RESERVED_SHIFT                             (0x00000003U)
#define CSL_CTSET2_CFG_CTUSERACCCTL_RESERVED_MAX                               (0x1FFFFFFFU)

/* CTSTMCNTL */

#define CSL_CTSET2_CFG_CTSTMCNTL_ENBL_MASK                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTSTMCNTL_ENBL_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTSTMCNTL_ENBL_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_SENDOVR_MASK                                  (0x00000002U)
#define CSL_CTSET2_CFG_CTSTMCNTL_SENDOVR_SHIFT                                 (0x00000001U)
#define CSL_CTSET2_CFG_CTSTMCNTL_SENDOVR_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_CSMXPORT_MASK                                 (0x00000004U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CSMXPORT_SHIFT                                (0x00000002U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CSMXPORT_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_CCMAVAIL_MASK                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CCMAVAIL_SHIFT                                (0x00000003U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CCMAVAIL_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_CCMPORT_MASK                                  (0x00000010U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CCMPORT_SHIFT                                 (0x00000004U)
#define CSL_CTSET2_CFG_CTSTMCNTL_CCMPORT_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_XPORTACT_MASK                                 (0x00000020U)
#define CSL_CTSET2_CFG_CTSTMCNTL_XPORTACT_SHIFT                                (0x00000005U)
#define CSL_CTSET2_CFG_CTSTMCNTL_XPORTACT_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTSTMCNTL_NUMXPORT_MASK                                 (0x00000FC0U)
#define CSL_CTSET2_CFG_CTSTMCNTL_NUMXPORT_SHIFT                                (0x00000006U)
#define CSL_CTSET2_CFG_CTSTMCNTL_NUMXPORT_MAX                                  (0x0000003FU)

#define CSL_CTSET2_CFG_CTSTMCNTL_RESERVED_MASK                                 (0xFFFFF000U)
#define CSL_CTSET2_CFG_CTSTMCNTL_RESERVED_SHIFT                                (0x0000000CU)
#define CSL_CTSET2_CFG_CTSTMCNTL_RESERVED_MAX                                  (0x000FFFFFU)

/* CTSTMMSTID */

#define CSL_CTSET2_CFG_CTSTMMSTID_MASTID_MASK                                  (0x000000FFU)
#define CSL_CTSET2_CFG_CTSTMMSTID_MASTID_SHIFT                                 (0x00000000U)
#define CSL_CTSET2_CFG_CTSTMMSTID_MASTID_MAX                                   (0x000000FFU)

#define CSL_CTSET2_CFG_CTSTMMSTID_RESERVED_MASK                                (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTSTMMSTID_RESERVED_SHIFT                               (0x00000008U)
#define CSL_CTSET2_CFG_CTSTMMSTID_RESERVED_MAX                                 (0x00FFFFFFU)

/* CTSTMINTVL */

#define CSL_CTSET2_CFG_CTSTMINTVL_INTERVAL_MASK                                (0x00007FFFU)
#define CSL_CTSET2_CFG_CTSTMINTVL_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTSTMINTVL_INTERVAL_MAX                                 (0x00007FFFU)

#define CSL_CTSET2_CFG_CTSTMINTVL_RESERVED_MASK                                (0xFFFF0000U)
#define CSL_CTSET2_CFG_CTSTMINTVL_RESERVED_SHIFT                               (0x00000010U)
#define CSL_CTSET2_CFG_CTSTMINTVL_RESERVED_MAX                                 (0x0000FFFFU)

/* CTSTMSEL0 */

#define CSL_CTSET2_CFG_CTSTMSEL0_COUNTSEL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTSTMSEL0_COUNTSEL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTSTMSEL0_COUNTSEL_MAX                                  (0xFFFFFFFFU)

/* CTSTMSEL1 */

#define CSL_CTSET2_CFG_CTSTMSEL1_COUNTSEL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTSTMSEL1_COUNTSEL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTSTMSEL1_COUNTSEL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR0 */

#define CSL_CTSET2_CFG_CTINTVLR0_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR0_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR0_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR1 */

#define CSL_CTSET2_CFG_CTINTVLR1_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR1_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR1_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR2 */

#define CSL_CTSET2_CFG_CTINTVLR2_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR2_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR2_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR3 */

#define CSL_CTSET2_CFG_CTINTVLR3_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR3_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR3_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR4 */

#define CSL_CTSET2_CFG_CTINTVLR4_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR4_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR4_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR5 */

#define CSL_CTSET2_CFG_CTINTVLR5_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR5_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR5_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR6 */

#define CSL_CTSET2_CFG_CTINTVLR6_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR6_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR6_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR7 */

#define CSL_CTSET2_CFG_CTINTVLR7_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR7_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR7_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR8 */

#define CSL_CTSET2_CFG_CTINTVLR8_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR8_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR8_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR9 */

#define CSL_CTSET2_CFG_CTINTVLR9_INTERVAL_MASK                                 (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR9_INTERVAL_SHIFT                                (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR9_INTERVAL_MAX                                  (0xFFFFFFFFU)

/* CTINTVLR10 */

#define CSL_CTSET2_CFG_CTINTVLR10_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR10_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR10_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTINTVLR11 */

#define CSL_CTSET2_CFG_CTINTVLR11_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR11_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR11_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTINTVLR12 */

#define CSL_CTSET2_CFG_CTINTVLR12_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR12_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR12_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTINTVLR13 */

#define CSL_CTSET2_CFG_CTINTVLR13_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR13_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR13_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTINTVLR14 */

#define CSL_CTSET2_CFG_CTINTVLR14_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR14_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR14_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTINTVLR15 */

#define CSL_CTSET2_CFG_CTINTVLR15_INTERVAL_MASK                                (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTINTVLR15_INTERVAL_SHIFT                               (0x00000000U)
#define CSL_CTSET2_CFG_CTINTVLR15_INTERVAL_MAX                                 (0xFFFFFFFFU)

/* CTDBGSGL0 */

#define CSL_CTSET2_CFG_CTDBGSGL0_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL0_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL0_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL0_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL0_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL0_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL1 */

#define CSL_CTSET2_CFG_CTDBGSGL1_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL1_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL1_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL1_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL1_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL1_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL2 */

#define CSL_CTSET2_CFG_CTDBGSGL2_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL2_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL2_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL2_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL2_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL2_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL3 */

#define CSL_CTSET2_CFG_CTDBGSGL3_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL3_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL3_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL3_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL3_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL3_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL4 */

#define CSL_CTSET2_CFG_CTDBGSGL4_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL4_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL4_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL4_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL4_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL4_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL5 */

#define CSL_CTSET2_CFG_CTDBGSGL5_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL5_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL5_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL5_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL5_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL5_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL6 */

#define CSL_CTSET2_CFG_CTDBGSGL6_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL6_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL6_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL6_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL6_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL6_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTDBGSGL7 */

#define CSL_CTSET2_CFG_CTDBGSGL7_INPSEL_MASK                                   (0x000000FFU)
#define CSL_CTSET2_CFG_CTDBGSGL7_INPSEL_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTDBGSGL7_INPSEL_MAX                                    (0x000000FFU)

#define CSL_CTSET2_CFG_CTDBGSGL7_RESERVED_MASK                                 (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTDBGSGL7_RESERVED_SHIFT                                (0x00000008U)
#define CSL_CTSET2_CFG_CTDBGSGL7_RESERVED_MAX                                  (0x00FFFFFFU)

/* CTGNBL0 */

#define CSL_CTSET2_CFG_CTGNBL0_ENABLE_MASK                                     (0x000000FFU)
#define CSL_CTSET2_CFG_CTGNBL0_ENABLE_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTGNBL0_ENABLE_MAX                                      (0x000000FFU)

/* CTGNBL1 */

#define CSL_CTSET2_CFG_CTGNBL1_ENABLE_MASK                                     (0x000000FFU)
#define CSL_CTSET2_CFG_CTGNBL1_ENABLE_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTGNBL1_ENABLE_MAX                                      (0x000000FFU)

/* CTGRST0 */

#define CSL_CTSET2_CFG_CTGRST0_RESET_MASK                                      (0x000000FFU)
#define CSL_CTSET2_CFG_CTGRST0_RESET_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTGRST0_RESET_MAX                                       (0x000000FFU)

/* CTGRST1 */

#define CSL_CTSET2_CFG_CTGRST1_RESET_MASK                                      (0x000000FFU)
#define CSL_CTSET2_CFG_CTGRST1_RESET_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTGRST1_RESET_MAX                                       (0x000000FFU)

/* CTCR0 */

#define CSL_CTSET2_CFG_CTCR0_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR0_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR0_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR0_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR0_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR0_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR0_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR0_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR0_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR0_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR0_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR0_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR0_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR0_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR0_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR0_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR0_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR0_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR0_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR0_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR0_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR0_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR0_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR0_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR0_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR0_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR0_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR0_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR0_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR0_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR0_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR0_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR0_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR0_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR0_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR0_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR0_WDRESET_MAX                                       (0x000000FFU)

/* CTCR1 */

#define CSL_CTSET2_CFG_CTCR1_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR1_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR1_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR1_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR1_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR1_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR1_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR1_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR1_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR1_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR1_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR1_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR1_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR1_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR1_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR1_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR1_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR1_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR1_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR1_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR1_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR1_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR1_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR1_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR1_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR1_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR1_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR1_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR1_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR1_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR1_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR1_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR1_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR1_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR1_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR1_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR1_WDRESET_MAX                                       (0x000000FFU)

/* CTCR2 */

#define CSL_CTSET2_CFG_CTCR2_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR2_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR2_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR2_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR2_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR2_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR2_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR2_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR2_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR2_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR2_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR2_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR2_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR2_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR2_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR2_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR2_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR2_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR2_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR2_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR2_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR2_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR2_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR2_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR2_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR2_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR2_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR2_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR2_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR2_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR2_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR2_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR2_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR2_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR2_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR2_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR2_WDRESET_MAX                                       (0x000000FFU)

/* CTCR3 */

#define CSL_CTSET2_CFG_CTCR3_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR3_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR3_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR3_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR3_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR3_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR3_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR3_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR3_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR3_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR3_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR3_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR3_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR3_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR3_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR3_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR3_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR3_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR3_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR3_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR3_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR3_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR3_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR3_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR3_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR3_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR3_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR3_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR3_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR3_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR3_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR3_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR3_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR3_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR3_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR3_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR3_WDRESET_MAX                                       (0x000000FFU)

/* CTCR4 */

#define CSL_CTSET2_CFG_CTCR4_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR4_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR4_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR4_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR4_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR4_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR4_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR4_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR4_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR4_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR4_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR4_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR4_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR4_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR4_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR4_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR4_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR4_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR4_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR4_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR4_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR4_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR4_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR4_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR4_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR4_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR4_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR4_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR4_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR4_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR4_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR4_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR4_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR4_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR4_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR4_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR4_WDRESET_MAX                                       (0x000000FFU)

/* CTCR5 */

#define CSL_CTSET2_CFG_CTCR5_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR5_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR5_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR5_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR5_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR5_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR5_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR5_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR5_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR5_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR5_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR5_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR5_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR5_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR5_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR5_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR5_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR5_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR5_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR5_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR5_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR5_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR5_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR5_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR5_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR5_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR5_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR5_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR5_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR5_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR5_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR5_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR5_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR5_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR5_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR5_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR5_WDRESET_MAX                                       (0x000000FFU)

/* CTCR6 */

#define CSL_CTSET2_CFG_CTCR6_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR6_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR6_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR6_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR6_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR6_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR6_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR6_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR6_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR6_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR6_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR6_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR6_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR6_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR6_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR6_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR6_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR6_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR6_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR6_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR6_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR6_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR6_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR6_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR6_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR6_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR6_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR6_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR6_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR6_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR6_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR6_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR6_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR6_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR6_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR6_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR6_WDRESET_MAX                                       (0x000000FFU)

/* CTCR7 */

#define CSL_CTSET2_CFG_CTCR7_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR7_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR7_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR7_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR7_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR7_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR7_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR7_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR7_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR7_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR7_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR7_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR7_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR7_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR7_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR7_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR7_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR7_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR7_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR7_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR7_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR7_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR7_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR7_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR7_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR7_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR7_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR7_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR7_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR7_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR7_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR7_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR7_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR7_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR7_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR7_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR7_WDRESET_MAX                                       (0x000000FFU)

/* CTCR8 */

#define CSL_CTSET2_CFG_CTCR8_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR8_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR8_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR8_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR8_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR8_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR8_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR8_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR8_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR8_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR8_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR8_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR8_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR8_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR8_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR8_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR8_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR8_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR8_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR8_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR8_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR8_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR8_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR8_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR8_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR8_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR8_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR8_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR8_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR8_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR8_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR8_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR8_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR8_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR8_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR8_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR8_WDRESET_MAX                                       (0x000000FFU)

/* CTCR9 */

#define CSL_CTSET2_CFG_CTCR9_ENBL_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CTCR9_ENBL_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CTCR9_ENBL_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_RESET_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_CTCR9_RESET_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTCR9_RESET_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_CHAIN_MASK                                        (0x00000004U)
#define CSL_CTSET2_CFG_CTCR9_CHAIN_SHIFT                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR9_CHAIN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_DURMODE_MASK                                      (0x00000008U)
#define CSL_CTSET2_CFG_CTCR9_DURMODE_SHIFT                                     (0x00000003U)
#define CSL_CTSET2_CFG_CTCR9_DURMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_RESERVED_MASK                                     (0x00000030U)
#define CSL_CTSET2_CFG_CTCR9_RESERVED_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTCR9_RESERVED_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR9_OVRFLW_MASK                                       (0x00000040U)
#define CSL_CTSET2_CFG_CTCR9_OVRFLW_SHIFT                                      (0x00000006U)
#define CSL_CTSET2_CFG_CTCR9_OVRFLW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_CHNSDW_MASK                                       (0x00000080U)
#define CSL_CTSET2_CFG_CTCR9_CHNSDW_SHIFT                                      (0x00000007U)
#define CSL_CTSET2_CFG_CTCR9_CHNSDW_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_INT_MASK                                          (0x00000100U)
#define CSL_CTSET2_CFG_CTCR9_INT_SHIFT                                         (0x00000008U)
#define CSL_CTSET2_CFG_CTCR9_INT_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_DBG_MASK                                          (0x00000200U)
#define CSL_CTSET2_CFG_CTCR9_DBG_SHIFT                                         (0x00000009U)
#define CSL_CTSET2_CFG_CTCR9_DBG_MAX                                           (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_RESTART_MASK                                      (0x00000400U)
#define CSL_CTSET2_CFG_CTCR9_RESTART_SHIFT                                     (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR9_RESTART_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_WDMODE_MASK                                       (0x00000800U)
#define CSL_CTSET2_CFG_CTCR9_WDMODE_SHIFT                                      (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR9_WDMODE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_DBG_TRIG_STAT_MASK                                (0x00001000U)
#define CSL_CTSET2_CFG_CTCR9_DBG_TRIG_STAT_SHIFT                               (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR9_DBG_TRIG_STAT_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_FILTER_MASK                                       (0x00002000U)
#define CSL_CTSET2_CFG_CTCR9_FILTER_SHIFT                                      (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR9_FILTER_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR9_MODESEL_MASK                                      (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR9_MODESEL_SHIFT                                     (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR9_MODESEL_MAX                                       (0x00000003U)

#define CSL_CTSET2_CFG_CTCR9_INPSEL_MASK                                       (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR9_INPSEL_SHIFT                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTCR9_INPSEL_MAX                                        (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR9_WDRESET_MASK                                      (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR9_WDRESET_SHIFT                                     (0x00000018U)
#define CSL_CTSET2_CFG_CTCR9_WDRESET_MAX                                       (0x000000FFU)

/* CTCR10 */

#define CSL_CTSET2_CFG_CTCR10_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR10_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR10_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR10_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR10_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR10_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR10_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR10_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR10_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR10_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR10_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR10_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR10_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR10_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR10_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR10_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR10_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR10_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR10_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR10_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR10_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR10_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR10_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR10_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR10_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR10_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR10_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR10_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR10_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR10_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR10_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR10_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR10_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR10_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR10_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR10_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR10_WDRESET_MAX                                      (0x000000FFU)

/* CTCR11 */

#define CSL_CTSET2_CFG_CTCR11_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR11_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR11_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR11_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR11_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR11_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR11_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR11_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR11_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR11_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR11_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR11_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR11_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR11_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR11_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR11_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR11_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR11_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR11_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR11_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR11_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR11_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR11_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR11_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR11_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR11_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR11_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR11_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR11_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR11_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR11_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR11_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR11_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR11_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR11_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR11_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR11_WDRESET_MAX                                      (0x000000FFU)

/* CTCR12 */

#define CSL_CTSET2_CFG_CTCR12_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR12_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR12_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR12_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR12_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR12_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR12_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR12_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR12_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR12_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR12_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR12_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR12_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR12_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR12_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR12_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR12_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR12_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR12_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR12_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR12_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR12_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR12_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR12_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR12_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR12_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR12_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR12_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR12_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR12_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR12_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR12_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR12_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR12_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR12_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR12_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR12_WDRESET_MAX                                      (0x000000FFU)

/* CTCR13 */

#define CSL_CTSET2_CFG_CTCR13_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR13_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR13_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR13_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR13_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR13_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR13_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR13_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR13_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR13_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR13_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR13_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR13_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR13_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR13_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR13_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR13_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR13_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR13_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR13_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR13_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR13_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR13_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR13_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR13_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR13_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR13_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR13_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR13_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR13_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR13_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR13_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR13_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR13_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR13_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR13_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR13_WDRESET_MAX                                      (0x000000FFU)

/* CTCR14 */

#define CSL_CTSET2_CFG_CTCR14_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR14_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR14_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR14_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR14_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR14_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR14_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR14_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR14_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR14_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR14_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR14_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR14_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR14_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR14_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR14_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR14_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR14_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR14_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR14_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR14_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR14_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR14_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR14_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR14_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR14_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR14_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR14_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR14_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR14_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR14_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR14_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR14_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR14_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR14_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR14_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR14_WDRESET_MAX                                      (0x000000FFU)

/* CTCR15 */

#define CSL_CTSET2_CFG_CTCR15_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR15_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR15_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR15_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR15_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR15_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR15_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR15_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR15_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR15_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR15_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR15_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR15_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR15_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR15_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR15_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR15_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR15_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR15_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR15_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR15_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR15_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR15_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR15_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR15_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR15_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR15_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR15_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR15_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR15_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR15_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR15_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR15_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR15_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR15_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR15_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR15_WDRESET_MAX                                      (0x000000FFU)

/* CTCR16 */

#define CSL_CTSET2_CFG_CTCR16_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR16_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR16_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR16_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR16_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR16_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR16_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR16_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR16_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR16_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR16_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR16_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR16_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR16_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR16_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR16_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR16_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR16_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR16_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR16_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR16_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR16_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR16_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR16_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR16_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR16_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR16_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR16_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR16_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR16_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR16_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR16_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR16_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR16_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR16_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR16_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR16_WDRESET_MAX                                      (0x000000FFU)

/* CTCR17 */

#define CSL_CTSET2_CFG_CTCR17_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR17_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR17_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR17_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR17_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR17_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR17_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR17_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR17_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR17_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR17_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR17_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR17_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR17_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR17_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR17_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR17_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR17_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR17_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR17_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR17_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR17_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR17_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR17_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR17_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR17_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR17_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR17_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR17_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR17_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR17_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR17_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR17_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR17_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR17_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR17_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR17_WDRESET_MAX                                      (0x000000FFU)

/* CTCR18 */

#define CSL_CTSET2_CFG_CTCR18_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR18_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR18_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR18_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR18_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR18_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR18_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR18_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR18_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR18_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR18_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR18_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR18_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR18_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR18_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR18_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR18_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR18_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR18_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR18_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR18_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR18_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR18_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR18_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR18_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR18_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR18_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR18_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR18_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR18_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR18_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR18_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR18_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR18_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR18_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR18_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR18_WDRESET_MAX                                      (0x000000FFU)

/* CTCR19 */

#define CSL_CTSET2_CFG_CTCR19_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR19_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR19_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR19_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR19_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR19_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR19_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR19_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR19_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR19_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR19_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR19_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR19_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR19_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR19_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR19_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR19_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR19_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR19_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR19_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR19_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR19_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR19_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR19_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR19_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR19_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR19_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR19_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR19_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR19_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR19_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR19_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR19_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR19_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR19_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR19_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR19_WDRESET_MAX                                      (0x000000FFU)

/* CTCR20 */

#define CSL_CTSET2_CFG_CTCR20_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR20_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR20_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR20_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR20_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR20_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR20_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR20_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR20_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR20_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR20_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR20_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR20_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR20_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR20_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR20_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR20_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR20_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR20_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR20_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR20_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR20_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR20_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR20_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR20_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR20_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR20_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR20_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR20_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR20_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR20_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR20_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR20_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR20_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR20_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR20_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR20_WDRESET_MAX                                      (0x000000FFU)

/* CTCR21 */

#define CSL_CTSET2_CFG_CTCR21_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR21_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR21_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR21_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR21_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR21_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR21_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR21_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR21_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR21_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR21_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR21_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR21_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR21_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR21_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR21_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR21_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR21_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR21_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR21_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR21_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR21_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR21_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR21_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR21_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR21_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR21_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR21_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR21_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR21_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR21_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR21_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR21_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR21_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR21_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR21_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR21_WDRESET_MAX                                      (0x000000FFU)

/* CTCR22 */

#define CSL_CTSET2_CFG_CTCR22_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR22_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR22_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR22_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR22_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR22_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR22_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR22_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR22_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR22_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR22_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR22_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR22_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR22_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR22_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR22_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR22_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR22_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR22_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR22_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR22_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR22_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR22_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR22_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR22_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR22_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR22_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR22_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR22_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR22_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR22_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR22_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR22_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR22_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR22_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR22_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR22_WDRESET_MAX                                      (0x000000FFU)

/* CTCR23 */

#define CSL_CTSET2_CFG_CTCR23_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR23_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR23_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR23_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR23_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR23_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR23_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR23_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR23_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR23_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR23_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR23_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR23_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR23_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR23_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR23_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR23_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR23_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR23_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR23_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR23_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR23_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR23_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR23_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR23_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR23_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR23_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR23_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR23_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR23_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR23_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR23_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR23_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR23_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR23_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR23_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR23_WDRESET_MAX                                      (0x000000FFU)

/* CTCR24 */

#define CSL_CTSET2_CFG_CTCR24_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR24_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR24_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR24_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR24_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR24_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR24_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR24_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR24_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR24_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR24_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR24_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR24_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR24_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR24_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR24_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR24_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR24_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR24_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR24_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR24_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR24_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR24_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR24_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR24_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR24_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR24_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR24_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR24_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR24_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR24_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR24_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR24_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR24_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR24_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR24_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR24_WDRESET_MAX                                      (0x000000FFU)

/* CTCR25 */

#define CSL_CTSET2_CFG_CTCR25_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR25_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR25_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR25_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR25_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR25_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR25_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR25_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR25_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR25_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR25_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR25_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR25_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR25_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR25_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR25_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR25_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR25_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR25_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR25_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR25_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR25_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR25_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR25_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR25_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR25_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR25_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR25_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR25_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR25_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR25_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR25_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR25_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR25_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR25_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR25_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR25_WDRESET_MAX                                      (0x000000FFU)

/* CTCR26 */

#define CSL_CTSET2_CFG_CTCR26_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR26_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR26_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR26_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR26_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR26_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR26_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR26_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR26_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR26_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR26_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR26_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR26_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR26_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR26_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR26_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR26_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR26_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR26_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR26_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR26_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR26_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR26_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR26_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR26_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR26_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR26_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR26_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR26_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR26_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR26_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR26_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR26_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR26_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR26_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR26_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR26_WDRESET_MAX                                      (0x000000FFU)

/* CTCR27 */

#define CSL_CTSET2_CFG_CTCR27_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR27_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR27_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR27_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR27_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR27_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR27_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR27_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR27_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR27_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR27_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR27_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR27_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR27_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR27_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR27_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR27_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR27_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR27_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR27_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR27_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR27_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR27_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR27_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR27_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR27_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR27_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR27_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR27_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR27_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR27_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR27_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR27_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR27_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR27_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR27_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR27_WDRESET_MAX                                      (0x000000FFU)

/* CTCR28 */

#define CSL_CTSET2_CFG_CTCR28_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR28_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR28_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR28_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR28_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR28_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR28_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR28_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR28_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR28_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR28_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR28_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR28_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR28_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR28_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR28_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR28_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR28_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR28_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR28_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR28_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR28_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR28_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR28_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR28_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR28_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR28_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR28_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR28_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR28_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR28_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR28_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR28_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR28_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR28_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR28_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR28_WDRESET_MAX                                      (0x000000FFU)

/* CTCR29 */

#define CSL_CTSET2_CFG_CTCR29_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR29_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR29_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR29_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR29_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR29_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR29_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR29_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR29_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR29_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR29_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR29_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR29_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR29_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR29_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR29_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR29_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR29_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR29_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR29_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR29_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR29_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR29_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR29_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR29_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR29_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR29_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR29_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR29_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR29_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR29_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR29_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR29_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR29_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR29_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR29_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR29_WDRESET_MAX                                      (0x000000FFU)

/* CTCR30 */

#define CSL_CTSET2_CFG_CTCR30_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR30_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR30_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR30_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR30_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR30_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR30_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR30_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR30_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR30_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR30_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR30_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR30_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR30_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR30_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR30_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR30_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR30_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR30_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR30_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR30_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR30_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR30_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR30_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR30_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR30_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR30_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR30_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR30_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR30_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR30_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR30_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR30_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR30_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR30_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR30_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR30_WDRESET_MAX                                      (0x000000FFU)

/* CTCR31 */

#define CSL_CTSET2_CFG_CTCR31_ENBL_MASK                                        (0x00000001U)
#define CSL_CTSET2_CFG_CTCR31_ENBL_SHIFT                                       (0x00000000U)
#define CSL_CTSET2_CFG_CTCR31_ENBL_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_RESET_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTCR31_RESET_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTCR31_RESET_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_CHAIN_MASK                                       (0x00000004U)
#define CSL_CTSET2_CFG_CTCR31_CHAIN_SHIFT                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTCR31_CHAIN_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_DURMODE_MASK                                     (0x00000008U)
#define CSL_CTSET2_CFG_CTCR31_DURMODE_SHIFT                                    (0x00000003U)
#define CSL_CTSET2_CFG_CTCR31_DURMODE_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_RESERVED_MASK                                    (0x00000030U)
#define CSL_CTSET2_CFG_CTCR31_RESERVED_SHIFT                                   (0x00000004U)
#define CSL_CTSET2_CFG_CTCR31_RESERVED_MAX                                     (0x00000003U)

#define CSL_CTSET2_CFG_CTCR31_OVRFLW_MASK                                      (0x00000040U)
#define CSL_CTSET2_CFG_CTCR31_OVRFLW_SHIFT                                     (0x00000006U)
#define CSL_CTSET2_CFG_CTCR31_OVRFLW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_CHNSDW_MASK                                      (0x00000080U)
#define CSL_CTSET2_CFG_CTCR31_CHNSDW_SHIFT                                     (0x00000007U)
#define CSL_CTSET2_CFG_CTCR31_CHNSDW_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_INT_MASK                                         (0x00000100U)
#define CSL_CTSET2_CFG_CTCR31_INT_SHIFT                                        (0x00000008U)
#define CSL_CTSET2_CFG_CTCR31_INT_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_DBG_MASK                                         (0x00000200U)
#define CSL_CTSET2_CFG_CTCR31_DBG_SHIFT                                        (0x00000009U)
#define CSL_CTSET2_CFG_CTCR31_DBG_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_RESTART_MASK                                     (0x00000400U)
#define CSL_CTSET2_CFG_CTCR31_RESTART_SHIFT                                    (0x0000000AU)
#define CSL_CTSET2_CFG_CTCR31_RESTART_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_WDMODE_MASK                                      (0x00000800U)
#define CSL_CTSET2_CFG_CTCR31_WDMODE_SHIFT                                     (0x0000000BU)
#define CSL_CTSET2_CFG_CTCR31_WDMODE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_DBG_TRIG_STAT_MASK                               (0x00001000U)
#define CSL_CTSET2_CFG_CTCR31_DBG_TRIG_STAT_SHIFT                              (0x0000000CU)
#define CSL_CTSET2_CFG_CTCR31_DBG_TRIG_STAT_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_FILTER_MASK                                      (0x00002000U)
#define CSL_CTSET2_CFG_CTCR31_FILTER_SHIFT                                     (0x0000000DU)
#define CSL_CTSET2_CFG_CTCR31_FILTER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTCR31_MODESEL_MASK                                     (0x0000C000U)
#define CSL_CTSET2_CFG_CTCR31_MODESEL_SHIFT                                    (0x0000000EU)
#define CSL_CTSET2_CFG_CTCR31_MODESEL_MAX                                      (0x00000003U)

#define CSL_CTSET2_CFG_CTCR31_INPSEL_MASK                                      (0x00FF0000U)
#define CSL_CTSET2_CFG_CTCR31_INPSEL_SHIFT                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTCR31_INPSEL_MAX                                       (0x000000FFU)

#define CSL_CTSET2_CFG_CTCR31_WDRESET_MASK                                     (0xFF000000U)
#define CSL_CTSET2_CFG_CTCR31_WDRESET_SHIFT                                    (0x00000018U)
#define CSL_CTSET2_CFG_CTCR31_WDRESET_MAX                                      (0x000000FFU)

/* CTOWN0 */

#define CSL_CTSET2_CFG_CTOWN0_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN0_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN0_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN0_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN0_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN0_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN0_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN0_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN0_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN0_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN0_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN0_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN1 */

#define CSL_CTSET2_CFG_CTOWN1_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN1_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN1_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN1_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN1_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN1_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN1_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN1_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN1_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN1_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN1_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN1_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN2 */

#define CSL_CTSET2_CFG_CTOWN2_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN2_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN2_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN2_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN2_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN2_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN2_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN2_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN2_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN2_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN2_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN2_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN3 */

#define CSL_CTSET2_CFG_CTOWN3_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN3_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN3_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN3_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN3_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN3_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN3_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN3_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN3_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN3_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN3_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN3_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN4 */

#define CSL_CTSET2_CFG_CTOWN4_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN4_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN4_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN4_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN4_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN4_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN4_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN4_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN4_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN4_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN4_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN4_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN5 */

#define CSL_CTSET2_CFG_CTOWN5_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN5_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN5_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN5_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN5_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN5_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN5_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN5_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN5_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN5_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN5_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN5_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN6 */

#define CSL_CTSET2_CFG_CTOWN6_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN6_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN6_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN6_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN6_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN6_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN6_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN6_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN6_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN6_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN6_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN6_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN7 */

#define CSL_CTSET2_CFG_CTOWN7_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN7_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN7_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN7_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN7_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN7_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN7_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN7_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN7_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN7_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN7_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN7_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN8 */

#define CSL_CTSET2_CFG_CTOWN8_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN8_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN8_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN8_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN8_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN8_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN8_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN8_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN8_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN8_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN8_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN8_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN9 */

#define CSL_CTSET2_CFG_CTOWN9_RESERVED_MASK                                    (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN9_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN9_RESERVED_MAX                                     (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN9_CURRENT_OWNER_MASK                               (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN9_CURRENT_OWNER_SHIFT                              (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN9_CURRENT_OWNER_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN9_DBG_OVERIDE_MASK                                 (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN9_DBG_OVERIDE_SHIFT                                (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN9_DBG_OVERIDE_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN9_OWNERSHIP_MASK                                   (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN9_OWNERSHIP_SHIFT                                  (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN9_OWNERSHIP_MAX                                    (0x00000003U)

/* CTOWN10 */

#define CSL_CTSET2_CFG_CTOWN10_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN10_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN10_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN10_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN10_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN10_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN10_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN10_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN10_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN10_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN10_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN10_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN11 */

#define CSL_CTSET2_CFG_CTOWN11_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN11_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN11_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN11_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN11_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN11_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN11_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN11_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN11_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN11_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN11_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN11_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN12 */

#define CSL_CTSET2_CFG_CTOWN12_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN12_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN12_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN12_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN12_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN12_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN12_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN12_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN12_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN12_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN12_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN12_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN13 */

#define CSL_CTSET2_CFG_CTOWN13_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN13_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN13_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN13_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN13_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN13_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN13_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN13_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN13_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN13_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN13_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN13_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN14 */

#define CSL_CTSET2_CFG_CTOWN14_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN14_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN14_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN14_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN14_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN14_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN14_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN14_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN14_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN14_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN14_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN14_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN15 */

#define CSL_CTSET2_CFG_CTOWN15_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN15_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN15_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN15_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN15_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN15_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN15_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN15_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN15_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN15_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN15_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN15_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN16 */

#define CSL_CTSET2_CFG_CTOWN16_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN16_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN16_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN16_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN16_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN16_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN16_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN16_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN16_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN16_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN16_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN16_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN17 */

#define CSL_CTSET2_CFG_CTOWN17_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN17_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN17_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN17_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN17_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN17_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN17_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN17_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN17_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN17_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN17_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN17_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN18 */

#define CSL_CTSET2_CFG_CTOWN18_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN18_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN18_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN18_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN18_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN18_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN18_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN18_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN18_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN18_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN18_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN18_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN19 */

#define CSL_CTSET2_CFG_CTOWN19_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN19_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN19_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN19_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN19_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN19_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN19_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN19_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN19_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN19_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN19_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN19_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN20 */

#define CSL_CTSET2_CFG_CTOWN20_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN20_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN20_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN20_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN20_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN20_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN20_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN20_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN20_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN20_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN20_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN20_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN21 */

#define CSL_CTSET2_CFG_CTOWN21_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN21_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN21_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN21_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN21_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN21_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN21_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN21_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN21_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN21_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN21_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN21_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN22 */

#define CSL_CTSET2_CFG_CTOWN22_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN22_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN22_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN22_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN22_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN22_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN22_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN22_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN22_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN22_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN22_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN22_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN23 */

#define CSL_CTSET2_CFG_CTOWN23_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN23_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN23_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN23_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN23_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN23_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN23_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN23_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN23_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN23_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN23_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN23_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN24 */

#define CSL_CTSET2_CFG_CTOWN24_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN24_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN24_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN24_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN24_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN24_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN24_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN24_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN24_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN24_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN24_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN24_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN25 */

#define CSL_CTSET2_CFG_CTOWN25_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN25_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN25_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN25_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN25_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN25_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN25_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN25_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN25_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN25_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN25_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN25_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN26 */

#define CSL_CTSET2_CFG_CTOWN26_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN26_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN26_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN26_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN26_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN26_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN26_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN26_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN26_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN26_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN26_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN26_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN27 */

#define CSL_CTSET2_CFG_CTOWN27_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN27_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN27_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN27_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN27_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN27_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN27_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN27_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN27_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN27_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN27_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN27_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN28 */

#define CSL_CTSET2_CFG_CTOWN28_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN28_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN28_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN28_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN28_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN28_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN28_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN28_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN28_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN28_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN28_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN28_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN29 */

#define CSL_CTSET2_CFG_CTOWN29_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN29_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN29_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN29_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN29_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN29_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN29_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN29_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN29_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN29_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN29_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN29_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN30 */

#define CSL_CTSET2_CFG_CTOWN30_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN30_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN30_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN30_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN30_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN30_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN30_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN30_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN30_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN30_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN30_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN30_OWNERSHIP_MAX                                   (0x00000003U)

/* CTOWN31 */

#define CSL_CTSET2_CFG_CTOWN31_RESERVED_MASK                                   (0x0FFFFFFFU)
#define CSL_CTSET2_CFG_CTOWN31_RESERVED_SHIFT                                  (0x00000000U)
#define CSL_CTSET2_CFG_CTOWN31_RESERVED_MAX                                    (0x0FFFFFFFU)

#define CSL_CTSET2_CFG_CTOWN31_CURRENT_OWNER_MASK                              (0x10000000U)
#define CSL_CTSET2_CFG_CTOWN31_CURRENT_OWNER_SHIFT                             (0x0000001CU)
#define CSL_CTSET2_CFG_CTOWN31_CURRENT_OWNER_MAX                               (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN31_DBG_OVERIDE_MASK                                (0x20000000U)
#define CSL_CTSET2_CFG_CTOWN31_DBG_OVERIDE_SHIFT                               (0x0000001DU)
#define CSL_CTSET2_CFG_CTOWN31_DBG_OVERIDE_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_CTOWN31_OWNERSHIP_MASK                                  (0xC0000000U)
#define CSL_CTSET2_CFG_CTOWN31_OWNERSHIP_SHIFT                                 (0x0000001EU)
#define CSL_CTSET2_CFG_CTOWN31_OWNERSHIP_MAX                                   (0x00000003U)

/* CTFILT0 */

#define CSL_CTSET2_CFG_CTFILT0_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT0_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT0_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT0_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT0_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT0_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT0_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT0_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT0_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT0_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT0_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT0_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT0_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT0_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT0_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT0_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT0_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT0_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT0_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT0_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT1 */

#define CSL_CTSET2_CFG_CTFILT1_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT1_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT1_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT1_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT1_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT1_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT1_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT1_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT1_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT1_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT1_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT1_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT1_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT1_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT1_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT1_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT1_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT1_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT1_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT1_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT2 */

#define CSL_CTSET2_CFG_CTFILT2_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT2_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT2_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT2_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT2_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT2_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT2_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT2_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT2_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT2_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT2_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT2_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT2_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT2_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT2_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT2_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT2_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT2_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT2_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT2_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT3 */

#define CSL_CTSET2_CFG_CTFILT3_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT3_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT3_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT3_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT3_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT3_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT3_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT3_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT3_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT3_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT3_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT3_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT3_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT3_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT3_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT3_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT3_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT3_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT3_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT3_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT4 */

#define CSL_CTSET2_CFG_CTFILT4_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT4_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT4_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT4_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT4_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT4_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT4_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT4_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT4_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT4_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT4_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT4_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT4_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT4_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT4_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT4_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT4_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT4_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT4_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT4_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT5 */

#define CSL_CTSET2_CFG_CTFILT5_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT5_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT5_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT5_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT5_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT5_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT5_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT5_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT5_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT5_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT5_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT5_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT5_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT5_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT5_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT5_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT5_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT5_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT5_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT5_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT6 */

#define CSL_CTSET2_CFG_CTFILT6_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT6_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT6_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT6_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT6_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT6_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT6_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT6_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT6_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT6_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT6_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT6_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT6_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT6_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT6_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT6_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT6_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT6_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT6_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT6_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT7 */

#define CSL_CTSET2_CFG_CTFILT7_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT7_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT7_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT7_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT7_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT7_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT7_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT7_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT7_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT7_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT7_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT7_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT7_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT7_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT7_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT7_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT7_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT7_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT7_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT7_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT8 */

#define CSL_CTSET2_CFG_CTFILT8_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT8_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT8_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT8_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT8_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT8_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT8_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT8_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT8_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT8_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT8_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT8_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT8_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT8_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT8_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT8_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT8_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT8_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT8_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT8_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT9 */

#define CSL_CTSET2_CFG_CTFILT9_FREE_MASK                                       (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT9_FREE_SHIFT                                      (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT9_FREE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_IDLE_MASK                                       (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT9_IDLE_SHIFT                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT9_IDLE_MAX                                        (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_NRUSER_MASK                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT9_NRUSER_SHIFT                                    (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT9_NRUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_NRSUPER_MASK                                    (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT9_NRSUPER_SHIFT                                   (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT9_NRSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_RUSER_MASK                                      (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT9_RUSER_SHIFT                                     (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT9_RUSER_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_RSUPER_MASK                                     (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT9_RSUPER_SHIFT                                    (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT9_RSUPER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_SECUSER_MASK                                    (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT9_SECUSER_SHIFT                                   (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT9_SECUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_SECSUPER_MASK                                   (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT9_SECSUPER_SHIFT                                  (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT9_SECSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT9_RESERVED_MASK                                   (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT9_RESERVED_SHIFT                                  (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT9_RESERVED_MAX                                    (0x00FFFFFFU)

/* CTFILT10 */

#define CSL_CTSET2_CFG_CTFILT10_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT10_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT10_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT10_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT10_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT10_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT10_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT10_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT10_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT10_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT10_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT10_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT10_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT10_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT10_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT10_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT10_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT10_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT10_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT10_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT11 */

#define CSL_CTSET2_CFG_CTFILT11_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT11_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT11_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT11_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT11_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT11_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT11_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT11_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT11_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT11_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT11_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT11_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT11_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT11_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT11_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT11_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT11_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT11_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT11_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT11_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT12 */

#define CSL_CTSET2_CFG_CTFILT12_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT12_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT12_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT12_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT12_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT12_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT12_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT12_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT12_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT12_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT12_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT12_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT12_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT12_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT12_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT12_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT12_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT12_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT12_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT12_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT13 */

#define CSL_CTSET2_CFG_CTFILT13_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT13_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT13_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT13_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT13_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT13_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT13_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT13_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT13_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT13_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT13_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT13_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT13_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT13_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT13_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT13_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT13_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT13_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT13_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT13_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT14 */

#define CSL_CTSET2_CFG_CTFILT14_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT14_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT14_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT14_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT14_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT14_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT14_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT14_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT14_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT14_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT14_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT14_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT14_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT14_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT14_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT14_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT14_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT14_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT14_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT14_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT15 */

#define CSL_CTSET2_CFG_CTFILT15_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT15_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT15_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT15_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT15_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT15_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT15_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT15_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT15_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT15_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT15_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT15_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT15_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT15_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT15_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT15_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT15_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT15_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT15_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT15_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT16 */

#define CSL_CTSET2_CFG_CTFILT16_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT16_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT16_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT16_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT16_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT16_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT16_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT16_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT16_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT16_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT16_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT16_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT16_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT16_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT16_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT16_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT16_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT16_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT16_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT16_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT17 */

#define CSL_CTSET2_CFG_CTFILT17_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT17_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT17_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT17_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT17_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT17_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT17_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT17_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT17_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT17_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT17_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT17_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT17_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT17_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT17_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT17_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT17_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT17_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT17_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT17_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT18 */

#define CSL_CTSET2_CFG_CTFILT18_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT18_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT18_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT18_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT18_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT18_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT18_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT18_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT18_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT18_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT18_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT18_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT18_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT18_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT18_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT18_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT18_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT18_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT18_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT18_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT19 */

#define CSL_CTSET2_CFG_CTFILT19_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT19_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT19_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT19_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT19_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT19_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT19_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT19_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT19_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT19_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT19_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT19_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT19_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT19_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT19_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT19_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT19_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT19_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT19_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT19_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT20 */

#define CSL_CTSET2_CFG_CTFILT20_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT20_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT20_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT20_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT20_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT20_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT20_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT20_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT20_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT20_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT20_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT20_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT20_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT20_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT20_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT20_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT20_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT20_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT20_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT20_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT21 */

#define CSL_CTSET2_CFG_CTFILT21_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT21_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT21_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT21_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT21_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT21_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT21_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT21_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT21_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT21_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT21_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT21_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT21_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT21_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT21_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT21_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT21_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT21_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT21_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT21_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT22 */

#define CSL_CTSET2_CFG_CTFILT22_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT22_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT22_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT22_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT22_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT22_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT22_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT22_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT22_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT22_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT22_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT22_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT22_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT22_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT22_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT22_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT22_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT22_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT22_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT22_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT23 */

#define CSL_CTSET2_CFG_CTFILT23_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT23_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT23_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT23_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT23_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT23_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT23_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT23_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT23_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT23_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT23_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT23_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT23_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT23_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT23_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT23_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT23_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT23_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT23_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT23_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT24 */

#define CSL_CTSET2_CFG_CTFILT24_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT24_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT24_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT24_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT24_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT24_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT24_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT24_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT24_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT24_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT24_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT24_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT24_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT24_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT24_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT24_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT24_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT24_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT24_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT24_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT25 */

#define CSL_CTSET2_CFG_CTFILT25_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT25_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT25_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT25_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT25_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT25_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT25_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT25_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT25_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT25_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT25_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT25_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT25_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT25_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT25_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT25_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT25_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT25_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT25_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT25_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT26 */

#define CSL_CTSET2_CFG_CTFILT26_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT26_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT26_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT26_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT26_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT26_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT26_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT26_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT26_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT26_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT26_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT26_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT26_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT26_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT26_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT26_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT26_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT26_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT26_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT26_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT27 */

#define CSL_CTSET2_CFG_CTFILT27_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT27_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT27_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT27_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT27_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT27_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT27_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT27_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT27_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT27_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT27_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT27_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT27_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT27_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT27_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT27_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT27_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT27_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT27_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT27_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT28 */

#define CSL_CTSET2_CFG_CTFILT28_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT28_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT28_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT28_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT28_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT28_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT28_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT28_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT28_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT28_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT28_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT28_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT28_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT28_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT28_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT28_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT28_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT28_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT28_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT28_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT29 */

#define CSL_CTSET2_CFG_CTFILT29_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT29_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT29_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT29_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT29_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT29_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT29_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT29_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT29_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT29_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT29_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT29_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT29_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT29_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT29_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT29_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT29_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT29_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT29_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT29_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT30 */

#define CSL_CTSET2_CFG_CTFILT30_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT30_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT30_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT30_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT30_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT30_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT30_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT30_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT30_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT30_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT30_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT30_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT30_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT30_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT30_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT30_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT30_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT30_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT30_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT30_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTFILT31 */

#define CSL_CTSET2_CFG_CTFILT31_FREE_MASK                                      (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT31_FREE_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTFILT31_FREE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_IDLE_MASK                                      (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT31_IDLE_SHIFT                                     (0x00000001U)
#define CSL_CTSET2_CFG_CTFILT31_IDLE_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_NRUSER_MASK                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT31_NRUSER_SHIFT                                   (0x00000002U)
#define CSL_CTSET2_CFG_CTFILT31_NRUSER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_NRSUPER_MASK                                   (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT31_NRSUPER_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_CTFILT31_NRSUPER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_RUSER_MASK                                     (0x00000010U)
#define CSL_CTSET2_CFG_CTFILT31_RUSER_SHIFT                                    (0x00000004U)
#define CSL_CTSET2_CFG_CTFILT31_RUSER_MAX                                      (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_RSUPER_MASK                                    (0x00000020U)
#define CSL_CTSET2_CFG_CTFILT31_RSUPER_SHIFT                                   (0x00000005U)
#define CSL_CTSET2_CFG_CTFILT31_RSUPER_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_SECUSER_MASK                                   (0x00000040U)
#define CSL_CTSET2_CFG_CTFILT31_SECUSER_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_CTFILT31_SECUSER_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_SECSUPER_MASK                                  (0x00000080U)
#define CSL_CTSET2_CFG_CTFILT31_SECSUPER_SHIFT                                 (0x00000007U)
#define CSL_CTSET2_CFG_CTFILT31_SECSUPER_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_CTFILT31_RESERVED_MASK                                  (0xFFFFFF00U)
#define CSL_CTSET2_CFG_CTFILT31_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_CTFILT31_RESERVED_MAX                                   (0x00FFFFFFU)

/* CTCNTR0 */

#define CSL_CTSET2_CFG_CTCNTR0_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR0_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR0_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR1 */

#define CSL_CTSET2_CFG_CTCNTR1_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR1_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR1_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR2 */

#define CSL_CTSET2_CFG_CTCNTR2_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR2_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR2_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR3 */

#define CSL_CTSET2_CFG_CTCNTR3_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR3_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR3_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR4 */

#define CSL_CTSET2_CFG_CTCNTR4_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR4_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR4_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR5 */

#define CSL_CTSET2_CFG_CTCNTR5_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR5_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR5_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR6 */

#define CSL_CTSET2_CFG_CTCNTR6_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR6_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR6_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR7 */

#define CSL_CTSET2_CFG_CTCNTR7_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR7_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR7_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR8 */

#define CSL_CTSET2_CFG_CTCNTR8_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR8_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR8_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR9 */

#define CSL_CTSET2_CFG_CTCNTR9_COUNT_MASK                                      (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR9_COUNT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR9_COUNT_MAX                                       (0xFFFFFFFFU)

/* CTCNTR10 */

#define CSL_CTSET2_CFG_CTCNTR10_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR10_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR10_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR11 */

#define CSL_CTSET2_CFG_CTCNTR11_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR11_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR11_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR12 */

#define CSL_CTSET2_CFG_CTCNTR12_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR12_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR12_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR13 */

#define CSL_CTSET2_CFG_CTCNTR13_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR13_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR13_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR14 */

#define CSL_CTSET2_CFG_CTCNTR14_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR14_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR14_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR15 */

#define CSL_CTSET2_CFG_CTCNTR15_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR15_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR15_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR16 */

#define CSL_CTSET2_CFG_CTCNTR16_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR16_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR16_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR17 */

#define CSL_CTSET2_CFG_CTCNTR17_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR17_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR17_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR18 */

#define CSL_CTSET2_CFG_CTCNTR18_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR18_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR18_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR19 */

#define CSL_CTSET2_CFG_CTCNTR19_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR19_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR19_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR20 */

#define CSL_CTSET2_CFG_CTCNTR20_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR20_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR20_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR21 */

#define CSL_CTSET2_CFG_CTCNTR21_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR21_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR21_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR22 */

#define CSL_CTSET2_CFG_CTCNTR22_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR22_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR22_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR23 */

#define CSL_CTSET2_CFG_CTCNTR23_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR23_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR23_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR24 */

#define CSL_CTSET2_CFG_CTCNTR24_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR24_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR24_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR25 */

#define CSL_CTSET2_CFG_CTCNTR25_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR25_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR25_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR26 */

#define CSL_CTSET2_CFG_CTCNTR26_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR26_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR26_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR27 */

#define CSL_CTSET2_CFG_CTCNTR27_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR27_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR27_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR28 */

#define CSL_CTSET2_CFG_CTCNTR28_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR28_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR28_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR29 */

#define CSL_CTSET2_CFG_CTCNTR29_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR29_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR29_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR30 */

#define CSL_CTSET2_CFG_CTCNTR30_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR30_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR30_COUNT_MAX                                      (0xFFFFFFFFU)

/* CTCNTR31 */

#define CSL_CTSET2_CFG_CTCNTR31_COUNT_MASK                                     (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTCNTR31_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_CTCNTR31_COUNT_MAX                                      (0xFFFFFFFFU)

/* CT_EOI */

#define CSL_CTSET2_CFG_CT_EOI_EOI_MASK                                         (0x00000001U)
#define CSL_CTSET2_CFG_CT_EOI_EOI_SHIFT                                        (0x00000000U)
#define CSL_CTSET2_CFG_CT_EOI_EOI_MAX                                          (0x00000001U)

#define CSL_CTSET2_CFG_CT_EOI_RESERVED_MASK                                    (0xFFFFFFFEU)
#define CSL_CTSET2_CFG_CT_EOI_RESERVED_SHIFT                                   (0x00000001U)
#define CSL_CTSET2_CFG_CT_EOI_RESERVED_MAX                                     (0x7FFFFFFFU)

/* CTIRQSTAT_RAW */

#define CSL_CTSET2_CFG_CTIRQSTAT_RAW_TIM_INTN_IRQ_MASK                         (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTIRQSTAT_RAW_TIM_INTN_IRQ_SHIFT                        (0x00000000U)
#define CSL_CTSET2_CFG_CTIRQSTAT_RAW_TIM_INTN_IRQ_MAX                          (0xFFFFFFFFU)

/* CTIRQSTAT */

#define CSL_CTSET2_CFG_CTIRQSTAT_TIM_INTN_IE_MASK                              (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTIRQSTAT_TIM_INTN_IE_SHIFT                             (0x00000000U)
#define CSL_CTSET2_CFG_CTIRQSTAT_TIM_INTN_IE_MAX                               (0xFFFFFFFFU)

/* CTIRQENABLE_SET */

#define CSL_CTSET2_CFG_CTIRQENABLE_SET_TIM_INTN_IES_MASK                       (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTIRQENABLE_SET_TIM_INTN_IES_SHIFT                      (0x00000000U)
#define CSL_CTSET2_CFG_CTIRQENABLE_SET_TIM_INTN_IES_MAX                        (0xFFFFFFFFU)

/* CTIRQENABLE_CLR */

#define CSL_CTSET2_CFG_CTIRQENABLE_CLR_TIM_INTN_IEC_MASK                       (0xFFFFFFFFU)
#define CSL_CTSET2_CFG_CTIRQENABLE_CLR_TIM_INTN_IEC_SHIFT                      (0x00000000U)
#define CSL_CTSET2_CFG_CTIRQENABLE_CLR_TIM_INTN_IEC_MAX                        (0xFFFFFFFFU)

/* STPTCR */

#define CSL_CTSET2_CFG_STPTCR_RESERVED_MASK                                    (0x00000001U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED_SHIFT                                   (0x00000000U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_TSEN_MASK                                        (0x00000002U)
#define CSL_CTSET2_CFG_STPTCR_TSEN_SHIFT                                       (0x00000001U)
#define CSL_CTSET2_CFG_STPTCR_TSEN_MAX                                         (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_SYNCEN_MASK                                      (0x00000004U)
#define CSL_CTSET2_CFG_STPTCR_SYNCEN_SHIFT                                     (0x00000002U)
#define CSL_CTSET2_CFG_STPTCR_SYNCEN_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_RESERVED1_MASK                                   (0x00000018U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED1_SHIFT                                  (0x00000003U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED1_MAX                                    (0x00000003U)

#define CSL_CTSET2_CFG_STPTCR_COMPEN_MASK                                      (0x00000020U)
#define CSL_CTSET2_CFG_STPTCR_COMPEN_SHIFT                                     (0x00000005U)
#define CSL_CTSET2_CFG_STPTCR_COMPEN_MAX                                       (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_RESERVED2_MASK                                   (0x007FFFC0U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED2_SHIFT                                  (0x00000006U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED2_MAX                                    (0x0001FFFFU)

#define CSL_CTSET2_CFG_STPTCR_DATA_FIFOFULL_MASK                               (0x00800000U)
#define CSL_CTSET2_CFG_STPTCR_DATA_FIFOFULL_SHIFT                              (0x00000017U)
#define CSL_CTSET2_CFG_STPTCR_DATA_FIFOFULL_MAX                                (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_MOD_FIFOFULL_MASK                                (0x01000000U)
#define CSL_CTSET2_CFG_STPTCR_MOD_FIFOFULL_SHIFT                               (0x00000018U)
#define CSL_CTSET2_CFG_STPTCR_MOD_FIFOFULL_MAX                                 (0x00000001U)

#define CSL_CTSET2_CFG_STPTCR_RESERVED3_MASK                                   (0xFE000000U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED3_SHIFT                                  (0x00000019U)
#define CSL_CTSET2_CFG_STPTCR_RESERVED3_MAX                                    (0x0000007FU)

/* STPTID */

#define CSL_CTSET2_CFG_STPTID_TRACEID_MASK                                     (0x0000007FU)
#define CSL_CTSET2_CFG_STPTID_TRACEID_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_STPTID_TRACEID_MAX                                      (0x0000007FU)

#define CSL_CTSET2_CFG_STPTID_RESERVED_MASK                                    (0xFFFFFF80U)
#define CSL_CTSET2_CFG_STPTID_RESERVED_SHIFT                                   (0x00000007U)
#define CSL_CTSET2_CFG_STPTID_RESERVED_MAX                                     (0x01FFFFFFU)

/* STPASYNC */

#define CSL_CTSET2_CFG_STPASYNC_COUNT_MASK                                     (0x00000FFFU)
#define CSL_CTSET2_CFG_STPASYNC_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CTSET2_CFG_STPASYNC_COUNT_MAX                                      (0x00000FFFU)

#define CSL_CTSET2_CFG_STPASYNC_EXPMODE_MASK                                   (0x00001000U)
#define CSL_CTSET2_CFG_STPASYNC_EXPMODE_SHIFT                                  (0x0000000CU)
#define CSL_CTSET2_CFG_STPASYNC_EXPMODE_MAX                                    (0x00000001U)

#define CSL_CTSET2_CFG_STPASYNC_RESERVED_MASK                                  (0xFFFFE000U)
#define CSL_CTSET2_CFG_STPASYNC_RESERVED_SHIFT                                 (0x0000000DU)
#define CSL_CTSET2_CFG_STPASYNC_RESERVED_MAX                                   (0x0007FFFFU)

/* STPFFCR */

#define CSL_CTSET2_CFG_STPFFCR_AUTOFLUSH_MASK                                  (0x00000001U)
#define CSL_CTSET2_CFG_STPFFCR_AUTOFLUSH_SHIFT                                 (0x00000000U)
#define CSL_CTSET2_CFG_STPFFCR_AUTOFLUSH_MAX                                   (0x00000001U)

#define CSL_CTSET2_CFG_STPFFCR_ASYNCPE_MASK                                    (0x00000002U)
#define CSL_CTSET2_CFG_STPFFCR_ASYNCPE_SHIFT                                   (0x00000001U)
#define CSL_CTSET2_CFG_STPFFCR_ASYNCPE_MAX                                     (0x00000001U)

#define CSL_CTSET2_CFG_STPFFCR_RESERVED_MASK                                   (0x0000001CU)
#define CSL_CTSET2_CFG_STPFFCR_RESERVED_SHIFT                                  (0x00000002U)
#define CSL_CTSET2_CFG_STPFFCR_RESERVED_MAX                                    (0x00000007U)

#define CSL_CTSET2_CFG_STPFFCR_FORCEFLUSH_MASK                                 (0x00000020U)
#define CSL_CTSET2_CFG_STPFFCR_FORCEFLUSH_SHIFT                                (0x00000005U)
#define CSL_CTSET2_CFG_STPFFCR_FORCEFLUSH_MAX                                  (0x00000001U)

#define CSL_CTSET2_CFG_STPFFCR_RESERVED1_MASK                                  (0xFFFFFFC0U)
#define CSL_CTSET2_CFG_STPFFCR_RESERVED1_SHIFT                                 (0x00000006U)
#define CSL_CTSET2_CFG_STPFFCR_RESERVED1_MAX                                   (0x03FFFFFFU)

/* STPFEAT1 */

#define CSL_CTSET2_CFG_STPFEAT1_PROT_MASK                                      (0x0000000FU)
#define CSL_CTSET2_CFG_STPFEAT1_PROT_SHIFT                                     (0x00000000U)
#define CSL_CTSET2_CFG_STPFEAT1_PROT_MAX                                       (0x0000000FU)

#define CSL_CTSET2_CFG_STPFEAT1_VERSION_MASK                                   (0x00000070U)
#define CSL_CTSET2_CFG_STPFEAT1_VERSION_SHIFT                                  (0x00000004U)
#define CSL_CTSET2_CFG_STPFEAT1_VERSION_MAX                                    (0x00000007U)

#define CSL_CTSET2_CFG_STPFEAT1_RESERVED_MASK                                  (0x0001FF00U)
#define CSL_CTSET2_CFG_STPFEAT1_RESERVED_SHIFT                                 (0x00000008U)
#define CSL_CTSET2_CFG_STPFEAT1_RESERVED_MAX                                   (0x000001FFU)

#define CSL_CTSET2_CFG_STPFEAT1_STP_MINVER_MASK                                (0x003E0000U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_MINVER_SHIFT                               (0x00000011U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_MINVER_MAX                                 (0x0000001FU)

#define CSL_CTSET2_CFG_STPFEAT1_STP_CUSTVER_MASK                               (0x00C00000U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_CUSTVER_SHIFT                              (0x00000016U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_CUSTVER_MAX                                (0x00000003U)

#define CSL_CTSET2_CFG_STPFEAT1_STP_MAJVER_MASK                                (0x07000000U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_MAJVER_SHIFT                               (0x00000018U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_MAJVER_MAX                                 (0x00000007U)

#define CSL_CTSET2_CFG_STPFEAT1_STP_RTLVER_MASK                                (0xF8000000U)
#define CSL_CTSET2_CFG_STPFEAT1_STP_RTLVER_SHIFT                               (0x0000001BU)
#define CSL_CTSET2_CFG_STPFEAT1_STP_RTLVER_MAX                                 (0x0000001FU)

#ifdef __cplusplus
}
#endif
#endif
