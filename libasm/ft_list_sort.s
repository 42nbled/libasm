section .text
global ft_list_sort

; rdi = t_list **a
; rsi = t_list **b
_ft_swap:
								; t_list *c = *a;
	mov rax, [rdi]
								; *a = *b;
	mov	rbx, [rsi]
	mov [rdi], rbx
								; *b = c;
	mov [rsi], rax
	ret

; rdi = t_list **header
; rsi = t_list *a
; rdx = t_list *b
_ft_lst_swap:
								; if (!header)
								;     return;
	test	rdi, rdi
	je		_ret
								; if (!a)
								;     return;
	test	rsi, rsi
	je		_ret
								; if (!b)
								;     return;
	test	rdx, rdx
	je		_ret
								; if (a == b)
								;     return;
	cmp		rsi, rdx
	je		_ret

								; t_list **first = header;
	mov		rax, rdi
_while_start_a:
								; while (*first
	mov		rbx, [rax]
	test	rbx,rbx
	je		_while_end_a
								; && *first != a)
	cmp		rbx, rsi
	je		_while_end_a
_while_do_a:
								; { first = &(*first)->next; }
	lea		rax, [rbx + 0x00]
	jmp		_while_start_a
_while_end_a:
	push	rax

								; t_list **second = header;
	mov		rax, rdi
_while_start_b:
								; while (*second
	mov		rbx, [rax]
	test	rbx,rbx
	je		_while_end_b
								; && *second != b)
	cmp		rbx, rdx
	je		_while_end_b
_while_do_b:
								; { second = &(*second)->next; }
	lea		rax, [rbx + 0x00]
	jmp		_while_start_b
_while_end_b:
	push	rax
								; rsi = second
								; rdi = first
	pop		rsi
	pop		rdi
								; ft_swap(first, second);
	call	_ft_swap

								; rsi = &(*second)->next)
								; rdi = &(*first)->next
	mov		rsi, [rsi]
	lea		rsi, [rsi + 0x00]
	mov		rdi, [rdi]
	lea		rdi, [rdi + 0x00]
								; ft_swap(first, second);
	call	_ft_swap
	jmp		_ret

; rdi = t_list **begin_list
; rsi = int (*cmp)()
ft_list_sort:
								; if (!begin_list)
								; return;
	test	rdi, rdi
	je		_ret
								; a = *begin_list
	mov		rax, [rdi]
								; r9 = int (*cmp)()
	mov		r9, rsi
								; while (
_while_start_c:
								; a
	test	rax, rax
	je		_ret
								;  && a->next)
	mov		rbx, [rax + 0x00]
	test	rbx, rbx
	je		_ret
								; {
_while_do_c:
								;     c = a;
	mov		rcx, rax
								;     while (
_while_start_d:
								;     b)
	test	rbx,rbx
	je		_while_end_d
								;     {
_while_do_d:
								;     if (cmp(c, b) > 0) {
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
								;         c = b;
	mov		rcx, rbx
								;         }
_after_cmp:
								;     b = b->next;
	mov		rbx, [rbx + 0x00]
								;     }
	jmp		_while_start_d
_while_end_d:
								;     d = a->next;
	mov		rdx, [rax + 0x00]
								;     ft_lst_swap(begin_list, a, c);
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
								;     a = d;
	mov		rax, rdx
								; }
	jmp		_while_start_c
_ret:
	ret
