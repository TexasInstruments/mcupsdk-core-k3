/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /**
 *  \file audio_player.c
 *
 *  \brief An example code which uses MCASP driver to play audio from SD card
 *         using TLV320AIC31 codec. The audio data from SD card is read into a
 *         circular buffer and then played. The audio from microphone can also
 *         be captured and played back. The mode can be switched using a GPIO.
 *         Makes use of McASP, UDMA, MMCSD, GPIO, UART, I2C drivers.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>

#include <drivers/i2c.h>
#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/hw_include/am62ax/cslr_intr_gicss0_common_0.h>
#include <drivers/hw_include/am62ax/cslr_intr_main_gpiomux_introuter0.h>
#include <drivers/sciclient.h>

#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ff_stdio.h"
#include "circular_buffer.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT  (4U)
#define APP_MCASP_AUDIO_BUFF_SIZE   (2048U)

#define MAX_WAV_FILES 10

#define GPIOMUX_INTROUTER_OUTP_0 (0U)

#define APP_UART_TX_BUFSIZE 128
#define APP_UART_RX_BUFSIZE 32

#define AUDIO_PLAYER_MODE_MIC   (0U)
#define AUDIO_PLAYER_MODE_SD    (1U)
#define AUDIO_PLAYER_MODE_MIX   (2U)
#define AUDIO_PLAYER_MODE_MAX   (3U)

#define AUDIO_PLAYER_CMD_NEXT    (0x23)
#define AUDIO_PLAYER_CMD_MIX     (0x24)

/**
 * @struct WAVHeader
 * @brief Represents the header of a WAV audio file.
 *
 * This structure contains the standard fields found in the header of a WAV file,
 * including chunk identifiers, format information, and audio data properties.
 *
 * @var WAVHeader::chunkID
 *   The RIFF chunk descriptor, should contain "RIFF".
 * @var WAVHeader::chunkSize
 *   The size of the overall file in bytes minus 8 bytes for the two fields not included in this count.
 * @var WAVHeader::format
 *   The format, should contain "WAVE".
 * @var WAVHeader::subchunk1ID
 *   The subchunk1 ID, should contain "fmt ".
 * @var WAVHeader::subchunk1Size
 *   The size of the subchunk1 (usually 16 for PCM).
 * @var WAVHeader::audioFormat
 *   The audio format code (1 for PCM).
 * @var WAVHeader::numChannels
 *   The number of audio channels (1 for mono, 2 for stereo).
 * @var WAVHeader::sampleRate
 *   The sample rate (e.g., 44100 Hz).
 * @var WAVHeader::byteRate
 *   The byte rate = SampleRate * NumChannels * BitsPerSample/8.
 * @var WAVHeader::blockAlign
 *   The block align = NumChannels * BitsPerSample/8.
 * @var WAVHeader::bitsPerSample
 *   The number of bits per sample (e.g., 16).
 * @var WAVHeader::subchunk2ID
 *   The subchunk2 ID, should contain "data".
 * @var WAVHeader::subchunk2Size
 *   The size of the audio data in bytes.
 */
typedef struct {
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2ID[4];
    uint32_t subchunk2Size;
} WAVHeader;

/**
 * @struct WAVFileDetails
 * @brief Stores metadata and properties of a WAV audio file.
 *
 * This structure is used to keep track of file-specific details such as
 * filename, audio format properties, and file size.
 *
 * @var WAVFileDetails::fileName
 *   The name of the WAV file.
 * @var WAVFileDetails::sampleRate
 *   The sample rate of the audio data.
 * @var WAVFileDetails::numChannels
 *   The number of audio channels.
 * @var WAVFileDetails::bitsPerSample
 *   The number of bits per audio sample.
 * @var WAVFileDetails::chunkSize
 *   The size of the main chunk in the WAV file.
 * @var WAVFileDetails::fileSize
 *   The total size of the WAV file in bytes.
 */
typedef struct {
    char fileName[64];
    uint32_t sampleRate;
    uint16_t numChannels;
    uint16_t bitsPerSample;
    uint32_t chunkSize;
    uint32_t fileSize;
} WAVFileDetails;

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create buffers for transmit and Receive in McASP */
static uint8_t AudioPlayer_TxBuf[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));
static uint8_t AudioPlayer_RxBuf[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));

/* Create transaction objects for transmit and Receive */
static MCASP_Transaction   AudioPlayer_McaspTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
static MCASP_Transaction   AudioPlayer_McaspTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

