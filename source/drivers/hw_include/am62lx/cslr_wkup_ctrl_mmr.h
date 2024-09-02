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
 *  VPVERSION   : 3.0.362 - 2023.09.22.21.39.55
 *  VPREV       : 2.23.4
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

#define CSL_WKUP_CTRL_MMR_CFG0_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG6_REGS_BASE                                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG7_REGS_BASE                                 (0x00000000U)


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
    volatile uint8_t  Resv_20[8];
    volatile uint32_t JTAGID;                    /* JTAG / DEVICE ID Register */
    volatile uint32_t JTAG_USER_ID;              /* JTAG User Code ID Register */
    volatile uint8_t  Resv_96[68];
    volatile uint32_t DEVICE_FEATURE0;           /* Device Feature Register 0 */
    volatile uint8_t  Resv_4112[4012];
    volatile uint32_t INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    volatile uint32_t INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    volatile uint32_t INTR_ENABLE;               /* Interrupt Enable register */
    volatile uint32_t INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    volatile uint32_t EOI;                       /* EOI register */
    volatile uint32_t FAULT_ADDRESS;             /* Fault Address register */
    volatile uint32_t FAULT_TYPE_STATUS;         /* Fault Type Status register */
    volatile uint32_t FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    volatile uint32_t FAULT_CLEAR;               /* Fault Clear register */
    volatile uint8_t  Resv_8192[4044];
    volatile uint32_t MAC_ID0;                   /* MAC Address Lo register */
    volatile uint32_t MAC_ID1;                   /* MAC Address Hi Register */
    volatile uint8_t  Resv_16384[8184];
    volatile uint32_t USB_DEVICE_ID0;            /* USB Device ID Register0 */
    volatile uint32_t USB_DEVICE_ID1;            /* USB Device ID Register1 */
    volatile uint8_t  Resv_20480[4088];
    volatile uint32_t GP_SW0;                    /* General Purpose Software Fuse Value 0 */
    volatile uint32_t GP_SW1;                    /* General Purpose Software Fuse Value 1 */
    volatile uint32_t GP_SW2;                    /* General Purpose Software Fuse Value 2 */
    volatile uint32_t GP_SW3;                    /* General Purpose Software Fuse Value 3 */
} CSL_wkup_ctrl_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG0_PID                                       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1                                  (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID                                    (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID                              (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0                           (0x00000060U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS                           (0x00001010U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLED_STATUS_CLEAR                 (0x00001014U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE                               (0x00001018U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR                         (0x0000101CU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI                                       (0x00001020U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS                             (0x00001024U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS                         (0x00001028U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS                         (0x0000102CU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR                               (0x00001030U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0                                   (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1                                   (0x00002004U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0                            (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1                            (0x00004004U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0                                    (0x00005000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1                                    (0x00005004U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2                                    (0x00005008U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3                                    (0x0000500CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_MASK                        (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_SHIFT                       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MINOR_MAX                         (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_MASK                       (0x000000C0U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_SHIFT                      (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_CUSTOM_MAX                        (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_MASK                        (0x00000700U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_SHIFT                       (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MAJOR_MAX                         (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_MASK                         (0x0000F800U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_SHIFT                        (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MISC_MAX                          (0x0000001FU)

#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_MASK                        (0xFFFF0000U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_SHIFT                       (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_PID_PID_MSB16_MAX                         (0x0000FFFFU)

/* MMR_CFG1 */

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MASK                  (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PARTITIONS_MAX                   (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MASK                    (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_SHIFT                   (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG0_MMR_CFG1_PROXY_EN_MAX                     (0x00000001U)

/* JTAGID */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_MASK                           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_SHIFT                          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_LSB_MAX                            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_MASK                           (0x00000FFEU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_SHIFT                          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_MFG_MAX                            (0x000007FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_MASK                        (0x0FFFF000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_SHIFT                       (0x0000000CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_PARTNO_MAX                         (0x0000FFFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_MASK                       (0xF0000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_SHIFT                      (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT_MAX                        (0x0000000FU)

/* JTAG_USER_ID */

#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_MASK                (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_JTAG_USER_ID_USERCODE_MAX                 (0xFFFFFFFFU)

/* DEVICE_FEATURE0 */

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_MASK   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE0_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_MASK   (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_SHIFT  (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE1_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_MASK   (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_SHIFT  (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE2_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_MASK   (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_SHIFT  (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MPU_CLUSTER0_CORE3_MAX    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MCUSS_MASK                (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MCUSS_SHIFT               (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_MCUSS_MAX                 (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DLA_MASK                  (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DLA_SHIFT                 (0x0000000DU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DLA_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DSP_MASK                  (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DSP_SHIFT                 (0x0000000EU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_DSP_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_ISP_MASK                  (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_ISP_SHIFT                 (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_ISP_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VENC_MASK                 (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VENC_SHIFT                (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VENC_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VDEC_MASK                 (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VDEC_SHIFT                (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_VDEC_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_GPU_MASK                  (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_GPU_SHIFT                 (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_GPU_MAX                   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PRU_MASK                  (0x00200000U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PRU_SHIFT                 (0x00000015U)
#define CSL_WKUP_CTRL_MMR_CFG0_DEVICE_FEATURE0_PRU_MAX                   (0x00000001U)

/* INTR_RAW_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MASK             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROT_ERR_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MASK             (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_SHIFT            (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_ADDR_ERR_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MASK             (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_SHIFT            (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_KICK_ERR_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MASK            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_SHIFT           (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_RAW_STATUS_PROXY_ERR_MAX             (0x00000001U)

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

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROT_ERR_EN_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MASK              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_SHIFT             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_ADDR_ERR_EN_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MASK              (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_SHIFT             (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_KICK_ERR_EN_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MASK             (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_SHIFT            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_PROXY_ERR_EN_MAX              (0x00000001U)

/* INTR_ENABLE_CLEAR */

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MASK    (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_SHIFT   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROT_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MASK    (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_SHIFT   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_ADDR_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MASK    (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_SHIFT   (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_KICK_ERR_EN_CLR_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MASK   (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_SHIFT  (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG0_INTR_ENABLE_CLEAR_PROXY_ERR_EN_CLR_MAX    (0x00000001U)

/* EOI */

#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MASK                       (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_SHIFT                      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_EOI_EOI_VECTOR_MAX                        (0x000000FFU)

/* FAULT_ADDRESS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MASK             (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ADDRESS_FAULT_ADDR_MAX              (0xFFFFFFFFU)

/* FAULT_TYPE_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MASK         (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_TYPE_MAX          (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MASK           (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_SHIFT          (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_TYPE_STATUS_FAULT_NS_MAX            (0x00000001U)

/* FAULT_ATTR_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MASK       (0x000000FFU)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_PRIVID_MAX        (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MASK      (0x000FFF00U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_SHIFT     (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_ROUTEID_MAX       (0x00000FFFU)

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MASK          (0xFFF00000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_SHIFT         (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_ATTR_STATUS_FAULT_XID_MAX           (0x00000FFFU)

/* FAULT_CLEAR */

#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MASK                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_FAULT_CLEAR_FAULT_CLR_MAX                 (0x00000001U)

/* MAC_ID0 */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_MASK                     (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID0_MACID_LO_MAX                      (0xFFFFFFFFU)

/* MAC_ID1 */

#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_MASK                     (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MAC_ID1_MACID_HI_MAX                      (0x0000FFFFU)

/* USB_DEVICE_ID0 */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_MASK                   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID0_ID0_MAX                    (0xFFFFFFFFU)

/* USB_DEVICE_ID1 */

#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_MASK                   (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_USB_DEVICE_ID1_ID1_MAX                    (0xFFFFFFFFU)

/* GP_SW0 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_MASK                           (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_SHIFT                          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW0_VAL_MAX                            (0xFFFFFFFFU)

/* GP_SW1 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_MASK                           (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_SHIFT                          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW1_VAL_MAX                            (0xFFFFFFFFU)

/* GP_SW2 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_MASK                           (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_SHIFT                          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW2_VAL_MAX                            (0xFFFFFFFFU)

/* GP_SW3 */

#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_MASK                           (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_SHIFT                          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_GP_SW3_VAL_MAX                            (0x0000000FU)

/**************************************************************************
* Hardware Region  : MMRs in region 1
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t DEVICE_TYPE;               /* Device Type/Subtype */
    volatile uint8_t  Resv_48[44];
    volatile uint32_t DEVSTAT;                   /* Device Status Register */
    volatile uint32_t BOOTCFG;                   /* Boot Configuration Register */
    volatile uint8_t  Resv_68[12];
    volatile uint32_t BOOT_PROGRESS;             /* ROM Boot Progress Register */
    volatile uint8_t  Resv_128[56];
    volatile uint32_t BOOTMODE_EFUSE[2];         /* EFUSE Boot Modeundefined */
    volatile uint8_t  Resv_160[24];
    volatile uint32_t BOOTMODE_EFUSE_RAW[2];     /* EFUSE Boot Modeundefined Uncorrected */
    volatile uint8_t  Resv_176[8];
    volatile uint32_t BOOTMODE_PINS_RAW;         /* Boot Mode Pins Unmodified */
    volatile uint8_t  Resv_4096[3916];
    volatile uint32_t FUSE_CTRL_STAT;            /* MAIN eFuse Controller Status MMR */
    volatile uint8_t  Resv_4128[28];
    volatile uint32_t FUSE_CRC_STAT;             /* MAIN eFuse CRC Status Register */
    volatile uint8_t  Resv_4356[224];
    volatile uint32_t CHAIN1_CRC_CALC;           /* MAIN eFuse Chain1 Calc CRC Register */
    volatile uint8_t  Resv_4612[252];
    volatile uint32_t CHAIN1_CRC_CALC_RO;        /* MAIN eFuse Chain1 Calc CRC Register - Read Only */
    volatile uint8_t  Resv_4868[252];
    volatile uint32_t CHAIN1_CRC_FUSE;           /* MAIN eFuse Chain1 CRC Register */
} CSL_wkup_ctrl_mmr_cfg1Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG1_DEVICE_TYPE                               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT                                   (0x00000030U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTCFG                                   (0x00000034U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOT_PROGRESS                             (0x00000044U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE(BOOTMODE_EFUSE)            (0x00000080U+((BOOTMODE_EFUSE)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_RAW(BOOTMODE_EFUSE_RAW)    (0x000000A0U+((BOOTMODE_EFUSE_RAW)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_PINS_RAW                         (0x000000B0U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT                            (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CRC_STAT                             (0x00001020U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC                           (0x00001104U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_RO                        (0x00001204U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_FUSE                           (0x00001304U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DEVICE_TYPE */

#define CSL_WKUP_CTRL_MMR_CFG1_DEVICE_TYPE_SMS_DEV_TYPE_MASK             (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG1_DEVICE_TYPE_SMS_DEV_TYPE_SHIFT            (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG1_DEVICE_TYPE_SMS_DEV_TYPE_MAX              (0x0000000FU)

/* DEVSTAT */

#define CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT_BOOTMODE_MASK                     (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT_BOOTMODE_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_DEVSTAT_BOOTMODE_MAX                      (0x0000FFFFU)

/* BOOTCFG */

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTCFG_BOOTMODE_MASK                     (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTCFG_BOOTMODE_SHIFT                    (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTCFG_BOOTMODE_MAX                      (0x0000FFFFU)

/* BOOT_PROGRESS */

#define CSL_WKUP_CTRL_MMR_CFG1_BOOT_PROGRESS_PROGRESS_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOT_PROGRESS_PROGRESS_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOT_PROGRESS_PROGRESS_MAX                (0xFFFFFFFFU)

/* BOOTMODE_EFUSE */

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_BOOTMODE_MASK              (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_BOOTMODE_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_BOOTMODE_MAX               (0x0000FFFFU)

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_SEC_MASK                   (0x40000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_SEC_SHIFT                  (0x0000001EU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_SEC_MAX                    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_DED_MASK                   (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_DED_SHIFT                  (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_DED_MAX                    (0x00000001U)

/* BOOTMODE_EFUSE_RAW */

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_RAW_BOOTMODE_MASK          (0x01FFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_RAW_BOOTMODE_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_EFUSE_RAW_BOOTMODE_MAX           (0x01FFFFFFU)

/* BOOTMODE_PINS_RAW */

#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_PINS_RAW_BOOTMODE_MASK           (0x0000FFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_PINS_RAW_BOOTMODE_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_BOOTMODE_PINS_RAW_BOOTMODE_MAX            (0x0000FFFFU)

/* FUSE_CTRL_STAT */

#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_MASK        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_0_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_MASK        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_SHIFT       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_1_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_MASK        (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_SHIFT       (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_2_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_MASK        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_SHIFT       (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CTRL_STAT_AUTOLOAD_ERR_3_MAX         (0x00000001U)

/* FUSE_CRC_STAT */

#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CRC_STAT_CRC_ERR_1_MASK              (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CRC_STAT_CRC_ERR_1_SHIFT             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG1_FUSE_CRC_STAT_CRC_ERR_1_MAX               (0x00000001U)

/* CHAIN1_CRC_CALC */

#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_CRC_MASK                  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_CRC_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_CRC_MAX                   (0xFFFFFFFFU)

/* CHAIN1_CRC_CALC_RO */

#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_RO_CRC_MASK               (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_RO_CRC_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_CALC_RO_CRC_MAX                (0xFFFFFFFFU)

/* CHAIN1_CRC_FUSE */

#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_FUSE_CRC_MASK                  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_FUSE_CRC_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG1_CHAIN1_CRC_FUSE_CRC_MAX                   (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : MMRs in region 2
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_256[256];
    volatile uint32_t CLK_32K_RC_CLKSEL;         /* Device 32KHz Clock Select Register */
    volatile uint8_t  Resv_264[4];
    volatile uint32_t RC12M_OSC_TRIM;            /* 12.5 MHz RC Oscillator Trim Register */
    volatile uint8_t  Resv_320[52];
    volatile uint32_t HFOSC0_TRIM;               /* Oscillator0 Trim Register */
    volatile uint8_t  Resv_328[4];
    volatile uint32_t HFOSC0_CLKOUT_32K_CTRL;    /* Control for 32K Clock Divider from HFOSC0 */
    volatile uint32_t HFOSC0_CTRL;               /* Oscillator0 Control Register */
    volatile uint8_t  Resv_512[176];
    volatile uint32_t WKUP_OBSCLK0_CLKSEL;       /* WKUP OBSCLK0 Pin Clock Select Register */
    volatile uint32_t WKUP_OBSCLK0_OUTMUX_SEL;   /* WKUP OBSCLK0 Pin Final Clock Select Register */
    volatile uint32_t WKUP_OBSCLK0_CLKDIV;       /* WKUP Observe Clock 0 Output Clock Divider Control Register */
    volatile uint8_t  Resv_4096[3572];
    volatile uint32_t WKUP_GTC_OUTMUX_SEL;       /* GTC Clock Select Register - Dynamic Configuration */
    volatile uint8_t  Resv_8192[4092];
    volatile uint32_t WKUP_TIMER0_CLKSEL;        /* Timer0 Clock Select Register */
    volatile uint32_t WKUP_TIMER1_CLKSEL;        /* Timer1 Clock Select Register */
    volatile uint8_t  Resv_12288[4088];
    volatile uint32_t WKUP_CLKOUT_SEL;           /* Controls the WKUP_CLKOUT0 pin mux */
    volatile uint32_t WKUP_CLKOUTMUX_SEL;        /* Controls the final WKUP_CLKOUT0 pin mux */
    volatile uint8_t  Resv_16384[4088];
    volatile uint32_t WKUP_GTC_CLKSEL;           /* GTC Clock Select Register - Static Configuration */
    volatile uint8_t  Resv_20480[4092];
    volatile uint32_t USB0_CLKSEL;               /* USB0 Clock Select Register */
    volatile uint32_t USB1_CLKSEL;               /* USB1 Clock Select Register */
    volatile uint8_t  Resv_20736[248];
    volatile uint32_t USB0_PHY_CLKSEL;           /* USB0 PHY Clock Select Register */
    volatile uint32_t USB1_PHY_CLKSEL;           /* USB1 PHY Clock Select Register */
    volatile uint8_t  Resv_32768[12024];
    volatile uint32_t WKUP_GPIO0_CLKSEL;         /* Wakeup Domain GPIO0 Module Clock Select */
    volatile uint8_t  Resv_61440[28668];
    volatile uint32_t EFUSE_CLKSEL;              /* Main eFuse Controller Clock Select Register */
} CSL_wkup_ctrl_mmr_cfg2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG2_CLK_32K_RC_CLKSEL                         (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM                            (0x00000108U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM                               (0x00000140U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL                    (0x00000148U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL                               (0x0000014CU)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKSEL                       (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_OUTMUX_SEL                   (0x00000204U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV                       (0x00000208U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_OUTMUX_SEL                       (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER0_CLKSEL                        (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER1_CLKSEL                        (0x00002004U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUT_SEL                           (0x00003000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUTMUX_SEL                        (0x00003004U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_CLKSEL                           (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_CLKSEL                               (0x00005000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_CLKSEL                               (0x00005004U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_PHY_CLKSEL                           (0x00005100U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_PHY_CLKSEL                           (0x00005104U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GPIO0_CLKSEL                         (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG2_EFUSE_CLKSEL                              (0x0000F000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CLK_32K_RC_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_CLK_32K_RC_CLKSEL_CLK_SEL_MASK            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG2_CLK_32K_RC_CLKSEL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_CLK_32K_RC_CLKSEL_CLK_SEL_MAX             (0x00000003U)

/* RC12M_OSC_TRIM */

#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_FINE_MASK          (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_FINE_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_FINE_MAX           (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_MASK        (0x00000038U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_SHIFT       (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_MAX         (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_MASK    (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_SHIFT   (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG2_RC12M_OSC_TRIM_TRIMOSC_COARSE_DIR_MAX     (0x00000001U)

/* HFOSC0_TRIM */

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_IBIAS_REF_MASK              (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_IBIAS_REF_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_IBIAS_REF_MAX               (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_IBIAS_COMP_MASK             (0x000000F0U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_IBIAS_COMP_SHIFT            (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_IBIAS_COMP_MAX              (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_REF_MASK                    (0x00003F00U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_REF_SHIFT                   (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_R_REF_MAX                     (0x0000003FU)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_MULT_MASK                   (0x00070000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_MULT_SHIFT                  (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_I_MULT_MAX                    (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_HYST_MASK                     (0x00300000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_HYST_SHIFT                    (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_HYST_MAX                      (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_TRIM_EN_MASK                  (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_TRIM_EN_SHIFT                 (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_TRIM_TRIM_EN_MAX                   (0x00000001U)

/* HFOSC0_CLKOUT_32K_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_HSDIV_MASK         (0x0000007FU)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_HSDIV_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_HSDIV_MAX          (0x0000007FU)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_MASK      (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_SHIFT     (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_SYNC_DIS_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_MASK     (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_SHIFT    (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_CLKOUT_EN_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_RESET_MASK         (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_RESET_SHIFT        (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CLKOUT_32K_CTRL_RESET_MAX          (0x00000001U)

/* HFOSC0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_BP_C_MASK                     (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_BP_C_SHIFT                    (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_BP_C_MAX                      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_PD_C_MASK                     (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_PD_C_SHIFT                    (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_HFOSC0_CTRL_PD_C_MAX                      (0x00000001U)

/* WKUP_OBSCLK0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKSEL_CLK_SEL_MASK          (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKSEL_CLK_SEL_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKSEL_CLK_SEL_MAX           (0x0000000FU)

/* WKUP_OBSCLK0_OUTMUX_SEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_OUTMUX_SEL_CLK_SEL_MASK      (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_OUTMUX_SEL_CLK_SEL_SHIFT     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_OUTMUX_SEL_CLK_SEL_MAX       (0x00000001U)

/* WKUP_OBSCLK0_CLKDIV */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_MASK          (0x0000FF00U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_SHIFT         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_MAX           (0x000000FFU)

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_LD_MASK       (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_LD_SHIFT      (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_OBSCLK0_CLKDIV_CLK_DIV_LD_MAX        (0x00000001U)

/* WKUP_GTC_OUTMUX_SEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_OUTMUX_SEL_CLK_SEL_MASK          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_OUTMUX_SEL_CLK_SEL_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_OUTMUX_SEL_CLK_SEL_MAX           (0x00000001U)

/* WKUP_TIMER0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER0_CLKSEL_CLK_SEL_MASK           (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER0_CLKSEL_CLK_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER0_CLKSEL_CLK_SEL_MAX            (0x00000007U)

/* WKUP_TIMER1_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER1_CLKSEL_CLK_SEL_MASK           (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER1_CLKSEL_CLK_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_TIMER1_CLKSEL_CLK_SEL_MAX            (0x00000007U)

/* WKUP_CLKOUT_SEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUT_SEL_CLK_SEL_MASK              (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUT_SEL_CLK_SEL_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUT_SEL_CLK_SEL_MAX               (0x00000007U)

/* WKUP_CLKOUTMUX_SEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUTMUX_SEL_CLK_SEL_MASK           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUTMUX_SEL_CLK_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_CLKOUTMUX_SEL_CLK_SEL_MAX            (0x00000001U)

/* WKUP_GTC_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_CLKSEL_CLK_SEL_MASK              (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_CLKSEL_CLK_SEL_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GTC_CLKSEL_CLK_SEL_MAX               (0x00000007U)

/* USB0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_USB0_CLKSEL_REFCLK_SEL_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_CLKSEL_REFCLK_SEL_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_CLKSEL_REFCLK_SEL_MAX                (0x00000001U)

/* USB1_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_USB1_CLKSEL_REFCLK_SEL_MASK               (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_CLKSEL_REFCLK_SEL_SHIFT              (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_CLKSEL_REFCLK_SEL_MAX                (0x00000001U)

/* USB0_PHY_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_USB0_PHY_CLKSEL_REFCLK_SEL_MASK           (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_PHY_CLKSEL_REFCLK_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB0_PHY_CLKSEL_REFCLK_SEL_MAX            (0x0000000FU)

/* USB1_PHY_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_USB1_PHY_CLKSEL_REFCLK_SEL_MASK           (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_PHY_CLKSEL_REFCLK_SEL_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_USB1_PHY_CLKSEL_REFCLK_SEL_MAX            (0x0000000FU)

/* WKUP_GPIO0_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GPIO0_CLKSEL_CLK_SEL_MASK            (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GPIO0_CLKSEL_CLK_SEL_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_WKUP_GPIO0_CLKSEL_CLK_SEL_MAX             (0x00000003U)

/* EFUSE_CLKSEL */

#define CSL_WKUP_CTRL_MMR_CFG2_EFUSE_CLKSEL_CLK_SEL_MASK                 (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG2_EFUSE_CLKSEL_CLK_SEL_SHIFT                (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG2_EFUSE_CLKSEL_CLK_SEL_MAX                  (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 3
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_4100[4100];
    volatile uint32_t DBOUNCE_CFG1;              /* Debounce Config Register */
    volatile uint32_t DBOUNCE_CFG2;              /* Debounce Config Register */
    volatile uint32_t DBOUNCE_CFG3;              /* Debounce Config Register */
    volatile uint32_t DBOUNCE_CFG4;              /* Debounce Config Register */
    volatile uint32_t DBOUNCE_CFG5;              /* Debounce Config Register */
    volatile uint32_t DBOUNCE_CFG6;              /* Debounce Config Register */
    volatile uint8_t  Resv_4352[228];
    volatile uint32_t IO_VOLTAGE_STAT;           /* I/O Voltage Status Register */
    volatile uint8_t  Resv_4864[508];
    volatile uint32_t SDIO0_CTRL;                /* SDIO0 Control Register */
    volatile uint32_t SDIO1_CTRL;                /* SDIO1 Control Register */
    volatile uint32_t SDIO2_CTRL;                /* SDIO2 Control Register */
} CSL_wkup_ctrl_mmr_cfg3Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG1                              (0x00001004U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG2                              (0x00001008U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG3                              (0x0000100CU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG4                              (0x00001010U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG5                              (0x00001014U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG6                              (0x00001018U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT                           (0x00001100U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO0_CTRL                                (0x00001300U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO1_CTRL                                (0x00001304U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO2_CTRL                                (0x00001308U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DBOUNCE_CFG1 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG1_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG1_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG1_DB_CFG_MAX                   (0x0000003FU)

/* DBOUNCE_CFG2 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG2_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG2_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG2_DB_CFG_MAX                   (0x0000003FU)

/* DBOUNCE_CFG3 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG3_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG3_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG3_DB_CFG_MAX                   (0x0000003FU)

/* DBOUNCE_CFG4 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG4_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG4_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG4_DB_CFG_MAX                   (0x0000003FU)

/* DBOUNCE_CFG5 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG5_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG5_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG5_DB_CFG_MAX                   (0x0000003FU)

/* DBOUNCE_CFG6 */

#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG6_DB_CFG_MASK                  (0x0000003FU)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG6_DB_CFG_SHIFT                 (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_DBOUNCE_CFG6_DB_CFG_MAX                   (0x0000003FU)

/* IO_VOLTAGE_STAT */

#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GENERAL1_MASK             (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GENERAL1_SHIFT            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GENERAL1_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC0_MASK                 (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC0_SHIFT                (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC0_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC1_MASK                 (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC1_SHIFT                (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC1_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC2_MASK                 (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC2_SHIFT                (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_MMC2_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GPMC_MASK                 (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GPMC_SHIFT                (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG3_IO_VOLTAGE_STAT_GPMC_MAX                  (0x00000001U)

/* SDIO0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG3_SDIO0_CTRL_DRV_STR_MASK                   (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO0_CTRL_DRV_STR_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO0_CTRL_DRV_STR_MAX                    (0x0000001FU)

/* SDIO1_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG3_SDIO1_CTRL_DRV_STR_MASK                   (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO1_CTRL_DRV_STR_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO1_CTRL_DRV_STR_MAX                    (0x0000001FU)

/* SDIO2_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG3_SDIO2_CTRL_DRV_STR_MASK                   (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO2_CTRL_DRV_STR_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG3_SDIO2_CTRL_DRV_STR_MAX                    (0x0000001FU)

/**************************************************************************
* Hardware Region  : MMRs in region 4
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CHNG_DDR4_FSP_REQ;         /* Change LPDDR4 FSP Request Register */
    volatile uint32_t CHNG_DDR4_FSP_ACK;         /* Change LPDDR4 FSP Acknowledge Register */
    volatile uint8_t  Resv_128[120];
    volatile uint32_t DDR4_FSP_CLKCHNG_REQ;      /* LPDDR4 FSP Clock Change Request Register */
    volatile uint32_t DDR4_FSP_CLKCHNG_ACK;      /* LPDDR4 FSP Clock Change Acknowledge Register */
    volatile uint8_t  Resv_4096[3960];
    volatile uint32_t DDR32SS_PMCTRL;            /* DDR32SS Power Management Control */
    volatile uint8_t  Resv_20480[16380];
    volatile uint32_t USB0_PHY_CTRL;             /* USB0 PHY Control Register */
    volatile uint32_t USB1_PHY_CTRL;             /* USB1 PHY Control Register */
} CSL_wkup_ctrl_mmr_cfg4Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ                         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK                         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ                      (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_ACK                      (0x00000084U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL                            (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG4_USB0_PHY_CTRL                             (0x00005000U)
#define CSL_WKUP_CTRL_MMR_CFG4_USB1_PHY_CTRL                             (0x00005004U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CHNG_DDR4_FSP_REQ */

#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_TYPE_MASK           (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_TYPE_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_TYPE_MAX            (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_MASK                (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_SHIFT               (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_REQ_REQ_MAX                 (0x00000001U)

/* CHNG_DDR4_FSP_ACK */

#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ERROR_MASK              (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ERROR_SHIFT             (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ERROR_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ACK_MASK                (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ACK_SHIFT               (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG4_CHNG_DDR4_FSP_ACK_ACK_MAX                 (0x00000001U)

/* DDR4_FSP_CLKCHNG_REQ */

#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_MASK        (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_TYPE_MAX         (0x00000003U)

#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_MASK             (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_SHIFT            (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_REQ_REQ_MAX              (0x00000001U)

/* DDR4_FSP_CLKCHNG_ACK */

#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_ACK_ACK_MASK             (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_ACK_ACK_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR4_FSP_CLKCHNG_ACK_ACK_MAX              (0x00000001U)

/* DDR32SS_PMCTRL */

#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RETENTION_MASK        (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RETENTION_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RETENTION_MAX         (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RET_LD_MASK           (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RET_LD_SHIFT          (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG4_DDR32SS_PMCTRL_DATA_RET_LD_MAX            (0x00000001U)

/* USB0_PHY_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG4_USB0_PHY_CTRL_CORE_VOLTAGE_MASK           (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_USB0_PHY_CTRL_CORE_VOLTAGE_SHIFT          (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG4_USB0_PHY_CTRL_CORE_VOLTAGE_MAX            (0x00000001U)

/* USB1_PHY_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG4_USB1_PHY_CTRL_CORE_VOLTAGE_MASK           (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG4_USB1_PHY_CTRL_CORE_VOLTAGE_SHIFT          (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG4_USB1_PHY_CTRL_CORE_VOLTAGE_MAX            (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 5
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_128[128];
    volatile uint32_t PMCTRL_SYS;                /* Power Management System Control */
    volatile uint32_t PMCTRL_IO_0;               /* Power Management IO Control 0 */
    volatile uint32_t PMCTRL_IO_1;               /* Power Management IO Control 1 */
    volatile uint8_t  Resv_144[4];
    volatile uint32_t PMCTRL_MOSC;               /* Power Management Main Oscillator Control */
    volatile uint8_t  Resv_152[4];
    volatile uint32_t PM_MISC_STATUS;            /* Power Management Misc Status */
    volatile uint8_t  Resv_160[4];
    volatile uint32_t PM_PERMISSION;             /* Power Management Permission Register */
    volatile uint8_t  Resv_352[188];
    volatile uint32_t DEEPSLEEP_CTRL;            /* Deep Sleep Control Register */
    volatile uint8_t  Resv_1024[668];
    volatile uint32_t WFI_STATUS;                /* WFI Status of Cores */
    volatile uint8_t  Resv_1040[12];
    volatile uint32_t SLEEP_STATUS;              /* Deep Sleep Entry/Exit Status Bits */
    volatile uint8_t  Resv_1280[236];
    volatile uint32_t DS_MAGIC_WORD;             /* Deep Sleep Magic Word */
    volatile uint8_t  Resv_4096[2812];
    volatile uint32_t WWD0_CTRL;                 /* WWD0 Control Register */
    volatile uint32_t WWD1_CTRL;                 /* WWD1 Control Register */
    volatile uint8_t  Resv_4872[768];
    volatile uint32_t CANUART_WAKE_STAT0;        /* CANUART IO Domain Daisy-Chain Wakeup Status Register 0 */
    volatile uint32_t CANUART_WAKE_STAT1;        /* CANUART IO Domain Daisy-Chain Wakeup Status Register 1 */
    volatile uint32_t CANUART_WAKE_OFF_MODE;     /* CANUART IO Domain OFF Mode Magic Word */
    volatile uint8_t  Resv_4888[4];
    volatile uint32_t CANUART_WAKE_OFF_MODE_STAT;   /* CANUART IO Domain OFF Mode Magic Word */
    volatile uint8_t  Resv_8192[3300];
    volatile uint32_t PMCTRL_MOSC_STARTUP;       /* Power Management Main Oscillator Control */
    volatile uint8_t  Resv_8448[252];
    volatile uint32_t HFOSC0_STAT;               /* Status of HF Oscillator Power Down Request By DM */
    volatile uint8_t  Resv_12288[3836];
    volatile uint32_t CANUART_WAKE_RESUME_KEY[4];   /* CAN_UART IO Domain Resume Key Value */
    volatile uint8_t  Resv_12544[240];
    volatile uint32_t CANUART_WAKE_RESUME_KEY_STAT[4];   /* CAN_UART IO Domain Resume Key Value */
    volatile uint32_t CANUART_WAKE_CTRL;         /* CANUART IO Domain Daisy-Chain Wakeup Control Register */
    volatile uint8_t  Resv_16384[3820];
    volatile uint32_t RST_CTRL;                  /* Reset Control Register */
    volatile uint8_t  Resv_16400[12];
    volatile uint32_t RST_SRC;                   /* Reset Source Register */
    volatile uint8_t  Resv_16432[28];
    volatile uint32_t WKUP0_EN;                  /* Wakeup Activate 0 */
    volatile uint8_t  Resv_16448[12];
    volatile uint32_t WKUP0_SRC;                 /* Wakeup Source 0 */
    volatile uint8_t  Resv_16464[12];
    volatile uint32_t CLKGATE_CTRL0;             /* WKUP Automatic Clock Gating Control Register0 */
} CSL_wkup_ctrl_mmr_cfg5Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS                                (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0                               (0x00000084U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1                               (0x00000088U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC                               (0x00000090U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_MISC_STATUS                            (0x00000098U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION                             (0x000000A0U)
#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL                            (0x00000160U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS                                (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS                              (0x00000410U)
#define CSL_WKUP_CTRL_MMR_CFG5_DS_MAGIC_WORD                             (0x00000500U)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD0_CTRL                                 (0x00001000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD1_CTRL                                 (0x00001004U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0                        (0x00001308U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT1                        (0x0000130CU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE                     (0x00001310U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_STAT                (0x00001318U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_STARTUP                       (0x00002000U)
#define CSL_WKUP_CTRL_MMR_CFG5_HFOSC0_STAT                               (0x00002100U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY(CANUART_WAKE_RESUME_KEY) (0x00003000U+((CANUART_WAKE_RESUME_KEY)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_STAT(CANUART_WAKE_RESUME_KEY_STAT) (0x00003100U+((CANUART_WAKE_RESUME_KEY_STAT)*0x4U))
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL                         (0x00003110U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL                                  (0x00004000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC                                   (0x00004010U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN                                  (0x00004030U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC                                 (0x00004040U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0                             (0x00004050U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PMCTRL_SYS */

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_MASK                    (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_SHIFT                   (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_MAX                     (0x00000007U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_WE_MASK                 (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_WE_SHIFT                (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_LPM_EN_WE_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_MASK                   (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_SHIFT                  (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_MAX                    (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_WE_MASK                (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_WE_SHIFT               (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_SYS_PMIC_EN_WE_MAX                 (0x00000001U)

/* PMCTRL_IO_0 */

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_OVRD_0_MASK            (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_OVRD_0_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_OVRD_0_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_STATUS_0_MASK          (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_STATUS_0_SHIFT         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOCLK_STATUS_0_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOOVR_EXTEND_0_MASK          (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOOVR_EXTEND_0_SHIFT         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOOVR_EXTEND_0_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ON_STATUS_0_MASK           (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ON_STATUS_0_SHIFT          (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ON_STATUS_0_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOBYPASS_OVR_0_MASK          (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOBYPASS_OVR_0_SHIFT         (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_ISOBYPASS_OVR_0_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_CTRL_0_MASK             (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_CTRL_0_SHIFT            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_CTRL_0_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_STATUS_0_MASK           (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_STATUS_0_SHIFT          (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_WUCLK_STATUS_0_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_GLOBAL_WUEN_0_MASK            (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_GLOBAL_WUEN_0_SHIFT           (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_GLOBAL_WUEN_0_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_CTRL_0_MASK            (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_CTRL_0_SHIFT           (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_CTRL_0_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_STATUS_0_MASK          (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_STATUS_0_SHIFT         (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_0_IO_ISO_STATUS_0_MAX           (0x00000001U)

/* PMCTRL_IO_1 */

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_OVRD_1_MASK            (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_OVRD_1_SHIFT           (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_OVRD_1_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_STATUS_1_MASK          (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_STATUS_1_SHIFT         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOCLK_STATUS_1_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOOVR_EXTEND_1_MASK          (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOOVR_EXTEND_1_SHIFT         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOOVR_EXTEND_1_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ON_STATUS_1_MASK           (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ON_STATUS_1_SHIFT          (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ON_STATUS_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOBYPASS_OVR_1_MASK          (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOBYPASS_OVR_1_SHIFT         (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_ISOBYPASS_OVR_1_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_CTRL_1_MASK             (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_CTRL_1_SHIFT            (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_CTRL_1_MAX              (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_STATUS_1_MASK           (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_STATUS_1_SHIFT          (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_WUCLK_STATUS_1_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_GLOBAL_WUEN_1_MASK            (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_GLOBAL_WUEN_1_SHIFT           (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_GLOBAL_WUEN_1_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_CTRL_1_MASK            (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_CTRL_1_SHIFT           (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_CTRL_1_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_STATUS_1_MASK          (0x02000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_STATUS_1_SHIFT         (0x00000019U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_IO_ISO_STATUS_1_MAX           (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_RESERVED4_MASK                (0xFC000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_RESERVED4_SHIFT               (0x0000001AU)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_IO_1_RESERVED4_MAX                 (0x0000003FU)

/* PMCTRL_MOSC */

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_OSC_CG_ON_WFI_MASK            (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_OSC_CG_ON_WFI_SHIFT           (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_OSC_CG_ON_WFI_MAX             (0x00000001U)

/* PM_MISC_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG5_PM_MISC_STATUS_OSC_CG_STAT_MASK           (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_MISC_STATUS_OSC_CG_STAT_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_MISC_STATUS_OSC_CG_STAT_MAX            (0x00000003U)

/* PM_PERMISSION */

#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_DEBUG_ACTIVE_MASK           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_DEBUG_ACTIVE_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_DEBUG_ACTIVE_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_SECURITY_ACTIVE_MASK        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_SECURITY_ACTIVE_SHIFT       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_PM_PERMISSION_SECURITY_ACTIVE_MAX         (0x00000001U)

/* DEEPSLEEP_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_WKUP_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_WKUP_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_WKUP_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_MAIN_MASK         (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_MAIN_SHIFT        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_DEEPSLEEP_CTRL_FORCE_DS_MAIN_MAX          (0x00000001U)

/* WFI_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_SMS_CPU0_WFI_MASK              (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_SMS_CPU0_WFI_SHIFT             (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_SMS_CPU0_WFI_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_L2WFI_MASK              (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_L2WFI_SHIFT             (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_L2WFI_MAX               (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU0_WFI_MASK           (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU0_WFI_SHIFT          (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU0_WFI_MAX            (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU1_WFI_MASK           (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU1_WFI_SHIFT          (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG5_WFI_STATUS_MPUSS0_CPU1_WFI_MAX            (0x00000001U)

/* SLEEP_STATUS */

#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_RESETSTATZ_MASK         (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_RESETSTATZ_SHIFT        (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_RESETSTATZ_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_DS_MASK                 (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_DS_SHIFT                (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_MAIN_DS_MAX                  (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_EXITED_SLEEP_MASK            (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_EXITED_SLEEP_SHIFT           (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG5_SLEEP_STATUS_EXITED_SLEEP_MAX             (0x00000001U)

/* DS_MAGIC_WORD */

#define CSL_WKUP_CTRL_MMR_CFG5_DS_MAGIC_WORD_DS_MAGIC_WORD_MASK          (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_DS_MAGIC_WORD_DS_MAGIC_WORD_SHIFT         (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_DS_MAGIC_WORD_DS_MAGIC_WORD_MAX           (0xFFFFFFFFU)

/* WWD0_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG5_WWD0_CTRL_WWD_STOP_MASK                   (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD0_CTRL_WWD_STOP_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD0_CTRL_WWD_STOP_MAX                    (0x0000000FU)

/* WWD1_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG5_WWD1_CTRL_WWD_STOP_MASK                   (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD1_CTRL_WWD_STOP_SHIFT                  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WWD1_CTRL_WWD_STOP_MAX                    (0x0000000FU)

/* CANUART_WAKE_STAT0 */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_LOAD_STAT_MASK      (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_LOAD_STAT_SHIFT     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_LOAD_STAT_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_STAT_MASK           (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_STAT_SHIFT          (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT0_MW_STAT_MAX            (0x7FFFFFFFU)

/* CANUART_WAKE_STAT1 */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT1_CANUART_IO_MODE_MASK   (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT1_CANUART_IO_MODE_SHIFT  (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_STAT1_CANUART_IO_MODE_MAX    (0x00000001U)

/* CANUART_WAKE_OFF_MODE */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_MW_MASK             (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_MW_SHIFT            (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_MW_MAX              (0xFFFFFFFFU)

/* CANUART_WAKE_OFF_MODE_STAT */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_STAT_MW_MASK        (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_STAT_MW_SHIFT       (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_OFF_MODE_STAT_MW_MAX         (0xFFFFFFFFU)

/* PMCTRL_MOSC_STARTUP */

#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_STARTUP_SETUP_TIME_MASK       (0x000FFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_STARTUP_SETUP_TIME_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_PMCTRL_MOSC_STARTUP_SETUP_TIME_MAX        (0x000FFFFFU)

/* HFOSC0_STAT */

#define CSL_WKUP_CTRL_MMR_CFG5_HFOSC0_STAT_DS_ON_WFI_STAT_MASK           (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_HFOSC0_STAT_DS_ON_WFI_STAT_SHIFT          (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_HFOSC0_STAT_DS_ON_WFI_STAT_MAX            (0x00000001U)

/* CANUART_WAKE_RESUME_KEY */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_KEYVAL_MASK       (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_KEYVAL_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_KEYVAL_MAX        (0xFFFFFFFFU)

/* CANUART_WAKE_RESUME_KEY_STAT */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_MASK  (0xFFFFFFFFU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_SHIFT (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_RESUME_KEY_STAT_KEYVAL_MAX   (0xFFFFFFFFU)

/* CANUART_WAKE_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_LOAD_EN_MASK         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_LOAD_EN_SHIFT        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_LOAD_EN_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_MASK                 (0xFFFFFFFEU)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_SHIFT                (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CANUART_WAKE_CTRL_MW_MAX                  (0x7FFFFFFFU)

/* RST_CTRL */

#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SW_WARMRESET_MASK                (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SW_WARMRESET_SHIFT               (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SW_WARMRESET_MAX                 (0x0000000FU)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SMS_COLD_RESET_EN_Z_MASK         (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SMS_COLD_RESET_EN_Z_SHIFT        (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_SMS_COLD_RESET_EN_Z_MAX          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_RESET_ISO_DONE_Z_MASK            (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_RESET_ISO_DONE_Z_SHIFT           (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_RESET_ISO_DONE_Z_MAX             (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_DDR_ERR_RESET_EN_Z_MASK          (0x01000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_DDR_ERR_RESET_EN_Z_SHIFT         (0x00000018U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_CTRL_DDR_ERR_RESET_EN_Z_MAX           (0x00000001U)

/* RST_SRC */

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC0_MASK                         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC0_SHIFT                        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC0_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC1_MASK                         (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC1_SHIFT                        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC1_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC2_MASK                         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC2_SHIFT                        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC2_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC3_MASK                         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC3_SHIFT                        (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC3_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC4_MASK                         (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC4_SHIFT                        (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC4_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC5_MASK                         (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC5_SHIFT                        (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC5_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC9_MASK                         (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC9_SHIFT                        (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC9_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC10_MASK                        (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC10_SHIFT                       (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC10_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC11_MASK                        (0x00000800U)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC11_SHIFT                       (0x0000000BU)
#define CSL_WKUP_CTRL_MMR_CFG5_RST_SRC_SRC11_MAX                         (0x00000001U)

/* WKUP0_EN */

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN0_MASK                         (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN0_SHIFT                        (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN0_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN1_MASK                         (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN1_SHIFT                        (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN1_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN2_MASK                         (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN2_SHIFT                        (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN2_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN3_MASK                         (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN3_SHIFT                        (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN3_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN5_MASK                         (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN5_SHIFT                        (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN5_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN6_MASK                         (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN6_SHIFT                        (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN6_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN7_MASK                         (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN7_SHIFT                        (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN7_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN9_MASK                         (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN9_SHIFT                        (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN9_MAX                          (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN10_MASK                        (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN10_SHIFT                       (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN10_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN16_MASK                        (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN16_SHIFT                       (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN16_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN17_MASK                        (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN17_SHIFT                       (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN17_MAX                         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN18_MASK                        (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN18_SHIFT                       (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_EN_EN18_MAX                         (0x00000001U)

/* WKUP0_SRC */

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT0_MASK                      (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT0_SHIFT                     (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT0_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT1_MASK                      (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT1_SHIFT                     (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT1_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT2_MASK                      (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT2_SHIFT                     (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT2_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT3_MASK                      (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT3_SHIFT                     (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT3_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT5_MASK                      (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT5_SHIFT                     (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT5_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT6_MASK                      (0x00000040U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT6_SHIFT                     (0x00000006U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT6_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT7_MASK                      (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT7_SHIFT                     (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT7_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT9_MASK                      (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT9_SHIFT                     (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT9_MAX                       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT10_MASK                     (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT10_SHIFT                    (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT10_MAX                      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT16_MASK                     (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT16_SHIFT                    (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT16_MAX                      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT17_MASK                     (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT17_SHIFT                    (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT17_MAX                      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT18_MASK                     (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT18_SHIFT                    (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG5_WKUP0_SRC_STAT18_MAX                      (0x00000001U)

/* CLKGATE_CTRL0 */

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA1_NOGATE_MASK       (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA1_NOGATE_SHIFT      (0x00000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA1_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA0_NOGATE_MASK       (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA0_NOGATE_SHIFT      (0x00000001U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_WKUP_CBA0_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA2_NOGATE_MASK       (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA2_NOGATE_SHIFT      (0x00000002U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA2_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA1_NOGATE_MASK       (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA1_NOGATE_SHIFT      (0x00000003U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA1_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA0_NOGATE_MASK       (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA0_NOGATE_SHIFT      (0x00000004U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_CBA0_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_MASK     (0x00000020U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_SHIFT    (0x00000005U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_FW_CBA_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_MASK      (0x00000080U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_SHIFT     (0x00000007U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_MASK  (0x00000100U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_SHIFT (0x00000008U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_ACP_NOGATE_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_MASK  (0x00000200U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_SHIFT (0x00000009U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_CFG_NOGATE_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_MASK  (0x00000400U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_SHIFT (0x0000000AU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_MPU_0_DBG_NOGATE_MAX   (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_MASK     (0x00008000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_SHIFT    (0x0000000FU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_GIC500_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_MASK       (0x00010000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_SHIFT      (0x00000010U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DMSS_NOGATE_MAX        (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_MASK      (0x00020000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_SHIFT     (0x00000011U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA0_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_MASK      (0x00040000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_SHIFT     (0x00000012U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA1_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_MASK      (0x00080000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_SHIFT     (0x00000013U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA2_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA_CRYPTO_NOGATE_MASK (0x00100000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA_CRYPTO_NOGATE_SHIFT (0x00000014U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PDMA_CRYPTO_NOGATE_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PSC_FW_CH_BR_NOGATE_MASK (0x00400000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PSC_FW_CH_BR_NOGATE_SHIFT (0x00000016U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_PSC_FW_CH_BR_NOGATE_MAX (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_SRAM0_NOGATE_MASK      (0x08000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_SRAM0_NOGATE_SHIFT     (0x0000001BU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_SRAM0_NOGATE_MAX       (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_MASK    (0x10000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_SHIFT   (0x0000001CU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_MAIN_DBG_CBA_NOGATE_MAX     (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_DMSS_CRYPTO_NOGATE_MASK     (0x20000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_DMSS_CRYPTO_NOGATE_SHIFT    (0x0000001DU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_DMSS_CRYPTO_NOGATE_MAX      (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_DMSS_NOGATE_MASK        (0x40000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_DMSS_NOGATE_SHIFT       (0x0000001EU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_DMSS_NOGATE_MAX         (0x00000001U)

#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_NOGATE_MASK             (0x80000000U)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_NOGATE_SHIFT            (0x0000001FU)
#define CSL_WKUP_CTRL_MMR_CFG5_CLKGATE_CTRL0_SMS_NOGATE_MAX              (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 6
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
} CSL_wkup_ctrl_mmr_cfg6Regs;


/**************************************************************************
* Register Macros
**************************************************************************/


/**************************************************************************
* Field Definition Macros
**************************************************************************/


/**************************************************************************
* Hardware Region  : MMRs in region 7
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
} CSL_wkup_ctrl_mmr_cfg7Regs;


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