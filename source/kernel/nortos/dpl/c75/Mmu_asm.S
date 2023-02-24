;
;  Copyright (c) 2019-2021, Texas Instruments Incorporated
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
; ======== Mmu_asm.s71 ========
;
;

        .global Mmu_init
        .sect ".text:Mmu_init"
        .clink
Mmu_init
;        .asmfunc

        mv.l1    a5, a0
  [!a0] mvc.s1   a4, TBR0
  [ a0] mvc.s1   a4, TBR0
||      ret.b1

;        .endasmfunc

        .global MmuP_isEnabled
        .sect ".text:MmuP_isEnabled"
        .clink
MmuP_isEnabled
;        .asmfunc

        mvc.s1   SCR, a4
        nop
        andd.l1  a4, 0x1, a4
||      ret.b1

;        .endasmfunc

        .global MmuP_setTCR
        .sect ".text:MmuP_setTCR"
        .clink
MmuP_setTCR
;        .asmfunc

        mv.l1    a5, a0
  [!a0] mvc.s1   a4, TCR0
  [ a0] mvc.s1   a4, TCR0
||      ret.b1

;        .endasmfunc

        .global  CacheP_setL1DWBINV

        .global MmuP_tlbInvAll
        .sect ".text:MmuP_tlbInvAll"
        .clink
MmuP_tlbInvAll
;        .asmfunc

        ;
        ; Don't write to the stack (or memory in general) before the
        ; cache WBINV operations.  This is because the MMU is typically
        ; disabled when this function is called and memory writes bypass
        ; the cache, and the WBINV might then overwrite that write.
        ;

        mvk64.l1  1, a5
        mvc.s1   a5, L1DWBINV

        mvc.s1   a4, TLB_INV
||      ret.b1

;        .endasmfunc

        .global MmuP_setMAIRAsm
        .sect ".text:MmuP_setMAIRAsm"
        .clink
MmuP_setMAIRAsm
;        .asmfunc

        shld.l1  a4, 3, a4
        shld.l1  a5, a4, a5
        mvk64.l1 0xff, a6
        mvc.s1   MAR, a7
        shld.l1  a6, a4, a6
        andnd.l1 a6, a7, a4
        ord.l1   a4, a5, a4
        mvc.s1   a4, MAR
        mvc.s1   a4, MAR
||      ret.b1

;        .endasmfunc
