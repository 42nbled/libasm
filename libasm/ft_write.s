section .text
global ft_write
extern __errno_location

; rdi = int fd
; rsi = const void *buf
; rdx = size_t nbyte
ft_write:
    mov rax, 1
    syscall
    cmp rax, 0
    jge _return

    neg rax
    mov rbx, rax
    call __errno_location wrt ..plt
    mov [rax], ebx
    mov rax, -1

_return:
    ret