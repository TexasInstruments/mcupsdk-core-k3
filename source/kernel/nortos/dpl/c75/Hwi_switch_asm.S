;
;  Copyright (c) 2021-2023, Texas Instruments Incorporated
;  All rights reserved.
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;  *  Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;
;  *  Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;
;  *  Neither the name of Texas Instruments Incorporated nor the names of
;     its contributors may be used to endorse or promote products derived
;     from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
;  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
;  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
;  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
; ======== Hwi_asm_switch.s71 ========
;
;

        .cdecls C,NOLIST,"HwiP_c75.h"

    .if $isdefed("__TI_ELFABI__")
    .if __TI_ELFABI__
        .asg ti_sysbios_family_xxx_Hwi_switchAndRunFunc, _ti_sysbios_family_xxx_Hwi_switchAndRunFunc
        .asg Hwi_switchAndDispatch, _Hwi_switchAndDispatch
        .asg Hwi_Module_state, Hwi_Module_state
        .asg Hwi_dispatchCore, _Hwi_dispatchCore
    .endif
    .endif

        .global ti_sysbios_family_xxx_Hwi_switchAndRunFunc
        .global Hwi_switchAndDispatch

        .global Hwi_dispatchCore
        .global Hwi_refreshNLC

Hwi_Module_state .tag Hwi_Module_State

        .text

        .asg	d15, SP

;
;  ======== ti_sysbios_family_xxx_Hwi_switchAndRunFunc ========
;  Hwi_switchAndRunFunc(Void (*func)());
;
;  Switch to ISR stack, run func() and then switch back to Task
;  stack.
;
;
        .sect ".text:ti_sysbios_family_xxx_Hwi_switchAndRunFunc"
        .clink
ti_sysbios_family_xxx_Hwi_switchAndRunFunc:
;        .asmfunc

        addkpc.d1  $PCR_OFFSET(Hwi_Module_state), a0
        ldd.d1     *a0(Hwi_Module_State.taskSP), a1
        ldd.d1     *a0(Hwi_Module_State.isrStack), a2
  [!a1] std.d1     SP, *a0(Hwi_Module_State.taskSP)
  [!a1] mv.d1      a2, SP                     ; set SP to isrStack
        std.d1     a8, *SP++[-2]              ; save SOE reg a8
||      mvc.s1     rp, a8
        std.d1     a1, *SP[3]                 ; save old taskSP on stack

        calla.s1   a4                         ; call func()

func_return:
        ldd.d1     *SP[3], a1                 ; get old taskSP
        addkpc.d1  $PCR_OFFSET(Hwi_Module_state), a0
        mvc.s1     a8, rp
        ldd.d1     *SP[2], a8                 ; restore SOE reg a8
        addd.d1    SP, 2*8, SP
  [!a1] ldd.d1     *a0(Hwi_Module_State.taskSP), a3
  [!a1] std.d1     a1, *a0(Hwi_Module_State.taskSP)
  [!a1] mv.d1      a3, SP                     ; set SP to taskSP

        ret.b1

;        .endasmfunc

;
;  ======== Hwi_switchAndDispatch ========
;
        .sect ".text:Hwi_switchAndDispatch"
        .clink
Hwi_switchAndDispatch
;        .asmfunc

; We could combine the code for switchAndRunFunc and switchAndDispatch,
; by using a4 as a switch - switchAndRunFunc will have non-zero a4 and
; switchAndDispatch could set a4 to zero before branching to common code.
; If a4 is 0 call dispatchCore, else call a4

        addkpc.d1  $PCR_OFFSET(Hwi_Module_state), a0
        ldd.d1     *a0(Hwi_Module_State.taskSP), a1
        ldd.d1     *a0(Hwi_Module_State.isrStack), a2
        addkpc.d1  $PCR_OFFSET(Hwi_dispatchCore), a3
  [!a1] std.d1     SP, *a0(Hwi_Module_State.taskSP)
  [!a1] mv.d1      a2, SP                     ; set SP to isrStack
        std.d1     a8, *SP++[-2]              ; save SOE reg a8
||      mvc.s1     rp, a8
        std.d1     a1, *SP[3]                 ; save old taskSP on stack

        calla.s1   a3

dispatch_return:
        ldd.d1     *SP[3], a1                 ; get old taskSP
        addkpc.d1  $PCR_OFFSET(Hwi_Module_state), a0
        mvc.s1     a8, rp
        ldd.d1     *SP[2], a8                 ; restore SOE reg a8
        addd.d1    SP, 2*8, SP
  [!a1] ldd.d1     *a0(Hwi_Module_State.taskSP), a3
  [!a1] std.d1     a1, *a0(Hwi_Module_State.taskSP)
  [!a1] mv.d1      a3, SP                     ; set SP to taskSP

        ret.b1

;        .endasmfunc

;
;  ======== Hwi_refreshNLC ========
; void Hwi_refreshNLC( void );
;
    .sect ".text:Hwi_refreshNLC"
    .clink
Hwi_refreshNLC:
        MVKU32 .L1  0x1, A0
        NLCINIT .S1 A0, 0x1, 0
||      RET .B1
