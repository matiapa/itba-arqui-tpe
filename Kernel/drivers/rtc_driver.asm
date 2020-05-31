GLOBAL getSecond
GLOBAL getMinute
GLOBAL getHour
GLOBAL setHour

%macro get 1
    mov al, %1
    out 70h, al
    mov rax, 0
    in al, 71h
    movzx rcx, al
    call bcdToDec
    ret
%endmacro

getSecond:
    get 0

getMinute:
    get 2

getHour:
    get 4

bcdToDec:
    ;mov cl, 00100011b
    mov rax, 0

    mov bh, cl      ; Get higher part
    and bh, 11110000b
    shr bh, 4

    mov bl, cl      ; Get lower part
    and bl, 00001111b

    mov al, bh      ; Multiply higher part by 10
    mov dl, 10
    mul dl

    movzx bx, bl    ; Add lower part
    add ax, bx
    
    ret