/*---------------------------------------------------------------------------------------------------
|   LIB.S  |                                                                             			|
|-----------                                                                               			|
| This file provides miscellaneous assembler functions.                                         	|
---------------------------------------------------------------------------------------------------*/

.global _cli
.global _sti
.global _in
.global _out

.intel_syntax noprefix

.section .text

_hlt:
    hlt
    ret


_cli:
	cli
	ret


_sti:
	sti
	ret

_in:
	push rdx
	mov rdx, rdi
	in eax, dx
	pop rdx
	ret

_out:
	push rdx
	mov rdx, rdi
	mov rax, rsi
	out dx, eax
	pop rdx
	ret
