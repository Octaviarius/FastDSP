
	.global _pid_process_F


ARG_P 		.set 0
ARG_I 		.set 2
ARG_D 		.set 4

ARG_CTRL 	.set 6

ARG_KP 		.set 8
ARG_KI 		.set 10
ARG_KD 		.set 12

ARG_SAT 	.set 14


;38 cycles
	.sect .text
_pid_process_F:

	;load saturation pointer
	MOVL		XAR5, XAR4
	ADDB		XAR5, #ARG_SAT

	SUBF32		R3H, R0H, R1H	;calc error = target - feedback
	MOV32		R0H, *+XAR4[ARG_P]	;load P

	;--- update differential part, D = error - P
	SUBF32		R2H, R3H, R0H	;calc D
	MOV32		R0H, R3H		;update P

	;--- update integral part
	MOV32		R1H, *+XAR4[ARG_I]
	ADDF32		R1H, R1H, R3H

	;--- saturating process
	; saturate P
	||MOV32		R3H, *XAR5++	;load sat_p min
	MAXF32		R0H, R3H
	MOV32		R3H, *XAR5++	;load sat_p max
	MINF32		R0H, R3H
	MOV32		*+XAR4[ARG_P], R0H	;save P

	; saturate I
	MOV32		R3H, *XAR5++	;load sat_i min
	MAXF32		R1H, R3H
	MOV32		R3H, *XAR5++	;load sat_i max
	MINF32		R1H, R3H
	MOV32		*+XAR4[ARG_I], R1H	;save I

	; saturate D
	MOV32		R3H, *XAR5++	;load sat_d min
	MAXF32		R2H, R3H
	MOV32		R3H, *XAR5++	;load sat_d max
	MINF32		R2H, R3H
	MOV32		*+XAR4[ARG_D], R2H	;save D

	;--- update control value
	MOVL		XAR7, XAR4
	ADDB		XAR7, #ARG_KP

	ZERO		R2H
	ZERO		R3H

	; !!! very important add NOP instructions for pipeline delay !!!
	MACF32		R7H, R3H, *XAR4++, *XAR7++	;Kp * P
	NOP
	MACF32		R7H, R3H, *XAR4++, *XAR7++	;Ki * I
	NOP
	MACF32		R7H, R3H, *XAR4++, *XAR7++	;Kd * D
	NOP
	ADDF32		R0H, R2H, R3H	;result summation

	; saturate OUT
	MOV32		R3H, *XAR5++	;load sat_out min
	MAXF32		R0H, R3H
	MOV32		R3H, *XAR5++	;load sat_out max
	MINF32		R0H, R3H
	MOV32		*XAR4++, R0H		;save OUT

	LRETR
