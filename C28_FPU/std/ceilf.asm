
	.global		_ceilf

; 7 cycles
	.sect .text
_ceilf:

	FRACF32		R1H, R0H		;get frac
	MOVF32		R2H, #0.0
	SUBF32		R0H, R0H, R1H	;calc int part
	ABSF32		R1H, R1H
	MOVF32		R3H, #1.0
	MINF32		R1H, R2H		;if frac > 0.0 then load 1.0
	||MOV32		R2H, R3H
	ADDF32		R0H, R0H, R2H

	LRETR

