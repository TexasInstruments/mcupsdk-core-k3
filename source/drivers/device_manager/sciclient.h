/*
 * Copyright (c) 2018-2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \defgroup DRV_SCICLIENT_MODULE SCIClient Driver
 *
 *  @{
 *
 * System Controller Interface (SCI) Client
 *
 * \par IMPORTANT NOTE
 *   <b> The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces. </b> \n
 *   <b> Refer to top level user guide for detailed features,
 *    limitations and usage description.
 *    </b>
 *
 *  ## Introduction to SCICLIENT
 *  The SCIClient is an interface to the TI-SCI protocol for RTOS and non-OS
 *  based applications. It exposes the core message details, valid module/clock
 *  IDs to the higher level software and abstracts the communication with the
 *  firmware based on the TI-SCI protocol. These APIs can be called by power,
 *  resource and security RTOS drivers or any other non-OS or RTOS based higher
 *  level software to be able to communicate with DMSC for its services. The
 *  higher level software is expected to populate the necessary message core
 *  parameters. The SCIClient would wrap the core message with the necessary
 *  protocol header and forward this to the DMSC. The SCIClient relies on the
 *  CSL-FL layer to program and interact with the Secure Proxy Threads. The
 *  SCIClient's goal is to ensure there is no duplication of the interface to
 *  the DMSC from different software components which need to interact with
 *  the DMSC or other System Control Entities in future devices.
 *  The Sciclient contains
 *  - \ref SCICLIENT_HAL
 *  - \ref SCICLIENT_FMW_PM_IF
 *  - \ref SCICLIENT_FMW_RM_IF
 *  - \ref SCICLIENT_FMW_PROCBOOT_IF
 *  - \ref SCICLIENT_ROM_HAL
 *
 * ## Introduction to DMSC
 * Traditional Texas Instruments SoCs have implemented system control
 * functions such as power management within operating systems on each of
 * the processing units (ARM/DSP). However, such a traditional approach
 * has had tremendous challenges to ensure system stability. Few of the
 * challenges faced include:
 *
 * - Complex interactions between Operating Systems on heterogeneous SoCs for
 *   generic features.
 * - Lack of centralized knowledge of system state.
 * - Consistency in SoC feature entitlement in all OSes for the SoC for
 *   complex SoC features and system quirks.
 *
 * Device Management and Security control (DMSC) attempts to resolve
 * these issues by being a consistent component of Keystone 3 SoC
 * architecture performing the role of a centralized SoC power, security
 * and device management controller.
 *
 * In effect, this is a microcontroller and runs a safety and security
 * certified firmware that provides services to the rest of the
 * OSes/Software running on various other processors on the SoC.
 *
 * ### DMSC Power Management
 * DMSC controls the power management of the device, hence is responsible for
 * bringing the device out of reset, enforce clock and reset rules. DMSC power
 * management functions are critical to bring device to low power modes, for
 * example DeepSleep, and sense wake-up events to bring device back online to
 * active state.
 *
 * ### DMSC Security Management
 * The DMSC firmware Security Management manages SoC central security
 * resources. The security subsystem provides APIs to other software entities to
 * avail these features in a controlled and secure way.
 * The security management firmware is subdivided into modules listed below:
 * - Firewall management
 * - ISC management
 * - Boot authentication
 * - SA2UL context management (for encryption and authentication)
 * - Crypto APIs (to access common SA2UL functions such as PKA, RNG)
 * - Secure keys management
 * - Secure debug
 *
 * ### DMSC Resource Management
 * The DMSC firmware Resource Management (RM) (sub) system manages SoC shared
 * resources.  RM manages access and configuration of shared resources amongst
 * SoC processing entities.  RM provides a set of interfaces over which SoC
 * processing entities can allocate and free access to shared resources.
 *
 * The resource management firmware is subdivided into modules listed below:
 * - Core database
 * - IRQ management
 * - Ring accelerator management
 * - UDMA-P management
 * - PSI-L management
 * - Non-secure proxy management
 *
 * ### Communication with DMSC
 * DMSC is a "black box" with respect to the other processing
 * entities (ARM/DSP) on the SoC. Communication with DMSC occurs over
 * a messaging protocol called the Texas Instruments System Control
 * Interface (TI-SCI). TI-SCI is a predefined request-response protocol
 * that provides access to the various services provided by DMSC.
 *
 * The actual messaging hardware block varies depending on SoC, but
 * typical examples include "Proxy over message manager" and
 * "Secure Proxy over Ring Accellerator". These communication
 * mechanisms are standardized and secured by DMSC firmware prior to
 * operation.
 *
 * The request/response format is described overall as in Figure 2 . The
 * message type describes the service to be performed and is operated
 * on depending on few attributes including privileges allowed and
 * operational state of the SoC.
 *
 * |Type | Byte Index| Data Type| Header
 * |:----|:---------:|:--------:|:------
 * |TISCI Header| [0:1]| U16| Message_type
 * || [2]| uint8_t| Host
 * || [3]| uint8_t| Sequence_id
 * || [4:7]| U32| Flags
 * |Payload | Depends on type of message||Payload Fields|
 */
