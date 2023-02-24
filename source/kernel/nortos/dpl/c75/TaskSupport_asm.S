;
;  Copyright (c) 2016-2021, Texas Instruments Incorporated
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
; ======== TaskSupport_asm.s71 ========
;
;

        .asg    D15, SP

;
; 8-byte stack alignment needs to be maintained.
; Given the architecture of Task_start below, SWREGS must be an
; even number to maintain 8-byte alignment.
;
SWREGS  .set    10                      ; number of regs saved in _Task_switch

    .if $isdefed("__TI_ELFABI__")
    .if __TI_ELFABI__
        .asg TaskSupport_buildTaskStack, _TaskSupport_buildTaskStack
        .asg TaskSupport_glue, _TaskSupport_glue
        .asg TaskSupport_glueUnpriv, _TaskSupport_glueUnpriv
        .asg TaskSupport_swap, _TaskSupport_swap
    .endif
    .endif

        .global TaskSupport_buildTaskStack
        .global TaskSupport_glue
        .global TaskSupport_glueUnpriv
        .global TaskSupport_swap
        .global Task_exit
        .global OS_mpeEnabled


;
;
;  Here is a pseudo image of the initial C7x task stack:
;
;   saved-by-callee registers
;   Task enter()
;   Task glue()
;   arg0
;   arg1
;   User's task func()
;   Task_exit()
;
;  The initial stack consists of the registers that are preserved by a
;  called C function as defined by the C compiler. These are the registers
;  pushed and popped by TaskSupport_swap.
;
;  Below (or above, depending on your view of the stack) those registers
;  are the Task enter() function which sets up the first invocation of the
;  task in the same manner as if it had been "returned" to from Task_restore()
;  which is the normal path back to an unblocked task.
;
;  Below the Task enter() function address on the initial task stack is the
;  address of the Glue function. This address is popped by the return from
;  Task enter(). Glue pops the 2 Args below it on the stack into the
;  appropriate registers for a fxn(arg0, arg1) call, and then "returns"
;  into the user's task function, which is the next to last address on
;  the stack.
;
;  Below the Task's function address on the stack is the Task_exit()
;  function address which is returned into if the task function falls
;  out the bottom.
;
;  The TaskSupport_swap() function pushes all the saved-by-callee
;  registers onto the task stack, then saves the updated SP into
;  the "old" task object's context (SP) address passed to it. Then it
;  loads the "new" task object's context (SP) (the second arg passed
;  to swap) into the SP, unrolls the saved registers and returns into
;  the new task.
;
;  The pointer returned by the buildTaskStack function is the task's initial
;  stack pointer. This address is stored into the task object's context
;  field and is passed to the TaskSupport_swap() function later.
;

;
;  ======== TaskSupport_buildTaskStack ========
;
;  TaskSupport_buildTaskStack(stack, fxn, argv, exit, entry, TCSP, privileged)
;
;
;

;
;    sp = TaskSupport_buildTaskStack((Ptr)((size_t)params->stack + params->stackSize-8), params->fxn, params->exit, params->enter, params->arg0, params->arg1);
;
        .sect ".text:TaskSupport_buildTaskStack"
        .clink

STACK   .set    a4                      ; 1st argument
FXN     .set    a5                      ; 2nd argument
EXIT    .set    a6                      ; 3rd argument
ENTRY   .set    a7                      ; 4th argument
ARG0    .set    a8                      ; 5th argument
ARG1    .set    a9                      ; 6th argument
TCSP    .set    a10                     ; 7th argument
PRIV    .set    a11                     ; 8th argument
RETVAL  .set    a4                      ; return value

;
; dword offsets - never use 1 since 16 bytes need to remain free @SP
;
Task_GLUEFRAMESIZE      .set    4
Task_GLUEEXIT           .set    5        ; OK for c7x, 16-byte space @SP
Task_GLUEFXN            .set    4
Task_GLUEARGV1          .set    3
Task_GLUEARGV0          .set    2

