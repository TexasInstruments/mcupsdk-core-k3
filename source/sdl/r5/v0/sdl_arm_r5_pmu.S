/*
 * Copyright (c) 2021-25 Texas Instruments Incorporated
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
    .text

/*==============================================================================
*   void SDL_pmuSelectCntr( uint32_t cntrNum )
==============================================================================*/
SDL_pmuSelectCntr:
    AND     r0, r0, #0x1F
    MCR     p15, #0, r0, c9, c12, #5        /* Write PMSELR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_cfg( uint32_t cycleCntDiv, uint32_t exportEvents, uint32_t userEnable)
* 	Design: PROC_SDL-2108
==============================================================================*/
    .global SDL_R5PMU_cfg
SDL_R5PMU_cfg:
    MRC     p15, #0, r3, c9, c12, #0        /* Read PMCR Register */
    BIC     r3, r3, #((1<<3) | (1<<4))      /* Clear D and X bits */
    CMP     r0, #0
    BEQ     armR5PmuCfg_00
    ORR     r3, r3, #(1<<3)                 /* Set D bit */
armR5PmuCfg_00:
    CMP     r1, #0
    BEQ     armR5PmuCfg_01
    ORR     r3, r3, #(1<<4)                 /* Set X bit */
armR5PmuCfg_01:
    MCR     p15, #0, r3, c9, c12, #0        /* Write PMCR Register */
    EOR     r3, r3, r3                      /* Clear r3 */
    CMP     r2, #0
    BEQ     armR5PmuCfg_02
    ORR     r3, r3, #1
armR5PmuCfg_02:
    MCR     p15, #0, r3, c9, c14, #0        /* Write PMUSERENR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_readStaticRegisters(SDL_PMU_staticRegs *pStaticRegs)
* 	Design: PROC_SDL-2495
==============================================================================*/
    .global SDL_R5PMU_readStaticRegisters
SDL_R5PMU_readStaticRegisters:
    MRC     p15, #0, r1, c9, c12, #0        /* Read PMCR Register */
	MOV 	r4, r1
    AND     r1, r1, #0x10                   /* Get X bit from PMCR register */
	CMP		r1, #0x10
	BEQ     getStatic_00
	MOV     r1, #0
	STR     r1, [r0]
	B       next_00
getStatic_00:
	MOV     r1, #1
	STR     r1, [r0]
next_00:
    AND     r4, r4, #0x08                   /* Get D bit from PMCR register */
	CMP		r4, #0x08
	ADD     r0, r0, #0x1
	BEQ     getStatic_01
	MOV     r4, #0
	STR     r4, [r0]
	B       next_01
getStatic_01:
	MOV     r4, #1
	STR     r4, [r0]
next_01:
    MRC     p15, #0, r2, c9, c14, #0        /* Read PMUSERENR Register */
	AND     r2,r2, #0x01
	ADD     r0 , r0, #0x1					/* Get User mode access enable bit */
	STR     r2, [r0]
	MRC     p15, #0, r3, c9, c12, #1        /* Read PMCNTENSET Register (writes of 0 have no effect) */
	ADD     r0, r0, #0x2
	STR     r3, [r0]
    BX      lr

/*==============================================================================
*   int32_t SDL_R5PMU_verifyCfg(uint32_t cycleCntDiv, uint32_t exportEvents)
* 	Design: PROC_SDL-2109
==============================================================================*/
    .global SDL_R5PMU_verifyCfg
SDL_R5PMU_verifyCfg:
    PUSH    {r4}
	PUSH    {r3}
    MRC     p15, #0, r4, c9, c12, #0        /* Read PMCR Register */
    AND     r4, r4, #0x18
	EOR     r3, r3, r3                      /* Clear r3 */
	CMP     r0, #0
    BEQ     armR5VerifyPmuCfg_00
    ORR     r3, r3, #(1<<3)
armR5VerifyPmuCfg_00:
    CMP     r1, #0
    BEQ     armR5VerifyPmuCfg_01
    ORR     r3, r3, #(1<<4)
armR5VerifyPmuCfg_01:
	SUBS    r4, r3, r4
    BEQ     armR5PmuVerifyCfgRegion_pass1
    MVN     r0, #0x0                        /* -1 in return value */
armR5PmuVerifyCfgRegion_pass1:
    ISB
    POP     {r4}
	POP     {r3}
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableAllCntrs ( uint32_t enable )
* 	Design: PROC_SDL-2112
==============================================================================*/
    .global SDL_R5PMU_enableAllCntrs
