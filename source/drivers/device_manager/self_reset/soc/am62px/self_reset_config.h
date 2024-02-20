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
 */

/**
 *  \file self_reset_config.h
 *
 *  \brief File containing the soc specific flags for dm r5 self reset.
 */

#ifndef SOC_AM62P_SELF_RESET_CONFIG_H
#define SOC_AM62P_SELF_RESET_CONFIG_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_hosts.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Processor ID for Device manager core */
#define SELF_RESET_PROCESSOR_ID         SCICLIENT_DEV_WKUP_R5FSS0_CORE0_PROCID

/** \brief Device ID for Device manager core */
#define SELF_RESET_DEVICE_ID            TISCI_DEV_R5FSS0_CORE0

/** \brief BOOT vector address for Device manager core */
#define SELF_RESET_BOOT_ADDRESS_LOW     0x00000000

/** \brief Flags to set during self reset of Device manager core */
#define SELF_RESET_SET_CONFIG_FLAGS     TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS

/** \brief Flags to clear during self reset of Device manager core */
#define SELF_RESET_CLEAR_CONFIGD_FLAGS  TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE

/** \brief Address at which vector table has to be copied before self reset */
#define SELF_RESET_TCM_ADDRESS_OFFSET   0x41010000

/** \brief Host ID requesting self reset of Device manager core */
#define SELF_RESET_DM_R5_HOST_ID        TISCI_HOST_ID_DM2TIFS

#if defined (CONFIG_LPM_DM)
/** \brief CANUART off mode magic word to detect IO Only plus DDR LPM exit */
#define SELF_RESET_CANUART_OFF_MODE_MAGIC_WORD     0x555555U
#endif

/* ========================================================================== */
/*                          Functions                                         */
/* ========================================================================== */

#if defined (CONFIG_LPM_DM)
/**
 * \brief Get CANUART off mode magic word value
 *
 * \return Value at the CANUART magic word MMR
 */
static inline uint32_t SelfReset_CANUARTGetMagicWordVal(void)
{
    return CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_OFF_MODE_STAT);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* SOC_AM62P_SELF_RESET_CONFIG_H */
