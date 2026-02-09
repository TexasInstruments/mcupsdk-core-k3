/*
 * Copyright (C) 2022-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
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
 *
 */

/**
 *  \defgroup DRV_PINMUX_MODULE APIs for PINMUX
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the pinmux module.
 *
 *  @{
 */

/**
 *  \file pinmux.h
 *
 *  \brief PINMUX Driver API/interface file.
 *
 * \brief  This file contains pad configure register offsets and bit-field
 *         value macros for different configurations,
 *
 *           BIT[21]        TXDISABLE       disable the pin's output driver
 *           BIT[18]        RXACTIVE        enable the pin's input buffer (typically kept enabled)
 *           BIT[17]        PULLTYPESEL     set the iternal resistor pull direction high or low (if enabled)
 *           BIT[16]        PULLUDEN        internal resistor disable (0 = enabled / 1 = disabled)
 *           BIT[3:0]       MUXMODE         select the desired function on the given pin
 */

#ifndef PINMUX_AM275X_H_
#define PINMUX_AM275X_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 *  \anchor Pinmux_DomainId_t
 *  \name Pinmux Domain ID
 *  @{
 */
#define PINMUX_DOMAIN_ID_MAIN          (0U)
#define PINMUX_DOMAIN_ID_MCU           (1U)
/** @} */

/** \brief Macro to mark end of pinmux config array */
#define PINMUX_END                      (-1)

/** \brief Pin mode - it is at 0th bit. No shift requried */
#define PIN_MODE(mode)                  ((uint32_t) mode)
/** \brief Resistor enable */
#define PIN_PULL_DISABLE                (((uint32_t) 0x1U) << 16U)
/** \brief Pull direction */
#define PIN_PULL_DIRECTION              (((uint32_t) 0x1U) << 17U)
/** \brief Receiver enable */
#define PIN_INPUT_ENABLE                (((uint32_t) 0x1U) << 18U)
/** \brief Drive strength */
#define	PIN_DRIVE_STRENGTH(strength)    ((uint32_t)(strength) << 19U)
/** \brief Driver disable */
#define PIN_OUTPUT_DISABLE              (((uint32_t) 0x1U) << 21U)
/** \brief Wakeup enable */
#define PIN_WAKEUP_ENABLE               (((uint32_t) 0x1U) << 29U)

#define PIN_DRV_STR_FAST                PIN_DRIVE_STRENGTH(2U)
#define PIN_DRV_STR_NOMINAL             PIN_DRIVE_STRENGTH(0U)


/** \brief Main domain pad config register offset in control module */
enum Pinmux_MainOffsets
{
    PIN_OSPI0_CLK        = 0x000,
    PIN_OSPI0_LBCLKO     = 0x004,
    PIN_OSPI0_DQS        = 0x008,
    PIN_OSPI0_D0         = 0x00C,
    PIN_OSPI0_D1         = 0x010,
    PIN_OSPI0_D2         = 0x014,
    PIN_OSPI0_D3         = 0x018,
    PIN_OSPI0_D4         = 0x01C,
    PIN_OSPI0_D5         = 0x020,
    PIN_OSPI0_D6         = 0x024,
    PIN_OSPI0_D7         = 0x028,
    PIN_OSPI0_CSN0       = 0x02C,
    PIN_OSPI0_CSN1       = 0x030,
    PIN_OSPI0_CSN2       = 0x034,
    PIN_OSPI0_CSN3       = 0x038,
    PIN_MCASP0_ACLKX     = 0x03C,
    PIN_MCASP0_AFSX      = 0x040,
    PIN_MCASP0_AXR0      = 0x044,
    PIN_MCASP0_AXR1      = 0x048,
    PIN_MCASP0_AXR2      = 0x04C,
    PIN_MCASP0_AXR3      = 0x050,
    PIN_MCASP0_AXR4      = 0x054,
    PIN_MCASP0_AXR5      = 0x058,
    PIN_MCASP0_AXR6      = 0x05C,
    PIN_MCASP0_AXR7      = 0x060,
    PIN_MCASP0_AXR8      = 0x064,
    PIN_MCASP0_AXR9      = 0x068,
    PIN_MCASP0_AXR10     = 0x06C,
    PIN_MCASP0_AXR11     = 0x070,
    PIN_MCASP0_AXR12     = 0x074,
    PIN_MCASP0_AXR13     = 0x078,
    PIN_MCASP0_AXR14     = 0x07C,
    PIN_MCASP0_AXR15     = 0x084,
    PIN_MCASP1_ACLKX     = 0x088,
    PIN_MCASP1_AFSX      = 0x08C,
    PIN_MCASP1_AXR0      = 0x090,
    PIN_MCASP1_AXR1      = 0x094,
    PIN_MCASP1_AXR2      = 0x098,
    PIN_MCASP1_AXR3      = 0x09C,
    PIN_MCASP2_ACLKX     = 0x0A0,
    PIN_MCASP2_AFSX      = 0x0A4,
    PIN_MCASP2_AXR0      = 0x0A8,
    PIN_MCASP2_AXR1      = 0x0AC,
    PIN_MCASP2_AXR2      = 0x0B0,
    PIN_MCASP2_AXR3      = 0x0B4,
    PIN_MCASP2_AXR4      = 0x0B8,
    PIN_MCASP2_AXR5      = 0x0BC,
    PIN_MCASP3_ACLKX     = 0x0C0,
    PIN_MCASP3_AFSX      = 0x0C4,
    PIN_MCASP3_AXR0      = 0x0C8,
    PIN_MCASP3_AXR1      = 0x0CC,
    PIN_MCASP3_AXR2      = 0x0D0,
    PIN_MCASP3_AXR3      = 0x0D4,
    PIN_MCASP4_ACLKX     = 0x0E0,
    PIN_MCASP4_AFSX      = 0x0E4,
    PIN_MCASP4_AXR0      = 0x0E8,
    PIN_MCASP4_AXR1      = 0x0EC,
    PIN_MCASP4_AXR2      = 0x0F0,
    PIN_MLB0_MLBSIG      = 0x0FC,
    PIN_MLB0_MLBCLK      = 0x100,
    PIN_MLB0_MLBDAT      = 0x104,
    PIN_OSPI1_CLK        = 0x108,
    PIN_OSPI1_LBCLKO     = 0x10C,
    PIN_OSPI1_DQS        = 0x110,
    PIN_OSPI1_D0         = 0x114,
    PIN_OSPI1_D1         = 0x118,
    PIN_OSPI1_D2         = 0x11C,
    PIN_OSPI1_D3         = 0x120,
    PIN_OSPI1_CSN0       = 0x124,
    PIN_RGMII1_TX_CTL    = 0x12C,
    PIN_RGMII1_TXC       = 0x130,
    PIN_RGMII1_TD0       = 0x134,
    PIN_RGMII1_TD1       = 0x138,
    PIN_RGMII1_TD2       = 0x13C,
    PIN_RGMII1_TD3       = 0x140,
    PIN_RGMII1_RX_CTL    = 0x144,
    PIN_RGMII1_RXC       = 0x148,
    PIN_RGMII1_RD0       = 0x14C,
    PIN_RGMII1_RD1       = 0x150,
    PIN_RGMII1_RD2       = 0x154,
    PIN_RGMII1_RD3       = 0x158,
    PIN_MDIO0_MDIO       = 0x15C,
    PIN_MDIO0_MDC        = 0x160,
    PIN_RGMII2_TX_CTL    = 0x164,
    PIN_RGMII2_TXC       = 0x168,
    PIN_RGMII2_TD0       = 0x16C,
    PIN_RGMII2_TD1       = 0x170,
    PIN_RGMII2_TD2       = 0x174,
    PIN_OSPI1_CSN1       = 0x128,
    PIN_RGMII2_TD3       = 0x178,
    PIN_RGMII2_RX_CTL    = 0x17C,
    PIN_RGMII2_RXC       = 0x180,
    PIN_RGMII2_RD0       = 0x184,
    PIN_RGMII2_RD1       = 0x188,
    PIN_RGMII2_RD2       = 0x18C,
    PIN_RGMII2_RD3       = 0x190,
    PIN_SPI2_D0          = 0x194,
    PIN_SPI2_D1          = 0x198,
    PIN_SPI2_CS2         = 0x19C,
    PIN_AUDIO_EXT_REFCLK0    = 0x1A0,
    PIN_SPI2_CS1         = 0x1A4,
    PIN_SPI2_CS3         = 0x1A8,
    PIN_SPI2_CS0         = 0x1AC,
    PIN_SPI2_CLK         = 0x1B0,
    PIN_SPI0_CS0         = 0x1B4,
    PIN_SPI0_CS1         = 0x1B8,
    PIN_SPI0_CLK         = 0x1BC,
    PIN_SPI0_D0          = 0x1C0,
    PIN_SPI0_D1          = 0x1C4,
    PIN_UART0_RXD        = 0x1C8,
    PIN_UART0_TXD        = 0x1CC,
    PIN_UART0_CTSN       = 0x1D0,
    PIN_UART0_RTSN       = 0x1D4,
    PIN_MCAN0_TX         = 0x1D8,
    PIN_MCAN0_RX         = 0x1DC,
    PIN_I2C0_SCL         = 0x1E0,
    PIN_I2C0_SDA         = 0x1E4,
    PIN_I2C1_SCL         = 0x1E8,
    PIN_I2C1_SDA         = 0x1EC,
    PIN_EXT_REFCLK1      = 0x1F0,
    PIN_EXTINTN          = 0x1F4,
    PIN_MMC0_DAT7        = 0x1F8,
    PIN_MMC0_DAT6        = 0x1FC,
    PIN_MMC0_DAT5        = 0x200,
    PIN_MMC0_DAT4        = 0x204,
    PIN_MMC0_DAT3        = 0x208,
    PIN_MMC0_DAT2        = 0x20C,
    PIN_MMC0_DAT1        = 0x210,
    PIN_MMC0_DAT0        = 0x214,
    PIN_MMC0_CLK         = 0x218,
    PIN_MMC0_CMD         = 0x220,
    PIN_SPI1_CS0         = 0x224,
    PIN_SPI1_CS1         = 0x228,
    PIN_SPI1_CLK         = 0x22C,
    PIN_SPI1_D0          = 0x230,
    PIN_SPI1_D1          = 0x234,
    PIN_GPIO1_47         = 0x23C,
    PIN_GPIO1_48         = 0x240,
    PIN_GPIO1_49         = 0x244,
    PIN_USB0_DRVVBUS     = 0x254,
    PIN_GPIO1_72         = 0x2AC,
    PIN_ADC0_AIN0        = 0x2B0,
    PIN_ADC0_AIN1        = 0x2B4,
    PIN_ADC0_AIN2        = 0x2B8,
    PIN_ADC0_AIN3        = 0x2BC,
    PIN_ADC0_AIN4        = 0x2C0,
    PIN_ADC0_AIN5        = 0x2C4,
    PIN_ADC0_AIN6        = 0x2C8,
    PIN_ADC0_AIN7        = 0x2CC,
    PIN_OSPI1_D4         = 0x2D0,
    PIN_OSPI1_D5         = 0x2D4,
    PIN_OSPI1_D6         = 0x2D8,
    PIN_OSPI1_D7         = 0x2DC
};

/** \brief Wakeup domain pad config register offset in control module */
enum Pinmux_McuOffsets
{
	PIN_EMU1            = 0x07C,
	PIN_EMU0            = 0x078,
	PIN_WKUP_CLKOUT0    = 0x084,
	PIN_PMIC_LPM_EN0    = 0x080,
	PIN_WKUP_I2C0_SDA   = 0x050,
	PIN_WKUP_I2C0_SCL   = 0x04C,
	PIN_MCU_GPIO0_16    = 0x040,
	PIN_MCU_GPIO0_15    = 0x03C,
	PIN_MCU_GPIO0_14    = 0x038,
	PIN_MCU_GPIO0_13    = 0x034,
	PIN_WKUP_UART0_RTSN = 0x030,
	PIN_WKUP_UART0_CTSN = 0x02C,
	PIN_WKUP_UART0_TXD  = 0x028,
	PIN_WKUP_UART0_RXD  = 0x024,
	PIN_MCU_GPIO0_8     = 0x020,
	PIN_MCU_GPIO0_7     = 0x01C,
	PIN_MCU_GPIO0_6     = 0x018,
	PIN_MCU_GPIO0_5     = 0x014,
	PIN_MCU_GPIO0_4     = 0x010,
	PIN_MCU_GPIO0_3     = 0x00C,
	PIN_MCU_GPIO0_2     = 0x008,
	PIN_WKUP_TIMER_IO1  = 0x004,
	PIN_WKUP_TIMER_IO0  = 0x000
};


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Structure defining the pin configuration parameters */
typedef struct Pinmux_PerCfg
{
    int16_t     offset;
    /**< Register offset for configuring the pin.
     *   Refer \ref Pinmux_MainOffsets and \ref Pinmux_McuOffsets.
     *   Set this to #PINMUX_END to demark the end of configuration array */
    uint32_t    settings;
    /**< Value to be configured.
     *   Active mode configurations like mux mode, pull resistor and
     *   buffer mode.
     *
     *   To set a value use like   : "| PIN_PULL_DISABLE"
     *   To reset a value use like : "& (~PIN_PULL_DIRECTION)"
     *
     *   For example,
     *   PIN_MODE(7) | ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION)
     */
} Pinmux_PerCfg_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This API configures the pinmux based on the domain
 *
 *  \param  pinmuxCfg   Pointer to list of pinmux configuration array.
 *                      This parameter cannot be NULL and the last entry should
 *                      be initialized with #PINMUX_END so that this function
 *                      knows the end of configuration.
 *  \param  domainId    Domain ID to set pinmux configuration.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_config(const Pinmux_PerCfg_t *pinmuxCfg, uint32_t domainId);

/**
 *  \brief  This API unlocks the PAD config control MMRs for the given domain
 *
 *  \param  domainId    Domain ID to unlock the PAD config MMRs.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_unlockMMR(uint32_t domainId);

/**
 *  \brief  This API locks the PAD config control MMRs for the given domain
 *
 *  \param  domainId    Domain ID to lock the PAD config MMRs.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_lockMMR(uint32_t domainId);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef PINMUX_AM275X_H_ */

/** @} */


