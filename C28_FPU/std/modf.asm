	.global _modff

; 5 cycles
	.sect .text
_modff:
	FRACF32		R1H, R0H
	NOP
	SUBF32		R2H, R0H, R1H
	MOV32		R0H, R1H
	MOV32		*XAR4, R2H
	LRETR