/* @} */

/**
 *  \ingroup DRV_SCICLIENT_MODULE
 *  \defgroup SCICLIENT_HAL System Controller Interface (SCI) Client HAL
 *
 * Major function of Sciclient is to pass on service requests from higher
 * level software to the DMSC/TIFS/DM firmware and forward the response from
 * firmware to the higher level software.
 *
 * The SCIClient library requires initialization of the a handle which is
 * used by the subsequent API calls. This handle is initialized by the
 * #Sciclient_init function. Once the application/higher level software is
 * being torn down or exiting the #Sciclient_deinit can be used to
 * de-initialize this handle.
 *
 * The SCIClient can operate in the following combinations:
 *
 * 1. Non-OS, Polling based message completion.
 * 2. Non-OS, Interrupt Based message completion.
 * 3. RTOS, Polling based message completion.
 * 4. RTOS, Interrupt based message completion.
 *
 * The SCIClient depends on the OSAL layer to differentiate between the
 * Non-OS and the RTOS implementation of Semaphores and Interrupts (HWIs).
 * The build parameter of the OSAL library would determine if the application
 * is bare metal or RTOS based. The polling versus interrupt based wait for
 * message completion is a run time configuration passed during the
 * #Sciclient_init initialization.
 *
 * All the APIs for interacting with the firmware are blocking with a
 * specified timeout . A common API #Sciclient_service is implemented for
 * all types of calls to the firmware which takes 2 arguments :
 * - #Sciclient_ReqPrm_t
 * - #Sciclient_RespPrm_t
 *
 * The API serves a particular request, based on the value of messageType
 * parameter in #Sciclient_ReqPrm_t, whose response is given to the higher
 * level API through #Sciclient_RespPrm_t. The #Sciclient_ReqPrm_t contains
 * the required inputs from the higher level software corresponding to the
 * message_type, timeout value and the core message as a byte stream.
 * A pointer #Sciclient_RespPrm_t has to be passed to the sciclient, which
 * shall be modified by sciclient.
 *
 * The Sciclient shall be responsible for abstracting all interaction with the
 * secure proxy and the ring accelerator.
 *
 *  @{
 */

/**
 *  \file sciclient.h
 *
 *  \brief This file contains prototypes for APIs contained
 *         as a part of SCICLIENT as well as the structures
 *         of their arguments.
 */

#ifndef SCICLIENT_H_
#define SCICLIENT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define the following macro to enable DM/TIFS logs */
#undef SYSFW_TRACE_ENABLE


/* Windows Visual Studio build doesn't  __attribute__ indentifier, so forcing it be to dummy for getting build working */
#ifdef _MSC_VER
  #ifndef __attribute__
    #define __attribute__()
  #endif
#endif

/* TISCI Include */
#define TISCI_BIT(n)  (1UL << (n))

/**
 * \brief Defines the sysfw DOMGRP type. This is meant to be used in code
 * or data structures that require distinction of domgrps.
 */
typedef uint8_t domgrp_t;

#ifndef SYSFW_DEVGRPS_H
/**
 * \brief Defines the sysfw DEVGRP type. This is meant to be used in code
 * or data structures that require distinction of devgrps.
 */
typedef uint8_t devgrp_t;

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

#endif

