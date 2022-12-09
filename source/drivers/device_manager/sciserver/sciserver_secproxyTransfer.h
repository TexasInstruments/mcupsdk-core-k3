/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 */

/**
 * \file sciserver_sec_proxy_transfer.h
 *
 * \brief Secure Proxy Transfer (Messaging) APIs
 */

#ifndef SEC_PROXY_TRANSFER_H
#define SEC_PROXY_TRANSFER_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Check to see if a message is pending on a Rx sec proxy thread
 *
 * \param rx_config_id - Index into gSciserverSecureProxyRxConfigurations
 *
 * \return 0 if there is pending message, else returns corresponding error
 * result.
 */
int32_t Sciserver_SproxyMsgIsPending(uint16_t rx_config_id);

/**
 * \brief Find the Sender's Host ID for a pending message
 *
 * Since every Tx thread is mapped to an Rx thread, when we get a message,
 * the hardware mechanisms allow us to identify the tx thread that send
 * the original message. This allows a lookup into what the exact host ID
 * should have been for the transmitting party. This, in conjunction with
 * appropriate firewall settings, should detect a spoof message being
 * send on a secure proxy thread that is incorrect.
 *
 * \param rx_config_id - Index into gSciserverSecureProxyRxConfigurations
 * \param sender_host_id - Returns the host ID from SoC database
 *
 * \return 0 if there was a pending message and sender_host_id is valid,
 * else, returns corresponding error value.
 */
int32_t Sciserver_SproxyMsgGetSenderHostId(uint16_t rx_config_id,
                                           uint32_t *sender_host_id);

/**
 * \brief read a message (but dont ack)
 *
 * This reads a message from a Rx secure proxy thread, without notifying the
 * hardware doorbell register that the message read is complete.
 *
 * \param rx_config_id - Index into gSciserverSecureProxyRxConfigurations
 * \param rx_buff - Rx buffer
 * \param rx_num_words - number of words to read (sizeof(uint32_t) elements)
 *
 * \return 0 if there was a pending message and the rx_buff now has
 * rx_num_words of data read from the secure proxy, else returns corresponding
 * error.
 */
int32_t Sciserver_SproxyMsgRead(uint16_t rx_config_id,
                                uint32_t *rx_buff,
                                uint32_t rx_num_words);

/**
 * \brief read a portion of the message (but dont ack)
 *
 * This is a companion API to \ref Sciserver_SproxyMsgRead. It can be used to read
 * specific portions of the message from Rx secure proxy thread without always starting at offset 0.
 *
 * \param rx_config_id - Index into gSciserverSecureProxyRxConfigurations
 * \param rx_buff - Rx buffer
 * \param rx_num_words - number of words to read (sizeof(uint32_t) elements)
 * \param offset - word offset from which we need to read the message.
 *
 * \return 0 if there was a pending message and the rx_buff now has
 * rx_num_words of data read from the secure proxy, else returns corresponding
 * error.
 */
int32_t Sciserver_SproxyMsgReadAtOffset(uint16_t rx_config_id,
                                        uint32_t *rx_buff,
                                        uint32_t rx_num_words,
                                        uint32_t offset);

/**
 * \brief acknowledge receipt of message to hardware
 *
 * *if* there was a pending message, let secure proxy hardware know that the
 * message has been consumed and to make the next message available (if any).
 *
 * \param rx_config_id - Index into gSciserverSecureProxyRxConfigurations
 *
 * \return 0 if there was a pending message and has been successfully acked,
 * else return corresponding error.
 */
int32_t Sciserver_SproxyMsgAck(uint16_t rx_config_id);

/**
 * \brief Check to see if we can indeed transmit a message
 *
 * Check secure proxy thread to see if we have enough credits to be able to
 * send at least 1 message.
 *
 * \param tx_config_id - Index into Sciserver_SecureProxyTxConfigurations
 *
 * \return 0 if we have space for at least 1 message, however, if we have
 * used up all hardware credits or error conditions, return corresponding
 * error value.
 */
int32_t Sciserver_SproxyCanSend(uint16_t tx_config_id);

