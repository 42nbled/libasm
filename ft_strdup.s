section .text
global ft_strdup
extern ft_strlen
extern malloc
extern ft_strcpy

ft_strdup:
    ; Check if the input string is NULL
    test    rdi, rdi
    jz      _null_return

    ; Calculate the length of the input string
    mov     rsi, rdi
    push    rsi
    call    ft_strlen
    add     rax, 1
    mov     rdi, rax

    ; Allocate memory for the new string
    call    malloc
    test    rax, rax
    jz      _null_return

    ; Copy the string to the allocated memory
    mov     rdi, rax
    pop     rsi
    call    ft_strcpy

    ret

_null_return:
    mov     rax, 0
    ret
