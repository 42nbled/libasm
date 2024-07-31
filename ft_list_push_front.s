section .text
global ft_list_push_front
extern malloc

ft_list_push_front:
	; t_list *a = malloc(sizeof(t_list));
	push	rdi
	push	rsi
	mov		rdi, 16
	call	malloc
	test	rax, rax
	je		_ret
	pop		rsi
	pop		rdi
	; a->next = *begin_list;
	mov		rbx, [rdi]
	mov		[rax + 0x00], rbx
	; a->data = data;
	mov		[rax + 0x08], rsi
	; *begin_list = a;
	mov		[rdi], rax
_ret:
	ret
