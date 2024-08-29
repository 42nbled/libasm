section .text
global ft_write
extern __errno_location

ft_write:
    mov rax, 1h
    syscall

	cmp		rax, 0
	jg		_ret

	mov		rbx, rax
	call	__errno_location
	neg		rbx
	mov		[rax], rbx
	mov		rax, -1
_ret:
	ret
