.include "m16def.inc"

	ldi r24 , low(RAMEND) ; initialize stack pointer
	out SPL , r24
	ldi r24 , high(RAMEND)
	out SPH , r24
	clr r24
	out DDRA , r24 ;; A is input
	ser r24 
	out DDRB, r24 ;; B is output

	clr r24 ;; counter for led position
	ldi r25 , 0x01

left:
	in r26 , PINA
	andi r26 , 0x01
	cpi r26 , 0x01
	breq left
	out PORTB , r25
	rcall wait
    inc r24
	lsl r25
	cpi r24 , 7
	breq right
	rjmp left

right:
	in r26 , PINA
	andi r26 , 0x01
	cpi r26 , 0x01
	breq right
	out PORTB , r25
	rcall wait
    dec r24
	lsr r25
	cpi r24 , 0
	breq left
	rjmp right

wait:
	ldi r30, low(500)
	ldi r31, high(500)
	rcall wait_msec
	ret

wait_msec:
	push r30 ; 2 κύκλοι (0.250 μsec)
	push r31 ; 2 κύκλοι
	ldi r30 , low(998) ; φόρτωσε τον καταχ. r25:r24 με 998 (1 κύκλος - 0.125 μsec)
	ldi r31 , high(998) ; 1 κύκλος (0.125 μsec)
	rcall wait_usec ; 3 κύκλοι (0.375 μsec), προκαλεί συνολικά καθυστέρηση 998.375 μsec
	pop r31 ; 2 κύκλοι (0.250 μsec)
	pop r30 ; 2 κύκλοι
	sbiw r30, 1 ; 2 κύκλοι
	brne wait_msec ; 1 ή 2 κύκλοι (0.125 ή 0.250 μsec)
	ret ; 4 κύκλοι (0.500 μsec)

wait_usec:
	sbiw r30, 1 ; 2 κύκλοι (0.250 μsec)
	nop ; 1 κύκλος (0.125 μsec)
	nop ; 1 κύκλος (0.125 μsec)
	nop ; 1 κύκλος (0.125 μsec)
	nop ; 1 κύκλος (0.125 μsec)
	brne wait_usec ; 1 ή 2 κύκλοι (0.125 ή 0.250 μsec)
	ret ; 4 κύκλοι (0.500 μsec)
