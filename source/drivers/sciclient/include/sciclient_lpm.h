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
/**
 * \ingroup DRV_SCICLIENT_MODULE
 * \defgroup SCICLIENT_FMW_LPM_IF Sciclient LPM API Interface
 *
 *
 * @{
 */
/**
 *  \file   sciclient_lpm.h
 *
 *  \brief  This file contains the definition of all the message IDs, message
 *          formats to be able to interact with the System Controller firmware
 *          for low power modes.
 */

#ifndef SCICLIENT_LPM_H_
#define SCICLIENT_LPM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

enum gLPMSysModes {
    TISCI_LPM_SYS_MODE_DEEP_SLEEP = 0U,
    TISCI_LPM_SYS_MODE_MCU_ONLY,
    TISCI_LPM_SYS_MODE_IO_ONLY_PLUS_DDR,
    TISCI_LPM_SYS_MODE_PARTIAL_IO,
    TISCI_LPM_SYS_MODE_STANDBY,
    TISCI_LPM_SYS_MODE_NOT_SELECTED = 0xFEU,
};

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief    Message to get the next system mode.
 *
 *  \n<b>Message</b>:    #TISCI_MSG_LPM_GET_NEXT_SYS_MODE
 *  \n<b>Request</b>:    #tisci_msg_lpm_get_next_sys_mode_req
 *  \n<b>Response</b>:   #tisci_msg_lpm_get_next_sys_mode_resp
 *
 *  \param  sysMode          Next system mode returned.
 *  \param  timeout          Gives a sense of how long to wait for the
 *                           operation. Refer
 *                           \ref SystemP_Timeout.
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_lpmGetNextSysMode(uint32_t timeout,
                                    uint8_t *sysMode);

/**
 *  \brief    Message to get the next host state.
 *
 *  \n<b>Message</b>:    #TISCI_MSG_LPM_GET_NEXT_HOST_STATE
 *  \n<b>Request</b>:    #tisci_msg_lpm_get_next_host_state_req
 *  \n<b>Response</b>:   #tisci_msg_lpm_get_next_host_state_resp
 *
 *  \param  hostState        Next host state returned.
 *  \param  timeout          Gives a sense of how long to wait for the
 *                           operation. Refer
 *                           \ref SystemP_Timeout.
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_lpmGetNextHostState(uint32_t timeout,
                                      uint8_t *hostState);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_LPM_H_ */

/** @} */
