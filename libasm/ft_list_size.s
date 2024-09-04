section .text
global ft_list_size

; rdi = t_list **begin_list
ft_list_size:
								; if (begin_list == NULL)
								;     return 0;
	test	rdi, rdi
	je		_ret_zero
								; rdi = begin_list->next
	mov		rdi, [rdi + 0x08]
								; if (rdi == NULL)
								;     return 1;
	test	rdi, rdi
	je		_ret_one
								; return(ft_list_size(rdi) + 1);
	call	ft_list_size
	inc		rax
	ret
								; return 1
_ret_one:
	mov		rax, 1
	ret
								; return 0
_ret_zero:
	mov		rax, 0
	ret
