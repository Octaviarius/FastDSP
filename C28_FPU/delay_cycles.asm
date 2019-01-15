

	.global _delay_cycles


	.sect .text


_delay_cycles:
	SUBB	ACC, #13
	PUSH	#3
	PUSH	#0
	POP		T
	LSRL	ACC, T
loop:
	SUBB	ACC, #1
	NOP
	NOP
	NOP
	BF		loop, EQ

	LRETR
