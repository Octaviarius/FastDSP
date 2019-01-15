
	.global FS$$DIV


;17 cycles
        .text
FS$$DIV:

        EINVF32     R2H, R1H            ; R2H = Ye = Estimate(1/B)
        CMPF32      R0H, #0.0           ; Check if A == 0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        NOP
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B
        NOP
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
; Next line: if commented out: 0.0/0.0 = 0.0
;            if not commented: 0.0/0.0 = infinity
;       MOV32       R2H, R0H, EQ        ; If A == 0.0, Ye = 0.0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        CMPF32      R1H, #0.0           ; Check if B == 0.0
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B
        NEGF32      R0H, R0H, EQ        ; Fixes sign for A/0.0
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
        MPYF32      R0H, R0H, R2H       ; R0H = Y = A*Ye = A/B
        LRETR

