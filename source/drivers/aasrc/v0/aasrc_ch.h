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
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_CHANNEL_MODULE AASRC Channel Configuration APIs
 *            This is AASRC channel related configuration parameters and
 *            API
 *
 *  @{
 */

/**
 *  \file v0/aasrc_ch.h
 *
 *  \brief AASRC channel related parameters and API.
 */

#ifndef AASRC_CH_H_
#define AASRC_CH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/aasrc/v0/aasrc_transactions.h>
#include <drivers/aasrc/v0/aasrc_dma.h>

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Default Input fifo threshold */
#define AASRC_DEFAULT_IN_FIFO_THRESHOLD         (16U)
/** \brief Default Output fifo threshold */
#define AASRC_DEFAULT_OUT_FIFO_THRESHOLD        (16U)

/** \brief Max Input fifo threshold */
#define AASRC_MAX_IN_FIFO_THRESHOLD             (32U)
/** \brief Max Output fifo threshold */
#define AASRC_MAX_OUT_FIFO_THRESHOLD            (16U)

/**
 *  \anchor AASRC_ChannelId
 *  \name AASRC Channel Id
 *
 *  Values used to determine the channel number used for AASRC
 *  communication. This determines which ASRC channel to use.
 *
 *  @{
 */
#define AASRC_CHANNEL_0                         (0U)
#define AASRC_CHANNEL_1                         (1U)
#define AASRC_CHANNEL_2                         (2U)
#define AASRC_CHANNEL_3                         (3U)
#define AASRC_CHANNEL_4                         (4U)
#define AASRC_CHANNEL_5                         (5U)
#define AASRC_CHANNEL_6                         (6U)
#define AASRC_CHANNEL_7                         (7U)
/** @} */

/**
 *  \anchor AASRC_GrpId
 *  \name AASRC Group Id
 *
 *  This represents the number of channel groups available in the AASRC IPs.
 *  Max number of groups in the chip is SOC dependent.
 *
 *  @{
 */
#define AASRC_GROUP0                            (0U)
#define AASRC_GROUP1                            (1U)
#define AASRC_GROUP2                            (2U)
#define AASRC_GROUP3                            (3U)
/** @} */

/**
 *  \anchor AASRC_DataLength
 *  \name AASRC Data Length
 *
 *  AASRC allowed sample word length
 *
 *  @{
 */
#define AASRC_SAMPLE_WORD_LENGTH_24             (24U)
#define AASRC_SAMPLE_WORD_LENGTH_20             (20U)
#define AASRC_SAMPLE_WORD_LENGTH_18             (18U)
#define AASRC_SAMPLE_WORD_LENGTH_16             (16U)
/** @} */

/**
 *  \anchor AASRC_GroupDelay
 *  \name AASRC Group Delay
 *
 * Interpolation filter group delay supported by AASRC. This represents
 * the number of samples which are prebuffered prior to the re-sampler
 * function.
 *  @{
 */
#define AASRC_GROUP_DELAY_64                    (64U)
#define AASRC_GROUP_DELAY_32                    (32U)
#define AASRC_GROUP_DELAY_16                    (16U)
#define AASRC_GROUP_DELAY_8                     (8U)
/** @} */

/** \brief AASRC maximum attenuation setting */
#define AASRC_MAX_ATTENUATION                   (255U)

/** \brief AASRC maximum number of de-emphasis modes */
#define AASRC_MAX_DEEMPHASIS_MODES              (4U)

/** \brief SRC Fifo control register offset */
#define AASRC_SRC_FIFO_CONTROL_REG_OFFSET   (0x00000010U)
/** \brief Find base address of SRC 'x' Fifo Control Register */
#define AASRC_SRC_FIFO_CONTROL(x)           ((uint32_t) CSL_AASRC_CFG_SRC_FIFO_CONTROL_0 + \
                                            (uint32_t) ((uint32_t) AASRC_SRC_FIFO_CONTROL_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief SRC control register offset */
#define AASRC_SRC_CONTROL_REG_OFFSET        (0x00000010U)
/** \brief Find base address of SRC 'x' Control Register */
#define AASRC_SRC_CONTROL(x)                ((uint32_t) CSL_AASRC_CFG_SRC_CONTROL_0 + \
                                            (uint32_t) ((uint32_t) AASRC_SRC_CONTROL_REG_OFFSET * \
                                                        (uint32_t) (x)))
/** \brief SRC status register offset */
#define AASRC_SRC_STATUS_REG_OFFSET         (0x00000010U)
/** \brief Find base address of SRC 'x' Status Register */
#define AASRC_SRC_STATUS(x)                 ((uint32_t) CSL_AASRC_CFG_SRC_STATUS_0 + \
                                            (uint32_t) ((uint32_t) AASRC_SRC_STATUS_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief SRC Group fifo control register offset */
#define AASRC_GROUP_FIFO_CONTROL_REG_OFFSET (0x00000008U)
/** \brief Find base address of Group 'x' Fifo Control Register */
#define AASRC_GROUP_FIFO_CONTROL(x)         ((uint32_t) CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0 + \
                                            (uint32_t) ((uint32_t) AASRC_GROUP_FIFO_CONTROL_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief SRC Group control register offset */
#define AASRC_GROUP_SRC_CONTROL_REG_OFFSET  (0x00000008U)
/** \brief Find base address of Group 'x' Control Register */
#define AASRC_GROUP_SRC_CONTROL(x)          ((uint32_t) CSL_AASRC_CFG_GROUP_SRC_CONTROL_0 + \
                                            (uint32_t) ((uint32_t) AASRC_GROUP_SRC_CONTROL_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief SRC Group select register offset */
#define AASRC_GROUP_SELECT_REG_OFFSET       (0x00000004U)
/** \brief Find base address of Input Group 'x' Select Register */
#define AASRC_INPUT_GROUP_SELECT(x)         ((uint32_t) CSL_AASRC_CFG_INPUT_GROUP_0_SELECT + \
                                            (uint32_t) ((uint32_t) AASRC_GROUP_SELECT_REG_OFFSET * \
                                                        (uint32_t) (x)))
/** \brief Find base address of Output Group 'x' Select Register */
#define AASRC_OUTPUT_GROUP_SELECT(x)        ((uint32_t) CSL_AASRC_CFG_OUTPUT_GROUP_0_SELECT + \
                                            (uint32_t) ((uint32_t) AASRC_GROUP_SELECT_REG_OFFSET * \
                                                        (uint32_t) (x)))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief AASRC Channel lock semaphore structure
 */
typedef struct
{
    void *lock;
    /**< Lock to protect AASRC channel open*/
    SemaphoreP_Object lockObj;
    /**< Lock object */
} AASRC_ChLockObj;

/**
 *  \brief Hardware FIFO setup structure
 */
typedef struct
{
    uint32_t                inFifoThreshold;
    /**<  Number of spaces in the input fifo, that must be available for the
    *     interrupt/event to fire */
    uint32_t                outFifoThreshold;
    /**<  Number of samples that must be available in the output fifo for the
     *    interrupt/event to fire */
} AASRC_FifoCfg;

/**
 *  \brief Hardware FIFO setup structure
 */
typedef struct
{
    uint8_t                 lChannelOverflow;
    /**<  left channel fifo overflow  */
    uint8_t                 rChannelOverflow;
    /**<  right channel fifo overflow  */
    uint8_t                 lChannelUnderflow;
    /**<  left channel fifo underflow  */
    uint8_t                 rChannelUnderflow;
    /**<  right channel fifo underflow  */
} AASRC_FifoErrorStatus;

/**
 *  \brief AASRC channel status register
 */
typedef struct
{
    uint32_t                rateRatio;
    /**<  input to output sampling ratio for the channel */
    uint32_t                upsample;
    /**<  set to 1 when the output sampeling rate is greater than
     *    input sampling rate  */
} AASRC_ChStatus;

/**
 *  \brief AASRC configuration parameters for the channel
 *
 *  AASRC channel parameters used with the #AASRC_chConfig() call.
 *  Default values for these parameters are set using AASRC_chConfigInit().
 *
 *  If NULL is passed for the parameters, #AASRC_chConfig() uses default
 *  parameters.
 *
 *  \sa #AASRC_chConfigInit()
 */
typedef struct
{
    /*
     * Primary user configs
     */
    uint32_t                chType;
    /**< Channel type. Refer \ref AASRC_ChTypes */
    uint32_t                chCount;
    /**< Channel count in a synchronized group  */

    /*
     * Secondary user configs
     */
    AASRC_FifoCfg           fifoControl;
    /**< Threshold configuration for input/output fifos of the channel */
    uint8_t                inClkZone;
    /**< Clock zone index for the input of the channel */
    uint8_t                outClkZone;
    /**< Clock zone index for the output of the channel */
    uint32_t                inWordLen;
    /**< Input sample word length - 24/20/18/16 bits */
    uint32_t                ditherEnable;
    /**< Enable dithering */
    uint32_t                mute;
    /**< Enable/disable ASRC output soft mute */
    uint32_t                directDownSample;
    /**< Selects the mode of the decimation function, either true decimation
     *   filter or direct down sampling without filtering */
    uint32_t                attenuation;
    /**< set the ASRC channel's digital output attenuation */
    uint32_t                deEmphasisMode;
    /**< Enable/disable digital de-emphasis filter manually */
    uint32_t                groupDelay;
    /**< Select the interpolation filter group delay */
    uint32_t                outWordLen;
    /**< Output sample word length - 24/20/18/16 bits. If outWordLen < inWordLen
     *   The word length reduction is performed by utilizing triangular PDF
     *   dithering. */
} AASRC_ChCfg;

/**
 *  \brief Hardware setup clock zones
 */

typedef struct
{
    uint32_t clkZoneDiv;
    /**< Clock Zone divider value */
    bool isClkZoneDivEnable;
    /**< is clock zone divider enabled */
    uint8_t syncPin;
    /**< Configures RX/TX sync pin to extClkSrc */
    uint32_t extClkSrc;
    /**< External CLK (TX/RX) source,
     *  Refer: \ref AASRC_RxSyncClkSources or \ref AASRC_TxSyncClkSources */
    bool overrideClkSettle;
    /**< Flag to override clkSettle */
} AASRC_ClockZoneConfig;


/**
 *  \brief AASRC Channel Clock Config
 */

 typedef struct
 {
     AASRC_ClockZoneConfig   rxClkZoneCfg;
     /**< rx clock zone config */
     AASRC_ClockZoneConfig   txClkZoneCfg;
     /**< tx clock zone config */
 } AASRC_ChClkCfg;


/**
 *  \brief AASRC Channel object
 */
typedef struct
{
    /*
     * Linker variables
     */
    AASRC_Handle            drvHandle;
    /**< Pointer to driver handle. */

    /*
     * State variables
     */
    bool                    isOpen;
    /**< Flag to indicate if the asrc channel is already open */
    AASRC_ChState           *chState;
    /**< Pointer to the global private structure holding channel state*/
    /*   User MUST not change this!*/

    /*
     * Channel Configuration variables
     */
    AASRC_ChCfg             chCfg;


    /**< Channel configs */

    AASRC_DmaChCfg          *dmaChCfg;
    /**< Channel dma configs, valid only in AASRC_TRANSFER_MODE_DMA */

    /*
     * Data transfer variables
     */
    AASRC_TransferObj       rcvObj;
    /**< Holds receive channel to the AASRC. */
    AASRC_TransferObj       xmtObj;
    /**< Holds transmit channel from AASRC. */
    /*
     * lock semaphore Obj
     */
    SemaphoreP_Object       transferSemObj;
    /**< Transfer Sync Semaphore object */
    /*
     * Data holding queues
     */
    QueueP_Object           reqQueueObjRx;
    /**< Queue Objs to store the application buffers for AASRC input >*/
    QueueP_Object           reqQueueObjTx;
    /**< Queue Objs to store the application buffers for AASRC output >*/
    QueueP_Handle           reqQueueHandleRx;
    /**< Queue handle used for storing the application buffers for AASRC input>*/
    QueueP_Handle           reqQueueHandleTx;
    /**< Queue handle used for storing the application buffers for AASRC output >*/

    /*
     * Status variables
     */
    AASRC_ChStatus          chStatus;
    /**< Rare ratio and upsample indicator status */
    AASRC_FifoErrorStatus   inFifoErrorStatus;
    /**< Reports infifo error status */
    AASRC_FifoErrorStatus   outFifoErrorStatus;
    /**< Reports outfifo error status */

    /*
     * Error call back function
     */
    AASRC_ChErrorCallbackFxn errCbFxn;
    /**< callback function provided by the app to be called by DMA or Host
     * in case of a channel error situation. If this was set to NULL
     * by the user, driver will try to recover from the error itself
     * but there will be gaps or errornous samples in the output. */

     uint32_t lastPlayed;
     /**< Last played ring element index */
     uint32_t lastFilled;
     /**< Last filled ring element index int TX */
     uint32_t lastReceived;
     /**< Last received ring element index */
     uint32_t lastRecQueued;
     /**< Last receive txn queued index */

     AASRC_DmaIcnt txDmaIcnt;
     /**< DMA Icnt values for Tx */
     AASRC_DmaIcnt rxDmaIcnt;
     /**< DMA Icnt values for Rx */

} AASRC_ChObj;

/** \brief Externally defined driver configuration array */
extern AASRC_ChObj *gConfigAasrcChObj[];

/** \brief AASRC Channel lock object */
AASRC_ChLockObj gAasrcChLockObj;

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to allocate a required ASRC channel
 *
 *  Opens an ASRC channel requested by the user. The channel types could be
 *  mono, stereo or a synchronized group of mono channels. This function
 *  takes care of the hardware resource allocation for opening a channel.
 *
 *  \param chIdx                 [IN] Index of channel config to use in the *AASRC Channel Config* array
 *  \param drvHandle             #AASRC_Handle returned from #AASRC_open()
 *
 *  \return channel handle. Returns NULL for errornous params or resource unavailability
 */
AASRC_ChHandle AASRC_chOpen(uint8_t chIdx, AASRC_Handle drvHandle);

/**
 *  \brief  This function returns the handle of an open AASRC Channel from the
 *          instance index & channel index
 *
 *  \param instIdx               [IN] Index of instance config to use in the *AASRC Driver Config* array
 *  \param chIdx                 [IN] Index of channel config to use in the *AASRC Channel Config* array

 *
 *  \return channel handle. Returns NULL for errornous params or resource unavailability
 */
AASRC_ChHandle AASRC_getChHandle(uint8_t instIdx, uint8_t chIdx);

/**
 *  \brief Function initialize AASRC_ChCfg
 *
 *  initializes the AASRC_ChCfg structure to its default values
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_chConfigInit(AASRC_ChHandle chHandle);

/**
 *  \brief Function to configure ASRC channels
 *
 *  This configures an ASRC channel or a group of ASRC channels
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_chConfig(AASRC_ChHandle chHandle);

/**
 *  \brief AASRC channel enable
 *
 *  This function enables the given ASRC channel via the chHandle. This is like
 *  getting the ASRC channels and data path out of reset.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_chEnable(AASRC_ChHandle chHandle);

/**
 *  \brief AASRC channel disable
 *
 *  This function dsiables the given ASRC channel via the chHandle.
 *  Channel disable is like a reset. It clears the datapath for the ASRC channel
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_chDisable(AASRC_ChHandle chHandle);

/**
 *  \brief is ASRC channel enabled
 *
 *  This function checks if a given ASRC channel via the chHandle is enabled or not.
 *  This setting is directly read from the hardware.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *  \param isEnabled                 [IN] set to 1 if the channel is enabled and
 *                                       0 if it is not
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_isChEnabled(AASRC_ChHandle chHandle, uint32_t *isEnabled);

/**
 *  \brief AASRC channel close
 *
 *  closes the asrc channel pointed by the chHandle and frees the hardware
 *  resources for another AASRC_chOpen() call
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_chClose(AASRC_ChHandle chHandle);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */



#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_CH_H_ */

/** @} */
