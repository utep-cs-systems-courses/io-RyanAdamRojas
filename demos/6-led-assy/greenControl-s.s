	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenControl
	.global GREEN
	.extern P1OUT

greenControl:
    cmp #0, r12             ; Compare `on` (in R12) with 0
    jz off                  ; If zero (off), jump to off
    bis.b #GREEN, &P1OUT    ; Otherwise, turn the LED on
    jmp done                ; Jump to done
off:
    mov.b #GREEN, r13       ; Move GREEN to r13
    xor #0xFFFF, r13             ; Invert all bits in r13 to perform NOT
    and.b r13, &P1OUT       ; Turn the LED off with the modified r13
done:
    pop r0                  ; Restore the previous condition code register (SR)

