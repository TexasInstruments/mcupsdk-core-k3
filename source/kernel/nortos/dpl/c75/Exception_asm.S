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
;  ======== Exception_asm.s71 ========
;
;


        .cdecls C,NOLIST,"Exception_c75.h"

        .text

    .if $isdefed("__TI_ELFABI__")
    .if __TI_ELFABI__
        .asg Exception_Module_state, _Exception_Module_state
        .asg Exception_handler, _Exception_handler
        .asg Exception_dispatch, _Exception_dispatch
    .endif
    .endif

        .global Exception_Module_state
        .global Exception_handler
        .global Exception_dispatch

SP      .set    d15

Exception_Module_state .tag Exception_Module_State

Exception_dispatch:
;        .asmfunc

        ;
        ; a0 holds SP (d15) value at time of exception.
        ; a1 holds vector type to pass to Exception_handler().
        ; a0/a1 already saved in vector code with:
        ;   std.d1    a0, *SP++[-1]
        ;   std.d1    a1, *SP++[-1]
        ;
        std.d1    a2, *SP
        addkpc.d1 $PCR_OFFSET(Exception_Module_state), a2
        ldd.d1    *a2(Exception_Module_State.excPtr), SP
        ldd.d1    *a0, a2                ; saved a0 from vector
        std.d1    a2, *SP++[-1]
        ldd.d1    *a0[-1], a2            ; saved a1 from vector
        std.d1    a2, *SP++[-1]
        ldd.d1    *a0[-2], a2            ; saved a2 from above
        std.d1    a2, *SP++[-1]

        std.d1    a3, *SP++[-1]
        std.d1    a4, *SP++[-1]
        std.d1    a5, *SP++[-1]
        mv.d1     a1, a5                 ; put vector type in param #2 reg
        std.d1    a6, *SP++[-1]
        std.d1    a7, *SP++[-1]
        std.d1    a8, *SP++[-1]
        std.d1    a9, *SP++[-1]
        std.d1    a10, *SP++[-1]
        std.d1    a11, *SP++[-1]
        std.d1    a12, *SP++[-1]
        std.d1    a13, *SP++[-1]
        std.d1    a14, *SP++[-1]
        std.d1    a15, *SP++[-1]

        std.d1    d0, *SP++[-1]
        std.d1    d1, *SP++[-1]
        std.d1    d2, *SP++[-1]
        std.d1    d3, *SP++[-1]
        std.d1    d4, *SP++[-1]
        std.d1    d5, *SP++[-1]
        std.d1    d6, *SP++[-1]
        std.d1    d7, *SP++[-1]
        std.d1    d8, *SP++[-1]
        std.d1    d9, *SP++[-1]
        std.d1    d10, *SP++[-1]
        std.d1    d11, *SP++[-1]
        std.d1    d12, *SP++[-1]
        std.d1    d13, *SP++[-1]
        std.d1    d14, *SP++[-1]
        ; vector code placed d15 (SP) in a0
        std.d1    a0, *SP++[-1]

||      mv.m1     am0, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am1, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am2, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am3, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am4, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am5, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am6, a1
        std.d1    a1, *SP++[-1]
||      mv.m1     am7, a1
        std.d1    a1, *SP++[-1]

||      mv.l1     al0, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al1, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al2, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al3, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al4, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al5, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al6, a1
        std.d1    a1, *SP++[-1]
||      mv.l1     al7, a1
        std.d1    a1, *SP++[-8]

        vst4d.d2  vb0, *SP++[-4]
        vst4d.d2  vb1, *SP++[-4]
        vst4d.d2  vb2, *SP++[-4]
        vst4d.d2  vb3, *SP++[-4]
        vst4d.d2  vb4, *SP++[-4]
        vst4d.d2  vb5, *SP++[-4]
        vst4d.d2  vb6, *SP++[-4]
        vst4d.d2  vb7, *SP++[-4]
        vst4d.d2  vb8, *SP++[-4]
        vst4d.d2  vb9, *SP++[-4]
        vst4d.d2  vb10, *SP++[-4]
        vst4d.d2  vb11, *SP++[-4]
        vst4d.d2  vb12, *SP++[-4]
        vst4d.d2  vb13, *SP++[-4]
        vst4d.d2  vb14, *SP++[-4]
        vst4d.d2  vb15, *SP++[-4]

||      vmv.m2    vbm0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm1, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm2, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm3, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm4, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm5, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm6, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.m2    vbm7, vb0
        vst4d.d2  vb0, *SP++[-4]

||      vmv.l2    vbl0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl1, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl2, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl3, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl4, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl5, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl6, vb0
        vst4d.d2  vb0, *SP++[-4]
||      vmv.l2    vbl7, vb0
        vst4d.d2  vb0, *SP++[-4]

||      mvc.c2    cucr0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    cucr1, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    cucr2, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    cucr3, vb0
        vst4d.d2  vb0, *SP++[-4]

||      mvc.c2    sa1cntr0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa1cntr0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa2cntr0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa3cntr0, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa1cr, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa1cr, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa2cr, vb0
        vst4d.d2  vb0, *SP++[-4]
||      mvc.c2    sa3cr, vb0
        vst4d.d2  vb0, *SP++[-4]

;||      sesave.l2 3, 1, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 2, 1, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 1, 1, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 0, 1, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 3, 0, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 2, 0, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 1, 0, vb0
;        vst8d.d2  vb0, *SP++[-8]
;||      sesave.l2 0, 0, vb0
;        vst8d.d2  vb0, *SP++[-1]

        mvk64.l1 -4, a3
        shld.s1 a3, 3, a3
        addd.d2 a3, d15, a3
        sesavest.d1 *a3[0], 1

        mvk64.l1 -4, a3
        shld.s1 a3, 3, a3
        addd.d2 a3, d15, a3
        sesavest.d1 *a3[0], 0


||      mvpb.l2   p0, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p1, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p2, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p3, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p4, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p5, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p6, b0
        std.d2    b0, *SP++[-1]
||      mvpb.l2   p7, b0
        std.d2    b0, *SP++[-1]

||      mvc.s1    gply, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    gfpgfr, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    fsr, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    fpcr, a1
        std.d1    a1, *SP++[-1]

||      mvc.s1    rp, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    iesr, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    iear, a1
        std.d1    a1, *SP++[-1]
||      mvc.s1    ierr, a1
        std.d1    a1, *SP

        addkpc.d1 $PCR_OFFSET(Exception_Module_state), a3
        std.d1    SP, *a3(Exception_Module_State.excContext)

        ldd.d1    *a3(Exception_Module_State.returnHook), a1
  [!a1] mvk64.l1  0x1, a4
||[ a1] mvk64.s1  0x0, a4
        mv.d1     a1, a8                ; preserve returnHook value

        mv.d1     a0, SP                ; restore SP to value at exception
	call.b1   $PCR_OFFSET(Exception_handler)

        ;
        ; If we get here, branch to Exception_returnHook (saved in a8)
        ; We will get here only when Exception_returnHook != 0 (because of
        ; "don't call SYS_abort" parameter)
        ;

        ;
        ; Disable intrs just in case handler above enabled them (more
        ; realistically, user hook called from handler enabled them).
        ; The function registered with Exception_returnHook must restore the
        ; context saved above and do "RETE.S1 <ret_addr_reg> <TSR_reg>"
        ;
        devt.s1  a4    ; returns old TSR.GEE >> 25

        ba.s1      a8

;        .endasmfunc
