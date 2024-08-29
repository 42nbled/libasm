section .text
global ft_read
extern __errno_location

ft_read:
    mov rax, 0h
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
