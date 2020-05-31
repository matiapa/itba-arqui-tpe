.global getBrandName
.global getBrandIndex
.intel_syntax noprefix

.section .text


.macro _getBrand part
    mov eax, 0x80000002+\part
    cpuid
    mov [rdi+16*\part+0], eax
    mov [rdi+16*\part+4], ebx
    mov [rdi+16*\part+8], ecx
    mov [rdi+16*\part+12], edx
.endm

getBrandName:
    push rbx

    _getBrand 0
    _getBrand 1
    _getBrand 2
    movb [rsi+49], 0

    pop rbx
    ret


getBrandIndex:
    mov eax, 1
    cpuid
    mov eax, ebx
    and eax, 0xF
    ret
