/**
 *
 * \file    GPMC_v1.h
 *
 * \brief   This file contains the GPMC controller specific struct
 *          definition, macros and function prototypes.
 *
 ******************************************************************************/


/*
 * Copyright (c) 2016 - 2020, Texas Instruments Incorporated
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
 *
 */



#ifndef _GPMC__H_
#define _GPMC__H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/cslr_gpmc.h>
#include <kernel/dpl/CacheP.h>


#define GPMC_CHIP_SELECT_0                            (0U)
#define GPMC_CHIP_SELECT_1                            (1U)
#define GPMC_CHIP_SELECT_2                            (2U)
#define GPMC_CHIP_SELECT_3                            (3U)
#define GPMC_CHIP_SELECT_4                            (4U)
#define GPMC_CHIP_SELECT_5                            (5U)
#define GPMC_CHIP_SELECT_6                            (6U)
#define GPMC_CHIP_SELECT_7                            (7U)
/*
* \brief Macros which can be used as 'flag' parameter to GPMCIntStatusGet,
* GPMCIntStatusClear APIs.
* @{
*/
#define GPMC_FIFOEVENT_STATUS                         (0U)
#define GPMC_TERMINALCOUNT_STATUS                     (1U)
#define GPMC_WAIT0EDGEDETECTION_STATUS                (2U)
#define GPMC_WAIT1EDGEDETECTION_STATUS                (3U)
/* @} */

/*
* \brief Macros which can be used as 'flag' parameter to GPMCIntEnable, GPMCIntDisable
* APIs.
* @{
*/
#define GPMC_FIFOEVENT_INT                            (0U)
#define GPMC_TERMINALCOUNT_INT                        (1U)
#define GPMC_WAIT0EDGEDETECTION_INT                   (2U)
#define GPMC_WAIT1EDGEDETECTION_INT                   (3U)
/* @} */


/* NAND Flash specific Configuration vals*/
/*
* \breif Macros which can be used as 'accessMode' parameter to
* GPMCPREFETCHAccessModeSelect API.
* @{
*/
#define GPMC_PREFETCH_ACCESSMODE_READ                 (0U)
#define GPMC_PREFETCH_ACCESSMODE_WRITE                (1U)
/* @} */

