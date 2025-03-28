/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

#ifndef SCMI_PROTOCOL_H
#define SCMI_PROTOCOL_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCMI_PROTOCOL_VENDOR_BASE	                    0x80

#define SCMI_MAX_STR_SIZE		                        64U
#define SCMI_MAX_NUM_RATES		                        16U

#define SCMI_BASE_PROTOCOL_VERSION                      0x20000U
#define SCMI_BASE_NAME_LENGTH_MAX                       16U
#define SCMI_BASE_MAX_NUM_PROTOCOLS                     10U

#define GENMASK(h, l)               (((~0UL) << (l)) & (~0UL >> (32 - 1 - (h))))

#define SCMI_PROTOCOL_ATTRS_NUM_AGENTS(attributes) \
				(((attributes) & GENMASK(15, 8)) >> 8)
#define SCMI_PROTOCOL_ATTRS_NUM_PROTOCOLS(attributes) \
				((attributes) & GENMASK(7, 0))


#define SCMI_PWD_POWER_STATE_ON                         (uint32_t)(0U << 30U)
#define SCMI_PWD_POWER_STATE_OFF                        (uint32_t)(1U << 30U)

#define SCMI_PWD_PROTOCOL_VERSION                       0x30000

#define SCMI_PWD_PSTATE_TYPE_LOST                       (1U << 30)
#define SCMI_PWD_PSTATE_ID                              GENMASK(27, 0)
#define SCMI_PWD_PROTO_ATTRS_NUM_PWD(attributes)        ((attributes) & \
                                                        GENMASK(15, 0))
#define SCMI_PWD_SHORT_NAME_SIZE	                    16
#define SCMI_PWD_NAME_LENGTH_MAX                        64
#define SCMI_PWD_SET_FLAGS_ASYNC                        (1U << 0)
#define SCMI_PWD_ATTR_PSTATE_CHANGE_NOTIFY	            (1U << 31)
#define SCMI_PWD_ATTR_PSTATE_ASYNC		                (1U << 30)
#define SCMI_PWD_ATTR_PSTATE_SYNC		                (1U << 29)
#define SCMI_PWD_ATTR_PSTATE_CHANGE_RQ_NOTIFY	        (1U << 28)
#define SCMI_PWD_ATTR_EXTENDED_NAME		                (1U << 27)
#define SCMI_PWD_EXTENDED_NAME_MAX                      64U

#define SCMI_CLK_PROTO_ATTR_COUNT_MASK	                GENMASK(15, 0)

#define SCMI_CLK_ATTR_RATE_CHANGED_NOTIFY               (1U << 31)
#define SCMI_CLK_ATTR_RATE_CHANGE_REQUESTED_NOTIFY      (1U << 30)
#define SCMI_CLK_ATTR_EXTENDED_NAMES		            (1U << 29)
#define SCMI_CLK_ATTR_PARENT_CLOCK		                (1U << 28)
#define SCMI_CLK_ATTR_EXTENDED_CONFIG		            (1U << 28)
#define SCMI_CLK_ATTR_GET_PERMISSIONS		            (1U << 1)

#define SCMI_CLK_RATE_ASYNC_NOTIFY	                    (1U << 0)
#define SCMI_CLK_RATE_ASYNC_NORESP	                    ((1U << 0U)) | (1U << 1U))
#define SCMI_CLK_RATE_ROUND_DOWN	                    0
#define SCMI_CLK_RATE_ROUND_UP		                    (1U << 2)
#define SCMI_CLK_RATE_ROUND_CLOSEST	                    (1U << 3)

#define SCMI_CLK_SHORT_NAME_SIZE	                    16
#define SCMI_CLK_NAME_LENGTH_MAX                        64

#define SCMI_CLK_CONFIG_SET_ENABLE                      (1U << 0)
#define SCMI_CLK_CONFIG_SET_DISABLE                     (0U)

#define SCMI_CLK_POSSIBLE_PARENTS_MASK                  255U
#define SCMI_CLK_POSSIBLE_PARENTS_NUM_PARENTS_RECV(x)   ((x) & (uint32_t)0xFF)
#define SCMI_CLK_POSSIBLE_PARENTS_NUM_PARENTS_REM(x)    ((x) >> 24)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef enum
{
	SCMI_PROTOCOL_VERSION = 0x0,
	SCMI_PROTOCOL_ATTRIBUTES = 0x1,
	SCMI_PROTOCOL_MESSAGE_ATTRIBUTES = 0x2,
	SCMI_NEGOTIATE_PROTOCOL_VERSION = 0x10,
} SCMI_CommonCommand;

