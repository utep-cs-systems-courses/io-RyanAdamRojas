    .arch msp430g2553
    .p2align 1,0
    .data

    .global red_on, green_on, led_changed, redVal, greenVal
    red_on:      .byte 0
    green_on:    .byte 0
    led_changed: .byte 0
    redVal:      .byte 0, LED_RED
    greenVal:    .byte 0, LED_GREEN

    .text
    .global led_init
    .global led_update
    .extern P1OUT
    .extern P1DIR
    .extern LEDS

led_init:
    mov.b #1, &led_changed
    call #led_update
    ret

led_update:
    mov.b &led_changed, r12    ; Load led_changed into r12
    cmp #0, r12
    jeq end                    ; Jump to end if led_changed is 0

    ; Determine ledFlags
    mov.b &red_on, r12         ; Load red_on into r12
    mov.b &redVal, r13         ; Load redVal into r13
    bit.b r12, r13             ; Test red_on, apply mask from redVal
    mov.b &green_on, r12       ; Load green_on into r12
    mov.b &greenVal, r14       ; Load greenVal into r14
    bit.b r12, r14             ; Test green_on, apply mask from greenVal
    bis.b r14, r13             ; Combine red and green

    ; Update P1OUT
    bic.b &LEDS, &P1OUT        ; Clear LEDS bits in P1OUT
    bis.b r13, &P1OUT          ; Set bits according to ledFlags

    ; Reset led_changed
    clr.b &led_changed

end:
    ret