/*
* Macros which can be used as 'syncType' parameter to
* GPMCPREFETCHSyncTypeSelect API.
* @{
*/
#define GPMC_PREFETCH_SYNCTYPE_DMA                    (1U)
#define GPMC_PREFETCH_SYNCTYPE_INT                    (0U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCPrefetchSyncModeConfig
* API.
* @{
*/
#define GPMC_PREFETCH_ACCESSCS_AT_START               (0U)
#define GPMC_PREFETCH_ACCESSCS_AT_STARTANDWAIT        (1U)
/* @} */

/*
* \breif Macros which can be used as 'waitPin' parameter to GPMCPrefetchWaitPinSelect
* API.
* @{
*/
#define GPMC_PREFETCH_WAITPINSELECTOR_W0              (0U)
#define GPMC_PREFETCH_WAITPINSELECTOR_W1              (1U)
/* @} */

/*
* \breif Macros which can be used as 'configVal' GPMCPrefetchAccessCycleOptConfig API.
* @{
*/
#define GPMC_PREFETCH_OPTIMIZED_ACCESS_ENABLE         (1U)
#define GPMC_PREFETCH_OPTIMIZED_ACCESS_DISABLE        (0U)
/* @} */

/*
* \breif Macros which can be used as 'configVal' parameter to
* GPMCPrefetchRRArbitrationConfig API.
* @{
*/
#define GPMC_PREFETCH_RR_ARBITRATION_ENABLE           (1U)
#define GPMC_PREFETCH_RR_ARBITRATION_DISABLE          (0U)
/* @} */

/*
* \breif Macros which can be used as 'algo' parameter to GPMCECCAlgoSelect API.
* @{
*/
#define GPMC_ECC_ALGORITHM_HAMMINGCODE                (0U)
#define GPMC_ECC_ALGORITHM_BCH                        (1U)
/* @} */

/*
* \breif Macros which can be used as 'errCorrCapVal' parameter to
* GPMCECCBCHErrCorrectionCapSelect API.
* @{
*/
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_4BITS            (0U)
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS            (1U)
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_16BITS           (2U)
/* @} */

/*
* \breif Macros which can be used as 'eccColVal' parameter to GPMCECCColumnSelect API.
* @{
*/
#define GPMC_ECC_COLUMNS_8                            (0U)
#define GPMC_ECC_COLUMNS_16                           (1U)
/* @} */

/*
* \breif Macros which can be used as 'numOfSects' parameter to
* GPMCECCBCHNumOfSectorsSelect API.
* Here 1 SECTOR = 512 bytes.
* @{
*/
#define GPMC_ECC_BCH_NUMOFSECTS_1                     (0U)
#define GPMC_ECC_BCH_NUMOFSECTS_2                     (1U)
#define GPMC_ECC_BCH_NUMOFSECTS_3                     (2U)
#define GPMC_ECC_BCH_NUMOFSECTS_4                     (3U)
#define GPMC_ECC_BCH_NUMOFSECTS_5                     (4U)
#define GPMC_ECC_BCH_NUMOFSECTS_6                     (5U)
#define GPMC_ECC_BCH_NUMOFSECTS_7                     (6U)
#define GPMC_ECC_BCH_NUMOFSECTS_8                     (7U)
/* @} */

/*
* \breif Macros which can be used as 'eccResReg' parameter to GPMCECCResultRegSelect
* API.
* @{
*/
#define GPMC_ECCPOINTER_RESULT_1                      (1U)
#define GPMC_ECCPOINTER_RESULT_2                      (2U)
#define GPMC_ECCPOINTER_RESULT_3                      (3U)
#define GPMC_ECCPOINTER_RESULT_4                      (4U)
#define GPMC_ECCPOINTER_RESULT_5                      (5U)
#define GPMC_ECCPOINTER_RESULT_6                      (6U)
#define GPMC_ECCPOINTER_RESULT_7                      (7U)
#define GPMC_ECCPOINTER_RESULT_8                      (8U)
#define GPMC_ECCPOINTER_RESULT_9                      (9U)
/* @} */

/*
* \breif Macros which can be used as 'eccSize' parameter to GPMCECCSizeValSet API.
* @{
*/
#define GPMC_ECC_SIZE_0                               (0U)
#define GPMC_ECC_SIZE_1                               (1U)
/* @} */

/*
* \breif Macros which can be used as 'eccResReg' parameter to GPMCECCResultSizeSelect
* API.
* @{
*/
#define GPMC_ECC_RESULT_1                             (1U)
#define GPMC_ECC_RESULT_2                             (2U)
#define GPMC_ECC_RESULT_3                             (3U)
#define GPMC_ECC_RESULT_4                             (4U)
#define GPMC_ECC_RESULT_5                             (5U)
#define GPMC_ECC_RESULT_6                             (6U)
#define GPMC_ECC_RESULT_7                             (7U)
#define GPMC_ECC_RESULT_8                             (8U)
#define GPMC_ECC_RESULT_9                             (9U)
/* @} */

/*
* \breif Macros which can be used as 'resIndex' parameter to GPMCECCBCHResultGet API.
* @{
*/
#define GPMC_BCH_RESULT0                             (0U)
#define GPMC_BCH_RESULT1                             (1U)
#define GPMC_BCH_RESULT2                             (2U)
#define GPMC_BCH_RESULT3                             (3U)
#define GPMC_BCH_RESULT4                             (4U)
#define GPMC_BCH_RESULT5                             (5U)
#define GPMC_BCH_RESULT6                             (6U)
/* @} */

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         CS signal timing configuration.\n
 *
 * \param  CSWrOffTime    CS# de-assertion time from start cycle time for write
 *                        accesses in GPMC_FCLK cycles.
 *
 *         CSRdOffTime    CS# de-assertion time from start cycle time for read
 *                        accesses in GPMC_FCLK cycles
 *
 *         CSExtDelayFlag Flag to indicate whether to add half GPMC_FCLK delay
 *                        to CS or not.
 *                        This can take one of the following values :
 *                        GPMC_CS_EXTRA_DELAY --   CS# Timing control
 *                                                 signal is delayed of
 *                                                 half GPMC_FCLK cycle.
 *                        GPMC_CS_EXTRA_NODELAY -- CS# Timing control
 *                                                 signal is not delayed
 *
 *         CSOnTime       CS# assertion time from start cycle time in GPMC_FCLK
 *                        cycles.
 */

#define GPMC_CS_TIMING_CONFIG(CSWrOffTime, CSRdOffTime, CSExtDelayFlag, \
                              CSOnTime)                                 \
    ((uint32_t) (((CSWrOffTime) << CSL_GPMC_CONFIG2_CSWROFFTIME_SHIFT)    \
                 & CSL_GPMC_CONFIG2_CSWROFFTIME_MASK) |                   \
     (((CSRdOffTime) << CSL_GPMC_CONFIG2_CSRDOFFTIME_SHIFT)               \
      & CSL_GPMC_CONFIG2_CSRDOFFTIME_MASK) |                              \
     (((CSExtDelayFlag) << CSL_GPMC_CONFIG2_CSEXTRADELAY_SHIFT)           \
      & CSL_GPMC_CONFIG2_CSEXTRADELAY_MASK) |                             \
     (((CSOnTime) << CSL_GPMC_CONFIG2_CSONTIME_SHIFT)                     \
      & CSL_GPMC_CONFIG2_CSONTIME_MASK))


