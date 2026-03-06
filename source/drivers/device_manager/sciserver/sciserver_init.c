/*
 *  Copyright (C) 2018-26 Texas Instruments Incorporated
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

/** \brief Sciserver Get Version String Function
 *  \param None
 *  \return string with Sciserver version info
 */
extern char * Sciserver_getVersionStr(void);

/** \brief Sciserver Get RM_PM_HAL Version String Function
 *  \param None
 *  \return string with RM_PM_HAL version info
 */
extern char * Sciserver_getRmPmHalVersionStr(void);

extern int32_t Sciserver_tirtosInitPrms_Init(Sciserver_TirtosCfgPrms_t *pPrms);


int32_t Sciserver_tirtosInitPrms_Init(Sciserver_TirtosCfgPrms_t *pPrms)
{
    int32_t ret = SystemP_SUCCESS;
    if (pPrms != NULL)
    {
#if defined (SOC_AM62PX)
        pPrms->taskPriority[SCISERVER_TASK_USER_LO] = 30U;
        pPrms->taskPriority[SCISERVER_TASK_USER_HI] = 31U;
#elif defined (SOC_J722S)
        pPrms->taskPriority[SCISERVER_TASK_USER_LO] = 29U;
        pPrms->taskPriority[SCISERVER_TASK_USER_HI] = 30U;
#else
        pPrms->taskPriority[SCISERVER_TASK_USER_LO] = 1U;
        pPrms->taskPriority[SCISERVER_TASK_USER_HI] = 3U;
#endif
    }
    else
    {
        ret = SystemP_FAILURE;
    }
    return ret;
}

/** \brief Initializing and starting the SCI server
 *  \param sciserverCfg Pointer to #Sciserver_TirtosCfgPrms_t
 */

void sciServer_init(Sciserver_TirtosCfgPrms_t *sciserverCfg)
{
    int32_t ret = SystemP_SUCCESS;

#if !defined(DEBUG_LOG_DISABLE) && DebugP_LOG_ENABLED
    char *version_str = NULL;
    char *rmpmhal_version_str = NULL;
#endif

    ret = Sciserver_tirtosInitPrms_Init(sciserverCfg);
    if (ret != SystemP_SUCCESS)
    {
        DebugP_log("ret variable init FAILED, ret=%d\r\n", ret);
    }

    if (ret == SystemP_SUCCESS)
    {
        ret = Sciserver_tirtosInit(sciserverCfg);
    }
    else
    {
        DebugP_log("Sciserver_tirtosInitPrms_Init FAILED, ret=%d\r\n", ret);
    }

#if !defined(DEBUG_LOG_DISABLE) && DebugP_LOG_ENABLED
    version_str = Sciserver_getVersionStr();
    rmpmhal_version_str = Sciserver_getRmPmHalVersionStr();

    DebugP_log("Sciserver Testapp Built On: %s %s\r\n", __DATE__, __TIME__);
    DebugP_log("Sciserver Version: %s\r\n", version_str);
    DebugP_log("RM_PM_HAL Version: %s\r\n", rmpmhal_version_str);
    if (ret == SystemP_SUCCESS)
    {
       DebugP_log("Starting Sciserver..... PASSED\r\n");
    }
    else
    {
        DebugP_log("Starting Sciserver (Sciserver_tirtosInit) FAILED, ret=%d\r\n", ret);
    }
#endif

    return;
}
