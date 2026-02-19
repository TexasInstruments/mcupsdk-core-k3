/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 *  \file test_mcanTestCasesConfig.h
 *
 *  \brief This file defines the test cases for mcan UT.
 */

#ifndef TEST_MCAN_TEST_CASES_CONFIG_H_
#define TEST_MCAN_TEST_CASES_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "test_mcan.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_MCAN_TX_BUFF_START_ADDR              (0x0U)
#define APP_MCAN_TX_BUFF_SIZE                    (16U)
#define APP_MCAN_TX_FIFO_SIZE                    (16U)
#define APP_MCAN_RX_BUFF_START_ADDR              (0x900U)
#define APP_MCAN_FIFO_0_START_ADDR               (0x1B00U)
#define APP_MCAN_FIFO_0_NUM                      (64U)
#define APP_MCAN_FIFO_1_START_ADDR               (0x2D00U)
#define APP_MCAN_FIFO_1_NUM                      (64U)
#define APP_MCAN_TX_EVENT_START_ADDR             (0x3F00U)
#define APP_MCAN_TX_EVENT_SIZE                   (32U)
#define APP_MCAN_STD_ID_FILT_START_ADDR          (0x4000U)
#define APP_MCAN_STD_ID_FILTER_NUM               (128U)
#define APP_MCAN_EXT_ID_FILT_START_ADDR          (0x4200U)
#define APP_MCAN_EXT_ID_FILTER_NUM               (64U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *  \brief Different Bit Timings Parameters Configurations.
 */
