

	.global _fill_FV

	.global _add_FV_FS
	.global _add_FV_FV
	.global _add_FV_FV_FS
	.global _add_FV_FV_FS2

	.global _sub_FV_FV

	.global _mul_FV_FV
	.global _mul_FV_FS
	.global _smul_FV_FV

	.global _div_FV_FV
	.global _inv_FV

	.global _sum_FV

	.global _abs_FV
	.global _abs2_FV

	.global _norm_euclid_FV
	.global _norm_manh_FV

	.global _dist_euclid_FV
	.global _dist_manh_FV

	.global _normalize_FV

	.global _max_FV
	.global _min_FV
	.global _max_FV_FV
	.global _min_FV_FV
	.global _constrain_FS
	.global _constrain_FV

	.global _mean_FV
	.global _mean2_FV
	.global _mean3_FV

	.global _conv_circle_FV
;	.global _circ_shift_FV

	.global _horner_FV

	.global _traverse_FV
	.global _traverse_FV_FV






	.ref     	FS$$DIV
	.ref     	_sqrtf
	
	


;================/ _fill_FV /==============
;2 + 5*N
	.sect .text
_fill_FV:
	SUBB		AL, #1
	MOVZ		AR0, AL

loop_fill_FV:
	MOV32		*XAR4++, R0H
	BANZ		loop_fill_FV, AR0--

	LRETR





;================/ _add_FV_FS /==============
;14 + 9*N/2		if N is EVEN
;20 + 9*N/2   	if N is ODD
	.sect .text
_add_FV_FS:

	TBIT		AL, #0
	BF			doubleloop_add_FV_FS, NTC

	MOV32		R1H, *XAR5++		;load r[0]
	ADDF32 		R1H, R1H, R0H		;calc r[0] + с
	NOP
	MOV32		*XAR4++, R1H		;write res


doubleloop_add_FV_FS:

	LSR 		AL, #1
	BF			return_add_FV_FS, EQ
	SUBB		AL, #1

	MOV32		R1H, *XAR5++		;load r[0]

	.align 2
	NOP
	RPTB 		loop_add_FV_FS, AL
	ADDF32 		R2H, R1H, R0H		;calc r[0] + с
	||MOV32		R1H, *XAR5++		;load r[0]
	ADDF32 		R3H, R1H, R0H		;calc r[0] + с
	||MOV32		R1H, *XAR5++		;load r[0]
	MOV32		*XAR4++, R2H		;write res
	MOV32		*XAR4++, R3H		;write res
loop_add_FV_FS:

return_add_FV_FS:

	LRETR









;================/ _add_FV_FV /==============
;14 + 9*N/2		if N is EVEN
;20 + 9*N/2   	if N is ODD
_add_FV_FV:

	MOVL		XAR6, *-SP[4]

	TBIT		AL, #0
	BF			doubleloop_add_FV_FV, NTC

	MOV32		R0H, *XAR5++		;load re1[0]
	MOV32 		R1H, *XAR6++		;load re2[0]
	ADDF32 		R0H, R0H, R1H		;calc re1[0] * re2[0]
	NOP
	MOV32		*XAR4++, R0H		;write re[0] * re[1]


doubleloop_add_FV_FV:

	LSR 		AL, #1
	BF			return_add_FV_FV, EQ
	SUBB		AL, #1

	MOV32		R0H, *XAR5++		;load first re1
	MOV32 		R1H, *XAR6++		;load first re2

	RPTB 		loop_add_FV_FV, AL
	ADDF32 		R2H, R0H, R1H		;y[i] = re1[i] + re2[i]
	|| MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]

	ADDF32 		R2H, R0H, R1H		;y[i] = re1[i] + re2[i]
	|| MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]
loop_add_FV_FV:

return_add_FV_FV:

	LRETR








;================/ _add_FV_FV_FS /==============
;14 + 9*N/2		if N is EVEN
;20 + 9*N/2   	if N is ODD
_add_FV_FV_FS:

	MOVL		XAR6, *-SP[4]

	MOV32		*SP++, R4H

	TBIT		AL, #0
	BF			doubleloop_add_FV_FV_FS, NTC

	MOV32		R2H, *XAR6++

	MPYF32		R2H, R2H, R0H
	MOV32		R1H, *XAR5++
	ADDF32		R1H, R1H, R2H
	NOP
	MOV32		*XAR4++, R1H			; save y[0]


