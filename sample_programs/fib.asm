machine .REM1           ; Specifying a redstone computer to to make a binary for

section .code           ; Next line is a 0x0 code address
                        ; (Floating program position isn't supported rn)
    set r1 1            ; Setting up first two members of Fibonacci sequence
    set r2 1
    set r10 5           ; Anount of iterations
    set r11 0x20        ; Current writting address

    .main_loop
    add r1 r2 r3        ; Calculate the value for current iteration
    mov r2 r1           ; Pseudo instruction, copy value to r1 from r2
    mov r3 r2
    mld r3 0 r11        ; Load r3 to r11 address at RAM
    inc r11             ; Pseudo instruction, increase r11 value by 1
    dec r10             ; Pseudo instruction, decrease r10 value by 1
    brh 0 .main_loop    ; Repeat the previous block, if r10 isn't 0
    hlt                 ; Stop the program

section .data           ; This is a description of initial saved data
                        ; (rn only "real" addresses are available)
    real 0x20 <- 1       ; The value at 0x0 and 0x1 addresses is 1
    real 0x21 <- 1       ; The default numerical system is decimal