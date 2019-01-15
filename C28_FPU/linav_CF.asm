

	.global _fill_CFV

	.global _convert_CI16_CF32
	.global _convert_CI32_CF32
	.global _convert_FV_CFV

	.global _add_CFS_CFS
	.global _add_CFV_CFS
	.global _add_CFV_CFV
	.global _add_CFV_CFV_CFS
	.global _add_CFV_CFV_CFS2
	.global _add_CFV_CFV_FS2

	.global _sub_CFS_CFS
	.global _sub_CFV_CFV

	.global _mul_CFS_CFS
	.global _mul_CFS_cFS
	.global _mul_CFS_FS
	.global _mul_CFV_FS
	.global _mul_CFV_FV
	.global _mul_CFV_CFV
	.global _mul_CFV_cFV
	.global _mul_CFV_CFS
	.global _smul_CFV_CFV
	.global _smul_CFV_cFV

	.global _div_CFS_CFS
	.global _div_CFV_CFV
	.global _inv_CFV

	.global _sum_CFV

	.global _abs_CFV
	.global _abs2_CFV

	.global _conjugate_CFS
	.global _conjugate_CFV

	.global _mag_CFS
	.global _mag2_CFS
	.global _mag_CFV
	.global _phase_CFS
	.global _phase_CFV

	.global _min_CFS
	.global _max_CFS
	.global _min_CFV
	.global _max_CFV

	.global _mean_CFV

	.global _conv_circle_CFV

	.global _traverse_CFV
	.global _traverse_CFV_CFV



	.ref _sqrtf
	.ref _atan2f
	.ref FS$$DIV






;================/ _fill_CFV /==============
;4 + 6*N
	.sect .text
_fill_CFV:
	SUBB		AL, #1
	MOVZ		AR0, AL
	MOV32		R0H, *+XAR5[0]
	MOV32		R1H, *+XAR5[2]
loop_fill_CFV:
	MOV32		*XAR4++, R0H
	MOV32		*XAR4++, R1H
	BANZ		loop_fill_CFV, AR0--

	LRETR







;******************************** Converter functions ******************************


;================/ _convert_CI16_CF32 /==============
;3 + 9*N
	.sect .text
_convert_CI16_CF32:

	MOVB		AH, #0
	MOVL		XAR0, ACC

	LSL			ACC, #2
	ADDL		ACC, XAR4
	MOVL		XAR4, ACC

	MOVL		ACC, XAR0
	LSL			ACC, #1
	ADDL		ACC, XAR5
	MOVL		XAR5, ACC

	MOVL		ACC, XAR0
	SUBB		AL, #1
	MOVF32		R2H, #3.0517578125E-5

	RPTB		loop_convert_CI16_CF32, AL
	I16TOF32	R1H, *--XAR5
	I16TOF32	R0H, *--XAR5
	MPYF32		R1H, R1H, R2H
	MPYF32		R0H, R0H, R2H
	MOV32		*--XAR4, R1H
	MOV32		*--XAR4, R0H
loop_convert_CI16_CF32:
	LRETR



;================/ _convert_CI32_CF32 /==============
;3 + 9*N
	.sect .text
_convert_CI32_CF32:

	SUBB		AL, #1
	MOVF32		R2H, #4.65661287307739E-10

	RPTB		loop_convert_CI32_CF32, AL
	I32TOF32	R0H, *XAR5++
	I32TOF32	R1H, *XAR5++
	MPYF32		R0H, R0H, R2H
	MPYF32		R1H, R1H, R2H
	MOV32		*XAR4++, R0H
	MOV32		*XAR4++, R1H
loop_convert_CI32_CF32:
	LRETR



;================/ _convert_FV_CFV /==============
;3 + 9*N
	.sect .text
_convert_FV_CFV:

	SUBB		AL, #1
	MOVF32		R2H, #3.0517578125E-5

	RPTB		loop_convert_FV_CFV, AL
	I32TOF32	R0H, *XAR5++
	I32TOF32	R1H, *XAR5++
	MPYF32		R0H, R0H, R2H
	MPYF32		R1H, R1H, R2H
	MOV32		*XAR4++, R0H
	MOV32		*XAR4++, R1H
loop_convert_FV_CFV:
	LRETR














;******************************** Addition functions ******************************

;================/ _add_CFS_CFS /==============
	.sect .text
_add_CFS_CFS:

	MOV32 		R0H, *+XAR4[0]					;R0H = ls_re
	MOV32 		R2H, *+XAR5[0]					;R2H = rs_re

	ADDF32 		R0H, R0H, R2H					;out_re = ls_re + ls_re
	|| MOV32 	R1H, *+XAR4[2]					;R1H = ls_im

	MOV32 		R3H, *+XAR5[2]					;R3H = rs_im
	ADDF32		R1H, R1H, R3H					;out_im = ls_im + rs_im

	MOV32 		*+XAR6[0], R0H					;store out_re
	MOV32 		*+XAR6[2], R1H					;store out_im

	LRETR







;================/ _add_CFV_CFS /==============
	.sect .text
_add_CFV_CFS:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer

	MOV32 		R2H, *+XAR6[0]		;load right c_re
	MOV32 		R3H, *+XAR6[2]		;load right c_im

	SUBB		AL, #1
;loop
	RPTB 		loop_add_CFV_CFS, AL
	MOV32		R0H, *XAR5++		;load  lv_re
	MOV32		R1H, *XAR5++		;load  lv_im

	ADDF32 		R0H, R0H, R2H		;y_re = lv_re + c_re
	ADDF32 		R1H, R1H, R3H		;y_im = lv_im + c_im

	MOV32		*XAR4++, R0H		;write y_re
	MOV32		*XAR4++, R1H		;write y_im
loop_add_CFV_CFS:

	LRETR








;================/ _add_CFV_CFV /==============
	.sect .text
_add_CFV_CFV:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer

	MOV32 		R2H, *XAR6++		;load first right re
	MOV32 		R3H, *XAR6++		;load first right im

	SUBB		AL, #1
