/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
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
 * \file osal_hwi.h
 *
 * OSAL Core Public APIs used for hwi control
 *
 */

#ifndef OSAL_HWI_H
#define OSAL_HWI_H

#include <types/short_types.h>
#include <types/errno.h>
// #include <ti/osal/HwiP.h> //tdt
#include <kernel/dpl/HwiP.h>

/**
 * \brief Disable interrupts globally and unconditionally.
 *
 * \return A key to be used with hwip_restore representing current state.
 */
static inline u32 osal_hwip_disable(void)
{
        return HwiP_disable();
}


/**
 * \brief Restore interrupts to a previous state held in key.
 *
 * \param key Value returned from hwip_enable or hwip_disable.
 *
 * This call is used to restore interrupts to the state previous to a call
 * to hwip_enable or hwip_disable when the returned key value is passed.
 */
static inline void osal_hwip_restore(u32 key)
{
        return HwiP_restore(key);
}

#endif /* OSAL_HWI_H */

