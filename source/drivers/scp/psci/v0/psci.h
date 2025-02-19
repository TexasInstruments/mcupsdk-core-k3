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

/**
 *  \defgroup DRV_PSCI_MODULE APIs for PSCI
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the PSCI module.
 *
 *  @{
 */

/**
 *  \file v0/psci.h
 *
 *  \brief PSCI Driver API/interface file.
 */

#ifndef PSCI_H_
#define PSCI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* PSCI function interface */
#define PSCI_BASE_FUNC		        (uint32_t) 0x84000000U
#define PSCI_FUNC(n)				(PSCI_BASE_FUNC + (n))
#define PSCI_FUNC_OFF_64BIT		    (uint32_t) 0x40000000U
#define PSCI_BASE_FUNC_64BIT			\
					(PSCI_BASE_FUNC + PSCI_FUNC_OFF_64BIT)
#define PSCI_FUNC_64BIT(n)			(PSCI_BASE_FUNC_64BIT + (n))

#define PSCI_FUNC_PSCI_VERSION		PSCI_FUNC(0)
#define PSCI_FUNC_CPU_OFF			PSCI_FUNC(2)
#define PSCI_FUNC_SYSTEM_RESET		PSCI_FUNC(9)
#define PSCI_FUNC_CPU_ON_64BIT		PSCI_FUNC_64BIT(3)
#define PSCI_FUNC_PSCI_FEATURES		PSCI_FUNC(10)

/* Decode PSCI versions into Major and Minor Versions */
#define PSCI_MAJOR_VERSION_SHIFT		(16U)
#define PSCI_MINOR_VERSION_MASK			\
		((1U << PSCI_MAJOR_VERSION_SHIFT) - 1)
#define PSCI_MAJOR_VERSION_MASK			~PSCI_MINOR_VERSION_MASK
#define PSCI_MAJOR_VERSION(ver)			\
		(((ver) & PSCI_MAJOR_VERSION_MASK) >> PSCI_MAJOR_VERSION_SHIFT)
#define PSCI_MINOR_VERSION(ver)			\
		((ver) & PSCI_MINOR_VERSION_MASK)

/* PSCI return values */
#define PSCI_SUCCESS			    (0)
#define PSCI_NOT_SUPPORTED			(-1)
#define PSCI_INVALID_PARAMS			(-2)
#define PSCI_DENIED				    (-3)
#define PSCI_ALREADY_ON			    (-4)
#define PSCI_ON_PENDING			    (-5)
#define PSCI_INTERNAL_FAILURE		(-6)
#define PSCI_NOT_PRESENT			(-7)
#define PSCI_DISABLED			    (-8)
#define PSCI_INVALID_ADDRESS		(-9)

/* ========================================================================== */
/*                          Structure Declarations                            */
/* ========================================================================== */

/**
 *  \brief A handle that is returned from a PSCI_open() call.
 */
typedef struct PSCI_Config_s     *PSCI_Handle;

/**
 *  \brief  PSCI driver object
 */
typedef struct  PSCI_Object_s
{
/** Grants exclusive access to this PSCI Instance */
    SemaphoreP_Object           mutex;
/** Flag to indicate whether the instance is opened already */
    bool                        isOpen;

}  PSCI_Object;

/**
 *  \brief  PSCI Global Configuration
 *
 *  The  PSCI_Config structure contains a set of pointers used to characterise
 *  the  PSCI driver implementation.
 *
 *  This structure needs to be defined before calling  PSCI_init() and it must
 *  not be changed thereafter.
 */
typedef struct  PSCI_Config_s
{
/** Pointer to a driver specific data object */
    PSCI_Object                      *object;

}  PSCI_Config;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Initialize the PSCI module.
 */
void PSCI_init(void);

/**
 * \brief Deinitialize the PSCI module.
 */
void PSCI_deinit(void);

/**
 * \brief Open the PSCI at index idx.
 *
 * \param idx [IN] Index of PSCI to open in global config
 *
 * \return PSCI_Handle
 */
PSCI_Handle PSCI_open(uint32_t idx);

/**
 * \brief Function to close the PSCI instance specified by the handle
 *
 * \pre #PSCI_open() has to be called first
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 *
 * \sa #PSCI_open()
 */
void PSCI_close(PSCI_Handle handle);

/**
 *  \brief  This function returns the handle of an open PSCI
 *          Instance from the instance index
 *
 *  \param  driverInstanceIndex Index of config to use in the *PSCI_Config* array
 *
 *  \return An #PSCI_Handle if it has been opened already or NULL otherwise
 */
PSCI_Handle PSCI_getHandle(uint32_t driverInstanceIndex);

/**
 *  \brief  This function returns the initialised instance index.
 *
 *  \return instanceIndex First instance which is open for PSCI driver
 */
uint32_t PSCI_getInitDriverIndex(void);

/**
 * \brief Get the PSCI version
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 * \param psciVer [OUT] Pointer to PSCI version.
 *
 * \return PSCI_StatusCode
 */
int32_t PSCI_getPSCIVersion(PSCI_Handle handle, uint32_t *psciVer);

/**
 * \brief Power off the calling CPU
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 *
 * \return SystemP_FAILURE if failure, else should never return.
 */
int32_t PSCI_cpuOff(PSCI_Handle handle);

/**
 * \brief Power on the CPU required.
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 * \param cpuId [IN] CPU ID of the CPU required to be powered on.
 * \param entryPoint [IN] Entry Point of the CPU in the non-secure world.
 *
 * \return PSCI_StatusCode
 */
int32_t PSCI_cpuOn(PSCI_Handle handle, uint32_t cpuId, uint32_t entryPoint);

/**
 * \brief Cold reset of the entire system
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 *
 * \return SystemP_FAILURE if failure, else should never return.
 */
int32_t PSCI_systemReset(PSCI_Handle handle);

/**
 * \brief Get the features of a PSCI function.
 *
 * \param handle [IN] #PSCI_Handle returned from PSCI_open()
 * \param functionId [IN] PSCI Function ID whose features are needed.
 * \param feature [OUT] Pointer to the PSCI feature result.
 *
 * \return PSCI_StatusCode
 */
int32_t PSCI_getFeatures(PSCI_Handle handle, uint32_t functionId, uint32_t *feature);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef PSCI_H_ */

/** @} */