SDL_R5PMU_enableAllCntrs:
    MRC     p15, #0, r1, c9, c12, #0        /* Read PMCR */
    CMP     r0, #0
    BEQ     armR5PmuEnableAllCntrs_disable
    ORR     r1, r1, #0x1                    /* Set E bit to enable all counters */
    B       armR5PmuEnableAllCntrs_00
armR5PmuEnableAllCntrs_disable:
    BIC     r1, r1, #0x1                    /* Clr E bit to disable all counters */
armR5PmuEnableAllCntrs_00:
    MCR     p15, #0, r1, c9, c12, #0        /* Write modified PMCR */
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_getNumCntrs( void )
* 	Design: PROC_SDL-2420
==============================================================================*/
    .global SDL_R5PMU_getNumCntrs
SDL_R5PMU_getNumCntrs:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR (Performance Monitor Control Register) */
    LSR     r0, r0, #11                     /* Shift and */
    AND     r0, r0, #0x1F                   /*   mask to get N */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_cfgCntr( uint32_t cntrNum, SDL_R5PmuEventType eventType )
* 	Design: PROC_SDL-2110
==============================================================================*/
    .global SDL_R5PMU_cfgCntr
SDL_R5PMU_cfgCntr:
    PUSH    {lr}
    BL      SDL_pmuSelectCntr          /* Select register */
    AND     r1, r1, #0xFF
    MCR     p15, #0, r1, c9, c13, #1        /* Write PMXEVTYPERx Register */
    POP     {lr}
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableCntrOverflowIntr( uint32_t cntrNum, uint32_t enable )
* 	Design: PROC_SDL-2115
==============================================================================*/
    .global SDL_R5PMU_enableCntrOverflowIntr
SDL_R5PMU_enableCntrOverflowIntr:
    AND     r0, r0, #0x1F                   /* cntrNum must be <= 31 */
    MOV     r2, #1
    LSL     r0, r2, r0                      /* r0 is bit-mask corresponding to cntrNum */
    CMP     r1, #0
    BEQ     armR5PmuEnableCntrOverflowIntr_clear
    MCR     p15, #0, r0, c9, c14, #1        /* Write PMINTENSET Register (writes of 0 have no effect) */
    B       armR5PmuEnableCntrOverflowIntr_00
armR5PmuEnableCntrOverflowIntr_clear:
    MCR     p15, #0, r0, c9, c14, #2        /* Write PMINTENCLR Register (writes of 0 have no effect) */
armR5PmuEnableCntrOverflowIntr_00:
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableCntr ( uint32_t cntrNum, uint32_t enable )
* 	Design: PROC_SDL-2113
==============================================================================*/
    .global SDL_R5PMU_enableCntr
SDL_R5PMU_enableCntr:
    AND     r0, r0, #0x1F                   /* cntrNum must be <= 31 */
    MOV     r2, #1
    LSL     r0, r2, r0                      /* r0 is bit-mask corresponding to cntrNum */
    CMP     r1, #0
    BEQ     armR5PmuEnableCntrs_clear
    MCR     p15, #0, r0, c9, c12, #1        /* Write PMCNTENSET Register (writes of 0 have no effect) */
    B       armR5PmuEnableCntrs_00
armR5PmuEnableCntrs_clear:
    MCR     p15, #0, r0, c9, c12, #2        /* Write PMCNTENCLR Register (writes of 0 have no effect) */
armR5PmuEnableCntrs_00:
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_readCntr( uint32_t cntrNum )
* 	Design: PROC_SDL-2116
==============================================================================*/
    .global SDL_R5PMU_readCntr
SDL_R5PMU_readCntr:
    PUSH    {lr}
    CMP     r0, #0x1F                        /* SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM */
    BEQ     armR5PmuReadCntr_cycles
    BL      SDL_pmuSelectCntr          /* Select register */
    MRC     p15, #0, r0, c9, c13, #2        /* Read current PMNx Register */
    B       armR5PmuReadCntr_00
armR5PmuReadCntr_cycles:
    MRC     p15, #0, r0, c9, c13, #0        /* Read PMCCNTR Register */
armR5PmuReadCntr_00:
    POP     {lr}
    BX      lr

/*==============================================================================
*   void  SDL_R5PMU_setResetCntr( uint32_t cntrNum, uint32_t cntrVal )
* 	Design: PROC_SDL-2114
==============================================================================*/
    .global SDL_R5PMU_setResetCntr
SDL_R5PMU_setResetCntr:
    PUSH    {lr}
    CMP     r0, #0x1F                      /* SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM */
    BEQ     armR5PmuSetCntr_cycles
    BL      SDL_pmuSelectCntr          /* Select register */
    MCR     p15, #0, r1, c9, c13, #2        /* Write current PMNx Register */
    B       armR5PmuSetCntr_00
armR5PmuSetCntr_cycles:
    MCR     p15, #0, r1, c9, c13, #0        /* Write PMCCNTR Register */
armR5PmuSetCntr_00:
    POP     {lr}
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_readCntrOverflowStatus( void )
* 	Design: PROC_SDL-2421
==============================================================================*/
    .global SDL_R5PMU_readCntrOverflowStatus
SDL_R5PMU_readCntrOverflowStatus:
    MRC     p15, #0, r0, c9, c12, #3        /* Read PMOVSR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_clearCntrOverflowStatus ( uint32_t cntrMask )
* 	Design: PROC_SDL-2111
==============================================================================*/
    .global SDL_R5PMU_clearCntrOverflowStatus
SDL_R5PMU_clearCntrOverflowStatus:
    MCR     p15, #0, r0, c9, c12, #3        /* Write PMOVSR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_resetCycleCnt ( void )
* 	Design: PROC_SDL-2117
==============================================================================*/
    .global SDL_R5PMU_resetCycleCnt
SDL_R5PMU_resetCycleCnt:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR */
    ORR     r0, r0, #(1<<2)                 /* Set C bit to reset the cycle counter, PMCCNTR, to zero */
    MCR     p15, #0, r0, c9, c12, #0        /* Write modified PMCR */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_resetCntrs( void )
* 	Design: PROC_SDL-2419
==============================================================================*/
    .global SDL_R5PMU_resetCntrs
SDL_R5PMU_resetCntrs:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR */
    ORR     r0, r0, #(1<<1)                 /* Set P bit to reset all event counters to zero */
    MCR     p15, #0, r0, c9, c12, #0        /* Write modified PMCR */
    BX      lr

    .end

/*
 * Copyright (c) 2021-24 Texas Instruments Incorporated
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
    .text

SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM:   .word        0x1F

/*==============================================================================
*   void SDL_pmuSelectCntr( uint32_t cntrNum )
==============================================================================*/
SDL_pmuSelectCntr:
    AND     r0, r0, #0x1F
    MCR     p15, #0, r0, c9, c12, #5        /* Write PMSELR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_cfg( uint32_t cycleCntDiv, uint32_t exportEvents, uint32_t userEnable)
* 	Design: PROC_SDL-2108
==============================================================================*/
    .global SDL_R5PMU_cfg
SDL_R5PMU_cfg:
    MRC     p15, #0, r3, c9, c12, #0        /* Read PMCR Register */
    BIC     r3, r3, #((1<<3) | (1<<4))      /* Clear D and X bits */
    CMP     r0, #0
    BEQ     armR5PmuCfg_00
    ORR     r3, r3, #(1<<3)                 /* Set D bit */
armR5PmuCfg_00:
    CMP     r1, #0
    BEQ     armR5PmuCfg_01
    ORR     r3, r3, #(1<<4)                 /* Set X bit */
armR5PmuCfg_01:
    MCR     p15, #0, r3, c9, c12, #0        /* Write PMCR Register */
    EOR     r3, r3, r3                      /* Clear r3 */
    CMP     r2, #0
    BEQ     armR5PmuCfg_02
    ORR     r3, r3, #1
armR5PmuCfg_02:
    MCR     p15, #0, r3, c9, c14, #0        /* Write PMUSERENR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_readStaticRegisters(SDL_PMU_staticRegs *pStaticRegs)
* 	Design: PROC_SDL-2495
==============================================================================*/
    .global SDL_R5PMU_readStaticRegisters
SDL_R5PMU_readStaticRegisters:
    MRC     p15, #0, r1, c9, c12, #0        /* Read PMCR Register */
	MOV 	r4, r1
    AND     r1, r1, #0x10                   /* Get X bit from PMCR register */
	CMP		r1, #0x10
	BEQ     getStatic_00
	MOV     r1, #0
	STR     r1, [r0]
	B       next_00
getStatic_00:
	MOV     r1, #1
	STR     r1, [r0]
