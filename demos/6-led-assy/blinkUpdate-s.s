	.arch msp430g2553
	.p2align 1,0
	.text

	.global blinkUpdate
	.extern greenControl
	.extern blinkLimit              ; Static integer

    .data
    blinkCount: .word 0             ; Initializes

blinkUpdate:
    add #1, &blinkCount             ; Increments blinkCount
    mov &blinkCount, r12            ; Loads to register
    cmp &blinkLimit, r12            ; a >= b
    jge turn_on                     ; if a >= b

    mov #0, r12                     ; else, greenControl(0)
    call #greenControl              ; Calls subroutine greenControl(off)
    jmp done

turn_on:
    mov #1, r12                     ; if true, greenControl(1)
    call #greenControl              ; Calls subroutine greenControl(on)

done:
    ret                             ; Returns from subroutine