/**
 * \brief send a message (stage it, but don't complete transmissions)
 *
 * This stages a message for transmission on a Tx secure proxy thread, without
 * notifying the hardware doorbell register that the message is ready to be
 * transmitted. So there is a very good chance that you may overwrite a staged
 * message with another staged message if \ref Sciserver_SproxyMsgFinish was failed to
 * be called in the middle.
 *
 * This API does not provide mutual exclusion for threads or against race against
 * \ref Sciserver_SproxyMsgFinish
 *
 * \param tx_config_id - Index into Sciserver_SecureProxyTxConfigurations
 * \param tx_buff - Transmit buffer
 * \param tx_num_words - number of words to write (sizeof(uint32_t) elements)
 *
 * \return 0 if message has been successfully been staged (NOTE: credit
 * is not decremented until confirmed), else returns corresponding error
 */
int32_t Sciserver_SproxyMsgSend(uint16_t tx_config_id,
                                uint32_t *tx_buff,
                                uint32_t tx_num_words);


/**
 * \brief send a message (stage it, but don't complete transmissions)
 *
 * This is a companion API to \ref Sciserver_SproxyMsgSend. It can be used to construct
 * a secure proxy message in parts as opposed to \ref Sciserver_SproxyMsgSend which always
 * overwrites the existing data.
 *
 * The parameter offset can be used to control where we start writing to into the
 * secure proxy data registers. When offset is 0, this function is equivalent to
 * \ref Sciserver_SproxyMsgSend.
 *
 * This API does not provide mutual exclusion for threads or against race against
 * \ref Sciserver_SproxyMsgFinish
 *
 * \param tx_config_id - Index into Sciserver_SecureProxyTxConfigurations
 * \param tx_buff - Transmit buffer
 * \param tx_num_words - number of words to write (sizeof(uint32_t) elements)
 * \param offset - number of words to index into the secure proxy registers when writing.
 *
 * \return 0 if message has been successfully been staged (NOTE: credit
 * is not decremented until confirmed), else returns corresponding error
 */
int32_t Sciserver_SproxyMsgSendAtOffset(uint16_t tx_config_id,
                                        uint32_t *tx_buff,
                                        uint32_t tx_num_words,
                                        uint32_t offset);

/**
 * \brief Confirm to hardware to transmit a staged message.
 *
 * NOTE: This API does not verify to make sure an actual data was made
 * available in the secure proxy via \ref Sciserver_SproxyMsgSend. Any call to this
 * API will result in reduction by 1 of available credits.
 *
 * This API does not provide mutual exclusion for threads
 *
 * \param tx_config_id - Index into Sciserver_SecureProxyTxConfigurations
 *
 * \return 0 if message has been successfully transmitted, else return
 * corresponding message.
 */
int32_t Sciserver_SproxyMsgFinish(uint16_t tx_config_id);

/**
 * \brief Function to trivially verify if the provided host_id is a valid ID
 *
 * \param host_id - Host ID to verify
 *
 * \return
 *  -EVINAL if the host ID is not valid
 *  CSL_PASS if the host ID is valid
 */
int32_t Sciserver_SproxyMsgValidateHostId(uint16_t host_id);

/**
 * \brief Retrieve the Tx thread config ID for response to a host ID
 *
 * Retrieve a Tx thread Config ID for a valid Host ID
 *
 * \param host_id - valid host id for the SoC
 * \param tx_config_id - returns if valid a corresponding tx config id
 *
 * \return 0  if the host id is valid and *tx_config_id is valid, else
 * returns corresponding error value
 */
int32_t Sciserver_SproxyGetResponseConfId(uint16_t host_id, uint16_t *tx_config_id);

/**
 * \brief Retrieve the Tx thread config ID for notification to a host ID
 *
 * Retrieve a Tx thread Config ID for a valid Host ID
 *
 * \param host_id - valid host id for the SoC
 * \param tx_config_id - returns if valid a corresponding tx config id
 *
 * \return 0  if the host id is valid and *tx_config_id is valid, else
 * returns corresponding error value
 */
int32_t Sciserver_SproxyGetNotifyConfId(uint16_t host_id, uint16_t *tx_config_id);

#endif

