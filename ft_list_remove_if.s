section .data
_message:
    db "loop", 10
section .text
global ft_list_remove_if
extern free

_debug:
	push	rax
	push	rbx
	push	rcx
	push	rdx
	push	rdi
	push	rsi

    mov    rax, 0x01
    mov rdi, 1
    mov rsi, _message
    mov    rdx, 5
    syscall
	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rbx
	pop		rax

    ret

; rdi = t_list **begin_list
; rsi = void *data_ref
; rdx = int (*cmp)()
; rcx = void (*free_fct)(void *)
ft_list_remove_if:
_loop_start:
	mov		rax, [rdi]
	test	rax, rax
	je		_loop_end

	push	rax
	push	rcx
	push	rdx
	push	rdi
	push	rsi

	mov		rdi, [rax + 0x08]
	call	rdx

	cmp		rax, 0
	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rax

	jne		_loop_end

_loop_do:
	mov		rbx, [rax + 0x00]
	mov		[rdi], rbx

	push	rax
	push	rbx
	push	rcx
	push	rdx
	push	rdi
	push	rsi
	push	rax

	mov		rdi, [rax + 0x08]
	call	rcx

	pop		rdi
	call	free

	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rbx
	pop		rax

	jmp		_loop_start
_loop_end:
	test	rax, rax
	je		_ret
	mov		rbx, [rax + 0x00]
_second_loop_start:
	test	rbx, rbx
	je		_ret
_second_loop_do:
	mov		rdi, [rbx + 0x08]
	push	rax
	push	rbx
	push	rcx
	push	rdx
	push	rdi
	push	rsi

	call	rdx
	cmp		rax, 0

	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rbx
	pop		rax

	jne		_else
_if:
	push	rdi
	mov		rdi, [rbx + 0x00]
	mov		[rax + 0x00], rdi
	pop		rdi

	push	rax
	push	rcx
	push	rdx
	push	rsi
	push	rbx

	call	rcx
	pop		rdi
	call	free

	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rax

	mov		rbx, [rax + 0x00]

	jmp _second_loop_start
_else:
	mov		rax, rbx
	mov		rbx, [rax + 0x00]

	jmp _second_loop_start
_ret:
	ret
