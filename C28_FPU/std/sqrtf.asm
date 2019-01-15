; ALGORITHM:
;
;	  Ye = Estimate(1/sqrt(X));
;	  Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;	  Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;	  Y  = sqrt(X) = X*Ye

	.page
	.global	 _sqrtf
	.text
;20 cycles
_sqrtf:
	; R0H = X on entry
 	EISQRTF32   R1H, R0H	; R1H = Ye = Estimate(1/sqrt(X))
	MPYF32	  	R2H, R0H, #0.5	  ; R2H = X*0.5
	MPYF32	  	R3H, R1H, R1H	   ; R3H = Ye*Ye
	NOP
	MPYF32	  	R3H, R3H, R2H	   ; R3H = Ye*Ye*X*0.5
	NOP
	SUBF32	  	R3H, #1.5, R3H	  ; R3H = 1.5 - Ye*Ye*X*0.5
	NOP
	MPYF32	  	R1H, R1H, R3H	   ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
	NOP
	MPYF32	  	R3H, R1H, R2H	   ; R3H = Ye*X*0.5
	NOP
	MPYF32	  	R3H, R1H, R3H	   ; R3H = Ye*Ye*X*0.5
	NOP
	SUBF32	  	R3H, #1.5, R3H	  ; R3H = 1.5 - Ye*Ye*X*0.5
	CMPF32	  	R0H, #0.0	   ; Check if X == 0
	MPYF32	  	R1H, R1H, R3H	   ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
	NOP
	MOV32		R1H, R0H, EQ	; If X is zero, change the Ye estimate to 0
	MPYF32	  	R0H, R0H, R1H	   ; R0H = Y = X*Ye = sqrt(X)
	LRETR
