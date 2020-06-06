/*---------------------------------------------------------------------------------------------------
|   SYSCALLS.S    |                                                                                 |
|----------------                                                                                   |
| This libary implements callers for all the syscalls provided by the kernel                        |
---------------------------------------------------------------------------------------------------*/

.intel_syntax noprefix
.global valueSet

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
syscall memDump, 4
syscall getTime, 5
syscall cpuInfo, 6
syscall cpuTemp, 7
syscall getLastException, 8
syscall getRegBkp, 9
