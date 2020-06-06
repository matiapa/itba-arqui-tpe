.globl _syscallDispatcher
.extern sysDraw
.extern sysRead
.extern sysGetRes
.extern sysMemDump
.extern sysGetTime
.extern sysCpuInfo
.extern sysCPUTemp
.intel_syntax noprefix

.section .text

_syscallDispatcher:
    cmp rax, 1
    je _draw

    cmp rax, 2
    je _read

    cmp rax, 3
    je _getRes

    cmp rax, 4
    je _memDump

    cmp rax, 5
    je _getTime

    cmp rax, 6
    je _cpuInfo

    cmp rax, 7
    je _cpuTemp

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

_cpuInfo:
    call sysCpuInfo
    iretq

_cpuTemp:
    call sysCPUTemp
    iretq
