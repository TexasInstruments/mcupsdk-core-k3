/********************************************************************
*
* MCU_M4FSS0_CORE0 INTERRUPT MAP. header file
*
* Copyright (C) 2023 Texas Instruments Incorporated.
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
#ifndef SDLR_MCU_M4FSS0_CORE0_INTERRUPT_MAP_H_
#define SDLR_MCU_M4FSS0_CORE0_INTERRUPT_MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: MCU_M4FSS0_CORE0
*/
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_MCU_GPIOMUX_INTROUTER0_OUTP_4                              (0U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_MCU_GPIOMUX_INTROUTER0_OUTP_5                              (1U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_MCU_GPIOMUX_INTROUTER0_OUTP_6                              (2U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_MCU_GPIOMUX_INTROUTER0_OUTP_7                              (3U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_TIMER0_INTR_PEND_0                                          (4U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_TIMER1_INTR_PEND_0                                          (5U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_TIMER2_INTR_PEND_0                                          (6U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_TIMER3_INTR_PEND_0                                          (7U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_7                               (8U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MAINRESET_REQUEST_GLUE_MAIN_RESETZ_SYNC_STRETCH_0     (9U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MAINRESET_REQUEST_GLUE_MAIN_PORZ_SYNC_STRETCH_0       (10U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_ESM0_ESM_INT_CFG_LVL_0                                     (11U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_ESM0_ESM_INT_HI_LVL_0                                      (12U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_ESM0_ESM_INT_LOW_LVL_0                                     (13U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_M4FSS0_RAT_0_EXP_INTR_0                                     (14U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MAIN_GPIOMUX_INTROUTER0_OUTP_34                                 (15U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MAIN_GPIOMUX_INTROUTER0_OUTP_35                                 (16U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_I2C0_POINTRPEND_0                                           (17U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DDPA0_DDPA_INTR_0                                               (18U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_RTI0_INTR_WWD_0                                             (19U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_PSC0_PSC_ALLINT_0                                          (20U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_DCC0_INTR_DONE_LEVEL_0                                      (21U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCSPI0_INTR_SPI_0                                           (22U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCSPI1_INTR_SPI_0                                           (23U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_UART0_USART_IRQ_0                                           (24U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCRC64_0_INT_MCRC_0                                         (25U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_SMS0_TIFS_CBASS_0_FW_EXCEPTION_INTR_0                           (26U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_SMS0_COMMON_0_COMBINED_SEC_IN_0                                 (27U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_LT_TH0_INTR_0                      (28U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH1_INTR_0                      (29U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH2_INTR_0                      (30U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MCU_CBASS_INTR_OR_GLUE_OUT_0                          (31U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_168                         (32U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_169                         (33U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_170                         (34U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_171                         (35U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_EPWM0_EPWM_ETINT_0                                              (36U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_EPWM1_EPWM_ETINT_0                                              (37U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_EPWM2_EPWM_ETINT_0                                              (38U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MCU_ACCESS_ERR_INTR_GLUE_OUT_0                        (39U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DSS0_DISPC_INTR_REQ_0_0                                         (40U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DSS0_DISPC_INTR_REQ_1_0                                         (41U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN0_COMMON_0_MCANSS_EXT_TS_ROLLOVER_LVL_INT_0             (42U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN0_COMMON_0_MCANSS_MCAN_LVL_INT_0                        (43U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN0_COMMON_0_MCANSS_MCAN_LVL_INT_1                        (44U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN1_COMMON_0_MCANSS_EXT_TS_ROLLOVER_LVL_INT_0             (45U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN1_COMMON_0_MCANSS_MCAN_LVL_INT_0                        (46U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MCU_MCAN1_COMMON_0_MCANSS_MCAN_LVL_INT_1                        (47U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_SMS0_AESEIP38T_0_AES_SINTREQUEST_P_0                            (48U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_SMS0_AESEIP38T_0_AES_SINTREQUEST_S_0                            (49U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_MAILBOX0_CLUSTER_0_MAILBOX_CLUSTER_PEND_2                       (50U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_ICSSM0_COMMON_0_PR1_HOST_INTR_PEND_6                            (51U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_ICSSM0_COMMON_0_PR1_HOST_INTR_PEND_7                            (52U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_ICSSM0_COMMON_0_ISO_RESET_PROTCOL_ACK_0                         (53U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_172                         (54U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_173                         (55U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_174                         (56U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_DMASS0_INTAGGR_0_INTAGGR_VINTR_PEND_175                         (57U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_CMP_EVENT_INTROUTER0_OUTP_34                                    (58U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_CMP_EVENT_INTROUTER0_OUTP_35                                    (59U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_CMP_EVENT_INTROUTER0_OUTP_36                                    (60U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_CMP_EVENT_INTROUTER0_OUTP_37                                    (61U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_SGASKET_INTR_GLUE_OUT_0                               (62U)
#define SDLR_MCU_M4FSS0_CORE0_NVIC_GLUELOGIC_MGASKET_INTR_GLUE_OUT_0                               (63U)


#ifdef __cplusplus
}
#endif
#endif /* SDLR_MCU_M4FSS0_CORE0_INTERRUPT_MAP_H_ */
