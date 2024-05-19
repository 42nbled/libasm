section .text
global ft_strcmp

ft_strcmp:
    ; test    rsi, rsi
    ; je      _strcmp_ret_zero
    ; test    rdi, rdi
    ; je      _strcmp_ret_zero
_strcmp_body:
    mov     al, [rsi]
    mov     bl, [rdi]
    cmp     al, bl
    jne     _strcmp_ret
    test    al, al
    je      _strcmp_ret_zero
    inc     rsi
    inc     rdi
    jmp     _strcmp_body
_strcmp_ret_minus_one:
    mov     rax, -1
    ret
_strcmp_ret_zero:
    mov     rax, 0
    ret
_strcmp_ret_one:
    mov     rax, 1
    ret
_strcmp_ret:
    cmp     bl, al
    jl      _strcmp_ret_minus_one
    jmp     _strcmp_ret_one