/** Aligned address at which the X509 header is placed. */
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
#define SCICLIENT_COMMON_X509_HEADER_ADDR (0x43c3f1e0)
#elif defined(SOC_AM62PX)
#define SCICLIENT_COMMON_X509_HEADER_ADDR (0x43c4f1e0)
#else
#define SCICLIENT_COMMON_X509_HEADER_ADDR (0x41cffb00)
#endif

#define SCISERVER_COMMON_X509_HEADER_ADDR \
    SCICLIENT_COMMON_X509_HEADER_ADDR

/**
 * Maximum number of devgrps that are supported by SYSFW.
 * Derived from the above definitions
 */
#define MAX_NUM_DEVGRPS (8U)

#if defined (SOC_AM62DX)
#define SOC_AM62AX
#endif

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
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
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
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#include <drivers/sciclient/include/am62ax/sciclient_fmwMsgParams.h>
#endif
#if defined (SOC_AM62PX)
#include <drivers/sciclient/include/tisci/am62px/tisci_resasg_types.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_sec_proxy.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_boardcfg_constraints.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_devices.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_clocks.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#include <drivers/sciclient/include/am62px/sciclient_fmwMsgParams.h>
//#include <drivers/sciclient/include/am62px/sciclient_firmware_V7.h>
#endif

#include <drivers/sciclient/include/tisci/security/tisci_sec_macros.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
#include <drivers/sciclient/include/tisci/security/tisci_ext_otp.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>
#include <drivers/sciclient/include/tisci/security/tisci_keystore.h>
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/tisci/security/tisci_sa2ul_rm.h>
#include <drivers/sciclient/include/tisci/security/tisci_sec_handover.h>
#include <drivers/sciclient/include/tisci/security/tisci_secure_jtag.h>
#include <drivers/sciclient/include/tisci/security/tisci_soc_uid.h>
#include <drivers/sciclient/include/tisci/security/tisci_keywriter.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
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
#include <drivers/sciclient/soc/sciclient_soc_priv.h>
#include <drivers/sciclient/include/sciclient_pm.h>
#include <drivers/sciclient/include/sciclient_rm.h>
#include <drivers/sciclient/include/sciclient_firewall.h>
#include <drivers/sciclient/include/sciclient_dkek.h>
#include <drivers/sciclient/include/sciclient_procboot.h>
#include <drivers/sciclient/include/sciclient_boardcfg.h>

