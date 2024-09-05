section .text
global ft_read
extern __errno_location

; rdi = int fd
; rsi = void *buf
; rdx = size_t nbyte
ft_read:
    mov		rax, 0
    syscall
	cmp		rax, 0
	jge		_ret

	mov		rbx, rax
	call	__errno_location wrt ..plt
	neg		rbx
	mov		[rax], ebx
	mov		rax, -1
_ret:
	ret
