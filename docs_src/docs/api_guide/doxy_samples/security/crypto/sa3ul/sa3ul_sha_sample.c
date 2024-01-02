//! [include]

#include<stdio.h>
#include <security/crypto.h>
#include <security/crypto/sa3ul/sa3ul.h>

Crypto_Context gCryptoSha512Context;
static uint8_t gCryptoSha512TestBuf[9] = {"abcdefpra"};
SA3UL_ContextObject  gCtxObj;
//! [include]

void sa3ul_Sha(void)
{
//! [sa3ulsha]

    int32_t             status;
    uint8_t             sha512sum[64];
    Crypto_Handle       shaHandle;
    SA3UL_ContextParams ctxParams;

    /* Init SA */
    SA3UL_init();

    /* Open SHA instance */
    shaHandle = Crypto_open(&gCryptoSha512Context);

    /* Configure secure context */
    ctxParams.opType    = SA3UL_OP_AUTH;
    ctxParams.hashAlg   = SA3UL_HASH_ALG_SHA2_512;
    ctxParams.inputLen  = sizeof(gCryptoSha512TestBuf);
    gCtxObj.totalLengthInBytes = sizeof(gCryptoSha512TestBuf);
    status = SA3UL_contextAlloc(gCryptoSha512Context.drvHandle,&gCtxObj,&ctxParams);

    /* Perform SHA operation */
    status = SA3UL_contextProcess(&gCtxObj,&gCryptoSha512TestBuf[0], sizeof(gCryptoSha512TestBuf), sha512sum);

    /* Free the secure context configuration */
    SA3UL_contextFree(&gCtxObj);

    /* Close SHA instance */
    status = Crypto_close(shaHandle);

    /*deinit SA */
    SA3UL_deinit();

    /* Kill warning of variable set but not used */
    (void) status;

//! [sa3ulsha]
}