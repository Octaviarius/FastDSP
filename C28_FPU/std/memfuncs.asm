
	.global _memcpy
	.global _memcpy16
	.global _memset
	.global _memset16
	.global _memmove
	.global _memswap








;=================/ memcpy /========================
	.text
_memcpy:

	SUBB AL, #1							;Repeat "N-1" times
	BF done_low_memcpy, NC				;Branch if N was zero
	MOVL XAR7, XAR5						;XAR7 = XAR5 = dst
	RPT @AL
	||PREAD *XAR4++, *XAR7				;Do the copy


done_low_memcpy:

	CMP 	AH, #0				;return if AH == 0
	BF 		done_hi_memcpy, EQ	;-//-

	ADD		AL, #1				;restore AL and save
	PUSH	AL					;-//-
	PUSH	#0xffff				;push value

	SUBB	AH, #1				;AH - 1
	MOVZ	AR0, AH				;-//-

	MOVL	ACC, XAR7			;increment SRC
	ADD		ACC, *-SP[2]		;-//-
	MOVL	XAR7, ACC			;-//-


loop_memcpy:
	RPT 	*-SP[1]
	||PREAD *XAR4++, *XAR7		;Do the copy

	MOVL	ACC, XAR7			;increment SRC by 0xffff
	ADD		ACC, *-SP[1]		;-//-
	MOVL	XAR7, ACC			;-//-
	BANZ	loop_memcpy, AR0--
;loop

	ADD		SP, #2				;restore stack
done_hi_memcpy:

	LRETR									;return










;=================/ memcpy16 /========================
	.text
_memcpy16:
		ADDB AL, #-1							;Repeat "N-1" times
		BF done, NC								;Branch if N was zero
		MOVL XAR7, XAR5							;XAR7 = XAR5 = dst
		RPT @AL
	||	PREAD *XAR4++, *XAR7					;Do the copy

;Finish up
done:
		LRETR									;return










;=================/ memset /========================
	.text
_memset:
	PUSH	AH

	SUBB 	AL, #1					;Repeat "N-1" times
	BF 		done_low_memset, NC			;Branch if N was zero

	MOV		AH, AR5
	RPT 	@AL
	||MOV 	*XAR4++, AH				;Do the copy
done_low_memset:

	CMP 	*-SP[1], #0				;return if AH == 0
	BF 		done_hi_memset, EQ			;-//-

	MOV		AL, AR5
	PUSH	#0xffff				;push value

	MOVZ	AR0, *-SP[2]		;-//-
	SUBB	XAR0, #1			;AH - 1

loop_memset:
	RPT 	*-SP[1]
	||MOV *XAR4++, AL			;Do the copy
	BANZ	loop_memset, AR0--
;loop

	SUBB	SP, #1				;restore stack

done_hi_memset:

	SUBB	SP, #1				;restore stack

	LRETR									;return











;=================/ memset16 /========================
_memset16:
		ADDB		AH, #-1						;Repeat "N-1" times
		BF			done_memset16, NC					;Branch if N was zero
		RPT			@AH
	||	MOV			*XAR4++, AL					;Initialize the memory

done_memset16:
		LRETR									;return









;=================/ memmove /========================
	.text
_memmove:

	PUSH	ACC
	MOVL	ACC, XAR5

	CMPL	ACC, XAR4
	BF		gt_memmove, GT
	BF		eq0_memmove, EQ
;less
	MOVL	ACC, XAR4
	ADDL	ACC, *-SP[2]
	MOVL	XAR4, ACC

	MOVL	ACC, XAR5
	ADDL	ACC, *-SP[2]
	MOVL	XAR5, ACC

	POP		ACC
;loop
loop_memmove:
	MOVZ	AR0, *--XAR5
	MOV		*--XAR4, AR0
	SUBB	ACC, #1
	BF		loop_memmove, NEQ
;end loop
	LRETR



gt_memmove:
	POP		ACC
	LCR		_memcpy
	LRETR

eq0_memmove:
	POP		ACC
	LRETR












;=================/ memswap /========================
_memswap:

	TBIT		AL, #0
	BF			double_memswap, NTC

	MOV			AR0, AL

	MOV			AL, *XAR5
	MOV			AH, *XAR4
	MOV			*XAR4++, AL
	MOV			*XAR5++, AH

	MOV			AL, AR0

double_memswap:
	LSR			AL, #1
	SUBB		AL, #1
	BF			return_memswap, NC
;loop
	NOP
	RPTB		loop_memswap, AL
	MOV32		R0H, *XAR5
	MOV32		R1H, *XAR4
	MOV32		*XAR4++, R0H
	MOV32		*XAR5++, R1H
loop_memswap:

return_memswap:
	LRETR
