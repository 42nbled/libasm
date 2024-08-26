section .text
global ft_list_sort

_ft_swap:
	mov rax, [rdi]
	mov	rbx, [rsi]
	mov [rdi], rbx
	mov [rsi], rax
	ret

_ft_lst_swap:
	test	rdi, rdi
	je		_ret
	test	rsi, rsi
	je		_ret
	test	rdx, rdx
	je		_ret
	cmp		rsi, rdx
	je		_ret

	mov		rax, rdi
_while_start_a:
	mov		rbx, [rax]
	test	rbx,rbx
	je		_while_end_a
	cmp		rbx, rsi
	je		_while_end_a
_while_do_a:
	lea		rax, [rbx + 0x00]
	jmp		_while_start_a
_while_end_a:
	push	rax

	mov		rax, rdi
_while_start_b:
	mov		rbx, [rax]
	test	rbx,rbx
	je		_while_end_b
	cmp		rbx, rdx
	je		_while_end_b
_while_do_b:
	lea		rax, [rbx + 0x00]
	jmp		_while_start_b
_while_end_b:
	push	rax

	pop		rsi ;second
	pop		rdi ;first
	call	_ft_swap
	mov		rsi, [rsi]
	lea		rsi, [rsi + 0x00]
	mov		rdi, [rdi]
	lea		rdi, [rdi + 0x00]
	call	_ft_swap
	jmp		_ret

; rdi = begin
; rsi = cmp
ft_list_sort:
	test	rdi, rdi
	je		_ret
	mov		rax, [rdi]
	mov		r9, rsi
_while_start_c:
	test	rax, rax
	je		_ret
	mov		rbx, [rax + 0x00]
	test	rbx, rbx
	je		_ret
_while_do_c:
	mov		rcx, rax
_while_start_d:
	test	rbx,rbx
	je		_while_end_d
_while_do_d:
	push	rdi
	push	r9
	push	rax
	push	rbx
	push	rcx

	mov		rdi, rcx
	mov		rsi, rbx
	call	r9
	mov		r10, rax

	pop		rcx
	pop		rbx
	pop		rax
	pop		r9
	pop		rdi

	cmp		r10, 0
	jle		_after_cmp
	mov		rcx, rbx
_after_cmp:
	mov		rbx, [rbx + 0x00]
	jmp		_while_start_d
_while_end_d:
	mov		rdx, [rax + 0x00]

	push	rdi
	push	rsi
	push	rax
	push	rbx
	push	rdx

	mov		rsi, rax
	mov		rdx, rcx
	call	_ft_lst_swap

	pop		rdx
	pop		rbx
	pop		rax
	pop		rsi
	pop		rdi

	mov		rax, rdx
	jmp		_while_start_c
_while_end_c:
_ret:
	ret
