section .text
global ft_list_push_front
extern malloc

; rdi = t_list **begin_list
; rsi = void *data
ft_list_push_front:
	push	rdi
	push	rsi
								; t_list *a = malloc(sizeof(t_list));
	mov		rdi, 16
	call	malloc wrt ..plt
								; if (a)
	test	rax, rax
								;     return;
	je		_ret

	pop		rsi
	pop		rdi
								; a->next = *begin_list;
	mov		rbx, [rdi]
	mov		[rax + 0x08], rbx
								; a->data = data;
	mov		[rax + 0x00], rsi
								; *begin_list = a;
	mov		[rdi], rax
_ret:
	ret