/* Structure array to store wave file details from SD card */
static WAVFileDetails AudioPlayer_WaveFileDetails[MAX_WAV_FILES];

/* Circular buffer for storing audio data from SD card */
static uint8_t AudioPlayer_CircBufStorage[8192] __attribute__((aligned(256))); /* 8KB ring for audio data */
static CircularBuffer AudioPlayer_CircBuf;

/* Audio buffers to read from SD card and microphone */
static uint32_t  AudioPlayer_SdAudioBuf[APP_MCASP_AUDIO_BUFF_SIZE/4];
static uint32_t  AudioPlayer_MicAudioBuf[APP_MCASP_AUDIO_BUFF_SIZE/4];
static uint8_t  AudioPlayer_TempAudioBuf[APP_MCASP_AUDIO_BUFF_SIZE];

/* UART TX and RX buffers */
static uint8_t AudioPlayer_UartTxBuf[APP_UART_TX_BUFSIZE];
static uint8_t AudioPlayer_UartRespBuf[APP_UART_RX_BUFSIZE];
static uint32_t AudioPlayer_UartRespBufIdx = 0;

/* UART task stack memory */
static uint8_t uartTaskStackMemory[8*1024];

/* GPIO interrupt pin base address */
static uint32_t  Gpio_BaseAddr = GPIO_PUSH_BUTTON_BASE_ADDR;

/* HW  object needed to register GPIO interrupt */
static HwiP_Object  Gpio_HwiObject;

/* Audio player variables */
static volatile uint32_t AudioPlayer_Mode = AUDIO_PLAYER_MODE_MIC;
static volatile uint32_t AudioPlayer_MixRatio = 5;
static uint32_t AudioPlayer_Command = 0;

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */

/* List all .wav files in the given directory (partition root or subdirectory) */
static uint32_t getWaveFileDetails(const char *directory, WAVFileDetails *wavFiles, uint32_t maxFiles);
/* Callback to handle the mode switch changes */
static void modeSwitchCallback(void *args);
/* Function to setup the mode switch */
static void modeSwitchSetup(void);
/* Function to deinitialize the mode switch */
static void modeSwitchDeinit(void);
/* Function to read response from UART */
static uint32_t readResponse(void);
/* UART task function */
static void uartHandlerTask(void *arg);

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
/* Configure codec TLV320AIC31 */
int32_t Board_codecConfig(void);

/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */
/**
 * @brief Main entry point for the audio player application.
 *
 * Initializes peripherals, sets up buffers, reads WAV files from SD card,
 * and manages audio playback and mode switching.
 *
 * @param args Not used.
 */
