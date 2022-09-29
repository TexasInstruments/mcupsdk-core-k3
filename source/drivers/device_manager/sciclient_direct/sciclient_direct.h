/*
 *  Copyright (C) 2018 Texas Instruments Incorporated
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
 * \defgroup SCICLIENT_FMW_DIRECT_IF Sciclient Direct API Interface
 *
 * Using DM services by on DM R5 with the help of sciclient direct.
 *
 *
 * @{
 */
/**
 *  \file   sciclient_direct.h
 *
 *  \brief  This file contains the declaration of internal structures necessary
 *          for Sciclient direct init for DM.
 */

#ifndef SCICLIENT_DIRECT_H_
#define SCICLIENT_DIRECT_H_

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* TISCI Include */
#define TISCI_BIT(n)  (1UL << (n))

/**
 * \brief Defines the sysfw DEVGRP type. This is meant to be used in code
 * or data structures that require distinction of devgrps.
 */
typedef uint8_t devgrp_t;

/**
 * \brief Defines the sysfw DOMGRP type. This is meant to be used in code
 * or data structures that require distinction of domgrps.
 */
typedef uint8_t domgrp_t;

/* External definitions */

/**
 * SoC SYSFW devgrp any: NOT TO BE used for SoC data.
 * This implies that specific sequenced devgrp is NOT used
 */
#define DEVGRP_ALL              (0x00U)

/** SoC defined SYSFW devgrp 00 */
#define DEVGRP_00               ((0x01U) << 0U)
/** SoC defined SYSFW devgrp 01 */
#define DEVGRP_01               ((0x01U) << 1U)
/** SoC defined SYSFW devgrp 02 */
#define DEVGRP_02               ((0x01U) << 2U)
/** SoC defined SYSFW devgrp 03 */
#define DEVGRP_03               ((0x01U) << 3U)
/** SoC defined SYSFW devgrp 04 */
#define DEVGRP_04               ((0x01U) << 4U)
/** SoC defined SYSFW devgrp 05 */
#define DEVGRP_05               ((0x01U) << 5U)
/** SoC defined SYSFW devgrp 06 */
#define DEVGRP_06               ((0x01U) << 6U)

/** SYSFW internal usage ONLY */

/** Module belonging solely to DMSC operations */
#define DEVGRP_DMSC             ((0x01U) << 7U)
/** Match everything - STRICTLY INTERNAL USAGE ONLY */
#define DEVGRP_DMSC_ALL         (0xFFU)

/**
 * Maximum number of devgrps that are supported by SYSFW.
 * Derived from the above definitions
 */
#define MAX_NUM_DEVGRPS (8U)

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/tisci_boardcfg_macros.h>
#include <drivers/sciclient/include/tisci/tisci_boardcfg.h>
#include <drivers/sciclient/include/tisci/tisci_boardcfg_rm.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#if defined (SOC_AM62X)
#include <drivers/sciclient/include/tisci/am62x/tisci_resasg_types.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_sec_proxy.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_boardcfg_constraints.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_devices.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_clocks.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_hosts.h>
#include <drivers/sciclient/include/am62x/sciclient_fmwMsgParams.h>
#endif
#if defined (SOC_AM62AX)
#include <drivers/sciclient/include/tisci/am62ax/tisci_resasg_types.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_sec_proxy.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_boardcfg_constraints.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_devices.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_clocks.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_hosts.h>
#include <drivers/sciclient/include/am62ax/sciclient_fmwMsgParams.h>
#endif
#include <drivers/sciclient/include/tisci/security/tisci_sec_macros.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/tisci/security/tisci_keystore.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
#include <drivers/sciclient/include/tisci/security/tisci_keywriter.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_clock.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_core.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_ra.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_irq.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_udmap.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_psil.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_shared.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_core.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_proxy.h>
#include <drivers/sciclient/include/tisci/security/tisci_sec_handover.h>
#include <drivers/sciclient/include/sciclient_pm.h>
#include <drivers/sciclient/include/sciclient_rm.h>
#include <drivers/sciclient/include/sciclient_firewall.h>
#include <drivers/sciclient/include/sciclient_dkek.h>
#include <drivers/sciclient/include/sciclient_procboot.h>
#include <drivers/sciclient/include/sciclient_boardcfg.h>

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief Input parameters for #Sciclient_service function.
 */
