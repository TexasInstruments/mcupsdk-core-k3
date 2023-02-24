;
;  Copyright (c) 2017-2021, Texas Instruments Incorporated
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
;  ======== Hwi_disp_always.s71 ========
;
;
        .if $isdefed("__TI_ASSEMBLER_VERSION__")
        .if __TI_ASSEMBLER_VERSION__ < 1003000
            .emsg "Compiler version must be 1.3.0 STS or higher"
        .endif
        .endif

        .cdecls C,NOLIST,"HwiP_c75.h"
;


VECTOR_WIDTH  .set     4
SEVECTOR_WIDTH .set    8
SAVECTOR_WIDTH .set    8


;
; The following are double word offsets (offset must be < 32 for A-reg access)
;
Hwi_SFA0        .set    1
Hwi_SFA1        .set    2
Hwi_SFA2        .set    3
Hwi_SFA3        .set    4
Hwi_SFA4        .set    5
Hwi_SFA5        .set    6
Hwi_SFA6        .set    7
Hwi_SFA7        .set    8
Hwi_SFA8        .set    9
Hwi_SFA9        .set    10
Hwi_SFA10       .set    11
Hwi_SFA11       .set    12
Hwi_SFA12       .set    13
Hwi_SFA13       .set    14
Hwi_SFA14       .set    15
Hwi_SFA15       .set    16
Hwi_SFAL0       .set    17
Hwi_SFAL1       .set    18
Hwi_SFAL2       .set    19
Hwi_SFAL3       .set    20
Hwi_SFAL4       .set    21
Hwi_SFAL5       .set    22
Hwi_SFAL6       .set    23
Hwi_SFAL7       .set    24
Hwi_SFAL8       .set    25
Hwi_SFAL9       .set    26
Hwi_SFAL10      .set    27
Hwi_SFAL11      .set    28
Hwi_SFAL12      .set    29
Hwi_SFAL13      .set    30
Hwi_SFAL14      .set    31
Hwi_SFAL15      .set    32
Hwi_SFAM0       .set    33
Hwi_SFAM1       .set    34
Hwi_SFAM2       .set    35
Hwi_SFAM3       .set    36
Hwi_SFAM4       .set    37
Hwi_SFAM5       .set    38
Hwi_SFAM6       .set    39
Hwi_SFAM7       .set    40
Hwi_SFAM8       .set    41
Hwi_SFAM9       .set    42
Hwi_SFAM10      .set    43
Hwi_SFAM11      .set    44
Hwi_SFAM12      .set    45
Hwi_SFAM13      .set    46
Hwi_SFAM14      .set    47
Hwi_SFAM15      .set    48
Hwi_SFD0        .set    49
Hwi_SFD1        .set    50
Hwi_SFD2        .set    51
Hwi_SFD3        .set    52
Hwi_SFD4        .set    53
Hwi_SFD5        .set    54
Hwi_SFD6        .set    55
Hwi_SFD7        .set    56
Hwi_SFD8        .set    57
Hwi_SFD9        .set    58
Hwi_SFD10       .set    59
Hwi_SFD11       .set    60
Hwi_SFD12       .set    61
Hwi_SFD13       .set    62
Hwi_SFD14       .set    63

Hwi_SFRP        .set    64
Hwi_SFFPCR      .set    65
Hwi_SFFSR       .set    66
Hwi_SFGFPGFR    .set    67
Hwi_SFGPLY      .set    68
Hwi_SFP0        .set    69
Hwi_SFP1        .set    70
Hwi_SFP2        .set    71
Hwi_SFP3        .set    72
Hwi_SFP4        .set    73
Hwi_SFP5        .set    74
Hwi_SFP6        .set    75
Hwi_SFP7        .set    76
Hwi_SFRXMR      .set    77


; offsets are in double word not in bytes
; all of these are expressed in double word, instruction takes in byte.