/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         ADV# signal timing configuration.\n
 *
 * \param  ADVAADMuxWrOffTime    ADV# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         ADVAADMuxRdOffTime    ADV# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         ADVWrOffTime          ADV# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time for write accesses
 *
 *         ADVRdOffTime          ADV# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time for write accesses
 *
 *         ADVExtDelayFlag       Flag to indicate whether to add half GPMC_FCLK
 *                               delay to ADV or not.
 *                               This can take one of the following values :
 *                               GPMC_ADV_EXTRA_DELAY --   ADV# Timing control
 *                                                         signal is delayed of
 *                                                         half GPMC_FCLK cycle.
 *                               GPMC_ADV_EXTRA_NODELAY -- ADV# Timing control
 *                                                         signal is not
 *                                                         delayed.
 *
 *         ADVAADMuxOnTime       ADV# assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the
 *                               AAD-Multiplexed protocol.
 *
 *         ADVOnTime             ADV# assertion time from start cycle time in
 *                               GPMC_FCLK cycles.
 */

#define GPMC_ADV_TIMING_CONFIG(ADVAADMuxWrOffTime, ADVAADMuxRdOffTime,      \
                               ADVWrOffTime, ADVRdOffTime, ADVExtDelayFlag, \
                               ADVAADMuxOnTime,                             \
                               ADVOnTime)                                   \
    ((uint32_t) (((ADVAADMuxWrOffTime) <<                                   \
                  CSL_GPMC_CONFIG3_ADVAADMUXWROFFTIME_SHIFT) &                \
                 CSL_GPMC_CONFIG3_ADVAADMUXWROFFTIME_MASK) |                  \
     (((ADVAADMuxRdOffTime) << CSL_GPMC_CONFIG3_ADVAADMUXRDOFFTIME_SHIFT) &   \
      CSL_GPMC_CONFIG3_ADVAADMUXRDOFFTIME_MASK) |                             \
     (((ADVWrOffTime) << CSL_GPMC_CONFIG3_ADVWROFFTIME_SHIFT) &               \
      CSL_GPMC_CONFIG3_ADVWROFFTIME_MASK) |                                   \
     (((ADVRdOffTime) << CSL_GPMC_CONFIG3_ADVRDOFFTIME_SHIFT) &               \
      CSL_GPMC_CONFIG3_ADVRDOFFTIME_MASK) |                                   \
     (((ADVExtDelayFlag) << CSL_GPMC_CONFIG3_ADVEXTRADELAY_SHIFT) &           \
      CSL_GPMC_CONFIG3_ADVEXTRADELAY_MASK) |                                  \
     (((ADVAADMuxOnTime) << CSL_GPMC_CONFIG3_ADVAADMUXONTIME_SHIFT) &         \
      CSL_GPMC_CONFIG3_ADVAADMUXONTIME_MASK) |                                \
     (((ADVOnTime) << CSL_GPMC_CONFIG3_ADVONTIME_SHIFT) &                     \
      CSL_GPMC_CONFIG3_ADVONTIME_MASK))


/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         WE# and OE# signal timing configuration.\n
 *
 * \param  WEOffTime             WE# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         WEExtDelayFlag        Flag to indicate whether to add half GPMC_FCLK
 *                               delay to WE or not.
 *                               This can take one of the following values :
 *                               GPMC_WE_EXTRA_DELAY --   WE# Timing control
 *                                                        signal is delayed of
 *                                                        half GPMC_FCLK cycle.
 *                               GPMC_WE_EXTRA_NODELAY -- WE# Timing control
 *                                                        signal is not delayed
 *         WEOnTime              WE# assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         OEAADMuxOffTime       OE# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         OEOffTime             OE# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         OEExtDelayFlag        Flag to indicate whether to add half GPMC_FCLK
 *                               delay to OE or not.
 *                               This can take one of the following values :
 *                               GPMC_OE_EXTRA_DELAY --   OE# Timing control
 *                                                        signal is delayed of
 *                                                        half GPMC_FCLK cycle.
 *                               GPMC_OE_EXTRA_NODELAY -- OE# Timing control
 *                                                        signal is not delayed
 *
 *         OEAADMuxOnTime        OE# assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         OEOnTime              OE# assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 */

