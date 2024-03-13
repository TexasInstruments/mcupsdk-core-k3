/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#ifndef PMUP_ARMV7R_H
#define PMUP_ARMV7R_H

#ifdef __cplusplus
extern "C"
{
#endif


#define PmuP_EVENT_TYPE_ICACHE_MISS                                   (0x01U)
#define PmuP_EVENT_TYPE_DCACHE_MISS                                   (0x03U)
#define PmuP_EVENT_TYPE_I_X                                           (0x08U)
#define PmuP_EVENT_TYPE_ICACHE_ACCESS                                 (0x58U)

#ifndef PMU_SECTION
#define PMU_SECTION __attribute__((section(".text.pmu")))
#endif

/**
 *  \brief Configure PMU counters
 *
 *  \param cycleCntDiv cycle count div
 *
 *  \param exportEvents export events
 *
 *  \param userEnable value 1 to enable
 *
 *  \return None
 */
void PmuP_Config( uint32_t cycleCntDiv, uint32_t exportEvents, uint32_t userEnable );

/**
 *  \brief Configure PMU counter
 *
 *  \param counterNumber counter number
 *
 *  \param eventType event type
 *
 *  \return None
 */
void PmuP_ConfigCounter( uint32_t counterNumber, uint32_t eventType );

/**
 *  \brief Enable all PMU counters
 *
 *  \param enable value 1 to enable
 *
 *  \return None
 */
void PmuP_EnableAllCounters( uint32_t enable );

/**
 *  \brief Reset PMU counters
 *
 *  \param None
 *
 *  \return None
 */
void PmuP_ResetCounters( void );

/**
 *  \brief Enable PMU counter
 *
 *  \param counterNumber Counter number
 *
 *  \param enable value 1 to enable
 *
 *  \return None
 */
void PmuP_enableCounter( uint32_t counterNumber, uint32_t enable );

/**
 *  \brief Read counter
 *
 *  \param counterNumber Counter number
 *
 *  \return Counter value
 */
uint32_t PmuP_ReadCounter( uint32_t counterNumber );

/**
 *  \brief Enable PMU counter overflow interrupt
 *
 *  \param counterNumber Counter number
 *
 *  \param enable value 1 to enable
 *
 *  \return None
 */
void PmuP_EnableCounterOverflowInterrupt( uint32_t counterNumber, uint32_t enable );

#ifdef __cplusplus
}
#endif

#endif /* PMUP_ARMV7R_H */
