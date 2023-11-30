	.arch msp430g2553
	.p2align 1,0
	.text

    .global oncePerSecond
    .global blinkLimit

oncePerSecond:
    add #1, &blinkLimit     ; Increments
    mov &blinkLimit, r12    ; Loads blinkLimit to r12 for cmp
    cmp #8, r12             ; Compares blink limit to 8
    jl done                 ; if less, done

    mov #0, &blinkLimit     ; else, blinkLimit = 0

done:
    ret                     ; Returns from subroutine
