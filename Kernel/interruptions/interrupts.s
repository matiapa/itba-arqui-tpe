.global _cli
.global _sti
.global picMasterMask
.global picSlaveMask
.global haltcpu
.global _hlt

.global _irq00Handler
.global _irq01Handler
.global _irq02Handler
.global _irq03Handler
.global _irq04Handler
.global _irq05Handler

.global _exception0Handler

.extern irqDispatcher
.extern exceptionDispatcher

.intel_syntax noprefix

.section .text

.macro pushState
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
.endm

.macro popState
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
.endm

.macro irqHandlerMaster irq
	pushState

	mov rdi, \irq # pasaje de parametro
	call irqDispatcher

	# signal pic EOI (End of Interrupt)
	mov al, 0x20
	out 0x20, al

	popState
	iretq
.endm



.macro exceptionHandler exception
	#pushState

	mov rdi, \exception # Exception code
	mov rsi, [rsp]	# EIP at exception generation
	call exceptionDispatcher

	#popState
	iretq
.endm


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	0x21,al
    pop rbp
    ret

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  # ax = mascara de 16 bits
    out	0xA1,al
    pop     rbp
    ret


#8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

#Keyboard
_irq01Handler:
	irqHandlerMaster 1

#Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

#Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

#Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

#USB
_irq05Handler:
	irqHandlerMaster 5


#Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret
