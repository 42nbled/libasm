section .text
global ft_list_size

ft_list_size:
	test	rdi, rdi
	je		_ret_zero
	mov		rdi, [rdi]
	test	rdi, rdi
	je		_ret_one
	call	ft_list_size
	inc		rax
	ret
_ret_one:
	mov		rax, 1
	ret
_ret_zero:
	mov		rax, 0
	ret