#define GPMC_WE_OE_TIMING_CONFIG(WEOffTime, WEExtDelayFlag, WEOnTime,           \
                                 OEAADMuxOffTime, OEOffTime, OEExtDelayFlag,    \
                                 OEAADMuxOnTime, OEOnTime)                      \
    ((uint32_t) (((WEOffTime) <<                                                \
                  CSL_GPMC_CONFIG4_WEOFFTIME_SHIFT) &                             \
                 CSL_GPMC_CONFIG4_WEOFFTIME_MASK) |                               \
     (((WEExtDelayFlag) <<                                                      \
       CSL_GPMC_CONFIG4_WEEXTRADELAY_SHIFT) & CSL_GPMC_CONFIG4_WEEXTRADELAY_MASK) | \
     (((WEOnTime) <<                                                            \
       CSL_GPMC_CONFIG4_WEONTIME_SHIFT) & CSL_GPMC_CONFIG4_WEONTIME_MASK) |         \
     (((OEAADMuxOffTime) <<                                                     \
       CSL_GPMC_CONFIG4_OEAADMUXOFFTIME_SHIFT) &                                  \
      CSL_GPMC_CONFIG4_OEAADMUXOFFTIME_MASK) |                                    \
     (((OEOffTime) <<                                                           \
       CSL_GPMC_CONFIG4_OEOFFTIME_SHIFT) & CSL_GPMC_CONFIG4_OEOFFTIME_MASK) |       \
     (((OEExtDelayFlag) <<                                                      \
       CSL_GPMC_CONFIG4_OEEXTRADELAY_SHIFT) & CSL_GPMC_CONFIG4_OEEXTRADELAY_MASK) | \
     (((OEAADMuxOnTime) <<                                                      \
       CSL_GPMC_CONFIG4_OEAADMUXONTIME_SHIFT) &                                   \
      CSL_GPMC_CONFIG4_OEAADMUXONTIME_MASK) |                                     \
     (((OEOnTime) <<                                                            \
       CSL_GPMC_CONFIG4_OEONTIME_SHIFT) & CSL_GPMC_CONFIG4_OEONTIME_MASK))

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         read access and cycle time timing configuration.\n
 *
 * \param  rdCycleTime           Total read cycle time in GPMC_FCLK cycles.
 *
 *         wrCycleTime           Total write cycle time in GPMC_FCLK cycles.
 *
 *         rdAccessTime          Read access time (Delay between start cycle
 *                               time and first data valid) in GPMC_FCLK cycles.
 *
 *         pageBurstAccessTime   Page burest access time (Delay between
 *                               successive words in a multiple access)in
 *                               GPMC_FCLK cycles.
 *
 */

#define GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG(rdCycleTime, wrCycleTime,         \
                                              rdAccessTime,                     \
                                              pageBurstAccessTime)              \
    ((uint32_t) (((rdCycleTime) <<                                              \
                  CSL_GPMC_CONFIG5_RDCYCLETIME_SHIFT) &                           \
                 CSL_GPMC_CONFIG5_RDCYCLETIME_MASK) |                             \
     (((wrCycleTime) <<                                                         \
       CSL_GPMC_CONFIG5_WRCYCLETIME_SHIFT) & CSL_GPMC_CONFIG5_WRCYCLETIME_MASK) |   \
     (((rdAccessTime) <<                                                        \
       CSL_GPMC_CONFIG5_RDACCESSTIME_SHIFT) & CSL_GPMC_CONFIG5_RDACCESSTIME_MASK) | \
     (((pageBurstAccessTime) <<                                                 \
       CSL_GPMC_CONFIG5_PAGEBURSTACCESSTIME_SHIFT) &                              \
      CSL_GPMC_CONFIG5_PAGEBURSTACCESSTIME_MASK))


/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         cycle to cycle and bus turn around time timing configuration.\n
 *
 * \param  cycle2CycleDelay       Cycle to cycle delay (Chip select high pulse
 *                                delay between two successive accesses)in
 *                                GPMC_FCLK cycles.
 *
 *      cycle2CycleDelaySameCSCfg Specified whether to add the cycle to cycle
 *                                delay between two successive accesses or not
 *                                (to the same chip-select).
 *                                This can take one of the following values :
 *                                GPMC_CYCLE2CYCLESAMECSEN_C2CDELAY   -- To add
 *                                                                    the delay.
 *                                GPMC_CYCLE2CYCLESAMECSEN_NOC2CDELAY -- Don't
 *                                                                add the delay.
 *
 *      cycle2CycleDelayDiffCSCfg Specified whether to add the cycle to cycle
 *                                delay between two successive accesses or not
 *                                (to the diffrent chip-select).
 *                                This can take one of the following values :
 *                                GPMC_CYCLE2CYCLEDIFFCSEN_C2CDELAY   -- To add
 *                                                                    the delay.
 *                                GPMC_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY -- Don't
 *                                                                add the delay.
 *
 *         busTAtime             Bus turn aroung time between two successive
 *                               accesses to the same chip-select
 *                               (read to write) or to a diff chip-select in
 *                               GPMC_FCLK cycles.
 *
 */

