	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenControl
	.extern P1OUT

greenControl:
	cmp #0, r12
	jz off
	bis.b #GREEN, &P1OUT		;or
	jmp done
off:	and.b #~GREEN, &P1OUT
done:	pop r0
