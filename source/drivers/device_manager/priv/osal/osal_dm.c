/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 *
 */

/*
 * \file osal_dm.c
 *
 * OSAL APIs for controlling DM
 *
 */

#include <string.h>
#include <types/short_types.h>
#include <kernel/dpl/TaskP.h>
#include <osal_dm.h>
#include <drivers/device_manager/sciserver_tirtos.h>
#include <kernel/nortos/dpl/r5/HwiP_armv7r_vim.h>

#ifndef MCU_PLUS_SDK
extern void CSL_armR5StartupIntrEnableVic( uint32_t enable );
#endif

/**
 * \brief Disable interrupts used by DM firmware
 *
 * \return None
 */
void osal_dm_disable_interrupt(void)
{
        Sciserver_tirtosDisableIntr();
}


/**
 * \brief Enable interrupts used by DM firmware
 *
 * \return None
 */
void osal_dm_enable_interrupt(void)
{
        Sciserver_tirtosEnableIntr();
}

/**
 * \brief Suspend DM firmware
 *
 * \return None
 */
void osal_suspend_dm(void)
{
        TaskP_disable();
        OS_StopTickTimer();
        #if defined MCU_PLUS_SDK
            HwiP_disableVIC();
        #else
            CSL_armR5StartupIntrEnableVic(0);  /* Disable VIC */
        #endif

}

static void copyDM_ResetVectors(void){
        void _freertosresetvectors (void);
        memcpy((void *)0x0, (void *)_freertosresetvectors , 0x40);
}

/**
 * \brief Resume DM firmware
 *
 * \return CSL_PASS if it is a success, else error
 */
u32 osal_resume_dm(void)
{
        copyDM_ResetVectors();
        #if defined MCU_PLUS_SDK
            HwiP_enableVIC();
        #else
            CSL_armR5StartupIntrEnableVic(1);      /* Enable VIC mode */
        #endif
        OS_StartTickTimer();
        TaskP_restore(0);
        return 0;
}

s32 osal_dm_copy_fs_stub_from_ddr_to_local_mem(void)
{
    return (Sciclient_copyLPMFSStubToLocalMem());
}
