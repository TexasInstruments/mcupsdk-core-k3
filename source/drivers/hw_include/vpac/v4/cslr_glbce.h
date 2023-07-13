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
 *  Name        : cslr_glbce.h
*/
#ifndef CSLR_GLBCE_H_
#define CSLR_GLBCE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : GLBCE Configuration regsiters
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CFG;
    volatile uint32_t MODE;
    volatile uint32_t CONTROL0;
    volatile uint32_t CONTROL1;
    volatile uint32_t BLACK_LEVEL;
    volatile uint32_t WHITE_LEVEL;
    volatile uint32_t VARIANCE;
    volatile uint32_t LIMIT_AMPL;
    volatile uint32_t DITHER;
    volatile uint32_t SLOPE_MAX;
    volatile uint32_t SLOPE_MIN;
    volatile uint32_t LUT_FI[33U];
    volatile uint32_t FORMAT_CONTROL_REG0;
    volatile uint32_t FORMAT_CONTROL_REG1;
    volatile uint32_t FRAME_WIDTH;
    volatile uint32_t FRAME_HEIGHT;
    volatile uint32_t STRENGTH_IR;
    volatile uint32_t PERCEPT_EN;
    volatile uint32_t REV_PERCEPT_LUT[65U];
    volatile uint32_t FWD_PERCEPT_LUT[65U];
    volatile uint32_t WDR_GAMMA_EN;
    volatile uint32_t WDR_GAMMA_LUT[257U];
    volatile uint32_t TILE_OUT_POS;
    volatile uint8_t  Resv_1760[4];
    volatile uint32_t TILE_OUT_SIZE;
    volatile uint8_t  Resv_1768[4];
    volatile uint32_t TILE_CONTROL;
    volatile uint32_t OUTPUT_FLAGS;
} CSL_glbceRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_GLBCE_CFG                                                (0x00000000U)
#define CSL_GLBCE_MODE                                               (0x00000004U)
#define CSL_GLBCE_CONTROL0                                           (0x00000008U)
#define CSL_GLBCE_CONTROL1                                           (0x0000000CU)
#define CSL_GLBCE_BLACK_LEVEL                                        (0x00000010U)
#define CSL_GLBCE_WHITE_LEVEL                                        (0x00000014U)
#define CSL_GLBCE_VARIANCE                                           (0x00000018U)
#define CSL_GLBCE_LIMIT_AMPL                                         (0x0000001CU)
#define CSL_GLBCE_DITHER                                             (0x00000020U)
#define CSL_GLBCE_SLOPE_MAX                                          (0x00000024U)
#define CSL_GLBCE_SLOPE_MIN                                          (0x00000028U)
#define CSL_GLBCE_LUT_FI_00                                          (0x0000002CU)
#define CSL_GLBCE_LUT_FI_01                                          (0x00000030U)
#define CSL_GLBCE_LUT_FI_02                                          (0x00000034U)
#define CSL_GLBCE_LUT_FI_03                                          (0x00000038U)
#define CSL_GLBCE_LUT_FI_04                                          (0x0000003CU)
#define CSL_GLBCE_LUT_FI_05                                          (0x00000040U)
#define CSL_GLBCE_LUT_FI_06                                          (0x00000044U)
#define CSL_GLBCE_LUT_FI_07                                          (0x00000048U)
#define CSL_GLBCE_LUT_FI_08                                          (0x0000004CU)
#define CSL_GLBCE_LUT_FI_09                                          (0x00000050U)
#define CSL_GLBCE_LUT_FI_10                                          (0x00000054U)
#define CSL_GLBCE_LUT_FI_11                                          (0x00000058U)
#define CSL_GLBCE_LUT_FI_12                                          (0x0000005CU)
#define CSL_GLBCE_LUT_FI_13                                          (0x00000060U)
#define CSL_GLBCE_LUT_FI_14                                          (0x00000064U)
#define CSL_GLBCE_LUT_FI_15                                          (0x00000068U)
#define CSL_GLBCE_LUT_FI_16                                          (0x0000006CU)
#define CSL_GLBCE_LUT_FI_17                                          (0x00000070U)
#define CSL_GLBCE_LUT_FI_18                                          (0x00000074U)
#define CSL_GLBCE_LUT_FI_19                                          (0x00000078U)
#define CSL_GLBCE_LUT_FI_20                                          (0x0000007CU)
#define CSL_GLBCE_LUT_FI_21                                          (0x00000080U)
#define CSL_GLBCE_LUT_FI_22                                          (0x00000084U)
#define CSL_GLBCE_LUT_FI_23                                          (0x00000088U)
#define CSL_GLBCE_LUT_FI_24                                          (0x0000008CU)
#define CSL_GLBCE_LUT_FI_25                                          (0x00000090U)
#define CSL_GLBCE_LUT_FI_26                                          (0x00000094U)
#define CSL_GLBCE_LUT_FI_27                                          (0x00000098U)
#define CSL_GLBCE_LUT_FI_28                                          (0x0000009CU)
#define CSL_GLBCE_LUT_FI_29                                          (0x000000A0U)
#define CSL_GLBCE_LUT_FI_30                                          (0x000000A4U)
#define CSL_GLBCE_LUT_FI_31                                          (0x000000A8U)
#define CSL_GLBCE_LUT_FI_32                                          (0x000000ACU)
#define CSL_GLBCE_FORMAT_CONTROL_REG0                                (0x000000B0U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1                                (0x000000B4U)
#define CSL_GLBCE_FRAME_WIDTH                                        (0x000000B8U)
#define CSL_GLBCE_FRAME_HEIGHT                                       (0x000000BCU)
#define CSL_GLBCE_STRENGTH_IR                                        (0x000000C0U)
#define CSL_GLBCE_PERCEPT_EN                                         (0x000000C4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_00                                 (0x000000C8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_01                                 (0x000000CCU)
#define CSL_GLBCE_REV_PERCEPT_LUT_02                                 (0x000000D0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_03                                 (0x000000D4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_04                                 (0x000000D8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_05                                 (0x000000DCU)
#define CSL_GLBCE_REV_PERCEPT_LUT_06                                 (0x000000E0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_07                                 (0x000000E4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_08                                 (0x000000E8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_09                                 (0x000000ECU)
#define CSL_GLBCE_REV_PERCEPT_LUT_10                                 (0x000000F0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_11                                 (0x000000F4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_12                                 (0x000000F8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_13                                 (0x000000FCU)
#define CSL_GLBCE_REV_PERCEPT_LUT_14                                 (0x00000100U)
#define CSL_GLBCE_REV_PERCEPT_LUT_15                                 (0x00000104U)
#define CSL_GLBCE_REV_PERCEPT_LUT_16                                 (0x00000108U)
#define CSL_GLBCE_REV_PERCEPT_LUT_17                                 (0x0000010CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_18                                 (0x00000110U)
#define CSL_GLBCE_REV_PERCEPT_LUT_19                                 (0x00000114U)
#define CSL_GLBCE_REV_PERCEPT_LUT_20                                 (0x00000118U)
#define CSL_GLBCE_REV_PERCEPT_LUT_21                                 (0x0000011CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_22                                 (0x00000120U)
#define CSL_GLBCE_REV_PERCEPT_LUT_23                                 (0x00000124U)
#define CSL_GLBCE_REV_PERCEPT_LUT_24                                 (0x00000128U)
#define CSL_GLBCE_REV_PERCEPT_LUT_25                                 (0x0000012CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_26                                 (0x00000130U)
#define CSL_GLBCE_REV_PERCEPT_LUT_27                                 (0x00000134U)
#define CSL_GLBCE_REV_PERCEPT_LUT_28                                 (0x00000138U)
#define CSL_GLBCE_REV_PERCEPT_LUT_29                                 (0x0000013CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_30                                 (0x00000140U)
#define CSL_GLBCE_REV_PERCEPT_LUT_31                                 (0x00000144U)
#define CSL_GLBCE_REV_PERCEPT_LUT_32                                 (0x00000148U)
#define CSL_GLBCE_REV_PERCEPT_LUT_33                                 (0x0000014CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_34                                 (0x00000150U)
#define CSL_GLBCE_REV_PERCEPT_LUT_35                                 (0x00000154U)
#define CSL_GLBCE_REV_PERCEPT_LUT_36                                 (0x00000158U)
#define CSL_GLBCE_REV_PERCEPT_LUT_37                                 (0x0000015CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_38                                 (0x00000160U)
#define CSL_GLBCE_REV_PERCEPT_LUT_39                                 (0x00000164U)
#define CSL_GLBCE_REV_PERCEPT_LUT_40                                 (0x00000168U)
#define CSL_GLBCE_REV_PERCEPT_LUT_41                                 (0x0000016CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_42                                 (0x00000170U)
#define CSL_GLBCE_REV_PERCEPT_LUT_43                                 (0x00000174U)
#define CSL_GLBCE_REV_PERCEPT_LUT_44                                 (0x00000178U)
#define CSL_GLBCE_REV_PERCEPT_LUT_45                                 (0x0000017CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_46                                 (0x00000180U)
#define CSL_GLBCE_REV_PERCEPT_LUT_47                                 (0x00000184U)
#define CSL_GLBCE_REV_PERCEPT_LUT_48                                 (0x00000188U)
#define CSL_GLBCE_REV_PERCEPT_LUT_49                                 (0x0000018CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_50                                 (0x00000190U)
#define CSL_GLBCE_REV_PERCEPT_LUT_51                                 (0x00000194U)
#define CSL_GLBCE_REV_PERCEPT_LUT_52                                 (0x00000198U)
#define CSL_GLBCE_REV_PERCEPT_LUT_53                                 (0x0000019CU)
#define CSL_GLBCE_REV_PERCEPT_LUT_54                                 (0x000001A0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_55                                 (0x000001A4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_56                                 (0x000001A8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_57                                 (0x000001ACU)
#define CSL_GLBCE_REV_PERCEPT_LUT_58                                 (0x000001B0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_59                                 (0x000001B4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_60                                 (0x000001B8U)
#define CSL_GLBCE_REV_PERCEPT_LUT_61                                 (0x000001BCU)
#define CSL_GLBCE_REV_PERCEPT_LUT_62                                 (0x000001C0U)
#define CSL_GLBCE_REV_PERCEPT_LUT_63                                 (0x000001C4U)
#define CSL_GLBCE_REV_PERCEPT_LUT_64                                 (0x000001C8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_00                                 (0x000001CCU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_01                                 (0x000001D0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_02                                 (0x000001D4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_03                                 (0x000001D8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_04                                 (0x000001DCU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_05                                 (0x000001E0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_06                                 (0x000001E4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_07                                 (0x000001E8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_08                                 (0x000001ECU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_09                                 (0x000001F0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_10                                 (0x000001F4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_11                                 (0x000001F8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_12                                 (0x000001FCU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_13                                 (0x00000200U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_14                                 (0x00000204U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_15                                 (0x00000208U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_16                                 (0x0000020CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_17                                 (0x00000210U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_18                                 (0x00000214U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_19                                 (0x00000218U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_20                                 (0x0000021CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_21                                 (0x00000220U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_22                                 (0x00000224U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_23                                 (0x00000228U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_24                                 (0x0000022CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_25                                 (0x00000230U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_26                                 (0x00000234U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_27                                 (0x00000238U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_28                                 (0x0000023CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_29                                 (0x00000240U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_30                                 (0x00000244U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_31                                 (0x00000248U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_32                                 (0x0000024CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_33                                 (0x00000250U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_34                                 (0x00000254U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_35                                 (0x00000258U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_36                                 (0x0000025CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_37                                 (0x00000260U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_38                                 (0x00000264U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_39                                 (0x00000268U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_40                                 (0x0000026CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_41                                 (0x00000270U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_42                                 (0x00000274U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_43                                 (0x00000278U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_44                                 (0x0000027CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_45                                 (0x00000280U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_46                                 (0x00000284U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_47                                 (0x00000288U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_48                                 (0x0000028CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_49                                 (0x00000290U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_50                                 (0x00000294U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_51                                 (0x00000298U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_52                                 (0x0000029CU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_53                                 (0x000002A0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_54                                 (0x000002A4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_55                                 (0x000002A8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_56                                 (0x000002ACU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_57                                 (0x000002B0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_58                                 (0x000002B4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_59                                 (0x000002B8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_60                                 (0x000002BCU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_61                                 (0x000002C0U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_62                                 (0x000002C4U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_63                                 (0x000002C8U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_64                                 (0x000002CCU)
#define CSL_GLBCE_WDR_GAMMA_EN                                       (0x000002D0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_00                                   (0x000002D4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_01                                   (0x000002D8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_02                                   (0x000002DCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_03                                   (0x000002E0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_04                                   (0x000002E4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_05                                   (0x000002E8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_06                                   (0x000002ECU)
#define CSL_GLBCE_WDR_GAMMA_LUT_07                                   (0x000002F0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_08                                   (0x000002F4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_09                                   (0x000002F8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_10                                   (0x000002FCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_11                                   (0x00000300U)
#define CSL_GLBCE_WDR_GAMMA_LUT_12                                   (0x00000304U)
#define CSL_GLBCE_WDR_GAMMA_LUT_13                                   (0x00000308U)
#define CSL_GLBCE_WDR_GAMMA_LUT_14                                   (0x0000030CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_15                                   (0x00000310U)
#define CSL_GLBCE_WDR_GAMMA_LUT_16                                   (0x00000314U)
#define CSL_GLBCE_WDR_GAMMA_LUT_17                                   (0x00000318U)
#define CSL_GLBCE_WDR_GAMMA_LUT_18                                   (0x0000031CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_19                                   (0x00000320U)
#define CSL_GLBCE_WDR_GAMMA_LUT_20                                   (0x00000324U)
#define CSL_GLBCE_WDR_GAMMA_LUT_21                                   (0x00000328U)
#define CSL_GLBCE_WDR_GAMMA_LUT_22                                   (0x0000032CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_23                                   (0x00000330U)
#define CSL_GLBCE_WDR_GAMMA_LUT_24                                   (0x00000334U)
#define CSL_GLBCE_WDR_GAMMA_LUT_25                                   (0x00000338U)
#define CSL_GLBCE_WDR_GAMMA_LUT_26                                   (0x0000033CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_27                                   (0x00000340U)
#define CSL_GLBCE_WDR_GAMMA_LUT_28                                   (0x00000344U)
#define CSL_GLBCE_WDR_GAMMA_LUT_29                                   (0x00000348U)
#define CSL_GLBCE_WDR_GAMMA_LUT_30                                   (0x0000034CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_31                                   (0x00000350U)
#define CSL_GLBCE_WDR_GAMMA_LUT_32                                   (0x00000354U)
#define CSL_GLBCE_WDR_GAMMA_LUT_33                                   (0x00000358U)
#define CSL_GLBCE_WDR_GAMMA_LUT_34                                   (0x0000035CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_35                                   (0x00000360U)
#define CSL_GLBCE_WDR_GAMMA_LUT_36                                   (0x00000364U)
#define CSL_GLBCE_WDR_GAMMA_LUT_37                                   (0x00000368U)
#define CSL_GLBCE_WDR_GAMMA_LUT_38                                   (0x0000036CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_39                                   (0x00000370U)
#define CSL_GLBCE_WDR_GAMMA_LUT_40                                   (0x00000374U)
#define CSL_GLBCE_WDR_GAMMA_LUT_41                                   (0x00000378U)
#define CSL_GLBCE_WDR_GAMMA_LUT_42                                   (0x0000037CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_43                                   (0x00000380U)
#define CSL_GLBCE_WDR_GAMMA_LUT_44                                   (0x00000384U)
#define CSL_GLBCE_WDR_GAMMA_LUT_45                                   (0x00000388U)
#define CSL_GLBCE_WDR_GAMMA_LUT_46                                   (0x0000038CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_47                                   (0x00000390U)
#define CSL_GLBCE_WDR_GAMMA_LUT_48                                   (0x00000394U)
#define CSL_GLBCE_WDR_GAMMA_LUT_49                                   (0x00000398U)
#define CSL_GLBCE_WDR_GAMMA_LUT_50                                   (0x0000039CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_51                                   (0x000003A0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_52                                   (0x000003A4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_53                                   (0x000003A8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_54                                   (0x000003ACU)
#define CSL_GLBCE_WDR_GAMMA_LUT_55                                   (0x000003B0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_56                                   (0x000003B4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_57                                   (0x000003B8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_58                                   (0x000003BCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_59                                   (0x000003C0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_60                                   (0x000003C4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_61                                   (0x000003C8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_62                                   (0x000003CCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_63                                   (0x000003D0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_64                                   (0x000003D4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_65                                   (0x000003D8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_66                                   (0x000003DCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_67                                   (0x000003E0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_68                                   (0x000003E4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_69                                   (0x000003E8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_70                                   (0x000003ECU)
#define CSL_GLBCE_WDR_GAMMA_LUT_71                                   (0x000003F0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_72                                   (0x000003F4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_73                                   (0x000003F8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_74                                   (0x000003FCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_75                                   (0x00000400U)
#define CSL_GLBCE_WDR_GAMMA_LUT_76                                   (0x00000404U)
#define CSL_GLBCE_WDR_GAMMA_LUT_77                                   (0x00000408U)
#define CSL_GLBCE_WDR_GAMMA_LUT_78                                   (0x0000040CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_79                                   (0x00000410U)
#define CSL_GLBCE_WDR_GAMMA_LUT_80                                   (0x00000414U)
#define CSL_GLBCE_WDR_GAMMA_LUT_81                                   (0x00000418U)
#define CSL_GLBCE_WDR_GAMMA_LUT_82                                   (0x0000041CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_83                                   (0x00000420U)
#define CSL_GLBCE_WDR_GAMMA_LUT_84                                   (0x00000424U)
#define CSL_GLBCE_WDR_GAMMA_LUT_85                                   (0x00000428U)
#define CSL_GLBCE_WDR_GAMMA_LUT_86                                   (0x0000042CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_87                                   (0x00000430U)
#define CSL_GLBCE_WDR_GAMMA_LUT_88                                   (0x00000434U)
#define CSL_GLBCE_WDR_GAMMA_LUT_89                                   (0x00000438U)
#define CSL_GLBCE_WDR_GAMMA_LUT_90                                   (0x0000043CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_91                                   (0x00000440U)
#define CSL_GLBCE_WDR_GAMMA_LUT_92                                   (0x00000444U)
#define CSL_GLBCE_WDR_GAMMA_LUT_93                                   (0x00000448U)
#define CSL_GLBCE_WDR_GAMMA_LUT_94                                   (0x0000044CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_95                                   (0x00000450U)
#define CSL_GLBCE_WDR_GAMMA_LUT_96                                   (0x00000454U)
#define CSL_GLBCE_WDR_GAMMA_LUT_97                                   (0x00000458U)
#define CSL_GLBCE_WDR_GAMMA_LUT_98                                   (0x0000045CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_99                                   (0x00000460U)
#define CSL_GLBCE_WDR_GAMMA_LUT_100                                  (0x00000464U)
#define CSL_GLBCE_WDR_GAMMA_LUT_101                                  (0x00000468U)
#define CSL_GLBCE_WDR_GAMMA_LUT_102                                  (0x0000046CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_103                                  (0x00000470U)
#define CSL_GLBCE_WDR_GAMMA_LUT_104                                  (0x00000474U)
#define CSL_GLBCE_WDR_GAMMA_LUT_105                                  (0x00000478U)
#define CSL_GLBCE_WDR_GAMMA_LUT_106                                  (0x0000047CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_107                                  (0x00000480U)
#define CSL_GLBCE_WDR_GAMMA_LUT_108                                  (0x00000484U)
#define CSL_GLBCE_WDR_GAMMA_LUT_109                                  (0x00000488U)
#define CSL_GLBCE_WDR_GAMMA_LUT_110                                  (0x0000048CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_111                                  (0x00000490U)
#define CSL_GLBCE_WDR_GAMMA_LUT_112                                  (0x00000494U)
#define CSL_GLBCE_WDR_GAMMA_LUT_113                                  (0x00000498U)
#define CSL_GLBCE_WDR_GAMMA_LUT_114                                  (0x0000049CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_115                                  (0x000004A0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_116                                  (0x000004A4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_117                                  (0x000004A8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_118                                  (0x000004ACU)
#define CSL_GLBCE_WDR_GAMMA_LUT_119                                  (0x000004B0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_120                                  (0x000004B4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_121                                  (0x000004B8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_122                                  (0x000004BCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_123                                  (0x000004C0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_124                                  (0x000004C4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_125                                  (0x000004C8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_126                                  (0x000004CCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_127                                  (0x000004D0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_128                                  (0x000004D4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_129                                  (0x000004D8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_130                                  (0x000004DCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_131                                  (0x000004E0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_132                                  (0x000004E4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_133                                  (0x000004E8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_134                                  (0x000004ECU)
#define CSL_GLBCE_WDR_GAMMA_LUT_135                                  (0x000004F0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_136                                  (0x000004F4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_137                                  (0x000004F8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_138                                  (0x000004FCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_139                                  (0x00000500U)
#define CSL_GLBCE_WDR_GAMMA_LUT_140                                  (0x00000504U)
#define CSL_GLBCE_WDR_GAMMA_LUT_141                                  (0x00000508U)
#define CSL_GLBCE_WDR_GAMMA_LUT_142                                  (0x0000050CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_143                                  (0x00000510U)
#define CSL_GLBCE_WDR_GAMMA_LUT_144                                  (0x00000514U)
#define CSL_GLBCE_WDR_GAMMA_LUT_145                                  (0x00000518U)
#define CSL_GLBCE_WDR_GAMMA_LUT_146                                  (0x0000051CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_147                                  (0x00000520U)
#define CSL_GLBCE_WDR_GAMMA_LUT_148                                  (0x00000524U)
#define CSL_GLBCE_WDR_GAMMA_LUT_149                                  (0x00000528U)
#define CSL_GLBCE_WDR_GAMMA_LUT_150                                  (0x0000052CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_151                                  (0x00000530U)
#define CSL_GLBCE_WDR_GAMMA_LUT_152                                  (0x00000534U)
#define CSL_GLBCE_WDR_GAMMA_LUT_153                                  (0x00000538U)
#define CSL_GLBCE_WDR_GAMMA_LUT_154                                  (0x0000053CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_155                                  (0x00000540U)
#define CSL_GLBCE_WDR_GAMMA_LUT_156                                  (0x00000544U)
#define CSL_GLBCE_WDR_GAMMA_LUT_157                                  (0x00000548U)
#define CSL_GLBCE_WDR_GAMMA_LUT_158                                  (0x0000054CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_159                                  (0x00000550U)
#define CSL_GLBCE_WDR_GAMMA_LUT_160                                  (0x00000554U)
#define CSL_GLBCE_WDR_GAMMA_LUT_161                                  (0x00000558U)
#define CSL_GLBCE_WDR_GAMMA_LUT_162                                  (0x0000055CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_163                                  (0x00000560U)
#define CSL_GLBCE_WDR_GAMMA_LUT_164                                  (0x00000564U)
#define CSL_GLBCE_WDR_GAMMA_LUT_165                                  (0x00000568U)
#define CSL_GLBCE_WDR_GAMMA_LUT_166                                  (0x0000056CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_167                                  (0x00000570U)
#define CSL_GLBCE_WDR_GAMMA_LUT_168                                  (0x00000574U)
#define CSL_GLBCE_WDR_GAMMA_LUT_169                                  (0x00000578U)
#define CSL_GLBCE_WDR_GAMMA_LUT_170                                  (0x0000057CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_171                                  (0x00000580U)
#define CSL_GLBCE_WDR_GAMMA_LUT_172                                  (0x00000584U)
#define CSL_GLBCE_WDR_GAMMA_LUT_173                                  (0x00000588U)
#define CSL_GLBCE_WDR_GAMMA_LUT_174                                  (0x0000058CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_175                                  (0x00000590U)
#define CSL_GLBCE_WDR_GAMMA_LUT_176                                  (0x00000594U)
#define CSL_GLBCE_WDR_GAMMA_LUT_177                                  (0x00000598U)
#define CSL_GLBCE_WDR_GAMMA_LUT_178                                  (0x0000059CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_179                                  (0x000005A0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_180                                  (0x000005A4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_181                                  (0x000005A8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_182                                  (0x000005ACU)
#define CSL_GLBCE_WDR_GAMMA_LUT_183                                  (0x000005B0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_184                                  (0x000005B4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_185                                  (0x000005B8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_186                                  (0x000005BCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_187                                  (0x000005C0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_188                                  (0x000005C4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_189                                  (0x000005C8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_190                                  (0x000005CCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_191                                  (0x000005D0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_192                                  (0x000005D4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_193                                  (0x000005D8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_194                                  (0x000005DCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_195                                  (0x000005E0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_196                                  (0x000005E4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_197                                  (0x000005E8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_198                                  (0x000005ECU)
#define CSL_GLBCE_WDR_GAMMA_LUT_199                                  (0x000005F0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_200                                  (0x000005F4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_201                                  (0x000005F8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_202                                  (0x000005FCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_203                                  (0x00000600U)
#define CSL_GLBCE_WDR_GAMMA_LUT_204                                  (0x00000604U)
#define CSL_GLBCE_WDR_GAMMA_LUT_205                                  (0x00000608U)
#define CSL_GLBCE_WDR_GAMMA_LUT_206                                  (0x0000060CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_207                                  (0x00000610U)
#define CSL_GLBCE_WDR_GAMMA_LUT_208                                  (0x00000614U)
#define CSL_GLBCE_WDR_GAMMA_LUT_209                                  (0x00000618U)
#define CSL_GLBCE_WDR_GAMMA_LUT_210                                  (0x0000061CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_211                                  (0x00000620U)
#define CSL_GLBCE_WDR_GAMMA_LUT_212                                  (0x00000624U)
#define CSL_GLBCE_WDR_GAMMA_LUT_213                                  (0x00000628U)
#define CSL_GLBCE_WDR_GAMMA_LUT_214                                  (0x0000062CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_215                                  (0x00000630U)
#define CSL_GLBCE_WDR_GAMMA_LUT_216                                  (0x00000634U)
#define CSL_GLBCE_WDR_GAMMA_LUT_217                                  (0x00000638U)
#define CSL_GLBCE_WDR_GAMMA_LUT_218                                  (0x0000063CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_219                                  (0x00000640U)
#define CSL_GLBCE_WDR_GAMMA_LUT_220                                  (0x00000644U)
#define CSL_GLBCE_WDR_GAMMA_LUT_221                                  (0x00000648U)
#define CSL_GLBCE_WDR_GAMMA_LUT_222                                  (0x0000064CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_223                                  (0x00000650U)
#define CSL_GLBCE_WDR_GAMMA_LUT_224                                  (0x00000654U)
#define CSL_GLBCE_WDR_GAMMA_LUT_225                                  (0x00000658U)
#define CSL_GLBCE_WDR_GAMMA_LUT_226                                  (0x0000065CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_227                                  (0x00000660U)
#define CSL_GLBCE_WDR_GAMMA_LUT_228                                  (0x00000664U)
#define CSL_GLBCE_WDR_GAMMA_LUT_229                                  (0x00000668U)
#define CSL_GLBCE_WDR_GAMMA_LUT_230                                  (0x0000066CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_231                                  (0x00000670U)
#define CSL_GLBCE_WDR_GAMMA_LUT_232                                  (0x00000674U)
#define CSL_GLBCE_WDR_GAMMA_LUT_233                                  (0x00000678U)
#define CSL_GLBCE_WDR_GAMMA_LUT_234                                  (0x0000067CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_235                                  (0x00000680U)
#define CSL_GLBCE_WDR_GAMMA_LUT_236                                  (0x00000684U)
#define CSL_GLBCE_WDR_GAMMA_LUT_237                                  (0x00000688U)
#define CSL_GLBCE_WDR_GAMMA_LUT_238                                  (0x0000068CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_239                                  (0x00000690U)
#define CSL_GLBCE_WDR_GAMMA_LUT_240                                  (0x00000694U)
#define CSL_GLBCE_WDR_GAMMA_LUT_241                                  (0x00000698U)
#define CSL_GLBCE_WDR_GAMMA_LUT_242                                  (0x0000069CU)
#define CSL_GLBCE_WDR_GAMMA_LUT_243                                  (0x000006A0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_244                                  (0x000006A4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_245                                  (0x000006A8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_246                                  (0x000006ACU)
#define CSL_GLBCE_WDR_GAMMA_LUT_247                                  (0x000006B0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_248                                  (0x000006B4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_249                                  (0x000006B8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_250                                  (0x000006BCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_251                                  (0x000006C0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_252                                  (0x000006C4U)
#define CSL_GLBCE_WDR_GAMMA_LUT_253                                  (0x000006C8U)
#define CSL_GLBCE_WDR_GAMMA_LUT_254                                  (0x000006CCU)
#define CSL_GLBCE_WDR_GAMMA_LUT_255                                  (0x000006D0U)
#define CSL_GLBCE_WDR_GAMMA_LUT_256                                  (0x000006D4U)
#define CSL_GLBCE_TILE_OUT_POS                                       (0x000006D8U)
#define CSL_GLBCE_TILE_OUT_SIZE                                      (0x000006E0U)
#define CSL_GLBCE_TILE_CONTROL                                       (0x000006E8U)
#define CSL_GLBCE_OUTPUT_FLAGS                                       (0x000006ECU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* GLBCE_CFG */

#define CSL_GLBCE_CFG_SWRST_MASK                                     (0x00000001U)
#define CSL_GLBCE_CFG_SWRST_SHIFT                                    (0x00000000U)
#define CSL_GLBCE_CFG_SWRST_MAX                                      (0x00000001U)

#define CSL_GLBCE_CFG_RESERVED_MASK                                  (0xFFFFFFFEU)
#define CSL_GLBCE_CFG_RESERVED_SHIFT                                 (0x00000001U)
#define CSL_GLBCE_CFG_RESERVED_MAX                                   (0x7FFFFFFFU)

/* GLBCE_MODE */

#define CSL_GLBCE_MODE_OST_MASK                                      (0x00000001U)
#define CSL_GLBCE_MODE_OST_SHIFT                                     (0x00000000U)
#define CSL_GLBCE_MODE_OST_MAX                                       (0x00000001U)

#define CSL_GLBCE_MODE_RESERVED_MASK                                 (0xFFFFFFFEU)
#define CSL_GLBCE_MODE_RESERVED_SHIFT                                (0x00000001U)
#define CSL_GLBCE_MODE_RESERVED_MAX                                  (0x7FFFFFFFU)

/* GLBCE_CONTROL0 */

#define CSL_GLBCE_CONTROL0_ONOFF_MASK                                (0x00000001U)
#define CSL_GLBCE_CONTROL0_ONOFF_SHIFT                               (0x00000000U)
#define CSL_GLBCE_CONTROL0_ONOFF_MAX                                 (0x00000001U)

#define CSL_GLBCE_CONTROL0_RESERVED0_MASK                            (0x00000006U)
#define CSL_GLBCE_CONTROL0_RESERVED0_SHIFT                           (0x00000001U)
#define CSL_GLBCE_CONTROL0_RESERVED0_MAX                             (0x00000003U)

#define CSL_GLBCE_CONTROL0_MB_MASK                                   (0x00000008U)
#define CSL_GLBCE_CONTROL0_MB_SHIFT                                  (0x00000003U)
#define CSL_GLBCE_CONTROL0_MB_MAX                                    (0x00000001U)

#define CSL_GLBCE_CONTROL0_RESERVED2_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_CONTROL0_RESERVED2_SHIFT                           (0x00000010U)
#define CSL_GLBCE_CONTROL0_RESERVED2_MAX                             (0x0000FFFFU)

#define CSL_GLBCE_CONTROL0_CCTL_MASK                                 (0x00000010U)
#define CSL_GLBCE_CONTROL0_CCTL_SHIFT                                (0x00000004U)
#define CSL_GLBCE_CONTROL0_CCTL_MAX                                  (0x00000001U)

#define CSL_GLBCE_CONTROL0_RESERVED1_MASK                            (0x0000FFE0U)
#define CSL_GLBCE_CONTROL0_RESERVED1_SHIFT                           (0x00000005U)
#define CSL_GLBCE_CONTROL0_RESERVED1_MAX                             (0x000007FFU)

/* GLBCE_CONTROL1 */

#define CSL_GLBCE_CONTROL1_CONTROL1_MASK                             (0x000000FFU)
#define CSL_GLBCE_CONTROL1_CONTROL1_SHIFT                            (0x00000000U)
#define CSL_GLBCE_CONTROL1_CONTROL1_MAX                              (0x000000FFU)

#define CSL_GLBCE_CONTROL1_RESERVED1_MASK                            (0xFFFFFF00U)
#define CSL_GLBCE_CONTROL1_RESERVED1_SHIFT                           (0x00000008U)
#define CSL_GLBCE_CONTROL1_RESERVED1_MAX                             (0x00FFFFFFU)

/* GLBCE_BLACK_LEVEL */

#define CSL_GLBCE_BLACK_LEVEL_VAL_MASK                               (0x0000FFFFU)
#define CSL_GLBCE_BLACK_LEVEL_VAL_SHIFT                              (0x00000000U)
#define CSL_GLBCE_BLACK_LEVEL_VAL_MAX                                (0x0000FFFFU)

#define CSL_GLBCE_BLACK_LEVEL_RESERVED_MASK                          (0xFFFF0000U)
#define CSL_GLBCE_BLACK_LEVEL_RESERVED_SHIFT                         (0x00000010U)
#define CSL_GLBCE_BLACK_LEVEL_RESERVED_MAX                           (0x0000FFFFU)

/* GLBCE_WHITE_LEVEL */

#define CSL_GLBCE_WHITE_LEVEL_VAL_MASK                               (0x0000FFFFU)
#define CSL_GLBCE_WHITE_LEVEL_VAL_SHIFT                              (0x00000000U)
#define CSL_GLBCE_WHITE_LEVEL_VAL_MAX                                (0x0000FFFFU)

#define CSL_GLBCE_WHITE_LEVEL_RESERVED1_MASK                         (0xFFFF0000U)
#define CSL_GLBCE_WHITE_LEVEL_RESERVED1_SHIFT                        (0x00000010U)
#define CSL_GLBCE_WHITE_LEVEL_RESERVED1_MAX                          (0x0000FFFFU)

/* GLBCE_VARIANCE */

#define CSL_GLBCE_VARIANCE_VARIANCESPACE_MASK                        (0x0000000FU)
#define CSL_GLBCE_VARIANCE_VARIANCESPACE_SHIFT                       (0x00000000U)
#define CSL_GLBCE_VARIANCE_VARIANCESPACE_MAX                         (0x0000000FU)

#define CSL_GLBCE_VARIANCE_VARIANCEINTENSITY_MASK                    (0x000000F0U)
#define CSL_GLBCE_VARIANCE_VARIANCEINTENSITY_SHIFT                   (0x00000004U)
#define CSL_GLBCE_VARIANCE_VARIANCEINTENSITY_MAX                     (0x0000000FU)

#define CSL_GLBCE_VARIANCE_RESERVED_MASK                             (0xFFFFFF00U)
#define CSL_GLBCE_VARIANCE_RESERVED_SHIFT                            (0x00000008U)
#define CSL_GLBCE_VARIANCE_RESERVED_MAX                              (0x00FFFFFFU)

/* GLBCE_LIMIT_AMPL */

#define CSL_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MASK             (0x0000000FU)
#define CSL_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_SHIFT            (0x00000000U)
#define CSL_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MAX              (0x0000000FU)

#define CSL_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MASK           (0x000000F0U)
#define CSL_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_SHIFT          (0x00000004U)
#define CSL_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MAX            (0x0000000FU)

#define CSL_GLBCE_LIMIT_AMPL_RESERVED_MASK                           (0xFFFFFF00U)
#define CSL_GLBCE_LIMIT_AMPL_RESERVED_SHIFT                          (0x00000008U)
#define CSL_GLBCE_LIMIT_AMPL_RESERVED_MAX                            (0x00FFFFFFU)

/* GLBCE_DITHER */

#define CSL_GLBCE_DITHER_DITHER_MASK                                 (0x00000007U)
#define CSL_GLBCE_DITHER_DITHER_SHIFT                                (0x00000000U)
#define CSL_GLBCE_DITHER_DITHER_MAX                                  (0x00000007U)

#define CSL_GLBCE_DITHER_RESERVED_MASK                               (0x00000078U)
#define CSL_GLBCE_DITHER_RESERVED_SHIFT                              (0x00000003U)
#define CSL_GLBCE_DITHER_RESERVED_MAX                                (0x0000000FU)

#define CSL_GLBCE_DITHER_RESERVED1_MASK                              (0xFFFFFF80U)
#define CSL_GLBCE_DITHER_RESERVED1_SHIFT                             (0x00000007U)
#define CSL_GLBCE_DITHER_RESERVED1_MAX                               (0x01FFFFFFU)

/* GLBCE_SLOPE_MAX */

#define CSL_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_MASK                       (0x000000FFU)
#define CSL_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_SHIFT                      (0x00000000U)
#define CSL_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_MAX                        (0x000000FFU)

#define CSL_GLBCE_SLOPE_MAX_RESERVED_MASK                            (0xFFFFFF00U)
#define CSL_GLBCE_SLOPE_MAX_RESERVED_SHIFT                           (0x00000008U)
#define CSL_GLBCE_SLOPE_MAX_RESERVED_MAX                             (0x00FFFFFFU)

/* GLBCE_SLOPE_MIN */

#define CSL_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_MASK                       (0x000000FFU)
#define CSL_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_SHIFT                      (0x00000000U)
#define CSL_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_MAX                        (0x000000FFU)

#define CSL_GLBCE_SLOPE_MIN_RESERVED_MASK                            (0xFFFFFF00U)
#define CSL_GLBCE_SLOPE_MIN_RESERVED_SHIFT                           (0x00000008U)
#define CSL_GLBCE_SLOPE_MIN_RESERVED_MAX                             (0x00FFFFFFU)

/* GLBCE_LUT_FI_00 */

#define CSL_GLBCE_LUT_FI_00_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_00_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_00_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_00_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_00_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_00_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_01 */

#define CSL_GLBCE_LUT_FI_01_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_01_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_01_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_01_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_01_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_01_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_02 */

#define CSL_GLBCE_LUT_FI_02_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_02_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_02_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_02_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_02_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_02_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_03 */

#define CSL_GLBCE_LUT_FI_03_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_03_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_03_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_03_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_03_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_03_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_04 */

#define CSL_GLBCE_LUT_FI_04_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_04_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_04_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_04_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_04_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_04_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_05 */

#define CSL_GLBCE_LUT_FI_05_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_05_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_05_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_05_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_05_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_05_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_06 */

#define CSL_GLBCE_LUT_FI_06_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_06_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_06_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_06_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_06_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_06_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_07 */

#define CSL_GLBCE_LUT_FI_07_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_07_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_07_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_07_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_07_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_07_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_08 */

#define CSL_GLBCE_LUT_FI_08_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_08_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_08_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_08_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_08_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_08_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_09 */

#define CSL_GLBCE_LUT_FI_09_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_09_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_09_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_09_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_09_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_09_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_10 */

#define CSL_GLBCE_LUT_FI_10_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_10_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_10_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_10_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_10_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_10_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_11 */

#define CSL_GLBCE_LUT_FI_11_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_11_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_11_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_11_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_11_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_11_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_12 */

#define CSL_GLBCE_LUT_FI_12_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_12_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_12_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_12_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_12_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_12_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_13 */

#define CSL_GLBCE_LUT_FI_13_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_13_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_13_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_13_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_13_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_13_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_14 */

#define CSL_GLBCE_LUT_FI_14_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_14_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_14_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_14_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_14_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_14_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_15 */

#define CSL_GLBCE_LUT_FI_15_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_15_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_15_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_15_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_15_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_15_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_16 */

#define CSL_GLBCE_LUT_FI_16_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_16_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_16_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_16_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_16_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_16_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_17 */

#define CSL_GLBCE_LUT_FI_17_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_17_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_17_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_17_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_17_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_17_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_18 */

#define CSL_GLBCE_LUT_FI_18_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_18_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_18_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_18_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_18_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_18_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_19 */

#define CSL_GLBCE_LUT_FI_19_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_19_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_19_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_19_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_19_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_19_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_20 */

#define CSL_GLBCE_LUT_FI_20_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_20_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_20_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_20_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_20_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_20_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_21 */

#define CSL_GLBCE_LUT_FI_21_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_21_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_21_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_21_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_21_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_21_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_22 */

#define CSL_GLBCE_LUT_FI_22_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_22_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_22_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_22_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_22_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_22_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_23 */

#define CSL_GLBCE_LUT_FI_23_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_23_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_23_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_23_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_23_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_23_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_24 */

#define CSL_GLBCE_LUT_FI_24_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_24_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_24_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_24_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_24_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_24_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_25 */

#define CSL_GLBCE_LUT_FI_25_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_25_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_25_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_25_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_25_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_25_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_26 */

#define CSL_GLBCE_LUT_FI_26_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_26_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_26_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_26_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_26_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_26_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_27 */

#define CSL_GLBCE_LUT_FI_27_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_27_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_27_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_27_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_27_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_27_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_28 */

#define CSL_GLBCE_LUT_FI_28_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_28_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_28_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_28_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_28_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_28_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_29 */

#define CSL_GLBCE_LUT_FI_29_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_29_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_29_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_29_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_29_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_29_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_30 */

#define CSL_GLBCE_LUT_FI_30_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_30_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_30_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_30_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_30_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_30_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_31 */

#define CSL_GLBCE_LUT_FI_31_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_31_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_31_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_31_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_31_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_31_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_LUT_FI_32 */

#define CSL_GLBCE_LUT_FI_32_VAL_MASK                                 (0x0000FFFFU)
#define CSL_GLBCE_LUT_FI_32_VAL_SHIFT                                (0x00000000U)
#define CSL_GLBCE_LUT_FI_32_VAL_MAX                                  (0x0000FFFFU)

#define CSL_GLBCE_LUT_FI_32_RESERVED_MASK                            (0xFFFF0000U)
#define CSL_GLBCE_LUT_FI_32_RESERVED_SHIFT                           (0x00000010U)
#define CSL_GLBCE_LUT_FI_32_RESERVED_MAX                             (0x0000FFFFU)

/* GLBCE_FORMAT_CONTROL_REG0 */

#define CSL_GLBCE_FORMAT_CONTROL_REG0_DATAFORMAT_MASK                (0x00000003U)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_DATAFORMAT_SHIFT               (0x00000000U)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_DATAFORMAT_MAX                 (0x00000003U)

#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED_MASK                  (0x000000FCU)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED_SHIFT                 (0x00000002U)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED_MAX                   (0x0000003FU)

#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED1_MASK                 (0xFFFFFF00U)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED1_SHIFT                (0x00000008U)
#define CSL_GLBCE_FORMAT_CONTROL_REG0_RESERVED1_MAX                  (0x00FFFFFFU)

/* GLBCE_FORMAT_CONTROL_REG1 */

#define CSL_GLBCE_FORMAT_CONTROL_REG1_HSPOL_MASK                     (0x00000001U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_HSPOL_SHIFT                    (0x00000000U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_HSPOL_MAX                      (0x00000001U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_VSPOL_MASK                     (0x00000002U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_VSPOL_SHIFT                    (0x00000001U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_VSPOL_MAX                      (0x00000001U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED_MASK                  (0x0000000CU)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED_SHIFT                 (0x00000002U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED_MAX                   (0x00000003U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_FCMODE_MASK                    (0x00000030U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_FCMODE_SHIFT                   (0x00000004U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_FCMODE_MAX                     (0x00000003U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_MASK                   (0x00000040U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_SHIFT                  (0x00000006U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_MAX                    (0x00000001U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_MASK                  (0x00000080U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_SHIFT                 (0x00000007U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_MAX                   (0x00000001U)

#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED1_MASK                 (0xFFFFFF00U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED1_SHIFT                (0x00000008U)
#define CSL_GLBCE_FORMAT_CONTROL_REG1_RESERVED1_MAX                  (0x00FFFFFFU)

/* GLBCE_FRAME_WIDTH */

#define CSL_GLBCE_FRAME_WIDTH_VAL_MASK                               (0x0000FFFFU)
#define CSL_GLBCE_FRAME_WIDTH_VAL_SHIFT                              (0x00000000U)
#define CSL_GLBCE_FRAME_WIDTH_VAL_MAX                                (0x0000FFFFU)

#define CSL_GLBCE_FRAME_WIDTH_RESERVED_MASK                          (0xFFFF0000U)
#define CSL_GLBCE_FRAME_WIDTH_RESERVED_SHIFT                         (0x00000010U)
#define CSL_GLBCE_FRAME_WIDTH_RESERVED_MAX                           (0x0000FFFFU)

/* GLBCE_FRAME_HEIGHT */

#define CSL_GLBCE_FRAME_HEIGHT_VAL_MASK                              (0x0000FFFFU)
#define CSL_GLBCE_FRAME_HEIGHT_VAL_SHIFT                             (0x00000000U)
#define CSL_GLBCE_FRAME_HEIGHT_VAL_MAX                               (0x0000FFFFU)

#define CSL_GLBCE_FRAME_HEIGHT_RESERVED_MASK                         (0xFFFF0000U)
#define CSL_GLBCE_FRAME_HEIGHT_RESERVED_SHIFT                        (0x00000010U)
#define CSL_GLBCE_FRAME_HEIGHT_RESERVED_MAX                          (0x0000FFFFU)

/* GLBCE_STRENGTH_IR */

#define CSL_GLBCE_STRENGTH_IR_VAL_MASK                               (0x000000FFU)
#define CSL_GLBCE_STRENGTH_IR_VAL_SHIFT                              (0x00000000U)
#define CSL_GLBCE_STRENGTH_IR_VAL_MAX                                (0x000000FFU)

#define CSL_GLBCE_STRENGTH_IR_RESERVED_MASK                          (0xFFFFFF00U)
#define CSL_GLBCE_STRENGTH_IR_RESERVED_SHIFT                         (0x00000008U)
#define CSL_GLBCE_STRENGTH_IR_RESERVED_MAX                           (0x00FFFFFFU)

/* GLBCE_PERCEPT_EN */

#define CSL_GLBCE_PERCEPT_EN_REV_EN_MASK                             (0x00000001U)
#define CSL_GLBCE_PERCEPT_EN_REV_EN_SHIFT                            (0x00000000U)
#define CSL_GLBCE_PERCEPT_EN_REV_EN_MAX                              (0x00000001U)

#define CSL_GLBCE_PERCEPT_EN_FWD_EN_MASK                             (0x00000002U)
#define CSL_GLBCE_PERCEPT_EN_FWD_EN_SHIFT                            (0x00000001U)
#define CSL_GLBCE_PERCEPT_EN_FWD_EN_MAX                              (0x00000001U)

#define CSL_GLBCE_PERCEPT_EN_RESERVED_MASK                           (0xFFFFFFFCU)
#define CSL_GLBCE_PERCEPT_EN_RESERVED_SHIFT                          (0x00000002U)
#define CSL_GLBCE_PERCEPT_EN_RESERVED_MAX                            (0x3FFFFFFFU)

/* GLBCE_REV_PERCEPT_LUT_00 */

#define CSL_GLBCE_REV_PERCEPT_LUT_00_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_00_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_00_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_00_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_00_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_00_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_01 */

#define CSL_GLBCE_REV_PERCEPT_LUT_01_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_01_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_01_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_01_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_01_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_01_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_02 */

#define CSL_GLBCE_REV_PERCEPT_LUT_02_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_02_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_02_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_02_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_02_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_02_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_03 */

#define CSL_GLBCE_REV_PERCEPT_LUT_03_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_03_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_03_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_03_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_03_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_03_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_04 */

#define CSL_GLBCE_REV_PERCEPT_LUT_04_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_04_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_04_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_04_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_04_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_04_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_05 */

#define CSL_GLBCE_REV_PERCEPT_LUT_05_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_05_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_05_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_05_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_05_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_05_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_06 */

#define CSL_GLBCE_REV_PERCEPT_LUT_06_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_06_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_06_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_06_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_06_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_06_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_07 */

#define CSL_GLBCE_REV_PERCEPT_LUT_07_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_07_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_07_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_07_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_07_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_07_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_08 */

#define CSL_GLBCE_REV_PERCEPT_LUT_08_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_08_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_08_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_08_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_08_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_08_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_09 */

#define CSL_GLBCE_REV_PERCEPT_LUT_09_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_09_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_09_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_09_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_09_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_09_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_10 */

#define CSL_GLBCE_REV_PERCEPT_LUT_10_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_10_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_10_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_10_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_10_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_10_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_11 */

#define CSL_GLBCE_REV_PERCEPT_LUT_11_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_11_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_11_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_11_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_11_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_11_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_12 */

#define CSL_GLBCE_REV_PERCEPT_LUT_12_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_12_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_12_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_12_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_12_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_12_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_13 */

#define CSL_GLBCE_REV_PERCEPT_LUT_13_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_13_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_13_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_13_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_13_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_13_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_14 */

#define CSL_GLBCE_REV_PERCEPT_LUT_14_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_14_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_14_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_14_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_14_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_14_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_15 */

#define CSL_GLBCE_REV_PERCEPT_LUT_15_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_15_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_15_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_15_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_15_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_15_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_16 */

#define CSL_GLBCE_REV_PERCEPT_LUT_16_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_16_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_16_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_16_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_16_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_16_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_17 */

#define CSL_GLBCE_REV_PERCEPT_LUT_17_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_17_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_17_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_17_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_17_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_17_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_18 */

#define CSL_GLBCE_REV_PERCEPT_LUT_18_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_18_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_18_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_18_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_18_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_18_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_19 */

#define CSL_GLBCE_REV_PERCEPT_LUT_19_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_19_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_19_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_19_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_19_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_19_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_20 */

#define CSL_GLBCE_REV_PERCEPT_LUT_20_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_20_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_20_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_20_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_20_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_20_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_21 */

#define CSL_GLBCE_REV_PERCEPT_LUT_21_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_21_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_21_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_21_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_21_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_21_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_22 */

#define CSL_GLBCE_REV_PERCEPT_LUT_22_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_22_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_22_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_22_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_22_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_22_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_23 */

#define CSL_GLBCE_REV_PERCEPT_LUT_23_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_23_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_23_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_23_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_23_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_23_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_24 */

#define CSL_GLBCE_REV_PERCEPT_LUT_24_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_24_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_24_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_24_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_24_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_24_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_25 */

#define CSL_GLBCE_REV_PERCEPT_LUT_25_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_25_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_25_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_25_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_25_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_25_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_26 */

#define CSL_GLBCE_REV_PERCEPT_LUT_26_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_26_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_26_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_26_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_26_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_26_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_27 */

#define CSL_GLBCE_REV_PERCEPT_LUT_27_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_27_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_27_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_27_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_27_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_27_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_28 */

#define CSL_GLBCE_REV_PERCEPT_LUT_28_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_28_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_28_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_28_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_28_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_28_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_29 */

#define CSL_GLBCE_REV_PERCEPT_LUT_29_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_29_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_29_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_29_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_29_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_29_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_30 */

#define CSL_GLBCE_REV_PERCEPT_LUT_30_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_30_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_30_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_30_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_30_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_30_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_31 */

#define CSL_GLBCE_REV_PERCEPT_LUT_31_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_31_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_31_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_31_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_31_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_31_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_32 */

#define CSL_GLBCE_REV_PERCEPT_LUT_32_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_32_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_32_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_32_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_32_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_32_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_33 */

#define CSL_GLBCE_REV_PERCEPT_LUT_33_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_33_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_33_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_33_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_33_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_33_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_34 */

#define CSL_GLBCE_REV_PERCEPT_LUT_34_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_34_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_34_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_34_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_34_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_34_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_35 */

#define CSL_GLBCE_REV_PERCEPT_LUT_35_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_35_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_35_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_35_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_35_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_35_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_36 */

#define CSL_GLBCE_REV_PERCEPT_LUT_36_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_36_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_36_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_36_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_36_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_36_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_37 */

#define CSL_GLBCE_REV_PERCEPT_LUT_37_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_37_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_37_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_37_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_37_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_37_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_38 */

#define CSL_GLBCE_REV_PERCEPT_LUT_38_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_38_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_38_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_38_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_38_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_38_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_39 */

#define CSL_GLBCE_REV_PERCEPT_LUT_39_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_39_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_39_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_39_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_39_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_39_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_40 */

#define CSL_GLBCE_REV_PERCEPT_LUT_40_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_40_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_40_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_40_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_40_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_40_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_41 */

#define CSL_GLBCE_REV_PERCEPT_LUT_41_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_41_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_41_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_41_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_41_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_41_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_42 */

#define CSL_GLBCE_REV_PERCEPT_LUT_42_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_42_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_42_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_42_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_42_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_42_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_43 */

#define CSL_GLBCE_REV_PERCEPT_LUT_43_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_43_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_43_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_43_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_43_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_43_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_44 */

#define CSL_GLBCE_REV_PERCEPT_LUT_44_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_44_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_44_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_44_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_44_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_44_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_45 */

#define CSL_GLBCE_REV_PERCEPT_LUT_45_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_45_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_45_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_45_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_45_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_45_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_46 */

#define CSL_GLBCE_REV_PERCEPT_LUT_46_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_46_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_46_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_46_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_46_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_46_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_47 */

#define CSL_GLBCE_REV_PERCEPT_LUT_47_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_47_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_47_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_47_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_47_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_47_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_48 */

#define CSL_GLBCE_REV_PERCEPT_LUT_48_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_48_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_48_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_48_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_48_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_48_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_49 */

#define CSL_GLBCE_REV_PERCEPT_LUT_49_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_49_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_49_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_49_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_49_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_49_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_50 */

#define CSL_GLBCE_REV_PERCEPT_LUT_50_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_50_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_50_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_50_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_50_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_50_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_51 */

#define CSL_GLBCE_REV_PERCEPT_LUT_51_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_51_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_51_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_51_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_51_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_51_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_52 */

#define CSL_GLBCE_REV_PERCEPT_LUT_52_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_52_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_52_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_52_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_52_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_52_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_53 */

#define CSL_GLBCE_REV_PERCEPT_LUT_53_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_53_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_53_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_53_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_53_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_53_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_54 */

#define CSL_GLBCE_REV_PERCEPT_LUT_54_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_54_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_54_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_54_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_54_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_54_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_55 */

#define CSL_GLBCE_REV_PERCEPT_LUT_55_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_55_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_55_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_55_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_55_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_55_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_56 */

#define CSL_GLBCE_REV_PERCEPT_LUT_56_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_56_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_56_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_56_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_56_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_56_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_57 */

#define CSL_GLBCE_REV_PERCEPT_LUT_57_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_57_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_57_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_57_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_57_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_57_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_58 */

#define CSL_GLBCE_REV_PERCEPT_LUT_58_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_58_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_58_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_58_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_58_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_58_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_59 */

#define CSL_GLBCE_REV_PERCEPT_LUT_59_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_59_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_59_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_59_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_59_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_59_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_60 */

#define CSL_GLBCE_REV_PERCEPT_LUT_60_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_60_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_60_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_60_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_60_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_60_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_61 */

#define CSL_GLBCE_REV_PERCEPT_LUT_61_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_61_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_61_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_61_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_61_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_61_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_62 */

#define CSL_GLBCE_REV_PERCEPT_LUT_62_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_62_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_62_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_62_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_62_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_62_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_63 */

#define CSL_GLBCE_REV_PERCEPT_LUT_63_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_63_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_63_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_63_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_63_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_63_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_REV_PERCEPT_LUT_64 */

#define CSL_GLBCE_REV_PERCEPT_LUT_64_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_REV_PERCEPT_LUT_64_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_64_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_REV_PERCEPT_LUT_64_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_REV_PERCEPT_LUT_64_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_REV_PERCEPT_LUT_64_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_00 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_00_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_00_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_00_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_00_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_00_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_00_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_01 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_01_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_01_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_01_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_01_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_01_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_01_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_02 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_02_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_02_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_02_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_02_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_02_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_02_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_03 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_03_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_03_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_03_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_03_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_03_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_03_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_04 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_04_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_04_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_04_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_04_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_04_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_04_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_05 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_05_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_05_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_05_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_05_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_05_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_05_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_06 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_06_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_06_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_06_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_06_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_06_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_06_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_07 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_07_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_07_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_07_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_07_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_07_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_07_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_08 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_08_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_08_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_08_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_08_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_08_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_08_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_09 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_09_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_09_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_09_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_09_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_09_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_09_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_10 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_10_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_10_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_10_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_10_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_10_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_10_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_11 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_11_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_11_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_11_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_11_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_11_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_11_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_12 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_12_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_12_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_12_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_12_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_12_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_12_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_13 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_13_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_13_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_13_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_13_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_13_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_13_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_14 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_14_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_14_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_14_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_14_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_14_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_14_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_15 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_15_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_15_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_15_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_15_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_15_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_15_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_16 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_16_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_16_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_16_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_16_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_16_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_16_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_17 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_17_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_17_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_17_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_17_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_17_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_17_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_18 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_18_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_18_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_18_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_18_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_18_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_18_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_19 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_19_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_19_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_19_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_19_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_19_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_19_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_20 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_20_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_20_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_20_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_20_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_20_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_20_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_21 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_21_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_21_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_21_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_21_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_21_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_21_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_22 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_22_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_22_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_22_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_22_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_22_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_22_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_23 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_23_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_23_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_23_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_23_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_23_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_23_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_24 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_24_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_24_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_24_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_24_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_24_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_24_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_25 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_25_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_25_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_25_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_25_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_25_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_25_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_26 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_26_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_26_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_26_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_26_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_26_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_26_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_27 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_27_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_27_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_27_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_27_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_27_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_27_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_28 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_28_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_28_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_28_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_28_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_28_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_28_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_29 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_29_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_29_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_29_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_29_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_29_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_29_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_30 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_30_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_30_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_30_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_30_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_30_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_30_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_31 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_31_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_31_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_31_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_31_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_31_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_31_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_32 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_32_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_32_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_32_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_32_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_32_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_32_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_33 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_33_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_33_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_33_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_33_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_33_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_33_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_34 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_34_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_34_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_34_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_34_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_34_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_34_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_35 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_35_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_35_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_35_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_35_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_35_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_35_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_36 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_36_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_36_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_36_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_36_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_36_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_36_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_37 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_37_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_37_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_37_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_37_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_37_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_37_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_38 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_38_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_38_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_38_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_38_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_38_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_38_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_39 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_39_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_39_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_39_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_39_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_39_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_39_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_40 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_40_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_40_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_40_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_40_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_40_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_40_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_41 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_41_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_41_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_41_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_41_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_41_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_41_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_42 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_42_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_42_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_42_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_42_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_42_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_42_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_43 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_43_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_43_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_43_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_43_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_43_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_43_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_44 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_44_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_44_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_44_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_44_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_44_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_44_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_45 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_45_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_45_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_45_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_45_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_45_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_45_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_46 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_46_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_46_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_46_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_46_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_46_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_46_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_47 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_47_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_47_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_47_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_47_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_47_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_47_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_48 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_48_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_48_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_48_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_48_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_48_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_48_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_49 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_49_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_49_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_49_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_49_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_49_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_49_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_50 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_50_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_50_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_50_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_50_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_50_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_50_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_51 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_51_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_51_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_51_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_51_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_51_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_51_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_52 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_52_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_52_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_52_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_52_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_52_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_52_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_53 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_53_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_53_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_53_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_53_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_53_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_53_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_54 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_54_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_54_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_54_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_54_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_54_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_54_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_55 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_55_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_55_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_55_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_55_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_55_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_55_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_56 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_56_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_56_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_56_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_56_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_56_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_56_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_57 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_57_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_57_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_57_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_57_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_57_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_57_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_58 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_58_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_58_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_58_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_58_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_58_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_58_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_59 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_59_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_59_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_59_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_59_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_59_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_59_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_60 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_60_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_60_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_60_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_60_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_60_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_60_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_61 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_61_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_61_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_61_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_61_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_61_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_61_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_62 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_62_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_62_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_62_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_62_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_62_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_62_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_63 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_63_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_63_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_63_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_63_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_63_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_63_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_FWD_PERCEPT_LUT_64 */

#define CSL_GLBCE_FWD_PERCEPT_LUT_64_VAL_MASK                        (0x0000FFFFU)
#define CSL_GLBCE_FWD_PERCEPT_LUT_64_VAL_SHIFT                       (0x00000000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_64_VAL_MAX                         (0x0000FFFFU)

#define CSL_GLBCE_FWD_PERCEPT_LUT_64_RESERVED_MASK                   (0xFFFF0000U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_64_RESERVED_SHIFT                  (0x00000010U)
#define CSL_GLBCE_FWD_PERCEPT_LUT_64_RESERVED_MAX                    (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_EN */

#define CSL_GLBCE_WDR_GAMMA_EN_EN_MASK                               (0x00000001U)
#define CSL_GLBCE_WDR_GAMMA_EN_EN_SHIFT                              (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_EN_EN_MAX                                (0x00000001U)

#define CSL_GLBCE_WDR_GAMMA_EN_RESERVED_MASK                         (0xFFFFFFFEU)
#define CSL_GLBCE_WDR_GAMMA_EN_RESERVED_SHIFT                        (0x00000001U)
#define CSL_GLBCE_WDR_GAMMA_EN_RESERVED_MAX                          (0x7FFFFFFFU)

/* GLBCE_WDR_GAMMA_LUT_00 */

#define CSL_GLBCE_WDR_GAMMA_LUT_00_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_00_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_00_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_00_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_00_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_00_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_01 */

#define CSL_GLBCE_WDR_GAMMA_LUT_01_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_01_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_01_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_01_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_01_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_01_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_02 */

#define CSL_GLBCE_WDR_GAMMA_LUT_02_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_02_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_02_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_02_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_02_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_02_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_03 */

#define CSL_GLBCE_WDR_GAMMA_LUT_03_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_03_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_03_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_03_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_03_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_03_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_04 */

#define CSL_GLBCE_WDR_GAMMA_LUT_04_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_04_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_04_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_04_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_04_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_04_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_05 */

#define CSL_GLBCE_WDR_GAMMA_LUT_05_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_05_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_05_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_05_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_05_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_05_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_06 */

#define CSL_GLBCE_WDR_GAMMA_LUT_06_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_06_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_06_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_06_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_06_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_06_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_07 */

#define CSL_GLBCE_WDR_GAMMA_LUT_07_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_07_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_07_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_07_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_07_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_07_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_08 */

#define CSL_GLBCE_WDR_GAMMA_LUT_08_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_08_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_08_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_08_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_08_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_08_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_09 */

#define CSL_GLBCE_WDR_GAMMA_LUT_09_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_09_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_09_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_09_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_09_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_09_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_10 */

#define CSL_GLBCE_WDR_GAMMA_LUT_10_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_10_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_10_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_10_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_10_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_10_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_11 */

#define CSL_GLBCE_WDR_GAMMA_LUT_11_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_11_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_11_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_11_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_11_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_11_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_12 */

#define CSL_GLBCE_WDR_GAMMA_LUT_12_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_12_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_12_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_12_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_12_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_12_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_13 */

#define CSL_GLBCE_WDR_GAMMA_LUT_13_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_13_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_13_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_13_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_13_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_13_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_14 */

#define CSL_GLBCE_WDR_GAMMA_LUT_14_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_14_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_14_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_14_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_14_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_14_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_15 */

#define CSL_GLBCE_WDR_GAMMA_LUT_15_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_15_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_15_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_15_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_15_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_15_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_16 */

#define CSL_GLBCE_WDR_GAMMA_LUT_16_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_16_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_16_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_16_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_16_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_16_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_17 */

#define CSL_GLBCE_WDR_GAMMA_LUT_17_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_17_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_17_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_17_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_17_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_17_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_18 */

#define CSL_GLBCE_WDR_GAMMA_LUT_18_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_18_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_18_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_18_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_18_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_18_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_19 */

#define CSL_GLBCE_WDR_GAMMA_LUT_19_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_19_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_19_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_19_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_19_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_19_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_20 */

#define CSL_GLBCE_WDR_GAMMA_LUT_20_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_20_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_20_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_20_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_20_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_20_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_21 */

#define CSL_GLBCE_WDR_GAMMA_LUT_21_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_21_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_21_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_21_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_21_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_21_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_22 */

#define CSL_GLBCE_WDR_GAMMA_LUT_22_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_22_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_22_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_22_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_22_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_22_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_23 */

#define CSL_GLBCE_WDR_GAMMA_LUT_23_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_23_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_23_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_23_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_23_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_23_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_24 */

#define CSL_GLBCE_WDR_GAMMA_LUT_24_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_24_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_24_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_24_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_24_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_24_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_25 */

#define CSL_GLBCE_WDR_GAMMA_LUT_25_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_25_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_25_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_25_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_25_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_25_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_26 */

#define CSL_GLBCE_WDR_GAMMA_LUT_26_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_26_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_26_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_26_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_26_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_26_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_27 */

#define CSL_GLBCE_WDR_GAMMA_LUT_27_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_27_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_27_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_27_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_27_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_27_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_28 */

#define CSL_GLBCE_WDR_GAMMA_LUT_28_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_28_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_28_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_28_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_28_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_28_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_29 */

#define CSL_GLBCE_WDR_GAMMA_LUT_29_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_29_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_29_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_29_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_29_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_29_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_30 */

#define CSL_GLBCE_WDR_GAMMA_LUT_30_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_30_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_30_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_30_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_30_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_30_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_31 */

#define CSL_GLBCE_WDR_GAMMA_LUT_31_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_31_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_31_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_31_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_31_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_31_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_32 */

#define CSL_GLBCE_WDR_GAMMA_LUT_32_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_32_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_32_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_32_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_32_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_32_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_33 */

#define CSL_GLBCE_WDR_GAMMA_LUT_33_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_33_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_33_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_33_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_33_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_33_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_34 */

#define CSL_GLBCE_WDR_GAMMA_LUT_34_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_34_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_34_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_34_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_34_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_34_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_35 */

#define CSL_GLBCE_WDR_GAMMA_LUT_35_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_35_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_35_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_35_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_35_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_35_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_36 */

#define CSL_GLBCE_WDR_GAMMA_LUT_36_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_36_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_36_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_36_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_36_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_36_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_37 */

#define CSL_GLBCE_WDR_GAMMA_LUT_37_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_37_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_37_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_37_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_37_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_37_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_38 */

#define CSL_GLBCE_WDR_GAMMA_LUT_38_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_38_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_38_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_38_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_38_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_38_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_39 */

#define CSL_GLBCE_WDR_GAMMA_LUT_39_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_39_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_39_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_39_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_39_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_39_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_40 */

#define CSL_GLBCE_WDR_GAMMA_LUT_40_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_40_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_40_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_40_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_40_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_40_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_41 */

#define CSL_GLBCE_WDR_GAMMA_LUT_41_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_41_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_41_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_41_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_41_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_41_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_42 */

#define CSL_GLBCE_WDR_GAMMA_LUT_42_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_42_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_42_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_42_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_42_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_42_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_43 */

#define CSL_GLBCE_WDR_GAMMA_LUT_43_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_43_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_43_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_43_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_43_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_43_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_44 */

#define CSL_GLBCE_WDR_GAMMA_LUT_44_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_44_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_44_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_44_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_44_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_44_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_45 */

#define CSL_GLBCE_WDR_GAMMA_LUT_45_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_45_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_45_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_45_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_45_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_45_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_46 */

#define CSL_GLBCE_WDR_GAMMA_LUT_46_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_46_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_46_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_46_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_46_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_46_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_47 */

#define CSL_GLBCE_WDR_GAMMA_LUT_47_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_47_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_47_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_47_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_47_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_47_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_48 */

#define CSL_GLBCE_WDR_GAMMA_LUT_48_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_48_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_48_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_48_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_48_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_48_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_49 */

#define CSL_GLBCE_WDR_GAMMA_LUT_49_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_49_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_49_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_49_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_49_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_49_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_50 */

#define CSL_GLBCE_WDR_GAMMA_LUT_50_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_50_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_50_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_50_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_50_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_50_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_51 */

#define CSL_GLBCE_WDR_GAMMA_LUT_51_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_51_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_51_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_51_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_51_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_51_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_52 */

#define CSL_GLBCE_WDR_GAMMA_LUT_52_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_52_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_52_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_52_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_52_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_52_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_53 */

#define CSL_GLBCE_WDR_GAMMA_LUT_53_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_53_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_53_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_53_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_53_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_53_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_54 */

#define CSL_GLBCE_WDR_GAMMA_LUT_54_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_54_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_54_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_54_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_54_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_54_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_55 */

#define CSL_GLBCE_WDR_GAMMA_LUT_55_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_55_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_55_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_55_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_55_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_55_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_56 */

#define CSL_GLBCE_WDR_GAMMA_LUT_56_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_56_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_56_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_56_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_56_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_56_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_57 */

#define CSL_GLBCE_WDR_GAMMA_LUT_57_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_57_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_57_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_57_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_57_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_57_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_58 */

#define CSL_GLBCE_WDR_GAMMA_LUT_58_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_58_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_58_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_58_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_58_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_58_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_59 */

#define CSL_GLBCE_WDR_GAMMA_LUT_59_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_59_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_59_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_59_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_59_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_59_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_60 */

#define CSL_GLBCE_WDR_GAMMA_LUT_60_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_60_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_60_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_60_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_60_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_60_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_61 */

#define CSL_GLBCE_WDR_GAMMA_LUT_61_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_61_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_61_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_61_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_61_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_61_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_62 */

#define CSL_GLBCE_WDR_GAMMA_LUT_62_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_62_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_62_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_62_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_62_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_62_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_63 */

#define CSL_GLBCE_WDR_GAMMA_LUT_63_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_63_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_63_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_63_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_63_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_63_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_64 */

#define CSL_GLBCE_WDR_GAMMA_LUT_64_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_64_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_64_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_64_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_64_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_64_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_65 */

#define CSL_GLBCE_WDR_GAMMA_LUT_65_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_65_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_65_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_65_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_65_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_65_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_66 */

#define CSL_GLBCE_WDR_GAMMA_LUT_66_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_66_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_66_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_66_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_66_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_66_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_67 */

#define CSL_GLBCE_WDR_GAMMA_LUT_67_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_67_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_67_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_67_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_67_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_67_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_68 */

#define CSL_GLBCE_WDR_GAMMA_LUT_68_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_68_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_68_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_68_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_68_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_68_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_69 */

#define CSL_GLBCE_WDR_GAMMA_LUT_69_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_69_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_69_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_69_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_69_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_69_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_70 */

#define CSL_GLBCE_WDR_GAMMA_LUT_70_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_70_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_70_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_70_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_70_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_70_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_71 */

#define CSL_GLBCE_WDR_GAMMA_LUT_71_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_71_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_71_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_71_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_71_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_71_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_72 */

#define CSL_GLBCE_WDR_GAMMA_LUT_72_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_72_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_72_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_72_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_72_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_72_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_73 */

#define CSL_GLBCE_WDR_GAMMA_LUT_73_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_73_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_73_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_73_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_73_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_73_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_74 */

#define CSL_GLBCE_WDR_GAMMA_LUT_74_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_74_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_74_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_74_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_74_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_74_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_75 */

#define CSL_GLBCE_WDR_GAMMA_LUT_75_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_75_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_75_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_75_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_75_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_75_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_76 */

#define CSL_GLBCE_WDR_GAMMA_LUT_76_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_76_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_76_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_76_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_76_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_76_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_77 */

#define CSL_GLBCE_WDR_GAMMA_LUT_77_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_77_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_77_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_77_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_77_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_77_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_78 */

#define CSL_GLBCE_WDR_GAMMA_LUT_78_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_78_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_78_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_78_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_78_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_78_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_79 */

#define CSL_GLBCE_WDR_GAMMA_LUT_79_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_79_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_79_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_79_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_79_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_79_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_80 */

#define CSL_GLBCE_WDR_GAMMA_LUT_80_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_80_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_80_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_80_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_80_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_80_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_81 */

#define CSL_GLBCE_WDR_GAMMA_LUT_81_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_81_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_81_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_81_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_81_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_81_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_82 */

#define CSL_GLBCE_WDR_GAMMA_LUT_82_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_82_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_82_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_82_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_82_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_82_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_83 */

#define CSL_GLBCE_WDR_GAMMA_LUT_83_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_83_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_83_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_83_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_83_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_83_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_84 */

#define CSL_GLBCE_WDR_GAMMA_LUT_84_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_84_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_84_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_84_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_84_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_84_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_85 */

#define CSL_GLBCE_WDR_GAMMA_LUT_85_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_85_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_85_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_85_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_85_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_85_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_86 */

#define CSL_GLBCE_WDR_GAMMA_LUT_86_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_86_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_86_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_86_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_86_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_86_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_87 */

#define CSL_GLBCE_WDR_GAMMA_LUT_87_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_87_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_87_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_87_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_87_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_87_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_88 */

#define CSL_GLBCE_WDR_GAMMA_LUT_88_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_88_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_88_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_88_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_88_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_88_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_89 */

#define CSL_GLBCE_WDR_GAMMA_LUT_89_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_89_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_89_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_89_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_89_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_89_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_90 */

#define CSL_GLBCE_WDR_GAMMA_LUT_90_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_90_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_90_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_90_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_90_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_90_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_91 */

#define CSL_GLBCE_WDR_GAMMA_LUT_91_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_91_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_91_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_91_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_91_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_91_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_92 */

#define CSL_GLBCE_WDR_GAMMA_LUT_92_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_92_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_92_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_92_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_92_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_92_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_93 */

#define CSL_GLBCE_WDR_GAMMA_LUT_93_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_93_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_93_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_93_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_93_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_93_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_94 */

#define CSL_GLBCE_WDR_GAMMA_LUT_94_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_94_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_94_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_94_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_94_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_94_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_95 */

#define CSL_GLBCE_WDR_GAMMA_LUT_95_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_95_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_95_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_95_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_95_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_95_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_96 */

#define CSL_GLBCE_WDR_GAMMA_LUT_96_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_96_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_96_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_96_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_96_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_96_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_97 */

#define CSL_GLBCE_WDR_GAMMA_LUT_97_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_97_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_97_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_97_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_97_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_97_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_98 */

#define CSL_GLBCE_WDR_GAMMA_LUT_98_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_98_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_98_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_98_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_98_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_98_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_99 */

#define CSL_GLBCE_WDR_GAMMA_LUT_99_VAL_MASK                          (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_99_VAL_SHIFT                         (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_99_VAL_MAX                           (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_99_RESERVED_MASK                     (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_99_RESERVED_SHIFT                    (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_99_RESERVED_MAX                      (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_100 */

#define CSL_GLBCE_WDR_GAMMA_LUT_100_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_100_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_100_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_100_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_100_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_100_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_101 */

#define CSL_GLBCE_WDR_GAMMA_LUT_101_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_101_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_101_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_101_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_101_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_101_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_102 */

#define CSL_GLBCE_WDR_GAMMA_LUT_102_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_102_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_102_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_102_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_102_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_102_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_103 */

#define CSL_GLBCE_WDR_GAMMA_LUT_103_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_103_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_103_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_103_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_103_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_103_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_104 */

#define CSL_GLBCE_WDR_GAMMA_LUT_104_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_104_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_104_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_104_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_104_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_104_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_105 */

#define CSL_GLBCE_WDR_GAMMA_LUT_105_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_105_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_105_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_105_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_105_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_105_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_106 */

#define CSL_GLBCE_WDR_GAMMA_LUT_106_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_106_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_106_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_106_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_106_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_106_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_107 */

#define CSL_GLBCE_WDR_GAMMA_LUT_107_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_107_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_107_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_107_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_107_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_107_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_108 */

#define CSL_GLBCE_WDR_GAMMA_LUT_108_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_108_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_108_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_108_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_108_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_108_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_109 */

#define CSL_GLBCE_WDR_GAMMA_LUT_109_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_109_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_109_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_109_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_109_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_109_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_110 */

#define CSL_GLBCE_WDR_GAMMA_LUT_110_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_110_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_110_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_110_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_110_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_110_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_111 */

#define CSL_GLBCE_WDR_GAMMA_LUT_111_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_111_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_111_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_111_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_111_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_111_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_112 */

#define CSL_GLBCE_WDR_GAMMA_LUT_112_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_112_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_112_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_112_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_112_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_112_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_113 */

#define CSL_GLBCE_WDR_GAMMA_LUT_113_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_113_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_113_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_113_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_113_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_113_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_114 */

#define CSL_GLBCE_WDR_GAMMA_LUT_114_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_114_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_114_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_114_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_114_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_114_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_115 */

#define CSL_GLBCE_WDR_GAMMA_LUT_115_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_115_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_115_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_115_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_115_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_115_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_116 */

#define CSL_GLBCE_WDR_GAMMA_LUT_116_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_116_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_116_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_116_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_116_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_116_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_117 */

#define CSL_GLBCE_WDR_GAMMA_LUT_117_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_117_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_117_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_117_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_117_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_117_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_118 */

#define CSL_GLBCE_WDR_GAMMA_LUT_118_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_118_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_118_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_118_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_118_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_118_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_119 */

#define CSL_GLBCE_WDR_GAMMA_LUT_119_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_119_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_119_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_119_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_119_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_119_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_120 */

#define CSL_GLBCE_WDR_GAMMA_LUT_120_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_120_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_120_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_120_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_120_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_120_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_121 */

#define CSL_GLBCE_WDR_GAMMA_LUT_121_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_121_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_121_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_121_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_121_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_121_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_122 */

#define CSL_GLBCE_WDR_GAMMA_LUT_122_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_122_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_122_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_122_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_122_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_122_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_123 */

#define CSL_GLBCE_WDR_GAMMA_LUT_123_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_123_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_123_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_123_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_123_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_123_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_124 */

#define CSL_GLBCE_WDR_GAMMA_LUT_124_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_124_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_124_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_124_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_124_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_124_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_125 */

#define CSL_GLBCE_WDR_GAMMA_LUT_125_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_125_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_125_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_125_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_125_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_125_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_126 */

#define CSL_GLBCE_WDR_GAMMA_LUT_126_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_126_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_126_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_126_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_126_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_126_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_127 */

#define CSL_GLBCE_WDR_GAMMA_LUT_127_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_127_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_127_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_127_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_127_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_127_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_128 */

#define CSL_GLBCE_WDR_GAMMA_LUT_128_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_128_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_128_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_128_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_128_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_128_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_129 */

#define CSL_GLBCE_WDR_GAMMA_LUT_129_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_129_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_129_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_129_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_129_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_129_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_130 */

#define CSL_GLBCE_WDR_GAMMA_LUT_130_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_130_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_130_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_130_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_130_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_130_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_131 */

#define CSL_GLBCE_WDR_GAMMA_LUT_131_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_131_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_131_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_131_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_131_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_131_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_132 */

#define CSL_GLBCE_WDR_GAMMA_LUT_132_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_132_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_132_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_132_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_132_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_132_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_133 */

#define CSL_GLBCE_WDR_GAMMA_LUT_133_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_133_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_133_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_133_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_133_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_133_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_134 */

#define CSL_GLBCE_WDR_GAMMA_LUT_134_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_134_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_134_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_134_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_134_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_134_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_135 */

#define CSL_GLBCE_WDR_GAMMA_LUT_135_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_135_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_135_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_135_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_135_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_135_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_136 */

#define CSL_GLBCE_WDR_GAMMA_LUT_136_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_136_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_136_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_136_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_136_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_136_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_137 */

#define CSL_GLBCE_WDR_GAMMA_LUT_137_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_137_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_137_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_137_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_137_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_137_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_138 */

#define CSL_GLBCE_WDR_GAMMA_LUT_138_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_138_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_138_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_138_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_138_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_138_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_139 */

#define CSL_GLBCE_WDR_GAMMA_LUT_139_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_139_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_139_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_139_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_139_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_139_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_140 */

#define CSL_GLBCE_WDR_GAMMA_LUT_140_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_140_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_140_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_140_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_140_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_140_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_141 */

#define CSL_GLBCE_WDR_GAMMA_LUT_141_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_141_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_141_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_141_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_141_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_141_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_142 */

#define CSL_GLBCE_WDR_GAMMA_LUT_142_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_142_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_142_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_142_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_142_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_142_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_143 */

#define CSL_GLBCE_WDR_GAMMA_LUT_143_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_143_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_143_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_143_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_143_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_143_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_144 */

#define CSL_GLBCE_WDR_GAMMA_LUT_144_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_144_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_144_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_144_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_144_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_144_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_145 */

#define CSL_GLBCE_WDR_GAMMA_LUT_145_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_145_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_145_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_145_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_145_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_145_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_146 */

#define CSL_GLBCE_WDR_GAMMA_LUT_146_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_146_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_146_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_146_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_146_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_146_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_147 */

#define CSL_GLBCE_WDR_GAMMA_LUT_147_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_147_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_147_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_147_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_147_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_147_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_148 */

#define CSL_GLBCE_WDR_GAMMA_LUT_148_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_148_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_148_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_148_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_148_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_148_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_149 */

#define CSL_GLBCE_WDR_GAMMA_LUT_149_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_149_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_149_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_149_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_149_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_149_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_150 */

#define CSL_GLBCE_WDR_GAMMA_LUT_150_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_150_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_150_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_150_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_150_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_150_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_151 */

#define CSL_GLBCE_WDR_GAMMA_LUT_151_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_151_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_151_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_151_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_151_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_151_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_152 */

#define CSL_GLBCE_WDR_GAMMA_LUT_152_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_152_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_152_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_152_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_152_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_152_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_153 */

#define CSL_GLBCE_WDR_GAMMA_LUT_153_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_153_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_153_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_153_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_153_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_153_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_154 */

#define CSL_GLBCE_WDR_GAMMA_LUT_154_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_154_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_154_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_154_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_154_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_154_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_155 */

#define CSL_GLBCE_WDR_GAMMA_LUT_155_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_155_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_155_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_155_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_155_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_155_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_156 */

#define CSL_GLBCE_WDR_GAMMA_LUT_156_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_156_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_156_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_156_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_156_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_156_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_157 */

#define CSL_GLBCE_WDR_GAMMA_LUT_157_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_157_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_157_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_157_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_157_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_157_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_158 */

#define CSL_GLBCE_WDR_GAMMA_LUT_158_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_158_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_158_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_158_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_158_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_158_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_159 */

#define CSL_GLBCE_WDR_GAMMA_LUT_159_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_159_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_159_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_159_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_159_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_159_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_160 */

#define CSL_GLBCE_WDR_GAMMA_LUT_160_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_160_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_160_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_160_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_160_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_160_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_161 */

#define CSL_GLBCE_WDR_GAMMA_LUT_161_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_161_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_161_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_161_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_161_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_161_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_162 */

#define CSL_GLBCE_WDR_GAMMA_LUT_162_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_162_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_162_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_162_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_162_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_162_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_163 */

#define CSL_GLBCE_WDR_GAMMA_LUT_163_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_163_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_163_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_163_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_163_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_163_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_164 */

#define CSL_GLBCE_WDR_GAMMA_LUT_164_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_164_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_164_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_164_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_164_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_164_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_165 */

#define CSL_GLBCE_WDR_GAMMA_LUT_165_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_165_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_165_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_165_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_165_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_165_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_166 */

#define CSL_GLBCE_WDR_GAMMA_LUT_166_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_166_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_166_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_166_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_166_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_166_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_167 */

#define CSL_GLBCE_WDR_GAMMA_LUT_167_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_167_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_167_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_167_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_167_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_167_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_168 */

#define CSL_GLBCE_WDR_GAMMA_LUT_168_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_168_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_168_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_168_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_168_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_168_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_169 */

#define CSL_GLBCE_WDR_GAMMA_LUT_169_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_169_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_169_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_169_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_169_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_169_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_170 */

#define CSL_GLBCE_WDR_GAMMA_LUT_170_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_170_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_170_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_170_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_170_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_170_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_171 */

#define CSL_GLBCE_WDR_GAMMA_LUT_171_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_171_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_171_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_171_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_171_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_171_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_172 */

#define CSL_GLBCE_WDR_GAMMA_LUT_172_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_172_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_172_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_172_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_172_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_172_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_173 */

#define CSL_GLBCE_WDR_GAMMA_LUT_173_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_173_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_173_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_173_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_173_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_173_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_174 */

#define CSL_GLBCE_WDR_GAMMA_LUT_174_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_174_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_174_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_174_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_174_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_174_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_175 */

#define CSL_GLBCE_WDR_GAMMA_LUT_175_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_175_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_175_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_175_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_175_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_175_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_176 */

#define CSL_GLBCE_WDR_GAMMA_LUT_176_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_176_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_176_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_176_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_176_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_176_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_177 */

#define CSL_GLBCE_WDR_GAMMA_LUT_177_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_177_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_177_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_177_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_177_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_177_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_178 */

#define CSL_GLBCE_WDR_GAMMA_LUT_178_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_178_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_178_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_178_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_178_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_178_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_179 */

#define CSL_GLBCE_WDR_GAMMA_LUT_179_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_179_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_179_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_179_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_179_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_179_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_180 */

#define CSL_GLBCE_WDR_GAMMA_LUT_180_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_180_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_180_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_180_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_180_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_180_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_181 */

#define CSL_GLBCE_WDR_GAMMA_LUT_181_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_181_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_181_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_181_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_181_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_181_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_182 */

#define CSL_GLBCE_WDR_GAMMA_LUT_182_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_182_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_182_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_182_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_182_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_182_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_183 */

#define CSL_GLBCE_WDR_GAMMA_LUT_183_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_183_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_183_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_183_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_183_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_183_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_184 */

#define CSL_GLBCE_WDR_GAMMA_LUT_184_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_184_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_184_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_184_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_184_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_184_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_185 */

#define CSL_GLBCE_WDR_GAMMA_LUT_185_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_185_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_185_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_185_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_185_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_185_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_186 */

#define CSL_GLBCE_WDR_GAMMA_LUT_186_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_186_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_186_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_186_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_186_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_186_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_187 */

#define CSL_GLBCE_WDR_GAMMA_LUT_187_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_187_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_187_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_187_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_187_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_187_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_188 */

#define CSL_GLBCE_WDR_GAMMA_LUT_188_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_188_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_188_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_188_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_188_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_188_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_189 */

#define CSL_GLBCE_WDR_GAMMA_LUT_189_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_189_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_189_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_189_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_189_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_189_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_190 */

#define CSL_GLBCE_WDR_GAMMA_LUT_190_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_190_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_190_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_190_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_190_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_190_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_191 */

#define CSL_GLBCE_WDR_GAMMA_LUT_191_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_191_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_191_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_191_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_191_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_191_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_192 */

#define CSL_GLBCE_WDR_GAMMA_LUT_192_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_192_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_192_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_192_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_192_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_192_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_193 */

#define CSL_GLBCE_WDR_GAMMA_LUT_193_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_193_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_193_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_193_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_193_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_193_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_194 */

#define CSL_GLBCE_WDR_GAMMA_LUT_194_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_194_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_194_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_194_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_194_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_194_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_195 */

#define CSL_GLBCE_WDR_GAMMA_LUT_195_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_195_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_195_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_195_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_195_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_195_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_196 */

#define CSL_GLBCE_WDR_GAMMA_LUT_196_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_196_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_196_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_196_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_196_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_196_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_197 */

#define CSL_GLBCE_WDR_GAMMA_LUT_197_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_197_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_197_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_197_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_197_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_197_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_198 */

#define CSL_GLBCE_WDR_GAMMA_LUT_198_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_198_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_198_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_198_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_198_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_198_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_199 */

#define CSL_GLBCE_WDR_GAMMA_LUT_199_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_199_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_199_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_199_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_199_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_199_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_200 */

#define CSL_GLBCE_WDR_GAMMA_LUT_200_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_200_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_200_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_200_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_200_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_200_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_201 */

#define CSL_GLBCE_WDR_GAMMA_LUT_201_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_201_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_201_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_201_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_201_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_201_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_202 */

#define CSL_GLBCE_WDR_GAMMA_LUT_202_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_202_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_202_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_202_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_202_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_202_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_203 */

#define CSL_GLBCE_WDR_GAMMA_LUT_203_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_203_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_203_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_203_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_203_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_203_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_204 */

#define CSL_GLBCE_WDR_GAMMA_LUT_204_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_204_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_204_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_204_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_204_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_204_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_205 */

#define CSL_GLBCE_WDR_GAMMA_LUT_205_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_205_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_205_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_205_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_205_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_205_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_206 */

#define CSL_GLBCE_WDR_GAMMA_LUT_206_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_206_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_206_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_206_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_206_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_206_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_207 */

#define CSL_GLBCE_WDR_GAMMA_LUT_207_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_207_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_207_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_207_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_207_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_207_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_208 */

#define CSL_GLBCE_WDR_GAMMA_LUT_208_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_208_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_208_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_208_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_208_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_208_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_209 */

#define CSL_GLBCE_WDR_GAMMA_LUT_209_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_209_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_209_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_209_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_209_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_209_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_210 */

#define CSL_GLBCE_WDR_GAMMA_LUT_210_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_210_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_210_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_210_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_210_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_210_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_211 */

#define CSL_GLBCE_WDR_GAMMA_LUT_211_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_211_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_211_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_211_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_211_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_211_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_212 */

#define CSL_GLBCE_WDR_GAMMA_LUT_212_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_212_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_212_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_212_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_212_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_212_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_213 */

#define CSL_GLBCE_WDR_GAMMA_LUT_213_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_213_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_213_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_213_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_213_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_213_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_214 */

#define CSL_GLBCE_WDR_GAMMA_LUT_214_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_214_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_214_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_214_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_214_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_214_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_215 */

#define CSL_GLBCE_WDR_GAMMA_LUT_215_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_215_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_215_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_215_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_215_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_215_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_216 */

#define CSL_GLBCE_WDR_GAMMA_LUT_216_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_216_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_216_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_216_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_216_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_216_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_217 */

#define CSL_GLBCE_WDR_GAMMA_LUT_217_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_217_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_217_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_217_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_217_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_217_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_218 */

#define CSL_GLBCE_WDR_GAMMA_LUT_218_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_218_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_218_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_218_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_218_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_218_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_219 */

#define CSL_GLBCE_WDR_GAMMA_LUT_219_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_219_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_219_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_219_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_219_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_219_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_220 */

#define CSL_GLBCE_WDR_GAMMA_LUT_220_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_220_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_220_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_220_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_220_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_220_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_221 */

#define CSL_GLBCE_WDR_GAMMA_LUT_221_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_221_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_221_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_221_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_221_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_221_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_222 */

#define CSL_GLBCE_WDR_GAMMA_LUT_222_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_222_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_222_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_222_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_222_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_222_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_223 */

#define CSL_GLBCE_WDR_GAMMA_LUT_223_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_223_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_223_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_223_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_223_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_223_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_224 */

#define CSL_GLBCE_WDR_GAMMA_LUT_224_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_224_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_224_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_224_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_224_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_224_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_225 */

#define CSL_GLBCE_WDR_GAMMA_LUT_225_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_225_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_225_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_225_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_225_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_225_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_226 */

#define CSL_GLBCE_WDR_GAMMA_LUT_226_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_226_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_226_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_226_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_226_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_226_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_227 */

#define CSL_GLBCE_WDR_GAMMA_LUT_227_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_227_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_227_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_227_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_227_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_227_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_228 */

#define CSL_GLBCE_WDR_GAMMA_LUT_228_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_228_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_228_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_228_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_228_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_228_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_229 */

#define CSL_GLBCE_WDR_GAMMA_LUT_229_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_229_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_229_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_229_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_229_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_229_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_230 */

#define CSL_GLBCE_WDR_GAMMA_LUT_230_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_230_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_230_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_230_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_230_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_230_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_231 */

#define CSL_GLBCE_WDR_GAMMA_LUT_231_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_231_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_231_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_231_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_231_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_231_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_232 */

#define CSL_GLBCE_WDR_GAMMA_LUT_232_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_232_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_232_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_232_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_232_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_232_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_233 */

#define CSL_GLBCE_WDR_GAMMA_LUT_233_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_233_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_233_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_233_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_233_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_233_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_234 */

#define CSL_GLBCE_WDR_GAMMA_LUT_234_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_234_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_234_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_234_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_234_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_234_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_235 */

#define CSL_GLBCE_WDR_GAMMA_LUT_235_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_235_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_235_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_235_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_235_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_235_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_236 */

#define CSL_GLBCE_WDR_GAMMA_LUT_236_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_236_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_236_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_236_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_236_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_236_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_237 */

#define CSL_GLBCE_WDR_GAMMA_LUT_237_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_237_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_237_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_237_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_237_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_237_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_238 */

#define CSL_GLBCE_WDR_GAMMA_LUT_238_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_238_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_238_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_238_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_238_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_238_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_239 */

#define CSL_GLBCE_WDR_GAMMA_LUT_239_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_239_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_239_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_239_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_239_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_239_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_240 */

#define CSL_GLBCE_WDR_GAMMA_LUT_240_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_240_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_240_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_240_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_240_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_240_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_241 */

#define CSL_GLBCE_WDR_GAMMA_LUT_241_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_241_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_241_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_241_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_241_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_241_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_242 */

#define CSL_GLBCE_WDR_GAMMA_LUT_242_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_242_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_242_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_242_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_242_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_242_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_243 */

#define CSL_GLBCE_WDR_GAMMA_LUT_243_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_243_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_243_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_243_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_243_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_243_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_244 */

#define CSL_GLBCE_WDR_GAMMA_LUT_244_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_244_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_244_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_244_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_244_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_244_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_245 */

#define CSL_GLBCE_WDR_GAMMA_LUT_245_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_245_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_245_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_245_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_245_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_245_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_246 */

#define CSL_GLBCE_WDR_GAMMA_LUT_246_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_246_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_246_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_246_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_246_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_246_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_247 */

#define CSL_GLBCE_WDR_GAMMA_LUT_247_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_247_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_247_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_247_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_247_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_247_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_248 */

#define CSL_GLBCE_WDR_GAMMA_LUT_248_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_248_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_248_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_248_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_248_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_248_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_249 */

#define CSL_GLBCE_WDR_GAMMA_LUT_249_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_249_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_249_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_249_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_249_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_249_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_250 */

#define CSL_GLBCE_WDR_GAMMA_LUT_250_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_250_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_250_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_250_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_250_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_250_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_251 */

#define CSL_GLBCE_WDR_GAMMA_LUT_251_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_251_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_251_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_251_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_251_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_251_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_252 */

#define CSL_GLBCE_WDR_GAMMA_LUT_252_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_252_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_252_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_252_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_252_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_252_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_253 */

#define CSL_GLBCE_WDR_GAMMA_LUT_253_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_253_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_253_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_253_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_253_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_253_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_254 */

#define CSL_GLBCE_WDR_GAMMA_LUT_254_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_254_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_254_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_254_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_254_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_254_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_255 */

#define CSL_GLBCE_WDR_GAMMA_LUT_255_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_255_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_255_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_255_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_255_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_255_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_WDR_GAMMA_LUT_256 */

#define CSL_GLBCE_WDR_GAMMA_LUT_256_VAL_MASK                         (0x0000FFFFU)
#define CSL_GLBCE_WDR_GAMMA_LUT_256_VAL_SHIFT                        (0x00000000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_256_VAL_MAX                          (0x0000FFFFU)

#define CSL_GLBCE_WDR_GAMMA_LUT_256_RESERVED_MASK                    (0xFFFF0000U)
#define CSL_GLBCE_WDR_GAMMA_LUT_256_RESERVED_SHIFT                   (0x00000010U)
#define CSL_GLBCE_WDR_GAMMA_LUT_256_RESERVED_MAX                     (0x0000FFFFU)

/* GLBCE_TILE_OUT_POS */

#define CSL_GLBCE_TILE_OUT_POS_LEFT_MASK                             (0x0000FFFFU)
#define CSL_GLBCE_TILE_OUT_POS_LEFT_SHIFT                            (0x00000000U)
#define CSL_GLBCE_TILE_OUT_POS_LEFT_MAX                              (0x0000FFFFU)

#define CSL_GLBCE_TILE_OUT_POS_TOP_MASK                              (0xFFFF0000U)
#define CSL_GLBCE_TILE_OUT_POS_TOP_SHIFT                             (0x00000010U)
#define CSL_GLBCE_TILE_OUT_POS_TOP_MAX                               (0x0000FFFFU)

/* GLBCE_TILE_OUT_SIZE */

#define CSL_GLBCE_TILE_OUT_SIZE_WIDTH_MASK                           (0x0000FFFFU)
#define CSL_GLBCE_TILE_OUT_SIZE_WIDTH_SHIFT                          (0x00000000U)
#define CSL_GLBCE_TILE_OUT_SIZE_WIDTH_MAX                            (0x0000FFFFU)

#define CSL_GLBCE_TILE_OUT_SIZE_HEIGHT_MASK                          (0xFFFF0000U)
#define CSL_GLBCE_TILE_OUT_SIZE_HEIGHT_SHIFT                         (0x00000010U)
#define CSL_GLBCE_TILE_OUT_SIZE_HEIGHT_MAX                           (0x0000FFFFU)

/* GLBCE_TILE_CONTROL */

#define CSL_GLBCE_TILE_CONTROL_RESERVED_MASK                         (0xFFFF8000U)
#define CSL_GLBCE_TILE_CONTROL_RESERVED_SHIFT                        (0x0000000FU)
#define CSL_GLBCE_TILE_CONTROL_RESERVED_MAX                          (0x0001FFFFU)

#define CSL_GLBCE_TILE_CONTROL_ENABLE_MASK                           (0x00000001U)
#define CSL_GLBCE_TILE_CONTROL_ENABLE_SHIFT                          (0x00000000U)
#define CSL_GLBCE_TILE_CONTROL_ENABLE_MAX                            (0x00000001U)

#define CSL_GLBCE_TILE_CONTROL_UPDATE_DSABLE_MASK                    (0x00000004U)
#define CSL_GLBCE_TILE_CONTROL_UPDATE_DSABLE_SHIFT                   (0x00000002U)
#define CSL_GLBCE_TILE_CONTROL_UPDATE_DSABLE_MAX                     (0x00000001U)

#define CSL_GLBCE_TILE_CONTROL_COLLECTION_DISABLE_MASK               (0x00000008U)
#define CSL_GLBCE_TILE_CONTROL_COLLECTION_DISABLE_SHIFT              (0x00000003U)
#define CSL_GLBCE_TILE_CONTROL_COLLECTION_DISABLE_MAX                (0x00000001U)

#define CSL_GLBCE_TILE_CONTROL_LAST_MASK                             (0x00000010U)
#define CSL_GLBCE_TILE_CONTROL_LAST_SHIFT                            (0x00000004U)
#define CSL_GLBCE_TILE_CONTROL_LAST_MAX                              (0x00000001U)

#define CSL_GLBCE_TILE_CONTROL_RESERVED1_MASK                        (0x00000002U)
#define CSL_GLBCE_TILE_CONTROL_RESERVED1_SHIFT                       (0x00000001U)
#define CSL_GLBCE_TILE_CONTROL_RESERVED1_MAX                         (0x00000001U)

#define CSL_GLBCE_TILE_CONTROL_RESERVED2_MASK                        (0x00007FE0U)
#define CSL_GLBCE_TILE_CONTROL_RESERVED2_SHIFT                       (0x00000005U)
#define CSL_GLBCE_TILE_CONTROL_RESERVED2_MAX                         (0x000003FFU)

/* GLBCE_OUTPUT_FLAGS */

#define CSL_GLBCE_OUTPUT_FLAGS_TILE_STATUS_MASK                      (0x0000FFFFU)
#define CSL_GLBCE_OUTPUT_FLAGS_TILE_STATUS_SHIFT                     (0x00000000U)
#define CSL_GLBCE_OUTPUT_FLAGS_TILE_STATUS_MAX                       (0x0000FFFFU)

#define CSL_GLBCE_OUTPUT_FLAGS_RESERVED_MASK                         (0xFFFF0000U)
#define CSL_GLBCE_OUTPUT_FLAGS_RESERVED_SHIFT                        (0x00000010U)
#define CSL_GLBCE_OUTPUT_FLAGS_RESERVED_MAX                          (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : GLBCE Statistics Memory config acccess
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t STATMEM[4096];             /* GLBCE Statastics memory */
} CSL_glbce_statmemRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_GLBCE_STATMEM_STATMEM(STATMEM)                                     (0x00000000U+((STATMEM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* STATMEM */

#define CSL_GLBCE_STATMEM_STATMEM_ODD_MASK                                     (0xFFFF0000U)
#define CSL_GLBCE_STATMEM_STATMEM_ODD_SHIFT                                    (0x00000010U)
#define CSL_GLBCE_STATMEM_STATMEM_ODD_MAX                                      (0x0000FFFFU)

#define CSL_GLBCE_STATMEM_STATMEM_EVEN_MASK                                    (0x0000FFFFU)
#define CSL_GLBCE_STATMEM_STATMEM_EVEN_SHIFT                                   (0x00000000U)
#define CSL_GLBCE_STATMEM_STATMEM_EVEN_MAX                                     (0x0000FFFFU)

#ifdef __cplusplus
}
#endif
#endif
