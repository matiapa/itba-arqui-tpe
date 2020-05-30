.globl draw
.globl read
.intel_syntax noprefix

draw:
    mov eax, 1
    int 0x80
    ret

read:
    mov eax, 2
    int 0x80
    ret