;loop
	RPTB 		loop_add_CFV_CFV, AL
	MOV32		R0H, *XAR5++		;load  left re
	MOV32		R1H, *XAR5++		;load  left im

	ADDF32 		R0H, R0H, R2H		;y_re = re1 + re2
	||MOV32		R2H, *XAR6++		;load next right re
	ADDF32 		R1H, R1H, R3H		;y_im = im1 + im2
	||MOV32		R3H, *XAR6++		;load next right im

	MOV32		*XAR4++, R0H		;write y_re
	MOV32		*XAR4++, R1H		;write y_im
loop_add_CFV_CFV:

	LRETR













;================/ _add_CFV_FV /==============
	.sect .text
_add_CFV_FV:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer

	MOV32 		R2H, *XAR6++		;load first right re

	SUBB		AL, #1
;loop
	RPTB 		loop_add_CFV_FV, AL
	MOV32		R0H, *XAR5++		;load left re
	ADDF32 		R0H, R0H, R2H		;y_re = re1 + r
	||MOV32		R2H, *XAR6++		;load next right r
	MOV32		R1H, *XAR5++
	MOV32		*XAR4++, R0H		;write y_re
	MOV32		*XAR4++, R1H		;write y_im
loop_add_CFV_FV:

	LRETR










;================/ _add_CFV_CFV_CFS /==============
;3 + 15*N cycles
_add_CFV_CFV_CFS:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer
	MOVL		XAR7, *-SP[6]		;load right-costant pointer

	MOV32		*SP++, R4H

	SUBB		AL, #1

;loop
	RPTB 		loop_add_CFV_CFV_CFS, AL

	MOV32 		R0H, *XAR6++		;R0H = rv_re
	MOV32 		R2H, *+XAR7[0]		;R2H = c_re

	MPYF32 		R3H, R0H, R2H		;R3H = rv_re * c_re
	|| MOV32 	R1H, *XAR6++		;R1H = rv_im

	MPYF32		R2H, R1H, R2H		;R2H = rv_im * c_re
	|| MOV32 	R4H, *+XAR7[2]		;R4H = c_im

	MPYF32 		R1H, R1H, R4H		;R1H = rv_im * c_im
	MPYF32 		R0H, R0H, R4H		;R0H = rv_re * c_im

	SUBF32 		R3H, R3H, R1H		;R3H = (r_re * c_re) - (r_im * c_im)
	||MOV32 	R1H, *XAR5++		;load lv_re
	ADDF32 		R2H, R2H, R0H		;R2H = (r_im * c_re) + (r_re * c_im)
	||MOV32 	R0H, *XAR5++		;load lv_im

	ADDF32 		R1H, R1H, R3H		;y_re = re1 + re2
	ADDF32 		R0H, R0H, R2H		;y_im = im1 + im2
	MOV32		*XAR4++, R1H		;write y_re
	MOV32		*XAR4++, R0H		;write y_im
loop_add_CFV_CFV_CFS:
	MOV32		R7H, *--SP

	LRETR










;================/ _add_CFV_CFV_CFS2 /==============
;12 + 31*N cycles
_add_CFV_CFV_CFS2:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer
	MOVL		XAR7, *-SP[6]		;load right-costant pointer
	MOVL		XAR0, *-SP[8]		;load left-costant pointer

;save context
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

	MOV32		R0H, *+XAR0[0]		;load ls_re
	MOV32		R1H, *+XAR0[2]		;load ls_im
	MOV32		R2H, *+XAR6[0]		;load rs_re
	MOV32		R3H, *+XAR6[2]		;load rs_im

	SUBB		AL, #1

;loop
	RPTB 		loop_add_CFV_CFV_CFS2, AL
;out_re part
	MOV32 		R4H, *+XAR5[0]		;R4H = lv_re
	MOV32 		R5H, *+XAR5[2]		;R5H = lv_im

	MOV32 		R6H, *+XAR6[0]		;R6H = rv_re
	MOV32 		R7H, *+XAR6[2]		;R7H = rv_im

	MPYF32		R4H, R4H, R0H		;lv_re * ls_re
	MPYF32		R5H, R5H, R1H		;lv_im * ls_im
	MPYF32		R6H, R6H, R2H		;rv_re * rs_re
	MPYF32		R7H, R7H, R3H		;rv_im * rs_im

	SUBF32		R4H, R4H, R5H		;left part
	SUBF32		R6H, R6H, R7H		;right part
	NOP
	ADDF32		R4H, R4H, R6H		;out_re
	NOP
	MOV32		*XAR4++, R4H		;store out_re

;out_im part
	MOV32 		R4H, *XAR5++		;R4H = lv_re
	MOV32 		R5H, *XAR5++		;R5H = lv_im

	MOV32 		R6H, *XAR6++		;R6H = rv_re
	MOV32 		R7H, *XAR6++		;R7H = rv_im

	MPYF32		R4H, R4H, R1H		;lv_re * ls_im
	MPYF32		R5H, R5H, R0H		;lv_im * ls_re
	MPYF32		R6H, R6H, R3H		;rv_re * rs_im
	MPYF32		R7H, R7H, R2H		;rv_im * rs_re

	ADDF32		R4H, R4H, R5H		;left part
	ADDF32		R6H, R6H, R7H		;right part
	NOP
	ADDF32		R4H, R4H, R7H		;out_im
	NOP
	MOV32		*XAR4++, R4H		;store out_im

loop_add_CFV_CFV_CFS2:

;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR











;================/ _add_CFV_CFV_FS2 /==============
;6 + 9*N cycles
_add_CFV_CFV_FS2:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer

;save context
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

	SUBB		AL, #1

;loop
	RPTB 		loop_add_CFV_CFV_FS2, AL

