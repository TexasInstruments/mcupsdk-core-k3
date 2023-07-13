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
 *  Name        : cslr_cbass.h
*/
#ifndef CSLR_CBASS_H_
#define CSLR_CBASS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : Global Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* Revision Register */
    volatile uint32_t DESTINATION_ID;            /* Destination ID Register */
    volatile uint8_t  Resv_32[24];
    volatile uint32_t EXCEPTION_LOGGING_CONTROL;   /* Exception Logging Control Register */
    volatile uint32_t EXCEPTION_LOGGING_HEADER0;   /* Exception Logging Header 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_HEADER1;   /* Exception Logging Header 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA0;   /* Exception Logging Data 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA1;   /* Exception Logging Data 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA2;   /* Exception Logging Data 2 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA3;   /* Exception Logging Data 3 Register */
    volatile uint8_t  Resv_64[4];
    volatile uint32_t EXCEPTION_PEND_SET;        /* Exception Logging Pending Set Register */
    volatile uint32_t EXCEPTION_PEND_CLEAR;      /* Exception Logging Pending Clear Register */
} CSL_cbass_glbRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CBASS_GLB_PID                                                      (0x00000000U)
#define CSL_CBASS_GLB_DESTINATION_ID                                           (0x00000004U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL                                (0x00000020U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_SET                                       (0x00000040U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_CLEAR                                     (0x00000044U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_CBASS_GLB_PID_MINOR_MASK                                           (0x0000003FU)
#define CSL_CBASS_GLB_PID_MINOR_SHIFT                                          (0x00000000U)
#define CSL_CBASS_GLB_PID_MINOR_MAX                                            (0x0000003FU)

#define CSL_CBASS_GLB_PID_CUSTOM_MASK                                          (0x000000C0U)
#define CSL_CBASS_GLB_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define CSL_CBASS_GLB_PID_CUSTOM_MAX                                           (0x00000003U)

#define CSL_CBASS_GLB_PID_MAJOR_MASK                                           (0x00000700U)
#define CSL_CBASS_GLB_PID_MAJOR_SHIFT                                          (0x00000008U)
#define CSL_CBASS_GLB_PID_MAJOR_MAX                                            (0x00000007U)

#define CSL_CBASS_GLB_PID_RTL_MASK                                             (0x0000F800U)
#define CSL_CBASS_GLB_PID_RTL_SHIFT                                            (0x0000000BU)
#define CSL_CBASS_GLB_PID_RTL_MAX                                              (0x0000001FU)

#define CSL_CBASS_GLB_PID_FUNC_MASK                                            (0x0FFF0000U)
#define CSL_CBASS_GLB_PID_FUNC_SHIFT                                           (0x00000010U)
#define CSL_CBASS_GLB_PID_FUNC_MAX                                             (0x00000FFFU)

#define CSL_CBASS_GLB_PID_BU_MASK                                              (0x30000000U)
#define CSL_CBASS_GLB_PID_BU_SHIFT                                             (0x0000001CU)
#define CSL_CBASS_GLB_PID_BU_MAX                                               (0x00000003U)

#define CSL_CBASS_GLB_PID_SCHEME_MASK                                          (0xC0000000U)
#define CSL_CBASS_GLB_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define CSL_CBASS_GLB_PID_SCHEME_MAX                                           (0x00000003U)

/* DESTINATION_ID */

#define CSL_CBASS_GLB_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define CSL_CBASS_GLB_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define CSL_CBASS_GLB_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

