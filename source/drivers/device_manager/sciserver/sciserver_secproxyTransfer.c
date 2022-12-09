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
 * \file sciserver_sec_proxy_transfer.c
 *
 * \brief Secure Proxy Transfer APIs
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/hw_types.h>
#include <drivers/hw_include/csl_types.h>
#include <types/errno.h>
#include <types/address_types.h>
#include <types/sbool.h>
#include <sciserver_secproxyTransfer.h>
#include <sciserver_secproxyDescription.h>
#include <sciserver_secproxyRegs.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Is the secure proxy thread ready to send data
 *
 * \param tx_config_id - Tx thread config ID
 *
 * \param tx_thread_ret - If data can be send, then returns the pointer to
 *    thread config for the Tx thread
 *
 * \param sproxy_ret - If data can be send, then returns the pointer to the
 *    sproxy instance that the Tx thread points to.
 *
 * \return 0 if there data can be send over the Tx thread pointed by the
 * tx thread config pointer. However, in case of bad pointers OR thread error
 * returns corresponding error value.
 */
static int32_t Sciserver_SproxyTxIsReady(
    uint16_t    tx_config_id,
    const struct Sciserver_SecureProxyTxThreadConfig        **tx_thread_ret,
    const struct Sciserver_SecureProxy        **sproxy_ret
    );

static int32_t Sciserver_SproxyMsgGetSenderThrId(
    uint16_t rx_config_id,
    uint16_t *sender_thr_id);

/**
 * \brief Helper function to find a Host ID from a Tx Thread ID.
 *
 * The thread ID must be present in \ref Sciserver_SecureProxyTxConfigurations.
 * But, we have to search for the tuple {rx_config_id, sender_thr_id}
 * That can only be unique given that Tx threads need to be associated
 * with a specific Rx thread, and RX_config_id is unique for all instances of
 * Rx_threads on all Sec proxies.
 *
 * \param rx_config_id - Rx Configuration ID
 *
 * \param sender_thr_id - Thread ID of the sender
 *
 * \param sender_host_id - Sender's Host ID is returned if a match is found
 *
 * \return 0 if a match is found, else return CSL_EFAIL
 */
static int32_t Sciserver_SproxySearchHost(uint16_t rx_config_id,
                                  uint16_t sender_thr_id,
                                  uint32_t *sender_host_id);

/**
 * \brief Helper function to check to see if secure proxy thread has valid data
 *
 * \param rx_config_id - Rx thread config ID
 *
 * \param rx_thread_ret - If data is ready, then returns the pointer to thread
 *    config for the Rx thread
 *
 * \param sproxy_ret - If data is ready, then returns the pointer to the sproxy
 *    instance that the Rx thread points to.
 *
 * \return 0 if there is data to be read from the Rx thread pointed by the
 * rx thread config pointer. However, in case of bad pointers OR thread error
 * returns corresponding error value.
 */
static int32_t Sciserver_SproxyRxIsReady(
    uint16_t    rx_config_id,
    const struct Sciserver_SecureProxyRxThreadConfig **rx_thread_ret,
    const struct Sciserver_SecureProxy **sproxy_ret);

/**
 * \brief Generic helper to get the status register value of a sproxy thread
 *
 * \param sproxy - Pointer to Secure proxy instance
 *
 * \param thread_id - Secure proxy thread ID to read status of
 *
 * \return secure proxy thread's status register value
 */
static uint32_t Sciserver_SproxyGetThreadStatus(
    const struct Sciserver_SecureProxy *sproxy,
    uint16_t                   thread_id);

/**
 * \brief Helper function to transfer a buffer to secure proxy memory
 *
 * \param is_rx STRUE if this is a read operation, else SFALSE
 *
 * \param thread_msg_addr - mapped_addr of a thread message area
 *
 * \param buff - pointer to the data buffer to transfer
 *
 * \param num_words - number of words to transfer
 */
static void Sciserver_SproxyTransferMessage(sbool is_rx,
                   mapped_addr_t thread_msg_addr,
                   uint32_t *buff,
                   uint32_t num_words);

