/*
 *  Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \defgroup SECURITY_DTHE_MODULE APIs for DTHE
 *  \ingroup  SECURITY_MODULE
 *
 *  This module contains APIs to program and use the DTHE.
 *
 *  @{
 */

/**
 *  \file dthe.h
 *
 *  \brief This file contains the prototype of DTHE driver APIs
 */

#ifndef DTHE_H_
#define DTHE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <security/crypto/dthe/hw_include/cslr_dthe.h>
#include <drivers/hw_include/am263x/cslr_soc_baseaddress.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Handle to the DTHE driver */
typedef void *DTHE_Handle;

/** \brief DTHE attributes */
typedef struct
{
    /*
     * SOC configuration
     */
	uint32_t				caBaseAddr;
	/**< Crypto Accelerator Base Adders*/
    uint32_t                aesBaseAddr;
    /**< Aes Base address */
    uint32_t                shaBaseAddr;
    /**< sha Base address */
	uint32_t                isOpen;
    /**< Flag to indicate whether the instance is opened already */
} DTHE_Attrs;

/** \brief DTHE driver context */
typedef struct
{
    DTHE_Attrs             *attrs;
    /**< Driver params passed during open */
} DTHE_Config;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Externally defined driver configuration array */
extern DTHE_Config          gDtheConfig[];
/** \brief Externally defined driver configuration Num */
extern uint32_t             gDtheConfigNum;

/* ========================================================================== */
/*                              Function Definitions                          */
/* ========================================================================== */
/**
 *  \brief          This function initializes the DTHE.
 */
void DTHE_init(void);

/**
 *  \brief          This function de-initializes the DTHE.
 */
void DTHE_deinit(void);

/**
 *  \brief          Function to open DTHE instance, enable DTHE engine.
 *
 *  \param  index   Index of config to use in the *DTHE_Config* array.
 *
 *  \return         A #DTHE_Handle on success or a NULL on an error.
 */
DTHE_Handle DTHE_open(uint32_t index);

/**
 *  \brief          Function to close a DTHE module specified by the DTHE handle.
 *
 *  \param  handle  #DTHE_Handle returned from #DTHE_open()
 */
int32_t DTHE_close(DTHE_Handle handle);

/**
 *  \brief          Function to enable secure request.
 *
 *  \param  handle  #DTHE_Handle returned from #DTHE_open()
 */
int32_t DTHE_enableSecureRequest(DTHE_Handle handle);

/**
 *  \brief          Function to disable secure request.
 *
 *  \param  handle  #DTHE_Handle returned from #DTHE_open()
 */
int32_t DTHE_disableSecureRequest(DTHE_Handle handle);

/**
 *  \brief          Function to check secure request enabled or not.
 *
 *  \param  handle  #DTHE_Handle returned from #DTHE_open()
 */
uint8_t DTHE_isSecureRequestEnabled(DTHE_Handle handle);

#endif /* DTHE_H_ */
/** @} */