/*
 *  Copyright (c) Texas Instruments Incorporated 2024-25
 *  All rights reserved.
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
 */

#ifndef CAN_RESPONSE_CONFIG_H_
#define CAN_RESPONSE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MCAN_RESPONSE_APP_MCU_MCAN0_STB_PIN                    (0xC)
#define MCAN_RESPONSE_APP_MCAN_STD_ID_FILT_NUM                 (0U)
#define MCAN_RESPONSE_APP_MCAN_EXT_ID_FILT_NUM                 (0U)
#define MCAN_RESPONSE_APP_MCAN_TX_EVENT_SIZE                   (0U)
#define MCAN_RESPONSE_APP_MCAN_TX_BUFF_START_ADDR              (0U)
#define MCAN_RESPONSE_APP_MCAN_TX_BUFF_SIZE                    (2U)
#define MCAN_RESPONSE_APP_MCAN_TX_FIFO_SIZE                    (0U)
#define MCAN_RESPONSE_APP_MCAN_RX_FIFO_0_NUM                   (0U)
#define MCAN_RESPONSE_APP_MCAN_RX_FIFO_1_NUM                   (0U)
#define MCAN_RESPONSE_APP_MCAN_RX_BUFF_START_ADDR              (80U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  This function will enable CAN transceivers
 *
 * \param  None
 *
 * \return None
 */
void CanResponseApp_enableTransceivers(void);

/**
 * \brief  This function transmits a CAN message
 *
 * \param  None
 *
 * \return None
 */
void CanResponseApp_transmit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CAN_RESPONSE_CONFIG_H_ */