doubleloop_add_FV_FV_FS:
	MOV32		R2H, *XAR6++
	MOV32		R4H, *XAR6++

	RPTB 		loop_add_FV_FV_FS, AL
	MPYF32		R2H, R2H, R0H			; rv[i] * rs
	||MOV32		R1H, *XAR5++			; load lv[i]
	MPYF32		R4H, R4H, R0H			; rv[i+1] * rs
	||MOV32		R3H, *XAR5++			; load lv[i+1]
	ADDF32		R1H, R1H, R2H			; y[i] = lv[i] + rv[i] * rs
	||MOV32		R2H, *XAR6++			; load rv[i+2]
	ADDF32		R3H, R3H, R4H			; y[i+1] = lv[i+1] + rv[i+1] * rs
	||MOV32		R4H, *XAR6++			; load rv[i+3]

	MOV32		*XAR4++, R1H			; save y[i]
	MOV32		*XAR4++, R3H			; save y[i+1]
loop_add_FV_FV_FS:

	MOV32		R4H, *--SP

	LRETR








;================/ _add_FV_FV_FS2 /==============
;8 + 12*N/2		if N is EVEN
;14 + 12*N/2   	if N is ODD
_add_FV_FV_FS2:

	MOVL		XAR6, *-SP[4]

	MOV32		*SP++, R4H
	MOV32		*SP++, R5H

	TBIT		AL, #0
	BF			doubleloop_add_FV_FV_FS2, NTC

	MOV32		R2H, *XAR5++
	MOV32		R3H, *XAR6++
	MPYF32		R2H, R2H, R0H
	MPYF32		R3H, R3H, R1H
	NOP
	ADDF32		R2H, R2H, R3H
	NOP
	MOV32		*XAR4++, R2H			; save y[0]


doubleloop_add_FV_FV_FS2:

	LSR 		AL, #1
	BF			return_add_FV_FV_FS2, EQ
	SUBB		AL, #1

	MOV32		R2H, *XAR5++			; load lv[i]
	MOV32		R3H, *XAR6++			; load rv[i]

	RPTB 		loop_add_FV_FV_FS2, AL	
	MPYF32		R2H, R2H, R0H			; lv[i] * ls
	||MOV32		R4H, *XAR5++			; load lv[i+1]
	MPYF32		R3H, R3H, R1H			; rv[i] * rs
	MOV32		R5H, *XAR6++			; load rv[i+1]
	
	MPYF32		R4H, R4H, R0H			; lv[i+1] * ls
	||ADDF32	R2H, R2H, R3H			; y[i] = lv[i] * ls + rv[i] * rs
	MPYF32		R5H, R5H, R1H			; rv[i+1] * rs
	MOV32		*XAR4++, R2H			; save y[i]

	ADDF32		R4H, R4H, R5H			; lv[i] * ls + rv[i] * rs	
	||MOV32		R2H, *XAR5++			; load lv[i+2]
	MOV32		R3H, *XAR6++			; load rv[i+2]
	
	MOV32		*XAR4++, R4H			; save y[i+1]
	
loop_add_FV_FV_FS2:

	MOV32		R5H, *--SP
	MOV32		R4H, *--SP
return_add_FV_FV_FS2:
	LRETR


















;**************************** Substruction reals ***************************

;================/ _sub_FV_FV /==============
;14 + 9*N/2		if N is EVEN
;20 + 9*N/2   	if N is ODD
_sub_FV_FV:

	MOVL		XAR6, *-SP[4]

	TBIT		AL, #0
	BF			doubleloop_sub_FV_FV, NTC

	MOV32		R0H, *XAR5++		;load re1[0]
	MOV32 		R1H, *XAR6++		;load re2[0]
	SUBF32 		R0H, R0H, R1H		;calc re1[0] * re2[0]
	NOP
	MOV32		*XAR4++, R0H		;write re[0] * re[1]


doubleloop_sub_FV_FV:

	LSR 		AL, #1
	BF			return_sub_FV_FV, EQ
	SUBB		AL, #1

	MOV32		R0H, *XAR5++		;load first re1
	MOV32 		R1H, *XAR6++		;load first re2

	RPTB 		loop_sub_FV_FV, AL
	SUBF32 		R2H, R0H, R1H		;y[i] = re1[i] + re2[i]
	||MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]

	SUBF32 		R2H, R0H, R1H		;y[i] = re1[i] + re2[i]
	||MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]
loop_sub_FV_FV:

return_sub_FV_FV:

	LRETR
































;**************************** Multiplication reals ***************************

;================/ _mul_FV_FS /==============
;14 + 7*N/2		if N is EVEN
;20 + 7*N/2   	if N is ODD
	.text
_mul_FV_FS:

	TBIT		AL, #0
	BF			doubleloop_mul_FV_FS, NTC

	MOV32 		R1H, *XAR5++		;load r[0]
	MPYF32 		R1H, R1H, R0H		;calc c * r[0]
	NOP
	MOV32		*XAR4++, R1H		;write c * r[0]

	.align 2
