; ALGORITHM:
;
;	   The sin value is calculated as follows:
;
;	   1) The offset into a 512 word sin/cos table is calculated:
;
;	  k = 0x1FF & (int(Radian*512/(2*pi)))
;
;
;	   2) The fractional component between table samples is
;	  calculated:
;
;	  x = fract(Radian*512/2*pi) * (2*pi)/512
;
;	   3) The output sine value is calculated as follows:
;
;	  sin(Radian) = S(k) + x*(C(k) + x*(-0.5*S(k) - 0.166667*x*C(k)))
;
;	  where  S(k) = Sin table value at offset "k"
;	 C(k) = Cos table value at offset "k"


	.global _sinf
	.ref	_FPUsinTable
	.ref	_FPUcosTable
	.text
_sinf:	; R0H = Radian (on entry)
	MOVF32		R1H, #81.4873309		; R1H = 512/(2*pi) = 512/6.28318531 = 81.4873309
	MPYF32		R0H, R0H, R1H	  		; R0H = Radian * 512/(2*pi)
	MOVF32	 	R2H,#0.012271846644531	; R2H = (2*pi)/512 = 0.012271846644531
	F32TOI32  	R1H, R0H	   			; R1H = int(Radian * 512/(2*pi))
	MOVL	  	XAR6,#_FPUcosTable
	MOVL	  	XAR7,#_FPUsinTable
	MOV32	 	ACC, R1H	   			; ACC = int(Radian *512/(2*pi))
	AND	   		@AL,#0x1FF
	LSL	   		AL,#1
	MOVZ	  	AR0,@AL					; AR0 = Index into "sin/cos" table = k
	FRACF32   	R0H, R0H	  	 		; R0H = fract(Radian*512/(2*pi))
	MOVF32	 	R3H,#0.166667			; R3H = 0.166667 (0x3E2AAAAB)
	MPYF32		R2H, R0H, R2H	  		; R2H = x = fract(Radian*512/(2*pi)) * (2*pi)/512
	|| MOV32	R1H,*+XAR6[AR0]			; R1H = C(k)
	MPYF32		R3H, R3H, R1H	  		; R3H = 0.166667*C(k)
	|| MOV32	R0H,*+XAR7[AR0]			; R0H = S(k)
	MPYF32		R0H, -0.5, R0H	 		; R0H = -.5*S(k)
	MPYF32		R3H, R2H, R3H	  		; R1H = x*0.166667*C(k)
	NOP
	SUBF32		R0H, R0H, R3H	  		; R0H = -.5*S(k) - 0.166667*x*C(k)
	NOP
	MPYF32		R3H, R2H, R0H	  		; R3H = x*(-.5*S(k) - 0.166667*x*C(k))
	|| MOV32	R1H, *+XAR6[AR0]  		; R1H = C(k)
	NOP
	ADDF32		R3H, R1H, R3H	  		; R3H = C(k) + x*(-.5*S(k) - 0.166667*x*C(k))
	NOP
	MPYF32		R3H, R2H, R3H	  		; R3H = x*(C(k) + x*(-.5*S(k) - 0.166667*x*C(k)))
	|| MOV32	R0H, *+XAR7[AR0]   		; R0H = S(k)
	NOP
	ADDF32		R0H, R0H, R3H	  		; R0H = sin(Radian) = S(k) + x*(C(k) + x*(-.5*S(k) - 0.166667*x*C(k)))
	LRETR
