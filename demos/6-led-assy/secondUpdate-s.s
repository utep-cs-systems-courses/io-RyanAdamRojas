    .arch msp430g2553
	.p2align 1,0
	.text

	.global secondUpdate
	.extern oncePerSecond

	.data
	secondCount: .word 0        ; Static integer

secondUpdate:
    add #1, secondCount         ; Increments
    mov &secondCount, r12       ; Moves secondCount to r12 for cmp
    cmp #250, r12               ; Compares a >= b
    jl done                     ; if less, done

    mov #0, &secondCount        ; else, secondCount reset
    call #oncePerSecond         ; Calls subroutine oncePerSecond

done:
    ret                         ; Returns from subroutine
