/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \defgroup SECURITY_SA3UL_MODULE APIs for SA3UL
 *  \ingroup  SECURITY_MODULE
 *
 *  This module contains APIs to program and use the SA3UL.
 *
 *  @{
 */

/**
 *  \file sa3ul.h
 *
 *  \brief This file contains the prototype of SA3UL driver APIs
 */

#ifndef SA3UL_H_
#define SA3UL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <drivers/udma.h>
#include <security/crypto/sa3ul/hw_include/cslr_cp_ace.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor SA3UL_InputSizes
 *  \name SA3UL macros
 *  @{
 */
/** \brief Max hash size in bytes */
#define SA3UL_MAX_HASH_SIZE_BYTES       (64U)
/** \brief Max key size in bytes */
#define SA3UL_MAX_KEY_SIZE_BYTES        (32U)
/** \brief Max Initialization vector (IV) size in bytes */
#define SA3UL_MAX_IV_SIZE_BYTES         (16U)
/** \brief Max number of rings */
#define SA3UL_NUMBER_OF_RINGS           (3U)
/** \brief Cache line size for alignment of descriptor and buffers */
#define SA3UL_CACHELINE_ALIGNMENT       (128U)
/** \brief Secure context memsize */
#define SA3UL_SECCTX_SIZE               (256U)
/** \brief Max SA3UL instances */
#define SA3UL_INSTANCES_MAX             (4U)
/** \brief Max SA3UL ring n elements */
#define SA3UL_RING_N_ELEMS              (8U)
/** \brief Max SA3UL sw ring number */
#define SA3UL_SW_RING_NUM               (304U)
/** \brief Max Aes input length for encryption and decryption (64KB-1)*/
#define SA3UL_MAX_INPUT_LENGTH_ENC      (0xFFFFU)
/** \brief Max input length for authentication (4MB-1) */
#define SA3UL_MAX_INPUT_LENGTH_AUTH     (0x3FFFFFU)
/** @} */

/**
 *  \anchor SA3UL_AlgoTypes
 *  \name SA3UL Algo Types
 *  @{
 */
/** \brief Hash Algo NULL */
#define SA3UL_HASH_ALG_NULL             (0x10U)
/** \brief Hash Algo SHA-1 */
#define SA3UL_HASH_ALG_SHA1             (0x12U)
/** \brief Hash Algo SHA-256 */
#define SA3UL_HASH_ALG_SHA2_256         (0x14U)
/** \brief Hash Algo SHA-512 */
#define SA3UL_HASH_ALG_SHA2_512         (0x16U)
/** @} */

/**
 *  \anchor SA3UL_Operations_Sequence
 *  \name SA3UL Operations Sequence
 *  @{
 */
/** \brief SA3UL operations encryption */
#define SA3UL_OP_ENC                    (0x01U)
/** \brief SA3UL operations authentication */
#define SA3UL_OP_AUTH                   (0x02U)
/** \brief SA3UL operation encryption then authentication */
#define SA3UL_OP_ENC_THEN_AUTH          (0x03U)
/** \brief SA3UL operations authentication then encryption */
#define SA3UL_OP_AUTH_THEN_ENC          (0x04U)
/** @} */

/**
 *  \anchor SA3UL_Engine_Operation_Type
 *  \name SA3UL engine operation type
 *  @{
 */
/** \brief SA3UL default engine Id */
#define SA3UL_ENGINE_CODE_DEFAULT_ENGINE_ID             (0U)
/** \brief SA3UL Encryption engine module p1 */
#define SA3UL_ENGINE_CODE_ENCRYPTION_MODULE_P1          (2U)
/** \brief SA3UL Encryption engine module p2 */
#define SA3UL_ENGINE_CODE_ENCRYPTION_MODULE_P2          (3U)
/** \brief SA3UL Authentication engine module p1 */
#define SA3UL_ENGINE_CODE_AUTHENTICATION_MODULE_P1      (4U)
/** \brief SA3UL Authentication engine module p2 */
#define SA3UL_ENGINE_CODE_AUTHENTICATION_MODULE_P2      (5U)
/** \brief SA3UL Default Engress Port */
#define SA3UL_ENGINE_CODE_DEFAULT_EGRESS_PORT           (20U)
/** @} */

/**
 *  \anchor SA3UL_Encryption_Algos
 *  \name SA3UL Encryption Algos
 *  @{
 */
/** \brief SA3UL AES Encryption Algorithm */
#define SA3UL_ENC_ALG_AES               (0x0U)
/** \brief SA3UL TDES Encryption Algorithm */
#define SA3UL_ENC_ALG_TDES              (0x1U)
/** \brief SA3UL Encryption Maximun number of Algorithms */
#define SA3UL_ENC_ALG_MAX               (0x2U)
/** @} */

/**
 *  \anchor SA3UL_Encryption_Direction
 *  \name SA3UL Encryption direction
 *  @{
 */
/** \brief Encryption direction */
#define SA3UL_ENC_DIR_ENCRYPT           (0x0U)
/** \brief Decryption direction */
#define SA3UL_ENC_DIR_DECRYPT           (0x1U)
/** @} */

/**
 *  \anchor SA3UL_Encryption_Modes
 *  \name SA3UL Encryption modes
 *  @{
 */
/** \brief ECB mode */
#define SA3UL_ENC_MODE_ECB              (0x0U)
/** \brief CBC mode */
#define SA3UL_ENC_MODE_CBC              (0x1U)
/** \brief Maximun Encryption modes */
#define SA3UL_ENC_MODE_MAX              (0x2U)
/** @} */

/**
 *  \anchor SA3UL_Encryption_Key_Sizes
 *  \name SA3UL Encryption key sizes
 *  @{
 */
/** \brief Encryption 128 bit key size */
#define SA3UL_ENC_KEYSIZE_128           (0x0U)
/** \brief Encryption 192 bit key size */
#define SA3UL_ENC_KEYSIZE_192           (0x1U)
/** \brief Encryption 256 bit key size */
#define SA3UL_ENC_KEYSIZE_256           (0x2U)
/** \brief Max key size */
#define SA3UL_ENC_KEYSIZE_MAX           (0x3U)
/** @} */

#define SA3UL_ENC_KEYSIZE_BITS(k)       (128u + (64u * (k)))
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \anchor SA3UL_Handle
 *  \brief Handle to the SA3UL driver returned by #SA3UL_open() */
typedef void *SA3UL_Handle;

/**
 *  \brief Parameters passed to #SA3UL_contextAlloc()
 */
typedef struct
{
    uint8_t                 opType;
    /**< SA operation type, refer \ref SA3UL_Engine_Operation_Type*/
    uint8_t                 hashAlg;
    /**< Hash algorithm, refer \ref SA3UL_AlgoTypes*/
    uint8_t                 encAlg;
    /**< Encryption algorithm to run, refer \ref SA3UL_Encryption_Algos*/
    uint8_t                 encDirection;
    /**< Encrypt or decrypt, refer \ref SA3UL_Encryption_Direction*/
    uint8_t                 encMode;
    /**< Encryption mode to run, refer \ref SA3UL_Encryption_Modes*/
    uint8_t                 key[SA3UL_MAX_KEY_SIZE_BYTES];
    /**< Key input for encryption */
    uint8_t                 encKeySize;
    /**< Encryption key size, refer \ref SA3UL_Encryption_Key_Sizes*/
    uint32_t                inputLen;
    /**< Overall data length, must be sum of all packet lengths */
    uint8_t                 iv[SA3UL_MAX_IV_SIZE_BYTES];
    /**< IV input for encryption, refer \ref SA3UL_InputSizes */
} SA3UL_ContextParams;

/**
 * \anchor SA3UL_Params
 *  \brief Parameters passed to #SA3UL_open()
 */
typedef struct
{
    uint32_t                reserved;
     /**< tbd for future */
} SA3UL_Params;

/**
 * \brief Object for a SA3UL crypto operation
 */
typedef struct
{
    SA3UL_Handle            handle;
    /**< Instance handle to which this object belongs, refer \ref SA3UL_Handle */
    SA3UL_Params            prms;
    /**< Open parameter as provided by user, refer \ref SA3UL_Params*/
    uint32_t                isOpen;
    /**< Flag to indicate whether the instance is opened already */
    CSL_Cp_aceRegs          *pSaRegs;
    /**< Pointer to register overlay */
    uint32_t                psilInst;
    /**< SA3UL psil Instance */
    uint32_t                ringaccChnls[SA3UL_NUMBER_OF_RINGS];
    /**< SA3UL psil Instance */
    uint32_t                udmapTxChnum;
    /**< UDMA tx channel allocated */
    uint32_t                udmapRxChnum[2];
    /**< UDMA Rx channel allocated */
    uint32_t                udmapRxFlownum;
    /**< UDMA Rx flow  allocated */
    /*
     * UDMA objects and druver handles
     */
    Udma_ChObject           udmaTxChObj;
    /**< UDMA tx ch object */
    Udma_ChObject           udmaRxChObj[2];
     /**< UDMA rx ch objects */
    Udma_FlowObject         udmaFlowObj;
     /**< UDMA rx flow object */
    Udma_RingObject         udmaRingObj[2];
    /**< UDMA ring object */
    Udma_EventObject        udmaEvtObj;
    /**< UDMA event object */
    Udma_EventObject        udmaEvtObj0;
    /**< UDMA event object0 */
    Udma_DrvHandle          drvHandle;
    /**< UDMA driver handle */
    Udma_ChHandle           rxChHandle[2];
    /**< UDMA rx channel handles */
    Udma_ChHandle           txChHandle;
    /**< UDMA tx channel handle */
    Udma_FlowHandle         rxFlowHandle;
    /**< UDMA rx flow  handle */
    Udma_RingHandle         rxFreeRingHandle;
    /**< UDMA rx free ring handle */
    Udma_RingHandle         rxRingHandle;
    /**< UDMA rx  ring handle */
    Udma_RingHandle         txComplRingHandle;
    /**< UDMA tx completion ring handle */
    Udma_RingHandle         txRingHandle;
    /**< UDMA tx  ring handle */
    Udma_EventHandle        rxEvtHandle;
    /**< UDMA rx event handle */
    /*
     * sa3ul storage Queue params
     */
    uint32_t                storageQueueHead;
    uint32_t                storageQueueTail;
    uint32_t                storageQueueFree;
    uint64_t                storageQueue[SA3UL_RING_N_ELEMS];
    /*
     * memory for SA3UL security context
     *
     * Caller must allocate SA3UL_SECCTX_SIZE bytes of 128-byte aligned
     * memory for this.
     */
    uint8_t                 sa3ulContextId[SA3UL_INSTANCES_MAX];
    /**< secure contextId array */
    uint8_t                 contextId;
    /**< secure context Id */
} SA3UL_Object;

/** \brief SA3UL instance attributes - used during init time */
typedef struct
{
    /*
     * SOC configuration
     */
    uint32_t                saBaseAddr;
    /**< Peripheral SA base address */
    uint32_t                txPsilThreadId;
    /**< Tx ch psil thread number  */
    uint32_t                rxPsil0ThreadId;
    /**< Rx ch0 psil thread number  */
    uint32_t                rxPsil1ThreadId;
    /**< Rx ch1 psil thread number  */
    uint32_t                rxRingMemAddr;
    /**< Mem address for RX ring elements  */
    uint32_t                txRingMemAddr;
    /**< Mem address for TX ring elements  */
    uint32_t                numDesc;
    /**< Descriptor count  */
    uint32_t                descSize;
    /**< Descriptor size  */
    uint32_t                descMemAddr;
    /**< Descriptor mem Address  */
    uint32_t                descMemSize;
    /**< Descriptor mem size in Bytes  */
    uint32_t                udmaSaTxGroupNum;
    /**< SA3UL Tx group num  */
    uint32_t                udmaSaRxGroupNum;
    /**< SA3UL Rx group num  */
    uint32_t                ringCnt;
    /**< Num rings  */
    uint32_t                udmaHandle;
    /**< Handle for UDMA object */
    uint32_t                contextIdStart;
    /**< secure context start index */
    uint32_t                contextIdMaxNum;
    /**< secure context max index*/
    uint32_t                txRingNumInt;
    /**< tx ring num internal always 0*/
    uint32_t                rxRingNumInt;
    /**< rx ring num internal always 1*/
    uint32_t                swRingNumInt;
    /**< sw ring num internal always 2*/
    uint32_t                privId;
    /**< core privileged Id*/
    uint32_t                priv;
    /**< core privileged Id*/
    uint32_t                secure;
    /**< secure transaction*/
} SA3UL_Attrs;

/** \brief SA3UL driver context */
typedef struct
{
    SA3UL_Attrs             *attrs;
    /**< Driver params passed during open */
    SA3UL_Object            *object;
    /**< Pointer to driver functions */
} SA3UL_Config;

/** \brief MEDdata for Encryption engine */
typedef struct
{
    uint8_t                 sopOffset;
    uint8_t                 middleOffset;
    uint8_t                 eopOffset;
    uint8_t                 nMCInstrs;
    const uint8_t          *mcInstrs;
}SA3UL_MCEData;

/** \brief SA3UL context RAM structure for authentication engine. */
typedef struct
{
    uint32_t                authCtx1;
    uint32_t                reserved0;
    uint32_t                authenticationLengthHi;
    uint32_t                authenticationLengthLo;
    uint32_t                reserved1[4];
    uint32_t                authenticationKeyValueL[8];
    uint32_t                oPadL[8];
    uint32_t                authenticationKeyValueH[8];
    uint32_t                oPadH[8];
}SA3UL_SecCtxAuth;

/**  \brief SA3UL SC control structure */
typedef struct
{
    uint32_t                scctl1;
    uint32_t                scctl2;
    uint32_t                scptrH;
    uint32_t                scptrL;
}SA3UL_Scctl;

/** \brief SA3UL context RAM structure for Encryption engine */
typedef struct
{
    uint32_t                encrCtl;
    uint32_t                modeCtrlInstrs[6];
    uint32_t                hwCtrlWord;
    uint32_t                encKeyValue[8];
    uint32_t                encAux1[8];
    uint32_t                encAux2[4];
    uint32_t                encAux3[4];
    uint32_t                encAux4[4];
    uint8_t                 preCryptoData[15];
}SA3UL_SecCtxEnc;

/**
 * \brief SA3UL context RAM structure
 */
typedef struct
{
    SA3UL_Scctl      scctl;
    uint32_t         unused[12];
    union
    {
        SA3UL_SecCtxAuth  auth;
        SA3UL_SecCtxEnc   enc;
    } u;
}SA3UL_SecCtx;

/**
 * \brief SA3UL context object structure
 */
typedef struct
{
    SA3UL_SecCtx            secCtx;
    uint8_t                 res[32];
    uint8_t                 secCtxId;
    SA3UL_Handle            handle;
    SA3UL_ContextParams     ctxPrms;
    /**< SA3UL secure parameter as provided by user */
    uint32_t                totalLengthInBytes;
    uint8_t                 computedHash[SA3UL_MAX_HASH_SIZE_BYTES];
    uint32_t                computationStatus;
    uint32_t                txBytesCnt;
    uint32_t                rxBytesCnt;
    uint32_t                sa3ulErrCnt;
} SA3UL_ContextObject;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Externally defined driver configuration array */
extern SA3UL_Config         gSa3ulConfig[];
/** \brief Externally defined driver configuration Num */
extern uint32_t             gSa3ulConfigNum;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/**
 *  \brief  This function initializes the SA3UL module
 */
void SA3UL_init(void);

/**
 *  \brief  This function de-initializes the SA3UL module
 */
void SA3UL_deinit(void);

/**
 *  \brief  This function opens a given SA3UL module
 *
 *  \param  index    Index of config to use in the *SA3UL_Config* array
 *
 *  \param  params   Pointer to open parameters. If NULL is passed, then
 *                   default values will be used
 *
 *  \return A #SA3UL_Handle on success or a NULL on an error or if it has been
 *          opened already
 */
SA3UL_Handle SA3UL_open(uint32_t index, const SA3UL_Params *params);

/**
 *  \brief  Function to close a SA3UL module specified by the SA3UL handle
 *
 *  \param  handle  #SA3UL_Handle returned from #SA3UL_open()
 */
void SA3UL_close(SA3UL_Handle handle);

/**
 *  \brief  Function to configure secure context
 *
 *  \param  handle  #SA3UL_Handle returned from #SA3UL_open()
 *
 *  \param  ctxObj  Pointer to #SA3UL_ContextObject structure
 *
 *  \param  ctxPrms Pointer to secure context parameters.If NULL is passed, then
 *                  default values will be used
 *
 *  \return A #SystemP_SUCCESS on success or a NULL on an error or if the instance
 *            index has  NOT been opened yet
 */
int32_t SA3UL_contextAlloc(SA3UL_Handle handle, SA3UL_ContextObject *ctxObj, const SA3UL_ContextParams *ctxPrms);

/**
 *  \brief  Function to free secure context configuration
 *
 *  \param  pCtxObj  Pointer to *SA3UL_ContextObject* structure
 *
 *  \return A #SystemP_SUCCESS on success or a NULL on an error or if the instance
 *            index has  NOT been opened yet
 */
int32_t SA3UL_contextFree(SA3UL_ContextObject *pCtxObj);

/**
 *  \brief  Function to transfer and recieve data buffer
 *
 *  \param  ctxObj  Pointer to *SA3UL_ContextObject* structure
 *
 *  \param  input   Pointer to input buffer to be processed
 *
 *  \param  ilen    Length of the input buffer
 *
 *  \param  output  Pointer to output buffer after the process is complete
 *
 *  \return A #SystemP_SUCCESS on success or a NULL on an error or if the instance
 *            index has  NOT been opened yet */
int32_t SA3UL_contextProcess(SA3UL_ContextObject *ctxObj, const uint8_t *input, uint32_t ilen, uint8_t *output);

/**
 *  \brief  Function to initialize default SA3UL parameters
 *
 *  \param  prms  Pointer to open parameters.
 */
static inline void SA3UL_Params_init(SA3UL_Params *prms);

/**
 * \brief setup the SA3UL RNG module.
 *
 * \param  handle  #SA3UL_Handle returned from #SA3UL_open()
 *
 * \return #SystemP_SUCCESS if successful
 */
int32_t SA3UL_rngSetup(SA3UL_Handle handle);

/**
 * \brief Read random numbers into the output buffer.
 *
 * \param  handle  #SA3UL_Handle returned from #SA3UL_open()
 *
 * \param out pointer to the buffer for the 128 bit random data.
 *
 * \return returns #SystemP_SUCCESS if requested data is available.
 *                 #SystemP_FAILURE if RNG is not initialized.
 */
int32_t SA3UL_rngRead(SA3UL_Handle handle, uint32_t *out);

static inline void SA3UL_ContextParams_init(SA3UL_ContextParams *ctxPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void SA3UL_Params_init(SA3UL_Params *prms)
{
    if(prms != NULL)
    {
        prms->reserved                        = 0;
    }
}

static inline void SA3UL_ContextParams_init(SA3UL_ContextParams *ctxPrms)
{
    if(ctxPrms != NULL)
    {
        memset(ctxPrms, 0, sizeof(*ctxPrms));
    }
}

#ifdef __cplusplus
}
#endif

#endif /* SA3UL_H_ */

/** @} */
