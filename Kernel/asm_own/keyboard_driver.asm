GLOBAL read

read:

    in al, 64h      ; Wait until bit 0 of status register is 1
    and al, 1h
    cmp al, 1
    jne read

    mov rax, 0
    in al, 60h
    ret