next_00:
    AND     r4, r4, #0x08                   /* Get D bit from PMCR register */
	CMP		r4, #0x08
	ADD     r0, r0, #0x1
	BEQ     getStatic_01
	MOV     r4, #0
	STR     r4, [r0]
	B       next_01
getStatic_01:
	MOV     r4, #1
	STR     r4, [r0]
next_01:
    MRC     p15, #0, r2, c9, c14, #0        /* Read PMUSERENR Register */
	AND     r2,r2, #0x01
	ADD     r0 , r0, #0x1					/* Get User mode access enable bit */
	STR     r2, [r0]
	MRC     p15, #0, r3, c9, c12, #1        /* Read PMCNTENSET Register (writes of 0 have no effect) */
	ADD     r0, r0, #0x2
	STR     r3, [r0]
    BX      lr

/*==============================================================================
*   int32_t SDL_R5PMU_verifyCfg(uint32_t cycleCntDiv, uint32_t exportEvents)
* 	Design: PROC_SDL-2109
==============================================================================*/
    .global SDL_R5PMU_verifyCfg
SDL_R5PMU_verifyCfg:
    PUSH    {r4}
	PUSH    {r3}
    MRC     p15, #0, r4, c9, c12, #0        /* Read PMCR Register */
    AND     r4, r4, #0x18
	EOR     r3, r3, r3                      /* Clear r3 */
	CMP     r0, #0
    BEQ     armR5VerifyPmuCfg_00
    ORR     r3, r3, #(1<<3)
armR5VerifyPmuCfg_00:
    CMP     r1, #0
    BEQ     armR5VerifyPmuCfg_01
    ORR     r3, r3, #(1<<4)
armR5VerifyPmuCfg_01:
	SUBS    r4, r3, r4
    BEQ     armR5PmuVerifyCfgRegion_pass1
    MVN     r0, #0x0                        /* -1 in return value */
armR5PmuVerifyCfgRegion_pass1:
    ISB
    POP     {r4}
	POP     {r3}
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableAllCntrs ( uint32_t enable )
* 	Design: PROC_SDL-2112
==============================================================================*/
    .global SDL_R5PMU_enableAllCntrs
SDL_R5PMU_enableAllCntrs:
    MRC     p15, #0, r1, c9, c12, #0        /* Read PMCR */
    CMP     r0, #0
    BEQ     armR5PmuEnableAllCntrs_disable
    ORR     r1, r1, #0x1                    /* Set E bit to enable all counters */
    B       armR5PmuEnableAllCntrs_00
armR5PmuEnableAllCntrs_disable:
    BIC     r1, r1, #0x1                    /* Clr E bit to disable all counters */
armR5PmuEnableAllCntrs_00:
    MCR     p15, #0, r1, c9, c12, #0        /* Write modified PMCR */
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_getNumCntrs( void )
* 	Design: PROC_SDL-2420
==============================================================================*/
    .global SDL_R5PMU_getNumCntrs
SDL_R5PMU_getNumCntrs:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR (Performance Monitor Control Register) */
    LSR     r0, r0, #11                     /* Shift and */
    AND     r0, r0, #0x1F                   /*   mask to get N */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_cfgCntr( uint32_t cntrNum, SDL_R5PmuEventType eventType )
* 	Design: PROC_SDL-2110
==============================================================================*/
    .global SDL_R5PMU_cfgCntr
SDL_R5PMU_cfgCntr:
    PUSH    {lr}
    BL      SDL_pmuSelectCntr          /* Select register */
    AND     r1, r1, #0xFF
    MCR     p15, #0, r1, c9, c13, #1        /* Write PMXEVTYPERx Register */
    POP     {lr}
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableCntrOverflowIntr( uint32_t cntrNum, uint32_t enable )
* 	Design: PROC_SDL-2115
==============================================================================*/
    .global SDL_R5PMU_enableCntrOverflowIntr
SDL_R5PMU_enableCntrOverflowIntr:
    AND     r0, r0, #0x1F                   /* cntrNum must be <= 31 */
    MOV     r2, #1
    LSL     r0, r2, r0                      /* r0 is bit-mask corresponding to cntrNum */
    CMP     r1, #0
    BEQ     armR5PmuEnableCntrOverflowIntr_clear
    MCR     p15, #0, r0, c9, c14, #1        /* Write PMINTENSET Register (writes of 0 have no effect) */
    B       armR5PmuEnableCntrOverflowIntr_00
