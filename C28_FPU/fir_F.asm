
	.global _fir_process_F



ARG_BUFF 	.set 0
ARG_CIDX 	.set 2
ARG_SIZE 	.set 3
ARG_INPUT 	.set 4
ARG_OUTPUT 	.set 6



;T = 49 + 10*N  CPU cycles
	.sect .text
_fir_process_F:


;save context
	PUSH		XAR1
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

;main algorithm
	MOVL		XAR7, *XAR4++				;load WEIGHTS
	MOVL		XAR6, *+XAR4[ARG_BUFF]		;load BUFFER ptr
	MOVL		ACC, *+XAR4[ARG_CIDX]		;load AL=CIDX, AH=SIZE


;calc new CIDX
	CMP			AL, #0
	BF			if_cidx0, NEQ
	MOV			AL, AH
if_cidx0:
	SUBB		AL, #1
	MOV			*+XAR4[ARG_CIDX], AL		;save new CIDX value

	LSL			ACC, #1						;mpy by 4 SIZE and CIDX
	SUBB		AH, #2
	MOVL		XAR1, ACC					;load AR1=CIDX, AR1H=SIZE circle indexer
;_____


	ZERO		R2H							;set zero
	ZERO		R3H							;-//-
	ZERO		R6H							;-//-
	ZERO		R7H							;-//-


	MOV32		R0H, *+XAR4[ARG_INPUT]		;load input
	MOV32		*+XAR6[AR1], R0H			;write input_re to BUFFER
	MOV			AH, *+XAR4[ARG_SIZE]		;load SIZE

;mpy loop
	.lp_amode
	SETC		AMODE

	SUBB		AH, #1
	RPT			AH
	||MACF32	R3H, R7H, *+XAR6[AR1%++], *XAR7++

	.c28_amode
	CLRC		AMODE
;____

	ADDF32		R0H, R3H, R2H
	ADDF32		R1H, R7H, R6H
	||MOV32		*--SP, R7H 					;restore R7H
	MOV32		*--SP, R6H					;restore R6H
	ADDF32		R0H, R0H, R1H
	POP			XAR1						;restore XAR1

	MOV32		*+XAR4[ARG_OUTPUT], R0H		;write output_re

	LRETR