typedef struct
{
    uint16_t       messageType;
    /**< [IN] Type of message */
    uint32_t       flags;
    /**< [IN] Flags for messages that are being transmitted.
     *
     */
    const uint8_t *pReqPayload;
    /**< [IN] Pointer to the payload to be transmitted */
    uint32_t       reqPayloadSize;
    /**< [IN] Size of the payload to be transmitted (in bytes)*/
    uint32_t       timeout;
    /**< [IN] Timeout(number of iterations) for receiving response
     *        (Refer \ref SystemP_Timeout) */
    uint8_t        forwardStatus;
    /**< [IN] Indicates whether the request is being forwarded to another
     *        service provider. Only to be set internally by sciserver, if
     *        integrated into this build. Unused otherwise. */
} Sciclient_ReqPrm_t;

/**
 *  \brief Output parameters for #Sciclient_service function.
 */
typedef struct
{
    uint32_t flags;
    /**< [OUT] Flags of response to messages. */
    uint8_t *pRespPayload;
    /**< [IN] Pointer to the received payload. The pointer is an input. The
     *        API will populate this with the firmware response upto the
     *        size mentioned in respPayloadSize. Please ensure respPayloadSize
     *        bytes are allocated.
     */
    uint32_t respPayloadSize;
    /**< [IN] Size of the response payload(in bytes) */
} Sciclient_RespPrm_t;

/*
 *  \brief Initialization parameters for sciclient.
 *         Pointer to this is passed to #Sciclient_init.
 */
typedef struct
{
    uint32_t        opModeFlag;
    /**< Operation mode for the Sciclient Service API. Refer to
     * \ref Sciclient_ServiceOperationMode for valid values.
     */
    Sciclient_BoardCfgPrms_t * pBoardCfgPrms;
    /**< NULL will result in using default board configuration.
    * Refer #Sciclient_BoardCfgPrms_t
    */
    uint32_t              isSecureMode;
    /**< Variable to check whether Core context is secure/non-secure. This has
     * to be given by the user via configParams. Default value is 0.
     */
    uint32_t              c66xRatRegion;
    /**< C66x Rat region to use for mapping the IR */
    uint8_t skipLocalBoardCfgProcess;
    /**< Skip processing of local RM/PM board configurations during
     *   initialization */
    Sciclient_BoardCfgPrms_t inPmPrms;
    /**< Power Management Board Config Input Parameters */
    Sciclient_BoardCfgPrms_t inRmPrms;
    /**< Resource Management Board Config Input Parameters */
} Sciclient_ConfigPrms_t;

/**
 *  \brief Input parameters for #Sciclient_service function.
 */
typedef struct
{
    const uint32_t     *boardCfgLow;
    /**< [OUT] Pointer to default board config */
    const uint32_t     *boardCfgLowRm;
    /**< [OUT] Pointer to default board config for RM */
    const uint32_t     *boardCfgLowSec;
    /**< [OUT] Pointer to default board config for Security */
    const uint32_t     *boardCfgLowPm;
    /**< [OUT] Pointer to default board config for PM */
    uint32_t            boardCfgLowSize;
    /**< [OUT] Size in bytes for default board config */
    uint32_t            boardCfgLowRmSize;
    /**< [OUT] Size in bytes for default board config for RM */
    uint32_t            boardCfgLowSecSize;
    /**< [OUT] Size in bytes for default board config for Security */
    uint32_t            boardCfgLowPmSize;
    /**< [OUT] Size in bytes for default board config for PM */
} Sciclient_DefaultBoardCfgInfo_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief  API to initialise SCI direct client.
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */
int32_t Sciclient_direct_init(void);

/**
 *  \brief  Loads the DMSC firmware. This is typically called by SBL. Load
 *          firmware does not require calling the #Sciclient_init function.
 *
 *  \param pSciclient_firmware     [IN]  Pointer to signed SYSFW binary
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */
int32_t Sciclient_loadFirmware(const uint32_t *pSciclient_firmware);

