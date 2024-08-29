section .text
global ft_strlen

ft_strlen:
    mov     rax, 0
    jmp     _strlen_body
_strlen_inc:
    inc     rax
    inc     rdi
_strlen_body:
    cmp     byte [rdi], 0
    jne     _strlen_inc
    ret
