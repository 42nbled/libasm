section .text
global ft_read

ft_read:
    mov rax, 0h
    syscall
    ret