#define GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG(cycle2CycleDelay,          \
                                                     cycle2CycleDelaySameCSCfg, \
                                                     cycle2CycleDelayDiffCSCfg, \
                                                     busTAtime)                 \
    ((uint32_t) (((cycle2CycleDelay) <<                                         \
                  CSL_GPMC_CONFIG6_CYCLE2CYCLEDELAY_SHIFT) &                      \
                 CSL_GPMC_CONFIG6_CYCLE2CYCLEDELAY_MASK) |                        \
     (((cycle2CycleDelaySameCSCfg) <<                                           \
       CSL_GPMC_CONFIG6_CYCLE2CYCLESAMECSEN_SHIFT) &                              \
      CSL_GPMC_CONFIG6_CYCLE2CYCLESAMECSEN_MASK) |                                \
     (((cycle2CycleDelayDiffCSCfg) <<                                           \
       CSL_GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN_SHIFT) &                              \
      CSL_GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN_MASK) |                                \
     (((busTAtime) <<                                                           \
       CSL_GPMC_CONFIG6_BUSTURNAROUND_SHIFT) & CSL_GPMC_CONFIG6_BUSTURNAROUND_MASK))




/*
* \breif Macros which can be used as 'addrMask' parameter to GPMCSMaskAddrSet API.
* @{
*/
#define GPMC_CS_MASK_ADDR_SIZE_256MB                            (0x00U)
#define GPMC_CS_MASK_ADDR_SIZE_128MB                            (0x08U)
#define GPMC_CS_MASK_ADDR_SIZE_64MB                             (0x0cU)
#define GPMC_CS_MASK_ADDR_SIZE_32MB                             (0x0eU)
#define GPMC_CS_MASK_ADDR_SIZE_16MB                             (0x0fU)
/* @} */

/* Nand flash specific GPMC timing parameters */
#define GPMC_NAND_CS_ON_TIME               0U          //!< Chip select on time  (FCLK periods)
#define GMPC_NAND_WE_ON_TIME               0U          //!< Write enable on time (FCLK periods)
#define GMPC_NAND_ADV_ON_TIME              0U          //!< Address valid on time (FCLK periods)

#define GMPC_NAND_CS_WR_OFF_TIME           8U          //!< Chip select off time for write (FCLK periods)
#define GMPC_NAND_WR_CYCLE_TIME            8U          //!< Read cycle time (FCLK periods)
#define GMPC_NAND_ADV_WR_OFF_TIME          8U          //!< Address valid off time for read (FCLK periods)

#define GMPC_NAND_CS_RD_OFF_TIME          11U          //!< Chip select off time for read (FCLK periods)
#define GMPC_NAND_RD_CYCLE_TIME           11U          //!< Read cycle time (FCLK periods)

#define GMPC_NAND_ADV_AADMUX_ON_TIME       0U
#define GMPC_NAND_ADV_AADMUX_RD_OFF_TIME   0U
#define GMPC_NAND_ADV_AADMUX_WR_OFF_TIME   0U

#define GPMC_NAND_PAGEBURST_ACCESS_TIME    0U

#define GMPC_NAND_OE_ON_TIME               0U          //!< Output enable on time (FCLK periods)
#define GMPC_NAND_OE_OFF_TIME              8U          //!< Output enable off time (FCLK periods)

#define GMPC_NAND_OE_AADMUX_ON_TIME        0U
#define GMPC_NAND_OE_AADMUX_OFF_TIME       0U

#define GMPC_NAND_ADV_RD_OFF_TIME          8U          //!< Address valid off time for read (FCLK periods)
#define GMPC_NAND_WE_OFF_TIME              5U          //!< Write enable off time (FCLK periods)
#define GMPC_NAND_RD_ACCESS_TIME           7U          //!< Read access time (FCLK periods)
#define GMPC_NAND_C2C_DELAY                1U          //!< CS high pulse delay (FCLK periods)
#define GMPC_NAND_ADMUX_DATA_VALID         0U          //!< First data write cycle (FCLK)
#define GMPC_NAND_WR_ACCESS_TIME           0U          //!< Write access time (FCLK periods)
#define GMPC_NAND_BRST_TAROUND_TIME        0U          //!< Burst turnaround latency (FCLK periods)


#define GPMC_CS_BASE_ADDR_SHIFT                      (24U)

#define GPMC_ECC_WRAP_MODE1                          (1)

#define GPMC_CMD_INVALID                             (0xFFFFFFFFU)


#define GPMC_MODULE_RESET_WAIT_TIME_MAX              (10 * 1000) /*10ms*/
#define GPMC_WAIT_PIN_STATUS_WAIT_TIME_MAX           (10 * 1000U) /*1ms*/
#define GPMC_WAIT_PIN_STATUS_WAIT_TIME_MIN           (0U) /*1ms*/
#define GPMC_ELM_ERR_STATUS_TIMEOUT_MAX              (10 * 1000U) /*1ms*/
/*
 *  \brief  Nand ECC alogorithm typedef
 */