doubleloop_mul_FV_FS:

	LSR 		AL, #1
	BF			return_mul_FV_FS, EQ
	SUBB		AL, #1

	MOV32 		R1H, *XAR5++		;load r[i]
	MOV32 		R2H, *XAR5++		;load r[i]

;loop
	RPTB 		loop_mul_FV_FS, AL
	MPYF32 		R3H, R0H, R1H		;calc c * r[i]
	||MOV32		R1H, *XAR5++		;load r[i+1]
	MPYF32 		R4H, R0H, R2H		;calc c * r[i]
	||MOV32		R2H, *XAR5++		;load r[i+1]
	MOV32		*XAR4++, R3H		;load r[i+1]
	MOV32		*XAR4++, R4H		;write re[0] * re[1]
loop_mul_FV_FS:

return_mul_FV_FS:


	LRETR










;================/ _mul_FV_FV /==============
;11 + 9*N/2   	if N is EVEN
;14 + 9*N/2		if N is ODD
_mul_FV_FV:

	MOVL		XAR6, *-SP[4]

	TBIT		AL, #0
	BF			doubleloop_mul_FV_FV, NTC

	MOV32		R0H, *XAR5++		;load re1[0]
	MOV32 		R1H, *XAR6++		;load re2[0]
	MPYF32 		R0H, R0H, R1H		;calc re1[0] * re2[0]
	NOP
	MOV32		*XAR4++, R0H		;write re[0] * re[1]


doubleloop_mul_FV_FV:

	LSR 		AL, #1
	BF			return_mul_FV_FV, EQ
	SUBB		AL, #1

	MOV32		R0H, *XAR5++		;load first re1
	MOV32 		R1H, *XAR6++		;load first re2
;loop
	RPTB 		loop_mul_FV_FV, AL
	MPYF32 		R2H, R0H, R1H		;y[i] = re1[i]*re2[i]
	|| MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]

	MPYF32 		R2H, R0H, R1H		;y[i] = re1[i]*re2[i]
	|| MOV32 	R0H, *XAR5++		;load next re1
	MOV32		R1H, *XAR6++		;load next re2
	MOV32		*XAR4++, R2H		;store y[i]
loop_mul_FV_FV:


return_mul_FV_FV:
	LRETR












;================/ _smul_FV_FV /==============
;14 + 3*N cycles
	.sect .text
_smul_FV_FV:

	MOV32       *SP++,R7H		;Save R7H (save-on-entry register)
    MOV32       *SP++,R6H		;Save R6H (save-on-entry register)

    ZERO        R2H				;Zero R3H
    ZERO        R3H				;Zero R7H
    ZERO        R6H				;Zero R3H
    ZERO        R7H				;Zero R7H

	SUBB		AL, #1			;calc N-1
	MOVL		XAR7, XAR5		;load real2

	RPT			AL
	||MACF32	R7H, R3H, *XAR4++, *XAR7++

	ADDF32		R0H, R2H, R3H
	ADDF32		R7H, R7H, R6H
    MOV32    	R6H,*--SP                   ;Restore R6H
	ADDF32		R0H, R0H, R7H
    MOV32       R7H,*--SP                   ;Restore R7H

    LRETR                                   ;return































;**************************** Division reals ***************************

;================/ _div_FV_FV /==============
; 3 + (8 + FS$$DIV) * N
	.text
_div_FV_FV:

	SUBB		AL, #1
	MOVL		XAR6, *-SP[4]
	PUSH		XAR1
	MOVZ		AR1, AL

loop_div_FV_FV:
	MOV32		R0H, *XAR5++
	MOV32		R1H, *XAR6++
	LCR			FS$$DIV
	MOV32		*XAR4++, R0H
	BANZ		loop_div_FV_FV, AR1--

	POP			XAR1
	LRETR





;================/ _inv_FV /==============
; 7 + 28 * N
	.text
_inv_FV:

	PUSH		XAR1
	SUBB		AL, #1
	MOVZ		AR1, AL
	MOVF32		R0H, #1.0
	MOV32		*SP++, R0H

loop_inv_FV:
	MOV32		R0H, *-SP[2]
	MOV32		R1H, *XAR5++
	LCR			FS$$DIV
	MOV32		*XAR4++, R0H
	BANZ		loop_inv_FV, AR1--

	MOV32		R0H, *--SP
	POP			XAR1
	LRETR























;================/ _sum_FV /==============
;13 + 3*N cycles
	.sect .text
_sum_FV:

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

	SUBB		AL, #1
	RPT			AL
	||MACF32	R7H, R3H, *XAR4, *XAR7++

	ADDB		SP, #-2			;free stack

	ADDF32		R3H, R3H, R2H
	ADDF32		R7H, R7H, R6H
	MOV32		R6H, *--SP		;restore
	ADDF32		R0H, R3H, R7H
	MOV32		R7H, *--SP		;restore

	LRETR













