;out_im part
	MOV32 		R4H, *XAR5++		;R4H = lv_re
	MPYF32		R2H, R4H, R0H		;ls * lv_re
	||MOV32 	R5H, *XAR6++		;R5H = rv_re
	MPYF32		R3H, R5H, R1H		;rs * rv_re

	MOV32 		R4H, *XAR5++		;R4H = lv_im
	MPYF32		R6H, R4H, R0H		;ls * lv_im
	||MOV32 	R5H, *XAR6++		;R5H = rv_im
	MPYF32		R7H, R5H, R1H		;rs * rv_im

	ADDF32		R2H, R2H, R3H		;out_re
	ADDF32		R6H, R6H, R7H		;out_im

	MOV32		*XAR4++, R2H		;store out_re
	MOV32		*XAR4++, R6H		;store out_im

loop_add_CFV_CFV_FS2:

;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR















;******************************** Substruction functions ******************************

;================/ _sub_CFS_CFS /==============
;7 cycles
	.sect .text
_sub_CFS_CFS:

		MOV32 		R0H, *+XAR4[0]					;R0H = a_re
		MOV32 		R2H, *+XAR5[0]					;R2H = b_re

		SUBF32 		R0H, R0H, R2H					;R0H = a_re - b_re
		||MOV32 	R1H, *+XAR4[2]					;R1H = a_im

		MOV32 		R3H, *+XAR5[2]					;R3H = b_im
		SUBF32		R1H, R1H, R3H					;R1H = a_im - b_re

		MOV32 		*+XAR6[0], R0H					;store real part of return value
		MOV32 		*+XAR6[2], R1H					;store imag part of return value

	LRETR






;================/ _sub_CFV_CFV /==============
;4 + 9*N
	.sect .text
_sub_CFV_CFV:
	MOVL		XAR6, *-SP[4]		;load right-vector pointer

	MOV32 		R2H, *XAR6++		;load first right re
	MOV32 		R3H, *XAR6++		;load first right im

	SUBB		AL, #1
;loop
	RPTB 		loop_sub_CFV_CFV, AL
	MOV32		R0H, *XAR5++		;load  left re
	MOV32		R1H, *XAR5++		;load  left im

	SUBF32 		R0H, R0H, R2H		;y_re = re1 - re2
	||MOV32		R2H, *XAR6++		;load next right re
	SUBF32 		R1H, R1H, R3H		;y_im = im1 - im2
	||MOV32		R3H, *XAR6++		;load next right im

	MOV32		*XAR4++, R0H		;write y_re
	MOV32		*XAR4++, R1H		;write y_im
loop_sub_CFV_CFV:

	LRETR






























;******************************** Multiplication functions ******************************

;================/ _mul_CFS_CFS /==============
;10 cycles
	.sect .text
_mul_CFS_CFS:

	MOV32		*SP++, R4H

	MOV32 		R0H, *+XAR4[0]					;R0H = a_re
	MOV32 		R2H, *+XAR5[0]					;R2H = b_re

	MPYF32 		R3H, R0H, R2H					;R3H = a_re * b_re
	|| MOV32 	R1H, *+XAR4[2]					;R1H = a_im

	MPYF32		R2H, R1H, R2H					;R2H = a_im * b_re
	|| MOV32 	R4H, *+XAR5[2]					;R4H = b_im

	MPYF32 		R1H, R1H, R4H					;R1H = a_im * b_im
	MPYF32 		R0H, R0H, R4H					;R0H = a_re * b_im

	SUBF32 		R3H, R3H, R1H					;R3H = (a_re * b_re) - (a_im * b_im)
	ADDF32 		R2H, R2H, R0H					;R2H = (a_im * b_re) + (a_re * b_im)

	MOV32 		*+XAR6[0], R3H					;store real part of return value
	MOV32 		*+XAR6[2], R2H					;store imag part of return value

	MOV32		R7H, *--SP

	LRETR










;================/ _mul_CFS_cFS /==============
;10 cycles
	.sect .text
_mul_CFS_cFS:

	MOV32		*SP++, R4H

	MOV32 		R0H, *+XAR4[0]					;R0H = a_re
	MOV32 		R2H, *+XAR5[0]					;R2H = b_re

	MPYF32 		R3H, R0H, R2H					;R3H = a_re * b_re
	|| MOV32 	R1H, *+XAR4[2]					;R1H = a_im

	MPYF32		R2H, R1H, R2H					;R2H = a_im * b_re
	|| MOV32 	R4H, *+XAR5[2]					;R4H = b_im

	MPYF32 		R1H, R1H, R4H					;R1H = a_im * b_im
	MPYF32 		R0H, R0H, R4H					;R0H = a_re * b_im

	ADDF32 		R3H, R3H, R1H					;R3H = (a_re * b_re) + (a_im * b_im)
	SUBF32		R2H, R2H, R0H					;R2H = (a_im * b_re) - (a_re * b_im)

	MOV32 		*+XAR6[0], R3H					;store real part of return value
	MOV32 		*+XAR6[2], R2H					;store imag part of return value

	MOV32		R4H, *--SP

	LRETR








;================/ _mul_CFS_FS /==============
;5 cycles
	.sect .text
_mul_CFS_FS:
		MOV32 		R1H, *+XAR4[0]					;load lv_re
		MPYF32		R1H, R1H, R0H					;lv_re * r
		||MOV32 	R2H, *+XAR4[2]					;load lv_im
		MPYF32		R2H, R2H, R0H					;lv_im * r
		MOV32 		*+XAR6[0], R1H					;store real part of return value
		MOV32 		*+XAR6[2], R2H					;store imag part of return value
	LRETR







;================/ _mul_CFV_FS /==============
;3 + 7*N	cycles
	.text
_mul_CFV_FS:
	MOV32		*SP++, R4H
	.align 2
	SUBB		AL, #1

	MOV32 		R1H, *XAR5++		;load re[0]
	MOV32 		R2H, *XAR5++		;load im[0]

	RPTB 		loop_mul_CFV_FS, AL
	MPYF32 		R3H, R0H, R1H		;calc c * re[i]
	||MOV32		R1H, *XAR5++		;load re[i+1]
	MPYF32 		R4H, R0H, R2H		;calc c * r[i]
	||MOV32		R2H, *XAR5++		;load im[i+1]
	MOV32		*XAR4++, R3H		;write c * re[i]
	MOV32		*XAR4++, R4H		;write c * r[i]