void audioPlayer_main(void *args)
{
    int32_t         status = SystemP_SUCCESS;
    uint32_t        i, idx = 0;
    uint32_t        newFile;
    size_t          readSize;
    MCASP_Handle    mcaspHandle;
    uint32_t        numWavFiles = 0;
    uint32_t        sdBufSize = APP_MCASP_AUDIO_BUFF_SIZE;
    uint32_t        bitsPerSample = 16;

    /* Create UART thread */
    TaskP_Object uartTaskObj;
    TaskP_Params uartTaskParams;

    FF_MMCSD_PartitionDetails partDetails;
    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];
    FF_FILE *fp = NULL;

    TaskP_Params_init(&uartTaskParams);
    uartTaskParams.name = "UartTask";
    uartTaskParams.stackSize = 2048;
    uartTaskParams.priority = 2;
    uartTaskParams.taskMain = uartHandlerTask;
    uartTaskParams.args = NULL;
    uartTaskParams.stack     = uartTaskStackMemory;

    TaskP_construct(&uartTaskObj, &uartTaskParams);

    /* Init circular buffer */
    CircBuf_Init(&AudioPlayer_CircBuf, AudioPlayer_CircBufStorage, sizeof(AudioPlayer_CircBufStorage));

    memset(&partDetails, 0, sizeof(FF_MMCSD_PartitionDetails));

    modeSwitchSetup();

    /* Check partition*/
    FF_MMCSDGetPartitionDetails(pDisk, &partDetails);

    if (partDetails.sectorCount != 0U)
    {
        /* Mount partition */
        FF_MMCSDMountPartition(pDisk, "/sd0");

        numWavFiles = getWaveFileDetails("/sd0/", AudioPlayer_WaveFileDetails, MAX_WAV_FILES);

        for (i = 0; i < numWavFiles; i++)
        {
            DebugP_log("WAV File: %s, Sample Rate: %d Hz, Channels: %d, BitsPerSample: %d, Chunk Size: %d File Size: %d\r\n",
                        AudioPlayer_WaveFileDetails[i].fileName,
                        AudioPlayer_WaveFileDetails[i].sampleRate,
                        AudioPlayer_WaveFileDetails[i].numChannels,
                        AudioPlayer_WaveFileDetails[i].bitsPerSample,
                        AudioPlayer_WaveFileDetails[i].chunkSize,
                        AudioPlayer_WaveFileDetails[i].fileSize);
        }
    }

    Board_codecConfig();

    DebugP_log("Audio player started\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    CacheP_wb(AudioPlayer_TxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);
    CacheP_wb(AudioPlayer_RxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);

    /* Prepare and submit audio transaction transmit objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        AudioPlayer_McaspTxnTx[i].buf = (void*) &AudioPlayer_TxBuf[i][0];
        AudioPlayer_McaspTxnTx[i].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        AudioPlayer_McaspTxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &AudioPlayer_McaspTxnTx[i]);
    }

    /* Prepare and submit audio transaction receive objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        AudioPlayer_McaspTxnRx[i].buf = (void*) &AudioPlayer_RxBuf[i][0];
        AudioPlayer_McaspTxnRx[i].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        AudioPlayer_McaspTxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(mcaspHandle, &AudioPlayer_McaspTxnRx[i]);
    }

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    idx = 0;
    newFile = 1;

    /* Main audio loop: handles file reading, buffer management, and transaction recycling */
    while(numWavFiles > 0)
    {
        if (AudioPlayer_Command == AUDIO_PLAYER_CMD_NEXT)
        {
            AudioPlayer_Command = 0;
            newFile = 1;

            if (fp != NULL)
            {
                ff_fclose(fp);
                fp = NULL;
            }
        }

        if (newFile == 1)
        {
            DebugP_log("New file - %s\r\n", AudioPlayer_WaveFileDetails[idx].fileName);
            newFile = 0;

            fp = ff_fopen(AudioPlayer_WaveFileDetails[idx].fileName, "r");

            /* Skip wave header (WAV PCM data starts after header) */
            ff_fseek(fp, sizeof(WAVHeader), FF_SEEK_SET);

            if (AudioPlayer_WaveFileDetails[idx].bitsPerSample == 32)
            {
                sdBufSize = APP_MCASP_AUDIO_BUFF_SIZE;
                bitsPerSample = 32;
            }
            else if (AudioPlayer_WaveFileDetails[idx].bitsPerSample == 16)
            {
                sdBufSize = APP_MCASP_AUDIO_BUFF_SIZE/2;
                bitsPerSample = 16;
            }
            else
            {
                /* Only supports 16 and 32 bits per sample. Skip to next file  */
                DebugP_log("Unsupported bits per sample: %d\r\n", AudioPlayer_WaveFileDetails[idx].bitsPerSample);
                newFile = 1;
            }

            idx++;
            if (idx >= numWavFiles)
            {
                idx = 0;
            }

            if (newFile == 1)
            {
                ff_fclose(fp);
                fp = NULL;
                continue;
            }
        }

        /* Only read from SD if there is enough space in the circular buffer */
        if (CircBuf_Space(&AudioPlayer_CircBuf) > APP_MCASP_AUDIO_BUFF_SIZE)
        {
            readSize = ff_fread(AudioPlayer_TempAudioBuf, 1, sdBufSize, fp);

            if (readSize < sdBufSize)
            {
                /* End of file: move to next WAV file in list (loop if needed) */
                DebugP_log("Next file\r\n");
                ff_fclose(fp);
                fp = NULL;
                newFile = 1;
            }
            else
            {
                size_t written;

                if (bitsPerSample == 16)
                {
                    /* If 16-bit audio, need to convert to 32-bit for McASP */
                    uint16_t *src = (uint16_t *)AudioPlayer_TempAudioBuf;

                    for (i=0;i<(sdBufSize/2);i++)
                    {
                        AudioPlayer_SdAudioBuf[i] = src[i] << 16;
                    }

                    /* Write new audio data into circular buffer */
                    written = CircBuf_Write(&AudioPlayer_CircBuf, (uint8_t*)(AudioPlayer_SdAudioBuf), APP_MCASP_AUDIO_BUFF_SIZE);
                }
                else
                {
                    /* Write new audio data into circular buffer */
                    written = CircBuf_Write(&AudioPlayer_CircBuf, AudioPlayer_TempAudioBuf, readSize);
                }

                /* Check for overflow */
                if (written < readSize)
                {
                    /* This should not happen due to space check, but is a safety net */
                    DebugP_logWarn("[A53] Audio circular buffer overflow, written %d of %d bytes\r\n", (int)written, (int)readSize);
                }
            }
        }

        /* Sleep to yield CPU and allow ISR-driven callbacks to run */
        ClockP_usleep(1000);
    }

    modeSwitchDeinit();
}

