/*
 *  Copyright (C) 2018-2022 Texas Instruments Incorporated
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

#include <drivers/device_manager/sciserver/sciserver_init.h>
#include <drivers/device_manager/sciclient.h>

/** \brief Task Ids to be used for the user and DM tasks */
enum Sciserver_TaskIds {
    SCISERVER_TASK_USER_HI = 0,
    /**< User High priority Task ID */
    SCISERVER_TASK_USER_LO = 1,
    /**< User Low priority Task ID */
    SCISERVER_TASK_MAX_CNT = 2,
    /**< User Max Task ID */
};

/** \brief Sciserver App Configuration Parameters */
typedef struct {
    uint32_t taskPriority[SCISERVER_TASK_MAX_CNT];
    /**< Task Priorities */
} Sciserver_TirtosCfgPrms_t ;

/** \brief Sciserver TI-RTOS Application Init.
 *
 *         NOTE: If this function is called form a Task Context
 *         (i.e, not from main / after starting the Schedular),
 *         the callee Task should be of priority higher than
 *         max of passed init param(pPrms) Task priorities
 *         i.e Sciserver_TirtosCfgPrms_t->taskPriority[x]
 *
 *  \param pPrms Pointer to #Sciserver_TirtosCfgPrms_t
 *  \return CSL_PASS if the init has happened correctly.
 *          CSL_EFAIL if otherwise.
 */
extern int32_t Sciserver_tirtosInit(Sciserver_TirtosCfgPrms_t *pPrms);

/** \brief Initialize the init params for SCISERVER.
 *  \param pPrms Pointer to the init parameters.
 *  \return CSL_PASS if init Params are initilized with some default.
 *          CSL_EFAIL otherwise.
 */
static int32_t Sciserver_tirtosInitPrms_Init(Sciserver_TirtosCfgPrms_t *pPrms)
{
    int32_t ret = SystemP_SUCCESS;
    if (pPrms != NULL)
    {
        pPrms->taskPriority[SCISERVER_TASK_USER_LO] = 1U;
        pPrms->taskPriority[SCISERVER_TASK_USER_HI] = 3U;
    }
    else
    {
        ret = SystemP_FAILURE;
    }
    return ret;
}

/** \brief Sciserver Get Version String Function
 *  \param None
 *  \return string with Sciserver version info
 */
extern char * Sciserver_getVersionStr();

/** \brief Sciserver Get RM_PM_HAL Version String Function
 *  \param None
 *  \return string with RM_PM_HAL version info
 */
extern char * Sciserver_getRmPmHalVersionStr();


/** \brief Initializing and starting the SCI server
 *  \param None
 */

void sciServer_init(void)
{
    int32_t ret = SystemP_SUCCESS;
    char *version_str = NULL;
    char *rmpmhal_version_str = NULL;
    Sciserver_TirtosCfgPrms_t appPrms;

    if (ret == SystemP_SUCCESS)
    {
        ret = Sciserver_tirtosInitPrms_Init(&appPrms);
    }
    else
    {
        DebugP_log("ret variable init FAILED, ret=%d\r\n", ret);
    }

    if (ret == SystemP_SUCCESS)
    {
        ret = Sciserver_tirtosInit(&appPrms);
    }
    else
    {
        DebugP_log("Sciserver_tirtosInitPrms_Init FAILED, ret=%d\r\n", ret);
    }

    version_str = Sciserver_getVersionStr();
    rmpmhal_version_str = Sciserver_getRmPmHalVersionStr();

    DebugP_log("Sciserver Testapp Built On: %s %s\r\n", __DATE__, __TIME__);
    DebugP_log("Sciserver Version: %s\r\n", version_str);
    DebugP_log("RM_PM_HAL Version: %s\r\n", rmpmhal_version_str);
    if (ret == SystemP_SUCCESS)
    {
       DebugP_log("Starting Sciserver..... PASSED\r\n");

        uint32_t freqHz;
#if defined (SOC_AM62X) || defined (SOC_AM62AX)
        Sciclient_pmGetModuleClkFreq(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);
#else
        Sciclient_pmGetModuleClkFreq(TISCI_DEV_GTC0, TISCI_DEV_GTC0_GTC_CLK,
            (uint64_t *) &freqHz, SystemP_WAIT_FOREVER);
#endif
       DebugP_log("GTC freq: %d\r\n", freqHz);

    }
    else
    {
        DebugP_log("Starting Sciserver (Sciserver_tirtosInit) FAILED, ret=%d\r\n", ret);
    }
    return;
}