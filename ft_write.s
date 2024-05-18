section .text
global ft_write

ft_write:
    mov rax, 1h
    syscall
    ret
