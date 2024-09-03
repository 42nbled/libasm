section .text
global ft_write
extern __errno_location

; rdi = int fd
; rsi = const void *buf
; rdx = size_t nbyte
ft_write:
    mov 	rax, 1
    syscall
	cmp		rax, 0
	jge		_ret

	mov		rbx, rax
	call	__errno_location
	neg		rbx
	mov		[rax], rbx
	mov		rax, -1
_ret:
	ret