typedef enum
{
	SCMI_PROTOCOL_BASE = 0x10,
	SCMI_PROTOCOL_POWER = 0x11,
	SCMI_PROTOCOL_SYSTEM = 0x12,
	SCMI_PROTOCOL_PERF = 0x13,
	SCMI_PROTOCOL_CLOCK = 0x14,
	SCMI_PROTOCOL_SENSOR = 0x15,
	SCMI_PROTOCOL_RESET = 0x16,
	SCMI_PROTOCOL_VOLTAGE = 0x17,
	SCMI_PROTOCOL_POWERCAP = 0x18,
	SCMI_PROTOCOL_PINCTRL = 0x19,
} SCMI_StandardProtocol;

typedef enum
{
	SCMI_SUCCESS =  0,
	SCMI_NOT_SUPPORTED = -1,
	SCMI_INVALID_PARAMETERS = -2,
	SCMI_DENIED = -3,
	SCMI_NOT_FOUND = -4,
	SCMI_OUT_OF_RANGE = -5,
	SCMI_BUSY = -6,
	SCMI_COMMS_ERROR = -7,
	SCMI_GENERIC_ERROR = -8,
	SCMI_HARDWARE_ERROR = -9,
	SCMI_PROTOCOL_ERROR = -10,
} SCMI_StatusCode;

/*
 * SCMI Base Protocol
 */
typedef enum
{
	SCMI_BASE_DISCOVER_VENDOR = 0x3,
	SCMI_BASE_DISCOVER_SUB_VENDOR = 0x4,
	SCMI_BASE_DISCOVER_IMPL_VERSION = 0x5,
	SCMI_BASE_DISCOVER_LIST_PROTOCOLS = 0x6,
	SCMI_BASE_DISCOVER_AGENT = 0x7,
	SCMI_BASE_NOTIFY_ERRORS = 0x8,
	SCMI_BASE_SET_DEVICE_PERMISSIONS = 0x9,
	SCMI_BASE_SET_PROTOCOL_PERMISSIONS = 0xa,
	SCMI_BASE_RESET_AGENT_CONFIGURATION = 0xb,
} SCMI_BaseMessageCommand ;

/**
 * \brief SCMI_ProtocolVersionData - Response for SCMI_PROTOCOL_VERSION
 *		  command
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t version;
    /**< Protocol version*/
} SCMI_ProtocolVersionData;

/**
 * \brief Response for SCMI_PROTOCOL_ATTRIBUTES
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Protocol attributes or implementation details */
} SCMI_ProtocolAttributesData;

/**
 * \brief Response for SCMI_PROTOCOL_MESSAGE_ATTRIBUTES command
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Message-specific attributes */
} SCMI_ProtocolMessageAttributesData;

/**
 * \brief Response for SCMI_BASE_DISCOVER_VENDOR or
 *		  SCMI_BASE_DISCOVER_SUB_VENDOR command
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint8_t vendorIdentifier[SCMI_BASE_NAME_LENGTH_MAX];
    /**< Name of vendor or sub-vendor in string */
} SCMI_BaseDiscoverVendorOut;

/**
 * \brief Response for SCMI_BASE_DISCOVER_IMPL_VERSION command
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t implVersion;
    /**< Vendor-specific implementation version */
} SCMI_BaseDiscoverImplementationVersionData;

/**
 * \brief Response for SCMI_BASE_DISCOVER_LIST_PROTOCOLS command
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t numProtocols;
    /**< Number of SCMI protocols */
	uint32_t protocols[SCMI_BASE_MAX_NUM_PROTOCOLS];
    /**< Array of packed SCMI protocol ID's */
} SCMI_BaseDiscoverListProtocolsData;

/*
 * SCMI Power Domain Management Protocol
 */
typedef enum
{
	SCMI_PWD_ATTRIBUTES = 0x3,
	SCMI_PWD_STATE_SET = 0x4,
	SCMI_PWD_STATE_GET = 0x5,
	SCMI_PWD_STATE_NOTIFY = 0x6,
	SCMI_PWD_STATE_CHANGE_REQUESTED_NOTIFY = 0x7,
	SCMI_PWD_NAME_GET = 0x8,
} SCMI_PowerDomainMessageId;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Protocol attributes */
	uint32_t statsAddrLow;
    /**< Lower 32 bits of address of statistics memory region */
	uint32_t statsAddrHigh;
    /**< Higher 32 bits of address of statistics memory region */
	uint32_t statsLen;
    /**< Length of statistics memory region */
} SCMI_PdProtocolAttrs;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Message specific attributes */
} SCMI_PdProtocolMessageAttrs;

