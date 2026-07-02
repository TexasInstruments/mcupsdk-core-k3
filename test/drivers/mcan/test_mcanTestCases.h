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
 *  \file stw_mcanTestcases.h
 *
 *  \brief This file defines the test cases for mcan UT.
 */

#ifndef TEST_MCAN_TEST_CASES_H_
#define TEST_MCAN_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "test_mcan.h"
#include "test_mcanTestCasesConfig.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MCAN_NUM_TESTCASES               (sizeof (gMcanTestcaseParams) / sizeof (st_mcanTestcaseParams_t))
#define MCAN_MANUAL_TEST_ENABLE          (0U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various mcan test cases. */
st_mcanTestcaseParams_t gMcanTestcaseParams[] =
{
    /* enableTest, testCaseId,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason
     * cpuID,
     * mcanConfigParams,
     * printEnable,
     * testType,
     */
    {
        TEST_ENABLE, 10222U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON And Bitrate 1MBps/5MBps",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10223U,
        "None",
        "MCAN: Internal Loopback, High Priority And Bitrate 1MBps/2.5MBps",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[1U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10224U,
        "None",
        "MCAN: Internal Loopback, High Priority And Bitrate 250Kbps/5MBps",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[2U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10225U,
        "None",
        "MCAN: Internal Loopback, High Priority And Bitrate 125Kbps/5MBps",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[3U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10226U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON Extended Id Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[1U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10227U,
        "None",
        "MCU MCAN 0: Classic CAN Mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_1)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10228U,
        "None",
        "MCU MCAN 0: Classic CAN Mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_1)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10229U,
        "None",
        "MCAN: Tx Mixed Config. With Buffer and Queue",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[1U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10230U,
        "None",
        "MCAN: Tx Mixed Config. With Buffer and FIFO",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10231U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON And MAX TX Buffer Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10232U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON And RX Buffer Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10271U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching OFF, RX FIFO 0 Test",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            3U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[5U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[3U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#if !defined(R5_FREERTOS_CORE) && !defined(MCU_M4_CORE)
    {
        TEST_ENABLE, 10233U,
        "None",
        "MCAN: Rx FIFO 1 Test mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[2U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[15U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10234U,
        "None",
        "MCAN: Rx FIFO 0 Message Lost Test",
        "In this TC, no filters will be configured and all incoming messages will be stored into FIFO(by accepting non-matching frame) for later comparison.", "None",
        "1. In Blocking Mode, after FIFO(FIFO1) full, new message shall be rejected. 2. In Overwrite Mode, after FIFO(FIFO0) full, new message shall be overwritten on oldest message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[2U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[17U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10235U,
        "None",
        "MCAN: Rx FIFO 0 Message Lost Test",
        "In this TC, no filters will be configured and all incoming messages will be stored into FIFO(by accepting non-matching frame) for later comparison.", "None",
        "1. In Blocking Mode, after FIFO(FIFO1) full, new message shall be rejected. 2. In Overwrite Mode, after FIFO(FIFO0) full, new message shall be overwritten on oldest message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[2U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[15U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 11863U,
        "None",
        "MCAN: Rx FIFO 0 Message Lost Interrupt Test",
        "Test MCAN_INTR_SRC_RX_FIFO0_MSG_LOST interrupt in blocking mode. No filters configured, all incoming messages stored into FIFO0 by accepting non-matching frames.", "None",
        "1. In Blocking Mode, after FIFO0 full, new message shall be rejected and MCAN_INTR_SRC_RX_FIFO0_MSG_LOST interrupt shall be triggered. 2. Get/Put indices shall not be updated after message lost.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[10U], /* mcan module MSG RAM configuration parameters - FIFO0 Blocking Mode */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[15U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#endif
    {
        TEST_ENABLE, 10236U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON And MAX TX Buffer Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10237U,
        "None",
        "MCAN: Tx and Rx Throughput Standard ID",
        "None", "None",
        "Sent messages shall match with received message and measured frames per seconds should be 85% of the theoretical.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1000U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[18U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[7U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10238U,
        "None",
        "MCAN: Tx and Rx Throughput Extended ID",
        "None", "None",
        "Sent messages shall match with received message and measured frames per seconds should be 85% of the theoretical.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1000U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[19U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[3U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10239U,
        "None",
        "MCAN: High Priority Messages",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10272U,
        "None",
        "MCAN: Message Cancel Test",
        "None", "None",
        "MCAN shall cancel pending messages.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10273U,
        "None",
        "MCAN: LOOPBACK Automatic Retransmission Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10240U,
        "None",
        "MCAN: LOOPBACK Transmitter Delay Compensation Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10274U,
        "None",
        "MCU MCAN 0: Classic CAN Mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_1)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10275U,
        "None",
        "MCAN: Revision ID Test",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_1)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10241U,
        "None",
        "MCAN: Pin State",
        "None", "None",
        "Configured PAD values shall match with read values.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10242U,
        "None",
        "MCAN: LOOPBACK Endianess Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10243U,
        "None",
        "MCAN: Rx FIFO Block Mode/Overwrite mode",
        "In this TC, no filters will be configured and all incoming messages will be stored into FIFO(by accepting non-matching frame) for later comparison.", "None",
        "1. In Blocking Mode, after FIFO(FIFO1) full, new message shall be rejected. 2. In Overwrite Mode, after FIFO(FIFO0) full, new message shall be overwritten on oldest message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[2U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[15U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10244U,
        "None",
        "MCAN: Acceptance Filter Range Filter Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10245U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON, DUAL FILTER ID Test",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[6U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10246U,
        "None",
        "MCAN: Internal Loopback, Classic BitMask Filter Test 1MBps/2.5MBps",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[1U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#if !defined (A53_CORE) && !defined (WKUP_R5_CORE)
    {
        TEST_ENABLE, 10247U,
        "None",
        "MCAN: External Time-Stamp Code Coverage Improvement Test",
        "None", "None",
        "1.Sent message shall match with received message.2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[3U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#endif
    {
        TEST_ENABLE, 10248U,
        "None",
        "MCAN: Time Stamp Counter Reset Code Coverage Improvement Test",
        "None", "None",
        "Time Stamp Counter shall get reset after calling TS Reset API.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10249U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10250U,
        "None",
        "MCAN: Clock Stop Request",
        "None", "None",
        "MCAN shall ack back the clock stop request.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10251U,
        "None",
        "MCAN: Code Coverage Enhancement Test, Error Test",
        "None", "None",
        "None",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[4U], /* mcan module bit timing parameters */
            &canFDInitParams[1U], /* mcan module initialization parameters */
            &canFDConfigParams[5U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[3U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    
    {
        TEST_ENABLE, 10253U,
        "None",
        "MCAN: Code Coverage Enhancement Test, Error Test",
        "None", "None",
        "None",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[5U], /* mcan module bit timing parameters */
            &canFDInitParams[1U], /* mcan module initialization parameters */
            &canFDConfigParams[5U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[3U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10254U,
        "None",
        "MCAN: Tx and Rx Acceptance Filter Test with SFID as 0xFFFFFFFF",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[20U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[8U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#if (MCAN_MANUAL_TEST_ENABLE == 1U)
    {
        TEST_ENABLE, 1259U,
        "Test Setup: Connect MCAN HIGH and MCAN LOW Pins to PCAN Tool",
        "MCAN: CAN FD Bus Monitor Test",
        "None", "None",
        "1.Sent message from PCAN shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[7U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1256U,
        "Test Setup: Short MCAN_HIGH and MCAN_LOW Pins",
        "MCAN: CAN FD Error Passive Test",
        "None", "None",
        "1.Error Passive Status Should Occur.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1257U,
        "Test Setup: Short MCAN_HIGH and MCAN_LOW Pins",
        "MCAN: CAN FD Bus Off Test",
        "None", "None",
        "1.BUS Off Should Occur.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 11088U,
        "Test Setup: Connect MCAN HIGH and MCAN LOW Pins to PCAN Tool\n"
        "PCAN: Nominal=1000kbps(SP=85%,Pr=2,TSEG1=33,TSEG2=6,tq=25ns,Nq=40) Data=5000kbps(SP=87.5%,Pr=2,TSEG1=13,TSEG2=2,tq=12.5ns,Nq=16)",
        "MCAN: External PCAN CAN FD TX/RX Test - 1000kbps Nominal (SP=85%) / 5000kbps Data (SP=87.5%)",
        "None", "None",
        "1. DUT transmits CAN FD message with BRS at 1000kbps Nominal / 5000kbps Data (SP=85%/87.5%).\n"
        "2. PCAN tool receives and validates the message.\n"
        "3. PCAN tool sends back a CAN FD message with matching ID (0x04).\n"
        "4. DUT receives and validates the message matches the transmitted one.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[12U], /* 1000kbps Nom (SP=85%) / 5000kbps Data (SP=87.5%) */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[29U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 11089U,
        "Test Setup: Connect MCAN HIGH and MCAN LOW Pins to PCAN Tool\n"
        "PCAN: Nominal=500kbps(SP=85%,Pr=2,TSEG1=67,TSEG2=12,tq=25ns,Nq=80) Data=2500kbps(SP=87.5%,Pr=1,TSEG1=27,TSEG2=4,tq=12.5ns,Nq=32)",
        "MCAN: External PCAN CAN FD TX/RX Test - 500kbps Nominal (SP=85%) / 2500kbps Data (SP=87.5%)",
        "None", "None",
        "1. DUT transmits CAN FD message with BRS at 500kbps Nominal / 2500kbps Data (SP=85%/87.5%).\n"
        "2. PCAN tool receives and validates the message.\n"
        "3. PCAN tool sends back a CAN FD message with matching ID (0x04).\n"
        "4. DUT receives and validates the message matches the transmitted one.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[13U], /* 500kbps Nom (SP=85%) / 2500kbps Data (SP=87.5%) */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[29U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 11090U,
        "Test Setup: Connect MCAN HIGH and MCAN LOW Pins to PCAN Tool\n"
        "PCAN: Nominal=250kbps(SP=85%,Pr=2,TSEG1=135,TSEG2=24,tq=25ns,Nq=160) Data=5000kbps(SP=87.5%,Pr=1,TSEG1=13,TSEG2=2,tq=12.5ns,Nq=16)",
        "MCAN: External PCAN CAN FD TX/RX Test - 250kbps Nominal (SP=85%) / 5000kbps Data (SP=87.5%)",
        "None", "None",
        "1. DUT transmits CAN FD message with BRS at 250kbps Nominal / 5000kbps Data (SP=85%/87.5%).\n"
        "2. PCAN tool receives and validates the message.\n"
        "3. PCAN tool sends back a CAN FD message with matching ID (0x04).\n"
        "4. DUT receives and validates the message matches the transmitted one.",
        IPU,
        {
            (MCAN_TEST_TYPE_EXTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[14U], /* 250kbps Nom (SP=85%) / 5000kbps Data (SP=87.5%) */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[29U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#endif
    {
        TEST_ENABLE, 10477U,
        "None",
        "MCAN: RX FIFO0 Watermark Interrupt Test",
        "None", "None",
        "Validate RX FIFO0 watermark interrupt and threshold behavior.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[2U], /* mcan module MSG RAM configuration parameters (FIFO0=5, WM=3) */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            3U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[5U], /* tx Buffer elements/Tx message (targets RX FIFO0) */
            &canSTDIDFilter[3U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10478U,
        "None",
        "MCAN: Timeout Counter (TOCC/TOCV) on RX FIFO0",
        "None", "None",
        "Enable timeout counter; verify TOO interrupt and counter zero.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* bit timing */
            &canFDInitParams[0U], /* init params */
            &canFDConfigParams[8U], /* config: timeout enabled, RX FIFO0 source */
            &canFDRAMConfigParams[2U], /* RAM: FIFO0 small */
            &canFDECCConfigParams[0U], /* ECC */
            &canFDECCErrForceConfigParams[0U], /* ECC force */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[3U], /* classic frame to RX FIFO0 */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND) | MCAN_INTR_SRC_TIMEOUT,  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL) | MCAN_INTR_SRC_TIMEOUT,  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    
    },
    {
        TEST_ENABLE, 10479U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching OFF, RX FIFO 0 Test with DLC = 0",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[21U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[3U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },

    /* Negative TC: send CAN-FD frame (dlc>8) while Message RAM element size configured as classic (8B) */
    {
        TEST_ENABLE, 10480U,
        "None",
        "MCAN: FD DLC >8 vs MSG RAM element size mismatch (negative)",
        "None", "None",
        "Send CAN-FD frame (fdf=1, dlc>8) while MSG RAM elements configured for classic frames (8B). Driver/MCAN should report error and not transmit corrupted data.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[6U], /* mcan module MSG RAM configuration parameters (8B elems) */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[22U], /* tx Buffer elements/Tx message (FD frame, dlc>8) */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_NEGATIVE),
    },

    /* Negative TC: send CAN-FD frame while FD operation is disabled in configuration */
    {
        TEST_ENABLE, 10481U,
        "None",
        "MCAN: FD operation disabled but sending FD frame (negative)",
        "None", "None",
        "Attempt to transmit CAN-FD frame (fdf=1) while FD operation is disabled in config. Driver/MCAN should reject FD frame or report error.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[4U], /* mcan module initialization parameters (FD disabled) */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message (FD frame) */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_NEGATIVE),
    },
    #if 0 /* This TC is currently disabled as it may cause system instability if NULL pointer dereference is not handled properly by driver/MCAN. To be enabled after fixing the issue. */
    {
        TEST_ENABLE, 10482U,
        "None",
        "MCAN: NULL pointer validation for all public APIs (negative)",
        "None", "None",
        "APIs should reject or safely handle NULL pointer arguments.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* bit timing parameters */
            &canFDInitParams[0U], /* initialization parameters */
            &canFDConfigParams[0U], /* configuration parameters */
            &canFDRAMConfigParams[0U], /* MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* ECC Error Force parameters */
            0U, /* tx message number */
            0U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            NULL, /* tx Buffer elements/Tx message */
            NULL, /* standard message ID filters */
            NULL, /* extended message ID filters */
            0U, /* Interrupt Enable/Disable Mask */
            0U, /* Interrupt Line Select Mask */
            0U  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_NEGATIVE),
    },
    #endif
    {
        TEST_ENABLE, 10483U,
        "None",
        "MCAN: Configure and validate 128 Standard ID filter elements",
        "None", "None",
        "Configure up to 128 standard ID filters and validate routing to buffers/FIFOs/reject.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* bit timing params */
            &canFDInitParams[0U], /* init params */
            &canFDConfigParams[1U], /* config params (ensure msg RAM supports 128 STD filters) */
            &canFDRAMConfigParams[0U], /* MSG RAM configuration params */
            &canFDECCConfigParams[0U], /* ECC config params */
            &canFDECCErrForceConfigParams[0U], /* ECC Err Force params */
            1U, /* tx message number */
            128U, /* standard ID message filter number (128 filters) */
            0U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message (choose appropriate) */
            &canSTDIDFilter[0U], /* pointer to STD ID filter array (must contain 128 entries) */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10484U,
        "None",
        "MCAN: Configure and validate 64 Extended ID filter elements",
        "None", "None",
        "Configure up to 64 extended ID filters and validate routing to buffers/FIFOs/reject.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* bit timing params */
            &canFDInitParams[0U], /* init params */
            &canFDConfigParams[1U], /* config params (ensure msg RAM supports 64 EXT filters) */
            &canFDRAMConfigParams[0U], /* MSG RAM configuration params */
            &canFDECCConfigParams[0U], /* ECC config params */
            &canFDECCErrForceConfigParams[0U], /* ECC Err Force params */
            1U, /* tx message number */
            0U, /* standard ID message filter number */
            64U, /* extended ID message filter number (64 filters) */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* pointer to EXT ID filter array (must contain 64 entries) */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10485U,
        "None",
        "MCAN: Burst TX FIFO (32) -> MAX RX FIFO0 (64) Test",
        "Burst test: all 32 TX FIFO slots are filled and all TX requests are submitted\n"
        "before waiting for any acknowledgement (Phase 1 burst fill).\n"
        "Phase 2 polls TXBTO until all 32 TXBTO bits are set.\n"
        "Phase 3 waits until RX FIFO0 fill level reaches 32, then drains continuously.",
        "None",
        "1. All 32 TX requests must complete without protocol errors.\n"
        "2. RX FIFO0 must accumulate exactly 32 messages.\n"
        "3. Each received message data[0] must match its submission sequence index (0-31).",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            32U, /* iteration count (used by App_mcanBurstTxTest as bust count) */
            &canFDBitTimings[0U], /* bit timing params */
            &canFDInitParams[0U], /* init params */
            &canFDConfigParams[1U], /* config params */
            &canFDRAMConfigParams[7U], /* MSG RAM: txFIFO=32, rxFIFO0=64, rxFIFO1=64 */
            &canFDECCConfigParams[0U], /* ECC config params */
            &canFDECCErrForceConfigParams[0U], /* ECC Err Force params */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[3U], /* Classic CAN 8B frame; storageId=FIFO, rxFIFO=FIFO0 */
            &canSTDIDFilter[2U], /* range [0x04..0x0A] -> FIFO0 */
            &canEXTIDFilter[0U],
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),
            (MCAN_INTR_MASK_ALL),
            (MCAN_INTR_LINE_NUM_0)
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 10486U,
        "None",
        "MCAN: Burst TX FIFO (32) -> MAX RX FIFO1 (64) Test",
        "Burst test: all 32 TX FIFO slots are filled and all TX requests are submitted\n"
        "before waiting for any acknowledgement (Phase 1 burst fill).\n"
        "Phase 2 polls TXBTO until all 32 TXBTO bits are set.\n"
        "Phase 3 waits until RX FIFO1 fill level reaches 32, then drains continuously.\n"
        "canTxMSG[23] has ID=0x3 which does not match filter [2] (range 0x04-0x0A),\n"
        "so GFC anfs=1 routes non-matching standard frames to RX FIFO1.",
        "None",
        "1. All 32 TX requests must complete without protocol errors.\n"
        "2. RX FIFO1 must accumulate exactly 32 messages.\n"
        "3. Each received message data[0] must match its submission sequence index (0-31).",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            32U, /* iteration count */
            &canFDBitTimings[0U],
            &canFDInitParams[0U],
            &canFDConfigParams[1U], /* GFC: anfs=1 routes non-matching std frames to FIFO1 */
            &canFDRAMConfigParams[7U], /* MSG RAM: txFIFO=32, rxFIFO0=64, rxFIFO1=64 */
            &canFDECCConfigParams[0U],
            &canFDECCErrForceConfigParams[0U],
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[23U], /* CAN-FD 64B frame; ID=0x3 (below filter range) -> FIFO1 via GFC */
            &canSTDIDFilter[2U], /* range [0x04..0x0A] -> FIFO0; ID 0x3 misses -> GFC -> FIFO1 */
            &canEXTIDFilter[0U],
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),
            (MCAN_INTR_MASK_ALL),
            (MCAN_INTR_LINE_NUM_0)
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 10487U,
        "None",
        "MCAN: Burst Dedicated TX Buffers (32) -> Dedicated RX Buffers (32) Test",
        "Burst test validating the dedicated RX buffer path with maximum (32) buffers.\n"
        "Setup: 32 std ID filters programmed dynamically in SW_INIT; each filter uses\n"
        "sfec=MCAN_STD_FILT_ELEM_BUFFER to route ID (0x001+i) into dedicated RX buffer i.\n"
        "Phase 1: Burst-fill all 32 dedicated TX buffers (data[0]=i, ID=0x001+i) and\n"
        "         issue all 32 TX requests at once before waiting for any completion.\n"
        "Phase 2: Poll MCAN_getTxBufTransmissionStatus() until all 32 TXBTO bits [0..31] set.\n"
        "Phase 3: Poll MCAN_getNewDataStatus().statusLow until bits 0..31 all set,\n"
        "         then read each dedicated RX buffer via MCAN_MEM_TYPE_BUF and verify.\n"
        "Uses canFDRAMConfigParams[8] (lss=32, txBufCnt=32, rxFIFO0/1=0).",
        "None",
        "1. All 32 TX buffers must transmit successfully (TXBTO bits 0..31 set).\n"
        "2. All 32 dedicated RX buffers must receive exactly one message each\n"
        "   (MCAN_getNewDataStatus().statusLow bits 0..31 all set).\n"
        "3. data[0] of each received message must equal its buffer index i.\n"
        "4. ID in each received message must equal (0x001 + i) in standard ID field.\n"
        "5. No protocol errors or error counter increments during the burst.\n"
        "6. RX FIFO0 and FIFO1 must remain empty (no messages routed there).",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U,                                 /* iteration count (test controls 32 internally) */
            &canFDBitTimings[0U],
            &canFDInitParams[0U],
            &canFDConfigParams[1U],
            &canFDRAMConfigParams[8U],           /* lss=32, txBufCnt=32, rxFIFO0/1=0 */
            &canFDECCConfigParams[0U],
            &canFDECCErrForceConfigParams[0U],
            1U,                                 /* tx message number (template; 32 used internally) */
            0U,                                 /* std ID filter num (added dynamically in test) */
            0U,                                 /* extended ID message filter number */
            &canTxMSG[0U],                      /* tx Buffer element template */
            &canSTDIDFilter[0U],                /* not used (stdIdFiltNum=0) */
            &canEXTIDFilter[0U],
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),
            (MCAN_INTR_MASK_ALL),
            (MCAN_INTR_LINE_NUM_0)
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    {
        TEST_ENABLE, 10488U,
        "None",
        "MCAN: Max Msg RAM Word Count - Send 193 Receive 192 Test",
        "This test validates max message RAM word count configuration (4352 words).\n"
        "128 Std ID filters, 64 Ext ID filters, 32 Tx buffers, 32 Tx Event FIFO,\n"
        "64 RX FIFO0, 64 RX FIFO1, 64 RX Buffers (Total 192 RX elements at limit).\n"
        "Sends 193 messages, receives 192 successfully, 193rd receive should fail.",
        "None",
        "1. Message RAM configuration should succeed at maximum allocation (4352 words).\n"
        "2. 192 messages should be received successfully (64 FIFO0 + 64 FIFO1 + 64 RX Buf).\n"
        "3. 193rd message should be lost (MSG_LOST) as all RX paths are full.\n"
        "4. Total received count must equal 192.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count - test uses custom send/receive logic */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[9U], /* mcan module MSG RAM configuration parameters - MAX Config */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number - test sends internally */
            0U, /* standard ID message filter number - filters set up dynamically */
            0U, /* extended ID message filter number - filters set up dynamically */
            &canTxMSG[0U], /* tx message template (uses dedicated buffer 0) */
            &canSTDIDFilter[0U], /* not used (stdIdFiltNum=0) */
            &canEXTIDFilter[0U],  /* not used (extIdFiltNum=0) */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    {
        TEST_ENABLE, 10489U,
        "None",
        "MCAN: Standard ID Filter Masking Validation Test",
        "This test validates that the MCAN driver properly masks standard ID filter values\n"
        "when out-of-range bits are set. Filter is configured with sfid1=0xFFFFF123 and\n"
        "sfid2=0xFFFFF456 (bits beyond 11 should be masked). Messages with IDs 0x123 and\n"
        "0x456 should match correctly if proper masking is applied before filter programming.",
        "None",
        "1. Filter configuration should mask input values to 11-bit standard ID range (0x000-0x7FF).\n"
        "2. Message with ID 0x123 should match sfid1 (after masking 0xFFFFF123 -> 0x123).\n"
        "3. Message with ID 0x456 should match sfid2 (after masking 0xFFFFF456 -> 0x456).\n"
        "4. Both transmitted messages should be received correctly in loopback mode.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx - send 2 messages (one for each filter ID) */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number - send 2 messages */
            1U, /* standard ID message filter number - 1 filter with dual ID mode */
            0U, /* extended ID message filter number */
            &canTxMSG[25U], /* tx messages 25 and 26 (IDs 0x123 and 0x456) */
            &canSTDIDFilter[9U], /* standard message ID filter 9 (with out-of-range values) */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_NEGATIVE),
    },
    {
        TEST_ENABLE, 10490U,
        "None",
        "MCAN: Extended ID Filter Masking Validation Test",
        "This test validates that the MCAN driver properly masks extended ID filter values\n"
        "when out-of-range bits are set. Filter is configured with efid1=0xFFFFFFFF and\n"
        "efid2=0xF2345678 (bits beyond 29 should be masked). Messages with IDs 0x1FFFFFFF and\n"
        "0x12345678 should match correctly if proper masking is applied before filter programming.",
        "None",
        "1. Filter configuration should mask input values to 29-bit extended ID range (0x00000000-0x1FFFFFFF).\n"
        "2. Message with ID 0x1FFFFFFF should match efid1 (after masking 0xFFFFFFFF -> 0x1FFFFFFF).\n"
        "3. Message with ID 0x12345678 should match efid2 (after masking 0xF2345678 -> 0x12345678).\n"
        "4. Both transmitted messages should be received correctly in loopback mode.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx - send 2 messages (one for each filter ID) */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number - send 2 messages */
            0U, /* standard ID message filter number */
            1U, /* extended ID message filter number - 1 filter with dual ID mode */
            &canTxMSG[27U], /* tx messages 27 and 28 (Extended IDs 0x1FFFFFFF and 0x12345678) */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[4U],  /* extended message ID filter 9 (with out-of-range values) */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_NEGATIVE),
    },
    #if defined (FREERTOS_CORE)
    {
        TEST_ENABLE, 10491U,
        "MCAN_MT_002",
        "MCAN: Multi-threaded TX/RX Test (5 Messages)",
        "None", 
        "None",
        "Simple multi-threaded test validating continuous TX/RX stability with 5 messages.\n"
        "TX Producer Thread: Transmits 5 CAN-FD messages with unique sequential data patterns.\n"
        "RX Consumer Thread: Receives and validates message integrity and data correctness.\n"
        "Uses TaskP_construct and SemaphoreP_constructCounting APIs as required.\n"
        "Validates: 1) Producer-Consumer pattern 2) End-to-end correctness 3) Thread safety",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    {
        TEST_ENABLE, 10492U,
        "MCAN_MT_003",
        "MCAN: Concurrent TX Test - Two Threads with Dedicated Buffers (10 Messages Each)",
        "None", 
        "None",
        "Concurrent TX test validating thread-safe simultaneous transmission from two threads.\n"
        "TX Thread 1: Transmits 10 CAN-FD messages using dedicated TX Buffer 0 (ID: 0x100, Data: 0x10+offset).\n"
        "TX Thread 2: Transmits 10 CAN-FD messages using dedicated TX Buffer 1 (ID: 0x200, Data: 0x20+offset).\n"
        "Both threads run concurrently with equal priority (5) for fair scheduling.\n"
        "Uses TaskP_construct and SemaphoreP_constructCounting APIs for synchronization.\n"
        "Validates: 1) Concurrent TX stability 2) Buffer isolation 3) Thread safety 4) Zero data corruption",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM config (16 TX buffers available) */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number (not used by concurrent test - threads send their own) */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements (not used - threads create their own messages) */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_STRESS),
    },
    #if !defined (A53_CORE) && !defined (WKUP_R5_CORE)
    {
        TEST_ENABLE, 10493U,
        "MCAN_MT_004",
        "MCAN: Multi-Instance Test - MCAN0 and MCAN1 Concurrent Operation",
        "None", 
        "None",
        "Multi-instance test validating independent concurrent operation of MCAN0 and MCAN1.\n"
        "Instance 0 Thread: Transmits 5 CAN-FD messages on MCAN0 (ID: 0x100, Marker: 0xAA, Data: 0x10+offset).\n"
        "Instance 1 Thread: Transmits 5 CAN-FD messages on MCAN1 (ID: 0x200, Marker: 0xBB, Data: 0x20+offset).\n"
        "Both instances operate in internal loopback mode with independent configurations.\n"
        "Each thread uses dedicated TX buffers with ping-pong strategy (buffers 0 and 1).\n"
        "Uses TaskP_construct and SemaphoreP_constructCounting APIs for synchronization.\n"
        "Validates: 1) Independent instance operation 2) Concurrent multi-controller stability\n"
        "          3) Zero cross-instance interference 4) Proper resource isolation",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_STRESS),
    },
    #endif
    {
        TEST_ENABLE, 10494U,
        "MCAN_MT_005",
        "MCAN: TX FIFO + RX FIFO0 Concurrent Test - Separate Producer/Consumer Threads",
        "None", 
        "None",
        "TX FIFO + RX FIFO0 concurrent test validating FIFO operation with separate producer/consumer threads.\n"
        "TX FIFO Producer Thread: Transmits 5 CAN-FD messages via TX FIFO with sequential data patterns (Data: 0x10+offset).\n"
        "RX FIFO0 Consumer Thread: Receives and validates messages from RX FIFO0, checking data integrity.\n"
        "Both threads synchronize using binary semaphores (gTxDoneSem, gRxDoneSem) for TX/RX completion.\n"
        "Uses TaskP_construct and SemaphoreP_constructCounting/Binary APIs for thread coordination.\n"
        "TX FIFO Management: Uses MCAN_getTxFIFOQueStatus() to get putIdx and MCAN_writeMsgRam() to write.\n"
        "RX FIFO0 Management: Uses MCAN_getRxFIFOStatus() to get getIdx, MCAN_readMsgRam() to read,\n"
        "                      and MCAN_writeRxFIFOAck() to acknowledge messages.\n"
        "Validates: 1) TX FIFO transmission stability 2) RX FIFO0 reception correctness\n"
        "          3) FIFO index management (putIdx/getIdx) 4) End-to-end data integrity\n"
        "          5) Producer-Consumer pattern with FIFOs 6) Thread-safe FIFO operations",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters - use config 1 for proper BRS */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM config (must have TX FIFO and RX FIFO0 configured) */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number (must route to RX FIFO0) */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements (template for TX FIFO messages) */
            &canSTDIDFilter[10U], /* standard message ID filters - Use filter 10 which routes ID 0x04 to RX FIFO0 (sfec=0x01) */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask (includes TX_COMPLETE and RX_FIFO0_NEW_MSG) */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_STRESS),
    },
    {
        TEST_ENABLE, 10495U,
        "MCAN_MT_006",
        "MCAN: Parallel Classic CAN and CAN FD Transmission with TxEvent Validation",
        "None", 
        "None",
        "Parallel transmission test validating concurrent Classic CAN and CAN FD frame transmission.\n"
        "Classic CAN Thread: Transmits 5 Classic CAN frames (FDF=0, BRS=0) using TX Buffer 0 (ID: 0x100, MM: 0xCC).\n"
        "CAN FD Thread: Transmits 5 CAN FD frames (FDF=1, BRS=1) using TX Buffer 1 (ID: 0x200, MM: 0xFD).\n"
        "Both threads run concurrently with equal priority and validate TxEvent FIFO entries.\n"
        "Uses TaskP_construct and SemaphoreP_constructCounting APIs for synchronization.\n"
        "Each thread validates that TxEvent entries match transmitted frame parameters.\n"
        "Validates: 1) Parallel Classic CAN and CAN FD transmission stability\n"
        "          2) No frame corruption between Classic CAN and CAN FD modes\n"
        "          3) Correct TxEvent FIFO entries for both frame types\n"
        "          4) Message Marker (MM) field correctly recorded in TxEvent\n"
        "          5) FDF and BRS flags correctly recorded in TxEvent\n"
        "          6) Thread-safe concurrent transmission with different frame formats",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_STRESS),
    },
    #if !defined(MCU_FREERTOS_CORE)
    {
        TEST_ENABLE, 10874U,
        "MCAN_MT_007",
        "MCAN: Interrupt + Polling Multi-Thread TX/RX Test",
        "None",
        "None",
        "Multi-threaded test with one thread using interrupt-mode TX/RX and another using polling-mode TX/RX.\n"
        "Interrupt Thread: Uses TX buffer 0, ID 0x04 routed to dedicated RX buffer 0 via filter.\n"
        "  Sends 5 CAN-FD messages (ID: 0x04, MM: 0xAA, Data: 0xA0+offset).\n"
        "  Waits for TX complete via ISR semaphore, then polls NDAT1 for RX buffer 0\n"
        "  new-data and reads directly via MCAN_readMsgRam (dedicated buffer).\n"
        "Polling Thread: Uses TX buffer 1, ID 0x05 routed to RX FIFO 0 via filter.\n"
        "  Polls MCAN_getRxFIFOStatus() for RX FIFO0 new message, reads via MCAN_readMsgRam().\n"
        "  Sends 5 CAN-FD messages (ID: 0x05, MM: 0xBB, Data: 0xB0+offset).\n"
        "Both threads run concurrently with equal priority on the same MCAN instance (internal loopback).\n"
        "RX paths are isolated: dedicated RX buffer (interrupt) vs RX FIFO 0 (polling).\n"
        "Validates: 1) Coexistence of interrupt and polling modes on same MCAN instance\n"
        "          2) No data corruption between interrupt-driven and polled operations\n"
        "          3) TX buffer isolation (buffer 0 for interrupt, buffer 1 for polling)\n"
        "          4) RX path isolation (dedicated buffer vs FIFO 0)\n"
        "          5) End-to-end data integrity for both threads\n"
        "          6) Thread-safe concurrent access to MCAN peripheral",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType - internal loopback */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number - 2 filters: ID 0x04->RxBuf, ID 0x05->FIFO0 */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[11U], /* standard message ID filters - filter 11: ID 0x04->RxBuf0, filter 12: ID 0x05->FIFO0 */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & ~MCAN_INTR_SRC_RX_FIFO0_NEW_MSG & ~MCAN_INTR_SRC_RX_FIFO1_NEW_MSG),  /* Interrupt Mask - disable FIFO RX interrupts so ISR only fires for dedicated RX buffer */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_STRESS),
    },
    #endif
    {
        TEST_ENABLE, 10875U,
        "None",
        "MCAN: Multi-Threaded Filter Test - Classic Bitmask and Dual Filters with Concurrent Accept and Reject Validation",
        "Two threads run concurrently. Each thread tests its filter with both accepted\n"
        "and rejected IDs inline (no separate sequential phase):\n"
        "Thread 1: Classic bitmask filter (sfid1=0x100, sfid2=0x700) -> RX FIFO0.\n"
        "  Accept: 0x100, 0x101, 0x10F (bits[10:8]==0x1 -> pass).\n"
        "  Reject: 0x300, 0x500 (bits[10:8]!=0x1 -> caught by catch-all REJECT at slot 2).\n"
        "Thread 2: Dual filter (sfid1=0x200, sfid2=0x201) -> RX FIFO1.\n"
        "  Accept: 0x200, 0x201, 0x200 (exact dual match -> pass).\n"
        "  Reject: 0x202, 0x400 (no match -> caught by catch-all REJECT at slot 2).\n"
        "Filter slots: Slot 0: Classic->FIFO0, Slot 1: Dual->FIFO1, Slot 2: Range REJECT (catch-all).\n"
        "Rejection is enforced by the catch-all REJECT filter, not GFC.ANFS, for platform portability.",
        "None",
        "1. Thread 1 must receive accepted IDs 0x100, 0x101, 0x10F in FIFO0 with correct data.\n"
        "2. Thread 1 must confirm rejected IDs 0x300, 0x500 do NOT appear in FIFO0.\n"
        "3. Thread 2 must receive accepted IDs 0x200, 0x201, 0x200 in FIFO1 with correct data.\n"
        "4. Thread 2 must confirm rejected IDs 0x202, 0x400 do NOT appear in FIFO1.\n"
        "5. No cross-contamination between FIFO0 and FIFO1.\n"
        "6. Each thread's pass counter must equal 5 (3 accept + 2 reject) and error counter must be 0.\n"
        "7. All messages must complete without protocol errors or timeout.\n"
        "8. Thread synchronization must work correctly without deadlocks.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            5U, /* iteration count for tx - each thread sends 5 messages */
            &canFDBitTimings[0U], /* mcan module bit timing parameters - 1Mbps/5Mbps */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM config - FIFO0, FIFO1, and buffers */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            3U, /* tx message number - 2 threads use TX buffers 0 and 1 */
            3U, /* standard ID message filter number - Classic, Dual, catch-all REJECT */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    #endif /* #if defined (R5_FREERTOS_CORE) */

    #ifdef MCAN_ECC_SUPPORTED
    {
    TEST_ENABLE, 10871U,
    "None",
    "MCAN: NoCpy Non-4-Aligned DLC test",
    "Covers MCAN_writeMsgRamNoCpy remaining-bytes path",
    "None",
    "Verify loopback payload match for DLC=1,2,3,5,6,7",
    IPU,
    {
        (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
        1U, /* iteration count */
        &canFDBitTimings[0U], /* bit timings */
        &canFDInitParams[0U], /* init params */
        &canFDConfigParams[1U], /* config params */
        &canFDRAMConfigParams[2U], /* ram config */
        &canFDECCConfigParams[0U], /* ecc config */
        &canFDECCErrForceConfigParams[0U], /* ecc force params */
        1U, /* tx message number */
        1U, /* std id filter num */
        0U, /* ext id filter num */
        &canTxMSG[10U], /* tx message(s) - adjust or add new message if needed */
        &canSTDIDFilter[0U],
        &canEXTIDFilter[0U],
        (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND), /* intr enable */
        (MCAN_INTR_MASK_ALL),  /* intr line select mask */
        (MCAN_INTR_LINE_NUM_0)  /* intr line */
    },
    PRINT_ENABLE,
    (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 10872U,
        "None",
        "MCAN: ECC Interrupt Status Get/Clear API Validation Test",
        "This test directly validates MCAN_eccGetIntrStatus and MCAN_eccClearIntrStatus APIs.\n"
        "It forces SEC and DED ECC errors via self-test, then verifies that:\n"
        "1) MCAN_eccGetIntrStatus returns pending status after error injection\n"
        "2) MCAN_eccClearIntrStatus clears the pending status\n"
        "3) Invalid errType parameter is handled gracefully (default branch)",
        "None",
        "1. Initial SEC/DED interrupt status should be clear (0).\n"
        "2. After forcing SEC error, MCAN_eccGetIntrStatus(SEC) should return non-zero.\n"
        "3. After clearing, MCAN_eccGetIntrStatus(SEC) should return 0.\n"
        "4. After forcing DED error, MCAN_eccGetIntrStatus(DED) should return non-zero.\n"
        "5. After clearing, MCAN_eccGetIntrStatus(DED) should return 0.\n"
        "6. Invalid errType should return 0 and not crash.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    #endif /* #ifdef MCAN_ECC_SUPPORTED */
    {
        TEST_ENABLE, 10870U,
        "None",
        "MCAN: Mixed Extended ID Classic CAN and CAN-FD Sequential Transmission Test",
        "This test validates sequential transmission of Extended ID frames with mixed Classic CAN and CAN-FD formats.\n"
        "The test transmits 3 messages in sequence (non-concurrent):\n"
        "1) Extended ID (29-bit) + Classic CAN + 8 bytes data\n"
        "2) Extended ID (29-bit) + CAN-FD + 16 bytes data + BRS\n"
        "3) Extended ID (29-bit) + CAN-FD + 64 bytes data + BRS\n"
        "Each message is transmitted, verified via loopback, and checked for correctness before the next transmission.",
        "None",
        "1. All 3 messages should transmit successfully in sequence.\n"
        "2. Each transmitted message should match the received message (ID, format, data).\n"
        "3. No error counters should be incremented during transmission.\n"
        "4. Protocol status should show no errors.\n"
        "5. Test demonstrates MCAN can handle Extended ID with both Classic and FD formats in same sequence.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number - using 3 buffers internally */
            0U, /* standard ID message filter number - not used */
            1U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    /* randomly hange the console log*/
    #if !defined (MCU_M4_CORE)
    {
        TEST_ENABLE, 10868U,
        "None",
        "MCAN: Explicit Buffer Numbers Validation - TX/RX Isolation and No Cross-Write Test",
        "This test validates that explicit buffer numbers (1, 2, 3, ...) correctly store and\n"
        "transmit/receive data without cross-buffer contamination. The test:\n"
        "1) Writes unique data patterns to multiple dedicated TX buffers (buffers 0, 1, 2, 3)\n"
        "2) Transmits from each buffer with unique message IDs\n"
        "3) Receives into corresponding dedicated RX buffers\n"
        "4) Verifies each RX buffer contains only its intended data (no cross-write)\n"
        "5) Validates buffer isolation by checking adjacent buffers remain unaffected",
        "None",
        "1. Each TX buffer should transmit its unique data pattern correctly.\n"
        "2. Each RX buffer should receive only the intended message for its buffer number.\n"
        "3. RX content must exactly match the corresponding TX content.\n"
        "4. No cross-write between buffers - adjacent buffers should not be corrupted.\n"
        "5. Buffer isolation is maintained throughout multiple transmit/receive cycles.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            4U, /* iteration count for tx - test with 4 different buffers */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM config - includes FIFO0, FIFO1, and dedicated buffers */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
    #endif
    {
        TEST_ENABLE, 10869U,
        "None",
        "MCAN: Combined Filter Types Test - Classic, Dual, and Bit Mask Filters with FIFO0, FIFO1, and Buffer",
        "This test validates simultaneous use of different filter types directing messages to\n"
        "different reception destinations. The test:\n"
        "1) Configures Classic Filter (exact match) to store messages in RX FIFO0\n"
        "2) Configures Dual Filter (match ID1 or ID2) to store messages in RX FIFO1\n"
        "3) Configures Bit Mask Filter (classic with mask) to store messages in Dedicated RX Buffer\n"
        "4) Sends messages matching each filter type\n"
        "5) Verifies each message is received in the correct destination (FIFO0, FIFO1, or Buffer)\n"
        "6) Validates data integrity for all received messages",
        "None",
        "1. Message matching Classic Filter should be received in RX FIFO0 with correct data.\n"
        "2. Message matching Dual Filter should be received in RX FIFO1 with correct data.\n"
        "3. Message matching Bit Mask Filter should be received in Dedicated RX Buffer with correct data.\n"
        "4. All three filter types should work simultaneously without interference.\n"
        "5. No protocol errors or error counters should be incremented.\n"
        "6. Data patterns in received messages must match transmitted data exactly.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOPBACK), /* testType */
            1U, /* iteration count for tx */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            3U, /* standard ID message filter number - 3 filters (Classic, Dual, Bit Mask) */
            0U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
    },
};

uint32_t bitTimingsListSize = (sizeof(canFDBitTimings) / sizeof(MCAN_BitTimingParams));

#endif /* #ifndef ST_MCAN_TEST_CASES_H_ */