typedef enum GPMC_v1_nandEccAlgo_s
{
    GPMC_NAND_ECC_ALGO_NONE  = 0x00U,
    GPMC_NAND_ECC_ALGO_HAMMING_1BIT,
    GPMC_NAND_ECC_ALGO_BCH_4BIT,
    GPMC_NAND_ECC_ALGO_BCH_8BIT,
    GPMC_NAND_ECC_ALGO_BCH_16BIT

} GPMC_nandEccAlgo;

/******************************************************************************
*          Structures to be passed to GPMC_soc
******************************************************************************/
/** \brief A handle that is returned from a #GPMC_open() call */

typedef void* GPMC_Handle;


typedef struct
{
    uint32_t cmdCycle1;
    uint32_t cmdCycle2;
    uint32_t rowAddress;
    uint32_t numRowAddrCycles;
    uint32_t colAddress;
    uint32_t numColAddrCycles;
    uint32_t waitTimeout;
    uint32_t checkReadypin;

} GPMC_nandCmdParams;


typedef enum GPMC_OperatingMode_s {
    /* Interupt based blocking mode */
    GPMC_OPERATING_MODE_BLOCKING = 0,
    /* Interupt based callback mode*/
    GPMC_OPERATING_MODE_CALLBACK,
    /* Non interupt base blocking mode*/
    GPMC_OPERATING_MODE_POLLING

} GPMC_OperatingMode;

/**
 *  \anchor GPMC_TransferMode
 *  \name Transfer Mode
 *
 *  This determines whether the driver operates synchronously or asynchronously
 *
 *  In #GPMC_TRANSFER_MODE_BLOCKING \ref GPMC_Transfer block code
 *  execution until the transaction has completed
 *
 *  In #GPMC_TRANSFER_MODE_CALLBACK GPMC_Transfers does not block code
 *  execution and instead calls a callback function when the
 *  transaction has completed
 *
 *  @{
 */
typedef enum GPMC_TransferMode_s {
    /**
     *  \brief \ref GPMC_Transfers blocks execution. This mode can only be used
    *  when called within a Task context and is interrupt based
    */
    GPMC_TRANSFER_MODE_BLOCKING = 0,
    /**
    *  \brief \ref GPMC_Transfers does not block code execution and will call a
    *  callback function. This mode can be used in a Task, Swi, or Hwi context
    */
    GPMC_TRANSFER_MODE_CALLBACK,
} GPMC_TransferMode;
/** @} */

/*!
 *  @brief      Type of the GPMC transaction.
 */
typedef enum GPMC_TransactionType_e {
    GPMC_TRANSACTION_TYPE_READ = 0,  /*!< Read transaction */
    GPMC_TRANSACTION_TYPE_WRITE      /*!< Write transaction */
} GPMC_TransactionType;


/*!
 *  @brief      Status codes that are set by the GPMC driver.
 */
typedef enum GPMC_TransactionStatus_s {
    GPMC_TRANSFER_COMPLETED = 0,
    GPMC_TRANSFER_STARTED,
    GPMC_TRANSFER_CANCELED,
    GPMC_TRANSFER_FAILED,
    GPMC_TRANSFER_CSN_DEASSERT,
    GPMC_TRANSFER_TIMEOUT,

} GPMC_TransactionStatus;

/*!
 *  @brief
 *  A ::GPMC_Transaction data structure is used with GPMC_transfer().
 */
typedef struct GPMC_Transaction_s {
    /* [IN] Transaction type */
	GPMC_TransactionType    transType;
    /* [IN] Number of bytes for this transaction */
    uint32_t                count;
    /* [IN] void * to a buffer to receive/send data */
    void                    *Buf;
    /* [IN] Argument to be passed to the callback function */
    void                    *arg;
    /* [IN] Timeout of the specific transfer */
    uint32_t                transferTimeout;
    /* [OUT] Status code set by GPMC_transfer */
    GPMC_TransactionStatus status;

} GPMC_Transaction;

/*!
 *  @brief      The definition of a callback function used by the GPMC driver
 *              when used in ::GPMC_MODE_CALLBACK
 *
 *  @param      GPMC_Handle          GPMC_Handle
 *  @param      GPMC_Transaction*    GPMC_Transaction*
 */
typedef void (*GPMC_CallbackFxn)(GPMC_Handle handle,
                                 GPMC_Transaction * transaction);


/**
 *  \brief  Parameters
 *
 *  GPMC Parameters are used to with the #GPMC_open() call. Default values for
 *  these parameters are set using #GPMC_Params_init().
 *
 *  If NULL is passed for the parameters, #GPMC_open() uses default parameters.
 *
 *  \sa #GPMC_Params_init()
 */
