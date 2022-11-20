.include "m16def.inc"
.DEF A = r16 ;; δήλωση καταχωρητών
.DEF B = r17
.DEF C = r18
.DEF D = r19
.DEF temp = r20
.DEF BN = r21 ;; complements
.DEF CN = r22
.DEF DN = r23
.DEF F0 = r24
.DEF F1 = r25
.cseg
.org 0 ;; διεύθυνση εκκίνησης

start:
	clr temp ;; θύρα Β ως είσοδος
	out DDRB, temp
	ser temp
	out DDRA, temp ;; θύρα A ως έξοδος

loop:
	in temp , PINB ;; ανάγνωση ακροδεκτών PORTB
	mov A, temp ;; το Α στο LSB του καταχωρητή Α
	lsr temp
	mov B, temp ;; το Β στο LSB του καταχωρητή Β
	lsr temp
	mov C, temp ;; το C στο LSB του καταχωρητή C
	lsr temp
	mov D, temp ;; το D στο LSB του καταχωρητή D

	mov BN, B ;; compute complements
	com BN
	mov CN, C
	com CN
	mov DN, D
	com DN

	mov F0, A ;; F0 = ABC + B'C'D'
	and F0, B
	and F0, C
	and BN, CN
	and BN, DN
	or F0, BN

	mov F1, A ;; F1 = (A + B + C) . D
	or F1, B
	or F1, C
	and F1, D
	
	andi F0, 1
	andi F1, 1
	lsl F1
	add F0, F1
	out PORTA, F0 ;; έξοδος αποτελέσματος
	rjmp loop ;; άλμα στην διεύθυνση loop για διαρκή εκτέλεση
