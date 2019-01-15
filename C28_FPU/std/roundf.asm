
	.global		_roundf

; 11 cycles
	.sect .text
_roundf:

	CMPF32		R0H, #0x0
	MOVST0		ZF, NF

	BF			pos, GEQ
	ADDF32		R0H, #-0.5, R0H
	NOP
	FRACF32		R1H, R0H
	NOP
	SUBF32		R0H, R0H, R1H
	LRETR
pos:
	ADDF32		R0H, #0.5, R0H
	NOP
	FRACF32		R1H, R0H
	NOP
	SUBF32		R0H, R0H, R1H
	LRETR
