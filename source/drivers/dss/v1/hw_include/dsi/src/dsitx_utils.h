/******************************************************************************
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Private declarations for MIPI DSITX Host Core Driver helper functions.
 * These functions are mainly dedicated for Core Driver internal use.
 *
 *****************************************************************************/

#ifndef DSITX_UTILS_H_
# define DSITX_UTILS_H_



/**
 * Reads 1 to 4 bytes from given address and returns them in
 * 32-bit little endian format.
 * This function helps the driver write data to the FIFO registers
 * from the data buffer.
 * @param buff Pointer to buffer from which bytes will be read.
 * @param size Number of bytes to read from buffer.
 */
uint32_t ReadFromBuff32le(const uint8_t *buff, uint32_t size);

/**
 * Writes 1 to 4 bytes to given address from the given 32-bit value.
 * This function helps the driver read data from the FIFO registers
 * to the data buffer.
 * @param buff Pointer to buffer to which bytes will be written in the
 * little endian format.
 * @param size Number of bytes to write to buffer from the val value.
 * @param val Value to write.
 */
void WriteToBuff32le(uint8_t *buff, uint32_t size, uint32_t val);

#endif /* DSITX_UTILS_H_ */
