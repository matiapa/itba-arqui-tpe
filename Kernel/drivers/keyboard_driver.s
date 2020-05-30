.globl read
.intel_syntax noprefix

.section .text

read:

    in al, 0x64      # Wait until bit 0 of status register is 1
    and al, 1
    cmp al, 1
    jne read

    mov rax, 0
    in al, 0x60
    ret
