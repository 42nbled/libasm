section .text
global ft_strdup
extern ft_strlen
extern malloc
extern ft_strcpy

; rdi = const char *s1
ft_strdup:
    test    rdi, rdi
    jz      _null_return

    mov     rsi, rdi
    push    rsi
    call    ft_strlen
    add     rax, 1
    mov     rdi, rax

    call    malloc wrt ..plt
    test    rax, rax
    jz      _null_return

    mov     rdi, rax
    pop     rsi
    call    ft_strcpy

    ret
_null_return:
    mov     rax, 0
    ret
