
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
	BF memcpy_done_low, NC				;Branch if N was zero
	MOVL XAR7, XAR5						;XAR7 = XAR5 = dst
	RPT @AL
	||PREAD *XAR4++, *XAR7				;Do the copy


memcpy_done_low:

	CMP 	AH, #0				;return if AH == 0
	BF 		memcpy_done_hi, EQ	;-//-

	ADD		AL, #1				;restore AL and save
	PUSH	AL					;-//-
	PUSH	#0xffff				;push value

	SUBB	AH, #1				;AH - 1
	MOVZ	AR0, AH				;-//-

	MOVL	ACC, XAR7			;increment SRC
	ADD		ACC, *-SP[2]		;-//-
	MOVL	XAR7, ACC			;-//-


memcpy_loop:
	RPT 	*-SP[1]
	||PREAD *XAR4++, *XAR7		;Do the copy

	MOVL	ACC, XAR7			;increment SRC by 0xffff
	ADD		ACC, *-SP[1]		;-//-
	MOVL	XAR7, ACC			;-//-
	BANZ	memcpy_loop, AR0--
;loop

	ADD		SP, #2				;restore stack
memcpy_done_hi:

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
	BF 		memset_done_low, NC			;Branch if N was zero

	MOV		AH, AR5
	RPT 	@AL
	||MOV 	*XAR4++, AH				;Do the copy
memset_done_low:

	CMP 	*-SP[1], #0				;return if AH == 0
	BF 		memset_done_hi, EQ			;-//-

	MOV		AL, AR5
	PUSH	#0xffff				;push value

	MOVZ	AR0, *-SP[2]		;-//-
	SUBB	XAR0, #1			;AH - 1

memset_loop:
	RPT 	*-SP[1]
	||MOV *XAR4++, AL			;Do the copy
	BANZ	memset_loop, AR0--
;loop

	SUBB	SP, #1				;restore stack

memset_done_hi:

	SUBB	SP, #1				;restore stack

	LRETR									;return











;=================/ memset16 /========================
_memset16:
		ADDB		AH, #-1						;Repeat "N-1" times
		BF			memset_done16, NC					;Branch if N was zero
		RPT			@AH
	||	MOV			*XAR4++, AL					;Initialize the memory

memset_done16:
		LRETR									;return









;=================/ memmove /========================
	.text
_memmove:

	PUSH	ACC
	MOVL	ACC, XAR5

	CMPL	ACC, XAR4
	BF		memmove_gt, GT
	BF		memmove_eq0, EQ
;less
	MOVL	ACC, XAR4
	ADDL	ACC, *-SP[2]
	MOVL	XAR4, ACC

	MOVL	ACC, XAR5
	ADDL	ACC, *-SP[2]
	MOVL	XAR5, ACC

	POP		ACC
;loop
memmove_loop:
	MOVZ	AR0, *--XAR5
	MOV		*--XAR4, AR0
	SUBB	ACC, #1
	BF		memmove_loop, NEQ
;end loop
	LRETR



memmove_gt:
	POP		ACC
	LCR		_memcpy
	LRETR

memmove_eq0:
	POP		ACC
	LRETR












;=================/ memswap /========================
_memswap:

	TBIT		AL, #0
	BF			memswap_double, NTC

	MOVL		XAR0, ACC

	MOV			AL, *XAR5
	MOV			AH, *XAR4
	MOV			*XAR4++, AL
	MOV			*XAR5++, AH

	MOVL		ACC, XAR0

memswap_double:
	MOVB		T, #1
	LSRL		ACC, #1
	SUBB		ACC, #1
	BF			memswap_return, NC
	
;loop
memswap_highloop:
	NOP
	RPTB		memswap_loop, AL
	MOV			AL, *XAR5
	MOV			AR6, *XAR4
	MOV			*XAR4++, AL
	MOV			*XAR5++, AR6
	MOV			AL, *XAR5
	MOV			AR6, *XAR4
	MOV			*XAR4++, AL
	MOV			*XAR5++, AR6
memswap_loop:

	CMPB		AH, #0
	BF			memswap_return, EQ
	MOVW		AL, #0xffff
	SUBB		AH
	SB			memswap_highloop
	
memswap_return:
	LRETR
