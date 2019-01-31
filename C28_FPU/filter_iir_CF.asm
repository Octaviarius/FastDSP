
	.global _iir_process_CF
	
ARG_WA 		.set 0
ARG_WB 		.set 2
ARG_BUFF 	.set 4
ARG_CIDX 	.set 6
ARG_SIZE 	.set 7
ARG_SIZEA 	.set 8
ARG_SIZEB 	.set 9
ARG_INPUT 	.set 10
ARG_OUTPUT 	.set 14








;T = 85 + 10*(N+M)  CPU cycles
	.sect .text
_iir_process_CF:



;save context
	PUSH		XAR1
	PUSH		XAR2
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H
;_____


	MOVL		XAR2, XAR4
	ADDB		XAR2, #ARG_INPUT			;load ptr to input
	MOVL		XAR5, *+XAR4[ARG_WA]		;load w_a
	MOVL		XAR6, *+XAR4[ARG_BUFF]		;load BUFFER ptr
	MOVL		ACC, *+XAR4[ARG_CIDX]		;load AL=CIDX, AH=SIZE



;config circular buffer
	CMP			AL, #0				;if CIDX_ptr <= 0
	BF			if_cidx_0, GT		;then CIDX_ptr = SIZE
	ADD			AL, AH
if_cidx_0:
	SUBB		AL, #1

	MOV			*+XAR4[ARG_CIDX], AL		;save new CIDX

	LSL			ACC, #2						;mpy by 4 SIZE and CIDX
	SUBB		AH, #2
	MOVL		XAR1, ACC					;load AR1=CIDX, AR1H=SIZE circle indexer
;calc next IDX





;*******convolve loopback
	.lp_amode
	SETC		AMODE

	MOV			AL, AR1					;save CIDX

	ZERO		R6H
	ZERO		R7H
	MOV32		R0H, *XAR2++			;load input_re
	MOV32		R1H, *XAR2++			;load input_im
	MOV32		*+XAR6[AR1%++], R0H 	;save input_re
	MOV32		*+XAR6[AR1%++], R1H		;save input_im
	MOV32		R2H, *XAR5++			;load wa_re
	MOV32		R3H, *XAR5++			;load wa_im


	MOV			AR0, #ARG_SIZEA
	MOV			AH, *+XAR4[AR0]
	SUBB		AH, #1
;loop_a
	RPTB		loop_a, AH

	MPYF32		R4H, R0H, R2H		;calc x_re * wa_re
	MPYF32		R5H, R1H, R2H		;calc x_im * wa_re
	||MOV32		R2H, *XAR5++		;load next wa_re

	ADDF32		R6H, R6H, R4H		;accum re += x_re * wa_re

	MPYF32		R4H, R1H, R3H		;calc x_im * wa_im
	||ADDF32	R7H, R7H, R5H		;accum im += x_im * wa_re
	MPYF32		R5H, R0H, R3H		;calc x_re * wa_im
	||MOV32		R3H, *XAR5++		;load next wa_im

	SUBF32		R6H, R6H, R4H		;accum re -= x_im * wa_im
	||MOV32		R0H, *+XAR6[AR1%++]	;load next x_re
	ADDF32		R7H, R7H, R5H		;accum im += x_re * wa_im
	||MOV32		R1H, *+XAR6[AR1%++]	;load next x_im
loop_a:

;save new recursive value to buffer
	MOV			AR1, AL
	MOV32		*+XAR6[AR1%++], R6H
	MOV32		*+XAR6[AR1%++], R7H

	.c28_amode
	CLRC		AMODE







;***** convolve direct

	MOVL		XAR5, *+XAR4[ARG_WB]		;load w_b
	MOVL		XAR6, *+XAR4[ARG_BUFF]		;load BUFFER ptr
	MOV			AR1, AL						;restore CIDX

	ZERO		R6H
	ZERO		R7H

	.lp_amode
	SETC		AMODE

	MOV32		R0H, *+XAR6[AR1%++]		;load x_re
	MOV32		R1H, *+XAR6[AR1%++]		;load x_im
	MOV32		R2H, *XAR5++			;load wa_re
	MOV32		R3H, *XAR5++			;load wa_im

	MOV			AR0, #ARG_SIZEB
	MOV			AH, *+XAR4[AR0]
	SUBB		AH, #1
;loop_b
	RPTB		loop_b, AH

	MPYF32		R4H, R0H, R2H		;calc x_re * wa_re
	MPYF32		R5H, R1H, R2H		;calc x_im * wa_re
	||MOV32		R2H, *XAR5++		;load next wa_re

	ADDF32		R6H, R6H, R4H		;accum re += x_re * wa_re

	MPYF32		R4H, R1H, R3H		;calc x_im * wa_im
	||ADDF32	R7H, R7H, R5H		;accum im += x_im * wa_re
	MPYF32		R5H, R0H, R3H		;calc x_re * wa_im
	||MOV32		R3H, *XAR5++		;load next wa_im

	SUBF32		R6H, R6H, R4H		;accum re -= x_im * wa_im
	||MOV32		R0H, *+XAR6[AR1%++]	;load next x_re
	ADDF32		R7H, R7H, R5H		;accum im += x_re * wa_im
	||MOV32		R1H, *+XAR6[AR1%++]	;load next x_im
loop_b:

	.c28_amode
	CLRC		AMODE

	MOV32		*XAR2++, R6H			;-//-
	MOV32		*XAR2++, R7H			;-//-


;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
	POP			XAR2
	POP			XAR1

	LRETR
	
	
	
	
	
	
	
	
	
	
	
	
	
