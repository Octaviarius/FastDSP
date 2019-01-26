
	.global _fir_process_CF
	
	

ARG_WA 		.set 0
ARG_BUFF 	.set 2
ARG_CIDX 	.set 4
ARG_SIZE 	.set 5
ARG_INPUT 	.set 6
ARG_OUTPUT 	.set 10



;T = 49 + 10*N  CPU cycles
	.sect .text
_fir_process_CF:


;save context
	PUSH		XAR1
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

;main algorithm
	MOVL		XAR5, *+XAR4[ARG_WA]		;load WEIGHTS
	MOVL		XAR6, *+XAR4[ARG_BUFF]		;load BUFFER ptr
	MOVL		ACC, *+XAR4[ARG_CIDX]		;load AL=CIDX, AH=SIZE


;calc new CIDX
	CMP			AL, #0
	BF			if_cidx0, NEQ
	MOV			AL, AH
if_cidx0:
	SUBB		AL, #1
	MOV			*+XAR4[ARG_CIDX], AL		;save new CIDX value

	LSL			ACC, #2						;mpy by 4 SIZE and CIDX
	SUBB		AH, #2
	MOVL		XAR1, ACC					;load AR1=CIDX, AR1H=SIZE circle indexer
;_____


	MOV			AR0, #ARG_INPUT				;load input_re
	MOV32		R0H, *+XAR4[AR0]			;-//-
	MOV			AR0, #ARG_INPUT+2			;load input_im
	MOV32		R1H, *+XAR4[AR0]			;-//-

	ZERO		R6H							;accum re = 0
	ZERO		R7H							;accum im = 0

	MOV			AH, *+XAR4[ARG_SIZE]		;load SIZE

	.lp_amode
	SETC		AMODE

	MOV32		*+XAR6[AR1%++], R0H		;write input_re to BUFFER
	MOV32		*+XAR6[AR1%++], R1H		;write input_im to BUFFER

	MOV32		R2H, *XAR5++			;load w_re
	MOV32		R3H, *XAR5++			;load w_im

	SUBB		AH, #1
;loop_a
	RPTB		loop_a, AH

	MPYF32		R4H, R0H, R2H		;calc x_re * w_re
	MPYF32		R5H, R1H, R2H		;calc x_im * w_re
	||MOV32		R2H, *XAR5++		;load next w_re

	ADDF32		R6H, R6H, R4H		;accum re += x_re * w_re

	MPYF32		R4H, R1H, R3H		;calc x_im * w_im
	||ADDF32	R7H, R7H, R5H		;accum im += x_im * w_re
	MPYF32		R5H, R0H, R3H		;calc x_re * w_im
	||MOV32		R3H, *XAR5++		;load next w_im

	SUBF32		R6H, R6H, R4H		;accum re -= x_im * w_im
	||MOV32		R0H, *+XAR6[AR1%++]	;load next x_re
	ADDF32		R7H, R7H, R5H		;accum im += x_re * w_im
	||MOV32		R1H, *+XAR6[AR1%++]	;load next x_im
loop_a:

	.c28_amode
	CLRC		AMODE
	
	ADDB		XAR4, #ARG_OUTPUT
	MOV32		*+XAR4[0], R6H		;write output_re
	MOV32		*+XAR4[2], R7H		;write output_im


;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
	POP			XAR1

	LRETR
	
	
	
	
	
	
	
	
	
	
	
	
	