;================/ _abs_FV /==============
;7 + 9*N/2		if N is EVEN
;10 + 9*N/2   	if N is ODD
	.sect .text
_abs_FV:

	TBIT		AL, #0
	BF			doubleloop_abs_FV, NTC

	MOV32		R0H, *XAR4++
	ABSF32		R0H, R0H
	MOV32 		*XAR5++, R0H


doubleloop_abs_FV:

	LSR			AL, #1
	BF			return_abs_FV, EQ
	SUBB		AL, #1

;__loop
	RPTB		loop_abs_FV, AL
	MOV32		R0H, *XAR4++
	ABSF32		R0H, R0H
	MOV32 		*XAR5++, R0H
	MOV32		R0H, *XAR4++
	ABSF32		R0H, R0H
	MOV32 		*XAR5++, R0H
loop_abs_FV:

return_abs_FV:
	LRETR



















;================/ _abs2_FV /==============
;12 + 9*N/2   	if N is ODD
;8 + 9*N/2		if N is EVEN
	.sect .text
_abs2_FV:

	TBIT		AL, #0
	BF			doubleloop_abs2_FV, NTC

	MOV32		R0H, *XAR5++		;load x
	MPYF32 		R0H, R0H, R0H		;calc x^2
	NOP
	MOV32		*XAR4++, R0H		;write x^2

doubleloop_abs2_FV:

	LSR 		AL, #1
	BF			return_abs2_FV, EQ
	SUBB		AL, #1

	RPTB 		loop_abs2_FV, AL

	MOV32		R0H, *XAR5++		;load x
	MOV32		R1H, *XAR5++		;load x
	MPYF32 		R0H, R1H, R1H		;calc x^2
	MPYF32 		R1H, R1H, R1H		;calc x^2
	MOV32		*XAR4++, R0H		;write x^2
	MOV32		*XAR4++, R1H		;write x^2

loop_abs2_FV:
return_abs2_FV:

	LRETR









;================/ _norm_euclid_FV /==============
;2 + _smul_FV_FV + _sqrtf
	.sect .text
_norm_euclid_FV:
	
	PUSH	XAR4
	POP		XAR5
	
	LCR		_smul_FV_FV
	LCR		_sqrtf
	
	LRETR
	




;================/ _norm_manh_FV /==============
;9 + 9*N/2		if N is EVEN
;11 + 9*N/2   	if N is ODD
	.sect .text
_norm_manh_FV:
	
	TBIT		AL, #0
	BF			doubleloop_norm_manh_FV, NTC

	MOV32		R1H, *XAR4++		; load iv[0]
	ABSF32		R0H, R1H			; |iv[0]|

doubleloop_norm_manh_FV:

	LSR 		AL, #1
	BF			return_norm_manh_FV, EQ
	SUBB		AL, #1

	MOV32		R1H, *XAR4++		;load iv[i]
	MOV32 		R2H, *XAR4++		;load iv[i+1]
;loop
	RPTB 		loop_norm_manh_FV, AL
	ABSF32		R1H, R1H
	ABSF32		R2H, R2H
	ADDF32		R0H, R0H, R1H
	MOV32		R1H, *XAR4++		;load iv[i+2]
	ADDF32		R0H, R0H, R2H
	MOV32		R2H, *XAR4++		;load iv[i+3]
loop_norm_manh_FV:

return_norm_manh_FV:
	LRETR
	

	
	
	
	
;================/ _dist_euclid_FV /==============
;14 + 13*N/2   	if N is ODD
;11 + 13*N/2	if N is EVEN
	.sect .text
_dist_euclid_FV:

	MOV32		*SP++, R4H
	MOV32		*SP++, R5H

	TBIT		AL, #0
	BF			doubleloop_dist_euclid_FV, NTC

	MOV32		R1H, *XAR4++		; load lv[0]
	MOV32		R2H, *XAR5++		; load rv[0]
	SUBF32		R1H, R1H, R2H		; lv[0] - rv[0]
	NOP
	MPYF32		R0H, R1H, R1H		; y = (lv[0] - rv[0])^2

doubleloop_dist_euclid_FV:

	LSR 		AL, #1
	BF			return_dist_euclid_FV, EQ
	SUBB		AL, #1

	MOV32		R1H, *XAR4++		; load lv[i]
	MOV32		R2H, *XAR5++		; load rv[i]