/**
 * \brief Map a physical address over to mapped_addr
 *
 * \param phy_addr Physical address
 *
 * \return Mapped address
 */
static inline mapped_addr_t Sciserver_SptMapRegion(soc_phys_addr_t phy_addr);

/**
 * \brief provide a simplified write uint32_t operation
 * \param v value
 * \param a address to write to
 */
static inline void Sciserver_WriteL(uint32_t v, local_phys_addr_t a);

/**
 * \brief provide a simplified read uint32_t operation
 * \param a address to write to
 *
 * \return uint32_t value at the address pointed by a
 */
static inline uint32_t Sciserver_ReadL(local_phys_addr_t a);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Receive (Rx) Path visible APIs
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int32_t Sciserver_SproxyMsgIsPending(uint16_t rx_config_id)
{
    int32_t ret;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    ret = Sciserver_SproxyRxIsReady(rx_config_id, &rx_thread, &sproxy);
    return ret;
}

int32_t Sciserver_SproxyMsgReadAtOffset(
    uint16_t rx_config_id,
    uint32_t *rx_buff,
    uint32_t rx_num_words,
    uint32_t offset)
{
    int32_t ret = CSL_PASS;
    soc_phys_addr_t thread_base_message_phy;
    mapped_addr_t thread_base_message;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    /* Don't bother to even attempt to read if too big */
    if ((rx_num_words + offset) > SCISERVER_SECPROXY_TARGET_MESSAGE_NUM_WORDS) {
        ret = CSL_EFAIL;
    }

    /* Is my buffer even valid */
    if (rx_buff == NULL) {
        ret = CSL_EFAIL;
    }

    /* Read nothing? */
    if (rx_num_words == 0U) {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS) {
        ret = Sciserver_SproxyRxIsReady(rx_config_id, &rx_thread, &sproxy);
    }

    /* Okay, we now have a valid message to read */
    if (ret == CSL_PASS) {
        thread_base_message_phy = sproxy->baseaddr_src_target_data +
                      Sciserver_SecProxyTargetMsgStart(
                      rx_thread->thread_id);
        thread_base_message = Sciserver_SptMapRegion(thread_base_message_phy);
        thread_base_message +=
            (mapped_addr_t)(offset * (uint32_t)sizeof(uint32_t));

        Sciserver_SproxyTransferMessage(STRUE,
                       thread_base_message,
                       rx_buff,
                       rx_num_words);
    }

    return ret;
}

int32_t Sciserver_SproxyMsgRead(uint16_t rx_config_id,
                        uint32_t *rx_buff,
                        uint32_t rx_num_words)
{
    return Sciserver_SproxyMsgReadAtOffset(
                rx_config_id, rx_buff, rx_num_words, 0U);
}

int32_t Sciserver_SproxyMsgGetSenderHostId (uint16_t rx_config_id,
                                            uint32_t *sender_host_id)
{
    int32_t ret = CSL_PASS;
    uint16_t sender_thr_id = 0U;

    /* Is my return ptr even valid? */
    if (sender_host_id == NULL) {
        ret = CSL_EFAIL;
    }

    /* First see if we can find a thread */
    if (ret == CSL_PASS) {
        ret = Sciserver_SproxyMsgGetSenderThrId(rx_config_id, &sender_thr_id);
    }

    if (ret == CSL_PASS) {
        ret = Sciserver_SproxySearchHost(rx_config_id, sender_thr_id,
                     sender_host_id);
    }

    return ret;
}

int32_t Sciserver_SproxyMsgValidateHostId(uint16_t host_id)
{
    uint16_t i;
    int32_t ret = CSL_EFAIL;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_threads;

    tx_threads = Sciserver_SecureProxyTxConfigurations;

    /* XXX: Is there a better search algo we could do? */
    for (i = 0U; i < Sciserver_SecureProxyTxConfigNum; i++) {
        if (host_id == tx_threads->host_id) {
            ret = CSL_PASS;
        }
        /*
         * XXX: XXX: XXX: XXX:
         * IMPORTANT NOTE: WE DONOT BREAK here:
         * This is a countermeasure implemented
         * against timing attack.
         * This is inefficient, however, required.
         * XXX: XXX: XXX: XXX:
         */
        tx_threads++;
    }
    return ret;
}

