;
;  Copyright (c) 2021, Texas Instruments Incorporated
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
; ======== Clobber_asm.s71 ========
;
;

        .cdecls C,NOLIST,"Clobber.h"

    .if $isdefed("__TI_ELFABI__")
    .if __TI_ELFABI__
        .asg Clobber_trashRegs, _Clobber_trashRegs
        .asg Clobber_checkRegs, _Clobber_checkRegs
        .asg Clobber_postIntr, _Clobber_postIntr
        .asg Clobber_postIntrCheck, _Clobber_postIntrCheck
    .endif
    .endif

        .global Clobber_trashRegs
        .global Clobber_checkRegs
        .global Clobber_postIntr
        .global Clobber_postIntrCheck

        .asg    d15, SP

        .text
;
;  ======== Clobber_trashRegs ========
;  trash all scratch registers:
;  A0-A7, D0-D14, VB0-VB13,
;  AL0-AL7, AM0-AM7, VBL0-VBL7, VBM0-VBM7
;  a4 can't be trashed/checked because it's being used and the compiler is
;  going to save it before calling postInt, and rp can't be tested because
;  it's the return register.
;  Instead, a4 and rp are trashed and checked inside postInt.
;
    .sect ".text:Clobber_trashRegs"
    .clink
Clobber_trashRegs:
;        .asmfunc

        mv.d1      a4, a0
        addd.d1    a0, 1, a1
        addd.d1    a1, 1, a2
        addd.d1    a2, 1, a3
        addd.d1    a3, 1, a5
        addd.d1    a5, 1, a6
        addd.d1    a6, 1, a7

        addd.d1    a7, 1, d0
        addd.d1    d0, 1, d1
        addd.d1    d1, 1, d2
        addd.d1    d2, 1, d3
        addd.d1    d3, 1, d4
        addd.d1    d4, 1, d5
        addd.d1    d5, 1, d6
        addd.d1    d6, 1, d7
        addd.d1    d7, 1, d8
        addd.d1    d8, 1, d9
        addd.d1    d9, 1, d10
        addd.d1    d10, 1, d11
        addd.d1    d11, 1, d12
        addd.d1    d12, 1, d13
        addd.d1    d13, 1, d14

        addd.d1    d14, 1, al0
        addd.s1    al0, 1, al1
        addd.s1    al1, 1, al2
        addd.s1    al2, 1, al3
        addd.s1    al3, 1, al4
        addd.s1    al4, 1, al5
        addd.s1    al5, 1, al6
        addd.s1    al6, 1, al7

        addd.s1    al7, 1, am0
        addd.m1    am0, 1, am1
        addd.m1    am1, 1, am2
        addd.m1    am2, 1, am3
        addd.m1    am3, 1, am4
        addd.m1    am4, 1, am5
        addd.m1    am5, 1, am6
        addd.m1    am6, 1, am7

        mv.m1      am7, a0
        mv.l2x     a0, b0

        vdupd.s2   b0, vb0
        vaddd.s2   vb0, 1, vb0
        vaddd.s2   vb0, 1, vb1
        vaddd.s2   vb1, 1, vb2
        vaddd.s2   vb2, 1, vb3
        vaddd.s2   vb3, 1, vb4
        vaddd.s2   vb4, 1, vb5
        vaddd.s2   vb5, 1, vb6
        vaddd.s2   vb6, 1, vb7
        vaddd.s2   vb7, 1, vb8
        vaddd.s2   vb8, 1, vb9
        vaddd.s2   vb9, 1, vb10
        vaddd.s2   vb10, 1, vb11
        vaddd.s2   vb11, 1, vb12
        vaddd.s2   vb12, 1, vb13
        vaddd.s2   vb13, 1, vb14
        vaddd.s2   vb14, 1, vb15

        vaddd.s2   vb15, 1, vbl0
        vaddd.s2   vbl0, 1, vbl1
        vaddd.s2   vbl1, 1, vbl2
        vaddd.s2   vbl2, 1, vbl3
        vaddd.s2   vbl3, 1, vbl4
        vaddd.s2   vbl4, 1, vbl5
        vaddd.s2   vbl5, 1, vbl6
        vaddd.s2   vbl6, 1, vbl7

        vaddd.s2   vbl7, 1, vbm0
        vaddd.m2   vbm0, 1, vbm1
        vaddd.m2   vbm1, 1, vbm2
        vaddd.m2   vbm2, 1, vbm3
        vaddd.m2   vbm3, 1, vbm4
        vaddd.m2   vbm4, 1, vbm5
        vaddd.m2   vbm5, 1, vbm6
        vaddd.m2   vbm6, 1, vbm7

        ret.b1

;        .endasmfunc