typedef struct GPMC_Params_s
{
    /* Index of Channel used by GPMC DMA Driver. This index will be set by SysCfg according to the DMA driver chosen.
     * The GPMC driver uses this index to do an \ref GPMC_dmaOpen inside the \ref GPMC_open if the DMA mode is enabled
     */
    int32_t                 gpmcDmaChIndex;
    /* device type, NAND or NOR like */
    uint32_t                devType;
    /* device size, 8-bit, 16-bit or 32-bit bus width */
    uint32_t                devSize;
    /* Signals timing latencies scalar factor */
    uint32_t                chipSel;
    /* Enable GPMC interrupt. */
    uint32_t                intrEnable;
    /* Enable GPMC DMA mode. */
    uint32_t                dmaEnable;
    /* Polling, blocking or callback mode . Refer \ref GPMC_TransferMode */
    GPMC_TransferMode       transferMode;
    /* Callback function pointer*/
    GPMC_CallbackFxn        transferCallBckFunc;

} GPMC_Params;

/*
 *  @brief  GPMC UDMA info structure
 */
typedef struct GPMC_dmaInfo_s {
    /* UDMA driver handle */
    void            *drvHandle;
    /* UDMA channel handle */
    void            *chHandle;
    /* UDMA ring memory pointers */
    void            *ringMem;
    /* UDMA complete queue ring memory pointers */
    void            *cqRingMem;
    /* UDMA tear down complete queue ring memory pointers */
    void            *tdCqRingMem;
    /* UDMA TR PD memory pointers */
    void            *tprdMem;
    /* UDMA event handles */
    void            *eventHandle;

} GPMC_dmaInfo;

/*
 *  @brief  GPMC_Object
 *
 *  The application must not access any member variables of this structure
 */
typedef struct GPMC_Object_s {
    /* Instance handle */
    GPMC_Handle                     handle;
    /* Callback function pointer */
    GPMC_CallbackFxn                transferCallbackFxn;
    /* Driver user configurable params structure */
    GPMC_Params                     params;
    /* GPMC Driver operating mode */
    GPMC_OperatingMode              operMode;
    /*
     * State variables
     */
    /* Flag to indicate if the instance is already open */
    uint32_t                        isOpen;
    /* Interrupt object */
    HwiP_Object                     hwi;
    /* Driver lock object */
    SemaphoreP_Object               mutex;
    /* Transfer Sync Semaphore object */
    SemaphoreP_Object               transferComplete;
    /* Pointer to current transaction struct */
    GPMC_Transaction                *transaction;
    /* UDMA configuration info */
    GPMC_dmaInfo           *dmaInfo;

} GPMC_Object;

/*
 *  \brief  Structure holding the timing parameters
 */
typedef struct GPMC_timingParams_s
{
    uint32_t    csOnTime;
    /* Chip Select assertion time. */
    uint32_t    csRdOffTime;
    /* Chip Select Read de-assertion time. */
    uint32_t    csWrOffTime;
    /* Chip Select Write de-assertion time. */
    uint32_t    advOnTime;
    /* ADV Assertion time. */
    uint32_t    advRdOffTime;
    /* ADV Read de-assertion time. */
    uint32_t    advWrOffTime;
    /* ADV Write de-assertion time. */
    uint32_t    advAadMuxOnTime;
    /* ADV Assertion time in an AADMultiplexed access. */
    uint32_t    advAadMuxRdOffTime;
    /* ADV Read de-assertion time in an AADMultiplexed access. */
    uint32_t    advAadMuxWrOffTime;
    /* ADV Write de-assertion time in an AADMultiplexed access. */
    uint32_t    weOnTtime;
    /* WE assertion time. */
    uint32_t    weOffTime;
    /* WE de-assertion time. */
    uint32_t    oeOnTime;
    /* OE assertion time. */
    uint32_t    oeOffTime;
    /* OE de-assertion time. */
    uint32_t    oeAadMuxOnTime;
    /* OE assertion time in an AADMultiplexed access. */
    uint32_t    oeAadMuxOffTime;
    /* OE de-assertion time in an AADMultiplexed access. */
    uint32_t    pageBurstAccess;
    /* Multiple access word delay. */
    uint32_t    rdAccessTime;
    /* Start-cycle to first valid delay. */
    uint32_t    wrAcessTime;
    /* Delay from StartAccessTime to the CLK rising edge. */
    uint32_t    rdCycleTime;
    /* Total read cycle time. */
    uint32_t    wrCycleTime;
    /* Total write cycle time. */
    uint32_t    wrDataOnMuxBusTime;
    /* Write Data on Mux Bus Time. */
    uint32_t    cycle2CycleDelay;
    /* Chip Select high pulse delay between two successive accesses. */
    uint32_t    cycleDelaySameChipSel;
    /* Value to control adding of cycle2cycle delay between two successive
         accesses to the same chip select. */
    uint32_t    cycleDelayDiffChipSel;
    /* Value to control adding of cycle2cycle delay between two successive
         accesses to the different chip select. */
    uint32_t    busTurnAroundTime;
    /* Bus turn around time between two successive
         accesses to the same chip-select (read to write)
         or to a different chip-select(read to read and read to write)
         in GPMC_FCLK cycles. */
} GPMC_timingParams;