loop_mul_CFV_FS:
	MOV32		R4H, *--SP

	LRETR









;================/ _mul_CFV_FV /==============
;9 + 8*N	cycles
	.sect .text
_mul_CFV_FV:

	MOVL		XAR6, *-SP[4]

	MOV32		*SP++, R4H

	MOV32		R0H, *XAR6++			;load w
	MOV32		R1H, *XAR5++			;load lv_re
	MOV32		R2H, *XAR5++			;load lv_im

	SUBB		AL, #1
;loop
	RPTB		loop_mul_CFV_FV, AL
	MPYF32		R3H, R1H, R0H			;calc lv_re * w
	||MOV32		R1H, *XAR5++			;load lv_re
	MPYF32		R4H, R2H, R0H			;calc lv_im * w
	||MOV32		R2H, *XAR5++			;load lv_im

	MOV32		*XAR4++, R3H
	MOV32		*XAR4++, R4H
	MOV32		R0H, *XAR6++			;load w
loop_mul_CFV_FV:
	MOV32		R4H, *--SP

	LRETR









;================/ _mul_CFV_CFV /==============
;12 + 9*N	cycles
	.sect .text
_mul_CFV_CFV:

	MOVL		XAR6, *-SP[4]
;save context
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H
;____
	MOV32		R0H, *XAR5++			;load lv_re
	MOV32		R1H, *XAR5++			;load lv_im
	MOV32		R2H, *XAR6++			;load rv_re
	MOV32		R3H, *XAR6++			;load rv_im
	MOV32		R7H, *--XAR4			;fictive load
	MOV32		R6H, *--XAR4			;fictive load

	SUBB		AL, #1
;loop
	RPTB		loop_mul_CFV_CFV, AL
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	||MOV32		*XAR4++, R6H			;write y_re
	MPYF32		R6H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		*XAR4++, R7H			;write y_im

	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im
	||MOV32		R0H, *XAR5++			;load lv_re
	MPYF32		R7H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR5++			;load lv_im

	SUBF32		R6H, R4H, R6H			;calc y_re = lv_re * rv_re - lv_im * rv_im
	||MOV32		R2H, *XAR6++			;load rv_re
	ADDF32		R7H, R5H, R7H			;calc y_im = lv_re * rv_im + lv_im * rv_re
	||MOV32		R3H, *XAR6++			;load rv_im
loop_mul_CFV_CFV:

	MOV32		*XAR4++, R6H			;write y_re
	MOV32		*XAR4++, R7H			;write y_im
;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
;____
	LRETR









;================/ _mul_CFV_cFV /==============
;12 + 9*N	cycles
	.sect .text
_mul_CFV_cFV:

	MOVL		XAR6, *-SP[4]
;save context
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H
;____
	MOV32		R0H, *XAR5++			;load lv_re
	MOV32		R1H, *XAR5++			;load lv_im
	MOV32		R2H, *XAR6++			;load rv_re
	MOV32		R3H, *XAR6++			;load rv_im
	MOV32		R7H, *--XAR4			;fictive load
	MOV32		R6H, *--XAR4			;fictive load

	SUBB		AL, #1
;loop
	RPTB		loop_mul_CFV_cFV, AL
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	||MOV32		*XAR4++, R6H			;write y_re
	MPYF32		R6H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		*XAR4++, R7H			;write y_im

	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im
	||MOV32		R0H, *XAR5++			;load lv_re
	MPYF32		R7H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR5++			;load lv_im

	ADDF32		R6H, R4H, R6H			;calc y_re = lv_re * rv_re + lv_im * rv_im
	||MOV32		R2H, *XAR6++			;load rv_re
	SUBF32		R7H, R5H, R7H			;calc y_im = lv_re * rv_im - lv_im * rv_re
	||MOV32		R3H, *XAR6++			;load rv_im
loop_mul_CFV_cFV:

	MOV32		*XAR4++, R6H			;write y_re
	MOV32		*XAR4++, R7H			;write y_im
;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR













;================/ _mul_CFV_CFS /==============
;12 + 9*N	cycles
	.sect .text
_mul_CFV_CFS:


	MOVL		XAR6, *-SP[4]
;save context
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H
;____

	MOV32		R0H, *XAR5++			;load lv_re
	MOV32		R1H, *XAR5++			;load lv_im
	MOV32		R2H, *XAR6++			;load rv_re
	MOV32		R3H, *XAR6++			;load rv_im
	MOV32		R7H, *--XAR4			;fictive load
	MOV32		R6H, *--XAR4			;fictive load

	SUBB		AL, #1
;loop
	RPTB		loop_mul_CFV_CFS, AL
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	||MOV32		*XAR4++, R6H			;write y_re
	MPYF32		R6H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		*XAR4++, R7H			;write y_im

	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im
	||MOV32		R0H, *XAR5++			;load lv_re
	MPYF32		R7H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR5++			;load lv_im

	SUBF32		R6H, R4H, R6H			;calc y_re = lv_re * rv_re - lv_im * rv_im
	ADDF32		R7H, R5H, R7H			;calc y_im = lv_re * rv_im + lv_im * rv_re
loop_mul_CFV_CFS:

	MOV32		*XAR4++, R6H			;write y_re
	MOV32		*XAR4++, R7H			;write y_im
;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
;____
	LRETR













;================/ _smul_CFV_CFV /==============
;21 + 11*N	cycles
	.sect .text
_smul_CFV_CFV:

	SUBB		AL, #1
	BF			return_smul_CFV_CFV, NC

	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

	ZERO		R6H
	ZERO		R7H

	MOV32		R0H, *XAR4++			;load lv_re
	MOV32		R1H, *XAR4++			;load lv_im
	MOV32		R2H, *XAR5++			;load rv_re
	MOV32		R3H, *XAR5++			;load rv_im