/**
 * struct SCMI_PowerDomainAttrsOutData
 * @status:	SCMI command status
 * @attributes:	Power domain attributes
 * @name:	Name of power domain
 */
typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Power domain attributes */
	uint8_t name[SCMI_PWD_NAME_LENGTH_MAX];
    /**< Name of power domain */
} SCMI_PowerDomainAttrsOutData;

typedef struct
{
	uint32_t flags;
    /**< Flags for power domain */
	uint32_t domainId;
    /**< Power domain identifier */
	uint32_t pstate;
    /**< Power state of the domain */
} SCMI_PowerDomainStateSetInput;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t pstate;
    /**< Power state of the domain */
} SCMI_PowerDomainStateGetOut;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t flags;
    /**< Parameter flags */
	uint8_t extendedName[SCMI_PWD_EXTENDED_NAME_MAX];
    /**< Extended name of power domain */
} SCMI_PowerDomainNameGetOut;

/*
 * SCMI Clock Protocol
 */

typedef enum
{
	SCMI_CLOCK_ATTRIBUTES = 0x3,
	SCMI_CLOCK_RATE_SET = 0x5,
	SCMI_CLOCK_RATE_GET = 0x6,
	SCMI_CLOCK_CONFIG_SET = 0x7,
	SCMI_CLOCK_NAME_GET = 0x8,
	SCMI_CLOCK_CONFIG_GET = 0xB,
	SCMI_CLOCK_POSSIBLE_PARENTS_GET = 0xC,
	SCMI_CLOCK_PARENT_SET = 0xD,
	SCMI_CLOCK_PARENT_GET = 0xE,
} SCMI_ClockMessageId;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Attributes of the clock protocol, mainly number of clocks exposed */
} SCMI_ClockProtocolAttrsOut;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Clock attributes */
	char clockName[SCMI_CLK_NAME_LENGTH_MAX];
    /**< Clock name */
} SCMI_ClockAttributeOut;

typedef struct
{
	uint32_t clockId;
    /**< SCMI Clock ID */
	uint32_t attributes;
    /**< Attributes of the targets clock state */
} SCMI_ClockStateIn;

typedef struct
{
	uint32_t clockId;
    /**< SCMI Clock ID */
	uint32_t flags;
    /**< Paramter flags for the clock */
} SCMI_ClockStateGetIn;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t attributes;
    /**< Attributes for clock */
	uint32_t config;
    /**< Clock state */
} SCMI_ClockStateGetOut;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t flags;
    /**< Paramter flags for the clock */
	char clockName[SCMI_CLK_NAME_LENGTH_MAX];
    /**< Extended name for clock */
} SCMI_ClockNameGetOut;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t clockRateLSB;
    /**< 32bit LSB of the clock rate in Hertz */
	uint32_t clockRateMSB;
    /*< 32bit MSB of the clock rate in Hertz*/
} SCMI_ClockRateGetOut;

typedef struct
{
	uint32_t flags;
    /**< Flags for the clock rate set request */
	uint32_t clockId;
    /**< SCMI Clock ID */
	uint32_t clockRateLSB;
    /*< 32bit LSB of the clock rate in Hertz*/
	uint32_t clockRateMSB;
    /*< 32bit MSB of the clock rate in Hertz*/
} SCMI_ClockRateSetIn;

typedef struct
{
	uint32_t clockId;
    /**< SCMI Clock ID */
	uint32_t parentId;
    /**< Parent identifier for the clock */
} SCMI_ClockParentSetIn;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t parentId;
    /**< Parent identifier for the clock */
} SCMI_ClockParentGetOut;

typedef struct
{
	int32_t status;
    /**< SCMI command status */
	uint32_t numParentsFlags;
    /**< Number of possible parents */
	uint32_t possibleParents[SCMI_CLK_POSSIBLE_PARENTS_MASK];
    /**< Array of possible parents */
} SCMI_ClockGetPossibleParentsOut;

typedef struct
{
	uint32_t clockId;
    /**< SCMI Clock ID */
	uint32_t skipParents;
    /**< Skip number of parents */
} SCMI_ClockGetPossibleParentsIn;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#endif