;loop
	RPTB 		loop_dist_euclid_FV, AL
	SUBF32		R3H, R1H, R2H		; x = lv[i] - rv[i]
	MOV32		R4H, *XAR4++		; load lv[i+1]
	MPYF32		R3H, R3H, R3H		; x = x^2
	MOV32		R5H, *XAR5++		; load rv[i+1]
	ADDF32		R0H, R0H, R3H		; y += x
	
	SUBF32		R3H, R4H, R5H		; x = lv[i+1] - rv[i+1]
	MOV32		R1H, *XAR4++		; load lv[i+2]
	MPYF32		R3H, R3H, R3H		; x = x^2
	MOV32		R2H, *XAR5++		; load rv[i+2]
	ADDF32		R0H, R0H, R3H		; y += x
loop_dist_euclid_FV:

	LCR			_sqrtf

return_dist_euclid_FV:
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR
	
	
	
	
	
	
;================/ _dist_manh_FV /==============
;11 + 11*N/2	if N is EVEN
;14 + 11*N/2   	if N is ODD
	.sect .text
_dist_manh_FV:
	MOV32		*SP++, R4H
	MOV32		*SP++, R5H

	TBIT		AL, #0
	BF			doubleloop_dist_manh_FV, NTC

	MOV32		R1H, *XAR4++		; load lv[0]
	MOV32		R2H, *XAR5++		; load rv[0]
	SUBF32		R1H, R1H, R2H		; lv[0] - rv[0]
	NOP
	ABSF32		R0H, R1H			; y = |lv[0] - rv[0]|

doubleloop_dist_manh_FV:

	LSR 		AL, #1
	BF			return_dist_manh_FV, EQ
	SUBB		AL, #1

	MOV32		R1H, *XAR4++		; load lv[i]
	MOV32		R2H, *XAR5++		; load rv[i]
;loop
	RPTB 		loop_dist_manh_FV, AL
	SUBF32		R3H, R1H, R2H		; x = lv[i] - rv[i]
	MOV32		R4H, *XAR4++		; load lv[i+1]
	ABSF32		R3H, R3H			; x = |x|
	ADDF32		R0H, R0H, R3H		; y += x
	||MOV32		R5H, *XAR5++		; load rv[i+1]
	
	SUBF32		R3H, R4H, R5H		; x = lv[i+1] - rv[i+1]
	MOV32		R1H, *XAR4++		; load lv[i+2]
	ABSF32		R3H, R3H			; x = |x|
	ADDF32		R0H, R0H, R3H		; y += x
	||MOV32		R2H, *XAR5++		; load rv[i+2]
loop_dist_manh_FV:

	LCR			_sqrtf

return_dist_manh_FV:
	MOV32		R5H, *--SP
	MOV32		R4H, *--SP

	LRETR
		
		
		
		

;================/ _normalize_FV /==============
;52 + 13*N/2	if N is EVEN
;58 + 13*N/2   	if N is ODD
	.sect .text
_normalize_FV:

	PUSH	XAR4
	MOVL	XAR5, *-SP[2]
	
	LCR		_smul_FV_FV
	SWAPF	R0H, R1H
	MOVF32	R0H, #1.0
	LCR		FS$$DIV
	
	POP		XAR4
	LCR		_mul_FV_FS
	
	LRETR
	




























	

;================/ _max_FV /==============
;19 + 9*N/2   	if N is ODD
;16 + 9*N/2		if N is EVEN
	.sect .text
_max_FV:
;Start with x[0] as the assumed max
	MOV32 		R0H, *XAR5						;R0H = x[0] (initial max is first element in x[])
	ZERO 		R2H								;R2H = 0.0 (initial index is 0)
	MOVF32 		R3H, #-1.0						;R3H = -1.0 (index_candidate, need to start at -1 because loop immediately increments)

	TBIT		AL, #0
	BF			doubleloop_max_FV, NTC

	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;max candidate = x[i] (also delay slot for ADDF32)

	MAXF32 		R0H, R1H					;if max < max_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R2H, R3H					;if R0H < R1H, then R0H=R1H and R2H=R3H


doubleloop_max_FV:

	LSR 		AL, #1						;Divide N by 2
	ADDB 		AL, #-1						;Subtract 1 from N since RPTB is 'n-1' times
	BF			loop_max_FV, EQ

;main cycle
	RPTB 		loop_max_FV, @AL
	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;max candidate = x[i] (also delay slot for ADDF32)
	;if max < max_candidate, then max = max_candidate and index = index_candidate
	MAXF32 		R0H, R1H
	||MOV32 	R2H, R3H					;if R0H < R1H, then R0H=R1H and R2H=R3H

	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;max candidate = x[i] (also delay slot for ADDF32)

	MAXF32 		R0H, R1H					;if max < max_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R2H, R3H					;if R0H < R1H, then R0H=R1H and R2H=R3H
loop_max_FV:

;Prepare the return value
	F32TOUI16 	R2H, R2H					;convert index from float32 to Uint16
	NOP
	MOV32		*XAR4, R0H					;write max value
	MOV32 		ACC, R2H

;Finish up
	LRETR									;return














;================/ _min_FV /==============
;19 + 9*N/2   	if N is ODD
;16 + 9*N/2		if N is EVEN
	.sect .text
_min_FV:
;Start with x[0] as the assumed max
	MOV32 		R0H, *XAR5						;R0H = x[0] (initial max is first element in x[])
	ZERO 		R2H								;R2H = 0.0 (initial index is 0)
	MOVF32 		R3H, #-1.0						;R3H = -1.0 (index_candidate, need to start at -1 because loop immediately increments)

	TBIT		AL, #0
	BF			doubleloop_min_FV, NTC

	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;min candidate = x[i] (also delay slot for ADDF32)
	MINF32 		R0H, R1H					;if min > min_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R2H, R3H					;if R0H > R1H, then R0H=R1H and R2H=R3H

doubleloop_min_FV:
	LSR 		AL, #1						;Divide N by 2
	SUBB 		AL, #1						;Subtract 1 from N since RPTB is 'n-1' times
	BF			loop_min_FV, EQ
;main cycle
	RPTB 		loop_min_FV, @AL
	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;min candidate = x[i] (also delay slot for ADDF32)
	MINF32 		R0H, R1H					;if min > min_candidate, then min = min_candidate and index = index_candidate
	||MOV32 	R2H, R3H					;if R0H > R1H, then R0H=R1H and R2H=R3H

	ADDF32 		R3H, R3H, #1.0				;increment index candidate
	MOV32 		R1H, *XAR5++				;max candidate = x[i] (also delay slot for ADDF32)
	MINF32 		R0H, R1H					;if min > min_candidate, then max = max_candidate and index = index_candidate
	||MOV32 	R2H, R3H					;if R0H > R1H, then R0H=R1H and R2H=R3H
loop_min_FV:

;Prepare the return value
	F32TOUI16 	R2H, R2H					;convert index from float32 to Uint16
	NOP
	MOV32		*XAR4, R0H					;write min value
	MOV32 		ACC, R2H


;Finish up
	LRETR									;return




















;================/ _max_FV_FV /==============
;19 + 9*N/2   	if N is ODD
;16 + 9*N/2		if N is EVEN
	.sect .text
_max_FV_FV:

	MOVL			XAR6, *-SP[4]

	.align 	2
	SUBB			AL, #1
	RPTB			loop_max_FV_FV, AL
	MOV32			R0H, *XAR5++
	MOV32			R1H, *XAR6++
	MAXF32			R0H, R1H
	MOV32			*XAR4++, R0H
loop_max_FV_FV:


	LRETR									;return














;================/ _min_FV_FV /==============
;19 + 9*N/2   	if N is ODD
;16 + 9*N/2		if N is EVEN
	.sect .text
_min_FV_FV:

	MOVL			XAR6, *-SP[4]

	.align 	2
	SUBB			AL, #1
	RPTB			loop_min_FV_FV, AL
	MOV32			R0H, *XAR5++
	MOV32			R1H, *XAR6++
	MINF32			R0H, R1H
	MOV32			*XAR4++, R0H
loop_min_FV_FV:

	LRETR									;return










;================/ _constrain_FS /==============
;3 cycles
	.sect .text
_constrain_FS:
	MAXF32		R0H, R1H
	MINF32		R0H, R2H
	LRETR





;================/ _constrain_FV /==============
;15 + 11*N/2   	if N is ODD
;10 + 11*N/2	if N is EVEN
	.sect .text
_constrain_FV:

	TBIT		AL, #0
	BF			doubleloop_constrain_FV, NTC

	MOV32		R2H, *XAR5++	;load next in
	MAXF32		R2H, R0H		;if x < min then x = min (greater of MIN and X)
	MINF32		R2H, R1H		;if x > max then x = max (lesser of MAX and X)
	MOV32		*XAR4++, R2H	;write to out

doubleloop_constrain_FV:

	LSR			AL, #1
	BF			return_constrain_FV, EQ

	SUBB		AL, #1

;__loop
	RPTB		loop_constrain_FV, AL
	MOV32		R2H, *XAR5++	;load next in
	MAXF32		R2H, R0H		;if x < min then x = min (greater of MIN and X)
	MINF32		R2H, R1H		;if x > max then x = max (lesser of MAX and X)
	MOV32		*XAR4++, R2H	;write to out

	MOV32		R2H, *XAR5++	;load next in
	MAXF32		R2H, R0H		;if x < min then x = min (greater of MIN and X)
	MINF32		R2H, R1H		;if x > max then x = max (lesser of MAX and X)
	MOV32		*XAR4++, R2H	;write to out