;loop
	RPTB		loop_smul_CFV_CFV, AL
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im

	ADDF32		R6H, R6H, R4H			;accum re
	ADDF32		R7H, R7H, R5H			;acuum im

	MPYF32		R4H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		R0H, *XAR4++			;load lv_re
	MPYF32		R5H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR4++			;load lv_im

	SUBF32		R6H, R6H, R4H
	||MOV32		R2H, *XAR5++			;load rv_re
	ADDF32		R7H, R7H, R5H
	||MOV32		R3H, *XAR5++			;load rv_im
loop_smul_CFV_CFV:

	MOV32		*+XAR6[0], R6H
	MOV32		*+XAR6[2], R7H

	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

return_smul_CFV_CFV:
    LRETR                                   ;return







;================/ _smul_CFV_cFV /==============
;21 + 11*N	cycles
	.sect .text
_smul_CFV_cFV:

	SUBB		AL, #1
	BF			return_smul_CFV_cFV, NC

	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

	ZERO		R6H
	ZERO		R7H

	MOV32		R0H, *XAR4++			;load lv_re
	MOV32		R1H, *XAR4++			;load lv_im
	MOV32		R2H, *XAR5++			;load rv_re
	MOV32		R3H, *XAR5++			;load rv_im

;loop
	RPTB		loop_smul_CFV_cFV, AL
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im

	ADDF32		R6H, R6H, R4H			;accum re
	SUBF32		R7H, R7H, R5H			;acuum im

	MPYF32		R4H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		R0H, *XAR4++			;load lv_re
	MPYF32		R5H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR4++			;load lv_im

	ADDF32		R6H, R6H, R4H
	||MOV32		R2H, *XAR5++			;load rv_re
	ADDF32		R7H, R7H, R5H
	||MOV32		R3H, *XAR5++			;load rv_im
loop_smul_CFV_cFV:

	MOV32		*+XAR6[0], R6H
	MOV32		*+XAR6[2], R7H

	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

return_smul_CFV_cFV:
    LRETR                                   ;return







































;******************************** Division functions ******************************


;================/ _div_CFS_CFS /==============
;40 cycles
_div_CFS_CFS:

	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H

	MOV32 		R2H, *+XAR5[0]					;R2H = b_re
	MPYF32		R5H, R2H, R2H					;R5H = b_re * b_re
	||MOV32 	R0H, *+XAR4[0]					;R0H = a_re

	MPYF32 		R3H, R0H, R2H					;R3H = a_re * b_re
	|| MOV32 	R1H, *+XAR4[2]					;R1H = a_im

	MPYF32		R2H, R1H, R2H					;R2H = a_im * b_re
	|| MOV32 	R4H, *+XAR5[2]					;R4H = b_im
	MPYF32		R6H, R4H, R4H					;R6H = b_im * b_im

	MPYF32 		R1H, R1H, R4H					;R1H = a_im * b_im
	MPYF32 		R0H, R0H, R4H					;R0H = a_re * b_im

	ADDF32 		R3H, R3H, R1H					;R3H = (a_re * b_re) + (a_im * b_im)
	SUBF32		R2H, R2H, R0H					;R2H = (a_im * b_re) - (a_re * b_im)
	MOV32		*SP++, R3H

	MOVF32		R0H, #1.0
	ADDF32		R1H, R6H, R5H					;R1H = b_re * b_re + b_im * b_im
	||MOV32		*SP++, R2H
	LCR			FS$$DIV

	MOV32		R2H, *--SP
	MPYF32		R2H, R2H, R0H
	||MOV32		R3H, *--SP
	MPYF32		R3H, R3H, R0H

	MOV32 		*+XAR6[2], R2H					;store imag part of return value
	MOV32 		*+XAR6[0], R3H					;store real part of return value

	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR








;================/ _div_CFV_CFV /==============
;12 + 31*N	cycles
	.sect .text
_div_CFV_CFV:

	MOVL		XAR6, *-SP[4]
;save context
	PUSH		XAR1
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H
;____
	MOV32		R0H, *XAR5++			;load lv_re
	MOV32		R1H, *XAR5++			;load lv_im
	MOV32		R2H, *XAR6++			;load rv_re
	MOV32		R3H, *XAR6++			;load rv_im
	MOV32		R7H, *--XAR4			;fictive load
	MOV32		R6H, *--XAR4			;fictive load

	SUBB		AL, #1
	MOVZ		AR1, AL
loop_div_CFV_CFV:
	MPYF32		R4H, R0H, R2H			;calc lv_re * rv_re
	||MOV32		*XAR4++, R6H			;write y_re
	MPYF32		R6H, R1H, R3H			;calc lv_im * rv_im
	||MOV32		*XAR4++, R7H			;write y_im

	MPYF32		R5H, R0H, R3H			;calc lv_re * rv_im
	||MOV32		R0H, *XAR5++			;load lv_re
	MPYF32		R7H, R1H, R2H			;calc lv_im * rv_re
	||MOV32		R1H, *XAR5++			;load lv_im

	MPYF32		R2H, R2H, R2H
	||ADDF32	R6H, R4H, R6H			;calc y_re = lv_re * rv_re - lv_im * rv_im
	MPYF32		R3H, R3H, R3H
	SUBF32		R7H, R7H, R5H 			;calc y_im = lv_im * rv_re - lv_re * rv_im
	MOVF32		R0H, #1.0
	ADDF32		R1H, R2H, R3H

	LCR			FS$$DIV

	MPYF32		R6H, R6H, R0H
	||MOV32		R2H, *XAR6++			;load rv_re
	MPYF32		R7H, R7H, R0H
	||MOV32		R3H, *XAR6++			;load rv_im

	BANZ		loop_div_CFV_CFV, AR1--	;loop


	MOV32		*XAR4++, R6H			;write y_re
	MOV32		*XAR4++, R7H			;write y_im

