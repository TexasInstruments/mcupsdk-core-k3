/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
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
 *  \file imx219_drv.h
 *
 *  \brief IMX219 Baremetal Driver for R5F
 *
 */

#ifndef _IMX219_DRV_H_
#define _IMX219_DRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/tistdtypes.h>
#include <drivers/i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define IMX219_OK         0
#define IMX219_NOT_OK    -1

#define IMX219_REG_X_ADD_STA_A      0x0164
#define IMX219_REG_X_ADD_END_A      0x0166
#define IMX219_REG_Y_ADD_STA_A      0x0168
#define IMX219_REG_Y_ADD_END_A      0x016a
#define IMX219_REG_X_OUTPUT_SIZE    0x016c
#define IMX219_REG_Y_OUTPUT_SIZE    0x016e
#define IMX219_REG_TP_WINDOW_WIDTH  0x0624
#define IMX219_REG_TP_WINDOW_HEIGHT 0x0626

/* IMX219 recommended setting */
#define IMX219_CONFIG       \
{   \
    {3, 0x01, 0x00, 1, 0},  \
    {2, 0x01, 0x00, 0, 0},  \
    {1, 0, 0, 0, 0},        \
    \
    {3, 0x01, 0x00, 0, 0},  \
    {2, 0x01, 0x00, 0, 0},  \
    {1, 0, 0, 0, 0},        \
    \
    {3, 0x01, 0x14, 1, 0},  \
    \
    {4, (uint8_t)((IMX219_REG_TP_WINDOW_WIDTH >> 8) & 0xFF), (uint8_t)(IMX219_REG_TP_WINDOW_WIDTH & 0xFF), (uint8_t)((3280 >> 8) & 0xFF), (uint8_t)(3280 & 0xFF)}, \
    {4, (uint8_t)((IMX219_REG_TP_WINDOW_HEIGHT >> 8) & 0xFF), (uint8_t)(IMX219_REG_TP_WINDOW_HEIGHT & 0xFF), (uint8_t)((2464 >> 8) & 0xFF), (uint8_t)(2464 & 0xFF)}, \
    \
    {4, 0x01, 0x8C, (uint8_t)((0x0808 >> 8) & 0xFF), (uint8_t)(0x0808 & 0xFF)},         \
    {3, 0x03, 0x09, (uint8_t)(0x0808 & 0xFF), 0},                                       \
    \
    {4, 0x01, 0x60, (uint8_t)((0x0dc6 >> 8) & 0xFF), (uint8_t)(0x0dc6 & 0xFF)}, \
    \
    {4, 0x01, 0x5A, (uint8_t)((0x0640 >> 8) & 0xFF), (uint8_t)(0x0640 & 0xFF)},         \
    \
    {4, 0x06, 0x02, (uint8_t)((0x3FF >> 8) & 0xFF), (uint8_t)(0x3FF & 0xFF)},           \
    \
    {4, 0x06, 0x04, (uint8_t)((0x3FF >> 8) & 0xFF), (uint8_t)(0x3FF & 0xFF)},           \
    \
    {4, 0x06, 0x06, (uint8_t)((0x3FF >> 8) & 0xFF), (uint8_t)(0x3FF & 0xFF)},           \
    \
    {4, 0x06, 0x08, (uint8_t)((0x3FF >> 8) & 0xFF), (uint8_t)(0x3FF & 0xFF)},           \
}

#endif /* _IMX219_DRV_H_ */
