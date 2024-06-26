/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
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

/** \file ext_otp.h
 *
 *   \brief This file contains extended OTP area access APIs.
 */

#ifndef EXT_OTP_INC_H_
#define EXT_OTP_INC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macro definitions */
#define NUM_BITS_PER_OTP_ROW 	        (25U)
#define OTP_COL_OFFSET       	        (2U)
#define OTP_ROW_FULL_MASK	            (0x01FFFFFFU)
#define MMR_SIZE_BITS			        (32U)
#define EXT_OTP_MAX_MMRS		        (32U)

/* USB VID/PID related defines */
#define EXT_OTP_ID0_FLAG_MASK	        (0x0000000FU)
#define EXT_OTP_ID0_FLAG_SHIFT	        (0U)
#define EXT_OTP_ID1_FLAG_MASK	        (0x000000F0U)
#define EXT_OTP_ID1_FLAG_SHIFT	        (4U)

/* Other defines(can be used for MAC Device ID) */
#define EXT_OTP_ID2_FLAG_MASK	        (0x00000F00U)
#define EXT_OTP_ID2_FLAG_SHIFT	        (8U)
#define EXT_OTP_ID3_FLAG_MASK	        (0x0000F000U)
#define EXT_OTP_ID3_FLAG_SHIFT	        (12)

#define EXT_OTP_ROM_MAGIC_WORD_MASK		(0xFFFF0000U)
#define EXT_OTP_ROM_MAGIC_WORD_SHIFT	(16U)
#define EXT_OTP_ROM_MAGIC_WORD			(0xEBC8U)

#define EXT_OTP_ID0_DATA_MASK	        (0xFFFF0000U)
#define EXT_OTP_ID0_DATA_SHIFT	        (16U)
#define EXT_OTP_ID1_DATA_MASK	        (0x0000FFFFU)
#define EXT_OTP_ID1_DATA_SHIFT	        (0U)
#define EXT_OTP_ID2_DATA_MASK	        (0xFFFF0000U)
#define EXT_OTP_ID2_DATA_SHIFT	        (16U)
#define EXT_OTP_ID3_DATA_MASK	        (0x0000FFFFU)
#define EXT_OTP_ID3_DATA_SHIFT	        (0U)

#define EXT_OTP_FLAG_USB_VID	        (1U)
#define EXT_OTP_FLAG_USB_PID	        (2U)
#define EXT_OTP_FLAG_MAC_CHUNK0	        (5U)
#define EXT_OTP_FLAG_MAC_CHUNK1	        (6U)
#define EXT_OTP_FLAG_MAC_CHUNK2	        (7U)

#define CTRL_MMR_USB_VID_MASK	        (0x0000FFFFU)
#define CTRL_MMR_USB_VID_SHIFT	        (0U)
#define CTRL_MMR_USB_PID_MASK	        (0xFFFF0000U)
#define CTRL_MMR_USB_PID_SHIFT	        (16U)
#define CTRL_MMR_MAC_CHUNK0_MASK	    (0x0000FFFFU)
#define CTRL_MMR_MAC_CHUNK0_SHIFT	    (0U)
#define CTRL_MMR_MAC_CHUNK1_MASK	    (0xFFFF0000U)
#define CTRL_MMR_MAC_CHUNK1_SHIFT	    (16U)
#define CTRL_MMR_MAC_CHUNK2_MASK	    (0x0000FFFFU)
#define CTRL_MMR_MAC_CHUNK2_SHIFT	    (0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void ext_otp_setVpp(void);
int32_t ext_otp_readMmr(uint8_t mmrIdx, uint32_t *mmrVal);
int32_t ext_otp_writeRow(uint8_t rowIdx, uint32_t rowVal, uint32_t rowMask, uint32_t *rowValRdBk );
int32_t ext_otp_writeMmr(uint32_t mmrIdx, uint32_t mmrVal);
int32_t ext_otp_writeUsbVidPid(uint32_t usbVID, uint32_t usbPID);
int32_t ext_otp_printMmrs(void);
int32_t ext_otp_getUsbVid(uint32_t *usb_vid);
int32_t ext_otp_getUsbPid(uint32_t *usb_pid);
int32_t ext_otp_lockRow(uint8_t rowIdx, uint8_t hwWriteLock, uint8_t hwReadLock);
int32_t ext_otp_getRowLockStatus(uint8_t rowIdx, uint8_t *globalsoftLock, uint8_t *hwWriteLock, uint8_t *hwReadLock);
int32_t ext_otp_softLockWriteGlobal(void);

#ifdef __cplusplus
}
#endif

#endif /* EXT_OTP_INC_H_ */
