.globl _syscallHandler
.extern sysDraw
.extern sysRead
.extern sysGetRes
.extern sysMemDump
.extern sysGetTime
.intel_syntax noprefix

.section .text

_syscallHandler:
    cmp rax, 1
    je _draw

    cmp rax, 2
    je _read

    cmp rax, 3
    je _getRes

    cmp rax, 5
    je _memDump

    cmp rax, 6
    je _getTime

    iretq

_draw:
    call sysDraw
    iretq

_read:
    call sysRead
    iretq

_getRes:
    call sysGetRes
    iretq

_memDump:
    call sysMemDump
    iretq

_getTime:
    call sysGetTime
    iretq
