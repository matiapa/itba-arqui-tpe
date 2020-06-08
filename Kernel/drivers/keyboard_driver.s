.globl read
.intel_syntax noprefix

.section .text

read:
    mov rax, 0
    in al, 0x60
    ret
