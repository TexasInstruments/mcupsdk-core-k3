/********************************************************************
 * Copyright (C) 2024 Texas Instruments Incorporated.
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
 *  VPVERSION   : 3.0.362 - 2023.09.22.21.39.55
 *  VPREV       : 2.23.4
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

#define CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG1_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG6_REGS_BASE                                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG7_REGS_BASE                                 (0x00000000U)


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
} CSL_main_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG0_PID                                       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1                                  (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS                           (0x00001010U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR                 (0x00001014U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE                               (0x00001018U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                         (0x0000101CU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI                                       (0x00001020U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS                             (0x00001024U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                         (0x00001028U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                         (0x0000102CU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR                               (0x00001030U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                        (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                       (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                         (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                       (0x000000C0U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                      (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                        (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                        (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                       (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                         (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_MASK                         (0x0000F800U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                        (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MISC_MAX                          (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                        (0xFFFF0000U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                       (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                         (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                  (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                   (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                    (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                   (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                     (0x00000001U)

/* INTR_RAW_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK             (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT            (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK             (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT            (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX              (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK            (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT           (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX             (0x00000001U)

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

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK              (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT             (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK              (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK              (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT             (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX               (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK             (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT            (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX              (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK    (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT   (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK    (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT   (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK    (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT   (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK   (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX    (0x00000001U)

/* EOI */

