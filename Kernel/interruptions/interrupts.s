/*---------------------------------------------------------------------------------------------------
|   INTERRUPTS.C    |                                                                    			|
|--------------------                                                                    			|
| This file provides functions for setting up interruptions routines and flags. Also, has the    	|
| functions that are directly loaded on to the IDT.													|
---------------------------------------------------------------------------------------------------*/


/* --------------------------------------------------------------------------------------------------------------------------------------------------
															DECLARATIONS
-------------------------------------------------------------------------------------------------------------------------------------------------- */

.global _cli
.global _sti
.global picMasterMask
.global picSlaveMask
.global haltcpu
.global _hlt

.global _irq00Handler
.global _irq01Handler

.global _exception0Handler
.global _exception6Handler

.extern irqDispatcher
.extern exceptionDispatcher

.extern read
.extern storeState

.intel_syntax noprefix


/* --------------------------------------------------------------------------------------------------------------------------------------------------
															MACROS
-------------------------------------------------------------------------------------------------------------------------------------------------- */


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


.macro irqHandlerMaster name irq
\name:
	pushState

	mov rdi, \irq
	call irqDispatcher

	mov al, 0x20	# Signal pic EOI (End of Interrupt)
	out 0x20, al

	popState
	iretq
.endm


.macro exceptionHandler name exception
\name:
	pushState
	call storeState
	popState

	mov rdi, \exception 	# Exception code
	mov rsi, [rsp]		# EIP at exception generation
	call exceptionDispatcher
	
	iretq
.endm


/* --------------------------------------------------------------------------------------------------------------------------------------------------
														PIC MASKS CONTROLLERS
-------------------------------------------------------------------------------------------------------------------------------------------------- */


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


/* --------------------------------------------------------------------------------------------------------------------------------------------------
													EXCEPTIONS ATTENTION ROUTINES
-------------------------------------------------------------------------------------------------------------------------------------------------- */


exceptionHandler _exception0Handler 0		# Zero Division Exception

exceptionHandler _exception6Handler 6		# Invalid Opcode Exception


/* --------------------------------------------------------------------------------------------------------------------------------------------------
													INTERRUPTIONS ATTENTION ROUTINES
-------------------------------------------------------------------------------------------------------------------------------------------------- */


irqHandlerMaster _irq00Handler 0		# RTC

_irq01Handler:			# Keyboard
	pushState

	call read			# Before lending control to dispatcher, it checks if TAB key has been pressed
	cmp rax, 15			# If so, it stores the state of the registers, this state can be accessed later through a syscall
	jne _skipStore

	call storeState

	_skipStore: mov rdi, 1
	call irqDispatcher

	mov al, 0x20
	out 0x20, al

	popState
	iretq


/* --------------------------------------------------------------------------------------------------------------------------------------------------
													INTERRUPT FLAG CONTROL FUNCTIONS
-------------------------------------------------------------------------------------------------------------------------------------------------- */


_cli:
	cli
	ret


_sti:
	sti
	ret
