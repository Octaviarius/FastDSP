
	.global		_roundf

; 8 cycles
	.sect .text
_roundf:

	MOVF32		R2H, #0.5
	CMPF32		R0H, #0.0
	NEGF32		R2H, R2H, LT

	ADDF32		R0H, R0H, R2H
	NOP
	FRACF32		R1H, R0H
	NOP
	SUBF32		R0H, R0H, R1H

	LRETR