MCAN_BitTimingParams canFDBitTimings[] =
{
    /* 1000kbps and 5000 kbps*/
    /* This is default baud*/
    {
        0x07U, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        0x00U  /* Data (Re)Synchronization Jump Width */
    },
    /* 1000kbps and 2500 kbps*/
    {
        0x07U, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x03U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        0x00U  /* Data (Re)Synchronization Jump Width */
    },
    /* 250kbps and 5000 kbps*/
    {
        0x0EU, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        0x00U  /* Data (Re)Synchronization Jump Width */
    },
    /* 125kbps and 5000 kbps*/
    {
        0x1FU, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        0x00U  /* Data (Re)Synchronization Jump Width */
    },
    {
        0x1FU, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        MCAN_NBTP_NSJW_MAX + 1, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        0x00U  /* Data (Re)Synchronization Jump Width */
    },
    {
        0x1FU, /* Nominal Baud Rate Pre-scaler */
        0x05U, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX + 1  /* Data (Re)Synchronization Jump Width */
    },
    {
        0x1FU, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MAX + 1, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    {
        MCAN_NBTP_NBRP_MAX + 1, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MAX, /* Nominal Time segment before sample point */
        MCAN_NBTP_NTSEG2_MAX, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    {
        MCAN_NBTP_NBRP_MAX, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MAX, /* Nominal Time segment before sample point */
        MCAN_NBTP_NTSEG2_MAX, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        MCAN_DBTP_DBRP_MAX + 1, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    {
        MCAN_NBTP_NBRP_MAX, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MAX, /* Nominal Time segment before sample point */
        MCAN_NBTP_NTSEG2_MAX, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        MCAN_DBTP_DBRP_MAX, /* Data Baud Rate Pre-scaler */
        MCAN_DBTP_DTSEG1_MAX + 1, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    {
        MCAN_NBTP_NBRP_MAX, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MAX, /* Nominal Time segment before sample point */
        MCAN_NBTP_NTSEG2_MAX, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        MCAN_DBTP_DBRP_MAX, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        MCAN_DBTP_DTSEG2_MAX + 1, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    {
        0x1FU, /* Nominal Baud Rate Pre-scaler */
        MCAN_NBTP_NTSEG1_MIN - 1U,  /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x00U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x03U, /* Data Time segment before sample point */
        0x02U, /* Data Time segment after sample point */
        MCAN_DBTP_DSJW_MAX  /* Data (Re)Synchronization Jump Width */
    },
    /* Index 12: 1000kbps Nominal (SP=85%) and 5000kbps Data (SP=87.5%) - for external PCAN tests */
    /* Nom: 80MHz / ((3+1) * (1+16+3)) = 80M / (4*20) = 1000kbps, SP = (1+16)/20 = 85% */
    /* Data: 80MHz / ((0+1) * (1+13+2)) = 80M / (1*16) = 5000kbps, SP = (1+13)/16 = 87.5% */
    {
        0x03U, /* Nominal Baud Rate Pre-scaler */
        0x0FU, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x02U, /* Nominal (Re)Synchronization Jump Width */
        0x00U, /* Data Baud Rate Pre-scaler */
        0x0CU, /* Data Time segment before sample point */
        0x01U, /* Data Time segment after sample point */
        0x01U  /* Data (Re)Synchronization Jump Width */
    },
    /* Index 13: 500kbps Nominal (SP=85%) and 2500kbps Data (SP=87.5%) - for external PCAN tests */
    /* Nom: 80MHz / ((7+1) * (1+16+3)) = 80M / (8*20) = 500kbps, SP = (1+16)/20 = 85% */
    /* Data: 80MHz / ((1+1) * (1+13+2)) = 80M / (2*16) = 2500kbps, SP = (1+13)/16 = 87.5% */
    {
        0x07U, /* Nominal Baud Rate Pre-scaler */
        0x0FU, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x02U, /* Nominal (Re)Synchronization Jump Width */
        0x01U, /* Data Baud Rate Pre-scaler */
        0x0CU, /* Data Time segment before sample point */
        0x01U, /* Data Time segment after sample point */
        0x01U  /* Data (Re)Synchronization Jump Width */
    },
    /* Index 14: 250kbps Nominal (SP=85%) and 5000kbps Data (SP=87.5%) - for external PCAN tests */
    /* Nom: 80MHz / ((15+1) * (1+16+3)) = 80M / (16*20) = 250kbps, SP = (1+16)/20 = 85% */
    /* Data: 80MHz / ((0+1) * (1+13+2)) = 80M / (1*16) = 5000kbps, SP = (1+13)/16 = 87.5% */
    {
        0x0FU, /* Nominal Baud Rate Pre-scaler */
        0x0FU, /* Nominal Time segment before sample point */
        0x02U, /* Nominal Time segment after sample point */
        0x02U, /* Nominal (Re)Synchronization Jump Width */
        0x00U, /* Data Baud Rate Pre-scaler */
        0x0CU, /* Data Time segment before sample point */
        0x01U, /* Data Time segment after sample point */
        0x01U  /* Data (Re)Synchronization Jump Width */
    }
};

/**
 *  \brief MCAN Initialization Parameters Configurations.
 */
MCAN_InitParams canFDInitParams[] =
{
    /* Config 0 */
    {
        0x01U, /* FD Operation Enable */
        0x01U, /* Bit Rate Switch Enable */
        0x00U, /* Transmit Pause */
        0x00U, /* FEdge Filtering during Bus Integration */
        0x00U, /* Protocol Exception Handling Disable */
        0x01U, /* Disable Automatic Retransmission */
        0x01U, /* Wakeup Request Enable */
        0x01U, /* Auto-Wakeup Enable */
        0x00U, /* Emulation/Debug Suspend Enable */
        0x00U, /* Emulation/Debug Suspend Fast Ack Enable */
        0x00U, /* Clock Stop Fast Ack Enable */
        0xFFU, /* Start value of the Message RAM Watchdog Counter */
        {
            0x0AU, /* Transmitter Delay Compensation Offset */
            0x06U,  /* Transmitter Delay Compensation Filter Window Length */
        },
        0x01U, /* Transmitter Delay Compensation Enable */
    },
    /* Config 1 */
    {
        0x01U, /* FD Operation Enable */
        0x01U, /* Bit Rate Switch Enable */
        0x00U, /* Transmit Pause */
        0x00U, /* FEdge Filtering during Bus Integration */
        0x00U, /* Protocol Exception Handling Disable */
        0x01U, /* Disable Automatic Retransmission */
        0x01U, /* Wakeup Request Enable */
        0x01U, /* Auto-Wakeup Enable */
        0x00U, /* Emulation/Debug Suspend Enable */
        0x00U, /* Emulation/Debug Suspend Fast Ack Enable */
        0x00U, /* Clock Stop Fast Ack Enable */
        MCAN_RWD_WDC_MAX, /* Start value of the Message RAM Watchdog Counter */
        {
            MCAN_TDCR_TDCF_MAX + 1, /* Transmitter Delay Compensation Offset */
            MCAN_TDCR_TDCO_MAX,  /* Transmitter Delay Compensation Filter Window Length */
        },
        0x01U, /* Transmitter Delay Compensation Enable */
    },
    {
        0x01U, /* FD Operation Enable */
        0x01U, /* Bit Rate Switch Enable */
        0x00U, /* Transmit Pause */
        0x00U, /* FEdge Filtering during Bus Integration */
        0x00U, /* Protocol Exception Handling Disable */
        0x01U, /* Disable Automatic Retransmission */
        0x01U, /* Wakeup Request Enable */
        0x01U, /* Auto-Wakeup Enable */
        0x00U, /* Emulation/Debug Suspend Enable */
        0x00U, /* Emulation/Debug Suspend Fast Ack Enable */
        0x00U, /* Clock Stop Fast Ack Enable */
        MCAN_RWD_WDC_MAX, /* Start value of the Message RAM Watchdog Counter */
        {
            MCAN_TDCR_TDCF_MAX, /* Transmitter Delay Compensation Offset */
            MCAN_TDCR_TDCO_MAX + 1,  /* Transmitter Delay Compensation Filter Window Length */
        },
        0x01U, /* Transmitter Delay Compensation Enable */
    },
    {
        0x01U, /* FD Operation Enable */
        0x01U, /* Bit Rate Switch Enable */
        0x00U, /* Transmit Pause */
        0x00U, /* FEdge Filtering during Bus Integration */
        0x00U, /* Protocol Exception Handling Disable */
        0x01U, /* Disable Automatic Retransmission */
        0x01U, /* Wakeup Request Enable */
        0x01U, /* Auto-Wakeup Enable */
        0x00U, /* Emulation/Debug Suspend Enable */
        0x00U, /* Emulation/Debug Suspend Fast Ack Enable */
        0x00U, /* Clock Stop Fast Ack Enable */
        MCAN_RWD_WDC_MAX + 1, /* Start value of the Message RAM Watchdog Counter */
        {
            MCAN_TDCR_TDCF_MAX, /* Transmitter Delay Compensation Offset */
            MCAN_TDCR_TDCO_MAX,  /* Transmitter Delay Compensation Filter Window Length */
        },
        0x01U, /* Transmitter Delay Compensation Enable */
    },
    /* Config 4 - FD Operation Disabled (for negative testing) */
    {
        0x00U, /* FD Operation Enable - DISABLED */
        0x00U, /* Bit Rate Switch Enable */
        0x00U, /* Transmit Pause */
        0x00U, /* FEdge Filtering during Bus Integration */
        0x00U, /* Protocol Exception Handling Disable */
        0x01U, /* Disable Automatic Retransmission */
        0x01U, /* Wakeup Request Enable */
        0x01U, /* Auto-Wakeup Enable */
        0x00U, /* Emulation/Debug Suspend Enable */
        0x00U, /* Emulation/Debug Suspend Fast Ack Enable */
        0x00U, /* Clock Stop Fast Ack Enable */
        0xFFU, /* Start value of the Message RAM Watchdog Counter */
        {
            0x0AU, /* Transmitter Delay Compensation Offset */
            0x06U,  /* Transmitter Delay Compensation Filter Window Length */
        },
        0x00U, /* Transmitter Delay Compensation Enable */
    },
};

/**
 *  \brief MCAN Configuration Parameters Configurations.
 */
MCAN_ConfigParams canFDConfigParams[] =
{
    /* Config 0 */
    {
        0x0U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 1 */
    {
        0x0U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x1U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 2 */
    {
        0x0U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 3 */
    {
        0x0U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x2U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 4 */
    {
        0x1U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 5 */
    {
        0x1U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        MCAN_TSCC_TCP_MAX + 1U, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        MCAN_TOCC_TOP_MAX + 1U, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 6 */
    {
        0x1U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        MCAN_TSCC_TCP_MAX, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        MCAN_TOCC_TOP_MAX + 1U, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 7 */
    {
        0x1U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x1U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_CONT, /* Time-out counter source select */
        0xFFFFU, /* Start value of the Timeout Counter (down-counter) */
        0x0U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
    /* Config 8: Timeout counter enabled, source = RX FIFO0, small preload */
    {
        0x0U, /* Bus Monitoring Mode */
        0x0U, /* Restricted Operation Mode */
        0xFU, /* Timestamp Counter Prescaler */
        0x0U, /* Timestamp source selection */
        MCAN_TIMEOUT_SELECT_RX_FIFO0, /* Time-out counter source select */
        0x10U, /* Start value of the Timeout Counter (down-counter) */
        0x1U, /* Time-out Counter Enable */
        {
            0x1U, /* Reject Remote Frames Extended */
            0x1U, /* Reject Remote Frames Standard */
            0x1U, /* Accept Non-matching Frames Extended */
            0x1U, /* Accept Non-matching Frames Standard */
        },
    },
};

/**
 *  \brief MCAN MSG RAM Configuration Parameters Configurations.
 */
MCAN_MsgRAMConfigParams canFDRAMConfigParams[] =
{
    /* Config 0 */
    [0U] = 
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = APP_MCAN_TX_BUFF_SIZE,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = APP_MCAN_TX_FIFO_SIZE,            /* Transmit FIFO/Queue Size */
        .txBufMode = 0U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = APP_MCAN_FIFO_0_NUM,           /* Event FIFO Size */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = APP_MCAN_FIFO_1_NUM,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [1U] = 
    /* Config 1 */
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = APP_MCAN_TX_BUFF_SIZE,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = APP_MCAN_TX_FIFO_SIZE,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = APP_MCAN_FIFO_0_NUM,           /* Event FIFO Size */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = APP_MCAN_FIFO_1_NUM,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [2U] = 
    /* Config 2 */
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = APP_MCAN_TX_BUFF_SIZE,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = APP_MCAN_TX_FIFO_SIZE,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = 5U,           /* Event FIFO Size */
        .rxFIFO0OpMode = 1U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = 5U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [3U] = 
    /* Config 3 */
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = 64,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = 64,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = 5U,           /* Event FIFO Size */
        .rxFIFO0OpMode = 1U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = 5U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [4U] =
    /* Config 4 */
    {
        .lss = 0U,      /* List Size: Standard ID */
        .lse = 0U,      /* List Size: Extended ID*/
        .txBufCnt = 0U,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = 0U,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = 0U,           /* Event FIFO Size */
        .rxFIFO0OpMode = 1U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = 0U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [5U] =
    /* Config 4 */
    {
        .lss = 128U,      /* List Size: Standard ID */
        .lse = 128U,      /* List Size: Extended ID*/
        .txBufCnt = 64U,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = 32U,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = 32U,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = 64U,           /* Event FIFO Size */
        .rxFIFO0OpMode = 1U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = 64U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [6U] = 
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = APP_MCAN_TX_BUFF_SIZE,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = APP_MCAN_TX_FIFO_SIZE,            /* Transmit FIFO/Queue Size */
        .txBufMode = 0U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = APP_MCAN_FIFO_0_NUM,           /* Event FIFO Size */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode */
        .rxFIFO1Cnt = APP_MCAN_FIFO_1_NUM,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode */
        .rxBufElemSize = MCAN_ELEM_SIZE_8BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
    [7U] =
    /* Config 7 - MAX Tx FIFO and RX FIFOs Configuration */
    {
        .lss = 2U,      /* List Size: Standard ID - minimal allocation */
        .lse = 2U,      /* List Size: Extended ID - minimal allocation */
        .txBufCnt = 0U,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = 32U,            /* Transmit FIFO/Queue Size - MAX */
        .txBufMode = 0U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = 32U,          /* Tx Event FIFO Size - MAX */
        .rxFIFO0Cnt = 64U,           /* RX FIFO0 Size - MAX */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode - Blocking */
        .rxFIFO1Cnt = 64U,             /* Rx FIFO1 Size - MAX */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode - Blocking */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 16U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 32U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 32U,                         /* RX FIFO1 FIFO Watermark */
    },
    [8U] =
    /* Config 8 - MAX Dedicated Tx Buffers and MAX Dedicated Rx Buffers Configuration */
    {
        .lss = 2U,      /* List Size: Standard ID - minimal allocation */
        .lse = 2U,      /* List Size: Extended ID - minimal allocation */
        .txBufCnt = 32U,           /* Number of Dedicated Transmit Buffers - MAX */
        .txFIFOCnt = 0U,            /* Transmit FIFO/Queue Size */
        .txBufMode = 0U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = 32U,          /* Tx Event FIFO Size - MAX */
        .rxFIFO0Cnt = 0U,           /* RX FIFO0 Size */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode - Blocking */
        .rxFIFO1Cnt = 0U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode - Blocking */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 16U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 0U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 0U,                         /* RX FIFO1 FIFO Watermark */
    },
    [9U] =
    /* Config 9 - MAXIMUM Message RAM Configuration (uses all 4352 words)
     * This configuration tests the absolute maximum message RAM allocation:
     * - 128 Std ID filters (128 words)
     * - 64 Ext ID filters (128 words)
     * - 32 Tx buffers (576 words)
     * - 32 Tx Event FIFO (64 words)
     * - 64 RX FIFO0 (1152 words)
     * - 64 RX FIFO1 (1152 words)
     * - 64 RX Buffers (1152 words)
     * Total: 4352 words (exactly at MCAN_MSG_RAM_MAX_WORD_COUNT limit)
     */
    {
        .lss = 128U,      /* List Size: Standard ID - MAX */
        .lse = 64U,       /* List Size: Extended ID - MAX */
        .txBufCnt = 32U,  /* Number of Dedicated Transmit Buffers - MAX */
        .txFIFOCnt = 0U,  /* Transmit FIFO/Queue Size */
        .txBufMode = 0U,  /* Tx FIFO/Queue Mode - Buffer mode */
        .txEventFIFOCnt = 32U,  /* Tx Event FIFO Size - MAX */
        .rxFIFO0Cnt = 64U,      /* RX FIFO0 Size - MAX */
        .rxFIFO0OpMode = 0U,    /* Rx FIFO0 Operation Mode - Blocking */
        .rxFIFO1Cnt = 64U,      /* Rx FIFO1 Size - MAX */
        .rxFIFO1OpMode = 0U,    /* Rx FIFO1 Operation Mode - Blocking */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,   /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES, /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES, /* Rx FIFO1 Element Size */
        .txBufElemSize = MCAN_ELEM_SIZE_64BYTES,   /* Tx Buffer Element Size */
        .txEventFIFOWaterMark = 16U,  /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 32U,      /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 32U,      /* RX FIFO1 FIFO Watermark */
    },
    [10U] = 
    /* Config 10 - FIFO0 Blocking Mode Test Configuration for MSG_LOST interrupt test */
    {
        .lss = APP_MCAN_STD_ID_FILTER_NUM,      /* List Size: Standard ID */
        .lse = APP_MCAN_EXT_ID_FILTER_NUM,      /* List Size: Extended ID*/
        .txBufCnt = APP_MCAN_TX_BUFF_SIZE,           /* Number of Dedicated Transmit Buffers */
        .txFIFOCnt = APP_MCAN_TX_FIFO_SIZE,            /* Transmit FIFO/Queue Size */
        .txBufMode = 1U,                              /* Tx FIFO/Queue Mode */
        .txEventFIFOCnt = APP_MCAN_TX_BUFF_SIZE,          /* Tx Buffer Element Size */
        .rxFIFO0Cnt = 5U,           /* Event FIFO Size */
        .rxFIFO0OpMode = 0U,                              /* Rx FIFO0 Operation Mode - Blocking */
        .rxFIFO1Cnt = 5U,             /* Rx FIFO1 Size */
        .rxFIFO1OpMode = 0U,                              /* Rx FIFO1 Operation Mode - Blocking */
        .rxBufElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx Buffer Element Size */
        .rxFIFO0ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO0 Element Size */
        .rxFIFO1ElemSize = MCAN_ELEM_SIZE_64BYTES,          /* Rx FIFO1 Element Size */
        .txEventFIFOWaterMark = 3U,                         /* Tx Event FIFO Watermark */
        .rxFIFO0WaterMark = 3U,                         /* RX FIFO0 Watermark */
        .rxFIFO1WaterMark = 3U,                         /* RX FIFO1 FIFO Watermark */
    },
};

/**
 *  \brief MCAN ECC Configuration Parameters Configurations.
 */
MCAN_ECCConfigParams canFDECCConfigParams[] =
{
    /* Config 0 */
    {
        0x01U, /* Enable/disable ECC */
        0x01U, /* Enable/disable ECC Check */
        0x01U, /* Enable/disable Read Modify Write operation */
    },
};

/**
 *  \brief MCAN ECC Error Force Configuration Parameters Configurations.
 */
MCAN_ECCErrForceParams canFDECCErrForceConfigParams[] =
{
    /* Config 0 */
    {
        MCAN_ECC_ERR_TYPE_SEC, /* Error type to be forced */
        0x0AU, /* Row address where error needs to be applied. */
        0x04U, /* Column/Data bit that needs to be flipped */
        0x01U, /* Data bit that needs to be flipped when force_ded is set */
        0x01U, /* Force Error once */
        0x00U, /* Force error on the next RAM read */
    },
    /* Config 1 */
    {
        MCAN_ECC_ERR_TYPE_DED, /* Error type to be forced */
        0x40U, /* Row address where error needs to be applied. */
        0x04U, /* Column/Data bit that needs to be flipped */
        0x01U, /* Data bit that needs to be flipped when force_ded is set */
        0x01U, /* Force Error once */
        0x00U, /* Force error on the next RAM read */
    },
};

/**
 *  \brief MCAN Tx Message .
 */
st_mcanTxMSGParams_t canTxMSG[] =
{
    /* Message 0 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 1 */
    {
        {
            ((uint32_t)0xC4U), /* Identifier */
            0U,      /* Remote Transmission Request */
            1U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x6U,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 2 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 3 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x8U,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            0U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 4 */
    {
        {
            ((uint32_t)0x9U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x8U,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            0U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 5 */
    {
        {
            ((uint32_t)0xAU << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 6 */
    {
        {
            ((uint32_t)0xBU << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 7 */
    {
        {
            ((uint32_t)0xEU << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 8 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 9 */
    {
        {
            ((uint32_t)0xFFU << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 10 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 11 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 12 */
    {
        {
            ((uint32_t)0x8U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        1U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 13 */
    {
        {
            ((uint32_t)0x5U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        2U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 14 */
    {
        {
            ((uint32_t)0x3U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        3U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 15 */
    {
        {
            ((uint32_t)0x3U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        3U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 16 */
    {
        {
            ((uint32_t)0x4U), /* Identifier */
            0U,      /* Remote Transmission Request */
            1U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x8U,    /* Data Length Code */
            0U,      /* Bit Rate Switching */
            0U,      /* FD Format */
            0U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 17 */
    {
        {
            ((uint32_t)0x3U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x7U,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        3U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 18 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 19 */
    {
        {
            ((uint32_t)0x4U), /* Identifier */
            0U,      /* Remote Transmission Request */
            1U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 20 */
    {
        {
            ((uint32_t)0x7FFU << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 21: DLC=0 (0 bytes) */
    {
        {
            ((uint32_t)0x100U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x0U,    /* Data Length Code = 0 bytes */
            0U,      /* Bit Rate Switching = OFF */
            1U,      /* FD Format = ON */
            1U,      /* Event FIFO Control */
            0x10U,   /* Message Marker */
            { 0 },   /* Data */
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number */
        MCAN_MEM_TYPE_BUF, /* RX Storage Identifier */
        0U, /* RX Buffer number */
    },
        /* Message 22: CAN FD frame (fdf=1) with DLC>8 to trigger element-size mismatch */
    {
        {
            ((uint32_t)0x200U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code (15 -> >8) */
            1U,      /* Bit Rate Switching = ON */
            1U,      /* FD Format = ON */
            1U,      /* Event FIFO Control */
            0x55U,   /* Message Marker */
            { /* Data (filled partially) */
                0xAA, 0xBB, 0xCC, 0xDD,
                0x11, 0x22, 0x33, 0x44,
                0x55, 0x66, 0x77, 0x88,
                0x99, 0x00, 0xEE, 0xFF,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
     /* Message 23 */
    {
        {
            ((uint32_t)0x3U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0x00, 0x00, 0x00, 0x00,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- where received message shall be stored */
        MCAN_RX_FIFO_NUM_1, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 24 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
                0x12, 0x34, 0xAB, 0xCD,
                0xDE, 0xAD, 0xBA, 0xBE,
                0x12, 0x34, 0x56, 0x78,
                0x9A, 0xBC, 0xDE, 0xF0,
                0x44, 0xf0, 0x0D, 0x44,
                0x11, 0x11, 0x11, 0x11,
                0x01, 0x32, 0x29, 0x50,
                0x44, 0x44, 0x44, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
    /* Message 25 - Test with ID 0x123 (should match filter 9 sfid1 after masking) */
    {
        {
            ((uint32_t)0x123U << 18U), /* Identifier - 0x123 in standard ID format */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x4U,    /* Data Length Code - 4 bytes */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0x25U,   /* Message Marker - 0x25 for message 25 */
            { /* Data */
                0xAA, 0xBB, 0xCC, 0xDD,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored (TX Buffer 0) */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- received message stored in RX FIFO */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored (RX FIFO 0) */
    },
    /* Message 26 - Test with ID 0x456 (should match filter 9 sfid2 after masking) */
    {
        {
            ((uint32_t)0x456U << 18U), /* Identifier - 0x456 in standard ID format */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x4U,    /* Data Length Code - 4 bytes */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0x26U,   /* Message Marker - 0x26 for message 26 */
            { /* Data */
                0x11, 0x22, 0x33, 0x44,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        1U, /* Buffer number where message is to be stored (TX Buffer 1) */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- received message stored in RX FIFO */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored (RX FIFO 0) */
    },
    /* Message 27 - Extended ID Test with ID 0x1FFFFFFF (should match filter 4 efid1 after masking 0xFFFFFFFF) */
    {
        {
            0x1FFFFFFFU, /* Identifier - 0x1FFFFFFF (max valid 29-bit extended ID) */
            0U,      /* Remote Transmission Request */
            1U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x4U,    /* Data Length Code - 4 bytes */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0x27U,   /* Message Marker - 0x27 for message 27 */
            { /* Data */
                0xEE, 0xFF, 0x11, 0x22,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored (TX Buffer 0) */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- received message stored in RX FIFO */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored (RX FIFO 0) */
    },
    /* Message 28 - Extended ID Test with ID 0x12345678 (should match filter 4 efid2 after masking 0xF2345678) */
    {
        {
            0x12345678U, /* Identifier - 0x12345678 (valid 29-bit extended ID) */
            0U,      /* Remote Transmission Request */
            1U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0x4U,    /* Data Length Code - 4 bytes */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0x28U,   /* Message Marker - 0x28 for message 28 */
            { /* Data */
                0x55, 0x66, 0x77, 0x88,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        1U, /* Buffer number where message is to be stored (TX Buffer 1) */
        MCAN_MEM_TYPE_FIFO, /* Storage Identifier- received message stored in RX FIFO */
        MCAN_RX_FIFO_NUM_0, /* Buffer/FIFO number where received message is to be stored (RX FIFO 0) */
    },
    /* Message 29 */
    {
        {
            ((uint32_t)0x4U << 18U), /* Identifier */
            0U,      /* Remote Transmission Request */
            0U,      /* Extended Identifier */
            0U,      /* Error State Indicator */
            0xFU,    /* Data Length Code */
            1U,      /* Bit Rate Switching */
            1U,      /* FD Format */
            1U,      /* Event FIFO Control */
            0xAAU,   /* Message Marker */
            { /* Data */
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
            },
        },
        MCAN_MEM_TYPE_BUF, /* Storage Identifier */
        0U, /* Buffer number where message is to be stored. */
        MCAN_MEM_TYPE_BUF, /* Storage Identifier- where received message shall be stored */
        0U, /* Buffer/FIFO number where received message is to be stored */
    },
};

/**
 *  \brief CAN Standard ID Filter Configurations.
 */
MCAN_StdMsgIDFilterElement canSTDIDFilter[] =
{
    /* Filter 0 */
    {
        (0x2U << 6U), /* Standard Filter ID 2 */
        0x04U, /* Standard Filter ID 1 */
        0x07U, /* Standard Filter Element Configuration */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 1 */
    {
        0x00U, /* Standard Filter ID 2 */
        0xFFU, /* Standard Filter ID 1 */
        0x07U, /* Standard Filter Element Configuration */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 2 */
    {
        0x0AU, /* Standard Filter ID 2 */
        0x04U, /* Standard Filter ID 1 */
        0x01U, /* Standard Filter Element Configuration */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 3 */
    {
        0x0AU, /* Standard Filter ID 2 */
        0x0FU, /* Standard Filter ID 1 */
        0x01U, /* Standard Filter Element Configuration */
        0x02U, /* Standard Filter Type */
    },
    /* Filter 4 */
    {
        0x0AU, /* Standard Filter ID 2 */
        0x0FU, /* Standard Filter ID 1 */
        0x01U, /* Standard Filter Element Configuration */
        0x02U, /* Standard Filter Type */
    },
    /* Filter 5 */
    {
        0x0AU, /* Standard Filter ID 2 */
        0x0FU, /* Standard Filter ID 1 */
        0x05U, /* Standard Filter Element Configuration */
        0x02U, /* Standard Filter Type */
    },
    /* Filter 6 */
    {
        (0x2U << 6U), /* Standard Filter ID 2 */
        0x04U, /* Standard Filter ID 1 */
        0x07U, /* Standard Filter Element Configuration */
        0x01U, /* Standard Filter Type */
    },
    /* Filter 7 */
    {
        (0x2U << 6U), /* Standard Filter ID 2 */
        0x04U, /* Standard Filter ID 1 */
        0x02U, /* Standard Filter Element Configuration */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 8 */
    {
        0x0U, /* Standard Filter ID 2 */
        0xFFFFFFFFU, /* Standard Filter ID 1 */
        0x07U, /* Standard Filter Element Configuration */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 9 - Test Masking with out-of-range values */
    {
        0xFFFFF456U, /* Standard Filter ID 2 - bits beyond 11 should be masked to 0x456 */
        0xFFFFF123U, /* Standard Filter ID 1 - bits beyond 11 should be masked to 0x123 */
        0x01U, /* Standard Filter Element Configuration - Store in Rx FIFO 0 (was 0x07) */
        0x01U, /* Standard Filter Type - Dual ID filter (match sfid1 OR sfid2) */
    },
    /* Filter 10 - For MultiThreaded Tests (10295, 10296, 10297) - Routes ID 0x04 to RX FIFO0 */
    {
        (0x2U << 6U), /* Standard Filter ID 2 */
        0x04U, /* Standard Filter ID 1 - Matches TX messages with ID 0x04 */
        0x01U, /* Standard Filter Element Configuration - Store in Rx FIFO 0 */
        0x00U, /* Standard Filter Type - Range filter */
    },
    /* Filter 11 - For Intr+Poll Multi-Thread Test (10498) - Routes ID 0x04 to dedicated RX Buffer 0 */
    {
        0x00U, /* Standard Filter ID 2 - RX buffer index 0 (used when sfec=7) */
        0x04U, /* Standard Filter ID 1 - Matches TX messages with ID 0x04 */
        0x07U, /* Standard Filter Element Configuration - Store in dedicated Rx Buffer */
        0x00U, /* Standard Filter Type */
    },
    /* Filter 12 - For Intr+Poll Multi-Thread Test (10498) - Routes ID 0x05 to RX FIFO 0 */
    {
        0x05U, /* Standard Filter ID 2 - same as ID1 for exact match range */
        0x05U, /* Standard Filter ID 1 - Matches TX messages with ID 0x05 */
        0x01U, /* Standard Filter Element Configuration - Store in Rx FIFO 0 */
        0x00U, /* Standard Filter Type - Range filter */
    },
};

/**
 *  \brief CAN Extended ID Filter Configurations.
 */
MCAN_ExtMsgIDFilterElement canEXTIDFilter[] =
{
    /* Filter 0 */
    {
        0xC4U, /* Extended Filter ID 1 */
        0x07U, /* Extended Filter Element Configuration */
        0x00U, /* Extended Filter ID 2 */
        0x00U, /* Extended Filter Type */
    },
    /* Filter 1 */
    {
        0xD4U, /* Extended Filter ID 1 */
        0x07U, /* Extended Filter Element Configuration */
        0x00U, /* Extended Filter ID 2 */
        0x00U, /* Extended Filter Type */
    },
    /* Filter 2 */
    {
        0x04U, /* Extended Filter ID 1 */
        0x07U, /* Extended Filter Element Configuration */
        (0x2U << 6U), /* Extended Filter ID 2 */
        0x00U, /* Extended Filter Type */
    },
    /* Filter 3 */
    {
        0x04U, /* Extended Filter ID 1 */
        0x02U, /* Extended Filter Element Configuration */
        (0x2U << 6U), /* Extended Filter ID 2 */
        0x00U, /* Extended Filter Type */
    },
        /* Filter 4 - Test Masking with out-of-range extended ID values */
    {
        0xFFFFFFFFU, /* Extended Filter ID 1 - bits beyond 29 should be masked to 0x1FFFFFFF */
        0x01U, /* Extended Filter Element Configuration - Store in Rx FIFO 0 (was 0x07) */
        0xF2345678U, /* Extended Filter ID 2 - bits beyond 29 should be masked to 0x12345678 */
        0x01U, /* Extended Filter Type - Dual ID filter (match efid1 OR efid2) */
    },
};

#endif /* #ifndef ST_MCAN_TEST_CASES_CONFIG_H_ */
