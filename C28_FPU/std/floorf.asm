
	.global		_floorf

; 7 cycles
	.sect .text
_floorf:

	FRACF32		R1H, R0H		;get frac
	MOVF32		R2H, #0.0
	SUBF32		R0H, R0H, R1H	;calc int part
	ABSF32		R1H, R1H
	MOVF32		R3H, #1.0
	MAXF32		R1H, R2H		;if frac < 0.0 then load 1.0
	||MOV32		R2H, R3H
	SUBF32		R0H, R0H, R2H

	LRETR

