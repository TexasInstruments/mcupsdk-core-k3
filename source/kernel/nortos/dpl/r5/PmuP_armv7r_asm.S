/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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


        .text

/* FUNCTION DEF: uint32_t CycleCounterP_getCount32(void) */
        .global CycleCounterP_getCount32
        .type CycleCounterP_getCount32,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
CycleCounterP_getCount32:
        MRC     p15, #0, r0, c9, c13, 0  // read PMCCNTR
        bx      LR

/* FUNCTION DEF: void PmuP_setup(uint32_t) */
        .global PmuP_setup
        .type PmuP_setup,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_setup:
        MCR     p15, #0, r0, c9, c12, 0 // write PMCR
        bx      LR


/* FUNCTION DEF: void PmuP_Config( uint32_t cycleCntDiv, uint32_t exportEvents, uint32_t userEnable ) */
        .global PmuP_Config
        .type PmuP_Config,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_Config:
        MRC     p15, #0, r3, c9, c12, #0        // Read PMCR Register
        BIC     r3, r3, #((1<<3) | (1<<4))      // Clear D and X bits
        CMP     r0, #0
        BEQ     PmuP_Config_00
        ORR     r3, r3, #(1<<3)                 // Set D bit
PmuP_Config_00:
        CMP     r1, #0
        BEQ     PmuP_Config_01
        ORR     r3, r3, #(1<<4)                 // Set X bit
PmuP_Config_01:
        MCR     p15, #0, r3, c9, c12, #0        // Write PMCR Register
        EOR     r3, r3, r3                      // Clear r3
        CMP     r2, #0
        BEQ     PmuP_Config_02
        ORR     r3, r3, #1
PmuP_Config_02:
        MCR     p15, #0, r3, c9, c14, #0        // Write PMUSERENR Register
        bx      lr

/* FUNCTION DEF: void PmuP_ConfigCounter( uint32_t counterNumber, CSL_ArmR5PmuEventType eventType ) */
        .global PmuP_ConfigCounter
        .type PmuP_ConfigCounter,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_ConfigCounter:
    PUSH    {lr}
    BL      PmuP_SelectCounter          // Select register
    AND     r1, r1, #0xFF
    MCR     p15, #0, r1, c9, c13, #1        // Write PMXEVTYPERx Register
    POP     {lr}
    BX      lr


/* FUNCTION DEF: void PmuP_SelectCounter( uint32_t counterNumber ) */
        .global PmuP_ConfigCounter
        .type PmuP_ConfigCounter,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_SelectCounter:
    AND     r0, r0, #0x1F
    MCR     p15, #0, r0, c9, c12, #5        // Write PMSELR Register
    BX      lr


/* FUNCTION DEF: void PmuP_ResetCounters( void ) */
        .global PmuP_ResetCounters
        .type PmuP_ResetCounters,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_ResetCounters:
    MRC     p15, #0, r0, c9, c12, #0        // Read PMCR
    ORR     r0, r0, #(1<<1)                 // Set P bit to reset all event counters to zero
    MCR     p15, #0, r0, c9, c12, #0        // Write modified PMCR
    BX      lr

/* FUNCTION DEF: void PmuP_enableCounters(uint32_t) */
        .global PmuP_enableCounters
        .type PmuP_enableCounters,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_enableCounters:
        MCR     p15, #0, r0, c9, c12, 1  // write PMCNTENSET
        bx      LR

/* FUNCTION DEF: void PmuP_disableCounters(uint32_t) */
        .global PmuP_disableCounters
        .type PmuP_disableCounters,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_disableCounters:
        MCR     p15, #0, r0, c9, c12, 2  // write PMCNTENCLR
        bx      LR