#if defined (SOC_AM62DX)
#undef SOC_AM62AX
#endif

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor Sciclient_ServiceOperationMode
 *  \name Sciclient Service API Operation Mode
 *  @{
 *  Sciclient Service API Operation Mode. The different types of modes supported
 *  are:\n
 *  (1) Polled Mode : no interrupts are registered. The completion of a message
 *                    is via polling on the Proxy registers.\n
 *  (2) Interrupt Mode : Interrupt are registered and the response message would
 *                       be via a interrupt routine.
 *  Default mode in case #Sciclient_ConfigPrms_t is NULL is interrupt.
 */
#define SCICLIENT_SERVICE_OPERATION_MODE_POLLED           (0U)
#define SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT        (1U)
/* @} */

/**
 *  \anchor Sciclient_ServiceOperationTimeout
 *  \name Sciclient Service API Operation Timeout
 *  @{
 *  Sciclient Service API Timeout Values. The different types are:\n
 *  (1) Wait forever for an operation to complete. \n
 *  (2) Do not wait for the operation to complete. \n
 *  (3) Wait for a given time interface for the operation to complete.
 */
#define SCICLIENT_SERVICE_WAIT_FOREVER                    (0xFFFFFFFFU)
#define SCICLIENT_SERVICE_NO_WAIT                         (0x0U)
/* @} */

/** Fault tolerant Pass */
#define SCICLIENT_FT_PASS (0xA5A5U)
/** Fault tolerant Fail */
#define SCICLIENT_FT_FAIL (0x5A5AU)

/** \brief Total size of FS stub binary and certificate */
#define LPM_FS_STUB_SIZE                                    (0x8000U)
/** \brief Size of LPM meta data that is not used */
#define LPM_META_DATA_RSVD_SIZE                             (0xFF0U)
/** \brief Size of LPM context save buffer */
#define LPM_FS_CTXT_SIZE                                    (0x80000U)
/** \brief Size of LPM data that is not used */
#define LPM_DATA_RSVD_SIZE                                  (0x17000U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
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
    uint16_t       messageType;
    /**< [IN] Type of message. */
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
     *        (Refer \ref Sciclient_ServiceOperationTimeout) */
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

/**
 *  \brief Parameters for LPM Meta Data structure.
 */
typedef struct
{
    uint64_t dmEntryPoint;
    /**< Variable to save the address of DM entry point */
    uint64_t fsCtxtAddr;
    /**< Variable to save the address of FS context start */
    uint8_t rsvd[LPM_META_DATA_RSVD_SIZE];
    /**< Meta data reserved section */
} DM_LPMMetaData_t;

/**
 *  \brief Input parameters for LPM Data initialization function.
 */
typedef struct
{
    uint8_t fsStub[LPM_FS_STUB_SIZE];
    /**< Buffer to store FS stub section */
    DM_LPMMetaData_t metaData;
    /**< LPM Meta data buffer */
    uint8_t fsCtxt[LPM_FS_CTXT_SIZE];
    /**< Buffer to store FS context data */
    uint8_t rsvd[LPM_DATA_RSVD_SIZE];
    /**< LPM data reserved section */
} DM_LPMData_t;

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
 *  Requirement: DOX_REQ_TAG(PDK-2146)
 *
 *  \param pCfgPrms     [IN]  Pointer to #Sciclient_ConfigPrms_t
 *
 *  \return CSL_PASS on success, else failure
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
 *
 * Requirement: DOX_REQ_TAG(PDK-2142), DOX_REQ_TAG(PDK-2141),
 *              DOX_REQ_TAG(PDK-2140), DOX_REQ_TAG(PDK-2139)
 *
 *  \param pReqPrm        [IN]  Pointer to #Sciclient_ReqPrm_t
 *  \param pRespPrm       [OUT] Pointer to #Sciclient_RespPrm_t
 *
 *  \return CSL_PASS on success, else failure
 *
 */
int32_t Sciclient_service(const Sciclient_ReqPrm_t *pReqPrm,
                          Sciclient_RespPrm_t      *pRespPrm);

#ifdef QNX_OS
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
 *
 * Requirement: DOX_REQ_TAG(PDK-2142), DOX_REQ_TAG(PDK-2141),
 *              DOX_REQ_TAG(PDK-2140), DOX_REQ_TAG(PDK-2139)
 *
 *  \param pReqPrm        [IN]  Pointer to #Sciclient_ReqPrm_t
 *  \param pRespPrm       [OUT] Pointer to #Sciclient_RespPrm_t
 *
 *  \return CSL_PASS on success, else failure
 *
 */
int32_t Sciclient_service_rsmgr(const Sciclient_ReqPrm_t *pReqPrm,
                          Sciclient_RespPrm_t      *pRespPrm);
#endif

/**
 *  \brief  De-initialization of sciclient. This de-initialization is specific
 *          to the application. It only de-initializes the semaphores,
 *          interrupts etc. which are initialized in #Sciclient_init. It does
 *          not de-initialize the system firmware.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2146)
 *
 *  \return CSL_PASS on success, else failure
 *
 */

int32_t Sciclient_deinit(void);

/**<
 *  \brief   API to verify that firmware ABI matches the supported ABI.
 *
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_abiCheck(void);

/**
 * @brief API to configure the trace configuration.
 *
 * @return return CSL_PASS on success, else failure
 */
int32_t Sciclient_setDebugConfig(void);

/**
 *  \brief API to get the default board config info.
 *
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_getDefaultBoardCfgInfo(Sciclient_DefaultBoardCfgInfo_t *pBoardCfgInfo);

/*
 * Structure Init functions
 *
 * Requirement: DOX_REQ_TAG(PDK-2936)
 */
/**
 *  \brief Sciclient_ConfigPrms_t structure init function.
 *
 *  \param pCfgPrms     [IN] Pointer to #Sciclient_ConfigPrms_t structure.
 *
 */
int32_t Sciclient_configPrmsInit(Sciclient_ConfigPrms_t *pCfgPrms);

/**
 *  \brief Send the Response in Ack. Used only with Sciserver or
 *         Sciclient Direct
 *
 *  \param hdr     [IN] Pointer to #tisci_header structure.
 *
 */
void Sciclient_TisciMsgSetAckResp(struct tisci_header *hdr);

/**
 *  \brief Send the Response in NAK. Used only with Sciserver or
 *         Sciclient Direct
 *
 *  \param hdr     [IN] Pointer to #tisci_header structure.
 *
 */
void Sciclient_TisciMsgSetNakResp(struct tisci_header *hdr);

/**
 *  \brief Prepare the header for the board configuration. This API is typically
 *         only used by SBL where it will prepare the headers for the
 *         sciserver to come and then read the board configurations for PM and
 *         RM. This will set up the headers which Sciserver will look to read
 *         the board configuration which the SBL leaves behind after boot.
 *         The Sciserver app will then send the configs for board configuration
 *         based on this.
 *  \param pCommonHeader Pointer to the common header which corresponds to the
 *                       format for the component left behind.
 *  \param pBoardCfgHeader Pointer to the board configuration header which
 *                         corresponds to the table which defines the board
 *                         config params.
 *  \param pInPmPrms    Pointer to the PM parameters.
 *  \param pInRmPrms    Pointer to the RM parameters.
 *  \return ret CSL_PASS if the paramters are populated correctly in the header.
 *              Fail otherwise.
 */
int32_t Sciclient_boardCfgPrepHeader (
    uint8_t * pCommonHeader, uint8_t * pBoardCfgHeader,
    const Sciclient_BoardCfgPrms_t * pInPmPrms,
    const Sciclient_BoardCfgPrms_t * pInRmPrms);

/**
 *  \brief Parse the header left behind by the SBL in the SCISERVER. This is
 *         used in the SCISERVER App to read the left behind header and
 *         configuration paramter.
 *  \param pCommonHeader Pointer to the common header which corresponds to the
 *                       format for the component left behind.
 *  \param pInPmPrms    Pointer to the PM parameters popolated by the API.
 *  \param pInRmPrms    Pointer to the RM parameters popolated by the API.
 *  \return ret CSL_PASS if the paramters are populated correctly.
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

/**
 *  \brief   API to initialise Low power mode data required by DM
 *
 *  \param pLPMData Pointer to starting address of LPM data section
 *
 */
void Sciclient_initDeviceManagerLPMData(DM_LPMData_t *pLPMData);

/**
 *  \brief   API to get address where LPM context has to be saved
 *
 *  \param pCtxtAddr Pointer to context address parameter
 *
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_getLPMCtxtSaveAddr(uint64_t *pCtxtAddr);

/**
 *  \brief   API to copy FS stub from load address in DDR to DM local memory
 *
 *  \return SystemP_SUCCESS on success, else failure
 */
int32_t Sciclient_copyLPMFSStubToLocalMem(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_H_ */

/* @} */

/**
 * \ingroup DRV_SCICLIENT_MODULE
 * \defgroup TISCI Texas Instruments System Controller Interface
 *
 *  @{
 *
 * ##Power and Clock Management Features
 * Public APIs are provided to:
 *
 * - Enable and release a module, such as a UART or a core
 * - This configures both power and clock details for the module and keeps track of its usage.
 * - Configure the lowest/deepest low-power (sleep) mode allowed as well as EMIF details to enable self-refresh
 * - Query thermal sensors
 *
 * ##Resource Management Features
 * Public APIs are provided to:
 *
 * - Manage DMA/Navigator Resources
 * - UDMAP
 * - Ring Accelerator
 * - PSI-L
 * - Proxy
 * - Program interrupts (interrupt aggregators and routers) both at SoC and subsystem (DMA/Navigator) level
 *
 * ##Security Features
 * Public APIs are provided to directly configure these features following polices and root of trust:
 *
 * - ISC
 * - Present at originator/master interfaces to control credentials from master
 * - Firewall
 * - Additional layer of access control beyond MMU/MPU located at each destination/slave interface to control memory and register access
 * - SA2-UL Security Contexts
 * - Contains actual keys for crypto accelerator
 * - APIs are also provided to authenticate and/or decrypt blobs in memory.
 */
/* @} */