/* EXCEPTION_LOGGING_CONTROL */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MASK                 (0x00000001U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_SHIFT                (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MAX                  (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MASK              (0x00000002U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_SHIFT             (0x00000001U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MAX               (0x00000001U)

/* EXCEPTION_LOGGING_HEADER0 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

/* EXCEPTION_LOGGING_HEADER1 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

/* EXCEPTION_LOGGING_DATA0 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

/* EXCEPTION_LOGGING_DATA1 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

/* EXCEPTION_LOGGING_DATA2 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

/* EXCEPTION_LOGGING_DATA3 */

#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

/* EXCEPTION_PEND_SET */

#define CSL_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MASK                         (0x00000001U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_SHIFT                        (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MAX                          (0x00000001U)

/* EXCEPTION_PEND_CLEAR */

#define CSL_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MASK                       (0x00000001U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_SHIFT                      (0x00000000U)
#define CSL_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MAX                        (0x00000001U)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t MSRAM0_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_4_CONTROL;   /* Firewall Region 4 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_4_PERMISSION_0;   /* Firewall Region 4 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_4_PERMISSION_1;   /* Firewall Region 4 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_4_PERMISSION_2;   /* Firewall Region 4 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_4_START_ADDRESS_L;   /* Firewall Region 4 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_4_START_ADDRESS_H;   /* Firewall Region 4 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_4_END_ADDRESS_L;   /* Firewall Region 4 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_4_END_ADDRESS_H;   /* Firewall Region 4 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_5_CONTROL;   /* Firewall Region 5 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_5_PERMISSION_0;   /* Firewall Region 5 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_5_PERMISSION_1;   /* Firewall Region 5 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_5_PERMISSION_2;   /* Firewall Region 5 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_5_START_ADDRESS_L;   /* Firewall Region 5 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_5_START_ADDRESS_H;   /* Firewall Region 5 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_5_END_ADDRESS_L;   /* Firewall Region 5 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_5_END_ADDRESS_H;   /* Firewall Region 5 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_6_CONTROL;   /* Firewall Region 6 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_6_PERMISSION_0;   /* Firewall Region 6 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_6_PERMISSION_1;   /* Firewall Region 6 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_6_PERMISSION_2;   /* Firewall Region 6 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_6_START_ADDRESS_L;   /* Firewall Region 6 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_6_START_ADDRESS_H;   /* Firewall Region 6 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_6_END_ADDRESS_L;   /* Firewall Region 6 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_6_END_ADDRESS_H;   /* Firewall Region 6 End Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_7_CONTROL;   /* Firewall Region 7 Control Register */
    volatile uint32_t MSRAM0_FW_REGION_7_PERMISSION_0;   /* Firewall Region 7 Permission 0 Register */
    volatile uint32_t MSRAM0_FW_REGION_7_PERMISSION_1;   /* Firewall Region 7 Permission 1 Register */
    volatile uint32_t MSRAM0_FW_REGION_7_PERMISSION_2;   /* Firewall Region 7 Permission 2 Register */
    volatile uint32_t MSRAM0_FW_REGION_7_START_ADDRESS_L;   /* Firewall Region 7 Start Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_7_START_ADDRESS_H;   /* Firewall Region 7 Start Address High Register */
    volatile uint32_t MSRAM0_FW_REGION_7_END_ADDRESS_L;   /* Firewall Region 7 End Address Low Register */
    volatile uint32_t MSRAM0_FW_REGION_7_END_ADDRESS_H;   /* Firewall Region 7 End Address High Register */
    volatile uint8_t  Resv_1024[768];
    volatile uint32_t MSRAM1_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_4_CONTROL;   /* Firewall Region 4 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_4_PERMISSION_0;   /* Firewall Region 4 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_4_PERMISSION_1;   /* Firewall Region 4 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_4_PERMISSION_2;   /* Firewall Region 4 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_4_START_ADDRESS_L;   /* Firewall Region 4 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_4_START_ADDRESS_H;   /* Firewall Region 4 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_4_END_ADDRESS_L;   /* Firewall Region 4 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_4_END_ADDRESS_H;   /* Firewall Region 4 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_5_CONTROL;   /* Firewall Region 5 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_5_PERMISSION_0;   /* Firewall Region 5 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_5_PERMISSION_1;   /* Firewall Region 5 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_5_PERMISSION_2;   /* Firewall Region 5 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_5_START_ADDRESS_L;   /* Firewall Region 5 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_5_START_ADDRESS_H;   /* Firewall Region 5 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_5_END_ADDRESS_L;   /* Firewall Region 5 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_5_END_ADDRESS_H;   /* Firewall Region 5 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_6_CONTROL;   /* Firewall Region 6 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_6_PERMISSION_0;   /* Firewall Region 6 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_6_PERMISSION_1;   /* Firewall Region 6 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_6_PERMISSION_2;   /* Firewall Region 6 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_6_START_ADDRESS_L;   /* Firewall Region 6 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_6_START_ADDRESS_H;   /* Firewall Region 6 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_6_END_ADDRESS_L;   /* Firewall Region 6 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_6_END_ADDRESS_H;   /* Firewall Region 6 End Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_7_CONTROL;   /* Firewall Region 7 Control Register */
    volatile uint32_t MSRAM1_FW_REGION_7_PERMISSION_0;   /* Firewall Region 7 Permission 0 Register */
    volatile uint32_t MSRAM1_FW_REGION_7_PERMISSION_1;   /* Firewall Region 7 Permission 1 Register */
    volatile uint32_t MSRAM1_FW_REGION_7_PERMISSION_2;   /* Firewall Region 7 Permission 2 Register */
    volatile uint32_t MSRAM1_FW_REGION_7_START_ADDRESS_L;   /* Firewall Region 7 Start Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_7_START_ADDRESS_H;   /* Firewall Region 7 Start Address High Register */
    volatile uint32_t MSRAM1_FW_REGION_7_END_ADDRESS_L;   /* Firewall Region 7 End Address Low Register */
    volatile uint32_t MSRAM1_FW_REGION_7_END_ADDRESS_H;   /* Firewall Region 7 End Address High Register */
    volatile uint8_t  Resv_2048[768];
    volatile uint32_t MSRAM2_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_4_CONTROL;   /* Firewall Region 4 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_4_PERMISSION_0;   /* Firewall Region 4 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_4_PERMISSION_1;   /* Firewall Region 4 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_4_PERMISSION_2;   /* Firewall Region 4 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_4_START_ADDRESS_L;   /* Firewall Region 4 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_4_START_ADDRESS_H;   /* Firewall Region 4 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_4_END_ADDRESS_L;   /* Firewall Region 4 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_4_END_ADDRESS_H;   /* Firewall Region 4 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_5_CONTROL;   /* Firewall Region 5 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_5_PERMISSION_0;   /* Firewall Region 5 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_5_PERMISSION_1;   /* Firewall Region 5 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_5_PERMISSION_2;   /* Firewall Region 5 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_5_START_ADDRESS_L;   /* Firewall Region 5 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_5_START_ADDRESS_H;   /* Firewall Region 5 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_5_END_ADDRESS_L;   /* Firewall Region 5 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_5_END_ADDRESS_H;   /* Firewall Region 5 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_6_CONTROL;   /* Firewall Region 6 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_6_PERMISSION_0;   /* Firewall Region 6 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_6_PERMISSION_1;   /* Firewall Region 6 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_6_PERMISSION_2;   /* Firewall Region 6 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_6_START_ADDRESS_L;   /* Firewall Region 6 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_6_START_ADDRESS_H;   /* Firewall Region 6 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_6_END_ADDRESS_L;   /* Firewall Region 6 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_6_END_ADDRESS_H;   /* Firewall Region 6 End Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_7_CONTROL;   /* Firewall Region 7 Control Register */
    volatile uint32_t MSRAM2_FW_REGION_7_PERMISSION_0;   /* Firewall Region 7 Permission 0 Register */
    volatile uint32_t MSRAM2_FW_REGION_7_PERMISSION_1;   /* Firewall Region 7 Permission 1 Register */
    volatile uint32_t MSRAM2_FW_REGION_7_PERMISSION_2;   /* Firewall Region 7 Permission 2 Register */
    volatile uint32_t MSRAM2_FW_REGION_7_START_ADDRESS_L;   /* Firewall Region 7 Start Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_7_START_ADDRESS_H;   /* Firewall Region 7 Start Address High Register */
    volatile uint32_t MSRAM2_FW_REGION_7_END_ADDRESS_L;   /* Firewall Region 7 End Address Low Register */
    volatile uint32_t MSRAM2_FW_REGION_7_END_ADDRESS_H;   /* Firewall Region 7 End Address High Register */
    volatile uint8_t  Resv_3072[768];
    volatile uint32_t MSRAM3_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_4_CONTROL;   /* Firewall Region 4 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_4_PERMISSION_0;   /* Firewall Region 4 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_4_PERMISSION_1;   /* Firewall Region 4 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_4_PERMISSION_2;   /* Firewall Region 4 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_4_START_ADDRESS_L;   /* Firewall Region 4 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_4_START_ADDRESS_H;   /* Firewall Region 4 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_4_END_ADDRESS_L;   /* Firewall Region 4 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_4_END_ADDRESS_H;   /* Firewall Region 4 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_5_CONTROL;   /* Firewall Region 5 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_5_PERMISSION_0;   /* Firewall Region 5 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_5_PERMISSION_1;   /* Firewall Region 5 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_5_PERMISSION_2;   /* Firewall Region 5 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_5_START_ADDRESS_L;   /* Firewall Region 5 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_5_START_ADDRESS_H;   /* Firewall Region 5 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_5_END_ADDRESS_L;   /* Firewall Region 5 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_5_END_ADDRESS_H;   /* Firewall Region 5 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_6_CONTROL;   /* Firewall Region 6 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_6_PERMISSION_0;   /* Firewall Region 6 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_6_PERMISSION_1;   /* Firewall Region 6 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_6_PERMISSION_2;   /* Firewall Region 6 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_6_START_ADDRESS_L;   /* Firewall Region 6 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_6_START_ADDRESS_H;   /* Firewall Region 6 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_6_END_ADDRESS_L;   /* Firewall Region 6 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_6_END_ADDRESS_H;   /* Firewall Region 6 End Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_7_CONTROL;   /* Firewall Region 7 Control Register */
    volatile uint32_t MSRAM3_FW_REGION_7_PERMISSION_0;   /* Firewall Region 7 Permission 0 Register */
    volatile uint32_t MSRAM3_FW_REGION_7_PERMISSION_1;   /* Firewall Region 7 Permission 1 Register */
    volatile uint32_t MSRAM3_FW_REGION_7_PERMISSION_2;   /* Firewall Region 7 Permission 2 Register */
    volatile uint32_t MSRAM3_FW_REGION_7_START_ADDRESS_L;   /* Firewall Region 7 Start Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_7_START_ADDRESS_H;   /* Firewall Region 7 Start Address High Register */
    volatile uint32_t MSRAM3_FW_REGION_7_END_ADDRESS_L;   /* Firewall Region 7 End Address Low Register */
    volatile uint32_t MSRAM3_FW_REGION_7_END_ADDRESS_H;   /* Firewall Region 7 End Address High Register */
} CSL_cbass_fwRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL                                (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0                           (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1                           (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2                           (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L                        (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_H                        (0x00000014U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L                          (0x00000018U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_H                          (0x0000001CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL                                (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0                           (0x00000024U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1                           (0x00000028U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2                           (0x0000002CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L                        (0x00000030U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_H                        (0x00000034U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L                          (0x00000038U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_H                          (0x0000003CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL                                (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0                           (0x00000044U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1                           (0x00000048U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2                           (0x0000004CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L                        (0x00000050U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_H                        (0x00000054U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L                          (0x00000058U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_H                          (0x0000005CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL                                (0x00000060U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0                           (0x00000064U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1                           (0x00000068U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2                           (0x0000006CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L                        (0x00000070U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_H                        (0x00000074U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L                          (0x00000078U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_H                          (0x0000007CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL                                (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0                           (0x00000084U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1                           (0x00000088U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2                           (0x0000008CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L                        (0x00000090U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_H                        (0x00000094U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L                          (0x00000098U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_H                          (0x0000009CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL                                (0x000000A0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0                           (0x000000A4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1                           (0x000000A8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2                           (0x000000ACU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L                        (0x000000B0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_H                        (0x000000B4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L                          (0x000000B8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_H                          (0x000000BCU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL                                (0x000000C0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0                           (0x000000C4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1                           (0x000000C8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2                           (0x000000CCU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L                        (0x000000D0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_H                        (0x000000D4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L                          (0x000000D8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_H                          (0x000000DCU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL                                (0x000000E0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0                           (0x000000E4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1                           (0x000000E8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2                           (0x000000ECU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L                        (0x000000F0U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_H                        (0x000000F4U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L                          (0x000000F8U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_H                          (0x000000FCU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL                                (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0                           (0x00000404U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1                           (0x00000408U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2                           (0x0000040CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L                        (0x00000410U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_H                        (0x00000414U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L                          (0x00000418U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_H                          (0x0000041CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL                                (0x00000420U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0                           (0x00000424U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1                           (0x00000428U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2                           (0x0000042CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L                        (0x00000430U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_H                        (0x00000434U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L                          (0x00000438U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_H                          (0x0000043CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL                                (0x00000440U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0                           (0x00000444U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1                           (0x00000448U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2                           (0x0000044CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L                        (0x00000450U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_H                        (0x00000454U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L                          (0x00000458U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_H                          (0x0000045CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL                                (0x00000460U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0                           (0x00000464U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1                           (0x00000468U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2                           (0x0000046CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L                        (0x00000470U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_H                        (0x00000474U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L                          (0x00000478U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_H                          (0x0000047CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL                                (0x00000480U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0                           (0x00000484U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1                           (0x00000488U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2                           (0x0000048CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L                        (0x00000490U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_H                        (0x00000494U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L                          (0x00000498U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_H                          (0x0000049CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL                                (0x000004A0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0                           (0x000004A4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1                           (0x000004A8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2                           (0x000004ACU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L                        (0x000004B0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_H                        (0x000004B4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L                          (0x000004B8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_H                          (0x000004BCU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL                                (0x000004C0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0                           (0x000004C4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1                           (0x000004C8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2                           (0x000004CCU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L                        (0x000004D0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_H                        (0x000004D4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L                          (0x000004D8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_H                          (0x000004DCU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL                                (0x000004E0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0                           (0x000004E4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1                           (0x000004E8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2                           (0x000004ECU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L                        (0x000004F0U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_H                        (0x000004F4U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L                          (0x000004F8U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_H                          (0x000004FCU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL                                (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0                           (0x00000804U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1                           (0x00000808U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2                           (0x0000080CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L                        (0x00000810U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_H                        (0x00000814U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L                          (0x00000818U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_H                          (0x0000081CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL                                (0x00000820U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0                           (0x00000824U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1                           (0x00000828U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2                           (0x0000082CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L                        (0x00000830U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_H                        (0x00000834U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L                          (0x00000838U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_H                          (0x0000083CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL                                (0x00000840U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0                           (0x00000844U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1                           (0x00000848U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2                           (0x0000084CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L                        (0x00000850U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_H                        (0x00000854U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L                          (0x00000858U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_H                          (0x0000085CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL                                (0x00000860U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0                           (0x00000864U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1                           (0x00000868U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2                           (0x0000086CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L                        (0x00000870U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_H                        (0x00000874U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L                          (0x00000878U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_H                          (0x0000087CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL                                (0x00000880U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0                           (0x00000884U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1                           (0x00000888U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2                           (0x0000088CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L                        (0x00000890U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_H                        (0x00000894U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L                          (0x00000898U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_H                          (0x0000089CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL                                (0x000008A0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0                           (0x000008A4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1                           (0x000008A8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2                           (0x000008ACU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L                        (0x000008B0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_H                        (0x000008B4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L                          (0x000008B8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_H                          (0x000008BCU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL                                (0x000008C0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0                           (0x000008C4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1                           (0x000008C8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2                           (0x000008CCU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L                        (0x000008D0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_H                        (0x000008D4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L                          (0x000008D8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_H                          (0x000008DCU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL                                (0x000008E0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0                           (0x000008E4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1                           (0x000008E8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2                           (0x000008ECU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L                        (0x000008F0U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_H                        (0x000008F4U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L                          (0x000008F8U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_H                          (0x000008FCU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL                                (0x00000C00U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0                           (0x00000C04U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1                           (0x00000C08U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2                           (0x00000C0CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L                        (0x00000C10U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_H                        (0x00000C14U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L                          (0x00000C18U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_H                          (0x00000C1CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL                                (0x00000C20U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0                           (0x00000C24U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1                           (0x00000C28U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2                           (0x00000C2CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L                        (0x00000C30U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_H                        (0x00000C34U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L                          (0x00000C38U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_H                          (0x00000C3CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL                                (0x00000C40U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0                           (0x00000C44U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1                           (0x00000C48U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2                           (0x00000C4CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L                        (0x00000C50U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_H                        (0x00000C54U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L                          (0x00000C58U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_H                          (0x00000C5CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL                                (0x00000C60U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0                           (0x00000C64U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1                           (0x00000C68U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2                           (0x00000C6CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L                        (0x00000C70U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_H                        (0x00000C74U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L                          (0x00000C78U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_H                          (0x00000C7CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL                                (0x00000C80U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0                           (0x00000C84U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1                           (0x00000C88U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2                           (0x00000C8CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L                        (0x00000C90U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_H                        (0x00000C94U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L                          (0x00000C98U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_H                          (0x00000C9CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL                                (0x00000CA0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0                           (0x00000CA4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1                           (0x00000CA8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2                           (0x00000CACU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L                        (0x00000CB0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_H                        (0x00000CB4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L                          (0x00000CB8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_H                          (0x00000CBCU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL                                (0x00000CC0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0                           (0x00000CC4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1                           (0x00000CC8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2                           (0x00000CCCU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L                        (0x00000CD0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_H                        (0x00000CD4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L                          (0x00000CD8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_H                          (0x00000CDCU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL                                (0x00000CE0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0                           (0x00000CE4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1                           (0x00000CE8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2                           (0x00000CECU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L                        (0x00000CF0U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_H                        (0x00000CF4U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L                          (0x00000CF8U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_H                          (0x00000CFCU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* MSRAM0_FW_REGION_0_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_0_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_0_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_0_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_1_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_1_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_1_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_1_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_2_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_2_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_2_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_2_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_2_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_2_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_2_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_2_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_3_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_3_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_3_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_3_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_3_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_3_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_3_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_3_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_4_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_4_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_4_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_4_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_4_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_4_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_4_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_4_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_5_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_5_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_5_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_5_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_5_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_5_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_5_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_5_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_6_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_6_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_6_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_6_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_6_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_6_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_6_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_6_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM0_FW_REGION_7_CONTROL */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM0_FW_REGION_7_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_7_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_7_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM0_FW_REGION_7_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM0_FW_REGION_7_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM0_FW_REGION_7_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM0_FW_REGION_7_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM0_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_0_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_0_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_0_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_0_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_1_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_1_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_1_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_1_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_2_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_2_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_2_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_2_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_2_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_2_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_2_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_2_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_3_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_3_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_3_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_3_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_3_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_3_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_3_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_3_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_4_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_4_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_4_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_4_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_4_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_4_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_4_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_4_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_5_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_5_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_5_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_5_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_5_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_5_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_5_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_5_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_6_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_6_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_6_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_6_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_6_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_6_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_6_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_6_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM1_FW_REGION_7_CONTROL */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM1_FW_REGION_7_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_7_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_7_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM1_FW_REGION_7_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM1_FW_REGION_7_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM1_FW_REGION_7_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM1_FW_REGION_7_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM1_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_0_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_0_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_0_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_0_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_1_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_1_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_1_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_1_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_2_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_2_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_2_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_2_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_2_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_2_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_2_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_2_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_3_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_3_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_3_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_3_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_3_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_3_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_3_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_3_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_4_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_4_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_4_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_4_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_4_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_4_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_4_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_4_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_5_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_5_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_5_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_5_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_5_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_5_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_5_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_5_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_6_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_6_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_6_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_6_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_6_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_6_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_6_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_6_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM2_FW_REGION_7_CONTROL */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM2_FW_REGION_7_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_7_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_7_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM2_FW_REGION_7_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM2_FW_REGION_7_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM2_FW_REGION_7_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM2_FW_REGION_7_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM2_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_0_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_0_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_0_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_0_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_1_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_1_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_1_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_1_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_2_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_2_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_2_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_2_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_2_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_2_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_2_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_2_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_3_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_3_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_3_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_3_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_3_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_3_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_3_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_3_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_4_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_4_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_4_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_4_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_4_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_4_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_4_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_4_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_5_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_5_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_5_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_5_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_5_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_5_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_5_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_5_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_6_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_6_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_6_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_6_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_6_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_6_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_6_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_6_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/* MSRAM3_FW_REGION_7_CONTROL */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_ENABLE_MASK                    (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_ENABLE_SHIFT                   (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_ENABLE_MAX                     (0x0000000FU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_LOCK_MASK                      (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_LOCK_SHIFT                     (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_LOCK_MAX                       (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_BACKGROUND_MASK                (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_BACKGROUND_SHIFT               (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_BACKGROUND_MAX                 (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_CACHE_MODE_MASK                (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_CACHE_MODE_SHIFT               (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_CONTROL_CACHE_MODE_MAX                 (0x00000001U)

/* MSRAM3_FW_REGION_7_PERMISSION_0 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_0_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_7_PERMISSION_1 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_1_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_7_PERMISSION_2 */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MASK       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MASK        (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_SHIFT       (0x00000001U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK   (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT  (0x00000002U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MASK       (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT      (0x00000003U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_SUPV_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MASK       (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_SHIFT      (0x00000004U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_WRITE_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MASK        (0x00000020U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_READ_SHIFT       (0x00000005U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_READ_MAX         (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MASK   (0x00000040U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT  (0x00000006U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_CACHEABLE_MAX    (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MASK       (0x00000080U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_SHIFT      (0x00000007U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_SEC_USER_DEBUG_MAX        (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MASK    (0x00000100U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT   (0x00000008U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MASK     (0x00000200U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_SHIFT    (0x00000009U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK    (0x00000800U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT   (0x0000000BU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MASK    (0x00001000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_SHIFT   (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_WRITE_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MASK     (0x00002000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_SHIFT    (0x0000000DU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_READ_MAX      (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MASK    (0x00008000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT   (0x0000000FU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_NONSEC_USER_DEBUG_MAX     (0x00000001U)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_PRIV_ID_MASK              (0x00FF0000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_PRIV_ID_SHIFT             (0x00000010U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_PERMISSION_2_PRIV_ID_MAX               (0x000000FFU)

/* MSRAM3_FW_REGION_7_START_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX  (0x00000FFFU)

/* MSRAM3_FW_REGION_7_START_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX    (0x0000FFFFU)

/* MSRAM3_FW_REGION_7_END_ADDRESS_L */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK       (0xFFFFF000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT      (0x0000000CU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX        (0x000FFFFFU)

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK     (0x00000FFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT    (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX      (0x00000FFFU)

/* MSRAM3_FW_REGION_7_END_ADDRESS_H */

#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK       (0x0000FFFFU)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT      (0x00000000U)
#define CSL_CBASS_FW_MSRAM3_FW_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX        (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t VISS0_MST_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_16[12];
    volatile uint32_t VISS0_MST_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t VISS0_MST_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t VISS0_MST_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t VISS0_MST_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t VISS0_MST_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_48[12];
    volatile uint32_t VISS0_MST_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t VISS0_MST_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t VISS0_MST_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t VISS0_MST_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t VISS0_MST_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_2048[1980];
    volatile uint32_t LDC0_MST_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_2064[12];
    volatile uint32_t LDC0_MST_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t LDC0_MST_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t LDC0_MST_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t LDC0_MST_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t LDC0_MST_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_2096[12];
    volatile uint32_t LDC0_MST_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t LDC0_MST_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t LDC0_MST_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t LDC0_MST_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t LDC0_MST_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_4096[1980];
    volatile uint32_t MSC_MST_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_4112[12];
    volatile uint32_t MSC_MST_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_4144[12];
    volatile uint32_t MSC_MST_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_4176[12];
    volatile uint32_t MSC_MST_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_4208[12];
    volatile uint32_t MSC_MST_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t MSC_MST_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t MSC_MST_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_5120[892];
    volatile uint32_t NF_MST_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_5136[12];
    volatile uint32_t NF_MST_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t NF_MST_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t NF_MST_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t NF_MST_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t NF_MST_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_5168[12];
    volatile uint32_t NF_MST_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t NF_MST_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t NF_MST_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t NF_MST_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t NF_MST_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
} CSL_cbass_iscRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL                           (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L                   (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_H                   (0x00000014U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L                     (0x00000018U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_H                     (0x0000001CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL                           (0x00000020U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L                   (0x00000030U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_H                   (0x00000034U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L                     (0x00000038U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_H                     (0x0000003CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL                         (0x00000040U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL                            (0x00000800U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L                    (0x00000810U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_H                    (0x00000814U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L                      (0x00000818U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_H                      (0x0000081CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL                            (0x00000820U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L                    (0x00000830U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_H                    (0x00000834U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L                      (0x00000838U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_H                      (0x0000083CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL                          (0x00000840U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL                             (0x00001000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L                     (0x00001010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_H                     (0x00001014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L                       (0x00001018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_H                       (0x0000101CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL                             (0x00001020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L                     (0x00001030U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_H                     (0x00001034U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L                       (0x00001038U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_H                       (0x0000103CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL                             (0x00001040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L                     (0x00001050U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_H                     (0x00001054U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L                       (0x00001058U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_H                       (0x0000105CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL                             (0x00001060U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L                     (0x00001070U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_H                     (0x00001074U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L                       (0x00001078U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_H                       (0x0000107CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL                           (0x00001080U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL                              (0x00001400U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L                      (0x00001410U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_H                      (0x00001414U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L                        (0x00001418U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_H                        (0x0000141CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL                              (0x00001420U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L                      (0x00001430U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_H                      (0x00001434U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L                        (0x00001438U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_H                        (0x0000143CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL                            (0x00001440U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* VISS0_MST_ISC_REGION_0_CONTROL */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_ENABLE_MASK               (0x0000000FU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_ENABLE_SHIFT              (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_ENABLE_MAX                (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_LOCK_MASK                 (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_LOCK_SHIFT                (0x00000004U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_LOCK_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_CH_MODE_MASK              (0x00000020U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_CH_MODE_SHIFT             (0x00000005U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_CH_MODE_MAX               (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_DEF_MASK                  (0x00000040U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_DEF_SHIFT                 (0x00000006U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_DEF_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_ID_MASK              (0x0000FF00U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT             (0x00000008U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_ID_MAX               (0x000000FFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_SEC_MASK                  (0x000F0000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_SEC_SHIFT                 (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_SEC_MAX                   (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NONSEC_MASK               (0x00100000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NONSEC_SHIFT              (0x00000014U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NONSEC_MAX                (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PASS_MASK                 (0x00200000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PASS_SHIFT                (0x00000015U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PASS_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_MASK                 (0x03000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_SHIFT                (0x00000018U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_PRIV_MAX                  (0x00000003U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NOPRIV_MASK               (0x0C000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NOPRIV_SHIFT              (0x0000001AU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_CONTROL_NOPRIV_MAX                (0x00000003U)

/* VISS0_MST_ISC_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* VISS0_MST_ISC_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* VISS0_MST_ISC_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK  (0xFFFFF000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX   (0x000FFFFFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

/* VISS0_MST_ISC_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK  (0x0000FFFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX   (0x0000FFFFU)

/* VISS0_MST_ISC_REGION_1_CONTROL */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_ENABLE_MASK               (0x0000000FU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_ENABLE_SHIFT              (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_ENABLE_MAX                (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_LOCK_MASK                 (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_LOCK_SHIFT                (0x00000004U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_LOCK_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_CH_MODE_MASK              (0x00000020U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_CH_MODE_SHIFT             (0x00000005U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_CH_MODE_MAX               (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_DEF_MASK                  (0x00000040U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_DEF_SHIFT                 (0x00000006U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_DEF_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_ID_MASK              (0x0000FF00U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT             (0x00000008U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_ID_MAX               (0x000000FFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_SEC_MASK                  (0x000F0000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_SEC_SHIFT                 (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_SEC_MAX                   (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NONSEC_MASK               (0x00100000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NONSEC_SHIFT              (0x00000014U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NONSEC_MAX                (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PASS_MASK                 (0x00200000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PASS_SHIFT                (0x00000015U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PASS_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_MASK                 (0x03000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_SHIFT                (0x00000018U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_PRIV_MAX                  (0x00000003U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NOPRIV_MASK               (0x0C000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NOPRIV_SHIFT              (0x0000001AU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_CONTROL_NOPRIV_MAX                (0x00000003U)

/* VISS0_MST_ISC_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* VISS0_MST_ISC_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* VISS0_MST_ISC_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK  (0xFFFFF000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX   (0x000FFFFFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

/* VISS0_MST_ISC_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK  (0x0000FFFFU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX   (0x0000FFFFU)

/* VISS0_MST_ISC_REGION_DEF_CONTROL */

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_ENABLE_MASK             (0x0000000FU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT            (0x00000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_ENABLE_MAX              (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_LOCK_MASK               (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_LOCK_SHIFT              (0x00000004U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_LOCK_MAX                (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MASK            (0x00000020U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT           (0x00000005U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MAX             (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_DEF_MASK                (0x00000040U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_DEF_SHIFT               (0x00000006U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_DEF_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK            (0x0000FF00U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT           (0x00000008U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX             (0x000000FFU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_SEC_MASK                (0x000F0000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_SEC_SHIFT               (0x00000010U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_SEC_MAX                 (0x0000000FU)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NONSEC_MASK             (0x00100000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT            (0x00000014U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NONSEC_MAX              (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PASS_MASK               (0x00200000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PASS_SHIFT              (0x00000015U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PASS_MAX                (0x00000001U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_MASK               (0x03000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_SHIFT              (0x00000018U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_PRIV_MAX                (0x00000003U)

#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MASK             (0x0C000000U)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT            (0x0000001AU)
#define CSL_CBASS_ISC_VISS0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MAX              (0x00000003U)

/* LDC0_MST_ISC_REGION_0_CONTROL */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_ENABLE_MASK                (0x0000000FU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_ENABLE_SHIFT               (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_ENABLE_MAX                 (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_LOCK_MASK                  (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_LOCK_SHIFT                 (0x00000004U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_LOCK_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_CH_MODE_MASK               (0x00000020U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_CH_MODE_SHIFT              (0x00000005U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_CH_MODE_MAX                (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_DEF_MASK                   (0x00000040U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_DEF_SHIFT                  (0x00000006U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_DEF_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_ID_MASK               (0x0000FF00U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT              (0x00000008U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_ID_MAX                (0x000000FFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_SEC_MASK                   (0x000F0000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_SEC_SHIFT                  (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_SEC_MAX                    (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NONSEC_MASK                (0x00100000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NONSEC_SHIFT               (0x00000014U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NONSEC_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PASS_MASK                  (0x00200000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PASS_SHIFT                 (0x00000015U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PASS_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_MASK                  (0x03000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_SHIFT                 (0x00000018U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_PRIV_MAX                   (0x00000003U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NOPRIV_MASK                (0x0C000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NOPRIV_SHIFT               (0x0000001AU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_CONTROL_NOPRIV_MAX                 (0x00000003U)

/* LDC0_MST_ISC_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* LDC0_MST_ISC_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* LDC0_MST_ISC_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX  (0x00000FFFU)

/* LDC0_MST_ISC_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX    (0x0000FFFFU)

/* LDC0_MST_ISC_REGION_1_CONTROL */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_ENABLE_MASK                (0x0000000FU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_ENABLE_SHIFT               (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_ENABLE_MAX                 (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_LOCK_MASK                  (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_LOCK_SHIFT                 (0x00000004U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_LOCK_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_CH_MODE_MASK               (0x00000020U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_CH_MODE_SHIFT              (0x00000005U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_CH_MODE_MAX                (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_DEF_MASK                   (0x00000040U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_DEF_SHIFT                  (0x00000006U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_DEF_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_ID_MASK               (0x0000FF00U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT              (0x00000008U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_ID_MAX                (0x000000FFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_SEC_MASK                   (0x000F0000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_SEC_SHIFT                  (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_SEC_MAX                    (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NONSEC_MASK                (0x00100000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NONSEC_SHIFT               (0x00000014U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NONSEC_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PASS_MASK                  (0x00200000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PASS_SHIFT                 (0x00000015U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PASS_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_MASK                  (0x03000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_SHIFT                 (0x00000018U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_PRIV_MAX                   (0x00000003U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NOPRIV_MASK                (0x0C000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NOPRIV_SHIFT               (0x0000001AU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_CONTROL_NOPRIV_MAX                 (0x00000003U)

/* LDC0_MST_ISC_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* LDC0_MST_ISC_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* LDC0_MST_ISC_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK   (0xFFFFF000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT  (0x0000000CU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX    (0x000FFFFFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX  (0x00000FFFU)

/* LDC0_MST_ISC_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK   (0x0000FFFFU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT  (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX    (0x0000FFFFU)

/* LDC0_MST_ISC_REGION_DEF_CONTROL */

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_ENABLE_MASK              (0x0000000FU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT             (0x00000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_ENABLE_MAX               (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_LOCK_MASK                (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_LOCK_SHIFT               (0x00000004U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_LOCK_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MASK             (0x00000020U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT            (0x00000005U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MAX              (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_DEF_MASK                 (0x00000040U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_DEF_SHIFT                (0x00000006U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_DEF_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK             (0x0000FF00U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT            (0x00000008U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX              (0x000000FFU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_SEC_MASK                 (0x000F0000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_SEC_SHIFT                (0x00000010U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_SEC_MAX                  (0x0000000FU)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NONSEC_MASK              (0x00100000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT             (0x00000014U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NONSEC_MAX               (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PASS_MASK                (0x00200000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PASS_SHIFT               (0x00000015U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PASS_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_MASK                (0x03000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_SHIFT               (0x00000018U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_PRIV_MAX                 (0x00000003U)

#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MASK              (0x0C000000U)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT             (0x0000001AU)
#define CSL_CBASS_ISC_LDC0_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MAX               (0x00000003U)

/* MSC_MST_ISC_REGION_0_CONTROL */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_ENABLE_MASK                 (0x0000000FU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_ENABLE_SHIFT                (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_ENABLE_MAX                  (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_LOCK_MASK                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_LOCK_SHIFT                  (0x00000004U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_LOCK_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_CH_MODE_MASK                (0x00000020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_CH_MODE_SHIFT               (0x00000005U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_CH_MODE_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_DEF_MASK                    (0x00000040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_DEF_SHIFT                   (0x00000006U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_DEF_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_ID_MASK                (0x0000FF00U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT               (0x00000008U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_ID_MAX                 (0x000000FFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_SEC_MASK                    (0x000F0000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_SEC_SHIFT                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_SEC_MAX                     (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NONSEC_MASK                 (0x00100000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NONSEC_SHIFT                (0x00000014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NONSEC_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PASS_MASK                   (0x00200000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PASS_SHIFT                  (0x00000015U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PASS_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_MASK                   (0x03000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_SHIFT                  (0x00000018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_PRIV_MAX                    (0x00000003U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NOPRIV_MASK                 (0x0C000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NOPRIV_SHIFT                (0x0000001AU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_CONTROL_NOPRIV_MAX                  (0x00000003U)

/* MSC_MST_ISC_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* MSC_MST_ISC_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* MSC_MST_ISC_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK    (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT   (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX     (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK  (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX   (0x00000FFFU)

/* MSC_MST_ISC_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK    (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT   (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX     (0x0000FFFFU)

/* MSC_MST_ISC_REGION_1_CONTROL */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_ENABLE_MASK                 (0x0000000FU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_ENABLE_SHIFT                (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_ENABLE_MAX                  (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_LOCK_MASK                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_LOCK_SHIFT                  (0x00000004U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_LOCK_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_CH_MODE_MASK                (0x00000020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_CH_MODE_SHIFT               (0x00000005U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_CH_MODE_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_DEF_MASK                    (0x00000040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_DEF_SHIFT                   (0x00000006U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_DEF_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_ID_MASK                (0x0000FF00U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT               (0x00000008U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_ID_MAX                 (0x000000FFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_SEC_MASK                    (0x000F0000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_SEC_SHIFT                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_SEC_MAX                     (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NONSEC_MASK                 (0x00100000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NONSEC_SHIFT                (0x00000014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NONSEC_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PASS_MASK                   (0x00200000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PASS_SHIFT                  (0x00000015U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PASS_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_MASK                   (0x03000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_SHIFT                  (0x00000018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_PRIV_MAX                    (0x00000003U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NOPRIV_MASK                 (0x0C000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NOPRIV_SHIFT                (0x0000001AU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_CONTROL_NOPRIV_MAX                  (0x00000003U)

/* MSC_MST_ISC_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* MSC_MST_ISC_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* MSC_MST_ISC_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK    (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT   (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX     (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK  (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX   (0x00000FFFU)

/* MSC_MST_ISC_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK    (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT   (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX     (0x0000FFFFU)

/* MSC_MST_ISC_REGION_2_CONTROL */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_ENABLE_MASK                 (0x0000000FU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_ENABLE_SHIFT                (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_ENABLE_MAX                  (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_LOCK_MASK                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_LOCK_SHIFT                  (0x00000004U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_LOCK_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_CH_MODE_MASK                (0x00000020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_CH_MODE_SHIFT               (0x00000005U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_CH_MODE_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_DEF_MASK                    (0x00000040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_DEF_SHIFT                   (0x00000006U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_DEF_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_ID_MASK                (0x0000FF00U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT               (0x00000008U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_ID_MAX                 (0x000000FFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_SEC_MASK                    (0x000F0000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_SEC_SHIFT                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_SEC_MAX                     (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NONSEC_MASK                 (0x00100000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NONSEC_SHIFT                (0x00000014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NONSEC_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PASS_MASK                   (0x00200000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PASS_SHIFT                  (0x00000015U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PASS_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_MASK                   (0x03000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_SHIFT                  (0x00000018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_PRIV_MAX                    (0x00000003U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NOPRIV_MASK                 (0x0C000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NOPRIV_SHIFT                (0x0000001AU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_CONTROL_NOPRIV_MAX                  (0x00000003U)

/* MSC_MST_ISC_REGION_2_START_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* MSC_MST_ISC_REGION_2_START_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* MSC_MST_ISC_REGION_2_END_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK    (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT   (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX     (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK  (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX   (0x00000FFFU)

/* MSC_MST_ISC_REGION_2_END_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK    (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT   (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX     (0x0000FFFFU)

/* MSC_MST_ISC_REGION_3_CONTROL */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_ENABLE_MASK                 (0x0000000FU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_ENABLE_SHIFT                (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_ENABLE_MAX                  (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_LOCK_MASK                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_LOCK_SHIFT                  (0x00000004U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_LOCK_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_CH_MODE_MASK                (0x00000020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_CH_MODE_SHIFT               (0x00000005U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_CH_MODE_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_DEF_MASK                    (0x00000040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_DEF_SHIFT                   (0x00000006U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_DEF_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_ID_MASK                (0x0000FF00U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT               (0x00000008U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_ID_MAX                 (0x000000FFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_SEC_MASK                    (0x000F0000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_SEC_SHIFT                   (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_SEC_MAX                     (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NONSEC_MASK                 (0x00100000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NONSEC_SHIFT                (0x00000014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NONSEC_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PASS_MASK                   (0x00200000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PASS_SHIFT                  (0x00000015U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PASS_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_MASK                   (0x03000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_SHIFT                  (0x00000018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_PRIV_MAX                    (0x00000003U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NOPRIV_MASK                 (0x0C000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NOPRIV_SHIFT                (0x0000001AU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_CONTROL_NOPRIV_MAX                  (0x00000003U)

/* MSC_MST_ISC_REGION_3_START_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* MSC_MST_ISC_REGION_3_START_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

/* MSC_MST_ISC_REGION_3_END_ADDRESS_L */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK    (0xFFFFF000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT   (0x0000000CU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX     (0x000FFFFFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK  (0x00000FFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX   (0x00000FFFU)

/* MSC_MST_ISC_REGION_3_END_ADDRESS_H */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK    (0x0000FFFFU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT   (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX     (0x0000FFFFU)

/* MSC_MST_ISC_REGION_DEF_CONTROL */

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_ENABLE_MASK               (0x0000000FU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT              (0x00000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_ENABLE_MAX                (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_LOCK_MASK                 (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_LOCK_SHIFT                (0x00000004U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_LOCK_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MASK              (0x00000020U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT             (0x00000005U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MAX               (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_DEF_MASK                  (0x00000040U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_DEF_SHIFT                 (0x00000006U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_DEF_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK              (0x0000FF00U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT             (0x00000008U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX               (0x000000FFU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_SEC_MASK                  (0x000F0000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_SEC_SHIFT                 (0x00000010U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_SEC_MAX                   (0x0000000FU)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NONSEC_MASK               (0x00100000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT              (0x00000014U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NONSEC_MAX                (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PASS_MASK                 (0x00200000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PASS_SHIFT                (0x00000015U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PASS_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_MASK                 (0x03000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_SHIFT                (0x00000018U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_PRIV_MAX                  (0x00000003U)

#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MASK               (0x0C000000U)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT              (0x0000001AU)
#define CSL_CBASS_ISC_MSC_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MAX                (0x00000003U)

/* NF_MST_ISC_REGION_0_CONTROL */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_ENABLE_MASK                  (0x0000000FU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_ENABLE_SHIFT                 (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_ENABLE_MAX                   (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_LOCK_MASK                    (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_LOCK_SHIFT                   (0x00000004U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_LOCK_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_CH_MODE_MASK                 (0x00000020U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_CH_MODE_SHIFT                (0x00000005U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_CH_MODE_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_DEF_MASK                     (0x00000040U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_DEF_SHIFT                    (0x00000006U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_DEF_MAX                      (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_ID_MASK                 (0x0000FF00U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT                (0x00000008U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_ID_MAX                  (0x000000FFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_SEC_MASK                     (0x000F0000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_SEC_SHIFT                    (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_SEC_MAX                      (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NONSEC_MASK                  (0x00100000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NONSEC_SHIFT                 (0x00000014U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NONSEC_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PASS_MASK                    (0x00200000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PASS_SHIFT                   (0x00000015U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PASS_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_MASK                    (0x03000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_SHIFT                   (0x00000018U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_PRIV_MAX                     (0x00000003U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NOPRIV_MASK                  (0x0C000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NOPRIV_SHIFT                 (0x0000001AU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_CONTROL_NOPRIV_MAX                   (0x00000003U)

/* NF_MST_ISC_REGION_0_START_ADDRESS_L */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX  (0x000FFFFFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* NF_MST_ISC_REGION_0_START_ADDRESS_H */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX  (0x0000FFFFU)

/* NF_MST_ISC_REGION_0_END_ADDRESS_L */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK     (0xFFFFF000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT    (0x0000000CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX      (0x000FFFFFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK   (0x00000FFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT  (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX    (0x00000FFFU)

/* NF_MST_ISC_REGION_0_END_ADDRESS_H */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK     (0x0000FFFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT    (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX      (0x0000FFFFU)

/* NF_MST_ISC_REGION_1_CONTROL */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_ENABLE_MASK                  (0x0000000FU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_ENABLE_SHIFT                 (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_ENABLE_MAX                   (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_LOCK_MASK                    (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_LOCK_SHIFT                   (0x00000004U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_LOCK_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_CH_MODE_MASK                 (0x00000020U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_CH_MODE_SHIFT                (0x00000005U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_CH_MODE_MAX                  (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_DEF_MASK                     (0x00000040U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_DEF_SHIFT                    (0x00000006U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_DEF_MAX                      (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_ID_MASK                 (0x0000FF00U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT                (0x00000008U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_ID_MAX                  (0x000000FFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_SEC_MASK                     (0x000F0000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_SEC_SHIFT                    (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_SEC_MAX                      (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NONSEC_MASK                  (0x00100000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NONSEC_SHIFT                 (0x00000014U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NONSEC_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PASS_MASK                    (0x00200000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PASS_SHIFT                   (0x00000015U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PASS_MAX                     (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_MASK                    (0x03000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_SHIFT                   (0x00000018U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_PRIV_MAX                     (0x00000003U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NOPRIV_MASK                  (0x0C000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NOPRIV_SHIFT                 (0x0000001AU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_CONTROL_NOPRIV_MAX                   (0x00000003U)

/* NF_MST_ISC_REGION_1_START_ADDRESS_L */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX  (0x000FFFFFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

/* NF_MST_ISC_REGION_1_START_ADDRESS_H */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX  (0x0000FFFFU)

/* NF_MST_ISC_REGION_1_END_ADDRESS_L */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK     (0xFFFFF000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT    (0x0000000CU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX      (0x000FFFFFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK   (0x00000FFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT  (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX    (0x00000FFFU)

/* NF_MST_ISC_REGION_1_END_ADDRESS_H */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK     (0x0000FFFFU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT    (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX      (0x0000FFFFU)

/* NF_MST_ISC_REGION_DEF_CONTROL */

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_ENABLE_MASK                (0x0000000FU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT               (0x00000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_ENABLE_MAX                 (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_LOCK_MASK                  (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_LOCK_SHIFT                 (0x00000004U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_LOCK_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MASK               (0x00000020U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT              (0x00000005U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_CH_MODE_MAX                (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_DEF_MASK                   (0x00000040U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_DEF_SHIFT                  (0x00000006U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_DEF_MAX                    (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK               (0x0000FF00U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT              (0x00000008U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX                (0x000000FFU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_SEC_MASK                   (0x000F0000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_SEC_SHIFT                  (0x00000010U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_SEC_MAX                    (0x0000000FU)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NONSEC_MASK                (0x00100000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT               (0x00000014U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NONSEC_MAX                 (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PASS_MASK                  (0x00200000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PASS_SHIFT                 (0x00000015U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PASS_MAX                   (0x00000001U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_MASK                  (0x03000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_SHIFT                 (0x00000018U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_PRIV_MAX                   (0x00000003U)

#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MASK                (0x0C000000U)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT               (0x0000001AU)
#define CSL_CBASS_ISC_NF_MST_ISC_REGION_DEF_CONTROL_NOPRIV_MAX                 (0x00000003U)

#ifdef __cplusplus
}
#endif
#endif