; 512 bit (64 byte) offsets
Hwi_SFVB0     .set    78
Hwi_SFVB1     .set    Hwi_SFVB0 + (VECTOR_WIDTH *1)
Hwi_SFVB2     .set    Hwi_SFVB0 + (VECTOR_WIDTH*2)
Hwi_SFVB3     .set    Hwi_SFVB0 + (VECTOR_WIDTH*3)
Hwi_SFVB4     .set    Hwi_SFVB0 + (VECTOR_WIDTH*4)
Hwi_SFVB5     .set    Hwi_SFVB0 + (VECTOR_WIDTH*5)
Hwi_SFVB6     .set    Hwi_SFVB0 + (VECTOR_WIDTH*6)
Hwi_SFVB7     .set    Hwi_SFVB0 + (VECTOR_WIDTH*7)
Hwi_SFVB8     .set    Hwi_SFVB0 + (VECTOR_WIDTH*8)
Hwi_SFVB9     .set    Hwi_SFVB0 + (VECTOR_WIDTH*9)
Hwi_SFVB10    .set    Hwi_SFVB0 + (VECTOR_WIDTH*10)
Hwi_SFVB11    .set    Hwi_SFVB0 + (VECTOR_WIDTH*11)
Hwi_SFVB12    .set    Hwi_SFVB0 + (VECTOR_WIDTH*12)
Hwi_SFVB13    .set    Hwi_SFVB0 + (VECTOR_WIDTH*13)
Hwi_SFVB14    .set    Hwi_SFVB0 + (VECTOR_WIDTH*14)
Hwi_SFVB15    .set    Hwi_SFVB0 + (VECTOR_WIDTH*15)
Hwi_SFVBL0    .set    Hwi_SFVB0 + (VECTOR_WIDTH*16)
Hwi_SFVBL1    .set    Hwi_SFVB0 + (VECTOR_WIDTH*17)
Hwi_SFVBL2    .set    Hwi_SFVB0 + (VECTOR_WIDTH*18)
Hwi_SFVBL3    .set    Hwi_SFVB0 + (VECTOR_WIDTH*19)
Hwi_SFVBL4    .set    Hwi_SFVB0 + (VECTOR_WIDTH*20)
Hwi_SFVBL5    .set    Hwi_SFVB0 + (VECTOR_WIDTH*21)
Hwi_SFVBL6    .set    Hwi_SFVB0 + (VECTOR_WIDTH*22)
Hwi_SFVBL7    .set    Hwi_SFVB0 + (VECTOR_WIDTH*23)
Hwi_SFVBM0    .set    Hwi_SFVB0 + (VECTOR_WIDTH*24)
Hwi_SFVBM1    .set    Hwi_SFVB0 + (VECTOR_WIDTH*25)
Hwi_SFVBM2    .set    Hwi_SFVB0 + (VECTOR_WIDTH*26)
Hwi_SFVBM3    .set    Hwi_SFVB0 + (VECTOR_WIDTH*27)
Hwi_SFVBM4    .set    Hwi_SFVB0 + (VECTOR_WIDTH*28)
Hwi_SFVBM5    .set    Hwi_SFVB0 + (VECTOR_WIDTH*29)
Hwi_SFVBM6    .set    Hwi_SFVB0 + (VECTOR_WIDTH*30)
Hwi_SFVBM7    .set    Hwi_SFVB0 + (VECTOR_WIDTH*31)
Hwi_SFCUCR0   .set    Hwi_SFVB0 + (VECTOR_WIDTH*32)
Hwi_SFCUCR1   .set    Hwi_SFVB0 + (VECTOR_WIDTH*33)
Hwi_SFCUCR2   .set    Hwi_SFVB0 + (VECTOR_WIDTH*34)
Hwi_SFCUCR3   .set    Hwi_SFVB0 + (VECTOR_WIDTH*35)
Hwi_SFCUCR4   .set    Hwi_SFVB0 + (VECTOR_WIDTH*36)
Hwi_SFCUCR5   .set    Hwi_SFVB0 + (VECTOR_WIDTH*37)
Hwi_SFCUCR6   .set    Hwi_SFVB0 + (VECTOR_WIDTH*38)
Hwi_SFCUCR7   .set    Hwi_SFVB0 + (VECTOR_WIDTH*39)

; 4 SA Registers - these are stream as well - 3 vectors 512 bits long
; Rename them to SFSA0, SFSA1, SFSA2
Hwi_SFSA0 .set  Hwi_SFVB0 + (VECTOR_WIDTH*40)
Hwi_SFSA1 .set  Hwi_SFSA0 + (SAVECTOR_WIDTH*3)
Hwi_SFSA2 .set  Hwi_SFSA1 + (SAVECTOR_WIDTH*3)
Hwi_SFSA3 .set  Hwi_SFSA2 + (SAVECTOR_WIDTH*3)

; 2 SE Registers - these are stream as well - 4 vectors 512 bits long
Hwi_SFSE0_0   .set    Hwi_SFSA3  +  (SAVECTOR_WIDTH*3)
Hwi_SFSE1_0   .set    Hwi_SFSE0_0 + (SEVECTOR_WIDTH*4)

