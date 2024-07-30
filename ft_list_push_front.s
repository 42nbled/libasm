section .text
global ft_list_push_front
extern malloc

ft_list_push_front:
	; t_list *a = malloc(sizeof(t_list));
	push	rdi
	push	rsi
	mov		rdi, 16
	call	malloc
ft_list_push_front_2:
	pop		rsi
	pop		rdi
	mov		rbx, [rax]
	; a->next = *begin_list;
	mov		[rbx + 0x00], rdi
	; a->data = data;
	mov		[rbx + 0x08], rsi
	; *begin_list = a;
	mov		rdi, [rdi]
	mov		[rdi], rax
	ret