/* FUNCTION DEF: void PmuP_enableCounter( uint32_t counterNumber, uint32_t enable ) */
        .global PmuP_enableCounter
        .type PmuP_enableCounter,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_enableCounter:
    AND     r0, r0, #0x1F                   // counterNumber must be <= 31
    MOV     r2, #1
    LSL     r0, r2, r0                      // r0 is bit-mask corresponding to counterNumber
    CMP     r1, #0
    BEQ     PmuP_enableCounter_clear
    MCR     p15, #0, r0, c9, c12, #1        // Write PMCNTENSET Register (writes of 0 have no effect)
    B       PmuP_enableCounter_00
PmuP_enableCounter_clear:
    MCR     p15, #0, r0, c9, c12, #2        // Write PMCNTENCLR Register (writes of 0 have no effect)
PmuP_enableCounter_00:
    BX      lr

/* FUNCTION DEF: void PmuP_EnableAllCounters( uint32_t enable ) */
        .global PmuP_EnableAllCounters
        .type PmuP_EnableAllCounters,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_EnableAllCounters:
        MRC     p15, #0, r1, c9, c12, #0        // Read PMCR
        CMP     r0, #0
        BEQ     PmuP_EnableAllCounters_disable
        ORR     r1, r1, #0x1                    // Set E bit to enable all counters
        B       PmuP_EnableAllCounters_00
PmuP_EnableAllCounters_disable:
        BIC     r1, r1, #0x1                    // Clr E bit to disable all counters
PmuP_EnableAllCounters_00:
        MCR     p15, #0, r1, c9, c12, #0        // Write modified PMCR
        bx      lr

/* FUNCTION DEF: uint32_t PmuP_ReadCounter( uint32_t counterNumber ); */
        .global PmuP_ReadCounter
        .type PmuP_ReadCounter,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_ReadCounter:
    PUSH    {lr}
    CMP     r0, #0x1F
    BEQ     PmuP_ReadCounter_cycles
    BL      PmuP_SelectCounter          // Select register
    MRC     p15, #0, r0, c9, c13, #2        // Read current PMNx Register
    B       PmuP_ReadCounter_00
PmuP_ReadCounter_cycles:
    MRC     p15, #0, r0, c9, c13, #0        // Read PMCCNTR Register
PmuP_ReadCounter_00:
    POP     {lr}
    BX      lr

/* FUNCTION DEF: void PmuP_EnableCounterOverflowInterrupt( uint32_t counterNumber, uint32_t enable ) */
        .global PmuP_EnableCounterOverflowInterrupt
        .type PmuP_EnableCounterOverflowInterrupt,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_EnableCounterOverflowInterrupt:
    AND     r0, r0, #0x1F                   // counterNumber must be <= 31
    MOV     r2, #1
    LSL     r0, r2, r0                      // r0 is bit-mask corresponding to counterNumber
    CMP     r1, #0
    BEQ     PmuP_EnableCounterOverflowInterrupt_clear
    MCR     p15, #0, r0, c9, c14, #1        // Write PMINTENSET Register (writes of 0 have no effect)
    B       PmuP_EnableCounterOverflowInterrupt_00
PmuP_EnableCounterOverflowInterrupt_clear:
    MCR     p15, #0, r0, c9, c14, #2        // Write PMINTENCLR Register (writes of 0 have no effect)
PmuP_EnableCounterOverflowInterrupt_00:
    BX      lr

/* FUNCTION DEF: uint32_t PmuP_getOverflowStatus(void) */
        .global PmuP_getOverflowStatus
        .type PmuP_getOverflowStatus,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_getOverflowStatus:
        MRC     p15, 0, r0, c9, c12, 3  // read PMOVSR
        bx      LR

/* FUNCTION DEF: uint32_t PmuP_clearOverflowStatus(void) */
        .global PmuP_clearOverflowStatus
        .type PmuP_clearOverflowStatus,%function
        .section ".text.pmu","ax",%progbits
        .arm
        .align 2
PmuP_clearOverflowStatus:
        MCR     p15, 0, r0, c9, c12, 3  // write PMOVSR
        bx      LR

	.end