Hwi_STACKFRAMESIZE      .set    Hwi_SFSE1_0 + (SEVECTOR_WIDTH*4)     ; 

SP              .set    d15

    .if $isdefed("__TI_ELFABI__")
    .if __TI_ELFABI__
        .asg Hwi_dispatchC, _Hwi_dispatchC
        .asg Hwi_dispatchAlways, _Hwi_dispatchAlways
        .asg Hwi_Module_state, _Hwi_Module_state
    .endif
    .endif

        .global Hwi_dispatchC
        .global Hwi_dispatchAlways
        .global SysCall_syscallHandler
    .if $isdefed("Exception_vectors__D")
        .global Exception_dispatch
    .endif

Hwi_Module_state .tag Hwi_Module_State

        .sect .vecs

        .global soft_reset

soft_reset:
        b.b1      $PCR_OFFSET(soft_reset)

        .align 0x200
int_exc:
    .if $isdefed("Exception_vectors__D")
        std.d2x   a0, *SP++[-1]
||      mv.d1     SP, a0
        std.d1    a1, *SP++[-1]
        mvk64.l1  0x0, a1
        b.b1      $PCR_OFFSET(Exception_dispatch)
    .else
        b.b1      $PCR_OFFSET(int_exc)
    .endif

        .align 0x200
page_fault:
    .if $isdefed("Exception_vectors__D")
        std.d2x   a0, *SP++[-1]
||      mv.d1     SP, a0
        std.d1    a1, *SP++[-1]
        mvk64.l1  0x1, a1
        b.b1      $PCR_OFFSET(Exception_dispatch)
    .else
        b.b1      $PCR_OFFSET(page_fault)
    .endif

        .align 0x200
nme:
        b.b1      $PCR_OFFSET(nme)

        .align 0x200
evt:
        b.b1      $PCR_OFFSET(Hwi_dispatchAlways)

    .if $isdefed("SysCall_vector__D")

        .align 0x1000
scall:
        .align 0x40
        mvk64.l1  0, a0    ; used for enterPrivMode
        b.b1      $PCR_OFFSET(SysCall_syscallHandler)

        .align 0x40
        mvk64.l1  1, a0    ; used for enterUnprivMode
        b.b1      $PCR_OFFSET(SysCall_syscallHandler)

        .align 0x40
        mvk64.l1  2, a0    ; used for restorePrivMode
        b.b1      $PCR_OFFSET(SysCall_syscallHandler)

    .endif

        .sect .secure_vecs

        .global secure_soft_reset

secure_soft_reset:
        b.b1      $PCR_OFFSET(secure_soft_reset)

        .align 0x200
secure_int_exc:
    .if $isdefed("Exception_vectors__D")
        std.d2x   a0, *SP++[-1]
||      mv.d1     SP, a0
        std.d1    a1, *SP++[-1]
        mvk64.l1  0x0, a1
        b.b1      $PCR_OFFSET(Exception_dispatch)
    .else
        b.b1      $PCR_OFFSET(secure_int_exc)
    .endif

        .align 0x200
secure_page_fault:
    .if $isdefed("Exception_vectors__D")
        std.d2x   a0, *SP++[-1]
||      mv.d1     SP, a0
        std.d1    a1, *SP++[-1]
        mvk64.l1  0x1, a1
        b.b1      $PCR_OFFSET(Exception_dispatch)
    .else
        b.b1      $PCR_OFFSET(secure_page_fault)
    .endif

        .align 0x200
secure_nme:
        b.b1      $PCR_OFFSET(secure_nme)

        .align 0x200
secure_evt:
        b.b1      $PCR_OFFSET(Hwi_dispatchAlways)

        .sect ".text:Hwi_dispatchAlways"

        .clink

Hwi_dispatchAlways:
;        .asmfunc

        std.d1    a0, *ECSP[0x300]
||      std.d2x   a1, *ECSP[0x301]

        addd.d1   SP, -Hwi_STACKFRAMESIZE*8, SP     ; alloc stack frame

;;        std.d1    a0, *SP[Hwi_SFA0]    ; already saved
;;||      std.d2x   a1, *SP[Hwi_SFA1]    ; already saved
        std.d1    a2, *SP[Hwi_SFA2]
||      std.d2x   a3, *SP[Hwi_SFA3]
        std.d1    a4, *SP[Hwi_SFA4]
||      std.d2x   a5, *SP[Hwi_SFA5]
        std.d1    a6, *SP[Hwi_SFA6]
||      std.d2x   a7, *SP[Hwi_SFA7]
        std.d1    a8, *SP[Hwi_SFA8]
||      std.d2x   a9, *SP[Hwi_SFA9]
        std.d1    a10, *SP[Hwi_SFA10]
||      std.d2x   a11, *SP[Hwi_SFA11]
        std.d1    a12, *SP[Hwi_SFA12]
||      std.d2x   a13, *SP[Hwi_SFA13]
        std.d1    a14, *SP[Hwi_SFA14]
||      std.d2x   a15, *SP[Hwi_SFA15]
||      mv.l1     al0, a0
||      mv.s1     al1, a1
        std.d1    a0, *SP[Hwi_SFAL0]
||      std.d2x   a1, *SP[Hwi_SFAL1]
||      mv.l1     al2, a0
||      mv.s1     al3, a1
        std.d1    a0, *SP[Hwi_SFAL2]
||      std.d2x   a1, *SP[Hwi_SFAL3]
||      mv.l1     al4, a0
||      mv.s1     al5, a1
        std.d1    a0, *SP[Hwi_SFAL4]
||      std.d2x   a1, *SP[Hwi_SFAL5]
||      mv.l1     al6, a0
||      mv.s1     al7, a1
        std.d1    a0, *SP[Hwi_SFAL6]
||      std.d2x   a1, *SP[Hwi_SFAL7]
||      mv.l1     al8, a0
||      mv.s1     al9, a1
        std.d1    a0, *SP[Hwi_SFAL8]
||      std.d2x   a1, *SP[Hwi_SFAL9]
||      mv.l1     al10, a0
||      mv.s1     al11, a1
        std.d1    a0, *SP[Hwi_SFAL10]
||      std.d2x   a1, *SP[Hwi_SFAL11]
||      mv.l1     al12, a0
||      mv.s1     al13, a1
        std.d1    a0, *SP[Hwi_SFAL12]
||      std.d2x   a1, *SP[Hwi_SFAL13]
||      mv.l1     al14, a0
||      mv.s1     al15, a1
        std.d1    a0, *SP[Hwi_SFAL14]
||      std.d2x   a1, *SP[Hwi_SFAL15]

||      mv.m1     am0, a0
        std.d1    a0, *SP[Hwi_SFAM0]
||      mv.m1     am1, a0
        std.d1    a0, *SP[Hwi_SFAM1]
||      mv.m1     am2, a0
        std.d1    a0, *SP[Hwi_SFAM2]
||      mv.m1     am3, a0
        std.d1    a0, *SP[Hwi_SFAM3]
||      mv.m1     am4, a0
        std.d1    a0, *SP[Hwi_SFAM4]
||      mv.m1     am5, a0
        std.d1    a0, *SP[Hwi_SFAM5]
||      mv.m1     am6, a0
        std.d1    a0, *SP[Hwi_SFAM6]
||      mv.m1     am7, a0
        std.d1    a0, *SP[Hwi_SFAM7]
||      mv.m1     am8, a0
        std.d1    a0, *SP[Hwi_SFAM8]
||      mv.m1     am9, a0
        std.d1    a0, *SP[Hwi_SFAM9]
||      mv.m1     am10, a0
        std.d1    a0, *SP[Hwi_SFAM10]
||      mv.m1     am11, a0
        std.d1    a0, *SP[Hwi_SFAM11]
||      mv.m1     am12, a0
        std.d1    a0, *SP[Hwi_SFAM12]
||      mv.m1     am13, a0
        std.d1    a0, *SP[Hwi_SFAM13]
||      mv.m1     am14, a0
        std.d1    a0, *SP[Hwi_SFAM14]