/*
 *  @brief  GPMC Hardware attributes
 */
typedef struct GPMC_HwAttrs_s {
    /*
     * SOC configuration
     */
    /* GPMC Peripheral base address. */
    uint32_t                gpmcBaseAddr;
    /* GPMC flash base address. */
    uint32_t                dataBaseAddr;
    /* Error Location Module base address for ECC computation. */
    uint32_t                elmBaseAddr;
    /* GPMC module input clock frequency. */
    uint32_t                inputClkFreq;
    /* GPMC Peripheral interupt number */
    uint32_t                intrNum;
    /* Interupt priority*/
    uint32_t                intrPriority;
    /* GPMC FCLK divider*/
    uint32_t                clkDivider;
    /* address and data multiplexed protocol */
    uint32_t                addrDataMux;
    /* Current Active chip select in use by the memory controller */
    uint32_t                timeLatency;
    /* Chip select base address (A29 - A24) */
    uint32_t                chipSelBaseAddr;
    /* Chip select address mask size */
    uint32_t                chipSelAddrSize;
    /* Wait pin number */
    uint32_t                waitPinNum;
    /* Wait pin polarity  */
    uint32_t                waitPinPol;
    /* Structure holding the timing parameters for the device. */
    GPMC_timingParams       timingParams;
    /* ECC algorithm supported by the controller. */
    GPMC_nandEccAlgo        eccAlgo;
    /* Read operation mode */
    uint32_t                readType;
    /* Write operation mode */
    uint32_t                writeType;
    /* Chip Select Extra Delay flag. */
    uint32_t                csExDelay;
    /* Memory access type */
    uint32_t                accessType;

} GPMC_HwAttrs;

/*
 *  @brief  GPMC Driver configuration structure
 */
typedef struct GPMC_Config_s {
    /* Pointer to driver specific hardware attributes */
    const GPMC_HwAttrs * attrs;
    /* Pointer to driver specific data object */
    GPMC_Object *object;

} GPMC_Config;

static inline void GPMC_Params_init(GPMC_Params *params);

static inline void GPMC_Params_init(GPMC_Params *params)
{
    if (params != NULL)
    {
        params->dmaEnable = FALSE;
        params->intrEnable = FALSE;
        params->chipSel = 0; //todo: use macro
        params->devType = CSL_GPMC_CONFIG1_DEVICETYPE_NANDLIKE;
        params->devType = CSL_GPMC_CONFIG1_DEVICESIZE_EIGHTBITS;
        params->gpmcDmaChIndex = -1;
        params->transferMode = GPMC_TRANSFER_MODE_BLOCKING;
        params->transferCallBckFunc = NULL;
    }
}
/** \brief Externally defined driver configuration array */
extern GPMC_Config gGpmcConfig[];
/** \brief Externally defined driver configuration array size */
extern uint32_t gGpmcConfigNum;

int32_t GPMC_ECCSizeValSet(GPMC_Handle handle, uint32_t eccSize, uint32_t eccSizeVal);
int32_t GPMC_BCHECCconfigureELM(GPMC_Handle handle);
int32_t GPMC_nandBCHEccConfig (GPMC_Handle handle);
int32_t GPMC_ECCengineEnable(GPMC_Handle handle);
void GPMC_ECCResultRegisterClear(GPMC_Handle handle);
int32_t GPMC_BCHECCcheckError(GPMC_Handle handle, uint32_t *bchData, uint32_t *errCount, uint32_t *errLoc);

void GPMC_writeNandCommandParamsInit(GPMC_nandCmdParams *cmdParams);
int32_t GPMC_writeNandCommand(GPMC_Handle handle, GPMC_nandCmdParams *cmdParams);
void GPMC_transactionInit(GPMC_Transaction *trans);
int32_t GPMC_nandReadData(GPMC_Handle handle, GPMC_Transaction *trans);
GPMC_Handle GPMC_getHandle(uint32_t driverInstanceIndex);

GPMC_Handle GPMC_open(uint32_t index, const GPMC_Params *prms);
void GPMC_close(GPMC_Handle handle);

int32_t GPMC_SetDeviceSize(GPMC_Handle handle, uint32_t deviceSize);
int32_t GPMC_SetDeviceType(GPMC_Handle handle, uint32_t deviceType);
int32_t GPMC_configureTimingParameters(GPMC_Handle handle);
void GPMC_init(void);
void GPMC_deinit(void);


uint32_t GPMC_getInputClk(GPMC_Handle handle);

#ifdef __cplusplus
}
#endif

#endif  /* _GPMC__H_ */
