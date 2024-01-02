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
 *  \file dss_evtMgr.h
 *
 *  \brief DSS driver event manager interface file.
 */

#ifndef DSS_EVTMGR_H_
#define DSS_EVTMGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/fvid2.h>
#include <drivers/dss.h>
#include <kernel/dpl/HwiP.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief This typedef defines the Event manager callback function prototype.
 *   Client registers this callback with the event manager and when event
 *   occurs, event manager calls this callback.
 *
 *  \param  event       This is an array of events occurred when interrupt came.
 *                      Event manager passes this list to the client.
 *  \param  numEvents   This tells number of events occurred.
 *  \param  arg         Client's Private Data
 */
typedef void (*Dss_evtMgrCbFxn)(const uint32_t *event,
                                uint32_t numEvents,
                                void *arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

struct Dss_EvtMgrInitParams_t
{
    uint32_t dssCommonRegionId;
    /**< DSS Common Region Id. Refer \ref CSL_DssCommRegId for values */
    uint32_t numIrq;
    /**< Number of valid entries in below two arrays */
    uint32_t instId[DSS_EVT_MGR_INST_ID_MAX];
    /**< Instance Ids */
    uint32_t irqNum[DSS_EVT_MGR_INST_ID_MAX];
    /**< Interrupt numbers */
};

typedef struct
{
    uint32_t eventGroup;
    /**< This tells the event group into which registered event belongs. Refer
         \ref Dss_EventGroup for values*/
} Dss_EvtMgrClientInfo;

/**
 *  \brief structure containing instance specific information, there should be
 *         one instance object for each independent IRQ
 */
typedef struct
{
    uint32_t isInitDone;
    /**< Flag to indicate that the instance is initialized */
    uint32_t dssCommonRegionId;
    /**< DSS Common Region Id. Refer \ref CSL_DssCommRegId for values */
    uint32_t instId;
    /**< Event manager Instance Id. Refer \ref Dss_EvtMgrInstId for values */
    uint32_t irqNum;
    /**< IRQ number at CPU level INTC */
    Fvid2Utils_Node *headNode;
    /**< Pointer to the head node of the priority linked list. */
    HwiP_Object intrHandle;
    /**< Handle to Hardware Interrupt */
    uint32_t numIntr;
    /**< Total number of interrupts occurred since last initialization */
    Fvid2Utils_TsPrfLog isrPrfLog;
    /**< ISR duration performance log. */
} Dss_EvtMgrInstObj;

struct Dss_EvtMgrInfo_t
{
    volatile void *l0EnableReg;
    /**< Address of the level 0 enable register */
    volatile void *l0StatusReg;
    /**< Address of the level 0 status register */
    volatile void *l0DisableReg;
    /**< Address of the level 0 disable register */
    uint32_t l0Mask;
    /**< Bit mask for checking and clearing the level 0 status */
    volatile void *l1EnableReg[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    /**< Address of the level 1 enable register */
    volatile void *l1StatusReg[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    /**< Address of the level 1 status register */
    uint32_t l1Mask[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    /**< Bit mask for checking and clearing the status of the event/IRQ */
    Dss_evtMgrCbFxn clientCb;
    /**< Client's callback function. This function will be called by the
     *   event manager whenever client registered event occurs */
    void *arg;
    /**< Client's private data to be passed to it when callback function is
     *   called */
    uint32_t eventGroup;
    /**< This tells the event group into which registered event belongs. Refer
     *   \ref Dss_EventGroup for values */
    uint32_t numIntr;
    /**< Number of interrupts occurred for this client */
    Dss_EvtMgrInstObj  *instObj;
    /**< Pointer to the Instance Object */
    uint32_t allEvents[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    /**< List of events for which client has registered callback */
    uint32_t setEvents[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    /**< This array contains the list of events occurred at the time of
     *   interrupt. It will be passed down to the clients.*/
    uint32_t numEvents;
    /**< Count of events for client has registered callback. */
};

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 *  \brief Dss_EvtMgrInitParams structure init function.
 *
 *  \param  evtMgrParams  Pointer to #Dss_EvtMgrInitParams structure.
 *
 *  \return None
 */
static inline void Dss_evtMgrInitParamsInit(Dss_EvtMgrInitParams *evtMgrParams);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t Dss_evtMgrInit(const Dss_EvtMgrInitParams *initPrms);

int32_t Dss_evtMgrDeInit(void);

void *Dss_evtMgrRegister(uint32_t instId,
                         uint32_t eventGroup,
                         const uint32_t *event,
                         uint32_t numEvents,
                         Dss_evtMgrCbFxn callback,
                         void *arg);

int32_t Dss_evtMgrUnRegister(void *handle);

int32_t Dss_evtMgrDisable(void *handle);

int32_t Dss_evtMgrEnable(void *handle);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Dss_evtMgrInitParamsInit(Dss_EvtMgrInitParams *evtMgrParams)
{
    uint32_t i;
    if(NULL != evtMgrParams)
    {
        evtMgrParams->dssCommonRegionId = CSL_DSS_COMM_REG_ID_0;
        evtMgrParams->numIrq = 0U;
        for(i=0U; i<DSS_EVT_MGR_INST_ID_MAX; i++)
        {
            evtMgrParams->instId[i] = 0x0U;
            evtMgrParams->irqNum[i] = 0x0U;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_EVTMGR_H_ */