;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
	POP			XAR1
;____
	LRETR











;================/ _inv_CFV /==============
;10 + 29*N	cycles
	.sect .text
_inv_CFV:

	MOVL		XAR6, *-SP[4]
;save context
	PUSH		XAR1
	MOV32		*SP++, R4H
;____

	MOV32		R3H, *XAR5++			;load lv_re
	MOV32		R4H, *XAR5++			;load lv_im
	MOVF32		R0H, #1.0
	SUBB		AL, #1
	MOVZ		AR1, AL
;loop
loop_inv_CFV:
	MPYF32		R1H, R3H, R3H
	MPYF32		R2H, R4H, R4H
	NEGF32		R4H, R4H
	ADDF32		R1H, R1H, R2H
	LCR			FS$$DIV
	MPYF32		R1H, R3H, R0H
	||MOV32		R3H, *XAR5++			;load lv_re
	MPYF32		R2H, R4H, R0H
	||MOV32		R4H, *XAR5++			;load lv_im
	MOV32		*XAR4++, R1H
	MOV32		*XAR4++, R2H
	BANZ		loop_inv_CFV, AR1--		;loop

;restore context
	POP			XAR1
	MOV32		R4H, *--SP
;____
	LRETR













;================/ _sum_CFV /==============
;19 + 6*N cycles
	.sect .text
_sum_CFV:

	MOV32		*SP++, R7H	;save
	MOV32		*SP++, R6H	;save

	MOVL		XAR7, XAR4

	MOVF32		R0H, #1.0
	MOVZ		AR4, SP
	ADDB		SP, #2		;alloc stack
	MOV32		*XAR4, R0H

	ZERO		R2H
	ZERO		R3H
	ZERO		R6H
	ZERO		R7H

	LSL			AL, 1
	SUBB		AL, #1
	RPT			AL
	||MACF32	R7H, R3H, *XAR4, *XAR7++

	ADDB		SP, #-2			;free stack

	ADDF32		R3H, R3H, R2H
	||MOV32		R6H, *--SP		;restore
	ADDF32		R7H, R7H, R6H
	MOV32		*+XAR6[0], R3H
	MOV32		*+XAR6[2], R7H

	MOV32		R7H, *--SP		;restore

	LRETR





















;================/ _abs_CFV /==============
;6 + 28*N cycles
	.sect .text
_abs_CFV:

	PUSH		XAR1

	SUBB		AL, #1
	MOVZ		AR1, AL

	MOV32		R0H, *XAR5++
	MOV32		R1H, *XAR5++

loop_abs_CFV:
	MPYF32		R2H, R0H, R0H
	||MOV32		R0H, *XAR5++
	MPYF32		R3H, R1H, R1H
	MOV32		R1H, *XAR5++
	ADDF32		R0H, R2H, R3H
	LCR			_sqrtf
	MOV32		*XAR4++, R0H
	BANZ		loop_abs_CFV, AR1--

	POP			XAR1

	LRETR





;================/ _abs2_CFV /==============
; EVEN 10 + 6*N cycles
; ODD 7 + 6*N cycles
	.sect .text
_abs2_CFV:

	TBIT		AL, #0
	BF			doubleloop_abs2_CFV, NTC

	MOV32		R0H, *XAR5++		;load re[0]
	MPYF32 		R0H, R0H, R0H		;calc re[0]^2
	||MOV32 	R1H, *XAR5++		;load im[0]
	MPYF32 		R1H, R1H, R1H		;calc im[0]^2
	NOP
	ADDF32		R0H, R0H, R1H		;calc sqr[0] = re[0]^2 + im[0]^2
	NOP
	MOV32		*XAR4++, R0H		;write sqr[0]

doubleloop_abs2_CFV:

	LSR 		AL, #1
	BF			return_abs2_CFV, EQ
	SUBB		AL, #1

	RPTB 		loop_abs2_CFV, AL
	MOV32		R0H, *XAR5++		;load re[0]
	MPYF32 		R0H, R0H, R0H		;calc re[0]^2
	||MOV32 	R1H, *XAR5++		;load im[0]
	MPYF32 		R1H, R1H, R1H		;calc im[0]^2
	||MOV32 	R2H, *XAR5++		;load re[1]
	MPYF32 		R2H, R2H, R2H		;calc re[1]^2
	||MOV32 	R3H, *XAR5++		;load im[1]
	MPYF32 		R3H, R3H, R3H		;calc im[1]^2

	ADDF32		R0H, R0H, R1H		;calc sqr[0] = re[0]^2 + im[0]^2
	ADDF32		R2H, R2H, R3H		;calc sqr[1] = re[1]^2 + im[1]^2

	MOV32		*XAR4++, R0H		;write sqr[0]
	MOV32		*XAR4++, R2H		;write sqr[1]
loop_abs2_CFV:

return_abs2_CFV:

	LRETR























;================/ _conjugate_CFS /==============
; 3 cycles
	.sect .text
_conjugate_CFS:
	MOV32			R0H, *+XAR4[2]
	NEGF32			R0H, R0H
	MOV32			*+XAR6[2], R0H
	LRETR



;================/ _conjugate_CFV /==============
; 1 + 8*N cycles
	.sect .text
_conjugate_CFV:
	SUBB			AL, #1
	.align 2
;loop
	RPTB			loop_conjugate_CFV, AL
	MOV32			R0H, *XAR5++
	MOV32			R1H, *XAR5++
	NEGF32			R1H, R1H
	MOV32			*XAR4++, R0H
	MOV32			*XAR4++, R1H
loop_conjugate_CFV:

	LRETR



























;================/ _mag_CFS /==============
; 25 cycles
	.sect .text
_mag_CFS:
	MOV32			R1H, *+XAR4[0]
	MPYF32			R1H, R1H, R1H
	||MOV32			R2H, *+XAR4[2]
	MPYF32			R2H, R2H, R2H
	NOP
	ADDF32			R0H, R1H, R2H
	LCR				_sqrtf
	LRETR


