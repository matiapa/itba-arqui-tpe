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
.global _exception6Handler

.extern irqDispatcher
.extern exceptionDispatcher

.extern readi
.extern storeState

.intel_syntax noprefix

.section .text

.macro pushState
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rbp
	push rdi
	push rsi
	push rdx
	push rcx
	push rbx
	push rax
.endm

.macro popState
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rbp
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
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
	pushState

	call readi
	cmp rax, 15
	jne _skip

	call storeState

	# signal pic EOI (End of Interrupt)
	_skip: mov rdi, 1 # pasaje de parametro
	call irqDispatcher

	mov al, 0x20
	out 0x20, al

	popState
	iretq
	

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

#Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret
