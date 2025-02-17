/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
 */

#ifndef SCMI_DEVICES_H
#define SCMI_DEVICES_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define AM62LX_DEV_ADC0                             0
#define AM62LX_DEV_MAIN_GPIOMUX_INTROUTER0          1
#define AM62LX_DEV_TIMESYNC_INTROUTER0              2
#define AM62LX_DEV_CPSW0                            3
#define AM62LX_DEV_CPT2_AGGR0                       4
#define AM62LX_DEV_CPT2_AGGR1                       5
#define AM62LX_DEV_WKUP_CPT2_AGGR0                  6
#define AM62LX_DEV_STM0                             7
#define AM62LX_DEV_DEBUGSS_WRAP0                    8
#define AM62LX_DEV_DMASS0                           9
#define AM62LX_DEV_DMASS0_BCDMA_0                   10
#define AM62LX_DEV_DMASS0_PKTDMA_0                  11
#define AM62LX_DEV_WKUP_DMASS0                      12
#define AM62LX_DEV_WKUP_DMASS0_DTHE                 13
#define AM62LX_DEV_WKUP_DMASS0_XLCDMA_0             14
#define AM62LX_DEV_TIMER0                           15
#define AM62LX_DEV_TIMER1                           16
#define AM62LX_DEV_TIMER2                           17
#define AM62LX_DEV_TIMER3                           18
#define AM62LX_DEV_WKUP_TIMER0                      19
#define AM62LX_DEV_WKUP_TIMER1                      20
#define AM62LX_DEV_WKUP_SMS_LITE0                   21
#define AM62LX_DEV_ECAP0                            22
#define AM62LX_DEV_ECAP1                            23
#define AM62LX_DEV_ECAP2                            24
#define AM62LX_DEV_ELM0                             25
#define AM62LX_DEV_MMCSD1                           26
#define AM62LX_DEV_MMCSD2                           27
#define AM62LX_DEV_MMCSD0                           28
#define AM62LX_DEV_EQEP0                            29
#define AM62LX_DEV_EQEP1                            30
#define AM62LX_DEV_EQEP2                            31
#define AM62LX_DEV_FSS0                             32
#define AM62LX_DEV_GICSS0                           33
#define AM62LX_DEV_GPIO0                            34
#define AM62LX_DEV_GPIO2                            35
#define AM62LX_DEV_WKUP_GPIO0                       36
#define AM62LX_DEV_GPMC0                            37
#define AM62LX_DEV_DSS_DSI0                         38
#define AM62LX_DEV_DSS0                             39
#define AM62LX_DEV_EPWM0                            40
#define AM62LX_DEV_EPWM1                            41
#define AM62LX_DEV_EPWM2                            42
#define AM62LX_DEV_LED0                             43
#define AM62LX_DEV_PBIST0                           44
#define AM62LX_DEV_WKUP_PBIST0                      45
#define AM62LX_DEV_WKUP_VTM0                        46
#define AM62LX_DEV_MCAN0                            47
#define AM62LX_DEV_MCAN1                            48
#define AM62LX_DEV_MCAN2                            49
#define AM62LX_DEV_MCASP0                           50
#define AM62LX_DEV_MCASP1                           51
#define AM62LX_DEV_MCASP2                           52
#define AM62LX_DEV_I2C0                             53
#define AM62LX_DEV_I2C1                             54
#define AM62LX_DEV_I2C2                             55
#define AM62LX_DEV_I2C3                             56
#define AM62LX_DEV_WKUP_I2C0                        57
#define AM62LX_DEV_WKUP_GTC0                        58
#define AM62LX_DEV_WKUP_RTCSS0                      59
#define AM62LX_DEV_RTI0                             60
#define AM62LX_DEV_RTI1                             61
#define AM62LX_DEV_DEBUGSS0                         62
#define AM62LX_DEV_MSRAM_96K0                       63
#define AM62LX_DEV_WKUP_PSRAM_64K0                  64
#define AM62LX_DEV_ROM0                             65
#define AM62LX_DEV_PSC0                             66
#define AM62LX_DEV_WKUP_DEEPSLEEP_SOURCES0          67
#define AM62LX_DEV_MCU_MCU_16FF0                    68
#define AM62LX_DEV_COMPUTE_CLUSTER0_ARM_COREPACK_0  69
#define AM62LX_DEV_DDR16SS0                         70
#define AM62LX_DEV_WKUP_DFTSS0                      71
#define AM62LX_DEV_MCSPI0                           72
#define AM62LX_DEV_MCSPI1                           73
#define AM62LX_DEV_MCSPI2                           74
#define AM62LX_DEV_MCSPI3                           75
#define AM62LX_DEV_TRNG_DRBG_EIP76D_WRAP0           76
#define AM62LX_DEV_UART1                            77
#define AM62LX_DEV_UART2                            78
#define AM62LX_DEV_UART3                            79
#define AM62LX_DEV_UART4                            80
#define AM62LX_DEV_UART5                            81
#define AM62LX_DEV_UART6                            82
#define AM62LX_DEV_WKUP_UART0                       83
#define AM62LX_DEV_USB0                             84
#define AM62LX_DEV_USB1                             85
#define AM62LX_DEV_DPHY_TX0                         86
#define AM62LX_DEV_COMPUTE_CLUSTER0_CLKDIV_0        87
#define AM62LX_DEV_COMPUTE_CLUSTER0_PBIST_0         88
#define AM62LX_DEV_UART0                            89
#define AM62LX_DEV_BOARD0                           90
#define AM62LX_DEV_WKUP_GTCCLK_SEL_DEV_VD           91
#define AM62LX_DEV_WKUP_OBSCLK_MUX_SEL_DEV_VD       92
#define AM62LX_DEV_WKUP_CLKOUT_SEL_DEV_VD           93
#define AM62LX_DEV_OBSCLK0_MUX_SEL_DEV_VD           94
#define AM62LX_DEV_MAIN_USB0_ISO_VD                 95
#define AM62LX_DEV_MAIN_USB1_ISO_VD                 96
#define AM62LX_DEV_CLK_32K_RC_SEL_DEV_VD            97

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* SCMI_DEVICES_H */

/** @} */