||      mv.m1     am15, a0
        std.d1    a0, *SP[Hwi_SFAM15]

        std.d1    d0, *SP[Hwi_SFD0]
        std.d1    d1, *SP[Hwi_SFD1]
        std.d1    d2, *SP[Hwi_SFD2]
        std.d1    d3, *SP[Hwi_SFD3]
        std.d1    d4, *SP[Hwi_SFD4]
        std.d1    d5, *SP[Hwi_SFD5]
        std.d1    d6, *SP[Hwi_SFD6]
        std.d1    d7, *SP[Hwi_SFD7]
        std.d1    d8, *SP[Hwi_SFD8]
        std.d1    d9, *SP[Hwi_SFD9]
        std.d1    d10, *SP[Hwi_SFD10]
        std.d1    d11, *SP[Hwi_SFD11]
        std.d1    d12, *SP[Hwi_SFD12]
        std.d1    d13, *SP[Hwi_SFD13]
        std.d1    d14, *SP[Hwi_SFD14]

        vst4d.d2  vb0, *SP[Hwi_SFVB0]
        vst4d.d2  vb1, *SP[Hwi_SFVB1]
        vst4d.d2  vb2, *SP[Hwi_SFVB2]
        vst4d.d2  vb3, *SP[Hwi_SFVB3]
        vst4d.d2  vb4, *SP[Hwi_SFVB4]
        vst4d.d2  vb5, *SP[Hwi_SFVB5]
        vst4d.d2  vb6, *SP[Hwi_SFVB6]
        vst4d.d2  vb7, *SP[Hwi_SFVB7]
        vst4d.d2  vb8, *SP[Hwi_SFVB8]
        vst4d.d2  vb9, *SP[Hwi_SFVB9]
        vst4d.d2  vb10, *SP[Hwi_SFVB10]
        vst4d.d2  vb11, *SP[Hwi_SFVB11]
        vst4d.d2  vb12, *SP[Hwi_SFVB12]
        vst4d.d2  vb13, *SP[Hwi_SFVB13]
        vst4d.d2  vb14, *SP[Hwi_SFVB14]
        vst4d.d2  vb15, *SP[Hwi_SFVB15]
||      vmv.s2    vbl0, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL0]
||      vmv.s2    vbl1, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL1]
||      vmv.s2    vbl2, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL2]
||      vmv.s2    vbl3, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL3]
||      vmv.s2    vbl4, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL4]
||      vmv.s2    vbl5, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL5]
||      vmv.s2    vbl6, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL6]
||      vmv.s2    vbl7, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBL7]
||      vmv.m2    vbm0, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM0]
||      vmv.m2    vbm1, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM1]
||      vmv.m2    vbm2, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM2]
||      vmv.m2    vbm3, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM3]
||      vmv.m2    vbm4, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM4]
||      vmv.m2    vbm5, vb0
        vst4d.d2  vb0, *SP[Hwi_SFVBM5]
||      vmv.m2    vbm6, vb0
||      mvc.c2    cucr0, vb1                  ; 2 cycle latency for CUCR regs
        vst4d.d2  vb0, *SP[Hwi_SFVBM6]
||      vmv.m2    vbm7, vb0
||      mvc.c2    cucr1, vb2
        vst4d.d2  vb0, *SP[Hwi_SFVBM7]
||      mvc.s1    rp, a0
||      mvc.c2    cucr2, vb3
        std.d1    a0, *SP[Hwi_SFRP]
||      vst4d.d2  vb1, *SP[Hwi_SFCUCR0]
||      mvc.s1    fpcr, a0
||      mvc.c2    cucr3, vb4
        std.d1    a0, *SP[Hwi_SFFPCR]
||      vst4d.d2  vb2, *SP[Hwi_SFCUCR1]
||      mvc.s1    fsr, a0
        std.d1    a0, *SP[Hwi_SFFSR]
||      vst4d.d2  vb3, *SP[Hwi_SFCUCR2]
||      mvc.s1    gfpgfr, a0
        std.d1    a0, *SP[Hwi_SFGFPGFR]
||      vst4d.d2  vb4, *SP[Hwi_SFCUCR3]
||      mvc.s1    gply, a0

        mvc.c2    cucr4, vb0                  ; 2 cycle latency for CUCR regs
        nop
        nop
        vst4d.d2  vb0, *SP[Hwi_SFCUCR4]

        mvc.c2    cucr5, vb0                  ; 2 cycle latency for CUCR regs
        nop
        nop
        vst4d.d2  vb0, *SP[Hwi_SFCUCR5]

        mvc.c2    cucr6, vb0                  ; 2 cycle latency for CUCR regs
        nop
        nop
        vst4d.d2  vb0, *SP[Hwi_SFCUCR6]

        mvc.c2    cucr7, vb0                  ; 2 cycle latency for CUCR regs
        nop
        nop
        vst4d.d2  vb0, *SP[Hwi_SFCUCR7]


        std.d1    a0, *SP[Hwi_SFGPLY]
||      mvpb.l2   p0, b0
||      mvpb.s2   p1, b1
        std.d1x   b0, *SP[Hwi_SFP0]
||      std.d2    b1, *SP[Hwi_SFP1]
||      mvpb.l2   p2, b2
||      mvpb.s2   p3, b3
        std.d1x   b2, *SP[Hwi_SFP2]
||      std.d2    b3, *SP[Hwi_SFP3]
||      mvpb.l2   p4, b4
||      mvpb.s2   p5, b5
        std.d1x   b4, *SP[Hwi_SFP4]
||      std.d2    b5, *SP[Hwi_SFP5]
||      mvpb.l2   p6, b6
||      mvpb.s2   p7, b7
        std.d1x   b6, *SP[Hwi_SFP6]
||      std.d2    b7, *SP[Hwi_SFP7]
||      mvc.s1    rxmr_s, a0
        std.d1    a0, *SP[Hwi_SFRXMR]


 MVK64 .L1 Hwi_SFSA0 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SASAVEST .D1 *A3[0], 0

 MVK64 .L1 Hwi_SFSA1 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SASAVEST .D1 *A3[0], 1

 MVK64 .L1 Hwi_SFSA2 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SASAVEST .D1 *A3[0], 2

 MVK64 .L1 Hwi_SFSA3 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SASAVEST .D1 *A3[0], 3

 MVK64 .L1 Hwi_SFSE0_0, A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SESAVEST .D1 *A3[0], 0

 MVK64 .L1 Hwi_SFSE1_0, A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SESAVEST .D1 *A3[0], 1

        mvc.s1    AHPEE, a4
        addkpc.d1 $PCR_OFFSET(Hwi_dispatchC), a3
        calla.s1     a3

        seclose.d2 0
        seclose.d2 1

 MVK64 .L1 Hwi_SFSE0_0, A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SERSTRLD .D1 *A3[0], 0

 MVK64 .L1 Hwi_SFSE1_0, A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SERSTRLD .D1 *A3[0], 1


        saclose.c2 0
        saclose.c2 1
        saclose.c2 2
        saclose.c2 3

 MVK64 .L1 Hwi_SFSA0 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SARSTRLD .D1 *A3[0], 0

 MVK64 .L1 Hwi_SFSA1 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SARSTRLD .D1 *A3[0], 1

 MVK64 .L1 Hwi_SFSA2 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SARSTRLD .D1 *A3[0], 2

 MVK64 .L1 Hwi_SFSA3 , A3
 SHLD .S1 A3, 3, A3
 ADDD .D2 A3, D15, A3 ;D15 is the SP register, per compiler ABI
 SARSTRLD .D1 *A3[0], 3

        ldd.d1    *SP[Hwi_SFRXMR], a0
        ldd.d1    *SP[Hwi_SFP7], b7
||      mvc.s1    a0, rxmr_s
        ldd.d1    *SP[Hwi_SFP6], b6
||      mv.l2     b7, p7
        ldd.d1    *SP[Hwi_SFP5], b5
||      mv.l2     b6, p6
        ldd.d1    *SP[Hwi_SFP4], b4
||      mv.l2     b5, p5
        ldd.d1    *SP[Hwi_SFP3], b3
||      mv.l2     b4, p4
        ldd.d1    *SP[Hwi_SFP2], b2
||      mv.l2     b3, p3
        ldd.d1    *SP[Hwi_SFP1], b1
||      mv.l2     b2, p2
        ldd.d1    *SP[Hwi_SFP0], b0
||      mv.l2     b1, p1
        vld4d.d1  *SP[Hwi_SFCUCR3], vb0
||      mv.l2     b0, p0
        vld4d.d1  *SP[Hwi_SFCUCR2], vb0
||      mvc.c2    vb0, cucr3
        vld4d.d1  *SP[Hwi_SFCUCR1], vb0
||      mvc.c2    vb0, cucr2
        vld4d.d1  *SP[Hwi_SFCUCR0], vb0
||      mvc.c2    vb0, cucr1
        ldd.d1    *SP[Hwi_SFGPLY], a0
||      mvc.c2    vb0, cucr0
        ldd.d1    *SP[Hwi_SFGFPGFR], a0
||      mvc.s1    a0, gply
        ldd.d1    *SP[Hwi_SFRP], a0
||      mvc.s1    a0, gfpgfr
        ldd.d1    *SP[Hwi_SFFPCR], a0
||      mvc.s1    a0, rp
        ldd.d1    *SP[Hwi_SFFSR], a0
||      mvc.s1    a0, fpcr
        mvc.s1    a0, fsr

        vld4d.d1  *SP[Hwi_SFCUCR4], vb0 
        mvc.c2    vb0, cucr4
        vld4d.d1  *SP[Hwi_SFCUCR5], vb1 
        mvc.c2    vb1, cucr5
        vld4d.d1  *SP[Hwi_SFCUCR6], vb2 
        mvc.c2    vb2, cucr6
        vld4d.d1  *SP[Hwi_SFCUCR7], vb3 
        mvc.c2    vb3, cucr7
        


        vld4d.d1  *SP[Hwi_SFVBM7], vb0
        vmv.m2    vb0, vbm7
||      vld4d.d1  *SP[Hwi_SFVBM6], vb0
        vmv.m2    vb0, vbm6
||      vld4d.d1  *SP[Hwi_SFVBM5], vb0
        vmv.m2    vb0, vbm5
||      vld4d.d1  *SP[Hwi_SFVBM4], vb0
        vmv.m2    vb0, vbm4
||      vld4d.d1  *SP[Hwi_SFVBM3], vb0
        vmv.m2    vb0, vbm3
||      vld4d.d1  *SP[Hwi_SFVBM2], vb0
        vmv.m2    vb0, vbm2
||      vld4d.d1  *SP[Hwi_SFVBM1], vb0
        vmv.m2    vb0, vbm1
||      vld4d.d1  *SP[Hwi_SFVBM0], vb0
        vmv.m2    vb0, vbm0
||      vld4d.d1  *SP[Hwi_SFVBL7], vb0
        vmv.m2    vb0, vbl7
||      vld4d.d1  *SP[Hwi_SFVBL6], vb0
        vmv.m2    vb0, vbl6
||      vld4d.d1  *SP[Hwi_SFVBL5], vb0
        vmv.m2    vb0, vbl5
||      vld4d.d1  *SP[Hwi_SFVBL4], vb0
        vmv.m2    vb0, vbl4
||      vld4d.d1  *SP[Hwi_SFVBL3], vb0
        vmv.m2    vb0, vbl3
||      vld4d.d1  *SP[Hwi_SFVBL2], vb0
        vmv.m2    vb0, vbl2
||      vld4d.d1  *SP[Hwi_SFVBL1], vb0
        vmv.m2    vb0, vbl1
||      vld4d.d1  *SP[Hwi_SFVBL0], vb0
        vmv.m2    vb0, vbl0
||      vld4d.d1  *SP[Hwi_SFVB15], vb15
        vld4d.d1  *SP[Hwi_SFVB14], vb14
        vld4d.d1  *SP[Hwi_SFVB13], vb13
        vld4d.d1  *SP[Hwi_SFVB12], vb12
        vld4d.d1  *SP[Hwi_SFVB11], vb11
        vld4d.d1  *SP[Hwi_SFVB10], vb10
        vld4d.d1  *SP[Hwi_SFVB9], vb9
        vld4d.d1  *SP[Hwi_SFVB8], vb8
        vld4d.d1  *SP[Hwi_SFVB7], vb7
        vld4d.d1  *SP[Hwi_SFVB6], vb6
        vld4d.d1  *SP[Hwi_SFVB5], vb5
        vld4d.d1  *SP[Hwi_SFVB4], vb4
        vld4d.d1  *SP[Hwi_SFVB3], vb3
        vld4d.d1  *SP[Hwi_SFVB2], vb2
        vld4d.d1  *SP[Hwi_SFVB1], vb1
        vld4d.d1  *SP[Hwi_SFVB0], vb0

        ldd.d1    *SP[Hwi_SFD14], d14
        ldd.d1    *SP[Hwi_SFD13], d13
        ldd.d1    *SP[Hwi_SFD12], d12
        ldd.d1    *SP[Hwi_SFD11], d11
        ldd.d1    *SP[Hwi_SFD10], d10
        ldd.d1    *SP[Hwi_SFD9], d9
        ldd.d1    *SP[Hwi_SFD8], d8
        ldd.d1    *SP[Hwi_SFD7], d7
        ldd.d1    *SP[Hwi_SFD6], d6
        ldd.d1    *SP[Hwi_SFD5], d5
        ldd.d1    *SP[Hwi_SFD4], d4
        ldd.d1    *SP[Hwi_SFD3], d3
        ldd.d1    *SP[Hwi_SFD2], d2
        ldd.d1    *SP[Hwi_SFD1], d1
        ldd.d1    *SP[Hwi_SFD0], d0

        ldd.d1    *SP[Hwi_SFAM15], a0
        mv.m1     a0, am15
||      ldd.d1    *SP[Hwi_SFAM14], a0
        mv.m1     a0, am14
||      ldd.d1    *SP[Hwi_SFAM13], a0
        mv.m1     a0, am13
||      ldd.d1    *SP[Hwi_SFAM12], a0
        mv.m1     a0, am12
||      ldd.d1    *SP[Hwi_SFAM11], a0
        mv.m1     a0, am11
||      ldd.d1    *SP[Hwi_SFAM10], a0
        mv.m1     a0, am10
||      ldd.d1    *SP[Hwi_SFAM9], a0
        mv.m1     a0, am9
||      ldd.d1    *SP[Hwi_SFAM8], a0
        mv.m1     a0, am8
        ldd.d1    *SP[Hwi_SFAM7], a0
        mv.m1     a0, am7
||      ldd.d1    *SP[Hwi_SFAM6], a0
        mv.m1     a0, am6
||      ldd.d1    *SP[Hwi_SFAM5], a0
        mv.m1     a0, am5
||      ldd.d1    *SP[Hwi_SFAM4], a0
        mv.m1     a0, am4
||      ldd.d1    *SP[Hwi_SFAM3], a0
        mv.m1     a0, am3
||      ldd.d1    *SP[Hwi_SFAM2], a0
        mv.m1     a0, am2
||      ldd.d1    *SP[Hwi_SFAM1], a0
        mv.m1     a0, am1
||      ldd.d1    *SP[Hwi_SFAM0], a0
        mv.m1     a0, am0

||      ldd.d1    *SP[Hwi_SFAL15], a0
        mv.m1     a0, al15
||      ldd.d1    *SP[Hwi_SFAL14], a0
        mv.m1     a0, al14
||      ldd.d1    *SP[Hwi_SFAL13], a0
        mv.m1     a0, al13
||      ldd.d1    *SP[Hwi_SFAL12], a0
        mv.m1     a0, al12
||      ldd.d1    *SP[Hwi_SFAL11], a0
        mv.m1     a0, al11
||      ldd.d1    *SP[Hwi_SFAL10], a0
        mv.m1     a0, al10
||      ldd.d1    *SP[Hwi_SFAL9], a0
        mv.m1     a0, al9
||      ldd.d1    *SP[Hwi_SFAL8], a0
        mv.m1     a0, al8
||      ldd.d1    *SP[Hwi_SFAL7], a0
        mv.m1     a0, al7
||      ldd.d1    *SP[Hwi_SFAL6], a0
        mv.m1     a0, al6
||      ldd.d1    *SP[Hwi_SFAL5], a0
        mv.m1     a0, al5
||      ldd.d1    *SP[Hwi_SFAL4], a0
        mv.m1     a0, al4
||      ldd.d1    *SP[Hwi_SFAL3], a0
        mv.m1     a0, al3
||      ldd.d1    *SP[Hwi_SFAL2], a0
        mv.m1     a0, al2
||      ldd.d1    *SP[Hwi_SFAL1], a0
        mv.m1     a0, al1
||      ldd.d1    *SP[Hwi_SFAL0], a0
        mv.m1     a0, al0

        ldd.d1    *SP[Hwi_SFA15], a15
        ldd.d1    *SP[Hwi_SFA14], a14
        ldd.d1    *SP[Hwi_SFA13], a13
        ldd.d1    *SP[Hwi_SFA12], a12
        ldd.d1    *SP[Hwi_SFA11], a11
        ldd.d1    *SP[Hwi_SFA10], a10
        ldd.d1    *SP[Hwi_SFA9], a9
        ldd.d1    *SP[Hwi_SFA8], a8
        ldd.d1    *SP[Hwi_SFA7], a7
        ldd.d1    *SP[Hwi_SFA6], a6
        ldd.d1    *SP[Hwi_SFA5], a5
        ldd.d1    *SP[Hwi_SFA4], a4
        ldd.d1    *SP[Hwi_SFA3], a3
        ldd.d1    *SP[Hwi_SFA2], a2
;;        ldd.d1    *SP[Hwi_SFA1], a1    ; restored below
;;        ldd.d1    *SP[Hwi_SFA0], a0    ; restored below

        addd.d1   SP, Hwi_STACKFRAMESIZE*8, SP     ; free stack frame

        ldd.d1    *ECSP[0], a0
||      ldd.d2    *ECSP[1], a1
        rete.s1   a0, a1
||      ldd.d1    *ECSP[0x300], a0
||      ldd.d2    *ECSP[0x301], a1

;        .endasmfunc