/**
 * @brief McASP transmit callback.
 *
 * Called when a transmit transaction completes. Puts the transaction back into the Tx FIFO.
 *
 * @param handle McASP handle
 * @param transaction Pointer to completed transaction
 */
void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t i;

    /* Invalidate cache before writing to DMA buffer */
    CacheP_inv(AudioPlayer_TxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);

    if (AudioPlayer_Mode == AUDIO_PLAYER_MODE_MIC)
    {
        /* In MIC mode, play back captured microphone data */
        memcpy((uint8_t *)transaction->buf, (uint8_t *)AudioPlayer_MicAudioBuf, APP_MCASP_AUDIO_BUFF_SIZE);
    }
    else if (AudioPlayer_Mode == AUDIO_PLAYER_MODE_SD)
    {
        /* In SD mode, play back data from SD card */
        CircBuf_Read(&AudioPlayer_CircBuf, (uint8_t *)transaction->buf, APP_MCASP_AUDIO_BUFF_SIZE);
    }
    else
    {
        /* In MIX mode, mix microphone and SD card audio */
        CircBuf_Read(&AudioPlayer_CircBuf, (uint8_t *)AudioPlayer_SdAudioBuf, APP_MCASP_AUDIO_BUFF_SIZE);

        int32_t *dst = (int32_t *)transaction->buf;

        for(i=0;i<transaction->count;i++)
        {
            dst[i] = AudioPlayer_SdAudioBuf[i] + AudioPlayer_MicAudioBuf[i];
        }
    }

    /* Writeback cache after filling buffer */
    CacheP_wb(AudioPlayer_TxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);

    MCASP_submitTx(handle, transaction);
}

/**
 * @brief McASP receive callback.
 *
 * Called when a receive transaction completes. Puts the transaction back into the Rx FIFO.
 *
 * @param handle McASP handle
 * @param transaction Pointer to completed transaction
 */
void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    /* Invalidate cache before reading from DMA buffer */
    CacheP_inv(AudioPlayer_RxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);

    memcpy((uint8_t *)AudioPlayer_MicAudioBuf, (uint8_t *)transaction->buf, APP_MCASP_AUDIO_BUFF_SIZE);

    /* Writeback cache after copying */
    CacheP_wb(AudioPlayer_RxBuf, APP_MCASP_AUDIO_BUFF_COUNT * APP_MCASP_AUDIO_BUFF_SIZE, CacheP_TYPE_ALL);

    MCASP_submitRx(handle, transaction);
}

/* ========================================================================== */
/*                        Static Function Definition                          */
/* ========================================================================== */

/**
 * @brief List all .wav files in the given directory and extract their details.
 *
 * @param directory Directory path to search
 * @param wavFiles Array to store file details
 * @param maxFiles Maximum number of files to store
 * @return Number of WAV files found
 */
