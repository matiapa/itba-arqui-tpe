.globl _syscallHandler
.extern syscallDraw
.extern syscallRead
.extern syscallGetRes
.intel_syntax noprefix

.section .text

_syscallHandler:
    cmp rax, 1
    je _draw

    cmp rax, 2
    je _read

    cmp rax, 3
    je _getRes

    iretq

_draw:
    call syscallDraw
    iretq

_read:
    call syscallRead
    iretq

_getRes:
    call syscallGetRes
    iretq
