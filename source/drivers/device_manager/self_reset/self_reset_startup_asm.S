//
// DM Stub firmware
//
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
//
// This software is licensed under the standard terms and conditions in the
// Texas Instruments Incorporated Technology and Software Publicly
// Available Software License Agreement, a copy of which is included in
// the software download.
//

    .global dm_r5_self_reset
    .global _self_reset_start
	.global __stack
	.global	__STACK_SIZE

	//.retain
	//.retainrefs

       .text
       .arm
       //.retain
       //.retainrefs



_self_reset_start:
    // switch to sys mode
    mrs     r0, cpsr
    bic     r0, r0, #0x1F  // CLEAR MODES
    orr     r0, r0, #0x1F  // SET SYSTEM MODE
    msr     cpsr_cf, r0

    // load the stack pointer
    ldr     sp, _stack_addr
    ldr     r0, _stack_size
    add     sp, sp, r0
    nop
    nop
    blx dm_r5_self_reset

_stack_addr:
	.word __stack
_stack_size:
	.word __STACK_SIZE

