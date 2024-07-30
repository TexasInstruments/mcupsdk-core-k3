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
 *  \defgroup BOARD_PMIC_MODULE APIs for PMIC
 *  \ingroup BOARD_MODULE
 *
 *  This module contains APIs to program and use the PMIC module
 *  on the board.
 *
 *  See \ref BOARD_PMIC_PAGE for more details.
 *
 *  @{
 */

#ifndef PMIC_BOARD_H_
#define PMIC_BOARD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <board/pmic/pmic_lld/pmic.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Handle to the PMIC driver returned by #PMIC_open() */
typedef void *PMIC_Handle;

/** \brief Forward declaration of \ref PMIC_Config */
typedef struct PMIC_Config_s PMIC_Config;

/** \brief Forward declaration of \ref PMIC_Params */
typedef struct PMIC_Params_s PMIC_Params;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief PMIC driver configuration, these are filled by SysCfg based on
 *  the device that is selected
 */
typedef struct PMIC_Config_s {
    Pmic_CoreCfg_t *pmicConfigData;
    /**< Configuration data used to initialize PMIC */
    Pmic_CoreHandle_t *pmicCoreHandle;
    /**< PMIC LLD driver handle, used to maintain driver implementation state */
    uint8_t wdogMode;
    /**< Watchdog mode - Trigger/Q&A */
    uint8_t trigWdogPin;
    /**< Trigger watchdog input signal GPIO pin number */
    uint8_t trigWdogPinFunc;
    /**< Trigger watchdog input signal GPIO pin function */
    uint8_t qaWdogpin1;
    /**< Q&A watchdog GPIO pin-1 number */
    uint8_t qaWdogpin2;
    /**< Q&A watchdog GPIO pin-2 number */
    uint8_t qaWdogpin1Func;
    /**< Q&A watchdog GPIO pin-1 fucntion */
    uint8_t qaWdogpin2Func;
    /**< Q&A watchdog GPIO pin-2 fucntion */
} PMIC_Config;

/**
 *  \brief Parameters passed during PMIC_open()
 */

typedef struct PMIC_Params_s {
    uint32_t        mainDrvinstance;
    /**< Underlying I2C/MCSPI peripheral driver instance that is
     *  used by the PMIC driver */
    uint32_t        qaWdogDrvinstance;
    /**< Underlying I2C peripheral driver instance that is
     * used by the PMIC driver. This is used only when watchdog
     * Q&A mode is enabled via separate I2C.*/
} PMIC_Params;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This function initializes the PMIC module
 */
void PMIC_init(void);

/**
 * \brief This function de-initializes the PMIC module
 */
void PMIC_deinit(void);

/**
 *  \brief Open PMIC driver
 *
 *  Make sure the SOC peripheral driver is open'ed before calling this API.
 *  Drivers_open function generated by SysCfg opens the underlying SOC
 *  peripheral driver, e.g I2C
 *
 *  Global variables `PMIC_Config gPmicConfig[]` and
 *  `uint32_t gPmicConfigNum` is instantiated by SysCfg
 *  to describe the PMIC configuration based on user selection in SysCfg.
 *
 *  \param instanceId   [IN] Index within `PMIC_Config gPmicConfig[]`
 *                      denoting the PMIC driver to open
 *  \param params       [IN] Open parameters
 *
 *  \return Handle to PMIC driver which should be used in subsequent API call
 *          Else returns NULL in case of failure
 */
PMIC_Handle PMIC_open(uint32_t instanceId, const PMIC_Params *params);

/**
 * \brief Get handle to PMIC driver
 *
 * \param instanceId    [in] Index within `PMIC_Config gPmicConfig[]`
 *
 * \return Handle to pmic driver
 * \return NULL in case of failure
 */
PMIC_Handle PMIC_getHandle(uint32_t instanceId);

/**
 *  \brief Close PMIC driver
 *
 *  \param handle    [IN] PMIC driver handle from \ref PMIC_open
 */
void PMIC_close(PMIC_Handle handle);

/**
 * @brief  Initiates the start of a critical section for PMIC operations.
 * This function attempts to acquire a semaphore, which is typically
 * used to ensure exclusive access to resources during PMIC operations.
 *
 */
void PMIC_critSecStartFn(void);

/**
 * @brief  Concludes a critical section for PMIC operations.
 * This function releases the semaphore, signifying
 * the end of a critical section initiated by a
 * corresponding "start" function.
 *
 */
void PMIC_critSecStopFn(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PMIC_BOARD_H_ */

/** @} */
