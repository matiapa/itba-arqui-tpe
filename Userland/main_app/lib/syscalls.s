.intel_syntax noprefix

.macro syscall name, code
.global \name
\name:
    mov eax, \code
    int 0x80
    ret
.endm

syscall draw, 1
syscall read, 2
syscall getRes, 3
syscall regDump, 4
syscall memDump, 5
syscall getTime, 6
syscall cpuInfo, 7
syscall cpuTemp, 8
