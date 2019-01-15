
	.global		_fmodf

	.ref		FS$$DIV


	.sect .text
_fmodf:
	MOV32		*SP++, R1H
	LCR			FS$$DIV			;calc a/b
	FRACF32		R0H, R0H		;get fraction part
	MOV32		R1H, *--SP
	MPYF32		R0H, R0H, R1H
	LRETR

