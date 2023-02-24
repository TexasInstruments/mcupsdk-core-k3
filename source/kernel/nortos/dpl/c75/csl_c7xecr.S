

	.global CSL_c7xSetTCR0
CSL_c7xSetTCR0:
	MVC	.S1	A4,		ECR785		;; Table Control Register 0
	RET	.B1



	.global CSL_c7xSetTBR0
CSL_c7xSetTBR0:
	MVC	.S1	A4,		ECR787		;; Table Base Register 0
	RET	.B1



	.global CSL_c7xSetMAR
CSL_c7xSetMAR:
	MVC	.S1	A4,		ECR789		;; Memory Attribute Register
	RET	.B1



	.global CSL_c7xSetSCR
CSL_c7xSetSCR:
	MVC	.S1	A4,		ECR784		;; System Control Register
	RET	.B1


	.global CSL_c7xSetL2CFG
CSL_c7xSetL2CFG:
	MVC	.S1	A4,		ECR384		;; L2 Cache Configuration Register
	RET	.B1

	.global CSL_c7xMmuTlbInvAll
CSL_c7xMmuTlbInvAll:                               ;; writing 0's to TLB_INV invalidates entire TLB
    ANDD    .L1     A4, 0x0, A4
    MVC     .S1     A4, TLB_INV
    RET     .B1

	.global CSL_c7xGetTLB_INVC
CSL_c7xGetTLB_INVC:
    MVC     .S1     ECR778, A4      ;; TLB Complete Register
    RET     .B1
