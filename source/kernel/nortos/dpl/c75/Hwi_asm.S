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
; ======== Hwi_asm.s71 ========
;
;

        .global Hwi_switchToNS
        .global _c_int00

        .sect ".text:Hwi_switchToNS"
        .clink
Hwi_switchToNS:
;        .asmfunc
        MVK32 .L1 0, A0
        MVC   .S1 A0, EASGR

        MVK64 .L1 0x7c295b00, a0 ; CLEC register for event 346
        ldw   .d1 *a0, a1
        andw  .m1 a1, a2, a1
        stw   .d1 a1, *a0        ; turn off Secure Claim bit

        MVC   .S1 TSR, A2
        MVK64 .L1 0xfffffffffffffff8, A1
        ANDD  .S1 A2 , A1, A2
        MVK64 .L1 0x3, A1
        ORD   .S1 A2 , A1, A2   ; set the lower 3 bits of the TSR to 011 (root supervisor)

        .global MmuP_tlbInvAll
        mvk64.l1 0, a4
        call.b1 $PCR_OFFSET(MmuP_tlbInvAll)

        MVK64 .L1 _c_int00, A1 ; set the destination of the RETE to the non-secure entry point
        RETE  .S1 A1 , A2      ; switch to NS root supervisor mode

;	.endasmfunc

        .global Hwi_disable

        .sect ".text:Hwi_disable"
        .clink
Hwi_disable:
;        .asmfunc

        devt.s1  a4    ; returns old TSR.GEE >> 25
||      ret.b1

;	.endasmfunc

        .global Hwi_enable

        .sect ".text:Hwi_enable"
        .clink
Hwi_enable:
;        .asmfunc

        mvc.s1   TSR, a5
||      mvk32.l1 1, a4
        revt.s1  a4
||      shruw.l1 a5, 25, a6
        andw.m1  a6, 1, a4    ; return old TSR.GEE >> 25
||      ret.b1

;	.endasmfunc

        .global Hwi_restore

        .sect ".text:Hwi_restore"
        .clink
Hwi_restore:
;        .asmfunc

        revt.s1 a4
||      ret.b1

;	.endasmfunc

        .global Hwi_setCOP

        .sect ".text:Hwi_setCOP"
        .clink
Hwi_setCOP:
;        .asmfunc

        setcop.s1  a4
||      ret.b1

;	.endasmfunc

        .global Hwi_getCXM

        .sect ".text:Hwi_getCXM"
        .clink
Hwi_getCXM:
;        .asmfunc

        mvc.s1   TSR, a5
        andd.l1  a5, 0x7, a4
||      ret.b1

;	.endasmfunc

;
; ======== Hwi_plug ========
;! Plug an interrupt vector with an ISR address.
;!       a4 <- intNum
;!       b4 <- isr
;
        .sect ".text:Hwi_plug"
        .clink
Hwi_plug:
;        .asmfunc
  .if 1
        ret.b1
  .else
        stw     b3, *b15--[2]
        mvk     1, a2

        mvc     ier, b8         ; disable the interrupt currently being
        shl     a2, a4, a2      ; plugged but leave global interrupts enabled.

        xor     -1, a2, b5
||      stw     b8, *b15[1]
        and     b8, b5, b5
        mvc     b5, ier

        ; FORM DESTINATION ADDRESS OF ACTUAL FETCH PACKET
        .if ($isdefed("ti_sysbios_BIOS_useSK__D"))

        ;
        ; if useSK is defined then do not read ISTP,
        ; use the label for Hwi_int0 instead.
        ;
        .global Hwi_int0
        mvkl    Hwi_int0, b5
        mvkh    Hwi_int0, b5

        .else
        mvc     istp, b5        ; interrupt vector table pointer

        .endif

        mvkl    ISTPMASK, b0
        mvkh    ISTPMASK, b0
        and     b0, b5, b5      ; mask to get ISTP
        shl     a4, 5, b7       ; intNum << 5 (table increments of 0x20)
        add     b5, b7, b5      ; b5 = interrupt fetch packet start address
        mv      b5, a2          ; use ISTP as direct destination

        ; replace existing "mvkl isr, b0" instruction
        clr     b4, 16, 31, b1      ; keep 16 lsb
        shl     b1, 7, b1
        mvkl    MVK_OP, b0
        mvkh    MVK_OP, b0
        or      b0, b1, b0
        stw     b0,*a2[3]

        ; replace existing "mvkh isr, b0" instruction
        clr     b4, 0, 15, b1       ; keep 16 msb
        shru    b1, 9, b1
        mvkl    MVKH_OP, b0
        mvkh    MVKH_OP, b0
        or      b0, b1, b0
        stw     b0,*a2[4]

        flushCache b5     ; flush L1D cache, invalidate L1P, wait for completion

        ldw     *b15[1], b8
        ldw     *++b15[2], b3
        mvc     ier, b0
        nop     2
        or      b0, b8, b8      ; restore original mask OR'd with current ier.
        mvc     b8, ier

        b b3                    ; return to caller
        nop 5

  .endif
;        .endasmfunc