armR5PmuEnableCntrOverflowIntr_clear:
    MCR     p15, #0, r0, c9, c14, #2        /* Write PMINTENCLR Register (writes of 0 have no effect) */
armR5PmuEnableCntrOverflowIntr_00:
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_enableCntr ( uint32_t cntrNum, uint32_t enable )
* 	Design: PROC_SDL-2113
==============================================================================*/
    .global SDL_R5PMU_enableCntr
SDL_R5PMU_enableCntr:
    AND     r0, r0, #0x1F                   /* cntrNum must be <= 31 */
    MOV     r2, #1
    LSL     r0, r2, r0                      /* r0 is bit-mask corresponding to cntrNum */
    CMP     r1, #0
    BEQ     armR5PmuEnableCntrs_clear
    MCR     p15, #0, r0, c9, c12, #1        /* Write PMCNTENSET Register (writes of 0 have no effect) */
    B       armR5PmuEnableCntrs_00
armR5PmuEnableCntrs_clear:
    MCR     p15, #0, r0, c9, c12, #2        /* Write PMCNTENCLR Register (writes of 0 have no effect) */
armR5PmuEnableCntrs_00:
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_readCntr( uint32_t cntrNum )
* 	Design: PROC_SDL-2116
==============================================================================*/
    .global SDL_R5PMU_readCntr
SDL_R5PMU_readCntr:
    PUSH    {lr}
    CMP     r0, #0x1F                        /* SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM */
    BEQ     armR5PmuReadCntr_cycles
    BL      SDL_pmuSelectCntr          /* Select register */
    MRC     p15, #0, r0, c9, c13, #2        /* Read current PMNx Register */
    B       armR5PmuReadCntr_00
armR5PmuReadCntr_cycles:
    MRC     p15, #0, r0, c9, c13, #0        /* Read PMCCNTR Register */
armR5PmuReadCntr_00:
    POP     {lr}
    BX      lr

/*==============================================================================
*   void  SDL_R5PMU_setResetCntr( uint32_t cntrNum, uint32_t cntrVal )
* 	Design: PROC_SDL-2114
==============================================================================*/
    .global SDL_R5PMU_setResetCntr
SDL_R5PMU_setResetCntr:
    PUSH    {lr}
    CMP     r0, #0x1F                      /* SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM */
    BEQ     armR5PmuSetCntr_cycles
    BL      SDL_pmuSelectCntr          /* Select register */
    MCR     p15, #0, r1, c9, c13, #2        /* Write current PMNx Register */
    B       armR5PmuSetCntr_00
armR5PmuSetCntr_cycles:
    MCR     p15, #0, r1, c9, c13, #0        /* Write PMCCNTR Register */
armR5PmuSetCntr_00:
    POP     {lr}
    BX      lr

/*==============================================================================
*   uint32_t SDL_R5PMU_readCntrOverflowStatus( void )
* 	Design: PROC_SDL-2421
==============================================================================*/
    .global SDL_R5PMU_readCntrOverflowStatus
SDL_R5PMU_readCntrOverflowStatus:
    MRC     p15, #0, r0, c9, c12, #3        /* Read PMOVSR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_clearCntrOverflowStatus ( uint32_t cntrMask )
* 	Design: PROC_SDL-2111
==============================================================================*/
    .global SDL_R5PMU_clearCntrOverflowStatus
SDL_R5PMU_clearCntrOverflowStatus:
    MCR     p15, #0, r0, c9, c12, #3        /* Write PMOVSR Register */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_resetCycleCnt ( void )
* 	Design: PROC_SDL-2117
==============================================================================*/
    .global SDL_R5PMU_resetCycleCnt
SDL_R5PMU_resetCycleCnt:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR */
    ORR     r0, r0, #(1<<2)                 /* Set C bit to reset the cycle counter, PMCCNTR, to zero */
    MCR     p15, #0, r0, c9, c12, #0        /* Write modified PMCR */
    BX      lr

/*==============================================================================
*   void SDL_R5PMU_resetCntrs( void )
* 	Design: PROC_SDL-2419
==============================================================================*/
    .global SDL_R5PMU_resetCntrs
SDL_R5PMU_resetCntrs:
    MRC     p15, #0, r0, c9, c12, #0        /* Read PMCR */
    ORR     r0, r0, #(1<<1)                 /* Set P bit to reset all event counters to zero */
    MCR     p15, #0, r0, c9, c12, #0        /* Write modified PMCR */
    BX      lr

    .end