static uint32_t getWaveFileDetails(const char *directory, WAVFileDetails *wavFiles, uint32_t maxFiles)
{
    FF_FindData_t findData;
    uint32_t res = ff_findfirst(directory, &findData);
    uint32_t idx = 0;
    FF_FILE *fp = NULL;
    WAVHeader header;
    char fileName[64];

    if (res == 0)
    {
        do
        {
            if (!(findData.ucAttributes & FF_FA_DIREC))
            {
                const char *fname = findData.pcFileName;
                size_t len = strlen(fname);
                if (len > 4 &&
                    (fname[len-4] == '.' || fname[len-4] == '.') &&
                    (fname[len-3] == 'w' || fname[len-3] == 'W') &&
                    (fname[len-2] == 'a' || fname[len-2] == 'A') &&
                    (fname[len-1] == 'v' || fname[len-1] == 'V'))
                {
                    if (idx >= maxFiles)
                    {
                        DebugP_log("[A53] Maximum WAV file limit reached (%d). Some files may not be listed.\r\n", maxFiles);
                        break;
                    }

                    fileName[0] = '\0';
                    strcat(fileName, directory);
                    strcat(fileName, fname);

                    /* Open file for reading */
                    fp = ff_fopen(fileName, "r");

                    if (ff_fread(&header, sizeof(WAVHeader), 1, fp) != 1)
                    {
                        DebugP_logWarn("[A53] Failed to read wav header\r\n");
                    } else
                    {
                        strcpy(wavFiles[idx].fileName, fileName);
                        wavFiles[idx].sampleRate = header.sampleRate;
                        wavFiles[idx].numChannels = header.numChannels;
                        wavFiles[idx].bitsPerSample = header.bitsPerSample;
                        wavFiles[idx].chunkSize = header.subchunk2Size;
                        wavFiles[idx].fileSize = findData.ulFileSize;
                        idx++;
                    }

                    ff_fclose(fp);
                }
            }
        } while (ff_findnext(&findData) == 0);
    }
    else
    {
        DebugP_logWarn("[A53] No files found or error in directory: %s\r\n", directory);
    }

    return idx;
}

/**
 * @brief GPIO interrupt callback for mode switch.
 *
 * @param args Pin number (cast to void*)
 */
static void modeSwitchCallback(void *args)
{
    uint32_t    pinNum = (uint32_t) args;
    uint32_t    bankNum =  GPIO_GET_BANK_INDEX(pinNum);
    uint32_t    intrStatus, pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Address translate */
    Gpio_BaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(Gpio_BaseAddr);

    /* Get and clear bank interrupt status */
    intrStatus = GPIO_getBankIntrStatus(Gpio_BaseAddr, bankNum);
    GPIO_clearBankIntrStatus(Gpio_BaseAddr, bankNum, intrStatus);

    /* Per pin interrupt handling */
    if(intrStatus & pinMask)
    {
        AudioPlayer_Mode++;

        if (AudioPlayer_Mode >= AUDIO_PLAYER_MODE_MAX)
        {
            AudioPlayer_Mode = AUDIO_PLAYER_MODE_MIC;
        }
    }
}

/**
 * @brief Setup GPIO and interrupt for mode switch button.
 */