;================/ _mag2_CFS /==============
; 5 cycles
	.sect .text
_mag2_CFS:
	MOV32			R0H, *+XAR4[0]
	MPYF32			R0H, R0H, R0H
	||MOV32			R1H, *+XAR4[2]
	MPYF32			R1H, R1H, R1H
	NOP
	ADDF32			R0H, R0H, R1H
	LRETR


;================/ _mag_CFV /==============
;6 + 28*N cycles
	.sect .text
_mag_CFV:
	LCR				_abs_CFV
	LRETR



;================/ _phase_CFS /==============
; * cycles
_phase_CFS:
	.sect .text
	MOV32		R0H, *+XAR4[2]
	MOV32		R1H, *+XAR4[0]
	LCR			_atan2f
	LRETR


;================/ _phase_CFV /==============
; * cycles
	.sect .text
_phase_CFV:
	PUSH		XAR1

	SUBB		AL, #1
	MOVZ		AR1, AL

loop_phase_CFV:
	MOV32		R1H, *XAR5++
	MOV32		R0H, *XAR5++
	LCR			_atan2f
	MOV32		*XAR4++, R0H
	BANZ		loop_phase_CFV, AR1--

	POP			XAR1

	LRETR










;================/ _max_CFV /==============
;20 + 11*N
	.sect .text
_max_CFV:
;Start with x[0] as the assumed max

	MOV32		*SP++, R4H			;save register
	MOVL		XAR6, XAR5
	MOV32 		R0H, *XAR5++		;R0H = x[0] (initial max is first element in x[])
	MPYF32		R4H, R0H, R0H
	||MOV32		R0H, *XAR5++
	MPYF32		R0H, R0H, R0H
	ZERO 		R2H					;R2H = 0.0 (initial index is 0)
	ADDF32		R0H, R0H, R4H

	ZERO 		R3H					;R3H = 0.0 (index candidate)

	SUBB 		AL, #1				;Subtract 1 from N since RPTB is 'n-1' times

;main cycle
	RPTB 		loop_max_CFV, AL
	ADDF32		R2H, R2H, #1.0
	MOV32 		R1H, *XAR5++
	MPYF32		R4H, R1H, R1H
	||MOV32		R1H, *XAR5++
	MPYF32		R1H, R1H, R1H
	NOP
	ADDF32		R1H, R1H, R4H
	NOP
	MAXF32 		R0H, R1H					;if max < max_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R3H, R2H					;if R0H < R1H, then R0H=R1H and R3H=R2H
loop_max_CFV:

;Prepare the return value
	F32TOUI16 	R3H, R3H					;convert index from float32 to Uint16
	MOV32		R4H, *--SP					;restore register
	MOV			T, #2
	MOV32 		ACC, R3H
	LSLL		ACC, T
	ADDL		ACC, XAR6
	MOVL		XAR6, ACC
	MOVL		ACC, *XAR6++
	MOVL		*XAR4++, ACC
	MOVL		ACC, *XAR6++
	MOVL		*XAR4++, ACC

;Finish up
	LRETR									;return







;================/ _min_CFS /==============
;20
	.sect .text
_min_CFS:
	MOV32		R0H, *+XAR4[0]
	MPYF32		R0H, R0H,R0H
	||MOV32		R1H, *+XAR4[2]
	MPYF32		R1H, R1H,R1H

	||MOV32		R2H, *+XAR5[0]
	MPYF32		R2H, R2H,R2H
	||MOV32		R3H, *+XAR5[2]
	MPYF32		R3H, R3H,R3H
	ADDF32		R0H, R0H, R1H
	ADDF32		R1H, R2H, R3H
	NOP
	SUBF32		R0H,R0H,R1H

	MOVST0		ZF,NF
	BF			ret2_min_CFS, GT
	MOVL		XAR7, XAR4
ret2_min_CFS:
	MOVL		XAR7, XAR5

	RPT 		#3
	||PREAD		*XAR6++, *XAR7
	LRETR




;================/ _max_CFS /==============
;20 + 11*N
	.sect .text
_max_CFS:
	MOV32		R0H, *+XAR4[0]
	MPYF32		R0H, R0H,R0H
	||MOV32		R1H, *+XAR4[2]
	MPYF32		R1H, R1H,R1H

	||MOV32		R2H, *+XAR5[0]
	MPYF32		R2H, R2H,R2H
	||MOV32		R3H, *+XAR5[2]
	MPYF32		R3H, R3H,R3H
	ADDF32		R0H, R0H, R1H
	ADDF32		R1H, R2H, R3H
	NOP
	SUBF32		R0H,R0H,R1H

	MOVST0		ZF,NF
	BF			ret2_max_CFS, LT
	MOVL		XAR7, XAR4
ret2_max_CFS:
	MOVL		XAR7, XAR5

	RPT 		#3
	||PREAD		*XAR6++, *XAR7
	LRETR



;================/ _min_CFV /==============
;20 + 11*N
	.sect .text
_min_CFV:
;Start with x[0] as the assumed max

	MOV32		*SP++, R4H			;save register
	MOVL		XAR6, XAR5
	MOV32 		R0H, *XAR5++		;R0H = x[0] (initial max is first element in x[])
	MPYF32		R4H, R0H, R0H
	||MOV32		R0H, *XAR5++
	MPYF32		R0H, R0H, R0H
	ZERO 		R2H					;R2H = 0.0 (initial index is 0)
	ADDF32		R0H, R0H, R4H

	ZERO 		R3H					;R3H = 0.0 (index candidate)

	SUBB 		AL, #1				;Subtract 1 from N since RPTB is 'n-1' times