Task_SWITCHFRAMESIZE    .set    14
Task_SWITCHRET          .set    15        ; OK for c7x, 16-byte space @SP
Task_SWITCHRP           .set    14
Task_SWITCHTSR          .set    13
Task_SWITCHTCSP         .set    12
Task_SWITCHB15          .set    11
Task_SWITCHB14          .set    10
Task_SWITCHA15          .set    9
Task_SWITCHA14          .set    8
Task_SWITCHA13          .set    7
Task_SWITCHA12          .set    6
Task_SWITCHA11          .set    5
Task_SWITCHA10          .set    4
Task_SWITCHA9           .set    3
Task_SWITCHA8           .set    2


TaskSupport_buildTaskStack:
;        .asmfunc

        ; allocate frame for glue
        addd.d1    STACK, -Task_GLUEFRAMESIZE*8, STACK

        ; the following four values are used by glue
        std.d1     EXIT, *STACK[Task_GLUEEXIT]        ; exit addr (Task_exit)
        std.d1     FXN,  *STACK[Task_GLUEFXN]         ; fxn addr
        std.d1     ARG1, *STACK[Task_GLUEARGV1]       ; argv[1]
        std.d1     ARG0, *STACK[Task_GLUEARGV0]       ; argv[0]

        ; allocate frame for swap
        addd.d1    STACK, -Task_SWITCHFRAMESIZE*8, STACK

        addkpc.d1  $PCR_OFFSET(OS_mpeEnabled), a0
        lduh.d1    *a0, a0
  [ a0] mv.d1      PRIV, a0                      ; if mpeEnabled, use priv flag
||[!a0] mvku32.l1  1, a0                         ; if !mpeEnabled, use glue fxn
  [ a0] addkpc.d1  $PCR_OFFSET(TaskSupport_glue), a3
  [!a0] addkpc.d1  $PCR_OFFSET(TaskSupport_glueUnpriv), a3

        std.d1     ENTRY, *STACK[Task_SWITCHRET]      ; entry addr (Task_enter)
        std.d1     a3,    *STACK[Task_SWITCHRP]       ; glue addr

        ; start 0-init @SP[2]
        addd.d1    STACK, 2*8, a0

        ; these 10 values (0) represent A8-A15/B14-B15 in the swap fxn
        mvku32.l1  0, a1
        mvku32.l1  SWREGS, a2                      ; loop executes a2 iters
loop:
        std.d1     a1, *a0++[1]                    ; push 0
        addd.d1    a2, -1, a2                      ; decr. loop counter
  [ a2] b.b1       loop

        mvc.s1     tsr, a2
        std.d1     TCSP, *a0++[1]
        std.d1     a2, *a0

        ret.b1                                     ; return stack pointer

;        .endasmfunc



;       .sect ".bios"

;
;  ======== TaskSupport_swap ========
;
;  TaskSupport_swap(oldSP, newSP)
;
    .sect ".text:TaskSupport_swap"
    .clink
TaskSupport_swap:
;        .asmfunc

        mvc.s1     rp, a1
        std.d1     a1, *SP++(-Task_SWITCHFRAMESIZE*8)

        mvc.s1     tcsp, a3
        mvc.s1     tsr, a2

; research if we should do automatically for task (would save user from a
; difficult debug situation). problem could happen if last valid se read from
; valid memory ends up spilling into invalid memory.
; flush out any pending cache operations (that use SE)
;;if SE is open in TSR
;;	vmv.l2     *se0|1

        mv.d1      SP, a0
        std.d1     SP, *a4

        ; must load new SP after storing old SP, to support a "self-yield"
        ldd.d1     *a5, SP
        std.d1     a8, *a0[Task_SWITCHA8]
        std.d1     a9, *a0[Task_SWITCHA9]
        std.d1     a10, *a0[Task_SWITCHA10]
        std.d1     a11, *a0[Task_SWITCHA11]
        std.d1     a12, *a0[Task_SWITCHA12]
        std.d1     a13, *a0[Task_SWITCHA13]
        std.d1     a14, *a0[Task_SWITCHA14]
        std.d1     a15, *a0[Task_SWITCHA15]
        std.d1x    b14, *a0[Task_SWITCHB14]
        std.d1x    b15, *a0[Task_SWITCHB15]
        std.d1     a1, *a0[Task_SWITCHRET]
        std.d1     a3, *a0[Task_SWITCHTCSP]
        std.d1     a2, *a0[Task_SWITCHTSR]