static void modeSwitchSetup(void)
{
    int32_t                             retVal;
    struct tisci_msg_rm_irq_set_req     rmIrqReq;
    struct tisci_msg_rm_irq_set_resp    rmIrqResp;
    uint32_t        pinNum, intrNum;
    uint16_t        eventId = HWIP_INVALID_EVENT_ID;
    uint32_t        bankNum;
    HwiP_Params     hwiPrms;

    rmIrqReq.valid_params           = 0U;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_ID_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
    rmIrqReq.global_event           = 0U;
    rmIrqReq.src_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.src_index              = CSLR_MAIN_GPIOMUX_INTROUTER0_IN_GPIO1_GPIO_BANK_1;
    rmIrqReq.dst_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP_0;
    rmIrqReq.ia_id                  = 0U;
    rmIrqReq.vint                   = 0U;
    rmIrqReq.vint_status_bit_index  = 0U;
    rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;

    retVal = Sciclient_rmIrqSetRaw(&rmIrqReq, &rmIrqResp, SystemP_WAIT_FOREVER);
    if(0 != retVal)
    {
        DebugP_log("[Error] Sciclient event config failed!!!\r\n");
        DebugP_assert(FALSE);
    }

    pinNum          = GPIO_PUSH_BUTTON_PIN;
    intrNum         = CSLR_GICSS0_COMMON_0_SPI_MAIN_GPIOMUX_INTROUTER0_OUTP_0;
    bankNum         = GPIO_GET_BANK_INDEX(pinNum);

    /* Address translate */
    Gpio_BaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(Gpio_BaseAddr);

    /* Setup GPIO for interrupt generation */
    GPIO_setDirMode(Gpio_BaseAddr, pinNum, GPIO_PUSH_BUTTON_DIR);
    GPIO_setTrigType(Gpio_BaseAddr, pinNum, GPIO_PUSH_BUTTON_TRIG_TYPE);
    GPIO_bankIntrEnable(Gpio_BaseAddr, bankNum);

    /* Register pin interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = intrNum;
    hwiPrms.eventId   = eventId;
    hwiPrms.isPulse = 1;
    hwiPrms.callback = &modeSwitchCallback;
    hwiPrms.args     = (void *) pinNum;

    retVal = HwiP_construct(&Gpio_HwiObject, &hwiPrms);
    DebugP_assert(retVal == SystemP_SUCCESS );
}

/**
 * @brief Deinitialize mode switch GPIO and interrupt.
 */
static void modeSwitchDeinit(void)
{
    int32_t                             retVal;
    struct tisci_msg_rm_irq_release_req rmIrqReq;
    uint32_t        pinNum, intrNum;
    uint32_t        bankNum;

    pinNum          = GPIO_PUSH_BUTTON_PIN;
    intrNum         = CSLR_GICSS0_COMMON_0_SPI_MAIN_GPIOMUX_INTROUTER0_OUTP_0;
    bankNum         = GPIO_GET_BANK_INDEX(pinNum);

    GPIO_bankIntrDisable(Gpio_BaseAddr, bankNum);
    GPIO_setTrigType(Gpio_BaseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_clearIntrStatus(Gpio_BaseAddr, pinNum);
    HwiP_destruct(&Gpio_HwiObject);

    rmIrqReq.valid_params           = 0U;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_ID_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
    rmIrqReq.global_event           = 0U;
    rmIrqReq.src_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.src_index              = CSLR_MAIN_GPIOMUX_INTROUTER0_IN_GPIO1_GPIO_BANK_1;
    rmIrqReq.dst_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP_0;
    rmIrqReq.ia_id                  = 0U;
    rmIrqReq.vint                   = 0U;
    rmIrqReq.vint_status_bit_index  = 0U;
    rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;

    retVal = Sciclient_rmIrqReleaseRaw(&rmIrqReq, SystemP_WAIT_FOREVER);
    if(0 != retVal)
    {
        DebugP_log("[Error] Sciclient event reset failed!!!\r\n");
        DebugP_assert(FALSE);
    }
}

/**
 * @brief Read a response from UART into the response buffer.
 *
 * @return 1 if a complete response was read, 0 otherwise
 */
static uint32_t readResponse(void)
{
    uint8_t temp;
    uint32_t status;
    uint32_t retVal = 0;

    status = UART_getChar(CSL_MCU_UART0_BASE, &temp);

    if (status)
    {
        UART_putChar(CSL_MCU_UART0_BASE, temp);

        if (temp == '\r' || temp == '\n' || AudioPlayer_UartRespBufIdx >= (APP_UART_RX_BUFSIZE - 1))
        {
            AudioPlayer_UartRespBuf[AudioPlayer_UartRespBufIdx] = '\0';
            retVal  = 1;
        }
        else
        {
            AudioPlayer_UartRespBuf[AudioPlayer_UartRespBufIdx++] = temp;
        }
    }

    return retVal;
}

/**
 * @brief UART handler task for echo and mode change notification.
 *
 * @param arg Not used.
 */
static void uartHandlerTask(void *arg)
{
    int32_t          transferOK;
    UART_Transaction trans;
    uint32_t  previousMode = AudioPlayer_Mode;
    UART_Transaction_init(&trans);

    trans.buf   = &AudioPlayer_UartTxBuf[0U];
    strncpy(trans.buf,"Use this terminal to send commands to player.\r\n", APP_UART_TX_BUFSIZE);
    trans.count = strlen(trans.buf);
    transferOK = UART_write(gUartHandle[CONFIG_UART0], &trans);
    AudioPlayer_UartRespBufIdx = 0;

    while (1)
    {
        if (readResponse() == 1)
        {
            DebugP_log("Received: %s\r\n", AudioPlayer_UartRespBuf);

            if (AudioPlayer_UartRespBuf[0] == 'm' || AudioPlayer_UartRespBuf[0] == 'M')
            {
                AudioPlayer_MixRatio = AudioPlayer_UartRespBuf[1] - '0'; /* Mix ratio */
                DebugP_log("Mix ratio set to %d\r\n", AudioPlayer_MixRatio);
            }
            else if (AudioPlayer_UartRespBuf[0] == 'n' || AudioPlayer_UartRespBuf[0] == 'N')
            {
                AudioPlayer_Command = AUDIO_PLAYER_CMD_NEXT;
            }
            else
            {
                DebugP_log("Unknown command\r\n");
            }

            AudioPlayer_UartRespBufIdx = 0;
        }

        if (previousMode != AudioPlayer_Mode)
        {
            DebugP_log("Audio Player Mode changed to %d\r\n", AudioPlayer_Mode);
            previousMode = AudioPlayer_Mode;
        }

        ClockP_sleep(1);
    }
}
