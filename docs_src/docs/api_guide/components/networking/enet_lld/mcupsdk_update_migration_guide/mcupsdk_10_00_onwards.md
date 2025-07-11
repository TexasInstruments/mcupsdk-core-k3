# Version Updates from 11.00 SDKs to Latest 11.1 {#enet_mcupsdk_update}

## Enet LLD 11.1 Changes
## Change Set
Change-1 : ENET UDMA API changes

### Change-1 Description
The ENET UDMA API has undergone some changes, with the primary goal of enhancing overall code quality and adhering to functional safety standards. These changes aim to minimize the use of error-prone constructs and eliminate the utilization of void pointers.

Old API Header                                                                                | New API Header                                                                     |
:-------------------------------------------------------------------------------------------  | :-------------                                                                     |
1. Initialize RX channel open parameters: EnetDma_initRxChParams(void *pRxChCfg)              | EnetUdma_initRxFlowParams(EnetUdma_OpenRxFlowPrms *pRxFlowPrms)
2. Enet DMA open RX channel: EnetDma_openRxCh(EnetDma_Handle hDma, const void *pRxChCfg)      | EnetUdma_openRxFlow(EnetDma_Handle hDma,const EnetUdma_OpenRxFlowPrms *pRxFlowPrms)|
3. Enet DMA close RX channel: EnetDma_closeRxCh(EnetDma_RxChHandle hRxCh, EnetDma_PktQ *fq, EnetDma_PktQ *cq)  | EnetUdma_closeRxFlow(EnetDma_RxChHandle hRxCh,EnetDma_PktQ *fq,EnetDma_PktQ *cq)|
4. Initialize TX channel open parameters: EnetDma_initTxChParams(void *pTxChCfg)             |   EnetUdma_initTxChParams(EnetUdma_OpenTxChPrms *pTxChPrms)|
5. Enet DMA open TX channel: EnetDma_openTxCh(EnetDma_Handle hDma, const void *pTxChCfg)     | EnetUdma_openTxCh(EnetDma_Handle hDma, const EnetUdma_OpenTxChPrms *pTxChPrms) |
6. Enet DMA close TX channel: EnetDma_closeTxCh(EnetDma_TxChHandle hTxCh, EnetDma_PktQ *fq, EnetDma_PktQ *cq) | EnetUdma_closeTxCh(EnetDma_TxChHandle hTxCh, EnetDma_PktQ *fq, EnetDma_PktQ *cq)|

[TOC]
\cond SOC_AM62PX
## EthFw 11.1 Changes
## Change Set
Change-1 : Aligning with ENET UDMA changes\n
Change-2 : Aligning with ENET OSAL changes

### Change-1 Description

The following changes have been made in the update from SDK version 11.00 to the latest version 11.1:

1. The `virtnetif_lwipif.c` file in the RTOS Client example \ref ETHFW_SERVER_AND_CLIENT has been modified to use the new ENET UDMA APIs.
2. Files `main.c` and `app_cpswconfighandler.c` in the apps/app_remoteswitchcfg_server/ folder now utilize the EnetDma_Cfg structure, replacing the EnetCpdma_Cfg structure.
3. The function pointer initializations have been removed from the `CpswRemoteApp_setTxChPrms()` and `CpswRemoteApp_setRxFlowPrms() ` functions in `virtnetif_lwipif.c.`

### Change-2 Description
To align with the Enet-lld OSPI lib changes, the EthFw code has undergone the following changes:

1. Calls to the `Enet_initOsalCfg()` API have been removed.
2. Functions arguments of `Enet_init(&osalPrms, &utilsPrms)` have been changed to `Enet_init(&utilsPrms)`.

\endcond