int32_t Sciserver_SproxyMsgAck (uint16_t rx_config_id)
{
    int32_t ret = CSL_PASS;
    soc_phys_addr_t thread_base_confirm_phy;
    mapped_addr_t thread_base_confirm;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    ret = Sciserver_SproxyRxIsReady(rx_config_id, &rx_thread, &sproxy);

    /* Okay, we now have a valid message to read */
    if (ret == CSL_PASS) {
        thread_base_confirm_phy = sproxy->baseaddr_src_target_data +
                      Sciserver_SecProxyTargetMsgConfirm(
            rx_thread->thread_id);
        thread_base_confirm = Sciserver_SptMapRegion(thread_base_confirm_phy);

        /* Just a read to pick the next available message */
        (void) Sciserver_ReadL((local_phys_addr_t)thread_base_confirm);
    }

    return ret;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Transmit (Tx) Path visible APIs
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int32_t Sciserver_SproxyCanSend(uint16_t tx_config_id)
{
    int32_t ret;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    ret = Sciserver_SproxyTxIsReady(tx_config_id, &tx_thread, &sproxy);
    return ret;
}

int32_t Sciserver_SproxyMsgSendAtOffset(uint16_t tx_config_id,
                                  uint32_t *tx_buff,
                                  uint32_t tx_num_words,
                                  uint32_t offset)
{
    int32_t ret = CSL_PASS;
    soc_phys_addr_t thread_base_message_phy;
    mapped_addr_t thread_base_message;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    /* Don't bother to even attempt to write if too big */
    if ((tx_num_words + offset) > SCISERVER_SECPROXY_TARGET_MESSAGE_NUM_WORDS) {
        ret = CSL_EFAIL;
    }

    /* Is my buffer even valid */
    if (tx_buff == NULL) {
        ret = CSL_EFAIL;
    }

    /* Send nothing? */
    if (tx_num_words == 0U) {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS) {
        ret = Sciserver_SproxyTxIsReady(tx_config_id, &tx_thread, &sproxy);
    }

    /* Okay, we now have a valid message to write */
    if (ret == CSL_PASS) {
        thread_base_message_phy = sproxy->baseaddr_src_target_data +
                      Sciserver_SecProxyTargetMsgStart(
            tx_thread->thread_id);
        thread_base_message = Sciserver_SptMapRegion(thread_base_message_phy);
        thread_base_message +=
            (mapped_addr_t)(offset * (uint32_t)sizeof(uint32_t));

        Sciserver_SproxyTransferMessage(SFALSE, thread_base_message, tx_buff,
                       tx_num_words);
    }

    return ret;
}

int32_t Sciserver_SproxyMsgSend(uint16_t tx_config_id,
                        uint32_t *tx_buff,
                        uint32_t tx_num_words)
{
    return Sciserver_SproxyMsgSendAtOffset(tx_config_id, tx_buff, tx_num_words, 0U);
}

int32_t Sciserver_SproxyMsgFinish(uint16_t tx_config_id)
{
    int32_t ret = CSL_PASS;
    soc_phys_addr_t thread_base_confirm_phy;
    mapped_addr_t thread_base_confirm;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    ret = Sciserver_SproxyTxIsReady(tx_config_id, &tx_thread, &sproxy);

    /* Okay, we now have a valid message to write */
    if (ret == CSL_PASS) {
        thread_base_confirm_phy = sproxy->baseaddr_src_target_data +
                      Sciserver_SecProxyTargetMsgConfirm(
            tx_thread->thread_id);
        thread_base_confirm = Sciserver_SptMapRegion(thread_base_confirm_phy);

        /* Just a write to flush out the message */
        Sciserver_WriteL(0x0U, (local_phys_addr_t)thread_base_confirm);
    }

    return ret;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Transmit (Tx) Path Helper APIs
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static int32_t Sciserver_SproxyTxIsReady(
    uint16_t    tx_config_id,
    const struct Sciserver_SecureProxyTxThreadConfig        **tx_thread_ret,
    const struct Sciserver_SecureProxy        **sproxy_ret
    )
{
    int32_t ret = CSL_PASS;
    uint32_t status = 0U;
    uint32_t num_messages = 0U;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_thread;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    if (tx_config_id > Sciserver_SecureProxyTxConfigNum) {
        ret = CSL_EFAIL;
    }

    /* All struct validation was done at init and memory is safe */
    if (ret == CSL_PASS) {
        tx_thread = &(Sciserver_SecureProxyTxConfigurations[tx_config_id]);
        rx_thread =
            &(gSciserverSecureProxyRxConfigurations[tx_thread->
                                 rx_thread_instance_id
              ]);
        sproxy =
            &(gSciserverSecureProxyInstances
              [rx_thread->secure_proxy_instance_id]);

        status = Sciserver_SproxyGetThreadStatus(sproxy, tx_thread->thread_id);

        /* Check if we have an error and min 1 message slot avail */
        if ((status & SEC_PROXY_RT_THREAD_STATUS_ERROR_MASK) != 0U) {
            /* TBD: XXX: Report error info */
            ret = CSL_EFAIL;
            /* TBD: XXX: Error recovery by write of 0 */
        } else {
            num_messages =
                (status &
                 SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) >>
                SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_SHIFT;
            if (num_messages == 0U) {
                ret = CSL_EFAIL;
            }
        }
    }

    if (ret == CSL_PASS) {
        *tx_thread_ret = tx_thread;
        *sproxy_ret = sproxy;
    }

    return ret;
}

static int32_t Sciserver_SproxyMsgGetSenderThrId(
    uint16_t rx_config_id,
    uint16_t *sender_thr_id)
{
    int32_t ret = CSL_PASS;
    soc_phys_addr_t thread_base_private_phy;
    mapped_addr_t thread_base_private;

    uint32_t priv = 0U;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    /* Is my return ptr even valid? */
    if (sender_thr_id == NULL) {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS) {
        ret = Sciserver_SproxyRxIsReady(rx_config_id, &rx_thread, &sproxy);
    }

    /* Okay, we now have a valid message to read */
    if (ret == CSL_PASS) {
        thread_base_private_phy = sproxy->baseaddr_src_target_data +
                      Sciserver_SecProxyTargetDataPrivate(
            rx_thread->thread_id);
        thread_base_private = Sciserver_SptMapRegion(thread_base_private_phy);

        priv = Sciserver_ReadL((local_phys_addr_t)thread_base_private);

        *sender_thr_id =
            (uint16_t)((priv &
             SEC_PROXY_TARGET_DATA_PRIVATE_SRC_THR_MASK) >>
            SEC_PROXY_TARGET_DATA_PRIVATE_SRC_THR_SHIFT);
    }

    return ret;
}

static inline uint32_t Sciserver_ReadL(local_phys_addr_t a)
{
    return HW_RD_REG32(a);
}

static inline void Sciserver_WriteL(uint32_t v, local_phys_addr_t a)
{
    HW_WR_REG32(a, v);
}

static inline mapped_addr_t Sciserver_SptMapRegion(soc_phys_addr_t phy_addr)
{
    /**
     * TBD - we need RAT if the mapping is not available.
     *
     * NOTE: we will misuse pm/soc/am6/dmsc.c configuration for now:
     *
     * ~~~
     * Physical address | mapped address | Size
     * ----------------------------------------
     * 0x00000000ULL    | 0x60000000UL   | 512MB
     * 0x20000000ULL    | 0x80000000UL   | 512MB
     * 0x40000000ULL    | 0xa0000000UL   | 512MB
     * ~~~
     *
     * *NOTE*: This wont work for firewall setup and separated ops.
     */

    return soc_phys_low_u32(phy_addr);
}

static void Sciserver_SproxyTransferMessage(sbool is_rx,
                   mapped_addr_t thread_msg_addr,
                   uint32_t *buff,
                   uint32_t num_words)
{
    uint32_t i;
    uint32_t *tmp_buff = buff;
    mapped_addr_t msg_addr = thread_msg_addr;

    for (i = 0U; i < num_words; i++) {
        if (is_rx == STRUE) {
            *tmp_buff = Sciserver_ReadL((local_phys_addr_t)msg_addr);
        } else {
            Sciserver_WriteL(*tmp_buff, (local_phys_addr_t)msg_addr);
        }
        tmp_buff++;
        msg_addr += (mapped_addr_t)sizeof(uint32_t);
    }
}

static uint32_t Sciserver_SproxyGetThreadStatus(
    const struct Sciserver_SecureProxy *sproxy,
    uint16_t                   thread_id)
{
    soc_phys_addr_t thread_base_stat_phy;
    mapped_addr_t thread_base_stat;
    uint32_t status;

    thread_base_stat_phy = sproxy->baseaddr_cfg_rt +
                   Sciserver_SecProxyRtThreadStatus(thread_id);
    thread_base_stat = Sciserver_SptMapRegion(thread_base_stat_phy);
    status = Sciserver_ReadL((local_phys_addr_t)thread_base_stat);

    return status;
}

static int32_t Sciserver_SproxyRxIsReady(
    uint16_t     rx_config_id,
    const struct Sciserver_SecureProxyRxThreadConfig **rx_thread_ret,
    const struct Sciserver_SecureProxy **sproxy_ret)
{
    int32_t ret = CSL_PASS;
    uint32_t status = 0U;
    uint32_t num_messages = 0U;
    const struct Sciserver_SecureProxyRxThreadConfig *rx_thread;
    const struct Sciserver_SecureProxy *sproxy;

    if (rx_config_id > gSciserverSecureProxyRxConfigNum) {
        ret = CSL_EFAIL;
    }

    /* All struct validation was done at init and memory is safe */
    if (ret == CSL_PASS) {
        rx_thread = &(gSciserverSecureProxyRxConfigurations[rx_config_id]);
        sproxy = &(gSciserverSecureProxyInstances
              [rx_thread->secure_proxy_instance_id]);
        status = Sciserver_SproxyGetThreadStatus(sproxy, rx_thread->thread_id);

        /* Check if we have an error and min 1 message to read */
        if ((status & SEC_PROXY_RT_THREAD_STATUS_ERROR_MASK) != 0U) {
            /* TBD: XXX: Report error info */
            ret = CSL_EFAIL;
            /* TBD: XXX: Error recovery by write of 0 */
        } else {
            num_messages =
                (status &
                 SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_MASK) >>
                SEC_PROXY_RT_THREAD_STATUS_CUR_CNT_SHIFT;
            if (num_messages == 0U) {
                ret = CSL_EFAIL;
            }
        }
    }

    if (ret == CSL_PASS) {
        *rx_thread_ret = rx_thread;
        *sproxy_ret = sproxy;
    }

    return ret;
}

static int32_t Sciserver_SproxySearchHost(uint16_t rx_config_id,
                                  uint16_t sender_thr_id,
                                  uint32_t *sender_host_id)
{
    uint16_t i;
    int32_t ret = CSL_EFAIL;
    const struct Sciserver_SecureProxyTxThreadConfig *tx_threads;

    tx_threads = Sciserver_SecureProxyTxConfigurations;

    /* XXX: Is there a better search algo we could do? hash? */
    for (i = 0U; i < Sciserver_SecureProxyTxConfigNum; i++) {
        if ((tx_threads->thread_id == sender_thr_id) &&
            (tx_threads->rx_thread_instance_id == rx_config_id)) {
            /* We have a match! */
            *sender_host_id = (uint32_t)(tx_threads->host_id);
            ret = CSL_PASS;
            /*
             * XXX: XXX: XXX: XXX:
             * IMPORTANT NOTE: WE DONOT BREAK here:
             * This is a countermeasure implemented
             * against timing attack.
             * This is inefficient, however, required.
             * XXX: XXX: XXX: XXX:
             */
        }
        tx_threads++;
    }

    return ret;
}