;
; For the first task switch, we will return to Task_enter.
; The first thing Task_enter will do is to save the return address (RP) on the
; stack. We want Task_enter to return to glue. This is accomplished by using
; a4 for this "return", and loading the address of glue into RP.
;

        ;
        ; SP is now the new SP
        ;
        ldd.d1    *SP[Task_SWITCHTSR], a2
        ldd.d1    *SP[Task_SWITCHTCSP], a3
        ldd.d1    *SP[Task_SWITCHRET], a4       ; 1st switch, a4 = Task_enter
        ldd.d1    *SP[Task_SWITCHRP], a0        ; load RP with glue
        ldd.d1    *SP[Task_SWITCHA8], a8
        ldd.d1    *SP[Task_SWITCHA9], a9
        ldd.d1    *SP[Task_SWITCHA10], a10
        ldd.d1    *SP[Task_SWITCHA11], a11
        ldd.d1    *SP[Task_SWITCHA12], a12
        ldd.d1    *SP[Task_SWITCHA13], a13
        ldd.d1    *SP[Task_SWITCHA14], a14
        ldd.d1    *SP[Task_SWITCHA15], a15
        ldd.d1    *SP[Task_SWITCHB14], b14
        ldd.d1    *SP[Task_SWITCHB15], b15

        addd.d1   SP, Task_SWITCHFRAMESIZE*8, SP

        mvc.s1    a0, rp
        mvc.s1    a3, tcsp

        andw.m1   a2, 0x8, a0
  [!a0] b.b1      thread_mode    ; branch to exit if in thread mode

        ehdl                     ; enable handler mode
        ba.s1     a4

thread_mode:
        dhdl                     ; enable thread mode
        ba.s1     a4

;        .endasmfunc


;
;  ======== TaskSupport_glue ========
;
;  This glue function is executed immediately before the executing "fxn"
;  passed to Task_start.  This function loads the parameters to "fxn" into
;  registers - necessary for the C71 register passing model.
;
        .sect ".text:TaskSupport_glue"
        .clink

TaskSupport_glue:
;        .asmfunc

; We must maintain 8-byte stack alignment, so do a one-time even-word
; adjustment after loading registers from the stack frame.
        ldd.d1     *SP[Task_GLUEEXIT], a0          ; start address of Task_exit
        ldd.d1     *SP[Task_GLUEFXN], a1           ; start address of new task
        ldd.d1     *SP[Task_GLUEARGV1], a5         ; arg 1
        ldd.d1     *SP[Task_GLUEARGV0], a4         ; arg 0
        addd.d1    SP, Task_GLUEFRAMESIZE*8, SP
        mvc.s1     a0, rp

; The first thing the new task will do is to save the return address (RP) on
; the stack. We want the task to return to Task_exit. This is accomplished by
; using a1 for this return, and loading the address of Task_exit into RP.

        nop
        ba.s1      a1                      ; "return" to new task

;       .endasmfunc

;
;  ======== TaskSupport_glueUnpriv ========
;
;  This glue function is executed immediately before the executing "fxn"
;  passed to Task_start.  This function loads the parameters to "fxn" into
;  registers - necessary for the C71 register passing model.
;
        .sect ".text:TaskSupport_glueUnpriv"
        .clink

TaskSupport_glueUnpriv:
;        .asmfunc

        ;
        ; syscallHandler uses a8 to validate calling fxn.
        ; Would normally save/restore it but doesn't apply here.
        ;
        addkpc.d1  $PCR_OFFSET(TaskSupport_glueUnpriv), a8
        syscall.b1 1                               ; enter unpriv mode

syscall_ret:

; We must maintain 8-byte stack alignment, so do a one-time even-word
; adjustment after loading registers from the stack frame.

        ldd.d1     *SP[Task_GLUEFXN], a1           ; start address of new task
        ldd.d1     *SP[Task_GLUEARGV1], a5         ; arg 1
        ldd.d1     *SP[Task_GLUEARGV0], a4         ; arg 0
        addd.d1    SP, Task_GLUEFRAMESIZE*8, SP

        calla.s1   a1                              ; call user task

        ;
        ; syscallHandler uses a8 to validate calling fxn which should
        ; still be valid from above (just needs to be somewhere in this fxn).
        ;
        syscall.b1 0                               ; enter priv mode

        b.b1       Task_exit

;        .endasmfunc