;main cycle
	RPTB 		loop_min_CFV, AL
	ADDF32		R2H, R2H, #1.0
	MOV32 		R1H, *XAR5++
	MPYF32		R4H, R1H, R1H
	||MOV32		R1H, *XAR5++
	MPYF32		R1H, R1H, R1H
	NOP
	ADDF32		R1H, R1H, R4H
	NOP
	MINF32 		R0H, R1H					;if max < max_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R3H, R2H					;if R0H < R1H, then R0H=R1H and R3H=R2H
loop_min_CFV:

;Prepare the return value
	F32TOUI16 	R3H, R3H					;convert index from float32 to Uint16
	MOV32		R4H, *--SP					;restore register
	MOV			T, #2
	MOV32 		ACC, R3H
	LSLL		ACC, T
	ADDL		ACC, XAR6
	MOVL		XAR6, ACC
	MOVL		ACC, *XAR6++
	MOVL		*XAR4++, ACC
	MOVL		ACC, *XAR6++
	MOVL		*XAR4++, ACC

;Finish up
	LRETR									;return














;================/ _mean_CFV /==============
; 43 + 6*N cycles
	.sect .text
_mean_CFV:
	MOV				AH, #0
	PUSH			ACC
	MOV32			R1H, *--SP
	UI16TOF32		R1H, R1H
	MOVF32			R0H, #1.0
	LCR				FS$$DIV
	MOV32			R1H, R0H
	LCR				_sum_CFV
	MPYF32			R0H, R0H, R1H
	LRETR












;================/ _conv_circle_CFV /==============
;20 + (12 + 3*K) * N
_conv_circle_CFV:
;XAR4 - output data
;XAR6 - input data
;XAR7 - kernel
;AR1 - circle index
;AR1H - n-1
;AH - RPT param

;save context
	PUSH		XAR1
	MOV32		*SP++, R6H
	MOV32		*SP++, R7H

	MOVL		XAR6, XAR5		;load iv ptr

;construct circle indexer
	MOVL		XAR0, ACC
	MOV			AH, AL
	SUBB		AH, #1
	LSL			AH, 2
	MOV			AL, #0
	MOVL		XAR1, ACC
	MOVL		XAR5, XAR1
	MOVL		ACC, XAR0

	SUBB		AL, #1			;dec value for main cycle
	SUBB		AH, #1			;dec value for convolve cycle

	ZEROA						;
	MOV32		R0H, *-SP[10]	;load kern ptr

	.lp_amode
	SETC		AMODE

	MOVZ		AR0, AL
mainloop_conv_circle_CFV:
	MOV32		XAR7, R0H	;load kern ptr

	ZERO		R6H
	ZERO		R7H

	MOV32		R0H, *+XAR6[AR1%++]		;load input_re
	MOV32		R1H, *+XAR6[AR1%++]		;load input_im

	MOV32		R2H, *XAR7++			;load w_re
	MOV32		R3H, *XAR7++			;load w_im

;conv cycle
	RPTB		convloop_conv_circle_CFV, AH

	MPYF32		R4H, R0H, R2H		;calc x_re * w_re
	MPYF32		R5H, R1H, R2H		;calc x_im * w_re
	||MOV32		R2H, *XAR7++		;load next w_re

	ADDF32		R6H, R6H, R4H		;accum re += x_re * w_re

	MPYF32		R4H, R1H, R3H		;calc x_im * w_im
	||ADDF32	R7H, R7H, R5H		;accum im += x_im * w_re
	MPYF32		R5H, R0H, R3H		;calc x_re * w_im
	||MOV32		R3H, *XAR7++		;load next w_im

	SUBF32		R6H, R6H, R4H		;accum re -= x_im * w_im
	||MOV32		R0H, *+XAR6[AR1%++]	;load next x_re
	ADDF32		R7H, R7H, R5H		;accum im += x_re * w_im
	||MOV32		R1H, *+XAR6[AR1%++]	;load next x_im
convloop_conv_circle_CFV:
;---

	ADDB		XAR5, #4
	MOVL		XAR1, XAR5
	MOV32		*XAR4++, R6H
	MOV32		*XAR4++, R7H

	BANZ		mainloop_conv_circle_CFV, AR0--
;---

	.c28_amode
	CLRC		AMODE

	MOV32		R1H, *--SP
;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	POP			XAR1

	LRETR
















;================/ _traverse_CFV /==============
;14 + (11 + func) * N  cycles
	.sect .text
_traverse_CFV:

	PUSH	XAR1
	PUSH	XAR2
	PUSH	XAR3

	MOVL	XAR2, XAR4
	MOVL	XAR3, XAR5

	SUBB	AL, #1
	MOVZ	AR1, AL
loop_traverse_CFV:
	MOVL	XAR4, XAR3
	MOVL	XAR6, XAR2
	MOVL	XAR7, *-SP[10]
	LCR		*XAR7
	ADDB	XAR2, #4
	ADDB	XAR3, #4
	BANZ	loop_traverse_CFV, AR1--

	POP		XAR3
	POP		XAR2
	POP		XAR1

return_traverse_CFV:
	LRETR





;================/ _traverse_CFV_CFV /==============
;14 + (14 + func) * N  cycles
	.sect .text
_traverse_CFV_CFV:


;save context
	PUSH	XAR1
	PUSH	XAR2
	PUSH	XAR3
	PUSH	XAR4

	MOVL	XAR2, XAR5		;load x1 ptr
	MOVL	XAR3, *-SP[12]	;load x2 ptr

	SUBB	AL, #1
	MOV		AR1, AL

loop_traverse_CFV_CFV:
	MOVL	XAR4, XAR2
	MOVL	XAR5, XAR3
	MOVL	XAR6, *-SP[2]
	MOVL	XAR7, *-SP[14]	;load function ptr
	LCR		*XAR7			;call function
	ADDB	XAR2, #4
	ADDB	XAR3, #4
	ADDB	XAR6, #4
	MOVL	*-SP[2], XAR6
	BANZ	loop_traverse_CFV_CFV, AR1--

;restore context
	POP		XAR4
	POP		XAR3
	POP		XAR2
	POP		XAR1

return_traverse_CFV_CFV:
	LRETR
