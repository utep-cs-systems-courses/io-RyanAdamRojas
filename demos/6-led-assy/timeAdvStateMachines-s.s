    .arch msp430g2553
    .p2align 1,0
    .text

    .global timeAdvStateMachines
    .extern blinkUpdate
    .extern secondUpdate

timeAdvStateMachines:
    call blinkUpdate       ; Calls the blinkUpdate function
    call secondUpdate      ; Calls the secondUpdate function
    ret                    ; Return from the function
