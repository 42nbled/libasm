section .text
global ft_list_remove_if
extern free

; r9	= data
; r10	= fonction
_macro_call:
	push	rcx
	push	rdx
	push	rdi
	push	rsi

	mov		rdi, r9
	call	r10

	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	ret

; rdi = t_list **begin_list
; rsi = void *data_ref
; rdx = int (*cmp)()
; rcx = void (*free_fct)(void *)
ft_list_remove_if:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 24

								; rbp - 08	= current
								; rbp - 10	= prev
								; rbp - 18	= temp
								; while (
_loop_start:
								; *begin_list
	mov		rax, [rdi]
	test	rax, rax
	je		_loop_end
								; && cmp((*begin_list)->data, data_ref) == 0
	mov		r9, [rax + 0x08]
	mov		r10, rdx
	call	_macro_call
	test	rax, rax
	jne		_loop_end
								; ) {
_loop_do:
								;     temp = *begin_list;
	mov		rax, [rdi]
	mov		[rbp - 0x18], rax
								;     *begin_list = (*begin_list)->next;
	mov		rax, [rdi]
	mov		rax, [rax + 0x00]
	mov		[rdi], rax
								;     free_fct(temp->data);
	mov		rax, [rbp - 0x18]
	mov		r9, [rax + 0x08]
	mov		r10, rcx
	call	_macro_call
								;     free(temp);
	mov		r9, [rbp - 0x18]
	mov		r10, free
	call	_macro_call
								; }
	jmp		_loop_start
_loop_end:
								; prev = *begin_list;
	mov		rax, [rdi]
	mov		[rbp - 0x10], rdi
								; if (prev == NULL)
	mov		rax, [rbp - 0x10]
	test	rax, rax
								;     return;
	je		_ret
								; current = prev->next;
	mov		rax, [rbp - 0x10]
	mov		rax, [rax + 0x00]
	mov		[rbp - 0x08], rax
								; while (
_second_loop_start:
								;    current
	mov		rax, [rbp - 0x08]
	test	rax, rax
	je		_ret
								;    ) {
_second_loop_do:
								;    if (cmp(current->data, data_ref) == 0)
	mov		r9, [rax + 0x08]
	mov		r10, rdx
	call	_macro_call
	test	rax, rax
	jne		_else
								;    {
_if:
								;        prev->next = current->next;
	mov		rax, [rbp - 0x10]
	mov		rbx, [rbp - 0x08]
	mov		rbx, [rbx + 0x00]
	mov		[rax + 0x00], rbx
								;        free_fct(current->data);
	mov		rax, [rbp - 0x08]
	mov		r9, [rax + 0x08]
	mov		r10, rcx
	call	_macro_call
								;        free(current);
	mov		r9, [rbp - 0x08]
	mov		r10, free
	call	_macro_call
								;        current = prev->next;
	mov		rax, [rbp - 0x10]
	mov		rax, [rax + 0x00]
	mov		[rbp - 0x08], rax
								;    }
	jmp		_second_loop_end
								;    else {
_else:
								;        prev = current;
	mov		rax, [rbp - 0x08]
	mov		[rbp - 0x10], rax
								;        current = current->next;
	mov		rax, [rbp - 0x08]
	mov		rax, [rax + 0x00]
	mov		[rbp - 0x08], rax
								;    }
_second_loop_end:
								; }
	jmp		_second_loop_start
_ret:
	add		rsp, 24
	pop		rbp
	ret
