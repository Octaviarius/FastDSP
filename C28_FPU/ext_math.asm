
	.global _pow2_F



	.sect .text
_pow2_F:
	ADDB   		AL, #127
	AND			AL, #255
	MOV			T, #23
	LSLL		ACC, T
	PUSH		ACC
	MOV32		R0H, *--SP
	LRETR