/**
 *  \brief  This API is called once for registering interrupts and creating
 *          semaphore handles to be able to talk to the firmware.
 *          The application should assume that the firmware is pre-loaded while
 *          calling the #Sciclient_init API.
 *          The firmware should have been loaded either via GEL or via the SBL
 *          prior to the application calling the #Sciclient_init.
 *          If a void pointer is passed, default values will be used, else
 *          the values passed will be used.
 *          Only first Sciclient_init call configuration will take effect,
 *          subsequent calls will return pass witout overwriting the previous
 *          configuration
 *
 *  \param pCfgPrms     [IN]  Pointer to #Sciclient_ConfigPrms_t
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */
int32_t Sciclient_init(const Sciclient_ConfigPrms_t *pCfgPrms);

/**
 *  \brief  This API allows communicating with the System firmware which can be
 *          called to perform various functions in the system.
 *          Core sciclient function for transmitting payload and recieving
 *          the response.
 *          The caller is expected to allocate memory for the input request
 *          parameter (Refer #Sciclient_ReqPrm_t). This involves setting the
 *          message type being communicated to the firmware, the response flags,
 *          populate the payload of the message based on the inputs in the
 *          files sciclient_fmwPmMessages.h,sciclient_fmwRmMessages.h,
 *          sciclient_fmwSecMessages.h and sciclient_fmwCommonMessages.h.
 *          Since the payload in considered a stream of bytes in this API,
 *          the caller should also populate the size of this stream in
 *          reqPayloadSize. The timeout is used to determine for what amount
 *          of iterations the API would wait for their operation to complete.
 *
 *          To make sure the response is captured correctly the caller should
 *          also allocate the space for #Sciclient_RespPrm_t parameters. The
 *          caller should populate the pointer to the pRespPayload and the size
 *          respPayloadSize. The API would populate the response flags to
 *          indicate any firmware specific errors and also populate the memory
 *          pointed by pRespPayload till the size given in respPayloadSize.
 *
 *  \param pReqPrm        [IN]  Pointer to #Sciclient_ReqPrm_t
 *  \param pRespPrm       [OUT] Pointer to #Sciclient_RespPrm_t
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */
int32_t Sciclient_service(const Sciclient_ReqPrm_t *pReqPrm,
                          Sciclient_RespPrm_t      *pRespPrm);

/**
 *  \brief  De-initialization of sciclient. This de-initialization is specific
 *          to the application. It only de-initializes the semaphores,
 *          interrupts etc. which are initialized in #Sciclient_init. It does
 *          not de-initialize the system firmware.
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */

int32_t Sciclient_deinit(void);

/**<
 *  \brief   API to verify that firmware ABI matches the supported ABI.
 *
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_abiCheck(void);

/**
 *  \brief API to get the default board config info.
 *
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_getDefaultBoardCfgInfo(Sciclient_DefaultBoardCfgInfo_t *pBoardCfgInfo);

/**
 *  \brief Sciclient_ConfigPrms_t structure init function.
 *
 *  \param pCfgPrms     [IN] Pointer to #Sciclient_ConfigPrms_t structure.
 *
 */
int32_t Sciclient_configPrmsInit(Sciclient_ConfigPrms_t *pCfgPrms);

/**
 *  \brief Parse the header left behind by the SBL in the SCISERVER. This is
 *         used in the SCISERVER App to read the left behind header and
 *         configuration paramter.
 *  \param pCommonHeader Pointer to the common header which corresponds to the
 *                       format for the component left behind.
 *  \param pInPmPrms    Pointer to the PM parameters popolated by the API.
 *  \param pInRmPrms    Pointer to the RM parameters popolated by the API.
 *  \return ret SystemP_SUCCESS if the paramters are populated correctly.
 *              Fail otherwise.
 */
int32_t Sciclient_boardCfgParseHeader (
    uint8_t * pCommonHeader,
    Sciclient_BoardCfgPrms_t * pInPmPrms,
    Sciclient_BoardCfgPrms_t * pInRmPrms);

/**
 *  \brief   API to send a get version command to SYSFW and optionally log the results to console
 *
 *  \param doLog [in] 0: No logging to console, 1: log version results to console
 *
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_getVersionCheck(uint32_t doLog);

/**<
 *  \brief   API to get the TISCI Device ID of the core on which driver is currently running.
 *
 *  \return TISCI Dev ID of the core
 */
uint32_t Sciclient_getSelfDevIdCore(void);

/**
 *  \brief  Waits for boot notification from SYSFW
 *
 *  \return SystemP_SUCCESS on success, else failure
 *
 */
int32_t Sciclient_waitForBootNotification(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_DIRECT_H_ */