;
;  ======== Clobber_checkRegs ========
;
;
    .sect ".text:Clobber_checkRegs"
    .clink
Clobber_checkRegs:
;        .asmfunc

  .if 1

        std.d1     a8, *SP++[-10]
        vst4d.d2   vb14, *SP(2*4)
        mv.d1      a1, a8
        vmv.m2     vb0, vb14

        cmpeqd.l1  a4, a0, a1
  [!a1] addd.d1    a1, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a8, a1    ; checking a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a3, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a5, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a6, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, a7, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d0, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d1, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d2, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d3, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d4, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d5, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d6, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d7, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d8, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d9, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d10, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d11, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d12, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d13, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.d1      d14, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al0, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al1, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al3, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al4, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al5, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al6, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        cmpeqd.l1  a4, al7, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am0, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am1, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am2, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am3, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am4, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am5, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am6, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.m1      am7, a2
        cmpeqd.l1  a4, a2, a1
  [!a1] addd.d1    a0, 1, a0
        addd.d1    a4, 1, a4

        mv.l2x     a4, b0
        vdupd.s2   b0, vb0

        vcmpeqd.l2 vb0, vb14, p0    ; checking vb0
;;        mvpd.l1      p0, a1
;;        cmpeqd.l2  p0, -1, b1
;;  [!p0] addd.d1    a0, 1, a0
        vaddd.s2   vb0, 1, vb0

        vld4d.d1   *SP(2*4), vb14
        ldd.d1     *SP[10], a8
||      addd.d2    SP, 2*10, SP
        mv.l1      a0, a4
        ret.b1

  .else
    stw     b10, *b15--[2]   ; Use b10 as the counter
    zero        b10

    stw     b11, *b15--[2]   ; Need a1 for conditional expressions.
    mv      a1, b11          ; Copy a1 to b11 so a1 can be used.


    cmpeq       a4, a0, a1
  [!a1]         add     1, b10, b10
        add     a4, 1, a4

    cmpeq       a4, b11, a1   ; Compare a1
  [!a1] add     1, b10, b10
        add     a4, 1, a4

    cmpeq       a4, a2, a1
  [!a1] add     1, b10, b10
        add     a4,1,a4

        cmpeq   a4,a3,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a5,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a6,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a7,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a8,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a9,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a16,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a17,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a18,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a19,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a20,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a21,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a22,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a23,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a24,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a25,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a26,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a27,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a28,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a29,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a30,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,a31,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b0,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b1,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b2,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b4,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b5,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b6,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b7,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b8,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b9,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4,b16,a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b17, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b18, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b19, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b20, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b21, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b22, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b23, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b24, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b25, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b26, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b27, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b28, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b29, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b30, a1
  [!a1] add     1,b10,b10
        add     a4,1,a4

        cmpeq   a4, b31, a1
  [!a1] add     1,b10,b10

        mv      b10, a4     ; Return the number of incorrect regs.

        ldw     *++b15[2], b11  ; Restore preserved reg b11.
        ldw     *++b15[2], b10  ; Restore preserved reg b10.

        b       b3
        nop     5
  .endif

;        .endasmFunc

;
;  ======== Clobber_postIntr ========
;
;
    .sect ".text:Clobber_postIntr"
    .clink
Clobber_postIntr:
;       .asmfunc

  .if 1
  .else
        stw     b10, *b15--[4]
        stw     b11, *+b15[1]
        stw     b12, *+b15[2]
        stw     b13, *+b15[3]


        mvk     0x1, b10
        mv  a4, b12
        shl     b10, b12, b11

        mv b3, b12      ; Backup return address

        mvkl   0x89ABCDEF, a4       ; Trash b3 and a4
        mvkh   0x89ABCDEF, a4

        mvkl   0xFEDCBA98, b3
        mvkh   0xFEDCBA98, b3

        mvc     b11, ISR

        nop 9   ; Give interrupt plenty of time to be taken

        mv b0, b11  ; backup b0

        mvkl   0x89ABCDEF, b13
        mvkh   0x89ABCDEF, b13

        cmpeq a4, b13, b0
  [!b0] mvk 1, a4
  [ b0] mvk 0, a4

        mvkl   0xFEDCBA98, b13
        mvkh   0xFEDCBA98, b13

        cmpeq b3, b13, b0
  [!b0] addk 1, a4

        mvkl   _Clobber_postIntrCheck, b10
        mvkh   _Clobber_postIntrCheck, b10
        stw    a4, *b10

        mv b11, b0

        ldw     *+b15[3], b13
        ldw     *+b15[1], b11

        b       b12
||      ldw     *+b15[2], b12
        ldw     *++b15[4], b10
        nop     4

  .endif

;        .endasmfunc
