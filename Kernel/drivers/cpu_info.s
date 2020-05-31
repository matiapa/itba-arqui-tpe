.global getBrandName
.global getBrandIndex
.global getRegisters
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


getRegisters:
    mov [rdi], rax
    mov [rdi+8], rbx
    mov [rdi+16], rcx
    mov [rdi+24], rdx
    mov [rdi+32], rsi
    mov [rdi+40], rdi
    mov [rdi+48], rbp
    mov [rdi+56], rsp
    #mov [rdi+64], rip
    mov [rdi+72], r8
    mov [rdi+80], r9
    mov [rdi+88], r10
    mov [rdi+96], r11
    mov [rdi+104], r12
    mov [rdi+112], r13
    mov [rdi+120], r14
    mov [rdi+128], r15
    #mov [rdi+136], eflags
    ret