loop_constrain_FV:
return_constrain_FV:
	LRETR









	
	
	
	
;================/ _mean_FV /==============
;38 + 3*N
_mean_FV:

	MOVB		AH, #0
	PUSH		ACC
	MOV32		R1H, *--SP
	MOVF32		R0H, #1.0
	I16TOF32	R1H, R1H
	LCR			FS$$DIV

	MOV32		*SP++, R0H
	LCR			_sum_FV
	MOV32		R1H, *--SP
	MPYF32		R0H, R0H, R1H

	LRETR
	
	
	
;================/ _mean2_FV /==============
;36 + 3*N
_mean2_FV:

	MOV32       *SP++,R7H		;Save R7H (save-on-entry register)
    MOV32       *SP++,R6H		;Save R6H (save-on-entry register)

    MOVL		XAR7, XAR4

    MOVF32 		R0H, #1.0		;R0H = 1.0

	MOV			AH, #0
	PUSH		ACC
	MOV32		R1H, *--SP		;
	UI16TOF32	R1H, R1H		;convert N to f32
	LCR			FS$$DIV

    ZERO        R2H				;Zero R2H
    ZERO        R3H				;Zero R3H
    ZERO        R6H				;Zero R6H
    ZERO        R7H				;Zero R7H

	SUBB		AL, #1			;calc N-1
	RPT			AL
	||MACF32	R7H, R3H, *XAR4++, *XAR7++		;res += x[i] * x[i]

	ADDF32		R3H, R3H, R2H
	ADDF32		R7H, R7H, R6H
    MOV32       R6H, *--SP                   ;Restore R6H
	ADDF32		R1H, R3H, R7H
    MOV32    	R7H, *--SP                   ;Restore R7H
	MPYF32		R0H, R0H, R1H	;equivalent res = res / N

return_mean2_mean2_FV:
    LRETR                                   ;return

	
	
	

;================/ _mean3_FV /==============
;27 + 8*N
_mean3_FV:

    MOVF32 		R0H, #1.0		;R0H = 1.0

	MOV			AH, #0
	PUSH		ACC				;save count
	MOV32		R1H, *-SP[2]
	UI16TOF32	R1H, R1H		;convert N to f32
	LCR			FS$$DIV			;c = 1 / count
	POP			ACC				;restore count

	SUBB		AL, #1			;calc N-1
	ZERO		R3H

	MOV32		R1H, *XAR4++	;load iv[i]
	RPTB		loop_mean3_FV, AL
	MPYF32		R2H, R1H, R1H	;tmp = iv[i] * iv[i]
	NOP
	MPYF32		R2H, R2H, R1H	;x^3 = tmp * iv[i]
	MOV32		R1H, *XAR4++	;load iv[i]
	ADDF32		R3H, R3H, R2H	;sum = sum + x^3
loop_mean3_FV:

	NOP
	MPYF32		R0H, R0H, R3H	;res = sum * c

	LRETR
	








;================/ _conv_circle_FV /==============
;20 + (12 + 3*K) * N
_conv_circle_FV:
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
	LSL			AH, 1
	MOV			AL, #0
	MOVL		XAR1, ACC
	MOVL		XAR5, XAR1
	MOVL		ACC, XAR0

	SUBB		AL, #1			;dec value for main cycle
	SUBB		AH, #1			;dec value for convolve cycle

	ZEROA						;
	MOV32		R0H, *-SP[10]	;load kern ptr
	MOVF32		R1H, #0.0
	MOVZ		AR0, SP
	MOV32		*SP++, R1H

	.lp_amode
	SETC		AMODE

;main cycle
	RPTB		loop_conv_circle_FV, AL
	MOV32		XAR7, R0H	;load kern ptr

;conv cycle
	RPT			AH
	||MACF32	R3H, R7H, *+XAR6[AR1%++], *XAR7++
;---

	ADDF32		R7H, R7H, R6H
	||MOV32		R6H, *,ARP0
	MOV32		R6H, *,ARP0
	ADDF32		R3H, R3H, R2H
	||MOV32		R2H, *,ARP0
	ADDB		XAR5, #2
	ADDF32		R3H, R3H, R7H
	||MOV32		R7H, *,ARP0
	MOVL		XAR1, XAR5
	MOV32		*XAR4++, R3H
	MOV32		R3H, *,ARP0
loop_conv_circle_FV:
;---

	.c28_amode
	CLRC		AMODE

	MOV32		R1H, *--SP
;restore context
	MOV32		R7H, *--SP
	MOV32		R6H, *--SP
	POP			XAR1

	LRETR
	
	
	
	


;================/ _circ_shift_FV /==============
;_circ_shift_FV:

;	PUSH		ACC
;	PUSH		XAR4
;	PUSH		XAR5
;	MOVL		ACC, XAR5
;	CMPL		ACC, *-SP[4]
;	BF			circ_shift_FV_anyway, EQ
;	;simple variant, ov != iv. Using memcpy
;
;	MOV			AL, *-SP[5]	;load shift
;	MOVB		AH, #0
;	LSL			ACC, #1
;	ADDL		ACC, *-SP[4] 	;ov += shift
;	MOVL		XAR4, ACC
;
;	MOVL		ACC, *-SP[6]
;	SUB			AL, AH
;	MOVB		AH, #0
;	LSL			ACC, #1			;size = 2 * (n - shift)
;	PUSH		ACC
;
;	LCR			_memcpy			;copy n - shift values
;
;	POP			ACC
;	ADDL		ACC, *-SP[2]
;	MOVL		XAR5, ACC		;iv += n - shift
;
;	MOVL		XAR4, *-SP[4]	;ov = ov arg
;
;	MOV			AL, *-SP[5]
;	MOV			AH, #0
;	LSL			ACC, #1			;size = 2 * shift
;
;	LCR			_memcpy			;copy n - shift values
;
;	SUBB		SP, #6
;	LRETR
;
;circ_shift_FV_anyway:
;	;if ov == iv
;	MOVL		XAR4, *-SP[4]	;load pointer
;	MOVZ		AR5, *-SP[6]	;load n
;	SUBB		XAR0, #1
;	MOV			AL, *-SP[5]		;load shift
;	MOV			AH, #0
;	ADDB		ACC, #1
;	LSL			ACC, #1
;
;	MOV32		R0H, *XAR4		;load r0 = iv[0]
;circ_shift_FV_loop:
;	ADDL		XAR4, ACC
;	MOV32		R1H, *XAR4		;load r1 = iv[i+shift]
;	SWAPF		R0H, R1H		;swap(r0,r1)
;	MOV32		*XAR4, R1H		;save iv[i+shift] = r0
;	BANZ		circ_shift_FV_loop, AR5--
;
;	LRETR








;================/ _horner_FV /==============
;8 + 7*N  cycles
	.sect .text
_horner_FV:
	MOVZ		AR0, AL
	SUBB		XAR0, #2

	MOV			AH, #0
	LSL			ACC, 1
	ADDL		ACC, XAR4
	MOVL		XAR4, ACC
	
	MOV32		R1H, R0H
	MOV32		R0H, *--XAR4			; load y = a[i]
loop_horner_FV:
	MPYF32		R0H, R0H, R1H			; y = x * y
	MOV32		R2H, *--XAR4			; load a[i-1]
	ADDF32		R0H, R0H, R2H			; y = y + a[i-1]
	BANZ		loop_horner_FV, AR0--
	
	LRETR








;================/ _traverse_FV /==============
;14 + (9 + func) * N  cycles
	.sect .text
_traverse_FV:

	SUBB	AL, #1
	BF		return_traverse_FV, NC

	PUSH	XAR1
	PUSH	XAR2
	PUSH	XAR3

	MOVL	XAR2, XAR4
	MOVL	XAR3, XAR5

	MOV		AR1, AL
loop_traverse_FV:
	MOV32	R0H, *XAR3++
	MOVL	XAR7, *-SP[10]
	LCR		*XAR7
	MOV32	*XAR2++, R0H
	BANZ	loop_traverse_FV, AR1--

	POP		XAR3
	POP		XAR2
	POP		XAR1

return_traverse_FV:
	LRETR




;================/ _traverse_FV_FV /==============
;2 + 6*N  cycles
	.sect .text
_traverse_FV_FV:

	SUBB	AL, #1
	BF		return_traverse_FV_FV, NC

;save context
	PUSH	XAR1
	PUSH	XAR2
	PUSH	XAR3
	PUSH	XAR4

	MOVL	XAR2, XAR5		;load x1 ptr
	MOVL	XAR3, *-SP[12]	;load x2 ptr

	MOV		AR1, AL

loop_traverse_FV_FV:
	MOV32	R0H, *XAR2++	;load x1 value
	MOV32	R1H, *XAR3++	;load x2 value
	MOVL	XAR7, *-SP[14]	;load function ptr
	LCR		*XAR7			;call function
	MOVL	XAR4, *-SP[2]	;load out ptr
	MOV32	*XAR4++, R0H	;write out
	MOVL	*-SP[2], XAR4	;save new out ptr
	BANZ	loop_traverse_FV_FV, AR1--

;restore context
	POP		XAR4
	POP		XAR3
	POP		XAR2
	POP		XAR1

return_traverse_FV_FV:
	LRETR
