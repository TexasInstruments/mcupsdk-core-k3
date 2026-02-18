/*
 *  Copyright (C) 2018-2026 Texas Instruments Incorporated
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

#include <stdlib.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>

/** \brief Task Ids to be used for the user and DM tasks */
#ifndef SCISERVER_TASKIDS_DEFINED
#define SCISERVER_TASKIDS_DEFINED
enum Sciserver_TaskIds {
    /**< User High priority Task ID */
    SCISERVER_TASK_USER_HI = 0,
    /**< User Low priority Task ID */    
    SCISERVER_TASK_USER_LO = 1,
    /**< User Max Task ID */
    SCISERVER_TASK_MAX_CNT = 2,
};
#endif

#ifndef SCISERVER_TIRTOSCFGPRMS_DEFINED
#define SCISERVER_TIRTOSCFGPRMS_DEFINED
/** \brief Sciserver App Configuration Parameters */
typedef struct {
    /**< Task Priorities */
    uint32_t taskPriority[SCISERVER_TASK_MAX_CNT];
    /**< Stack buffer for high-priority task */
    uint8_t *hiTaskStack;
    /**< Stack buffer for low-priority task */
    uint8_t *loTaskStack;
    /**< Stack size for the tasks */
    uint32_t taskStackSize;
} Sciserver_TirtosCfgPrms_t ;
#endif

/** \brief Initializing and starting the SCI server
 *  \param sciserverCfg Pointer to #Sciserver_TirtosCfgPrms_t
 */

void sciServer_init(Sciserver_TirtosCfgPrms_t *sciserverCfg);
