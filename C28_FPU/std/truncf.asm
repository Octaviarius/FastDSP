
	.global		_truncf

; 3 cycles
	.sect .text
_truncf:
	FRACF32		R1H, R0H		;get frac
	NOP
	SUBF32		R0H, R0H, R1H	;calc int part
	LRETR