#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                       (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                        (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK             (0xFFFFFFFFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX              (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK         (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX          (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK           (0x00000040U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT          (0x00000006U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX            (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK       (0x000000FFU)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX        (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK      (0x000FFF00U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT     (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX       (0x00000FFFU)

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK          (0xFFF00000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT         (0x00000014U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX           (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK                (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX                 (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 1
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_256[256];
    volatile uint32_t IPC_SET[8];                /* IPC Generation Register 0 */
    volatile uint8_t  Resv_384[96];
    volatile uint32_t IPC_CLR[8];                /* IPC Acknowledge Register0 */
} CSL_main_ctrl_mmr_cfg1Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET(IPC_SET)                          (0x00000100U+((IPC_SET)*0x4U))
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR(IPC_CLR)                          (0x00000180U+((IPC_CLR)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* IPC_SET */

#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SET_MASK                      (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SET_SHIFT                     (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SET_MAX                       (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SRC_SET_MASK                  (0xFFFFFFF0U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SRC_SET_SHIFT                 (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_SET_IPC_SRC_SET_MAX                   (0x0FFFFFFFU)

/* IPC_CLR */

#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_CLR_MASK                      (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_CLR_SHIFT                     (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_CLR_MAX                       (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_SRC_CLR_MASK                  (0xFFFFFFF0U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_SRC_CLR_SHIFT                 (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG1_IPC_CLR_IPC_SRC_CLR_MAX                   (0x0FFFFFFFU)

/**************************************************************************
* Hardware Region  : MMRs in region 2
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_36864[36864];
    volatile uint32_t OBSCLK0_CTRL;              /* Observe Clock 0 Output Control Register */
    volatile uint8_t  Resv_36880[12];
    volatile uint32_t OBSCLK0_CLKDIV;            /* Observe Clock 0 Output Clock Divider Control Register */
    volatile uint8_t  Resv_40960[4076];
    volatile uint32_t CLKOUT_CLKSEL;             /* CLKOUT Clock Select Register */
    volatile uint8_t  Resv_45056[4092];
    volatile uint32_t EMMC0_CLKSEL;              /* eMMC0  Clock Select Register */
    volatile uint8_t  Resv_49152[4092];
    volatile uint32_t EMMC1_CLKSEL;              /* eMMC1  Clock Select Register */
    volatile uint8_t  Resv_53248[4092];
    volatile uint32_t EMMC2_CLKSEL;              /* eMMC2  Clock Select Register */
    volatile uint8_t  Resv_69632[16380];
    volatile uint32_t OSPI0_CLKSEL;              /* OSPI0 Clock Select Register */
    volatile uint8_t  Resv_81920[12284];
    volatile uint32_t GPMC_CLKSEL;               /* GPMC Clock Select Register */
    volatile uint8_t  Resv_86016[4092];
    volatile uint32_t TIMER0_CLKSEL;             /* Timer0 Clock Select Register */
    volatile uint8_t  Resv_90112[4092];
    volatile uint32_t TIMER1_CLKSEL;             /* Timer1 Clock Select Register */
    volatile uint8_t  Resv_94208[4092];
    volatile uint32_t TIMER2_CLKSEL;             /* Timer2 Clock Select Register */
    volatile uint8_t  Resv_98304[4092];
    volatile uint32_t TIMER3_CLKSEL;             /* Timer3 Clock Select Register */
    volatile uint8_t  Resv_118784[20476];
    volatile uint32_t WWD0_CLKSEL;               /* WWD0 Clock Select Register */
    volatile uint8_t  Resv_122880[4092];
    volatile uint32_t WWD1_CLKSEL;               /* WWD1 Clock Select Register */
    volatile uint8_t  Resv_155648[32764];
    volatile uint32_t SPI0_CLKSEL;               /* SPI0 Clock Select Register */
    volatile uint8_t  Resv_159744[4092];
    volatile uint32_t SPI1_CLKSEL;               /* SPI1 Clock Select Register */
    volatile uint8_t  Resv_163840[4092];
    volatile uint32_t SPI2_CLKSEL;               /* SPI2 Clock Select Register */
    volatile uint8_t  Resv_167936[4092];
    volatile uint32_t SPI3_CLKSEL;               /* SPI3 Clock Select Register */
    volatile uint8_t  Resv_188416[20476];
    volatile uint32_t USART0_CLKDIV;             /* USART0 Functional Clock Control */
    volatile uint8_t  Resv_192512[4092];
    volatile uint32_t USART1_CLKDIV;             /* USART1 Functional Clock Control */
    volatile uint8_t  Resv_196608[4092];
    volatile uint32_t USART2_CLKDIV;             /* USART2 Functional Clock Control */
    volatile uint8_t  Resv_200704[4092];
    volatile uint32_t USART3_CLKDIV;             /* USART3 Functional Clock Control */
    volatile uint8_t  Resv_204800[4092];
    volatile uint32_t USART4_CLKDIV;             /* USART4 Functional Clock Control */
    volatile uint8_t  Resv_208896[4092];
    volatile uint32_t USART5_CLKDIV;             /* USART5 Functional Clock Control */
    volatile uint8_t  Resv_212992[4092];
    volatile uint32_t USART6_CLKDIV;             /* USART6 Functional Clock Control */
    volatile uint8_t  Resv_253952[40956];
    volatile uint32_t CPSW0_CLKSEL;              /* CPSW0 Clock Select Register */
    volatile uint8_t  Resv_262144[8188];
    volatile uint32_t MCAN0_CLKSEL;              /* MCAN0 Clock Select Register */
    volatile uint8_t  Resv_266240[4092];
    volatile uint32_t MCAN1_CLKSEL;              /* MCAN1 Clock Select Register */
    volatile uint8_t  Resv_270336[4092];
    volatile uint32_t MCAN2_CLKSEL;              /* MCAN2 Clock Select Register */
    volatile uint8_t  Resv_294912[24572];
    volatile uint32_t AUDIO_REFCLK0_CLKSEL;      /* Audio External Reference Clock Select */
    volatile uint8_t  Resv_294928[12];
    volatile uint32_t AUDIO_REFCLK1_CLKSEL;      /* Audio External Reference Clock Select */
    volatile uint8_t  Resv_299008[4076];
    volatile uint32_t MCASP0_CLKSEL;             /* McASP0 Clock Select Register */
    volatile uint8_t  Resv_299264[252];
    volatile uint32_t MCASP0_AHCLKSEL;           /* McASP0 AHClock Select Register */
    volatile uint8_t  Resv_303104[3836];
    volatile uint32_t MCASP1_CLKSEL;             /* McASP1 Clock Select Register */
    volatile uint8_t  Resv_303360[252];
    volatile uint32_t MCASP1_AHCLKSEL;           /* McASP1 AHClock Select Register */
    volatile uint8_t  Resv_307200[3836];
    volatile uint32_t MCASP2_CLKSEL;             /* McASP2 Clock Select Register */
    volatile uint8_t  Resv_307456[252];
    volatile uint32_t MCASP2_AHCLKSEL;           /* McASP2 AHClock Select Register */
    volatile uint8_t  Resv_372736[65276];
    volatile uint32_t DSS0_DISPC0_CLKSEL;        /* DSS Display Controller Clock Select Register */
    volatile uint8_t  Resv_405504[32764];
    volatile uint32_t DPHY0_CLKSEL;              /* DSI0 PHY Clock Select Register */
    volatile uint8_t  Resv_430080[24572];
    volatile uint32_t ADC0_CLKSEL;               /* ADC0 Clock Select Register */
} CSL_main_ctrl_mmr_cfg2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL                              (0x00009000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV                            (0x00009010U)
#define CSL_MAIN_CTRL_MMR_CFG2_CLKOUT_CLKSEL                             (0x0000A000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC0_CLKSEL                              (0x0000B000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC1_CLKSEL                              (0x0000C000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC2_CLKSEL                              (0x0000D000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OSPI0_CLKSEL                              (0x00011000U)
#define CSL_MAIN_CTRL_MMR_CFG2_GPMC_CLKSEL                               (0x00014000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER0_CLKSEL                             (0x00015000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER1_CLKSEL                             (0x00016000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER2_CLKSEL                             (0x00017000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER3_CLKSEL                             (0x00018000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL                               (0x0001D000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL                               (0x0001E000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI0_CLKSEL                               (0x00026000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI1_CLKSEL                               (0x00027000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI2_CLKSEL                               (0x00028000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI3_CLKSEL                               (0x00029000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV                             (0x0002E000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV                             (0x0002F000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV                             (0x00030000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV                             (0x00031000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV                             (0x00032000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV                             (0x00033000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV                             (0x00034000U)
#define CSL_MAIN_CTRL_MMR_CFG2_CPSW0_CLKSEL                              (0x0003E000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN0_CLKSEL                              (0x00040000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN1_CLKSEL                              (0x00041000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN2_CLKSEL                              (0x00042000U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK0_CLKSEL                      (0x00048000U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK1_CLKSEL                      (0x00048010U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_CLKSEL                             (0x00049000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL                           (0x00049100U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_CLKSEL                             (0x0004A000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL                           (0x0004A100U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_CLKSEL                             (0x0004B000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL                           (0x0004B100U)
#define CSL_MAIN_CTRL_MMR_CFG2_DSS0_DISPC0_CLKSEL                        (0x0005B000U)
#define CSL_MAIN_CTRL_MMR_CFG2_DPHY0_CLKSEL                              (0x00063000U)
#define CSL_MAIN_CTRL_MMR_CFG2_ADC0_CLKSEL                               (0x00069000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* OBSCLK0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_CLK_SEL_MASK                 (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_CLK_SEL_MAX                  (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_OUT_MUX_SEL_MASK             (0x01000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_OUT_MUX_SEL_SHIFT            (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CTRL_OUT_MUX_SEL_MAX              (0x00000001U)

/* OBSCLK0_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_MASK               (0x0000FF00U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_MAX                (0x000000FFU)

#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_LD_MASK            (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_LD_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_OBSCLK0_CLKDIV_CLK_DIV_LD_MAX             (0x00000001U)

/* CLKOUT_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_CLKOUT_CLKSEL_CLK_SEL_MASK                (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_CLKOUT_CLKSEL_CLK_SEL_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_CLKOUT_CLKSEL_CLK_SEL_MAX                 (0x00000001U)

/* EMMC0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC0_CLKSEL_EMMCSD_REFCLK_SEL_MAX        (0x00000001U)

/* EMMC1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC1_CLKSEL_EMMCSD_REFCLK_SEL_MAX        (0x00000001U)

/* EMMC2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_EMMC2_CLKSEL_EMMCSD_REFCLK_SEL_MAX        (0x00000001U)

/* OSPI0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_OSPI0_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_OSPI0_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_OSPI0_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/* GPMC_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_GPMC_CLKSEL_CLK_SEL_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_GPMC_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_GPMC_CLKSEL_CLK_SEL_MAX                   (0x00000001U)

/* TIMER0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_TIMER0_CLKSEL_CLK_SEL_MASK                (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER0_CLKSEL_CLK_SEL_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER0_CLKSEL_CLK_SEL_MAX                 (0x0000000FU)

/* TIMER1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_TIMER1_CLKSEL_CLK_SEL_MASK                (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER1_CLKSEL_CLK_SEL_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER1_CLKSEL_CLK_SEL_MAX                 (0x0000000FU)

/* TIMER2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_TIMER2_CLKSEL_CLK_SEL_MASK                (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER2_CLKSEL_CLK_SEL_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER2_CLKSEL_CLK_SEL_MAX                 (0x0000000FU)

/* TIMER3_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_TIMER3_CLKSEL_CLK_SEL_MASK                (0x0000000FU)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER3_CLKSEL_CLK_SEL_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_TIMER3_CLKSEL_CLK_SEL_MAX                 (0x0000000FU)

/* WWD0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_CLK_SEL_MASK                  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_CLK_SEL_MAX                   (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_WRTLOCK_MASK                  (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_WRTLOCK_SHIFT                 (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD0_CLKSEL_WRTLOCK_MAX                   (0x00000001U)

/* WWD1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_CLK_SEL_MASK                  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_CLK_SEL_MAX                   (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_WRTLOCK_MASK                  (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_WRTLOCK_SHIFT                 (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG2_WWD1_CLKSEL_WRTLOCK_MAX                   (0x00000001U)

/* SPI0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_SPI0_CLKSEL_MSTR_LB_CLKSEL_MASK           (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI0_CLKSEL_MSTR_LB_CLKSEL_SHIFT          (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI0_CLKSEL_MSTR_LB_CLKSEL_MAX            (0x00000001U)

/* SPI1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_SPI1_CLKSEL_MSTR_LB_CLKSEL_MASK           (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI1_CLKSEL_MSTR_LB_CLKSEL_SHIFT          (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI1_CLKSEL_MSTR_LB_CLKSEL_MAX            (0x00000001U)

/* SPI2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_SPI2_CLKSEL_MSTR_LB_CLKSEL_MASK           (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI2_CLKSEL_MSTR_LB_CLKSEL_SHIFT          (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI2_CLKSEL_MSTR_LB_CLKSEL_MAX            (0x00000001U)

/* SPI3_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_SPI3_CLKSEL_MSTR_LB_CLKSEL_MASK           (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI3_CLKSEL_MSTR_LB_CLKSEL_SHIFT          (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_SPI3_CLKSEL_MSTR_LB_CLKSEL_MAX            (0x00000001U)

/* USART0_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART0_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART1_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART1_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART2_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART2_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART3_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART3_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART4_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART4_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART5_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART5_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* USART6_CLKDIV */

#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_MASK                (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_SHIFT               (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_MAX                 (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_LD_MASK             (0x00010000U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_LD_SHIFT            (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG2_USART6_CLKDIV_CLK_DIV_LD_MAX              (0x00000001U)

/* CPSW0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_CPSW0_CLKSEL_CPTS_CLKSEL_MASK             (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG2_CPSW0_CLKSEL_CPTS_CLKSEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_CPSW0_CLKSEL_CPTS_CLKSEL_MAX              (0x00000007U)

/* MCAN0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCAN0_CLKSEL_CLK_SEL_MASK                 (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN0_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN0_CLKSEL_CLK_SEL_MAX                  (0x00000003U)

/* MCAN1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCAN1_CLKSEL_CLK_SEL_MASK                 (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN1_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN1_CLKSEL_CLK_SEL_MAX                  (0x00000003U)

/* MCAN2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCAN2_CLKSEL_CLK_SEL_MASK                 (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN2_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCAN2_CLKSEL_CLK_SEL_MAX                  (0x00000003U)

/* AUDIO_REFCLK0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK0_CLKSEL_CLK_SEL_MASK         (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK0_CLKSEL_CLK_SEL_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK0_CLKSEL_CLK_SEL_MAX          (0x00000007U)

/* AUDIO_REFCLK1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK1_CLKSEL_CLK_SEL_MASK         (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK1_CLKSEL_CLK_SEL_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_AUDIO_REFCLK1_CLKSEL_CLK_SEL_MAX          (0x00000007U)

/* MCASP0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_CLKSEL_AUXCLK_SEL_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_CLKSEL_AUXCLK_SEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_CLKSEL_AUXCLK_SEL_MAX              (0x00000001U)

/* MCASP0_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKR_SEL_MASK           (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKR_SEL_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKR_SEL_MAX            (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKX_SEL_MASK           (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKX_SEL_SHIFT          (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP0_AHCLKSEL_AHCLKX_SEL_MAX            (0x00000003U)

/* MCASP1_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_CLKSEL_AUXCLK_SEL_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_CLKSEL_AUXCLK_SEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_CLKSEL_AUXCLK_SEL_MAX              (0x00000001U)

/* MCASP1_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKR_SEL_MASK           (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKR_SEL_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKR_SEL_MAX            (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKX_SEL_MASK           (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKX_SEL_SHIFT          (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP1_AHCLKSEL_AHCLKX_SEL_MAX            (0x00000003U)

/* MCASP2_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_CLKSEL_AUXCLK_SEL_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_CLKSEL_AUXCLK_SEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_CLKSEL_AUXCLK_SEL_MAX              (0x00000001U)

/* MCASP2_AHCLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKR_SEL_MASK           (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKR_SEL_SHIFT          (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKR_SEL_MAX            (0x00000003U)

#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKX_SEL_MASK           (0x00000300U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKX_SEL_SHIFT          (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG2_MCASP2_AHCLKSEL_AHCLKX_SEL_MAX            (0x00000003U)

/* DSS0_DISPC0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_DSS0_DISPC0_CLKSEL_DPI0_PCLK_MASK         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_DSS0_DISPC0_CLKSEL_DPI0_PCLK_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_DSS0_DISPC0_CLKSEL_DPI0_PCLK_MAX          (0x00000001U)

/* DPHY0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_DPHY0_CLKSEL_REF_CLK_SEL_MASK             (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG2_DPHY0_CLKSEL_REF_CLK_SEL_SHIFT            (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_DPHY0_CLKSEL_REF_CLK_SEL_MAX              (0x00000001U)

/* ADC0_CLKSEL */

#define CSL_MAIN_CTRL_MMR_CFG2_ADC0_CLKSEL_CLK_SEL_MASK                  (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG2_ADC0_CLKSEL_CLK_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG2_ADC0_CLKSEL_CLK_SEL_MAX                   (0x00000003U)

/**************************************************************************
* Hardware Region  : MMRs in region 3
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_45056[45056];
    volatile uint32_t EMMC0_CTRL;                /* EMMC0 Control Register */
    volatile uint32_t EMMC0_STAT;                /* Status of EMMC0 Module */
    volatile uint8_t  Resv_49152[4088];
    volatile uint32_t EMMC1_CTRL;                /* EMMC1 Control Register */
    volatile uint32_t EMMC1_STAT;                /* Status of EMMC1 Module */
    volatile uint8_t  Resv_53248[4088];
    volatile uint32_t EMMC2_CTRL;                /* EMMC2 Control Register */
    volatile uint32_t EMMC2_STAT;                /* Status of EMMC2 Module */
    volatile uint8_t  Resv_69632[16376];
    volatile uint32_t OSPI0_CTRL;                /* OSPI0 Clock Loopback Control Register */
    volatile uint8_t  Resv_69888[252];
    volatile uint32_t FSS_CTRL;                  /* Flash Subsystem Control Register */
    volatile uint8_t  Resv_90112[20220];
    volatile uint32_t TIMER1_CTRL;               /* TIMER1 Control Register */
    volatile uint8_t  Resv_98304[8188];
    volatile uint32_t TIMER3_CTRL;               /* TIMER3 Control Register */
    volatile uint8_t  Resv_229376[131068];
    volatile uint32_t I2C2_CTRL;                 /* I2C2 Control Register */
    volatile uint8_t  Resv_253952[24572];
    volatile uint32_t CPSW0_PORT0_CTRL;          /* CPSW0 Port0 Control Register */
    volatile uint32_t CPSW0_PORT1_CTRL;          /* CPSW0 Port1 Control Register */
    volatile uint8_t  Resv_405760[151800];
    volatile uint32_t DPHY_TX0_CTRL;             /* Video Transmit MIPI DPHY0 Lane0 Control Register */
    volatile uint8_t  Resv_430080[24316];
    volatile uint32_t ADC0_CTRL;                 /* ADC0 Control Register */
    volatile uint8_t  Resv_430096[12];
    volatile uint32_t ADC0_TRIM;                 /* ADC0 TRIM Register */
    volatile uint8_t  Resv_430336[236];
    volatile uint32_t EPWM_TB_CLKEN;             /* EPWM Time Base Clock Activate Register */
    volatile uint8_t  Resv_430592[252];
    volatile uint32_t EPWM0_CTRL;                /* PWM0 Control Register */
    volatile uint8_t  Resv_430608[12];
    volatile uint32_t EPWM1_CTRL;                /* PWM1 Control Register */
    volatile uint8_t  Resv_430624[12];
    volatile uint32_t EPWM2_CTRL;                /* PWM2 Control Register */
    volatile uint8_t  Resv_430848[220];
    volatile uint32_t EQEP0_CTRL;                /* EQEP SOCA Select Register */
    volatile uint32_t EQEP1_CTRL;                /* EQEP SOCA Select Register */
    volatile uint32_t EQEP2_CTRL;                /* EQEP SOCA Select Register */
} CSL_main_ctrl_mmr_cfg3Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_CTRL                                (0x0000B000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_STAT                                (0x0000B004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_CTRL                                (0x0000C000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_STAT                                (0x0000C004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_CTRL                                (0x0000D000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_STAT                                (0x0000D004U)
#define CSL_MAIN_CTRL_MMR_CFG3_OSPI0_CTRL                                (0x00011000U)
#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL                                  (0x00011100U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER1_CTRL                               (0x00016000U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER3_CTRL                               (0x00018000U)
#define CSL_MAIN_CTRL_MMR_CFG3_I2C2_CTRL                                 (0x00038000U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL                          (0x0003E000U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL                          (0x0003E004U)
#define CSL_MAIN_CTRL_MMR_CFG3_DPHY_TX0_CTRL                             (0x00063100U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_CTRL                                 (0x00069000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM                                 (0x00069010U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN                             (0x00069100U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL                                (0x00069200U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM1_CTRL                                (0x00069210U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM2_CTRL                                (0x00069220U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP0_CTRL                                (0x00069300U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP1_CTRL                                (0x00069304U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP2_CTRL                                (0x00069308U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* EMMC0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_CTRL_EMMCSD_IO_CLKLB_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_CTRL_EMMCSD_IO_CLKLB_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_CTRL_EMMCSD_IO_CLKLB_SEL_MAX        (0x00000001U)

/* EMMC0_STAT */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_STAT_SIG1P8_EN_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_STAT_SIG1P8_EN_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC0_STAT_SIG1P8_EN_MAX                  (0x00000001U)

/* EMMC1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_CTRL_EMMCSD_IO_CLKLB_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_CTRL_EMMCSD_IO_CLKLB_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_CTRL_EMMCSD_IO_CLKLB_SEL_MAX        (0x00000001U)

/* EMMC1_STAT */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_STAT_SIG1P8_EN_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_STAT_SIG1P8_EN_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC1_STAT_SIG1P8_EN_MAX                  (0x00000001U)

/* EMMC2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_CTRL_EMMCSD_IO_CLKLB_SEL_MASK       (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_CTRL_EMMCSD_IO_CLKLB_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_CTRL_EMMCSD_IO_CLKLB_SEL_MAX        (0x00000001U)

/* EMMC2_STAT */

#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_STAT_SIG1P8_EN_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_STAT_SIG1P8_EN_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EMMC2_STAT_SIG1P8_EN_MAX                  (0x00000001U)

/* OSPI0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_OSPI0_CTRL_LOOPCLK_SEL_MASK               (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_OSPI0_CTRL_LOOPCLK_SEL_SHIFT              (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_OSPI0_CTRL_LOOPCLK_SEL_MAX                (0x00000001U)

/* FSS_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SEG_MASK                 (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SEG_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SEG_MAX                  (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SIZE_MASK                (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SIZE_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG3_FSS_CTRL_S0_BOOT_SIZE_MAX                 (0x00000001U)

/* TIMER1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_TIMER1_CTRL_CASCADE_EN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER1_CTRL_CASCADE_EN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER1_CTRL_CASCADE_EN_MAX                (0x00000001U)

/* TIMER3_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_TIMER3_CTRL_CASCADE_EN_MASK               (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER3_CTRL_CASCADE_EN_SHIFT              (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG3_TIMER3_CTRL_CASCADE_EN_MAX                (0x00000001U)

/* I2C2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_I2C2_CTRL_HS_MCS_EN_MASK                  (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_I2C2_CTRL_HS_MCS_EN_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_I2C2_CTRL_HS_MCS_EN_MAX                   (0x00000001U)

/* CPSW0_PORT0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_PORT_MODE_SEL_MASK       (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_PORT_MODE_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_PORT_MODE_SEL_MAX        (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_RGMII_ID_MODE_MASK       (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_RGMII_ID_MODE_SHIFT      (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT0_CTRL_RGMII_ID_MODE_MAX        (0x00000001U)

/* CPSW0_PORT1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_PORT_MODE_SEL_MASK       (0x00000007U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_PORT_MODE_SEL_SHIFT      (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_PORT_MODE_SEL_MAX        (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_RGMII_ID_MODE_MASK       (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_RGMII_ID_MODE_SHIFT      (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_CPSW0_PORT1_CTRL_RGMII_ID_MODE_MAX        (0x00000001U)

/* DPHY_TX0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_DPHY_TX0_CTRL_LANE_FUNC_SEL_MASK          (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG3_DPHY_TX0_CTRL_LANE_FUNC_SEL_SHIFT         (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_DPHY_TX0_CTRL_LANE_FUNC_SEL_MAX           (0x00000003U)

/* ADC0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_CTRL_TRIG_SEL_MASK                   (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_CTRL_TRIG_SEL_SHIFT                  (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_CTRL_TRIG_SEL_MAX                    (0x0000001FU)

/* ADC0_TRIM */

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CAL_MASK               (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CAL_SHIFT              (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CAL_MAX                (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CALB_MASK              (0x000003E0U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CALB_SHIFT             (0x00000005U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_ACTIVATE_CALB_MAX               (0x0000001FU)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM1_MASK                      (0x00003C00U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM1_SHIFT                     (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM1_MAX                       (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM2_MASK                      (0x0003C000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM2_SHIFT                     (0x0000000EU)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM2_MAX                       (0x0000000FU)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM3_MASK                      (0x001C0000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM3_SHIFT                     (0x00000012U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM3_MAX                       (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM4_MASK                      (0x00E00000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM4_SHIFT                     (0x00000015U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM4_MAX                       (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM5_MASK                      (0x07000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM5_SHIFT                     (0x00000018U)
#define CSL_MAIN_CTRL_MMR_CFG3_ADC0_TRIM_TRIM5_MAX                       (0x00000007U)

/* EPWM_TB_CLKEN */

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_MASK         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_SHIFT        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM0_TB_CLKEN_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_MASK         (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_SHIFT        (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM1_TB_CLKEN_MAX          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_MASK         (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_SHIFT        (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM_TB_CLKEN_EPWM2_TB_CLKEN_MAX          (0x00000001U)

/* EPWM0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_EALLOW_MASK                    (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_EALLOW_SHIFT                   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_EALLOW_MAX                     (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_SYNCIN_SEL_MASK                (0x00000700U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_SYNCIN_SEL_SHIFT               (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM0_CTRL_SYNCIN_SEL_MAX                 (0x00000007U)

/* EPWM1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM1_CTRL_EALLOW_MASK                    (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM1_CTRL_EALLOW_SHIFT                   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM1_CTRL_EALLOW_MAX                     (0x00000001U)

/* EPWM2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EPWM2_CTRL_EALLOW_MASK                    (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM2_CTRL_EALLOW_SHIFT                   (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG3_EPWM2_CTRL_EALLOW_MAX                     (0x00000001U)

/* EQEP0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EQEP0_CTRL_SOCA_SEL_MASK                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP0_CTRL_SOCA_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP0_CTRL_SOCA_SEL_MAX                   (0x0000001FU)

/* EQEP1_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EQEP1_CTRL_SOCA_SEL_MASK                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP1_CTRL_SOCA_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP1_CTRL_SOCA_SEL_MAX                   (0x0000001FU)

/* EQEP2_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG3_EQEP2_CTRL_SOCA_SEL_MASK                  (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP2_CTRL_SOCA_SEL_SHIFT                 (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG3_EQEP2_CTRL_SOCA_SEL_MAX                   (0x0000001FU)

/**************************************************************************
* Hardware Region  : MMRs in region 5
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_4112[4112];
    volatile uint32_t RST_STAT;                  /* Reset Status Register */
    volatile uint8_t  Resv_4128[12];
    volatile uint32_t RST_SRC;                   /* Reset Source Register */
    volatile uint8_t  Resv_32768[28636];
    volatile uint32_t GLDTC0_CTRL;               /* Power Glitch Detect Control Register */
    volatile uint32_t GLDTC0_STAT;               /* Power Glitch Detect Status Register */
} CSL_main_ctrl_mmr_cfg5Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG5_RST_STAT                                  (0x00001010U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC                                   (0x00001020U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL                               (0x00008000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT                               (0x00008004U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RST_STAT */

#define CSL_MAIN_CTRL_MMR_CFG5_RST_STAT_RESET_ISO_DONE_Z_MASK            (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_STAT_RESET_ISO_DONE_Z_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_STAT_RESET_ISO_DONE_Z_MAX             (0x00000001U)

/* RST_SRC */

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC0_MASK                         (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC0_SHIFT                        (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC0_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC1_MASK                         (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC1_SHIFT                        (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC1_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC2_MASK                         (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC2_SHIFT                        (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC2_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC3_MASK                         (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC3_SHIFT                        (0x00000003U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC3_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC4_MASK                         (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC4_SHIFT                        (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC4_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC5_MASK                         (0x00000020U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC5_SHIFT                        (0x00000005U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC5_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC9_MASK                         (0x00000200U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC9_SHIFT                        (0x00000009U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC9_MAX                          (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC10_MASK                        (0x00000400U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC10_SHIFT                       (0x0000000AU)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC10_MAX                         (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC11_MASK                        (0x00000800U)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC11_SHIFT                       (0x0000000BU)
#define CSL_MAIN_CTRL_MMR_CFG5_RST_SRC_SRC11_MAX                         (0x00000001U)

/* GLDTC0_CTRL */

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_LO_SEL_MASK            (0x0000003FU)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_LO_SEL_SHIFT           (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_LO_SEL_MAX             (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_HI_SEL_MASK            (0x00003F00U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_HI_SEL_SHIFT           (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_THRESH_HI_SEL_MAX             (0x0000003FU)

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_LP_FILTER_SEL_MASK            (0x00070000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_LP_FILTER_SEL_SHIFT           (0x00000010U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_LP_FILTER_SEL_MAX             (0x00000007U)

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_RSTB_MASK                     (0x40000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_RSTB_SHIFT                    (0x0000001EU)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_RSTB_MAX                      (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_PWDB_MASK                     (0x80000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_PWDB_SHIFT                    (0x0000001FU)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_CTRL_PWDB_MAX                      (0x00000001U)

/* GLDTC0_STAT */

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_LOW_FLAG_MASK          (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_LOW_FLAG_SHIFT         (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_LOW_FLAG_MAX           (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_HI_FLAG_MASK           (0x00000100U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_HI_FLAG_SHIFT          (0x00000008U)
#define CSL_MAIN_CTRL_MMR_CFG5_GLDTC0_STAT_THRESH_HI_FLAG_MAX            (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 6
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_364544[364544];
    volatile uint32_t EQEP_STAT;                 /* EQEP Status Register */
} CSL_main_ctrl_mmr_cfg6Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT                                 (0x00059000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* EQEP_STAT */

#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR0_MASK                 (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR0_SHIFT                (0x00000000U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR0_MAX                  (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR1_MASK                 (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR1_SHIFT                (0x00000001U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR1_MAX                  (0x00000001U)

#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR2_MASK                 (0x00000004U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR2_SHIFT                (0x00000002U)
#define CSL_MAIN_CTRL_MMR_CFG6_EQEP_STAT_PHASE_ERR2_MAX                  (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 7
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
} CSL_main_ctrl_mmr_cfg7Regs;


/**************************************************************************
* Register Macros
**************************************************************************/


/**************************************************************************
* Field Definition Macros
**************************************************************************/


#ifdef __cplusplus
}
#endif
#endif