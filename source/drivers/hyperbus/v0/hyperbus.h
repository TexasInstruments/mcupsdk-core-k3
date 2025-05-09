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
 *  \defgroup DRV_HYPERBUS_MODULE APIs for HYPERBUS
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the HYPERBUS module. The APIs
 *  can be used by other drivers to get access to HYPERBUS and also by
 *  application to initiate data transfer operation.
 *
 *  @{
 */

/**
 *  \file v0/hyperbus.h
 *
 *  \brief HYPERBUS Driver API/interface file.
 */

#ifndef HYPERBUS_H_
#define HYPERBUS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SemaphoreP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief A handle that is returned from a #HYPERBUS_open() call */
typedef void *HYPERBUS_Handle;

/**
 * \brief Enum for device type
 */
typedef enum HYPERBUS_Devicetype_e
{
    HYPERBUS_DEVICETYPE_HYPERRAM,
    HYPERBUS_DEVICETYPE_NONE,
    HYPERBUS_DEVICETYPE_HYPERFLASH
} HYPERBUS_Devicetype;

/**
 * \brief Memory offset for HYPERBUS controller
 */
#define HYPERBUS_MEM_OFFSET          0U

/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x1 = configurable CS# low time, 0x0 otherwise
 */
#define HYPERBUS_MCR_CONFIGURABLE_CS_LOW_TIME    0x1U
#define HYPERBUS_MCR_NO_CONFIGURABLE_CS_LOW_TIME 0x0U

/**
 * \brief Maximum Length defines
 * \details
 * This bit indicates maximum read/write transaction length to memory.
 * This bit is ignored when MAXEN bit is 0.
 * 000000000: 2 Byte [1 HyperBus CK]
 * 000000001: 4 Byte [2 HyperBus CK]
 * 000000010: 6 Byte [3 HyperBus CK]
 * 111111111: 1024 Byte [512 HyperBus CK]
 */
#define HYPERBUS_MCR_MAXLEN_2_BYTE              0x0U
#define HYPERBUS_MCR_MAXLEN_4_BYTE              0x1U
#define HYPERBUS_MCR_MAXLEN_6_BYTE              0x2U
#define HYPERBUS_MCR_MAXLEN_1024_BYTE           0x1FFU
/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x1 = merge WRAP and INCR, 0x0 otherwise
 */
#define HYPERBUS_MCR_MERGE_WRAP_INCR             0x1U
#define HYPERBUS_MCR_NO_MERGE_WRAP_INCR          0x0U

/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x1 = asymmetry cache support, 0x0 otherwise
 */
#define HYPERBUS_MCR_ASYMM_CACHE_SUPPORT         0x1U
#define HYPERBUS_MCR_NO_ASYMM_CACHE_SUPPORT      0x0U

/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x0 = memory space, 0x1 = CR space
 */
#define HYPERBUS_MCR_MEM_SPACE                   0x0U
#define HYPERBUS_MCR_CR_SPACE                    0x1U

/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x0 = HyperFlash, 0x1 = HyperRAM
 */
#define HYPERBUS_MCR_HYPERFLASH                  0x0U
#define HYPERBUS_MCR_HYPERRAM                    0x1U

/**
 * \brief Memory Configuration Register defines
 * \details
 * 0x0 = wrap size none, 0x1 = 64B, 0x2 = 16B, 0x3 = 32B
 */
#define HYPERBUS_MCR_WRAPSIZE_NONE               0x0U
#define HYPERBUS_MCR_WRAPSIZE_64B                0x1U
#define HYPERBUS_MCR_WRAPSIZE_16B                0x2U
#define HYPERBUS_MCR_WRAPSIZE_32B                0x3U

/**
*  \anchor HYPERBUS_ChipSelect
*  \name Chip Selects
*
*  Chip selects
*
*  @{
*/
#define HYPERBUS_CS0  (0U)
#define HYPERBUS_CS1  (1U)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 * \brief Memory Configuration Structure
 *
 * This structure holds the memory configuration settings for the HYPERBUS.
 */
typedef struct {
    uint16_t max_en;
    /**< Configurable CS# low time: 0x1 for enabled, 0x0 otherwise */
    uint16_t max_len;
    /**< Maximum length: 0x0 to 0x1FF representing 1 to 512 HBMC Clks */
    uint16_t true_cont_merge;
    /**< Merge WRAP and INCR: 0x1 for enabled, 0x0 otherwise */
    uint16_t asymm_cache;
    /**< Asymmetry cache support: 0x1 for enabled, 0x0 otherwise */
    uint16_t cfg_reg_target;
    /**< Configuration register target: 0x0 for memory space, 0x1 for CR space */
    uint16_t dev_type;
    /**< Device type: 0x0 for HyperFlash, 0x1 for HyperRAM */
    uint16_t wrap_size;
    /**< Wrap size: 0x0 reserved, 0x1 for 64B, 0x2 for 16B, 0x3 for 32B */
} HYPERBUS_MemCfg;

/**
 * \brief FSS Data Interface Structure
 *
 * This structure contains the global and local addresses of the data interface
 */
typedef struct fss_dataif_l{
    uint64_t  addr_glb;
    /*!< The global address of the interface */
    uintptr_t addr_loc;
    /*!< The local address of the interface */
}HYPERBUS_fssDataIf;

/**
 * \brief FSS Handle Structure
 *
 * This structure contains the base addresses of the configuration and data interface
 */
typedef struct fss_handle_l{
    uintptr_t cfg_base;
    /*!< configuration region base address */
    uintptr_t fsas_base;
    /*!< FSAS region base address */
    uintptr_t otfa_base;
    /*!< OTFA region base address */
    HYPERBUS_fssDataIf s0_reg0_base;
    /*!< slave0 rsel=0 base address struct */
    HYPERBUS_fssDataIf s0_reg1_base;
    /*!< slave0 rsel=1 base address struct */
    HYPERBUS_fssDataIf s0_reg3_base;
    /*!< slave0 rsel=3 base address struct */
} HYPERBUS_fssHandle;

/**
 * \brief Register structure for the Memory Timing Register
 */
typedef struct
{
    /**< Initial latency for read/write access, only applicable for HyperRAM */
    uint32_t latency;
    /**< CS# hold time for write to CS# deassertion 
      *  Range 0 to 15
      *  0  means 1  Cycle
      *  15 means 16 Cycles */
    uint32_t writeCSHold;
    /**< CS# hold time for read to CS# deassertion 
      *  Range 0 to 15
      *  0  means 1  Cycle
      *  15 means 16 Cycles */
    uint32_t readCSHold;
    /**< CS# setup time for write from CS# assertion 
      *  Range 0 to 15
      *  0  means 1  Cycle
      *  15 means 16 Cycles */
    uint32_t writeCSSetup;
    /**< CS# setup time for read from CS# assertion
      *  Range 0 to 15
      *  0  means 1  Cycle
      *  15 means 16 Cycles */
    uint32_t readCSSetup;
    /**< CS# high time for write between operations 
      *  Range 0 to 15
      *  0  means 1.5  Cycle
      *  15 means 16.5 Cycles*/
    uint32_t writeCSHigh;
    /**< CS# high time for read between operations 
      *  Range 0 to 15
      *  0  means 1.5  Cycle
      *  15 means 16.5 Cycles*/
    uint32_t readCSHigh;
}HYPERBUS_MemTiming;

/** \brief HYPERBUS instance attributes - used during init time */
typedef struct
{
    uint32_t                deviceType;
    /*
     * SOC configuration
     */
    uint32_t                baseAddr;
    /**< Peripheral base address */
    uint32_t                ssBaseAddr;
    /**< Peripheral sys base address */
    uint32_t                dataBaseAddr;
    /**< Base address of the HYPERBUS HyperRam */
    uint32_t                fssCfgBase;
    uint32_t                fssFsasBase;
    uint32_t                fssOtfaBase;
    uint64_t                fssS0Reg0Base;
    uint64_t                fssS0Reg1Base;
    uint64_t                fssS0Reg3Base;
    uint32_t                inputClkFreq;
    /**< Module input clock frequency */

    /*
     * Driver configuration
     */
    uint32_t                intrNum;
    /**< Peripheral interrupt number */
    uint32_t                intrEnable;
    /**< Enable interrupt mode */
    uint8_t                 intrPriority;
    /**< Interrupt priority */
    uint32_t                ECCEnable;
    /**< Enable ECC */
    uint32_t                OTFAEnable;
    /**< Enable OTFA */
    uint32_t                chipSelect;
    /**< HyperBus Chip select number */

    uint32_t latency;
    /**< Initial latency for read/write access, only applicable for HyperRAM */
    uint32_t writeCSHold;
    /**< CS# hold time for write to CS# deassertion 
      * Range 0 to 15
      * 0  means 1  Cycle
      * 15 means 16 Cycles */
    uint32_t readCSHold; 
    /**< CS# hold time for read to CS# deassertion 
      * Range 0 to 15
      * 0  means 1  Cycle
      * 15 means 16 Cycles */
    uint32_t writeCSSetup;
    /**< CS# setup time for write from CS# assertion 
      * Range 0 to 15
      * 0  means 1  Cycle
      * 15 means 16 Cycles */
    uint32_t readCSSetup;
    /**< CS# setup time for read from CS# assertion
      * Range 0 to 15
      * 0  means 1  Cycle
      * 15 means 16 Cycles */
    uint32_t writeCSHigh;
    /**< CS# high time for write between operations 
      * Range 0 to 15
      * 0  means 1.5  Cycle
      * 15 means 16.5 Cycles */
    uint32_t readCSHigh;
    /**< CS# high time for read between operations 
      * Range 0 to 15
      * 0  means 1.5  Cycle
      * 15 means 16.5 Cycles */
} HYPERBUS_Attrs;

/**
 *  \brief HYPERBUS driver object
 */

typedef struct
{
    HYPERBUS_Handle handle;
    /**< Instance handle */
    uint32_t isOpen;
    /**< Flag to indicate if the instance is already open */
    SemaphoreP_Object       lockObj;
    /**< Transfer Sync Semaphore object */
} HYPERBUS_Object;

/**
 *  \brief HYPERBUS driver configuration structure
 *
 *  This structure is used to pass configuration information to the
 *  HYPERBUS driver.
 */
typedef struct
{
    const HYPERBUS_Attrs *attrs;
    /**< Pointer to driver specific hardware attributes */
    HYPERBUS_Object *object;
    /**< Pointer to driver specific data object */
} HYPERBUS_Config;

/** \brief Externally defined driver configuration array */
extern HYPERBUS_Config gHyperBusConfig[];

/** \brief Externally defined driver configuration array size */
extern uint32_t    gHyperBusConfigNum;

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */

/**
 *  \brief  This function initializes the HYPERBUS module
 */
void HYPERBUS_init(void);

/**
 *  \brief  This function de-initializes the HYPERBUS module
 */
void HYPERBUS_deinit(void);

/**
 *  \brief  This function opens a given HYPERBUS peripheral
 *
 *  \pre    HYPERBUS controller has been initialized using #HYPERBUS_init()
 *
 *  \param  index       Index of config to use in the *HYPERBUS_Config* array
 *
 *  \return A #HYPERBUS_Handle on success or a NULL on an error or if it has been
 *          opened already
 *
 *  \sa     #HYPERBUS_init()
 *  \sa     #HYPERBUS_close()
 */
HYPERBUS_Handle HYPERBUS_open(uint32_t index);

/**
 *  \brief  Function to close a HYPERBUS peripheral specified by the HYPERBUS handle
 *
 *  \pre    #HYPERBUS_open() has to be called first
 *
 *  \param  handle      #HYPERBUS_Handle returned from #HYPERBUS_open()
 *
 *  \sa     #HYPERBUS_open()
 */
void HYPERBUS_close(HYPERBUS_Handle handle);

/**
 *  \brief  This function returns the handle of an open HYPERBUS Instance from the instance index
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  index Index of config to use in the *HYPERBUS_Config* array
 *
 *  \return An #HYPERBUS_Handle if it has been opened already or NULL otherwise
 *
 *  \sa     #HYPERBUS_init()
 *  \sa     #HYPERBUS_open()
 */
HYPERBUS_Handle HYPERBUS_getHandle(uint32_t index);

/**
 *  \brief  This function gets the SOC mapped data base address of the HyperRam
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  handle  An #HYPERBUS_Handle returned from an #HYPERBUS_open()
 *
 *  \return Data BaseAddress of the HyperRam
 */
uint32_t HYPERBUS_getHyperBusDataBaseAddr(HYPERBUS_Handle handle);

/**
 *  \brief  This function returns the memory configuration of the HYPERBUS Instance
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  handle  An #HYPERBUS_Handle returned from an #HYPERBUS_open()
 *  \param  pHyperBusMemCfg  An #HYPERBUS_MemCfg to be filled
 *
 *  \return memory configuration of the HYPERBUS Instance
 */
static uint32_t HYPERBUS_makeMemCfg(HYPERBUS_Handle handle, HYPERBUS_MemCfg *pHyperBusMemCfg);

/**
 *  \brief  This function returns the memory Timings of the HYPERBUS Instance
 *
 *  \pre    HYPERBUS controller has been opened using #HYPERBUS_open()
 *
 *  \param  handle  An #HYPERBUS_Handle returned from an #HYPERBUS_open()
 *  \param  pHyperBusMemTiming  An #HYPERBUS_MemTiming to be filled
 *
 *  \return memory Timings of the HYPERBUS Instance
 */
static uint32_t HYPERBUS_makeMemTiming(HYPERBUS_Handle handle, HYPERBUS_MemTiming *pHyperBusMemTiming);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HYPERBUS_H_ */
